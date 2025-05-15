/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-11-19     greedyhao         first version
 * 2025-05-15     kurisaW           support gpio interrupt
 */

#include "drv_gpio.h"

#ifdef RT_USING_PIN

// #define DRV_DEBUG
#define LOG_TAG             "drv.gpio"
#include <drv_log.h>

struct port_info
{
    rt_uint8_t start_pin;
    rt_uint8_t delta_pin;
    rt_uint8_t total_pin;
};

/* It needs to be adjusted to the hardware. */
static const struct port_info port_table[] =
{
    {0, 8, 0},      /* PA0-PA7 */
    {0, 5, 8},      /* PB0-PB4 */
    {0, 8, 13},     /* PE0-PE7 */
    {0, 6, 21},     /* PF0-PF5 */
};

static const hal_sfr_t port_sfr[] =
{
    GPIOA_BASE,
    GPIOB_BASE,
    GPIOE_BASE,
    GPIOF_BASE,
};

static struct ab32_pin_irq pin_irq_table[8] = {0}; // For WAKEUP_CRICUIT_0 to _7
static rt_mq_t gpio_irq_mq = RT_NULL;

static rt_uint8_t _pin_port(rt_uint32_t pin)
{
    rt_uint8_t port = 0;
    for (port = 0; port < 3; port++) {
        if (pin < (port_table[port].total_pin + port_table[port].delta_pin)) {
            break;
        }
    }
    return port;
}

#define PIN_NUM(port, no)       ((rt_uint8_t)(port_table[port].total_pin + no - port_table[port].start_pin))
#define PIN_PORT(pin)           _pin_port(pin)
#define PORT_SFR(port)          (port_sfr[(port)])
#define PIN_NO(pin)             (rt_uint8_t)((pin) & 0xFu)

static rt_base_t ab32_pin_get(const char *name)
{
    rt_base_t pin = 0;
    int hw_port_num, hw_pin_num = 0;
    int i, name_len;

    name_len = rt_strlen(name);

    if ((name_len < 4) || (name_len >= 6))
    {
        return -RT_EINVAL;
    }
    if ((name[0] != 'P') || (name[2] != '.'))
    {
        return -RT_EINVAL;
    }

    if ((name[1] >= 'A') && (name[1] <= 'B'))
    {
        hw_port_num = (int)(name[1] - 'A');
    }
    else if ((name[1] >= 'E') && (name[1] <= 'G'))
    {
        hw_port_num = (int)(name[1] - 'A') - 2;  /* Without 'C' and 'D'. */
    }
    else
    {
        return -RT_EINVAL;
    }

    for (i = 3; i < name_len; i++)
    {
        hw_pin_num *= 10;
        hw_pin_num += name[i] - '0';
    }

    pin = PIN_NUM(hw_port_num, hw_pin_num);
    LOG_D("name=%s", name);
    LOG_D("hw_port_num=%d hw_pin_num=%d pin=%d", hw_port_num, hw_pin_num, pin);

    return pin;
}

static void ab32_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    rt_uint8_t port = PIN_PORT(pin);
    rt_uint8_t gpio_pin  = pin - port_table[port].total_pin;
    hal_gpio_write(PORT_SFR(port), gpio_pin, (rt_uint8_t)value);
}

static rt_ssize_t ab32_pin_read(rt_device_t dev, rt_base_t pin)
{
    rt_uint8_t port = PIN_PORT(pin);
    rt_uint8_t gpio_pin  = pin - port_table[port].total_pin;
    return hal_gpio_read(PORT_SFR(port), gpio_pin);
}

static void ab32_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    struct gpio_init gpio_init;
    rt_uint8_t port = PIN_PORT(pin);

    gpio_init.pin = BIT(pin - port_table[port].total_pin);
    gpio_init.de  = GPIO_DIGITAL;
    gpio_init.af_con = GPIO_AFDIS;
    LOG_D("port=%d pin=%d", port, gpio_init.pin);

    switch (mode)
    {
    case PIN_MODE_INPUT:
        gpio_init.pull = GPIO_NOPULL;
        gpio_init.dir = GPIO_DIR_INPUT;
        break;
    case PIN_MODE_INPUT_PULLUP:
        gpio_init.pull = GPIO_PULLUP;
        gpio_init.dir = GPIO_DIR_INPUT;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        gpio_init.pull = GPIO_PULLDOWN;
        gpio_init.dir = GPIO_DIR_INPUT;
        break;
    case PIN_MODE_OUTPUT:
    case PIN_MODE_OUTPUT_OD:
    default:
        gpio_init.pull = GPIO_NOPULL;
        gpio_init.dir = GPIO_DIR_OUTPUT;
        break;
    }
    hal_gpio_init(PORT_SFR(port), &gpio_init);
}

static rt_err_t get_port_pin(rt_base_t pin, rt_uint8_t *port, rt_uint8_t *hw_pin)
{
    rt_uint8_t i;
    for (i = 0; i < sizeof(port_table) / sizeof(port_table[0]); i++)
    {
        if (pin >= port_table[i].total_pin &&
            pin < port_table[i].total_pin + port_table[i].delta_pin)
        {
            *port = i;
            *hw_pin = pin - port_table[i].total_pin + port_table[i].start_pin;
            return RT_EOK;
        }
    }
    return -RT_EINVAL;
}

static rt_int32_t get_wakeup_circuit(rt_base_t pin)
{
    /* Special interrupt pins */
    if (pin == PIN_NUM(0, 7)) return WAKEUP_CRICUIT_0; // PA7
    if (pin == PIN_NUM(1, 1)) return WAKEUP_CRICUIT_1; // PB1
    if (pin == PIN_NUM(1, 2)) return WAKEUP_CRICUIT_2; // PB2
    if (pin == PIN_NUM(1, 3)) return WAKEUP_CRICUIT_3; // PB3
    if (pin == PIN_NUM(1, 4)) return WAKEUP_CRICUIT_4; // PB4
    /* WAKEUP_CRICUIT_5 is for RTC (WKO), assuming not a GPIO pin */
    /* Other pins use WAKEUP_CRICUIT_6 (falling) or WAKEUP_CRICUIT_7 (rising) */
    return -1; // Will be handled in attach_irq based on mode
}

static rt_uint32_t get_edge_select_bit(rt_uint8_t circuit)
{
    switch (circuit)
    {
        case WAKEUP_CRICUIT_0: return WAKEUP_EDGE_SELECT_0;
        case WAKEUP_CRICUIT_1: return WAKEUP_EDGE_SELECT_1;
        case WAKEUP_CRICUIT_2: return WAKEUP_EDGE_SELECT_2;
        case WAKEUP_CRICUIT_3: return WAKEUP_EDGE_SELECT_3;
        case WAKEUP_CRICUIT_4: return WAKEUP_EDGE_SELECT_4;
        case WAKEUP_CRICUIT_5: return WAKEUP_EDGE_SELECT_5;
        case WAKEUP_CRICUIT_6: return WAKEUP_EDGE_SELECT_6;
        case WAKEUP_CRICUIT_7: return WAKEUP_EDGE_SELECT_7;
        default: return 0;
    }
}

void __attribute__((section(".irq.gpio"))) ab32_pin_irq_handler(void *args)
{
    rt_interrupt_enter();
    rt_uint32_t pending = WKUPEDG;
    rt_uint8_t circuit = 0;

    for (circuit = 0; circuit <= WAKEUP_CRICUIT_7; circuit++)
    {
        if (pending & (BIT(circuit) << WAKEUP_INT_ENABLE))
        {
            /* clear pending interrupt */
            WKUPCPND = (BIT(circuit) << WAKEUP_INT_ENABLE);
            rt_mq_send(gpio_irq_mq, &circuit, sizeof(circuit));
        }
    }
    rt_interrupt_leave();
}

static void ab32_pin_irq_thread(void *parameter)
{
    rt_uint8_t circuit;
    while (1)
    {
        if (rt_mq_recv(gpio_irq_mq, &circuit, sizeof(circuit), RT_WAITING_FOREVER) == RT_EOK)
        {
            if (circuit <= WAKEUP_CRICUIT_7 && pin_irq_table[circuit].hdr)
            {
                pin_irq_table[circuit].hdr(pin_irq_table[circuit].args);
            }
        }
    }
}

static rt_err_t ab32_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                    rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    rt_uint8_t port, hw_pin;
    rt_int32_t circuit;
    uint8_t pin_mode;

    if (get_port_pin(pin, &port, &hw_pin) != RT_EOK)
    {
        return -RT_EINVAL;
    }

    circuit = get_wakeup_circuit(pin);
    if(circuit == -1)
    {
        circuit = (mode == PIN_IRQ_MODE_FALLING) ? WAKEUP_CRICUIT_6 : WAKEUP_CRICUIT_7;
    }

    /* store handler and arguments */
    pin_irq_table[circuit].hdr = hdr;
    pin_irq_table[circuit].args = args;

    /* The interrupt source in the port is: Port_intsrc = {PG[4:0], PF[5:0], PE[7:0], PB[4:0], PA[7:0]}. */
    /* Such as:the interrupt source number of PA0 is 0, interrupt source number of PG4 is 31. */
    PORTINTEN |= BIT(pin); // Enable interrupt
    PORTINTEDG |= BIT(pin); // Edge trigger

    return RT_EOK;
}

static rt_err_t ab32_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
    rt_uint8_t port, hw_pin;
    rt_int32_t circuit;

    if (get_port_pin(pin, &port, &hw_pin) != RT_EOK)
    {
        return -RT_EINVAL;
    }

    circuit = get_wakeup_circuit(pin);
    if (circuit < 0)
    {
        /* assume previously assigned to WAKEUP_CRICUIT_6 or _7 */
        /* check both circuits for handler */
        if (pin_irq_table[WAKEUP_CRICUIT_6].hdr)
            circuit = WAKEUP_CRICUIT_6;
        else if (pin_irq_table[WAKEUP_CRICUIT_7].hdr)
            circuit = WAKEUP_CRICUIT_7;
        else
            return RT_EOK;
    }

    PORTINTEN &= ~BIT(circuit);
    WKUPCON &= ~BIT(circuit);
    WKUPCPND = BIT(get_edge_select_bit(circuit));

    /* clear handler */
    pin_irq_table[circuit].hdr = RT_NULL;
    pin_irq_table[circuit].args = RT_NULL;

    return RT_EOK;
}

static rt_err_t ab32_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                    rt_uint32_t enabled)
{
    rt_uint8_t port, hw_pin;
    rt_int32_t circuit;

    if (get_port_pin(pin, &port, &hw_pin) != RT_EOK)
    {
        return -RT_EINVAL;
    }

    circuit = get_wakeup_circuit(pin);
    if (circuit < 0)
    {
        if (pin_irq_table[WAKEUP_CRICUIT_6].hdr)
        {
            circuit = WAKEUP_CRICUIT_6;
        }
        else if (pin_irq_table[WAKEUP_CRICUIT_7].hdr)
        {
            circuit = WAKEUP_CRICUIT_7;
        }
        else
            return -RT_EINVAL;
    }

    rt_uint32_t edge_bit = get_edge_select_bit(circuit);

    if (enabled == RT_TRUE)
    {
        WKUPEDG = BIT(circuit) | BIT(edge_bit);
        WKUPCON = BIT(circuit) | BIT(WAKEUP_INT_ENABLE);

        WKUPCPND = BIT(circuit);

        /* install interrupt handler */
        rt_hw_interrupt_install(IRQ_GPIO_IRQ, ab32_pin_irq_handler, RT_NULL, "gpio_isr");
        rt_hw_irq_enable(IRQ_GPIO_IRQ);
    }
    else
    {
        /* disable interrupt */
        WKUPCON &= ~BIT(circuit);
    }

    return RT_EOK;
}

static int ab32_pin_irq_init(void)
{
    gpio_irq_mq = rt_mq_create("gpio_irq", sizeof(rt_uint8_t), 128, RT_IPC_FLAG_FIFO);
    if (gpio_irq_mq == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    rt_thread_t tid = rt_thread_create("gpio_irq",
                                       ab32_pin_irq_thread,
                                       RT_NULL,
                                       512,
                                       15,
                                       5);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        rt_mq_delete(gpio_irq_mq);
        return -RT_ENOMEM;
    }

    return RT_EOK;
}
INIT_PREV_EXPORT(ab32_pin_irq_init);

const static struct rt_pin_ops _ab32_pin_ops =
{
    ab32_pin_mode,
    ab32_pin_write,
    ab32_pin_read,
    ab32_pin_attach_irq,
    ab32_pin_dettach_irq,
    ab32_pin_irq_enable,
    ab32_pin_get,
};

int rt_hw_pin_init(void)
{
    return rt_device_pin_register("pin", &_ab32_pin_ops, RT_NULL);
}

#endif
