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
	
		rate = 50
		r = rospy.Rate(rate);
		
		linear_speed = 0.2
		goal_distance = 1.0 
		linear_duration = goal_distance / linear_speed
		angular_speed = 1.0
		n = 4
		angle = 360 / n		
		pi = 3.14
		rad = angle*(pi/180)
		
		angular_duration = rad / angular_speed

		
		move_cmd.angular.z = rad
		move_cmd.linear.x = linear_speed
		ticks = int(linear_duration * rate)

		for t in range(ticks):
			self.cmd_vel.publish(move_cmd)
			r.sleep()

		move_cmd = Twist()
		self.cmd_vel.publish(move_cmd)
		rate.sleep(1)
		
		move_cmd.angular.z = angular_speed
		ticks = int(goal_angle * rate)

		for t in range(ticks):
			self.cmd_vel.publish(move_cmd)
			r.sleep()

		move_cmd = Twist()
		self.cmd_vel.publish(move_cmd)
		rate.sleep(1)	

		self.cmd_vel.publish(Twist)

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
