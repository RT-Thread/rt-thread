/** @file hal_stdtypes.h
*   @brief HALCoGen standard types header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Type and Global definitions which are relevant for all drivers.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __HAL_STDTYPES_H__
#define __HAL_STDTYPES_H__

/* USER CODE BEGIN (0) */
/* USER CODE END */
/************************************************************/
/* Type Definitions                                         */
/************************************************************/
#ifndef _UINT64_DECLARED
typedef unsigned long long uint64;
#define	_UINT64_DECLARED
#endif

#ifndef _UINT32_DECLARED
typedef unsigned int uint32;
#define	_UINT32_DECLARED
#endif

#ifndef _UINT16_DECLARED
typedef unsigned short uint16;
#define	_UINT16_DECLARED
#endif

#ifndef _UINT8_DECLARED
typedef unsigned char uint8;
#define	_UINT8_DECLARED
#endif

#ifndef _BOOLEAN_DECLARED
typedef unsigned char boolean;
typedef unsigned char boolean_t;
#define	_BOOLEAN_DECLARED
#endif

#ifndef _SINT64_DECLARED
typedef signed long long sint64;
#define	_SINT64_DECLARED
#endif

#ifndef _SINT32_DECLARED
typedef signed int sint32;
#define	_SINT32_DECLARED
#endif

#ifndef _SINT16_DECLARED
typedef signed short sint16;
#define	_SINT16_DECLARED
#endif

#ifndef _SINT8_DECLARED
typedef signed char sint8;
#define	_SINT8_DECLARED
#endif

#ifndef _FLOAT32_DECLARED
typedef float float32;
#define	_FLOAT32_DECLARED
#endif

#ifndef _FLOAT64_DECLARED
typedef double float64;
#define	_FLOAT64_DECLARED
#endif


/************************************************************/
/* Global Definitions                                       */
/************************************************************/
/** @def NULL
*   @brief NULL definition
*/
#ifndef NULL
    #define NULL ((void *) 0U)
#endif

/** @def TRUE
*   @brief definition for TRUE
*/
#ifndef TRUE
    #define TRUE (boolean)1U
#endif

/** @def FALSE
*   @brief BOOLEAN definition for FALSE
*/
#ifndef FALSE
    #define FALSE (boolean)0U
#endif

/* USER CODE BEGIN (1) */
/* USER CODE END */

#endif /* __HAL_STDTYPES_H__ */
