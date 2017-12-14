
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
	ros::Rate loop_rate(rate);
	//r	

	while(ros::ok()){
	linear_speed = 0.5;
	goal_distance = 1.0;
	linear_duration = goal_distance / linear_speed;
	
	n = 4;
	angle = 360/n;	
	pi = 3.14;
	rad = angle*(pi/180);

	angular_speed = 1.0;
	angular_duration = (rad / angular_speed);


	for(int i=0;i<=n;i++){
		geomtery_msgs::Twist move_cmd;
		move_cmd.linear.x = linear_speed;
		ROS_INFO("Move forward");

		ticks = int(linear_duration * rate);
		for(int t=0; t<=ticks; t++){
			cmd_vel.publish(move_cmd);
			rate.sleep();
		}

		geomtery_msgs::Twist move_cmd;
		cmd_vel.publish(move_cmd);
		ros::Duration(1).sleep();
		ROS_INFO("Turn");
		
		move_cmd.angular.z = angular_speed + 0.10;
		ticks = int(rad * rate);
		for(int t=0; t<=ticks; t++){
			cmd_vel.publish(move_cmd);
			r.sleep();
		}	

		geomtery_msgs::Twist move_cmd;
		cmd_vel.publish(move_cmd);
		ros::Duration(1).sleep();
	}

//	cmd_vel.publish(move_cmd);	//instead if move_cmd it was "Twist()", so take care)
	
//	while(ros::ok()){
//		cmd_vel.publish(move_cmd);
//		rate.sleep();
//}

	ROS_INFO("Stopping Turtlebot");
	self.cmd_vel.publish(geometry_msgs::Twist);
	ros::Duration(1).sleep();	//Here i have used the replacement for the same Twist() in cpp
	}
	
return 0;
}





//ControlTurtlebot::~ControlTurtlebot(){
//}
*/






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



