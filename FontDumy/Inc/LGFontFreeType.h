#if !defined (_LGE_FONT_FREETYPE_H_)
#define _LGE_FONT_FREETYPE_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_CACHE_H
#include "LGFont.h"
#include "LGFontFileFreeType.h"

typedef struct : public LGFontMask {
	int stride;
	int xadjust;
	int yadjust;
	int xadvance;
	int yignorepixel;
	void* reference;
} LGFontFreeType2Mask;

#define	FREE_TYPE_INVALID_FILE_SIZE			((size_t)(-1))
#define	FREE_TYPE_CACHE_MAX_FACE_COUNT		(1)
#define	FREE_TYPE_CACHE_MAX_SIZE_COUNT		(6)
#define	FREE_TYPE_CACHE_MAX_BYTES			(1024 * 1024)

//
//@class CLGFontFreeType
//	전체 압축된 폰트를 사용할 클래스(이전 소스)
//

class CLGFontFreeType : public CLGFont
{
public:
    CLGFontFreeType();
    CLGFontFreeType(CLGResourceReader *_reader, uint32_t index);    
    virtual ~CLGFontFreeType();

public:
	virtual lgBOOL      Init();
    virtual void        Release();
	
    // @brief
    //  기본 폰트를 가져온다.
    //
	virtual LGFontMask* getDefaultFontMask() {return 0;}

    // @brief
    //  현재 폰트의 높이 값을 구한다.
    //
	virtual int32_t      getHeight() const;

	static bool InitFreeTypeFontMetaData(CLGResourceReader *reader);
	static size_t getFontCount();
	static void ReleaseFreeTypeFontMetaData();

private:    
	const LGFontAttribute*		m_fontAttribute;
	FTC_FaceID					m_faceId;
	struct FTC_ScalerRec_		m_ftcScaler;

	virtual LGFontMask* getMask(wchar_t _char) const;
	virtual void ReleaseMask(const LGFontMask* mask) const;

	virtual int32_t     getKerning(wchar_t pc, wchar_t cc) const;        
	virtual lgBOOL      parserHeader(void)			{return lgFALSE;}
    virtual lgBOOL      parserMaskInfo(void)		{return lgFALSE;}
    virtual lgBOOL      parserKerningInfo(void)		{return lgFALSE;}

};

#endif

