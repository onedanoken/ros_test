#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


static const std::string c_node_name = "first_node";
static const std::string c_topic_publisher = "publisher";
static const std::string c_topic_subscriber = "subscription";
static const uint8_t c_n_test_sec = 15;
static const uint8_t c_queue_size_test = 20;
static const std::string c_n_parameter = "timer_param";
static const std::string c_queue_size_parameter = "queue_size_param";
static const std::string c_first_node_msg = "Hello, I'm Alive!";

class FirstNode : public rclcpp::Node
{
public:
  FirstNode()
  : Node(c_node_name)
  {
    this->declare_parameter(c_n_parameter, c_n_test_sec);
    this->declare_parameter(c_queue_size_parameter, c_queue_size_test);
    _n_sec = static_cast<uint8_t>(this->get_parameter(c_n_parameter).as_int());
    _queue_size = static_cast<uint8_t>(this->get_parameter(c_queue_size_parameter).as_int());
    _ppublisher = this->create_publisher<std_msgs::msg::String>(c_topic_publisher, _queue_size);
    _psubscription = this->create_subscription<std_msgs::msg::String>(
      c_topic_subscriber, _queue_size,
      std::bind(&FirstNode::topic_callback, this, std::placeholders::_1));
    _ptimer = this->create_wall_timer(
      std::chrono::seconds(_n_sec), std::bind(&FirstNode::timer_callback, this));
  }

private:
  uint8_t _n_sec;
  uint8_t _queue_size;

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

private:
  rclcpp::TimerBase::SharedPtr _ptimer;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _ppublisher;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr _psubscription;
};
