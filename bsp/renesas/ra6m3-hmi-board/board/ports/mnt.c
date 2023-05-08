#include <rtthread.h>
#include "hal_data.h"

#ifdef BSP_USING_FS

#include <dfs_fs.h>

#define DBG_TAG "app.filesystem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef BSP_USING_SDCARD_FS
#include <drv_sdhi.h>
static void _sdcard_mount(void)
{
    rt_device_t device;

    device = rt_device_find("sd");

    if (device == NULL)
    {
        mmcsd_wait_cd_changed(0);
        mmcsd_wait_cd_changed(RT_WAITING_FOREVER);
        device = rt_device_find("sd");
    }

    if (device != RT_NULL)
    {
        if (dfs_mount("sd", "/", "elm", 0, 0) == RT_EOK)
        {
            LOG_I("sd card mount to '/'");
        }
        else
        {
            LOG_W("sd card mount to '/' failed!");
        }
    }
}

static void sd_mount(void)
{
    rt_thread_mdelay(200);

    _sdcard_mount();
}

#else
#include <spi_msd.h>
#include "drv_sci_spi.h"
int sd_mount(void)
{
    uint32_t cs_pin = BSP_IO_PORT_06_PIN_11;
    rt_hw_sci_spi_device_attach("scpi7", "scpi70", cs_pin);
    msd_init("sd0", "scpi70");
    if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    {
        LOG_I("Mount \"/dev/sd0\" on \"/\"\n");
    }
    else
    {
        LOG_W("sd card mount to '/' failed!");
    }
    return 0;
}
#endif /* BSP_USING_SDCARD_FS */

int mount_init(void)
{
    sd_mount();
    return RT_EOK;
}
INIT_ENV_EXPORT(mount_init);
#endif
