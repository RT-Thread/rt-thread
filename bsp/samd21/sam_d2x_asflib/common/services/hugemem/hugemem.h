/**
 * \file
 *
 * \brief Huge data memory space access
 *
 * Copyright (c) 2009-2015 Atmel Corporation. All rights reserved.
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
#ifndef HUGEMEM_H_INCLUDED
#define HUGEMEM_H_INCLUDED

#include <stdint.h>
#include <stddef.h>

#if defined(__AVR32__) || defined(__ICCAVR32__)
# include <generic/hugemem.h>
#elif defined(__AVR__) || defined (__ICCAVR__)
# include <avr8/hugemem.h>
#else
# error Unknown architecture passed to hugemem interface.
# error Expected __AVR32__ or __AVR__.
#endif

/**
 * \defgroup hugemem_group Data in Huge Data Memory Space
 *
 * Due to shortcomings of the GCC compiler for 8-bit AVR, custom functions are
 * needed for access to data beyond the 64 kB boundary, i.e., addresses that
 * are larger than 16-bit.
 *
 * The definition of huge memory space can differ between architectures, so the
 * implementation is architecture specific.
 *
 * This module supplies functions for copying a number of bytes between huge
 * and 64 kB data memory space, and is needed solely for code compatibility
 * across compilers.
 *
 * @{
 */

/**
 * \typedef hugemem_ptr_t
 *
 * \brief Type to use for pointers to huge memory.
 */

/**
 * \def HUGEMEM_NULL
 *
 * \brief Hugemem null pointer, similar to NULL, but works across different
 * platforms.
 */

/**
 * \fn uint_fast8_t hugemem_read8(const hugemem_ptr_t from)
 *
 * \brief Read 8-bit value stored at huge memory address \a from.
 */

/**
 * \fn uint_fast16_t hugemem_read16(const hugemem_ptr_t from)
 *
 * \brief Read 16-bit value stored at huge memory address \a from.
 */

/**
 * \fn void hugemem_read_block(void *to, const hugemem_ptr_t from, size_t size)
 *
 * \brief Read \a size bytes from huge memory address \a from into buffer at
 * address \a to.
 */

/**
 * \fn uint_fast32_t hugemem_read32(const hugemem_ptr_t from)
 *
 * \brief Read 32-bit value stored at huge memory address \a from.
 */

/**
 * \fn void hugemem_write8(hugemem_ptr_t to, uint_fast8_t val)
 *
 * \brief Write 8-bit value \a val to huge memory address \a to.
 */

/**
 * \fn void hugemem_write16(hugemem_ptr_t to, uint_fast16_t val)
 *
 * \brief Write 16-bit value \a val to huge memory address \a to.
 */

/**
 * \fn void hugemem_write32(hugemem_ptr_t to, uint_fast32_t val)
 *
 * \brief Write 32-bit value \a val to huge memory address \a to.
 */

/**
 * \fn void hugemem_write_block(hugemem_ptr_t to, const void *from, size_t size)
 *
 * \brief Write \a size bytes from buffer at address \a from to huge memory
 * address \a to.
 */

//@}

#endif /* HUGEMEM_H_INCLUDED */
