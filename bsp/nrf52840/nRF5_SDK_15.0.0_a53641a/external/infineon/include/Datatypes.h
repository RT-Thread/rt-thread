/**
* \copyright
* Copyright (c) 2018, Infineon Technologies AG
* All rights reserved.                                                         
*
* This software is provided with terms and conditions as specified in OPTIGA(TM) Trust X Evaluation Kit License Agreement.
* \endcopyright
*
* \author Infineon AG
*
* \file
*
* \brief This file contains the type definitions for the fundamental data types.
*
* 
*
*/

#ifndef _DATATYPES_H_
#define _DATATYPES_H_

/******************************************************************************
* required includes
* Setup common include order for the used types and definitions
******************************************************************************/
#include <stdlib.h>   
#include <string.h>
#include <stdint.h>

/******************************************************************************
* DataTypes.h
******************************************************************************/

/******************************************************************************
* defines
******************************************************************************/

/// @cond hidden
#ifndef _OPTIGA_EXPORTS_DLLEXPORT_H_
#define _OPTIGA_EXPORTS_DLLEXPORT_H_

#if defined(WIN32) || defined(_WIN32)

#ifdef OPTIGA_LIB_EXPORTS
#define LIBRARY_EXPORTS __declspec(dllexport)
#elif defined(OPTIGA_LIB_EXCLUDE_IMPORT)
#define LIBRARY_EXPORTS 
#else
#define LIBRARY_EXPORTS __declspec(dllimport)
#endif  // OPTIGA_LIB_EXPORTS

#else
#define LIBRARY_EXPORTS
#endif //WIN32

#endif /*_OPTIGA_EXPORTS_DLLEXPORT_H_*/
/// @endcond 

/// Definition for false 
#ifndef FALSE
#define FALSE               0
#endif

/// Definition for true 
#ifndef TRUE
#define TRUE                1
#endif

/******************************************************************************
* fundamental typedefs
******************************************************************************/

/// Typedef for one byte integer
typedef char char_t;

/// Typedef for native byte pointer
typedef uint8_t* puint8_t;

/// Typedef for a 4 byte unsigned integer pointer
typedef uint32_t* puint32_t;

/// Typedef for unsigned word pointer
typedef uint16_t* puint16_t ;

/// Typedef for a void
typedef void			Void;

/// Typedef for a double word
typedef double			double_t;

/// Typedef for a float
typedef float			float_t;

/// Typedef for a boolean
typedef uint8_t         bool_t;

/// Typedef for Handle
typedef Void* hdl_t;

/// typedef for host library status
typedef uint16_t host_lib_status_t;
    
/**
 * \brief Structure to specify a byte stream consisting of length and data
 *        pointer.
 */
typedef struct sbBlob_d
{
    /// Length of the byte stream
    uint16_t wLen;

    /// Pointer to byte array which contains the data stream
    uint8_t *prgbStream;
} sbBlob_d;

/// typedef for application event handler
typedef void (*app_event_handler_t)(void* upper_layer_ctx, host_lib_status_t event);

#ifndef _STATIC_H
#define _STATIC_H static
#endif
#endif /* __DATATYPES_H__ */
