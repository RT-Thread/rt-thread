/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-21     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtdm.mnt"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <stdlib.h>
#include <dfs_fs.h>
#ifdef RT_USING_FINSH
#include <msh.h>
#endif
#include <ioremap.h>

#ifdef RT_USING_OFW
#define bootargs_select rt_ofw_bootargs_select
#define memregion_request rt_fdt_commit_memregion_request
#else
#error Platform have not kernel parameters select interfaces!
#endif

static int rootfs_mnt_init(void)
{
    rt_err_t err = -RT_ERROR;
    void *fsdata = RT_NULL;
    const char *cromfs_type = "crom";
    const char *dev = bootargs_select("root=", 0);
    const char *fstype = bootargs_select("rootfstype=", 0);
    const char *rw = bootargs_select("rw", 0);

    if (!dev || !fstype)
    {
        const char *name = "initrd";
        rt_size_t mem_region_nr;
        rt_region_t *mem_region;
        rt_uint64_t initrd_start = 0, initrd_end = 0;

        if (!memregion_request(&mem_region, &mem_region_nr, RT_TRUE))
        {
            while (mem_region_nr-- > 0)
            {
                if (mem_region->name == name || !rt_strcmp(mem_region->name, name))
                {
                    initrd_start = mem_region->start;
                    initrd_end = mem_region->end;

                    break;
                }

                mem_region++;
            }
        }

        if (initrd_start && initrd_end)
        {
            size_t initrd_size = initrd_end - initrd_start;

            if ((fsdata = rt_ioremap_cached((void *)initrd_start, initrd_size)))
            {
                fstype = cromfs_type;
            }
        }
    }

    if (fstype != cromfs_type && dev)
    {
        rt_tick_t timeout = 0;
        const char *rootwait, *rootdelay = RT_NULL;

        rootwait = bootargs_select("rootwait", 0);

        /* Maybe it is undefined or 'rootwaitABC' */
        if (!rootwait || *rootwait)
        {
            rootdelay = bootargs_select("rootdelay=", 0);

            if (rootdelay)
            {
                timeout = rt_tick_from_millisecond(atoi(rootdelay));
            }

            rootwait = RT_NULL;
        }

        /*
         * Delays in boot flow is a terrible behavior in RTOS, but the RT-Thread
         * SDIO framework init the devices in a task that we need to wait for
         * SDIO devices to init complete...
         *
         * WHAT THE F*CK PROBLEMS WILL HAPPENED?
         *
         * Your main PE, applications, services that depend on the root FS and
         * the multi cores setup, init will delay, too...
         *
         * So, you can try to link this function to `INIT_APP_EXPORT` even later
         * and remove the delays if you want to optimize the boot time and mount
         * the FS auto.
         */
        for (; rootdelay || rootwait; --timeout)
        {
            if (!rootwait && timeout == 0)
            {
                LOG_E("Wait for /dev/%s init time out", dev);

                /*
                 * We don't return at once because the device driver may init OK
                 * when we break from this point, might as well give it another
                 * try.
                 */
                break;
            }

            if (rt_device_find(dev))
            {
                break;
            }

            rt_thread_mdelay(1);
        }
    }

    if (fstype)
    {
        if (!(err = dfs_mount(dev, "/", fstype, rw ? 0 : ~0, fsdata)))
        {
            LOG_I("Mount root %s%s type=%s %s",
                (dev && *dev) ? "on /dev/" : "",
                (dev && *dev) ? dev : "\b",
                fstype, "done");
        }
        else
        {
            LOG_W("Mount root %s%s type=%s %s",
                (dev && *dev) ? "on /dev/" : "",
                (dev && *dev) ? dev : "\b",
                fstype, "fail");

            if (fstype == cromfs_type)
            {
                rt_iounmap(fsdata);
            }
        }
    }

    return 0;
}
INIT_ENV_EXPORT(rootfs_mnt_init);

static int fstab_mnt_init(void)
{
    mkdir("/mnt", 0755);

#ifdef RT_USING_FINSH
    /* Try mount by table */
    msh_exec_script("fstab.sh", 16);
#endif

    LOG_I("File system initialization done");

    return 0;
}
INIT_FS_EXPORT(fstab_mnt_init);
