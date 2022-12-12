/*
 * Copyright 2020-2021, NXP
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
    /* APC_x bits in GPR2 to GPR25 only take effect when this bit is set high */
    IOMUXC_LPSR_GPR->GPR25 |= IOMUXC_LPSR_GPR_GPR25_APC_VALID_MASK;
    __DSB();
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
    /* APC_x bits in GPR2 to GPR25 only take effect when this bit is set high */
    IOMUXC_LPSR_GPR->GPR25 &= ~IOMUXC_LPSR_GPR_GPR25_APC_VALID_MASK;
    __DSB();
    return;
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

    if (region == kIEE_APC_Region0)
    {
        IOMUXC_LPSR_GPR->GPR2 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR3 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IEE_APC->REGION0_BOT_ADDR = startAddr >> 3;
        IEE_APC->REGION0_TOP_ADDR = endAddr >> 3;
    }
    if (region == kIEE_APC_Region1)
    {
        IOMUXC_LPSR_GPR->GPR4 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR5 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IEE_APC->REGION1_BOT_ADDR = startAddr >> 3;
        IEE_APC->REGION1_TOP_ADDR = endAddr >> 3;
    }
    if (region == kIEE_APC_Region2)
    {
        IOMUXC_LPSR_GPR->GPR6 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR7 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IEE_APC->REGION2_BOT_ADDR = startAddr >> 3;
        IEE_APC->REGION2_TOP_ADDR = endAddr >> 3;
    }
    if (region == kIEE_APC_Region3)
    {
        IOMUXC_LPSR_GPR->GPR8 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR9 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IEE_APC->REGION3_BOT_ADDR = startAddr >> 3;
        IEE_APC->REGION3_TOP_ADDR = endAddr >> 3;
    }
    if (region == kIEE_APC_Region4)
    {
        IOMUXC_LPSR_GPR->GPR10 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR11 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IEE_APC->REGION4_BOT_ADDR = startAddr >> 3;
        IEE_APC->REGION4_TOP_ADDR = endAddr >> 3;
    }
    if (region == kIEE_APC_Region5)
    {
        IOMUXC_LPSR_GPR->GPR12 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR13 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IEE_APC->REGION5_BOT_ADDR = startAddr >> 3;
        IEE_APC->REGION5_TOP_ADDR = endAddr >> 3;
    }
    if (region == kIEE_APC_Region6)
    {
        IOMUXC_LPSR_GPR->GPR14 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR15 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IEE_APC->REGION6_BOT_ADDR = startAddr >> 3;
        IEE_APC->REGION6_TOP_ADDR = endAddr >> 3;
    }
    if (region == kIEE_APC_Region7)
    {
        IOMUXC_LPSR_GPR->GPR16 |= startAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IOMUXC_LPSR_GPR->GPR17 |= endAddr & IOMUXC_LPSR_GPR_APC_ADDR_MASK;
        IEE_APC->REGION7_BOT_ADDR = startAddr >> 3;
        IEE_APC->REGION7_TOP_ADDR = endAddr >> 3;
    }

    return kStatus_Success;
}

/*!
 * brief Lock the LPSR GPR and APC IEE configuration.
 *
 * This function locks writting to IOMUXC LPSR GPR and APC IEE encryption region setting registers.
 * Only system reset can clear the LPSR GPR and APC IEE-RDC_D0/1 Lock bit
 *
 * param base APC IEE peripheral address.
 * param region Selection of the APC IEE region to be locked.
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
            IEE_APC->REGION0_RDC_D0 |= IEE_APC_REGION0_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            IEE_APC->REGION0_RDC_D0 |= IEE_APC_REGION0_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            IEE_APC->REGION0_RDC_D1 |= IEE_APC_REGION0_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            IEE_APC->REGION0_RDC_D1 |= IEE_APC_REGION0_RDC_D1_RDC_D1_LOCK_MASK;
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
            IEE_APC->REGION1_RDC_D0 |= IEE_APC_REGION1_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            IEE_APC->REGION1_RDC_D0 |= IEE_APC_REGION1_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            IEE_APC->REGION1_RDC_D1 |= IEE_APC_REGION1_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            IEE_APC->REGION1_RDC_D1 |= IEE_APC_REGION1_RDC_D1_RDC_D1_LOCK_MASK;
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
            IEE_APC->REGION2_RDC_D0 |= IEE_APC_REGION2_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            IEE_APC->REGION2_RDC_D0 |= IEE_APC_REGION2_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            IEE_APC->REGION2_RDC_D1 |= IEE_APC_REGION2_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            IEE_APC->REGION2_RDC_D1 |= IEE_APC_REGION2_RDC_D1_RDC_D1_LOCK_MASK;
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
            IEE_APC->REGION3_RDC_D0 |= IEE_APC_REGION3_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            IEE_APC->REGION3_RDC_D0 |= IEE_APC_REGION3_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            IEE_APC->REGION3_RDC_D1 |= IEE_APC_REGION3_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            IEE_APC->REGION3_RDC_D1 |= IEE_APC_REGION3_RDC_D1_RDC_D1_LOCK_MASK;
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
            IEE_APC->REGION4_RDC_D0 |= IEE_APC_REGION4_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            IEE_APC->REGION4_RDC_D0 |= IEE_APC_REGION4_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            IEE_APC->REGION4_RDC_D1 |= IEE_APC_REGION4_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            IEE_APC->REGION4_RDC_D1 |= IEE_APC_REGION4_RDC_D1_RDC_D1_LOCK_MASK;
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
            IEE_APC->REGION5_RDC_D0 |= IEE_APC_REGION5_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            IEE_APC->REGION5_RDC_D0 |= IEE_APC_REGION5_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            IEE_APC->REGION5_RDC_D1 |= IEE_APC_REGION5_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            IEE_APC->REGION5_RDC_D1 |= IEE_APC_REGION5_RDC_D1_RDC_D1_LOCK_MASK;
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
            IEE_APC->REGION6_RDC_D0 |= IEE_APC_REGION6_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            IEE_APC->REGION6_RDC_D0 |= IEE_APC_REGION6_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            IEE_APC->REGION6_RDC_D1 |= IEE_APC_REGION6_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            IEE_APC->REGION6_RDC_D1 |= IEE_APC_REGION6_RDC_D1_RDC_D1_LOCK_MASK;
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
            IEE_APC->REGION7_RDC_D0 |= IEE_APC_REGION7_RDC_D0_RDC_D0_WRITE_DIS_MASK;
            IEE_APC->REGION7_RDC_D0 |= IEE_APC_REGION7_RDC_D0_RDC_D0_LOCK_MASK;
        }
        else if (domain == kIEE_APC_Domain1)
        {
            IEE_APC->REGION7_RDC_D1 |= IEE_APC_REGION7_RDC_D1_RDC_D1_WRITE_DIS_MASK;
            IEE_APC->REGION7_RDC_D1 |= IEE_APC_REGION7_RDC_D1_RDC_D1_LOCK_MASK;
        }
        else
        {
            /* Intentional empty */
        }
    }

    return kStatus_Success;
}

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
        IOMUXC_LPSR_GPR->GPR18 |= IOMUXC_LPSR_GPR_GPR18_APC_R0_ENCRYPT_ENABLE_MASK;
    }
    if (region == kIEE_APC_Region1)
    {
        IOMUXC_LPSR_GPR->GPR19 |= IOMUXC_LPSR_GPR_GPR19_APC_R1_ENCRYPT_ENABLE_MASK;
    }
    if (region == kIEE_APC_Region2)
    {
        IOMUXC_LPSR_GPR->GPR20 |= IOMUXC_LPSR_GPR_GPR20_APC_R2_ENCRYPT_ENABLE_MASK;
    }
    if (region == kIEE_APC_Region3)
    {
        IOMUXC_LPSR_GPR->GPR21 |= IOMUXC_LPSR_GPR_GPR21_APC_R3_ENCRYPT_ENABLE_MASK;
    }
    if (region == kIEE_APC_Region4)
    {
        IOMUXC_LPSR_GPR->GPR22 |= IOMUXC_LPSR_GPR_GPR22_APC_R4_ENCRYPT_ENABLE_MASK;
    }
    if (region == kIEE_APC_Region5)
    {
        IOMUXC_LPSR_GPR->GPR23 |= IOMUXC_LPSR_GPR_GPR23_APC_R5_ENCRYPT_ENABLE_MASK;
    }
    if (region == kIEE_APC_Region6)
    {
        IOMUXC_LPSR_GPR->GPR24 |= IOMUXC_LPSR_GPR_GPR24_APC_R6_ENCRYPT_ENABLE_MASK;
    }
    if (region == kIEE_APC_Region7)
    {
        IOMUXC_LPSR_GPR->GPR25 |= IOMUXC_LPSR_GPR_GPR25_APC_R7_ENCRYPT_ENABLE_MASK;
    }

    return;
}
