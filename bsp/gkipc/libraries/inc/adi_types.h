/*!
*****************************************************************************
** \file        ./adi/inc/adi_types.h
**
** \version     $Id: adi_types.h 2 2014-08-07 07:42:50Z huangjunlei $
**
** \brief       adapte driver interface type define
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/

#ifndef _ADI_TYPES_H_
#define _ADI_TYPES_H_

#include "adi_sys_error.h"

/*!
*******************************************************************************
** \brief ADI type define
*******************************************************************************
*/

typedef unsigned char       GADI_U8;         /*!< 8 bit unsigned integer. */
typedef unsigned short      GADI_U16;        /*!< 16 bit unsigned integer. */
typedef unsigned long       GADI_U32;        /*!< 32 bit unsigned integer. */
typedef unsigned long long  GADI_U64;        /*!< 64 bit unsigned integer. */
typedef signed char         GADI_S8;         /*!< 8 bit signed integer. */
typedef signed short        GADI_S16;        /*!< 16 bit signed integer. */
typedef signed long         GADI_S32;        /*!< 32 bit signed integer. */
typedef signed long long    GADI_S64;        /*!< 64 bit unsigned integer. */
typedef signed long         GADI_ERR;        /*!< error code type .*/
typedef unsigned long       GADI_HANDLE;     /*!< 32 bit unsigned integer. */
typedef char                GADI_CHAR;       /*!< char */
typedef void                GADI_VOID;       /*!< void*/

/*! common handle type */
typedef void*            GADI_SYS_HandleT;

/*! semaphore handle type */
typedef unsigned long    GADI_SYS_SemHandleT;

/*! thread handle type */
typedef unsigned long    GADI_SYS_ThreadHandleT;

/*! mutex handle type */
typedef unsigned long    GADI_SYS_MutexHandleT;

/*! cond handle type */
typedef unsigned long    GADI_SYS_ConHandleT;


/*!
*******************************************************************************
** \brief ADI BOOL enum
*******************************************************************************
*/
typedef enum {
    GADI_FALSE = 0,  /*!< Logical false. */
    GADI_TRUE  = 1   /*!< Logical true. */
} GADI_BOOL;


#if defined(__HIGHC__)
    #undef NULL
    #define NULL 0
#else

#ifndef NULL
    #define NULL 0  /*!< NULL define to 0. */
#endif
#endif


/*!
*******************************************************************************
** \brief Common inline key word.
*******************************************************************************
*/
#if defined(__HIGHC__)
#define FINLINE _Inline
#else
#define FINLINE inline
#endif


#endif /* _ADI_TYPES_H_ */

