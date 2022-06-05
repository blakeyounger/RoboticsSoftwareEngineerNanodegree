#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"
#include <string>

//TODO: Include the ball_chaser "DriveToTarget" header file

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
{
  //Instantiate a Twist motor_command
  geometry_msgs::Twist motor_command;

  motor_command.linear.x = req.linear_x;
  motor_command.angular.z = req.angular_z;
  
  //Publish the commands
  motor_command_publisher.publish(motor_command);
  
  //feedback message
  res.msg_feedback = "Published linear_x: " + std::to_string(motor_command.linear.x) + "\n Published angular_z: " + std::to_string(motor_command.angular.z) + "\n";
  ROS_INFO_STREAM(res.msg_feedback);
  
  return true;
}




int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function

    // TODO: Delete the loop, move the code to the inside of the callback function and make the necessary changes to publish the requested velocities instead of constant values
    // Service with a handle_drive_request callback function (called when service request is received)
    ros::ServiceServer server = n.advertiseService("/ball_chaser/command_robot", handle_drive_request);

    // TODO: Handle ROS communication events
    ros::spin();

    return 0;
}
