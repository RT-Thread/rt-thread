#include <rtthread.h>
#include "hal_data.h"

#ifdef BSP_USING_FS

#include <dfs_fs.h>
#include <rtdbg.h>

#define DBG_TAG "app.filesystem"
#define DBG_LVL DBG_INFO

#ifdef BSP_USING_OPENMV
#include "led.h"
#endif /* BSP_USING_OPENMV */

#ifdef BSP_USING_ONCHIP_FS
#include "fal.h"
#define FS_PARTITION_NAME  "disk"

static void sd_mount(void)
{
    struct rt_device *flash_dev = fal_blk_device_create(FS_PARTITION_NAME);

    if (flash_dev == NULL)
    {
        rt_kprintf("Can't create a block device on '%s' partition.\n", FS_PARTITION_NAME);
    }
    else
    {
        rt_kprintf("Create a block device on the %s partition of flash successful.\n", FS_PARTITION_NAME);
    }

    if(rt_device_find(FS_PARTITION_NAME) != RT_NULL)
    {
        dfs_mkfs("elm", FS_PARTITION_NAME);
        if (dfs_mount(FS_PARTITION_NAME, "/", "elm", 0, 0) == RT_EOK)
        {
            rt_kprintf("onchip elm filesystem mount to '/'\n");
        }
        else
        {
            rt_kprintf("onchip elm filesystem mount to '/' failed!\n");
        }
    }
    else
    {
        rt_kprintf("find filesystem portion failed\r\n");
    }
}

#elif defined(BSP_USING_SDCARD_FS)
#include <drv_sdhi.h>

#ifdef SDHI_USING_CD
/* SD Card hot plug detection pin */
#define SD_CHECK_PIN  RA_SDHI_CD_PIN
static rt_base_t sd_check_pin = 0;
#endif

static void _sdcard_mount(void)
{
    rt_device_t device;

    device = rt_device_find("sd");
    rt_kprintf("rt_device_find %x \r\n", device);
    if (device == NULL)
    {
        mmcsd_wait_cd_changed(0);
        sdcard_change();
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

static void _sdcard_unmount(void)
{
    rt_thread_mdelay(200);
    dfs_unmount("/sdcard");
    LOG_I("Unmount \"/sdcard\"");

    mmcsd_wait_cd_changed(0);
    sdcard_change();
    mmcsd_wait_cd_changed(RT_WAITING_FOREVER);
}

static void sd_auto_mount(void *parameter)
{
    rt_uint8_t re_sd_check_pin = 0;
    rt_thread_mdelay(500);

#ifdef SDHI_USING_CD
    if (re_sd_check_pin = rt_pin_read(sd_check_pin))
    {
        _sdcard_mount();
    }

    while (1)
    {
        rt_thread_mdelay(200);
        if (!re_sd_check_pin && (re_sd_check_pin = rt_pin_read(sd_check_pin)) != 0)
        {
#ifdef BSP_USING_OPENMV
            led_state(LED_RED, 1);
#endif  /* BSP_USING_OPENMV */
            _sdcard_mount();
#ifdef BSP_USING_OPENMV
            led_state(LED_RED, 0);
#endif  /* BSP_USING_OPENMV */
        }

        if (re_sd_check_pin && (re_sd_check_pin = rt_pin_read(sd_check_pin)) == 0)
        {
            _sdcard_unmount();
        }
    }
#else
    _sdcard_mount();
#endif  /* SDHI_USING_CD */
}

static void sd_mount(void)
{
    rt_thread_t tid;
#ifdef SDHI_USING_CD
    sd_check_pin = rt_pin_get(SD_CHECK_PIN);
    rt_pin_mode(sd_check_pin, PIN_MODE_INPUT_PULLUP);
#endif  /* SDHI_USING_CD */
    tid = rt_thread_create("sd_mount", sd_auto_mount, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX - 12, 20);
    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        LOG_E("create sd_mount thread err!");
        return;
    }
}

#else
#include <spi_msd.h>
#include "drv_sci_spi.h"
int sd_mount(void)
{
    uint32_t cs_pin = BSP_IO_PORT_10_PIN_05;
    rt_hw_sci_spi_device_attach("scpi2", "scpi20", cs_pin);
    msd_init("sd0", "scpi20");
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
    rt_thread_mdelay(200);
    sd_mount();
    return RT_EOK;
}
INIT_ENV_EXPORT(mount_init);
#endif