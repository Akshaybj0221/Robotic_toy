### Robotic_toy

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://github.com/Akshaybj0221/Robotic_toy/blob/master/LICENSE)
[![Build Status](https://travis-ci.org/Akshaybj0221/Robotic_toy.svg?branch=master)](https://travis-ci.org/Akshaybj0221/Robotic_toy)

Robotic_toy: A Robot Toy which moves in a polygon pattern as commanded by the user

![Turtlebot moving in Rviz](https://github.com/Akshaybj0221/Robotic_toy/blob/master/output/Screenshot%20(226).png)

The project is envisioned to be a robotic toy which can help kids to learn elementary level things such as shapes, numbers and alphabets, etc. in an interactive way. The robot moves in a trajectory on the floor that corresponds to a polygonal shape.
This project focuses on shape teaching component of the robot which will take the input from users (kids) and will move in the desired shaped path. The input given to the robot would be number of sides. And according to that, the robot will calculate what the shape should be and it would move in a trajectory of that specified shape, completing the loop. 

The developed system is capable of:
* taking input from the user
* calculating what a shape must be just by knowing the number of sides of tha polygon 
* calculating the trajectory of the shape and
* Moving in that trajectory completing a loop

The project was programmed in the C++ programming language and uses with C++ 11/14 features with ephasis given to Object Oriented Programming principles. The code follows the Google C++ Styleguide with cpplint validation. Cppcheck was also used for static code analysis. This project followed Test-driven Development to guide implementation and uses unit tests to test the code coverage written using Google Test framework. The entire code was written and debugged using the Eclipse IDE. The code follows doxygen-formatted comments to aid doxygen documentation.

The project was completed in about two weeks time.  This project was implemented by following the Solo Iterative Process(SIP). This included the creation of a product backlog using the requirements and ordering them in the order of their priority. Finally, the software was developed over two sprints which were of varying duration. The first week focused on the planning and design of the project inculding the initial UML diagrams. The second week involved the programming of the actual module and the development of a video presentation explaining the entire project (links of planning stubs in the SIP Process section).


This repository showcases the ROS package for the Robotic toy project.

---

## SIP Process:

The SIP for the project can be found [here](https://docs.google.com/spreadsheets/d/1jLItNdomgrqtsU7UJ7i3CasUFsOEN9d-EHtjViunuMg/edit?usp=sharing).

The Planning notes for the project can be found [here](https://docs.google.com/document/d/1cuM1NgHEFEkOeJMYtaNpIpAXfJ_u0YdG9ozSTAGEVLY/edit?usp=sharing).

The link to the defect log, time log, product backlog, and release backlog table are as follows:

[Product Backlog](https://docs.google.com/spreadsheets/d/1XhrbZjeozz02wAhwiE5d25f-5yS15jGHrX1-cPPEQfs/edit?usp=sharing).

[Release Backlog Table](https://docs.google.com/spreadsheets/d/1TbC_kTvKK2MRH9XEX8YbNeR_NHrXO2tIK1uxxjgT04Y/edit?usp=sharing).

[Defect Log](https://docs.google.com/spreadsheets/d/1sQbnvWU1MZIwgt0YRekxqZq24jqrIhIC-pB-LOpDczo/edit?usp=sharing)

[Time Log](https://docs.google.com/spreadsheets/d/1VeWo3rjCu81KB_xSVg6yemmHTXDCDP8UWNnFYt2IB9k/edit?usp=sharing)

Link to the video presentation uploaded on youtube: 
[Presentation Video](https://www.youtube.com/watch?v=9u4PGOxRDGw)
[Live Package Run](https://www.youtube.com/watch?v=-qi4Jy60qDk)


## Example outputs

![Turtlebot moving in Rviz](https://github.com/Akshaybj0221/Robotic_toy/blob/master/output/Screenshot%20(226).png)

![Rviz and Turtlebot launching together](https://github.com/Akshaybj0221/Robotic_toy/blob/master/output/Screenshot%20(230).png)


## About the Developer

I am Akshay Bajaj. I am a Research assistant under Dr. Elisabeth Smela in Mechanical Department, UMD and currently pursing my Masters in Robotics at University of Maryland - College Park. I am also a Software Developer in Cadeo groups and I hold a Bachelors degree in Computer Science Engineer from, IIST, India. 

Some of my previous work can be found at [here](https://github.com/Akshaybj0221).


## Dependencies/Prerequiesites 
The dependencies of this repository are:

```
* Ubuntu 16.04
* ROS Kinetic Kame
* TurtleBot
* Gazebo
```

## Building the code

The code can be built by cloning the repository and executing following steps:
```
<home>$ cd <workspace>/src
<workspace>/src$ git clone https://github.com/Akshaybj0221/Robotic_toy.git
<workspace>/src$ cd ..
<workspace>$ catkin_make 
```

If you wish to run this code in an existing catkin workspace:
```
cd ~/catkin_ws/
source devel/setup.bash
cd src/
git clone --recursive https://github.com/Akshaybj0221/Robotic_toy.git
cd ..
catkin_make
```
## Running the Demo Using Launch File
To run the demo we need to run a launch files which is in the directory Robotic_toy/launch. First launch file loads the Gazebo and rviz simulators along with a client service node *input* to take in input from the user (Number of sides). 

Once, the launch file is run, now the user will have to call a node *free_space_navigation_node* which enables the robot to calculate the trajectory and move on it.

The instructions to use it are as follows:

After following the build instructions Open a new terminal, and do as follows:
```
cd ~/catkin_ws/
source devel/setup.bash
roslaunch toy_robot toy_robot.launch 
```
This will load the turtlebot in the gazebo world and in rviz. It will also open an *xterm* console which will display the service call and its behavior. Now to run trajectory node, in a new terminal:
```
cd ~/catkin_ws/
source devel/setup.bash
rosrun toy_robot free_space_navigation_node <no_of_sides_you_want_to_enter> 
```
NOTE: THE SIDES SHOULD BE MORE THAN 2 OR ELSE IT WILL GIVE UNEXPECTED BEHAVIOR!

This will start the toy_robot package and make the robot move in the corresponding shape in both rviz and Gazebo.

# Example: 
This will make a square shaped trajrctory of the robot: 
```
rosrun toy_robot free_space_navigation_node 4
```

### Recording, Inspecting and Playing back bag files
To enable bag file recording of all topics except camera. While launching the demo, in a new terminal:
```
cd ~/catkin_ws/
source devel/setup.bash
roslaunch toy_robot toy_robot.launch rec:=1
```
This will save a bag file in the results folder of the package.

To inspect the bag file, In a new terminal:
```
cd ~/catkin_ws/
source devel/setup.bash
cd src/Roomba_robot/results
rosbag info recording.bag
```
or instead of the last command use:
```
rosbag info recTalker.bag
```

To replay the bag file, first run rosmaster from a terminal:
```
roscore
```
Now, from the results folder run the following command in a new terminal:
```
cd ~/catkin_ws/
source devel/setup.bash
cd src/Roomba_robot/results
rosbag play recTalker.bag
```

## Running Rostest
To run rostest, in a new terminal:
```
cd ~/catkin_ws/
source devel/setup.bash
cd build/
make run_tests
```
### Code Coverage Output Using lcov

* Unable to show code coverage using coveralls. 
* When gazebo initializes it  throws some errors of missing plugins and thi followin error:
  SpawnModel: Failure - model name mobile_base already exist.
  However, these make no difference to the demo. The latter error maybe resolved once ros answers is back online.

### Generating Doxygen Documentation

To install doxygen run the following command: 
```
sudo apt-get install doxygen
```

Now from your cloned directory, run the following command:

```
doxygen Docs
```

Doxygen files will be generated to /docs folder

To view them in a browser:
```
cd docs
cd html
firefox index.html
```

Else, can use *doxywizard* and use the GUI console. 

## Results

The software is very effective and fast in tracking any tagging motion simultaneously.
Its funtionality has been tested on multiple test videos and software has a success rate of 98%.

The working output of the software can be seen in the output folder of the repository or the link below:
https://github.com/Akshaybj0221/ENPM808X_Midterm.git


### Miscellaneous Instructions

1. cpplint and cppcheck output files are added in the *results* folder.

2. screenshots are added in the *output* folder.

3. *msg* folder is to be ignored as it has nothing relevant to the project.

4. *config* folder contains the custom rviz file.


## First sprint update (1,2,3)
Things done in the first sprint:
# First Sub-Tasks
	* Install all the packages necessary to run Turtlebot in Gazebo and rviz
	* Test the working of the necessary packages and check the data being received from the robot
	* Explore various topics and packages that can be used in this project
	* Create initial UML diagrams
	* Setup Travis for the repository
	* Create SIP log and other log files.

Things done in second sprint:
# Second sub-tasks 
 
	* Create stub implementation of the class 
	* Create methods and function definitions
	* Create Working test cases for the classes 
	* Control the Turtlebot using commandline as well as dummy script.
	* Create planning notes and update SIP tasklog as well as release backlog.
	* Unit testing and debugging
	* Coverage testing

Things done in third sprint:
# Third sub-tasks 

	* Make a launch file to open Gazebo world, rviz and script	
	* Make a topic subscriber (odometry)
	* Make a topic publisher (velocity)
	* Create planning notes and update SIP tasklog as well as release backlog.
	* Unit testing and extensive debugging


## Second sprint update (4,5,6)
Things done in fourth sprint:
# First sub-tasks 

	* Search how to input parameter in form of a service from user 
	* Make a service for taking input from the user 
	* Make a new script which make a ros service server
	* Service definition
	* Unit testing and extensive debugging

Things done in fifth sprint:
# Second sub-tasks 

	* Create a custom gazebo world that can be used a testing rig to test the performance of the algorithm
	* Service launch parameters included in launch file
	* Create a rviz configuration file
	* Create Gazebo and rviz launch file
	* Create Gazebo world

Things done in sixth sprint:
# Third sub-tasks 

	* Create a custom callback funtion
	* Create main function calling stubs
	* Create logic for no. of sides to angle conversion
	* Unit testing and debugging
	* Coverage testing

## Third sprint update (7,8,9)
Things done in seventh sprint:
# First sub-tasks 

	* Add doxygen style comments to every script
	* Remove cppling errors and save output
	* Remove cppckeck errors and save output
	* Create doxygen files for the software
	* Cmakelists and package.xml dependencies
	* Unit testing and debugging
	* Coverage testing and Integration testing

Things done in seventh sprint:
# Second sub-tasks 

	* Create screen casts of output 
	* Complete Readme.md
	* Create screenshots of output 
	* Create Presentation
	* Create youtube video and upload




