#pragma once
#include <vector>

// need a struct for bounding box values
// detection variables
// width and height of a bounding box
// confidence of box, (if it contains an oject)
// classid: label of object in box
struct Detection {
    float x, y, width, height;
    float confidence;
    int classId;
};

class Postprocessor {
public:
    // constructor
    // parameters will be confidence threshold and nms threshold
    // nms is non maximal suppression, find out what this is
    Postprocessor(float confidenceThreshold, float nmsThreshold);
    // destructor
    ~Postprocessor();

    // member function for converting raw model
    // output to detections
    
    // pass struct variables into resziable array
    // find out why using std::vector is important for all
    // of these member functions
    std::vector<Detection> postprocess(float* output, int outputsize);

    // applying no maximum suppression (NMS)
    std::vector<Detection> applyNMS(const std::vector<Detection>& detections);

private:
    // find out why use this m underscoe
    float m_confidenceThreshold;
    float m_nmsThreshold;

    // parse the yolo output format
    std::vector<Detection> parseYOLO(float* output, int outputsize);

};