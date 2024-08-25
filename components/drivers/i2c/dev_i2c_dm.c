/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#include <rtdevice.h>

#define DBG_TAG "dev.i2c.dm"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_OFW
static void i2c_parse_timing(struct rt_ofw_node *dev_np, const char *propname,
        rt_uint32_t *out_value, rt_uint32_t def_value, rt_bool_t use_defaults)
{
    if (rt_ofw_prop_read_u32(dev_np, propname, out_value) && use_defaults)
    {
        *out_value = def_value;
    }
}

rt_err_t i2c_timings_ofw_parse(struct rt_ofw_node *dev_np, struct i2c_timings *timings,
        rt_bool_t use_defaults)
{
    rt_ubase_t def;
    rt_bool_t udef = use_defaults;
    struct i2c_timings *t = timings;

    i2c_parse_timing(dev_np, "clock-frequency", &t->bus_freq_hz, I2C_MAX_STANDARD_MODE_FREQ, udef);

    def = t->bus_freq_hz <= I2C_MAX_STANDARD_MODE_FREQ ? 1000 : t->bus_freq_hz <= I2C_MAX_FAST_MODE_FREQ ? 300 : 120;
    i2c_parse_timing(dev_np, "i2c-scl-rising-time-ns", &t->scl_rise_ns, def, udef);

    def = t->bus_freq_hz <= I2C_MAX_FAST_MODE_FREQ ? 300 : 120;
    i2c_parse_timing(dev_np, "i2c-scl-falling-time-ns", &t->scl_fall_ns, def, udef);

    i2c_parse_timing(dev_np, "i2c-scl-internal-delay-ns", &t->scl_int_delay_ns, 0, udef);
    i2c_parse_timing(dev_np, "i2c-sda-falling-time-ns", &t->sda_fall_ns, t->scl_fall_ns, udef);
    i2c_parse_timing(dev_np, "i2c-sda-hold-time-ns", &t->sda_hold_ns, 0, udef);
    i2c_parse_timing(dev_np, "i2c-digital-filter-width-ns", &t->digital_filter_width_ns, 0, udef);
    i2c_parse_timing(dev_np, "i2c-analog-filter-cutoff-frequency", &t->analog_filter_cutoff_freq_hz, 0, udef);

    return RT_EOK;
}
#endif /* RT_USING_OFW */
