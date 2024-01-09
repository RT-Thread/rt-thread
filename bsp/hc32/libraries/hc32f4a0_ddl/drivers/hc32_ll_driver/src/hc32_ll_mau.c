/**
 *******************************************************************************
 * @file  hc32_ll_mau.c
 * @brief This file provides firmware functions to manage the MAU.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-06-30       CDT             Add API MAU_DeInit()
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
#include "hc32_ll_mau.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_MAU MAU
 * @brief MAU Driver Library
 * @{
 */

#if (LL_MAU_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup MAU_Local_Macros MAU Local Macros
 * @{
 */

/**
 * @defgroup MAU_Check_Parameters_Validity MAU Check Parameters Validity
 * @{
 */
#define IS_VALID_UNIT(x)            ((x) == CM_MAU)
#define IS_LSHBIT_NUM(x)            ((x) <= MAU_SQRT_OUTPUT_LSHIFT_MAX)
#define IS_ANGLE_IDX(x)             ((x) < MAU_SIN_ANGIDX_TOTAL)
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

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/

/**
 * @defgroup MAU_Global_Functions MAU Global Functions
 * @{
 */

/**
 * @brief  Sqrt result left shift config
 * @param  [in] MAUx            Pointer to MAU instance register base.
 *         This parameter can only be: @arg CM_MAU
 * @param  [in] u8ShiftNum      Number of left shift bits
 *                              Max value is MAU_SQRT_OUTPUT_LSHIFT_MAX
 * @retval None
 */
void MAU_SqrtResultLShiftConfig(CM_MAU_TypeDef *MAUx, uint8_t u8ShiftNum)
{
    DDL_ASSERT(IS_VALID_UNIT(MAUx));
    DDL_ASSERT(IS_LSHBIT_NUM(u8ShiftNum));

    MODIFY_REG32(MAUx->CSR, MAU_CSR_SHIFT, ((uint32_t)u8ShiftNum << MAU_CSR_SHIFT_POS));
}

/**
 * @brief  Sqrt interrupt function command
 * @param  [in] MAUx            Pointer to MAU instance register base.
 *         This parameter can only be: @arg CM_MAU
 * @param  [in] enNewState      An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void MAU_SqrtIntCmd(CM_MAU_TypeDef *MAUx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(MAUx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(MAUx->CSR, MAU_CSR_INTEN, (uint32_t)enNewState << MAU_CSR_INTEN_POS);
}

/**
 * @brief  Input radicand for sqrt
 * @param  [in] MAUx            Pointer to MAU instance register base.
 *         This parameter can only be: @arg CM_MAU
 * @param  [in] u32Radicand     Data to be square rooted
 * @retval None
 */
void MAU_SqrtWriteData(CM_MAU_TypeDef *MAUx, uint32_t u32Radicand)
{
    DDL_ASSERT(IS_VALID_UNIT(MAUx));

    WRITE_REG32(MAUx->DTR0, u32Radicand);
}

/**
 * @brief  Start sqrt calculation
 * @param  [in] MAUx            Pointer to MAU instance register base.
 *         This parameter can only be: @arg CM_MAU
 * @retval None
 */
void MAU_SqrtStart(CM_MAU_TypeDef *MAUx)
{
    DDL_ASSERT(IS_VALID_UNIT(MAUx));

    SET_REG32_BIT(MAUx->CSR, MAU_CSR_START);
}

/**
 * @brief  Check whether the sqrt calculation is in progress
 * @param  [in] MAUx            Pointer to MAU instance register base.
 *         This parameter can only be: @arg CM_MAU
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t MAU_SqrtGetStatus(const CM_MAU_TypeDef *MAUx)
{
    DDL_ASSERT(IS_VALID_UNIT(MAUx));

    return (0UL != READ_REG32_BIT(MAUx->CSR, MAU_CSR_BUSY)) ? SET : RESET;
}

/**
 * @brief  Read result of sqrt
 * @param  [in] MAUx            Pointer to MAU instance register base.
 *         This parameter can only be: @arg CM_MAU
 * @retval Result of sqrt,range is [0,0x10000]
 */
uint32_t MAU_SqrtReadData(const CM_MAU_TypeDef *MAUx)
{
    DDL_ASSERT(IS_VALID_UNIT(MAUx));

    return READ_REG32(MAUx->RTR0);
}

/**
 * @brief  Initialize the MAU Sqrt function.
 * @param  [in] MAUx            Pointer to MAU instance register base.
 *         This parameter can only be: @arg CM_MAU
 * @param  [in] u8ShiftNum      Sqrt result left shift bits, max value is @ref MAU_SQRT_OUTPUT_LSHIFT_MAX
 * @param  [in] enNewState      Enable or Disable sqrt interrupt @ref en_functional_state_t
 * @retval None
 */
void MAU_SqrtInit(CM_MAU_TypeDef *MAUx, uint8_t u8ShiftNum, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(MAUx));
    DDL_ASSERT(IS_LSHBIT_NUM(u8ShiftNum));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(MAUx->CSR, MAU_CSR_SHIFT | MAU_CSR_INTEN,
                 ((((uint32_t)u8ShiftNum << MAU_CSR_SHIFT_POS)) | ((uint32_t)enNewState << MAU_CSR_INTEN_POS)));
}

/**
 * @brief  De-initialize the MAU Sqrt function.
 * @param  [in] MAUx            Pointer to MAU instance register base.
 *         This parameter can only be: @arg CM_MAU
 * @retval None
 */
void MAU_SqrtDeInit(CM_MAU_TypeDef *MAUx)
{
    DDL_ASSERT(IS_VALID_UNIT(MAUx));

    CLR_REG32_BIT(MAUx->CSR, MAU_CSR_SHIFT | MAU_CSR_INTEN);
}

/**
 * @brief  Square root
 * @param  [in] MAUx            Pointer to MAU instance register base.
 *         This parameter can only be: @arg CM_MAU
 * @param  [in]  u32Radicand    Data to be square rooted
 * @param  [out] pu32Result     Result of sqrt,range is [0,0x10000]
 * @retval int32_t:
 *               -  LL_OK:      No errors occurred
 *               -  LL_ERR:     Errors occurred
 */
int32_t MAU_Sqrt(CM_MAU_TypeDef *MAUx, uint32_t u32Radicand, uint32_t *pu32Result)
{
    __IO uint32_t u32TimeCount = MAU_SQRT_TIMEOUT;
    int32_t i32Ret = LL_OK;

    DDL_ASSERT(IS_VALID_UNIT(MAUx));
    DDL_ASSERT(pu32Result != (void *)0UL);

    WRITE_REG32(MAUx->DTR0, u32Radicand);

    SET_REG32_BIT(MAUx->CSR, MAU_CSR_START);
    __ASM("NOP");
    __ASM("NOP");
    __ASM("NOP");

    while ((MAUx->CSR & MAU_CSR_BUSY) != 0UL) {
        if (u32TimeCount-- == 0UL) {
            i32Ret = LL_ERR;
            break;
        }
    }

    if (LL_OK == i32Ret) {
        *pu32Result = READ_REG32(MAUx->RTR0);
    }

    return i32Ret;
}

/**
 * @brief  Sine
 * @param  [in] MAUx            Pointer to MAU instance register base.
 *         This parameter can only be: @arg CM_MAU
 * @param  u16AngleIdx:         Angle index,range is [0,0xFFF], calculation method for reference:
           AngleIdx = (uint16_t)(Angle * 4096.0F / 360.0F + 0.5F) % 4096U
 * @retval Result of Sine in Q15 format
 */
int16_t MAU_Sin(CM_MAU_TypeDef *MAUx, uint16_t u16AngleIdx)
{
    DDL_ASSERT(IS_VALID_UNIT(MAUx));
    DDL_ASSERT(IS_ANGLE_IDX(u16AngleIdx));

    WRITE_REG16(MAUx->DTR1, u16AngleIdx);
    __ASM("NOP");

    return (int16_t)READ_REG16(MAUx->RTR1);
}

/**
 * @brief  De-initializes MAU.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   De-Initialize success.
 *           - LL_ERR_TIMEOUT:          Timeout.
 */
int32_t MAU_DeInit(void)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t u32TimeOut = MAU_SQRT_TIMEOUT;
    /* Wait generating done */
    while (0UL != READ_REG32(bCM_MAU->CSR_b.BUSY)) {
        u32TimeOut--;
        if (0UL == u32TimeOut) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }
    if (LL_OK == i32Ret) {
        WRITE_REG32(CM_MAU->CSR, 0x00000000UL);
        WRITE_REG32(CM_MAU->DTR0,  0x00000000UL);
        WRITE_REG32(CM_MAU->RTR0,  0x00000000UL);
        WRITE_REG32(CM_MAU->DTR1,  0x00000000UL);
        WRITE_REG32(CM_MAU->RTR1,  0x00000000UL);
    }
    return i32Ret;
}

/**
 * @}
 */

#endif /* LL_MAU_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
