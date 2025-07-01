cmake_minimum_required(VERSION 3.18)
project(yolov8_trt_embodied LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directories
include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
    # Add TensorRT include path manually if needed
    # /path/to/TensorRT/include
)

# Link directories
# link_directories(/path/to/TensorRT/lib)  # Uncomment and edit when you add TensorRT libs

# Source files
add_executable(yolov8_trt_embodied
    src/main.cpp
    src/engine.cpp
    src/preprocessor.cpp
    src/postprocessor.cpp
    src/utils.cpp
    src/visualizer.cpp
)

# Link libraries
target_link_libraries(yolov8_trt_embodied
    ${OpenCV_LIBS}
    # Add TensorRT libs manually when ready:
    # nvinfer nvinfer_plugin nvparsers cudart
)

