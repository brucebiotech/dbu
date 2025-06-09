# dbu
Firmware for a cmsis-dap compatible arm swd debug adapter.

[About](#about-the-dbu)

[Building the software](https://github.com/brucebiotech/dbu/blob/main/software/README.md)

[dbu hardware](https://github.com/brucebiotech/dbu/blob/main/hardware/README.md)


# About the dbu

It is based on [free-dap](https://github.com/ataradov/free-dap) adding the saml21 as a platform and introducing the capability to connect to multiple target CPU's.



It also implements cmsis-dap vendor extensions to 
  - control power delivery to the target
  - transport a uart debug message stream to the host debugger

