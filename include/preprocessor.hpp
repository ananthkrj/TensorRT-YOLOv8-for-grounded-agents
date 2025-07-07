#pragma once
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

    // main preprocessing pipeline

    // individual preprocessing steps

    // getters

    // setters

// why private again?
private:
    // private helper methods
    
};