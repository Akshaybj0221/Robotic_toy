
#include "ControlTurtlebot.hpp"
#include "ros/ros.h"

ControlTurtlebot::ControlTurtlebot(ros::NodeHandle nh){
  
  init(nh);
  shutdown(nh);

}

int ControlTurtlebot::init(nh){

	for(int i=0;i<=n;i++){
		geomtery_msgs::Twist move_cmd;
		move_cmd.linear.x = linear_speed;
		ROS_INFO("Inside 1st loop");
		ticks = int(linear_duration * rate);

		for(int t=0; t<=ticks; t++){
			cmd_vel.publish(move_cmd);
			r.sleep();
		}

		geomtery_msgs::Twist move_cmd;
		cmd_vel.publish(move_cmd);
		ros::Duration(1).sleep();
		
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

	cmd_vel.publish(move_cmd);	//instead if move_cmd it was "Twist()", so take care)
	
	while(ros::ok()){
		cmd_vel.publish(move_cmd);
		rate.sleep();

	return 0;
}

int ControlTurtlebot::shutdown(nh){

	ROS_INFO("Stopping Turtlebot");
	cmd_vel.publish(geometry_msgs::Twist);
	ros::Duration(1).sleep();	//Here i have used the replacement for the same Twist() in cpp

	return 0;
}

ControlTurtlebot::~ControlTurtlebot(){
}


