ENTRY(_start)
MEMORY
{
    ROM (rx) : ORIGIN = 0x30000000, LENGTH = 32K
    RAM (xrw) : ORIGIN = 0x80000000, LENGTH = 32K
}
SECTIONS {
    .text :
    {
        . = ALIGN(4);
        *(.startup)
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        *(.srodata)
        *(.srodata*)
        . = ALIGN(4);
        _etext = .;
        _sidata = _etext;
    } >ROM
    .data : AT ( _sidata )
    {
        . = ALIGN(4);
        _sdata = .;
        _ram_start = .;
        *(.data)
        *(.data*)
        *(.sdata)
        *(.sdata*)
        . = ALIGN(4);
        _edata = .;
    } >RAM
    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(.sbss)
        *(.sbss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >RAM
    .heap (NOLOAD) :
    {
        _heap_start = .;
        . = ORIGIN(RAM) + LENGTH(RAM) - 4K;
        . = ALIGN(4);
        _heap_end = .;
    } >RAM
    .stack (NOLOAD) :
    {
        _stack_top = .;
        . = ALIGN(4);
        . = . + 4K;
        . = ALIGN(4);
        _stack_pointer = .;
    } >RAM
}
