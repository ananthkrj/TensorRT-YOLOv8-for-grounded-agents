// preprocessor.cpp implementation logic:
// - Constructor: store input dimensions
// - preprocess(): resize image, convert BGR to RGB, normalize, copy to float buffer
// - resizeImage(): use cv::resize() to match model input size
// - normalizeImage(): convert uint8 pixels to float, apply normalization
#include "preprocessor.hpp"

// constructor
preprocessor::preprocessor(int inputWidth, int inputHeight) {

}

// destructor
preprocessor::~preprocessor() {

}

bool preprocessor::preprocess(const cv::Mat& image, float* output) {

}


cv::Mat preprocessor::resizeImage(const cv::Mat& image) {

}

preprocessor::void normalizeImage(const cv::Mat& image, float* buffer) {

}
