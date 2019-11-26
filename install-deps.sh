#!/bin/bash

sudo apt-get update
sudo apt-get remove --auto-remove gcc
sudo apt-get remove --auto-remove g++
sudo add-apt-repository ppa:ubuntu-toolchain-r/test && sudo apt-get update && sudo apt-get install gcc-8 g++-8
sudo add-apt-repository ppa:mhier/libboost-latest && sudo apt update &&sudo apt install libboost1.67-dev
sudo apt-get install libssl-dev cmake g++
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 800 --slave /usr/bin/g++ g++ /usr/bin/g++-8
mkdir /third_party && cd /third_party
git clone https://github.com/microsoft/cpprestsdk.git
cd /third_party/cpprestsdk
git submodule update --init
cmake .
make -j4
sudo make  install
cd /third_party
git clone https://github.com/jbeder/yaml-cpp.git
cd /third_party/yaml-cpp
cmake .
make -j4
sudo make DESTDIR=/usr/local/lib64 install