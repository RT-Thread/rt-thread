/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "soc.info"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct spacemit_soc_info
{
    rt_uint32_t die_id;     /* Die/wafer id */
    rt_uint32_t ver_id;     /* Die/wafer version */
    rt_uint32_t pack_id;    /* Package id */
    rt_uint32_t svtdro;     /* Dro vaule */
    rt_uint64_t chipid;     /* Chip serial number */
    rt_uint32_t soc_id;     /* SoC id */
    char *name;             /* Chip name */
};

struct spacemit_soc_id
{
    const char *name;
    rt_uint32_t id;
};

static const struct spacemit_soc_id soc_ids[] =
{
    { "unknown", 0x00000000 },
    /* k1 serial soc */
    { "M1-8571", 0x36070000 },
    { "K1-6370", 0x36070009 },
    { "K1-6350", 0x36070012 },
    { "K1-6371", 0x36070040 },
    { "M103-6370", 0x36070109 },
    { "M103-6371", 0x36070140 },
};

static const char *soc_id_to_chip_name(rt_uint32_t die_id, rt_uint32_t ver_id, rt_uint32_t pack_id)
{
    rt_uint32_t soc_id = (die_id << 16) | (pack_id);

    for (int i = 0; i < RT_ARRAY_SIZE(soc_ids); ++i)
    {
        if (soc_id == soc_ids[i].id)
        {
            return soc_ids[i].name;
        }
    }

    /* The soc id is unkown */
    return soc_ids[0].name;
}

static rt_ssize_t socinfo_get_nvparam(struct rt_device *dev, char *cell_name, void *val, rt_size_t size)
{
    rt_ssize_t res;
    struct rt_nvmem_cell *cell;

    cell = rt_nvmem_get_cell_by_name(dev, cell_name);
    if (rt_is_err(cell))
    {
        LOG_E("NVMEM cell get %s failed", cell_name);
        return rt_ptr_err(cell);
    }

    res = rt_nvmem_cell_read(cell, val, rt_min_t(rt_size_t, cell->bytes, size));
    if (res < 0)
    {
        LOG_E("NVMEM cell read %s failed", cell_name);
        goto _end;
    }

_end:
    rt_nvmem_put_cell(cell);

    return res;
}

static rt_err_t spacemit_socinfo_probe(struct rt_platform_device *pdev)
{
    rt_ssize_t res;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_soc_info socinfo;

    if ((res = socinfo_get_nvparam(dev, "soc_die_id",
        &socinfo.die_id, sizeof(socinfo.die_id))) <= 0)
    {
        LOG_E("Try to get soc_%s from efuse failed", "die_id");
    }

    if ((res = socinfo_get_nvparam(dev, "soc_ver_id",
        &socinfo.ver_id, sizeof(socinfo.ver_id))) <= 0)
    {
        LOG_E("Try to get soc_%s from efuse failed", "ver_id");
    }

    if ((res = socinfo_get_nvparam(dev, "soc_pack_id",
        &socinfo.pack_id, sizeof(socinfo.pack_id))) <= 0)
    {
        LOG_E("Try to get soc_%s from efuse failed", "pack_id");
    }

    if ((res = socinfo_get_nvparam(dev, "soc_svt_dro",
        &socinfo.svtdro, sizeof(socinfo.svtdro))) <= 0)
    {
        LOG_E("Try to get soc_%s from efuse failed", "svt_dro");
    }

    if ((res = socinfo_get_nvparam(dev, "soc_chip_id",
        &socinfo.chipid, sizeof(socinfo.chipid))) <= 0)
    {
        LOG_E("Try to get soc_%s from efuse failed", "chip_id");
    }

    socinfo.soc_id = (socinfo.die_id << 16) | socinfo.pack_id;

    LOG_I("Revision : %c", (socinfo.ver_id + 'A') & 0xff);
    LOG_I("ID       : %s", soc_id_to_chip_name(socinfo.die_id, socinfo.ver_id, socinfo.pack_id));
    LOG_I("Serial No: %016llX", socinfo.chipid);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_socinfo_ofw_ids[] =
{
    { .compatible = "spacemit,socinfo-k1x" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_socinfo_driver =
{
    .name = "spacemit-socinfo",
    .ids = spacemit_socinfo_ofw_ids,

    .probe = spacemit_socinfo_probe,
};
RT_PLATFORM_DRIVER_EXPORT(spacemit_socinfo_driver);
