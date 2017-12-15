#pragma once

#ifndef INCLUDE_CONTROLTURTLEBOT_HPP_
#define INCLUDE_CONTROLTURTLEBOT_HPP_

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "nav_msgs/Odometry.h"
#include "tf/tf.h"
#include <tf/transform_listener.h>
#include <fstream>
#include <math.h>
#include "toy_robot/input.h"


class ControlTurtlebot {
  

  public:

  #define ANGULAR_VELOCITY_MINIMUM_THRESHOLD 0.4
  #define pi 22/7

//  ControlTurtlebot();



  //declare publishers
  ros::Publisher pub;
  //declare subscribers
  ros::Subscriber pose_subscriber;
  //global variable to update the position of the robot
  nav_msgs::Odometry turtlebot_odom_pose;

  ros::NodeHandle n;

  double circle(double speed);
  
  //callback function for the /odom topic to update the pose
  void poseCallback(const nav_msgs::Odometry::ConstPtr& pose_message);
  
//  bool add(toy_robot::input::Request  &req, toy_robot::input::Response &res);

  //the function that makes the robot moves forward and backward
  void move_linear(double speed, double distance, bool isForward);
  
  //the function that makes the robot rotates left and right
  double rotate(double ang_vel, double angle_radian, bool isClockwise);
  
  double degree2radian(double degreeAngle);
  double radian2degree(double radianAngle);
  
  void moveShape(double sideLength, double totalSides, double angle, double velocity);

};

#endif

