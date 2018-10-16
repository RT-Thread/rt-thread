#include <rtthread.h>
#include <dfs_fs.h>
#include <dfs_romfs.h>

static int _dfsmount(const char   *device_name,
					 const char   *path,
					 const char   *filesystemtype)
{
	int ret = dfs_mount(device_name, path, filesystemtype, 0, RT_NULL);
	if(ret != 0)
	{
		ret = dfs_mkfs(filesystemtype, device_name);
		if(ret != 0)
		{
			rt_kprintf("on %s mkfs with %s failed!\n", device_name, filesystemtype);
			return -1;
		}
		ret = dfs_mount(device_name, path, filesystemtype, 0, RT_NULL);
		if(ret != 0)
		{
			rt_kprintf("%s mount to %s failed!\n", device_name, path);
			return -2;
		}	
	}
    rt_kprintf("%s mount to %s !\n", device_name, path);
	return 0;
}

int init_rom_filesystem(void)
{
	rt_thread_delay(RT_TICK_PER_SECOND);
	static const struct romfs_dirent _romfs_root[] = {
		{ROMFS_DIRENT_DIR, "udisk", RT_NULL, 0},
		{ROMFS_DIRENT_DIR, "spi", RT_NULL, 0},
		{ROMFS_DIRENT_DIR, "sdcard", RT_NULL, 0},
		{ROMFS_DIRENT_DIR, "nand", RT_NULL, 0}
	};

	static const struct romfs_dirent romfs_root = {
		ROMFS_DIRENT_DIR, "/", (rt_uint8_t *)_romfs_root, sizeof(_romfs_root)/sizeof(_romfs_root[0])
	};

	if (dfs_mount(RT_NULL, "/", "rom", 0, &(romfs_root)) == 0)
	{
		rt_kprintf("ROM file system initializated!\n");
	}
	else			
	{
		rt_kprintf("ROM file system failed!\n");
	}
    /* mount sd card fat partition 0 as root directory */
    _dfsmount("flash0", "/spi", "elm");
	_dfsmount("nand0", "/nand", "uffs");
    
    /* mount sd card fat partition 0 as root directory */
    if (dfs_mount("sd0", "/sdcard", "elm", 0, 0) == 0)
    {
        rt_kprintf("sd card mount to /sdcard!\n");        
    }
    else
    {
        rt_kprintf("sd card mount to /sdcard failed!\n");
    }
	return 0;
}
INIT_ENV_EXPORT(init_rom_filesystem);
