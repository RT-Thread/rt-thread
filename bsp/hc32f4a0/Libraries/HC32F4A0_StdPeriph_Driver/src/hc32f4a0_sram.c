/**
 *******************************************************************************
 * @file  hc32f4a0_sram.c
 * @brief This file provides firmware functions to manage the SRAM.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Wuze            First version
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
#include "hc32f4a0_sram.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_SRAM SRAM
 * @brief SRAM Driver Library
 * @{
 */

#if (DDL_SRAM_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup SRAM_Local_Macros SRAM Local Macros
 * @{
 */

/**
 * @defgroup SRAM_Configuration_Bits_Mask SRAM Configuration Bits Mask
 * @{
 */
#define SRAM_ECC_MODE_MSK           (SRAMC_CKCR_ECCMOD)
#define SRAM_CYCLE_MSK              (SRAMC_WTCR_SRAM123RWT)
/**
 * @}
 */

/**
 * @defgroup SRAM_Check_Parameters_Validity SRAM check parameters validity
 * @{
 */
#define IS_SRAM_ERR_OP(x)                                                      \
(   ((x) == SRAM_ERR_OP_NMI)                ||                                 \
    ((x) == SRAM_ERR_OP_RESET))

#define IS_SRAM_CYCLE(x)                                                       \
(   ((x) <= SRAM_WAIT_CYCLE_7))

#define IS_SRAM_ECC_MODE(x)                                                    \
(   ((x) == SRAM_ECC_MODE_INVALID)          ||                                 \
    ((x) == SRAM_ECC_MODE_1)                ||                                 \
    ((x) == SRAM_ECC_MODE_2)                ||                                 \
    ((x) == SRAM_ECC_MODE_3))

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
 * @defgroup SRAM_Global_Functions SRAM Global Functions
 * @{
 */

/**
 * @brief  Initializes SRAM.
 * @param  None
 * @retval None
 */
void SRAM_Init(void)
{
    SET_REG32_BIT(M4_SRAMC->CKSR, SRAM_FLAG_ALL);
}

/**
 * @brief  De-initializes SRAM. Reset the registers of SRAM.
 * @param  None
 * @retval None
 * @note   Call SRAM_WTCR_Unlock to unlock register WTCR and SRAM_CKCR_Unlock to unlock register CKCR first.
 */
void SRAM_DeInit(void)
{
    /* Call SRAM_WTCR_Unlock to unlock register WTCR. */
    DDL_ASSERT(M4_SRAMC->WTPR == SRAM_UNLOCK_CMD);
    /* Call SRAM_CKCR_Unlock to unlock register CKCR. */
    DDL_ASSERT(M4_SRAMC->CKPR == SRAM_UNLOCK_CMD);

    WRITE_REG32(M4_SRAMC->WTCR, 0U);
    WRITE_REG32(M4_SRAMC->CKCR, 0U);
    SET_REG32_BIT(M4_SRAMC->CKSR, SRAM_FLAG_ALL);
}

/**
 * @brief  Set access wait cycle for SRAM(s).
 * @param  [in]  u32SramIndex           The SRAM(s) index bit mask.
 *                                      This parameter can be values of @ref SRAM_Index_Bit_Mask
 *   @arg  SRAM_SRAMH:                  SRAMH.
 *   @arg  SRAM_SRAM123:                SRAM1, SRAM2 and SRAM3. When the CPU clock frequency is higher
 *                                      than 200MHz, access wait cycle is needed.
 *   @arg  SRAM_SRAM4:                  SRAM4. When the CPU clock frequency is higher than 200MHz,
 *                                      access wait cycle is needed.
 *   @arg  SRAM_SRAMB:                  SRAMB. When the CPU clock frequency is higher than 120MHz,
 *                                      access wait cycle is needed.
 * @param  [in]  u32WriteCycle          The write access wait cycle for the specified SRAM(s)
 *                                      This parameter can be a value of @ref SRAM_Access_Wait_Cycle
 *   @arg  SRAM_WAIT_CYCLE_0:           Wait 0 CPU cycle.
 *   @arg  SRAM_WAIT_CYCLE_1:           Wait 1 CPU cycle.
 *   @arg  SRAM_WAIT_CYCLE_2:           Wait 2 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE_3:           Wait 3 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE_4:           Wait 4 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE_5:           Wait 5 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE_6:           Wait 6 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE_7:           Wait 7 CPU cycles.
 * @param  [in]  u32ReadCycle           The read access wait cycle for the specified SRAM(s)
 *                                      This parameter can be a value of @ref SRAM_Access_Wait_Cycle
 *                                      The arguments are same as u32WriteCycle.
 * @retval None
 * @note   Call SRAM_WTCR_Unlock to unlock register WTCR first.
 */
void SRAM_SetWaitCycle(uint32_t u32SramIndex, uint32_t u32WriteCycle, uint32_t u32ReadCycle)
{
    uint8_t i;
    uint8_t u8OfsWt;
    uint8_t u8OfsRd;
    uint32_t au32SramList[4U] = {SRAM_SRAM123, SRAM_SRAM4, SRAM_SRAMH, SRAM_SRAMB};

    DDL_ASSERT(IS_SRAM_CYCLE(u32WriteCycle));
    DDL_ASSERT(IS_SRAM_CYCLE(u32ReadCycle));
    DDL_ASSERT(M4_SRAMC->WTPR == SRAM_UNLOCK_CMD);

    for (i=0U; i<4U; i++)
    {
        if ((u32SramIndex & au32SramList[i]) != 0U)
        {
            u8OfsWt = i << 3U;
            u8OfsRd = u8OfsWt + 4U;
            MODIFY_REG32(M4_SRAMC->WTCR,
                         ((SRAM_CYCLE_MSK << u8OfsWt) | (SRAM_CYCLE_MSK << u8OfsRd)),
                         ((u32WriteCycle << u8OfsWt) | (u32ReadCycle << u8OfsRd)));
        }
    }
}

/**
 * @brief  Set ECC mode for SRAM4 and SRAMB.
 * @param  [in]  u32SramIndex           The SRAM(s) index bit mask.This function is used to set the
 *                                      ECC mode of SRAM4 and SRAMB, so u32SramIndex must contain
 *                                      SRAM_SRAM4 or SRAM_SRAMB or both, from @ref SRAM_Index_Bit_Mask
 * @param  [in]  u32EccMode             The ECC mode of SRAM4 and SRAMB.
 *                                      This parameter can be a value of @ref SRAM_ECC_Mode
 *   @arg  SRAM_ECC_MODE_INVALID:       The ECC mode is invalid.
 *   @arg  SRAM_ECC_MODE_1:             When 1-bit error occurred:
 *                                      ECC error corrects.
 *                                      No 1-bit-error status flag setting, no interrupt or reset.
 *                                      When 2-bit error occurred:
 *                                      ECC error detects.
 *                                      2-bit-error status flag sets and interrupt or reset occurred.
 *   @arg  SRAM_ECC_MODE_2:             When 1-bit error occurred:
 *                                      ECC error corrects.
 *                                      1-bit-error status flag sets, no interrupt or reset.
 *                                      When 2-bit error occurred:
 *                                      ECC error detects.
 *                                      2-bit-error status flag sets and interrupt or reset occurred.
 *   @arg  SRAM_ECC_MODE_3:             When 1-bit error occurred:
 *                                      ECC error corrects.
 *                                      1-bit-error status flag sets and interrupt or reset occurred.
 *                                      When 2-bit error occurred:
 *                                      ECC error detects.
 *                                      2-bit-error status flag sets and interrupt or reset occurred.
 * @retval None
 * @note   Call SRAM_CKCR_Unlock to unlock register CKCR first.
 */
void SRAM_SetEccMode(uint32_t u32SramIndex, uint32_t u32EccMode)
{
    DDL_ASSERT(IS_SRAM_ECC_MODE(u32EccMode));
    DDL_ASSERT(M4_SRAMC->CKPR == SRAM_UNLOCK_CMD);

    if ((u32SramIndex & SRAM_SRAM4) != 0U)
    {
        MODIFY_REG32(M4_SRAMC->CKCR, SRAM_ECC_MODE_MSK, u32EccMode);
    }

    if ((u32SramIndex & SRAM_SRAMB) != 0U)
    {
        MODIFY_REG32(M4_SRAMC->CKCR, SRAM_ECC_MODE_MSK<<2U, u32EccMode);
    }
}

/**
 * @brief  Set the operation which is operated after check error occurred.
 * @param  [in]  u32SramIndex           The SRAM(s) index bit mask.
 *                                      This parameter can be values of @ref SRAM_Index_Bit_Mask
 *   @arg  SRAM_SRAMH:                  SRAMH.
 *   @arg  SRAM_SRAM123:                SRAM1, SRAM2 and SRAM3.
 *   @arg  SRAM_SRAM4:                  SRAM4.
 *   @arg  SRAM_SRAMB:                  SRAMB.
 * @param  [out] u32OpAfterError        The operation after check error occurred.
 *                                      This parameter can be a value of @ref SRAM_Operation_After_Check_Error
 *   @arg  SRAM_ERR_OP_NMI:             Check error generates NMI(non-maskable interrupt).
 *   @arg  SRAM_ERR_OP_RESET:           Check error generates system reset.
 * @retval None
 * @note   Call SRAM_CKCR_Unlock to unlock register CKCR first.
 */
void SRAM_SetErrOperation(uint32_t u32SramIndex, uint32_t u32OpAfterError)
{
    DDL_ASSERT(IS_SRAM_ERR_OP(u32OpAfterError));
    DDL_ASSERT(M4_SRAMC->CKPR == SRAM_UNLOCK_CMD);

    if ((u32SramIndex & (SRAM_SRAM123 | SRAM_SRAMH)) != 0U)
    {
        WRITE_REG32(bM4_SRAMC->CKCR_b.PYOAD, u32OpAfterError);
    }

    if ((u32SramIndex & SRAM_SRAM4) != 0U)
    {
        WRITE_REG32(bM4_SRAMC->CKCR_b.ECCOAD, u32OpAfterError);
    }

    if ((u32SramIndex & SRAM_SRAMB) != 0U)
    {
        WRITE_REG32(bM4_SRAMC->CKCR_b.BECCOAD, u32OpAfterError);
    }
}

/**
 * @brief  Get the status of the specified flag of SRAM.
 * @param  [in]  u32Flag                The flag of SRAM.
 *                                      This parameter can be a value of @ref SRAM_Check_Status_Flag
 *   @arg  SRAM_FLAG_SRAM1_PYERR:       SRAM1 parity error.
 *   @arg  SRAM_FLAG_SRAM2_PYERR:       SRAM2 parity error.
 *   @arg  SRAM_FLAG_SRAM3_PYERR:       SRAM3 parity error.
 *   @arg  SRAM_FLAG_SRAMH_PYERR:       SRAMH parity error.
 *   @arg  SRAM_FLAG_SRAM4_1ERR:        SRAM4 ECC 1-bit error.
 *   @arg  SRAM_FLAG_SRAM4_2ERR:        SRAM4 ECC 2-bit error.
 *   @arg  SRAM_FLAG_SRAMB_1ERR:        SRAMB ECC 1-bit error.
 *   @arg  SRAM_FLAG_SRAMB_2ERR:        SRAMB ECC 2-bit error.
 *   @arg  SRAM_FLAG_CACHE_PYERR:       Cache RAM parity error.
 * @retval An en_flag_status_t enumeration type value.
 *   @arg  Set:                         The specified flag is set.
 *   @arg  Reset:                       The specified flag is not set.
 */
en_flag_status_t SRAM_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlag = Reset;

    if (READ_REG32_BIT(M4_SRAMC->CKSR, (u32Flag & SRAM_FLAG_ALL)) != 0U)
    {
        enFlag = Set;
    }

    return enFlag;
}

/**
 * @brief  Clear the status of the specified flag of SRAM.
 * @param  [in]  u32Flag                The flag of SRAM.
 *                                      This parameter can be a value(s) of @ref SRAM_Check_Status_Flag
 *   @arg  SRAM_FLAG_SRAM1_PYERR:       SRAM1 parity error.
 *   @arg  SRAM_FLAG_SRAM2_PYERR:       SRAM2 parity error.
 *   @arg  SRAM_FLAG_SRAM3_PYERR:       SRAM3 parity error.
 *   @arg  SRAM_FLAG_SRAMH_PYERR:       SRAMH parity error.
 *   @arg  SRAM_FLAG_SRAM4_1ERR:        SRAM4 ECC 1-bit error.
 *   @arg  SRAM_FLAG_SRAM4_2ERR:        SRAM4 ECC 2-bit error.
 *   @arg  SRAM_FLAG_SRAMB_1ERR:        SRAMB ECC 1-bit error.
 *   @arg  SRAM_FLAG_SRAMB_2ERR:        SRAMB ECC 2-bit error.
 *   @arg  SRAM_FLAG_CACHE_PYERR:       Cache RAM parity error.
 * @retval None
 */
void SRAM_ClrStatus(uint32_t u32Flag)
{
    SET_REG32_BIT(M4_SRAMC->CKSR, (u32Flag & SRAM_FLAG_ALL));
}

/**
 * @}
 */

#endif /* DDL_SRAM_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
