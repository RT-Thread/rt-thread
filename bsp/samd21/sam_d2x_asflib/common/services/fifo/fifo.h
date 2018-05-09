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

#ifndef _FIFO_H_
#define _FIFO_H_

#include "compiler.h"

/**
 * \defgroup fifo_group First-In-First-Out Buffer (FIFO)
 *
 * See \ref fifo_quickstart.
 *
 * These functions manages FIFOs thanks to simple a API. The FIFO can
 * be 100% full thanks to a double-index range implementation. For example,
 * a FIFO of 4 elements can be implemented: the FIFO can really hold up to 4
 * elements. This is particularly well suited for any kind of application
 * needing a lot of small FIFO. The maximum fifo size is 128 items (uint8,
 * uint16 or uint32). Note that the driver, thanks to its conception, does
 * not use interrupt protection.
 *
 * @{
 */

//! Error codes used by FIFO driver.
enum {
	FIFO_OK = 0,          //!< Normal operation.
	FIFO_ERROR_OVERFLOW,  //!< Attempt to push something in a FIFO that is full.
	FIFO_ERROR_UNDERFLOW, //!< Attempt to pull something from a FIFO that is empty
	FIFO_ERROR,           //!< Error condition during FIFO initialization
};

//! FIFO descriptor used by FIFO driver.
struct fifo_desc {
	union
	{
		uint32_t *u32ptr; //!< Pointer to unsigned-32 bits location
		uint16_t *u16ptr; //!< Pointer to unsigned-16 bits location
		uint8_t  *u8ptr;  //!< Pointer to unsigned-8 bits location
	}  buffer;
	volatile uint8_t read_index;  //!< Read index
	volatile uint8_t write_index; //!< Write index
	uint8_t size;                 //!< Size of the FIFO (unit is in number of 'element')
	uint8_t mask;                 //!< Mask used to speed up FIFO operation (wrapping)
};

typedef struct fifo_desc fifo_desc_t;

/**
 *  \brief Initializes a new software FIFO for a certain 'size'.
 *
 *  \pre Both fifo descriptor and buffer must be allocated by the caller before.
 *
 *  \param fifo_desc  Pointer on the FIFO descriptor.
 *  \param buffer     Pointer on the FIFO buffer.
 *  \param size       Size of the buffer (unit is in number of 'elements').
 *                    It must be a 2-power and <= to 128.
 *
 *  \return Status
 *    \retval FIFO_OK when no error occurred.
 *    \retval FIFO_ERROR when the size is not a 2-power.
 */
int fifo_init(fifo_desc_t *fifo_desc, void *buffer, uint8_t size);

/**
 *  \brief Returns the number of elements in the FIFO.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *
 *  \return The number of used elements.
 */
static inline uint8_t fifo_get_used_size(fifo_desc_t *fifo_desc)
{
	return ((fifo_desc->write_index - fifo_desc->read_index) & fifo_desc->mask);
}

/**
 *  \brief Returns the remaining free spaces of the FIFO (in number of elements).
 *
 *  \param fifo_desc  The FIFO descriptor.
 *
 *  \return The number of free elements.
 */
static inline uint8_t fifo_get_free_size(fifo_desc_t *fifo_desc)
{
	return fifo_desc->size - fifo_get_used_size(fifo_desc);
}

/**
 *  \brief Tests if a FIFO is empty.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *
 *  \return Status
 *    \retval true when the FIFO is empty.
 *    \retval false when the FIFO is not empty.
 */
static inline bool fifo_is_empty(fifo_desc_t *fifo_desc)
{
	return (fifo_desc->write_index == fifo_desc->read_index);
}

/**
 *  \brief Tests if a FIFO is full.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *
 *  \return Status
 *    \retval true when the FIFO is full.
 *    \retval false when the FIFO is not full.
 */
static inline bool fifo_is_full(fifo_desc_t *fifo_desc)
{
	return (fifo_get_used_size(fifo_desc) == fifo_desc->size);
}

/**
 *  \brief Puts a new 8-bits element into the FIFO.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *  \param item       extracted element.
 */
static inline void fifo_push_uint8_nocheck(fifo_desc_t *fifo_desc, uint32_t item)
{
	uint8_t write_index;

	write_index = fifo_desc->write_index;
	fifo_desc->buffer.u8ptr[write_index & (fifo_desc->mask >> 1)] = item;
	write_index = (write_index + 1) & fifo_desc->mask;

	// Must be the last thing to do.
	barrier();
	fifo_desc->write_index = write_index;
}

/**
 *  \brief Puts a new 8-bits element into the FIFO and
 *         checks for a possible overflow.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *  \param item       extracted element.
 *
 *  \return Status
 *    \retval FIFO_OK when no error occurred.
 *    \retval FIFO_ERROR_UNDERFLOW when the FIFO was empty.
 */
static inline int fifo_push_uint8(fifo_desc_t *fifo_desc, uint32_t item)
{
	uint8_t write_index;

	if (fifo_is_full(fifo_desc)) {
		return FIFO_ERROR_OVERFLOW;
	}

	write_index = fifo_desc->write_index;
	fifo_desc->buffer.u8ptr[write_index & (fifo_desc->mask >> 1)] = item;
	write_index = (write_index + 1) & fifo_desc->mask;

	// Must be the last thing to do.
	barrier();
	fifo_desc->write_index = write_index;

	return FIFO_OK;
}

/**
 *  \brief Puts a new 16-bits element into the FIFO.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *  \param item       extracted element.
 */
static inline void fifo_push_uint16_nocheck(fifo_desc_t *fifo_desc, uint32_t item)
{
	uint8_t write_index;

	write_index = fifo_desc->write_index;
	fifo_desc->buffer.u16ptr[write_index & (fifo_desc->mask >> 1)] = item;
	write_index = (write_index + 1) & fifo_desc->mask;

	// Must be the last thing to do.
	barrier();
	fifo_desc->write_index = write_index;
}

/**
 *  \brief Puts a new 16-bits element into the FIFO and
 *         checks for a possible overflow.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *  \param item       extracted element.
 *
 *  \return Status
 *    \retval FIFO_OK when no error occurred.
 *    \retval FIFO_ERROR_UNDERFLOW when the FIFO was empty.
 */
static inline int fifo_push_uint16(fifo_desc_t *fifo_desc, uint32_t item)
{
	uint8_t write_index;

	if (fifo_is_full(fifo_desc)) {
		return FIFO_ERROR_OVERFLOW;
	}

	write_index = fifo_desc->write_index;
	fifo_desc->buffer.u16ptr[write_index & (fifo_desc->mask >> 1)] = item;
	write_index = (write_index + 1) & fifo_desc->mask;

	// Must be the last thing to do.
	barrier();
	fifo_desc->write_index = write_index;

	return FIFO_OK;
}

/**
 *  \brief Puts a new 32-bits element into the FIFO.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *  \param item       extracted element.
 */
static inline void fifo_push_uint32_nocheck(fifo_desc_t *fifo_desc, uint32_t item)
{
	uint8_t write_index;

	write_index = fifo_desc->write_index;
	fifo_desc->buffer.u32ptr[write_index & (fifo_desc->mask >> 1)] = item;
	write_index = (write_index + 1) & fifo_desc->mask;

	// Must be the last thing to do.
	barrier();
	fifo_desc->write_index = write_index;
}

/**
 *  \brief Puts a new 32-bits element into the FIFO and
 *         checks for a possible overflow.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *  \param item       extracted element.
 *
 *  \return Status
 *    \retval FIFO_OK when no error occurred.
 *    \retval FIFO_ERROR_UNDERFLOW when the FIFO was empty.
 */
static inline int fifo_push_uint32(fifo_desc_t *fifo_desc, uint32_t item)
{
	uint8_t write_index;

	if (fifo_is_full(fifo_desc)) {
		return FIFO_ERROR_OVERFLOW;
	}

	write_index = fifo_desc->write_index;
	fifo_desc->buffer.u32ptr[write_index & (fifo_desc->mask >> 1)] = item;
	write_index = (write_index + 1) & fifo_desc->mask;

	// Must be the last thing to do.
	barrier();
	fifo_desc->write_index = write_index;

	return FIFO_OK;
}

/**
 *  \brief Gets a 8-bits element from the FIFO.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *
 *  \return extracted element.
 */
static inline uint8_t fifo_pull_uint8_nocheck(fifo_desc_t *fifo_desc)
{
	uint8_t read_index;
	uint8_t item;

	read_index = fifo_desc->read_index;
	item = fifo_desc->buffer.u8ptr[read_index & (fifo_desc->mask >> 1)];
	read_index = (read_index + 1) & fifo_desc->mask;

	// Must be the last thing to do.
	barrier();
	fifo_desc->read_index = read_index;

	return item;
}

/**
 *  \brief Gets a 8-bits element from the FIFO and
 *         checks for a possible underflow.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *  \param item       extracted element.
 *
 *  \return Status
 *    \retval FIFO_OK when no error occurred.
 *    \retval FIFO_ERROR_UNDERFLOW when the FIFO was empty.
 */
static inline int fifo_pull_uint8(fifo_desc_t *fifo_desc, uint8_t *item)
{
	uint8_t read_index;

	if (fifo_is_empty(fifo_desc)) {
		return FIFO_ERROR_UNDERFLOW;
	}

	read_index = fifo_desc->read_index;
	*item = fifo_desc->buffer.u8ptr[read_index & (fifo_desc->mask >> 1)];
	read_index = (read_index + 1) & fifo_desc->mask;

	// Must be the last thing to do.
	barrier();
	fifo_desc->read_index = read_index;

	return FIFO_OK;
}

/**
 *  \brief Gets a 16-bits element from the FIFO.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *
 *  \return extracted element.
 */
static inline uint16_t fifo_pull_uint16_nocheck(fifo_desc_t *fifo_desc)
{
	uint8_t read_index;
	uint16_t item;

	read_index = fifo_desc->read_index;
	item = fifo_desc->buffer.u16ptr[read_index & (fifo_desc->mask >> 1)];
	read_index = (read_index + 1) & fifo_desc->mask;

	// Must be the last thing to do.
	barrier();
	fifo_desc->read_index = read_index;

	return item;
}

/**
 *  \brief Gets a 16-bits element from the FIFO and
 *         checks for a possible underflow.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *  \param item       extracted element.
 *
 *  \return Status
 *    \retval FIFO_OK when no error occurred.
 *    \retval FIFO_ERROR_UNDERFLOW when the FIFO was empty.
 */
static inline int fifo_pull_uint16(fifo_desc_t *fifo_desc, uint16_t *item)
{
	uint8_t read_index;

	if (fifo_is_empty(fifo_desc)) {
		return FIFO_ERROR_UNDERFLOW;
	}

	read_index = fifo_desc->read_index;
	*item = fifo_desc->buffer.u16ptr[read_index & (fifo_desc->mask >> 1)];
	read_index = (read_index + 1) & fifo_desc->mask;

	// Must be the last thing to do.
	barrier();
	fifo_desc->read_index = read_index;

	return FIFO_OK;
}

/**
 *  \brief Gets a 32-bits element from the FIFO
 *
 *  \param fifo_desc  The FIFO descriptor.
 *
 *  \return extracted element.
 */
static inline uint32_t fifo_pull_uint32_nocheck(fifo_desc_t *fifo_desc)
{
	uint8_t read_index;
	uint32_t item;

	read_index = fifo_desc->read_index;
	item = fifo_desc->buffer.u32ptr[read_index & (fifo_desc->mask >> 1)];
	read_index = (read_index + 1) & fifo_desc->mask;

	// Must be the last thing to do.
	barrier();
	fifo_desc->read_index = read_index;

	return item;
}

/**
 *  \brief Gets a 32-bits element from the FIFO and
 *         checks for a possible underflow.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *  \param item       extracted element.
 *
 *  \return Status
 *    \retval FIFO_OK when no error occurred.
 *    \retval FIFO_ERROR_UNDERFLOW when the FIFO was empty.
 */
static inline int fifo_pull_uint32(fifo_desc_t *fifo_desc, uint32_t *item)
{
	uint8_t read_index;

	if (fifo_is_empty(fifo_desc)) {
		return FIFO_ERROR_UNDERFLOW;
	}

	read_index = fifo_desc->read_index;
	*item = fifo_desc->buffer.u32ptr[read_index & (fifo_desc->mask >> 1)];
	read_index = (read_index + 1) & fifo_desc->mask;

	// Must be the last thing to do.
	barrier();
	fifo_desc->read_index = read_index;

	return FIFO_OK;
}

/**
 *  \brief Gets a 32-bits element from the FIFO but does
 *         not remove it from the FIFO.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *
 *  \retval item      extracted element.
 */
static inline uint32_t fifo_peek_uint32(fifo_desc_t *fifo_desc)
{
	return fifo_desc->buffer.u32ptr[fifo_desc->read_index & (fifo_desc->mask >> 1)];
}

/**
 *  \brief Gets a 16-bits element from the FIFO but does
 *         not remove it from the FIFO.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *
 *  \retval item      extracted element.
 */
static inline uint16_t fifo_peek_uint16(fifo_desc_t *fifo_desc)
{
	return fifo_desc->buffer.u16ptr[fifo_desc->read_index & (fifo_desc->mask >> 1)];
}

/**
 *  \brief Gets a 8-bits element from the FIFO but does
 *         not remove it from the FIFO.
 *
 *  \param fifo_desc  The FIFO descriptor.
 *
 *  \retval item      extracted element.
 */
static inline uint8_t fifo_peek_uint8(fifo_desc_t *fifo_desc)
{
	return fifo_desc->buffer.u8ptr[fifo_desc->read_index & (fifo_desc->mask >> 1)];
}

/**
 *  \brief Flushes a software FIFO.
 *
 *  \param fifo_desc  The FIFO descriptor.
 */
static inline void fifo_flush(fifo_desc_t *fifo_desc)
{
	// Fifo starts empty.
	fifo_desc->read_index = fifo_desc->write_index = 0;
}

/**
 * @}
 */

 /**
 * \page fifo_quickstart Quick start guide for First-In-First-Out Buffer (FIFO)
 *
 * This is the quick start guide for the \ref fifo_group, with
 * step-by-step instructions on how to configure and use the driver in a
 * selection of use cases.
 *
 * The use cases contain several code fragments. The code fragments in the
 * steps for setup can be copied into a custom initialization function, while
 * the steps for usage can be copied into, e.g., the main application function.
 *
 * \section fifo_use_cases FIFO use cases
 * - \ref fifo_basic_use_case
 * - \subpage fifo_use_case_1
 *
 * \section fifo_basic_use_case Basic use case - Push and pull
 * In this use case, an element will be pushed to the FIFO, and the same
 * element will be pulled from it.
 *
 * \section fifo_basic_use_case_setup Setup steps
 *
 * \subsection fifo_basic_use_case_setup_code Example code
 * The following must be added to the project:
 * \code
	#define FIFO_BUFFER_LENGTH  4
	#define PUSH_VALUE          0x12345678
	union buffer_element {
	   uint8_t  byte;
	   uint16_t halfword;
	   uint32_t word;
	};
\endcode
 *
 * Add to application initialization:
 * \code
	union buffer_element fifo_buffer[FIFO_BUFFER_LENGTH];
	fifo_desc_t fifo_desc;
	fifo_init(&fifo_desc, fifo_buffer, FIFO_BUFFER_LENGTH); 
\endcode
 *
 * \subsection fifo_basic_use_case_setup_flow Workflow
 * -# Create a FIFO buffer of FIFO_BUFFER_LENGTH elements, capable
 * of holding a byte, halfword or word:
 *   - \code union buffer_element fifo_buffer[FIFO_BUFFER_LENGTH]; \endcode
 * -# Create a FIFO buffer descriptor that contains information about the
 * location of the FIFO buffer, its size and where to read from or write to
 * upon the next buffer pull or push:
 *   - \code fifo_desc_t fifo_desc; \endcode
 * -# Initialize the FIFO:
 *   - \code fifo_init(&fifo_desc, fifo_buffer, FIFO_BUFFER_LENGTH); \endcode
 *
 * \section fifo_basic_use_case_usage Usage steps
 *
 * \subsection fifo_basic_use_case_usage_code Example code
 * Add to application C-file:
 * \code
	uint8_t status;
	uint8_t pull_value;
	status = fifo_push_uint8(&fifo_desc, PUSH_VALUE & 0xff);
	status = fifo_pull_uint8(&fifo_desc, &pull_value);
\endcode
 *
 * \subsection fifo_basic_use_case_usage_flow Workflow
 * -# Create a variable to hold the return status from the FIFO:
 *   - \code uint8_t status; \endcode
 * -# Create a variable to hold the pulled value from the FIFO:
 *   - \code uint8_t pull_value; \endcode
 * -# Put a new 8-bit element into the FIFO:
 *   - \code status = fifo_push_uint8(&fifo_desc, PUSH_VALUE & 0xff); \endcode
 * \note The status variable will contain \ref FIFO_OK if no error occurred.
 * -# Get the 8-bit element from the FIFO:
 *   - \code status = fifo_pull_uint8(&fifo_desc, &pull_value); \endcode
 * \note The status variable will contain \ref FIFO_OK if no error occurred.
 */

/**
 * \page fifo_use_case_1 Push and flush
 *
 * In this use case, two elements will be pushed to the FIFO, and the FIFO
 * will be flushed.
 *
 * \section fifo_use_case_1_setup Setup steps
 *
 * \subsection fifo_use_case_1_setup_code Example code
 * The following must be added to the project:
 * \code
	#define FIFO_BUFFER_LENGTH  4
	#define PUSH_VALUE          0x12345678
	union buffer_element {
	   uint8_t  byte;
	   uint16_t halfword;
	   uint32_t word;
	};
\endcode
 *
 * Add to application initialization:
 * \code
	union buffer_element fifo_buffer[FIFO_BUFFER_LENGTH];
	fifo_desc_t fifo_desc;
	fifo_init(&fifo_desc, fifo_buffer, FIFO_BUFFER_LENGTH); 
\endcode
 *
 * \subsection fifo_use_case_1_setup_flow Workflow
 * -# Create a FIFO buffer of FIFO_BUFFER_LENGTH elements, capable
 * of holding a byte, halfword or word:
 *   - \code union buffer_element fifo_buffer[FIFO_BUFFER_LENGTH]; \endcode
 * -# Create a FIFO buffer descriptor that containing information about the
 * location of the FIFO buffer, its size and where to read from or write to
 * upon the next buffer pull or push:
 *   - \code fifo_desc_t fifo_desc; \endcode
 * -# Initialize the FIFO:
 *   - \code fifo_init(&fifo_desc, fifo_buffer, FIFO_BUFFER_LENGTH); \endcode
 * \section fifo_use_case_1_usage Usage steps
 *
 * \subsection fifo_use_case_1_usage_code Example code
 * Add to application C-file:
 * \code
	uint8_t status;
	bool fifo_empty;
	status = fifo_push_uint16(&fifo_desc, PUSH_VALUE & 0xffff);
	status = fifo_push_uint16(&fifo_desc, PUSH_VALUE & 0xffff);
	fifo_flush(&fifo_desc);
	fifo_empty = fifo_is_empty(&fifo_desc);
\endcode
 *
 * \subsection fifo_use_case_1_usage_flow Workflow
 * -# Create a variable to hold the return status from the FIFO:
 *   - \code uint8_t status; \endcode
 * -# Create a variable to hold the pulled value from the FIFO:
 *   - \code uint16_t pull_value; \endcode
 * -# Put two new 16-bit element into the FIFO:
 *   - \code status = fifo_push_uint16(&fifo_desc, PUSH_VALUE & 0xffff); \endcode
 *   - \code status = fifo_push_uint16(&fifo_desc, PUSH_VALUE & 0xffff); \endcode
 * \note The status variable will contain \ref FIFO_OK if no error occurred.
 * -# Flush the FIFO:
 *   - \code fifo_flush(&fifo_desc); \endcode
 * -# Check that the FIFO is empty after flushing:
 *   - \code fifo_empty = fifo_is_empty(&fifo_desc); \endcode
 * \note The fifo_empty variable will be true if the FIFO is empty.
 */

#endif  // _FIFO_H_
