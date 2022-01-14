/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-03     mazhiyuan    first version
 */

#ifndef __DRV_SDHI_H__
#define __DRV_SDHI_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_common.h>
#include <drv_config.h>
#include <hal_data.h>

#ifndef SDIO_BUFF_SIZE
    #define SDIO_BUFF_SIZE 4096
#endif

#ifndef SDIO_ALIGN_LEN
    #define SDIO_ALIGN_LEN (32)
#endif

#define SD_INFO2_CBSY_SDD0MON_IDLE_VAL 0x80
#define SD_INFO2_CBSY_SDD0MON_IDLE_MASK 0x4080
#define BUSY_TIMEOUT_US 5000000

#define SDHI_INFO1_RESPONSE_END 1
#define SDHI_INFO1_ACCESS_END (1 << 2)
#define SDHI_INFO2_MASK_CMD_SEND 0x00007C80U
#define SDHI_INFO2_BRE (1 << 8)
#define SDHI_INFO2_BWE (1 << 9)

#define SDHI_CMD_RESP_TYPE_EXT_NONE (0 << 8)
#define SDHI_CMD_RESP_TYPE_EXT_R1_R5_R6_R7 (4 << 8)
#define SDHI_CMD_RESP_TYPE_EXT_R1B (5 << 8)
#define SDHI_CMD_RESP_TYPE_EXT_R2 (6 << 8)
#define SDHI_CMD_RESP_TYPE_EXT_R3_R4 (7 << 8)
#define SDHI_CMD_ADTC_EN (1 << 11)
#define SDHI_CMD_DATA_DIR_READ (1 << 12)
#define SDHI_BLK_TRANSFER (1 << 13)

#define SDIO_MAX_FREQ 25000000

#define HW_SDHI_ERR_CRCE (0x01U << 17)
#define HW_SDHI_ERR_RTIMEOUT (0x01U << 22)
#define HW_SDHI_ERR_DTIMEOUT (0x01U << 19)

#define SDHI_WAIT_ACCESS_BIT 2
#define SDHI_WAIT_RESPONSE_BIT 0

#define SDIO_TX_RX_COMPLETE_TIMEOUT_LOOPS (1000000U)

struct ra_sdhi
{
    const sdmmc_instance_t *instance;
    sdmmc_device_t *media_device;
};

#endif
