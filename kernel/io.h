#ifndef _H_KERNEL_IO
#define _H_KERNEL_IO


void outb(const short port, const char data);

unsigned char inb(const short port);

#endif