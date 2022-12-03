/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2021-12-15     JasonHu         first version
 */

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#include "drv_spi.h"

#define DBG_TAG     "DRV.SPI"
#define DBG_LVL     DBG_LOG
#include <rtdbg.h>
#include <sunxi_hal_spi.h>

#ifdef BSP_USING_SPI

struct hw_spi_bus
{
    struct rt_spi_bus parent;
    hal_spi_master_port_t port;
};

#define BSP_SPI_MAX_HZ         SPI_MAX_FREQUENCY

#if defined (BSP_USING_SPI0)
#define SPI0_BUS_NAME      "spi0"
#define SPI0_BUS_DEVICE0_NAME      "spi01"

struct hw_spi_bus spi0_bus;

#endif /* BSP_USING_SPI0 */

#if defined (BSP_USING_SPI1)
#define SPI1_BUS_NAME      "spi1"
#define SPI1_BUS_DEVICE0_NAME      "spi11"

struct hw_spi_bus spi1_bus;

#endif /* BSP_USING_SPI1 */

static rt_err_t hw_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *cfg)
{
    RT_ASSERT(cfg != RT_NULL);
    RT_ASSERT(device != RT_NULL);

    struct hw_spi_bus *spi_dev = RT_NULL;
    hal_spi_master_config_t hal_cfg;

    LOG_D("configure mode:%x, clk:%d\n", cfg->mode, cfg->max_hz);

    /* trans cfg to hal cfg */
    spi_dev = (struct hw_spi_bus *)(device->parent.user_data);

    if (cfg->max_hz > BSP_SPI_MAX_HZ)
        cfg->max_hz = BSP_SPI_MAX_HZ;

    /* set default frequency */
    hal_cfg.clock_frequency = cfg->max_hz;
    hal_cfg.slave_port = HAL_SPI_MASTER_SLAVE_0; /* only support slave 0 */

    /* byte order */
    if (cfg->mode & RT_SPI_MSB)
    {
        hal_cfg.bit_order = HAL_SPI_MASTER_MSB_FIRST;
    }
    else
    {
        hal_cfg.bit_order = HAL_SPI_MASTER_LSB_FIRST;
    }

    if(cfg->mode & RT_SPI_CPOL)
    {
        hal_cfg.cpol = HAL_SPI_MASTER_CLOCK_POLARITY1;
    }
    else
    {
        hal_cfg.cpol = HAL_SPI_MASTER_CLOCK_POLARITY0;
    }

    if(cfg->mode & RT_SPI_CPHA)
    {
        hal_cfg.cpha = HAL_SPI_MASTER_CLOCK_PHASE1;
    }
    else
    {
        hal_cfg.cpha = HAL_SPI_MASTER_CLOCK_PHASE0;
    }

    if (cfg->mode & RT_SPI_NO_CS)
    {
        hal_cfg.csmode = HAL_SPI_MASTER_CS_AUTO;
    }
    else
    {
        hal_cfg.csmode = HAL_SPI_MASTER_CS_SOFT;
    }

    if (hal_spi_hw_config(spi_dev->port, &hal_cfg) != SPI_MASTER_OK)
    {
        return -RT_EIO;
    }

    return RT_EOK;
}

static rt_uint32_t hw_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    spi_master_status_t ret = SPI_MASTER_OK;
    hal_spi_master_transfer_t tr;
    struct hw_spi_bus *spi_dev = RT_NULL;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->bus != RT_NULL);
    RT_ASSERT(device->parent.user_data != RT_NULL);

    spi_dev = (struct hw_spi_bus *)(device->parent.user_data);

    tr.rx_buf = message->recv_buf;
    tr.rx_len = message->recv_buf == RT_NULL ? 0 : message->length;
    tr.tx_buf = message->send_buf;
    tr.tx_len = message->send_buf == RT_NULL ? 0 : message->length;
    tr.dummy_byte = 0;
    tr.tx_single_len = message->send_buf == RT_NULL ? 0 : message->length;
    tr.rx_nbits = SPI_NBITS_SINGLE;
    tr.tx_nbits = SPI_NBITS_SINGLE;

    if (message->cs_take && !(device->config.mode & RT_SPI_NO_CS))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
        {
            hal_spi_cs(spi_dev->port, 1);
        }
        else
        {
            hal_spi_cs(spi_dev->port, 0);
        }
    }

    if (message->length > 0)
    {
        ret = hal_spi_xfer(spi_dev->port, &tr);
    }

    // FIXME: GCC O3 maybe not execute.
    if (message->cs_release && !(device->config.mode & RT_SPI_NO_CS))
    {
        if (device->config.mode & RT_SPI_CS_HIGH)
        {
            hal_spi_cs(spi_dev->port, 0);
        }
        else
        {
            hal_spi_cs(spi_dev->port, 1);
        }
    }

    if (ret != SPI_MASTER_OK)
    {
        LOG_E("xfer err ret:%ld", ret);
        return -RT_EIO;
    }

    return message->length;
}

/**
 * attach a spi device on bus
 */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name)
{
    rt_err_t ret = RT_EOK;
    struct hw_spi_bus *hw_spi = RT_NULL;

    struct rt_spi_device *spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device));
    RT_ASSERT(spi_device != RT_NULL);
#ifdef BSP_USING_SPI0
    if (!rt_strcmp(bus_name, SPI0_BUS_NAME))
    {
        hw_spi = &spi0_bus;
    }
    else
#endif
#ifdef BSP_USING_SPI1
    if (!rt_strcmp(bus_name, SPI0_BUS_NAME))
    {
        hw_spi = &spi1_bus;
    }
    else
#endif
    {
        return -RT_EIO;
    }
    /* TODO: attach device */
    ret = rt_spi_bus_attach_device(spi_device, device_name, bus_name, hw_spi);
    return ret;
}

static struct rt_spi_ops hw_spi_ops =
{
    .configure = hw_spi_configure,
    .xfer = hw_spi_xfer
};

#endif /* BSP_USING_SPI */

/* used to init spi bus */
static hal_spi_master_config_t default_hal_cfg = {
    .bit_order = HAL_SPI_MASTER_MSB_FIRST,
    .clock_frequency = 5000000,//SPI_MOD_CLK,
    .cpha = HAL_SPI_MASTER_CLOCK_PHASE0,
    .cpol = HAL_SPI_MASTER_CLOCK_POLARITY0,
    .slave_port = HAL_SPI_MASTER_SLAVE_0,
    .csmode = HAL_SPI_MASTER_CS_SOFT,
};

int rt_hw_spi_init(void)
{
#if defined (BSP_USING_SPI0)
    spi0_bus.port = HAL_SPI_MASTER_0;
    if (hal_spi_init(spi0_bus.port, &default_hal_cfg) != SPI_MASTER_OK)
    {
        LOG_E("hal init %s bus failed!", SPI0_BUS_NAME);
        return -1;
    }
    rt_spi_bus_register(&spi0_bus.parent, SPI0_BUS_NAME, &hw_spi_ops);

    rt_hw_spi_device_attach(SPI0_BUS_NAME, SPI0_BUS_DEVICE0_NAME);
#endif /* BSP_USING_SPI0 */

#if defined (BSP_USING_SPI1)
    spi1_bus.port = HAL_SPI_MASTER_1;
    if (hal_spi_init(spi1_bus.port, &default_hal_cfg) != SPI_MASTER_OK)
    {
        LOG_E("hal init %s bus failed!", SPI1_BUS_NAME);
        return -1;
    }
    rt_spi_bus_register(&spi1_bus.parent, SPI1_BUS_NAME, &hw_spi_ops);
    rt_hw_spi_device_attach(SPI1_BUS_NAME, SPI1_BUS_DEVICE0_NAME);

#endif /* BSP_USING_SPI1 */
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spi_init);

#define CFG_GPIO_PORT(p) ((p) - 'A' + 1)

int32_t hal_spi_gpio_cfg_count(const char *secname)
{
    return 4;
}

static const user_gpio_set_t _spi_gpio_cfg[][4] = {
    {// spi0
        {
            .gpio_name = "spi0_sclk",
            .port = CFG_GPIO_PORT('C'),
            .port_num = 2, // PC02
            .mul_sel = 2,
            .pull = 0, // no pull
            .drv_level = 3,
            .data = 0,
        },
        {
            .gpio_name = "spi0_cs",
            .port = CFG_GPIO_PORT('C'),
            .port_num = 3, // PC03
            .mul_sel = 2,
            .pull = 1, // pull up
            .drv_level = 3,
            .data = 0,
        },
        {
            .gpio_name = "spi0_mosi",
            .port = CFG_GPIO_PORT('C'),
            .port_num = 4, // PC04
            .mul_sel = 2,
            .pull = 0, // no pull
            .drv_level = 3,
            .data = 0,
        },
        {
            .gpio_name = "spi0_miso",
            .port = CFG_GPIO_PORT('C'),
            .port_num = 5, // PC05
            .mul_sel = 2,
            .pull = 0, // no pull
            .drv_level = 3,
            .data = 0,
        }
    },
};

int hal_spi_gpio_cfg_load(user_gpio_set_t *gpio_cfg, int32_t GPIONum, int id)
{
    int i;

    if (id > sizeof(_spi_gpio_cfg) / sizeof(_spi_gpio_cfg[0]))
    {
        rt_kprintf("spi id %d>%d\n", id, sizeof(_spi_gpio_cfg) / sizeof(_spi_gpio_cfg[0]));
        return -1;
    }

    /* twi0 */
    for (i = 0; i < GPIONum; i++)
    {
        memcpy(gpio_cfg, &_spi_gpio_cfg[id][i], sizeof(user_gpio_set_t));
        gpio_cfg++;
    }

    return 0;
}

/*
 * 程序清单：这是一个 SPI 设备使用例程
 * 例程导出了 spi_w25q_sample 命令到控制终端
 * 命令调用格式：spi_w25q_sample spi10
 * 命令解释：命令第二个参数是要使用的SPI设备名称，为空则使用默认的SPI设备
 * 程序功能：通过SPI设备读取 w25q 的 ID 数据
*/

#include <rtthread.h>
#include <rtdevice.h>

#define SPI_DEVICE_NAME     "spi01"

static void spi_sample(int argc, char *argv[])
{
    struct rt_spi_device *spi_dev;
    static char cmd[200];
    static char recv_data[200];
    rt_uint8_t id[5] = {0};
    int i;
    rt_err_t err;
    int type;

    type = atoi(argv[1]);

    for (i = 0; i < sizeof(cmd); i++)
    {
        cmd[i] = i + 1;
    }

    /* 查找 spi 设备获取设备句柄 */
    spi_dev = (struct rt_spi_device *)rt_device_find(SPI_DEVICE_NAME);
    if (!spi_dev)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n", SPI_DEVICE_NAME);
    }
    else
    {
        struct rt_spi_configuration spi_cfg;
        spi_cfg.max_hz = 5000000;
        spi_cfg.mode = RT_SPI_MODE_0 | RT_SPI_MSB;
        spi_cfg.data_width = 8;

        rt_spi_configure(spi_dev, &spi_cfg);
        if (type == 1)
        {
            err = rt_spi_transfer(spi_dev, cmd, recv_data, sizeof(recv_data));
        }
        else if (type == 2)
        {
            err = rt_spi_send_then_recv(spi_dev, cmd, sizeof(cmd), recv_data, sizeof(recv_data));
        }
        else if (type == 3)
        {
            err = rt_spi_send(spi_dev, cmd, sizeof(cmd));
        }
        else if (type == 4)
        {
            err = rt_spi_send_then_send(spi_dev, cmd, sizeof(cmd), cmd, sizeof(cmd));
        }
        else if (type == 5)
        {
            err = rt_spi_recv(spi_dev, recv_data, sizeof(recv_data));
        }
        // err = rt_spi_send(spi_dev, cmd, sizeof(cmd));
        if (err != sizeof(cmd))
        {
            rt_kprintf("spi send error:%d\n", err);
        }
    }
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(spi_sample, spi w25q sample);
