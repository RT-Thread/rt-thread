/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-01-11   HPMicro     First version
 * 2022-07-28   HPMicro     Fixed compiling warnings
 * 2023-05-08   HPMicro     Adapt RT-Thread V5.0.0
 * 2023-08-15   HPMicro     Enable pad loopback feature
 * 2024-01-08   HPMicro     Implemented pin_get
 * 2024-04-17   HPMicro     Refined pin irq implementation
 * 2024-05-31   HPMicro     Adapt later PIN driver framework
 * 2024-07-03   HPMicro     Determined the existence of GPIO via GPIO_DO_GPIOx macro
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
#include "hpm_soc_feature.h"


typedef struct
{
    uint32_t gpio_idx;
    uint32_t irq_num;
    struct rt_pin_irq_hdr *pin_irq_tbl;
} gpio_irq_map_t;

#ifdef GPIO_DO_GPIOA
static struct rt_pin_irq_hdr hpm_gpio0_a_pin_hdr[32];
#endif
#ifdef GPIO_DO_GPIOB
static struct rt_pin_irq_hdr hpm_gpio0_b_pin_hdr[32];
#endif
#ifdef GPIO_DO_GPIOC
static struct rt_pin_irq_hdr hpm_gpio0_c_pin_hdr[32];
#endif
#ifdef GPIO_DO_GPIOD
static struct rt_pin_irq_hdr hpm_gpio0_d_pin_hdr[32];
#endif
#ifdef GPIO_DO_GPIOE
static struct rt_pin_irq_hdr hpm_gpio0_e_pin_hdr[32];
#endif
#ifdef GPIO_DO_GPIOF
static struct rt_pin_irq_hdr hpm_gpio0_f_pin_hdr[32];
#endif
#ifdef GPIO_DO_GPIOV
static struct rt_pin_irq_hdr hpm_gpio0_v_pin_hdr[32];
#endif
#ifdef GPIO_DO_GPIOW
static struct rt_pin_irq_hdr hpm_gpio0_w_pin_hdr[32];
#endif
#ifdef GPIO_DO_GPIOX
static struct rt_pin_irq_hdr hpm_gpio0_x_pin_hdr[32];
#endif
#ifdef GPIO_DO_GPIOY
static struct rt_pin_irq_hdr hpm_gpio0_y_pin_hdr[32];
#endif
#ifdef GPIO_DO_GPIOZ
static struct rt_pin_irq_hdr hpm_gpio0_z_pin_hdr[32];
#endif

static const gpio_irq_map_t hpm_gpio_irq_map[] = {
#ifdef GPIO_DO_GPIOA
        { GPIO_IE_GPIOA, IRQn_GPIO0_A, hpm_gpio0_a_pin_hdr },
#endif
#ifdef GPIO_DO_GPIOB
        { GPIO_IE_GPIOB, IRQn_GPIO0_B, hpm_gpio0_b_pin_hdr },
#endif
#ifdef GPIO_DO_GPIOC
        { GPIO_IE_GPIOC, IRQn_GPIO0_C, hpm_gpio0_c_pin_hdr },
#endif
#ifdef GPIO_DO_GPIOD
        { GPIO_IE_GPIOD, IRQn_GPIO0_D, hpm_gpio0_d_pin_hdr },
#endif
#ifdef GPIO_DO_GPIOE
        { GPIO_IE_GPIOE, IRQn_GPIO0_E, hpm_gpio0_e_pin_hdr },
#endif
#ifdef GPIO_DO_GPIOF
        { GPIO_IE_GPIOF, IRQn_GPIO0_F, hpm_gpio0_f_pin_hdr },
#endif
#ifdef GPIO_DO_GPIOV
        { GPIO_IE_GPIOV, IRQn_GPIO0_V, hpm_gpio0_v_pin_hdr },
#endif
#ifdef GPIO_DO_GPIOW
        { GPIO_IE_GPIOW, IRQn_GPIO0_W, hpm_gpio0_w_pin_hdr },
#endif
#ifdef GPIO_DO_GPIOX
        { GPIO_IE_GPIOX, IRQn_GPIO0_X, hpm_gpio0_x_pin_hdr },
#endif
#ifdef GPIO_DO_GPIOY
        { GPIO_IE_GPIOY, IRQn_GPIO0_Y, hpm_gpio0_y_pin_hdr },
#endif
#ifdef GPIO_DO_GPIOZ
        { GPIO_IE_GPIOZ, IRQn_GPIO0_Z, hpm_gpio0_z_pin_hdr },
#endif
};

static struct rt_pin_irq_hdr *lookup_pin_irq_hdr_tbl(rt_base_t pin)
{
    struct rt_pin_irq_hdr *pin_irq_hdr_tbl = RT_NULL;
    uint32_t gpio_idx = pin >> 5;

    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_gpio_irq_map); i++)
    {
        if (hpm_gpio_irq_map[i].gpio_idx == gpio_idx)
        {
            pin_irq_hdr_tbl = hpm_gpio_irq_map[i].pin_irq_tbl;
            break;
        }
    }
    return pin_irq_hdr_tbl;
}

static int hpm_get_gpio_irq_num(uint32_t gpio_idx)
{
    int irq_num = -1;

    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_gpio_irq_map); i++)
    {
        if (hpm_gpio_irq_map[i].gpio_idx == gpio_idx)
        {
            irq_num = hpm_gpio_irq_map[i].irq_num;
            break;
        }
    }
    return irq_num;
}

static void hpm_gpio_isr(uint32_t gpio_idx, GPIO_Type *base)
{
    /* Lookup the Pin IRQ Header Table */
    struct rt_pin_irq_hdr *pin_irq_hdr = RT_NULL;
    for (uint32_t i = 0; i < ARRAY_SIZE(hpm_gpio_irq_map); i++)
    {
        if (hpm_gpio_irq_map[i].gpio_idx == gpio_idx)
        {
            pin_irq_hdr = hpm_gpio_irq_map[i].pin_irq_tbl;
            break;
        }
    }

    for(uint32_t pin_idx = 0; pin_idx < 32; pin_idx++)
    {
        if (gpio_check_pin_interrupt_flag(base, gpio_idx, pin_idx))
        {
            gpio_clear_pin_interrupt_flag(base, gpio_idx, pin_idx);

            if (pin_irq_hdr[pin_idx].hdr != RT_NULL)
            {
                pin_irq_hdr[pin_idx].hdr(pin_irq_hdr[pin_idx].args);
            }
        }
    }
}

#ifdef GPIO_DO_GPIOA
void gpioa_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOA, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_A, gpioa_isr)
#endif

#ifdef GPIO_DO_GPIOB
void gpiob_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOB, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_B, gpiob_isr)
#endif

#ifdef GPIO_DO_GPIOC
void gpioc_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOC, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_C, gpioc_isr)
#endif

#ifdef GPIO_DO_GPIOD
void gpiod_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOD, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_D, gpiod_isr)
#endif

#ifdef GPIO_DO_GPIOE
void gpioe_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOE, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_E, gpioe_isr)
#endif

#ifdef GPIO_DO_GPIOF
void gpiof_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOF, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_F, gpiof_isr)
#endif

#ifdef GPIO_DO_GPIOV
void gpiov_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOV, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_V, gpiox_isr)
#endif

#ifdef GPIO_DO_GPIOW
void gpiow_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOW, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_W, gpiox_isr)
#endif

#ifdef GPIO_DO_GPIOX
void gpiox_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOX, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_X, gpiox_isr)
#endif

#ifdef GPIO_DO_GPIOY
void gpioy_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOY, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_Y, gpioy_isr)
#endif

#ifdef GPIO_DO_GPIOZ
void gpioz_isr(void)
{
    hpm_gpio_isr(GPIO_IF_GPIOZ, HPM_GPIO0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_GPIO0_Z, gpioz_isr)
#endif

/**
 * @brief Get Pin index from name
 *
 * Name rule is : <GPIO NAME><Index>
 *  for example: PA00, PZ03
 *
 **/
static rt_base_t hpm_pin_get(const char *name)
{
    if (!(  (rt_strlen(name) == 4) &&
            (name[0] == 'P') &&
            ((('A' <= name[1]) && (name[1] <= 'F')) || (('V' <= name[1]) && (name[1] <= 'Z'))) &&
            (('0' <= name[2]) && (name[2] <= '9')) &&
            (('0' <= name[3]) && (name[3] <= '9'))
        ))
    {
        return -RT_EINVAL;
    }

    uint32_t gpio_idx = (name[1] <= 'F') ? (name[1] - 'A') : (11 + name[1] - 'V');
    uint32_t pin_idx = (uint32_t)(name[2] - '0') * 10 + (name[3] - '0');
    return (gpio_idx * 32 + pin_idx);
}

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
#ifdef GPIO_DI_GPIOZ
    case GPIO_DI_GPIOZ :
#ifdef HPM_BIOC
        HPM_BIOC->PAD[pin].FUNC_CTL = 3;
#endif
        break;
#endif
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
    HPM_IOC->PAD[pin].FUNC_CTL = IOC_PAD_FUNC_CTL_LOOP_BACK_MASK;
}

static rt_ssize_t hpm_pin_read(rt_device_t dev, rt_base_t pin)
{
    /* TODO: Check the validity of the pin value */
    uint32_t gpio_idx = pin >> 5;
    uint32_t pin_idx = pin & 0x1FU;

    return (rt_ssize_t) gpio_read_pin(HPM_GPIO0, gpio_idx, pin_idx);
}

static void hpm_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    /* TODO: Check the validity of the pin value */
    uint32_t gpio_idx = pin >> 5;
    uint32_t pin_idx = pin & 0x1FU;

    gpio_write_pin(HPM_GPIO0, gpio_idx, pin_idx, value);
}

static rt_err_t hpm_pin_attach_irq(struct rt_device *device,
                                   rt_base_t pin,
                                   rt_uint8_t mode,
                                   void (*hdr)(void *args),
                                   void *args)
{
    struct rt_pin_irq_hdr *pin_irq_hdr_tbl = lookup_pin_irq_hdr_tbl(pin);
    if (pin_irq_hdr_tbl == RT_NULL)
    {
        return -RT_EINVAL;
    }

    rt_base_t level = rt_hw_interrupt_disable();
    uint32_t pin_idx = pin & 0x1FUL;
    pin_irq_hdr_tbl[pin_idx].pin = pin;
    pin_irq_hdr_tbl[pin_idx].hdr = hdr;
    pin_irq_hdr_tbl[pin_idx].mode = mode;
    pin_irq_hdr_tbl[pin_idx].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t hpm_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    struct rt_pin_irq_hdr *pin_irq_hdr_tbl = lookup_pin_irq_hdr_tbl(pin);
    if (pin_irq_hdr_tbl == RT_NULL)
    {
        return -RT_EINVAL;
    }
    rt_base_t level = rt_hw_interrupt_disable();
    uint32_t pin_idx = pin & 0x1FUL;
    pin_irq_hdr_tbl[pin_idx].pin = -1;
    pin_irq_hdr_tbl[pin_idx].hdr = RT_NULL;
    pin_irq_hdr_tbl[pin_idx].mode = 0;
    pin_irq_hdr_tbl[pin_idx].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t hpm_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    /* TODO: Check the validity of the pin value */
    uint32_t gpio_idx = pin >> 5;
    uint32_t pin_idx = pin & 0x1FU;

    struct rt_pin_irq_hdr *pin_irq_hdr_tbl = lookup_pin_irq_hdr_tbl(pin);
    if (pin_irq_hdr_tbl == RT_NULL)
    {
        return -RT_EINVAL;
    }

    gpio_interrupt_trigger_t trigger;
    if (enabled == PIN_IRQ_ENABLE)
    {
        switch(pin_irq_hdr_tbl[pin_idx].mode)
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
        uint32_t irq_num = hpm_get_gpio_irq_num(gpio_idx);
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
        .pin_irq_enable = hpm_pin_irq_enable,
        .pin_get = hpm_pin_get,
};

int rt_hw_pin_init(void)
{
    int ret = RT_EOK;

    ret = rt_device_pin_register("pin", &hpm_pin_ops, RT_NULL);

    return ret;
}

INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* BSP_USING_GPIO */
