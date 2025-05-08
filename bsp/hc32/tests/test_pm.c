/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

/*
* 功能
* 程序清单：这是一个 PM 设备使用例程
* 例程导出了 pm_sample_init 命令到控制终端
* 命令调用格式：pm_sample_init
*
*   展示RTT休眠模式的进入和退出
*   hc32 drv_pm 支持的RTT休眠模式包括： idle、deep、standby、shutdown
*   每种休眠模式与芯片低功耗模式的对应关系是：
*       RTT                    |   HC32
*       -----------------------|----------
*       PM_SLEEP_MODE_IDLE     | 睡眠模式
*       PM_SLEEP_MODE_DEEP     | 停止模式
*       PM_SLEEP_MODE_STANDBY  | 掉电模式1或2（可配，默认配置是模式1）
*       PM_SLEEP_MODE_SHUTDOWN | 掉电模式3或4（可配，默认配置是模式3）
*
* 操作步骤1：
*   1）按下按键K10：  MCU进入休眠模式
*   2）再按下按键K10：MCU退出休眠模式
*   3）重复上述按键操作，MCU循环进入休眠模式(deep、standby、shutdown、idle)和退出对应的休眠模式。
*   每次进入休眠模式前，MCU打印 "sleep:" + 休眠模式名称
*   每次退出休眠模式后，MCU打印 "wake from sleep:" + 休眠模式名称
* 操作步骤2：
*   1）支持运行模式切换的芯片循环切换 低速->高速->低速 运行模式,对应时钟输出口输出对应模式下的时钟信号
*/

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <drivers/lptimer.h>

#if defined(BSP_USING_PM)

#if defined (HC32F4A0)
    #define PLL_SRC                             ((CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLSRC) >> CMU_PLLHCFGR_PLLSRC_POS)
    #define BSP_KEY_PORT                        (GPIO_PORT_A)   /* Key10 */
    #define BSP_KEY_PIN                         (GPIO_PIN_00)
    #define BSP_KEY_EXTINT                      (EXTINT_CH00)
    #define BSP_KEY_INT_SRC                     (INT_SRC_PORT_EIRQ0)
    #define BSP_KEY_IRQn                        (INT001_IRQn)
    #define BSP_KEY_INTC_STOP_WKUP_EXTINT       (INTC_STOP_WKUP_EXTINT_CH0)
    #define BSP_KEY_EVT                         (EVT_SRC_PORT_EIRQ0)
    #define BSP_KEY_PWC_PD_WKUP_TRIG_WKUP       (PWC_PD_WKUP_TRIG_WKUP0)
    #define BSP_KEY_PWC_PD_WKUP_WKUP            (PWC_PD_WKUP_WKUP00)

    #define MCO_PORT                            (GPIO_PORT_A)
    #define MCO_PIN                             (GPIO_PIN_08)
    #define MCO_GPIO_FUNC                       (GPIO_FUNC_1)

#elif defined (HC32F460)
    #define PLL_SRC                             ((CM_CMU->PLLCFGR & CMU_PLLCFGR_PLLSRC) >> CMU_PLLCFGR_PLLSRC_POS)
    #define BSP_KEY_PORT                        (GPIO_PORT_B)   /* Key10 */
    #define BSP_KEY_PIN                         (GPIO_PIN_01)
    #define BSP_KEY_EXTINT                      (EXTINT_CH01)
    #define BSP_KEY_INT_SRC                     (INT_SRC_PORT_EIRQ1)
    #define BSP_KEY_IRQn                        (INT001_IRQn)
    #define BSP_KEY_INTC_STOP_WKUP_EXTINT       (INTC_STOP_WKUP_EXTINT_CH1)
    #define BSP_KEY_EVT                         (EVT_SRC_PORT_EIRQ1)
    #define BSP_KEY_PWC_PD_WKUP_TRIG_WKUP       (PWC_PD_WKUP_TRIG_WKUP1)
    #define BSP_KEY_PWC_PD_WKUP_WKUP            (PWC_PD_WKUP_WKUP01)

    #define MCO_PORT                            (GPIO_PORT_A)
    #define MCO_PIN                             (GPIO_PIN_08)
    #define MCO_GPIO_FUNC                       (GPIO_FUNC_1)

#elif defined (HC32F448)
    #define PLL_SRC                             ((CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLSRC) >> CMU_PLLHCFGR_PLLSRC_POS)
    #define BSP_KEY_PORT                        (GPIO_PORT_B)   /* Key5 */
    #define BSP_KEY_PIN                         (GPIO_PIN_06)
    #define BSP_KEY_EXTINT                      (EXTINT_CH06)
    #define BSP_KEY_INT_SRC                     (INT_SRC_PORT_EIRQ6)
    #define BSP_KEY_IRQn                        (INT001_IRQn)
    #define BSP_KEY_INTC_STOP_WKUP_EXTINT       (INTC_STOP_WKUP_EXTINT_CH6)
    #define BSP_KEY_EVT                         (EVT_SRC_PORT_EIRQ6)
    #define BSP_KEY_PWC_PD_WKUP_TRIG_WKUP       (PWC_PD_WKUP_TRIG_WKUP1)
    #define BSP_KEY_PWC_PD_WKUP_WKUP            (PWC_PD_WKUP_WKUP12)

    #define MCO_PORT                            (GPIO_PORT_A)
    #define MCO_PIN                             (GPIO_PIN_08)
    #define MCO_GPIO_FUNC                       (GPIO_FUNC_1)

#elif defined (HC32F472)
    #define PLL_SRC                             ((CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLSRC) >> CMU_PLLHCFGR_PLLSRC_POS)
    #define BSP_KEY_PORT                        (GPIO_PORT_B)   /* Key5 */
    #define BSP_KEY_PIN                         (GPIO_PIN_05)
    #define BSP_KEY_EXTINT                      (EXTINT_CH05)
    #define BSP_KEY_INT_SRC                     (INT_SRC_PORT_EIRQ5)
    #define BSP_KEY_IRQn                        (INT001_IRQn)
    #define BSP_KEY_INTC_STOP_WKUP_EXTINT       (INTC_STOP_WKUP_EXTINT_CH5)
    #define BSP_KEY_EVT                         (EVT_SRC_PORT_EIRQ5)
    #define BSP_KEY_PWC_PD_WKUP_TRIG_WKUP       (PWC_PD_WKUP_TRIG_WKUP1)
    #define BSP_KEY_PWC_PD_WKUP_WKUP            (PWC_PD_WKUP_WKUP11)
#endif

#define KEYCNT_BACKUP_ADDR                      (uint32_t *)(0x200F0010)
#define KEYCNT_CMD_SLEEP_NONE                   (0)
#define KEYCNT_CMD_SLEEP_IDLE                   (1)
#define KEYCNT_CMD_SLEEP_DEEP                   (3)
#define KEYCNT_CMD_SLEEP_STANDBY                (5)
#define KEYCNT_CMD_SLEEP_SHUTDOWN               (7)

#define PM_DBG
#if defined PM_DBG
    #define pm_dbg  rt_kprintf
#else
    #define pm_dbg
#endif

static volatile uint32_t g_keycnt_cmd;
static volatile rt_bool_t g_wkup_flag = RT_FALSE;

static void KEY_IrqHandler(void)
{
    if (SET == EXTINT_GetExtIntStatus(BSP_KEY_EXTINT))
    {
        EXTINT_ClearExtIntStatus(BSP_KEY_EXTINT);
        __DSB();
        __ISB();
    }

    if (g_wkup_flag)
    {
        g_wkup_flag = RT_FALSE;
        return;
    }

    g_keycnt_cmd++;
    pm_dbg("g_keycnt_cmd =%d, ", g_keycnt_cmd);
    pm_dbg("recv sleep request\n");
    NVIC_DisableIRQ(BSP_KEY_IRQn);
    NVIC_ClearPendingIRQ(BSP_KEY_IRQn);
}

static void _key_int_init(void)
{
    stc_extint_init_t stcExtIntInit;
    stc_irq_signin_config_t stcIrqSignConfig;
    stc_gpio_init_t stcGpioInit;

    /* configuration structure initialization */
    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16ExtInt = PIN_EXTINT_ON;
    stcGpioInit.u16PullUp = PIN_PU_ON;
    /* GPIO config */
    (void)GPIO_Init(BSP_KEY_PORT, BSP_KEY_PIN, &stcGpioInit);

    /* Extint config */
    (void)EXTINT_StructInit(&stcExtIntInit);
    stcExtIntInit.u32Edge = EXTINT_TRIG_FALLING;
    (void)EXTINT_Init(BSP_KEY_EXTINT, &stcExtIntInit);

    /* IRQ sign-in */
    stcIrqSignConfig.enIntSrc = BSP_KEY_INT_SRC;
    stcIrqSignConfig.enIRQn   = BSP_KEY_IRQn;
    stcIrqSignConfig.pfnCallback = KEY_IrqHandler;
    (void)INTC_IrqSignIn(&stcIrqSignConfig);

    /* NVIC config */
    NVIC_ClearPendingIRQ(stcIrqSignConfig.enIRQn);
    NVIC_SetPriority(stcIrqSignConfig.enIRQn, DDL_IRQ_PRIO_DEFAULT);
    NVIC_EnableIRQ(stcIrqSignConfig.enIRQn);
}


static void _wkup_cfg_sleep_deep()
{
    INTC_WakeupSrcCmd(BSP_KEY_INTC_STOP_WKUP_EXTINT, ENABLE);
}

static void _wkup_cfg_sleep_standby(void)
{
    PWC_PD_SetWakeupTriggerEdge(BSP_KEY_PWC_PD_WKUP_TRIG_WKUP, PWC_PD_WKUP_TRIG_FALLING);
    PWC_PD_WakeupCmd(BSP_KEY_PWC_PD_WKUP_WKUP, ENABLE);

    PWC_PD_ClearWakeupStatus(PWC_PD_WKUP_FLAG_ALL);
}
static void _wkup_cfg_sleep_shutdown(void)
{
    PWC_PD_SetWakeupTriggerEdge(BSP_KEY_PWC_PD_WKUP_TRIG_WKUP, PWC_PD_WKUP_TRIG_FALLING);
    PWC_PD_WakeupCmd(BSP_KEY_PWC_PD_WKUP_WKUP, ENABLE);
}

static void _sleep_enter_event_idle(void)
{
    rt_kprintf("sleep: idle\n");
}

static void _sleep_enter_event_deep(void)
{
    _wkup_cfg_sleep_deep();
    rt_kprintf("sleep: deep\n");
    DDL_DelayMS(50);
}

static void _sleep_enter_event_standby(void)
{
    _wkup_cfg_sleep_standby();
#if defined (HC32F4A0)
    PWC_BKR_Write(0, g_keycnt_cmd & 0xFF);
#endif
    *KEYCNT_BACKUP_ADDR = g_keycnt_cmd;
    rt_kprintf("sleep: standby\n");
    DDL_DelayMS(50);
}

static void _sleep_enter_event_shutdown(void)
{
    _wkup_cfg_sleep_shutdown();
    *KEYCNT_BACKUP_ADDR = g_keycnt_cmd;
    rt_kprintf("sleep: shutdown\n");
    DDL_DelayMS(50);
}

static void _sleep_exit_event_idle(void)
{
    rt_pm_release(PM_SLEEP_MODE_IDLE);
    rt_pm_request(PM_SLEEP_MODE_NONE);
    rt_kprintf("wakeup from sleep: idle\n");
}

static void _sleep_exit_event_deep(void)
{
#if defined (HC32F460)
    PWC_STOP_ClockRecover();
#endif
    rt_pm_release(PM_SLEEP_MODE_DEEP);
    rt_pm_request(PM_SLEEP_MODE_NONE);
    rt_kprintf("wakeup from sleep: deep\n");
}

typedef void (*notify)(void);
static notify sleep_enter_func[PM_SLEEP_MODE_MAX] =
{
    RT_NULL,
    _sleep_enter_event_idle,
    RT_NULL,
    _sleep_enter_event_deep,
    _sleep_enter_event_standby,
    _sleep_enter_event_shutdown,
};

static notify sleep_exit_func[PM_SLEEP_MODE_MAX] =
{
    RT_NULL,
    _sleep_exit_event_idle,
    RT_NULL,
    _sleep_exit_event_deep,
    RT_NULL,
    RT_NULL,
};

static void  _notify_func(uint8_t event, uint8_t mode, void *data)
{
    if (event == RT_PM_ENTER_SLEEP)
    {
        SysTick_Suspend();
        if (sleep_enter_func[mode] == RT_NULL)
        {
            return;
        }
        sleep_enter_func[mode]();
    }
    else
    {
        SysTick_Resume();
        if (sleep_exit_func[mode] != RT_NULL)
        {
            sleep_exit_func[mode]();
        }
        g_keycnt_cmd++;
        g_wkup_flag = RT_TRUE;
        pm_dbg("g_keycnt_cmd =%d, ", g_keycnt_cmd);

        NVIC_EnableIRQ(BSP_KEY_IRQn);
    }
}

static void pm_cmd_handler(void *parameter)
{
    rt_uint8_t sleep_mode = PM_SLEEP_MODE_NONE;

    while (1)
    {
        if ((KEYCNT_CMD_SLEEP_IDLE == g_keycnt_cmd) || (KEYCNT_CMD_SLEEP_DEEP == g_keycnt_cmd) || \
                (KEYCNT_CMD_SLEEP_STANDBY == g_keycnt_cmd) || (KEYCNT_CMD_SLEEP_SHUTDOWN == g_keycnt_cmd))
        {
            switch (g_keycnt_cmd)
            {
            case KEYCNT_CMD_SLEEP_IDLE:
                sleep_mode = PM_SLEEP_MODE_IDLE;
                break;
            case KEYCNT_CMD_SLEEP_DEEP:
                sleep_mode = PM_SLEEP_MODE_DEEP;
                break;
            case KEYCNT_CMD_SLEEP_STANDBY:
                sleep_mode = PM_SLEEP_MODE_STANDBY;
                break;
            case KEYCNT_CMD_SLEEP_SHUTDOWN:
                sleep_mode = PM_SLEEP_MODE_SHUTDOWN;
                break;
            default:
                break;
            }
            rt_pm_request(sleep_mode);
            rt_pm_release(PM_SLEEP_MODE_NONE);
            rt_thread_mdelay(500);
        }
        else
        {
            rt_thread_mdelay(50);
        }
    }
}

#if defined(HC32F4A0) || defined(HC32F460) || defined(HC32F448)
static void pm_run_main(void *parameter)
{
    static rt_uint8_t run_index = 0;
    char *speed[] = {"low", "high"};
    const rt_uint8_t run_mode[] = {PM_RUN_MODE_LOW_SPEED,  PM_RUN_MODE_HIGH_SPEED};

    GPIO_SetFunc(MCO_PORT, MCO_PIN, MCO_GPIO_FUNC);
    /* Configure clock output system clock */
    CLK_MCOConfig(CLK_MCO1, CLK_MCO_SRC_HCLK, CLK_MCO_DIV8);
    /* MCO1 output enable */
    CLK_MCOCmd(CLK_MCO1, ENABLE);

    while (1)
    {
        rt_pm_run_enter(run_mode[run_index]);

        rt_thread_mdelay(100);

        rt_kprintf("system clock switch to %s speed\n\n", speed[run_index]);
        if (++run_index >= ARRAY_SZ(run_mode))
        {
            run_index = 0;
        }

        rt_thread_mdelay(3000);
    }
}
#endif

static void _keycnt_cmd_init_after_power_on(void)
{
    en_flag_status_t wkup_from_ptwk = PWC_PD_GetWakeupStatus(PWC_PD_WKUP_FLAG_WKUP0);
#if defined (HC32F4A0)
    en_flag_status_t bakram_pd = PWC_BKR_GetStatus(PWC_BACKUP_RAM_FLAG_RAMPDF);
    uint8_t bkr0 = PWC_BKR_Read(0);

    if (bakram_pd == RT_TRUE)
    {
        g_keycnt_cmd = KEYCNT_CMD_SLEEP_NONE;
    }
    else
#endif
    {
        g_keycnt_cmd = *KEYCNT_BACKUP_ADDR;
        if (g_keycnt_cmd == KEYCNT_CMD_SLEEP_STANDBY)
        {
            if (wkup_from_ptwk)
            {
                g_keycnt_cmd++;
                pm_dbg("g_keycnt_cmd =%d, ", g_keycnt_cmd);
                rt_kprintf("wakeup from sleep: standby\n\n");
            }
            else
            {
                g_keycnt_cmd = KEYCNT_CMD_SLEEP_NONE;
            }
        }
        else if (g_keycnt_cmd >= KEYCNT_CMD_SLEEP_SHUTDOWN)
        {
            if ((g_keycnt_cmd == KEYCNT_CMD_SLEEP_SHUTDOWN) && wkup_from_ptwk)
            {
                pm_dbg("g_keycnt_cmd =%d \n", KEYCNT_CMD_SLEEP_NONE);
                rt_kprintf("wakeup from sleep: shutdown\n\n");
            }
            g_keycnt_cmd = KEYCNT_CMD_SLEEP_NONE;
        }
    }

    pm_dbg("KEYCNT_BACKUP_ADDR addr =0x%p,value = %d\n", KEYCNT_BACKUP_ADDR, *KEYCNT_BACKUP_ADDR);
    pm_dbg("wkup_from_ptwk = %d\n", wkup_from_ptwk);
#if defined (HC32F4A0)
    pm_dbg("bakram_pd = %d\n", bakram_pd);
    pm_dbg("bkr0 = %d\n", bkr0);
#endif
}

static void _vbat_init(void)
{
#if defined (HC32F4A0)
    while (PWC_BKR_GetStatus(PWC_BACKUP_RAM_FLAG_RAMVALID) == RESET)
    {
        rt_thread_delay(10);
    }
    FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_SRAMB, ENABLE);
#elif defined (HC32F448)
    FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_SRAMB, ENABLE);
#elif defined (HC32F460)
    FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_SRAMRET, ENABLE);
#elif defined (HC32F472)
    FCG_Fcg0PeriphClockCmd(FCG0_PERIPH_SRAMRET, ENABLE);
#endif
    pm_dbg("vbat init success\n");
}

int pm_sample_init(void)
{
    pm_dbg("pm_sample_init\n\n");

    _keycnt_cmd_init_after_power_on();
    _vbat_init();
    _key_int_init();

    rt_pm_notify_set(_notify_func, NULL);

    rt_thread_t  thread = rt_thread_create("pm_cmd_handler", pm_cmd_handler, RT_NULL, 1024, 25, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create pm sample thread failed!\n");
    }

#if defined(HC32F4A0) || defined(HC32F460) || defined(HC32F448)
    thread = rt_thread_create("pm_run_main", pm_run_main, RT_NULL, 1024, 25, 10);
    if (thread != RT_NULL)
    {
        rt_thread_startup(thread);
    }
    else
    {
        rt_kprintf("create pm run thread failed!\n");
    }
#endif

    return RT_EOK;
}
MSH_CMD_EXPORT(pm_sample_init, pm sample init);

#endif /* end of BSP_USING_PM */
