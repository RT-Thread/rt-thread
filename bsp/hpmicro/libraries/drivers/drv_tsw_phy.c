/*
 * Copyright (c) 2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Change Logs:
 * Date         Author      Notes
 * 2025-3-31    Jiading     Initial version
 */

#include "rtthread.h"

#ifdef RT_USING_PHY
#include <rtdevice.h>
#include <rtdbg.h>
#include "hpm_tsw_drv.h"
#include "drv_tsw_phy.h"
#include "hpm_tsw_phy.h"
#include "hpm_soc.h"
#include "netif/ethernetif.h"
#include "board.h"

typedef struct {
    TSW_Type *instance;
    uint8_t port;
} tsw_phy_instance_t;

typedef struct
{
    char *mdio_name;
    tsw_phy_instance_t *phy_ins;
    struct eth_device *eth_dev;
    phy_device_t *phy_dev;
    struct rt_mdio_bus *mdio_bus;
} tsw_phy_handle_t;

typedef struct
{
    uint8_t phy_handle_cnt;
    tsw_phy_handle_t **phy_handle;
} tsw_phy_monitor_handle_t;

extern struct eth_device eth0_dev;
static phy_device_t phy0_dev;
static struct rt_mdio_bus_ops mdio0_bus_ops;
static struct rt_mdio_bus mdio0_bus = {.ops = &mdio0_bus_ops};
static tsw_phy_instance_t instance = {.instance = BOARD_TSW,
                                      .port = BOARD_TSW_PORT
                                        };

static tsw_phy_handle_t tsw_phy_handle = {
    .phy_ins   = &instance,
    .eth_dev   = &eth0_dev,
    .phy_dev   = &phy0_dev,
    .mdio_name = "MDIO0",
    .mdio_bus  = &mdio0_bus,
};

static tsw_phy_handle_t *s_gphys[] = {
    &tsw_phy_handle
};

tsw_phy_monitor_handle_t phy_monitor_handle = {
    .phy_handle_cnt = ARRAY_SIZE(s_gphys),
    .phy_handle     = s_gphys
};

static struct rt_phy_ops phy_ops;

static rt_phy_status phy_init(void *object, rt_uint32_t phy_addr, rt_uint32_t src_clock_hz)
{
    tsw_phy_instance_t *phy_ins = (tsw_phy_instance_t *)object;

    if (phy_ins->instance == HPM_TSW) {
        rtl8211_config_t phy_config;

        /* Set MDC clock frequency */
        tsw_ep_set_mdio_config(phy_ins->instance, phy_ins->port, src_clock_hz / (2 * PHY_MDIO_CLK_FREQ) - 1);

        /* PHY Reset */
        rtl8211_reset(phy_ins->instance, phy_ins->port);
        rtl8211_basic_mode_default_config(phy_ins->instance, &phy_config);
        if (rtl8211_basic_mode_init(phy_ins->instance, phy_ins->port, &phy_config) == true) {
            return PHY_STATUS_OK;
        } else {
            return PHY_STATUS_FAIL;
        }
    }

    return -RT_EINVAL;
}

static rt_size_t phy_read(void *bus, rt_uint32_t addr, rt_uint32_t reg, void *data, rt_uint32_t size)
{
    hpm_stat_t stat;
    tsw_phy_instance_t *phy_ins = ((struct rt_mdio_bus *)bus)->hw_obj;

    stat = tsw_ep_mdio_read(phy_ins->instance, phy_ins->port, addr, reg, (uint16_t *)data);

    if (stat == status_success) {
        return size;
    } else {
        return 0;
    }
}

static rt_size_t phy_write(void *bus, rt_uint32_t addr, rt_uint32_t reg, void *data, rt_uint32_t size)
{
    hpm_stat_t stat;
    tsw_phy_instance_t *phy_ins = ((struct rt_mdio_bus *)bus)->hw_obj;

    stat = tsw_ep_mdio_write(phy_ins->instance, phy_ins->port, addr, reg, *(uint16_t *)data);

    if (stat == status_success) {
        return size;
    } else {
        return 0;
    }
}

static rt_phy_status phy_get_link_status(rt_phy_t *phy, rt_bool_t *status)
{
    tsw_phy_instance_t *phy_ins = phy->bus->hw_obj;
    tsw_phy_status_t phy_status;

    if (phy_ins->instance == HPM_TSW) {
        #if defined(__USE_RTL8211) && __USE_RTL8211
        rtl8211_get_phy_status(phy_ins->instance, phy_ins->port, &phy_status);
        #endif
    }

    *status = phy_status.tsw_phy_link;

    return PHY_STATUS_OK;
}

static rt_phy_status phy_get_link_speed_duplex(rt_phy_t *phy, rt_uint32_t *speed, rt_uint32_t *duplex)
{
    tsw_phy_instance_t *phy_ins = phy->bus->hw_obj;
    tsw_phy_status_t phy_status;

    if (phy_ins->instance == HPM_TSW) {
        #if defined(__USE_RTL8211) && __USE_RTL8211
        rtl8211_get_phy_status(phy_ins->instance, phy_ins->port, &phy_status);
        #endif
    }

    *speed  = phy_status.tsw_phy_speed;
    *duplex = phy_status.tsw_phy_duplex;

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
    tsw_port_speed_t port_speed[] = {tsw_port_speed_10mbps, tsw_port_speed_100mbps, tsw_port_speed_1000mbps};
    tsw_phy_monitor_handle_t *phy_monitor_handle = (tsw_phy_monitor_handle_t *)parameter;

    for (uint32_t i = 0; i < phy_monitor_handle->phy_handle_cnt; i++) {
        eth_dev = phy_monitor_handle->phy_handle[i]->eth_dev;
        phy_dev = phy_monitor_handle->phy_handle[i]->phy_dev;

        phy_dev->phy.ops->get_link_status(&phy_dev->phy, &status);

        if (status) {
            phy_dev->phy.ops->get_link_speed_duplex(&phy_dev->phy, &phy_info.phy_speed, &phy_info.phy_duplex);

            ret = memcmp(&phy_dev->phy_info, &phy_info, sizeof(phy_info_t));
            if (ret != 0) {
                memcpy(&phy_dev->phy_info, &phy_info, sizeof(phy_info_t));
            }
        }

        if (phy_dev->phy_link != status) {
            phy_dev->phy_link = status ? PHY_LINK_UP : PHY_LINK_DOWN;
            eth_device_linkchange(eth_dev, status);
            LOG_I("PHY Status: %s", status ? "Link up" : "Link down\n");
            if (status == PHY_LINK_UP) {
                LOG_I("PHY Speed: %s", ps[phy_dev->phy_info.phy_speed]);
                LOG_I("PHY Duplex: %s\n", phy_dev->phy_info.phy_duplex & PHY_FULL_DUPLEX ? "full duplex" : "half duplex");
                tsw_set_port_speed(phy_monitor_handle->phy_handle[i]->phy_ins->instance, phy_monitor_handle->phy_handle[i]->phy_ins->port, port_speed[phy_dev->phy_info.phy_speed]);
                if (!(phy_dev->phy_info.phy_duplex & PHY_FULL_DUPLEX)) {
                    LOG_E("Error: PHY is in half duplex now, but TSW MAC supports only full duplex mode!\n");
                   return;
               }
            }
        }
    }
}

static void phy_detection(void *parameter)
{
    phy_device_t *phy_dev = (phy_device_t *)parameter;

    if (phy_dev->phy.ops->init(phy_dev->phy.bus->hw_obj, 0, PHY_MDIO_CSR_CLK_FREQ) != PHY_STATUS_OK) {
        LOG_E("No any PHY device is detected! Please check your hardware!\n");
    }

    return;

}

static void phy_monitor_thread_entry(void *args)
{
    rt_timer_t phy_status_timer;

    tsw_phy_monitor_handle_t *phy_monitor_handle = (tsw_phy_monitor_handle_t *)args;

    for (uint32_t i = 0; i < phy_monitor_handle->phy_handle_cnt; i++) {
        LOG_D("Detect a PHY%d\n", i);
        phy_detection(phy_monitor_handle->phy_handle[i]->phy_dev);
    }

    phy_status_timer = rt_timer_create("PHY_Monitor", phy_poll_status, phy_monitor_handle, RT_TICK_PER_SECOND, RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);

    if (!phy_status_timer || rt_timer_start(phy_status_timer) != RT_EOK) {
        LOG_E("Failed to start link change detection timer\n");
    }
}

int phy_device_register(void)
{
    rt_err_t err = -RT_ERROR;
    rt_thread_t thread_phy_monitor;

    /* Set ops for PHY */
    phy_ops.init = phy_init;
    phy_ops.get_link_status = phy_get_link_status;
    phy_ops.get_link_speed_duplex = phy_get_link_speed_duplex;

    for (uint32_t i = 0; i < ARRAY_SIZE(s_gphys); i++) {
        /* Set PHY address */
        s_gphys[i]->phy_dev->phy.addr = 0xffff;

        /* Set MIDO bus */
        s_gphys[i]->mdio_bus->hw_obj     = s_gphys[i]->phy_ins;
        s_gphys[i]->mdio_bus->name       = s_gphys[i]->mdio_name;
        s_gphys[i]->mdio_bus->ops->read  = phy_read;
        s_gphys[i]->mdio_bus->ops->write = phy_write;
        s_gphys[i]->phy_dev->phy.bus     = s_gphys[i]->mdio_bus;
        s_gphys[i]->phy_dev->phy.ops     = &phy_ops;

        rt_hw_phy_register(&s_gphys[i]->phy_dev->phy, NULL);
    }

    /* Start PHY monitor */
    thread_phy_monitor = rt_thread_create("PHY Monitor", phy_monitor_thread_entry, &phy_monitor_handle, 4096, RT_THREAD_PRIORITY_MAX - 2, 2);

    if (thread_phy_monitor != RT_NULL) {
        rt_thread_startup(thread_phy_monitor);
    } else {
        err = -RT_ERROR;
    }

    return err;
}
INIT_PREV_EXPORT(phy_device_register);
#endif /* RT_USING_PHY */
