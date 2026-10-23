/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <dev_pin_dm.h>

#define DBG_TAG "pinctrl.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <sunxi_pinctrl.h>

#define SUNXI_PINS_PER_BANK      32
#define SUNXI_MAX_EINT_BANKS     11
#define SUNXI_GPIO_IN            0
#define SUNXI_GPIO_OUT           1
#define SUNXI_PULL_DISABLE       0
#define SUNXI_PULL_UP            1
#define SUNXI_PULL_DOWN          2
#define SUNXI_EINT_CFG           0x200
#define SUNXI_EINT_CTRL          0x210
#define SUNXI_EINT_STATUS        0x214
#define SUNXI_EINT_BANK_STRIDE   0x20
#define SUNXI_EINT_PINS_PER_CFG  8
#define SUNXI_EINT_CFG_BITS      4

#define SUNXI_EINT_RISING        0
#define SUNXI_EINT_FALLING       1
#define SUNXI_EINT_HIGH          2
#define SUNXI_EINT_LOW           3
#define SUNXI_EINT_BOTH          4

struct sunxi_pinctrl;

struct sunxi_pinctrl_irq_bank
{
    struct sunxi_pinctrl *pinctrl;
    rt_uint8_t bank;
    int irq;
};

struct sunxi_pinctrl_irq_handler
{
    void (*hdr)(void *args);
    void *args;
};

struct sunxi_pinctrl
{
    struct rt_device_pin parent;
    const struct sunxi_pinctrl_data *data;

    void *base;
    struct rt_spinlock lock;
    struct sunxi_pinctrl_irq_bank irq_banks[SUNXI_MAX_EINT_BANKS];
    struct sunxi_pinctrl_irq_handler *irq_handlers;
};

#define to_sunxi_pinctrl(raw) rt_container_of(raw, struct sunxi_pinctrl, parent)

/* rt_pin_ops.pin_get has no provider argument; Sunxi systems expose one PIO. */
static struct sunxi_pinctrl *sunxi_pinctrl_primary;

static rt_uint32_t sunxi_pinctrl_field_mask(rt_uint8_t width)
{
    return RT_BIT(width) - 1;
}

static rt_bool_t sunxi_pinctrl_pin_valid(const struct sunxi_pinctrl *pinctrl,
        rt_base_t pin)
{
    rt_uint32_t bank;

    if (pin < 0 || pin >= pinctrl->data->banks_nr * SUNXI_PINS_PER_BANK)
    {
        return RT_FALSE;
    }

    bank = pin / SUNXI_PINS_PER_BANK;

    return pin % SUNXI_PINS_PER_BANK < pinctrl->data->bank_pins[bank];
}

static rt_err_t sunxi_pinctrl_pin_from_name(const struct sunxi_pinctrl *pinctrl,
        const char *name, rt_uint32_t *pin)
{
    rt_uint32_t number = 0;
    rt_uint32_t bank;

    if (!name || name[0] != 'P' || name[1] < 'A' + pinctrl->data->bank_base ||
        name[1] >= 'A' + pinctrl->data->bank_base + pinctrl->data->banks_nr || !name[2])
    {
        return -RT_EINVAL;
    }

    bank = name[1] - 'A' - pinctrl->data->bank_base;
    if (!pinctrl->data->bank_pins[bank])
    {
        return -RT_EINVAL;
    }

    for (name += 2; *name; ++name)
    {
        if (*name < '0' || *name > '9' ||
            number > (pinctrl->data->bank_pins[bank] - 1) / 10)
        {
            return -RT_EINVAL;
        }

        number = number * 10 + *name - '0';

        if (number >= pinctrl->data->bank_pins[bank])
        {
            return -RT_EINVAL;
        }
    }

    *pin = bank * SUNXI_PINS_PER_BANK + number;

    return RT_EOK;
}

static void sunxi_pinctrl_set_field(struct sunxi_pinctrl *pinctrl,
        rt_uint32_t pin, rt_uint16_t reg_offset, rt_uint8_t field_bits,
        rt_uint32_t value)
{
    rt_ubase_t level;
    rt_uint32_t reg_value;
    rt_uint32_t pins_per_reg = 32 / field_bits;
    rt_uint32_t mask = sunxi_pinctrl_field_mask(field_bits);
    rt_uint32_t pin_in_bank = pin % SUNXI_PINS_PER_BANK;
    rt_uint32_t bank = pin / SUNXI_PINS_PER_BANK;
    rt_uint32_t shift = (pin_in_bank % pins_per_reg) * field_bits;
    const struct sunxi_pinctrl_layout *layout = pinctrl->data->layout;
    void *reg = pinctrl->base + bank * layout->bank_stride + reg_offset +
            (pin_in_bank / pins_per_reg) * sizeof(rt_uint32_t);

    level = rt_spin_lock_irqsave(&pinctrl->lock);
    reg_value = HWREG32(reg);
    reg_value &= ~(mask << shift);
    reg_value |= (value & mask) << shift;
    HWREG32(reg) = reg_value;
    rt_spin_unlock_irqrestore(&pinctrl->lock, level);
}

static void sunxi_pinctrl_set_mux(struct sunxi_pinctrl *pinctrl,
        rt_uint32_t pin, rt_uint32_t function)
{
    const struct sunxi_pinctrl_layout *layout = pinctrl->data->layout;

    sunxi_pinctrl_set_field(pinctrl, pin, layout->mux_reg,
            layout->mux_bits, function);
}

static rt_err_t sunxi_pinctrl_function(const struct sunxi_pinctrl *pinctrl,
        const char *name, rt_uint32_t pin, rt_uint32_t *mux)
{
    rt_size_t index;
    rt_uint32_t bank = pin / SUNXI_PINS_PER_BANK;
    rt_uint32_t number = pin % SUNXI_PINS_PER_BANK;

    if (!rt_strcmp(name, "gpio_in"))
    {
        *mux = SUNXI_GPIO_IN;
        return RT_EOK;
    }
    else if (!rt_strcmp(name, "gpio_out"))
    {
        *mux = SUNXI_GPIO_OUT;
        return RT_EOK;
    }
    else if (!rt_strcmp(name, "io_disabled"))
    {
        *mux = pinctrl->data->layout->disabled_mux;
        return RT_EOK;
    }

    for (index = 0; index < pinctrl->data->functions_nr; ++index)
    {
        const struct sunxi_pinctrl_function *function =
                &pinctrl->data->functions[index];

        if (!rt_strcmp(name, function->name) && bank == function->bank &&
            number >= function->first_pin &&
            number < function->first_pin + function->pin_count)
        {
            *mux = function->mux;
            return RT_EOK;
        }
    }

    return -RT_EINVAL;
}

static void sunxi_pinctrl_pin_mode(struct rt_device *device, rt_base_t pin,
        rt_uint8_t mode)
{
    struct sunxi_pinctrl *pinctrl = to_sunxi_pinctrl(device);
    const struct sunxi_pinctrl_layout *layout = pinctrl->data->layout;

    if (!sunxi_pinctrl_pin_valid(pinctrl, pin))
    {
        return;
    }

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
    case PIN_MODE_OUTPUT_OD:
        sunxi_pinctrl_set_mux(pinctrl, pin, SUNXI_GPIO_OUT);
        sunxi_pinctrl_set_field(pinctrl, pin, layout->pull_reg,
                layout->pull_bits, SUNXI_PULL_DISABLE);
        break;

    case PIN_MODE_INPUT_PULLUP:
        sunxi_pinctrl_set_mux(pinctrl, pin, SUNXI_GPIO_IN);
        sunxi_pinctrl_set_field(pinctrl, pin, layout->pull_reg,
                layout->pull_bits, SUNXI_PULL_UP);
        break;

    case PIN_MODE_INPUT_PULLDOWN:
        sunxi_pinctrl_set_mux(pinctrl, pin, SUNXI_GPIO_IN);
        sunxi_pinctrl_set_field(pinctrl, pin, layout->pull_reg,
                layout->pull_bits, SUNXI_PULL_DOWN);
        break;

    default:
        sunxi_pinctrl_set_mux(pinctrl, pin, SUNXI_GPIO_IN);
        sunxi_pinctrl_set_field(pinctrl, pin, layout->pull_reg,
                layout->pull_bits, SUNXI_PULL_DISABLE);
        break;
    }
}

static void sunxi_pinctrl_pin_write(struct rt_device *device, rt_base_t pin,
        rt_uint8_t value)
{
    rt_ubase_t level;
    rt_uint32_t reg_value;
    struct sunxi_pinctrl *pinctrl = to_sunxi_pinctrl(device);
    const struct sunxi_pinctrl_layout *layout = pinctrl->data->layout;
    rt_uint32_t bank;
    rt_uint32_t number;
    void *reg;

    if (!sunxi_pinctrl_pin_valid(pinctrl, pin))
    {
        return;
    }

    bank = pin / SUNXI_PINS_PER_BANK;
    number = pin % SUNXI_PINS_PER_BANK;
    reg = pinctrl->base + bank * layout->bank_stride + layout->data_reg;

    level = rt_spin_lock_irqsave(&pinctrl->lock);
    reg_value = HWREG32(reg);
    reg_value = value ? reg_value | RT_BIT(number) : reg_value & ~RT_BIT(number);
    HWREG32(reg) = reg_value;
    rt_spin_unlock_irqrestore(&pinctrl->lock, level);
}

static rt_ssize_t sunxi_pinctrl_pin_read(struct rt_device *device, rt_base_t pin)
{
    struct sunxi_pinctrl *pinctrl = to_sunxi_pinctrl(device);
    const struct sunxi_pinctrl_layout *layout = pinctrl->data->layout;
    rt_uint32_t bank;
    rt_uint32_t number;

    if (!sunxi_pinctrl_pin_valid(pinctrl, pin))
    {
        return -RT_EINVAL;
    }

    bank = pin / SUNXI_PINS_PER_BANK;
    number = pin % SUNXI_PINS_PER_BANK;

    if (pinctrl->data->irq_read_needs_mux)
    {
        rt_base_t level = rt_spin_lock_irqsave(&pinctrl->lock);
        void *reg = pinctrl->base + bank * layout->bank_stride +
                layout->mux_reg + number / 8 * 4;
        rt_uint32_t shift = number % 8 * 4;
        rt_uint32_t mux = HWREG32(reg);
        rt_ssize_t value;

        if (((mux >> shift) & 0xf) == pinctrl->data->irq_mux)
        {
            HWREG32(reg) = mux & ~(0xfU << shift);
        }
        value = !!(HWREG32(pinctrl->base + bank * layout->bank_stride +
                layout->data_reg) & RT_BIT(number));
        HWREG32(reg) = mux;
        rt_spin_unlock_irqrestore(&pinctrl->lock, level);
        return value;
    }

    return !!(HWREG32(pinctrl->base + bank * layout->bank_stride +
            layout->data_reg) & RT_BIT(number));
}

static rt_base_t sunxi_pinctrl_pin_get(const char *name)
{
    rt_uint32_t pin;

    if (!sunxi_pinctrl_primary)
    {
        return -RT_EINVAL;
    }

    return sunxi_pinctrl_pin_from_name(sunxi_pinctrl_primary, name, &pin) ?
            -RT_EINVAL : pin;
}

static rt_ssize_t sunxi_pinctrl_pin_parse(struct rt_device *device,
        struct rt_ofw_cell_args *args, rt_uint32_t *flags)
{
    struct sunxi_pinctrl *pinctrl = to_sunxi_pinctrl(device);

    if (args->args_count != 3 || args->args[0] >= pinctrl->data->banks_nr ||
        args->args[1] >= pinctrl->data->bank_pins[args->args[0]])
    {
        return -RT_EINVAL;
    }

    *flags = args->args[2];

    return args->args[0] * SUNXI_PINS_PER_BANK + args->args[1];
}

static rt_err_t sunxi_pinctrl_irq_mode_to_hw(rt_uint8_t mode,
        rt_uint32_t *hw_mode)
{
    switch (mode)
    {
    case PIN_IRQ_MODE_RISING:
        *hw_mode = SUNXI_EINT_RISING;
        break;
    case PIN_IRQ_MODE_FALLING:
        *hw_mode = SUNXI_EINT_FALLING;
        break;
    case PIN_IRQ_MODE_RISING_FALLING:
        *hw_mode = SUNXI_EINT_BOTH;
        break;
    case PIN_IRQ_MODE_HIGH_LEVEL:
        *hw_mode = SUNXI_EINT_HIGH;
        break;
    case PIN_IRQ_MODE_LOW_LEVEL:
        *hw_mode = SUNXI_EINT_LOW;
        break;
    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_bool_t sunxi_pinctrl_irq_bank_valid(struct sunxi_pinctrl *pinctrl,
        rt_uint32_t bank)
{
    rt_size_t index;

    for (index = 0; index < pinctrl->data->irq_banks; ++index)
    {
        if (bank == (pinctrl->data->irq_bank_map ?
                pinctrl->data->irq_bank_map[index] : index))
        {
            return RT_TRUE;
        }
    }
    return RT_FALSE;
}

static rt_err_t sunxi_pinctrl_pin_irq_mode(struct rt_device *device,
        rt_base_t pin, rt_uint8_t mode)
{
    rt_ubase_t level;
    rt_uint32_t control;
    rt_uint32_t hw_mode;
    rt_uint32_t bank;
    rt_uint32_t number;
    rt_uint32_t cfg_offset;
    rt_uint32_t cfg_shift;
    struct sunxi_pinctrl *pinctrl = to_sunxi_pinctrl(device);

    if (!pinctrl->data->irq_banks ||
            !sunxi_pinctrl_pin_valid(pinctrl, pin))
    {
        return -RT_ENOSYS;
    }
    bank = pin / SUNXI_PINS_PER_BANK;
    if (!sunxi_pinctrl_irq_bank_valid(pinctrl, bank) ||
            sunxi_pinctrl_irq_mode_to_hw(mode, &hw_mode))
    {
        return -RT_EINVAL;
    }

    number = pin % SUNXI_PINS_PER_BANK;
    cfg_offset = SUNXI_EINT_CFG + bank * SUNXI_EINT_BANK_STRIDE +
            number / SUNXI_EINT_PINS_PER_CFG * sizeof(rt_uint32_t);
    cfg_shift = number % SUNXI_EINT_PINS_PER_CFG * SUNXI_EINT_CFG_BITS;

    sunxi_pinctrl_set_mux(pinctrl, pin, pinctrl->data->irq_mux);

    level = rt_spin_lock_irqsave(&pinctrl->lock);
    control = HWREG32(pinctrl->base + cfg_offset);
    control &= ~(0xf << cfg_shift);
    control |= hw_mode << cfg_shift;
    HWREG32(pinctrl->base + cfg_offset) = control;
    HWREG32(pinctrl->base + SUNXI_EINT_STATUS +
            bank * SUNXI_EINT_BANK_STRIDE) = RT_BIT(number);
    rt_spin_unlock_irqrestore(&pinctrl->lock, level);

    return RT_EOK;
}

static rt_err_t sunxi_pinctrl_pin_irq_enable(struct rt_device *device,
        rt_base_t pin, rt_uint8_t enabled)
{
    rt_ubase_t level;
    rt_uint32_t bank;
    rt_uint32_t number;
    rt_uint32_t control;
    struct sunxi_pinctrl *pinctrl = to_sunxi_pinctrl(device);

    if (!pinctrl->data->irq_banks ||
            !sunxi_pinctrl_pin_valid(pinctrl, pin))
    {
        return -RT_ENOSYS;
    }

    bank = pin / SUNXI_PINS_PER_BANK;
    number = pin % SUNXI_PINS_PER_BANK;
    if (!sunxi_pinctrl_irq_bank_valid(pinctrl, bank))
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&pinctrl->lock);
    control = HWREG32(pinctrl->base + SUNXI_EINT_CTRL +
            bank * SUNXI_EINT_BANK_STRIDE);
    if (enabled)
    {
        HWREG32(pinctrl->base + SUNXI_EINT_STATUS +
                bank * SUNXI_EINT_BANK_STRIDE) = RT_BIT(number);
        control |= RT_BIT(number);
    }
    else
    {
        control &= ~RT_BIT(number);
    }
    HWREG32(pinctrl->base + SUNXI_EINT_CTRL +
            bank * SUNXI_EINT_BANK_STRIDE) = control;
    rt_spin_unlock_irqrestore(&pinctrl->lock, level);

    return RT_EOK;
}

static rt_err_t sunxi_pinctrl_pin_attach_irq(struct rt_device *device,
        rt_base_t pin, rt_uint8_t mode, void (*hdr)(void *args), void *args)
{
    rt_ubase_t level;
    struct sunxi_pinctrl *pinctrl = to_sunxi_pinctrl(device);
    struct sunxi_pinctrl_irq_handler *handler;
    rt_err_t err;

    if (!hdr || !pinctrl->irq_handlers ||
            !sunxi_pinctrl_pin_valid(pinctrl, pin))
    {
        return -RT_EINVAL;
    }
    if ((err = sunxi_pinctrl_pin_irq_mode(device, pin, mode)))
    {
        return err;
    }

    level = rt_spin_lock_irqsave(&pinctrl->lock);
    handler = &pinctrl->irq_handlers[pin];
    if (handler->hdr)
    {
        err = -RT_EBUSY;
    }
    else
    {
        handler->hdr = hdr;
        handler->args = args;
        err = RT_EOK;
    }
    rt_spin_unlock_irqrestore(&pinctrl->lock, level);

    return err;
}

static rt_err_t sunxi_pinctrl_pin_detach_irq(struct rt_device *device,
        rt_base_t pin)
{
    rt_ubase_t level;
    struct sunxi_pinctrl *pinctrl = to_sunxi_pinctrl(device);

    if (!pinctrl->irq_handlers || !sunxi_pinctrl_pin_valid(pinctrl, pin))
    {
        return -RT_EINVAL;
    }

    sunxi_pinctrl_pin_irq_enable(device, pin, PIN_IRQ_DISABLE);
    level = rt_spin_lock_irqsave(&pinctrl->lock);
    rt_memset(&pinctrl->irq_handlers[pin], 0,
            sizeof(pinctrl->irq_handlers[pin]));
    rt_spin_unlock_irqrestore(&pinctrl->lock, level);

    return RT_EOK;
}

static void sunxi_pinctrl_irq_handler(int vector, void *param)
{
    rt_uint32_t enabled;
    rt_uint32_t pending;
    rt_uint32_t raw_pending;
    struct sunxi_pinctrl_irq_bank *irq_bank = param;
    struct sunxi_pinctrl *pinctrl = irq_bank->pinctrl;

    RT_UNUSED(vector);

    raw_pending = HWREG32(pinctrl->base + SUNXI_EINT_STATUS +
            irq_bank->bank * SUNXI_EINT_BANK_STRIDE);
    HWREG32(pinctrl->base + SUNXI_EINT_STATUS +
            irq_bank->bank * SUNXI_EINT_BANK_STRIDE) = raw_pending;
    enabled = HWREG32(pinctrl->base + SUNXI_EINT_CTRL +
            irq_bank->bank * SUNXI_EINT_BANK_STRIDE);
    pending = raw_pending & enabled;

    while (pending)
    {
        rt_uint32_t number = __builtin_ctz(pending);
        rt_ubase_t level;
        void (*hdr)(void *args);
        void *args;
        struct sunxi_pinctrl_irq_handler *handler =
                &pinctrl->irq_handlers[irq_bank->bank * SUNXI_PINS_PER_BANK + number];

        pending &= ~RT_BIT(number);
        level = rt_spin_lock_irqsave(&pinctrl->lock);
        hdr = handler->hdr;
        args = handler->args;
        rt_spin_unlock_irqrestore(&pinctrl->lock, level);

        if (hdr)
        {
            hdr(args);
        }
    }
}

static void sunxi_pinctrl_irq_deinit(struct sunxi_pinctrl *pinctrl)
{
    rt_size_t index;

    for (index = 0; index < pinctrl->data->irq_banks; ++index)
    {
        struct sunxi_pinctrl_irq_bank *irq_bank = &pinctrl->irq_banks[index];

        if (irq_bank->irq >= 0)
        {
            rt_hw_interrupt_mask(irq_bank->irq);
            rt_hw_interrupt_uninstall(irq_bank->irq,
                    sunxi_pinctrl_irq_handler, irq_bank);
        }
    }
    rt_free(pinctrl->irq_handlers);
    pinctrl->irq_handlers = RT_NULL;
}

static rt_err_t sunxi_pinctrl_irq_init(struct sunxi_pinctrl *pinctrl,
        struct rt_device *dev)
{
    rt_size_t index;
    rt_size_t pins_nr = pinctrl->data->banks_nr * SUNXI_PINS_PER_BANK;

    if (!pinctrl->data->irq_banks)
    {
        return RT_EOK;
    }
    if (rt_dm_dev_get_irq_count(dev) < pinctrl->data->irq_banks)
    {
        return -RT_EINVAL;
    }

    pinctrl->irq_handlers = rt_calloc(pins_nr,
            sizeof(*pinctrl->irq_handlers));
    if (!pinctrl->irq_handlers)
    {
        return -RT_ENOMEM;
    }

    for (index = 0; index < pinctrl->data->irq_banks; ++index)
    {
        struct sunxi_pinctrl_irq_bank *irq_bank = &pinctrl->irq_banks[index];

        irq_bank->pinctrl = pinctrl;
        irq_bank->bank = pinctrl->data->irq_bank_map ?
                pinctrl->data->irq_bank_map[index] : index;
        irq_bank->irq = rt_dm_dev_get_irq(dev, index);
        if (irq_bank->irq < 0)
        {
            sunxi_pinctrl_irq_deinit(pinctrl);
            return irq_bank->irq;
        }

        rt_hw_interrupt_install(irq_bank->irq, sunxi_pinctrl_irq_handler,
                irq_bank, "sunxi-pio");
        rt_hw_interrupt_umask(irq_bank->irq);
    }

    return RT_EOK;
}

static rt_err_t sunxi_pinctrl_confs_apply(struct rt_device *device,
        void *fw_conf_np)
{
    rt_err_t err;
    rt_uint32_t drive_strength;
    rt_uint32_t function;
    rt_uint32_t pin;
    const char *pin_name;
    const char *function_name;
    struct rt_ofw_prop *prop;
    struct rt_ofw_node *conf_np = fw_conf_np;
    struct sunxi_pinctrl *pinctrl = to_sunxi_pinctrl(device);
    const struct sunxi_pinctrl_layout *layout = pinctrl->data->layout;

    if ((err = rt_ofw_prop_read_string(conf_np, "function", &function_name)))
    {
        LOG_E("%s: missing function", rt_ofw_node_full_name(conf_np));
        return err;
    }

    if (!rt_ofw_prop_read_u32(conf_np, "drive-strength", &drive_strength))
    {
        if (drive_strength < 10 || drive_strength > 40 || drive_strength % 10)
        {
            return -RT_EINVAL;
        }

        drive_strength = drive_strength / 10 - 1;
    }
    else
    {
        drive_strength = RT_UINT32_MAX;
    }

    prop = rt_ofw_get_prop(conf_np, "pins", RT_NULL);
    if (!prop)
    {
        LOG_E("%s: missing pins", rt_ofw_node_full_name(conf_np));
        return -RT_EINVAL;
    }

    for (pin_name = rt_ofw_prop_next_string(prop, RT_NULL); pin_name;
            pin_name = rt_ofw_prop_next_string(prop, pin_name))
    {
        if ((err = sunxi_pinctrl_pin_from_name(pinctrl, pin_name, &pin)))
        {
            LOG_E("%s: invalid pin %s", rt_ofw_node_full_name(conf_np), pin_name);
            return err;
        }

        if ((err = sunxi_pinctrl_function(pinctrl, function_name, pin, &function)))
        {
            LOG_E("%s: function %s is unavailable on %s",
                    rt_ofw_node_full_name(conf_np), function_name, pin_name);
            return err;
        }

        sunxi_pinctrl_set_mux(pinctrl, pin, function);

        if (drive_strength != RT_UINT32_MAX)
        {
            sunxi_pinctrl_set_field(pinctrl, pin, layout->drive_reg,
                    layout->drive_bits, drive_strength);
        }

        if (rt_ofw_prop_read_bool(conf_np, "bias-pull-up"))
        {
            sunxi_pinctrl_set_field(pinctrl, pin, layout->pull_reg,
                    layout->pull_bits, SUNXI_PULL_UP);
        }
        else if (rt_ofw_prop_read_bool(conf_np, "bias-pull-down"))
        {
            sunxi_pinctrl_set_field(pinctrl, pin, layout->pull_reg,
                    layout->pull_bits, SUNXI_PULL_DOWN);
        }
        else if (rt_ofw_prop_read_bool(conf_np, "bias-disable"))
        {
            sunxi_pinctrl_set_field(pinctrl, pin, layout->pull_reg,
                    layout->pull_bits, SUNXI_PULL_DISABLE);
        }
    }

    return RT_EOK;
}

static const struct rt_pin_ops sunxi_pinctrl_ops =
{
    .pin_mode = sunxi_pinctrl_pin_mode,
    .pin_write = sunxi_pinctrl_pin_write,
    .pin_read = sunxi_pinctrl_pin_read,
    .pin_attach_irq = sunxi_pinctrl_pin_attach_irq,
    .pin_detach_irq = sunxi_pinctrl_pin_detach_irq,
    .pin_irq_enable = sunxi_pinctrl_pin_irq_enable,
    .pin_get = sunxi_pinctrl_pin_get,
    .pin_irq_mode = sunxi_pinctrl_pin_irq_mode,
    .pin_parse = sunxi_pinctrl_pin_parse,
    .pin_ctrl_confs_apply = sunxi_pinctrl_confs_apply,
};

static rt_err_t sunxi_pinctrl_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_size_t index;
    struct rt_device *dev = &pdev->parent;
    const struct sunxi_pinctrl_data *data = pdev->id ? pdev->id->data : RT_NULL;
    struct sunxi_pinctrl *pinctrl;

    if (!data || !data->layout || !data->bank_pins || !data->banks_nr ||
        !data->layout->bank_stride || !data->layout->mux_bits ||
        !data->layout->drive_bits || !data->layout->pull_bits ||
        data->layout->mux_bits > 16 || data->layout->drive_bits > 16 ||
        data->layout->pull_bits > 16 ||
        data->irq_banks > data->banks_nr || data->irq_banks > SUNXI_MAX_EINT_BANKS ||
        (data->irq_banks && data->irq_mux >
                sunxi_pinctrl_field_mask(data->layout->mux_bits)) ||
        data->layout->disabled_mux > sunxi_pinctrl_field_mask(data->layout->mux_bits) ||
        (data->functions_nr && !data->functions))
    {
        return -RT_EINVAL;
    }

    for (index = 0; index < data->banks_nr; ++index)
    {
        if (data->bank_pins[index] > SUNXI_PINS_PER_BANK)
        {
            return -RT_EINVAL;
        }
    }

    for (index = 0; data->irq_bank_map && index < data->irq_banks; ++index)
    {
        if (data->irq_bank_map[index] >= data->banks_nr)
        {
            return -RT_EINVAL;
        }
    }

    for (index = 0; index < data->functions_nr; ++index)
    {
        const struct sunxi_pinctrl_function *function = &data->functions[index];

        if (!function->name || !function->pin_count ||
            function->bank >= data->banks_nr ||
            function->first_pin + function->pin_count >
                    data->bank_pins[function->bank] ||
            function->mux > sunxi_pinctrl_field_mask(data->layout->mux_bits))
        {
            return -RT_EINVAL;
        }
    }

    pinctrl = rt_calloc(1, sizeof(*pinctrl));
    if (!pinctrl)
    {
        return -RT_ENOMEM;
    }

    pinctrl->base = rt_dm_dev_iomap(dev, 0);
    if (!pinctrl->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    pinctrl->data = data;
    pinctrl->parent.ops = &sunxi_pinctrl_ops;
    pinctrl->parent.parent.ofw_node = dev->ofw_node;
    rt_spin_lock_init(&pinctrl->lock);

    for (index = 0; index < RT_ARRAY_SIZE(pinctrl->irq_banks); ++index)
    {
        pinctrl->irq_banks[index].irq = -1;
    }
    if ((err = sunxi_pinctrl_irq_init(pinctrl, dev)))
    {
        goto _fail;
    }

    if ((err = pin_api_init(&pinctrl->parent,
            data->banks_nr * SUNXI_PINS_PER_BANK)))
    {
        goto _fail;
    }

    if (!data->bank_base)
    {
        sunxi_pinctrl_primary = pinctrl;
    }
    rt_ofw_data(dev->ofw_node) = &pinctrl->parent;

    return RT_EOK;

_fail:
    sunxi_pinctrl_irq_deinit(pinctrl);
    if (pinctrl->base)
    {
        rt_iounmap(pinctrl->base);
    }
    rt_free(pinctrl);

    return err;
}

static const struct rt_ofw_node_id sunxi_pinctrl_ofw_ids[] =
{
#ifdef RT_PINCTRL_SUN252I_F101
    { .compatible = "allwinner,sun252i-f101-pinctrl", .data = &sun252i_f101_pinctrl_data },
#endif
#ifdef RT_PINCTRL_SUN50I_H616
    { .compatible = "allwinner,sun50i-h616-pinctrl", .data = &sun50i_h616_pinctrl_data },
    { .compatible = "allwinner,sun50i-h616-r-pinctrl", .data = &sun50i_h616_r_pinctrl_data },
#endif
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_pinctrl_driver =
{
    .name = "sunxi-pinctrl",
    .ids = sunxi_pinctrl_ofw_ids,
    .probe = sunxi_pinctrl_probe,
};

static int sunxi_pinctrl_register(void)
{
    rt_platform_driver_register(&sunxi_pinctrl_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(sunxi_pinctrl_register);
