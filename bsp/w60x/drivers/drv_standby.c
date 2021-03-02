/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-03-13     tyx          first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_standby.h"

#ifdef BSP_USING_STANDBY
#include "wm_type_def.h"
#include "wm_cpu.h"
#include "wm_pmu.h"
#include "wm_irq.h"
#include "wm_regs.h"

typedef volatile unsigned long vu32;
#define M32(adr)    (*((vu32*) (adr)))
typedef void (*rom_standby_func)(void);

static const rom_standby_func pm_standby = (rom_standby_func)0x499;

#ifdef __ICCARM__
extern void standby_idr(void);
#endif

#if (1 == GCC_COMPILE)
void wm_pm_standby(void)
{
    __asm volatile (
        " cpsid            i    \n"  /* disable irq*/
        " dsb                   \n"
        " ldr r0, =0X499        \n"
        " bx r0                 \n"
        " movs r0, #0x00        \n"
        " isb                   \n"
    );
}
#endif

/**
 * This function will put w60x into run/shutdown mode.
 *
 * @param timeout How many OS Ticks that MCU can sleep
 */
void sys_start_standby(int ms)
{
    rt_uint32_t val;
    int timeout = ms;

    RT_ASSERT(timeout > 0);

    tls_pmu_clk_select(0);

    if (timeout <= 65535)
    {
        /* Enter PM_TIMER_MODE */
        tls_irq_enable(PMU_TIMER1_INT);
        tls_pmu_timer1_stop();
        tls_pmu_timer1_start(timeout);
    }
    else if(timeout <= 65535000)
    {
        timeout /= 1000;
        tls_irq_enable(PMU_TIMER0_INT);
        tls_pmu_timer0_stop();
        tls_pmu_timer0_start(timeout);
    }
    else
    {
        return;
    }
    tls_irq_enable(PMU_GPIO_WAKEUP_INT);    //Open interrupt by default to clear the interrupt flag for IO wake-up
    val = tls_reg_read32(HR_PMU_PS_CR);
    val |= 0x01;
    tls_reg_write32(HR_PMU_PS_CR, val);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <stdlib.h>
static void standby(uint8_t argc, char **argv)
{
    if (argc != 2)
    {
        rt_kprintf("Usage: standby timeout(ms)\n");
        rt_kprintf("eg   : standby 5000\n");
    }
    else
    {
        sys_start_standby(atoi(argv[1]));
    }
}
FINSH_FUNCTION_EXPORT_ALIAS(standby, __cmd_standby, sleep System);
#endif /* RT_USING_FINSH */

#endif /* BSP_USING_STANDBY */
