/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-24     YangXi       the first version.
 */

#include "drv_pin.h"

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

#ifdef RT_USING_PIN

#define DBG_TAG    "drv.pin"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#define GET_GPIO_PORT(x)      ((x) / 32)
#define GET_GPIO_PIN(x)       ((x) % 32)

static struct rt_pin_ops mcx_pin_ops;

static GPIO_Type *GPIO_TYPE_TBL[] = GPIO_BASE_PTRS;
static PORT_Type *PORT_TYPE_TBL[] = PORT_BASE_PTRS;
static IRQn_Type   IRQ_TYPE_TBL[] = PORT_IRQS;


#define PIN2GPIO(x)     GPIO_TYPE_TBL[GET_GPIO_PORT(x)]
#define PIN2PORT(x)     PORT_TYPE_TBL[GET_GPIO_PORT(x)]
#define PIN2IRQ(x)      IRQ_TYPE_TBL[GET_GPIO_PORT(x)]

struct rt_pin_irq_hdr pin_irq_hdr_tab[32*5] = {0};

static void mcx_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    port_pin_config_t port_pin_config = {0};
    gpio_pin_config_t gpio_pin_config = {0};

    port_pin_config.mux = kPORT_MuxAsGpio;

    switch (mode)
    {
        case PIN_MODE_OUTPUT:
        case PIN_MODE_OUTPUT_OD: /* MCX E2 does not support OD. */
        {
            gpio_pin_config.pinDirection = kGPIO_DigitalOutput;
            port_pin_config.pullSelect = kPORT_PullDisable;
        }
        break;

        case PIN_MODE_INPUT:
        {
            gpio_pin_config.pinDirection = kGPIO_DigitalInput;
            port_pin_config.pullSelect = kPORT_PullDisable;
        }
        break;

        case PIN_MODE_INPUT_PULLDOWN:
        {
            gpio_pin_config.pinDirection = kGPIO_DigitalInput;
            port_pin_config.pullSelect = kPORT_PullDown;
        }
        break;

        case PIN_MODE_INPUT_PULLUP:
        {
            gpio_pin_config.pinDirection = kGPIO_DigitalInput;
            port_pin_config.pullSelect = kPORT_PullUp;
        }
        break;

        default:
        break;
    }

    PORT_SetPinConfig(PIN2PORT(pin), GET_GPIO_PIN(pin), &port_pin_config);
    GPIO_PinInit(PIN2GPIO(pin), GET_GPIO_PIN(pin) , &gpio_pin_config);
}


static void mcx_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    GPIO_PinWrite(PIN2GPIO(pin), GET_GPIO_PIN(pin), value);
}

static rt_ssize_t mcx_pin_read(rt_device_t dev, rt_base_t pin)
{
    return GPIO_PinRead(PIN2GPIO(pin), GET_GPIO_PIN(pin)) ? 1 : 0;
}


rt_inline void pin_irq_handler(uint8_t gpio_idx)
{
    int i;

    rt_interrupt_enter();

    uint32_t INTFLAG = PORT_GetPinsInterruptFlags(PORT_TYPE_TBL[gpio_idx]);
    PORT_ClearPinsInterruptFlags(PORT_TYPE_TBL[gpio_idx], INTFLAG);


    for(i=0; i<ARRAY_SIZE(pin_irq_hdr_tab); i++)
    {
        if((INTFLAG & (1<<GET_GPIO_PIN(pin_irq_hdr_tab[i].pin))) && pin_irq_hdr_tab[i].hdr && (GET_GPIO_PORT(pin_irq_hdr_tab[i].pin)) == gpio_idx)
        {
            pin_irq_hdr_tab[i].hdr(pin_irq_hdr_tab[i].args);
        }
    }

    rt_interrupt_leave();
}

void PORTA_IRQHandler(void)
{
    pin_irq_handler(0);
}

void PORTB_IRQHandler(void)
{
    pin_irq_handler(1);
}

void PORTC_IRQHandler(void)
{
    pin_irq_handler(2);
}

void PORTD_IRQHandler(void)
{
    pin_irq_handler(3);
}

void PORTE_IRQHandler(void)
{
    pin_irq_handler(4);
}


static rt_err_t mcx_pin_attach_irq(struct rt_device *device, rt_base_t pin, rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    switch (mode)
    {
        case PIN_IRQ_MODE_RISING:
            PORT_SetPinInterruptConfig(PIN2PORT(pin), GET_GPIO_PIN(pin), kPORT_InterruptRisingEdge);
            break;
        case PIN_IRQ_MODE_FALLING:
            PORT_SetPinInterruptConfig(PIN2PORT(pin), GET_GPIO_PIN(pin), kPORT_InterruptFallingEdge);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            PORT_SetPinInterruptConfig(PIN2PORT(pin), GET_GPIO_PIN(pin), kPORT_InterruptEitherEdge);
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            PORT_SetPinInterruptConfig(PIN2PORT(pin), GET_GPIO_PIN(pin), kPORT_InterruptLogicOne);
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            PORT_SetPinInterruptConfig(PIN2PORT(pin), GET_GPIO_PIN(pin), kPORT_InterruptLogicZero);
            break;
    }

    pin_irq_hdr_tab[pin].pin = pin;
    pin_irq_hdr_tab[pin].mode = mode;
    pin_irq_hdr_tab[pin].hdr = hdr;
    pin_irq_hdr_tab[pin].args = args;

    return RT_EOK;
}

static rt_err_t mcx_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    PORT_SetPinInterruptConfig(PIN2PORT(pin), GET_GPIO_PIN(pin), kPORT_InterruptOrDMADisabled);
    return RT_EOK;
}

static rt_err_t mcx_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    if(enabled)
    {
        EnableIRQ(PIN2IRQ(pin));
    }
    else
    {
        DisableIRQ(PIN2IRQ(pin));
    }

    return RT_EOK;
}

int rt_hw_pin_init(void)
{
    int ret = RT_EOK;

    mcx_pin_ops.pin_mode        = mcx_pin_mode;
    mcx_pin_ops.pin_read        = mcx_pin_read;
    mcx_pin_ops.pin_write       = mcx_pin_write;
    mcx_pin_ops.pin_attach_irq  = mcx_pin_attach_irq;
    mcx_pin_ops.pin_detach_irq  = mcx_pin_detach_irq;
    mcx_pin_ops.pin_irq_enable  = mcx_pin_irq_enable;
    mcx_pin_ops.pin_get         = RT_NULL,

    ret = rt_device_pin_register("pin", &mcx_pin_ops, RT_NULL);

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /*RT_USING_PIN */

// end file
