#ifndef _H_KERNEL_PANIC
#define _H_KERNEL_PANIC

namespace horos {
	void panic(const char *);
}

#define BREAK_PT __asm("XCHG %BX, %BX\n")

#define str(x) str2(x)
#define str2(x) #x

#define ASSERT(...) if(!(__VA_ARGS__)) { \
 BREAK_PT; \
 horos::panic("BUGON: " __FILE__ ":" str(__LINE__) ": " str(__VA_ARGS__));\
}\


#endif