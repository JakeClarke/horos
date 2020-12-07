. = 0x00100000;          /* the code should be loaded at 1 MB */
. = 0xC0100000;

/* these labels get exported to the code files */
kernel_virtual_start = .;
kernel_virtual_offset = 0xC0000000;
kernel_physical_start = . - kernel_virtual_offset;


SECTIONS {
    .text ALIGN (0x1000) : AT(ADDR(.text)-0xC0000000)  /* align at 4 KB, load at 1MiB */
    {
        *(.text)             /* all text sections from all files */
    }

    .rodata ALIGN (0x1000) : AT(ADDR(.rodata)-0xC0000000)  /* align at 4 KB, load at 1MiB */
    {
        *(.rodata*)          /* all read-only data sections from all files */
    }

    .data ALIGN (0x1000) : AT(ADDR(.data)-0xC0000000) /* align at 4 KB, load at 1MiB */
    {
        *(.data)             /* all data sections from all files */
    }

    .bss ALIGN (0x1000) : AT(ADDR(.bss)-0xC0000000)  /* align at 4 KB, load at 1MiB */
    {
        *(COMMON)            /* all COMMON sections from all files */
        *(.bss)              /* all bss sections from all files */
    }
}

kernel_virtual_end = .;
kernel_virtual_size = kernel_virtual_end - kernel_virtual_start;
kernel_physical_end = . - kernel_virtual_offset;
kernel_physical_size = kernel_physical_end - kernel_physical_start;

loffset = loader - kernel_virtual_offset;

ENTRY(loffset)                /* the name of the entry label */
