#ifndef _H_DISPAY
#define _H_DISPAY

void fbWrite(const char * d, const unsigned int len);

void fbWriteString(const char *d);

struct FbCell {
	unsigned char c;
	unsigned char fg : 4;
	unsigned char bg : 4;
};

void fbWriteCell(unsigned int i, struct FbCell data);

void fbClear();

void fbMvCursor(const unsigned char x, const unsigned char y);

#endif