# Robotic_toy

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://github.com/Akshaybj0221/Robotic_toy/blob/master/LICENSE)
[![Build Status](https://travis-ci.org/Akshaybj0221/Robotic_toy.svg?branch=master)](https://travis-ci.org/Akshaybj0221/Robotic_toy)

Robotic_toy: A Robot Toy which moves in a polygon pattern as commanded by the user

This repository showcases the ROS package for the Robotic toy project.

---

## SIP Process:

The SIP for the project can be found [here](https://docs.google.com/spreadsheets/d/1jLItNdomgrqtsU7UJ7i3CasUFsOEN9d-EHtjViunuMg/edit?usp=sharing).

The Planning notes for the project can be found [here](https://docs.google.com/document/d/1cuM1NgHEFEkOeJMYtaNpIpAXfJ_u0YdG9ozSTAGEVLY/edit?usp=sharing).

The link to the defect log, time log, product backlog, and release backlog table are as follows:

[Product Backlog](https://docs.google.com/spreadsheets/d/1XhrbZjeozz02wAhwiE5d25f-5yS15jGHrX1-cPPEQfs/edit?usp=sharing).

[Release Backlog Table](https://docs.google.com/spreadsheets/d/1TbC_kTvKK2MRH9XEX8YbNeR_NHrXO2tIK1uxxjgT04Y/edit?usp=sharing).

[Defect Log](https://docs.google.com/spreadsheets/d/1sQbnvWU1MZIwgt0YRekxqZq24jqrIhIC-pB-LOpDczo/edit?usp=sharing)

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

## First sprint update
Things done in the first sprint:

	* Install all the packages necessary to run Turtlebot in Gazebo and rviz
	* Test the working of the necessary packages and check the data being received from the robot
	* Explore various topics and packages that can be used in this project
	* Create initial UML diagrams
	* Setup Travis for the repository
	* Create SIP log

## Second sprint update 
Things done in second sprint:

	* Create a custom gazebo world that can be used a testing rig to test the performance of the algorithm 
	* Create stub implementation of the class 
	* Create Working test cases for the classes 
	* Search how to input parameter in form of a service from user 
	* Make a service for taking input from the user 
	* Make a launch file to open Gazebo world, rviz and script	
	* Control the Turtlebot using commandline as well as dummy script.
	* Create planning notes and update SIP tasklog as well as release backlog. 

## Results

The software is very effective and fast in tracking any tagging motion simultaneously.
Its funtionality has been tested on multiple test videos and software has a success rate of 98%.

The working output of the software can be seen in the output folder of the repository or the link below:
https://github.com/Akshaybj0221/ENPM808X_Midterm.git


### Miscellaneous Instructions

1. cpplint and cppcheck output files are added in the *results* folder.

2. screenshots are added in the *output* folder.

3. *msg* folder is to be ignored as it has nothing relevant to the project.

4. *config* folder contains the custom log file.

