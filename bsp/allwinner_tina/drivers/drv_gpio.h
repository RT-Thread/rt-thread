/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-02-08     RT-Thread    the first version
 */
#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtdef.h>

/* IO default function */
#define IO_INPUT         (0x00)
#define IO_OUTPUT        (0x01)
#define IO_DISABLE       (0x07)

#define IO_FUN_1         (0x02)
#define IO_FUN_2         (0x03)
#define IO_FUN_3         (0x04)
#define IO_FUN_4         (0x05)
#define IO_FUN_5         (0x06)

/* IO port */
enum gpio_port
{
    GPIO_PORT_A = 0,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_NUM,
};

/* IO pin */
enum gpio_pin
{
    GPIO_PIN_0 = 0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15,
    GPIO_PIN_16,
    GPIO_PIN_17,
    GPIO_PIN_18,
    GPIO_PIN_19,
    GPIO_PIN_20,
    GPIO_PIN_21,
    GPIO_PIN_22,
    GPIO_PIN_23,
    GPIO_PIN_NUM,
};

/* Drive level */
enum gpio_drv_level
{
    DRV_LEVEL_0 = 0,
    DRV_LEVEL_1,
    DRV_LEVEL_2,
    DRV_LEVEL_3,
};

/* Pull mode */
enum gpio_pull
{
    PULL_DISABLE = 0,
    PULL_UP,
    PULL_DOWN,
};

/* interrupt type */
enum gpio_irq_type
{
    POSITIVE = 0,
    NEGATIVE,
    HIGH,
    LOW,
    DOUBLE,
};

enum gpio_irq_clock
{
    GPIO_IRQ_LOSC_32KHZ = 0,
    GPIO_IRQ_HOSC_24MHZ
};

enum gpio_direction_type
{
    DEBOUNCE_PRE_SCALE_1 = 0,
    DEBOUNCE_PRE_SCALE_2,
    DEBOUNCE_PRE_SCALE_4,
    DEBOUNCE_PRE_SCALE_8,
    DEBOUNCE_PRE_SCALE_16,
    DEBOUNCE_PRE_SCALE_32,
    DEBOUNCE_PRE_SCALE_64,
    DEBOUNCE_PRE_SCALE_128,
};

struct gpio_irq_def
{
    void    *irq_arg[32];
    void (*irq_cb[32])(void *param);
};

#define GPIO_BASE_ADDR           (0x01C20800)
#define GPIOn_CFG_ADDR(n)        (GPIO_BASE_ADDR + (n) * 0x24 + 0x00)
#define GPIOn_DATA_ADDR(n)       (GPIO_BASE_ADDR + (n) * 0x24 + 0x10)
#define GPIOn_DRV_ADDR(n)        (GPIO_BASE_ADDR + (n) * 0x24 + 0x14)
#define GPIOn_PUL_ADDR(n)        (GPIO_BASE_ADDR + (n) * 0x24 + 0x1C)
#define GPIOn_INT_CFG_ADDR(n)    (GPIO_BASE_ADDR + 0x200 + (n) * 0x20 + 0x00)
#define GPIOn_INT_CTRL_ADDR(n)   (GPIO_BASE_ADDR + 0x200 + (n) * 0x20 + 0x10)
#define GPIOn_INT_STA_ADDR(n)    (GPIO_BASE_ADDR + 0x200 + (n) * 0x20 + 0x14)
#define GPIOn_INT_DEB_ADDR(n)    (GPIO_BASE_ADDR + 0x200 + (n) * 0x20 + 0x18)

struct tina_gpio
{
    volatile rt_uint32_t pa_cfg0;        /* 0x00 */
    volatile rt_uint32_t pa_cfg1;        /* 0x04 */
    volatile rt_uint32_t pa_cfg2;        /* 0x08 */
    volatile rt_uint32_t pa_cfg3;        /* 0x0C */
    volatile rt_uint32_t pa_data;        /* 0x10 */
    volatile rt_uint32_t pa_drv0;        /* 0x14 */
    volatile rt_uint32_t pa_drv1;        /* 0x18 */
    volatile rt_uint32_t pa_pul0;        /* 0x1C */
    volatile rt_uint32_t pa_pul1;        /* 0x20 */
    volatile rt_uint32_t pb_cfg0;        /* 0x24 */
    volatile rt_uint32_t pb_cfg1;        /* 0x28 */
    volatile rt_uint32_t pb_cfg2;        /* 0x2C */
    volatile rt_uint32_t pb_cfg3;        /* 0x30 */
    volatile rt_uint32_t pb_data;        /* 0x34 */
    volatile rt_uint32_t pb_drv0;        /* 0x38 */
    volatile rt_uint32_t pb_drv1;        /* 0x3C */
    volatile rt_uint32_t pb_pul0;        /* 0x40 */
    volatile rt_uint32_t pb_pul1;        /* 0x44 */
    volatile rt_uint32_t pc_cfg0;        /* 0x48 */
    volatile rt_uint32_t pc_cfg1;        /* 0x4C */
    volatile rt_uint32_t pc_cfg2;        /* 0x50 */
    volatile rt_uint32_t pc_cfg3;        /* 0x54 */
    volatile rt_uint32_t pc_data;        /* 0x58 */
    volatile rt_uint32_t pc_drv0;        /* 0x5C */
    volatile rt_uint32_t pc_drv1;        /* 0x60 */
    volatile rt_uint32_t pc_pul0;        /* 0x64 */
    volatile rt_uint32_t pc_pul1;        /* 0x68 */
    volatile rt_uint32_t pd_cfg0;        /* 0x6C */
    volatile rt_uint32_t pd_cfg1;        /* 0x70 */
    volatile rt_uint32_t pd_cfg2;        /* 0x74 */
    volatile rt_uint32_t pd_cfg3;        /* 0x78 */
    volatile rt_uint32_t pd_data;        /* 0x7C */
    volatile rt_uint32_t pd_drv0;        /* 0x80 */
    volatile rt_uint32_t pd_drv1;        /* 0x84 */
    volatile rt_uint32_t pd_pul0;        /* 0x88 */
    volatile rt_uint32_t pd_pul1;        /* 0x8C */
    volatile rt_uint32_t pe_cfg0;        /* 0x90 */
    volatile rt_uint32_t pe_cfg1;        /* 0x94 */
    volatile rt_uint32_t pe_cfg2;        /* 0x98 */
    volatile rt_uint32_t pe_cfg3;        /* 0x9C */
    volatile rt_uint32_t pe_data;        /* 0xA0 */
    volatile rt_uint32_t pe_drv0;        /* 0xA4 */
    volatile rt_uint32_t pe_drv1;        /* 0xA8 */
    volatile rt_uint32_t pe_pul0;        /* 0xAC */
    volatile rt_uint32_t pe_pul1;        /* 0xB0 */
    volatile rt_uint32_t pf_cfg0;        /* 0xB4 */
    volatile rt_uint32_t pf_cfg1;        /* 0xB8 */
    volatile rt_uint32_t pf_cfg2;        /* 0xBC */
    volatile rt_uint32_t pf_cfg3;        /* 0xC0 */
    volatile rt_uint32_t pf_data;        /* 0xC4 */
    volatile rt_uint32_t pf_drv0;        /* 0xC8 */
    volatile rt_uint32_t pf_drv1;        /* 0xCC */
    volatile rt_uint32_t pf_pul0;        /* 0xD0 */
    volatile rt_uint32_t reserved0[76];
    volatile rt_uint32_t pd_int_cfg0;    /* 0x200 */
    volatile rt_uint32_t pd_int_cfg1;    /* 0x204 */
    volatile rt_uint32_t pd_int_cfg2;    /* 0x208 */
    volatile rt_uint32_t pd_int_cfg3;    /* 0x20C */
    volatile rt_uint32_t pd_int_ctrl;    /* 0x210 */
    volatile rt_uint32_t pd_int_sta;     /* 0x214 */
    volatile rt_uint32_t pd_int_deb;     /* 0x218 */
    volatile rt_uint32_t reserved1;
    volatile rt_uint32_t pe_int_cfg0;    /* 0x220 */
    volatile rt_uint32_t pe_int_cfg1;    /* 0x224 */
    volatile rt_uint32_t pe_int_cfg2;    /* 0x228 */
    volatile rt_uint32_t pe_int_cfg3;    /* 0x22C */
    volatile rt_uint32_t pe_int_ctrl;    /* 0x230 */
    volatile rt_uint32_t pe_int_sta;     /* 0x234 */
    volatile rt_uint32_t pe_int_deb;     /* 0x238 */
    volatile rt_uint32_t reserved2;
    volatile rt_uint32_t pf_int_cfg0;    /* 0x240 */
    volatile rt_uint32_t pf_int_cfg1;    /* 0x244 */
    volatile rt_uint32_t pf_int_cfg2;    /* 0x248 */
    volatile rt_uint32_t pf_int_cfg3;    /* 0x24C */
    volatile rt_uint32_t pf_int_ctrl;    /* 0x250 */
    volatile rt_uint32_t pf_int_sta;     /* 0x254 */
    volatile rt_uint32_t pf_int_deb;     /* 0x258 */
    volatile rt_uint32_t reserved3[26];
    volatile rt_uint32_t sdr_pad_drv;    /* 0x2C0*/
    volatile rt_uint32_t sdr_pad_pul;    /* 0x2C4 */
};

typedef struct tina_gpio *tina_gpio_t;

#define GPIO ((tina_gpio_t)GPIO_BASE_ADDR)

rt_err_t gpio_set_func(enum gpio_port port, enum gpio_pin pin, rt_uint8_t func);
int gpio_set_value(enum gpio_port port, enum gpio_pin pin, rt_uint8_t value);
int gpio_get_value(enum gpio_port port, enum gpio_pin pin);
int gpio_set_pull_mode(enum gpio_port port,  enum gpio_pin pin, enum gpio_pull pull);
int gpio_set_drive_level(enum gpio_port port, enum gpio_pin pin, enum gpio_drv_level level);
void gpio_direction_input(enum gpio_port port,  enum gpio_pin pin);
void gpio_direction_output(enum gpio_port port, enum gpio_pin pin, int value);
void gpio_irq_enable(enum gpio_port port,  enum gpio_pin pin);
void gpio_irq_disable(enum gpio_port port,  enum gpio_pin pin);
void gpio_set_irq_type(enum gpio_port port,  enum gpio_pin pin, enum gpio_irq_type irq_type);
void gpio_select_irq_clock(enum gpio_port port, enum gpio_irq_clock clock);
void gpio_set_debounce(enum gpio_port port, rt_uint8_t prescaler);
void gpio_set_irq_callback(enum gpio_port port, enum gpio_pin pin, void (*irq_cb)(void *), void *irq_arg);
int rt_hw_gpio_init(void);

#endif /* __DRV_GPIO_H__ */
