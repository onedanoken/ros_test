#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int32.hpp"

static const uint8_t c_n_sec = 1;
static const std::string c_topic_name = "topic";
static const uint8_t c_queue_size = 10;

class FirstNode : public rclcpp::Node
{
  public:
    FirstNode()
    : Node("first_node")
    {
      _ppublisher = this->create_publisher<std_msgs::msg::String>(c_topic_name, c_queue_size);
      _ptimer = this->create_wall_timer(
      std::chrono::seconds(c_n_sec), std::bind(&FirstNode::timer_callback, this));
    }

  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::String();
      message.data = "Hello, I’m alive!";
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      _ppublisher->publish(message);
    }

  private:
    rclcpp::TimerBase::SharedPtr _ptimer;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _ppublisher;
};