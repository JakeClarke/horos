global loader                   ; the entry symbol for ELF

extern kmain
extern gdtInit
extern kernel_virtual_offset
global page_directory
global page_table_1mb
global page_table_768

MAGIC_NUMBER equ 0x1BADB002     ; define the magic number constant
FLAGS        equ 0x0            ; multiboot flags
CHECKSUM     equ -MAGIC_NUMBER  ; calculate the checksum
                                ; (magic number + checksum + flags should equal 0)
KERNEL_STACK_SIZE equ 4096                  ; size of stack in bytes


section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE
align 4096
page_directory: resb 4096
page_table_768: resb 4096

section .text                   ; start of the text (code) section
align 4                         ; the code must be 4 byte aligned
    dd MAGIC_NUMBER             ; write the magic number to the machine code,
    dd FLAGS                    ; the flags,
    dd CHECKSUM                 ; and the checksum
loader:                         ; the loader label (defined as entry point in linker script)
    
    
    xchg bx, bx
    ; reset page tables
    mov eax, 0x0 ; loop idx
    mov ebx, 0x0 ; current physical offset of the identity page
    .init_pages:
        mov ecx, page_directory ; we are using the space that has been allocated by grub
        sub ecx, kernel_virtual_offset
        ; zero the pd
        mov dword [ecx + (eax * 4)], 0x0
        ; identity page tables
        mov ecx, page_table_768
        sub ecx, kernel_virtual_offset
        mov edx, ebx
        or edx, 3 ; present bit, read/write
        mov [ecx+(eax * 4)],edx
        add ebx, 4096
        ; loop
        inc eax
        cmp eax, 1024
        je .end
        jmp .init_pages
    .end:
    xchg bx, bx
    ; setting the pde for higher half
    mov eax, page_table_768
    sub eax, kernel_virtual_offset
    or eax, 3 ; present bit, read/write
    mov ecx, page_directory
    sub ecx, kernel_virtual_offset
    mov [ecx + (768*4)], eax
    mov [ecx], eax

    ; enabling the pd
    xchg bx, bx
    mov cr3, ecx
    mov eax, cr0
    or eax, 0x80000001
    mov cr0, eax

    ; enter higher half
    mov eax, enter_higher
    jmp eax
enter_higher:
    ; other init
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    call gdtInit
    mov eax, 0xCAFEBABE         ; place the number 0xCAFEBABE in the register eax
    mov [0x000B8000], WORD 0x4128
    call kmain
.loop:
    jmp .loop                   ; loop forever
