# convert yolov8 into an onnx file

from ultralytics import YOLO

model = YOLO("yolov8n.pt")
model.export(format="onnx")
