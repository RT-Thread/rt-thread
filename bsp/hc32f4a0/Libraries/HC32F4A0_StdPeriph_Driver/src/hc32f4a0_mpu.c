/**
 *******************************************************************************
 * @file  hc32f4a0_mpu.c
 * @brief This file provides firmware functions to manage the Memory Protection
 *        Unit(MPU).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
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
#include "hc32f4a0_mpu.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_MPU MPU
 * @brief Memory Protection Unit Driver Library
 * @{
 */

#if (DDL_MPU_ENABLE == DDL_ON)

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

/* Number of MPU unit */
#define MPU_UNIT_NUM                    (5UL)
/* Number of MPU region */
#define MPU_REGION_NUM                  (16UL)

/* MPU Register Combination Mask */
#define MPU_UNIT_CONFIG_MASK            (MPU_S1CR_SMPU1BRP  | MPU_S1CR_SMPU1BWP  | MPU_S1CR_SMPU1ACT)

/* DMA units with only 8 regions */
#define MPU_NORMAL_UNIT                 (MPU_UNIT_USBFS_DMA | MPU_UNIT_USBHS_DMA | MPU_UNIT_ETH_DMA)

/* Get the specified register address of the MPU Intrusion Control */
#define MPU_RGD(__NUM__)                ((uint32_t)(&(M4_MPU->RGD0))   + ((uint32_t)(__NUM__) << 2U))

#define MPU_RGE(__UNIT__)               ((uint32_t)(&(M4_MPU->S1RGE))  + (uint32_t)(__UNIT__))
#define MPU_RGWP(__UNIT__)              ((uint32_t)(&(M4_MPU->S1RGWP)) + (uint32_t)(__UNIT__))
#define MPU_RGRP(__UNIT__)              ((uint32_t)(&(M4_MPU->S1RGRP)) + (uint32_t)(__UNIT__))
#define MPU_CR(__UNIT__)                ((uint32_t)(&(M4_MPU->S1CR))   + (uint32_t)(__UNIT__))

/**
 * @defgroup MPU_Check_Parameters_Validity MPU Check Parameters Validity
 * @{
 */
#define IS_MPU_UNIT(x)                                                         \
(   ((x) != 0UL)                                &&                             \
    (((x) | MPU_UNIT_ALL) == MPU_UNIT_ALL))

#define IS_MPU_REGION(x)                                                       \
(   ((x) == MPU_REGION_NUM0)                    ||                             \
    ((x) == MPU_REGION_NUM1)                    ||                             \
    ((x) == MPU_REGION_NUM2)                    ||                             \
    ((x) == MPU_REGION_NUM3)                    ||                             \
    ((x) == MPU_REGION_NUM4)                    ||                             \
    ((x) == MPU_REGION_NUM5)                    ||                             \
    ((x) == MPU_REGION_NUM6)                    ||                             \
    ((x) == MPU_REGION_NUM7)                    ||                             \
    ((x) == MPU_REGION_NUM8)                    ||                             \
    ((x) == MPU_REGION_NUM9)                    ||                             \
    ((x) == MPU_REGION_NUM10)                   ||                             \
    ((x) == MPU_REGION_NUM11)                   ||                             \
    ((x) == MPU_REGION_NUM12)                   ||                             \
    ((x) == MPU_REGION_NUM13)                   ||                             \
    ((x) == MPU_REGION_NUM14)                   ||                             \
    ((x) == MPU_REGION_NUM15))

#define IS_MPU_UNIT_REGION(unit, region)                                       \
(   (((unit) & MPU_NORMAL_UNIT) == 0UL)         ||                             \
    (((region) == MPU_REGION_NUM0) ||                                          \
     ((region) == MPU_REGION_NUM1) ||                                          \
     ((region) == MPU_REGION_NUM2) ||                                          \
     ((region) == MPU_REGION_NUM3) ||                                          \
     ((region) == MPU_REGION_NUM4) ||                                          \
     ((region) == MPU_REGION_NUM5) ||                                          \
     ((region) == MPU_REGION_NUM6) ||                                          \
     ((region) == MPU_REGION_NUM7)))

#define IS_MPU_BKGRD_WR_PROTECT(x)                                             \
(   ((x) == MPU_BKGRD_WR_PROTECT_DISABLE)       ||                             \
    ((x) == MPU_BKGRD_WR_PROTECT_ENABLE))

#define IS_MPU_BKGRD_RD_PROTECT(x)                                             \
(   ((x) == MPU_BKGRD_RD_PROTECT_DISABLE)       ||                             \
    ((x) == MPU_BKGRD_RD_PROTECT_ENABLE))

#define IS_MPU_EXP_TYPE(x)                                                     \
(   ((x) == MPU_EXP_TYPE_NONE)                  ||                             \
    ((x) == MPU_EXP_TYPE_BUS_ERR)               ||                             \
    ((x) == MPU_EXP_TYPE_NMI)                   ||                             \
    ((x) == MPU_EXP_TYPE_RST))

#define IS_MPU_REGION_WR_PROTECT(x)                                            \
(   ((x) == MPU_REGION_WR_PROTECT_DISABLE)      ||                             \
    ((x) == MPU_REGION_WR_PROTECT_ENABLE))

#define IS_MPU_REGION_RD_PROTECT(x)                                            \
(   ((x) == MPU_REGION_RD_PROTECT_DISABLE)      ||                             \
    ((x) == MPU_REGION_RD_PROTECT_ENABLE))

#define IS_MPU_REGION_SIZE(x)                                                  \
(   ((x) == MPU_REGION_SIZE_32BYTE)             ||                             \
    ((x) == MPU_REGION_SIZE_64BYTE)             ||                             \
    ((x) == MPU_REGION_SIZE_128BYTE)            ||                             \
    ((x) == MPU_REGION_SIZE_256BYTE)            ||                             \
    ((x) == MPU_REGION_SIZE_512BYTE)            ||                             \
    ((x) == MPU_REGION_SIZE_1KBYTE)             ||                             \
    ((x) == MPU_REGION_SIZE_2KBYTE)             ||                             \
    ((x) == MPU_REGION_SIZE_4KBYTE)             ||                             \
    ((x) == MPU_REGION_SIZE_8KBYTE)             ||                             \
    ((x) == MPU_REGION_SIZE_16KBYTE)            ||                             \
    ((x) == MPU_REGION_SIZE_32KBYTE)            ||                             \
    ((x) == MPU_REGION_SIZE_64KBYTE)            ||                             \
    ((x) == MPU_REGION_SIZE_128KBYTE)           ||                             \
    ((x) == MPU_REGION_SIZE_256KBYTE)           ||                             \
    ((x) == MPU_REGION_SIZE_512KBYTE)           ||                             \
    ((x) == MPU_REGION_SIZE_1MBYTE)             ||                             \
    ((x) == MPU_REGION_SIZE_2MBYTE)             ||                             \
    ((x) == MPU_REGION_SIZE_4MBYTE)             ||                             \
    ((x) == MPU_REGION_SIZE_8MBYTE)             ||                             \
    ((x) == MPU_REGION_SIZE_16MBYTE)            ||                             \
    ((x) == MPU_REGION_SIZE_32MBYTE)            ||                             \
    ((x) == MPU_REGION_SIZE_64MBYTE)            ||                             \
    ((x) == MPU_REGION_SIZE_128MBYTE)           ||                             \
    ((x) == MPU_REGION_SIZE_256MBYTE)           ||                             \
    ((x) == MPU_REGION_SIZE_512MBYTE)           ||                             \
    ((x) == MPU_REGION_SIZE_1GBYTE)             ||                             \
    ((x) == MPU_REGION_SIZE_2GBYTE)             ||                             \
    ((x) == MPU_REGION_SIZE_4GBYTE))

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

#define IS_MPU_UNLOCK()             ((M4_MPU->WP & MPU_WP_MPUWE) == MPU_WP_MPUWE)

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

    for (i = 0UL; i < MPU_REGION_NUM; i++)
    {
        RGD = (__IO uint32_t *)MPU_RGD(i);
        WRITE_REG32(*RGD, 0UL);
    }
    WRITE_REG32(M4_MPU->ECLR, 0x1FUL);
    WRITE_REG32(M4_MPU->IPPR, 0UL);
    for (i = 0UL; i < MPU_UNIT_NUM; i++)
    {
        RGE = (__IO uint32_t *)MPU_RGE(i << 4);
        WRITE_REG32(*RGE, 0UL);
        RGWP = (__IO uint32_t *)MPU_RGWP(i << 4);
        WRITE_REG32(*RGWP, 0UL);
        RGRP = (__IO uint32_t *)MPU_RGRP(i << 4);
        WRITE_REG32(*RGRP, 0UL);
        CR = (__IO uint32_t *)MPU_CR(i << 4);
        WRITE_REG32(*CR, 0UL);
    }
}

/**
 * @brief  Initialize MPU.
 * @param  [in] pstcMpuInit             Pointer to a @ref stc_mpu_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t MPU_Init(const stc_mpu_init_t *pstcMpuInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcMpuInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_MPU_UNLOCK());
        DDL_ASSERT(IS_MPU_EXP_TYPE(pstcMpuInit->stcDma1.u32ExceptionType));
        DDL_ASSERT(IS_MPU_EXP_TYPE(pstcMpuInit->stcDma2.u32ExceptionType));
        DDL_ASSERT(IS_MPU_EXP_TYPE(pstcMpuInit->stcUsbFSDma.u32ExceptionType));
        DDL_ASSERT(IS_MPU_EXP_TYPE(pstcMpuInit->stcUsbHSDma.u32ExceptionType));
        DDL_ASSERT(IS_MPU_EXP_TYPE(pstcMpuInit->stcEthDma.u32ExceptionType));
        DDL_ASSERT(IS_MPU_BKGRD_WR_PROTECT(pstcMpuInit->stcDma1.u32BackgroundWriteProtect));
        DDL_ASSERT(IS_MPU_BKGRD_WR_PROTECT(pstcMpuInit->stcDma2.u32BackgroundWriteProtect));
        DDL_ASSERT(IS_MPU_BKGRD_WR_PROTECT(pstcMpuInit->stcUsbFSDma.u32BackgroundWriteProtect));
        DDL_ASSERT(IS_MPU_BKGRD_WR_PROTECT(pstcMpuInit->stcUsbHSDma.u32BackgroundWriteProtect));
        DDL_ASSERT(IS_MPU_BKGRD_WR_PROTECT(pstcMpuInit->stcEthDma.u32BackgroundWriteProtect));
        DDL_ASSERT(IS_MPU_BKGRD_RD_PROTECT(pstcMpuInit->stcDma1.u32BackgroundReadProtect));
        DDL_ASSERT(IS_MPU_BKGRD_RD_PROTECT(pstcMpuInit->stcDma2.u32BackgroundReadProtect));
        DDL_ASSERT(IS_MPU_BKGRD_RD_PROTECT(pstcMpuInit->stcUsbFSDma.u32BackgroundReadProtect));
        DDL_ASSERT(IS_MPU_BKGRD_RD_PROTECT(pstcMpuInit->stcUsbHSDma.u32BackgroundReadProtect));
        DDL_ASSERT(IS_MPU_BKGRD_RD_PROTECT(pstcMpuInit->stcEthDma.u32BackgroundReadProtect));

        MODIFY_REG32(M4_MPU->S1CR, MPU_UNIT_CONFIG_MASK,
                     (pstcMpuInit->stcDma1.u32ExceptionType              |
                      pstcMpuInit->stcDma1.u32BackgroundWriteProtect     | pstcMpuInit->stcDma1.u32BackgroundReadProtect));
        MODIFY_REG32(M4_MPU->S2CR, MPU_UNIT_CONFIG_MASK,
                     (pstcMpuInit->stcDma2.u32ExceptionType              |
                      pstcMpuInit->stcDma2.u32BackgroundWriteProtect     | pstcMpuInit->stcDma2.u32BackgroundReadProtect));
        MODIFY_REG32(M4_MPU->FCR, MPU_UNIT_CONFIG_MASK,
                     (pstcMpuInit->stcUsbFSDma.u32ExceptionType          |
                      pstcMpuInit->stcUsbFSDma.u32BackgroundWriteProtect | pstcMpuInit->stcUsbFSDma.u32BackgroundReadProtect));
        MODIFY_REG32(M4_MPU->HCR, MPU_UNIT_CONFIG_MASK,
                     (pstcMpuInit->stcUsbHSDma.u32ExceptionType          |
                      pstcMpuInit->stcUsbHSDma.u32BackgroundWriteProtect | pstcMpuInit->stcUsbHSDma.u32BackgroundReadProtect));
        MODIFY_REG32(M4_MPU->ECR, MPU_UNIT_CONFIG_MASK,
                     (pstcMpuInit->stcEthDma.u32ExceptionType            |
                      pstcMpuInit->stcEthDma.u32BackgroundWriteProtect   | pstcMpuInit->stcEthDma.u32BackgroundReadProtect));
    }

    return enRet;
}

/**
 * @brief  Fills each stc_mpu_init_t member with default value.
 * @param  [out] pstcMpuInit            Pointer to a @ref stc_mpu_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: stc_mpu_init_t member initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t MPU_StructInit(stc_mpu_init_t *pstcMpuInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcMpuInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcMpuInit->stcDma1.u32ExceptionType              = MPU_EXP_TYPE_NONE;
        pstcMpuInit->stcDma2.u32ExceptionType              = MPU_EXP_TYPE_NONE;
        pstcMpuInit->stcUsbFSDma.u32ExceptionType          = MPU_EXP_TYPE_NONE;
        pstcMpuInit->stcUsbHSDma.u32ExceptionType          = MPU_EXP_TYPE_NONE;
        pstcMpuInit->stcEthDma.u32ExceptionType            = MPU_EXP_TYPE_NONE;
        pstcMpuInit->stcDma1.u32BackgroundWriteProtect     = MPU_BKGRD_WR_PROTECT_DISABLE;
        pstcMpuInit->stcDma2.u32BackgroundWriteProtect     = MPU_BKGRD_WR_PROTECT_DISABLE;
        pstcMpuInit->stcUsbFSDma.u32BackgroundWriteProtect = MPU_BKGRD_WR_PROTECT_DISABLE;
        pstcMpuInit->stcUsbHSDma.u32BackgroundWriteProtect = MPU_BKGRD_WR_PROTECT_DISABLE;
        pstcMpuInit->stcEthDma.u32BackgroundWriteProtect   = MPU_BKGRD_WR_PROTECT_DISABLE;
        pstcMpuInit->stcDma1.u32BackgroundReadProtect      = MPU_BKGRD_RD_PROTECT_DISABLE;
        pstcMpuInit->stcDma2.u32BackgroundReadProtect      = MPU_BKGRD_RD_PROTECT_DISABLE;
        pstcMpuInit->stcUsbFSDma.u32BackgroundReadProtect  = MPU_BKGRD_RD_PROTECT_DISABLE;
        pstcMpuInit->stcUsbHSDma.u32BackgroundReadProtect  = MPU_BKGRD_RD_PROTECT_DISABLE;
        pstcMpuInit->stcEthDma.u32BackgroundReadProtect    = MPU_BKGRD_RD_PROTECT_DISABLE;
    }

    return enRet;
}

/**
 * @brief  Set the exception type of the unit.
 * @param  [in] u32Unit                 The type of MPU unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg MPU_UNIT_DMA1:        System DMA_1 MPU
 *           @arg MPU_UNIT_DMA2:        System DMA_2 MPU
 *           @arg MPU_UNIT_USBFS_DMA:   USBFS_DMA MPU
 *           @arg MPU_UNIT_USBHS_DMA:   USBHS_DMA MPU
 *           @arg MPU_UNIT_ETH_DMA:     ETH_DMA MPU
 * @param  [in] u32ExceptionType        Exception type of MPU unit.
 *         This parameter can be one of the following values:
 *           @arg MPU_EXP_TYPE_NONE:    The host unit access protection regions will be ignored
 *           @arg MPU_EXP_TYPE_BUS_ERR: The host unit access protection regions will be ignored and a bus error will be triggered
 *           @arg MPU_EXP_TYPE_NMI:     The host unit access protection regions will be ignored and a NMI interrupt will be triggered
 *           @arg MPU_EXP_TYPE_RST:     The host unit access protection regions will trigger the reset
 * @retval None
 */
void MPU_SetExceptionType(uint32_t u32Unit, uint32_t u32ExceptionType)
{
    __IO uint32_t *CR;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_UNIT(u32Unit));
    DDL_ASSERT(IS_MPU_EXP_TYPE(u32ExceptionType));

    u32Temp = u32Unit;
    while (0UL != u32Temp)
    {
        if (0UL != (u32Temp & 0x1UL))
        {
            CR = (__IO uint32_t *)MPU_CR(u32UnitPos);
            MODIFY_REG32(*CR, MPU_S1CR_SMPU1ACT, u32ExceptionType);
        }
        u32Temp >>= 1UL;
        u32UnitPos += 0x10U;
    }
}

/**
 * @brief  Enable or disable the write protection of the unit for background space.
 * @param  [in] u32Unit                 The type of MPU unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg MPU_UNIT_DMA1:        System DMA_1 MPU
 *           @arg MPU_UNIT_DMA2:        System DMA_2 MPU
 *           @arg MPU_UNIT_USBFS_DMA:   USBFS_DMA MPU
 *           @arg MPU_UNIT_USBHS_DMA:   USBHS_DMA MPU
 *           @arg MPU_UNIT_ETH_DMA:     ETH_DMA MPU
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void MPU_BackgroundWriteProtectCmd(uint32_t u32Unit, en_functional_state_t enNewState)
{
    __IO uint32_t *CR;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_UNIT(u32Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Temp = u32Unit;
    while (0UL != u32Temp)
    {
        if (0UL != (u32Temp & 0x1UL))
        {
            CR = (__IO uint32_t *)MPU_CR(u32UnitPos);
            if (Disable != enNewState)
            {
                SET_REG32_BIT(*CR, MPU_S1CR_SMPU1BWP);
            }
            else
            {
                CLEAR_REG32_BIT(*CR, MPU_S1CR_SMPU1BWP);
            }
        }
        u32Temp >>= 1UL;
        u32UnitPos += 0x10U;
    }
}

/**
 * @brief  Enable or disable the read protection of the unit for background space.
 * @param  [in] u32Unit                 The type of MPU unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg MPU_UNIT_DMA1:        System DMA_1 MPU
 *           @arg MPU_UNIT_DMA2:        System DMA_2 MPU
 *           @arg MPU_UNIT_USBFS_DMA:   USBFS_DMA MPU
 *           @arg MPU_UNIT_USBHS_DMA:   USBHS_DMA MPU
 *           @arg MPU_UNIT_ETH_DMA:     ETH_DMA MPU
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void MPU_BackgroundReadProtectCmd(uint32_t u32Unit, en_functional_state_t enNewState)
{
    __IO uint32_t *CR;
    uint32_t u32UnitPos = 0UL;
    uint32_t u32Temp;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_UNIT(u32Unit));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Temp = u32Unit;
    while (0UL != u32Temp)
    {
        if (0UL != (u32Temp & 0x1UL))
        {
            CR = (__IO uint32_t *)MPU_CR(u32UnitPos);
            if (Disable != enNewState)
            {
                SET_REG32_BIT(*CR, MPU_S1CR_SMPU1BRP);
            }
            else
            {
                CLEAR_REG32_BIT(*CR, MPU_S1CR_SMPU1BRP);
            }
        }
        u32Temp >>= 1UL;
        u32UnitPos += 0x10U;
    }
}

/**
 * @brief  Enable or disable the access control of the unit.
 * @param  [in] u32Unit                 The type of MPU unit.
 *         This parameter can be one or any combination of the following values:
 *           @arg MPU_UNIT_DMA1:        System DMA_1 MPU
 *           @arg MPU_UNIT_DMA2:        System DMA_2 MPU
 *           @arg MPU_UNIT_USBFS_DMA:   USBFS_DMA MPU
 *           @arg MPU_UNIT_USBHS_DMA:   USBHS_DMA MPU
 *           @arg MPU_UNIT_ETH_DMA:     ETH_DMA MPU
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
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
    while (0UL != u32Temp)
    {
        if (0UL != (u32Temp & 0x1UL))
        {
            CR = (__IO uint32_t *)MPU_CR(u32UnitPos);
            if (Disable != enNewState)
            {
                SET_REG32_BIT(*CR, MPU_S1CR_SMPU1E);
            }
            else
            {
                CLEAR_REG32_BIT(*CR, MPU_S1CR_SMPU1E);
            }
        }
        u32Temp >>= 1UL;
        u32UnitPos += 0x10U;
    }
}

/**
 * @brief  Gets the status of MPU flag.
 * @param  [in] u32Flag                 The type of MPU flag.
 *         This parameter can be one or any combination of the following values:
 *           @arg MPU_FLAG_SMPU1EAF:    System DMA_1 error flag
 *           @arg MPU_FLAG_SMPU2EAF:    System DMA_2 error flag
 *           @arg MPU_FLAG_FMPUEAF:     USBFS_DMA error flag
 *           @arg MPU_FLAG_HMPUEAF:     USBHS_DMA error flag
 *           @arg MPU_FLAG_EMPUEAF:     ETH_DMA error flag
 *           @arg MPU_FLAG_ALL:         All of the above
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t MPU_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_FLAG(u32Flag));

    if (0UL != (READ_REG32_BIT(M4_MPU->SR, u32Flag)))
    {
        enFlagSta = Set;
    }

    return enFlagSta;
}

/**
 * @brief  Clear the flag of MPU.
 * @param  [in] u32Flag                 The type of MPU flag.
 *         This parameter can be one or any combination of the following values:
 *           @arg MPU_FLAG_SMPU1EAF:    System DMA_1 error flag
 *           @arg MPU_FLAG_SMPU2EAF:    System DMA_2 error flag
 *           @arg MPU_FLAG_FMPUEAF:     USBFS_DMA error flag
 *           @arg MPU_FLAG_HMPUEAF:     USBHS_DMA error flag
 *           @arg MPU_FLAG_EMPUEAF:     ETH_DMA error flag
 *           @arg MPU_FLAG_ALL:         All of the above
 * @retval None
 */
void MPU_ClearStatus(uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_MPU_FLAG(u32Flag));

    SET_REG32_BIT(M4_MPU->ECLR, u32Flag);
}

/**
 * @brief  Initialize the region.
 * @note   'MPU_REGION_NUM8' to 'MPU_REGION_NUM15' are only valid when the MPU unit is 'MPU_UNIT_DMA1' or 'MPU_UNIT_DMA2'.
 * @note   The effective bits of the 'u32BaseAddr' are related to the 'u32Size' of the region,
 *         and the low 'u32Size+1' bits are fixed at 0.
 * @param  [in] u32Num                  The number of the regsion.
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
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t MPU_RegionInit(uint32_t u32Num, const stc_mpu_region_init_t *pstcRegionInit)
{
    en_result_t enRet = Ok;
    __IO uint32_t *RGD;
    __IO uint32_t *RGWP;
    __IO uint32_t *RGRP;
    uint32_t i;
    uint32_t u32UnitNum = MPU_UNIT_NUM;
    stc_mpu_region_permission_t RegionBuffer[MPU_UNIT_NUM];

    if (NULL == pstcRegionInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_MPU_UNLOCK());
        DDL_ASSERT(IS_MPU_REGION(u32Num));
        DDL_ASSERT(IS_MPU_REGION_SIZE(pstcRegionInit->u32Size));
        DDL_ASSERT(IS_MPU_REGION_BASE_ADDER(pstcRegionInit->u32BaseAddr, pstcRegionInit->u32Size));
        DDL_ASSERT(IS_MPU_REGION_WR_PROTECT(pstcRegionInit->stcDma1.u32WriteProtect));
        DDL_ASSERT(IS_MPU_REGION_WR_PROTECT(pstcRegionInit->stcDma2.u32WriteProtect));
        DDL_ASSERT(IS_MPU_REGION_WR_PROTECT(pstcRegionInit->stcUsbFSDma.u32WriteProtect));
        DDL_ASSERT(IS_MPU_REGION_WR_PROTECT(pstcRegionInit->stcUsbHSDma.u32WriteProtect));
        DDL_ASSERT(IS_MPU_REGION_WR_PROTECT(pstcRegionInit->stcEthDma.u32WriteProtect));
        DDL_ASSERT(IS_MPU_REGION_RD_PROTECT(pstcRegionInit->stcDma1.u32ReadProtect));
        DDL_ASSERT(IS_MPU_REGION_RD_PROTECT(pstcRegionInit->stcDma2.u32ReadProtect));
        DDL_ASSERT(IS_MPU_REGION_RD_PROTECT(pstcRegionInit->stcUsbFSDma.u32ReadProtect));
        DDL_ASSERT(IS_MPU_REGION_RD_PROTECT(pstcRegionInit->stcUsbHSDma.u32ReadProtect));
        DDL_ASSERT(IS_MPU_REGION_RD_PROTECT(pstcRegionInit->stcEthDma.u32ReadProtect));

        RGD = (__IO uint32_t *)MPU_RGD(u32Num);
        WRITE_REG32(*RGD, (pstcRegionInit->u32Size | pstcRegionInit->u32BaseAddr));
        /* Configure the read/write permission for the region */ 
        RegionBuffer[0] = pstcRegionInit->stcDma1;
        RegionBuffer[1] = pstcRegionInit->stcDma2;
        RegionBuffer[2] = pstcRegionInit->stcUsbFSDma;
        RegionBuffer[3] = pstcRegionInit->stcUsbHSDma;
        RegionBuffer[4] = pstcRegionInit->stcEthDma;
        if ((u32Num >= MPU_REGION_NUM8) && (u32Num <= MPU_REGION_NUM15))
        {
            u32UnitNum = 2UL;
        }
        for (i = 0UL; i < u32UnitNum; i++)
        {
            /* Configure the write permission for the region */
            RGWP = (__IO uint32_t *)MPU_RGWP(i << 4);
            if (MPU_REGION_WR_PROTECT_DISABLE != RegionBuffer[i].u32WriteProtect)
            {
                SET_REG32_BIT(*RGWP, (0x1UL << u32Num));
            }
            else
            {
                CLEAR_REG32_BIT(*RGWP, (0x1UL << u32Num));
            }
            /* Configure the read permission for the region */
            RGRP = (__IO uint32_t *)MPU_RGRP(i << 4);
            if (MPU_REGION_WR_PROTECT_DISABLE != RegionBuffer[i].u32ReadProtect)
            {
                SET_REG32_BIT(*RGRP, (0x1UL << u32Num));
            }
            else
            {
                CLEAR_REG32_BIT(*RGRP, (0x1UL << u32Num));
            }
        }
    }

    return enRet;
}

/**
 * @brief  Fills each stc_mpu_region_init_t member with default value.
 * @param  [out] pstcRegionInit         Pointer to a @ref stc_mpu_region_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: stc_mpu_region_init_t member initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t MPU_RegionStructInit(stc_mpu_region_init_t *pstcRegionInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcRegionInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcRegionInit->u32BaseAddr                 = 0UL;
        pstcRegionInit->u32Size                     = MPU_REGION_SIZE_32BYTE;
        pstcRegionInit->stcDma1.u32WriteProtect     = MPU_REGION_WR_PROTECT_DISABLE;
        pstcRegionInit->stcDma2.u32WriteProtect     = MPU_REGION_WR_PROTECT_DISABLE;
        pstcRegionInit->stcUsbFSDma.u32WriteProtect = MPU_REGION_WR_PROTECT_DISABLE;
        pstcRegionInit->stcUsbHSDma.u32WriteProtect = MPU_REGION_WR_PROTECT_DISABLE;
        pstcRegionInit->stcEthDma.u32WriteProtect   = MPU_REGION_WR_PROTECT_DISABLE;
        pstcRegionInit->stcDma1.u32ReadProtect      = MPU_REGION_RD_PROTECT_DISABLE;
        pstcRegionInit->stcDma2.u32ReadProtect      = MPU_REGION_RD_PROTECT_DISABLE;
        pstcRegionInit->stcUsbFSDma.u32ReadProtect  = MPU_REGION_RD_PROTECT_DISABLE;
        pstcRegionInit->stcUsbHSDma.u32ReadProtect  = MPU_REGION_RD_PROTECT_DISABLE;
        pstcRegionInit->stcEthDma.u32ReadProtect    = MPU_REGION_RD_PROTECT_DISABLE;
    }

    return enRet;
}

/**
 * @brief  Set the base address of the region.
 * @note   The effective bits of the 'u32Addr' are related to the 'size' of the region,
 *         and the low 'size+1' bits are fixed at 0.
 * @param  [in] u32Num                  The number of the regsion.
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

    RGD = (__IO uint32_t *)MPU_RGD(u32Num);
    /* Check parameters */
    DDL_ASSERT(IS_MPU_REGION_BASE_ADDER(u32Addr, READ_REG32_BIT(*RGD, MPU_RGD_MPURGSIZE)));

    MODIFY_REG32(*RGD, MPU_RGD_MPURGADDR, u32Addr);
}

/**
 * @brief  Set the size of the region.
 * @param  [in] u32Num                  The number of the regsion.
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
 *           @arg MPU_REGION_SIZE_32BYTE:       32 Byte
 *           @arg MPU_REGION_SIZE_64BYTE:       64 Byte
 *           @arg MPU_REGION_SIZE_128BYTE:      126 Byte
 *           @arg MPU_REGION_SIZE_256BYTE:      256 Byte
 *           @arg MPU_REGION_SIZE_512BYTE:      512 Byte
 *           @arg MPU_REGION_SIZE_1KBYTE:       1K Byte
 *           @arg MPU_REGION_SIZE_2KBYTE:       2K Byte
 *           @arg MPU_REGION_SIZE_4KBYTE:       4K Byte
 *           @arg MPU_REGION_SIZE_8KBYTE:       8K Byte
 *           @arg MPU_REGION_SIZE_16KBYTE:      16K Byte
 *           @arg MPU_REGION_SIZE_32KBYTE:      32K Byte
 *           @arg MPU_REGION_SIZE_64KBYTE:      64K Byte
 *           @arg MPU_REGION_SIZE_128KBYTE:     128K Byte
 *           @arg MPU_REGION_SIZE_256KBYTE:     256K Byte
 *           @arg MPU_REGION_SIZE_512KBYTE:     512K Byte
 *           @arg MPU_REGION_SIZE_1MBYTE:       1M Byte
 *           @arg MPU_REGION_SIZE_2MBYTE:       2M Byte
 *           @arg MPU_REGION_SIZE_4MBYTE:       4M Byte
 *           @arg MPU_REGION_SIZE_8MBYTE:       8M Byte
 *           @arg MPU_REGION_SIZE_16MBYTE:      16M Byte
 *           @arg MPU_REGION_SIZE_32MBYTE:      32M Byte
 *           @arg MPU_REGION_SIZE_64MBYTE:      64M Byte
 *           @arg MPU_REGION_SIZE_128MBYTE:     128M Byte
 *           @arg MPU_REGION_SIZE_256MBYTE:     256M Byte
 *           @arg MPU_REGION_SIZE_512MBYTE:     512M Byte
 *           @arg MPU_REGION_SIZE_1GBYTE:       1G Byte
 *           @arg MPU_REGION_SIZE_2GBYTE:       2G Byte
 *           @arg MPU_REGION_SIZE_4GBYTE:       4G Byte
 * @retval None
 */
void MPU_SetRegionSize(uint32_t u32Num, uint32_t u32Size)
{
    __IO uint32_t *RGD;

    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_REGION(u32Num));
    DDL_ASSERT(IS_MPU_REGION_SIZE(u32Size));

    RGD = (__IO uint32_t *)MPU_RGD(u32Num);
    MODIFY_REG32(*RGD, MPU_RGD_MPURGSIZE, u32Size);
}

/**
 * @brief  Enable or disable the write protection of the unit for the region.
 * @note   'MPU_REGION_NUM8' to 'MPU_REGION_NUM15' are only valid when the MPU unit is 'MPU_UNIT_DMA1' or 'MPU_UNIT_DMA2'.
 * @param  [in] u32Num                  The number of the regsion.
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
 *           @arg MPU_UNIT_DMA1:        System DMA_1 MPU
 *           @arg MPU_UNIT_DMA2:        System DMA_2 MPU
 *           @arg MPU_UNIT_USBFS_DMA:   USBFS_DMA MPU
 *           @arg MPU_UNIT_USBHS_DMA:   USBHS_DMA MPU
 *           @arg MPU_UNIT_ETH_DMA:     ETH_DMA MPU
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void MPU_RegionWriteProtectCmd(uint32_t u32Num, uint32_t u32Unit, en_functional_state_t enNewState)
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
    while (0UL != u32Temp)
    {
        if (0UL != (u32Temp & 0x1UL))
        {
            /* Configure the write permission for the region */
            RGWP = (__IO uint32_t *)MPU_RGWP(u32UnitPos);
            if (Disable != enNewState)
            {
                SET_REG32_BIT(*RGWP, (0x1UL << u32Num));
            }
            else
            {
                CLEAR_REG32_BIT(*RGWP, (0x1UL << u32Num));
            }
        }
        u32Temp >>= 1UL;
        u32UnitPos += 0x10U;
    }
}

/**
 * @brief  Enable or disable the read protection of the unit for the region.
 * @note   'MPU_REGION_NUM8' to 'MPU_REGION_NUM15' are only valid when the MPU unit is 'MPU_UNIT_DMA1' or 'MPU_UNIT_DMA2'.
 * @param  [in] u32Num                  The number of the regsion.
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
 *           @arg MPU_UNIT_DMA1:        System DMA_1 MPU
 *           @arg MPU_UNIT_DMA2:        System DMA_2 MPU
 *           @arg MPU_UNIT_USBFS_DMA:   USBFS_DMA MPU
 *           @arg MPU_UNIT_USBHS_DMA:   USBHS_DMA MPU
 *           @arg MPU_UNIT_ETH_DMA:     ETH_DMA MPU
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void MPU_RegionReadProtectCmd(uint32_t u32Num, uint32_t u32Unit, en_functional_state_t enNewState)
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
    while (0UL != u32Temp)
    {
        if (0UL != (u32Temp & 0x1UL))
        {
            /* Configure the read permission for the region */
            RGRP = (__IO uint32_t *)MPU_RGRP(u32UnitPos);
            if (Disable != enNewState)
            {
                SET_REG32_BIT(*RGRP, (0x1UL << u32Num));
            }
            else
            {
                CLEAR_REG32_BIT(*RGRP, (0x1UL << u32Num));
            }
        }
        u32Temp >>= 1UL;
        u32UnitPos += 0x10U;
    }
}

/**
 * @brief  Enable or disable the access control of the unit for the region.
 * @note   'MPU_REGION_NUM8' to 'MPU_REGION_NUM15' are only valid when the MPU unit is 'MPU_UNIT_DMA1' or 'MPU_UNIT_DMA2'.
 * @param  [in] u32Num                  The number of the regsion.
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
 *           @arg MPU_UNIT_DMA1:        System DMA_1 MPU
 *           @arg MPU_UNIT_DMA2:        System DMA_2 MPU
 *           @arg MPU_UNIT_USBFS_DMA:   USBFS_DMA MPU
 *           @arg MPU_UNIT_USBHS_DMA:   USBHS_DMA MPU
 *           @arg MPU_UNIT_ETH_DMA:     ETH_DMA MPU
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
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
    while (0UL != u32Temp)
    {
        if (0UL != (u32Temp & 0x1UL))
        {
            RGE = (__IO uint32_t *)MPU_RGE(u32UnitPos);
            if (Disable != enNewState)
            {
                SET_REG32_BIT(*RGE, (0x1UL << u32Num));
            }
            else
            {
                CLEAR_REG32_BIT(*RGE, (0x1UL << u32Num));
            }
        }
        u32Temp >>= 1UL;
        u32UnitPos += 0x10U;
    }
}

/**
 * @brief  Set the type of exception to access the protected IP.
 * @param  [in] u32ExceptionType                Exception type of MPU IP.
 *         This parameter can be one of the following values:
 *           @arg MPU_IP_EXP_TYPE_NONE:         Access to the protected IP will be ignored
 *           @arg MPU_IP_EXP_TYPE_BUS_ERR:      Access to the protected IP will trigger a bus error
 * @retval None
 */
void MPU_IP_SetExceptionType(uint32_t u32ExceptionType)
{
    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_IP_EXP_TYPE(u32ExceptionType));

    WRITE_REG32(bM4_MPU->IPPR_b.BUSERRE, (u32ExceptionType >> MPU_IPPR_BUSERRE_POS));
}

/**
 * @brief  Enable or disable write protection for the IP.
 * @param  [in] u32Peripheral           The peripheral of the chip.
 *         This parameter can be one or any combination of the following values:
 *           @arg MPU_IP_AES:           AES module
 *           @arg MPU_IP_HASH:          HASH module
 *           @arg MPU_IP_TRNG:          TRNG module
 *           @arg MPU_IP_CRC:           CRC module
 *           @arg MPU_IP_FMC:           FMC module
 *           @arg MPU_IP_WDT:           WDT module
 *           @arg MPU_IP_SWDT:          SWDT module
 *           @arg MPU_IP_BKSRAM:        BKSRAM module
 *           @arg MPU_IP_RTC:           RTC module
 *           @arg MPU_IP_DMPU:          DMPU module
 *           @arg MPU_IP_SRAMC:         SRAMC module
 *           @arg MPU_IP_INTC:          INTC module
 *           @arg MPU_IP_SYSC:          SYSC module
 *           @arg MPU_IP_MSTP:          MSTP module
 *           @arg MPU_IP_ALL:           All of the above
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void MPU_IP_WriteProtectCmd(uint32_t u32Peripheral, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_IP_TYPE(u32Peripheral));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Disable != enNewState)
    {
        SET_REG32_BIT(M4_MPU->IPPR, (u32Peripheral << 1U));
    }
    else
    {
        CLEAR_REG32_BIT(M4_MPU->IPPR, (u32Peripheral << 1U));
    }
}

/**
 * @brief  Enable or disable read protection for the IP.
 * @param  [in] u32Peripheral           The peripheral of the chip.
 *         This parameter can be one or any combination of the following values:
 *           @arg MPU_IP_AES:           AES module
 *           @arg MPU_IP_HASH:          HASH module
 *           @arg MPU_IP_TRNG:          TRNG module
 *           @arg MPU_IP_CRC:           CRC module
 *           @arg MPU_IP_FMC:           FMC module
 *           @arg MPU_IP_WDT:           WDT module
 *           @arg MPU_IP_SWDT:          SWDT module
 *           @arg MPU_IP_BKSRAM:        BKSRAM module
 *           @arg MPU_IP_RTC:           RTC module
 *           @arg MPU_IP_DMPU:          DMPU module
 *           @arg MPU_IP_SRAMC:         SRAMC module
 *           @arg MPU_IP_INTC:          INTC module
 *           @arg MPU_IP_SYSC:          SYSC module
 *           @arg MPU_IP_MSTP:          MSTP module
 *           @arg MPU_IP_ALL:           All of the above
 * @param  [in] enNewState              The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void MPU_IP_ReadProtectCmd(uint32_t u32Peripheral, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_MPU_UNLOCK());
    DDL_ASSERT(IS_MPU_IP_TYPE(u32Peripheral));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Disable != enNewState)
    {
        SET_REG32_BIT(M4_MPU->IPPR, u32Peripheral);
    }
    else
    {
        CLEAR_REG32_BIT(M4_MPU->IPPR, u32Peripheral);
    }
}

/**
 * @}
 */

#endif /* DDL_MPU_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
