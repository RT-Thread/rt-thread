#include <rtdef.h>
#include "drv_ioremap.h"

static rt_ubase_t pinmux_base = RT_NULL;

rt_ubase_t pinmux_base_ioremap(void)
{
    if (pinmux_base == RT_NULL)
    {
        pinmux_base = (rt_size_t)rt_ioremap((void*)0x03001000, 0x1000);
    }

    return pinmux_base;
}
