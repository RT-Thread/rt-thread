/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-20     Bernard      the first version
 * 2017-10-20      ZYH          add mode open drain and input pull down
 */

#ifndef DEV_PIN_H__
#define DEV_PIN_H__

#include <rtthread.h>

/**
 * @addtogroup  Drivers          RTTHREAD Driver
 * @defgroup    Pin              Pin
 *
 * @brief       Pin driver api
 *
 * <b>Example</b>
 * @code {.c}
 * #include <rtthread.h>
 * #include <rtdevice.h>
 *
 *
 * #ifndef BEEP_PIN_NUM
 *     #define BEEP_PIN_NUM            35  // PB0
 * #endif
 * #ifndef KEY0_PIN_NUM
 *     #define KEY0_PIN_NUM            55  // PD8
 * #endif
 * #ifndef KEY1_PIN_NUM
 *     #define KEY1_PIN_NUM            56  // PD9
 * #endif
 *
 * void beep_on(void *args)
 * {
 *     rt_kprintf("turn on beep!\n");
 *
 *     rt_pin_write(BEEP_PIN_NUM, PIN_HIGH);
 * }
 *
 * void beep_off(void *args)
 * {
 *     rt_kprintf("turn off beep!\n");
 *
 *     rt_pin_write(BEEP_PIN_NUM, PIN_LOW);
 * }
 *
 * static void pin_beep_sample(void)
 * {
 *     rt_pin_mode(BEEP_PIN_NUM, PIN_MODE_OUTPUT);
 *     rt_pin_write(BEEP_PIN_NUM, PIN_LOW);
 *
 *     rt_pin_mode(KEY0_PIN_NUM, PIN_MODE_INPUT_PULLUP);
 *     rt_pin_attach_irq(KEY0_PIN_NUM, PIN_IRQ_MODE_FALLING, beep_on, RT_NULL);
 *     rt_pin_irq_enable(KEY0_PIN_NUM, PIN_IRQ_ENABLE);
 *
 *
 *     rt_pin_mode(KEY1_PIN_NUM, PIN_MODE_INPUT_PULLUP);
 *     rt_pin_attach_irq(KEY1_PIN_NUM, PIN_IRQ_MODE_FALLING, beep_off, RT_NULL);
 *     rt_pin_irq_enable(KEY1_PIN_NUM, PIN_IRQ_ENABLE);
 * }
 *
 * MSH_CMD_EXPORT(pin_beep_sample, pin beep sample);
 * @endcode
 *
 * @ingroup     Drivers
 */

/*!
 * @addtogroup Pin
 * @{
 */
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

struct rt_pin_irq_hdr;
#endif /* RT_USING_DM */

/**
 * @brief pin device structure
 */
struct rt_device_pin
{
    struct rt_device parent;
#ifdef RT_USING_DM
    /* MUST keep the order member after parent */
    struct rt_pin_irqchip irqchip;
    /* Fill by DM */
    rt_base_t pin_start;
    rt_size_t pin_nr;
    rt_list_t list;
    struct rt_pin_irq_hdr *legacy_isr;
#endif /* RT_USING_DM */
    const struct rt_pin_ops *ops;
};

#define PIN_NONE                (-1)

#define PIN_LOW                 0x00 /*!< low level */
#define PIN_HIGH                0x01 /*!< high level */

#define PIN_MODE_OUTPUT         0x00 /*!< output mode */
#define PIN_MODE_INPUT          0x01 /*!< input mode */
#define PIN_MODE_INPUT_PULLUP   0x02 /*!< input mode with pull-up */
#define PIN_MODE_INPUT_PULLDOWN 0x03 /*!< input mode with pull-down */
#define PIN_MODE_OUTPUT_OD      0x04 /*!< output mode with open-drain */

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

#define PIN_IRQ_MODE_RISING             0x00 /*!< rising edge trigger */
#define PIN_IRQ_MODE_FALLING            0x01 /*!< falling edge trigger */
#define PIN_IRQ_MODE_RISING_FALLING     0x02 /*!< rising and falling edge trigger */
#define PIN_IRQ_MODE_HIGH_LEVEL         0x03 /*!< high level trigger */
#define PIN_IRQ_MODE_LOW_LEVEL          0x04 /*!< low level trigger */

#define PIN_IRQ_DISABLE                 0x00 /*!< disable irq */
#define PIN_IRQ_ENABLE                  0x01 /*!< enable irq */

#define PIN_IRQ_PIN_NONE                PIN_NONE /*!< no pin irq */

/**
 * @brief pin mode structure
 */
struct rt_device_pin_mode
{
    rt_base_t pin;
    rt_uint8_t mode; /* e.g. PIN_MODE_OUTPUT */
};

/**
 * @brief pin value structure
 */
struct rt_device_pin_value
{
    rt_base_t pin;
    rt_uint8_t value; /* PIN_LOW or PIN_HIGH */
};

/**
 * @brief pin irq structure
 */
struct rt_pin_irq_hdr
{
    rt_base_t        pin;
    rt_uint8_t       mode; /* e.g. PIN_IRQ_MODE_RISING */
    void (*hdr)(void *args);
    void             *args;
};

#ifdef RT_USING_PINCTRL
/**
 * @brief pin control configure structure
 */
struct rt_pin_ctrl_conf_params
{
    const char *propname;
    rt_uint32_t param;
    rt_uint32_t default_value;
};
#endif /* RT_USING_PINCTRL */

/**
 * @brief pin device operations
 */
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
    rt_err_t (*pin_debounce)(struct rt_device *device, rt_base_t pin, rt_uint32_t debounce);
#ifdef RT_USING_DM
    rt_err_t (*pin_irq_mode)(struct rt_device *device, rt_base_t pin, rt_uint8_t mode);
    rt_ssize_t (*pin_parse)(struct rt_device *device, struct rt_ofw_cell_args *args, rt_uint32_t *flags);
#endif
#ifdef RT_USING_PINCTRL
    rt_err_t (*pin_ctrl_confs_apply)(struct rt_device *device, void *fw_conf_np);
#endif /* RT_USING_PINCTRL */
};

/**
 * @brief register a pin device
 * @param name the name of pin device
 * @param ops the operations of pin device
 * @param user_data the user data of pin device
 * @return int error code
 */
int rt_device_pin_register(const char *name, const struct rt_pin_ops *ops, void *user_data);

/**
 * @brief set pin mode
 * @param pin the pin number
 * @param mode the pin mode
 */
void rt_pin_mode(rt_base_t pin, rt_uint8_t mode);

/**
 * @brief write pin value
 * @param pin the pin number
 * @param value the pin value
 */
void rt_pin_write(rt_base_t pin, rt_ssize_t value);

/**
 * @brief read pin value
 * @param pin the pin number
 * @return rt_ssize_t the pin value
 */
rt_ssize_t rt_pin_read(rt_base_t pin);

/**
 * @brief get pin number by name
 * @param name the pin name
 * @return rt_base_t the pin number
 */
rt_base_t rt_pin_get(const char *name);

/**
 * @brief bind the pin interrupt callback function
 * @param pin the pin number
 * @param mode the irq mode
 * @param hdr the irq callback function
 * @param args the argument of the callback function
 * @return rt_err_t error code
 */
rt_err_t rt_pin_attach_irq(rt_base_t pin, rt_uint8_t mode,
                           void (*hdr)(void *args), void  *args);

/**
 * @brief detach the pin interrupt callback function
 * @param pin the pin number
 * @return rt_err_t error code
 */
rt_err_t rt_pin_detach_irq(rt_base_t pin);

/**
 * @brief enable or disable the pin interrupt
 * @param pin the pin number
 * @param enabled PIN_IRQ_ENABLE or PIN_IRQ_DISABLE
 * @return rt_err_t error code
 */
rt_err_t rt_pin_irq_enable(rt_base_t pin, rt_uint8_t enabled);

/**
 * @brief set the pin's debounce time
 * @param pin the pin number
 * @param debounce time
 * @return rt_err_t error code
 */
rt_err_t rt_pin_debounce(rt_base_t pin, rt_uint32_t debounce);

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

/*! @}*/

#endif
