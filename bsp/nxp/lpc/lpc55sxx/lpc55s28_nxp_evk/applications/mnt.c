/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *  sdio filesystem support
 * Change Logs:
 * Date         Author        Notes
 * 2021-10-10   supperthomas  first version
 */
#include "dfs_fs.h"
#include <rtthread.h>
#include <rtdevice.h>

#ifdef BSP_USING_SDIO

/**
  * @brief  SDIO filesystem init
  * @param  void
  * @retval 0: filesystem init success, -1: filesystem init failed
  */

static int sdio_fs_init(void)
{
    int result = 0;
    dfs_mount("sdcard0", "/", "elm", 0, 0);
    return result;
}

INIT_ENV_EXPORT(sdio_fs_init);

#endif /* BSP_USING_SDIO */
