/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-xx-xx     CDT          first version
 */

#ifndef __DRV_MCAN_H__
#define __DRV_MCAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <board.h>
#include <rtdevice.h>
#include <rtthread.h>

/* Attention !!!
* If RT_CAN_USING_CANFD is enabled, RT_CAN_CMD_SET_BITTIMING is more recommended
* than RT_CAN_CMD_SET_BAUD_FD.
* because sample point is not specified by config when using RT_CAN_CMD_SET_BAUD_FD
* but in range [MCAN_SAMPLEPOINT_MIN/1000, MCAN_SAMPLEPOINT_MAX/1000]
* this may not match with your application
*/
#define MCAN_SAMPLEPOINT_MIN            (700U)
#define MCAN_SAMPLEPOINT_MAX            (850U)

#define MCAN_CLOCK_SRC_20M              (20*1000*1000UL)
#define MCAN_CLOCK_SRC_40M              (40*1000*1000UL)
#define MCAN_CLOCK_SRC_80M              (80*1000*1000UL)

#define MCANFD_NOMINAL_BAUD_500K        (500*1000UL)
#define MCANFD_NOMINAL_BAUD_1M          (1000*1000UL)

#define MCANFD_DATA_BAUD_1M             (1*1000*1000UL)
#define MCANFD_DATA_BAUD_2M             (2*1000*1000UL)
#define MCANFD_DATA_BAUD_4M             (4*1000*1000UL)
#define MCANFD_DATA_BAUD_5M             (5*1000*1000UL)
#define MCANFD_DATA_BAUD_8M             (8*1000*1000UL)


int rt_hw_mcan_init(void);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_MCAN_H__ */

/************************** end of file ******************/
