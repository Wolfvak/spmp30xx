OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(vectors)

MEMORY {
    RAM (RWX) : ORIGIN = 0x24C00000, LENGTH = 4M
}

SECTIONS {
    .text : ALIGN(4) {
        __text_s = .;
        *(.text.vectors)
        *(.text)
        *(.text*)
        __text_e = .;
    } >RAM

    .data : ALIGN(4) {
        __data_s = .;
        *(.data)
        *(.data*)
        __data_e = .;
    } >RAM

    .rodata : ALIGN(4) {
        __rodata_s = .;
        *(.rodata)
        *(.rodata*)
        __rodata_e = .;
    } >RAM

    .bss (NOLOAD) : ALIGN(4) {
        __bss_s = .;
        *(.bss)
        *(.bss*)
        __bss_e = .;
    } >RAM

    . = ALIGN(4096);
    __end__ = .;

    __heap_start = .;
    __heap_end   = ORIGIN(RAM) + LENGTH(RAM);
}    
