#include <assert.h>

#include "LGFontManager.h"
#include "LGFontFreeType.h"

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

// @brief
// Type01_32px-CHN --> 01
static uint16_t  parser_fontType(const wchar_t *_name)
{
    /* park lgString str = _name;	
    lgString temp = str.substr(4, 2);    
    return (uint16_t)wcstoul(temp.c_str(), NULL, 10);*/
	return  0;
}

// @brief
// Type01_32px-CHN --> 32
static uint16_t  parser_fontSize(const wchar_t *_name)
{
	/* park lgString::size_type begin;
    lgString str = _name;      
	lgString temp = str.substr(7, 2);        
    return (uint16_t)wcstoul(temp.c_str(), NULL, 10);*/
	return 0;
}

// @brief
// Type01_32px-CHN --> CHN
static uint16_t  parser_fontIdentifier(const wchar_t *_name)
{
	/* park lgString::size_type begin, end;
    lgString str = _name;
	begin = str.find_last_of(L"-");
	
	if(begin == lgString::npos)
	{
		return FONT_ENGLISH;
	}
	
	begin++;
	end = str.length();

	lgString temp = str.substr(begin, begin - end);

	if(temp.compare(L"CHN") == 0 ) return FONT_CHINESE;
	if(temp.compare(L"JPN") == 0 ) return FONT_JAPANESE;*/

	return FONT_ENGLISH;
}

#ifdef CONFIG_FONT_FREE_TYPE
static uint16_t	parser_fontStyle(const string& _name) 
{
	FT_Library library;
	FT_Face face;
	
	if (FT_Init_FreeType( &library )) 
		return FREETYPE_STYLE_UNSUPPORTED;

	if (FT_New_Face( library, _name.c_str(), 0, &face )) 
		return FREETYPE_STYLE_UNSUPPORTED;
	
	uint16_t style = FREETYPE_STYLE_DEFAULT;
	if(face->style_flags & FT_STYLE_FLAG_BOLD)
	{
		if(face->style_flags & FT_STYLE_FLAG_ITALIC)
		{
			style = FREETYPE_STYLE_BOLD_ITALIC;
		}
		else
		{
			style = FREETYPE_STYLE_BOLD;
		}		
	}
	else if(face->style_flags & FT_STYLE_FLAG_ITALIC)
	{
		style = FREETYPE_STYLE_BOLD_ITALIC;
	}
	
	FT_Done_Face(face);
	FT_Done_FreeType(library);
	
	return style;	
}
#endif

//CLGFontManager
CLGFontManager::CLGFontManager()
{
	reader = NULL;
	activeFontIndex = -1;
    activeFontSet = NULL;
	fontCount = 0;

	fontIgnorePixel = 0;
}

CLGFontManager::~CLGFontManager()
{
#ifdef WIN32
	Release();

	fontSetVector.clear();	
	
	if(reader) 
	{
		delete reader;
		reader = NULL;
	}
#else

#endif
}

lgBOOL CLGFontManager::InitCommon(const char *path) 
{
	lgBOOL ret = lgFALSE;

	do {
		if(UNLIKELY(!reader->isValid())) 
		{
			break;
		}

		if(UNLIKELY(!reader->isLengthValid())) 
		{
			break;
		}

		if(CLGFontFreeType::InitFreeTypeFontMetaData(reader)) {
			size_t fontCount = CLGFontFreeType::getFontCount();
		
			CLGFontFreeType *font;
			for(size_t idx = 0; idx < fontCount; ++ idx) 
			{
				font = new CLGFontFreeType(reader, idx);
				if(UNLIKELY(!font)) 
				{
					break;
				}
				
				font->setType(idx);
				font->setSize(0);
				font->setIdentifier(FONT_ENGLISH);
				font->setStyle(FREETYPE_STYLE_DEFAULT);
				
				CLGFontSet* FontSet = const_cast<CLGFontSet*>(getType(idx));
				
				if(UNLIKELY(!FontSet))
				{
					FontSet = new CLGFontSet();
					FontSet->addFont((CLGFont *const)font);
					fontSetVector.push_back((CLGFontSet *const)FontSet);
				}
				else
				{
					FontSet->addFont((CLGFont *const)font);
				}
			}
		} else {
			// log...
			break;
		}

		ret = true;

	} while(lgFALSE);

	return ret;
}

lgBOOL CLGFontManager::Init(const char *path) 
{
	if(reader) return lgTRUE;

	lgBOOL ret = lgFALSE;

	do {
		reader = new CMappedFileReader(path);

		if(reader == NULL) 
		{
			break;
		}

		if(!InitCommon(path)) 
		{
			break;
		}
		ret = lgTRUE;

	} while(false);

	if(UNLIKELY(!ret)) 
	{
		if(reader) 
		{
			delete reader;
			reader = NULL;
		}
	} 
	else 
	{

	}

	return ret;
}

lgBOOL CLGFontManager::Init(const uint8_t *buf, uint32_t bufSize) 
{
	if(reader) return lgTRUE;

	bool ret = false;

	do {
		reader = new CMemoryReader(buf, bufSize);
		if(UNLIKELY(reader == NULL)) 
		{
			break;
		}

		if(UNLIKELY(!InitCommon())) 
		{
			break;
		}
		ret = lgTRUE;

	} while(lgFALSE);

	if(UNLIKELY(!ret)) 
	{
		if(LIKELY(reader)) 
		{
			delete reader;
			reader = NULL;
		}
	} 
	else 
	{

	}

	return ret;
}

void CLGFontManager::Release() 
{
	FontManagerVectorConstIterator iter = fontSetVector.begin();
		
	for(; iter != fontSetVector.end(); ++ iter) 
	{
		CLGFontSet * const & fontset = *iter;
		fontset->FullRelease();
		delete fontset;
	}
	fontSetVector.clear();

#ifdef CONFIG_FONT_FREE_TYPE
	CLGFontFreeType::ReleaseFreeTypeFontMetaData();
#endif

	if(reader) {
		delete reader;
		reader = NULL;
	}
}


const LGFontMask*   CLGFontManager::getMask(wchar_t _char)
{
	if(UNLIKELY(!activeFontSet)) { return 0; }
	return activeFontSet->getMask(_char);
}

#ifdef CONFIG_FONT_FREE_TYPE
const void CLGFontManager::ReleaseMask(const LGFontMask* mask)
{
	if(UNLIKELY(!mask))
	{
		return;
	}
	if(UNLIKELY(!activeFontSet)) { return; }	
	activeFontSet->ReleaseMask(mask);
}
#endif

const int32_t CLGFontManager::getKerning(wchar_t pc, wchar_t cc)
{
	if(UNLIKELY(!activeFontSet)) { return 0; }
	return activeFontSet->getKerning(pc, cc);
}

const LGFontMask* CLGFontManager::getDefaultFontMask(void)
{
	if(UNLIKELY(!activeFontSet)) { return 0; }
	return activeFontSet->getDefaultFontMask();
}

const CLGFontSet* CLGFontManager::getType(uint16_t _type)
{
	FontManagerVectorConstIterator iter = fontSetVector.begin();
	for(; iter != fontSetVector.end(); ++ iter) 
	{
		CLGFontSet * const & fontset = *iter;
		if(fontset->getType() == _type)
		{
			return fontset;
		}
	}
	return NULL;
}

#ifdef CONFIG_FONT_FREE_TYPE
const CLGFontSet* CLGFontManager::getStyle(uint16_t _style)
{
	FontManagerVectorConstIterator iter = fontSetVector.begin();
	for(; iter != fontSetVector.end(); ++ iter) 
	{
		CLGFontSet * const & fontset = *iter;
		if(LIKELY(fontset->getStyle(_style)))
		{
			return fontset;
		}
	}
	return NULL;
}
#endif

const CLGFontSet* CLGFontManager::getName(const wchar_t *fontName) 
{
	FontManagerVectorConstIterator iter = fontSetVector.begin();
	for(; LIKELY(iter != fontSetVector.end()); ++ iter) 
	{
		CLGFontSet * const & fontset = *iter;
		
		if(LIKELY(fontset->getFontName((const wchar_t *)fontName)))
		{
			if(LIKELY(fontset->Init()))
			{
				return fontset;
			}
		}
	}

	return NULL;
}


const uint32_t CLGFontManager::getWidth(const wchar_t _char)
{
	if(UNLIKELY(!activeFontSet)) { return 0; }	
	const LGFontMask *fontMask = activeFontSet->getMask(_char);
	
	// 폰트의 Decender 영역의 최대 출력 픽셀 수 값을 초기화
	fontIgnorePixel = 0;
	fontyadjust = 999;

	if(fontMask != NULL) 
	{
#ifndef CONFIG_FONT_FREE_TYPE
		return fontMask->width;
#else
		uint32_t width = ((LGFontFreeType2Mask*)fontMask)->xadvance;

		if(((LGFontFreeType2Mask*)fontMask)->yignorepixel > fontIgnorePixel)
		{
			fontIgnorePixel = ((LGFontFreeType2Mask*)fontMask)->yignorepixel;
		}

		if(((LGFontFreeType2Mask*)fontMask)->yadjust < fontyadjust)
		{
			fontyadjust = ((LGFontFreeType2Mask*)fontMask)->yadjust;
		}

		ReleaseMask(fontMask);
		return width;
#endif
	}
	return 0;
}

const uint32_t CLGFontManager::getWidth(const wchar_t *string, uint32_t *width_array)
{
	if(UNLIKELY(!activeFontSet)) { return 0; }
	uint32_t width	= 0;

	// 폰트의 Decender 영역의 최대 출력 픽셀 수 값을 초기화
	fontIgnorePixel = 0;
	fontyadjust = 999;

	if(LIKELY(string && *string)) 
	{
		wchar_t pc, cc;
		const LGFontMask* mask;

		pc = *(string ++);
		mask = getMask(pc);

		if( mask )
		{
#ifndef CONFIG_FONT_FREE_TYPE
			width = mask->width;
#else
			if(((LGFontFreeType2Mask*)mask)->yignorepixel > fontIgnorePixel)
			{
				fontIgnorePixel = ((LGFontFreeType2Mask*)mask)->yignorepixel;
			}

			if(((LGFontFreeType2Mask*)mask)->yadjust < fontyadjust)
			{
				fontyadjust = ((LGFontFreeType2Mask*)mask)->yadjust;
			}

			width = ((LGFontFreeType2Mask*)mask)->xadvance;
			ReleaseMask(mask);
#endif
		}
		else
		{ 
#ifndef CONFIG_FONT_FREE_TYPE
			if( getDefaultFontMask() )
			{
				width = getDefaultFontMask()->width;
			}
#else
			mask = getDefaultFontMask();
			if(LIKELY(mask))
			{
				if(((LGFontFreeType2Mask*)mask)->yignorepixel > fontIgnorePixel)
				{
					fontIgnorePixel = ((LGFontFreeType2Mask*)mask)->yignorepixel;
				}

				if(((LGFontFreeType2Mask*)mask)->yadjust < fontyadjust)
				{
					fontyadjust = ((LGFontFreeType2Mask*)mask)->yadjust;
				}

				width = ((LGFontFreeType2Mask*)mask)->xadvance;
				ReleaseMask(mask);
			}
#endif
		}

		if(LIKELY(width_array))
		{
			*(width_array++) = width;
		}
		
		while(LIKELY((cc = *(string ++)))) 
		{
			width += getKerning(pc, cc);

			mask = getMask(cc);
			if( mask )
			{
#ifndef CONFIG_FONT_FREE_TYPE
				width += mask->width;
#else
				if(((LGFontFreeType2Mask*)mask)->yignorepixel > fontIgnorePixel)
				{
					fontIgnorePixel = ((LGFontFreeType2Mask*)mask)->yignorepixel;
				}

				if(((LGFontFreeType2Mask*)mask)->yadjust < fontyadjust)
				{
					fontyadjust = ((LGFontFreeType2Mask*)mask)->yadjust;
				}

				width += ((LGFontFreeType2Mask*)mask)->xadvance;
				ReleaseMask(mask);
#endif
			}
			else
			{
#ifndef CONFIG_FONT_FREE_TYPE
				if( getDefaultFontMask() )
				{
					width += getDefaultFontMask()->width;
				}
#else
				mask = getDefaultFontMask();
				if(LIKELY(mask))
				{
					if(((LGFontFreeType2Mask*)mask)->yignorepixel > fontIgnorePixel)
					{
						fontIgnorePixel = ((LGFontFreeType2Mask*)mask)->yignorepixel;
					}	

					if(((LGFontFreeType2Mask*)mask)->yadjust < fontyadjust)
					{
						fontyadjust = ((LGFontFreeType2Mask*)mask)->yadjust;
					}

					width += ((LGFontFreeType2Mask*)mask)->xadvance;
					ReleaseMask(mask);
				}
#endif
			}
			
			if(LIKELY(width_array))
			{
				*(width_array++) = width;
			}

			pc = cc;
		}
	}

	return width;
}
   
const uint32_t CLGFontManager::getWidth(const wchar_t *string, int32_t start, int32_t end)
{
	uint32_t width = 0;
	
	// 폰트의 Decender 영역의 최대 출력 픽셀 수 값을 초기화
	fontIgnorePixel = 0;
	fontyadjust = 999;

	size_t len = wcslen(string);

	if(LIKELY(len && (start >= 0) && ((uint32_t)start < len) && ((end < 0) || (end > start)))) 
	{
		if(UNLIKELY((end < 0) || ((uint32_t)end > len))) 
		{
			end = len;
		}
	}

	const wchar_t *string_end = string + end;
	string = string + start;

	if(LIKELY(*string && start < end)) 
	{
		wchar_t pc, cc;
		const LGFontMask* mask;

		pc = *(string ++);
		mask = getMask(pc);

		if( mask )
		{
#ifndef CONFIG_FONT_FREE_TYPE
			width = mask->width;
#else
			if(((LGFontFreeType2Mask*)mask)->yignorepixel > fontIgnorePixel)
			{
				fontIgnorePixel = ((LGFontFreeType2Mask*)mask)->yignorepixel;
			}

			if(((LGFontFreeType2Mask*)mask)->yadjust < fontyadjust)
			{
				fontyadjust = ((LGFontFreeType2Mask*)mask)->yadjust;
			}

			width = ((LGFontFreeType2Mask*)mask)->xadvance;
			ReleaseMask(mask);
#endif
		}
		else
		{ 
#ifndef CONFIG_FONT_FREE_TYPE
			if( getDefaultFontMask() )
			{
				width = getDefaultFontMask()->width;
			}
#else
			mask = getDefaultFontMask();
			if(LIKELY(mask))
			{
				if(((LGFontFreeType2Mask*)mask)->yignorepixel > fontIgnorePixel)
				{
					fontIgnorePixel = ((LGFontFreeType2Mask*)mask)->yignorepixel;
				}

				if(((LGFontFreeType2Mask*)mask)->yadjust < fontyadjust)
				{
					fontyadjust = ((LGFontFreeType2Mask*)mask)->yadjust;
				}

				width = ((LGFontFreeType2Mask*)mask)->xadvance;
				ReleaseMask(mask);
			}
#endif
		}

		while(LIKELY(string != string_end)) 
		{
			cc = *(string ++);
			width += getKerning(pc, cc);

			mask = getMask(cc);
			if( mask )
			{
#ifndef CONFIG_FONT_FREE_TYPE
				width += mask->width;
#else
				if(((LGFontFreeType2Mask*)mask)->yignorepixel > fontIgnorePixel)
				{
					fontIgnorePixel = ((LGFontFreeType2Mask*)mask)->yignorepixel;
				}

				if(((LGFontFreeType2Mask*)mask)->yadjust < fontyadjust)
				{
					fontyadjust = ((LGFontFreeType2Mask*)mask)->yadjust;
				}

				width += ((LGFontFreeType2Mask*)mask)->xadvance;
				ReleaseMask(mask);
#endif
			}
			else
			{
#ifndef CONFIG_FONT_FREE_TYPE
				if( getDefaultFontMask() )
				{
					width += getDefaultFontMask()->width;
				}
#else
				mask = getDefaultFontMask();
				if(LIKELY(mask))
				{
					if(((LGFontFreeType2Mask*)mask)->yignorepixel > fontIgnorePixel)
					{
						fontIgnorePixel = ((LGFontFreeType2Mask*)mask)->yignorepixel;
					}

					if(((LGFontFreeType2Mask*)mask)->yadjust < fontyadjust)
					{
						fontyadjust = ((LGFontFreeType2Mask*)mask)->yadjust;
					}

					width += ((LGFontFreeType2Mask*)mask)->xadvance;
					ReleaseMask(mask);
				}
#endif
			}
			
			pc = cc;
		}
	}

	return width;	
}

void  CLGFontManager::setFontSizeLanguage(uint32_t _type) 
{	
	assert(_type > 0);
	uint32_t _index = _type - 1;
	
	// 폰트의 Decender 영역의 최대 출력 픽셀 수 값을 초기화
	fontIgnorePixel = 0;
	fontyadjust = 999;
	
	if( _index == activeFontIndex && LIKELY(activeFontSet))
		return;	

	uint16_t identifier = FONT_ENGLISH;

#ifdef CONFIG_FONT_FREE_TYPE
	identifier = FONT_NEUTRAL;
#endif

	FontManagerVectorConstIterator iter = fontSetVector.begin();
	for(int i =0; LIKELY(iter != fontSetVector.end()); ++ iter, i++) 
	{
		CLGFontSet * const & fontset = *iter;
		
		if(i == _index)
		{		
			if(activeFontSet != fontset)
			{
			
			}

			activeFontIndex = _index;
			activeFontSet = fontset;

#ifndef CONFIG_FONT_FREE_TYPE
			activeFontSet->setFontIdentifer(identifier);
#else
			activeFontSet->setStyle(FREETYPE_STYLE_DEFAULT);
#endif
			if (activeFontSet->Init() == lgFALSE)
			{

			}
			else
			{

			}
			return;
		}
	}
}


#ifdef CONFIG_FONT_FREE_TYPE
void  CLGFontManager::setFontSizeStyle(uint32_t _type, uint16_t _style) 
{
	assert(_type > 0);
	uint32_t _index = _type - 1;
	
	if( _index == activeFontIndex && LIKELY(activeFontSet))
		return;

	FontManagerVectorConstIterator iter = fontSetVector.begin();
	for(int i =0; LIKELY(iter != fontSetVector.end()); ++ iter, i++) 
	{
		CLGFontSet * const & fontset = *iter;
		
		if(i == _index)
		{			
			activeFontIndex = _index;
			activeFontSet = fontset;
			activeFontSet->setStyle(_style);

			if (activeFontSet->Init() == lgFALSE)
			{
				
			}
			else
			{
				
			}
			return;
		}
	}
}
#endif


int32_t CLGFontManager::getFontHeight()
{
	if(UNLIKELY(!activeFontSet)) { return 0; }	
	return activeFontSet->getHeight();
}

uint16_t CLGFontManager::getFontAscender()
{
	if(UNLIKELY(!activeFontSet)) { return 0; }	
	return activeFontSet->getAscender();
}

uint16_t CLGFontManager::getFontAscender(uint32_t i_type)
{
	setFontSizeLanguage(i_type);
	return getFontAscender();
}

uint16_t CLGFontManager::getFontDescender()
{
	if(UNLIKELY(!activeFontSet)) { return 0; }	
	return activeFontSet->getDescender();
}

uint16_t CLGFontManager::getFontCapitalHeight()
{
	if(UNLIKELY(!activeFontSet)) { return 0; }	
	return activeFontSet->getCapitalHeight();
}

uint16_t CLGFontManager::getFontLineSpace()
{
	if(UNLIKELY(!activeFontSet)) { return 0; }	
	return activeFontSet->getLineSpace();
}

/******************************************************************************************
 *
 *****************************************************************************************/
CLGFontManager& CLGFontManager::getManager()
{
	static CLGFontManager* s_instance = NULL;

	if(UNLIKELY(s_instance == NULL))
	{
		s_instance = new CLGFontManager();
		assert(s_instance);
	}

	return *s_instance;
}

