#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
  ROS_INFO_STREAM("drive_robot() called");
  ball_chaser::DriveToTarget srv;
  srv.request.angular_z = ang_z;
  srv.request.linear_x = lin_x;

  if (client.call(srv)) {
     ROS_INFO("Service called");
  } else {
     ROS_ERROR("Error calling Service");
  }
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    ROS_INFO_STREAM("process_image_callback() called");
    int white_pixel = 255;
    int red_pixel = 0;
    int green_pixel = 0;
    int blue_pixel = 0;
    int img_size = img.height * img.width * 3;
    bool ball_found = false;
    int white_pixel_xlocation = 0;
    float white_pixel_xlocation_ratio = 0; 

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera

    for (int i = 0; i < (img_size - 2); i = i + 3) {
  	red_pixel = img.data[i];
	green_pixel = img.data[i+1];
	blue_pixel = img.data[i+2];
	//check if red, green, and blue pixels match white's 255 value
	if((red_pixel == white_pixel) && (green_pixel == white_pixel) && (blue_pixel == white_pixel)) {
		//white pixel found. Find the X value of the pixel to move the robot in the right direction
		ROS_INFO_STREAM("White pixel found");
		white_pixel_xlocation = i % img.width;
		ROS_INFO_STREAM("White pixel x location: " << white_pixel_xlocation);
		ball_found = true;
		break;		
	}
    }
    if (!ball_found){
        //stop the robot
	ROS_INFO("Ball not found. Stopping robot");
	drive_robot(0, 0);
    } else {
	if(white_pixel_xlocation < (img.width/3)){
		ROS_INFO_STREAM("Turning left");
		drive_robot(0, 0.5);
    	}   else if(white_pixel_xlocation > 2*(img.width/3)) {
		ROS_INFO_STREAM("Turning right");
		drive_robot(0, -0.5);
    	}   else {
		ROS_INFO_STREAM("Driving forward");
		drive_robot(0.5, 0);
    	}
    }
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
