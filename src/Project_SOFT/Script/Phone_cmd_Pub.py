import sys

import rospy
from std_msgs.msg import Int8

def CMD(data):
    pub = rospy.Publisher("CMD_start_stop", Int8, queue_size=10)
    rospy.init_node("Chatter_Pub",anonymous=True)
    
    if data == "start":
        user_val = 1

    elif data == "stop":
        user_val = 0

    elif data == "GPS_on":
        user_val = 2

    elif data == "GPS_off":
        user_val = 3


    pub.publish(user_val)                   
