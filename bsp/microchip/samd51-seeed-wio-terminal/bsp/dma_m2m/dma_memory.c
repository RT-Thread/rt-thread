/**
 * \file
 *
 * \brief Memory with DMA functionality implementation.
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

#include "dma_memory.h"
#include "dma_memory_config.h"
#include <utils_assert.h>
#include <utils.h>
#include <hal_atomic.h>

/**
 * \brief Driver version
 */
#define DRIVER_VERSION 0x00000001u

/**
 * \brief memory with dma descriptor instance
 */
static struct dma_memory_descriptor descr;

/**
 * \internal Process transfer done interrupts
 *
 * \param[in] resource The pointer to memory resource
 */
static void dma_transfer_done(struct _dma_resource *resource)
{
	(void)resource;
	if (descr.memory_cb.complete) {
		descr.memory_cb.complete();
	}
}

/**
 * \internal Process transfer error interrupts
 *
 * \param[in] resource The pointer to memory resource
 */
static void dma_memory_error(struct _dma_resource *resource)
{
	(void)resource;
	if (descr.memory_cb.error) {
		descr.memory_cb.error();
	}
}

/**
 * \brief Initialize DMA
 */
int32_t dma_memory_init(void)
{
	_dma_get_channel_resource(&descr.resource, CONF_DMA_MEMORY_CHANNEL);
	descr.resource->dma_cb.transfer_done = dma_transfer_done;
	descr.resource->dma_cb.error         = dma_memory_error;

	return ERR_NONE;
}

/**
 * \brief Register DMA callback
 */
int32_t dma_memory_register_callback(const enum dma_memory_callback_type type, dma_memory_cb_t cb)
{
	switch (type) {
	case DMA_MEMORY_COMPLETE_CB:
		descr.memory_cb.complete = cb;
		break;

	case DMA_MEMORY_ERROR_CB:
		descr.memory_cb.error = cb;
		break;

	default:
		return ERR_INVALID_ARG;
	}

	_dma_set_irq_state(CONF_DMA_MEMORY_CHANNEL, (enum _dma_callback_type)type, (cb != NULL));

	return ERR_NONE;
}

/**
 * \brief Memory copy with dma
 */
int32_t dma_memcpy(void *dst, void *src, uint32_t size)
{
	_dma_srcinc_enable(CONF_DMA_MEMORY_CHANNEL, true);
	_dma_dstinc_enable(CONF_DMA_MEMORY_CHANNEL, true);
	_dma_set_destination_address(CONF_DMA_MEMORY_CHANNEL, dst);
	_dma_set_source_address(CONF_DMA_MEMORY_CHANNEL, src);
	_dma_set_data_amount(CONF_DMA_MEMORY_CHANNEL, size);
	_dma_enable_transaction(CONF_DMA_MEMORY_CHANNEL, true);

	return ERR_NONE;
}

/**
 * \brief Memory set with dma
 */
int32_t dma_memset(void *dst, int32_t ch, uint32_t size)
{
	static int32_t tmp_ch;

	tmp_ch = ch;

	_dma_set_source_address(CONF_DMA_MEMORY_CHANNEL, &tmp_ch);
	_dma_srcinc_enable(CONF_DMA_MEMORY_CHANNEL, false);
	_dma_dstinc_enable(CONF_DMA_MEMORY_CHANNEL, true);
	_dma_set_destination_address(CONF_DMA_MEMORY_CHANNEL, dst);
	_dma_set_data_amount(CONF_DMA_MEMORY_CHANNEL, size);
	_dma_enable_transaction(CONF_DMA_MEMORY_CHANNEL, true);

	return ERR_NONE;
}
