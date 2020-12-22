#include "display.h"
#include "panic.h"
#include "mem/phys_serv.h"
#include "log/printf.h"

using namespace horos;

extern "C" void kmain() {
	display::fbClear();
	display::fbMvCursor(0, 0);
	mem::init(32*1024*1024);
	logging::info("a: {} world", "hello1");
	logging::info("b: {} woorld {}", "hello2", 0);
	logging::info("b: {} wiorld {}", "hello3", -142);

	display::fbWriteString("Hello Kernel!\nLook it supports 2 lines of text.\n A really really really really really really really really really really really long line of text");
	panic("end of kmain()");
}