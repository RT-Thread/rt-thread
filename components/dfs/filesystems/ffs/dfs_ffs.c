/*
 * File      : dfs_ffs.c
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2011, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>
#include "dfs_ffs.h"
#include "fs.h"
#include "fs.h"
#include "fsdata.h"
#include "file/filedata.h"

int dfs_ffs_mount(struct dfs_filesystem *fs, unsigned long rwflag, const void *data)
{
	struct fsdata_file *root_dirent;

	if (data == RT_NULL)	
		root_dirent = (struct fsdata_file*)&FS_ROOT;
	else
		root_dirent = (struct fsdata_file*)data;
	fs->data = root_dirent;

	return DFS_STATUS_OK;
}

int dfs_ffs_unmount(struct dfs_filesystem *fs)
{
	return DFS_STATUS_OK;
}

int dfs_ffs_ioctl(struct dfs_fd *file, int cmd, void *args)
{
	return -DFS_STATUS_EIO;
}

struct fsdata_file *dfs_ffs_lookup(struct fsdata_file *root_dirent, const char *path, rt_size_t *size)
{


	const struct fsdata_file *f;
	*size=0;
	if(path[0]=='/' && path[0]==0)
	{
		for(f = FS_ROOT; f != NULL; f = f->next){
			*size=*size+f->len;
	 	}
		return (struct fsdata_file *) FS_ROOT;
	}
	else
	{
	     for(f = FS_ROOT; f != NULL; f = f->next) {
			if (!strcmp((char *)f->name,path))
			{
				*size=f->len;
				return (struct fsdata_file *) f;
			}
		}
	}
	/* not found */
	return RT_NULL;
}

int dfs_ffs_read(struct dfs_fd *file, void *buf, rt_size_t count)
{
	rt_size_t length;
	struct fsdata_file *dirent;

	dirent = (struct fsdata_file *)file->data;
	RT_ASSERT(dirent != RT_NULL);

	if (count < file->size - file->pos)
		length = count;
	else
		length = file->size - file->pos;

	if (length > 0)
		memcpy(buf, &(dirent->data[file->pos]), length);

	/* update file current position */
	file->pos += length;

	return length;
}

int dfs_ffs_lseek(struct dfs_fd *file, rt_off_t offset)
{
	if (offset <= file->size)
	{
		file->pos = offset;
		return file->pos;
	}

	return -DFS_STATUS_EIO;
}

int dfs_ffs_close(struct dfs_fd *file)
{
	file->data = RT_NULL;
	return DFS_STATUS_OK;
}

int dfs_ffs_open(struct dfs_fd *file)
{
	rt_size_t size;
	struct fsdata_file *dirent;
	struct fsdata_file *root_dirent;

	root_dirent = (struct fsdata_file *)file->fs->data;

	if (file->flags & (DFS_O_CREAT | DFS_O_WRONLY | DFS_O_APPEND | DFS_O_TRUNC | DFS_O_RDWR))
		return -DFS_STATUS_EINVAL;

	dirent = dfs_ffs_lookup(root_dirent, file->path, &size);
	if (dirent == RT_NULL)
		return -DFS_STATUS_ENOENT;

	/* entry is a file, but open it as a directory */
	if (file->flags & DFS_O_DIRECTORY)
		return -DFS_STATUS_ENOENT;

	file->data = dirent;
	file->size = size;
	file->pos = 0;

	return DFS_STATUS_OK;
}

int dfs_ffs_stat(struct dfs_filesystem *fs, const char *path, struct stat *st)
{
	rt_size_t size;
	struct fsdata_file *dirent;
	struct fsdata_file *root_dirent;

	root_dirent = (struct fsdata_file *)fs->data;
	dirent = dfs_ffs_lookup(root_dirent, path, &size);

	if (dirent == RT_NULL)
		return -DFS_STATUS_ENOENT;

	st->st_dev = 0;
	st->st_mode = DFS_S_IFREG | DFS_S_IRUSR | DFS_S_IRGRP | DFS_S_IROTH |
	DFS_S_IWUSR | DFS_S_IWGRP | DFS_S_IWOTH;

	st->st_size = dirent->len;
	st->st_mtime = 0;
	st->st_blksize = 512;

	return DFS_STATUS_OK;
}

int dfs_ffs_getdents(struct dfs_fd *file, struct dirent *dirp, rt_uint32_t count)
{
	rt_size_t index;
	const char *name;
	struct dirent *d;
	struct fsdata_file *dirent, *sub_dirent;

	dirent = (struct fsdata_file *)file->data;
	RT_ASSERT(dirent->type == FFS_DIRENT_DIR);

	/* enter directory */
	dirent = (struct fsdata_file *)dirent->data;
	
	/* make integer count */
	count = (count / sizeof(struct dirent));
	if (count == 0)
		return -DFS_STATUS_EINVAL;
	
	index = 0;
	for (index = 0; index < count && file->pos < file->size; index ++)
	{
		d = dirp + index;

		sub_dirent = &dirent[file->pos];
		name = (const char *)sub_dirent->name;


			d->d_type = DFS_DT_REG;

		d->d_namlen = rt_strlen(name);
		d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
		rt_strncpy(d->d_name, name, rt_strlen(name) + 1);

		/* move to next position */
		++ file->pos; 
	}

	return index * sizeof(struct dirent);
}

static const struct dfs_filesystem_operation _ffs = 
{
	"ffs",
	DFS_FS_FLAG_DEFAULT,
	dfs_ffs_mount,
	dfs_ffs_unmount,
	RT_NULL,
	RT_NULL,

	dfs_ffs_open,
	dfs_ffs_close,
	dfs_ffs_ioctl,
	dfs_ffs_read,
	RT_NULL,
	RT_NULL,
	dfs_ffs_lseek,
	dfs_ffs_getdents,
	RT_NULL,
	dfs_ffs_stat,
	RT_NULL,
};

int dfs_ffs_init(void)
{
    /* register rom file system */
    dfs_register(&_ffs);
	return 0;
}
INIT_FS_EXPORT(dfs_ffs_init);

