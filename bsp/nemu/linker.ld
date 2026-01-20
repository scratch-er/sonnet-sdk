ENTRY(_start)
MEMORY
{
    RAM (xrw) : ORIGIN = 0x80000000, LENGTH = 128M
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
        . = ALIGN(4);
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
    .stack :
    {
        _stack_top = ALIGN(0x1000);
        . = _stack_top + 0x8000;
        _stack_pointer = .;
        end = .;
        _end = .;
    } >RAM
    .heap :
    {
        . = ALIGN(4);
        _heap_start = .;
    } >RAM
}
