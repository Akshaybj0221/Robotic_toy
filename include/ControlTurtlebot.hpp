/**
 *  MIT License
 *
 *  Copyright (c) 2017 Karan Vivek Bhargava
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without
 *  limitation the rights to use, copy, modify, merge, publish, distribute,
 *  sublicense, and/or sell copies of the Software, and to permit persons to
 *  whom the Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall be included
 *  in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *
 *  @file    ControlTurtlebot.cpp
 *  @author  Akshay Bajaj
 *  @copyright MIT License (c) 2017 Akshay Bajaj
 *
 *  @brief Final Project - Robotic Toy - Moving in a polygonal trajectory inspired by users input
 *
 *  @section DESCRIPTION
 *
 *  This program will instantiate a input server node, and  service server "input"
 *
 */
#pragma once

#ifndef INCLUDE_CONTROLTURTLEBOT_HPP_
#define INCLUDE_CONTROLTURTLEBOT_HPP_

#include <math.h>
#include <tf/transform_listener.h>
#include <fstream>
#include "ros/ros.h"
#include "tf/tf.h"
#include "toy_robot/input.h"
#include "geometry_msgs/Twist.h"
#include "sensor_msgs/LaserScan.h"
#include "nav_msgs/Odometry.h"


class ControlTurtlebot {
 public:
  // Declare constant variables
#define ANGULAR_VELOCITY_MINIMUM_THRESHOLD 0.4
#define pi 22/7
  // declare publishers
  ros::Publisher pub;
  // declare subscribers
  ros::Subscriber pose_subscriber;
  // global variable to update the position of the robot
  nav_msgs::Odometry turtlebot_odom_pose;
  // declare an object to ros node, i.e., a Nodehandle
  ros::NodeHandle n;
  /**
   * @brief Take the action
   * @details Move robot in a random dummy trajectory
   * @return double: Return true
   */
  double circle(double speed);
  /**
   * @brief Callback function for service
   * @details Function callback for the service input
   *
   * @param pose_message Service message
   
   * @return void: Return nothing
   */
  // callback function for the /odom topic to update the pose
  void poseCallback(const nav_msgs::Odometry::ConstPtr& pose_message);
  /**
   * @brief     linearly moving funtion/method
   * @details   the function that makes the robot moves forward and backward
   *
   *
   * @param  distance     Length of one side of the polygonal trajectory
   * @param  totalSides   Total number of sides inserted by the user
   * @param  isForward    To check if forward moving value or backward
   * @param  speed        Velocity of robot
   * 
   *
   * @return bool: Return true if succeeded
   */
  void move_linear(double speed, double distance, bool isForward,
                   double totalSides);
  /**
   * @brief      Executes the rotation for turtlebot
   * @details   the function that makes the robot rotate
   *
   * @param[in]  isClockwise     To make sure robot always rotates in a clockwise direction
   * @param[in]  angle_radian    Angle by which the robot needs to turn
   * @param[in]  angular_vel     Velocity of robot rotation
   *
   * @return bool: Return true if succeeded
   * 
   */
  // the function that makes the robot rotates left and right
  double rotate(double ang_vel, double angle_radian, bool isClockwise);
  /**
   * @brief      makes conversion from degree to degree
   *
   * @param[in]  radianAngle              Angle by which the robot needs to turn
   * 
   * @return bool: Return true if succeeded
   */
  double degree2radian(double degreeAngle);
  /**
   * @brief      makes conversion from radian to degree
   *
   * @param[in]  radianAngle              Angle by which the robot needs to turn
   * 
   * @return bool: Return true if succeeded
   */
  double radian2degree(double radianAngle);
  /**
   * @brief      Executes the planned trajectory for turtlebot
   *
   * @param[in]  sideLength   Length of one side of the polygonal trajectory
   * @param[in]  totalSides   Total number of sides inserted by the user
   * @param[in]  angle        Angle by which the robot needs to turn
   * @param[in]  velocity     Velocity of robot
   *
   * @return void: Return nothing
   * 
   */
  void moveShape(double sideLength, double totalSides, double angle,
                 double velocity);
};
#endif

