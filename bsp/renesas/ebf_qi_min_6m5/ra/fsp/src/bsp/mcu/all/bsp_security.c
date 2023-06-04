/***********************************************************************************************************************
 * Copyright [2020-2023] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics America Inc. and may only be used with products
 * of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.  Renesas products are
 * sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for the selection and use
 * of Renesas products and Renesas assumes no liability.  No license, express or implied, to any intellectual property
 * right is granted by Renesas. This software is protected under all applicable laws, including copyright laws. Renesas
 * reserves the right to change or discontinue this software and/or this documentation. THE SOFTWARE AND DOCUMENTATION
 * IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT
 * PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE OR
 * DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.  TO THE MAXIMUM
 * EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR DOCUMENTATION
 * (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING,
 * WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY LOST PROFITS,
 * OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE POSSIBILITY
 * OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

#if BSP_FEATURE_TZ_HAS_TRUSTZONE

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
 #define BSP_PRV_TZ_REG_KEY       (0xA500U)
 #define BSP_PRV_AIRCR_VECTKEY    (0x05FA0000U)
 #define RA_NOT_DEFINED           (0)

/* Branch T3 Instruction (IMM11=-2) */
 #define BSP_PRV_INFINITE_LOOP    (0xE7FE)

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
extern const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES];

 #if defined(__ARMCC_VERSION) || defined(__ICCARM__)
typedef void (BSP_CMSE_NONSECURE_CALL * bsp_nonsecure_func_t)(void);
 #elif defined(__GNUC__)
typedef BSP_CMSE_NONSECURE_CALL void (*volatile bsp_nonsecure_func_t)(void);
 #endif

 #if   defined(__IAR_SYSTEMS_ICC__) && BSP_TZ_SECURE_BUILD

  #pragma section=".tz_flash_ns_start"
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_flash = (uint32_t *) __section_begin(".tz_flash_ns_start");
  #pragma section="Veneer$$CMSE"
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_callable_flash = (uint32_t *) __section_begin(
    "Veneer$$CMSE");
  #pragma section=".tz_ram_ns_start"
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_ram = (uint32_t *) __section_begin(".tz_ram_ns_start");
  #pragma section=".tz_ram_nsc_start"
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_callable_ram = (uint32_t *) __section_begin(
    ".tz_ram_nsc_start");
  #pragma section=".tz_data_flash_ns_start"
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_data_flash = (uint32_t *) __section_begin(
    ".tz_data_flash_ns_start");

 #elif defined(__ARMCC_VERSION)
  #if BSP_FEATURE_BSP_HAS_ITCM
extern const uint32_t Image$$__tz_ITCM_N$$Base;
extern const uint32_t Image$$__tz_ITCM_S$$Base;
  #endif
  #if BSP_FEATURE_BSP_HAS_DTCM
extern const uint32_t Image$$__tz_DTCM_N$$Base;
extern const uint32_t Image$$__tz_DTCM_S$$Base;
  #endif
  #if BSP_FEATURE_BSP_HAS_STBRAMSABAR
extern const uint32_t Image$$__tz_STANDBY_SRAM_N$$Base;
extern const uint32_t Image$$__tz_STANDBY_SRAM_S$$Base;
  #endif
extern const uint32_t Image$$__tz_FLASH_N$$Base;
extern const uint32_t Image$$__tz_FLASH_C$$Base;
extern const uint32_t Image$$__tz_FLASH_S$$Base;
extern const uint32_t Image$$__tz_RAM_N$$Base;
extern const uint32_t Image$$__tz_RAM_C$$Base;
extern const uint32_t Image$$__tz_RAM_S$$Base;
extern const uint32_t Image$$__tz_DATA_FLASH_N$$Base;
extern const uint32_t Image$$__tz_DATA_FLASH_S$$Base;
extern const uint32_t Image$$__tz_QSPI_FLASH_N$$Base;
extern const uint32_t Image$$__tz_QSPI_FLASH_S$$Base;
extern const uint32_t Image$$__tz_SDRAM_N$$Base;
extern const uint32_t Image$$__tz_SDRAM_S$$Base;
extern const uint32_t Image$$__tz_OSPI_DEVICE_0_N$$Base;
extern const uint32_t Image$$__tz_OSPI_DEVICE_0_S$$Base;
extern const uint32_t Image$$__tz_OSPI_DEVICE_1_N$$Base;
extern const uint32_t Image$$__tz_OSPI_DEVICE_1_S$$Base;
extern const uint32_t Image$$__tz_OPTION_SETTING_N$$Base;
extern const uint32_t Image$$__tz_OPTION_SETTING_S$$Base;
extern const uint32_t Image$$__tz_OPTION_SETTING_S_N$$Base;
extern const uint32_t Image$$__tz_OPTION_SETTING_S_S$$Base;
extern const uint32_t Image$$__tz_ID_CODE_N$$Base;
extern const uint32_t Image$$__tz_ID_CODE_S$$Base;

  #if BSP_FEATURE_BSP_HAS_ITCM
   #define __tz_ITCM_N               Image$$__tz_ITCM_N$$Base
   #define __tz_ITCM_S               Image$$__tz_ITCM_S$$Base
  #endif
  #if BSP_FEATURE_BSP_HAS_DTCM
   #define __tz_DTCM_N               Image$$__tz_DTCM_N$$Base
   #define __tz_DTCM_S               Image$$__tz_DTCM_S$$Base
  #endif
  #if BSP_FEATURE_BSP_HAS_STBRAMSABAR
   #define __tz_STANDBY_SRAM_N       Image$$__tz_STANDBY_SRAM_N$$Base
   #define __tz_STANDBY_SRAM_S       Image$$__tz_STANDBY_SRAM_S$$Base
  #endif
  #define __tz_FLASH_N               Image$$__tz_FLASH_N$$Base
  #define __tz_FLASH_C               Image$$__tz_FLASH_C$$Base
  #define __tz_FLASH_S               Image$$__tz_FLASH_S$$Base
  #define __tz_RAM_N                 Image$$__tz_RAM_N$$Base
  #define __tz_RAM_C                 Image$$__tz_RAM_C$$Base
  #define __tz_RAM_S                 Image$$__tz_RAM_S$$Base
  #define __tz_DATA_FLASH_N          Image$$__tz_DATA_FLASH_N$$Base
  #define __tz_DATA_FLASH_S          Image$$__tz_DATA_FLASH_S$$Base
  #define __tz_QSPI_FLASH_N          Image$$__tz_QSPI_FLASH_N$$Base
  #define __tz_QSPI_FLASH_S          Image$$__tz_QSPI_FLASH_S$$Base
  #define __tz_SDRAM_N               Image$$__tz_SDRAM_N$$Base
  #define __tz_SDRAM_S               Image$$__tz_SDRAM_S$$Base
  #define __tz_OSPI_DEVICE_0_N       Image$$__tz_OSPI_DEVICE_0_N$$Base
  #define __tz_OSPI_DEVICE_0_S       Image$$__tz_OSPI_DEVICE_0_S$$Base
  #define __tz_OSPI_DEVICE_1_N       Image$$__tz_OSPI_DEVICE_1_N$$Base
  #define __tz_OSPI_DEVICE_1_S       Image$$__tz_OSPI_DEVICE_1_S$$Base
  #define __tz_OPTION_SETTING_N      Image$$__tz_OPTION_SETTING_N$$Base
  #define __tz_OPTION_SETTING_S      Image$$__tz_OPTION_SETTING_S$$Base
  #define __tz_OPTION_SETTING_S_N    Image$$__tz_OPTION_SETTING_S_N$$Base
  #define __tz_OPTION_SETTING_S_S    Image$$__tz_OPTION_SETTING_S_S$$Base
  #define __tz_ID_CODE_N             Image$$__tz_ID_CODE_N$$Base
  #define __tz_ID_CODE_S             Image$$__tz_ID_CODE_S$$Base

/* Assign region addresses to pointers so that AC6 includes symbols that can be used to determine the
 * start addresses of Secure, Non-secure and Non-secure Callable regions. */
  #if BSP_FEATURE_BSP_HAS_ITCM
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_itcm = &__tz_ITCM_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_secure_itcm    = &__tz_ITCM_S;
  #endif
  #if BSP_FEATURE_BSP_HAS_DTCM
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_dtcm = &__tz_DTCM_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_secure_dtcm    = &__tz_DTCM_S;
  #endif
  #if BSP_FEATURE_BSP_HAS_STBRAMSABAR
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_standby_sram = &__tz_STANDBY_SRAM_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_secure_standby_sram    = &__tz_STANDBY_SRAM_S;
  #endif
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_flash          = &__tz_FLASH_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_callable_flash = &__tz_FLASH_C;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_secure_flash             = &__tz_FLASH_S;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_ram            = &__tz_RAM_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_callable_ram   = &__tz_RAM_C;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_secure_ram               = &__tz_RAM_S;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_data_flash     = &__tz_DATA_FLASH_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_secure_data_flash        = &__tz_DATA_FLASH_S;

  #if BSP_TZ_SECURE_BUILD

BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_qspi_flash       = &__tz_QSPI_FLASH_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_secure_qspi_flash          = &__tz_QSPI_FLASH_S;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_sdram            = &__tz_SDRAM_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_secure_sdram               = &__tz_SDRAM_S;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_ospi_device_0    = &__tz_OSPI_DEVICE_0_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_secure_ospi_device_0       = &__tz_OSPI_DEVICE_0_S;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_ospi_device_1    = &__tz_OSPI_DEVICE_1_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_secure_ospi_device_1       = &__tz_OSPI_DEVICE_1_S;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_option_setting   = &__tz_OPTION_SETTING_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_secure_option_setting      = &__tz_OPTION_SETTING_S;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_option_setting_s = &__tz_OPTION_SETTING_S_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_secure_option_setting_s    = &__tz_OPTION_SETTING_S_S;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_id_code          = &__tz_ID_CODE_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_secure_id_code             = &__tz_ID_CODE_S;

  #endif

 #elif defined(__GNUC__)

extern const uint32_t FLASH_NS_IMAGE_START;
extern const uint32_t __tz_FLASH_C;
extern const uint32_t __tz_DATA_FLASH_N;
extern const uint32_t __tz_RAM_N;
extern const uint32_t __tz_RAM_C;

BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_flash          = &FLASH_NS_IMAGE_START;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_callable_flash = (uint32_t *) &__tz_FLASH_C;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_data_flash     = (uint32_t *) &__tz_DATA_FLASH_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_ram            = (uint32_t *) &__tz_RAM_N;
BSP_DONT_REMOVE uint32_t const * const gp_start_of_nonsecure_callable_ram   = (uint32_t *) &__tz_RAM_C;

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
    uint32_t const * p_ns_vector_table = gp_start_of_nonsecure_flash;

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
        p_ns_reset = (bsp_nonsecure_func_t) gp_start_of_nonsecure_ram;

        /* Write an infinite loop into start of NS RAM (Branch T3 Instruction (b.n <gp_start_of_nonsecure_ram>)). */
        uint16_t * infinite_loop = (uint16_t *) gp_start_of_nonsecure_ram;
        *infinite_loop = BSP_PRV_INFINITE_LOOP;

        /* Set the NS stack pointer to a valid location in NS RAM. */
        __TZ_set_MSP_NS((uint32_t) gp_start_of_nonsecure_ram + 0x20U);

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
    R_PSCU->CFSAMONA = (uint32_t) gp_start_of_nonsecure_flash & R_PSCU_CFSAMONA_CFS2_Msk;
    R_PSCU->CFSAMONB = (uint32_t) gp_start_of_nonsecure_callable_flash & R_PSCU_CFSAMONB_CFS1_Msk;
    R_PSCU->DFSAMON  = (uint32_t) gp_start_of_nonsecure_data_flash & R_PSCU_DFSAMON_DFS_Msk;
    R_PSCU->SSAMONA  = (uint32_t) gp_start_of_nonsecure_ram & R_PSCU_SSAMONA_SS2_Msk;
    R_PSCU->SSAMONB  = (uint32_t) gp_start_of_nonsecure_callable_ram & R_PSCU_SSAMONB_SS1_Msk;
  #endif

    /* Setting SAU_CTRL.ALLNS to 1 allows the security attribution of all addresses to be set by the IDAU in the
     * system. */
    SAU->CTRL = SAU_CTRL_ALLNS_Msk;

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

  #if BSP_FEATURE_BSP_HAS_TZFSAR

    /* Set TrustZone filter to Secure. */
    R_TZF->TZFSAR = ~R_TZF_TZFSAR_TZFSA0_Msk;
  #endif

    /* Set TrustZone filter exception response. */
    R_TZF->TZFPT  = BSP_PRV_TZ_REG_KEY + 1U;
    R_TZF->TZFOAD = BSP_PRV_TZ_REG_KEY + BSP_TZ_CFG_EXCEPTION_RESPONSE;
    R_TZF->TZFPT  = BSP_PRV_TZ_REG_KEY + 0U;

    /* Initialize PSARs. */
    R_PSCU->PSARB = BSP_TZ_CFG_PSARB;
    R_PSCU->PSARC = BSP_TZ_CFG_PSARC;
    R_PSCU->PSARD = BSP_TZ_CFG_PSARD;
    R_PSCU->PSARE = BSP_TZ_CFG_PSARE;
    R_PSCU->MSSAR = BSP_TZ_CFG_MSSAR;

    /* Initialize Type 2 SARs. */
  #ifdef BSP_TZ_CFG_CSAR
    R_CPSCU->CSAR = BSP_TZ_CFG_CSAR;           /* Cache Security Attribution. */
  #endif
    R_SYSTEM->RSTSAR = BSP_TZ_CFG_RSTSAR;      /* RSTSRn Security Attribution. */
    R_SYSTEM->LVDSAR = BSP_TZ_CFG_LVDSAR;      /* LVD Security Attribution. */
    R_SYSTEM->CGFSAR = BSP_TZ_CFG_CGFSAR;      /* CGC Security Attribution. */
    R_SYSTEM->LPMSAR = BSP_TZ_CFG_LPMSAR;      /* LPM Security Attribution. */
    R_SYSTEM->DPFSAR = BSP_TZ_CFG_DPFSAR;      /* Deep Standby Interrupt Factor Security Attribution. */
  #ifdef BSP_TZ_CFG_BBFSAR
    R_SYSTEM->BBFSAR = BSP_TZ_CFG_BBFSAR;      /* Battery Backup Security Attribution. */
  #endif
    R_CPSCU->ICUSARA = BSP_TZ_CFG_ICUSARA;     /* External IRQ Security Attribution. */
    R_CPSCU->ICUSARB = BSP_TZ_CFG_ICUSARB;     /* NMI Security Attribution. */
  #ifdef BSP_TZ_CFG_ICUSARC
    R_CPSCU->ICUSARC = BSP_TZ_CFG_ICUSARC;     /* DMAC Channel Security Attribution. */
  #endif
  #ifdef BSP_TZ_CFG_DMASARA
    R_CPSCU->DMASARA = BSP_TZ_CFG_DMASARA;     /* DMAC Channel Security Attribution. */
  #endif
  #ifdef BSP_TZ_CFG_ICUSARD
    R_CPSCU->ICUSARD = BSP_TZ_CFG_ICUSARD;     /* SELSR0 Security Attribution. */
  #endif
    R_CPSCU->ICUSARE = BSP_TZ_CFG_ICUSARE;     /* WUPEN0 Security Attribution. */
  #ifdef BSP_TZ_CFG_ICUSARF
    R_CPSCU->ICUSARF = BSP_TZ_CFG_ICUSARF;     /* WUPEN1 Security Attribution. */
  #endif
  #ifdef BSP_TZ_CFG_TEVTRCR
    R_CPSCU->TEVTRCR = BSP_TZ_CFG_TEVTRCR;     /* Trusted Event Route Enable. */
  #endif
    R_FCACHE->FSAR     = BSP_TZ_CFG_FSAR;      /* FLWT and FCKMHZ Security Attribution. */
    R_CPSCU->SRAMSAR   = BSP_TZ_CFG_SRAMSAR;   /* SRAM Security Attribution. */
    R_CPSCU->STBRAMSAR = BSP_TZ_CFG_STBRAMSAR; /* Standby RAM Security Attribution. */
    R_CPSCU->MMPUSARA  = BSP_TZ_CFG_MMPUSARA;  /* Security Attribution for the DMAC Bus Master MPU. */
    R_CPSCU->BUSSARA   = BSP_TZ_CFG_BUSSARA;   /* Security Attribution Register A for the BUS Control Registers. */
    R_CPSCU->BUSSARB   = BSP_TZ_CFG_BUSSARB;   /* Security Attribution Register B for the BUS Control Registers. */

  #if (defined(BSP_TZ_CFG_ICUSARC) && (BSP_TZ_CFG_ICUSARC != UINT32_MAX)) || \
    (defined(BSP_TZ_CFG_DMASARA) && (BSP_TZ_CFG_DMASARA != UINT32_MAX))

    R_BSP_MODULE_START(FSP_IP_DMAC, 0);

    /* If any DMAC channels are required by secure program, disable nonsecure write access to DMAST
     * in order to prevent the nonsecure program from disabling all DMAC channels. */
    R_CPSCU->DMACSAR = ~1U;            /* Protect DMAST from nonsecure write access. */

    /* Ensure that DMAST is set so that the nonsecure program can use DMA. */
    R_DMA->DMAST = 1U;
  #endif

  #if BSP_TZ_CFG_DTC_USED
    R_BSP_MODULE_START(FSP_IP_DTC, 0);

    /* If the DTC is used by the secure program, disable nonsecure write access to DTCST
     * in order to prevent the nonsecure program from disabling all DTC transfers. */
    R_CPSCU->DTCSAR = ~1U;

    /* Ensure that DTCST is set so that the nonsecure program can use DTC. */
    R_DTC->DTCST = 1U;
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
