/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/02/22     flyingcys    first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_adc.h"
#include "drv_pinmux.h"
#include "drv_ioremap.h"

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.ADC"

rt_inline void cvi_set_saradc_ctrl(unsigned long reg_base, rt_uint32_t value)
{
    value |= mmio_read_32(reg_base + SARADC_CTRL_OFFSET);
    mmio_write_32(reg_base + SARADC_CTRL_OFFSET, value);
}

rt_inline void cvi_reset_saradc_ctrl(unsigned long reg_base, rt_uint32_t value)
{
    value = mmio_read_32(reg_base + SARADC_CTRL_OFFSET) & ~value;
    mmio_write_32(reg_base + SARADC_CTRL_OFFSET, value);
}

rt_inline rt_uint32_t cvi_get_saradc_status(unsigned long reg_base)
{
    return((rt_uint32_t)mmio_read_32(reg_base + SARADC_STATUS_OFFSET));
}

rt_inline void cvi_set_cyc(unsigned long reg_base)
{
    rt_uint32_t value;

    value = mmio_read_32(reg_base + SARADC_CYC_SET_OFFSET);

    value &= ~SARADC_CYC_CLKDIV_DIV_16;
    mmio_write_32(reg_base + SARADC_CYC_SET_OFFSET, value);

    value |= SARADC_CYC_CLKDIV_DIV_16;                                                               //set saradc clock cycle=840ns
    mmio_write_32(reg_base + SARADC_CYC_SET_OFFSET, value);
}

rt_inline void cvi_do_calibration(unsigned long reg_base)
{
    rt_uint32_t val;

    val = mmio_read_32(reg_base + SARADC_TEST_OFFSET);
    val |= 1 << SARADC_TEST_VREFSEL_BIT;
    mmio_write_32(reg_base + SARADC_TEST_OFFSET, val);

    val = mmio_read_32(reg_base + SARADC_TRIM_OFFSET);
    val |= 0x4;
    mmio_write_32(reg_base + SARADC_TRIM_OFFSET, val);
}

struct cvi_adc_dev
{
    struct rt_adc_device device;
    const char *name;
    rt_ubase_t base;
};

static struct cvi_adc_dev adc_dev_config[] =
{
#ifdef BSP_USING_ADC_ACTIVE
    {
        .name = "adc1",
        .base = SARADC_BASE
    },
#endif /* BSP_USING_ADC_ACTIVE */
#ifdef BSP_USING_ADC_NODIE
    {
        .name = "adc2",
        .base = RTC_ADC_BASE
    },
#endif /* BSP_USING_ADC_NODIE */
};

static rt_err_t _adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    struct cvi_adc_dev *adc_dev = (struct cvi_adc_dev *)device->parent.user_data;
    uint32_t value;

    RT_ASSERT(adc_dev != RT_NULL);

    if (channel > SARADC_CH_MAX)
        return -RT_EINVAL;

    if (enabled)
    {
        //set channel
        cvi_set_saradc_ctrl(adc_dev->base, (rt_uint32_t)channel << (SARADC_CTRL_SEL_POS + 1));

        //set saradc clock cycle
        cvi_set_cyc(adc_dev->base);

        //start
        cvi_set_saradc_ctrl(adc_dev->base, SARADC_CTRL_START);
        LOG_D("enable saradc...");
    }
    else
    {
        cvi_reset_saradc_ctrl(adc_dev->base, (rt_uint32_t)channel << (SARADC_CTRL_SEL_POS + 1));
        LOG_D("disable saradc...");
    }
    return RT_EOK;
}

static rt_err_t _adc_convert(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    struct cvi_adc_dev *adc_dev = (struct cvi_adc_dev *)device->parent.user_data;
    rt_uint32_t result;
    rt_uint32_t cnt = 0;

    RT_ASSERT(adc_dev != RT_NULL);

    if (channel > SARADC_CH_MAX)
        return -RT_EINVAL;

    while (cvi_get_saradc_status(adc_dev->base) & SARADC_STATUS_BUSY)
    {
        rt_thread_delay(10);
        LOG_D("wait saradc ready");
        cnt ++;
        if (cnt > 100)
            return -RT_ETIMEOUT;
    }

    result = mmio_read_32(adc_dev->base + SARADC_RESULT(channel - 1));
    if (result & SARADC_RESULT_VALID)
    {
        *value = result & SARADC_RESULT_MASK;
        LOG_D("saradc channel %d value: %04x", channel, *value);
    }
    else
    {
        LOG_E("saradc channel %d read failed. result:0x%04x", channel, result);
        return -RT_ERROR;
    }
    return RT_EOK;
}

static const struct rt_adc_ops _adc_ops =
{
    .enabled = _adc_enabled,
    .convert = _adc_convert,
};


#if defined(BOARD_TYPE_MILKV_DUO) || defined(BOARD_TYPE_MILKV_DUO_SPINOR)

/*
 * cv180xb supports
 * - adc1 & adc2 for active domain
 * - adc3 for no-die domain
 */
#ifdef BSP_USING_ADC_ACTIVE
static const char *pinname_whitelist_adc1_active[] = {
    "ADC1",
    NULL,
};
static const char *pinname_whitelist_adc2_active[] = {
    NULL,
};
static const char *pinname_whitelist_adc3_active[] = {
    NULL,
};
#endif

#ifdef BSP_USING_ADC_NODIE
static const char *pinname_whitelist_adc1_nodie[] = {
    "PWR_GPIO2",
    NULL,
};
static const char *pinname_whitelist_adc2_nodie[] = {
    "PWR_GPIO1",
    NULL,
};
static const char *pinname_whitelist_adc3_nodie[] = {
    "PWR_VBAT_DET",
    NULL,
};
#endif

#elif defined(BOARD_TYPE_MILKV_DUO256M) || defined(BOARD_TYPE_MILKV_DUO256M_SPINOR)

/*
 * sg2002 supports
 * - adc1 for active domain
 * - adc1/adc2/adc3 for no-die domain
 */

#ifdef BSP_USING_ADC_ACTIVE
static const char *pinname_whitelist_adc1_active[] = {
    "ADC1",
    NULL,
};
static const char *pinname_whitelist_adc2_active[] = {
    NULL,
};
static const char *pinname_whitelist_adc3_active[] = {
    NULL,
};
#endif

#ifdef BSP_USING_ADC_NODIE
static const char *pinname_whitelist_adc1_nodie[] = {
    "PWR_GPIO2",
    NULL,
};
static const char *pinname_whitelist_adc2_nodie[] = {
    "PWR_GPIO1",
    NULL,
};
static const char *pinname_whitelist_adc3_nodie[] = {
    "PWR_VBAT_DET",
    NULL,
};
#endif

#else
    #error "Unsupported board type!"
#endif

static void rt_hw_adc_pinmux_config()
{
#ifdef BSP_USING_ADC_ACTIVE
    pinmux_config(BSP_ACTIVE_ADC1_PINNAME, XGPIOB_3, pinname_whitelist_adc1_active);
    pinmux_config(BSP_ACTIVE_ADC2_PINNAME, XGPIOB_6, pinname_whitelist_adc2_active);
    /* cv1800b & sg2002 don't support ADC3 either in active domain */
#endif

#ifdef BSP_USING_ADC_NODIE
    pinmux_config(BSP_NODIE_ADC1_PINNAME, PWR_GPIO_2, pinname_whitelist_adc1_nodie);
    pinmux_config(BSP_NODIE_ADC2_PINNAME, PWR_GPIO_1, pinname_whitelist_adc2_nodie);
    pinmux_config(BSP_NODIE_ADC3_PINNAME, PWR_VBAT_DET, pinname_whitelist_adc3_nodie);
#endif
}

int rt_hw_adc_init(void)
{
    rt_uint8_t i;

    for (i = 0; i < sizeof(adc_dev_config) / sizeof(adc_dev_config[0]); i++)
    {
        if (!rt_strcmp(adc_dev_config[i].name, "adc1"))
        {
            adc_dev_config[i].base = (rt_ubase_t)DRV_IOREMAP(SARADC_BASE, 0x10000);
        }
        else if (!rt_strcmp(adc_dev_config[i].name, "adc2"))
        {
            adc_dev_config[i].base = (rt_ubase_t)DRV_IOREMAP(RTC_ADC_BASE, 0x1000);
        }
    }

    rt_hw_adc_pinmux_config();

    for (i = 0; i < sizeof(adc_dev_config) / sizeof(adc_dev_config[0]); i++)
    {
        cvi_do_calibration(adc_dev_config[i].base);

        if (rt_hw_adc_register(&adc_dev_config[i].device, adc_dev_config[i].name, &_adc_ops, &adc_dev_config[i]) != RT_EOK)
        {
            LOG_E("%s register failed!", adc_dev_config[i].name);
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_adc_init);
