# Real Time Object Detection for Embodied Agents using TensorRT + YOLOv8
An object estimatation inference for embodied agents built off YOLOv8 + TensorRT

# Plan
High level phases:

**Understanding the model**
- TensorRT architecture and C++ API
- YOLOv8 architecture
- Pre/postprocessing

# Convert from yolov8 pytorch to ONNX (Done)
- Utilized ultralytics to convert yolov8 into ONNX format
- Why: Because ONNX acts a bridge which allows yolov8 models originally
written in pyorch to be optimized and deployed within tensorRT ecosystem for
faster inference speeds and low latency connection

# Load TensorRT engine
- Goals are to load the .engine file, manage GPU 
memory, and run inference
- Will be working on engine.hpp and engine.cpp

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


