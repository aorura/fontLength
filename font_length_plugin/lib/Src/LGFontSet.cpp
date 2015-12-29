#include "LGFontSet.h"

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


//CLGFontSet
CLGFontSet::CLGFontSet()
:englishOnly(lgFALSE)
,activeFont(NULL)
{
}

CLGFontSet::~CLGFontSet()
{
	fontVector.clear();
}

const void CLGFontSet::addFont(const CLGFont* _font)
{
	CLGFont* font = const_cast<CLGFont*>(_font);

	fontVector.push_back((CLGFont *const)font);

#ifndef CONFIG_FONT_FREE_TYPE
	if(font->getIdentifier() == FONT_ENGLISH)
	{
		activeFont = (CLGFont* const)font;
	}
#else
	if(font->getStyle() == FREETYPE_STYLE_DEFAULT)
	{
		activeFont = (CLGFont* const)font;
	}
#endif
}

lgBOOL CLGFontSet::Init() 
{
	if(UNLIKELY(!activeFont)) { return lgFALSE; }
	if(UNLIKELY(!activeFont->loadFont)) { return activeFont->Init(); }
	return lgTRUE;
}

void CLGFontSet::FullRelease()
{
	FontVectorConstIterator iter = fontVector.begin();
	
	if(englishOnly == lgFALSE)
	{
		for(; iter != fontVector.end(); ++ iter) 
		{
			CLGFont * const & font = *iter;
			font->Release();			
			delete font;
		}
	}
	else
	{
		CLGFont * const & font = *iter;
		font->Release();
		delete font;
	}
	fontVector.clear();
}

void CLGFontSet::Release()
{
	FontVectorConstIterator iter = fontVector.begin();
	
	if(englishOnly == lgFALSE)
	{
		for(; iter != fontVector.end(); ++ iter) 
		{
			CLGFont * const & font = *iter;
			font->Release();			
		}
	}
	else
	{
		CLGFont * const & font = *iter;
		font->Release();			
	}
}

const uint32_t CLGFontSet::getHeight() 
{
	if(UNLIKELY(!activeFont)) { return 0; }
	return activeFont->getHeight();
}

const uint16_t CLGFontSet::getType() 
{
	if(UNLIKELY(!activeFont)) { return 0; }
	return activeFont->getType();
}

const uint16_t CLGFontSet::getSize() 
{
	if(UNLIKELY(!activeFont)) { return 0; }
	return activeFont->getSize();
}

const uint16_t CLGFontSet::getIdentifier() 
{
	if(UNLIKELY(!activeFont)) { return 0; }
	return activeFont->getIdentifier();
}

#ifdef CONFIG_FONT_FREE_TYPE
const CLGFont* CLGFontSet::getStyle(uint16_t _style)  
{
	if(UNLIKELY(!fontVector.size())) { return 0; }
	if(_style == FREETYPE_STYLE_DEFAULT) return activeFont;
	
	FontVectorConstIterator iter = fontVector.begin();
	for(; iter != fontVector.end(); ++ iter) 
	{
		CLGFont * const & font = *iter;
		if(font->getStyle() == _style)
		{
			return font;
		}
	}
	return NULL;
}

const void CLGFontSet::setStyle(uint16_t _style) 
{
	if(UNLIKELY(!fontVector.size())) { return; }
	
	FontVectorConstIterator iter = fontVector.begin();
	for(; iter != fontVector.end(); ++ iter) 
	{
		CLGFont * const & font = *iter;
		if(font->getStyle() == _style)
		{
			activeFont = font;
			break;
		}
	}

	if(UNLIKELY(!activeFont) && LIKELY(fontVector.size()))
	{
		activeFont = fontVector.at(0);
	}
}
#endif

const CLGFont* CLGFontSet::getFont() 
{
	if(UNLIKELY(!activeFont)) { return 0; }
	return activeFont;
}

const void CLGFontSet::setFont(CLGFont* _font)
{
	if(UNLIKELY(!_font)) { return; }	
	if(UNLIKELY(!fontVector.size())) { return; }

	activeFont = NULL;
	
	FontVectorConstIterator iter = fontVector.begin();
	for(; iter != fontVector.end(); ++ iter) 
	{
		CLGFont * const & font = *iter;
		if(font->getIdentifier() == _font->getIdentifier())
		{
			activeFont = font;
			break;
		}
	}
}

const CLGFont* CLGFontSet::getFontName(const wchar_t *fontName) 
{
	if(UNLIKELY(!fontVector.size())) { return 0; }
	
	FontVectorConstIterator iter = fontVector.begin();
	for(; iter != fontVector.end(); ++ iter) 
	{
		CLGFont * const & font = *iter;
		if(wcscmp(font->getName(), fontName) == 0)
		{
			return font;
		}
	}
	
	return NULL;
}

const CLGFont* CLGFontSet::getFontIdentifier(uint16_t _identifier) 
{
	if(UNLIKELY(!fontVector.size())) { return 0; }
	
	FontVectorConstIterator iter = fontVector.begin();
	for(; iter != fontVector.end(); ++ iter) 
	{
		CLGFont * const & font = *iter;
		if(font->getIdentifier() == _identifier)
		{
			return font;
		}
	}

#if(0)
	iter = fontVector.begin();
	for(; iter != fontVector.end(); ++ iter) 
	{
		CLGFont * const & font = *iter;
		if(font->getIdentifier() == FONT_ENGLISH)
		{
			return font;
		}
	}
#endif

	return NULL;
}

const void CLGFontSet::setFontIdentifer(uint16_t _identifier)
{
	if(UNLIKELY(!fontVector.size())) 
	{ 
		return; 
	}

	activeFont = NULL;
	
	FontVectorConstIterator iter = fontVector.begin();
	for(; iter != fontVector.end(); ++ iter) 
	{
		CLGFont * const & font = *iter;
		if(font->getIdentifier() == _identifier)
		{
			activeFont = font;
			break;
		}
	}

	if(UNLIKELY(!activeFont) && LIKELY(fontVector.size()))
	{
		activeFont = fontVector.at(0);
	}

}

LGFontMask*	CLGFontSet::getDefaultFontMask(void)
{
	return (LGFontMask*)activeFont->getDefaultFontMask();
}

const LGFontMask* CLGFontSet::getMask(wchar_t _char)
{	
#ifdef CONFIG_FONT_FREE_TYPE
	if(UNLIKELY(!fontVector.size())) { return 0; }
	if(UNLIKELY(!activeFont)) 
	{ 
		activeFont = const_cast<CLGFont*>(getStyle((uint16_t)FREETYPE_STYLE_DEFAULT));
	}

	const LGFontMask *fontMask = activeFont->getMask(_char);
	return fontMask;

#else
	if(UNLIKELY(!fontVector.size())) { return 0; }
	if(UNLIKELY(!activeFont)) 
	{ 
		activeFont = const_cast<CLGFont*>(getFontIdentifier((uint16_t)FONT_ENGLISH));
	}

	CLGFont *enFont = const_cast<CLGFont*>(getFontIdentifier((uint16_t)FONT_ENGLISH));
	CLGFont *cnFont = const_cast<CLGFont*>(getFontIdentifier((uint16_t)FONT_CHINESE));
	CLGFont *jnFont = const_cast<CLGFont*>(getFontIdentifier((uint16_t)FONT_JAPANESE));	
 
	const LGFontMask *fontMask = enFont->getMask(_char);
	uint16_t identifier  = activeFont->getIdentifier();

	if(fontMask != NULL)
	{	
		return fontMask;
	}

	if (identifier == FONT_CHINESE)
	{
		if(cnFont != NULL)
		{
			fontMask = (LGFontMask *)cnFont->getMask(_char);
			if(fontMask != NULL )
			{	
				return fontMask;
			}
		}

		if( jnFont != NULL)
		{
			fontMask = (LGFontMask *)jnFont->getMask(_char);
			if(fontMask != NULL )
			{	
				return fontMask;
			}
		}
	}
	else if(identifier == FONT_JAPANESE)
	{
		if( jnFont != NULL)
		{
			fontMask = (LGFontMask *)jnFont->getMask(_char);
			if(fontMask != NULL )
			{	
				return fontMask;
			}
		}

		if(cnFont != NULL)
		{
			fontMask = (LGFontMask *)cnFont->getMask(_char);
			if(fontMask != NULL )
			{	
				return fontMask;
			}
		}
	}
	else
	{
		if(cnFont != NULL)
		{
			fontMask = (LGFontMask *)cnFont->getMask(_char);
			if(fontMask != NULL )
			{	
				return fontMask;
			}
		}

		if( jnFont != NULL)
		{
			fontMask = (LGFontMask *)jnFont->getMask(_char);
			if(fontMask != NULL )
			{	
				return fontMask;
			}
		}
	}
	return const_cast<LGFontMask *>(activeFont->getDefaultFontMask());
#endif	
}

#ifdef CONFIG_FONT_FREE_TYPE
const void CLGFontSet::ReleaseMask(const LGFontMask* mask)
{
	if(UNLIKELY(!fontVector.size())) { return; }
	if(UNLIKELY(!activeFont)) 
	{ 
		activeFont = const_cast<CLGFont*>(getStyle((uint16_t)FREETYPE_STYLE_DEFAULT));
	}
	activeFont->ReleaseMask(mask);
}
#endif

const int32_t CLGFontSet::getKerning(wchar_t pc, wchar_t cc)
{
	if(UNLIKELY(!fontVector.size())) { return 0; }

#ifdef CONFIG_FONT_FREE_TYPE
	if(UNLIKELY(!activeFont)) 
	{ 
		activeFont = const_cast<CLGFont*>(getStyle((uint16_t)FREETYPE_STYLE_DEFAULT));
	}
#else
	if(UNLIKELY(!activeFont)) 
	{ 
		activeFont = const_cast<CLGFont*>(getFontIdentifier((uint16_t)FONT_ENGLISH));
	}

	CLGFont *enFont = const_cast<CLGFont*>(getFontIdentifier((uint16_t)FONT_ENGLISH));
	CLGFont *cnFont = const_cast<CLGFont*>(getFontIdentifier((uint16_t)FONT_CHINESE));
	CLGFont *jnFont = const_cast<CLGFont*>(getFontIdentifier((uint16_t)FONT_JAPANESE));	

	int32_t kerning = enFont->getKerning(pc, cc);
	uint16_t identifier  = activeFont->getIdentifier();

	if( kerning != 0)
	{
		return kerning;
	}

	if (identifier == FONT_CHINESE)
	{
		if(cnFont != NULL)
		{
			kerning = cnFont->getKerning(pc, cc);
			if(kerning != NULL )
			{	
				return kerning;
			}
		}

		if( jnFont != NULL)
		{
			kerning = jnFont->getKerning(pc, cc);
			if(kerning != NULL )
			{	
				return kerning;
			}
		}
	}
	else if(identifier == FONT_JAPANESE)
	{
		if( jnFont != NULL)
		{
			kerning = jnFont->getKerning(pc, cc);
			if(kerning != NULL )
			{	
				return kerning;
			}
		}

		if(cnFont != NULL)
		{
			kerning = cnFont->getKerning(pc, cc);
			if(kerning != NULL )
			{	
				return kerning;
			}
		}
	}
	else
	{
		if(cnFont != NULL)
		{
			kerning = cnFont->getKerning(pc, cc);
			if(kerning != NULL )
			{	
				return kerning;
			}
		}

		if( jnFont != NULL)
		{
			kerning = jnFont->getKerning(pc, cc);
			if(kerning != NULL )
			{	
				return kerning;
			}
		}
	}
#endif

	return activeFont->getKerning(pc, cc);
}


const uint16_t CLGFontSet::getAscender() 
{
	if(UNLIKELY(!activeFont)) { return 0; }
	return activeFont->getTrueFontAscender();
}

const uint16_t CLGFontSet::getDescender() 
{
	if(UNLIKELY(!activeFont)) { return 0; }
	return activeFont->getTrueFontDescender();
}

const uint16_t CLGFontSet::getCapitalHeight() 
{
	if(UNLIKELY(!activeFont)) { return 0; }
	return activeFont->getTrueFontCapitalHeight();
}

const uint16_t CLGFontSet::getLineSpace() 
{
	if(UNLIKELY(!activeFont)) { return 0; }
	return activeFont->getTrueFontLineSpace();
}