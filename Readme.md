# CCAM Earth "Hello World"

## About
This repository is meant to serve primarily as a jumping off point for C++ projects built on the CCAM earth module. NOTE: I am running on Fedora linux, the steps will likely be fairly different on Mac/Windows.

## Setup
```
git clone git@github.com:garnetgrimm/CCAM-Earth-Init.git --recurse-submodules

cd CCAM-Earth-init

yum install dfu-util arm-none-eabi-gcc-cs arm-none-eabi-newlib

make
```

## Flash
I set APP_TYPE=BOOT_SRAM in Makefile, which allows us to use a number of bells and whistles (like print statements for example). This means we have to first load the bootloader program onto the board, and then flash our image on top.
```
# upload bootloader
make program-boot

# build the code
make

# flash code to board
make program-dfu
```

## Debug
After you plug in the board, check `sudo dmesg | tail` to determine the serail port number. Then you can use screen to monitor the device.
```
sudo screen /dev/ttyACM0 115200
```
Note that the program will not start running until you connect, so if you do not plan on using the serial monitor it
it probably a good idea to remove that line entirely.

