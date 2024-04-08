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

#include "fsl_uart.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* UART transfer state. */
enum _uart_tansfer_states
{
    kUART_TxIdle,         /* TX idle. */
    kUART_TxBusy,         /* TX busy. */
    kUART_RxIdle,         /* RX idle. */
    kUART_RxBusy,         /* RX busy. */
    kUART_RxFramingError, /* Rx framing error */
    kUART_RxParityError   /* Rx parity error */
};

/* Typedef for interrupt handler. */
typedef void (*uart_isr_t)(UART_Type *base, uart_handle_t *handle);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get the UART instance from peripheral base address.
 *
 * @param base UART peripheral base address.
 * @return UART instance.
 */
uint32_t UART_GetInstance(UART_Type *base);

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
 * @param data Start addresss of the buffer to store the received data.
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
 * @param data Start addresss of the data to write.
 * @param length Size of the buffer to be sent.
 */
static void UART_WriteNonBlocking(UART_Type *base, const uint8_t *data, size_t length);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* ARRAY of UART handle */
#if (defined(UART8))
#define UART_HANDLE_ARRAY_SIZE 8
#else /* UART8 */
#if (defined(UART7))
#define UART_HANDLE_ARRAY_SIZE 7
#else /* UART7 */
#if (defined(UART6))
#define UART_HANDLE_ARRAY_SIZE 6
#else /* UART6 */
#if (defined(UART5))
#define UART_HANDLE_ARRAY_SIZE 5
#else /* UART5 */
#if (defined(UART4))
#define UART_HANDLE_ARRAY_SIZE 4
#else /* UART4 */
#if (defined(UART3))
#define UART_HANDLE_ARRAY_SIZE 3
#else /* UART3 */
#if (defined(UART2))
#define UART_HANDLE_ARRAY_SIZE 2
#else /* UART2 */
#if (defined(UART1))
#define UART_HANDLE_ARRAY_SIZE 1
#else /* UART1 */
#error No UART instance.
#endif /* UART 1 */
#endif /* UART 2 */
#endif /* UART 3 */
#endif /* UART 4 */
#endif /* UART 5 */
#endif /* UART 6 */
#endif /* UART 7 */
#endif /* UART 8 */
static uart_handle_t *s_uartHandle[UART_HANDLE_ARRAY_SIZE];

/* Array of UART peripheral base address. */
static UART_Type *const s_uartBases[] = UART_BASE_PTRS;

/* Array of UART IRQ number. */
static const IRQn_Type s_uartIRQ[] = UART_IRQS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/* Array of UART clock name. */
static const clock_ip_name_t s_uartClock[] = UART_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/* UART ISR for transactional APIs. */
static uart_isr_t s_uartIsr;

/*******************************************************************************
 * Code
 ******************************************************************************/
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

size_t UART_TransferGetRxRingBufferLength(uart_handle_t *handle)
{
    assert(handle);

    size_t size;

    if (handle->rxRingBufferTail > handle->rxRingBufferHead)
    {
        size = (size_t)(handle->rxRingBufferHead + handle->rxRingBufferSize - handle->rxRingBufferTail);
    }
    else
    {
        size = (size_t)(handle->rxRingBufferHead - handle->rxRingBufferTail);
    }

    return size;
}

static bool UART_TransferIsRxRingBufferFull(uart_handle_t *handle)
{
    assert(handle);

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

status_t UART_Init(UART_Type *base, const uart_config_t *config, uint32_t srcClock_Hz)
{
    /* Check argument */
    assert(!((NULL == base) || (NULL == config) || (0U == srcClock_Hz)));

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Enable uart clock */
    CLOCK_EnableClock(s_uartClock[UART_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    /* Disable UART Module. */
    UART_Disable(base);
    /* Reset the transmit and receive state machines, all FIFOs and register
     * USR1, USR2, UBIR, UBMR, UBRC, URXD, UTXD and UTS[6-3]. */
    UART_SoftwareReset(base);

    /* Set UART Module Register content to default value */
    base->UCR1 = 0x0;
    base->UCR2 = UART_UCR2_SRST_MASK;
    base->UCR3 = UART_UCR3_DSR_MASK | UART_UCR3_DCD_MASK | UART_UCR3_RI_MASK;
    base->UCR4 = UART_UCR4_CTSTL(32);
    base->UFCR = UART_UFCR_TXTL(2) | UART_UFCR_RXTL(1);
    base->UESC = UART_UESC_ESC_CHAR(0x2B);
    base->UTIM = 0x0;
    base->ONEMS = 0x0;
    base->UTS = UART_UTS_TXEMPTY_MASK | UART_UTS_RXEMPTY_MASK;
    base->UMCR = 0x0;

    /* Set UART data word length, stop bit count, parity mode and communication
     * direction according to uart init struct, disable RTS hardware flow control.
     */
    base->UCR2 |=
        ((uint32_t)UART_UCR2_WS(config->dataBitsCount) | (uint32_t)UART_UCR2_STPB(config->stopBitCount) |
         (uint32_t)(((config->parityMode) << UART_UCR2_PROE_SHIFT) & (UART_UCR2_PREN_MASK | UART_UCR2_PROE_MASK)) |
         (uint32_t)UART_UCR2_TXEN(config->enableTx) | (uint32_t)UART_UCR2_RXEN(config->enableRx) | UART_UCR2_IRTS_MASK);

    /* For imx family device, UARTs are used in MUXED mode, so that this bit should always be set.*/
    if (FSL_FEATURE_IUART_RXDMUXSEL)
    {
        base->UCR3 |= UART_UCR3_RXDMUXSEL_MASK;
    }
    /* Set TX/RX fifo water mark */
    UART_SetTxFifoWatermark(base, config->txFifoWatermark);
    UART_SetRxFifoWatermark(base, config->rxFifoWatermark);

    if (config->enableAutoBaudRate)
    {
        /* Start automatic baud rate detection */
        UART_EnableAutoBaudRate(base, true);
    }
    else if (config->baudRate_Bps)
    {
        /* Stop automatic baud rate detection */
        UART_EnableAutoBaudRate(base, false);
        /* Set BaudRate according to uart initialize struct. Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1)) */
        if (kStatus_Success != UART_SetBaudRate(base, config->baudRate_Bps, srcClock_Hz))
        {
            return kStatus_UART_BaudrateNotSupport;
        }
    }
    else
    {
        /* Stop automatic baud rate detection */
        UART_EnableAutoBaudRate(base, false);
    }

    /* Enable UART module */
    UART_Enable(base);

    return kStatus_Success;
}

void UART_Deinit(UART_Type *base)
{
    /* Wait transmit FIFO buffer and shift register empty */
    while (UART_USR2_TXDC_MASK != (base->USR2 & UART_USR2_TXDC_MASK))
    {
    }
    /* Disable UART Module */
    UART_Disable(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    /* Disable uart clock */
    CLOCK_DisableClock(s_uartClock[UART_GetInstance(base)]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void UART_GetDefaultConfig(uart_config_t *config)
{
    assert(config);

    config->baudRate_Bps = 115200U;
    config->parityMode = kUART_ParityDisabled;
    config->dataBitsCount = kUART_EightDataBits;
    config->stopBitCount = kUART_OneStopBit;
    config->txFifoWatermark = 2;
    config->rxFifoWatermark = 1;
    config->enableAutoBaudRate = false;
    config->enableTx = false;
    config->enableRx = false;
}

/* This UART instantiation uses a slightly different baud rate calculation.
 * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1)).
 * To get a baud rate, three register need to be writen, UFCR,UBMR and UBIR
 * At first, find the approximately maximum divisor of src_Clock and baudRate_Bps.
 * If the numerator and denominator are larger then register maximum value(0xFFFF),
 * both of numerator and denominator will be divided by the same value, which
 * will ensure numerator and denominator range from 0~maximum value(0xFFFF).
 * Then calculate UFCR and UBIR value from numerator, and get UBMR value from denominator.
 */
status_t UART_SetBaudRate(UART_Type *base, uint32_t baudRate_Bps, uint32_t srcClock_Hz)
{
    uint32_t numerator = 0u;
    uint32_t denominator = 0U;
    uint32_t divisor = 0U;
    uint32_t refFreqDiv = 0U;
    uint32_t divider = 1U;
    uint64_t baudDiff = 0U;
    uint64_t tempNumerator = 0U;
    uint32_t tempDenominator = 0u;

    /* get the approximately maximum divisor */
    numerator = srcClock_Hz;
    denominator = baudRate_Bps << 4;
    divisor = 1;

    while (denominator != 0)
    {
        divisor = denominator;
        denominator = numerator % denominator;
        numerator = divisor;
    }

    numerator = srcClock_Hz / divisor;
    denominator = (baudRate_Bps << 4) / divisor;

    /* numerator ranges from 1 ~ 7 * 64k */
    /* denominator ranges from 1 ~ 64k */
    if ((numerator > (UART_UBIR_INC_MASK * 7)) || (denominator > UART_UBIR_INC_MASK))
    {
        uint32_t m = (numerator - 1) / (UART_UBIR_INC_MASK * 7) + 1;
        uint32_t n = (denominator - 1) / UART_UBIR_INC_MASK + 1;
        uint32_t max = m > n ? m : n;
        numerator /= max;
        denominator /= max;
        if (0 == numerator)
        {
            numerator = 1;
        }
        if (0 == denominator)
        {
            denominator = 1;
        }
    }
    divider = (numerator - 1) / UART_UBIR_INC_MASK + 1;

    switch (divider)
    {
        case 1:
            refFreqDiv = 0x05;
            break;
        case 2:
            refFreqDiv = 0x04;
            break;
        case 3:
            refFreqDiv = 0x03;
            break;
        case 4:
            refFreqDiv = 0x02;
            break;
        case 5:
            refFreqDiv = 0x01;
            break;
        case 6:
            refFreqDiv = 0x00;
            break;
        case 7:
            refFreqDiv = 0x06;
            break;
        default:
            refFreqDiv = 0x05;
            break;
    }
    /* Compare the difference between baudRate_Bps and calculated baud rate.
     * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1)).
     * baudDiff = (srcClock_Hz/divider)/( 16 * ((numerator / divider)/ denominator).
     */
    tempNumerator = srcClock_Hz;
    tempDenominator = (numerator << 4);
    divisor = 1;
    /* get the approximately maximum divisor */
    while (tempDenominator != 0)
    {
        divisor = tempDenominator;
        tempDenominator = tempNumerator % tempDenominator;
        tempNumerator = divisor;
    }
    tempNumerator = srcClock_Hz / divisor;
    tempDenominator = (numerator << 4) / divisor;
    baudDiff = (tempNumerator * denominator) / tempDenominator;
    baudDiff = (baudDiff >= baudRate_Bps) ? (baudDiff - baudRate_Bps) : (baudRate_Bps - baudDiff);

    if (baudDiff < (baudRate_Bps / 100) * 3)
    {
        base->UFCR &= ~UART_UFCR_RFDIV_MASK;
        base->UFCR |= UART_UFCR_RFDIV(refFreqDiv);
        base->UBIR = UART_UBIR_INC(denominator - 1);
        base->UBMR = UART_UBMR_MOD(numerator / divider - 1);
        base->ONEMS = UART_ONEMS_ONEMS(srcClock_Hz / (1000 * divider));

        return kStatus_Success;
    }
    else
    {
        return kStatus_UART_BaudrateNotSupport;
    }
}

void UART_EnableInterrupts(UART_Type *base, uint32_t mask)
{
    assert(0x3F3FF73FU & mask);

    if (0X3F & mask)
    {
        base->UCR1 |= ((mask << UART_UCR1_ADEN_SHIFT) & UART_UCR1_ADEN_MASK) |
                      (((mask >> 1) << UART_UCR1_TRDYEN_SHIFT) & UART_UCR1_TRDYEN_MASK) |
                      (((mask >> 2) << UART_UCR1_IDEN_SHIFT) & UART_UCR1_IDEN_MASK) |
                      (((mask >> 3) << UART_UCR1_RRDYEN_SHIFT) & UART_UCR1_RRDYEN_MASK) |
                      (((mask >> 4) << UART_UCR1_TXMPTYEN_SHIFT) & UART_UCR1_TXMPTYEN_MASK) |
                      (((mask >> 5) << UART_UCR1_RTSDEN_SHIFT) & UART_UCR1_RTSDEN_MASK);
    }
    if (0X700U & mask)
    {
        base->UCR2 |= (((mask >> 8) << UART_UCR2_ESCI_SHIFT) & UART_UCR2_ESCI_MASK) |
                      (((mask >> 9) << UART_UCR2_RTSEN_SHIFT) & UART_UCR2_RTSEN_MASK) |
                      (((mask >> 10) << UART_UCR2_ATEN_SHIFT) & UART_UCR2_ATEN_MASK);
    }
    if (0x3FF000 & mask)
    {
        base->UCR3 |= (((mask >> 12) << UART_UCR3_DTREN_SHIFT) & UART_UCR3_DTREN_MASK) |
                      (((mask >> 13) << UART_UCR3_PARERREN_SHIFT) & UART_UCR3_PARERREN_MASK) |
                      (((mask >> 14) << UART_UCR3_FRAERREN_SHIFT) & UART_UCR3_FRAERREN_MASK) |
                      (((mask >> 15) << UART_UCR3_DCD_SHIFT) & UART_UCR3_DCD_MASK) |
                      (((mask >> 16) << UART_UCR3_RI_SHIFT) & UART_UCR3_RI_MASK) |
                      (((mask >> 17) << UART_UCR3_RXDSEN_SHIFT) & UART_UCR3_RXDSEN_MASK) |
                      (((mask >> 18) << UART_UCR3_AIRINTEN_SHIFT) & UART_UCR3_AIRINTEN_MASK) |
                      (((mask >> 19) << UART_UCR3_AWAKEN_SHIFT) & UART_UCR3_AWAKEN_MASK) |
                      (((mask >> 20) << UART_UCR3_DTRDEN_SHIFT) & UART_UCR3_DTRDEN_MASK) |
                      (((mask >> 21) << UART_UCR3_ACIEN_SHIFT) & UART_UCR3_ACIEN_MASK);
    }
    if (0x3F000000 & mask)
    {
        base->UCR4 |= (((mask >> 24) << UART_UCR4_ENIRI_SHIFT) & UART_UCR4_ENIRI_MASK) |
                      (((mask >> 25) << UART_UCR4_WKEN_SHIFT) & UART_UCR4_WKEN_MASK) |
                      (((mask >> 26) << UART_UCR4_TCEN_SHIFT) & UART_UCR4_TCEN_MASK) |
                      (((mask >> 27) << UART_UCR4_BKEN_SHIFT) & UART_UCR4_BKEN_MASK) |
                      (((mask >> 28) << UART_UCR4_OREN_SHIFT) & UART_UCR4_OREN_MASK) |
                      (((mask >> 29) << UART_UCR4_DREN_SHIFT) & UART_UCR4_DREN_MASK);
    }
}

void UART_DisableInterrupts(UART_Type *base, uint32_t mask)
{
    assert(0x3F3FF73FU & mask);

    if (0X3F & mask)
    {
        base->UCR1 &= ~(((mask << UART_UCR1_ADEN_SHIFT) & UART_UCR1_ADEN_MASK) |
                        (((mask >> 1) << UART_UCR1_TRDYEN_SHIFT) & UART_UCR1_TRDYEN_MASK) |
                        (((mask >> 2) << UART_UCR1_IDEN_SHIFT) & UART_UCR1_IDEN_MASK) |
                        (((mask >> 3) << UART_UCR1_RRDYEN_SHIFT) & UART_UCR1_RRDYEN_MASK) |
                        (((mask >> 4) << UART_UCR1_TXMPTYEN_SHIFT) & UART_UCR1_TXMPTYEN_MASK) |
                        (((mask >> 5) << UART_UCR1_RTSDEN_SHIFT) & UART_UCR1_RTSDEN_MASK));
    }
    if (0X700U & mask)
    {
        base->UCR2 &= ~((((mask >> 8) << UART_UCR2_ESCI_SHIFT) & UART_UCR2_ESCI_MASK) |
                        (((mask >> 9) << UART_UCR2_RTSEN_SHIFT) & UART_UCR2_RTSEN_MASK) |
                        (((mask >> 10) << UART_UCR2_ATEN_SHIFT) & UART_UCR2_ATEN_MASK));
    }
    if (0x3FF000 & mask)
    {
        base->UCR3 &= ~((((mask >> 12) << UART_UCR3_DTREN_SHIFT) & UART_UCR3_DTREN_MASK) |
                        (((mask >> 13) << UART_UCR3_PARERREN_SHIFT) & UART_UCR3_PARERREN_MASK) |
                        (((mask >> 14) << UART_UCR3_FRAERREN_SHIFT) & UART_UCR3_FRAERREN_MASK) |
                        (((mask >> 15) << UART_UCR3_DCD_SHIFT) & UART_UCR3_DCD_MASK) |
                        (((mask >> 16) << UART_UCR3_RI_SHIFT) & UART_UCR3_RI_MASK) |
                        (((mask >> 17) << UART_UCR3_RXDSEN_SHIFT) & UART_UCR3_RXDSEN_MASK) |
                        (((mask >> 18) << UART_UCR3_AIRINTEN_SHIFT) & UART_UCR3_AIRINTEN_MASK) |
                        (((mask >> 19) << UART_UCR3_AWAKEN_SHIFT) & UART_UCR3_AWAKEN_MASK) |
                        (((mask >> 20) << UART_UCR3_DTRDEN_SHIFT) & UART_UCR3_DTRDEN_MASK) |
                        (((mask >> 21) << UART_UCR3_ACIEN_SHIFT) & UART_UCR3_ACIEN_MASK));
    }
    if (0x3F000000 & mask)
    {
        base->UCR4 &= ~((((mask >> 24) << UART_UCR4_ENIRI_SHIFT) & UART_UCR4_ENIRI_MASK) |
                        (((mask >> 25) << UART_UCR4_WKEN_SHIFT) & UART_UCR4_WKEN_MASK) |
                        (((mask >> 26) << UART_UCR4_TCEN_SHIFT) & UART_UCR4_TCEN_MASK) |
                        (((mask >> 27) << UART_UCR4_BKEN_SHIFT) & UART_UCR4_BKEN_MASK) |
                        (((mask >> 28) << UART_UCR4_OREN_SHIFT) & UART_UCR4_OREN_MASK) |
                        (((mask >> 29) << UART_UCR4_DREN_SHIFT) & UART_UCR4_DREN_MASK));
    }
}

uint32_t UART_GetEnabledInterrupts(UART_Type *base)
{
    assert(base);
    uint32_t temp = 0U;
    /* Get enabled interrupts from UCR1 */
    temp |= ((base->UCR1 & UART_UCR1_ADEN_MASK) >> UART_UCR1_ADEN_SHIFT) |
            (((base->UCR1 & UART_UCR1_TRDYEN_MASK) >> UART_UCR1_TRDYEN_SHIFT) << 1) |
            (((base->UCR1 & UART_UCR1_IDEN_MASK) >> UART_UCR1_IDEN_SHIFT) << 2) |
            (((base->UCR1 & UART_UCR1_RRDYEN_MASK) >> UART_UCR1_RRDYEN_SHIFT) << 3) |
            (((base->UCR1 & UART_UCR1_TXMPTYEN_MASK) >> UART_UCR1_TXMPTYEN_SHIFT) << 4) |
            (((base->UCR1 & UART_UCR1_RTSDEN_MASK) >> UART_UCR1_RTSDEN_SHIFT) << 5);
    /* Get enabled interrupts from UCR2 */
    temp |= (((base->UCR2 & UART_UCR2_ESCI_MASK) >> UART_UCR2_ESCI_SHIFT) << 8) |
            (((base->UCR2 & UART_UCR2_RTSEN_MASK) >> UART_UCR2_RTSEN_SHIFT) << 9) |
            (((base->UCR2 & UART_UCR2_ATEN_MASK) >> UART_UCR2_ATEN_SHIFT) << 10);
    /* Get enabled interrupts from UCR3 */
    temp |= (((base->UCR3 & UART_UCR3_DTREN_MASK) >> UART_UCR3_DTREN_SHIFT) << 12) |
            (((base->UCR3 & UART_UCR3_PARERREN_MASK) >> UART_UCR3_PARERREN_SHIFT) << 13) |
            (((base->UCR3 & UART_UCR3_FRAERREN_MASK) >> UART_UCR3_FRAERREN_SHIFT) << 14) |
            (((base->UCR3 & UART_UCR3_DCD_MASK) >> UART_UCR3_DCD_SHIFT) << 15) |
            (((base->UCR3 & UART_UCR3_RI_MASK) >> UART_UCR3_RI_SHIFT) << 16) |
            (((base->UCR3 & UART_UCR3_RXDSEN_MASK) >> UART_UCR3_RXDSEN_SHIFT) << 17) |
            (((base->UCR3 & UART_UCR3_AIRINTEN_MASK) >> UART_UCR3_AIRINTEN_SHIFT) << 18) |
            (((base->UCR3 & UART_UCR3_AWAKEN_MASK) >> UART_UCR3_AWAKEN_SHIFT) << 19) |
            (((base->UCR3 & UART_UCR3_DTRDEN_MASK) >> UART_UCR3_DTRDEN_SHIFT) << 20) |
            (((base->UCR3 & UART_UCR3_ACIEN_MASK) >> UART_UCR3_ACIEN_SHIFT) << 21);
    /* Get enabled interrupts from UCR4 */
    temp |= (((base->UCR4 & UART_UCR4_ENIRI_MASK) >> UART_UCR4_ENIRI_SHIFT) << 24) |
            (((base->UCR4 & UART_UCR4_WKEN_MASK) >> UART_UCR4_WKEN_SHIFT) << 25) |
            (((base->UCR4 & UART_UCR4_TCEN_MASK) >> UART_UCR4_TCEN_SHIFT) << 26) |
            (((base->UCR4 & UART_UCR4_BKEN_MASK) >> UART_UCR4_BKEN_SHIFT) << 27) |
            (((base->UCR4 & UART_UCR4_OREN_MASK) >> UART_UCR4_OREN_SHIFT) << 28) |
            (((base->UCR4 & UART_UCR4_DREN_MASK) >> UART_UCR4_DREN_SHIFT) << 29);

    return temp;
}

bool UART_GetStatusFlag(UART_Type *base, uint32_t flag)
{
    volatile uint32_t *uart_reg;

    uart_reg = (uint32_t *)((uint32_t)base + (flag >> 16));
    return (bool)(((*uart_reg) >> (flag & 0x1FU)) & 0x1U);
}

void UART_ClearStatusFlag(UART_Type *base, uint32_t flag)
{
    volatile uint32_t *uart_reg = 0;
    uint32_t uart_mask = 0;

    uart_reg = (uint32_t *)((uint32_t)base + (flag >> 16));
    uart_mask = (1U << (flag & 0x1FU));

    *uart_reg = uart_mask;
}

void UART_EnableDMA(UART_Type *base, uint32_t dmaSource, bool enable)
{
    volatile uint32_t *uart_reg = 0;
    uint32_t uart_mask = 0;

    uart_reg = (uint32_t *)((uint32_t)base + (dmaSource >> 16));
    uart_mask = (1U << (dmaSource & 0x1FU));
    if (enable)
    {
        *uart_reg |= uart_mask;
    }
    else
    {
        *uart_reg &= ~uart_mask;
    }
}

void UART_WriteBlocking(UART_Type *base, const uint8_t *data, size_t length)
{
    assert(data);

    while (length--)
    {
        /* Wait for TX fifo valid.
         * This API can only ensure that the data is written into the data buffer but can't
         * ensure all data in the data buffer are sent into the transmit shift buffer.
         */
        while (!(base->USR2 & UART_USR2_TXDC_MASK))
        {
        }
        UART_WriteByte(base, *(data++));
    }
}

status_t UART_ReadBlocking(UART_Type *base, uint8_t *data, size_t length)
{
    assert(data);

    while (length--)
    {
        /* Wait for receive data in URXD register is ready */
        while (!(base->USR2 & UART_USR2_RDR_MASK))
        {
            /* Parity error check for receiving character */
            if (base->USR1 & UART_USR1_PARITYERR_MASK)
            {
                UART_ClearStatusFlag(base, kUART_ParityErrorFlag);
                return kStatus_UART_ParityError;
            }
            /* Framing error check for receiving character */
            if (base->USR1 & UART_USR1_FRAMERR_MASK)
            {
                UART_ClearStatusFlag(base, kUART_FrameErrorFlag);
                return kStatus_UART_FramingError;
            }
            /* Over run check for receiving character */
            if (base->USR2 & UART_USR2_ORE_MASK)
            {
                UART_ClearStatusFlag(base, kUART_RxOverrunFlag);
                return kStatus_UART_RxHardwareOverrun;
            }
        }
        /* Read data from URXD */
        *(data++) = UART_ReadByte(base);
    }

    return kStatus_Success;
}

static void UART_WriteNonBlocking(UART_Type *base, const uint8_t *data, size_t length)
{
    assert(data);

    size_t i;

    /* The Non Blocking write data API assume user have ensured there is enough space in
     * peripheral to write. UTXD register holds the parallel transmit data inputs. In 7-bit mode,
     * D7 is ignored. In 8-bit mode, all bits are used.
     */
    for (i = 0; i < length; i++)
    {
        base->UTXD = data[i] & UART_UTXD_TX_DATA_MASK;
    }
}

static void UART_ReadNonBlocking(UART_Type *base, uint8_t *data, size_t length)
{
    assert(data);

    size_t i;

    /* The Non Blocking read data API assume user have ensured there is enough space in
     * peripheral to write. The URXD holds the received character,In 7-bit mode,
     * the most significant bit (MSB) is forced to 0.In 8-bit mode, all bits are active.
     */
    for (i = 0; i < length; i++)
    {
        data[i] = (uint8_t)((base->URXD & UART_URXD_RX_DATA_MASK) >> UART_URXD_RX_DATA_SHIFT);
    }
}

void UART_TransferCreateHandle(UART_Type *base,
                               uart_handle_t *handle,
                               uart_transfer_callback_t callback,
                               void *userData)
{
    assert(handle);

    uint32_t instance;

    /* Zero the handle. */
    memset(handle, 0, sizeof(*handle));

    /* Set the TX/RX state. */
    handle->rxState = kUART_RxIdle;
    handle->txState = kUART_TxIdle;

    /* Set the callback and user data. */
    handle->callback = callback;
    handle->userData = userData;

    /* Get instance from peripheral base address. */
    instance = UART_GetInstance(base);

    /* Save the handle in global variables to support the double weak mechanism. */
    s_uartHandle[instance - 1] = handle;

    s_uartIsr = UART_TransferHandleIRQ;

    /* Enable interrupt in NVIC. */
    EnableIRQ(s_uartIRQ[instance]);
}

void UART_TransferStartRingBuffer(UART_Type *base, uart_handle_t *handle, uint8_t *ringBuffer, size_t ringBufferSize)
{
    assert(handle);
    assert(ringBuffer);

    /* Setup the ringbuffer address */
    handle->rxRingBuffer = ringBuffer;
    handle->rxRingBufferSize = ringBufferSize;
    handle->rxRingBufferHead = 0U;
    handle->rxRingBufferTail = 0U;

    /* Enable the interrupt to accept the data when user need the ring buffer. */
    UART_EnableInterrupts(base, kUART_RxReadyEnable | kUART_AgingTimerEnable | kUART_RxOverrunEnable |
                                    kUART_ParityErrorEnable | kUART_FrameErrorEnable);
}

void UART_TransferStopRingBuffer(UART_Type *base, uart_handle_t *handle)
{
    assert(handle);

    if (handle->rxState == kUART_RxIdle)
    {
        UART_DisableInterrupts(base, kUART_RxReadyEnable | kUART_AgingTimerEnable | kUART_RxOverrunEnable |
                                         kUART_ParityErrorEnable | kUART_FrameErrorEnable);
    }

    handle->rxRingBuffer = NULL;
    handle->rxRingBufferSize = 0U;
    handle->rxRingBufferHead = 0U;
    handle->rxRingBufferTail = 0U;
}

status_t UART_TransferSendNonBlocking(UART_Type *base, uart_handle_t *handle, uart_transfer_t *xfer)
{
    assert(handle);
    assert(xfer);
    assert(xfer->dataSize);
    assert(xfer->data);

    status_t status;

    /* Return error if current TX busy. */
    if (kUART_TxBusy == handle->txState)
    {
        status = kStatus_UART_TxBusy;
    }
    else
    {
        handle->txData = xfer->data;
        handle->txDataSize = xfer->dataSize;
        handle->txDataSizeAll = xfer->dataSize;
        handle->txState = kUART_TxBusy;

        /* Enable transmiter interrupt. */
        UART_EnableInterrupts(base, kUART_TxReadyEnable);
        status = kStatus_Success;
    }

    return status;
}

void UART_TransferAbortSend(UART_Type *base, uart_handle_t *handle)
{
    assert(handle);

    UART_DisableInterrupts(base, kUART_TxEmptyEnable);

    handle->txDataSize = 0;
    handle->txState = kUART_TxIdle;
}

status_t UART_TransferGetSendCount(UART_Type *base, uart_handle_t *handle, uint32_t *count)
{
    assert(handle);
    assert(count);

    if (kUART_TxIdle == handle->txState)
    {
        return kStatus_NoTransferInProgress;
    }

    *count = handle->txDataSizeAll - handle->txDataSize;

    return kStatus_Success;
}

status_t UART_TransferReceiveNonBlocking(UART_Type *base,
                                         uart_handle_t *handle,
                                         uart_transfer_t *xfer,
                                         size_t *receivedBytes)
{
    assert(handle);
    assert(xfer);
    assert(xfer->data);
    assert(xfer->dataSize);

    uint32_t i;
    status_t status;
    /* How many bytes to copy from ring buffer to user memory. */
    size_t bytesToCopy = 0U;
    /* How many bytes to receive. */
    size_t bytesToReceive;
    /* How many bytes currently have received. */
    size_t bytesCurrentReceived;

    /* How to get data:
       1. If RX ring buffer is not enabled, then save xfer->data and xfer->dataSize
          to uart handle, enable interrupt to store received data to xfer->data. When
          all data received, trigger callback.
       2. If RX ring buffer is enabled and not empty, get data from ring buffer first.
          If there are enough data in ring buffer, copy them to xfer->data and return.
          If there are not enough data in ring buffer, copy all of them to xfer->data,
          save the xfer->data remained empty space to uart handle, receive data
          to this empty space and trigger callback when finished. */

    if (kUART_RxBusy == handle->rxState)
    {
        status = kStatus_UART_RxBusy;
    }
    else
    {
        bytesToReceive = xfer->dataSize;
        bytesCurrentReceived = 0U;

        /* If RX ring buffer is used. */
        if (handle->rxRingBuffer)
        {
            /* Disable UART RX IRQ, protect ring buffer. */
            UART_DisableInterrupts(base, kUART_RxReadyEnable | kUART_AgingTimerEnable);

            /* How many bytes in RX ring buffer currently. */
            bytesToCopy = UART_TransferGetRxRingBufferLength(handle);

            if (bytesToCopy)
            {
                bytesToCopy = MIN(bytesToReceive, bytesToCopy);

                bytesToReceive -= bytesToCopy;

                /* Copy data from ring buffer to user memory. */
                for (i = 0U; i < bytesToCopy; i++)
                {
                    xfer->data[bytesCurrentReceived++] = handle->rxRingBuffer[handle->rxRingBufferTail];

                    /* Wrap to 0. Not use modulo (%) because it might be large and slow. */
                    if (handle->rxRingBufferTail + 1U == handle->rxRingBufferSize)
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
            if (bytesToReceive)
            {
                /* No data in ring buffer, save the request to UART handle. */
                handle->rxData = xfer->data + bytesCurrentReceived;
                handle->rxDataSize = bytesToReceive;
                handle->rxDataSizeAll = bytesToReceive;
                handle->rxState = kUART_RxBusy;
            }

            /* Enable UART RX IRQ if previously enabled. */
            UART_EnableInterrupts(base, kUART_RxReadyEnable | kUART_AgingTimerEnable);

            /* Call user callback since all data are received. */
            if (0 == bytesToReceive)
            {
                if (handle->callback)
                {
                    handle->callback(base, handle, kStatus_UART_RxIdle, handle->userData);
                }
            }
        }
        /* Ring buffer not used. */
        else
        {
            handle->rxData = xfer->data + bytesCurrentReceived;
            handle->rxDataSize = bytesToReceive;
            handle->rxDataSizeAll = bytesToReceive;
            handle->rxState = kUART_RxBusy;

            /* Enable RX/Rx overrun/framing error interrupt. */
            UART_EnableInterrupts(base, kUART_RxReadyEnable | kUART_AgingTimerEnable | kUART_RxOverrunEnable |
                                            kUART_ParityErrorEnable | kUART_FrameErrorEnable);
        }

        /* Return the how many bytes have read. */
        if (receivedBytes)
        {
            *receivedBytes = bytesCurrentReceived;
        }

        status = kStatus_Success;
    }

    return status;
}

void UART_TransferAbortReceive(UART_Type *base, uart_handle_t *handle)
{
    assert(handle);

    /* Only abort the receive to handle->rxData, the RX ring buffer is still working. */
    if (!handle->rxRingBuffer)
    {
        /* Disable RX interrupt. */
        UART_DisableInterrupts(base, kUART_RxReadyEnable | kUART_AgingTimerEnable | kUART_RxOverrunEnable |
                                         kUART_ParityErrorEnable | kUART_FrameErrorEnable);
    }

    handle->rxDataSize = 0U;
    handle->rxState = kUART_RxIdle;
}

status_t UART_TransferGetReceiveCount(UART_Type *base, uart_handle_t *handle, uint32_t *count)
{
    assert(handle);
    assert(count);

    if (kUART_RxIdle == handle->rxState)
    {
        return kStatus_NoTransferInProgress;
    }

    if (!count)
    {
        return kStatus_InvalidArgument;
    }

    *count = handle->rxDataSizeAll - handle->rxDataSize;

    return kStatus_Success;
}

void UART_TransferHandleIRQ(UART_Type *base, uart_handle_t *handle)
{
    assert(handle);

    uint8_t count;
    uint8_t tempCount;

    /* If RX framing error */
    if (UART_USR1_FRAMERR_MASK & base->USR1)
    {
        /* Write 1 to clear framing error flag */
        base->USR1 |= UART_USR1_FRAMERR_MASK;

        handle->rxState = kUART_RxFramingError;
        handle->rxDataSize = 0U;
        /* Trigger callback. */
        if (handle->callback)
        {
            handle->callback(base, handle, kStatus_UART_FramingError, handle->userData);
        }
    }

    /* If RX parity error */
    if (UART_USR1_PARITYERR_MASK & base->USR1)
    {
        /* Write 1 to clear parity error flag. */
        base->USR1 |= UART_USR1_PARITYERR_MASK;

        handle->rxState = kUART_RxParityError;
        handle->rxDataSize = 0U;
        /* Trigger callback. */
        if (handle->callback)
        {
            handle->callback(base, handle, kStatus_UART_ParityError, handle->userData);
        }
    }

    /* If RX overrun. */
    if (UART_USR2_ORE_MASK & base->USR2)
    {
        /* Write 1 to clear overrun flag. */
        base->USR2 |= UART_USR2_ORE_MASK;
        /* Trigger callback. */
        if (handle->callback)
        {
            handle->callback(base, handle, kStatus_UART_RxHardwareOverrun, handle->userData);
        }
    }

    /* Receive data FIFO buffer reach the trigger level */
    if (((UART_USR1_RRDY_MASK)&base->USR1) && (UART_UCR1_RRDYEN_MASK & base->UCR1))
    {
        /* Get the size that stored in receive FIFO buffer for this interrupt. */
        count = ((base->UFCR & UART_UFCR_RXTL_MASK) >> UART_UFCR_RXTL_SHIFT);

        /* If count and handle->rxDataSize are not 0, first save data to handle->rxData. */
        while ((count) && (handle->rxDataSize))
        {
            tempCount = MIN(handle->rxDataSize, count);
            /* Using non block API to read the data from the registers. */
            UART_ReadNonBlocking(base, handle->rxData, tempCount);
            handle->rxData += tempCount;
            handle->rxDataSize -= tempCount;
            count -= tempCount;

            /* If all the data required for upper layer is ready, trigger callback. */
            if (!handle->rxDataSize)
            {
                handle->rxState = kUART_RxIdle;

                if (handle->callback)
                {
                    handle->callback(base, handle, kStatus_UART_RxIdle, handle->userData);
                }
            }
        }

        /* If use RX ring buffer, receive data to ring buffer. */
        if (handle->rxRingBuffer)
        {
            while (count--)
            {
                /* If RX ring buffer is full, trigger callback to notify over run. */
                if (UART_TransferIsRxRingBufferFull(handle))
                {
                    if (handle->callback)
                    {
                        handle->callback(base, handle, kStatus_UART_RxRingBufferOverrun, handle->userData);
                    }
                }

                /* If ring buffer is still full after callback function, the oldest data is overrided. */
                if (UART_TransferIsRxRingBufferFull(handle))
                {
                    /* Increase handle->rxRingBufferTail to make room for new data. */
                    if (handle->rxRingBufferTail + 1U == handle->rxRingBufferSize)
                    {
                        handle->rxRingBufferTail = 0U;
                    }
                    else
                    {
                        handle->rxRingBufferTail++;
                    }
                }

                /* Read data. */
                handle->rxRingBuffer[handle->rxRingBufferHead] =
                    (uint8_t)((base->URXD & UART_URXD_RX_DATA_MASK) >> UART_URXD_RX_DATA_SHIFT);

                /* Increase handle->rxRingBufferHead. */
                if (handle->rxRingBufferHead + 1U == handle->rxRingBufferSize)
                {
                    handle->rxRingBufferHead = 0U;
                }
                else
                {
                    handle->rxRingBufferHead++;
                }
            }
        }

        else if (!handle->rxDataSize)
        {
            /* Disable RX interrupt/overrun interrupt/framing error interrupt */
            UART_DisableInterrupts(base, kUART_RxReadyEnable | kUART_AgingTimerEnable | kUART_RxOverrunEnable |
                                             kUART_ParityErrorEnable | kUART_FrameErrorEnable);
        }
        else
        {
        }
    }
    /* Receive FIFO buffer has been idle for a time of 8 characters, and FIFO data level
     * is less than RxFIFO threshold level.
     */
    if (((UART_USR1_AGTIM_MASK)&base->USR1) && (UART_UCR2_ATEN_MASK & base->UCR2))
    {
        /* If count and handle->rxDataSize are not 0, first save data to handle->rxData. */
        while ((base->USR2 & UART_USR2_RDR_MASK) && (handle->rxDataSize))
        {
            /* Read one data from the URXD registers. */
            *handle->rxData = UART_ReadByte(base);
            handle->rxData += 1;
            handle->rxDataSize -= 1;

            /* If all the data required for upper layer is ready, trigger callback. */
            if (!handle->rxDataSize)
            {
                handle->rxState = kUART_RxIdle;

                if (handle->callback)
                {
                    handle->callback(base, handle, kStatus_UART_RxIdle, handle->userData);
                }
            }
        }

        /* If use RX ring buffer, receive data to ring buffer. */
        if (handle->rxRingBuffer)
        {
            while (base->USR2 & UART_USR2_RDR_MASK)
            {
                /* If RX ring buffer is full, trigger callback to notify over run. */
                if (UART_TransferIsRxRingBufferFull(handle))
                {
                    if (handle->callback)
                    {
                        handle->callback(base, handle, kStatus_UART_RxRingBufferOverrun, handle->userData);
                    }
                }

                /* If ring buffer is still full after callback function, the oldest data is overrided. */
                if (UART_TransferIsRxRingBufferFull(handle))
                {
                    /* Increase handle->rxRingBufferTail to make room for new data. */
                    if (handle->rxRingBufferTail + 1U == handle->rxRingBufferSize)
                    {
                        handle->rxRingBufferTail = 0U;
                    }
                    else
                    {
                        handle->rxRingBufferTail++;
                    }
                }
                /* Read one data from URXD register. */
                handle->rxRingBuffer[handle->rxRingBufferHead] = UART_ReadByte(base);

                /* Increase handle->rxRingBufferHead. */
                if (handle->rxRingBufferHead + 1U == handle->rxRingBufferSize)
                {
                    handle->rxRingBufferHead = 0U;
                }
                else
                {
                    handle->rxRingBufferHead++;
                }
            }
        }
        /* If ring buffer is not used and rxDataSize is 0 */
        else if (!handle->rxDataSize)
        {
            /* Disable RX interrupt/overrun interrupt/framing error interrupt */
            UART_DisableInterrupts(base, kUART_RxReadyEnable | kUART_AgingTimerEnable | kUART_RxOverrunEnable |
                                             kUART_ParityErrorEnable | kUART_FrameErrorEnable);
        }
        else
        {
        }
        /* Clear aging timer flag for next interrupt */
        UART_ClearStatusFlag(base, kUART_AgingTimerFlag);
    }
    /* If frame error or parity error happened, stop the RX interrupt when ues no ring buffer */
    if (((handle->rxState == kUART_RxFramingError) || (handle->rxState == kUART_RxParityError)) &&
        (!handle->rxRingBuffer))
    {
        /* Disable Receive ready interrupt, aging timer interrupt, receive over run interrupt,
         * parity error interrupt and frame error interrupt.
         */
        UART_DisableInterrupts(base, kUART_RxReadyEnable | kUART_AgingTimerEnable | kUART_RxOverrunEnable |
                                         kUART_ParityErrorEnable | kUART_FrameErrorEnable);
    }

    /* Send data register empty and the interrupt is enabled. */
    if ((UART_USR1_TRDY_MASK & base->USR1) && (UART_UCR1_TRDYEN_MASK & base->UCR1))
    {
        /* Get the bytes that available at this moment. */
        if (0U != ((base->UFCR & UART_UFCR_TXTL_MASK) >> UART_UFCR_TXTL_SHIFT))
        {
            if (UART_UTS_TXEMPTY_MASK & (base->UTS))
            {
                count = FSL_FEATURE_IUART_FIFO_SIZEn(base);
            }
            else
            {
                count =
                    FSL_FEATURE_IUART_FIFO_SIZEn(base) - ((base->UFCR & UART_UFCR_TXTL_MASK) >> UART_UFCR_TXTL_SHIFT);
            }
        }
        else
        {
            count = 1;
        }

        while ((count) && (handle->txDataSize))
        {
            if (0U != ((base->UFCR & UART_UFCR_TXTL_MASK) >> UART_UFCR_TXTL_SHIFT))
            {
                tempCount = MIN(handle->txDataSize, count);
            }
            else
            {
                tempCount = 1;
            }
            /* Using non block API to write the data to the registers. */
            UART_WriteNonBlocking(base, handle->txData, tempCount);
            handle->txData += tempCount;
            handle->txDataSize -= tempCount;
            count -= tempCount;

            /* If all the data are written to data register, TX finished. */
            if (!handle->txDataSize)
            {
                handle->txState = kUART_TxIdle;
                /* Disable TX FIFO buffer empty interrupt. */
                UART_DisableInterrupts(base, kUART_TxReadyEnable);
                /* Trigger callback.
                 * Note: This callback is called when all data have been send to TX FIFO,
                 *       but this not mean transmit has completed, some data may still in
                 *       FIFO buffer.
                 */
                if (handle->callback)
                {
                    handle->callback(base, handle, kStatus_UART_TxIdle, handle->userData);
                }
            }
        }
    }
}

#if defined(UART1)
void UART1_DriverIRQHandler(void)
{
    s_uartIsr(UART1, s_uartHandle[0]);
}
#endif

#if defined(UART2)
void UART2_DriverIRQHandler(void)
{
    s_uartIsr(UART2, s_uartHandle[1]);
}
#endif

#if defined(UART3)
void UART3_DriverIRQHandler(void)
{
    s_uartIsr(UART3, s_uartHandle[2]);
}
#endif

#if defined(UART4)
void UART4_DriverIRQHandler(void)
{
    s_uartIsr(UART4, s_uartHandle[3]);
}
#endif

#if defined(UART5)
void UART5_DriverIRQHandler(void)
{
    s_uartIsr(UART5, s_uartHandle[4]);
}
#endif

#if defined(UART6)
void UART6_DriverIRQHandler(void)
{
    s_uartIsr(UART6, s_uartHandle[5]);
}
#endif

#if defined(UART7)
void UART7_DriverIRQHandler(void)
{
    s_uartIsr(UART7, s_uartHandle[6]);
}
#endif

#if defined(UART8)
void UART8_DriverIRQHandler(void)
{
    s_uartIsr(UART8, s_uartHandle[7]);
}
#endif
