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

void yolov8_object(cv::Mat frame){
    //Initalize Python Interpreter
    Py_Initialize();

    //Import python script
    PyObject* pModule = PyImport_ImportModule("yolov8");

    //Get Reference to the function in your python script
    PyObject* pFunction = PyObject_GetAttrString(pModule, "object_detection");
    //Check if function exist
    /*if(pFunction && PyCallable_Check(pFunction)){
        //Convert OpenCV Mat to Python NumPy array
        PyObject* pImage = PyCapsule_New((void*)&frame,"cv::Mat", NULL);

        //Call the python function with the frame as argument
        PyObject* pResult = PyObject_CallFunction(pFunction, "0", pImage);

        // Check if the call was successful
        if(pResult != NULL){
            std::cout<<pResult<<std::endl;
        }
        else{
            PyErr_Print();
        }


    }
    //FILE* fp = fopen("/home/toukheer/C++_coding/reverse_assist/back_camera_assist/yolov8.py","r");
    //std::cout<<fp<<std::endl;
    //if(fp){
     //   PyRun_SimpleFile(fp,"/home/toukheer/C++_coding/reverse_assist/back_camera_assist/yolov8.py");
     //   fclose(fp);
    //}  */

    // Decrement reference counts
    Py_XDECREF(pFunction);
    Py_XDECREF(pModule);
    // Finalize Python interpreter
    Py_Finalize();
}


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

            //Initalize Python Interpreter
            Py_Initialize();

            //Import python script
            PyObject* pModule = PyImport_ImportModule("yolov8");

            //Get Reference to the function in your python script
            //PyObject* pFunction = PyObject_GetAttrString(pModule, "object_detection");
            //yolov8_object(frame);
            //std::thread yolov8_thread(yolov8_object,frame);
            //yolov8_thread.join();
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