#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "sensor_msgs/Range.h"

std_msgs::Float32 avg_range;
float sum = 0, counting = 0;

void SonarAverageFilter(const sensor_msgs::Range::ConstPtr& msg)
{
	if(counting > 5)
	{
		avg_range.data = sum/5;
		counting = 0;
		sum = 0;
	}
	else
	{
		sum += msg->range;
		counting++;
	}
}

int main(int argc, char **argv)
{
  int count = 0;
  
  ros::init(argc, argv, "sonar_avg_filter");

  ros::NodeHandle n;

  ros::Rate loop_rate(5);
  
  ros::Subscriber sub = n.subscribe("range", 1000, SonarAverageFilter);
  
  ros::Publisher pub_SonarAverage = n.advertise<std_msgs::Float32>("/range_avg",10);
  while(ros::ok())
  {

	pub_SonarAverage.publish(avg_range);
	

	ROS_INFO("Sonar_average Range = %f", avg_range.data);

	loop_rate.sleep();
	ros::spinOnce();	
	count++;
  }

  return 0;
}
