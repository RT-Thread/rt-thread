/*
 * Copyright (c) 2019 Winner Microelectronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-09-15     flyingcys    1st version
 */

#include <rthw.h>
#include <rtthread.h>
#include "wm_type_def.h"
#include "misc.h"
#include "wm_cpu.h"
#include "wm_debug.h"
#include "wm_io.h"
#include "wm_gpio_afsel.h"
#include "wm_crypto_hard.h"
#include "wm_hostspi.h"
#include "wm_flash.h"
#include "wm_internal_flash.h"
#include "wm_fwup.h"
#include "wm_pmu.h"
#include "drv_uart.h"
#include "board.h"

#define FW_MAJOR_VER           0x03
#define FW_MINOR_VER           0x00
#define FW_PATCH_VER           0x00

const char FirmWareVer[4] =
{
    'G',
    FW_MAJOR_VER,  /* Main version */
    FW_MINOR_VER,  /* Subversion */
    FW_PATCH_VER   /* Internal version */
};
const char HwVer[6] =
{
    'H',
    0x1,
    0x0,
    0x0,
    0x0,
    0x0
};

const unsigned int HZ = RT_TICK_PER_SECOND;

struct tls_ethif *tls_netif_get_ethif(void)
{
    return RT_NULL;
}

int tls_os_get_type(void)
{
    return 0;
}

err_t tls_dhcp_stop(void)
{
    return 0;
}

u8 tls_get_isr_count(void)
{
    return 0;
}

void *mem_alloc_debug(u32 size)
{
    return rt_malloc(size);
}

void mem_free_debug(void *p)
{
    rt_free(p);
}

void disp_version_info(void)
{
    extern const char WiFiVer[];
    TLS_DBGPRT_INFO("\n\n");
    TLS_DBGPRT_INFO("****************************************************************\n");
    TLS_DBGPRT_INFO("*                                                              *\n");
    TLS_DBGPRT_INFO("* Copyright (C) 2014 WinnerMicro Co. Ltd.                      *\n");
    TLS_DBGPRT_INFO("* All rights reserved.                                         *\n");
    TLS_DBGPRT_INFO("* WinnerMicro Firmware Version: %x.%x.%X                         *\n",
                    FirmWareVer[1], FirmWareVer[2], FirmWareVer[3]);
    TLS_DBGPRT_INFO("* WinnerMicro Hardware Version: %x.%x.%x.%x.%x                      *\n",
                    HwVer[1], HwVer[2], HwVer[3], HwVer[4], HwVer[5]);
    TLS_DBGPRT_INFO("*                                                              *\n");
    TLS_DBGPRT_INFO("* WinnerMicro Wi-Fi Lib Version: %x.%x.%x                         *\n",
                    WiFiVer[0], WiFiVer[1], WiFiVer[2]);
    TLS_DBGPRT_INFO("****************************************************************\n");
}

void wm_gpio_config(void)
{
	/* must call first */
	wm_gpio_af_disable();

	/*MASTER SPI configuratioin*/
	wm_spi_cs_config(WM_IO_PA_02);
	wm_spi_ck_config(WM_IO_PA_11);
	wm_spi_di_config(WM_IO_PA_03);
	wm_spi_do_config(WM_IO_PA_09);
}

static int wm_infsl_init(void)
{
    tls_spi_init();
    tls_spifls_init();
    tls_fls_init();

    /*initialize flash layout parameter according to image type*/
    tls_fls_layout_init();

    return 0;
}
INIT_DEVICE_EXPORT(wm_infsl_init);

static void _idle_hook_callback(void)
{
#if !defined(__CC_ARM)
    __asm volatile ("wfi");
#else
    __asm
    {
        WFI;
    }
#endif
}

static void _thread_inited_hook(rt_thread_t thread)
{
    rt_uint32_t stack_size, stk_start;

    stack_size = (rt_uint32_t)thread->stack_size;
    stk_start = (rt_uint32_t)thread->stack_addr;

    if ((stk_start + stack_size) >= TASK_STACK_USING_MEM_UPPER_RANGE)
    {
        rt_kprintf("thread[%s] stack only between 0x%08x and 0x%08x, please use rt_create_thread()!!\n",
                   thread->name, TASK_STACK_USING_MEM_LOWER_RANGE, TASK_STACK_USING_MEM_UPPER_RANGE);
    }
    RT_ASSERT((stk_start + stack_size) < TASK_STACK_USING_MEM_UPPER_RANGE);
}

void wm_sys_clk_config(void)
{
    tls_sys_clk sysclk;

    tls_sys_clk_set(CPU_CLK_80M);
    tls_sys_clk_get(&sysclk);
    SysTick_Config(sysclk.cpuclk * UNIT_MHZ / RT_TICK_PER_SECOND);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    tls_pmu_clk_select(0);
}

/**
 * This is the timer interrupt service routine.
 *
 */
void OS_CPU_SysTickHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/**
 * This function will initial board.
 */
void rt_hw_board_init(void)
{
    /* must call first to configure gpio Alternate functions according the hardware design */
    wm_gpio_config();

    wm_sys_clk_config();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#ifdef RT_USING_CONSOLE
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#if TLS_CONFIG_HARD_CRYPTO
    tls_crypto_init();
#endif

    NVIC_SystemLPConfig(NVIC_LP_SLEEPDEEP, ENABLE);
    rt_thread_idle_sethook(_idle_hook_callback);
    rt_thread_inited_sethook(_thread_inited_hook);
}

#include <wm_watchdog.h>
void rt_hw_cpu_reset(void)
{
    extern void tls_sys_reset(void);
    tls_sys_reset();
}

#ifdef RT_USING_FINSH
#include <finsh.h>
static void reboot(uint8_t argc, char **argv)
{
    rt_hw_cpu_reset();
}
FINSH_FUNCTION_EXPORT_ALIAS(reboot, __cmd_reboot, Reboot System);
#endif /* RT_USING_FINSH */

/*@}*/
