#import os
#import matplotlib as plt 
#from ultralytics import YOLO


def object_detection(frame):
    import torch
    import cv2
    import numpy as np 
    frame = np.asarray(frame)
    frame = frame[:,:,::-1].copy()
    
    model = torch.hub.load('ultralytics/yolov5','custom','/home/toukheer/C++_coding/yolo/runs/detect/train11/weights/best.pt',force_reload=True)
    results = model(frame)
