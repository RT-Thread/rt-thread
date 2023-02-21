/**
  ******************************************************************************
  * @file    bl808_uart.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#ifndef __BL808_UART_H__
#define __BL808_UART_H__

#include "uart_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  UART
 *  @{
 */

/** @defgroup  UART_Public_Types
 *  @{
 */

/**
 *  @brief UART port type definition
 */
typedef enum {
    UART0_ID,    /*!< UART0 port define */
    UART1_ID,    /*!< UART1 port define */
    UART2_ID,    /*!< UART2 port define */
    UART0_MM_ID, /*!< MM system UART0 port define */
    UART_ID_MAX, /*!< UART MAX ID define */
} UART_ID_Type;

/**
 *  @brief UART direction type definition
 */
typedef enum {
    UART_TX,   /*!< UART TX Direction */
    UART_RX,   /*!< UART RX Direction */
    UART_TXRX, /*!< UART TX and RX Direction */
} UART_Direction_Type;

/**
 *  @brief UART parity type definition
 */
typedef enum {
    UART_PARITY_NONE, /*!< UART parity none define */
    UART_PARITY_ODD,  /*!< UART parity odd define */
    UART_PARITY_EVEN, /*!< UART parity even define */
} UART_Parity_Type;

/**
 *  @brief UART data bits type definiton
 */
typedef enum {
    UART_DATABITS_5, /*!< UART data bits length:5 bits */
    UART_DATABITS_6, /*!< UART data bits length:6 bits */
    UART_DATABITS_7, /*!< UART data bits length:7 bits */
    UART_DATABITS_8, /*!< UART data bits length:8 bits */
} UART_DataBits_Type;

/**
 *  @brief UART stop bits type definiton
 */
typedef enum {
    UART_STOPBITS_0_5, /*!< UART data stop bits length:0.5 bits */
    UART_STOPBITS_1,   /*!< UART data stop bits length:1 bits */
    UART_STOPBITS_1_5, /*!< UART data stop bits length:1.5 bits */
    UART_STOPBITS_2,   /*!< UART data stop bits length:2 bits */
} UART_StopBits_Type;

/**
 *  @brief UART each data byte is send out LSB-first or MSB-first type definiton
 */
typedef enum {
    UART_LSB_FIRST, /*!< UART each byte is send out LSB-first */
    UART_MSB_FIRST, /*!< UART each byte is send out MSB-first */
} UART_ByteBitInverse_Type;

/**
 *  @brief UART auto baudrate detection using codeword 0x55 or start bit definiton
 */
typedef enum {
    UART_AUTOBAUD_0X55,     /*!< UART auto baudrate detection using codeword 0x55 */
    UART_AUTOBAUD_STARTBIT, /*!< UART auto baudrate detection using start bit */
} UART_AutoBaudDetection_Type;

/**
 *  @brief UART RS-485 mode DE pin polarity definiton
 */
typedef enum {
    UART_RS485_DE_ACTIVE_LOW,  /*!< UART DE is active-low */
    UART_RS485_DE_ACTIVE_HIGH, /*!< UART DE is active-high */
} UART_RS485Polarity_Type;

/**
 *  @brief UART interrupt type definition
 */
typedef enum {
    UART_INT_TX_END,      /*!< UART tx transfer end interrupt */
    UART_INT_RX_END,      /*!< UART rx transfer end interrupt */
    UART_INT_TX_FIFO_REQ, /*!< UART tx fifo interrupt when tx fifo count reaches,auto clear */
    UART_INT_RX_FIFO_REQ, /*!< UART rx fifo interrupt when rx fifo count reaches,auto clear */
    UART_INT_RTO,         /*!< UART rx time-out interrupt */
    UART_INT_PCE,         /*!< UART rx parity check error interrupt */
    UART_INT_TX_FER,      /*!< UART tx fifo overflow/underflow error interrupt */
    UART_INT_RX_FER,      /*!< UART rx fifo overflow/underflow error interrupt */
    UART_INT_LSE,         /*!< UART rx lin mode sync field error interrupt */
    UART_INT_BCR,         /*!< UART rx byte count reached interrupt */
    UART_INT_STARTBIT,    /*!< UART rx auto baudrate detection finish interrupt using start bit */
    UART_INT_0X55,        /*!< UART rx auto baudrate detection finish interrupt using codeword 0x55 */
    UART_INT_ALL,         /*!< All the interrupt */
} UART_INT_Type;

/**
 *  @brief UART overflow or underflow type definition
 */
typedef enum {
    UART_TX_OVERFLOW,  /*!< UART tx fifo overflow */
    UART_TX_UNDERFLOW, /*!< UART tx fifo underflow */
    UART_RX_OVERFLOW,  /*!< UART rx fifo overflow */
    UART_RX_UNDERFLOW, /*!< UART rx fifo underflow */
} UART_Overflow_Type;

/**
 *  @brief UART configuration structure type definition
 */
typedef struct
{
    uint32_t uartClk;                        /*!< Uart module clock */
    uint32_t baudRate;                       /*!< Uart baudrate */
    UART_DataBits_Type dataBits;             /*!< Uart frame length of data bit */
    UART_StopBits_Type stopBits;             /*!< Uart frame length of stop bit */
    UART_Parity_Type parity;                 /*!< Uart parity check type */
    BL_Fun_Type ctsFlowControl;              /*!< Enable or disable tx CTS flow control */
    BL_Fun_Type rxDeglitch;                  /*!< Enable or disable rx input de-glitch function */
    BL_Fun_Type rtsSoftwareControl;          /*!< Enable or disable rx RTS output SW control mode */
    BL_Fun_Type txSoftwareControl;           /*!< Enable or disable tx output SW control mode */
    BL_Fun_Type txLinMode;                   /*!< Enable or disable tx LIN mode,LIN header will be sent before sending data */
    BL_Fun_Type rxLinMode;                   /*!< Enable or disable rx LIN mode,LIN header will be required and checked before receiving data */
    uint8_t txBreakBitCnt;                   /*!< Uart tx break bit count,additional 8 bit times will be added since LIN break field requires at
                                                 least 13 bit times */
    UART_ByteBitInverse_Type byteBitInverse; /*!< Uart each data byte is send out LSB-first or MSB-first */
} UART_CFG_Type;

/**
 *  @brief UART FIFO configuration structure type definition
 */
typedef struct
{
    uint8_t txFifoDmaThreshold;  /*!< TX FIFO threshold, dma tx request will not be asserted if tx fifo count is less than this value */
    uint8_t rxFifoDmaThreshold;  /*!< RX FIFO threshold, dma rx request will not be asserted if rx fifo count is less than this value */
    BL_Fun_Type txFifoDmaEnable; /*!< Enable or disable tx dma req/ack interface */
    BL_Fun_Type rxFifoDmaEnable; /*!< Enable or disable rx dma req/ack interface */
} UART_FifoCfg_Type;

/**
 *  @brief UART infrared configuration structure type definition
 */
typedef struct
{
    BL_Fun_Type txIrEnable;  /*!< Enable or disable uart tx ir mode */
    BL_Fun_Type rxIrEnable;  /*!< Enable or disable uart rx ir mode */
    BL_Fun_Type txIrInverse; /*!< Enable or disable inverse signal of uart tx output in ir mode */
    BL_Fun_Type rxIrInverse; /*!< Enable or disable inverse signal of uart rx input in ir mode */
    uint16_t txIrPulseStart; /*!< Set start position of uart tx ir pulse */
    uint16_t txIrPulseStop;  /*!< Set stop position of uart tx ir pulse */
    uint16_t rxIrPulseStart; /*!< Set start position of uart rx pulse recovered from ir signal */
} UART_IrCfg_Type;

/*@} end of group UART_Public_Types */

/** @defgroup  UART_Public_Constants
 *  @{
 */

/** @defgroup  UART_ID_TYPE
 *  @{
 */
#define IS_UART_ID_TYPE(type) (((type) == UART0_ID) ||    \
                               ((type) == UART1_ID) ||    \
                               ((type) == UART2_ID) ||    \
                               ((type) == UART0_MM_ID) || \
                               ((type) == UART_ID_MAX))

/** @defgroup  UART_DIRECTION_TYPE
 *  @{
 */
#define IS_UART_DIRECTION_TYPE(type) (((type) == UART_TX) || \
                                      ((type) == UART_RX) || \
                                      ((type) == UART_TXRX))

/** @defgroup  UART_PARITY_TYPE
 *  @{
 */
#define IS_UART_PARITY_TYPE(type) (((type) == UART_PARITY_NONE) || \
                                   ((type) == UART_PARITY_ODD) ||  \
                                   ((type) == UART_PARITY_EVEN))

/** @defgroup  UART_DATABITS_TYPE
 *  @{
 */
#define IS_UART_DATABITS_TYPE(type) (((type) == UART_DATABITS_5) || \
                                     ((type) == UART_DATABITS_6) || \
                                     ((type) == UART_DATABITS_7) || \
                                     ((type) == UART_DATABITS_8))

/** @defgroup  UART_STOPBITS_TYPE
 *  @{
 */
#define IS_UART_STOPBITS_TYPE(type) (((type) == UART_STOPBITS_1) ||   \
                                     ((type) == UART_STOPBITS_1_5) || \
                                     ((type) == UART_STOPBITS_2))

/** @defgroup  UART_BYTEBITINVERSE_TYPE
 *  @{
 */
#define IS_UART_BYTEBITINVERSE_TYPE(type) (((type) == UART_LSB_FIRST) || \
                                           ((type) == UART_MSB_FIRST))

/** @defgroup  UART_AUTOBAUDDETECTION_TYPE
 *  @{
 */
#define IS_UART_AUTOBAUDDETECTION_TYPE(type) (((type) == UART_AUTOBAUD_0X55) || \
                                              ((type) == UART_AUTOBAUD_STARTBIT))

/** @defgroup  UART_RS485POLARITY_TYPE
 *  @{
 */
#define IS_UART_RS485POLARITY_TYPE(type) (((type) == UART_RS485_DE_ACTIVE_LOW) || \
                                          ((type) == UART_RS485_DE_ACTIVE_HIGH))

/** @defgroup  UART_INT_TYPE
 *  @{
 */
#define IS_UART_INT_TYPE(type) (((type) == UART_INT_TX_END) ||      \
                                ((type) == UART_INT_RX_END) ||      \
                                ((type) == UART_INT_TX_FIFO_REQ) || \
                                ((type) == UART_INT_RX_FIFO_REQ) || \
                                ((type) == UART_INT_RTO) ||         \
                                ((type) == UART_INT_PCE) ||         \
                                ((type) == UART_INT_TX_FER) ||      \
                                ((type) == UART_INT_RX_FER) ||      \
                                ((type) == UART_INT_LSE) ||         \
                                ((type) == UART_INT_BCR) ||         \
                                ((type) == UART_INT_STARTBIT) ||    \
                                ((type) == UART_INT_0X55) ||        \
                                ((type) == UART_INT_ALL))

/** @defgroup  UART_OVERFLOW_TYPE
 *  @{
 */
#define IS_UART_OVERFLOW_TYPE(type) (((type) == UART_TX_OVERFLOW) ||  \
                                     ((type) == UART_TX_UNDERFLOW) || \
                                     ((type) == UART_RX_OVERFLOW) ||  \
                                     ((type) == UART_RX_UNDERFLOW))

/*@} end of group UART_Public_Constants */

/** @defgroup  UART_Public_Macros
 *  @{
 */
#define UART_RX_FIFO_SIZE         128
#define UART_TX_FIFO_SIZE         128
#define UART_DEFAULT_RECV_TIMEOUT 80

/*@} end of group UART_Public_Macros */

/** @defgroup  UART_Public_Functions
 *  @{
 */

/**
 *  @brief UART Functions
 */
#if (defined BOOTROM) || (!defined BFLB_USE_HAL_DRIVER) || (defined BFLB_EFLASH_LOADER)
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void UART2_IRQHandler(void);
void UART3_IRQHandler(void);
void UART4_IRQHandler(void);
#endif
BL_Err_Type UART_SetBaudRate(UART_ID_Type uartId, uint32_t baudRate);
BL_Err_Type UART_Init(UART_ID_Type uartId, UART_CFG_Type *uartCfg);
BL_Err_Type UART_DeInit(UART_ID_Type uartId);
BL_Err_Type UART_FifoConfig(UART_ID_Type uartId, UART_FifoCfg_Type *fifoCfg);
BL_Err_Type UART_IrConfig(UART_ID_Type uartId, UART_IrCfg_Type *irCfg);
BL_Err_Type UART_Enable(UART_ID_Type uartId, UART_Direction_Type direct);
BL_Err_Type UART_Disable(UART_ID_Type uartId, UART_Direction_Type direct);
BL_Err_Type UART_SetTxDataLength(UART_ID_Type uartId, uint16_t length);
BL_Err_Type UART_SetRxDataLength(UART_ID_Type uartId, uint16_t length);
BL_Err_Type UART_SetRxTimeoutValue(UART_ID_Type uartId, uint8_t time);
BL_Err_Type UART_SetRxByteCount(UART_ID_Type uartId, uint16_t count);
BL_Err_Type UART_SetDeglitchCount(UART_ID_Type uartId, uint8_t deglitchCnt);
BL_Err_Type UART_ApplyAbrResult(UART_ID_Type uartId, UART_AutoBaudDetection_Type autoBaudDet);
BL_Err_Type UART_SetRtsValue(UART_ID_Type uartId);
BL_Err_Type UART_ClrRtsValue(UART_ID_Type uartId);
BL_Err_Type UART_SetTxValue(UART_ID_Type uartId);
BL_Err_Type UART_ClrTxValue(UART_ID_Type uartId);
BL_Err_Type UART_TxFreeRun(UART_ID_Type uartId, BL_Fun_Type txFreeRun);
BL_Err_Type UART_AutoBaudDetection(UART_ID_Type uartId, BL_Fun_Type autoBaud);
BL_Err_Type UART_SetAllowableError0X55(UART_ID_Type uartId, uint8_t allowableError);
BL_Err_Type UART_GetBitWidth0X55(UART_ID_Type uartId, uint16_t *width);
BL_Err_Type UART_SetRS485(UART_ID_Type uartId, BL_Fun_Type enable, UART_RS485Polarity_Type polarity);
BL_Err_Type UART_TxFifoClear(UART_ID_Type uartId);
BL_Err_Type UART_RxFifoClear(UART_ID_Type uartId);
BL_Err_Type UART_IntMask(UART_ID_Type uartId, UART_INT_Type intType, BL_Mask_Type intMask);
BL_Err_Type UART_IntClear(UART_ID_Type uartId, UART_INT_Type intType);
BL_Err_Type UART_Int_Callback_Install(UART_ID_Type uartId, UART_INT_Type intType, intCallback_Type *cbFun);
BL_Err_Type UART_SendData(UART_ID_Type uartId, uint8_t *data, uint32_t len);
BL_Err_Type UART_SendDataBlock(UART_ID_Type uartId, uint8_t *data, uint32_t len);
uint32_t UART_ReceiveData(UART_ID_Type uartId, uint8_t *data, uint32_t maxLen);
uint16_t UART_GetAutoBaudCount(UART_ID_Type uartId, UART_AutoBaudDetection_Type autoBaudDet);
uint16_t UART_GetRxByteCount(UART_ID_Type uartId);
uint8_t UART_GetTxFifoCount(UART_ID_Type uartId);
uint8_t UART_GetRxFifoCount(UART_ID_Type uartId);
BL_Sts_Type UART_GetIntStatus(UART_ID_Type uartId, UART_INT_Type intType);
BL_Sts_Type UART_GetTxBusBusyStatus(UART_ID_Type uartId);
BL_Sts_Type UART_GetRxBusBusyStatus(UART_ID_Type uartId);
BL_Sts_Type UART_GetOverflowStatus(UART_ID_Type uartId, UART_Overflow_Type overflow);

/*@} end of group UART_Public_Functions */

/*@} end of group UART */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_UART_H__ */
