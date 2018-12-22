/**
 * \file
 *
 * \brief 32-bit CRC implementation.
 *
 * Copyright (C) 2014-2015 Atmel Corporation. All rights reserved.
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

#include "crc32.h"
#include <status_codes.h>


/**
 * Convenience typedef for words.
 *
 * \note This type has an architecture dependent size, and is used to optimize
 * the CRC algorithm with regards to the number of databus accesses.
 */
typedef unsigned int word_t;

/** Polynomial for 32-bit CRC in IEEE 802.3. */
#define CRC32_POLYNOMIAL     0xEDB88320UL

/** Convenience macro for inverting the CRC. */
#define COMPLEMENT_CRC(c)    ((c) ^ 0xffffffffUL)

/** Convenience macro for size of a word. */
#define WORD_SIZE            (sizeof(word_t))

/** Bitmask for word-aligning an address. */
#define WORD_ALIGNMENT_MASK  ~((uintptr_t)WORD_SIZE - 1)


/**
 * \internal
 * \brief Recalculate 32-bit CRC for bytes within a word
 *
 * \param[in] data Data to recalculate for.
 * \param[in] crc Initial/current CRC value.
 * \param[in] bytes Number of data bytes in word.
 *
 * \return New CRC value.
 *
 * \attention This implementation assumes a little-endian architecture.
 */
static inline crc32_t _crc32_recalculate_bytes_helper(word_t data,
		crc32_t crc, uint_fast8_t bytes)
{
	uint_fast8_t bit;

	crc ^= data;

	for (bit = 8 * bytes; bit > 0; bit--) {
		if (crc & 1) {
			crc = (crc >> 1) ^ CRC32_POLYNOMIAL;
		} else {
			crc >>= 1;
		}
	}

	return crc;
}

/**
 * \brief Recalculate 32-bit CRC for another block
 *
 * This function recalculates the CRC according to the polynomial
 * \ref CRC32_POLYNOMIAL for the specified data block and initial CRC value.
 *
 * To reduce the number of databus accesses and thus speed up the calculation,
 * the algorithm is tuned to work with words as much as possible.
 *
 * \param[in] data Address of data.
 * \param[in] length Length of data.
 * \param[in,out] crc Address of variable containing current CRC, and to store
 * recalculated CRC in.
 *
 * \return Status of calculation.
 * \retval STATUS_OK if calculation succeeded.
 * \retval <other> if calculation failed or could not be started.
 *
 * \note To calculate the CRC of multiple blocks, use \ref crc32_calculate()
 * first, then this function for the following blocks.
 *
 * \attention This implementation assumes a little-endian architecture.
 */
enum status_code crc32_recalculate(const void *data, size_t length, crc32_t *crc)
{
	const word_t *word_ptr =
			(word_t *)((uintptr_t)data & WORD_ALIGNMENT_MASK);
	size_t temp_length;
	crc32_t temp_crc = COMPLEMENT_CRC(*crc);
	word_t word;

	// Calculate for initial bytes to get word-aligned
	if (length < WORD_SIZE) {
		temp_length = length;
	} else {
		temp_length = ~WORD_ALIGNMENT_MASK & (WORD_SIZE - (uintptr_t)data);
	}

	if (temp_length) {
		length -= temp_length;

		word = *(word_ptr++);
		word >>= 8 * (WORD_SIZE - temp_length);
		temp_crc = _crc32_recalculate_bytes_helper(word, temp_crc, temp_length);
	}

	// Calculate for whole words, if any
	temp_length = length & WORD_ALIGNMENT_MASK;

	if (temp_length) {
		length -= temp_length;
		temp_length /= WORD_SIZE;

		while (temp_length--) {
			word = *(word_ptr++);
			temp_crc = _crc32_recalculate_bytes_helper(word, temp_crc, WORD_SIZE);
		}
	}

	// Calculate for tailing bytes
	if (length) {
		word = *word_ptr;
		word &= 0xffffffffUL >> (8 * (WORD_SIZE - length));
		temp_crc = _crc32_recalculate_bytes_helper(word, temp_crc, length);
	}

	*crc = COMPLEMENT_CRC(temp_crc);

	return STATUS_OK;
}