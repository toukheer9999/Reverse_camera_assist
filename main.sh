#!/bin/bash

g++ -o main back_camera_assist/main.cpp back_camera_assist/dynamics.cpp back_camera_assist/video_viz.cpp -I /usr/include/opencv4 -L /usr/lib -lopencv_core -lopencv_imgproc -lopencv_videoio $(pkg-config --cflags --libs opencv4) -I /usr/include/python3.10/Include -I /usr/include/python3.10 -L /usr/include/python3.10/Lib -lpython3.10 -lncurses -pthread -ldl -lutil -std=c++11

if [ $? -eq 0 ]; then
    # Run the program with the video file path as an argument
    if [ $# -eq 1 ]; then
        ./main "$1"
    else
        echo "Usage: $0 <video_file_path>"
    fi
else
    echo "Compilation failed."
fi
