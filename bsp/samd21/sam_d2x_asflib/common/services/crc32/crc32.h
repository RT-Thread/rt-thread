/**
 * \file
 *
 * \brief 32-bit CRC header.
 *
 * Copyright (C) 2013-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CRC32_H
#define CRC32_H


#include <compiler.h>


/**
 * \defgroup common_services_crc32 CRC-32 calculation service
 *
 * See \ref common_services_crc32_quickstart.
 *
 * This service enables the user to calculate 32-bit CRC using the polynomial
 * defined in the IEEE 802.3 standard, with support for multiple data blocks
 * of arbitrary sizes, and any alignment in memory.
 *
 * @{
 */


//! Type to contain 32-bit CRC.
typedef uint32_t crc32_t;


#ifdef __cplusplus
extern "C" {
#endif

enum status_code crc32_recalculate(const void *data, size_t length, crc32_t *crc);

#ifdef __cplusplus
}
#endif


/**
 * \brief Calculate 32-bit CRC for initial block
 *
 * This function calculates the CRC for the specified data block, which may be
 * first of an arbitrary number of blocks.
 *
 * The actual calculation is done in \ref crc32_recalculate(), while this
 * function just sets up the initial CRC value.
 *
 * \param[in] data Address of data.
 * \param[in] length Length of data.
 * \param[out] crc Address of variable to store the calculated CRC in.
 *
 * \return Status of calculation.
 * \retval STATUS_OK if calculation succeeded.
 * \retval <other> if calculation failed somehow.
 *
 * \note To calculate the CRC of multiple blocks, use this function first, then
 * \ref crc32_recalculate() for the following blocks.
 */
static inline enum status_code crc32_calculate(const void *data, size_t length,
		crc32_t *crc)
{
	*crc = 0;

	return crc32_recalculate(data, length, crc);
}

/** @} */

/**
 * \page common_services_crc32_quickstart Quick Start Guide for CRC-32
 *
 * To use this service, the user must supply a \ref crc32_t "container" variable
 * for the CRC and call \ref crc32_calculate() with the parameters for the first
 * block in the dataset. For subsequent blocks, \ref crc32_recalculate() must be
 * used.
 *
 * \note The user may also initialize the container with a known CRC value and
 * use that as the "seed" for \ref crc32_recalculate().
 *
 *
 * \section common_services_crc32_quickstart_code Example Code
 *
\code
	uint8_t block1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	uint8_t block2[6] = {0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

	crc32_t my_crc;

	crc32_calculate(block1, sizeof(block1), &my_crc);
	crc32_recalculate(block2, sizeof(block2), &my_crc);
\endcode
 *
 */

#endif // CRC32_H