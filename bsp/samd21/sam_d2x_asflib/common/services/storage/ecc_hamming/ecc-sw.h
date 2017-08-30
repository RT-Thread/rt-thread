/**
 * \file
 *
 * \brief Hamming ECC software implementation.
 *
 * This file contains a software Hamming ECC implementation.
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
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

#ifndef ECC_SW_H_INCLUDED
#define ECC_SW_H_INCLUDED

#include "compiler.h"

/**
 *  These are the possible errors when trying to verify a block of data encoded
 *  using a Hamming code:
 *
 *  \section Errors
 *   - HAMMING_ERROR_SINGLE_BIT
 *   - HAMMING_ERROR_ECC
 *   - HAMMING_ERROR_MULTIPLE_BITS
 */

/*  A single bit was incorrect but has been recovered. */
#define HAMMING_ERROR_SINGLE_BIT         1

/* The original code has been corrupted. */
#define HAMMING_ERROR_ECC               2

/* Multiple bits are incorrect in the data and they cannot be corrected. */
#define HAMMING_ERROR_MULTIPLE_BITS      3


void hamming_compute_256x(const uint8_t *puc_data, uint32_t dw_size,
		uint8_t *puc_code);
uint32_t hamming_verify_256x(uint8_t *puc_data, uint32_t dw_size,
		const uint8_t *puc_code);

#endif /* ECC_SW_H_INCLUDED */
