/*
 * Copyright (c) 2021 - 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2022-01-11   hpmicro     First version
 */

#include "rtthread.h"

#ifdef RT_USING_PHY
#include <rtdevice.h>
#include <rtdbg.h>
#include "hpm_enet_drv.h"
#include "eth_phy_port.h"
#include "hpm_soc.h"
#include "netif/ethernetif.h"
#include "board.h"

typedef struct
{
    char *mdio_name;
    ENET_Type *instance;
    struct eth_device *eth_dev;
    phy_device_t *phy_dev;
    struct rt_mdio_bus *mdio_bus;
} eth_phy_handle_t;

typedef struct
{
    uint8_t phy_handle_cnt;
    eth_phy_handle_t **phy_handle;
} eth_phy_monitor_handle_t;

#ifdef BSP_USING_ETH0
extern struct eth_device eth0_dev;
static struct rt_mdio_bus mdio0_bus;
static phy_device_t phy0_dev;
static uint8_t phy0_reg_list[]= {PHY0_REG_LIST};

static eth_phy_handle_t eth0_phy_handle =
{
    .instance  = HPM_ENET0,
    .eth_dev   = &eth0_dev,
    .phy_dev   = &phy0_dev,
    .mdio_name = "MDIO0",
    .mdio_bus  = &mdio0_bus,
};
#endif

#ifdef BSP_USING_ETH1
extern struct eth_device eth1_dev;
static struct rt_mdio_bus mdio1_bus;
static phy_device_t phy1_dev;
static uint8_t phy1_reg_list[]= {PHY1_REG_LIST};

static eth_phy_handle_t eth1_phy_handle =
{
    .instance     = HPM_ENET1,
    .eth_dev      = &eth1_dev,
    .phy_dev      = &phy1_dev,
    .mdio_name    = "MDIO1",
    .mdio_bus     = &mdio1_bus,
};
#endif

static eth_phy_handle_t *s_gphys[] =
{
#ifdef BSP_USING_ETH0
&eth0_phy_handle,
#endif

#ifdef BSP_USING_ETH1
&eth1_phy_handle
#endif
};

static uint8_t *s_gphy_reg_list[] =
{
#ifdef BSP_USING_ETH0
phy0_reg_list,
#endif

#ifdef BSP_USING_ETH1
phy1_reg_list,
#endif
};

eth_phy_monitor_handle_t phy_monitor_handle =
{
    .phy_handle_cnt = ARRAY_SIZE(s_gphys),
    .phy_handle     = s_gphys
};

static struct rt_phy_ops phy_ops;

static rt_phy_status phy_init(void *object, rt_uint32_t phy_addr, rt_uint32_t src_clock_hz)
{
    return PHY_STATUS_OK;
}

static rt_size_t phy_read(void *bus, rt_uint32_t addr, rt_uint32_t reg, void *data, rt_uint32_t size)
{
    *(uint16_t *)data = enet_read_phy(((struct rt_mdio_bus *)bus)->hw_obj, addr, reg);

    return size;
}

static rt_size_t phy_write(void *bus, rt_uint32_t addr, rt_uint32_t reg, void *data, rt_uint32_t size)
{
    enet_write_phy(((struct rt_mdio_bus *)bus)->hw_obj, addr, reg,  *(uint16_t *)data);

    return size;
}

static rt_phy_status phy_get_link_status(rt_phy_t *phy, rt_bool_t *status)
{
    uint16_t reg_status;

    reg_status = enet_read_phy(phy->bus->hw_obj, phy->addr, phy->reg_list[PHY_BASIC_STATUS_REG_IDX]);

    #if PHY_AUTO_NEGO
        reg_status &= PHY_AUTONEGO_COMPLETE_MASK | PHY_LINKED_STATUS_MASK;
        *status = reg_status ? RT_TRUE : RT_FALSE;

    #else
        reg_status &= PHY_LINKED_STATUS_MASK;
        *status = reg_status ? RT_TRUE : RT_FALSE;
    #endif

    return PHY_STATUS_OK;
}

static rt_phy_status phy_get_link_speed_duplex(rt_phy_t *phy, rt_uint32_t *speed, rt_uint32_t *duplex)
{
    uint16_t reg_status;

    reg_status = enet_read_phy(phy->bus->hw_obj, phy->addr, phy->reg_list[PHY_STATUS_REG_IDX]);

    *speed = PHY_STATUS_SPEED_100M(reg_status) ? PHY_SPEED_100M : PHY_SPEED_10M;
    *duplex = PHY_STATUS_FULL_DUPLEX(reg_status) ? PHY_FULL_DUPLEX: PHY_HALF_DUPLEX;

    return PHY_STATUS_OK;
}

static void phy_poll_status(void *parameter)
{
    int ret;
    phy_info_t phy_info;
    rt_bool_t status;
    rt_device_t dev;
    rt_phy_msg_t msg;
    rt_uint32_t speed, duplex;
    phy_device_t *phy_dev;
    struct eth_device* eth_dev;
    char const *ps[] = {"10Mbps", "100Mbps", "1000Mbps"};
    enet_line_speed_t line_speed[] = {enet_line_speed_10mbps, enet_line_speed_100mbps, enet_line_speed_1000mbps};

    eth_phy_monitor_handle_t *phy_monitor_handle = (eth_phy_monitor_handle_t *)parameter;

    for (uint32_t i = 0; i < phy_monitor_handle->phy_handle_cnt; i++)
    {
        eth_dev = phy_monitor_handle->phy_handle[i]->eth_dev;
        phy_dev = phy_monitor_handle->phy_handle[i]->phy_dev;

        phy_dev->phy.ops->get_link_status(&phy_dev->phy, &status);

        if (status)
        {
            phy_dev->phy.ops->get_link_speed_duplex(&phy_dev->phy, &phy_info.phy_speed, &phy_info.phy_duplex);

            ret = memcmp(&phy_dev->phy_info, &phy_info, sizeof(phy_info_t));
            if (ret != 0)
            {
                memcpy(&phy_dev->phy_info, &phy_info, sizeof(phy_info_t));
            }
        }

        if (phy_dev->phy_link != status)
        {
            phy_dev->phy_link = status ? PHY_LINK_UP : PHY_LINK_DOWN;
            eth_device_linkchange(eth_dev, status);
            LOG_I("PHY Status: %s", status ? "Link up" : "Link down\n");
            if (status == PHY_LINK_UP)
            {
                LOG_I("PHY Speed: %s", ps[phy_dev->phy_info.phy_speed]);
                LOG_I("PHY Duplex: %s\n", phy_dev->phy_info.phy_duplex & PHY_FULL_DUPLEX ? "full duplex" : "half duplex");
                enet_set_line_speed(phy_monitor_handle->phy_handle[i]->instance, line_speed[phy_dev->phy_info.phy_speed]);
                enet_set_duplex_mode(phy_monitor_handle->phy_handle[i]->instance, phy_dev->phy_info.phy_duplex);
            }
        }
    }
}

static void phy_detection(void *parameter)
{
    uint8_t detected_count = 0;
    struct rt_phy_msg msg = {0, 0};
    phy_device_t *phy_dev = (phy_device_t *)parameter;
    rt_uint32_t i;

    msg.reg = phy_dev->phy.reg_list[PHY_ID1_REG_IDX];
    phy_dev->phy.ops->init(phy_dev->phy.bus->hw_obj, phy_dev->phy.addr, PHY_MDIO_CSR_CLK_FREQ);

    while(phy_dev->phy.addr == 0xffff)
    {
        /* Search a PHY */
        for (i = 0; i <= 0x1f; i++)
        {
            ((rt_phy_t *)(phy_dev->phy.parent.user_data))->addr = i;
            phy_dev->phy.parent.read(&(phy_dev->phy.parent), 0, &msg, 1);

            if (msg.value == PHY_ID1)
            {
                phy_dev->phy.addr = i;
                LOG_D("Found a PHY device[address:0x%02x].\n", phy_dev->phy.addr);
                return;
            }
        }

        phy_dev->phy.addr = 0xffff;
        detected_count++;
        rt_thread_mdelay(1000);

        if (detected_count > 3)
        {
            LOG_E("No any PHY device is detected! Please check your hardware!\n");
            return;
        }
    }
}

static void phy_monitor_thread_entry(void *args)
{
    rt_timer_t phy_status_timer;

    eth_phy_monitor_handle_t *phy_monitor_handle = (eth_phy_monitor_handle_t *)args;

    for (uint32_t i = 0; i < phy_monitor_handle->phy_handle_cnt; i++)
    {
        LOG_D("Detect a PHY%d\n", i);
        phy_detection(phy_monitor_handle->phy_handle[i]->phy_dev);
    }

    phy_status_timer = rt_timer_create("PHY_Monitor", phy_poll_status, phy_monitor_handle, RT_TICK_PER_SECOND, RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);

    if (!phy_status_timer || rt_timer_start(phy_status_timer) != RT_EOK)
    {
        LOG_E("Failed to start link change detection timer\n");
    }
}

int phy_device_register(void)
{
    rt_err_t err = RT_ERROR;
    rt_thread_t thread_phy_monitor;

    /* Set ops for PHY */
    phy_ops.init = phy_init;
    phy_ops.get_link_status = phy_get_link_status;
    phy_ops.get_link_speed_duplex = phy_get_link_speed_duplex;

    for (uint32_t i = 0; i < ARRAY_SIZE(s_gphys); i++)
    {
        /* Set PHY address */
        s_gphys[i]->phy_dev->phy.addr = 0xffff;

        /* Set MIDO bus */
        s_gphys[i]->mdio_bus->hw_obj     = s_gphys[i]->instance;
        s_gphys[i]->mdio_bus->name       = s_gphys[i]->mdio_name;
        s_gphys[i]->mdio_bus->ops->read  = phy_read;
        s_gphys[i]->mdio_bus->ops->write = phy_write;
        s_gphys[i]->phy_dev->phy.bus     = s_gphys[i]->mdio_bus;
        s_gphys[i]->phy_dev->phy.ops     = &phy_ops;

        /* Set PHY register list */
        s_gphys[i]->phy_dev->phy.reg_list = s_gphy_reg_list[i];

        rt_hw_phy_register(&s_gphys[i]->phy_dev->phy, PHY_NAME);
    }

    /* Start PHY monitor */
    thread_phy_monitor = rt_thread_create("PHY Monitor", phy_monitor_thread_entry, &phy_monitor_handle, 1024, RT_THREAD_PRIORITY_MAX - 2, 2);

    if (thread_phy_monitor != RT_NULL)
    {
        rt_thread_startup(thread_phy_monitor);
    }
    else
    {
        err = RT_ERROR;
    }

    return err;
}
INIT_PREV_EXPORT(phy_device_register);
#endif /* RT_USING_PHY */
