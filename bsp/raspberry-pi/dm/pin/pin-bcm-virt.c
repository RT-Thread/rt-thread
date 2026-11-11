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

#include <firmware-raspberrypi.h>

#include "dev_pin_dm.h"

#define NUM_GPIO 2

struct brcmvirt_gpio
{
    struct rt_device_pin parent;
    rt_uint32_t *ts_base;

    rt_uint32_t enables_disables[NUM_GPIO];
    rt_ubase_t bus_addr;
};

#define raw_to_brcmvirt_gpio(raw) rt_container_of(raw, struct brcmvirt_gpio, parent)

static void brcmvirt_gpio_mode(struct rt_device *device, rt_base_t pin, rt_uint8_t mode)
{
}

static void brcmvirt_gpio_write(struct rt_device *device, rt_base_t pin, rt_uint8_t value)
{
    rt_bool_t lit;
    rt_uint16_t enables, disables;
    struct brcmvirt_gpio *gpio = raw_to_brcmvirt_gpio(device);

    enables = gpio->enables_disables[pin] >> 16;
    disables = gpio->enables_disables[pin] >>  0;
    lit = (rt_int16_t)(enables - disables) > 0;

    if ((value && lit) || (!value && !lit))
    {
        return;
    }

    if (value)
    {
        enables++;
    }
    else
    {
        disables++;
    }

    gpio->enables_disables[pin] = (enables << 16) | (disables << 0);
    HWREG32(gpio->ts_base + pin) = gpio->enables_disables[pin];
}

static rt_ssize_t brcmvirt_gpio_read(struct rt_device *device, rt_base_t pin)
{
    rt_uint32_t value;
    struct brcmvirt_gpio *gpio = raw_to_brcmvirt_gpio(device);

    value = HWREG32(gpio->ts_base + pin);

    return (rt_int16_t)((value >> 16) - value) > 0;
}

static const struct rt_pin_ops brcmvirt_gpio_ops =
{
    .pin_mode = brcmvirt_gpio_mode,
    .pin_write = brcmvirt_gpio_write,
    .pin_read = brcmvirt_gpio_read,
};

static rt_err_t brcmvirt_gpio_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    void *ts_base;
    rt_uint32_t virtbuf;
    struct rpi_firmware *rpi_fw = RT_NULL;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *fw_np;
    struct brcmvirt_gpio *gpio = rt_calloc(1, sizeof(*gpio));

    if (!gpio)
    {
        return -RT_ENOMEM;
    }

    fw_np = rt_ofw_parse_phandle(np, "firmware", 0);

    if (!fw_np)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    rpi_fw = rpi_firmware_get(fw_np);
    rt_ofw_node_put(fw_np);

    if (!rpi_fw)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    ts_base = rt_dma_alloc_coherent(dev, ARCH_PAGE_SIZE, &gpio->bus_addr);

    if (!ts_base)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    virtbuf = (rt_uint32_t)gpio->bus_addr;
    err = rpi_firmware_property(rpi_fw,
            RPI_FIRMWARE_FRAMEBUFFER_SET_GPIOVIRTBUF, &gpio->bus_addr, sizeof(virtbuf));

    if (err)
    {
        goto _fail;
    }

    err = rpi_firmware_property(rpi_fw,
            RPI_FIRMWARE_FRAMEBUFFER_GET_GPIOVIRTBUF, &virtbuf, sizeof(virtbuf));

    if (err)
    {
        goto _fail;
    }

    virtbuf &= ~0xc0000000;
    gpio->ts_base = rt_ioremap((void *)(rt_ubase_t)virtbuf, ARCH_PAGE_SIZE);

    if (!gpio->ts_base)
    {
        goto _fail;
    }

    rt_dm_dev_bind_fwdata(dev, RT_NULL, &gpio->parent);

    gpio->parent.ops = &brcmvirt_gpio_ops;
    pin_api_init(&gpio->parent, NUM_GPIO);

    return RT_EOK;

_fail:
    if (gpio->bus_addr)
    {
        rt_dma_free_coherent(dev, ARCH_PAGE_SIZE, ts_base, gpio->bus_addr);
    }

    if (rpi_fw)
    {
        rpi_firmware_put(rpi_fw);
    }

    rt_free(gpio);

    return err;
}

static const struct rt_ofw_node_id brcmvirt_gpio_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-virtgpio" },
    { /* sentinel */ }
};

static struct rt_platform_driver brcmvirt_gpio_driver =
{
    .name = "brcmvirt-gpio",
    .ids = brcmvirt_gpio_ofw_ids,

    .probe = brcmvirt_gpio_probe,
};

static int brcmvirt_gpio_drv_register(void)
{
    rt_platform_driver_register(&brcmvirt_gpio_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(brcmvirt_gpio_drv_register);
