#include <iostream>
#include <cmath>
#include "dynamics.hpp"
#include <vector>
#include<eigen3/Eigen/Dense>
#include<opencv2/opencv.hpp>
#include "matplotlibcpp.h"
#include "ncurses.h"

std::vector<cv::Point> vectopt(std::vector<double> u,std::vector<double> v){
    /* Converting vector double type to cv::point format*/
    std::vector<cv::Point> points;
    for(int i = 0; i<u.size();i++){
        cv::Point point(u[i],v[i]);
        points.push_back(point);
    }
    return points;    
}

std::vector<double> Vectorize(Eigen::VectorXd v){
    /*Vectorizing the matrix*/
    std::vector<double> v1;
    v1.resize(v.size());
    Eigen::VectorXd::Map(&v1[0], v.size()) = v;
    return v1;
};

void world_to_pix(double theta,double h,double Wx,double Wy,double& u, double& v){
    
    /*Camera Intrinsic parameters*/
    double fx = 720; //1907.78;
    double fy = 720;//1908.92;
    double cx = 420; //982.75;
    double cy = 240; //547.373;

    double thetax = theta;
    double thetay = 0;
    double thetaz = 0;

    Eigen::Matrix<double,3,3> Ic;
    Ic << fx,0,cx,
         0,fy,cy,
         0,0,1;

    /*rotation matrix*/
    Eigen::Matrix<double,3,3> R1,R2,R3;
    R1 << 1,0,0,
          0,cos(thetax),-sin(thetax),
          0,sin(thetax),cos(thetax);


    R2 << cos(thetay),0,-sin(thetay),
          0,1,0,
          sin(thetay),0,cos(thetay);

    R3 << cos(thetaz),-sin(thetaz),0,
          sin(thetaz),cos(thetaz),0,
          0,0,1;

    /*World Frame matrix*/
    Eigen::Matrix<double,3,1> W;
    W << Wx,
         h,
         Wy;
    
    Eigen::Matrix<double,3,1> w2c = R1 * W; // World frame to camera frame
    Eigen::Matrix<double,3,1> c2p = Ic * w2c; // Camera frame to pixel frame

    u = c2p(0)/c2p(2);
    v = c2p(1)/c2p(2);
};

void out_of_screen(double& u, double& v){
    if(0 <= u <= 1920 and 0 <= v <= 1080){
        u = int(u);
        v = int(v);
    }
    else{
        u = -1;
        v = -1;
    }
};

void visualization(Eigen::MatrixXd left_traj,Eigen::MatrixXd right_traj,
Eigen::MatrixXd traj_bl,Eigen::MatrixXd traj_ml,
Eigen::MatrixXd traj_tl, Eigen::MatrixXd traj_lr){
    /* Visualizing the trajectory in 2D plot
    Requires matplolibcpp library*/
    namespace plt = matplotlibcpp;
    std::vector<double> left_traj_x = Vectorize(left_traj.col(0));
    std::vector<double> left_traj_y = Vectorize(left_traj.col(1));
    std::vector<double> right_traj_x = Vectorize(right_traj.col(0));
    std::vector<double> right_traj_y = Vectorize(right_traj.col(1));
    std::vector<double> traj_bl_x = Vectorize(traj_bl.col(0));
    std::vector<double> traj_bl_y = Vectorize(traj_bl.col(1));
    std::vector<double> traj_ml_x = Vectorize(traj_ml.col(0));
    std::vector<double> traj_ml_y = Vectorize(traj_ml.col(1));
    std::vector<double> traj_tl_x = Vectorize(traj_tl.col(0));
    std::vector<double> traj_tl_y = Vectorize(traj_tl.col(1));
    std::vector<double> traj_l_x = Vectorize(traj_lr.col(0));
    std::vector<double> traj_l_y = Vectorize(traj_lr.col(1));
    std::vector<double> traj_r_x = Vectorize(traj_lr.col(2));
    std::vector<double> traj_r_y = Vectorize(traj_lr.col(3));


    plt::plot(left_traj_x,left_traj_y,"g");
    plt::plot(right_traj_x,right_traj_y,"g");
    plt::plot(traj_bl_x,traj_bl_y,"y");
    plt::plot(traj_ml_x,traj_ml_y,"orange");
    plt::plot(traj_tl_x,traj_tl_y,"r");
    plt::plot(traj_l_x,traj_l_y,"y");
    plt::plot(traj_r_x,traj_r_y,"y");
    plt::show();
};

void video_viz(std::vector<double> pix_left_u,std::vector<double> pix_left_v,
std::vector<double> pix_right_u,std::vector<double> pix_right_v,
std::vector<double> pix_tl_u,std::vector<double> pix_tl_v,
std::vector<double> pix_tr_u,std::vector<double> pix_tr_v,
std::vector<double> pix_bl_u,std::vector<double> pix_bl_v,
std::vector<double> pix_ml_u,std::vector<double> pix_ml_v,
std::vector<double> pix_tpl_u,std::vector<double> pix_tpl_v,double& delta_,
cv::Mat frame){
            //cv::Mat frame;
            cv::polylines(frame,vectopt(pix_left_u,pix_left_v),false,cv::Scalar(0,255,100),3);
            cv::polylines(frame,vectopt(pix_right_u,pix_right_v),false,cv::Scalar(0,255,100),3);
            cv::polylines(frame,vectopt(pix_tl_u,pix_tl_v),false,cv::Scalar(0,255,100),3);
            cv::polylines(frame,vectopt(pix_tr_u,pix_tr_v),false,cv::Scalar(0,255,100),3);
            cv::polylines(frame,vectopt(pix_bl_u,pix_bl_v),false,cv::Scalar(0,0,255),3);
            cv::polylines(frame,vectopt(pix_ml_u,pix_ml_v),false,cv::Scalar(0,255,255),3);
            cv::polylines(frame,vectopt(pix_tpl_u,pix_tpl_v),false,cv::Scalar(0,255,100),3); 
            cv::imshow("Dynamic Backup Line", frame);
}

void coordinate_transform(Eigen::MatrixXd left_traj,Eigen::MatrixXd right_traj,
Eigen::MatrixXd traj_bl,Eigen::MatrixXd traj_ml,
Eigen::MatrixXd traj_tl, Eigen::MatrixXd traj_lr,double& delta_,
cv::Mat frame){
    /*Transforming from world frame to pixel frame*/
    double h = 0.65; 
    double theta =3*3.14159/180; 

    //load trajectories
    std::vector<double> left_traj_x = Vectorize(left_traj.col(0));
    std::vector<double> left_traj_y = Vectorize(left_traj.col(1));
    std::vector<double> right_traj_x = Vectorize(right_traj.col(0));
    std::vector<double> right_traj_y = Vectorize(right_traj.col(1));
    std::vector<double> traj_bl_x = Vectorize(traj_bl.col(0));
    std::vector<double> traj_bl_y = Vectorize(traj_bl.col(1));
    std::vector<double> traj_ml_x = Vectorize(traj_ml.col(0));
    std::vector<double> traj_ml_y = Vectorize(traj_ml.col(1));
    std::vector<double> traj_tl_x = Vectorize(traj_tl.col(0));
    std::vector<double> traj_tl_y = Vectorize(traj_tl.col(1));
    std::vector<double> traj_l_x = Vectorize(traj_lr.col(0));
    std::vector<double> traj_l_y = Vectorize(traj_lr.col(1));
    std::vector<double> traj_r_x = Vectorize(traj_lr.col(2));
    std::vector<double> traj_r_y = Vectorize(traj_lr.col(3));
    double u,v;

    //world to pixel frame
    //left wheel trajectory
    std::vector<double> pix_left_u;
    std::vector<double> pix_left_v;
    for(int i=0;i<left_traj_x.size();i++){
        world_to_pix(theta,h,left_traj_x[i],left_traj_y[i],u,v);
        out_of_screen(u,v);
        if(u == -1){
            continue;
        }
        else{
            pix_left_u.push_back(u);
            pix_left_v.push_back(v);
        }
    }
    
    //right wheel trajectory
    std::vector<double> pix_right_u;
    std::vector<double> pix_right_v;
    for(int i=0;i<left_traj_x.size();i++){
        world_to_pix(theta,h,right_traj_x[i],right_traj_y[i],u,v);
        out_of_screen(u,v);
        if(u == -1){
            continue;
        }
        else{
            pix_right_u.push_back(u);
            pix_right_v.push_back(v);
        }
    }

    //left wheel straight trajectory
    std::vector<double> pix_tl_u;
    std::vector<double> pix_tl_v;
    for(int i=0;i<left_traj_x.size();i++){
        world_to_pix(theta,h,traj_l_x[i],traj_l_y[i],u,v);
        out_of_screen(u,v);
        if(u == -1){
            continue;
        }
        else{
            pix_tl_u.push_back(u);
            pix_tl_v.push_back(v);
        }
    }
    
    //right wheel straight trajectory
    std::vector<double> pix_tr_u;
    std::vector<double> pix_tr_v;
    for(int i=0;i<left_traj_x.size();i++){
        world_to_pix(theta,h,traj_r_x[i],traj_r_y[i],u,v);
        out_of_screen(u,v);
        if(u == -1){
            continue;
        }
        else{
            pix_tr_u.push_back(u);
            pix_tr_v.push_back(v);
        }
    }
    
    //car width at length of the given trajectory end point
    std::vector<double> pix_bl_u;
    std::vector<double> pix_bl_v;
    for(int i=0;i<left_traj_x.size();i++){
        world_to_pix(theta,h,traj_bl_x[i],traj_bl_y[i],u,v);
        out_of_screen(u,v);
        if(u == -1){
            continue;
        }
        else{
            pix_bl_u.push_back(u);
            pix_bl_v.push_back(v);
        }
    }
    
    //car width at half of the length of the given trajectory end point
    std::vector<double> pix_ml_u;
    std::vector<double> pix_ml_v;
    for(int i=0;i<left_traj_x.size();i++){
        world_to_pix(theta,h,traj_ml_x[i],traj_ml_y[i],u,v);
        out_of_screen(u,v);
        if(u == -1){
            continue;
        }
        else{
            pix_ml_u.push_back(u);
            pix_ml_v.push_back(v);
        }
    }

    //car width at 1/4th of the length of the given trajectory end point
    std::vector<double> pix_tpl_u;
    std::vector<double> pix_tpl_v;
    for(int i=0;i<left_traj_x.size();i++){
        world_to_pix(theta,h,traj_tl_x[i],traj_tl_y[i],u,v);
        out_of_screen(u,v);
        if(u == -1){
            continue;
        }
        else{
            pix_tpl_u.push_back(u);
            pix_tpl_v.push_back(v);
        }
    }

    video_viz(pix_left_u,pix_left_v,pix_right_u,pix_right_v,
    pix_tl_u,pix_tl_v,pix_tr_u,pix_tr_v,
    pix_bl_u,pix_bl_v,pix_ml_u,pix_ml_v,
    pix_tpl_u,pix_tpl_v,delta_,frame);
};

//Constructor
Trajectory::Trajectory(double const& W, double const& L, double const& delta): W_(W),L_(L), delta_(delta){
    traj_width = Eigen::VectorXd::LinSpaced(100,-W/2, W/2);
};


void Trajectory::ackermann(cv::Mat frame){
    /*  Ackermann calculations
     r1 = length from instantenous center to front right tire
     r4 = length from instantenous center to rear right tire
     r3 = length from instantenous center to rear left tire  */
    double r1 = L_/tan(delta_*3.14159/180);
    double r4 = sqrt(pow(r1,2) - pow(L_,2));
    double r3 = r4 + W_;
    if(delta_ > 0){
        cartesian(r3,r4,frame);
    }
    else{
        cartesian(r4,r3,frame);
    }
};

void Trajectory::cartesian(double left_tire, double right_tire,cv::Mat frame){
    /* Creating vehicle trajectory lines when turning overlapped with straight lines*/
    Eigen::VectorXd length_= Eigen::VectorXd::LinSpaced(100,0,traj_length); 
    
    for(int i=0; i< 100; i++){
        left_traj(i,0) = -W_/2;
        left_traj(i,1) = length_[i];
        right_traj(i,0) = W_/2;
        right_traj(i,1) = length_[i];
    }

    Eigen::VectorXd traj_width_top = Eigen::VectorXd::Constant(traj_width.size(),
                                                        left_traj(left_traj.rows()-1,1));
    Eigen::VectorXd traj_width_middle = Eigen::VectorXd::Constant(traj_width.size(),
                                                        left_traj(left_traj.rows()-1,1)/2);
    Eigen::VectorXd traj_width_bottom = Eigen::VectorXd::Constant(traj_width.size(),
                                                        left_traj(left_traj.rows()-1,1)/3); 

    Eigen::Matrix<double,100,2> traj_bottom_line;
    Eigen::Matrix<double,100,2> traj_middle_line;
    Eigen::Matrix<double,100,2> traj_top_line;
    Eigen::Matrix<double,100,4> traj_left_right;

    traj_bottom_line << traj_width,traj_width_bottom;
    traj_middle_line << traj_width,traj_width_middle;
    traj_top_line << traj_width,traj_width_top;
    traj_left_right << left_traj,right_traj;

    if(delta_<0){
        double theta = traj_length / (left_tire+ W_/2);
        Eigen::VectorXd theta_ = Eigen::VectorXd::LinSpaced(100,0, theta);

        for(int i=0; i< theta_.size(); i++){
            left_traj(i,0) = -W_/2 + left_tire*(cos(theta_[i])-1);
            left_traj(i,1) = left_tire*sin(theta_[i]);
            right_traj(i,0) = -W_/2 - left_tire + right_tire*(cos(theta_[i]));
            right_traj(i,1) = right_tire*sin(theta_[i]);   
        }
    }

    if(delta_ >0){
        double theta = traj_length / (right_tire+ W_/2);
        Eigen::VectorXd theta_ = Eigen::VectorXd::LinSpaced(100,0, theta);

        for(int i=0; i< theta_.size(); i++){
            left_traj(i,0) = -W_/2 + left_tire*(1 - cos(theta_[i]));
            left_traj(i,1) = left_tire*sin(theta_[i]);
            right_traj(i,0) = W_/2 + right_tire*(1 - cos(theta_[i]));
            right_traj(i,1) = right_tire*sin(theta_[i]);   
        }
    }

    coordinate_transform(left_traj,right_traj,traj_bottom_line,traj_middle_line,
    traj_top_line,traj_left_right,delta_,frame);
    
    /*if you want to visualize the trajectory in 2d
     plot the uncomment the below function 
     and comment out the coordinate transform*/

    //visualization(left_traj,right_traj,traj_width_w4,traj_width_w2,traj_width_w,traj_width_baseline);
};
