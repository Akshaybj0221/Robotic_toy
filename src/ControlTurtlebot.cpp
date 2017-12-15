#include "ControlTurtlebot.hpp"


//ControlTurtlebot::ControlTurtlebot() {

//ros::ServiceServer service = n.advertiseService("input", &ControlTurtlebot::add, this);	

//}


void ControlTurtlebot::poseCallback(const nav_msgs::Odometry::ConstPtr& pose_message){

	turtlebot_odom_pose.pose.pose.position.x=pose_message->pose.pose.position.x;
	turtlebot_odom_pose.pose.pose.position.y=pose_message->pose.pose.position.y;
	turtlebot_odom_pose.pose.pose.position.z=pose_message->pose.pose.position.z;

	turtlebot_odom_pose.pose.pose.orientation.w=pose_message->pose.pose.orientation.w;
	turtlebot_odom_pose.pose.pose.orientation.x=pose_message->pose.pose.orientation.x;
	turtlebot_odom_pose.pose.pose.orientation.y=pose_message->pose.pose.orientation.y;
	turtlebot_odom_pose.pose.pose.orientation.z=pose_message->pose.pose.orientation.z;

}	

/*
bool ControlTurtlebot::add(toy_robot::input::Request  &req,
         toy_robot::input::Response &res)
{
  res.totalSidesOut = req.totalSidesIn;
  ROS_INFO("request: x=%ld", (long int)req.totalSidesIn);
  ROS_INFO("sending back response: [%ld]", (long int)res.totalSidesOut);
  return true;
}

*/


void ControlTurtlebot::moveShape(double sideLength, double totalSides, double angle, double velocity){

	std::cout<<"Inside moveShape\n";
	std::cout<<"\nTotalSides: "<<totalSides<<"\n";
	std::cout<<"\nAngle: "<<angle<<"\n";
	std::cout<<"\nVelocity: "<<velocity<<"\n";

	for (int i=0;i<totalSides;i++){

	std::cout<<"Inside I of moveShape func\n";		
	if(totalSides > 1){		
		move_linear(velocity, sideLength, true, totalSides);
		rotate (velocity, degree2radian(angle), true);
	}
	else{
		circle (velocity);
	}
	}	
}


void ControlTurtlebot::move_linear(double speed, double distance, bool isForward, double totalSides){
	//delcare a Twist message to send velocity commands
	geometry_msgs::Twist VelocityMessage;
	//initial pose of the turtlebot before start moving
	nav_msgs::Odometry initial_turtlebot_odom_pose;

	std::cout<<"SPEED / linear.x "<<speed<<"\n";
	

	//set the linear velocity to a positive value if isFoward is true
	if (isForward)
		VelocityMessage.linear.x =speed;
	//all velocities of other axes must be zero.
	VelocityMessage.linear.y = VelocityMessage.linear.z =VelocityMessage.angular.x =VelocityMessage.angular.y =VelocityMessage.angular.z =0;

	double distance_moved = 0.0;
	ros::Rate loop_rate(10); // we publish the velocity at 10 Hz (10 times a second)

	int count = 0;

	//we update the initial_turtlebot_odom_pose using the turtlebot_odom_pose global variable updated in the callback function poseCallback
	initial_turtlebot_odom_pose = turtlebot_odom_pose;

//	std::cout<<"Velocity message BEFORE calculation"<<VelocityMessage;
	do{
		pub.publish(VelocityMessage);
		std::cout<<"Velocity message BEFORE calculation"<<VelocityMessage;

		ros::spinOnce();
		loop_rate.sleep();
		distance_moved = sqrt(pow((turtlebot_odom_pose.pose.pose.position.x-initial_turtlebot_odom_pose.pose.pose.position.x), 2) +
				pow((turtlebot_odom_pose.pose.pose.position.y-initial_turtlebot_odom_pose.pose.pose.position.y), 2));

	if((turtlebot_odom_pose.pose.pose.position.x == initial_turtlebot_odom_pose.pose.pose.position.x)||(turtlebot_odom_pose.pose.pose.position.y == initial_turtlebot_odom_pose.pose.pose.position.y)){
	count ++;
	}

	}while((distance_moved<distance)&&(ros::ok())&&(count<totalSides));

	//finally, stop the robot when the distance is moved
	VelocityMessage.linear.x =0;
	pub.publish(VelocityMessage);
	std::cout<<"Velocity message AFTER calculation"<<VelocityMessage;
	count = 0;

}

double ControlTurtlebot::circle(double speed){
	geometry_msgs::Twist VelocityMessage;
	pub.publish(VelocityMessage);
	VelocityMessage.linear.x =speed;
	VelocityMessage.angular.z =speed;
}

double ControlTurtlebot::rotate(double angular_velocity, double radians,  bool clockwise)
{

	//delcare a Twist message to send velocity commands
	geometry_msgs::Twist VelocityMessage;
	//declare tf transform listener: this transform listener will be used to listen and capture the transformation between
	// the odom frame (that represent the reference frame) and the base_footprint frame the represent moving frame
	tf::TransformListener TFListener;
	//declare tf transform
	//init_transform: is the transformation before starting the motion
	tf::StampedTransform init_transform;
	//current_transformation: is the transformation while the robot is moving
	tf::StampedTransform current_transform;
	//initial coordinates (for method 3)
	nav_msgs::Odometry initial_turtlebot_odom_pose;

	double angle_turned =0.0;

	//validate angular velocity; ANGULAR_VELOCITY_MINIMUM_THRESHOLD is the minimum allowed
	angular_velocity=((angular_velocity>ANGULAR_VELOCITY_MINIMUM_THRESHOLD)?angular_velocity:ANGULAR_VELOCITY_MINIMUM_THRESHOLD);

	while(radians < 0) radians += 2*pi;
	while(radians > 2*pi) radians -= 2*pi;

	//wait for the listener to get the first message
	TFListener.waitForTransform("base_footprint", "odom", ros::Time(0), ros::Duration(1.0));

	//record the starting transform from the odometry to the base frame
	TFListener.lookupTransform("base_footprint", "odom", ros::Time(0), init_transform);

	//the command will be to turn at 0.75 rad/s
	VelocityMessage.linear.x = VelocityMessage.linear.y = 0.0;
	VelocityMessage.angular.z = angular_velocity;
	if (clockwise) VelocityMessage.angular.z = -VelocityMessage.angular.z;

	//the axis we want to be rotating by
	tf::Vector3 desired_turn_axis(0,0,1);
	if (!clockwise) desired_turn_axis = -desired_turn_axis;

	ros::Rate rate(10.0);
	bool done = false;
	while (!done )
	{
		//send the drive command
		pub.publish(VelocityMessage);
		rate.sleep();
		//get the current transform
		try
		{
			TFListener.waitForTransform("base_footprint", "odom", ros::Time(0), ros::Duration(1.0));
			TFListener.lookupTransform("base_footprint", "odom", ros::Time(0), current_transform);
		}
		catch (tf::TransformException ex)
		{
			ROS_ERROR("%s",ex.what());
			break;
		}
		tf::Transform relative_transform = init_transform.inverse() * current_transform;
		tf::Vector3 actual_turn_axis = relative_transform.getRotation().getAxis();
		angle_turned = relative_transform.getRotation().getAngle();

		if (fabs(angle_turned) < 1.0e-2) continue;
		if (actual_turn_axis.dot(desired_turn_axis ) < 0 )
			angle_turned = 2 * pi - angle_turned;

		if (!clockwise)
			VelocityMessage.angular.z = (angular_velocity-ANGULAR_VELOCITY_MINIMUM_THRESHOLD) * (fabs(radian2degree(radians-angle_turned)/radian2degree(radians)))+ANGULAR_VELOCITY_MINIMUM_THRESHOLD;
		else
			if (clockwise)
				VelocityMessage.angular.z = (-angular_velocity+ANGULAR_VELOCITY_MINIMUM_THRESHOLD) * (fabs(radian2degree(radians-angle_turned)/radian2degree(radians)))-ANGULAR_VELOCITY_MINIMUM_THRESHOLD;

		if (angle_turned > radians) {
			done = true;
			VelocityMessage.linear.x = VelocityMessage.linear.y = VelocityMessage.angular.z = 0;
			pub.publish(VelocityMessage);
		}

	}
	if (done) return angle_turned;
	return angle_turned;
}

/* makes conversion from radian to degree */
double ControlTurtlebot::radian2degree(double radianAngle){
	return (radianAngle*57.2957795);
}


/* makes conversion from degree to radian */
double ControlTurtlebot::degree2radian(double degreeAngle){
	return (degreeAngle/57.2957795);
}






