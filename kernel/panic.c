#include "panic.h"
#include "display.h"

void panic(const char * msg) {
	fbWriteString("\n!PANIC!\n");
	fbWriteString(msg);
	// do something else. maybe halt?
	__asm("hlt\n");
	while(1) {}
}