#!/usr/bin/env/python
import rospy
from geometry_msgs.msg import Twist

class ControlTurtlebot():
	def __init__(self):
		rospy.init_node('ControlTurtlebotNode', anonymous=False)
		rospy.loginfo("Ctrl + C to exit/stop")
		rospy.on_shutdown(self.shutdown)
		
		#Topic on which msg will be sent
		#cmd_vel_mux/input/navi		
		self.cmd_vel = rospy.Publisher('mobile_base/commands/velocity', Twist, queue_size=10)
		rate = rospy.Rate(10);
		move_cmd = Twist()
		move_cmd.linear.x = 0.3
		move_cmd.angular.z = 0

		while not rospy.is_shutdown():
			self.cmd_vel.publish(move_cmd)
			rate.sleep()

	def shutdown(self):
		rospy.loginfo("Stopping turtlebot")
		self.cmd_vel.publish(Twist())
		rospy.sleep(1)
if __name__ == '__main__':
	try:
		ControlTurtlebot()
	except:
		rospy.loginfo("ENd of the turtlebot trip")
