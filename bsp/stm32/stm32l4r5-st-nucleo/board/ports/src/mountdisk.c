
#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <dfs_fs.h>
#include <fal.h>

#define DBG_TAG    "MOUNT_DISK"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

#define FS_PARTITION_NAME		"filesystem"
#define FS_PATH_NAME			"/"
#define FS_TYPE_NAME			"elm"

static int mount_disk(void)
{	
    fal_init();//初始化 fal 
    
    if (fal_blk_device_create(FS_PARTITION_NAME) == NULL)//如果生成 block 设备失败
    {
        LOG_E("Can't create a block device on '%s' partition.", FS_PARTITION_NAME);
        return(RT_ERROR);
    }

    LOG_I("Create a block device on  %s OK!", FS_PARTITION_NAME);
	
    if (dfs_mount(FS_PARTITION_NAME, FS_PATH_NAME, FS_TYPE_NAME, 0, 0) != 0) //如果挂载文件系统失败
    {
        LOG_E("Failed to initialize filesystem!");
        return(RT_ERROR);
    }
    
    LOG_I("Filesystem initialized!");

	return(RT_EOK);
}
INIT_ENV_EXPORT(mount_disk);

