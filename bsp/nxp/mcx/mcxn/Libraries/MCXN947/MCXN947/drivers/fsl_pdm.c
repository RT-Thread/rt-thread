/*
 * Copyright (c) 2018, Freescale Semiconductor, Inc.
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pdm.h"
/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.pdm"
#endif

/*******************************************************************************
 * Definitations
 ******************************************************************************/
/*! @brief Typedef for pdm rx interrupt handler. */
typedef void (*pdm_isr_t)(PDM_Type *base, pdm_handle_t *pdmHandle);
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if !(defined FSL_FEATURE_PDM_HAS_NO_MINIMUM_CLKDIV && FSL_FEATURE_PDM_HAS_NO_MINIMUM_CLKDIV)
/*!
 * @brief Get the instance number for PDM.
 *
 * @param channelMask enabled channel.
 * @param qualitymode selected quality mode.
 * @param osr      oversample rate.
 * @param regdiv   register divider.
 */
static status_t PDM_ValidateSrcClockRate(uint32_t channelMask,
                                         pdm_df_quality_mode_t qualityMode,
                                         uint8_t osr,
                                         uint32_t regDiv);
#endif

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Base pointer array */
static PDM_Type *const s_pdmBases[] = PDM_BASE_PTRS;
/*!@brief PDM handle pointer */
static pdm_handle_t *s_pdmHandle[ARRAY_SIZE(s_pdmBases)];
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Clock name array */
static const clock_ip_name_t s_pdmClock[] = PDM_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if defined(FSL_PDM_HAS_FILTER_CLOCK_GATE) && FSL_PDM_HAS_FILTER_CLOCK_GATE
/* Clock name array */
static const clock_ip_name_t s_pdmFilterClock[] = PDM_FILTER_CLOCKS;
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointer to tx IRQ handler for each instance. */
static pdm_isr_t s_pdmIsr;
#if !(defined(FSL_FEATURE_PDM_HAS_NO_HWVAD) && FSL_FEATURE_PDM_HAS_NO_HWVAD)
/*! @brief callback for hwvad. */
static pdm_hwvad_notification_t s_pdm_hwvad_notification[ARRAY_SIZE(s_pdmBases)];
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t PDM_GetInstance(PDM_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_pdmBases); instance++)
    {
        if (s_pdmBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_pdmBases));

    return instance;
}

/*!
 * brief PDM read fifo.
 * Note: This function support 16 bit only for IP version that only supports 16bit.
 *
 * param base PDM base pointer.
 * param startChannel start channel number.
 * param channelNums total enabled channelnums.
 * param buffer received buffer address.
 * param size number of samples to read.
 * param dataWidth sample width.
 */
void PDM_ReadFifo(
    PDM_Type *base, uint32_t startChannel, uint32_t channelNums, void *buffer, size_t size, uint32_t dataWidth)
{
    uint32_t i = 0, j = 0U;
    uint32_t *dataAddr = (uint32_t *)buffer;

    for (i = 0U; i < size; i++)
    {
        for (j = 0; j < channelNums; j++)
        {
#if defined(FSL_FEATURE_PDM_FIFO_WIDTH) && (FSL_FEATURE_PDM_FIFO_WIDTH != 2U)
            *dataAddr = base->DATACH[startChannel + j] >> (dataWidth == 4U ? 0U : 8U);
            dataAddr  = (uint32_t *)((uint32_t)dataAddr + dataWidth);
#else
            *dataAddr = base->DATACH[startChannel + j];
            dataAddr  = (uint32_t *)((uint32_t)dataAddr + 2U);
#endif
        }
    }
}

#if defined(FSL_FEATURE_PDM_FIFO_WIDTH) && (FSL_FEATURE_PDM_FIFO_WIDTH == 2U)
/*!
 * brief PDM read data non blocking, only support 16bit data read.
 * So the actually read data byte size in this function is (size * 2 * channelNums).
 * param base PDM base pointer.
 * param startChannel start channel number.
 * param channelNums total enabled channelnums.
 * param buffer received buffer address.
 * param size number of 16bit data to read.
 */
void PDM_ReadNonBlocking(PDM_Type *base, uint32_t startChannel, uint32_t channelNums, int16_t *buffer, size_t size)
{
    uint32_t i = 0, j = 0U;

    for (i = 0U; i < size; i++)
    {
        for (j = 0; j < channelNums; j++)
        {
            *buffer++ = (int16_t)base->DATACH[startChannel + j];
        }
    }
}
#endif

#if !(defined FSL_FEATURE_PDM_HAS_NO_MINIMUM_CLKDIV && FSL_FEATURE_PDM_HAS_NO_MINIMUM_CLKDIV)
static status_t PDM_ValidateSrcClockRate(uint32_t channelMask,
                                         pdm_df_quality_mode_t qualityMode,
                                         uint8_t osr,
                                         uint32_t regDiv)
{
    uint32_t enabledChannel = 0U, i = 0U, factor = 0U, k = 0U;

    for (i = 0U; i < (uint32_t)FSL_FEATURE_PDM_CHANNEL_NUM; i++)
    {
        if (((channelMask >> i) & 0x01U) != 0U)
        {
            enabledChannel++;
        }
    }

    switch (qualityMode)
    {
        case kPDM_QualityModeMedium:
            factor = FSL_FEATURE_PDM_HIGH_QUALITY_CLKDIV_FACTOR;
            k      = 2U;
            break;

        case kPDM_QualityModeHigh:
            factor = FSL_FEATURE_PDM_HIGH_QUALITY_CLKDIV_FACTOR;
            k      = 1U;
            break;

        case kPDM_QualityModeLow:
            factor = FSL_FEATURE_PDM_HIGH_QUALITY_CLKDIV_FACTOR;
            k      = 4U;
            break;

        case kPDM_QualityModeVeryLow0:
            factor = FSL_FEATURE_PDM_VERY_LOW_QUALITY_CLKDIV_FACTOR;
            k      = 2U;
            break;

        case kPDM_QualityModeVeryLow1:
            factor = FSL_FEATURE_PDM_VERY_LOW_QUALITY_CLKDIV_FACTOR;
            k      = 4U;
            break;

        case kPDM_QualityModeVeryLow2:
            factor = FSL_FEATURE_PDM_VERY_LOW_QUALITY_CLKDIV_FACTOR;
            k      = 8U;
            break;

        default:
            assert(false);
            break;
    }

    /* validate the minimum clock divider */
    /* 2U is for canculating k, 100U is for determing the specific float number of clock divider */
    if (((regDiv * k) / 2U * 100U) < (((10U + factor * enabledChannel) * 100U / (8U * osr)) * k / 2U))
    {
        return kStatus_Fail;
    }

    return kStatus_Success;
}
#endif

/*!
 * brief PDM set sample rate.
 *
 * note This function is depend on the configuration of the PDM and PDM channel, so the correct call sequence is
 * code
 * PDM_Init(base, pdmConfig)
 * PDM_SetChannelConfig(base, channel, &channelConfig)
 * PDM_SetSampleRateConfig(base, source, sampleRate)
 * endcode
 * param base PDM base pointer
 * param sourceClock_HZ PDM source clock frequency.
 * param sampleRate_HZ PDM sample rate.
 */
status_t PDM_SetSampleRateConfig(PDM_Type *base, uint32_t sourceClock_HZ, uint32_t sampleRate_HZ)
{
    uint32_t osr = (base->CTRL_2 & PDM_CTRL_2_CICOSR_MASK) >> PDM_CTRL_2_CICOSR_SHIFT;
#if !(defined FSL_FEATURE_PDM_HAS_NO_MINIMUM_CLKDIV && FSL_FEATURE_PDM_HAS_NO_MINIMUM_CLKDIV)
    pdm_df_quality_mode_t qualityMode =
        (pdm_df_quality_mode_t)(uint32_t)((base->CTRL_2 & PDM_CTRL_2_QSEL_MASK) >> PDM_CTRL_2_QSEL_SHIFT);
    uint32_t enabledChannelMask = base->CTRL_1 & (uint32_t)kPDM_EnableChannelAll;
#endif

    uint32_t pdmClockRate = 0U;
    uint32_t regDiv       = 0U;

    /* get divider */
    osr          = 16U - osr;
    pdmClockRate = sampleRate_HZ * osr * 8U;
    regDiv       = sourceClock_HZ / pdmClockRate;

    if (regDiv > PDM_CTRL_2_CLKDIV_MASK)
    {
        return kStatus_Fail;
    }

#if !(defined FSL_FEATURE_PDM_HAS_NO_MINIMUM_CLKDIV && FSL_FEATURE_PDM_HAS_NO_MINIMUM_CLKDIV)
    if (PDM_ValidateSrcClockRate(enabledChannelMask, qualityMode, (uint8_t)osr, regDiv) == kStatus_Fail)
    {
        return kStatus_Fail;
    }
#endif

    base->CTRL_2 = (base->CTRL_2 & (~PDM_CTRL_2_CLKDIV_MASK)) | PDM_CTRL_2_CLKDIV(regDiv);

    return kStatus_Success;
}

/*!
 * brief PDM set sample rate.
 *
 * deprecated Do not use this function.  It has been superceded by @ref PDM_SetSampleRateConfig
 * param base PDM base pointer
 * param enableChannelMask PDM channel enable mask.
 * param qualityMode quality mode.
 * param osr cic oversample rate
 * param clkDiv clock divider
 */
status_t PDM_SetSampleRate(
    PDM_Type *base, uint32_t enableChannelMask, pdm_df_quality_mode_t qualityMode, uint8_t osr, uint32_t clkDiv)
{
#if !(defined FSL_FEATURE_PDM_HAS_NO_MINIMUM_CLKDIV && FSL_FEATURE_PDM_HAS_NO_MINIMUM_CLKDIV)
    uint8_t realOsr = 16U - (osr & (PDM_CTRL_2_CICOSR_MASK >> PDM_CTRL_2_CICOSR_SHIFT));
#endif
    uint32_t regDiv = clkDiv >> 1U;

    switch (qualityMode)
    {
        case kPDM_QualityModeHigh:
            regDiv <<= 1U;
            break;
        case kPDM_QualityModeLow:
        case kPDM_QualityModeVeryLow1:
            regDiv >>= 1U;
            break;
        case kPDM_QualityModeVeryLow2:
            regDiv >>= 2U;
            break;
        default:
            assert(false);
            break;
    }

#if !(defined FSL_FEATURE_PDM_HAS_NO_MINIMUM_CLKDIV && FSL_FEATURE_PDM_HAS_NO_MINIMUM_CLKDIV)
    if (PDM_ValidateSrcClockRate(enableChannelMask, qualityMode, realOsr, regDiv) == kStatus_Fail)
    {
        return kStatus_Fail;
    }
#endif

    assert(regDiv <= PDM_CTRL_2_CLKDIV_MASK);
    base->CTRL_2 = (base->CTRL_2 & (~PDM_CTRL_2_CLKDIV_MASK)) | PDM_CTRL_2_CLKDIV(regDiv);

    return kStatus_Success;
}

/*!
 * brief Initializes the PDM peripheral.
 *
 * Ungates the PDM clock, resets the module, and configures PDM with a configuration structure.
 * The configuration structure can be custom filled or set with default values by
 * PDM_GetDefaultConfig().
 *
 * note  This API should be called at the beginning of the application to use
 * the PDM driver. Otherwise, accessing the PDM module can cause a hard fault
 * because the clock is not enabled.
 *
 * param base PDM base pointer
 * param config PDM configuration structure.
 */
void PDM_Init(PDM_Type *base, const pdm_config_t *config)
{
    assert(config != NULL);
    assert(config->fifoWatermark <= PDM_FIFO_CTRL_FIFOWMK_MASK);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable the PDM clock */
    CLOCK_EnableClock(s_pdmClock[PDM_GetInstance(base)]);
#if defined(FSL_PDM_HAS_FILTER_CLOCK_GATE) && FSL_PDM_HAS_FILTER_CLOCK_GATE
    CLOCK_EnableClock(s_pdmFilterClock[PDM_GetInstance(base)]);
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Enable the module and disable the interface/all channel */
    base->CTRL_1 &=
        ~(PDM_CTRL_1_MDIS_MASK | PDM_CTRL_1_PDMIEN_MASK | PDM_CTRL_1_ERREN_MASK | (uint32_t)kPDM_EnableChannelAll);

    /* wait all filter stopped */
    while ((base->STAT & PDM_STAT_BSY_FIL_MASK) != 0U)
    {
    }

    /* software reset */
    base->CTRL_1 |= PDM_CTRL_1_SRES_MASK;

    /* Set the configure settings */
    base->CTRL_1 = (base->CTRL_1 & (~PDM_CTRL_1_DOZEN_MASK)) | PDM_CTRL_1_DOZEN(config->enableDoze);

    base->CTRL_2 = (base->CTRL_2 & (~(PDM_CTRL_2_CICOSR_MASK | PDM_CTRL_2_QSEL_MASK))) |
                   PDM_CTRL_2_CICOSR(config->cicOverSampleRate) | PDM_CTRL_2_QSEL(config->qualityMode);

    /* Set the watermark */
    base->FIFO_CTRL = PDM_FIFO_CTRL_FIFOWMK(config->fifoWatermark);
}

/*!
 * brief De-initializes the PDM peripheral.
 *
 * This API gates the PDM clock. The PDM module can't operate unless PDM_Init
 * is called to enable the clock.
 *
 * param base PDM base pointer
 */
void PDM_Deinit(PDM_Type *base)
{
    /* disable PDM interface */
    PDM_Enable(base, false);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(s_pdmClock[PDM_GetInstance(base)]);
#if defined(FSL_PDM_HAS_FILTER_CLOCK_GATE) && FSL_PDM_HAS_FILTER_CLOCK_GATE
    CLOCK_DisableClock(s_pdmFilterClock[PDM_GetInstance(base)]);
#endif
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Enables the PDM interrupt requests.
 *
 * param base PDM base pointer
 * param mask interrupt source
 *     The parameter can be a combination of the following sources if defined.
 *     arg kPDM_ErrorInterruptEnable
 *     arg kPDM_FIFOInterruptEnable
 */
void PDM_EnableInterrupts(PDM_Type *base, uint32_t mask)
{
    if ((mask & (uint32_t)kPDM_FIFOInterruptEnable) != 0U)
    {
        base->CTRL_1 = (base->CTRL_1 & (~PDM_CTRL_1_DISEL_MASK)) | (uint32_t)kPDM_FIFOInterruptEnable;
    }
    if ((mask & (uint32_t)kPDM_ErrorInterruptEnable) != 0U)
    {
        base->CTRL_1 = (base->CTRL_1 & (~PDM_CTRL_1_ERREN_MASK)) | (uint32_t)kPDM_ErrorInterruptEnable;
    }
}

/*!
 * brief PDM one channel configurations.
 *
 * param base PDM base pointer
 * param config PDM channel configurations.
 * param channel channel number.
 * after completing the current frame in debug mode.
 */
void PDM_SetChannelConfig(PDM_Type *base, uint32_t channel, const pdm_channel_config_t *config)
{
    assert(config != NULL);
    assert(channel <= (uint32_t)FSL_FEATURE_PDM_CHANNEL_NUM);

    uint32_t dcCtrl = 0U;

#if (defined(FSL_FEATURE_PDM_HAS_DC_OUT_CTRL) && (FSL_FEATURE_PDM_HAS_DC_OUT_CTRL))
    dcCtrl = base->DC_OUT_CTRL;
    /* configure gain and cut off freq */
    dcCtrl &= ~((uint32_t)PDM_DC_OUT_CTRL_DCCONFIG0_MASK << (channel << 1U));
    dcCtrl |= (uint32_t)config->outputCutOffFreq << (channel << 1U);
    base->DC_OUT_CTRL = dcCtrl;
#endif

#if !(defined(FSL_FEATURE_PDM_DC_CTRL_VALUE_FIXED) && (FSL_FEATURE_PDM_DC_CTRL_VALUE_FIXED))
    dcCtrl = base->DC_CTRL;
    /* configure gain and cut off freq */
    dcCtrl &= ~((uint32_t)PDM_DC_CTRL_DCCONFIG0_MASK << (channel << 1U));
    dcCtrl |= (uint32_t)config->cutOffFreq << (channel << 1U);
    base->DC_CTRL = dcCtrl;
#endif

    PDM_SetChannelGain(base, channel, config->gain);

    /* enable channel */
    base->CTRL_1 |= 1UL << channel;
}

/*!
 * brief Set the PDM channel gain.
 *
 * Please note for different quality mode, the valid gain value is different, reference RM for detail.
 * param base PDM base pointer.
 * param channel PDM channel index.
 * param gain channel gain, the register gain value range is 0 - 15.
 */
void PDM_SetChannelGain(PDM_Type *base, uint32_t channel, pdm_df_output_gain_t gain)
{
    assert(channel <= (uint32_t)FSL_FEATURE_PDM_CHANNEL_NUM);

#if defined(FSL_FEATURE_PDM_HAS_RANGE_CTRL) && FSL_FEATURE_PDM_HAS_RANGE_CTRL
    uint32_t outCtrl = base->RANGE_CTRL;
#else
    uint32_t outCtrl = base->OUT_CTRL;
#endif

#if defined(FSL_FEATURE_PDM_HAS_RANGE_CTRL) && FSL_FEATURE_PDM_HAS_RANGE_CTRL
    outCtrl &= ~((uint32_t)PDM_RANGE_CTRL_RANGEADJ0_MASK << (channel << 2U));
#else
    outCtrl &= ~((uint32_t)PDM_OUT_CTRL_OUTGAIN0_MASK << (channel << 2U));
#endif

    outCtrl |= (uint32_t)gain << (channel << 2U);

#if defined(FSL_FEATURE_PDM_HAS_RANGE_CTRL) && FSL_FEATURE_PDM_HAS_RANGE_CTRL
    base->RANGE_CTRL = outCtrl;
#else
    base->OUT_CTRL = outCtrl;
#endif
}

/*!
 * brief PDM set channel transfer config.
 *
 * param base PDM base pointer.
 * param handle PDM handle pointer.
 * param channel PDM channel.
 * param config channel config.
 * param format data format.
 */
status_t PDM_TransferSetChannelConfig(
    PDM_Type *base, pdm_handle_t *handle, uint32_t channel, const pdm_channel_config_t *config, uint32_t format)
{
    assert(handle != NULL);

    PDM_SetChannelConfig(base, channel, config);

    handle->format = format;

    if (handle->channelNums == 0U)
    {
        handle->startChannel = (uint8_t)channel;
    }

    handle->channelNums++;

    if (handle->channelNums > (uint8_t)FSL_FEATURE_PDM_CHANNEL_NUM)
    {
        return kStatus_PDM_ChannelConfig_Failed;
    }

    return kStatus_Success;
}

/*!
 * brief Initializes the PDM handle.
 *
 * This function initializes the handle for the PDM transactional APIs. Call
 * this function once to get the handle initialized.
 *
 * param base PDM base pointer.
 * param handle PDM handle pointer.
 * param callback Pointer to the user callback function.
 * param userData User parameter passed to the callback function.
 */
void PDM_TransferCreateHandle(PDM_Type *base, pdm_handle_t *handle, pdm_transfer_callback_t callback, void *userData)
{
    assert(handle != NULL);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    s_pdmHandle[PDM_GetInstance(base)] = handle;

    handle->callback  = callback;
    handle->userData  = userData;
    handle->watermark = (uint8_t)(base->FIFO_CTRL & PDM_FIFO_CTRL_FIFOWMK_MASK);

    /* Set the isr pointer */
    s_pdmIsr = PDM_TransferHandleIRQ;

    /* Enable RX event IRQ */
    (void)EnableIRQ(PDM_EVENT_IRQn);
#if !(defined FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ && FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ)
    /* Enable FIFO error IRQ */
    (void)EnableIRQ(PDM_ERROR_IRQn);
#endif
}

/*!
 * brief Performs an interrupt non-blocking receive transfer on PDM.
 *
 * note This API returns immediately after the transfer initiates.
 * Call the PDM_RxGetTransferStatusIRQ to poll the transfer status and check whether
 * the transfer is finished. If the return status is not kStatus_PDM_Busy, the transfer
 * is finished.
 *
 * param base PDM base pointer
 * param handle Pointer to the pdm_handle_t structure which stores the transfer state.
 * param xfer Pointer to the pdm_transfer_t structure.
 * retval kStatus_Success Successfully started the data receive.
 * retval kStatus_PDM_Busy Previous receive still not finished.
 */
status_t PDM_TransferReceiveNonBlocking(PDM_Type *base, pdm_handle_t *handle, pdm_transfer_t *xfer)
{
    assert(handle != NULL);

    /* Check if the queue is full */
    if (handle->pdmQueue[handle->queueUser].data != NULL)
    {
        return kStatus_PDM_QueueFull;
    }

    /* Add into queue */
    handle->transferSize[handle->queueUser]      = xfer->dataSize;
    handle->pdmQueue[handle->queueUser].data     = xfer->data;
    handle->pdmQueue[handle->queueUser].dataSize = xfer->dataSize;
    handle->queueUser                            = (handle->queueUser + 1U) % PDM_XFER_QUEUE_SIZE;

    /* Set state to busy */
    handle->state = kStatus_PDM_Busy;

    /* Enable interrupt */
    PDM_EnableInterrupts(base, (uint32_t)kPDM_FIFOInterruptEnable);

    PDM_Enable(base, true);

    return kStatus_Success;
}

/*!
 * brief Aborts the current IRQ receive.
 *
 * note This API can be called when an interrupt non-blocking transfer initiates
 * to abort the transfer early.
 *
 * param base PDM base pointer
 * param handle Pointer to the pdm_handle_t structure which stores the transfer state.
 */
void PDM_TransferAbortReceive(PDM_Type *base, pdm_handle_t *handle)
{
    assert(handle != NULL);

    /* Use FIFO request interrupt and fifo error */
    PDM_DisableInterrupts(base, (uint32_t)kPDM_FIFOInterruptEnable | (uint32_t)kPDM_ErrorInterruptEnable);
    PDM_Enable(base, false);
    handle->state = kStatus_PDM_Idle;
    /* Clear the queue */
    (void)memset(handle->pdmQueue, 0, sizeof(pdm_transfer_t) * PDM_XFER_QUEUE_SIZE);
    handle->queueDriver = 0;
    handle->queueUser   = 0;
}

/*!
 * brief Tx interrupt handler.
 *
 * param base PDM base pointer.
 * param handle Pointer to the pdm_handle_t structure.
 */
void PDM_TransferHandleIRQ(PDM_Type *base, pdm_handle_t *handle)
{
    assert(handle != NULL);

#if (defined FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ && FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ)
    uint32_t status = 0U;

#if (defined(FSL_FEATURE_PDM_HAS_STATUS_LOW_FREQ) && (FSL_FEATURE_PDM_HAS_STATUS_LOW_FREQ == 1U))
    if (PDM_GetStatus(base) & PDM_STAT_LOWFREQF_MASK)
    {
        PDM_ClearStatus(base, PDM_STAT_LOWFREQF_MASK);
        if (handle->callback != NULL)
        {
            (handle->callback)(base, handle, kStatus_PDM_CLK_LOW, handle->userData);
        }
    }
#endif
    status = PDM_GetFifoStatus(base);
    if (status != 0U)
    {
        PDM_ClearFIFOStatus(base, status);
        if (handle->callback != NULL)
        {
            (handle->callback)(base, handle, kStatus_PDM_FIFO_ERROR, handle->userData);
        }
    }

#if !(defined(FSL_FEATURE_PDM_HAS_RANGE_CTRL) && FSL_FEATURE_PDM_HAS_RANGE_CTRL)
    status = PDM_GetOutputStatus(base);
    if (status != 0U)
    {
        PDM_ClearOutputStatus(base, status);
        if (handle->callback != NULL)
        {
            (handle->callback)(base, handle, kStatus_PDM_Output_ERROR, handle->userData);
        }
    }
#endif
#endif

    /* Handle transfer */
    if (((base->STAT & 0xFFU) != 0U) && (handle->channelNums != 0U) &&
        ((base->CTRL_1 & PDM_CTRL_1_DISEL_MASK) == (0x2UL << PDM_CTRL_1_DISEL_SHIFT)))
    {
        PDM_ClearStatus(base, 0xFFU);
        /* Judge if the data need to transmit is less than space */
        uint8_t size = (uint8_t)MIN((handle->pdmQueue[handle->queueDriver].dataSize),
                                    ((uint32_t)handle->watermark * handle->channelNums * handle->format));

        PDM_ReadFifo(base, handle->startChannel, handle->channelNums,
                     (uint8_t *)(uint32_t)handle->pdmQueue[handle->queueDriver].data,
                     ((size_t)size / handle->channelNums / handle->format), handle->format);

        /* Update the internal counter */
        handle->pdmQueue[handle->queueDriver].dataSize -= size;
        handle->pdmQueue[handle->queueDriver].data = &(handle->pdmQueue[handle->queueDriver].data[size]);
    }

    /* If finished a block, call the callback function */
    if (handle->pdmQueue[handle->queueDriver].dataSize == 0U)
    {
        handle->pdmQueue[handle->queueDriver].data = NULL;
        handle->queueDriver                        = (handle->queueDriver + 1U) % PDM_XFER_QUEUE_SIZE;
        if (handle->callback != NULL)
        {
            (handle->callback)(base, handle, kStatus_PDM_Idle, handle->userData);
        }
    }

    /* If all data finished, just stop the transfer */
    if (handle->pdmQueue[handle->queueDriver].data == NULL)
    {
        PDM_TransferAbortReceive(base, handle);
    }
}

#if !(defined(FSL_FEATURE_PDM_HAS_NO_HWVAD) && FSL_FEATURE_PDM_HAS_NO_HWVAD)
/*!
 * brief set HWVAD in envelope based mode .
 * Recommand configurations,
 * code
 * static const pdm_hwvad_config_t hwvadConfig = {
 *   .channel           = 0,
 *   .initializeTime    = 10U,
 *   .cicOverSampleRate = 0U,
 *   .inputGain         = 0U,
 *   .frameTime         = 10U,
 *   .cutOffFreq        = kPDM_HwvadHpfBypassed,
 *   .enableFrameEnergy = false,
 *   .enablePreFilter   = true,
};

 * static const pdm_hwvad_noise_filter_t noiseFilterConfig = {
 *   .enableAutoNoiseFilter = false,
 *   .enableNoiseMin        = true,
 *   .enableNoiseDecimation = true,
 *   .noiseFilterAdjustment = 0U,
 *   .noiseGain             = 7U,
 *   .enableNoiseDetectOR   = true,
 * };
 * code
 * param base PDM base pointer.
 * param hwvadConfig internal filter status.
 * param noiseConfig Voice activity detector noise filter configure structure pointer.
 * param zcdConfig Voice activity detector zero cross detector configure structure pointer .
 * param signalGain signal gain value.
 */
void PDM_SetHwvadInEnvelopeBasedMode(PDM_Type *base,
                                     const pdm_hwvad_config_t *hwvadConfig,
                                     const pdm_hwvad_noise_filter_t *noiseConfig,
                                     const pdm_hwvad_zero_cross_detector_t *zcdConfig,
                                     uint32_t signalGain)
{
    assert(hwvadConfig != NULL);
    assert(noiseConfig != NULL);

    uint32_t i = 0U;

    PDM_SetHwvadConfig(base, hwvadConfig);
    PDM_SetHwvadSignalFilterConfig(base, true, signalGain);
    PDM_SetHwvadNoiseFilterConfig(base, noiseConfig);
    PDM_EnableHwvad(base, true);

    if (NULL != zcdConfig)
    {
        PDM_SetHwvadZeroCrossDetectorConfig(base, zcdConfig);
    }

    PDM_Enable(base, true);

    while (PDM_GetHwvadInitialFlag(base) != 0U)
    {
    }

    for (i = 0; i < 3U; i++)
    {
        /* set HWVAD interal filter stauts initial */
        PDM_SetHwvadInternalFilterStatus(base, kPDM_HwvadInternalFilterInitial);
    }

    PDM_SetHwvadInternalFilterStatus(base, kPDM_HwvadInternalFilterNormalOperation);
}

/*!
 * brief set HWVAD in energy based mode .
 * Recommand configurations,
 * code
 * static const pdm_hwvad_config_t hwvadConfig = {
 *   .channel           = 0,
 *   .initializeTime    = 10U,
 *   .cicOverSampleRate = 0U,
 *   .inputGain         = 0U,
 *   .frameTime         = 10U,
 *   .cutOffFreq        = kPDM_HwvadHpfBypassed,
 *   .enableFrameEnergy = true,
 *   .enablePreFilter   = true,
};

 * static const pdm_hwvad_noise_filter_t noiseFilterConfig = {
 *   .enableAutoNoiseFilter = true,
 *   .enableNoiseMin        = false,
 *   .enableNoiseDecimation = false,
 *   .noiseFilterAdjustment = 0U,
 *   .noiseGain             = 7U,
 *   .enableNoiseDetectOR   = false,
 * };
 * code
 * param base PDM base pointer.
 * param hwvadConfig internal filter status.
 * param noiseConfig Voice activity detector noise filter configure structure pointer.
 * param zcdConfig Voice activity detector zero cross detector configure structure pointer .
 * param signalGain signal gain value, signal gain value should be properly according to application.
 */
void PDM_SetHwvadInEnergyBasedMode(PDM_Type *base,
                                   const pdm_hwvad_config_t *hwvadConfig,
                                   const pdm_hwvad_noise_filter_t *noiseConfig,
                                   const pdm_hwvad_zero_cross_detector_t *zcdConfig,
                                   uint32_t signalGain)
{
    assert(hwvadConfig != NULL);
    assert(noiseConfig != NULL);

    PDM_SetHwvadConfig(base, hwvadConfig);
    /* signal filter need to disable, but signal gain value should be set */
    base->VAD0_SCONFIG = PDM_VAD0_SCONFIG_VADSGAIN(signalGain);
    PDM_SetHwvadNoiseFilterConfig(base, noiseConfig);
    PDM_EnableHwvad(base, true);

    if (NULL != zcdConfig)
    {
        PDM_SetHwvadZeroCrossDetectorConfig(base, zcdConfig);
    }

    PDM_Enable(base, true);
}

/*!
 * brief Configure voice activity detector.
 *
 * param base PDM base pointer
 * param config Voice activity detector configure structure pointer .
 */
void PDM_SetHwvadConfig(PDM_Type *base, const pdm_hwvad_config_t *config)
{
    assert(config != NULL);

    uint32_t ctrl1 = base->VAD0_CTRL_1;

    /* Configure VAD0_CTRL_1 register */
    ctrl1 &= ~(PDM_VAD0_CTRL_1_VADCHSEL_MASK | PDM_VAD0_CTRL_1_VADCICOSR_MASK | PDM_VAD0_CTRL_1_VADINITT_MASK);
    ctrl1 |= (PDM_VAD0_CTRL_1_VADCHSEL(config->channel) | PDM_VAD0_CTRL_1_VADCICOSR(config->cicOverSampleRate) |
              PDM_VAD0_CTRL_1_VADINITT(config->initializeTime));
    base->VAD0_CTRL_1 = ctrl1;

    /* Configure VAD0_CTRL_2 register */
    base->VAD0_CTRL_2 =
        (PDM_VAD0_CTRL_2_VADFRENDIS((config->enableFrameEnergy == true) ? 0U : 1U) |
         PDM_VAD0_CTRL_2_VADPREFEN(config->enablePreFilter) | PDM_VAD0_CTRL_2_VADFRAMET(config->frameTime) |
         PDM_VAD0_CTRL_2_VADINPGAIN(config->inputGain) | PDM_VAD0_CTRL_2_VADHPF(config->cutOffFreq));
}

/*!
 * brief Configure voice activity detector signal filter.
 *
 * param base PDM base pointer
 * param enableMaxBlock If signal maximum block enabled.
 * param signalGain Gain value for the signal energy.
 */
void PDM_SetHwvadSignalFilterConfig(PDM_Type *base, bool enableMaxBlock, uint32_t signalGain)
{
    uint32_t signalConfig = base->VAD0_SCONFIG;

    signalConfig &= ~(PDM_VAD0_SCONFIG_VADSMAXEN_MASK | PDM_VAD0_SCONFIG_VADSGAIN_MASK);
    signalConfig |= (PDM_VAD0_SCONFIG_VADSMAXEN(enableMaxBlock) | PDM_VAD0_SCONFIG_VADSGAIN(signalGain)) |
                    PDM_VAD0_SCONFIG_VADSFILEN_MASK;
    base->VAD0_SCONFIG = signalConfig;
}

/*!
 * brief Configure voice activity detector noise filter.
 *
 * param base PDM base pointer
 * param config Voice activity detector noise filter configure structure pointer .
 */
void PDM_SetHwvadNoiseFilterConfig(PDM_Type *base, const pdm_hwvad_noise_filter_t *config)
{
    assert(config != NULL);

    base->VAD0_NCONFIG =
        (PDM_VAD0_NCONFIG_VADNFILAUTO(config->enableAutoNoiseFilter) |
         PDM_VAD0_NCONFIG_VADNOREN(config->enableNoiseDetectOR) | PDM_VAD0_NCONFIG_VADNMINEN(config->enableNoiseMin) |
         PDM_VAD0_NCONFIG_VADNDECEN(config->enableNoiseDecimation) |
         PDM_VAD0_NCONFIG_VADNFILADJ(config->noiseFilterAdjustment) | PDM_VAD0_NCONFIG_VADNGAIN(config->noiseGain));
}

/*!
 * brief Configure voice activity detector zero cross detector.
 *
 * param base PDM base pointer
 * param config Voice activity detector zero cross detector configure structure pointer .
 */
void PDM_SetHwvadZeroCrossDetectorConfig(PDM_Type *base, const pdm_hwvad_zero_cross_detector_t *config)
{
    assert(config != NULL);

    uint32_t zcd = (base->VAD0_ZCD & (~(PDM_VAD0_ZCD_VADZCDTH_MASK | PDM_VAD0_ZCD_VADZCDADJ_MASK |
                                        PDM_VAD0_ZCD_VADZCDAUTO_MASK | PDM_VAD0_ZCD_VADZCDAND_MASK)));

    zcd |= (PDM_VAD0_ZCD_VADZCDTH(config->threshold) | PDM_VAD0_ZCD_VADZCDADJ(config->adjustmentThreshold) |
            PDM_VAD0_ZCD_VADZCDAUTO(config->enableAutoThreshold) | PDM_VAD0_ZCD_VADZCDAND(config->zcdAnd)) |
           PDM_VAD0_ZCD_VADZCDEN_MASK;

    base->VAD0_ZCD = zcd;
}

/*!
 * brief   Enable/Disable  hwvad callback.

 * This function enable/disable the hwvad interrupt for the selected PDM peripheral.
 *
 * param base Base address of the PDM peripheral.
 * param vadCallback callback Pointer to store callback function, should be NULL when disable.
 * param userData user data.
 * param enable true is enable, false is disable.
 * retval None.
 */
void PDM_EnableHwvadInterruptCallback(PDM_Type *base, pdm_hwvad_callback_t vadCallback, void *userData, bool enable)
{
    uint32_t instance = PDM_GetInstance(base);

    if (enable)
    {
        PDM_EnableHwvadInterrupts(base, (uint32_t)kPDM_HwvadErrorInterruptEnable | (uint32_t)kPDM_HwvadInterruptEnable);
        NVIC_ClearPendingIRQ(PDM_HWVAD_EVENT_IRQn);
        (void)EnableIRQ(PDM_HWVAD_EVENT_IRQn);
#if !(defined FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ && FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ)
        NVIC_ClearPendingIRQ(PDM_HWVAD_ERROR_IRQn);
        (void)EnableIRQ(PDM_HWVAD_ERROR_IRQn);
#endif
        s_pdm_hwvad_notification[instance].callback = vadCallback;
        s_pdm_hwvad_notification[instance].userData = userData;
    }
    else
    {
        PDM_DisableHwvadInterrupts(base,
                                   (uint32_t)kPDM_HwvadErrorInterruptEnable | (uint32_t)kPDM_HwvadInterruptEnable);
        (void)DisableIRQ(PDM_HWVAD_EVENT_IRQn);
#if !(defined FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ && FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ)
        (void)DisableIRQ(PDM_HWVAD_ERROR_IRQn);
        NVIC_ClearPendingIRQ(PDM_HWVAD_ERROR_IRQn);
#endif
        s_pdm_hwvad_notification[instance].callback = NULL;
        s_pdm_hwvad_notification[instance].userData = NULL;
        NVIC_ClearPendingIRQ(PDM_HWVAD_EVENT_IRQn);
    }
}

#if (defined PDM)
void PDM_HWVAD_EVENT_DriverIRQHandler(void);
void PDM_HWVAD_EVENT_DriverIRQHandler(void)
{
    if ((PDM_GetHwvadInterruptStatusFlags(PDM) & (uint32_t)kPDM_HwvadStatusVoiceDetectFlag) != 0U)
    {
        PDM_ClearHwvadInterruptStatusFlags(PDM, (uint32_t)kPDM_HwvadStatusVoiceDetectFlag);
        if (s_pdm_hwvad_notification[0].callback != NULL)
        {
            s_pdm_hwvad_notification[0].callback(kStatus_PDM_HWVAD_VoiceDetected, s_pdm_hwvad_notification[0].userData);
        }
    }
#if (defined FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ && FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ)
    else
    {
        PDM_ClearHwvadInterruptStatusFlags(PDM, (uint32_t)kPDM_HwvadStatusInputSaturation);
        if (s_pdm_hwvad_notification[0].callback != NULL)
        {
            s_pdm_hwvad_notification[0].callback(kStatus_PDM_HWVAD_Error, s_pdm_hwvad_notification[0].userData);
        }
    }
#endif
    SDK_ISR_EXIT_BARRIER;
}

#if !(defined FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ && FSL_FEATURE_PDM_HAS_NO_INDEPENDENT_ERROR_IRQ)
void PDM_HWVAD_ERROR_DriverIRQHandler(void);
void PDM_HWVAD_ERROR_DriverIRQHandler(void)
{
    PDM_ClearHwvadInterruptStatusFlags(PDM, (uint32_t)kPDM_HwvadStatusInputSaturation);
    if (s_pdm_hwvad_notification[0].callback != NULL)
    {
        s_pdm_hwvad_notification[0].callback(kStatus_PDM_HWVAD_Error, s_pdm_hwvad_notification[0].userData);
    }
    SDK_ISR_EXIT_BARRIER;
}
#endif
#endif
#endif

#if defined(PDM)
void PDM_EVENT_DriverIRQHandler(void);
void PDM_EVENT_DriverIRQHandler(void)
{
    assert(s_pdmHandle[0] != NULL);
    s_pdmIsr(PDM, s_pdmHandle[0]);
    SDK_ISR_EXIT_BARRIER;
}
#endif
