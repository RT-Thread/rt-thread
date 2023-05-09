/*
 * Copyright (c) 2021 hpm
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-01-11   hpmicro     First version
 * 2022-07-28   hpmicro     Fixed compiling warnings
 */

#include <rtthread.h>

#ifdef BSP_USING_GPIO
#include <rthw.h>
#include <rtdevice.h>
#include "board.h"
#include "drv_gpio.h"
#include "hpm_gpio_drv.h"
#include "hpm_gpiom_drv.h"
#include "hpm_clock_drv.h"

typedef struct
{
    uint32_t gpio_idx;
    uint32_t irq_num;
} gpio_irq_map_t;

static const gpio_irq_map_t hpm_gpio_irq_map[] = {
#ifdef IRQn_GPIO0_A
        { GPIO_IE_GPIOA, IRQn_GPIO0_A },
#endif
#ifdef IRQn_GPIO0_B
        { GPIO_IE_GPIOB, IRQn_GPIO0_B },
#endif
#ifdef IRQn_GPIO0_C
        { GPIO_IE_GPIOC, IRQn_GPIO0_C },
#endif
#ifdef GPIO_IE_GPIOD
        { GPIO_IE_GPIOD, IRQn_GPIO0_D },
#endif
#ifdef IRQn_GPIO0_E
        { GPIO_IE_GPIOE, IRQn_GPIO0_E },
#endif
#ifdef IRQn_GPIO0_F
        { GPIO_IE_GPIOF, IRQn_GPIO0_F },
#endif
#ifdef IRQn_GPIO0_X
        { GPIO_IE_GPIOX, IRQn_GPIO0_X },
#endif
#ifdef IRQn_GPIO0_Y
        { GPIO_IE_GPIOY, IRQn_GPIO0_Y },
#endif
#ifdef IRQn_GPIO0_Z
        { GPIO_IE_GPIOZ, IRQn_GPIO0_Z },
#endif
        };

static struct rt_pin_irq_hdr hpm_gpio_pin_hdr_tbl[IOC_PAD_PZ11];

static int hpm_get_gpi_irq_num(uint32_t gpio_idx)
{
    int irq_num = -1;

    for (uint32_t i = 0; i < sizeof(hpm_gpio_irq_map) / sizeof(hpm_gpio_irq_map[0]); i++)
    {
        if (hpm_gpio_irq_map[i].gpio_idx == gpio_idx)
        {
            irq_num = hpm_gpio_irq_map[i].irq_num;
            break;
        }
    }
    return irq_num;
}

static void hpm_gpio_isr(uint32_t gpio_index, GPIO_Type *base)
{
    uint32_t pin_idx = 0;
    for(pin_idx = 0; pin_idx < 32; pin_idx++)
    {
        if (gpio_check_pin_interrupt_flag(base, gpio_index, pin_idx))
        {
            uint32_t pin = gpio_index * 32U + pin_idx;
            gpio_clear_pin_interrupt_flag(base, gpio_index, pin_idx);
            if (hpm_gpio_pin_hdr_tbl[pin].hdr != RT_NULL)
            {
                hpm_gpio_pin_hdr_tbl[pin].hdr(hpm_gpio_pin_hdr_tbl[pin].args);
            }
        }
    }
}

#ifdef GPIO_IF_GPIOA
void gpioa_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOA, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_A, gpioa_isr)
#endif

#ifdef GPIO_IF_GPIOB
void gpiob_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOB, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_B, gpiob_isr)
#endif

#ifdef GPIO_IF_GPIOC
void gpioc_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOC, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_C, gpioc_isr)
#endif

#ifdef GPIO_IF_GPIOD
void gpiod_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOD, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_D, gpiod_isr)
#endif

#ifdef GPIO_IF_GPIOE
void gpioe_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOE, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_E, gpioe_isr)
#endif

#ifdef GPIO_IF_GPIOF
void gpiof_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOF, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_F, gpiof_isr)
#endif

#ifdef GPIO_IF_GPIOX
void gpiox_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOX, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_X, gpiox_isr)
#endif

#ifdef GPIO_IF_GPIOY
void gpioy_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOY, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_Y, gpioy_isr)
#endif

#ifdef GPIO_IF_GPIOZ
void gpioz_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOZ, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_Z, gpioz_isr)
#endif


static void hpm_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    /* TODO: Check the validity of the pin value */
    uint32_t gpio_idx = pin >> 5;
    uint32_t pin_idx = pin & 0x1FU;

    gpiom_set_pin_controller(HPM_GPIOM, gpio_idx, pin_idx, gpiom_soc_gpio0);

    HPM_IOC->PAD[pin].FUNC_CTL = 0;

    switch (gpio_idx)
    {
    case GPIO_DI_GPIOY :
        HPM_PIOC->PAD[pin].FUNC_CTL = 3;
        break;
    case GPIO_DI_GPIOZ :
        HPM_BIOC->PAD[pin].FUNC_CTL = 3;
        break;
    default :
        break;
    }

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        gpio_set_pin_output(HPM_GPIO0, gpio_idx, pin_idx);
        HPM_IOC->PAD[pin].PAD_CTL &=  ~(IOC_PAD_PAD_CTL_PS_MASK | IOC_PAD_PAD_CTL_PE_MASK | IOC_PAD_PAD_CTL_OD_MASK);
        break;
    case PIN_MODE_INPUT:
        gpio_set_pin_input(HPM_GPIO0, gpio_idx, pin_idx);
        HPM_IOC->PAD[pin].PAD_CTL &= ~(IOC_PAD_PAD_CTL_PS_MASK | IOC_PAD_PAD_CTL_PE_MASK);
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        gpio_set_pin_input(HPM_GPIO0, gpio_idx, pin_idx);
        HPM_IOC->PAD[pin].PAD_CTL = (HPM_IOC->PAD[pin].PAD_CTL & ~IOC_PAD_PAD_CTL_PS_MASK) | IOC_PAD_PAD_CTL_PE_SET(1);
        break;
    case PIN_MODE_INPUT_PULLUP:
        gpio_set_pin_input(HPM_GPIO0, gpio_idx, pin_idx);
        HPM_IOC->PAD[pin].PAD_CTL |= IOC_PAD_PAD_CTL_PE_SET(1) | IOC_PAD_PAD_CTL_PS_SET(1);
        break;
    case PIN_MODE_OUTPUT_OD:
        gpio_set_pin_output(HPM_GPIO0, gpio_idx, pin_idx);
        HPM_IOC->PAD[pin].PAD_CTL = (HPM_IOC->PAD[pin].PAD_CTL & ~(IOC_PAD_PAD_CTL_PS_MASK | IOC_PAD_PAD_CTL_PE_MASK)) | IOC_PAD_PAD_CTL_OD_SET(1);
        break;
    default:
        /* Invalid mode */
        break;
    }
}

static rt_int8_t hpm_pin_read(rt_device_t dev, rt_base_t pin)
{
    /* TODO: Check the validity of the pin value */
    uint32_t gpio_idx = pin >> 5;
    uint32_t pin_idx = pin & 0x1FU;

    return (rt_int8_t) gpio_read_pin(HPM_GPIO0, gpio_idx, pin_idx);
}

static void hpm_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    /* TODO: Check the validity of the pin value */
    uint32_t gpio_idx = pin >> 5;
    uint32_t pin_idx = pin & 0x1FU;

    gpio_write_pin(HPM_GPIO0, gpio_idx, pin_idx, value);
}

static rt_err_t hpm_pin_attach_irq(struct rt_device *device, rt_base_t pin, rt_uint8_t mode,
        void (*hdr)(void *args), void *args)
{

    rt_base_t level;
    level = rt_hw_interrupt_disable();
    hpm_gpio_pin_hdr_tbl[pin].pin = pin;
    hpm_gpio_pin_hdr_tbl[pin].hdr = hdr;
    hpm_gpio_pin_hdr_tbl[pin].mode = mode;
    hpm_gpio_pin_hdr_tbl[pin].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t hpm_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level;
    level = rt_hw_interrupt_disable();
    hpm_gpio_pin_hdr_tbl[pin].pin = -1;
    hpm_gpio_pin_hdr_tbl[pin].hdr = RT_NULL;
    hpm_gpio_pin_hdr_tbl[pin].mode = 0;
    hpm_gpio_pin_hdr_tbl[pin].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t hpm_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    /* TODO: Check the validity of the pin value */
    uint32_t gpio_idx = pin >> 5;
    uint32_t pin_idx = pin & 0x1FU;

    gpio_interrupt_trigger_t trigger;
    if (enabled == PIN_IRQ_ENABLE)
    {
        switch(hpm_gpio_pin_hdr_tbl[pin].mode)
        {
        case PIN_IRQ_MODE_RISING:
            trigger = gpio_interrupt_trigger_edge_rising;
            break;
        case PIN_IRQ_MODE_FALLING:
            trigger = gpio_interrupt_trigger_edge_falling;
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            trigger = gpio_interrupt_trigger_level_high;
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            trigger = gpio_interrupt_trigger_level_low;
            break;
        default:
            trigger = gpio_interrupt_trigger_edge_rising;
            break;
        }
        gpio_config_pin_interrupt(HPM_GPIO0, gpio_idx, pin_idx, trigger);
        uint32_t irq_num = hpm_get_gpi_irq_num(gpio_idx);
        gpio_enable_pin_interrupt(HPM_GPIO0, gpio_idx, pin_idx);
        intc_m_enable_irq_with_priority(irq_num, 1);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        gpio_disable_pin_interrupt(HPM_GPIO0, gpio_idx, pin_idx);
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

const static struct rt_pin_ops hpm_pin_ops = {
        .pin_mode = hpm_pin_mode,
        .pin_write = hpm_pin_write,
        .pin_read = hpm_pin_read,
        .pin_attach_irq = hpm_pin_attach_irq,
        .pin_detach_irq = hpm_pin_detach_irq,
        .pin_irq_enable = hpm_pin_irq_enable};

int rt_hw_pin_init(void)
{
    int ret = RT_EOK;

    ret = rt_device_pin_register("pin", &hpm_pin_ops, RT_NULL);

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* BSP_USING_GPIO */
