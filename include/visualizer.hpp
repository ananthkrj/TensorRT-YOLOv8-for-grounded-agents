#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
// for the detection struct include postprocessor.hpp struct
#include "postprocessor.hpp"

class Visualizer {
public:
    // need a constructor and destructor
    Visualizer();
    ~Visualizer();

    // find out difference between detections and detection
    // draw bounding boxes on image
    // pass image, and struct variables
    // find out if passing the image as a const changes anything
    void drawDetections(cv::Mat& image, const std::vector<Detection>& detections);
    
    // draw a single bounding box, boxes is built off this
    void drawDetection(cv::Mat &image, const std::vector<Detection>& detections);

    // add a class label text
    // pass image by reference
    void drawLabel(cv::Mat &image, const std::vector<Detection>& detection, const std::string& label);

private:
    // colors for different classes
    // find out what scalar does in opencv
    std::vector<cv::Scalar> m_color;

    // generate random colors
    void generateColor(int numClasses);
};