# Software User Guide

dbu provides the functionality of a standard cmsis-dap debug unit.

The caveat on this is that this is only possible on the currently selected swd port.

This is because none of the existing tools, [e.g. openOCD](#using-dbu-with-openocd) support the commands to switch the active SWD port.

dbu will power-up with port 0 active.  In order to connect debug tools to dbu on ports other than port 0, you need to use a separate port-switch application. 

## dbu specific fork of EDBG

The dbu port of [EDGB](https://github.com/brucebiotech/edbg) provides additional dbu specific command options.
```
   -get
   -set n
   -power on|off|status
```

(The uart "printf" port functions in dbu are not yet supported by edbg.)

### Examples

A get port command:
```
   edbg -get -s 0 
```
will print the currently selected port for the dbu with serial number 0.

If the cmsis-dap dbug unit with serial number 0 is not a dbu then this command fails with an error message.

A set port command:
```
   edbg -set 3 -s 0 
```
will set the active swd port on dbu 0 to be port 3.

### get edbg

To get the dbu specific edbg command you will need to clone [this repository](https://github.com/brucebiotech/edbg) and follow its build instructions.

These are very simple; simply run make all and you will get a small binary, called edbg.

## Using dbu with OpenOCD

Just ensure that OpenOCD is configured to use the cmsis-dap adapter driver; e.e include the following in your openocd.cfg.

```
adapter driver  cmsis-dap
```
