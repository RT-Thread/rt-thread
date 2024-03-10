/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

#include "fsl_ecspi.h"

/*******************************************************************************
 * Definitons
 ******************************************************************************/
/*! @brief ECSPI transfer state, which is used for ECSPI transactiaonl APIs' internal state. */
enum _ecspi_transfer_states_t
{
    kECSPI_Idle = 0x0, /*!< ECSPI is idle state */
    kECSPI_Busy        /*!< ECSPI is busy tranferring data. */
};

/*! @brief Typedef for ecspi master interrupt handler. ecspi master and slave handle is the same. */
typedef void (*ecspi_isr_t)(ECSPI_Type *base, ecspi_master_handle_t *ecspiHandle);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get the instance for ECSPI module.
 *
 * @param base ECSPI base address
 */
uint32_t ECSPI_GetInstance(ECSPI_Type *base);

/*!
 * @brief Sends a buffer of data bytes in non-blocking way.
 *
 * @param base ECSPI base pointer
 * @param buffer The data bytes to send
 * @param size The number of data bytes to send
 */
static void ECSPI_WriteNonBlocking(ECSPI_Type *base, uint32_t *buffer, size_t size);

/*!
 * @brief Receive a buffer of data bytes in non-blocking way.
 *
 * @param base ECSPI base pointer
 * @param buffer The data bytes to send
 * @param size The number of data bytes to send
 */
static void ECSPI_ReadNonBlocking(ECSPI_Type *base, uint32_t *buffer, size_t size);

/*!
 * @brief Send a piece of data for ECSPI.
 *
 * This function computes the number of data to be written into D register or Tx FIFO,
 * and write the data into it. At the same time, this function updates the values in
 * master handle structure.
 *
 * @param base ECSPI base pointer
 * @param handle Pointer to ECSPI master handle structure.
 */
static void ECSPI_SendTransfer(ECSPI_Type *base, ecspi_master_handle_t *handle);

/*!
 * @brief Receive a piece of data for ECSPI master.
 *
 * This function computes the number of data to receive from D register or Rx FIFO,
 * and write the data to destination address. At the same time, this function updates
 * the values in master handle structure.
 *
 * @param base ECSPI base pointer
 * @param handle Pointer to ECSPI master handle structure.
 */
static void ECSPI_ReceiveTransfer(ECSPI_Type *base, ecspi_master_handle_t *handle);

/*!
* @brief  Sets the ECSPI channel configuration structure to default values.
*
* This function is to get the channel configuration structure initialized for use in ECSPI_SetChannelConfig().
* User may use the initialized structure unchanged in ECSPI_SetChannelConfig(), or modify
* some fields of the structure before calling ECSPI_SetChannelConfig().
*
* @param config pointer to config structure
*/
static void ECSPI_GetDefaultChannelConfig(ecspi_channel_config_t *config);

/*!
 * @brief Common IRQ handler for SPI.
 *
 * @param base SPI base pointer.
 * @param instance SPI instance number.
 */
static void ECSPI_CommonIRQHandler(ECSPI_Type *base, ecspi_master_handle_t *handle);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Base pointer array */
static ECSPI_Type *const s_ecspiBases[] = ECSPI_BASE_PTRS;
/*! @brief ECSPI internal handle pointer array */
static ecspi_master_handle_t *s_ecspiHandle[ARRAY_SIZE(s_ecspiBases)];
/*! @brief IRQ name array */
static const IRQn_Type s_ecspiIRQ[] = ECSPI_IRQS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Clock array name */
static const clock_ip_name_t s_ecspiClock[] = ECSPI_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointer to master IRQ handler for each instance. */
static ecspi_isr_t s_ecspiMasterIsr;
/*! @brief Pointer to slave IRQ handler for each instance. */
static ecspi_isr_t s_ecspiSlaveIsr;

/*******************************************************************************
 * Code
 ******************************************************************************/
uint32_t ECSPI_GetInstance(ECSPI_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_ecspiBases); instance++)
    {
        if (s_ecspiBases[instance] == base)
        {
            break;
        }
    }
    assert(instance <= ARRAY_SIZE(s_ecspiBases));
    return instance;
}

static void ECSPI_WriteNonBlocking(ECSPI_Type *base, uint32_t *buffer, size_t size)
{
    size_t i = 0U;

    for (i = 0U; i < size; i++)
    {
        if (buffer != NULL)
        {
            base->TXDATA = *buffer++;
        }
        else
        {
            ECSPI_WriteData(base, ECSPI_DUMMYDATA);
        }
    }
}

static void ECSPI_ReadNonBlocking(ECSPI_Type *base, uint32_t *buffer, size_t size)
{
    if (NULL != buffer)
    {
        while (size--)
        {
            *buffer++ = ECSPI_ReadData(base);
        }
    }
    else
    {
        while (size--)
        {
            (void)ECSPI_ReadData(base);
        }
    }
}

static void ECSPI_SendTransfer(ECSPI_Type *base, ecspi_master_handle_t *handle)
{
    assert(base);
    assert(handle);

    uint32_t dataCounts = 0U;
    /* Caculate the data size to send */
    dataCounts = (FSL_FEATURE_ECSPI_TX_FIFO_SIZEn(base) - ECSPI_GetTxFifoCount(base)) < (handle->txRemainingBytes) ?
                     (FSL_FEATURE_ECSPI_TX_FIFO_SIZEn(base) - ECSPI_GetTxFifoCount(base)) :
                     (handle->txRemainingBytes);
    while (dataCounts--)
    {
        ECSPI_WriteNonBlocking(base, handle->txData, 1);
        if (NULL != handle->txData)
        {
            handle->txData += 1U;
        }
        handle->txRemainingBytes -= 1U;
    }
}

static void ECSPI_ReceiveTransfer(ECSPI_Type *base, ecspi_master_handle_t *handle)
{
    assert(base);

    uint32_t dataCounts = 0U;
    /* Caculate the data size need to receive */
    dataCounts =
        (ECSPI_GetRxFifoCount(base) < handle->rxRemainingBytes) ? ECSPI_GetRxFifoCount(base) : handle->rxRemainingBytes;

    ECSPI_ReadNonBlocking(base, handle->rxData, dataCounts);
    if (NULL != handle->rxData)
    {
        handle->rxData += dataCounts;
    }
    handle->rxRemainingBytes -= dataCounts;
}
static void ECSPI_GetDefaultChannelConfig(ecspi_channel_config_t *config)
{
    config->channelMode = kECSPI_Slave;                              /*!< ECSPI peripheral operates in slave mode.*/
    config->clockInactiveState = kECSPI_ClockInactiveStateLow;       /*!< Clock line (SCLK) inactive state */
    config->dataLineInactiveState = kECSPI_DataLineInactiveStateLow; /*!< Data line (MOSI&MISO) inactive state */
    config->chipSlectActiveState = kECSPI_ChipSelectActiveStateLow;  /*!< Chip select(SS) line active state */
    config->waveForm = kECSPI_WaveFormSingle;                        /*!< ECSPI SS wave form */
    config->polarity = kECSPI_PolarityActiveHigh;                    /*!< Clock polarity */
    config->phase = kECSPI_ClockPhaseFirstEdge;                      /*!< clock phase */
}

void ECSPI_MasterGetDefaultConfig(ecspi_master_config_t *config)
{
    config->channel = kECSPI_Channel0;
    config->burstLength = 8;
    config->samplePeriodClock = kECSPI_spiClock;
    config->baudRate_Bps = 500000;
    config->chipSelectDelay = 0;
    config->samplePeriod = 0;
    config->txFifoThreshold = 1;
    config->rxFifoThreshold = 0;
    /* Default configuration of channel */
    ECSPI_GetDefaultChannelConfig(&config->channelConfig);
    /*!< ECSPI peripheral operates in slave mode.*/
    config->channelConfig.channelMode = kECSPI_Master;
}

void ECSPI_MasterInit(ECSPI_Type *base, const ecspi_master_config_t *config, uint32_t srcClock_Hz)
{
    assert(config && srcClock_Hz);
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Open clock gate for SPI and open interrupt */
    CLOCK_EnableClock(s_ecspiClock[ECSPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
    /* Reset control register to default value */
    ECSPI_SoftwareReset(base);
    /* Config CONREG register */
    base->CONREG = ECSPI_CONREG_BURST_LENGTH(config->burstLength - 1) | ECSPI_CONREG_SMC(1) | ECSPI_CONREG_EN(1);
    /* Config CONFIGREG register */
    ECSPI_SetChannelConfig(base, config->channel, &config->channelConfig);
    /* Config DMAREG register */
    base->DMAREG |=
        ECSPI_DMAREG_TX_THRESHOLD(config->txFifoThreshold) | ECSPI_DMAREG_RX_THRESHOLD(config->rxFifoThreshold);
    /* Config PERIODREG register */
    base->PERIODREG |= ECSPI_PERIODREG_CSRC(config->samplePeriodClock) |
                       ECSPI_PERIODREG_SAMPLE_PERIOD(config->samplePeriod) |
                       ECSPI_PERIODREG_CSD_CTL(config->chipSelectDelay);
    /* Set baud rate */
    ECSPI_SetBaudRate(base, config->baudRate_Bps, srcClock_Hz);
}

void ECSPI_SlaveGetDefaultConfig(ecspi_slave_config_t *config)
{
    /* Default configuration of channel nember */
    config->channel = kECSPI_Channel0;
    config->burstLength = 8;
    config->txFifoThreshold = 1;
    config->rxFifoThreshold = 0;
    /* Set default channel configuration */
    ECSPI_GetDefaultChannelConfig(&config->channelConfig);
    /* ECSPI peripheral operates in slave mode.*/
    config->channelConfig.channelMode = kECSPI_Slave;
}

void ECSPI_SlaveInit(ECSPI_Type *base, const ecspi_slave_config_t *config)
{
    assert(base && config);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Open clock gate for SPI and open interrupt */
    CLOCK_EnableClock(s_ecspiClock[ECSPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Reset control register to default value */
    ECSPI_SoftwareReset(base);
    /* Config CONREG register */
    base->CONREG = ECSPI_CONREG_BURST_LENGTH(config->burstLength - 1) | ECSPI_CONREG_EN(1);
    /* Config DMAREG register */
    base->DMAREG |=
        ECSPI_DMAREG_TX_THRESHOLD(config->txFifoThreshold) | ECSPI_DMAREG_RX_THRESHOLD(config->rxFifoThreshold);
    /* Setup channel configuration */
    ECSPI_SetChannelConfig(base, config->channel, &config->channelConfig);
}

void ECSPI_Deinit(ECSPI_Type *base)
{
    /* Disable ECSPI module before shutting down */
    base->CONREG &= ~ECSPI_CONREG_EN_MASK;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the clock */
    CLOCK_DisableClock(s_ecspiClock[ECSPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void ECSPI_SetBaudRate(ECSPI_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz)
{
    assert(base);

    uint8_t bestPreDividerValue = 0U, preDividerValue = 0U;
    uint8_t bestPostDividerValue = 0U, postDividerValue = 0U;
    uint32_t realBaudrate = 0U;
    uint32_t diff = 0xFFFFFFFFU;
    uint32_t min_diff = 0xFFFFFFFFU;

    for (preDividerValue = 0; (preDividerValue < 16) && diff; preDividerValue++)
    {
        for (postDividerValue = 0; (postDividerValue < 16) && diff; postDividerValue++)
        {
            realBaudrate = (srcClock_Hz / (preDividerValue + 1)) >> postDividerValue;
            if (realBaudrate > baudRate_Bps)
            {
                diff = realBaudrate - baudRate_Bps;
                if (diff < min_diff)
                {
                    min_diff = diff;
                    bestPreDividerValue = preDividerValue;
                    bestPostDividerValue = postDividerValue;
                }
            }
            else
            {
                diff = baudRate_Bps - realBaudrate;
                if (diff < min_diff)
                {
                    min_diff = diff;
                    bestPreDividerValue = preDividerValue;
                    bestPostDividerValue = postDividerValue;
                }
            }
        }
    }

    base->CONREG |= ECSPI_CONREG_PRE_DIVIDER(bestPreDividerValue) | ECSPI_CONREG_POST_DIVIDER(bestPostDividerValue);
}

void ECSPI_SetChannelConfig(ECSPI_Type *base, ecspi_channel_source_t channel, const ecspi_channel_config_t *config)
{
    switch (channel)
    {
        case kECSPI_Channel0:
            base->CONREG |= ECSPI_CONREG_CHANNEL_MODE(config->channelMode);
            base->CONFIGREG |=
                (ECSPI_CONFIGREG_SCLK_CTL(config->clockInactiveState) |
                 ECSPI_CONFIGREG_DATA_CTL(config->dataLineInactiveState) |
                 ECSPI_CONFIGREG_SS_POL(config->chipSlectActiveState) | ECSPI_CONFIGREG_SS_CTL(config->waveForm) |
                 ECSPI_CONFIGREG_SCLK_POL(config->polarity) | ECSPI_CONFIGREG_SCLK_PHA(config->phase));
            break;

        case kECSPI_Channel1:
            base->CONREG |= ECSPI_CONREG_CHANNEL_MODE(config->channelMode) << 1;
            base->CONFIGREG |=
                ((ECSPI_CONFIGREG_SCLK_CTL(config->clockInactiveState) << 1) |
                 (ECSPI_CONFIGREG_DATA_CTL(config->dataLineInactiveState) << 1) |
                 (ECSPI_CONFIGREG_SS_POL(config->chipSlectActiveState) << 1) |
                 (ECSPI_CONFIGREG_SS_CTL(config->waveForm) << 1) | (ECSPI_CONFIGREG_SCLK_POL(config->polarity) << 1) |
                 (ECSPI_CONFIGREG_SCLK_PHA(config->phase) << 1));
            break;

        case kECSPI_Channel2:
            base->CONREG |= ECSPI_CONREG_CHANNEL_MODE(config->channelMode) << 2;
            base->CONFIGREG |=
                ((ECSPI_CONFIGREG_SCLK_CTL(config->clockInactiveState) << 2) |
                 (ECSPI_CONFIGREG_DATA_CTL(config->dataLineInactiveState) << 2) |
                 (ECSPI_CONFIGREG_SS_POL(config->chipSlectActiveState) << 2) |
                 (ECSPI_CONFIGREG_SS_CTL(config->waveForm) << 2) | (ECSPI_CONFIGREG_SCLK_POL(config->polarity) << 2) |
                 (ECSPI_CONFIGREG_SCLK_PHA(config->phase) << 2));
            break;

        case kECSPI_Channel3:
            base->CONREG |= ECSPI_CONREG_CHANNEL_MODE(config->channelMode) << 3;
            base->CONFIGREG |=
                ((ECSPI_CONFIGREG_SCLK_CTL(config->clockInactiveState) << 3) |
                 (ECSPI_CONFIGREG_DATA_CTL(config->dataLineInactiveState) << 3) |
                 (ECSPI_CONFIGREG_SS_POL(config->chipSlectActiveState) << 3) |
                 (ECSPI_CONFIGREG_SS_CTL(config->waveForm) << 3) | (ECSPI_CONFIGREG_SCLK_POL(config->polarity) << 3) |
                 (ECSPI_CONFIGREG_SCLK_PHA(config->phase) << 3));
            break;

        default:
            break;
    }
}

void ECSPI_WriteBlocking(ECSPI_Type *base, uint32_t *buffer, size_t size)
{
    size_t i = 0U;

    while (i < size)
    {
        /* Wait for TX fifo buffer empty */
        while (!(base->STATREG & ECSPI_STATREG_TE_MASK))
        {
        }
        /* Write data to tx register */
        if (NULL != buffer)
        {
            ECSPI_WriteData(base, *buffer++);
        }
        else
        {
            ECSPI_WriteData(base, ECSPI_DUMMYDATA);
        }
        i++;
    }
}

static status_t ECSPI_ReadBlocking(ECSPI_Type *base, uint32_t *buffer, size_t size)
{
    assert(base);

    uint32_t state = 0U;
    size_t i = 0U;

    while (i < size)
    {
        /* Wait for RX FIFO buffer ready */
        while (!(base->STATREG & ECSPI_STATREG_RR_MASK))
        {
            /* Get status flags of ECSPI */
            state = ECSPI_GetStatusFlags(base);
            /* If hardware overflow happen */
            if (ECSPI_STATREG_RO_MASK & state)
            {
                /* Clear overflow flag for next transfer */
                ECSPI_ClearStatusFlags(base, kECSPI_RxFifoOverFlowFlag);
                return kStatus_ECSPI_HardwareOverFlow;
            }
        }
        /* Read data from rx register */
        if (NULL != buffer)
        {
            *buffer++ = ECSPI_ReadData(base);
        }
        else
        {
            (void)ECSPI_ReadData(base);
        }
        i++;
    }
    return kStatus_Success;
}

void ECSPI_MasterTransferCreateHandle(ECSPI_Type *base,
                                      ecspi_master_handle_t *handle,
                                      ecspi_master_callback_t callback,
                                      void *userData)
{
    assert(base);
    assert(handle);

    uint8_t instance = ECSPI_GetInstance(base);

    /* Initialize the handle */
    s_ecspiHandle[instance] = handle;
    handle->callback = callback;
    handle->userData = userData;
    s_ecspiMasterIsr = ECSPI_MasterTransferHandleIRQ;

    /* Enable ECSPI NVIC */
    EnableIRQ(s_ecspiIRQ[instance]);
}

status_t ECSPI_MasterTransferBlocking(ECSPI_Type *base, ecspi_transfer_t *xfer)
{
    assert(base && xfer);

    status_t state;
    uint32_t burstLength = 0U;
    uint32_t dataCounts = 0U;
    /* Check if the argument is legal */
    if ((xfer->txData == NULL) && (xfer->rxData == NULL))
    {
        return kStatus_InvalidArgument;
    }
    /* Select ECSPI channel to current channel
     * Note:
     *     xfer.channel must be configured before transfer, because every channel has
     *     it's own configuration,if don't configure this parameter, transfer channel
     *     will use the default channel0.
     */
    ECSPI_SetChannelSelect(base, xfer->channel);
    /* Caculate the data size need to be send for one burst */
    burstLength = ((base->CONREG & ECSPI_CONREG_BURST_LENGTH_MASK) >> ECSPI_CONREG_BURST_LENGTH_SHIFT) + 1;
    dataCounts = (burstLength % 32) ? (burstLength / 32 + 1) : (burstLength / 32);

    while (xfer->dataSize > 0)
    {
        /* ECSPI will transmit and receive at the same time, if txData is NULL,
         * instance will transmit dummy data, the dummy data can be set by user.
         * if rxData is NULL, data will be read from RX FIFO buffer, but the
         * data will be ignored by driver.
         * Note that, txData and rxData can not be both NULL.
         */
        ECSPI_WriteBlocking(base, xfer->txData, dataCounts);
        if (NULL != xfer->txData)
        {
            xfer->txData += dataCounts;
        }
        state = ECSPI_ReadBlocking(base, xfer->rxData, dataCounts);
        if ((kStatus_Success == state) && (NULL != xfer->rxData))
        {
            xfer->rxData += dataCounts;
        }
        if (kStatus_ECSPI_HardwareOverFlow == state)
        {
            return kStatus_ECSPI_HardwareOverFlow;
        }

        xfer->dataSize -= dataCounts;
    }

    return kStatus_Success;
}

status_t ECSPI_MasterTransferNonBlocking(ECSPI_Type *base, ecspi_master_handle_t *handle, ecspi_transfer_t *xfer)
{
    assert(base && handle && xfer);

    /* Check if ECSPI is busy */
    if (handle->state == kECSPI_Busy)
    {
        return kStatus_ECSPI_Busy;
    }

    /* Check if the input arguments valid */
    if (((xfer->txData == NULL) && (xfer->rxData == NULL)) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }

    /* Set the handle information */
    handle->channel = xfer->channel;
    handle->txData = xfer->txData;
    handle->rxData = xfer->rxData;
    handle->transferSize = xfer->dataSize;
    handle->txRemainingBytes = xfer->dataSize;
    handle->rxRemainingBytes = xfer->dataSize;

    /* Set the ECSPI state to busy */
    handle->state = kECSPI_Busy;

    /* Select ECSPI channel to current channel
     * Note:
     *     xfer.channel must be configured before transferfer, because every channel has
     *     it's own configuration, if don't configure this parameter, transfer channel
     *     will use the default channel0.
     */
    ECSPI_SetChannelSelect(base, xfer->channel);

    /* First send data to Tx FIFO to start a ECSPI transfer */
    ECSPI_SendTransfer(base, handle);

    if (NULL != xfer->rxData)
    {
        /* Enable Rx data request interrupt and receive overflow interrupt, when data in RX FIFO buffer is greater
         * than the RX_THRESHOLD, then a interrupt occurred. Only enable Rx interrupt,
         * use rx interrupt to driver ECSPI transfer.
         */
        ECSPI_EnableInterrupts(base, kECSPI_RxFifoReadyInterruptEnable | kECSPI_RxFifoOverFlowInterruptEnable);
    }
    else
    {
        /* Enable Tx data request interrupt, when data in TX FIFO buffer is greater
         * than the TX_THRESHOLD, then a interrupt occurred.
         */
        ECSPI_EnableInterrupts(base, kECSPI_TxFifoDataRequstInterruptEnable);
    }

    return kStatus_Success;
}

status_t ECSPI_MasterTransferGetCount(ECSPI_Type *base, ecspi_master_handle_t *handle, size_t *count)
{
    assert(handle);

    status_t status = kStatus_Success;

    if (handle->state != kStatus_ECSPI_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        /* Return remaing bytes in different cases */
        if (handle->rxData)
        {
            *count = handle->transferSize - handle->rxRemainingBytes;
        }
        else
        {
            *count = handle->transferSize - handle->txRemainingBytes;
        }
    }

    return status;
}

void ECSPI_MasterTransferAbort(ECSPI_Type *base, ecspi_master_handle_t *handle)
{
    assert(handle);

    /* Stop interrupts */
    if (NULL != handle->rxData)
    {
        ECSPI_DisableInterrupts(base, kECSPI_RxFifoReadyInterruptEnable | kECSPI_RxFifoOverFlowInterruptEnable);
    }
    else
    {
        ECSPI_DisableInterrupts(base, kECSPI_TxFifoDataRequstInterruptEnable);
    }
    /* Transfer finished, set the state to Done*/
    handle->state = kECSPI_Idle;

    /* Clear the internal state */
    handle->rxRemainingBytes = 0;
    handle->txRemainingBytes = 0;
}

void ECSPI_MasterTransferHandleIRQ(ECSPI_Type *base, ecspi_master_handle_t *handle)
{
    assert(handle);

    /* If hardware overflow happens */
    if (base->STATREG & ECSPI_STATREG_RO_MASK)
    {
        /* Clear overflow flag for next transfer */
        ECSPI_ClearStatusFlags(base, kECSPI_RxFifoOverFlowFlag);
        if (handle->callback)
        {
            (handle->callback)(base, handle, kStatus_ECSPI_HardwareOverFlow, handle->userData);
        }
    }
    /* If need to receive data, do a receive */
    if (handle->rxRemainingBytes)
    {
        ECSPI_ReceiveTransfer(base, handle);
    }

    /* We always need to send a data to make the ECSPI run */
    if (handle->txRemainingBytes)
    {
        ECSPI_SendTransfer(base, handle);
    }

    /* All the transfer finished */
    if ((handle->txRemainingBytes == 0) && (handle->rxRemainingBytes == 0))
    {
        /* Complete the transfer */
        ECSPI_MasterTransferAbort(base, handle);

        if (handle->callback)
        {
            (handle->callback)(base, handle, kStatus_Success, handle->userData);
        }
    }
}

void ECSPI_SlaveTransferCreateHandle(ECSPI_Type *base,
                                     ecspi_slave_handle_t *handle,
                                     ecspi_slave_callback_t callback,
                                     void *userData)
{
    assert(handle);

    /* Slave create handle share same logic with master create handle, the only difference
    is the Isr pointer. */
    ECSPI_MasterTransferCreateHandle(base, handle, callback, userData);
    s_ecspiSlaveIsr = ECSPI_SlaveTransferHandleIRQ;
}

void ECSPI_SlaveTransferHandleIRQ(ECSPI_Type *base, ecspi_slave_handle_t *handle)
{
    assert(handle);
    /* If hardware overflow happens */
    if (base->STATREG & ECSPI_STATREG_RO_MASK)
    {
        /* Clear overflow flag for next transfer */
        ECSPI_ClearStatusFlags(base, kECSPI_RxFifoOverFlowFlag);
        if (handle->callback)
        {
            (handle->callback)(base, handle, kStatus_ECSPI_HardwareOverFlow, handle->userData);
        }
    }
    /* If needs to receive data, do a receive */
    if (handle->rxRemainingBytes)
    {
        ECSPI_ReceiveTransfer(base, handle);
    }

    /* We always need to send a data to make the ECSPI run */
    if (handle->txRemainingBytes)
    {
        ECSPI_SendTransfer(base, handle);
    }

    /* All the transfer finished */
    if ((handle->txRemainingBytes == 0) && (handle->rxRemainingBytes == 0))
    {
        /* Complete the transfer */
        ECSPI_SlaveTransferAbort(base, handle);

        if (handle->callback)
        {
            (handle->callback)(base, handle, kStatus_Success, handle->userData);
        }
    }
}

static void ECSPI_CommonIRQHandler(ECSPI_Type *base, ecspi_master_handle_t *handle)
{
    if (ECSPI_IsMaster(base, handle->channel))
    {
        s_ecspiMasterIsr(base, handle);
    }
    else
    {
        s_ecspiSlaveIsr(base, handle);
    }
}

#if defined(ECSPI1)
void ECSPI1_DriverIRQHandler(void)
{
    assert(s_ecspiHandle[1]);
    ECSPI_CommonIRQHandler(ECSPI1, s_ecspiHandle[1]);
}
#endif /* ECSPI1 */

#if defined(ECSPI2)
void ECSPI2_DriverIRQHandler(void)
{
    assert(s_ecspiHandle[2]);
    ECSPI_CommonIRQHandler(ECSPI2, s_ecspiHandle[2]);
}
#endif /* ECSPI2 */

#if defined(ECSPI3)
void ECSPI3_DriverIRQHandler(void)
{
    assert(s_ecspiHandle[3]);
    ECSPI_CommonIRQHandler(ECSPI3, s_ecspiHandle[3]);
}
#endif /* ECSPI3 */

#if defined(ECSPI4)
void ECSPI4_DriverIRQHandler(void)
{
    assert(s_ecspiHandle[4]);
    ECSPI_CommonIRQHandler(ECSPI4, s_ecspiHandle[4]);
}
#endif /* ECSPI4 */
