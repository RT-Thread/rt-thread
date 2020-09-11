/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-4-30     misonyo     the first version.
 */

#include <rtthread.h>
#ifdef BSP_USING_GPIO

#include <rthw.h>
#include "drv_gpio.h"
#include "board.h"
#include "fsl_gpio.h"
#include "fsl_iomuxc.h"

#define LOG_TAG             "drv.gpio"
#include <drv_log.h>

#if defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL
    #error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

#define __IMXRT_HDR_DEFAULT                      {-1, 0, RT_NULL, RT_NULL}
#define PIN_INVALID_CHECK(PORT_INDEX,PIN_NUM)    (PORT_INDEX > 4) || ((mask_tab[PORT_INDEX].valid_mask & (1 << PIN_NUM)) == 0)

#if defined(SOC_IMXRT1015_SERIES)
#define muxReg_base         0x401f8024
#define configReg_base      0x401f8198
#elif defined(SOC_IMXRT1020_SERIES)
#define muxReg_base         0x401f8014
#define configReg_base      0x401f8188
#else /* 1050 & 1060 & 1064 series*/
#define MUX_BASE            0x401f8014
#define CONFIG_BASE         0x401f8204
#endif

#define GPIO5_MUX_BASE      0x400A8000
#define GPIO5_CONFIG_BASE   0x400A8018

struct pin_mask
{
    GPIO_Type    *gpio;
    rt_int32_t    valid_mask;
};

const struct pin_mask mask_tab[5] =
{
#if defined(SOC_IMXRT1015_SERIES)
    {GPIO1, 0xfc00ffff},     /* GPIO1,16~25 not supported */
    {GPIO2, 0xffff03f8},     /* GPIO2,0~2,10~15 not supported */
    {GPIO3, 0x7ff0000f},     /* GPIO3,4~19 not supported */
    {GPIO4, 0x00000000},     /* GPIO4 not supported */
    {GPIO5, 0x00000001}      /* GPIO5,0,2,3~31 not supported */
#elif defined(SOC_IMXRT1020_SERIES)
    {GPIO1, 0xffffffff},     /* GPIO1 */
    {GPIO2, 0xffffffff},     /* GPIO2 */
    {GPIO3, 0xffffe3ff},     /* GPIO3,10~12 not supported */
    {GPIO4, 0x00000000},     /* GPIO4 not supported */
    {GPIO5, 0x00000007}      /* GPIO5,3~31 not supported */
#else   /* 1050 & 1060 & 1064 series*/
    {GPIO1, 0xffffffff},     /* GPIO1 */
    {GPIO2, 0xffffffff},     /* GPIO2 */
    {GPIO3, 0x0fffffff},     /* GPIO3,28~31 not supported */
    {GPIO4, 0xffffffff},     /* GPIO4 */
    {GPIO5, 0x00000007}      /* GPIO5,3~31 not supported */
#endif
};

const rt_int8_t reg_offset[] = 
{
#if defined(SOC_IMXRT1015_SERIES)
    38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 64, 65, 66, 67, 68, 69,
    -1, -1, -1, -1,  0,  1,  2,  3,  4,  5, -1, -1, -1, -1, -1, -1, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, -1, -1, -1, -1,
    28, 29, 30, 31, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88,
#elif defined(SOC_IMXRT1020_SERIES)
    42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, -1, -1, -1, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92,
#else /* 1050 & 1060 & 1064 series*/
    42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
    74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99,100,101,102,103,104,105,
   112,113,114,115,116,117,118,119,120,121,122,123,106,107,108,109,110,111, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, -1, -1, -1, -1,
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
#endif
};

static const IRQn_Type irq_tab[10] =
{
    GPIO1_Combined_0_15_IRQn,
    GPIO1_Combined_16_31_IRQn,
    GPIO2_Combined_0_15_IRQn,
    GPIO2_Combined_16_31_IRQn,
    GPIO3_Combined_0_15_IRQn,
    GPIO3_Combined_16_31_IRQn,
    GPIO4_Combined_0_15_IRQn,
    GPIO4_Combined_16_31_IRQn,
    GPIO5_Combined_0_15_IRQn,
    GPIO5_Combined_16_31_IRQn
};

static struct rt_pin_irq_hdr hdr_tab[] =
{
    /* GPIO1 */
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    /* GPIO2 */
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    /* GPIO3 */
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    /* GPIO4 */
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    /* GPIO5 */
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
    __IMXRT_HDR_DEFAULT,
};

static void imxrt_isr(rt_int16_t index_offset, rt_int8_t pin_start, GPIO_Type *base)
{
    rt_int32_t isr_status, index;
    rt_int8_t i, pin_end;

    pin_end = pin_start + 15;
    isr_status = GPIO_PortGetInterruptFlags(base) & base->IMR;

    for (i = pin_start; i <= pin_end ; i++)
    {
        if (isr_status & (1 << i))
        {
            GPIO_PortClearInterruptFlags(base, (1 << i));
            index = index_offset + i;
            if (hdr_tab[index].hdr != RT_NULL)
            {
                hdr_tab[index].hdr(hdr_tab[index].args);
            }
        }
    }
}

/* GPIO1 index offset is 0 */
void GPIO1_Combined_0_15_IRQHandler(void)
{
    rt_interrupt_enter();

    imxrt_isr(0, 0, GPIO1);

    rt_interrupt_leave();
}

void GPIO1_Combined_16_31_IRQHandler(void)
{
    rt_interrupt_enter();

    imxrt_isr(0, 15, GPIO1);

    rt_interrupt_leave();
}

/* GPIO2 index offset is 32 */
void GPIO2_Combined_0_15_IRQHandler(void)
{
    rt_interrupt_enter();

    imxrt_isr(32, 0, GPIO2);

    rt_interrupt_leave();
}

void GPIO2_Combined_16_31_IRQHandler(void)
{
    rt_interrupt_enter();

    imxrt_isr(32, 15, GPIO2);

    rt_interrupt_leave();
}

/* GPIO3 index offset is 64 */
void GPIO3_Combined_0_15_IRQHandler(void)
{
    rt_interrupt_enter();

    imxrt_isr(64, 0, GPIO3);

    rt_interrupt_leave();
}

void GPIO3_Combined_16_31_IRQHandler(void)
{
    rt_interrupt_enter();

    imxrt_isr(64, 15, GPIO3);

    rt_interrupt_leave();
}

#ifdef GPIO4
/* GPIO4 index offset is 96 */
void GPIO4_Combined_0_15_IRQHandler(void)
{
    rt_interrupt_enter();

    imxrt_isr(96, 0, GPIO4);

    rt_interrupt_leave();
}
void GPIO4_Combined_16_31_IRQHandler(void)
{
    rt_interrupt_enter();

    imxrt_isr(96, 15, GPIO4);

    rt_interrupt_leave();
}
#endif

/* GPIO5 index offset is 128 */
void GPIO5_Combined_0_15_IRQHandler(void)
{
    rt_interrupt_enter();

    imxrt_isr(128, 0, GPIO5);

    rt_interrupt_leave();
}

static void imxrt_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    gpio_pin_config_t gpio;
    rt_uint32_t config_value = 0;
    rt_int8_t port, pin_num;

    port = pin >> 5;
    pin_num = pin & 31;

    if (PIN_INVALID_CHECK(port, pin_num))
    {
        LOG_D("invalid pin,rtt pin: %d,port: %d,pin: %d \n", pin,port + 1,pin_num);
        return;
    }

    gpio.outputLogic = 0;
    gpio.interruptMode = kGPIO_NoIntmode;

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
    {
        gpio.direction = kGPIO_DigitalOutput;
        config_value = 0x0030U;    /* Drive Strength R0/6 */
    }
    break;

    case PIN_MODE_INPUT:
    {
        gpio.direction = kGPIO_DigitalInput;
        config_value = 0x0830U;    /* Open Drain Enable */
    }
    break;

    case PIN_MODE_INPUT_PULLDOWN:
    {
        gpio.direction = kGPIO_DigitalInput;
        config_value = 0x3030U;    /* 100K Ohm Pull Down */
    }
    break;

    case PIN_MODE_INPUT_PULLUP:
    {
        gpio.direction = kGPIO_DigitalInput;
        config_value = 0xB030U;    /* 100K Ohm Pull Up */
    }
    break;

    case PIN_MODE_OUTPUT_OD:
    {
        gpio.direction = kGPIO_DigitalOutput;
        config_value = 0x0830U;    /* Open Drain Enable */
    }
    break;
    }

    if (mask_tab[port].gpio != GPIO5)
    {
        CLOCK_EnableClock(kCLOCK_Iomuxc);
        IOMUXC_SetPinMux(MUX_BASE + reg_offset[pin] * 4, 0x5U, 0, 0, CONFIG_BASE + reg_offset[pin] * 4, 1);
        IOMUXC_SetPinConfig(MUX_BASE + reg_offset[pin] * 4, 0x5U, 0, 0, CONFIG_BASE + reg_offset[pin] * 4, config_value);
    }
    else
    {
        CLOCK_EnableClock(kCLOCK_IomuxcSnvs);
        IOMUXC_SetPinMux(GPIO5_MUX_BASE + pin_num * 4, 0x5U, 0, 0, GPIO5_CONFIG_BASE + pin_num * 4, 1);
        IOMUXC_SetPinConfig(GPIO5_MUX_BASE + pin_num * 4, 0x5U, 0, 0, GPIO5_CONFIG_BASE + pin_num * 4, config_value);
    }

    GPIO_PinInit(mask_tab[port].gpio, pin_num, &gpio);
}

static int imxrt_pin_read(rt_device_t dev, rt_base_t pin)
{
    int value;
    rt_int8_t port, pin_num;

    value = PIN_LOW;
    port = pin >> 5;
    pin_num = pin & 31;

    if (PIN_INVALID_CHECK(port, pin_num))
    {
        LOG_D("invalid pin,rtt pin: %d,port: %d,pin: %d \n", pin,port + 1,pin_num);
        return value;
    }

    return GPIO_PinReadPadStatus(mask_tab[port].gpio, pin_num);
}

static void imxrt_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    rt_int8_t port, pin_num;

    port = pin >> 5;
    pin_num = pin & 31;

    if (PIN_INVALID_CHECK(port, pin_num))
    {
        LOG_D("invalid pin,rtt pin: %d,port: %d,pin: %d \n", pin,port + 1,pin_num);
        return;
    }

    GPIO_PinWrite(mask_tab[port].gpio, pin_num, value);
}

static rt_err_t imxrt_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                     rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
    rt_base_t level;
    rt_int8_t port, pin_num;

    port = pin >> 5;
    pin_num = pin & 31;

    if (PIN_INVALID_CHECK(port, pin_num))
    {
        LOG_D("invalid pin,rtt pin: %d,port: %d,pin: %d \n", pin,port + 1,pin_num);
        return RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (hdr_tab[pin].pin == pin &&
        hdr_tab[pin].hdr == hdr &&
        hdr_tab[pin].mode == mode &&
        hdr_tab[pin].args == args)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }

    hdr_tab[pin].pin  = pin;
    hdr_tab[pin].hdr  = hdr;
    hdr_tab[pin].mode = mode;
    hdr_tab[pin].args = args;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t imxrt_pin_detach_irq(struct rt_device *device, rt_int32_t pin)
{
    rt_base_t level;
    rt_int8_t port, pin_num;

    port = pin >> 5;
    pin_num = pin & 31;

    if (PIN_INVALID_CHECK(port, pin_num))
    {
        LOG_D("invalid pin,rtt pin: %d,port: %d,pin: %d \n", pin,port + 1,pin_num);
        return RT_ENOSYS;
    }

    level = rt_hw_interrupt_disable();
    if (hdr_tab[pin].pin == -1)
    {
        rt_hw_interrupt_enable(level);
        return RT_EOK;
    }
    hdr_tab[pin].pin = -1;
    hdr_tab[pin].hdr = RT_NULL;
    hdr_tab[pin].mode = 0;
    hdr_tab[pin].args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t imxrt_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
    gpio_interrupt_mode_t int_mode;
    rt_int8_t port, pin_num, irq_index;

    port = pin >> 5;
    pin_num = pin & 31;

    if (PIN_INVALID_CHECK(port, pin_num))
    {
        LOG_D("invalid pin,rtt pin: %d,port: %d,pin: %d \n", pin,port + 1,pin_num);
        return RT_ENOSYS;
    }

    if (hdr_tab[pin].pin == -1)
    {
        LOG_D("rtt pin: %d callback function not initialized!\n", pin);
        return RT_ENOSYS;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        switch (hdr_tab[pin].mode)
        {
        case PIN_IRQ_MODE_RISING:
            int_mode = kGPIO_IntRisingEdge;
            break;
        case PIN_IRQ_MODE_FALLING:
            int_mode = kGPIO_IntFallingEdge;
            break;
        case PIN_IRQ_MODE_RISING_FALLING:
            int_mode = kGPIO_IntRisingOrFallingEdge;
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            int_mode = kGPIO_IntHighLevel;
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            int_mode = kGPIO_IntLowLevel;
            break;
        default:
            int_mode = kGPIO_IntRisingEdge;
            break;
        }
        irq_index = (port << 1) + (pin_num >> 4);
        GPIO_PinSetInterruptConfig(mask_tab[port].gpio, pin_num, int_mode);
        GPIO_PortEnableInterrupts(mask_tab[port].gpio, 1U << pin_num);
        NVIC_SetPriority(irq_tab[irq_index], NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 5, 0));
        EnableIRQ(irq_tab[irq_index]);
    }
    else if (enabled == PIN_IRQ_DISABLE)
    {
        GPIO_PortDisableInterrupts(mask_tab[port].gpio, 1U << pin_num);
    }
    else
    {
        return RT_EINVAL;
    }

    return RT_EOK;
}
const static struct rt_pin_ops imxrt_pin_ops =
{
    imxrt_pin_mode,
    imxrt_pin_write,
    imxrt_pin_read,
    imxrt_pin_attach_irq,
    imxrt_pin_detach_irq,
    imxrt_pin_irq_enable,
    RT_NULL,
};

int rt_hw_pin_init(void)
{
    int ret = RT_EOK;

    ret = rt_device_pin_register("pin", &imxrt_pin_ops, RT_NULL);

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_pin_init);

#endif /* BSP_USING_GPIO */
