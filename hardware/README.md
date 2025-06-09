# dbu embedded on a target

```
         Target development board
      .------------------------------------------------.
      |                                                |
      |                                                |          
     ---.   .------.   cmsis-dap over SWD IO pins      |  
     USB|---| DBU  |-----+-----+-----+-----+-----.     |   
     ---'   '------'     |     |     |     |     |     |   
      |                .---.  ---.  ---.  ---. .---.   |   
      |                |CPU| |CPU| |CPU| |CPU| |CPU|   |
      | ARM Cortex-M   |   | |   | |   | |   | |   |   |
      | CPUs           `---' `---' `---' `---' `---'   |
      |                                                |
      `------------------------------------------------'
```
# dbu bootstrap

![PCB](https://github.com/brucebiotech/dbu/blob/main/docs/saml21-narrow-dbu-v2.png)

The debugger is connected to a traget using an edge connector on the target's PCB.

![edge](https://github.com/brucebiotech/dbu/blob/main/docs/target-edge-connector.png)

