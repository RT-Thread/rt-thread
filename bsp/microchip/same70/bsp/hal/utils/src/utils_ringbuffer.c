/**
 * \file
 *
 * \brief Ringbuffer functionality implementation.
 *
 * Copyright (c) 2014-2018 Microchip Technology Inc. and its subsidiaries.
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
#include "utils_ringbuffer.h"

/**
 * \brief Ringbuffer init
 */
int32_t ringbuffer_init(struct ringbuffer *const rb, void *buf, uint32_t size)
{
	ASSERT(rb && buf && size);

	/*
	 * buf size must be aligned to power of 2
	 */
	if ((size & (size - 1)) != 0) {
		return ERR_INVALID_ARG;
	}

	/* size - 1 is faster in calculation */
	rb->size        = size - 1;
	rb->read_index  = 0;
	rb->write_index = rb->read_index;
	rb->buf         = (uint8_t *)buf;

	return ERR_NONE;
}

/**
 * \brief Get one byte from ringbuffer
 *
 */
int32_t ringbuffer_get(struct ringbuffer *const rb, uint8_t *data)
{
	ASSERT(rb && data);

	if (rb->write_index != rb->read_index) {
		*data = rb->buf[rb->read_index & rb->size];
		rb->read_index++;
		return ERR_NONE;
	}

	return ERR_NOT_FOUND;
}

/**
 * \brief Put one byte to ringbuffer
 *
 */
int32_t ringbuffer_put(struct ringbuffer *const rb, uint8_t data)
{
	ASSERT(rb);

	rb->buf[rb->write_index & rb->size] = data;

	/*
	 * buffer full strategy: new data will overwrite the oldest data in
	 * the buffer
	 */
	if ((rb->write_index - rb->read_index) > rb->size) {
		rb->read_index = rb->write_index - rb->size;
	}

	rb->write_index++;

	return ERR_NONE;
}

/**
 * \brief Return the element number of ringbuffer
 */
uint32_t ringbuffer_num(const struct ringbuffer *const rb)
{
	ASSERT(rb);

	return rb->write_index - rb->read_index;
}

/**
 * \brief Flush ringbuffer
 */
uint32_t ringbuffer_flush(struct ringbuffer *const rb)
{
	ASSERT(rb);

	rb->read_index = rb->write_index;

	return ERR_NONE;
}
