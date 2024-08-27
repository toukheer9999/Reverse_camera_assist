#ifndef  DYNAMICS_H_
#define  DYNAMICS_H_

#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<eigen3/Eigen/Dense>
#include<opencv2/opencv.hpp>
#include<thread>


void video_play(double W,double L,double& delta,const std::string file_name);
void key_input(double& delta);

class Trajectory{
    public:
    Trajectory(double const& W, double const& L, double const& delta);
    void ackermann(cv::Mat frame);
    void cartesian(double rl, double rr,cv::Mat frame);

    double W_;
    double L_;
    double delta_;
    double traj_length = 6 ; // the length you want to project your trajectory
    Eigen::VectorXd traj_width; // linear space length from left tire to right tire
    
    Eigen::Matrix<double, 100,2> left_traj;
    Eigen::Matrix<double, 100,2> right_traj;
};

#endif /*DYNAMICS_H*/