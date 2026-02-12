#include "rtconfig.h"

#ifdef BSP_USING_AT24C02_INIT

#include "at24c02.h"

at24cxx_device_t gd32_at24c02 = RT_NULL;

static int init_gd32_at24c02(void)
{
    rt_err_t result = RT_EOK;

    gd32_at24c02 = at24cxx_init(AT24C02_I2C_NAME, AT24C02_ADDR_INPUT);

    if (gd32_at24c02 == RT_NULL)
    {
        rt_kprintf("AT24C02 initialization failed\n");
        return -RT_ERROR;
    }

    result = at24cxx_check(gd32_at24c02);

    if (result == -RT_ERROR)
    {
        rt_kprintf("AT24C02 check failed\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}


INIT_DEVICE_EXPORT(init_gd32_at24c02);

#endif