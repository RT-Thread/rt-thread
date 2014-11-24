/*
 * File      : dfs_romfs.c
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
#include "dfs_romfs.h"

int dfs_romfs_mount(struct dfs_filesystem *fs, unsigned long rwflag, const void *data)
{
	struct romfs_dirent *root_dirent;

	if (data == RT_NULL)
		return -DFS_STATUS_EIO;

	root_dirent = (struct romfs_dirent *)data;
	fs->data = root_dirent;

	return DFS_STATUS_OK;
}

int dfs_romfs_unmount(struct dfs_filesystem *fs)
{
	return DFS_STATUS_OK;
}

int dfs_romfs_ioctl(struct dfs_fd *file, int cmd, void *args)
{
	return -DFS_STATUS_EIO;
}

rt_inline int check_dirent(struct romfs_dirent *dirent)
{
    if ((dirent->type != ROMFS_DIRENT_FILE && dirent->type != ROMFS_DIRENT_DIR)
        || dirent->size == ~0)
        return -1;
    return 0;
}

struct romfs_dirent *dfs_romfs_lookup(struct romfs_dirent *root_dirent, const char *path, rt_size_t *size)
{
	rt_size_t index, found;
	const char *subpath, *subpath_end;
	struct romfs_dirent *dirent;
	rt_size_t dirent_size;

    /* Check the root_dirent. */
    if (check_dirent(root_dirent) != 0)
        return RT_NULL;

	if (path[0] == '/' && path[1] == '\0')
	{
		*size = root_dirent->size;
		return root_dirent;
	}

	/* goto root directy entries */
	dirent = (struct romfs_dirent *)root_dirent->data;
	dirent_size = root_dirent->size;

	/* get the end position of this subpath */
	subpath_end = path;
	/* skip /// */
	while (*subpath_end && *subpath_end == '/')
		subpath_end ++;
	subpath = subpath_end;
	while ((*subpath_end != '/') && *subpath_end)
		subpath_end ++;

	while (dirent != RT_NULL)
	{
		found = 0;

		/* search in folder */
		for (index = 0; index < dirent_size; index ++)
		{
            if (check_dirent(&dirent[index]) != 0)
                return RT_NULL;
			if (rt_strncmp(dirent[index].name, subpath, (subpath_end - subpath)) == 0)
			{
				dirent_size = dirent[index].size;

				/* skip /// */
				while (*subpath_end && *subpath_end == '/')
					subpath_end ++;
				subpath = subpath_end;
				while ((*subpath_end != '/') && *subpath_end)
					subpath_end ++;

				if (!(*subpath))
				{
					*size = dirent_size;
					return &dirent[index];
				}

				if (dirent[index].type == ROMFS_DIRENT_DIR)
				{
					/* enter directory */
					dirent = (struct romfs_dirent*)dirent[index].data;
					found = 1;
					break;
				}
				else
				{
					/* return file dirent */
					if (subpath != RT_NULL)
						break; /* not the end of path */

					return &dirent[index];
				}
			}
		}

		if (!found)
			break; /* not found */
	}

	/* not found */
	return RT_NULL;
}

int dfs_romfs_read(struct dfs_fd *file, void *buf, rt_size_t count)
{
	rt_size_t length;
	struct romfs_dirent *dirent;

	dirent = (struct romfs_dirent *)file->data;
	RT_ASSERT(dirent != RT_NULL);

    if (check_dirent(dirent) != 0)
    {
        return -DFS_STATUS_EIO;
    }

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

int dfs_romfs_lseek(struct dfs_fd *file, rt_off_t offset)
{
	if (offset <= file->size)
	{
		file->pos = offset;
		return file->pos;
	}

	return -DFS_STATUS_EIO;
}

int dfs_romfs_close(struct dfs_fd *file)
{
	file->data = RT_NULL;
	return DFS_STATUS_OK;
}

int dfs_romfs_open(struct dfs_fd *file)
{
	rt_size_t size;
	struct romfs_dirent *dirent;
	struct romfs_dirent *root_dirent;

	root_dirent = (struct romfs_dirent *)file->fs->data;

    if (check_dirent(root_dirent) != 0)
        return -DFS_STATUS_EIO;

	if (file->flags & (DFS_O_CREAT | DFS_O_WRONLY | DFS_O_APPEND | DFS_O_TRUNC | DFS_O_RDWR))
		return -DFS_STATUS_EINVAL;

	dirent = dfs_romfs_lookup(root_dirent, file->path, &size);
	if (dirent == RT_NULL)
		return -DFS_STATUS_ENOENT;

	/* entry is a directory file type */
	if (dirent->type == ROMFS_DIRENT_DIR)
	{
		if (!(file->flags & DFS_O_DIRECTORY))
			return -DFS_STATUS_ENOENT;
	}
	else
	{
		/* entry is a file, but open it as a directory */
		if (file->flags & DFS_O_DIRECTORY)
			return -DFS_STATUS_ENOENT;
	}

	file->data = dirent;
	file->size = size;
	file->pos = 0;

	return DFS_STATUS_OK;
}

int dfs_romfs_stat(struct dfs_filesystem *fs, const char *path, struct stat *st)
{
	rt_size_t size;
	struct romfs_dirent *dirent;
	struct romfs_dirent *root_dirent;

	root_dirent = (struct romfs_dirent *)fs->data;
	dirent = dfs_romfs_lookup(root_dirent, path, &size);

	if (dirent == RT_NULL)
		return -DFS_STATUS_ENOENT;

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

int dfs_romfs_getdents(struct dfs_fd *file, struct dirent *dirp, rt_uint32_t count)
{
	rt_size_t index;
	const char *name;
	struct dirent *d;
	struct romfs_dirent *dirent, *sub_dirent;

	dirent = (struct romfs_dirent *)file->data;
    if (check_dirent(dirent) != 0)
        return -DFS_STATUS_EIO;
	RT_ASSERT(dirent->type == ROMFS_DIRENT_DIR);

	/* enter directory */
	dirent = (struct romfs_dirent *)dirent->data;

	/* make integer count */
	count = (count / sizeof(struct dirent));
	if (count == 0)
		return -DFS_STATUS_EINVAL;

	index = 0;
	for (index = 0; index < count && file->pos < file->size; index ++)
	{
		d = dirp + index;

		sub_dirent = &dirent[file->pos];
		name = sub_dirent->name;

		/* fill dirent */
		if (sub_dirent->type == ROMFS_DIRENT_DIR)
			d->d_type = DFS_DT_DIR;
		else
			d->d_type = DFS_DT_REG;

		d->d_namlen = rt_strlen(name);
		d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
		rt_strncpy(d->d_name, name, rt_strlen(name) + 1);

		/* move to next position */
		++ file->pos;
	}

	return index * sizeof(struct dirent);
}

static const struct dfs_filesystem_operation _romfs =
{
	"rom",
	DFS_FS_FLAG_DEFAULT,
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
INIT_FS_EXPORT(dfs_romfs_init);

