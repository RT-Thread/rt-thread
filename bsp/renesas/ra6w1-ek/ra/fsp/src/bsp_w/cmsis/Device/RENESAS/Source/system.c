/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Mask to select CP bits( 0xF00000 ) */
#define CP_MASK                    (0xFU << 20)

/* Key code for writing PRCR register. */
#if defined(__ICCARM__)
 #ifndef __Vectors
  #define __Vectors                __vector_table
 #endif
#endif
#define BSP_PRV_STACK_LIMIT        ((uint32_t) __Vectors[0] - BSP_CFG_STACK_MAIN_BYTES)
#define BSP_TZ_STACK_SEAL_VALUE    (0xFEF5EDA5)

#if defined(GPREG_DEBUG_REG_ETM_TRACE_MAP_ON_PINS_EN_Msk)
 #define ETM_TRACE_ENABLE          (GPREG->DEBUG_REG_b.ETM_TRACE_MAP_ON_PINS_EN)
#elif defined(GPREG_DEBUG_REG_ETM_ITM_TRACE_MAP_ON_PINS_EN_Msk)
 #define ETM_TRACE_ENABLE          (GPREG->DEBUG_REG_b.ETM_ITM_TRACE_MAP_ON_PINS_EN)
#endif

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/** System Clock Frequency (Core Clock) */
uint32_t SystemCoreClock BSP_SECTION_EARLY_INIT;
uint32_t g_bsp_reset_stat_reg BSP_PLACE_IN_SECTION(BSP_SECTION_NOINIT);

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

extern void  * __VECTOR_TABLE[];
extern uint8_t g_main_stack[];

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

__STATIC_FORCEINLINE void bsp_debugger_enable(void);
__STATIC_FORCEINLINE void bsp_clock_div_early_init(void);
__STATIC_FORCEINLINE void bsp_etm_trace_setup(void);
static void               SystemRuntimeInit(const uint32_t external);

#if !BSP_TZ_NONSECURE_BUILD
__STATIC_FORCEINLINE void bsp_sys_force_active(void);
__STATIC_FORCEINLINE void bsp_power_domains_early_init(void);
__STATIC_FORCEINLINE void bsp_mem_retain_early_init(void);
static void               bsp_rails_early_init(void);

#endif

BSP_WEAK_REFERENCE __NO_RETURN void _exit(int __status);

/*******************************************************************************************************************//**
 * Initialize the MCU and the runtime environment.
 **********************************************************************************************************************/
void SystemInit (void)
{
    /** In Trustzone enabled project the g_bsp_reset_stat_reg is updated exclusively from the S application,
     * which is executed first. The g_bsp_reset_stat_reg status can be read by NS application by calling the
     * R_BSP_ResetStatusGet()
     */
#if !BSP_TZ_NONSECURE_BUILD
    g_bsp_reset_stat_reg    = CRG_TOP->RESET_STAT_REG;
    CRG_TOP->RESET_STAT_REG = 0;
#endif

#if __FPU_USED

    /* Enable the FPU only when it is used.
     * Code taken from Section 7.1, Cortex-M4 TRM (DDI0439C) */

    /* Set bits 20-23 (CP10 and CP11) to enable FPU. */
    SCB->CPACR = (uint32_t) CP_MASK;

    /* ASPEN = 1 ==> Hardware should automatically preserve floating point
     * context on exception entry and restore on exception return.
     * LSPEN = 1 ==> Enable lazy context save of FP state. */
    FPU->FPCCR |= (FPU_FPCCR_ASPEN_Msk | FPU_FPCCR_LSPEN_Msk);
#endif

#if BSP_TZ_SECURE_BUILD

    /* Seal the main stack for secure projects. Reference:
     * https://developer.arm.com/documentation/100720/0300
     * https://developer.arm.com/support/arm-security-updates/armv8-m-stack-sealing */
    uint32_t * p_main_stack_top = (uint32_t *) __Vectors[0];
    *p_main_stack_top = BSP_TZ_STACK_SEAL_VALUE;
#endif

#if BSP_CFG_EARLY_INIT

    /* Initialize uninitialized BSP variables early for use in R_BSP_WarmStart. */
    bsp_init_uninitialized_vars();
#endif

    bsp_prv_halt_implementation_early_set();

    /* TODO: Remove guard when device info is ready for other RAfW boards as well. */
#if BSP_MCU_GROUP_RA6W1

    /* Populate device information attributes. */
    BSP_CHECK_DEBUG(bsp_device_info_init());
#endif

    bsp_debugger_enable();

    /* Call pre clock initialization hook. */
    R_BSP_WarmStart(BSP_WARM_START_RESET);

    /*
     * Setup the dividers for HCLK and PCLK defined by the user.
     */
    bsp_clock_div_early_init();

#if 0

    // TODO: Identify whether this code will be executed. If yes, then implement this function properly
    // for all RAfW devices.

    /*
     * Check that the firmware and the chip that it runs on are compatible with each other.
     */
    BSP_CHECK_DEBUG(bsp_device_info_compatibility_check());
#endif

    SystemRuntimeInit(0);
#if !BSP_FEATURE_FLASH_IS_INTERNAL

    /* TODO: Consider case where we also have some external PSRAM, that
     * has not been properly setup to be transparent for reads/writes.
     * In this case RAM variables present in that memory are never initialized,
     * or a BusFault occurs here.
     */
    SystemRuntimeInit(1);
#endif

#if !BSP_TZ_NONSECURE_BUILD
    bsp_sys_force_active();

    bsp_rails_early_init();

    bsp_power_domains_early_init();

    bsp_mem_retain_early_init();
#endif

    bsp_etm_trace_setup();

#if BSP_TZ_CFG_SKIP_INIT

    /* Initialize clock variables to be used with R_BSP_SoftwareDelay. */
    bsp_clock_freq_var_init();
#else
 #ifdef BSP_PRV_TCS_HANDLING_READY

    /* Apply TCS values before initializing clocks */
    bsp_prv_tcs_init();
 #endif

    /* Configure system clocks. */
    bsp_clock_init();
#endif

    /* Call post clock initialization hook. */
    R_BSP_WarmStart(BSP_WARM_START_POST_CLOCK);

#if BSP_FEATURE_TZ_HAS_TRUSTZONE
 #if 33U == __CORTEX_M

    /* Use CM33 stack monitor. */
    __set_MSPLIM(BSP_PRV_STACK_LIMIT);
 #else
 #endif
#endif

#if BSP_TZ_SECURE_BUILD

    /* Initialize security features. */
    R_BSP_SecurityInit();
#endif

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
    SystemCoreClock = BSP_RCLP_HZ;
 #endif
}

#endif

/*******************************************************************************************************************//**
 * Fallback weak implemenation of _exit(), which just hangs.
 **********************************************************************************************************************/
void _exit (int __status)
{
    FSP_PARAMETER_NOT_USED(__status);
    while (1)
    {
        ;
    }
}

#if defined(__GNUC__)

// TIN_HACK_WIFI
 #ifdef BSP_MCU_GROUP_RA6W1
BSP_WEAK_REFERENCE extern int _read(int fd, char * ptr, int len);
BSP_WEAK_REFERENCE extern int _write(int fd, char * ptr, int len);

/*******************************************************************************************************************//**
 * Stub to override _read(), to silence a link warning when using recent gcc
 **********************************************************************************************************************/
BSP_WEAK_REFERENCE int _read (int fd, char * ptr, int len)
{
    FSP_PARAMETER_NOT_USED(fd);
    FSP_PARAMETER_NOT_USED(ptr);
    FSP_PARAMETER_NOT_USED(len);

    return -1;
}

/*******************************************************************************************************************//**
 * Stub to override _write(), to silence a link warning when using recent gcc
 **********************************************************************************************************************/
BSP_WEAK_REFERENCE int _write (int fd, char * ptr, int len)
{
    FSP_PARAMETER_NOT_USED(fd);
    FSP_PARAMETER_NOT_USED(ptr);
    FSP_PARAMETER_NOT_USED(len);

    return -1;
}

 #else
extern _ssize_t _read_r(struct _reent * _reent, int _fd, void * _buff, size_t _cnt);

/*******************************************************************************************************************//**
 * Stub to override _read_r(), to silence a link warning when using recent gcc
 **********************************************************************************************************************/
_ssize_t _read_r (struct _reent * _reent, int _fd, void * _buff, size_t _cnt)
{
    FSP_PARAMETER_NOT_USED(_reent);
    FSP_PARAMETER_NOT_USED(_fd);
    FSP_PARAMETER_NOT_USED(_buff);
    FSP_PARAMETER_NOT_USED(_cnt);

    return -1;
}

 #endif

#if 0
extern _off_t _lseek_r(struct _reent * _reent, int _fdes, _off_t _off, int _w);
extern int    _kill_r(void * _reent, int _pid, int _signal);
extern int    _getpid_r(void * _reent);
extern int    _gettimeofday_r(void * _reent, void * _tp, void * _tzp);

 #if BSP_MCU_GROUP_RA6W1               // TIN-TODO: All these are required due to the printfs inside RA6W1 BSP. Are printfs accepted at BSP level?

struct stat;

BSP_WEAK_REFERENCE extern int _open_r(struct _reent * _reent, const char * _path, int _flag, int _m);
BSP_WEAK_REFERENCE extern int _fstat_r(struct _reent * _reent, int _fd, struct stat * _buff);
BSP_WEAK_REFERENCE extern int _isatty_r(struct _reent * _reent, int _fd);
BSP_WEAK_REFERENCE extern int _close_r(struct _reent * _reent, int _fd);
BSP_WEAK_REFERENCE extern int _link_r(struct _reent * _reent, const char * _oldpath, const char * _newpath);
BSP_WEAK_REFERENCE extern int _unlink_r(struct _reent * _reent, const char * _path);

 #endif

/*******************************************************************************************************************//**
 * Stub to override _lseek_r(), to silence a link warning when using recent gcc
 **********************************************************************************************************************/
_off_t _lseek_r (struct _reent * _reent, int _fdes, _off_t _off, int _w)
{
    FSP_PARAMETER_NOT_USED(_reent);
    FSP_PARAMETER_NOT_USED(_fdes);
    FSP_PARAMETER_NOT_USED(_off);
    FSP_PARAMETER_NOT_USED(_w);

    return -1;
}

/*******************************************************************************************************************//**
 * Stub to override _kill_r(), to silence a link warning when using recent gcc
 **********************************************************************************************************************/
int _kill_r (void * _reent, int _pid, int _signal)
{
    FSP_PARAMETER_NOT_USED(_reent);
    FSP_PARAMETER_NOT_USED(_pid);
    FSP_PARAMETER_NOT_USED(_signal);

    return -1;
}

/*******************************************************************************************************************//**
 * Stub to override _getpid_r(), to silence a link warning when using recent gcc
 **********************************************************************************************************************/
int _getpid_r (void * _reent)
{
    FSP_PARAMETER_NOT_USED(_reent);

    return -1;
}

/*******************************************************************************************************************//**
 * Stub to override _gettimeofday_r(), to silence a link warning when using recent gcc
 **********************************************************************************************************************/
int _gettimeofday_r (void * _reent, void * _tp, void * _tzp)
{
    FSP_PARAMETER_NOT_USED(_reent);
    FSP_PARAMETER_NOT_USED(_tp);
    FSP_PARAMETER_NOT_USED(_tzp);

    return -1;
}

 #if BSP_MCU_GROUP_RA6W1               // TIN-TODO: All these are required due to the printfs inside RA6W1 BSP. Are printfs accepted at BSP level?

/*******************************************************************************************************************//**
 * Stub to override _open_r(), to silence a link warning when using recent gcc
 **********************************************************************************************************************/
int _open_r (struct _reent * _reent, const char * _path, int _flag, int _m)
{
    FSP_PARAMETER_NOT_USED(_reent);
    FSP_PARAMETER_NOT_USED(_path);
    FSP_PARAMETER_NOT_USED(_flag);
    FSP_PARAMETER_NOT_USED(_m);

    return -1;
}

/*******************************************************************************************************************//**
 * Stub to override _fstat_r(), to silence a link warning when using recent gcc
 **********************************************************************************************************************/
int _fstat_r (struct _reent * _reent, int _fd, struct stat * _buff)
{
    FSP_PARAMETER_NOT_USED(_reent);
    FSP_PARAMETER_NOT_USED(_fd);
    FSP_PARAMETER_NOT_USED(_buff);

    return -1;
}

/*******************************************************************************************************************//**
 * Stub to override _isatty_r(), to silence a link warning when using recent gcc
 **********************************************************************************************************************/
int _isatty_r (struct _reent * _reent, int _fd)
{
    FSP_PARAMETER_NOT_USED(_reent);
    FSP_PARAMETER_NOT_USED(_fd);

    return -1;
}

/*******************************************************************************************************************//**
 * Stub to override _close_r(), to silence a link warning when using recent gcc
 **********************************************************************************************************************/
int _close_r (struct _reent * _reent, int _fd)
{
    FSP_PARAMETER_NOT_USED(_reent);
    FSP_PARAMETER_NOT_USED(_fd);

    return -1;
}

/*******************************************************************************************************************//**
 * Stub to override _link_r(), to silence a link warning when using recent gcc
 **********************************************************************************************************************/
int _link_r (struct _reent * _reent, const char * _oldpath, const char * _newpath)
{
    FSP_PARAMETER_NOT_USED(_reent);
    FSP_PARAMETER_NOT_USED(_oldpath);
    FSP_PARAMETER_NOT_USED(_newpath);

    return -1;
}

/*******************************************************************************************************************//**
 * Stub to override _unlink_r(), to silence a link warning when using recent gcc
 **********************************************************************************************************************/
int _unlink_r (struct _reent * _reent, const char * _path)
{
    FSP_PARAMETER_NOT_USED(_reent);
    FSP_PARAMETER_NOT_USED(_path);

    return -1;
}

 #endif
#endif
#endif

#if defined(__GNUC__) || defined(__ICCARM__)
__STATIC_FORCEINLINE void bsp_debugger_enable (void)
{
 #if BSP_CFG_DEBUGGER_ENABLE
    CRG_TOP->SYS_CTRL_REG |= CRG_TOP_SYS_CTRL_REG_DEBUGGER_ENABLE_Msk;
 #endif

 #if (BSP_CFG_CMAC_DEBUGGER_ENABLE)
    CRG_TOP->SYS_CTRL_REG |= CRG_TOP_SYS_CTRL_REG_CMAC_DEBUGGER_ENABLE_Msk;
 #endif
}

__STATIC_FORCEINLINE void bsp_clock_div_early_init (void)
{
    uint32_t val = CRG_TOP->CLK_AMBA_REG;

 #if BSP_FEATURE_CGC_HAS_HCLK_DIV
    FSP_REG_VAR_FIELD_SET(CRG_TOP, CLK_AMBA_REG, HCLK_DIV, val, BSP_CFG_HCLK_DIV);
 #endif

 #if BSP_FEATURE_CGC_HAS_PCLK_DIV
    FSP_REG_VAR_FIELD_SET(CRG_TOP, CLK_AMBA_REG, PCLK_DIV, val, BSP_CFG_PCLK_DIV);
 #endif

    CRG_TOP->CLK_AMBA_REG = val;
}

 #if !BSP_TZ_NONSECURE_BUILD
__STATIC_FORCEINLINE void bsp_sys_force_active (void)
{
  #if defined(CRG_TOP_PMU_CTRL_REG_SYS_SLEEP_Pos)
    CRG_TOP->PMU_CTRL_REG_b.SYS_SLEEP = 0;
  #endif
}

static void bsp_rails_early_init (void)
{
  #if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6B2 || BSP_MCU_GROUP_RA6U1

    /* XXX Setup rails based on HW recommendations (unchanged for RA6B1/RA6U1) */
    PMU_ANA->POWER_CTRL_REG_b.V18_ENABLE = 0x1;
    PMU_ANA->POWER_CTRL_REG_b.VDD_ENABLE = 0x2;

   #ifndef BSP_MCU_GROUP_RA6B2
    PMU_ANA->POWER_CTRL_REG_b.V10_ENABLE     = 0x2;
    PMU_ANA->POWER_CTRL_REG_b.LDO_ANA_ENABLE = 0x1;
   #endif

    /* V18EXT is not enabled since it is tied to a HW issue where the current required by all rails
     * cannot be provided and the device crashes. The rail is only used by the external QSPI memory,
     * and should only be enabled when that is used.
     */
  #elif BSP_MCU_GROUP_RA6W1

    /**
     * TIN-TODO: Identify whether these are always needed or if we should only enable them for PLL.
     * There is an issue with the external flash when the PLL clock is selected in Tin and the
     * workaround to the HW bug is to increase the current provided to the pads.
     * TIN-TODO: It is unclear why the clock for the DMA is enabled as well.
     *//* Set QSPI pads drive current to 8 mA. Default was 2 mA. */
    OQSPIF->OQSPIF_GP_REG_b.OSPIC_PADS_DRV = 2;

    /* The following is required for BA. */
    CRG_TOP->CLK_AMBA_REG_b.GEN_DMA_ENABLE = 1;
  #endif
}

__STATIC_FORCEINLINE void bsp_power_domains_early_init (void)
{
/* TIN-TODO: Identify if similar approach to other RAfW devices should be used,
 * where all domains are enabled at startup.
 */
  #if !BSP_MCU_GROUP_RA6W1
    bsp_pd_init();

    /* Enable all power domains during startup. */
    for (uint8_t pd = 0; pd < BSP_PD_ID_COUNT; pd++)
    {
        bsp_pd_enable(pd);
    }
  #endif
}

__STATIC_FORCEINLINE void bsp_mem_retain_early_init (void)
{
    // TIN-TODO: Identify whether RETAIN_MEM_CTRL_REG should be written here to enable retainment of cache.
  #if !BSP_MCU_GROUP_RA6W1
    CRG_TOP->RAM_RETAIN_REG = UINT32_MAX;
  #endif
}

 #endif

__STATIC_FORCEINLINE void bsp_etm_trace_setup (void)
{
    /* TIN-TODO: Tin appears to have ETM support but the datasheet does not define any dedicated pins
     * for the trace signals.
     */
 #if !BSP_MCU_GROUP_RA6W1
    if (!ETM_TRACE_ENABLE)
    {
        /* No ETM trace required. Nothing to do. */
        return;
    }

    uint32_t p0_etm_pins = 0;

    p0_etm_pins |= (1 << BSP_IO_PORT_00_PIN_19) | (1 << BSP_IO_PORT_00_PIN_20); /* TRACE_CLK & TRACE_DATA[0] */

    /* Get trace port size from Current Parallel Port Size Register (CSPSR) */
    uint32_t trace_port_width = TPIU->CSPSR;
    if (trace_port_width > 1)
    {
        p0_etm_pins |= (1 << BSP_IO_PORT_00_PIN_21); /* TRACE_DATA[1] */
    }

    if (trace_port_width == 8)
    {
        p0_etm_pins |= (1 << BSP_IO_PORT_00_PIN_22); /* TRACE_DATA[2] */
        p0_etm_pins |= (1 << BSP_IO_PORT_00_PIN_23); /* TRACE_DATA[3] */
    }
    CRG_TOP->P0_SET_PAD_LATCH_REG = p0_etm_pins;
 #endif
}

static void SystemRuntimeInit (const uint32_t external)
{
    /* Initialize C runtime environment. */
    for (uint32_t i = 0; i < g_init_info.zero_count; i++)
    {
        if (external == g_init_info.p_zero_list[i].type.external)
        {
            uint32_t size =
                ((uint32_t) g_init_info.p_zero_list[i].p_limit - (uint32_t) g_init_info.p_zero_list[i].p_base);

 #if defined(__ICCARM__)
            size /= sizeof(uint32_t);
            for (uint32_t it = 0; it < size; it++)
            {
                g_init_info.p_zero_list[i].p_base[it] = 0;
            }
 #else
            fast_memset(g_init_info.p_zero_list[i].p_base, 0, size);
 #endif
        }
    }

    for (uint32_t i = 0; i < g_init_info.copy_count; i++)
    {
        if (external == g_init_info.p_copy_list[i].type.external)
        {
            uint32_t size =
                ((uint32_t) g_init_info.p_copy_list[i].p_limit - (uint32_t) g_init_info.p_copy_list[i].p_base);

 #if defined(__ICCARM__)
            size /= sizeof(uint32_t);
            for (uint32_t it = 0; it < size; it++)
            {
                g_init_info.p_copy_list[i].p_base[it] = g_init_info.p_copy_list[i].p_load[it];
            }
 #else
            fast_memcpy(g_init_info.p_copy_list[i].p_base, g_init_info.p_copy_list[i].p_load, size);
 #endif
        }
    }
}

#endif

/** @} (end addtogroup BSP_MCU) */
