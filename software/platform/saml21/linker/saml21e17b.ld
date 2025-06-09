
MEMORY
{
  flash (rx) : ORIGIN = 0x00000000, LENGTH = 128k
  ram   (rw) : ORIGIN = 0x20000000, LENGTH = 16k
}

__top_flash = 0x20000;
__top_ram = 0x20000000 + 0x4000;

ENTRY(irq_handler_reset)

SECTIONS
{
  .text (READONLY) :
  {
    FILL(0xff)
    KEEP(*(.vectors))
	*(.text)           /* .text sections (code) */
	*(.text*)          /* .text* sections (code) */
	*(.glue_7)         /* glue arm to thumb code */
	*(.glue_7t)        /* glue thumb to arm code */
	*(.eh_frame)
    *(.rodata)
    *(.rodata.*)
    . = ALIGN(4);
  } > flash

  . = ALIGN(4);
  _etext = .;


  .data : ALIGN(4)
  {
    FILL(0xff)
    _data = .;
    *(vtable)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } > ram AT> flash

  .bss : ALIGN(4)
  {
    _bss = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
    PROVIDE(_end = .);
  } > ram

	.ARM.extab (READONLY)  : {
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } >flash
  
  PROVIDE(_stack_top = __top_ram - 0);
}
