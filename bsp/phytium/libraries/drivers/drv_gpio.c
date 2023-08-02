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
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "interrupt.h"
#include "rtdbg.h"
#ifdef RT_USING_SMART
    #include "ioremap.h"
#endif

#include <string.h>

#if defined(TARGET_E2000)
    #include "fparameters.h"
#endif
#include "fkernel.h"
#include "fpinctrl.h"
#include "fcpu_info.h"
#include "ftypes.h"
#include "board.h"

#ifdef RT_USING_PIN
#include "fiopad.h"
#include "fgpio.h"
#include "drv_gpio.h"
/**************************** Type Definitions *******************************/
typedef void (*FGpioOpsIrqHandler)(s32 vector, void *param);
typedef struct
{
    FGpioDirection direction;
    boolean en_irq;
    FGpioIrqType irq_type;
    FGpioOpsIrqHandler irq_handler;
    void *irq_args;
} FGpioOpsPinConfig;

typedef struct
{
    FGpio ctrl;
    FGpioPin pins[FGPIO_PORT_NUM][FGPIO_PIN_NUM];
    FGpioOpsPinConfig pin_config[FGPIO_PORT_NUM][FGPIO_PIN_NUM];
    boolean init_ok;
} FGpioOps;
/***************** Macros (Inline Functions) Definitions *********************/
#if defined(TARGET_E2000)
    #define FGPIO_VERSION_2
#endif
/************************** Variable Definitions *****************************/
static FGpioOps gpio[FGPIO_NUM];
extern FIOPadCtrl iopad_ctrl;
/*******************************Api Functions*********************************/
static void FGpioOpsSetupCtrlIRQ(FGpio *ctrl)
{
    u32 cpu_id;
    u32 irq_num = ctrl->config.irq_num[0];

    GetCpuId(&cpu_id);
    LOG_D("In FGpioOpsSetupCtrlIRQ() -> cpu_id %d, irq_num %d\r\n", cpu_id, irq_num);
    rt_hw_interrupt_set_target_cpus(irq_num, cpu_id);
    rt_hw_interrupt_set_priority(irq_num, ctrl->config.irq_priority); /* setup interrupt */
    rt_hw_interrupt_install(irq_num, FGpioInterruptHandler, ctrl, NULL); /* register intr handler */
    rt_hw_interrupt_umask(irq_num);
    return;
}

/* setup gpio pin interrupt */
static void FGpioOpsSetupPinIRQ(FGpio *ctrl, FGpioPin *const pin, FGpioOpsPinConfig *config)
{
    u32 cpu_id;
    u32 irq_num = ctrl->config.irq_num[pin->index.pin];

    GetCpuId(&cpu_id);
    LOG_D("in FGpioOpsSetupPinIRQ() -> cpu_id %d, irq_num %d", cpu_id, irq_num);
    rt_hw_interrupt_set_target_cpus(irq_num, cpu_id);
    rt_hw_interrupt_set_priority(irq_num, ctrl->config.irq_priority); /* setup interrupt */
    rt_hw_interrupt_install(irq_num, FGpioInterruptHandler, config->irq_args, NULL); /* register intr handler */
    rt_hw_interrupt_umask(irq_num);
    return;
}

void FIOPadSetGpioMux(u32 ctrl_id_p, u32 pin_id_p)
{
#if defined(TARGET_E2000D)
    if (ctrl_id_p == FGPIO4_ID)
    {
        switch (pin_id_p)
        {
        case 11: /* gpio 4-a-11 */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AC45_REG0_OFFSET, FIOPAD_FUNC6);
            break;
        case 12: /* gpio 4-a-12 */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AE43_REG0_OFFSET, FIOPAD_FUNC6);
            break;
        default:
            LOG_E("Unsupported ctrl pin.");
            RT_ASSERT(0);
            break;
        }
    }
    else
    {
        LOG_E("Unsupported ctrl.");
        RT_ASSERT(0);
    }
#endif

#if defined(TARGET_E2000Q)
    if (ctrl_id_p == FGPIO4_ID)
    {
        switch (pin_id_p)
        {
        case 11: /* gpio 4-a-11 */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AC49_REG0_OFFSET, FIOPAD_FUNC6);
            break;
        case 12: /* gpio 4-a-12 */
            FIOPadSetFunc(&iopad_ctrl, FIOPAD_AE47_REG0_OFFSET, FIOPAD_FUNC6);
            break;
        default:
            LOG_E("Unsupported ctrl pin.");
            RT_ASSERT(0);
            break;
        }
    }
    else
    {
        LOG_E("Unsupported ctrl.");
        RT_ASSERT(0);
    }
#endif
}

/* on E2000, if u want use GPIO-4-11, set pin = FGPIO_OPS_PIN_INDEX(4, 0, 11) */
static void drv_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    u32 ctrl_id = FGPIO_OPS_PIN_CTRL_ID(pin);
    u32 port_id = FGPIO_OPS_PIN_PORT_ID(pin);
    u32 pin_id = FGPIO_OPS_PIN_ID(pin);
    FGpioPinId gpio_pin_id;
    FError err = FGPIO_SUCCESS;
    FGpio *instance = &gpio[ctrl_id].ctrl;
    FGpioPin *pin_instance = &gpio[ctrl_id].pins[port_id][pin_id];
    FGpioOpsPinConfig *pin_config = &gpio[ctrl_id].pin_config[port_id][pin_id];

    if (ctrl_id >= FGPIO_NUM)
    {
        LOG_E("ctrl_id too large!!!");
        return;
    }

    if (FALSE == gpio[ctrl_id].init_ok) /* init ctrl if needed */
    {
        FGpioConfig input_cfg = *FGpioLookupConfig(ctrl_id);
        memset(instance, 0, sizeof(*instance));
#ifdef RT_USING_SMART
        input_cfg.base_addr = (uintptr)rt_ioremap((void *)input_cfg.base_addr, 0x1000);
#endif
        err = FGpioCfgInitialize(instance, &input_cfg);
        if (FGPIO_SUCCESS != err)
        {
            LOG_E("Ctrl: %d init fail!!!\n", ctrl_id);
            return;
        }
        gpio[ctrl_id].init_ok = TRUE;
    }

    FIOPadSetGpioMux(ctrl_id, pin_id);

    if (FT_COMPONENT_IS_READY == pin_instance->is_ready)
    {
        FGpioPinDeInitialize(pin_instance);
    }

    gpio_pin_id.ctrl = ctrl_id;
    gpio_pin_id.port = port_id;
    gpio_pin_id.pin = pin_id;
    err = FGpioPinInitialize(instance, pin_instance, gpio_pin_id);

    if (FGPIO_SUCCESS != err)
    {
        LOG_E("Pin %d-%c-%d init fail!!!\n",
              ctrl_id,
              port_id == 0 ? 'a' : 'b',
              pin_id);
        return;
    }

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        pin_config->direction =  FGPIO_DIR_OUTPUT;
        pin_config->en_irq = FALSE;
        break;
    case PIN_MODE_INPUT:
        pin_config->direction =  FGPIO_DIR_INPUT;
        pin_config->en_irq = TRUE;
        pin_config->irq_type = FGPIO_IRQ_TYPE_EDGE_RISING;
        break;
    default:
        rt_kprintf("Not support mode %d!!!\n", mode);
        break;
    }

    FGpioSetDirection(pin_instance, pin_config->direction);
    rt_kprintf("Init GPIO-%d-%c-%d as an %sput pin\r\n",
               ctrl_id,
               port_id,
               pin_id, pin_config->direction == FGPIO_DIR_OUTPUT ? "out" : "in");
}

void drv_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    u32 ctrl_id = FGPIO_OPS_PIN_CTRL_ID(pin);
    u32 port_id = FGPIO_OPS_PIN_PORT_ID(pin);
    u32 pin_id = FGPIO_OPS_PIN_ID(pin);
    FGpioPin *pin_instance = &gpio[ctrl_id].pins[port_id][pin_id];

    if (pin_instance == RT_NULL)
    {
        rt_kprintf("Pin %d-%c-%d not set mode\n",
                   ctrl_id,
                   port_id == 0 ? 'a' : 'b',
                   pin_id);
        return;
    }
    FGpioSetOutputValue(pin_instance, (value == PIN_HIGH) ? FGPIO_PIN_HIGH : FGPIO_PIN_LOW);
}

rt_int8_t drv_pin_read(struct rt_device *device, rt_base_t pin)
{
    u32 ctrl_id = FGPIO_OPS_PIN_CTRL_ID(pin);
    u32 port_id = FGPIO_OPS_PIN_PORT_ID(pin);
    u32 pin_id = FGPIO_OPS_PIN_ID(pin);
    FGpioPin *pin_instance = &gpio[ctrl_id].pins[port_id][pin_id];

    if (pin_instance == RT_NULL)
    {
        rt_kprintf("Pin %d-%c-%d not set mode\n",
                   ctrl_id,
                   port_id == 0 ? 'a' : 'b',
                   pin_id);
        return RT_ERROR;
    }
    return FGpioGetInputValue(pin_instance) == FGPIO_PIN_HIGH ? PIN_HIGH : PIN_LOW;
}

rt_err_t drv_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                            rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    u32 ctrl_id = FGPIO_OPS_PIN_CTRL_ID(pin);
    u32 port_id = FGPIO_OPS_PIN_PORT_ID(pin);
    u32 pin_id = FGPIO_OPS_PIN_ID(pin);
    rt_base_t level;
    FGpio *instance = &gpio[ctrl_id].ctrl;
    FGpioPin *pin_instance = &gpio[ctrl_id].pins[port_id][pin_id];
    FGpioOpsPinConfig *pin_config = &gpio[ctrl_id].pin_config[port_id][pin_id];

    level = rt_hw_interrupt_disable();

    pin_config->irq_handler = (FGpioOpsIrqHandler)hdr;
    pin_config->irq_args = args;

    if (pin_instance == RT_NULL)
    {
        LOG_E("GPIO%d-%c-%d not init yet.\n", ctrl_id, port_id == 0 ? 'a' : 'b', pin_id);
        return RT_ERROR;
    }

    if (pin_config->en_irq)
    {
        FGpioSetInterruptMask(pin_instance, FALSE);
        FGpioPinId pin_of_ctrl =
        {
            .ctrl = ctrl_id,
            .port = FGPIO_PORT_A,
            .pin = FGPIO_PIN_0
        };

        if (FGPIO_IRQ_BY_CONTROLLER == FGpioGetPinIrqSourceType(pin_of_ctrl)) /* setup for ctrl report interrupt */
        {
            FGpioOpsSetupCtrlIRQ(instance);
            LOG_I("GPIO-%d report irq by controller", ctrl_id);
        }
        else if (FGPIO_IRQ_BY_PIN == FGpioGetPinIrqSourceType(pin_of_ctrl))
        {
            FGpioOpsSetupPinIRQ(instance, pin_instance, pin_config);
            LOG_I("GPIO-%d report irq by pin", ctrl_id);
        }

        switch (mode)
        {
        case PIN_IRQ_MODE_RISING:
            pin_config->irq_type = FGPIO_IRQ_TYPE_EDGE_RISING;
            break;
        case PIN_IRQ_MODE_FALLING:
            pin_config->irq_type = FGPIO_IRQ_TYPE_EDGE_FALLING;
            break;
        case PIN_IRQ_MODE_LOW_LEVEL:
            pin_config->irq_type = FGPIO_IRQ_TYPE_LEVEL_LOW;
            break;
        case PIN_IRQ_MODE_HIGH_LEVEL:
            pin_config->irq_type = FGPIO_IRQ_TYPE_LEVEL_HIGH;
            break;
        default:
            LOG_E("Do not spport irq_mode: %d\n", mode);
            break;
        }
        FGpioSetInterruptType(pin_instance, pin_config->irq_type);
        FGpioRegisterInterruptCB(pin_instance, pin_config->irq_handler,
                                 pin_config->irq_args, TRUE); /* register intr callback */
    }
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t drv_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    u32 ctrl_id = FGPIO_OPS_PIN_CTRL_ID(pin);
    u32 port_id = FGPIO_OPS_PIN_PORT_ID(pin);
    u32 pin_id = FGPIO_OPS_PIN_ID(pin);
    rt_base_t level;
    FGpioPin *pin_instance = &gpio[ctrl_id].pins[port_id][pin_id];
    FGpioOpsPinConfig *pin_config = &gpio[ctrl_id].pin_config[port_id][pin_id];

    if (pin_instance == RT_NULL)
    {
        rt_kprintf("pin %d-%c-%d not set mode\n",
                   ctrl_id,
                   port_id == 0 ? 'a' : 'b',
                   pin_id);
        return RT_ERROR;
    }

    level = rt_hw_interrupt_disable();
    pin_config->irq_handler = RT_NULL;
    pin_config->irq_args = RT_NULL;
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

rt_err_t drv_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    u32 ctrl_id = FGPIO_OPS_PIN_CTRL_ID(pin);
    u32 port_id = FGPIO_OPS_PIN_PORT_ID(pin);
    u32 pin_id = FGPIO_OPS_PIN_ID(pin);
    FGpioPin *pin_instance = &gpio[ctrl_id].pins[port_id][pin_id];

    if (pin_instance == RT_NULL)
    {
        rt_kprintf("Pin %d-%c-%d not set mode\n",
                   ctrl_id,
                   port_id == 0 ? 'a' : 'b',
                   pin_id);
        return RT_ERROR;
    }

    FGpioSetInterruptMask(pin_instance, enabled);

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
    ret = rt_device_pin_register("pin", &drv_pin_ops, RT_NULL);
    rt_kprintf("Register pin with return: %d\n", ret);
    return ret;
}
INIT_DEVICE_EXPORT(ft_pin_init);
#endif /* RT_USING_PIN */