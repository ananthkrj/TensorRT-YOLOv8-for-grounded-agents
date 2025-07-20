// header guards
#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include <opencv2/opencv.hpp>
#include <string>

/* The goal of preprocessing is to preprocess the input,
resize, convert Bgrt to rgb, normalize, and convertoblob

And set environment configurations for the different
types of testing environments
*/

// struct for preprocessinginfo information and important
// variables that will be used
struct PreprocessInfo {
    float scale_x;
    float scale_y;
    int pad_x;
    int pad_y;
    cv::Size original_size;
    cv::Size target_size;

    // struct intitialization with variables
    PreprocessInfo() : scale_x(1.0f), scale_y(1.0f), pad_x(0), pad_y(0) {}
};

// use enum class for environment types for testing, find out
// what enum class is
// the two different colors i will be initializing camera
// environment with
enum class CameraEnvironment {
    NORMAL_COLOR,
    GRAYSCALE
};

// class for preprocessing
class Preprocessor {
public:
    // constructor with target dimensions
    // always 640x640 for yolov8
    Preprocessor(int target_width = 640, int target_height = 640);

    // main preprocessing pipeline, 
    // pass in the input image and normal color camera environment
    cv::Mat preprocess(cv::Mat& input, CameraEnvironment env = CameraEnvironment::NORMAL_COLOR);

    // core preprocessing steps
    // the core preprocessing stpes are always:
    // 1. Resize with padding
    // 2. Convert BGR to RGB
    // 3. normalize
    // 4. convert to blob
    cv::Mat ResizeWithPadding(const cv::Mat& input);
    cv::Mat ConvertBGRtoRGB(const cv::Mat& input);
    cv::Mat Normalize(const cv::Mat& input);
    cv::Mat ConvertToBlob(const cv::Mat& input);

    // environment specific preprocrssing
    cv::Mat processNormalColor(cv::Mat input);
    cv::Mat processGrayscale(cv::Mat input);

    // utility methods (will be used to error check and convert)
    bool IsGrayscale(cv::Mat& input) const;
    cv::Mat convertToGrayscale(const cv::Mat& input);
    cv::Mat grayscaleToRGB(const cv::Mat& input);


    // getters (find out what these getters would even be used for)
    PreprocessInfo getLastPreprocessInfo() const;
    cv::Size getTargetSize() const;


private:
    // variables that will be used for member funcs
    // target dimensions
    int target_width_;
    int target_height_;

    // normalization parameters (ImageNet defaults)
    cv::Scalar mean_;
    cv::Scalar std_;

    // last preprocessing info
    PreprocessingInfo last_preprocess_info;

    // helper method to update preprocessing info
    void updatePreprocessInfo(const cv::Mat& original, const cv::Mat& processed, 
    float scale_x, float scale_y, int pad_x, int pad_y);
}

#endif 