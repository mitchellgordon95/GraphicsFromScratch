#!/bin/bash
[ -z "`dpkg -l | grep libarmadillo-dev`" ] && sudo apt-get install libarmadillo-dev
[ -z "`dpkg -l | grep libarmadillo3`" ] && sudo apt-get install libarmadillo3
[ -z "`dpkg -l | grep libblas3`" ] && sudo apt-get install libblas3
[ -z "`dpkg -l | grep libblas-dev`" ] && sudo apt-get install libblas-dev
[ -z "`dpkg -l | grep libopenblas-dev`" ] && sudo apt-get install libopenblas-dev
[ -z "`dpkg -l | grep liblapack-dev`" ] && sudo apt-get install liblapack-dev
[ -z "`dpkg -l | grep libboost-math-dev`" ] && sudo apt-get install libboost-math-dev
exit 0
