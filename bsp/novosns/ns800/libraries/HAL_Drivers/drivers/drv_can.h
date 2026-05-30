/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-05     Xeon Xu      the first version
 * 2019-01-22     YLZ          port from stm324xx-HAL to bsp stm3210x-HAL
 * 2019-01-26     YLZ          redefine `struct stm32_drv_can` add member `Rx1Message`
 * 2019-02-19     YLZ          port to BSP [stm32]
 * 2019-06-17     YLZ          modify struct stm32_drv_can.
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <board.h>
#include <rtdevice.h>

#define CAN_FILTER_NUM_MAX (16U)

enum _can_state
{
    StateIdle = 0x0,     /*!< MB idle.*/
    StateRxData = 0x1,   /*!< MB receiving.*/
    StateRxRemote = 0x2, /*!< MB receiving remote reply.*/
    StateTxData = 0x3,   /*!< MB transmitting.*/
    StateTxRemote = 0x4, /*!< MB transmitting remote request.*/
};

struct ns800rt7_baud_rate_tab
{
    rt_uint32_t baud_rate;
    rt_uint32_t config_data;
};
#define BAUD_DATA(NO)       (can_baud_rate_tab[NO].config_data)


/* stm32 can device */
typedef struct
{
    char                         *name;
    FLEXCANDRV_ControllerCfgType CanCfg;
    IRQn_Type                    irqn1;
    IRQn_Type                    irqn2;
    FLEXCANDRV_Type              CanHandle;
    FLEXCANDRV_MsgCfgType        FilterConfig[CAN_FILTER_NUM_MAX];
    uint8_t                      FilterNum;
    volatile uint8_t             mbState[128];
    struct rt_can_device         device;     /* inherit from can device */
} ns800rt7_can;

int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_CAN_H__ */

/************************** end of file ******************/

