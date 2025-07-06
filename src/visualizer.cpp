// visualizer.cpp implementation logic:
// - Constructor: initialize color palette
// - drawDetections(): iterate through detections, draw each one
// - drawBoundingBox(): use cv::rectangle() to draw box
// - drawLabel(): use cv::putText() to add class name and confidence

#include "visualizer.hpp"

//constructor
Visualizer::Visualizer() {

}

// destructor 
Visualizer::~Visualizer() {

}

// public member functions

Visualizer::drawDetections(cv::Mat& image, const std::vector<Detection>& detections) {

}


Visualizer::drawDetection(cv::Mat& image, const std::vector<Detection>& detection) {

}

Visualizer::drawLabel(cv::Mat& image, const std::vector<Detection>& detection, const std::string& label) {

}

Visualizer::generateColor(int numClasses) {
    
}
