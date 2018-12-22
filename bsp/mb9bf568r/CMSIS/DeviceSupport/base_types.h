/*******************************************************************************
* Copyright (C) 2013 Spansion LLC. All Rights Reserved. 
*
* This software is owned and published by: 
* Spansion LLC, 915 DeGuigne Dr. Sunnyvale, CA  94088-3453 ("Spansion").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND 
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with Spansion 
* components. This software is licensed by Spansion to be adapted only 
* for use in systems utilizing Spansion components. Spansion shall not be 
* responsible for misuse or illegal use of this software for devices not 
* supported herein.  Spansion is providing this software "AS IS" and will 
* not be responsible for issues arising from incorrect user implementation 
* of the software.  
*
* SPANSION MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS), 
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING, 
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED 
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED 
* WARRANTY OF NONINFRINGEMENT.  
* SPANSION SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT, 
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT 
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, 
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR 
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA, 
* SAVINGS OR PROFITS, 
* EVEN IF SPANSION HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED 
* FROM, THE SOFTWARE.  
*
* This software may be replicated in part or whole for the licensed use, 
* with the restriction that this Disclaimer and Copyright notice must be 
* included with each copy of this software, whether used in part or whole, 
* at all times.  
*/

/*****************************************************************************/
/** \file base_types.h
 **
 ** Additional base type definitions to stddef.h and stdint.h
 **
 ** History:
 **   - 2013-03-21  1.0  MWi  First version.
 **
 *****************************************************************************/

#ifndef __BASE_TYPES_H__
#define __BASE_TYPES_H__

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include <stddef.h>
#include "stdint.h"
  
/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
#ifndef TRUE
  /** Value is true (boolean_t type) */
  #define TRUE        ((boolean_t) 1)
#endif

#ifndef FALSE
  /** Value is false (boolean_t type) */
  #define FALSE       ((boolean_t) 0)
#endif  

/** Returns the minimum value out of two values */
#define MIN( X, Y )  ((X) < (Y) ? (X) : (Y))

/** Returns the maximum value out of two values */
#define MAX( X, Y )  ((X) > (Y) ? (X) : (Y))

/** Returns the dimension of an array */
#define DIM( X )  (sizeof(X) / sizeof(X[0]))

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/** logical datatype (only values are TRUE and FALSE) */
typedef uint8_t      boolean_t;
  
/** single precision floating point number (4 byte) */
typedef float        float32_t;

/** double precision floating point number (8 byte) */
typedef double       float64_t;

/** ASCCI character for string generation (8 bit) */
typedef char         char_t;

/** function pointer type to void/void function */
typedef void         (*func_ptr_t)(void);

/** function pointer type to void/uint8_t function */
typedef void         (*func_ptr_arg1_t)(uint8_t);

/** generic error codes */
typedef enum en_result
{
    Ok                          = 0,  ///< No error
    Error                       = 1,  ///< Non-specific error code
    ErrorAddressAlignment       = 2,  ///< Address alignment does not match
    ErrorAccessRights           = 3,  ///< Wrong mode (e.g. user/system) mode is set
    ErrorInvalidParameter       = 4,  ///< Provided parameter is not valid
    ErrorOperationInProgress    = 5,  ///< A conflicting or requested operation is still in progress
    ErrorInvalidMode            = 6,  ///< Operation not allowed in current mode
    ErrorUninitialized          = 7,  ///< Module (or part of it) was not initialized properly
    ErrorBufferFull             = 8,  ///< Circular buffer can not be written because the buffer is full
    ErrorTimeout                = 9,  ///< Time Out error occurred (e.g. I2C arbitration lost, Flash time-out, etc.)
    ErrorNotReady               = 10, ///< A requested final state is not reached
    OperationInProgress         = 11  ///< Indicator for operation in progress (e.g. ADC conversion not finished, DMA channel used, etc.)
} en_result_t;

/**
 ******************************************************************************
 ** \brief Level
 ** 
 ** Specifies levels.
 **
 ******************************************************************************/
typedef enum en_level
{
    PDLLow      = 0,  ///< Low level '0'
    PDLHigh     = 1   ///< High level '1'
} en_level_t;

/**
 ******************************************************************************
 ** \brief Generic Flag Code
 ** 
 ** Specifies flags.
 **
 ******************************************************************************/
typedef enum en_flag
{
    PdlClr = 0,       ///< Flag clr '0'
    PdlSet = 1        ///< Flag set '1' 
} en_stat_flag_t, en_int_flag_t;      

/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source)           */
/*****************************************************************************/

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source)             */
/*****************************************************************************/

#endif /* __BASE_TYPES_H__ */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
