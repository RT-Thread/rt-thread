/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-07-19     Magicoe      The first version for LPC55S6x
 */

#ifndef __DRV_SD_H__
#define __DRV_SD_H__

#include <rtthread.h>
#include "rtdef.h"

struct mci_device
{
    struct rt_device                parent;      /**< RT-Thread device struct */
    struct rt_device_blk_geometry   geometry;    /**< sector size, sector count */
    sd_card_t                       card;        /**< Card descriptor */
    rt_event_t finish_event;                     /**< data send finish event*/
    rt_bool_t data_error;                        /**< data send error*/
    struct rt_mutex lock;
};

extern int rt_hw_mci_init(void);

#endif // __DRV_SD_H__
