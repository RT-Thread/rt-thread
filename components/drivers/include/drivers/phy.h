/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-14     wangqiang    the first version
 * 2022-08-17     xjy198903    add 1000M definition
 */

#ifndef __PHY_H__
#define __PHY_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* Defines the PHY link speed. This is align with the speed for MAC. */
#define PHY_SPEED_10M   0U     /* PHY 10M speed. */
#define PHY_SPEED_100M  1U     /* PHY 100M speed. */
#define PHY_SPEED_1000M 2U     /* PHY 1000M speed. */

/* Defines the PHY link duplex. */
#define PHY_HALF_DUPLEX 0U     /* PHY half duplex. */
#define PHY_FULL_DUPLEX 1U     /* PHY full duplex. */

/*! @brief Defines the PHY loopback mode. */
#define PHY_LOCAL_LOOP  0U     /* PHY local loopback. */
#define PHY_REMOTE_LOOP 1U     /* PHY remote loopback. */

#define PHY_STATUS_OK      0U
#define PHY_STATUS_FAIL    1U
#define PHY_STATUS_TIMEOUT 2U

typedef struct rt_phy_msg
{
    rt_uint32_t reg;
    rt_uint32_t value;
}rt_phy_msg_t;

typedef struct rt_phy_device
{
    struct rt_device parent;
    struct rt_mdio_bus *bus;
    rt_uint32_t addr;
    struct rt_phy_ops *ops;
}rt_phy_t;

typedef rt_int32_t rt_phy_status;

struct rt_phy_ops
{
    rt_phy_status (*init)(void *object, rt_uint32_t phy_addr, rt_uint32_t src_clock_hz);
    rt_phy_status (*read)(rt_uint32_t reg, rt_uint32_t *data);
    rt_phy_status (*write)(rt_uint32_t reg, rt_uint32_t data);
    rt_phy_status (*loopback)(rt_uint32_t mode, rt_uint32_t speed, rt_bool_t enable);
    rt_phy_status (*get_link_status)(rt_bool_t *status);
    rt_phy_status (*get_link_speed_duplex)(rt_uint32_t *speed, rt_uint32_t *duplex);
};

rt_err_t rt_hw_phy_register(struct rt_phy_device *phy, const char *name);

#ifdef __cplusplus
}
#endif

#endif /* __PHY_H__*/
