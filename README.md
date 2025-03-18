# Reverse Camera Assist

## Overview
This project implements a **Reverse Camera Assist** system using C++. The system helps enhance rear-view assistance by processing camera data and providing relevant feedback. The project consists of multiple components, including a shell script for setup and C++ source files for core functionality.

## Features
- Real-time processing of camera input
- Dynamic calculations to assist with reversing
- Efficient and modular C++ implementation
- Easy-to-run shell script for execution

## Installation
### Prerequisites
Ensure you have the following installed on your system:
- **g++** (C++ Compiler)
- **OpenCV** (`opencv_core`, `opencv_imgproc`, `opencv_videoio`)
- **Python 3.10 Development Libraries** (`python3.10`)
- **Ncurses** (`lncurses`)
- **Pthread** (`-pthread`)
- **Torch (PyTorch)** (Ensure `$TORCH_INCLUDE` and `$TORCH_LIB` are set correctly)
- **Dynamic Linking Libraries** (`-ldl`, `-lutil`)
- **Bash** (for script execution)

### Compilation & Execution
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/reverse-camera-assist.git
   cd reverse-camera-assist
   ```
2. Compile the C++ files:
   ```sh
   g++ -o reverse_assist main.cpp dynamics.cpp -std=c++11
   ```
3. Run the program using the shell script:
   ```sh
   ./main.sh
   ```

## File Structure
- **`main.sh`** - Shell script for executing the program
- **`dynamics.cpp`** - Implements core dynamic calculations for reverse assistance
- **`main.cpp`** - Main program that integrates all components

## Usage
Once executed, the system will process input from the reverse camera and provide assistance accordingly. Modify the source code as needed to adapt it for specific hardware integrations.

## Contributing
Feel free to contribute by submitting issues or pull requests. Ensure code is well-documented and tested before making a submission.

## License
This project is licensed under the MIT License.

---
Author: **Toukheer Shaik**


