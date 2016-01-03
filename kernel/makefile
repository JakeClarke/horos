OBJECTS = loader.o io.o display.o main.o panic.o
CC=gcc
AS=nasm
ASFLAGS=-f elf32
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -g -og -std=c99

.PHONY: clean 

kernel.elf: link.ld $(OBJECTS)
	$(LD) $(OBJECTS) -T link.ld -melf_i386 -o kernel.elf

all: kernel.elf

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm *.o kernel.elf