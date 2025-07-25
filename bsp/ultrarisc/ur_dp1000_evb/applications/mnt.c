
#include <rtthread.h>
#include <rtconfig.h>
#include <dev_spi_msd.h>
#include <dfs_fs.h>

int mnt_init(void)
{
    msd_init("sd0", "spi00");

    if (dfs_mount("sd0", "/", "ext", 0, 0) == 0)
    {
        rt_kprintf("Mount \"/dev/sd0p1\" on \"/\"\n");
    }
    else if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("Mount \"/dev/sd0p1\" on \"/\"\n");
    }
    return 0;
}
INIT_ENV_EXPORT(mnt_init);