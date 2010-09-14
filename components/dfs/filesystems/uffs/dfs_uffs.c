#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>

/* mount and unmount file system */
static int dfs_uffs_mount(struct dfs_filesystem* fs, unsigned long rwflag, const void* data)
{
}

static int dfs_uffs_unmount(struct dfs_filesystem* fs)
{
}

static int dfs_uffs_mkfs(const char* device_name)
{
	return -DFS_STATUS_EIO;
}

static int dfs_uffs_statfs(struct dfs_filesystem* fs, struct _statfs *buf)
{
}

static int dfs_uffs_open(struct dfs_fd* fd)
{
}

static int dfs_uffs_close(struct dfs_fd* fd)
{
}

static int dfs_uffs_ioctl(struct dfs_fd* fd, int cmd, void *args)
{
}

static int dfs_uffs_read(struct dfs_fd* fd, void* buf, rt_size_t count)
{
}

static int dfs_uffs_write(struct dfs_fd* fd, const void* buf, rt_size_t count)
{
}

static int dfs_uffs_flush(struct dfs_fd* fd)
{
}

static int dfs_uffs_lseek(struct dfs_fd* fd, rt_off_t offset)
{
}

static int dfs_uffs_getdents(struct dfs_fd* fd, struct _dirent* dirp, rt_uint32_t count)
{
}

static int dfs_uffs_unlink(struct dfs_filesystem* fs, const char* pathname)
{
}

static int dfs_uffs_stat(struct dfs_filesystem* fs, const char* filename, struct _stat* buf)
{
}

static int dfs_uffs_rename(struct dfs_filesystem* fs, const char* oldpath, const char* newpath)
{
}

static const struct dfs_filesystem_operation _uffs = 
{
	"uffs",
	dfs_uffs_mount,
	dfs_uffs_unmount,
	dfs_uffs_mkfs,
	dfs_uffs_statfs,

	dfs_uffs_open,
	dfs_uffs_close,
	dfs_uffs_ioctl,
	dfs_uffs_read,
	dfs_uffs_write,
	dfs_uffs_flush,
	dfs_uffs_lseek,
	dfs_uffs_getdents,
	dfs_uffs_unlink,
	dfs_uffs_stat,
	dfs_uffs_rename,
};

int dfs_uffs_init(void)
{
    /* register UFFS file system */
    return dfs_register(&_uffs);
}
