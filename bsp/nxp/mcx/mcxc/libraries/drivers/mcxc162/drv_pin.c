/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "drv_pin.h"

#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_reset.h"

#ifdef RT_USING_PIN

#define PIN_PORT(pin)  ((rt_uint32_t)(pin) / 32U)
#define PIN_INDEX(pin) ((rt_uint32_t)(pin) % 32U)
#define PIN_COUNT      ((sizeof(gpio_bases) / sizeof(gpio_bases[0])) * 32U)

struct mcxc162_pin_irq
{
    rt_base_t pin;
    gpio_interrupt_config_t mode;
    void (*handler)(void *args);
    void *args;
    struct mcxc162_pin_irq *next;
};

static GPIO_Type * const gpio_bases[] = GPIO_BASE_PTRS;
static PORT_Type * const port_bases[] = PORT_BASE_PTRS;
static const IRQn_Type gpio_irqs[] = GPIO_IRQS;
static const clock_ip_name_t port_clocks[] = {
    kCLOCK_GatePORT0,
    kCLOCK_GatePORT1,
    kCLOCK_GatePORT2,
    kCLOCK_GatePORT3,
};
static const reset_ip_name_t port_resets[] = {
    kPORT0_RST_SHIFT_RSTn,
    kPORT1_RST_SHIFT_RSTn,
    kPORT2_RST_SHIFT_RSTn,
    kPORT3_RST_SHIFT_RSTn,
};
static struct mcxc162_pin_irq *pin_irqs;
static rt_uint32_t enabled_masks[4];

static rt_bool_t is_valid_pin(rt_base_t pin)
{
    return pin >= 0 && (rt_ubase_t)pin < PIN_COUNT;
}

static struct mcxc162_pin_irq *find_pin_irq(rt_base_t pin)
{
    struct mcxc162_pin_irq *irq = pin_irqs;

    while (irq != RT_NULL && irq->pin != pin)
    {
        irq = irq->next;
    }

    return irq;
}

static gpio_interrupt_config_t get_irq_mode(rt_uint8_t mode)
{
    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        return kGPIO_InterruptRisingEdge;
    case PIN_IRQ_MODE_FALLING:
        return kGPIO_InterruptFallingEdge;
    case PIN_IRQ_MODE_RISING_FALLING:
        return kGPIO_InterruptEitherEdge;
    case PIN_IRQ_MODE_HIGH_LEVEL:
        return kGPIO_InterruptLogicOne;
    case PIN_IRQ_MODE_LOW_LEVEL:
        return kGPIO_InterruptLogicZero;
    default:
        return kGPIO_InterruptStatusFlagDisabled;
    }
}

static void mcxc162_pin_mode(rt_device_t device, rt_base_t pin, rt_uint8_t mode)
{
    gpio_pin_config_t gpio_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U,
    };
    port_pin_config_t port_config = {
        .pullSelect = kPORT_PullDisable,
        .pullValueSelect = kPORT_LowPullResistor,
        .slewRate = kPORT_FastSlewRate,
        .passiveFilterEnable = kPORT_PassiveFilterDisable,
        .openDrainEnable = kPORT_OpenDrainDisable,
        .driveStrength = kPORT_LowDriveStrength,
        .driveStrength1 = kPORT_NormalDriveStrength,
        .mux = kPORT_MuxAsGpio,
        .inputBuffer = kPORT_InputBufferEnable,
        .invertInput = kPORT_InputNormal,
        .lockRegister = kPORT_UnlockRegister,
    };

    (void)device;

    if (!is_valid_pin(pin))
    {
        return;
    }

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        gpio_config.pinDirection = kGPIO_DigitalOutput;
        gpio_config.outputLogic =
            (gpio_bases[PIN_PORT(pin)]->PDOR >> PIN_INDEX(pin)) & 1U;
        break;
    case PIN_MODE_INPUT_PULLUP:
        gpio_config.pinDirection = kGPIO_DigitalInput;
        port_config.pullSelect = kPORT_PullUp;
        break;
    case PIN_MODE_INPUT_PULLDOWN:
        gpio_config.pinDirection = kGPIO_DigitalInput;
        port_config.pullSelect = kPORT_PullDown;
        break;
    case PIN_MODE_OUTPUT_OD:
        gpio_config.pinDirection = kGPIO_DigitalOutput;
        gpio_config.outputLogic = 1U;
        port_config.openDrainEnable = kPORT_OpenDrainEnable;
        break;
    default:
        gpio_config.pinDirection = kGPIO_DigitalInput;
        break;
    }

    PORT_SetPinConfig(port_bases[PIN_PORT(pin)], PIN_INDEX(pin), &port_config);
    GPIO_PinInit(gpio_bases[PIN_PORT(pin)], PIN_INDEX(pin), &gpio_config);
}

static void mcxc162_pin_write(rt_device_t device, rt_base_t pin, rt_uint8_t value)
{
    (void)device;

    if (!is_valid_pin(pin))
    {
        return;
    }

    GPIO_PinWrite(gpio_bases[PIN_PORT(pin)], PIN_INDEX(pin), value);
}

static rt_ssize_t mcxc162_pin_read(rt_device_t device, rt_base_t pin)
{
    (void)device;

    if (!is_valid_pin(pin))
    {
        return -RT_EINVAL;
    }

    return GPIO_PinRead(gpio_bases[PIN_PORT(pin)], PIN_INDEX(pin));
}

static rt_err_t mcxc162_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                       rt_uint8_t mode, void (*handler)(void *args), void *args)
{
    struct mcxc162_pin_irq *irq;
    gpio_interrupt_config_t irq_mode = get_irq_mode(mode);
    rt_base_t level;

    (void)device;

    if (!is_valid_pin(pin) || handler == RT_NULL ||
        irq_mode == kGPIO_InterruptStatusFlagDisabled)
    {
        return -RT_EINVAL;
    }

    irq = find_pin_irq(pin);
    if (irq != RT_NULL)
    {
        return irq->mode == irq_mode && irq->handler == handler && irq->args == args ? RT_EOK : -RT_EBUSY;
    }

    GPIO_SetPinInterruptConfig(gpio_bases[PIN_PORT(pin)], PIN_INDEX(pin),
                               kGPIO_InterruptStatusFlagDisabled);
    irq = rt_malloc(sizeof(*irq));
    if (irq == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    irq->pin = pin;
    irq->mode = irq_mode;
    irq->handler = handler;
    irq->args = args;
    level = rt_hw_interrupt_disable();
    irq->next = pin_irqs;
    pin_irqs = irq;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t mcxc162_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    struct mcxc162_pin_irq **link = &pin_irqs;
    struct mcxc162_pin_irq *irq;
    rt_uint32_t port;
    rt_uint32_t mask;
    rt_base_t level;

    (void)device;

    if (!is_valid_pin(pin))
    {
        return -RT_EINVAL;
    }

    port = PIN_PORT(pin);
    mask = 1UL << PIN_INDEX(pin);

    GPIO_SetPinInterruptConfig(gpio_bases[port], PIN_INDEX(pin),
                               kGPIO_InterruptStatusFlagDisabled);
    enabled_masks[port] &= ~mask;
    if (enabled_masks[port] == 0U)
    {
        DisableIRQ(gpio_irqs[port]);
    }

    level = rt_hw_interrupt_disable();
    while (*link != RT_NULL && (*link)->pin != pin)
    {
        link = &(*link)->next;
    }

    irq = *link;
    if (irq != RT_NULL)
    {
        *link = irq->next;
    }
    rt_hw_interrupt_enable(level);

    if (irq != RT_NULL)
    {
        rt_free(irq);
    }

    return RT_EOK;
}

static rt_err_t mcxc162_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                       rt_uint8_t enabled)
{
    struct mcxc162_pin_irq *irq;
    rt_uint32_t port;
    rt_uint32_t mask;
    rt_base_t level;

    (void)device;

    if (!is_valid_pin(pin))
    {
        return -RT_EINVAL;
    }

    irq = find_pin_irq(pin);
    if (irq == RT_NULL)
    {
        return -RT_EINVAL;
    }

    port = PIN_PORT(pin);
    mask = 1UL << PIN_INDEX(pin);

    level = rt_hw_interrupt_disable();
    if (enabled == PIN_IRQ_ENABLE)
    {
        GPIO_GpioClearInterruptFlags(gpio_bases[port], mask);
        GPIO_SetPinInterruptConfig(gpio_bases[port], PIN_INDEX(pin), irq->mode);
        enabled_masks[port] |= mask;
        EnableIRQ(gpio_irqs[port]);
    }
    else
    {
        GPIO_SetPinInterruptConfig(gpio_bases[port], PIN_INDEX(pin),
                                   kGPIO_InterruptStatusFlagDisabled);
        enabled_masks[port] &= ~mask;
        if (enabled_masks[port] == 0U)
        {
            DisableIRQ(gpio_irqs[port]);
        }
    }
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static void mcxc162_gpio_irq_handler(rt_uint32_t port)
{
    struct mcxc162_pin_irq *irq;
    rt_uint32_t flags;

    rt_interrupt_enter();

    flags = GPIO_GpioGetInterruptFlags(gpio_bases[port]);
    GPIO_GpioClearInterruptFlags(gpio_bases[port], flags);
    flags &= enabled_masks[port];

    for (irq = pin_irqs; irq != RT_NULL; irq = irq->next)
    {
        if (PIN_PORT(irq->pin) == port &&
            (flags & (1UL << PIN_INDEX(irq->pin))) != 0U)
        {
            irq->handler(irq->args);
        }
    }

    rt_interrupt_leave();
}

void GPIO0_IRQHandler(void)
{
    mcxc162_gpio_irq_handler(0U);
}

void GPIO1_IRQHandler(void)
{
    mcxc162_gpio_irq_handler(1U);
}

void GPIO2_IRQHandler(void)
{
    mcxc162_gpio_irq_handler(2U);
}

void GPIO3_IRQHandler(void)
{
    mcxc162_gpio_irq_handler(3U);
}

static const struct rt_pin_ops mcxc162_pin_ops = {
    .pin_mode = mcxc162_pin_mode,
    .pin_write = mcxc162_pin_write,
    .pin_read = mcxc162_pin_read,
    .pin_attach_irq = mcxc162_pin_attach_irq,
    .pin_detach_irq = mcxc162_pin_detach_irq,
    .pin_irq_enable = mcxc162_pin_irq_enable,
};

int rt_hw_pin_init(void)
{
    rt_uint32_t port;

    for (port = 0U; port < 4U; port++)
    {
        CLOCK_EnableClock(port_clocks[port]);
        RESET_ReleasePeripheralReset(port_resets[port]);
        GPIO_PortInit(gpio_bases[port]);
    }

    return rt_device_pin_register("pin", &mcxc162_pin_ops, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* RT_USING_PIN */
