/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#include <fal.h>
#include <rtdevice.h>

#define DBG_TAG "FAL"
#ifdef FAL_USING_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_WARNING
#endif
#include <rtdbg.h>

static rt_uint8_t init_ok = 0;

/**
 * FAL (Flash Abstraction Layer) initialization.
 * It will initialize all flash device and all flash partition.
 *
 * @return >= 0: partitions total number
 */
int fal_init(void)
{
    extern int fal_flash_init(void);
    extern int fal_partition_init(void);

    int result;

    /* initialize all flash device on FAL flash table */
    result = fal_flash_init();

    if (result < 0) {
        goto __exit;
    }

    /* initialize all flash partition on FAL partition table */
    result = fal_partition_init();

__exit:

    if ((result > 0) && (!init_ok))
    {
        init_ok = 1;
        LOG_I("RT-Thread Flash Abstraction Layer initialize success.");
    }
    else if(result <= 0)
    {
        init_ok = 0;
        LOG_E("RT-Thread Flash Abstraction Layer initialize failed.");
    }

    return result;
}

/**
 * Check if the FAL is initialized successfully
 *
 * @return 0: not init or init failed; 1: init success
 */
int fal_init_check(void)
{
    return init_ok;
}
