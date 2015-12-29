#ifndef _FONT_FILE_FREE_TYPE_H_
#define _FONT_FILE_FREE_TYPE_H_

#include <stdint.h>

#ifndef LG_FONT_FILE_MAGIC
#define	LG_FONT_FILE_MAGIC			0x31544E46	// FNT1
#endif

typedef struct {
	uint32_t fileOffset;
	uint32_t fileSize;
	uint32_t faceIndex;
} LGFaceAttribute;

typedef struct {
	uint16_t faceAttributeIndex;
	int16_t fontHeight;
	int8_t fontCapitalHeight;
	int8_t fontAscender;
	int8_t fontDecender;
	int8_t fontLinespace;
	// int8_t reserved1[2];
} LGFontAttribute;

#endif

