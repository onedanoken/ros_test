#include "base_node.hpp"


class FirstNode : public BaseNode
{
public:
  FirstNode()
  : BaseNode(c_first_node_name)
  {
    this->declare_parameter(c_n_parameter, c_n_test_sec);
    this->declare_parameter(c_queue_size_parameter, c_queue_size_test);
    _n_sec = this->get_parameter(c_n_parameter).as_int();
    _queue_size = this->get_parameter(c_queue_size_parameter).as_int();
    _ppublisher = this->create_publisher<std_msgs::msg::String>(c_topic_publisher, _queue_size);
    _psubscription = this->create_subscription<std_msgs::msg::String>(
      c_topic_subscriber, _queue_size,
      std::bind(&FirstNode::topic_callback, this, std::placeholders::_1));
    _ptimer = this->create_wall_timer(
      std::chrono::seconds(_n_sec), std::bind(&FirstNode::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    message.data = c_first_node_msg;
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    _ppublisher->publish(message);
  }

private:
  void topic_callback(const std_msgs::msg::String & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
  }
};
