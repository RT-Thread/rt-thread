/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-02-24     heyuan       the first version
 * 2020-08-17     malongwei    Fix something
 */

#ifndef __DRV_FDCAN_H__
#define __DRV_FDCAN_H__

#include <rtdevice.h>
#include <rtthread.h>

#ifdef RT_USING_CAN

#ifdef __cplusplus
extern "C" {
#endif

#define BSP_FDCAN_FRAMEFORMAT_CLASSIC       (0)
#define BSP_FDCAN_FRAMEFORMAT_FD_NO_BRS     (1)
#define BSP_FDCAN_FRAMEFORMAT_FD_BRS        (2)

enum _BSP_FDCAN_DATA_BAUD{
    BSP_FDCAN_BAUD_DATA_2M=(2*1000*1000),
    BSP_FDCAN_BAUD_DATA_2M5=(2500*1000),
    BSP_FDCAN_BAUD_DATA_4M=(4*1000*1000),
    BSP_FDCAN_BAUD_DATA_5M=(5*1000*1000)
};

#define BSP_CAN_CMD_SET_BRS_BAUD            (0x30)

typedef struct
{
    const char *name;
    FDCAN_HandleTypeDef fdcanHandle;
    FDCAN_RxHeaderTypeDef RxHeader;
    FDCAN_TxHeaderTypeDef TxHeader;
    uint8_t u8RxDataBuffer[8];
    uint8_t u8TxDataBuufer[8];

#ifdef RT_CAN_USING_HDR
    FDCAN_FilterTypeDef FilterConfig; /*FDCAN filter*/
    uint8_t std_filter_num;
    uint8_t ext_filter_num;
#endif

    struct rt_can_device device;      /* inherit from can device */
} _stm32_fdcan_t;

/* h7r，前面范围时仲裁/经典CAN范围，后面时数据段范围 */
typedef struct
{
    uint32_t u32NBaudrate;  /* <1M, ? */
    uint16_t u16Nbrp;       /* 1-512, 1-32 */
    uint8_t u8Nsjw;         /* 1-128, 1-16 */
    uint8_t u8Ntseg1;       /* 1-256, 1-32 */
    uint8_t u8Ntseg2;       /* 1-128, 1-16 */
} _stm32_fdcan_NTconfig_t;


#ifdef __cplusplus
}
#endif

#endif /* RT_USING_CAN */
#endif /* __DRV_FDCAN_H__ */
