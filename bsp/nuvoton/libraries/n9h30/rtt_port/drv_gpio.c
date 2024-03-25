/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-12-12      Wayne            First version
*
******************************************************************************/

#include <rtconfig.h>

#if (defined(BSP_USING_GPIO) && defined(RT_USING_PIN))

#include <rtdevice.h>
#include <rthw.h>
#include "NuMicro.h"
#include <nu_bitutil.h>
#include <drv_gpio.h>
#include <stdlib.h>
#include <drv_sys.h>

#define LOG_TAG                 "drv.gpio"
#define DBG_ENABLE
#define DBG_SECTION_NAME        LOG_TAG
#define DBG_LEVEL               DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

/* Private define ---------------------------------------------------------------*/

#define PORT_OFFSET         0x40
#define IRQ_MAX_NUM         16            //Max support 32
#define GPIO_PIN_MAX        16

/* Private functions ------------------------------------------------------------*/

static void nu_gpio_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode);
static void nu_gpio_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value);
static rt_ssize_t nu_gpio_read(struct rt_device *device, rt_base_t pin);
static rt_err_t nu_gpio_attach_irq(struct rt_device *device, rt_int32_t pin, rt_uint8_t mode, void (*hdr)(void *args), void *args);
static rt_err_t nu_gpio_detach_irq(struct rt_device *device, rt_int32_t pin);
static rt_err_t nu_gpio_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled);
static rt_base_t nu_gpio_pin_get(const char *name);

/* Private variables ------------------------------------------------------------*/
static struct rt_pin_irq_hdr pin_irq_hdr_tab[IRQ_MAX_NUM];
static struct rt_pin_ops nu_gpio_ops =
{
    nu_gpio_mode,
    nu_gpio_write,
    nu_gpio_read,
    nu_gpio_attach_irq,
    nu_gpio_detach_irq,
    nu_gpio_irq_enable,
    nu_gpio_pin_get,
};

static rt_uint32_t g_u32PinIrqMask = 0x0;

static uint32_t au32PinMaskTbl[] = {GPIOA_MASK, GPIOB_MASK, GPIOC_MASK, GPIOD_MASK, GPIOE_MASK, GPIOF_MASK, GPIOG_MASK, GPIOH_MASK, GPIOI_MASK, GPIOJ_MASK};

/* Functions define ------------------------------------------------------------*/

static rt_err_t nu_port_check(rt_int32_t pin)
{
    if (NU_GET_PORT(pin) >= NU_PORT_CNT)
    {
        LOG_E("Over port group. %04x", pin);
        return -(RT_ERROR);
    }

    if (!(au32PinMaskTbl[NU_GET_PORT(pin)] & NU_GET_PIN_MASK(NU_GET_PINS(pin))))
    {
        LOG_E("Over port-pin group. %04x", pin);
        return -(RT_ERROR);
    }

    return RT_EOK;
}

static rt_int32_t nu_find_irqindex(rt_uint32_t pin_index)
{
    rt_int32_t irqindex;
    rt_int32_t u32PinIrqStatus = g_u32PinIrqMask;

    // Find index of pin is attached in pool.
    while ((irqindex = nu_ctz(u32PinIrqStatus)) < IRQ_MAX_NUM) // Count Trailing Zeros ==> Find First One
    {
        if (pin_irq_hdr_tab[irqindex].pin == pin_index)
            return irqindex;

        u32PinIrqStatus &= ~(1 << irqindex);
    }

    return -(RT_ERROR);
}

static void pin_irq_hdr(rt_uint32_t irq_status, rt_uint32_t port_index)
{
    rt_int32_t irqindex, i;
    rt_int32_t pinindex = port_index * GPIO_PIN_MAX ;

    while ((i = nu_ctz(irq_status)) < GPIO_PIN_MAX)// Count Trailing Zeros ==> Find First One
    {
        int pin_mask = (1 << i);
        irqindex = nu_find_irqindex(pinindex + i);
        if (irqindex != -(RT_ERROR))
        {
            if (pin_irq_hdr_tab[irqindex].hdr)
            {
                pin_irq_hdr_tab[irqindex].hdr(pin_irq_hdr_tab[irqindex].args);
            }
        }
        // Clear the served bit.
        irq_status &= ~pin_mask;
    }
}

static rt_base_t nu_gpio_pin_get(const char *name)
{
    /* Get pin number by name,such as PA.0, PF12 */
    if ((name[2] == '\0') || ((name[2] == '.') && (name[3] == '\0')))
        return -(RT_EINVAL);

    long number;

    if ((name[2] == '.'))
        number = atol(&name[3]);
    else
        number = atol(&name[2]);

    if (number > 15)
        return -(RT_EINVAL);

    if (name[1] >= 'A' && name[1] <= 'J')
        return ((name[1] - 'A') * 0x10) + number;

    if (name[1] >= 'a' && name[1] <= 'i')
        return ((name[1] - 'a') * 0x10) + number;

    return -(RT_EINVAL);
}

static void nu_gpio_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    GPIO_PORT PORT;

    if (nu_port_check(pin))
        return;

    PORT = (GPIO_PORT)(GPIOA + (NU_GET_PORT(pin) * PORT_OFFSET));

    switch (mode)
    {
    case PIN_MODE_INPUT_PULLUP:
        GPIO_OpenBit(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), DIR_INPUT, PULL_UP);
        break;

    case PIN_MODE_INPUT_PULLDOWN:
        GPIO_OpenBit(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), DIR_INPUT, PULL_DOWN);
        break;

    case PIN_MODE_OUTPUT:
        GPIO_OpenBit(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), DIR_OUTPUT, NO_PULL_UP);
        break;

    case PIN_MODE_INPUT:
        GPIO_OpenBit(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), DIR_INPUT, NO_PULL_UP);
        break;

    case PIN_MODE_OUTPUT_OD:
    default:
        LOG_E("Open-drian is not supportted.");
        break;
    }
}

static void nu_gpio_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    GPIO_PORT PORT;

    if (nu_port_check(pin))
        return;

    PORT = (GPIO_PORT)(GPIOA + (NU_GET_PORT(pin) * PORT_OFFSET));

    if (value)
        GPIO_SetBit(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)));
    else
        GPIO_ClrBit(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)));
}

static rt_ssize_t nu_gpio_read(struct rt_device *device, rt_base_t pin)
{
    GPIO_PORT PORT;

    if (nu_port_check(pin))
    {
        return -RT_EINVAL;
    }

    PORT = (GPIO_PORT)(GPIOA + (NU_GET_PORT(pin) * PORT_OFFSET));

    return GPIO_ReadBit(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)));
}

static rt_err_t nu_gpio_attach_irq(struct rt_device *device, rt_int32_t pin, rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex;

    if (nu_port_check(pin))
        return -(RT_ERROR);

    level = rt_hw_interrupt_disable();

    /* Find index of pin is attached in pool. */
    if ((irqindex = nu_find_irqindex(pin)) >= 0)
        goto exit_nu_gpio_attach_irq;

    /* Find available index of pin in pool. */
    if ((irqindex = nu_cto(g_u32PinIrqMask)) < IRQ_MAX_NUM)  // Count Trailing Ones ==> Find First Zero
        goto exit_nu_gpio_attach_irq;

    rt_hw_interrupt_enable(level);

    return -(RT_EBUSY);

exit_nu_gpio_attach_irq:

    pin_irq_hdr_tab[irqindex].pin = pin;
    pin_irq_hdr_tab[irqindex].hdr = hdr;
    pin_irq_hdr_tab[irqindex].mode = mode;
    pin_irq_hdr_tab[irqindex].args = args;

    g_u32PinIrqMask |= (1 << irqindex);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t nu_gpio_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    rt_base_t level;
    rt_int32_t irqindex;
    rt_int32_t u32PinIrqStatus;

    if (nu_port_check(pin))
        return -(RT_ERROR);

    level = rt_hw_interrupt_disable();

    u32PinIrqStatus = g_u32PinIrqMask;

    // Find index of pin is attached in pool.
    while ((irqindex = nu_ctz(u32PinIrqStatus)) < IRQ_MAX_NUM)// Count Trailing Zeros ==> Find First One
    {
        if (pin_irq_hdr_tab[irqindex].pin == pin)
        {
            pin_irq_hdr_tab[irqindex].pin = PIN_IRQ_PIN_NONE;
            pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
            pin_irq_hdr_tab[irqindex].mode = PIN_IRQ_MODE_RISING;
            pin_irq_hdr_tab[irqindex].args = RT_NULL;
            g_u32PinIrqMask &= ~(1 << irqindex);
            break;
        }
        u32PinIrqStatus &= ~(1 << irqindex);
    }

    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

static void nu_gpio_isr(int vector, void *param)
{
    int i;
    rt_uint32_t u32IntStatus_Port;

    u32IntStatus_Port = inpw(REG_GPIO_ISR) | ~((1 << MAX_PORT) - 1);
    while ((i = nu_ctz(u32IntStatus_Port)) < MAX_PORT)// Count Trailing Zeros ==> Find First One
    {
        int port_mask = (1 << i);
        rt_uint32_t u32IntStatus_Pins = inpw(REG_GPIOA_ISR + PORT_OFFSET * i);

        /* Invoke pins status and port number */
        pin_irq_hdr(u32IntStatus_Pins, i);

        /* Clear Interrupt flag. */
        outpw(REG_GPIOA_ISR + PORT_OFFSET * i, u32IntStatus_Pins);

        /* Clear the served bit. */
        u32IntStatus_Port &= ~port_mask;
    }

    /* Clear interrupt */
    outpw(REG_AIC_SCCRH, IRQ_GPIO - 1);
}

static rt_err_t nu_gpio_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    GPIO_PORT PORT;
    GPIO_TRIGGER_TYPE triggerType;

    rt_base_t level;
    rt_int32_t irqindex;
    rt_err_t ret = RT_EOK;

    if (nu_port_check(pin))
        return -(RT_ERROR);

    level = rt_hw_interrupt_disable();

    irqindex = nu_find_irqindex(pin);
    if (irqindex == -(RT_ERROR))
    {
        ret = -RT_ERROR;
        goto exit_nu_gpio_irq_enable;
    }

    PORT = (GPIO_PORT)(GPIOA + (NU_GET_PORT(pin) * PORT_OFFSET));

    if (enabled == PIN_IRQ_ENABLE)
    {
        switch (pin_irq_hdr_tab[irqindex].mode)
        {
        case PIN_IRQ_MODE_RISING:
            triggerType = RISING;
            break;

        case PIN_IRQ_MODE_FALLING:
            triggerType = FALLING;
            break;

        case PIN_IRQ_MODE_RISING_FALLING:
            triggerType = BOTH_EDGE;
            break;

        case PIN_IRQ_MODE_HIGH_LEVEL:
            triggerType = HIGH;
            break;

        case PIN_IRQ_MODE_LOW_LEVEL:
            triggerType = LOW;
            break;

        default:
            goto exit_nu_gpio_irq_enable;
        }
        GPIO_EnableTriggerType(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), triggerType);
    }
    else
    {
        GPIO_DisableTriggerType(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)));
    }

exit_nu_gpio_irq_enable:

    rt_hw_interrupt_enable(level);
    return -(ret);
}

int rt_hw_gpio_init(void)
{
    char szTmp[16];
    rt_int32_t irqindex;

    for (irqindex = 0; irqindex < IRQ_MAX_NUM ; irqindex++)
    {
        pin_irq_hdr_tab[irqindex].pin = PIN_IRQ_PIN_NONE;
        pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
        pin_irq_hdr_tab[irqindex].mode = PIN_IRQ_MODE_RISING;
        pin_irq_hdr_tab[irqindex].args = RT_NULL;
    }

    nu_sys_ipclk_enable(GPIOCKEN);

    snprintf(szTmp, sizeof(szTmp), "gpio");
    rt_hw_interrupt_install(IRQ_GPIO, nu_gpio_isr, RT_NULL, szTmp);
    rt_hw_interrupt_set_type(IRQ_GPIO, HIGH_LEVEL_SENSITIVE);
    rt_hw_interrupt_umask(IRQ_GPIO);

    return rt_device_pin_register("gpio", &nu_gpio_ops, RT_NULL);
}

INIT_BOARD_EXPORT(rt_hw_gpio_init);

#endif //#if (defined(BSP_USING_GPIO) && defined(RT_USING_PIN))
