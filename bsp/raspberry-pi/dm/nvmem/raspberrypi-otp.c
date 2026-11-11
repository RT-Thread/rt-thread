/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "nvmem.raspberrypi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <firmware-raspberrypi.h>

#define MAX_ROWS 192

struct rpi_otp
{
    struct rt_nvmem_device parent;

    struct rpi_firmware *fw;
    rt_uint32_t block;
};

#define raw_to_rpi_otp(raw) rt_container_of(raw, struct rpi_otp, parent)

static rt_ssize_t rpi_otp_read(struct rt_nvmem_device *ndev, int offset,
        void *val, rt_size_t bytes)
{
    rt_err_t err;
    int words, index;
    rt_uint32_t data[3 + MAX_ROWS];
    struct rpi_otp *otp = raw_to_rpi_otp(ndev);

    words = bytes / sizeof(rt_uint32_t);
    index = offset / sizeof(rt_uint32_t);
    data[0] = otp->block;
    data[1] = index;
    data[2] = words;

    if (words > MAX_ROWS)
    {
        return -RT_EINVAL;
    }

    err = rpi_firmware_property(otp->fw, RPI_FIRMWARE_GET_USER_OTP, &data, sizeof(data));

    if (!err)
    {
        rt_memcpy(val, data + 3, bytes);
    }
    else
    {
        rt_memset(val, 0xee, bytes);
    }

    return err ? : bytes;
}

static rt_ssize_t rpi_otp_write(struct rt_nvmem_device *ndev, int offset,
        void *val, rt_size_t bytes)
{
    int words, index;
    rt_uint32_t data[3 + MAX_ROWS];
    struct rpi_otp *otp = raw_to_rpi_otp(ndev);

    words = bytes / sizeof(rt_uint32_t);
    index = offset / sizeof(rt_uint32_t);
    data[0] = otp->block;
    data[1] = index;
    data[2] = words;

    if (bytes > MAX_ROWS * sizeof(rt_uint32_t))
    {
        return -RT_EINVAL;
    }

    rt_memcpy(data + 3, val, bytes);

    return rpi_firmware_property(otp->fw, RPI_FIRMWARE_SET_USER_OTP, &data, sizeof(data)) ? : bytes;
}

static rt_err_t rpi_otp_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t reg[2];
    struct rt_nvmem_device *nvmem;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *fw_np;
    struct rpi_otp *otp = rt_calloc(1, sizeof(*otp));

    if (!otp)
    {
        return -RT_ENOMEM;
    }

    fw_np = rt_ofw_parse_phandle(np, "firmware", 0);

    if (!fw_np)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    otp->fw = rpi_firmware_get(fw_np);
    rt_ofw_node_put(fw_np);

    if (!otp->fw)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if (rt_dm_dev_prop_read_u32_array_index(dev, "reg", 0, RT_ARRAY_SIZE(reg), reg) <= 0)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    nvmem = &otp->parent;
    nvmem->parent.ofw_node = np;
    nvmem->reg_read = rpi_otp_read,
    nvmem->reg_write = rpi_otp_write,
    nvmem->size = reg[1] * sizeof(rt_uint32_t);
    nvmem->read_only = !rt_dm_dev_prop_read_bool(dev, "rw");
    nvmem->stride = sizeof(rt_uint32_t);
    nvmem->word_size = sizeof(rt_uint32_t);

    if ((err = rt_nvmem_device_register(nvmem)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (otp->fw)
    {
        rpi_firmware_put(otp->fw);
    }

    rt_free(otp);

    return err;
}

static rt_err_t rpi_otp_remove(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rpi_otp *otp = pdev->parent.user_data;

    err = rt_nvmem_device_unregister(&otp->parent);

    rpi_firmware_put(otp->fw);

    rt_free(otp);

    return err;
}

static const struct rt_ofw_node_id rpi_top_ofw_ids[] =
{
    { .compatible = "raspberrypi,rpi-otp", },
    { /* sentinel */ }
};

static struct rt_platform_driver rpi_top_driver =
{
    .name = "nvmem-raspberrypi-otp",
    .ids = rpi_top_ofw_ids,

    .probe = rpi_otp_probe,
    .remove = rpi_otp_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rpi_top_driver);
