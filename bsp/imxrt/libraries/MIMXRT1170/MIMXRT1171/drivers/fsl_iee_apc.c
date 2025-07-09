/*
 * Copyright 2020-2021,2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_iee_apc.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.iee_apc"
#endif

#define IOMUXC_LPSR_GPR_APC_ADDR_MASK 0xFFFFFFF8U

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Enable the APC IEE Region setting.
 *
 * This function enables IOMUXC LPSR GPR and APC IEE for setting the region.
 *
 * param base APC IEE peripheral address.
 */
void IEE_APC_GlobalEnable(IEE_APC_Type *base)
{
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
    /* APC_x bits in GPR2 to GPR25 only take effect when this bit is set high */
    IOMUXC_LPSR_GPR->GPR25 |= IOMUXC_LPSR_GPR_GPR25_APC_VALID_MASK;
    __DSB();
#else
    for(uint32_t i = (uint32_t)kIEE_APC_Region0; i <= (uint32_t)kIEE_APC_Region7; i++)
    {
      IEE_APC_RegionEnable(base, (iee_apc_region_t)i);
    }
#endif
    return;
}

/*!
 * brief Disables the APC IEE Region setting.
 *
 * This function disables IOMUXC LPSR GPR and APC IEE for setting the region.
 *
 * param base APC IEE peripheral address.
 */
void IEE_APC_GlobalDisable(IEE_APC_Type *base)
{
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
    /* APC_x bits in GPR2 to GPR25 only take effect when this bit is set high */
    IOMUXC_LPSR_GPR->GPR25 &= ~IOMUXC_LPSR_GPR_GPR25_APC_VALID_MASK;
    __DSB();
    return;
#else
    for(uint32_t i = (uint32_t)kIEE_APC_Region0; i <= (uint32_t)kIEE_APC_Region7; i++)
    {
      IEE_APC_RegionDisable(base, (iee_apc_region_t)i);
    }
#endif
}

/*!
 * brief Sets the APC IEE Memory Region setting.
 *
 * This function configure IOMUXC LPSR GPR and APC IEE for the encryption region.
 *
 * param base APC IEE peripheral address.
 * param region Selection of the APC IEE region to be configured.
 * param startAddr Start encryption adress for the selected APC IEE region.
 * param endAddr End encryption adress for the selected APC IEE region.
 */
status_t IEE_APC_SetRegionConfig(IEE_APC_Type *base, iee_apc_region_t region, uint32_t startAddr, uint32_t endAddr)
{
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
    /* bit[2:0] of adress must be zero
     *
     * Note: For i.MXRT1170, region is [bot:top), the end is open interval. So the bit[2:0] of the end address must
     * be zero.
     * Note: from design's aspect, 'top' means the top of the space, the higher address which is the end
     * address.
     */
    if ((startAddr & (~IOMUXC_LPSR_GPR_GPR3_APC_AC_R0_TOP_MASK)) != 0U ||
        (endAddr & (~IOMUXC_LPSR_GPR_GPR2_APC_AC_R0_BOT_MASK)) != 0U)
    {
        return kStatus_InvalidArgument;
    }
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) */

    if (region == kIEE_APC_Region0)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR2 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR3 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;

        base->REGION0_BOT_ADDR = startAddr >> 3u;
        base->REGION0_TOP_ADDR = endAddr >> 3u;
#else
        base->REGION0_BOT_ADDR = startAddr;
        base->REGION0_TOP_ADDR = endAddr;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) */
    }
    if (region == kIEE_APC_Region1)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR4 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR5 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        base->REGION1_BOT_ADDR = startAddr >> 3u;
        base->REGION1_TOP_ADDR = endAddr >> 3u;
#else
        base->REGION1_BOT_ADDR = startAddr;
        base->REGION1_TOP_ADDR = endAddr;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) */
    }
    if (region == kIEE_APC_Region2)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR6 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR7 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        base->REGION2_BOT_ADDR = startAddr >> 3;
        base->REGION2_TOP_ADDR = endAddr >> 3;
#else
        base->REGION2_BOT_ADDR = startAddr;
        base->REGION2_TOP_ADDR = endAddr;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) */
    }
    if (region == kIEE_APC_Region3)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR8 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR9 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        base->REGION3_BOT_ADDR = startAddr >> 3;
        base->REGION3_TOP_ADDR = endAddr >> 3;
#else
        base->REGION3_BOT_ADDR = startAddr;
        base->REGION3_TOP_ADDR = endAddr;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) */
    }
    if (region == kIEE_APC_Region4)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR10 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR11 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        base->REGION4_BOT_ADDR = startAddr >> 3;
        base->REGION4_TOP_ADDR = endAddr >> 3;
#else
        base->REGION4_BOT_ADDR = startAddr;
        base->REGION4_TOP_ADDR = endAddr;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) */
    }
    if (region == kIEE_APC_Region5)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR12 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR13 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        base->REGION5_BOT_ADDR = startAddr >> 3;
        base->REGION5_TOP_ADDR = endAddr >> 3;
#else
        base->REGION5_BOT_ADDR = startAddr;
        base->REGION5_TOP_ADDR = endAddr;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) */
    }
    if (region == kIEE_APC_Region6)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR14 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR15 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        base->REGION6_BOT_ADDR = startAddr >> 3;
        base->REGION6_TOP_ADDR = endAddr >> 3;
#else
        base->REGION6_BOT_ADDR = startAddr;
        base->REGION6_TOP_ADDR = endAddr;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) */
    }
    if (region == kIEE_APC_Region7)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR16 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR17 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        base->REGION7_BOT_ADDR = startAddr >> 3;
        base->REGION7_TOP_ADDR = endAddr >> 3;
#else
        base->REGION7_BOT_ADDR = startAddr;
        base->REGION7_TOP_ADDR = endAddr;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) */
    }

    return kStatus_Success;
}

#if !(defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u))
/*!
 * brief Lock the LPSR GPR and APC IEE configuration.
 *
 * This function locks writting to IOMUXC LPSR GPR and APC IEE encryption region setting registers.
 * Only system reset can clear the LPSR GPR and APC IEE-RDC_D0/1 Lock bit
 *
 * param base APC IEE peripheral address.
 * param region Selection of the APC IEE region to be locked.
 * param domain Domain ID to access the IEE APC registers of this region. The ID is drivn by TRDC.
 */
status_t IEE_APC_LockRegionConfig(IEE_APC_Type *base, iee_apc_region_t region, uint8_t domain)
{
    uint32_t didVal = 0u;
  
    if (region == kIEE_APC_Region0)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        didVal = base->REGION0_ACC_CTL ;
        /* Clear ALLOW_DID */
        didVal = didVal & (~IEE_APC_REGION0_ACC_CTL_ALLOW_DID_MASK);
        /* Set new acces control value */
        base->REGION0_ACC_CTL = didVal | IEE_APC_REGION0_ACC_CTL_ALLOW_DID(domain);
        
        /* Once this bit is set, the value of the lower half word can't be changed 
         * until next system reset. The access check against domain ID will only 
         * take effect once this bit is set. */
        base->REGION0_ACC_CTL |= IEE_APC_REGION0_ACC_CTL_LOCK_L_MASK;
        base->REGION0_ACC_CTL |= IEE_APC_REGION0_ACC_CTL_LOCK_H_MASK;
    }
    if (region == kIEE_APC_Region1)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        didVal = base->REGION1_ACC_CTL ;
        didVal = didVal & (~IEE_APC_REGION1_ACC_CTL_ALLOW_DID_MASK);
        base->REGION1_ACC_CTL = didVal | IEE_APC_REGION1_ACC_CTL_ALLOW_DID(domain);

        base->REGION1_ACC_CTL |= IEE_APC_REGION1_ACC_CTL_LOCK_L_MASK;
        base->REGION1_ACC_CTL |= IEE_APC_REGION1_ACC_CTL_LOCK_H_MASK;
    }
    if (region == kIEE_APC_Region2)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        didVal = base->REGION2_ACC_CTL ;
        didVal = didVal & (~IEE_APC_REGION2_ACC_CTL_ALLOW_DID_MASK);
        base->REGION2_ACC_CTL = didVal | IEE_APC_REGION2_ACC_CTL_ALLOW_DID(domain);
        
        base->REGION2_ACC_CTL |= IEE_APC_REGION2_ACC_CTL_LOCK_L_MASK;
        base->REGION2_ACC_CTL |= IEE_APC_REGION2_ACC_CTL_LOCK_H_MASK;
    }
    if (region == kIEE_APC_Region3)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        didVal = base->REGION3_ACC_CTL ;
        didVal = didVal & (~IEE_APC_REGION3_ACC_CTL_ALLOW_DID_MASK);
        base->REGION3_ACC_CTL = didVal | IEE_APC_REGION3_ACC_CTL_ALLOW_DID(domain);

        base->REGION3_ACC_CTL |= IEE_APC_REGION3_ACC_CTL_LOCK_L_MASK;
        base->REGION3_ACC_CTL |= IEE_APC_REGION3_ACC_CTL_LOCK_H_MASK;
    }
    if (region == kIEE_APC_Region4)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        didVal = base->REGION4_ACC_CTL ;
        didVal = didVal & (~IEE_APC_REGION4_ACC_CTL_ALLOW_DID_MASK);
        base->REGION4_ACC_CTL = didVal | IEE_APC_REGION4_ACC_CTL_ALLOW_DID(domain);

        
        base->REGION4_ACC_CTL |= IEE_APC_REGION4_ACC_CTL_LOCK_L_MASK;
        base->REGION4_ACC_CTL |= IEE_APC_REGION4_ACC_CTL_LOCK_H_MASK;
    }
    if (region == kIEE_APC_Region5)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        didVal = base->REGION5_ACC_CTL ;
        didVal = didVal & (~IEE_APC_REGION5_ACC_CTL_ALLOW_DID_MASK);
        base->REGION5_ACC_CTL = didVal | IEE_APC_REGION5_ACC_CTL_ALLOW_DID(domain);
        
        base->REGION5_ACC_CTL |= IEE_APC_REGION5_ACC_CTL_LOCK_L_MASK;
        base->REGION5_ACC_CTL |= IEE_APC_REGION5_ACC_CTL_LOCK_H_MASK;
    }
    if (region == kIEE_APC_Region6)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        didVal = base->REGION6_ACC_CTL ;
        didVal = didVal & (~IEE_APC_REGION6_ACC_CTL_ALLOW_DID_MASK);
        base->REGION6_ACC_CTL = didVal | IEE_APC_REGION6_ACC_CTL_ALLOW_DID(domain);
        
        base->REGION6_ACC_CTL |= IEE_APC_REGION6_ACC_CTL_LOCK_L_MASK;
        base->REGION6_ACC_CTL |= IEE_APC_REGION6_ACC_CTL_LOCK_H_MASK;
    }
    if (region == kIEE_APC_Region7)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        didVal = base->REGION7_ACC_CTL ;
        didVal = didVal & (~IEE_APC_REGION7_ACC_CTL_ALLOW_DID_MASK);
        base->REGION7_ACC_CTL = didVal | IEE_APC_REGION7_ACC_CTL_ALLOW_DID(domain);
        
        base->REGION7_ACC_CTL |= IEE_APC_REGION7_ACC_CTL_LOCK_L_MASK;
        base->REGION7_ACC_CTL |= IEE_APC_REGION7_ACC_CTL_LOCK_H_MASK;
    }

    return kStatus_Success;
}
#endif /* !(defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)) */

#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
/*!
 * brief Lock the LPSR GPR and APC IEE configuration.
 *
 * This function locks writting to IOMUXC LPSR GPR and APC IEE encryption region setting registers.
 * Only system reset can clear the LPSR GPR and APC IEE-RDC_D0/1 Lock bit
 *
 * param base APC IEE peripheral address.
 * param region Selection of the APC IEE region to be locked.
 * param domain Core domain ID
 */
status_t IEE_APC_LockRegionConfig(IEE_APC_Type *base, iee_apc_region_t region, iee_apc_domain_t domain)
{
    if (region == kIEE_APC_Region0)
    {
        /* Locks write into APC Region 0 BOT address */
        IOMUXC_LPSR_GPR->GPR2 |= IOMUXC_LPSR_GPR_GPR2_LOCK(1);
        /* Locks write into APC Region 0 TOP address */
        IOMUXC_LPSR_GPR->GPR3 |= IOMUXC_LPSR_GPR_GPR3_LOCK(1);
        /* Locks write into APC REGION 0 Valid, Debug, Sand box, Safe box, Execute only and Encrytp enable bits */
        IOMUXC_LPSR_GPR->GPR18 |= IOMUXC_LPSR_GPR_GPR18_LOCK(1);

        if (domain == kIEE_APC_Domain0)
        {
            base->REGION0_RDC_D0 |= IEE_APC_REGION0_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            base->REGION0_RDC_D0 |= IEE_APC_REGION0_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            base->REGION0_RDC_D1 |= IEE_APC_REGION0_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            base->REGION0_RDC_D1 |= IEE_APC_REGION0_RDC_D1_RDC_D1_LOCK_MASK;
        }
        else
        {
            /* Intentional empty */
        }
    }
    if (region == kIEE_APC_Region1)
    {
        /* Locks write into APC Region 1 BOT address */
        IOMUXC_LPSR_GPR->GPR4 |= IOMUXC_LPSR_GPR_GPR4_LOCK(1);
        /* Locks write into APC Region 1 TOP address */
        IOMUXC_LPSR_GPR->GPR5 |= IOMUXC_LPSR_GPR_GPR5_LOCK(1);
        /* Locks write into APC REGION 1 Valid, Debug, Sand box, Safe box, Execute only and Encrytp enable bits */
        IOMUXC_LPSR_GPR->GPR19 |= IOMUXC_LPSR_GPR_GPR19_LOCK(1);

        if (domain == kIEE_APC_Domain0)
        {
            base->REGION1_RDC_D0 |= IEE_APC_REGION1_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            base->REGION1_RDC_D0 |= IEE_APC_REGION1_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            base->REGION1_RDC_D1 |= IEE_APC_REGION1_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            base->REGION1_RDC_D1 |= IEE_APC_REGION1_RDC_D1_RDC_D1_LOCK_MASK;
        }
        else
        {
            /* Intentional empty */
        }
    }
    if (region == kIEE_APC_Region2)
    {
        /* Locks write into APC Region 2 BOT address */
        IOMUXC_LPSR_GPR->GPR6 |= IOMUXC_LPSR_GPR_GPR6_LOCK(1);
        /* Locks write into APC Region 2 TOP address */
        IOMUXC_LPSR_GPR->GPR7 |= IOMUXC_LPSR_GPR_GPR7_LOCK(1);
        /* Locks write into APC REGION 2 Valid, Debug, Sand box, Safe box, Execute only and Encrytp enable bits */
        IOMUXC_LPSR_GPR->GPR20 |= IOMUXC_LPSR_GPR_GPR20_LOCK(1);

        if (domain == kIEE_APC_Domain0)
        {
            base->REGION2_RDC_D0 |= IEE_APC_REGION2_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            base->REGION2_RDC_D0 |= IEE_APC_REGION2_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            base->REGION2_RDC_D1 |= IEE_APC_REGION2_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            base->REGION2_RDC_D1 |= IEE_APC_REGION2_RDC_D1_RDC_D1_LOCK_MASK;
        }
        else
        {
            /* Intentional empty */
        }
    }
    if (region == kIEE_APC_Region3)
    {
        /* Locks write into APC Region 3 BOT address */
        IOMUXC_LPSR_GPR->GPR8 |= IOMUXC_LPSR_GPR_GPR8_LOCK(1);
        /* Locks write into APC Region 3 TOP address */
        IOMUXC_LPSR_GPR->GPR9 |= IOMUXC_LPSR_GPR_GPR9_LOCK(1);
        /* Locks write into APC REGION 3 Valid, Debug, Sand box, Safe box, Execute only and Encrytp enable bits */
        IOMUXC_LPSR_GPR->GPR21 |= IOMUXC_LPSR_GPR_GPR21_LOCK(1);

        if (domain == kIEE_APC_Domain0)
        {
            base->REGION3_RDC_D0 |= IEE_APC_REGION3_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            base->REGION3_RDC_D0 |= IEE_APC_REGION3_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            base->REGION3_RDC_D1 |= IEE_APC_REGION3_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            base->REGION3_RDC_D1 |= IEE_APC_REGION3_RDC_D1_RDC_D1_LOCK_MASK;
        }
        else
        {
            /* Intentional empty */
        }
    }
    if (region == kIEE_APC_Region4)
    {
        /* Locks write into APC Region 4 BOT address */
        IOMUXC_LPSR_GPR->GPR10 |= IOMUXC_LPSR_GPR_GPR10_LOCK(1);
        /* Locks write into APC Region 4 TOP address */
        IOMUXC_LPSR_GPR->GPR11 |= IOMUXC_LPSR_GPR_GPR11_LOCK(1);
        /* Locks write into APC REGION 4 Valid, Debug, Sand box, Safe box, Execute only and Encrytp enable bits */
        IOMUXC_LPSR_GPR->GPR22 |= IOMUXC_LPSR_GPR_GPR22_LOCK(1);

        if (domain == kIEE_APC_Domain0)
        {
            base->REGION4_RDC_D0 |= IEE_APC_REGION4_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            base->REGION4_RDC_D0 |= IEE_APC_REGION4_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            base->REGION4_RDC_D1 |= IEE_APC_REGION4_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            base->REGION4_RDC_D1 |= IEE_APC_REGION4_RDC_D1_RDC_D1_LOCK_MASK;
        }
        else
        {
            /* Intentional empty */
        }
    }
    if (region == kIEE_APC_Region5)
    {
        /* Locks write into APC Region 5 BOT address */
        IOMUXC_LPSR_GPR->GPR12 |= IOMUXC_LPSR_GPR_GPR12_LOCK(1);
        /* Locks write into APC Region 5 TOP address */
        IOMUXC_LPSR_GPR->GPR13 |= IOMUXC_LPSR_GPR_GPR13_LOCK(1);
        /* Locks write into APC REGION 5 Valid, Debug, Sand box, Safe box, Execute only and Encrytp enable bits */
        IOMUXC_LPSR_GPR->GPR23 |= IOMUXC_LPSR_GPR_GPR23_LOCK(1);

        if (domain == kIEE_APC_Domain0)
        {
            base->REGION5_RDC_D0 |= IEE_APC_REGION5_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            base->REGION5_RDC_D0 |= IEE_APC_REGION5_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            base->REGION5_RDC_D1 |= IEE_APC_REGION5_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            base->REGION5_RDC_D1 |= IEE_APC_REGION5_RDC_D1_RDC_D1_LOCK_MASK;
        }
        else
        {
            /* Intentional empty */
        }
    }
    if (region == kIEE_APC_Region6)
    {
        /* Locks write into APC Region 6 BOT address */
        IOMUXC_LPSR_GPR->GPR14 |= IOMUXC_LPSR_GPR_GPR14_LOCK(1);
        /* Locks write into APC Region 6 TOP address */
        IOMUXC_LPSR_GPR->GPR15 |= IOMUXC_LPSR_GPR_GPR15_LOCK(1);
        /* Locks write into APC REGION 6 Valid, Debug, Sand box, Safe box, Execute only and Encrytp enable bits */
        IOMUXC_LPSR_GPR->GPR24 |= IOMUXC_LPSR_GPR_GPR24_LOCK(1);

        if (domain == kIEE_APC_Domain0)
        {
            base->REGION6_RDC_D0 |= IEE_APC_REGION6_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            base->REGION6_RDC_D0 |= IEE_APC_REGION6_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            base->REGION6_RDC_D1 |= IEE_APC_REGION6_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            base->REGION6_RDC_D1 |= IEE_APC_REGION6_RDC_D1_RDC_D1_LOCK_MASK;
        }
        else
        {
            /* Intentional empty */
        }
    }
    if (region == kIEE_APC_Region7)
    {
        /* Locks write into APC Region 7 BOT address */
        IOMUXC_LPSR_GPR->GPR16 |= IOMUXC_LPSR_GPR_GPR15_LOCK(1);
        /* Locks write into APC Region 7 TOP address */
        IOMUXC_LPSR_GPR->GPR17 |= IOMUXC_LPSR_GPR_GPR16_LOCK(1);
        /* Locks write into APC REGION 7 Valid, Debug, Sand box, Safe box, Execute only and Encrytp enable bits */
        IOMUXC_LPSR_GPR->GPR25 |= IOMUXC_LPSR_GPR_GPR25_LOCK(1);

        if (domain == kIEE_APC_Domain0)
        {
            base->REGION7_RDC_D0 |= IEE_APC_REGION7_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            base->REGION7_RDC_D0 |= IEE_APC_REGION7_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            base->REGION7_RDC_D1 |= IEE_APC_REGION7_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            base->REGION7_RDC_D1 |= IEE_APC_REGION7_RDC_D1_RDC_D1_LOCK_MASK;
        }
        else
        {
            /* Intentional empty */
        }
    }

    return kStatus_Success;
}
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u) */

#if !(defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u))
/*!
 * brief Set access control of the APC IEE.
 *
 * This function configure APC IEE encryption region access control settings.
 *
 * param base APC IEE peripheral address.
 * param region Selection of the APC IEE region to be locked.
 * param allowNonSecure Allow nonsecure mode access
 * param allowUser Allow user mode access
 */
status_t IEE_APC_SetAccessControl(IEE_APC_Type *base, iee_apc_region_t region, bool allowNonSecure, bool allowUser)
{
    uint32_t allowCltVal = 0u;
  
    if (region == kIEE_APC_Region0)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        allowCltVal = base->REGION0_ACC_CTL;
        /* Clear allow user and ns */
        allowCltVal = allowCltVal & (~IEE_APC_REGION0_ACC_CTL_ALLOW_NS_MASK);
        allowCltVal = allowCltVal & (~IEE_APC_REGION0_ACC_CTL_ALLOW_USER_MASK);
        /* Set new acces control value */
        base->REGION0_ACC_CTL = allowCltVal | IEE_APC_REGION0_ACC_CTL_ALLOW_NS(allowNonSecure) | 
                                IEE_APC_REGION0_ACC_CTL_ALLOW_USER(allowUser);

    }
    if (region == kIEE_APC_Region1)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        allowCltVal = base->REGION1_ACC_CTL;
        /* Clear allow user and ns */
        allowCltVal = allowCltVal & (~IEE_APC_REGION1_ACC_CTL_ALLOW_NS_MASK);
        allowCltVal = allowCltVal & (~IEE_APC_REGION1_ACC_CTL_ALLOW_USER_MASK);
        /* Set new acces control value */
        base->REGION1_ACC_CTL = allowCltVal | IEE_APC_REGION1_ACC_CTL_ALLOW_NS(allowNonSecure) | 
                                IEE_APC_REGION1_ACC_CTL_ALLOW_USER(allowUser);
    }
    if (region == kIEE_APC_Region2)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        allowCltVal = base->REGION2_ACC_CTL;
        /* Clear allow user and ns */
        allowCltVal = allowCltVal & (~IEE_APC_REGION2_ACC_CTL_ALLOW_NS_MASK);
        allowCltVal = allowCltVal & (~IEE_APC_REGION2_ACC_CTL_ALLOW_USER_MASK);
        /* Set new acces control value */
        base->REGION2_ACC_CTL = allowCltVal | IEE_APC_REGION2_ACC_CTL_ALLOW_NS(allowNonSecure) | 
                                IEE_APC_REGION2_ACC_CTL_ALLOW_USER(allowUser);
    }
    if (region == kIEE_APC_Region3)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        allowCltVal = base->REGION3_ACC_CTL;
        /* Clear allow user and ns */
        allowCltVal = allowCltVal & (~IEE_APC_REGION3_ACC_CTL_ALLOW_NS_MASK);
        allowCltVal = allowCltVal & (~IEE_APC_REGION3_ACC_CTL_ALLOW_USER_MASK);
        /* Set new acces control value */
        base->REGION3_ACC_CTL = allowCltVal | IEE_APC_REGION3_ACC_CTL_ALLOW_NS(allowNonSecure) | 
                                IEE_APC_REGION3_ACC_CTL_ALLOW_USER(allowUser);
    }
    if (region == kIEE_APC_Region4)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        allowCltVal = base->REGION4_ACC_CTL;
        /* Clear allow user and ns */
        allowCltVal = allowCltVal & (~IEE_APC_REGION4_ACC_CTL_ALLOW_NS_MASK);
        allowCltVal = allowCltVal & (~IEE_APC_REGION4_ACC_CTL_ALLOW_USER_MASK);
        /* Set new acces control value */
        base->REGION4_ACC_CTL = allowCltVal | IEE_APC_REGION4_ACC_CTL_ALLOW_NS(allowNonSecure) | 
                                IEE_APC_REGION4_ACC_CTL_ALLOW_USER(allowUser);
    }
    if (region == kIEE_APC_Region5)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        allowCltVal = base->REGION5_ACC_CTL;
        /* Clear allow user and ns */
        allowCltVal = allowCltVal & (~IEE_APC_REGION5_ACC_CTL_ALLOW_NS_MASK);
        allowCltVal = allowCltVal & (~IEE_APC_REGION5_ACC_CTL_ALLOW_USER_MASK);
        /* Set new acces control value */
        base->REGION5_ACC_CTL = allowCltVal | IEE_APC_REGION5_ACC_CTL_ALLOW_NS(allowNonSecure) | 
                                IEE_APC_REGION5_ACC_CTL_ALLOW_USER(allowUser);
    }
    if (region == kIEE_APC_Region6)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        allowCltVal = base->REGION6_ACC_CTL;
        /* Clear allow user and ns */
        allowCltVal = allowCltVal & (~IEE_APC_REGION6_ACC_CTL_ALLOW_NS_MASK);
        allowCltVal = allowCltVal & (~IEE_APC_REGION6_ACC_CTL_ALLOW_USER_MASK);
        /* Set new acces control value */
        base->REGION6_ACC_CTL = allowCltVal | IEE_APC_REGION6_ACC_CTL_ALLOW_NS(allowNonSecure) | 
                                IEE_APC_REGION6_ACC_CTL_ALLOW_USER(allowUser);
    }
    if (region == kIEE_APC_Region7)
    {
        /* Set allowed domain ID to access the IEE APC registers of this region. */
        allowCltVal = base->REGION6_ACC_CTL;
        /* Clear allow user and ns */
        allowCltVal = allowCltVal & (~IEE_APC_REGION6_ACC_CTL_ALLOW_NS_MASK);
        allowCltVal = allowCltVal & (~IEE_APC_REGION6_ACC_CTL_ALLOW_USER_MASK);
        /* Set new acces control value */
        base->REGION6_ACC_CTL = allowCltVal | IEE_APC_REGION6_ACC_CTL_ALLOW_NS(allowNonSecure) | 
                                IEE_APC_REGION6_ACC_CTL_ALLOW_USER(allowUser);
    }
    return kStatus_Success;
}
#endif /* !(defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)) */

/*!
 * brief Enable the IEE encryption/decryption for specific region.
 *
 * This function enables encryption/decryption by writting to IOMUXC LPSR GPR.
 *
 * param base APC IEE peripheral address.
 * param region Selection of the APC IEE region to be enabled.
 */
void IEE_APC_RegionEnable(IEE_APC_Type *base, iee_apc_region_t region)
{

    if (region == kIEE_APC_Region0)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR18 |= IOMUXC_LPSR_GPR_GPR18_APC_R0_ENCRYPT_ENABLE_MASK;
#else
        base->REGION0_ENA |= IEE_APC_REGION0_ENA_ENCRYPT_ENABLE_MASK;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u) */
    }
    if (region == kIEE_APC_Region1)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR19 |= IOMUXC_LPSR_GPR_GPR19_APC_R1_ENCRYPT_ENABLE_MASK;
#else
        base->REGION1_ENA |= IEE_APC_REGION1_ENA_ENCRYPT_ENABLE_MASK;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u) */
    }
    if (region == kIEE_APC_Region2)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR20 |= IOMUXC_LPSR_GPR_GPR20_APC_R2_ENCRYPT_ENABLE_MASK;
#else
        base->REGION2_ENA |= IEE_APC_REGION2_ENA_ENCRYPT_ENABLE_MASK;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u) */
    }
    if (region == kIEE_APC_Region3)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)

        IOMUXC_LPSR_GPR->GPR21 |= IOMUXC_LPSR_GPR_GPR21_APC_R3_ENCRYPT_ENABLE_MASK;
#else
        base->REGION3_ENA |= IEE_APC_REGION3_ENA_ENCRYPT_ENABLE_MASK;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u) */
    }
    if (region == kIEE_APC_Region4)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR22 |= IOMUXC_LPSR_GPR_GPR22_APC_R4_ENCRYPT_ENABLE_MASK;
#else
        base->REGION4_ENA |= IEE_APC_REGION4_ENA_ENCRYPT_ENABLE_MASK;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u) */
    }
    if (region == kIEE_APC_Region5)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR23 |= IOMUXC_LPSR_GPR_GPR23_APC_R5_ENCRYPT_ENABLE_MASK;
#else
        base->REGION5_ENA |= IEE_APC_REGION5_ENA_ENCRYPT_ENABLE_MASK;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u) */
    }
    if (region == kIEE_APC_Region6)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR24 |= IOMUXC_LPSR_GPR_GPR24_APC_R6_ENCRYPT_ENABLE_MASK;
#else
        base->REGION6_ENA |= IEE_APC_REGION6_ENA_ENCRYPT_ENABLE_MASK;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u) */
    }
    if (region == kIEE_APC_Region7)
    {
#if defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)
        IOMUXC_LPSR_GPR->GPR25 |= IOMUXC_LPSR_GPR_GPR25_APC_R7_ENCRYPT_ENABLE_MASK;
#else
        base->REGION7_ENA |= IEE_APC_REGION7_ENA_ENCRYPT_ENABLE_MASK;
#endif /* defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u) */
    }

    return;
}

#if !(defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u))
/*!
 * brief Disable the IEE encryption/decryption for specific region.
 *
 * This function disables encryption/decryption by writting to IOMUXC LPSR GPR.
 *
 * param base APC IEE peripheral address.
 * param region Selection of the APC IEE region to be enabled.
 */
void IEE_APC_RegionDisable(IEE_APC_Type *base, iee_apc_region_t region)
{
    if (region == kIEE_APC_Region0)
    {
        base->REGION0_ENA = 0u;
    }
    if (region == kIEE_APC_Region1)
    {
        base->REGION1_ENA = 0u;
    }
    if (region == kIEE_APC_Region2)
    {
        base->REGION2_ENA = 0u;
    }
    if (region == kIEE_APC_Region3)
    {
        base->REGION3_ENA = 0u;
    }
    if (region == kIEE_APC_Region4)
    {
        base->REGION4_ENA = 0u;
    }
    if (region == kIEE_APC_Region5)
    {
        base->REGION5_ENA = 0u;
    }
    if (region == kIEE_APC_Region6)
    {
        base->REGION6_ENA = 0u;
    }
    if (region == kIEE_APC_Region7)
    {
        base->REGION7_ENA = 0u;
    }

    return;
}
#endif /* !(defined(FSL_FEATURE_IEE_APC_USE_GPR) && (FSL_FEATURE_IEE_APC_USE_GPR > 0u)) */