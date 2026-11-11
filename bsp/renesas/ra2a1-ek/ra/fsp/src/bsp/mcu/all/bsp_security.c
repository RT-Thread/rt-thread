/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

#if BSP_FEATURE_TZ_HAS_TRUSTZONE

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #define BSP_PRV_TZ_REG_KEY                       (0xA500U)
 #define BSP_PRV_AIRCR_VECTKEY                    (0x05FA0000U)
 #define RA_NOT_DEFINED                           (0)

/* Branch T3 Instruction (IMM11=-2) */
 #define BSP_PRV_INFINITE_LOOP                    (0xE7FE)

 #define BSP_SAU_REGION_CODE_FLASH_NSC            (0U)
 #define BSP_SAU_REGION_1_NS                      (1U)
 #define BSP_SAU_REGION_SRAM_NSC                  (2U)
 #define BSP_SAU_REGION_2_NS                      (3U)
 #define BSP_SAU_REGION_3_NS                      (4U)

/* Non-secure regions defined by the IDAU. These regions must be defined as non-secure in the SAU. */
 #define BSP_PRV_SAU_NS_REGION_1_BASE_ADDRESS     (0x10000000U)
 #define BSP_PRV_SAU_NS_REGION_1_LIMIT_ADDRESS    (0x1FFFFFFFU)
 #define BSP_PRV_SAU_NS_REGION_2_BASE_ADDRESS     (0x30000000U)
 #define BSP_PRV_SAU_NS_REGION_2_LIMIT_ADDRESS    (0x3FFFFFFFU)
 #define BSP_PRV_SAU_NS_REGION_3_BASE_ADDRESS     (0x50000000U)
 #define BSP_PRV_SAU_NS_REGION_3_LIMIT_ADDRESS    (0xDFFFFFFFU)

/* Protect DMAST/DTCST from nonsecure write access. */
 #if (1U == BSP_CFG_CPU_CORE)
  #define DMACX_REGISTER_SHIFT                    (16)
  #define DTCX_REGISTER_SHIFT                     (16)
 #else
  #define DMACX_REGISTER_SHIFT                    (0)
  #define DTCX_REGISTER_SHIFT                     (0)
 #endif

/* Macros to align to next memory region for TZ (mainly to "find" NS locations) */
 #if defined(BSP_PARTITION_FLASH_CPU0_S_START) && (0U == BSP_CFG_CPU_CORE)

/* Use partition macros for primary core */
  #define FLASH_NSC_START        ((uint32_t *) BSP_PARTITION_FLASH_CPU0_C_START)
  #define FLASH_NSC_LIMIT        ((uint32_t) BSP_PARTITION_FLASH_CPU0_C_START + BSP_PARTITION_FLASH_CPU0_C_SIZE - 1)
  #define FLASH_NS_START         ((uint32_t *) BSP_PARTITION_FLASH_CPU0_N_START)
  #define RAM_NSC_START          ((uint32_t *) BSP_PARTITION_RAM_CPU0_C_START)
  #define RAM_NSC_LIMIT          ((uint32_t) BSP_PARTITION_RAM_CPU0_C_START + BSP_PARTITION_RAM_CPU0_C_SIZE - 1)
  #define RAM_NS_START           ((uint32_t *) BSP_PARTITION_RAM_CPU0_N_START)
  #define DATA_FLASH_NS_START    ((uint32_t *) BSP_PARTITION_DATA_FLASH_CPU0_N_START)

 #elif defined(BSP_PARTITION_FLASH_CPU1_S_START) && (1U == BSP_CFG_CPU_CORE)

/* Use partition macros for secondary core */
  #define FLASH_NSC_START        ((uint32_t *) BSP_PARTITION_FLASH_CPU1_C_START)
  #define FLASH_NSC_LIMIT        ((uint32_t) BSP_PARTITION_FLASH_CPU1_C_START + BSP_PARTITION_FLASH_CPU1_C_SIZE - 1)
  #define FLASH_NS_START         ((uint32_t *) BSP_PARTITION_FLASH_CPU1_N_START)
  #define RAM_NSC_START          ((uint32_t *) BSP_PARTITION_RAM_CPU1_C_START)
  #define RAM_NSC_LIMIT          ((uint32_t) BSP_PARTITION_RAM_CPU1_C_START + BSP_PARTITION_RAM_CPU1_C_SIZE - 1)
  #define RAM_NS_START           ((uint32_t *) BSP_PARTITION_RAM_CPU1_N_START)
  #define DATA_FLASH_NS_START    ((uint32_t *) BSP_PARTITION_DATA_FLASH_CPU1_N_START)

 #else

/* Use legacy tail-chaining to find NS */
  #define FLASH_NS_START         ((uint32_t *) ((((uint32_t) gp_ddsc_FLASH_END + 0x8000 - 1) & \
                                                 0xFFFF8000) | BSP_FEATURE_TZ_NS_OFFSET))
  #define FLASH_NSC_START        ((uint32_t *) gp_ddsc_FLASH_NSC)
  #define FLASH_NSC_LIMIT        (((uint32_t) FLASH_NS_START & ~BSP_FEATURE_TZ_NS_OFFSET) - 1U)
  #define RAM_NS_START           ((uint32_t *) ((((uint32_t) gp_ddsc_RAM_END + 0x2000 - 1) & \
                                                 0xFFFFE000) | BSP_FEATURE_TZ_NS_OFFSET))
  #define RAM_NSC_START          ((uint32_t *) gp_ddsc_RAM_NSC)
  #define RAM_NSC_LIMIT          (((uint32_t) RAM_NS_START & ~BSP_FEATURE_TZ_NS_OFFSET) - 1U)
  #define DATA_FLASH_NS_START    ((uint32_t *) ((((uint32_t) gp_ddsc_DATA_FLASH_END + 0x400 - 1) & \
                                                 0xFFFFFC00) | BSP_FEATURE_TZ_NS_OFFSET))

 #endif

 #define RAM_NS_START_S_ALIAS    ((uint32_t *) ((uint32_t) RAM_NS_START & ~BSP_FEATURE_TZ_NS_OFFSET))

/* Operation after detection registers.
 * RA8 devices have the registers under MSA/BUS while other devices have them under TZF. */
 #ifdef R_TZF
  #define BSP_PRV_OAD_REG        R_TZF->TZFOAD
  #define BSP_PRV_OAD_PT_REG     R_TZF->TZFPT
 #else
  #define BSP_PRV_OAD_REG        R_BUS->OAD.MSAOAD
  #define BSP_PRV_OAD_PT_REG     R_BUS->OAD.MSAPT
 #endif

 #if BSP_SECONDARY_CORE_BUILD

/* For a secure secondary core the SAR has already been written so it
 * only needs to modify the security attributes it is using:
 * - Secure (0) will always stay Secure
 * - Non-secure (1) will either stay non-secure or become secure
 * This is the same as using a bitwise AND.
 */
  #define BSP_PRV_SAR_WRITE(register, value)    register &= value
 #else
  #define BSP_PRV_SAR_WRITE(register, value)    register = value
 #endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
void R_BSP_SecurityInit(void);
void R_BSP_PinCfgSecurityInit(void);
void R_BSP_ElcCfgSecurityInit(void);

/***********************************************************************************************************************
 * External symbols
 **********************************************************************************************************************/

 #if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * bsp_nonsecure_func_t)(void);
 #elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile bsp_nonsecure_func_t)(void);
 #endif

 #if BSP_TZ_SECURE_BUILD

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Enter the non-secure code environment.
 *
 * This function configures the non-secure MSP and vector table then jumps to the non-secure project's Reset_Handler.
 *
 * @note This function (and therefore the non-secure code) should not return.
 **********************************************************************************************************************/
void R_BSP_NonSecureEnter (void)
{
    /* The NS vector table is at the start of the NS section in flash */
    uint32_t const * p_ns_vector_table = FLASH_NS_START;

    /* Set up the NS Reset_Handler to be called */
    uint32_t const     * p_ns_reset_address = (uint32_t const *) ((uint32_t) p_ns_vector_table + sizeof(uint32_t));
    bsp_nonsecure_func_t p_ns_reset         = (bsp_nonsecure_func_t) (*p_ns_reset_address);

  #if BSP_TZ_CFG_NON_SECURE_APPLICATION_FALLBACK

    /* Check if the NS application exists. If the address of the Reset_Handler is all '1's, then assume that
     * the NS application has not been programmed.
     *
     * If the secure application attempts to jump to an invalid instruction, a HardFault will occur. If the
     * MCU is in NSECSD state, then the debugger will be unable to connect and program the NS Application. Jumping to
     * a valid instruction ensures that the debugger will be able to connect.
     */
    if (UINT32_MAX == *p_ns_reset_address)
    {
        p_ns_reset = (bsp_nonsecure_func_t) ((uint32_t) RAM_NS_START);

        /* Write an infinite loop into start of NS RAM (Branch T3 Instruction (b.n <RAM_NS_START>)). */
        uint16_t * infinite_loop = (uint16_t *) ((uint32_t) RAM_NS_START);
        *infinite_loop = BSP_PRV_INFINITE_LOOP;

        /* Set the NS stack pointer to a valid location in NS RAM. */
        __TZ_set_MSP_NS((uint32_t) RAM_NS_START + 0x20U);

        /* Jump to the infinite loop. */
        p_ns_reset();
    }
  #endif

    /* Set the NS vector table address */
    SCB_NS->VTOR = (uint32_t) p_ns_vector_table;

    /* Set the NS stack pointer to the first entry in the NS vector table */
    __TZ_set_MSP_NS(p_ns_vector_table[0]);

    /* Jump to the NS Reset_Handler */
    p_ns_reset();
}

/** @} (end addtogroup BSP_MCU) */

/*******************************************************************************************************************//**
 * Initialize security features for TrustZone.
 *
 * This function initializes ARM security register and Renesas SAR registers for secure projects.
 *
 * @note IDAU settings must be configured to match project settings with a separate configuration tool.
 **********************************************************************************************************************/
void R_BSP_SecurityInit (void)
{
    /* Disable PRCR for SARs. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SAR);

  #if 0 == BSP_FEATURE_TZ_HAS_DLM

    /* If DLM is not implemented, then the TrustZone partitions must be set at run-time. */
    R_PSCU->CFSAMONA = (uint32_t) FLASH_NS_START & ~BSP_FEATURE_TZ_NS_OFFSET & R_PSCU_CFSAMONA_CFS2_Msk;
    R_PSCU->CFSAMONB = (uint32_t) FLASH_NSC_START & R_PSCU_CFSAMONB_CFS1_Msk;
    R_PSCU->DFSAMON  = (uint32_t) DATA_FLASH_NS_START & R_PSCU_DFSAMON_DFS_Msk;
    R_PSCU->SSAMONA  = (uint32_t) RAM_NS_START_S_ALIAS & R_PSCU_SSAMONA_SS2_Msk;
    R_PSCU->SSAMONB  = (uint32_t) RAM_NSC_START & R_PSCU_SSAMONB_SS1_Msk;
  #endif

  #if (BSP_CFG_CPU_CORE == 0) && (BSP_FEATURE_BSP_HAS_ITCM)

    /* Total ITCM block size in bytes is equal to 2 ^ (BLKSZ + 5). */
    uint32_t itcm_block_exponent =
        ((MEMSYSCTL->ITGU_CFG & MEMSYSCTL_ITGU_CFG_BLKSZ_Msk) >> MEMSYSCTL_ITGU_CFG_BLKSZ_Pos) +
        5U;
    uint32_t itcm_block_size = (1U << itcm_block_exponent);

    /* The number of secure ITCM blocks is equal to size of the secure region in bytes divided by the ITCM block size. */
    uint32_t itcm_num_sec_blocks =
        ((uint32_t) gp_ddsc_ITCM_END + itcm_block_size - 1 - (uint32_t) gp_ddsc_ITCM_START) >>
        itcm_block_exponent;

    /* Set all secure blocks to '0' and all non-secure blocks to 1. */
    MEMSYSCTL->ITGU_LUT[0] = ~((1U << itcm_num_sec_blocks) - 1U);
  #endif

  #if (BSP_CFG_CPU_CORE == 0) && (BSP_FEATURE_BSP_HAS_DTCM)

    /* Total DTCM block size in bytes is equal to 2 ^ (BLKSZ + 5). */
    uint32_t dtcm_block_exponent =
        ((MEMSYSCTL->DTGU_CFG & MEMSYSCTL_DTGU_CFG_BLKSZ_Msk) >> MEMSYSCTL_DTGU_CFG_BLKSZ_Pos) +
        5U;
    uint32_t dtcm_block_size = (1U << dtcm_block_exponent);

    /* The number of secure DTCM blocks is equal to size of the secure region in bytes divided by the DTCM block size. */
    uint32_t dtcm_num_sec_blocks =
        ((uint32_t) gp_ddsc_DTCM_END + dtcm_block_size - 1 - (uint32_t) gp_ddsc_DTCM_START) >>
        dtcm_block_exponent;

    /* Set all secure blocks to '0' and all non-secure blocks to 1. */
    MEMSYSCTL->DTGU_LUT[0] = ~((1U << dtcm_num_sec_blocks) - 1U);
  #endif

  #if (BSP_CFG_CPU_CORE == 1) && defined(R_TCM)
   #ifdef BSP_PARTITION_CTCM_CPU1_S_START

    /* Set boundary address for CTCM S/NS */
    R_CPSCU->TCMSABARC = BSP_PARTITION_CTCM_CPU1_S_START + BSP_PARTITION_CTCM_CPU1_S_SIZE;
   #endif
   #ifdef BSP_PARTITION_STCM_CPU1_S_START

    /* Set boundary address for STCM S/NS */
    R_CPSCU->TCMSABARS = BSP_PARTITION_STCM_CPU1_S_START + BSP_PARTITION_STCM_CPU1_S_SIZE;
   #endif
  #endif

  #if __SAUREGION_PRESENT
   #if !BSP_SECONDARY_CORE_BUILD

    /* Configure IDAU to divide SRAM region into NSC/NS. */
    R_CPSCU->SRAMSABAR0 = (uint32_t) RAM_NS_START_S_ALIAS & R_CPSCU_SRAMSABAR0_SRAMSABAR_Msk;
    R_CPSCU->SRAMSABAR1 = (uint32_t) RAM_NS_START_S_ALIAS & R_CPSCU_SRAMSABAR1_SRAMSABAR_Msk;
    #if BSP_FEATURE_SRAM_HAS_EXTRA_SRAMSABAR
    R_CPSCU->SRAMSABAR2 = (uint32_t) RAM_NS_START_S_ALIAS & R_CPSCU_SRAMSABAR2_SRAMSABAR_Msk;
    R_CPSCU->SRAMSABAR3 = (uint32_t) RAM_NS_START_S_ALIAS & R_CPSCU_SRAMSABAR3_SRAMSABAR_Msk;
    #endif

    #ifdef BSP_TZ_CFG_SRAMESAR

    /* Configure SRAM ECC Region as S/NS */
    R_CPSCU->SRAMESAR = BSP_TZ_CFG_SRAMESAR;
    #endif
   #endif

    /* Configure SAU region used for Code Flash Non-secure callable. */
    SAU->RNR  = BSP_SAU_REGION_CODE_FLASH_NSC;
    SAU->RBAR = (uint32_t) FLASH_NSC_START & SAU_RBAR_BADDR_Msk;
    SAU->RLAR = (FLASH_NSC_LIMIT & SAU_RLAR_LADDR_Msk) | SAU_RLAR_NSC_Msk |
                SAU_RLAR_ENABLE_Msk;

    /* Configure SAU region used for Non-secure region 1:
     * - ITCM
     * - Code Flash
     * - On-chip flash (Factory Flash)
     * - On-chip flash (option-setting memory)
     */
    SAU->RNR  = BSP_SAU_REGION_1_NS;
    SAU->RBAR = (uint32_t) BSP_PRV_SAU_NS_REGION_1_BASE_ADDRESS & SAU_RBAR_BADDR_Msk;
    SAU->RLAR = ((BSP_PRV_SAU_NS_REGION_1_LIMIT_ADDRESS) &SAU_RLAR_LADDR_Msk) | SAU_RLAR_ENABLE_Msk;

    /* Configure SAU region used for Non-secure callable SRAM. */
    SAU->RNR  = BSP_SAU_REGION_SRAM_NSC;
    SAU->RBAR = (uint32_t) RAM_NSC_START & SAU_RBAR_BADDR_Msk;
    SAU->RLAR = (RAM_NSC_LIMIT & SAU_RLAR_LADDR_Msk) | SAU_RLAR_NSC_Msk |
                SAU_RLAR_ENABLE_Msk;

    /* Configure SAU region used for Non-secure region 2:
     * - DTCM
     * - On-chip SRAM
     * - Standby SRAM
     * - On-chip flash (data flash)
     */
    SAU->RNR  = BSP_SAU_REGION_2_NS;
    SAU->RBAR = ((uint32_t) BSP_PRV_SAU_NS_REGION_2_BASE_ADDRESS & SAU_RBAR_BADDR_Msk) | BSP_FEATURE_TZ_NS_OFFSET;
    SAU->RLAR = (BSP_PRV_SAU_NS_REGION_2_LIMIT_ADDRESS & SAU_RLAR_LADDR_Msk) | SAU_RLAR_ENABLE_Msk;

    /* Configure SAU region used for Non-secure region 3:
     * - Peripheral I/O registers
     * - Flash I/O registers
     * - External address space (CS area)
     * - External address space (SDRAM area)
     * - External address space (OSPI area)
     */
    SAU->RNR  = BSP_SAU_REGION_3_NS;
    SAU->RBAR = BSP_PRV_SAU_NS_REGION_3_BASE_ADDRESS & SAU_RBAR_BADDR_Msk;
    SAU->RLAR = (BSP_PRV_SAU_NS_REGION_3_LIMIT_ADDRESS & SAU_RLAR_LADDR_Msk) | SAU_RLAR_ENABLE_Msk;

    /* Enable the SAU. */
    SAU->CTRL = SAU_CTRL_ENABLE_Msk;

   #if __ICACHE_PRESENT == 1U

    /* Cache maintenance is required when changing security attribution of an address.
     * Barrier instructions are required to guarantee intended operation
     * (See Arm Cortex-M85 Technical Reference Manual Section 10.9.3). */
    SCB_InvalidateICache();
   #endif
  #else

    /* Setting SAU_CTRL.ALLNS to 1 allows the security attribution of all addresses to be set by the IDAU in the
     * system. */
    SAU->CTRL = SAU_CTRL_ALLNS_Msk;
  #endif

    /* The following section of code to configure SCB->AIRCR, SCB->NSACR, and FPU->FPCCR is taken from
     * system_ARMCM33.c in the CMSIS_5 repository. SCB->SCR SLEEPDEEPS bit is not configured because the
     * SCB->SCR SLEEPDEEP bit is ignored on RA MCUs. */
  #if defined(SCB_CSR_AIRCR_INIT) && (SCB_CSR_AIRCR_INIT == 1U)

    /* Configure whether non-secure projects have access to system reset, whether bus fault, hard fault, and NMI target
     * secure or non-secure, and whether non-secure interrupt priorities are reduced to the lowest 8 priority levels. */
    SCB->AIRCR = (SCB->AIRCR & ~(SCB_AIRCR_VECTKEY_Msk | SCB_AIRCR_SYSRESETREQS_Msk |
                                 SCB_AIRCR_BFHFNMINS_Msk | SCB_AIRCR_PRIS_Msk)) |
                 BSP_PRV_AIRCR_VECTKEY |
                 ((SCB_AIRCR_SYSRESETREQS_VAL << SCB_AIRCR_SYSRESETREQS_Pos) & SCB_AIRCR_SYSRESETREQS_Msk) |
                 ((SCB_AIRCR_PRIS_VAL << SCB_AIRCR_PRIS_Pos) & SCB_AIRCR_PRIS_Msk) |
                 ((SCB_AIRCR_BFHFNMINS_VAL << SCB_AIRCR_BFHFNMINS_Pos) & SCB_AIRCR_BFHFNMINS_Msk);
  #endif

  #if defined(__FPU_USED) && (__FPU_USED == 1U) && \
    defined(TZ_FPU_NS_USAGE) && (TZ_FPU_NS_USAGE == 1U)

    /* Configure whether the FPU can be accessed in the non-secure project. */
    SCB->NSACR = (SCB->NSACR & ~(SCB_NSACR_CP10_Msk | SCB_NSACR_CP11_Msk)) |
                 ((SCB_NSACR_CP10_11_VAL << SCB_NSACR_CP10_Pos) & (SCB_NSACR_CP10_Msk | SCB_NSACR_CP11_Msk));

    /* Configure whether FPU registers are always treated as non-secure (and therefore not preserved on the stack when
     * switching from secure to non-secure), and whether the FPU registers should be cleared on exception return. */
    FPU->FPCCR = (FPU->FPCCR & ~(FPU_FPCCR_TS_Msk | FPU_FPCCR_CLRONRETS_Msk | FPU_FPCCR_CLRONRET_Msk)) |
                 ((FPU_FPCCR_TS_VAL << FPU_FPCCR_TS_Pos) & FPU_FPCCR_TS_Msk) |
                 ((FPU_FPCCR_CLRONRETS_VAL << FPU_FPCCR_CLRONRETS_Pos) & FPU_FPCCR_CLRONRETS_Msk) |
                 ((FPU_FPCCR_CLRONRET_VAL << FPU_FPCCR_CLRONRET_Pos) & FPU_FPCCR_CLRONRET_Msk);
  #endif

  #if !BSP_SECONDARY_CORE_BUILD
   #if BSP_FEATURE_BSP_HAS_TZFSAR

    /* Set TrustZone filter to Secure. */
    R_CPSCU->TZFSAR = ~R_CPSCU_TZFSAR_TZFSA0_Msk;
   #endif

    /* Set TrustZone filter exception response. */
    BSP_PRV_OAD_PT_REG = BSP_PRV_TZ_REG_KEY + 1U;
    BSP_PRV_OAD_REG    = BSP_PRV_TZ_REG_KEY + BSP_TZ_CFG_EXCEPTION_RESPONSE;
    BSP_PRV_OAD_PT_REG = BSP_PRV_TZ_REG_KEY + 0U;
  #endif

    /* Initialize PSARs. */
    BSP_PRV_SAR_WRITE(R_PSCU->PSARB, BSP_TZ_CFG_PSARB);
    BSP_PRV_SAR_WRITE(R_PSCU->PSARC, BSP_TZ_CFG_PSARC);
    BSP_PRV_SAR_WRITE(R_PSCU->PSARD, BSP_TZ_CFG_PSARD);
    BSP_PRV_SAR_WRITE(R_PSCU->PSARE, BSP_TZ_CFG_PSARE);

  #if !BSP_SECONDARY_CORE_BUILD
    R_PSCU->MSSAR = BSP_TZ_CFG_MSSAR;
  #endif

    /* Initialize Type 2 SARs. */
  #ifdef BSP_TZ_CFG_CSAR
    R_CPSCU->CSAR = BSP_TZ_CFG_CSAR;                         /* Cache Security Attribution. */
  #endif
  #ifdef BSP_TZ_CFG_CACHESAR
    R_CPSCU->CACHESAR = BSP_TZ_CFG_CACHESAR;                 /* Cache Security Attribution. */
  #endif
  #if !BSP_SECONDARY_CORE_BUILD
    R_SYSTEM->RSTSAR = BSP_TZ_CFG_RSTSAR;                    /* RSTSRn Security Attribution. */
  #endif
    BSP_PRV_SAR_WRITE(R_SYSTEM->LVDSAR, BSP_TZ_CFG_LVDSAR);  /* LVD Security Attribution. */

  #if !BSP_SECONDARY_CORE_BUILD
    R_SYSTEM->CGFSAR = BSP_TZ_CFG_CGFSAR;                    /* CGC Security Attribution. */
    R_SYSTEM->LPMSAR = BSP_TZ_CFG_LPMSAR;                    /* LPM Security Attribution. */
   #ifdef BSP_TZ_CFG_DPFSAR
    R_SYSTEM->DPFSAR = BSP_TZ_CFG_DPFSAR;                    /* Deep Standby Interrupt Factor Security Attribution. */
   #endif
   #ifdef BSP_TZ_CFG_RSCSAR
    R_SYSTEM->RSCSAR = BSP_TZ_CFG_RSCSAR;                    /* RAM Standby Control Security Attribution. */
   #endif
   #ifdef BSP_TZ_CFG_PGCSAR
    R_SYSTEM->PGCSAR = BSP_TZ_CFG_PGCSAR;                    /* Power Gating Control Security Attribution. */
   #endif
   #ifdef BSP_TZ_CFG_BBFSAR
    R_SYSTEM->BBFSAR = BSP_TZ_CFG_BBFSAR;                    /* Battery Backup Security Attribution. */
   #endif
   #ifdef BSP_TZ_CFG_VBRSABAR
    R_SYSTEM->VBRSABAR = BSP_TZ_CFG_VBRSABAR;                /* Battery Backup Security Attribution (VBTBKRn). */
   #endif
  #endif

    BSP_PRV_SAR_WRITE(R_CPSCU->ICUSARA, BSP_TZ_CFG_ICUSARA); /* External IRQ Security Attribution. */

  #if !BSP_SECONDARY_CORE_BUILD
    R_CPSCU->ICUSARB = BSP_TZ_CFG_ICUSARB;                   /* NMI Security Attribution. */
   #ifdef BSP_TZ_CFG_ICUSARC
    R_CPSCU->ICUSARC = BSP_TZ_CFG_ICUSARC;                   /* DMAC Channel Security Attribution. */
   #endif
  #endif

  #ifdef BSP_TZ_CFG_DMACCHSAR
    R_CPSCU->DMACCHSAR |= (BSP_TZ_CFG_DMACCHSAR << DMACX_REGISTER_SHIFT); /* DMAC Channel Security Attribution. */
  #endif

  #if !BSP_SECONDARY_CORE_BUILD
   #ifdef BSP_TZ_CFG_ICUSARD
    R_CPSCU->ICUSARD = BSP_TZ_CFG_ICUSARD;                              /* SELSR0 Security Attribution. */
   #endif
    R_CPSCU->ICUSARE = BSP_TZ_CFG_ICUSARE;                              /* WUPEN0 Security Attribution. */
   #ifdef BSP_TZ_CFG_ICUSARF
    R_CPSCU->ICUSARF = BSP_TZ_CFG_ICUSARF;                              /* WUPEN1 Security Attribution. */
   #endif
   #ifdef BSP_TZ_CFG_TEVTRCR
    R_CPSCU->TEVTRCR = BSP_TZ_CFG_TEVTRCR;                              /* Trusted Event Route Enable. */
   #endif
   #ifdef BSP_TZ_CFG_ELCSARA
    R_ELC->ELCSARA = BSP_TZ_CFG_ELCSARA;                                /* ELCR, ELSEGR0, ELSEGR1 Security Attribution. */
   #endif
   #ifdef BSP_TZ_CFG_FSAR
    R_FCACHE->FSAR = BSP_TZ_CFG_FSAR;                                   /* FLWT and FCKMHZ Security Attribution. */
   #endif
   #ifdef BSP_TZ_CFG_MSAR
    R_MRMS->MSAR = BSP_TZ_CFG_MSAR;                                     /* MRAM Security Attribution. */
   #endif

    R_CPSCU->SRAMSAR = BSP_TZ_CFG_SRAMSAR;                              /* SRAM Security Attribution. */
   #ifdef BSP_TZ_CFG_STBRAMSAR
    R_CPSCU->STBRAMSAR = BSP_TZ_CFG_STBRAMSAR;                          /* Standby RAM Security Attribution. */
   #endif
  #endif

    R_CPSCU->MMPUSARA |= (BSP_TZ_CFG_MMPUSARA << DMACX_REGISTER_SHIFT); /* Security Attribution for the DMAC Bus Master MPU. */

  #if !BSP_SECONDARY_CORE_BUILD
    R_CPSCU->BUSSARA = BSP_TZ_CFG_BUSSARA;                              /* Security Attribution Register A for the BUS Control Registers. */
    R_CPSCU->BUSSARB = BSP_TZ_CFG_BUSSARB;                              /* Security Attribution Register B for the BUS Control Registers. */
   #ifdef BSP_TZ_CFG_BUSSARC
    R_CPSCU->BUSSARC = BSP_TZ_CFG_BUSSARC;                              /* Security Attribution Register C for the BUS Control Registers. */
   #endif
  #endif

  #ifdef BSP_TZ_CFG_IPCSAR
    BSP_PRV_SAR_WRITE(R_CPSCU->IPCSAR, BSP_TZ_CFG_IPCSAR); /* IPC Security Attribution */
  #endif

  #if (defined(BSP_TZ_CFG_ICUSARC) && (BSP_TZ_CFG_ICUSARC != UINT32_MAX)) || \
    (defined(BSP_TZ_CFG_DMACCHSAR) &&                                        \
    ((BSP_TZ_CFG_DMACCHSAR & R_CPSCU_DMACCHSAR_DMACCHSARn_Msk) != R_CPSCU_DMACCHSAR_DMACCHSARn_Msk))

    R_BSP_MODULE_START(FSP_IP_DMAC, 0);

   #if BSP_FEATURE_TZ_VERSION == 2

    /* On MCUs with this implementation of trustzone, DMAST security attribution is set to secure after reset. */
   #else

    /* If any DMAC channels are required by secure program, disable nonsecure write access to DMAST
     * in order to prevent the nonsecure program from disabling all DMAC channels. */
    R_CPSCU->DMACSAR &= ~(1U << DMACX_REGISTER_SHIFT); /* Protect DMAST from nonsecure write access. */
   #endif

    /* Ensure that DMAST is set so that the nonsecure program can use DMA. */
    R_DMA->DMAST = 1U;
  #else

    /* On MCUs with this implementation of trustzone, DMACSAR security attribution is set to secure after reset.
     * If the DMAC is not used in the secure application,then configure DMAST security attribution to non-secure. */
    R_CPSCU->DMACSAR = 1U;
  #endif

  #if BSP_TZ_CFG_DTC_USED
    R_BSP_MODULE_START(FSP_IP_DTC, 0);

   #if BSP_FEATURE_TZ_VERSION == 2

    /* On MCUs with this implementation of trustzone, DTCST security attribution is set to secure after reset. */
   #else

    /* If the DTC is used by the secure program, disable nonsecure write access to DTCST
     * in order to prevent the nonsecure program from disabling all DTC transfers. */
    R_CPSCU->DTCSAR &= ~(1U << DTCX_REGISTER_SHIFT);
   #endif

    /* Ensure that DTCST is set so that the nonsecure program can use DTC. */
    R_DTC->DTCST = 1U;
  #elif BSP_FEATURE_TZ_VERSION == 2

    /* On MCUs with this implementation of trustzone, DTCST security attribution is set to secure after reset.
     * If the DTC is not used in the secure application,then configure DTCST security attribution to non-secure. */
    R_CPSCU->DTCSAR |= (1U << DTCX_REGISTER_SHIFT);
  #endif

    /* Initialize security attribution registers for Pins. */
    R_BSP_PinCfgSecurityInit();

    /* Initialize security attribution registers for ELC. */
    R_BSP_ElcCfgSecurityInit();

    /* Reenable PRCR for SARs. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);
}

/* This function is overridden by tooling. */
BSP_WEAK_REFERENCE void R_BSP_PinCfgSecurityInit (void)
{
}

/* This function is overridden by tooling. */
BSP_WEAK_REFERENCE void R_BSP_ElcCfgSecurityInit (void)
{
}

 #endif
#endif
