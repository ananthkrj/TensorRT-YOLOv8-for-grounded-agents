// postprocessor.cpp implementation logic:
// - Constructor: store thresholds
// - postprocess(): parse raw output, filter by confidence, apply NMS
// - parseYOLOOutput(): interpret YOLO output format (boxes, scores, classes)
// - applyNMS(): remove overlapping detections using IoU calculation
#include "postprocessor.hpp"

// constructor
Postprocessor::Postprocessor(float confidenceThreshold, float nmsThreshold) {

}

// destructor
Postprocessor::~Postprocessor() {

}

// public member functions for post processing and applying nms
// always place return type of function before the scope resolition. and the scope
// reolution should be in front of function name
std::vector<Detection> Postprocessor::postprocess(float* output, int outputsize) {

}

std::vector<Detection> Postprocessor::applyNMS(const std::vector<Detection>& detections) {
    
}