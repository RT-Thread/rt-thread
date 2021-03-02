/**
    *****************************************************************************
    * @file     cmem7_uart.h
    *
    * @brief    CMEM7 uart header file
    *
    *
    * @version  V1.0
    * @date     3. September 2013
    *
    * @note
    *
    *****************************************************************************
    * @attention
    *
    * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
    * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
    * TIME. AS A RESULT, CAPITAL-MICRO SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
    * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
    * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
    * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
    *
    * <h2><center>&copy; COPYRIGHT 2013 Capital-micro </center></h2>
    *****************************************************************************
    */

#ifndef __CMEM7_UART_H
#define __CMEM7_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "cmem7.h"
#include "cmem7_conf.h"

#define IS_UART_ALL_PERIPH(PERIPH) (((PERIPH) == UART0) || \
                                     ((PERIPH) == UART1) || \
                                     ((PERIPH) == UART2))

/** @defgroup UART_StopBits
  * @{
  */
#define UART_StopBits_0_5                 0
#define UART_StopBits_1                   1
#define UART_StopBits_1_5                 2
#define UART_StopBits_2                   3
#define IS_UART_STOPBITS(STOPBITS) (((STOPBITS) == UART_StopBits_1) || \
                                     ((STOPBITS) == UART_StopBits_0_5) || \
                                     ((STOPBITS) == UART_StopBits_2) || \
                                     ((STOPBITS) == UART_StopBits_1_5))
/**
  * @}
  */

/** @defgroup UART_Parity
  * @{
  */
#define UART_Parity_Even                  0
#define UART_Parity_Odd                   1
#define UART_Parity_None                  2
#define IS_UART_PARITY(PARITY) (((PARITY) == UART_Parity_Even) || \
                                 ((PARITY) == UART_Parity_Odd) || \
                                                                 ((PARITY) == UART_Parity_None))
/**
  * @}
  */

/** @defgroup UART_Int
  * @{
  */
#define UART_Int_RxNotEmpty               0x00000001
#define UART_Int_TxEmpty                  0x00000002
#define UART_Int_TxHalfEmpty              0x00000004
#define UART_Int_TxTimeoutNotEmpty        0x00000008
#define UART_Int_TxTimeoutEmpty           0x00000010
#define UART_Int_RxHalfFull               0x00000020
#define UART_Int_TxFull                   0x00000040
#define UART_Int_ParityError              0x00000080
#define UART_Int_FrameError               0x00000100
#define UART_Int_OverrunError             0x00000200
#define UART_Int_RxThresholdReach         0x00000400
#define UART_Int_All                      0x000007FF

#define IS_UART_INT(INT)        (((INT) != 0) && (((INT) & ~UART_Int_All) == 0))

/**
  * @}
  */

/**
  * @brief  UART initialization structure
    */
typedef struct
{
    uint32_t UART_BaudRate;            /*!< Baudrate */
    uint8_t UART_StopBits;             /*!< Specifies the number of stop bits transmitted,
                                                                                    It's a value of @ref UART_StopBits */
    uint8_t UART_Parity;               /*!< Specifies the parity mode.
                                                                                    It's a value of @ref UART_Parity */
    BOOL UART_LoopBack;                /*!< loop back mode */
    BOOL UART_RxEn;                    /*!< Receive enable bit */
    BOOL UART_CtsEn;                   /*!< Clear to set */
} UART_InitTypeDef;

/**
  * @brief  UART initialization
  * @note   This function should be called at first before any other interfaces.
    * @param[in] UARTx UART peripheral, which is UART0, UART1 or UART2
    * @param[in] init A pointer to structure UART_InitTypeDef
  * @retval None
    */
void UART_Init(UART0_Type* UARTx, UART_InitTypeDef *init);

/**
  * @brief  Enable or disable UART interrupt.
    * @param[in] UARTx UART peripheral, which is UART0, UART1 or UART2
    * @param[in] Int interrupt mask bits, which can be the combination of @ref UART_Int
    * @param[in] Enable The bit indicates if specific interrupts are enable or not
  * @retval None
    */
void UART_EnableInt(UART0_Type* UARTx, uint32_t Int, BOOL Enable);

/**
  * @brief  Enable or disable UART.
    * @param[in] UARTx UART peripheral, which is UART0, UART1 or UART2
    * @param[in] Enable The bit indicates if the specific UART is enable or not
  * @retval None
    */
void UART_Enable(UART0_Type* UARTx, BOOL enable);

/**
  * @brief  Check specific interrupts are set or not
    * @param[in] UARTx UART peripheral, which is UART0, UART1 or UART2
    * @param[in] Int interrupt mask bits, which can be the combination of @ref UART_Int
  * @retval BOOL The bit indicates if specific interrupts are set or not
    */
BOOL UART_GetIntStatus(UART0_Type* UARTx, uint32_t Int);

/**
  * @brief  Clear specific interrupts
    * @param[in] UARTx UART peripheral, which is UART0, UART1 or UART2
    * @param[in] Int interrupt mask bits, which can be the combination of @ref UART_Int
  * @retval None
    */
void UART_ClearInt(UART0_Type* UARTx, uint32_t Int);

/**
  * @brief  Write data to UART
    * @param[in] UARTx UART peripheral, which is UART0, UART1 or UART2
    * @param[in] Size Expected data size to be written
    * @param[in] Data A pointer to the data to be written
  * @retval uint8_t Actual written data size
    */
uint8_t UART_Write(UART0_Type* UARTx, uint8_t Size, uint8_t* Data);

/**
  * @brief  Read data from UART
    * @param[in] UARTx UART peripheral, which is UART0, UART1 or UART2
    * @param[in] Size Expected data size to be read
    * @param[out] Data A user-allocated buffer to fetch data to be read
  * @retval uint8_t Actual read data size
    */
uint8_t UART_Read(UART0_Type* UARTx, uint8_t Size, uint8_t* Data);


#ifdef __cplusplus
}
#endif

#endif /* __CMEM7_UART_H */

