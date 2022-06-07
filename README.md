# Udacity's Robotics Software Engineer Nanodegree
#### Course website: [Robotics Software Engineer](www.udacity.com/course/robotics-software-engineer--nd209)
#### Link to the syllabus: https://d20vrrgs8k4bvw.cloudfront.net/documents/en-US/nd209_Robo_syllabus_v2.pdf
There are a total of 5 projects, starting off easy with ROS essentials and building a world in Gazebo, and 
ending with making a mobile robot perform a pickup-dropoff in an unknown map using the ROS navigation stack.

## Projects

### Project 1: Build My World
An introduction to Gazebo: creating models and buildings and populating a world with them. ```world``` files created in this project were used in the subsequent projects.

### Project 2: Go Chase It!
A very basic visual servoing task in which a differential drive mobile robot detects and pursues a ball.

### Project 3: Where Am I
Given a map generated by ```pgm_map_creator```, Adaptive Monte Carlo Localization (also called particle filter localization) is used to localize the robot. As can be seen from the converging yellow markers, only the first few sensor updates are sufficient for the robot to be confident enough of its location relative to the map. 

## To Be Continued...
Unfortunately, I encounted a series of stubborn bugs in Project 3 that prevented me from finishing the project. Despite about 11 hours of debugging, reading forums, and trying 3 different environments, I could not get the PGM map to generate from by Gazebo world file, and after building this PGM file manually, I could not get it to load using roslaunch. As much as I want to continue, I am also aware of the sunk cost fallacy and opportunity cost of spending more time on this. I'm going to work on some other projects, and potentially revisit this in the future when updates to the course and more forum posts may help fix the problems I'm facing

