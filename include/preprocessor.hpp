// header guards
#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include <opencv2/opencv.hpp>

/* The goal of preprocessing is to preprocess the input,
resize, convert Bgrt to rgb, normalize, and convertoblob
*/

// struct for preprocessinginfo
// difference in constructor for stuct and oop constructor?
struct PreprocessInfo {
    float scale_x;
    float scale_y;
    int pad_x;
    int pad_y;
    // specifiy size of image
    cv::Size original_size;
    cv::Size target_size;

    // constructor for struct, as we use field initialization
    // in struct
}

class Preprocessor {
private:
    // target dimensions
    int target_width_;
    int target_height_;

    // normalization parameters
    cv::Scalar mean_;
    cv::Scalar std_;

    // last preprocessing info
    // from struct
    PreProcessInfo last_preprocess_info_;

public:
    // question:
    // why does only engine.cpp have a destructor why not
    // other files? Is raii still being upheld in other files?
    // compile generated destructor does correcmtly already

    // constructor
    // parameters will be target width and target height
    // dimensions should be 640x640
    Preprocessor(int target_width = 640, int target_height = 640);

    // main preprocessing pipeline
    // cummmulative preprocessing member function
    // all the preprocessing member functions have cv::Mat
    // as there data types
    cv::Mat preprocess(const cv::Mat& input);

    // individual preprocessing steps
    // individual components of preprocessing is resizing
    // with padding, converting bgrt to rgb, normalizing,
    // and converting to blob
    cv::Mat resizeWithPadding(const cv::Mat& input, int target_width, int target_height);
    cv::Mat convertBGRTtoRGB(const cv::Mat& input);
    cv::Mat normalize(const cv::Mat& input);
    cv::Mat convertoBlob(const cv::Mat& input);

    // getters
    // need to get the struct preprocessing info
    // need to get the target size
    PreprocessInfo getLastPreprocessInfo() const;
    cv::Size getTargetSize() const;

    // setters
    void setTargetSize(int width, int height);
    void setNormalizationParams(const cv::Scalar& mean, condt cv::Scalar& std);

// why private again?
private:
    // private helper methods
    // private helper method for updating preprocessinfo
    void updatePreprocessInfo(const cv::Mat& original, const cv::Mat& processed,
                              float scale_x, float scale_y, int pad_x, int pad_y);

};

// header guard
#endif