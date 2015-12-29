#if !defined (_LG_FONT_H_)
#define _LG_FONT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mman.h>
#include <wchar.h>
#include <vector>
#include <list>

#include "LGFontFile.h"
#include "LGResourceReader.h"
#include "LGTypeDef.h"
#include "LGFontIdentifier.h"
#include "LGResource.h"

#ifdef WIN32
#include <io.h>
#else
#include <pthread.h>
#include <sys/time.h>
#endif


// 폰트별 정의
#define CONFIG_FONT_FREE_TYPE


#define	GET_UINT32(p)				(*(uint32_t *)(p));((p)+=4)
#define	GET_UINT16(p)				(*(uint16_t *)(p));((p)+=2)
#define	GET_UINT8(p)				(*(uint8_t *)(p));((p)+=1)
#define	MAKE_KERNING_KEY(pc, cc)	(((cc)<<16)|(pc))

#define FREETYPE_STYLE_DEFAULT		0
#define FREETYPE_STYLE_BOLD			1
#define FREETYPE_STYLE_ITALIC		2
#define FREETYPE_STYLE_BOLD_ITALIC	3
#define FREETYPE_STYLE_UNSUPPORTED	99

//
//@class CLGFont
//	Font 관리하는 상위 클래스.
//	Font의 종류는 부분 압축, 이전 압축(소스관리상), TrueType 폰트로 구분한다.
//
class CLGFont 
{

public:
    CLGFont();
    CLGFont(CLGResourceReader *_reader, size_t _offset, const wchar_t *_name);
    virtual ~CLGFont(); 

protected:
#ifndef _WIN32 
	pthread_mutex_t		lock;
#endif    
	lgBOOL				loadFont;

	CLGResourceReader   *reader;    
	const wchar_t       *name;                      // @brief   폰트 이름
	uint32_t            offset;                     // @brief   폰트 전체내의 폰트 offset

	uint16_t            fontType;                   // @brief   폰트 Type 정의
	uint16_t            fontSize;                   // @brief   폰트 크기 정의
	uint16_t            fontIdentifier;             // @brief   폰트 언어 정의
#ifdef CONFIG_FONT_FREE_TYPE
	uint16_t			fontStyle;					// @brief   트루타입 폰트의 폰트 스타일 정의
#endif

	uint16_t			trueFontAscender;			// @brief   Truetype Font Ascender
	uint16_t			trueFontDescender;			// @brief   Truetype Font Descender
	uint16_t			trueFontCapitalHeight;		// @brief   Truetype Font Height of capital letter
	uint16_t			trueFontLinespace;			// @brief   Truetype Font LineSpace

    uint32_t            headerOffset;               // @brief   폰트 헤더 offset
    uint32_t            maskOffset;                 // @brief   폰트 maskinfo offset
    uint32_t            kerningOffset;              // @brief   폰트 kerning offset

    // @brief
    // 폰트의 전체 압축 사이즈와 해제 사이즈
	uint32_t            uncompressFontSize;         // @brief   폰트 압축 후 사이즈 
	uint32_t            compressFontSize;           // @brief   폰트 압축 사이즈 

    // @brief
    // 폰트의 HEADER 정보 변수
    LGFontHeaderInfo*   headerInfo;                 // @brief   폰트의 헤더 정보
public:   
	inline  void 		setTrueFontAscender(uint16_t ascender)			{ trueFontAscender = ascender;}
	inline  void 		setTrueFontDescender(uint16_t descender)		{ trueFontDescender = descender;}
	inline  void 		setTrueFontCapitalHeight(uint16_t height)		{ trueFontCapitalHeight = height;}
	inline  void 		setTrueFontLineSpace(uint16_t linespace)		{ trueFontLinespace = linespace;}

	inline  uint16_t	getTrueFontAscender()							{ return trueFontAscender;}
	inline  uint16_t	getTrueFontDescender()							{ return trueFontDescender;}
	inline  uint16_t	getTrueFontCapitalHeight()						{ return trueFontCapitalHeight;}
	inline  uint16_t	getTrueFontLineSpace()							{ return trueFontLinespace;}

    // @brief
    //  현재 폰트의 부분 압축 값을 리턴한다.(0, 1,2,3,4......)
    //  0 : 전체 압축
	uint16_t            getPartial();

    // @brief
    //  현재 폰트의 높이 값을 구한다.
    //
	virtual int32_t     getHeight() const = 0;
    // @brief
    //  폰트 초기화
    //
	virtual lgBOOL      Init() = 0;
    virtual void        Release() = 0;

    virtual CLGResourceReader* getReader() const { return reader;}
    // @brief	
    //  폰트 이름을 설정한다.
    //
	void                setName(const wchar_t *_name);   
	const wchar_t*      getName() {return name;}
    
    // @brief
    //  폰트 이름을 설정한다.
    //
	void                setOffset(size_t _offset);      

    // @brief
    //  리소스 리더 주소값을 설정한다.
    //
	void                setResourceReader(CLGResourceReader *_reader);


    inline  void        setSize(uint16_t _size)             { fontSize = _size;     }
    inline  uint16_t    getSize()                           { return fontSize;      }
    inline  void        setType(uint16_t _type)             { fontType = _type;     }        
    inline  uint16_t    getType()                           { return fontType;      }
    inline  void        setIdentifier(uint16_t _lang)       { fontIdentifier = _lang;}            
    inline  uint16_t    getIdentifier()                     { return fontIdentifier;}

#ifdef CONFIG_FONT_FREE_TYPE
	inline	void		setStyle(uint16_t fs=FREETYPE_STYLE_DEFAULT) { fontStyle = fs;}
	inline	uint16_t	getStyle()							{ return fontStyle;}
#endif
    // @brief
    //  기본 폰트를 가져온다.
    //
	virtual LGFontMask* getDefaultFontMask() = 0;    

#ifndef _WIN32
    inline uint32_t getTick() 
    {
        struct timeval gettick;
        uint32_t tick;
        int ret;

        gettimeofday(&gettick, NULL);
        tick = gettick.tv_sec*1000 + gettick.tv_usec;
        return tick;            
    }
#endif
private:
    // @brief
    //  기본 폰트의 마스크 정보를 취득한다.
    //
	virtual LGFontMask* getMask(wchar_t _char) const = 0;

	// @brief
    //  트루타입 폰트의 마스크 정보를 해제한다.
    //
	virtual void		ReleaseMask(const LGFontMask* mask) const = 0;

    // @brief
    //  폰트의 인덱스를 구한다.
    //
    virtual int32_t		getKerning(wchar_t pc, wchar_t cc) const = 0;

private:    
    
    // @brief
    //  폰트 HEADER 정보를 얻어온다.
    //    
	virtual lgBOOL		parserHeader(void) = 0;

    // @brief
    //  폰트 MASKINFO 정보를 얻어온다.
    //    
	virtual lgBOOL		parserMaskInfo(void) = 0;    
   
    // @brief
    //  폰트 KERNINGINFO 정보를 얻어온다.
    //    
	virtual lgBOOL		parserKerningInfo(void) = 0;
 
protected:
	friend class CLGFontSet; 
};

#endif
