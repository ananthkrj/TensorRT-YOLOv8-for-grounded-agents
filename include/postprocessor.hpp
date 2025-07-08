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
    // constructor

    // main cummalative preprocesing pipeline

    // indidual preprocessing steps

    // utility methods

    // getters and setters

    // debug methods


private:
    // private helper methods
};

#endif