/*
File Name    : yc_uart.h
Author       : Yichip
Version      : V1.0
Date         : 2019/12/4
Description  : UART encapsulation.
*/
#ifndef __YC_UART_H__
#define __YC_UART_H__

#include "yc3121.h"

/** @def time of UART receive data  time out intterrupt. real time = regvalue*48
  * @{
  */
#define TIME_IT_TIMEOUT (uint16_t)0x01

/** @defgroup USART_Mode
  * @{
  */
#define Mode_Single_Line       (1<<6)
#define Mode_duplex            (0<<6)
#define IS_MODE(MODE)  (((MODE) == Mode_Single_Line) ||\
                        ((MODE) == Mode_duplex))
/**
  * @}
  */

/** @
  * @defgroup USART_DataBits
  */
#define Databits_8b            (0<<2)
#define Databits_9b            (1<<2)

#define IS_USART_WORD_LENGTH(LENGTH)  (((LENGTH) == Databits_8b) || \
                                       ((LENGTH) == Databits_9b))
/**
  * @}
  */

/** @defgroup USART_Stop_Bits
  * @{
  */
#define StopBits_1            (0<<3)
#define StopBits_2            (1<<3)
#define IS_USART_STOPBITS(STOPBITS)  (((STOPBITS) == StopBits_1) ||  \
                                      ((STOPBITS) == StopBits_2) )
/**
  * @}
  */

/** @defgroup USART_Hardware_Flow_Control
  * @{
  */
#define FlowCtrl_None       (0<<4)
#define FlowCtrl_Enable     (1<<4)

#define IS_FlowCtrl(CONTROL)  (((CONTROL) == FlowCtrl_None) || \
                               ((CONTROL) == FlowCtrl_Enable))
/**
  * @}
  */

/** @defgroup UART_Interrupt_Type_definition
  * @{
  */
#define UART_IT_TX	      0x01
#define UART_IT_RX        0x02
#define IS_UART_IT(x)     (x == UART_IT_TX)||(x == UART_IT_RX)
/**
  * @}
  */

/** @defgroup USART_Parity
* @{
*/
#define   Parity_None       (0<<1)
#define   Parity_Even       (0<<1)
#define   Parity_Odd        (1<<1)
#define IS_PARITY(PARITY)  (((PARITY) == Parity_Even) ||\
                            ((PARITY) == Parity_None)  ||\
                            ((PARITY) == Parity_Odd))
/**
  * @}
  */

/** @defgroup USART_BaudRate
* @{
*/
#define IS_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0x5B8) && ((BAUDRATE) < 0x0044AA21))
/**
  * @}
  */

typedef struct
{
    uint8_t Mode;         /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                             This parameter can be a value of @ref USART_Mode */

    uint32_t BaudRate;    /*!< This member configures the USART communication baud rate. */

    uint8_t DataBits;     /*!< Specifies the number of data bits transmitted or received in a frame.
                             This parameter can be a value of @ref USART_DataBits */

    uint8_t StopBits;     /*!< Specifies the number of stop bits transmitted.
                             This parameter can be a value of @ref USART_Stop_Bits */

    uint8_t Parity;       /*!< Specifies the parity mode.
                             This parameter can be a value of @ref USART_Parity
                             @note When parity is enabled, the computed parity is inserted
                             at the MSB position of the transmitted data (9th bit when
                             the word length is set to 9 data bits; 8th bit when the
                             word length is set to 8 data bits). */

    uint8_t FlowCtrl;     /*!< Specifies wether the hardware flow control mode is enabled or disabled.
                             This parameter can be a value of @ref USART_Hardware_Flow_Control */

    int RxBufLen;          /*!< Specifies uart DMA Rx  buff length */

} UART_InitTypeDef;

/** @defgroup UART_TypeDef
* @{
*/
typedef enum
{
    UART0 = 0,
    UART1,
} UART_TypeDef;

#define IS_UART(UARTx) (UARTx == UART0 ||UARTx == UART1)
/**
 * @}
 */

/**
  * @brief  ENABLE or DISABLE UARTx auto flow control
  * @param  USARTx: Select the USART or the UART peripheral.
  *         This parameter can be one of the following values:
  *         UART0, UART1.
  * @param  NewState:ENABLE or DISABLE auto flow control
  * @retval None
  */
void UART_AutoFlowCtrlCmd(UART_TypeDef UARTx, FunctionalState NewState);

/**
  * @brief  Clear IT
  * @param  USARTx: Select the USART or the UART peripheral.
  *         This parameter can be one of the following values:
  *         UART0, UART1.
  * @retval None
  */
void UART_ClearIT(UART_TypeDef UARTx);

/**
  * @brief  DeInit UART
  * @param  UARTx: Select the UART peripheral.
  *         This parameter can be one of the following values:
  *         UART0, UART1.
  * @retval None
  */
void UART_DeInit(UART_TypeDef UARTx);

/**
  * @brief  Transmits datas via UART DMA .
  * @param  USARTx: Select the USART or the UART peripheral.
  *         This parameter can be one of the following values:
  *         UART0, UART1.
  * @param  buf: pointer to a buf that contains the data you want transmit.
  * @param  len: the buf length
  * @retval None
  */
void UART_DMASendBuf(UART_TypeDef UARTx, uint8_t *buf, int len);

/**
  * @brief  Get IT Identity
  * @param  UARTx: Select the UART peripheral.
  * @retval IT Identity
  */
uint8_t UART_GetITIdentity(UART_TypeDef UARTx);

/**
  * @brief  Initializes the USARTx peripheral according to the specified
  *         parameters in the USART_InitStruct .
  * @param  UARTx: Select the UART peripheral.
  *         This parameter can be one of the following values:
  *         UART0, UART1.
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure
  *         that contains the configuration information for the specified USART
  *         peripheral.
  * @retval None
  */
void UART_Init(UART_TypeDef UARTx, UART_InitTypeDef *UART_InitStruct);

/**
  * @brief  Judge Rx fifo full is or not.
  * @param  UARTx: Select the UART peripheral.
  * @retval TRUE:Rx fifo is full.
  *         FALSE:Rx fifo is not full
  */
Boolean UART_IsRXFIFOFull(UART_TypeDef UARTx);

/**
  * @brief  Judge Rx fifo empty is or not.
  * @param  UARTx: Select the UART peripheral.
  * @retval TRUE:Rx fifo is not empty.
  *         FALSE:Rx fifo is empty;
  */
Boolean UART_IsRXFIFONotEmpty(UART_TypeDef UARTx);

/**
  * @brief  Judge UART is Busy or not
  * @param  UARTx: Select the UART peripheral.
  * @retval None
  */
Boolean UART_IsUARTBusy(UART_TypeDef  UARTx);

/**
  * @brief  Config Interrupt trigger mode
  * @param  USARTx: Select the USART or the UART peripheral.
  *                 This parameter can be one of the following values:
  *                 UART0, UART1.
  * @param  UART_IT: Interrupt trigger mode ,this param will the following values,
  *         UART_IT_TX:interrupt trigger after send data completed.
  *         UART_IT_RX:interrupt trigger when received data.
  * @param  NewState:
  * @retval None
  */
void UART_ITConfig(UART_TypeDef UARTx, uint32_t UART_IT, FunctionalState NewState);

/**
  * @brief  Receive single data through the USARTx peripheral.
  * @param  USARTx: Select the USART or the UART peripheral.
  *   This parameter can be one of the following values:
  *   UART0, UART1.
  * @retval None
  */
uint8_t UART_ReceiveData(UART_TypeDef UARTx);

/**
  * @brief  Receives datas through the UART DMA.
  * @param  USARTx: Select the USART or the UART peripheral.
  *         This parameter can be one of the following values:
  *         UART0, UART1.
  * @param  buf: pointer to a buf that contains the data you want receive.
  * @param  len: the buf length
  * @retval None
  */
int UART_RecvBuf(UART_TypeDef UARTx, uint8_t *buf, int len);

/**
  * @brief T ransmits datas via UART DMA,the function will return after datas is sent.
  * @param USARTx: Select the USART or the UART peripheral.
  *          This parameter can be one of the following values:
  *         UART0, UART1.
  * @param  buf: pointer to a buf that contains the data you want transmit.
  * @param  len: the buf length
  * @retval None
  */
void UART_SendBuf(UART_TypeDef UARTx, uint8_t *buf, int len);

/**
  * @brief  UART Send One Data
  * @param  UARTx: Select  the UART peripheral.
  * @retval None
  */
void UART_SendData(UART_TypeDef UARTx, uint8_t Data);

/**
  * @brief  UART_SetITTimeout
  * @param  USARTx: Select the USART or the UART peripheral.
  *         This parameter can be one of the following values:
  *         UART0, UART1.
	*         timeout: 0x0000~0xffff
  * @retval None
  */
void UART_SetITTimeout(UART_TypeDef UARTx, uint16_t timeout);

/**
  * @brief  Set the number of uart receive data intterupt trigger
  * @param  UARTx: Select the UART peripheral.
  *         This parameter can be one of the following values:
  *         UART0, UART1.
  * @param  Bcnt: if the number of receive datas greater than Bcnt,interrupt trigger
  * @retval None
  */
void UART_SetRxITNum(UART_TypeDef UARTx, uint8_t Bcnt);

/**
  * @brief  Fills each USART_InitStruct member with its default value.
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void UART_StructInit(UART_InitTypeDef *UART_InitStruct);

/**
  * @brief  UART_ReceiveDataLen
  * @param  UARTx: UART0 or UART1
  * @retval Data len
  */
uint16_t UART_ReceiveDataLen(UART_TypeDef UARTx);

#endif /*__YC_UART_H__*/
