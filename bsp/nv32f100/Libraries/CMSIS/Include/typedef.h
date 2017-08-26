/******************************************************************************
*
* @brief provide some type definitions which are not CMSIS style. 
*
*******************************************************************************/

#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	s8
#define s8		char
#endif
#ifndef	u8
#define u8		unsigned char
#endif
#ifndef	s16
#define s16		short
#endif
#ifndef	u16
#define u16		unsigned short
#endif
#ifndef	s32
#define s32		long
#endif
#ifndef	u32
#define u32		unsigned long
#endif
#ifndef	sint
#define sint		int
#endif
#ifndef	uint
#define uint		unsigned int
#endif
#ifndef	s64
#define s64		long long
#endif
#ifndef	u64
#define u64		unsigned long long
#endif

#ifdef __cplusplus 
} 
#endif 

#endif	/* __TYPEDEF_H__ */