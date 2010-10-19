/*
 * A skeleton of file system in Device File System
 */
#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>

#include "dfs_skt_fs.h"

int dfs_skt_mount(struct dfs_filesystem* fs, unsigned long rwflag, const void* data)
{
	return DFS_STATUS_OK;
}

int dfs_skt_unmount(struct dfs_filesystem* fs)
{
	return DFS_STATUS_OK;
}

int dfs_skt_ioctl(struct dfs_fd* file, int cmd,	void* args)
{
	return -DFS_STATUS_EIO;
}

int dfs_skt_read(struct dfs_fd* file, void *buf, rt_size_t count)
{
	return count;
}

int dfs_skt_lseek(struct dfs_fd* file, rt_off_t offset)
{
	return -DFS_STATUS_EIO;
}

int dfs_skt_close(struct dfs_fd* file)
{
	return DFS_STATUS_OK;
}

int dfs_skt_open(struct dfs_fd* file)
{
	return DFS_STATUS_OK;
}

int dfs_skt_stat(struct dfs_filesystem* fs, const char *path, struct stat *st)
{
	return DFS_STATUS_OK;
}

int dfs_skt_getdents(struct dfs_fd* file, struct dirent* dirp, rt_uint32_t count)
{
	return count * sizeof(struct dirent);
}

static const struct dfs_filesystem_operation _skt_fs = 
{
	"skt",
	dfs_skt_mount,
	dfs_skt_unmount,
	RT_NULL,
	RT_NULL,

	dfs_skt_open,
	dfs_skt_close,
	dfs_skt_ioctl,
	dfs_skt_read,
	RT_NULL,
	RT_NULL,
	dfs_skt_lseek,
	dfs_skt_getdents,
	RT_NULL,
	dfs_skt_stat,
	RT_NULL,
};

int dfs_skt_init(void)
{
    /* register rom file system */
    dfs_register(&_skt_fs);
	return 0;
}
