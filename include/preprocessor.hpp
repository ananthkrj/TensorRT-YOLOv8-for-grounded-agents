// header guards
#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include <opencv2/opencv.hpp>

/* The goal of preprocessing is to preprocess the input,
resize, convert Bgrt to rgb, normalize, and convertoblob

And set environment configurations for the different
types of testing environments
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
    std::string environment_profile;

    // constructor for struct, as we use field initialization
    // in struct
    // struct initialization using preprocess info variables
    PreprocessInfo() : scale_x(1.0f), scale_y(1.0f), pad_x(0), pad_y(0) {}
};

// another struct here for enviornment info
struct EnvironmentConfig {
    // find out why i need all these variables
    // for configuartion of different colored
    // environments

    // brightness contrast adjustments
    double brightness_factor;
    double contrast_factor;
    double gamma_correction;

    // noise reduction
    // gaussian blur, and vairable for blur in kernel
    bool apply_gaussian_blur;
    cv::Size blur_kernel_size;

    // historgram equalization
    bool apply_clahe;
    double clahe_clip_limit;
    cv::Size clahe_tile_size;

    // color space adjustments
    bool enhance_saturation;
    double saturation_factor;

    // normalization parameter
    cv::Scalar mean;
    cv::Scalar std;

    // constructor with all defaults
    EnvironmentConfig() : 
        brightness_factor(1.0), contrast_factor(1.0), gamma_correction(1.0),
        apply_gaussian_blur(false), blur_kernel_size(3, 3),
        apply_clahe(false), clahe_clip_limit(2.0), clahe_tile_size(8, 8),
        enhance_saturation(false), saturation_factor(1.0),
        mean(cv::Scalar(0.485, 0.456, 0.406)), std(cv::Scalar(0.229, 0.224, 0.225)) {}
};
class Preprocessor {

public:
    // question:
    // why does only engine.cpp have a destructor why not
    // other files?: Becuase engine files are the only one where
    // we manually allocate memory, used for engine properties.
    // in all other files, mainly utilize stl's like vector and string
    // for storing memory and, cleanup for that is destructed within
    // the compiler itself. 

    // constructor
    // parameters will be target width and target height
    // dimensions should be 640x640
    Preprocessor(int target_width = 640, int target_height = 640);

    // main preprocessing pipeline
    // cummmulative preprocessing member function
    // all the preprocessing member functions have cv::Mat
    // as there data types
    cv::Mat preprocess(const cv::Mat& input);
    cv::Mat preprocess(const cv::Mat& input, const std::string* environment);

    // environment specific methods
    // set environment profile
    void setEnvironmentProfile(const std::string& profile);
    // create custom environment
    // get avail environment

    // individual preprocessing steps
    // individual components of preprocessing is resizing
    // with padding, converting bgrt to rgb, normalizing,
    // and converting to blob
    cv::Mat resizeWithPadding(const cv::Mat& input, int target_width, int target_height);
    cv::Mat convertBGRTtoRGB(const cv::Mat& input);
    cv::Mat normalize(const cv::Mat& input);
    cv::Mat convertoBlob(const cv::Mat& input);

    // lightiing/enhancement methods

    // grayscale handling

    // utility methods

    // getters
    // need to get the struct preprocessing info
    // need to get the target size
    PreprocessInfo getLastPreprocessInfo() const;
    cv::Size getTargetSize() const;
    // get current config
    // get curr env

    // setters
    void setTargetSize(int width, int height);
    void setNormalizationParams(const cv::Scalar& mean, condt cv::Scalar& std);
    // set env config

private:
    // target dimensions
    int target_width_;
    int target_height_;

    // current environment configuration
    EnvironmentConfig current_config_;
    std::string current_environment_;

    // predefined environment cnfigs
    // put in form of a hashmap
    std::map<std::string, EnvironmentConfig> environment_configs_;

    // last preprocessing info
    // from struct
    PreProcessInfo last_preprocess_info_;

    // private helper methods
    // initialize environment configs
    void initializeEnvironmentConfigs();

    // private helper method for updating preprocessinfo
    void updatePreprocessInfo(const cv::Mat& original, const cv::Mat& processed,
                              float scale_x, float scale_y, int pad_x, int pad_y);

    // apply configured enhancements
    cv::Mat applyConfiguredEnhancements(const cv::Mat& input, const EnvironmentConfig& config);

    // environment specific envoirnment enhancement chains
    // process bright environment
    cv::Mat processBrightEnv(const cv::Mat& input);

    // process dark environment
    cv::Mat processDarkEnv(const cv::Mat& input);

    // process grainy env
    cv::Mat processGrainyEnv(const cv::Mat& input);

    // process grayscale env
    cv::Mat processGrayscaleEnv(const cv::Mat& input);
};

// header guard
#endif