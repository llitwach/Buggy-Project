#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"
#include <sstream>


int main(int argc, char **argv)
{
  std_msgs::Int8 user_val;

  ros::init(argc, argv, "Buggy");


  ros::NodeHandle n;

  
  ros::Publisher chatter_pub = n.advertise<std_msgs::Int8>("CMD_start_stop", 1000);

  ros::Rate loop_rate(10);

  
  while (ros::ok())
  {
   
    std_msgs::String msg;

    std::cout << "Send Command: ";
    std::getline (std::cin,msg.data);

   if(msg.data == "start"){
	user_val.data = 1;
	 }
	if(msg.data== "stop"){
	user_val.data = 0;
	 }
	if(msg.data== "GPS_on"){
	user_val.data = 2;
	 }

	if(msg.data== "GPS_off"){
	user_val.data = 3;
	 }

    ROS_INFO("%s", msg.data.c_str());

    
    chatter_pub.publish(user_val);

    ros::spinOnce();

    loop_rate.sleep();
    
  }


  return 0;
}