#include "base_node.hpp"


class SecondNode : public BaseNode
{
public:
  SecondNode()
  : BaseNode(c_second_node_name)
  {
    this->declare_parameter(c_queue_size_parameter, c_queue_size_test);
    _queue_size = static_cast<uint8_t>(this->get_parameter(c_queue_size_parameter).as_int());
    _ppublisher = this->create_publisher<std_msgs::msg::String>(c_topic_subscriber, _queue_size);
    _psubscription = this->create_subscription<std_msgs::msg::String>(
      c_topic_publisher, _queue_size,
      std::bind(&SecondNode::topic_callback, this, std::placeholders::_1));
  }

private:
  void topic_callback(const std_msgs::msg::String & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());

    auto message = std_msgs::msg::String();
    message.data = c_second_node_msg;
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    _ppublisher->publish(message);
  }
};
