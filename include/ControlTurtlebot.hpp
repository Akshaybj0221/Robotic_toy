#pragma once

#ifndef INCLUDE_CONTROLTURTLEBOT_HPP_
#define INCLUDE_CONTROLTURTLEBOT_HPP_

#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

#include "std_msgs/Float64.h"

class ControlTurtlebot {
  private:

    ros::Subscriber sub;

    int i, t, ticks;    
    int rate = 50;
    ros::Rate loop_rate(rate);		
    int r = ros::Rate loop_rate(rate);
    int n = 4;

    float linear_speed = 0.5;
    float goal_distance = 1.0;
    float linear_duration = goal_distance / linear_speed;
    float angular_speed = 1.0;
    float angle = 360/n;	
    float pi = 3.14;
    float rad = angle*(pi/180);
    float angular_duration = (rad / angular_speed);

    geometry_msgs::Twist move_cmd;
    ros::Publisher cmd_vel;

  public:
    ControlTurtlebot(ros::NodeHandle nh);
    ~ControlTurtlebot();
    
    void init();
    void shutdown();
};

#endif

