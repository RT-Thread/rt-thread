/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file gpio.c
 * @brief Driver to control the GPIO module.
 * @ingroup diag_gpio
 */

#include "sdk.h"
#include "gpio/gpio.h"
#include "registers/regsgpio.h"
#include "registers/regsiomuxc.h"
#include "gpio_map.h"

int32_t gpio_get_port_count(void)
{
    return HW_GPIO_INSTANCE_COUNT;
}

int gpio_set_gpio(int32_t port, int32_t pin)
{
    // Validate port and pin before indexing into the map arrays.
    if (port < 1 || port > HW_GPIO_INSTANCE_COUNT || pin < 0 || pin > 31)
    {
        debug_printf("Invalid GPIO port or pin number.\n");
        return INVALID_PARAMETER;
    }
    
    // Look up mux register address.
    uint32_t addr = k_gpio_mux_registers[port - 1][pin];
    if (!addr)
    {
        return INVALID_PARAMETER;
    }
    
    volatile uint32_t * reg = (volatile uint32_t *)addr;
    
    // Switch mux to ALT5, which is always GPIO mode. We're just using this register's
    // BM_ and BF_ macros because they are convenient, and is present on all three mx6.
    *reg = (*reg & ~BM_IOMUXC_SW_MUX_CTL_PAD_KEY_COL0_MUX_MODE)
         | BF_IOMUXC_SW_MUX_CTL_PAD_KEY_COL0_MUX_MODE_V(ALT5);
    
    return SUCCESS;
}

int32_t gpio_set_direction(int32_t port, int32_t pin, int32_t dir)
{
    uint32_t oldVal = 0, newVal = 0;

    if ((port > HW_GPIO_INSTANCE_COUNT) || (port < 1))
    {
        debug_printf("Invalid GPIO Instance GPIO_PORT%d parameter. GPIO_PORT1~GPIO_PORT%d is allowed.\n",
        		port, HW_GPIO_INSTANCE_COUNT);
        return INVALID_PARAMETER;
    }

    if ((pin > 31) || (pin < 0))
    {
        debug_printf("Invalid GPIO Pin %d parameter. Pin 0~31 is allowed.\n", pin);
        return INVALID_PARAMETER;
    }
    
    oldVal = HW_GPIO_GDIR_RD(port);

    if (dir == GPIO_GDIR_INPUT)
        newVal = oldVal & (~(1 << pin));
    else
        newVal = oldVal | (1 << pin);

    HW_GPIO_GDIR_WR(port, newVal);

    return 0; //SUCCESS;
}

int32_t gpio_get_direction(int32_t port, int32_t pin)
{
    if ((port > HW_GPIO_INSTANCE_COUNT) || (port < 1))
    {
        debug_printf("Invalid GPIO Instance GPIO_PORT%d parameter. GPIO_PORT1~GPIO_PORT%d is allowed.\n",
        		port, HW_GPIO_INSTANCE_COUNT);
        return INVALID_PARAMETER;
    }

    if ((pin > 31) || (pin < 0))
    {
        debug_printf("Invalid GPIO Pin %d parameter. Pin 0~31 is allowed.\n", pin);
        return INVALID_PARAMETER;
    }
    
    return (HW_GPIO_GDIR_RD(port) >> pin) & 1;
}


int32_t gpio_set_level(int32_t port, int32_t pin, uint32_t level)
{
    if ((port > HW_GPIO_INSTANCE_COUNT) || (port < 1))
    {
        debug_printf("Invalid GPIO Instance GPIO_PORT%d parameter. GPIO_PORT1~GPIO_PORT%d is allowed.\n",
        		port, HW_GPIO_INSTANCE_COUNT);
        return INVALID_PARAMETER;
    }

    if ((pin > 31) || (pin < 0))
    {
        debug_printf("Invalid GPIO Pin %d parameter. Pin 0~31 is allowed.\n", pin);
        return INVALID_PARAMETER;
    }

    uint32_t mask = 1 << pin;

    int32_t dir = HW_GPIO_GDIR_RD(port) & mask ? GPIO_GDIR_OUTPUT : GPIO_GDIR_INPUT;

    if (dir != GPIO_GDIR_OUTPUT)
    {
        printf("GPIO_PORT%d_%d is not configured to be output!\n", port, pin);
        return -1;
    }

    uint32_t value = HW_GPIO_DR_RD(port);   // read current value

    if (level == GPIO_LOW_LEVEL)            // fix it up
    	value &= ~mask;
    else if ( level == GPIO_HIGH_LEVEL)
    	value |= mask;

    HW_GPIO_DR_WR(port, value);             // write new value

    return 0; //SUCCESS;
}

int32_t gpio_get_level(int32_t port, int32_t pin)
{
    if ((port > HW_GPIO_INSTANCE_COUNT) || (port < 1))
    {
        debug_printf("Invalid GPIO Instance GPIO_PORT%d parameter. GPIO_PORT1~GPIO_PORT%d is allowed.\n",
        		port, HW_GPIO_INSTANCE_COUNT);
        return INVALID_PARAMETER;
    }

    if ((pin > 31) || (pin < 0))
    {
        debug_printf("Invalid GPIO Pin %d parameter. Pin 0~31 is allowed.\n", pin);
        return INVALID_PARAMETER;
    }

    uint32_t mask = 1 << pin;

    return HW_GPIO_DR_RD(port) & mask ? GPIO_HIGH_LEVEL : GPIO_LOW_LEVEL;
}

int32_t gpio_set_interrupt_config(int32_t port, int32_t pin, int32_t config)
{
    if ((port > HW_GPIO_INSTANCE_COUNT) || (port < 1))
    {
        debug_printf("Invalid GPIO Instance GPIO_PORT%d parameter. GPIO_PORT1~GPIO_PORT%d is allowed.\n",
        		port, HW_GPIO_INSTANCE_COUNT);
        return INVALID_PARAMETER;
    }

    if ((pin > 31) || (pin < 0))
    {
        debug_printf("Invalid GPIO Pin %d parameter. Pin 0~31 is allowed.\n", pin);
        return INVALID_PARAMETER;
    }

    if (pin < 16)
    {
        // GPIOs 0-15 use ICR1 register
    	uint32_t value = HW_GPIO_ICR1_RD(port);        // read current value
    	uint32_t field_offset = pin * 2;               // fields are 2 bits wide
        value &= ~(BM_GPIO_ICR1_ICR0 << field_offset); // clear specified field
        value |= config << field_offset;               // set specified field
        HW_GPIO_ICR1_WR(port, value);                  // write new value
    }
    else
    {
        // GPIOs 16-31 use ICR2 register
        uint32_t value = HW_GPIO_ICR2_RD(port);         // read current value
    	uint32_t field_offset = (pin - 16) * 2;         // fields are 2 bits wide
        value &= ~(BM_GPIO_ICR2_ICR16 << field_offset); // clear specified field
        value |= config << field_offset;                // set specified field
        HW_GPIO_ICR1_WR(port, value);                   // write new value
    }

    return 0; //SUCCESS;
}

int32_t gpio_set_interrupt_mask(int32_t port, int32_t pin, int32_t mask)
{
    if ((port > HW_GPIO_INSTANCE_COUNT) || (port < 1))
    {
        debug_printf("Invalid GPIO Instance GPIO_PORT%d parameter. GPIO_PORT1~GPIO_PORT%d is allowed.\n",
        		port, HW_GPIO_INSTANCE_COUNT);
        return INVALID_PARAMETER;
    }

    if ((pin > 31) || (pin < 0))
    {
        debug_printf("Invalid GPIO Pin %d parameter. Pin 0~31 is allowed.\n", pin);
        return INVALID_PARAMETER;
    }

    uint32_t value = HW_GPIO_IMR_RD(port);

    if (mask == GPIO_IMR_MASKED)
        value &= ~(1 << pin);
    else
        value |= 1 << pin;

    HW_GPIO_GDIR_WR(port, value);

    return 0; //SUCCESS;
}

int32_t gpio_get_interrupt_status(int32_t port, int32_t pin)
{
    if ((port > HW_GPIO_INSTANCE_COUNT) || (port < 1))
    {
        debug_printf("Invalid GPIO Instance GPIO_PORT%d parameter. GPIO_PORT1~GPIO_PORT%d is allowed.\n",
        		port, HW_GPIO_INSTANCE_COUNT);
        return INVALID_PARAMETER;
    }

    if ((pin > 31) || (pin < 0))
    {
        debug_printf("Invalid GPIO Pin %d parameter. Pin 0~31 is allowed.\n", pin);
        return INVALID_PARAMETER;
    }

    return HW_GPIO_ISR_RD(port) & (1 << pin) ? GPIO_ISR_ASSERTED : GPIO_ISR_NOT_ASSERTED;
}

int32_t gpio_clear_interrupt(int32_t port, int32_t pin)
{
    if ((port > HW_GPIO_INSTANCE_COUNT) || (port < 1))
    {
        debug_printf("Invalid GPIO Instance GPIO_PORT%d parameter. GPIO_PORT1~GPIO_PORT%d is allowed.\n",
        		port, HW_GPIO_INSTANCE_COUNT);
        return INVALID_PARAMETER;
    }

    if ((pin > 31) || (pin < 0))
    {
        debug_printf("Invalid GPIO Pin %d parameter. Pin 0~31 is allowed.\n", pin);
        return INVALID_PARAMETER;
    }

    uint32_t value = HW_GPIO_ISR_RD(port);
    value |= 1 << pin;
    HW_GPIO_ISR_WR(port, value);
    
    return 0; //SUCCESS;
}
