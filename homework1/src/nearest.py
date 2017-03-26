#!/usr/bin/env python

import rospy
from sensor_msgs.msg import LaserScan
from std_msgs.msg import String

pub = rospy.Publisher('value_node', String, queue_size=10)


def sub_callback(data):
	min_value = 'Min value = ' + str(min(data.ranges))
	rospy.loginfo('%s', min_value)
	pub.publish(min_value)

def nearest():
	rospy.init_node('nearest', anonymous=True)
	rospy.Subscriber("/base_scan", LaserScan, sub_callback)
	rospy.spin()
	
if __name__ == '__main__':
    try:
        nearest()
    except rospy.ROSInterruptException:
        pass
