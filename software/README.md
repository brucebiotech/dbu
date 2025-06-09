# Building the dbu firmware

The firmware build uses gnu make and arm-none-eabi-gcc on linux or windows (building on windows requires msys2).

## Get the software

The easiest way to get the software is to clone this repository and goto the software directory.

## Build tools

The build requires gnu make, arm-none-eabi-gcc version 12 or later and arm-none-eabi-objcopy.

These tools should be available in the package manager for you chosen flavour of linux.  On Windows the best way to get these is to [install msys2](https://www.msys2.org/).

The makefile assumes these tools are in the path.

## Building

Select a supported dbu application tagget from the [makefile]().







