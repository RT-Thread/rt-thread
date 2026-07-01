/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "dvfs.dfi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define PX30_PMUGRF_OS_REG2         0x208
#define PX30_PMUGRF_OS_REG3         0x20c

#define MAX_DMC_NUM_CH              4
#define READ_DRAMTYPE_INFO(n)       (((n) >> 13) & 0x7)
#define READ_DRAMTYPE_INFO_V3(n, m) ((((n) >> 13) & 0x7) | ((((m) >> 12) & 0x3) << 3))
#define READ_SYSREG_VERSION(m)      (((m) >> 28) & 0xf)

#define DDRMON_CTRL                 0x04
#define CLR_DDRMON_CTRL             ((rt_uint32_t)0xffff0000 << 0)
#define DDR2_3_EN                   (0x10001 << 15)
#define LPDDR5_EN                   (0x10001 << 6)
#define DDR4_EN                     (0x10001 << 5)
#define LPDDR4_EN                   (0x10001 << 4)
#define HARDWARE_EN                 (0x10001 << 3)
#define LPDDR2_3_EN                 (0x10001 << 2)
#define SOFTWARE_EN                 (0x10001 << 1)
#define SOFTWARE_DIS                (0x10000 << 1)

enum rockchip_dram_type
{
    ROCKCHIP_DFI_DDR4 = 0,
    ROCKCHIP_DFI_DDR2 = 2,
    ROCKCHIP_DFI_DDR3 = 3,
    ROCKCHIP_DFI_LPDDR2 = 5,
    ROCKCHIP_DFI_LPDDR3 = 6,
    ROCKCHIP_DFI_LPDDR4 = 7,
    ROCKCHIP_DFI_LPDDR4X = 8,
    ROCKCHIP_DFI_LPDDR5 = 9,
};

struct rockchip_dfi_usage
{
    rt_uint64_t access;
    rt_uint64_t total;
};

struct rockchip_dfi
{
    struct rt_dvfs_event event;
    struct rt_platform_device *pdev;

    struct rockchip_dfi_usage ch_usage[MAX_DMC_NUM_CH];

    volatile rt_uint32_t *regs;
    struct rt_syscon *pmugrf;

    rt_uint32_t dram_type;
    rt_uint32_t mon_version;
    rt_uint32_t mon_idx;
    rt_uint32_t mon_ctrl0;
    rt_uint32_t mon_access_num;
    rt_uint32_t mon_count_num;
    rt_uint32_t count_rate;
    rt_uint32_t ch_msk;
};

static void rockchip_dfi_get_mon_version(struct rockchip_dfi *dfi)
{
    dfi->mon_version = dfi->regs[0];

    if (dfi->mon_version < 0x40)
    {
        dfi->mon_ctrl0 = 0x4;
        dfi->mon_access_num = 0x2c;
        dfi->mon_count_num = 0x28;
    }
    else
    {
        dfi->mon_ctrl0 = 0x4;
        dfi->mon_access_num = 0x34;
        dfi->mon_count_num = 0x30;
    }
}

static void rockchip_dfi_start_counter(struct rockchip_dfi *dfi)
{
    rt_uint32_t mon_idx = dfi->mon_idx, ctrl0 = dfi->mon_ctrl0;

    for (rt_uint32_t i = 0; i < MAX_DMC_NUM_CH; ++i)
    {
        rt_uint32_t base;

        if (!(dfi->ch_msk & RT_BIT(i)))
        {
            continue;
        }

        if (i > 0 && mon_idx == 0)
        {
            continue;
        }

        base = i * mon_idx;
        dfi->regs[(base + ctrl0) / 4] = CLR_DDRMON_CTRL;

        switch (dfi->dram_type)
        {
        case ROCKCHIP_DFI_LPDDR3:
        case ROCKCHIP_DFI_LPDDR2:
            dfi->regs[(base + ctrl0) / 4] = LPDDR2_3_EN;
            break;
        case ROCKCHIP_DFI_LPDDR4:
        case ROCKCHIP_DFI_LPDDR4X:
            dfi->regs[(base + ctrl0) / 4] = LPDDR4_EN;
            break;
        case ROCKCHIP_DFI_DDR2:
        case ROCKCHIP_DFI_DDR3:
            dfi->regs[(base + ctrl0) / 4] = DDR2_3_EN;
            break;
        case ROCKCHIP_DFI_DDR4:
            dfi->regs[(base + ctrl0) / 4] = DDR4_EN;
            break;
        default:
            break;
        }

        dfi->regs[(base + ctrl0) / 4] = SOFTWARE_EN;
    }
}

static void rockchip_dfi_stop_counter(struct rockchip_dfi *dfi)
{
    rt_uint32_t mon_idx = dfi->mon_idx;

    for (rt_uint32_t i = 0; i < MAX_DMC_NUM_CH; ++i)
    {
        rt_uint32_t base;

        if (!(dfi->ch_msk & RT_BIT(i)))
        {
            continue;
        }

        if (i > 0 && mon_idx == 0)
        {
            continue;
        }

        base = i * mon_idx;
        dfi->regs[(base + DDRMON_CTRL) / 4] = SOFTWARE_DIS;
    }
}

static int rockchip_dfi_get_busier_ch(struct rockchip_dfi *dfi)
{
    rt_uint32_t busier_ch = 0, max = 0;
    rt_uint32_t mon_idx = dfi->mon_idx ? dfi->mon_idx : 0x14;
    rt_uint32_t count_rate = dfi->count_rate ? dfi->count_rate : 1;

    rockchip_dfi_stop_counter(dfi);

    for (rt_uint32_t i = 0; i < MAX_DMC_NUM_CH; ++i)
    {
        rt_uint32_t tmp, base;

        if (!(dfi->ch_msk & RT_BIT(i)))
        {
            continue;
        }

        base = i * mon_idx;
        dfi->ch_usage[i].total = dfi->regs[(base + dfi->mon_count_num) / 4] * count_rate;

        tmp = dfi->regs[(base + dfi->mon_access_num) / 4];
        if (dfi->dram_type == ROCKCHIP_DFI_LPDDR4 || dfi->dram_type == ROCKCHIP_DFI_LPDDR4X)
        {
            tmp *= 8;
        }
        else
        {
            tmp *= 4;
        }
        dfi->ch_usage[i].access = tmp;

        if (tmp > max)
        {
            max = tmp;
            busier_ch = i;
        }
    }

    rockchip_dfi_start_counter(dfi);

    return (int)busier_ch;
}

static rt_err_t rockchip_dfi_event_ready(struct rt_dvfs_event *ev)
{
    RT_UNUSED(ev);
    return RT_EOK;
}

static rt_err_t rockchip_dfi_event_enable(struct rt_dvfs_event *ev)
{
    struct rockchip_dfi *dfi = ev->priv;

    rockchip_dfi_get_mon_version(dfi);
    rockchip_dfi_start_counter(dfi);

    return RT_EOK;
}

static rt_err_t rockchip_dfi_event_disable(struct rt_dvfs_event *ev)
{
    struct rockchip_dfi *dfi = ev->priv;

    rockchip_dfi_stop_counter(dfi);

    return RT_EOK;
}

static rt_err_t rockchip_dfi_event_read(struct rt_dvfs_event *ev,
        struct rt_dvfs_event_data *evd)
{
    int busier_ch;
    rt_base_t level;
    struct rockchip_dfi *dfi = ev->priv;

    level = rt_hw_interrupt_disable();
    busier_ch = rockchip_dfi_get_busier_ch(dfi);
    rt_hw_interrupt_enable(level);

    evd->load_count = dfi->ch_usage[busier_ch].access;
    evd->total_count = dfi->ch_usage[busier_ch].total;

    return RT_EOK;
}

static const struct rt_dvfs_event_ops rockchip_dfi_event_ops =
{
    .ready = rockchip_dfi_event_ready,
    .read = rockchip_dfi_event_read,
    .enable = rockchip_dfi_event_enable,
    .disable = rockchip_dfi_event_disable,
};

static rt_err_t rockchip_px30_dfi_init(struct rockchip_dfi *dfi,
        struct rt_ofw_node *np)
{
    rt_uint32_t val_2 = 0, val_3 = 0;

    dfi->pmugrf = rt_syscon_find_by_ofw_phandle(np, "rockchip,pmugrf");
    if (!dfi->pmugrf)
    {
        return -RT_ENOENT;
    }

    rt_syscon_read(dfi->pmugrf, PX30_PMUGRF_OS_REG2, &val_2);
    rt_syscon_read(dfi->pmugrf, PX30_PMUGRF_OS_REG3, &val_3);

    if (READ_SYSREG_VERSION(val_3) >= 0x3)
    {
        dfi->dram_type = READ_DRAMTYPE_INFO_V3(val_2, val_3);
    }
    else
    {
        dfi->dram_type = READ_DRAMTYPE_INFO(val_2);
    }

    dfi->ch_msk = 1;
    dfi->count_rate = 1;

    return RT_EOK;
}

static rt_err_t rockchip_dfi_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rockchip_dfi *dfi;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node;
    const struct rt_ofw_node_id *match;

    if (!(dfi = rt_calloc(1, sizeof(*dfi))))
    {
        return -RT_ENOMEM;
    }

    dfi->pdev = pdev;
    dfi->event.dev = dev;
    dfi->event.ops = &rockchip_dfi_event_ops;
    dfi->event.priv = dfi;

    if (!(dfi->regs = rt_dm_dev_iomap(dev, 0)))
    {
        err = -RT_EIO;
        goto _fail;
    }

    match = pdev->id;
    if (match && match->data)
    {
        err = ((rt_err_t (*)(struct rockchip_dfi *, struct rt_ofw_node *))match->data)(dfi, np);
        if (err)
        {
            goto _fail;
        }
    }
    else
    {
        err = -RT_ENOSYS;
        goto _fail;
    }

    rt_dm_dev_set_name_auto(dev, "dfi");

    if ((err = rt_device_register(dev, rt_dm_dev_get_name(dev), RT_DEVICE_FLAG_DEACTIVATE)))
    {
        goto _fail;
    }

    if ((err = rt_dvfs_event_register(&dfi->event)))
    {
        goto _fail_dev;
    }

    pdev->priv = dfi;

    LOG_I("%s: dram_type=%u ch_msk=0x%x", rt_dm_dev_get_name(dev),
          dfi->dram_type, dfi->ch_msk);

    return RT_EOK;

_fail_dev:
    rt_device_unregister(dev);
_fail:
    if (dfi)
    {
        rt_free(dfi);
    }
    return err;
}

static rt_err_t rockchip_dfi_remove(struct rt_platform_device *pdev)
{
    struct rockchip_dfi *dfi = pdev->priv;

    if (!dfi)
    {
        return RT_EOK;
    }

    rt_dvfs_event_unregister(&dfi->event);
    rt_bus_remove_device(&dfi->pdev->parent);
    rt_free(dfi);
    pdev->priv = RT_NULL;

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_dfi_ofw_ids[] =
{
    { .compatible = "rockchip,rk3568-dfi", .data = rockchip_px30_dfi_init },
    { .compatible = "rockchip,rk3562-dfi", .data = rockchip_px30_dfi_init },
    { .compatible = "rockchip,px30-dfi", .data = rockchip_px30_dfi_init },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_dfi_driver =
{
    .name = "rockchip-dfi",
    .ids = rockchip_dfi_ofw_ids,
    .probe = rockchip_dfi_probe,
    .remove = rockchip_dfi_remove,
};

static int rockchip_dfi_driver_register(void)
{
    rt_platform_driver_register(&rockchip_dfi_driver);

    return 0;
}
INIT_PLATFORM_EXPORT(rockchip_dfi_driver_register);

#ifdef RT_USING_FINSH
#include <finsh.h>

static struct rt_dvfs_event *dfi_event_get(const char *name)
{
    struct rt_device *dev = rt_device_find(name);

    if (!dev || !dev->ofw_node)
    {
        return RT_NULL;
    }

    return rt_ofw_data(dev->ofw_node);
}

static int dfi_read(int argc, char **argv)
{
    struct rt_dvfs_event *ev;
    struct rt_dvfs_event_data evd;
    rt_err_t err;

    if (argc != 2)
    {
        rt_kprintf("Usage: dfi_read <device name>\n");
        return -1;
    }

    if (!(ev = dfi_event_get(argv[1])))
    {
        rt_kprintf("dfi device not found\n");
        return -1;
    }

    if ((err = rt_dvfs_event_enable(ev)))
    {
        rt_kprintf("enable failed: %s\n", rt_strerror(err));
        return -1;
    }

    err = rt_dvfs_event_read(ev, &evd);
    if (err)
    {
        rt_kprintf("read failed: %s\n", rt_strerror(err));
        rt_dvfs_event_disable(ev);
        return -1;
    }

    if (evd.total_count)
    {
        rt_uint64_t load_p = evd.load_count * 100000000ULL / evd.total_count;
        rt_uint32_t load_int = (rt_uint32_t)(load_p / 1000000ULL);
        rt_uint32_t load_frac = (rt_uint32_t)(load_p % 1000000ULL);

        rt_kprintf("load_count=%lu total_count=%lu load=%u.%06u%%\n",
                (unsigned long)evd.load_count,
                (unsigned long)evd.total_count,
                load_int, load_frac);
    }
    else
    {
        rt_kprintf("load_count=%lu total_count=%lu load=0%%\n",
                (unsigned long)evd.load_count,
                (unsigned long)evd.total_count);
    }

    return 0;
}
MSH_CMD_EXPORT(dfi_read, read rockchip DFI devfreq-event counters);
#endif /* RT_USING_FINSH */
