OBJECTS = loader.o io.o display.o main.o panic.o mem/mem.a
CC=gcc
AS=nasm
ASFLAGS=-f elf32
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -g -og -std=c99

CXXFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
    -g -std=c++11 -Wall -nostartfiles -nodefaultlibs -pedantic -c



.PHONY: clean force

kernel.elf: link.ld $(OBJECTS)
	$(LD) $(OBJECTS) -T link.ld -melf_i386 -o kernel.elf

all: kernel.elf

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm *.o kernel.elf
	cd mem && make clean

mem/mem.a: force
	cd mem && make

force:
