// header guards
#ifndef POSTPROCESSOR_HPP
#define POSTPROCESSOR_HPP

// libraries used
#include <opencv2/opencv,hpp>

#include <vector>
#include <string>

#include "preprocessor.hpp"

// create struct for common variables to be used
// in postprocessing
// this struct will be used in member functions
/*
class id, class name, confidence of bounding,
width, and height (rec2f box), center point
(point2f)
*/
struct Detection {
    int class_id;
    std::string class_name;
    float confidence;
    cv::Rect2f bbox;
    cv::Point2f center;

    // understand need for this constructor
    // initialization in detection struct

    // constructor with class id and 
    // confidence initialized
    Detection() : class_id(-1), confidence(0.0f) {}

    // constructor with params
    Detection(int id, const std::string& name, float conf, const cv::Rect2f& box)
        : class_id(id), class_name(name), confidence(conf), bbox(box) {
        center = cv::Point2f(box.x + box.width / 2, box.y + box.height / 2);
    }
};
class Postprocessor {

private:
    // threshold variables
    float confidence_threshold_;
    float nms_threshold_;

    // class information
    // vector of strings for class names
    std::vector<std::string> class_names_;
    int num_classes_;

    // output parameters
    // number of detections and output dimensions
    // 8400 for yolov8
    int num_detections_;
    // 84 for yolov8
    int output_dimensions_;

public:
    // constructor with threshold values 
    // passed as parameters
    // find out why these are the tresholds
    Postprocessor(float confidence_threshold = 0.5f, float threshold = 0.4f);


    // main cummalative preprocesing pipeline
    // pass in output, and preprocessinfo struct as parameters
    std::vector<Detection> postprocess(const std::vector<float>& output, const PreprocessInfo& preprocess_info);

    // indidual preprocessing steps
    // parsing output
    std::vector<Detection> parseOutput(const std::vector<float>& output);
    // filter by confidence
    std::vector<Detection> confidenceFilter(const std::vector<Detection>& detections);
    // apply NMS
    std::vector<Detection> applyNMS(const std::vector<Detection>& detections);
    // scale the coordinates
    std::vector<Detection> scaleCord(const std::vector<Detection>& detections, const PreprocessInfo& preprocess_info);

    // utility methods
    // calculate intersection over union
    float calculateIoU(const Detection& det1, const Detection& det2);
    // pass name of the class name path as a parameter
    bool loadClassNames(const std::string& class_names_path);

    // getters and setters
    // confidence, nms, set modeloutput dimensions
    float getConfidenceThreshold() const;
    float getNMSThreshold() const;
    void setConfidenceThreshold(float threshold);
    void setNMSThreshold(float threshold);
    void setModelOutputDimensions(int num_detections, int output_dimensions);

    // debug methods


private:
    // Private helper methods
    cv::Rect2f convertCenterToRect(float center_x, float center_y, float width, float height);
    std::string getClassName(int class_id) const;
    void sortDetectionsByConfidence(std::vector<Detection>& detections);
};

#endif