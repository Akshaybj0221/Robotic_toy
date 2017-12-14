
#include "ControlTurtlebot.hpp"

/*ControlTurtlebot::ControlTurtlebot(self){
		
		this->self = self;
		ros::init(argc, argv, "ControlTurtlebotNode");
		ROS_INFO("Press Ctrl+C to exit/stop");
		ros::shutdown(self.shutdown());		
		ros::Publisher self.cmd_vel = nh.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity", 10)

		rate = 50;
		r = ros::Rate loop_rate(rate);
		
		linear_speed = 0.5;
		goal_distance = 1.0;
		linear_duration = goal_distance / linear_speed;
		angular_speed = 1.0;

		n = 4;
		angle = 360/n;	
		pi = 3.14;
		rad = angle*(pi/180);

		angular_duration = (rad / angular_speed);

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

	void shutdown(self){
		ROS_INFO("Stopping Turtlebot");
		self.cmd_vel.publish(geometry_msgs::Twist);
		ros::Duration(1).sleep();	//Here i have used the replacement for the same Twist() in cpp
	}

ControlTurtlebot::~ControlTurtlebot(){
}
*/
void main(int argc, char **argv){

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

}
