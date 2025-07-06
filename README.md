# Real Time Object Detection for Embodied Agents using Onnx Runtime + YOLOv8
An object estimatation inference for embodied agents built off YOLOv8 + TensorRT

# Plan
High level phases:

Goals:
- fully finish header
- fully finish cpp files structure
- code up all cpp files

**Understanding the model**
- TensorRT architecture and C++ API
- YOLOv8 architecture
- Pre/postprocessing

# Convert from yolov8 pytorch to ONNX (Done)
- Utilized ultralytics to convert yolov8 into ONNX format
- Why: Because ONNX acts a bridge which allows yolov8 models originally
written in pyorch to be optimized and deployed within tensorRT ecosystem for
faster inference speeds and low latency connection

# Load onnx logic
- Goals are to load the onnx file, complete implementation

# Implement Preprocessing
- Goals are to resize, pad, and normalize image input, and convert to TensorRT input format
- Will be working on preprocessor.hpp and preprocessor.cpp

# Implement Postprocessing
- Goals are to parse TensorRT output and apply NMS
- Will be working on postprocessing.hpp and postprocessing.cpp

# Add OpenCV visualization
- Goals are to draw boxes and labels on the image frames
= Woking on visualizer.hpp and visualizer.cpp

# Build Main Loop
- Goal is to tie all the components together into a real time inference loop
- Working on main.cpp
- Test on both normal images, and mp3/mp4 video. 

# Add timing and benchmarking
- Profile pipeline and log latency
- Only work on once everything above is done
- utils.hpp and utils.cpp

# Implementation Priority Order

**Phase 1: Core Functionality**

RAII - Get resource management right from the start
Smart Pointers - For ONNX session management
Struct Constructors - For data structures
member initializer lists for constructors
Pass by Reference - For performance

**Phase 2: Data Processing**

std::vector - For dynamic arrays
OpenCV Mat Management - For image processing
STL Algorithms - For filtering and sorting
Lambda Functions - For custom predicates

**Phase 3: Advanced Features**

Exception Handling - For robustness
std::chrono - For timing
std::map - For color mapping
Template Basics - For generic utilities

**Phase 4: Optimization**

Move Semantics - For performance
constexpr - For compile-time optimization
Memory Alignment - For ONNX optimization


# Critical Concepts for Each File
**engine.cpp**

RAII, Smart Pointers, Exception Handling, Memory Alignment

**preprocessor.cpp**

OpenCV Mat Management, Method Chaining, Data Type Conversions, Pass by Reference

**postprocessor.cpp**

STL Algorithms, Lambda Functions, Function Objects, Iterator Concepts

**visualizer.cpp**

std::map, Color Conversions, Method Overloading

**utils.cpp**

std::filesystem, Exception Handling, Template Basics, std::chrono