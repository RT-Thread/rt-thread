/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-11-06     QT-one       first version
 */

#ifndef __DRV_SDIO_H__
#define __DRV_SDIO_H__

#include <rtthread.h>
#include <rtdevice.h>

#include <string.h>
#include "drv_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SDIO_BASE_ADDRESS
#define SDIO_BASE_ADDRESS                      HT_SDIO
#endif

#ifndef SDIO_CLOCK_FREQ
#define SDIO_CLOCK_FREQ                        (48U * 1000 * 1000)
#endif

#ifndef SDIO_BUFF_SIZE
#define SDIO_BUFF_SIZE                         (4096)
#endif

#ifndef SDIO_ALIGN_LEN
#define SDIO_ALIGN_LEN                         (32)
#endif

#ifndef SDIO_MAX_FREQ
#define SDIO_MAX_FREQ                          (24 * 1000 * 1000)
#endif

#define HW_SDIO_CMD_FLAG \
    (SDIO_INT_CMD_SEND | SDIO_FLAG_CMD_TIMEOUT | SDIO_FLAG_CMD_CRCERR | SDIO_FLAG_CMD_IDXERR)

#define HW_SDIO_DATA_FLAG \
    (SDIO_FLAG_BUF_OVERFLOW | SDIO_FLAG_BUF_UNDERFLOW | SDIO_FLAG_DATA_CRCERR | SDIO_FLAG_DATA_TIMEOUT | SDIO_FLAG_TRANS_END)

#define HW_SDIO_DATATIMEOUT                    (0x000FFFFF)

void ht32_mmcsd_change(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_SDIO_H__ */
