/**
 *******************************************************************************
 * @file  hc32f4a0_usart.h
 * @brief This file contains all the functions prototypes of the USART(Universal
 *        Synchronous/Asynchronous Receiver Transmitter) driver library.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hongjh          First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __HC32F4A0_USART_H__
#define __HC32F4A0_USART_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_common.h"
#include "ddl_config.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @addtogroup DDL_USART
 * @{
 */

#if (DDL_USART_ENABLE == DDL_ON)

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Types USART Global Types
 * @{
 */

/**
 * @brief UART mode initialization structure definition
 */
typedef struct
{
    uint32_t u32Baudrate;               /*!< UART baudrate. The baudrate is valid when clock source is PCLK. */

    uint32_t u32ClkMode;                /*!< Clock mode.
                                             This parameter can be a value of @ref USART_Clock_Mode */

    uint32_t u32PclkDiv;                /*!< PCLK division. The PCLK division function is valid when clock source is PCLK.
                                             This parameter can be a value of @ref USART_PCLK_Division */

    uint32_t u32Parity;                 /*!< Parity format.
                                             This parameter can be a value of @ref USART_Parity_Control */

    uint32_t u32DataWidth;              /*!< Data width.
                                             This parameter can be a value of @ref USART_Data_Length_Bits */

    uint32_t u32StopBit;                /*!< Stop Bits.
                                             This parameter can be a value of @ref USART_Stop_Bits */

    uint32_t u32OversamplingBits;       /*!< Oversampling Bits.
                                             This parameter can be a value of @ref USART_Oversampling_Bits */

    uint32_t u32BitDirection;           /*!< Significant bit.
                                             This parameter can be a value of @ref USART_Significant_Bit */

    uint32_t u32NoiseFilterState;       /*!< RX pin noise filter state.
                                             This parameter can be a value of @ref USART_Noise_Filter_State */

    uint32_t u32SbDetectPolarity;       /*!< Start Bit Detect Polarity.
                                             This parameter can be a value of @ref USART_Start_Bit_Detect_Polarity */

    uint32_t u32HwFlowCtrl;             /*!< Hardware flow control.
                                             This parameter can be a value of @ref USART_Hardware_Flow_Control */
} stc_usart_uart_init_t;

/**
 * @brief UART multiple-processor initialization structure definition
 */
typedef struct
{
    uint32_t u32Baudrate;               /*!< UART baudrate. The baudrate is valid when clock source is PCLK. */

    uint32_t u32ClkMode;                /*!< Clock mode.
                                             This parameter can be a value of @ref USART_Clock_Mode */

    uint32_t u32PclkDiv;                /*!< PCLK division. The PCLK division function is valid when clock source is PCLK.
                                             This parameter can be a value of @ref USART_PCLK_Division */

    uint32_t u32DataWidth;              /*!< Data width.
                                             This parameter can be a value of @ref USART_Data_Length_Bits */

    uint32_t u32StopBit;                /*!< Stop Bits.
                                             This parameter can be a value of @ref USART_Stop_Bits */

    uint32_t u32OversamplingBits;       /*!< Oversampling Bits.
                                             This parameter can be a value of @ref USART_Oversampling_Bits */

    uint32_t u32BitDirection;           /*!< Significant bit.
                                             This parameter can be a value of @ref USART_Significant_Bit */

    uint32_t u32NoiseFilterState;       /*!< RX pin noise filter state.
                                             This parameter can be a value of @ref USART_Noise_Filter_State */

    uint32_t u32SbDetectPolarity;       /*!< Start Bit Detect Polarity.
                                             This parameter can be a value of @ref USART_Start_Bit_Detect_Polarity */

    uint32_t u32HwFlowCtrl;             /*!< Hardware flow control.
                                             This parameter can be a value of @ref USART_Hardware_Flow_Control */
} stc_usart_multiprocessor_init_t;

/**
 * @brief LIN mode initialization structure definition
 */
typedef struct
{
    uint32_t u32Baudrate;               /*!< UART baudrate. The baudrate is valid when clock source is PCLK. */

    uint32_t u32ClkMode;                /*!< Clock mode.
                                             This parameter can be a value of @ref USART_Clock_Mode */

    uint32_t u32PclkDiv;                /*!< PCLK division. The PCLK division function is valid when clock source is PCLK.
                                             This parameter can be a value of @ref USART_PCLK_Division */

    uint32_t u32BmcPclkDiv;             /*!< BMC PCLK division. The PCLK division function is valid when clock source is PCLK.
                                             This parameter can be a value of @ref USART_LIN_BMC_PCLK_Division */

    uint32_t u32OversamplingBits;       /*!< Oversampling Bits.
                                             This parameter can be a value of @ref USART_Oversampling_Bits */

    uint32_t u32DetectBreakLen;         /*!< Detect break length.
                                             This parameter can be a value of @ref USART_LIN_Detect_Break_Length */

    uint32_t u32SendBreakLen;           /*!< Send break length.
                                             This parameter can be a value of @ref USART_LIN_Send_Break_Length */

    uint32_t u32SendBreakMode;          /*!< Send break mode.
                                             This parameter can be a value of @ref USART_LIN_Send_Break_Mode */
} stc_usart_lin_init_t;

/**
 * @brief Smart card mode initialization structure definition
 */
typedef struct
{
    uint32_t u32Baudrate;               /*!< UART baudrate */

    uint32_t u32ClkMode;                /*!< Clock mode.
                                             This parameter can be a value of @ref USART_Clock_Mode */

    uint32_t u32PclkDiv;                /*!< PCLK division. The PCLK division function is valid when clock source is PCLK.
                                             This parameter can be a value of @ref USART_PCLK_Division */

    uint32_t u32StopBit;                /*!< Stop Bits.
                                             This parameter can be a value of @ref USART_Stop_Bits */

    uint32_t u32BitDirection;           /*!< Significant bit.
                                             This parameter can be a value of @ref USART_Significant_Bit */
} stc_usart_smartcard_init_t;

/**
 * @brief clock synchronization mode initialization structure definition
 */
typedef struct
{
    uint32_t u32Baudrate;               /*!< UART baudrate. The baudrate is valid when clock source is PCLK. */

    uint32_t u32ClkMode;                /*!< Clock mode.
                                             This parameter can be a value of @ref USART_Clock_Mode */

    uint32_t u32PclkDiv;                /*!< PCLK division. The PCLK division function is valid when clock source is PCLK.
                                             This parameter can be a value of @ref USART_PCLK_Division */

    uint32_t u32BitDirection;           /*!< Significant bit.
                                             This parameter can be a value of @ref USART_Significant_Bit */

    uint32_t u32HwFlowCtrl;             /*!< Hardware flow control.
                                             This parameter can be a value of @ref USART_Hardware_Flow_Control */
} stc_usart_clksync_init_t;

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
#define USART_FLAG_PE                       (USART_SR_PE)       /*!< Parity error flag */
#define USART_FLAG_FE                       (USART_SR_FE)       /*!< Framing error flag */
#define USART_FLAG_ORE                      (USART_SR_ORE)      /*!< Overrun error flag */
#define USART_FLAG_BE                       (USART_SR_BE)       /*!< LIN bus error flag */
#define USART_FLAG_RXNE                     (USART_SR_RXNE)     /*!< Receive data register not empty flag */
#define USART_FLAG_TC                       (USART_SR_TC)       /*!< Transmission complete flag */
#define USART_FLAG_TXE                      (USART_SR_TXE)      /*!< Transmit data register empty flag */
#define USART_FLAG_RTOF                     (USART_SR_RTOF)     /*!< Receive timeout flag */
#define USART_FLAG_LBD                      (USART_SR_LBD)      /*!< LIN break signal detection flag */
#define USART_FLAG_WKUP                     (USART_SR_WKUP)     /*!< LIN wakeup signal detection flag */
#define USART_FLAG_MPB                      (USART_SR_MPB)      /*!< Receive processor ID flag */
/**
 * @}
 */

/**
 * @defgroup USART_Transmission_Type USART Transmission Type
 * @{
 */
#define USART_TRANSMISSION_ID               (USART_DR_MPID)
#define USART_TRANSMISSION_DATA             (0UL)
/**
 * @}
 */

/**
 * @defgroup USART_Clear_Flag USART Clear Flag
 * @{
 */
#define USART_CLEAR_FLAG_PE                 (USART_CR1_CPE)     /*!< Clear Parity error flag */
#define USART_CLEAR_FLAG_FE                 (USART_CR1_CFE)     /*!< Clear Framing error flag */
#define USART_CLEAR_FLAG_ORE                (USART_CR1_CORE)    /*!< Clear Overrun error flag */
#define USART_CLEAR_FLAG_RTOF               (USART_CR1_CRTOF)   /*!< Clear RX timeout flag */
#define USART_CLEAR_FLAG_BE                 (USART_CR1_CBE)     /*!< Clear LIN bus error flag */
#define USART_CLEAR_FLAG_WKUP               (USART_CR1_CWKUP)   /*!< Clear LIN wakeup signal flag */
#define USART_CLEAR_FLAG_LBD                (USART_CR1_CLBD)    /*!< Clear LIN break detection flag */
/**
 * @}
 */

/**
 * @defgroup USART_Transmit_Receive_Function USART Transmit/Receive Function
 * @{
 */
#define USART_RX                            (USART_CR1_RE)      /*!< USART RX function */
#define USART_TX                            (USART_CR1_TE)      /*!< USART TX function */
#define USART_RTO                           (USART_CR1_RTOE)    /*!< USART RX timerout function */
#define USART_INT_RX                        (USART_CR1_RIE)     /*!< USART receive data register not empty && receive error interrupt */
#define USART_INT_TXE                       (USART_CR1_TXEIE)   /*!< USART transmit data register empty interrupt */
#define USART_INT_TC                        (USART_CR1_TCIE)    /*!< USART transmission complete interrupt */
#define USART_INT_RTO                       (USART_CR1_RTOIE)   /*!< USART RX timerout interrupt */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Function USART LIN Function
 * @{
 */
#define USART_LIN                           (USART_CR2_LINEN)   /*!< USART LIN function */
#define USART_LIN_WKUP                      (USART_CR2_WKUPE)   /*!< USART LIN wakeup signal detect function */
#define USART_LIN_INT_WKUP                  (USART_CR2_WKUPIE)  /*!< USART LIN wakeup signal detect interrupt function */
#define USART_LIN_BUSERR                    (USART_CR2_BEE)     /*!< USART LIN bus error detect function */
#define USART_LIN_INT_BUSERR                (USART_CR2_BEIE)    /*!< USART LIN bus error detect interrupt function */
#define USART_LIN_INT_BREAK                 (USART_CR2_LBDIE)   /*!< USART LIN break field detect interrupt function */
/**
 * @}
 */

/**
 * @defgroup USART_Parity_Control USART Parity Control
 * @{
 */
#define USART_PARITY_NONE                   (0UL)               /*!< Parity control disabled */
#define USART_PARITY_EVEN                   (USART_CR1_PCE)     /*!< Parity control enabled and Even Parity is selected */
#define USART_PARITY_ODD                    (USART_CR1_PCE | \
                                             USART_CR1_PS)      /*!< Parity control enabled and Odd Parity is selected */
/**
 * @}
 */

/**
 * @defgroup USART_Data_Length_Bits Data Length Bits
 * @{
 */
#define USART_DATA_LENGTH_8BIT              (0UL)               /*!< 8 bits */
#define USART_DATA_LENGTH_9BIT              (USART_CR1_M)       /*!< 9 bits */
/**
 * @}
 */

/**
 * @defgroup USART_Oversampling_Bits USART Oversampling Bits
 * @{
 */
#define USART_OVERSAMPLING_16BIT            (0UL)               /*!< Oversampling by 16 bits */
#define USART_OVERSAMPLING_8BIT             (USART_CR1_OVER8)   /*!< Oversampling by 8 bits */
/**
 * @}
 */

/**
 * @defgroup USART_Significant_Bit USART Significant Bit
 * @{
 */
#define USART_LSB                           (0UL)               /*!< LSB(Least Significant Bit) */
#define USART_MSB                           (USART_CR1_ML)      /*!< MSB(Most Significant Bit) */
/**
 * @}
 */

/**
 * @defgroup USART_Noise_Filter_State USART Noise Filter State
 * @{
 */
#define USART_NOISE_FILTER_DISABLE          (0UL)               /*!< Disable noise filter */
#define USART_NOISE_FILTER_ENABLE           (USART_CR1_NFE)     /*!< Enable noise filter */
/**
 * @}
 */

/**
 * @defgroup USART_Start_Bit_Detect_Polarity USART Start Bit Detect Polarity
 * @{
 */
#define USART_SB_DETECT_LOW                 (0UL)               /*!< Detect RX pin low level */
#define USART_SB_DETECT_FALLING             (USART_CR1_SBS)     /*!< Detect RX pin falling edge */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Send_Break_Mode USART LIN Send Break Mode
 * @{
 */
#define USART_LIN_SEND_BREAK_MODE_SBK       (0UL)               /*!< Start send break after USART_CR2 SBK bit set 1 value */
#define USART_LIN_SEND_BREAK_MODE_TDR       (USART_CR2_SBKM)    /*!< Start send break after USART_DR TDR write 0x00 value */
/**
 * @}
 */

/**
 * @defgroup USART_Multiple_Processor_State USART Multiple Processor State
 * @{
 */
#define USART_MULTIPLE_PROCESSOR_DISABLE    (0UL)               /*!< Disable multiple processor function */
#define USART_MULTIPLE_PROCESSOR_ENABLE     (USART_CR2_MPE)     /*!< Enable multiple processor function */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Detect_Break_Length USART LIN Detect Break Length
 * @{
 */
#define USART_LIN_DETECT_BREAK_10BIT        (0UL)               /*!< Detect break 10-bit */
#define USART_LIN_DETECT_BREAK_11BIT        (USART_CR2_LBDL)    /*!< Detect break 11-bit */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Send_Break_Length USART LIN Send Break Length
 * @{
 */
#define USART_LIN_SEND_BREAK_10BIT          (0UL)               /*!< Send break 10-bit */
#define USART_LIN_SEND_BREAK_11BIT          (USART_CR2_SBKL_0)  /*!< Send break 11-bit */
#define USART_LIN_SEND_BREAK_13BIT          (USART_CR2_SBKL_1)  /*!< Send break 13-bit */
#define USART_LIN_SEND_BREAK_14BIT          (USART_CR2_SBKL)    /*!< Send break 14-bit */
/**
 * @}
 */

/**
 * @defgroup USART_Clock_Mode USART Clock Mode Selection
 * @{
 */
#define USART_EXTCLK                        (USART_CR2_CLKC_1)  /*!< Select external clock source. */
#define USART_INTERNCLK_OUTPUT              (USART_CR2_CLKC_0)  /*!< Select internal clock source and output clock. */
#define USART_INTERNCLK_NONE_OUTPUT         (0UL)               /*!< Select internal clock source and don't output clock */
/**
 * @}
 */

/**
 * @defgroup USART_Stop_Bits USART Stop Bits
 * @{
 */
#define USART_STOPBIT_1BIT                  (0UL)               /*!< 1 stop bit */
#define USART_STOPBIT_2BIT                  (USART_CR2_STOP)    /*!< 2 stop bit */
/**
 * @}
 */

/**
 * @defgroup USART_DUPLEX_SEL USART Half-duplex/Full-duplex Selection
 * @{
 */
#define USART_FULLDUPLEX_MODE               (0UL)               /*!< USART full-duplex mode */
#define USART_HALFDUPLEX_MODE               (USART_CR3_HDSEL)   /*!< USART half-duplex mode */
/**
 * @}
 */

/**
 * @defgroup USART_Hardware_Flow_Control USART Hardware Flow Control RTS/CTS
 * @{
 */
#define USART_HWFLOWCTRL_NONE               (0UL)               /*!< Disable USART hardware flow controle */
#define USART_HWFLOWCTRL_RTS                (USART_CR3_RTSE)    /*!< USART hardware flow control RTS mode */
#define USART_HWFLOWCTRL_CTS                (USART_CR3_CTSE)    /*!< USART hardware flow control CTS mode */
#define USART_HWFLOWCTRL_RTS_CTS            (USART_CR3_RTSE | \
                                             USART_CR3_CTSE)    /*!< USART hardware flow control RTS and CTS mode */
/**
 * @}
 */

/**
 * @defgroup USART_Smartcard_ETU_Clock USART Smartcard ETU Clock
 * @{
 */
#define USART_SC_ETU_CLK_32                 (0UL)               /*!< 1 etu = 32/f */
#define USART_SC_ETU_CLK_64                 (USART_CR3_BCN_0)   /*!< 1 etu = 64/f */
#define USART_SC_ETU_CLK_128                (USART_CR3_BCN_1 | \
                                             USART_CR3_BCN_0)   /*!< 1 etu = 128/f */
#define USART_SC_ETU_CLK_256                (USART_CR3_BCN_2 | \
                                             USART_CR3_BCN_0)   /*!< 1 etu = 256/f */
#define USART_SC_ETU_CLK_372                (USART_CR3_BCN_2 | \
                                             USART_CR3_BCN_1)   /*!< 1 etu = 372/f */
/**
 * @}
 */

/**
 * @defgroup USART_PCLK_Division USART PCLK Clock Prescaler Division
 * @{
 */
#define USART_PCLK_DIV1                     (0UL)               /*!< PCLK */
#define USART_PCLK_DIV4                     (USART_PR_PSC_0)    /*!< PCLK/4 */
#define USART_PCLK_DIV16                    (USART_PR_PSC_1)    /*!< PCLK/16 */
#define USART_PCLK_DIV64                    (USART_PR_PSC)      /*!< PCLK/64 */
/**
 * @}
 */

/**
 * @defgroup USART_LIN_BMC_PCLK_Division USART LIN Baudrate Measure Counter PCLK Division
 * @{
 */
#define USART_LIN_BMC_PCLK_DIV1             (0UL)               /*!< PCLK */
#define USART_LIN_BMC_PCLK_DIV2             (USART_PR_LBMPSC_0) /*!< PCLK/2 */
#define USART_LIN_BMC_PCLK_DIV4             (USART_PR_LBMPSC_1) /*!< PCLK/4 */
#define USART_LIN_BMC_PCLK_DIV8             (USART_PR_LBMPSC)   /*!< PCLK/8 */
/**
 * @}
 */

/**
 * @defgroup USART_Stop_Mode_Noise_Filter USART Stop Mode Noise_Filter
 * @{
 */
#define USART_STOP_MODE_FILTER_NONE             (0UL)                       /*!< Disable noise filter */
#define USART_STOP_MODE_FILTER_WIDTH_LEVEL_1    (PERIC_USART1_NFC_NFE)      /*!< Filter width level 1 */
#define USART_STOP_MODE_FILTER_WIDTH_LEVEL_2    (PERIC_USART1_NFC_NFE | \
                                                 PERIC_USART1_NFC_NFS_0)    /*!< Filter width level 2 */
#define USART_STOP_MODE_FILTER_WIDTH_LEVEL_3    (PERIC_USART1_NFC_NFE | \
                                                 PERIC_USART1_NFC_NFS_1)    /*!< Filter width level 3 */
#define USART_STOP_MODE_FILTER_WIDTH_LEVEL_4    (PERIC_USART1_NFC_NFE | \
                                                 PERIC_USART1_NFC_NFS)      /*!< Filter width level 4 */
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
en_result_t USART_UartInit(M4_USART_TypeDef *USARTx,
                            const stc_usart_uart_init_t *pstcInit);
en_result_t USART_HalfduplexInit(M4_USART_TypeDef *USARTx,
                                    const stc_usart_uart_init_t *pstcInit);
en_result_t USART_UartStructInit(stc_usart_uart_init_t *pstcInit);
en_result_t USART_MultiProcessorInit(M4_USART_TypeDef *USARTx,
                                const stc_usart_multiprocessor_init_t *pstcInit);
en_result_t USART_MultiProcessorStructInit(stc_usart_multiprocessor_init_t *pstcInit);
en_result_t USART_LinInit(M4_USART_TypeDef *USARTx,
                            const stc_usart_lin_init_t *pstcInit);
en_result_t USART_LinStructInit(stc_usart_lin_init_t *pstcInit);
en_result_t USART_SmartcardInit(M4_USART_TypeDef *USARTx,
                                    const stc_usart_smartcard_init_t *pstcInit);
en_result_t USART_SmartcardStructInit(stc_usart_smartcard_init_t *pstcInit);
en_result_t USART_ClkSyncInit(M4_USART_TypeDef *USARTx,
                                const stc_usart_clksync_init_t *pstcInit);
en_result_t USART_ClkSyncStructInit(stc_usart_clksync_init_t *pstcInit);
void USART_DeInit(M4_USART_TypeDef *USARTx);
void USART_FuncCmd(M4_USART_TypeDef *USARTx,
                        uint32_t u32Func,
                        en_functional_state_t enNewState);
en_functional_state_t USART_GetFuncState(const M4_USART_TypeDef *USARTx,
                                            uint32_t u32Func);
en_flag_status_t USART_GetStatus(const M4_USART_TypeDef *USARTx,
                                    uint32_t u32Flag);
void USART_ClearStatus(M4_USART_TypeDef *USARTx, uint32_t u32Flag);
void USART_SetTransmissionType(M4_USART_TypeDef *USARTx, uint32_t u32Type);
uint32_t USART_GetTransmissionType(const M4_USART_TypeDef *USARTx);
void USART_SetParity(M4_USART_TypeDef *USARTx, uint32_t u32Parity);
uint32_t USART_GetParity(const M4_USART_TypeDef *USARTx);
void USART_SetDataWidth(M4_USART_TypeDef *USARTx, uint32_t u32DataWidth);
uint32_t USART_GetDataWidth(const M4_USART_TypeDef *USARTx);
void USART_SetOversmaplingBits(M4_USART_TypeDef *USARTx,
                                        uint32_t u32OversamplingBits);
uint32_t USART_GetOversmaplingBits(const M4_USART_TypeDef *USARTx);
void USART_SetBitDirection(M4_USART_TypeDef *USARTx, uint32_t u32BitDir);
uint32_t USART_GetBitDirection(const M4_USART_TypeDef *USARTx);
void USART_SetSbDetectPolarity(M4_USART_TypeDef *USARTx,
                                        uint32_t u32Polarity);
uint32_t USART_GetSbDetectPolarity(const M4_USART_TypeDef *USARTx);
void USART_SetClockMode(M4_USART_TypeDef *USARTx, uint32_t u32ClkMode);
uint32_t USART_GetClockMode(const M4_USART_TypeDef *USARTx);
void USART_SetStopBits(M4_USART_TypeDef *USARTx, uint32_t u32StopBits);
uint32_t USART_GetStopBits(const M4_USART_TypeDef *USARTx);
uint16_t USART_RecData(const M4_USART_TypeDef *USARTx);
void USART_SendData(M4_USART_TypeDef *USARTx, uint16_t u16Data);
void USART_SendId(M4_USART_TypeDef *USARTx, uint16_t u16ID);
void USART_SilenceCmd(M4_USART_TypeDef *USARTx,
                            en_functional_state_t enNewState);
void USART_LinLoopCmd(M4_USART_TypeDef *USARTx,
                        en_functional_state_t enNewState);
void USART_LinRequestBreakSending(M4_USART_TypeDef *USARTx);
en_flag_status_t USART_GetLinRequestBreakStatus(const M4_USART_TypeDef *USARTx);
void USART_SetLinBreakMode(M4_USART_TypeDef *USARTx, uint32_t u32Mode);
uint32_t USART_GetLinBreakMode(const M4_USART_TypeDef *USARTx);
void USART_SetDuplexMode(M4_USART_TypeDef *USARTx, uint32_t u32Mode);
uint32_t USART_GetDuplexMode(const M4_USART_TypeDef *USARTx);
void USART_SetHwFlowCtrl(M4_USART_TypeDef *USARTx, uint32_t u32HwFlowCtrl);
uint32_t USART_GetHwFlowCtrl(const M4_USART_TypeDef *USARTx);
void USART_SetSmartcardEtuClk(M4_USART_TypeDef *USARTx,
                                    uint32_t u32EtuClk);
uint32_t USART_GetSmartcardEtuClk(const M4_USART_TypeDef *USARTx);
void USART_SetPclkDiv(M4_USART_TypeDef *USARTx,
                                uint32_t u32PclkDiv);
uint32_t USART_GetPclkDiv(const M4_USART_TypeDef *USARTx);
void USART_SetLinBmcPclkDiv(M4_USART_TypeDef *USARTx,
                                        uint32_t u32PclkDiv);
uint32_t USART_GetLinBmcPclkDiv(const M4_USART_TypeDef *USARTx);
void USART_SetStopModeNoiseFilter(const M4_USART_TypeDef *USARTx,
                                            uint32_t u32Filter);
uint32_t USART_GetStopModeNoiseFilter(const M4_USART_TypeDef *USARTx);
void USART_LinFuncCmd(M4_USART_TypeDef *USARTx,
                            uint32_t u32Func,
                            en_functional_state_t enNewState);
en_functional_state_t USART_GetLinFuncState(const M4_USART_TypeDef *USARTx,
                                                    uint32_t u32Func);
uint32_t USART_GetLinMeasureCnt(const M4_USART_TypeDef *USARTx);
uint32_t USART_GetLinMeasureBaudrate(const M4_USART_TypeDef *USARTx);
void USART_SetLinDetectBreakLen(M4_USART_TypeDef *USARTx,
                                        uint32_t u32Len);
uint32_t USART_GetLinDetectBreakLen(const M4_USART_TypeDef *USARTx);
void USART_SetLinSendBreakLen(M4_USART_TypeDef *USARTx, uint32_t u32Len);
uint32_t USART_GetLinSendBreakLen(const M4_USART_TypeDef *USARTx);
en_result_t USART_SetBaudrate(M4_USART_TypeDef *USARTx,
                                    uint32_t u32Baudrate,
                                    float32_t *pf32Err);

/**
 * @}
 */

#endif /* DDL_USART_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32F4A0_USART_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
