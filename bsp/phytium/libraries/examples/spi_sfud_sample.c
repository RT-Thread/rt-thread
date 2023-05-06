/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-11-20  liqiaozhong  first commit
 * 2022-03-08  liqiaozhong  add format function and mount table
 */
#include <rtthread.h>
#include <string.h>

#if defined (RT_USING_SFUD) && defined(RT_USING_DFS)

#include <dfs_fs.h>
#include <dfs_file.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include "spi_flash.h"
#include "spi_flash_sfud.h"

#include "fdebug.h"
#include "fparameters_comm.h"

#include "fspim.h"
/************************** Variable Definitions *****************************/
sfud_flash_t spim_flash = RT_NULL;
const struct dfs_mount_tbl mount_table[] =
{
    { "flash2", "/", "elm", 0, RT_NULL },
    {0},
};
/***************** Macros (Inline Fungoctions) Definitions *********************/
#define FSPIM_DEBUG_TAG "SPIM"
#define FSPIM_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_WARN(format, ...)   FT_DEBUG_PRINT_W(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_INFO(format, ...)    FT_DEBUG_PRINT_I(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSPIM_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSPIM_DEBUG_TAG, format, ##__VA_ARGS__)

/*******************************Api Functions*********************************/
static int spi_flash_sfud_init(void)
{
    if (RT_NULL == rt_sfud_flash_probe("flash2", "spi02"))
    {
        rt_kprintf("rt_sfud_flash_probe failed\n");
        return RT_ERROR;
    }
    spim_flash = rt_sfud_flash_find_by_dev_name("flash2");
    if (RT_NULL == spim_flash)
    {
        rt_kprintf("Flash init failed -> can't find flash2 device!\n");
        return RT_ERROR;
    }
    rt_kprintf("Spi flash device flash2 init\n");
    rt_kprintf("Flash device: flash2 info\nmf_id: 0x%x\ntype_id: 0x%x\ncapacity_id: 0x%x\nerase granularity: %lu\n",
    spim_flash->chip.mf_id,
    spim_flash->chip.type_id,
    spim_flash->chip.capacity_id,
    spim_flash->chip.erase_gran);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(spi_flash_sfud_init);

/* format the flash with elm environment */
static int flash_format_operation(void)
{
    int result = RT_EOK;
    result = dfs_mkfs("elm", "flash2");
    return result;
}
INIT_ENV_EXPORT(flash_format_operation);

#endif /* RT_USING_SFUD || RT_USING_DFS */
