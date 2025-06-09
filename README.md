# dbu
Firmware for a cmsis-dap compatible arm swd debug adapter.

It is based on [free-dap](https://github.com/ataradov/free-dap) adding the saml21 as a platform.

It also implements cmsis-dap vendor extensions to 
  - control power delivery to the target
  - and transport a uart debug message stream to the host debugger.

![PCB](https://github.com/brucebiotech/dbu/blob/main/saml21-narrow-dbu-v2.png)

The debugger is connected to a traget using an edge connector on the target's PCB.

![edge](https://github.com/brucebiotech/dbu/blob/main/target-edge-connector.png)
