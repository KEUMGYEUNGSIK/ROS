#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h> //cmd_vel
#include <sensor_msgs/Range.h>   //ultrasonic sensor message

std_msgs::Bool flag_AEB;

void UltraCallBack(const sensor_msgs::Range::ConstPtr& msg)
{
  ROS_INFO("Sonar Range : [%f]", msg->range);
  
  if(msg->range <= 1.0)
  {
		flag_AEB.data = true;
  }
  else
  {
		flag_AEB.data = false;
  }
}

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "aeb_controller1");

  ros::NodeHandle n;

  ros::Rate loop_rate(1); 
  
  ros::Publisher pub1 = n.advertise<std_msgs::Int32>("range1", 1000);
  
  while (ros::ok())
  {
	  
	  pub1.publish(flag_AEB);
	  
	  loop_rate.sleep();
	  ros::spinOnce();
  }
  return 0;
}

