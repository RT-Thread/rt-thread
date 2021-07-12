/*
 * Copyright (C) 2010-2020 Xilinx, Inc.
 * Copyright (c) 2020-2021, WangHuachen
 * All rights reserved.
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-11-30     WangHuachen  the first version
 */
#ifndef XIL_TYPES_H    /* prevent circular inclusions */
#define XIL_TYPES_H    /* by using protection macros */

#include <rtdef.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/************************** Constant Definitions *****************************/

#ifndef TRUE
#  define TRUE        1U
#endif

#ifndef FALSE
#  define FALSE        0U
#endif

#ifndef NULL
#define NULL        0U
#endif

#define XIL_COMPONENT_IS_READY     0x11111111U  /**< In device drivers, This macro will be
                                                 assigend to "IsReady" member of driver
                                                 instance to indicate that driver
                                                 instance is initialized and ready to use. */
#define XIL_COMPONENT_IS_STARTED   0x22222222U  /**< In device drivers, This macro will be assigend to
                                                 "IsStarted" member of driver instance
                                                 to indicate that driver instance is
                                                 started and it can be enabled. */

typedef rt_uint8_t u8;
typedef rt_uint16_t u16;
typedef rt_uint32_t u32;

typedef char char8;
typedef rt_int8_t s8;
typedef rt_int16_t s16;
typedef rt_int32_t s32;
typedef rt_int64_t s64;
typedef rt_uint64_t u64;
typedef int sint32;

typedef intptr_t INTPTR;
typedef uintptr_t UINTPTR;
typedef ptrdiff_t PTRDIFF;


#if !defined(LONG) || !defined(ULONG)
typedef long LONG;
typedef unsigned long ULONG;
#endif

#define ULONG64_HI_MASK    0xFFFFFFFF00000000U
#define ULONG64_LO_MASK    ~ULONG64_HI_MASK

/** @{ */
/**
 * This data type defines an interrupt handler for a device.
 * The argument points to the instance of the component
 */
typedef void (*XInterruptHandler) (void *InstancePtr);

/**
 * This data type defines an exception handler for a processor.
 * The argument points to the instance of the component
 */
typedef void (*XExceptionHandler) (void *InstancePtr);

/**
 * @brief  Returns 32-63 bits of a number.
 * @param  n : Number being accessed.
 * @return Bits 32-63 of number.
 *
 * @note    A basic shift-right of a 64- or 32-bit quantity.
 *          Use this to suppress the "right shift count >= width of type"
 *          warning when that quantity is 32-bits.
 */
#if defined (__aarch64__) || defined (__arch64__)
#define UPPER_32_BITS(n) ((u32)(((n) >> 16) >> 16))
#else
#define UPPER_32_BITS(n) 0U
#endif
/**
 * @brief  Returns 0-31 bits of a number
 * @param  n : Number being accessed.
 * @return Bits 0-31 of number
 */
#define LOWER_32_BITS(n) ((u32)(n))




/************************** Constant Definitions *****************************/

#ifndef TRUE
#define TRUE        1U
#endif

#ifndef FALSE
#define FALSE        0U
#endif

#ifndef NULL
#define NULL        0U
#endif

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
}
#endif

#endif    /* end of protection macro */
/**
* @} End of "addtogroup common_types".
*/
