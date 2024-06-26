/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2023/7/24   liqiaozhong  first add, support intr
 * 2024/6/3    zhangyan     Adaptive drive
 *
 */

#include "rtconfig.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "interrupt.h"
#define LOG_TAG      "gpio_drv"
#include "drv_log.h"
#ifdef RT_USING_SMART
    #include "ioremap.h"
#endif

#if defined(TARGET_E2000)
    #include "fparameters.h"
#endif
#include "fkernel.h"
#include "fcpu_info.h"
#include "ftypes.h"
#include "fio_mux.h"
#include "board.h"

#include "fiopad.h"
#include "fgpio.h"
#include "drv_gpio.h"
/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Variable Definitions *****************************/
static FGpio gpio_device[FGPIO_NUM];
extern FGpioIntrMap fgpio_intr_map[FGPIO_CTRL_NUM];
/*******************************Api Functions*********************************/
static void FGpioOpsSetupIRQ(FGpio *ctrl)
{
    rt_uint32_t cpu_id = rt_hw_cpu_id();
    u32 irq_num = ctrl->config.irq_num;

    LOG_D("In FGpioOpsSetupIRQ() -> cpu_id %d, irq_num %d\r\n", cpu_id, irq_num);
    rt_hw_interrupt_set_target_cpus(irq_num, cpu_id);
    rt_hw_interrupt_set_priority(irq_num, 0xd0); /* setup interrupt */
    rt_hw_interrupt_install(irq_num, FGpioInterruptHandler, NULL, NULL); /* register intr handler */
    rt_hw_interrupt_umask(irq_num);

    return;
}

/* on E2000, if u want use GPIO-4-11, set pin = FGPIO_OPS_PIN_INDEX(4, 0, 11) */
static void drv_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    FGpio *instance = (FGpio *)device->user_data;
    FError err = FGPIO_SUCCESS;
    u32 index = (u32)pin;

    if (index >= FGPIO_NUM)
    {
        LOG_E("ctrl_id too large!!!");
        return;
    }

    FGpioConfig input_cfg = *FGpioLookupConfig(index);
    rt_memset(&instance[index], 0, sizeof(FGpio));
#ifdef RT_USING_SMART
    input_cfg.base_addr = (uintptr)rt_ioremap((void *)input_cfg.base_addr, 0x1000);
#endif
    err = FGpioCfgInitialize(&instance[index], &input_cfg);
    if (FGPIO_SUCCESS != err)
    {
        LOG_E("Ctrl: %d init fail!!!\n");
    }

    FIOPadSetGpioMux(instance[index].config.ctrl, instance[index].config.pin);

    switch (mode)
    {
        case PIN_MODE_OUTPUT:
            FGpioSetDirection(&instance[index], FGPIO_DIR_OUTPUT);
            break;
        case PIN_MODE_INPUT:
            FGpioSetDirection(&instance[index], FGPIO_DIR_INPUT);
            break;
        default:
            rt_kprintf("Not support mode %d!!!\n", mode);
            break;
    }

}

void drv_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    FGpio *instance = (FGpio *)device->user_data;
    u32 index = (u32)pin;

    FGpioSetOutputValue(&instance[index], (value == PIN_HIGH) ? FGPIO_PIN_HIGH : FGPIO_PIN_LOW);
}

rt_ssize_t drv_pin_read(struct rt_device *device, rt_base_t pin)
{
    FGpio *instance = (FGpio *)device->user_data;
    u32 index = (u32)pin;

    return FGpioGetInputValue(&instance[index]) == FGPIO_PIN_HIGH ? PIN_HIGH : PIN_LOW;
}

rt_err_t drv_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                            rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    FGpio *instance = (FGpio *)device->user_data;
    u32 index = (u32)pin;
    rt_base_t level;

#ifdef RT_USING_SMART
    FGpioIntrMap *map = &fgpio_intr_map[instance[index].config.ctrl];
    map->base_addr = (uintptr)rt_ioremap((void *)map->base_addr, 0x1000);
#endif

    level = rt_hw_interrupt_disable();

    FGpioOpsSetupIRQ(&instance[index]);

    switch (mode)
    {
        case PIN_IRQ_MODE_RISING:
            FGpioSetInterruptType(&instance[index], FGPIO_IRQ_TYPE_EDGE_RISING);
            break;
        case PIN_IRQ_MODE_FALLING:
            FGpioSetInterruptType(&instance[index], FGPIO_IRQ_TYPE_EDGE_FALLING);
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            FGpioSetInterruptType(&instance[index], FGPIO_IRQ_TYPE_LEVEL_LOW);
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            FGpioSetInterruptType(&instance[index], FGPIO_IRQ_TYPE_LEVEL_HIGH);
            break;
        default:
            LOG_E("Do not spport irq_mode: %d\n", mode);
            break;
    }

    FGpioRegisterInterruptCB(&instance[index], (FGpioInterruptCallback)hdr, args); /* register intr callback */
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t drv_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    FGpio *instance = (FGpio *)device->user_data;
    u32 index = (u32)pin;
    FGpioIntrMap *map = &fgpio_intr_map[instance[index].config.ctrl];
    rt_base_t level;

    level = rt_hw_interrupt_disable();

    if (instance[index].config.cap == FGPIO_CAP_IRQ_BY_PIN)
    {
        map->irq_cbs[instance[index].config.pin] = NULL;
    }
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t drv_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    FGpio *instance = (FGpio *)device->user_data;
    u32 index = (u32)pin;

    FGpioSetInterruptMask(&instance[index], enabled);

    return RT_EOK;
}

const struct rt_pin_ops drv_pin_ops =
{
    .pin_mode = drv_pin_mode,
    .pin_write = drv_pin_write,
    .pin_read = drv_pin_read,

    .pin_attach_irq = drv_pin_attach_irq,
    .pin_detach_irq = drv_pin_detach_irq,
    .pin_irq_enable = drv_pin_irq_enable,
    .pin_get = RT_NULL
};

int ft_pin_init(void)
{
    rt_err_t ret = RT_EOK;
    ret = rt_device_pin_register("pin", &drv_pin_ops, gpio_device);
    rt_kprintf("Register pin with return: %d\n", ret);
    return ret;
}
INIT_DEVICE_EXPORT(ft_pin_init);
