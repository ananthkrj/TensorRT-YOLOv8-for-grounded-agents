#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

// Create a class that will act as a wrapper for preprocessing
// the image input

// preprocessing will need constructor/destructor and member functions
// that will execute these actions:
// OpenCV c++: resizing, pad, and normalize image output
class Preprocessor {

public:
// constructor
// dimensions of image
    preprocessor(int inputWidth, int inputHeight);
// destructor
    ~preprocessor();

// public member functions

// need to process image, convert image to model input format
// pass by image by reference
bool preprocess(const cv:Mat& image, float* output);

// need to resize to model dimensions
// also pass unchangebale image by reference
cv::Mat resizeImage(const cv::Mat& image);

// and normalize pixel values to floated memory where
// neormalized floats will go
// float* buffer is a pointer to pre-alloca
void normalizeImage(const cv::Mat& image, float* buffer);

private:
// parameters to pass into constructor
    int m_inputWidth;
    int m_inputHeight;

    // target mean/std for normalization
};