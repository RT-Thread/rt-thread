/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-08-30     shelton      first version
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtdevice.h>
#include <rtthread.h>
#include "drv_common.h"

#define CANFD_DATA_1MBaud                (1*1000*1000UL)
#define CANFD_DATA_2MBaud                (2*1000*1000UL)
#define CANFD_DATA_3MBaud                (3*1000*1000UL)
#define CANFD_DATA_4MBaud                (4*1000*1000UL)
#define CANFD_DATA_5MBaud                (5*1000*1000UL)
#define CANFD_DATA_6MBaud                (6*1000*1000UL)

struct at32_baud_rate
{
    rt_uint32_t baud_rate;
    rt_uint8_t div;
    rt_uint8_t rsaw_size;
    rt_uint16_t bts1_size;
    rt_uint8_t bts2_size;
};

struct at32_baud_rate_fd
{
    rt_uint32_t baud_rate;
    rt_uint8_t div;
    rt_uint8_t rsaw_size;
    rt_uint16_t bts1_size;
    rt_uint8_t bts2_size;
    rt_uint16_t ssoffset;
};

/* at32 can device */
struct at32_can
{
    char *name;
    can_type *can_x;
    IRQn_Type tx_irqn;
    IRQn_Type rx_irqn;
    IRQn_Type stat_irqn;
    IRQn_Type err_irqn;
    uint8_t enable_canfd;
    can_bittime_type bittime_init_struct;
    can_filter_config_type filter_init_struct;
    struct rt_can_device device;     /* inherit from can device */
};

int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_CAN_H__ */

/************************** end of file ******************/
