#!/bin/sh
# 
# File:   run.sh
# Author: Zexi Liu
#
# Created on Jun 10, 2015, 10:11:42 PM
#
set -e

echo "CLEANING..."
rm -f -r build
echo "CLEAN SUCCESSFUL!" 

mkdir -p build

echo "Compiling wordCount.cpp..."
g++ -c -O2 -std=c++11 -MMD -MP -MF "./build/wordCount.o.d" -o ./build/wordCount.o ./src/wordCount.cpp
g++ -o ./build/wordCount ./build/wordCount.o

echo "Compiling runningMedian.cpp..."
g++ -c -O2 -std=c++11 -MMD -MP -MF "./build/runningMedian.o.d" -o ./build/runningMedian.o ./src/runningMedian.cpp
g++ -o ./build/runningMedian ./build/runningMedian.o

echo "Clean object files..."
rm ./build/*.o ./build/*.d

echo "Running wordCount..."
./build/wordCount

echo "Running runningMedian..."
./build/runningMedian
