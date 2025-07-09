#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

// System includes
#include <vector>
#include <map>

// Third-party includes
#include <opencv2/opencv.hpp>

// Project includes
#include "postprocessor.hpp"  // For Detection struct

// Color palette structure
struct ColorPalette {
    std::vector<cv::Scalar> colors;
    
    ColorPalette() {
        // Initialize with common colors
        colors = {
            cv::Scalar(255, 0, 0),     // Red
            cv::Scalar(0, 255, 0),     // Green
            cv::Scalar(0, 0, 255),     // Blue
            cv::Scalar(255, 255, 0),   // Yellow
            cv::Scalar(255, 0, 255),   // Magenta
            cv::Scalar(0, 255, 255),   // Cyan
            cv::Scalar(128, 0, 128),   // Purple
            cv::Scalar(255, 165, 0),   // Orange
        };
    }
};

class Visualizer {
private:
    // Drawing parameters
    int line_thickness_;
    int font_face_;
    double font_scale_;
    cv::Scalar font_color_;
    
    // Color management
    ColorPalette color_palette_;
    std::map<int, cv::Scalar> class_colors_;
    
    // Display options
    bool show_confidence_;
    bool show_class_names_;
    bool show_fps_;
    bool show_detection_count_;

public:
    // Constructor
    Visualizer();
    
    // Main visualization method
    void visualize(cv::Mat& image, const std::vector<Detection>& detections);
    
    // Individual drawing methods
    void drawBoundingBoxes(cv::Mat& image, const std::vector<Detection>& detections);
    void drawLabels(cv::Mat& image, const std::vector<Detection>& detections);
    void drawFPS(cv::Mat& image, double fps);
    void drawDetectionCount(cv::Mat& image, int count);
    
    // Utility methods
    cv::Scalar getClassColor(int class_id);
    void generateColorPalette(int num_classes);
    
    // Setters for display options
    void setShowConfidence(bool show);
    void setShowClassNames(bool show);
    void setShowFPS(bool show);
    void setShowDetectionCount(bool show);
    void setLineThickness(int thickness);
    void setFontScale(double scale);
    
    // Getters
    bool getShowConfidence() const;
    bool getShowClassNames() const;
    bool getShowFPS() const;
    bool getShowDetectionCount() const;

private:
    // Private helper methods
    cv::Size getTextSize(const std::string& text);
    void drawTextWithBackground(cv::Mat& image, const std::string& text, 
                               const cv::Point& position, const cv::Scalar& text_color,
                               const cv::Scalar& background_color);
    cv::Scalar generateRandomColor(int seed);
};

#endif // VISUALIZER_HPP