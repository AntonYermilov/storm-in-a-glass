#!/bin/bash

mkdir -p build
cd build
cmake ..
make
mv storm-in-a-glass ../.
cd ..
rm -rf build
