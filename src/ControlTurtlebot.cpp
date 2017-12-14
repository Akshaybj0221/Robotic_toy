
#include "ControlTurtlebot.hpp"
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
ControlTurtlebot::ControlTurtlebot(ros::NodeHandle nh){
  	
  init(nh);
  shutdown(nh);

}

int ControlTurtlebot::init(ros::NodeHandle nh){

    int i, t, ticks;    
    int rate = 50;
//    ros::Rate r = ros::Rate loop_rate(50);		

    ros::Rate r(rate);

    int n = 4;

    float linear_speed = 0.5;
    float goal_distance = 1.0;
    float linear_duration = goal_distance / linear_speed;
    float angular_speed = 1.0;
    float angle = 360/n;	
    float pi = 3.14;
    float rad = angle*(pi/180);
    float angular_duration = (rad / angular_speed);


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
		
		move_cmd.angular.z = angular_speed;
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
		r.sleep();

	return 0;
}

int ControlTurtlebot::shutdown(ros::NodeHandle nh){

	ROS_INFO("Stopping Turtlebot");
	cmd_vel.publish(geometry_msgs::Twist);
	ros::Duration(1).sleep();	//Here i have used the replacement for the same Twist() in cpp

	return 0;
}

ControlTurtlebot::~ControlTurtlebot(){
}


