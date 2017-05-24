#include "ros/ros.h"
#include "std_msgs/String.h"




bool start = false;
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());

	if(msg->data.c_str() == "start"){
		start = true;
	}
	if(msg->data.c_str() == "stop"){
		start = false;
	}
}

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "Arduino_listen");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("CMD_start_stop", 1000, chatterCallback);


  ros::spin();

  return 0;
}





