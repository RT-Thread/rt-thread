/**
 *******************************************************************************
 * @file  hc32_ll_usart.h
 * @brief This file contains all the functions prototypes of the USART(Universal
 *        Synchronous/Asynchronous Receiver Transmitter) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
   2023-09-30       CDT             Remove u32StopBit param from stc_usart_smartcard_init_t structure
   2023-12-15       CDT             Add the declaration of API USART_GetFuncState()
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
 * @brief LIN mode initialization structure definition
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
    uint32_t u32OverSampleBit;          /*!< Oversampling Bits.
                                             This parameter can be a value of @ref USART_Over_Sample_Bit */
    uint32_t u32BmcClockDiv;            /*!< BMC clock division.
                                             This parameter can be a value of @ref USART_LIN_BMC_Clock_Division.
                                             @note The clock division is valid when clock source is the internal clock. */
    uint32_t u32DetectBreakLen;         /*!< Detect break length.
                                             This parameter can be a value of @ref USART_LIN_Detect_Break_Length */
    uint32_t u32SendBreakLen;           /*!< Send break length.
                                             This parameter can be a value of @ref USART_LIN_Send_Break_Length */
    uint32_t u32SendBreakMode;          /*!< Send break mode.
                                             This parameter can be a value of @ref USART_LIN_Send_Break_Mode */
} stc_usart_lin_init_t;

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
#define USART_FLAG_LIN_ERR              (USART_SR_BE)       /*!< LIN bus error flag */
#define USART_FLAG_LIN_WKUP             (USART_SR_WKUP)     /*!< LIN wakeup signal detection flag */
#define USART_FLAG_LIN_BREAK            (USART_SR_LBD)      /*!< LIN break signal detection flag */
#define USART_FLAG_TX_END               (USART_SR_TEND)     /*!< Transmission complete flag (can be cleared) */

#define USART_FLAG_ALL                  (USART_FLAG_RX_FULL | USART_FLAG_FRAME_ERR  | USART_FLAG_TX_EMPTY   | \
                                         USART_FLAG_OVERRUN | USART_FLAG_PARITY_ERR | USART_FLAG_RX_TIMEOUT | \
                                         USART_FLAG_TX_CPLT | USART_FLAG_LIN_BREAK  | USART_FLAG_LIN_WKUP   | \
                                         USART_FLAG_LIN_ERR | USART_FLAG_MX_PROCESSOR | USART_FLAG_TX_END)

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
#define USART_INT_TX_END                (USART_CR1_TENDIE)   /*!< USART transmission complete interrupt */
#define USART_LIN                       (USART_CR2_LINEN  << 16UL)  /*!< USART LIN function */
#define USART_LIN_WKUP                  (USART_CR2_WKUPE  << 16UL)  /*!< USART LIN wakeup signal detect function */
#define USART_LIN_ERR                   (USART_CR2_BEE    << 16UL)  /*!< USART LIN bus error detect function */
#define USART_LIN_BREAK                 (USART_CR2_LBDL   << 16UL)  /*!< USART LIN bus break field detect function */
#define USART_LIN_INT_ERR               (USART_CR2_BEIE   << 16UL)  /*!< USART LIN bus error detect interrupt function */
#define USART_LIN_INT_BREAK             (USART_CR2_LBDIE  << 16UL)  /*!< USART LIN bus break field detect interrupt function */
#define USART_LIN_INT_WKUP              (USART_CR2_WKUPIE << 16UL)  /*!< USART LIN bus wakeup signal detect interrupt function */

#define USART_FUNC_ALL                  (USART_TX | USART_RX  | USART_INT_RX | USART_INT_TX_CPLT | USART_RX_TIMEOUT | \
                                         USART_INT_RX_TIMEOUT | USART_INT_TX_EMPTY | USART_LIN | USART_LIN_WKUP | \
                                         USART_LIN_ERR | USART_LIN_BREAK | USART_LIN_INT_ERR | USART_LIN_INT_BREAK | \
                                         USART_LIN_INT_WKUP | USART_INT_TX_END)

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
#define USART_HW_FLOWCTRL_NONE          (0UL)                   /*!< Disable USART hardware flow control */
#define USART_HW_FLOWCTRL_RTS_CTS       (USART_HW_FLOWCTRL_CTS | \
                                         USART_HW_FLOWCTRL_RTS) /*!< USART hardware flow control RTS and CTS mode */
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
#define USART_CLK_DIV128                (0UL | USART_PR_ULBREN)   /*!< CLK/128  */
#define USART_CLK_DIV256                (1UL | USART_PR_ULBREN)   /*!< CLK/256  */
#define USART_CLK_DIV512                (2UL | USART_PR_ULBREN)   /*!< CLK/512  */
#define USART_CLK_DIV1024               (3UL | USART_PR_ULBREN)   /*!< CLK/1024 */
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
 * @defgroup USART_Stop_Mode_Noise_Filter_Width_Level USART Stop Mode Noise Filter Width Level
 * @{
 */
#define USART_STOP_MD_FILTER_LVL1       (0UL)                               /*!< Filter width level 1 */
#define USART_STOP_MD_FILTER_LVL2       (PERIC_USART1_NFC_USASRT1_NFS_0)    /*!< Filter width level 2 */
#define USART_STOP_MD_FILTER_LVL3       (PERIC_USART1_NFC_USASRT1_NFS_1)    /*!< Filter width level 3 */
#define USART_STOP_MD_FILTER_LVL4       (PERIC_USART1_NFC_USASRT1_NFS)      /*!< Filter width level 4 */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_BMC_Clock_Division USART LIN Baudrate Measure Counter Clock Division
 * @{
 */
#define USART_LIN_BMC_CLK_DIV1          (0UL)               /*!< CLK */
#define USART_LIN_BMC_CLK_DIV2          (USART_PR_LBMPSC_0) /*!< CLK/2 */
#define USART_LIN_BMC_CLK_DIV4          (USART_PR_LBMPSC_1) /*!< CLK/4 */
#define USART_LIN_BMC_CLK_DIV8          (USART_PR_LBMPSC)   /*!< CLK/8 */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Send_Break_Mode USART LIN Send Break Mode
 * @{
 */
#define USART_LIN_SEND_BREAK_MD_SBK     (0UL)               /*!< Start send break after USART_CR2 SBK bit set 1 value */
#define USART_LIN_SEND_BREAK_MD_TDR     (USART_CR2_SBKM)    /*!< Start send break after USART_DR TDR write 0x00 value */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Detect_Break_Length USART LIN Detect Break Length
 * @{
 */
#define USART_LIN_DETECT_BREAK_10BIT    (0UL)               /*!< Detect break 10-bit */
#define USART_LIN_DETECT_BREAK_11BIT    (USART_CR2_LBDL)    /*!< Detect break 11-bit */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Send_Break_Length USART LIN Send Break Length
 * @{
 */
#define USART_LIN_SEND_BREAK_10BIT      (0UL)               /*!< Send break 10-bit */
#define USART_LIN_SEND_BREAK_11BIT      (USART_CR2_SBKL_0)  /*!< Send break 11-bit */
#define USART_LIN_SEND_BREAK_13BIT      (USART_CR2_SBKL_1)  /*!< Send break 13-bit */
#define USART_LIN_SEND_BREAK_14BIT      (USART_CR2_SBKL)    /*!< Send break 14-bit */
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

int32_t USART_HalfDuplex_Init(CM_USART_TypeDef *USARTx,
                              const stc_usart_uart_init_t *pstcUartInit, float32_t *pf32Error);

int32_t USART_LIN_StructInit(stc_usart_lin_init_t *pstcLinInit);
int32_t USART_LIN_Init(CM_USART_TypeDef *USARTx, const stc_usart_lin_init_t *pstcLinInit, float32_t *pf32Error);

int32_t USART_SmartCard_StructInit(stc_usart_smartcard_init_t *pstcSmartCardInit);
int32_t USART_SmartCard_Init(CM_USART_TypeDef *USARTx,
                             const stc_usart_smartcard_init_t *pstcSmartCardInit, float32_t *pf32Error);

int32_t USART_DeInit(CM_USART_TypeDef *USARTx);
void USART_FuncCmd(CM_USART_TypeDef *USARTx, uint32_t u32Func, en_functional_state_t enNewState);
en_functional_state_t USART_GetFuncState(CM_USART_TypeDef *USARTx, uint32_t u32Func);
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

void USART_StopModeNoiseFilterCmd(const CM_USART_TypeDef *USARTx, en_functional_state_t enNewState);
void USART_SetStopModeNoiseFilter(const CM_USART_TypeDef *USARTx, uint32_t u32Level);

void USART_LIN_LoopbackCmd(CM_USART_TypeDef *USARTx, en_functional_state_t enNewState);
void USART_LIN_SetBmcClockDiv(CM_USART_TypeDef *USARTx, uint32_t u32ClockDiv);
void USART_LIN_RequestBreakSending(CM_USART_TypeDef *USARTx);
en_flag_status_t USART_LIN_GetRequestBreakStatus(const CM_USART_TypeDef *USARTx);
void USART_LIN_SetBreakMode(CM_USART_TypeDef *USARTx, uint32_t u32Mode);
uint32_t USART_LIN_GetBreakMode(const CM_USART_TypeDef *USARTx);
uint32_t USART_LIN_GetMeasureCount(const CM_USART_TypeDef *USARTx);
uint32_t USART_LIN_GetMeasureBaudrate(const CM_USART_TypeDef *USARTx);
void USART_LIN_SetDetectBreakLen(CM_USART_TypeDef *USARTx, uint32_t u32Len);
void USART_LIN_SetSendBreakLen(CM_USART_TypeDef *USARTx, uint32_t u32Len);

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
