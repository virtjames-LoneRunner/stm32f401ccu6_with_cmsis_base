/* Define the end of RAM (Stack Top) */
_estack = 0x20010000;    /* Adjust for your chip's RAM size */

MEMORY
{
    FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 256K
    RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
    /* The Vector Table goes first in FLASH */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector)) 
        . = ALIGN(4);
    } > FLASH

    /* The program code */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .; 
    } > FLASH

    /* Initialized data used by the startup file to copy from FLASH to RAM */
    _sidata = LOADADDR(.data);

    .data : 
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > RAM AT > FLASH

    /* Uninitialized data (zero-initialized) */
    .bss :
    {
        _sbss = .;
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        _ebss = .;
        __bss_end__ = _ebss;
    } > RAM
}
