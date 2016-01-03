#include "panic.h"
#include "display.h"

void horos::panic(const char * msg) {
	display::fbWriteString("\n!PANIC!\n");
	display::fbWriteString(msg);
	// do something else. maybe halt?
	__asm("hlt\n");
	while(true) {}
}