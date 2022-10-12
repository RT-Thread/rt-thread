/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_base.h"

#ifdef HAL_UART_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup UART
 *  @{
 */

/** @defgroup UART_How_To_Use How To Use
 *  @{

 The UART driver can be used as follows:

 @} */

/** @defgroup UART_Private_Definition Private Definition
 *  @{
 */
/********************* Private MACRO Definition ******************************/
/********************* Private Structure Definition **************************/
/********************* Private Variable Definition ***************************/

/********************* Private Function Definition ***************************/
static void UART_EnableDLAB(struct UART_REG *pReg)
{
    pReg->LCR |= UART_LCR_DLAB;
}

static void UART_DisableDLAB(struct UART_REG *pReg)
{
    pReg->LCR &= ~(UART_LCR_DLAB);
}

static int32_t UART_SetBaudRate(struct UART_REG *pReg, uint32_t clkRate,
                                uint32_t baudRate)
{
    uint32_t DivLatch;

    DivLatch = clkRate / MODE_X_DIV / baudRate;

    pReg->MCR |= UART_MCR_LOOP;
    UART_EnableDLAB(pReg);

    pReg->DLL = DivLatch & 0xff;
    pReg->DLH = (DivLatch >> 8) & 0xff;

    UART_DisableDLAB(pReg);
    pReg->MCR &= ~(UART_MCR_LOOP);

    return (0);
}

static int32_t UART_SetLcrReg(struct UART_REG *pReg, uint8_t byteSize,
                              uint8_t parity, uint8_t stopBits)
{
    uint32_t lcr = 0;
    int32_t bRet = 0;

    switch (byteSize) {
    case UART_DATA_5B:
        lcr |= UART_LCR_WLEN5;
        break;
    case UART_DATA_6B:
        lcr |= UART_LCR_WLEN6;
        break;
    case UART_DATA_7B:
        lcr |= UART_LCR_WLEN7;
        break;
    case UART_DATA_8B:
        lcr |= UART_LCR_WLEN8;
        break;
    default:
        bRet = -1;
        break;
    }

    switch (parity) {
    case UART_ODD_PARITY:
    case UART_EVEN_PARITY:
        lcr |= UART_LCR_PARITY;
        lcr |= ((parity) << 4);
        break;
    case UART_PARITY_DISABLE:
        lcr &= ~UART_LCR_PARITY;
        break;
    default:
        bRet = -1;
        break;
    }

    if (stopBits == UART_ONE_AND_HALF_OR_TWO_STOPBIT) {
        lcr |= UART_LCR_STOP;
    }

    pReg->LCR = lcr;

    return (bRet);
}

/** @} */
/********************* Public Function Definition ****************************/

/** @defgroup UART_Exported_Functions_Group1 Suspend and Resume Functions

 This section provides functions allowing to suspend and resume the module:

 *  @{
 */
/**
  * @brief  suspend uart
  * @param  pReg:      uart reg base
  * @param  pUartSave: save uart reg
  * @return HAL_OK
  */
HAL_Status HAL_UART_Suspend(struct UART_REG *pReg, struct UART_SAVE_CONFIG *pUartSave)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));
    if (pUartSave && pReg) {
        while (!(pReg->USR & UART_USR_TX_FIFO_EMPTY)) {
            ;
        }
        pUartSave->LCR = pReg->LCR;
        pUartSave->IER = pReg->IER;
        pUartSave->MCR = pReg->MCR;
        if (pReg->USR & UART_USR_BUSY) {
            HAL_DelayMs(10);
        }
        if (pReg->USR & UART_USR_BUSY) {
            pReg->SRR = UART_SRR_XFR | UART_SRR_RFR;
        }
        pReg->LCR = UART_LCR_DLAB;
        pUartSave->DLL = pReg->DLL;
        pUartSave->DLH = pReg->DLH;
        pUartSave->SRT = pReg->SRT;
        pUartSave->STET = pReg->STET;
        pReg->LCR = pUartSave->LCR;
    }

    return HAL_OK;
}

/**
  * @brief  resume uart
  * @param  pReg:      uart reg base
  * @param  pUartSave: save uart reg
  * @return HAL_OK
  */
HAL_Status HAL_UART_Resume(struct UART_REG *pReg, struct UART_SAVE_CONFIG *pUartSave)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));
    if (pUartSave && pReg) {
        pReg->SRR = UART_SRR_XFR | UART_SRR_RFR | UART_SRR_UR;
        pReg->MCR = UART_MCR_LOOP;
        pReg->LCR = UART_LCR_DLAB;
        pReg->DLL = pUartSave->DLL;
        pReg->DLH = pUartSave->DLH;
        pReg->LCR = pUartSave->LCR;
        pReg->IER = pUartSave->IER;
        pReg->FCR = UART_FCR_ENABLE_FIFO;
        pReg->MCR = pUartSave->MCR;
        pReg->SRT = pUartSave->SRT;
        pReg->STET = pUartSave->STET;
    }

    return HAL_OK;
}
/** @} */

/** @defgroup UART_Exported_Functions_Group2 State and Errors Functions

 This section provides functions allowing to get uart status:

 *  @{
 */

/**
  * @brief  get uart sub interrupt number
  * @param  pReg: uart reg base
  * @return irq number like UART_IIR_RDI
  */
uint32_t HAL_UART_GetIrqID(struct UART_REG *pReg)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));

    return (pReg->IIR & UART_IIR_MASK);
}

/**
  * @brief  get uart sub interrupt number
  * @param  pReg: uart reg base
  * @return line status
  */
uint32_t HAL_UART_GetLsr(struct UART_REG *pReg)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));

    return pReg->LSR;
}

/**
  * @brief  get uart status
  * @param  pReg: uart reg base
  * @return uart status
  */
uint32_t HAL_UART_GetUsr(struct UART_REG *pReg)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));

    return pReg->USR;
}

/**
  * @brief  get uart modem status
  * @param  pReg: uart reg base
  * @return uart modem status
  */
uint32_t HAL_UART_GetMsr(struct UART_REG *pReg)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));

    return pReg->MSR;
}

/** @} */

/** @defgroup UART_Exported_Functions_Group3 IO Functions

 This section provides functions allowing to IO controlling:

 *  @{
 */
/**
  * @brief  send one character
  * @param  pReg: uart reg base
  * @param  c: the character to be sent
  */
void HAL_UART_SerialOutChar(struct UART_REG *pReg, char c)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));

    while (!(pReg->USR & UART_USR_TX_FIFO_NOT_FULL)) {
        ;
    }
    pReg->THR = (uint32_t)c;
}

/**
  * @brief  send many characters
  * @param  pReg: uart reg base
  * @param  pdata: characters buffer
  * @param  cnt: the number of characters
  * @return dwRealSize the number has been sent
  */
int HAL_UART_SerialOut(struct UART_REG *pReg, const uint8_t *pdata, uint32_t cnt)
{
    int dwRealSize = 0;

    HAL_ASSERT(IS_UART_INSTANCE(pReg));

    while (cnt--) {
        while (!(pReg->USR & UART_USR_TX_FIFO_NOT_FULL)) {
            ;
        }
        pReg->THR = *pdata++;
        dwRealSize++;
    }

    return dwRealSize;
}

/**
  * @brief  receive many characters
  * @param  pReg: uart reg base
  * @param  pdata: characters buffer
  * @param  cnt: the number of characters
  * @return dwRealSize the number has been received
  */
int HAL_UART_SerialIn(struct UART_REG *pReg, uint8_t *pdata, uint32_t cnt)
{
    int dwRealSize = 0;

    HAL_ASSERT(IS_UART_INSTANCE(pReg));

    while (cnt--) {
        if (!(pReg->USR & UART_USR_RX_FIFO_NOT_EMPTY)) {
            break;
        }

        *pdata++ = (uint8_t)pReg->RBR;
        dwRealSize++;
    }

    return dwRealSize;
}

/** @} */

/** @defgroup UART_Exported_Functions_Group4 Init and DeInit Functions

 This section provides functions allowing to init and deinit the module:

 *  @{
 */

/**
  * @brief  reset uart
  * @param  pReg: uart reg base
  */
void HAL_UART_Reset(struct UART_REG *pReg)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));
    pReg->SRR = UART_SRR_UR | UART_SRR_RFR | UART_SRR_XFR;
    pReg->IER = 0;
    pReg->DMASA = 1;
}

/**
  * @brief  configure uart baudrate,data bit,stop bit and so on
  * @param  dev: uart hal information
  * @param  config: uart baud rate,data bit
  * @return HAL_OK for reserve
  */
HAL_Status HAL_UART_Init(const struct HAL_UART_DEV *dev, const struct HAL_UART_CONFIG *config)
{
    uint32_t newRate;
    struct UART_REG *pReg;

    HAL_ASSERT(dev != NULL);

    pReg = dev->pReg;
    HAL_ASSERT(IS_UART_INSTANCE(pReg));

#ifdef RK_BSP_TEMP
#if defined(HAL_CRU_MODULE_ENABLED) && !defined(IS_FPGA)
    {
        uint32_t rate;

        /* set sclk according to uart baud rate */
        if (config->baudRate <= 115200) {
            rate = PLL_INPUT_OSC_RATE;
        } else {
            rate = config->baudRate * 16;
        }
        HAL_CRU_ClkSetFreq(dev->sclkID, rate);
        newRate = HAL_CRU_ClkGetFreq(dev->sclkID);
        HAL_ASSERT(rate == newRate);
    }
#elif defined(PLL_INPUT_OSC_RATE) && !defined(IS_FPGA)
    newRate = PLL_INPUT_OSC_RATE;
#else
    newRate = 24000000;
#endif
#endif
    newRate = 24000000;

    pReg->FCR =
        UART_FCR_ENABLE_FIFO | UART_FCR_R_TRIG_10 | UART_FCR_T_TRIG_10;
    UART_SetLcrReg(pReg, config->dataBit, config->parity, config->stopBit);
    UART_SetBaudRate(pReg, newRate, config->baudRate);

    return HAL_OK;
}

/**
  * @brief  disable uart by resetting it
  * @param  pReg: uart reg base
  * @return HAL_OK for reserve
  */
HAL_Status HAL_UART_DeInit(struct UART_REG *pReg)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));
    HAL_UART_Reset(pReg);

    return HAL_OK;
}

/** @} */

/** @defgroup UART_Exported_Functions_Group5 Other Functions

 This section provides functions allowing to control uart:

 *  @{
 */
/**
  * @brief  enable uart sub interrupt
  * @param  pReg: uart reg base
  * @param  uartIntNumb: uart irq num, such as UART_IER_RDI
  */
void HAL_UART_EnableIrq(struct UART_REG *pReg, uint32_t uartIntNumb)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));
    pReg->IER |= uartIntNumb;
}

/**
  * @brief  disable uart sub interrupt
  * @param  pReg: uart reg base
  * @param  uartIntNumb: uart irq num, such as UART_IER_RDI
  */
void HAL_UART_DisableIrq(struct UART_REG *pReg, uint32_t uartIntNumb)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));
    pReg->IER &= ~uartIntNumb;
}

/**
  * @brief  enable uart loop back mode
  * @param  pReg: uart reg base
  */
void HAL_UART_EnableLoopback(struct UART_REG *pReg)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));
    pReg->MCR |= UART_MCR_LOOP;
}

/**
  * @brief  disable uart loop back mode
  * @param  pReg: uart reg base
  */
void HAL_UART_DisableLoopback(struct UART_REG *pReg)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));
    pReg->MCR &= ~(UART_MCR_LOOP);
}

/**
  * @brief  enable uart hardware auto flow control
  * @param  pReg: uart reg base
  */
void HAL_UART_EnableAutoFlowControl(struct UART_REG *pReg)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));
    pReg->MCR = UART_MCR_AFE | 0X02;
}

/**
  * @brief  disable uart hardware auto flow control
  * @param  pReg: uart reg base
  */
void HAL_UART_DisableAutoFlowControl(struct UART_REG *pReg)
{
    HAL_ASSERT(IS_UART_INSTANCE(pReg));
    pReg->MCR &= ~UART_MCR_AFE;
}

/**
  * @brief  low level irq handler, for msi, busy, rlsi
  * @param  pReg: uart reg base
  * @return HAL_OK for reserve
  */
HAL_Status HAL_UART_HandleIrq(struct UART_REG *pReg)
{
    int iir = 0;

    HAL_ASSERT(IS_UART_INSTANCE(pReg));

    iir = HAL_UART_GetIrqID(pReg);

    /* Handle the three sub interrupts, so the upper irq handler needn't handle those */
    switch (iir) {
    case UART_IIR_MSI:
        HAL_UART_GetMsr(pReg); /* clear MSI only */
        break;
    case UART_IIR_BUSY:
        HAL_UART_GetUsr(pReg); /* clear BUSY interrupt only */
        break;
    case UART_IIR_RLSI:
        HAL_UART_GetMsr(pReg); /* clear RLSI interrupt only */
        break;
    case UART_IIR_NO_INT:
        break;
    }

    return HAL_OK;
}

/** @} */

/** @} */

/** @} */

#endif /* HAL_UART_MODULE_ENABLED */
