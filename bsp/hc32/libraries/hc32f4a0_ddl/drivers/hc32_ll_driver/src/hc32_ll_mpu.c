/**
 *******************************************************************************
 * @file  hc32_ll_mpu.c
 * @brief This file provides firmware functions to manage the Memory Protection
 *        Unit(MPU).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2023-01-15       CDT             Update define base on new head file
                                    Modify IS_MPU_SP_START_ADDR & SP start address
   2023-09-30       CDT             Modify typo
                                    Optimize MPU_ClearStatus function
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
#include "hc32_ll_mpu.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_MPU MPU
 * @brief Memory Protection Unit Driver Library
 * @{
 */

#if (LL_MPU_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup MPU_Local_Macros MPU Local Macros
 * @{
 */

/* Number of MPU region */
#define MPU_REGION_MAX_NUM              (16UL)

/* Number of MPU unit */
#define MPU_UNIT_MAX_NUM                (5UL)

/* Number of SP unit */

/* MPU Register Combination Mask */
#define MPU_UNIT_CONFIG_MASK            (MPU_SCR_SMPUBRP | MPU_SCR_SMPUBWP | MPU_SCR_SMPUACT)
/* DMA units have 16 regions */
#define MPU_16REGION_UNIT               (MPU_UNIT_DMA1 | MPU_UNIT_DMA2)

/* Get the specified register address of the MPU Intrusion Control */
#define MPU_RGD_ADDR(__NUM__)           (__IO uint32_t *)((uint32_t)(&(CM_MPU->RGD0)) + ((uint32_t)(__NUM__) << 2U))
#define MPU_RGE_ADDR(__UNIT__)          (__IO uint32_t *)((uint32_t)(&(CM_MPU->S1RGE))  + ((uint32_t)(__UNIT__) << 4U))
#define MPU_RGWP_ADDR(__UNIT__)         (__IO uint32_t *)((uint32_t)(&(CM_MPU->S1RGWP)) + ((uint32_t)(__UNIT__) << 4U))
#define MPU_RGRP_ADDR(__UNIT__)         (__IO uint32_t *)((uint32_t)(&(CM_MPU->S1RGRP)) + ((uint32_t)(__UNIT__) << 4U))
#define MPU_CR_ADDR(__UNIT__)           (__IO uint32_t *)((uint32_t)(&(CM_MPU->S1CR))   + ((uint32_t)(__UNIT__) << 4U))

/* Get the SP register address */

/**
 * @defgroup MPU_Check_Parameters_Validity MPU Check Parameters Validity
 * @{
 */
#define IS_MPU_UNIT(x)                                                         \
(   ((x) != 0UL)                                &&                             \
    (((x) | MPU_UNIT_ALL) == MPU_UNIT_ALL))

#define IS_MPU_REGION(x)                        ((x) <= MPU_REGION_NUM15)

#define IS_MPU_UNIT_REGION(unit, region)                                       \
(   (((unit) | MPU_16REGION_UNIT) == MPU_16REGION_UNIT)     ||                 \
    ((region) <= MPU_REGION_NUM7))

#define IS_MPU_BACKGROUND_WR(x)                                                \
(   ((x) == MPU_BACKGROUND_WR_DISABLE)          ||                             \
    ((x) == MPU_BACKGROUND_WR_ENABLE))

#define IS_MPU_BACKGROUND_RD(x)                                                \
(   ((x) == MPU_BACKGROUND_RD_DISABLE)          ||                             \
    ((x) == MPU_BACKGROUND_RD_ENABLE))

#define IS_MPU_EXP_TYPE(x)                                                     \
(   ((x) == MPU_EXP_TYPE_NONE)                  ||                             \
    ((x) == MPU_EXP_TYPE_BUS_ERR)               ||                             \
    ((x) == MPU_EXP_TYPE_NMI)                   ||                             \
    ((x) == MPU_EXP_TYPE_RST))

#define IS_MPU_REGION_WR(x)                                                    \
(   ((x) == MPU_REGION_WR_DISABLE)              ||                             \
    ((x) == MPU_REGION_WR_ENABLE))

#define IS_MPU_REGION_RD(x)                                                    \
(   ((x) == MPU_REGION_RD_DISABLE)              ||                             \
    ((x) == MPU_REGION_RD_ENABLE))

#define IS_MPU_REGION_SIZE(x)                                                  \
(   ((x) >= MPU_REGION_SIZE_32BYTE)             &&                             \
    ((x) <= MPU_REGION_SIZE_4GBYTE))

#define IS_MPU_REGION_BASE_ADDER(addr, size)                                   \
(   ((addr) & ((uint32_t)(~((uint64_t)0xFFFFFFFFUL << ((size) + 1U))))) == 0UL)

#define IS_MPU_FLAG(x)                                                         \
(   ((x) != 0UL)                                &&                             \
    (((x) | MPU_FLAG_ALL) == MPU_FLAG_ALL))

#define IS_MPU_IP_TYPE(x)                                                      \
(   ((x) != 0UL)                                &&                             \
    (((x) | MPU_IP_ALL) == MPU_IP_ALL))

#define IS_MPU_IP_EXP_TYPE(x)                                                  \
(   ((x) == MPU_IP_EXP_TYPE_NONE)               ||                             \
    ((x) == MPU_IP_EXP_TYPE_BUS_ERR))

#define IS_MPU_UNLOCK()                 ((CM_MPU->WP & MPU_WP_MPUWE) == MPU_WP_MPUWE)
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
 * @defgroup MPU_Global_Functions MPU Global Functions
 * @{
 */

/**
 * @brief  De-Initialize MPU.
 * @param  None
 * @retval None
 */
void MPU_DeInit(void)
{
    uint32_t i;
    __IO uint32_t *RGD;
    __IO uint32_t *RGE;
    __IO uint32_t *RGWP;
    __IO uint32_t *RGRP;
    __IO uint32_t *CR;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());

    for (i = 0UL; i < MPU_REGION_MAX_NUM; i++) {
        RGD = MPU_RGD_ADDR(i);
        WRITE_REG32(*RGD, 0UL);
    }
    WRITE_REG32(CM_MPU->ECLR, MPU_FLAG_ALL);
    WRITE_REG32(CM_MPU->IPPR, 0UL);
    for (i = 0UL; i < MPU_UNIT_MAX_NUM; i++) {
        RGE = MPU_RGE_ADDR(i);
        WRITE_REG32(*RGE, 0UL);
        RGWP = MPU_RGWP_ADDR(i);
        WRITE_REG32(*RGWP, 0UL);
        RGRP = MPU_RGRP_ADDR(i);
        WRITE_REG32(*RGRP, 0UL);
        CR = MPU_CR_ADDR(i);
        WRITE_REG32(*CR, 0UL);
    }
}

/**
 * @brief  Initialize MPU.
 * @param  [in] pstcMpuInit             Pointer to a @ref stc_mpu_init_t structure
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t MPU_Init(const stc_mpu_init_t *pstcMpuInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcMpuInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_MPU_UNLOCK());
        DDL_ASSERT(IS_MPU_EXP_TYPE(pstcMpuInit->stcDma1.u32ExceptionType));
        DDL_ASSERT(IS_MPU_BACKGROUND_WR(pstcMpuInit->stcDma1.u32BackgroundWrite));
        DDL_ASSERT(IS_MPU_BACKGROUND_RD(pstcMpuInit->stcDma1.u32BackgroundRead));
        DDL_ASSERT(IS_MPU_EXP_TYPE(pstcMpuInit->stcDma2.u32ExceptionType));
        DDL_ASSERT(IS_MPU_BACKGROUND_WR(pstcMpuInit->stcDma2.u32BackgroundWrite));
        DDL_ASSERT(IS_MPU_BACKGROUND_RD(pstcMpuInit->stcDma2.u32BackgroundRead));
        DDL_ASSERT(IS_MPU_EXP_TYPE(pstcMpuInit->stcUsbFSDma.u32ExceptionType));
        DDL_ASSERT(IS_MPU_BACKGROUND_WR(pstcMpuInit->stcUsbFSDma.u32BackgroundWrite));
        DDL_ASSERT(IS_MPU_BACKGROUND_RD(pstcMpuInit->stcUsbFSDma.u32BackgroundRead));
        DDL_ASSERT(IS_MPU_EXP_TYPE(pstcMpuInit->stcUsbHSDma.u32ExceptionType));
        DDL_ASSERT(IS_MPU_BACKGROUND_WR(pstcMpuInit->stcUsbHSDma.u32BackgroundWrite));
        DDL_ASSERT(IS_MPU_BACKGROUND_RD(pstcMpuInit->stcUsbHSDma.u32BackgroundRead));
        DDL_ASSERT(IS_MPU_EXP_TYPE(pstcMpuInit->stcEthDma.u32ExceptionType));
        DDL_ASSERT(IS_MPU_BACKGROUND_WR(pstcMpuInit->stcEthDma.u32BackgroundWrite));
        DDL_ASSERT(IS_MPU_BACKGROUND_RD(pstcMpuInit->stcEthDma.u32BackgroundRead));

        MODIFY_REG32(CM_MPU->S1CR, MPU_UNIT_CONFIG_MASK,
                     (pstcMpuInit->stcDma1.u32ExceptionType | pstcMpuInit->stcDma1.u32BackgroundWrite |
                      pstcMpuInit->stcDma1.u32BackgroundRead));
        MODIFY_REG32(CM_MPU->S2CR, MPU_UNIT_CONFIG_MASK,
                     (pstcMpuInit->stcDma2.u32ExceptionType | pstcMpuInit->stcDma2.u32BackgroundWrite |
                      pstcMpuInit->stcDma2.u32BackgroundRead));
        MODIFY_REG32(CM_MPU->FCR, MPU_UNIT_CONFIG_MASK,
                     (pstcMpuInit->stcUsbFSDma.u32ExceptionType | pstcMpuInit->stcUsbFSDma.u32BackgroundWrite |
                      pstcMpuInit->stcUsbFSDma.u32BackgroundRead));
        MODIFY_REG32(CM_MPU->HCR, MPU_UNIT_CONFIG_MASK,
                     (pstcMpuInit->stcUsbHSDma.u32ExceptionType | pstcMpuInit->stcUsbHSDma.u32BackgroundWrite |
                      pstcMpuInit->stcUsbHSDma.u32BackgroundRead));
        MODIFY_REG32(CM_MPU->ECR, MPU_UNIT_CONFIG_MASK,
                     (pstcMpuInit->stcEthDma.u32ExceptionType | pstcMpuInit->stcEthDma.u32BackgroundWrite |
                      pstcMpuInit->stcEthDma.u32BackgroundRead));
    }

    return i32Ret;
}

/**
 * @brief  Fills each stc_mpu_init_t member with default value.
 * @param  [out] pstcMpuInit            Pointer to a @ref stc_mpu_init_t structure
 * @retval int32_t:
 *           - LL_OK: stc_mpu_init_t member initialize success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t MPU_StructInit(stc_mpu_init_t *pstcMpuInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcMpuInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcMpuInit->stcDma1.u32ExceptionType       = MPU_EXP_TYPE_NONE;
        pstcMpuInit->stcDma1.u32BackgroundWrite     = MPU_BACKGROUND_WR_DISABLE;
        pstcMpuInit->stcDma1.u32BackgroundRead      = MPU_BACKGROUND_RD_DISABLE;
        pstcMpuInit->stcDma2.u32ExceptionType       = MPU_EXP_TYPE_NONE;
        pstcMpuInit->stcDma2.u32BackgroundWrite     = MPU_BACKGROUND_WR_DISABLE;
        pstcMpuInit->stcDma2.u32BackgroundRead      = MPU_BACKGROUND_RD_DISABLE;
        pstcMpuInit->stcUsbFSDma.u32ExceptionType   = MPU_EXP_TYPE_NONE;
        pstcMpuInit->stcUsbFSDma.u32BackgroundWrite = MPU_BACKGROUND_WR_DISABLE;
        pstcMpuInit->stcUsbFSDma.u32BackgroundRead  = MPU_BACKGROUND_RD_DISABLE;
        pstcMpuInit->stcUsbHSDma.u32ExceptionType   = MPU_EXP_TYPE_NONE;
        pstcMpuInit->stcUsbHSDma.u32BackgroundWrite = MPU_BACKGROUND_WR_DISABLE;
        pstcMpuInit->stcUsbHSDma.u32BackgroundRead  = MPU_BACKGROUND_RD_DISABLE;
        pstcMpuInit->stcEthDma.u32ExceptionType     = MPU_EXP_TYPE_NONE;
        pstcMpuInit->stcEthDma.u32BackgroundWrite   = MPU_BACKGROUND_WR_DISABLE;
        pstcMpuInit->stcEthDma.u32BackgroundRead    = MPU_BACKGROUND_RD_DISABLE;
    }

    return i32Ret;
}

/**
 * @brief  Set the exception type of the unit.
 * @param  [in] u32Unit                 The type of MPU unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref MPU_Unit_Type
 * @param  [in] u32Type                 Exception type of MPU unit.
 *         This parameter can be one of the following values:
 *           @arg MPU_EXP_TYPE_NONE:    The host unit access protection regions will be ignored
 *           @arg MPU_EXP_TYPE_BUS_ERR: The host unit access protection regions will be ignored and a bus error will be triggered
 *           @arg MPU_EXP_TYPE_NMI:     The host unit access protection regions will be ignored and a NMI interrupt will be triggered
 *           @arg MPU_EXP_TYPE_RST:     The host unit access protection regions will trigger the reset
 * @retval None
 */
void MPU_SetExceptionType(uint32_t u32Unit, uint32_t u32Type)
{
    __IO uint32_t *CR;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_UNIT(u32Unit));
    DDL_ASSERT(IS_MPU_EXP_TYPE(u32Type));

    u32Temp = u32Unit;
    while (0UL != u32Temp) {
        if (0UL != (u32Temp & 0x1UL)) {
            CR = MPU_CR_ADDR(u32UnitPos);
            MODIFY_REG32(*CR, MPU_SCR_SMPUACT, u32Type);
        }
        u32Temp >>= 1UL;
        u32UnitPos++;
    }
}

/**
 * @brief  Enable or disable the write of the unit for background space.
 * @param  [in] u32Unit                 The type of MPU unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref MPU_Unit_Type
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void MPU_BackgroundWriteCmd(uint32_t u32Unit, en_functional_state_t enNewState)
{
    __IO uint32_t *CR;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_UNIT(u32Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Temp = u32Unit;
    while (0UL != u32Temp) {
        if (0UL != (u32Temp & 0x1UL)) {
            CR = MPU_CR_ADDR(u32UnitPos);
            if (DISABLE != enNewState) {
                CLR_REG32_BIT(*CR, MPU_SCR_SMPUBWP);
            } else {
                SET_REG32_BIT(*CR, MPU_SCR_SMPUBWP);
            }
        }
        u32Temp >>= 1UL;
        u32UnitPos++;
    }
}

/**
 * @brief  Enable or disable the read of the unit for background space.
 * @param  [in] u32Unit                 The type of MPU unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref MPU_Unit_Type
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void MPU_BackgroundReadCmd(uint32_t u32Unit, en_functional_state_t enNewState)
{
    __IO uint32_t *CR;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_UNIT(u32Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Temp = u32Unit;
    while (0UL != u32Temp) {
        if (0UL != (u32Temp & 0x1UL)) {
            CR = MPU_CR_ADDR(u32UnitPos);
            if (DISABLE != enNewState) {
                CLR_REG32_BIT(*CR, MPU_SCR_SMPUBRP);
            } else {
                SET_REG32_BIT(*CR, MPU_SCR_SMPUBRP);
            }
        }
        u32Temp >>= 1UL;
        u32UnitPos++;
    }
}

/**
 * @brief  Enable or disable the access control of the unit.
 * @param  [in] u32Unit                 The type of MPU unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref MPU_Unit_Type
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void MPU_UnitCmd(uint32_t u32Unit, en_functional_state_t enNewState)
{
    __IO uint32_t *CR;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_UNIT(u32Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Temp = u32Unit;
    while (0UL != u32Temp) {
        if (0UL != (u32Temp & 0x1UL)) {
            CR = MPU_CR_ADDR(u32UnitPos);
            if (DISABLE != enNewState) {
                SET_REG32_BIT(*CR, MPU_SCR_SMPUE);
            } else {
                CLR_REG32_BIT(*CR, MPU_SCR_SMPUE);
            }
        }
        u32Temp >>= 1UL;
        u32UnitPos++;
    }
}

/**
 * @brief  Gets the status of MPU flag.
 * @param  [in] u32Flag                 The type of MPU flag.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref MPU_Flag
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t MPU_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(CM_MPU->SR, u32Flag))) {
        enFlagSta = SET;
    }

    return enFlagSta;
}

/**
 * @brief  Clear the flag of MPU.
 * @param  [in] u32Flag                 The type of MPU flag.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref MPU_Flag
 * @retval None
 */
void MPU_ClearStatus(uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_MPU_FLAG(u32Flag));

    WRITE_REG32(CM_MPU->ECLR, u32Flag);
}

/**
 * @brief  Initialize the region.
 * @note   'MPU_REGION_NUM8' to 'MPU_REGION_NUM15' are only valid when the MPU unit is 'MPU_UNIT_DMA1' or 'MPU_UNIT_DMA2'.
 * @note   The effective bits of the 'u32BaseAddr' are related to the 'u32Size' of the region,
 *         and the low 'u32Size+1' bits are fixed at 0.
 * @param  [in] u32Num                  The number of the region.
 *         This parameter can be one of the following values:
 *           @arg MPU_REGION_NUM0:      MPU region number 0
 *           @arg MPU_REGION_NUM1:      MPU region number 1
 *           @arg MPU_REGION_NUM2:      MPU region number 2
 *           @arg MPU_REGION_NUM3:      MPU region number 3
 *           @arg MPU_REGION_NUM4:      MPU region number 4
 *           @arg MPU_REGION_NUM5:      MPU region number 5
 *           @arg MPU_REGION_NUM6:      MPU region number 6
 *           @arg MPU_REGION_NUM7:      MPU region number 7
 *           @arg MPU_REGION_NUM8:      MPU region number 8
 *           @arg MPU_REGION_NUM9:      MPU region number 9
 *           @arg MPU_REGION_NUM10:     MPU region number 10
 *           @arg MPU_REGION_NUM11:     MPU region number 11
 *           @arg MPU_REGION_NUM12:     MPU region number 12
 *           @arg MPU_REGION_NUM13:     MPU region number 13
 *           @arg MPU_REGION_NUM14:     MPU region number 14
 *           @arg MPU_REGION_NUM15:     MPU region number 15
 * @param  [in] pstcRegionInit          Pointer to a @ref stc_mpu_region_init_t structure
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t MPU_RegionInit(uint32_t u32Num, const stc_mpu_region_init_t *pstcRegionInit)
{
    int32_t i32Ret = LL_OK;
    __IO uint32_t *RGD;
    __IO uint32_t *RGWP;
    __IO uint32_t *RGRP;
    uint32_t i;
    uint32_t u32UnitNum = MPU_UNIT_MAX_NUM;
    stc_mpu_region_permission_t RegionBuffer[MPU_UNIT_MAX_NUM];

    if (NULL == pstcRegionInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_MPU_UNLOCK());
        DDL_ASSERT(IS_MPU_REGION(u32Num));
        DDL_ASSERT(IS_MPU_REGION_SIZE(pstcRegionInit->u32Size));
        DDL_ASSERT(IS_MPU_REGION_BASE_ADDER(pstcRegionInit->u32BaseAddr, pstcRegionInit->u32Size));
        DDL_ASSERT(IS_MPU_REGION_WR(pstcRegionInit->stcDma1.u32RegionWrite));
        DDL_ASSERT(IS_MPU_REGION_RD(pstcRegionInit->stcDma1.u32RegionRead));
        DDL_ASSERT(IS_MPU_REGION_WR(pstcRegionInit->stcDma2.u32RegionWrite));
        DDL_ASSERT(IS_MPU_REGION_RD(pstcRegionInit->stcDma2.u32RegionRead));
        DDL_ASSERT(IS_MPU_REGION_WR(pstcRegionInit->stcUsbFSDma.u32RegionWrite));
        DDL_ASSERT(IS_MPU_REGION_RD(pstcRegionInit->stcUsbFSDma.u32RegionRead));
        DDL_ASSERT(IS_MPU_REGION_WR(pstcRegionInit->stcUsbHSDma.u32RegionWrite));
        DDL_ASSERT(IS_MPU_REGION_RD(pstcRegionInit->stcUsbHSDma.u32RegionRead));
        DDL_ASSERT(IS_MPU_REGION_WR(pstcRegionInit->stcEthDma.u32RegionWrite));
        DDL_ASSERT(IS_MPU_REGION_RD(pstcRegionInit->stcEthDma.u32RegionRead));

        RGD = MPU_RGD_ADDR(u32Num);
        WRITE_REG32(*RGD, (pstcRegionInit->u32Size | pstcRegionInit->u32BaseAddr));
        /* Configure the read/write permission for the region */
        RegionBuffer[0] = pstcRegionInit->stcDma1;
        RegionBuffer[1] = pstcRegionInit->stcDma2;
        RegionBuffer[2] = pstcRegionInit->stcUsbFSDma;
        RegionBuffer[3] = pstcRegionInit->stcUsbHSDma;
        RegionBuffer[4] = pstcRegionInit->stcEthDma;
        if ((u32Num >= MPU_REGION_NUM8) && (u32Num <= MPU_REGION_NUM15)) {
            u32UnitNum = 2UL;
        }
        for (i = 0UL; i < u32UnitNum; i++) {
            /* Configure the write permission for the region */
            RGWP = MPU_RGWP_ADDR(i);
            if (MPU_REGION_WR_DISABLE != RegionBuffer[i].u32RegionWrite) {
                CLR_REG32_BIT(*RGWP, (0x1UL << u32Num));
            } else {
                SET_REG32_BIT(*RGWP, (0x1UL << u32Num));
            }
            /* Configure the read permission for the region */
            RGRP = MPU_RGRP_ADDR(i);
            if (MPU_REGION_WR_DISABLE != RegionBuffer[i].u32RegionRead) {
                CLR_REG32_BIT(*RGRP, (0x1UL << u32Num));
            } else {
                SET_REG32_BIT(*RGRP, (0x1UL << u32Num));
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Fills each stc_mpu_region_init_t member with default value.
 * @param  [out] pstcRegionInit         Pointer to a @ref stc_mpu_region_init_t structure
 * @retval int32_t:
 *           - LL_OK: stc_mpu_region_init_t member initialize success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t MPU_RegionStructInit(stc_mpu_region_init_t *pstcRegionInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcRegionInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcRegionInit->u32BaseAddr                 = 0UL;
        pstcRegionInit->u32Size                     = MPU_REGION_SIZE_32BYTE;
        pstcRegionInit->stcDma1.u32RegionWrite      = MPU_REGION_WR_DISABLE;
        pstcRegionInit->stcDma1.u32RegionRead       = MPU_REGION_RD_DISABLE;
        pstcRegionInit->stcDma2.u32RegionWrite      = MPU_REGION_WR_DISABLE;
        pstcRegionInit->stcDma2.u32RegionRead       = MPU_REGION_RD_DISABLE;
        pstcRegionInit->stcUsbFSDma.u32RegionWrite  = MPU_REGION_WR_DISABLE;
        pstcRegionInit->stcUsbFSDma.u32RegionRead   = MPU_REGION_RD_DISABLE;
        pstcRegionInit->stcUsbHSDma.u32RegionWrite  = MPU_REGION_WR_DISABLE;
        pstcRegionInit->stcUsbHSDma.u32RegionRead   = MPU_REGION_RD_DISABLE;
        pstcRegionInit->stcEthDma.u32RegionWrite    = MPU_REGION_WR_DISABLE;
        pstcRegionInit->stcEthDma.u32RegionRead     = MPU_REGION_RD_DISABLE;
    }

    return i32Ret;
}

/**
 * @brief  Set the base address of the region.
 * @note   The effective bits of the 'u32Addr' are related to the 'size' of the region,
 *         and the low 'size+1' bits are fixed at 0.
 * @param  [in] u32Num                  The number of the region.
 *         This parameter can be one of the following values:
 *           @arg MPU_REGION_NUM0:      MPU region number 0
 *           @arg MPU_REGION_NUM1:      MPU region number 1
 *           @arg MPU_REGION_NUM2:      MPU region number 2
 *           @arg MPU_REGION_NUM3:      MPU region number 3
 *           @arg MPU_REGION_NUM4:      MPU region number 4
 *           @arg MPU_REGION_NUM5:      MPU region number 5
 *           @arg MPU_REGION_NUM6:      MPU region number 6
 *           @arg MPU_REGION_NUM7:      MPU region number 7
 *           @arg MPU_REGION_NUM8:      MPU region number 8
 *           @arg MPU_REGION_NUM9:      MPU region number 9
 *           @arg MPU_REGION_NUM10:     MPU region number 10
 *           @arg MPU_REGION_NUM11:     MPU region number 11
 *           @arg MPU_REGION_NUM12:     MPU region number 12
 *           @arg MPU_REGION_NUM13:     MPU region number 13
 *           @arg MPU_REGION_NUM14:     MPU region number 14
 *           @arg MPU_REGION_NUM15:     MPU region number 15
 * @param  [in] u32Addr                 The base address of the region.
 * @retval None
 */
void MPU_SetRegionBaseAddr(uint32_t u32Num, uint32_t u32Addr)
{
    __IO uint32_t *RGD;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_REGION(u32Num));

    RGD = MPU_RGD_ADDR(u32Num);
    /* Check parameters */
    DDL_ASSERT(IS_MPU_REGION_BASE_ADDER(u32Addr, READ_REG32_BIT(*RGD, MPU_RGD_MPURGSIZE)));

    MODIFY_REG32(*RGD, MPU_RGD_MPURGADDR, u32Addr);
}

/**
 * @brief  Set the size of the region.
 * @param  [in] u32Num                  The number of the region.
 *         This parameter can be one of the following values:
 *           @arg MPU_REGION_NUM0:      MPU region number 0
 *           @arg MPU_REGION_NUM1:      MPU region number 1
 *           @arg MPU_REGION_NUM2:      MPU region number 2
 *           @arg MPU_REGION_NUM3:      MPU region number 3
 *           @arg MPU_REGION_NUM4:      MPU region number 4
 *           @arg MPU_REGION_NUM5:      MPU region number 5
 *           @arg MPU_REGION_NUM6:      MPU region number 6
 *           @arg MPU_REGION_NUM7:      MPU region number 7
 *           @arg MPU_REGION_NUM8:      MPU region number 8
 *           @arg MPU_REGION_NUM9:      MPU region number 9
 *           @arg MPU_REGION_NUM10:     MPU region number 10
 *           @arg MPU_REGION_NUM11:     MPU region number 11
 *           @arg MPU_REGION_NUM12:     MPU region number 12
 *           @arg MPU_REGION_NUM13:     MPU region number 13
 *           @arg MPU_REGION_NUM14:     MPU region number 14
 *           @arg MPU_REGION_NUM15:     MPU region number 15
 * @param  [in] u32Size                 The size of the region.
 *         This parameter can be one of the following values:
 *           @arg MPU_REGION_SIZE_32BYTE:   32 Byte
 *           @arg MPU_REGION_SIZE_64BYTE:   64 Byte
 *           @arg MPU_REGION_SIZE_128BYTE:  126 Byte
 *           @arg MPU_REGION_SIZE_256BYTE:  256 Byte
 *           @arg MPU_REGION_SIZE_512BYTE:  512 Byte
 *           @arg MPU_REGION_SIZE_1KBYTE:   1K Byte
 *           @arg MPU_REGION_SIZE_2KBYTE:   2K Byte
 *           @arg MPU_REGION_SIZE_4KBYTE:   4K Byte
 *           @arg MPU_REGION_SIZE_8KBYTE:   8K Byte
 *           @arg MPU_REGION_SIZE_16KBYTE:  16K Byte
 *           @arg MPU_REGION_SIZE_32KBYTE:  32K Byte
 *           @arg MPU_REGION_SIZE_64KBYTE:  64K Byte
 *           @arg MPU_REGION_SIZE_128KBYTE: 128K Byte
 *           @arg MPU_REGION_SIZE_256KBYTE: 256K Byte
 *           @arg MPU_REGION_SIZE_512KBYTE: 512K Byte
 *           @arg MPU_REGION_SIZE_1MBYTE:   1M Byte
 *           @arg MPU_REGION_SIZE_2MBYTE:   2M Byte
 *           @arg MPU_REGION_SIZE_4MBYTE:   4M Byte
 *           @arg MPU_REGION_SIZE_8MBYTE:   8M Byte
 *           @arg MPU_REGION_SIZE_16MBYTE:  16M Byte
 *           @arg MPU_REGION_SIZE_32MBYTE:  32M Byte
 *           @arg MPU_REGION_SIZE_64MBYTE:  64M Byte
 *           @arg MPU_REGION_SIZE_128MBYTE: 128M Byte
 *           @arg MPU_REGION_SIZE_256MBYTE: 256M Byte
 *           @arg MPU_REGION_SIZE_512MBYTE: 512M Byte
 *           @arg MPU_REGION_SIZE_1GBYTE:   1G Byte
 *           @arg MPU_REGION_SIZE_2GBYTE:   2G Byte
 *           @arg MPU_REGION_SIZE_4GBYTE:   4G Byte
 * @retval None
 */
void MPU_SetRegionSize(uint32_t u32Num, uint32_t u32Size)
{
    __IO uint32_t *RGD;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_REGION(u32Num));
    DDL_ASSERT(IS_MPU_REGION_SIZE(u32Size));

    RGD = MPU_RGD_ADDR(u32Num);
    MODIFY_REG32(*RGD, MPU_RGD_MPURGSIZE, u32Size);
}

/**
 * @brief  Enable or disable the write of the unit for the region.
 * @note   'MPU_REGION_NUM8' to 'MPU_REGION_NUM15' are only valid when the MPU unit is 'MPU_UNIT_DMA1' or 'MPU_UNIT_DMA2'.
 * @param  [in] u32Num                  The number of the region.
 *         This parameter can be one of the following values:
 *           @arg MPU_REGION_NUM0:      MPU region number 0
 *           @arg MPU_REGION_NUM1:      MPU region number 1
 *           @arg MPU_REGION_NUM2:      MPU region number 2
 *           @arg MPU_REGION_NUM3:      MPU region number 3
 *           @arg MPU_REGION_NUM4:      MPU region number 4
 *           @arg MPU_REGION_NUM5:      MPU region number 5
 *           @arg MPU_REGION_NUM6:      MPU region number 6
 *           @arg MPU_REGION_NUM7:      MPU region number 7
 *           @arg MPU_REGION_NUM8:      MPU region number 8
 *           @arg MPU_REGION_NUM9:      MPU region number 9
 *           @arg MPU_REGION_NUM10:     MPU region number 10
 *           @arg MPU_REGION_NUM11:     MPU region number 11
 *           @arg MPU_REGION_NUM12:     MPU region number 12
 *           @arg MPU_REGION_NUM13:     MPU region number 13
 *           @arg MPU_REGION_NUM14:     MPU region number 14
 *           @arg MPU_REGION_NUM15:     MPU region number 15
 * @param  [in] u32Unit                 The type of MPU unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref MPU_Unit_Type
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void MPU_RegionWriteCmd(uint32_t u32Num, uint32_t u32Unit, en_functional_state_t enNewState)
{
    __IO uint32_t *RGWP;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_REGION(u32Num));
    DDL_ASSERT(IS_MPU_UNIT(u32Unit));
    DDL_ASSERT(IS_MPU_UNIT_REGION(u32Unit, u32Num));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Temp = u32Unit;
    while (0UL != u32Temp) {
        if (0UL != (u32Temp & 0x1UL)) {
            /* Configure the write permission for the region */
            RGWP = MPU_RGWP_ADDR(u32UnitPos);
            if (DISABLE != enNewState) {
                CLR_REG32_BIT(*RGWP, (0x1UL << u32Num));
            } else {
                SET_REG32_BIT(*RGWP, (0x1UL << u32Num));
            }
        }
        u32Temp >>= 1UL;
        u32UnitPos++;
    }
}

/**
 * @brief  Enable or disable the read of the unit for the region.
 * @note   'MPU_REGION_NUM8' to 'MPU_REGION_NUM15' are only valid when the MPU unit is 'MPU_UNIT_DMA1' or 'MPU_UNIT_DMA2'.
 * @param  [in] u32Num                  The number of the region.
 *         This parameter can be one of the following values:
 *           @arg MPU_REGION_NUM0:      MPU region number 0
 *           @arg MPU_REGION_NUM1:      MPU region number 1
 *           @arg MPU_REGION_NUM2:      MPU region number 2
 *           @arg MPU_REGION_NUM3:      MPU region number 3
 *           @arg MPU_REGION_NUM4:      MPU region number 4
 *           @arg MPU_REGION_NUM5:      MPU region number 5
 *           @arg MPU_REGION_NUM6:      MPU region number 6
 *           @arg MPU_REGION_NUM7:      MPU region number 7
 *           @arg MPU_REGION_NUM8:      MPU region number 8
 *           @arg MPU_REGION_NUM9:      MPU region number 9
 *           @arg MPU_REGION_NUM10:     MPU region number 10
 *           @arg MPU_REGION_NUM11:     MPU region number 11
 *           @arg MPU_REGION_NUM12:     MPU region number 12
 *           @arg MPU_REGION_NUM13:     MPU region number 13
 *           @arg MPU_REGION_NUM14:     MPU region number 14
 *           @arg MPU_REGION_NUM15:     MPU region number 15
 * @param  [in] u32Unit                 The type of MPU unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref MPU_Unit_Type
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void MPU_RegionReadCmd(uint32_t u32Num, uint32_t u32Unit, en_functional_state_t enNewState)
{
    __IO uint32_t *RGRP;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_REGION(u32Num));
    DDL_ASSERT(IS_MPU_UNIT(u32Unit));
    DDL_ASSERT(IS_MPU_UNIT_REGION(u32Unit, u32Num));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Temp = u32Unit;
    while (0UL != u32Temp) {
        if (0UL != (u32Temp & 0x1UL)) {
            /* Configure the read permission for the region */
            RGRP = MPU_RGRP_ADDR(u32UnitPos);
            if (DISABLE != enNewState) {
                CLR_REG32_BIT(*RGRP, (0x1UL << u32Num));
            } else {
                SET_REG32_BIT(*RGRP, (0x1UL << u32Num));
            }
        }
        u32Temp >>= 1UL;
        u32UnitPos++;
    }
}

/**
 * @brief  Enable or disable the access control of the unit for the region.
 * @note   'MPU_REGION_NUM8' to 'MPU_REGION_NUM15' are only valid when the MPU unit is 'MPU_UNIT_DMA1' or 'MPU_UNIT_DMA2'.
 * @param  [in] u32Num                  The number of the region.
 *         This parameter can be one of the following values:
 *           @arg MPU_REGION_NUM0:      MPU region number 0
 *           @arg MPU_REGION_NUM1:      MPU region number 1
 *           @arg MPU_REGION_NUM2:      MPU region number 2
 *           @arg MPU_REGION_NUM3:      MPU region number 3
 *           @arg MPU_REGION_NUM4:      MPU region number 4
 *           @arg MPU_REGION_NUM5:      MPU region number 5
 *           @arg MPU_REGION_NUM6:      MPU region number 6
 *           @arg MPU_REGION_NUM7:      MPU region number 7
 *           @arg MPU_REGION_NUM8:      MPU region number 8
 *           @arg MPU_REGION_NUM9:      MPU region number 9
 *           @arg MPU_REGION_NUM10:     MPU region number 10
 *           @arg MPU_REGION_NUM11:     MPU region number 11
 *           @arg MPU_REGION_NUM12:     MPU region number 12
 *           @arg MPU_REGION_NUM13:     MPU region number 13
 *           @arg MPU_REGION_NUM14:     MPU region number 14
 *           @arg MPU_REGION_NUM15:     MPU region number 15
 * @param  [in] u32Unit                 The type of MPU unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref MPU_Unit_Type
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void MPU_RegionCmd(uint32_t u32Num, uint32_t u32Unit, en_functional_state_t enNewState)
{
    __IO uint32_t *RGE;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_REGION(u32Num));
    DDL_ASSERT(IS_MPU_UNIT(u32Unit));
    DDL_ASSERT(IS_MPU_UNIT_REGION(u32Unit, u32Num));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Temp = u32Unit;
    while (0UL != u32Temp) {
        if (0UL != (u32Temp & 0x1UL)) {
            RGE = MPU_RGE_ADDR(u32UnitPos);
            if (DISABLE != enNewState) {
                SET_REG32_BIT(*RGE, (0x1UL << u32Num));
            } else {
                CLR_REG32_BIT(*RGE, (0x1UL << u32Num));
            }
        }
        u32Temp >>= 1UL;
        u32UnitPos++;
    }
}

/**
 * @brief  Set the type of exception to access the protected IP.
 * @param  [in] u32Type                 Exception type of MPU IP.
 *         This parameter can be one of the following values:
 *           @arg MPU_IP_EXP_TYPE_NONE:     Access to the protected IP will be ignored
 *           @arg MPU_IP_EXP_TYPE_BUS_ERR:  Access to the protected IP will trigger a bus error
 * @retval None
 */
void MPU_IP_SetExceptionType(uint32_t u32Type)
{
    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_IP_EXP_TYPE(u32Type));

    WRITE_REG32(bCM_MPU->IPPR_b.BUSERRE, (u32Type >> MPU_IPPR_BUSERRE_POS));
}

/**
 * @brief  Enable or disable write for the IP.
 * @param  [in] u32Periph               The peripheral of the chip.
 *         This parameter can be one or any combination of the following values:
 *           @arg MPU_IP_AES:           AES module
 *           @arg MPU_IP_HASH:          HASH module
 *           @arg MPU_IP_TRNG:          TRNG module
 *           @arg MPU_IP_CRC:           CRC module
 *           @arg MPU_IP_EFM:           EFM module
 *           @arg MPU_IP_WDT:           WDT module
 *           @arg MPU_IP_SWDT:          SWDT module
 *           @arg MPU_IP_BKSRAM:        BKSRAM module
 *           @arg MPU_IP_RTC:           RTC module
 *           @arg MPU_IP_MPU:           MPU module
 *           @arg MPU_IP_SRAMC:         SRAMC module
 *           @arg MPU_IP_INTC:          INTC module
 *           @arg MPU_IP_RMU_CMU_PWC:   RMU, CMU and PWC modules
 *           @arg MPU_IP_FCG:           PWR_FCG0/1/2/3 and PWR_FCG0PC registers
 *           @arg MPU_IP_ALL:           All of the above
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void MPU_IP_WriteCmd(uint32_t u32Periph, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_IP_TYPE(u32Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        CLR_REG32_BIT(CM_MPU->IPPR, (u32Periph << 1U));
    } else {
        SET_REG32_BIT(CM_MPU->IPPR, (u32Periph << 1U));
    }
}

/**
 * @brief  Enable or disable read for the IP.
 * @param  [in] u32Periph               The peripheral of the chip.
 *         This parameter can be one or any combination of the following values:
 *           @arg MPU_IP_AES:           AES module
 *           @arg MPU_IP_HASH:          HASH module
 *           @arg MPU_IP_TRNG:          TRNG module
 *           @arg MPU_IP_CRC:           CRC module
 *           @arg MPU_IP_EFM:           EFM module
 *           @arg MPU_IP_WDT:           WDT module
 *           @arg MPU_IP_SWDT:          SWDT module
 *           @arg MPU_IP_BKSRAM:        BKSRAM module
 *           @arg MPU_IP_RTC:           RTC module
 *           @arg MPU_IP_MPU:           MPU module
 *           @arg MPU_IP_SRAMC:         SRAMC module
 *           @arg MPU_IP_INTC:          INTC module
 *           @arg MPU_IP_RMU_CMU_PWC:   RMU, CMU and PWC modules
 *           @arg MPU_IP_FCG:           PWR_FCG0/1/2/3 and PWR_FCG0PC registers
 *           @arg MPU_IP_ALL:           All of the above
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void MPU_IP_ReadCmd(uint32_t u32Periph, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_IP_TYPE(u32Periph));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (DISABLE != enNewState) {
        CLR_REG32_BIT(CM_MPU->IPPR, u32Periph);
    } else {
        SET_REG32_BIT(CM_MPU->IPPR, u32Periph);
    }
}

/**
 * @}
 */

#endif /* LL_MPU_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
