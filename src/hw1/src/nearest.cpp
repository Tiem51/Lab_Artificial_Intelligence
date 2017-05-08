#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/LaserScan.h"

ros::Publisher pub;

void callback(const sensor_msgs::LaserScan::ConstPtr& data){
	double min_value = DBL_MAX;
    int length = (data->ranges).size();
    int i = 0;
    
    while(i < length) {	
		double curr_value = (data->ranges)[i];
		if(curr_value < min_value) min_value = curr_value;
		i++;
    }
	
	if(ros::ok()) {
		std::stringstream ss;
		ss << "Nearest value is: " << min_value;
		
		std_msgs::String msg;
		msg.data = ss.str();
		
		ROS_INFO("%s", msg.data.c_str());
		pub.publish(msg);
	}
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "nearest");

	ros::NodeHandle nodeH;
		
	pub = nodeH.advertise<std_msgs::String>("nearest_value", 1000);
	ros::Subscriber sub = nodeH.subscribe("/base_scan", 1000,  callback);

	ros::spin();
	return 0;
}
