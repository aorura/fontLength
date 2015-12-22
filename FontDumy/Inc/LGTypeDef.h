
 //	 CARINFO3 Team. LABORATORY, LG ELECTRONICS INC., 
 //	 Copyright(c) 2012 by LG Electronics Inc.
 //
 //	 All rights reserved. No part of this work may be reproduced, stored in a
 //	 retrieval system, or transmitted by any means without prior written
 //	 permission of LG Electronics Inc.
 //

 // \file LGTypeDef
 //
 //	@brief Common Used Type Definitions.
 //
 //----------------------------------------------------------------------------
 //  Ver.    Date        name               Edition history
 // -----  --------  ------------  --------------------------------------------
 // 1.0.0  2012.7.7   Mason.Woo             released
 

#pragma once


#ifdef IS_WINDOWS
 #pragma warning(disable:4996)
 #pragma warning(disable:4209)
 #pragma warning(disable:4786)
 #pragma warning(disable:4204)
#endif

#ifndef __LGTYPEDEF_H__
#define __LGTYPEDEF_H__


#ifdef WIN32
//#pragma comment(lib,"libagg.lib")
//#pragma comment(lib,"libpng.lib")
//#pragma comment(lib,"libz.lib")
//#pragma comment(lib,"comctl32.lib")
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <list>
#include <vector>

#ifndef _WCHAR_T_DEFINED
# include <wchar.h>
#endif

using namespace std;

#ifdef _UNICODE
	typedef wstring  lgString;
#else
	typedef string  lgString;
#endif

//#define	CALLBACK __stdcall

//////////////////////////////////////////////////////////////////////////
//Type redefine.
#ifdef WIN32
// unsigned number 
typedef	unsigned char				lgBYTE, *lgPBYTE;
typedef unsigned short				lgWORD, *lgPWORD;
typedef unsigned long				lgDWORD, *lgPDWORD;
//typedef unsigned __int64			lgQWORD, *lgPQWORD;

// signed number 
typedef short						lgSHORT, *lgPSHORT;
typedef long						lgLONG, *lgPLONG;
//typedef __int64						lgLLONG, *lgPLLONG;

// normal number
typedef int							lgINT, *lgPINT;
typedef unsigned int				lgUINT, *lgPUINT;

// size 
typedef size_t						lgSIZET, *lgPSIZET;

// float
typedef float						lgSINGLE, *lgPSINGLE;
typedef double						lgDOUBLE, *lgPDOUBLE;
#ifdef M_FLOAT_SINGLE
typedef lgSINGLE					lgFLOAT, *lgPFLOAT;
#else
typedef lgDOUBLE					lgFLOAT, *lgPFLOAT;
#endif

// void type 
typedef void						lgVOID, *lgPVOID;

// Gerneral pointer 
typedef lgVOID*						lgPTR;
typedef const lgVOID*				lgCONSTPTR;

// handle 
typedef lgVOID*						lgHANDLE, *lgPHANDLE;

// string 
typedef char						lgACHAR;
typedef lgACHAR*					lgASTRING;
typedef const lgACHAR*				lgCONSTASTRING;
typedef wchar_t						lgWCHAR;
typedef lgWCHAR*					lgWSTRING;
typedef const lgWCHAR*				lgCONSTWSTRING;
#else
	typedef	unsigned char				lgBYTE, *lgPBYTE;
	typedef unsigned short				lgWORD, *lgPWORD;
	typedef unsigned long				lgDWORD, *lgPDWORD;
	//typedef unsigned __int64			lgQWORD, *lgPQWORD;

	// signed number 
	typedef short						lgSHORT, *lgPSHORT;
	typedef long						lgLONG, *lgPLONG;
	//typedef __int64						lgLLONG, *lgPLLONG;

	// normal number
	typedef int							lgINT, *lgPINT;
	typedef unsigned int				lgUINT, *lgPUINT;

	// size 
	typedef size_t						lgSIZET, *lgPSIZET;

	// float 
	typedef float						lgSINGLE, *lgPSINGLE;
	typedef double						lgDOUBLE, *lgPDOUBLE;
#ifdef M_FLOAT_SINGLE
	typedef lgSINGLE					lgFLOAT, *lgPFLOAT;
#else
	typedef lgDOUBLE					lgFLOAT, *lgPFLOAT;
#endif

	// void type 
	typedef void						lgVOID, *lgPVOID;

	// Gerneral pointer 
	typedef lgVOID*						lgPTR;
	typedef const lgVOID*				lgCONSTPTR;

	// handle 
	typedef lgVOID*						lgHANDLE, *lgPHANDLE;

	// string 
	typedef char						lgACHAR;
	typedef lgACHAR*					lgASTRING;
	typedef const lgACHAR*				lgCONSTASTRING;
	typedef wchar_t						lgWCHAR;
	typedef lgWCHAR*					lgWSTRING;
	typedef const lgWCHAR*				lgCONSTWSTRING;

#endif

// NULL VALUE 
#ifndef NULL
#define NULL	0
#endif

typedef	unsigned char				uint8;
typedef	signed char					sint8;

typedef	unsigned short				uint16;
typedef	signed short				sint16;

typedef	unsigned int				uint32;
typedef signed int					sint32;

typedef	unsigned long long			uint64;
typedef	signed long long			sint64;



#if !WIN32
 typedef	unsigned int			boolean;
#else
#endif

#ifndef FALSE
#define FALSE						(0)
#endif

typedef char						lgBOOL;
#define lgTRUE						1
#define lgFALSE						0

#ifndef NULL
#define NULL						((lgVOID *)0)
#endif

#ifndef _UNICODE
typedef lgACHAR						lgCHAR;
#define	LG_T(x)						x
#define STRLEN						strlen
#define STRCPY						strcpy
#define STRDUP						strdup
#define STRNCPY						strncpy
#define STRCAT						strcat
#define STRNCAT						strncat
#define STRCMP						strcmp
#define STRICMP						stricmp
#define STRNCMP						strncmp
#define STRNICMP					strnicmp
#define STRCHR						strchr
#define STRRCHR						strrchr
#define STRSTR						strstr
#define STRUPR						strupr
#define STRLWR						strlwr
#define STRTOK						strtok
#define ATOI						atoi
#define ATOF						atof
#define PRINTF						printf
#define SPRINTF						sprintf
#ifdef _MSC_VER
#define VSPRINTF					_vsnprintf
#else
#define VSPRINTF					vsnprintf
#endif
#define SSCANF						sscanf
#define FOPEN						fopen
#define GETENV						getenv
#define FGETS						fgets
#else	// _UNICODE
typedef lgWCHAR						lgCHAR; 

#define LG_T(x)						L##x

#define STRLEN						wcslen
#define STRCPY						wcscpy
#define STRNCPY						wcsncpy
#define STRDUP						wcsdup
#define STRCAT						wcscat
#define STRNCAT						wcsncat
#define STRCMP						wcscmp
#define STRICMP						wcsicmp
#define STRNCMP						wcsncmp
#define STRNICMP					wcsnicmp
#define STRCHR						wcschr
#define STRRCHR						wcsrchr
#define STRSTR						wcsstr
#define STRUPR						wcsupr
#define STRLWR						wcslwr
#define STRTOK						wcstok
#define ATOI						_wtoi
#define ATOF(x)						wcstod(x,NULL)
#define PRINTF						wprintf
#define SPRINTF						swprintf
#ifdef _MSC_VER
#define VSPRINTF					_vsnwprintf
#else
#define VSPRINTF					vswprintf
#endif	// WIN32
#define SSCANF						swscanf
#define FOPEN						_wfopen
#define GETENV						_wgetenv
#define FGETS						fgetws
#endif	// _UNICODE

typedef lgCHAR*						lgSTRING;
typedef const lgCHAR*				lgCONSTSTRING;

//typedef struct st_id_name
//{
//	uint32	id;
//	uint8	name[252];
//}idname;

#define UI8_0						(uint8)0
#define UI16_0						(uint16)0
#define UI32_0						(uint32)0
#define UI64_0						(uint64)0
#define SI8_0						(sint8)0
#define SI16_0						(sint16)0
#define SI32_0						(sint32)0
#define SI64_0						(sint64)0

#ifdef _MSC_VER
#define LGFILE_SEPARATOR			LG_T('\\')
#else
#define LGFILE_SEPARATOR			LG_T('/')
#endif

//////////////////////////////////////////////////////////////////////////
// Common Macro Function.
#define SAFE_NEW(x,y)				{x=NULL;if(!x)x = new y;}
#define SAFE_NEW1(x,y,z)			{x=NULL;if(!x)x = new y[z];}
#define SAFE_CREATE(x,y,z)			{if(!x)x = new y;x->OnCreate(z);}

#define SAFE_DESTROY(x)				if (x) {x->OnDestroy(); delete x; x = NULL;}
#define SAFE_DELETE(x)				if (x) {delete x; x = NULL;}
#define SAFE_DELETE1(x)				if (x) {delete[] x; x = NULL;}

#define MEMZERO(destin)				memset (&destin, 0, sizeof (destin));
#define BMP_BUF_SIZE(w,h,b)			( ( ( ( w * b + b ) >> 2 ) << 2 ) * h )
#define BMP_LINE_SIZE(w,b)			( ( ( w * b + b ) >> 2 ) << 2 )

///////////////////////////////////////////////////////////////////////////////////////////////
// UNICODE<->ANSI CODE :  Global UNICODE<>ANSI translation helpers
//949: Korean code-Page.
#define HELPER_A2W(psz, wsz, iOutLen) MultiByteToWideChar(CP_ACP, 0, psz, -1, wsz, iOutLen)
#define HELPER_A2WEX(iCodePage, psz, wsz, iOutLen) MultiByteToWideChar(iCodePage, 0, psz, -1, wsz, iOutLen)
#define HELPER_W2A(wsz, psz, iOutLen) WideCharToMultiByte(CP_ACP, 0, wsz, -1, psz, iOutLen, 0, 0)

///////////////////////////////////////////////////////////////////////////////////////////////
// EVENT
//#define ON_EVENT(instance,_this,callee,type,nScene){instance->RegisterHandler(_this,callee,type,nScene);}

typedef lgBOOL (* NOTIFY_HANDLER)(lgVOID* pParam, lgVOID* pParam1,lgVOID* pParam2,lgVOID* pParam3);
typedef lgBOOL (* DRAW_HANDLER)(lgVOID* pParam, lgVOID* pParam1,lgVOID* pParam2,lgVOID* pParam3);
typedef lgBOOL (* EVENT_HANDLER)( lgUINT x, lgUINT y, lgINT nID, lgVOID* pParam, lgVOID* pParam1, lgVOID* pParam2, lgVOID* pParam3);

///////////////////////////////////////////////////////////////////////////////////////////////
// Operation
#define DIM( _x )	( sizeof(_x) / sizeof( (_x)[0] ) )

///////////////////////////////////////////////////////////////////////////////////////////////
// Debug
#ifdef _HMI_ENGINE_SIMULATOR_MFC

extern lgVOID		OuputMessageEmulator( char* message);

#define lgdebug( ... )		( printf(__VA_ARGS__) )
//#define dlgdebug( ... )		( printf(__VA_ARGS__) )
#define dlgdebug( ... ) {char s[128];sprintf( s,__VA_ARGS__ );OuputMessageEmulator(s);}
#define windebug( ... )		( printf(__VA_ARGS__) )

#elif WIN32
#define lgdebug( ... )		( printf(__VA_ARGS__) )
#define dlgdebug( ... )		( printf(__VA_ARGS__) )
#define windebug( ... )		( printf(__VA_ARGS__) )

#else

#include "../../include/bscommon.h"
#include "../../include/bslog.h"
#include "../../include/bsipc.h"
//#include "../../include/bslog_attr.h"
//#include "../../include/bslog_attr_debug.h"
//#include "../../include/bslog_logtrace.h"

#define lgdebug( ... )		lg_print(eLGDP_GUI_TRACE, ##__VA_ARGS__)
#define dlgdebug( ... )		lg_print(eLGDP_GUI_TRACE, ##__VA_ARGS__)

#define windebug( ... )		

#endif

typedef struct tagCALANDER {	
	lgINT year;  ///< 현재일자
	lgINT month; ///< 1(1월)-12
	lgINT mday;  ///< 월중일자, 1-31
} CALENDER, *PCALENDER;


typedef struct tagCLOCK {	
	lgINT hour;  ///< 시
	lgINT min; ///< 분	
	lgINT second;
} CLOCK, *PCLOCK;


//static char * ltoa( int val, int base )
//{
//	static char buf[32] = {0,};
//	int i =30;
//	for( ; val&i; --i, val/=base )
//		buf[i] = "0123456789abcdef"[val%base];
//	return &buf[i+1];
//}

static wchar_t * ltowcs( int val, int base )
{
	static wchar_t buf[32] = {0,};
	int i =30;
	for( ; val&i; --i, val/=base )
		buf[i] = L"0123456789abcdef"[val%base];
	return &buf[i+1];
}

#endif	//__LGTYPEDEF_H__

