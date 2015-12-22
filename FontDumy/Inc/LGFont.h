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


// ��Ʈ�� ����
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
//	Font �����ϴ� ���� Ŭ����.
//	Font�� ������ �κ� ����, ���� ����(�ҽ�������), TrueType ��Ʈ�� �����Ѵ�.
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
	const wchar_t       *name;                      // @brief   ��Ʈ �̸�
	uint32_t            offset;                     // @brief   ��Ʈ ��ü���� ��Ʈ offset

	uint16_t            fontType;                   // @brief   ��Ʈ Type ����
	uint16_t            fontSize;                   // @brief   ��Ʈ ũ�� ����
	uint16_t            fontIdentifier;             // @brief   ��Ʈ ��� ����
#ifdef CONFIG_FONT_FREE_TYPE
	uint16_t			fontStyle;					// @brief   Ʈ��Ÿ�� ��Ʈ�� ��Ʈ ��Ÿ�� ����
#endif

	uint16_t			trueFontAscender;			// @brief   Truetype Font Ascender
	uint16_t			trueFontDescender;			// @brief   Truetype Font Descender
	uint16_t			trueFontCapitalHeight;		// @brief   Truetype Font Height of capital letter
	uint16_t			trueFontLinespace;			// @brief   Truetype Font LineSpace

    uint32_t            headerOffset;               // @brief   ��Ʈ ��� offset
    uint32_t            maskOffset;                 // @brief   ��Ʈ maskinfo offset
    uint32_t            kerningOffset;              // @brief   ��Ʈ kerning offset

    // @brief
    // ��Ʈ�� ��ü ���� ������� ���� ������
	uint32_t            uncompressFontSize;         // @brief   ��Ʈ ���� �� ������ 
	uint32_t            compressFontSize;           // @brief   ��Ʈ ���� ������ 

    // @brief
    // ��Ʈ�� HEADER ���� ����
    LGFontHeaderInfo*   headerInfo;                 // @brief   ��Ʈ�� ��� ����
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
    //  ���� ��Ʈ�� �κ� ���� ���� �����Ѵ�.(0, 1,2,3,4......)
    //  0 : ��ü ����
	uint16_t            getPartial();

    // @brief
    //  ���� ��Ʈ�� ���� ���� ���Ѵ�.
    //
	virtual int32_t     getHeight() const = 0;
    // @brief
    //  ��Ʈ �ʱ�ȭ
    //
	virtual lgBOOL      Init() = 0;
    virtual void        Release() = 0;

    virtual CLGResourceReader* getReader() const { return reader;}
    // @brief	
    //  ��Ʈ �̸��� �����Ѵ�.
    //
	void                setName(const wchar_t *_name);   
	const wchar_t*      getName() {return name;}
    
    // @brief
    //  ��Ʈ �̸��� �����Ѵ�.
    //
	void                setOffset(size_t _offset);      

    // @brief
    //  ���ҽ� ���� �ּҰ��� �����Ѵ�.
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
    //  �⺻ ��Ʈ�� �����´�.
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
    //  �⺻ ��Ʈ�� ����ũ ������ ����Ѵ�.
    //
	virtual LGFontMask* getMask(wchar_t _char) const = 0;

	// @brief
    //  Ʈ��Ÿ�� ��Ʈ�� ����ũ ������ �����Ѵ�.
    //
	virtual void		ReleaseMask(const LGFontMask* mask) const = 0;

    // @brief
    //  ��Ʈ�� �ε����� ���Ѵ�.
    //
    virtual int32_t		getKerning(wchar_t pc, wchar_t cc) const = 0;

private:    
    
    // @brief
    //  ��Ʈ HEADER ������ ���´�.
    //    
	virtual lgBOOL		parserHeader(void) = 0;

    // @brief
    //  ��Ʈ MASKINFO ������ ���´�.
    //    
	virtual lgBOOL		parserMaskInfo(void) = 0;    
   
    // @brief
    //  ��Ʈ KERNINGINFO ������ ���´�.
    //    
	virtual lgBOOL		parserKerningInfo(void) = 0;
 
protected:
	friend class CLGFontSet; 
};

#endif
