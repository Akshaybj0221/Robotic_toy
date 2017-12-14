#pragma once

#ifndef INCLUDE_CONTROLTURTLEBOT_HPP_
#define INCLUDE_CONTROLTURTLEBOT_HPP_

#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

#include "std_msgs/Float64.h"

class ControlTurtlebot {
  private:
    ros::NodeHandle nh;
    ros::Subscriber sub;

  public:
    ControlTurtlebot();
    ~ControlTurtlebot();
    
    int rate, r, n, i, t, ticks;
    float linear_speed, goal_distance, linear_duration, angular_speed, angle, pi, rad, angular_duration;
    
    geometry_msg::Twist move_cmd;
    ros::Publisher cmd_vel;   
    
    void init(self);
    void shutdown(self);
};

#endif

