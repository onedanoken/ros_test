#include "/home/iurbanovitch/ros2_ws/src/ros_test/include/ros_test/first_node.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FirstNode>());
  rclcpp::shutdown();
  return 0;
}
