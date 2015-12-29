#include "LGFont.h"

// For Win32
#ifdef WIN32
#define wcsdup	_wcsdup
#define close	_close
#define open	_open

typedef uint32_t WCHAR_T;

static inline size_t strlen_W(const WCHAR_T *s) {
	size_t len = 0;
	if(s) {
		while(*(s ++)) ++ len;
	}
	return len;
}

static inline void strcpy_W_to_w(wchar_t *ds, const WCHAR_T *ss) {
	while(*ss) {
		*(ds ++) = (wchar_t)(*ss ++);
	}
	*ds = 0;
}

#else
typedef wchar_t WCHAR_T;
#endif

// uint16lgString
static inline size_t strlen16(const uint16_t *str) {
	size_t len = 0;
	if(str) {
		while(*(str ++)) ++ len;
	}
	return len;
}

//CLGFont
CLGFont::CLGFont() 
: name(NULL)
,reader(NULL)
,offset(0)
,headerOffset(0)
,uncompressFontSize(0)
,compressFontSize(0)
,headerInfo(NULL)
,maskOffset(0)
,kerningOffset(0)
,loadFont(lgFALSE)
{
#ifndef _WIN32 
	pthread_mutex_init(&lock, NULL);
#endif
}

CLGFont::CLGFont(CLGResourceReader *_reader, size_t _offset, const wchar_t *_name)
:reader(_reader)
,offset(_offset)
,headerOffset(_offset)
,uncompressFontSize(0)
,compressFontSize(0)
,headerInfo(NULL)
,maskOffset(0)
,kerningOffset(0)
,loadFont(lgFALSE)
{
	name = wcsdup(_name);
#ifndef _WIN32 
	pthread_mutex_init(&lock, NULL);
#endif
}

CLGFont::~CLGFont()
{
#ifndef _WIN32 
	pthread_mutex_destroy(&lock);
#endif
}


uint16_t CLGFont::getPartial()
{
	if(UNLIKELY(!loadFont)) {(const_cast<CLGFont*>(this))->Init();}
	if(LIKELY(headerInfo))
	{
		return headerInfo->fontPartial;
	}
	
	return 0;
}

void CLGFont::setName(const wchar_t *_name)
{
	name = wcsdup(_name);
}


void CLGFont::setResourceReader(CLGResourceReader *_reader)
{
	reader = _reader;
}

void CLGFont::setOffset(size_t _offset)
{
	offset = headerOffset = _offset;
}

