#ifndef _H_DISPAY
#define _H_DISPAY

void fbWrite(const char * d, const unsigned int len);

void fbWriteString(const char *d);

void fbWriteCell(unsigned int i, char c, unsigned char fg, unsigned char bg);

void fbClear();

void fbMvCursor(const unsigned char x, const unsigned char y);

#endif