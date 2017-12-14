
#include "ControlTurtlebot.hpp"

class ControlTurtlebot::ControlTurtlebot(self){

//		rospy.init_node('ControlTurtlebotNode', anonymous=False)
//		rospy.loginfo("Ctrl + C to exit/stop")
//		rospy.on_shutdown(self.shutdown)
//		self.cmd_vel = rospy.Publisher('mobile_base/commands/velocity', Twist, queue_size=10)
//		rate = 50
//		r = rospy.Rate(rate);
//		linear_speed = 0.5
//		goal_distance = 1.0 
//		linear_duration = goal_distance / linear_speed
//		angular_speed = 1.0
//
//		n = 4
//		angle = 360 / n		
//		pi = 3.14
//		rad = angle*(pi/180)
//
//		angular_duration = (rad / angular_speed)
//		for i in range(n):

/*			move_cmd = Twist()
			move_cmd.linear.x = linear_speed
			rospy.loginfo("Inside 1st i loop")
			ticks = int(linear_duration * rate)

			for t in range(ticks):
				self.cmd_vel.publish(move_cmd)
				r.sleep()
	
			move_cmd = Twist()
			self.cmd_vel.publish(move_cmd)
			rospy.sleep(1)
			
			move_cmd.angular.z = angular_speed + 0.10
			ticks = int(rad * rate)
	
			for t in range(ticks):
				self.cmd_vel.publish(move_cmd)
				r.sleep()
	
			move_cmd = Twist()
			self.cmd_vel.publish(move_cmd)
			rospy.sleep(1)	
	
		self.cmd_vel.publish(Twist())

#		while not rospy.is_shutdown():
#			self.cmd_vel.publish(move_cmd)
#			rate.sleep()

	def shutdown(self):
		rospy.loginfo("Stopping turtlebot")
		self.cmd_vel.publish(Twist())
		rospy.sleep(1)

if __name__ == '__main__':
	try:
		ControlTurtlebot()
	except:
		rospy.loginfo("ENd of the turtlebot trip")
*/


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


void main(){
	try{
		ControlTurtlebot();
	} catch{
		ROS_INFO("End of Turtlebot Trip");
	}
}
