#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>
#include "dfs_romfs.h"

int dfs_romfs_mount(struct dfs_filesystem* fs, unsigned long rwflag, const void* data)
{
	struct romfs_dirent* root_dirent;

	if (data == RT_NULL) return -DFS_STATUS_EIO;

	root_dirent = (struct romfs_dirent*)data;
	fs->data = root_dirent;

	return DFS_STATUS_OK;
}

int dfs_romfs_unmount(struct dfs_filesystem* fs)
{
	return DFS_STATUS_OK;
}

int dfs_romfs_ioctl(struct dfs_fd* file, int cmd,	void* args)
{
	return -DFS_STATUS_EIO;
}

struct romfs_dirent* dfs_romfs_lookup(struct romfs_dirent* root_dirent, const char* path)
{
	rt_size_t index;
	const char *subpath, *subpath_end;
	struct romfs_dirent* dirent;

	dirent = root_dirent;

	if (path[0] == '/' && path[1] == '\0') return dirent;

	/* get the end position of this subpath */
	subpath_end = path;
	/* skip /// */
	while (*subpath_end && *subpath_end == '/') subpath_end ++;
	subpath = subpath_end;
	while ((*subpath_end != '/') && *subpath_end) subpath_end ++;

	while (dirent != RT_NULL)
	{
		/* search in folder */
		for (index = 0; index < dirent->size; index ++)
		{
			if (rt_strncmp(dirent[index].name, subpath, (subpath_end - subpath)) == 0)
			{
				/* skip /// */
				while (*subpath_end && *subpath_end == '/') subpath_end ++;
				subpath = subpath_end;
				while ((*subpath_end != '/') && *subpath_end) subpath_end ++;

				if (!(*subpath)) return dirent;

				if (dirent[index].type == ROMFS_DIRENT_DIR)
				{
					dirent = (struct romfs_dirent*)dirent[index].data;
					break;
				}
				else return dirent;
			}
		}
	}

	/* not found */
	return RT_NULL;
}

int dfs_romfs_read(struct dfs_fd* file, void *buf, rt_size_t count)
{
	rt_size_t length;
	struct romfs_dirent* dirent;

	dirent = (struct romfs_dirent *)file->data;
	RT_ASSERT(dirent != RT_NULL);

	if (count < file->size - file->pos)
		length = count;
	else
		length = file->size - file->pos;

	if (length > 0)
		memcpy(buf, &(dirent->data[file->pos]), length);

	return length;
}

int dfs_romfs_lseek(struct dfs_fd* file, rt_off_t offset)
{
	if (offset < file->size)
	{
		file->pos = offset;
		return file->pos;
	}

	return -DFS_STATUS_EIO;
}

int dfs_romfs_close(struct dfs_fd* file)
{
	file->data = RT_NULL;
	return DFS_STATUS_OK;
}

int dfs_romfs_open(struct dfs_fd* file)
{
	struct romfs_dirent* root_dirent;
	struct romfs_dirent* dirent;

	root_dirent = (struct romfs_dirent*)file->fs->data;

	if (file->flags & (DFS_O_CREAT | DFS_O_WRONLY | DFS_O_APPEND | DFS_O_TRUNC | DFS_O_RDWR))
		return -DFS_STATUS_EINVAL;

	dirent = dfs_romfs_lookup(root_dirent, file->path);
	if (dirent == RT_NULL) return -DFS_STATUS_ENOENT;

	if (file->flags & DFS_O_DIRECTORY)
		file->data = dirent;

	file->size = dirent->size;
	file->pos = 0;
	return DFS_STATUS_OK;
}

int dfs_romfs_stat(struct dfs_filesystem* fs, const char *path, struct _stat *st)
{
	struct romfs_dirent* root_dirent;
	struct romfs_dirent* dirent;

	root_dirent = (struct romfs_dirent*)fs->data;
	dirent = dfs_romfs_lookup(root_dirent, path);

	if (dirent == RT_NULL) return -DFS_STATUS_ENOENT;

	st->st_dev = 0;
	st->st_mode = DFS_S_IFREG | DFS_S_IRUSR | DFS_S_IRGRP | DFS_S_IROTH |
	DFS_S_IWUSR | DFS_S_IWGRP | DFS_S_IWOTH;
	if (dirent->type == ROMFS_DIRENT_DIR)
	{
		st->st_mode &= ~DFS_S_IFREG;
		st->st_mode |= DFS_S_IFDIR | DFS_S_IXUSR | DFS_S_IXGRP | DFS_S_IXOTH;
	}

	st->st_size = dirent->size;
	st->st_mtime = 0;
	st->st_blksize = 512;

	return DFS_STATUS_OK;
}

int dfs_romfs_getdents(struct dfs_fd* file, struct _dirent* dirp, rt_uint32_t count)
{
	rt_size_t index;
	const char *name;
	struct _dirent* d;
	struct romfs_dirent *dirent, *sub_dirent;

	dirent = (struct romfs_dirent*) file->data;

	/* make integer count */
	count = (count / sizeof(struct _dirent)) * sizeof(struct _dirent);
	if ( count == 0 ) return -DFS_STATUS_EINVAL;
	
	index = 0;
	sub_dirent = &dirent[file->pos];
	for (index = 0; index < count; index ++)
	{
		d = dirp + index;

		sub_dirent = &dirent[file->pos];
		name = sub_dirent->name;

		/* fill dirent */
		d->d_type &= DFS_DT_REG;
		d->d_namlen = rt_strlen(name);
		d->d_reclen = (rt_uint16_t)sizeof(struct _dirent);
		rt_strncpy(d->d_name, name, rt_strlen(name) + 1);

		/* move to next position */
		++ file->pos; 
		if (file->pos > file->size) break;
	}

	return index * sizeof(struct _dirent);
}

static const struct dfs_filesystem_operation _romfs = 
{
	"rom",
	dfs_romfs_mount,
	dfs_romfs_unmount,
	RT_NULL,
	RT_NULL,

	dfs_romfs_open,
	dfs_romfs_close,
	dfs_romfs_ioctl,
	dfs_romfs_read,
	RT_NULL,
	RT_NULL,
	dfs_romfs_lseek,
	dfs_romfs_getdents,
	RT_NULL,
	dfs_romfs_stat,
	RT_NULL,
};

int dfs_romfs_init(void)
{
    /* register rom file system */
    dfs_register(&_romfs);
	return 0;
}

