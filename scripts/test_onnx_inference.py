# scripts/test_onnx_inference.py
import onnxruntime as ort
import numpy as np
import cv2

# Simulate a real YOLOv8 input: batch size 1, 3 color channels, 640x640
img = np.random.rand(1, 3, 640, 640).astype(np.float32)

# Load the ONNX model
session = ort.InferenceSession("models/yolov8n.onnx")

# Prepare input dict using dynamic input name
input_name = session.get_inputs()[0].name
inputs = {input_name: img}

# Run inference
outputs = session.run(None, inputs)

# Print the shape of the output
print("Output shape:", outputs[0].shape)  # Expected: (1, 84, 8400)

# Works!, outputted (1, 84, 8400)