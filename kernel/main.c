#include "display.h"
#include "panic.h"


void kmain() {
	fbClear();
	fbMvCursor(0, 0);
	fbWriteString("Hello Kernel!\nLook it supports 2 lines of text.\n A really really really really really really really really really really really long line of text");
	panic("end of kmain()");
}