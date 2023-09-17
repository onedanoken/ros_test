import rclpy
from rclpy.node import Node

from std_msgs.msg import String

c_queue_size = 10
c_topic_pub = 'publisher'
c_topic_sub = 'subscription'
c_node_msg = 'Funny!'


class SecondNode(Node):

    def __init__(self):
        super().__init__('second_node')
        self._ppublisher = self.create_publisher(
            String,
            c_topic_sub,
            c_queue_size)
        self._psubscription = self.create_subscription(
            String,
            c_topic_pub,
            self.listener_callback,
            c_queue_size)

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.data)

        msg = String()
        msg.data = c_node_msg
        self._ppublisher.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)


def main(args=None):
    rclpy.init(args=args)

    subscriber = SecondNode()

    rclpy.spin(subscriber)

    subscriber.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
