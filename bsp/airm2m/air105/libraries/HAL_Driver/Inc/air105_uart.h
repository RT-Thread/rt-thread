/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef __AIR105_UART_H
#define __AIR105_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "air105.h"

/**
  * @brief  UART Init Structure definition
  */

typedef struct
{
  uint32_t UART_BaudRate;            /*!< This member configures the UART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (UART_InitStruct->UART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

  uint32_t UART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref UART_Word_Length */

  uint32_t UART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref UART_Stop_Bits */

  uint32_t UART_Parity;              /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref UART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                at the MSB position of the transmitted data (9th bit when
                                                the word length is set to 9 data bits; 8th bit when the
                                                word length is set to 8 data bits). */

} UART_InitTypeDef;
/**
  * @}
  */

#define IS_UART_PERIPH(PERIPH) (((PERIPH) == UART0) || \
                                ((PERIPH) == UART1) || \
                                ((PERIPH) == UART2) || \
                                ((PERIPH) == UART3))

/**
  * @brief  UART FIFO Init Structure definition
  */
typedef struct
{
    FunctionalState FIFO_Enable;
    uint32_t FIFO_DMA_Mode;
    uint32_t FIFO_RX_Trigger;
    uint32_t FIFO_TX_Trigger;
    uint32_t FIFO_TX_TriggerIntEnable;
}UART_FIFOInitTypeDef;
/**
  * @}
  */

/** @defgroup UART_Word_Length
  * @{
  */

#define UART_WordLength_5b                  (0x00000000)
#define UART_WordLength_6b                  (0x00000001)
#define UART_WordLength_7b                  (0x00000002)
#define UART_WordLength_8b                  (0x00000003)

#define IS_UART_WORD_LENGTH(LENGTH)         (((LENGTH) == UART_WordLength_5b) || \
                                            ((LENGTH) == UART_WordLength_6b) || \
                                            ((LENGTH) == UART_WordLength_7b) || \
                                            ((LENGTH) == UART_WordLength_8b))
/**
  * @}
  */

/** @defgroup UART_Stop_Bits
  * @{
  */

#define UART_StopBits_1                         (0x00000000)
#define UART_StopBits_1_5                       (0x00000004)
#define UART_StopBits_2                         (0x00000004)
#define IS_UART_STOPBITS(STOPBITS, DATALENGTH)  (((STOPBITS) == UART_StopBits_1) || \
                                                ((STOPBITS) == UART_StopBits_1_5 && DATALENGTH == UART_WordLength_5b) || \
                                                ((STOPBITS) == UART_StopBits_2 && DATALENGTH != UART_WordLength_5b))
/**
  * @}
  */

/** @defgroup UART_Parity
  * @{
  */

#define UART_Parity_No                              (0x00000000)
#define UART_Parity_Even                            (0x00000018)
#define UART_Parity_Odd                             (0x00000008)
#define IS_UART_PARITY(PARITY)                      (((PARITY) == UART_Parity_No) || \
                                                     ((PARITY) == UART_Parity_Even) || \
                                                     ((PARITY) == UART_Parity_Odd))
/**
  * @}
  */

/** @defgroup UART_Mode
  * @{
  */

#define UART_Mode_Rx                        ((uint16_t)0x0001)
#define UART_Mode_Tx                        ((uint16_t)0x0002)
#define IS_UART_MODE(MODE)                  ((((MODE) & (uint16_t)0xFFFC) == 0x00) && ((MODE) != (uint16_t)0x00))
/**
  * @}
  */

/** @defgroup UART_Set_Check_define
  * @{
  */

#define IS_UART_DATA(DATA)                  ((DATA) <= 0x000001FF)
#define IS_UART_BAUDRATE(BAUDRATE)          (((BAUDRATE) > 0) && ((BAUDRATE) < 0x0044AA21))

/**
  * @}
  */

/** @defgroup UART_Interrupt_definition
  * @{
  */

#define UART_IT_RX_RECVD                                        (UART_IER_ERBFI)
#define UART_IT_TX_EMPTY                                        (UART_IER_ETBEI)
#define UART_IT_LINE_STATUS                                     (UART_IER_ELSI)
#define UART_IT_MODEM_STATUS                                    (UART_IER_EDSSI)

/**
  * @}
  */


/** @defgroup UART_Interrupt_identity
  * @{
  */

#define UART_IT_ID_MODEM_STATUS                                 ((uint32_t)0x0000)
#define UART_IT_ID_NO_INTERRUPT                                 ((uint32_t)0x0001)
#define UART_IT_ID_TX_EMPTY                                     ((uint32_t)0x0002)
#define UART_IT_ID_RX_RECVD                                     ((uint32_t)0x0004)
#define UART_IT_ID_LINE_STATUS                                  ((uint32_t)0x0006)
#define UART_IT_ID_BUSY_DETECT                                  ((uint32_t)0x0007)
#define UART_IT_ID_CHAR_TIMEOUT                                 ((uint32_t)0x000C)

/**
  * @}
  */


/** @defgroup UART_FIFO_Control_define
  * @{
  */

#define UART_FIFO_DEPTH                                         (16)

#define UART_FIFO_RX                                            ((uint32_t)0x0000)
#define UART_FIFO_TX                                            ((uint32_t)0x0001)

#define UART_FIFO_DMA_Mode_0                                    ((uint32_t)0x0000)
#define UART_FIFO_DMA_Mode_1                                    ((uint32_t)0x0001)

#define UART_FIFO_RX_Trigger_1_Char                             ((uint32_t)0x0000)
#define UART_FIFO_RX_Trigger_1_4_Full                           ((uint32_t)0x0001)
#define UART_FIFO_RX_Trigger_1_2_Full                           ((uint32_t)0x0002)
#define UART_FIFO_RX_Trigger_2_CharLessFull                     ((uint32_t)0x0003)

#define UART_FIFO_TX_Trigger_Empty                              ((uint32_t)0x0000)
#define UART_FIFO_TX_Trigger_2_Chars                            ((uint32_t)0x0001)
#define UART_FIFO_TX_Trigger_1_4_Full                           ((uint32_t)0x0002)
#define UART_FIFO_TX_Trigger_1_2_Full                           ((uint32_t)0x0003)

/**
  * @}
  */


/** @defgroup UART_Line_Status_Flag_define
  * @{
  */
#define UART_LINE_STATUS_RX_RECVD                               (UART_LSR_DR)
#define UART_LINE_STATUS_RX_OVERRUN_ERROR                       (UART_LSR_OE)
#define UART_LINE_STATUS_RX_PARITY_ERROR                        (UART_LSR_PE)
#define UART_LINE_STATUS_RX_FRAMING_ERROR                       (UART_LSR_FE)
#define UART_LINE_STATUS_RX_BREAK_INTERRUPT                     (UART_LSR_BI)
#define UART_LINE_STATUS_TX_HOLDING_REGISTER_EMPTY              (UART_LSR_THRE)
#define UART_LINE_STATUS_TX_EMPTY                               (UART_LSR_TEMT)
#define UART_LINE_STATUS_RX_FIFO_ERROR                          (UART_LSR_PFE)

/**
  * @}
  */


/** @defgroup UART_Modem_Status_Flag_define
  * @{
  */
#define UART_MODEM_STATUS_CTS_CHANGED                           (UART_MSR_DCTS)
#define UART_MODEM_STATUS_DSR_CHANGED                           (UART_MSR_DDSR)
#define UART_MODEM_STATUS_RI_CHANGED                            (UART_MSR_TERI)
#define UART_MODEM_STATUS_DCD_CHANGED                           (UART_MSR_DDCD)
#define UART_MODEM_STATUS_CTS                                   (UART_MSR_CTS)
#define UART_MODEM_STATUS_DSR                                   (UART_MSR_DSR)
#define UART_MODEM_STATUS_RI                                    (UART_MSR_RI)
#define UART_MODEM_STATUS_DCD                                   (UART_MSR_DCD)
/**
  * @}
  */


/** @defgroup UART_Status_Flag_define
  * @{
  */
#define UART_STATUS_BUSY                                        (UART_USR_BUSY)
#define UART_STATUS_TX_FIFO_NOT_FULL                            (UART_USR_TFNF)
#define UART_STATUS_TX_FIFO_EMPTY                               (UART_USR_TFE)
#define UART_STATUS_RX_FIFO_NOT_EMPTY                           (UART_USR_RFNE)
#define UART_STATUS_RX_FIFO_FULL                                (UART_USR_RFF)



/**
  * @}
  */

void UART_DeInit(UART_TypeDef* UARTx);
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct);
void UART_StructInit(UART_InitTypeDef* UART_InitStruct);
void UART_ITConfig(UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState);
void UART_SendData(UART_TypeDef* UARTx, uint8_t Data);
uint8_t UART_ReceiveData(UART_TypeDef* UARTx);
void UART_FIFOInit(UART_TypeDef* UARTx, UART_FIFOInitTypeDef* UART_FIFOInitStruct);
void UART_FIFOStructInit(UART_FIFOInitTypeDef* UART_FIFOInitStruct);
void UART_FIFOReset(UART_TypeDef* UARTx, uint32_t UART_FIFO);
void UART_FIFOCmd(UART_TypeDef* UARTx,FunctionalState NewState);
void UART_SetRTS(UART_TypeDef* UARTx);
void UART_ResetRTS(UART_TypeDef* UARTx);
void UART_SetDTR(UART_TypeDef* UARTx);
void UART_ResetDTR(UART_TypeDef* UARTx);
void UART_SendBreak(UART_TypeDef* UARTx);
void UART_AutoFlowCtrlCmd(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_IrDACmd(UART_TypeDef* UARTx, FunctionalState NewState);

uint32_t UART_GetLineStatus(UART_TypeDef* UARTx);
uint32_t UART_GetModemStatus(UART_TypeDef* UARTx);
uint32_t UART_GetITIdentity(UART_TypeDef* UARTx);

Boolean UART_IsTXEmpty(UART_TypeDef* UARTx);
Boolean UART_IsTXHoldingRegisterEmpty(UART_TypeDef* UARTx);

Boolean UART_IsRXFIFOFull(UART_TypeDef* UARTx);
Boolean UART_IsRXFIFONotEmpty(UART_TypeDef* UARTx);
Boolean UART_IsTXFIFOEmpty(UART_TypeDef* UARTx);
Boolean UART_IsTXFIFONotFull(UART_TypeDef* UARTx);
Boolean UART_IsBusy(UART_TypeDef* UARTx);

void UART_DMAGenerateSoftAck(UART_TypeDef* UARTx);

void UART_TXHaltCmd(UART_TypeDef* UARTx, FunctionalState NewStatus);
void UART_FIFOAccessModeCmd(UART_TypeDef* UARTx, FunctionalState NewStatus);
uint8_t UART_FIFOTxRead(UART_TypeDef* UARTx);


#ifdef __cplusplus
}
#endif

#endif // __AIR105_UART_H

/**************************      (C) COPYRIGHT Megahunt    *****END OF FILE****/
