#ifndef _FONT_FILE_H_
#define _FONT_FILE_H_

#define	LG_FONT_FILE_MAGIC			0x31544E46	// FNT1
#define	LG_FONT_NAME_LEN			(32)

typedef struct {
	uint16_t ch;
	uint8_t width, height;
	union {
		uint8_t *buf;
		uint32_t offset;
	};
} LGFontMask;

typedef struct {
	union {
		struct {
			uint16_t preCh;
			uint16_t curCh;
		};
		uint32_t key;
	};
	int32_t kerning;
} LGFontKerningInfo;

typedef struct {
	uint8_t *compressBuf;
	uint32_t binerySize;
	uint32_t compressSize;	
} LGMaskSizeInfo;

// @brief
// 폰트 헤더 정보 구조체
typedef struct {
    uint32_t maskinfoCount;
    uint32_t kerninginfoCount;
    uint16_t defaultChar;
    uint16_t fontHeight;
    uint16_t fontIdentifier;
    uint16_t fontPartial;
} LGFontHeaderInfo;

#endif

