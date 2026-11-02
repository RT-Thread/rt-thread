/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_clocks.h"
#include "bsp_common.h"

#if BSP_TZ_NONSECURE_BUILD
 #include "bsp_guard.h"
#endif

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#if BSP_FEATURE_CGC_HAS_RCX_CONTROL
 #if defined(CRG_AON_AON_OSC_EN_REG_RCX_ENABLE_Msk)
  #define RCX()    CRG_AON->AON_OSC_EN_REG_b
 #else
  #define RCX()    CRG_AON->CLK_RCX_REG_b
 #endif
#endif

#if BSP_FEATURE_CGC_HAS_SOSC
 #if defined(CRG_AON_AON_OSC_EN_REG_XTAL32K_ENABLE_Msk)
  #define XTAL32K()    CRG_AON->AON_OSC_EN_REG_b
 #else
  #define XTAL32K()    CRG_AON->CLK_XTAL32K_REG_b
 #endif
#endif

/* The number of clocks is used to size the g_sys_clock_freq array. */
#define BSP_PRV_NUM_SOURCE_CLOCKS    ((uint8_t) BSP_CLOCKS_SOURCE_CLOCK_DIGITAL + 1U)

#define BSP_PRV_STABILIZE_PLL        (1)
#define BSP_PRV_STABILIZE_XTAL32M    (1)

#define NSEC_TO_CLK_CYCLES(nsec, clk_freq_hz)    ((((nsec) * ((clk_freq_hz) / 10000)) + 99999) / 100000)

#if BSP_FEATURE_CGC_HAS_POWER_LVL_REG
 #define BSP_PRV_1V2_FOR_PLL_ENABLE()            do {CRG_TOP->POWER_LVL_REG_b.V12_LEVEL = 2;} while (0)
#else
 #define BSP_PRV_1V2_FOR_PLL_ENABLE()            do {CRG_TOP->POWER_CTRL_REG_b.VDD_LEVEL = 3;} while (0)
#endif

#if BSP_FEATURE_CGC_HAS_RCHS_SPEEDS
 #define BSP_PRV_RUNNING_AT_RCHS_MASK    CRG_TOP_CLK_CTRL_REG_RUNNING_AT_RCHS_Msk
#else
 #define BSP_PRV_RUNNING_AT_RCHS_MASK    CRG_TOP_CLK_CTRL_REG_RUNNING_AT_RC32M_Msk
#endif

#if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1 || BSP_MCU_GROUP_RA6B2
 #define BSP_PRV_RUNNING_AT_XTALM        CRG_TOP->CLK_CTRL_REG_b.RUNNING_AT_XTAL32M
#elif BSP_MCU_GROUP_RA6W1 || BSP_MCU_GROUP_RA6W3
 #define BSP_PRV_RUNNING_AT_XTALM        CRG_TOP->CLK_CTRL_REG_b.RUNNING_AT_XTAL40M
#endif

#ifdef CRG_TOP_CLK_CTRL_REG_RUNNING_AT_PLL_Msk
 #define BSP_PRV_RUNNING_AT_PLL_MASK     CRG_TOP_CLK_CTRL_REG_RUNNING_AT_PLL_Msk
#else
 #define BSP_PRV_RUNNING_AT_PLL_MASK     CRG_TOP_CLK_CTRL_REG_RUNNING_AT_PLL96M_Msk
#endif

#if BSP_MCU_GROUP_RA6W1
 #define BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET (1)
#endif

/***********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

#if BSP_FEATURE_CGC_HAS_LP_CLOCK

/** Low Power Clock Frequency */
BSP_SECTION_EARLY_INIT uint32_t g_bsp_lp_clock;
#endif

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/* This array stores the clock frequency of each system clock. This section of RAM should not be initialized by the C
 * runtime environment. This is initialized and used in bsp_clock_init, which is called before the C runtime
 * environment is initialized. */
uint32_t g_clock_freq[BSP_PRV_NUM_SOURCE_CLOCKS]  BSP_PLACE_IN_SECTION(BSP_SECTION_NOINIT);

/***********************************************************************************************************************
 * Public Functions
 **********************************************************************************************************************/
#if BSP_FEATURE_CGC_HAS_RCHS
void bsp_clock_rchs_enable (bool enable)
{
    CRG_TOP->CLK_RCHS_REG_b.RCHS_ENABLE = enable;
}

bool bsp_clock_rchs_is_enabled (void)
{
    return CRG_TOP->CLK_RCHS_REG_b.RCHS_ENABLE;
}

#endif

#if BSP_FEATURE_CGC_HAS_RCLP
void bsp_clock_rclp_enable (bool enable)
{
    CRG_TOP->CLK_RCLP_REG_b.RCLP_DISABLE = !enable;
}

bool bsp_clock_rclp_is_enabled (void)
{
    return !CRG_TOP->CLK_RCLP_REG_b.RCLP_DISABLE;
}

#endif

#if BSP_FEATURE_CGC_HAS_RCX_CONTROL
void bsp_clock_rcx_enable (bool enable)
{
    RCX().RCX_ENABLE = enable;
}

#endif

#if BSP_FEATURE_CGC_HAS_RCX
bool bsp_clock_rcx_is_enabled (void)
{
 #if BSP_FEATURE_CGC_HAS_RCX_CONTROL

    return RCX().RCX_ENABLE;
 #else

    return true;
 #endif
}

#endif

#if BSP_FEATURE_CGC_HAS_SOSC

void bsp_clock_xtalk_enable (bool enable)
{
    XTAL32K().XTAL32K_ENABLE = enable;
}

bool bsp_clock_xtalk_is_enabled (void)
{
    return XTAL32K().XTAL32K_ENABLE;
}

#endif

#if BSP_CLOCK_CFG_MAIN_OSC_POPULATED

static void bsp_prv_clock_xtalm_start (void)
{
    if (0 == BSP_PRV_RUNNING_AT_XTALM)
    {
 #if !BSP_MCU_GROUP_RA6W3              /* TODO: Workaround for OSPI XIP */
        BSP_CHECK_DEBUG(FSP_SUCCESS == bsp_clock_xtalm_preconditions_check());
 #endif

        bsp_clock_xtalm_enable(true);

 #if BSP_CLOCK_CFG_XTAL32M_STABILIZATION_USEC
        R_BSP_SoftwareDelay(BSP_CLOCK_CFG_XTAL32M_STABILIZATION_USEC, BSP_DELAY_UNITS_MICROSECONDS);
 #else
        while (false == bsp_clock_xtalm_is_settled())
        {
            /* Wait. */
        }
 #endif
    }
}

bool bsp_clock_xtalm_is_enabled (void)
{
 #if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1 || BSP_MCU_GROUP_RA6B2

    return XTAL32M->XTAL32M_ENABLE_REG &
           (XTAL32M_XTAL32M_ENABLE_REG_LDOXTAL_EN_Msk |
            XTAL32M_XTAL32M_ENABLE_REG_EN_XTAL_BIAS_Msk |
            XTAL32M_XTAL32M_ENABLE_REG_EN_XTAL_OSC_Msk);
 #elif BSP_MCU_GROUP_RA6W3

    return XTAL32M->XTAL40M_ENABLE_REG &
           (XTAL32M_XTAL40M_ENABLE_REG_LDOXTAL_EN_Msk |
            XTAL32M_XTAL40M_ENABLE_REG_EN_XTAL_BIAS_Msk |
            XTAL32M_XTAL40M_ENABLE_REG_EN_XTAL_OSC_Msk);
 #elif BSP_MCU_GROUP_RA6W1

    return CRG_COM->XTAL40M_CTRL_REG_b.XTAL40M_RDY;
 #endif
}

#endif                                 /* BSP_CLOCK_CFG_MAIN_OSC_POPULATED */

#if !BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET
static void bsp_prv_clock_set_hard_reset(void);

#endif

#if BSP_TZ_SECURE_BUILD

/* Callback used to notify the nonsecure project that the clock settings have changed. */
static bsp_clock_update_callback_t g_bsp_clock_update_callback = NULL;

/* Pointer to nonsecure memory to store the callback args. */
static bsp_clock_update_callback_args_t * gp_callback_memory = NULL;

/* Reentrant method of calling the clock_update_callback. */
static void r_bsp_clock_update_callback_call (bsp_clock_update_callback_t        p_callback,
                                              bsp_clock_update_callback_args_t * p_callback_args)
{
    /* Allocate memory for saving global callback args on the secure stack. */
    bsp_clock_update_callback_args_t callback_args;

    /* Save current info stored in callback memory. */
    callback_args = *gp_callback_memory;

    /* Write the callback args to the nonsecure callback memory. */
    *gp_callback_memory = *p_callback_args;

    /* Call the callback to notifiy ns project about clock changes. */
    p_callback(gp_callback_memory);

    /* Restore the info in callback memory. */
    *gp_callback_memory = callback_args;
}

/* Initialize the callback, callback memory and invoke the callback to ensure the nonsecure project has the correct clock settings. */
void r_bsp_clock_update_callback_set (bsp_clock_update_callback_t        p_callback,
                                      bsp_clock_update_callback_args_t * p_callback_memory)
{
    /* Store pointer to nonsecure callback memory. */
    gp_callback_memory = p_callback_memory;

    /* Store callback. */
    g_bsp_clock_update_callback = p_callback;

    /* Set callback args. */
    bsp_clock_update_callback_args_t callback_args =
    {
        .pll_freq = g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL]
    };

    /* Call the callback. */
    r_bsp_clock_update_callback_call(g_bsp_clock_update_callback, &callback_args);
}

#elif BSP_TZ_NONSECURE_BUILD && BSP_TZ_CFG_CGFSAR != 0xFFFFFFFFU

bsp_clock_update_callback_args_t g_callback_memory;
 #if BSP_TZ_SECURE_BUILD || BSP_TZ_NONSECURE_BUILD
  #if defined(__ARMCC_VERSION) || defined(__ICCARM__)
static void BSP_CMSE_NONSECURE_CALL g_bsp_clock_update_callback (bsp_clock_update_callback_args_t * p_callback_args)
  #elif defined(__GNUC__)

static BSP_CMSE_NONSECURE_CALL void g_bsp_clock_update_callback (bsp_clock_update_callback_args_t * p_callback_args)
  #endif

{
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL] = p_callback_args->pll_freq;

    /* Update the SystemCoreClock value based on the new g_sys_clock_freq settings. */
    SystemCoreClockUpdate();
}

 #endif
#endif

/*******************************************************************************************************************//**
 * @internal
 * @addtogroup BSP_MCU_PRV Internal BSP Documentation
 * @ingroup RENESAS_INTERNAL
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * Update SystemCoreClock variable based on current clock settings.
 **********************************************************************************************************************/
void SystemCoreClockUpdate (void)
{
    uint32_t clock_index = CRG_TOP->CLK_CTRL_REG_b.SYS_CLK_SEL;

    SystemCoreClock = g_clock_freq[clock_index] >> bsp_clock_ahb_div_get();
}

#if BSP_FEATURE_CGC_HAS_LP_CLOCK

/*******************************************************************************************************************//**
 * Update g_bsp_lp_clock variable based on current clock settings.
 **********************************************************************************************************************/
void R_BSP_LPClockUpdate (void)
{
    uint32_t clock_index = CRG_TOP->CLK_CTRL_REG_b.LP_CLK_SEL + BSP_CLOCKS_SOURCE_CLOCK_RCLP;

    g_bsp_lp_clock = g_clock_freq[clock_index];
}

#endif

#if BSP_FEATURE_CGC_HAS_RCHS_SPEEDS

/*******************************************************************************************************************//**
 * @brief Set the speed mode of the RCHS clock
 *
 * @param[in] speed  the speed mode to use
 **********************************************************************************************************************/
void bsp_clock_rchs_speed_set (bsp_clock_rchs_speed_t speed)
{
    uint32_t value = 0;
    uint32_t freq  = BSP_RCHS_HZ;
    FSP_CRITICAL_SECTION_DEFINE;

    if (BSP_CLOCK_RCHS_SPEED_64M == speed)
    {
        value = CRG_TOP_CLK_RCHS_REG_RCHS_SPEED_Msk;
        freq  = 2 * BSP_RCHS_HZ;
    }

    FSP_CRITICAL_SECTION_ENTER;
    FSP_REG_SET_MASKED(CRG_TOP, CLK_RCHS_REG, CRG_TOP_CLK_RCHS_REG_RCHS_SPEED_Msk, value);
    FSP_CRITICAL_SECTION_EXIT;

    R_BSP_SourceClockHzSet(FSP_PRIV_CLOCK_RCHS, freq);
}

#endif                                 /* BSP_FEATURE_CGC_HAS_RCHS_SPEEDS */

#if BSP_FEATURE_CGC_HAS_RCLP_SPEEDS

/*******************************************************************************************************************//**
 * @brief Set the speed mode of the RCLP clock
 *
 * @param[in] speed  the speed mode to use
 **********************************************************************************************************************/
void bsp_clock_rclp_speed_set (bsp_clock_rclp_speed_t speed)
{
    static const uint32_t mask = CRG_TOP_CLK_RCLP_REG_RCLP_LOW_SPEED_FORCE_Msk | CRG_AON_RCLP_TRIM_REG_RCLP_TRIM_Msk;
    uint32_t              value;
    uint32_t              freq = BSP_RCLP_HZ;
    FSP_CRITICAL_SECTION_DEFINE;

    if (BSP_CLOCK_RCLP_SPEED_512K == speed)
    {
        value = CRG_TOP_CLK_RCLP_REG_RCLP_HIGH_SPEED_FORCE_Msk;
    }
    else if (BSP_CLOCK_RCLP_SPEED_32K == speed)
    {
        value = CRG_TOP_CLK_RCLP_REG_RCLP_LOW_SPEED_FORCE_Msk;
        freq  = BSP_RCLP_LOW_SPEED_FREQ_HZ;
    }
    else
    {
        value = 0;
    }

    FSP_CRITICAL_SECTION_ENTER;
    FSP_REG_SET_MASKED(CRG_TOP, CLK_RCLP_REG, mask, value);
    FSP_CRITICAL_SECTION_EXIT;

    R_BSP_SourceClockHzSet(FSP_PRIV_CLOCK_RCLP, freq);
}

#endif                                 /* BSP_FEATURE_CGC_HAS_RCLP_SPEEDS */

/*******************************************************************************************************************//**
 * Set System clock.
 *
 * \param[in] clock The new system clock.
 *
 * @note If any one of the lp clocks is requested, this function changes the system clock to the currently selected lp
 *       clock (whichever that is).
 **********************************************************************************************************************/
void bsp_clock_sysclk_set (fsp_priv_source_clock_t clock)
{
#if BSP_FEATURE_CGC_HAS_XTALM_SWITCH
    if ((FSP_PRIV_CLOCK_XTALM == clock) && CRG_TOP->CLK_CTRL_REG_b.RUNNING_AT_RCHS)
    {
        CRG_TOP->CLK_SWITCH2XTAL_REG_b.SWITCH2XTAL = 1;
    }
    else
#endif
    {
#if BSP_FPGA
 #if BSP_PRV_PLL_SUPPORTED
        if (FSP_PRIV_CLOCK_PLL == clock)
        {
            bsp_clock_pll_enable(false);
            bsp_clock_pll_enable(true);
        }
 #endif
#endif
        uint32_t clock_index = clock > BSP_CLOCKS_SOURCE_CLOCK_PLL ? BSP_CLOCKS_SOURCE_CLOCK_RCLP : clock;
        FSP_CRITICAL_SECTION_DEFINE;
        FSP_CRITICAL_SECTION_ENTER;

        CRG_TOP->CLK_CTRL_REG_b.SYS_CLK_SEL = clock_index &
                                              (CRG_TOP_CLK_CTRL_REG_SYS_CLK_SEL_Msk >>
                                               CRG_TOP_CLK_CTRL_REG_SYS_CLK_SEL_Pos);
        FSP_CRITICAL_SECTION_EXIT;
    }

    /* Update the CMSIS core clock variable so that it reflects the new HCLK frequency. */
    SystemCoreClockUpdate();

    /* Wait until the switch is done! */
    switch (clock)
    {
#if BSP_CLOCK_CFG_MAIN_OSC_POPULATED
        case FSP_PRIV_CLOCK_XTALM:
        {
 #if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1
            while (!CRG_TOP->CLK_CTRL_REG_b.RUNNING_AT_XTAL32M)
 #elif BSP_MCU_GROUP_RA6W1 || BSP_MCU_GROUP_RA6W3
            while (!CRG_TOP->CLK_CTRL_REG_b.RUNNING_AT_XTAL40M)
 #endif
            {
            }

            return;
        }

 #if BSP_FEATURE_CGC_HAS_XTALM_DBLR
        case FSP_PRIV_CLOCK_XTALM_DBLR:
        {
  #if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1
            while (!CRG_TOP->CLK_CTRL_REG_b.RUNNING_AT_XTAL64M)
  #elif BSP_MCU_GROUP_RA6W3
            while (!CRG_TOP->CLK_CTRL_REG_b.RUNNING_AT_XTAL80M)
  #endif
            {
            }

            return;
        }
 #endif
#endif
#if BSP_FEATURE_CGC_HAS_RCHS
        case FSP_PRIV_CLOCK_RCHS:
        {
            while (!CRG_TOP->CLK_CTRL_REG_b.RUNNING_AT_RCHS)
            {
            }

            return;
        }
#endif
#if BSP_PRV_PLL_SUPPORTED
        case FSP_PRIV_CLOCK_PLL:
        {
 #if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1
            while (!CRG_TOP->CLK_CTRL_REG_b.RUNNING_AT_PLL)
 #elif BSP_MCU_GROUP_RA6W3
            while (!CRG_TOP->CLK_CTRL_REG_b.RUNNING_AT_PLL320M)
 #endif
            {
            }

            return;
        }
#endif

        case FSP_PRIV_CLOCK_RCLP:
#if BSP_FEATURE_CGC_ANY_LP_CLK_CAN_BE_SYS_CLK
 #if BSP_FEATURE_CGC_HAS_SOSC && BSP_CLOCK_CFG_SUBCLOCK_POPULATED
        case FSP_PRIV_CLOCK_XTALK:
 #endif
        case FSP_PRIV_CLOCK_RCX:
        case FSP_PRIV_CLOCK_DIGITAL:
        {
            /* Low-power clock */
            while (!CRG_TOP->CLK_CTRL_REG_b.RUNNING_AT_LP_CLK)
            {
            }
        }
#endif                                 /* BSP_FEATURE_CGC_ANY_LP_CLK_CAN_BE_SYS_CLK */

        default:
        {
            BSP_CHECK_DEBUG(0);
            break;
        }
    }
}

/*******************************************************************************************************************//**
 * Applies system core clock source and divider changes.
 *
 * @param[in] clock                    Desired system clock
 * @param[in] clk_amba_reg_div         Value to set in dividers of CLK_AMBA_REG register
 **********************************************************************************************************************/
void bsp_clock_set (fsp_priv_source_clock_t clock, uint32_t clk_amba_reg_div)
{
    /* Set dividers. */
    uint32_t clk_amba_reg_val = (CRG_TOP->CLK_AMBA_REG & ~BSP_PRV_CLK_AMBA_REG_DIV) |
                                (clk_amba_reg_div & BSP_PRV_CLK_AMBA_REG_DIV);

    CRG_TOP->CLK_AMBA_REG = clk_amba_reg_val;

    /* Set lp clock if needed. */
#if BSP_FEATURE_CGC_ANY_LP_CLK_CAN_BE_SYS_CLK
    if ((FSP_PRIV_CLOCK_RCLP == clock) || (FSP_PRIV_CLOCK_RCX == clock) ||
 #if BSP_FEATURE_CGC_HAS_SOSC
  #if BSP_CLOCK_CFG_SUBCLOCK_POPULATED
        (FSP_PRIV_CLOCK_XTALK == clock) ||
  #endif
 #endif
        (FSP_PRIV_CLOCK_DIGITAL == clock))
    {
        bsp_clock_lpclk_set(clock);
    }
#endif

    /* Set system clock. */
    bsp_clock_sysclk_set(clock);
}

#if !BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET

static void bsp_prv_clock_set_hard_reset (void)
{
    /* Set the system source clock */
 #if BSP_CLOCK_CFG_MAIN_OSC_POPULATED && (BSP_CLOCKS_SOURCE_CLOCK_XTALM == BSP_CFG_CLOCK_SOURCE)

    /* Nothing to do. Xtal32m has already been set as system clock in bsp_clock_init(). */
 #elif BSP_CLOCK_CFG_MAIN_OSC_POPULATED && BSP_FEATURE_CGC_HAS_XTALM_DBLR && \
    (BSP_CLOCKS_SOURCE_CLOCK_XTALM_DBLR == BSP_CFG_CLOCK_SOURCE)

    bsp_clock_xtalm_64m_output_enable(true);
 #elif (BSP_CLOCKS_SOURCE_CLOCK_RCHS == BSP_CFG_CLOCK_SOURCE)
  #if BSP_FEATURE_CGC_HAS_RCHS_SPEEDS && (BSP_RCHS_64M_SPEED_MODE == BSP_CFG_RCHS_FREQUENCY)
    BSP_CHECK_DEBUG(FSP_SUCCESS == bsp_clock_rchs_high_speed_preconditions_check());
  #endif
  #if BSP_CLOCK_CFG_MAIN_OSC_POPULATED
    bsp_clock_rchs_enable(true);
  #endif
 #elif BSP_PRV_PLL_SUPPORTED && (BSP_CLOCKS_SOURCE_CLOCK_PLL == BSP_CFG_CLOCK_SOURCE)
    bsp_clock_pll_enable(true);

  #if BSP_PRV_STABILIZE_PLL
    while (!bsp_clock_pll_is_locked())
    {
    }
  #endif

    /*
     * If ultra-fast wake-up mode is used, make sure that the startup state
     * machine is finished and all power regulation is in order.
     */
    while (0 == CRG_TOP->SYS_STAT_REG_b.POWER_IS_UP)
    {
        /* Wait. */
    }
 #endif                                /* BSP_CFG_CLOCK_SOURCE */

 #if BSP_FEATURE_CGC_HAS_RCHS_SPEEDS
  #if (BSP_CLOCKS_SOURCE_CLOCK_RCHS == BSP_CFG_CLOCK_SOURCE)
    bsp_clock_rchs_speed_set((bsp_clock_rchs_speed_t) BSP_CFG_RCHS_FREQUENCY);

    /* Switching to/from 64 MHz requires >100us for the RCHS to settle */
    R_BSP_SoftwareDelay(150, BSP_DELAY_UNITS_MICROSECONDS);
  #endif                               /* BSP_CFG_CLOCK_SOURCE */
 #endif                                /* BSP_FEATURE_CGC_HAS_RCHS_SPEEDS */

    bsp_clock_sysclk_set((fsp_priv_source_clock_t) BSP_CFG_CLOCK_SOURCE);

    /* Update the CMSIS core clock variable so that it reflects the new ICLK frequency. */
    SystemCoreClockUpdate();

    /* Clocks are now at requested frequencies. */
}

#endif

/*******************************************************************************************************************//**
 * Initializes variable to store system clock frequencies.
 **********************************************************************************************************************/
#if BSP_TZ_NONSECURE_BUILD
void bsp_clock_freq_var_init (void)
#else
static void bsp_clock_freq_var_init (void)
#endif
{
    memset(g_clock_freq, 0, sizeof(g_clock_freq));

    /* Initialize System Clock frequencies. */
#if BSP_FEATURE_CGC_HAS_RCHS
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_RCHS] = BSP_RCHS_HZ;
#endif

#if BSP_CLOCK_CFG_MAIN_OSC_POPULATED
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_XTALM] = BSP_CFG_XTALM_HZ;
 #if BSP_FEATURE_CGC_HAS_XTALM_DBLR
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_XTALM_DBLR] = 2 * BSP_CFG_XTALM_HZ;
 #endif
#endif

#if BSP_PRV_PLL_SUPPORTED
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_PLL] = BSP_PLL_FREQ_HZ;
#endif

#if BSP_FEATURE_CGC_HAS_RCLP
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_RCLP] = BSP_RCLP_HZ;
#endif

#if BSP_FEATURE_CGC_HAS_RCX
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_RCX] = BSP_RCX_HZ;
#endif

#if BSP_FEATURE_CGC_HAS_SOSC && BSP_CLOCK_CFG_SUBCLOCK_POPULATED
    g_clock_freq[BSP_CLOCKS_SOURCE_CLOCK_XTALK] = BSP_CFG_XTALK_HZ;
#endif

#if BSP_TZ_NONSECURE_BUILD && BSP_TZ_CFG_CGFSAR != 0xFFFFFFFFU

    /* If the CGC is secure and this is a non secure project, register a callback for getting clock settings. */
    R_BSP_ClockUpdateCallbackSet(g_bsp_clock_update_callback, &g_callback_memory);
#endif

    /* The SystemCoreClock needs to be updated before calling R_BSP_SoftwareDelay. */
    SystemCoreClockUpdate();

#if BSP_FEATURE_CGC_HAS_LP_CLOCK

    /* The g_bsp_lp_clock variable needs to be updated. */
    R_BSP_LPClockUpdate();
#endif
}

/*******************************************************************************************************************//**
 * Initializes system clocks.  Makes no assumptions about current register settings.
 **********************************************************************************************************************/
void bsp_clock_init (void)
{
    bsp_clock_freq_var_init();

#if BSP_CLOCK_CFG_MAIN_OSC_POPULATED
    bsp_clock_xtalm_configure();
    bsp_prv_clock_xtalm_start();
#else
    bsp_clock_rchs_enable(true);
#endif

#if BSP_FEATURE_CGC_HAS_SOSC
 #if BSP_CLOCK_CFG_SUBCLOCK_POPULATED
    bsp_clock_xtalk_configure();
 #else
    bsp_clock_xtalk_enable(false);
 #endif
#endif

#if BSP_FEATURE_CGC_HAS_RCLP_SPEEDS
    bsp_clock_rclp_speed_set((bsp_clock_rclp_speed_t) BSP_CFG_RCLP_FREQUENCY);
#endif

#if BSP_CLOCKS_SOURCE_CLOCK_RCLP == BSP_CFG_LP_CLOCK_SOURCE
    bsp_clock_rclp_enable(true);
#elif BSP_CLOCKS_SOURCE_CLOCK_RCX == BSP_CFG_LP_CLOCK_SOURCE
 #if BSP_FEATURE_CGC_HAS_RCX_CONTROL
    bsp_clock_rcx_enable(true);
 #endif

 #if !defined(BSP_MCU_GROUP_RA6W1) && !defined(BSP_MCU_GROUP_RA6W3)
  #if BSP_CLOCK_CFG_MAIN_OSC_POPULATED
    bsp_clock_msr_sel_t ref_clock = BSP_CLOCK_MSR_SEL_XTAL32M;
  #else
    bsp_clock_msr_sel_t ref_clock = BSP_CLOCK_MSR_SEL_DIVN;
  #endif

    /* Perform initial measurement of RCX and update the value in the frequency table. */
    R_BSP_SourceClockHzSet(FSP_PRIV_CLOCK_RCX,
                           bsp_clock_measurement(BSP_CLOCK_MSR_SEL_RCX, ref_clock, BSP_CFG_CLOCK_CALIBRATION_CYCLES));
 #endif
#elif BSP_CLOCKS_SOURCE_CLOCK_XTALK == BSP_CFG_LP_CLOCK_SOURCE
 #if BSP_FEATURE_CGC_HAS_SOSC
  #if BSP_CLOCK_CFG_SUBCLOCK_POPULATED
    bsp_clock_xtalk_enable(true);
   #if BSP_MCU_GROUP_RA6B1 || BSP_MCU_GROUP_RA6U1

    R_BSP_SoftwareDelay(BSP_CLOCK_CFG_SUBCLOCK_STABILIZATION_MS, BSP_DELAY_UNITS_MILLISECONDS);
   #endif
  #endif
 #endif
#endif

#if BSP_FEATURE_CGC_HAS_LP_CLOCK
    bsp_clock_lpclk_set((fsp_priv_source_clock_t) BSP_CFG_LP_CLOCK_SOURCE);

    R_BSP_LPClockUpdate();
#endif

#if BSP_CLOCK_CFG_MAIN_OSC_POPULATED

    /* Switch to XTAL32M first in any case. */
    bsp_clock_sysclk_set(FSP_PRIV_CLOCK_XTALM);
#endif

    /* Set source clock and dividers. */
#if BSP_CFG_STARTUP_CLOCK_REG_NOT_RESET
 #if BSP_TZ_SECURE_BUILD

    /* In case of soft reset, make sure callback pointer is NULL initially. */
    g_bsp_clock_update_callback = NULL;
 #endif
#else
    bsp_prv_clock_set_hard_reset();
#endif
}

/*******************************************************************************************************************//**
 * Gets the frequency of a source clock.
 * @param[in]   clock   Pointer to Octaclk setting structure which provides information regarding
 *                                  Octaclk source and divider settings to be applied.
 * @return     Frequency of requested clock in Hertz.
 **********************************************************************************************************************/
uint32_t R_BSP_SourceClockHzGet (fsp_priv_source_clock_t clock)
{
    BSP_CHECK_FATAL(clock <= FSP_PRIV_CLOCK_DIGITAL);

    uint32_t source_clock = 0;

    source_clock = g_clock_freq[clock];

    return source_clock;
}

/*******************************************************************************************************************//**
 * Sets the frequency of a source clock.
 * @param[in]   clock   Pointer to Octaclk setting structure which provides information regarding
 *                                  Octaclk source and divider settings to be applied.
 * @param[in]   freq    Frequency of requested clock in Hertz.
 **********************************************************************************************************************/
void R_BSP_SourceClockHzSet (fsp_priv_source_clock_t clock, uint32_t freq)
{
    BSP_CHECK_FATAL(clock <= FSP_PRIV_CLOCK_DIGITAL);

    g_clock_freq[clock] = freq;

    SystemCoreClockUpdate();
#if BSP_FEATURE_CGC_HAS_LP_CLOCK
    R_BSP_LPClockUpdate();
#endif
}

#if BSP_FEATURE_CGC_HAS_LP_CLOCK

/*******************************************************************************************************************//**
 * Set Low Power clock.
 *
 * \param[in] clock The new low power clock.
 **********************************************************************************************************************/
void bsp_clock_lpclk_set (fsp_priv_source_clock_t clock)
{
    uint32_t clock_index = clock - FSP_PRIV_CLOCK_RCLP;
    uint32_t clk_ctrl_reg;
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    clk_ctrl_reg = CRG_TOP->CLK_CTRL_REG;
    FSP_REG_VAR_FIELD_SET(CRG_TOP, CLK_CTRL_REG, LP_CLK_SEL, clk_ctrl_reg, clock_index);
    CRG_TOP->CLK_CTRL_REG = clk_ctrl_reg;

    FSP_CRITICAL_SECTION_EXIT;
}

/*******************************************************************************************************************//**
 * Gets the frequency of the low power clock.
 *
 * @return     Frequency of requested clock in Hertz.
 **********************************************************************************************************************/
uint32_t R_BSP_LPClockHzGet (void)
{
    return g_bsp_lp_clock;
}

#endif

#if BSP_FEATURE_RTC_IS_AVAILABLE

/*******************************************************************************************************************//**
 * RTC Initialization
 *
 * Configures the dividers for the 100kHz clock generation & the RTC_KEEP_RTC_REG.
 **********************************************************************************************************************/
void R_BSP_Init_RTC (void)
{
    uint16_t div_int;
    uint16_t div_frac;
    uint32_t clk_rtc_div;
    uint32_t lp_clk_freq = R_BSP_LPClockHzGet();

    div_int  = (uint16_t) (lp_clk_freq / 100);                    // NOLINT
    div_frac = (uint16_t) (10 * (lp_clk_freq - (div_int * 100))); // NOLINT

    clk_rtc_div  = div_frac;
    clk_rtc_div += div_int << CRG_AON_CLK_RTCDIV_REG_RTC_DIV_INT_Pos;

    clk_rtc_div += (CRG_TOP->CLK_CTRL_REG_b.LP_CLK_SEL) << CRG_AON_CLK_RTCDIV_REG_RTC_CLK_SEL_Pos;

    CRG_AON->CLK_RTCDIV_REG = clk_rtc_div;

    RTC->RTC_KEEP_RTC_REG = 1U;
}

#endif

/** @} (end addtogroup BSP_MCU_PRV) */
