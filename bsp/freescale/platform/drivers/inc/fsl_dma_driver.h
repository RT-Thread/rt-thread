/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__FSL_DMA_DRIVER_H__)
#define __FSL_DMA_DRIVER_H__

#include <stdint.h>
#include <stdlib.h>
#include "fsl_device_registers.h"
#include "fsl_dma_request.h"
#include "fsl_dma_hal.h"
#include "fsl_dmamux_hal.h"
#include "fsl_os_abstraction.h"
#if FSL_FEATURE_SOC_DMA_COUNT

/*!
 * @addtogroup dma_driver
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Array for eDMA module register base address. */
extern DMA_Type * const g_dmaBase[DMA_INSTANCE_COUNT];

/*! @brief Array for DMAMUX module register base address. */
extern DMAMUX_Type * const g_dmamuxBase[DMAMUX_INSTANCE_COUNT];

/*! @brief Two-dimensional array for eDMA channel interrupt vector number. */
extern const IRQn_Type g_dmaIrqId[DMA_INSTANCE_COUNT][FSL_FEATURE_DMA_DMAMUX_CHANNELS];

/*!
 * @brief Channel status for the DMA channel.
 *
 * A structure describing the status of the DMA channel. The user can get the status from the channel callback
 * function.
 */
typedef enum _dma_channel_status {
    kDmaIdle,                    /*!< DMA channel is idle. */
    kDmaNormal,                /*!< DMA channel is occupied. */
    kDmaError                    /*!< Error occurs in the DMA channel. */
} dma_channel_status_t;

/*! @brief Type for the DMA channel, which is used for the DMA channel allocation. */
typedef enum _dma_channel_type {
    kDmaInvalidChannel = 0xFFU,  /*!< Macros indicating the failure of the channel request. */
    kDmaAnyChannel = 0xFEU       /*!< Macros used when requesting a channel.  */
                                /*!< kEdmaAnyChannel means a request of dynamic channel allocation. */
} dma_channel_type_t;

/*!
 * @brief A definition for the DMA channel callback function.
 *
 * A prototype for the callback function registered into the DMA driver.
 */
typedef void (*dma_callback_t)(void *parameter, dma_channel_status_t status);

/*! @brief Data structure for the DMA channel management. */
typedef struct DmaChannel {
    uint8_t channel;            /*!< Channel number */
    uint8_t dmamuxModule;       /*!< DMAMUX module index */
    uint8_t dmamuxChannel;      /*!< DMAMUX module channel */
    dma_callback_t callback;    /*!< Callback function for this channel */
    void *parameter;            /*!< Parameter for the callback function */
    volatile dma_channel_status_t status;/*!< Channel status */
} dma_channel_t;

/*! @brief Data structure for the DMA controller management. */
typedef struct DmaState {
    dma_channel_t * volatile dmaChan[FSL_FEATURE_DMA_DMAMUX_CHANNELS];
#if USE_RTOS
    mutex_t lock;
#endif
} dma_state_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name DMA Driver
 * @{
 */

/*!
 * @brief Initializes the DMA.
 *
 * @param state DMA state structure used for the DMA internal logic.
 * @return If successful, returns the kStatus_DMA_Success. Otherwise, it returns an error.
 */
dma_status_t DMA_DRV_Init(dma_state_t *state);

/*!
 * @brief De-initializes the DMA.
 *
 * @return If successful, returns the kStatus_DMA_Success. Otherwise, it returns an error.
 */
dma_status_t DMA_DRV_Deinit(void);

/*!
 * @brief Updates the DMA destination transfer size.
 *
 * @param chn A handler for the DMA channel
 * @param transferSize Size of destination at each transfer
 *
 * @return If successful, returns the kStatus_DMA_Success. Otherwise, it returns an error.
 */
dma_status_t DMA_DRV_SetDestTransferSize(dma_channel_t *chn, uint32_t transferSize);

/*!
 * @brief Updates the DMA source transfer size.
 *
 * @param chn A handler for the DMA channel
 * @param transferSize Size of source at each transfer
 *
 * @return If successful, returns the kStatus_DMA_Success. Otherwise, it returns an error.
 */
dma_status_t DMA_DRV_SetSourceTransferSize(dma_channel_t *chn, uint32_t transferSize);

/*!
 * @brief Registers the callback function and a parameter.
 *
 * The user registers the callback function and a parameter for a specified DMA channel. When the channel
 * interrupt or a channel error happens, the callback and the parameter are called.
 * The user parameter is also provided to give a channel status.
 *
 * @param chn  A handler for the DMA channel
 * @param callback Callback function
 * @param para  A parameter for callback functions
 * @return If successful, returns the kStatus_DMA_Success. Otherwise, it returns an error.
 */
dma_status_t DMA_DRV_RegisterCallback(
        dma_channel_t *chn, dma_callback_t callback, void *para);

/*!
 * @brief Gets the number of unfinished bytes.
 *
 * Gets the bytes that remain to be transferred.
 *
 * @param chn A handler for the DMA channel
 * @return If successful, returns the kStatus_DMA_Success. Otherwise, it returns an error.
 */
uint32_t DMA_DRV_GetUnfinishedBytes(dma_channel_t *chn);

/*!
 * @brief Claims a DMA channel.
 *
 * @param channel Channel index which needs to claim.
 * @param source DMA request source.
 * @param chn A handler for the DMA channel
 * @return If successful, returns the kStatus_DMA_Success. Otherwise, it returns an error.
 */
dma_status_t DMA_DRV_ClaimChannel(
        uint32_t channel, dma_request_source_t source, dma_channel_t *chn);


/*!
 * @brief Requests a DMA channel.
 *
 * This function provides two ways to allocate a DMA channel: static and dynamic allocation.
 * To allocate a channel dynamically, set the channel parameter with the value of
 * kDmaAnyChannel. The driver searches all available free channels and assigns the first
 * channel to the user.
 * To allocate the channel statically, set the channel parameter with the value of a specified
 * channel. If the channel is available, the driver assigns the channel.
 * Notes: The user must provide a handler memory for the DMA channel. The driver initializes
 * the handler and configures the handler memory.
 *
 * @param channel A DMA channel number. If a channel is assigned with a valid channel number, the
 * DMA driver tries to assign a specified channel. If a channel is assigned with
 * kDmaAnyChannel, the DMA driver searches all available channels and assigns the first channel to the user.
 * @param source A DMA hardware request.
 * @param chn Memory pointing to DMA channel. The user must ensure that the handler memory is
 * valid and that it will not be released or changed by any other code before the channel
 * dma_free_channel() operation.
 *
 * @return If the channel allocation is successful, the return value indicates the requested channel. If
 * not, the driver  returns a  kDmaInvalidChannel value to indicate that the request operation has failed.
 */
uint32_t DMA_DRV_RequestChannel(
        uint32_t channel, dma_request_source_t source, dma_channel_t *chn);

/*!
 * @brief Frees DMA channel hardware and software resource.
 *
 * This function frees the relevant software and hardware resources. Both the request and the free operations need to
 * be called as a pair.
 *
 * @param chn Memory pointing to DMA channel.
 * @return If successful, returns the kStatus_DMA_Success. Otherwise, it returns an error.
 *
 */
dma_status_t DMA_DRV_FreeChannel(dma_channel_t *chn);

/*!
 * @brief Starts a DMA channel.
 *
 * Starts a DMA channel. The driver starts a DMA channel by enabling the DMA request.
 * A software start bit is not used in the DMA Peripheral driver.
 *
 * @param chn Memory pointing to the DMA channel.
 * @return If successful, returns the kStatus_DMA_Success. Otherwise, it returns an error.
 */
dma_status_t DMA_DRV_StartChannel(dma_channel_t *chn);

/*!
 * @brief Stops a DMA  channel.
 *
 * @param chn Memory pointing to the DMA channel.
 * @return If successful, returns the kStatus_DMA_Success. Otherwise, it returns an error.
 */
dma_status_t DMA_DRV_StopChannel(dma_channel_t *chn);

/*!
 * @brief Configures a transfer for the DMA.
 *
 * Configures a transfer for the DMA.
 *
 * @param chn Memory pointing to the DMA channel.
 * @param type Transfer type.
 * @param size Size to be transferred on each DMA write/read. Source/Dest share the same write/read
 * size.
 * @param sourceAddr Source address.
 * @param destAddr Destination address.
 * @param length Bytes to be transferred.
 * @return If successful, returns the kStatus_DMA_Success. Otherwise, it returns an error.
 */
dma_status_t DMA_DRV_ConfigTransfer(
        dma_channel_t *chn, dma_transfer_type_t type,
        uint32_t size, uint32_t sourceAddr, uint32_t destAddr, uint32_t length);

/*!
 * @brief Configures the channel link feature.
 *
 * @param chn Memory pointing to the DMA channel.
 * @param link_config Configure of channel link in DMA.
 * @return If successful, returns the kStatus_DMA_Success. Otherwise, it returns an error.
 */
dma_status_t DMA_DRV_ConfigChanLink(
        dma_channel_t *chn, dma_channel_link_config_t *link_config);

/*!
 * @brief DMA IRQ handler for both an interrupt and an error.
 *
 * @param channel DMA channel number.
 *
 */
void DMA_DRV_IRQhandler(uint32_t channel);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
#endif /* __FSL_DMA_DRIVER_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

