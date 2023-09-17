import rclpy
from rclpy.node import Node

from std_msgs.msg import String

c_n_sec = 3
c_queue_size = 10
c_topic_pub = 'publisher'
c_topic_sub = 'subscription'
c_node_msg = 'Hello, I\'m Alive!'


class FirstNode(Node):

    def __init__(self):
        super().__init__('first_node')
        self._ppublisher = self.create_publisher(
            String,
            c_topic_pub,
            c_queue_size)
        self._psubscription = self.create_subscription(
            String,
            c_topic_sub,
            self.listener_callback,
            c_queue_size)
        self.timer = self.create_timer(c_n_sec, self.timer_callback)

    def timer_callback(self):
        msg = String()
        msg.data = c_node_msg
        self._ppublisher.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.data)


def main(args=None):
    rclpy.init(args=args)

    publisher = FirstNode()

    rclpy.spin(publisher)

    publisher.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
