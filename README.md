# Reverse Camera Assist Project

## Introduction
This project is a reverse camera assist system where dynamic guide lines are projected onto a video feed. The lines adjust according to the steering wheel movement, simulating how the vehicle's trajectory would change based on the steering angle. The project is implemented using C++ with OpenCV for video processing and visualization, and it includes keyboard input for controlling the steering angle.

## Features

    Dynamic Guide Lines: The system projects guide lines onto the video feed that change dynamically based on the steering angle.

    Keyboard Control: The steering angle can be controlled using the keyboard arrow keys:

        Right Arrow: Increases the steering angle (turns right).

        Left Arrow: Decreases the steering angle (turns left).

        ESC Key: Exits the keyboard input mode.

    Real-Time Visualization: The video feed is displayed in real-time with the projected guide lines overlayed.

    Ackermann Steering Geometry: The guide lines are calculated using Ackermann steering geometry, which ensures realistic turning behavior.

## System Requirements

To run this project, you need the following software and libraries installed on your system:

- C++ Compiler: A C++ compiler that supports C++11 (e.g., g++).

- OpenCV: OpenCV library for video processing and visualization (version 4.x recommended).

- Eigen: Eigen library for linear algebra operations.

- Python: Python 3.x for plotting (optional, if you want to visualize trajectories using matplotlibcpp).

- ncurses: ncurses library for keyboard input handling.

## Installation Instructions

    Install OpenCV:
    ```bash	
    sudo apt-get install libopencv-dev
    ```

    Install Eigen:
    ```bash
    sudo apt-get install libeigen3-dev
    ```

    Install ncurses:
    ```bash
    sudo apt-get install libncurses5-dev
    ```
    
    Install Python and matplotlib (optional):
    ```bash
    sudo apt-get install python3 python3-matplotlib
    ```
    
## Building the Project

    Clone the repository:
    ```bash
    https://github.com/toukheer9999/Reverse_camera_assist.git
    cd reverse-camera-assist
    ```
    
    Build the project:
    ```bash
    mkdir build
    cd build
    cmake ..
    cd ..
    ```
    
    Compile the project using the provided main.sh script:
    ```bash
    chmod +x main.sh
    ```
   
    Run the compiled program:
    ```bash
    ./main <video_file_path>
    ```
    
    Replace <video_file_path> with the path to your video file.


## Usage

    Use the Left Arrow and Right Arrow keys to adjust the steering angle.

    Press the ESC key to exit the program.

    The guide lines will update in real-time based on the steering angle, showing the projected trajectory of the vehicle.
    
## Result
 
[Watch the Demo Video](./videos/result.mp4)


