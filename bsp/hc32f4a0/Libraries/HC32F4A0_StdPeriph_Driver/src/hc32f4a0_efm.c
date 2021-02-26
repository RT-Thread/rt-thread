/**
 *******************************************************************************
 * @file  hc32f4a0_efm.c
 * @brief This file provides firmware functions to manage the Embedded Flash
 *        Memory unit (EFM).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Heqb           First version
   2020-07-03       Heqb           Add flag judgment when operate SWAP
   2020-07-07       Heqb           Add flag judgment for EFM_SetOperateMode function
   2020-08-11       Heqb           1.Refine function EFM_SequenceProgram()
                                   2.Typo
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
#include "hc32f4a0_efm.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_EFM EFM
 * @brief Embedded Flash Management Driver Library
 * @{
 */

#if (DDL_EFM_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EFM_Local_Macros EFM Local Macros
 * @{
 */
#define SECTOR_SIZE                  (0x2000UL)
#define REG_LENGTH                   (32U)
#define OTP_LOCK_ADDR_START          (0x03001800UL)
#define OTP_LOCK_ADDR_END            (0x03001AD7UL)
#define OTP_ENABLE_ADDR              (0x03001AD8UL)
#define EFM_PGM_TIMEOUT              (HCLK_VALUE / 20000UL)   /* EFM Program timeout */
#define EFM_ERASE_TIMEOUT            (HCLK_VALUE / 20UL)      /* EFM Erase timeout */
#define EFM_SEQ_PGM_TIMEOUT          (HCLK_VALUE / 2000000UL) /* EFM Sequence Program timeout */
/**
 * @defgroup EFM_Configuration_Bit_Mask EFM Configuration Bit Mask
 * @{
 */
#define EFM_CLR_FLAG_MASK      (EFM_FLAG_CLR_OTPWERR0 | EFM_FLAG_CLR_PRTWERR0 | EFM_FLAG_CLR_PGSZERR0 | \
                                EFM_FLAG_CLR_MISMTCH0 | EFM_FLAG_CLR_OPTEND0  | EFM_FLAG_CLR_CLOLERR0 | \
                                EFM_FLAG_CLR_PRTWERR1 | EFM_FLAG_CLR_PGSZERR1 | EFM_FLAG_CLR_MISMTCH1 | \
                                EFM_FLAG_CLR_OPTEND1  | EFM_FLAG_CLR_CLOLERR1)

#define EFM_CACHE_MASK         (EFM_FRMC_CRST | EFM_FRMC_PREFE | EFM_FRMC_DCACHE | EFM_FRMC_ICACHE)

#define EFM_FLAG_MASK          (EFM_FLAG_OTPWERR0 | EFM_FLAG_PRTWERR0 | EFM_FLAG_PGSZERR0 | \
                                EFM_FLAG_MISMTCH0 | EFM_FLAG_OPTEND0  | EFM_FLAG_CLOLERR0 | \
                                EFM_FLAG_PRTWERR1 | EFM_FLAG_PGSZERR1 | EFM_FLAG_MISMTCH1 | \
                                EFM_FLAG_OPTEND1  | EFM_FLAG_CLOLERR1 | EFM_FLAG_RDY0 | EFM_FLAG_RDY1)

/**
 * @}
 */

/**
 * @defgroup EFM_Check_Parameters_Validity EFM Check Parameters Validity
 * @{
 */

/*! Parameter validity check for flash latency. */
#define IS_VALID_EFM_WAIT_CYCLE(x)         ((x) <= EFM_WAIT_CYCLE_15)

/*! Parameter validity check for operate mode. */
#define IS_VALID_EFM_OPERATE_MD(x)                                   \
(   ((x) == EFM_MODE_PROGRAMSINGLE)   ||                             \
    ((x) == EFM_MODE_PROGRAMREADBACK) ||                             \
    ((x) == EFM_MODE_PROGRAMSEQUENCE) ||                             \
    ((x) == EFM_MODE_ERASESECTOR)     ||                             \
    ((x) == EFM_MODE_ERASECHIP1)      ||                             \
    ((x) == EFM_MODE_ERASEFULL)       ||                             \
    ((x) == EFM_MODE_READONLY))

/*! Parameter validity check for flash interrupt select. */
#define IS_VALID_EFM_INT_SEL(x)       (((x) | EFM_INT_MASK) == EFM_INT_MASK)

/*! Parameter validity check for flash flag. */
#define IS_VALID_EFM_FLAG(x)          (((x) | EFM_FLAG_MASK) == EFM_FLAG_MASK)

/*! Parameter validity check for flash clear flag. */
#define IS_VALID_EFM_CLRFLAG(x)       (((x) | EFM_CLR_FLAG_MASK) == EFM_CLR_FLAG_MASK)

/*! Parameter validity check for bus status while flash program or erase. */
#define IS_VALID_EFM_BUS_STATUS(x)                                   \
(   ((x) == EFM_BUS_BUSY)              ||                            \
    ((x) == EFM_BUS_RELEASE))

/*! Parameter validity check for efm data cache reset function. */
#define IS_VALID_EFM_CACHERST_FUNC(x)                                \
(   ((x) == EFM_CACHERST_ON)           ||                            \
    ((x) == EFM_CACHERST_OFF))

/*! Parameter validity check for efm prefetch function. */
#define IS_VALID_EFM_PREFETCH_FUNC(x)                                \
(   ((x) == EFM_PREFETCH_ON)           ||                            \
    ((x) == EFM_PREFETCH_OFF))

/*! Parameter validity check for efm data cache function. */
#define IS_VALID_EFM_DCHEEN_FUNC(x)                                  \
(   ((x) == EFM_DATACACHE_ON)          ||                            \
    ((x) == EFM_DATACACHE_OFF))

/*! Parameter validity check for efm instruction cache function. */
#define IS_VALID_EFM_ICHEEN_FUNC(x)                                  \
(   ((x) == EFM_INSCACHE_ON)           ||                            \
    ((x) == EFM_INSCACHE_OFF))

/*! Parameter validity check for efm status. */
#define IS_VALID_EFM_STATUS(x)                                       \
(   ((x) == EFM_FLASH0_ACT_FLASH1_ACT)     ||                        \
    ((x) == EFM_FLASH0_STP_FLASH1_ACT)     ||                        \
    ((x) == EFM_FLASH0_ACT_FLASH1_STP)     ||                        \
    ((x) == EFM_FLASH0_STP_FLASH1_STP))

/*! Parameter validity check for efm address. */
#define IS_VALID_EFM_ADDR(x)                                         \
(   ((x) <= EFM_END_ADDR)              ||                            \
    (((x) >= EFM_OTP_BLOCK16) && ((x) <= EFM_OTP_BLOCK181)))

/*! Parameter validity check for efm chip erase address. */
#define IS_VALID_EFM_CHIP_ERASE_ADDR(x)          ((x) <= EFM_END_ADDR)

/*! Parameter validity check for sector protected register locking. */
#define IS_VALID_EFM_REG_LOCK(x)                       ((x) <= 0xFFU)

/*! Parameter validity check for efm protect register . */
#define IS_VALID_EFM_PRTREG(x)                                       \
(   ((x) == EFM_PROTECT_FWMC)          ||                            \
    ((x) == EFM_PROTECT_OTP))

/*! Parameter validity check for efm chip . */
#define IS_VALID_EFM_CHIP(x)    (((x) | EFM_FLASH0_STP_FLASH1_STP) == EFM_FLASH0_STP_FLASH1_STP)

/*! Parameter validity check for efm read mode . */
#define IS_VALID_EFM_LVREAD_MODE(x)                                  \
(   ((x) == EFM_LOWVOLREAD_ON)         ||                            \
    ((x) == EFM_LOWVOLREAD_OFF))

/*! Parameter validity check for efm erase mode . */
#define IS_VALID_EFM_ERASE_MODE(x)                                   \
(   ((x) == EFM_MODE_ERASECHIP1)       ||                            \
    ((x) == EFM_MODE_ERASEFULL))

/*! Parameter validity check for efm address alignment . */
#define IS_VALID_EFM_ADDR_ALIGNMENT(x)    (((x) | 0xFFFFFFFCUL) == 0xFFFFFFFCUL)

/*! Parameter validity check for efm sector . */
#define IS_VALID_EFM_SECTOR(x)            ((x) <= EFM_SECTOR_255)

/*! Parameter validity check for EFM lock status. */
#define IS_VALID_EFM_UNLOCK()             (M4_EFM->FAPRT == 0x00000001UL)

/*! Parameter validity check for EFM_FWMC register lock status. */
#define IS_VALID_EFM_FWMC_UNLOCK()        (bM4_EFM->FWMC_b.KEY1LOCK == 0U)

/*! Parameter validity check for OTP lock status. */
#define IS_VALID_EFM_OTP_UNLOCK()         (bM4_EFM->FWMC_b.KEY2LOCK == 0U)

/*! Parameter validity check for EFM sector number */
#define IS_VALID_EFM_SECTOR_NUM(x)         ((x) <= 256U)
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
 * @defgroup EFM_Global_Functions EFM Global Functions
 * @{
 */

/**
 * @brief  EFM_FWMC register unlock.
 * @param  None
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_FWMC_Unlock(void)
{
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    WRITE_REG32(M4_EFM->KEY1, 0x01234567UL);
    WRITE_REG32(M4_EFM->KEY1, 0xFEDCBA98UL);
}

/**
 * @brief  EFM_FWMC register lock.
 * @param  None
 * @retval None
 * @note   Call EFM_Unlock() and EFM_FWMC_Unlock() unlock EFM_FWMC register first.
 */
void EFM_FWMC_Lock(void)
{
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_FWMC_UNLOCK());

    SET_REG32_BIT(M4_EFM->FWMC, EFM_FWMC_KEY1LOCK);
}

/**
 * @brief  EFM OTP operate unlock.
 * @param  None
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_OTP_WP_Unlock(void)
{
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    WRITE_REG32(M4_EFM->KEY2, 0x10325476UL);
    WRITE_REG32(M4_EFM->KEY2, 0xEFCDAB89UL);
}

/**
 * @brief  EFM OTP write protect lock.
 * @param  None
 * @retval None
 * @note   Call EFM_Unlock() and EFM_FWMC_Unlock() unlock OTP write protect first.
 */
void EFM_OTP_WP_Lock(void)
{
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_FWMC_UNLOCK());

    SET_REG32_BIT(M4_EFM->FWMC, EFM_FWMC_KEY2LOCK);
}

/**
 * @brief  Enable or disable EFM.
 * @param  [in] u32EfmStatus            Specifies the flash Chip.
 *   @arg  EFM_FLASH0_ACT_FLASH1_ACT:   Flash 0 and 1 activity 0
 *   @arg  EFM_FLASH0_STP_FLASH1_ACT:   Flash 0 stop,Flash 1 activity
 *   @arg  EFM_FLASH0_ACT_FLASH1_STP:   Flash 0 activity,Flash 1 stop
 *   @arg  EFM_FLASH0_STP_FLASH1_STP:   Flash 0 and 1 stop
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_Cmd(uint32_t u32EfmStatus)
{
    DDL_ASSERT(IS_VALID_EFM_STATUS(u32EfmStatus));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    WRITE_REG32(M4_EFM->FSTP, u32EfmStatus);
}

/**
 * @brief  Init efm config structure with default value.
 * @param  [in] pstcEfmCfg          The pointer of efm config structure.
 *   @arg  u32WaitCycle:            Specifies the efm read wait cycles.
 *   @arg  u32Prefetch:             Specifies the prefetch on or off.
 *   @arg  u32CacheRst:             Specifies the data cache reset on or off.
 *   @arg  u32InsCache:             Specifies the instruction cache on or off.
 *   @arg  u32DataCache:            Specifies the data cache on or off.
 *   @arg  u32LowVolRead:           Specifies the read of low-voltage mode on or off.
 *   @arg  u32BusStatus:            Specifies the bus status busy or release while program & erase.
 *   @arg  u32OperateMode:          Specifies the operate mode.
 *   @arg  u32FlashStatus:          Specifies the Flash status.
 * @retval An en_result_t enumeration value:
 *         - Ok: Initialize successfully
 *         - ErrorInvalidParameter: Invalid parameter
 */
en_result_t EFM_StructInit(stc_efm_cfg_t *pstcEfmCfg)
{
    en_result_t enRet = Ok;

    /* Check if pointer is NULL */
    if (NULL == pstcEfmCfg)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Configure to default value */
        pstcEfmCfg->u32WaitCycle   = EFM_WAIT_CYCLE_0;
        pstcEfmCfg->u32Prefetch    = EFM_PREFETCH_OFF;
        pstcEfmCfg->u32CacheRst    = EFM_CACHERST_OFF;
        pstcEfmCfg->u32InsCache    = EFM_INSCACHE_OFF;
        pstcEfmCfg->u32DataCache   = EFM_DATACACHE_OFF;
        pstcEfmCfg->u32LowVolRead  = EFM_LOWVOLREAD_OFF;
        pstcEfmCfg->u32BusStatus   = EFM_BUS_BUSY;
        pstcEfmCfg->u32OperateMode = EFM_MODE_READONLY;
        pstcEfmCfg->u32FlashStatus = EFM_FLASH0_ACT_FLASH1_ACT;
    }

    return enRet;
}


/**
 * @brief  Efm initialize.
 * @param  [in] pstcEfmCfg          The pointer of efm config structure.
 *   @arg  u32WaitCycle:            Specifies the efm read wait cycles.
 *   @arg  u32Prefetch:             Specifies the prefetch on or off.
 *   @arg  u32CacheRst:             Specifies the data cache reset on or off.
 *   @arg  u32InsCache:             Specifies the instruction cache on or off.
 *   @arg  u32DataCache:            Specifies the data cache on or off.
 *   @arg  u32LowVolRead:           Specifies the read of low-voltage mode on or off.
 *   @arg  u32BusStatus:            Specifies the bus status busy or release while program & erase.
 *   @arg  u32OperateMode:          Specifies the operate mode.
 *   @arg  u32FlashStatus:          Specifies the Flash status.
 * @retval An en_result_t enumeration value:
 *         - Ok: Configure success
 *         - ErrorInvalidParameter: Invalid parameter
 * @note   Call EFM_Unlock() and EFM_FWMC_Unlock() unlock EFM_FWMC register first.
 */
en_result_t EFM_Init(const stc_efm_cfg_t *pstcEfmCfg)
{
    en_result_t enRet = Ok;
    uint32_t u32Temp;
    /* Check if pointer is NULL */
    if (NULL == pstcEfmCfg)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Param valid check */
        DDL_ASSERT(IS_VALID_EFM_UNLOCK());
        DDL_ASSERT(IS_VALID_EFM_FWMC_UNLOCK());
        DDL_ASSERT(IS_VALID_EFM_WAIT_CYCLE(pstcEfmCfg->u32WaitCycle));
        DDL_ASSERT(IS_VALID_EFM_BUS_STATUS(pstcEfmCfg->u32BusStatus));
        DDL_ASSERT(IS_VALID_EFM_CACHERST_FUNC(pstcEfmCfg->u32CacheRst));
        DDL_ASSERT(IS_VALID_EFM_PREFETCH_FUNC(pstcEfmCfg->u32Prefetch));
        DDL_ASSERT(IS_VALID_EFM_DCHEEN_FUNC(pstcEfmCfg->u32DataCache));
        DDL_ASSERT(IS_VALID_EFM_ICHEEN_FUNC(pstcEfmCfg->u32InsCache));
        DDL_ASSERT(IS_VALID_EFM_LVREAD_MODE(pstcEfmCfg->u32LowVolRead));
        DDL_ASSERT(IS_VALID_EFM_OPERATE_MD(pstcEfmCfg->u32OperateMode));
        DDL_ASSERT(IS_VALID_EFM_STATUS(pstcEfmCfg->u32FlashStatus));

        u32Temp = pstcEfmCfg->u32WaitCycle | pstcEfmCfg->u32InsCache | pstcEfmCfg->u32DataCache | \
                  pstcEfmCfg->u32Prefetch | pstcEfmCfg->u32CacheRst | pstcEfmCfg->u32LowVolRead;
        /* Config efm. */
        MODIFY_REG32(M4_EFM->FRMC, EFM_FRMC_FLWT | EFM_FRMC_PREFE | EFM_FRMC_LVM | \
                                   EFM_FRMC_ICACHE | EFM_FRMC_DCACHE | EFM_FRMC_CRST, u32Temp);
        MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_BUSHLDCTL | EFM_FWMC_PEMOD, \
                                    pstcEfmCfg->u32BusStatus | pstcEfmCfg->u32OperateMode);
        MODIFY_REG32(M4_EFM->FSTP, EFM_FSTP_F0STP | EFM_FSTP_F1STP, pstcEfmCfg->u32FlashStatus);
    }

    return enRet;
}

/**
 * @brief  Set the efm read wait cycles.
 * @param  [in] u32WaitCycle            Specifies the efm read wait cycles.
 *  This parameter can be one of the following values:
 *   @arg  EFM_WAIT_CYCLE_0:            Don't insert read wait cycle
 *   @arg  EFM_WAIT_CYCLE_1:            Insert 1 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_2:            Insert 2 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_3:            Insert 3 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_4:            Insert 4 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_5:            Insert 5 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_6:            Insert 6 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_7:            Insert 7 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_8:            Insert 8 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_9:            Insert 9 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_10:           Insert 10 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_11:           Insert 11 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_12:           Insert 12 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_13:           Insert 13 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_14:           Insert 14 read wait cycles
 *   @arg  EFM_WAIT_CYCLE_15:           Insert 15 read wait cycles
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_SetWaitCycle(uint32_t u32WaitCycle)
{
    /* Param valid check */
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_WAIT_CYCLE(u32WaitCycle));
    /* Set the code latency value. */
    MODIFY_REG32(M4_EFM->FRMC, EFM_FRMC_FLWT, u32WaitCycle);
}

/**
 * @brief  Enable or disable the flash data cache reset.
 * @param  [in] enNewState           The new status of the flash data cache reset.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_DataCacheRstCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    WRITE_REG32(bM4_EFM->FRMC_b.CRST, enNewState);
}

/**
 * @brief  Enable or disable the flash prefetch.
 * @param  [in] enNewState                The new state of the flash prefetch.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_PrefetchCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    WRITE_REG32(bM4_EFM->FRMC_b.PREFE, enNewState);
}

/**
 * @brief  Enable or disable the flash data cache.
 * @param  [in] enNewState                The new state of the flash data cache.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_DataCacheCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    WRITE_REG32(bM4_EFM->FRMC_b.DCACHE, enNewState);
}

/**
 * @brief  Enable or disable the flash instruction cache.
 * @param  [in] enNewState                The new state of the flash instruction cache.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_InsCacheCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    WRITE_REG32(bM4_EFM->FRMC_b.ICACHE, enNewState);
}

/**
 * @brief  Enable or disable the Read of low-voltage mode.
 * @param  [in] enNewState                The new state of the flash Low voltage read mode.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_LowVolReadCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    WRITE_REG32(bM4_EFM->FRMC_b.LVM, enNewState);
}

/**
 * @brief  Set the FLASH erase program mode .
 * @param  [in] u32PgmMode                  Specifies the FLASH erase program mode.
 *  This parameter can be one of the following values:
 *   @arg  EFM_MODE_PROGRAMSINGLE:          Program single at a specified address
 *   @arg  EFM_MODE_PROGRAMREADBACK:        Program and read back at a specified address
 *   @arg  EFM_MODE_PROGRAMSEQUENCE:        Program sequence at sequence address
 *   @arg  EFM_MODE_ERASESECTOR:            Sector erase
 *   @arg  EFM_MODE_ERASECHIP1:             A flash Chip erase
 *   @arg  EFM_MODE_ERASEFULL:              Two flash Chip erase
 *   @arg  EFM_MODE_READONLY:               Read only
 * @retval An en_result_t enumeration value:
 *         - Ok: Success
 *         - ErrorTimeout: Process timeout
 * @note   Call EFM_Unlock() and EFM_FWMC_Unlock() unlock EFM_FWMC register first.
 */
en_result_t EFM_SetOperateMode(uint32_t u32PgmMode)
{
    en_result_t enRet = Ok;
    uint32_t u32Timeout = 0UL;
    DDL_ASSERT(IS_VALID_EFM_OPERATE_MD(u32PgmMode));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_FWMC_UNLOCK());
    while ((READ_REG32(M4_EFM->FSR) & 0x01000100UL) != 0x01000100UL)
    {
        u32Timeout ++;
        if (u32Timeout > EFM_SEQ_PGM_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    if (enRet == Ok)
    {
        /* Set the program or erase mode. */
        MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, u32PgmMode);
    }
    return enRet;
}

/**
 * @brief  Enable or Disable EFM interrupt.
 * @param  [in] u32EfmInt               Specifies the FLASH interrupt source and status.
 *   @arg  EFM_INT_OPTEND:              End of EFM Operation Interrupt source
 *   @arg  EFM_INT_PEERR:               Program/erase error Interrupt source
 *   @arg  EFM_INT_RDCOLERR:            Read collide error Interrupt source
 * @param  [in] enNewState              The new state of specified interrupt.
 *  This parameter can be: Enable or Disable.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_InterruptCmd(uint32_t u32EfmInt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_VALID_EFM_INT_SEL(u32EfmInt));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    if(Enable == enNewState)
    {
        SET_REG32_BIT(M4_EFM->FITE, u32EfmInt);
    }
    else
    {
        CLEAR_REG32_BIT(M4_EFM->FITE, u32EfmInt);
    }
}

/**
 * @brief  Checks whether the specified FLASH flag is set or not.
 * @param  [in] u32Flag                    Specifies the FLASH flag to check.
 *   @arg  EFM_FLAG_OTPWERR0:              Flash0 otp Programming/erase error flag.
 *   @arg  EFM_FLAG_PRTWERR0:              Flash0 write protect address error flag.
 *   @arg  EFM_FLAG_PGSZERR0:              Flash0 programming size error flag.
 *   @arg  EFM_FLAG_MISMTCH0:              Flash0 programming missing match error flag.
 *   @arg  EFM_FLAG_OPTEND0:               Flash0 end of operation flag.
 *   @arg  EFM_FLAG_CLOLERR0:              Flash0 read write error flag.
 *   @arg  EFM_FLAG_RDY0:                  Flash0 ready flag.
 *   @arg  EFM_FLAG_PRTWERR1:              Flash1 write protect address error flag.
 *   @arg  EFM_FLAG_PGSZERR1:              Flash1 programming size error flag.
 *   @arg  EFM_FLAG_MISMTCH1:              Flash1 programming missing match error flag.
 *   @arg  EFM_FLAG_OPTEND1:               Flash1 end of operation flag.
 *   @arg  EFM_FLAG_CLOLERR1:              Flash1 read write error flag.
 *   @arg  EFM_FLAG_RDY1:                  Flash1 ready flag.
 * @retval An en_flag_status_t enumeration value:
 *         - Set: flag is set
 *         - Reset: flag is reset
 */
en_flag_status_t EFM_GetFlagStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_VALID_EFM_FLAG(u32Flag));
    return ((0UL == READ_REG32_BIT(M4_EFM->FSR, u32Flag)) ? Reset :Set);
}

/**
 * @brief  Clear the flash flag.
 * @param  [in] u32Flag                  Specifies the FLASH flag to clear.
 *   @arg  EFM_FLAG_CLR_OTPWERR0:        Clear Flash0 otp Programming/erase error flag
 *   @arg  EFM_FLAG_CLR_PRTWERR0:        Clear Flash0 write protect address error flag
 *   @arg  EFM_FLAG_CLR_PGSZERR0:        Clear Flash0 programming size error flag
 *   @arg  EFM_FLAG_CLR_MISMTCH0:        Clear Flash0 programming miss match error flag
 *   @arg  EFM_FLAG_CLR_OPTEND0:         Clear Flash0 end of operation flag
 *   @arg  EFM_FLAG_CLR_CLOLERR0:        Clear Flash0 read collide error flag
 *   @arg  EFM_FLAG_CLR_PRTWERR1:        Clear Flash1 write protect address error flag
 *   @arg  EFM_FLAG_CLR_PGSZERR1:        Clear Flash1 programming size error flag
 *   @arg  EFM_FLAG_CLR_MISMTCH1:        Clear Flash1 programming miss match error flag
 *   @arg  EFM_FLAG_CLR_OPTEND1:         Clear Flash1 end of operation flag
 *   @arg  EFM_FLAG_CLR_CLOLERR1:        Clear Flash1 read collide error flag
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_ClearFlag(uint32_t u32Flag)
{
    DDL_ASSERT(IS_VALID_EFM_CLRFLAG(u32Flag));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    SET_REG32_BIT(M4_EFM->FSCLR, u32Flag);
}

/**
 * @brief  Sector protected register lock.
 * @param  [in] u32EfmRegLock                  Specifies sector protected register locking.
 *  @arg   EFM_WRLOCK0:                        F0NWPRT0 controlled sector lock
 *  @arg   EFM_WRLOCK1:                        F0NWPRT1 controlled sector lock
 *  @arg   EFM_WRLOCK2:                        F0NWPRT2 controlled sector lock
 *  @arg   EFM_WRLOCK3:                        F0NWPRT3 controlled sector lock
 *  @arg   EFM_WRLOCK4:                        F1NWPRT0 controlled sector lock
 *  @arg   EFM_WRLOCK5:                        F1NWPRT1 controlled sector lock
 *  @arg   EFM_WRLOCK6:                        F1NWPRT2 controlled sector lock
 *  @arg   EFM_WRLOCK7:                        F1NWPRT3 controlled sector lock
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
void EFM_SectorRegLock(uint32_t u32EfmRegLock)
{
    DDL_ASSERT(IS_VALID_EFM_REG_LOCK(u32EfmRegLock));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    SET_REG32_BIT(M4_EFM->WLOCK, u32EfmRegLock);
}

/**
 * @brief  Set sector lock or unlock (Single).
 * @param  [in] u8SectorNum                   Specifies sector for unlock.
 *  This parameter can be set 0~255
 * @param  [in] enNewState                    The new status of specified sector lock or unlock.
 *  This parameter can be: Enable or Disable.
 * @retval None
 * @note   Call EFM_Unlock() unlock EFM register first.
 *         If you want to unlock sequential sectors,Please call EFM_SectorCmd_Sequential function
 */
void EFM_SectorCmd_Single(uint8_t u8SectorNum, en_functional_state_t enNewState)
{
    __IO uint32_t *EFM_FxNWPRTy;
    const uint8_t u8RegIndex = u8SectorNum / REG_LENGTH;
    const uint8_t u8BitPos = u8SectorNum % REG_LENGTH;
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    EFM_FxNWPRTy = (__IO uint32_t*)((uint32_t)(&M4_EFM->F0NWPRT0) + ((uint32_t)u8RegIndex << 2UL));
    MODIFY_REG32(*EFM_FxNWPRTy, 1UL<<u8BitPos, (uint32_t)enNewState<<u8BitPos);
}

/**
 * @brief  Set sector lock or unlock (Sequential).
 * @param  [in] u32StartAddr                  Specifies start address for unlock.
 * @param  [in] u16SectorCnt                  Specifies length for unlock.
 *  This parameter can be set 0~256.
 * @param  [in] enNewState                    The new status of specified sector lock or unlock.
 *  This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *         - Ok: Operate successfully.
 *         - ErrorInvalidParameter: Invalid parameter
 * @note   Call EFM_Unlock() unlock EFM register first.
 *         If you want to unlock a sector,Please call EFM_SectorCmd_Single function
 */
en_result_t EFM_SectorCmd_Sequential(uint32_t u32StartAddr, uint16_t u16SectorCnt, en_functional_state_t enNewState)
{
    en_result_t enRet = ErrorInvalidParameter;
    __IO uint32_t *EFM_FxNWPRTy;
    uint32_t StartSect;
    uint32_t EndSect;
    uint32_t EndAddr;
    uint16_t Num;
    uint16_t NeedSector;
    uint16_t StartRegIndex;
    uint16_t StartBitPos;
    uint16_t EndRegIndex;
    uint16_t EndBitPos;
    EndAddr = u32StartAddr + u16SectorCnt * SECTOR_SIZE -1U;
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_SECTOR_NUM(u16SectorCnt));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if(EndAddr < EFM_END_ADDR + SECTOR_SIZE)
    {
        StartSect = (uint16_t)(u32StartAddr / SECTOR_SIZE);            /* Calculate the start sector */
        NeedSector = u16SectorCnt;                                     /* Calculate the required sectors */
        EndSect = (uint16_t)(StartSect + NeedSector - 1U);             /* Calculate the end sector */
        StartRegIndex = (uint16_t)(StartSect / REG_LENGTH);            /* Register offset for the start sector */
        StartBitPos = (uint16_t)(StartSect % REG_LENGTH);              /* Bit offset for the start sector */
        EndRegIndex = (uint16_t)(EndSect / REG_LENGTH);                /* Register offset for the end sector */
        EndBitPos = (uint16_t)(EndSect % REG_LENGTH);                  /* Bit offset for the end sector */

        EFM_FxNWPRTy = (__IO uint32_t*)((uint32_t)(&M4_EFM->F0NWPRT0) + ((uint32_t)StartRegIndex << 2UL));

        if(StartRegIndex == EndRegIndex)
        {
            for(Num = StartBitPos; Num <= EndBitPos; Num++)
            {
                MODIFY_REG32(*EFM_FxNWPRTy,(uint32_t)1UL<<Num,(uint32_t)enNewState<<Num);
            }
        }
        else
        {
            for(Num = StartBitPos; Num < REG_LENGTH; Num++)
            {
                MODIFY_REG32(*EFM_FxNWPRTy,(uint32_t)1UL<<Num,(uint32_t)enNewState<<Num);
            }
            StartRegIndex += 1U;
            EFM_FxNWPRTy = (__IO uint32_t*)((uint32_t)(&M4_EFM->F0NWPRT0) + ((uint32_t)EndRegIndex << 2U));
            for(Num = 0U;Num <= EndBitPos;Num++)
            {
                MODIFY_REG32(*EFM_FxNWPRTy, (uint32_t)1UL<<Num, (uint32_t)enNewState<<Num);
            }

            while(StartRegIndex < EndRegIndex)
            {
                EFM_FxNWPRTy = (__IO uint32_t*)((uint32_t)(&M4_EFM->F0NWPRT0) + ((uint32_t)StartRegIndex << 2U));
                if(enNewState == Enable)
                {
                    WRITE_REG32(*EFM_FxNWPRTy, 0xFFFFFFFFUL);
                }
                else
                {
                    WRITE_REG32(*EFM_FxNWPRTy, 0x0UL);
                }
                StartRegIndex += 1U;
            }
        enRet = Ok;
        }
    }
    return enRet;
}

/**
 * @brief  Set bus status while flash program or erase.
 * @param  [in] u32Status                  Specifies the new bus status while flash program or erase.
 *  This parameter can be one of the following values:
 *   @arg  EFM_BUS_BUSY:                   Bus busy while flash program or erase.
 *   @arg  EFM_BUS_RELEASE:                Bus releas while flash program or erase.
 * @retval None
 * @note   Call EFM_Unlock() and EFM_FWMC_Unlock() unlock EFM_FWMC register first.
 */
void EFM_SetBusStatus(uint32_t u32Status)
{
    DDL_ASSERT(IS_VALID_EFM_BUS_STATUS(u32Status));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_VALID_EFM_FWMC_UNLOCK());

    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_BUSHLDCTL, u32Status);
}

/**
 * @brief  Flash single program mode.
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u32Data                   The specified program data.
 * @retval An en_result_t enumeration value:
 *         - Ok: program success
 *         - Error: program error
 *         - ErrorTimeout: program error timeout
 * @note  The address should be word align.
 *        Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_SingleProgram(uint32_t u32Addr, uint32_t u32Data)
{
    en_result_t enRet = Ok;
    uint32_t u32Timeout = 0UL;
    uint32_t u32tmp;
    uint32_t u32EfmFlag = EFM_FLAG_RDY1;
    uint32_t u32EfmClrFlag = EFM_FLAG_CLR_OPTEND1;

    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_VALID_EFM_ADDR_ALIGNMENT(u32Addr));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    /* Clear the error flag. */
    EFM_ClearFlag(EFM_CLR_FLAG_MASK);
    /* Get CACHE status */
    u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CACHE_MASK);
    /* Disable CACHE function */
    CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CACHE_MASK);
    /* Set single program mode. */
    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_PROGRAMSINGLE);
    /* Program data. */
    RW_MEM32(u32Addr) = (uint32_t)u32Data;
    if((u32Addr < EFM_ADDR_SECTOR128) || (u32Addr >= EFM_OTP_BLOCK16))
    {
        u32EfmFlag = EFM_FLAG_RDY0;
        u32EfmClrFlag = EFM_FLAG_CLR_OPTEND0;
    }
    /* Wait for operation end  */
    while(Set != EFM_GetFlagStatus(u32EfmFlag))
    {
        u32Timeout ++;
        if(u32Timeout >= EFM_PGM_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    if(u32Data != RW_MEM32(u32Addr))
    {
        enRet = Error;
    }
    /* CLear the end of operate flag */
    EFM_ClearFlag(u32EfmClrFlag);
    /* Set read only mode. */
    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_READONLY);
    /* Recover CACHE function */
    MODIFY_REG32(M4_EFM->FRMC, EFM_CACHE_MASK, u32tmp);

    return enRet;
}

/**
 * @brief  Flash single program with read back.
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u32Data                   The specified program data.
 * @retval An en_result_t enumeration value:
 *         - Ok: program success
 *         - Error: program error
 *         - ErrorTimeout: program error timeout
 * @note  The address should be word align.
 *        Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_ProgramReadBack(uint32_t u32Addr, uint32_t u32Data)
{
    en_result_t enRet = Ok;
    uint32_t u32Timeout = 0UL;
    uint32_t u32tmp;
    uint32_t u32EfmFlag = EFM_FLAG_RDY1;
    uint32_t u32EfmClrFlag = EFM_FLAG_CLR_OPTEND1;
    uint32_t u32EfmFlag1 = EFM_FLAG_MISMTCH1;
    uint32_t u32EfmClrFlag1 = EFM_FLAG_CLR_MISMTCH1;

    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_VALID_EFM_ADDR_ALIGNMENT(u32Addr));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    /* Clear the error flag. */
    EFM_ClearFlag(EFM_CLR_FLAG_MASK);
    /* Get CACHE status */
    u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CACHE_MASK);
    /* Disable CACHE */
    CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CACHE_MASK);
    /* Set Program and read back mode. */
    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_PROGRAMREADBACK);
    /* Program data. */
    RW_MEM32(u32Addr) = (uint32_t)u32Data;
    if((u32Addr < EFM_ADDR_SECTOR128) || (u32Addr >= EFM_OTP_BLOCK16))
    {
        u32EfmFlag = EFM_FLAG_RDY0;
        u32EfmClrFlag = EFM_FLAG_CLR_OPTEND0;
        u32EfmFlag1 = EFM_FLAG_MISMTCH0;
        u32EfmClrFlag1 = EFM_FLAG_CLR_MISMTCH0;
    }
    while(Set != EFM_GetFlagStatus(u32EfmFlag))
    {
        u32Timeout ++;
        if(u32Timeout >= EFM_PGM_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    /* Get the flag MISMTCH0*/
    if(Set == EFM_GetFlagStatus(u32EfmFlag1))
    {
        /* Clear flag PGMISMTCH */
        EFM_ClearFlag(u32EfmClrFlag1);
        enRet = Error;
    }
    /* CLear the end of operate flag */
    EFM_ClearFlag(u32EfmClrFlag);
    /* Set read only mode. */
    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_READONLY);
    /* recover CACHE function */
    MODIFY_REG32(M4_EFM->FRMC, EFM_CACHE_MASK, u32tmp);

    return enRet;
}

/**
 * @brief  Flash sequence program.
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u32Len                    The len of specified program data.
 * @param  [in] pu32Buf                   The pointer of specified program data.
 * @retval An en_result_t enumeration value:
 *         - Ok: program success
 *         - ErrorTimeout: program error timeout
 * @note  The address should be word align.
 *        Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_SequenceProgram(uint32_t u32Addr, uint32_t u32Len, const uint32_t *pu32Buf)
{
    en_result_t enRet = Ok;
    uint32_t u32Timeout;
    uint32_t u32tmp;
    uint32_t u32LoopWords = u32Len >> 2UL;
    uint32_t u32EfmFlag = EFM_FLAG_OPTEND0;
    uint32_t u32EfmFlag1 = EFM_FLAG_RDY0;
    uint32_t u32EfmClrFlag = EFM_FLAG_CLR_OPTEND0;
    uint32_t u32SrcDataAddr = (uint32_t)pu32Buf;
    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_VALID_EFM_ADDR_ALIGNMENT(u32Addr));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    /* CLear the error flag. */
    EFM_ClearFlag(EFM_CLR_FLAG_MASK);
    /* Get CACHE status */
    u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CACHE_MASK);
    /* Disable CACHE */
    CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CACHE_MASK);
    /* Set sequence program mode. */
    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_PROGRAMSEQUENCE);
    /* program data. */
    while((u32LoopWords--) > 0UL)
    {
        RW_MEM32(u32Addr) = RW_MEM32(u32SrcDataAddr);
        /* wait operate end. */
        if((u32Addr >= EFM_ADDR_SECTOR128) && (u32Addr < EFM_END_ADDR))
        {
            u32EfmFlag = EFM_FLAG_OPTEND1;
            u32EfmFlag1 = EFM_FLAG_RDY1;
            u32EfmClrFlag = EFM_FLAG_CLR_OPTEND1;
        }
        u32Timeout = 0UL;
        while(Set != EFM_GetFlagStatus(u32EfmFlag))
        {
            if(u32Timeout++ >= EFM_PGM_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        u32Timeout = 0UL;
        /* Clear operation end flag */
        while(Reset != EFM_GetFlagStatus(u32EfmFlag))
        {
            if(u32Timeout++ >= EFM_SEQ_PGM_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
            /* clear end flag. */
            EFM_ClearFlag(u32EfmClrFlag);
        }
        if (enRet != Ok)
        {
            break;
        }
        u32Addr += 4UL;
        u32SrcDataAddr += 4UL;
        if (u32Addr == EFM_ADDR_SECTOR128)
        {
            /* Set read only mode. */
            MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_READONLY);
            u32Timeout = 0UL;
            /* wait for flash ready . */
            while(Set != EFM_GetFlagStatus(u32EfmFlag1))
            {
                u32Timeout ++;
                if(u32Timeout >= EFM_PGM_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
            if (enRet == Ok)
            {
                /* Set sequence program mode. */
                MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_PROGRAMSEQUENCE);
            }
        }
    }
    /* Set read only mode. */
    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_READONLY);
    u32Timeout = 0UL;
    /* wait for flash ready . */
    while(Set != EFM_GetFlagStatus(u32EfmFlag1))
    {
        u32Timeout ++;
        if(u32Timeout >= EFM_PGM_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    /* Recover CACHE */
    MODIFY_REG32(M4_EFM->FRMC, EFM_CACHE_MASK, u32tmp);
    return enRet;
}

/**
 * @brief  Flash sector erase.
 * @param  [in] u32Addr                   The address in the specified sector.
 * @retval An en_result_t enumeration value:
 *         - Ok: erase success
 *         - ErrorTimeout: program error timeout
 * @note   The address should be word align.
 *         Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_SectorErase(uint32_t u32Addr)
{
    en_result_t enRet = Ok;
    uint32_t u32Timeout = 0UL;
    uint32_t u32tmp;
    uint32_t u32EfmFlag = EFM_FLAG_RDY1;
    uint32_t u32EfmClrFlag = EFM_FLAG_CLR_OPTEND1;

    DDL_ASSERT(IS_VALID_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    /* CLear the error flag. */
    EFM_ClearFlag(EFM_CLR_FLAG_MASK);
    /* Get CACHE status */
    u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CACHE_MASK);
    /* Disable CACHE */
    CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CACHE_MASK);
    /* Set sector erase mode. */
    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_ERASESECTOR);
    /* Erase */
    RW_MEM32(u32Addr & 0xFFFFFFFCUL) = (uint32_t)0UL;
    if((u32Addr < EFM_ADDR_SECTOR128) || (u32Addr >= EFM_OTP_BLOCK16))
    {
        u32EfmFlag = EFM_FLAG_RDY0;
        u32EfmClrFlag = EFM_FLAG_CLR_OPTEND0;
    }
    while(Set != EFM_GetFlagStatus(u32EfmFlag))
    {
        u32Timeout ++;
        if(u32Timeout >= EFM_ERASE_TIMEOUT)
        {
            enRet = ErrorTimeout;
            break;
        }
    }
    /* Clear the end of operate flag */
    EFM_ClearFlag(u32EfmClrFlag);
    /* Set read only mode. */
    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_READONLY);
    /* Recover CACHE */
    MODIFY_REG32(M4_EFM->FRMC, EFM_CACHE_MASK, u32tmp);

    return enRet;
}

/**
 * @brief  Flash OTP lock.
 * @param  [in]  u32Addr           Specifies the OTP block
 * @retval An en_result_t enumeration value:
 *         - Ok: program success
 *         - ErrorInvalidParameter: Invalid parameter
 * @note   The address should be word align.
 *         Call EFM_Unlock() and EFM_OTP_WP_Unlock() unlock EFM_FWMC register first.
 */
en_result_t EFM_OTPLock(uint32_t u32Addr)
{
    en_result_t enRet = ErrorInvalidParameter;
    uint32_t u32Timeout = 0UL;

    if((u32Addr >= OTP_LOCK_ADDR_START) && (u32Addr < OTP_LOCK_ADDR_END ))
    {
        DDL_ASSERT(IS_VALID_EFM_UNLOCK());
        DDL_ASSERT(IS_VALID_EFM_OTP_UNLOCK());

        enRet = Ok;
        /* Set single program mode. */
        MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_PROGRAMSINGLE);
        /* Enable OTP */
        RW_MEM32(OTP_ENABLE_ADDR) = (uint32_t)0UL;
        /* Wait for operation end */
        while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY0))
        {
            u32Timeout ++;
            if(u32Timeout >= EFM_PGM_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        /* CLear the end of operate flag */
        EFM_ClearFlag(EFM_FLAG_CLR_OPTEND0);
        if (enRet == Ok)
        {
            /* OTP latch */
            RW_MEM32(u32Addr & 0xFFFFFFFCUL) = (uint32_t)0UL;
            /* Wait for operation end */
            u32Timeout = 0UL;
            while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY0))
            {
                u32Timeout ++;
                if(u32Timeout >= EFM_PGM_TIMEOUT)
                {
                    enRet = ErrorTimeout;
                    break;
                }
            }
        }
        /* CLear the end of operate flag */
        EFM_ClearFlag(EFM_FLAG_CLR_OPTEND0);
        /* Set read only mode. */
        MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_READONLY);
    }

    return enRet;
}

/**
 * @brief  Flash chip erase.
 * @param  [in]  EraseMode      Specifies the FLASH erase mode.
 *   @arg  EFM_MODE_ERASECHIP1  A flash Chip erase mode
 *   @arg  EFM_MODE_ERASECHIP1  Two flash Chip erase mode
 * @param  [in]  u32Addr        Specifies the FLASH block
 * @retval An en_result_t enumeration value:
 *         - Ok: program success
 *         - ErrorTimeout: program error timeout
 * @note   The address should be word align.
 *         Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_ChipErase(uint32_t EraseMode, uint32_t u32Addr)
{
    en_result_t enRet = Ok;
    uint32_t u32Timeout = 0UL;
    uint32_t u32tmp;
    uint32_t u32EfmFlag;
    uint32_t u32EfmClrFlag;

    DDL_ASSERT(IS_VALID_EFM_ERASE_MODE(EraseMode));
    DDL_ASSERT(IS_VALID_EFM_CHIP_ERASE_ADDR(u32Addr));
    DDL_ASSERT(IS_VALID_EFM_UNLOCK());

    /* CLear the error flag. */
    EFM_ClearFlag(EFM_CLR_FLAG_MASK);
    /* Get CACHE status */
    u32tmp = READ_REG32_BIT(M4_EFM->FRMC, EFM_CACHE_MASK);
    /* Disable CACHE */
    CLEAR_REG32_BIT(M4_EFM->FRMC, EFM_CACHE_MASK);
    /* If wsap enable, Disable it */
    if (RW_MEM32(EFM_SWAP_ADDR) == EFM_SWAP_DATA)
    {
        /* Set Sector erase mode. */
        MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_ERASESECTOR);
        /* Disable flash switch function */
        RW_MEM32(EFM_SWAP_ADDR) = 0x0UL;
        while(Set != EFM_GetFlagStatus(EFM_FLAG_OPTEND0))
        {
            u32Timeout ++;
            if(u32Timeout >= EFM_ERASE_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        /* CLear the end of operate flag */
        EFM_ClearFlag(EFM_FLAG_CLR_OPTEND0);
    }
    /* Set chip erase mode. */
    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EraseMode);
    if(EraseMode == EFM_MODE_ERASECHIP1)
    {
        if (u32Addr >= EFM_ADDR_SECTOR128)
        {
            u32EfmFlag = EFM_FLAG_RDY1;
            u32EfmClrFlag = EFM_FLAG_CLR_OPTEND1;
            /* Flash1 disables write protection  */
            WRITE_REG32(M4_EFM->F1NWPRT0, 0xFFFFFFFFUL);
            WRITE_REG32(M4_EFM->F1NWPRT1, 0xFFFFFFFFUL);
            WRITE_REG32(M4_EFM->F1NWPRT2, 0xFFFFFFFFUL);
            WRITE_REG32(M4_EFM->F1NWPRT3, 0xFFFFFFFFUL);
        }
        else
        {
            u32EfmFlag = EFM_FLAG_RDY0;
            u32EfmClrFlag = EFM_FLAG_CLR_OPTEND0;
            /* Flash0 disables write protection  */
            WRITE_REG32(M4_EFM->F0NWPRT0, 0xFFFFFFFFUL);
            WRITE_REG32(M4_EFM->F0NWPRT1, 0xFFFFFFFFUL);
            WRITE_REG32(M4_EFM->F0NWPRT2, 0xFFFFFFFFUL);
            WRITE_REG32(M4_EFM->F0NWPRT3, 0xFFFFFFFFUL);
        }

        /* Erase */
        RW_MEM32(u32Addr & 0xFFFFFFFCUL) = (uint32_t)0UL;
        while(Set != EFM_GetFlagStatus(u32EfmFlag))
        {
            u32Timeout ++;
            if(u32Timeout >= EFM_ERASE_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        /* CLear the end of operate flag */
        EFM_ClearFlag(u32EfmClrFlag);
    }
    else
    {
            /* Flash0 and Flash1 disables write protection  */
            WRITE_REG32(M4_EFM->F0NWPRT0, 0xFFFFFFFFUL);
            WRITE_REG32(M4_EFM->F0NWPRT1, 0xFFFFFFFFUL);
            WRITE_REG32(M4_EFM->F0NWPRT2, 0xFFFFFFFFUL);
            WRITE_REG32(M4_EFM->F0NWPRT3, 0xFFFFFFFFUL);
            WRITE_REG32(M4_EFM->F1NWPRT0, 0xFFFFFFFFUL);
            WRITE_REG32(M4_EFM->F1NWPRT1, 0xFFFFFFFFUL);
            WRITE_REG32(M4_EFM->F1NWPRT2, 0xFFFFFFFFUL);
            WRITE_REG32(M4_EFM->F1NWPRT3, 0xFFFFFFFFUL);
        /* Erase */
        RW_MEM32(u32Addr & 0xFFFFFFFCUL) = (uint32_t)0UL;
        while(Set != EFM_GetFlagStatus(EFM_FLAG_RDY0))
        {
            u32Timeout ++;
            if(u32Timeout >= EFM_ERASE_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        /* CLear the end of operate flag */
        EFM_ClearFlag(EFM_FLAG_CLR_OPTEND0);
        EFM_ClearFlag(EFM_FLAG_CLR_OPTEND1);
    }
    /* Set read only mode. */
    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_READONLY);
    /* recover CACHE */
    MODIFY_REG32(M4_EFM->FRMC, EFM_CACHE_MASK, u32tmp);
    return enRet;
}

/**
 * @brief  Enable or disable the EFM swap function.
 * @param  [in] enNewState                The new state of the flash swap function.
 *   @arg  This parameter can be: Enable or Disable.
 * @retval An en_result_t enumeration value:
 *         - Ok: program success
 *         - ErrorTimeout: program error timeout
 * @note   Call EFM_Unlock() unlock EFM register first.
 */
en_result_t EFM_SwapCmd(en_functional_state_t enNewState)
{
    en_result_t enRet = Ok;
    uint32_t u32Timeout = 0UL;

    DDL_ASSERT(IS_VALID_EFM_UNLOCK());
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    if (enNewState ==Enable)
    {
        /* Set Program single mode. */
        MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_PROGRAMSINGLE);
        /* Enable flash swap function */
        RW_MEM32(EFM_SWAP_ADDR) = EFM_SWAP_DATA;
        while(Set != EFM_GetFlagStatus(EFM_FLAG_OPTEND0))
        {
            u32Timeout ++;
            if(u32Timeout >= EFM_PGM_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        /* CLear the end of operate flag */
        EFM_ClearFlag(EFM_FLAG_CLR_OPTEND0);
    }
    else{
        /* Set Sector erase mode. */
        MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_ERASESECTOR);
        /* Disable flash switch function */
        RW_MEM32(EFM_SWAP_ADDR) = 0x0UL;
        while(Set != EFM_GetFlagStatus(EFM_FLAG_OPTEND0))
        {
            u32Timeout ++;
            if(u32Timeout >= EFM_ERASE_TIMEOUT)
            {
                enRet = ErrorTimeout;
                break;
            }
        }
        /* CLear the end of operate flag */
        EFM_ClearFlag(EFM_FLAG_CLR_OPTEND0);
    }
    /* Set read only mode. */
    MODIFY_REG32(M4_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MODE_READONLY);

    return enRet;
}

/**
 * @brief  Get chip ID.
 * @param  None
 * @retval Returns the value of the Chip ID
 */
uint32_t EFM_GetCID(void)
{
    uint32_t u32CID;
    u32CID = M4_EFM->FHDFG;
    return u32CID;
}

/**
 * @brief  Get unique ID.
 * @param  [out] stcUID      Unique ID struct
 * @retval Returns the value of the unique ID
 */
void EFM_GetUID(stc_efm_unique_id_t *stcUID)
{
    stcUID->u32UniqueID0 = READ_REG32(M4_EFM->UQID0);
    stcUID->u32UniqueID1 = READ_REG32(M4_EFM->UQID1);
    stcUID->u32UniqueID2 = READ_REG32(M4_EFM->UQID2);
}

/**
 * @}
 */

#endif  /* DDL_EFM_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
