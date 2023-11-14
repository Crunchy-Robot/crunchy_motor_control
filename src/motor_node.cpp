#include "rclcpp/rclcpp.hpp"
#include "crunchy_motor_control/msg/motor_command.hpp"

namespace crunchy {
  class MotorNode : public rclcpp::Node {
  public:
    MotorNode() : Node("motor_node") {
      command_subscriber_ = this->create_subscription<crunchy_motor_control::msg::MotorCommand>(
          "command", 10,
	  std::bind(&MotorNode::callback, this, std::placeholders::_1));
    }

  private:
    void callback(const crunchy_motor_control::msg::MotorCommand::SharedPtr msg) const {
      std::cout << msg->step_count << ", " << msg->speed << std::endl;
    }

    rclcpp::Subscription<crunchy_motor_control::msg::MotorCommand>::SharedPtr command_subscriber_;
  };
} // namespace crunchy

int main(int argc, char** argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<crunchy::MotorNode>());
  rclcpp::shutdown();

  return 0;
}
