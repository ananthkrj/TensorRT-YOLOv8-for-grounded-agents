#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

// forward struct declaration
// figure out if need a struct here or not
struct Detection;

class Visualizer {

public:
    // constructor with sensible defaults
    Visualizer();

    // main visualization methods
    void drawDetections(image, detections);
    void drawEnvironmentInfo(image, environment_type);

    // individual drawing components
    void drawBoundingBox(image, detection, color);
    void drawLabel(image, detection, color);

    // utility methods
    cv::Scalar getColorForClass(int class_id);
    void displayResults(image, const std::string& window_name = "Detection Results");


private:
    // Drawing parameters
    int line_thickness_;
    double font_scale_;
    cv::Scalar default_colors_;
    
    // Predefined colors for different colors (cycle through them)
    std::vector<cv::Scalar> class_colors_;

    // helper methods
    void initializeColors();
    std::string getClassName(int class_id);
};


#endif