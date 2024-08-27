#!/bin/bash

g++ -o main back_camera_assist/main.cpp back_camera_assist/dynamics.cpp back_camera_assist/video_viz.cpp -I /usr/include/opencv2 -L /usr/lib -lopencv_core -lopencv_imgproc -lopencv_videoio $(pkg-config --cflags --libs opencv) -I/home/toukheer/Python-3.11.0/Include -I/home/toukheer/Python-3.11.0 -L/home/toukheer/Python-3.11.0/Lib -lpython3.11 -lncurses -pthread -I$TORCH_INCLUDE -L$TORCH_LIB -ldl -lutil -std=c++11

if [ $? -eq 0 ]; then
    ./main
else
    echo "Compilation failed."
fi
