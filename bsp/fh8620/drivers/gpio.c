/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "fh_def.h"
#include "gpio.h"
#include "libraries/inc/fh_gpio.h"
#include "interrupt.h"
#include "board_info.h"
#include <rtdevice.h>
#include "fh_arch.h"
//#define FH_GPIO_DEBUG

#ifdef FH_GPIO_DEBUG
#define PRINT_GPIO_DBG(fmt, args...)     \
    do                                  \
    {                                   \
        rt_kprintf("FH_GPIO_DEBUG: ");   \
        rt_kprintf(fmt, ## args);       \
    }                                   \
    while(0)
#else
#define PRINT_GPIO_DBG(fmt, args...)  do { } while (0)
#endif

int gpio_available[NUM_OF_GPIO];
extern struct rt_irq_desc irq_desc[];

static inline rt_uint32_t gpio_to_base(rt_uint32_t gpio)
{
    if (gpio >= 32 && gpio < 64)
    {
        return GPIO1_REG_BASE;
    }
    else if(gpio < 32)
    {
        return GPIO0_REG_BASE;
    }
    else
    {
        rt_kprintf("ERROR: %s, incorrect GPIO num\n", __func__);
        return -RT_ERROR;
    }
}

static inline rt_uint32_t irq_to_base(rt_uint32_t irq)
{
    return (irq-NR_INTERNAL_IRQS > 32) ? GPIO1_REG_BASE : GPIO0_REG_BASE;
}

static inline rt_uint32_t irq_to_bit(rt_uint32_t irq)
{
    if(irq >= NR_INTERNAL_IRQS && irq < NR_INTERNAL_IRQS + 32)
        return 0;
    else
        return 32;
}

rt_uint32_t gpio_to_irq(rt_uint32_t gpio)
{
    return (gpio + NR_INTERNAL_IRQS);
}

void gpio_enable_debounce(rt_uint32_t gpio)
{
    rt_uint32_t tmp, base, offset;

    offset = gpio % 32;
    base = gpio_to_base(gpio);

    tmp = GET_REG(base + REG_GPIO_DEBOUNCE);

    tmp |= BIT(offset);

    SET_REG(base + REG_GPIO_DEBOUNCE, tmp);
}

void gpio_disable_debounce(rt_uint32_t gpio)
{
    rt_uint32_t tmp, base, offset;

    offset = gpio % 32;
    base = gpio_to_base(gpio);

    tmp = GET_REG(base + REG_GPIO_DEBOUNCE);

    tmp &= ~BIT(offset);

    SET_REG(base + REG_GPIO_DEBOUNCE, tmp);
}

int gpio_get_value(rt_uint32_t gpio)
{
    rt_uint32_t tmp, base, offset;

    offset = gpio % 32;
    base = gpio_to_base(gpio);

    tmp = GET_REG(base + REG_GPIO_SWPORTA_DDR);
    tmp &= BIT(offset);

    if (tmp) {
        tmp = GET_REG(base + REG_GPIO_SWPORTA_DR);
    } else {
        tmp = GET_REG(base + REG_GPIO_EXT_PORTA);
    }
    tmp &= BIT(offset);
    tmp = tmp >> offset;
    return tmp;
}

void gpio_set_value(rt_uint32_t gpio, int val)
{
    rt_uint32_t tmp, base, offset;

    offset = gpio % 32;
    base = gpio_to_base(gpio);

    tmp = GET_REG(base + REG_GPIO_SWPORTA_DR);

    if(val)
        tmp |= BIT(offset);
    else
        tmp &= ~BIT(offset);

    SET_REG(base + REG_GPIO_SWPORTA_DR, tmp);

}


int gpio_get_direction(rt_uint32_t gpio)
{
    rt_uint32_t tmp, base, offset;

    offset = gpio % 32;
    base = gpio_to_base(gpio);

    tmp = GET_REG(base + REG_GPIO_SWPORTA_DDR);

    tmp &= BIT(offset);
    tmp = tmp >> offset;
    return tmp;
}

void gpio_set_direction(rt_uint32_t gpio, rt_uint32_t direction)
{
    rt_uint32_t tmp, base, offset;

    offset = gpio % 32;
    base = gpio_to_base(gpio);

    tmp = GET_REG(base + REG_GPIO_SWPORTA_DDR);

    if(direction == GPIO_DIR_OUTPUT)
        tmp |= BIT(offset);
    else
        tmp &= ~BIT(offset);

    SET_REG(base + REG_GPIO_SWPORTA_DDR, tmp);
}


int gpio_set_irq_type(rt_uint32_t gpio, rt_uint32_t type)
{
    rt_uint32_t int_type, int_polarity;
    rt_uint32_t bit = gpio % 32;
    rt_uint32_t base;
    base = gpio_to_base(gpio);

    int_type = GET_REG(base + REG_GPIO_INTTYPE_LEVEL);
    int_polarity = GET_REG(base + REG_GPIO_INT_POLARITY);

    switch (type & IRQ_TYPE_TRIGGER_MASK) {
    case IRQ_TYPE_EDGE_BOTH:
        int_type |= BIT(bit);
        // toggle trigger
        if (gpio_get_value(gpio))
            int_polarity &= ~BIT(bit);
        else
            int_polarity |= BIT(bit);
        break;
    case IRQ_TYPE_EDGE_RISING:
        int_type |= BIT(bit);
        int_polarity |= BIT(bit);
        break;
    case IRQ_TYPE_EDGE_FALLING:
        int_type |= BIT(bit);
        int_polarity &= ~BIT(bit);
        break;
    case IRQ_TYPE_LEVEL_HIGH:
        int_type &= ~BIT(bit);
        int_polarity |= BIT(bit);
        break;
    case IRQ_TYPE_LEVEL_LOW:
        int_type &= ~BIT(bit);
        int_polarity &= ~BIT(bit);
        break;
    case IRQ_TYPE_NONE:
        return 0;
    default:
        return -RT_ERROR;
    }
    SET_REG(base + REG_GPIO_INTTYPE_LEVEL, int_type);
    SET_REG(base + REG_GPIO_INT_POLARITY, int_polarity);
    return 0;
}

int gpio_irq_mask(rt_uint32_t irq)
{
    rt_uint32_t tmp, base, bit;

    base = irq_to_base(irq);
    bit = irq_to_bit(irq);

    tmp = GET_REG(base + REG_GPIO_INTMASK);
    tmp |= BIT(irq - NR_INTERNAL_IRQS - bit);
    SET_REG(base + REG_GPIO_INTMASK, tmp);
    return 0;
}

int gpio_irq_unmask(rt_uint32_t irq)
{
    rt_uint32_t tmp, base, bit;

    base = irq_to_base(irq);
    bit = irq_to_bit(irq);

    tmp = GET_REG(base + REG_GPIO_INTMASK);
    tmp &= ~BIT((irq - NR_INTERNAL_IRQS - bit));
    SET_REG(base + REG_GPIO_INTMASK, tmp);
    return 0;
}

void gpio_irq_enable(rt_uint32_t irq)
{
    rt_uint32_t tmp, base, bit;

    base = irq_to_base(irq);
    bit = irq_to_bit(irq);

    tmp = GET_REG(base + REG_GPIO_INTEN);
    tmp |= BIT(irq - NR_INTERNAL_IRQS - bit);
    SET_REG(base + REG_GPIO_INTEN, tmp);
}

void gpio_irq_disable(rt_uint32_t irq)
{
    rt_uint32_t tmp, base, bit;

    base = irq_to_base(irq);
    bit = irq_to_bit(irq);

    tmp = GET_REG(base + REG_GPIO_INTEN);
    tmp &= ~BIT((irq - NR_INTERNAL_IRQS - bit));
    SET_REG(base + REG_GPIO_INTEN, tmp);
}

static void fh_gpio_interrupt(int irq, void *param)
{
    rt_uint32_t irq_status;
    int gpio_num, gpio;
    rt_uint32_t base;
    struct fh_gpio_obj *gpio_obj = (struct fh_gpio_obj *)param;

    //rt_kprintf("fh_gpio_interrupt start\n");

    //fixme: spin lock???
    base = (irq==40) ? GPIO0_REG_BASE : GPIO1_REG_BASE;

    irq_status = GET_REG(base + REG_GPIO_INTSTATUS);

    if (irq_status == 0) {
        rt_kprintf("gpio irq status is zero.\n");
        return;
    }

    /* temporarily mask (level sensitive) parent IRQ */
    gpio_irq_mask(irq);

    gpio_num = __rt_ffs(irq_status) - 1;

    SET_REG(base + REG_GPIO_PORTA_EOI, BIT(gpio_num));

    gpio = gpio_num + ((irq==40) ? 0 : 32);

    //generic_handle_irq(gpio_to_irq(gpio));
    if(irq_desc[gpio_to_irq(gpio)].handler)
        irq_desc[gpio_to_irq(gpio)].handler(gpio_to_irq(gpio), irq_desc[gpio_to_irq(gpio)].param);

    gpio_irq_mask(irq);
    /* now it may re-trigger */
}


int gpio_direction_input(rt_uint32_t gpio)
{
    rt_uint32_t reg, base;

    if(gpio > NUM_OF_GPIO)
    {
        rt_kprintf("ERROR: %s, incorrect GPIO num\n", __func__);
        return -RT_ERROR;
    }

    if(!gpio_available[gpio])
    {
        rt_kprintf("ERROR: %s, GPIO %d is not available\n", __func__, gpio);
        return -RT_EBUSY;
    }

    base = gpio_to_base(gpio);
    gpio = gpio % 32;


    //fixme: lock
    //spin_lock_irqsave(&chip->lock, flags);
    reg = GET_REG(base + REG_GPIO_SWPORTA_DDR);
    reg &= ~(1 << gpio);
    SET_REG(base + REG_GPIO_SWPORTA_DDR, reg);
    //spin_unlock_irqrestore(&chip->lock, flags);

    return 0;
}

int gpio_direction_output(rt_uint32_t gpio, rt_uint32_t val)
{
    rt_uint32_t reg, base;

    if(gpio > NUM_OF_GPIO)
    {
        rt_kprintf("ERROR: %s, incorrect GPIO num\n", __func__);
        return -RT_ERROR;
    }

    if(!gpio_available[gpio])
    {
        rt_kprintf("ERROR: %s, GPIO %d is not available\n", __func__, gpio);
        return -RT_EBUSY;
    }

    base = gpio_to_base(gpio);
    gpio = gpio % 32;

    //fixme: lock
    //spin_lock_irqsave(&chip->lock, flags);
    reg = GET_REG(base + REG_GPIO_SWPORTA_DDR);
    reg |= (1 << gpio);
    SET_REG(base + REG_GPIO_SWPORTA_DDR, reg);

    reg = GET_REG(base + REG_GPIO_SWPORTA_DR);

    if(val)
        reg |= (1 << gpio);
    else
        reg &= ~(1 << gpio);
    SET_REG(base + REG_GPIO_SWPORTA_DR, reg);

    //spin_unlock_irqrestore(&chip->lock, flags);

    return 0;
}

int gpio_request(rt_uint32_t gpio)
{
    if(gpio > NUM_OF_GPIO)
    {
        rt_kprintf("ERROR: %s, incorrect GPIO num\n", __func__);
        return -RT_ERROR;
    }
    gpio_available[gpio] = 1;
    return 0;
}

int gpio_release(rt_uint32_t gpio)
{
    if(gpio > NUM_OF_GPIO)
    {
        rt_kprintf("ERROR: %s, incorrect GPIO num\n", __func__);
        return -RT_ERROR;
    }
    gpio_available[gpio] = 0;
    return 0;
}

int fh_gpio_probe(void *priv_data)
{
    struct fh_gpio_obj *gpio_obj = (struct fh_gpio_obj *)priv_data;
    int i;

    if(gpio_obj->id == 0){
    	  rt_hw_interrupt_install(gpio_obj->irq, fh_gpio_interrupt, (void *)gpio_obj, "gpio_0");
    }
    else if(gpio_obj->id == 1){
    	rt_hw_interrupt_install(gpio_obj->irq, fh_gpio_interrupt, (void *)gpio_obj, "gpio_1");
    }



    rt_hw_interrupt_umask(gpio_obj->irq);

    for(i=0; i<32; i++)
    {
        irq_desc[NR_INTERNAL_IRQS + 32 * gpio_obj->id + i].param = gpio_obj;
    }

    return 0;
}

int fh_gpio_exit(void *priv_data)
{
    return 0;
}

struct fh_board_ops gpio_driver_ops =
{
        .probe = fh_gpio_probe,
        .exit = fh_gpio_exit,
};

void rt_hw_gpio_init(void)
{
    PRINT_GPIO_DBG("%s start\n", __func__);
    rt_memset(gpio_available, 0, sizeof(int) * NUM_OF_GPIO);
    fh_board_driver_register("gpio", &gpio_driver_ops);
    PRINT_GPIO_DBG("%s end\n", __func__);
}


