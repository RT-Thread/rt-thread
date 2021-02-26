/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2020-12-15     liuhy        the first version
 */

#include "drv_pm.h"

#ifdef RT_USING_PM

//uint32_t save_mem[1024] __attribute__ ((aligned(4)));

void save_register(void *p_head,uint32_t size,void *p_save)
{
     memcpy(p_save,p_head,size);
}
 
void load_register(void *p_head,uint32_t size,void *p_load)
{
    uint32_t tmp;
     memcpy(p_head,p_load,size);
    
    if((p_head == UART0) || (p_head == UART1) || (p_head == UART2) || 
         (p_head == UART3) || (p_head == UART4) || (p_head == UART5) )
    {
        tmp = ((UART_TypeDef*)p_load)->IVS;
        ((UART_TypeDef*)p_head)->IER = tmp;
    }
}

static void uart_console_reconfig(void)
{
    struct serial_configure config = RT_SERIAL_CONFIG_DEFAULT;

    rt_device_control(rt_console_get_device(), RT_DEVICE_CTRL_CONFIG, &config);
}

static void delay(void)
{
    long i;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    i = 0;
    do{
        i++;
    }
    while (i < 4000000); 
    
    rt_hw_interrupt_enable(level);
}

/**
 * This function will put ES32F369x into sleep mode.
 *
 * @param pm pointer to power manage structure
 */

struct pm_callback_t
{
     volatile int in_fun_times;   /*进入函数的次数*/
     volatile char flag;          /*标志*/
     volatile int mode;           /*需要打印的模式*/
};

extern volatile struct pm_callback_t g_pm_data;

static void sleep(struct rt_pm *pm, uint8_t mode)
{
   
    switch (mode)
    {
    case PM_SLEEP_MODE_NONE:
        break;

    case PM_SLEEP_MODE_IDLE:
        break;

    case PM_SLEEP_MODE_LIGHT:
        /* Enter SLEEP Mode, Main regulator is ON */
        ald_pmu_stop1_enter();
        delay();
      
        break;

    case PM_SLEEP_MODE_DEEP:           
        /* Enter STOP 2 mode  */
        ald_pmu_stop2_enter();
        delay();
        break;

    case PM_SLEEP_MODE_STANDBY:
        /* Enter STANDBY mode */
        ald_pmu_stop2_enter();
        delay();
        break;

    case PM_SLEEP_MODE_SHUTDOWN:
        /* Enter SHUTDOWNN mode */
        ald_pmu_stop2_enter();
        delay();
        break;

    default:
        RT_ASSERT(0);
        break;
    }
    
}

static uint8_t run_speed[PM_RUN_MODE_MAX][2] =
{
    {48, 0},
    {48, 1},
    {24, 2},
    {2,  3},
};

static void run(struct rt_pm *pm, uint8_t mode)
{
    static uint8_t last_mode;
    static char *run_str[] = PM_RUN_MODE_NAMES;
    extern uint32_t __system_clock;

    if (mode == last_mode)
        return;
    last_mode = mode;

    ald_cmu_clock_config_default();
    __system_clock = 24000000;
    switch (mode)
    {
    case PM_RUN_MODE_HIGH_SPEED:
    case PM_RUN_MODE_NORMAL_SPEED:
        /* hosc 12MHz, from hosc/3 pll to 48MHz */
        ald_cmu_pll1_config(CMU_PLL1_INPUT_HRC_6, CMU_PLL1_OUTPUT_48M);
        /* MCLK 48MHz */
        ald_cmu_clock_config(CMU_CLOCK_PLL1, 48000000);
        break;
    case PM_RUN_MODE_MEDIUM_SPEED:
        break;
    case PM_RUN_MODE_LOW_SPEED:
        ald_cmu_clock_config(CMU_CLOCK_HRC, 2000000);
        break;
    default:
        break;
    }

    /* 4. 更新外设时钟 */
    uart_console_reconfig();
    /* Re-Configure the Systick time */
    SysTick_Config(ald_cmu_get_sys_clock() / RT_TICK_PER_SECOND);

    rt_kprintf("switch to %s mode, frequency = %d MHz\n", run_str[mode], run_speed[mode][0]);
}

/**
 * This function caculate the PM tick from OS tick
 *
 * @param tick OS tick
 *
 * @return the PM tick
 */
static rt_tick_t es32f3_pm_tick_from_os_tick(rt_tick_t tick)
{
    rt_uint32_t freq = 1;

    return (freq * tick / RT_TICK_PER_SECOND);
}

/**
 * This function caculate the OS tick from PM tick
 *
 * @param tick PM tick
 *
 * @return the OS tick
 */
static rt_tick_t es32f3_os_tick_from_pm_tick(rt_uint32_t tick)
{
    static rt_uint32_t os_tick_remain = 0;
    rt_uint32_t ret, freq;

    freq = 1;
    ret = (tick * RT_TICK_PER_SECOND + os_tick_remain) / freq;

    os_tick_remain += (tick * RT_TICK_PER_SECOND);
    os_tick_remain %= freq;

    return ret;
}

/**
 * This function start the timer of pm
 *
 * @param pm Pointer to power manage structure
 * @param timeout How many OS Ticks that MCU can sleep
 */
static void pm_timer_start(struct rt_pm *pm, rt_uint32_t timeout)
{
    RT_ASSERT(pm != RT_NULL);
    RT_ASSERT(timeout > 0);

    if (timeout != RT_TICK_MAX)
    {
        /* Convert OS Tick to pmtimer timeout value */
        timeout = es32f3_pm_tick_from_os_tick(timeout);
        /* MAX 0xFFFF */
        if (timeout > 0xFFFF)
        {
            timeout = 0xFFFF;
        }
    }
}

/**
 * This function stop the timer of pm
 *
 * @param pm Pointer to power manage structure
 */
static void pm_timer_stop(struct rt_pm *pm)
{
    RT_ASSERT(pm != RT_NULL);
}

/**
 * This function calculate how many OS Ticks that MCU have suspended
 *
 * @param pm Pointer to power manage structure
 *
 * @return OS Ticks
 */
static rt_tick_t pm_timer_get_tick(struct rt_pm *pm)
{
    rt_uint32_t timer_tick;

    RT_ASSERT(pm != RT_NULL);

    timer_tick = 1;

    return es32f3_os_tick_from_pm_tick(timer_tick);
}

/**
 * This function initialize the power manager
 */
int drv_pm_hw_init(void)
{
    static const struct rt_pm_ops _ops =
    {
        sleep,
        run,
        pm_timer_start,
        pm_timer_stop,
        pm_timer_get_tick
    };

    rt_uint8_t timer_mask = 0;

    /* initialize timer mask */
    timer_mask = 1UL << PM_SLEEP_MODE_DEEP;

    /* initialize system pm module */
    rt_system_pm_init(&_ops, timer_mask, RT_NULL);

    return 0;
}
INIT_BOARD_EXPORT(drv_pm_hw_init);

#endif
