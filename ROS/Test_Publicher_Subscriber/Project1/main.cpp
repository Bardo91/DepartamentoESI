#include "ros/ros.h"

#include "std_msgs/String.h"


#include <sstream>
#include <string>

int main(int argc, char **argv)
{
	std::cout << "EMPEZANDO!" << std::endl;

	std::string name = "talker";


	ros::init(argc, argv, name);


	std::cout << "Creando handler del nodo" << std::endl;
	ros::NodeHandle n;
	

	std::cout << "Creando publicador" << std::endl;
	ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
	
	
	
	ros::Rate loop_rate(10);
	
	std::cout << "Entrando en el bucle" << std::endl;
	int count = 0;
	while (ros::ok())
	{
	
	  std_msgs::String msg;
	
	  std::stringstream ss;
	  ss << "hello world " << count;
	  msg.data = ss.str();
	
	  ROS_INFO("%s", msg.data.c_str());
	
	  chatter_pub.publish(msg);
	
	  ros::spinOnce();
	
	  loop_rate.sleep();
	
	  ++count;
	}
	
	
  return 0;
}
