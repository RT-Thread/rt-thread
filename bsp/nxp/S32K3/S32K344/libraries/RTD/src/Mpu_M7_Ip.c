/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 5.0.0
*   Build Version        : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
*   Copyright 2020 - 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file       Mpu_M7_Ip.c
*
*   @defgroup   Mpu_M7_Ip Mpu M7 IPV Driver
*   @ingroup    Platform
*
*   @addtogroup Mpu_M7_Ip
*   @{
*/

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Mpu_M7_Ip.h"

#ifdef MPU_M7_IP_DEV_ERROR_DETECT
#if(MPU_M7_IP_DEV_ERROR_DETECT == STD_ON)
    #include "Devassert.h"
#endif
#endif

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_MPU_M7_IP_VENDOR_ID_C                      43
#define CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_MAJOR_VERSION_C       4
#define CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_MINOR_VERSION_C       7
#define CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_REVISION_VERSION_C    0
#define CDD_PLATFORM_MPU_M7_IP_SW_MAJOR_VERSION_C               5
#define CDD_PLATFORM_MPU_M7_IP_SW_MINOR_VERSION_C               0
#define CDD_PLATFORM_MPU_M7_IP_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Mpu_M7_Ip.h */
#if (CDD_PLATFORM_MPU_M7_IP_VENDOR_ID_C !=  CDD_PLATFORM_MPU_M7_IP_VENDOR_ID)
    #error "Mpu_M7_Ip.c and Mpu_M7_Ip.h have different vendor ids"
#endif
#if ((CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_MAJOR_VERSION_C    !=  CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_MAJOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_MINOR_VERSION_C    !=  CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_MINOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_REVISION_VERSION_C !=  CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Mpu_M7_Ip.c and Mpu_M7_Ip.h are different"
#endif
#if ((CDD_PLATFORM_MPU_M7_IP_SW_MAJOR_VERSION_C !=  CDD_PLATFORM_MPU_M7_IP_SW_MAJOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_SW_MINOR_VERSION_C !=  CDD_PLATFORM_MPU_M7_IP_SW_MINOR_VERSION) || \
     (CDD_PLATFORM_MPU_M7_IP_SW_PATCH_VERSION_C !=  CDD_PLATFORM_MPU_M7_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mpu_M7_Ip.c and Mpu_M7_Ip.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#ifdef MPU_M7_IP_DEV_ERROR_DETECT
#if(MPU_M7_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check if the files Mpu_M7_Ip.c and Devassert.h are of the same version */
    #if ((CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_MAJOR_VERSION_C != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
        (CDD_PLATFORM_MPU_M7_IP_AR_RELEASE_MINOR_VERSION_C != DEVASSERT_AR_RELEASE_MINOR_VERSION)     \
        )
        #error "AUTOSAR Version Numbers of Mpu_M7_Ip.c and Devassert.h are different"
    #endif
#endif
#endif
#endif
/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/
#ifdef  PLATFORM_IP_ENABLE_MPU_M7
#if  (PLATFORM_IP_ENABLE_MPU_M7 == STD_ON)

#define PLATFORM_START_SEC_CONST_8
#include "Platform_MemMap.h"

static const uint8 u8Mpu_M7_MemoryTypeValues[MPU_M7_MEM_NO] =
{
    /* 7-6, 5-3, 2, 1, 0 bit S always clear to not influence previous setting
     *      Res, TEX, S, C, B */
    0x00U, /*0b00000000,  MPU_M7_MEMORY_TYPE_STRONG_ORDER  */
    0x01U, /*0b00000001,  MPU_M7_MEMORY_TYPE_DEVICE_SHARED */
    0x02U, /*0b00000010,  MPU_M7_MEMORY_TYPE_NORMAL_IN_OUT_WRITE_THROUGH */
    0x03U, /*0b00000011,  MPU_M7_MEMORY_TYPE_NORMAL_IN_OUT_WRITE_BACK1 */
    0x08U, /*0b00001000,  MPU_M7_MEMORY_TYPE_NORMAL_IN_OUT_NO_CACHE */
    0x0BU, /*0b00001011,  MPU_M7_MEMORY_TYPE_NORMAL_IN_OUT_WRITE_BACK2 */
    0x10U, /*0b00010000,  MPU_M7_MEMORY_TYPE_DEVICE_NOSHARE */
    0x20U  /*0b00100000   MPU_M7_MEMORY_TYPE_NORMAL_CACHEABLE */
};
#define PLATFORM_STOP_SEC_CONST_8
#include "Platform_MemMap.h"

#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"
/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
void Mpu_M7_Ip_Init_Privileged(const Mpu_M7_Ip_ConfigType * pConfig);

void Mpu_M7_Ip_SetRegionConfig_Privileged(uint8 u8RegionNum,
                                          const Mpu_M7_Ip_RegionConfigType * const pUserConfigPtr
                                         );

void Mpu_M7_Ip_Deinit_Privileged(void);

void Mpu_M7_Ip_EnableRegion_Privileged(uint8 u8RegionNum, boolean bEnable);

void Mpu_M7_Ip_SetAccessRight_Privileged(uint8 u8RegionNum, Mpu_M7_Ip_AccessRightsType eRights);

static uint8 Mpu_M7_Ip_GetDRegion(S32_MPU_Type const * const base);

static uint32 Mpu_M7_Ip_CalculateRegionSize(uint32 u32StartAddr, uint32 u32EndAddr);

static void Mpu_M7_Ip_SetMemoryType(uint32 * pRegionAttr, Mpu_M7_Ip_MemoryType eType);

static void Mpu_M7_Ip_SetCachePolicies(uint32 * pRegionAttr,
                                       Mpu_M7_Ip_CachePolicyType eInnerPolicy,
                                       Mpu_M7_Ip_CachePolicyType eOuterPolicy
                                      );

static void Mpu_M7_Ip_ComputeAccessRights(uint32 * pRegionAttr, Mpu_M7_Ip_AccessRightsType eAccessRights);

static void Mpu_M7_Ip_GetErrorRegisters(uint32 * pMmfsr, uint32 * pAddress);

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
/*!
 *  @brief Get Memory regions
 *
 *  @param[in] base The MPU peripheral base address.
 *  @return Number of regions supported by MPU ,if 0 MPU is not supported by core.
 *
 */
static uint8 Mpu_M7_Ip_GetDRegion(S32_MPU_Type const * const base)
{
    return (uint8)((base->TYPE & S32_MPU_TYPE_DREGION_MASK)>>S32_MPU_TYPE_DREGION_SHIFT) & 0xFFU;
}

/*!
 * @brief Calculate log2(n) size for a specific region
 *
 * @param[in] u32StartAddr Region Start address
 * @param[in] u32EndAddr   Region End address
 *
 * @return Region size as a power of 2
 */
static uint32 Mpu_M7_Ip_CalculateRegionSize(uint32 u32StartAddr, uint32 u32EndAddr)
{
    uint32 u32FinalSize = 0UL;
    uint32 u32Size = 0UL;

    u32Size = u32EndAddr - u32StartAddr;
    while (u32Size > 0U)
    {
        u32FinalSize++;
        u32Size >>= 1U;
    }

    return u32FinalSize;
}

/*!
 * @brief Configure memory type
 *
 * @param[out] pRegionAttr RASR register where to save the attributes
 * @param[in]  eType       Memory type
 *
 * @return void
 */
static void Mpu_M7_Ip_SetMemoryType(uint32 * pRegionAttr, Mpu_M7_Ip_MemoryType eType)
{
    *pRegionAttr |= ((uint32)u8Mpu_M7_MemoryTypeValues[eType] << S32_MPU_A_RASR_B_SHIFT);
}

/*!
 * @brief Set inner and outer cache policies
 *
 * @param[out] pRegionAttr   RASR register where to save the attributes
 * @param[in]  eInnerPolicy  Inner cache policy
 * @param[in]  eOuterPolicy  Outer cache policy
 *
 * @return void
 */
static void Mpu_M7_Ip_SetCachePolicies(uint32 * pRegionAttr,
                                       Mpu_M7_Ip_CachePolicyType eInnerPolicy,
                                       Mpu_M7_Ip_CachePolicyType eOuterPolicy
                                      )
{
    *pRegionAttr |= S32_MPU_RASR_C((uint32)eInnerPolicy >> 1UL) | S32_MPU_RASR_B((uint32)eInnerPolicy);
    *pRegionAttr |= S32_MPU_RASR_TEX(0x4UL | (uint32)eOuterPolicy);
}

/*!
 * @brief Set access rights
 *
 * @param[out] pRegionAttr   RASR register where to save the attributes
 * @param[in]  eAccessRights Region access rights
 *
 * @return void
 */
static void Mpu_M7_Ip_ComputeAccessRights(uint32 * pRegionAttr, Mpu_M7_Ip_AccessRightsType eAccessRights)
{
    *pRegionAttr &= ~(S32_MPU_RASR_AP_MASK | S32_MPU_RASR_XN_MASK);
    *pRegionAttr |= S32_MPU_RASR_AP(eAccessRights);
    if (((uint8)eAccessRights & (uint8)MPU_M7_IP_EXECUTE_RIGHT_MASK) == (uint8)0U)
    {
        *pRegionAttr |= S32_MPU_RASR_XN(1UL);
    }
    else
    {
        *pRegionAttr &= ~S32_MPU_RASR_XN(1UL);
    }

}

/*!
 * @brief Retrieve fault information from SCB
 *
 * @param[out] pMmfsr   SCB->MMFSR register contents
 * @param[out] pAddress Address of the violation
 *
 * @return void
 */
static void Mpu_M7_Ip_GetErrorRegisters(uint32 * pMmfsr, uint32 * pAddress)
{
    MCAL_FAULT_INJECTION_POINT(T_MPU_M7_INJ);

    *pMmfsr = S32_SCB->CFSR & (uint32)MPU_M7_IP_SCB_CFSR_MMFSR_MASK_WITHOUT_VALID;
    if (((S32_SCB->CFSR & (uint32)S32_SCB_CFSR_MMFSR_MMARVALID_MASK) >> (uint32)S32_SCB_CFSR_MMFSR_MMARVALID_SHIFT) == (uint32)1UL)
    {
        *pAddress = (uint32)S32_SCB->MMFAR;
    }
    else
    {
        *pAddress = 0xFFFFFFFFUL;
    }
}

/**
 * @brief         Initializes the Memory Protection Unit general parameters and
 *                region configurations
 *
 * @details       This function is non-reentrant
 *
 * @param[in]     pConfig: pointer to configuration structure for MPU M7.
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
void Mpu_M7_Ip_Init_Privileged(const Mpu_M7_Ip_ConfigType * pConfig)
{
    uint8 u8Region;
    const Mpu_M7_Ip_RegionConfigType * regionCfg;
    S32_MPU_Type * base = S32_MPU;

#if (MPU_M7_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check the input parameters */
    DevAssert(pConfig != NULL_PTR);
    DevAssert(pConfig->pRegionConfigArr != NULL_PTR);
    DevAssert(pConfig->u8RegionCnt > 0U);
    DevAssert(pConfig->u8RegionCnt <= Mpu_M7_Ip_GetDRegion(base));
#endif

    /* Reset the peripheral to the default settings */
    Mpu_M7_Ip_Deinit();

    /* Configure MPU general settings */
    if (pConfig->bDefaultMapEn == TRUE)
    {
        base->CTRL |=S32_MPU_CTRL_PRIVDEFENA_MASK;
    }
    else
    {
        base->CTRL &= (~((uint32)S32_MPU_CTRL_PRIVDEFENA_MASK));
    }

    if (pConfig->bEnableRunHFNMI == TRUE)
    {
        base->CTRL |=S32_MPU_CTRL_HFNMIENA_MASK;
    }
    else
    {
        base->CTRL &= (~((uint32)S32_MPU_CTRL_HFNMIENA_MASK));
    }

    if (pConfig->bEnMemManageInterrupt == TRUE)
    {
        S32_SCB->SHCSR |= S32_SCB_SHCSR_MEMFAULTENA_MASK;
    }
    else
    {
        S32_SCB->SHCSR &= ~S32_SCB_SHCSR_MEMFAULTENA_MASK;
    }

    for (u8Region = 0U; u8Region < pConfig->u8RegionCnt; u8Region++)
    {
        regionCfg = &pConfig->pRegionConfigArr[u8Region];
        Mpu_M7_Ip_SetRegionConfig_Privileged((pConfig->pRegionConfigArr[u8Region]).u8RegionNum, regionCfg);
    }

    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();

    base->CTRL |= S32_MPU_CTRL_ENABLE(1U);

    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();
}

/**
 * @brief         Configures the region selected by u8RegionNum with the data from pUserConfigPtr
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum:    region number
 * @param[in]     pUserConfigPtr: pointer to the region configuration structure for MPU M7.
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
void Mpu_M7_Ip_SetRegionConfig_Privileged(uint8 u8RegionNum,
                                          const Mpu_M7_Ip_RegionConfigType * const pUserConfigPtr
                                         )
{
    S32_MPU_Type * base = S32_MPU;
    uint32 regionSize;
    uint32 regionAttributes = 0UL;

#if (MPU_M7_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check if the region size is at least the minimum supported */
    DevAssert(u8RegionNum < Mpu_M7_Ip_GetDRegion(base));
    DevAssert(pUserConfigPtr != NULL_PTR);
    DevAssert((pUserConfigPtr->u32EndAddr - pUserConfigPtr->u32StartAddr) >= MPU_M7_IP_MIN_REGION_SIZE);
#endif

    /* Calculate log2(region) */
    regionSize = Mpu_M7_Ip_CalculateRegionSize(pUserConfigPtr->u32StartAddr, pUserConfigPtr->u32EndAddr);

#if (MPU_M7_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check if the region start address is aligned to the region's size */
    DevAssert((pUserConfigPtr->u32StartAddr & ((1UL << regionSize) - 1UL)) == 0UL);
#endif
    SchM_Enter_Platform_PLATFORM_EXCLUSIVE_AREA_00();
    /* Set the region number */
    base->RNR = u8RegionNum;
    /* Set the region base address */
    base->RBAR = pUserConfigPtr->u32StartAddr;
    /* Set the region size */
    regionAttributes |= S32_MPU_RASR_SIZE(regionSize - 1UL);

    /* Configure sub region disable mask if the size of the region allows it */
    if ((pUserConfigPtr->u32EndAddr - pUserConfigPtr->u32StartAddr) >= MPU_M7_IP_MIN_REGION_SIZE)
    {
        regionAttributes |= S32_MPU_RASR_SRD(pUserConfigPtr->u8SubRegMask);
    }

    /* Configure shareability */
    if (pUserConfigPtr->bShareable == TRUE)
    {
        regionAttributes |=S32_MPU_RASR_S_MASK;
    }
    else
    {
        regionAttributes &= (~((uint32)S32_MPU_RASR_S_MASK));
    }

    /* Set memory attributes and cacheability options */
    if (pUserConfigPtr->eMemType != MPU_M7_MEM_NORMAL_CACHEABLE)
    {
        Mpu_M7_Ip_SetMemoryType(&regionAttributes, pUserConfigPtr->eMemType);
    }
    else
    {
        Mpu_M7_Ip_SetCachePolicies(&regionAttributes, pUserConfigPtr->eInnerCachePolicy, pUserConfigPtr->eOuterCachePolicy);
    }

    /* Compute access rights */
    Mpu_M7_Ip_ComputeAccessRights(&regionAttributes, pUserConfigPtr->eAccessRight);

    /* Enable Region */
    regionAttributes |= S32_MPU_RASR_ENABLE(1UL);

    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();

    /* Write final values */
    base->RASR = regionAttributes;

    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();
    SchM_Exit_Platform_PLATFORM_EXCLUSIVE_AREA_00();
}

/**
 * @brief         Disables the module and resets all region configurations
 *
 * @details       This function is Reentrant
 *
 * @return        void
 *
 * @api
 *
 * @pre
 * */
void Mpu_M7_Ip_Deinit_Privileged(void)
{
    uint8 region;
    S32_MPU_Type * base = S32_MPU;

    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();

    base->CTRL &= ~(S32_MPU_CTRL_PRIVDEFENA_MASK | S32_MPU_CTRL_HFNMIENA_MASK | S32_MPU_CTRL_ENABLE_MASK);

    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();

    for (region = 0U; region < Mpu_M7_Ip_GetDRegion(base); region++)
    {
        base->RNR = (uint32)region;
        base->RASR = 0UL;
        base->RBAR = 0UL;
    }
}

/**
 * @brief         Enables or disabled a specific MPU region
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum : Region to be modified
 * @param[in]     bEnable  : Specifies wheter the region is enabled or disabled
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
void Mpu_M7_Ip_EnableRegion_Privileged(uint8 u8RegionNum, boolean bEnable)
{
    S32_MPU_Type * base = S32_MPU;

#if (MPU_M7_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check the input parameters */
    DevAssert(u8RegionNum < Mpu_M7_Ip_GetDRegion(base));
#endif
    SchM_Enter_Platform_PLATFORM_EXCLUSIVE_AREA_01();
    base->RNR = (uint32)u8RegionNum;
    if (bEnable == TRUE)
    {
        MCAL_DATA_SYNC_BARRIER();
        MCAL_INSTRUCTION_SYNC_BARRIER();

        base->RASR |= S32_MPU_RASR_ENABLE(1UL);

        MCAL_DATA_SYNC_BARRIER();
        MCAL_INSTRUCTION_SYNC_BARRIER();
    }
    else
    {
        MCAL_DATA_SYNC_BARRIER();
        MCAL_INSTRUCTION_SYNC_BARRIER();

        base->RASR &= ~S32_MPU_RASR_ENABLE(1UL);

        MCAL_DATA_SYNC_BARRIER();
        MCAL_INSTRUCTION_SYNC_BARRIER();
    }
    SchM_Exit_Platform_PLATFORM_EXCLUSIVE_AREA_01();
}

/**
 * @brief         Modify the access rights for a specific region
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum : Region to be modified
 * @param[in]     eRights     : Specifies the new access rights
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
void Mpu_M7_Ip_SetAccessRight_Privileged(uint8 u8RegionNum, Mpu_M7_Ip_AccessRightsType eRights)
{
    uint32 regionAttributes;
    S32_MPU_Type * base = S32_MPU;

#if (MPU_M7_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check the input parameters */
    DevAssert(u8RegionNum < Mpu_M7_Ip_GetDRegion(base));
#endif
    SchM_Enter_Platform_PLATFORM_EXCLUSIVE_AREA_02();
    base->RNR = (uint32)u8RegionNum;
    regionAttributes = base->RASR;
    Mpu_M7_Ip_ComputeAccessRights(&regionAttributes, eRights);

    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();

    base->RASR = regionAttributes;

    MCAL_DATA_SYNC_BARRIER();
    MCAL_INSTRUCTION_SYNC_BARRIER();
    SchM_Exit_Platform_PLATFORM_EXCLUSIVE_AREA_02();

}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
 * @brief         Initializes the Memory Protection Unit general parameters and
 *                region configurations
 *
 * @details       This function is non-reentrant
 *
 * @param[in]     pConfig: pointer to configuration structure for MPU M7.
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
 /* @implements    Mpu_M7_Ip_Init_Activity */
void Mpu_M7_Ip_Init(const Mpu_M7_Ip_ConfigType * pConfig)
{
#ifdef MPU_M7_IP_ENABLE_USER_MODE_SUPPORT
    OsIf_Trusted_Call1param(Mpu_M7_Ip_Init_Privileged, pConfig);
#else
    Mpu_M7_Ip_Init_Privileged(pConfig);
#endif
}

/**
 * @brief         Configures the region selected by u8RegionNum with the data from pUserConfigPtr
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum      Region number
 * @param[in]     pUserConfigPtr   Pointer to the region configuration structure for MPU M7.
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
 /* @implements    Mpu_M7_Ip_SetRegionConfig_Activity */
void Mpu_M7_Ip_SetRegionConfig(uint8 u8RegionNum, const Mpu_M7_Ip_RegionConfigType * const pUserConfigPtr)
{
#ifdef MPU_M7_IP_ENABLE_USER_MODE_SUPPORT
    OsIf_Trusted_Call2params(Mpu_M7_Ip_SetRegionConfig_Privileged, u8RegionNum, pUserConfigPtr);
#else
    Mpu_M7_Ip_SetRegionConfig_Privileged(u8RegionNum, pUserConfigPtr);
#endif
}

/**
 * @brief         Disables the module and resets all region configurations
 *
 * @details       This function is Reentrant
 *
 * @return        void
 *
 * @api
 *
 * @pre
 * */
 /* @implements   Mpu_M7_Ip_Deinit_Activity */
void Mpu_M7_Ip_Deinit(void)
{
#ifdef MPU_M7_IP_ENABLE_USER_MODE_SUPPORT
    OsIf_Trusted_Call(Mpu_M7_Ip_Deinit_Privileged);
#else
    Mpu_M7_Ip_Deinit_Privileged();
#endif
}

/**
 * @brief         Enables or disabled a specific region
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum : Region to be modified
 * @param[in]     bEnable  : Specifies wheter the region is enabled or disabled
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
 /* @implements   Mpu_M7_Ip_EnableRegion_Activity */
void Mpu_M7_Ip_EnableRegion(uint8 u8RegionNum, boolean bEnable)
{
#ifdef MPU_M7_IP_ENABLE_USER_MODE_SUPPORT
    OsIf_Trusted_Call2params(Mpu_M7_Ip_EnableRegion_Privileged, u8RegionNum, bEnable);
#else
    Mpu_M7_Ip_EnableRegion_Privileged(u8RegionNum, bEnable);
#endif
}

/**
 * @brief         Modify the access rights for a specific region
 *
 * @details       This function is Reentrant
 *
 * @param[in]     u8RegionNum : Region to be modified
 * @param[in]     eRights     : Specifies the new access rights
 * @return        void
 *
 * @api
 *
 * @pre
 *
 * */
  /* @implements    Mpu_M7_Ip_SetAccessRight_Activity */
void Mpu_M7_Ip_SetAccessRight(uint8 u8RegionNum, Mpu_M7_Ip_AccessRightsType eRights)
{
#ifdef MPU_M7_IP_ENABLE_USER_MODE_SUPPORT
    OsIf_Trusted_Call2params(Mpu_M7_Ip_SetAccessRight_Privileged, u8RegionNum, eRights);
#else
    Mpu_M7_Ip_SetAccessRight_Privileged(u8RegionNum, eRights);
#endif
}

/**
 * @brief         Retrieve error details
 *
 * @details       This function is Reentrant
 *
 * @param[out]    pErrorDetails : Storage where the data will be saved
 *
 * @return        boolean
 * @retval        TRUE       if an error was present
 * @retval        FALSE      otherwise
 *
 * @api
 *
 * @pre
 *
 * */
 /* @implements    Mpu_M7_Ip_GetErrorDetails_Activity */
boolean Mpu_M7_Ip_GetErrorDetails(Mpu_M7_Ip_ErrorDetailsType * pErrorDetails)
{
    boolean bResult = FALSE;
    uint32  u32Mmfsr;
    uint32  u32MmfsrCopy;
    uint32  u32ErrorAddress;
    uint8   u8ErrorCount = 0U;

#if (MPU_M7_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(pErrorDetails != NULL_PTR);
#endif

#ifdef MPU_M7_IP_ENABLE_USER_MODE_SUPPORT
    OsIf_Trusted_Call2params(Mpu_M7_Ip_GetErrorRegisters, &u32Mmfsr, &u32ErrorAddress);
#else
    Mpu_M7_Ip_GetErrorRegisters(&u32Mmfsr, &u32ErrorAddress);
#endif
    u32MmfsrCopy = u32Mmfsr;
    while (u32Mmfsr != 0U)
    {
        u8ErrorCount += (uint8)(u32Mmfsr & 1UL);
        u32Mmfsr >>= 1UL;
    }

    if (u8ErrorCount > 1U)
    {
        pErrorDetails->eType = MPU_M7_MEMMAN_ERROR_MULTIPLE;
    }
    else
    {
        u32Mmfsr = u32MmfsrCopy;
        switch(u32Mmfsr)
        {
            case (1U << S32_SCB_CFSR_MMFSR_IACCVIOL_SHIFT):
                pErrorDetails->eType = MPU_M7_MEMMAN_ERROR_INSTRUCTION_ACCESS;
                break;
            case (1U << S32_SCB_CFSR_MMFSR_DACCVIOL_SHIFT):
                pErrorDetails->eType = MPU_M7_MEMMAN_ERROR_DATA_ACCESS;
                break;
            case (1U << S32_SCB_CFSR_MMFSR_MUNSTKERR_SHIFT):
                pErrorDetails->eType = MPU_M7_MEMMAN_ERROR_UNSTACK;
                break;
            case (1U << S32_SCB_CFSR_MMFSR_MSTKERR_SHIFT):
                pErrorDetails->eType = MPU_M7_MEMMAN_ERROR_STACK;
                break;
            case (1U << S32_SCB_CFSR_MMFSR_MLSPERR_SHIFT):
                pErrorDetails->eType = MPU_M7_MEMMAN_ERROR_FLOATING_POINT;
                break;
            default:
                pErrorDetails->eType = MPU_M7_MEMMAN_ERROR_NONE;
                break;
        }
    }

    pErrorDetails->u32Address = u32ErrorAddress;

    if (u8ErrorCount > 0U)
    {
        bResult = TRUE;
    }

    return bResult;
}

#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"

#endif
#endif  /* PLATFORM_IP_ENABLE_MPU_M7*/

#ifdef __cplusplus
}
#endif

/** @} */
