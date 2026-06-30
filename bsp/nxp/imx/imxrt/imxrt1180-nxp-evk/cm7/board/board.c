/*
 * Copyright 2021-2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "pin_mux.h"
#include "fsl_iomuxc.h"
#include "fsl_rgpio.h"
#include "fsl_cache.h"
#include "fsl_ele_base_api.h"
#include "fsl_dcdc.h"
#include "fsl_trdc.h"
#include "fsl_rgpio.h"

#define NVIC_PRIORITYGROUP_0         0x00000007U /*!< 0 bits for pre-emption priority
                                                      4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         0x00000006U /*!< 1 bits for pre-emption priority
                                                      3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         0x00000005U /*!< 2 bits for pre-emption priority
                                                      2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         0x00000004U /*!< 3 bits for pre-emption priority
                                                      1 bits for subpriority */
#define NVIC_PRIORITYGROUP_4         0x00000003U /*!< 4 bits for pre-emption priority
                                                      0 bits for subpriority */

/* MPU configuration. */
void BOARD_ConfigMPU(void)
{
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
    extern uint32_t Image$$RW_m_ncache$$Base[];
    /* RW_m_ncache_aux is a auxiliary region which is used to get the whole size of noncache section */
    extern uint32_t Image$$RW_m_ncache_aux$$Base[];
    uint32_t nonCacheStart = (uint32_t)Image$$RW_m_ncache$$Base;
    uint32_t nonCacheSize  = ((uint32_t)Image$$RW_m_ncache_aux$$Base) - nonCacheStart;
#elif defined(__MCUXPRESSO)
    extern uint32_t __base_NCACHE_REGION;
    extern uint32_t __top_NCACHE_REGION;
    uint32_t nonCacheStart = (uint32_t)(&__base_NCACHE_REGION);
    uint32_t nonCacheSize  = (uint32_t)(&__top_NCACHE_REGION) - nonCacheStart;
#elif defined(__ICCARM__) || defined(__GNUC__)
    extern uint32_t __NCACHE_REGION_START[];
    extern uint32_t __NCACHE_REGION_SIZE[];
    uint32_t nonCacheStart = (uint32_t)__NCACHE_REGION_START;
    uint32_t nonCacheSize  = (uint32_t)__NCACHE_REGION_SIZE;
#endif
#if defined(__USE_SHMEM)
#if defined(__CC_ARM) || defined(__ARMCC_VERSION)
    extern uint32_t Image$$RPMSG_SH_MEM$$Base[];
    /* RPMSG_SH_MEM_aux is a auxiliary region which is used to get the whole size of RPMSG_SH_MEM section */
    extern uint32_t Image$$RPMSG_SH_MEM_aux$$Base[];
    uint32_t rpmsgShmemStart = (uint32_t)Image$$RPMSG_SH_MEM$$Base;
    uint32_t rpmsgShmemSize  = ((uint32_t)Image$$RPMSG_SH_MEM_aux$$Base) - rpmsgShmemStart;
#elif defined(__MCUXPRESSO)
    extern uint32_t __base_SHMEM_REGION;
    extern uint32_t __top_SHMEM_REGION;
    uint32_t rpmsgShmemStart = (uint32_t)(&__base_SHMEM_REGION);
    uint32_t rpmsgShmemSize  = (uint32_t)(&__top_SHMEM_REGION) - rpmsgShmemStart;
#elif defined(__ICCARM__) || defined(__GNUC__)
    extern uint32_t __RPMSG_SH_MEM_START[];
    extern uint32_t __RPMSG_SH_MEM_SIZE[];
    uint32_t rpmsgShmemStart = (uint32_t)__RPMSG_SH_MEM_START;
    uint32_t rpmsgShmemSize  = (uint32_t)__RPMSG_SH_MEM_SIZE;
#endif
#endif
    volatile uint32_t i;

    /* Disable I cache and D cache */
    L1CACHE_DisableICache();
    L1CACHE_DisableDCache();

    /* Disable MPU */
    ARM_MPU_Disable();

    /* clang-format off */

    /* MPU configure:
     * Use ARM_MPU_RASR(DisableExec, AccessPermission, TypeExtField, IsShareable, IsCacheable, IsBufferable, SubRegionDisable, Size)
     * API in mpu_armv7.h.
     * param DisableExec       Instruction access (XN) disable bit,0=instruction fetches enabled, 1=instruction fetches disabled.
     * param AccessPermission  Data access permissions, allows you to configure read/write access for User and Privileged mode.
     *                         Use MACROS defined in mpu_armv7.h:
     *                         ARM_MPU_AP_NONE/ARM_MPU_AP_PRIV/ARM_MPU_AP_URO/ARM_MPU_AP_FULL/ARM_MPU_AP_PRO/ARM_MPU_AP_RO
     *
     * Combine TypeExtField/IsShareable/IsCacheable/IsBufferable to configure MPU memory access attributes.
     *  TypeExtField  IsShareable  IsCacheable  IsBufferable   Memory Attribute    Shareability        Cache
     *     0             x           0           0             Strongly Ordered    shareable
     *     0             x           0           1              Device             shareable
     *     0             0           1           0              Normal             not shareable   Outer and inner write
     *                                                                                             through no write allocate
     *     0             0           1           1              Normal             not shareable   Outer and inner write
     *                                                                                             back no write allocate
     *     0             1           1           0              Normal             shareable       Outer and inner write
     *                                                                                             through no write allocate
     *     0             1           1           1              Normal             shareable       Outer and inner write
     *                                                                                             back no write allocate
     *     1             0           0           0              Normal             not shareable   outer and inner
     *                                                                                             noncache
     *     1             1           0           0              Normal             shareable       outer and inner
     *                                                                                             noncache
     *     1             0           1           1              Normal             not shareable   outer and inner write
     *                                                                                             back write/read acllocate
     *     1             1           1           1              Normal             shareable       outer and inner write
     *                                                                                             back write/read acllocate
     *     2             x           0           0              Device             not shareable
     *   Above are normal use settings, if your want to see more details or want to config different inner/outer cache
     * policy, please refer to Table 4-55 /4-56 in arm cortex-M7 generic user guide <dui0646b_cortex_m7_dgug.pdf>
     *
     * param SubRegionDisable  Sub-region disable field. 0=sub-region is enabled, 1=sub-region is disabled.
     * param Size              Region size of the region to be configured. use ARM_MPU_REGION_SIZE_xxx MACRO in mpu_armv7.h.
     */

    /* clang-format on */

    /*
     * Add default region to deny access to whole address space to workaround speculative prefetch.
     * Refer to Arm errata 1013783-B for more details.
     */

    /* Region 0 setting: Instruction access disabled, No data access permission. */
    MPU->RBAR = ARM_MPU_RBAR(0, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(1, ARM_MPU_AP_NONE, 0, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_4GB);

    /* Region 1 setting: Memory with Device type, not shareable, non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(1, 0x80000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_512MB);

    /* Region 3 setting: Memory with Device type, not shareable, non-cacheable. */
    MPU->RBAR = ARM_MPU_RBAR(3, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 2, 0, 0, 0, 0, ARM_MPU_REGION_SIZE_2GB);

    /* Region 4 setting: Memory with Normal type, not shareable, outer/inner write back */ /*ITCM*/
    MPU->RBAR = ARM_MPU_RBAR(4, 0x00000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_256KB);

    /* Region 5 setting: Memory with Normal type, not shareable, outer/inner write back */ /*DTCM*/
    MPU->RBAR = ARM_MPU_RBAR(5, 0x20000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_256KB);

    MPU->RBAR = ARM_MPU_RBAR(6, 0x20480000U);
#if defined(CACHE_MODE_WRITE_THROUGH)
    /* Region 6 setting: Memory with Normal type, not shareable, outer/inner write through */ /*OCRAM1*/
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 0, 0, ARM_MPU_REGION_SIZE_512KB);
#else
    /* Region 6 setting: Memory with Normal type, not shareable, outer/inner write back */ /*OCRAM1*/
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_512KB);
#endif

    MPU->RBAR = ARM_MPU_RBAR(7, 0x20500000U);
#if defined(CACHE_MODE_WRITE_THROUGH)
    /* Region 7 setting: Memory with Normal type, not shareable, outer/inner write through */ /*OCRAM2*/
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 0, 0, ARM_MPU_REGION_SIZE_256KB);
#else
    /* Region 7 setting: Memory with Normal type, not shareable, outer/inner write back */ /*OCRAM2*/
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_256KB);
#endif

#if defined(XIP_EXTERNAL_FLASH) && (XIP_EXTERNAL_FLASH == 1)
    /* Region 8 setting: Memory with Normal type, not shareable, outer/inner write back. */ /*FSPI1*/
    MPU->RBAR = ARM_MPU_RBAR(8, 0x28000000U);
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_RO, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_16MB);
#endif

#if defined(USE_HYPERRAM)
    MPU->RBAR = ARM_MPU_RBAR(9, 0x04000000U);
#if defined(CACHE_MODE_WRITE_THROUGH)
    /* Region 9 setting: Memory with Normal type, not shareable, outer/inner write through. */ /*FSPI2*/
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 0, 0, ARM_MPU_REGION_SIZE_8MB);
#else
    /* Region 9 setting: Memory with Normal type, not shareable, outer/inner write back. */ /*FSPI2*/
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_8MB);
#endif
#endif

#if defined(USE_SDRAM)
    MPU->RBAR = ARM_MPU_RBAR(10, 0x80000000U);
#if defined(CACHE_MODE_WRITE_THROUGH)
    /* Region 10 setting: Memory with Normal type, not shareable, outer/inner write through */
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 0, 0, ARM_MPU_REGION_SIZE_64MB);
#else
    /* Region 10 setting: Memory with Normal type, not shareable, outer/inner write back */
    MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 0, 0, 1, 1, 0, ARM_MPU_REGION_SIZE_64MB);
#endif
#endif

    i = 0;
    while ((nonCacheSize >> i) > 0x1U)
    {
        i++;
    }

    if (i != 0)
    {
        /* The MPU region size should be 2^N, 5<=N<=32, region base should be multiples of size. */
        assert(!(nonCacheStart % nonCacheSize));
        assert(nonCacheSize == (uint32_t)(1 << i));
        assert(i >= 5);

        /* Region 11 setting: Memory with Normal type, not shareable, non-cacheable */
        MPU->RBAR = ARM_MPU_RBAR(11, nonCacheStart);
        MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 0, 0, 0, i - 1);
    }

#if defined(__USE_SHMEM)
    i = 0;
    while ((rpmsgShmemSize >> i) > 0x1U)
    {
        i++;
    }

    if (i != 0)
    {
        /* The MPU region size should be 2^N, 5<=N<=32, region base should be multiples of size. */
        assert(!(rpmsgShmemStart % rpmsgShmemSize));
        assert(rpmsgShmemSize == (uint32_t)(1 << i));
        assert(i >= 5);

        /* Region 12 setting: Memory with Normal type, not shareable, non-cacheable */
        MPU->RBAR = ARM_MPU_RBAR(12, rpmsgShmemStart);
        MPU->RASR = ARM_MPU_RASR(0, ARM_MPU_AP_FULL, 1, 0, 0, 0, 0, i - 1);
    }
#endif

    /* Enable MPU */
    ARM_MPU_Enable(MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_HFNMIENA_Msk);

    /* Enable I cache and D cache */
    L1CACHE_EnableDCache();
    L1CACHE_EnableICache();
}

void BOARD_RequestTRDC(bool bRequestAON, bool bRequestWakeup, bool bReqeustMega)
{
#define ELE_TRDC_AON_ID    0x74
#define ELE_TRDC_WAKEUP_ID 0x78
#define ELE_TRDC_MEGA_ID   0x82
#define ELE_CORE_CM33_ID   0x1
#define ELE_CORE_CM7_ID    0x2

#if (__CORTEX_M == 33)
    uint8_t ele_core_id = ELE_CORE_CM33_ID;
#elif (__CORTEX_M == 7)
    uint8_t ele_core_id = ELE_CORE_CM7_ID;
#endif

    uint32_t ele_fw_sts;

    /* Get ELE FW status */
    ELE_BaseAPI_GetFwStatus(MU_RT_S3MUA, &ele_fw_sts);

    if (bRequestAON)
    {
        /* Release TRDC AON to current core */
        ELE_BaseAPI_ReleaseRDC(MU_RT_S3MUA, ELE_TRDC_AON_ID, ele_core_id);
    }

    /*
     * TRDC MEGA request must be prior to TRDC WAKEUP, as TRDC MEGA access
     * is controlled by the TRDC WAKEUP.
     * note:
     *   If TRDC WAKEUP has been release to one core firstly, then it will fail
     *   to release TRDC MEGA to same/another core.
     */
    if (bReqeustMega)
    {
        /* Release TRDC MEGA to current core */
        ELE_BaseAPI_ReleaseRDC(MU_RT_S3MUA, ELE_TRDC_MEGA_ID, ele_core_id);
    }

    if (bRequestWakeup)
    {
        /* Release TRDC WAKEUP to current core */
        ELE_BaseAPI_ReleaseRDC(MU_RT_S3MUA, ELE_TRDC_WAKEUP_ID, ele_core_id);
    }
}

void APP_CommonTrdcDACSetting(void)
{
    trdc_processor_domain_assignment_t procAssign = {.domainId           = 0U,
                                                     .domainIdSelect     = kTRDC_DidInput,
                                                     .pidDomainHitConfig = kTRDC_pidDomainHitNone0,
                                                     .pidMask            = 0U,
                                                     .secureAttr         = kTRDC_ForceSecure,
                                                     .pid                = 0U,
                                                     .lock               = false
                                                    };

    trdc_non_processor_domain_assignment_t nonProcAssign = {.domainId       = 0U,
                                                            .privilegeAttr  = kTRDC_ForcePrivilege,
                                                            .secureAttr     = kTRDC_ForceSecure,
                                                            .bypassDomainId = true,
                                                            .lock           = false
                                                           };

    /* 1. Set the MDAC Configuration in TRDC1. */
    /* Configure the access control for CM33(master 1 for TRDC1, MDAC_A1). */
    procAssign.domainId = 0x2U;
    TRDC_SetProcessorDomainAssignment(TRDC1, (uint8_t)kTRDC1_MasterCM33, 0U, &procAssign);
    /* Configure the access control for eDMA3(master 2 for TRDC1, MDAC_A2). */
    nonProcAssign.domainId = 0x7U;
    TRDC_SetNonProcessorDomainAssignment(TRDC1, (uint8_t)kTRDC1_MasterDMA3, &nonProcAssign);

    /* 2. Set the MDAC Configuration in TRDC2. */
    /* Configure the access control for CM7 AHBP(master 0 for TRDC2, MDAC_W0). */
    procAssign.domainId = 0x4U;
    TRDC_SetProcessorDomainAssignment(TRDC2, (uint8_t)kTRDC2_MasterCM7AHBP, 0U, &procAssign);
    /* Configure the access control for CM7 AXI(master 1 for TRDC2, MDAC_W1). */
    TRDC_SetProcessorDomainAssignment(TRDC2, (uint8_t)kTRDC2_MasterCM7AXI, 0U, &procAssign);
    /* Configure the access control for DAP AHB_AP_SYS(master 2 for TRDC2, MDAC_W2). */
    nonProcAssign.domainId = 0x9U;
    TRDC_SetNonProcessorDomainAssignment(TRDC2, (uint8_t)kTRDC2_MasterDAP, &nonProcAssign);
    /* Configure the access control for CoreSight(master 3 for TRDC2, MDAC_W3). */
    nonProcAssign.domainId = 0x8U;
    TRDC_SetNonProcessorDomainAssignment(TRDC2, (uint8_t)kTRDC2_MasterCoreSight, &nonProcAssign);
    /* Configure the access control for DMA4(master 4 for TRDC2, MDAC_W4). */
    nonProcAssign.domainId = 0x7U;
    TRDC_SetNonProcessorDomainAssignment(TRDC2, (uint8_t)kTRDC2_MasterDMA4, &nonProcAssign);
    /* Configure the access control for NETC(master 5 for TRDC2, MDAC_W5). */
    procAssign.domainId = 0xAU;
    TRDC_SetProcessorDomainAssignment(TRDC2, (uint8_t)kTRDC2_MasterNETC, 0U, &procAssign);

    /* 3. Set the MDAC Configuration in TRDC3. */
    /* Configure the access control for uSDHC1(master 0 for TRDC3, MDAC_M0). */
    nonProcAssign.domainId = 0x5U;
    TRDC_SetNonProcessorDomainAssignment(TRDC3, (uint8_t)kTRDC3_MasterUSDHC1, &nonProcAssign);
    /* Configure the access control for uSDHC2(master 1 for TRDC3, MDAC_M1). */
    nonProcAssign.domainId = 0x6U;
    TRDC_SetNonProcessorDomainAssignment(TRDC3, (uint8_t)kTRDC3_MasterUSDHC2, &nonProcAssign);
    /* Configure the access control for USB(master 3 for TRDC3, MDAC_M3). */
    nonProcAssign.domainId = 0xBU;
    TRDC_SetNonProcessorDomainAssignment(TRDC3, (uint8_t)kTRDC3_MasterUsb, &nonProcAssign);
    /* Configure the access control for FlexSPI_FLR(master 4 for TRDC3, MDAC_M4). */
    nonProcAssign.domainId = 0xAU;
    TRDC_SetNonProcessorDomainAssignment(TRDC3, (uint8_t)kTRDC3_MasterFlexspiFlr, &nonProcAssign);
}

static bool TRDC_IsValidDomain(TRDC_Type *trdc, uint8_t domain)
{
    bool r = true;

    if ((domain > 11) || (domain < 2) || (domain == 3))
    {
        r = false;
    }
    return r;
}

static bool TRDC_IsValidMbc(TRDC_Type *trdc, uint8_t mbc)
{
    bool r = false;
    if (trdc == TRDC1)
    {
        switch (mbc)
        {
        case 0: /* TRDC1 MBC_A0   */
        case 1: /* TRDC1 MBC_A1   */
            r = true;
            break;
        default:
            break;
        }
    }
    else if (trdc == TRDC2)
    {
        switch (mbc)
        {
        case 0: /* TRDC2 MBC_W0   */
        case 1: /* TRDC2 MBC_W1   */
            r = true;
            break;
        default:
            break;
        }
    }
    return r;
}

static uint32_t TRDC_GetMbcMemNum(TRDC_Type *trdc, uint32_t mbc)
{
    uint32_t memNumber = 0U;
    if (trdc == TRDC1)
    {
        uint8_t MemNum[2] = {3, 2};
        switch (mbc)
        {
        case 0: /* TRDC1 MBC_A0 AIPS1/Edgelock/GPIO1      */
        case 1: /* TRDC1 MBC_A1 CM33 Code-TCM/CM33 System-TCM     */
            memNumber = MemNum[mbc];
            break;
        default:
            break;
        }
    }
    else if (trdc == TRDC2)
    {
        uint8_t MemNum[2] = {4, 4};
        switch (mbc)
        {
        case 0: /* TRDC2 MBC_A0 AIPS2/GPIO2, GPIO4, GPIO6/GPIO3, GPIO5/DAP (Debug) */
        case 1: /* TRDC2 MBC_A1 AIPS3/AHB_ISPAP/NIC_MAIN GPV/SRAMC                 */
            memNumber = MemNum[mbc];
            break;
        default:
            break;
        }
    }
    return memNumber;
}

static bool TRDC_IsValidMbcMem(TRDC_Type *trdc, uint8_t mbc, uint8_t mem)
{
    bool r = false;
    if (trdc == TRDC1)
    {
        switch (mbc)
        {
        case 0: /* TRDC1 MBC_A0                      */
            switch (mem)
            {
            case 0: /* TRDC1 MBC_A0 AIPS1                */
                r = true;
                break;
            case 1: /* TRDC1 MBC_A0 Edgelock             */
                break; /* Intentional, Edgelock region not touched. */
            case 2: /* TRDC1 MBC_A0 GPIO1                */
                r = true;
                break;
            default:
                break;
            }
            break;
        case 1: /* TRDC1 MBC_A1                        */
            switch (mem)
            {
            case 0: /* TRDC1 MBC_A1 CM33 Code-TCM          */
            case 1: /* TRDC1 MBC_A1 CM33 System-TCM        */
                r = true;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
    else if (trdc == TRDC2)
    {
        switch (mbc)
        {
        case 0: /* TRDC2 MBC_W0                        */
            switch (mem)
            {
            case 0: /* TRDC2 MBC_W0 AIPS2                  */
            case 1: /* TRDC2 MBC_W0 GPIO2, GPIO4, GPIO6    */
            case 2: /* TRDC2 MBC_W0 GPIO3, GPIO5           */
            case 3: /* TRDC2 MBC_W0 DAP (Debug)            */
                r = true;
                break;

            default:
                break;
            }
            break;
        case 1: /* TRDC2 MBC_W1                         */
            switch (mem)
            {
            case 0: /* TRDC2 MBC_W1 AIPS3                  */
            case 1: /* TRDC2 MBC_W1 AHB_ISPAP              */
            case 2: /* TRDC2 MBC_W1 NIC_MAIN GPV           */
            case 3: /* TRDC2 MBC_W1 SRAMC                  */
                r = true;
                break;

            default:
                break;
            }
            break;
        default:
            break;
        }
    }
    return r;
}

static bool TRDC_IsValidMrc(TRDC_Type *trdc, uint8_t mrc)
{
    bool r = false;
    if (trdc == TRDC1)
    {
        switch (mrc)
        {
        case 0: /* TRDC1 MRC_A0   */
        case 1: /* TRDC1 MRC_A1   */
            r = true;
            break;
        default:
            break;
        }
    }
    else if (trdc == TRDC2)
    {
        switch (mrc)
        {
        case 1: /* TRDC2 MRC_W1   */
        case 2: /* TRDC2 MRC_W2   */
        case 3: /* TRDC2 MRC_W3   */
        case 4: /* TRDC2 MRC_W4   */
        case 5: /* TRDC2 MRC_W5   */
        case 6: /* TRDC2 MRC_W6   */
            r = true;
            break;
        default:
            break;
        }
    }
    return r;
}

static bool TRDC_GetMrcRegionAddr(TRDC_Type *trdc, uint8_t mrc, uint32_t *pStartAddr, uint32_t *pStopAddr)
{
    bool r = true;
    if (trdc == TRDC1)
    {
        switch (mrc)
        {
        case 0: /* TRDC1 MRC_A0 CM33 ROM  */
            *pStartAddr = 0x00000000UL;
            *pStopAddr  = 0x00027FFFUL;
            break;
        case 1: /* TRDC1 MRC_A1 FlexSPI2  */
            *pStartAddr = 0x04000000UL;
            *pStopAddr  = 0x07FFFFFFUL;
            break;
        default:
            r = false;
            break;
        }
    }
    else if (trdc == TRDC2)
    {
        switch (mrc)
        {
        case 1: /* TRDC2 MRC_W1 FlexSPI1         */
            *pStartAddr = 0x28000000UL;
            *pStopAddr  = 0x2FFFFFFFUL;
            break;
        case 2: /* TRDC2 MRC_W2 CM7 I-TCM D-TCM  */
            *pStartAddr = 0x203C0000UL;
            *pStopAddr  = 0x2043FFFFUL;
            break;
        case 3: /* TRDC2 MRC_W3 OCRAM1           */
            *pStartAddr = 0x20480000UL;
            *pStopAddr  = 0x204FFFFFUL;
            break;
        case 4: /* TRDC2 MRC_W4 OCRAM2           */
            *pStartAddr = 0x20500000UL;
            *pStopAddr  = 0x2053FFFFUL;
            break;
        case 5: /* TRDC2 MRC_W5 SEMC             */
            *pStartAddr = 0x80000000UL;
            *pStopAddr  = 0x8FFFFFFFUL;
            break;
        case 6: /* TRDC2 MRC_W6 NETC             */
            *pStartAddr = 0x60000000UL;
            *pStopAddr  = 0x60FFFFFFUL;
            break;
        default:
            r = false;
            break;
        }
    }
    return r;
}

void APP_CommonTrdcAccessControlSetting(TRDC_Type *trdc)
{
    trdc_hardware_config_t hwConfig;
    trdc_memory_access_control_config_t memAccessConfig;
    trdc_mbc_memory_block_config_t mbcBlockConfig;
    trdc_mrc_region_descriptor_config_t mrcRegionConfig;

    TRDC_GetHardwareConfig(trdc, &hwConfig);

    /* Enable all read/write/execute access for MRC/MBC access control. */
    (void)memset(&memAccessConfig, 0, sizeof(memAccessConfig));
    memAccessConfig.nonsecureUsrX  = 1U;
    memAccessConfig.nonsecureUsrW  = 1U;
    memAccessConfig.nonsecureUsrR  = 1U;
    memAccessConfig.nonsecurePrivX = 1U;
    memAccessConfig.nonsecurePrivW = 1U;
    memAccessConfig.nonsecurePrivR = 1U;
    memAccessConfig.secureUsrX     = 1U;
    memAccessConfig.secureUsrW     = 1U;
    memAccessConfig.secureUsrR     = 1U;
    memAccessConfig.securePrivX    = 1U;
    memAccessConfig.securePrivW    = 1U;
    memAccessConfig.securePrivR    = 1U;

    for (uint32_t mrc = 0U; mrc < hwConfig.mrcNumber; mrc++)
    {
        if (TRDC_IsValidMrc(trdc, mrc))
        {
            for (uint32_t i = 0U; i < 8U; i++)
            {
                TRDC_MrcSetMemoryAccessConfig(trdc, &memAccessConfig, mrc, i);
            }
        }
    }

    for (uint32_t mbc = 0U; mbc < hwConfig.mbcNumber; mbc++)
    {
        if (TRDC_IsValidMbc(trdc, mbc))
        {
            for (uint32_t i = 0U; i < 8U; i++)
            {
                TRDC_MbcSetMemoryAccessConfig(trdc, &memAccessConfig, mbc, i);
            }
        }
    }

    memset(&mbcBlockConfig, 0, sizeof(mbcBlockConfig));
    mbcBlockConfig.nseEnable                 = false;
    mbcBlockConfig.memoryAccessControlSelect = 0;

    memset(&mrcRegionConfig, 0, sizeof(mrcRegionConfig));
    mrcRegionConfig.memoryAccessControlSelect = 0U;
    mrcRegionConfig.valid                     = true;
    mrcRegionConfig.nseEnable                 = false;
    mrcRegionConfig.regionIdx                 = 0U;

    for (uint32_t domain = 0; domain < hwConfig.domainNumber; domain++)
    {
        if (TRDC_IsValidDomain(trdc, domain))
        {
            /* Set the configuration for MBC. */
            for (uint32_t mbc = 0U; mbc < hwConfig.mbcNumber; mbc++)
            {
                if (TRDC_IsValidMbc(trdc, mbc))
                {
                    uint32_t mem_num = TRDC_GetMbcMemNum(trdc, mbc);
                    for (uint32_t mem = 0; mem < mem_num; mem++)
                    {
                        if (TRDC_IsValidMbcMem(trdc, mbc, mem))
                        {
                            trdc_slave_memory_hardware_config_t mbcHwConfig;
                            TRDC_GetMbcHardwareConfig(trdc, &mbcHwConfig, mbc, mem);
                            for (uint32_t block = 0; block < mbcHwConfig.blockNum; block++)
                            {
                                mbcBlockConfig.domainIdx      = domain;
                                mbcBlockConfig.mbcIdx         = mbc;
                                mbcBlockConfig.slaveMemoryIdx = mem;
                                mbcBlockConfig.memoryBlockIdx = block;
                                TRDC_MbcSetMemoryBlockConfig(trdc, &mbcBlockConfig);
                            }
                        }
                    }
                }
            }

            /* Set the configuration for MRC. */
            for (uint32_t mrc = 0U; mrc < hwConfig.mrcNumber; mrc++)
            {
                if (TRDC_IsValidMrc(trdc, mrc))
                {
                    uint32_t start_addr, end_addr;

                    if (TRDC_GetMrcRegionAddr(trdc, mrc, &start_addr, &end_addr))
                    {
                        mrcRegionConfig.startAddr = start_addr;
                        mrcRegionConfig.endAddr   = end_addr;
                        mrcRegionConfig.domainIdx = domain;
                        mrcRegionConfig.mrcIdx    = mrc;
                        TRDC_MrcSetRegionDescriptorConfig(trdc, &mrcRegionConfig);
                    }
                    else
                    {
                        assert(false);
                    }
                }
            }
        }
    }
}

void BOARD_GrantTRDCFullPermissions(void)
{
    /* 1. Request TRDC ownership */
    BOARD_RequestTRDC(true, true, true);

    /* 2. Config DAC. */
    APP_CommonTrdcDACSetting();

    /* 3. Enable all access control */
    APP_CommonTrdcAccessControlSetting(TRDC1);
    APP_CommonTrdcAccessControlSetting(TRDC2);
}

void BOARD_CommonSetting(void)
{
    BOARD_GrantTRDCFullPermissions();
}

/* This is the timer interrupt service routine. */
void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

void imxrt_uart_pins_init(void)
{
#ifdef BSP_USING_LPUART1
    CLOCK_EnableClock(kCLOCK_Iomuxc2);           /* Turn on LPCG: LPCG is ON. */

    IOMUXC_SetPinMux(
        IOMUXC_GPIO_AON_08_LPUART1_TX,           /* GPIO_AON_08 is configured as LPUART1_TX */
        0U);                                      /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinMux(
        IOMUXC_GPIO_AON_09_LPUART1_RX,           /* GPIO_AON_09 is configured as LPUART1_RX */
        0U);                                      /* Software Input On Field: Input Path is determined by functionality */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_AON_08_LPUART1_TX,           /* GPIO_AON_08 PAD functional properties : */
        0x02U);                                   /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: high driver
                                                     Pull / Keep Select Field: Pull Disable, Highz
                                                     Pull Up / Down Config. Field: Weak pull down
                                                     Open Drain Field: Disabled */
    IOMUXC_SetPinConfig(
        IOMUXC_GPIO_AON_09_LPUART1_RX,           /* GPIO_AON_09 PAD functional properties : */
        0x02U);                                   /* Slew Rate Field: Fast Slew Rate
                                                     Drive Strength Field: high driver
                                                     Pull / Keep Select Field: Pull Disable, Highz
                                                     Pull Up / Down Config. Field: Weak pull down
                                                     Open Drain Field: Disabled */
#endif
}

void rt_hw_board_init()
{
    BOARD_CommonSetting();
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();

    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
    SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);

#ifdef BSP_USING_LPUART
    imxrt_uart_pins_init();
#endif

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}

