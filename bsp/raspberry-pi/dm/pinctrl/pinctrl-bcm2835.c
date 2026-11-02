/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pinctrl.bcm2835"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <bitmap.h>
#include <dev_pin_dm.h>
#include <dt-bindings/pinctrl/bcm2835.h>

/* GPIO register offsets */
#define GPFSEL0                         0x0     /* Function Select */
#define GPSET0                          0x1c    /* Pin Output Set */
#define GPCLR0                          0x28    /* Pin Output Clear */
#define GPLEV0                          0x34    /* Pin Level */
#define GPEDS0                          0x40    /* Pin Event Detect Status */
#define GPREN0                          0x4c    /* Pin Rising Edge Detect Enable */
#define GPFEN0                          0x58    /* Pin Falling Edge Detect Enable */
#define GPHEN0                          0x64    /* Pin High Detect Enable */
#define GPLEN0                          0x70    /* Pin Low Detect Enable */
#define GPAREN0                         0x7c    /* Pin Async Rising Edge Detect */
#define GPAFEN0                         0x88    /* Pin Async Falling Edge Detect */
#define GPPUD                           0x94    /* Pin Pull-up/down Enable */
#define GPPUDCLK0                       0x98    /* Pin Pull-up/down Enable Clock */
#define GP_GPIO_PUP_PDN_CNTRL_REG0      0xe4    /* 2711 Pin Pull-up/down select */

#define FSEL_REG(p)                     (GPFSEL0 + (((p) / 10) * 4))
#define FSEL_SHIFT(p)                   (((p) % 10) * 3)
#define GPIO_REG_OFFSET(p)              ((p) / 32)
#define GPIO_REG_SHIFT(p)               ((p) % 32)

#define PUD_2711_MASK                   0x3
#define PUD_2711_REG_OFFSET(p)          ((p) / 16)
#define PUD_2711_REG_SHIFT(p)           (((p) % 16) * 2)

/* argument: bcm2835_pinconf_pull */
#define BCM2835_PINCONF_PARAM_PULL      (PIN_CONFIG_END + 1)

#define BCM2835_NUM_GPIOS               54
#define BCM2711_NUM_GPIOS               58
#define BCM2835_NUM_BANKS               2
#define BCM2835_NUM_IRQS                3

#define BCM2711_PULL_NONE               0x0
#define BCM2711_PULL_UP                 0x1
#define BCM2711_PULL_DOWN               0x2

enum
{
    SOC_TYPE_BCM2835,
    SOC_TYPE_BCM2711,
    SOC_TYPE_BCM7211,
};

enum bcm2835_fsel
{
    BCM2835_FSEL_COUNT = 8,
    BCM2835_FSEL_MASK = 0x7,
};

struct bcm2835_pinctrl_soc_data
{
    rt_uint32_t soc_type;
    rt_uint32_t num_gpios;
};

struct bcm2835_pinctrl
{
    struct rt_device_pin parent;
    const struct bcm2835_pinctrl_soc_data *soc_data;

    void *base;
    int irqs[BCM2835_NUM_IRQS];

    rt_bitmap_t enabled_irq_map[BCM2835_NUM_BANKS];
    rt_uint8_t irq_type[BCM2711_NUM_GPIOS];

    struct rt_spinlock irq_lock[BCM2835_NUM_BANKS];
    struct rt_spinlock fsel_lock;   /* Protect FSEL registers */
};

#define raw_to_bcm2835_pinctrl(raw) rt_container_of(raw, struct bcm2835_pinctrl, parent)

rt_inline rt_uint32_t bcm2835_gpio_rd(struct bcm2835_pinctrl *pc, int reg)
{
    return HWREG32(pc->base + reg);
}

rt_inline void bcm2835_gpio_wr(struct bcm2835_pinctrl *pc, int reg, rt_uint32_t val)
{
    HWREG32(pc->base + reg) = val;
}

rt_inline int bcm2835_gpio_get_bit(struct bcm2835_pinctrl *pc, int reg, int bit)
{
    reg += GPIO_REG_OFFSET(bit) * 4;
    return (bcm2835_gpio_rd(pc, reg) >> GPIO_REG_SHIFT(bit)) & 1;
}

/* note NOT a read/modify/write cycle */
rt_inline void bcm2835_gpio_set_bit(struct bcm2835_pinctrl *pc, int reg, int bit)
{
    reg += GPIO_REG_OFFSET(bit) * 4;
    bcm2835_gpio_wr(pc, reg, RT_BIT(GPIO_REG_SHIFT(bit)));
}

rt_inline enum bcm2835_fsel bcm2835_pinctrl_fsel_get(struct bcm2835_pinctrl *pc,
        rt_ubase_t pin)
{
    rt_uint32_t val = bcm2835_gpio_rd(pc, FSEL_REG(pin));

    return (val >> FSEL_SHIFT(pin)) & BCM2835_FSEL_MASK;
}

static void bcm2835_pinctrl_fsel_set(struct bcm2835_pinctrl *pc, rt_ubase_t pin,
        enum bcm2835_fsel fsel)
{
    rt_uint32_t val;
    rt_ubase_t level;
    enum bcm2835_fsel cur;

    level = rt_spin_lock_irqsave(&pc->fsel_lock);

    val = bcm2835_gpio_rd(pc, FSEL_REG(pin));
    cur = (val >> FSEL_SHIFT(pin)) & BCM2835_FSEL_MASK;

    if (cur == fsel)
    {
        goto _out_lock;
    }

    if (cur != BCM2835_FSEL_GPIO_IN && fsel != BCM2835_FSEL_GPIO_IN)
    {
        /* Always transition through GPIO_IN */
        val &= ~(BCM2835_FSEL_MASK << FSEL_SHIFT(pin));
        val |= BCM2835_FSEL_GPIO_IN << FSEL_SHIFT(pin);

        bcm2835_gpio_wr(pc, FSEL_REG(pin), val);
    }

    val &= ~(BCM2835_FSEL_MASK << FSEL_SHIFT(pin));
    val |= fsel << FSEL_SHIFT(pin);

    bcm2835_gpio_wr(pc, FSEL_REG(pin), val);

_out_lock:
    rt_spin_unlock_irqrestore(&pc->fsel_lock, level);
}

static void bcm2835_gpio_irq_config_reg(struct bcm2835_pinctrl *pc,
        int reg, int offset, rt_bool_t enable)
{
    rt_uint32_t value;

    reg += GPIO_REG_OFFSET(offset) * 4;
    value = bcm2835_gpio_rd(pc, reg);

    if (enable)
    {
        value |= RT_BIT(GPIO_REG_SHIFT(offset));
    }
    else
    {
        value &= ~(RT_BIT(GPIO_REG_SHIFT(offset)));
    }

    bcm2835_gpio_wr(pc, reg, value);
}

/* fast path for IRQ handler */
static void bcm2835_gpio_irq_config(struct bcm2835_pinctrl *pc, int offset, rt_bool_t enable)
{
    switch (pc->irq_type[offset])
    {
    case PIN_IRQ_MODE_RISING:
        bcm2835_gpio_irq_config_reg(pc, GPREN0, offset, enable);
        break;

    case PIN_IRQ_MODE_FALLING:
        bcm2835_gpio_irq_config_reg(pc, GPFEN0, offset, enable);
        break;

    case PIN_IRQ_MODE_RISING_FALLING:
        bcm2835_gpio_irq_config_reg(pc, GPREN0, offset, enable);
        bcm2835_gpio_irq_config_reg(pc, GPFEN0, offset, enable);
        break;

    case PIN_IRQ_MODE_HIGH_LEVEL:
        bcm2835_gpio_irq_config_reg(pc, GPHEN0, offset, enable);
        break;

    case PIN_IRQ_MODE_LOW_LEVEL:
        bcm2835_gpio_irq_config_reg(pc, GPLEN0, offset, enable);
        break;
    }
}

static rt_err_t bcm2835_gpio_irq_set_type_enabled(struct bcm2835_pinctrl *pc,
        int offset, rt_uint8_t type)
{
    switch (type)
    {
    case PIN_IRQ_MODE_RISING:
        if (pc->irq_type[offset] == PIN_IRQ_MODE_RISING_FALLING)
        {
            /* RISING already enabled, disable FALLING */
            pc->irq_type[offset] = PIN_IRQ_MODE_FALLING;
            bcm2835_gpio_irq_config(pc, offset, RT_FALSE);
            pc->irq_type[offset] = type;
        }
        else if (pc->irq_type[offset] != type)
        {
            bcm2835_gpio_irq_config(pc, offset, RT_FALSE);
            pc->irq_type[offset] = type;
            bcm2835_gpio_irq_config(pc, offset, RT_TRUE);
        }
        break;

    case PIN_IRQ_MODE_FALLING:
        if (pc->irq_type[offset] == PIN_IRQ_MODE_RISING_FALLING)
        {
            /* FALLING already enabled, disable RISING */
            pc->irq_type[offset] = PIN_IRQ_MODE_RISING;
            bcm2835_gpio_irq_config(pc, offset, RT_FALSE);
            pc->irq_type[offset] = type;
        }
        else if (pc->irq_type[offset] != type)
        {
            bcm2835_gpio_irq_config(pc, offset, RT_FALSE);
            pc->irq_type[offset] = type;
            bcm2835_gpio_irq_config(pc, offset, RT_TRUE);
        }
        break;

    case PIN_IRQ_MODE_RISING_FALLING:
        if (pc->irq_type[offset] == PIN_IRQ_MODE_RISING)
        {
            /* RISING already enabled, enable FALLING too */
            pc->irq_type[offset] = PIN_IRQ_MODE_FALLING;
            bcm2835_gpio_irq_config(pc, offset, RT_TRUE);
            pc->irq_type[offset] = type;
        }
        else if (pc->irq_type[offset] == PIN_IRQ_MODE_FALLING)
        {
            /* FALLING already enabled, enable RISING too */
            pc->irq_type[offset] = PIN_IRQ_MODE_RISING;
            bcm2835_gpio_irq_config(pc, offset, RT_TRUE);
            pc->irq_type[offset] = type;
        }
        else if (pc->irq_type[offset] != type)
        {
            bcm2835_gpio_irq_config(pc, offset, RT_FALSE);
            pc->irq_type[offset] = type;
            bcm2835_gpio_irq_config(pc, offset, RT_TRUE);
        }
        break;

    case PIN_IRQ_MODE_HIGH_LEVEL:
    case PIN_IRQ_MODE_LOW_LEVEL:
        if (pc->irq_type[offset] != type)
        {
            bcm2835_gpio_irq_config(pc, offset, RT_FALSE);
            pc->irq_type[offset] = type;
            bcm2835_gpio_irq_config(pc, offset, RT_TRUE);
        }
        break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t bcm2835_gpio_irq_set_type_disabled(struct bcm2835_pinctrl *pc,
        int offset, rt_uint8_t type)
{
    switch (type)
    {
    case PIN_IRQ_MODE_RISING:
    case PIN_IRQ_MODE_FALLING:
    case PIN_IRQ_MODE_RISING_FALLING:
    case PIN_IRQ_MODE_HIGH_LEVEL:
    case PIN_IRQ_MODE_LOW_LEVEL:
        pc->irq_type[offset] = type;
        break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static void bcm2835_pull_config_set(struct bcm2835_pinctrl *pc, int pin, rt_uint32_t arg)
{
    rt_uint32_t off, bit;

    off = GPIO_REG_OFFSET(pin);
    bit = GPIO_REG_SHIFT(pin);

    bcm2835_gpio_wr(pc, GPPUD, arg & 3);
    /*
     * BCM2835 datasheet say to wait 150 cycles, but not of what.
     * But the VideoCore firmware delay for this operation
     * based nearly on the same amount of VPU cycles and this clock
     * runs at 250 MHz.
     */
    rt_hw_us_delay(1);
    bcm2835_gpio_wr(pc, GPPUDCLK0 + (off * 4), RT_BIT(bit));
    rt_hw_us_delay(1);
    bcm2835_gpio_wr(pc, GPPUDCLK0 + (off * 4), 0);
}

static void bcm2711_pull_config_set(struct bcm2835_pinctrl *pc, int pin, rt_uint32_t arg)
{
    rt_uint32_t shifter, value, off;

    off = PUD_2711_REG_OFFSET(pin);
    shifter = PUD_2711_REG_SHIFT(pin);

    value = bcm2835_gpio_rd(pc, GP_GPIO_PUP_PDN_CNTRL_REG0 + (off * 4));
    value &= ~(PUD_2711_MASK << shifter);
    value |= (arg << shifter);
    bcm2835_gpio_wr(pc, GP_GPIO_PUP_PDN_CNTRL_REG0 + (off * 4), value);
}

static void bcm2835_pinctrl_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    struct bcm2835_pinctrl *pc = raw_to_bcm2835_pinctrl(device);

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        bcm2835_pinctrl_fsel_set(pc, pin, BCM2835_FSEL_GPIO_OUT);
        break;

    case PIN_MODE_INPUT:
        bcm2835_pinctrl_fsel_set(pc, pin, BCM2835_FSEL_GPIO_IN);
        break;

    default:
        break;
    }
}

static void bcm2835_pinctrl_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    struct bcm2835_pinctrl *pc = raw_to_bcm2835_pinctrl(device);

    bcm2835_gpio_set_bit(pc, value ? GPSET0 : GPCLR0, pin);
}

static rt_ssize_t bcm2835_pinctrl_read(struct rt_device *device, rt_base_t pin)
{
    struct bcm2835_pinctrl *pc = raw_to_bcm2835_pinctrl(device);

    return bcm2835_gpio_get_bit(pc, GPLEV0, pin);
}

static rt_err_t bcm2835_pinctrl_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint8_t enabled)
{
    rt_ubase_t level;
    rt_uint32_t offset, bank;
    struct bcm2835_pinctrl *pc = raw_to_bcm2835_pinctrl(device);

    offset = GPIO_REG_SHIFT(pin);
    bank = GPIO_REG_OFFSET(pin);

    level = rt_spin_lock_irqsave(&pc->irq_lock[bank]);

    if (enabled)
    {
        rt_bitmap_set_bit(&pc->enabled_irq_map[bank], offset);
        bcm2835_gpio_irq_config(pc, pin, RT_TRUE);
    }
    else
    {
        bcm2835_gpio_irq_config(pc, pin, RT_FALSE);
        /* Clear events that were latched prior to clearing event sources */
        bcm2835_gpio_set_bit(pc, GPEDS0, pin);
        rt_bitmap_clear_bit(&pc->enabled_irq_map[bank], offset);
    }

    rt_spin_unlock_irqrestore(&pc->irq_lock[bank], level);

    return RT_EOK;
}

static rt_err_t bcm2835_pinctrl_irq_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
    rt_err_t err;
    rt_ubase_t level;
    rt_uint32_t offset, bank;
    struct bcm2835_pinctrl *pc = raw_to_bcm2835_pinctrl(device);

    offset = GPIO_REG_SHIFT(pin);
    bank = GPIO_REG_OFFSET(pin);

    level = rt_spin_lock_irqsave(&pc->irq_lock[bank]);

    if (rt_bitmap_test_bit(&pc->enabled_irq_map[bank], offset))
    {
        err = bcm2835_gpio_irq_set_type_enabled(pc, pin, mode);
    }
    else
    {
        err = bcm2835_gpio_irq_set_type_disabled(pc, pin, mode);
    }

    rt_spin_unlock_irqrestore(&pc->irq_lock[bank], level);

    return err;
}

static rt_err_t bcm2835_pinctrl_confs_apply(struct rt_device *device, void *fw_conf_np)
{
    int pin;
    rt_err_t err;
    const fdt32_t *cell;
    rt_uint32_t value, idx;
    enum bcm2835_fsel fsel;
    struct rt_ofw_prop *prop;
    struct rt_ofw_node *conf_np = fw_conf_np;
    struct bcm2835_pinctrl *pc = raw_to_bcm2835_pinctrl(device);

    if ((err = rt_ofw_prop_read_u32(conf_np, "brcm,function", &value)))
    {
        return err;
    }
    fsel = value;

    idx = 0;
    rt_ofw_foreach_prop_u32(conf_np, "brcm,pins", prop, cell, value)
    {
        if (prop->length < sizeof(*cell))
        {
            break;
        }

        pin = value;
        bcm2835_pinctrl_fsel_set(pc, pin, fsel);

        if (rt_ofw_prop_read_u32_index(conf_np, "brcm,pull", idx++, &value))
        {
            continue;
        }

        if (pc->soc_data->soc_type == SOC_TYPE_BCM2835)
        {
            bcm2835_pull_config_set(pc, pin, value);
        }
        else
        {
            bcm2711_pull_config_set(pc, pin, value);
        }
    }

    return RT_EOK;
}

static const struct rt_pin_ops bcm2835_pinctrl_ops =
{
    .pin_mode = bcm2835_pinctrl_mode,
    .pin_write = bcm2835_pinctrl_write,
    .pin_read = bcm2835_pinctrl_read,
    .pin_irq_enable = bcm2835_pinctrl_irq_enable,
    .pin_irq_mode = bcm2835_pinctrl_irq_mode,
    .pin_ctrl_confs_apply = bcm2835_pinctrl_confs_apply,
};

static void bcm2835_gpio_bank_isr(struct bcm2835_pinctrl *pc, int bank, rt_uint32_t mask)
{
    rt_ubase_t events;
    rt_uint32_t offset, gpio, levs, levs2;

    events = bcm2835_gpio_rd(pc, GPEDS0 + bank * 4);
    levs = bcm2835_gpio_rd(pc, GPLEV0 + bank * 4);
    events &= mask;
    events &= pc->enabled_irq_map[bank];
    bcm2835_gpio_wr(pc, GPEDS0 + bank * 4, events);

_retry:
    rt_bitmap_for_each_set_bit(&events, offset, 32)
    {
        gpio = (32 * bank) + offset;

        pin_pic_handle_isr(&pc->parent, gpio);
    }

    events = bcm2835_gpio_rd(pc, GPEDS0 + bank * 4);
    levs2 = bcm2835_gpio_rd(pc, GPLEV0 + bank * 4);

    events |= levs2 & ~levs & bcm2835_gpio_rd(pc, GPREN0 + bank * 4);
    events |= ~levs2 & levs & bcm2835_gpio_rd(pc, GPFEN0 + bank * 4);
    events &= mask;
    events &= pc->enabled_irq_map[bank];

    if (events)
    {
        bcm2835_gpio_wr(pc, GPEDS0 + bank * 4, events);
        levs = levs2;
        goto _retry;
    }
}

static void bcm2835_pinctrl_isr(int irq, void *param)
{
    int group = 0;
    struct bcm2835_pinctrl *pc = param;

    for (int i = 0; i < BCM2835_NUM_IRQS; ++i)
    {
        if (pc->irqs[i] == irq)
        {
            group = i;
            break;
        }
    }

    switch (group)
    {
    case 0: /* IRQ0 covers GPIOs 0-27 */
        bcm2835_gpio_bank_isr(pc, 0, 0x0fffffff);
        break;

    case 1: /* IRQ1 covers GPIOs 28-45 */
        bcm2835_gpio_bank_isr(pc, 0, 0xf0000000);
        bcm2835_gpio_bank_isr(pc, 1, 0x00003fff);
        break;

    case 2: /* IRQ2 covers GPIOs 46-57 */
        bcm2835_gpio_bank_isr(pc, 1, 0x003fc000);
        break;
    }
}

static rt_err_t bcm2835_pinctrl_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node;
    const struct bcm2835_pinctrl_soc_data *soc_data;
    struct bcm2835_pinctrl *pc = rt_calloc(1, sizeof(*pc));

    if (!pc)
    {
        return -RT_ENOMEM;
    }
    soc_data = pdev->id->data;
    pc->soc_data = soc_data;

    if (!(pc->base = rt_dm_dev_iomap(dev, 0)))
    {
        err = -RT_EIO;
        goto _fail;
    }

    rt_spin_lock_init(&pc->fsel_lock);

    for (int i = 0; i < BCM2835_NUM_BANKS; ++i)
    {
        int offset;
        rt_ubase_t events;

        /* clear event detection flags */
        bcm2835_gpio_wr(pc, GPREN0 + i * 4, 0);
        bcm2835_gpio_wr(pc, GPFEN0 + i * 4, 0);
        bcm2835_gpio_wr(pc, GPHEN0 + i * 4, 0);
        bcm2835_gpio_wr(pc, GPLEN0 + i * 4, 0);
        bcm2835_gpio_wr(pc, GPAREN0 + i * 4, 0);
        bcm2835_gpio_wr(pc, GPAFEN0 + i * 4, 0);

        /* clear all the events */
        events = bcm2835_gpio_rd(pc, GPEDS0 + i * 4);
        rt_bitmap_for_each_set_bit(&events, offset, 32)
        {
            bcm2835_gpio_wr(pc, GPEDS0 + i * 4, RT_BIT(offset));
        }

        rt_spin_lock_init(&pc->irq_lock[i]);
    }

    pc->parent.ops = &bcm2835_pinctrl_ops;
    pin_api_init(&pc->parent, soc_data->num_gpios);
    pin_pic_init(&pc->parent, pc->irqs[0]);

    for (int i = 0; i < RT_ARRAY_SIZE(pc->irqs); ++i)
    {
        pc->irqs[i] = rt_dm_dev_get_irq(dev, i);

        if (soc_data->soc_type != SOC_TYPE_BCM7211)
        {
            if (pc->irqs[i] < 0)
            {
                break;
            }

            continue;
        }
        else if (pc->irqs[i] < 0)
        {
            err = pc->irqs[i];
            goto _fail;
        }
    }

    for (int i = 0; i < RT_ARRAY_SIZE(pc->irqs); ++i)
    {
        int irq = pc->irqs[i];

        if (irq < 0)
        {
            break;
        }

        rt_hw_interrupt_install(irq, bcm2835_pinctrl_isr, pc, "bcm2835-pinctrl");
        rt_hw_interrupt_umask(irq);
    }

    rt_ofw_data(np) = &pc->parent;

    return RT_EOK;

_fail:
    rt_free(pc);

    return err;
}

static struct bcm2835_pinctrl_soc_data bcm2835_data =
{
    .soc_type = SOC_TYPE_BCM2835,
    .num_gpios = BCM2835_NUM_GPIOS,
};

static struct bcm2835_pinctrl_soc_data bcm2711_data =
{
    .soc_type = SOC_TYPE_BCM2711,
    .num_gpios = BCM2711_NUM_GPIOS,
};

static struct bcm2835_pinctrl_soc_data bcm7211_data =
{
    .soc_type = SOC_TYPE_BCM7211,
    .num_gpios = BCM2711_NUM_GPIOS,
};

static const struct rt_ofw_node_id bcm2835_pinctrl_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-gpio", .data = &bcm2835_data },
    { .compatible = "brcm,bcm2711-gpio", .data = &bcm2711_data },
    { .compatible = "brcm,bcm7211-gpio", .data = &bcm7211_data },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835_pinctrl_driver =
{
    .name = "pinctrl-bcm2835",
    .ids = bcm2835_pinctrl_ofw_ids,

    .probe = bcm2835_pinctrl_probe,
};

static int bcm2835_pinctrl_register(void)
{
    rt_platform_driver_register(&bcm2835_pinctrl_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(bcm2835_pinctrl_register);
