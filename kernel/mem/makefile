CXXFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-g -std=c++11 -Wall -nostartfiles -nodefaultlibs -pedantic -c

ASFLAGS=-f elf32
CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c -g -o0 -std=c99

OBJ=seg.o seg-asm.o phys_serv.o

AS=nasm

mem.a: $(OBJ)
	$(AR) -r $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

.PHONY: clean

clean:
	rm *.o *.a