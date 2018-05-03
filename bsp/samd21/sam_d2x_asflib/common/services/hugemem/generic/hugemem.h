/**
 * \file
 *
 * \brief Generic implementation of huge data memory access
 *
 * Copyright (c) 2010-2015 Atmel Corporation. All rights reserved.
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
#ifndef GENERIC_HUGEMEM_H_INCLUDED
#define GENERIC_HUGEMEM_H_INCLUDED

#include <stdint.h>
#include <string.h>

/**
 * \weakgroup hugemem_group
 * @{
 */

/**
 * \internal
 * \defgroup hugemem_generic_group Generic hugemem implementation.
 *
 * These functions are needed for code compatibility between 8- and 32-bit AVR,
 * as well as a different application configurations on 8-bit AVR, i.e., if huge
 * data memory is optional.
 */

typedef void * hugemem_ptr_t;

#define HUGEMEM_NULL    NULL

static inline uint8_t hugemem_read8(const hugemem_ptr_t from)
{
	return *(uint8_t *)from;
}

static inline uint16_t hugemem_read16(const hugemem_ptr_t from)
{
	return *(uint16_t *)from;
}

static inline uint32_t hugemem_read32(const hugemem_ptr_t from)
{
	return *(uint32_t *)from;
}

static inline void hugemem_read_block(void *to, const hugemem_ptr_t from,
		size_t size)
{
	memcpy(to, from, size);
}

static inline void hugemem_write8(hugemem_ptr_t to, uint8_t val)
{
	*(uint8_t *)to = val;
}

static inline void hugemem_write16(hugemem_ptr_t to, uint16_t val)
{
	*(uint16_t *)to = val;
}


static inline void hugemem_write32(hugemem_ptr_t to, uint32_t val)
{
	*(uint32_t *)to = val;
}

static inline void hugemem_write_block(hugemem_ptr_t to, const void *from,
		size_t size)
{
	memcpy(to, from, size);
}

//@}

#endif /* GENERIC_HUGEMEM_H */
