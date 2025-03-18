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

int main(int argc, char* argv[]){
    if(argc < 2) {
    	std::cerr << "Usage: " << argv[0] << " <video_file_path>" << std::endl;
    	return 1;
    }		

    //Parameters of the car
    double W = 1.8; // track width in meters
    double L = 4.6; // wheelbase in meters
    double delta; // steering angle

    //Video and key threading
    std::string file_name = argv[1];
    std::thread videoThread(video_play,W,L,std::ref(delta),file_name);
    std::thread keythread(key_input,std::ref(delta));
    
    videoThread.join();
    keythread.join();
    return 0;
}
