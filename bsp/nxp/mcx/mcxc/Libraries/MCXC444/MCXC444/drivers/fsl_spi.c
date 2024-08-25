/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_spi.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.spi"
#endif

/*! @brief SPI transfer state, which is used for SPI transactiaonl APIs' internal state. */
enum _spi_transfer_states_t
{
    kSPI_Idle = 0x0, /*!< SPI is idle state */
    kSPI_Busy        /*!< SPI is busy tranferring data. */
};

/*! @brief Typedef for spi master interrupt handler. spi master and slave handle is the same. */
typedef void (*spi_isr_t)(SPI_Type *base, spi_master_handle_t *spiHandle);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Sends a buffer of data bytes in non-blocking way.
 *
 * @param base SPI base pointer
 * @param buffer The data bytes to send
 * @param size The number of data bytes to send
 */
static void SPI_WriteNonBlocking(SPI_Type *base, const uint8_t *buffer, size_t size);

/*!
 * @brief Receive a buffer of data bytes in non-blocking way.
 *
 * @param base SPI base pointer
 * @param buffer The data bytes to send
 * @param size The number of data bytes to send
 */
static void SPI_ReadNonBlocking(SPI_Type *base, uint8_t *buffer, size_t size);

/*!
 * @brief Get the waterrmark value for this SPI instance.
 *
 * @param base SPI base pointer
 * @return Watermark value for the SPI instance.
 */
static uint8_t SPI_GetWatermark(SPI_Type *base);

/*!
 * @brief Send a piece of data for SPI.
 *
 * This function computes the number of data to be written into D register or Tx FIFO,
 * and write the data into it. At the same time, this function updates the values in
 * master handle structure.
 *
 * @param base SPI base pointer
 * @param handle Pointer to SPI master handle structure.
 */
static void SPI_SendTransfer(SPI_Type *base, spi_master_handle_t *handle);

/*!
 * @brief Receive a piece of data for SPI master.
 *
 * This function computes the number of data to receive from D register or Rx FIFO,
 * and write the data to destination address. At the same time, this function updates
 * the values in master handle structure.
 *
 * @param base SPI base pointer
 * @param handle Pointer to SPI master handle structure.
 */
static void SPI_ReceiveTransfer(SPI_Type *base, spi_master_handle_t *handle);

/*!
 * @brief Common IRQ handler for SPI.
 *
 * @param base SPI base pointer.
 * @param instance SPI instance number.
 */
static void SPI_CommonIRQHandler(SPI_Type *base, uint32_t instance);
/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief SPI internal handle pointer array */
static spi_master_handle_t *s_spiHandle[FSL_FEATURE_SOC_SPI_COUNT];
/*! @brief Base pointer array */
static SPI_Type *const s_spiBases[] = SPI_BASE_PTRS;
/*! @brief IRQ name array */
static const IRQn_Type s_spiIRQ[] = SPI_IRQS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Clock array name */
static const clock_ip_name_t s_spiClock[] = SPI_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*! @brief Pointer to master IRQ handler for each instance. */
static spi_isr_t s_spiMasterIsr;
static spi_isr_t s_spiSlaveIsr;

/* @brief Dummy data for each instance. This data is used when user's tx buffer is NULL*/
volatile uint8_t g_spiDummyData[ARRAY_SIZE(s_spiBases)] = {0};
/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * brief Get the instance for SPI module.
 *
 * param base SPI base address
 */
uint32_t SPI_GetInstance(SPI_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_spiBases); instance++)
    {
        if (s_spiBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_spiBases));

    return instance;
}

/*!
 * brief Set up the dummy data.
 *
 * param base SPI peripheral address.
 * param dummyData Data to be transferred when tx buffer is NULL.
 */
void SPI_SetDummyData(SPI_Type *base, uint8_t dummyData)
{
    uint32_t instance        = SPI_GetInstance(base);
    g_spiDummyData[instance] = dummyData;
}

static void SPI_WriteNonBlocking(SPI_Type *base, const uint8_t *buffer, size_t size)
{
    uint32_t i            = 0;
    uint8_t bytesPerFrame = 1U;
    uint32_t instance     = SPI_GetInstance(base);

#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    /* Check if 16 bits or 8 bits */
    bytesPerFrame = ((base->C2 & SPI_C2_SPIMODE_MASK) >> SPI_C2_SPIMODE_SHIFT) + 1U;
#endif

    while (i < size)
    {
        if (buffer != NULL)
        {
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
            base->DL = *buffer++;
            /*16 bit mode*/
            if ((base->C2 & SPI_C2_SPIMODE_MASK) != 0U)
            {
                base->DH = *buffer++;
            }
#else
            base->D   = *buffer++;
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */
        }
        /* Send dummy data */
        else
        {
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && (FSL_FEATURE_SPI_16BIT_TRANSFERS)
            base->DL = g_spiDummyData[instance] & 0xFFU;
            base->DH = g_spiDummyData[instance] & 0xFFU;
#else
            base->D   = g_spiDummyData[instance] & 0xFFU;
#endif
        }
        i += bytesPerFrame;
    }
}

static void SPI_ReadNonBlocking(SPI_Type *base, uint8_t *buffer, size_t size)
{
    uint32_t i            = 0U;
    uint8_t bytesPerFrame = 1U;

#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    /* Check if 16 bits or 8 bits */
    bytesPerFrame = ((base->C2 & SPI_C2_SPIMODE_MASK) >> SPI_C2_SPIMODE_SHIFT) + 1U;
#endif

    while (i < size)
    {
        if (buffer != NULL)
        {
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
            *buffer++ = base->DL;
            /*16 bit mode*/
            if ((base->C2 & SPI_C2_SPIMODE_MASK) != 0U)
            {
                *buffer++ = base->DH;
            }
#else
            *buffer++ = base->D;
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */
        }
        else
        {
            (void)SPI_ReadData(base);
        }
        i += bytesPerFrame;
    }
}

/* Get the watermark value of transfer. Please note that the entery width of FIFO is 16 bits. */
static uint8_t SPI_GetWatermark(SPI_Type *base)
{
    uint8_t ret = 0U;
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    uint8_t rxSize = 0U;
    /* Get the number to be sent if there is FIFO */
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        rxSize = (base->C3 & SPI_C3_RNFULLF_MARK_MASK) >> SPI_C3_RNFULLF_MARK_SHIFT;
        if (rxSize == 0U)
        {
            ret = (uint8_t)FSL_FEATURE_SPI_FIFO_SIZEn(base) * 3U / 4U;
        }
        else
        {
            ret = (uint8_t)FSL_FEATURE_SPI_FIFO_SIZEn(base) / 2U;
        }
    }
    /* If no FIFO, just set the watermark to 1 */
    else
    {
        ret = 1U;
    }
#else
    ret = 1U;
#endif /* FSL_FEATURE_SPI_HAS_FIFO */
    return ret;
}

static void SPI_SendInitialTransfer(SPI_Type *base, spi_master_handle_t *handle)
{
    uint8_t bytestoTransfer = handle->bytePerFrame;

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && (FSL_FEATURE_SPI_HAS_FIFO)
    if (handle->watermark > 1U)
    {
        /* In the first time to send data to FIFO, if transfer size is not larger than
         * the FIFO size, send all data to FIFO, or send data to make the FIFO full.
         * Besides, The FIFO's entry width is 16 bits, need to translate it to bytes.
         */
        int32_t fifosize = FSL_FEATURE_SPI_FIFO_SIZEn(base);
        assert(fifosize > 0);
        bytestoTransfer = (uint8_t)MIN(handle->txRemainingBytes, ((uint32_t)fifosize * 2U));
    }
#endif

    SPI_WriteNonBlocking(base, handle->txData, bytestoTransfer);

    /* Update handle information */
    if (handle->txData != NULL)
    {
        handle->txData += bytestoTransfer;
    }
    handle->txRemainingBytes -= bytestoTransfer;
}

static void SPI_SendTransfer(SPI_Type *base, spi_master_handle_t *handle)
{
    uint8_t bytes = handle->bytePerFrame;

    /* Read S register and ensure SPTEF is 1, otherwise the write would be ignored. */
    if (handle->watermark == 1U)
    {
        /* Send data */
        if ((base->C1 & SPI_C1_MSTR_MASK) != 0U)
        {
            /* As a master, only write once */
            if ((base->S & SPI_S_SPTEF_MASK) != 0U)
            {
                SPI_WriteNonBlocking(base, handle->txData, bytes);
                /* Update handle information */
                if (handle->txData != NULL)
                {
                    handle->txData += bytes;
                }
                handle->txRemainingBytes -= bytes;
            }
        }
        else
        {
            /* As a slave, send data until SPTEF cleared */
            while (((base->S & SPI_S_SPTEF_MASK) != 0U) && (handle->txRemainingBytes >= bytes))
            {
                SPI_WriteNonBlocking(base, handle->txData, bytes);

                /* Update handle information */
                if (handle->txData != NULL)
                {
                    handle->txData += bytes;
                }
                handle->txRemainingBytes -= bytes;
            }
        }
    }

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && (FSL_FEATURE_SPI_HAS_FIFO)
    /* If use FIFO */
    else
    {
        /* The FIFO's entry width is 16 bits, need to translate it to bytes. */
        uint8_t bytestoTransfer = (uint8_t)handle->watermark * 2U;

        if (handle->txRemainingBytes < 8U)
        {
            bytestoTransfer = (uint8_t)handle->txRemainingBytes;
        }

        SPI_WriteNonBlocking(base, handle->txData, bytestoTransfer);

        /* Update handle information */
        if (handle->txData != NULL)
        {
            handle->txData += bytestoTransfer;
        }
        handle->txRemainingBytes -= bytestoTransfer;
    }
#endif
}

static void SPI_ReceiveTransfer(SPI_Type *base, spi_master_handle_t *handle)
{
    uint8_t bytes = handle->bytePerFrame;

    /* Read S register and ensure SPRF is 1, otherwise the write would be ignored. */
    if (handle->watermark == 1U)
    {
        if ((base->S & SPI_S_SPRF_MASK) != 0U)
        {
            SPI_ReadNonBlocking(base, handle->rxData, bytes);

            /* Update information in handle */
            if (handle->rxData != NULL)
            {
                handle->rxData += bytes;
            }
            handle->rxRemainingBytes -= bytes;
        }
    }
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && (FSL_FEATURE_SPI_HAS_FIFO)
    /* If use FIFO */
    else
    {
        /* While rx fifo not empty and remaining data can also trigger the last interrupt */
        while ((base->S & SPI_S_RFIFOEF_MASK) == 0U)
        {
            SPI_ReadNonBlocking(base, handle->rxData, bytes);

            /* Update information in handle */
            if (handle->rxData != NULL)
            {
                handle->rxData += bytes;
            }
            handle->rxRemainingBytes -= bytes;

            /* If the reamining data equals to watermark, leave to last interrupt */
            if (handle->rxRemainingBytes == ((uint32_t)handle->watermark * 2U))
            {
                break;
            }
        }
    }
#endif
}

/*!
 * brief  Sets the SPI master configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in SPI_MasterInit().
 * User may use the initialized structure unchanged in SPI_MasterInit(), or modify
 * some fields of the structure before calling SPI_MasterInit(). After calling this API,
 * the master is ready to transfer.
 * Example:
   code
   spi_master_config_t config;
   SPI_MasterGetDefaultConfig(&config);
   endcode
 *
 * param config pointer to master config structure
 */
void SPI_MasterGetDefaultConfig(spi_master_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)(void) memset(config, 0, sizeof(*config));

    config->enableMaster         = true;
    config->enableStopInWaitMode = false;
    config->polarity             = kSPI_ClockPolarityActiveHigh;
    config->phase                = kSPI_ClockPhaseFirstEdge;
    config->direction            = kSPI_MsbFirst;

#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    config->dataMode = kSPI_8BitMode;
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    config->txWatermark = kSPI_TxFifoOneHalfEmpty;
    config->rxWatermark = kSPI_RxFifoOneHalfFull;
#endif /* FSL_FEATURE_SPI_HAS_FIFO */

    config->pinMode      = kSPI_PinModeNormal;
    config->outputMode   = kSPI_SlaveSelectAutomaticOutput;
    config->baudRate_Bps = 500000U;
}

/*!
 * brief Initializes the SPI with master configuration.
 *
 * The configuration structure can be filled by user from scratch, or be set with default
 * values by SPI_MasterGetDefaultConfig(). After calling this API, the slave is ready to transfer.
 * Example
   code
   spi_master_config_t config = {
   .baudRate_Bps = 400000,
   ...
   };
   SPI_MasterInit(SPI0, &config);
   endcode
 *
 * param base SPI base pointer
 * param config pointer to master configuration structure
 * param srcClock_Hz Source clock frequency.
 */
void SPI_MasterInit(SPI_Type *base, const spi_master_config_t *config, uint32_t srcClock_Hz)
{
    assert((config != NULL) && (srcClock_Hz != 0U));

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Open clock gate for SPI and open interrupt */
    CLOCK_EnableClock(s_spiClock[SPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Disable SPI before configuration */
    base->C1 &= (uint8_t)(~SPI_C1_SPE_MASK);

    /* Configure clock polarity and phase, set SPI to master */
    base->C1 = SPI_C1_MSTR(1U) | SPI_C1_CPOL(config->polarity) | SPI_C1_CPHA(config->phase) |
               SPI_C1_SSOE((uint8_t)config->outputMode & 1U) | SPI_C1_LSBFE((uint8_t)config->direction);

/* Set data mode, and also pin mode and mode fault settings */
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    base->C2 = SPI_C2_MODFEN((uint8_t)config->outputMode >> 1U) | SPI_C2_BIDIROE((uint8_t)config->pinMode >> 1U) |
               SPI_C2_SPISWAI(config->enableStopInWaitMode) | SPI_C2_SPC0((uint8_t)config->pinMode & 1U) |
               SPI_C2_SPIMODE(config->dataMode);
#else
    base->C2 = SPI_C2_MODFEN((uint8_t)config->outputMode >> 1U) | SPI_C2_BIDIROE((uint8_t)config->pinMode >> 1U) |
               SPI_C2_SPISWAI(config->enableStopInWaitMode) | SPI_C2_SPC0((uint8_t)config->pinMode & 1U);
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

/* Set watermark, FIFO is enabled */
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        base->C3 = SPI_C3_TNEAREF_MARK(config->txWatermark) | SPI_C3_RNFULLF_MARK(config->rxWatermark) |
                   SPI_C3_INTCLR(0U) | SPI_C3_FIFOMODE(1U);
    }
#endif /* FSL_FEATURE_SPI_HAS_FIFO */

    /* Set baud rate */
    SPI_MasterSetBaudRate(base, config->baudRate_Bps, srcClock_Hz);

    /* Set the dummy data, this data will usefull when tx buffer is NULL. */
    SPI_SetDummyData(base, SPI_DUMMYDATA);

    /* Enable SPI */
    if (config->enableMaster)
    {
        base->C1 |= SPI_C1_SPE_MASK;
    }
}

/*!
 * brief  Sets the SPI slave configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in SPI_SlaveInit().
 * Modify some fields of the structure before calling SPI_SlaveInit().
 * Example:
   code
   spi_slave_config_t config;
   SPI_SlaveGetDefaultConfig(&config);
   endcode
 *
 * param config pointer to slave configuration structure
 */
void SPI_SlaveGetDefaultConfig(spi_slave_config_t *config)
{
    /* Initializes the configure structure to zero. */
    (void)(void) memset(config, 0, sizeof(*config));

    config->enableSlave          = true;
    config->polarity             = kSPI_ClockPolarityActiveHigh;
    config->phase                = kSPI_ClockPhaseFirstEdge;
    config->direction            = kSPI_MsbFirst;
    config->enableStopInWaitMode = false;

#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    config->dataMode = kSPI_8BitMode;
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    config->txWatermark = kSPI_TxFifoOneHalfEmpty;
    config->rxWatermark = kSPI_RxFifoOneHalfFull;
#endif /* FSL_FEATURE_SPI_HAS_FIFO */
    config->pinMode = kSPI_PinModeNormal;
}

/*!
 * brief Initializes the SPI with slave configuration.
 *
 * The configuration structure can be filled by user from scratch or be set with
 * default values by SPI_SlaveGetDefaultConfig().
 * After calling this API, the slave is ready to transfer.
 * Example
   code
    spi_slave_config_t config = {
    .polarity = kSPIClockPolarity_ActiveHigh;
    .phase = kSPIClockPhase_FirstEdge;
    .direction = kSPIMsbFirst;
    ...
    };
    SPI_MasterInit(SPI0, &config);
   endcode
 *
 * param base SPI base pointer
 * param config pointer to master configuration structure
 */
void SPI_SlaveInit(SPI_Type *base, const spi_slave_config_t *config)
{
    assert(config != NULL);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Open clock gate for SPI and open interrupt */
    CLOCK_EnableClock(s_spiClock[SPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Disable SPI before configuration */
    base->C1 &= (uint8_t)(~SPI_C1_SPE_MASK);

    /* Configure master and clock polarity and phase */
    base->C1 =
        SPI_C1_MSTR(0U) | SPI_C1_CPOL(config->polarity) | SPI_C1_CPHA(config->phase) | SPI_C1_LSBFE(config->direction);

/* Configure data mode if needed */
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    base->C2 = SPI_C2_SPIMODE(config->dataMode) | SPI_C2_SPISWAI(config->enableStopInWaitMode) |
               SPI_C2_BIDIROE((uint8_t)config->pinMode >> 1U) | SPI_C2_SPC0((uint8_t)config->pinMode & 1U);
#else
    base->C2 = SPI_C2_SPISWAI(config->enableStopInWaitMode) | SPI_C2_BIDIROE((uint8_t)config->pinMode >> 1U) |
               SPI_C2_SPC0((uint8_t)config->pinMode & 1U);
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

/* Set watermark */
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        base->C3 = SPI_C3_TNEAREF_MARK(config->txWatermark) | SPI_C3_RNFULLF_MARK(config->rxWatermark) |
                   SPI_C3_INTCLR(0U) | SPI_C3_FIFOMODE(1U);
    }
#endif /* FSL_FEATURE_SPI_HAS_FIFO */

    /* Set the dummy data, this data will usefull when tx buffer is NULL. */
    SPI_SetDummyData(base, SPI_DUMMYDATA);

    /* Enable SPI */
    if (config->enableSlave)
    {
        base->C1 |= SPI_C1_SPE_MASK;
    }
}

/*!
 * brief De-initializes the SPI.
 *
 * Calling this API resets the SPI module, gates the SPI clock.
 * The SPI module can't work unless calling the SPI_MasterInit/SPI_SlaveInit to initialize module.
 *
 * param base SPI base pointer
 */
void SPI_Deinit(SPI_Type *base)
{
    /* Disable SPI module before shutting down */
    base->C1 &= (uint8_t)(~SPI_C1_SPE_MASK);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Gate the clock */
    CLOCK_DisableClock(s_spiClock[SPI_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets the status flag.
 *
 * param base SPI base pointer
 * return SPI Status, use status flag to AND #_spi_flags could get the related status.
 */
uint32_t SPI_GetStatusFlags(SPI_Type *base)
{
    uint32_t status = (uint32_t)base->S;
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        status |= (((uint32_t)base->CI) << 8U);
    }
#endif /* FSL_FEATURE_SPI_HAS_FIFO */
    return status;
}

/*!
 * brief Enables the interrupt for the SPI.
 *
 * param base SPI base pointer
 * param mask SPI interrupt source. The parameter can be any combination of the following values:
 *        arg kSPI_RxFullAndModfInterruptEnable
 *        arg kSPI_TxEmptyInterruptEnable
 *        arg kSPI_MatchInterruptEnable
 *        arg kSPI_RxFifoNearFullInterruptEnable
 *        arg kSPI_TxFifoNearEmptyInterruptEnable
 */
void SPI_EnableInterrupts(SPI_Type *base, uint32_t mask)
{
    /* Rx full interrupt */
    if ((mask & (uint32_t)kSPI_RxFullAndModfInterruptEnable) != 0U)
    {
        base->C1 |= SPI_C1_SPIE_MASK;
    }

    /* Tx empty interrupt */
    if ((mask & (uint32_t)kSPI_TxEmptyInterruptEnable) != 0U)
    {
        base->C1 |= SPI_C1_SPTIE_MASK;
    }

    /* Data match interrupt */
    if ((mask & (uint32_t)kSPI_MatchInterruptEnable) != 0U)
    {
        base->C2 |= SPI_C2_SPMIE_MASK;
    }

/* FIFO related interrupts */
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        /* Rx FIFO near full interrupt */
        if ((mask & (uint32_t)kSPI_RxFifoNearFullInterruptEnable) != 0U)
        {
            base->C3 |= SPI_C3_RNFULLIEN_MASK;
        }

        /* Tx FIFO near empty interrupt */
        if ((mask & (uint32_t)kSPI_TxFifoNearEmptyInterruptEnable) != 0U)
        {
            base->C3 |= SPI_C3_TNEARIEN_MASK;
        }
    }
#endif /* FSL_FEATURE_SPI_HAS_FIFO */
}

/*!
 * brief Disables the interrupt for the SPI.
 *
 * param base SPI base pointer
 * param mask SPI interrupt source. The parameter can be any combination of the following values:
 *        arg kSPI_RxFullAndModfInterruptEnable
 *        arg kSPI_TxEmptyInterruptEnable
 *        arg kSPI_MatchInterruptEnable
 *        arg kSPI_RxFifoNearFullInterruptEnable
 *        arg kSPI_TxFifoNearEmptyInterruptEnable
 */
void SPI_DisableInterrupts(SPI_Type *base, uint32_t mask)
{
    /* Rx full interrupt */
    if ((mask & (uint32_t)kSPI_RxFullAndModfInterruptEnable) != 0U)
    {
        base->C1 &= (uint8_t)(~SPI_C1_SPIE_MASK);
    }

    /* Tx empty interrupt */
    if ((mask & (uint32_t)kSPI_TxEmptyInterruptEnable) != 0U)
    {
        base->C1 &= (uint8_t)(~SPI_C1_SPTIE_MASK);
    }

    /* Data match interrupt */
    if ((mask & (uint32_t)kSPI_MatchInterruptEnable) != 0U)
    {
        base->C2 &= (uint8_t)(~SPI_C2_SPMIE_MASK);
    }

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        /* Rx FIFO near full interrupt */
        if ((mask & (uint32_t)kSPI_RxFifoNearFullInterruptEnable) != 0U)
        {
            base->C3 &= (uint8_t)(~SPI_C3_RNFULLIEN_MASK);
        }

        /* Tx FIFO near empty interrupt */
        if ((mask & (uint32_t)kSPI_TxFifoNearEmptyInterruptEnable) != 0U)
        {
            base->C3 &= (uint8_t)(~SPI_C3_TNEARIEN_MASK);
        }
    }
#endif /* FSL_FEATURE_SPI_HAS_FIFO */
}

/*!
 * brief Sets the baud rate for SPI transfer. This is only used in master.
 *
 * param base SPI base pointer
 * param baudRate_Bps baud rate needed in Hz.
 * param srcClock_Hz SPI source clock frequency in Hz.
 */
void SPI_MasterSetBaudRate(SPI_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz)
{
    uint32_t prescaler;
    uint32_t bestPrescaler;
    uint32_t rateDivisor;
    uint32_t bestDivisor;
    uint32_t rateDivisorValue;
    uint32_t realBaudrate;
    uint32_t diff;
    uint32_t min_diff;
    uint32_t freq = baudRate_Bps;

    /* Find combination of prescaler and scaler resulting in baudrate closest to the requested value */
    min_diff = 0xFFFFFFFFU;

    /* Set the maximum divisor bit settings for each of the following divisors */
    bestPrescaler = 7U;
    bestDivisor   = 8U;

    /* In all for loops, if min_diff = 0, the exit for loop*/
    for (prescaler = 0U; prescaler <= 7U; prescaler++)
    {
        if (min_diff == 0U)
        {
            break;
        }
        /* Initialize to div-by-2 */
        rateDivisorValue = 2U;

        for (rateDivisor = 0; rateDivisor <= 8U; rateDivisor++)
        {
            if (min_diff == 0U)
            {
                break;
            }
            /* Calculate actual baud rate, note need to add 1 to prescaler */
            realBaudrate = ((srcClock_Hz) / ((prescaler + 1U) * rateDivisorValue));

            /* Calculate the baud rate difference based on the conditional statement ,that states that the
            calculated baud rate must not exceed the desired baud rate */
            if (freq >= realBaudrate)
            {
                diff = freq - realBaudrate;
                if (min_diff > diff)
                {
                    /* A better match found */
                    min_diff      = diff;
                    bestPrescaler = prescaler;
                    bestDivisor   = rateDivisor;
                }
            }

            /* Multiply by 2 for each iteration, possible divisor values: 2, 4, 8, 16, ... 512 */
            rateDivisorValue *= 2U;
        }
    }

    /* Write the best prescalar and baud rate scalar */
    base->BR = SPI_BR_SPR(bestDivisor) | SPI_BR_SPPR(bestPrescaler);
}

/*!
 * brief Sends a buffer of data bytes using a blocking method.
 *
 * note This function blocks via polling until all bytes have been sent.
 *
 * param base SPI base pointer
 * param buffer The data bytes to send
 * param size The number of data bytes to send
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_SPI_Timeout The transfer timed out and was aborted.
 */
status_t SPI_WriteBlocking(SPI_Type *base, uint8_t *buffer, size_t size)
{
    uint32_t i            = 0;
    uint8_t bytesPerFrame = 1U;

#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    /* Check if 16 bits or 8 bits */
    bytesPerFrame = ((base->C2 & SPI_C2_SPIMODE_MASK) >> SPI_C2_SPIMODE_SHIFT) + 1U;
#endif

#if SPI_RETRY_TIMES
    uint32_t waitTimes;
#endif

    while (i < size)
    {
#if SPI_RETRY_TIMES
        waitTimes = SPI_RETRY_TIMES;
        while (((base->S & SPI_S_SPTEF_MASK) == 0U) && (--waitTimes != 0U))
#else
        while ((base->S & SPI_S_SPTEF_MASK) == 0U)
#endif
        {
        }
#if SPI_RETRY_TIMES
        if (waitTimes == 0U)
        {
            return kStatus_SPI_Timeout;
        }
#endif

        /* Send a frame of data */
        SPI_WriteNonBlocking(base, buffer, bytesPerFrame);

        i += bytesPerFrame;
        buffer += bytesPerFrame;
    }

    return kStatus_Success;
}

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
/*!
 * brief Enables or disables the FIFO if there is a FIFO.
 *
 * param base SPI base pointer
 * param enable True means enable FIFO, false means disable FIFO.
 */
void SPI_EnableFIFO(SPI_Type *base, bool enable)
{
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        if (enable)
        {
            base->C3 |= SPI_C3_FIFOMODE_MASK;
        }
        else
        {
            base->C3 &= (uint8_t)(~SPI_C3_FIFOMODE_MASK);
        }
    }
}
#endif /* FSL_FEATURE_SPI_HAS_FIFO */

/*!
 * brief Writes a data into the SPI data register.
 *
 * param base SPI base pointer
 * param data needs to be write.
 */
void SPI_WriteData(SPI_Type *base, uint16_t data)
{
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && (FSL_FEATURE_SPI_16BIT_TRANSFERS)
    base->DL = (uint8_t)data & 0xFFU;
    base->DH = (uint8_t)(data >> 8U) & 0xFFU;
#else
    base->D = (uint8_t)data & 0xFFU;
#endif
}

/*!
 * brief Gets a data from the SPI data register.
 *
 * param base SPI base pointer
 * return Data in the register.
 */
uint16_t SPI_ReadData(SPI_Type *base)
{
    uint16_t val = 0;
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && (FSL_FEATURE_SPI_16BIT_TRANSFERS)
    val = base->DL;
    val |= (uint16_t)((uint16_t)(base->DH) << 8U);
#else
    val = base->D;
#endif
    return val;
}

/*!
 * brief Transfers a block of data using a polling method.
 *
 * param base SPI base pointer
 * param xfer pointer to spi_xfer_config_t structure
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_SPI_Timeout The transfer timed out and was aborted.
 */
status_t SPI_MasterTransferBlocking(SPI_Type *base, spi_transfer_t *xfer)
{
    assert(xfer != NULL);

    uint8_t bytesPerFrame = 1U;
#if SPI_RETRY_TIMES
    uint32_t waitTimes = SPI_RETRY_TIMES;
#endif

    /* Check if the argument is legal */
    if ((xfer->txData == NULL) && (xfer->rxData == NULL))
    {
        return (status_t)kStatus_InvalidArgument;
    }

#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && FSL_FEATURE_SPI_16BIT_TRANSFERS
    /* Check if 16 bits or 8 bits */
    bytesPerFrame = ((base->C2 & SPI_C2_SPIMODE_MASK) >> SPI_C2_SPIMODE_SHIFT) + 1U;
#endif

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO

    /* Disable FIFO, as the FIFO may cause data loss if the data size is not integer
       times of 2bytes. As SPI cannot set watermark to 0, only can set to 1/2 FIFO size or 3/4 FIFO
       size. */
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        base->C3 &= (uint8_t)(~SPI_C3_FIFOMODE_MASK);
    }

#endif /* FSL_FEATURE_SPI_HAS_FIFO */

    /* Begin the polling transfer until all data sent */
    while (xfer->dataSize > 0U)
    {
        /* Data send */
#if SPI_RETRY_TIMES
        waitTimes = SPI_RETRY_TIMES;
        while (((base->S & SPI_S_SPTEF_MASK) == 0U) && (--waitTimes != 0U))
        {
        }
        if (waitTimes == 0U)
        {
            return kStatus_SPI_Timeout;
        }
#else
        while ((base->S & SPI_S_SPTEF_MASK) == 0U)
        {
        }
#endif
        SPI_WriteNonBlocking(base, xfer->txData, bytesPerFrame);
        if (xfer->txData != NULL)
        {
            xfer->txData += bytesPerFrame;
        }

#if SPI_RETRY_TIMES
        waitTimes = SPI_RETRY_TIMES;
        while (((base->S & SPI_S_SPRF_MASK) == 0U) && (--waitTimes != 0U))
        {
        }
        if (waitTimes == 0U)
        {
            return kStatus_SPI_Timeout;
        }
#else
        while ((base->S & SPI_S_SPRF_MASK) == 0U)
        {
        }
#endif
        SPI_ReadNonBlocking(base, xfer->rxData, bytesPerFrame);
        if (xfer->rxData != NULL)
        {
            xfer->rxData += bytesPerFrame;
        }

        /* Decrease the number */
        xfer->dataSize -= bytesPerFrame;
    }

    return kStatus_Success;
}

/*!
 * brief Initializes the SPI master handle.
 *
 * This function initializes the SPI master handle which can be used for other SPI master transactional APIs. Usually,
 * for a specified SPI instance, call this API once to get the initialized handle.
 *
 * param base SPI peripheral base address.
 * param handle SPI handle pointer.
 * param callback Callback function.
 * param userData User data.
 */
void SPI_MasterTransferCreateHandle(SPI_Type *base,
                                    spi_master_handle_t *handle,
                                    spi_master_callback_t callback,
                                    void *userData)
{
    assert(handle != NULL);

    uint32_t instance = SPI_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Initialize the handle */
    s_spiHandle[instance] = handle;
    handle->callback      = callback;
    handle->userData      = userData;
    s_spiMasterIsr        = SPI_MasterTransferHandleIRQ;
    handle->watermark     = SPI_GetWatermark(base);

/* Get the bytes per frame */
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && (FSL_FEATURE_SPI_16BIT_TRANSFERS)
    handle->bytePerFrame = ((base->C2 & SPI_C2_SPIMODE_MASK) >> SPI_C2_SPIMODE_SHIFT) + 1U;
#else
    handle->bytePerFrame = 1U;
#endif

    /* Enable SPI NVIC */
    (void)EnableIRQ(s_spiIRQ[instance]);
}

/*!
 * brief Performs a non-blocking SPI interrupt transfer.
 *
 * note The API immediately returns after transfer initialization is finished.
 * Call SPI_GetStatusIRQ() to get the transfer status.
 * note If SPI transfer data frame size is 16 bits, the transfer size cannot be an odd number.
 *
 * param base SPI peripheral base address.
 * param handle pointer to spi_master_handle_t structure which stores the transfer state
 * param xfer pointer to spi_xfer_config_t structure
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_SPI_Busy SPI is not idle, is running another transfer.
 */
status_t SPI_MasterTransferNonBlocking(SPI_Type *base, spi_master_handle_t *handle, spi_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));
    uint32_t mask = 0U;

    /* Check if SPI is busy */
    if (handle->state == (uint32_t)kSPI_Busy)
    {
        return (status_t)kStatus_SPI_Busy;
    }

    /* Check if the input arguments valid */
    if (((xfer->txData == NULL) && (xfer->rxData == NULL)) || (xfer->dataSize == 0U))
    {
        return (status_t)kStatus_InvalidArgument;
    }

    /* Set the handle information */
    handle->txData           = xfer->txData;
    handle->rxData           = xfer->rxData;
    handle->transferSize     = xfer->dataSize;
    handle->txRemainingBytes = xfer->dataSize;
    handle->rxRemainingBytes = xfer->dataSize;

    /* Set the SPI state to busy */
    handle->state = (uint32_t)kSPI_Busy;

    /* Enable Interrupt */
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO

    handle->watermark = SPI_GetWatermark(base);

    /* If the size of the transfer size less than watermark, set watermark to 1 */
    if (xfer->dataSize < (uint32_t)handle->watermark * 2U)
    {
        handle->watermark = 1U;
    }

    /* According to watermark size, enable interrupts */
    if (handle->watermark > 1U)
    {
        /* Enable Rx near full interrupt */
        mask = (uint32_t)kSPI_RxFifoNearFullInterruptEnable;
        /* Enable Tx near full interrupt only if there are data to send */
        if (handle->txData != NULL)
        {
            mask |= (uint32_t)kSPI_TxFifoNearEmptyInterruptEnable;
        }

        SPI_EnableFIFO(base, true);
        /* First send a piece of data to Tx Data or FIFO to start a SPI transfer */
        while ((base->S & SPI_S_TNEAREF_MASK) != SPI_S_TNEAREF_MASK)
        {
        }
        SPI_SendInitialTransfer(base, handle);
    }
    else
    {
        /* Enable Rx full interrupt */
        mask = (uint32_t)kSPI_RxFullAndModfInterruptEnable;
        /* Enable Tx full interrupt only if there are data to send */
        if (handle->txData != NULL)
        {
            mask |= (uint32_t)kSPI_TxEmptyInterruptEnable;
        }

        SPI_EnableFIFO(base, false);
        while ((base->S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK)
        {
        }
        /* First send a piece of data to Tx Data or FIFO to start a SPI transfer */
        SPI_SendInitialTransfer(base, handle);
    }
#else
    /* Enable Rx full interrupt */
    mask = (uint32_t)kSPI_RxFullAndModfInterruptEnable;
    /* Enable Tx full interrupt only if there are data to send */
    if (handle->txData != NULL)
    {
        mask |= (uint32_t)kSPI_TxEmptyInterruptEnable;
    }

    while ((base->S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK)
    {
    }
    /* First send a piece of data to Tx Data or FIFO to start a SPI transfer */
    SPI_SendInitialTransfer(base, handle);
#endif

    SPI_EnableInterrupts(base, mask);
    return kStatus_Success;
}

/*!
 * brief Gets the bytes of the SPI interrupt transferred.
 *
 * param base SPI peripheral base address.
 * param handle Pointer to SPI transfer handle, this should be a static variable.
 * param count Transferred bytes of SPI master.
 * retval kStatus_SPI_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t SPI_MasterTransferGetCount(SPI_Type *base, spi_master_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kSPI_Busy)
    {
        status = (status_t)kStatus_NoTransferInProgress;
    }
    else
    {
        /* Return remaing bytes in different cases */
        if (handle->rxData != NULL)
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

/*!
 * brief Aborts an SPI transfer using interrupt.
 *
 * param base SPI peripheral base address.
 * param handle Pointer to SPI transfer handle, this should be a static variable.
 */
void SPI_MasterTransferAbort(SPI_Type *base, spi_master_handle_t *handle)
{
    assert(handle != NULL);
    uint32_t mask = (uint32_t)kSPI_TxEmptyInterruptEnable;

    /* Stop interrupts */
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    if (handle->watermark > 1U)
    {
        mask |= (uint32_t)kSPI_RxFifoNearFullInterruptEnable | (uint32_t)kSPI_TxFifoNearEmptyInterruptEnable;
    }
    else
    {
        mask |= (uint32_t)kSPI_RxFullAndModfInterruptEnable | (uint32_t)kSPI_TxEmptyInterruptEnable;
    }
#else
    mask |= (uint32_t)kSPI_RxFullAndModfInterruptEnable | (uint32_t)kSPI_TxEmptyInterruptEnable;
#endif

    SPI_DisableInterrupts(base, mask);
    /* Transfer finished, set the state to Done*/
    handle->state = (uint32_t)kSPI_Idle;

    /* Clear the internal state */
    handle->rxRemainingBytes = 0;
    handle->txRemainingBytes = 0;
}

/*!
 * brief Interrupts the handler for the SPI.
 *
 * param base SPI peripheral base address.
 * param handle pointer to spi_master_handle_t structure which stores the transfer state.
 */
void SPI_MasterTransferHandleIRQ(SPI_Type *base, spi_master_handle_t *handle)
{
    assert(handle != NULL);

    /* If needs to receive data, do a receive */
    if ((handle->rxRemainingBytes) != 0U)
    {
        SPI_ReceiveTransfer(base, handle);
    }

    /* We always need to send a data to make the SPI run */
    /* To prevent rx overflow, calculate the difference between rxRemainingBytes
       and txRemainingBytes and make sure the difference is smaller than watermark.
       The watermark is set according to FIFO size, for instance that does not have
       FIFO, the watermark is 1. */
    if (((handle->txRemainingBytes) != 0U) &&
        ((handle->rxRemainingBytes - handle->txRemainingBytes) < handle->watermark))
    {
        SPI_SendTransfer(base, handle);
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
        if (handle->txRemainingBytes == 0U)
        {
            SPI_DisableInterrupts(base, (uint32_t)kSPI_TxFifoNearEmptyInterruptEnable);
            SPI_EnableInterrupts(base, (uint32_t)kSPI_TxEmptyInterruptEnable);
        }
#endif
    }

    /* All the transfer finished */
    if ((handle->txRemainingBytes == 0U) && (handle->rxRemainingBytes == 0U))
    {
        if ((SPI_GetStatusFlags(base) & (uint32_t)kSPI_TxBufferEmptyFlag) != 0U)
        {
            /* Complete the transfer */
            SPI_MasterTransferAbort(base, handle);

            if (handle->callback != NULL)
            {
                (handle->callback)(base, handle, kStatus_SPI_Idle, handle->userData);
            }
        }
    }
}
/*!
 * brief Initializes the SPI slave handle.
 *
 * This function initializes the SPI slave handle which can be used for other SPI slave transactional APIs. Usually,
 * for a specified SPI instance, call this API once to get the initialized handle.
 *
 * param base SPI peripheral base address.
 * param handle SPI handle pointer.
 * param callback Callback function.
 * param userData User data.
 */
void SPI_SlaveTransferCreateHandle(SPI_Type *base,
                                   spi_slave_handle_t *handle,
                                   spi_slave_callback_t callback,
                                   void *userData)
{
    assert(handle != NULL);

    /* Slave create handle share same logic with master create handle, the only difference
    is the Isr pointer. */
    SPI_MasterTransferCreateHandle(base, handle, callback, userData);
    s_spiSlaveIsr = SPI_SlaveTransferHandleIRQ;
}

/*!
 * brief Performs a non-blocking SPI slave interrupt transfer.
 *
 * note The API returns immediately after the transfer initialization is finished.
 * Call SPI_GetStatusIRQ() to get the transfer status.
 * note If SPI transfer data frame size is 16 bits, the transfer size cannot be an odd number.
 *
 * param base SPI peripheral base address.
 * param handle pointer to spi_slave_handle_t structure which stores the transfer state
 * param xfer pointer to spi_xfer_config_t structure
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_SPI_Busy SPI is not idle, is running another transfer.
 */
status_t SPI_SlaveTransferNonBlocking(SPI_Type *base, spi_slave_handle_t *handle, spi_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));
    uint32_t mask = 0U;

    /* Check if SPI is busy */
    if (handle->state == (uint32_t)kSPI_Busy)
    {
        return (status_t)kStatus_SPI_Busy;
    }

    /* Check if the input arguments valid */
    if (((xfer->txData == NULL) && (xfer->rxData == NULL)) || (xfer->dataSize == 0U))
    {
        return (status_t)kStatus_InvalidArgument;
    }

    /* Read out any possible data */
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
    /* If instance has FIFO and FIFO is enabled. */
    if ((FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0) && ((base->C3 & SPI_C3_FIFOMODE_MASK) != 0U))
    {
        while ((SPI_GetStatusFlags(base) & (uint32_t)kSPI_RxFifoEmptyFlag) == 0U)
        {
            (void)SPI_ReadData(base);
        }
    }
    else
    {
        if ((SPI_GetStatusFlags(base) & (uint32_t)kSPI_RxBufferFullFlag) != 0U)
        {
            (void)SPI_ReadData(base);
        }
    }
#else
    if ((SPI_GetStatusFlags(base) & (uint32_t)kSPI_RxBufferFullFlag) != 0U)
    {
        (void)SPI_ReadData(base);
    }
#endif /* FSL_FEATURE_SPI_HAS_FIFO */

    /* Set the handle information */
    handle->txData           = xfer->txData;
    handle->rxData           = xfer->rxData;
    handle->transferSize     = xfer->dataSize;
    handle->txRemainingBytes = (xfer->txData == NULL) ? 0U : xfer->dataSize;
    handle->rxRemainingBytes = (xfer->rxData == NULL) ? 0U : xfer->dataSize;

    /* Set the SPI state to busy */
    handle->state = (uint32_t)kSPI_Busy;

    /* Enable Interrupt */
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO

    handle->watermark = SPI_GetWatermark(base);

    /* If the size of the transfer size less than watermark, set watermark to 1 */
    if (xfer->dataSize < (uint32_t)handle->watermark * 2U)
    {
        handle->watermark = 1U;
    }

    /* According to watermark size, enable interrupts */
    if (handle->watermark > 1U)
    {
        /* Enable Rx near full interrupt */

        if (handle->rxData != NULL)
        {
            mask |= (uint32_t)kSPI_RxFifoNearFullInterruptEnable;
        }
        /* Enable Tx near full interrupt only if there are data to send */
        if (handle->txData != NULL)
        {
            mask |= (uint32_t)kSPI_TxFifoNearEmptyInterruptEnable;
        }

        SPI_EnableFIFO(base, true);
    }
    else
    {
        /* Enable Rx full interrupt */
        if (handle->rxData != NULL)
        {
            mask |= (uint32_t)kSPI_RxFullAndModfInterruptEnable;
        }
        /* Enable Tx full interrupt only if there are data to send */
        if (handle->txData != NULL)
        {
            mask |= (uint32_t)kSPI_TxEmptyInterruptEnable;
        }

        SPI_EnableFIFO(base, false);
    }
#else
    /* Enable Rx full interrupt */
    if (handle->rxData != NULL)
    {
        mask |= (uint32_t)kSPI_RxFullAndModfInterruptEnable;
    }
    /* Enable Tx full interrupt only if there are data to send */
    if (handle->txData != NULL)
    {
        mask |= (uint32_t)kSPI_TxEmptyInterruptEnable;
    }
#endif

    SPI_EnableInterrupts(base, mask);
    return kStatus_Success;
}

/*!
 * brief Interrupts a handler for the SPI slave.
 *
 * param base SPI peripheral base address.
 * param handle pointer to spi_slave_handle_t structure which stores the transfer state
 */
void SPI_SlaveTransferHandleIRQ(SPI_Type *base, spi_slave_handle_t *handle)
{
    assert(handle != NULL);

    /* If needs to receive data, do a receive */
    if ((handle->rxRemainingBytes) != 0U)
    {
        SPI_ReceiveTransfer(base, handle);
    }

    if ((handle->txRemainingBytes) != 0U)
    {
        SPI_SendTransfer(base, handle);
#if defined(FSL_FEATURE_SPI_HAS_FIFO) && FSL_FEATURE_SPI_HAS_FIFO
        if (handle->txRemainingBytes == 0U)
        {
            SPI_DisableInterrupts(base, (uint32_t)kSPI_TxFifoNearEmptyInterruptEnable);
            SPI_EnableInterrupts(base, (uint32_t)kSPI_TxEmptyInterruptEnable);
        }
#endif
    }

    /* All the transfer finished */
    if ((handle->txRemainingBytes == 0U) && (handle->rxRemainingBytes == 0U))
    {
        if ((SPI_GetStatusFlags(base) & (uint32_t)kSPI_TxBufferEmptyFlag) != 0U)
        {
            /* Complete the transfer */
            SPI_SlaveTransferAbort(base, handle);

            if (handle->callback != NULL)
            {
                handle->callback(base, handle, kStatus_SPI_Idle, handle->userData);
            }
        }
    }
}

static void SPI_CommonIRQHandler(SPI_Type *base, uint32_t instance)
{
    if ((base->C1 & SPI_C1_MSTR_MASK) != 0U)
    {
        s_spiMasterIsr(base, s_spiHandle[instance]);
    }
    else
    {
        s_spiSlaveIsr(base, s_spiHandle[instance]);
    }
    SDK_ISR_EXIT_BARRIER;
}

#if defined(FSL_FEATURE_SPI_HAS_SHARED_IRQ0_IRQ1_IRQ2) && FSL_FEATURE_SPI_HAS_SHARED_IRQ0_IRQ1_IRQ2
void SPI0_SPI1_SPI2_DriverIRQHandler(void);
void SPI0_SPI1_SPI2_DriverIRQHandler(void)
{
    for (uint32_t instance = 0U; instance < 3U; instance++)
    {
        if (s_spiHandle[instance] != NULL)
        {
            SPI_CommonIRQHandler(s_spiBases[instance], instance);
        }
    }
}
#elif defined(FSL_FEATURE_SPI_HAS_SHARED_IRQ0_IRQ1) && FSL_FEATURE_SPI_HAS_SHARED_IRQ0_IRQ1
void SPI0_SPI1_DriverIRQHandler(void);
void SPI0_SPI1_DriverIRQHandler(void)
{
    for (uint32_t instance = 0U; instance < 2U; instance++)
    {
        if (s_spiHandle[instance] != NULL)
        {
            SPI_CommonIRQHandler(s_spiBases[instance], instance);
        }
    }
}
#else
#if defined(SPI0)
void SPI0_DriverIRQHandler(void);
void SPI0_DriverIRQHandler(void)
{
    assert(s_spiHandle[0] != NULL);
    SPI_CommonIRQHandler(SPI0, 0);
}
#endif

#if defined(SPI1)
void SPI1_DriverIRQHandler(void);
void SPI1_DriverIRQHandler(void)
{
    assert(s_spiHandle[1] != NULL);
    SPI_CommonIRQHandler(SPI1, 1);
}
#endif

#if defined(SPI2)
void SPI2_DriverIRQHandler(void);
void SPI2_DriverIRQHandler(void)
{
    assert(s_spiHandle[2] != NULL);
    SPI_CommonIRQHandler(SPI2, 2);
}
#endif
#endif
