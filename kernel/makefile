kernel.elf: link.ld loader.o
	ld -T link.ld -melf_i386 loader.o -o kernel.elf

loader.o: loader.s
	nasm -f elf32 loader.s

.PHONY: clean
clean:
	rm *.o kernel.elf