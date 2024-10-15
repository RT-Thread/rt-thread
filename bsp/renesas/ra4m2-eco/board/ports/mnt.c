#include <rtthread.h>
#include "hal_data.h"

#ifdef BSP_USING_FS

#include <dfs_fs.h>

#include <dev_spi_msd.h>
#include "drv_sci.h"

#define DBG_TAG "app.filesystem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

void sd_mount(void)
{
    uint32_t cs_pin = BSP_IO_PORT_06_PIN_03;
    rt_hw_sci_spi_device_attach("sci9s", "scpi90", cs_pin);
    msd_init("sd0", "scpi90");
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

int mount_init(void)
{
    sd_mount();
    return RT_EOK;
}
INIT_ENV_EXPORT(mount_init);

#endif  /* BSP_USING_FS */
