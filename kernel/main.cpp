#include "display.h"
#include "panic.h"

using namespace horos;

extern "C" void kmain() {
	display::fbClear();
	display::fbMvCursor(0, 0);
	display::fbWriteString("Hello Kernel!\nLook it supports 2 lines of text.\n A really really really really really really really really really really really long line of text");
	panic("end of kmain()");
}