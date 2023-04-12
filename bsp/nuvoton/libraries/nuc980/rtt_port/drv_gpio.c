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

/* Private define ---------------------------------------------------------------*/

#define PORT_OFFSET         0x40
#define IRQ_MAX_NUM         16            //Max support 32

/* Private functions ------------------------------------------------------------*/

static void nu_gpio_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode);
static void nu_gpio_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value);
static rt_int8_t nu_gpio_read(struct rt_device *device, rt_base_t pin);
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

static IRQn_Type au32GPIRQ[NU_PORT_CNT] = {IRQ_GPA, IRQ_GPB, IRQ_GPC, IRQ_GPD, IRQ_GPE, IRQ_GPF, IRQ_GPG};

static rt_uint32_t g_u32PinIrqMask = 0x0;

/* Functions define ------------------------------------------------------------*/

static rt_err_t nu_port_check(rt_int32_t pin)
{
    if (NU_GET_PORT(pin) >= NU_PORT_CNT)
        return -(RT_ERROR);

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

    if (name[1] >= 'A' && name[1] <= 'H')
        return ((name[1] - 'A') * 0x10) + number;

    if (name[1] >= 'a' && name[1] <= 'h')
        return ((name[1] - 'a') * 0x10) + number;

    return -(RT_EINVAL);
}

static void nu_gpio_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    GPIO_T *PORT;

    if (nu_port_check(pin))
        return;

    PORT = (GPIO_T *)(PA_BA + (NU_GET_PORT(pin) * PORT_OFFSET));

    if (mode == PIN_MODE_INPUT_PULLUP)
    {
        GPIO_SetMode(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), GPIO_MODE_INPUT);
        GPIO_SetPullCtl(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), GPIO_PUSEL_PULL_UP);
    }
    else if (mode == PIN_MODE_INPUT_PULLDOWN)
    {
        GPIO_SetMode(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), GPIO_MODE_INPUT);
        GPIO_SetPullCtl(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), GPIO_PUSEL_PULL_DOWN);
    }
    else if (mode == PIN_MODE_OUTPUT)
    {
        GPIO_SetMode(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), GPIO_MODE_OUTPUT);
    }
    else if (mode == PIN_MODE_INPUT)
    {
        GPIO_SetMode(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), GPIO_MODE_INPUT);
        GPIO_SetPullCtl(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), GPIO_PUSEL_DISABLE);
    }
    else if (mode == PIN_MODE_OUTPUT_OD)
    {
        GPIO_SetMode(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), GPIO_MODE_OPEN_DRAIN);
        GPIO_SetPullCtl(PORT, NU_GET_PIN_MASK(NU_GET_PINS(pin)), GPIO_PUSEL_DISABLE);
    }
}

static void nu_gpio_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    if (nu_port_check(pin))
        return;

    GPIO_PIN_DATA(NU_GET_PORT(pin), NU_GET_PINS(pin)) = value;
}

static rt_int8_t nu_gpio_read(struct rt_device *device, rt_base_t pin)
{
    if (nu_port_check(pin))
        return PIN_LOW;

    return GPIO_PIN_DATA(NU_GET_PORT(pin), NU_GET_PINS(pin));
}

static rt_err_t nu_gpio_attach_irq(struct rt_device *device, rt_int32_t pin, rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int32_t irqindex;

    if (nu_port_check(pin))
        return -(RT_ERROR);

    level = rt_hw_interrupt_disable();

    // Find index of pin is attached in pool.
    if ((irqindex = nu_find_irqindex(pin)) >= 0)
        goto exit_nu_gpio_attach_irq;

    // Find available index of pin in pool.
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
    rt_uint32_t int_status;
    GPIO_T *PORT = (GPIO_T *)param;
    rt_uint32_t port_idx = ((rt_uint32_t)PORT - PA_BA) / PORT_OFFSET ;

    int_status = PORT->INTSRC;
    pin_irq_hdr(int_status, port_idx);
    PORT->INTSRC = int_status;
}

static rt_err_t nu_gpio_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    GPIO_T *PORT;
    rt_base_t level;
    uint32_t u32IntAttribs;
    rt_int32_t irqindex;
    rt_err_t ret = RT_EOK;
    IRQn_Type irqn;

    if (nu_port_check(pin))
        return -(RT_ERROR);

    level = rt_hw_interrupt_disable();

    irqindex = nu_find_irqindex(pin);
    if (irqindex == -(RT_ERROR))
    {
        ret = -RT_ERROR;
        goto exit_nu_gpio_irq_enable;
    }

    PORT = (GPIO_T *)(PA_BA + (NU_GET_PORT(pin) * PORT_OFFSET));

    irqn = au32GPIRQ[NU_GET_PORT(pin)];

    if (enabled == PIN_IRQ_ENABLE)
    {
        if (pin_irq_hdr_tab[irqindex].mode == PIN_IRQ_MODE_RISING)
            u32IntAttribs = GPIO_INT_RISING;
        else if (pin_irq_hdr_tab[irqindex].mode == PIN_IRQ_MODE_FALLING)
            u32IntAttribs = GPIO_INT_FALLING;
        else if (pin_irq_hdr_tab[irqindex].mode == PIN_IRQ_MODE_RISING_FALLING)
            u32IntAttribs = GPIO_INT_BOTH_EDGE;
        else if (pin_irq_hdr_tab[irqindex].mode == PIN_IRQ_MODE_HIGH_LEVEL)
            u32IntAttribs = GPIO_INT_HIGH;
        else if (pin_irq_hdr_tab[irqindex].mode == PIN_IRQ_MODE_LOW_LEVEL)
            u32IntAttribs = GPIO_INT_LOW;
        else
            goto exit_nu_gpio_irq_enable;

        GPIO_EnableInt(PORT, NU_GET_PINS(pin), u32IntAttribs);

        rt_hw_interrupt_umask(irqn);

    }
    else
    {
        GPIO_DisableInt(PORT, NU_GET_PINS(pin));
        rt_hw_interrupt_mask(irqn);
    }

exit_nu_gpio_irq_enable:

    rt_hw_interrupt_enable(level);
    return -(ret);
}

int rt_hw_gpio_init(void)
{
    char szTmp[16];
    int i;
    rt_int32_t irqindex;
    for (irqindex = 0; irqindex < IRQ_MAX_NUM ; irqindex++)
    {
        pin_irq_hdr_tab[irqindex].pin = PIN_IRQ_PIN_NONE;
        pin_irq_hdr_tab[irqindex].hdr = RT_NULL;
        pin_irq_hdr_tab[irqindex].mode = PIN_IRQ_MODE_RISING;
        pin_irq_hdr_tab[irqindex].args = RT_NULL;
    }

    for (i = 0; i < NU_PORT_CNT ; i++)
    {
        IRQn_Type irqn = au32GPIRQ[i];
        snprintf(szTmp, sizeof(szTmp), "gpio-%d", i);
        rt_hw_interrupt_install(irqn, nu_gpio_isr, (void *)(PA_BA + (i * PORT_OFFSET)), szTmp);
        rt_hw_interrupt_set_type(irqn, HIGH_LEVEL_SENSITIVE);
    }

    nu_sys_ipclk_enable(GPIOCKEN);

    return rt_device_pin_register("gpio", &nu_gpio_ops, RT_NULL);
}

INIT_BOARD_EXPORT(rt_hw_gpio_init);

#endif //#if (defined(BSP_USING_GPIO) && defined(RT_USING_PIN))
