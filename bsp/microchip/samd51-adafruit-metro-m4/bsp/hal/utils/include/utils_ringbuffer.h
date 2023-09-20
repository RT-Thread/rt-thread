/**
 * \file
 *
 * \brief Ringbuffer declaration.
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
#ifndef _UTILS_RINGBUFFER_H_INCLUDED
#define _UTILS_RINGBUFFER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup doc_driver_hal_utils_ringbuffer
 *
 * @{
 */

#include "compiler.h"
#include "utils_assert.h"

/**
 * \brief Ring buffer element type
 */
struct ringbuffer {
	uint8_t *buf;         /** Buffer base address */
	uint32_t size;        /** Buffer size */
	uint32_t read_index;  /** Buffer read index */
	uint32_t write_index; /** Buffer write index */
};

/**
 * \brief Ring buffer init
 *
 * \param[in] rb The pointer to a ring buffer structure instance
 * \param[in] buf Space to store the data
 * \param[in] size The buffer length, must be aligned with power of 2
 *
 * \return ERR_NONE on success, or an error code on failure.
 */
int32_t ringbuffer_init(struct ringbuffer *const rb, void *buf, uint32_t size);

/**
 * \brief Get one byte from ring buffer, the user needs to handle the concurrent
 * access on buffer via put/get/flush
 *
 * \param[in] rb The pointer to a ring buffer structure instance
 * \param[in] data One byte space to store the read data
 *
 * \return ERR_NONE on success, or an error code on failure.
 */
int32_t ringbuffer_get(struct ringbuffer *const rb, uint8_t *data);

/**
 * \brief Put one byte to ring buffer, the user needs to handle the concurrent access
 * on buffer via put/get/flush
 *
 * \param[in] rb The pointer to a ring buffer structure instance
 * \param[in] data One byte data to be put into ring buffer
 *
 * \return ERR_NONE on success, or an error code on failure.
 */
int32_t ringbuffer_put(struct ringbuffer *const rb, uint8_t data);

/**
 * \brief Return the element number of ring buffer
 *
 * \param[in] rb The pointer to a ring buffer structure instance
 *
 * \return The number of elements in ring buffer [0, rb->size]
 */
uint32_t ringbuffer_num(const struct ringbuffer *const rb);

/**
 * \brief Flush ring buffer, the user needs to handle the concurrent access on buffer
 * via put/get/flush
 *
 * \param[in] rb The pointer to a ring buffer structure instance
 *
 * \return ERR_NONE on success, or an error code on failure.
 */
uint32_t ringbuffer_flush(struct ringbuffer *const rb);

/**@}*/

#ifdef __cplusplus
}
#endif
#endif /* _UTILS_RINGBUFFER_H_INCLUDED */
