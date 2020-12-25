/**
 *******************************************************************************
 * @file  hc32f4a0_usart.c
 * @brief This file provides firmware functions to manage the USART(Universal
 *        Synchronous/Asynchronous Receiver Transmitter).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hongjh          First version
   2020-07-03       Hongjh          Add doxygen group:USART_Local_Functions.
   2020-08-25       Hongjh          The variable f32Err un-initializes an 
                                    unnecessary assignment.
   2020-10-19       Hongjh          Modify USART initialization function.
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_usart.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_USART USART
 * @brief USART Driver Library
 * @{
 */

#if (DDL_USART_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup USART_Local_Macros USART Local Macros
 * @{
 */

/**
 * @defgroup USART_Check_Parameters_Validity USART Check Parameters Validity
 * @{
 */

#define IS_USART_INSTANCE(x)                                                   \
(   (M4_USART1 == (x))                          ||                             \
    (M4_USART2 == (x))                          ||                             \
    (M4_USART3 == (x))                          ||                             \
    (M4_USART4 == (x))                          ||                             \
    (M4_USART5 == (x))                          ||                             \
    (M4_USART6 == (x))                          ||                             \
    (M4_USART7 == (x))                          ||                             \
    (M4_USART8 == (x))                          ||                             \
    (M4_USART9 == (x))                          ||                             \
    (M4_USART10 == (x)))

#define IS_USART_SMARTCARD_INSTANCE(x)                                         \
(   (M4_USART1 == (x))                          ||                             \
    (M4_USART2 == (x))                          ||                             \
    (M4_USART3 == (x))                          ||                             \
    (M4_USART4 == (x))                          ||                             \
    (M4_USART6 == (x))                          ||                             \
    (M4_USART7 == (x))                          ||                             \
    (M4_USART8 == (x))                          ||                             \
    (M4_USART9 == (x)))

#define IS_USART_LIN_INSTANCE(x)                                               \
(   (M4_USART5 == (x))                          ||                             \
    (M4_USART10 == (x)))

#define IS_USART_STOPMODE_INSTANCE(x)           (M4_USART1 == (x))

#define IS_USART_TIMEOUT_INSTANCE(x)                                           \
(   (M4_USART1 == (x))                          ||                             \
    (M4_USART2 == (x))                          ||                             \
    (M4_USART5 == (x))                          ||                             \
    (M4_USART6 == (x)))

#define IS_USART_FRACTION_INSTANCE(x)                                          \
(   (M4_USART1 == (x))                          ||                             \
    (M4_USART2 == (x))                          ||                             \
    (M4_USART3 == (x))                          ||                             \
    (M4_USART4 == (x))                          ||                             \
    (M4_USART6 == (x))                          ||                             \
    (M4_USART7 == (x))                          ||                             \
    (M4_USART8 == (x))                          ||                             \
    (M4_USART9 == (x)))

#define IS_USART_FUNCTION(x)                                                   \
(   (0UL != (x))                                &&                             \
    (0UL == ((x) & (~USART_FUNCTION_MASK))))

#define IS_USART_LIN_FUNCTION(x)                                               \
(   (0UL != (x))                                &&                             \
    (0UL == ((x) & (~USART_LIN_FUNCTION_MASK))))

#define IS_USART_FLAG(x)                                                       \
(   (0UL != (x))                                &&                             \
    (0UL == ((x) & (~USART_FLAG_MASK))))

#define IS_USART_CLEAR_FLAG(x)                                                 \
(   (0UL != (x))                                &&                             \
    (0UL == ((x) & (~USART_CLEAR_FLAG_MASK))))

#define IS_USART_TRANSMISSION_TYPE(x)                                          \
(   (USART_TRANSMISSION_ID == (x))              ||                             \
    (USART_TRANSMISSION_DATA == (x)))

#define IS_USART_PARITY_CONTROL(x)                                             \
(   (USART_PARITY_ODD == (x))                   ||                             \
    (USART_PARITY_EVEN == (x))                  ||                             \
    (USART_PARITY_NONE == (x)))

#define IS_USART_DATA_WIDTH(x)                                                 \
(   (USART_DATA_LENGTH_8BIT == (x))             ||                             \
    (USART_DATA_LENGTH_9BIT == (x)))

#define IS_USART_NOISE_FILTER(x)                                               \
(   (USART_NOISE_FILTER_ENABLE == (x))          ||                             \
    (USART_NOISE_FILTER_DISABLE == (x)))

#define IS_USART_OVERSAMPLING_BITS(x)                                          \
(   (USART_OVERSAMPLING_8BIT == (x))            ||                             \
    (USART_OVERSAMPLING_16BIT == (x)))

#define IS_USART_SIGNIFICANT_BIT(x)                                            \
(   (USART_MSB == (x))                          ||                             \
    (USART_LSB == (x)))

#define IS_USART_SB_DETECT_POLARITY(x)                                         \
(   (USART_SB_DETECT_LOW == (x))                ||                             \
    (USART_SB_DETECT_FALLING == (x)))

#define IS_USART_CLOCK_MODE(x)                                                 \
(   (USART_EXTCLK == (x))                       ||                             \
    (USART_INTERNCLK_OUTPUT == (x))             ||                             \
    (USART_INTERNCLK_NONE_OUTPUT == (x)))

#define IS_USART_SMARTCARD_CLOCK_MODE(x)                                       \
(   (USART_INTERNCLK_OUTPUT == (x))             ||                             \
    (USART_INTERNCLK_NONE_OUTPUT == (x)))

#define IS_USART_CLKSYNC_CLOCK_MODE(x)                                         \
(   (USART_EXTCLK == (x))                       ||                             \
    (USART_INTERNCLK_OUTPUT == (x)))

#define IS_USART_STOP_BITS(x)                                                  \
(   (USART_STOPBIT_1BIT == (x))                 ||                             \
    (USART_STOPBIT_2BIT == (x)))

#define IS_UART_DUPLEX_MODE(x)                                                 \
(   (USART_HALFDUPLEX_MODE == (x))              ||                             \
    (USART_FULLDUPLEX_MODE == (x)))

#define IS_USART_HWFLOWCTRL(x)                                                 \
(   (USART_HWFLOWCTRL_NONE == (x))              ||                             \
    (USART_HWFLOWCTRL_CTS == (x))               ||                             \
    (USART_HWFLOWCTRL_RTS == (x))               ||                             \
    (USART_HWFLOWCTRL_RTS_CTS == (x)))

#define IS_USART_PCLK_DIV(x)                                                   \
(   (USART_PCLK_DIV1 == (x))                    ||                             \
    (USART_PCLK_DIV4 == (x))                    ||                             \
    (USART_PCLK_DIV16 == (x))                   ||                             \
    (USART_PCLK_DIV64 == (x)))

#define IS_USART_LIN_BMC_PCLK_DIV(x)                                           \
(   (USART_LIN_BMC_PCLK_DIV1 == (x))            ||                             \
    (USART_LIN_BMC_PCLK_DIV2 == (x))            ||                             \
    (USART_LIN_BMC_PCLK_DIV4 == (x))            ||                             \
    (USART_LIN_BMC_PCLK_DIV8 == (x)))

#define IS_USART_STOPMODE_FILTER(x)                                            \
(   (USART_STOP_MODE_FILTER_NONE == (x))            ||                         \
    (USART_STOP_MODE_FILTER_WIDTH_LEVEL_1 == (x))   ||                         \
    (USART_STOP_MODE_FILTER_WIDTH_LEVEL_2 == (x))   ||                         \
    (USART_STOP_MODE_FILTER_WIDTH_LEVEL_3 == (x))   ||                         \
    (USART_STOP_MODE_FILTER_WIDTH_LEVEL_4 == (x)))

#define IS_USART_SMARTCARD_ETU_CLK(x)                                          \
(   (USART_SC_ETU_CLK_32 == (x))                ||                             \
    (USART_SC_ETU_CLK_64 == (x))                ||                             \
    (USART_SC_ETU_CLK_128 == (x))               ||                             \
    (USART_SC_ETU_CLK_256 == (x))               ||                             \
    (USART_SC_ETU_CLK_372 == (x)))

#define IS_USART_LIN_SEND_BREAK_MODE(x)                                        \
(   (USART_LIN_SEND_BREAK_MODE_SBK == (x))      ||                             \
    (USART_LIN_SEND_BREAK_MODE_TDR == (x)))

#define IS_USART_LIN_DETECT_BREAK_LEN(x)                                       \
(   (USART_LIN_DETECT_BREAK_10BIT == (x))       ||                             \
    (USART_LIN_DETECT_BREAK_11BIT == (x)))

#define IS_USART_LIN_SEND_BREAK_LEN(x)                                         \
(   (USART_LIN_SEND_BREAK_10BIT == (x))         ||                             \
    (USART_LIN_SEND_BREAK_11BIT == (x))         ||                             \
    (USART_LIN_SEND_BREAK_13BIT == (x))         ||                             \
    (USART_LIN_SEND_BREAK_14BIT == (x)))

/**
 * @}
 */

/**
 * @defgroup USART_Flag_Mask USART flag mask definition
 * @{
 */
#define USART_FLAG_MASK                     (USART_FLAG_PE      |              \
                                             USART_FLAG_FE      |              \
                                             USART_FLAG_ORE     |              \
                                             USART_FLAG_BE      |              \
                                             USART_FLAG_RXNE    |              \
                                             USART_FLAG_TC      |              \
                                             USART_FLAG_TXE     |              \
                                             USART_FLAG_RTOF    |              \
                                             USART_FLAG_LBD     |              \
                                             USART_FLAG_WKUP    |              \
                                             USART_FLAG_MPB)
/**
 * @}
 */

/**
 * @defgroup USART_Clear_Flag_Mask USART clear flag mask definition
 * @{
 */
#define USART_CLEAR_FLAG_MASK               (USART_CLEAR_FLAG_PE    |          \
                                             USART_CLEAR_FLAG_FE    |          \
                                             USART_CLEAR_FLAG_ORE   |          \
                                             USART_CLEAR_FLAG_RTOF  |          \
                                             USART_CLEAR_FLAG_BE    |          \
                                             USART_CLEAR_FLAG_WKUP  |          \
                                             USART_CLEAR_FLAG_LBD)
/**
 * @}
 */

/**
 * @defgroup USART_function_Mask USART function mask definition
 * @{
 */
#define USART_FUNCTION_MASK                 (USART_RX       |                  \
                                             USART_TX       |                  \
                                             USART_RTO      |                  \
                                             USART_INT_RX   |                  \
                                             USART_INT_TC   |                  \
                                             USART_INT_TXE  |                  \
                                             USART_INT_RTO)
/**
 * @}
 */

/**
 * @defgroup USART_LIN_function_Mask USART LIN function mask definition
 * @{
 */
#define USART_LIN_FUNCTION_MASK             (USART_LIN              |          \
                                             USART_LIN_WKUP         |          \
                                             USART_LIN_BUSERR       |          \
                                             USART_LIN_INT_WKUP     |          \
                                             USART_LIN_INT_BREAK    |          \
                                             USART_LIN_INT_BUSERR)
/**
 * @}
 */

/**
 * @defgroup USART_CR1_Clear_Flag_Mask USART register clear flag bits mask definition
 * @{
 */
#define USART_CR1_CLR_FLAG_MASK             (USART_CR1_CPE      |              \
                                             USART_CR1_CORE     |              \
                                             USART_CR1_CFE      |              \
                                             USART_CR1_CRTOF    |              \
                                             USART_CR1_CBE      |              \
                                             USART_CR1_CWKUP    |              \
                                             USART_CR1_CLBD)
/**
 * @}
 */

/**
 * @defgroup USART_CR2_Reserved_Bit USART CR2 register reserved bit 9/10 definition
 * @{
 */
#define USART_CR2_BIT9                      (0x00000200UL)
#define USART_CR2_BIT10                     (0x00000400UL)
/**
 * @}
 */

/**
 * @defgroup USART_Clk_Frequency USART Clk Frequency
 * @{
 */
#define USART_DIV(INSTANCE)                                                    \
(   1UL << (READ_REG32_BIT((INSTANCE)->PR, USART_PR_PSC) * 2UL))

#define USART_BMC_DIV(INSTANCE)                                                \
(   1UL << (READ_REG32_BIT((INSTANCE)->PR, USART_PR_LBMPSC) >> USART_PR_LBMPSC_POS))

#define PCLK_FREQ                                                              \
(   SystemCoreClock >> (READ_REG32_BIT(M4_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS))
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/
/**
 * @addtogroup USART_Local_Functions
 * @{
 */

static en_result_t CalcUartBaudrate(const M4_USART_TypeDef *USARTx,
                                        uint32_t u32UartClk,
                                        uint32_t u32Baudrate,
                                        uint32_t *pu32BrrVal,
                                        uint32_t *pu32FractEn,
                                        float32_t *pf32Err);
static en_result_t CalcClkSyncBaudrate(const M4_USART_TypeDef *USARTx,
                                            uint32_t u32UsartClk,
                                            uint32_t u32Baudrate,
                                            uint32_t *pu32BrrVal,
                                            uint32_t *pu32FractEn,
                                            float32_t *pf32Err);
static en_result_t CalcSmartcardBaudrate(const M4_USART_TypeDef *USARTx,
                                            uint32_t u32UartClk,
                                            uint32_t u32Baudrate,
                                            uint32_t *pu32BrrVal,
                                            uint32_t *pu32FractEn,
                                            float32_t *pf32Err);

/**
 * @}
 */

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup USART_Global_Functions USART Global Functions
 * @{
 */

/**
 * @brief  Initialize UART function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] pstcInit                Pointer to a @ref stc_usart_uart_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: the pointer pstcInit is NULL or baudrate set unsuccessfully
 */
en_result_t USART_UartInit(M4_USART_TypeDef *USARTx,
                            const stc_usart_uart_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_INSTANCE(USARTx));
        DDL_ASSERT(IS_USART_CLOCK_MODE(pstcInit->u32ClkMode));
        DDL_ASSERT(IS_USART_PARITY_CONTROL(pstcInit->u32Parity));
        DDL_ASSERT(IS_USART_DATA_WIDTH(pstcInit->u32DataWidth));
        DDL_ASSERT(IS_USART_STOP_BITS(pstcInit->u32StopBit));
        DDL_ASSERT(IS_USART_OVERSAMPLING_BITS(pstcInit->u32OversamplingBits));
        DDL_ASSERT(IS_USART_SIGNIFICANT_BIT(pstcInit->u32BitDirection));
        DDL_ASSERT(IS_USART_NOISE_FILTER(pstcInit->u32NoiseFilterState));
        DDL_ASSERT(IS_USART_SB_DETECT_POLARITY(pstcInit->u32SbDetectPolarity));
        DDL_ASSERT(IS_USART_HWFLOWCTRL(pstcInit->u32HwFlowCtrl));

        /* Disbale TX/RX && clear flag */
        WRITE_REG32(USARTx->CR1, USART_CR1_CLR_FLAG_MASK);

        /* Set CR2 */
        WRITE_REG32(USARTx->CR2, (USART_CR2_BIT9 | \
                                  USART_CR2_BIT10 | \
                                  pstcInit->u32ClkMode |
                                  pstcInit->u32StopBit));

        /* Set CR3 */
        WRITE_REG32(USARTx->CR3, pstcInit->u32HwFlowCtrl);

        /* Set CR1 */
        WRITE_REG32(USARTx->CR1, (pstcInit->u32Parity | \
                                  pstcInit->u32DataWidth | \
                                  pstcInit->u32OversamplingBits | \
                                  pstcInit->u32BitDirection | \
                                  pstcInit->u32NoiseFilterState | \
                                  pstcInit->u32SbDetectPolarity));

        /* Set LBMC */
        WRITE_REG32(USARTx->LBMC, 0UL);

        if (USART_EXTCLK != pstcInit->u32ClkMode)
        {
            DDL_ASSERT(IS_USART_PCLK_DIV(pstcInit->u32PclkDiv));

            /* Set PR */
            WRITE_REG32(USARTx->PR, pstcInit->u32PclkDiv);

            /* Set baudrate */
            enRet = USART_SetBaudrate(USARTx, pstcInit->u32Baudrate, NULL);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Initialize UART half duplex function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] pstcInit                Pointer to a @ref stc_usart_uart_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: the pointer pstcInit is NULL or baudrate set unsuccessfully
 */
en_result_t USART_HalfduplexInit(M4_USART_TypeDef *USARTx,
                                    const stc_usart_uart_init_t *pstcInit)
{
    en_result_t enRet;

    enRet = USART_UartInit(USARTx, pstcInit);
    if (Ok == enRet)
    {
        /* Set CR3: UART half duplex */
        SET_REG32_BIT(USARTx->CR3, USART_CR3_HDSEL);
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_usart_uart_init_t to default values.
 * @param  [out] pstcInit               Pointer to a @ref stc_usart_uart_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: the pointer pstcInit is NULL
 */
en_result_t USART_UartStructInit(stc_usart_uart_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32Baudrate = 9600UL;
        pstcInit->u32ClkMode = USART_INTERNCLK_NONE_OUTPUT;
        pstcInit->u32PclkDiv = USART_PCLK_DIV1;
        pstcInit->u32Parity = USART_PARITY_NONE;
        pstcInit->u32DataWidth = USART_DATA_LENGTH_8BIT;
        pstcInit->u32StopBit = USART_STOPBIT_1BIT;
        pstcInit->u32OversamplingBits = USART_OVERSAMPLING_16BIT;
        pstcInit->u32BitDirection = USART_LSB;
        pstcInit->u32NoiseFilterState = USART_NOISE_FILTER_DISABLE;
        pstcInit->u32SbDetectPolarity = USART_SB_DETECT_FALLING;
        pstcInit->u32HwFlowCtrl = USART_HWFLOWCTRL_NONE;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Initialize UART multiple processor function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] pstcInit                Pointer to a @ref stc_usart_multiprocessor_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: the pointer pstcInit is NULL or baudrate set unsuccessfully
 */
en_result_t USART_MultiProcessorInit(M4_USART_TypeDef *USARTx,
                                const stc_usart_multiprocessor_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_INSTANCE(USARTx));
        DDL_ASSERT(IS_USART_CLOCK_MODE(pstcInit->u32ClkMode));
        DDL_ASSERT(IS_USART_DATA_WIDTH(pstcInit->u32DataWidth));
        DDL_ASSERT(IS_USART_STOP_BITS(pstcInit->u32StopBit));
        DDL_ASSERT(IS_USART_OVERSAMPLING_BITS(pstcInit->u32OversamplingBits));
        DDL_ASSERT(IS_USART_SIGNIFICANT_BIT(pstcInit->u32BitDirection));
        DDL_ASSERT(IS_USART_NOISE_FILTER(pstcInit->u32NoiseFilterState));
        DDL_ASSERT(IS_USART_SB_DETECT_POLARITY(pstcInit->u32SbDetectPolarity));
        DDL_ASSERT(IS_USART_HWFLOWCTRL(pstcInit->u32HwFlowCtrl));

        /* Disbale TX/RX && clear flag */
        WRITE_REG32(USARTx->CR1, USART_CR1_CLR_FLAG_MASK);

        /* Set CR2 */
        WRITE_REG32(USARTx->CR2, (USART_CR2_MPE | \
                                  USART_CR2_BIT9 | \
                                  USART_CR2_BIT10 | \
                                  pstcInit->u32ClkMode | \
                                  pstcInit->u32StopBit));

        /* Set CR3 */
        WRITE_REG32(USARTx->CR3, pstcInit->u32HwFlowCtrl);

        /* Set CR1 */
        WRITE_REG32(USARTx->CR1, (pstcInit->u32DataWidth | \
                                  pstcInit->u32OversamplingBits | \
                                  pstcInit->u32BitDirection | \
                                  pstcInit->u32NoiseFilterState | \
                                  pstcInit->u32SbDetectPolarity));

        /* Set LBMC */
        WRITE_REG32(USARTx->LBMC, 0UL);

        if (USART_EXTCLK != pstcInit->u32ClkMode)
        {
            DDL_ASSERT(IS_USART_PCLK_DIV(pstcInit->u32PclkDiv));

            /* Set PR */
            WRITE_REG32(USARTx->PR, pstcInit->u32PclkDiv);

            /* Set baudrate */
            enRet = USART_SetBaudrate(USARTx, pstcInit->u32Baudrate, NULL);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_usart_multiprocessor_init_t to default values.
 * @param  [out] pstcInit               Pointer to a @ref stc_usart_multiprocessor_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: the pointer pstcInit is NULL
 */
en_result_t USART_MultiProcessorStructInit(stc_usart_multiprocessor_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32Baudrate = 9600UL;
        pstcInit->u32ClkMode = USART_INTERNCLK_NONE_OUTPUT;
        pstcInit->u32PclkDiv = USART_PCLK_DIV1;
        pstcInit->u32DataWidth = USART_DATA_LENGTH_8BIT;
        pstcInit->u32StopBit = USART_STOPBIT_1BIT;
        pstcInit->u32OversamplingBits = USART_OVERSAMPLING_16BIT;
        pstcInit->u32BitDirection = USART_LSB;
        pstcInit->u32NoiseFilterState = USART_NOISE_FILTER_DISABLE;
        pstcInit->u32SbDetectPolarity = USART_SB_DETECT_FALLING;
        pstcInit->u32HwFlowCtrl = USART_HWFLOWCTRL_NONE;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Initialize LIN function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] pstcInit                Pointer to a @ref stc_usart_lin_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: the pointer pstcInit is NULL or baudrate set unsuccessfully
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
en_result_t USART_LinInit(M4_USART_TypeDef *USARTx,
                            const stc_usart_lin_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));
        DDL_ASSERT(IS_USART_CLOCK_MODE(pstcInit->u32ClkMode));
        DDL_ASSERT(IS_USART_OVERSAMPLING_BITS(pstcInit->u32OversamplingBits));
        DDL_ASSERT(IS_USART_LIN_DETECT_BREAK_LEN(pstcInit->u32DetectBreakLen));
        DDL_ASSERT(IS_USART_LIN_SEND_BREAK_LEN(pstcInit->u32SendBreakLen));
        DDL_ASSERT(IS_USART_LIN_SEND_BREAK_MODE(pstcInit->u32SendBreakMode));

        /* Disbale TX/RX && clear flag */
        WRITE_REG32(USARTx->CR1, USART_CR1_CLR_FLAG_MASK);

        /* Set CR2 */
        WRITE_REG32(USARTx->CR2, (USART_CR2_BIT9 | \
                                  USART_CR2_BIT10 | \
                                  pstcInit->u32ClkMode | \
                                  USART_CR2_LINEN | \
                                  pstcInit->u32DetectBreakLen | \
                                  pstcInit->u32SendBreakLen | \
                                  pstcInit->u32SendBreakMode));

        /* Set CR3 */
        WRITE_REG32(USARTx->CR3, 0UL);

        /* Set CR1 */
        WRITE_REG32(USARTx->CR1, (pstcInit->u32OversamplingBits | \
                                  USART_CR1_SBS));

        /* Set LBMC */
        WRITE_REG32(USARTx->LBMC, 0UL);

        if (USART_EXTCLK != pstcInit->u32ClkMode)
        {
            DDL_ASSERT(IS_USART_PCLK_DIV(pstcInit->u32PclkDiv));
            DDL_ASSERT(IS_USART_LIN_BMC_PCLK_DIV(pstcInit->u32BmcPclkDiv));

            /* Set PR */
            WRITE_REG32(USARTx->PR, (pstcInit->u32PclkDiv | \
                                     pstcInit->u32BmcPclkDiv));

            /* Set baudrate */
            enRet = USART_SetBaudrate(USARTx, pstcInit->u32Baudrate, NULL);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_usart_lin_init_t to default values.
 * @param  [out] pstcInit               Pointer to a @ref stc_usart_lin_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: the pointer pstcInit is NULL
 */
en_result_t USART_LinStructInit(stc_usart_lin_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32Baudrate = 9600UL;
        pstcInit->u32ClkMode = USART_INTERNCLK_NONE_OUTPUT;
        pstcInit->u32PclkDiv = USART_PCLK_DIV1;
        pstcInit->u32BmcPclkDiv = USART_LIN_BMC_PCLK_DIV1;
        pstcInit->u32OversamplingBits = USART_OVERSAMPLING_16BIT;
        pstcInit->u32DetectBreakLen = USART_LIN_DETECT_BREAK_10BIT;
        pstcInit->u32SendBreakLen = USART_LIN_SEND_BREAK_10BIT;
        pstcInit->u32SendBreakMode = USART_LIN_SEND_BREAK_MODE_SBK;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Initialize smartcard function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 * @param  [in] pstcInit                Pointer to a @ref stc_usart_smartcard_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: the pointer pstcInit is NULL or baudrate set unsuccessfully
 * @note   Smartcard feature is unsupported by M4_USART5/M4_USART10
 */
en_result_t USART_SmartcardInit(M4_USART_TypeDef *USARTx,
                                    const stc_usart_smartcard_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_SMARTCARD_INSTANCE(USARTx));
        DDL_ASSERT(IS_USART_SMARTCARD_CLOCK_MODE(pstcInit->u32ClkMode));
        DDL_ASSERT(IS_USART_PCLK_DIV(pstcInit->u32PclkDiv));
        DDL_ASSERT(IS_USART_SIGNIFICANT_BIT(pstcInit->u32BitDirection));

        /* Disbale TX/RX && clear flag */
        WRITE_REG32(USARTx->CR1, USART_CR1_CLR_FLAG_MASK);

        /* Set CR2 */
        WRITE_REG32(USARTx->CR2, (USART_CR2_BIT9 | \
                                  USART_CR2_BIT10 | \
                                  pstcInit->u32ClkMode | \
                                  pstcInit->u32StopBit));

        /* Set CR3 */
        WRITE_REG32(USARTx->CR3, USART_CR3_SCEN | USART_SC_ETU_CLK_372);

        /* Set CR1 */
        WRITE_REG32(USARTx->CR1, (USART_CR1_PCE | \
                                  pstcInit->u32BitDirection | \
                                  USART_CR1_SBS));

        /* Set PR */
        WRITE_REG32(USARTx->PR, pstcInit->u32PclkDiv);

        /* Set LBMC */
        WRITE_REG32(USARTx->LBMC, 0UL);

        /* Set baudrate */
        enRet = USART_SetBaudrate(USARTx, pstcInit->u32Baudrate, NULL);
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_usart_smartcard_init_t to default values.
 * @param  [out] pstcInit               Pointer to a @ref stc_usart_smartcard_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: the pointer pstcInit is NULL
 */
en_result_t USART_SmartcardStructInit(stc_usart_smartcard_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32Baudrate = 9600UL;
        pstcInit->u32ClkMode = USART_INTERNCLK_NONE_OUTPUT;
        pstcInit->u32PclkDiv = USART_PCLK_DIV1;
        pstcInit->u32BitDirection = USART_LSB;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Initialize clock synchronization function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] pstcInit                Pointer to a @ref stc_usart_clksync_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: the pointer pstcInit is NULL or baudrate set unsuccessfully
 */
en_result_t USART_ClkSyncInit(M4_USART_TypeDef *USARTx,
                                const stc_usart_clksync_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_USART_INSTANCE(USARTx));
        DDL_ASSERT(IS_USART_CLKSYNC_CLOCK_MODE(pstcInit->u32ClkMode));
        DDL_ASSERT(IS_USART_SIGNIFICANT_BIT(pstcInit->u32BitDirection));
        DDL_ASSERT(IS_USART_HWFLOWCTRL(pstcInit->u32HwFlowCtrl));

        /* Disbale TX/RX && clear flag */
        WRITE_REG32(USARTx->CR1, USART_CR1_CLR_FLAG_MASK);

        /* Set CR2 */
        WRITE_REG32(USARTx->CR2, (USART_CR2_BIT9 | \
                                  USART_CR2_BIT10 | \
                                  pstcInit->u32ClkMode));

        /* Set CR3 */
        WRITE_REG32(USARTx->CR3, pstcInit->u32HwFlowCtrl);

        /* Set CR1 */
        WRITE_REG32(USARTx->CR1, (USART_CR1_MS | \
                                  pstcInit->u32BitDirection | \
                                  USART_CR1_SBS));

        /* Set LBMC */
        WRITE_REG32(USARTx->LBMC, 0UL);

        if (USART_EXTCLK != pstcInit->u32ClkMode)
        {
            DDL_ASSERT(IS_USART_PCLK_DIV(pstcInit->u32PclkDiv));

            /* Set PR */
            WRITE_REG32(USARTx->PR, pstcInit->u32PclkDiv);

            /* Set baudrate */
            enRet = USART_SetBaudrate(USARTx, pstcInit->u32Baudrate, NULL);
        }
        else
        {
            enRet = Ok;
        }
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_usart_clksync_init_t to default values.
 * @param  [out] pstcInit               Pointer to a @ref stc_usart_clksync_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: the pointer pstcInit is NULL
 */
en_result_t USART_ClkSyncStructInit(stc_usart_clksync_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32Baudrate = 9600UL;
        pstcInit->u32ClkMode = USART_INTERNCLK_NONE_OUTPUT;
        pstcInit->u32PclkDiv = USART_PCLK_DIV1;
        pstcInit->u32BitDirection = USART_LSB;
        pstcInit->u32HwFlowCtrl = USART_HWFLOWCTRL_NONE;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize USART function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval None
 */
void USART_DeInit(M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    /* Configures the registers to reset value. */
    WRITE_REG32(USARTx->CR1, USART_CR1_CLR_FLAG_MASK);
    WRITE_REG32(USARTx->PR, 0x00000000UL);
    WRITE_REG32(USARTx->BRR, 0x0000FF00UL);
    WRITE_REG32(USARTx->CR1, 0x80000000UL);
    WRITE_REG32(USARTx->CR2, 0x00000600UL);
    WRITE_REG32(USARTx->CR3, 0x00000000UL);
    WRITE_REG32(USARTx->LBMC, 0x00000000UL);
}

/**
 * @brief  Enable/disable USART Transmit/Receive Function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32Func                 USART function type
 *         This parameter can be any composed value of the following values:
 *           @arg USART_RX:             USART RX function
 *           @arg USART_TX:             USART TX function
 *           @arg USART_RTO:            USART RX timerout function
 *           @arg USART_INT_RX:         USART receive data register not empty && receive error interrupt
 *           @arg USART_INT_TE:         USART transmit data register empty interrupt
 *           @arg USART_INT_TC:         USART transmission complete interrupt
 *           @arg USART_INT_RTO:        USART RX timerout interrupt
 * @param  [in] enNewState              The function new state.
 *           @arg  This parameter can be: Enable or Disable.
 * @retval None
 * @note   USART RX timeout feature is supported by M4_USART1/M4_USART2/M4_USART5/M4_USART6
 */
void USART_FuncCmd(M4_USART_TypeDef *USARTx,
                        uint32_t u32Func,
                        en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_TIMEOUT_INSTANCE(USARTx) || \
               ((!IS_USART_TIMEOUT_INSTANCE(USARTx)) && (0UL == (u32Func & (USART_RTO | USART_INT_RTO)))));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_USART_FUNCTION(u32Func));

    (Enable == enNewState) ? SET_REG32_BIT(USARTx->CR1, u32Func) : CLEAR_REG32_BIT(USARTx->CR1, u32Func);
}

/**
 * @brief  Get USART function state.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32Func                 USART function type
 *         This parameter can be one of the following values:
 *           @arg USART_RX:             USART RX function
 *           @arg USART_TX:             USART TX function
 *           @arg USART_RTO:            USART RX timerout function
 *           @arg USART_INT_RX:         USART RX interrupt function
 *           @arg USART_INT_TXE:        Transmit data register empty interrupt
 *           @arg USART_INT_TC:         USART transmission complete interrupt
 *           @arg USART_INT_RTO:        USART RX timerout interrupt
 * @retval An en_functional_state_t enumeration value:
 *           - Enable: Enable function
 *           - Disable: Disable function
 */
en_functional_state_t USART_GetFuncState(const M4_USART_TypeDef *USARTx,
                                            uint32_t u32Func)
{
    /* Check parameters */
    DDL_ASSERT (IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_FUNCTION(u32Func));

    return (READ_REG32_BIT(USARTx->CR1, u32Func) ? Enable : Disable);
}

/**
 * @brief  Get USART flag.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32Flag                 USART flag type
 *         This parameter can be any composed value of the following values:
 *           @arg USART_FLAG_PE:        Parity error flag
 *           @arg USART_FLAG_FE:        Framing error flag
 *           @arg USART_FLAG_ORE:       Overrun error flag
 *           @arg USART_FLAG_BE:        LIN bus error flag
 *           @arg USART_FLAG_RXNE:      Receive data register not empty flag
 *           @arg USART_FLAG_TC:        Transmission complete flag
 *           @arg USART_FLAG_TXE:       Transmit data register empty flag
 *           @arg USART_FLAG_MPB:       Receive processor ID flag
 *           @arg USART_FLAG_RTOF:      Receive timeout flag
 *           @arg USART_FLAG_LBD:       LIN break signal detection flag
 *           @arg USART_FLAG_WKUP:      LIN wakeup signal detection flag
 *           @arg USART_FLAG_MPB:       Receive processor ID flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t USART_GetStatus(const M4_USART_TypeDef *USARTx,
                                    uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_FLAG(u32Flag));

    return (READ_REG32_BIT(USARTx->SR, u32Flag) ? Set : Reset);
}

/**
 * @brief  Get USART flag.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32Flag                 USART flag type
 *         This parameter can be any composed value of the following values:
 *           @arg USART_CLEAR_FLAG_PE:  Clear Parity error flag
 *           @arg USART_CLEAR_FLAG_FE:  Clear Framing error flag
 *           @arg USART_CLEAR_FLAG_ORE: Clear Overrun error flag
 *           @arg USART_CLEAR_FLAG_RTOF:Clear RX timeout flag
 *           @arg USART_CLEAR_FLAG_BE:  Clear LIN bus error flag
 *           @arg USART_CLEAR_FLAG_WKUP:Clear LIN wakeup signal flag
 *           @arg USART_CLEAR_FLAG_LBD: Clear Clear LIN break detection flag
 * @retval None
 */
void USART_ClearStatus(M4_USART_TypeDef *USARTx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT (IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_CLEAR_FLAG(u32Flag));

    SET_REG32_BIT(USARTx->CR1, u32Flag);
}

/**
 * @brief  Set USART transmission type.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32Type                 USART transmission content type
 *         This parameter can be one of the following values:
 *           @arg USART_TRANSMISSION_ID     USART transmission content type is processor ID
 *           @arg USART_TRANSMISSION_DATA   USART transmission content type is frame data
 * @retval None
 */
void USART_SetTransmissionType(M4_USART_TypeDef *USARTx, uint32_t u32Type)
{
    /* Check parameters */
    DDL_ASSERT (IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_TRANSMISSION_TYPE(u32Type));

    MODIFY_REG32(USARTx->DR, USART_DR_MPID, u32Type);
}

/**
 * @brief  Get USART transmission type.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_TRANSMISSION_ID     USART transmission content type is processor ID
 *           @arg USART_TRANSMISSION_DATA   USART transmission content type is frame data
 */
uint32_t USART_GetTransmissionType(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->DR, USART_DR_MPID);
}

/**
 * @brief  Set USART parity.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32Parity               USART parity
 *         This parameter can be one of the following values:
 *           @arg USART_PARITY_NONE:    Parity control disabled
 *           @arg USART_PARITY_ODD:     Parity control enabled and Odd Parity is selected
 *           @arg USART_PARITY_EVEN:    Parity control enabled and Even Parity is selected
 * @retval None
 */
void USART_SetParity(M4_USART_TypeDef *USARTx, uint32_t u32Parity)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_PARITY_CONTROL(u32Parity));

    MODIFY_REG32(USARTx->CR1, (USART_CR1_PS | USART_CR1_PCE), u32Parity);
}

/**
 * @brief  Get USART parity.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_PARITY_NONE:    Parity control disabled
 *           @arg USART_PARITY_ODD:     Parity control enabled and Odd Parity is selected
 *           @arg USART_PARITY_EVEN:    Parity control enabled and Even Parity is selected
 */
uint32_t USART_GetParity(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR1, (USART_CR1_PS | USART_CR1_PCE));
}

/**
 * @brief  Set USART data width.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32DataWidth            USART data width
 *         This parameter can be one of the following values:
 *           @arg USART_DATA_LENGTH_8BIT: 8 bits word length
 *           @arg USART_DATA_LENGTH_9BIT: 9 bits word length
 * @retval None
 */
void USART_SetDataWidth(M4_USART_TypeDef *USARTx, uint32_t u32DataWidth)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_DATA_WIDTH(u32DataWidth));

    MODIFY_REG32(USARTx->CR1, USART_CR1_M, u32DataWidth);
}

/**
 * @brief  Get USART data width.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_DATA_LENGTH_8BIT: 8 bits word length
 *           @arg USART_DATA_LENGTH_9BIT: 9 bits word length
 */
uint32_t USART_GetDataWidth(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR1, USART_CR1_M);
}

/**
 * @brief  Set USART oversampling bits.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32OversamplingBits     USART oversampling bits
 *         This parameter can be one of the following values:
 *           @arg USART_OVERSAMPLING_8BIT:    Oversampling by 8 bits
 *           @arg USART_OVERSAMPLING_16BIT:   Oversampling by 16 bits
 * @retval None
 */
void USART_SetOversmaplingBits(M4_USART_TypeDef *USARTx,
                                        uint32_t u32OversamplingBits)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_OVERSAMPLING_BITS(u32OversamplingBits));

    MODIFY_REG32(USARTx->CR1, USART_CR1_OVER8, u32OversamplingBits);
}

/**
 * @brief  Get USART oversampling bits.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_OVERSAMPLING_8BIT:    Oversampling by 8 bits
 *           @arg USART_OVERSAMPLING_16BIT:   Oversampling by 16 bits
 */
uint32_t USART_GetOversmaplingBits(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR1, USART_CR1_OVER8);
}

/**
 * @brief  Set USART bit direction.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32BitDir               USART bit direction
 *         This parameter can be one of the following values:
 *           @arg USART_MSB:            MSB(Most Significant Bit)
 *           @arg USART_LSB:            LSB(Least Significant Bit)
 * @retval None
 */
void USART_SetBitDirection(M4_USART_TypeDef *USARTx, uint32_t u32BitDir)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_SIGNIFICANT_BIT(u32BitDir));

    MODIFY_REG32(USARTx->CR1, USART_CR1_ML, u32BitDir);
}

/**
 * @brief  Get USART bit direction.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_MSB:            MSB(Most Significant Bit)
 *           @arg USART_LSB:            LSB(Least Significant Bit)
 */
uint32_t USART_GetBitDirection(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR1, USART_CR1_ML);
}

/**
 * @brief  Set USART start bit detect polarity.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32Polarity             USART start bit detect polarity
 *         This parameter can be one of the following values:
 *           @arg USART_SB_DETECT_LOW:      Detect RX pin low level
 *           @arg USART_SB_DETECT_FALLING:  Detect RX pin falling edge
 * @retval None
 */
void USART_SetSbDetectPolarity(M4_USART_TypeDef *USARTx,
                                        uint32_t u32Polarity)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_SB_DETECT_POLARITY(u32Polarity));

    MODIFY_REG32(USARTx->CR1, USART_CR1_SBS, u32Polarity);
}

/**
 * @brief  Get USART start bit detect polarity.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_SB_DETECT_LOW:      Detect RX pin low level
 *           @arg USART_SB_DETECT_FALLING:  Detect RX pin falling edge
 */
uint32_t USART_GetSbDetectPolarity(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR1, USART_CR1_SBS);
}

/**
 * @brief  Set USART clock mode.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32ClkMode              USART clock mode
 *         This parameter can be one of the following values:
 *           @arg USART_EXTCLK:                Select external clock source.
 *           @arg USART_INTERNCLK_OUTPUT:      Select internal clock source and output clock.
 *           @arg USART_INTERNCLK_NONE_OUTPUT: Select internal clock source and don't output clock
 * @retval None
 */
void USART_SetClockMode(M4_USART_TypeDef *USARTx, uint32_t u32ClkMode)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_CLOCK_MODE(u32ClkMode));

    MODIFY_REG32(USARTx->CR2, USART_CR2_CLKC, u32ClkMode);
}

/**
 * @brief  Get USART clock mode.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_EXTCLK:                Select external clock source.
 *           @arg USART_INTERNCLK_OUTPUT:      Select internal clock source and output clock.
 *           @arg USART_INTERNCLK_NONE_OUTPUT: Select internal clock source and don't output clock
 */
uint32_t USART_GetClockMode(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR2, USART_CR2_CLKC);
}

/**
 * @brief  Set USART stop bits.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32StopBits             USART stop bits
 *         This parameter can be one of the following values:
 *           @arg USART_STOPBIT_1BIT:    1 stop bit
 *           @arg USART_STOPBIT_2BIT:    2 stop bits
 * @retval None
 */
void USART_SetStopBits(M4_USART_TypeDef *USARTx, uint32_t u32StopBits)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_STOP_BITS(u32StopBits));

    MODIFY_REG32(USARTx->CR2, USART_CR2_STOP, u32StopBits);
}

/**
 * @brief  Get USART clock mode.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_STOPBIT_1BIT:    1 stop bit
 *           @arg USART_STOPBIT_2BIT:    2 stop bits
 */
uint32_t USART_GetStopBits(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR2, USART_CR2_STOP);
}

/**
 * @brief  USART receive data.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Receive data
 */
uint16_t USART_RecData(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    return (uint16_t)(READ_REG32(USARTx->DR) >> USART_DR_RDR_POS);
}

/**
 * @brief  USART send data.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 ** \param [in] u16Data                 Transmit data
 * @retval None
 */
void USART_SendData(M4_USART_TypeDef *USARTx, uint16_t u16Data)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    WRITE_REG32(USARTx->DR, ((uint32_t)u16Data & 0x01FFUL));
}

/**
 * @brief  USART send processor ID.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 ** \param [in] u16ID                   Processor ID
 * @retval None
 */
void USART_SendId(M4_USART_TypeDef *USARTx, uint16_t u16ID)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    WRITE_REG32(USARTx->DR, (USART_DR_MPID | ((uint32_t)u16ID & 0x01FFUL)));
}

/**
 * @brief  Enable or disable USART silence.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] enNewState              The function new state.
 *           @arg  This parameter can be: Enable or Disable.
 * @retval None
 */
void USART_SilenceCmd(M4_USART_TypeDef *USARTx,
                            en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(USARTx->CR1, USART_CR1_SLME);
    }
    else
    {
        CLEAR_REG32_BIT(USARTx->CR1, USART_CR1_SLME);
    }
}

/**
 * @brief  Enable or disable USART loop function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] enNewState              The function new state.
 *           @arg  This parameter can be: Enable or Disable.
 * @retval None
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
void USART_LinLoopCmd(M4_USART_TypeDef *USARTx,
                        en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(USARTx->CR3, USART_CR3_LOOP);
    }
    else
    {
        CLEAR_REG32_BIT(USARTx->CR3, USART_CR3_LOOP);
    }
}

/**
 * @brief  LIN Request break sending
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval None
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
void USART_LinRequestBreakSending(M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));

    SET_REG32_BIT(USARTx->CR2, USART_CR2_SBK);
}

/**
 * @brief  Get request break sending status
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Sending break
 *           - Reset: Send break completely
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
en_flag_status_t USART_GetLinRequestBreakStatus(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR2, USART_CR2_SBK) ? Set : Reset;
}

/**
 * @brief  Set send break mode for USART LIN.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32Mode                 USART send break mode
 *         This parameter can be one of the following values:
 *           @arg USART_LIN_SEND_BREAK_MODE_SBK: Start send break after USART_CR2 SBK bit set 1 value
 *           @arg USART_LIN_SEND_BREAK_MODE_TDR: Start send break after USART_DR TDR write 0x00 value
 * @retval None
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
void USART_SetLinBreakMode(M4_USART_TypeDef *USARTx, uint32_t u32Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_LIN_SEND_BREAK_MODE(u32Mode));

    MODIFY_REG32(USARTx->CR2, USART_CR2_SBKM, u32Mode);
}

/**
 * @brief  Get send break mode for USART LIN.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_LIN_SEND_BREAK_MODE_SBK: Start send break after USART_CR2 SBK bit set 1 value
 *           @arg USART_LIN_SEND_BREAK_MODE_TDR: Start send break after USART_DR TDR write 0x00 value
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
uint32_t USART_GetLinBreakMode(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR2, USART_CR2_SBKM);
}

/**
 * @brief  Set UART half/full duplex selection.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32Mode                 USART half/full duplex selection
 *         This parameter can be one of the following values:
 *           @arg USART_HALFDUPLEX_MODE:USART half-duplex mode
 *           @arg USART_FULLDUPLEX_MODE:USART full-duplex mode
 * @retval None
 */
void USART_SetDuplexMode(M4_USART_TypeDef *USARTx, uint32_t u32Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_UART_DUPLEX_MODE(u32Mode));

    MODIFY_REG32(USARTx->CR3, USART_CR3_HDSEL, u32Mode);
}

/**
 * @brief  Get USART half/full duplex.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_HALFDUPLEX_MODE:USART half-duplex mode
 *           @arg USART_FULLDUPLEX_MODE:USART full-duplex mode
 */
uint32_t USART_GetDuplexMode(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR3, USART_CR3_HDSEL);
}

/**
 * @brief  Set UART hardware flow control CTS/RTS selection.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32HwFlowCtrl           USART hardware flow control CTS/RTS selection
 *         This parameter can be one of the following values:
 *           @arg USART_HWFLOWCTRL_NONE Disable USART hardware flow control
 *           @arg USART_HWFLOWCTRL_CTS: UART hardware flow control CTS mode
 *           @arg USART_HWFLOWCTRL_RTS: UART hardware flow control RTS mode
 *           @arg USART_HWFLOWCTRL_RTS_CTS: UART hardware flow control RTS and CTS mode
 * @retval None
 */
void USART_SetHwFlowCtrl(M4_USART_TypeDef *USARTx, uint32_t u32HwFlowCtrl)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_HWFLOWCTRL(u32HwFlowCtrl));

    MODIFY_REG32(USARTx->CR3, (USART_CR3_RTSE | USART_CR3_CTSE), u32HwFlowCtrl);
}

/**
 * @brief  Get USART hardware flow control CTS/RTS selection.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_HWFLOWCTRL_NONE: Disable USART hardware flow control
 *           @arg USART_HWFLOWCTRL_CTS: UART hardware flow control CTS mode
 *           @arg USART_HWFLOWCTRL_RTS: UART hardware flow control RTS mode
 *           @arg USART_HWFLOWCTRL_RTS_CTS: UART hardware flow control RTS and CTS mode
 */
uint32_t USART_GetHwFlowCtrl(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR3, (USART_CR3_RTSE | USART_CR3_CTSE));
}

/**
 * @brief  Set USART Smartcard ETU Clock.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 * @param  [in] u32EtuClk               USART Smartcard ETU Clock.
 *         This parameter can be one of the following values:
 *           @arg USART_SC_ETU_CLK_32:  1 etu = 32/f
 *           @arg USART_SC_ETU_CLK_64:  1 etu = 64/f
 *           @arg USART_SC_ETU_CLK_128: 1 etu = 128/f
 *           @arg USART_SC_ETU_CLK_256: 1 etu = 256/f
 *           @arg USART_SC_ETU_CLK_372: 1 etu = 372/f
 * @retval None
 * @note   Smartcard feature is unsupported by M4_USART5/M4_USART10
 */
void USART_SetSmartcardEtuClk(M4_USART_TypeDef *USARTx,
                                    uint32_t u32EtuClk)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_SMARTCARD_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_SMARTCARD_ETU_CLK(u32EtuClk));

    MODIFY_REG32(USARTx->CR3, USART_CR3_BCN, u32EtuClk);
}

/**
 * @brief  Get USART Smartcard ETU Clock.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_SC_ETU_CLK_32:  1 etu = 32/f
 *           @arg USART_SC_ETU_CLK_64:  1 etu = 64/f
 *           @arg USART_SC_ETU_CLK_128: 1 etu = 128/f
 *           @arg USART_SC_ETU_CLK_256: 1 etu = 256/f
 *           @arg USART_SC_ETU_CLK_372: 1 etu = 372/f
 * @note   Smartcard feature is unsupported by M4_USART5/M4_USART10
 */
uint32_t USART_GetSmartcardEtuClk(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_SMARTCARD_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR3, USART_CR3_BCN);
}

/**
 * @brief  Set USART clock prescaler division.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32PclkDiv              USART clock prescaler division.
 *         This parameter can be one of the following values:
 *           @arg USART_PCLK_DIV1:     PCLK
 *           @arg USART_PCLK_DIV4:     PCLK/4
 *           @arg USART_PCLK_DIV16:    PCLK/16
 *           @arg USART_PCLK_DIV64:    PCLK/64
 * @retval None
 * @note   The PCLK division function is valid when clock source is PCLK
 */
void USART_SetPclkDiv(M4_USART_TypeDef *USARTx,
                                uint32_t u32PclkDiv)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_PCLK_DIV(u32PclkDiv));

    MODIFY_REG32(USARTx->PR, USART_PR_PSC, u32PclkDiv);
}

/**
 * @brief  Get USART clock prescaler division.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_PCLK_DIV1:     PCLK
 *           @arg USART_PCLK_DIV4:     PCLK/4
 *           @arg USART_PCLK_DIV16:    PCLK/16
 *           @arg USART_PCLK_DIV64:    PCLK/64
 * @note   The PCLK division function is valid when clock source is PCLK
 */
uint32_t USART_GetPclkDiv(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->PR, USART_PR_PSC);
}

/**
 * @brief  Set USART LIN counter clock prescaler division.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32PclkDiv              USART USART LIN counter clock prescaler division.
 *         This parameter can be one of the following values:
 *           @arg USART_LIN_BMC_PCLK_DIV1: PCLK
 *           @arg USART_LIN_BMC_PCLK_DIV2: PCLK/2
 *           @arg USART_LIN_BMC_PCLK_DIV4: PCLK/4
 *           @arg USART_LIN_BMC_PCLK_DIV8: PCLK/8
 * @retval None
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 * @note   The PCLK division function is valid when clock source is PCLK
 */
void USART_SetLinBmcPclkDiv(M4_USART_TypeDef *USARTx,
                                        uint32_t u32PclkDiv)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_LIN_BMC_PCLK_DIV(u32PclkDiv));

    MODIFY_REG32(USARTx->PR, USART_PR_LBMPSC, u32PclkDiv);
}

/**
 * @brief  Get USART LIN counter clock prescaler division.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_LIN_BMC_PCLK_DIV1: PCLK
 *           @arg USART_LIN_BMC_PCLK_DIV2: PCLK/2
 *           @arg USART_LIN_BMC_PCLK_DIV4: PCLK/4
 *           @arg USART_LIN_BMC_PCLK_DIV8: PCLK/8
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
uint32_t USART_GetLinBmcPclkDiv(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->PR, USART_PR_LBMPSC);
}

/**
 * @brief  Set stop mode noise filter.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 * @param  [in] u32Filter               The noise filter value
 *         This parameter can be one of the following values:
 *           @arg USART_STOP_MODE_FILTER_NONE:          Disable noise filter
 *           @arg USART_STOP_MODE_FILTER_WIDTH_LEVEL_1: Filter width level 1
 *           @arg USART_STOP_MODE_FILTER_WIDTH_LEVEL_2: Filter width level 2
 *           @arg USART_STOP_MODE_FILTER_WIDTH_LEVEL_3: Filter width level 3
 *           @arg USART_STOP_MODE_FILTER_WIDTH_LEVEL_4: Filter width level 4
 * @retval None
 * @note   The stop mode noise filter is supported by M4_USART1
 */
void USART_SetStopModeNoiseFilter(const M4_USART_TypeDef *USARTx,
                                            uint32_t u32Filter)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_STOPMODE_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_STOPMODE_FILTER(u32Filter));

    WRITE_REG32(M4_PERIC->USART1_NFC, u32Filter);
}

/**
 * @brief  Disable UART multiple processor function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_STOP_MODE_FILTER_NONE:          Disable noise filter
 *           @arg USART_STOP_MODE_FILTER_WIDTH_LEVEL_1: Filter width level 1
 *           @arg USART_STOP_MODE_FILTER_WIDTH_LEVEL_2: Filter width level 2
 *           @arg USART_STOP_MODE_FILTER_WIDTH_LEVEL_3: Filter width level 3
 *           @arg USART_STOP_MODE_FILTER_WIDTH_LEVEL_4: Filter width level 4
 * @note   The stop mode noise filter is supported by M4_USART1
 */
uint32_t USART_GetStopModeNoiseFilter(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_STOPMODE_INSTANCE(USARTx));

    return READ_REG32_BIT(M4_PERIC->USART1_NFC, (PERIC_USART1_NFC_NFE | PERIC_USART1_NFC_NFS));
}

/**
 * @brief  Enable/disable USART LIN Function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32Func                 USART function type
 *         This parameter can be any composed value of the following values:
 *           @arg USART_LIN:            USART LIN function
 *           @arg USART_LIN_WKUP:       USART LIN wakeup signal detect function
 *           @arg USART_LIN_INT_WKUP:   USART LIN wakeup signal detect interrupt function
 *           @arg USART_LIN_BUSERR:     USART LIN bus error detect function
 *           @arg USART_LIN_INT_BUSERR: USART LIN bus error detect interrupt function
 *           @arg USART_LIN_INT_BREAK:  USART LIN break field detect interrupt function
 * @param  [in] enNewState              The function new state.
 *           @arg  This parameter can be: Enable or Disable.
 * @retval None
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
void USART_LinFuncCmd(M4_USART_TypeDef *USARTx,
                            uint32_t u32Func,
                            en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_USART_LIN_FUNCTION(u32Func));

    (Enable == enNewState) ? SET_REG32_BIT(USARTx->CR2, u32Func) : CLEAR_REG32_BIT(USARTx->CR2, u32Func);
}

/**
 * @brief  Get USART LIN function state.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32Func                 USART function type
 *         This parameter can be one of the following values:
 *           @arg USART_LIN:            USART LIN function
 *           @arg USART_LIN_WKUP:       USART LIN wakeup signal detect function
 *           @arg USART_LIN_INT_WKUP:   USART LIN wakeup signal detect interrupt function
 *           @arg USART_LIN_BUSERR:     USART LIN bus error detect function
 *           @arg USART_LIN_INT_BUSERR: USART LIN bus error detect interrupt function
 *           @arg USART_LIN_INT_BREAK:  USART LIN break field detect interrupt function
 * @retval An en_functional_state_t enumeration value:
 *           - Enable: Enable function
 *           - Disable: Disable function
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
en_functional_state_t USART_GetLinFuncState(const M4_USART_TypeDef *USARTx,
                                                    uint32_t u32Func)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_FUNCTION(u32Func));

    return (READ_REG32_BIT(USARTx->CR2, u32Func) ? Enable : Disable);
}

/**
 * @brief  Get USART LIN baudrate measure count.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval LIN baudrate measure count value
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
uint32_t USART_GetLinMeasureCnt(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->LBMC, USART_LBMC_LBMC);
}

/**
 * @brief  Get USART LIN baudrate measure count.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @retval LIN baudrate measure count value
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
uint32_t USART_GetLinMeasureBaudrate(const M4_USART_TypeDef *USARTx)
{
    uint32_t u32BmClk;
    uint32_t u32BmDiv;
    uint32_t u32LBMC;

    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));

    u32BmDiv = USART_BMC_DIV(USARTx);
    u32BmClk = PCLK_FREQ / u32BmDiv;
    u32LBMC = READ_REG32_BIT(USARTx->LBMC, USART_LBMC_LBMC);

    return (u32LBMC > 0UL) ? (u32BmClk / u32LBMC) : 0UL;
}

/**
 * @brief  Set USART LIN break detection length.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 1 instance register base
 *           @arg M4_USART10:           USART unit 2 instance register base
 * @param  [in] u32Len                  USART clock prescaler division.
 *         This parameter can be one of the following values:
 *           @arg USART_LIN_DETECT_BREAK_10BIT: 10-bit break detection
 *           @arg USART_LIN_DETECT_BREAK_11BIT: 11-bit break detection
 * @retval None
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
void USART_SetLinDetectBreakLen(M4_USART_TypeDef *USARTx,
                                        uint32_t u32Len)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_LIN_DETECT_BREAK_LEN(u32Len));

    MODIFY_REG32(USARTx->CR2, USART_CR2_LBDL, u32Len);
}

/**
 * @brief  Get USART LIN break detection length.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 1 instance register base
 *           @arg M4_USART10:           USART unit 2 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_LIN_DETECT_BREAK_10BIT: 10-bit break detection
 *           @arg USART_LIN_DETECT_BREAK_11BIT: 11-bit break detection
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
uint32_t USART_GetLinDetectBreakLen(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR2, USART_CR2_LBDL);
}

/**
 * @brief  Set USART LIN break sending length.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 1 instance register base
 *           @arg M4_USART10:           USART unit 2 instance register base
 * @param  [in] u32Len                  USART clock prescaler division.
 *         This parameter can be one of the following values:
 *           @arg USART_LIN_SEND_BREAK_10BIT: Send break 10-bit
 *           @arg USART_LIN_SEND_BREAK_11BIT: Send break 11-bit
 *           @arg USART_LIN_SEND_BREAK_13BIT: Send break 13-bit
 *           @arg USART_LIN_SEND_BREAK_14BIT: Send break 14-bit
 * @retval None
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
void USART_SetLinSendBreakLen(M4_USART_TypeDef *USARTx, uint32_t u32Len)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));
    DDL_ASSERT(IS_USART_LIN_SEND_BREAK_LEN(u32Len));

    MODIFY_REG32(USARTx->CR2, USART_CR2_SBKL, u32Len);
}

/**
 * @brief  Get USART LIN break detection length.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART5:            USART unit 1 instance register base
 *           @arg M4_USART10:           USART unit 2 instance register base
 * @retval Returned value can be one of the following values:
 *           @arg USART_LIN_SEND_BREAK_10BIT: Send break 10-bit
 *           @arg USART_LIN_SEND_BREAK_11BIT: Send break 11-bit
 *           @arg USART_LIN_SEND_BREAK_13BIT: Send break 13-bit
 *           @arg USART_LIN_SEND_BREAK_14BIT: Send break 14-bit
 * @note   LIN feature is supported by M4_USART5/M4_USART10
 */
uint32_t USART_GetLinSendBreakLen(const M4_USART_TypeDef *USARTx)
{
    /* Check parameters */
    DDL_ASSERT(IS_USART_LIN_INSTANCE(USARTx));

    return READ_REG32_BIT(USARTx->CR2, USART_CR2_SBKL);
}

/**
 * @brief  Set USART baudrate.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32Baudrate             UART baudrate
 * @param  [out] pf32Err                E(%) baudrate error rate
 * @retval An en_result_t enumeration value:
 *           - Ok: Set successfully
 *           - ErrorInvalidParameter: set unsuccessfully
 */
en_result_t USART_SetBaudrate(M4_USART_TypeDef *USARTx,
                                    uint32_t u32Baudrate,
                                    float32_t *pf32Err)
{
    uint32_t u32Mode;
    uint32_t u32BrrVal = 0UL;
    uint32_t u32FractEn = 0UL;
    uint32_t u32UsartClk;
    uint32_t u32UsartDiv;
    en_result_t enRet;

    /* Check parameter */
    DDL_ASSERT(u32Baudrate > 0UL);
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    /* Get USART clock frequency */
    u32UsartDiv = USART_DIV(USARTx);
    u32UsartClk = PCLK_FREQ / u32UsartDiv;

    u32Mode = READ_REG32_BIT(USARTx->CR3, USART_CR3_SCEN);
    if (u32Mode > 0UL)
    {
        /* Smart card */
        enRet = CalcSmartcardBaudrate(USARTx, u32UsartClk, u32Baudrate, &u32BrrVal, &u32FractEn, pf32Err);
    }
    else
    {
        u32Mode = READ_REG32_BIT(USARTx->CR1, USART_CR1_MS);
        if (u32Mode > 0UL)
        {
            /* Clock synchronization */
            enRet = CalcClkSyncBaudrate(USARTx, u32UsartClk, u32Baudrate, &u32BrrVal, &u32FractEn, pf32Err);
        }
        else
        {
            /* UART */
            enRet = CalcUartBaudrate(USARTx, u32UsartClk, u32Baudrate, &u32BrrVal, &u32FractEn, pf32Err);
        }
    }

    if (Ok == enRet)
    {
        if ((!IS_USART_FRACTION_INSTANCE(USARTx)) && (u32FractEn > 0UL))
        {
            enRet = Error;
        }
        else
        {
            /* Set baudrate */
            MODIFY_REG32(USARTx->CR1, USART_CR1_FBME, u32FractEn);
            WRITE_REG32(USARTx->BRR, u32BrrVal);
        }
    }

    return enRet;
}

/**
 * @}
 */

/**
 * @defgroup USART_Local_Functions USART Local Functions
 * @{
 */

/**
 * @brief  Calculate baudrate for UART mode.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32UsartClk             USART clock
 * @param  [in] u32Baudrate             UART baudrate
 * @param  [out] pu32BrrVal             Pointer to BRR register value
 * @param  [out] pu32FractEn            Pointer to CR1 FBME bit value
 * @param  [out] pf32Err                E(%) baudrate error rate
 * @retval An en_result_t enumeration value:
 *           - Ok: Set successfully
 *           - ErrorInvalidParameter: set unsuccessfully
 * @note   Baudrate fraction feature is unsupported by M4_USART5/M4_USART10
 */
static en_result_t CalcUartBaudrate(const M4_USART_TypeDef *USARTx,
                                        uint32_t u32UsartClk,
                                        uint32_t u32Baudrate,
                                        uint32_t *pu32BrrVal,
                                        uint32_t *pu32FractEn,
                                        float32_t *pf32Err)
{
    uint32_t B;
    uint32_t C;
    uint32_t OVER8;
    float32_t DIV;
    uint64_t u64Temp;
    uint64_t u64Dividend;
    uint32_t DIV_Integer;
    uint32_t DIV_Fraction = 0UL;
    float32_t f32Err;
    en_result_t enRet = Ok;

    /* Check parameter */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    C = u32UsartClk;
    B = u32Baudrate;

    if ((C > 0UL) && (B > 0UL))
    {
        OVER8 = READ_REG32_BIT(USARTx->CR1, USART_CR1_OVER8) ? 1UL : 0UL;

        /* UART mode baudrate integer calculation formula:      */
        /*      B = C / (8 * (2 - OVER8) * (DIV_Integer + 1))   */
        /*      DIV_Integer = (C / (B * 8 * (2 - OVER8))) - 1   */
        DIV = ((float)C / ((float)B * 8.0F * (2.0F - (float)OVER8))) - 1.0F;
        DIV_Integer = (uint32_t)(DIV);
        DDL_ASSERT((DIV > 0.0F) && (DIV_Integer <= 0xFFUL));

        u64Temp = (uint64_t)((uint64_t)8UL * ((uint64_t)2UL - (uint64_t)OVER8) * ((uint64_t)DIV_Integer + (uint64_t)1UL) * (uint64_t)B);

        if (IS_USART_FRACTION_INSTANCE(USARTx))
        {
            if ((DIV - (float32_t)DIV_Integer) > 0.00001F)
            {
                /* UART mode baudrate fraction calculation formula:                                 */
                /*      B = C * (128 + DIV_Fraction) / (8 * (2 - OVER8) * (DIV_Integer + 1) * 256)  */
                /*      DIV_Fraction = (256 * (8 * (2 - OVER8) * (DIV_Integer + 1) * B) / C) - 128  */
                DIV_Fraction = (uint32_t)(256UL * u64Temp / C - 128UL);
                if (DIV_Fraction > 0x7FUL)
                {
                    enRet = ErrorInvalidParameter;
                }
            }
        }

        if (Ok == enRet)
        {
            *pu32FractEn = (DIV_Fraction > 0UL) ? USART_CR1_FBME : 0UL;
            *pu32BrrVal = DIV_Fraction + (uint32_t)(DIV_Integer << USART_BRR_DIV_INTEGER_POS);

            if (NULL != pf32Err)
            {
                if (0UL == DIV_Fraction)
                {
                    /* E(%) = C / (8 * (2 - OVER8) * (DIV_Integer + 1) * B) - 1 */
                    f32Err = (float32_t)((float64_t)C / (float64_t)u64Temp) - 1.0F;
                }
                else
                {
                    /* E(%) = C * (128 + DIV_Fraction) / (256 * (8 * (2 - OVER8) * (DIV_Integer + 1) * B)) - 1 */
                    u64Temp *= (uint64_t)256UL;
                    u64Dividend = (uint64_t)C * ((uint64_t)128UL + (uint64_t)DIV_Fraction);
                    f32Err = (float32_t)((float64_t)(u64Dividend) / (float64_t)(u64Temp)) - 1.0F;
                }

                *pf32Err = f32Err;
            }
        }
    }
    else
    {
        enRet = ErrorInvalidParameter;
    }

    return enRet;
}

/**
 * @brief  Calculate baudrate for clock synchronization mode.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART5:            USART unit 5 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 *           @arg M4_USART10:           USART unit 10 instance register base
 * @param  [in] u32UsartClk             USART clock
 * @param  [in] u32Baudrate             UART baudrate
 * @param  [out] pu32BrrVal             Pointer to BRR register value
 * @param  [out] pu32FractEn            Pointer to CR1 FBME bit value
 * @param  [out] pf32Err                E(%) baudrate error rate
 * @retval An en_result_t enumeration value:
 *           - Ok: Set successfully
 *           - ErrorInvalidParameter: set unsuccessfully
 */
static en_result_t CalcClkSyncBaudrate(const M4_USART_TypeDef *USARTx,
                                            uint32_t u32UsartClk,
                                            uint32_t u32Baudrate,
                                            uint32_t *pu32BrrVal,
                                            uint32_t *pu32FractEn,
                                            float32_t *pf32Err)
{
    uint32_t C;
    uint32_t B;
    float32_t DIV;
    uint64_t u64Temp;
    uint64_t u64Dividend;
    uint32_t DIV_Integer;
    uint32_t DIV_Fraction = 0UL;
    float32_t f32Err;
    en_result_t enRet = Ok;

    /* Check parameter */
    DDL_ASSERT(IS_USART_INSTANCE(USARTx));

    C = u32UsartClk;
    B = u32Baudrate;

    if ((C > 0UL) && (B > 0UL))
    {
        /* Clock sync mode baudrate integer calculation formula:    */
        /*          B = C / (4 * (DIV_Integer + 1))                 */
        /*          DIV_Integer = (C / (B * 4)) - 1                 */
        DIV = ((float)C / ((float)B * 4.0F)) - 1.0F;
        DIV_Integer = (uint32_t)DIV;
        DDL_ASSERT((DIV > 0.0F) && (DIV_Integer <= 0xFFUL));

        u64Temp = (uint64_t)((uint64_t)4U * ((uint64_t)DIV_Integer + (uint64_t)1UL) * (uint64_t)B);

        if (IS_USART_FRACTION_INSTANCE(USARTx))
        {
            if ((DIV - (float32_t)DIV_Integer) > 0.00001F)
            {
                /* Clock sync mode baudrate fraction calculation formula:               */
                /*      B = C * (128 + DIV_Fraction) / (4 * (DIV_Integer + 1) * 256)    */
                /*      DIV_Fraction = 256 * (4 * (DIV_Integer + 1) * B / C - 128       */
                DIV_Fraction = (uint32_t)(256UL * u64Temp / C - 128UL);
                if (DIV_Fraction > 0x7FUL)
                {
                    enRet = ErrorInvalidParameter;
                }
            }
        }

        if (Ok == enRet)
        {
            *pu32FractEn = (DIV_Fraction > 0UL) ? USART_CR1_FBME : 0UL;
            *pu32BrrVal = DIV_Fraction + (uint32_t)(DIV_Integer << USART_BRR_DIV_INTEGER_POS);

            if (NULL != pf32Err)
            {
                if (0UL == DIV_Fraction)
                {
                    /* E(%) = C / (4 * (DIV_Integer + 1) * B) - 1 */
                    f32Err = (float32_t)((float64_t)C / (float64_t)u64Temp) - 1.0F;
                }
                else
                {
                    /* E(%) = C * (128 + DIV_Fraction) / (4 * (DIV_Integer + 1) * B * 256) - 1 */
                    u64Temp *= (uint64_t)256UL;
                    u64Dividend = (uint64_t)C * ((uint64_t)128UL + (uint64_t)DIV_Fraction);
                    f32Err = (float32_t)((float64_t)(u64Dividend) / (float64_t)(u64Temp)) - 1.0F;
                }

                *pf32Err = f32Err;
            }
        }
    }
    else
    {
        enRet = ErrorInvalidParameter;
    }

    return enRet;
}

/**
 * @brief  Calculate baudrate for smart-card mode.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_USART1:            USART unit 1 instance register base
 *           @arg M4_USART2:            USART unit 2 instance register base
 *           @arg M4_USART3:            USART unit 3 instance register base
 *           @arg M4_USART4:            USART unit 4 instance register base
 *           @arg M4_USART6:            USART unit 6 instance register base
 *           @arg M4_USART7:            USART unit 7 instance register base
 *           @arg M4_USART8:            USART unit 8 instance register base
 *           @arg M4_USART9:            USART unit 9 instance register base
 * @param  [in] u32UsartClk             USART clock
 * @param  [in] u32Baudrate             UART baudrate
 * @param  [out] pu32BrrVal             Pointer to BRR register value
 * @param  [out] pu32FractEn            Pointer to CR1 FBME bit value
 * @param  [out] pf32Err                E(%) baudrate error rate
 * @retval An en_result_t enumeration value:
 *           - Ok: Set successfully
 *           - ErrorInvalidParameter: set unsuccessfully
 * @note   Smartcard feature is unsupported by M4_USART5/M4_USART10
 */
static en_result_t CalcSmartcardBaudrate(const M4_USART_TypeDef *USARTx,
                                            uint32_t u32UsartClk,
                                            uint32_t u32Baudrate,
                                            uint32_t *pu32BrrVal,
                                            uint32_t *pu32FractEn,
                                            float32_t *pf32Err)
{
    uint32_t B;
    uint32_t C;
    uint32_t BCN;
    float32_t DIV;
    uint64_t u64Temp;
    uint64_t u64Dividend;
    uint32_t DIV_Integer;
    uint32_t DIV_Fraction = 0UL;
    const uint16_t au16EtuClkCnts[] = {32U, 64U, 93U, 128U, 186U, 256U, 372U, 512U};
    float32_t f32Err;
    en_result_t enRet = Ok;

    /* Check parameter */
    DDL_ASSERT(IS_USART_SMARTCARD_INSTANCE(USARTx));

    C = u32UsartClk;
    B = u32Baudrate;

    if ((C > 0UL) && (B > 0UL))
    {
        BCN = READ_REG32_BIT(USARTx->CR3, USART_CR3_BCN);
        DDL_ASSERT(IS_USART_SMARTCARD_ETU_CLK(BCN));
        BCN = au16EtuClkCnts[BCN >> USART_CR3_BCN_POS];

        /* Smartcard mode baudrate integer calculation formula: */
        /*      B = C / (2 * BCN * (DIV_Integer + 1))           */
        /*      DIV_Integer = (C / (B * 2 * BCN)) - 1           */
        DIV = ((float)C / ((float)B * (float)BCN * 2.0F)) - 1.0F;
        DIV_Integer = (uint32_t)DIV;

        DDL_ASSERT((DIV > 0.0F) && (DIV_Integer <= 0xFFUL));

        u64Temp = (uint64_t)((uint64_t)2UL * BCN * ((uint64_t)DIV_Integer + (uint64_t)1UL) * B);

        if (IS_USART_FRACTION_INSTANCE(USARTx))
        {
            if ((DIV - (float32_t)DIV_Integer) > 0.00001F)
            {
                /* Smartcard mode baudrate fraction calculation formula:                        */
                /*      B = C * (128 + DIV_Fraction) / ((2 * BCN) * (DIV_Integer + 1) * 256)    */
                /*      DIV_Fraction = (256 * (2 * BCN * (DIV_Integer + 1) * B) / C) - 128      */
                DIV_Fraction = (uint32_t)(256UL * u64Temp / C - 128UL);
                if (DIV_Fraction > 0x7FUL)
                {
                    enRet = ErrorInvalidParameter;
                }
            }
        }

        if (Ok == enRet)
        {
            *pu32FractEn = (DIV_Fraction > 0UL )? USART_CR1_FBME : 0UL;
            *pu32BrrVal = DIV_Fraction + (uint32_t)(DIV_Integer << USART_BRR_DIV_INTEGER_POS);

            if (NULL != pf32Err)
            {
                if (0UL == DIV_Fraction)
                {
                    /* E(%) = C / (2 * BCN * (DIV_Integer + 1) * B) - 1 */
                    f32Err = (float32_t)((float64_t)C / (float64_t)u64Temp) - 1.0F;
                }
                else
                {
                    /* E(%) = C * (128 + DIV_Fraction) / (2 * BCN * (DIV_Integer + 1) * B * 256) - 1 */
                    u64Temp *= (uint64_t)256UL;
                    u64Dividend = (uint64_t)C * ((uint64_t)128UL + (uint64_t)DIV_Fraction);
                    f32Err = (float32_t)((float64_t)u64Dividend / (float64_t)(u64Temp)) - 1.0F;
                }

                *pf32Err = f32Err;
            }
        }
    }
    else
    {
        enRet = ErrorInvalidParameter;
    }

    return enRet;
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
