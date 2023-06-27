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

#ifndef _FSL_UART_H_
#define _FSL_UART_H_

#include "fsl_common.h"

/*!
 * @addtogroup uart_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @name Driver version */
/*@{*/
/*! @brief UART driver version 2.0.0. */
#define FSL_UART_DRIVER_VERSION (MAKE_VERSION(2, 0, 0))
/*@}*/

/*! @brief Error codes for the UART driver. */
enum _uart_status
{
    kStatus_UART_TxBusy = MAKE_STATUS(kStatusGroup_IUART, 0),              /*!< Transmitter is busy. */
    kStatus_UART_RxBusy = MAKE_STATUS(kStatusGroup_IUART, 1),              /*!< Receiver is busy. */
    kStatus_UART_TxIdle = MAKE_STATUS(kStatusGroup_IUART, 2),              /*!< UART transmitter is idle. */
    kStatus_UART_RxIdle = MAKE_STATUS(kStatusGroup_IUART, 3),              /*!< UART receiver is idle. */
    kStatus_UART_TxWatermarkTooLarge = MAKE_STATUS(kStatusGroup_IUART, 4), /*!< TX FIFO watermark too large  */
    kStatus_UART_RxWatermarkTooLarge = MAKE_STATUS(kStatusGroup_IUART, 5), /*!< RX FIFO watermark too large  */
    kStatus_UART_FlagCannotClearManually =
        MAKE_STATUS(kStatusGroup_IUART, 6),                                /*!< UART flag can't be manually cleared. */
    kStatus_UART_Error = MAKE_STATUS(kStatusGroup_IUART, 7),               /*!< Error happens on UART. */
    kStatus_UART_RxRingBufferOverrun = MAKE_STATUS(kStatusGroup_IUART, 8), /*!< UART RX software ring buffer overrun. */
    kStatus_UART_RxHardwareOverrun = MAKE_STATUS(kStatusGroup_IUART, 9),   /*!< UART RX receiver overrun. */
    kStatus_UART_NoiseError = MAKE_STATUS(kStatusGroup_IUART, 10),         /*!< UART noise error. */
    kStatus_UART_FramingError = MAKE_STATUS(kStatusGroup_IUART, 11),       /*!< UART framing error. */
    kStatus_UART_ParityError = MAKE_STATUS(kStatusGroup_IUART, 12),        /*!< UART parity error. */
    kStatus_UART_BaudrateNotSupport =
        MAKE_STATUS(kStatusGroup_IUART, 13), /*!< Baudrate is not support in current clock source */
    kStatus_UART_BreakDetect = MAKE_STATUS(kStatusGroup_IUART, 14), /*!< Receiver detect BREAK signal */
};

/*! @brief UART data bits count. */
typedef enum _uart_data_bits
{
    kUART_SevenDataBits = 0x0U, /*!< Seven data bit */
    kUART_EightDataBits = 0x1U, /*!< Eight data bit */
} uart_data_bits_t;

/*! @brief UART parity mode. */
typedef enum _uart_parity_mode
{
    kUART_ParityDisabled = 0x0U, /*!< Parity disabled */
    kUART_ParityEven = 0x2U,     /*!< Even error check is selected */
    kUART_ParityOdd = 0x3U,      /*!< Odd error check is selected */
} uart_parity_mode_t;

/*! @brief UART stop bit count. */
typedef enum _uart_stop_bit_count
{
    kUART_OneStopBit = 0x0U, /*!< One stop bit */
    kUART_TwoStopBit = 0x1U, /*!< Two stop bits */
} uart_stop_bit_count_t;

/*! @brief This structure contains the settings for all of the UART interrupt configurations. */
enum _uart_interrupt_enable
{
    kUART_AutoBaudEnable = 0x1U,            /* !< Automatic baud rate detection Interrupt Enable. */
    kUART_TxReadyEnable = (0X1U << 1),      /* !< transmitter ready Interrupt Enable. */
    kUART_IdleEnable = (0x1U << 2),         /* !< IDLE Interrupt Enable. */
    kUART_RxReadyEnable = (0x1U << 3),      /* !< Receiver Ready Interrupt Enable. */
    kUART_TxEmptyEnable = (0x1U << 4),      /* !< Transmitter Empty Interrupt Enable. */
    kUART_RtsDeltaEnable = (0x1U << 5),     /* !< RTS Delta Interrupt Enable. */
    kUART_EscapeEnable = (0x1U << 8),       /* !< Escape Sequence Interrupt Enable. */
    kUART_RtsEnable = (0x1U << 9),          /* !< Request to Send Interrupt Enable. */
    kUART_AgingTimerEnable = (0x1U << 10),  /* !< Aging Timer Interrupt Enable. */
    kUART_DtrEnable = (0x1U << 12),         /* !< Data Terminal Ready Interrupt Enable. */
    kUART_ParityErrorEnable = (0x1U << 13), /* !< Parity Error Interrupt Enable.  */
    kUART_FrameErrorEnable = (0x1U << 14),  /* !< Frame Error Interrupt Enable. */
    kUART_DcdEnable = (0x1U << 15),         /* !< Data Carrier Detect Interrupt Enable. */
    kUART_RiEnable = (0x1U << 16),          /* !< Ring Indicator Interrupt Enable. */
    kUART_RxDsEnable = (0x1U << 17),        /* !< Receive Status Interrupt Enable. */
    kUART_tAirWakeEnable = (0x1U << 18),    /* !< Asynchronous IR WAKE Interrupt Enable. */
    kUART_AwakeEnable = (0x1U << 19),       /* !< Asynchronous WAKE Interrupt Enable. */
    kUART_DtrDeltaEnable = (0x1U << 20),    /* !< Data Terminal Ready Delta Interrupt Enable. */
    kUART_AutoBaudCntEnable = (0x1U << 21), /* !< Auto-baud Counter Interrupt Enable. */
    kUART_IrEnable = (0X1U << 24),          /* !< Serial Infrared Interrupt Enable. */
    kUART_WakeEnable = (0X1U << 25),        /* !< WAKE Interrupt Enable. */
    kUART_TxCompleteEnable = (0X1U << 26),  /* !< TransmitComplete Interrupt Enable. */
    kUART_BreakDetectEnable = (0X1U << 27), /* !< BREAK Condition Detected Interrupt Enable. */
    kUART_RxOverrunEnable = (0X1U << 28),   /* !< Receiver Overrun Interrupt Enable. */
    kUART_RxDataReadyEnable = (0X1U << 29), /* !< Receive Data Ready Interrupt Enable. */
    kUART_AllInterruptsEnable = kUART_AutoBaudEnable | kUART_TxReadyEnable | kUART_IdleEnable | kUART_RxReadyEnable |
                                kUART_TxEmptyEnable | kUART_RtsDeltaEnable | kUART_EscapeEnable | kUART_RtsEnable |
                                kUART_AgingTimerEnable | kUART_DtrEnable | kUART_ParityErrorEnable |
                                kUART_FrameErrorEnable | kUART_DcdEnable | kUART_RiEnable | kUART_RxDsEnable |
                                kUART_tAirWakeEnable | kUART_AwakeEnable | kUART_DtrDeltaEnable |
                                kUART_AutoBaudCntEnable | kUART_IrEnable | kUART_WakeEnable | kUART_TxCompleteEnable |
                                kUART_BreakDetectEnable | kUART_RxOverrunEnable | kUART_RxDataReadyEnable,
};

/*!
 * @brief UART status flags.
 *
 * This provides constants for the UART status flags for use in the UART functions.
 */
enum _uart_flags
{
    kUART_RxCharReadyFlag = 0x0000000FU,         /*!< Rx Character Ready Flag. */
    kUART_RxErrorFlag = 0x0000000EU,             /*!< Rx Error Detect Flag. */
    kUART_RxOverrunErrorFlag = 0x0000000DU,      /*!< Rx Overrun Flag. */
    kUART_RxFrameErrorFlag = 0x0000000CU,        /*!< Rx Frame Error Flag. */
    kUART_RxBreakDetectFlag = 0x0000000BU,       /*!< Rx Break Detect Flag. */
    kUART_RxParityErrorFlag = 0x0000000AU,       /*!< Rx Parity Error Flag. */
    kUART_ParityErrorFlag = 0x0094000FU,         /*!< Parity Error Interrupt Flag. */
    kUART_RtsStatusFlag = 0x0094000EU,           /*!< RTS_B Pin Status Flag. */
    kUART_TxReadyFlag = 0x0094000DU,             /*!< Transmitter Ready Interrupt/DMA Flag. */
    kUART_RtsDeltaFlag = 0x0094000CU,            /*!< RTS Delta Flag. */
    kUART_EscapeFlag = 0x0094000BU,              /*!< Escape Sequence Interrupt Flag. */
    kUART_FrameErrorFlag = 0x0094000AU,          /*!< Frame Error Interrupt Flag. */
    kUART_RxReadyFlag = 0x00940009U,             /*!< Receiver Ready Interrupt/DMA Flag. */
    kUART_AgingTimerFlag = 0x00940008U,          /*!< Aging Timer Interrupt Flag. */
    kUART_DtrDeltaFlag = 0x00940007U,            /*!< DTR Delta Flag. */
    kUART_RxDsFlag = 0x00940006U,                /*!< Receiver IDLE Interrupt Flag. */
    kUART_tAirWakeFlag = 0x00940005U,            /*!< Asynchronous IR WAKE Interrupt Flag. */
    kUART_AwakeFlag = 0x00940004U,               /*!< Asynchronous WAKE Interrupt Flag. */
    kUART_Rs485SlaveAddrMatchFlag = 0x00940003U, /*!< RS-485 Slave Address Detected Interrupt Flag. */
    kUART_AutoBaudFlag = 0x0098000FU,            /*!< Automatic Baud Rate Detect Complete Flag. */
    kUART_TxEmptyFlag = 0x0098000EU,             /*!< Transmit Buffer FIFO Empty. */
    kUART_DtrFlag = 0x0098000DU,                 /*!< DTR edge triggered interrupt flag. */
    kUART_IdleFlag = 0x0098000CU,                /*!< Idle Condition Flag. */
    kUART_AutoBaudCntStopFlag = 0x0098000BU,     /*!< Auto-baud Counter Stopped Flag. */
    kUART_RiDeltaFlag = 0x0098000AU,             /*!< Ring Indicator Delta Flag. */
    kUART_RiFlag = 0x00980009U,                  /*!< Ring Indicator Input Flag. */
    kUART_IrFlag = 0x00980008U,                  /*!< Serial Infrared Interrupt Flag. */
    kUART_WakeFlag = 0x00980007U,                /*!< Wake Flag. */
    kUART_DcdDeltaFlag = 0x00980006U,            /*!< Data Carrier Detect Delta Flag. */
    kUART_DcdFlag = 0x00980005U,                 /*!< Data Carrier Detect Input Flag. */
    kUART_RtsFlag = 0x00980004U,                 /*!< RTS Edge Triggered Interrupt Flag. */
    kUART_TxCompleteFlag = 0x00980003U,          /*!< Transmitter Complete Flag. */
    kUART_BreakDetectFlag = 0x00980002U,         /*!< BREAK Condition Detected Flag. */
    kUART_RxOverrunFlag = 0x00980001U,           /*!< Overrun Error Flag. */
    kUART_RxDataReadyFlag = 0x00980000U,         /*!< Receive Data Ready Flag. */
};

/*! @brief UART configuration structure. */
typedef struct _uart_config
{
    uint32_t baudRate_Bps;              /*!< UART baud rate. */
    uart_parity_mode_t parityMode;      /*!< Parity error check mode of this module. */
    uart_data_bits_t dataBitsCount;     /*!< Data bits count, eight (default), seven */
    uart_stop_bit_count_t stopBitCount; /*!< Number of stop bits in one frame. */
    uint8_t txFifoWatermark;            /*!< TX FIFO watermark */
    uint8_t rxFifoWatermark;            /*!< RX FIFO watermark */
    bool enableAutoBaudRate;            /*!< Enable automatic baud rate detection */
    bool enableTx;                      /*!< Enable TX */
    bool enableRx;                      /*!< Enable RX */
} uart_config_t;

/*! @brief UART transfer structure. */
typedef struct _uart_transfer
{
    uint8_t *data;   /*!< The buffer of data to be transfer.*/
    size_t dataSize; /*!< The byte count to be transfer. */
} uart_transfer_t;

/* Forward declaration of the handle typedef. */
typedef struct _uart_handle uart_handle_t;

/*! @brief UART transfer callback function. */
typedef void (*uart_transfer_callback_t)(UART_Type *base, uart_handle_t *handle, status_t status, void *userData);

/*! @brief UART handle structure. */
struct _uart_handle
{
    uint8_t *volatile txData;   /*!< Address of remaining data to send. */
    volatile size_t txDataSize; /*!< Size of the remaining data to send. */
    size_t txDataSizeAll;       /*!< Size of the data to send out. */
    uint8_t *volatile rxData;   /*!< Address of remaining data to receive. */
    volatile size_t rxDataSize; /*!< Size of the remaining data to receive. */
    size_t rxDataSizeAll;       /*!< Size of the data to receive. */

    uint8_t *rxRingBuffer;              /*!< Start address of the receiver ring buffer. */
    size_t rxRingBufferSize;            /*!< Size of the ring buffer. */
    volatile uint16_t rxRingBufferHead; /*!< Index for the driver to store received data into ring buffer. */
    volatile uint16_t rxRingBufferTail; /*!< Index for the user to get data from the ring buffer. */

    uart_transfer_callback_t callback; /*!< Callback function. */
    void *userData;                    /*!< UART callback function parameter.*/

    volatile uint8_t txState; /*!< TX transfer state. */
    volatile uint8_t rxState; /*!< RX transfer state */
};
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Software Reset
 * @{
 */

/*!
 * @brief Resets the UART using software.
 *
 * This function resets the transmit and receive state machines, all FIFOs and register
 * USR1, USR2, UBIR, UBMR, UBRC , URXD, UTXD and UTS[6-3]
 *
 * @param base UART peripheral base address.
 */
static inline void UART_SoftwareReset(UART_Type *base)
{
    base->UCR2 &= ~UART_UCR2_SRST_MASK;
    while ((base->UCR2 & UART_UCR2_SRST_MASK) == 0)
    {
    }
}

/* @} */

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes an UART instance with the user configuration structure and the peripheral clock.
 *
 * This function configures the UART module with user-defined settings. Call the UART_GetDefaultConfig() function
 * to configure the configuration structure and get the default configuration.
 * The example below shows how to use this API to configure the UART.
 * @code
 *  uart_config_t uartConfig;
 *  uartConfig.baudRate_Bps = 115200U;
 *  uartConfig.parityMode = kUART_ParityDisabled;
 *  uartConfig.dataBitsCount = kUART_EightDataBits;
 *  uartConfig.stopBitCount = kUART_OneStopBit;
 *  uartConfig.txFifoWatermark = 2;
 *  uartConfig.rxFifoWatermark = 1;
 *  uartConfig.enableAutoBaudrate = false;
 *  uartConfig.enableTx = true;
 *  uartConfig.enableRx = true;
 *  UART_Init(UART1, &uartConfig, 24000000U);
 * @endcode
 *
 * @param base UART peripheral base address.
 * @param config Pointer to a user-defined configuration structure.
 * @param srcClock_Hz UART clock source frequency in HZ.
 * @retval kStatus_Success UART initialize succeed
 */
status_t UART_Init(UART_Type *base, const uart_config_t *config, uint32_t srcClock_Hz);

/*!
 * @brief Deinitializes a UART instance.
 *
 * This function waits for transmit to complete, disables TX and RX, and disables the UART clock.
 *
 * @param base UART peripheral base address.
 */
void UART_Deinit(UART_Type *base);

/*!l
 * @brief Gets the default configuration structure.
 *
 * This function initializes the UART configuration structure to a default value. The default
 * values are:
 *   uartConfig->baudRate_Bps = 115200U;
 *   uartConfig->parityMode = kUART_ParityDisabled;
 *   uartConfig->dataBitsCount = kUART_EightDataBits;
 *   uartConfig->stopBitCount = kUART_OneStopBit;
 *   uartConfig->txFifoWatermark = 2;
 *   uartConfig->rxFifoWatermark = 1;
 *   uartConfig->enableAutoBaudrate = flase;
 *   uartConfig->enableTx = false;
 *   uartConfig->enableRx = false;
 *
 * @param config Pointer to a configuration structure.
 */
void UART_GetDefaultConfig(uart_config_t *config);

/*!
 * @brief Sets the UART instance baud rate.
 *
 * This function configures the UART module baud rate. This function is used to update
 * the UART module baud rate after the UART module is initialized by the UART_Init.
 * @code
 *  UART_SetBaudRate(UART1, 115200U, 20000000U);
 * @endcode
 *
 * @param base UART peripheral base address.
 * @param baudRate_Bps UART baudrate to be set.
 * @param srcClock_Hz UART clock source freqency in Hz.
 * @retval kStatus_UART_BaudrateNotSupport Baudrate is not support in the current clock source.
 * @retval kStatus_Success Set baudrate succeeded.
 */
status_t UART_SetBaudRate(UART_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz);
/*!
 * @brief This function is used to Enable the UART Module.
 *
 * @param base UART base pointer.
 */
static inline void UART_Enable(UART_Type *base)
{
    base->UCR1 |= UART_UCR1_UARTEN_MASK;
}

/*!
 * @brief This function is used to Disable the UART Module.
 *
 * @param base UART base pointer.
 */
static inline void UART_Disable(UART_Type *base)
{
    base->UCR1 &= ~UART_UCR1_UARTEN_MASK;
}

/* @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief This function is used to get the current status of specific
 *        UART status flag(including interrupt flag). The available
 *        status flag can be select from @ref uart_status_flag_t enumeration.
 *
 * @param base UART base pointer.
 * @param flag Status flag to check.
 * @retval current state of corresponding status flag.
 */
bool UART_GetStatusFlag(UART_Type *base, uint32_t flag);

/*!
 * @brief This function is used to clear the current status
 *        of specific UART status flag. The available status
 *        flag can be select from @ref uart_status_flag_t enumeration.
 *
 * @param base UART base pointer.
 * @param flag Status flag to clear.
 */
void UART_ClearStatusFlag(UART_Type *base, uint32_t flag);

/*@}*/

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables UART interrupts according to the provided mask.
 *
 * This function enables the UART interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members. See @ref _uart_interrupt_enable.
 * For example, to enable TX empty interrupt and RX data ready interrupt, do the following.
 * @code
 *     UART_EnableInterrupts(UART1,kUART_TxEmptyEnable | kUART_RxDataReadyEnable);
 * @endcode
 *
 * @param base UART peripheral base address.
 * @param mask The interrupts to enable. Logical OR of @ref _uart_interrupt_enable.
 */
void UART_EnableInterrupts(UART_Type *base, uint32_t mask);

/*!
 * @brief Disables the UART interrupts according to the provided mask.
 *
 * This function disables the UART interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members. See @ref _uart_interrupt_enable.
 * For example, to disable TX empty interrupt and RX data ready interrupt do the following.
 * @code
 *     UART_EnableInterrupts(UART1,kUART_TxEmptyEnable | kUART_RxDataReadyEnable);
 * @endcode
 *
 * @param base UART peripheral base address.
 * @param mask The interrupts to disable. Logical OR of @ref _uart_interrupt_enable.
 */
void UART_DisableInterrupts(UART_Type *base, uint32_t mask);

/*!
 * @brief Gets enabled UART interrupts.
 *
 * This function gets the enabled UART interrupts. The enabled interrupts are returned
 * as the logical OR value of the enumerators @ref _uart_interrupt_enable. To check
 * a specific interrupt enable status, compare the return value with enumerators
 * in @ref _uart_interrupt_enable.
 * For example, to check whether the TX empty interrupt is enabled:
 * @code
 *     uint32_t enabledInterrupts = UART_GetEnabledInterrupts(UART1);
 *
 *     if (kUART_TxEmptyEnable & enabledInterrupts)
 *     {
 *         ...
 *     }
 * @endcode
 *
 * @param base UART peripheral base address.
 * @return UART interrupt flags which are logical OR of the enumerators in @ref _uart_interrupt_enable.
 */
uint32_t UART_GetEnabledInterrupts(UART_Type *base);

/* @} */

/*!
 * @name Bus Operations
 * @{
 */

/*!
 * @brief Enables or disables the UART transmitter.
 *
 * This function enables or disables the UART transmitter.
 *
 * @param base UART peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void UART_EnableTx(UART_Type *base, bool enable)
{
    if (enable)
    {
        base->UCR2 |= UART_UCR2_TXEN_MASK;
    }
    else
    {
        base->UCR2 &= ~UART_UCR2_TXEN_MASK;
    }
}

/*!
 * @brief Enables or disables the UART receiver.
 *
 * This function enables or disables the UART receiver.
 *
 * @param base UART peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void UART_EnableRx(UART_Type *base, bool enable)
{
    if (enable)
    {
        base->UCR2 |= UART_UCR2_RXEN_MASK;
    }
    else
    {
        base->UCR2 &= ~UART_UCR2_RXEN_MASK;
    }
}

/*!
 * @brief Writes to the transmitter register.
 *
 * This function is used to write data to transmitter register.
 * The upper layer must ensure that the TX register is empty or that
 * the TX FIFO has room before calling this function.
 *
 * @param base UART peripheral base address.
 * @param data Data write to the TX register.
 */
static inline void UART_WriteByte(UART_Type *base, uint8_t data)
{
    base->UTXD = data & UART_UTXD_TX_DATA_MASK;
}

/*!
 * @brief Reads the receiver register.
 *
 * This function is used to read data from receiver register.
 * The upper layer must ensure that the receiver register is full or that
 * the RX FIFO has data before calling this function.
 *
 * @param base UART peripheral base address.
 * @return Data read from data register.
 */
static inline uint8_t UART_ReadByte(UART_Type *base)
{
    return (uint8_t)((base->URXD & UART_URXD_RX_DATA_MASK) >> UART_URXD_RX_DATA_SHIFT);
}

/*!
 * @brief Writes to the TX register using a blocking method.
 *
 * This function polls the TX register, waits for the TX register to be empty or for the TX FIFO
 * to have room and writes data to the TX buffer.
 *
 * @note This function does not check whether all data is sent out to the bus.
 * Before disabling the TX, check kUART_TransmissionCompleteFlag to ensure that the TX is
 * finished.
 *
 * @param base UART peripheral base address.
 * @param data Start address of the data to write.
 * @param length Size of the data to write.
 */
void UART_WriteBlocking(UART_Type *base, const uint8_t *data, size_t length);

/*!
 * @brief Read RX data register using a blocking method.
 *
 * This function polls the RX register, waits for the RX register to be full or for RX FIFO to
 * have data, and reads data from the TX register.
 *
 * @param base UART peripheral base address.
 * @param data Start address of the buffer to store the received data.
 * @param length Size of the buffer.
 * @retval kStatus_UART_RxHardwareOverrun Receiver overrun occurred while receiving data.
 * @retval kStatus_UART_NoiseError A noise error occurred while receiving data.
 * @retval kStatus_UART_FramingError A framing error occurred while receiving data.
 * @retval kStatus_UART_ParityError A parity error occurred while receiving data.
 * @retval kStatus_Success Successfully received all data.
 */
status_t UART_ReadBlocking(UART_Type *base, uint8_t *data, size_t length);

/* @} */

/*!
 * @name Transactional
 * @{
 */

/*!
 * @brief Initializes the UART handle.
 *
 * This function initializes the UART handle which can be used for other UART
 * transactional APIs. Usually, for a specified UART instance,
 * call this API once to get the initialized handle.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 * @param callback The callback function.
 * @param userData The parameter of the callback function.
 */
void UART_TransferCreateHandle(UART_Type *base,
                               uart_handle_t *handle,
                               uart_transfer_callback_t callback,
                               void *userData);

/*!
 * @brief Sets up the RX ring buffer.
 *
 * This function sets up the RX ring buffer to a specific UART handle.
 *
 * When the RX ring buffer is used, data received are stored into the ring buffer even when the
 * user doesn't call the UART_TransferReceiveNonBlocking() API. If data is already received
 * in the ring buffer, the user can get the received data from the ring buffer directly.
 *
 * @note When using the RX ring buffer, one byte is reserved for internal use. In other
 * words, if @p ringBufferSize is 32, only 31 bytes are used for saving data.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 * @param ringBuffer Start address of the ring buffer for background receiving. Pass NULL to disable the ring buffer.
 * @param ringBufferSize Size of the ring buffer.
 */
void UART_TransferStartRingBuffer(UART_Type *base, uart_handle_t *handle, uint8_t *ringBuffer, size_t ringBufferSize);

/*!
 * @brief Aborts the background transfer and uninstalls the ring buffer.
 *
 * This function aborts the background transfer and uninstalls the ring buffer.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 */
void UART_TransferStopRingBuffer(UART_Type *base, uart_handle_t *handle);

/*!
 * @brief Get the length of received data in RX ring buffer.
 *
 * @param handle UART handle pointer.
 * @return Length of received data in RX ring buffer.
 */
size_t UART_TransferGetRxRingBufferLength(uart_handle_t *handle);

/*!
 * @brief Transmits a buffer of data using the interrupt method.
 *
 * This function sends data using an interrupt method. This is a non-blocking function, which
 * returns directly without waiting for all data to be written to the TX register. When
 * all data is written to the TX register in the ISR, the UART driver calls the callback
 * function and passes the @ref kStatus_UART_TxIdle as status parameter.
 *
 * @note The kStatus_UART_TxIdle is passed to the upper layer when all data is written
 * to the TX register. However, it does not ensure that all data is sent out. Before disabling the TX,
 * check the kUART_TransmissionCompleteFlag to ensure that the TX is finished.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 * @param xfer UART transfer structure. See  #uart_transfer_t.
 * @retval kStatus_Success Successfully start the data transmission.
 * @retval kStatus_UART_TxBusy Previous transmission still not finished; data not all written to TX register yet.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_TransferSendNonBlocking(UART_Type *base, uart_handle_t *handle, uart_transfer_t *xfer);

/*!
 * @brief Aborts the interrupt-driven data transmit.
 *
 * This function aborts the interrupt-driven data sending. The user can get the remainBytes to find out
 * how many bytes are not sent out.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 */
void UART_TransferAbortSend(UART_Type *base, uart_handle_t *handle);

/*!
 * @brief Gets the number of bytes written to the UART TX register.
 *
 * This function gets the number of bytes written to the UART TX
 * register by using the interrupt method.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 * @param count Send bytes count.
 * @retval kStatus_NoTransferInProgress No send in progress.
 * @retval kStatus_InvalidArgument The parameter is invalid.
 * @retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t UART_TransferGetSendCount(UART_Type *base, uart_handle_t *handle, uint32_t *count);

/*!
 * @brief Receives a buffer of data using an interrupt method.
 *
 * This function receives data using an interrupt method. This is a non-blocking function, which
 *  returns without waiting for all data to be received.
 * If the RX ring buffer is used and not empty, the data in the ring buffer is copied and
 * the parameter @p receivedBytes shows how many bytes are copied from the ring buffer.
 * After copying, if the data in the ring buffer is not enough to read, the receive
 * request is saved by the UART driver. When the new data arrives, the receive request
 * is serviced first. When all data is received, the UART driver notifies the upper layer
 * through a callback function and passes the status parameter @ref kStatus_UART_RxIdle.
 * For example, the upper layer needs 10 bytes but there are only 5 bytes in the ring buffer.
 * The 5 bytes are copied to the xfer->data and this function returns with the
 * parameter @p receivedBytes set to 5. For the left 5 bytes, newly arrived data is
 * saved from the xfer->data[5]. When 5 bytes are received, the UART driver notifies the upper layer.
 * If the RX ring buffer is not enabled, this function enables the RX and RX interrupt
 * to receive data to the xfer->data. When all data is received, the upper layer is notified.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 * @param xfer UART transfer structure, see #uart_transfer_t.
 * @param receivedBytes Bytes received from the ring buffer directly.
 * @retval kStatus_Success Successfully queue the transfer into transmit queue.
 * @retval kStatus_UART_RxBusy Previous receive request is not finished.
 * @retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_TransferReceiveNonBlocking(UART_Type *base,
                                         uart_handle_t *handle,
                                         uart_transfer_t *xfer,
                                         size_t *receivedBytes);

/*!
 * @brief Aborts the interrupt-driven data receiving.
 *
 * This function aborts the interrupt-driven data receiving. The user can get the remainBytes to know
 * how many bytes are not received yet.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 */
void UART_TransferAbortReceive(UART_Type *base, uart_handle_t *handle);

/*!
 * @brief Gets the number of bytes that have been received.
 *
 * This function gets the number of bytes that have been received.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 * @param count Receive bytes count.
 * @retval kStatus_NoTransferInProgress No receive in progress.
 * @retval kStatus_InvalidArgument Parameter is invalid.
 * @retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t UART_TransferGetReceiveCount(UART_Type *base, uart_handle_t *handle, uint32_t *count);

/*!
 * @brief UART IRQ handle function.
 *
 * This function handles the UART transmit and receive IRQ request.
 *
 * @param base UART peripheral base address.
 * @param handle UART handle pointer.
 */
void UART_TransferHandleIRQ(UART_Type *base, uart_handle_t *handle);

/*@}*/

/*!
 * @name DMA control functions.
 * @{
 */

/*!
 * @brief Enables or disables the UART transmitter DMA request.
 *
 * This function enables or disables the transmit request when the transmitter
 * has one or more slots available in the TxFIFO. The fill level in the TxFIFO
 * that generates the DMA request is controlled by the TXTL bits.
 *
 * @param base UART peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void UART_EnableTxDMA(UART_Type *base, bool enable)
{
    assert(base);

    if (enable)
    {
        base->UCR1 |= UART_UCR1_TXDMAEN_MASK;
    }
    else
    {
        base->UCR1 &= ~UART_UCR1_TXDMAEN_MASK;
    }
}

/*!
 * @brief Enables or disables the UART receiver DMA request.
 *
 * This function enables or disables the receive request when the receiver
 * has data in the RxFIFO. The fill level in the RxFIFO at which a DMA request
 * is generated is controlled by the RXTL bits .
 *
 * @param base UART peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void UART_EnableRxDMA(UART_Type *base, bool enable)
{
    assert(base);

    if (enable)
    {
        base->UCR1 |= UART_UCR1_RXDMAEN_MASK;
    }
    else
    {
        base->UCR1 &= ~UART_UCR1_RXDMAEN_MASK;
    }
}

/*@}*/

/*!
 * @name FIFO control functions.
 * @{
 */

/*!
 * @brief This function is used to set the watermark of UART Tx FIFO.
 *        A maskable interrupt is generated whenever the data level in
 *        the TxFIFO falls below the Tx FIFO watermark.
 *
 * @param base UART base pointer.
 * @param watermark The Tx FIFO watermark.
 */
static inline void UART_SetTxFifoWatermark(UART_Type *base, uint8_t watermark)
{
    assert((watermark >= 2) && (watermark <= FSL_FEATURE_IUART_FIFO_SIZEn(base)));
    base->UFCR = (base->UFCR & ~UART_UFCR_TXTL_MASK) | UART_UFCR_TXTL(watermark);
}

/*!
 * @brief This function is used to set the watermark of UART Rx FIFO.
 *        A maskable interrupt is generated whenever the data level in
 *        the RxFIFO reaches the Rx FIFO watermark.
 *
 * @param base UART base pointer.
 * @param watermark The Rx FIFO watermark.
 */
static inline void UART_SetRxFifoWatermark(UART_Type *base, uint8_t watermark)
{
    assert(watermark <= FSL_FEATURE_IUART_FIFO_SIZEn(base));
    base->UFCR = (base->UFCR & ~UART_UFCR_RXTL_MASK) | UART_UFCR_RXTL(watermark);
}

/*@}*/

/*!
 * @name Auto baud rate detection.
 * @{
 */

/*!
 * @brief This function is used to set the enable condition of
 *        Automatic Baud Rate Detection feature.
 *
 * @param base UART base pointer.
 * @param enable Enable/Disable Automatic Baud Rate Detection feature.
 *               - true: Enable Automatic Baud Rate Detection feature.
 *               - false: Disable Automatic Baud Rate Detection feature.
 */
static inline void UART_EnableAutoBaudRate(UART_Type *base, bool enable)
{
    if (enable)
    {
        /* When ADET=0 and ADBR=1, automatic baud rate detection starts */
        /* Enable automatic baud rate detection */
        base->UCR1 |= UART_UCR1_ADBR_MASK;
        /* Clear ADET brfore start automatic baud rate detection*/
        base->USR2 |= UART_USR2_ADET_MASK;
    }
    else
    {
        /* Disable automatic baud rate detection */
        base->UCR1 &= ~UART_UCR1_ADBR_MASK;
    }
}
/*!
 * @brief This function is used to read if the automatic baud rate detection
 *        has finished.
 *
 * @param base UART base pointer.
 * @return - true: Automatic baud rate detection has finished.
 *         - false: Automatic baud rate detection has not finished.
 */
static inline bool UART_IsAutoBaudRateComplete(UART_Type *base)
{
    if (UART_USR2_ACST_MASK & base->USR2)
    {
        base->USR2 |= UART_USR2_ACST_MASK;
        return true;
    }
    else
    {
        return false;
    }
}

#ifdef __cplusplus
}
#endif

/*! @}*/

#endif /* _FSL_UART_H_ */
