#include "ControlTurtlebot.hpp"


int main(int argc, char **argv){

	//initialize the ROS node
	ros::init(argc, argv, "free_space_navigation_node");
	ros::NodeHandle n;

	ControlTurtlebot obj;

	//subscribe to the odometry topic to get the position of the robot
	obj.pose_subscriber = n.subscribe("/odom", 10, obj.poseCallback);
	//register the velocity publisher
	obj.pub =n.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity", 1000);

	ros::spinOnce();
	ros::Rate loop(1);
	loop.sleep();loop.sleep();loop.sleep();//loop.sleep();loop.sleep();
	ros::spinOnce();

	while (ros::ok()){
		ros::spinOnce();loop.sleep();
		printf("robot initial pose: (%.2f, %.2f, %.2f)\n", obj.turtlebot_odom_pose.pose.pose.position.x, obj.turtlebot_odom_pose.pose.pose.position.y, obj.radian2degree(tf::getYaw(obj.turtlebot_odom_pose.pose.pose.orientation)));

		double velocity = 0.3;

		obj.moveShape(1.0, 3, 120, velocity);
		
		//exercise: try to remove the ros::SpinOnce() and observe and comment the result
		ros::spinOnce();loop.sleep();ros::spinOnce();
		printf("robot final pose: (%.2f, %.2f, %.2f)\n", obj.turtlebot_odom_pose.pose.pose.position.x, obj.turtlebot_odom_pose.pose.pose.position.y, obj.radian2degree(tf::getYaw(obj.turtlebot_odom_pose.pose.pose.orientation)));
		return 0;
	}

	return 0;
}
