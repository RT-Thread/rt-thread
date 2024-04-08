/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <board.h>
#include <rtdevice.h>
#include <rtthread.h>

/* attention !!!
* if RT_CAN_USING_CANFD is enabled, RT_CAN_CMD_SET_BITTIMING is more recommended
* than RT_CAN_CMD_SET_BAUD_FD.
* because sample point is not specified by config when using RT_CAN_CMD_SET_BAUD_FD
* but in range [CAN_SAMPLEPOINT_MIN/1000,CAN_SAMPLEPOINT_MAX/1000]
* this may not match with your application
*/
#define CAN_SAMPLEPOINT_MIN             (750U)
#define CAN_SAMPLEPOINT_MAX             (800U)

#define CAN_CLOCK_SRC_20M               (20*1000*1000UL)
#define CAN_CLOCK_SRC_40M               (40*1000*1000UL)
#define CAN_CLOCK_SRC_80M               (80*1000*1000UL)

#define CANFD_ARBITRATION_BAUD_250K     (250*1000UL)
#define CANFD_ARBITRATION_BAUD_500K     (500*1000UL)

#define CANFD_DATA_BAUD_1M              (1*1000*1000UL)
#define CANFD_DATA_BAUD_2M              (2*1000*1000UL)
#define CANFD_DATA_BAUD_4M              (4*1000*1000UL)
#define CANFD_DATA_BAUD_5M              (5*1000*1000UL)
#define CANFD_DATA_BAUD_8M              (8*1000*1000UL)

/* hc32 can device */
struct can_dev_init_params
{
    char *name;
    rt_bool_t single_trans_mode;
};

int rt_hw_can_init(void);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_CAN_H__ */

/************************** end of file ******************/
