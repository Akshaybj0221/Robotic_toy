
//#include "ControlTurtlebot.hpp"



#include <iostream>
#include <sstream>
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"

int main(int argc, char **argv){

	ros::init(argc, argv, "ControlTurtlebotNode");
	
	ros::NodeHandle nh;
	ROS_INFO("Press Ctrl+C to exit/stop");

	ros::Publisher cmd_vel = nh.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity", 10);

	int rate = 50;
//	ros::Rate loop_rate(rate);
	//r	
        ros::Rate r(rate);

	while(ros::ok()){
	float linear_speed = 0.5;
	float goal_distance = 1.0;
	float linear_duration = goal_distance / linear_speed;
	
	int n = 4;
	float angle = 360/n;	
	float pi = 3.14;
	float rad = angle*(pi/180);

	float angular_speed = 1.0;
	float angular_duration = (rad / angular_speed);

	int ticks;

	for(int i=0;i<n;i++){
		geometry_msgs::Twist move_cmd;
		move_cmd.linear.x = linear_speed;
		ROS_INFO("Move forward");

		ticks = int(linear_duration * rate);
		for(int t=0; t<=ticks; t++){
			cmd_vel.publish(move_cmd);
			r.sleep();
		}


//		cmd_vel.publish(move_cmd);
		ros::Duration(1).sleep();
		ROS_INFO("Turn");
		
		move_cmd.angular.z = angular_speed + 0.10;
		ticks = int(rad * rate);
		for(int t=0; t<=ticks; t++){
			cmd_vel.publish(move_cmd);
			r.sleep();
		}

	}
	
	ros::spinOnce();
	r.sleep();


	geometry_msgs::Twist move_cmd;
	ROS_INFO("Stopping Turtlebot");

	cmd_vel.publish(move_cmd);
	ros::Duration(1).sleep();	//Here i have used the replacement for the same Twist() in cpp
	
	ros::shutdown();
	}
	
	

return 0;
}





//ControlTurtlebot::~ControlTurtlebot(){
//}








/*
void main(int argc, char **argv){

	cout<<"----------------------In main------------------------";

	ros::init(argc, argv, "ControlTurtlebotNode");
	ros::NodeHandle nh;
	
	ROS_INFO("Press Ctrl+C to exit/stop");
	
	ros::Publisher cmd_vel = nh.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity", 10);

	int r = ros::Rate loop_rate(50);
	

	ControlTurtlebot self(nh);

//	self.init(nh);
//	self.shutdown(nh);

//	ros::shutdown(self.shutdown());		

	
//	self.init();
//	self.shutdown();

}*/



