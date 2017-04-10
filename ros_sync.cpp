#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <sensor_msgs/Image.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace message_filters;
int i=0, j=0;
void synchronizedCallback(const sensor_msgs::ImageConstPtr& rgb_msg, const sensor_msgs::ImageConstPtr& depth_msg)
{
  ROS_INFO("Messages synchronized!");
  cv_bridge::CvImagePtr rgb_ptr, depth_ptr;
  rgb_ptr = cv_bridge::toCvCopy(rgb_msg, sensor_msgs::image_encodings::BGR8);
  cv::imwrite("rgb_frame_%d", i ,rgb_ptr->image);
  i++;
  depth_ptr = cv_bridge::toCvCopy(depth_msg, sensor_msgs::image_encodings::MONO8);
  cv::imwrite("depth_frame_%d", j ,depth_ptr->image);
  j++;
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "message_synchronizer_node");

  ros::NodeHandle nh;
  message_filters::Subscriber<sensor_msgs::Image> odom_sub(nh, "/kinect2/qhd/image_color_rect", 1);
  message_filters::Subscriber<sensor_msgs::Image> scan_sub(nh, "/kinect2/qhd/image_color_rect", 1);

  typedef sync_policies::ApproximateTime<sensor_msgs::Image, sensor_msgs::Image> MySyncPolicy;
  // ApproximateTime takes a queue size as its constructor argument, hence MySyncPolicy(10)
  Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), odom_sub, scan_sub);
  sync.registerCallback(boost::bind(&synchronizedCallback, _1, _2));

  ros::spin();

  return 0;
}