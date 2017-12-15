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
 *  @file    input.cpp
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
#include "ros/ros.h"
#include "toy_robot/input.h"
#include <cstdlib>

bool add(toy_robot::input::Request  &req,
         toy_robot::input::Response &res)
{
  // Get the service request & Update the service response
  res.totalSidesOut = req.totalSidesIn;
  //Print request and response
  ROS_INFO("request: x=%ld", (long int)req.totalSidesIn);
  ROS_INFO("sending back response: [%ld]", (long int)res.totalSidesOut);
  return true;
}

int main(int argc, char **argv)
{
  //initialize the ROS node
  ros::init(argc, argv, "input_server");
  // Create a nodehandle
  ros::NodeHandle n;
  // Advertise the service
  ros::ServiceServer service = n.advertiseService("input", add);
  ROS_INFO("User Input Service Started!");
  ros::spin();
  return 0;
}
