/**
 *******************************************************************************
 * @file  hc32_ll_sram.c
 * @brief This file provides firmware functions to manage the SRAM.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Deleted redundant comments
   2023-06-30       CDT             API fixed: SRAM_ClearStatus()
   2023-09-30       CDT             API fixed: SRAM_SetWaitCycle()
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
#include "hc32_ll_sram.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_SRAM SRAM
 * @brief SRAM Driver Library
 * @{
 */

#if (LL_SRAM_ENABLE == DDL_ON)

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
#define SRAM_ECC_MD_MASK            (SRAMC_CKCR_ECCMOD)
#define SRAM_CYCLE_MASK             (0x00000007UL)
/**
 * @}
 */

/**
 * @defgroup SRAM_Check_Parameters_Validity SRAM check parameters validity
 * @{
 */
#define IS_SRAM_BIT_MASK(x, mask)   (((x) != 0U) && (((x) | (mask)) == (mask)))

#define IS_SRAM_ERR_MD(x)           (((x) == SRAM_ERR_MD_NMI) || ((x) == SRAM_ERR_MD_RST))

#define IS_SRAM_WAIT_CYCLE(x)       ((x) <= SRAM_WAIT_CYCLE7)

#define IS_SRAM_SEL(x)              IS_SRAM_BIT_MASK(x, SRAM_SRAM_ALL)

#define IS_SRAM_ECC_SRAM(x)         IS_SRAM_BIT_MASK(x, SRAM_ECC_SRAM4 | SRAM_ECC_SRAMB)

#define IS_SRAM_FLAG(x)             IS_SRAM_BIT_MASK(x, SRAM_FLAG_ALL)

#define IS_SRAM_WTPR_UNLOCK()       (CM_SRAMC->WTPR == SRAM_REG_UNLOCK_KEY)

#define IS_SRAM_CKPR_UNLOCK()       (CM_SRAMC->CKPR == SRAM_REG_UNLOCK_KEY)

#define IS_SRAM_ECC_MD(x)                                                      \
(   ((x) == SRAM_ECC_MD_INVD)               ||                                 \
    ((x) == SRAM_ECC_MD1)                   ||                                 \
    ((x) == SRAM_ECC_MD2)                   ||                                 \
    ((x) == SRAM_ECC_MD3))

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
    SET_REG32_BIT(CM_SRAMC->CKSR, SRAM_FLAG_ALL);
}

/**
 * @brief  De-initializes SRAM. RESET the registers of SRAM.
 * @param  None
 * @retval None
 * @note   Call SRAM_REG_Unlock to unlock registers WTCR and CKCR first.
 */
void SRAM_DeInit(void)
{
    /* Call SRAM_REG_Unlock to unlock register WTCR and CKCR. */
    DDL_ASSERT(IS_SRAM_WTPR_UNLOCK());
    DDL_ASSERT(IS_SRAM_CKPR_UNLOCK());

    WRITE_REG32(CM_SRAMC->WTCR, 0U);
    WRITE_REG32(CM_SRAMC->CKCR, 0U);
    SET_REG32_BIT(CM_SRAMC->CKSR, SRAM_FLAG_ALL);
}

/**
 * @brief  Specifies access wait cycle for SRAM.
 * @param  [in]  u32SramSel             The SRAM selection.
 *                                      This parameter can be values of @ref SRAM_Sel
 * @param  [in]  u32WriteCycle          The write access wait cycle for the specified SRAM
 *                                      This parameter can be a value of @ref SRAM_Access_Wait_Cycle
 * @param  [in]  u32ReadCycle           The read access wait cycle for the specified SRAM.
 *                                      This parameter can be a value of @ref SRAM_Access_Wait_Cycle
 *   @arg  SRAM_WAIT_CYCLE0:            Wait 0 CPU cycle.
 *   @arg  SRAM_WAIT_CYCLE1:            Wait 1 CPU cycle.
 *   @arg  SRAM_WAIT_CYCLE2:            Wait 2 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE3:            Wait 3 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE4:            Wait 4 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE5:            Wait 5 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE6:            Wait 6 CPU cycles.
 *   @arg  SRAM_WAIT_CYCLE7:            Wait 7 CPU cycles.
 * @retval None
 * @note   Call SRAM_REG_Unlock to unlock register WTCR first.
 */
void SRAM_SetWaitCycle(uint32_t u32SramSel, uint32_t u32WriteCycle, uint32_t u32ReadCycle)
{
    uint8_t i = 0U;
    uint8_t u8OfsWt;
    uint8_t u8OfsRd;

    DDL_ASSERT(IS_SRAM_SEL(u32SramSel));
    DDL_ASSERT(IS_SRAM_WAIT_CYCLE(u32WriteCycle));
    DDL_ASSERT(IS_SRAM_WAIT_CYCLE(u32ReadCycle));
    DDL_ASSERT(IS_SRAM_WTPR_UNLOCK());

    while (u32SramSel != 0UL) {
        if ((u32SramSel & 0x1UL) != 0UL) {
            u8OfsRd = i * 8U;
            u8OfsWt = u8OfsRd + 4U;
            MODIFY_REG32(CM_SRAMC->WTCR,
                         ((SRAM_CYCLE_MASK << u8OfsWt) | (SRAM_CYCLE_MASK << u8OfsRd)),
                         ((u32WriteCycle << u8OfsWt) | (u32ReadCycle << u8OfsRd)));
        }
        u32SramSel >>= 1U;
        i++;
    }
}

/**
 * @brief  Specifies ECC mode.
 * @param  [in]  u32SramSel             The SRAM selection. This function is used to specify the
 *                                      ECC mode for members SRAM_ECC_XXXX of @ref SRAM_Sel
 * @param  [in]  u32EccMode             The ECC mode.
 *                                      This parameter can be a value of @ref SRAM_ECC_Mode
 *   @arg  SRAM_ECC_MD_INVD:            The ECC mode is invalid.
 *   @arg  SRAM_ECC_MD1:                When 1-bit error occurred:
 *                                      ECC error corrects.
 *                                      No 1-bit-error status flag setting, no interrupt or reset.
 *                                      When 2-bit error occurred:
 *                                      ECC error detects.
 *                                      2-bit-error status flag sets and interrupt or reset occurred.
 *   @arg  SRAM_ECC_MD2:                When 1-bit error occurred:
 *                                      ECC error corrects.
 *                                      1-bit-error status flag sets, no interrupt or reset.
 *                                      When 2-bit error occurred:
 *                                      ECC error detects.
 *                                      2-bit-error status flag sets and interrupt or reset occurred.
 *   @arg  SRAM_ECC_MD3:                When 1-bit error occurred:
 *                                      ECC error corrects.
 *                                      1-bit-error status flag sets and interrupt or reset occurred.
 *                                      When 2-bit error occurred:
 *                                      ECC error detects.
 *                                      2-bit-error status flag sets and interrupt or reset occurred.
 * @retval None
 * @note   Call SRAM_REG_Unlock to unlock register CKCR first.
 */
void SRAM_SetEccMode(uint32_t u32SramSel, uint32_t u32EccMode)
{
    DDL_ASSERT(IS_SRAM_ECC_SRAM(u32SramSel));
    DDL_ASSERT(IS_SRAM_ECC_MD(u32EccMode));
    DDL_ASSERT(IS_SRAM_CKPR_UNLOCK());

    if ((u32SramSel & SRAM_SRAM4) != 0U) {
        MODIFY_REG32(CM_SRAMC->CKCR, SRAM_ECC_MD_MASK, u32EccMode);
    }

    if ((u32SramSel & SRAM_SRAMB) != 0U) {
        MODIFY_REG32(CM_SRAMC->CKCR, SRAM_ECC_MD_MASK << 2U, u32EccMode << 2U);
    }
}

/**
 * @brief  Specifies the operation which is operated after check error occurred.
 * @param  [in]  u32SramSel             The SRAM selection.
 *                                      This parameter can be values of @ref SRAM_Sel
 * @param  [out] u32ErrMode             The operation after check error occurred.
 *                                      This parameter can be a value of @ref SRAM_Err_Mode
 *   @arg  SRAM_ERR_MD_NMI:             Check error generates NMI(non-maskable interrupt).
 *   @arg  SRAM_ERR_MD_RST:             Check error generates system reset.
 * @retval None
 * @note   Call SRAM_REG_Unlock to unlock register CKCR first.
 */
void SRAM_SetErrorMode(uint32_t u32SramSel, uint32_t u32ErrMode)
{
    DDL_ASSERT(IS_SRAM_SEL(u32SramSel));
    DDL_ASSERT(IS_SRAM_ERR_MD(u32ErrMode));
    DDL_ASSERT(IS_SRAM_CKPR_UNLOCK());

    if ((u32SramSel & (SRAM_SRAM123 | SRAM_SRAMH)) != 0U) {
        WRITE_REG32(bCM_SRAMC->CKCR_b.PYOAD, u32ErrMode);
    }

    if ((u32SramSel & SRAM_SRAM4) != 0U) {
        WRITE_REG32(bCM_SRAMC->CKCR_b.ECCOAD, u32ErrMode);
    }

    if ((u32SramSel & SRAM_SRAMB) != 0U) {
        WRITE_REG32(bCM_SRAMC->CKCR_b.BECCOAD, u32ErrMode);
    }
}

/**
 * @brief  Get the status of the specified flag of SRAM.
 * @param  [in]  u32Flag                The flag of SRAM.
 *                                      This parameter can be a value of @ref SRAM_Err_Status_Flag
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t SRAM_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enStatus = RESET;

    DDL_ASSERT(IS_SRAM_FLAG(u32Flag));
    if (READ_REG32_BIT(CM_SRAMC->CKSR, u32Flag) != 0U) {
        enStatus = SET;
    }

    return enStatus;
}

/**
 * @brief  Clear the status of the specified flag of SRAM.
 * @param  [in]  u32Flag                The flag of SRAM.
 *                                      This parameter can be values of @ref SRAM_Err_Status_Flag
 * @retval None
 */
void SRAM_ClearStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_SRAM_FLAG(u32Flag));
    WRITE_REG32(CM_SRAMC->CKSR, u32Flag);
}

/**
 * @}
 */

#endif /* LL_SRAM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
