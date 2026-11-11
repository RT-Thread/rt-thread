/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author              Notes
 * 2021-07-29       KyleChan            first version
 * 2026-07-15       rain                RA Wireless GPIO adapter
 */

#include <drv_gpio_w.h>

#ifdef RT_USING_PIN
#ifdef R_EXT_IRQ_W_H

#define DBG_TAG              "drv.gpio.wireless"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */

#define RA_WIRELESS_EXT_IRQ_MAX_CHANNEL    30

static struct rt_pin_irq_hdr pin_irq_hdr_tab[RA_WIRELESS_EXT_IRQ_MAX_CHANNEL] = {0};
static ext_irq_w_instance_ctrl_t ra_ext_irq_ctrl_tab[RA_WIRELESS_EXT_IRQ_MAX_CHANNEL];
static ext_irq_w_extended_cfg_t ra_ext_irq_extend_tab[RA_WIRELESS_EXT_IRQ_MAX_CHANNEL];
static external_irq_cfg_t ra_ext_irq_cfg_tab[RA_WIRELESS_EXT_IRQ_MAX_CHANNEL];
static rt_int32_t ra_ext_irq_pin_to_channel[RA_WIRELESS_EXT_IRQ_MAX_CHANNEL];

static void ra_irq_tab_init(void)
{
    for (int i = 0; i < RA_WIRELESS_EXT_IRQ_MAX_CHANNEL; ++i)
    {
        pin_irq_hdr_tab[i].pin  = -1;
        pin_irq_hdr_tab[i].mode = 0;
        pin_irq_hdr_tab[i].args = RT_NULL;
        pin_irq_hdr_tab[i].hdr  = RT_NULL;
        ra_ext_irq_pin_to_channel[i] = -1;
    }
}

static rt_int32_t ra_pin_find_irq_channel(rt_uint32_t pin)
{
    for (int i = 0; i < RA_WIRELESS_EXT_IRQ_MAX_CHANNEL; ++i)
    {
        if (ra_ext_irq_pin_to_channel[i] == (rt_int32_t) pin)
        {
            return i;
        }
    }

    return -1;
}

static rt_int32_t ra_pin_alloc_irq_channel(rt_uint32_t pin)
{
    rt_int32_t channel = ra_pin_find_irq_channel(pin);

    if (channel >= 0)
    {
        return channel;
    }

    for (int i = 0; i < RA_WIRELESS_EXT_IRQ_MAX_CHANNEL; ++i)
    {
        if (ra_ext_irq_pin_to_channel[i] < 0)
        {
            ra_ext_irq_pin_to_channel[i] = (rt_int32_t) pin;
            return i;
        }
    }

    return -1;
}

static rt_bool_t ra_wireless_pin_valid(rt_base_t pin)
{
    rt_uint32_t port;
    rt_uint32_t pin_id;

    if (pin < 0)
    {
        return RT_FALSE;
    }

    port = ((rt_uint32_t) pin & BSP_IO_PORT_BITS) >> BSP_IO_PORT_OFFSET;
    pin_id = (rt_uint32_t) pin & BSP_IO_PIN_BITS;

    return (((BSP_IO_PORT_00 == port) && (pin_id < BSP_FEATURE_IO_PORT0_GPIO_COUNT)) ||
            ((BSP_IO_PORT_01 == port) && (pin_id < BSP_FEATURE_IO_PORT1_GPIO_COUNT)));
}

static rt_bool_t ra_ext_irq_w_pin_supported(rt_base_t pin)
{
    rt_uint32_t port;
    rt_uint32_t pin_id;

    if (pin < 0)
    {
        return RT_FALSE;
    }

    port = ((rt_uint32_t) pin & BSP_IO_PORT_BITS) >> BSP_IO_PORT_OFFSET;
    pin_id = (rt_uint32_t) pin & BSP_IO_PIN_BITS;

    return (((BSP_IO_PORT_00 == port) && (pin_id <= 13U)) ||
            ((BSP_IO_PORT_01 == port) && (pin_id <= 15U)));
}

static external_irq_trigger_t ra_pin_irq_mode_to_trigger(rt_uint8_t mode)
{
    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        return EXTERNAL_IRQ_TRIG_RISING;
    case PIN_IRQ_MODE_FALLING:
        return EXTERNAL_IRQ_TRIG_FALLING;
    case PIN_IRQ_MODE_HIGH_LEVEL:
        return EXTERNAL_IRQ_TRIG_LEVEL_HIGH;
    case PIN_IRQ_MODE_LOW_LEVEL:
        return EXTERNAL_IRQ_TRIG_LEVEL_LOW;
    default:
        return (external_irq_trigger_t) -1;
    }
}

static void ra_ext_irq_w_callback(external_irq_callback_args_t *p_args)
{
    struct rt_pin_irq_hdr *irq_hdr = (struct rt_pin_irq_hdr *) p_args->p_context;

    rt_interrupt_enter();
    if ((RT_NULL != irq_hdr) && (RT_NULL != irq_hdr->hdr))
    {
        irq_hdr->hdr(irq_hdr->args);
    }
    rt_interrupt_leave();
}

static void ra_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    fsp_err_t err;
    uint32_t cfg;

    RT_UNUSED(dev);

    if (!ra_wireless_pin_valid(pin))
    {
        LOG_E("invalid pin: 0x%x", pin);
        return;
    }

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        cfg = GPIO_W_CFG_PORT_DIRECTION_OUTPUT;
        break;

    case PIN_MODE_INPUT:
        cfg = GPIO_W_CFG_PORT_DIRECTION_INPUT;
        break;

    case PIN_MODE_INPUT_PULLUP:
        cfg = GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_PULLUP_ENABLE;
        break;

    case PIN_MODE_INPUT_PULLDOWN:
        cfg = GPIO_W_CFG_PORT_DIRECTION_INPUT | GPIO_W_CFG_PULLDOWN_ENABLE;
        break;

    case PIN_MODE_OUTPUT_OD:
        cfg = GPIO_W_CFG_OPEN_DRAIN_ENABLE;
        break;

    default:
        LOG_E("unsupported pin mode: %d", mode);
        return;
    }

    err = R_IOPORT_PinCfg(&g_ioport_ctrl, (bsp_io_port_pin_t) pin, cfg);
    if (err != FSP_SUCCESS)
    {
        LOG_E("pin mode configuration failed: %d", err);
    }
}

static void ra_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    bsp_io_level_t level = BSP_IO_LEVEL_HIGH;

    RT_UNUSED(dev);

    if (!ra_wireless_pin_valid(pin))
    {
        LOG_E("invalid pin: 0x%x", pin);
        return;
    }

    if (value != level)
    {
        level = BSP_IO_LEVEL_LOW;
    }

    R_BSP_PinAccessEnable();
    R_BSP_PinWrite(pin, level);
    R_BSP_PinAccessDisable();
}

static rt_ssize_t ra_pin_read(rt_device_t dev, rt_base_t pin)
{
    RT_UNUSED(dev);

    if (!ra_wireless_pin_valid(pin))
    {
        return -RT_EINVAL;
    }
    return R_BSP_PinRead(pin);
}

static rt_err_t ra_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    fsp_err_t err;
    rt_int32_t irqx = ra_pin_find_irq_channel((rt_uint32_t) pin);

    RT_UNUSED(device);

    if ((irqx < 0) || (irqx >= RA_WIRELESS_EXT_IRQ_MAX_CHANNEL))
    {
        return -RT_ERROR;
    }

    if (PIN_IRQ_ENABLE == enabled)
    {
        err = R_EXT_IRQ_W_ExternalIrqOpen((external_irq_ctrl_t *) &ra_ext_irq_ctrl_tab[irqx],
                                          (external_irq_cfg_t const *) &ra_ext_irq_cfg_tab[irqx]);
        if ((FSP_SUCCESS != err) && (FSP_ERR_ALREADY_OPEN != err))
        {
            LOG_E("R_EXT_IRQ_W_ExternalIrqOpen failed: %d", err);
            return -RT_ERROR;
        }

        err = R_EXT_IRQ_W_ExternalIrqEnable((external_irq_ctrl_t *) &ra_ext_irq_ctrl_tab[irqx]);
        if (FSP_SUCCESS != err)
        {
            LOG_E("R_EXT_IRQ_W_ExternalIrqEnable failed: %d", err);
            return -RT_ERROR;
        }
    }
    else if (PIN_IRQ_DISABLE == enabled)
    {
        err = R_EXT_IRQ_W_ExternalIrqDisable((external_irq_ctrl_t *) &ra_ext_irq_ctrl_tab[irqx]);
        if ((FSP_SUCCESS != err) && (FSP_ERR_NOT_OPEN != err))
        {
            LOG_E("R_EXT_IRQ_W_ExternalIrqDisable failed: %d", err);
            return -RT_ERROR;
        }

        err = R_EXT_IRQ_W_ExternalIrqClose((external_irq_ctrl_t *) &ra_ext_irq_ctrl_tab[irqx]);
        if ((FSP_SUCCESS != err) && (FSP_ERR_NOT_OPEN != err))
        {
            LOG_E("R_EXT_IRQ_W_ExternalIrqClose failed: %d", err);
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}

static rt_err_t ra_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                  rt_uint8_t   mode, void (*hdr)(void *args), void *args)
{
    rt_int32_t irqx;
    external_irq_trigger_t trigger = ra_pin_irq_mode_to_trigger(mode);

    if (((external_irq_trigger_t) -1) == trigger)
    {
        LOG_W("RA Wireless EXT IRQ does not support mode %d", mode);
        return -RT_EINVAL;
    }

    RT_UNUSED(device);

    if (!ra_ext_irq_w_pin_supported(pin))
    {
        return -RT_EINVAL;
    }

    irqx = ra_pin_alloc_irq_channel((rt_uint32_t) pin);
    if ((irqx < 0) || (irqx >= RA_WIRELESS_EXT_IRQ_MAX_CHANNEL))
    {
        return -RT_ERROR;
    }

    int level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqx].pin == pin &&
            pin_irq_hdr_tab[irqx].hdr == hdr &&
            pin_irq_hdr_tab[irqx].mode == mode &&
            pin_irq_hdr_tab[irqx].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    if (pin_irq_hdr_tab[irqx].pin != -1)
    {
        rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }

    pin_irq_hdr_tab[irqx].pin = pin;
    pin_irq_hdr_tab[irqx].hdr = hdr;
    pin_irq_hdr_tab[irqx].mode = mode;
    pin_irq_hdr_tab[irqx].args = args;

    ra_ext_irq_extend_tab[irqx].irq_pin = (bsp_io_port_pin_t) pin;

    ra_ext_irq_cfg_tab[irqx].channel = (uint8_t) irqx;
    ra_ext_irq_cfg_tab[irqx].ipl = 4;
    ra_ext_irq_cfg_tab[irqx].irq = FSP_INVALID_VECTOR;
    ra_ext_irq_cfg_tab[irqx].trigger = trigger;
    ra_ext_irq_cfg_tab[irqx].clock_source_div = EXTERNAL_IRQ_CLOCK_SOURCE_DIV_1;
    ra_ext_irq_cfg_tab[irqx].filter_enable = false;
    ra_ext_irq_cfg_tab[irqx].p_callback = ra_ext_irq_w_callback;
    ra_ext_irq_cfg_tab[irqx].p_context = &pin_irq_hdr_tab[irqx];
    ra_ext_irq_cfg_tab[irqx].p_extend = &ra_ext_irq_extend_tab[irqx];

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t ra_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    fsp_err_t err;
    rt_int32_t irqx = ra_pin_find_irq_channel((rt_uint32_t) pin);

    RT_UNUSED(device);

    if ((irqx < 0) || (irqx >= RA_WIRELESS_EXT_IRQ_MAX_CHANNEL))
    {
        return -RT_ERROR;
    }

    err = R_EXT_IRQ_W_ExternalIrqDisable((external_irq_ctrl_t *) &ra_ext_irq_ctrl_tab[irqx]);
    if ((FSP_SUCCESS != err) && (FSP_ERR_NOT_OPEN != err))
    {
        return -RT_ERROR;
    }

    err = R_EXT_IRQ_W_ExternalIrqClose((external_irq_ctrl_t *) &ra_ext_irq_ctrl_tab[irqx]);
    if ((FSP_SUCCESS != err) && (FSP_ERR_NOT_OPEN != err))
    {
        return -RT_ERROR;
    }

    int level = rt_hw_interrupt_disable();
    if (pin_irq_hdr_tab[irqx].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }

    pin_irq_hdr_tab[irqx].pin = -1;
    pin_irq_hdr_tab[irqx].hdr = RT_NULL;
    pin_irq_hdr_tab[irqx].mode = 0;
    pin_irq_hdr_tab[irqx].args = RT_NULL;
    ra_ext_irq_pin_to_channel[irqx] = -1;
    rt_memset(&ra_ext_irq_ctrl_tab[irqx], 0, sizeof(ra_ext_irq_ctrl_tab[irqx]));
    rt_memset(&ra_ext_irq_cfg_tab[irqx], 0, sizeof(ra_ext_irq_cfg_tab[irqx]));
    rt_memset(&ra_ext_irq_extend_tab[irqx], 0, sizeof(ra_ext_irq_extend_tab[irqx]));

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_base_t ra_pin_get(const char *name)
{
    rt_int32_t port = -1;
    rt_int32_t pin = -1;

    if ((rt_strlen(name) == 5) &&
        ((name[0] == 'P') || (name[0] == 'p')) &&
        (name[2] == '_') &&
        ('0' <= (int) name[1] && (int) name[1] <= '9') &&
        ('0' <= (int) name[3] && (int) name[3] <= '9') &&
        ('0' <= (int) name[4] && (int) name[4] <= '9'))
    {
        port = (rt_int32_t) (name[1] - '0');
        pin = (rt_int32_t) ((name[3] - '0') * 10 + (name[4] - '0'));
    }
    else if ((rt_strlen(name) == 4) &&
             ((name[0] == 'P') || (name[0] == 'p')) &&
             ('0' <= (int) name[1] && (int) name[1] <= '9') &&
             ('0' <= (int) name[2] && (int) name[2] <= '9') &&
             ('0' <= (int) name[3] && (int) name[3] <= '9'))
    {
        port = (rt_int32_t) (name[1] - '0');
        pin = (rt_int32_t) ((name[2] - '0') * 10 + (name[3] - '0'));
    }

    if ((port >= 0) && (pin >= 0) && (pin <= (rt_int32_t) BSP_IO_PIN_BITS))
    {
        rt_base_t pin_value = (rt_base_t) ((port << BSP_IO_PORT_OFFSET) | pin);
        if (ra_wireless_pin_valid(pin_value))
        {
            return pin_value;
        }
    }

    LOG_W("Invalid pin expression, use `P0_06` or `P006` format");
    return -RT_ERROR;
}

const static struct rt_pin_ops _ra_pin_ops =
{
    .pin_mode       = ra_pin_mode,
    .pin_write      = ra_pin_write,
    .pin_read       = ra_pin_read,
    .pin_attach_irq = ra_pin_attach_irq,
    .pin_detach_irq = ra_pin_dettach_irq,
    .pin_irq_enable = ra_pin_irq_enable,
    .pin_get        = ra_pin_get,
};

int rt_hw_pin_init(void)
{
    fsp_err_t err;

    ra_irq_tab_init();
    ra_w_pin_config_init();

    err = R_IOPORT_Open(&g_ioport_ctrl, &g_bsp_pin_cfg);
    if ((err != FSP_SUCCESS) && (err != FSP_ERR_ALREADY_OPEN))
    {
        LOG_E("GPIO open failed: %d", err);
        return -RT_ERROR;
    }

    return rt_device_pin_register("pin", &_ra_pin_ops, RT_NULL);
}
#endif /* R_EXT_IRQ_W_H */
#endif /* RT_USING_PIN */

