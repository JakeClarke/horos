global outb
global inb

section .text
align 4
outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret
inb:
    mov dx, [esp + 4]       ; move the address of the I/O port to the dx register
    in  al, dx              ; read a byte from the I/O port and store it in the al register
    ret                     ; return the read byte