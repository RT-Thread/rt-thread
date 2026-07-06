/**
******************************************************************************
* @file  HAL_UART.h
* @author  IC Applications Department
* @version  V0.8
* @date  2019_08_02
* @brief  This file contains all the functions prototypes for the UART
*         firmware library.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, HOLOCENE SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2016 HOLOCENE</center></h2>
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_UART_H
#define __HAL_UART_H

/* Includes ------------------------------------------------------------------*/
#include "HAL_device.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @addtogroup UART
* @{
*/

/** @defgroup UART_Exported_Types
* @{
*/

/**
* @brief  UART Init Structure definition
*/

typedef struct
{
  uint32_t UART_BaudRate;
  uint16_t UART_WordLength;
  uint16_t UART_StopBits;
  uint16_t UART_Parity;
  uint16_t UART_Mode;
  uint16_t UART_HardwareFlowControl;
} UART_InitTypeDef;


/**
* @}
*/

/** @defgroup UART_Exported_Constants
* @{
*/

#define IS_UART_ALL_PERIPH(PERIPH) (((*(uint32_t*)&(PERIPH)) == UART1_BASE) || \
((*(uint32_t*)&(PERIPH)) == UART2_BASE) || \
  ((*(uint32_t*)&(PERIPH)) == UART3_BASE))
#define IS_UART_123_PERIPH(PERIPH) (((*(uint32_t*)&(PERIPH)) == UART1_BASE) || \
((*(uint32_t*)&(PERIPH)) == UART2_BASE) || \
  ((*(uint32_t*)&(PERIPH)) == UART3_BASE))

/** @defgroup UART_Word_Length
* @{
*/

#define UART_WordLength_5b                  ((uint16_t)0x0000)
#define UART_WordLength_6b                  ((uint16_t)0x0010)
#define UART_WordLength_7b                  ((uint16_t)0x0020)
#define UART_WordLength_8b                  ((uint16_t)0x0030)


#define IS_UART_WORD_LENGTH(LENGTH) (((LENGTH) == UART_WordLength_5b) || \
((LENGTH) == UART_WordLength_6b) || \
  ((LENGTH) == UART_WordLength_7b) || \
    ((LENGTH) == UART_WordLength_8b))
/**
* @}
*/

/** @defgroup UART_Stop_Bits
* @{
*/

#define UART_StopBits_1                     ((uint16_t)0x0000)
#define UART_StopBits_2                     ((uint16_t)0x0004)

#define IS_UART_STOPBITS(STOPBITS) (((STOPBITS) == UART_StopBits_1) || \
((STOPBITS) == UART_StopBits_2))

/**
* @}
*/

/** @defgroup UART_Parity
* @{
*/

#define UART_Parity_No                      ((uint16_t)0x0000)
#define UART_Parity_Even                    ((uint16_t)0x0003)
#define UART_Parity_Odd                     ((uint16_t)0x0001)
#define IS_UART_PARITY(PARITY) (((PARITY) == UART_Parity_No) || \
((PARITY) == UART_Parity_Even) || \
  ((PARITY) == UART_Parity_Odd))
/**
* @}
*/

/** @defgroup UART_Mode
* @{
*/

#define UART_Mode_Rx                        ((uint16_t)0x0008)
#define UART_Mode_Tx                        ((uint16_t)0x0010)
#define IS_UART_MODE(MODE) ((((MODE) & (uint16_t)0xFFE7) == 0x00) && ((MODE) != (uint16_t)0x00))

#define UART_EN                             ((uint16_t)0x0001)

/**
* @}
*/

/** @defgroup UART_Hardware_Flow_Control
* @{
*/
#define UART_HardwareFlowControl_None       ((uint16_t)0x0000)

#define IS_UART_HARDWARE_FLOW_CONTROL(CONTROL)\
(((CONTROL) == UART_HardwareFlowControl_None) || \
  ((CONTROL) == UART_HardwareFlowControl_RTS) || \
    ((CONTROL) == UART_HardwareFlowControl_CTS) || \
      ((CONTROL) == UART_HardwareFlowControl_RTS_CTS))

/** @defgroup UART_Interrupt_definition
* @{
*/


#define UART_IT_ERR            ((uint16_t)0x0020)
#define UART_IT_PE             ((uint16_t)0x0010)
#define UART_OVER_ERR          ((uint16_t)0x0008)
#define UART_TIMEOUT_ERR       ((uint16_t)0x0004)
#define UART_IT_RXIEN          ((uint16_t)0x0002)
#define UART_IT_TXIEN          ((uint16_t)0x0001)

#define IS_UART_CONFIG_IT(IT) (((IT) == UART_IT_PE) || ((IT) == UART_IT_TXIEN) || \
((IT) == UART_IT_RXIEN) || ((IT) == UART_IT_ERR))

#define IS_UART_GET_IT(IT) (((IT) == UART_IT_PE) || ((IT) == UART_IT_TXIEN) || \
((IT) == UART_IT_ERR) || ((IT) == UART_IT_RXIEN) || \
  ((IT) == UART_OVER_ERR) || ((IT) == UART_TIMEOUT_ERR))

#define IS_UART_CLEAR_IT(IT) ((IT) == UART_IT_RXIEN)


/**
* @}
*/

/** @defgroup UART_DMA_Requests
* @{
*/
#define UART_DMAReq_EN                      ((uint16_t)0x0002)

#define IS_UART_DMAREQ(DMAREQ) ((((DMAREQ) & (uint16_t)0xFFFD) == 0x00) && ((DMAREQ) != (uint16_t)0x00))

/**
* @}
*/


/** @defgroup UART_Flags
* @{
*/


#define UART_FLAG_TXEMPTY                   ((uint16_t)0x0008)
#define UART_FLAG_TXFULL                    ((uint16_t)0x0004)
#define UART_FLAG_RXAVL                     ((uint16_t)0x0002)
#define UART_FLAG_TXEPT                     ((uint16_t)0x0001)


#define IS_UART_FLAG(FLAG) (((FLAG) == UART_FLAG_TXEMPTY) || ((FLAG) == UART_FLAG_TXFULL) || \
((FLAG) == UART_FLAG_RXAVL) || ((FLAG) == UART_FLAG_TXEPT))


#define IS_UART_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0x00FF) == 0x00) && ((FLAG) != (uint16_t)0x00))

#define IS_UART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) < 0x0044AA21))
#define IS_UART_ADDRESS(ADDRESS) ((ADDRESS) <= 0xF)
#define IS_UART_DATA(DATA) ((DATA) <= 0x1FF)

/**
* @}
*/

/**
* @}
*/

/** @defgroup UART_Exported_Macros
* @{
*/

/**
* @}
*/

/** @defgroup UART_Exported_Functions
* @{
*/

void UART_DeInit(UART_TypeDef* UARTx);
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct);
void UART_StructInit(UART_InitTypeDef* UART_InitStruct);
void UART_Cmd(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_ITConfig(UART_TypeDef* UARTx, uint16_t UART_IT, FunctionalState NewState);
void UART_DMACmd(UART_TypeDef* UARTx, uint16_t UART_DMAReq, FunctionalState NewState);
void UART_SendData(UART_TypeDef* UARTx, uint16_t Data);
uint16_t UART_ReceiveData(UART_TypeDef* UARTx);
FlagStatus UART_GetFlagStatus(UART_TypeDef* UARTx, uint16_t UART_FLAG);
void UART_ClearFlag(UART_TypeDef* UARTx, uint16_t UART_FLAG);
ITStatus UART_GetITStatus(UART_TypeDef* UARTx, uint16_t UART_IT);
void UART_ClearITPendingBit(UART_TypeDef* UARTx, uint16_t UART_IT);
#endif /* __HAL_UART_H */
/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2016 HOLOCENE ----------------------*/
