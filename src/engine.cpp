/*
Goal of engine.cpp:
Implementation details, private methods, 
TensorRT API calls
*/
#include "engine.hpp"
#include <iostream>
#include <memory>

// constructor and destructor

Engine::Engine() {
    // TODO: Initialize session pointer to nullptr
    // TODO: Initialize input/output names
    // TODO: Set default model dimensions (640x640 for YOLOv8)
}

Engine::~Engine() {
    // TODO: Clean up ONNX session if it exists
    // TODO: Release any allocated memory
}

// loading onnx file
bool Engine::loadModel(const std::string& modelPath) {
    // TODO: Check if model file exists
    // TODO: Create ONNX Runtime environment
    // TODO: Set session options (optimization level, thread count)
    // TODO: Create inference session from model file
    // TODO: Get input/output tensor info (names, shapes, types)
    // TODO: Store input/output metadata for later use
    // TODO: Return true if successful, false otherwise
}

// running inference on preprocessed input
std::vector<float> Engine::runInference(cv::Mat& preprocessedInput) {
    // TODO: Create input tensor from cv::Mat data
    // TODO: Prepare input tensor array for session
    // TODO: Prepare output tensor array for session
    // TODO: Run inference session
    // TODO: Extract output data from tensor
    // TODO: Convert output to std::vector<float>
    // TODO: Return output vector
}

// const member functions, getting the model
cv::Size Engine::getInputSize() const {
    // TODO: Return model input dimensions (usually 640x640 for YOLOv8)
}

// dimensions and getting number of classes
// model can detect
int Engine::getNumClasses() const {
    // TODO: Calculate from output tensor shape
    // TODO: YOLOv8 output format: [1, 84, 8400] where 84 = 4(bbox) + 80(classes)
}