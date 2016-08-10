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
#ifndef __FSL_DMA_HAL_H__
#define __FSL_DMA_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_DMA_COUNT

/*!
 * @addtogroup dma_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief DMA status */
typedef enum _dma_status
{
    kStatus_DMA_Success = 0U,
    kStatus_DMA_InvalidArgument = 1U, /*!< Parameter is not available for the current
                                                     configuration. */
    kStatus_DMA_Fail = 2U             /*!< Function operation  failed. */
} dma_status_t;

/*! @brief DMA transfer size type*/
typedef enum _dma_transfer_size {
    kDmaTransfersize32bits = 0x0U,    /*!< 32 bits are transferred for every read/write */
    kDmaTransfersize8bits = 0x1U,     /*!< 8 bits are transferred for every read/write */
    kDmaTransfersize16bits = 0x2U     /*!< 16b its are transferred for every read/write */
} dma_transfer_size_t;

/*! @brief Configuration type for the DMA modulo */
typedef enum _dma_modulo {
    kDmaModuloDisable = 0x0U,
    kDmaModulo16Bytes = 0x1U,
    kDmaModulo32Bytes = 0x2U,
    kDmaModulo64Bytes = 0x3U,
    kDmaModulo128Bytes = 0x4U,
    kDmaModulo256Bytes = 0x5U,
    kDmaModulo512Bytes = 0x6U,
    kDmaModulo1KBytes = 0x7U,
    kDmaModulo2KBytes = 0x8U,
    kDmaModulo4KBytes = 0x9U,
    kDmaModulo8KBytes = 0xaU,
    kDmaModulo16KBytes = 0xbU,
    kDmaModulo32KBytes = 0xcU,
    kDmaModulo64KBytes = 0xdU,
    kDmaModulo128KBytes = 0xeU,
    kDmaModulo256KBytes = 0xfU,
} dma_modulo_t;

/*! @brief DMA channel link type */
typedef enum _dma_channel_link_type {
    kDmaChannelLinkDisable = 0x0U,          /*!< No channel link */
    kDmaChannelLinkChan1AndChan2 = 0x1U,    /*!< Perform a link to channel 1 after each cycle-steal
                                                 transfer followed by a link and to channel 2 after the
                                                 BCR decrements to zeros. */
    kDmaChannelLinkChan1 = 0x2U,            /*!< Perform a link to channel 1 after each cycle-steal
                                                 transfer. */
    kDmaChannelLinkChan1AfterBCR0 = 0x3U     /*!< Perform a link to channel1 after the BCR decrements
                                                 to zero.  */
} dma_channel_link_type_t;

/*! @brief Data structure for data structure configuration */
typedef struct DmaChannelLinkConfig {
    dma_channel_link_type_t linkType;   /*!< Channel link type */
    uint32_t channel1;                  /*!< Channel 1 configuration  */
    uint32_t channel2;                  /*!< Channel 2 configuration  */
} dma_channel_link_config_t;

/*! @brief Data structure to get status of the DMA channel status */
typedef struct DmaErrorStatus {
    uint32_t dmaBytesToBeTransffered;  /*!< Bytes to be transferred */
    bool dmaTransDone;              /*!< DMA channel transfer is done. */
    bool dmaBusy;                   /*!< DMA is running. */
    bool dmaPendingRequest;         /*!< A transfer  remains. */
    bool dmaDestBusError;           /*!< Bus error on destination address */
    bool dmaSourceBusError;         /*!< Bus error on source address */
    bool dmaConfigError;            /*!< Configuration error */
} dma_error_status_t;

/*! @brief Type for DMA transfer. */
typedef enum _dma_transfer_type {
    kDmaPeripheralToMemory,     /*!< Transfer from the peripheral to memory */
    kDmaMemoryToPeripheral,     /*!< Transfer from the memory to peripheral */
    kDmaMemoryToMemory,         /*!< Transfer from the memory to memory */
    kDmaPeripheralToPeripheral  /*!< Transfer from the peripheral to peripheral */
} dma_transfer_type_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name DMA HAL channel configuration
 * @{
 */

/*!
 * @brief Sets all registers of the channel to 0.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 */
void DMA_HAL_Init(DMA_Type * base, uint32_t channel);

/*!
 * @brief Basic DMA transfer configuration.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param size Size to be transferred on each DMA write/read. Source/Dest share the same write/read
 * size.
 * @param type Transfer type.
 * @param sourceAddr Source address.
 * @param destAddr Destination address.
 * @param length Bytes to be transferred.
 */
void DMA_HAL_ConfigTransfer(
    DMA_Type * base, uint32_t channel, dma_transfer_size_t size, dma_transfer_type_t type,
    uint32_t sourceAddr, uint32_t destAddr, uint32_t length);

/*!
 * @brief Configures the source address.
 *
 * Each SAR contains the byte address used by the DMA to read data. The SARn is typically
 * aligned on a 0-modulo-size boundary-that is on the natural alignment of the source data.
 * Bits 31-20 of this register must be written with one of the only four allowed values. Each of these
 * allowed values corresponds to a valid region of the devices' memory map. The allowed values
 * are:
 * 0x000x_xxxx
 * 0x1FFx_xxxx
 * 0x200x_xxxx
 * 0x400x_xxxx
 * After they are written with one of the allowed values, bits 31-20 read back as the written value.
 * After they are written with any other value, bits 31-20 read back as an indeterminate value.
 *
 * This function enables the request for a specified channel.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param address memory address pointing to the source address.
 */
static inline void DMA_HAL_SetSourceAddr(
        DMA_Type * base, uint32_t channel, uint32_t address)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_WR_SAR(base, channel, address);
}

/*!
 * @brief Configures the source address.
 *
 * Each DAR contains the byte address used by the DMA to read data. The DARn is typically
 * aligned on a 0-modulo-size boundary-that is on the natural alignment of the source data.
 * Bits 31-20 of this register must be written with one of the only four allowed values. Each of these
 * allowed values corresponds to a valid region of the devices' memory map. The allowed values
 * are:
 * 0x000x_xxxx
 * 0x1FFx_xxxx
 * 0x200x_xxxx
 * 0x400x_xxxx
 * After they are written with one of the allowed values, bits 31-20 read back as the written value.
 * After they are written with any other value, bits 31-20 read back as an indeterminate value.
 *
 * This function enables the request for specified channel.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param address Destination address.
 */
static inline void DMA_HAL_SetDestAddr(
        DMA_Type * base, uint32_t channel, uint32_t address)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_WR_DAR(base, channel, address);
}

/*!
 * @brief Configures the bytes to be transferred.
 *
 * Transfer bytes must be written with a value equal to or less than 0F_FFFFh. After being written
 * with a value in this range, bits 23-20 of the BCR read back as 1110b. A write to the BCR with a value
 * greater than 0F_FFFFh causes a configuration error when the channel starts to execute. After
 * they are written with a value in this range, bits 23-20 of BCR read back as 1111b.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param count bytes to be transferred.
 */
static inline void DMA_HAL_SetTransferCount(
                    DMA_Type * base, uint32_t channel, uint32_t count)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DSR_BCR_BCR(base, channel, count);
}

/*!
 * @brief Gets the left bytes not to be transferred.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @return unfinished bytes.
 */
static inline uint32_t DMA_HAL_GetUnfinishedByte(DMA_Type * base, uint32_t channel)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    return DMA_RD_DSR_BCR(base, channel) & DMA_DSR_BCR_BCR_MASK;
}

/*!
 * @brief Enables the interrupt for the DMA channel after the work is done.
 *
 * This function enables the request for specified channel.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param enable True means enable interrupt, false means disable.
 */
static inline void DMA_HAL_SetIntCmd(DMA_Type * base, uint8_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DCR_EINT(base, channel, enable);
}

/*!
 * @brief Configures the DMA transfer mode to cycle steal or continuous modes.
 *
 * If continuous mode is enabled, DMA continuously makes write/read transfers until BCR decrement to
 * 0. If continuous mode is disabled, DMA write/read is only triggered on every request.
 *s
 * @param base DMA base.
 * @param channel DMA channel.
 * @param enable 1 means cycle-steal mode, 0 means continuous mode.
 */
static inline void DMA_HAL_SetCycleStealCmd(
        DMA_Type * base, uint8_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DCR_CS(base, channel, enable);
}

/*!
 * @brief Configures the auto-align feature.
 *
 * If auto-align is enabled, the appropriate address register increments, regardless of whether it is a source increment or
 * a destination increment.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param enable 0 means disable auto-align. 1 means enable auto-align.
 */
static inline void DMA_HAL_SetAutoAlignCmd(
        DMA_Type * base, uint8_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DCR_AA(base, channel, enable);
}

/*!
 * @brief Configures the a-sync DMA request feature.
 *
 * Enables/disables the a-synchronization mode in a STOP mode for each DMA channel.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param enable 0 means disable DMA request a-sync. 1 means enable DMA request -.
 */
static inline void DMA_HAL_SetAsyncDmaRequestCmd(
        DMA_Type * base, uint8_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DCR_EADREQ(base, channel, enable);
}

/*!
 * @brief Enables/disables the source increment.
 *
 * Controls whether the source address increments after each successful transfer. If enabled, the
 * SAR increments by 1,2,4 as determined by the transfer size.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param enable Enabled/Disable increment.
 */
static inline void DMA_HAL_SetSourceIncrementCmd(
        DMA_Type * base, uint32_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DCR_SINC(base, channel, enable);
}

/*!
 * @brief Enables/disables destination increment.
 *
 * Controls whether the destination address increments after each successful transfer. If enabled, the
 * DAR increments by 1,2,4 as determined by the transfer size.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param enable Enabled/Disable increment.
 */
static inline void DMA_HAL_SetDestIncrementCmd(
        DMA_Type * base, uint32_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DCR_DINC(base, channel, enable);
}

/*!
 * @brief Configures the source transfer size.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param transfersize enum type for transfer size.
 */
static inline void DMA_HAL_SetSourceTransferSize(
        DMA_Type * base, uint32_t channel, dma_transfer_size_t transfersize)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DCR_SSIZE(base, channel, transfersize);
}

/*!
 * @brief Configures the destination transfer size.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param transfersize enum type for transfer size.
 */
static inline void DMA_HAL_SetDestTransferSize(
        DMA_Type * base, uint32_t channel, dma_transfer_size_t transfersize)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DCR_DSIZE(base, channel, transfersize);
}

/*!
 * @brief Triggers the start.
 *
 * When the DMA begins the transfer, the START bit is cleared automatically after one module clock and always
 * reads as logic 0.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param enable Enable/disable trigger start.
 */
static inline void DMA_HAL_SetTriggerStartCmd(DMA_Type * base, uint32_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DCR_START(base, channel, enable);
}

/*!
 * @brief  Configures the modulo for the source address.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param modulo enum data type for source modulo.
 */
static inline void DMA_HAL_SetSourceModulo(
        DMA_Type * base, uint32_t channel, dma_modulo_t modulo)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DCR_SMOD(base, channel, modulo);
}

/*!
 * @brief Configures the modulo for the destination address.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param modulo enum data type for dest modulo.
 */
static inline void DMA_HAL_SetDestModulo(
        DMA_Type * base, uint32_t channel, dma_modulo_t modulo)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DCR_DMOD(base, channel, modulo);
}

/*!
 * @brief Enables/disables the DMA request.
 *
 * @param base DMA base.
 * @param channel DMA channel.
 * @param enable Enable/disable dma request.
 */
static inline void DMA_HAL_SetDmaRequestCmd(
        DMA_Type * base, uint32_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DCR_ERQ(base, channel, enable);
}

/*!
 * @brief Configures the DMA request state after the work is done.
 *
 * Disables/enables the DMA request after a DMA DONE is generated. If it works in the loop mode, this bit
 * should not be set.
 * @param base DMA base address.
 * @param channel DMA channel.
 * @param enable 0 means DMA request would not be disabled after work done. 1 means disable.
 */
static inline void DMA_HAL_SetDisableRequestAfterDoneCmd(
        DMA_Type * base, uint32_t channel, bool enable)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DCR_D_REQ(base, channel, enable);

}

/*!
 * @brief Configures the channel link feature.
 *
 * @param base DMA base address.
 * @param channel DMA channel.
 * @param mode Mode of channel link in DMA.
 */
void DMA_HAL_SetChanLink(
        DMA_Type * base, uint8_t channel, dma_channel_link_config_t *mode);

/*!
 * @brief Clears the status of the DMA channel.
 *
 * This function clears the status for a specified DMA channel. The error status and done status
 * are cleared.
 * @param base DMA base address.
 * @param channel DMA channel.
 */
static inline void DMA_HAL_ClearStatus(DMA_Type * base, uint8_t channel)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_BWR_DSR_BCR_DONE(base, channel, 1U);
}

/*!
 * @brief Gets the DMA controller channel status.
 *
 * Gets the status of the DMA channel. The user can get the error status, as to whether the descriptor is finished or there are bytes left.
 * @param base DMA base address.
 * @param channel DMA channel.
 * @return Status of the DMA channel.
 */
dma_error_status_t DMA_HAL_GetStatus(DMA_Type * base, uint8_t channel);

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif
#endif /* __FSL_DMA_HAL_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

