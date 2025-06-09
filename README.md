# dbu
Firmware for a cmsis-dap compatible arm swd debug adapter.

[About](#what-is-a-dbu)

[Building the software](#make)

[Get DBU hardware](#pcb)


# What is a dbu

It is based on [free-dap](https://github.com/ataradov/free-dap) adding the saml21 as a platform.

It also implements cmsis-dap vendor extensions to 
  - control power delivery to the target
  - and transport a uart debug message stream to the host debugger.

# PCB

![PCB](https://github.com/brucebiotech/dbu/blob/main/saml21-narrow-dbu-v2.png)

The debugger is connected to a traget using an edge connector on the target's PCB.

![edge](https://github.com/brucebiotech/dbu/blob/main/target-edge-connector.png)

# Make

The firmware used gnu make and arm-none-eabi-gcc on linux or as provided by msys2 on windows.

