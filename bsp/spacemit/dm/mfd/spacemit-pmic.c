/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>

#define DBG_TAG "mfd.spacemit-pmic"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>
#define __SPACEMIT_PMIC_INTERNAL
#include <mfd/spacemit-pmic.h>

struct restart_config_info
{
    const char *cmd;
    uint32_t value;
};

static const struct restart_config_info config_info[] =
{
    /* Enter uboot fastboot mode after restart */
    { "fastboot", 1 },
    /* Enter uboot shell after restart */
    { "uboot", 2 },
};

static rt_err_t spacemit_pmic_reboot(struct rt_device *dev, char *cmd)
{
    struct spacemit_pmic *pmic = dev->user_data;
    const struct spacemit_pmic_mfd_data *mfd_data = pmic->mfd_data;

    if (cmd)
    {
        for (int i = 0; i < RT_ARRAY_SIZE(config_info); ++i)
        {
            if (!rt_strcmp(cmd, config_info[i].cmd))
            {
                spacemit_pmic_update_bits(pmic,
                    mfd_data->non_reset.reg,
                    mfd_data->non_reset.bit,
                    config_info[i].value);
                break;
            }
        }
    }

    if (spacemit_pmic_update_bits(pmic,
            mfd_data->reboot.reg,
            mfd_data->reboot.bit,
            mfd_data->reboot.bit))
    {
        LOG_E("Failed to %s device", "reboot");
    }

    return RT_EOK;
}

static rt_err_t spacemit_pmic_shutdown(struct rt_device *dev)
{
    struct spacemit_pmic *pmic = dev->user_data;
    const struct spacemit_pmic_mfd_data *mfd_data = pmic->mfd_data;

    if (spacemit_pmic_update_bits(pmic,
            mfd_data->shutdown.reg,
            mfd_data->shutdown.bit,
            mfd_data->shutdown.bit))
    {
        LOG_E("Failed to %s device", "shutdown");
    }

    return RT_EOK;
}

static void spacemit_pmic_irq_mask(struct rt_pic_irq *pirq)
{
    unsigned value;
    struct spacemit_pmic_irqchip *irqchip = raw_to_spacemit_pmic_irqchip(pirq->pic);
    const struct spacemit_pmic_irq_map *irq_map = &irqchip->irqs_map[pirq->hwirq];

    value = irqchip->mask_base + (irq_map->reg_offset / irqchip->reg_stride);

    spacemit_pmic_update_bits(irqchip->pmic, value, irq_map->mask,
            irqchip->mask_unmask_non_inverted ? 0 : irq_map->mask);
}

static void spacemit_pmic_irq_unmask(struct rt_pic_irq *pirq)
{
    unsigned value;
    struct spacemit_pmic_irqchip *irqchip = raw_to_spacemit_pmic_irqchip(pirq->pic);
    const struct spacemit_pmic_irq_map *irq_map = &irqchip->irqs_map[pirq->hwirq];

    value = irqchip->mask_base + (irq_map->reg_offset / irqchip->reg_stride);

    spacemit_pmic_update_bits(irqchip->pmic, value, irq_map->mask,
            irqchip->mask_unmask_non_inverted ? irq_map->mask : 0);
}

static int spacemit_pmic_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    int irq = -1;
    struct rt_pic_irq *pirq = rt_pic_find_irq(pic, hwirq);

    if (pirq)
    {
        struct spacemit_pmic_irqchip *irqchip = raw_to_spacemit_pmic_irqchip(pic);

        irq = rt_pic_config_irq(pic, hwirq, hwirq);
        pirq->mode = mode;
        rt_pic_cascade(pirq, irqchip->pmic->irq);
    }

    return irq;
}

static rt_err_t spacemit_pmic_irq_parse(struct rt_pic *pic, struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    struct spacemit_pmic_irqchip *irqchip = raw_to_spacemit_pmic_irqchip(pic);

    if (args->args_count != 1)
    {
        return -RT_EINVAL;
    }

    out_pirq->mode = rt_pic_irq_get_triger_mode(irqchip->pmic->irq);
    out_pirq->hwirq = args->args[0];

    return RT_EOK;
}

const static struct rt_pic_ops spacemit_pmic_irq_ops =
{
    .name = "Spacemit-PMIC",
    .irq_mask = spacemit_pmic_irq_mask,
    .irq_unmask = spacemit_pmic_irq_unmask,
    .irq_map = spacemit_pmic_irq_map,
    .irq_parse = spacemit_pmic_irq_parse,
};

static void spacemit_pmic_thread_isr(void *param)
{
    rt_uint32_t *status;
    rt_uint16_t base, reg;
    struct rt_pic_irq *pirq;
    struct spacemit_pmic *pmic;
    struct spacemit_pmic_irqchip *irqchip = param;

    pmic = irqchip->pmic;
    status = irqchip->irq_status;

    while (RT_TRUE)
    {
        rt_thread_suspend(irqchip->irq_thread);
        rt_schedule();

        base = irqchip->status_base;
        rt_memset(status, 0, sizeof(*status) * irqchip->num_regs);

        for (int i = 0; i < irqchip->num_regs; ++i)
        {
            reg = base + i * irqchip->reg_stride;
            status[i] = spacemit_pmic_read(pmic, reg);

            if ((rt_err_t)status[i] < 0)
            {
                LOG_E("Read IRQ status failed error = %s", rt_strerror(status[i]));

                goto _end;
            }
        }

        base = irqchip->ack_base;

        for (int i = 0; i < irqchip->num_regs; ++i)
        {
            rt_err_t err;

            reg = base + i * irqchip->reg_stride;
            err = spacemit_pmic_write(pmic, reg, status[i]);

            if (err)
            {
                LOG_E("ACK IRQ failed error = %s", rt_strerror(err));

                goto _end;
            }
        }

        for (int i = 0; i < irqchip->irqs_nr; ++i)
        {
            base = irqchip->irqs_map[i].reg_offset / irqchip->reg_stride;

            if (status[base] & irqchip->irqs_map[i].mask)
            {
                pirq = rt_pic_find_irq(&irqchip->parent, i);

                if (pirq && pirq->pic)
                {
                    rt_pic_handle_isr(pirq);
                }
            }
        }
    _end:
        rt_hw_interrupt_umask(pmic->irq);
    }
}

static void spacemit_pmic_isr(int irqno, void *param)
{
    struct spacemit_pmic_irqchip *irqchip = param;

    rt_hw_interrupt_mask(irqchip->pmic->irq);

    rt_thread_resume(irqchip->irq_thread);
}

#define spacemit_pmic_to_i2c_client(pmic) rt_container_of((pmic)->dev, struct rt_i2c_client, parent)

static unsigned spacemit_pmic_i2c_read(struct spacemit_pmic *pmic, unsigned reg)
{
    rt_uint8_t data = 0;
    rt_uint8_t send_buf[2];
    struct rt_i2c_msg msg[2];
    struct rt_i2c_client *client = spacemit_pmic_to_i2c_client(pmic);

    send_buf[0] = (reg & 0xff);

    msg[0].addr  = client->client_addr + pmic->addr_offset;
    msg[0].flags = RT_I2C_WR;
    msg[0].len   = 1;
    msg[0].buf   = send_buf;

    msg[1].addr  = client->client_addr + pmic->addr_offset;
    msg[1].flags = RT_I2C_RD;
    msg[1].len   = 1;
    msg[1].buf   = &data;

    if (rt_i2c_transfer(client->bus, msg, 2) == 2)
    {
        return data;
    }
    else
    {
        return (unsigned)-RT_ERROR;
    }
}

static rt_err_t spacemit_pmic_i2c_write(struct spacemit_pmic *pmic,
        unsigned reg, unsigned data)
{
    rt_uint8_t send_buf[2];
    struct rt_i2c_msg msg;
    struct rt_i2c_client *client = spacemit_pmic_to_i2c_client(pmic);

    send_buf[0] = reg & 0xff;
    send_buf[1] = data;

    msg.addr = client->client_addr + pmic->addr_offset;
    msg.flags = RT_I2C_WR;
    msg.len = 2;
    msg.buf = send_buf;

    if (rt_i2c_transfer(client->bus, &msg, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}

static rt_err_t spacemit_pmic_i2c_write_bit(struct spacemit_pmic *pmic,
        unsigned reg, unsigned mask, unsigned data)
{
    rt_uint32_t val = spacemit_pmic_i2c_read(pmic, reg);

    if ((rt_int32_t)val < 0)
    {
        return -RT_ERROR;
    }

    if (data)
    {
        val |= mask;
    }
    else
    {
        val &= ~mask;
    }

    return spacemit_pmic_i2c_write(pmic, reg, val);
}

static rt_err_t spacemit_pmic_i2c_update_bits(struct spacemit_pmic *pmic, unsigned reg,
        unsigned mask, unsigned data)
{
    rt_uint32_t old, tmp;

    old = spacemit_pmic_i2c_read(pmic, reg);

    if (old < 0)
    {
        return old;
    }

    tmp = old & ~mask;
    tmp |= (data & mask);

    return spacemit_pmic_i2c_write(pmic, reg, tmp);
}

static rt_err_t create_spacemit_pmic_platform_device(rt_bus_t platform_bus,
        struct spacemit_pmic *pmic, const char *name, void *ofw_node)
{
    rt_err_t err;
    struct rt_platform_device *pdev = rt_platform_device_alloc(name);

    if (!pdev)
    {
        return -RT_ENOMEM;
    }

    pdev->parent.ofw_node = ofw_node;
    pdev->priv = pmic;

    err = rt_bus_add_device(platform_bus, &pdev->parent);

    if (err && err != -RT_ENOSYS)
    {
        LOG_E("Add %s - %s error = %s", "SPACEMIT-PMIC", name, rt_strerror(err));
    }

    return err;
}

static rt_err_t spacemit_pmic_ofw_bind_irq(struct spacemit_pmic_irqchip *irqchip,
        struct rt_ofw_node *dev_np, struct rt_ofw_node *np,
        const struct spacemit_pmic_mfd_endpoint *ep)
{
    /*
     *  ic: spacemit-pmic-interrupt-controller {
     *      #interrupt-cells = <1>;
     *
     *      spacemit-pmic-endpoint0 {
     *          interrupts-extended = <&ic 0>;
     *      }
     *
     *      spacemit-pmic-endpoint1 {
     *          interrupts-extended = <&ic 1>, <&ic 2>;
     *      }
     *  }
     */
    rt_err_t err;
    fdt32_t *values;
    rt_size_t irq_list_size;
    static fdt32_t irq_cell;
    static struct rt_ofw_node *ic_np = RT_NULL;

    if (!ic_np)
    {
        ic_np = rt_ofw_append_child(dev_np, "spacemit-pmic-interrupt-controller");

        if (!ic_np)
        {
            return -RT_ENOSYS;
        }

        irq_cell = cpu_to_fdt32(1);
        err = rt_ofw_append_prop(ic_np, "#interrupt-cells", sizeof(fdt32_t), &irq_cell);

        if (err)
        {
            return err;
        }

        rt_ofw_data(ic_np) = &irqchip->parent;
    }

    irq_list_size = sizeof(fdt32_t) * 2 * ep->irqs_nr;
    values = rt_malloc(irq_list_size);

    if (!values)
    {
        return -RT_ENOMEM;
    }

    for (int i = 0; i < ep->irqs_nr; ++i)
    {
        values[i * 2] = cpu_to_fdt32(ic_np->phandle);
        values[i * 2 + 1] = cpu_to_fdt32(ep->irqs_list[i]);
    }

    if ((err = rt_ofw_append_prop(np, "interrupts-extended", irq_list_size, values)))
    {
        rt_free(values);
    }

    return err;
}

static rt_err_t spacemit_pmic_i2c_probe(struct rt_i2c_client *client)
{
    rt_err_t err;
    rt_bus_t platform_bus;
    struct rt_ofw_node *np, *dev_np;
    struct rt_device *dev = &client->parent;
    struct spacemit_pmic *pmic;
    struct spacemit_pmic_mfd_endpoint *pmic_ep;
    const struct spacemit_pmic_mfd_data *mfd_data = rt_i2c_client_id_data(client);

    platform_bus = rt_bus_find_by_name("platform");

    if (!platform_bus)
    {
        return -RT_EIO;
    }

    if (!(pmic = rt_calloc(1, sizeof(*pmic))))
    {
        return -RT_ENOMEM;
    }
    pmic->dev = dev;
    pmic->mfd_data = mfd_data;
    pmic->read = spacemit_pmic_i2c_read;
    pmic->write = spacemit_pmic_i2c_write;
    pmic->write_bit = spacemit_pmic_i2c_write_bit;
    pmic->update_bits = spacemit_pmic_i2c_update_bits;

    if (mfd_data->irqchip)
    {
        struct spacemit_pmic_irqchip *irqchip = mfd_data->irqchip;

        if ((pmic->irq = rt_dm_dev_get_irq(dev, 0)) < 0)
        {
            err = pmic->irq;
            goto _fail;
        }

        irqchip->pmic = pmic;
        irqchip->parent.priv_data = irqchip;
        irqchip->parent.ops = &spacemit_pmic_irq_ops;

        if ((err = rt_pic_linear_irq(&irqchip->parent, irqchip->irqs_nr)))
        {
            LOG_E("Init %s IRQ chip failed error = %s", "SPACEMIT-PMIC", rt_strerror(err));
            goto _fail;
        }

        /* Clear all interrupts */
        for (int i = 0; i < irqchip->num_regs; ++i)
        {
            spacemit_pmic_write(pmic, irqchip->ack_base + i * irqchip->reg_stride, 0xff);
        }

        rt_pic_user_extends(&irqchip->parent);

        irqchip->irq_thread = rt_thread_create("spacemit-pmic", &spacemit_pmic_thread_isr,
                irqchip, DM_THREAD_STACK_SIZE, RT_THREAD_PRIORITY_MAX / 2, 10);

        if (!irqchip->irq_thread)
        {
            rt_pic_cancel_irq(&irqchip->parent);
            err = -RT_ENOMEM;
            goto _fail;
        }

        rt_thread_startup(irqchip->irq_thread);

        rt_hw_interrupt_install(pmic->irq, spacemit_pmic_isr, irqchip, "spacemit-pmic");
        rt_hw_interrupt_umask(pmic->irq);
    }

    dev->user_data = pmic;

    if (mfd_data->shutdown.reg)
    {
        if (rt_dm_power_off_handler(dev, RT_DM_POWER_OFF_MODE_SHUTDOWN,
                RT_DM_POWER_OFF_PRIO_PLATFORM, spacemit_pmic_shutdown))
        {
            LOG_W("Add %s failed", "shutdown");
        }
    }

    if (mfd_data->reboot.reg)
    {
        if (rt_dm_reboot_mode_register(dev, spacemit_pmic_reboot))
        {
            LOG_W("Add %s failed", "reboot");
        }
    }

    dev_np = dev->ofw_node;
    pmic_ep = mfd_data->endpoint;

    for (int i = 0; i < mfd_data->endpoint_num; ++i, ++pmic_ep)
    {
        np = RT_NULL;

        if (!(np = rt_ofw_get_child_by_tag(dev_np, pmic_ep->ofw_name)))
        {
            if (pmic_ep->ofw_compatible)
            {
                np = rt_ofw_get_child_by_compatible(dev_np, pmic_ep->ofw_compatible);
            }

            if (!np)
            {
                LOG_D("%s not found", pmic_ep->ofw_name);

                continue;
            }
        }

        if (!rt_ofw_node_is_available(np))
        {
            continue;
        }

        if (pmic_ep->irqs_nr)
        {
            if (!np && !(np = rt_ofw_append_child(dev_np, pmic_ep->ofw_name)))
            {
                continue;
            }

            err = spacemit_pmic_ofw_bind_irq(mfd_data->irqchip, dev_np, np, pmic_ep);

            if (err == -RT_ENOMEM)
            {
                goto _out_put;
            }
        }

        err = create_spacemit_pmic_platform_device(platform_bus, pmic, pmic_ep->ofw_name, np);

    _out_put:
        rt_ofw_node_put(np);

        if (err == -RT_ENOMEM)
        {
            LOG_E("No memory to create %s", pmic_ep->ofw_name);
            break;
        }
    }

    return RT_EOK;

_fail:
    rt_free(pmic);

    return err;
}

static const struct rt_ofw_node_id spacemit_pmic_i2c_ofw_ids[] =
{
    { .compatible = "spacemit,spm8821", .data = &spm8821_mfd_data },
    { .compatible = "spacemit,pm853", .data = &pm853_mfd_data },
    { .compatible = "spacemit,sy8810l", .data = &sy8810l_mfd_data },
    { /* sentinel */ },
};

static struct rt_i2c_driver spacemit_pmic_i2c_driver =
{
    .ofw_ids = spacemit_pmic_i2c_ofw_ids,

    .probe = spacemit_pmic_i2c_probe,
};

static int spacemit_pmic_i2c_drv_register(void)
{
    rt_i2c_driver_register(&spacemit_pmic_i2c_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(spacemit_pmic_i2c_drv_register);
