#include "display.h"


void kmain() {
	fbClear();
	fbWriteString("Hello Kernel!\nLook it supports 2 lines of text.\n A really really really really really really really really really really really long line of text");
}