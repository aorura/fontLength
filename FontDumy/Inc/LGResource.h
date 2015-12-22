#ifndef _LGRESOURCE_H_
#define _LGRESOURCE_H_
#include <stdint.h>


typedef enum {
	LANGUAGE_CODE_UNKNOWN = -1,
	LANGUAGE_CODE_UNDEFINED = 0,

	LANGUAGE_CODE_CZECH,
	LANGUAGE_CODE_GERMAN,
	LANGUAGE_CODE_ENGLISH_UK,
	LANGUAGE_CODE_ENGLISH_US,
	LANGUAGE_CODE_SPANISH,//5

	LANGUAGE_CODE_FRENCH,
	LANGUAGE_CODE_ITANLIAN,
	LANGUAGE_CODE_DUTCH,
	LANGUAGE_CODE_NORWAY,
	LANGUAGE_CODE_POLISH,//10

	LANGUAGE_CODE_PORTUGUESE,
	LANGUAGE_CODE_RUSSIAN,
	LANGUAGE_CODE_SWEDISH,
	LANGUAGE_CODE_TURKISH,
	LANGUAGE_CODE_SPANISHMEXIKO,//15

	LANGUAGE_CODE_FRENCH_CA,
	LANGUAGE_CODE_PORTUGUESEBRAZIL,
	LANGUAGE_CODE_DANISH,
	LANGUAGE_CODE_GREEK,
	LANGUAGE_CODE_CROATIAN,//20

	LANGUAGE_CODE_HUNGARIAN, 
	LANGUAGE_CODE_FINNISH,
	LANGUAGE_CODE_ARABIC_QATAR,
	LANGUAGE_CODE_SPANISH_ES,

	LANGUAGE_CODE_BOSNIAN,
	LANGUAGE_CODE_ROMANIAN,
	LANGUAGE_CODE_SLOVAK,
	LANGUAGE_CODE_SLOVENIAN,
	LANGUAGE_CODE_SERBIAN,

	LANGUAGE_CODE_KOREAN,

	LANGUAGE_CODE_BULGARIAN,
	LANGUAGE_CODE_ESTONIAN,
	LANGUAGE_CODE_JAPANESE,
	LANGUAGE_CODE_LITHUANIAN,
	LANGUAGE_CODE_LATVIAN,
	LANGUAGE_CODE_UKRAINIAN,
	LANGUAGE_CODE_CHINESEPRC,
	LANGUAGE_CODE_CHINESEHONGKONG,
	LANGUAGE_CODE_CHINESETAIWAN,

	LANGUAGE_CODE_ARABIC_SA,
	LANGUAGE_CODE_ARMENIAN,

	LANGUAGE_CODE_COUNT
} LGLanguageCode;

#endif // _LGRESOURCE_H_