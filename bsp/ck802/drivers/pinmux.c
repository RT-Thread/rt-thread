/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     pinmux.c
 * @brief    source file for the pinmux
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#include <stdint.h>
#include "pinmux.h"
#include "pin_name.h"

#define readl(addr) \
    ({ unsigned int __v = (*(volatile unsigned int *) (addr)); __v; })

#define writel(b,addr) (void)((*(volatile unsigned int *) (addr)) = (b))

/*******************************************************************************
 * function: phobos_ioreuse_inital
 *
 * description:
 *   initial phobos_pinmux
 *******************************************************************************/

void phobos_ioreuse_initial(void)
{
    unsigned int value;

    /* gpio data source select */
    value = readl(PHOBOS_GIPO0_PORTCTL_REG);
    value |= GPIO0_REUSE_EN;
    writel(value, PHOBOS_GIPO0_PORTCTL_REG);

    value = readl(PHOBOS_GIPO1_PORTCTL_REG);
    value |= GPIO1_REUSE_EN;
    writel(value, PHOBOS_GIPO1_PORTCTL_REG);

    /* reuse function select */
    value = readl(PHOBOS_IOMUX0L_REG);
    value |= IOMUX0L_FUNCTION_SEL;
    writel(value, PHOBOS_IOMUX0L_REG);

    value = readl(PHOBOS_IOMUX0H_REG);
    value |= IOMUX1L_FUNCTION_SEL;
    writel(value, PHOBOS_IOMUX0H_REG);

    value = readl(PHOBOS_IOMUX1L_REG);
    value |= IOMUX1L_FUNCTION_SEL;
    writel(value, PHOBOS_IOMUX1L_REG);
}

void phobos_pwm_ioreuse(void)
{
    unsigned int value;

    /* gpio data source select */
    value = readl(PHOBOS_GIPO0_PORTCTL_REG);
    value |= PWM_GPIO0_REUSE_EN;
    writel(value, PHOBOS_GIPO0_PORTCTL_REG);

    /* reuse function select */
    value = readl(PHOBOS_IOMUX0L_REG);
    value |= PWM_IOMUX0L_FUNCTION_SEL;
    writel(value, PHOBOS_IOMUX0L_REG);
}


int32_t pin_mux(pin_name_t pin, uint16_t function)
{
    unsigned int val = 0;
    unsigned int reg_val = 0;

    uint8_t offset;

    if (function > 3)
    {
        if (pin < PB0_ADC0_SDA0_PWM5_XX)
        {
            offset = pin;
            /* gpio data source select */
            val = readl(PHOBOS_GIPO0_PORTCTL_REG);
            val &= ~(1 << offset);
            writel(val, PHOBOS_GIPO0_PORTCTL_REG);
            return 0;
        }
        else if (pin >= PB0_ADC0_SDA0_PWM5_XX)
        {
            offset = pin - 32;
            /* gpio data source select */
            val = readl(PHOBOS_GIPO1_PORTCTL_REG);
            val &= ~(1 << offset);
            writel(val, PHOBOS_GIPO1_PORTCTL_REG);
            return 0;
        }
        else
        {
            return -1;
        }
    }

    if (pin >= PB0_ADC0_SDA0_PWM5_XX)
    {
        offset = pin - 32;

        /* gpio data source select */
        val = readl(PHOBOS_GIPO1_PORTCTL_REG);
        val |= (1 << offset);
        writel(val, PHOBOS_GIPO1_PORTCTL_REG);

        reg_val = (0x3 << (offset * 2));
        /* reuse function select */
        val = readl(PHOBOS_IOMUX1L_REG);
        val &= ~(reg_val);
        val |= (function << (2 * offset));
        writel(val, PHOBOS_IOMUX1L_REG);
        return 0;
    }

    offset = pin;
    /* gpio data source select */
    val = readl(PHOBOS_GIPO0_PORTCTL_REG);
    val |= (1 << offset);
    writel(val, PHOBOS_GIPO0_PORTCTL_REG);

    if (pin >= PA16_SPI1CLK_PWMTRIG1_XX_XX)
    {
        offset = pin - 16;
        reg_val = (0x3 << (offset * 2));
        /* reuse function select */
        val = readl(PHOBOS_IOMUX0H_REG);
        val &= ~(reg_val);
        val |= (function << (2 * offset));
        writel(val, PHOBOS_IOMUX0H_REG);
        return 0;
    }

    reg_val = (0x3 << (offset * 2));
    /* reuse function select */
    val = readl(PHOBOS_IOMUX0L_REG);
    val &= ~(reg_val);
    val |= (function << (2 * offset));
    writel(val, PHOBOS_IOMUX0L_REG);
    return 0;
}
