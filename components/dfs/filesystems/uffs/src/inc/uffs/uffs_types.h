/*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  
  Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

  UFFS is free software; you can redistribute it and/or modify it under
  the GNU Library General Public License as published by the Free Software 
  Foundation; either version 2 of the License, or (at your option) any
  later version.

  UFFS is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
  or GNU Library General Public License, as applicable, for more details.
 
  You should have received a copy of the GNU General Public License
  and GNU Library General Public License along with UFFS; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA  02110-1301, USA.

  As a special exception, if other files instantiate templates or use
  macros or inline functions from this file, or you compile this file
  and link it with other works to produce a work based on this file,
  this file does not by itself cause the resulting work to be covered
  by the GNU General Public License. However the source code for this
  file must still be made available in accordance with section (3) of
  the GNU General Public License v2.
 
  This exception does not invalidate any other reasons why a work based
  on this file might be covered by the GNU General Public License.
*/

#ifndef _UFFS_TYPES_H_
#define _UFFS_TYPES_H_

#ifdef __CDT_PARSER__
#undef __cplusplus
#endif

#ifdef __cplusplus
extern "C"{
#endif

#ifdef _UBASE_
#include <sys/utypes.h>
#endif

/** 
 * \file uffs_types.h
 * \brief basic types used on uffs
 * \author Ricky Zheng
 */

/* basic types */

/** \typedef i8 
 * \brief 8 bit integer
 */
typedef char i8;

/** \typedef u8 
 * \brief 8 bit unsigned integer
 */
typedef unsigned char u8;

/** \typedef i16 
 * \brief 16 bit integer
 */
typedef short int i16;


/** \typedef u16
 * \brief 16 bit unsigned integer
 */
typedef unsigned short int u16;


/** \typedef i32
 * \brief 32 bit integer
 */
typedef int i32;

/** \typedef u32 
 * \brief 32 bit unsigned integer
 */
typedef unsigned int u32;


#ifndef _UBASE_

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

/* boolean type */

/** \typedef UBOOL 
 * \brief boolean type for uffs, the value would be: #U_TRUE or #U_FALSE
 */
typedef int UBOOL;

/** \def U_TRUE 
 * \brief boolean true for uffs
 */
#define U_TRUE (TRUE)


/** \def U_FALSE 
 * \brief boolean false for uffs
 */
#define U_FALSE (FALSE)


/** \typedef URET 
 * \brief return type for uffs, should be #U_FAIL or #U_SUCC
 */
typedef int URET;

/** \def U_FAIL 
 * \brief indicator of fail
 */
#define U_FAIL -1

/** \def U_SUCC 
 * \brief indicator of successful
 */
#define U_SUCC 0

/** \def IS_SUCC(ret) 
 * \brief is it successful ?
 */
#define IS_SUCC(ret) (ret >= 0 ? U_TRUE : U_FALSE)


/** \def IS_FAIL(ret) 
 * \brief is it fail ?
 */
#define IS_FAIL(ret) (ret < 0 ? U_TRUE : U_FALSE)

#ifndef NULL
/** \def NULL 
 * \brief zero for pointer
 */
#define NULL 0
#endif

#endif // _UBASE_


#ifdef __cplusplus
}
#endif


#endif

