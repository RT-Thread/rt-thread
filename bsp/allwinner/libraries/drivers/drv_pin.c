#include <rthw.h>
#include <rtdevice.h>
#include <hal_gpio.h>

static void hal_pin_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    switch (mode)
    {
        case PIN_MODE_OUTPUT:
            hal_gpio_set_direction(pin,GPIO_DIRECTION_OUTPUT);
            break;
        case PIN_MODE_INPUT:
            hal_gpio_set_direction(pin,GPIO_DIRECTION_INPUT);
            break;
        case PIN_MODE_INPUT_PULLDOWN:
            hal_gpio_set_pull(pin, GPIO_PULL_DOWN);
            hal_gpio_set_direction(pin,GPIO_DIRECTION_INPUT);
            break;
        case PIN_MODE_INPUT_PULLUP:
            hal_gpio_set_pull(pin,GPIO_PULL_UP);
            hal_gpio_set_direction(pin,GPIO_DIRECTION_INPUT);
            break;
        case PIN_MODE_OUTPUT_OD:
            hal_gpio_set_pull(pin, GPIO_PULL_DOWN_DISABLED);
            hal_gpio_set_direction(pin,GPIO_DIRECTION_OUTPUT);
            break;
    }
}

static void hal_pin_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    hal_gpio_set_data(pin,value);
}

static rt_ssize_t hal_pin_read(struct rt_device *device, rt_base_t pin)
{
    gpio_data_t value;
    hal_gpio_get_data(pin,&value);
    return (rt_ssize_t)value;
}

static rt_err_t hal_pin_attach_irq(struct rt_device *device, rt_base_t pin,
                                       rt_uint8_t mode, void (*hdr)(void *args),
                                       void *args)
{
    rt_base_t level = 0;
    uint32_t irq;
    int ret = 0;

    ret = hal_gpio_to_irq(pin, &irq);
    if (ret < 0)
    {
        rt_kprintf("gpio to irq error, irq num:%lu error num: %d", irq, ret);
        return -RT_ERROR;
    }

    level = rt_hw_interrupt_disable();
    hal_gpio_set_debounce(pin, 1); // enable debounce 24Mhz
    ret = hal_gpio_irq_attach(irq, hdr, mode + 1, args);
    if (ret < 0)
    {
        rt_hw_interrupt_enable(level);
        rt_kprintf("request irq error, irq num:%lu error num: %d", irq, ret);
        return -RT_ERROR;
    }
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t hal_pin_detach_irq(struct rt_device *device, rt_base_t pin)
{
    rt_base_t level = 0;
    uint32_t irq;
    int ret;

    ret = hal_gpio_to_irq(pin, &irq);
    if (ret < 0)
    {
        rt_kprintf("gpio to irq error, irq num:%lu error num: %d", irq, ret);
        return -RT_ERROR;
    }

    level = rt_hw_interrupt_disable();
    ret = hal_gpio_irq_free(irq);
    if (ret < 0)
    {
        rt_hw_interrupt_enable(level);
        rt_kprintf("free irq error, error num: %d", ret);
        return -RT_ERROR;
    }
    return RT_EOK;
}

static rt_err_t hal_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    uint32_t irq;
    int ret;

    ret = hal_gpio_to_irq(pin, &irq);
    if (ret < 0)
    {
        rt_kprintf("gpio to irq error, irq num:%lu error num: %d", irq, ret);
        return -RT_ERROR;
    }

    if (enabled == PIN_IRQ_ENABLE)
    {
        ret = hal_gpio_irq_enable(irq);
        if (ret < 0)
        {
            rt_kprintf("request irq error, error num: %d", ret);
            return -RT_ERROR;
        }
    }
    else
    {
        ret = hal_gpio_irq_disable(irq);
        if (ret < 0)
        {
            rt_kprintf("disable irq error, irq num:%lu, error num: %d", irq, ret);
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}

static const struct rt_pin_ops gpio_ops =
{
    hal_pin_mode,
    hal_pin_write,
    hal_pin_read,
    hal_pin_attach_irq,
    hal_pin_detach_irq,
    hal_pin_irq_enable,
    RT_NULL,
};

int hal_hw_pin_init(void)
{
    return rt_device_pin_register("pin", &gpio_ops, RT_NULL);
}

INIT_BOARD_EXPORT(hal_hw_pin_init);
