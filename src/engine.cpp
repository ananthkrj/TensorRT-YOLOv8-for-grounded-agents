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
        char* name = session_.GetInputName(i, allocator);
        input_names_.push_back(name); 

        // utilize type info ort struct, type info -> tensor info -> tensorshapeandinfo
        // need these series of steps to populate the input shape
        Ort::TypeInfo type_info = session_->GetTypeInfo();
        auto tensor_info = session_->GetTensorTypeAndShapeInfo();
        input_shapes_.push_back(tensor_info.GetShape());
    }

    // populate output names and shapes
    for (int i = 0; i < num_output_nodes = session)

}

// Run inference on preprocessed input
std::vector<float> Engine::runInference(const cv::Mat& preprocessedInput) {
    // TODO: Create input tensor from cv::Mat data
    // TODO: Prepare input tensor array for session
    // TODO: Prepare output tensor array for session
    // TODO: Run inference session
    // TODO: Extract output data from tensor
    // TODO: Convert output to std::vector<float>
    // TODO: Return output vector
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
}

std::vector<float> Engine::tensorToVector(const Ort::Value& tensor) {
    // convert tensor to vector
}