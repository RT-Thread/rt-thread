/*
 * Copyright (c) 2015-2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_uart.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.uart"
#endif

/* UART transfer state. */
enum
{
    kUART_TxIdle,         /* TX idle. */
    kUART_TxBusy,         /* TX busy. */
    kUART_RxIdle,         /* RX idle. */
    kUART_RxBusy,         /* RX busy. */
    kUART_RxFramingError, /* Rx framing error */
    kUART_RxParityError   /* Rx parity error */
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Check whether the RX ring buffer is full.
 *
 * @param handle UART handle pointer.
 * @retval true  RX ring buffer is full.
 * @retval false RX ring buffer is not full.
 */
static bool UART_TransferIsRxRingBufferFull(uart_handle_t *handle);

/*!
 * @brief Read RX register using non-blocking method.
 *
 * This function reads data from the TX register directly, upper layer must make
 * sure the RX register is full or TX FIFO has data before calling this function.
 *
 * @param base UART peripheral base address.
 * @param data Start address of the buffer to store the received data.
 * @param length Size of the buffer.
 */
static void UART_ReadNonBlocking(UART_Type *base, uint8_t *data, size_t length);

/*!
 * @brief Write to TX register using non-blocking method.
 *
 * This function writes data to the TX register directly, upper layer must make
 * sure the TX register is empty or TX FIFO has empty room before calling this function.
 *
 * @note This function does not check whether all the data has been sent out to bus,
 * so before disable TX, check kUART_TransmissionCompleteFlag to ensure the TX is
 * finished.
 *
 * @param base UART peripheral base address.
 * @param data Start address of the data to write.
 * @param length Size of the buffer to be sent.
 */
static void UART_WriteNonBlocking(UART_Type *base, const uint8_t *data, size_t length);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Array of UART handle. */
#if (defined(UART5))
#define UART_HANDLE_ARRAY_SIZE 6
#else /* UART5 */
#if (defined(UART4))
#define UART_HANDLE_ARRAY_SIZE 5
#else /* UART4 */
#if (defined(UART3))
#define UART_HANDLE_ARRAY_SIZE 4
#else /* UART3 */
#if (defined(UART2))
#define UART_HANDLE_ARRAY_SIZE 3
#else /* UART2 */
#if (defined(UART1))
#define UART_HANDLE_ARRAY_SIZE 2
#else /* UART1 */
#if (defined(UART0))
#define UART_HANDLE_ARRAY_SIZE 1
#else /* UART0 */
#error No UART instance.
#endif /* UART 0 */
#endif /* UART 1 */
#endif /* UART 2 */
#endif /* UART 3 */
#endif /* UART 4 */
#endif /* UART 5 */
void *s_uartHandle[UART_HANDLE_ARRAY_SIZE];
/* Array of UART peripheral base address. */
static UART_Type *const s_uartBases[] = UART_BASE_PTRS;

/* Array of UART IRQ number. */
const IRQn_Type s_uartIRQ[] = UART_RX_TX_IRQS;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of UART clock name. */
static const clock_ip_name_t s_uartClock[] = UART_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/* UART ISR for transactional APIs. */
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
uart_isr_t s_uartIsr = (uart_isr_t)DefaultISR;
#else
uart_isr_t s_uartIsr;
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Get the UART instance from peripheral base address.
 *
 * param base UART peripheral base address.
 * return UART instance.
 */
uint32_t UART_GetInstance(UART_Type *base)
{
    uint32_t instance;
    uint32_t uartArrayCount = (sizeof(s_uartBases) / sizeof(s_uartBases[0]));

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < uartArrayCount; instance++)
    {
        if (s_uartBases[instance] == base)
        {
            break;
        }
    }

    assert(instance < uartArrayCount);

    return instance;
}

/*!
 * brief Get the length of received data in RX ring buffer.
 *
 * param handle UART handle pointer.
 * return Length of received data in RX ring buffer.
 */
size_t UART_TransferGetRxRingBufferLength(uart_handle_t *handle)
{
    assert(handle != NULL);

    size_t size;
    uint16_t rxRingBufferHead = handle->rxRingBufferHead;
    uint16_t rxRingBufferTail = handle->rxRingBufferTail;

    if (rxRingBufferTail > rxRingBufferHead)
    {
        size = (size_t)rxRingBufferHead + handle->rxRingBufferSize - (size_t)rxRingBufferTail;
    }
    else
    {
        size = (size_t)rxRingBufferHead - (size_t)rxRingBufferTail;
    }

    return size;
}

static bool UART_TransferIsRxRingBufferFull(uart_handle_t *handle)
{
    assert(handle != NULL);

    bool full;

    if (UART_TransferGetRxRingBufferLength(handle) == (handle->rxRingBufferSize - 1U))
    {
        full = true;
    }
    else
    {
        full = false;
    }

    return full;
}

/*!
 * brief Initializes a UART instance with a user configuration structure and peripheral clock.
 *
 * This function configures the UART module with the user-defined settings. The user can configure the configuration
 * structure and also get the default configuration by using the UART_GetDefaultConfig() function.
 * The example below shows how to use this API to configure UART.
 * code
 *  uart_config_t uartConfig;
 *  uartConfig.baudRate_Bps = 115200U;
 *  uartConfig.parityMode = kUART_ParityDisabled;
 *  uartConfig.stopBitCount = kUART_OneStopBit;
 *  uartConfig.txFifoWatermark = 0;
 *  uartConfig.rxFifoWatermark = 1;
 *  UART_Init(UART1, &uartConfig, 20000000U);
 * endcode
 *
 * param base UART peripheral base address.
 * param config Pointer to the user-defined configuration structure.
 * param srcClock_Hz UART clock source frequency in HZ.
 * retval kStatus_UART_BaudrateNotSupport Baudrate is not support in current clock source.
 * retval kStatus_Success Status UART initialize succeed
 */
status_t UART_Init(UART_Type *base, const uart_config_t *config, uint32_t srcClock_Hz)
{
    assert(config != NULL);
    assert(config->baudRate_Bps != 0U);
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    assert((uint8_t)FSL_FEATURE_UART_FIFO_SIZEn(base) >= config->txFifoWatermark);
    assert((uint8_t)FSL_FEATURE_UART_FIFO_SIZEn(base) >= config->rxFifoWatermark);
#endif

    uint32_t sbr      = 0U;
    uint8_t temp      = 0U;
    uint32_t baudDiff = 0U;

    /* Calculate the baud rate modulo divisor, sbr*/
    sbr = srcClock_Hz / (config->baudRate_Bps * 16U);
    /* set sbrTemp to 1 if the sourceClockInHz can not satisfy the desired baud rate */
    if (sbr == 0U)
    {
        sbr = 1U;
    }
#if defined(FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT) && FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT
    /* Determine if a fractional divider is needed to fine tune closer to the
     * desired baud, each value of brfa is in 1/32 increments,
     * hence the multiply-by-32. */
    uint32_t tempBaud = 0U;

    uint32_t brfa = (2U * srcClock_Hz / (config->baudRate_Bps)) - 32U * sbr;

    /* Calculate the baud rate based on the temporary SBR values and BRFA */
    tempBaud = srcClock_Hz * 2U / (sbr * 32U + brfa);
    baudDiff =
        (tempBaud > config->baudRate_Bps) ? (tempBaud - config->baudRate_Bps) : (config->baudRate_Bps - tempBaud);

#else
    /* Calculate the baud rate based on the temporary SBR values */
    baudDiff = (srcClock_Hz / (sbr * 16U)) - config->baudRate_Bps;

    /* Select the better value between sbr and (sbr + 1) */
    if (baudDiff > (config->baudRate_Bps - (srcClock_Hz / (16U * ((uint32_t)sbr + 1U)))))
    {
        baudDiff = config->baudRate_Bps - (srcClock_Hz / (16U * ((uint32_t)sbr + 1U)));
        sbr++;
    }
#endif

    /* next, check to see if actual baud rate is within 3% of desired baud rate
     * based on the calculate SBR value */
    if (baudDiff > ((config->baudRate_Bps / 100U) * 3U))
    {
        /* Unacceptable baud rate difference of more than 3%*/
        return kStatus_UART_BaudrateNotSupport;
    }

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable uart clock */
    CLOCK_EnableClock(s_uartClock[UART_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Disable UART TX RX before setting. */
    base->C2 &= ~((uint8_t)UART_C2_TE_MASK | (uint8_t)UART_C2_RE_MASK);

    /* Write the sbr value to the BDH and BDL registers*/
    base->BDH = (base->BDH & ~(uint8_t)UART_BDH_SBR_MASK) | (uint8_t)(sbr >> 8);
    base->BDL = (uint8_t)sbr;

#if defined(FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT) && FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT
    /* Write the brfa value to the register*/
    base->C4 = (base->C4 & ~(uint8_t)UART_C4_BRFA_MASK) | ((uint8_t)brfa & UART_C4_BRFA_MASK);
#endif

    /* Set bit count/parity mode/idle type. */
    temp = base->C1 &
           ~((uint8_t)UART_C1_PE_MASK | (uint8_t)UART_C1_PT_MASK | (uint8_t)UART_C1_M_MASK | (uint8_t)UART_C1_ILT_MASK);

    temp |= UART_C1_ILT(config->idleType);

    if (kUART_ParityDisabled != config->parityMode)
    {
        temp |= (UART_C1_M_MASK | (uint8_t)config->parityMode);
    }

    base->C1 = temp;

#if defined(FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT) && FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
    /* Set stop bit per char */
    base->BDH = (base->BDH & ~(uint8_t)UART_BDH_SBNS_MASK) | (uint8_t)UART_BDH_SBNS((uint8_t)config->stopBitCount);
#endif

#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    /* Set tx/rx FIFO watermark
       Note:
       Take care of the RX FIFO, RX interrupt request only assert when received bytes
       equal or more than RX water mark, there is potential issue if RX water
       mark larger than 1.
       For example, if RX FIFO water mark is 2, upper layer needs 5 bytes and
       5 bytes are received. the last byte will be saved in FIFO but not trigger
       RX interrupt because the water mark is 2.
     */
    base->TWFIFO = config->txFifoWatermark;
    base->RWFIFO = config->rxFifoWatermark;

    /* Enable tx/rx FIFO */
    base->PFIFO |= (UART_PFIFO_TXFE_MASK | UART_PFIFO_RXFE_MASK);

    /* Flush FIFO */
    base->CFIFO |= (UART_CFIFO_TXFLUSH_MASK | UART_CFIFO_RXFLUSH_MASK);
#endif
#if defined(FSL_FEATURE_UART_HAS_MODEM_SUPPORT) && FSL_FEATURE_UART_HAS_MODEM_SUPPORT
    if (config->enableRxRTS)
    {
        /* Enable receiver RTS(request-to-send) function. */
        base->MODEM |= UART_MODEM_RXRTSE_MASK;
    }
    if (config->enableTxCTS)
    {
        /* Enable transmitter CTS(clear-to-send) function. */
        base->MODEM |= UART_MODEM_TXCTSE_MASK;
    }
#endif

    /* Enable TX/RX base on configure structure. */
    temp = base->C2;

    if (config->enableTx)
    {
        temp |= UART_C2_TE_MASK;
    }

    if (config->enableRx)
    {
        temp |= UART_C2_RE_MASK;
    }

    base->C2 = temp;

    return kStatus_Success;
}

/*!
 * brief Deinitializes a UART instance.
 *
 * This function waits for TX complete, disables TX and RX, and disables the UART clock.
 *
 * param base UART peripheral base address.
 */
void UART_Deinit(UART_Type *base)
{
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    /* Wait tx FIFO send out*/
    while (0U != base->TCFIFO)
    {
    }
#endif
    /* Wait last char shoft out */
    while (0U == (base->S1 & UART_S1_TC_MASK))
    {
    }

    /* Disable the module. */
    base->C2 = 0;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable uart clock */
    CLOCK_DisableClock(s_uartClock[UART_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Gets the default configuration structure.
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
 * param config Pointer to configuration structure.
 */
void UART_GetDefaultConfig(uart_config_t *config)
{
    assert(config != NULL);

    /* Initializes the configure structure to zero. */
    (void)memset(config, 0, sizeof(*config));

    config->baudRate_Bps = 115200U;
    config->parityMode   = kUART_ParityDisabled;
#if defined(FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT) && FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
    config->stopBitCount = kUART_OneStopBit;
#endif
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    config->txFifoWatermark = 0;
    config->rxFifoWatermark = 1;
#endif
#if defined(FSL_FEATURE_UART_HAS_MODEM_SUPPORT) && FSL_FEATURE_UART_HAS_MODEM_SUPPORT
    config->enableRxRTS = false;
    config->enableTxCTS = false;
#endif
    config->idleType = kUART_IdleTypeStartBit;
    config->enableTx = false;
    config->enableRx = false;
}

/*!
 * brief Sets the UART instance baud rate.
 *
 * This function configures the UART module baud rate. This function is used to update
 * the UART module baud rate after the UART module is initialized by the UART_Init.
 * code
 *  UART_SetBaudRate(UART1, 115200U, 20000000U);
 * endcode
 *
 * param base UART peripheral base address.
 * param baudRate_Bps UART baudrate to be set.
 * param srcClock_Hz UART clock source frequency in Hz.
 * retval kStatus_UART_BaudrateNotSupport Baudrate is not support in the current clock source.
 * retval kStatus_Success Set baudrate succeeded.
 */
status_t UART_SetBaudRate(UART_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz)
{
    assert(baudRate_Bps != 0U);

    uint32_t sbr      = 0;
    uint32_t baudDiff = 0;
    uint8_t oldCtrl;

    /* Calculate the baud rate modulo divisor, sbr*/
    sbr = srcClock_Hz / (baudRate_Bps * 16U);
    /* set sbrTemp to 1 if the sourceClockInHz can not satisfy the desired baud rate */
    if (sbr == 0U)
    {
        sbr = 1U;
    }
#if defined(FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT) && FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT
    /* Determine if a fractional divider is needed to fine tune closer to the
     * desired baud, each value of brfa is in 1/32 increments,
     * hence the multiply-by-32. */
    uint32_t tempBaud = 0U;

    uint32_t brfa = (2U * srcClock_Hz / (baudRate_Bps)) - 32U * sbr;

    /* Calculate the baud rate based on the temporary SBR values and BRFA */
    tempBaud = (srcClock_Hz * 2U / ((sbr * 32U + brfa)));
    baudDiff = (tempBaud > baudRate_Bps) ? (tempBaud - baudRate_Bps) : (baudRate_Bps - tempBaud);
#else
    /* Calculate the baud rate based on the temporary SBR values */
    baudDiff = (srcClock_Hz / (sbr * 16U)) - baudRate_Bps;

    /* Select the better value between sbr and (sbr + 1) */
    if (baudDiff > (baudRate_Bps - (srcClock_Hz / (16U * (sbr + 1U)))))
    {
        baudDiff = baudRate_Bps - (srcClock_Hz / (16U * (sbr + 1U)));
        sbr++;
    }
#endif

    /* next, check to see if actual baud rate is within 3% of desired baud rate
     * based on the calculate SBR value */
    if (baudDiff < ((baudRate_Bps / 100U) * 3U))
    {
        /* Store C2 before disable Tx and Rx */
        oldCtrl = base->C2;

        /* Disable UART TX RX before setting. */
        base->C2 &= ~((uint8_t)UART_C2_TE_MASK | (uint8_t)UART_C2_RE_MASK);

        /* Write the sbr value to the BDH and BDL registers*/
        base->BDH = (base->BDH & ~(uint8_t)UART_BDH_SBR_MASK) | (uint8_t)(sbr >> 8);
        base->BDL = (uint8_t)sbr;

#if defined(FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT) && FSL_FEATURE_UART_HAS_BAUD_RATE_FINE_ADJUST_SUPPORT
        /* Write the brfa value to the register*/
        base->C4 = (base->C4 & ~(uint8_t)UART_C4_BRFA_MASK) | ((uint8_t)brfa & (uint8_t)UART_C4_BRFA_MASK);
#endif
        /* Restore C2. */
        base->C2 = oldCtrl;

        return kStatus_Success;
    }
    else
    {
        /* Unacceptable baud rate difference of more than 3%*/
        return kStatus_UART_BaudrateNotSupport;
    }
}

/*!
 * brief Enable 9-bit data mode for UART.
 *
 * This function set the 9-bit mode for UART module. The 9th bit is not used for parity thus can be modified by user.
 *
 * param base UART peripheral base address.
 * param enable true to enable, flase to disable.
 */
void UART_Enable9bitMode(UART_Type *base, bool enable)
{
    assert(base != NULL);

    uint8_t temp = 0U;

    if (enable)
    {
        /* Set UART_C1_M for 9-bit mode, clear UART_C1_PT and UART_C1_PE to disable parity. */
        temp = base->C1 & ~((uint8_t)UART_C1_PE_MASK | (uint8_t)UART_C1_PT_MASK | (uint8_t)UART_C1_M_MASK);
        temp |= (uint8_t)UART_C1_M_MASK;
        base->C1 = temp;
    }
    else
    {
        /* Clear UART_C1_M. */
        base->C1 &= ~(uint8_t)UART_C1_M_MASK;
    }
}

#if defined(FSL_FEATURE_UART_HAS_ADDRESS_MATCHING) && FSL_FEATURE_UART_HAS_ADDRESS_MATCHING
/*!
 * brief Transmit an address frame in 9-bit data mode.
 *
 * param base UART peripheral base address.
 * param address UART slave address.
 */
void UART_SendAddress(UART_Type *base, uint8_t address)
{
    assert(base != NULL);

    /* Set address mark. */
    UART_Set9thTransmitBit(base);
    /* Send address. */
    UART_WriteByte(base, address);
    /* Clear address mark for following data transfer. */
    UART_Clear9thTransmitBit(base);
}
#endif

/*!
 * brief Enables UART interrupts according to the provided mask.
 *
 * This function enables the UART interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members. See ref _uart_interrupt_enable.
 * For example, to enable TX empty interrupt and RX full interrupt, do the following.
 * code
 *     UART_EnableInterrupts(UART1,kUART_TxDataRegEmptyInterruptEnable | kUART_RxDataRegFullInterruptEnable);
 * endcode
 *
 * param base UART peripheral base address.
 * param mask The interrupts to enable. Logical OR of ref _uart_interrupt_enable.
 */
void UART_EnableInterrupts(UART_Type *base, uint32_t mask)
{
    mask &= (uint32_t)kUART_AllInterruptsEnable;

    /* The interrupt mask is combined by control bits from several register: ((CFIFO<<24) | (C3<<16) | (C2<<8) |(BDH))
     */
    base->BDH |= (uint8_t)mask;
    base->C2 |= (uint8_t)(mask >> 8);
    base->C3 |= (uint8_t)(mask >> 16);

#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    base->CFIFO |= (uint8_t)(mask >> 24);
#endif
}

/*!
 * brief Disables the UART interrupts according to the provided mask.
 *
 * This function disables the UART interrupts according to the provided mask. The mask
 * is a logical OR of enumeration members. See ref _uart_interrupt_enable.
 * For example, to disable TX empty interrupt and RX full interrupt do the following.
 * code
 *     UART_DisableInterrupts(UART1,kUART_TxDataRegEmptyInterruptEnable | kUART_RxDataRegFullInterruptEnable);
 * endcode
 *
 * param base UART peripheral base address.
 * param mask The interrupts to disable. Logical OR of ref _uart_interrupt_enable.
 */
void UART_DisableInterrupts(UART_Type *base, uint32_t mask)
{
    mask &= (uint32_t)kUART_AllInterruptsEnable;

    /* The interrupt mask is combined by control bits from several register: ((CFIFO<<24) | (C3<<16) | (C2<<8) |(BDH))
     */
    base->BDH &= ~(uint8_t)mask;
    base->C2 &= ~(uint8_t)(mask >> 8);
    base->C3 &= ~(uint8_t)(mask >> 16);

#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    base->CFIFO &= ~(uint8_t)(mask >> 24);
#endif
}

/*!
 * brief Gets the enabled UART interrupts.
 *
 * This function gets the enabled UART interrupts. The enabled interrupts are returned
 * as the logical OR value of the enumerators ref _uart_interrupt_enable. To check
 * a specific interrupts enable status, compare the return value with enumerators
 * in ref _uart_interrupt_enable.
 * For example, to check whether TX empty interrupt is enabled, do the following.
 * code
 *     uint32_t enabledInterrupts = UART_GetEnabledInterrupts(UART1);
 *
 *     if (kUART_TxDataRegEmptyInterruptEnable & enabledInterrupts)
 *     {
 *         ...
 *     }
 * endcode
 *
 * param base UART peripheral base address.
 * return UART interrupt flags which are logical OR of the enumerators in ref _uart_interrupt_enable.
 */
uint32_t UART_GetEnabledInterrupts(UART_Type *base)
{
    uint32_t temp;

    temp = (uint32_t)base->BDH;
    temp |= ((uint32_t)(base->C2) << 8);
    temp |= ((uint32_t)(base->C3) << 16);

#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    temp |= ((uint32_t)(base->CFIFO) << 24);
#endif

    return temp & (uint32_t)kUART_AllInterruptsEnable;
}

/*!
 * brief Gets UART status flags.
 *
 * This function gets all UART status flags. The flags are returned as the logical
 * OR value of the enumerators ref _uart_flags. To check a specific status,
 * compare the return value with enumerators in ref _uart_flags.
 * For example, to check whether the TX is empty, do the following.
 * code
 *     if (kUART_TxDataRegEmptyFlag & UART_GetStatusFlags(UART1))
 *     {
 *         ...
 *     }
 * endcode
 *
 * param base UART peripheral base address.
 * return UART status flags which are ORed by the enumerators in the _uart_flags.
 */
uint32_t UART_GetStatusFlags(UART_Type *base)
{
    uint32_t status_flag;

    status_flag = (uint32_t)base->S1;
    status_flag |= ((uint32_t)(base->S2) << 8);

#if defined(FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS) && FSL_FEATURE_UART_HAS_EXTENDED_DATA_REGISTER_FLAGS
    status_flag |= ((uint32_t)(base->ED) << 16);
#endif

#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    status_flag |= ((uint32_t)(base->SFIFO) << 24);
#endif

    return status_flag;
}

/*!
 * brief Clears status flags with the provided mask.
 *
 * This function clears UART status flags with a provided mask. An automatically cleared flag
 * can't be cleared by this function.
 * These flags can only be cleared or set by hardware.
 *    kUART_TxDataRegEmptyFlag, kUART_TransmissionCompleteFlag, kUART_RxDataRegFullFlag,
 *    kUART_RxActiveFlag, kUART_NoiseErrorInRxDataRegFlag, kUART_ParityErrorInRxDataRegFlag,
 *    kUART_TxFifoEmptyFlag,kUART_RxFifoEmptyFlag
 * Note that this API should be called when the Tx/Rx is idle. Otherwise it has no effect.
 *
 * param base UART peripheral base address.
 * param mask The status flags to be cleared; it is logical OR value of ref _uart_flags.
 * retval kStatus_UART_FlagCannotClearManually The flag can't be cleared by this function but
 *         it is cleared automatically by hardware.
 * retval kStatus_Success Status in the mask is cleared.
 */
status_t UART_ClearStatusFlags(UART_Type *base, uint32_t mask)
{
    uint8_t reg = base->S2;
    status_t status;

#if defined(FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT) && FSL_FEATURE_UART_HAS_LIN_BREAK_DETECT
    reg &= ~((uint8_t)UART_S2_RXEDGIF_MASK | (uint8_t)UART_S2_LBKDIF_MASK);
#else
    reg &= ~(uint8_t)UART_S2_RXEDGIF_MASK;
#endif

    base->S2 = reg | (uint8_t)(mask >> 8);

#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    base->SFIFO = (uint8_t)(mask >> 24);
#endif

    if ((mask & ((uint32_t)kUART_IdleLineFlag | (uint32_t)kUART_NoiseErrorFlag | (uint32_t)kUART_FramingErrorFlag |
                 (uint32_t)kUART_ParityErrorFlag | (uint32_t)kUART_RxOverrunFlag)) != 0u)
    {
        /* Read base->S1 and base->D to clear the flags. */
        (void)base->S1;
        (void)base->D;
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
        /* Read base->D may cause receiver underflow when there are no valid data.
           Clear receiver underflow flag */
        base->SFIFO = UART_SFIFO_RXUF_MASK;
        /* Flush FIFO data. Otherwise FIFO pointer will be in unknown state. */
        base->CFIFO |= UART_CFIFO_RXFLUSH_MASK;
#endif
    }

    /* If some flags still pending. */
    if ((mask & UART_GetStatusFlags(base)) != 0U)
    {
        /* Some flags can only clear or set by the hardware itself, these flags are: kUART_TxDataRegEmptyFlag,
        kUART_TransmissionCompleteFlag, kUART_RxDataRegFullFlag, kUART_RxActiveFlag, kUART_NoiseErrorInRxDataRegFlag,
        kUART_ParityErrorInRxDataRegFlag, kUART_TxFifoEmptyFlag, kUART_RxFifoEmptyFlag. */
        status = kStatus_UART_FlagCannotClearManually;
    }
    else
    {
        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Writes to the TX register using a blocking method.
 *
 * This function polls the TX register, waits for the TX register to be empty or for the TX FIFO
 * to have room and writes data to the TX buffer.
 *
 * param base UART peripheral base address.
 * param data Start address of the data to write.
 * param length Size of the data to write.
 * retval kStatus_UART_Timeout Transmission timed out and was aborted.
 * retval kStatus_Success Successfully wrote all data.
 */
status_t UART_WriteBlocking(UART_Type *base, const uint8_t *data, size_t length)
{
#if UART_RETRY_TIMES
    uint32_t waitTimes;
#endif
    while (0U != length--)
    {
#if UART_RETRY_TIMES
        waitTimes = UART_RETRY_TIMES;
        while ((0U == (base->S1 & UART_S1_TDRE_MASK)) && (0U != --waitTimes))
#else
        while (0U == (base->S1 & UART_S1_TDRE_MASK))
#endif
        {
        }
#if UART_RETRY_TIMES
        if (waitTimes == 0U)
        {
            return kStatus_LPUART_Timeout;
        }
#endif
        base->D = *(data++);
    }

    /* Ensure all the data in the transmit buffer are sent out to bus. */
#if UART_RETRY_TIMES
    waitTimes = UART_RETRY_TIMES;
    while ((0U == (base->S1 & UART_S1_TC_MASK)) && (0U != --waitTimes))
#else
    while (0U == (base->S1 & UART_S1_TC_MASK))
#endif
    {
    }
#if UART_RETRY_TIMES
    if (waitTimes == 0U)
    {
        return kStatus_LPUART_Timeout;
    }
#endif
    return kStatus_Success;
}

static void UART_WriteNonBlocking(UART_Type *base, const uint8_t *data, size_t length)
{
    assert(data != NULL);

    size_t i;

    /* The Non Blocking write data API assume user have ensured there is enough space in
    peripheral to write. */
    for (i = 0; i < length; i++)
    {
        base->D = data[i];
    }
}

/*!
 * brief Read RX data register using a blocking method.
 *
 * This function polls the RX register, waits for the RX register to be full or for RX FIFO to
 * have data, and reads data from the TX register.
 *
 * param base UART peripheral base address.
 * param data Start address of the buffer to store the received data.
 * param length Size of the buffer.
 * retval kStatus_UART_RxHardwareOverrun Receiver overrun occurred while receiving data.
 * retval kStatus_UART_NoiseError A noise error occurred while receiving data.
 * retval kStatus_UART_FramingError A framing error occurred while receiving data.
 * retval kStatus_UART_ParityError A parity error occurred while receiving data.
 * retval kStatus_UART_Timeout Transmission timed out and was aborted.
 * retval kStatus_Success Successfully received all data.
 */
status_t UART_ReadBlocking(UART_Type *base, uint8_t *data, size_t length)
{
    assert(data != NULL);

    status_t status = kStatus_Success;
    uint32_t statusFlag;
#if UART_RETRY_TIMES
    uint32_t waitTimes;
#endif

    while (length-- != 0U)
    {
#if UART_RETRY_TIMES
        waitTimes = UART_RETRY_TIMES;
#endif
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
        while (base->RCFIFO == 0U)
#else
        while ((base->S1 & UART_S1_RDRF_MASK) == 0U)
#endif
        {
#if UART_RETRY_TIMES
            if (0U == --waitTimes)
            {
                status = kStatus_LPUART_Timeout;
                break;
            }
#endif
            statusFlag = UART_GetStatusFlags(base);

            if (0U != (statusFlag & (uint32_t)kUART_RxOverrunFlag))
            {
                status = ((kStatus_Success == UART_ClearStatusFlags(base, (uint32_t)kUART_RxOverrunFlag)) ?
                              (status_t)(kStatus_UART_RxHardwareOverrun) :
                              (status_t)(kStatus_UART_FlagCannotClearManually));
                /* If the OR bit is set all the other error flags are prevented from setting,
                   no need to check other status flags. */
                break;
            }

            if (0U != (statusFlag & (uint32_t)kUART_ParityErrorFlag))
            {
                status = ((kStatus_Success == UART_ClearStatusFlags(base, (uint32_t)kUART_ParityErrorFlag)) ?
                              (status_t)(kStatus_UART_ParityError) :
                              (status_t)(kStatus_UART_FlagCannotClearManually));
            }

            if (0U != (statusFlag & (uint32_t)kUART_FramingErrorFlag))
            {
                status = ((kStatus_Success == UART_ClearStatusFlags(base, (uint32_t)kUART_FramingErrorFlag)) ?
                              (status_t)(kStatus_UART_FramingError) :
                              (status_t)(kStatus_UART_FlagCannotClearManually));
            }

            if (0U != (statusFlag & (uint32_t)kUART_NoiseErrorFlag))
            {
                status = ((kStatus_Success == UART_ClearStatusFlags(base, (uint32_t)kUART_NoiseErrorFlag)) ?
                              (status_t)(kStatus_UART_NoiseError) :
                              (status_t)(kStatus_UART_FlagCannotClearManually));
            }
            if (kStatus_Success != status)
            {
                break;
            }
        }
        if (kStatus_Success == status)
        {
            *(data++) = base->D;
        }
        else
        {
            break;
        }
    }

    return status;
}

static void UART_ReadNonBlocking(UART_Type *base, uint8_t *data, size_t length)
{
    assert(data != NULL);

    size_t i;

    /* The Non Blocking read data API assume user have ensured there is enough space in
    peripheral to write. */
    for (i = 0; i < length; i++)
    {
        data[i] = base->D;
    }
}

/*!
 * brief Initializes the UART handle.
 *
 * This function initializes the UART handle which can be used for other UART
 * transactional APIs. Usually, for a specified UART instance,
 * call this API once to get the initialized handle.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param callback The callback function.
 * param userData The parameter of the callback function.
 */
void UART_TransferCreateHandle(UART_Type *base,
                               uart_handle_t *handle,
                               uart_transfer_callback_t callback,
                               void *userData)
{
    assert(handle != NULL);

    uint32_t instance;

    /* Zero the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set the TX/RX state. */
    handle->rxState = (uint8_t)kUART_RxIdle;
    handle->txState = (uint8_t)kUART_TxIdle;

    /* Set the callback and user data. */
    handle->callback = callback;
    handle->userData = userData;

    /* Get instance from peripheral base address. */
    instance = UART_GetInstance(base);

    /* Save the handle in global variables to support the double weak mechanism. */
    s_uartHandle[instance] = handle;

    s_uartIsr = UART_TransferHandleIRQ;
    /* Enable interrupt in NVIC. */
    (void)EnableIRQ(s_uartIRQ[instance]);
}

/*!
 * brief Sets up the RX ring buffer.
 *
 * This function sets up the RX ring buffer to a specific UART handle.
 *
 * When the RX ring buffer is used, data received are stored into the ring buffer even when the
 * user doesn't call the UART_TransferReceiveNonBlocking() API. If data is already received
 * in the ring buffer, the user can get the received data from the ring buffer directly.
 *
 * note When using the RX ring buffer, one byte is reserved for internal use. In other
 * words, if p ringBufferSize is 32, only 31 bytes are used for saving data.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param ringBuffer Start address of the ring buffer for background receiving. Pass NULL to disable the ring buffer.
 * param ringBufferSize Size of the ring buffer.
 */
void UART_TransferStartRingBuffer(UART_Type *base, uart_handle_t *handle, uint8_t *ringBuffer, size_t ringBufferSize)
{
    assert(handle != NULL);
    assert(ringBuffer != NULL);

    /* Setup the ringbuffer address */
    handle->rxRingBuffer     = ringBuffer;
    handle->rxRingBufferSize = ringBufferSize;
    handle->rxRingBufferHead = 0U;
    handle->rxRingBufferTail = 0U;

    /* Disable and re-enable the global interrupt to protect the interrupt enable register during read-modify-wrte. */
    uint32_t irqMask = DisableGlobalIRQ();
    /* Enable the interrupt to accept the data when user need the ring buffer. */
    base->C2 |= (uint8_t)UART_C2_RIE_MASK;
    base->C3 |= ((uint8_t)UART_C3_ORIE_MASK | (uint8_t)UART_C3_FEIE_MASK);
    /* Enable parity error interrupt when parity mode is enable*/
    if (((uint8_t)UART_C1_PE_MASK & base->C1) != 0U)
    {
        base->C3 |= (uint8_t)UART_C3_PEIE_MASK;
    }
    EnableGlobalIRQ(irqMask);
}

/*!
 * brief Aborts the background transfer and uninstalls the ring buffer.
 *
 * This function aborts the background transfer and uninstalls the ring buffer.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 */
void UART_TransferStopRingBuffer(UART_Type *base, uart_handle_t *handle)
{
    assert(handle != NULL);

    if (handle->rxState == (uint8_t)kUART_RxIdle)
    {
        /* Disable and re-enable the global interrupt to protect the interrupt enable register during read-modify-wrte.
         */
        uint32_t irqMask = DisableGlobalIRQ();
        base->C2 &= ~(uint8_t)UART_C2_RIE_MASK;
        base->C3 &= ~((uint8_t)UART_C3_ORIE_MASK | (uint8_t)UART_C3_FEIE_MASK);
        /* Disable parity error interrupt when parity mode is enable*/
        if (((uint8_t)UART_C1_PE_MASK & base->C1) != 0U)
        {
            base->C3 &= ~(uint8_t)UART_C3_PEIE_MASK;
        }
        EnableGlobalIRQ(irqMask);
    }

    handle->rxRingBuffer     = NULL;
    handle->rxRingBufferSize = 0U;
    handle->rxRingBufferHead = 0U;
    handle->rxRingBufferTail = 0U;
}

/*!
 * brief Transmits a buffer of data using the interrupt method.
 *
 * This function sends data using an interrupt method. This is a non-blocking function, which
 * returns directly without waiting for all data to be written to the TX register. When
 * all data is written to the TX register in the ISR, the UART driver calls the callback
 * function and passes the ref kStatus_UART_TxIdle as status parameter.
 *
 * note The kStatus_UART_TxIdle is passed to the upper layer when all data is written
 * to the TX register. However, it does not ensure that all data is sent out. Before disabling the TX,
 * check the kUART_TransmissionCompleteFlag to ensure that the TX is finished.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param xfer UART transfer structure. See  #uart_transfer_t.
 * retval kStatus_Success Successfully start the data transmission.
 * retval kStatus_UART_TxBusy Previous transmission still not finished; data not all written to TX register yet.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_TransferSendNonBlocking(UART_Type *base, uart_handle_t *handle, uart_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(xfer != NULL);
    assert(xfer->dataSize != 0U);
    assert(xfer->txData != NULL);

    status_t status;

    /* Return error if current TX busy. */
    if ((uint8_t)kUART_TxBusy == handle->txState)
    {
        status = kStatus_UART_TxBusy;
    }
    else
    {
        handle->txData        = xfer->txData;
        handle->txDataSize    = xfer->dataSize;
        handle->txDataSizeAll = xfer->dataSize;
        handle->txState       = (uint8_t)kUART_TxBusy;

        /* Disable and re-enable the global interrupt to protect the interrupt enable register during read-modify-wrte.
         */
        uint32_t irqMask = DisableGlobalIRQ();
        /* Enable transmitter interrupt. */
        base->C2 |= (uint8_t)UART_C2_TIE_MASK;
        EnableGlobalIRQ(irqMask);

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Aborts the interrupt-driven data transmit.
 *
 * This function aborts the interrupt-driven data sending. The user can get the remainBytes to find out
 * how many bytes are not sent out.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 */
void UART_TransferAbortSend(UART_Type *base, uart_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable and re-enable the global interrupt to protect the interrupt enable register during read-modify-wrte. */
    uint32_t irqMask = DisableGlobalIRQ();
    base->C2 &= ~((uint8_t)UART_C2_TIE_MASK | (uint8_t)UART_C2_TCIE_MASK);
    EnableGlobalIRQ(irqMask);

    handle->txDataSize = 0;
    handle->txState    = (uint8_t)kUART_TxIdle;
}

/*!
 * brief Gets the number of bytes sent out to bus.
 *
 * This function gets the number of bytes sent out to bus by using the interrupt method.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param count Send bytes count.
 * retval kStatus_NoTransferInProgress No send in progress.
 * retval kStatus_InvalidArgument The parameter is invalid.
 * retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t UART_TransferGetSendCount(UART_Type *base, uart_handle_t *handle, uint32_t *count)
{
    assert(handle != NULL);
    assert(count != NULL);

    if ((uint8_t)kUART_TxIdle == handle->txState)
    {
        return kStatus_NoTransferInProgress;
    }
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
    *count = handle->txDataSizeAll - handle->txDataSize - base->TCFIFO;
#else
    if ((base->S1 & (uint8_t)kUART_TxDataRegEmptyFlag) != 0U)
    {
        *count = handle->txDataSizeAll - handle->txDataSize;
    }
    else
    {
        *count = handle->txDataSizeAll - handle->txDataSize - 1U;
    }
#endif /* FSL_FEATURE_UART_HAS_FIFO */

    return kStatus_Success;
}

/*!
 * brief Receives a buffer of data using an interrupt method.
 *
 * This function receives data using an interrupt method. This is a non-blocking function, which
 *  returns without waiting for all data to be received.
 * If the RX ring buffer is used and not empty, the data in the ring buffer is copied and
 * the parameter p receivedBytes shows how many bytes are copied from the ring buffer.
 * After copying, if the data in the ring buffer is not enough to read, the receive
 * request is saved by the UART driver. When the new data arrives, the receive request
 * is serviced first. When all data is received, the UART driver notifies the upper layer
 * through a callback function and passes the status parameter ref kStatus_UART_RxIdle.
 * For example, the upper layer needs 10 bytes but there are only 5 bytes in the ring buffer.
 * The 5 bytes are copied to the xfer->data and this function returns with the
 * parameter p receivedBytes set to 5. For the left 5 bytes, newly arrived data is
 * saved from the xfer->data[5]. When 5 bytes are received, the UART driver notifies the upper layer.
 * If the RX ring buffer is not enabled, this function enables the RX and RX interrupt
 * to receive data to the xfer->data. When all data is received, the upper layer is notified.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param xfer UART transfer structure, see #uart_transfer_t.
 * param receivedBytes Bytes received from the ring buffer directly.
 * retval kStatus_Success Successfully queue the transfer into transmit queue.
 * retval kStatus_UART_RxBusy Previous receive request is not finished.
 * retval kStatus_InvalidArgument Invalid argument.
 */
status_t UART_TransferReceiveNonBlocking(UART_Type *base,
                                         uart_handle_t *handle,
                                         uart_transfer_t *xfer,
                                         size_t *receivedBytes)
{
    assert(handle != NULL);
    assert(xfer != NULL);
    assert(xfer->rxData != NULL);
    assert(xfer->dataSize != 0U);

    uint32_t i;
    status_t status;
    /* How many bytes to copy from ring buffer to user memory. */
    size_t bytesToCopy = 0U;
    /* How many bytes to receive. */
    size_t bytesToReceive;
    /* How many bytes currently have received. */
    size_t bytesCurrentReceived;
    uint32_t irqMask;

    /* How to get data:
       1. If RX ring buffer is not enabled, then save xfer->data and xfer->dataSize
          to uart handle, enable interrupt to store received data to xfer->data. When
          all data received, trigger callback.
       2. If RX ring buffer is enabled and not empty, get data from ring buffer first.
          If there are enough data in ring buffer, copy them to xfer->data and return.
          If there are not enough data in ring buffer, copy all of them to xfer->data,
          save the xfer->data remained empty space to uart handle, receive data
          to this empty space and trigger callback when finished. */

    if ((uint8_t)kUART_RxBusy == handle->rxState)
    {
        status = kStatus_UART_RxBusy;
    }
    else
    {
        bytesToReceive       = xfer->dataSize;
        bytesCurrentReceived = 0U;

        /* If RX ring buffer is used. */
        if (handle->rxRingBuffer != NULL)
        {
            /* Disable and re-enable the global interrupt to protect the interrupt enable register during
             * read-modify-wrte. */
            irqMask = DisableGlobalIRQ();
            /* Disable UART RX IRQ, protect ring buffer. */
            base->C2 &= ~(uint8_t)UART_C2_RIE_MASK;
            EnableGlobalIRQ(irqMask);

            /* How many bytes in RX ring buffer currently. */
            bytesToCopy = UART_TransferGetRxRingBufferLength(handle);

            if (bytesToCopy != 0U)
            {
                bytesToCopy = MIN(bytesToReceive, bytesToCopy);

                bytesToReceive -= bytesToCopy;

                /* Copy data from ring buffer to user memory. */
                for (i = 0U; i < bytesToCopy; i++)
                {
                    xfer->rxData[bytesCurrentReceived++] = handle->rxRingBuffer[handle->rxRingBufferTail];

                    /* Wrap to 0. Not use modulo (%) because it might be large and slow. */
                    if ((size_t)handle->rxRingBufferTail + 1U == handle->rxRingBufferSize)
                    {
                        handle->rxRingBufferTail = 0U;
                    }
                    else
                    {
                        handle->rxRingBufferTail++;
                    }
                }
            }

            /* If ring buffer does not have enough data, still need to read more data. */
            if (bytesToReceive != 0U)
            {
                /* No data in ring buffer, save the request to UART handle. */
                handle->rxData        = xfer->rxData + bytesCurrentReceived;
                handle->rxDataSize    = bytesToReceive;
                handle->rxDataSizeAll = xfer->dataSize;
                handle->rxState       = (uint8_t)kUART_RxBusy;
            }

            /* Disable and re-enable the global interrupt to protect the interrupt enable register during
             * read-modify-wrte. */
            irqMask = DisableGlobalIRQ();
            /* Re-enable UART RX IRQ. */
            base->C2 |= (uint8_t)UART_C2_RIE_MASK;
            EnableGlobalIRQ(irqMask);

            /* Call user callback since all data are received. */
            if (0U == bytesToReceive)
            {
                if (handle->callback != NULL)
                {
                    handle->callback(base, handle, kStatus_UART_RxIdle, handle->userData);
                }
            }
        }
        /* Ring buffer not used. */
        else
        {
            handle->rxData        = xfer->rxData + bytesCurrentReceived;
            handle->rxDataSize    = bytesToReceive;
            handle->rxDataSizeAll = bytesToReceive;
            handle->rxState       = (uint8_t)kUART_RxBusy;

            /* Disable and re-enable the global interrupt to protect the interrupt enable register during
             * read-modify-wrte. */
            irqMask = DisableGlobalIRQ();
            /* Enable RX/Rx overrun/framing error/idle line interrupt. */
            base->C2 |= ((uint8_t)UART_C2_RIE_MASK | (uint8_t)UART_C2_ILIE_MASK);
            base->C3 |= ((uint8_t)UART_C3_ORIE_MASK | (uint8_t)UART_C3_FEIE_MASK);

            /* Enable parity error interrupt when parity mode is enable*/
            if (((uint8_t)UART_C1_PE_MASK & base->C1) != 0U)
            {
                base->C3 |= (uint8_t)UART_C3_PEIE_MASK;
            }
            EnableGlobalIRQ(irqMask);
        }

        /* Return the how many bytes have read. */
        if (receivedBytes != NULL)
        {
            *receivedBytes = bytesCurrentReceived;
        }

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Aborts the interrupt-driven data receiving.
 *
 * This function aborts the interrupt-driven data receiving. The user can get the remainBytes to know
 * how many bytes are not received yet.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 */
void UART_TransferAbortReceive(UART_Type *base, uart_handle_t *handle)
{
    assert(handle != NULL);

    /* Only abort the receive to handle->rxData, the RX ring buffer is still working. */
    if (NULL == handle->rxRingBuffer)
    {
        /* Disable and re-enable the global interrupt to protect the interrupt enable register during read-modify-wrte.
         */
        uint32_t irqMask = DisableGlobalIRQ();
        /* Disable RX interrupt. */
        base->C2 &= ~((uint8_t)UART_C2_RIE_MASK | (uint8_t)UART_C2_ILIE_MASK);
        base->C3 &= ~((uint8_t)UART_C3_ORIE_MASK | (uint8_t)UART_C3_FEIE_MASK);
        /* Disable parity error interrupt when parity mode is enable*/
        if (((uint8_t)UART_C1_PE_MASK & base->C1) != 0U)
        {
            base->C3 &= ~(uint8_t)UART_C3_PEIE_MASK;
        }
        EnableGlobalIRQ(irqMask);
    }

    handle->rxDataSize = 0U;
    handle->rxState    = (uint8_t)kUART_RxIdle;
}

/*!
 * brief Gets the number of bytes that have been received.
 *
 * This function gets the number of bytes that have been received.
 *
 * param base UART peripheral base address.
 * param handle UART handle pointer.
 * param count Receive bytes count.
 * retval kStatus_NoTransferInProgress No receive in progress.
 * retval kStatus_InvalidArgument Parameter is invalid.
 * retval kStatus_Success Get successfully through the parameter \p count;
 */
status_t UART_TransferGetReceiveCount(UART_Type *base, uart_handle_t *handle, uint32_t *count)
{
    assert(handle != NULL);
    assert(count != NULL);

    if ((uint8_t)kUART_RxIdle == handle->rxState)
    {
        return kStatus_NoTransferInProgress;
    }

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    *count = handle->rxDataSizeAll - handle->rxDataSize;

    return kStatus_Success;
}

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
status_t UART_EnableTxFIFO(UART_Type *base, bool enable)
{
    uint8_t sfifo = 0;
    uint8_t temp  = 0;

    sfifo = base->SFIFO;
    temp  = base->C2 & (UART_C2_RE_MASK | UART_C2_TE_MASK);
    /* The Tx FIFO must be empty */
    if ((sfifo & UART_SFIFO_TXEMPT_MASK) == UART_SFIFO_TXEMPT_MASK)
    {
        /* Disable UART TX RX before setting */
        base->C2 &= ~((uint8_t)UART_C2_TE_MASK | (uint8_t)UART_C2_RE_MASK);
        /* Flush FIFO */
        base->CFIFO |= (UART_CFIFO_TXFLUSH_MASK | UART_CFIFO_RXFLUSH_MASK);

        if (enable)
        {
            base->PFIFO |= (uint8_t)UART_PFIFO_TXFE_MASK;
        }
        else
        {
            base->PFIFO &= ~(uint8_t)UART_PFIFO_TXFE_MASK;
        }

        /* Flush FIFO */
        base->CFIFO |= (UART_CFIFO_TXFLUSH_MASK | UART_CFIFO_RXFLUSH_MASK);
        base->C2 |= temp;
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}

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
status_t UART_EnableRxFIFO(UART_Type *base, bool enable)
{
    uint8_t sfifo = 0;
    uint8_t temp  = 0;

    sfifo = base->SFIFO;
    temp  = base->C2 & ((uint8_t)UART_C2_RE_MASK | (uint8_t)UART_C2_TE_MASK);
    /* The Rx FIFO must be empty */
    if ((sfifo & UART_SFIFO_RXEMPT_MASK) == UART_SFIFO_RXEMPT_MASK)
    {
        /* Disable UART TX RX before setting */
        base->C2 &= ~((uint8_t)UART_C2_TE_MASK | (uint8_t)UART_C2_RE_MASK);
        /* Flush FIFO */
        base->CFIFO |= (UART_CFIFO_TXFLUSH_MASK | UART_CFIFO_RXFLUSH_MASK);

        if (enable)
        {
            base->PFIFO |= (uint8_t)UART_PFIFO_RXFE_MASK;
        }
        else
        {
            base->PFIFO &= ~(uint8_t)UART_PFIFO_RXFE_MASK;
        }
        /* Flush FIFO */
        base->CFIFO |= (UART_CFIFO_TXFLUSH_MASK | UART_CFIFO_RXFLUSH_MASK);
        base->C2 |= temp;
        return kStatus_Success;
    }
    else
    {
        return kStatus_Fail;
    }
}
#endif /* FSL_FEATURE_UART_HAS_FIFO */

/*!
 * brief UART IRQ handle function.
 *
 * This function handles the UART transmit and receive IRQ request.
 *
 * param base UART peripheral base address.
 * param irqHandle UART handle pointer.
 */
void UART_TransferHandleIRQ(UART_Type *base, void *irqHandle)
{
    assert(irqHandle != NULL);

    uint8_t count;
    uint8_t tempCount;
    uint32_t status = UART_GetStatusFlags(base);
    uint8_t tmpdata;
    uint32_t irqMask;
    uart_handle_t *handle = (uart_handle_t *)irqHandle;

    /* If RX framing error */
    if (((uint32_t)kUART_FramingErrorFlag & status) != 0U)
    {
        /* Read base->D to clear framing error flag, otherwise the RX does not work. */
        while ((base->S1 & UART_S1_RDRF_MASK) != 0U)
        {
            (void)base->D;
        }
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
        /* Flush FIFO date, otherwise FIFO pointer will be in unknown state. */
        base->CFIFO |= UART_CFIFO_RXFLUSH_MASK;
#endif

        handle->rxState    = (uint8_t)kUART_RxFramingError;
        handle->rxDataSize = 0U;
        /* Trigger callback. */
        if (handle->callback != NULL)
        {
            handle->callback(base, handle, kStatus_UART_FramingError, handle->userData);
        }
    }

    /* If RX parity error */
    if (((uint32_t)kUART_ParityErrorFlag & status) != 0U)
    {
        /* Read base->D to clear parity error flag, otherwise the RX does not work. */
        while ((base->S1 & UART_S1_RDRF_MASK) != 0U)
        {
            (void)base->D;
        }
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
        /* Flush FIFO date, otherwise FIFO pointer will be in unknown state. */
        base->CFIFO |= UART_CFIFO_RXFLUSH_MASK;
#endif

        handle->rxState    = (uint8_t)kUART_RxParityError;
        handle->rxDataSize = 0U;
        /* Trigger callback. */
        if (handle->callback != NULL)
        {
            handle->callback(base, handle, kStatus_UART_ParityError, handle->userData);
        }
    }

    /* If RX overrun. */
    if (((uint32_t)kUART_RxOverrunFlag & status) != 0U)
    {
        /* Read base->D to clear overrun flag, otherwise the RX does not work. */
        while ((base->S1 & UART_S1_RDRF_MASK) != 0U)
        {
            (void)base->D;
        }
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
        /* Flush FIFO date, otherwise FIFO pointer will be in unknown state. */
        base->CFIFO |= UART_CFIFO_RXFLUSH_MASK;
#endif
        /* Trigger callback. */
        if (handle->callback != NULL)
        {
            handle->callback(base, handle, kStatus_UART_RxHardwareOverrun, handle->userData);
        }
    }

    /* If IDLE line was detected. */
    if ((((uint32_t)kUART_IdleLineFlag & status) != 0U) && ((UART_C2_ILIE_MASK & base->C2) != 0U))
    {
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
        /* If still some data in the FIFO, read out these data to user data buffer. */
        count = base->RCFIFO;
        /* If handle->rxDataSize is not 0, first save data to handle->rxData. */
        while ((count != 0U) && (handle->rxDataSize != 0U))
        {
            tempCount = (uint8_t)MIN(handle->rxDataSize, (uint32_t)count);

            /* Using non block API to read the data from the registers. */
            UART_ReadNonBlocking(base, handle->rxData, tempCount);
            handle->rxData += tempCount;
            handle->rxDataSize -= tempCount;
            count -= tempCount;

            /* If all the data required for upper layer is ready, trigger callback. */
            if (0U == handle->rxDataSize)
            {
                handle->rxState = (uint8_t)kUART_RxIdle;

                /* Disable and re-enable the global interrupt to protect the interrupt enable register during
                 * read-modify-wrte. */
                irqMask = DisableGlobalIRQ();
                /* Disable RX interrupt/overrun interrupt/fram error/idle line detected interrupt */
                base->C2 &= ~(uint8_t)UART_C2_RIE_MASK;
                base->C3 &= ~((uint8_t)UART_C3_ORIE_MASK | (uint8_t)UART_C3_FEIE_MASK);
                /* Disable parity error interrupt when parity mode is enabled */
                if (((uint8_t)UART_C1_PE_MASK & base->C1) != 0U)
                {
                    base->C3 &= ~(uint8_t)UART_C3_PEIE_MASK;
                }
                EnableGlobalIRQ(irqMask);

                if (handle->callback != NULL)
                {
                    handle->callback(base, handle, kStatus_UART_RxIdle, handle->userData);
                }
            }
        }
#endif
        /* To clear IDLE, read UART status S1 with IDLE set and then read D.*/
        while ((UART_S1_IDLE_MASK & base->S1) != 0U)
        {
            (void)base->D;
        }
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
        /* Flush FIFO date, otherwise FIFO pointer will be in unknown state. */
        base->CFIFO |= UART_CFIFO_RXFLUSH_MASK;
#endif
        /* If rxDataSize is 0, disable idle line interrupt.*/
        if (0U == (handle->rxDataSize))
        {
            /* Disable and re-enable the global interrupt to protect the interrupt enable register during
             * read-modify-wrte. */
            irqMask = DisableGlobalIRQ();
            base->C2 &= ~(uint8_t)UART_C2_ILIE_MASK;
            EnableGlobalIRQ(irqMask);
        }
        /* If callback is not NULL and rxDataSize is not 0. */
        if ((handle->callback != NULL) && (handle->rxDataSize != 0U))
        {
            handle->callback(base, handle, kStatus_UART_IdleLineDetected, handle->userData);
        }
    }
    /* Receive data register full */
    if ((((uint32_t)kUART_RxDataRegFullFlag & status) != 0U) && ((UART_C2_RIE_MASK & base->C2) != 0U))
    {
/* Get the size that can be stored into buffer for this interrupt. */
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
        count = base->RCFIFO;
#else
        count = 1;
#endif

        /* If handle->rxDataSize is not 0, first save data to handle->rxData. */
        while ((count != 0U) && (handle->rxDataSize != 0U))
        {
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
            tempCount = (uint8_t)MIN(handle->rxDataSize, (uint32_t)count);
#else
            tempCount = 1;
#endif

            /* Using non block API to read the data from the registers. */
            UART_ReadNonBlocking(base, handle->rxData, tempCount);
            handle->rxData += tempCount;
            handle->rxDataSize -= tempCount;
            count -= tempCount;

            /* If all the data required for upper layer is ready, trigger callback. */
            if (0U == handle->rxDataSize)
            {
                handle->rxState = (uint8_t)kUART_RxIdle;

                if (handle->callback != NULL)
                {
                    handle->callback(base, handle, kStatus_UART_RxIdle, handle->userData);
                }
            }
        }

        /* If use RX ring buffer, receive data to ring buffer. */
        if (handle->rxRingBuffer != NULL)
        {
            while (0U != count--)
            {
                /* If RX ring buffer is full, trigger callback to notify over run. */
                if (UART_TransferIsRxRingBufferFull(handle))
                {
                    if (handle->callback != NULL)
                    {
                        handle->callback(base, handle, kStatus_UART_RxRingBufferOverrun, handle->userData);
                    }
                }

                /* If ring buffer is still full after callback function, the oldest data is overridden. */
                if (UART_TransferIsRxRingBufferFull(handle))
                {
                    /* Increase handle->rxRingBufferTail to make room for new data. */
                    if ((size_t)handle->rxRingBufferTail + 1U == handle->rxRingBufferSize)
                    {
                        handle->rxRingBufferTail = 0U;
                    }
                    else
                    {
                        handle->rxRingBufferTail++;
                    }
                }

                /* Read data. */
                tmpdata                                        = base->D;
                handle->rxRingBuffer[handle->rxRingBufferHead] = tmpdata;

                /* Increase handle->rxRingBufferHead. */
                if ((size_t)handle->rxRingBufferHead + 1U == handle->rxRingBufferSize)
                {
                    handle->rxRingBufferHead = 0U;
                }
                else
                {
                    handle->rxRingBufferHead++;
                }
            }
        }

        else if (0U == handle->rxDataSize)
        {
            /* Disable and re-enable the global interrupt to protect the interrupt enable register during
             * read-modify-wrte. */
            irqMask = DisableGlobalIRQ();
            /* Disable RX interrupt/overrun interrupt/fram error/idle line detected interrupt */
            base->C2 &= ~(uint8_t)UART_C2_RIE_MASK;
            base->C3 &= ~((uint8_t)UART_C3_ORIE_MASK | (uint8_t)UART_C3_FEIE_MASK);
            /* Disable parity error interrupt when parity mode is enabled */
            if (((uint8_t)UART_C1_PE_MASK & base->C1) != 0U)
            {
                base->C3 &= ~(uint8_t)UART_C3_PEIE_MASK;
            }
            EnableGlobalIRQ(irqMask);
        }
        else
        {
        }
    }

    /* If framing error or parity error happened, stop the RX interrupt when use no ring buffer */
    if (((handle->rxState == (uint8_t)kUART_RxFramingError) || (handle->rxState == (uint8_t)kUART_RxParityError)) &&
        (NULL == handle->rxRingBuffer))
    {
        /* Disable and re-enable the global interrupt to protect the interrupt enable register during read-modify-wrte.
         */
        irqMask = DisableGlobalIRQ();
        /* Enable RX/Rx overrun/framing error/idle line interrupt. */
        base->C2 |= ((uint8_t)UART_C2_RIE_MASK | (uint8_t)UART_C2_ILIE_MASK);
        base->C3 |= ((uint8_t)UART_C3_ORIE_MASK | (uint8_t)UART_C3_FEIE_MASK);

        /* Enable parity error interrupt when parity mode is enable*/
        if (((uint8_t)UART_C1_PE_MASK & base->C1) != 0U)
        {
            base->C3 |= (uint8_t)UART_C3_PEIE_MASK;
        }
        EnableGlobalIRQ(irqMask);
    }

    /* Send data register empty and the interrupt is enabled. */
    if ((((uint32_t)kUART_TxDataRegEmptyFlag & status) != 0U) && ((base->C2 & UART_C2_TIE_MASK) != 0U))
    {
/* Get the bytes that available at this moment. */
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
        count = (uint8_t)FSL_FEATURE_UART_FIFO_SIZEn(base) - base->TCFIFO;
#else
        count = 1;
#endif

        while ((count != 0U) && (handle->txDataSize != 0U))
        {
#if defined(FSL_FEATURE_UART_HAS_FIFO) && FSL_FEATURE_UART_HAS_FIFO
            tempCount = (uint8_t)MIN(handle->txDataSize, (uint32_t)count);
#else
            tempCount = 1;
#endif

            /* Using non block API to write the data to the registers. */
            UART_WriteNonBlocking(base, handle->txData, tempCount);
            handle->txData += tempCount;
            handle->txDataSize -= tempCount;
            count -= tempCount;

            /* If all the data are written to data register, TX finished. */
            if (0U == handle->txDataSize)
            {
                /* Disable and re-enable the global interrupt to protect the interrupt enable register during
                 * read-modify-wrte. */
                irqMask = DisableGlobalIRQ();
                /* Disable TX register empty interrupt and enable transmission complete interrupt. */
                base->C2 = (base->C2 & ~(uint8_t)UART_C2_TIE_MASK) | (uint8_t)UART_C2_TCIE_MASK;
                EnableGlobalIRQ(irqMask);
            }
        }
    }

    /* Transmission complete and the interrupt is enabled. */
    if ((0U != ((uint32_t)kUART_TransmissionCompleteFlag & status)) && (0U != (base->C2 & UART_C2_TCIE_MASK)))
    {
        /* Set txState to idle only when all data has been sent out to bus. */
        handle->txState = (uint8_t)kUART_TxIdle;

        /* Disable and re-enable the global interrupt to protect the interrupt enable register during read-modify-wrte.
         */
        irqMask = DisableGlobalIRQ();
        /* Disable transmission complete interrupt. */
        base->C2 &= ~(uint8_t)UART_C2_TCIE_MASK;
        EnableGlobalIRQ(irqMask);

        /* Trigger callback. */
        if (handle->callback != NULL)
        {
            handle->callback(base, handle, kStatus_UART_TxIdle, handle->userData);
        }
    }
}

/*!
 * brief UART Error IRQ handle function.
 *
 * This function handles the UART error IRQ request.
 *
 * param base UART peripheral base address.
 * param irqHandle UART handle pointer.
 */
void UART_TransferHandleErrorIRQ(UART_Type *base, void *irqHandle)
{
    /* To be implemented by User. */
}

#if defined(FSL_FEATURE_UART_HAS_SHARED_IRQ0_IRQ1_IRQ2_IRQ3) && FSL_FEATURE_UART_HAS_SHARED_IRQ0_IRQ1_IRQ2_IRQ3
void UART0_UART1_UART2_UART3_DriverIRQHandler(void);
void UART0_UART1_UART2_UART3_DriverIRQHandler(void)
{
    for (uint32_t instance = 0U; instance < 4U; instance++)
    {
        if (s_uartHandle[instance] != NULL)
        {
            s_uartIsr(s_uartBases[instance], s_uartHandle[instance]);
        }
    }
}
#else
#if defined(FSL_FEATURE_UART_HAS_SHARED_IRQ0_IRQ1) && FSL_FEATURE_UART_HAS_SHARED_IRQ0_IRQ1
void UART0_UART1_DriverIRQHandler(void);
void UART0_UART1_DriverIRQHandler(void)
{
    for (uint32_t instance = 0U; instance < 2U; instance++)
    {
        if (s_uartHandle[instance] != NULL)
        {
            s_uartIsr(s_uartBases[instance], s_uartHandle[instance]);
        }
    }
}
#else /* FSL_FEATURE_UART_HAS_SHARED_IRQ0_IRQ1 */
#if defined(UART0)
#if ((!(defined(FSL_FEATURE_SOC_LPSCI_COUNT))) || \
     ((defined(FSL_FEATURE_SOC_LPSCI_COUNT)) && (FSL_FEATURE_SOC_LPSCI_COUNT == 0)))
void UART0_DriverIRQHandler(void);
void UART0_DriverIRQHandler(void)
{
    s_uartIsr(UART0, s_uartHandle[0]);
    SDK_ISR_EXIT_BARRIER;
}

void UART0_RX_TX_DriverIRQHandler(void);
void UART0_RX_TX_DriverIRQHandler(void)
{
    UART0_DriverIRQHandler();
    SDK_ISR_EXIT_BARRIER;
}
#endif /* FSL_FEATURE_SOC_LPSCI_COUNT */
#endif /* UART0 */

#if defined(UART1)
void UART1_DriverIRQHandler(void);
void UART1_DriverIRQHandler(void)
{
    s_uartIsr(UART1, s_uartHandle[1]);
    SDK_ISR_EXIT_BARRIER;
}

void UART1_RX_TX_DriverIRQHandler(void);
void UART1_RX_TX_DriverIRQHandler(void)
{
    UART1_DriverIRQHandler();
    SDK_ISR_EXIT_BARRIER;
}
#endif /* UART1 */
#endif /* FSL_FEATURE_UART_HAS_SHARED_IRQ0_IRQ1 */

#if defined(FSL_FEATURE_UART_HAS_SHARED_IRQ2_IRQ3) && FSL_FEATURE_UART_HAS_SHARED_IRQ2_IRQ3
void UART2_UART3_DriverIRQHandler(void);
void UART2_UART3_DriverIRQHandler(void)
{
    for (uint32_t instance = 2U; instance < 4U; instance++)
    {
        if (s_uartHandle[instance] != NULL)
        {
            s_uartIsr(s_uartBases[instance], s_uartHandle[instance]);
        }
    }
}
#else /* FSL_FEATURE_UART_HAS_SHARED_IRQ2_IRQ3 */
#if defined(UART2)
void UART2_DriverIRQHandler(void);
void UART2_DriverIRQHandler(void)
{
    s_uartIsr(UART2, s_uartHandle[2]);
    SDK_ISR_EXIT_BARRIER;
}

void UART2_RX_TX_DriverIRQHandler(void);
void UART2_RX_TX_DriverIRQHandler(void)
{
    UART2_DriverIRQHandler();
    SDK_ISR_EXIT_BARRIER;
}
#endif /* UART2 */

#if defined(UART3)
void UART3_DriverIRQHandler(void);
void UART3_DriverIRQHandler(void)
{
    s_uartIsr(UART3, s_uartHandle[3]);
    SDK_ISR_EXIT_BARRIER;
}

void UART3_RX_TX_DriverIRQHandler(void);
void UART3_RX_TX_DriverIRQHandler(void)
{
    UART3_DriverIRQHandler();
    SDK_ISR_EXIT_BARRIER;
}
#endif /* UART3 */
#endif /* FSL_FEATURE_UART_HAS_SHARED_IRQ2_IRQ3 */
#endif /* FSL_FEATURE_UART_HAS_SHARED_IRQ0_IRQ1_IRQ2_IRQ3 */

#if defined(UART4)
void UART4_DriverIRQHandler(void);
void UART4_DriverIRQHandler(void)
{
    s_uartIsr(UART4, s_uartHandle[4]);
    SDK_ISR_EXIT_BARRIER;
}

void UART4_RX_TX_DriverIRQHandler(void);
void UART4_RX_TX_DriverIRQHandler(void)
{
    UART4_DriverIRQHandler();
    SDK_ISR_EXIT_BARRIER;
}
#endif

#if defined(UART5)
void UART5_DriverIRQHandler(void);
void UART5_DriverIRQHandler(void)
{
    s_uartIsr(UART5, s_uartHandle[5]);
    SDK_ISR_EXIT_BARRIER;
}

void UART5_RX_TX_DriverIRQHandler(void);
void UART5_RX_TX_DriverIRQHandler(void)
{
    UART5_DriverIRQHandler();
    SDK_ISR_EXIT_BARRIER;
}
#endif
