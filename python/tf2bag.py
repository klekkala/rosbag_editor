import rospy
import rosbag
from sensor_msgs.msg import LaserScan
import math
from tf2_msgs.msg import TFMessage
from geometry_msgs.msg import TransformStamped
import tf
import csv

def make_tf_msg(time, x, y, z, qw, qx, qy, qz):
    norm = math.sqrt(qw**2 + qx**2 + qy**2 + qz**2)
    trans = TransformStamped()
    trans.header.stamp = time
    trans.header.frame_id = '/odom'
    trans.child_frame_id = '/laser'
    trans.transform.translation.x = x
    trans.transform.translation.y = y
    trans.transform.translation.z = z
    trans.transform.rotation.x = qx/norm
    trans.transform.rotation.y = qy/norm
    trans.transform.rotation.z = qz/norm
    trans.transform.rotation.w = qw/norm

    msg = TFMessage()
    msg.transforms.append(trans)
    return msg


rospy.init_node('tf2bag')
with open('v102.csv') as dataset:
    with rosbag.Bag('v102_ground.bag', 'w') as bag:
        reader = csv.reader(dataset)
        t = rospy.get_rostime()
        T = 1.0/60.0
        d = rospy.Duration(T)
        for line in reader:
            time, x, y, z, qw, qx, qy, qz = line
            tf_msg = make_tf_msg(t, float(x), float(y), float(z), float(qw), float(qx), float(qy), float(qz))
            t = t+d
            bag.write('tf', tf_msg, t)