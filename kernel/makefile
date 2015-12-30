OBJECTS = loader.o display.o main.o
CC=gcc
LD=ld
AS=nasm
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -g -o0 -std=c99

.PHONY: clean 

kernel.elf: link.ld $(OBJECTS)
	$(LD) $(OBJECTS) -T link.ld -melf_i386 -o kernel.elf

all: kernel.elf

loader.o: loader.s
	nasm -f elf32 loader.s

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm *.o kernel.elf