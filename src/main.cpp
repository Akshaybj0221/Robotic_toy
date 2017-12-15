#include "ControlTurtlebot.hpp"



int main(int argc, char **argv){

  	double velocity = 0.3;
  	double angle;
  	double sideLength = 1.0;


	//initialize the ROS node
	ros::init(argc, argv, "free_space_navigation_node");
	ros::NodeHandle n;


	ControlTurtlebot obj;
//	sleep(30);
	ros::ServiceClient client = n.serviceClient<toy_robot::input>("input");
	toy_robot::input srv;
	srv.request.totalSidesIn = atoll(argv[1]);

	if (ros::service::waitForService("input", 1000)) {
   	    ros::init(argc, argv, "free_space_navigation_node");
	    ROS_INFO("The service is available!", (long int)srv.response.totalSidesOut);
	}


	if (client.call(srv))
	{
		ros::init(argc, argv, "free_space_navigation_node");		
		ROS_INFO("Request of input service is: ", (long int)srv.response.totalSidesOut);
	}		
	else
 	{
    		ROS_ERROR("Failed to call service input");
    		return 1;
  	}



	double totalSides = abs(srv.response.totalSidesOut);	

  	//subscribe to the odometry topic to get the position of the robot
  	obj.pose_subscriber = n.subscribe("/odom", 10, &ControlTurtlebot::poseCallback, &obj);
	//register the velocity publisher

	obj.pub =n.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity", 1000);

	ros::spinOnce();
	ros::Rate loop(1);
	loop.sleep();loop.sleep();loop.sleep();//loop.sleep();loop.sleep();
	ros::spinOnce();

	while (ros::ok()){
		ros::spinOnce();loop.sleep();
		printf("robot initial pose: (%.2f, %.2f, %.2f)\n", obj.turtlebot_odom_pose.pose.pose.position.x, obj.turtlebot_odom_pose.pose.pose.position.y, obj.radian2degree(tf::getYaw(obj.turtlebot_odom_pose.pose.pose.orientation)));

		if(totalSides > 1){
			angle = 360/totalSides;
		}
		if(totalSides <= 1){
			angle = 360;
			totalSides = 1;
		}	

		obj.moveShape(sideLength, totalSides, angle, velocity);

//		obj.moveShape(1.0, 3, 120, 0.3);


//		obj.moveLinear(1.0, 1.0, true);
		
		//exercise: try to remove the ros::SpinOnce() and observe and comment the result
		ros::spinOnce();loop.sleep();ros::spinOnce();
		printf("robot final pose: (%.2f, %.2f, %.2f)\n", obj.turtlebot_odom_pose.pose.pose.position.x, obj.turtlebot_odom_pose.pose.pose.position.y, obj.radian2degree(tf::getYaw(obj.turtlebot_odom_pose.pose.pose.orientation)));
		return 0;
	}

	return 0;
}



