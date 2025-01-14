/**
 *******************************************************************************
 * @file  hc32_ll_efm.c
 * @brief This file provides firmware functions to manage the Embedded Flash
 *        Memory unit (EFM).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-10-31       CDT             Add API EFM_Protect_Enable & EFM_WriteSecurityCode
                                    Modify API EFM_Read & EFM_Program
   2023-01-15       CDT             Code refine
   2023-06-30       CDT             Modify API EFM_Program()
                                    Modify assert IS_EFM_ADDR() range
                                    Modify API EFM_Protect_Enable()
                                    Modify typo
                                    Modify API EFM_WriteSecurityCode(), switch to read_only mode before exit
   2023-09-30       CDT             Remove address assert from EFM_ReadByte()
                                    Refine EFM_SequenceProgram() & EFM_ChipErase(), and put them in RAM
                                    Fix bug of EFM_GetSwapStatus()
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
#include "hc32_ll_efm.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_EFM EFM
 * @brief Embedded Flash Management Driver Library
 * @{
 */

#if (LL_EFM_ENABLE == DDL_ON)

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
#ifndef __EFM_FUNC
#define __EFM_FUNC                      __RAM_FUNC
#endif

#define REG_LEN                         (32U)
#define EFM_TIMEOUT                     (HCLK_VALUE / 20000UL)  /* EFM wait read timeout */
#define EFM_PGM_TIMEOUT                 (HCLK_VALUE / 20000UL)  /* EFM Program timeout max 53us */
#define EFM_ERASE_TIMEOUT               (HCLK_VALUE / 50UL)     /* EFM Erase timeout max 20ms */
#define EFM_SEQ_PGM_TIMEOUT             (HCLK_VALUE / 62500UL)  /* EFM Sequence Program timeout max 16us */

#define REMCR_REG(x)                    (*(__IO uint32_t *)((uint32_t)(&CM_EFM->MMF_REMCR0) + (4UL * (x))))

/**
 * @defgroup EFM_Configuration_Bit_Mask EFM Configuration Bit Mask
 * @{
 */
#define EFM_CACHE_ALL                   (EFM_FRMC_CRST | EFM_FRMC_CACHE)

/**
 * @}
 */

/**
 * @defgroup EFM_protect EFM protect define
 * @{
 */
#define EFM_SECURITY_LEN                (12UL)
#define EFM_PROTECT1_KEY                (0xAF180402UL)
#define EFM_PROTECT2_KEY                (0xA85173AEUL)

#define EFM_PROTECT1_ADDR               (0x00000410UL)
#define EFM_PROTECT2_ADDR               (0x00000414UL)
#define EFM_SECURITY_ADDR               (0x0317FFECUL)
#define EFM_SECURITY_ADDR1              (0x0317FFE0UL)
/**
 * @}
 */

/**
 * @defgroup EFM_Check_Parameters_Validity EFM Check Parameters Validity
 * @{
 */
/* Parameter validity check for efm chip . */
#define IS_EFM_CHIP(x)                  ((x) == EFM_CHIP_ALL)

/* Parameter validity check for flash latency. */
#define IS_EFM_WAIT_CYCLE(x)            ((x) <= EFM_WAIT_CYCLE15)

/* Parameter validity check for operate mode. */
#define IS_EFM_OPERATE_MD(x)                                                    \
(   ((x) == EFM_MD_PGM_SINGLE)          ||                                      \
    ((x) == EFM_MD_PGM_READBACK)        ||                                      \
    ((x) == EFM_MD_PGM_SEQ)             ||                                      \
    ((x) == EFM_MD_ERASE_SECTOR)        ||                                      \
    ((x) == EFM_MD_ERASE_ALL_CHIP)      ||                                      \
    ((x) == EFM_MD_READONLY))

/* Parameter validity check for flash interrupt select. */
#define IS_EFM_INT_SEL(x)               (((x) | EFM_INT_ALL) == EFM_INT_ALL)

/* Parameter validity check for flash flag. */
#define IS_EFM_FLAG(x)                  (((x) | EFM_FLAG_ALL) == EFM_FLAG_ALL)

/* Parameter validity check for flash clear flag. */
#define IS_EFM_CLRFLAG(x)               (((x) | EFM_FLAG_ALL) == EFM_FLAG_ALL)

/* Parameter validity check for bus status while flash program or erase. */
#define IS_EFM_BUS_STATUS(x)                                                    \
(   ((x) == EFM_BUS_HOLD)               ||                                      \
    ((x) == EFM_BUS_RELEASE))

/* Parameter validity check for efm address. */
#define IS_EFM_ADDR(x)                                                          \
(   ((x) <= EFM_END_ADDR)               ||                                      \
    (((x) >= EFM_OTP_START_ADDR) && ((x) <= EFM_OTP_END_ADDR)) ||               \
    (((x) >= EFM_SECURITY_START_ADDR) && ((x) <= EFM_SECURITY_END_ADDR)))

/* Parameter validity check for efm erase address. */
#define IS_EFM_ERASE_ADDR(x)            ((x) <= EFM_END_ADDR)

/* Parameter validity check for efm erase mode . */
#define IS_EFM_ERASE_MD(x)                                                      \
(   ((x) == EFM_MD_ERASE_ONE_CHIP)      ||                                      \
    ((x) == EFM_MD_ERASE_FULL))

/* Parameter validity check for EFM lock status. */
#define IS_EFM_REG_UNLOCK()             (CM_EFM->FAPRT == 0x00000001UL)

/* Parameter validity check for EFM_FWMC register lock status. */
#define IS_EFM_FWMC_UNLOCK()            (bCM_EFM->FWMC_b.PEMODE == 1U)

/* Parameter validity check for EFM remap lock status. */
#define IS_EFM_REMAP_UNLOCK()           (CM_EFM->MMF_REMPRT == 0x00000001UL)

/* Parameter validity check for EFM remap index */
#define IS_EFM_REMAP_IDX(x)                                                     \
(   ((x) == EFM_REMAP_IDX0)             ||                                      \
    ((x) == EFM_REMAP_IDX1))

/* Parameter validity check for EFM remap size */
#define IS_EFM_REMAP_SIZE(x)                                                    \
(   ((x) >= EFM_REMAP_4K)               &&                                      \
    ((x) <= EFM_REMAP_512K))

/* Parameter validity check for EFM remap address */
#define IS_EFM_REMAP_ADDR(x)                                                    \
(   ((x) <= EFM_REMAP_ROM_END_ADDR)     ||                                      \
    (((x) >= EFM_REMAP_RAM_START_ADDR)  &&                                      \
    ((x) <= EFM_REMAP_RAM_END_ADDR)))

/* Parameter validity check for EFM remap state */
#define IS_EFM_REMAP_STATE(x)                                                  \
(   ((x) == EFM_REMAP_OFF)             ||                                      \
    ((x) == EFM_REMAP_ON))

/* Parameter validity check for EFM security code length */
#define IS_EFM_SECURITY_CODE_LEN(x)    ((x) <= EFM_SECURITY_LEN)
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
 * @defgroup EFM_Local_Functions EFM Local Functions
 * @{
 */
/**
 * @brief  Wait EFM flag.
 * @param  [in] u32Flag     Specifies the flag to be wait. @ref EFM_Flag_Sel
 * @param  [in] u32Time     Specifies the time to wait while the flag not be set.
 * @retval int32_t:
 *         - LL_OK: Flag was set.
 *         - LL_ERR_TIMEOUT: Flag was not set.
 */
static int32_t EFM_WaitFlag(uint32_t u32Flag, uint32_t u32Time)
{
    __IO uint32_t u32Timeout = 0UL;
    int32_t i32Ret = LL_OK;

    while (SET != EFM_GetStatus(u32Flag)) {
        u32Timeout++;
        if (u32Timeout > u32Time) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    return i32Ret;
}

/**
 * @}
 */

/**
 * @defgroup EFM_Global_Functions EFM Global Functions
 * @{
 */

/**
 * @brief  Enable or disable EFM.
 * @param  [in]  u32Flash       Specifies the FLASH. @ref EFM_Chip_Sel
 * @param  [in] enNewState      An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void EFM_Cmd(uint32_t u32Flash, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_EFM_REG_UNLOCK());
    DDL_ASSERT(IS_EFM_CHIP(u32Flash));

    if (ENABLE == enNewState) {
        CLR_REG32_BIT(CM_EFM->FSTP, u32Flash);
    } else {
        SET_REG32_BIT(CM_EFM->FSTP, u32Flash);
    }
}

/**
 * @brief  Set the efm read wait cycles.
 * @param  [in] u32WaitCycle            Specifies the efm read wait cycles.
 *    @arg  This parameter can be of a value of @ref EFM_Wait_Cycle
 * @retval int32_t:
 *         - LL_OK: Program successfully.
 *         - LL_ERR_TIMEOUT: EFM is not ready.
 * @note   Call EFM_REG_Unlock() unlock EFM register first.
 */
int32_t EFM_SetWaitCycle(uint32_t u32WaitCycle)
{
    uint32_t u32Timeout = 0UL;

    /* Param valid check */
    DDL_ASSERT(IS_EFM_REG_UNLOCK());
    DDL_ASSERT(IS_EFM_WAIT_CYCLE(u32WaitCycle));

    MODIFY_REG32(CM_EFM->FRMC, EFM_FRMC_FLWT, u32WaitCycle);
    while (u32WaitCycle != READ_REG32_BIT(CM_EFM->FRMC, EFM_FRMC_FLWT)) {
        u32Timeout++;
        if (u32Timeout > EFM_TIMEOUT) {
            return LL_ERR_TIMEOUT;
        }
    }
    return LL_OK;
}

/**
 * @brief  Enable or disable the flash data cache reset.
 * @param  [in] enNewState           An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void EFM_DataCacheResetCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_EFM_REG_UNLOCK());

    WRITE_REG32(bCM_EFM->FRMC_b.CRST, enNewState);
}

/**
 * @brief  Enable or disable the flash data cache and instruction cache.
 * @param  [in] enNewState                An @ref en_functional_state_t enumeration value.
 * @retval None
 * @note   Call EFM_REG_Unlock() unlock EFM register first.
 */
void EFM_CacheCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_EFM_REG_UNLOCK());

    WRITE_REG32(bCM_EFM->FRMC_b.CACHE, enNewState);
}

/**
 * @brief  Enable or disable the Read of low-voltage mode.
 * @param  [in] enNewState                An @ref en_functional_state_t enumeration value.
 * @retval None
 * @note   Call EFM_REG_Unlock() unlock EFM register first.
 */
void EFM_LowVoltageReadCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_EFM_REG_UNLOCK());

    WRITE_REG32(bCM_EFM->FRMC_b.SLPMD, enNewState);
}

/**
 * @brief  Enable or disable the EFM swap function.
 * @param  [in] enNewState                An @ref en_functional_state_t enumeration value.
 * @retval int32_t:
 *         - LL_OK: Program successfully.
 *         - LL_ERR_NOT_RDY: EFM is not ready.
 * @note   Call EFM_REG_Unlock() unlock EFM register first.
 */
int32_t EFM_SwapCmd(en_functional_state_t enNewState)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32Tmp;

    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    DDL_ASSERT(IS_EFM_REG_UNLOCK());
    DDL_ASSERT(IS_EFM_FWMC_UNLOCK());

    /* Get CACHE status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);
    /* Disable CACHE */
    CLR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);

    if (enNewState == ENABLE) {
        /* Set Program single mode. */
        MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_PGM_SINGLE);
        /* Enable flash swap function */
        RW_MEM32(EFM_SWAP_ADDR) = EFM_SWAP_DATA;
        /* Wait for ready flag. */
        if (LL_ERR_TIMEOUT == EFM_WaitFlag(EFM_FLAG_RDY, EFM_PGM_TIMEOUT)) {
            i32Ret = LL_ERR_NOT_RDY;
        }
        /* CLear the operation end flag. */
        EFM_ClearStatus(EFM_FLAG_OPTEND);
    } else {
        /* Set Sector erase mode. */
        MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_ERASE_SECTOR);
        /* Disable flash switch function */
        RW_MEM32(EFM_SWAP_ADDR) = 0x0UL;
        /* Wait for ready flag. */
        if (LL_ERR_TIMEOUT == EFM_WaitFlag(EFM_FLAG_RDY, EFM_ERASE_TIMEOUT)) {
            i32Ret = LL_ERR_NOT_RDY;
        }
        /* CLear the operation end flag. */
        EFM_ClearStatus(EFM_FLAG_OPTEND);
    }
    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);

    /* recover CACHE */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_ALL, u32Tmp);

    return i32Ret;
}

/**
 * @brief  Checks whether the swap function enable or disable.
 * @param  None
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t EFM_GetSwapStatus(void)
{
    return ((0UL == READ_REG32(bCM_EFM->FSWP_b.FSWP)) ? SET : RESET);
}

/**
 * @brief  Enable or disable the EFM low-voltage mode.
 * @param  [in] enNewState                An @ref en_functional_state_t enumeration value.
 * @retval None
 * @note   Call EFM_REG_Unlock() unlock EFM register first.
 */
void EFM_LowVoltageCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    WRITE_REG32(bCM_EFM->FRMC_b.LVM, enNewState);
}

/**
 * @brief  Set the FLASH erase program mode .
 * @param  [in] u32Mode                   Specifies the FLASH erase program mode.
 *    @arg  This parameter can be of a value of @ref EFM_OperateMode_Sel
 * @retval int32_t:
 *         - LL_OK: Set mode successfully.
 *         - LL_ERR_NOT_RDY: EFM is not ready.
 */
int32_t EFM_SetOperateMode(uint32_t u32Mode)
{
    int32_t i32Ret = LL_OK;
    DDL_ASSERT(IS_EFM_OPERATE_MD(u32Mode));
    DDL_ASSERT(IS_EFM_REG_UNLOCK());
    DDL_ASSERT(IS_EFM_FWMC_UNLOCK());

    if (LL_ERR_TIMEOUT == EFM_WaitFlag(EFM_FLAG_RDY, EFM_SEQ_PGM_TIMEOUT)) {
        i32Ret = LL_ERR_NOT_RDY;
    }

    if (i32Ret == LL_OK) {
        /* Set the program or erase mode. */
        MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, u32Mode);
    }
    return i32Ret;
}

/**
 * @brief  Enable or Disable EFM interrupt.
 * @param  [in] u32EfmInt               Specifies the FLASH interrupt source and status. @ref EFM_Interrupt_Sel
 *   @arg  EFM_INT_OPTEND:              End of EFM Operation Interrupt source
 *   @arg  EFM_INT_PEERR:               Program/erase error Interrupt source
 *   @arg  EFM_INT_COLERR:              Read collide error Interrupt source
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 * @note   Call EFM_REG_Unlock() unlock EFM register first.
 */
void EFM_IntCmd(uint32_t u32EfmInt, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_EFM_REG_UNLOCK());
    DDL_ASSERT(IS_EFM_INT_SEL(u32EfmInt));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_EFM->FITE, u32EfmInt);
    } else {
        CLR_REG32_BIT(CM_EFM->FITE, u32EfmInt);
    }
}

/**
 * @brief  Check any of the specified flag is set or not.
 * @param  [in] u32Flag                    Specifies the FLASH flag to check.
 *   @arg  This parameter can be of a value of @ref EFM_Flag_Sel
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t EFM_GetAnyStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_EFM_FLAG(u32Flag));

    return ((0UL == READ_REG32_BIT(CM_EFM->FSR, u32Flag)) ? RESET : SET);
}

/**
 * @brief  Check all the specified flag is set or not.
 * @param  [in] u32Flag                    Specifies the FLASH flag to check.
 *   @arg  This parameter can be of a value of @ref EFM_Flag_Sel
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t EFM_GetStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_EFM_FLAG(u32Flag));

    return ((u32Flag == READ_REG32_BIT(CM_EFM->FSR, u32Flag)) ? SET : RESET);
}

/**
 * @brief  Clear the flash flag.
 * @param  [in] u32Flag                  Specifies the FLASH flag to clear.
 *   @arg  This parameter can be of a value of @ref EFM_Flag_Sel
 * @retval None
 * @note   Call EFM_REG_Unlock() unlock EFM register first.
 */
void EFM_ClearStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_EFM_REG_UNLOCK());
    DDL_ASSERT(IS_EFM_CLRFLAG(u32Flag));

    SET_REG32_BIT(CM_EFM->FSCLR, u32Flag);
}

/**
 * @brief  Set bus status while flash program or erase.
 * @param  [in] u32Status                  Specifies the new bus status while flash program or erase.
 *  This parameter can be one of the following values:
 *   @arg  EFM_BUS_HOLD:                   Bus busy while flash program or erase.
 *   @arg  EFM_BUS_RELEASE:                Bus release while flash program or erase.
 * @retval None
 */
void EFM_SetBusStatus(uint32_t u32Status)
{
    DDL_ASSERT(IS_EFM_REG_UNLOCK());
    DDL_ASSERT(IS_EFM_BUS_STATUS(u32Status));
    DDL_ASSERT(IS_EFM_FWMC_UNLOCK());

    WRITE_REG32(bCM_EFM->FWMC_b.BUSHLDCTL, u32Status);
}

/**
 * @brief  EFM read byte.
 * @param  [in] u32Addr               The specified address to read.
 * @param  [in] pu8ReadBuf            The specified read buffer.
 * @param  [in] u32ByteLen            The specified length to read.
 * @retval int32_t:
 *         - LL_OK: Read successfully
 *         - LL_ERR_INVD_PARAM: Invalid parameter
 *         - LL_ERR_NOT_RDY: EFM is not ready.
 */
int32_t EFM_ReadByte(uint32_t u32Addr, uint8_t *pu8ReadBuf, uint32_t u32ByteLen)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    __IO uint8_t *pu8Buf = (uint8_t *)u32Addr;
    uint32_t u32Len = u32ByteLen;
    uint32_t u32ReadyFlag = EFM_FLAG_RDY;

    DDL_ASSERT(IS_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_EFM_ADDR(u32Addr + u32ByteLen - 1UL));

    if (NULL != pu8ReadBuf) {

        if (LL_OK == EFM_WaitFlag(u32ReadyFlag, EFM_TIMEOUT)) {
            while (0UL != u32Len) {
                *(pu8ReadBuf++) = *(pu8Buf++);
                u32Len--;
            }
            i32Ret = LL_OK;
        } else {
            i32Ret = LL_ERR_NOT_RDY;
        }
    }

    return i32Ret;
}

/**
 * @brief  EFM program (single program mode).
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] pu8Buf                    The pointer of specified program data.
 * @param  [in] u32Len                    The length of specified program data.
 * @retval int32_t:
 *         - LL_OK: Program successful.
 *         - LL_ERR_NOT_RDY: EFM if not ready.
 * @note  Call EFM_REG_Unlock() unlock EFM register first.
 */
int32_t EFM_Program(uint32_t u32Addr, uint8_t *pu8Buf, uint32_t u32Len)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32Tmp;
    uint8_t u8Shift;
    uint32_t u32LoopWords = u32Len >> 2UL;
    uint32_t u32RemainBytes = u32Len % 4UL;
    uint32_t *u32pSource = (uint32_t *)(uint32_t)pu8Buf;
    uint32_t *u32pDest = (uint32_t *)u32Addr;
    uint32_t u32LastWord;

    DDL_ASSERT(IS_EFM_REG_UNLOCK());
    DDL_ASSERT(IS_EFM_FWMC_UNLOCK());
    DDL_ASSERT(IS_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_EFM_ADDR(u32Addr + u32Len - 1UL));
    DDL_ASSERT(IS_ADDR_ALIGN_WORD(u32Addr));

    u8Shift = 0U;

    /* CLear the error flag. */
    EFM_ClearStatus(EFM_FLAG_ALL);
    /* Get CACHE status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);
    /* Disable CACHE */
    CLR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);

    /* Set single program mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_PGM_SINGLE);

    while (u32LoopWords-- > 0UL) {
        /* program data. */
        *u32pDest++ = *u32pSource++;
        /* Wait for ready flag. */
        if (LL_ERR_TIMEOUT == EFM_WaitFlag(EFM_FLAG_RDY << u8Shift, EFM_PGM_TIMEOUT)) {
            i32Ret = LL_ERR_NOT_RDY;
        }
        /* CLear the operation end flag. */
        EFM_ClearStatus(EFM_FLAG_OPTEND << u8Shift);
    }

    if (0U != u32RemainBytes) {
        u32LastWord = *u32pSource;
        u32LastWord |= 0xFFFFFFFFUL << (u32RemainBytes * 8UL);
        *u32pDest++ = u32LastWord;
        /* Wait for ready flag. */
        if (LL_ERR_TIMEOUT == EFM_WaitFlag(EFM_FLAG_RDY << u8Shift, EFM_PGM_TIMEOUT)) {
            i32Ret = LL_ERR_NOT_RDY;
        }
        /* CLear the operation end flag. */
        EFM_ClearStatus(EFM_FLAG_OPTEND << u8Shift);

    }
    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);
    /* Reset cache data */
    /* Recover CACHE function */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_ALL, u32Tmp);
    return i32Ret;
}

/**
 * @brief  EFM single program mode(Word).
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u32Data                   The specified program data.
 * @retval int32_t:
 *         - LL_OK: Program successfully
 *         - LL_ERR_NOT_RDY: EFM is not ready.
 * @note  Call EFM_REG_Unlock() unlock EFM register first.
 */
int32_t EFM_ProgramWord(uint32_t u32Addr, uint32_t u32Data)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32Tmp;
    uint8_t u8Shift;

    DDL_ASSERT(IS_EFM_REG_UNLOCK());
    DDL_ASSERT(IS_EFM_FWMC_UNLOCK());
    DDL_ASSERT(IS_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_ADDR_ALIGN_WORD(u32Addr));

    /* Clear the error flag. */
    EFM_ClearStatus(EFM_FLAG_ALL);
    /* Get CACHE status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);
    /* Disable CACHE function */
    CLR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);
    u8Shift = 0U;
    /* Set single program mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_PGM_SINGLE);
    /* Program data. */
    RW_MEM32(u32Addr) = u32Data;

    /* Wait for ready flag. */
    if (LL_ERR_TIMEOUT == EFM_WaitFlag(EFM_FLAG_RDY << u8Shift, EFM_PGM_TIMEOUT)) {
        i32Ret = LL_ERR_NOT_RDY;
    }
    /* CLear the operation end flag. */
    EFM_ClearStatus(EFM_FLAG_OPTEND << u8Shift);

    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);

    /* Recover CACHE function */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_ALL, u32Tmp);

    return i32Ret;
}

/**
 * @brief  EFM single program with read back(Word).
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] u32Data                   The specified program data.
 * @retval int32_t:
 *         - LL_OK: Program successfully
 *         - LL_ERR: program error
 *         - LL_ERR_NOT_RDY: EFM is not ready.
 * @note  Call EFM_REG_Unlock() unlock EFM register first.
 */
int32_t EFM_ProgramWordReadBack(uint32_t u32Addr, uint32_t u32Data)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32Tmp;
    uint8_t u8Shift;

    DDL_ASSERT(IS_EFM_REG_UNLOCK());
    DDL_ASSERT(IS_EFM_FWMC_UNLOCK());
    DDL_ASSERT(IS_EFM_ADDR(u32Addr));
    DDL_ASSERT(IS_ADDR_ALIGN_WORD(u32Addr));

    /* Clear the error flag. */
    EFM_ClearStatus(EFM_FLAG_ALL);
    /* Get CACHE status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);
    /* Disable CACHE */
    CLR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);
    u8Shift = 0U;
    /* Set Program and read back mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_PGM_READBACK);
    /* Program data. */
    RW_MEM32(u32Addr) = (uint32_t)u32Data;

    /* Wait for ready flag. */
    if (LL_ERR_TIMEOUT == EFM_WaitFlag(EFM_FLAG_RDY << u8Shift, EFM_PGM_TIMEOUT)) {
        i32Ret = LL_ERR_NOT_RDY;
    }

    /* Get the flag PGMISMTCH */
    if (SET == EFM_GetStatus(EFM_FLAG_PGMISMTCH << u8Shift)) {
        /* Clear flag PGMISMTCH */
        EFM_ClearStatus(EFM_FLAG_PGMISMTCH << u8Shift);
        i32Ret = LL_ERR;
    }
    /* CLear the operation end flag. */
    EFM_ClearStatus(EFM_FLAG_OPTEND << u8Shift);
    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);

    /* recover CACHE function */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_ALL, u32Tmp);

    return i32Ret;
}

/**
 * @brief  EFM program (sequence program mode).
 * @param  [in] u32Addr                   The specified program address.
 * @param  [in] pu8Buf                    The pointer of specified program data.
 * @param  [in] u32Len                    The length of specified program data.
 * @retval int32_t:
 *         - LL_OK: Program successfully
 *         - LL_ERR_TIMEOUT: program error timeout
 * @note  Call EFM_REG_Unlock() unlock EFM register first.
 *        __EFM_FUNC default value is __RAM_FUNC.
 */
__EFM_FUNC int32_t EFM_SequenceProgram(uint32_t u32Addr, uint8_t *pu8Buf, uint32_t u32Len)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32Tmp;
    uint32_t u32LoopWords = u32Len >> 2UL;
    uint32_t u32RemainBytes = u32Len % 4UL;
    uint32_t *u32pSource = (uint32_t *)(uint32_t)pu8Buf;
    uint32_t *u32pDest = (uint32_t *)u32Addr;
    uint32_t u32Timeout;
    uint32_t u32LastWord;

    /* Assert */
    if (!IS_EFM_REG_UNLOCK()) {
        return LL_ERR_NOT_RDY;
    }
    if ((!IS_EFM_FWMC_UNLOCK()) || (!IS_EFM_ADDR(u32Addr)) || (!IS_EFM_ADDR(u32Addr + u32Len - 1UL))) {
        return LL_ERR_INVD_PARAM;
    }
    if (!IS_ADDR_ALIGN_WORD(u32Addr)) {
        return LL_ERR_INVD_PARAM;
    }

    /* CLear the error flag. */
    SET_REG32_BIT(CM_EFM->FSCLR, EFM_FLAG_ALL);
    /* Get CACHE status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);
    /* Disable CACHE */
    CLR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);
    /* Set sequence program mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_PGM_SEQ);

    while (u32LoopWords-- > 0UL) {
        /* program data. */
        *u32pDest++ = *u32pSource++;
        /* wait for operation end flag. */
        u32Timeout = 0UL;
        while (EFM_FLAG_OPTEND != READ_REG32_BIT(CM_EFM->FSR, EFM_FLAG_OPTEND)) {
            if (u32Timeout++ >= EFM_PGM_TIMEOUT) {
                i32Ret = LL_ERR_TIMEOUT;
                break;
            }
        }
        /* Clear operation end flag */
        u32Timeout = 0UL;
        while (EFM_FLAG_OPTEND == READ_REG32_BIT(CM_EFM->FSR, EFM_FLAG_OPTEND)) {
            SET_REG32_BIT(CM_EFM->FSCLR, EFM_FLAG_OPTEND);
            if (u32Timeout++ >= EFM_TIMEOUT) {
                i32Ret = LL_ERR_TIMEOUT;
                break;
            }
        }
    }

    if (0U != u32RemainBytes) {
        u32LastWord = *u32pSource;
        u32LastWord |= 0xFFFFFFFFUL << (u32RemainBytes * 8UL);
        *u32pDest++ = u32LastWord;

        /* wait for operation end flag. */
        u32Timeout = 0UL;
        while (EFM_FLAG_OPTEND != READ_REG32_BIT(CM_EFM->FSR, EFM_FLAG_OPTEND)) {
            if (u32Timeout++ >= EFM_PGM_TIMEOUT) {
                i32Ret = LL_ERR_TIMEOUT;
                break;
            }
        }
        /* Clear operation end flag */
        u32Timeout = 0UL;
        while (EFM_FLAG_OPTEND == READ_REG32_BIT(CM_EFM->FSR, EFM_FLAG_OPTEND)) {
            SET_REG32_BIT(CM_EFM->FSCLR, EFM_FLAG_OPTEND);
            if (u32Timeout++ >= EFM_TIMEOUT) {
                i32Ret = LL_ERR_TIMEOUT;
                break;
            }
        }

    }

    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);
    /* Wait for ready flag. */
    u32Timeout = 0UL;
    while (EFM_FLAG_RDY != READ_REG32_BIT(CM_EFM->FSR, EFM_FLAG_RDY)) {
        if (u32Timeout++ >= EFM_PGM_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    /* Recover CACHE */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_ALL, u32Tmp);
    return i32Ret;
}

/**
 * @brief  EFM sector erase.
 * @param  [in] u32Addr                   The address in the specified sector.
 * @retval int32_t:
 *         - LL_OK: Erase successful.
 *         - LL_ERR_NOT_RDY: EFM is not ready.
 * @note   Call EFM_REG_Unlock() unlock EFM register first.
 */
int32_t EFM_SectorErase(uint32_t u32Addr)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32Tmp;
    uint8_t u8Shift;

    DDL_ASSERT(IS_EFM_ERASE_ADDR(u32Addr));
    DDL_ASSERT(IS_ADDR_ALIGN_WORD(u32Addr));
    DDL_ASSERT(IS_EFM_REG_UNLOCK());
    DDL_ASSERT(IS_EFM_FWMC_UNLOCK());

    /* CLear the error flag. */
    EFM_ClearStatus(EFM_FLAG_ALL);
    /* Get CACHE status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);
    /* Disable CACHE */
    CLR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);
    u8Shift = 0U;
    /* Set sector erase mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_ERASE_SECTOR);

    /* Erase */
    RW_MEM32(u32Addr) = 0UL;

    /* Wait for ready flag. */
    if (LL_ERR_TIMEOUT == EFM_WaitFlag(EFM_FLAG_RDY << u8Shift, EFM_ERASE_TIMEOUT)) {
        i32Ret = LL_ERR_NOT_RDY;
    }
    /* Clear the operation end flag */
    EFM_ClearStatus(EFM_FLAG_OPTEND << u8Shift);
    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);
    /* Recover CACHE */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_ALL, u32Tmp);

    return i32Ret;
}

/**
 * @brief  EFM chip erase.
 * @param  [in]  u8Chip      Specifies the chip to be erased @ref EFM_Chip_Sel
 * @retval int32_t:
 *         - LL_OK: Erase successfully
 *         - LL_ERR_NOT_RDY: EFM is not ready.
 * @note   Call EFM_REG_Unlock() unlock EFM register first.
 *         __EFM_FUNC default value is __RAM_FUNC.
 */
__EFM_FUNC int32_t EFM_ChipErase(uint8_t u8Chip)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32Tmp;
    uint32_t u32Addr = 0UL;
    uint8_t u8Shift;
    uint32_t u32Timeout;

    /* Assert */
    if (!IS_EFM_REG_UNLOCK()) {
        return LL_ERR_NOT_RDY;
    }
    if ((!IS_EFM_FWMC_UNLOCK()) || !IS_EFM_CHIP(u8Chip)) {
        return LL_ERR_INVD_PARAM;
    }

    u8Shift = 0U;

    /* CLear the error flag. */
    SET_REG32_BIT(CM_EFM->FSCLR, EFM_FLAG_ALL);
    /* Get CACHE status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);
    /* Disable CACHE */
    CLR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);

    if (EFM_CHIP_ALL == u8Chip) {
        if (1UL == (READ_REG32(bCM_EFM->FSWP_b.FSWP))) {
            /* Set Sector erase mode. */
            MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_ERASE_SECTOR);
            /* Disable flash switch function */
            RW_MEM32(EFM_SWAP_ADDR) = 0x0UL;
            /* wait for operation end flag. */
            u32Timeout = 0UL;
            while (EFM_FLAG_OPTEND != READ_REG32_BIT(CM_EFM->FSR, EFM_FLAG_OPTEND)) {
                if (u32Timeout++ >= EFM_PGM_TIMEOUT) {
                    i32Ret = LL_ERR_TIMEOUT;
                    break;
                }
            }
            /* CLear the operation end flag */
            SET_REG32_BIT(CM_EFM->FSCLR, EFM_FLAG_OPTEND);
        }
    }

    /* Set chip erase mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_ERASE_ALL_CHIP);
    /* Erase */
    RW_MEM32(u32Addr) = 0UL;
    /* Wait for ready flag. */
    u32Timeout = 0UL;
    while ((EFM_FLAG_RDY << u8Shift) != READ_REG32_BIT(CM_EFM->FSR, EFM_FLAG_RDY << u8Shift)) {
        if (u32Timeout++ >= EFM_ERASE_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }
    /* CLear the operation end flag. */
    SET_REG32_BIT(CM_EFM->FSCLR, EFM_FLAG_OPTEND << u8Shift);
    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);

    /* recover CACHE */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_ALL, u32Tmp);
    return i32Ret;
}

/**
 * @brief  FWMC register write enable or disable.
 * @param  [in] enNewState                An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void EFM_FWMC_Cmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_EFM->FWMC_b.PEMODE, enNewState);
}

/**
 * @brief  EFM OTP lock.
 * @param  [in]  u32Addr           Specifies the OTP block
 * @retval int32_t:
 *         - LL_OK: Lock successfully
 *         - LL_ERR_NOT_RDY: EFM is not ready.
 * @note   The address should be word align.
 *         Call EFM_REG_Unlock() and EFM_OTP_WP_Unlock() unlock EFM_FWMC register first.
 */
int32_t EFM_OTP_Lock(uint32_t u32Addr)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32Tmp;

    if ((u32Addr >= EFM_OTP_LOCK_ADDR_START) && (u32Addr < EFM_OTP_LOCK_ADDR_END)) {
        DDL_ASSERT(IS_ADDR_ALIGN_WORD(u32Addr));
        DDL_ASSERT(IS_EFM_FWMC_UNLOCK());
        DDL_ASSERT(IS_EFM_REG_UNLOCK());
        /* Get CACHE status */
        u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);
        /* Disable CACHE */
        CLR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);

        /* Set single program mode. */
        MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_PGM_SINGLE);

        /* OTP latch */
        RW_MEM32(u32Addr) = (uint32_t)0UL;
        /* Wait for ready flag. */
        if (LL_ERR_TIMEOUT == EFM_WaitFlag(EFM_FLAG_RDY, EFM_ERASE_TIMEOUT)) {
            i32Ret = LL_ERR_NOT_RDY;
        }
        /* CLear the operation end flag. */
        EFM_ClearStatus(EFM_FLAG_OPTEND);

        /* Set read only mode. */
        MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);

        /* Recover CACHE */
        MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_ALL, u32Tmp);
    }

    return i32Ret;
}

/**
 * @brief  Set flash protect area.
 * @param  [in] u32StartAddr       Start address of protect area.
 * @param  [in] u32EndAddr         End address of protect area.
 * @retval None
 * @note   Call EFM_REG_Unlock() unlock EFM register first.
 */
void EFM_SetWindowProtectAddr(uint32_t u32StartAddr, uint32_t u32EndAddr)
{
    DDL_ASSERT(IS_EFM_REG_UNLOCK());
    DDL_ASSERT(IS_EFM_ADDR(u32StartAddr));
    DDL_ASSERT(IS_EFM_ADDR(u32EndAddr));
    /* Set protect area start address */
    WRITE_REG32(CM_EFM->FPMTSW, u32StartAddr);
    /* Set protect area end address */
    WRITE_REG32(CM_EFM->FPMTEW, u32EndAddr);
}

/**
 * @brief  Get unique ID.
 * @param  [out] pstcUID     Unique ID struct
 * @retval Returns the value of the unique ID
 */
void EFM_GetUID(stc_efm_unique_id_t *pstcUID)
{
    if (NULL != pstcUID) {
        pstcUID->u32UniqueID0 = READ_REG32(CM_EFM->UQID0);
        pstcUID->u32UniqueID1 = READ_REG32(CM_EFM->UQID1);
        pstcUID->u32UniqueID2 = READ_REG32(CM_EFM->UQID2);
    }
}

/**
 * @brief  Init REMAP initial structure with default value.
 * @param  [in] pstcEfmRemapInit specifies the Parameter of REMAP.
 * @retval int32_t:
 *         - LL_OK: Initialize success
 *         - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t EFM_REMAP_StructInit(stc_efm_remap_init_t *pstcEfmRemapInit)
{
    int32_t i32Ret = LL_OK;
    if (NULL == pstcEfmRemapInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcEfmRemapInit->u32State = EFM_REMAP_OFF;
        pstcEfmRemapInit->u32Addr = 0UL;
        pstcEfmRemapInit->u32Size = EFM_REMAP_4K;
    }
    return i32Ret;
}

/**
 * @brief  REMAP initialize.
 * @param  [in] u8RemapIdx      Specifies the remap ID.
 * @param  [in] pstcEfmRemapInit specifies the Parameter of REMAP.
 * @retval int32_t:
 *         - LL_OK: Initialize success
 *         - LL_ERR_INVD_PARAM: NULL pointer
 */
int32_t EFM_REMAP_Init(uint8_t u8RemapIdx, stc_efm_remap_init_t *pstcEfmRemapInit)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t *REMCRx;

    if (NULL == pstcEfmRemapInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        DDL_ASSERT(IS_EFM_REMAP_UNLOCK());
        DDL_ASSERT(IS_EFM_REMAP_IDX(u8RemapIdx));
        DDL_ASSERT(IS_EFM_REMAP_SIZE(pstcEfmRemapInit->u32Size));
        DDL_ASSERT(IS_EFM_REMAP_ADDR(pstcEfmRemapInit->u32Addr));
        DDL_ASSERT(IS_EFM_REMAP_STATE(pstcEfmRemapInit->u32State));
        if ((pstcEfmRemapInit->u32Addr % (1UL << pstcEfmRemapInit->u32Size)) != 0U) {
            i32Ret = LL_ERR_INVD_PARAM;
        } else {
            REMCRx = &REMCR_REG(u8RemapIdx);
            MODIFY_REG32(*REMCRx, EFM_MMF_REMCR_EN | EFM_MMF_REMCR_RMTADDR | EFM_MMF_REMCR_RMSIZE, \
                         pstcEfmRemapInit->u32State | pstcEfmRemapInit->u32Addr | pstcEfmRemapInit->u32Size);
        }
    }
    return i32Ret;
}

/**
 * @brief  EFM REMAP de-initialize.
 * @param  None
 * @retval None
 */
void EFM_REMAP_DeInit(void)
{
    DDL_ASSERT(IS_EFM_REMAP_UNLOCK());

    WRITE_REG32(CM_EFM->MMF_REMCR0, 0UL);
    WRITE_REG32(CM_EFM->MMF_REMCR1, 0UL);
}

/**
 * @brief  Enable or disable REMAP function.
 * @param  [in] u8RemapIdx      Specifies the remap ID.
 * @param  [in] enNewState      An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void EFM_REMAP_Cmd(uint8_t u8RemapIdx, en_functional_state_t enNewState)
{
    __IO uint32_t *REMCRx;

    DDL_ASSERT(IS_EFM_REMAP_UNLOCK());
    DDL_ASSERT(IS_EFM_REMAP_IDX(u8RemapIdx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    REMCRx = &REMCR_REG(u8RemapIdx);
    if (ENABLE == enNewState) {
        SET_REG32_BIT(*REMCRx, EFM_MMF_REMCR_EN);
    } else {
        CLR_REG32_BIT(*REMCRx, EFM_MMF_REMCR_EN);
    }
}

/**
 * @brief  Set specified REMAP target address.
 * @param  [in] u8RemapIdx      Specifies the remap ID.
 * @param  [in] u32Addr         Specifies the target address.
 * @retval None
 */
void EFM_REMAP_SetAddr(uint8_t u8RemapIdx, uint32_t u32Addr)
{
    __IO uint32_t *REMCRx;

    DDL_ASSERT(IS_EFM_REMAP_UNLOCK());
    DDL_ASSERT(IS_EFM_REMAP_IDX(u8RemapIdx));
    DDL_ASSERT(IS_EFM_REMAP_ADDR(u32Addr));

    REMCRx = &REMCR_REG(u8RemapIdx);
    MODIFY_REG32(*REMCRx, EFM_MMF_REMCR_RMTADDR, u32Addr);
}

/**
 * @brief  Set specified REMAP size.
 * @param  [in] u8RemapIdx      Specifies the remap ID.
 * @param  [in] u32Size         Specifies the remap size.
 * @retval None
 */
void EFM_REMAP_SetSize(uint8_t u8RemapIdx, uint32_t u32Size)
{
    __IO uint32_t *REMCRx;

    DDL_ASSERT(IS_EFM_REMAP_UNLOCK());
    DDL_ASSERT(IS_EFM_REMAP_IDX(u8RemapIdx));
    DDL_ASSERT(IS_EFM_REMAP_SIZE(u32Size));

    REMCRx = &REMCR_REG(u8RemapIdx);
    MODIFY_REG32(*REMCRx, EFM_MMF_REMCR_RMSIZE, u32Size);
}

/**
 * @brief  Enable efm protect.
 * @param  [in] u8Level      Specifies the protect level. @ref EFM_Protect_Level
 * @retval None
 */
void EFM_Protect_Enable(uint8_t u8Level)
{
    uint8_t u8Code[12] = {0};

    (void)EFM_Program(EFM_SECURITY_ADDR1, u8Code, sizeof(u8Code));
    if (EFM_PROTECT_LEVEL1 == u8Level) {
        (void)EFM_ProgramWord(EFM_PROTECT1_ADDR, EFM_PROTECT1_KEY);
    } else if (EFM_PROTECT_LEVEL2 == u8Level) {
        (void)EFM_ProgramWord(EFM_PROTECT2_ADDR, EFM_PROTECT2_KEY);
    } else {
        /* rsvd */
    }
}

/**
 * @brief  Write the security code.
 * @param  [in] pu8Buf       Specifies the security code.
 * @param  [in] u32Len       Specified the length of the security code.
 * @retval int32_t
 */
int32_t EFM_WriteSecurityCode(uint8_t *pu8Buf, uint32_t u32Len)
{
    int32_t i32Ret = LL_OK;
    uint32_t u32Tmp;
    uint32_t u32LoopWords = u32Len >> 2UL;
    uint32_t *u32pSource = (uint32_t *)(uint32_t)pu8Buf;
    uint32_t *u32pDest = (uint32_t *)EFM_SECURITY_ADDR;

    DDL_ASSERT(IS_EFM_REG_UNLOCK());
    DDL_ASSERT(IS_EFM_FWMC_UNLOCK());
    DDL_ASSERT(IS_EFM_SECURITY_CODE_LEN(u32Len));

    /* CLear the error flag. */
    EFM_ClearStatus(EFM_FLAG_ALL);
    /* Get CACHE status */
    u32Tmp = READ_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);
    /* Disable CACHE */
    CLR_REG32_BIT(CM_EFM->FRMC, EFM_CACHE_ALL);

    /* Set sector erase mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_ERASE_SECTOR);
    /* Erase */
    RW_MEM32(EFM_SECURITY_ADDR) = 0UL;
    if (LL_ERR_TIMEOUT == EFM_WaitFlag(EFM_FLAG_RDY, EFM_PGM_TIMEOUT)) {
        i32Ret = LL_ERR_NOT_RDY;
    }
    /* CLear the operation end flag. */
    EFM_ClearStatus(EFM_FLAG_OPTEND);

    /* Set single program mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_PGM_SINGLE);

    while (u32LoopWords-- > 0UL) {
        /* program data. */
        *u32pDest++ = *u32pSource++;
        /* Wait for ready flag. */
        if (LL_ERR_TIMEOUT == EFM_WaitFlag(EFM_FLAG_RDY, EFM_PGM_TIMEOUT)) {
            i32Ret = LL_ERR_NOT_RDY;
        }
        /* CLear the operation end flag. */
        EFM_ClearStatus(EFM_FLAG_OPTEND);
    }

    /* Set read only mode. */
    MODIFY_REG32(CM_EFM->FWMC, EFM_FWMC_PEMOD, EFM_MD_READONLY);

    /* Recover CACHE function */
    MODIFY_REG32(CM_EFM->FRMC, EFM_CACHE_ALL, u32Tmp);
    return i32Ret;
}

/**
 * @}
 */

#endif  /* LL_EFM_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
