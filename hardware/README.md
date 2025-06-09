# target hardware

The target hardware is yours to design.  It just needs to incorporate the SAML21 and botstrap programming connector somewhere.

```
                   Your board
                 .------------------------------------------------.
                 |                                                |
                 |                                                |
                ---.   .------.   cmsis-dap                       |  
                USB|---|SAML21|-----+-----+-----+-----+-----.     |   
                ---'   '------'     |     |     |     |     |     |   
                 |        |SWD    .---.  ---.  ---.  ---. .---.   |   
                ---.      |       |CPU| |CPU| |CPU| |CPU| |CPU|   |
                 --|------'       |   | |   | |   | |   | |   |   |
                ---'              `---' `---' `---' `---' `---'   |
                 |                     Your CPUs here...          |
                 `------------------------------------------------'
```
# dbu bootstrap

An option would be to put a standard 10-way debug pin header on the target board.  

As this connector is not used in the normal development workflow of the target, this is an example hardware for bootstrapping that saves the cost and real estate of adding the 10-pin header.  

![PCB](https://github.com/brucebiotech/dbu/blob/main/docs/saml21-narrow-dbu-v2.png)

The debugger is connected to a traget using an edge connector on the target's PCB.

![edge](https://github.com/brucebiotech/dbu/blob/main/docs/target-edge-connector.png)

