/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
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
 #define BSP_PRV_AIRCR_VECTKEY            (0x05FA0000U)

/* Branch T3 Instruction (IMM11=-2) */
 #define BSP_PRV_INFINITE_LOOP            (0xE7FE)

 #define BSP_SAU_REGION_ROM_NSC           (0U) // SAU Region 0
 #define BSP_SAU_REGION_CODE_MRM_NS       (1U) // SAU Region 1
 #define BSP_SAU_REGION_CODE_SRAM_NSC     (2U) // SAU Region 2
 #define BSP_SAU_REGION_CODE_NVM_NSC      (3U) // SAU Region 3
 #define BSP_SAU_REGION_CODE_SRAM_NS      (4U) // SAU Region 4
 #define BSP_SAU_REGION_CODE_NVM_NS       (5U) // SAU Region 5
 #define BSP_SAU_REGION_CODE_QSPI_NS      (6U) // SAU Region 6
 #define BSP_SAU_REGION_DATA_PERIPH_NS    (7U) // SAU Region 7

/* Non-secure regions defined by the IDAU. These regions must be defined as non-secure in the SAU. */

// TODO: Use BSP BASE Address macros instead of magic numbers to define the next addresses

 #define BSP_SAU_REGION_SROM_NSC_BASE_ADDRESS           (0x0000010000U)
 #define BSP_SAU_REGION_SROM_NSC_LIMIT_ADDRESS          ((BSP_SAU_REGION_SROM_NSC_BASE_ADDRESS) +0x0000010000U)

 #define BSP_SAU_REGION_CODE_MRM_NS_BASE_ADDRESS        (0x01000020U | BSP_FEATURE_TZ_NS_OFFSET)
 #define BSP_SAU_REGION_CODE_MRM_NS_LIMIT_ADDRESS       ((BSP_SAU_REGION_CODE_MRM_NS_BASE_ADDRESS) +0x0000003BU)

 #define BSP_SAU_REGION_CODE_SRAM_NS_BASE_ADDRESS       (0x03000000U | BSP_FEATURE_TZ_NS_OFFSET)
 #define BSP_SAU_REGION_CODE_SRAM_NS_LIMIT_ADDRESS      ((BSP_SAU_REGION_CODE_SRAM_NS_BASE_ADDRESS) +0x00FFFFFFU)

 #define BSP_SAU_REGION_CODE_NVM_NS_BASE_ADDRESS        (0x04000000U | BSP_FEATURE_TZ_NS_OFFSET)
 #define BSP_SAU_REGION_CODE_NVM_NS_LIMIT_ADDRESS       ((BSP_SAU_REGION_CODE_NVM_NS_BASE_ADDRESS) +0x00FFFFFFU)

 #define BSP_SAU_REGION_CODE_QSPI_NS_BASE_ADDRESS       (0x06000000U | BSP_FEATURE_TZ_NS_OFFSET)
 #define BSP_SAU_REGION_CODE_QSPI_NS_LIMIT_ADDRESS      ((BSP_SAU_REGION_CODE_QSPI_NS_BASE_ADDRESS) +0x01FFFFFFU)

 #define BSP_SAU_REGION_DATA_PERIPH_NS_BASE_ADDRESS     (0x30000000U)
 #define BSP_SAU_REGION_DATA_PERIPH_NS_LIMIT_ADDRESS    (0x5FFFFFFFU)

/* Use partition macros for primary core */
 #define FLASH_NSC_START                                ((uint32_t *) BSP_PARTITION_FLASH_CPU0_C_START)
 #define FLASH_NSC_LIMIT                                ((uint32_t) BSP_PARTITION_FLASH_CPU0_C_START + \
                                                         BSP_PARTITION_FLASH_CPU0_C_SIZE - 1)
 #define FLASH_NS_START                                 ((uint32_t *) BSP_PARTITION_FLASH_CPU0_N_START)
 #define RAMCODE_NSC_START                              ((uint32_t *) BSP_PARTITION_RAMCODE_CPU0_C_START)
 #define RAMCODE_NSC_LIMIT                              ((uint32_t) BSP_PARTITION_RAMCODE_CPU0_C_START + \
                                                         BSP_PARTITION_RAMCODE_CPU0_C_SIZE - 1)
 #define RAMCODE_NS_START                               ((uint32_t *) BSP_PARTITION_RAMCODE_CPU0_N_START)

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
    uint32_t const * p_ns_vector_table = (uint32_t *) ((uint32_t) FLASH_NS_START);

    /* Set up the NS Reset_Handler to be called */
    uint32_t const     * p_ns_reset_address = (uint32_t const *) ((uint32_t) p_ns_vector_table + sizeof(uint32_t));
    bsp_nonsecure_func_t p_ns_reset         = (bsp_nonsecure_func_t) (*p_ns_reset_address);

  #if BSP_TZ_CFG_NON_SECURE_APPLICATION_FALLBACK
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
  #if __SAUREGION_PRESENT
    ICU->ICU_NMIER_REG_b.ICU_TZ_EN = 0x1;         // Enable TZ NMI
    CRG_TOP->TZ_CFG_REG_b.TZ_EN = 0x1;            // Enable TZ
    CRG_TOP->TZ_CFG_REG_b.TZ_ERR_RESP = 0x1;      // Set NMI response upon TZ error
    CRG_TOP->TZ_ERR_STAT_REG_b.TZ_ERR_STAT = 0x1; // Enable TZ error

    // TODO: This register must be set based on the size of the S/NS applications. Temporary split of the NVM between S/NS worlds to enable NS
    // TODO: application executed without raising a HardFault due to TZ violation.
    SYSB->TZ_NVMB_REG_b.TZ_NVMB = (uint32_t) FLASH_NS_START & SYSB_TZ_NVMB_REG_TZ_NVMB_Msk;
    SYSB->TZ_RAMB_REG_b.TZ_RAMB = (uint32_t) RAMCODE_NS_START & SYSB_TZ_RAMB_REG_TZ_RAMB_Msk;

    /* Maintain the default settings of SAU to ensure the SAU attribution for the entire ROM area remains secure. */
    SAU->RNR = BSP_SAU_REGION_ROM_NSC;
    SAU->RBAR = (uint32_t) BSP_SAU_REGION_SROM_NSC_BASE_ADDRESS & SAU_RBAR_BADDR_Msk;
    SAU->RLAR = (BSP_SAU_REGION_SROM_NSC_LIMIT_ADDRESS & SAU_RLAR_LADDR_Msk) | SAU_RLAR_NSC_Msk |
                SAU_RLAR_ENABLE_Msk;

    /* Configure SAU region used for Non-secure MRM */
    SAU->RNR = BSP_SAU_REGION_CODE_MRM_NS;
    SAU->RBAR = (uint32_t) BSP_SAU_REGION_CODE_MRM_NS_BASE_ADDRESS & SAU_RBAR_BADDR_Msk;
    SAU->RLAR = (BSP_SAU_REGION_CODE_MRM_NS_LIMIT_ADDRESS & SAU_RLAR_LADDR_Msk) | SAU_RLAR_ENABLE_Msk;

    /* Configure SAU region used for Non-secure callable SRAM (Code). */
    SAU->RNR = BSP_SAU_REGION_CODE_SRAM_NSC;
    SAU->RBAR = (uint32_t) RAMCODE_NSC_START & SAU_RBAR_BADDR_Msk;
    SAU->RLAR = (RAMCODE_NSC_LIMIT & SAU_RLAR_LADDR_Msk) | SAU_RLAR_NSC_Msk |
                SAU_RLAR_ENABLE_Msk;

    /* Configure SAU region used for Non-secure callable NVM (Code). */
    SAU->RNR = BSP_SAU_REGION_CODE_NVM_NSC;
    SAU->RBAR = (uint32_t) FLASH_NSC_START & SAU_RBAR_BADDR_Msk;
    SAU->RLAR = (FLASH_NSC_LIMIT & SAU_RLAR_LADDR_Msk) | SAU_RLAR_NSC_Msk |
                SAU_RLAR_ENABLE_Msk;

    /* Configure SAU region used for Non-secure SRAM (Code). */
    SAU->RNR = BSP_SAU_REGION_CODE_SRAM_NS;
    SAU->RBAR = (uint32_t) BSP_SAU_REGION_CODE_SRAM_NS_BASE_ADDRESS & SAU_RBAR_BADDR_Msk;
    SAU->RLAR = (BSP_SAU_REGION_CODE_SRAM_NS_LIMIT_ADDRESS & SAU_RLAR_LADDR_Msk) | SAU_RLAR_ENABLE_Msk;

    /* Configure SAU region used for Non-secure NVM (Code). */
    SAU->RNR = BSP_SAU_REGION_CODE_NVM_NS;
    SAU->RBAR = (uint32_t) BSP_SAU_REGION_CODE_NVM_NS_BASE_ADDRESS & SAU_RBAR_BADDR_Msk;
    SAU->RLAR = (BSP_SAU_REGION_CODE_NVM_NS_LIMIT_ADDRESS & SAU_RLAR_LADDR_Msk) | SAU_RLAR_ENABLE_Msk;

    /* Configure SAU region used for always Non-secure QSPI (Code). */
    SAU->RNR = BSP_SAU_REGION_CODE_QSPI_NS;
    SAU->RBAR = (uint32_t) BSP_SAU_REGION_CODE_QSPI_NS_BASE_ADDRESS & SAU_RBAR_BADDR_Msk;
    SAU->RLAR = (BSP_SAU_REGION_CODE_QSPI_NS_LIMIT_ADDRESS & SAU_RLAR_LADDR_Msk) | SAU_RLAR_ENABLE_Msk;

    /* Configure SAU region used for Non-secure NVM/SRAM (Data) and AHB/APB Peripherals. */

    // TODO: Consider splitting this SAU region into multiple regions (Optional, as the final security attribution is overruled by IDAU).
    SAU->RNR = BSP_SAU_REGION_DATA_PERIPH_NS;
    SAU->RBAR = (uint32_t) BSP_SAU_REGION_DATA_PERIPH_NS_BASE_ADDRESS & SAU_RBAR_BADDR_Msk;
    SAU->RLAR = (BSP_SAU_REGION_DATA_PERIPH_NS_LIMIT_ADDRESS & SAU_RLAR_LADDR_Msk) | SAU_RLAR_ENABLE_Msk;

    /* Enable the SAU. */
    SAU->CTRL = SAU_CTRL_ENABLE_Msk;

    // Configure Secure Fault Handler
    SCB->SHCSR |= SCB_SHCSR_SECUREFAULTENA_Msk;

    /* Cache maintenance is required when changing security attribution of an address.
     * Barrier instructions are required to guarantee intended operation
     * (See Arm Cortex-M85 Technical Reference Manual Section 10.9.3). */

    // SCB_InvalidateICache();
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

    /* Initialize SSA Registers. */
    SYSB->TZ_SSA_REG = BSP_TZ_CFG_SSA_REG;
    SYSB->TZ_SSA2_REG = BSP_TZ_CFG_SSA2_REG;

    /* Initialize Type 2 SARs. */

    // TODO: Add Type 2 SARs initialization

    // TODO: Port it or drop it
  #if (defined(BSP_TZ_CFG_ICUSARC) && (BSP_TZ_CFG_ICUSARC != UINT32_MAX)) || \
    (defined(BSP_TZ_CFG_DMACCHSAR) &&                                        \
    ((BSP_TZ_CFG_DMACCHSAR & R_CPSCU_DMACCHSAR_DMACCHSARn_Msk) != R_CPSCU_DMACCHSAR_DMACCHSARn_Msk))

    R_BSP_MODULE_START(FSP_IP_DMAC, 0);

    /* On MCUs with this implementation of trustzone, DMAST security attribution is set to secure after reset. */

    /* Ensure that DMAST is set so that the nonsecure program can use DMA. */

    // R_DMA->DMAST = 1U;
  #else

    /* On MCUs with this implementation of trustzone, DMACSAR security attribution is set to secure after reset.
     * If the DMAC is not used in the secure application,then configure DMAST security attribution to non-secure. */

    // R_CPSCU->DMACSAR = 1U;
  #endif

  #if BSP_TZ_CFG_DTC_USED
    R_BSP_MODULE_START(FSP_IP_DTC, 0);

    /* On MCUs with this implementation of trustzone, DTCST security attribution is set to secure after reset. */

    /* Ensure that DTCST is set so that the nonsecure program can use DTC. */

    // R_DTC->DTCST = 1U;
  #elif BSP_FEATURE_TZ_VERSION == 2    // TODO: consider removing it

    /* On MCUs with this implementation of trustzone, DTCST security attribution is set to secure after reset.
     * If the DTC is not used in the secure application,then configure DTCST security attribution to non-secure. */

    // R_CPSCU->DTCSAR = 1U;
  #endif

    /* Initialize security attribution registers for Pins. */
    R_BSP_PinCfgSecurityInit();

    /* Initialize security attribution registers for ELC. */
    R_BSP_ElcCfgSecurityInit();
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
