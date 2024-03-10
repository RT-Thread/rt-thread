/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-16     songchao   first version
 * 2021-08-13     songchao   add more device info
 */

#ifndef __DRV_ETH_H__
#define __DRV_ETH_H__

#include <rtthread.h>
#include <netif/ethernetif.h>
#include "fsl_phy.h"
#include "imx6ull.h"
#include "drv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_ADDR_LEN 6
struct rt_imx6ul_ethps
{
    /* inherit from ethernet device */
    struct eth_device parent;
    /* interface address info, hw address */
    rt_uint8_t  dev_addr[MAX_ADDR_LEN];
    /* ETH_Speed */
    uint32_t    ETH_Speed;
    /* ETH_Duplex_Mode */
    uint32_t    ETH_Mode;
    rt_bool_t phy_link_status;
    const char *mac_name;
    const char *irq_name;
    enum _imx_interrupts irq_num;
    uint8_t phy_num;
    const ENET_Type *enet_phy_base_addr;
    ENET_Type *enet_virtual_base_addr;
    uint32_t mac_num;
    enet_buffer_config_t buffConfig;
    enet_config_t config;
    enet_handle_t handle;
    struct imx6ull_iomuxc gpio[9];
    GPIO_Type *phy_base_addr;
    uint32_t phy_gpio_pin;
    uint32_t phy_id;
};

int32_t get_instance_by_base(void *base);
#ifdef __cplusplus
}
#endif

#endif /* __DRV_ETH_H__ */
