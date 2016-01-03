#include "display.h"
#include "io.h"
#include "utils.h"

using namespace horos::display;

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

#define FB_CLEAR_COLOR 0x4128

#define FB_CLEAR_MAX 255


#define FB_START (0x000B8000)

#define FB_ROW_MAX 25
#define FB_COL_MAX 80

#define FB_DEFAULT_FG (2)
#define FB_DEFAULT_BG (0)

namespace {
	int currentRow = 0;
	int currentCol = 0;

	unsigned int toFbOffset(k_byte col, k_byte row) {
		return col + (row * FB_COL_MAX);
	}

	FbCell * fb = reinterpret_cast<FbCell *>(FB_START);
}


void horos::display::fbWriteCell(unsigned int i, FbCell data) {
	fb[i] = data;
}



void horos::display::fbClear() {
	FbCell data;
	data.fg = FB_DEFAULT_FG;
	data.bg = FB_DEFAULT_BG;
	data.c = '\0';
	for (int i = 0; i < FB_COL_MAX * FB_ROW_MAX; ++i)
	{
		fbWriteCell(i, data);
	}
	
	currentRow = 0;
	currentCol = 0;
}

void horos::display::fbWrite(const char * d, unsigned int len) {
	FbCell data;
	data.fg = FB_DEFAULT_FG;
	data.bg = FB_DEFAULT_BG;
	for(unsigned int i = 0; i < len; ++i) {
		while(currentRow >= FB_ROW_MAX)
		{
			kmemcpy(fb, fb + toFbOffset(0, 1), 2 * FB_COL_MAX * (FB_ROW_MAX - 1));
			currentRow--;
		}

		if (d[i] == '\n')
		{
			data.c = '\0';
			// blank the rest of the line.
			while(currentCol < FB_COL_MAX) {
				fbWriteCell(toFbOffset(currentCol++, currentRow), data);
			}
			currentCol = 0;
			currentRow++;
		} else {
			data.c = d[i];
			fbWriteCell(toFbOffset(currentCol++, currentRow), data);
			if (currentCol >= FB_COL_MAX) {
				currentCol = 0;
				currentRow++; 
			}
		}
	}
}

void horos::display::fbWriteString(const char *d) {
	// TODO write directly to the fb.
	unsigned int len = 0;
	while(d[len] != '\0') {
		++len;
	}
	fbWrite(d, len);
}

void horos::display::fbMvCursor(unsigned char x, unsigned char y) {
	unsigned int offset = toFbOffset(x, y);
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, (offset & 0xff00) >> 8);
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, offset & 0xff);
}