/**************************************************************************************
* Copyright (c) 2016-2017, ARM Limited or its affiliates. All rights reserved         *
*                                                                                     *
* This file and the related binary are licensed under the following license:          *
*                                                                                     *
* ARM Object Code and Header Files License, v1.0 Redistribution.                      *
*                                                                                     *
* Redistribution and use of object code, header files, and documentation, without     *
* modification, are permitted provided that the following conditions are met:         *
*                                                                                     *
* 1) Redistributions must reproduce the above copyright notice and the                *
*    following disclaimer in the documentation and/or other materials                 *
*    provided with the distribution.                                                  *
*                                                                                     *
* 2) Unless to the extent explicitly permitted by law, no reverse                     *
*    engineering, decompilation, or disassembly of is permitted.                      *
*                                                                                     *
* 3) Redistribution and use is permitted solely for the purpose of                    *
*    developing or executing applications that are targeted for use                   *
*    on an ARM-based product.                                                         *
*                                                                                     *
* DISCLAIMER. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND                  *
* CONTRIBUTORS "AS IS." ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT             *
* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT,        *
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          *
* COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED            *
* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR              *
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF              *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING                *
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                  *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                        *
**************************************************************************************/


#ifndef __SSI_PAL_COMPILER_H__
#define __SSI_PAL_COMPILER_H__

/*!
@file
@brief This file contains compiler related definitions.
@defgroup ssi_pal_compiler CryptoCell PAL platform dependant compiler specific definitions
@{
@ingroup ssi_pal

*/

#ifdef __GNUC__

/************************ Defines ******************************/

/*! Associate a symbol with a link section. */
#define SASI_PAL_COMPILER_SECTION(sectionName)  __attribute__((section(sectionName)))

/*! Mark symbol as used, i.e., prevent garbage collector from dropping it. */
#define SASI_PAL_COMPILER_KEEP_SYMBOL __attribute__((used))

/*! Make given data item aligned (alignment in bytes). */
#define SASI_PAL_COMPILER_ALIGN(alignement)  __attribute__((aligned(alignement)))

/*! Mark function that never returns. */
#define SASI_PAL_COMPILER_FUNC_NEVER_RETURNS __attribute__((noreturn))

/*! Prevent function from being inlined */
#define SASI_PAL_COMPILER_FUNC_DONT_INLINE __attribute__((noinline))

/*! Given data type may cast (alias) another data type pointer. */
/* (this is used for "superclass" struct casting)             */
#define SASI_PAL_COMPILER_TYPE_MAY_ALIAS __attribute__((__may_alias__))

/*! Get sizeof for a structure type member. */
#define SASI_PAL_COMPILER_SIZEOF_STRUCT_MEMBER(type_name, member_name) \
	sizeof(((type_name *)0)->member_name)

/*! Assertion. */
#define SASI_ASSERT_CONCAT_(a, b) a##b
#define SASI_ASSERT_CONCAT(a, b) SASI_ASSERT_CONCAT_(a, b)
#define SASI_PAL_COMPILER_ASSERT(cond, message) \
	enum { SASI_ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(cond)) }

#elif defined(__ARM_DSM__) || defined(__CC_ARM)
#define inline 
/*! Associate a symbol with a link section. */
#define SASI_PAL_COMPILER_SECTION(sectionName)  __attribute__((section(sectionName)))

/*! Mark symbol as used, i.e., prevent garbage collector from dropping it. */
#define SASI_PAL_COMPILER_KEEP_SYMBOL __attribute__((used))

/*! Make given data item aligned (alignment in bytes). */
#define SASI_PAL_COMPILER_ALIGN(alignement)  __attribute__((aligned(alignement)))

/*! Mark function that never returns. */
#define SASI_PAL_COMPILER_FUNC_NEVER_RETURNS __attribute__((noreturn))

/*! Prevent function from being inlined. */
#define SASI_PAL_COMPILER_FUNC_DONT_INLINE __attribute__((noinline))

/*! Given data type may cast (alias) another data type pointer. */
/* (this is used for "superclass" struct casting)             */
#define SASI_PAL_COMPILER_TYPE_MAY_ALIAS __attribute__((__may_alias__))

/*! Get sizeof for a structure type member. */
#define SASI_PAL_COMPILER_SIZEOF_STRUCT_MEMBER(type_name, member_name) \
	sizeof(((type_name *)0)->member_name)

/*! Assertion. */
#define SASI_ASSERT_CONCAT_(a, b) a##b
#define SASI_ASSERT_CONCAT(a, b) SASI_ASSERT_CONCAT_(a, b)
#define SASI_PAL_COMPILER_ASSERT(cond, message) \
	enum { SASI_ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(cond)) }

#elif defined(__ARM_DS__)
#define inline
/*! Associate a symbol with a link section. */
#define SASI_PAL_COMPILER_SECTION(sectionName)  __attribute__((section(sectionName)))

/*! Mark symbol as used, i.e., prevent garbage collector from dropping it. */
#define SASI_PAL_COMPILER_KEEP_SYMBOL __attribute__((used))

/*! Make given data item aligned (alignment in bytes). */
#define SASI_PAL_COMPILER_ALIGN(alignement)  __attribute__((aligned(alignement)))

/*! Mark function that never returns. */
#define SASI_PAL_COMPILER_FUNC_NEVER_RETURNS __attribute__((noreturn))

/*! Prevent function from being inlined. */
#define SASI_PAL_COMPILER_FUNC_DONT_INLINE __attribute__((noinline))

/*! Given data type may cast (alias) another data type pointer. */
/* (this is used for "superclass" struct casting)             */
#define SASI_PAL_COMPILER_TYPE_MAY_ALIAS 

/*! Get sizeof for a structure type member. */
#define SASI_PAL_COMPILER_SIZEOF_STRUCT_MEMBER(type_name, member_name) \
	sizeof(((type_name *)0)->member_name)

/*! Assertion. */
#define SASI_ASSERT_CONCAT_(a, b) a##b
#define SASI_ASSERT_CONCAT(a, b) SASI_ASSERT_CONCAT_(a, b)
#define SASI_PAL_COMPILER_ASSERT(cond, message) \
	enum { SASI_ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(cond)) }

#elif defined(__ICCARM__)

/************************ Defines ******************************/

/*! Associate a symbol with a link section. */
#define SASI_PAL_COMPILER_SECTION(sectionName)  __attribute__((section(sectionName)))

/*! Mark symbol as used, i.e., prevent garbage collector from dropping it. */
#define SASI_PAL_COMPILER_KEEP_SYMBOL __attribute__((used))

/*! Make given data item aligned (alignment in bytes). */
#define STRING_PRAGMA(x) _Pragma(#x)
//#define SASI_PAL_COMPILER_ALIGN(n) STRING_PRAGMA(data_alignment = n)
#define SASI_PAL_COMPILER_ALIGN(n)

/*! Mark function that never returns. Not implemented */
#define SASI_PAL_COMPILER_FUNC_NEVER_RETURNS

/* Prevent function from being inlined */
#define SASI_PAL_COMPILER_FUNC_DONT_INLINE STRING_PRAGMA(optimize = no_inline)

/*! Given data type may cast (alias) another data type pointer. */
/* (this is used for "superclass" struct casting). Not implemented */
#define SASI_PAL_COMPILER_TYPE_MAY_ALIAS 

/*! Get sizeof for a structure type member. */
#define SASI_PAL_COMPILER_SIZEOF_STRUCT_MEMBER(type_name, member_name) \
	sizeof(((type_name *)0)->member_name)

/*! Assertion. */
#define SASI_ASSERT_CONCAT_(a, b) a##b
#define SASI_ASSERT_CONCAT(a, b) SASI_ASSERT_CONCAT_(a, b)

#define SASI_PAL_COMPILER_ASSERT(cond, message) \
	enum { SASI_ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(cond)) }


#else    
#error Unsupported compiler.
#endif
/**
@}
 */
#endif /*__SSI_PAL_COMPILER_H__*/
