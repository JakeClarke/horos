#ifndef _H_KERNEL_IO
#define _H_KERNEL_IO

#ifdef __cplusplus
extern "C" {
#endif

void outb(const short port, const char data);

unsigned char inb(const short port);

#ifdef __cplusplus
}
#endif

#endif