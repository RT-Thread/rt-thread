/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-25     RT-Thread    the first version for MCXC444.
 */

#include "drv_pin.h"

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_port.h"

#ifdef RT_USING_PIN

#define GET_GPIO_PORT(x)      ((x) / 32)
#define GET_GPIO_PIN(x)       ((x) % 32)

static struct rt_pin_ops mcx_pin_ops;

static GPIO_Type *GPIO_TYPE_TBL[] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE};
static PORT_Type *PORT_TYPE_TBL[] = {PORTA, PORTB, PORTC, PORTD, PORTE};
static void (*pin_irq_hdr_tab[32 * 5])(void *args) = {0};
static void *pin_irq_arg_tab[32 * 5] = {0};

#define PIN2GPIO(x)     GPIO_TYPE_TBL[GET_GPIO_PORT(x)]
#define PIN2PORT(x)     PORT_TYPE_TBL[GET_GPIO_PORT(x)]

static void mcx_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    gpio_pin_config_t gpio_config = {0};
    PORT_SetPinMux(PIN2PORT(pin), GET_GPIO_PIN(pin), kPORT_MuxAsGpio);

    switch (mode)
    {
        case PIN_MODE_OUTPUT:
            gpio_config.pinDirection = kGPIO_DigitalOutput;
            gpio_config.outputLogic = 0;
            break;
        case PIN_MODE_INPUT:
            gpio_config.pinDirection = kGPIO_DigitalInput;
            //PORT_SetPinPullSelect(PIN2PORT(pin), GET_GPIO_PIN(pin), kPORT_PullDisable);
            break;
        case PIN_MODE_INPUT_PULLUP:
            gpio_config.pinDirection = kGPIO_DigitalInput;
            //PORT_SetPinPullSelect(PIN2PORT(pin), GET_GPIO_PIN(pin), kPORT_PullUp);
            break;
        case PIN_MODE_INPUT_PULLDOWN:
            gpio_config.pinDirection = kGPIO_DigitalInput;
            //PORT_SetPinPullSelect(PIN2PORT(pin), GET_GPIO_PIN(pin), kPORT_PullDown);
            break;
        case PIN_MODE_OUTPUT_OD:
            gpio_config.pinDirection = kGPIO_DigitalOutput;
            gpio_config.outputLogic = 1;
            //PORT_SetPinOpenDrainEnable(PIN2PORT(pin), GET_GPIO_PIN(pin), true);
            break;
    }

    GPIO_PinInit(PIN2GPIO(pin), GET_GPIO_PIN(pin), &gpio_config);
}

static void mcx_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    GPIO_PinWrite(PIN2GPIO(pin), GET_GPIO_PIN(pin), value);
}

static rt_ssize_t mcx_pin_read(rt_device_t dev, rt_base_t pin)
{
    return GPIO_PinRead(PIN2GPIO(pin), GET_GPIO_PIN(pin));
}

static rt_err_t mcx_pin_attach_irq(struct rt_device *device, rt_base_t pin, rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    PORT_Type *port = PIN2PORT(pin);
    uint32_t pin_index = GET_GPIO_PIN(pin);
    uint32_t port_index = GET_GPIO_PORT(pin);
    port_interrupt_t port_int = kPORT_InterruptOrDMADisabled;

    switch (mode)
    {
        case PIN_IRQ_MODE_RISING:
            port_int = kPORT_InterruptRisingEdge;
            break;
        case PIN_IRQ_MODE_FALLING:
            port_int = kPORT_InterruptFallingEdge;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            port_int = kPORT_InterruptEitherEdge;
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            port_int = kPORT_InterruptLogicOne;
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            port_int = kPORT_InterruptLogicZero;
            break;
        default:
            return RT_EINVAL;
    }

    PORT_SetPinInterruptConfig(port, pin_index, kPORT_InterruptOrDMADisabled);

    pin_irq_hdr_tab[port_index * 32 + pin_index] = hdr;
    pin_irq_arg_tab[port_index * 32 + pin_index] = args;

    PORT_SetPinInterruptConfig(port, pin_index, port_int);

    return RT_EOK;
}


static rt_err_t mcx_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    PORT_Type *port = PIN2PORT(pin);
    uint32_t pin_index = GET_GPIO_PIN(pin);

    PORT_SetPinInterruptConfig(port, pin_index, kPORT_InterruptOrDMADisabled);

    return RT_EOK;
}

static rt_err_t mcx_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    PORT_Type *port = PIN2PORT(pin);
    uint32_t pin_index = GET_GPIO_PIN(pin);
    IRQn_Type irqn;

    switch ((uint32_t)port)
    {
        case PORTA_BASE:
            irqn = PORTA_IRQn;
            break;
        case PORTB_BASE:
            irqn = NotAvail_IRQn;
            break;
        case PORTC_BASE:
            irqn = PORTC_PORTD_IRQn;
            break;
        case PORTD_BASE:
            irqn = PORTC_PORTD_IRQn;
            break;
        case PORTE_BASE:
            irqn = NotAvail_IRQn;
            break;
        default:
            return RT_ERROR;
    }

    if (enabled)
    {
        PORT_SetPinInterruptConfig(port, pin_index, kPORT_InterruptRisingEdge);

        PORT_ClearPinsInterruptFlags(port, (1U << pin_index));

        NVIC_EnableIRQ(irqn);
    }
    else
    {
        PORT_SetPinInterruptConfig(port, pin_index, kPORT_InterruptOrDMADisabled);

        NVIC_DisableIRQ(irqn);
    }

    return RT_EOK;
}


static void mcx_gpio_irq_handler(PORT_Type *port)
{
    uint32_t pin_index;
    uint32_t port_index = ((uint32_t)port - PORTA_BASE) / (PORTB_BASE - PORTA_BASE);


    for (pin_index = 0; pin_index < 32; pin_index++)
    {
        if (PORT_GetPinsInterruptFlags(port) & (1U << pin_index))
        {
            PORT_ClearPinsInterruptFlags(port, 1U << pin_index);
            if (pin_irq_hdr_tab[port_index * 32 + pin_index])
            {
                pin_irq_hdr_tab[port_index * 32 + pin_index](pin_irq_arg_tab[port_index * 32 + pin_index]);
            }
        }
    }
}

void PORTA_IRQHandler(void)
{
    rt_interrupt_enter();
    mcx_gpio_irq_handler(PORTA);
    rt_interrupt_leave();
}


void PORTC_PORTD_IRQHandler(void)
{
    rt_interrupt_enter();
    mcx_gpio_irq_handler(PORTC);
    rt_interrupt_leave();
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
    mcx_pin_ops.pin_get         = RT_NULL;

    ret = rt_device_pin_register("pin", &mcx_pin_ops, RT_NULL);

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* RT_USING_PIN */
