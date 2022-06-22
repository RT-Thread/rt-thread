/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/11/29     Bernard      the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "drv_uart.h"

#include "pin_mux.h"
#include "clock_config.h"

#include <fsl_clock.h>
#include <fsl_intmux.h>

void LPIT0_IRQHandler(void)
{
    rt_tick_increase();

    SystemClearSystickFlag();
}

int rt_hw_systick_init(void)
{
    CLOCK_SetIpSrc(kCLOCK_Lpit0, kCLOCK_IpSrcFircAsync);

    SystemSetupSystick (RT_TICK_PER_SECOND, 0);
    SystemClearSystickFlag();

    return 0;
}

const scg_lpfll_config_t g_appScgLpFllConfig_BOARD_BootClockRUN = {
    .enableMode = kSCG_LpFllEnable, /* LPFLL clock disabled */
    .div1 = kSCG_AsyncClkDivBy1,    /* Low Power FLL Clock Divider 1: Clock output is disabled */
    .div2 = kSCG_AsyncClkDisable,   /* Low Power FLL Clock Divider 2: Clock output is disabled */
    .div3 = kSCG_AsyncClkDisable,   /* Low Power FLL Clock Divider 3: Clock output is disabled */
    .range = kSCG_LpFllRange72M,    /* LPFLL is trimmed to 72MHz */
    .trimConfig = NULL,
};

void rt_hw_board_init(void)
{
    BOARD_InitPins();
    BOARD_BootClockRUN();
    /* Init LPFLL */
    CLOCK_InitLpFll(&g_appScgLpFllConfig_BOARD_BootClockRUN);

    INTMUX_Init(INTMUX0);
    INTMUX_EnableInterrupt(INTMUX0, 0, PORTC_IRQn);

    /* initialize hardware interrupt */
    rt_hw_uart_init();
    rt_hw_systick_init();

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    /* set console device */
    rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_system_heap_init(RT_HW_HEAP_BEGIN, RT_HW_HEAP_END);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}
