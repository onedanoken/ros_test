#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


static const uint8_t c_n_sec = 5;
static const std::string c_topic_publisher = "publisher";
static const std::string c_topic_subscriber = "subscription";
static const uint8_t c_queue_size = 10;
static const std::string c_first_node_msg = "Hello, I'm Alive!";

class FirstNode : public rclcpp::Node
{
public:
  FirstNode()
  : Node("first_node")
  {
    _ppublisher = this->create_publisher<std_msgs::msg::String>(c_topic_publisher, c_queue_size);
    _psubscription = this->create_subscription<std_msgs::msg::String>(
      c_topic_subscriber, c_queue_size,
      std::bind(&FirstNode::topic_callback, this, std::placeholders::_1));
    _ptimer = this->create_wall_timer(
      std::chrono::seconds(c_n_sec), std::bind(&FirstNode::timer_callback, this));
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

private:
  rclcpp::TimerBase::SharedPtr _ptimer;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _ppublisher;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr _psubscription;
};
