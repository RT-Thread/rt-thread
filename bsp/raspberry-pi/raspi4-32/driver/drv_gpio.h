/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "interrupt.h"

struct gpio_irq_def
{
    void  *irq_arg[32];
    void (*irq_cb[32])(void *param);
    rt_uint8_t irq_type[32];
    rt_uint8_t state[32];
};

#define GPIO_REG_GPFSEL0(BASE)             HWREG32(BASE + 0x00)
#define GPIO_REG_GPFSEL1(BASE)             HWREG32(BASE + 0x04)
#define GPIO_REG_GPFSEL2(BASE)             HWREG32(BASE + 0x08)
#define GPIO_REG_GPFSEL3(BASE)             HWREG32(BASE + 0x0C)
#define GPIO_REG_GPFSEL4(BASE)             HWREG32(BASE + 0x10)
#define GPIO_REG_GPFSEL5(BASE)             HWREG32(BASE + 0x14)
#define GPIO_REG_REV0(BASE)                HWREG32(BASE + 0x18)
#define GPIO_REG_GPSET0(BASE)              HWREG32(BASE + 0x1C)
#define GPIO_REG_GPSET1(BASE)              HWREG32(BASE + 0x20)
#define GPIO_REG_REV1(BASE)                HWREG32(BASE + 0x24)
#define GPIO_REG_GPCLR0(BASE)              HWREG32(BASE + 0x28)
#define GPIO_REG_GPCLR1(BASE)              HWREG32(BASE + 0x2C)
#define GPIO_REG_REV2(BASE)                HWREG32(BASE + 0x30)
#define GPIO_REG_GPLEV0(BASE)              HWREG32(BASE + 0x34)
#define GPIO_REG_GPLEV1(BASE)              HWREG32(BASE + 0x38)
#define GPIO_REG_REV3(BASE)                HWREG32(BASE + 0x3C)
#define GPIO_REG_GPEDS0(BASE)              HWREG32(BASE + 0x40)
#define GPIO_REG_GPEDS1(BASE)              HWREG32(BASE + 0x44)
#define GPIO_REG_REV4(BASE)                HWREG32(BASE + 0x48)
#define GPIO_REG_GPREN0(BASE)              HWREG32(BASE + 0x4C)
#define GPIO_REG_GPREN1(BASE)              HWREG32(BASE + 0x50)
#define GPIO_REG_REV5(BASE)                HWREG32(BASE + 0x54)
#define GPIO_REG_GPFEN0(BASE)              HWREG32(BASE + 0x58)
#define GPIO_REG_GPFEN1(BASE)              HWREG32(BASE + 0x5C)
#define GPIO_REG_REV6(BASE)                HWREG32(BASE + 0x60)
#define GPIO_REG_GPHEN0(BASE)              HWREG32(BASE + 0x64)
#define GPIO_REG_GPHEN1(BASE)              HWREG32(BASE + 0x68)
#define GPIO_REG_REV7(BASE)                HWREG32(BASE + 0x6C)
#define GPIO_REG_GPLEN0(BASE)              HWREG32(BASE + 0x70)
#define GPIO_REG_GPLEN1(BASE)              HWREG32(BASE + 0x74)
#define GPIO_REG_REV8(BASE)                HWREG32(BASE + 0x78)
#define GPIO_REG_GPAREN0(BASE)             HWREG32(BASE + 0x7C)
#define GPIO_REG_GPAREN1(BASE)             HWREG32(BASE + 0x80)
#define GPIO_REG_REV11(BASE)               HWREG32(BASE + 0x84)
#define GPIO_REG_GPAFEN0(BASE)             HWREG32(BASE + 0x88)
#define GPIO_REG_GPAFEN1(BASE)             HWREG32(BASE + 0x8C)
#define GPIO_REG_REV10(BASE)               HWREG32(BASE + 0x90)
#define GPIO_REG_GPPUD(BASE)               HWREG32(BASE + 0x94)
#define GPIO_REG_GPPUDCLK0(BASE)           HWREG32(BASE + 0x98)
#define GPIO_REG_GPPUDCLK1(BASE)           HWREG32(BASE + 0x9C)
#define GPIO_REG_REV9(BASE)                HWREG32(BASE + 0xA0)
#define GPIO_REG_TEST(BASE)                HWREG32(BASE + 0xA4)
#define GPIO_PUP_PDN_CNTRL_REG0(BASE)      HWREG32(BASE + 0xE4)
#define GPIO_PUP_PDN_CNTRL_REG1(BASE)      HWREG32(BASE + 0xE8)
#define GPIO_PUP_PDN_CNTRL_REG2(BASE)      HWREG32(BASE + 0xEC)
#define GPIO_PUP_PDN_CNTRL_REG3(BASE)      HWREG32(BASE + 0xF0)

typedef enum {
    GPIO_PIN_0,
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
    GPIO_PIN_24,
    GPIO_PIN_25,
    GPIO_PIN_26,
    GPIO_PIN_27,
    GPIO_PIN_28,
    GPIO_PIN_29,
    GPIO_PIN_30,
    GPIO_PIN_31,
    GPIO_PIN_32,
    GPIO_PIN_33,
    GPIO_PIN_34,
    GPIO_PIN_35,
    GPIO_PIN_36,
    GPIO_PIN_37,
    GPIO_PIN_38,
    GPIO_PIN_39,
    GPIO_PIN_40,
} GPIO_PIN;

typedef enum {
    INPUT = 0b000,
    OUTPUT = 0b001,
    ALT0 = 0b100,
    ALT1 = 0b101,
    ALT2 = 0b110,
    ALT3 = 0b111,
    ALT4 = 0b011,
    ALT5 = 0b010
} GPIO_FUNC;

typedef enum {
    RASPI_NO_RESISTOR = 0x00,
    RASPI_PULL_UP = 0x01,
    RASPI_PULL_DOWN = 0x10
} GPIO_PUPD_FUNC;

void prev_raspi_pin_mode(GPIO_PIN pin, GPIO_FUNC mode);
void prev_raspi_pin_write(GPIO_PIN pin, int pin_value);
int rt_hw_gpio_init(void);

#endif /* __DRV_GPIO_H__ */
