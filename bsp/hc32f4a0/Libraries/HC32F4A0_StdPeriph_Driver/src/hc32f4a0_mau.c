/**
 *******************************************************************************
 * @file  hc32f4a0_mau.c
 * @brief This file provides firmware functions to manage the MAU.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hexiao          First version
   2020-07-15       Hexiao          Modify MAU_SqrtStartCmd to MAU_SqrtStart
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
#include "hc32f4a0_mau.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_MAU MAU
 * @brief MAU Driver Library
 * @{
 */

#if (DDL_MAU_ENABLE == DDL_ON)

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
#define IS_VALID_UNIT(x)            ((x) == M4_MAU)
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
 * @param  [in] MAUx   Pointer to MAU instance register base.
 *         This parameter can only be: @arg M4_MAU
 * @param  [in] u8LShBitsNumber     number of left shift bits
 *                                  max value is MAU_SQRT_OUTPUT_LSHIFT_MAX
 * @retval None
 */
void MAU_SqrtResultLShiftCfg(M4_MAU_TypeDef *MAUx, uint8_t u8LShBitsNumber)
{
    DDL_ASSERT(IS_VALID_UNIT(MAUx));
    DDL_ASSERT(u8LShBitsNumber <= MAU_SQRT_OUTPUT_LSHIFT_MAX);

    MODIFY_REG32(MAUx->CSR, MAU_CSR_SHIFT, ((uint32_t)u8LShBitsNumber << MAU_CSR_SHIFT_POS));
}

/**
 * @brief  Sqrt interrupt function command
 * @param  [in] MAUx   Pointer to MAU instance register base.
 *         This parameter can only be: @arg M4_MAU
 * @param  [in] enNewState           New state of the MAUx sqrt interrupt function,
 *                                   @ref en_functional_state_t
 * @retval None
 */
void MAU_SqrtIntCmd(M4_MAU_TypeDef *MAUx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_UNIT(MAUx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    MODIFY_REG32(MAUx->CSR, MAU_CSR_INTEN, (uint32_t)enNewState << MAU_CSR_INTEN_POS);
}

/**
 * @brief  Input radicand for sqrt
 * @param  [in] MAUx   Pointer to MAU instance register base.
 *         This parameter can only be: @arg M4_MAU
 * @param  [in]  u32Radicand   data to be square rooted
 * @retval None
 */
void MAU_SqrtWriteDataReg(M4_MAU_TypeDef* MAUx, uint32_t u32Radicand)
{
    DDL_ASSERT(M4_MAU == MAUx);

    WRITE_REG32(MAUx->DTR0, u32Radicand);
}

/**
 * @brief  Start sqrt calculation
 * @param  [in] MAUx   Pointer to MAU instance register base.
 *         This parameter can only be: @arg M4_MAU
 * @retval None
 */
void MAU_SqrtStart(M4_MAU_TypeDef *MAUx)
{
    DDL_ASSERT(M4_MAU == MAUx);

    SET_REG32_BIT(MAUx->CSR, MAU_CSR_START);
}

/**
 * @brief  Read if sqrt calculation is ongoing or not
 * @param  [in] MAUx   Pointer to MAU instance register base.
 *         This parameter can only be: @arg M4_MAU
 * @retval An en_flag_status_t enumeration value:
 *           - Set: calculation is ongoing
 *           - Reset: calculation is not ongoing
 */
en_flag_status_t MAU_SqrtGetStatus(const M4_MAU_TypeDef *MAUx)
{
    DDL_ASSERT(M4_MAU == MAUx);

    return (0UL != READ_REG32_BIT(MAUx->CSR, MAU_CSR_BUSY)) ? Set : Reset;
}

/**
 * @brief  Read result of sqrt
 * @param  [in] MAUx   Pointer to MAU instance register base.
 *         This parameter can only be: @arg M4_MAU
 * @retval Result of sqrt,range is [0,0x10000]
 */
uint32_t MAU_SqrtReadDataReg(const M4_MAU_TypeDef *MAUx)
{
    DDL_ASSERT(M4_MAU == MAUx);

    return READ_REG32(MAUx->RTR0);
}

/**
 * @brief  Initialize the specified DAC peripheral according to the specified parameters.
 * @param  [in]  MAUx                  Pointer to MAU instance register base.
 *         This parameter can only be: @arg M4_MAU
 * @param  [in] u8LShBitsNumber       Sqrt result left shift bits number
 *                                    max value is @ref MAU_SQRT_OUTPUT_LSHIFT_MAX
 * @param  [in] enIntNewState         Enable or Disable sqrt interrupt
 *                                    @ref en_functional_state_t
 * @retval None
 */
void MAU_SqrtInit(M4_MAU_TypeDef *MAUx, uint8_t u8LShBitsNumber, en_functional_state_t enIntNewState)
{
    DDL_ASSERT(M4_MAU == MAUx);
    DDL_ASSERT(u8LShBitsNumber <= MAU_SQRT_OUTPUT_LSHIFT_MAX);
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enIntNewState));

    MODIFY_REG32(MAUx->CSR, MAU_CSR_SHIFT | MAU_CSR_INTEN,
    ((((uint32_t)u8LShBitsNumber << MAU_CSR_SHIFT_POS)) | ((uint32_t)enIntNewState << MAU_CSR_INTEN_POS)));
}

/**
 * @brief  De-initialize the DAC peripheral. Reset the registers of the specified DAC unit.
 * @param  [in]  MAUx       Pointer to MAU instance register base.
 *         This parameter can only be: @arg M4_MAU
 * @retval None
 */
void MAU_SqrtDeInit(M4_MAU_TypeDef *MAUx)
{
    DDL_ASSERT(M4_MAU == MAUx);

    CLEAR_REG32_BIT(MAUx->CSR, MAU_CSR_SHIFT | MAU_CSR_INTEN);
}

/**
 * @brief  Square root
 * @param  [in]  MAUx       Pointer to MAU instance register base.
 *         This parameter can only be: @arg M4_MAU
 * @param  [in]  u32Radicand   data to be square rooted
 * @param  [out] pu32Result    Result of sqrt,range is [0,0x10000]
 * @retval An en_result_t enumeration value
 *               -  Ok:      No errors occurred
 *               -  Error:   errors occurred
 */
en_result_t MAU_Sqrt(M4_MAU_TypeDef *MAUx, uint32_t u32Radicand, uint32_t *pu32Result)
{
    DDL_ASSERT(M4_MAU == MAUx);
    DDL_ASSERT(pu32Result != (void *)0UL);

    uint32_t u32TimeCount = 0UL;
    en_result_t enRet = Ok;

    WRITE_REG32(MAUx->DTR0, u32Radicand);
    SET_REG32_BIT(MAUx->CSR, MAU_CSR_START);
    __ASM("NOP");
    __ASM("NOP");
    __ASM("NOP");

    while((MAUx->CSR & MAU_CSR_BUSY) != 0UL)
    {
        if(u32TimeCount++ > MAU_SQRT_TIMEOUT)
        {
            enRet = Error;
            break;
        }
    }

    if(Ok == enRet)
    {
        *pu32Result = READ_REG32(MAUx->RTR0);
    }

    return enRet;
}

/**
 * @brief  Sine
 * @param  [in] MAUx   Pointer to MAU instance register base.
 *         This parameter can only be: @arg M4_MAU
 * @param  u16AngleIdx: Angle index,range is [0,0xFFF], calculation method for reference:
           AngleIdx = (uint16_t)(Angle * 4096.0F / 360.0F + 0.5F) % 4096U
 * @retval Result of Sine in Q15 format
 */
int16_t MAU_Sin(M4_MAU_TypeDef *MAUx, uint16_t u16AngleIdx)
{
    DDL_ASSERT(M4_MAU == MAUx);
    DDL_ASSERT(MAU_SIN_ANGIDX_TOTAL > u16AngleIdx);

    WRITE_REG16(MAUx->DTR1, u16AngleIdx);
    __ASM("NOP");

    return (int16_t)READ_REG16(MAUx->RTR1);
}

/**
 * @}
 */

#endif /* DDL_MAU_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
