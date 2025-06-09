# dbu

This repository contains the software and hardware details for a cmsis-dap compatible ARM debug unit.

Based on [free-dap](https://github.com/ataradov/free-dap), dbu adds the SAML21 as a platform and introducs the capability to connect to multiple target CPU's.  The SAML21 can support up to 6 target CPUs.

Using the dbu comprises adding a SAML21 cpu and USB connector to your targed development board and providing a method of bootstrapping the code into the SAML21.

This repository includes a low-cost edge connector adaptor as a bootstrap option.

```
                Target development board
              .------------------------------------------------.
              |                                                |
              |                                                |          
cmsis-dap    ---.   .------.   cmsis-dap                       |  
hid host     USB|---| DBU  |-----+-----+-----+-----+-----.     |   
adapter      ---'   '------'     |     |     |     |     |     |   
              |        |SWD    .---.  ---.  ---.  ---. .---.   |   
Bootstrap    ---.      |       |CPU| |CPU| |CPU| |CPU| |CPU|   |
programming   --|------'       |   | |   | |   | |   | |   |   |
connector    ---'              `---' `---' `---' `---' `---'   |
              |                     Debug target CPUs          |
              `------------------------------------------------'
		
```

The dbu software also implements cmsis-dap vendor extensions to 
  - control power delivery to the target
  - transport a uart debug message stream to the host debugger

Follow these links for more information including instructions on building the software and hardware.

[Building the software](https://github.com/brucebiotech/dbu/blob/main/software/README.md)

[Building the hardware](https://github.com/brucebiotech/dbu/blob/main/hardware/README.md)
