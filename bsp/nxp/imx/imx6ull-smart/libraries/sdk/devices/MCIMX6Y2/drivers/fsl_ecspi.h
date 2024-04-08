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
#ifndef _FSL_ECSPI_H_
#define _FSL_ECSPI_H_

#include "fsl_common.h"

/*!
 * @addtogroup ecspi_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief ECSPI driver version 2.0.0. */
#define FSL_ECSPI_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

#ifndef ECSPI_DUMMYDATA
/*! @brief ECSPI dummy transfer data, the data is sent while txBuff is NULL. */
#define ECSPI_DUMMYDATA (0xFFFFFFFFU)
#endif

/*! @brief Return status for the ECSPI driver. */
enum _ecspi_status
{
    kStatus_ECSPI_Busy = MAKE_STATUS(kStatusGroup_ECSPI, 0),             /*!< ECSPI bus is busy */
    kStatus_ECSPI_Idle = MAKE_STATUS(kStatusGroup_ECSPI, 1),             /*!< ECSPI is idle */
    kStatus_ECSPI_Error = MAKE_STATUS(kStatusGroup_ECSPI, 2),            /*!< ECSPI  error */
    kStatus_ECSPI_HardwareOverFlow = MAKE_STATUS(kStatusGroup_ECSPI, 3), /*!< ECSPI  hardware overflow */
};

/*! @brief ECSPI clock polarity configuration. */
typedef enum _ecspi_clock_polarity
{
    kECSPI_PolarityActiveHigh = 0x0U, /*!< Active-high ECSPI polarity high (idles low). */
    kECSPI_PolarityActiveLow,         /*!< Active-low ECSPI polarity low (idles high). */
} ecspi_clock_polarity_t;

/*! @brief ECSPI clock phase configuration. */
typedef enum _ecspi_clock_phase
{
    kECSPI_ClockPhaseFirstEdge =
        0x0U,                    /*!< First edge on SPSCK occurs at the middle of the first cycle of a data transfer. */
    kECSPI_ClockPhaseSecondEdge, /*!< First edge on SPSCK occurs at the start of the first cycle of a data transfer. */
} ecspi_clock_phase_t;

/*! @brief ECSPI interrupt sources. */
enum _ecspi_interrupt_enable
{
    kECSPI_TxfifoEmptyInterruptEnable = ECSPI_INTREG_TEEN_MASK,       /*!< Transmit FIFO buffer empty interrupt */
    kECSPI_TxFifoDataRequstInterruptEnable = ECSPI_INTREG_TDREN_MASK, /*!< Transmit FIFO data requst interrupt */
    kECSPI_TxFifoFullInterruptEnable = ECSPI_INTREG_TFEN_MASK,        /*!< Transmit FIFO full interrupt */
    kECSPI_RxFifoReadyInterruptEnable = ECSPI_INTREG_RREN_MASK,       /*!< Receiver FIFO ready interrupt */
    kECSPI_RxFifoDataRequstInterruptEnable = ECSPI_INTREG_RDREN_MASK, /*!< Receiver FIFO data requst interrupt */
    kECSPI_RxFifoFullInterruptEnable = ECSPI_INTREG_RFEN_MASK,        /*!< Receiver FIFO full interrupt */
    kECSPI_RxFifoOverFlowInterruptEnable = ECSPI_INTREG_ROEN_MASK,    /*!< Receiver FIFO buffer overflow interrupt */
    kECSPI_TransferCompleteInterruptEnable = ECSPI_INTREG_TCEN_MASK,  /*!< Transfer complete interrupt */
    kECSPI_AllInterruptEnable = (ECSPI_INTREG_TEEN_MASK | ECSPI_INTREG_TDREN_MASK | ECSPI_INTREG_TFEN_MASK |
                                 ECSPI_INTREG_RREN_MASK | ECSPI_INTREG_RDREN_MASK | ECSPI_INTREG_RFEN_MASK |
                                 ECSPI_INTREG_ROEN_MASK | ECSPI_INTREG_TCEN_MASK), /*!< All interrupt */
};

/*! @brief ECSPI status flags. */
enum _ecspi_flags
{
    kECSPI_TxfifoEmptyFlag = ECSPI_STATREG_TE_MASK,       /*!< Transmit FIFO buffer empty flag */
    kECSPI_TxFifoDataRequstFlag = ECSPI_STATREG_TDR_MASK, /*!< Transmit FIFO data requst flag */
    kECSPI_TxFifoFullFlag = ECSPI_STATREG_TF_MASK,        /*!< Transmit FIFO full flag */
    kECSPI_RxFifoReadyFlag = ECSPI_STATREG_RR_MASK,       /*!< Receiver FIFO ready flag */
    kECSPI_RxFifoDataRequstFlag = ECSPI_STATREG_RDR_MASK, /*!< Receiver FIFO data requst flag */
    kECSPI_RxFifoFullFlag = ECSPI_STATREG_RF_MASK,        /*!< Receiver FIFO full flag */
    kECSPI_RxFifoOverFlowFlag = ECSPI_STATREG_RO_MASK,    /*!< Receiver FIFO buffer overflow flag */
    kECSPI_TransferCompleteFlag = ECSPI_STATREG_TC_MASK,  /*!< Transfer complete flag */
};
/*! @brief ECSPI DMA enable.*/
enum _ecspi_dma_enable_t
{
    kECSPI_TxDmaEnable = ECSPI_DMAREG_TEDEN_MASK,                             /*!< Tx DMA request source */
    kECSPI_RxDmaEnable = ECSPI_DMAREG_RXDEN_MASK,                             /*!< Rx DMA request source */
    kECSPI_DmaAllEnable = (ECSPI_DMAREG_TEDEN_MASK | ECSPI_DMAREG_RXDEN_MASK) /*!< All DMA request source*/
};

/*! @brief ECSPI SPI_RDY signal configuration. */
typedef enum _ecspi_data_ready
{
    kECSPI_DataReadyIgnore = 0x0U, /*!< SPI_RDY signal is ignored */
    kECSPI_DataReadyFallingEdge,   /*!< SPI_RDY signal will be triggerd by the falling edge */
    kECSPI_DataReadyLowLevel,      /*!< SPI_RDY signal will be triggerd by a low level */
} ecspi_Data_ready_t;

/*! @brief ECSPI channel select source. */
typedef enum _ecspi_channel_source
{
    kECSPI_Channel0 = 0x0U, /*!< Channel 0 is selectd */
    kECSPI_Channel1,        /*!< Channel 1 is selectd */
    kECSPI_Channel2,        /*!< Channel 2 is selectd */
    kECSPI_Channel3,        /*!< Channel 3 is selectd */
} ecspi_channel_source_t;

/*! @brief ECSPI master or slave mode configuration. */
typedef enum _ecspi_master_slave_mode
{
    kECSPI_Slave = 0U, /*!< ECSPI peripheral operates in slave mode.*/
    kECSPI_Master,     /*!< ECSPI peripheral operates in master mode.*/
} ecspi_master_slave_mode_t;

/*! @brief ECSPI data line inactive state configuration. */
typedef enum _ecspi_data_line_inactive_state_t
{
    kECSPI_DataLineInactiveStateHigh = 0x0U, /*!< The data line inactive state stays high. */
    kECSPI_DataLineInactiveStateLow,         /*!< The data line inactive state stays low. */
} ecspi_data_line_inactive_state_t;

/*! @brief ECSPI clock inactive state configuration. */
typedef enum _ecspi_clock_inactive_state_t
{
    kECSPI_ClockInactiveStateLow = 0x0U, /*!< The SCLK inactive state stays low. */
    kECSPI_ClockInactiveStateHigh,       /*!< The SCLK inactive state stays high. */
} ecspi_clock_inactive_state_t;

/*! @brief ECSPI active state configuration.*/
typedef enum _ecspi_chip_select_active_state_t
{
    kECSPI_ChipSelectActiveStateLow = 0x0U, /*!< The SS signal line active stays low. */
    kECSPI_ChipSelectActiveStateHigh,       /*!< The SS signal line active stays high. */
} ecspi_chip_select_active_state_t;

/*! @brief ECSPI wave form configuration.*/
typedef enum _ecspi_wave_form_t
{
    kECSPI_WaveFormSingle = 0x0U, /*!< The wave form for signal burst */
    kECSPI_WaveFormMultiple,      /*!< The wave form for multiple burst */
} ecspi_wave_form_t;

/*! @brief ECSPI sample period clock configuration.*/
typedef enum _ecspi_sample_period_clock_source
{
    kECSPI_spiClock = 0x0U, /*!< The sample period clock source is SCLK. */
    kECSPI_lowFreqClock,    /*!< The sample seriod clock source is low_frequency reference clock(32.768 kHz). */
} ecspi_sample_period_clock_source_t;

/*! @brief ECSPI user channel configure structure.*/
typedef struct _ecspi_channel_config
{
    ecspi_master_slave_mode_t channelMode;                  /*!< Channel mode */
    ecspi_clock_inactive_state_t clockInactiveState;        /*!< Clock line (SCLK) inactive state */
    ecspi_data_line_inactive_state_t dataLineInactiveState; /*!< Data line (MOSI&MISO) inactive state */
    ecspi_chip_select_active_state_t chipSlectActiveState;  /*!< Chip select(SS) line active state */
    ecspi_wave_form_t waveForm;                             /*!< Wave form */
    ecspi_clock_polarity_t polarity;                        /*!< Clock polarity */
    ecspi_clock_phase_t phase;                              /*!< Clock phase */
} ecspi_channel_config_t;

/*! @brief ECSPI master configure structure.*/
typedef struct _ecspi_master_config
{
    ecspi_channel_source_t channel;                       /*!< Channel number */
    ecspi_channel_config_t channelConfig;                 /*!< Channel configuration */
    ecspi_sample_period_clock_source_t samplePeriodClock; /*!< Sample period clock source */

    uint8_t burstLength;     /*!< Burst length */
    uint8_t chipSelectDelay; /*!< SS delay time */
    uint16_t samplePeriod;   /*!< Sample period */
    uint8_t txFifoThreshold; /*!< TX Threshold */
    uint8_t rxFifoThreshold; /*!< RX Threshold */
    uint32_t baudRate_Bps;   /*!< ECSPI baud rate for master mode */
} ecspi_master_config_t;

/*! @brief ECSPI slave configure structure.*/
typedef struct _ecspi_slave_config
{
    ecspi_channel_source_t channel;       /*Channel number */
    uint8_t burstLength;                  /*!< Burst length */
    uint8_t txFifoThreshold;              /*!< TX Threshold */
    uint8_t rxFifoThreshold;              /*!< RX Threshold */
    ecspi_channel_config_t channelConfig; /*!< Channel configuration */
} ecspi_slave_config_t;

/*! @brief ECSPI transfer structure */
typedef struct _ecspi_transfer
{
    uint32_t *txData;               /*!< Send buffer */
    uint32_t *rxData;               /*!< Receive buffer */
    size_t dataSize;                /*!< Transfer bytes */
    ecspi_channel_source_t channel; /*!< ECSPI channel select */
} ecspi_transfer_t;

typedef struct _ecspi_master_handle ecspi_master_handle_t;
/*! @brief  Slave handle is the same with master handle  */
typedef ecspi_master_handle_t ecspi_slave_handle_t;

/*! @brief ECSPI master callback for finished transmit */
typedef void (*ecspi_master_callback_t)(ECSPI_Type *base,
                                        ecspi_master_handle_t *handle,
                                        status_t status,
                                        void *userData);

/*! @brief ECSPI slave callback for finished transmit */
typedef void (*ecspi_slave_callback_t)(ECSPI_Type *base, ecspi_slave_handle_t *handle, status_t status, void *userData);

/*! @brief ECSPI master handle structure */
struct _ecspi_master_handle
{
    ecspi_channel_source_t channel;   /*!< Channel number */
    uint32_t *volatile txData;        /*!< Transfer buffer */
    uint32_t *volatile rxData;        /*!< Receive buffer */
    volatile size_t txRemainingBytes; /*!< Send data remaining in bytes */
    volatile size_t rxRemainingBytes; /*!< Receive data remaining in bytes */
    volatile uint32_t state;          /*!< ECSPI internal state */
    size_t transferSize;              /*!< Bytes to be transferred */
    ecspi_master_callback_t callback; /*!< ECSPI callback */
    void *userData;                   /*!< Callback parameter */
};

#if defined(__cplusplus)
extern "C" {
#endif
/*******************************************************************************
 * APIs
 ******************************************************************************/
/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief  Sets the ECSPI configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in ECSPI_MasterInit().
 * User may use the initialized structure unchanged in ECSPI_MasterInit, or modify
 * some fields of the structure before calling ECSPI_MasterInit. After calling this API,
 * the master is ready to transfer.
 * Example:
   @code
   ecspi_master_config_t config;
   ECSPI_MasterGetDefaultConfig(&config);
   @endcode
 *
 * @param config pointer to config structure
 */
void ECSPI_MasterGetDefaultConfig(ecspi_master_config_t *config);

/*!
 * @brief Initializes the ECSPI with configuration.
 *
 * The configuration structure can be filled by user from scratch, or be set with default
 * values by ECSPI_MasterGetDefaultConfig(). After calling this API, the slave is ready to transfer.
 * Example
   @code
   ecspi_master_config_t config = {
   .baudRate_Bps = 400000,
   ...
   };
   ECSPI_MasterInit(ECSPI0, &config);
   @endcode
 *
 * @param base ECSPI base pointer
 * @param config pointer to master configuration structure
 * @param srcClock_Hz Source clock frequency.
 */
void ECSPI_MasterInit(ECSPI_Type *base, const ecspi_master_config_t *config, uint32_t srcClock_Hz);

/*!
 * @brief  Sets the ECSPI configuration structure to default values.
 *
 * The purpose of this API is to get the configuration structure initialized for use in ECSPI_SlaveInit().
 * User may use the initialized structure unchanged in ECSPI_SlaveInit(), or modify
 * some fields of the structure before calling ECSPI_SlaveInit(). After calling this API,
 * the master is ready to transfer.
 * Example:
   @code
   ecspi_Slaveconfig_t config;
   ECSPI_SlaveGetDefaultConfig(&config);
   @endcode
 *
 * @param config pointer to config structure
 */
void ECSPI_SlaveGetDefaultConfig(ecspi_slave_config_t *config);

/*!
 * @brief Initializes the ECSPI with configuration.
 *
 * The configuration structure can be filled by user from scratch, or be set with default
 * values by ECSPI_SlaveGetDefaultConfig(). After calling this API, the slave is ready to transfer.
 * Example
   @code
   ecspi_Salveconfig_t config = {
   .baudRate_Bps = 400000,
   ...
   };
   ECSPI_SlaveInit(ECSPI1, &config);
   @endcode
 *
 * @param base ECSPI base pointer
 * @param config pointer to master configuration structure
 */
void ECSPI_SlaveInit(ECSPI_Type *base, const ecspi_slave_config_t *config);

/*!
 * @brief De-initializes the ECSPI.
 *
 * Calling this API resets the ECSPI module, gates the ECSPI clock.
 * The ECSPI module can't work unless calling the ECSPI_MasterInit/ECSPI_SlaveInit to initialize module.
 *
 * @param base ECSPI base pointer
 */
void ECSPI_Deinit(ECSPI_Type *base);

/*!
 * @brief Enables or disables the ECSPI.
 *
 * @param base ECSPI base pointer
 * @param enable pass true to enable module, false to disable module
 */
static inline void ECSPI_Enable(ECSPI_Type *base, bool enable)
{
    if (enable)
    {
        base->CONREG |= ECSPI_CONREG_EN_MASK;
    }
    else
    {
        base->CONREG &= ~ECSPI_CONREG_EN_MASK;
    }
}
/*! @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the status flag.
 *
 * @param base ECSPI base pointer
 * @return ECSPI Status, use status flag to AND #_ecspi_flags could get the related status.
 */
static inline uint32_t ECSPI_GetStatusFlags(ECSPI_Type *base)
{
    return (base->STATREG);
}

/*!
 * @brief Clear the status flag.
 *
 * @param base ECSPI base pointer
 * @param mask ECSPI Status, use status flag to AND #_ecspi_flags could get the related status.
 */
static inline void ECSPI_ClearStatusFlags(ECSPI_Type *base, uint32_t mask)
{
    base->STATREG |= mask;
}
/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables the interrupt for the ECSPI.
 *
 * @param base ECSPI base pointer
 * @param mask ECSPI interrupt source. The parameter can be any combination of the following values:
 *        @arg kECSPI_TxfifoEmptyInterruptEnable
 *        @arg kECSPI_TxFifoDataRequstInterruptEnable
 *        @arg kECSPI_TxFifoFullInterruptEnable
 *        @arg kECSPI_RxFifoReadyInterruptEnable
 *        @arg kECSPI_RxFifoDataRequstInterruptEnable
 *        @arg kECSPI_RxFifoFullInterruptEnable
 *        @arg kECSPI_RxFifoOverFlowInterruptEnable
 *        @arg kECSPI_TransferCompleteInterruptEnable
 *        @arg kECSPI_AllInterruptEnable
 */
static inline void ECSPI_EnableInterrupts(ECSPI_Type *base, uint32_t mask)
{
    base->INTREG |= mask;
}

/*!
 * @brief Disables the interrupt for the ECSPI.
 *
 * @param base ECSPI base pointer
 * @param mask ECSPI interrupt source. The parameter can be any combination of the following values:
 *        @arg kECSPI_TxfifoEmptyInterruptEnable
 *        @arg kECSPI_TxFifoDataRequstInterruptEnable
 *        @arg kECSPI_TxFifoFullInterruptEnable
 *        @arg kECSPI_RxFifoReadyInterruptEnable
 *        @arg kECSPI_RxFifoDataRequstInterruptEnable
 *        @arg kECSPI_RxFifoFullInterruptEnable
 *        @arg kECSPI_RxFifoOverFlowInterruptEnable
 *        @arg kECSPI_TransferCompleteInterruptEnable
 *        @arg kECSPI_AllInterruptEnable
 */
static inline void ECSPI_DisableInterrupts(ECSPI_Type *base, uint32_t mask)
{
    base->INTREG &= ~(mask);
}
/*! @} */

/*!
 * @name Software Reset
 * @{
 */

/*!
 * @brief Software reset.
 *
 * @param base ECSPI base pointer
 */
static inline void ECSPI_SoftwareReset(ECSPI_Type *base)
{
    /* Disables the block and resets the internal logic with the exception of the ECSPI control register */
    base->CONREG &= ~ECSPI_CONREG_EN_MASK;
    /* Software reset can not reset the control register, so clear the control register manually */
    base->CONREG = 0x0U;
}
/*! @} */

/*!
 * @name Channel mode check
 * @{
 */

/*!
 * @brief Mode check
 *
 * @param base ECSPI base pointer
 * @param channel ECSPI channel source
 * @return mode of channel
 */
static inline bool ECSPI_IsMaster(ECSPI_Type *base, ecspi_channel_source_t channel)
{
    return (bool)(((base->CONREG & ECSPI_CONREG_CHANNEL_MODE_MASK) >> (ECSPI_CONREG_CHANNEL_MODE_SHIFT + channel)) &
                  0x1U);
}
/*! @} */

/*!
 * @name DMA Control
 * @{
 */

/*!
 * @brief Enables the DMA source for ECSPI.
 *
 * @param base ECSPI base pointer
 * @param source ECSPI DMA source.
 * @param enable True means enable DMA, false means disable DMA
 */
static inline void ECSPI_EnableDMA(ECSPI_Type *base, uint32_t mask, bool enable)
{
    if (enable)
    {
        base->DMAREG |= mask;
    }
    else
    {
        base->DMAREG &= ~mask;
    }
}
/*! @} */

/*!
 * @name FIFO Operation
 * @{
 */

/*!
 * @brief Get the Tx FIFO data count.
 *
 * @param base ECSPI base pointer.
 * @return the number of words in Tx FIFO buffer.
 */
static inline uint8_t ECSPI_GetTxFifoCount(ECSPI_Type *base)
{
    return (uint8_t)((base->TESTREG & ECSPI_TESTREG_TXCNT_MASK) >> ECSPI_TESTREG_TXCNT_SHIFT);
}

/*!
 * @brief Get the Rx FIFO data count.
 *
 * @param base ECSPI base pointer.
 * @return the number of words in Rx FIFO buffer.
 */
static inline uint8_t ECSPI_GetRxFifoCount(ECSPI_Type *base)
{
    return (uint8_t)((base->TESTREG & ECSPI_TESTREG_RXCNT_MASK) >> ECSPI_TESTREG_RXCNT_SHIFT);
}
/*! @} */

/*!
 * @name Bus Operations
 * @{
 */

/*!
 * @brief Set channel select for transfer.
 *
 * @param base ECSPI base pointer
 * @param channel Channel source.
 */
static inline void ECSPI_SetChannelSelect(ECSPI_Type *base, ecspi_channel_source_t channel)
{
    /* Clear Channel select bits in CONREG register */
    uint32_t temp = base->CONREG & (~(ECSPI_CONREG_CHANNEL_SELECT_MASK));
    /* Set channel select bits */
    base->CONREG = (temp | ECSPI_CONREG_CHANNEL_SELECT(channel));
}
/*!
 * @brief Set channel select configuration for transfer.
 *
 * The purpose of this API is to set the channel will be use to transfer.
 * User may use this API after instance has been initialized or before transfer start.
 * The configuration structure #_ecspi_channel_config_ can be filled by user from scratch.
 * After calling this API, user can select this channel as transfer channel.
 *
 * @param base ECSPI base pointer
 * @param channel Channel source.
 * @param config Configuration struct of channel
 */
void ECSPI_SetChannelConfig(ECSPI_Type *base, ecspi_channel_source_t channel, const ecspi_channel_config_t *config);

/*!
 * @brief Sets the baud rate for ECSPI transfer. This is only used in master.
 *
 * @param base ECSPI base pointer
 * @param baudRate_Bps baud rate needed in Hz.
 * @param srcClock_Hz ECSPI source clock frequency in Hz.
 */
void ECSPI_SetBaudRate(ECSPI_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz);

/*!
 * @brief Sends a buffer of data bytes using a blocking method.
 *
 * @note This function blocks via polling until all bytes have been sent.
 *
 * @param base ECSPI base pointer
 * @param buffer The data bytes to send
 * @param size The number of data bytes to send
 */
void ECSPI_WriteBlocking(ECSPI_Type *base, uint32_t *buffer, size_t size);

/*!
 * @brief Writes a data into the ECSPI data register.
 *
 * @param base ECSPI base pointer
 * @param data Data needs to be write.
 */
static inline void ECSPI_WriteData(ECSPI_Type *base, uint32_t data)
{
    base->TXDATA = data;
}

/*!
 * @brief Gets a data from the ECSPI data register.
 *
 * @param base ECSPI base pointer
 * @return Data in the register.
 */
static inline uint32_t ECSPI_ReadData(ECSPI_Type *base)
{
    return (uint32_t)(base->RXDATA);
}
/*! @} */

/*!
 * @name Transactional
 * @{
 */
/*!
 * @brief Initializes the ECSPI master handle.
 *
 * This function initializes the ECSPI master handle which can be used for other ECSPI master transactional APIs.
 * Usually,
 * for a specified ECSPI instance, call this API once to get the initialized handle.
 *
 * @param base ECSPI peripheral base address.
 * @param handle ECSPI handle pointer.
 * @param callback Callback function.
 * @param userData User data.
 */
void ECSPI_MasterTransferCreateHandle(ECSPI_Type *base,
                                      ecspi_master_handle_t *handle,
                                      ecspi_master_callback_t callback,
                                      void *userData);

/*!
 * @brief Transfers a block of data using a polling method.
 *
 * @param base SPI base pointer
 * @param xfer pointer to spi_xfer_config_t structure
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 */
status_t ECSPI_MasterTransferBlocking(ECSPI_Type *base, ecspi_transfer_t *xfer);

/*!
 * @brief Performs a non-blocking ECSPI interrupt transfer.
 *
 * @note The API immediately returns after transfer initialization is finished.
 * @note If ECSPI transfer data frame size is 16 bits, the transfer size cannot be an odd number.
 *
 * @param base ECSPI peripheral base address.
 * @param handle pointer to ecspi_master_handle_t structure which stores the transfer state
 * @param xfer pointer to ecspi_transfer_t structure
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_ECSPI_Busy ECSPI is not idle, is running another transfer.
 */
status_t ECSPI_MasterTransferNonBlocking(ECSPI_Type *base, ecspi_master_handle_t *handle, ecspi_transfer_t *xfer);

/*!
 * @brief Gets the bytes of the ECSPI interrupt transferred.
 *
 * @param base ECSPI peripheral base address.
 * @param handle Pointer to ECSPI transfer handle, this should be a static variable.
 * @param count Transferred bytes of ECSPI master.
 * @retval kStatus_ECSPI_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t ECSPI_MasterTransferGetCount(ECSPI_Type *base, ecspi_master_handle_t *handle, size_t *count);

/*!
 * @brief Aborts an ECSPI transfer using interrupt.
 *
 * @param base ECSPI peripheral base address.
 * @param handle Pointer to ECSPI transfer handle, this should be a static variable.
 */
void ECSPI_MasterTransferAbort(ECSPI_Type *base, ecspi_master_handle_t *handle);

/*!
 * @brief Interrupts the handler for the ECSPI.
 *
 * @param base ECSPI peripheral base address.
 * @param handle pointer to ecspi_master_handle_t structure which stores the transfer state.
 */
void ECSPI_MasterTransferHandleIRQ(ECSPI_Type *base, ecspi_master_handle_t *handle);

/*!
 * @brief Initializes the ECSPI slave handle.
 *
 * This function initializes the ECSPI slave handle which can be used for other ECSPI slave transactional APIs. Usually,
 * for a specified ECSPI instance, call this API once to get the initialized handle.
 *
 * @param base ECSPI peripheral base address.
 * @param handle ECSPI handle pointer.
 * @param callback Callback function.
 * @param userData User data.
 */
void ECSPI_SlaveTransferCreateHandle(ECSPI_Type *base,
                                     ecspi_slave_handle_t *handle,
                                     ecspi_slave_callback_t callback,
                                     void *userData);

/*!
 * @brief Performs a non-blocking ECSPI slave interrupt transfer.
 *
 * @note The API returns immediately after the transfer initialization is finished.
 *
 * @param base ECSPI peripheral base address.
 * @param handle pointer to ecspi_master_handle_t structure which stores the transfer state
 * @param xfer pointer to ecspi_transfer_t structure
 * @retval kStatus_Success Successfully start a transfer.
 * @retval kStatus_InvalidArgument Input argument is invalid.
 * @retval kStatus_ECSPI_Busy ECSPI is not idle, is running another transfer.
 */
static inline status_t ECSPI_SlaveTransferNonBlocking(ECSPI_Type *base,
                                                      ecspi_slave_handle_t *handle,
                                                      ecspi_transfer_t *xfer)
{
    return ECSPI_MasterTransferNonBlocking(base, handle, xfer);
}

/*!
 * @brief Gets the bytes of the ECSPI interrupt transferred.
 *
 * @param base ECSPI peripheral base address.
 * @param handle Pointer to ECSPI transfer handle, this should be a static variable.
 * @param count Transferred bytes of ECSPI slave.
 * @retval kStatus_ECSPI_Success Succeed get the transfer count.
 * @retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
static inline status_t ECSPI_SlaveTransferGetCount(ECSPI_Type *base, ecspi_slave_handle_t *handle, size_t *count)
{
    return ECSPI_MasterTransferGetCount(base, handle, count);
}

/*!
 * @brief Aborts an ECSPI slave transfer using interrupt.
 *
 * @param base ECSPI peripheral base address.
 * @param handle Pointer to ECSPI transfer handle, this should be a static variable.
 */
static inline void ECSPI_SlaveTransferAbort(ECSPI_Type *base, ecspi_slave_handle_t *handle)
{
    ECSPI_MasterTransferAbort(base, handle);
}

/*!
 * @brief Interrupts a handler for the ECSPI slave.
 *
 * @param base ECSPI peripheral base address.
 * @param handle pointer to ecspi_slave_handle_t structure which stores the transfer state
 */
void ECSPI_SlaveTransferHandleIRQ(ECSPI_Type *base, ecspi_slave_handle_t *handle);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _FSL_ECSPI_H_*/
