/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_DMA_H_
#define FSL_DMA_H_

#include "fsl_common.h"

/*!
 * @addtogroup dma
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief DMA driver version 2.1.2. */
#define FSL_DMA_DRIVER_VERSION (MAKE_VERSION(2, 1, 2))
/*! @} */

/*! @brief _dma_channel_status_flags status flag for the DMA driver. */
enum
{
    kDMA_TransactionsBCRFlag = DMA_DSR_BCR_BCR_MASK,        /*!< Contains the number of bytes yet to be
                                                                 transferred for a given block */
    kDMA_TransactionsDoneFlag      = DMA_DSR_BCR_DONE_MASK, /*!< Transactions Done */
    kDMA_TransactionsBusyFlag      = DMA_DSR_BCR_BSY_MASK,  /*!< Transactions Busy */
    kDMA_TransactionsRequestFlag   = DMA_DSR_BCR_REQ_MASK,  /*!< Transactions Request */
    kDMA_BusErrorOnDestinationFlag = DMA_DSR_BCR_BED_MASK,  /*!< Bus Error on Destination */
    kDMA_BusErrorOnSourceFlag      = DMA_DSR_BCR_BES_MASK,  /*!< Bus Error on Source */
    kDMA_ConfigurationErrorFlag    = DMA_DSR_BCR_CE_MASK,   /*!< Configuration Error */
};

/*! @brief DMA transfer size type*/
typedef enum _dma_transfer_size
{
    kDMA_Transfersize32bits = 0x0U, /*!< 32 bits are transferred for every read/write */
    kDMA_Transfersize8bits,         /*!< 8 bits are transferred for every read/write */
    kDMA_Transfersize16bits,        /*!< 16b its are transferred for every read/write */
} dma_transfer_size_t;

/*! @brief Configuration type for the DMA modulo */
typedef enum _dma_modulo
{
    kDMA_ModuloDisable = 0x0U, /*!< Buffer disabled */
    kDMA_Modulo16Bytes,        /*!< Circular buffer size is 16 bytes. */
    kDMA_Modulo32Bytes,        /*!< Circular buffer size is 32 bytes. */
    kDMA_Modulo64Bytes,        /*!< Circular buffer size is 64 bytes. */
    kDMA_Modulo128Bytes,       /*!< Circular buffer size is 128 bytes. */
    kDMA_Modulo256Bytes,       /*!< Circular buffer size is 256 bytes. */
    kDMA_Modulo512Bytes,       /*!< Circular buffer size is 512 bytes. */
    kDMA_Modulo1KBytes,        /*!< Circular buffer size is 1 KB. */
    kDMA_Modulo2KBytes,        /*!< Circular buffer size is 2 KB. */
    kDMA_Modulo4KBytes,        /*!< Circular buffer size is 4 KB. */
    kDMA_Modulo8KBytes,        /*!< Circular buffer size is 8 KB. */
    kDMA_Modulo16KBytes,       /*!< Circular buffer size is 16 KB. */
    kDMA_Modulo32KBytes,       /*!< Circular buffer size is 32 KB. */
    kDMA_Modulo64KBytes,       /*!< Circular buffer size is 64 KB. */
    kDMA_Modulo128KBytes,      /*!< Circular buffer size is 128 KB. */
    kDMA_Modulo256KBytes,      /*!< Circular buffer size is 256 KB. */
} dma_modulo_t;

/*! @brief DMA channel link type */
typedef enum _dma_channel_link_type
{
    kDMA_ChannelLinkDisable = 0x0U,      /*!< No channel link. */
    kDMA_ChannelLinkChannel1AndChannel2, /*!< Perform a link to channel LCH1 after each cycle-steal transfer.
                                              followed by a link to LCH2 after the BCR decrements to 0. */
    kDMA_ChannelLinkChannel1,            /*!< Perform a link to LCH1 after each cycle-steal transfer. */
    kDMA_ChannelLinkChannel1AfterBCR0,   /*!< Perform a link to LCH1 after the BCR decrements. */
} dma_channel_link_type_t;

/*! @brief DMA transfer type */
typedef enum _dma_transfer_type
{
    kDMA_MemoryToMemory = 0x0U, /*!< Memory to Memory transfer. */
    kDMA_PeripheralToMemory,    /*!< Peripheral to Memory transfer. */
    kDMA_MemoryToPeripheral,    /*!< Memory to Peripheral transfer. */
} dma_transfer_type_t;

/*! @brief DMA transfer options */
typedef enum _dma_transfer_options
{
    kDMA_NoOptions = 0x0U, /*!< Transfer without options. */
    kDMA_EnableInterrupt,  /*!< Enable interrupt while transfer complete. */
} dma_transfer_options_t;

/*! @brief dma addre increment type */
typedef enum _dma_addr_increment
{
    kDMA_AddrNoIncrement               = 0x0U, /*!< Transfer address not increment. */
    kDMA_AddrIncrementPerTransferWidth = 0x1U, /*!< Transfer address increment per transfer width */
} dma_addr_increment_t;

/*! @brief _dma_transfer_status DMA transfer status */
enum
{
    kStatus_DMA_Busy = MAKE_STATUS(kStatusGroup_DMA, 0), /*!< DMA is busy. */
};

/*! @brief DMA transfer configuration structure */
typedef struct _dma_transfer_config
{
    uint32_t srcAddr;             /*!< DMA transfer source address. */
    uint32_t destAddr;            /*!< DMA destination address.*/
    bool enableSrcIncrement;      /*!< Source address increase after each transfer. */
    dma_transfer_size_t srcSize;  /*!< Source transfer size unit. */
    bool enableDestIncrement;     /*!< Destination address increase after each transfer. */
    dma_transfer_size_t destSize; /*!< Destination transfer unit.*/
    uint32_t transferSize;        /*!< The number of bytes to be transferred. */
} dma_transfer_config_t;

/*! @brief DMA transfer configuration structure */
typedef struct _dma_channel_link_config
{
    dma_channel_link_type_t linkType; /*!< Channel link type. */
    uint32_t channel1;                /*!< The index of channel 1. */
    uint32_t channel2;                /*!< The index of channel 2. */
} dma_channel_link_config_t;

struct _dma_handle;
/*! @brief Callback function prototype for the DMA driver. */
typedef void (*dma_callback)(struct _dma_handle *handle, void *userData);

/*! @brief DMA DMA handle structure */
typedef struct _dma_handle
{
    DMA_Type *base;        /*!< DMA peripheral address. */
    uint8_t channel;       /*!< DMA channel used. */
    dma_callback callback; /*!< DMA callback function.*/
    void *userData;        /*!< Callback parameter. */
} dma_handle_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name DMA Initialization and De-initialization
 * @{
 */

/*!
 * @brief Initializes the DMA peripheral.
 *
 * This function ungates the DMA clock.
 *
 * @param base DMA peripheral base address.
 */
void DMA_Init(DMA_Type *base);

/*!
 * @brief Deinitializes the DMA peripheral.
 *
 * This function gates the DMA clock.
 *
 * @param base DMA peripheral base address.
 */
void DMA_Deinit(DMA_Type *base);

/*! @} */
/*!
 * @name DMA Channel Operation
 * @{
 */

/*!
 * @brief Resets the DMA channel.
 *
 * Sets all register values to reset values and enables
 * the cycle steal and auto stop channel request features.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 */
void DMA_ResetChannel(DMA_Type *base, uint32_t channel);

/*!
 * @brief Configures the DMA transfer attribute.
 *
 * This function configures the transfer attribute including the source address,
 * destination address, transfer size, and so on.
 * This example shows how to set up the dma_transfer_config_t
 * parameters and how to call the DMA_ConfigBasicTransfer function.
 * @code
 *   dma_transfer_config_t transferConfig;
 *   memset(&transferConfig, 0, sizeof(transferConfig));
 *   transferConfig.srcAddr = (uint32_t)srcAddr;
 *   transferConfig.destAddr = (uint32_t)destAddr;
 *   transferConfig.enbaleSrcIncrement = true;
 *   transferConfig.enableDestIncrement = true;
 *   transferConfig.srcSize = kDMA_Transfersize32bits;
 *   transferConfig.destSize = kDMA_Transfersize32bits;
 *   transferConfig.transferSize = sizeof(uint32_t) * BUFF_LENGTH;
 *   DMA_SetTransferConfig(DMA0, 0, &transferConfig);
 * @endcode
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 * @param config Pointer to the DMA transfer configuration structure.
 */
void DMA_SetTransferConfig(DMA_Type *base, uint32_t channel, const dma_transfer_config_t *config);

/*!
 * @brief Configures the DMA channel link feature.
 *
 * This function allows DMA channels to have their transfers linked. The current DMA channel
 * triggers a DMA request to the linked channels (LCH1 or LCH2) depending on the channel link
 * type.
 * Perform a link to channel LCH1 after each cycle-steal transfer followed by a link to LCH2
 * after the BCR decrements to 0 if the type is kDMA_ChannelLinkChannel1AndChannel2.
 * Perform a link to LCH1 after each cycle-steal transfer if the type is kDMA_ChannelLinkChannel1.
 * Perform a link to LCH1 after the BCR decrements to 0 if the type is kDMA_ChannelLinkChannel1AfterBCR0.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 * @param config Pointer to the channel link configuration structure.
 */
void DMA_SetChannelLinkConfig(DMA_Type *base, uint32_t channel, const dma_channel_link_config_t *config);

/*!
 * @brief Sets the DMA source address for the DMA transfer.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 * @param srcAddr DMA source address.
 */
static inline void DMA_SetSourceAddress(DMA_Type *base, uint32_t channel, uint32_t srcAddr)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    base->DMA[channel].SAR = srcAddr;
}

/*!
 * @brief Sets the DMA destination address for the DMA transfer.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 * @param destAddr DMA destination address.
 */
static inline void DMA_SetDestinationAddress(DMA_Type *base, uint32_t channel, uint32_t destAddr)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    base->DMA[channel].DAR = destAddr;
}

/*!
 * @brief Sets the DMA transfer size for the DMA transfer.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 * @param size The number of bytes to be transferred.
 */
static inline void DMA_SetTransferSize(DMA_Type *base, uint32_t channel, uint32_t size)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    base->DMA[channel].DSR_BCR = DMA_DSR_BCR_BCR(size);
}

/*!
 * @brief Sets the DMA modulo for the DMA transfer.
 *
 * This function defines a specific address range specified to be the value after (SAR + SSIZE)/(DAR + DSIZE)
 * calculation is performed or the original register value. It provides the ability to implement a circular
 * data queue easily.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 * @param srcModulo source address modulo.
 * @param destModulo destination address modulo.
 */
void DMA_SetModulo(DMA_Type *base, uint32_t channel, dma_modulo_t srcModulo, dma_modulo_t destModulo);

/*!
 * @brief Enables the DMA cycle steal for the DMA transfer.
 *
 * If the cycle steal feature is enabled (true), the DMA controller forces a single read/write transfer per request,
 *  or it continuously makes read/write transfers until the BCR decrements to 0.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 * @param enable The command for enable (true) or disable (false).
 */
static inline void DMA_EnableCycleSteal(DMA_Type *base, uint32_t channel, bool enable)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    base->DMA[channel].DCR = (base->DMA[channel].DCR & (~DMA_DCR_CS_MASK)) | DMA_DCR_CS(enable);
}

/*!
 * @brief Enables the DMA auto align for the DMA transfer.
 *
 * If the auto align feature is enabled (true), the appropriate address register increments
 * regardless of DINC or SINC.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 * @param enable The command for enable (true) or disable (false).
 */
static inline void DMA_EnableAutoAlign(DMA_Type *base, uint32_t channel, bool enable)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    base->DMA[channel].DCR = (base->DMA[channel].DCR & (~DMA_DCR_AA_MASK)) | DMA_DCR_AA(enable);
}

/*!
 * @brief Enables the DMA async request for the DMA transfer.
 *
 * If the async request feature is enabled (true), the DMA supports asynchronous DREQs
 * while the MCU is in stop mode.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 * @param enable The command for enable (true) or disable (false).
 */
static inline void DMA_EnableAsyncRequest(DMA_Type *base, uint32_t channel, bool enable)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    base->DMA[channel].DCR = (base->DMA[channel].DCR & (~DMA_DCR_EADREQ_MASK)) | DMA_DCR_EADREQ(enable);
}

/*!
 * @brief Enables an interrupt for the DMA transfer.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 */
static inline void DMA_EnableInterrupts(DMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    base->DMA[channel].DCR |= DMA_DCR_EINT(true);
}

/*!
 * @brief Disables an interrupt for the DMA transfer.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 */
static inline void DMA_DisableInterrupts(DMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    base->DMA[channel].DCR &= ~DMA_DCR_EINT_MASK;
}

/*! @} */
/*!
 * @name DMA Channel Transfer Operation
 * @{
 */

/*!
 * @brief Enables the DMA hardware channel request.
 *
 * @param base DMA peripheral base address.
 * @param channel The DMA channel number.
 */
static inline void DMA_EnableChannelRequest(DMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    base->DMA[channel].DCR |= DMA_DCR_ERQ_MASK;
}

/*!
 * @brief Disables the DMA hardware channel request.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 */
static inline void DMA_DisableChannelRequest(DMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    base->DMA[channel].DCR &= ~DMA_DCR_ERQ_MASK;
}

/*!
 * @brief Starts the DMA transfer with a software trigger.
 *
 * This function starts only one read/write iteration.
 *
 * @param base DMA peripheral base address.
 * @param channel The DMA channel number.
 */
static inline void DMA_TriggerChannelStart(DMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    base->DMA[channel].DCR |= DMA_DCR_START_MASK;
}

/*!
 * @brief Starts the DMA enable/disable auto disable request.
 *
 * @param base DMA peripheral base address.
 * @param channel The DMA channel number.
 * @param enable true is enable, false is disable.
 */
static inline void DMA_EnableAutoStopRequest(DMA_Type *base, uint32_t channel, bool enable)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    if (enable)
    {
        base->DMA[channel].DCR |= DMA_DCR_D_REQ(1);
    }
    else
    {
        base->DMA[channel].DCR &= ~DMA_DCR_D_REQ_MASK;
    }
}

/*! @} */
/*!
 * @name DMA Channel Status Operation
 * @{
 */

/*!
 * @brief Gets the remaining bytes of the current DMA transfer.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 * @return The number of bytes which have not been transferred yet.
 */
static inline uint32_t DMA_GetRemainingBytes(DMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    return (base->DMA[channel].DSR_BCR & DMA_DSR_BCR_BCR_MASK) >> DMA_DSR_BCR_BCR_SHIFT;
}

/*!
 * @brief Gets the DMA channel status flags.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 * @return The mask of the channel status. Use the _dma_channel_status_flags
 *         type to decode the return 32 bit variables.
 */
static inline uint32_t DMA_GetChannelStatusFlags(DMA_Type *base, uint32_t channel)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    return base->DMA[channel].DSR_BCR;
}

/*!
 * @brief Clears the DMA channel status flags.
 *
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 * @param mask The mask of the channel status to be cleared. Use
 *             the defined _dma_channel_status_flags type.
 */
static inline void DMA_ClearChannelStatusFlags(DMA_Type *base, uint32_t channel, uint32_t mask)
{
    assert(channel < (uint32_t)FSL_FEATURE_DMA_MODULE_CHANNEL);

    if (mask != 0U)
    {
        base->DMA[channel].DSR_BCR |= DMA_DSR_BCR_DONE(true);
    }
}

/*! @} */
/*!
 * @name DMA Channel Transactional Operation
 * @{
 */

/*!
 * @brief Creates the DMA handle.
 *
 * This function is called first if using the transactional API for the DMA. This function
 * initializes the internal state of the DMA handle.
 *
 * @param handle DMA handle pointer. The DMA handle stores callback function and
 *               parameters.
 * @param base DMA peripheral base address.
 * @param channel DMA channel number.
 */
void DMA_CreateHandle(dma_handle_t *handle, DMA_Type *base, uint32_t channel);

/*!
 * @brief Sets the DMA callback function.
 *
 * This callback is called in the DMA IRQ handler. Use the callback to do something
 * after the current transfer complete.
 *
 * @param handle DMA handle pointer.
 * @param callback DMA callback function pointer.
 * @param userData Parameter for callback function. If it is not needed, just set to NULL.
 */
void DMA_SetCallback(dma_handle_t *handle, dma_callback callback, void *userData);

/*!
 * @brief Prepares the DMA transfer configuration structure.
 *
 * This function prepares the transfer configuration structure according to the user input.
 * The difference between this function and DMA_PrepareTransfer is that this function expose the address increment
 * parameter to application, but in DMA_PrepareTransfer, only parts of the address increment option can be selected by
 * dma_transfer_type_t.
 *
 * @param config Pointer to the user configuration structure of type dma_transfer_config_t.
 * @param srcAddr DMA transfer source address.
 * @param srcWidth DMA transfer source address width (byte).
 * @param destAddr DMA transfer destination address.
 * @param destWidth DMA transfer destination address width (byte).
 * @param transferBytes DMA transfer bytes to be transferred.
 * @param srcIncrement source address increment type.
 * @param destIncrement dest address increment type.
 */
void DMA_PrepareTransferConfig(dma_transfer_config_t *config,
                               void *srcAddr,
                               uint32_t srcWidth,
                               void *destAddr,
                               uint32_t destWidth,
                               uint32_t transferBytes,
                               dma_addr_increment_t srcIncrement,
                               dma_addr_increment_t destIncrement);

/*!
 * @brief Prepares the DMA transfer configuration structure.
 *
 * This function prepares the transfer configuration structure according to the user input.
 *
 * @param config Pointer to the user configuration structure of type dma_transfer_config_t.
 * @param srcAddr DMA transfer source address.
 * @param srcWidth DMA transfer source address width (byte).
 * @param destAddr DMA transfer destination address.
 * @param destWidth DMA transfer destination address width (byte).
 * @param transferBytes DMA transfer bytes to be transferred.
 * @param type DMA transfer type.
 */
void DMA_PrepareTransfer(dma_transfer_config_t *config,
                         void *srcAddr,
                         uint32_t srcWidth,
                         void *destAddr,
                         uint32_t destWidth,
                         uint32_t transferBytes,
                         dma_transfer_type_t type);

/*!
 * @brief Submits the DMA transfer request.
 *
 * This function submits the DMA transfer request according to the transfer configuration structure.
 *
 * @param handle DMA handle pointer.
 * @param config Pointer to DMA transfer configuration structure.
 * @param options Additional configurations for transfer. Use
 *                the defined dma_transfer_options_t type.
 * @retval kStatus_DMA_Success It indicates that the DMA submit transfer request succeeded.
 * @retval kStatus_DMA_Busy It indicates that the DMA is busy. Submit transfer request is not allowed.
 * @note This function can't process multi transfer request.
 */
status_t DMA_SubmitTransfer(dma_handle_t *handle, const dma_transfer_config_t *config, uint32_t options);

/*!
 * @brief DMA starts a transfer.
 *
 * This function enables the channel request. Call this function
 * after submitting a transfer request.
 *
 * @param handle DMA handle pointer.
 * @retval kStatus_DMA_Success It indicates that the DMA start transfer succeed.
 * @retval kStatus_DMA_Busy It indicates that the DMA has started a transfer.
 */
static inline void DMA_StartTransfer(dma_handle_t *handle)
{
    assert(handle != NULL);

    handle->base->DMA[handle->channel].DCR |= DMA_DCR_ERQ_MASK;
}

/*!
 * @brief DMA stops a transfer.
 *
 * This function disables the channel request to stop a DMA transfer.
 * The transfer can be resumed by calling the DMA_StartTransfer.
 *
 * @param handle DMA handle pointer.
 */
static inline void DMA_StopTransfer(dma_handle_t *handle)
{
    assert(handle != NULL);

    handle->base->DMA[handle->channel].DCR &= ~DMA_DCR_ERQ_MASK;
}

/*!
 * @brief DMA aborts a transfer.
 *
 * This function disables the channel request and clears all status bits.
 * Submit another transfer after calling this API.
 *
 * @param handle DMA handle pointer.
 */
void DMA_AbortTransfer(dma_handle_t *handle);

/*!
 * @brief DMA IRQ handler for current transfer complete.
 *
 * This function clears the channel interrupt flag and calls
 * the callback function if it is not NULL.
 *
 * @param handle DMA handle pointer.
 */
void DMA_HandleIRQ(dma_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* FSL_DMA_H_ */
