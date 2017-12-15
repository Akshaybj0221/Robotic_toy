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
 *  @file    main.cpp
 *  @author  Akshay Bajaj
 *  @copyright MIT License (c) 2017 Akshay Bajaj
 *
 *  @brief Final Project - Robotic Toy - Moving in a polygonal trajectory inspired by users input
 *
 *  @section DESCRIPTION
 *
 *  This program will instantiate a free space navigation node, and  service client "input"
 *
 */



#include "ControlTurtlebot.hpp"

int main(int argc, char **argv){
  // initialse variables needed for making the robot move in a particular polygonal trajectory
  // velocity by which robot will move
  double velocity = 0.3;
  // angle variable
  double angle;
  // length of side of the shape that the robot will move
  double sideLength = 1.0;
  //initialize the ROS node
  ros::init(argc, argv, "free_space_navigation_node");
  // Create a nodehandle
  ros::NodeHandle n;
  // Create a class object
  ControlTurtlebot obj;
  // Create a client for service /input
  ros::ServiceClient client = n.serviceClient<toy_robot::input>("input");
  // Create a service instance
  toy_robot::input srv;
  // Set the request
  srv.request.totalSidesIn = atoll(argv[1]);
  // Call the service
	if (client.call(srv))
	{
		ros::init(argc, argv, "free_space_navigation_node");		
		ROS_INFO("Request of input service is: ", (long int)srv.response.totalSidesOut);
	}		
	else
 	{
    		ROS_ERROR("Failed to call service input");
    		return 1;
  	}
  // Wait for service to advertise
  if (ros::service::waitForService("input", 1000)) {
    ROS_INFO("The service is available!");
  }
  // Initialize response part of service message in a variable
  double totalSides = abs(srv.response.totalSidesOut);	
  //subscribe to the odometry topic to get the position of the robot
  obj.pose_subscriber = n.subscribe("/odom", 10, &ControlTurtlebot::poseCallback, &obj);
  //register the velocity publisher 
  obj.pub =n.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity", 1000);
  ros::spinOnce();
  ros::Rate loop(1);
  loop.sleep();loop.sleep();loop.sleep();
  ros::spinOnce();
  while (ros::ok()){
    ros::spinOnce();loop.sleep();
    // Print Initial pose of the turtlebot before moving
    printf("robot initial pose: (%.2f, %.2f, %.2f)\n", obj.turtlebot_odom_pose.pose.pose.position.x,
    obj.turtlebot_odom_pose.pose.pose.position.y, 
    obj.radian2degree(tf::getYaw(obj.turtlebot_odom_pose.pose.pose.orientation)));
    // Calculate angle of turtlebot rotation depending on the number of sides given by user
    if(totalSides > 1){
      angle = 360/totalSides;
      }
    // If totalSides less than 3, then it will not form a polygon, hence commanded to form a line
    if(totalSides <= 1){
      angle = 360;
      totalSides = 1;
    }	
    // Called a function which makes the robot move in the desired shape corresponding to users input of number of sides
    obj.moveShape(sideLength, totalSides, angle, velocity);
    ros::spinOnce();loop.sleep();ros::spinOnce();
    // Print Final pose of the turtlebot after moving (it will be near about initial pose, but not exact as it is just a toy so need for such accuracy
    printf("robot final pose: (%.2f, %.2f, %.2f)\n", obj.turtlebot_odom_pose.pose.pose.position.x, 
    obj.turtlebot_odom_pose.pose.pose.position.y, 
    obj.radian2degree(tf::getYaw(obj.turtlebot_odom_pose.pose.pose.orientation)));
    return 0;
  }
  return 0;
}



