# Real Time Object Detection for Embodied Agents using TensorRT + YOLOv8
A trash inference built off YOLOv8 + TensorRT, will be constructed to fit a future pipeline of vision classification for embodied agents

# Plan
High level phases:

**Understanding the Model**

Set up Inference

**Optimize and Deploy**

Objectives for each phase

**Understanding the model**
- YOLOv8 architecture
- Pre/postprocessing

**Set up Inference**
- Exporting to ONNX
- Convert to TensorRT
- Run inference with TensorRT Python API

**Optimize and Deploy**
- Benchmark with cudaEvent_t, Nsight
- Integrate into a camera stream or robot perception

**Architecture Steps** 
1. Export Model to ONNX
2. Load TensorRT Engine
3. Implement Preprocessing
4. Implement PostProcessing
5. Add OpenCV Visualization
6. Build Main Loop
7. Add timing and benchmarking