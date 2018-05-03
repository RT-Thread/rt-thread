/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
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
