#if !defined (_LG_FONTSET_H_)
#define _LG_FONTSET_H_

#include "LGFont.h"

//@class CLGFontSet
//	LGFont �� �����ϴ� Ŭ����
//
class CLGFontSet
{
public:
    CLGFontSet();
    CLGFontSet(CLGResourceReader *_reader, size_t _offset, const wchar_t *_name);
    virtual ~CLGFontSet(); 

    // @brief
    //  ���� ��Ʈ�¿� ��Ʈ�� �߰��Ѵ�.
   const void           addFont(const CLGFont* _font);

public:      
    // @brief
    //  ���� ��Ʈ�� �ʱ�ȭ�Ѵ�.
    //    
    lgBOOL        Init();    
    
	void          FullRelease();

	// @brief
    //  ���� ��Ʈ Ÿ���� ���Ѵ�.
    //    
    void          Release();

    // @brief
    //  ���� ��Ʈ Ÿ���� ���Ѵ�.
    //    
    const uint16_t      getType();    

    // @brief
    //  ���� ��Ʈ ����� ���Ѵ�.
    //    
    const uint16_t      getSize();

    // @brief
    //  ���� ��Ʈ �� ���Ѵ�.
    //    
    const uint16_t      getIdentifier();

    // @brief
    //  ���� �⺻ ��Ʈ ���Ѵ�.
    //
    const CLGFont*		getFont();

    // @brief
    //  ��Ʈ �ּҰ��� �������� �⺻ ��Ʈ�� �����Ѵ�.
    //
    const void		    setFont(CLGFont* _font);   

    // @brief
    //  ��Ʈ �� �������� �⺻ ��Ʈ�� �����Ѵ�.
    //
    const void		    setFontIdentifer(uint16_t _identifier = FONT_ENGLISH);

    // @brief
    //  ��Ʈ �� �������� ��Ʈ�� �����´�.
    //            
    const CLGFont*		getFontIdentifier(uint16_t _identifier = FONT_ENGLISH);

   
#ifdef CONFIG_FONT_FREE_TYPE
    // @brief
    //  ���� ��Ʈ ��Ÿ���� ���Ѵ�.
    //    
    const void			setStyle(uint16_t _style = FREETYPE_STYLE_DEFAULT); 

    // @brief
    //  ��Ʈ ��Ÿ�ϸ� �������� �⺻ ��Ʈ�� �����Ѵ�.
    //
    const CLGFont*		getStyle(uint16_t _style = FREETYPE_STYLE_DEFAULT);
#endif

    // @brief
    //  ��Ʈ �̸��� �������� ��Ʈ�� �����´�.
    //        
    const CLGFont*		getFontName(const wchar_t *fontName);
	const uint32_t		getHeight() ;
	
	const uint16_t		getAscender();
	const uint16_t		getDescender();
	const uint16_t		getCapitalHeight();
	const uint16_t		getLineSpace();

    // @brief
    //  �⺻ ��Ʈ �������� ��Ʈ����ũ ������ �����´�.
    //
	const LGFontMask*	getMask(wchar_t _char);

#ifdef CONFIG_FONT_FREE_TYPE
	const void			ReleaseMask(const LGFontMask* mask);
#endif

    const int32_t		getKerning(wchar_t pc, wchar_t cc);
	LGFontMask*			getDefaultFontMask(void);
    
    // @brief
    //  PQMIN ���� ��Ʈ �׷쿡 ���ؼ� �߱���� �Ϻ�� �ٸ� Ÿ���� ��Ʈ�� ����ϱ� ���ؼ�
    //  TYPE 4�ϰ��
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
