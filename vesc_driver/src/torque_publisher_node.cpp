#include <chrono>
#include "ros/ros.h"
#include "std_msgs/Float64.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "torque_publisher");
  ros::NodeHandle n;
  ros::Publisher torque_pub = n.advertise<std_msgs::Float64>("/vesc/commands/motor/torque", 1000);
  ros::Rate loop_rate(10);

  std::chrono::seconds timeout(3);

  std_msgs::Float64 torque_input;
  std::chrono::time_point<std::chrono::system_clock> start{std::chrono::system_clock::now()};
  while (ros::ok())
  {
    torque_input.data = 0.01;
    torque_pub.publish(torque_input);

    ros::spinOnce();

    loop_rate.sleep();
    std::chrono::time_point<std::chrono::system_clock> current{std::chrono::system_clock::now()};
    std::chrono::duration<double> elapsedSeconds{current-start};
    if (elapsedSeconds > timeout)
      break;
  }
  torque_input.data = 0.0;
  torque_pub.publish(torque_input);
  return 0;
}
