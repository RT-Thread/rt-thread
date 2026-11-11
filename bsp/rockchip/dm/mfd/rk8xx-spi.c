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

#define DBG_TAG "mfd.rk8xx-spi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rk8xx.h"

#define RK806_CMD_PACKAGE(CMD, LEN) \
        (RK806_CMD_##CMD | RK806_CMD_CRC_DIS | (LEN & RK806_CMD_LEN_MSK))

/*
 * Format of SPI commands (3 data packages: CMD, REG_L, REG_H)
 *  CMD R/W[7]: R=0, W=1
 *  CMD CRC_EN[6]: Enable=1, Disable=0
 *  CMD Len[3:0]:
 *      case 1: CRC_EN=1
 *          The length of data written or read is noted in Len[3:0].
 *          The host or slave computer transmits CRC data at the position of len+1.
 *      case 2: CRC_EN=0
 *          The data transmission takes no advantage of the length.
 *          The addresses of registers of slave computer self-increase within the interval of 0~255.
 *
 *  REG_L[7:0]: The address of the target register is low-8 bit.
 *  REG_H[15:8]: The address of the target register is high-8 bit.
 */

static rt_uint32_t rk8xx_spi_read(struct rk8xx *rk8xx, rt_uint16_t reg)
{
    rt_err_t err;
    rt_uint8_t data = 0, package[3];
    struct rt_spi_device *spi_dev = rk8xx_to_spi_device(rk8xx);

    package[0] = RK806_CMD_PACKAGE(READ, sizeof(data));
    package[1] = reg & 0xff;
    package[2] = (reg >> 8) & 0xff;

    err = rt_spi_send_then_recv(spi_dev, package, sizeof(package),
            &data, sizeof(data));

    return !err ? data : (rt_uint32_t)err;
}

static rt_err_t rk8xx_spi_write(struct rk8xx *rk8xx, rt_uint16_t reg,
        rt_uint8_t data)
{
    rt_ssize_t res;
    rt_uint8_t package[4];
    struct rt_spi_device *spi_dev = rk8xx_to_spi_device(rk8xx);

    package[0] = RK806_CMD_PACKAGE(WRITE, sizeof(data));
    package[1] = reg & 0xff;
    package[2] = (reg >> 8) & 0xff;
    package[3] = data;

    res = rt_spi_transfer(spi_dev, package, RT_NULL, sizeof(package));

    return res > 0 ? RT_EOK : (res == 0 ? -RT_EIO : res);
}

static rt_err_t rk8xx_spi_update_bits(struct rk8xx *rk8xx, rt_uint16_t reg,
        rt_uint8_t mask, rt_uint8_t data)
{
    rt_uint32_t old, tmp;

    old = rk8xx_spi_read(rk8xx, reg);

    if ((rt_err_t)old < 0)
    {
        return old;
    }

    tmp = old & ~mask;
    tmp |= (data & mask);

    return rk8xx_spi_write(rk8xx, reg, tmp);
}

static rt_err_t rk8xx_spi_probe(struct rt_spi_device *spi_dev)
{
    rt_err_t err;
    struct rk8xx *rk8xx = rt_calloc(1, sizeof(*rk8xx));

    if (!rk8xx)
    {
        return -RT_ENOMEM;
    }

    rk8xx->irq = rt_dm_dev_get_irq(&spi_dev->parent, 0);

    if (rk8xx->irq < 0)
    {
        err = rk8xx->irq;
        goto _fail;
    }

    rk8xx->variant = RK806_ID;
    rk8xx->dev = &spi_dev->parent;
    rk8xx->read = rk8xx_spi_read;
    rk8xx->write = rk8xx_spi_write;
    rk8xx->update_bits = rk8xx_spi_update_bits;

    if ((err = rk8xx_probe(rk8xx)))
    {
        goto _fail;
    }

    rt_dm_dev_set_name(&spi_dev->parent, "pmic");

    return RT_EOK;

_fail:
    rt_free(rk8xx);

    return err;
}

static const struct rt_spi_device_id rk8xx_spi_ids[] =
{
    { .name = "rk806" },
    { /* sentinel */ },
};

static const struct rt_ofw_node_id rk8xx_spi_ofw_ids[] =
{
    { .compatible = "rockchip,rk806" },
    { /* sentinel */ },
};

static struct rt_spi_driver rk8xx_spi_driver =
{
    .ids = rk8xx_spi_ids,
    .ofw_ids = rk8xx_spi_ofw_ids,

    .probe = rk8xx_spi_probe,
};
RT_SPI_DRIVER_EXPORT(rk8xx_spi_driver);
