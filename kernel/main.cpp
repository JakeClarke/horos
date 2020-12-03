#include "display.h"
#include "panic.h"
#include "mem/phys_serv.h"

using namespace horos;

extern "C" void kmain() {
	mem::init(32*1024*1024);
	display::fbClear();
	display::fbMvCursor(0, 0);
	display::fbWriteString("Hello Kernel!\nLook it supports 2 lines of text.\n A really really really really really really really really really really really long line of text");
	panic("end of kmain()");
}