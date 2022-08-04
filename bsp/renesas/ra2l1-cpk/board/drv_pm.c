/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-03-22     Sherman      first version
 */

// #define DRV_DEBUG
#define DBG_TAG              "drv.pm"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */

#include <rtdbg.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <hal_data.h>

#include <drivers/pm.h>

#define RESET_VALUE     (0x00)
#define CLOCK_START     (0U)
#define CLOCK_STOP      (1U)

/* Control block configuration in LPM mode */
#ifdef BSP_LPM_SLEEP
    #define LPM_SLEEP_CTRL  (lpm_instance_ctrl_t *)&g_lpm_sleep_ctrl
    #define LPM_SLEEP_CFG   (lpm_cfg_t *)&g_lpm_sleep_cfg
#else
    #define LPM_SLEEP_CTRL  RT_NULL
    #define LPM_SLEEP_CFG   RT_NULL
#endif

#ifdef BSP_LPM_STANDBY
    #define LPM_SW_STANDBY_CTRL  (lpm_instance_ctrl_t *)&g_lpm_sw_standby_ctrl
    #define LPM_SW_STANDBY_CFG  (lpm_cfg_t *)&g_lpm_sw_standby_cfg
#else
    #define LPM_SW_STANDBY_CTRL  RT_NULL
    #define LPM_SW_STANDBY_CFG  RT_NULL
#endif

#ifdef BSP_LPM_SNOOZE
    #define LPM_SW_SNOOZE_CTRL  (lpm_instance_ctrl_t *)&g_lpm_sw_standby_with_snooze_ctrl
    #define LPM_SW_SNOOZE_CFG   (lpm_cfg_t *)&g_lpm_sw_standby_with_snooze_cfg
#else
    #define LPM_SW_SNOOZE_CFG   RT_NULL
    #define LPM_SW_SNOOZE_CTRL  RT_NULL
#endif

/**
 * These are LPM Mode instances for Sleep, Software Standby, Snooze and Deep
 * Software Standby Modes.These instances are created by the FSP. We need these
 * at the Application level to take the MCU to different LPM modes with configured
 * trigger/cancel sources
 */
lpm_instance_ctrl_t *g_lpm_ctrl_instance_ctrls[] =
{
    LPM_SLEEP_CTRL,
    LPM_SW_STANDBY_CTRL,
    LPM_SW_SNOOZE_CTRL,
};

lpm_cfg_t   *g_lpm_ctrl_instance_cfgs[]  =
{
    LPM_SLEEP_CFG,
    LPM_SW_STANDBY_CFG,
    LPM_SW_SNOOZE_CFG,
};

/**
 * Low Power Mode Definitions for LPM app
 * Since there are no Normal mode definition in LPM driver, use this enum to keep LPM app state including:
 * Sleep, SW Standby, SW Standby with Snooze enabled, Deep SW Standby, Normal.
 * Power consumption: NORMAL_STATE > SLEEP_STATE > SW_STANDBY_SNOOZE_STATE > SW_STANDBY_STATE > DEEP_SW_STANDBY_STATE
 */
enum
{
    SLEEP_STATE = 0,             /* Sleep mode */
    SW_STANDBY_STATE,            /* SW Standby mode */
    SW_STANDBY_SNOOZE_STATE,     /* SW Standby mode with Snooze enabled */
    DEEP_SW_STANDBY_STATE,       /* Deep SW Standby mode */
    NORMAL_STATE                 /* Normal mode */
};

#ifdef DRV_DEBUG
static char *lpmstate_to_string(rt_uint8_t state)
{
    switch (state)
    {
    case SLEEP_STATE:
        return "SLEEP";
    case SW_STANDBY_STATE:
        return "SW STANDBY";
    case SW_STANDBY_SNOOZE_STATE:
        return "SW STANDBY SNOOZE";
    case DEEP_SW_STANDBY_STATE:
        return "DEEP SW STANDBY";
    case NORMAL_STATE:
        return "NORMAL";
    default:
        return "UNKNOWN";
    }
    return "UNKNOWN";
}

static char *clk_to_string(cgc_clock_t cstate)
{
    switch (cstate)
    {
    case CGC_CLOCK_HOCO:
        return "HOCO CLOCK";
    case CGC_CLOCK_MOCO:
        return "MOCO CLOCK";
    case CGC_CLOCK_LOCO:
        return "LOCO CLOCK";
    case CGC_CLOCK_MAIN_OSC:
        return "MAIN OSC CLOCK";
    case CGC_CLOCK_SUBCLOCK:
        return "SUB OSC CLOCK";
    case CGC_CLOCK_PLL:
        return "PLL OSC CLOCK";
    default:
        return "UNKNOWN";
    }
    return "UNKNOWN";
}
#endif

/**
 * @brief       This function enables and puts the MCU in sleep mode.
 * @param[IN]   Requested LPM Mode and the pointer to it's instance
 * @retval      FSP_SUCCESS:    Upon successful entering sleep mode
 * @retval      Any Other Error code apart from FSP_SUCCESS
 */
static fsp_err_t lpm_mode_enter(uint8_t lpm_mode, lpm_instance_ctrl_t *const p_current_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;

    switch (lpm_mode)
    {

    case SW_STANDBY_STATE:
        /* Enter SW Standby mode */
        err = R_LPM_LowPowerModeEnter(p_current_ctrl);
        break;

    case SLEEP_STATE:
        /* Enter Sleep mode */
        err = R_LPM_LowPowerModeEnter(p_current_ctrl);
        break;

    case SW_STANDBY_SNOOZE_STATE:
        /* Enter SW Standby with Snooze enabled mode */
        err = R_LPM_LowPowerModeEnter(p_current_ctrl);
        break;

    default:
        /* return error */
        err = FSP_ERR_INVALID_MODE;
        break;
    }
    return err;
}

/**
 * @brief       Start the LPM mode based on the incoming state
 * @param[IN]   state: This is requested LPM state
 * @retval      None.
 */
static void entry_lpm(uint8_t state)
{
    if (RT_NULL == g_lpm_ctrl_instance_ctrls[state])
    {
        return;
    }

    fsp_err_t err = FSP_SUCCESS;
    /* Disable IO port if it's not in Deep SW Standby mode */
    if (DEEP_SW_STANDBY_STATE != state)
    {
        /* Disable IO port before going to LPM mode*/
        err = R_IOPORT_PinsCfg(&g_ioport_ctrl, &g_bsp_pin_cfg);
        /* Handle error */
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }
    }

    /* Open LPM instance*/
    err = R_LPM_Open(g_lpm_ctrl_instance_ctrls[state], g_lpm_ctrl_instance_cfgs[state]);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        LOG_E("Returned Error Code: 0x%x", err);
    }
    /* Enter LPM mode. Function will return after waking from low power mode. */
    err = lpm_mode_enter(state, g_lpm_ctrl_instance_ctrls[state]);

    /* Handle error */
    if (FSP_SUCCESS == err)
    {
        /* Close LPM instance.*/
        err = R_LPM_Close(g_lpm_ctrl_instance_ctrls[state]);
        /* Handle error */
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }

        /* Put IO port configuration back to user's selections */
        err = R_IOPORT_PinsCfg(&g_ioport_ctrl, &g_bsp_pin_cfg);
        /* Handle error */
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }
    }
    else
    {
        LOG_E("Returned Error Code: 0x%x", err);
    }
}

/**********************************************************************************************************************
 * @brief       This function does necessary setups before entering SW Standby with Snooze enabled.
 * @retval      FSP_SUCCESS Upon successful checking and starting LOCO clock, AGT1 timer
 * @retval      Any Other Error code apart from FSP_SUCCESS
 **********************************************************************************************************************/
static fsp_err_t standby_snooze_set(void)
{
    fsp_err_t err = FSP_SUCCESS;
    agt_extended_cfg_t const *p_agt0_extend = agt1_timer_cascade_trigger_cfg.p_extend;

    /* Turn off part of the clock before entering Snooze */
    err = R_CGC_ClockStop(&g_cgc0_ctrl, CGC_CLOCK_MOCO);
    if (FSP_SUCCESS != err)
    {
        LOG_E("Returned Error Code: 0x%x", err);
    }

    err = R_CGC_ClockStop(&g_cgc0_ctrl, CGC_CLOCK_MAIN_OSC);
    if (FSP_SUCCESS != err)
    {
        LOG_E("Returned Error Code: 0x%x", err);
    }

    err = R_CGC_ClockStop(&g_cgc0_ctrl, CGC_CLOCK_SUBCLOCK);
    if (FSP_SUCCESS != err)
    {
        LOG_E("Returned Error Code: 0x%x", err);
    }

    /*
     * Check and start LOCO clock. LOCO is needed since it is selected as AGT1 timer counter source
     * CGC module is opened in user_clocks_set function
     */
    if (AGT_CLOCK_LOCO == p_agt0_extend->count_source)
    {
        if (CLOCK_STOP == R_SYSTEM->LOCOCR_b.LCSTP)
        {
            /* Start LOCO clock */
            err = R_CGC_ClockStart(&g_cgc0_ctrl, CGC_CLOCK_LOCO, NULL);
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                return err;
            }
            /* LOCO does not have Oscillation Stabilization Flag, wait for its stabilization by adding delay */
            R_BSP_SoftwareDelay(BSP_FEATURE_CGC_LOCO_STABILIZATION_MAX_US, BSP_DELAY_UNITS_MICROSECONDS);
        }
    }

    return err;
}

static void ra_sleep(struct rt_pm *pm, rt_uint8_t mode)
{
    switch (mode)
    {
    case PM_SLEEP_MODE_NONE:
        break;

    case PM_SLEEP_MODE_IDLE:
#ifdef BSP_LPM_SLEEP
        /* enrty sleep mode */
        entry_lpm(SLEEP_STATE);
#else
        LOG_W("Disable mode:%s", lpmstate_to_string(SLEEP_STATE));
#endif
        break;

    case PM_SLEEP_MODE_LIGHT:
        LOG_W("PM_SLEEP_MODE_LIGHT:This mode is not supported!");
        break;

    case PM_SLEEP_MODE_DEEP:
#ifdef BSP_LPM_SNOOZE
        /* enrty standby snooze mode */
        standby_snooze_set();
        entry_lpm(SW_STANDBY_SNOOZE_STATE);
#else
        LOG_W("Disable mode:%s", lpmstate_to_string(SW_STANDBY_SNOOZE_STATE));
#endif
        break;

    case PM_SLEEP_MODE_STANDBY:
#ifdef BSP_LPM_STANDBY
        /* enrty standby mode */
        entry_lpm(SW_STANDBY_STATE);
#else
        LOG_W("Disable mode:%s", lpmstate_to_string(SW_STANDBY_STATE));
#endif
        break;

    case PM_SLEEP_MODE_SHUTDOWN:
        LOG_W("PM_SLEEP_MODE_SHUTDOWN:This mode is not supported!");
        break;

    default:
        RT_ASSERT(0);
        break;
    }
}

/**
 * @brief This function changes the System Clock. Currently MOSC and SOSC are not connected on RA2L1 board.
 *        So these needs to be turned OFF
 */
static void preffered_ra_clock_setting(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Stop the Main Oscillator as it is not available on RA2L1-EK Board */
    err = R_CGC_ClockStop(&g_cgc0_ctrl, CGC_CLOCK_MAIN_OSC);
    if (FSP_SUCCESS != err)
    {
        LOG_E("Returned Error Code: 0x%x", err);
    }

    /* Stop the Sub Oscillator as it is not available on RA2L1-EK Board */
    err = R_CGC_ClockStop(&g_cgc0_ctrl, CGC_CLOCK_SUBCLOCK);
    if (FSP_SUCCESS != err)
    {
        LOG_E("Returned Error Code: 0x%x", err);
    }
}

#ifdef R_CGC_H
void uart_update(rt_uint8_t clockmode)
{
    baud_setting_t baud_setting;
    uint32_t       baud_rate                 = BAUD_RATE_115200;
    bool           enable_bitrate_modulation = false;
    uint32_t       error_rate_x_1000         = 5000;

    switch (clockmode)
    {
    case CGC_CLOCK_HOCO:
        baud_rate = BAUD_RATE_115200;
        break;
    case CGC_CLOCK_MOCO:
        baud_rate = BAUD_RATE_38400;
        break;
    case CGC_CLOCK_LOCO:
    case CGC_CLOCK_SUBCLOCK:
        baud_rate = 600;
        break;
    default:
        baud_rate = BAUD_RATE_115200;
        break;
    }

    fsp_err_t err = R_SCI_UART_BaudCalculate(baud_rate,
                    enable_bitrate_modulation,
                    error_rate_x_1000,
                    &baud_setting);
    err = R_SCI_UART_BaudSet(&g_uart9_ctrl, (void *) &baud_setting);
    assert(FSP_SUCCESS == err);
}

/**
 * @brief This function is used to changes the System Clock.
 */
static void change_system_clock(rt_uint8_t clockmode)
{
    fsp_err_t err = FSP_SUCCESS;
    cgc_divider_cfg_t sys_divider_cf = { RESET_VALUE };
    cgc_clock_t  sys_clock_source    = { RESET_VALUE };
    cgc_clocks_cfg_t sys_clk_cfg     = { RESET_VALUE };
    cgc_pll_cfg_t new_clk            = { RESET_VALUE };

#if defined (CPK_R7FA2L1AB)
    preffered_ra_clock_setting();
    sys_clk_cfg.mainosc_state = CGC_CLOCK_CHANGE_STOP;
#endif

    err = R_CGC_SystemClockGet(&g_cgc0_ctrl, &sys_clock_source, &sys_divider_cf);
    if (FSP_SUCCESS != err)
    {
        LOG_E("Returned Error Code: 0x%x", err);
    }

    LOG_D("MCU Running with Clock Source = %s.", clk_to_string(sys_clock_source));
    switch (clockmode)
    {
    case CGC_CLOCK_HOCO:
    case CGC_CLOCK_MOCO:
    {
        sys_clock_source = clockmode;
        sys_clk_cfg.hoco_state = CGC_CLOCK_CHANGE_START;

        sys_clk_cfg.pll_cfg.source_clock = sys_clock_source;
        sys_clk_cfg.pll_cfg.divider = CGC_PLL_DIV_1;
        sys_clk_cfg.pll_cfg.multiplier = 0;

        sys_clk_cfg.pll2_cfg.source_clock = sys_clock_source;
        sys_clk_cfg.pll2_cfg.divider = CGC_PLL_DIV_1;
        sys_clk_cfg.pll2_cfg.multiplier = 0;

        sys_clk_cfg.divider_cfg.pclka_div = CGC_SYS_CLOCK_DIV_1;
        sys_clk_cfg.divider_cfg.pclkb_div = CGC_SYS_CLOCK_DIV_2;
        sys_clk_cfg.divider_cfg.pclkc_div = CGC_SYS_CLOCK_DIV_1;
        sys_clk_cfg.divider_cfg.pclkd_div = CGC_SYS_CLOCK_DIV_1;

        sys_clk_cfg.divider_cfg.iclk_div = CGC_SYS_CLOCK_DIV_1;
        sys_clk_cfg.divider_cfg.bclk_div = CGC_SYS_CLOCK_DIV_1;
        sys_clk_cfg.divider_cfg.fclk_div = CGC_SYS_CLOCK_DIV_1;
        break;
    }

    case CGC_CLOCK_LOCO:
    case CGC_CLOCK_SUBCLOCK:
    {
        sys_clock_source = clockmode;
        sys_clk_cfg.hoco_state = CGC_CLOCK_CHANGE_START;

        sys_clk_cfg.pll_cfg.source_clock = sys_clock_source;
        sys_clk_cfg.pll_cfg.divider = CGC_PLL_DIV_1;
        sys_clk_cfg.pll_cfg.multiplier = 0;

        sys_clk_cfg.pll2_cfg.source_clock = sys_clock_source;
        sys_clk_cfg.pll2_cfg.divider = CGC_PLL_DIV_1;
        sys_clk_cfg.pll2_cfg.multiplier = 0;

        sys_clk_cfg.divider_cfg.pclka_div = CGC_SYS_CLOCK_DIV_1;
        sys_clk_cfg.divider_cfg.pclkb_div = CGC_SYS_CLOCK_DIV_1;
        sys_clk_cfg.divider_cfg.pclkc_div = CGC_SYS_CLOCK_DIV_1;
        sys_clk_cfg.divider_cfg.pclkd_div = CGC_SYS_CLOCK_DIV_1;

        sys_clk_cfg.divider_cfg.iclk_div = CGC_SYS_CLOCK_DIV_1;
        sys_clk_cfg.divider_cfg.bclk_div = CGC_SYS_CLOCK_DIV_1;
        sys_clk_cfg.divider_cfg.fclk_div = CGC_SYS_CLOCK_DIV_1;
        break;
    }

    default:
    {
        sys_clock_source = CGC_CLOCK_PLL;
        sys_clk_cfg.pll_state = CGC_CLOCK_CHANGE_NONE;
        break;
    }
    }

    sys_clk_cfg.system_clock = sys_clock_source;

    err = R_CGC_ClocksCfg(&g_cgc0_ctrl, &sys_clk_cfg);
    if (FSP_SUCCESS != err)
    {
        LOG_E("Returned Error Code: 0x%x", err);
    }

    err = R_CGC_SystemClockSet(&g_cgc0_ctrl, sys_clock_source, &sys_clk_cfg.divider_cfg);
    if (FSP_SUCCESS != err)
    {
        LOG_E("Returned Error Code: 0x%x", err);
    }
    LOG_D("Requested Clock Source for MCU = %s.", clk_to_string(sys_clock_source));

    if (CGC_CLOCK_SUBCLOCK == sys_clock_source)
    {
        new_clk.source_clock = CGC_CLOCK_SUBCLOCK;
        err = R_CGC_ClockStart(&g_cgc0_ctrl, CGC_CLOCK_SUBCLOCK, &new_clk);
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }
        err = R_CGC_ClockStop(&g_cgc0_ctrl, CGC_CLOCK_HOCO);
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }

        err = R_CGC_ClockStop(&g_cgc0_ctrl, CGC_CLOCK_MOCO);
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }

        err = R_CGC_ClockStop(&g_cgc0_ctrl, CGC_CLOCK_LOCO);
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }
    }
    else if (CGC_CLOCK_LOCO == sys_clock_source)
    {
        new_clk.source_clock = CGC_CLOCK_LOCO;
        err = R_CGC_ClockStart(&g_cgc0_ctrl, CGC_CLOCK_LOCO, &new_clk);
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }

        err = R_CGC_ClockStop(&g_cgc0_ctrl, CGC_CLOCK_HOCO);
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }

        err = R_CGC_ClockStop(&g_cgc0_ctrl, CGC_CLOCK_MOCO);
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }
    }
    else if (CGC_CLOCK_MOCO == sys_clock_source)
    {
        new_clk.source_clock = CGC_CLOCK_MOCO;
        err = R_CGC_ClockStart(&g_cgc0_ctrl, CGC_CLOCK_MOCO, &new_clk);
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }

        err = R_CGC_ClockStop(&g_cgc0_ctrl, CGC_CLOCK_HOCO);
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }
    }
    else if (CGC_CLOCK_HOCO == sys_clock_source)
    {
        new_clk.source_clock = CGC_CLOCK_HOCO;

        err = R_CGC_ClockStart(&g_cgc0_ctrl, CGC_CLOCK_HOCO, &new_clk);
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }

        err = R_CGC_ClockStop(&g_cgc0_ctrl, CGC_CLOCK_MOCO);
        if (FSP_SUCCESS != err)
        {
            LOG_E("Returned Error Code: 0x%x", err);
        }
    }

    /* Clock  Oscillation Stabilization, wait for its stabilization by adding delay */
    R_BSP_SoftwareDelay(BSP_FEATURE_CGC_LOCO_STABILIZATION_MAX_US, BSP_DELAY_UNITS_MICROSECONDS);

    extern void rt_hw_systick_init(void);
    rt_hw_systick_init();
    uart_update(clockmode);
}

static void ra_run(struct rt_pm *pm, rt_uint8_t mode)
{
    switch (mode)
    {
    case PM_RUN_MODE_HIGH_SPEED:
    case PM_RUN_MODE_NORMAL_SPEED:
        change_system_clock(CGC_CLOCK_HOCO);
        break;
    case PM_RUN_MODE_MEDIUM_SPEED:
        change_system_clock(CGC_CLOCK_MOCO);
        break;
    case PM_RUN_MODE_LOW_SPEED:
        change_system_clock(CGC_CLOCK_LOCO);
        break;
    default:
        break;
    }
}
#endif

/* Agt1 serves as a low-power timer */
/**
 * @brief       This function opens AGT modules
 */
static fsp_err_t agt_timer_init(void)
{
    fsp_err_t err = FSP_SUCCESS;
    /* Open AGT1 Timer in Periodic mode */
    err = R_AGT_Open(&agt1_timer_cascade_trigger_ctrl, &agt1_timer_cascade_trigger_cfg);
    return err;
}

/**
 * @brief       This function starts AGT modules
 */
#define AGT_SECOND_COUNT   512 /* clock_frequency / clock_divider */
#define PERIOD_MAX   0xFFFF
static fsp_err_t agt_timer_start(rt_uint32_t timeout)
{
    fsp_err_t err = FSP_SUCCESS;
    rt_uint32_t tick = timeout * AGT_SECOND_COUNT / RT_TICK_PER_SECOND;
    rt_uint32_t period1 = tick > PERIOD_MAX ? PERIOD_MAX : tick;
    if (period1)
    {
        /* PeriodSet AGT1 timer */
        err = R_AGT_PeriodSet(&agt1_timer_cascade_trigger_ctrl, period1);
        if (FSP_SUCCESS == err)
        {
            /* Start AGT1 timer */
            err = R_AGT_Start(&agt1_timer_cascade_trigger_ctrl);
        }
    }

    return err;
}

/**
 * @brief       This function stops AGT modules
 */
static fsp_err_t agt_timer_stop(void)
{
    fsp_err_t err = FSP_SUCCESS;
    timer_status_t agt_status = {0};

    err =  R_AGT_StatusGet(&agt1_timer_cascade_trigger_ctrl, &agt_status);
    if (FSP_SUCCESS == err)
    {
        if (agt_status.state)
        {
            /* Stop Timer */
            err = R_AGT_Stop(&agt1_timer_cascade_trigger_ctrl);
            if (FSP_SUCCESS == err)
            {
                /* Reset counter */
                err = R_AGT_PeriodSet(&agt1_timer_cascade_trigger_ctrl, 0);
                err = R_AGT_Reset(&agt1_timer_cascade_trigger_ctrl);
            }
        }
    }
    return err;
}

static rt_uint32_t agt_timer_get(void)
{
    rt_uint32_t tick = 0;
    rt_uint32_t counter = 0;

    timer_status_t agt1_status = {0};
    timer_info_t agt1_info = {RESET_VALUE};
    /* Stop AGT timers if they are counting */
    R_AGT_InfoGet(&agt1_timer_cascade_trigger_ctrl, &agt1_info);
    R_AGT_StatusGet(&agt1_timer_cascade_trigger_ctrl, &agt1_status);
    counter = agt1_status.counter < agt1_info.period_counts ?
              agt1_info.period_counts : (agt1_info.period_counts - agt1_status.counter);

    tick = counter * RT_TICK_PER_SECOND / AGT_SECOND_COUNT;
    LOG_D("get tick %u counter %u", tick, counter);
    return tick;
}

static void ra_timer_start(struct rt_pm *pm, rt_uint32_t timeout)
{
    agt_timer_start(timeout);
}

static void ra_timer_stop(struct rt_pm *pm)
{
    agt_timer_stop();
}

static rt_tick_t ra_timer_get_tick(struct rt_pm *pm)
{
    return agt_timer_get();
}

static const struct rt_pm_ops _ops =
{
    ra_sleep,
#ifdef R_CGC_H
    ra_run,
#else
    RT_NULL,
#endif
    ra_timer_start,
    ra_timer_stop,
    ra_timer_get_tick
};

/**
 * @brief       This function initializes clock module by opening the CGC Module and Changes the System Clock to MOSC
 * @param[IN]   None
 * @retval      FSP_SUCCESS:     Upon successful initialization.
 * @retval      Any Other Error code apart from FSP_SUCCESS
 */
static fsp_err_t init_cgc(void)
{
    fsp_err_t err = FSP_SUCCESS;

    cgc_clock_t       lsys_clock_source = {RESET_VALUE};
    cgc_divider_cfg_t sys_divider_cf    = {RESET_VALUE};

    /* Open CGC module */
    err = R_CGC_Open(&g_cgc0_ctrl, &g_cgc0_cfg);
    /* Handle error */
    if (FSP_SUCCESS == err)
    {
        /* Get system clock source */
        err =  R_CGC_SystemClockGet(&g_cgc0_ctrl, &lsys_clock_source, &sys_divider_cf);
        /* Handle error */
        if (FSP_SUCCESS == err)
        {
            LOG_D("MCU Running with Clock Source = %s.", clk_to_string(lsys_clock_source));
        }
    }
    return err;
}

/**
 * @brief   This function initialize the power manager
 */
int drv_pm_hw_init(void)
{
    rt_uint8_t timer_mask = 0;
    fsp_err_t err = FSP_SUCCESS;
    /* Initialize the CGC(Clock Generation Circuit) module.
     * The CGC module API is used to dynamically change the required clock source */
    err = init_cgc();
    if (FSP_SUCCESS != err)
    {
        LOG_D("CGC Initialization Failed \r\n");
        LOG_E("Returned Error Code: 0x%x", err);
        return -1;
    }

    err = agt_timer_init();
    if (FSP_SUCCESS != err)
    {
        LOG_D("AGT Initialization Failed \r\n");
        LOG_E("Returned Error Code: 0x%x", err);
        return -1;
    }

    /* initialize timer mask */
    timer_mask = (1UL << PM_SLEEP_MODE_DEEP) | (1UL << PM_SLEEP_MODE_STANDBY);

    /* initialize system pm module */
    rt_system_pm_init(&_ops, timer_mask, RT_NULL);

    return 0;
}
INIT_BOARD_EXPORT(drv_pm_hw_init);
