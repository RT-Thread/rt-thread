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

#include "slcd_rhe6616tp01.h"

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
    uint32_t u32CurTickCount = rt_tick_get();

    /* ZONE_MAIN_DIGIT */
    LCDLIB_PrintNumber(ZONE_MAIN_DIGIT, u32CurTickCount);

    /* ZONE_PPM_DIGIT */
    LCDLIB_PrintNumber(ZONE_PPM_DIGIT, u32CurTickCount);

    /* ZONE_TEMP_DIGIT */
    LCDLIB_PrintNumber(ZONE_TEMP_DIGIT, u32CurTickCount);

    /* ZONE_VER_DIGIT */
    LCDLIB_PrintNumber(ZONE_VER_DIGIT, u32CurTickCount);

    /* ZONE_TIME_DIGIT */
    LCDLIB_PrintNumber(ZONE_TIME_DIGIT, u32CurTickCount);

    /* ZONE_NUMICRO_DIGIT */
    LCDLIB_PrintNumber(ZONE_NUMICRO_DIGIT, u32CurTickCount);

    /* Travel all symbols */
    LCDLIB_SetSymbol(au32SLCDSymbols[u32CurTickCount % i32SLCDSymbolsSize], (u32CurTickCount / i32SLCDSymbolsSize) % 2);

    /* Travel all dots */
    LCDLIB_SetSymbol(SYMBOL_S(u32CurTickCount % 40 + 1), (u32CurTickCount / 40) % 2);
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
