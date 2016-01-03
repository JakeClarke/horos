#ifndef _H_DISPAY
#define _H_DISPAY

namespace horos {
namespace display {
	void fbWrite(const char * d, unsigned int len);

	void fbWriteString(const char *d);

	struct FbCell {
		unsigned char c;
		unsigned char fg : 4;
		unsigned char bg : 4;
	};

	void fbWriteCell(unsigned int i, FbCell data);

	void fbClear();

	void fbMvCursor(unsigned char x, unsigned char y);
}
}

#endif