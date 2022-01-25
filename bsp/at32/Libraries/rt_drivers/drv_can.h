/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-02-09     shelton      the first version
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <board.h>
#include <rtdevice.h>
#include <rtthread.h>

#define CAN_TX_MAILBOX0             (0x00000001U)  /*!< Tx Mailbox 0  */
#define CAN_TX_MAILBOX1             (0x00000002U)  /*!< Tx Mailbox 1  */
#define CAN_TX_MAILBOX2             (0x00000004U)  /*!< Tx Mailbox 2  */

struct at32_baud_rate_tab
{
    rt_uint32_t baud_rate;
    rt_uint32_t sjw;
    rt_uint32_t bs1;
    rt_uint32_t bs2;
    rt_uint32_t psc;
};

struct CAN_Handler
{
    CAN_Type *Instance;
    CAN_InitType CanInit;
    CAN_FilterInitType FilterConfig;
};

/* at32 can device */
struct at32_can
{
    char *name;
    struct CAN_Handler CanConfig;
    struct rt_can_device device;     /* inherit from can device */
};

int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_CAN_H__ */

/************************** end of file ******************/
