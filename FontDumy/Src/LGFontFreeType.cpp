#include <assert.h>
#include "LGFontFreeType.h"

/////////////////////////////////////////////////
// FontAttribute
/////////////////////////////////////////////////
// FreeType2 Face Requester
static FT_Library					g_library = NULL;
static FTC_Manager					g_ftcManager = NULL;
static FTC_CMapCache				g_ftcCMapCache = NULL;
static FTC_SBitCache				g_ftcSBitCache = NULL;
static lgBOOL						g_library_is_inited = lgFALSE;

static LGFaceAttribute *g_faceAttributes = NULL;
static size_t g_faceAttributeCount = 0;

static LGFontAttribute *g_fontAttributes = NULL;;
static size_t g_fontAttributeCount = 0;

/////////////////////////////////////////////////
// FreeType2 Face Requester
static FT_Error ftcFaceRequester(FTC_FaceID faceID, FT_Library lib, FT_Pointer _reqData, FT_Face *face);

/////////////////////////////////////////////////
// EmptyFontMaskPool
static LGFontFreeType2Mask* getEmptyFontMask();
static void putFontMaskToPool(LGFontFreeType2Mask* mask);
static void flushEmptyFontMaskPool();

///////////////////////////////////////////////
//CLGFontFreeType
CLGFontFreeType::CLGFontFreeType() : m_faceId(0)
{
}

CLGFontFreeType::CLGFontFreeType(CLGResourceReader *_reader, uint32_t fontIndex) : CLGFont(_reader, 0, L""), m_faceId(0)
{
}	

CLGFontFreeType::~CLGFontFreeType()
{
	Release();
	if(name) free((void *)name);
}

void CLGFontFreeType::Release()
{
#ifdef _WIN32
	if(LIKELY(loadFont)) 
	{
		m_faceId = 0;
	}

	loadFont = lgFALSE;
#endif

}

lgBOOL CLGFontFreeType::Init()
{
	if(LIKELY(loadFont)) { return lgTRUE; }

#ifndef _WIN32 
	pthread_mutex_lock(&lock);
#endif

	FT_Error error;
	
	if(UNLIKELY(!g_library_is_inited)) 
	{
		error = FT_Init_FreeType(&g_library);
		if(UNLIKELY(error))
		{			
			return lgFALSE;
		}

		error = FTC_Manager_New(g_library, FREE_TYPE_CACHE_MAX_FACE_COUNT, FREE_TYPE_CACHE_MAX_SIZE_COUNT, FREE_TYPE_CACHE_MAX_BYTES, ftcFaceRequester, this, &g_ftcManager);
		if(UNLIKELY(error))
		{
			return lgFALSE;
		}

		error = FTC_CMapCache_New(g_ftcManager, &g_ftcCMapCache);
		if(UNLIKELY(error))
		{
			return lgFALSE;
		}

		error = FTC_SBitCache_New(g_ftcManager, &g_ftcSBitCache);
		if(UNLIKELY(error))
		{
			return lgFALSE;
		}

		g_library_is_inited = lgTRUE;		
	}
	
	assert(getType() < g_fontAttributeCount);
	m_fontAttribute = &g_fontAttributes[getType()];

	setTrueFontAscender(m_fontAttribute->fontAscender);
	setTrueFontDescender(m_fontAttribute->fontDecender);
	setTrueFontCapitalHeight(m_fontAttribute->fontCapitalHeight);
	setTrueFontLineSpace(m_fontAttribute->fontLinespace);

	if(UNLIKELY(!m_fontAttribute))
	{
		return lgFALSE;
	}

	assert(m_fontAttribute->faceAttributeIndex < g_faceAttributeCount);
	m_faceId = (FTC_FaceID)&g_faceAttributes[m_fontAttribute->faceAttributeIndex];

	m_ftcScaler.face_id = m_faceId;
	m_ftcScaler.width = 0;
	m_ftcScaler.height = m_fontAttribute->fontHeight;
	m_ftcScaler.pixel = 0;
	m_ftcScaler.x_res = 0;
	m_ftcScaler.y_res = 0;

	loadFont = lgTRUE;

#ifndef _WIN32 
	pthread_mutex_unlock(&lock);
#endif

	return loadFont;	
}

LGFontMask* CLGFontFreeType::getMask(wchar_t _char) const
{
	if(UNLIKELY(!loadFont)) {(const_cast<CLGFontFreeType*>(this))->Init();}

	FT_Error error;
	FTC_SBit ftcSBit;
	FTC_Node ftcNode;

	LGFontFreeType2Mask* mask = getEmptyFontMask();
	if(UNLIKELY(!mask))
	{
		return 0;
	}

	FT_UInt glyphIndex = FTC_CMapCache_Lookup(g_ftcCMapCache, m_faceId, -1, _char);

	CLGFontFreeType* athis = const_cast<CLGFontFreeType*>(this);
	error = FTC_SBitCache_LookupScaler(g_ftcSBitCache, &athis->m_ftcScaler, FT_LOAD_RENDER | FT_LOAD_NO_BITMAP | FT_LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH, glyphIndex, &ftcSBit, &ftcNode);
	if(UNLIKELY(error))
	{
		return 0;
	}

	if(UNLIKELY(!(ftcSBit->pitch >= 0)))
	{
		return 0;
	}	

	if(UNLIKELY(!(ftcSBit->format == 2)))
	{
		return 0;
	}	

	mask->ch = _char;
	mask->width = ftcSBit->width;
	mask->height = ftcSBit->height;
	mask->buf = ftcSBit->buffer;
	mask->stride = ftcSBit->pitch;
	mask->xadjust = ftcSBit->left;
	mask->yadjust = (m_fontAttribute->fontAscender + m_fontAttribute->fontCapitalHeight)- ftcSBit->top;
	mask->xadvance = ftcSBit->xadvance;
	mask->yignorepixel = abs(ftcSBit->height - ftcSBit->top);
	mask->reference = ftcNode;

	return mask;
}

int32_t CLGFontFreeType::getKerning(wchar_t pc, wchar_t cc) const
{
	if(UNLIKELY(!loadFont)) {(const_cast<CLGFontFreeType*>(this))->Init();}

	FT_Face face;
	FT_Error error;
	
	error = FTC_Manager_LookupFace(g_ftcManager, m_faceId, &face);
	if(UNLIKELY(error))
	{
		return 0;
	}

	FT_Size size;
	error = FTC_Manager_LookupSize(g_ftcManager, (FTC_Scaler)&m_ftcScaler, &size);
	if(UNLIKELY(error))
	{
		return 0;
	}

	FT_Vector kerning = {0, 0};
	FT_Get_Kerning(face, pc, cc, FT_KERNING_DEFAULT, &kerning);
	return (kerning.x >> 6);
}


void CLGFontFreeType::ReleaseMask(const LGFontMask* mask) const
{
	if(UNLIKELY(!mask))
	{
		return;
	}

	LGFontFreeType2Mask* freeMask2 = (LGFontFreeType2Mask*)mask;

	putFontMaskToPool(const_cast<LGFontFreeType2Mask*>(freeMask2));
	FTC_Node_Unref((FTC_Node)freeMask2->reference, g_ftcManager);
}

int32_t CLGFontFreeType::getHeight() const
{
	return (m_fontAttribute->fontAscender + m_fontAttribute->fontCapitalHeight + m_fontAttribute->fontDecender);
}

bool CLGFontFreeType::InitFreeTypeFontMetaData(CLGResourceReader *reader) {
	bool retBool;
	size_t retSize;

	retBool = reader->readUint32(retSize);
	assert(retBool);
	assert(retSize == LG_FONT_FILE_MAGIC);

	retBool = reader->readUint32(g_faceAttributeCount);
	assert(retBool);

	g_faceAttributes = (LGFaceAttribute*)malloc(sizeof(LGFaceAttribute) * g_faceAttributeCount);
	assert(g_faceAttributes);

	retSize = reader->readData((uint8_t *)g_faceAttributes, sizeof(LGFaceAttribute) * g_faceAttributeCount);
	assert(retSize == sizeof(LGFaceAttribute) * g_faceAttributeCount);

	retBool = reader->readUint32(g_fontAttributeCount);
	assert(retBool);

	g_fontAttributes = (LGFontAttribute*)malloc(sizeof(LGFontAttribute) * g_fontAttributeCount);
	assert(g_fontAttributes);

	retSize = reader->readData((uint8_t *)g_fontAttributes, sizeof(LGFontAttribute) * g_fontAttributeCount);
	assert(retSize == sizeof(LGFontAttribute) * g_fontAttributeCount);

	return true;
}

size_t CLGFontFreeType::getFontCount() {
	return g_fontAttributeCount;
}

void CLGFontFreeType::ReleaseFreeTypeFontMetaData() {
	FTC_Manager_Done(g_ftcManager);
	g_ftcManager = NULL;
	g_ftcCMapCache = NULL;
	g_ftcSBitCache = NULL;			

	FT_Done_FreeType(g_library);
	g_library = NULL;

	flushEmptyFontMaskPool();

	g_library_is_inited = lgFALSE;		

	if(g_faceAttributes) {
		free(g_faceAttributes);
		g_faceAttributes = NULL;
	}

	if(g_fontAttributes) {
		free(g_fontAttributes);
		g_fontAttributes = NULL;
	}

	g_fontAttributeCount = g_fontAttributeCount = 0;
}

/////////////////////////////////////////////////
// FreeType2 Face Requester
FT_Error ftcFaceRequester(FTC_FaceID faceID, FT_Library lib, FT_Pointer _reqData, FT_Face *face) 
{
	CLGFontFreeType* font = (CLGFontFreeType*)_reqData;
	CLGResourceReader* reader = font->getReader();
	LGFaceAttribute* faceAttribute = (LGFaceAttribute*)faceID;

	if(UNLIKELY(!reader->isBufferValid()))
	{
		return 1;
	}

	const uint8_t *fileBase = reader->getBuffer() + faceAttribute->fileOffset;
	size_t fileSize = faceAttribute->fileSize;

	FT_Error error = FT_New_Memory_Face(lib, fileBase, fileSize, faceAttribute->faceIndex, face);
	if(UNLIKELY(error))
	{
		return error;
	}

	return error;
}


/////////////////////////////////////////////////
// EmptyFontMaskPool
static std::list<LGFontFreeType2Mask*> m_emptyFontMaskPool;

LGFontFreeType2Mask* getEmptyFontMask() 
{
	LGFontFreeType2Mask* mask = NULL;
	if(LIKELY(m_emptyFontMaskPool.size())) 
	{
		mask = m_emptyFontMaskPool.front();
		m_emptyFontMaskPool.pop_front();
	} 
	else 
	{
		mask = (LGFontFreeType2Mask*)malloc(sizeof(LGFontFreeType2Mask));
	}
	
	return mask;
}

void putFontMaskToPool(LGFontFreeType2Mask* mask) 
{
	m_emptyFontMaskPool.push_back(mask);
}

void flushEmptyFontMaskPool() 
{
	while(LIKELY(m_emptyFontMaskPool.size())) 
	{
		LGFontFreeType2Mask* mask = m_emptyFontMaskPool.front();
		m_emptyFontMaskPool.pop_front();
		free(mask);
	}
}
