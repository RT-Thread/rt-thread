/**
 * \file
 *
 * \brief Special user data area access
 *
 * Copyright (c) 2016-2018 Microchip Technology Inc. and its subsidiaries.
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
 *
 */

#ifndef _HPL_USER_DATA_H_INCLUDED
#define _HPL_USER_DATA_H_INCLUDED

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Read data from user data area
 *
 * The user data area could be the area that stores user data that is not erased
 * with the flash contents, e.g.,
 * - NVM Software Calibration Area of SAM D/L/C family
 * - User Signature of SAM E/S/V 70
 *
 * \param[in]  base   The base address of the user area
 * \param[in]  offset The byte offset of the data to be read inside the area
 * \param[out] buf    Pointer to buffer to place the read data
 * \param[in]  size   Size of data in number of bytes
 *
 * \return Operation status or bytes read.
 * \retval ERR_NONE Data read successfully
 * \retval ERR_UNSUPPORTED_OP base address not in any supported user area
 * \retval ERR_BAD_ADDRESS offset not in right area
 * \retval ERR_INVALID_ARG offset and size exceeds the right area
 */
int32_t _user_area_read(const void *base, const uint32_t offset, uint8_t *buf, const uint32_t size);

/**
 * \brief Read no more than 32 bits data from user data area
 *
 * When reading bits, the bitfield can cross 32-bis boundaries.
 *
 * \param[in] base       The base address of the user area
 * \param[in] bit_offset Offset in number of bits
 * \param[in] n_bits     Number of bits to read
 * \return data read, assert if anything wrong (address not in user area
 *         offset, size error, etc.).
 */
uint32_t _user_area_read_bits(const void *base, const uint32_t bit_offset, const uint8_t n_bits);

/**
 * \brief Write data to user data area
 *
 * The user data area could be the area that stores user data that is not erased
 * with the flash contents, e.g.,
 * - NVM Software Calibration Area of SAM D/L/C family
 * - User Signature of SAM E/S/V 70
 *
 * When assigned offset and size exceeds the data area, error is reported.
 *
 * \param[out] base  The base address of the user area
 * \param[in]  offset The offset of the data to be written inside the area
 * \param[in]  buf    Pointer to buffer to place the written data
 * \param[in]  size   Size of data in number of bytes
 *
 * \return Operation status or bytes writting.
 * \retval ERR_NONE Data written successfully
 * \retval ERR_UNSUPPORTED_OP base address not in any supported user area
 * \retval ERR_DENIED Security bit is set
 * \retval ERR_BAD_ADDRESS offset not in right area
 * \retval ERR_INVALID_ARG offset and size exceeds the right area
 */
int32_t _user_area_write(void *base, const uint32_t offset, const uint8_t *buf, const uint32_t size);

/**
 * \brief Write no more than 32 bits data to user data area
 *
 * When writting bits, the bitfield can cross 32-bis boundaries.
 *
 * \param[out] base       The base address of the user area
 * \param[in]  bit_offset Offset in number of bits
 * \param[in]  bits       The data content
 * \param[in]  n_bits     Number of bits to write
 * \return Operation result
 * \retval ERR_NONE Data written successfully
 * \retval ERR_UNSUPPORTED_OP base address not in any supported user area
 * \retval ERR_DENIED Security bit is set
 * \retval ERR_BAD_ADDRESS offset not in right area
 * \retval ERR_INVALID_ARG offset and size exceeds the right area
 */
int32_t _user_area_write_bits(void *base, const uint32_t bit_offset, const uint32_t bits, const uint8_t n_bits);

#ifdef __cplusplus
}
#endif

#endif /* _HPL_USER_DATA_H_INCLUDED */
