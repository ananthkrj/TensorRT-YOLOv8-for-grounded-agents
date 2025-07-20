// header guards
#ifndef POSTPROCESSOR_HPP
#define POSTPROCESSOR_HPP

// libraries used
#include <opencv2/opencv.hpp>
#include <vector>

// create struct for common variables to be used
// in postprocessing
// this struct will be used in member functions
/*
class id, class name, confidence of bounding,
width, and height (rec2f box), center point
(point2f)

Goal is to process the output and get it ready for
 visualization
*/

// structure for detection
// struct initialization will apply these variables
// bounding box, confidence score, class ID, and optional class name
// find out what these variables do
struct Detection {
    cv::Rect bbox;
    float confidence;
    int class_id;
    std::string class_name;

    // two list initializations
    Detection() : confidence(0.0f), class_id(-1) {}
    // figure out if this initialization is correct
    Detection(const cv::Rect& box, float conf, int id
        : bbox(box), confidence(conf), class_id(id)) {}
};

class Postprocessor {
public:
    // constructor with default yolov8 parameters
    Postprocessor(float confidence_threshold_ = 0.5f, float nms_threshold_ = 0.4f);

    // main postprocessing pipeline
    std::vector<Detection> postprocess(const std::vector<float>& raw_output, 
    const cv::Size& original_size, const cv::Size& input_size);

    // core postprocessing pipeline steps
    std::vector<Detection> parseYoloOutput(const std::vector<float> output);
    std::vector<Detection> applyNMS(const std::vector<Detection> detections);
    void scaleDetections(const std::vector<Detection>detections, 
    const cv::Size& original_size, const cv::Size& input_size);

    // getters and setters
    void setConfidenceThreshold(float threshold);
    void setNMSThreshold(float threshold);
    float getConfidenceThreshold() const;
    float getNMSThreshold() const;


private:
    // Threshold variables
    float confidence_threshold_;
    float nms_threshold_;

    // Yolov8 constants
    // doible check if i am using coco here
    static const int NUM_CLASSES = 80; // coco dataset classes
    static const int NUM_BOXES = 8400; // default number of yolov8 output boxes
    static const int BOX_ELEMENTS = 84; // 4 coords + 80 classes

    // helper methods
    // find out what IoU is
    float calculateIoU(Const cv::Rect& box1, const cv::Rect& box2);
    cv::Rect parseBox(const float* data, int index);
    float getMaxConfidence(const float* data, int index, int& class_id);
};

#endif