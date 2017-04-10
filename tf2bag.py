import rospy
import rosbag
from sensor_msgs.msg import LaserScan
from math import pi
from tf2_msgs.msg import TFMessage
from geometry_msgs.msg import TransformStamped
import tf
import csv

def make_tf_msg(time, x, y, z, qw, qx, qy, qz):
    trans = TransformStamped()
    trans.header.stamp = time
    trans.header.frame_id = '/odom'
    trans.transform.translation.x = x
    trans.transform.translation.y = y
    trans.transform.translation.z = z
    trans.transform.rotation.x = qx
    trans.transform.rotation.y = qy
    trans.transform.rotation.z = qz
    trans.transform.rotation.w = qw

    msg = TFMessage()
    msg.transforms.append(trans)
    return msg

with open('v103.csv') as dataset:
    with rosbag.Bag('v103_ground.bag', 'w') as bag:
        reader = csv.reader(dataset)
        for line in reader:
            time, x, y, z, qw, qx, qy, qz = line
            tf_msg = make_tf_msg(time, x, y, z, qw, qx, qy, qz)
            bag.write('tf', tf_msg, time)