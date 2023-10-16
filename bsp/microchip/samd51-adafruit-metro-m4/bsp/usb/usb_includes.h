/**
 * \file
 *
 * \brief USB Include Header Files.
 *
 * This file contains the USB definitions and data structures provided by the
 * USB 2.0 specification.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 */

#ifndef _USB_INCLUDES_H_
#define _USB_INCLUDES_H_

#ifdef USB_USER_INCLUDES

#include "usb_user_includes.h"

#else
/* Include START headers */
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <utils.h>
#include <utils_list.h>
#include <utils_assert.h>
#include <hal_atomic.h>

typedef uint16_t le16_t;
typedef uint32_t le32_t;
typedef uint16_t be16_t;
typedef uint32_t be32_t;

#if (defined __GNUC__) || (defined __CC_ARM)
#define is_constant(exp) __builtin_constant_p(exp)
#else
#define is_constant(exp) (0)
#endif

/*! \brief Toggles the endianism of \a u16 (by swapping its bytes).
 *
 * \param u16 U16 of which to toggle the endianism.
 *
 * \return Value resulting from \a u16 with toggled endianism.
 *
 * \note More optimized if only used with values known at compile time.
 */
#define swap_u16(u16) ((uint16_t)(((uint16_t)(u16) >> 8) | ((uint16_t)(u16) << 8)))

/*! \brief Toggles the endianism of \a u32 (by swapping its bytes).
 *
 * \param u32 U32 of which to toggle the endianism.
 *
 * \return Value resulting from \a u32 with toggled endianism.
 *
 * \note More optimized if only used with values known at compile time.
 */
#if (defined __GNUC__)
#define swap_u32(u32)                                                                                                  \
	(is_constant(u32)                                                                                                  \
	     ? ((uint32_t)(((uint32_t)swap_u16((uint32_t)(u32) >> 16)) | ((uint32_t)swap_u16((uint32_t)(u32)) << 16)))     \
	     : ((uint32_t)__builtin_bswap32((uint32_t)(u32))))
#else
#define swap_u32(u32)                                                                                                  \
	((uint32_t)(((uint32_t)swap_u16((uint32_t)(u32) >> 16)) | ((uint32_t)swap_u16((uint32_t)(u32)) << 16)))
#endif

/** Get a value from/to LE16 data */
#define LE16(x) (x)
/** Get a value from/to LE32 data */
#define LE32(x) (x)
/** Get a value from/to BE16 data */
#define BE16(x) swap_u16(x)
/** Get a value from/to BE32 data */
#define BE32(x) swap_u32(x)

/** Get byte 0 for BE 16-bit value */
#define BE16B0(a) ((uint8_t)((a) >> 8))
/** Get byte 1 for BE 16-bit value */
#define BE16B1(a) ((uint8_t)((a) >> 0))

/** Get byte 0 for BE 32-bit value */
#define BE32B0(a) ((uint8_t)((a) >> 24))
/** Get byte 1 for BE 32-bit value */
#define BE32B1(a) ((uint8_t)((a) >> 16))
/** Get byte 2 for BE 32-bit value */
#define BE32B2(a) ((uint8_t)((a) >> 8))
/** Get byte 3 for BE 32-bit value */
#define BE32B3(a) ((uint8_t)((a) >> 0))

/** Get byte 0 for LE 16-bit value */
#define LE16B0(a) ((uint8_t)((a) >> 0))
/** Get byte 1 for LE 16-bit value */
#define LE16B1(a) ((uint8_t)((a) >> 8))

/** Get byte 0 for LE 32-bit value */
#define LE32B0(a) ((uint8_t)((a) >> 0))
/** Get byte 1 for LE 32-bit value */
#define LE32B1(a) ((uint8_t)((a) >> 8))
/** Get byte 2 for LE 32-bit value */
#define LE32B2(a) ((uint8_t)((a) >> 16))
/** Get byte 3 for LE 32-bit value */
#define LE32B3(a) ((uint8_t)((a) >> 24))

#endif /* USB_USER_INCLUDES */

#endif /* _USB_INCLUDES_H_ */
