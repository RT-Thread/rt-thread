/*
 * Copyright (c) 2023-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2023-12-20   Jiading     Optimization for all-in-one version
 * 2024-04-17   Jiading     Support multiple PHYs
 * 2026-09-28   Jiading     Wait for enet_phy_speed_valid before announcing link-up
 */

#include "rtthread.h"

#if !defined(RT_USING_PHY)
#error Please enable phy abstraction layer or remove the current file from your project!
#endif

#ifdef RT_USING_PHY
#include <rtdevice.h>
#include <rtdbg.h>
#include "drv_enet.h"
#include "drv_enet_phy.h"
#include "hpm_enet_phy.h"
#include "hpm_soc.h"
#include "netif/ethernetif.h"
#include "board.h"
#include "hpm_enet_drv.h"

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
static struct rt_mdio_bus_ops mdio0_bus_ops;
static struct rt_mdio_bus mdio0_bus = {.ops = &mdio0_bus_ops};
static phy_device_t phy0_dev;

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
static struct rt_mdio_bus_ops mdio1_bus_ops;
static struct rt_mdio_bus mdio1_bus = {.ops = &mdio1_bus_ops};
static phy_device_t phy1_dev;

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

eth_phy_monitor_handle_t phy_monitor_handle =
{
    .phy_handle_cnt = ARRAY_SIZE(s_gphys),
    .phy_handle     = s_gphys
};

static struct rt_phy_ops phy_ops;

static rt_phy_status phy_init(void *object, rt_uint32_t phy_addr, rt_uint32_t src_clock_hz)
{
#if defined(BSP_USING_ETH0) && defined(BSP_USING_ENET_PHY_DP83867)
    if ((ENET_Type *)object == HPM_ENET0)
    {
       dp83867_config_t phy_config;

       dp83867_reset((ENET_Type *)object);
       #if defined(__DISABLE_AUTO_NEGO) && __DISABLE_AUTO_NEGO
       dp83867_set_mdi_crossover_mode((ENET_Type *)object, enet_phy_mdi_crossover_manual_mdix);
       #endif
       dp83867_basic_mode_default_config((ENET_Type *)object, &phy_config);
       if (dp83867_basic_mode_init((ENET_Type *)object, &phy_config) == true) {
           return PHY_STATUS_OK;
       } else {
        return PHY_STATUS_FAIL;
       }
    }
#endif


#if defined(BSP_USING_ETH0) && defined(BSP_USING_ENET_PHY_RTL8211)
    if ((ENET_Type *)object == HPM_ENET0)
    {
        rtl8211_config_t phy_config;

        rtl8211_reset((ENET_Type *)object, RTL8211_ADDR);
        rtl8211_basic_mode_default_config((ENET_Type *)object, &phy_config);
        if (rtl8211_basic_mode_init((ENET_Type *)object, RTL8211_ADDR, &phy_config) == true) {
            return PHY_STATUS_OK;
        } else {
            return PHY_STATUS_FAIL;
        }
    }
#endif

#if defined(BSP_USING_ETH0) && defined(BSP_USING_ENET_PHY_RTL8201) && !defined(BSP_USING_ETH1)
    if ((ENET_Type *)object == HPM_ENET0)
    {
        rtl8201_config_t phy_config;
        rtl8201_reset((ENET_Type *)object, RTL8201_ADDR);
        rtl8201_basic_mode_default_config((ENET_Type *)object, &phy_config);
        phy_config.media_interface = ((enet_device *)eth0_phy_handle.eth_dev->parent.user_data)->media_interface;
        phy_config.rmii_refclk_dir = ((enet_device *)eth0_phy_handle.eth_dev->parent.user_data)->int_refclk;
        if (rtl8201_basic_mode_init((ENET_Type *)object, RTL8201_ADDR, &phy_config) == true) {
            return PHY_STATUS_OK;
        } else {
            return PHY_STATUS_FAIL;
        }
    }
#endif

#if defined(BSP_USING_ETH1) && defined(BSP_USING_ENET_PHY_DP83848)
    if ((ENET_Type *)object == HPM_ENET1)
    {
        dp83848_config_t phy_config;

        dp83848_reset((ENET_Type *)object);
        dp83848_basic_mode_default_config((ENET_Type *)object, &phy_config);
        if (dp83848_basic_mode_init((ENET_Type *)object, &phy_config) == true) {
            return PHY_STATUS_OK;
        } else {
            return PHY_STATUS_FAIL;
        }
    }
#endif

#if defined(BSP_USING_ETH1) && defined(BSP_USING_ENET_PHY_RTL8201)
    if ((ENET_Type *)object == HPM_ENET1)
    {
        rtl8201_config_t phy_config;

        rtl8201_reset((ENET_Type *)object, RTL8201_ADDR);
        rtl8201_basic_mode_default_config((ENET_Type *)object, &phy_config);
        phy_config.media_interface = ((enet_device *)eth1_phy_handle.eth_dev->parent.user_data)->media_interface;
        phy_config.rmii_refclk_dir = ((enet_device *)eth1_phy_handle.eth_dev->parent.user_data)->int_refclk;
        if (rtl8201_basic_mode_init((ENET_Type *)object, RTL8201_ADDR, &phy_config) == true) {
            return PHY_STATUS_OK;
        } else {
            return PHY_STATUS_FAIL;
        }
    }
#endif

#if defined(BSP_USING_ETH1) && defined(BSP_USING_ENET_PHY_LAN8720)
    if ((ENET_Type *)object == HPM_ENET1)
    {
        lan8720_config_t phy_config;

        lan8720_reset((ENET_Type *)object, LAN8720_ADDR);
        lan8720_basic_mode_default_config((ENET_Type *)object, &phy_config);
        if (lan8720_basic_mode_init((ENET_Type *)object, LAN8720_ADDR, &phy_config) == true) {
            return PHY_STATUS_OK;
        } else {
            return PHY_STATUS_FAIL;
        }
    }
#endif

    return PHY_STATUS_FAIL;
}

static rt_size_t phy_read(void *bus, rt_uint32_t addr, rt_uint32_t reg, void *data, rt_uint32_t size)
{
    enet_read_phy(((struct rt_mdio_bus *)bus)->hw_obj, addr, reg, (uint16_t *)data);

    return size;
}

static rt_size_t phy_write(void *bus, rt_uint32_t addr, rt_uint32_t reg, void *data, rt_uint32_t size)
{
    enet_write_phy(((struct rt_mdio_bus *)bus)->hw_obj, addr, reg,  *(uint16_t *)data);

    return size;
}

static rt_phy_status phy_query_status(rt_phy_t *phy, enet_phy_status_t *phy_status)
{
    hpm_stat_t stat = status_fail;

    *phy_status = (enet_phy_status_t){0};

    if (phy->bus->hw_obj == HPM_ENET0)
    {
        #if defined(__USE_DP83867) && __USE_DP83867
        stat = dp83867_get_phy_status(phy->bus->hw_obj, DP83867_ADDR, phy_status);
        #endif

        #if defined(__USE_RTL8211) && __USE_RTL8211
        stat = rtl8211_get_phy_status(phy->bus->hw_obj, RTL8211_ADDR, phy_status);
        #endif

        #if defined(__USE_RTL8201) && __USE_RTL8201 && !defined(BSP_USING_ETH1)
        stat = rtl8201_get_phy_status(phy->bus->hw_obj, RTL8201_ADDR, phy_status);
        #endif
    }

#if defined(HPM_ENET1_BASE)
    if (phy->bus->hw_obj == HPM_ENET1)
    {
        #if defined(__USE_DP83848) && __USE_DP83848
        stat = dp83848_get_phy_status(phy->bus->hw_obj, DP83848_ADDR, phy_status);
        #endif

        #if defined(__USE_RTL8201) && __USE_RTL8201
        stat = rtl8201_get_phy_status(phy->bus->hw_obj, RTL8201_ADDR, phy_status);
        #endif

        #if defined(__USE_LAN8720) && __USE_LAN8720
        stat = lan8720_get_phy_status(phy->bus->hw_obj, LAN8720_ADDR, phy_status);
        #endif
    }
#endif

    if (stat != status_success) {
        return PHY_STATUS_FAIL;
    }

    return PHY_STATUS_OK;
}

static void phy_apply_mac(ENET_Type *instance, const phy_info_t *phy_info)
{
    enet_line_speed_t line_speed[] = {enet_line_speed_10mbps, enet_line_speed_100mbps, enet_line_speed_1000mbps};

    if (phy_info->phy_speed >= ARRAY_SIZE(line_speed)) {
        return;
    }

    enet_set_line_speed(instance, line_speed[phy_info->phy_speed]);
    enet_set_duplex_mode(instance, phy_info->phy_duplex);
}

static rt_phy_status phy_get_link_status(rt_phy_t *phy, rt_bool_t *status)
{
    enet_phy_status_t phy_status;

    if (phy_query_status(phy, &phy_status) != PHY_STATUS_OK) {
        *status = RT_FALSE;
        return PHY_STATUS_FAIL;
    }

    *status = (phy_status.enet_phy_link == enet_phy_link_up) ? RT_TRUE : RT_FALSE;

    return PHY_STATUS_OK;
}

static rt_phy_status phy_get_link_speed_duplex(rt_phy_t *phy, rt_uint32_t *speed, rt_uint32_t *duplex)
{
    enet_phy_status_t phy_status;

    if (phy_query_status(phy, &phy_status) != PHY_STATUS_OK) {
        return PHY_STATUS_FAIL;
    }

    if (!enet_phy_link_up_with_valid_speed(&phy_status)) {
        return PHY_STATUS_FAIL;
    }

    *speed  = phy_status.enet_phy_speed;
    *duplex = phy_status.enet_phy_duplex;

    return PHY_STATUS_OK;
}

static void phy_poll_status(void *parameter)
{
    int ret;
    phy_info_t phy_info;
    enet_phy_status_t phy_status;
    phy_device_t *phy_dev;
    struct eth_device *eth_dev;
    char const *ps[] = {"10Mbps", "100Mbps", "1000Mbps"};
    eth_phy_monitor_handle_t *phy_monitor_handle = (eth_phy_monitor_handle_t *)parameter;

    for (uint32_t i = 0; i < phy_monitor_handle->phy_handle_cnt; i++)
    {
        eth_dev = phy_monitor_handle->phy_handle[i]->eth_dev;
        phy_dev = phy_monitor_handle->phy_handle[i]->phy_dev;

        if (phy_dev->phy.ops == NULL) {
            LOG_E("phy.ops is NULL! Please check your initialization of phy.ops in phy_device_register()!\n");
            return;
        }

        if (phy_query_status(&phy_dev->phy, &phy_status) != PHY_STATUS_OK) {
            continue;
        }

        if (phy_status.enet_phy_link == enet_phy_link_down) {
            if (phy_dev->phy_link != PHY_LINK_DOWN) {
                phy_dev->phy_link = PHY_LINK_DOWN;
                eth_device_linkchange(eth_dev, RT_FALSE);
                LOG_I("%s", phy_dev->phy.bus->hw_obj == HPM_ENET0 ? "ENET0" : "ENET1");
                LOG_I("PHY Status: %s", "Link down\n");
            }
            continue;
        }

        if (!enet_phy_link_up_with_valid_speed(&phy_status)) {
            continue;
        }

        phy_info.phy_speed = phy_status.enet_phy_speed;
        phy_info.phy_duplex = phy_status.enet_phy_duplex;

        ret = memcmp(&phy_dev->phy_info, &phy_info, sizeof(phy_info_t));
        if (ret != 0) {
            memcpy(&phy_dev->phy_info, &phy_info, sizeof(phy_info_t));
            if (phy_dev->phy_link == PHY_LINK_UP) {
                phy_apply_mac(phy_monitor_handle->phy_handle[i]->instance, &phy_dev->phy_info);
                LOG_I("%s", phy_dev->phy.bus->hw_obj == HPM_ENET0 ? "ENET0" : "ENET1");
                LOG_I("PHY Speed: %s", ps[phy_dev->phy_info.phy_speed]);
                LOG_I("PHY Duplex: %s\n", phy_dev->phy_info.phy_duplex & PHY_FULL_DUPLEX ? "full duplex" : "half duplex");
            }
        }

        if (phy_dev->phy_link != PHY_LINK_UP) {
            phy_dev->phy_link = PHY_LINK_UP;
            eth_device_linkchange(eth_dev, RT_TRUE);
            LOG_I("%s", phy_dev->phy.bus->hw_obj == HPM_ENET0 ? "ENET0" : "ENET1");
            LOG_I("PHY Status: %s", "Link up");
            LOG_I("PHY Speed: %s", ps[phy_dev->phy_info.phy_speed]);
            LOG_I("PHY Duplex: %s\n", phy_dev->phy_info.phy_duplex & PHY_FULL_DUPLEX ? "full duplex" : "half duplex");
            phy_apply_mac(phy_monitor_handle->phy_handle[i]->instance, &phy_dev->phy_info);
        }
    }
}

static void phy_detection(void *parameter)
{
    phy_device_t *phy_dev = (phy_device_t *)parameter;

    if (phy_dev->phy.ops->init(phy_dev->phy.bus->hw_obj, 0, PHY_MDIO_CSR_CLK_FREQ) != PHY_STATUS_OK)
    {
        LOG_E("No any PHY device is detected! Please check your hardware!\n");
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
    rt_err_t err = -RT_ERROR;
    rt_thread_t thread_phy_monitor;
    char phy_dev_name[8]={0};

    /* Set ops for PHY */
    phy_ops.init = phy_init;
    phy_ops.get_link_status = phy_get_link_status;
    phy_ops.get_link_speed_duplex = phy_get_link_speed_duplex;

    for (uint32_t i = 0; i < ARRAY_SIZE(s_gphys); i++)
    {
        /* Set PHY address */
        s_gphys[i]->phy_dev->phy.addr = 0xffff;

        /* Set MDIO bus */
        s_gphys[i]->mdio_bus->hw_obj     = s_gphys[i]->instance;
        s_gphys[i]->mdio_bus->name       = s_gphys[i]->mdio_name;
        s_gphys[i]->mdio_bus->ops->read  = phy_read;
        s_gphys[i]->mdio_bus->ops->write = phy_write;
        s_gphys[i]->phy_dev->phy.bus     = s_gphys[i]->mdio_bus;
        s_gphys[i]->phy_dev->phy.ops     = &phy_ops;

        sprintf(phy_dev_name, "PHYDev%d", i);
        rt_hw_phy_register(&s_gphys[i]->phy_dev->phy, phy_dev_name);
    }

    /* Start PHY monitor */
    thread_phy_monitor = rt_thread_create("PHY Monitor", phy_monitor_thread_entry, &phy_monitor_handle, 1024, RT_THREAD_PRIORITY_MAX - 2, 2);

    if (thread_phy_monitor != RT_NULL)
    {
        rt_thread_startup(thread_phy_monitor);
        err = RT_EOK;
    }
    else
    {
        err = -RT_ERROR;
    }

    return err;
}
INIT_PREV_EXPORT(phy_device_register);
#endif /* RT_USING_PHY */
