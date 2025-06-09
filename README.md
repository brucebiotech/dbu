# dbu
Firmware for a cmsis-dap compatible arm swd debug adapter.

[About](#about-the-dbu)

[Building the software](#make)

[Get DBU hardware](#pcb)


# About the dbu

It is based on [free-dap](https://github.com/ataradov/free-dap).  It adds the saml21 as a platform and also introduces the capability to connect to multiple target CPU's.



It also implements cmsis-dap vendor extensions to 
  - control power delivery to the target
  - transport a uart debug message stream to the host debugger

# PCB

![PCB](https://github.com/brucebiotech/dbu/blob/main/saml21-narrow-dbu-v2.png)

The debugger is connected to a traget using an edge connector on the target's PCB.

![edge](https://github.com/brucebiotech/dbu/blob/main/target-edge-connector.png)

# Make

The firmware build uses gnu make and arm-none-eabi-gcc on linux or windows (building on windows requires msys2).

