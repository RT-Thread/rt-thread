#include <board.h>
#include "drv_gpio.h"
#include "rtdevice.h"
#include "rthw.h"

#include "xparameters.h"
#include "xgpiops.h"

#define GPIOPS_ID XPAR_XGPIOPS_0_DEVICE_ID
#define GPIO_INTERRUPT_ID XPAR_XGPIOPS_0_INTR

struct hw_intr_node {
    rt_slist_t node;
    rt_uint32_t id;
    void (*hdr)(void *args);
    void *args;
};

static XGpioPs gpio;
static rt_slist_t intr_list;

rt_inline struct hw_intr_node *_find_intr_node(rt_uint32_t id)
{
    struct hw_intr_node *p;
    rt_slist_for_each_entry(p, &intr_list, node)
    {
        if (p->id == id)
        {
            return p;
        }
    }

    return RT_NULL;
}

static void intr_handler(int vector, void *param)
{
    struct hw_intr_node *p;
    rt_slist_for_each_entry(p, &intr_list, node)
    {
        if (!XGpioPs_IntrGetStatusPin(&gpio, p->id))
            continue;

        XGpioPs_IntrDisablePin(&gpio, p->id);
        if (p->hdr)
            p->hdr(p->args);

        XGpioPs_IntrClearPin(&gpio, p->id);
        XGpioPs_IntrEnablePin(&gpio, p->id);
    }
}

static rt_base_t zynq_pin_get(const char *name)
{
    rt_set_errno(-RT_ENOSYS);
    return -1;
}

static void zynq_pin_write(rt_device_t dev, rt_base_t pin, rt_uint8_t value)
{
    if (pin >= XGPIOPS_DEVICE_MAX_PIN_NUM)
    {
        rt_set_errno(-RT_ENOSYS);
        return;
    }

    XGpioPs_WritePin(&gpio, pin, value);
}

static rt_int8_t zynq_pin_read(rt_device_t dev, rt_base_t pin)
{
    if (pin >= XGPIOPS_DEVICE_MAX_PIN_NUM)
    {
        rt_set_errno(-RT_ENOSYS);
        return -1;
    }

    return XGpioPs_ReadPin(&gpio, pin);
}

static void zynq_pin_mode(rt_device_t dev, rt_base_t pin, rt_uint8_t mode)
{
    rt_uint8_t isOutput = (mode == PIN_MODE_OUTPUT) || (mode == PIN_MODE_OUTPUT_OD);
    XGpioPs_SetDirectionPin(&gpio, pin, isOutput);
    XGpioPs_SetOutputEnablePin(&gpio, pin, isOutput);
}

static rt_err_t zynq_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                     rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    u8 irq_type;
    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        irq_type = XGPIOPS_IRQ_TYPE_EDGE_RISING;
        break;

    case PIN_IRQ_MODE_FALLING:
        irq_type = XGPIOPS_IRQ_TYPE_EDGE_FALLING;
        break;

    case PIN_IRQ_MODE_RISING_FALLING:
        irq_type = XGPIOPS_IRQ_TYPE_EDGE_BOTH;
        break;

    case PIN_IRQ_MODE_HIGH_LEVEL:
        irq_type = XGPIOPS_IRQ_TYPE_LEVEL_HIGH;
        break;

    case PIN_IRQ_MODE_LOW_LEVEL:
        irq_type = XGPIOPS_IRQ_TYPE_LEVEL_LOW;
        break;

    default:
        return -RT_ENOSYS;
    }

    struct hw_intr_node *node = _find_intr_node(pin);
    if (node != RT_NULL)
    {
        return -RT_EBUSY;
    }

    node = rt_malloc(sizeof(struct hw_intr_node));
    if (node == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    XGpioPs_SetIntrTypePin(&gpio, pin, irq_type);

    node->id = pin;
    node->hdr = hdr;
    node->args = args;

    rt_slist_append(&intr_list, &node->node);

    return RT_EOK;
}

static rt_err_t zynq_pin_dettach_irq(struct rt_device *device, rt_base_t pin)
{
    struct hw_intr_node *node;

    rt_enter_critical();
    node = _find_intr_node(pin);
    if (node != RT_NULL)
    {
        rt_exit_critical();
        return -RT_ERROR;
    }
    rt_slist_remove(&intr_list, &node->node);
    rt_exit_critical();

    rt_free(node);

    return RT_EOK;
}

static rt_err_t zynq_pin_irq_enable(struct rt_device *device, rt_base_t pin,
                                     rt_uint8_t enabled)
{
    if (enabled)
    {
        XGpioPs_IntrEnablePin(&gpio, pin);
    }
    else
    {
        XGpioPs_IntrDisablePin(&gpio, pin);
    }

    return RT_EOK;
}

const static struct rt_pin_ops _zynq_pin_ops =
{
    zynq_pin_mode,
    zynq_pin_write,
    zynq_pin_read,
    zynq_pin_attach_irq,
    zynq_pin_dettach_irq,
    zynq_pin_irq_enable,
    zynq_pin_get,
};

int rt_hw_pin_init(void)
{
    XGpioPs_Config *gpiops_cfg_ptr;
    gpiops_cfg_ptr = XGpioPs_LookupConfig(GPIOPS_ID);
    RT_ASSERT(gpiops_cfg_ptr);

    RT_ASSERT(
        XGpioPs_CfgInitialize(&gpio, gpiops_cfg_ptr, gpiops_cfg_ptr->BaseAddr)
        == 0
    )

    rt_slist_init(&intr_list);
    rt_hw_interrupt_install(GPIO_INTERRUPT_ID, intr_handler, RT_NULL, "pin");
    rt_hw_interrupt_umask(GPIO_INTERRUPT_ID);

    return rt_device_pin_register("pin", &_zynq_pin_ops, RT_NULL);
}
