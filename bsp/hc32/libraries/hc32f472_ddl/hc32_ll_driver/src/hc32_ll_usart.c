/**
 *******************************************************************************
 * @file  hc32_ll_usart.c
 * @brief This file provides firmware functions to manage the USART(Universal
 *        Synchronous/Asynchronous Receiver Transmitter).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Add function note: USART_FuncCmd
                                    Modify typo
                                    Round off baudrate fraction division
                                    Split register USART_DR to USART_RDR and USART_TDR
                                    Modify USART_SetTransType parameter: u32Type -> u16Type
                                    Delete function: USART_GetUsartClockDiv
                                    Fix MISRAC2012 warning: USART_GetUsartClockFreq
                                    Code Refine
   2023-09-30       CDT             Modify USART_SmartCard_Init() for stc_usart_smartcard_init_t has modified(u32StopBit has removed)
                                    Fix bug: did not enable MP while USART_MultiProcessor_Init()
   2023-12-15       CDT             Add API USART_GetFuncState()
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_usart.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_USART USART
 * @brief USART Driver Library
 * @{
 */

#if (LL_USART_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/**
 * @defgroup USART_Local_Types USART Local Types
 * @{
 */

/**
 * @brief usart BRR division calculate structure definition
 */
typedef struct {
    uint32_t u32UsartClock;             /*!< USART clock. */
    uint32_t u32Baudrate;               /*!< USART baudrate. */
    uint32_t u32Integer;                /*!< Pointer to BRR integer division value. */
    uint32_t u32Fraction;               /*!< Pointer to BRR fraction division value. */
    float32_t f32Error;                 /*!< E(%) baudrate error rate. */
} stc_usart_brr_t;

/**
 * @}
 */

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

/**
 * @defgroup USART_Check_Parameters_Validity_Unit USART Check Parameters Validity Unit
 * @{
 */
#define IS_USART_UNIT(x)                                                       \
(   ((x) == CM_USART1)                  ||                                     \
    ((x) == CM_USART2)                  ||                                     \
    ((x) == CM_USART3)                  ||                                     \
    ((x) == CM_USART4)                  ||                                     \
    ((x) == CM_USART5)                  ||                                     \
    ((x) == CM_USART6))
#define IS_USART_SMARTCARD_UNIT(x)                                             \
(   ((x) == CM_USART1)                  ||                                     \
    ((x) == CM_USART2)                  ||                                     \
    ((x) == CM_USART4)                  ||                                     \
    ((x) == CM_USART5))
#define IS_USART_LIN_UNIT(x)                                                   \
(   ((x) == CM_USART3)                  ||                                     \
    ((x) == CM_USART6))
#define IS_USART_STOP_MD_UNIT(x)        ((x) == CM_USART1)
#define IS_USART_TIMEOUT_UNIT(x)                                               \
(   ((x) == CM_USART1)                  ||                                     \
    ((x) == CM_USART2)                  ||                                     \
    ((x) == CM_USART4)                  ||                                     \
    ((x) == CM_USART5))
/**
 * @}
 */

#define IS_USART_FUNC(x)                                                       \
(   ((x) != 0UL)                        &&                                     \
    (((x) | USART_FUNC_ALL) == USART_FUNC_ALL))

#define IS_USART_FLAG(x)                                                       \
(   ((x) != 0UL)                        &&                                     \
    (((x) | USART_FLAG_ALL) == USART_FLAG_ALL))

#define IS_USART_TRANS_TYPE(x)                                                 \
(   ((x) == USART_TRANS_ID)             ||                                     \
    ((x) == USART_TRANS_DATA))

#define IS_USART_PARITY(x)                                                     \
(   ((x) == USART_PARITY_ODD)           ||                                     \
    ((x) == USART_PARITY_EVEN)          ||                                     \
    ((x) == USART_PARITY_NONE))

#define IS_USART_DATA_WIDTH(x)                                                 \
(   ((x) == USART_DATA_WIDTH_8BIT)      ||                                     \
    ((x) == USART_DATA_WIDTH_9BIT))

#define IS_USART_STOPBIT(x)                                                    \
(   ((x) == USART_STOPBIT_1BIT)         ||                                     \
    ((x) == USART_STOPBIT_2BIT))

#define IS_USART_FIRST_BIT(x)                                                  \
(   ((x) == USART_FIRST_BIT_MSB)        ||                                     \
    ((x) == USART_FIRST_BIT_LSB))

#define IS_USART_OVER_SAMPLE_BIT(x)                                            \
(   ((x) == USART_OVER_SAMPLE_8BIT)     ||                                     \
    ((x) == USART_OVER_SAMPLE_16BIT))

#define IS_USART_START_BIT_POLARITY(x)                                         \
(   ((x) == USART_START_BIT_LOW)        ||                                     \
    ((x) == USART_START_BIT_FALLING))

#define IS_USART_CLK_SRC(x)                                                    \
(   ((x) == USART_CLK_SRC_EXTCLK)       ||                                     \
    ((x) == USART_CLK_SRC_INTERNCLK))

#define IS_USART_CK_OUTPUT(x)                                                  \
(   ((x) == USART_CK_OUTPUT_ENABLE)     ||                                     \
    ((x) == USART_CK_OUTPUT_DISABLE))

#define IS_USART_CLK_DIV(x)             ((x) <= USART_CLK_DIV_MAX)

#define IS_USART_DATA(x)                ((x) <= 0x01FFUL)

/**
 * @defgroup USART_Check_Parameters_Validity_Hardware_Flow_Control USART Check Parameters Validity Hardware Flow Control
 * @{
 */
#define IS_USART_HW_FLOWCTRL(x)                                                \
(   ((x) == USART_HW_FLOWCTRL_NONE)     ||                                     \
    ((x) == USART_HW_FLOWCTRL_CTS)      ||                                     \
    ((x) == USART_HW_FLOWCTRL_RTS)      ||                                     \
    ((x) == USART_HW_FLOWCTRL_RTS_CTS))
/**
 * @}
 */

/**
 * @defgroup USART_Check_Parameters_Validity_Smartcard_Clock USART Check Parameters Validity Smartcard Clock
 * @{
 */
#define IS_USART_SMARTCARD_ETU_CLK(x)                                          \
(   ((x) == USART_SC_ETU_CLK32)         ||                                     \
    ((x) == USART_SC_ETU_CLK64)         ||                                     \
    ((x) == USART_SC_ETU_CLK128)        ||                                     \
    ((x) == USART_SC_ETU_CLK256)        ||                                     \
    ((x) == USART_SC_ETU_CLK372))
/**
 * @}
 */

/**
 * @defgroup USART_Check_Parameters_Validity_Stopmode_Filter USART Check Parameters Validity Stopmode Filter
 * @{
 */
#define IS_USART_STOP_MD_FILTER(x)                                             \
(   ((x) == USART_STOP_MD_FILTER_LVL1)  ||                                     \
    ((x) == USART_STOP_MD_FILTER_LVL2)  ||                                     \
    ((x) == USART_STOP_MD_FILTER_LVL3)  ||                                     \
    ((x) == USART_STOP_MD_FILTER_LVL4))
/**
 * @}
 */

/**
 * @defgroup USART_Check_Parameters_Validity_Timeout_Function USART Check Parameters Validity Timeout Function
 * @{
 */
#define IS_USART_TIMEOUT_FUNC(x, func)                                         \
(   IS_USART_TIMEOUT_UNIT(x)            ||                                     \
    ((!IS_USART_TIMEOUT_UNIT(x)) && (((func) & (USART_RX_TIMEOUT | USART_INT_RX_TIMEOUT)) == 0UL)))
/**
 * @}
 */

/**
 * @defgroup USART_Check_Parameters_Validity_LIN_Function USART Check Parameters Validity LIN Function
 * @{
 */
#define IS_USART_LIN_FUNC(x, func)                                             \
(   IS_USART_LIN_UNIT(x)                ||                                     \
    ((!IS_USART_LIN_UNIT(x)) && (((func) & USART_LIN_FUNC_MASK) == 0UL)))

#define IS_USART_LIN_BMC_CLK_DIV(x)                                            \
(   ((x) == USART_LIN_BMC_CLK_DIV1)     ||                                     \
    ((x) == USART_LIN_BMC_CLK_DIV2)     ||                                     \
    ((x) == USART_LIN_BMC_CLK_DIV4)     ||                                     \
    ((x) == USART_LIN_BMC_CLK_DIV8))

#define IS_USART_LIN_SEND_BREAK_MD(x)                                          \
(   ((x) == USART_LIN_SEND_BREAK_MD_SBK)    ||                                 \
    ((x) == USART_LIN_SEND_BREAK_MD_TDR))

#define IS_USART_LIN_DETECT_BREAK_LEN(x)                                       \
(   ((x) == USART_LIN_DETECT_BREAK_10BIT)   ||                                 \
    ((x) == USART_LIN_DETECT_BREAK_11BIT))

#define IS_USART_LIN_SEND_BREAK_LEN(x)                                         \
(   ((x) == USART_LIN_SEND_BREAK_10BIT) ||                                     \
    ((x) == USART_LIN_SEND_BREAK_11BIT) ||                                     \
    ((x) == USART_LIN_SEND_BREAK_13BIT) ||                                     \
    ((x) == USART_LIN_SEND_BREAK_14BIT))
/**
 * @}
 */

/**
 * @}
 */

/**
 * @defgroup USART_Flag_Error_Mask USART Flag Error Mask
 * @{
 */
#define USART_FLAG_ERR_MASK             (USART_FLAG_OVERRUN     |              \
                                         USART_FLAG_FRAME_ERR   |              \
                                         USART_FLAG_PARITY_ERR)
/**
 * @}
 */

/**
 * @defgroup USART_Registers_Reset_Value_definition USART Registers Reset Value
 * @{
 */
#define USART_CR1_RST_VALUE             (0x80000000UL)

#define USART_CR2_RST_VALUE             (0x0600UL)
/**
 * @}
 */

/**
 * @defgroup USART_LIN_Function_Mask USART LIN Function Mask
 * @{
 */
#define USART_LIN_FUNC_OFFSET           (16U)

#define USART_LIN_FUNC_MASK             (USART_LIN              |              \
                                         USART_LIN_ERR          |              \
                                         USART_LIN_WKUP         |              \
                                         USART_LIN_INT_WKUP     |              \
                                         USART_LIN_INT_BREAK    |              \
                                         USART_LIN_INT_ERR)
/**
 * @}
 */

/**
 * @defgroup USART_BRR_Division_Max USART BRR Register Division Max
 * @{
 */
#define USART_BRR_DIV_INTEGER_MAX       (0xFFUL)
#define USART_BRR_DIV_FRACTION_MAX      (0x7FUL)
/**
 * @}
 */

/**
 * @defgroup USART_Clock_Division_Max USART Clock Division Max
 * @{
 */
#define USART_CLK_DIV_MAX               (USART_CLK_DIV64)
/**
 * @}
 */

/**
 * @defgroup USART_Default_Baudrate USART Default Baudrate
 * @{
 */
#define USART_DEFAULT_BAUDRATE          (9600UL)
/**
 * @}
 */

#define USART_RMU_TIMEOUT               (100U)

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup USART_Local_Functions USART Local Functions
 * @{
 */
/**
 * @brief  Try to wait the expected status of specified flags
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32Flag                 USART flag
 *         This parameter can be a value of @ref USART_Flag
 * @param  [in] enStatus                Expected status
 *         This parameter can be one of the following values:
 *           @arg  SET:                 Wait flag set
 *           @arg  RESET:               Wait flag reset
 * @param  [in] u32Timeout              Maximum count(Max value @ref USART_Max_Timeout) of trying to get status
 * @retval int32_t:
 *           - LL_OK:                   Complete wait the expected status of the specified flags.
 *           - LL_ERR_TIMEOUT:          Wait timeout.
 * @note Block checking flag if u32Timeout value is USART_MAX_TIMEOUT.
 */
static int32_t USART_WaitStatus(const CM_USART_TypeDef *USARTx,
                                uint32_t u32Flag,
                                en_flag_status_t enStatus,
                                uint32_t u32Timeout)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32To = 0UL;

    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_FLAG(u32Flag));

    while (USART_GetStatus(USARTx, u32Flag) != enStatus) {
        /* Block checking flag if timeout value is USART_TIMEOUT_MAX */
        if ((u32To > u32Timeout) && (u32Timeout < USART_MAX_TIMEOUT)) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }

        u32To++;
    }

    return i32Ret;
}

/**
 * @brief  Calculate baudrate division for UART mode.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] pstcUartBrr             Pointer to a stc_usart_brr_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Set successfully.
 *           - LL_ERR:                  Set unsuccessfully.
 */
static int32_t UART_CalculateBrr(const CM_USART_TypeDef *USARTx, stc_usart_brr_t *pstcUartBrr)
{
    uint32_t B;
    uint32_t C;
    uint32_t OVER8;
    uint64_t u64Temp;
    uint64_t u64Temp0;
    uint64_t u64Dividend;
    uint32_t DIV_Integer;
    uint32_t DIV_IntegerMod;
    uint32_t DIV_Fraction;
    float32_t f32CalcError;
    uint32_t u32FractionFlag = 1UL;
    int32_t i32Ret = LL_ERR;

    DDL_ASSERT(IS_USART_UNIT(USARTx));
    C = pstcUartBrr->u32UsartClock;
    B = pstcUartBrr->u32Baudrate;
    if ((C > 0UL) && (B > 0UL)) {
        OVER8 = READ_REG32_BIT(USARTx->CR1, USART_CR1_OVER8) >> USART_CR1_OVER8_POS;

        /* UART mode baudrate integer calculation formula:      */
        /*      B = C / (8 * (2 - OVER8) * (DIV_Integer + 1))   */
        /*      DIV_Integer = (C / (B * 8 * (2 - OVER8))) - 1   */
        DIV_Integer = (C / (B * 8UL * (2UL - OVER8))) - 1U;
        if (DIV_Integer <= USART_BRR_DIV_INTEGER_MAX) {
            pstcUartBrr->u32Integer = DIV_Integer;
            DIV_IntegerMod = C % (B * 8UL * (2UL - OVER8));
            if (0UL == DIV_IntegerMod) {
                /* Get accurate baudrate without fraction */
                pstcUartBrr->f32Error = (float32_t)0.0F;
                i32Ret = LL_OK;
            } else {
                /* UART mode baudrate fraction calculation formula:                                 */
                /*      B = C * (128 + DIV_Fraction) / (8 * (2 - OVER8) * (DIV_Integer + 1) * 256)  */
                /*      DIV_Fraction = (256 * (8 * (2 - OVER8) * (DIV_Integer + 1) * B) / C) - 128  */
                /* u64Temp = (8 * (2 - OVER8) * (DIV_Integer + 1) * B)  */
                u64Temp0 = (uint64_t)((uint64_t)8UL * ((uint64_t)2UL - (uint64_t)OVER8) * \
                                      ((uint64_t)DIV_Integer + (uint64_t)1UL) * (uint64_t)B);

                /* u64Temp = u64Temp0 *256 + C/2 */
                u64Temp0 = (u64Temp0 << 8UL);
                u64Temp = u64Temp0 + ((uint64_t)C >> 1);    /*  +(C >> 1) for rounding off */
                if (u64Temp > (uint64_t)(UINT32_MAX)) {
                    DIV_Fraction = (uint32_t)(u64Temp / C) - 128UL;
                } else {
                    DIV_Fraction = ((uint32_t)u64Temp) / C - 128UL;
                }
                if (DIV_Fraction <= USART_BRR_DIV_FRACTION_MAX) {
                    pstcUartBrr->u32Fraction = DIV_Fraction;
                    /* E(%) = C * (128 + DIV_Fraction) / (256 * (8 * (2 - OVER8) * (DIV_Integer + 1) * B)) - 1 */
                    u64Temp = u64Temp0;
                    u64Dividend = (uint64_t)C * ((uint64_t)128UL + (uint64_t)DIV_Fraction);
                    f32CalcError = (float32_t)((float64_t)(u64Dividend) / (float64_t)(u64Temp)) - 1.0F;
                    pstcUartBrr->f32Error = f32CalcError;
                    i32Ret = LL_OK;
                } else {
                    u32FractionFlag = 0UL;
                }
            }
        }
        if (0UL == u32FractionFlag) {
            /* Integer rounding off */
            DIV_Integer = ((((C * 10UL) / (B * 8UL * (2UL - OVER8))) + 5UL) / 10UL) - 1UL; /*  +5UL for rounding off */
            if (DIV_Integer <= USART_BRR_DIV_INTEGER_MAX) {
                pstcUartBrr->u32Integer = DIV_Integer;
                /* E(%) = C / (8 * (2 - OVER8) * (DIV_Integer + 1) * B) - 1 */
                /* u64Temp = (8 * (2 - OVER8) * (DIV_Integer + 1) * B)  */
                u64Temp = (uint64_t)((uint64_t)8UL * ((uint64_t)2UL - (uint64_t)OVER8) * ((uint64_t)DIV_Integer + \
                                                                                          (uint64_t)1UL) * (uint64_t)B);
                f32CalcError = (float32_t)((float64_t)C / (float64_t)u64Temp) - 1.0F;
                pstcUartBrr->f32Error = f32CalcError;
                i32Ret = LL_OK;
            }
        }
    }
    return i32Ret;
}

/**
 * @brief  Calculate baudrate division for UART mode.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] pstcClockSyncBrr        Pointer to a stc_usart_brr_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Set successfully.
 *           - LL_ERR:                  Set unsuccessfully.
 */
static int32_t ClockSync_CalculateBrr(const CM_USART_TypeDef *USARTx, stc_usart_brr_t *pstcClockSyncBrr)
{
    uint32_t B;
    uint32_t C;
    uint64_t u64Temp;
    uint64_t u64Dividend;
    uint32_t DIV_Integer;
    uint32_t DIV_IntegerMod;
    uint32_t DIV_Fraction;
    float32_t f32CalcError;
    uint32_t u32FractionFlag = 1UL;
    int32_t i32Ret = LL_ERR;

    DDL_ASSERT(IS_USART_UNIT(USARTx));

    C = pstcClockSyncBrr->u32UsartClock;
    B = pstcClockSyncBrr->u32Baudrate;
    if ((C > 0UL) && (B > 0UL)) {
        /* Clock sync mode baudrate integer calculation formula:    */
        /*          B = C / (4 * (DIV_Integer + 1))                 */
        /*          DIV_Integer = (C / (B * 4)) - 1                 */
        DIV_Integer = (C / (B * 4UL)) - 1UL;
        if (DIV_Integer <= USART_BRR_DIV_INTEGER_MAX) {
            pstcClockSyncBrr->u32Integer = DIV_Integer;
            DIV_IntegerMod = C % (B * 4UL);
            if (0UL == DIV_IntegerMod) {
                /* Get accurate baudrate without fraction */
                pstcClockSyncBrr->f32Error = (float32_t)0.0F;
                i32Ret = LL_OK;
            } else {
                /* Clock sync mode baudrate fraction calculation formula:               */
                /*      B = C * (128 + DIV_Fraction) / (4 * (DIV_Integer + 1) * 256)    */
                /*      DIV_Fraction = 256 * (4 * (DIV_Integer + 1) * B) / C - 128       */

                /* u64Temp = (4 * (DIV_Integer + 1) * B)  */
                u64Temp = (uint64_t)((uint64_t)4U * ((uint64_t)DIV_Integer + (uint64_t)1UL) * (uint64_t)B);
                DIV_Fraction = (uint32_t)((256UL * u64Temp + ((uint64_t)C >> 1)) / C - 128UL);  /*  +(C >> 1) for rounding off */
                if (DIV_Fraction <= USART_BRR_DIV_FRACTION_MAX) {
                    pstcClockSyncBrr->u32Fraction = DIV_Fraction;
                    /* E(%) = C * (128 + DIV_Fraction) / (4 * (DIV_Integer + 1) * B * 256) - 1 */
                    u64Temp *= (uint64_t)256UL;
                    u64Dividend = (uint64_t)C * ((uint64_t)128UL + (uint64_t)DIV_Fraction);
                    f32CalcError = (float32_t)((float64_t)(u64Dividend) / (float64_t)(u64Temp)) - 1.0F;
                    pstcClockSyncBrr->f32Error = f32CalcError;
                    i32Ret = LL_OK;
                } else {
                    u32FractionFlag = 0UL;
                }
            }
        }
        if (0UL == u32FractionFlag) {
            /* Integer rounding off */
            DIV_Integer = ((((C * 10UL) / (B * 4UL)) + 5UL) / 10UL) - 1UL; /*  +5UL for rounding off */
            if (DIV_Integer <= USART_BRR_DIV_INTEGER_MAX) {
                pstcClockSyncBrr->u32Integer = DIV_Integer;
                /* E(%) = C / (4 * (DIV_Integer + 1) * B) - 1 */
                /* u64Temp = 4 * (DIV_Integer + 1) * B */
                u64Temp = (uint64_t)((uint64_t)4U * ((uint64_t)DIV_Integer + (uint64_t)1UL) * (uint64_t)B);
                f32CalcError = (float32_t)((float64_t)C / (float64_t)u64Temp) - 1.0F;
                pstcClockSyncBrr->f32Error = f32CalcError;
                i32Ret = LL_OK;
            }
        }
    }
    return i32Ret;
}

/**
 * @brief  Calculate baudrate division for UART mode.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] pstcSmartCardBrr            Pointer to a stc_usart_brr_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Set successfully.
 *           - LL_ERR:                  Set unsuccessfully.
 */
static int32_t SmartCard_CalculateBrr(const CM_USART_TypeDef *USARTx, stc_usart_brr_t *pstcSmartCardBrr)
{
    uint32_t B;
    uint32_t C;
    uint32_t BCN;
    uint64_t u64Temp;
    uint64_t u64Dividend;
    uint32_t DIV_Integer;
    uint32_t DIV_IntegerMod;
    uint32_t DIV_Fraction;
    float32_t f32CalcError;
    const uint16_t au16EtuClkCnts[] = {32U, 64U, 93U, 128U, 186U, 256U, 372U, 512U};
    int32_t i32Ret = LL_ERR;

    DDL_ASSERT(IS_USART_SMARTCARD_UNIT(USARTx));

    C = pstcSmartCardBrr->u32UsartClock;
    B = pstcSmartCardBrr->u32Baudrate;
    if ((C > 0UL) && (B > 0UL)) {
        BCN = READ_REG32_BIT(USARTx->CR3, USART_CR3_BCN);
        DDL_ASSERT(IS_USART_SMARTCARD_ETU_CLK(BCN));
        BCN = au16EtuClkCnts[BCN >> USART_CR3_BCN_POS];
        /* Smartcard mode baudrate integer calculation formula: */
        /*      B = C / (2 * BCN * (DIV_Integer + 1))           */
        /*      DIV_Integer = (C / (B * 2 * BCN)) - 1           */
        DIV_Integer = (C / (B * BCN * 2UL)) - 1UL;
        if (DIV_Integer <= USART_BRR_DIV_INTEGER_MAX) {
            pstcSmartCardBrr->u32Integer = DIV_Integer;
            DIV_IntegerMod = C % (B * BCN * 2UL);
            if (0UL == DIV_IntegerMod) {
                /* Get accurate baudrate without fraction */
                pstcSmartCardBrr->f32Error = (float32_t)0.0F;
                i32Ret = LL_OK;
            } else {
                /* Smartcard mode baudrate fraction calculation formula:                        */
                /*      B = C * (128 + DIV_Fraction) / ((2 * BCN) * (DIV_Integer + 1) * 256)    */
                /*      DIV_Fraction = (256 * (2 * BCN * (DIV_Integer + 1) * B) / C) - 128      */

                /* u64Temp = (2 * BCN * (DIV_Integer + 1) * B)  */
                u64Temp = (uint64_t)((uint64_t)2UL * BCN * ((uint64_t)DIV_Integer + (uint64_t)1UL) * B);
                DIV_Fraction = (uint32_t)((256UL * u64Temp + ((uint64_t)C >> 1)) / C - 128UL);  /*  +(C >> 1) for rounding off */
                if (DIV_Fraction <= USART_BRR_DIV_FRACTION_MAX) {
                    pstcSmartCardBrr->u32Fraction = DIV_Fraction;
                    /* E(%) = C * (128 + DIV_Fraction) / (4 * (DIV_Integer + 1) * B * 256) - 1 */
                    u64Temp *= (uint64_t)256UL;
                    u64Dividend = (uint64_t)C * ((uint64_t)128UL + (uint64_t)DIV_Fraction);
                    f32CalcError = (float32_t)((float64_t)u64Dividend / (float64_t)(u64Temp)) - 1.0F;
                    pstcSmartCardBrr->f32Error = f32CalcError;
                    i32Ret = LL_OK;
                }
            }
        }
        if (LL_ERR == i32Ret) {
            /* Integer rounding off */
            DIV_Integer = (((C * 10UL) / (B * BCN * 2UL) + 5UL) / 10UL) - 1UL; /*  +5UL for rounding off */
            if (DIV_Integer <= USART_BRR_DIV_INTEGER_MAX) {
                pstcSmartCardBrr->u32Integer = DIV_Integer;
                /* E(%) = C / (2 * BCN * (DIV_Integer + 1) * B) - 1 */
                /* u64Temp = 4 * (DIV_Integer + 1) * B */
                u64Temp = (uint64_t)((uint64_t)2UL * BCN * ((uint64_t)DIV_Integer + (uint64_t)1UL) * B);
                f32CalcError = (float32_t)((float64_t)C / (float64_t)u64Temp) - 1.0F;
                pstcSmartCardBrr->f32Error = f32CalcError;
                i32Ret = LL_OK;
            }
        }
    }
    return i32Ret;
}

/**
 * @brief  Get bus(which USART mounts on) clock frequency value.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @retval USART clock frequency value
 */
static uint32_t USART_GetBusClockFreq(const CM_USART_TypeDef *USARTx)
{
    uint32_t u32BusClock;

    (void)USARTx;

    u32BusClock = SystemCoreClock >> (READ_REG32_BIT(CM_CMU->SCFGR, CMU_SCFGR_PCLK1S) >> CMU_SCFGR_PCLK1S_POS);

    return u32BusClock;
}

/**
 * @brief  Get USART clock frequency value.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @retval USART clock frequency value
 */
static uint32_t USART_GetUsartClockFreq(const CM_USART_TypeDef *USARTx)
{
    uint32_t u32BusClock;
    uint32_t u32UsartClockDiv;
    uint32_t u32UsartClock;

    DDL_ASSERT(IS_USART_UNIT(USARTx));

    u32BusClock = USART_GetBusClockFreq(USARTx);

    u32UsartClockDiv = (1UL << (READ_REG32_BIT(USARTx->PR, USART_PR_PSC) * 2UL));

    u32UsartClock = u32BusClock / u32UsartClockDiv;
    return u32UsartClock;
}

/**
 * @brief  Get USART BMC clock frequency value.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @retval USART BMC clock frequency value
 */
static uint32_t USART_GetLinBmcClockFreq(const CM_USART_TypeDef *USARTx)
{
    uint32_t u32BusClock;
    uint32_t u32UsartBmcDiv;
    uint32_t u32UsartBmcClock;

    DDL_ASSERT(IS_USART_LIN_UNIT(USARTx));

    u32BusClock = USART_GetBusClockFreq(USARTx);
    u32UsartBmcDiv = (1UL << (READ_REG32_BIT((USARTx)->PR, USART_PR_LBMPSC) >> USART_PR_LBMPSC_POS));

    u32UsartBmcClock = u32BusClock / u32UsartBmcDiv;
    return u32UsartBmcClock;
}

/**
 * @}
 */

/**
 * @defgroup USART_Global_Functions USART Global Functions
 * @{
 */

/**
 * @brief  Set the fields of structure stc_usart_clocksync_init_t to default values.
 * @param  [out] pstcClockSyncInit      Pointer to a @ref stc_usart_clocksync_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcClockSyncInit value is NULL.
 */
int32_t USART_ClockSync_StructInit(stc_usart_clocksync_init_t *pstcClockSyncInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcClockSyncInit) {
        pstcClockSyncInit->u32ClockSrc = USART_CLK_SRC_INTERNCLK;
        pstcClockSyncInit->u32ClockDiv = USART_CLK_DIV1;
        pstcClockSyncInit->u32Baudrate = USART_DEFAULT_BAUDRATE;
        pstcClockSyncInit->u32FirstBit = USART_FIRST_BIT_LSB;
        pstcClockSyncInit->u32HWFlowControl = USART_HW_FLOWCTRL_RTS;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize clock synchronization function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] pstcClockSyncInit       Pointer to a @ref stc_usart_clocksync_init_t structure.
 * @param  [out] pf32Error              E(%) baudrate error rate
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcClockSyncInit value is NULL or baudrate set unsuccessfully.
 */
int32_t USART_ClockSync_Init(CM_USART_TypeDef *USARTx,
                             const stc_usart_clocksync_init_t *pstcClockSyncInit, float32_t *pf32Error)
{
    uint32_t u32CR1Value;
    uint32_t u32CR2Value;
    uint32_t u32CR3Value;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcClockSyncInit) {
        DDL_ASSERT(IS_USART_UNIT(USARTx));
        DDL_ASSERT(IS_USART_CLK_SRC(pstcClockSyncInit->u32ClockSrc));
        DDL_ASSERT(IS_USART_FIRST_BIT(pstcClockSyncInit->u32FirstBit));
        DDL_ASSERT(IS_USART_HW_FLOWCTRL(pstcClockSyncInit->u32HWFlowControl));

        u32CR1Value = (pstcClockSyncInit->u32FirstBit | USART_CR1_MS | USART_CR1_SBS);
        u32CR2Value = (pstcClockSyncInit->u32ClockSrc | USART_CR2_RST_VALUE);
        if (USART_CLK_SRC_INTERNCLK == pstcClockSyncInit->u32ClockSrc) {
            u32CR2Value |= USART_CK_OUTPUT_ENABLE;
        }
        u32CR3Value = pstcClockSyncInit->u32HWFlowControl;

        /* Set control register: CR1/CR2/CR3 */
        WRITE_REG32(USARTx->CR1, u32CR1Value);
        WRITE_REG32(USARTx->CR2, u32CR2Value);
        WRITE_REG32(USARTx->CR3, u32CR3Value);

        if (USART_CLK_SRC_INTERNCLK == pstcClockSyncInit->u32ClockSrc) {
            DDL_ASSERT(IS_USART_CLK_DIV(pstcClockSyncInit->u32ClockDiv));

            /* Set prescaler register register: PR */
            WRITE_REG32(USARTx->PR, pstcClockSyncInit->u32ClockDiv);

            /* Set baudrate */
            i32Ret = USART_SetBaudrate(USARTx, pstcClockSyncInit->u32Baudrate, pf32Error);
        } else {
            i32Ret = LL_OK;
        }
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_usart_multiprocessor_init_t to default values.
 * @param  [out] pstcMultiProcessorInit Pointer to a @ref stc_usart_multiprocessor_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcMultiProcessorInit value is NULL.
 */
int32_t USART_MultiProcessor_StructInit(stc_usart_multiprocessor_init_t *pstcMultiProcessorInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcMultiProcessorInit) {
        pstcMultiProcessorInit->u32ClockSrc = USART_CLK_SRC_INTERNCLK;
        pstcMultiProcessorInit->u32ClockDiv = USART_CLK_DIV1;
        pstcMultiProcessorInit->u32CKOutput = USART_CK_OUTPUT_DISABLE;
        pstcMultiProcessorInit->u32Baudrate = USART_DEFAULT_BAUDRATE;
        pstcMultiProcessorInit->u32DataWidth = USART_DATA_WIDTH_8BIT;
        pstcMultiProcessorInit->u32StopBit = USART_STOPBIT_1BIT;
        pstcMultiProcessorInit->u32OverSampleBit = USART_OVER_SAMPLE_16BIT;
        pstcMultiProcessorInit->u32FirstBit = USART_FIRST_BIT_LSB;
        pstcMultiProcessorInit->u32StartBitPolarity = USART_START_BIT_FALLING;
        pstcMultiProcessorInit->u32HWFlowControl = USART_HW_FLOWCTRL_RTS;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize UART multiple processor function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] pstcMultiProcessorInit  Pointer to a @ref stc_usart_multiprocessor_init_t structure.
 * @param  [out] pf32Error              E(%) baudrate error rate
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcMxProcessorInit value is NULL or baudrate set unsuccessfully.
 */
int32_t USART_MultiProcessor_Init(CM_USART_TypeDef *USARTx,
                                  const stc_usart_multiprocessor_init_t *pstcMultiProcessorInit, float32_t *pf32Error)
{
    uint32_t u32CR1Value;
    uint32_t u32CR2Value;
    uint32_t u32CR3Value;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcMultiProcessorInit) {
        DDL_ASSERT(IS_USART_UNIT(USARTx));
        DDL_ASSERT(IS_USART_CLK_SRC(pstcMultiProcessorInit->u32ClockSrc));
        DDL_ASSERT(IS_USART_CK_OUTPUT(pstcMultiProcessorInit->u32CKOutput));
        DDL_ASSERT(IS_USART_DATA_WIDTH(pstcMultiProcessorInit->u32DataWidth));
        DDL_ASSERT(IS_USART_STOPBIT(pstcMultiProcessorInit->u32StopBit));
        DDL_ASSERT(IS_USART_OVER_SAMPLE_BIT(pstcMultiProcessorInit->u32OverSampleBit));
        DDL_ASSERT(IS_USART_FIRST_BIT(pstcMultiProcessorInit->u32FirstBit));
        DDL_ASSERT(IS_USART_START_BIT_POLARITY(pstcMultiProcessorInit->u32StartBitPolarity));
        DDL_ASSERT(IS_USART_HW_FLOWCTRL(pstcMultiProcessorInit->u32HWFlowControl));

        u32CR1Value = (pstcMultiProcessorInit->u32DataWidth | pstcMultiProcessorInit->u32OverSampleBit | \
                       pstcMultiProcessorInit->u32FirstBit  | pstcMultiProcessorInit->u32StartBitPolarity);
        u32CR2Value = (USART_CR2_RST_VALUE | USART_CR2_MPE | pstcMultiProcessorInit->u32ClockSrc | \
                       pstcMultiProcessorInit->u32CKOutput | pstcMultiProcessorInit->u32StopBit);
        u32CR3Value = pstcMultiProcessorInit->u32HWFlowControl;

        /* Set control register: CR1/CR2/CR3 */
        WRITE_REG32(USARTx->CR1, u32CR1Value);
        WRITE_REG32(USARTx->CR2, u32CR2Value);
        WRITE_REG32(USARTx->CR3, u32CR3Value);

        if (USART_CLK_SRC_INTERNCLK == pstcMultiProcessorInit->u32ClockSrc) {
            DDL_ASSERT(IS_USART_CLK_DIV(pstcMultiProcessorInit->u32ClockDiv));

            /* Set prescaler register register: PR */
            WRITE_REG32(USARTx->PR, pstcMultiProcessorInit->u32ClockDiv);

            /* Set baudrate */
            i32Ret = USART_SetBaudrate(USARTx, pstcMultiProcessorInit->u32Baudrate, pf32Error);
        } else {
            i32Ret = LL_OK;
        }
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_usart_uart_init_t to default values.
 * @param  [out] pstcUartInit           Pointer to a @ref stc_usart_uart_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcUartInit value is NULL.
 */
int32_t USART_UART_StructInit(stc_usart_uart_init_t *pstcUartInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcUartInit) {
        pstcUartInit->u32ClockSrc = USART_CLK_SRC_INTERNCLK;
        pstcUartInit->u32ClockDiv = USART_CLK_DIV1;
        pstcUartInit->u32CKOutput = USART_CK_OUTPUT_DISABLE;
        pstcUartInit->u32Baudrate = USART_DEFAULT_BAUDRATE;
        pstcUartInit->u32DataWidth = USART_DATA_WIDTH_8BIT;
        pstcUartInit->u32StopBit = USART_STOPBIT_1BIT;
        pstcUartInit->u32Parity = USART_PARITY_NONE;
        pstcUartInit->u32OverSampleBit = USART_OVER_SAMPLE_16BIT;
        pstcUartInit->u32FirstBit = USART_FIRST_BIT_LSB;
        pstcUartInit->u32StartBitPolarity = USART_START_BIT_FALLING;
        pstcUartInit->u32HWFlowControl = USART_HW_FLOWCTRL_RTS;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize UART function.
 * @param  [in]  USARTx                 Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in]  pstcUartInit           Pointer to a @ref stc_usart_uart_init_t structure.
 * @param  [out] pf32Error              E(%) baudrate error rate
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcUartInit value is NULL or baudrate set unsuccessfully.
 */
int32_t USART_UART_Init(CM_USART_TypeDef *USARTx, const stc_usart_uart_init_t *pstcUartInit, float32_t *pf32Error)
{
    uint32_t u32CR1Value;
    uint32_t u32CR2Value;
    uint32_t u32CR3Value;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcUartInit) {
        DDL_ASSERT(IS_USART_UNIT(USARTx));
        DDL_ASSERT(IS_USART_CLK_SRC(pstcUartInit->u32ClockSrc));
        DDL_ASSERT(IS_USART_CK_OUTPUT(pstcUartInit->u32CKOutput));
        DDL_ASSERT(IS_USART_PARITY(pstcUartInit->u32Parity));
        DDL_ASSERT(IS_USART_DATA_WIDTH(pstcUartInit->u32DataWidth));
        DDL_ASSERT(IS_USART_STOPBIT(pstcUartInit->u32StopBit));
        DDL_ASSERT(IS_USART_OVER_SAMPLE_BIT(pstcUartInit->u32OverSampleBit));
        DDL_ASSERT(IS_USART_FIRST_BIT(pstcUartInit->u32FirstBit));
        DDL_ASSERT(IS_USART_START_BIT_POLARITY(pstcUartInit->u32StartBitPolarity));
        DDL_ASSERT(IS_USART_HW_FLOWCTRL(pstcUartInit->u32HWFlowControl));

        u32CR1Value = (pstcUartInit->u32Parity | pstcUartInit->u32DataWidth | pstcUartInit->u32FirstBit | \
                       pstcUartInit->u32OverSampleBit | pstcUartInit->u32StartBitPolarity);
        u32CR2Value = (USART_CR2_RST_VALUE | pstcUartInit->u32ClockSrc | \
                       pstcUartInit->u32CKOutput | pstcUartInit->u32StopBit);
        u32CR3Value = pstcUartInit->u32HWFlowControl;

        /* Set control register: CR1/CR2/CR3 */
        WRITE_REG32(USARTx->CR1, u32CR1Value);
        WRITE_REG32(USARTx->CR2, u32CR2Value);
        WRITE_REG32(USARTx->CR3, u32CR3Value);

        if (USART_CLK_SRC_INTERNCLK == pstcUartInit->u32ClockSrc) {
            DDL_ASSERT(IS_USART_CLK_DIV(pstcUartInit->u32ClockDiv));

            /* Set prescaler register register: PR */
            WRITE_REG32(USARTx->PR, pstcUartInit->u32ClockDiv);

            /* Set baudrate */
            i32Ret = USART_SetBaudrate(USARTx, pstcUartInit->u32Baudrate, pf32Error);
        } else {
            i32Ret = LL_OK;
        }
    }

    return i32Ret;
}

/**
 * @brief  Initialize UART half duplex function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] pstcUartInit            Pointer to a @ref stc_usart_uart_init_t structure.
 * @param  [out] pf32Error              E(%) baudrate error rate
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcUartInit value is NULL or baudrate set unsuccessfully.
 */
int32_t USART_HalfDuplex_Init(CM_USART_TypeDef *USARTx,
                              const stc_usart_uart_init_t *pstcUartInit, float32_t *pf32Error)
{
    int32_t i32Ret;

    i32Ret = USART_UART_Init(USARTx, pstcUartInit, pf32Error);
    if (LL_OK == i32Ret) {
        /* Set CR3: UART half duplex */
        SET_REG32_BIT(USARTx->CR3, USART_CR3_HDSEL);
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_usart_lin_init_t to default values.
 * @param  [out] pstcLinInit            Pointer to a @ref stc_usart_lin_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcLinInit is NULL.
 */
int32_t USART_LIN_StructInit(stc_usart_lin_init_t *pstcLinInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcLinInit) {
        pstcLinInit->u32ClockSrc = USART_CLK_SRC_INTERNCLK;
        pstcLinInit->u32ClockDiv = USART_CLK_DIV1;
        pstcLinInit->u32CKOutput = USART_CK_OUTPUT_DISABLE;
        pstcLinInit->u32Baudrate = USART_DEFAULT_BAUDRATE;
        pstcLinInit->u32OverSampleBit = USART_OVER_SAMPLE_16BIT;
        pstcLinInit->u32BmcClockDiv = USART_LIN_BMC_CLK_DIV1;
        pstcLinInit->u32DetectBreakLen = USART_LIN_DETECT_BREAK_10BIT;
        pstcLinInit->u32SendBreakLen = USART_LIN_SEND_BREAK_10BIT;
        pstcLinInit->u32SendBreakMode = USART_LIN_SEND_BREAK_MD_SBK;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize LIN function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] pstcLinInit             Pointer to a @ref stc_usart_lin_init_t structure.
 * @param  [out] pf32Error              E(%) baudrate error rate
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcLinInit value is NULL or baudrate set unsuccessfully.
 */
int32_t USART_LIN_Init(CM_USART_TypeDef *USARTx, const stc_usart_lin_init_t *pstcLinInit, float32_t *pf32Error)
{
    uint32_t u32CR1Value;
    uint32_t u32CR2Value;
    uint32_t u32PRValue;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcLinInit) {
        DDL_ASSERT(IS_USART_LIN_UNIT(USARTx));
        DDL_ASSERT(IS_USART_CLK_SRC(pstcLinInit->u32ClockSrc));
        DDL_ASSERT(IS_USART_CK_OUTPUT(pstcLinInit->u32CKOutput));
        DDL_ASSERT(IS_USART_CLK_DIV(pstcLinInit->u32ClockDiv));
        DDL_ASSERT(IS_USART_OVER_SAMPLE_BIT(pstcLinInit->u32OverSampleBit));

        u32CR1Value = (pstcLinInit->u32OverSampleBit | USART_CR1_SBS);
        u32CR2Value = (pstcLinInit->u32ClockSrc | pstcLinInit->u32CKOutput | USART_CR2_LINEN | USART_CR2_RST_VALUE);

        DDL_ASSERT(IS_USART_LIN_DETECT_BREAK_LEN(pstcLinInit->u32DetectBreakLen));
        DDL_ASSERT(IS_USART_LIN_SEND_BREAK_LEN(pstcLinInit->u32SendBreakLen));
        DDL_ASSERT(IS_USART_LIN_SEND_BREAK_MD(pstcLinInit->u32SendBreakMode));
        u32CR2Value |= (pstcLinInit->u32DetectBreakLen | pstcLinInit->u32SendBreakLen | pstcLinInit->u32SendBreakMode);

        /* Set control register: CR1/CR2/CR3 */
        WRITE_REG32(USARTx->CR1, u32CR1Value);
        WRITE_REG32(USARTx->CR2, u32CR2Value);
        WRITE_REG32(USARTx->CR3, 0UL);

        if (USART_CLK_SRC_INTERNCLK == pstcLinInit->u32ClockSrc) {
            DDL_ASSERT(IS_USART_CLK_DIV(pstcLinInit->u32ClockDiv));
            u32PRValue = pstcLinInit->u32ClockDiv;

            DDL_ASSERT(IS_USART_LIN_BMC_CLK_DIV(pstcLinInit->u32BmcClockDiv));
            u32PRValue |= pstcLinInit->u32BmcClockDiv;

            /* Set prescaler register register: PR */
            WRITE_REG32(USARTx->PR, u32PRValue);

            /* Set baudrate */
            i32Ret = USART_SetBaudrate(USARTx, pstcLinInit->u32Baudrate, pf32Error);
        } else {
            i32Ret = LL_OK;
        }
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_usart_smartcard_init_t to default values.
 * @param  [out] pstcSmartCardInit      Pointer to a @ref stc_usart_smartcard_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcSmartCardInit value is NULL.
 */
int32_t USART_SmartCard_StructInit(stc_usart_smartcard_init_t *pstcSmartCardInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcSmartCardInit) {
        pstcSmartCardInit->u32ClockDiv = USART_CLK_DIV1;
        pstcSmartCardInit->u32CKOutput = USART_CK_OUTPUT_DISABLE;
        pstcSmartCardInit->u32Baudrate = USART_DEFAULT_BAUDRATE;
        pstcSmartCardInit->u32FirstBit = USART_FIRST_BIT_LSB;
        i32Ret = LL_OK;
    }

    return i32Ret;
}
/**
 * @brief  Initialize smartcard function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] pstcSmartCardInit       Pointer to a @ref stc_usart_smartcard_init_t structure.
 * @param  [out] pf32Error              E(%) baudrate error rate
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcSmartCardInit value is NULL or baudrate set unsuccessfully.
 */
int32_t USART_SmartCard_Init(CM_USART_TypeDef *USARTx,
                             const stc_usart_smartcard_init_t *pstcSmartCardInit, float32_t *pf32Error)
{
    uint32_t u32CR1Value;
    uint32_t u32CR2Value;
    uint32_t u32CR3Value;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcSmartCardInit) {
        DDL_ASSERT(IS_USART_SMARTCARD_UNIT(USARTx));
        DDL_ASSERT(IS_USART_CK_OUTPUT(pstcSmartCardInit->u32CKOutput));
        DDL_ASSERT(IS_USART_CLK_DIV(pstcSmartCardInit->u32ClockDiv));
        DDL_ASSERT(IS_USART_FIRST_BIT(pstcSmartCardInit->u32FirstBit));

        u32CR1Value = (pstcSmartCardInit->u32FirstBit | USART_CR1_PCE | USART_CR1_SBS);
        u32CR2Value = (pstcSmartCardInit->u32CKOutput | USART_CR2_RST_VALUE);
        u32CR3Value = USART_CR3_SCEN | USART_SC_ETU_CLK372;

        /* Set control register: CR1/CR2/CR3 */
        WRITE_REG32(USARTx->CR1, u32CR1Value);
        WRITE_REG32(USARTx->CR2, u32CR2Value);
        WRITE_REG32(USARTx->CR3, u32CR3Value);

        /* Set prescaler register register: PR */
        WRITE_REG32(USARTx->PR, pstcSmartCardInit->u32ClockDiv);

        /* Set baudrate */
        i32Ret = USART_SetBaudrate(USARTx, pstcSmartCardInit->u32Baudrate, pf32Error);
    }

    return i32Ret;
}

/**
 * @brief  De-Initialize USART function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @retval int32_t:
 *           - LL_OK:           Reset success.
 *           - LL_ERR_TIMEOUT:  Reset time out.
 * @note   Call LL_PERIPH_WE(LL_PERIPH_PWC_CLK_RMU) unlock RMU_FRSTx register first.
 */
int32_t USART_DeInit(CM_USART_TypeDef *USARTx)
{
    uint32_t i;
    int32_t i32Ret = LL_OK;
    __IO uint8_t u8TimeOut = 0U;
    __IO uint32_t *bCM_RMU_FRST3_USARTx = NULL;
    const uint32_t au32USARTx[] = {CM_USART1_BASE, CM_USART2_BASE, CM_USART3_BASE, \
                                   CM_USART4_BASE, CM_USART5_BASE, CM_USART6_BASE
                                  };

    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1);

    for (i = 0UL; i < ARRAY_SZ(au32USARTx); i++) {
        if ((uint32_t)USARTx == au32USARTx[i]) {
            bCM_RMU_FRST3_USARTx = (__IO uint32_t *)((uint32_t)&bCM_RMU->FRST3_b.USART1 + (i << 2));
            break;
        }
    }

    /* Reset USART */
    WRITE_REG32(*bCM_RMU_FRST3_USARTx, 0UL);

    /* Ensure reset procedure is completed */
    while (READ_REG32(*bCM_RMU_FRST3_USARTx) != 1UL) {
        u8TimeOut++;
        if (u8TimeOut > USART_RMU_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable/disable USART Transmit/Receive Function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32Func                 USART function type
 *         This parameter can be any composed value of the macros group @ref USART_Function.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 * @note   In clock synchronization mode, the bit TE or RE of register USART_CR can only be
 *         written to 1 when TE = 0 and RE = 0 (transmit and receive disabled)
 */
void USART_FuncCmd(CM_USART_TypeDef *USARTx, uint32_t u32Func, en_functional_state_t enNewState)
{
    uint32_t u32BaseFunc;
    uint32_t u32LinFunc;

    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_USART_FUNC(u32Func));
    DDL_ASSERT(IS_USART_LIN_FUNC(USARTx, u32Func));
    DDL_ASSERT(IS_USART_TIMEOUT_FUNC(USARTx, u32Func));

    u32BaseFunc = (u32Func & 0xFFFFUL);
    if (u32BaseFunc > 0UL) {
        (ENABLE == enNewState) ? SET_REG32_BIT(USARTx->CR1, u32BaseFunc) : CLR_REG32_BIT(USARTx->CR1, u32BaseFunc);
    }

    u32LinFunc = ((u32Func & USART_LIN_FUNC_MASK) >> USART_LIN_FUNC_OFFSET);
    if (u32LinFunc > 0UL) {
        (ENABLE == enNewState) ? SET_REG32_BIT(USARTx->CR2, u32LinFunc) : CLR_REG32_BIT(USARTx->CR2, u32LinFunc);
    }
}

/**
 * @brief  Enable/disable USART Transmit/Receive Function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32Func                 USART function type
 *         This parameter can be any composed value of the macros group @ref USART_Function.
 * @retval An @ref en_functional_state_t enumeration value.
 *           - ENABLE: DVP capture started
 *           - DISABLE: DVP capture stopped
 * @note   In clock synchronization mode, the bit TE or RE of register USART_CR can only be
 *         written to 1 when TE = 0 and RE = 0 (transmit and receive disabled)
 */
en_functional_state_t USART_GetFuncState(CM_USART_TypeDef *USARTx, uint32_t u32Func)
{
    uint32_t u32BaseFunc;
    en_functional_state_t enNewState = DISABLE;

    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_FUNC(u32Func));
    DDL_ASSERT(IS_USART_LIN_FUNC(USARTx, u32Func));
    DDL_ASSERT(IS_USART_TIMEOUT_FUNC(USARTx, u32Func));

    u32BaseFunc = (u32Func & 0xFFFFUL);
    if (0UL != u32BaseFunc) {
        if (0UL != READ_REG32_BIT(USARTx->CR1, u32BaseFunc)) {
            enNewState = ENABLE;
        }
    }
    u32BaseFunc = u32Func >> USART_LIN_FUNC_OFFSET;
    if (0UL != u32BaseFunc) {
        if (0UL != READ_REG32_BIT(USARTx->CR2, u32BaseFunc)) {
            enNewState = ENABLE;
        }
    }
    return enNewState;
}

/**
 * @brief  Get USART flag.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32Flag                 USART flag type
 *         This parameter can be any composed value of the macros group @ref USART_Flag.
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t USART_GetStatus(const CM_USART_TypeDef *USARTx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_FLAG(u32Flag));

    return (0UL == (READ_REG32_BIT(USARTx->SR, u32Flag)) ? RESET : SET);
}

/**
 * @brief  Clear USART flag.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32Flag                 USART flag type
 *         This parameter can be any composed value of the macros group @ref USART_Flag.
 * @retval None
 */
void USART_ClearStatus(CM_USART_TypeDef *USARTx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_FLAG(u32Flag));

    if ((u32Flag & USART_FLAG_ERR_MASK) > 0UL) {
        SET_REG32_BIT(USARTx->CR1, (u32Flag & USART_FLAG_ERR_MASK) << USART_CR1_CPE_POS);
    }

    /* Timeout flag */
    if ((u32Flag & USART_FLAG_RX_TIMEOUT) > 0UL) {
        SET_REG32_BIT(USARTx->CR1, USART_CR1_CRTOF);
    }

    /* LIN flag */
    if ((u32Flag & USART_FLAG_LIN_ERR) > 0UL) {
        SET_REG32_BIT(USARTx->CR1, USART_CR1_CBE);
    }

    if ((u32Flag & USART_FLAG_LIN_WKUP) > 0UL) {
        SET_REG32_BIT(USARTx->CR1, USART_CR1_CWKUP);
    }

    if ((u32Flag & USART_FLAG_LIN_BREAK) > 0UL) {
        SET_REG32_BIT(USARTx->CR1, USART_CR1_CLBD);
    }

    /* Transmission complete flag */
    if ((u32Flag & USART_FLAG_TX_END) > 0UL) {
        SET_REG32_BIT(USARTx->CR1, USART_CR1_CTEND);
    }
}

/**
 * @brief  Set USART parity.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32Parity               USART parity
 *         This parameter can be one of the macros group @ref USART_Parity_Control
 *           @arg USART_PARITY_NONE:    Parity control disabled
 *           @arg USART_PARITY_ODD:     Parity control enabled and Odd Parity is selected
 *           @arg USART_PARITY_EVEN:    Parity control enabled and Even Parity is selected
 * @retval None
 */
void USART_SetParity(CM_USART_TypeDef *USARTx, uint32_t u32Parity)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_PARITY(u32Parity));

    MODIFY_REG32(USARTx->CR1, (USART_CR1_PS | USART_CR1_PCE), u32Parity);
}

/**
 * @brief  Set USART bit direction.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32FirstBit             USART bit direction
 *         This parameter can be one of the macros group @ref USART_First_Bit
 *           @arg  USART_FIRST_BIT_MSB: MSB(Most Significant Bit)
 *           @arg  USART_FIRST_BIT_LSB: LSB(Least Significant Bit)
 * @retval None
 */
void USART_SetFirstBit(CM_USART_TypeDef *USARTx, uint32_t u32FirstBit)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_FIRST_BIT(u32FirstBit));

    MODIFY_REG32(USARTx->CR1, USART_CR1_ML, u32FirstBit);
}

/**
 * @brief  Set USART stop bit.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32StopBit              USART stop bits
 *         This parameter can be one of the macros group @ref USART_Stop_Bit
 *           @arg USART_STOPBIT_1BIT:   1 stop bit
 *           @arg USART_STOPBIT_2BIT:   2 stop bit
 * @retval None
 */
void USART_SetStopBit(CM_USART_TypeDef *USARTx, uint32_t u32StopBit)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_STOPBIT(u32StopBit));

    MODIFY_REG32(USARTx->CR2, USART_CR2_STOP, u32StopBit);
}

/**
 * @brief  Set USART data width.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32DataWidth            USART data width
 *         This parameter can be one of the macros group @ref USART_Data_Width_Bit
 *           @arg USART_DATA_WIDTH_8BIT: 8 bits word width
 *           @arg USART_DATA_WIDTH_9BIT: 9 bits word width
 * @retval None
 */
void USART_SetDataWidth(CM_USART_TypeDef *USARTx, uint32_t u32DataWidth)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_DATA_WIDTH(u32DataWidth));

    MODIFY_REG32(USARTx->CR1, USART_CR1_M, u32DataWidth);
}

/**
 * @brief  Set USART oversampling bits.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32OverSampleBit        USART over sample bit
 *         This parameter can be one of the macros group @ref USART_Over_Sample_Bit
 *           @arg USART_OVER_SAMPLE_8BIT:  Oversampling by 8 bit
 *           @arg USART_OVER_SAMPLE_16BIT: Oversampling by 16 bit
 * @retval None
 */
void USART_SetOverSampleBit(CM_USART_TypeDef *USARTx, uint32_t u32OverSampleBit)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_OVER_SAMPLE_BIT(u32OverSampleBit));

    MODIFY_REG32(USARTx->CR1, USART_CR1_OVER8, u32OverSampleBit);
}

/**
 * @brief  Set USART start bit detect polarity.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32Polarity             USART start bit detect polarity
 *         This parameter can be one of the macros group @ref USART_Start_Bit_Polarity
 *           @arg USART_START_BIT_LOW:     Detect RX pin low level
 *           @arg USART_START_BIT_FALLING: Detect RX pin falling edge
 * @retval None
 */
void USART_SetStartBitPolarity(CM_USART_TypeDef *USARTx, uint32_t u32Polarity)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_START_BIT_POLARITY(u32Polarity));

    MODIFY_REG32(USARTx->CR1, USART_CR1_SBS, u32Polarity);
}

/**
 * @brief  Set USART transmission type.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u16Type                 USART transmission content type
 *         This parameter can be one of the macros group @ref USART_Transmission_Type
 *           @arg USART_TRANS_ID:       USART transmission content type is processor ID
 *           @arg USART_TRANS_DATA:     USART transmission content type is frame data
 * @retval None
 */
void USART_SetTransType(CM_USART_TypeDef *USARTx, uint16_t u16Type)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_TRANS_TYPE(u16Type));

    MODIFY_REG16(USARTx->TDR, USART_TDR_MPID, u16Type);
}

/**
 * @brief  Set USART clock prescaler division.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32ClockDiv             USART clock prescaler division.
 *         This parameter can be one of the macros group @ref USART_Clock_Division
 * @retval None
 * @note   The clock division function is valid only when clock source is internal clock.
 */
void USART_SetClockDiv(CM_USART_TypeDef *USARTx, uint32_t u32ClockDiv)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_CLK_DIV(u32ClockDiv));

    MODIFY_REG32(USARTx->PR, USART_PR_PSC, u32ClockDiv);
}

/**
 * @brief  Get USART clock prescaler division.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @retval Returned value can be one of the macros group @ref USART_Clock_Division
 * @note   The clock division function is valid only when clock source is internal clock.
 */
uint32_t USART_GetClockDiv(const CM_USART_TypeDef *USARTx)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));

    return READ_REG32_BIT(USARTx->PR, USART_PR_PSC);
}

/**
 * @brief  Set USART clock source.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32ClockSrc             USART clock source
 *         This parameter can be one of the macros group @ref USART_Clock_Source
 *           @arg USART_CLK_SRC_EXTCLK:    Clock source is external clock(USART_CK).
 *           @arg USART_CLK_SRC_INTERNCLK: Clock source is internal clock.
 * @retval None
 */
void USART_SetClockSrc(CM_USART_TypeDef *USARTx, uint32_t u32ClockSrc)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_CLK_SRC(u32ClockSrc));

    MODIFY_REG32(USARTx->CR2, USART_CR2_CLKC_1, u32ClockSrc);
}

/**
 * @brief  Get USART clock source.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @retval Returned value can be one of the following values:
 *           - USART_CLK_SRC_EXTCLK:    Clock source is external clock(USART_CK).
 *           - USART_CLK_SRC_INTERNCLK: Clock source is internal clock.
 */
uint32_t USART_GetClockSrc(const CM_USART_TypeDef *USARTx)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));

    return READ_REG32_BIT(USARTx->CR2, USART_CR2_CLKC_1);
}

/**
 * @brief  Enable or disable USART noise filter.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void USART_FilterCmd(CM_USART_TypeDef *USARTx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(USARTx->CR1, USART_CR1_NFE);
    } else {
        CLR_REG32_BIT(USARTx->CR1, USART_CR1_NFE);
    }
}

/**
 * @brief  Enable or disable USART silence.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void USART_SilenceCmd(CM_USART_TypeDef *USARTx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(USARTx->CR1, USART_CR1_SLME);
    } else {
        CLR_REG32_BIT(USARTx->CR1, USART_CR1_SLME);
    }
}

/**
 * @brief  Set UART hardware flow control CTS/RTS selection.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32HWFlowControl        USART hardware flow control CTS/RTS selection
 *         This parameter can be one of the macros group @ref USART_Hardware_Flow_Control.
 * @retval None
 */
void USART_SetHWFlowControl(CM_USART_TypeDef *USARTx, uint32_t u32HWFlowControl)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_HW_FLOWCTRL(u32HWFlowControl));

    MODIFY_REG32(USARTx->CR3, (USART_CR3_CTSE | USART_CR3_RTSE), u32HWFlowControl);
}

/**
 * @brief  USART receive data.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @retval Receive data
 */
uint16_t USART_ReadData(const CM_USART_TypeDef *USARTx)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));

    return READ_REG16(USARTx->RDR);
}

/**
 * @brief  USART send data.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u16Data                 Transmit data
 * @retval None
 */
void USART_WriteData(CM_USART_TypeDef *USARTx, uint16_t u16Data)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_DATA(u16Data));

    WRITE_REG16(USARTx->TDR, u16Data);
}

/**
 * @brief  USART send processor ID.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 ** @param [in] u16ID                   Processor ID
 * @retval None
 */
void USART_WriteID(CM_USART_TypeDef *USARTx, uint16_t u16ID)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));
    DDL_ASSERT(IS_USART_DATA(u16ID));

    WRITE_REG16(USARTx->TDR, (USART_TDR_MPID | u16ID));
}

/**
 * @brief  Set USART baudrate.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32Baudrate             UART baudrate
 * @param  [out] pf32Error              E(%) baudrate error rate
 * @retval int32_t:
 *           - LL_OK:                   Set successfully.
 *           - LL_ERR_INVD_PARAM:       Set unsuccessfully.
 * @note The function uses fraction division to ensure baudrate accuracy if USART unit supports baudrate fraction division.
 */
int32_t USART_SetBaudrate(CM_USART_TypeDef *USARTx, uint32_t u32Baudrate, float32_t *pf32Error)
{
    uint32_t u32Mode;
    stc_usart_brr_t stcUsartBrr;
    int32_t i32Ret;

    DDL_ASSERT(u32Baudrate > 0UL);
    DDL_ASSERT(IS_USART_UNIT(USARTx));

    /* Get USART clock frequency */
    stcUsartBrr.u32UsartClock = USART_GetUsartClockFreq(USARTx);
    stcUsartBrr.u32Baudrate   = u32Baudrate;
    stcUsartBrr.f32Error      = 0.0F;
    stcUsartBrr.u32Fraction   = 0xFFUL;

    /* Get usart mode */
    u32Mode = READ_REG32_BIT(USARTx->CR1, USART_CR1_MS);
    /* Calculate baudrate for BRR */
    if (0UL == u32Mode) {
        if (0UL == READ_REG32_BIT(USARTx->CR3, USART_CR3_SCEN)) {
            /* uart mode */
            i32Ret = UART_CalculateBrr(USARTx, &stcUsartBrr);
        } else {
            /* Smart_card function */
            i32Ret = SmartCard_CalculateBrr(USARTx, &stcUsartBrr);
        }
    } else {
        /* Clock sync mode */
        i32Ret = ClockSync_CalculateBrr(USARTx, &stcUsartBrr);
    }

    if (LL_OK == i32Ret) {
        /* Set BRR value(integer & fraction) */
        MODIFY_REG32(USARTx->BRR, (USART_BRR_DIV_INTEGER | USART_BRR_DIV_FRACTION), \
                     (stcUsartBrr.u32Fraction | (stcUsartBrr.u32Integer << USART_BRR_DIV_INTEGER_POS)));

        if (0xFFUL != stcUsartBrr.u32Fraction) {
            SET_REG32_BIT(USARTx->CR1, USART_CR1_FBME);
        }
    } else {
        /* rsvd */
    }
    if (NULL != pf32Error) {
        *pf32Error = stcUsartBrr.f32Error;
    }

    return i32Ret;
}

/**
 * @brief  Set USART Smartcard ETU Clock.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32EtuClock             USART Smartcard ETU Clock.
 *         This parameter can be one of the macros group @ref USART_Smartcard_ETU_Clock
 *           @arg USART_SC_ETU_CLK32:   1 etu = 32/f
 *           @arg USART_SC_ETU_CLK64:   1 etu = 64/f
 *           @arg USART_SC_ETU_CLK128:  1 etu = 128/f
 *           @arg USART_SC_ETU_CLK256:  1 etu = 256/f
 *           @arg USART_SC_ETU_CLK372:  1 etu = 372/f
 * @retval None
 */
void USART_SmartCard_SetEtuClock(CM_USART_TypeDef *USARTx, uint32_t u32EtuClock)
{
    DDL_ASSERT(IS_USART_SMARTCARD_UNIT(USARTx));
    DDL_ASSERT(IS_USART_SMARTCARD_ETU_CLK(u32EtuClock));

    MODIFY_REG32(USARTx->CR3, USART_CR3_BCN, u32EtuClock);
}

/**
 * @brief  Enable/disable stop mode noise filter.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void USART_StopModeNoiseFilterCmd(const CM_USART_TypeDef *USARTx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_USART_STOP_MD_UNIT(USARTx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_PERIC->USART1_NFC, PERIC_USART1_NFC_USART1_NFE);
    } else {
        CLR_REG32_BIT(CM_PERIC->USART1_NFC, PERIC_USART1_NFC_USART1_NFE);
    }
}

/**
 * @brief  Set stop mode noise filter.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32Level                The noise filter width level value
 *         This parameter can be one of the macros group @ref USART_Stop_Mode_Noise_Filter_Width_Level
 *           @arg USART_STOP_MD_FILTER_LVL1: Filter width level 1
 *           @arg USART_STOP_MD_FILTER_LVL2: Filter width level 2
 *           @arg USART_STOP_MD_FILTER_LVL3: Filter width level 3
 *           @arg USART_STOP_MD_FILTER_LVL4: Filter width level 4
 * @retval None
 */
void USART_SetStopModeNoiseFilter(const CM_USART_TypeDef *USARTx, uint32_t u32Level)
{
    DDL_ASSERT(IS_USART_STOP_MD_UNIT(USARTx));
    DDL_ASSERT(IS_USART_STOP_MD_FILTER(u32Level));

    MODIFY_REG32(CM_PERIC->USART1_NFC, PERIC_USART1_NFC_USASRT1_NFS, u32Level);
}

/**
 * @brief  Enable or disable USART loopback function.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void USART_LIN_LoopbackCmd(CM_USART_TypeDef *USARTx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_USART_LIN_UNIT(USARTx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(USARTx->CR3, USART_CR3_LOOP);
    } else {
        CLR_REG32_BIT(USARTx->CR3, USART_CR3_LOOP);
    }
}

/**
 * @brief  Set USART LIN counter clock prescaler division.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32ClockDiv             USART USART LIN counter clock prescaler division.
 *         This parameter can be one of the macros group @ref USART_LIN_BMC_Clock_Division
 *           @arg USART_LIN_BMC_CLK_DIV1: CLK
 *           @arg USART_LIN_BMC_CLK_DIV2: CLK/2
 *           @arg USART_LIN_BMC_CLK_DIV4: CLK/4
 *           @arg USART_LIN_BMC_CLK_DIV8: CLK/8
 * @retval None
 * @note   The clock division function is valid when clock source is internal clock.
 */
void USART_LIN_SetBmcClockDiv(CM_USART_TypeDef *USARTx, uint32_t u32ClockDiv)
{
    DDL_ASSERT(IS_USART_LIN_UNIT(USARTx));
    DDL_ASSERT(IS_USART_LIN_BMC_CLK_DIV(u32ClockDiv));

    MODIFY_REG32(USARTx->PR, USART_PR_LBMPSC, u32ClockDiv);
}

/**
 * @brief  LIN Request break sending
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @retval None
 */
void USART_LIN_RequestBreakSending(CM_USART_TypeDef *USARTx)
{
    DDL_ASSERT(IS_USART_LIN_UNIT(USARTx));

    SET_REG32_BIT(USARTx->CR2, USART_CR2_SBK);
}

/**
 * @brief  Get request break sending status
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t USART_LIN_GetRequestBreakStatus(const CM_USART_TypeDef *USARTx)
{
    DDL_ASSERT(IS_USART_UNIT(USARTx));

    return (0UL == READ_REG32_BIT(USARTx->CR2, USART_CR2_SBK)) ? RESET : SET;
}

/**
 * @brief  Set send break mode for USART LIN.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32Mode                 USART send break mode
 *         This parameter can be one of the macros group @ref USART_LIN_Send_Break_Mode
 *           @arg USART_LIN_SEND_BREAK_MD_SBK: Start send break after USART_CR2 SBK bit set 1 value
 *           @arg USART_LIN_SEND_BREAK_MD_TDR: Start send break after USART_DR TDR write 0x00 value
 * @retval None
 */
void USART_LIN_SetBreakMode(CM_USART_TypeDef *USARTx, uint32_t u32Mode)
{
    DDL_ASSERT(IS_USART_LIN_UNIT(USARTx));
    DDL_ASSERT(IS_USART_LIN_SEND_BREAK_MD(u32Mode));

    MODIFY_REG32(USARTx->CR2, USART_CR2_SBKM, u32Mode);
}

/**
 * @brief  Get send break mode for USART LIN.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @retval Returned value can be one of the following values:
 *           - USART_LIN_SEND_BREAK_MD_SBK: Start send break after USART_CR2 SBK bit set 1 value
 *           - USART_LIN_SEND_BREAK_MD_TDR: Start send break after USART_DR TDR write 0x00 value
 */
uint32_t USART_LIN_GetBreakMode(const CM_USART_TypeDef *USARTx)
{
    DDL_ASSERT(IS_USART_LIN_UNIT(USARTx));

    return READ_REG32_BIT(USARTx->CR2, USART_CR2_SBKM);
}

/**
 * @brief  Get USART LIN baudrate measure count.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @retval LIN baudrate measure count value
 */
uint32_t USART_LIN_GetMeasureCount(const CM_USART_TypeDef *USARTx)
{
    DDL_ASSERT(IS_USART_LIN_UNIT(USARTx));

    return READ_REG32_BIT(USARTx->LBMC, USART_LBMC_LBMC);
}

/**
 * @brief  Get USART LIN baudrate measure count.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @retval LIN baudrate measure count value
 */
uint32_t USART_LIN_GetMeasureBaudrate(const CM_USART_TypeDef *USARTx)
{
    uint32_t u32BmClk;
    uint32_t u32LBMC;

    DDL_ASSERT(IS_USART_LIN_UNIT(USARTx));

    u32BmClk = USART_GetLinBmcClockFreq(USARTx);
    u32LBMC = READ_REG32_BIT(USARTx->LBMC, USART_LBMC_LBMC);

    return (u32LBMC > 0UL) ? (u32BmClk / u32LBMC) : 0UL;
}

/**
 * @brief  Set USART LIN break detection length.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32Len                  USART clock prescaler division.
 *         This parameter can be one of the macros group @ref USART_LIN_Detect_Break_Length
 *           @arg USART_LIN_DETECT_BREAK_10BIT: 10-bit break detection
 *           @arg USART_LIN_DETECT_BREAK_11BIT: 11-bit break detection
 * @retval None
 */
void USART_LIN_SetDetectBreakLen(CM_USART_TypeDef *USARTx, uint32_t u32Len)
{
    DDL_ASSERT(IS_USART_LIN_UNIT(USARTx));
    DDL_ASSERT(IS_USART_LIN_DETECT_BREAK_LEN(u32Len));

    MODIFY_REG32(USARTx->CR2, USART_CR2_LBDL, u32Len);
}

/**
 * @brief  Set USART LIN break sending length.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] u32Len                  USART clock prescaler division.
 *         This parameter can be one of the macros group @ref USART_LIN_Send_Break_Length
 *           @arg USART_LIN_SEND_BREAK_10BIT: Send break 10-bit
 *           @arg USART_LIN_SEND_BREAK_11BIT: Send break 11-bit
 *           @arg USART_LIN_SEND_BREAK_13BIT: Send break 13-bit
 *           @arg USART_LIN_SEND_BREAK_14BIT: Send break 14-bit
 * @retval None
 */
void USART_LIN_SetSendBreakLen(CM_USART_TypeDef *USARTx, uint32_t u32Len)
{
    DDL_ASSERT(IS_USART_LIN_UNIT(USARTx));
    DDL_ASSERT(IS_USART_LIN_SEND_BREAK_LEN(u32Len));

    MODIFY_REG32(USARTx->CR2, USART_CR2_SBKL, u32Len);
}

/**
 * @brief  UART transmit data in polling mode.
 * @param  [in]  USARTx                 Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [out] pvBuf                  The pointer to data transmitted buffer
 * @param  [in]  u32Len                 Amount of frame to be sent.
 * @param  [in]  u32Timeout             Timeout duration(Max value @ref USART_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Communicate timeout.
 *           - LL_ERR_INVD_PARAM:       u32Len value is 0 or pvBuf is NULL.
 * @note Block checking flag if u32Timeout value is USART_MAX_TIMEOUT
 */
int32_t USART_UART_Trans(CM_USART_TypeDef *USARTx, const void *pvBuf, uint32_t u32Len, uint32_t u32Timeout)
{
    uint32_t i;
    uint32_t u32DataWidth;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_USART_UNIT(USARTx));

    if ((NULL != pvBuf) && (u32Len > 0UL)) {
        u32DataWidth = READ_REG32_BIT(USARTx->CR1, USART_CR1_M);

        if ((USART_DATA_WIDTH_8BIT == u32DataWidth) || (USART_DATA_WIDTH_9BIT == u32DataWidth)) {
            for (i = 0UL; i < u32Len; i++) {
                /* Wait TX buffer empty. */
                i32Ret = USART_WaitStatus(USARTx, USART_FLAG_TX_EMPTY, SET, u32Timeout);
                if (LL_OK != i32Ret) {
                    break;
                }

                if (u32DataWidth == USART_DATA_WIDTH_8BIT) {
                    USART_WriteData(USARTx, ((const uint8_t *)pvBuf)[i]);
                } else {
                    USART_WriteData(USARTx, ((const uint16_t *)pvBuf)[i]);
                }
            }

            if (LL_OK == i32Ret) {
                i32Ret = USART_WaitStatus(USARTx, USART_FLAG_TX_CPLT, SET, u32Timeout);
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  UART receive data in polling mode.
 * @param  [in]  USARTx                 Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [out] pvBuf                  The pointer to data received buffer
 * @param  [in]  u32Len                 Amount of frame to be received.
 * @param  [in]  u32Timeout             Timeout duration(Max value @ref USART_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Communicate timeout.
 *           - LL_ERR_INVD_PARAM:       u32Len value is 0 or the pointer pvBuf value is NULL.
 * @note Block checking flag if u32Timeout value is USART_MAX_TIMEOUT
 */
int32_t USART_UART_Receive(const CM_USART_TypeDef *USARTx, void *pvBuf, uint32_t u32Len, uint32_t u32Timeout)
{
    uint32_t u32Count;
    uint32_t u32DataWidth;
    uint16_t u16ReceiveData;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_USART_UNIT(USARTx));

    if ((NULL != pvBuf) && (u32Len > 0UL)) {
        u32DataWidth = READ_REG32_BIT(USARTx->CR1, USART_CR1_M);

        for (u32Count = 0UL; u32Count < u32Len; u32Count++) {
            i32Ret = USART_WaitStatus(USARTx, USART_FLAG_RX_FULL, SET, u32Timeout);
            if (LL_OK == i32Ret) {
                u16ReceiveData = USART_ReadData(USARTx);
                if (USART_DATA_WIDTH_8BIT == u32DataWidth) {
                    ((uint8_t *)pvBuf)[u32Count] = (uint8_t)(u16ReceiveData & 0xFFU);
                } else {
                    ((uint16_t *)pvBuf)[u32Count] = (uint16_t)(u16ReceiveData & 0x1FFU);
                }
            } else {
                break;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Clock sync transmit && receive data in polling mode.
 * @param  [in] USARTx                  Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in] au8Buf                  The pointer to data transmitted buffer
 * @param  [in] u32Len                  Amount of data to be transmitted.
 * @param  [in] u32Timeout              Timeout duration(Max value @ref USART_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Communicate timeout.
 *           - LL_ERR_INVD_PARAM:       u32Len value is 0 or the pointer au8Buf value is NULL.
 * @note Block checking flag if u32Timeout value is USART_MAX_TIMEOUT
 */
int32_t USART_ClockSync_Trans(CM_USART_TypeDef *USARTx, const uint8_t au8Buf[], uint32_t u32Len, uint32_t u32Timeout)
{
    uint32_t i;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_USART_UNIT(USARTx));

    if ((NULL != au8Buf) && (u32Len > 0UL)) {
        for (i = 0UL; i < u32Len; i++) {
            /* Wait TX buffer empty. */
            i32Ret = USART_WaitStatus(USARTx, USART_FLAG_TX_EMPTY, SET, u32Timeout);
            if (LL_OK == i32Ret) {
                USART_WriteData(USARTx, au8Buf[i]);
                if (READ_REG32_BIT(USARTx->CR1, USART_RX) != 0UL) {
                    i32Ret = USART_WaitStatus(USARTx, USART_FLAG_RX_FULL, SET, u32Timeout);
                    if (LL_OK == i32Ret) {
                        (void)USART_ReadData(USARTx);
                    }
                }
            }

            if (LL_OK != i32Ret) {
                break;
            }
        }

        if (LL_OK == i32Ret) {
            i32Ret = USART_WaitStatus(USARTx, USART_FLAG_TX_CPLT, SET, u32Timeout);
        }
    }

    return i32Ret;
}

/**
 * @brief  Clock sync receive data in polling mode.
 * @param  [in]  USARTx                 Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [out] au8Buf                 The pointer to data received buffer
 * @param  [in]  u32Len                 Amount of data to be sent and received.
 * @param  [in]  u32Timeout             Timeout duration(Max value @ref USART_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Communicate timeout.
 *           - LL_ERR_INVD_PARAM:       u32Len value is 0 or the pointer au8Buf value is NULL.
 * @note Block checking flag if u32Timeout value is USART_MAX_TIMEOUT.
 */
int32_t USART_ClockSync_Receive(CM_USART_TypeDef *USARTx, uint8_t au8Buf[], uint32_t u32Len, uint32_t u32Timeout)
{
    uint32_t i;
    en_functional_state_t enTX;
    en_functional_state_t enMasterMode;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_USART_UNIT(USARTx));

    if ((NULL != au8Buf) && (u32Len > 0UL)) {
        i32Ret = LL_OK;
        enTX = (READ_REG32_BIT(USARTx->CR1, USART_TX) == 0UL) ? DISABLE : ENABLE;
        enMasterMode = (USART_CLK_SRC_EXTCLK == READ_REG32_BIT(USARTx->CR2, USART_CR2_CLKC)) ? DISABLE : ENABLE;

        for (i = 0UL; i < u32Len; i++) {
            if ((ENABLE == enMasterMode) || (ENABLE == enTX)) {
                USART_WriteData(USARTx, 0xFFU);

                /* Wait TX buffer empty. */
                i32Ret = USART_WaitStatus(USARTx, USART_FLAG_TX_EMPTY, SET, u32Timeout);
            }

            if (LL_OK == i32Ret) {
                i32Ret = USART_WaitStatus(USARTx, USART_FLAG_RX_FULL, SET, u32Timeout);
                if (LL_OK == i32Ret) {
                    au8Buf[i] = (uint8_t)USART_ReadData(USARTx);
                }
            }

            if (LL_OK != i32Ret) {
                break;
            }
        }

        if (LL_OK == i32Ret) {
            i32Ret = USART_WaitStatus(USARTx, USART_FLAG_TX_CPLT, SET, u32Timeout);
        }
    }

    return i32Ret;
}

/**
 * @brief  Clock sync transmit && receive data in polling mode.
 * @param  [in]  USARTx                 Pointer to USART instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_USARTx:            USART unit instance register base
 * @param  [in]  au8TxBuf               The pointer to data transmitted buffer
 * @param  [out] au8RxBuf               The pointer to data received buffer
 * @param  [in]  u32Len                 Amount of data to be sent and received.
 * @param  [in]  u32Timeout             Timeout duration(Max value @ref USART_Max_Timeout)
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_TIMEOUT:          Communicate timeout.
 *           - LL_ERR_INVD_PARAM:       u32Len value is 0.
 * @note Block checking flag if u32Timeout value is USART_MAX_TIMEOUT.
 */
int32_t USART_ClockSync_TransReceive(CM_USART_TypeDef *USARTx, const uint8_t au8TxBuf[], uint8_t au8RxBuf[],
                                     uint32_t u32Len, uint32_t u32Timeout)
{
    uint32_t i;
    uint8_t u8ReceiveData;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_USART_UNIT(USARTx));

    if (u32Len > 0UL) {
        for (i = 0UL; i < u32Len; i++) {
            if (NULL != au8TxBuf) {
                USART_WriteData(USARTx, au8TxBuf[i]);
            } else {
                USART_WriteData(USARTx, 0xFFU);
            }

            /* Wait TX buffer empty. */
            i32Ret = USART_WaitStatus(USARTx, USART_FLAG_TX_EMPTY, SET, u32Timeout);
            if (LL_OK == i32Ret) {
                i32Ret = USART_WaitStatus(USARTx, USART_FLAG_RX_FULL, SET, u32Timeout);
                if (LL_OK == i32Ret) {
                    u8ReceiveData = (uint8_t)USART_ReadData(USARTx);
                    if (NULL != au8RxBuf) {
                        au8RxBuf[i] = u8ReceiveData;
                    }
                }
            }

            if (LL_OK != i32Ret) {
                break;
            }
        }

        if (LL_OK == i32Ret) {
            i32Ret = USART_WaitStatus(USARTx, USART_FLAG_TX_CPLT, SET, u32Timeout);
        }
    }

    return i32Ret;
}

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

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
