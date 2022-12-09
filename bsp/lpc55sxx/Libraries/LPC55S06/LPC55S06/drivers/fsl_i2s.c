/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_i2s.h"
#include "fsl_flexcomm.h"
#include <string.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexcomm_i2s"
#endif

/* TODO - absent in device header files, should be there */
#define I2S_FIFOCFG_TXI2SE0_MASK  (0x4U)
#define I2S_FIFOCFG_TXI2SE0_SHIFT (2U)
#define I2S_FIFOCFG_TXI2SE0(x)    (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_TXI2SE0_SHIFT)) & I2S_FIFOCFG_TXI2SE0_MASK)
#define I2S_FIFOCFG_PACK48_MASK   (0x8U)
#define I2S_FIFOCFG_PACK48_SHIFT  (3U)
#define I2S_FIFOCFG_PACK48(x)     (((uint32_t)(((uint32_t)(x)) << I2S_FIFOCFG_PACK48_SHIFT)) & I2S_FIFOCFG_PACK48_MASK)
/*! @brief i2s empty tx fifo timeout value */
#define I2S_FIFO_DEPTH                   (8U)
#define I2S_TX_ONE_SAMPLE_MAX_TIMEOUT    (125U) /* 8K/8bit one sample need 125us*/
#define I2S_TX_FIFO_EMPTY_TIMEOUT(count) (count) * I2S_TX_ONE_SAMPLE_MAX_TIMEOUT
/*! @brief _i2s_state I2S states. */
enum
{
    kI2S_StateIdle = 0x0,             /*!< Not performing transfer */
    kI2S_StateTx,                     /*!< Performing transmit */
    kI2S_StateTxWaitToWriteDummyData, /*!< Wait on FIFO in order to write final dummy data there */
    kI2S_StateTxWaitForEmptyFifo,     /*!< Wait for FIFO to be flushed */
    kI2S_StateRx,                     /*!< Performing receive */
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static void I2S_Config(I2S_Type *base, const i2s_config_t *config);
static void I2S_TxEnable(I2S_Type *base, bool enable);
static void I2S_RxEnable(I2S_Type *base, bool enable);
static status_t I2S_ValidateBuffer(i2s_handle_t *handle, i2s_transfer_t *transfer);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Array to map i2c instance number to base address. */
static const uint32_t s_i2sBaseAddrs[] = I2S_BASE_ADDRS;

/*! @brief IRQ name array */
static const IRQn_Type s_i2sIRQ[] = I2S_IRQS;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Returns an instance number given a base address.
 *
 * If an invalid base address is passed, debug builds will assert. Release builds will just return
 * instance number 0.
 *
 * @param base The I2S peripheral base address.
 * @return I2S instance number starting from 0.
 */
static uint32_t I2S_GetInstance(I2S_Type *base)
{
    uint32_t i;
    for (i = 0; i < (uint32_t)ARRAY_SIZE(s_i2sBaseAddrs); i++)
    {
        if ((uint32_t)base == s_i2sBaseAddrs[i])
        {
            return i;
        }
    }
    assert(false);
    return 0;
}

/*!
 * brief Transmitter bit clock rate configurations.
 *
 * param base SAI base pointer.
 * param sourceClockHz, bit clock source frequency.
 * param sampleRate audio data sample rate.
 * param bitWidth, audio data bitWidth.
 * param channelNumbers, audio channel numbers.
 */
void I2S_SetBitClockRate(
    I2S_Type *base, uint32_t sourceClockHz, uint32_t sampleRate, uint32_t bitWidth, uint32_t channelNumbers)
{
    uint32_t bitClockDivider = sourceClockHz / sampleRate / bitWidth / channelNumbers;

    assert(bitClockDivider >= 1U);
    base->DIV = I2S_DIV_DIV(bitClockDivider - 1U);
}

/*!
 * brief Initializes the FLEXCOMM peripheral for I2S transmit functionality.
 *
 * Ungates the FLEXCOMM clock and configures the module
 * for I2S transmission using a configuration structure.
 * The configuration structure can be custom filled or set with default values by
 * I2S_TxGetDefaultConfig().
 *
 * note This API should be called at the beginning of the application to use
 * the I2S driver.
 *
 * param base I2S base pointer.
 * param config pointer to I2S configuration structure.
 */
void I2S_TxInit(I2S_Type *base, const i2s_config_t *config)
{
    uint32_t cfg  = 0U;
    uint32_t trig = 0U;

    (void)FLEXCOMM_Init(base, FLEXCOMM_PERIPH_I2S_TX);
    I2S_Config(base, config);

    /* Configure FIFO */

    cfg |= I2S_FIFOCFG_ENABLETX(1U);                 /* enable TX FIFO */
    cfg |= I2S_FIFOCFG_EMPTYTX(1U);                  /* empty TX FIFO */
    cfg |= I2S_FIFOCFG_TXI2SE0(config->txEmptyZero); /* transmit zero when buffer becomes empty or last item */
    cfg |= I2S_FIFOCFG_PACK48(config->pack48);       /* set pack 48-bit format or not */
    trig |= I2S_FIFOTRIG_TXLVLENA(1U);               /* enable TX FIFO trigger */
    trig |= I2S_FIFOTRIG_TXLVL(config->watermark);   /* set TX FIFO trigger level */

    base->FIFOCFG  = cfg;
    base->FIFOTRIG = trig;
}

/*!
 * brief Initializes the FLEXCOMM peripheral for I2S receive functionality.
 *
 * Ungates the FLEXCOMM clock and configures the module
 * for I2S receive using a configuration structure.
 * The configuration structure can be custom filled or set with default values by
 * I2S_RxGetDefaultConfig().
 *
 * note This API should be called at the beginning of the application to use
 * the I2S driver.
 *
 * param base I2S base pointer.
 * param config pointer to I2S configuration structure.
 */
void I2S_RxInit(I2S_Type *base, const i2s_config_t *config)
{
    uint32_t cfg  = 0U;
    uint32_t trig = 0U;

    (void)FLEXCOMM_Init(base, FLEXCOMM_PERIPH_I2S_RX);
    I2S_Config(base, config);

    /* Configure FIFO */

    cfg |= I2S_FIFOCFG_ENABLERX(1U);               /* enable RX FIFO */
    cfg |= I2S_FIFOCFG_EMPTYRX(1U);                /* empty RX FIFO */
    cfg |= I2S_FIFOCFG_PACK48(config->pack48);     /* set pack 48-bit format or not */
    trig |= I2S_FIFOTRIG_RXLVLENA(1U);             /* enable RX FIFO trigger */
    trig |= I2S_FIFOTRIG_RXLVL(config->watermark); /* set RX FIFO trigger level */

    base->FIFOCFG  = cfg;
    base->FIFOTRIG = trig;
}

/*!
 * brief Flush the valid data in TX fifo.
 *
 * param base I2S base pointer.
 * return kStatus_Fail empty TX fifo failed, kStatus_Success empty tx fifo success.
 */
status_t I2S_EmptyTxFifo(I2S_Type *base)
{
    uint32_t timeout = I2S_TX_FIFO_EMPTY_TIMEOUT(I2S_FIFO_DEPTH);

    while (((base->FIFOSTAT & I2S_FIFOSTAT_TXEMPTY_MASK) == 0U) && (timeout != 0U))
    {
        timeout -= I2S_TX_ONE_SAMPLE_MAX_TIMEOUT;
        SDK_DelayAtLeastUs(I2S_TX_ONE_SAMPLE_MAX_TIMEOUT, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }

    /* The last piece of valid data can be still being transmitted from I2S at this moment */
    timeout = I2S_TX_ONE_SAMPLE_MAX_TIMEOUT;
    /* Write additional data to FIFO */
    base->FIFOWR = 0U;
    while (((base->FIFOSTAT & I2S_FIFOSTAT_TXEMPTY_MASK) == 0U) && (timeout != 0U))
    {
        timeout -= I2S_TX_ONE_SAMPLE_MAX_TIMEOUT;
        SDK_DelayAtLeastUs(I2S_TX_ONE_SAMPLE_MAX_TIMEOUT, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }

    return ((base->FIFOSTAT & I2S_FIFOSTAT_TXEMPTY_MASK) == 0U) ? kStatus_Fail : kStatus_Success;
}

/*!
 * brief Sets the I2S Tx configuration structure to default values.
 *
 * This API initializes the configuration structure for use in I2S_TxInit().
 * The initialized structure can remain unchanged in I2S_TxInit(), or it can be modified
 * before calling I2S_TxInit().
 * Example:
   code
   i2s_config_t config;
   I2S_TxGetDefaultConfig(&config);
   endcode
 *
 * Default values:
 * code
 *   config->masterSlave = kI2S_MasterSlaveNormalMaster;
 *   config->mode = kI2S_ModeI2sClassic;
 *   config->rightLow = false;
 *   config->leftJust = false;
 *   config->pdmData = false;
 *   config->sckPol = false;
 *   config->wsPol = false;
 *   config->divider = 1;
 *   config->oneChannel = false;
 *   config->dataLength = 16;
 *   config->frameLength = 32;
 *   config->position = 0;
 *   config->watermark = 4;
 *   config->txEmptyZero = true;
 *   config->pack48 = false;
 * endcode
 *
 * param config pointer to I2S configuration structure.
 */
void I2S_TxGetDefaultConfig(i2s_config_t *config)
{
    config->masterSlave = kI2S_MasterSlaveNormalMaster;
    config->mode        = kI2S_ModeI2sClassic;
    config->rightLow    = false;
    config->leftJust    = false;
#if (defined(FSL_FEATURE_FLEXCOMM_I2S_HAS_DMIC_INTERCONNECTION) && FSL_FEATURE_FLEXCOMM_I2S_HAS_DMIC_INTERCONNECTION)
    config->pdmData = false;
#endif
    config->sckPol      = false;
    config->wsPol       = false;
    config->divider     = 1U;
    config->oneChannel  = false;
    config->dataLength  = 16U;
    config->frameLength = 32U;
    config->position    = 0U;
    config->watermark   = 4U;
    config->txEmptyZero = true;
    config->pack48      = false;
}

/*!
 * brief Sets the I2S Rx configuration structure to default values.
 *
 * This API initializes the configuration structure for use in I2S_RxInit().
 * The initialized structure can remain unchanged in I2S_RxInit(), or it can be modified
 * before calling I2S_RxInit().
 * Example:
   code
   i2s_config_t config;
   I2S_RxGetDefaultConfig(&config);
   endcode
 *
 * Default values:
 * code
 *   config->masterSlave = kI2S_MasterSlaveNormalSlave;
 *   config->mode = kI2S_ModeI2sClassic;
 *   config->rightLow = false;
 *   config->leftJust = false;
 *   config->pdmData = false;
 *   config->sckPol = false;
 *   config->wsPol = false;
 *   config->divider = 1;
 *   config->oneChannel = false;
 *   config->dataLength = 16;
 *   config->frameLength = 32;
 *   config->position = 0;
 *   config->watermark = 4;
 *   config->txEmptyZero = false;
 *   config->pack48 = false;
 * endcode
 *
 * param config pointer to I2S configuration structure.
 */
void I2S_RxGetDefaultConfig(i2s_config_t *config)
{
    config->masterSlave = kI2S_MasterSlaveNormalSlave;
    config->mode        = kI2S_ModeI2sClassic;
    config->rightLow    = false;
    config->leftJust    = false;
#if (defined(FSL_FEATURE_FLEXCOMM_I2S_HAS_DMIC_INTERCONNECTION) && FSL_FEATURE_FLEXCOMM_I2S_HAS_DMIC_INTERCONNECTION)
    config->pdmData = false;
#endif
    config->sckPol      = false;
    config->wsPol       = false;
    config->divider     = 1U;
    config->oneChannel  = false;
    config->dataLength  = 16U;
    config->frameLength = 32U;
    config->position    = 0U;
    config->watermark   = 4U;
    config->txEmptyZero = false;
    config->pack48      = false;
}

static void I2S_Config(I2S_Type *base, const i2s_config_t *config)
{
    assert(config != NULL);

    uint32_t cfg1 = 0U;
    uint32_t cfg2 = 0U;

    /* set master/slave configuration */
    cfg1 |= I2S_CFG1_MSTSLVCFG(config->masterSlave);

    /* set I2S mode */
    cfg1 |= I2S_CFG1_MODE(config->mode);

    /* set right low (channel swap) */
    cfg1 |= I2S_CFG1_RIGHTLOW(config->rightLow);

    /* set data justification */
    cfg1 |= I2S_CFG1_LEFTJUST(config->leftJust);

#if (defined(FSL_FEATURE_FLEXCOMM_I2S_HAS_DMIC_INTERCONNECTION) && FSL_FEATURE_FLEXCOMM_I2S_HAS_DMIC_INTERCONNECTION)
    if (FSL_FEATURE_FLEXCOMM_INSTANCE_I2S_HAS_DMIC_INTERCONNECTIONn((FLEXCOMM_Type *)(uint32_t)base) > 0)
    {
        /* set source to PDM dmic */
        cfg1 |= I2S_CFG1_PDMDATA(config->pdmData);
    }
#endif

    /* set SCLK polarity */
    cfg1 |= I2S_CFG1_SCK_POL(config->sckPol);

    /* set WS polarity */
    cfg1 |= I2S_CFG1_WS_POL(config->wsPol);

    /* set mono mode */
    cfg1 |= I2S_CFG1_ONECHANNEL(config->oneChannel);

    /* set data length */
    cfg1 |= I2S_CFG1_DATALEN(config->dataLength - 1UL);

    /* set frame length */
    cfg2 |= I2S_CFG2_FRAMELEN(config->frameLength - 1UL);

    /* set data position of this channel pair within the frame */
    cfg2 |= I2S_CFG2_POSITION(config->position);

    /* write to registers */
    base->CFG1 = cfg1;
    base->CFG2 = cfg2;

    /* set the clock divider */
    base->DIV = I2S_DIV_DIV(config->divider - 1UL);
}

/*!
 * brief De-initializes the I2S peripheral.
 *
 * This API gates the FLEXCOMM clock. The I2S module can't operate unless I2S_TxInit
 * or I2S_RxInit is called to enable the clock.
 *
 * param base I2S base pointer.
 */
void I2S_Deinit(I2S_Type *base)
{
    /* TODO gate FLEXCOMM clock via FLEXCOMM driver */
}

static void I2S_TxEnable(I2S_Type *base, bool enable)
{
    if (enable)
    {
        I2S_Enable(base);
        I2S_EnableInterrupts(base, (uint32_t)kI2S_TxErrorFlag | (uint32_t)kI2S_TxLevelFlag);
    }
    else
    {
        I2S_DisableInterrupts(base, (uint32_t)kI2S_TxErrorFlag | (uint32_t)kI2S_TxLevelFlag);
        I2S_Disable(base);
        base->FIFOCFG |= I2S_FIFOCFG_EMPTYTX_MASK;
    }
}

static void I2S_RxEnable(I2S_Type *base, bool enable)
{
    if (enable)
    {
        I2S_Enable(base);
        I2S_EnableInterrupts(base, (uint32_t)kI2S_RxErrorFlag | (uint32_t)kI2S_RxLevelFlag);
    }
    else
    {
        I2S_DisableInterrupts(base, (uint32_t)kI2S_RxErrorFlag | (uint32_t)kI2S_RxLevelFlag);
        I2S_Disable(base);
        base->FIFOCFG |= I2S_FIFOCFG_EMPTYRX_MASK;
    }
}

static status_t I2S_ValidateBuffer(i2s_handle_t *handle, i2s_transfer_t *transfer)
{
    assert(transfer->data != NULL);

    if (transfer->data == NULL)
    {
        return kStatus_InvalidArgument;
    }

    assert(transfer->dataSize > 0U);
    if (transfer->dataSize <= 0U)
    {
        return kStatus_InvalidArgument;
    }

    if (handle->dataLength == 4U)
    {
        /* No alignment and data length requirements */
    }
    else if ((handle->dataLength >= 5U) && (handle->dataLength <= 8U))
    {
        assert((((uint32_t)transfer->data) % 2U) == 0U);
        if ((((uint32_t)transfer->data) % 2U) != 0U)
        {
            /* Data not 2-bytes aligned */
            return kStatus_InvalidArgument;
        }

        assert((transfer->dataSize % 2U) == 0U);
        if ((transfer->dataSize % 2U) != 0U)
        {
            /* Data not in pairs of left/right channel bytes */
            return kStatus_InvalidArgument;
        }
    }
    else if ((handle->dataLength >= 9U) && (handle->dataLength <= 16U))
    {
        assert((((uint32_t)transfer->data) % 4U) == 0U);
        if ((((uint32_t)transfer->data) % 4U) != 0U)
        {
            /* Data not 4-bytes aligned */
            return kStatus_InvalidArgument;
        }

        assert((transfer->dataSize % 4U) == 0U);
        if ((transfer->dataSize % 4U) != 0U)
        {
            /* Data lenght not multiply of 4 */
            return kStatus_InvalidArgument;
        }
    }
    else if ((handle->dataLength >= 17U) && (handle->dataLength <= 24U))
    {
        assert((transfer->dataSize % 6U) == 0U);
        if ((transfer->dataSize % 6U) != 0U)
        {
            /* Data lenght not multiply of 6 */
            return kStatus_InvalidArgument;
        }

        assert(!((handle->pack48) && ((((uint32_t)transfer->data) % 4U) != 0U)));
        if ((handle->pack48) && ((((uint32_t)transfer->data) % 4U) != 0U))
        {
            /* Data not 4-bytes aligned */
            return kStatus_InvalidArgument;
        }
    }
    else /* if (handle->dataLength >= 25U) */
    {
        assert((((uint32_t)transfer->data) % 4U) == 0U);
        if ((((uint32_t)transfer->data) % 4U) != 0U)
        {
            /* Data not 4-bytes aligned */
            return kStatus_InvalidArgument;
        }

        if (handle->oneChannel)
        {
            assert((transfer->dataSize % 4U) == 0U);
            if ((transfer->dataSize % 4U) != 0U)
            {
                /* Data lenght not multiply of 4 */
                return kStatus_InvalidArgument;
            }
        }
        else
        {
            assert((transfer->dataSize % 8U) == 0U);
            if ((transfer->dataSize % 8U) != 0U)
            {
                /* Data lenght not multiply of 8 */
                return kStatus_InvalidArgument;
            }
        }
    }

    return kStatus_Success;
}

#if (defined(FSL_FEATURE_I2S_SUPPORT_SECONDARY_CHANNEL) && FSL_FEATURE_I2S_SUPPORT_SECONDARY_CHANNEL)
/*!
 * brief Enables I2S secondary channel.
 *
 * param base I2S      base pointer.
 * param channel       seondary channel channel number, reference _i2s_secondary_channel.
 * param oneChannel    true is treated as single channel, functionality left channel for this pair.
 * param position      define the location within the frame of the data, should not bigger than 0x1FFU.
 */
void I2S_EnableSecondaryChannel(I2S_Type *base, uint32_t channel, bool oneChannel, uint32_t position)
{
    assert(channel <= (uint32_t)kI2S_SecondaryChannel3);
#if defined FSL_FEATURE_FLEXCOMM_INSTANCE_I2S_SUPPORT_SECONDARY_CHANNELn
    assert(FSL_FEATURE_FLEXCOMM_INSTANCE_I2S_SUPPORT_SECONDARY_CHANNELn((FLEXCOMM_Type *)(uint32_t)base) == 1);
#endif

    uint32_t pcfg1 = base->SECCHANNEL[channel].PCFG1;
    uint32_t pcfg2 = base->SECCHANNEL[channel].PCFG2;

    pcfg1 &= ~I2S_CFG1_ONECHANNEL_MASK;
    pcfg1 |= I2S_CFG1_MAINENABLE_MASK | I2S_CFG1_ONECHANNEL(oneChannel);

    pcfg2 &= ~I2S_CFG2_POSITION_MASK;
    pcfg2 |= I2S_CFG2_POSITION(position);

    base->SECCHANNEL[channel].PCFG1 = pcfg1;
    base->SECCHANNEL[channel].PCFG2 = pcfg2;
}
#endif

/*!
 * brief Initializes handle for transfer of audio data.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 * param callback function to be called back when transfer is done or fails.
 * param userData pointer to data passed to callback.
 */
void I2S_TxTransferCreateHandle(I2S_Type *base, i2s_handle_t *handle, i2s_transfer_callback_t callback, void *userData)
{
    assert(handle != NULL);

    uint32_t instance;

    /* Clear out the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Look up instance number */
    instance = I2S_GetInstance(base);

    /* Save callback and user data */
    handle->completionCallback = callback;
    handle->userData           = userData;

    /* Remember some items set previously by configuration */
    handle->watermark  = (uint8_t)((base->FIFOTRIG & I2S_FIFOTRIG_TXLVL_MASK) >> I2S_FIFOTRIG_TXLVL_SHIFT);
    handle->oneChannel = ((base->CFG1 & I2S_CFG1_ONECHANNEL_MASK) >> I2S_CFG1_ONECHANNEL_SHIFT) != 0U ? true : false;
    handle->dataLength = (uint8_t)((base->CFG1 & I2S_CFG1_DATALEN_MASK) >> I2S_CFG1_DATALEN_SHIFT) + 1U;
    handle->pack48     = ((base->FIFOCFG & I2S_FIFOCFG_PACK48_MASK) >> I2S_FIFOCFG_PACK48_SHIFT) != 0u ? true : false;

    handle->useFifo48H = false;

    /* Register IRQ handling */
    FLEXCOMM_SetIRQHandler(base, (flexcomm_irq_handler_t)I2S_TxHandleIRQ, handle);
    /* Clear internal IRQ enables and enable NVIC IRQ. */
    I2S_DisableInterrupts(base, (uint32_t)kI2S_TxErrorFlag | (uint32_t)kI2S_TxLevelFlag);
    (void)EnableIRQ(s_i2sIRQ[instance]);
}

/*!
 * brief Begins or queue sending of the given data.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 * param transfer data buffer.
 *
 * retval kStatus_Success
 * retval kStatus_I2S_Busy if all queue slots are occupied with unsent buffers.
 */
status_t I2S_TxTransferNonBlocking(I2S_Type *base, i2s_handle_t *handle, i2s_transfer_t transfer)
{
    assert(handle != NULL);

    status_t result;

    if (handle == NULL)
    {
        return kStatus_InvalidArgument;
    }

    result = I2S_ValidateBuffer(handle, &transfer);
    if (result != kStatus_Success)
    {
        return result;
    }

    if (handle->i2sQueue[handle->queueUser].dataSize != 0UL)
    {
        /* Previously prepared buffers not processed yet */
        return kStatus_I2S_Busy;
    }

    handle->i2sQueue[handle->queueUser].data     = transfer.data;
    handle->i2sQueue[handle->queueUser].dataSize = transfer.dataSize;
    handle->queueUser                            = (handle->queueUser + 1U) % I2S_NUM_BUFFERS;

    base->FIFOTRIG = (base->FIFOTRIG & (~I2S_FIFOTRIG_TXLVL_MASK)) | I2S_FIFOTRIG_TXLVL(handle->watermark);
    I2S_TxEnable(base, true);

    return kStatus_Success;
}

/*!
 * brief Aborts sending of data.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 */
void I2S_TxTransferAbort(I2S_Type *base, i2s_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable I2S operation and interrupts */
    I2S_TxEnable(base, false);

    /* Reset state */
    handle->state = (uint32_t)kI2S_StateIdle;

    /* Clear transfer queue */
    (void)memset((void *)&handle->i2sQueue, 0, sizeof(i2s_transfer_t) * I2S_NUM_BUFFERS);
    handle->queueDriver = 0U;
    handle->queueUser   = 0U;
}

/*!
 * brief Initializes handle for reception of audio data.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 * param callback function to be called back when transfer is done or fails.
 * param userData pointer to data passed to callback.
 */
void I2S_RxTransferCreateHandle(I2S_Type *base, i2s_handle_t *handle, i2s_transfer_callback_t callback, void *userData)
{
    assert(handle != NULL);

    uint32_t instance;

    /* Clear out the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Look up instance number */
    instance = I2S_GetInstance(base);

    /* Save callback and user data */
    handle->completionCallback = callback;
    handle->userData           = userData;

    /* Remember some items set previously by configuration */
    handle->watermark  = (uint8_t)((base->FIFOTRIG & I2S_FIFOTRIG_RXLVL_MASK) >> I2S_FIFOTRIG_RXLVL_SHIFT);
    handle->oneChannel = ((base->CFG1 & I2S_CFG1_ONECHANNEL_MASK) >> I2S_CFG1_ONECHANNEL_SHIFT) != 0UL ? true : false;
    handle->dataLength = (uint8_t)((base->CFG1 & I2S_CFG1_DATALEN_MASK) >> I2S_CFG1_DATALEN_SHIFT) + 1U;
    handle->pack48     = ((base->FIFOCFG & I2S_FIFOCFG_PACK48_MASK) >> I2S_FIFOCFG_PACK48_SHIFT) != 0UL ? true : false;

    handle->useFifo48H = false;

    /* Register IRQ handling */
    FLEXCOMM_SetIRQHandler(base, (flexcomm_irq_handler_t)I2S_RxHandleIRQ, handle);
    /* Clear internal IRQ enables and enable NVIC IRQ. */
    I2S_DisableInterrupts(base, (uint32_t)kI2S_RxErrorFlag | (uint32_t)kI2S_RxLevelFlag);

    (void)EnableIRQ(s_i2sIRQ[instance]);
}

/*!
 * brief Begins or queue reception of data into given buffer.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 * param transfer data buffer.
 *
 * retval kStatus_Success
 * retval kStatus_I2S_Busy if all queue slots are occupied with buffers which are not full.
 */
status_t I2S_RxTransferNonBlocking(I2S_Type *base, i2s_handle_t *handle, i2s_transfer_t transfer)
{
    assert(handle != NULL);

    status_t result;

    if (NULL == handle)
    {
        return kStatus_InvalidArgument;
    }

    result = I2S_ValidateBuffer(handle, &transfer);
    if (result != kStatus_Success)
    {
        return result;
    }

    if (handle->i2sQueue[handle->queueUser].dataSize != 0UL)
    {
        /* Previously prepared buffers not processed yet */
        return kStatus_I2S_Busy;
    }

    handle->i2sQueue[handle->queueUser].data     = transfer.data;
    handle->i2sQueue[handle->queueUser].dataSize = transfer.dataSize;
    handle->queueUser                            = (handle->queueUser + 1U) % I2S_NUM_BUFFERS;

    base->FIFOTRIG = (base->FIFOTRIG & (~I2S_FIFOTRIG_RXLVL_MASK)) | I2S_FIFOTRIG_RXLVL(handle->watermark);
    I2S_RxEnable(base, true);

    return kStatus_Success;
}

/*!
 * brief Aborts receiving of data.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 */
void I2S_RxTransferAbort(I2S_Type *base, i2s_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable I2S operation and interrupts */
    I2S_RxEnable(base, false);

    /* Reset state */
    handle->state = (uint32_t)kI2S_StateIdle;

    /* Clear transfer queue */
    (void)memset((void *)&handle->i2sQueue, 0, sizeof(i2s_transfer_t) * I2S_NUM_BUFFERS);
    handle->queueDriver = 0U;
    handle->queueUser   = 0U;
}

/*!
 * brief Returns number of bytes transferred so far.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 * param[out] count number of bytes transferred so far by the non-blocking transaction.
 *
 * retval kStatus_Success
 * retval kStatus_NoTransferInProgress there is no non-blocking transaction currently in progress.
 */
status_t I2S_TransferGetCount(I2S_Type *base, i2s_handle_t *handle, size_t *count)
{
    assert(handle != NULL);
    assert(count != NULL);

    if (NULL == handle)
    {
        return kStatus_InvalidArgument;
    }

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    if (handle->state == (uint32_t)kI2S_StateIdle)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->transferCount;

    return kStatus_Success;
}

/*!
 * brief Returns number of buffer underruns or overruns.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 * param[out] count number of transmit errors encountered so far by the non-blocking transaction.
 *
 * retval kStatus_Success
 * retval kStatus_NoTransferInProgress there is no non-blocking transaction currently in progress.
 */
status_t I2S_TransferGetErrorCount(I2S_Type *base, i2s_handle_t *handle, size_t *count)
{
    assert(handle != NULL);
    assert(count != NULL);

    if (NULL == handle)
    {
        return kStatus_InvalidArgument;
    }

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    if (handle->state == (uint32_t)kI2S_StateIdle)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->errorCount;

    return kStatus_Success;
}

/*!
 * brief Invoked from interrupt handler when transmit FIFO level decreases.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 */
void I2S_TxHandleIRQ(I2S_Type *base, i2s_handle_t *handle)
{
    uint32_t intstat = base->FIFOINTSTAT;
    uint32_t data;
    uint8_t queueDriverIndex = handle->queueDriver;
    uint32_t dataAddr        = (uint32_t)handle->i2sQueue[queueDriverIndex].data;
    uint32_t dataSize        = handle->i2sQueue[queueDriverIndex].dataSize;

    if ((intstat & I2S_FIFOINTSTAT_TXERR_MASK) != 0UL)
    {
        handle->errorCount++;

        /* Clear TX error interrupt flag */
        base->FIFOSTAT = I2S_FIFOSTAT_TXERR(1U);
    }

    if ((intstat & I2S_FIFOINTSTAT_TXLVL_MASK) != 0UL)
    {
        if ((handle->state != (uint32_t)kI2S_StateTx) && (dataSize != 0U) && (dataAddr != 0U))
        {
            handle->state = (uint32_t)kI2S_StateTx;
        }

        if (handle->state == (uint32_t)kI2S_StateTx)
        {
            /* Send data */

            while (((base->FIFOSTAT & I2S_FIFOSTAT_TXNOTFULL_MASK) != 0UL) && (dataSize > 0U))
            {
                /* Write output data */
                if (handle->dataLength == 4U)
                {
                    data         = *((uint8_t *)dataAddr);
                    base->FIFOWR = ((data & 0xF0U) << 12U) | (data & 0xFU);
                    dataAddr++;
                    handle->transferCount++;
                    dataSize--;
                }
                else if (handle->dataLength <= 8U)
                {
                    data = *((volatile uint16_t *)dataAddr);
                    if (handle->oneChannel)
                    {
                        base->FIFOWR = (data & 0xFFU);
                        dataAddr += sizeof(uint8_t);
                        handle->transferCount += sizeof(uint8_t);
                        dataSize -= sizeof(uint8_t);
                    }
                    else
                    {
                        base->FIFOWR = ((data & 0xFF00U) << 8U) | (data & 0xFFU);
                        dataAddr += sizeof(uint16_t);
                        handle->transferCount += sizeof(uint16_t);
                        dataSize -= sizeof(uint16_t);
                    }
                }
                else if (handle->dataLength <= 16U)
                {
                    data = *((volatile uint32_t *)(dataAddr));
                    if (handle->oneChannel)
                    {
                        base->FIFOWR = data & 0xFFFFU;
                        dataAddr += sizeof(uint16_t);
                        handle->transferCount += sizeof(uint16_t);
                        dataSize -= sizeof(uint16_t);
                    }
                    else
                    {
                        base->FIFOWR = data;
                        dataAddr += sizeof(uint32_t);
                        handle->transferCount += sizeof(uint32_t);
                        dataSize -= sizeof(uint32_t);
                    }
                }
                else if (handle->dataLength <= 24U)
                {
                    if (handle->pack48)
                    {
                        if (handle->useFifo48H)
                        {
                            base->FIFOWR48H = *((volatile uint16_t *)(dataAddr));
                            dataAddr += sizeof(uint16_t);
                            handle->transferCount += sizeof(uint16_t);
                            dataSize -= sizeof(uint16_t);
                            handle->useFifo48H = false;
                        }
                        else
                        {
                            base->FIFOWR = *((volatile uint32_t *)(dataAddr));
                            dataAddr += sizeof(uint32_t);
                            handle->transferCount += sizeof(uint32_t);
                            dataSize -= sizeof(uint32_t);
                            handle->useFifo48H = true;
                        }
                    }
                    else
                    {
                        data = (uint32_t)(*(uint8_t *)(dataAddr++));
                        data |= ((uint32_t)(*(uint8_t *)(dataAddr++))) << 8U;
                        data |= ((uint32_t)(*(uint8_t *)(dataAddr++))) << 16U;
                        if ((handle->useFifo48H) && (handle->oneChannel == false))
                        {
                            base->FIFOWR48H    = data;
                            handle->useFifo48H = false;
                        }
                        else
                        {
                            base->FIFOWR       = data;
                            handle->useFifo48H = true;
                        }
                        handle->transferCount += 3U;
                        dataSize -= 3U;
                    }
                }
                else /* if (handle->dataLength <= 32U) */
                {
                    base->FIFOWR = *((volatile uint32_t *)(dataAddr));
                    dataAddr += sizeof(uint32_t);
                    handle->transferCount += sizeof(uint32_t);
                    dataSize -= sizeof(uint32_t);
                }

                if (dataSize == 0U)
                {
                    handle->i2sQueue[queueDriverIndex].dataSize = 0U;
                    /* Actual data buffer sent out, switch to a next one */
                    handle->queueDriver = (queueDriverIndex + 1U) % I2S_NUM_BUFFERS;

                    /* Notify user */
                    if (handle->completionCallback != NULL)
                    {
                        handle->completionCallback(base, handle, kStatus_I2S_BufferComplete, handle->userData);
                    }

                    /* Check if the next buffer contains anything to send */
                    if (handle->i2sQueue[handle->queueDriver].dataSize == 0U)
                    {
                        /* Everything has been written to FIFO */
                        handle->state = kI2S_StateTxWaitToWriteDummyData;
                        break;
                    }
                }
                else
                {
                    handle->i2sQueue[queueDriverIndex].dataSize = dataSize;
                    handle->i2sQueue[queueDriverIndex].data     = (uint8_t *)dataAddr;
                }
            }
        }
        else if (handle->state == (uint32_t)kI2S_StateTxWaitToWriteDummyData)
        {
            /* Write dummy data */
            if ((handle->dataLength > 16U) && (handle->dataLength < 25U))
            {
                if (handle->useFifo48H)
                {
                    base->FIFOWR48H    = 0U;
                    handle->useFifo48H = false;
                }
                else
                {
                    base->FIFOWR    = 0U;
                    base->FIFOWR48H = 0U;
                }
            }
            else
            {
                base->FIFOWR = 0U;
            }

            /* Next time invoke this handler when FIFO becomes empty (TX level 0) */
            base->FIFOTRIG &= ~I2S_FIFOTRIG_TXLVL_MASK;
            handle->state = (uint32_t)kI2S_StateTxWaitForEmptyFifo;
        }
        else if (handle->state == (uint32_t)kI2S_StateTxWaitForEmptyFifo)
        {
            /* FIFO, including additional dummy data, has been emptied now,
             * all relevant data should have been output from peripheral */

            /* Stop transfer */
            I2S_Disable(base);
            I2S_DisableInterrupts(base, (uint32_t)kI2S_TxErrorFlag | (uint32_t)kI2S_TxLevelFlag);
            base->FIFOCFG |= I2S_FIFOCFG_EMPTYTX_MASK;

            /* Reset state */
            handle->state = (uint32_t)kI2S_StateIdle;

            /* Notify user */
            if (handle->completionCallback != NULL)
            {
                handle->completionCallback(base, handle, kStatus_I2S_Done, handle->userData);
            }
        }
        else
        {
            /* Do nothing */
        }

        /* Clear TX level interrupt flag */
        base->FIFOSTAT = I2S_FIFOSTAT_TXLVL(1U);
    }
}

/*!
 * brief Invoked from interrupt handler when receive FIFO level decreases.
 *
 * param base I2S base pointer.
 * param handle pointer to handle structure.
 */
void I2S_RxHandleIRQ(I2S_Type *base, i2s_handle_t *handle)
{
    uint32_t intstat = base->FIFOINTSTAT;
    uint32_t data;
    uint8_t queueDriverIndex = handle->queueDriver;
    uint32_t dataAddr        = (uint32_t)handle->i2sQueue[queueDriverIndex].data;
    uint32_t dataSize        = handle->i2sQueue[queueDriverIndex].dataSize;

    if ((intstat & I2S_FIFOINTSTAT_RXERR_MASK) != 0UL)
    {
        handle->errorCount++;

        /* Clear RX error interrupt flag */
        base->FIFOSTAT = I2S_FIFOSTAT_RXERR(1U);
    }

    if ((intstat & I2S_FIFOINTSTAT_RXLVL_MASK) != 0UL)
    {
        while (((base->FIFOSTAT & I2S_FIFOSTAT_RXNOTEMPTY_MASK) != 0UL) && (dataSize > 0U))
        {
            /* Read input data */
            if (handle->dataLength == 4U)
            {
                data                   = base->FIFORD;
                *((uint8_t *)dataAddr) = (uint8_t)(((data & 0x000F0000U) >> 12U) | (data & 0x0000000FU));
                dataAddr++;
                handle->transferCount++;
                dataSize--;
            }
            else if (handle->dataLength <= 8U)
            {
                data = base->FIFORD;

                if (handle->oneChannel)
                {
                    *((volatile uint8_t *)dataAddr) = (uint8_t)(data & 0xFFU);
                    dataAddr += sizeof(uint8_t);
                    handle->transferCount += sizeof(uint8_t);
                    dataSize -= sizeof(uint8_t);
                }
                else
                {
                    *((volatile uint16_t *)dataAddr) = (uint16_t)(((data >> 8U) & 0xFF00U) | (data & 0xFFU));
                    dataAddr += sizeof(uint16_t);
                    handle->transferCount += sizeof(uint16_t);
                    dataSize -= sizeof(uint16_t);
                }
            }
            else if (handle->dataLength <= 16U)
            {
                data = base->FIFORD;

                if (handle->oneChannel)
                {
                    *((volatile uint16_t *)dataAddr) = (uint16_t)(data & 0xFFFFU);
                    dataAddr += sizeof(uint16_t);
                    handle->transferCount += sizeof(uint16_t);
                    dataSize -= sizeof(uint16_t);
                }
                else
                {
                    *((volatile uint32_t *)dataAddr) = data;
                    dataAddr += sizeof(uint32_t);
                    handle->transferCount += sizeof(uint32_t);
                    dataSize -= sizeof(uint32_t);
                }
            }
            else if (handle->dataLength <= 24U)
            {
                if (handle->pack48)
                {
                    if (handle->useFifo48H)
                    {
                        data               = base->FIFORD48H;
                        handle->useFifo48H = false;

                        *((volatile uint16_t *)dataAddr) = (uint16_t)data;
                        dataAddr += sizeof(uint16_t);
                        handle->transferCount += sizeof(uint16_t);
                        dataSize -= sizeof(uint16_t);
                    }
                    else
                    {
                        data               = base->FIFORD;
                        handle->useFifo48H = true;

                        *((volatile uint32_t *)dataAddr) = data;
                        dataAddr += sizeof(uint32_t);
                        handle->transferCount += sizeof(uint32_t);
                        dataSize -= sizeof(uint32_t);
                    }
                }
                else
                {
                    if (handle->useFifo48H)
                    {
                        data               = base->FIFORD48H;
                        handle->useFifo48H = false;
                    }
                    else
                    {
                        data               = base->FIFORD;
                        handle->useFifo48H = true;
                    }

                    *(uint8_t *)(dataAddr++) = (uint8_t)(data & 0xFFU);
                    *(uint8_t *)(dataAddr++) = (uint8_t)((data >> 8U) & 0xFFU);
                    *(uint8_t *)(dataAddr++) = (uint8_t)((data >> 16U) & 0xFFU);
                    handle->transferCount += 3U;
                    dataSize -= 3U;
                }
            }
            else /* if (handle->dataLength <= 32U) */
            {
                data                             = base->FIFORD;
                *((volatile uint32_t *)dataAddr) = data;
                dataAddr += sizeof(uint32_t);
                handle->transferCount += sizeof(uint32_t);
                dataSize -= sizeof(uint32_t);
            }

            if (dataSize == 0U)
            {
                handle->i2sQueue[queueDriverIndex].dataSize = 0U;
                /* Actual data buffer filled with input data, switch to a next one */
                handle->queueDriver = (queueDriverIndex + 1U) % I2S_NUM_BUFFERS;

                /* Notify user */
                if (handle->completionCallback != NULL)
                {
                    handle->completionCallback(base, handle, kStatus_I2S_BufferComplete, handle->userData);
                }

                if (handle->i2sQueue[handle->queueDriver].dataSize == 0U)
                {
                    /* No other buffer prepared to receive data into */

                    /* Disable I2S operation and interrupts */
                    I2S_Disable(base);
                    I2S_DisableInterrupts(base, (uint32_t)kI2S_RxErrorFlag | (uint32_t)kI2S_RxLevelFlag);
                    base->FIFOCFG |= I2S_FIFOCFG_EMPTYRX_MASK;

                    /* Reset state */
                    handle->state = (uint32_t)kI2S_StateIdle;

                    /* Notify user */
                    if (handle->completionCallback != NULL)
                    {
                        handle->completionCallback(base, handle, kStatus_I2S_Done, handle->userData);
                    }

                    /* Clear RX level interrupt flag */
                    base->FIFOSTAT = I2S_FIFOSTAT_RXLVL(1U);

                    return;
                }
            }
            else
            {
                handle->i2sQueue[queueDriverIndex].dataSize = dataSize;
                handle->i2sQueue[queueDriverIndex].data     = (uint8_t *)dataAddr;
            }
        }

        /* Clear RX level interrupt flag */
        base->FIFOSTAT = I2S_FIFOSTAT_RXLVL(1U);
    }
}
