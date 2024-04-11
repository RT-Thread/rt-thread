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
#include "fsl_inputmux.h"

#ifdef RT_USING_PIN


#define GET_GPIO_PORT(x)      ((x) / 32)
#define GET_GPIO_PIN(x)       ((x) % 32)

static struct rt_pin_ops mcx_pin_ops;

static GPIO_Type *GPIO_TYPE_TBL[] = {GPIO0, GPIO1, GPIO2, GPIO3};
static PORT_Type *PORT_TYPE_TBL[] = {PORT0, PORT1, PORT2, PORT3};
static IRQn_Type   IRQ_TYPE_TBL[] = {GPIO0_IRQn, GPIO1_IRQn, GPIO2_IRQn, GPIO3_IRQn};


#define PIN2GPIO(x)     GPIO_TYPE_TBL[GET_GPIO_PORT(x)]
#define PIN2PORT(x)     PORT_TYPE_TBL[GET_GPIO_PORT(x)]
#define PIN2IRQ(x)      IRQ_TYPE_TBL[GET_GPIO_PORT(x)]

struct rt_pin_irq_hdr pin_irq_hdr_tab[32*4] = {0};

static void mcx_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    port_pin_config_t port_pin_config = {0};
    gpio_pin_config_t gpio_pin_config = {0};

    port_pin_config.mux = kPORT_MuxAlt0;

    switch (mode)
    {
        case PIN_MODE_OUTPUT:
        {
            gpio_pin_config.pinDirection = kGPIO_DigitalOutput;
            port_pin_config.pullSelect = kPORT_PullDisable;
            port_pin_config.inputBuffer = kPORT_InputBufferEnable;
        }
        break;

        case PIN_MODE_INPUT:
        {
            gpio_pin_config.pinDirection = kGPIO_DigitalInput;
            port_pin_config.pullSelect = kPORT_PullDisable;
            port_pin_config.inputBuffer = kPORT_InputBufferEnable;
        }
        break;

        case PIN_MODE_INPUT_PULLDOWN:
        {
            gpio_pin_config.pinDirection = kGPIO_DigitalInput;
            port_pin_config.pullSelect = kPORT_PullDown;
            port_pin_config.pullValueSelect = kPORT_LowPullResistor;
            port_pin_config.inputBuffer = kPORT_InputBufferEnable;
        }
        break;

        case PIN_MODE_INPUT_PULLUP:
        {
            gpio_pin_config.pinDirection = kGPIO_DigitalInput;
            port_pin_config.pullSelect = kPORT_PullUp;
            port_pin_config.pullValueSelect = kPORT_LowPullResistor;
            port_pin_config.inputBuffer = kPORT_InputBufferEnable;
        }
        break;

        case PIN_MODE_OUTPUT_OD:
        {
            port_pin_config.openDrainEnable = kPORT_OpenDrainEnable;
            gpio_pin_config.pinDirection = kGPIO_DigitalOutput;
            port_pin_config.inputBuffer = kPORT_InputBufferEnable;
        }
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
    return GPIO_PinRead(PIN2GPIO(pin), GET_GPIO_PIN(pin));
}


rt_inline void pin_irq_handler(uint8_t gpio_idx)
{
    int i;

    rt_interrupt_enter();

    uint32_t INTFLAG = GPIO_GpioGetInterruptFlags(GPIO_TYPE_TBL[gpio_idx]);
    GPIO_GpioClearInterruptFlags(GPIO_TYPE_TBL[gpio_idx], INTFLAG);


    for(i=0; i<ARRAY_SIZE(pin_irq_hdr_tab); i++)
    {
        if((INTFLAG & (1<<GET_GPIO_PIN(pin_irq_hdr_tab[i].pin))) && pin_irq_hdr_tab[i].hdr && (GET_GPIO_PORT(pin_irq_hdr_tab[i].pin)) == gpio_idx)
        {
            pin_irq_hdr_tab[i].hdr(pin_irq_hdr_tab[i].args);
        }
    }

    rt_interrupt_leave();
}

void GPIO0_IRQHandler(void)
{
    pin_irq_handler(0);
}

void GPIO1_IRQHandler(void)
{
    pin_irq_handler(1);
}

void GPIO2_IRQHandler(void)
{
    pin_irq_handler(2);
}

void GPIO3_IRQHandler(void)
{
    pin_irq_handler(3);
}


static rt_err_t mcx_pin_attach_irq(struct rt_device *device, rt_base_t pin, rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    switch (mode)
    {
        case PIN_IRQ_MODE_RISING:
            GPIO_SetPinInterruptConfig(PIN2GPIO(pin), GET_GPIO_PIN(pin), kGPIO_InterruptRisingEdge);
            break;
        case PIN_IRQ_MODE_FALLING:
            GPIO_SetPinInterruptConfig(PIN2GPIO(pin), GET_GPIO_PIN(pin), kGPIO_InterruptFallingEdge);
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            GPIO_SetPinInterruptConfig(PIN2GPIO(pin), GET_GPIO_PIN(pin), kGPIO_InterruptEitherEdge);
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            GPIO_SetPinInterruptConfig(PIN2GPIO(pin), GET_GPIO_PIN(pin), kGPIO_InterruptLogicOne);
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            GPIO_SetPinInterruptConfig(PIN2GPIO(pin), GET_GPIO_PIN(pin), kGPIO_InterruptLogicZero);
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
    GPIO_SetPinInterruptConfig(PIN2GPIO(pin), GET_GPIO_PIN(pin), kGPIO_InterruptStatusFlagDisabled);
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
