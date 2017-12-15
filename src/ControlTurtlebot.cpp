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
#include "ControlTurtlebot.hpp"
/**
 * @brief      Callback for the Odometry data
 *
 * @param[in]  pose_message   The message
 */
void ControlTurtlebot::poseCallback(
    const nav_msgs::Odometry::ConstPtr& pose_message) {
  turtlebot_odom_pose.pose.pose.position.x = pose_message->pose.pose.position.x;
  turtlebot_odom_pose.pose.pose.position.y = pose_message->pose.pose.position.y;
  turtlebot_odom_pose.pose.pose.position.z = pose_message->pose.pose.position.z;
  turtlebot_odom_pose.pose.pose.orientation.w = pose_message->pose.pose
      .orientation.w;
  turtlebot_odom_pose.pose.pose.orientation.x = pose_message->pose.pose
      .orientation.x;
  turtlebot_odom_pose.pose.pose.orientation.y = pose_message->pose.pose
      .orientation.y;
  turtlebot_odom_pose.pose.pose.orientation.z = pose_message->pose.pose
      .orientation.z;
}
/**
 * @brief      Executes the planned trajectory for turtlebot
 *
 * @param[in]  sideLength   Length of one side of the polygonal trajectory
 * @param[in]  totalSides   Total number of sides inserted by the user
 * @param[in]  angle        Angle by which the robot needs to turn
 * @param[in]  velocity     Velocity of robot
 * 
 */
void ControlTurtlebot::moveShape(double sideLength, double totalSides,
                                 double angle, double velocity) {
  for (int i = 0; i < totalSides; i++) {
    if (totalSides > 1) {
      // Function that makes the robot move in a forward direction
      move_linear(velocity, sideLength, true, totalSides);
      // Function that makes the robot rotate at a certain angle
      rotate(velocity, degree2radian(angle - 10), true);
    } else {
      // Dummy movement function in case the number of sides are less than 3
      circle(velocity);
    }
  }
}
/**
 * @brief      Makes the turtlebot move in a straight line at a particular distance
 *
 * @param[in]  distance   Length of one side of the polygonal trajectory
 * @param[in]  totalSides   Total number of sides inserted by the user
 * @param[in]  speed        Velocity of robot
 * @param  isForward    To check if forward moving value or backward
 * 
 */
void ControlTurtlebot::move_linear(double speed, double distance,
                                   bool isForward, double totalSides) {
  // delcare a Twist message to send velocity commands
  geometry_msgs::Twist VelocityMessage;
  // initial pose of the turtlebot before start moving
  nav_msgs::Odometry initial_turtlebot_odom_pose;
  // set the linear velocity to a positive value if isFoward is true
  if (isForward)
    VelocityMessage.linear.x = speed;
  // all velocities of other axes must be zero.
  VelocityMessage.linear.y = VelocityMessage.linear.z = VelocityMessage.angular
      .x = VelocityMessage.angular.y = VelocityMessage.angular.z = 0;
  double distance_moved = 0.0;
  // we publish the velocity at 10 Hz (10 times a second)
  ros::Rate loop_rate(10);
  int count = 0;
  // Updated the initial_turtlebot_odom_pose using the turtlebot_odom_pose
  // global variable updated in the callback function poseCallback
  initial_turtlebot_odom_pose = turtlebot_odom_pose;
  do {
    // Publish the velocity messages on the topic
    pub.publish(VelocityMessage);
    ros::spinOnce();
    loop_rate.sleep();
    // Calcute the distance moved by the robot
    distance_moved = sqrt(
        pow((turtlebot_odom_pose.pose.pose.position.x
                - initial_turtlebot_odom_pose.pose.pose.position.x),
            2)
            + pow(
                (turtlebot_odom_pose.pose.pose.position.y
                    - initial_turtlebot_odom_pose.pose.pose.position.y),
                2));
    // Move until robot reaches the desired distance
  } while ((distance_moved < distance) && (ros::ok()));
  // finally, stop the robot when the distance is moved
  VelocityMessage.linear.x = 0;
  // Publish Empty linear message to stop robot
  pub.publish(VelocityMessage);
}
/**
 * @brief      Executes a dummy trajectory for turtlebot
 *
 * @param[in]  velocity     Velocity of robot
 * 
 */
double ControlTurtlebot::circle(double speed) {
  geometry_msgs::Twist VelocityMessage;
  // Publish velocity message
  pub.publish(VelocityMessage);
  VelocityMessage.linear.x = speed;
  VelocityMessage.angular.z = speed;
  return 1;
}
/**
 * @brief      Executes the rotation for turtlebot
 *
 * @param[in]  clockwise            To make sure robot always rotates in a clockwise direction
 * @param[in]  radians              Angle by which the robot needs to turn
 * @param[in]  angular_velocity     Velocity of robot rotation
 * 
 */
double ControlTurtlebot::rotate(double angular_velocity, double radians,
                                bool clockwise) {
  // delcare a Twist message to send velocity commands
  geometry_msgs::Twist VelocityMessage;
  // declare tf transform listener: this transform listener
  // will be used to listen and capture the transformation between
  // the odom frame (that represent the reference frame) and the
  // base_footprint frame the represent moving frame
  tf::TransformListener TFListener;
  // declare tf transform
  // init_transform: is the transformation before starting the motion
  tf::StampedTransform init_transform;
  // current_transformation: is the transformation while the
  // robot is moving
  tf::StampedTransform current_transform;
  // initial coordinates (for method 3)
  nav_msgs::Odometry initial_turtlebot_odom_pose;
  double angle_turned = 0.0;
  // validate angular velocity;
  // ANGULAR_VELOCITY_MINIMUM_THRESHOLD is the minimum allowed
  angular_velocity = (
      (angular_velocity > ANGULAR_VELOCITY_MINIMUM_THRESHOLD) ?
          angular_velocity : ANGULAR_VELOCITY_MINIMUM_THRESHOLD);
  // Keep radians in the range
  while (radians < 0)
    radians += 2 * pi;
  while (radians > 2 * pi)
    radians -= 2 * pi;
  // wait for the listener to get the first message
  TFListener.waitForTransform("base_footprint", "odom", ros::Time(0),
                              ros::Duration(1.0));
  // record the starting transform from the odometry to the base frame
  TFListener.lookupTransform("base_footprint", "odom", ros::Time(0),
                             init_transform);
  // the command will be to turn at 0.75 rad/s
  VelocityMessage.linear.x = VelocityMessage.linear.y = 0.0;
  VelocityMessage.angular.z = angular_velocity;
  // Makes sure it moves in clocwise direction
  if (clockwise)
    VelocityMessage.angular.z = -VelocityMessage.angular.z;
  // the axis we want to be rotating by
  tf::Vector3 desired_turn_axis(0, 0, 1);
  // Makes sure it moves in clocwise direction
  if (!clockwise)
    desired_turn_axis = -desired_turn_axis;
  ros::Rate rate(10.0);
  bool done = false;
  while (!done) {
    // send the drive command
    pub.publish(VelocityMessage);
    rate.sleep();
    // get the current transform
    try {
      TFListener.waitForTransform("base_footprint", "odom", ros::Time(0),
                                  ros::Duration(1.0));
      TFListener.lookupTransform("base_footprint", "odom", ros::Time(0),
                                 current_transform);
    } catch (tf::TransformException ex) {
      ROS_ERROR("%s", ex.what());
      break;
    }
    tf::Transform relative_transform = init_transform.inverse()
        * current_transform;
    tf::Vector3 actual_turn_axis = relative_transform.getRotation().getAxis();
    angle_turned = relative_transform.getRotation().getAngle();

    if (fabs(angle_turned) < 1.0e-2)
      continue;
    if (actual_turn_axis.dot(desired_turn_axis) < 0)
      angle_turned = 2 * pi - angle_turned;

    if (!clockwise)
      VelocityMessage.angular.z = (angular_velocity
          - ANGULAR_VELOCITY_MINIMUM_THRESHOLD)
          * (fabs(
              radian2degree(radians - angle_turned) / radian2degree(radians)))
          + ANGULAR_VELOCITY_MINIMUM_THRESHOLD;
    else if (clockwise)
      VelocityMessage.angular.z = (-angular_velocity
          + ANGULAR_VELOCITY_MINIMUM_THRESHOLD)
          * (fabs(
              radian2degree(radians - angle_turned) / radian2degree(radians)))
          - ANGULAR_VELOCITY_MINIMUM_THRESHOLD;

    if (angle_turned > radians) {
      done = true;
      VelocityMessage.linear.x = VelocityMessage.linear.y = VelocityMessage
          .angular.z = 0;
      pub.publish(VelocityMessage);
    }
  }
  if (done)
    return angle_turned;
  return angle_turned;
}
/**
 * @brief      makes conversion from radian to degree
 *
 * @param[in]  radianAngle              Angle by which the robot needs to turn
 * 
 */
double ControlTurtlebot::radian2degree(double radianAngle) {
  return (radianAngle * 57.2957795);
}

/**
 * @brief      makes conversion from degree to radian
 *
 * @param[in]  radianAngle              Angle by which the robot needs to turn
 * 
 */
double ControlTurtlebot::degree2radian(double degreeAngle) {
  return (degreeAngle / 57.2957795);
}

