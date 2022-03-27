#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Range.h"
#include <geometry_msgs/Twist.h> //cmd_vel
#include <sensor_msgs/Range.h>   //ultrasonic sensor message
#include "nav_msgs/Odometry.h"

std_msgs::Bool flag_AEB;
std_msgs::Float32 delta_range;
std_msgs::Float32 old_sonar_range;
std_msgs::Float32 before_range;
geometry_msgs::Twist cmd_vel_msg;
nav_msgs::Odometry pos, delta_pos, before_pos;
nav_msgs::Odometry velocity;

void odomCallback(const nav_msgs::Odometry& msg)
{
	pos.pose.pose.position.x = msg.pose.pose.position.x;
	pos.pose.pose.position.y = msg.pose.pose.position.y;
	
	delta_pos.pose.pose.position.x = pos.pose.pose.position.x - before_pos.pose.pose.position.x;
	delta_pos.pose.pose.position.y = pos.pose.pose.position.y - before_pos.pose.pose.position.y;
	
	before_pos.pose.pose.position.x = msg.pose.pose.position.x;
	before_pos.pose.pose.position.y = msg.pose.pose.position.y;	
	
	velocity.twist.twist.linear.x = delta_pos.pose.pose.position.x / 0.02; //delta_t - 50hz -> 0.02s
	velocity.twist.twist.linear.y = delta_pos.pose.pose.position.y / 0.02;
}
/*
void UltraSonarCallback(const sensor_msgs::Range::ConstPtr& msg)
{
	ROS_INFO("Sonar Seq: [%d]", msg->header.seq);
	ROS_INFO("Sonar Range [%f]", msg->range);
	
	if(msg->range <=1.0)
	{
		ROS_INFO("AEB_Activation!!");
		flag_AEB.data = true;
	}
	else
	{
		flag_AEB.data = false;
	}
}
*/

void UltraSonarCallback2(const sensor_msgs::Range::ConstPtr& msg)
{
	ROS_INFO("Sonar Seq: [%d]", msg->header.seq);
	ROS_INFO("Sonar Range [%f]", msg->range);
	
	if(msg->range <=1.5)
	{
		ROS_INFO("AEB_Activation!!");
		flag_AEB.data = true;
	}
	else
	{
		flag_AEB.data = false;
	}
	
	delta_range.data = msg->range-old_sonar_range.data;
	ROS_INFO("delta_range : [%f]", delta_range.data);
	old_sonar_range.data = msg->range;
}

void CarControlCallback3(const geometry_msgs::Twist& msg)
{
	ROS_INFO("Cmd_vel : linear x [%f]", msg.linear.x);
	cmd_vel_msg = msg;
	/*
	ROS_INFO("Cmd_vel : linear_x [%f]", cmd_vel_msg.linear.x);
	*/
}

int main(int argc, char **argv)
{
  int count = 0;
  before_pos.pose.pose.position.x=0.0;
  before_pos.pose.pose.position.y=0.0;
  velocity.twist.twist.linear.x =0.0;
  velocity.twist.twist.linear.y =0.0;


  std::string odom_sub_topic = "/ackermann_steering_controller/odom"; //50hz
  old_sonar_range.data = 0;
  
  ros::init(argc, argv, "aeb_controller2");

  ros::NodeHandle n;
  //Subscriber
  /*
  ros::Subscriber sub1 = n.subscribe("seq", 1000, UltraSonarCallback2);
  */
  
  ros::Subscriber sub = n.subscribe("range", 1000, UltraSonarCallback2);
  /*
  ros::Subscriber sub1 = n.subscribe("/RangeSonar1", 1000, UltraSonarCallback);
  */
  ros::Subscriber cmd_vel_sub = n.subscribe("/cmd_vel", 10, &CarControlCallback3);
  
  ros::Subscriber sub_odom = n.subscribe("/odom_sub_topic", 10, &odomCallback);
  //Publusher
  ros::Publisher pub_aeb_activation_flag = n.advertise<std_msgs::Bool>("/aeb_activation_flag", 1);
  
  ros::Publisher pub_cmd_vel = n.advertise<geometry_msgs::Twist>("/ackermann_steering_controller/cmd_vel", 10);
  
  ros::Publisher pub_delta_range = n.advertise<std_msgs::Float32>("/delta_range",1);

  ros::Publisher pub_velocity = n.advertise<nav_msgs::Odometry>("/odom_sub_topic",10);
  
  ros::Rate loop_rate(10); 
  
  while(ros::ok())
  {
	if((count%10)==0)
	{
		pub_aeb_activation_flag.publish(flag_AEB);
	
	}
	
	if(flag_AEB.data == true)
	{
		cmd_vel_msg.linear.x = 0;
		pub_cmd_vel.publish(cmd_vel_msg);
	}
	
	else
	{
		pub_cmd_vel.publish(cmd_vel_msg);
	}

	pub_velocity.publish(velocity);
	
	loop_rate.sleep();
	ros::spinOnce();	
	count++;
  }
  
  return 0;
}
