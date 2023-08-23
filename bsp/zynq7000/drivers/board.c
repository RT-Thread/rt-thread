/*
 * COPYRIGHT (C) 2013-2023, Shanghai Real-Thread Technology Co., Ltd
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"

#include "xil_assert.h"
#include "rtdevice.h"
#include "drv_gpio.h"

typedef struct
{
    volatile rt_uint32_t LOAD;
    volatile rt_uint32_t COUNTER;
    volatile rt_uint32_t CONTROL;
    volatile rt_uint32_t ISR;
} ptimer_reg_t;

/* Values for control register */
#define PRIVATE_TIMER_CONTROL_PRESCALER_MASK     0x0000FF00
#define PRIVATE_TIMER_CONTROL_PRESCALER_SHIFT    8
#define PRIVATE_TIMER_CONTROL_IRQ_ENABLE_MASK    0x00000004
#define PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK   0x00000002
#define PRIVATE_TIMER_CONTROL_ENABLE_MASK        0x00000001

/* Values for ISR register */
#define PRIVATE_TIMER_ISR_EVENT_FLAG_MASK        0x00000001


#define PRIVATE_TIMER_BASE            0xF8F00600
#define PRIVATE_TIMER                ((ptimer_reg_t*)PRIVATE_TIMER_BASE)

static void rt_hw_timer_isr(int vector, void *param)
{
    rt_tick_increase();

    /* clear interrupt */
    PRIVATE_TIMER->ISR = PRIVATE_TIMER_ISR_EVENT_FLAG_MASK;
}

int rt_hw_timer_init(void)
{
    PRIVATE_TIMER->CONTROL &= ~PRIVATE_TIMER_CONTROL_ENABLE_MASK;
    {
        /* Clear the prescaler. */
        rt_uint32_t ctrl = PRIVATE_TIMER->CONTROL;
        ctrl &= ~PRIVATE_TIMER_CONTROL_PRESCALER_MASK;
        PRIVATE_TIMER->CONTROL = ctrl;
    }
    /* The processor timer is always clocked at 1/2 CPU frequency(CPU_3x2x). */
    PRIVATE_TIMER->COUNTER = APU_FREQ/2/RT_TICK_PER_SECOND;
    /* Set reload value. */
    PRIVATE_TIMER->LOAD = APU_FREQ/2/RT_TICK_PER_SECOND;
    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_AUTO_RELOAD_MASK;

    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_IRQ_ENABLE_MASK;
    PRIVATE_TIMER->ISR = PRIVATE_TIMER_ISR_EVENT_FLAG_MASK;

    rt_hw_interrupt_install(IRQ_Zynq7000_PTIMER, rt_hw_timer_isr, RT_NULL, "tick");
    rt_hw_interrupt_umask(IRQ_Zynq7000_PTIMER);

    PRIVATE_TIMER->CONTROL |= PRIVATE_TIMER_CONTROL_ENABLE_MASK;

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);

#include <mmu.h>

#undef AP_RO
#define DESC_SEC       (0x2)
#define CB             (3<<2)  //cache_on, write_back
#define CNB            (2<<2)  //cache_on, write_through
#define NCB            (1<<2)  //cache_off,WR_BUF on
#define NCNB           (0<<2)  //cache_off,WR_BUF off
#define AP_RW          (3<<10) //supervisor=RW, user=RW
#define AP_RO          (2<<10) //supervisor=RW, user=RO
#define XN             (1<<4)  //eXecute Never

#define DOMAIN_FAULT   (0x0)
#define DOMAIN_CHK     (0x1)
#define DOMAIN_NOTCHK  (0x3)
#define DOMAIN0        (0x0<<5)
#define DOMAIN1        (0x1<<5)

#define DOMAIN0_ATTR   (DOMAIN_CHK<<0)
#define DOMAIN1_ATTR   (DOMAIN_FAULT<<2)

/* Read/Write, cache, write back */
#define RW_CB          (AP_RW|DOMAIN0|CB|DESC_SEC)
/* Read/Write, cache, write through */
#define RW_CNB         (AP_RW|DOMAIN0|CNB|DESC_SEC)
/* Read/Write, device type */
#define RW_NCB         (AP_RW|DOMAIN0|NCB|DESC_SEC)
/* Read/Write strongly ordered type */
#define RW_NCNB        (AP_RW|DOMAIN0|NCNB|DESC_SEC)
/* Read/Write without cache and write buffer, no execute */
#define RW_NCNBXN      (AP_RW|DOMAIN0|NCNB|DESC_SEC|XN)
/* Read/Write without cache and write buffer */
#define RW_FAULT       (AP_RW|DOMAIN1|NCNB|DESC_SEC)

extern rt_uint32_t __text_start;

struct mem_desc platform_mem_desc[] = {
    /* no access to the memory below .text */
    /* 521Mb cached DDR memory */
    {(rt_uint32_t)&__text_start, 0x3F600000-1, (rt_uint32_t)&__text_start, RW_CB},
    {0x3F600000, 0x3FFFFFFF, 0x3F600000, RW_NCNBXN},
    /* PL region */
    {0x40000000, 0xBFFFFFFF, 0x40000000, RW_NCNBXN},
    /* IOP registers */
    {0xE0000000, 0xE02FFFFF, 0xE0000000, RW_NCNBXN},
    /* SLCR, PS and CPU private registers, note we map more memory space as the
     * entry is 1MB in size. */
    {0xF8000000, 0xFFFFFFFF, 0xF8000000, RW_NCNBXN},
};

const rt_uint32_t platform_mem_desc_size = sizeof(platform_mem_desc)/sizeof(platform_mem_desc[0]);

void idle_wfi(void)
{
    asm volatile ("wfi");
}

static void rt_xil_assert_callback(const char8 *File, s32 Line)
{
    rt_kprintf("Xil_AssertCallback: %s, %d\n", File, Line);
    RT_ASSERT(0);
}

typedef void (*usleep_hook_t) (unsigned long useconds);

// note: should edit usleep.c in bsp to fix it
//
// static usleep_hook_t usleep_hook;
//
//
// int usleep(unsigned long useconds)
// {
//  if (usleep_hook)
//  {
//      usleep_hook(useconds);
//      return 0;
//  }

//  XTime tEnd, tCur;

//  XTime_GetTime(&tCur);
//  tEnd = tCur + (((XTime) useconds) * COUNTS_PER_USECOND);
//  do
//  {
//      XTime_GetTime(&tCur);
//  } while (tCur < tEnd);

//  return 0;
// }
//
//
//
// void zynq_set_usleep_hook(usleep_hook_t hook)
// {
//  usleep_hook = hook;
// }

extern void zynq_set_usleep_hook(usleep_hook_t hook);

static void hw_usleep_hook(unsigned long useconds)
{
    useconds /= 1000;
    if (useconds == 0)
        useconds = 1;

    rt_thread_mdelay(useconds);
}

static int setup_zynq_usleep_hook(void)
{
    zynq_set_usleep_hook(hw_usleep_hook);
    return 0;
}
INIT_BOARD_EXPORT(setup_zynq_usleep_hook);

static void _assert_hook (const char *ex, const char *func, rt_size_t line)
{
    RT_ASSERT(0);
}

/**
 * This function will initialize beaglebone board
 */
void rt_hw_board_init(void)
{
    Xil_AssertSetCallback(rt_xil_assert_callback);

    /* initialize hardware interrupt */
    rt_hw_interrupt_init();
    /* initialize system heap */
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);

    rt_hw_pin_init();

    rt_components_board_init();

    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);

    rt_thread_idle_sethook(idle_wfi);

#ifdef RT_USING_SMP
    /* install IPI handle */
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
#endif

    rt_assert_set_hook(_assert_hook);
}

#include "xil_io.h"
#define PSS_RST_CTRL_REG 0xF8000200
#define SLCR_UNLOCK_ADDR 0xF8000008
#define UNLOCK_KEY 0xDF0D
#define PSS_RST_MASK 0x01

static void zynq_hw_software_reset(void)
{
    Xil_Out32(SLCR_UNLOCK_ADDR, UNLOCK_KEY);
    Xil_Out32(PSS_RST_CTRL_REG, PSS_RST_MASK);
}
MSH_CMD_EXPORT_ALIAS(zynq_hw_software_reset, reboot, soft reboot);
