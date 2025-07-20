#include "engine.hpp"
#include <iostream>
#include <memory>
#include <filesystem>

/*
Constructor where we intiialize session components such as env 
and session_options + optimization. Will be used to initialize
session object in initializeSession() member function
*/
Engine::Engine() {
    // initialize the environment name
    env_ = std::make_unique<Ort::Env>(ORT_LOGGING_LEVEL_WARNING, "Yolov8Engine");
    // initialize the session options as well
    session_options_ = std::make_unique<Ort::SessionOptions>();
    // set graph optimization (highest level) for session opetions
    session_options_->SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
}

// no need for a destructor, because i am not allocating anything in the
// the constructor

/**
 * check if initialize sesison works and call
 * extractModelMetaData member fucntion
*/
bool Engine::loadModel(const std::string& modelPath) {

    // check if initializesession works
    if (!(initializeSession(modelPath))) {
        std::cerr << "Session is not initialized";
    }
    
    // and call extractModelMetaDaata
    extractModelMetaData();
    return true;
}

/**
 * Initializes session
*/
bool Engine::initializeSession(const std::string& model_path) {
    // check if model_path exists
    // use std::filesystem to check if model_path(string parameter) exists
    namespace fs = std::filesystem;
    if (!fs::exists(model_path)) {
        std::cerr << "Model does not exist at: " << model_path << '\n';
        return false;
    }
    
    // clear session, can use clear on unique pointers
    session_.clear();

    // intilize session with constructor configurations, pointer to environment, 
    // model_path as a c string, and pointer to session_options
    // use std::make_unique to create and return a unique pointer to a newly allocted object
    session_ = std::make_unique<Ort::Session>(*env_, model_path.c_str(), *session_options_);

    return true;
}

// before moving onto other memb functions, write down all onnx methods

// Run inference on preprocessed input

std::vector<float> Engine::runInference(const cv::Mat& preprocessedInput) {
    // definition of runningInference: Takes the preprocessedInput and runs it through
    // the model, and return the results

    // 1. Convert preprocessedInput to a float if needed
    // find out what begin and end does, how begin and end
    // allows me to fully convert a cv::Mat object into a float object
    std::vector<float> inputTensorValues(preprocessedInput.begin<float>, preprocessedInput.end<float>);
    // 2. create an onnx tensor from the preprocessedinput (integral)

    // define input tensor shape as {1, 3, 640, 640}
    std::vector<int64_t> inputShape = {1, 3, preprocessedInput.rows, preprocessedInput.cols};

    // create tensor, usitlise memoryinfo
    // tensor data will reside on the CPU, so need to use CreateCPU api part of MemoryInfo
    // creating tensors using memoryInfo class, and createCPU memberfunction of this class, along with device
    // allocator and OrtmemTypeCPU as parameters
    Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCPU(OrtDeviceAllocator, OrtMemTypeCPU);

    // create variable called input tensor and initialize it with the CreateTensor Ort API function
    // initialize CreateTensor with float converted preprocessed image, data and size of the inputted tensor values,
    // and data and size of inputShape, pass these parameters
    // Ort::Value is a container for data passed to and from the inference engine
    
    Ort::Value inputTensor = Ort::Value::CreateTensor(memoryInfo, 
    inputTensorValues.data(), inputTensorValues.size(), inputShape.data(), inputShape.size());
    
    // 4. run the session (integral)
    // intialize a variable outputTensors, and run the session
    // pass these parameters: RunOptions{nullptr}, input_names.data(), &inputTensor, 1, output_names.data(), 
    // iutput_names.size()

    // Ort::RunOptions{nullptr}: creates a default run options object with no configuration, can use
    // this to set a tag for profile/logging
    // &inputTensor: pointer to the tensor that was created
    // input_names_.data(): input node names
    // output_names_.data(): output node names
    // output_names_.size(): size of output nodes
    // 1: number of input tensors passing in: must be specified in onnx runtime

    auto outputTensors = session_.Run(Ort::RunOptions{nullptr}, 
    input_names_.data(), &inputTensor, 1, output_names_.data(), output_names_.size());

    // 5. convert Ort::value to a float value

    // convert using GetTensorMutableData from onnx class
    float* floatArray = outputTensors[0].GetTensorMutableData();
    // tensorInfo
    auto tensorInfo = outputTensors[0].GetTensorTypeAndShapeInfo();
    // num of elements in tensor, using elementcount from tensortypeandhshapeinfo
    size_t numElements = tensorInfo.GetElementCount();

    // return coverted tensor to float vector
    return std::vector<float>(floatArray, floatArray + numElements);
}

/* Don't even need likely, keep in case
// if useful later
*/
// Get model input dimensions
cv::Size Engine::getInputSize() const {
    // TODO: Return model input dimensions (usually 640x640 for YOLOv8)
    // return input size
    return input_shapes_[0];
}

// Get number of classes the model can detect
/*
Return the number of classes in the model
Just return [0] and [1] of output_shapes_
Maybe useful in future implementations
*/
int Engine::getNumClasses() const {
    // TODO: Calculate from output tensor shape
    // TODO: YOLOv8 output format: [1, 84, 8400] where 84 = 4(bbox) + 80(classes)
    // return number of classes
    return output_shapes_[0][1];
}

/*
To fix and test:

Missing functionality:

input_names_ and output_names_ should store const char* or convert to std::string
Memory management for ONNX allocated strings needs proper handling

*/

void Engine::extractModelMetadata() {
    // input and output metadata population

    // reset metadata, can use clear maybe both names and shapes are vector containers
    input_names_.clear();
    input_shapes_.clear();
    output_names_.clear();
    output_names_.clear();

    // declare allocator with the default options from onnx c++ api
    Ort::AllocatorWithDefaultOptions allocator;

    // declare input and output nodes that we will iterate through, based on functions
    // that will be used with session_ object and from Session class
    size_t num_input_nodes = session_.GetInputCount();
    size_t num_output_nodes = session_.GetOutputCount();

    // populate input metadata
    // emplace back used when the goal is to construct an object
    // directly within a containers allocatd memory (passing allocator)
    // within name char pointer onto input_names
    for (int i = 0; i < num_input_nodes; i++) {
        char* name = session_->GetInputCount(i, allocator);
        input_names_.emplace_back(name);
        allocator.Free(name);

        // utlize type info struct
        Ort::TypeInfo type_info = session_->GetTypeInfo();
        auto tensor_info = type_info._GetTensorTypeAndShapeInfo();
        input_shapes_.push_back(tensor_info.GetShape());
    }
    
    // populate output metadata
    for(int i = 0; i < num_output_nodes; i++) {
        // name
        // go from raw char pointer of name, to input names, then freeing allocated mem
        char* name = session_->GetOutputCount(i, allocator);
        output_names_.emplace_back(name);
        allocator.Free(name);

        // shape
        // utilaize typeInfo struct again
        Ort::TypeInfo type_info = session_->GetTypeInfo();
        auto tensor_info = type_info.GetTensorTypeAndShapeInfo();
        output_shapes_.push_back(tensor_info.GetShape());
    }
}