# dbu

This project provides details on both the software and hardware for dbu, a cmsis-dap tool used for debugging ARM processors.

Based on [free-dap](https://github.com/ataradov/free-dap), dbu adds the SAML21 as a platform and introducs the capability to connect to multiple target CPU's.  A single SAML21 can support up to 6 target CPUs.

## How to use dbu

dbu is a component added to a target development board. 

```
                   Target development board
                 .-------------------------------------------------------.
                 |                       Debug target CPUs               |
                 |                                                       |          
cmsis-dap       ---.   .------.         cmsis-dap swd ports              |  
hid host        USB|---| DBU  |------+-----+-----+-----+-----+-----.     |   
adapter         ---'   |      |-.    |     |     |     |     |     |     |   
                 |     `------' |    |0    |1    |2    |3    |4    |5    |   
                 |     SWD|     |  .-+-.  -+-.  -+-.  -+-. .-+-. .-+-.   |   
bootstrap       ---.      |     |  |CPU| |CPU| |CPU| |CPU| |CPU| |CPU|   |
programming      --|------'     |  |   | |   | |   | |   | |   | |   |   |
connector       ---'            |  `-+-' `-+-' `-+-' `-+-' `-+-' `-+-'   |
                 |              |    |     |     |     |     |     |     |
                 |              `----+-----+-----+-----+-----+-----'     |
                 |                        "printf" uarts                 |
                 |                                                       |
                 `-------------------------------------------------------'
		
```
To use dbu, add a SAML21 CPU and a USB connector to your development board and provide a method of bootstrapping the dbu firmware into the SAML21. (This repository includes a low-cost edge connector based adaptor as a [bootstrap option](https://github.com/brucebiotech/dbu/blob/main/hardware/README.md#dbu-bootstrap).)

## Additional features

The dbu software also implements a cmsis-dap vendor extension to control power delivery to the target.

It also supports the cmsis-dap UART commands to tunnel a uart debug message stream over the cmsis-dap HID interface.  In other words dbu enables support for printf debugging of each target CPU over a single USB connection.

Follow these links for more information including instructions on building the software and hardware.

## The detail

[Building the software](https://github.com/brucebiotech/dbu/blob/main/software/README.md)

[Software user guide](https://github.com/brucebiotech/dbu/blob/main/docs/README.md)

[Building the hardware](https://github.com/brucebiotech/dbu/blob/main/hardware/README.md)
