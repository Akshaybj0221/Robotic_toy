#include "ros/ros.h"
#include "toy_robot/input.h"
#include <cstdlib>

bool add(toy_robot::input::Request  &req,
         toy_robot::input::Response &res)
{
  res.totalSidesOut = req.totalSidesIn;
  ROS_INFO("request: x=%ld", (long int)req.totalSidesIn);
  ROS_INFO("sending back response: [%ld]", (long int)res.totalSidesOut);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "input_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("input", add);
  ROS_INFO("User Input Service Started!");
  ros::spin();

  return 0;
}
