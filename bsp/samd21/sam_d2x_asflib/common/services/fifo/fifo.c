/**
 * \file
 *
 * \brief This file controls the software FIFO management.
 *
 * These functions manages FIFOs thanks to simple a API. The FIFO can
 * be 100% full thanks to a double-index range implementation. For example,
 * a FIFO of 4 elements can be implemented: the FIFO can really hold up to 4
 * elements.
 * This is particularly well suited for any kind of application needing a lot of
 * small FIFO.
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

#include "fifo.h"

int fifo_init(fifo_desc_t *fifo_desc, void *buffer, uint8_t size)
{
	// Check the size parameter. It must be not null...
	Assert (size);

	// ... must be a 2-power ...
	Assert (!(size & (size - 1)));

	// ... and must fit in a uint8_t. Since the read and write indexes are using a
	// double-index range implementation, the max FIFO size is thus 128 items.
	Assert (size <= 128);

	// Fifo starts empty.
	fifo_desc->read_index  = 0;
	fifo_desc->write_index = 0;

	// Save the size parameter.
	fifo_desc->size = size;

	// Create a mask to speed up the FIFO management (index swapping).
	fifo_desc->mask = (2 * (uint16_t)size) - 1;

	// Save the buffer pointer.
	fifo_desc->buffer.u8ptr = buffer;

	return FIFO_OK;
}
