/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-20     Bernard      the first version
 * 2017-10-20      ZYH          add mode open drain and input pull down
 */

#ifndef PIN_H__
#define PIN_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RT_USING_DM
#include <drivers/pic.h>

struct rt_pin_irqchip
{
    struct rt_pic parent;

    int irq;
    rt_base_t pin_range[2];
};
#endif /* RT_USING_DM */

/* pin device and operations for RT-Thread */
struct rt_device_pin
{
    struct rt_device parent;
#ifdef RT_USING_DM
    struct rt_pin_irqchip irqchip;
#endif /* RT_USING_DM */
    const struct rt_pin_ops *ops;
};

#define PIN_NONE                (-1)

#define PIN_LOW                 0x00
#define PIN_HIGH                0x01

#define PIN_MODE_OUTPUT         0x00
#define PIN_MODE_INPUT          0x01
#define PIN_MODE_INPUT_PULLUP   0x02
#define PIN_MODE_INPUT_PULLDOWN 0x03
#define PIN_MODE_OUTPUT_OD      0x04

#ifdef RT_USING_PINCTRL
enum
{
    PIN_CONFIG_BIAS_BUS_HOLD,
    PIN_CONFIG_BIAS_DISABLE,
    PIN_CONFIG_BIAS_HIGH_IMPEDANCE,
    PIN_CONFIG_BIAS_PULL_DOWN,
    PIN_CONFIG_BIAS_PULL_PIN_DEFAULT,
    PIN_CONFIG_BIAS_PULL_UP,
    PIN_CONFIG_DRIVE_OPEN_DRAIN,
    PIN_CONFIG_DRIVE_OPEN_SOURCE,
    PIN_CONFIG_DRIVE_PUSH_PULL,
    PIN_CONFIG_DRIVE_STRENGTH,
    PIN_CONFIG_DRIVE_STRENGTH_UA,
    PIN_CONFIG_INPUT_DEBOUNCE,
    PIN_CONFIG_INPUT_ENABLE,
    PIN_CONFIG_INPUT_SCHMITT,
    PIN_CONFIG_INPUT_SCHMITT_ENABLE,
    PIN_CONFIG_MODE_LOW_POWER,
    PIN_CONFIG_MODE_PWM,
    PIN_CONFIG_OUTPUT,
    PIN_CONFIG_OUTPUT_ENABLE,
    PIN_CONFIG_OUTPUT_IMPEDANCE_OHMS,
    PIN_CONFIG_PERSIST_STATE,
    PIN_CONFIG_POWER_SOURCE,
    PIN_CONFIG_SKEW_DELAY,
    PIN_CONFIG_SLEEP_HARDWARE_STATE,
    PIN_CONFIG_SLEW_RATE,
    PIN_CONFIG_END = 0x7f,
    PIN_CONFIG_MAX = 0xff,
};
#endif /* RT_USING_PINCTRL */

#define PIN_IRQ_MODE_RISING             0x00
#define PIN_IRQ_MODE_FALLING            0x01
#define PIN_IRQ_MODE_RISING_FALLING     0x02
#define PIN_IRQ_MODE_HIGH_LEVEL         0x03
#define PIN_IRQ_MODE_LOW_LEVEL          0x04

#define PIN_IRQ_DISABLE                 0x00
#define PIN_IRQ_ENABLE                  0x01

#define PIN_IRQ_PIN_NONE                PIN_NONE

struct rt_device_pin_mode
{
    rt_base_t pin;
    rt_uint8_t mode; /* e.g. PIN_MODE_OUTPUT */
};

struct rt_device_pin_value
{
    rt_base_t pin;
    rt_uint8_t value; /* PIN_LOW or PIN_HIGH */
};

struct rt_pin_irq_hdr
{
    rt_base_t        pin;
    rt_uint8_t       mode; /* e.g. PIN_IRQ_MODE_RISING */
    void (*hdr)(void *args);
    void             *args;
};

#ifdef RT_USING_PINCTRL
struct rt_pin_ctrl_conf_params
{
    const char *propname;
    rt_uint32_t param;
    rt_uint32_t default_value;
};
#endif /* RT_USING_PINCTRL */

struct rt_pin_ops
{
    void (*pin_mode)(struct rt_device *device, rt_base_t pin, rt_uint8_t mode);
    void (*pin_write)(struct rt_device *device, rt_base_t pin, rt_uint8_t value);
    rt_ssize_t  (*pin_read)(struct rt_device *device, rt_base_t pin);
    rt_err_t (*pin_attach_irq)(struct rt_device *device, rt_base_t pin,
            rt_uint8_t mode, void (*hdr)(void *args), void *args);
    rt_err_t (*pin_detach_irq)(struct rt_device *device, rt_base_t pin);
    rt_err_t (*pin_irq_enable)(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled);
    rt_base_t (*pin_get)(const char *name);
#ifdef RT_USING_DM
    rt_err_t (*pin_irq_mode)(struct rt_device *device, rt_base_t pin, rt_uint8_t mode);
    rt_ssize_t (*pin_parse)(struct rt_device *device, struct rt_ofw_cell_args *args, rt_uint32_t *flags);
#endif
#ifdef RT_USING_PINCTRL
    rt_err_t (*pin_ctrl_confs_apply)(struct rt_device *device, void *fw_conf_np);
#endif /* RT_USING_PINCTRL */
};

int rt_device_pin_register(const char *name, const struct rt_pin_ops *ops, void *user_data);
void rt_pin_mode(rt_base_t pin, rt_uint8_t mode);
void rt_pin_write(rt_base_t pin, rt_ssize_t value);
rt_ssize_t rt_pin_read(rt_base_t pin);
rt_base_t rt_pin_get(const char *name);
rt_err_t rt_pin_attach_irq(rt_base_t pin, rt_uint8_t mode,
                           void (*hdr)(void *args), void  *args);
rt_err_t rt_pin_detach_irq(rt_base_t pin);
rt_err_t rt_pin_irq_enable(rt_base_t pin, rt_uint8_t enabled);

#ifdef RT_USING_DM
rt_ssize_t rt_pin_get_named_pin(struct rt_device *dev, const char *propname, int index,
        rt_uint8_t *out_mode, rt_uint8_t *out_value);
rt_ssize_t rt_pin_get_named_pin_count(struct rt_device *dev, const char *propname);

#ifdef RT_USING_OFW
rt_ssize_t rt_ofw_get_named_pin(struct rt_ofw_node *np, const char *propname, int index,
        rt_uint8_t *out_mode, rt_uint8_t *out_value);
rt_ssize_t rt_ofw_get_named_pin_count(struct rt_ofw_node *np, const char *propname);
#endif
#endif /* RT_USING_DM */

#ifdef RT_USING_PINCTRL
rt_ssize_t rt_pin_ctrl_confs_lookup(struct rt_device *device, const char *name);
rt_err_t rt_pin_ctrl_confs_apply(struct rt_device *device, int index);
rt_err_t rt_pin_ctrl_confs_apply_by_name(struct rt_device *device, const char *name);
#endif /* RT_USING_PINCTRL */

#ifdef __cplusplus
}
#endif

#endif
