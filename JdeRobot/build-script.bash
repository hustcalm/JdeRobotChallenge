#!/bin/bash

# Build box
# Distributor ID: Ubuntu
# Description:    Ubuntu 14.04.1 LTS
# Release:    14.04
# Codename:   trusty

# Install Dependencies
sudo aptitude install build-essential libtinyxml-dev libtbb-dev libxml2-dev libqt4-dev pkg-config libprotoc-dev libfreeimage-dev libprotobuf-dev protobuf-compiler libboost-all-dev  freeglut3-dev cmake libogre-dev libtar-dev libcurl4-openssl-dev libcegui-mk2-dev libswscale-dev libavformat-dev libavcodec-dev

sudo apt-get install ice35-slice ice35-translators libusb-1.0-0 libusb-1.0-0-dev libcwiid-dev libv4l-dev

sudo apt-get install libxml++2.6-2 libxml++2.6-dev

sudo apt-get install  libgtk2.0-dev libgtkmm-2.4-dev libglademm-2.4-dev libgnomecanvas2-dev libgnomecanvasmm-2.6-dev libgtkglextmm-x11-1.2-dev libgtkgl2.0-1 libgtkgl2.0-dev

# Get source code
git clone https://github.com/RoboticsURJC/JdeRobot

# Build
cd JdeRobot
./clean_repository
cmake .
make
