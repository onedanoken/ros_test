#include <memory>
#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/int8.hpp"

static const uint8_t c_n_sec = 3;
static const std::string c_topic_publisher = "publisher";
static const std::string c_topic_subscriber = "subscription";
static const uint8_t c_queue_size = 10;
static const std::string c_second_node_msg = "Funny!";

class SecondNode : public rclcpp::Node
{
  public:
    SecondNode()
    : Node("second_node")
    {
      _ppublisher = this->create_publisher<std_msgs::msg::String>(c_topic_subscriber, c_queue_size);
      _psubscription = this->create_subscription<std_msgs::msg::String>(
      c_topic_publisher, c_queue_size, std::bind(&SecondNode::topic_callback, this, std::placeholders::_1));
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

  private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _ppublisher;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr _psubscription;
};