#if !defined (_LG_FONTSET_H_)
#define _LG_FONTSET_H_

#include "LGFont.h"

//@class CLGFontSet
//	LGFont 를 관리하는 클래스
//
class CLGFontSet
{
public:
    CLGFontSet();
    CLGFontSet(CLGResourceReader *_reader, size_t _offset, const wchar_t *_name);
    virtual ~CLGFontSet(); 

    // @brief
    //  현재 폰트셋에 폰트를 추가한다.
   const void           addFont(const CLGFont* _font);

public:      
    // @brief
    //  현재 폰트를 초기화한다.
    //    
    lgBOOL        Init();    
    
	void          FullRelease();

	// @brief
    //  현재 폰트 타입을 구한다.
    //    
    void          Release();

    // @brief
    //  현재 폰트 타입을 구한다.
    //    
    const uint16_t      getType();    

    // @brief
    //  현재 폰트 사이즈를 구한다.
    //    
    const uint16_t      getSize();

    // @brief
    //  현재 폰트 언어를 구한다.
    //    
    const uint16_t      getIdentifier();

    // @brief
    //  현재 기본 폰트 구한다.
    //
    const CLGFont*		getFont();

    // @brief
    //  폰트 주소값을 기준으로 기본 폰트를 설정한다.
    //
    const void		    setFont(CLGFont* _font);   

    // @brief
    //  폰트 언어를 기준으로 기본 폰트를 설정한다.
    //
    const void		    setFontIdentifer(uint16_t _identifier = FONT_ENGLISH);

    // @brief
    //  폰트 언어를 기준으로 폰트를 가져온다.
    //            
    const CLGFont*		getFontIdentifier(uint16_t _identifier = FONT_ENGLISH);

   
#ifdef CONFIG_FONT_FREE_TYPE
    // @brief
    //  현재 폰트 스타일을 구한다.
    //    
    const void			setStyle(uint16_t _style = FREETYPE_STYLE_DEFAULT); 

    // @brief
    //  폰트 스타일를 기준으로 기본 폰트를 설정한다.
    //
    const CLGFont*		getStyle(uint16_t _style = FREETYPE_STYLE_DEFAULT);
#endif

    // @brief
    //  폰트 이름을 기준으로 폰트를 가져온다.
    //        
    const CLGFont*		getFontName(const wchar_t *fontName);
	const uint32_t		getHeight() ;
	
	const uint16_t		getAscender();
	const uint16_t		getDescender();
	const uint16_t		getCapitalHeight();
	const uint16_t		getLineSpace();

    // @brief
    //  기본 폰트 기준으로 폰트마스크 정보를 가져온다.
    //
	const LGFontMask*	getMask(wchar_t _char);

#ifdef CONFIG_FONT_FREE_TYPE
	const void			ReleaseMask(const LGFontMask* mask);
#endif

    const int32_t		getKerning(wchar_t pc, wchar_t cc);
	LGFontMask*			getDefaultFontMask(void);
    
    // @brief
    //  PQMIN 모델의 폰트 그룹에 의해서 중국어와 일본어를 다른 타입의 폰트를 사용하기 위해서
    //  TYPE 4일경우
    const void          setEnglishOnly() {englishOnly = lgTRUE;};    

private:       
	typedef std::vector<CLGFont*>           FontVector;
	typedef FontVector::iterator			FontVectorIterator;
	typedef FontVector::const_iterator		FontVectorConstIterator;
 	FontVector                              fontVector;
    CLGFont                                *activeFont;
	lgBOOL									englishOnly;

protected:
	friend class CLGFont; 
};

#endif
