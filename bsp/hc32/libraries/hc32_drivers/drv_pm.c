/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-12     CDT          first version
 */

#include <board.h>
#include <drv_pm.h>
#include <drv_common.h>
#include <drv_wktm.h>
#include <drv_config.h>

#if defined(RT_USING_PM)

#if defined(BSP_USING_PM)

#define LOG_TAG             "drv_pm"
#include <drv_log.h>

#define IS_PWC_UNLOCKED()           ((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1)

typedef void (* run_switch_func_type)(void);
typedef void (* sleep_enter_func_type)(void);
static void _sleep_enter_idle(void);
static void _sleep_enter_deep(void);
static void _sleep_enter_standby(void);
static void _sleep_enter_shutdown(void);
static void _run_switch_high_to_low(void);
static void _run_switch_low_to_high(void);

static run_switch_func_type _run_switch_func[PM_RUN_MODE_MAX][PM_RUN_MODE_MAX] =
{
    {RT_NULL, RT_NULL, RT_NULL, _run_switch_high_to_low},
    {RT_NULL, RT_NULL, RT_NULL, _run_switch_high_to_low},
    {RT_NULL, RT_NULL, RT_NULL, RT_NULL},
    {_run_switch_low_to_high, _run_switch_low_to_high, RT_NULL, RT_NULL},
};

static sleep_enter_func_type _sleep_enter_func[PM_SLEEP_MODE_MAX] =
{
    RT_NULL,
    _sleep_enter_idle,
    RT_NULL,
    _sleep_enter_deep,
    _sleep_enter_standby,
    _sleep_enter_shutdown,
};

static void _uart_console_reconfig(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    rt_device_control(rt_console_get_device(), RT_DEVICE_CTRL_CONFIG, &config);
}

/**
 * @brief  Enter sleep mode.
 * @param  [in] u8SleepType specifies the type of enter sleep's command.
 *   @arg  PWC_SLEEP_WFI            Enter sleep mode by WFI, and wake-up by interrupt handle.
 *   @arg  PWC_SLEEP_WFE_INT        Enter sleep mode by WFE, and wake-up by interrupt request(SEVONPEND=1)
 *   @arg  PWC_SLEEP_WFE_EVT        Enter sleep mode by WFE, and wake-up by event(SEVONPEND=0).

 * @retval None
 */
__WEAKDEF void pwc_sleep_enter(uint8_t u8SleepType)
{
    DDL_ASSERT(IS_PWC_UNLOCKED());

    CLR_REG16_BIT(CM_PWC->STPMCR, PWC_STPMCR_STOP);
    CLR_REG8_BIT(CM_PWC->PWRC0, PWC_PWRC0_PWDN);

    if (PWC_SLEEP_WFI == u8SleepType)
    {
        __WFI();
    }
    else
    {
        if (PWC_SLEEP_WFE_INT == u8SleepType)
        {
            SET_REG32_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
        }
        else
        {
            CLR_REG32_BIT(SCB->SCR, SCB_SCR_SEVONPEND_Msk);
        }
        __SEV();
        __WFE();
        __WFE();
    }
}

static void _sleep_enter_idle(void)
{
    struct pm_sleep_mode_idle_config sleep_idle_cfg = PM_SLEEP_IDLE_CFG;
    pwc_sleep_enter(sleep_idle_cfg.pwc_sleep_type);
}

static void _sleep_enter_deep(void)
{
    struct pm_sleep_mode_deep_config sleep_deep_cfg = PM_SLEEP_DEEP_CFG;

    RT_ASSERT(PM_SLEEP_CHECK(PM_SLEEP_MODE_DEEP));

    (void)PWC_STOP_Config(&sleep_deep_cfg.cfg);

    if (PWC_PWRC2_DVS == (READ_REG8(CM_PWC->PWRC2) & PWC_PWRC2_DVS))
    {
        CLR_REG8_BIT(CM_PWC->PWRC1, PWC_PWRC1_STPDAS);
    }
    else
    {
        SET_REG8_BIT(CM_PWC->PWRC1, PWC_PWRC1_STPDAS);
    }
    PWC_STOP_Enter(sleep_deep_cfg.pwc_stop_type);
}

static void _sleep_enter_standby(void)
{
    struct pm_sleep_mode_standby_config sleep_standby_cfg = PM_SLEEP_STANDBY_CFG;
    RT_ASSERT(PM_SLEEP_CHECK(PM_SLEEP_MODE_SHUTDOWN));
    RT_ASSERT(sleep_standby_cfg.cfg.u8Mode == PWC_PD_MD1 || sleep_standby_cfg.cfg.u8Mode == PWC_PD_MD2);

    (void)PWC_PD_Config(&sleep_standby_cfg.cfg);
    PWC_PD_ClearWakeupStatus(PWC_PD_WKUP_FLAG_ALL);
    __set_FAULTMASK(1);
    PWC_PD_Enter();
}

static void _sleep_enter_shutdown(void)
{
    struct pm_sleep_mode_shutdown_config sleep_shutdown_cfg = PM_SLEEP_SHUTDOWN_CFG;
    RT_ASSERT(PM_SLEEP_CHECK(PM_SLEEP_MODE_SHUTDOWN));
    RT_ASSERT(sleep_shutdown_cfg.cfg.u8Mode == PWC_PD_MD3 || sleep_shutdown_cfg.cfg.u8Mode == PWC_PD_MD4);

    (void)PWC_PD_Config(&sleep_shutdown_cfg.cfg);
    PWC_PD_ClearWakeupStatus(PWC_PD_WKUP_FLAG_ALL);
    __set_FAULTMASK(1);
    PWC_PD_Enter();
}

/**
 * @param pm pointer to power manage structure
 */
static void _pm_sleep(struct rt_pm *pm, uint8_t mode)
{
    RT_ASSERT(mode < PM_SLEEP_MODE_MAX);

    if (_sleep_enter_func[mode] != NULL)
    {
        _sleep_enter_func[mode]();
    }
}

static void _run_switch_high_to_low(void)
{
    struct pm_run_mode_config st_run_mode_cfg = PM_RUN_MODE_CFG;
    st_run_mode_cfg.sys_clk_cfg(PM_RUN_MODE_LOW_SPEED);
    SysTick_Configuration();

    PWC_HighSpeedToLowSpeed();
}

static void _run_switch_low_to_high(void)
{
    PWC_LowSpeedToHighSpeed();
    struct pm_run_mode_config st_run_mode_cfg = PM_RUN_MODE_CFG;

    st_run_mode_cfg.sys_clk_cfg(PM_RUN_MODE_HIGH_SPEED);
    SysTick_Configuration();
}

static void _pm_run(struct rt_pm *pm, uint8_t mode)
{
    static uint8_t last_mode = PM_RUN_MODE_NORMAL_SPEED;

    if (mode == last_mode)
        return;

    if (_run_switch_func[last_mode][mode] != RT_NULL)
    {
        _run_switch_func[last_mode][mode]();
    }

    _uart_console_reconfig();

    last_mode = mode;
}

/**
 * This function calculate the PM tick from OS tick
 *
 * @param tick OS tick
 *
 * @return the PM tick
 */
static rt_tick_t _pm_wakeup_timer_tick_from_os_tick(rt_tick_t tick)
{
    rt_uint32_t freq = hc32_wktm_get_countfreq();

    return (freq * tick / RT_TICK_PER_SECOND);
}

/**
 * This function start the timer of pm
 *
 * @param pm Pointer to power manage structure
 * @param timeout How many OS Ticks that MCU can sleep
 */
static void _pm_wakeup_timer_start(struct rt_pm *pm, rt_uint32_t timeout)
{
    RT_ASSERT(pm != RT_NULL);

    /* Convert OS Tick to pmtimer timeout value */
    timeout = _pm_wakeup_timer_tick_from_os_tick(timeout);

    /* Enter __WAKEUP_TIMER_MODE */
    hc32_wktm_start(timeout);
}

/**
 * This function stop the timer of pm
 *
 * @param pm Pointer to power manage structure
 */
static void _pm_wakeup_timer_stop(struct rt_pm *pm)
{
    RT_ASSERT(pm != RT_NULL);

    /* Reset pmtimer status */
    hc32_wktm_stop();
}

/**
 * This function initialize the power manager
 * @note timer feature: only work as wake up timer
 */
int rt_hw_pm_init(void)
{
    static const struct rt_pm_ops _ops =
    {
        _pm_sleep,
        _pm_run,
        _pm_wakeup_timer_start,
        _pm_wakeup_timer_stop,
        RT_NULL
    };

    rt_uint8_t timer_mask = PM_TICKLESS_TIMER_ENABLE_MASK;
    /* initialize system pm module */
    rt_system_pm_init(&_ops, timer_mask, RT_NULL);
    return 0;
}

INIT_DEVICE_EXPORT(rt_hw_pm_init);

#endif

#endif  /* RT_USING_PM */
