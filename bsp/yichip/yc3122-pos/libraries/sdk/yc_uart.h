/*
 * Copyright (c); 2006-2020, YICHIP Development Team
 * @file     yc_uart.h
 * @brief    source file for setting uart
 *
 * Change Logs:
 * Date            Author             Version        Notes
 * 2020-11-06      wushengyan         V1.0.0         the first version
 */

#ifndef __YC_UART_H__
#define __YC_UART_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "yc3122.h"
#include "system.h"

/**
 * @defgroup UARTx
 */
#define IS_UART(UARTx)              (((UARTx) == MUART0) ||\
                                    ((UARTx) == MUART1) ||\
                                    ((UARTx) == MUART2) ||\
                                    ((UARTx) == MUART3))

/**
 * @defgroup UART_RxMode
 */
#define MODE_RX_ENABLE              1
#define MODE_RX_DISABLE             0
#define IS_UART_RX_MODE(MODE)       (((MODE) == MODE_RX_ENABLE) ||\
                                    ((MODE) == MODE_RX_DISABLE))

/**
 * @defgroup USART_Parity
 */
#define YC_PARITY_NONE                 0
#define YC_PARITY_EVEN                 0
#define YC_PARITY_ODD                  1
#define IS_UART_PARITY(PARITY)      (((PARITY) == YC_PARITY_NONE) ||\
                                    ((PARITY) == YC_PARITY_EVEN)  ||\
                                    ((PARITY) == YC_PARITY_ODD))

/**
 * @defgroup UART_DataBits
 */
#define DATABITS_8B                 0
#define DATABITS_9B                 1
#define IS_UART_WORD_LENGTH(LENGTH) (((LENGTH) == DATABITS_8B) || \
                                    ((LENGTH) == DATABITS_9B))

/**
 * @defgroup UART_Stop_Bits
 */
#define STOPBITS_1                  0
#define STOPBITS_2                  1
#define IS_UART_STOPBITS(STOPBITS)  (((STOPBITS) == STOPBITS_1) ||  \
                                    ((STOPBITS) == STOPBITS_2) )

/**
 * @defgroup UART_Hardware_Flow_Control
 */
#define FLOWCTRL_NONE               0
#define FLOWCTRL_ENABLE             1
#define IS_UART_FLOW_CTRL(CTRL)     (((CTRL) == FLOWCTRL_NONE) || \
                                    ((CTRL) == FLOWCTRL_ENABLE))

/**
 * @defgroup UART_Smart_Card_Control
 */
#define SMARTCARD_ENABLE            1
#define SMARTCARD_DISABLE           0
#define IS_UART_SMART_CARD(CTRL)    (((CTRL) == SMARTCARD_ENABLE) || \
                                    ((CTRL) == SMARTCARD_DISABLE))

/**
 * @defgroup UART_CommMode
 */
#define MODE_SINGLE_LINE            1
#define MODE_DUPLEX                 0
#define IS_UART_COMM_MODE(MODE)     (((MODE) == MODE_SINGLE_LINE) ||\
                                    ((MODE) == MODE_DUPLEX))

/**
 * @defgroup USART_BaudRate
 */
#define IS_UART_BAUDRATE(BAUDRATE)  (((BAUDRATE) > 0x5B8) &&\
                                    ((BAUDRATE) < 0x0044AA21))

/**
 * @defgroup UART_Interrupt_Type_definition
 */
#define UART_IT_TX                  0x01
#define UART_IT_RX                  0x02
#define IS_UART_IT(ITx)             (((ITx) == UART_IT_TX) || ((ITx) == UART_IT_RX))

typedef struct
{
    uint8_t RxMode;        /*!< Specifies wether the Receive or Transmit mode
                                is enabled or disabled. This parameter can be
                                a value of @ref UART_Mode */

    uint8_t Parity;        /*!< Specifies the parity mode.
                                This parameter can be a value of
                                @ref UART_Parity @note When parity is enabled,
                                the computed parity is inserted at
                                the MSB position of the transmitted data
                                (9th bit when the word length is set to
                                9 data bits; 8th bit when the word length is
                                set to 8 data bits);. */

    uint8_t DataBits;      /*!< Specifies the number of data bits transmitted
                                or received in a frame. This parameter can be
                                a value of @ref UART_DataBits */

    uint8_t StopBits;      /*!< Specifies the number of stop bits transmitted.
                                parameter can be a value of @ref UART_Stop_Bits */

    uint8_t FlowCtrl;      /*!< Specifies wether the hardware flow control mode
                                is enabled or disabled. This parameter can be
                                a value of @ref UART_Hardware_Flow_Control */

    uint8_t SmartCard;

    uint8_t CommMode;

    uint32_t BaudRate;     /*!< This member configures the USART
                                communication baud rate. */
} UART_InitTypeDef;

void UART_DeInit(UART_TypeDef *UARTx);
void UART_Init(UART_TypeDef *UARTx, UART_InitTypeDef *UART_InitStruct);
void UART_StructInit(UART_InitTypeDef *UART_InitStruct);
void UART_ITConfig(UART_TypeDef *UARTx, uint32_t UART_IT, FunctionalState NewState);
void UART_SendData(UART_TypeDef *UARTx, uint8_t Data);
void UART_SendBuf(UART_TypeDef *UARTx, uint8_t *buf, uint32_t len);
uint8_t UART_ReceiveData(UART_TypeDef *UARTx);
uint32_t UART_ReceiveBuf(UART_TypeDef *UARTx, uint8_t *buf, uint32_t len);
void UART_AutoFlowCtrlCmd(UART_TypeDef *UARTx, FunctionalState NewState);
uint8_t UART_GetITIdentity(UART_TypeDef *UARTx);
Boolean UART_IsRXFIFOFull(UART_TypeDef *UARTx);
Boolean UART_IsRXFIFONotEmpty(UART_TypeDef *UARTx);
Boolean UART_IsBusy(UART_TypeDef *UARTx);
void UART_SetITTimeout(UART_TypeDef *UARTx, uint16_t timeout);
void UART_SetRxITNum(UART_TypeDef *UARTx, uint8_t Bcnt);
uint32_t UART_ReceiveDataLen(UART_TypeDef *UARTx);

#ifdef __cplusplus
}
#endif

#endif

/************************ (C) COPYRIGHT Yichip Microelectronics *****END OF FILE****/
