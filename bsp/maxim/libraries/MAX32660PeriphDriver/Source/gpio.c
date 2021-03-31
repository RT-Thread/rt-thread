/* *****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2018-12-18 15:37:22 -0600 (Tue, 18 Dec 2018) $
 * $Revision: 40072 $
 *
 **************************************************************************** */

/* **** Includes **** */
#include "mxc_config.h"
#include "mxc_assert.h"
#include "gpio.h"
#include <stddef.h>

/* **** Definitions **** */

/* **** Globals **** */

static void (*callback[MXC_CFG_GPIO_INSTANCES][MXC_CFG_GPIO_PINS_PORT])(void *);
static void *cbparam[MXC_CFG_GPIO_INSTANCES][MXC_CFG_GPIO_PINS_PORT];

/* **** Functions **** */

int GPIO_Init(void)
{
    int i;
    int j;
    
    // Initialize call back arrays
    for(i = 0; i < MXC_CFG_GPIO_INSTANCES; i++) {
        for(j = 0; j < MXC_CFG_GPIO_PINS_PORT; j++) {
            callback[i][j] = NULL;
        }
    }            
    return E_NO_ERROR;
}

/* ************************************************************************** */
/*
 *       GPIO_EN2 |  GPIO_EN1           |  GPIO_EN            |   Function
 *  --------------|---------------------|---------------------|----------------------
 *     0          |          0          |          0          |     Alternative 1
 *     0          |          1          |          0          |     Alternative 2
 *     1          |          0          |          0          |     Alternative 3
 *     1          |          1          |          0          |     Alternative 4
 *     0          |          0          |          1          |     GPIO (default)
*/

int GPIO_Config(const gpio_cfg_t *cfg)
{
    mxc_gpio_regs_t *gpio = MXC_GPIO_GET_GPIO(cfg->port);

    // Set the GPIO type
    switch (cfg->func) {
        case GPIO_FUNC_IN:
            gpio->out_en_clr = cfg->mask;
            gpio->en_set     = cfg->mask;
            gpio->en1_clr    = cfg->mask;
            gpio->en2_clr    = cfg->mask;
            break;
        case GPIO_FUNC_OUT:
            gpio->out_en_set = cfg->mask;
            gpio->en_set     = cfg->mask;
            gpio->en1_clr    = cfg->mask;
            gpio->en2_clr    = cfg->mask;
            break;
        case GPIO_FUNC_ALT1:
            gpio->en_clr     = cfg->mask;
            gpio->en1_clr    = cfg->mask;
            gpio->en2_clr    = cfg->mask;
            break;
        case GPIO_FUNC_ALT2:
            gpio->en_clr     = cfg->mask;
            gpio->en1_set    = cfg->mask;
            gpio->en2_clr    = cfg->mask;
            break;
        case GPIO_FUNC_ALT3:
#if TARGET==32660
            gpio->en_set     = cfg->mask;
            gpio->en1_set    = cfg->mask;
#else
            gpio->en_clr     = cfg->mask;
            gpio->en1_clr    = cfg->mask;
            gpio->en2_set    = cfg->mask;
#endif
            break;
        case GPIO_FUNC_ALT4:
            gpio->en_clr     = cfg->mask;
            gpio->en1_set    = cfg->mask;
            gpio->en2_set    = cfg->mask;
            break;
        default:
            return E_BAD_PARAM;
    }

    // Configure the pad
    switch (cfg->pad) {
        case GPIO_PAD_NONE:
            gpio->pad_cfg1 &= ~cfg->mask;
            gpio->pad_cfg2 &= ~cfg->mask;
#if TARGET==32660
            gpio->ps &= ~cfg->mask;
#endif
            break;
        case GPIO_PAD_PULL_UP:
            gpio->pad_cfg1 |=  cfg->mask;
            gpio->pad_cfg2 &= ~cfg->mask;
#if TARGET==32660
            gpio->ps |= cfg->mask;
#endif
            break;
        case GPIO_PAD_PULL_DOWN:
            gpio->pad_cfg1 &= ~cfg->mask;
            gpio->pad_cfg2 |=  cfg->mask;
#if TARGET==32660
            gpio->ps &= ~cfg->mask;
#endif
            break;
        default:
            return E_BAD_PARAM;
    }

    return E_NO_ERROR;
}

/* ************************************************************************** */
uint32_t GPIO_InGet(const gpio_cfg_t *cfg)
{
    mxc_gpio_regs_t *gpio = MXC_GPIO_GET_GPIO(cfg->port);

    return (gpio->in & cfg->mask);
}

/* ************************************************************************** */
void GPIO_OutSet(const gpio_cfg_t *cfg)
{
    mxc_gpio_regs_t *gpio = MXC_GPIO_GET_GPIO(cfg->port);

    gpio->out_set = cfg->mask;
}

/* ************************************************************************** */
void GPIO_OutClr(const gpio_cfg_t *cfg)
{
    mxc_gpio_regs_t *gpio = MXC_GPIO_GET_GPIO(cfg->port);

    gpio->out_clr = cfg->mask;
}

/* ************************************************************************** */
uint32_t GPIO_OutGet(const gpio_cfg_t *cfg)
{
    mxc_gpio_regs_t *gpio = MXC_GPIO_GET_GPIO(cfg->port);

    return (gpio->out & cfg->mask);
}

/* ************************************************************************** */
void GPIO_OutPut(const gpio_cfg_t *cfg, uint32_t val)
{
    mxc_gpio_regs_t *gpio = MXC_GPIO_GET_GPIO(cfg->port);

    gpio->out = (gpio->out & ~cfg->mask) | (val & cfg->mask);
}

/* ************************************************************************** */
void GPIO_OutToggle(const gpio_cfg_t *cfg)
{
    mxc_gpio_regs_t *gpio = MXC_GPIO_GET_GPIO(cfg->port);

    gpio->out ^= cfg->mask;
}

/* ************************************************************************** */
int GPIO_IntConfig(const gpio_cfg_t *cfg, gpio_int_mode_t mode, gpio_int_pol_t pol)
{
    mxc_gpio_regs_t *gpio = MXC_GPIO_GET_GPIO(cfg->port);

    switch (mode) {
        case GPIO_INT_LEVEL:
            gpio->int_mod &= ~cfg->mask;
            break;
        case GPIO_INT_EDGE:
            gpio->int_mod |= cfg->mask;
            break;
        default:
            return E_BAD_PARAM;
    }

    switch (pol) {
        case GPIO_INT_FALLING:  /* GPIO_INT_HIGH */
            gpio->int_pol &= ~cfg->mask;
            gpio->int_dual_edge &= ~cfg->mask;
        break;
        case GPIO_INT_RISING:   /* GPIO_INT_LOW */
            gpio->int_pol |= cfg->mask;
            gpio->int_dual_edge &= ~cfg->mask;
        break;
        case GPIO_INT_BOTH:
            gpio->int_dual_edge |= cfg->mask;
        break;
        default:
            return E_BAD_PARAM;
    }

    return E_NO_ERROR;
}

/* ************************************************************************** */
void GPIO_IntEnable(const gpio_cfg_t *cfg)
{
    mxc_gpio_regs_t *gpio = MXC_GPIO_GET_GPIO(cfg->port);

    gpio->int_en_set = cfg->mask;
}

/* ************************************************************************** */
void GPIO_IntDisable(const gpio_cfg_t *cfg)
{
    mxc_gpio_regs_t *gpio = MXC_GPIO_GET_GPIO(cfg->port);

    gpio->int_en_clr = cfg->mask;
}

/* ************************************************************************** */
uint32_t GPIO_IntStatus(const gpio_cfg_t *cfg)
{
    mxc_gpio_regs_t *gpio = MXC_GPIO_GET_GPIO(cfg->port);

    return (gpio->int_stat & cfg->mask);
}

/* ************************************************************************** */
void GPIO_IntClr(const gpio_cfg_t *cfg)
{
    mxc_gpio_regs_t *gpio = MXC_GPIO_GET_GPIO(cfg->port);

    gpio->int_clr = cfg->mask;
}

/* ************************************************************************** */
void GPIO_RegisterCallback(const gpio_cfg_t *cfg, gpio_callback_fn func, void *cbdata)
{
    uint32_t mask;
    unsigned int pin;

    mask = cfg->mask;
    pin = 0;

    while (mask) {
        if (mask & 1) {
            callback[cfg->port][pin] = func;
            cbparam[cfg->port][pin] = cbdata;
        }
        pin++;
        mask >>= 1;
    }
}

/* ************************************************************************** */
void GPIO_Handler(unsigned int port)
{
    uint32_t stat;
    unsigned int pin;

    MXC_ASSERT(port < MXC_CFG_GPIO_INSTANCES);

    mxc_gpio_regs_t *gpio = MXC_GPIO_GET_GPIO(port);

    stat = gpio->int_stat;
    gpio->int_clr = stat;

    pin = 0;

    while (stat) {
        if (stat & 1) {
            if(callback[port][pin]) {
                callback[port][pin](cbparam[port][pin]);
            }
        }
        pin++;
        stat >>= 1;
    }
}
