/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-11-11      Wayne        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_SLCD)

#include <rtthread.h>
#include <rtdevice.h>
#include <sys/time.h>

#include "slcd_rhe6616tp01.h"

#if defined(RT_USING_NETDEV)
    #if defined(RT_USING_SAL)
        #include <arpa/inet.h>
    #elif defined(RT_USING_LWIP)
        #include <lwip/inet.h>
    #endif /* RT_USING_SAL */
    #include <netdev.h>
#endif

const uint32_t au32SLCDSymbols [] =
{
    SYMBOL_NVT,
    SYMBOL_WIFI,
    SYMBOL_SOUND,
    SYMBOL_NUMICRO,
    SYMBOL_BAT_FRAME,
    SYMBOL_BAT_1,
    SYMBOL_BAT_2,
    SYMBOL_BAT_3,
    SYMBOL_PLUS,
    SYMBOL_MINUS,
    SYMBOL_V,
    SYMBOL_A,
    SYMBOL_W,
    SYMBOL_ARROW_UP,
    SYMBOL_ARROW_LEFT,
    SYMBOL_ARROW_DOWN,
    SYMBOL_ARROW_RIGHT,
    SYMBOL_CIRCLE_UP,
    SYMBOL_CIRCLE_LEFT,
    SYMBOL_CIRCLE_RIGHT,
    SYMBOL_PERCENTAGE,
    SYMBOL_PPM,
    SYMBOL_TEMP_C,
    SYMBOL_TEMP_F,
    SYMBOL_VERSION,
    SYMBOL_MAIN_DIG_COL1,
    SYMBOL_MAIN_DIG_COL2,
    SYMBOL_MAIN_DIG_COL3,
    SYMBOL_MAIN_DIG_COL4,
    SYMBOL_MAIN_DIG_COL5,
    SYMBOL_MAIN_DIG_COL6,
    SYMBOL_MAIN_DIG_P1,
    SYMBOL_MAIN_DIG_P2,
    SYMBOL_MAIN_DIG_P3,
    SYMBOL_MAIN_DIG_P4,
    SYMBOL_MAIN_DIG_P5,
    SYMBOL_MAIN_DIG_P6,
    SYMBOL_VER_DIG_P1,
    SYMBOL_VER_DIG_P2,
    SYMBOL_TIME_DIG_COL1,
    SYMBOL_TIME_DIG_P1,
    SYMBOL_TIME_DIG_P2,
    SYMBOL_TIME_DIG_P3
};
const int i32SLCDSymbolsSize  = sizeof(au32SLCDSymbols) / sizeof(au32SLCDSymbols[0]);

void slcd_demo_hook(void)
{
    static uint32_t u32NextShowTime = 0;
    static uint32_t u32ShownTime = 0;
    uint32_t u32CurTickCount = rt_tick_get();
    char au8Str[16];

    if (u32CurTickCount < u32NextShowTime)
        return;

    u32NextShowTime = u32CurTickCount + 500;
    u32ShownTime++;

    /* Show NuMicro Log. */
    {
        LCDLIB_SetSymbol(SYMBOL_NVT, 1);
        LCDLIB_SetSymbol(SYMBOL_NUMICRO, 1);
        LCDLIB_SetSymbol(SYMBOL_ARROW_UP, 1);
        LCDLIB_SetSymbol(SYMBOL_ARROW_LEFT, 1);
        LCDLIB_SetSymbol(SYMBOL_ARROW_DOWN, 1);
        LCDLIB_SetSymbol(SYMBOL_ARROW_RIGHT, 1);
        LCDLIB_SetSymbol(SYMBOL_CIRCLE_UP, 1);
        LCDLIB_SetSymbol(SYMBOL_CIRCLE_LEFT, 1);
        LCDLIB_SetSymbol(SYMBOL_CIRCLE_RIGHT,  1);
    }
    {
        struct tm *g_pstm;
        time_t now;
        /* output current time */
        now = time(RT_NULL);
        g_pstm = localtime(&now);
        rt_snprintf(au8Str, sizeof(au8Str), "%02d%02d", g_pstm->tm_hour, g_pstm->tm_min);
        LCDLIB_Printf(ZONE_TIME_DIGIT, &au8Str[0]);
        LCDLIB_SetSymbol(SYMBOL_TIME_DIG_COL1, u32ShownTime % 2);

        rt_snprintf(au8Str, sizeof(au8Str), "-%02d", g_pstm->tm_sec);
        LCDLIB_Printf(ZONE_NUMICRO_DIGIT, &au8Str[0]);
    }
    /* Show RTT version. */
    {
        LCDLIB_SetSymbol(SYMBOL_VERSION, 1);
        rt_snprintf(au8Str, sizeof(au8Str), "%d%02d%03d", RT_VERSION_MAJOR, RT_VERSION_MINOR, RT_VERSION_PATCH);
        LCDLIB_Printf(ZONE_VER_DIGIT, &au8Str[0]);
        LCDLIB_SetSymbol(SYMBOL_VER_DIG_P1, 1);
        LCDLIB_SetSymbol(SYMBOL_VER_DIG_P2, 1);
    }

#if defined(RT_USING_NETDEV)
    /* Show Wi-Fi connective if leased an ip address. */
    {
        struct netdev *netdev = netdev_get_by_name("esp0");
        LCDLIB_SetSymbol(SYMBOL_WIFI, netdev_is_dhcp_enabled(netdev));
    }
#endif

    /* Travel all dots */
    LCDLIB_SetSymbol(SYMBOL_S(u32ShownTime % 40 + 1), (u32ShownTime / 40) % 2);
}

static int slcd_demo_init(void)
{
    rt_err_t err = rt_thread_idle_sethook(slcd_demo_hook);

    if (err != RT_EOK)
    {
        rt_kprintf("set idle hook failed!\n");
        return -1;
    }

    return 0;
}
INIT_APP_EXPORT(slcd_demo_init);

#endif /* #if defined(BSP_USING_SLCD) */
