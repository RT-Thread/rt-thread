/**
 *******************************************************************************
 * @file  hc32_ll_usart.h
 * @brief This file contains all the functions prototypes of the USART(Universal
 *        Synchronous/Asynchronous Receiver Transmitter) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-06-30       CDT             Modify typo
                                    Change macro-definition: USART_DR_MPID -> USART_TDR_MPID
                                    Modify USART_SetTransType parameter: u32Type -> u16Type
                                    Modify USART_SC_ETU_CLK128/256 value
                                    Modify return type of function USART_DeInit
   2023-09-30       CDT             Remove u32StopBit param from stc_usart_smartcard_init_t structure
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32_LL_USART_H__
#define __HC32_LL_USART_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_USART
 * @{
 */

#if (LL_USART_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Types USART Global Types
 * @{
 */

/**
 * @brief clock synchronization mode initialization structure definition
 * @note The parameter(u32ClockDiv/u32CKOutput/u32Baudrate) is valid when clock source is the internal clock.
 */
typedef struct {
    uint32_t u32ClockSrc;               /*!< Clock Source.
                                             This parameter can be a value of @ref USART_Clock_Source */
    uint32_t u32ClockDiv;               /*!< Clock division.
                                             This parameter can be a value of @ref USART_Clock_Division. */
    uint32_t u32Baudrate;               /*!< USART baudrate.
                                             This parameter is valid when clock source is the internal clock. */
    uint32_t u32FirstBit;               /*!< Significant bit.
                                             This parameter can be a value of @ref USART_First_Bit */
    uint32_t u32HWFlowControl;          /*!< Hardware flow control.
                                             This parameter can be a value of @ref USART_Hardware_Flow_Control */
} stc_usart_clocksync_init_t;

/**
 * @brief UART multiple-processor initialization structure definition
 * @note The parameter(u32ClockDiv/u32CKOutput/u32Baudrate) is valid when clock source is the internal clock.
 */
typedef struct {
    uint32_t u32ClockSrc;               /*!< Clock Source.
                                             This parameter can be a value of @ref USART_Clock_Source */
    uint32_t u32ClockDiv;               /*!< Clock division.
                                             This parameter can be a value of @ref USART_Clock_Division. */
    uint32_t u32CKOutput;               /*!< USART_CK output selection.
                                             This parameter can be a value of @ref USART_CK_Output_Selection. */
    uint32_t u32Baudrate;               /*!< USART baudrate.
                                             This parameter is valid when clock source is the internal clock. */
    uint32_t u32DataWidth;              /*!< Data width.
                                             This parameter can be a value of @ref USART_Data_Width_Bit */
    uint32_t u32StopBit;                /*!< Stop Bits.
                                             This parameter can be a value of @ref USART_Stop_Bit */
    uint32_t u32OverSampleBit;          /*!< Oversampling Bits.
                                             This parameter can be a value of @ref USART_Over_Sample_Bit */
    uint32_t u32FirstBit;               /*!< Significant bit.
                                             This parameter can be a value of @ref USART_First_Bit */
    uint32_t u32StartBitPolarity;       /*!< Start Bit Detect Polarity.
                                             This parameter can be a value of @ref USART_Start_Bit_Polarity */
    uint32_t u32HWFlowControl;          /*!< Hardware flow control.
                                             This parameter can be a value of @ref USART_Hardware_Flow_Control */
} stc_usart_multiprocessor_init_t;

/**
 * @brief UART mode initialization structure definition
 * @note The parameter(u32ClockDiv/u32CKOutput/u32Baudrate) is valid when clock source is the internal clock.
 */
typedef struct {
    uint32_t u32ClockSrc;               /*!< Clock Source.
                                             This parameter can be a value of @ref USART_Clock_Source */
    uint32_t u32ClockDiv;               /*!< Clock division.
                                             This parameter can be a value of @ref USART_Clock_Division. */
    uint32_t u32CKOutput;               /*!< USART_CK output selection.
                                             This parameter can be a value of @ref USART_CK_Output_Selection. */
    uint32_t u32Baudrate;               /*!< USART baudrate.
                                             This parameter is valid when clock source is the internal clock. */
    uint32_t u32DataWidth;              /*!< Data width.
                                             This parameter can be a value of @ref USART_Data_Width_Bit */
    uint32_t u32StopBit;                /*!< Stop Bits.
                                             This parameter can be a value of @ref USART_Stop_Bit */
    uint32_t u32Parity;                 /*!< Parity format.
                                             This parameter can be a value of @ref USART_Parity_Control */
    uint32_t u32OverSampleBit;          /*!< Oversampling Bits.
                                             This parameter can be a value of @ref USART_Over_Sample_Bit */
    uint32_t u32FirstBit;               /*!< Significant bit.
                                             This parameter can be a value of @ref USART_First_Bit */
    uint32_t u32StartBitPolarity;       /*!< Start Bit Detect Polarity.
                                             This parameter can be a value of @ref USART_Start_Bit_Polarity */
    uint32_t u32HWFlowControl;          /*!< Hardware flow control.
                                             This parameter can be a value of @ref USART_Hardware_Flow_Control */
} stc_usart_uart_init_t;

/**
 * @brief Smartcard mode initialization structure definition
 */
typedef struct {
    uint32_t u32ClockDiv;               /*!< Clock division. This parameter can be a value of @ref USART_Clock_Division.
                                             @note This parameter is valid when clock source is the internal clock. */
    uint32_t u32CKOutput;               /*!< USART_CK output selection. This parameter can be a value of @ref USART_CK_Output_Selection.
                                             @note This parameter is valid when clock source is the internal clock. */
    uint32_t u32Baudrate;               /*!< USART baudrate.
                                             This parameter is calculated according with smartcard default ETU and clock. */
    uint32_t u32FirstBit;               /*!< Significant bit.
                                             This parameter can be a value of @ref USART_First_Bit */
} stc_usart_smartcard_init_t;

/**
 * @}
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Macros USART Global Macros
 * @{
 */

/**
 * @defgroup USART_Flag USART Flag
 * @{
 */
#define USART_FLAG_RX_FULL              (USART_SR_RXNE)     /*!< Receive data register not empty flag */
#define USART_FLAG_OVERRUN              (USART_SR_ORE)      /*!< Overrun error flag */
#define USART_FLAG_TX_CPLT              (USART_SR_TC)       /*!< Transmission complete flag */
#define USART_FLAG_TX_EMPTY             (USART_SR_TXE)      /*!< Transmit data register empty flag */
#define USART_FLAG_FRAME_ERR            (USART_SR_FE)       /*!< Framing error flag */
#define USART_FLAG_PARITY_ERR           (USART_SR_PE)       /*!< Parity error flag */
#define USART_FLAG_MX_PROCESSOR         (USART_SR_MPB)      /*!< Receive processor ID flag */
#define USART_FLAG_RX_TIMEOUT           (USART_SR_RTOF)     /*!< Receive timeout flag */

#define USART_FLAG_ALL                  (USART_FLAG_RX_FULL | USART_FLAG_FRAME_ERR  | USART_FLAG_TX_EMPTY   | \
                                         USART_FLAG_OVERRUN | USART_FLAG_PARITY_ERR | USART_FLAG_RX_TIMEOUT | \
                                         USART_FLAG_TX_CPLT | USART_FLAG_MX_PROCESSOR )

/**
 * @}
 */

/**
 * @defgroup USART_Transmission_Type USART Transmission Type
 * @{
 */
#define USART_TRANS_DATA                (0UL)
#define USART_TRANS_ID                  (USART_TDR_MPID)
/**
 * @}
 */

/**
 * @defgroup USART_Function USART Function
 * @{
 */
#define USART_TX                        (USART_CR1_TE)      /*!< USART TX function */
#define USART_RX                        (USART_CR1_RE)      /*!< USART RX function */
#define USART_INT_RX                    (USART_CR1_RIE)     /*!< USART receive data register not empty && receive error interrupt */
#define USART_INT_TX_CPLT               (USART_CR1_TCIE)    /*!< USART transmission complete interrupt */
#define USART_INT_TX_EMPTY              (USART_CR1_TXEIE)   /*!< USART transmit data register empty interrupt */
#define USART_RX_TIMEOUT                (USART_CR1_RTOE)    /*!< USART RX timeout function */
#define USART_INT_RX_TIMEOUT            (USART_CR1_RTOIE)   /*!< USART RX timeout interrupt */

#define USART_FUNC_ALL                  (USART_TX | USART_RX  | USART_INT_RX | USART_INT_TX_CPLT | USART_RX_TIMEOUT | \
                                         USART_INT_RX_TIMEOUT | USART_INT_TX_EMPTY)

/**
 * @}
 */

/**
 * @defgroup USART_Parity_Control USART Parity Control
 * @{
 */
#define USART_PARITY_NONE               (0UL)               /*!< Parity control disabled */
#define USART_PARITY_EVEN               (USART_CR1_PCE)     /*!< Parity control enabled and Even Parity is selected */
#define USART_PARITY_ODD                (USART_CR1_PCE | \
                                         USART_CR1_PS)      /*!< Parity control enabled and Odd Parity is selected */
/**
 * @}
 */

/**
 * @defgroup USART_Data_Width_Bit USART Data Width Bit
 * @{
 */
#define USART_DATA_WIDTH_8BIT           (0UL)               /*!< 8 bits */
#define USART_DATA_WIDTH_9BIT           (USART_CR1_M)       /*!< 9 bits */
/**
 * @}
 */

/**
 * @defgroup USART_Over_Sample_Bit USART Over Sample Bit
 * @{
 */
#define USART_OVER_SAMPLE_16BIT         (0UL)               /*!< Oversampling by 16 bits */
#define USART_OVER_SAMPLE_8BIT          (USART_CR1_OVER8)   /*!< Oversampling by 8 bits */
/**
 * @}
 */

/**
 * @defgroup USART_First_Bit USART First Bit
 * @{
 */
#define USART_FIRST_BIT_LSB             (0UL)               /*!< LSB(Least Significant Bit) */
#define USART_FIRST_BIT_MSB             (USART_CR1_ML)      /*!< MSB(Most Significant Bit) */
/**
 * @}
 */

/**
 * @defgroup USART_Start_Bit_Polarity USART Start Bit Polarity
 * @{
 */
#define USART_START_BIT_LOW             (0UL)               /*!< Detect RX pin low level */
#define USART_START_BIT_FALLING         (USART_CR1_SBS)     /*!< Detect RX pin falling edge */
/**
 * @}
 */

/**
 * @defgroup USART_Clock_Source USART Clock Source
 * @{
 */
#define USART_CLK_SRC_INTERNCLK         (0UL)               /*!< Select internal clock source and don't output clock */
#define USART_CLK_SRC_EXTCLK            (USART_CR2_CLKC_1)  /*!< Select external clock source. */
/**
 * @}
 */

/**
 * @defgroup USART_CK_Output_Selection USART_CK Output Selection
 * @{
 */
#define USART_CK_OUTPUT_DISABLE         (0UL)               /*!< Disable USART_CK output */
#define USART_CK_OUTPUT_ENABLE          (USART_CR2_CLKC_0)  /*!< Enable USART_CK output. */
/**
 * @}
 */

/**
 * @defgroup USART_Stop_Bit USART Stop Bit
 * @{
 */
#define USART_STOPBIT_1BIT              (0UL)               /*!< 1 stop bit */
#define USART_STOPBIT_2BIT              (USART_CR2_STOP)    /*!< 2 stop bit */
/**
 * @}
 */

/**
 * @defgroup USART_Hardware_Flow_Control USART Hardware Flow Control
 * @{
 */
#define USART_HW_FLOWCTRL_CTS           (USART_CR3_CTSE)        /*!< USART hardware flow control CTS mode */
#define USART_HW_FLOWCTRL_RTS           (USART_CR3_CTSE >> 1U)  /*!< USART hardware flow control RTS mode */
/**
 * @}
 */

/**
 * @defgroup USART_Clock_Division USART Clock Division
 * @{
 */
#define USART_CLK_DIV1                  (0UL)   /*!< CLK      */
#define USART_CLK_DIV4                  (1UL)   /*!< CLK/4    */
#define USART_CLK_DIV16                 (2UL)   /*!< CLK/16   */
#define USART_CLK_DIV64                 (3UL)   /*!< CLK/64   */
/**
 * @}
 */

/**
 * @defgroup USART_Max_Timeout USART Max Timeout
 * @{
 */
#define USART_MAX_TIMEOUT               (0xFFFFFFFFUL)
/**
 * @}
 */

/**
 * @defgroup USART_Smartcard_ETU_Clock USART Smartcard ETU Clock
 * @{
 */
#define USART_SC_ETU_CLK32              (0UL << USART_CR3_BCN_POS)  /*!< 1 etu = 32/f */
#define USART_SC_ETU_CLK64              (1UL << USART_CR3_BCN_POS)  /*!< 1 etu = 64/f */
#define USART_SC_ETU_CLK128             (3UL << USART_CR3_BCN_POS)  /*!< 1 etu = 128/f */
#define USART_SC_ETU_CLK256             (5UL << USART_CR3_BCN_POS)  /*!< 1 etu = 256/f */
#define USART_SC_ETU_CLK372             (6UL << USART_CR3_BCN_POS)  /*!< 1 etu = 372/f */
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup USART_Global_Functions
 * @{
 */
int32_t USART_ClockSync_StructInit(stc_usart_clocksync_init_t *pstcClockSyncInit);
int32_t USART_ClockSync_Init(CM_USART_TypeDef *USARTx,
                             const stc_usart_clocksync_init_t *pstcClockSyncInit, float32_t *pf32Error);
int32_t USART_MultiProcessor_StructInit(stc_usart_multiprocessor_init_t *pstcMultiProcessorInit);
int32_t USART_MultiProcessor_Init(CM_USART_TypeDef *USARTx,
                                  const stc_usart_multiprocessor_init_t *pstcMultiProcessorInit, float32_t *pf32Error);
int32_t USART_UART_StructInit(stc_usart_uart_init_t *pstcUartInit);
int32_t USART_UART_Init(CM_USART_TypeDef *USARTx, const stc_usart_uart_init_t *pstcUartInit, float32_t *pf32Error);

int32_t USART_SmartCard_StructInit(stc_usart_smartcard_init_t *pstcSmartCardInit);
int32_t USART_SmartCard_Init(CM_USART_TypeDef *USARTx,
                             const stc_usart_smartcard_init_t *pstcSmartCardInit, float32_t *pf32Error);

int32_t USART_DeInit(CM_USART_TypeDef *USARTx);
void USART_FuncCmd(CM_USART_TypeDef *USARTx, uint32_t u32Func, en_functional_state_t enNewState);
en_flag_status_t USART_GetStatus(const CM_USART_TypeDef *USARTx, uint32_t u32Flag);
void USART_ClearStatus(CM_USART_TypeDef *USARTx, uint32_t u32Flag);
void USART_SetParity(CM_USART_TypeDef *USARTx, uint32_t u32Parity);
void USART_SetFirstBit(CM_USART_TypeDef *USARTx, uint32_t u32FirstBit);
void USART_SetStopBit(CM_USART_TypeDef *USARTx, uint32_t u32StopBit);
void USART_SetDataWidth(CM_USART_TypeDef *USARTx, uint32_t u32DataWidth);
void USART_SetOverSampleBit(CM_USART_TypeDef *USARTx, uint32_t u32OverSampleBit);
void USART_SetStartBitPolarity(CM_USART_TypeDef *USARTx, uint32_t u32Polarity);
void USART_SetTransType(CM_USART_TypeDef *USARTx, uint16_t u16Type);
void USART_SetClockDiv(CM_USART_TypeDef *USARTx, uint32_t u32ClockDiv);
uint32_t USART_GetClockDiv(const CM_USART_TypeDef *USARTx);
void USART_SetClockSrc(CM_USART_TypeDef *USARTx, uint32_t u32ClockSrc);
uint32_t USART_GetClockSrc(const CM_USART_TypeDef *USARTx);
void USART_FilterCmd(CM_USART_TypeDef *USARTx, en_functional_state_t enNewState);
void USART_SilenceCmd(CM_USART_TypeDef *USARTx, en_functional_state_t enNewState);
void USART_SetHWFlowControl(CM_USART_TypeDef *USARTx, uint32_t u32HWFlowControl);
uint16_t USART_ReadData(const CM_USART_TypeDef *USARTx);
void USART_WriteData(CM_USART_TypeDef *USARTx, uint16_t u16Data);
void USART_WriteID(CM_USART_TypeDef *USARTx, uint16_t u16ID);

int32_t USART_SetBaudrate(CM_USART_TypeDef *USARTx, uint32_t u32Baudrate, float32_t *pf32Error);

void USART_SmartCard_SetEtuClock(CM_USART_TypeDef *USARTx, uint32_t u32EtuClock);

int32_t USART_UART_Trans(CM_USART_TypeDef *USARTx, const void *pvBuf, uint32_t u32Len, uint32_t u32Timeout);
int32_t USART_UART_Receive(const CM_USART_TypeDef *USARTx, void *pvBuf, uint32_t u32Len, uint32_t u32Timeout);
int32_t USART_ClockSync_Trans(CM_USART_TypeDef *USARTx, const uint8_t au8Buf[], uint32_t u32Len, uint32_t u32Timeout);
int32_t USART_ClockSync_Receive(CM_USART_TypeDef *USARTx, uint8_t au8Buf[], uint32_t u32Len, uint32_t u32Timeout);
int32_t USART_ClockSync_TransReceive(CM_USART_TypeDef *USARTx, const uint8_t au8TxBuf[], uint8_t au8RxBuf[],
                                     uint32_t u32Len, uint32_t u32Timeout);

/**
 * @}
 */

#endif /* LL_USART_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_USART_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
