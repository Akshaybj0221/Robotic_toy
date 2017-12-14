int main(int argc, char **argv){

	//initialize the ROS node
	ros::init(argc, argv, "free_space_navigation_node");
	ros::NodeHandle n;

	//subscribe to the odometry topic to get the position of the robot
	pose_subscriber = n.subscribe("/odom", 10, poseCallback);
	//register the velocity publisher
	pub =n.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity", 1000);

	ros::spinOnce();
	ros::Rate loop(1);
	loop.sleep();loop.sleep();loop.sleep();//loop.sleep();loop.sleep();
	ros::spinOnce();

	while (ros::ok()){
		ros::spinOnce();loop.sleep();
		printf("robot initial pose: (%.2f, %.2f, %.2f)\n",turtlebot_odom_pose.pose.pose.position.x,turtlebot_odom_pose.pose.pose.position.y,radian2degree(tf::getYaw(turtlebot_odom_pose.pose.pose.orientation)));

		double velocity = 0.3;

		moveShape(1.0, 3, 120, velocity);
		
		//exercise: try to remove the ros::SpinOnce() and observe and comment the result
		ros::spinOnce();loop.sleep();ros::spinOnce();
		printf("robot final pose: (%.2f, %.2f, %.2f)\n",turtlebot_odom_pose.pose.pose.position.x,turtlebot_odom_pose.pose.pose.position.y,radian2degree(tf::getYaw(turtlebot_odom_pose.pose.pose.orientation)));
		return 0;
	}

	return 0;
}
