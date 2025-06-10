# Building the dbu firmware

The firmware build uses gnu make and arm-none-eabi-gcc on linux or windows (building on windows requires msys2).

## Get the software

The easiest way to get the software is to clone this repository and goto the software directory.

## Build tools

The build requires gnu make, arm-none-eabi-gcc version 12 or later and arm-none-eabi-objcopy.

These tools should be available in the package manager for you chosen flavour of linux.  On Windows the best way to get these is to [install msys2](https://www.msys2.org/).

The makefile assumes these tools are in the path.

## Building

Select a supported dbu application name from the [makefile](https://github.com/brucebiotech/dbu/blob/main/software/platform/saml21/build/makefile).

Then use the command

```
make APPLICATION_NAME=<chosen appliction name>
```

This will generate a firmware binary dbu.elf in the application build directory ./build/<app name/dbu.elf.

The next step is to load this firmware into the SAML21.

## Flash firmware

Unfortunately there is no magic solution here.  You will need to use your normal default flash programming tool.

As a suggestion [EDGB](https://github.com/brucebiotech/edbg) is an easy to use cmsis-dap programmer which supports the SAML21.  This particular fork of EDBG als implements some additional functions specific to dbu described [here]().






