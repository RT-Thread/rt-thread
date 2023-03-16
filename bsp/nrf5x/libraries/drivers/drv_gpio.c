/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-06-16     guohp1128         first version
 */

#include "drv_gpio.h"

#ifdef RT_USING_PIN

static const struct pin_index pins[] =
{
    __NRF5X_PIN(0 ,  0, 0 ),
    __NRF5X_PIN(1 ,  0, 1 ),
    __NRF5X_PIN(2 ,  0, 2 ),
    __NRF5X_PIN(3 ,  0, 3 ),
    __NRF5X_PIN(4 ,  0, 4 ),
    __NRF5X_PIN(5 ,  0, 5 ),
    __NRF5X_PIN(6 ,  0, 6 ),
    __NRF5X_PIN(7 ,  0, 7 ),
    __NRF5X_PIN(8 ,  0, 8 ),
    __NRF5X_PIN(9 ,  0, 9 ),
    __NRF5X_PIN(10,  0, 10),
    __NRF5X_PIN(11,  0, 11),
    __NRF5X_PIN(12,  0, 12),
    __NRF5X_PIN(13,  0, 13),
    __NRF5X_PIN(14,  0, 14),
    __NRF5X_PIN(15,  0, 15),
    __NRF5X_PIN(16,  0, 16),
    __NRF5X_PIN(17,  0, 17),
    __NRF5X_PIN(18,  0, 18),
    __NRF5X_PIN(19,  0, 19),
    __NRF5X_PIN(20,  0, 20),
    __NRF5X_PIN(21,  0, 21),
    __NRF5X_PIN(22,  0, 22),
    __NRF5X_PIN(23,  0, 23),
    __NRF5X_PIN(24,  0, 24),
    __NRF5X_PIN(25,  0, 25),
    __NRF5X_PIN(26,  0, 26),
    __NRF5X_PIN(27,  0, 27),
    __NRF5X_PIN(28,  0, 28),
    __NRF5X_PIN(29,  0, 29),
    __NRF5X_PIN(30,  0, 30),
    __NRF5X_PIN(31,  0, 31),
#if defined(SOC_NRF52840) || defined(SOC_NRF5340)
    __NRF5X_PIN(32,  1, 0 ),
    __NRF5X_PIN(33,  1, 1 ),
    __NRF5X_PIN(34,  1, 2 ),
    __NRF5X_PIN(35,  1, 3 ),
    __NRF5X_PIN(36,  1, 4 ),
    __NRF5X_PIN(37,  1, 5 ),
    __NRF5X_PIN(38,  1, 6 ),
    __NRF5X_PIN(39,  1, 7 ),
    __NRF5X_PIN(40,  1, 8 ),
    __NRF5X_PIN(41,  1, 9 ),
    __NRF5X_PIN(42,  1, 10),
    __NRF5X_PIN(43,  1, 11),
    __NRF5X_PIN(44,  1, 12),
    __NRF5X_PIN(45,  1, 13),
    __NRF5X_PIN(46,  1, 14),
    __NRF5X_PIN(47,  1, 15),
#endif /* SOC_NRF52840 5340*/
};

/* EVENTS_IN[n](n=0..7) and EVENTS_PORT */
static struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
{
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
};

#define ITEM_NUM(items) sizeof(items) / sizeof(items[0])

/* pin: the number of pins */
static const struct pin_index *get_pin(uint8_t pin)
{
    const struct pin_index *index;

    if (pin < ITEM_NUM(pins))
    {
        index = &pins[pin];
        if (index->index == -1)
            index = RT_NULL;
    }
    else
    {
        index = RT_NULL;
    }

    return index;
};

static void nrf5x_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    nrf_gpio_pin_write(pin, value);
}

static int nrf5x_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    const struct pin_index *index;

    value = PIN_LOW;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return value;
    }

    value = nrf_gpio_pin_read(pin);

    return value;
}

static void nrf5x_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    const struct pin_index *index;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return;
    }

    if (mode == PIN_MODE_OUTPUT)
    {
        /* output setting */
        nrf_gpio_cfg_output(pin);
    }
    else if (mode == PIN_MODE_INPUT)
    {
        /* input setting: not pull. */
        nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_NOPULL);
    }
    else if (mode == PIN_MODE_INPUT_PULLUP)
    {
        /* input setting: pull up. */
        nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_PULLUP);
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        /* input setting: pull down. */
        nrf_gpio_cfg_input(pin, NRF_GPIO_PIN_PULLDOWN);
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        /* output setting: od. */
        nrf_gpio_cfg(
        pin,
        NRF_GPIO_PIN_DIR_OUTPUT,
        NRF_GPIO_PIN_INPUT_DISCONNECT,
        NRF_GPIO_PIN_NOPULL,
        NRF_GPIO_PIN_S0D1,
        NRF_GPIO_PIN_NOSENSE);
    }
}

static void pin_irq_hdr(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    int i;
    int irq_quantity;

    irq_quantity = ITEM_NUM(pin_irq_hdr_tab);
    for(i = 0; i < irq_quantity; i++)
    {
        if(pin_irq_hdr_tab[i].pin == pin)
        {
            pin_irq_hdr_tab[i].hdr(pin_irq_hdr_tab[i].args);
        }
    }
}

/*  args = true : hi_accuracy(IN_EVENT)
 *  args = false: lo_accuracy(PORT_EVENT)
 */
static rt_err_t nrf5x_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                     rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    const struct pin_index *index;
    rt_int32_t irqindex = -1;
    rt_base_t level;
    nrfx_err_t err_code;
    int i;
    int irq_quantity;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }

    irq_quantity = ITEM_NUM(pin_irq_hdr_tab);
    for(i = 0; i < irq_quantity; i++)
    {
        if(pin_irq_hdr_tab[i].pin != -1)
        {
            irqindex = -1;
            continue;
        }
        else
        {
            irqindex = i;
            break;
        }
    }
    if(irqindex == -1)
    {
        return RT_ENOMEM;
    }

    level = rt_hw_interrupt_disable();
    pin_irq_hdr_tab[irqindex].pin  = pin;
    pin_irq_hdr_tab[irqindex].hdr  = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;

  if(mode == PIN_IRQ_MODE_RISING)
    {
        nrfx_gpiote_in_config_t inConfig = NRFX_GPIOTE_CONFIG_IN_SENSE_LOTOHI(args);
        inConfig.pull = NRF_GPIO_PIN_PULLDOWN;
        err_code = nrfx_gpiote_in_init(pin, &inConfig, pin_irq_hdr);
    }

    else if(mode == PIN_IRQ_MODE_FALLING)
    {
        nrfx_gpiote_in_config_t inConfig = NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO(args);
        inConfig.pull = NRF_GPIO_PIN_PULLUP;
        err_code = nrfx_gpiote_in_init(pin, &inConfig, pin_irq_hdr);
    }

    else if(mode == PIN_IRQ_MODE_RISING_FALLING)
    {
        nrfx_gpiote_in_config_t inConfig = NRFX_GPIOTE_CONFIG_IN_SENSE_TOGGLE(args);
        inConfig.pull = NRF_GPIO_PIN_PULLUP;
        err_code = nrfx_gpiote_in_init(pin, &inConfig, pin_irq_hdr);
    }

    rt_hw_interrupt_enable(level);

    switch(err_code)
    {
        case NRFX_ERROR_BUSY:
            return RT_EBUSY;
        case NRFX_SUCCESS:
            return RT_EOK;
        case NRFX_ERROR_NO_MEM:
            return RT_ENOMEM;
        default:
            return RT_ERROR;
    }
}

static rt_err_t nrf5x_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    const struct pin_index *index;
    rt_base_t level;
    int i;
    int irq_quantity;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }

    irq_quantity = ITEM_NUM(pin_irq_hdr_tab);
    for(i = 0; i < irq_quantity; i++)
    {
        if(pin_irq_hdr_tab[i].pin == pin)
        {
            level = rt_hw_interrupt_disable();
            pin_irq_hdr_tab[i].pin  = -1;
            pin_irq_hdr_tab[i].hdr  = RT_NULL;
            pin_irq_hdr_tab[i].mode = 0;
            pin_irq_hdr_tab[i].args = RT_NULL;
            nrfx_gpiote_in_uninit(pin);
            rt_hw_interrupt_enable(level);
            break;
        }
    }
    if(i >= irq_quantity)
    {
        return RT_ENOSYS;
    }
    return RT_EOK;
}

static rt_err_t nrf5x_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint32_t enabled)
{
    const struct pin_index *index;
    rt_base_t level;
    int i;
    int irq_quantity;

    index = get_pin(pin);
    if (index == RT_NULL)
    {
        return RT_ENOSYS;
    }

    irq_quantity = ITEM_NUM(pin_irq_hdr_tab);
    for(i = 0; i < irq_quantity; i++)
    {
        if(pin_irq_hdr_tab[i].pin == pin)
        {
            level = rt_hw_interrupt_disable();
            if(enabled == PIN_IRQ_ENABLE)
            {
                nrfx_gpiote_in_event_enable(pin,enabled);
            }
            else if(enabled == PIN_IRQ_DISABLE)
            {
                nrfx_gpiote_in_event_disable(pin);
            }
            rt_hw_interrupt_enable(level);
            break;
        }
    }

    if(i >= irq_quantity)
    {
        return RT_ENOSYS;
    }
    return RT_EOK;
}

const static struct rt_pin_ops _nrf5x_pin_ops =
{
    nrf5x_pin_mode,
    nrf5x_pin_write,
    nrf5x_pin_read,
    nrf5x_pin_attach_irq,
    nrf5x_pin_dettach_irq,
    nrf5x_pin_irq_enable,
    RT_NULL,
};

rt_err_t rt_hw_pin_init(void)
{
    nrfx_err_t err_code;

    err_code = (nrfx_err_t)rt_device_pin_register("pin", &_nrf5x_pin_ops, RT_NULL);
    err_code = nrfx_gpiote_init(NRFX_GPIOTE_CONFIG_IRQ_PRIORITY);

    switch(err_code)
    {
        case NRFX_ERROR_INVALID_STATE:
            return -RT_EINVAL;
        case NRFX_SUCCESS:
            return RT_EOK;
        default:
            return -RT_ERROR;;
    }

}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#if defined(SOC_NRF5340)
/* test GPIO write, read, input interrupt */
#define DK_BOARD_LED_1  28
#define DK_BOARD_LED_2  29
#define DK_BOARD_LED_3  30
#define DK_BOARD_LED_4  31

#define DK_BOARD_BUTTON_1  23
#define DK_BOARD_BUTTON_2  24
#define DK_BOARD_BUTTON_3  8
#define DK_BOARD_BUTTON_4  9
#else
/* test GPIO write, read, input interrupt */
#define DK_BOARD_LED_1  13
#define DK_BOARD_LED_2  14
#define DK_BOARD_LED_3  15
#define DK_BOARD_LED_4  16

#define DK_BOARD_BUTTON_1  11
#define DK_BOARD_BUTTON_2  12
#define DK_BOARD_BUTTON_3  24
#define DK_BOARD_BUTTON_4  25
#endif

void button_1_callback(void *args)
{
    static int flag1 = 0;
    if(flag1 == 0)
    {
        flag1 = 1;
        rt_pin_write(DK_BOARD_LED_1, PIN_LOW);
    }
    else
    {
        flag1 = 0;
        rt_pin_write(DK_BOARD_LED_1, PIN_HIGH);
    }
}
void button_2_callback(void *args)
{
    static int flag2 = 0;
    if(flag2 == 0)
    {
        flag2 = 1;
        rt_pin_write(DK_BOARD_LED_2, PIN_LOW);
    }
    else
    {
        flag2 = 0;
        rt_pin_write(DK_BOARD_LED_2, PIN_HIGH);
    }
}
void button_3_callback(void *args)
{
    static int flag3 = 0;
    if(flag3 == 0)
    {
        flag3 = 1;
        rt_pin_write(DK_BOARD_LED_3, PIN_LOW);
    }
    else
    {
        flag3 = 0;
        rt_pin_write(DK_BOARD_LED_3, PIN_HIGH);
    }
}
void button_4_callback(void *args)
{
    static int flag4 = 0;
    if(flag4 == 0)
    {
        flag4 = 1;
        rt_pin_write(DK_BOARD_LED_4, PIN_LOW);
    }
    else
    {
        flag4 = 0;
        rt_pin_write(DK_BOARD_LED_4, PIN_HIGH);
    }
}

void gpio_sample(void)
{
    rt_pin_mode(DK_BOARD_LED_1, PIN_MODE_OUTPUT);
    rt_pin_mode(DK_BOARD_LED_2, PIN_MODE_OUTPUT);
    rt_pin_mode(DK_BOARD_LED_3, PIN_MODE_OUTPUT);
    rt_pin_mode(DK_BOARD_LED_4, PIN_MODE_OUTPUT);

    rt_pin_write(DK_BOARD_LED_1, PIN_HIGH);
    rt_pin_write(DK_BOARD_LED_2, PIN_HIGH);
    rt_pin_write(DK_BOARD_LED_3, PIN_HIGH);
    rt_pin_write(DK_BOARD_LED_4, PIN_HIGH);

    rt_pin_attach_irq(DK_BOARD_BUTTON_1, PIN_IRQ_MODE_FALLING,
                                    button_1_callback, (void*) true); //true: hi_accuracy(IN_EVENT),false: lo_accuracy(PORT_EVENT)
    rt_pin_irq_enable(DK_BOARD_BUTTON_1, PIN_IRQ_ENABLE);

    rt_pin_attach_irq(DK_BOARD_BUTTON_2, PIN_IRQ_MODE_FALLING,
                                    button_2_callback, (void*) true); //true: hi_accuracy(IN_EVENT),false: lo_accuracy(PORT_EVENT)
    rt_pin_irq_enable(DK_BOARD_BUTTON_2, PIN_IRQ_ENABLE);

    rt_pin_attach_irq(DK_BOARD_BUTTON_3, PIN_IRQ_MODE_FALLING,
                                    button_3_callback, (void*) true); //true: hi_accuracy(IN_EVENT),false: lo_accuracy(PORT_EVENT)
    rt_pin_irq_enable(DK_BOARD_BUTTON_3, PIN_IRQ_ENABLE);

    rt_pin_attach_irq(DK_BOARD_BUTTON_4, PIN_IRQ_MODE_FALLING,
                                    button_4_callback, (void*) false); //true: hi_accuracy(IN_EVENT),false: lo_accuracy(PORT_EVENT)
    rt_pin_irq_enable(DK_BOARD_BUTTON_4, PIN_IRQ_ENABLE);
}
MSH_CMD_EXPORT(gpio_sample, gpio sample);

#endif /* RT_USING_PIN */
