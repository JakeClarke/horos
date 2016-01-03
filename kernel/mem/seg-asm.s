global selectSeg
global setGDT
global reloadSeg

section .text
align 4
selectSeg:
	mov cs, [esp + 2]
	mov ds, [esp + 4]
	mov ss, [esp + 8]
	ret

reloadSeg:
	ret

gdtr:
	DW 0 ; Limit
	DD 0 ; Base
setGDT:
	mov eax, [esp + 4]
	mov [gdtr + 2], eax
	mov ax, [esp + 8]
	mov [gdtr], ax
	lgdt [gdtr]
	jmp 0x08:.reload_CS
.reload_CS:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret
