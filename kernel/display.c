#include "display.h"
#include "io.h"
#include "utils.h"

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

int currentRow = 0;
int currentCol = 0;

void fbWriteCell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
	char * fbCell = (char *)(FB_START + (i * 2));
	*fbCell = c;
	short color = (fg & 0x0F) << 4 | (bg & 0x0F);
	*(fbCell + 1) = color;
}

static unsigned int toFbOffset(k_byte row, k_byte col) {
	return col + (row * FB_COL_MAX);
}

void fbClear() {
	kmemset((void *)FB_START, '0', 2 * FB_COL_MAX * FB_ROW_MAX);

	currentRow = 0;
	currentCol = 0;
}




void fbWrite(const char * d, const unsigned int len) {
	for(unsigned int i = 0; i < len; ++i) {
		if (currentRow >= FB_COL_MAX)
		{
			kmemcpy((void *)FB_START, (void *)FB_START + toFbOffset(0, 1), 2 * FB_COL_MAX * (FB_ROW_MAX - 1));
			currentRow--;
		}

		if (d[i] == '\n')
		{
			currentCol = 0;
			currentRow++; 
		} else {
			fbWriteCell(toFbOffset(currentRow, currentCol++), d[i], FB_DEFAULT_FG, FB_DEFAULT_BG);
			if (currentCol >= FB_COL_MAX) {
				currentCol = 0;
				currentRow++; 
			}
		}
	}
}

void fbWriteString(const char *d) {
	// TODO write directly to the fb.
	unsigned int len = 0;
	while(d[len] != '\0') {
		++len;
	}
	fbWrite(d, len);
}