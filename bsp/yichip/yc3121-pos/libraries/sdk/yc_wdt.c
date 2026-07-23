#include "yc_wdt.h"

#define WDT_ENABLE_BIT_Mask     6
#define WDT_MODE_BIT_Mask       5
#define SYSCTRL_WDT_EN_BIT_Mask 1

/**************the value of feed dog************/
#define COUNTER_RELOAD_KEY      0x5937

void WDT_SetReload(uint32_t Reload)
{
    uint32_t wdt_config = 0;

    _ASSERT(ISWDTRELOAD(Reload));

    wdt_config = WD_CONFIG;
    wdt_config &= 0xE0;
    wdt_config |= Reload;
    WD_CONFIG = wdt_config;
}

void WDT_ReloadCounter(void)
{
    WD_KICK = COUNTER_RELOAD_KEY;
}

void WDT_Enable(void)
{
    WD_CONFIG |= (1 << WDT_ENABLE_BIT_Mask);
}

void WDT_ModeConfig(WDT_ModeTypeDef WDT_Mode)
{
    WD_CONFIG &= ~(1 << WDT_MODE_BIT_Mask);
    WD_CONFIG |= (WDT_Mode << WDT_MODE_BIT_Mask);
    if (WDT_CPUReset == WDT_Mode)
    {
        SYSCTRL_RST_EN |= (1 << 1);
    }
    else
    {
        SYSCTRL_RST_EN &= ~(1 << 1);
    }
}

ITStatus WDT_GetITStatus(void)
{
    return (ITStatus)(WD_KICK & 1);
}

void WDT_ClearITPendingBit(void)
{
    WD_CLEAR = 1;
}
