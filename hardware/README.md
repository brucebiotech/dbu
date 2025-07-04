# target hardware

The target hardware is yours to design.  It just needs to incorporate the SAML21 and botstrap programming connector somewhere, e.g as done in the [schematic](https://kicanvas.org/?github=https%3A%2F%2Fgithub.com%2Fbrucebiotech%2Fdbu%2Fblob%2Fmain%2Fhardware%2Fsaml21-narrow-dbu-v1.kicad_sch) and [PCB](https://kicanvas.org/?github=https%3A%2F%2Fgithub.com%2Fbrucebiotech%2Fdbu%2Fblob%2Fmain%2Fhardware%2Fsaml21-narrow-dbu-v1.kicad_pcb) in the hardware folder.

```
                   Your board
                 .-------------------------------------------------------.
                 |                       Your CPUs here...               |
                 |                                                       |          
                ---.   .------.         cmsis-dap                        |  
                USB|---|SAML21|------+-----+-----+-----+-----+-----.     |   
                ---'   |      |-.    |     |                       |     |   
                 |     `------' |    |0    |1         ...          |n    |   
                 |     SWD|     |  .-+-.  -+-.                   .-+-.   |   
                ---.      |     |  |CPU| |CPU|                   |CPU|   |
                 --|------'     |  |   | |   |                   |   |   |
                ---'            |  `-+-' `-+-'                   `-+-'   |
                 |              |    |     |                       |     |
                 |              `----+-----+-----+-----+-----+-----'     |
                 |                             uarts                     |
                 `-------------------------------------------------------'
```
# dbu bootstrap

An option would be to put a standard 10-way debug pin header on the target board.  

As this connector is not used in the normal development workflow of the target, this is an example hardware for bootstrapping that saves the cost and real estate of adding the 10-pin header. 

The bootstrap dbu is connected to a traget using an edge connector on the target's PCB. The particular details of this connection are detailed as J4 on the KiCad [schematic](https://kicanvas.org/?github=https%3A%2F%2Fgithub.com%2Fbrucebiotech%2Fdbu%2Fblob%2Fmain%2Fhardware%2Fsaml21-narrow-dbu-v1.kicad_sch) and [PCB](https://kicanvas.org/?github=https%3A%2F%2Fgithub.com%2Fbrucebiotech%2Fdbu%2Fblob%2Fmain%2Fhardware%2Fsaml21-narrow-dbu-v1.kicad_pcb) hardware files.

![edge](https://github.com/brucebiotech/dbu/blob/main/docs/target-edge-connector.png)

You then need a second, bootstrap dbu to attach to the dbu on the target, e.g.

[![PCB](https://github.com/brucebiotech/dbu/blob/main/docs/saml21-narrow-dbu-v2.png)](https://kicanvas.org/?github=https%3A%2F%2Fgithub.com%2Fbrucebiotech%2Fdbu%2Fblob%2Fmain%2Fhardware%2Fsaml21-narrow-dbu-v1.kicad_pcb)

Note that this board has a break-away section for the AVX edge connector. Usually you would detach this section and connect the two parts with the 10-pin right angle pin header.


