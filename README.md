# dbu

Software and hardware for a cmsis-dap compatible ARM swd debug unit.


It is based on [free-dap](https://github.com/ataradov/free-dap) adding the saml21 as a platform and introducing the capability to connect to multiple target CPU's.

It also implements cmsis-dap vendor extensions to 
  - control power delivery to the target
  - transport a uart debug message stream to the host debugger

[Building the software](https://github.com/brucebiotech/dbu/blob/main/software/README.md)

[Building the hardware](https://github.com/brucebiotech/dbu/blob/main/hardware/README.md)
