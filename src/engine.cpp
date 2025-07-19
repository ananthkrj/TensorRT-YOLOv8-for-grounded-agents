#include "engine.hpp"
#include <iostream>
#include <memory>
#include <filesystem>

/*
Where we load the model and extract its metadata using onnx runtime calls
*/
Engine::Engine() {
    // initiliaze onnx runtime components
    // TODO: Initialize the session characteristics
    // TODO: Initialize input/output names
    // TODO: Set default model dimensions (640x640 for YOLOv8)

    // initialize the environment name
    env_ = std::make_unique<Ort::Env>(ORT_LOGGING_LEVEL_WARNING, "Yolov8Engine");
    // initialize the session options as well
    session_options_ = std::make_unique<Ort::SessionOptions>();
    // set graph optimization (highest level) for session opetions
    session_options_->SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
}

// no need for a destructor, because i am not allocating anything in the
// the constructor

// Load ONNX model from file path

// what to test: 
bool Engine::loadModel(const std::string& modelPath) {
    // TODO: Check if model file exists
    // TODO: Create ONNX Runtime environment
    // TODO: Set session options (optimization level, thread count)
    // TODO: Create inference session from model file
    // TODO: Get input/output tensor info (names, shapes, types)
    // TODO: Store input/output metadata for later use
    // TODO: Return true if successful, false otherwise

    // check if model file exists
    namespace fs = std::filesystem;
    // turn this into a conditional
    if (!fs::exists(modelPath)) {
        std::cerr << "Model file is not found at " << modelPath << '\n';
        return false;
    }

    // crearte onnxruntime enviornment

    // clear previous session
    session_.clear()

    // create session, using env, model path, and session_options
    // pass the environment and session options by value
    session_ = std::make_unique<Ort::Session>(*env_, model_path.c_str(), *session_options_);

    // reset metadata
    input_names_.clear();
    output_names_.clear();
    input_shapes_.clear();
    output_shapes_.clear();

    // declare ort allocator, way to access standard memory management provided by ort
    Ort::AllocatorWithDefaultOptions allocator;

    // declare input and output nodes
    size_t num_input_nodes = session_->GetInputCount();
    size_t num_output_nodes = session_->GetOutputCount();

    // populate input names and shapes
    for (int i = 0; i < num_input_nodes; i++) {
        // allocate each node/index and store in char pointer
        char* name = session_->GetInputName(i, allocator);
        input_names_.push_back(name); 

        // utilize type info ort struct, type info -> tensor info -> tensorshapeandinfo
        // need these series of steps to populate the input shape 
        Ort::TypeInfo type_info = session_->GetTypeInfo();
        auto tensor_info = session_->GetTensorTypeAndShapeInfo();
        input_shapes_.push_back(tensor_info.GetShape());
    }

    // populate output names and shapes
    for (int i = 0; i < num_output_nodes = session) {
        // allocate each node/index and store it in a char point
        char* name = session_->GetOutputName(i, allocator);
        output_names_.push_back(name);

        // utilize type info ort struct, 
        // type info -> tensor info -> append to oujtpit sjapes
        Ort::TypeInfo type_info = session_->GetTypeInfo();
        auto tensor_info = session_->GetTensorTypeAndShapeInfo();
        output_shapes_.push_back(tensor_info.GetShape());
    }

    return true;

}

// before moving onto other memb functions, write down all onnx methods

// Run inference on preprocessed input

// find out what it means to run inference on preprocessed input
std::vector<float> Engine::runInference(const cv::Mat& preprocessedInput) {
    // definition of runningInference: Takes the preprocessedInput and runs it through
    // the model, and return the results

    // 1. Convert preprocessedInput to a float if needed
    // find out what begin and end does, how begin and end
    // allows me to fully convert a cv::Mat object into a float object
    std::vector<float> inputTensorValues = (preprocessedInput.begin<float>, preprocessedInput.end<float>);
    // 2. create an onnx tensor from the preprocessedinput (integral)

    // define input tensor shape as {1, 3, 640, 640}
    std::vector<int64_t> inputShape = {1, 3, preprocessedInput.rows, preprocessedInput.cols};

    // create tensor, usitlise memoryinfo
    // tensor data will reside on the CPU, so need to use CreateCPU api part of MemoryInfo
    // creating tensors using memoryInfo class, and createCPU memberfunction of this class, along with device
    // allocator and OrtmemTypeCPU as parameters
    Ort::MemoryInfo memoryInfo= Ort::MemoryInfo::CreateCPU(OrtDeviceAllocator, OrtMemTypeCPU);

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

    auto outputTensor = session_.Run(Ort::SessionOptions{nullptr}, 
    input_names_.data(), &inputTensor, 1, output_names_.data(), output_names_.size());

    // 5. convert Ort::value to a float value
    // 6. return result to be preprocessed
    // use tensorToVector helper finmction, pass in outputTensor(first value) as the parameter

    return tensorToVector(outputTensor[0]);
}

    
// Get model input dimensions
cv::Size Engine::getInputSize() const {
    // TODO: Return model input dimensions (usually 640x640 for YOLOv8)
    // return input size
    return input_shapes_;
}

// Get number of classes the model can detect
int Engine::getNumClasses() const {
    // TODO: Calculate from output tensor shape
    // TODO: YOLOv8 output format: [1, 84, 8400] where 84 = 4(bbox) + 80(classes)
    // return number of classes
}

// private member functions

bool Engine::initializeSession(const std::string& model_path) {
    // initialize the onnx runime sessions
}

void Engine::extractModelMetadata() {
    // extract model metadata

    // Get the input/output names and shapes
}

std::vector<float> Engine::tensorToVector(const Ort::Value& tensor) {
    // helper function to convert tensor to vector, will be used in runInference

    // Convert Ort::value tensor to a c++ vector
}