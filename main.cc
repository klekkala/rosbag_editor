#include<iostream>
#include<fstream>
#include<sstream>
#include<ros/ros.h>
#include<rosbag/bag.h>
#include<rosbag/view.h>
#include<sensor_msgs/Image.h>
#include<std_msgs/Time.h>
#include<std_msgs/Header.h>
#include<cstdlib>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <ardrone_autonomy/Navdata.h>
#include "Thirdparty/DLib/FileFunctions.h"


using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "BagFromImages");

  //  if(argc!=5)
    //{
      //  cerr << "Usage: rosrun BagFromImages BagfromImages <frequency> <path to output bag>" << endl;
      //  return 0;
   // }

    ros::start();

    ifstream vx_log("/home/kiran/rosbuild_ws/package_dir/rosbag_modifier/vx_log.txt", ios::in);
    ifstream vy_log("/home/kiran/rosbuild_ws/package_dir/rosbag_modifier/vy_log.txt", std::ios::in);
    ifstream ax_log("/home/kiran/rosbuild_ws/package_dir/rosbag_modifier/ax_log.txt", std::ios::in);
    ifstream ay_log("/home/kiran/rosbuild_ws/package_dir/rosbag_modifier/ay_log.txt", std::ios::in);
    ifstream az_log("/home/kiran/rosbuild_ws/package_dir/rosbag_modifier/az_log.txt", std::ios::in);
    ifstream roll_log("/home/kiran/rosbuild_ws/package_dir/rosbag_modifier/roll_log.txt", std::ios::in);
    ifstream pitch_log("/home/kiran/rosbuild_ws/package_dir/rosbag_modifier/pitch_log.txt", std::ios::in);
    ifstream yaw_log("/home/kiran/rosbuild_ws/package_dir/rosbag_modifier/yaw_log.txt", std::ios::in);
    ifstream altd_log("/home/kiran/rosbuild_ws/package_dir/rosbag_modifier/altd_log.txt", std::ios::in);

    if (!vx_log.is_open()) {
        std::cerr << "There was a problem opening the input file!\n";
        exit(1);//exit or do additional error checking
    }

    //read ifstream nto array
    vector<double> vx;
    vector<double> vy;
    vector<double> ax;
    vector<double> ay;
    vector<double> az;
    vector<double> altd;
    vector<double> roll;
    vector<double> pitch;
    vector<double> yaw;
    int i=0;
    string line;
    double num;
    while (vx_log >> num) {
        vx.push_back(num);
        getchar();
    }
    
    num = 0.0;
    while (vy_log >> num) {
        vy.push_back(num);
    }

    num = 0.0;
    while (ax_log >> num) {
        ax.push_back(num);
    }

    num = 0.0;
    while (ay_log >> num) {
        ay.push_back(num);
    }

    num = 0.0;
	    while (az_log >> num) {
	        az.push_back(num);
	    }

	    num = 0.0;
    while (roll_log >> num) {
        roll.push_back(num);
    }

    num = 0.0;
    while (pitch_log >> num) {
        pitch.push_back(num);
    }

    num = 0.0;
    while (yaw_log >> num) {
        yaw.push_back(num);
    }
    ardrone_autonomy::Navdata msg;
    // Frequency
    double freq = 15;

    // Output bag
    rosbag::Bag bag_out("bag.bag",rosbag::bagmode::Write);

    ros::Time t = ros::Time::now();

    const float T=1.0f/freq;
    ros::Duration d(T);

    cout << vx.size() << endl;
    cout << vx[3090] << endl;
   /* for(i=0;i<4704;i++)
    {
        if(!ros::ok())
            break;

        msg.header.seq = i;
        msg.header.stamp = ros::Time::now();
        msg.rotX = pitch[i];
        msg.rotY = roll[i];
        msg.rotZ = yaw[i];
        msg.altd = altd[i];
        msg.vx = vx[i];
        msg.vy = vy[i];
        msg.ax = ax[i];
        msg.ay = ay[i];
        msg.az = az[i];
        bag_out.write("/ardrone/navdata",ros::Time(t),msg);
        t+=d;
        cout << pitch[i] << " / " << 4704 << endl;
    }
*/
    bag_out.close();

    ros::shutdown();

    return 0;
}
