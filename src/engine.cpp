#include "engine.hpp"
#include <iostream>
#include <memory>

/*
Where we load the model and extract its metadata using onnx runtime calls
*/
Engine::Engine() {
    // initiliaze onnx runtime components
    // TODO: Initialize session pointer 
    // TODO: Initialize input/output names
    // TODO: Set default model dimensions (640x640 for YOLOv8)

    // Initialize session (you likely want to pass environment + session options here)
    session_ = std::make_unique<Ort::Session>(env_, model_path.c_str(), session_options_);
    
    // vectors holding the pointers to character of input and output nodes
    // in onnx graph must be populated with actual input and output from
    // generated onnx model

    // initilaize variable to store number of model inputs and outputs
    // iterate through, and populate indidual character array 
    // with index and allocator
    // then populate overall unique pointer with those individual
    // character arrays until iteration is done
    Ort:AllocatorWithDefaultOptions allocator;

    size_t num_input_nodes = session_.GetInputCount();

    for (size_t i = 0; i < num_input_nodes; i++) {
        char* input_name = session_->GetInputName(i, allocator);
        input_names_.push_back(input_name);
    }

    size_t num_output_nodes = session_.GetOutputCount();

    for (size_t i = 0; i < num_output_nodes; i++) {
        char* output_name = session_->GetOutputName(i, allocator);
        output_names_.push_back(output_name);
    }

    // set model input and output dimensions by dynamically 
    // getting the info from model using Ort member functions
    // get the type info (model and shape) of session_ pointer
    // intialize tensor info using auto type deduction and tensor
    // shape and info member fucntion of type info
    // populate input shape vector with shape of tensor info
    // append input shape vector to input shapes (dimension) 
    
    for (size_t i = 0; i < num_input_nodes; i++) {
        Ort::TypeInfo type_info = session_->GetInputTypeInfo();
        auto tensor_info = type_info_.GetTensorTypeAndShapeInfo();
        std::vector<int64_t> input_shape = tensor_info_.GetShape();

        input_shapes_.push_back(input_shape);
    }
    
    size_t num_outputs = session_.GetOutputCount();

    for (size_t i = 0; i < num_output_nodes; i++) {
        Ort:TypeInfo type_info = session_->GetOutputTypeInfo();
        auto tensor_info = type_info_.GetTensorTypeAndShapeInfo();
        std::vector<int64_t> output_shape = tensor_info_GetShape();

        output_shapes_.push_back(output_shape);
    }
}

// Destructor: Clean up resources
Engine::~Engine() {
    // TODO: Clean up ONNX session if it exists
    // uni
    // TODO: Release any allocated memory
}

// Load ONNX model from file path
bool Engine::loadModel(const std::string& modelPath) {
    // TODO: Check if model file exists
    // TODO: Create ONNX Runtime environment
    // TODO: Set session options (optimization level, thread count)
    // TODO: Create inference session from model file
    // TODO: Get input/output tensor info (names, shapes, types)
    // TODO: Store input/output metadata for later use
    // TODO: Return true if successful, false otherwise
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