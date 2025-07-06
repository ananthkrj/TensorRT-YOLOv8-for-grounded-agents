/*
Goal of engine.hpp: Class declaration, public interface, includes

pragma once used to make sure header file
is not used more than once in compilation

including NvInfer.h allows us to enable C++ API
for tensorRT
*/

#pragma once
#include <opencv2/opencv.hpp>
#include <string>


class Engine {
public:
    // constructor and destructor
    Engine();

    ~Engine();

    // member func for loading onnx model from file
    // pass onnx file as it is a string
    bool loadModel(const std::string& modelPath);
    
    // run inference on preprocessed input
    std::vector<float> runInference(const cv::Mat& prepreprocessedInput);


private:
    // get model input dimensions
    cv::Size getInputSize() const;

    // get number of classes model can detect
    int getNumClasses() const;
};