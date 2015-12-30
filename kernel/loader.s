global loader                   ; the entry symbol for ELF
global outb

extern kmain

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
                                ; (magic number + checksum + flags should equal 0)
KERNEL_STACK_SIZE equ 4096                  ; size of stack in bytes


section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .text                   ; start of the text (code) section
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd FLAGS                    ; the flags,
    dd CHECKSUM                 ; and the checksum
loader:                         ; the loader label (defined as entry point in linker script)
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    mov eax, 0xCAFEBABE         ; place the number 0xCAFEBABE in the register eax
    mov [0x000B8000], WORD 0x4128
    call kmain
.loop:
    jmp .loop                   ; loop forever
outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al,
    ret