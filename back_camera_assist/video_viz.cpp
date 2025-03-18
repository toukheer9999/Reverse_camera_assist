#include<iostream>
#include <cmath>
#include "dynamics.hpp"
#include <vector>
#include<eigen3/Eigen/Dense>
#include<opencv2/opencv.hpp>
#include "matplotlibcpp.h"
#include "ncurses.h"
#include <thread>
#include <Python.h>



void video_play(double W,double L,double& delta,const std::string file_name){
    /*Playing the video using opencv */
    cv::VideoCapture cap(file_name);

    if(!cap.isOpened()){
        std::cerr <<"Error opening the video file" << std::endl;
    }
    
    while(cap.isOpened()){
        cv::Mat frame;
        bool ret = cap.read(frame);

        if(ret){
            Trajectory trajectory(W,L,delta); // constructor
            trajectory.ackermann(frame); //  Ackermann function

            if(cv::waitKey(1)=='q'){
                break;
            }
        }
        else{
            break;
        }
        cv::waitKey(30);
    }


    cap.release();
    cv::destroyAllWindows();
    //std::cout<<delta;
}

void key_input(double& delta){
    /* Initialize the Keyboard Input
        -> turns the steering angle to right(consider you are facing front of the car)
        <- turns the steering angle to left
        ESC closes your Keyboard menu*/
        
    initscr(); //initialize ncurses
    cbreak(); //Disable line buffering
    noecho(); // Don't echo characters to the screen
    keypad(stdscr, TRUE); //Enable keyboard input
    
    while(true){
    int ch = getch(); //get the pressed key
    if(ch == KEY_RIGHT){
        delta = delta + 1;
    }
    else if(ch == KEY_LEFT){
        delta = delta - 1;
    }
    else if(ch == 27){
        break;
    }
    clear();
    printw("Value: %lf\n", delta);
    refresh();
    if(delta >= 20){
        delta = 20;
    }
    if(delta <= -20){
        delta = -20;
    }
    }
    endwin(); //End ncurses
}
