/**
 * \file
 *
 * \brief Memory with DMA functionality declaration.
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

#ifndef DMA_MEMORY_H_INCLUDED
#define DMA_MEMORY_H_INCLUDED

#include <hpl_dma.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup dma_memory
 *
 * \section dma_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */

/**
 * \brief Memory with DMA descriptor
 *
 * The Memory with DMA descriptor forward declaration.
 */
struct dma_memory_descriptor;

/**
 * \brief memory with dma callback type
 */
typedef void (*dma_memory_cb_t)(void);

/**
 * \brief Memory with DMA callback types
 */
enum dma_memory_callback_type { DMA_MEMORY_COMPLETE_CB, DMA_MEMORY_ERROR_CB };

/**
 * \brief Memory with DMA callbacks
 */
struct dma_memory_callbacks {
	dma_memory_cb_t complete;
	dma_memory_cb_t error;
};

/**
 * \brief Memory with DMA descriptor
 */
struct dma_memory_descriptor {
	struct _dma_resource *      resource;
	struct dma_memory_callbacks memory_cb;
};

/**
 * \brief Initialize Memory with DMA
 *
 * \return Initialization status.
 */
int32_t dma_memory_init(void);

/**
 * \brief Register Memory with DMA callback
 *
 * \param[in] type Callback type
 * \param[in] cb A callback function, passing NULL de-registers callback
 *
 * \return The status of callback assignment.
 * \retval ERR_INVALID_ARG Passed parameters were invalid
 * \retval ERR_NONE A callback is registered successfully
 */
int32_t dma_memory_register_callback(const enum dma_memory_callback_type type, dma_memory_cb_t cb);

/**
 * \brief dma memory copy
 *
 * \param[in] dst The pointer to destination address for transfer
 * \param[in] src The pointer to source address for transfer
 * \param[in] size The transfer size
 *
 * \return the status of operation`
 */
int32_t dma_memcpy(void *dst, void *src, uint32_t size);

/**
 * \brief dma memory set
 *
 * \param[in] dst The pointer to address to  fill
 * \param[in] ch The value to be filled
 * \param[in] size Number of bytes to set to the value
 *
 * \return the status of operation
 */
int32_t dma_memset(void *dst, int32_t ch, uint32_t size);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif /* DMA_MEMORY_H_INCLUDED */
