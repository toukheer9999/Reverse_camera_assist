#include<iostream>
#include <cmath>
#include "dynamics.hpp"
#include <vector>
#include<opencv2/opencv.hpp>
#include "matplotlibcpp.h"
#include<eigen3/Eigen/Dense>
#include "ncurses.h"
#include <thread>
#include<Python.h>


int main(){
    //Parameters of the car
    double W = 1.8; // track width in meters
    double L = 4.6; // wheelbase in meters
    double delta; // steering angle

    //Video and key threading
    std::string file_name = "/home/toukheer/C++_coding/reverse_assist/back_camera_assist/reversing.mp4";
    std::thread videoThread(video_play,W,L,std::ref(delta),file_name);
    std::thread keythread(key_input,std::ref(delta));
    
    videoThread.join();
    keythread.join();
    return 0;
}