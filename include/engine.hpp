
#ifndef ENGINE_HPP
#define ENGINE_HPP

// System includes
#include <string>
#include <vector>
#include <memory>

// Third-party includes
// find out why error appears for 
// including opencv library
#include <opencv2/opencv.hpp>
#include <onnxruntime_cxx_api.h>

// Forward declarations (if needed)
class Preprocessor;

class Engine {
private:
    // ONNX Runtime components
    std::unique_ptr<Ort::Env> env_;
    std::unique_ptr<Ort::Session> session_;
    std::unique_ptr<Ort::SessionOptions> session_options_;
    
    // Model metadata
    std::vector<const char*> input_names_;
    std::vector<const char*> output_names_;
    std::vector<std::vector<int64_t>> input_shapes_;
    std::vector<std::vector<int64_t>> output_shapes_;
    
    // Model parameters
    cv::Size input_size_;
    int num_classes_;
    bool model_loaded_;

public:
    // Constructor and destructor
    Engine();
    ~Engine();
    
    // Delete copy constructor and assignment operator (RAII best practice)
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    
    // Core functionality
    bool loadModel(const std::string& model_path);
    std::vector<float> runInference(const cv::Mat& preprocessed_input);
    
    // Getters
    cv::Size getInputSize() const;
    int getNumClasses() const;
    bool isModelLoaded() const;
    
    // Utility methods
    void printModelInfo() const;
    
private:
    // Private helper methods
    bool initializeSession(const std::string& model_path);
    void extractModelMetadata();
    std::vector<float> tensorToVector(const Ort::Value& tensor);
};
