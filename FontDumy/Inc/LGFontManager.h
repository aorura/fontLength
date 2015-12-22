#if !defined (_LG_FONTMANAGER_H_)
#define _LG_FONTMANAGER_H_

#include "LGFontSet.h"

//
//@class CLGFontManager
//	LGFontSet 를 관리하는 클래스
//
class CLGFontManager
{
public:
	lgBOOL              Init(const char *path);
	lgBOOL              Init(const uint8_t *buf, uint32_t bufSize);
	void                Release();

    // @brief
    // 폰트 타입에 맞는 폰트셋을 가져온다.
    const CLGFontSet*   getType(uint16_t _type);

	const LGFontMask*   getMask(wchar_t _char);
#ifdef CONFIG_FONT_FREE_TYPE
	const void			ReleaseMask(const LGFontMask* mask);
	const CLGFontSet*	getStyle(uint16_t _style);
#endif

	const int32_t       getKerning(wchar_t pc, wchar_t cc);
	const LGFontMask*	getDefaultFontMask(void);

	const uint32_t      getWidth(const wchar_t _char);
    const uint32_t      getWidth(const wchar_t *string, uint32_t *width_array);    
    const uint32_t      getWidth(const wchar_t *string, int32_t start, int32_t end);

	void				setFontSizeLanguage(uint32_t _index);
#ifdef CONFIG_FONT_FREE_TYPE
	void				setFontSizeStyle(uint32_t _index, uint16_t _style=FREETYPE_STYLE_DEFAULT);
#endif

	int32_t				getFontHeight();
	uint16_t			getFontAscender();
	uint16_t			getFontAscender(uint32_t i_type);    
	uint16_t			getFontDescender();
	uint16_t			getFontCapitalHeight();
	uint16_t			getFontLineSpace();
	uint32_t			getIgnorePixel()	{ return fontIgnorePixel; }
	uint32_t			getYadjust()		{ return fontyadjust; }

    // @brief
    // 폰트 이름에 맞는 폰트셋을 가져온다.
    const CLGFontSet*  getName(const wchar_t *fontName);

public:
    static CLGFontManager& getManager();

    CLGFontManager();
    virtual ~CLGFontManager(); 

private:
	lgBOOL              InitCommon(const char *path = NULL);    
     
private:          
    
	typedef std::vector<CLGFontSet*>				FontManagerVector;
	typedef FontManagerVector::iterator             FontManagerVectorIterator;
	typedef FontManagerVector::const_iterator       FontManagerVectorConstIterator;
    
 	FontManagerVector   fontSetVector;
    CLGResourceReader   *reader;

    uint32_t            activeFontIndex;    
    CLGFontSet*         activeFontSet;    

    uint32_t            fontCount;

	uint32_t            fontIgnorePixel;
	uint32_t            fontyadjust;

};


#endif
