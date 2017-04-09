#include "ros/ros.h"
#include "std_msgs/String.h"
#include "tf/transform_listener.h"
#include "sensor_msgs/LaserScan.h"

ros::Publisher pub

void callback(const sensor_msgs::LaserScan::ConstPtr&, 
			  tf::TransformListener* listener)
{

	tf::StampedTransform transform;
	try{
    	ros::Time t = ros::Time::now();
    	listener->waitForTransform("/base_laser_link", "/odom",
								   t, ros::Duration(3.0));
    	listener->lookupTransform("/base_laser_link", "/odom",
                                  t, transform);
                             
        std::stringstream ss;
        ss << "Laser(t,x,y,theta): " << transform.stamp_.toSec();
        ss << ", " << transform.getOrigin().x();
        ss << ", " << transform.getOrigin().y();
        ss << ", " << transform.getRotation().getAngle();
        
        
        std_msgs::String msg;
        msg.data = ss.str();
		ROS_INFO("%s", msg.data.c_str());
		
		pub.publish(msg);
        
    } catch(tf::TransformException ex){
    	ROS_ERROR("%s",ex.what());
    	ros::Duration(1.0).sleep(); 	
    }
}


int main(int argc, char** argv) {
	ros::init(argc, argv, "transformer");
	
	ros::NodeHandle n;
	tf::TransformListener listener;
	
	pub = nodeHandle.advertise<std_msgs::String>("position", 1000);
	
	ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>(
						  "base_scan", 1000, boost::bind(callback, _1, &listener));
	
	ros::spin();
	return 0;
}
