
#include "ControlTurtlebot.hpp"

ControlTurtlebot::ControlTurtlebot(ros::NodeHandle nh){

//		this->self = self;
		ros::init(argc, argv, "ControlTurtlebotNode");
		ROS_INFO("Press Ctrl+C to exit/stop");
		ros::shutdown(self.shutdown());		
		ros::Publisher self.cmd_vel = nh.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity", 10)
}

void ControlTurtlebot::init(){

	for(int i=0;i<=n;i++){
		geomtery_msgs::Twist move_cmd;
		move_cmd.linear.x = linear_speed;
		ROS_INFO("Inside 1st loop");
		ticks = int(linear_duration * rate);

		for(int t=0; t<=ticks; t++){
			self.cmd_vel.publish(move_cmd);
			r.sleep();
		}

		geomtery_msgs::Twist move_cmd;
		self.cmd_vel.publish(move_cmd);
		ros::Duration(1).sleep();
		
		move_cmd.angular.z = angular_speed + 0.10;
		ticks = int(rad * rate);
	
		for(int t=0; t<=ticks; t++){
			self.cmd_vel.publish(move_cmd);
			r.sleep();
		}	
		geomtery_msgs::Twist move_cmd;
		self.cmd_vel.publish(move_cmd);
		ros::Duration(1).sleep();
	}

	self.cmd_vel.publish(move_cmd);	//instead if move_cmd it was "Twist()", so take care)
	
	while(ros::ok()){
		self.cmd_vel.publish(move_cmd);
		rate.sleep();
}

void ControlTurtlebot::shutdown(){
	ROS_INFO("Stopping Turtlebot");
	self.cmd_vel.publish(geometry_msgs::Twist);
	ros::Duration(1).sleep();	//Here i have used the replacement for the same Twist() in cpp
}

ControlTurtlebot::~ControlTurtlebot(self){
}

void main(){
	try{
		ControlTurtlebot();
	} catch{
		ROS_INFO("End of Turtlebot Trip");
	}
}
