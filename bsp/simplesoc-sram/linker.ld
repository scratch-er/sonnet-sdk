ENTRY(_start)
MEMORY
{
    RAM (xrw) : ORIGIN = 0x80000000, LENGTH = 64K
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
    } >RAM
    .data :
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
    .bss :
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
    .heap :
    {
        . = ALIGN(4);
        _heap_start = .;
    } >RAM
    .stack (NOLOAD) :
    {
        . = ALIGN(4);
        . = . + 4K;
        . = ALIGN(4);
        _heap_end = .;
        _stack_top = .;
    } >RAM
}
