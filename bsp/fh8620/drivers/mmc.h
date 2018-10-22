/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef MMC_H_
#define MMC_H_

#include "libraries/inc/fh_driverlib.h"
#define MMC_FEQ_MIN 100000
#define MMC_FEQ_MAX 50000000

#define CARD_UNPLUGED   1
#define CARD_PLUGED     0

struct mmc_driver
{
    MMC_DMA_Descriptors* dma_descriptors;
    rt_uint32_t max_desc;
    struct rt_mmcsd_host *host;
    struct rt_mmcsd_req *req;
    struct rt_mmcsd_data *data;
    struct rt_mmcsd_cmd *cmd;
    struct rt_completion transfer_completion;
    void*  priv;
};

void rt_hw_mmc_init(void);

#endif /* MMC_H_ */
