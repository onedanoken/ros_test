#pragma once

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"


static const std::string c_topic_publisher = "publisher";
static const std::string c_topic_subscriber = "subscription";
static const uint8_t c_queue_size_test = 20;
static const uint8_t c_n_test_sec = 15;
static const std::string c_n_parameter = "timer_param";
static const std::string c_queue_size_parameter = "queue_size_param";
static const std::string c_first_node_msg = "Hello, I'm Alive!";
static const std::string c_second_node_msg = "Funny!";
static const std::string c_first_node_name = "first_node";
static const std::string c_second_node_name = "second_node";

class BaseNode : public rclcpp::Node
{
public:
  BaseNode(const std::string & _node_name)
  : Node(_node_name)
  {
  }

public:
  uint8_t _queue_size;
  uint8_t _n_sec;

private:
  void timer_callback();

private:
  void topic_callback(const std_msgs::msg::String & msg) const;

protected:
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _ppublisher;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr _psubscription;
  rclcpp::TimerBase::SharedPtr _ptimer;
};
