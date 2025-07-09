/*****************************************************************************
* File Name      : sysinit.c
* Author         : Inhand Embedded Team
* Description    :
* Copyright      :
* Website        : https://www.inhand.com.cn
******************************************************************************
* modification history :
* liliang created on 2019-10-27 16:27:52
******************************************************************************/
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <dfs_posix.h>
#include "drv_gpio.h"
#include "drv_spi.h"
#include "fal.h"



#if defined(RT_USING_SFUD)
    #include <spi_flash_sfud.h>
#endif /* defined(RT_USING_SFUD) */

#undef LOG_TAG
#define  LOG_TAG    "sysinit"

/******************************************************************************/
#define DEFAULT_WDT_TIMEOUT_S                   60
#define GET_SPI_FLASH_CS_PIN()                  GET_PIN(3, 28)// GPIO_SD_B0_01_GPIO3_IO13

/******************************************************************************/
/******************************************************************************/

/******************************************************************************/

/**
 * @brief 初始化FLA分区管理
 * 
 * @return int 
 */
int __init_fal(void)
{
    return fal_init();
}
INIT_COMPONENT_EXPORT(__init_fal);


#if defined(BSP_USING_SPI_FLASH)
/**
 * @brief 初始化SPI FALSH
 * 
 * @return int 
 */
int __init_spi_flash(void)
{
    rt_hw_spi_device_attach(BSP_SPI_FLASH_SPI_BUS, BSP_SPI_FLASH_BUS_NAME, GET_SPI_FLASH_CS_PIN());
    
#if defined(RT_USING_SFUD)
    if(RT_NULL == rt_sfud_flash_probe(BSP_SPI_FLASH_DEV_NAME, BSP_SPI_FLASH_BUS_NAME))
    {
        LOG_E("rt_sfud_flash_probe error.");
        return -RT_ERROR;
    }
#endif /* RT_USING_SFUD */
    return RT_EOK;
}
INIT_PREV_EXPORT(__init_spi_flash);
#endif

#define FS_PARTITION_NAME   "Littlefs"
int __init_lfs(void)
{
    int ret = RT_EOK;
    DIR *dirp = RT_NULL;
    /* 生成SPI块设备 */
    struct rt_device *mtd_dev = RT_NULL;
    mtd_dev = fal_mtd_nor_device_create(FS_PARTITION_NAME);
    if(!mtd_dev)
    {
        LOG_E("Can't create a mtd device on '%s' partition.", FS_PARTITION_NAME);
        return -RT_ERROR;
    }
    /* 挂载lfs文件系统 */
    ret = dfs_mount(FS_PARTITION_NAME, "/", "lfs", 0, RT_NULL);
    if(ret)
    {
        /* 格式化lfs文件系统 */
        ret = dfs_mkfs("lfs", FS_PARTITION_NAME);
        if(ret)
        {
            LOG_E("Format %s failed, ret = %d",FS_PARTITION_NAME, ret);
            return ret;
        }
        else
        {
            LOG_I("Format "FS_PARTITION_NAME" ok!");
        }

        /* 挂载lfs文件系统 */
        ret = dfs_mount(FS_PARTITION_NAME, "/", "lfs", 0, RT_NULL);
        if(ret)
        {
            LOG_E("Failed to mount %s, ret = %d",FS_PARTITION_NAME, ret);
            return ret;
        }
        else
        {
            LOG_I("Mount "FS_PARTITION_NAME" OK!");
        }
    }
    else
    {
        log_i("Mount "FS_PARTITION_NAME" OK!");
    }    
    return ret;
}
INIT_APP_EXPORT(__init_lfs);



/* End of file****************************************************************/
