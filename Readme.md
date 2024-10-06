# CCAM Earth "Hello World"

## About
This repository is meant to serve primarily as a jumping off point for C++ projects built on the CCAM earth module

## Setup
Linux setup
```
git clone git@github.com:garnetgrimm/CCAM-Earth-Init.git
git submodule update --init --recursive
yum install dfu-util arm-none-eabi-gcc-cs arm-none-eabi-newlib

pushd DaisySP
make
popd

pushd libDaisy
make
popd
```