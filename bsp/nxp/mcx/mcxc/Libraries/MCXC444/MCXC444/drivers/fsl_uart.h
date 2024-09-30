/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_UART_H_
#define FSL_UART_H_

#include "fsl_common.h"

/*!
 * @addtogroup uart_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief UART driver version. */
#define FSL_UART_DRIVER_VERSION (MAKE_VERSION(2, 5, 1))
/*! @} */

/*! @brief Retry times for waiting flag. */
#ifndef UART_RETRY_TIMES
#define UART_RETRY_TIMES 0U /* Defining to zero means to keep waiting for the flag until it is assert/deassert. */
#endif

/*! @brief Error codes for the UART driver. */
enum
{
    kStatus_UART_TxBusy              = MAKE_STATUS(kStatusGroup_UART, 0), /*!< Transmitter is busy. */
    kStatus_UART_RxBusy              = MAKE_STATUS(kStatusGroup_UART, 1), /*!< Receiver is busy. */
    kStatus_UART_TxIdle              = MAKE_STATUS(kStatusGroup_UART, 2), /*!< UART transmitter is idle. */
    kStatus_UART_RxIdle              = MAKE_STATUS(kStatusGroup_UART, 3), /*!< UART receiver is idle. */
    kStatus_UART_TxWatermarkTooLarge = MAKE_STATUS(kStatusGroup_UART, 4), /*!< TX FIFO watermark too large  */
    kStatus_UART_RxWatermarkTooLarge = MAKE_STATUS(kStatusGroup_UART, 5), /*!< RX FIFO watermark too large  */
    kStatus_UART_FlagCannotClearManually =
        MAKE_STATUS(kStatusGroup_UART, 6),                                 /*!< UART flag can't be manually cleared. */
    kStatus_UART_Error               = MAKE_STATUS(kStatusGroup_UART, 7),  /*!< Error happens on UART. */
    kStatus_UART_RxRingBufferOverrun = MAKE_STATUS(kStatusGroup_UART, 8),  /*!< UART RX software ring buffer overrun. */
    kStatus_UART_RxHardwareOverrun   = MAKE_STATUS(kStatusGroup_UART, 9),  /*!< UART RX receiver overrun. */
    kStatus_UART_NoiseError          = MAKE_STATUS(kStatusGroup_UART, 10), /*!< UART noise error. */
    kStatus_UART_FramingError        = MAKE_STATUS(kStatusGroup_UART, 11), /*!< UART framing error. */
    kStatus_UART_ParityError         = MAKE_STATUS(kStatusGroup_UART, 12), /*!< UART parity error. */
    kStatus_UART_BaudrateNotSupport =
        MAKE_STATUS(kStatusGroup_UART, 13), /*!< Baudrate is not support in current clock source */
    kStatus_UART_IdleLineDetected = MAKE_STATUS(kStatusGroup_UART, 14), /*!< UART IDLE line detected. */
    kStatus_UART_Timeout          = MAKE_STATUS(kStatusGroup_UART, 15), /*!< UART times out. */
};

/*! @brief UART parity mode. */
typedef enum _uart_parity_mode
{
    kUART_ParityDisabled = 0x0U, /*!< Parity disabled */
    kUART_ParityEven     = 0x2U, /*!< Parity enabled, type even, bit setting: PE|PT = 10 */
    kUART_ParityOdd      = 0x3U, /*!< Parity enabled, type odd,  bit setting: PE|PT = 11 */
} uart_parity_mode_t;

/*! @brief UART stop bit count. */
typedef enum _uart_stop_bit_count
{
    kUART_OneStopBit = 0U, /*!< One stop bit */
    kUART_TwoStopBit = 1U, /*!< Two stop bits */
} uart_stop_bit_count_t;

/*! @brief UART idle type select. */
typedef enum _uart_idle_type_select
{
    kUART_IdleTypeStartBit = 0U, /*!< Start counting after a valid start bit. */
    kUART_IdleTypeStopBit  = 1U, /*!< Start counting after a stop bit. */
} uart_idle_type_select_t;

/*!
 * @brief UART interrupt configuration structure, default settings all disabled.
 *
 * This structure contains the settings for all of the UART interrupt configurations.
 */
enum _uart_interrupt_enable
{
#if defined(FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT) && FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT
    kUART_LinBreakInterruptEnable = (UART_BDH_LBKDIE_MASK), /*!< LIN break detect interrupt. */
#endif
    kUART_RxActiveEdgeInterruptEnable         = (UART_BDH_RXEDGIE_MASK), /*!< RX active edge interrupt. */
    kUART_TxDataRegEmptyInterruptEnable       = (UART_C2_TIE_MASK << 8), /*!< Transmit data register empty interrupt. */
    kUART_TransmissionCompleteInterruptEnable = (UART_C2_TCIE_MASK << 8), /*!< Transmission complete interrupt. */
    kUART_RxDataRegFullInterruptEnable        = (UART_C2_RIE_MASK << 8),  /*!< Receiver data register full interrupt. */
    kUART_IdleLineInterruptEnable             = (UART_C2_ILIE_MASK << 8), /*!< Idle line interrupt. */
    kUART_RxOverrunInterruptEnable            = (UART_C3_ORIE_MASK << 16), /*!< Receiver overrun interrupt. */
    kUART_NoiseErrorInterruptEnable           = (UART_C3_NEIE_MASK << 16), /*!< Noise error flag interrupt. */
    kUART_FramingErrorInterruptEnable         = (UART_C3_FEIE_MASK << 16), /*!< Framing error flag interrupt. */
    kUART_ParityErrorInterruptEnable          = (UART_C3_PEIE_MASK << 16), /*!< Parity error flag interrupt. */
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    kUART_RxFifoOverflowInterruptEnable  = (UART_CFIFO_RXOFE_MASK << 24), /*!< RX FIFO overflow interrupt. */
    kUART_TxFifoOverflowInterruptEnable  = (UART_CFIFO_TXOFE_MASK << 24), /*!< TX FIFO overflow interrupt. */
    kUART_RxFifoUnderflowInterruptEnable = (UART_CFIFO_RXUFE_MASK << 24), /*!< RX FIFO underflow interrupt. */
#endif
    kUART_AllInterruptsEnable =
#if defined(FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT) && FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT
        kUART_LinBreakInterruptEnable |
#endif
        kUART_RxActiveEdgeInterruptEnable | kUART_TxDataRegEmptyInterruptEnable |
        kUART_TransmissionCompleteInterruptEnable | kUART_RxDataRegFullInterruptEnable | kUART_IdleLineInterruptEnable |
        kUART_RxOverrunInterruptEnable | kUART_NoiseErrorInterruptEnable | kUART_FramingErrorInterruptEnable |
        kUART_ParityErrorInterruptEnable
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
        | kUART_RxFifoOverflowInterruptEnable | kUART_TxFifoOverflowInterruptEnable |
        kUART_RxFifoUnderflowInterruptEnable
#endif
    ,
};

/*!
 * @brief UART status flags.
 *
 * This provides constants for the UART status flags for use in the UART functions.
 */
enum
{
    kUART_TxDataRegEmptyFlag       = (UART_S1_TDRE_MASK), /*!< TX data register empty flag. */
    kUART_TransmissionCompleteFlag = (UART_S1_TC_MASK),   /*!< Transmission complete flag. */
    kUART_RxDataRegFullFlag        = (UART_S1_RDRF_MASK), /*!< RX data register full flag. */
    kUART_IdleLineFlag             = (UART_S1_IDLE_MASK), /*!< Idle line detect flag. */
    kUART_RxOverrunFlag            = (UART_S1_OR_MASK),   /*!< RX overrun flag. */
    kUART_NoiseErrorFlag           = (UART_S1_NF_MASK),   /*!< RX takes 3 samples of each received bit.
                                                               If any of these samples differ, noise flag sets */
    kUART_FramingErrorFlag = (UART_S1_FE_MASK),           /*!< Frame error flag, sets if logic 0 was detected
                                                               where stop bit expected */
    kUART_ParityErrorFlag = (UART_S1_PF_MASK),            /*!< If parity enabled, sets upon parity error detection */
#if defined(FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT) && FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT
    kUART_LinBreakFlag =
        (UART_S2_LBKDIF_MASK
         << 8), /*!< LIN break detect interrupt flag, sets when LIN break char detected and LIN circuit enabled */
#endif
    kUART_RxActiveEdgeFlag =
        (UART_S2_RXEDGIF_MASK << 8), /*!< RX pin active edge interrupt flag,sets when active edge detected */
    kUART_RxActiveFlag =
        (UART_S2_RAF_MASK << 8), /*!< Receiver Active Flag (RAF), sets at beginning of valid start bit */
#if defined(FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS) && FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS
    kUART_NoiseErrorInRxDataRegFlag  = (UART_ED_NOISY_MASK << 16),   /*!< Noisy bit, sets if noise detected. */
    kUART_ParityErrorInRxDataRegFlag = (UART_ED_PARITYE_MASK << 16), /*!< Parity bit, sets if parity error detected. */
#endif
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    kUART_TxFifoEmptyFlag     = (int)(UART_SFIFO_TXEMPT_MASK << 24), /*!< TXEMPT bit, sets if TX buffer is empty */
    kUART_RxFifoEmptyFlag     = (UART_SFIFO_RXEMPT_MASK << 24),      /*!< RXEMPT bit, sets if RX buffer is empty */
    kUART_TxFifoOverflowFlag  = (UART_SFIFO_TXOF_MASK << 24), /*!< TXOF bit, sets if TX buffer overflow occurred */
    kUART_RxFifoOverflowFlag  = (UART_SFIFO_RXOF_MASK << 24), /*!< RXOF bit, sets if receive buffer overflow */
    kUART_RxFifoUnderflowFlag = (UART_SFIFO_RXUF_MASK << 24), /*!< RXUF bit, sets if receive buffer underflow */
#endif
};

/*! @brief UART configuration structure. */
typedef struct _uart_config
{
    uint32_t baudRate_Bps;         /*!< UART baud rate  */
    uart_parity_mode_t parityMode; /*!< Parity mode, disabled (default), even, odd */
#if defined(FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT) && FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
    uart_stop_bit_count_t stopBitCount; /*!< Number of stop bits, 1 stop bit (default) or 2 stop bits  */
#endif
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    uint8_t txFifoWatermark; /*!< TX FIFO watermark */
    uint8_t rxFifoWatermark; /*!< RX FIFO watermark */
#endif
#if defined(FSL_FEATURE_UART_HAS_MODEM_SUPPORT) && FSL_FEATURE_UART_HAS_MODEM_SUPPORT
    bool enableRxRTS; /*!< RX RTS enable */
    bool enableTxCTS; /*!< TX CTS enable */
#endif
    uart_idle_type_select_t idleType; /*!< IDLE type select. */
    bool enableTx;                    /*!< Enable TX */
    bool enableRx;                    /*!< Enable RX */
} uart_config_t;

/*! @brief UART transfer structure. */
typedef struct _uart_transfer
{
    /*
     * Use separate TX and RX data pointer, because TX data is const data.
     * The member data is kept for backward compatibility.
     */
    union
    {
        uint8_t *data;         /*!< The buffer of data to be transfer.*/
        uint8_t *rxData;       /*!< The buffer to receive data. */
        const uint8_t *txData; /*!< The buffer of data to be sent. */
    };
    size_t dataSize; /*!< The byte count to be transfer. */
} uart_transfer_t;

/* Forward declaration of the handle typedef. */
typedef struct _uart_handle uart_handle_t;

/*! @brief UART transfer callback function. */
typedef void (*uart_transfer_callback_t)(UART_Type *base, uart_handle_t *handle, status_t status, void *userData);

/*! @brief UART handle structure. */
struct _uart_handle
{
    const uint8_t *volatile txData; /*!< Address of remaining data to send. */
    volatile size_t txDataSize;     /*!< Size of the remaining data to send. */
    size_t txDataSizeAll;           /*!< Size of the data to send out. */
    uint8_t *volatile rxData;       /*!< Address of remaining data to receive. */
    volatile size_t rxDataSize;     /*!< Size of the remaining data to receive. */
    size_t rxDataSizeAll;           /*!< Size of the data to receive. */

    uint8_t *rxRingBuffer;              /*!< Start address of the receiver ring buffer. */
    size_t rxRingBufferSize;            /*!< Size of the ring buffer. */
    volatile uint16_t rxRingBufferHead; /*!< Index for the driver to store received data into ring buffer. */
    volatile uint16_t rxRingBufferTail; /*!< Index for the user to get data from the ring buffer. */

    uart_transfer_callback_t callback; /*!< Callback function. */
    void *userData;                    /*!< UART callback function parameter.*/

    volatile uint8_t txState; /*!< TX transfer state. */
    volatile uint8_t rxState; /*!< RX transfer state */
};

/* Typedef for interrupt handler. */
typedef void (*uart_isr_t)(UART_Type *base, void *handle);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! Pointers to uart handles for each instance. */
extern void *s_uartHandle[];

/* Array of UART IRQs. */
extern const IRQn_Type s_uartIRQ[];

/*! Pointer to uart IRQ handler for each instance. */
extern uart_isr_t s_uartIsr;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* _cplusplus */

/*!
 * @brief Get the UART instance from peripheral base address.
 *
 * @param base UART peripheral base address.
 * @return UART instance.
 */
uint32_t UART_GetInstance(UART_Type *base);

/*!
 * @name Initialization and deinitialization
 * @{
 */

/*!
 * @brief Initializes a UART instance with a user configuration structure and peripheral clock.
 *
 * This function configures the UART module with the user-defined settings. The user can configure the configuration
 * structure and also get the default configuration by using the UART_GetDefaultConfig() function.
 * The example below shows how to use this API to configure UART.
 * @code
 *  uart_config_t uartConfig;
 *  uartConfig.baudRate_Bps = 115200U;
 *  uartConfig.parityMode = kUART_ParityDisabled;
 *  uartConfig.stopBitCount = kUART_OneStopBit;
 *  uartConfig.txFifoWatermark = 0;
 *  uartConfig.rxFifoWatermark = 1;
 *  UART_Init(UART1, &uartConfig, 20000000U);
 * @endcode
 *
 * @param base UART peripheral base address.
 * @param config Pointer to the user-defined configuration structure.
 * @param srcClock_Hz UART clock source frequency in HZ.
 * @retval kStatus_UART_BaudrateNotSupport Baudrate is not support in current clock source.
 * @retval kStatus_Success Status UART initialize succeed
 */
status_t UART_Init(UART_Type *base, const uart_config_t *config, uint32_t srcClock_Hz);

/*!
 * @brief Deinitializes a UART instance.
 *
 * This function waits for TX complete, disables TX and RX, and disables the UART clock.
 *
 * @param base UART peripheral base address.
 */
void UART_Deinit(UART_Type *base);

/*!
 * @brief Gets the default configuration structure.
 *
 * This function initializes the UART configuration structure to a default value. The default
 * values are as follows.
 *   uartConfig->baudRate_Bps = 115200U;
 *   uartConfig->bitCountPerChar = kUART_8BitsPerChar;
 *   uartConfig->parityMode = kUART_ParityDisabled;
 *   uartConfig->stopBitCount = kUART_OneStopBit;
 *   uartConfig->txFifoWatermark = 0;
 *   uartConfig->rxFifoWatermark = 1;
 *   uartConfig->idleType = kUART_IdleTypeStartBit;
 *   uartConfig->enableTx = false;
 *   uartConfig->enableRx = false;
 *
 * @param config Pointer to configuration structure.
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
 * @param srcClock_Hz UART clock source frequency in Hz.
 * @retval kStatus_UART_BaudrateNotSupport Baudrate is not support in the current clock source.
 * @retval kStatus_Success Set baudrate succeeded.
 */
status_t UART_SetBaudRate(UART_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz);

/*!
 * @brief Enable 9-bit data mode for UART.
 *
 * This function set the 9-bit mode for UART module. The 9th bit is not used for parity thus can be modified by user.
 *
 * @param base UART peripheral base address.
 * @param enable true to enable, flase to disable.
 */
void UART_Enable9bitMode(UART_Type *base, bool enable);

#if defined(FSL_FEATURE_UART_HAS_ADDRESS_MATCHING) && FSL_FEATURE_UART_HAS_ADDRESS_MATCHING
/*!
 * @brief Set the UART slave address.
 *
 * This function configures the address for UART module that works as slave in 9-bit data mode. One or two address
 * fields can be configured. When the address field's match enable bit is set, the frame it receices with MSB being
 * 1 is considered as an address frame, otherwise it is considered as data frame. Once the address frame matches one
 * of slave's own addresses, this slave is addressed. This address frame and its following data frames are stored in
 * the receive buffer, otherwise the frames will be discarded. To un-address a slave, just send an address frame with
 * unmatched address.
 *
 * @note Any UART instance joined in the multi-slave system can work as slave. The position of the address mark is the
 * same as the parity bit when parity is enabled for 8 bit and 9 bit data formats.
 *
 * @param base UART peripheral base address.
 * @param address1 UART slave address 1.
 * @param address2 UART slave address 2.
 */
static inline void UART_SetMatchAddress(UART_Type *base, uint8_t address1, uint8_t address2)
{
    /* Configure match address. */
    base->MA1 = address1;
    base->MA2 = address2;
}

/*!
 * @brief Enable the UART match address feature.
 *
 * @param base UART peripheral base address.
 * @param match1 true to enable match address1, false to disable.
 * @param match2 true to enable match address2, false to disable.
 */
static inline void UART_EnableMatchAddress(UART_Type *base, bool match1, bool match2)
{
    /* Configure match address1 enable bit. */
    if (match1)
    {
        base->C4 |= (uint8_t)UART_C4_MAEN1_MASK;
    }
    else
    {
        base->C4 &= ~(uint8_t)UART_C4_MAEN1_MASK;
    }
    /* Configure match address2 enable bit. */
    if (match2)
    {
        base->C4 |= (uint8_t)UART_C4_MAEN2_MASK;
    }
    else
    {
        base->C4 &= ~(uint8_t)UART_C4_MAEN2_MASK;
    }
}
#endif

/*!
 * @brief Set UART 9th transmit bit.
 *
 * @param base UART peripheral base address.
 */
static inline void UART_Set9thTransmitBit(UART_Type *base)
{
    base->C3 |= (uint8_t)UART_C3_T8_MASK;
}

/*!
 * @brief Clear UART 9th transmit bit.
 *
 * @param base UART peripheral base address.
 */
static inline void UART_Clear9thTransmitBit(UART_Type *base)
{
    base->C3 &= ~(uint8_t)UART_C3_T8_MASK;
}

/*! @} */

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets UART status flags.
 *
 * This function gets all UART status flags. The flags are returned as the logical
 * OR value of the enumerators _uart_flags. To check a specific status,
 * compare the return value with enumerators in _uart_flags.
 * For example, to check whether the TX is empty, do the following.
 * @code
 *     if (kUART_TxDataRegEmptyFlag & UART_GetStatusFlags(UART1))
 *     {
 *         ...
 *     }
 * @endcode
 *
 * @param base UART peripheral base address.
 * @return UART status flags which are ORed by the enumerators in the _uart_flags.
 */
uint32_t UART_GetStatusFlags(UART_Type *base);

/*!
 * @brief Clears status flags with the provided mask.
 *
 * This function clears UART status flags with a provided mask. An automatically cleared flag
 * can't be cleared by this function.
 * These flags can only be cleared or set by hardware.
 *    kUART_TxDataRegEmptyFlag, kUART_TransmissionCompleteFlag, kUART_RxDataRegFullFlag,
 *    kUART_RxActiveFlag, kUART_NoiseErrorInRxDataRegFlag, kUART_ParityErrorInRxDataRegFlag,
 *    kUART_TxFifoEmptyFlag,kUART_RxFifoEmptyFlag
 * @note that this API should be called when the Tx/Rx is idle. Otherwise it has no effect.
 *
 * @param base UART peripheral base address.
 * @param mask The status flags to be cleared; it is logical OR value of _uart_flags.
 * @retval kStatus_UART_FlagCannotClearManually The flag can't be cleared by this function but
 *         it is cleared automatically by hardware.
 * @retval kStatus_Success Status in the mask is cleared.
 */
status_t UART_ClearStatusFlags(UART_Type *base, uint32_t mask);

/*! @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables UART interrupts according to the provided mask.
 *
 * This function enables the UART interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members. See @ref _uart_interrupt_enable.
 * For example, to enable TX empty interrupt and RX full interrupt, do the following.
 * @code
 *     UART_EnableInterrupts(UART1,kUART_TxDataRegEmptyInterruptEnable | kUART_RxDataRegFullInterruptEnable);
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
 * For example, to disable TX empty interrupt and RX full interrupt do the following.
 * @code
 *     UART_DisableInterrupts(UART1,kUART_TxDataRegEmptyInterruptEnable | kUART_RxDataRegFullInterruptEnable);
 * @endcode
 *
 * @param base UART peripheral base address.
 * @param mask The interrupts to disable. Logical OR of @ref _uart_interrupt_enable.
 */
void UART_DisableInterrupts(UART_Type *base, uint32_t mask);

/*!
 * @brief Gets the enabled UART interrupts.
 *
 * This function gets the enabled UART interrupts. The enabled interrupts are returned
 * as the logical OR value of the enumerators @ref _uart_interrupt_enable. To check
 * a specific interrupts enable status, compare the return value with enumerators
 * in @ref _uart_interrupt_enable.
 * For example, to check whether TX empty interrupt is enabled, do the following.
 * @code
 *     uint32_t enabledInterrupts = UART_GetEnabledInterrupts(UART1);
 *
 *     if (kUART_TxDataRegEmptyInterruptEnable & enabledInterrupts)
 *     {
 *         ...
 *     }
 * @endcode
 *
 * @param base UART peripheral base address.
 * @return UART interrupt flags which are logical OR of the enumerators in @ref _uart_interrupt_enable.
 */
uint32_t UART_GetEnabledInterrupts(UART_Type *base);

/*! @} */

#if defined(FSL_FEATURE_UART_HAS_DMA_SELECT) && FSL_FEATURE_UART_HAS_DMA_SELECT
/*!
 * @name DMA Control
 * @{
 */

/*!
 * @brief Gets the UART data register address.
 *
 * This function returns the UART data register address, which is mainly used by DMA/eDMA.
 *
 * @param base UART peripheral base address.
 * @return UART data register addresses which are used both by the transmitter and the receiver.
 */
static inline uint32_t UART_GetDataRegisterAddress(UART_Type *base)
{
    return (uint32_t) & (base->D);
}

/*!
 * @brief Enables or disables the UART transmitter DMA request.
 *
 * This function enables or disables the transmit data register empty flag, S1[TDRE], to generate the DMA requests.
 *
 * @param base UART peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void UART_EnableTxDMA(UART_Type *base, bool enable)
{
    if (enable)
    {
#if (defined(FSL_FEATURE_UART_IS_SCI) && FSL_FEATURE_UART_IS_SCI)
        base->C4 |= (uint8_t)UART_C4_TDMAS_MASK;
#else
        base->C5 |= (uint8_t)UART_C5_TDMAS_MASK;
#endif
        base->C2 |= (uint8_t)UART_C2_TIE_MASK;
    }
    else
    {
#if (defined(FSL_FEATURE_UART_IS_SCI) && FSL_FEATURE_UART_IS_SCI)
        base->C4 &= ~(uint8_t)UART_C4_TDMAS_MASK;
#else
        base->C5 &= ~(uint8_t)UART_C5_TDMAS_MASK;
#endif
        base->C2 &= ~(uint8_t)UART_C2_TIE_MASK;
    }
}

/*!
 * @brief Enables or disables the UART receiver DMA.
 *
 * This function enables or disables the receiver data register full flag, S1[RDRF], to generate DMA requests.
 *
 * @param base UART peripheral base address.
 * @param enable True to enable, false to disable.
 */
static inline void UART_EnableRxDMA(UART_Type *base, bool enable)
{
    if (enable)
    {
#if (defined(FSL_FEATURE_UART_IS_SCI) && FSL_FEATURE_UART_IS_SCI)
        base->C4 |= (uint8_t)UART_C4_RDMAS_MASK;
#else
        base->C5 |= (uint8_t)UART_C5_RDMAS_MASK;
#endif
        base->C2 |= (uint8_t)UART_C2_RIE_MASK;
    }
    else
    {
#if (defined(FSL_FEATURE_UART_IS_SCI) && FSL_FEATURE_UART_IS_SCI)
        base->C4 &= ~(uint8_t)UART_C4_RDMAS_MASK;
#else
        base->C5 &= ~(uint8_t)UART_C5_RDMAS_MASK;
#endif
        base->C2 &= ~(uint8_t)UART_C2_RIE_MASK;
    }
}

/*! @} */
#endif /* FSL_FEATURE_UART_HAS_DMA_SELECT */

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
        base->C2 |= (uint8_t)UART_C2_TE_MASK;
    }
    else
    {
        base->C2 &= ~(uint8_t)UART_C2_TE_MASK;
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
        base->C2 |= (uint8_t)UART_C2_RE_MASK;
    }
    else
    {
        base->C2 &= ~(uint8_t)UART_C2_RE_MASK;
    }
}

/*!
 * @brief Writes to the TX register.
 *
 * This function writes data to the TX register directly. The upper layer must ensure
 * that the TX register is empty or TX FIFO has empty room before calling this function.
 *
 * @param base UART peripheral base address.
 * @param data The byte to write.
 */
static inline void UART_WriteByte(UART_Type *base, uint8_t data)
{
    base->D = data;
}

/*!
 * @brief Reads the RX register directly.
 *
 * This function reads data from the RX register directly. The upper layer must
 * ensure that the RX register is full or that the TX FIFO has data before calling this function.
 *
 * @param base UART peripheral base address.
 * @return The byte read from UART data register.
 */
static inline uint8_t UART_ReadByte(UART_Type *base)
{
    return base->D;
}

#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
/*!
 * @brief Gets the rx FIFO data count.
 *
 * @param base UART peripheral base address.
 * @return rx FIFO data count.
 */
static inline uint8_t UART_GetRxFifoCount(UART_Type *base)
{
    return (uint8_t)base->RCFIFO;
}

/*!
 * @brief Gets the tx FIFO data count.
 *
 * @param base UART peripheral base address.
 * @return tx FIFO data count.
 */
static inline uint8_t UART_GetTxFifoCount(UART_Type *base)
{
    return (uint8_t)base->TCFIFO;
}
#endif /* FSL_FEATURE_UART_HAS_FIFO */

#if defined(FSL_FEATURE_UART_HAS_ADDRESS_MATCHING) && FSL_FEATURE_UART_HAS_ADDRESS_MATCHING
/*!
 * @brief Transmit an address frame in 9-bit data mode.
 *
 * @param base UART peripheral base address.
 * @param address UART slave address.
 */
void UART_SendAddress(UART_Type *base, uint8_t address);
#endif

/*!
 * @brief Writes to the TX register using a blocking method.
 *
 * This function polls the TX register, waits for the TX register to be empty or for the TX FIFO
 * to have room and writes data to the TX buffer.
 *
 * @param base UART peripheral base address.
 * @param data Start address of the data to write.
 * @param length Size of the data to write.
 * @retval kStatus_UART_Timeout Transmission timed out and was aborted.
 * @retval kStatus_Success Successfully wrote all data.
 */
status_t UART_WriteBlocking(UART_Type *base, const uint8_t *data, size_t length);

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
 * @retval kStatus_UART_Timeout Transmission timed out and was aborted.
 * @retval kStatus_Success Successfully received all data.
 */
status_t UART_ReadBlocking(UART_Type *base, uint8_t *data, size_t length);

/*! @} */

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
 * @brief Gets the number of bytes sent out to bus.
 *
 * This function gets the number of bytes sent out to bus by using the interrupt method.
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

#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
/*!
 * @brief Enables or disables the UART Tx FIFO.
 *
 * This function enables or disables the UART Tx FIFO.
 *
 * param base UART peripheral base address.
 * param enable true to enable, false to disable.
 * retval kStatus_Success Successfully turn on or turn off Tx FIFO.
 * retval kStatus_Fail Fail to turn on or turn off Tx FIFO.
 */
status_t UART_EnableTxFIFO(UART_Type *base, bool enable);

/*!
 * @brief Enables or disables the UART Rx FIFO.
 *
 * This function enables or disables the UART Rx FIFO.
 *
 * param base UART peripheral base address.
 * param enable true to enable, false to disable.
 * retval kStatus_Success Successfully turn on or turn off Rx FIFO.
 * retval kStatus_Fail Fail to turn on or turn off Rx FIFO.
 */
status_t UART_EnableRxFIFO(UART_Type *base, bool enable);

/*!
 * @brief Sets the rx FIFO watermark.
 *
 * @param base UART peripheral base address.
 * @param water Rx FIFO watermark.
 */
static inline void UART_SetRxFifoWatermark(UART_Type *base, uint8_t water)
{
    assert((uint8_t)FSL_FEATURE_UART_FIFO_SIZEn(base) >= water);
    base->RWFIFO = water;
}

/*!
 * @brief Sets the tx FIFO watermark.
 *
 * @param base UART peripheral base address.
 * @param water Tx FIFO watermark.
 */
static inline void UART_SetTxFifoWatermark(UART_Type *base, uint8_t water)
{
    assert((uint8_t)FSL_FEATURE_UART_FIFO_SIZEn(base) >= water);
    base->TWFIFO = water;
}
#endif /* FSL_FEATURE_UART_HAS_FIFO */

/*!
 * @brief UART IRQ handle function.
 *
 * This function handles the UART transmit and receive IRQ request.
 *
 * @param base UART peripheral base address.
 * @param irqHandle UART handle pointer.
 */
void UART_TransferHandleIRQ(UART_Type *base, void *irqHandle);

/*!
 * @brief UART Error IRQ handle function.
 *
 * This function handles the UART error IRQ request.
 *
 * @param base UART peripheral base address.
 * @param irqHandle UART handle pointer.
 */
void UART_TransferHandleErrorIRQ(UART_Type *base, void *irqHandle);

/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* FSL_UART_H_ */
