/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_conf.h"

#ifdef HAL_UART_MODULE_ENABLED

/** @addtogroup RK_HAL_Driver
 *  @{
 */

/** @addtogroup UART
 *  @{
 */

#ifndef _HAL_UART_H_
#define _HAL_UART_H_

#include "hal_def.h"
#include "hal_base.h"

/***************************** MACRO Definition ******************************/
/** @defgroup UART_Exported_Definition_Group1 Basic Definition
 *  @{
 */

/* Out: Interrupt Enable Register */
#define UART_IER_PTIME 0x80 /**< Enable Programmable THRE Interrupt Mode */
#define UART_IER_MSI   0x08 /**< Enable Modem status interrupt */
#define UART_IER_RLSI  0x04 /**< Enable receiver line status interrupt */
#define UART_IER_THRI  0x02 /**< Enable Transmitter holding register int. */
#define UART_IER_RDI   0x01 /**< Enable receiver data interrupt */

/* In:  Interrupt ID Register */
#define UART_IIR_MASK       0x0f /**< Interrupt ID Mask */
#define UART_IIR_NO_INT     0x01 /**< No interrupts pending */
#define UART_IIR_ID         0x0e /**< Mask for the interrupt ID */
#define UART_IIR_MSI        0x00 /**< Modem status interrupt */
#define UART_IIR_THRI       0x02 /**< Transmitter holding register empty */
#define UART_IIR_RDI        0x04 /**< Receiver data interrupt */
#define UART_IIR_RLSI       0x06 /**< Receiver line status interrupt */
#define UART_IIR_BUSY       0x07 /**< DesignWare APB Busy Detect */
#define UART_IIR_RX_TIMEOUT 0x0c /**< RX Timeout interrupt */

/* Out: FIFO Control Register */
#define UART_FCR_ENABLE_FIFO 0x01 /**< Enable the FIFO */
#define UART_FCR_CLEAR_RCVR  0x02 /**< Clear the RCVR FIFO */
#define UART_FCR_CLEAR_XMIT  0x04 /**< Clear the XMIT FIFO */
#define UART_FCR_DMA_SELECT  0x08 /**< For DMA applications */

#define UART_FCR_R_TRIG_00 0x00
#define UART_FCR_R_TRIG_01 0x40
#define UART_FCR_R_TRIG_10 0x80
#define UART_FCR_R_TRIG_11 0xc0
#define UART_FCR_T_TRIG_00 0x00
#define UART_FCR_T_TRIG_01 0x10
#define UART_FCR_T_TRIG_10 0x20
#define UART_FCR_T_TRIG_11 0x30

#define UART_FCR_TRIGGER_MASK 0xC0 /**< Mask for the FIFO trigger range */
#define UART_FCR_TRIGGER_1    0x00 /**< Mask for trigger set at 1 */
#define UART_FCR_TRIGGER_4    0x40 /**< Mask for trigger set at 4 */
#define UART_FCR_TRIGGER_8    0x80 /**< Mask for trigger set at 8 */
#define UART_FCR_TRIGGER_14   0xC0 /**< Mask for trigger set at 14 */
/* 16650 definitions */
#define UART_FCR6_R_TRIGGER_8  0x00 /**< Mask for receive trigger set at 1 */
#define UART_FCR6_R_TRIGGER_16 0x40 /**< Mask for receive trigger set at 4 */
#define UART_FCR6_R_TRIGGER_24 0x80 /**< Mask for receive trigger set at 8 */
#define UART_FCR6_R_TRIGGER_28 0xC0 /**< Mask for receive trigger set at 14 */
#define UART_FCR6_T_TRIGGER_16 0x00 /**< Mask for transmit trigger set at 16 */
#define UART_FCR6_T_TRIGGER_8  0x10 /**< Mask for transmit trigger set at 8 */
#define UART_FCR6_T_TRIGGER_24 0x20 /**< Mask for transmit trigger set at 24 */
#define UART_FCR6_T_TRIGGER_30 0x30 /**< Mask for transmit trigger set at 30 */
#define UART_FCR7_64BYTE       0x20
/* Go into 64 byte mode (TI16C750 and some Freescale UARTs) */

#define UART_FCR_R_TRIG_SHIFT     6
#define UART_FCR_R_TRIG_BITS(x)   (((x)&UART_FCR_TRIGGER_MASK) >> UART_FCR_R_TRIG_SHIFT)
#define UART_FCR_R_TRIG_MAX_STATE 4

/* Out: Line Control Register */
/*
 * Note: if the word length is 5 bits (UART_LCR_WLEN5), then setting
 * UART_LCR_STOP will select 1.5 stop bits, not 2 stop bits.
 */
#define UART_LCR_DLAB   0x80 /**< Divisor latch access bit */
#define UART_LCR_SBC    0x40 /**< Set break control */
#define UART_LCR_SPAR   0x20 /**< Stick parity (?) */
#define UART_LCR_EPAR   0x10 /**< Even parity select */
#define UART_LCR_PARITY 0x08 /**< Parity Enable */
#define UART_LCR_STOP   0x04 /**< Stop bits: 0=1 bit, 1=2 bits */
#define UART_LCR_WLEN5  0x00 /**< Wordlength: 5 bits */
#define UART_LCR_WLEN6  0x01 /**< Wordlength: 6 bits */
#define UART_LCR_WLEN7  0x02 /**< Wordlength: 7 bits */
#define UART_LCR_WLEN8  0x03 /**< Wordlength: 8 bits */

/* Out: Modem Control Register */
#define UART_MCR_CLKSEL 0x80 /**< Divide clock by 4 (TI16C752, EFR[4]=1) */
#define UART_MCR_TCRTLR 0x40 /**< Access TCR/TLR (TI16C752, EFR[4]=1) */
#define UART_MCR_XONANY 0x20 /**< Enable Xon Any (TI16C752, EFR[4]=1) */
#define UART_MCR_AFE    0x20 /**< Enable auto-RTS/CTS (TI16C550C/TI16C750) */
#define UART_MCR_LOOP   0x10 /**< Enable loopback test mode */
#define UART_MCR_OUT2   0x08 /**< Out2 complement */
#define UART_MCR_OUT1   0x04 /**< Out1 complement */
#define UART_MCR_RTS    0x02 /**< RTS complement */
#define UART_MCR_DTR    0x01 /**< DTR complement */

/* In:  Line Status Register */
#define UART_LSR_FIFOE          0x80 /**< Fifo error */
#define UART_LSR_TEMT           0x40 /**< Transmitter empty */
#define UART_LSR_THRE           0x20 /**< Transmit-hold-register empty */
#define UART_LSR_BI             0x10 /**< Break interrupt indicator */
#define UART_LSR_FE             0x08 /**< Frame error indicator */
#define UART_LSR_PE             0x04 /**< Parity error indicator */
#define UART_LSR_OE             0x02 /**< Overrun error indicator */
#define UART_LSR_DR             0x01 /**< Receiver data ready */
#define UART_LSR_BRK_ERROR_BITS 0x1E /**< BI, FE, PE, OE bits */

/* In:  Modem Status Register */
#define UART_MSR_DCD       0x80 /**< Data Carrier Detect */
#define UART_MSR_RI        0x40 /**< Ring Indicator */
#define UART_MSR_DSR       0x20 /**< Data Set Ready */
#define UART_MSR_CTS       0x10 /**< Clear to Send */
#define UART_MSR_DDCD      0x08 /**< Delta DCD */
#define UART_MSR_TERI      0x04 /**< Trailing edge ring indicator */
#define UART_MSR_DDSR      0x02 /**< Delta DSR */
#define UART_MSR_DCTS      0x01 /**< Delta CTS */
#define UART_MSR_ANY_DELTA 0x0F /**< Any of the delta bits! */

#define UART_USR_RX_FIFO_FULL      0x10 /**< Receive FIFO full */
#define UART_USR_RX_FIFO_NOT_EMPTY 0x08 /**< Receive FIFO not empty */
#define UART_USR_TX_FIFO_EMPTY     0x04 /**< Transmit FIFO empty */
#define UART_USR_TX_FIFO_NOT_FULL  0x02 /**< Transmit FIFO not full */
#define UART_USR_BUSY              0x01 /**< UART busy indicator */

#define UART_SRR_UR  0x1 /**< UART Reset */
#define UART_SRR_RFR 0X2 /**< RCVR FIFO Reset */
#define UART_SRR_XFR 0x4 /**< XMIT FIFO Reset */

#define MODE_X_DIV 16 /**< baud = f / 16 / div */

/***************************** Structure Definition **************************/

/**
  * @brief  UART baud rate definition
  */
typedef enum {
    UART_BR_110     = 110,
    UART_BR_300     = 300,
    UART_BR_600     = 600,
    UART_BR_1200    = 1200,
    UART_BR_2400    = 2400,
    UART_BR_4800    = 4800,
    UART_BR_9600    = 9600,
    UART_BR_14400   = 14400,
    UART_BR_19200   = 19200,
    UART_BR_38400   = 38400,
    UART_BR_57600   = 57600,
    UART_BR_115200  = 115200,
    UART_BR_230400  = 230400,
    UART_BR_380400  = 380400,
    UART_BR_460800  = 460800,
    UART_BR_921600  = 921600,
    UART_BR_1000000 = 1000000,
    UART_BR_1500000 = 1500000,
    UART_BR_2000000 = 2000000,
    UART_BR_3000000 = 3000000,
    UART_BR_4000000 = 4000000,
} eUART_baudRate;

/**
  * @brief  UART data bit definition
  */
typedef enum {
    UART_DATA_5B = 5,
    UART_DATA_6B,
    UART_DATA_7B,
    UART_DATA_8B
} eUART_dataLen;

/**
  * @brief  UART stop bit definition
  */
typedef enum {
    UART_ONE_STOPBIT,
    UART_ONE_AND_HALF_OR_TWO_STOPBIT
} eUART_stopBit;

/**
  * @brief  UART parity definition
  */
typedef enum {
    UART_ODD_PARITY,
    UART_EVEN_PARITY,
    UART_PARITY_DISABLE
} eUART_parityEn;

/**
  * @brief  UART config definition
  */
struct HAL_UART_CONFIG {
    eUART_baudRate baudRate;
    eUART_dataLen dataBit;
    eUART_stopBit stopBit;
    eUART_parityEn parity;
};

/**
  * @brief  UART HW information definition on a soc
  */
struct HAL_UART_DEV {
    struct UART_REG *pReg; /**< registers base address */

    /* sclk is for uart logic, pclk is for register access */
    eCLOCK_Name sclkID;
    uint32_t sclkGateID;
    uint32_t pclkGateID;

    IRQn_Type irqNum;
    bool isAutoFlow;
    ePM_RUNTIME_ID runtimeID;
    DMA_REQ_Type dmaTxReqNum; /**< peri dma tx request num */
    DMA_REQ_Type dmaRxReqNum; /**< peri dma rx request num */
    struct DMA_REG *dmac; /**< dmac reg base ptr */
};

/**
  * @brief  Save UART regist
  */
struct UART_SAVE_CONFIG {
    uint32_t DLL;
    uint32_t DLH;
    uint32_t IER;
    uint32_t LCR;
    uint32_t MCR;
    uint32_t SRT;
    uint32_t STET;
};

/** @} */

/***************************** Function Declare ******************************/
/** @defgroup UART_Public_Function_Declare Public Function Declare
 *  @{
 */
void HAL_UART_EnableIrq(struct UART_REG *pReg, uint32_t uartIntNumb);
void HAL_UART_DisableIrq(struct UART_REG *pReg, uint32_t uartIntNumb);
void HAL_UART_EnableLoopback(struct UART_REG *pReg);
void HAL_UART_DisableLoopback(struct UART_REG *pReg);
void HAL_UART_EnableAutoFlowControl(struct UART_REG *pReg);
void HAL_UART_DisableAutoFlowControl(struct UART_REG *pReg);
uint32_t HAL_UART_GetIrqID(struct UART_REG *pReg);
uint32_t HAL_UART_GetLsr(struct UART_REG *pReg);
uint32_t HAL_UART_GetUsr(struct UART_REG *pReg);
uint32_t HAL_UART_GetMsr(struct UART_REG *pReg);
void HAL_UART_SerialOutChar(struct UART_REG *pReg, char c);
int HAL_UART_SerialOut(struct UART_REG *pReg, const uint8_t *pdata, uint32_t cnt);
int HAL_UART_SerialIn(struct UART_REG *pReg, uint8_t *pdata, uint32_t cnt);
HAL_Status HAL_UART_HandleIrq(struct UART_REG *pReg);
void HAL_UART_Reset(struct UART_REG *pReg);
HAL_Status HAL_UART_Init(const struct HAL_UART_DEV *dev, const struct HAL_UART_CONFIG *config);
HAL_Status HAL_UART_DeInit(struct UART_REG *pReg);
HAL_Status HAL_UART_Suspend(struct UART_REG *pReg, struct UART_SAVE_CONFIG *pUartSave);
HAL_Status HAL_UART_Resume(struct UART_REG *pReg, struct UART_SAVE_CONFIG *pUartSave);

/** @} */

#endif

/** @} */

/** @} */

#endif /* HAL_UART_MODULE_ENABLED */
