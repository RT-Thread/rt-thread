/**
 * \file
 *
 * \brief DMA related functionality declaration.
 *
 * Copyright (c) 2015-2018 Microchip Technology Inc. and its subsidiaries.
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

#ifndef _HPL_DMA_H_INCLUDED
#define _HPL_DMA_H_INCLUDED

/**
 * \addtogroup HPL DMA
 *
 * \section hpl_dma_rev Revision History
 * - v1.0.0 Initial Release
 *
 *@{
 */

#include <compiler.h>
#include <hpl_irq.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _dma_resource;

/**
 * \brief DMA callback types
 */
enum _dma_callback_type { DMA_TRANSFER_COMPLETE_CB, DMA_TRANSFER_ERROR_CB };

/**
 * \brief DMA interrupt callbacks
 */
struct _dma_callbacks {
	void (*transfer_done)(struct _dma_resource *resource);
	void (*error)(struct _dma_resource *resource);
};

/**
 * \brief DMA resource structure
 */
struct _dma_resource {
	struct _dma_callbacks dma_cb;
	void *                back;
};

/**
 * \brief Initialize DMA
 *
 * This function does low level DMA configuration.
 *
 * \return initialize status
 */
int32_t _dma_init(void);

/**
 * \brief Set destination address
 *
 * \param[in] channel DMA channel to set destination address for
 * \param[in] dst Destination address
 *
 * \return setting status
 */
int32_t _dma_set_destination_address(const uint8_t channel, const void *const dst);

/**
 * \brief Set source address
 *
 * \param[in] channel DMA channel to set source address for
 * \param[in] src Source address
 *
 * \return setting status
 */
int32_t _dma_set_source_address(const uint8_t channel, const void *const src);

/**
 * \brief Set next descriptor address
 *
 * \param[in] current_channel Current DMA channel to set next descriptor address
 * \param[in] next_channel Next DMA channel used as next descriptor
 *
 * \return setting status
 */
int32_t _dma_set_next_descriptor(const uint8_t current_channel, const uint8_t next_channel);

/**
 * \brief Enable/disable source address incrementation during DMA transaction
 *
 * \param[in] channel DMA channel to set source address for
 * \param[in] enable True to enable, false to disable
 *
 * \return status of operation
 */
int32_t _dma_srcinc_enable(const uint8_t channel, const bool enable);

/**
 * \brief Enable/disable Destination address incrementation during DMA transaction
 *
 * \param[in] channel DMA channel to set destination address for
 * \param[in] enable True to enable, false to disable
 *
 * \return status of operation
 */
int32_t _dma_dstinc_enable(const uint8_t channel, const bool enable);
/**
 * \brief Set the amount of data to be transfered per transaction
 *
 * \param[in] channel DMA channel to set data amount for
 * \param[in] amount Data amount
 *
 * \return status of operation
 */
int32_t _dma_set_data_amount(const uint8_t channel, const uint32_t amount);

/**
 * \brief Trigger DMA transaction on the given channel
 *
 * \param[in] channel DMA channel to trigger transaction on
 *
 * \return status of operation
 */
int32_t _dma_enable_transaction(const uint8_t channel, const bool software_trigger);

/**
 * \brief Retrieves DMA resource structure
 *
 * \param[out] resource The resource to be retrieved
 * \param[in] channel DMA channel to retrieve structure for
 *
 * \return status of operation
 */
int32_t _dma_get_channel_resource(struct _dma_resource **resource, const uint8_t channel);

/**
 * \brief Enable/disable DMA interrupt
 *
 * \param[in] channel DMA channel to enable/disable interrupt for
 * \param[in] type The type of interrupt to disable/enable if applicable
 * \param[in] state Enable or disable
 */
void _dma_set_irq_state(const uint8_t channel, const enum _dma_callback_type type, const bool state);

#ifdef __cplusplus
}
#endif

#endif /* HPL_DMA_H_INCLUDED */
