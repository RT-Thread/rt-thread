/*!
*******************************************************************************
**
** \file      gtypes.h
**
** \brief     GoKe data types and defines.
**
**            This file contains common GoKe data types and defines
**            used by all drivers and applications.
**
**            (C) Copyright 2012-2013 by Goke Microelectronics Shanghai Branch
**
** \attention THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**            ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**            OMMISSIONS.
**
** \version   \$Revision: 1.0 $
**
******************************************************************************/
#ifndef _GTYPES_H_
#define _GTYPES_H_


/* necessary undefines */
#ifdef GFALSE
    #undef GFALSE
#endif
#ifdef GTRUE
    #undef GTRUE
#endif


/* supported MPEG device identifiers (deprecated) */
//#define MB87M2141_DEVICE_ID   0x03010108
//#define MB87M2142_DEVICE_ID   0x03020108


/*!
*******************************************************************************
**
** \name GOKESDK Error Codes
**
*******************************************************************************
*/
/*@{*/
enum
{
    GD_OK = 0,                     //!< No error.
    GD_ERR_BAD_PARAMETER,          //!< Bad parameter passed.
    GD_ERR_OUT_OF_MEMORY,          //!< Memory allocation failed.
    GD_ERR_ALREADY_INITIALIZED,    //!< Device already initialised.
    GD_ERR_NOT_INITIALIZED,        //!< Device not initialised.
    GD_ERR_ALREADY_OPEN,           //!< Device could not be opened again.
    GD_ERR_FEATURE_NOT_SUPPORTED,  //!< Feature or function is not available.
    GD_ERR_TIMEOUT,                //!< Timeout occured.
    GD_ERR_DEVICE_BUSY,            //!< The device is busy.
    GD_ERR_INVALID_HANDLE,         //!< The handle is invalid.
    GD_ERR_OCCUPIED_BY_OTHER,      //!< The handle is invalid.
    GD_ERR_NO_DEVICE_DETECT,       //!< The handle is invalid.
    // Add by Steven Yu 2013.05.27
    GD_ERR_SEMAPHORE_CREATE,       //!< Semaphore could not be created.
    GD_ERR_UNSUPPORTED_VERSION,    //!< The driver's used version is not supported.
    GD_ERR_MAILQUEUE_CREATE,       //!< Mailqueue coult not be created.
    GD_ERR_ERR_NOT_OPEN,           //!< Device/handle is not open.
    GD_ERR_CRC32_MISMATCH,         //!< Generic CRC32 mismatch detection.
    GD_ERR_THREAD_CREATE,          //!< Thread could not be created.
    GD_ERR_TABLE_OVERFLOW,         //!< Memory allocation failed.
    GD_ERR_NOT_ALLOWED,            //!< Not allowed in interrupt context
    GD_ERR_HANDLE_DESTROYED,       //!< Handle destroyed in the meantime
    GD_ERR_BUFFER_EMPTY,           //!< The buffer is empty
    GD_ERR_BUFFER_OVERFLOW,        //!< The buffer is overflow
    // End
};
/*@}*/


/*!
*******************************************************************************
**
** \name GOKESDK Data Types
**
*******************************************************************************
*/
/*@{*/
typedef unsigned char        U8;         //!< 8 bit unsigned integer.
typedef unsigned short       U16;        //!< 16 bit unsigned integer.
typedef unsigned long        U32;        //!< 32 bit unsigned integer.
typedef unsigned long long   U64;        //!< 64 bit unsigned integer.

typedef unsigned char        u8;         //!< 8 bit unsigned integer.
typedef unsigned short       u16;        //!< 16 bit unsigned integer.
typedef unsigned long        u32;        //!< 32 bit unsigned integer.
typedef unsigned long long   u64;        //!< 64 bit unsigned integer.

typedef signed char          S8;         //!< 8 bit signed integer.
typedef signed short         S16;        //!< 16 bit signed integer.
typedef signed long          S32;        //!< 32 bit signed integer.
typedef signed long long     S64;        //!< 64 bit signed integer.

typedef signed char          s8;         //!< 8 bit signed integer.
typedef signed short         s16;        //!< 16 bit signed integer.
typedef signed long          s32;        //!< 32 bit signed integer.
typedef signed long long     s64;        //!< 64 bit signed integer.

typedef unsigned long        GERR;       //!< GOKESDK error/return code.
typedef unsigned long        GD_HANDLE;  //!< GOKESDK handle.

typedef unsigned int    	UINT32;
typedef signed long         INT32;
typedef unsigned char       UC8; 


/*! \brief Defines a GOKESDK boolean. */
#ifndef GTYPES_NO_BOOL
typedef enum
{
    GFALSE = 0,  //!< Logical false.
    GTRUE  = 1   //!< Logical true.
} GBOOL;
#endif
/*@}*/


/*!
*******************************************************************************
**
** \brief Defines a GOKESDK null.
**
*******************************************************************************
*/
#ifndef NULL
    #define NULL 0
#endif

/*!
*******************************************************************************
**
** \brief Macro for entering a critical section.
**
**        GD_EnterCritical() stores the current value of the status
**        register in the given variable where GD_LeaveCritical() uses
**        the given value to reset the flags to a previously stored value.
**
**        Usage:
**
** \code
**             U32 status;
**
**             ...
**             GD_EnterCritical( status );
**             ...
**             ... perform some global variable access
**             ...
**             GD_LeaveCritical( status );
** \endcode
**
** \sa    GD_LeaveCritical()
**
*******************************************************************************
*/
//#define GD_EnterCritical(varname)   varname=_lr(0);_flag(0)

/*!
*******************************************************************************
**
** \brief Macro for leaving a critical section.
**
** \sa    GD_EnterCritical()
**
*******************************************************************************
*/
//#define GD_LeaveCritical(varname)   _flag((varname>>25)&6)


/*
*******************************************************************************
**
** Defines the keyword for inlining a function.
**
*******************************************************************************
*/
#if defined(__HIGHC__)
#define GINLINE _Inline
#else
#if defined(__GNUC__)
#define GINLINE __inline__
#else
#define GINLINE __inline
#endif
#endif


/*
*******************************************************************************
**
** Interrupt service handler
**
** NOTE: In normal configuration all drivers use the Metaware C-type
** '_Interrut1/2' for interrupt handlers. This type allows automatic
** push/pop operations for ISR and exit the ISR with the necessary
** ilink1/2 branch. You may customize this with your own interrupt
** handler just calling the driver ISR then with 'void'
**
*******************************************************************************
*/
//#define GISR_IS_INTERRUPT        /* 'Special'-_Interrut1/2' Int-Handlers */
//#define GISR_IS_VOID             /* 'void'-functions for Int-Handlers */
#if defined(__GNUC__)
    #define GISR1 void             /* customize C-Interrupt handler */
    #define GISR2 void
#else
    #define GISR1 _Interrupt1
    #define GISR2 _Interrupt2
#endif

//#define CPU_VOID_MEM_SWAP 0x80000000

/*
*******************************************************************************
**
** Special redefinitions for the GNU C compiler.
**
*******************************************************************************
*/
#if defined(__HIGHC__)
    extern unsigned int   _cpu_lpcount(unsigned int val);
    #define _lpcount(val) _cpu_lpcount(val)
#endif
#ifdef _ARC
    #define _sr(val,reg)  *((volatile U32 *)reg) = val
    #define _lr(reg)      *((volatile U32 *)reg)
    #define _flag(val)    (val)
    #define _lpcount(val) (val)
    #define _ASM          __asm
    #define _Interrupt1   void
    #define _Interrupt2   void
    #define _Unaligned
#endif

#define _ASM          __asm


/*
*******************************************************************************
**
** Special defines to access special CPU registers from C code.
**
** Usage:
**   void myfunction()
**   {
**       register U32 varname __USE_CPU_REGISTER__(24);
**       :
**       :
**   }
**
*******************************************************************************
*/
#if defined(__HIGHC__)
    #define __USE_CPU_REGISTER__(name) ==name
#endif
#if defined(__GNUC__)
    #define __makestring(val)          #val
    #define __concat(val1,val2)        __makestring( val1 ## val2 )
    #define __USE_CPU_REGISTER__(name) asm( __concat(r,name) )
#endif

/*
*******************************************************************************
**
** Special defines to disable and enable bypassing the cache when
** accessing data through volatile pointers. All GOKESDK drivers assume
** that this behaviour is enabled by default.
**
*******************************************************************************
*/
#if defined(__HIGHC__)
    #define G_VOLATILE_CACHE_BYPASS_OFF #pragma Off(Volatile_cache_bypass)
    #define G_VOLATILE_CACHE_BYPASS_ON  #pragma On(Volatile_cache_bypass)
#endif
#if defined(__GNUC__)
    #define G_VOLATILE_CACHE_BYPASS_OFF
    #define G_VOLATILE_CACHE_BYPASS_ON
#endif


#endif /* _GTYPES_H_ */
