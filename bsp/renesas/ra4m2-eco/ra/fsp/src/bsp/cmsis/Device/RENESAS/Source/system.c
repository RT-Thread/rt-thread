/***********************************************************************************************************************
 * Copyright [2020-2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <string.h>
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Mask to select CP bits( 0xF00000 ) */
#define CP_MASK                                       (0xFU << 20)

/* Startup value for CCR to enable instruction cache, branch prediction and LOB extension */
#define CCR_CACHE_ENABLE                              (0x000E0201)

/* Value to write to OAD register of MPU stack monitor to enable NMI when a stack overflow is detected. */
#define BSP_STACK_POINTER_MONITOR_NMI_ON_DETECTION    (0xA500U)

/* Key code for writing PRCR register. */
#define BSP_PRV_PRCR_KEY                              (0xA500U)
#define BSP_PRV_PRCR_PRC1_UNLOCK                      ((BSP_PRV_PRCR_KEY) | 0x2U)
#define BSP_PRV_PRCR_LOCK                             ((BSP_PRV_PRCR_KEY) | 0x0U)
#define BSP_PRV_STACK_LIMIT                           ((uint32_t) __Vectors[0] - BSP_CFG_STACK_MAIN_BYTES)
#define BSP_PRV_STACK_TOP                             ((uint32_t) __Vectors[0])
#define BSP_TZ_STACK_SEAL_VALUE                       (0xFEF5EDA5)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/** System Clock Frequency (Core Clock) */
uint32_t SystemCoreClock BSP_SECTION_EARLY_INIT;

#if defined(__ARMCC_VERSION)
extern uint32_t Image$$BSS$$ZI$$Base;
extern uint32_t Image$$BSS$$ZI$$Length;
extern uint32_t Load$$DATA$$Base;
extern uint32_t Image$$DATA$$Base;
extern uint32_t Image$$DATA$$Length;
extern uint32_t Image$$STACK$$ZI$$Base;
extern uint32_t Image$$STACK$$ZI$$Length;
 #if BSP_FEATURE_BSP_HAS_DTCM == 1
extern uint32_t Load$$DTCM_DATA_INIT$$Base;
extern uint32_t Image$$DTCM_DATA_INIT$$Base;
extern uint32_t Image$$DTCM_DATA_INIT$$Length;
 #endif
#elif defined(__GNUC__)

/* Generated by linker. */
extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __StackLimit;
extern uint32_t __StackTop;
 #if BSP_FEATURE_BSP_HAS_DTCM == 1
extern uint32_t __dtcm_data_init_start;
extern uint32_t __dtcm_data_start__;
extern uint32_t __dtcm_data_end__;
 #endif
#elif defined(__ICCARM__)
 #pragma section=".bss"
 #pragma section=".data"
 #pragma section=".data_init"
 #pragma section=".stack"
 #if BSP_FEATURE_BSP_HAS_DTCM == 1
  #pragma section=".dtcm_data"
  #pragma section=".dtcm_data_init"
 #endif
#endif

/* Initialize static constructors */
#if defined(__ARMCC_VERSION)
extern void (* Image$$INIT_ARRAY$$Base[])(void);
extern void (* Image$$INIT_ARRAY$$Limit[])(void);
#elif defined(__GNUC__)

extern void (* __init_array_start[])(void);

extern void (* __init_array_end[])(void);
#elif defined(__ICCARM__)
extern void __call_ctors(void const *, void const *);

 #pragma section = "SHT$$PREINIT_ARRAY" const
 #pragma section = "SHT$$INIT_ARRAY" const
#endif

extern void * __Vectors[];

extern void R_BSP_SecurityInit(void);

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

#if BSP_FEATURE_BSP_RESET_TRNG
static void bsp_reset_trng_circuit(void);

#endif

#if defined(__ICCARM__)

void R_BSP_WarmStart(bsp_warm_start_event_t event);

 #pragma weak R_BSP_WarmStart

#elif defined(__GNUC__) || defined(__ARMCC_VERSION)

void R_BSP_WarmStart(bsp_warm_start_event_t event) __attribute__((weak));

#endif

#if BSP_CFG_EARLY_INIT
static void bsp_init_uninitialized_vars(void);

#endif

/*******************************************************************************************************************//**
 * Initialize the MCU and the runtime environment.
 **********************************************************************************************************************/
void SystemInit (void)
{
#if defined(RENESAS_CORTEX_M85)

    /* Enable the ARM core instruction cache, branch prediction and low-overhead-branch extension.
     * See Section 5.5 of the Cortex-M55 TRM and Section D1.2.9 in the ARMv8-M Architecture Reference Manual */
    SCB->CCR = (uint32_t) CCR_CACHE_ENABLE;
    __DSB();
    __ISB();
#endif

#if __FPU_USED

    /* Enable the FPU only when it is used.
     * Code taken from Section 7.1, Cortex-M4 TRM (DDI0439C) */

    /* Set bits 20-23 (CP10 and CP11) to enable FPU. */
    SCB->CPACR = (uint32_t) CP_MASK;
#endif

#if BSP_TZ_SECURE_BUILD

    /* Seal the main stack for secure projects. Reference:
     * https://developer.arm.com/documentation/100720/0300
     * https://developer.arm.com/support/arm-security-updates/armv8-m-stack-sealing */
    uint32_t * p_main_stack_top = (uint32_t *) __Vectors[0];
    *p_main_stack_top = BSP_TZ_STACK_SEAL_VALUE;
#endif

#if !BSP_TZ_NONSECURE_BUILD

    /* VTOR is in undefined state out of RESET:
     * https://developer.arm.com/documentation/100235/0004/the-cortex-m33-peripherals/system-control-block/system-control-block-registers-summary?lang=en.
     * Set the Secure/Non-Secure VTOR to the vector table address based on the build. This is skipped for non-secure
     * projects because SCB_NS->VTOR is set by the secure project before the non-secure project runs. */
    SCB->VTOR = (uint32_t) &__Vectors;
#endif

#if !BSP_TZ_CFG_SKIP_INIT
 #if BSP_FEATURE_BSP_VBATT_HAS_VBTCR1_BPWSWSTP

    /* Unlock VBTCR1 register. */
    R_SYSTEM->PRCR = (uint16_t) BSP_PRV_PRCR_PRC1_UNLOCK;

    /* The VBTCR1.BPWSWSTP must be set after reset on MCUs that have VBTCR1.BPWSWSTP. Reference section 11.2.1
     * "VBATT Control Register 1 (VBTCR1)" and Figure 11.2 "Setting flow of the VBTCR1.BPWSWSTP bit" in the RA4M1 manual
     * R01UM0007EU0110. This must be done before bsp_clock_init because LOCOCR, LOCOUTCR, SOSCCR, and SOMCR cannot
     * be accessed until VBTSR.VBTRVLD is set. */
    R_SYSTEM->VBTCR1 = 1U;
    FSP_HARDWARE_REGISTER_WAIT(R_SYSTEM->VBTSR_b.VBTRVLD, 1U);

    /* Lock VBTCR1 register. */
    R_SYSTEM->PRCR = (uint16_t) BSP_PRV_PRCR_LOCK;
 #endif
#endif

#if BSP_FEATURE_TFU_SUPPORTED
    R_BSP_MODULE_START(FSP_IP_TFU, 0U);
#endif

#if BSP_CFG_EARLY_INIT

    /* Initialize uninitialized BSP variables early for use in R_BSP_WarmStart. */
    bsp_init_uninitialized_vars();
#endif

    /* Call pre clock initialization hook. */
    R_BSP_WarmStart(BSP_WARM_START_RESET);

#if BSP_TZ_CFG_SKIP_INIT

    /* Initialize clock variables to be used with R_BSP_SoftwareDelay. */
    bsp_clock_freq_var_init();
#else

    /* Configure system clocks. */
    bsp_clock_init();

 #if BSP_FEATURE_BSP_RESET_TRNG

    /* To prevent an undesired current draw, this MCU requires a reset
     * of the TRNG circuit after the clocks are initialized */

    bsp_reset_trng_circuit();
 #endif
#endif

#if BSP_FEATURE_BSP_HAS_GRAPHICS_DOMAIN

    /* Turn on graphics power domain.
     * This requires MOCO to be enabled, but MOCO is always enabled after bsp_clock_init(). */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_OM_LPC_BATT);
    R_SYSTEM->PDCTRGD = 0;
    (void) R_SYSTEM->PDCTRGD;
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_OM_LPC_BATT);
#endif

    /* Call post clock initialization hook. */
    R_BSP_WarmStart(BSP_WARM_START_POST_CLOCK);

#if BSP_FEATURE_BSP_HAS_SP_MON

    /* Disable MSP monitoring  */
    R_MPU_SPMON->SP[0].CTL = 0;

    /* Setup NMI interrupt  */
    R_MPU_SPMON->SP[0].OAD = BSP_STACK_POINTER_MONITOR_NMI_ON_DETECTION;

    /* Setup start address  */
    R_MPU_SPMON->SP[0].SA = BSP_PRV_STACK_LIMIT;

    /* Setup end address  */
    R_MPU_SPMON->SP[0].EA = BSP_PRV_STACK_TOP;

    /* Set SPEEN bit to enable NMI on stack monitor exception. NMIER bits cannot be cleared after reset, so no need
     * to read-modify-write. */
    R_ICU->NMIER = R_ICU_NMIER_SPEEN_Msk;

    /* Enable MSP monitoring  */
    R_MPU_SPMON->SP[0].CTL = 1U;
#endif

#if BSP_FEATURE_TZ_HAS_TRUSTZONE
 #if 33U == __CORTEX_M

    /* Use CM33 stack monitor. */
    __set_MSPLIM(BSP_PRV_STACK_LIMIT);
 #else

    /* CM85 stack monitor not yet supported. */
 #endif
#endif

#if BSP_CFG_C_RUNTIME_INIT

    /* Initialize C runtime environment. */
    /* Zero out BSS */
 #if defined(__ARMCC_VERSION)
    memset((uint8_t *) &Image$$BSS$$ZI$$Base, 0U, (uint32_t) &Image$$BSS$$ZI$$Length);
 #elif defined(__GNUC__)
    memset(&__bss_start__, 0U, ((uint32_t) &__bss_end__ - (uint32_t) &__bss_start__));
 #elif defined(__ICCARM__)
    memset((uint32_t *) __section_begin(".bss"), 0U, (uint32_t) __section_size(".bss"));
 #endif

    /* Copy initialized RAM data from ROM to RAM. */
 #if defined(__ARMCC_VERSION)
    memcpy((uint8_t *) &Image$$DATA$$Base, (uint8_t *) &Load$$DATA$$Base, (uint32_t) &Image$$DATA$$Length);
  #if BSP_FEATURE_BSP_HAS_DTCM == 1
    memcpy((uint8_t *) &Image$$DTCM_DATA_INIT$$Base,
           (uint8_t *) &Load$$DTCM_DATA_INIT$$Base,
           (uint32_t) &Image$$DTCM_DATA_INIT$$Length);
  #endif
 #elif defined(__GNUC__)
    memcpy(&__data_start__, &__etext, ((uint32_t) &__data_end__ - (uint32_t) &__data_start__));
  #if BSP_FEATURE_BSP_HAS_DTCM == 1
    memcpy(&__dtcm_data_start__, &__dtcm_data_init_start,
           ((uint32_t) &__dtcm_data_end__ - (uint32_t) &__dtcm_data_start__));
  #endif
 #elif defined(__ICCARM__)
    memcpy((uint32_t *) __section_begin(".data"), (uint32_t *) __section_begin(".data_init"),
           (uint32_t) __section_size(".data"));

    /* Copy functions to be executed from RAM. */
  #pragma section=".code_in_ram"
  #pragma section=".code_in_ram_init"
    memcpy((uint32_t *) __section_begin(".code_in_ram"),
           (uint32_t *) __section_begin(".code_in_ram_init"),
           (uint32_t) __section_size(".code_in_ram"));

    /* Copy main thread TLS to RAM. */
  #pragma section="__DLIB_PERTHREAD_init"
  #pragma section="__DLIB_PERTHREAD"
    memcpy((uint32_t *) __section_begin("__DLIB_PERTHREAD"), (uint32_t *) __section_begin("__DLIB_PERTHREAD_init"),
           (uint32_t) __section_size("__DLIB_PERTHREAD_init"));
  #if BSP_FEATURE_BSP_HAS_DTCM == 1
    memcpy((uint32_t *) __section_begin(".dtcm_data"),
           (uint32_t *) __section_begin(".dtcm_data_init"),
           (uint32_t) __section_size(".dtcm_data"));
  #endif
 #endif

    /* Initialize static constructors */
 #if defined(__ARMCC_VERSION)
    int32_t count = Image$$INIT_ARRAY$$Limit - Image$$INIT_ARRAY$$Base;
    for (int32_t i = 0; i < count; i++)
    {
        void (* p_init_func)(void) =
            (void (*)(void))((uint32_t) &Image$$INIT_ARRAY$$Base + (uint32_t) Image$$INIT_ARRAY$$Base[i]);
        p_init_func();
    }

 #elif defined(__GNUC__)
    int32_t count = __init_array_end - __init_array_start;
    for (int32_t i = 0; i < count; i++)
    {
        __init_array_start[i]();
    }

 #elif defined(__ICCARM__)
    void const * pibase = __section_begin("SHT$$PREINIT_ARRAY");
    void const * ilimit = __section_end("SHT$$INIT_ARRAY");
    __call_ctors(pibase, ilimit);
 #endif
#endif                                 // BSP_CFG_C_RUNTIME_INIT

    /* Initialize SystemCoreClock variable. */
    SystemCoreClockUpdate();

#if !BSP_CFG_PFS_PROTECT
 #if BSP_TZ_SECURE_BUILD || (BSP_CFG_MCU_PART_SERIES == 8)
    R_PMISC->PWPRS = 0;                              ///< Clear BOWI bit - writing to PFSWE bit enabled
    R_PMISC->PWPRS = 1U << BSP_IO_PWPR_PFSWE_OFFSET; ///< Set PFSWE bit - writing to PFS register enabled
 #else
    R_PMISC->PWPR = 0;                               ///< Clear BOWI bit - writing to PFSWE bit enabled
    R_PMISC->PWPR = 1U << BSP_IO_PWPR_PFSWE_OFFSET;  ///< Set PFSWE bit - writing to PFS register enabled
 #endif
#endif

#if FSP_PRIV_TZ_USE_SECURE_REGS

    /* Ensure that the PMSAR registers are reset (Soft reset does not reset PMSAR). */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_SAR);

    for (uint32_t i = 0; i < 9; i++)
    {
        R_PMISC->PMSAR[i].PMSAR = UINT16_MAX;
    }
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_SAR);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Initialize security features. */
    R_BSP_SecurityInit();
#endif

    /* Call Post C runtime initialization hook. */
    R_BSP_WarmStart(BSP_WARM_START_POST_C);

    /* Initialize ELC events that will be used to trigger NVIC interrupts. */
    bsp_irq_cfg();

    /* Call any BSP specific code. No arguments are needed so NULL is sent. */
    bsp_init(NULL);
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.
 * This function is declared as a weak symbol higher up in this file because it is meant to be overridden by a user
 * implemented version. One of the main uses for this function is to call functional safety code during the startup
 * process. To use this function just copy this function into your own code and modify it to meet your needs.
 *
 * @param[in]  event    Where the code currently is in the start up process
 **********************************************************************************************************************/
void R_BSP_WarmStart (bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
        /* C runtime environment has not been setup so you cannot use globals. System clocks are not setup. */
    }

    if (BSP_WARM_START_POST_CLOCK == event)
    {
        /* C runtime environment has not been setup so you cannot use globals. Clocks have been initialized. */
    }
    else if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment, system clocks, and pins are all setup. */
    }
    else
    {
        /* Do nothing */
    }
}

/*******************************************************************************************************************//**
 * Disable TRNG circuit to prevent unnecessary current draw which may otherwise occur when the Crypto module
 * is not in use.
 **********************************************************************************************************************/
#if BSP_FEATURE_BSP_RESET_TRNG
static void bsp_reset_trng_circuit (void)
{
    volatile uint8_t read_port = 0U;
    FSP_PARAMETER_NOT_USED(read_port); /// Prevent compiler 'unused' warning

    /* Release register protection for low power modes (per RA2A1 User's Manual (R01UH0888EJ0100) Figure 11.13 "Example
     * of initial setting flow for an unused circuit") */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_OM_LPC_BATT);

    /* Enable TRNG function (disable stop function) */
 #if BSP_FEATURE_BSP_HAS_SCE_ON_RA2
    R_BSP_MODULE_START(FSP_IP_TRNG, 0); ///< TRNG Module Stop needs to be started/stopped for RA2 series.
 #elif BSP_FEATURE_BSP_HAS_SCE5
    R_BSP_MODULE_START(FSP_IP_SCE, 0);  ///< TRNG Module Stop needs to be started/stopped for RA4 series.
 #else
  #error "BSP_FEATURE_BSP_RESET_TRNG is defined but not handled."
 #endif

    /* Wait for at least 3 PCLKB cycles */
    read_port = R_PFS->PORT[0].PIN[0].PmnPFS_b.PODR;
    read_port = R_PFS->PORT[0].PIN[0].PmnPFS_b.PODR;
    read_port = R_PFS->PORT[0].PIN[0].PmnPFS_b.PODR;

    /* Disable TRNG function */
 #if BSP_FEATURE_BSP_HAS_SCE_ON_RA2
    R_BSP_MODULE_STOP(FSP_IP_TRNG, 0); ///< TRNG Module Stop needs to be started/stopped for RA2 series.
 #elif BSP_FEATURE_BSP_HAS_SCE5
    R_BSP_MODULE_STOP(FSP_IP_SCE, 0);  ///< TRNG Module Stop needs to be started/stopped for RA4 series.
 #else
  #error "BSP_FEATURE_BSP_RESET_TRNG is defined but not handled."
 #endif

    /* Reapply register protection for low power modes (per RA2A1 User's Manual (R01UH0888EJ0100) Figure 11.13 "Example
     * of initial setting flow for an unused circuit") */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_OM_LPC_BATT);
}

#endif

#if BSP_CFG_EARLY_INIT

/*******************************************************************************************************************//**
 * Initialize BSP variables not handled by C runtime startup.
 **********************************************************************************************************************/
static void bsp_init_uninitialized_vars (void)
{
    g_protect_pfswe_counter = 0;

    extern volatile uint16_t g_protect_counters[];
    for (uint32_t i = 0; i < 4; i++)
    {
        g_protect_counters[i] = 0;
    }

    extern bsp_grp_irq_cb_t g_bsp_group_irq_sources[];
    for (uint32_t i = 0; i < 16; i++)
    {
        g_bsp_group_irq_sources[i] = 0;
    }

 #if BSP_CFG_EARLY_INIT

    /* Set SystemCoreClock to MOCO */
    SystemCoreClock = BSP_MOCO_HZ;
 #endif
}

#endif

/** @} (end addtogroup BSP_MCU) */
