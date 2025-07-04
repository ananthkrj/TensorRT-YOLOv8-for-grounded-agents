// postprocessor.cpp implementation logic:
// - Constructor: store thresholds
// - postprocess(): parse raw output, filter by confidence, apply NMS
// - parseYOLOOutput(): interpret YOLO output format (boxes, scores, classes)
// - applyNMS(): remove overlapping detections using IoU calculation