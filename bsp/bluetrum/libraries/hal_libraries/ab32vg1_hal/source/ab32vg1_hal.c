#include "ab32vg1_hal.h"

static uint32_t hw_ticks = 0;

static void (*tick_cfg_hook)(uint32_t ticks) = HAL_NULL;

void hal_set_tick_hook(void (*hook)(uint32_t ticks))
{
    tick_cfg_hook = hook;
}

void hal_set_ticks(uint32_t ticks)
{
    if (ticks != hw_ticks) {
        hw_ticks = ticks;
    }
    if (tick_cfg_hook != HAL_NULL) {
        tick_cfg_hook(hw_ticks);
    }
}

WEAK void hal_mdelay(uint32_t nms)
{

}

void hal_udelay(uint16_t nus)
{
   int i;
   for (i = 0; i < nus*10; i++) {
        asm("nop");
   }
}

WEAK void hal_printf(const char *fmt, ...)
{}
