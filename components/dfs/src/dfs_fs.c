/*
 * File      : dfs_fs.c
 * This file is part of Device File System in RT-Thread RTOS
 * COPYRIGHT (C) 2004-2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2005-02-22     Bernard      The first version.
 * 2010-06-30     Bernard      Optimize for RT-Thread RTOS
 * 2011-03-12     Bernard      fix the filesystem lookup issue.
 */

#include <dfs_fs.h>
#include <dfs_file.h>

/**
 * @addtogroup FsApi
 */
/*@{*/

/**
 * this function will register a file system instance to device file system.
 *
 * @param ops the file system instance to be registered.
 *
 * @return 0 on successful, -1 on failed.
 */
int dfs_register(const struct dfs_filesystem_operation *ops)
{
	int index, result;

	result = 0;

	/* lock filesystem */
	dfs_lock();

	/* check if this filesystem was already registered */
	for (index = 0; index < DFS_FILESYSTEM_TYPES_MAX; index++)
	{
		if (filesystem_operation_table[index] != RT_NULL &&
			strcmp(filesystem_operation_table[index]->name, ops->name) == 0)
		{
			result = -1;
			goto err;
		}
	}

	/* find out an empty filesystem type entry */
	for (index = 0; index < DFS_FILESYSTEM_TYPES_MAX && filesystem_operation_table[index] != RT_NULL;
		index++) ;

	/* filesystem type table full */
	if (index == DFS_FILESYSTEM_TYPES_MAX)
	{
		result = -1;
		goto err;
	}

	/* save the filesystem's operations */
	filesystem_operation_table[index] = ops;

err:
	dfs_unlock();
	return result;
}

/**
 * this function will return the file system mounted on specified path.
 *
 * @param path the specified path string.
 *
 * @return the found file system or NULL if no file system mounted on
 * specified path
 */
struct dfs_filesystem *dfs_filesystem_lookup(const char *path)
{
	struct dfs_filesystem *fs;
	rt_uint32_t index, fspath, prefixlen;

	fs = RT_NULL;
	prefixlen = 0;

	/* lock filesystem */
	dfs_lock();

	/* lookup it in the filesystem table */
	for (index = 0; index < DFS_FILESYSTEMS_MAX; index++)
	{
		if (filesystem_table[index].path == RT_NULL)
			continue;
		else
		{
			fspath = strlen(filesystem_table[index].path);
			if (fspath < prefixlen)
				continue;
		}

		if ((filesystem_table[index].ops != RT_NULL) &&
			(strncmp(filesystem_table[index].path, path, fspath) == 0))
		{
			/* check next path separator */
			if (fspath > 1 && (strlen(path) > fspath) && (path[fspath] != '/'))
				continue;

			fs = &filesystem_table[index];
			prefixlen = fspath;
		}
	}

	dfs_unlock();

	return fs;
}

/**
 * this function will fetch the partition table on specified buffer.
 *
 * @param part the returned partition structure.
 * @param buf the buffer contains partition table.
 * @param pindex the index of partition table to fetch.
 *
 * @return RT_EOK on successful or -RT_ERROR on failed.
 */
rt_err_t dfs_filesystem_get_partition(struct dfs_partition *part, rt_uint8_t *buf, rt_uint32_t pindex)
{
#define DPT_ADDRESS		0x1be		/* device partition offset in Boot Sector */
#define DPT_ITEM_SIZE	16			/* partition item size */

	rt_uint8_t *dpt;
	rt_uint8_t type;
	rt_err_t result;

	RT_ASSERT(part != RT_NULL);
	RT_ASSERT(buf != RT_NULL);

	result = RT_EOK;

	dpt = buf + DPT_ADDRESS + pindex * DPT_ITEM_SIZE;

	if ((*dpt != 0x80) && (*dpt != 0x00))
	{
		/* which is not a partition table */
		result = -RT_ERROR;
		return result;
	}

	/* get partition type */
	type = *(dpt+4);

	if (type != 0)
	{
		/* set partition type */
		part->type = type;

		/* get partition offset and size */
		part->offset = *(dpt+8) | *(dpt+9)<<8 | *(dpt+10)<<16 | *(dpt+11)<<24;
		part->size = *(dpt+12) | *(dpt+13)<<8 | *(dpt+14)<<16 | *(dpt+15)<<24;

		rt_kprintf("found part[%d], begin: %d, size: ", pindex, part->offset*512);
		if ((part->size>>11) > 0) /* MB */
		{
			unsigned int part_size;
			part_size = part->size >> 11;/* MB */
			if ((part_size>>10) > 0) /* GB */
			{
				rt_kprintf("%d.%d%s",part_size>>10,part_size&0x3FF,"GB\r\n");/* GB */
			}
			else
			{
				rt_kprintf("%d.%d%s",part_size,(part->size>>1)&0x3FF,"MB\r\n");/* MB */
			}
		}
		else
		{
			rt_kprintf("%d%s",part->size>>1,"KB\r\n");/* KB */
		}
	}
	else
	{
		result = -RT_ERROR;
	}

	return result;
}

/**
 * this function will mount a file system on a specified path.
 *
 * @param device_name the name of device which includes a file system.
 * @param path the path to mount a file system
 * @param filesystemtype the file system type
 * @param rwflag the read/write etc. flag.
 * @param data the private data(parameter) for this file system.
 *
 * @return 0 on successful or -1 on failed.
 */
int dfs_mount(const char *device_name, const char *path,
			const char *filesystemtype, unsigned long rwflag, const
			void *data)
{
	const struct dfs_filesystem_operation *ops;
	struct dfs_filesystem *fs;
	char *fullpath=RT_NULL;
	rt_device_t dev_id;
	int index;

	/* open specific device */
	if (device_name != RT_NULL)
	{
		dev_id = rt_device_find(device_name);
		if (dev_id == RT_NULL)
		{
			/* no this device */
			rt_set_errno(-DFS_STATUS_ENODEV);
			return -1;
		}
	}
	else
	{
		/* which is a non-device filesystem mount */
		dev_id = RT_NULL;
	}

	/* find out specific filesystem */
	dfs_lock();
	for (index = 0; index < DFS_FILESYSTEM_TYPES_MAX; index++)
	{
		if (strcmp(filesystem_operation_table[index]->name, filesystemtype) == 0)
			break;
	}

	/* can't find filesystem */
	if (index == DFS_FILESYSTEM_TYPES_MAX)
	{
		rt_set_errno(-DFS_STATUS_ENODEV);
		dfs_unlock();
		return -1;
	}
	ops = filesystem_operation_table[index];
	dfs_unlock();

	/* make full path for special file */
	fullpath = dfs_normalize_path(RT_NULL, path);
	if (fullpath == RT_NULL) /* not an abstract path */
	{
		rt_set_errno(-DFS_STATUS_ENOTDIR);
		return -1;
	}

	/* Check if the path exists or not, raw APIs call, fixme */
	if ((strcmp(fullpath, "/") != 0) && (strcmp(fullpath, "/dev") != 0))
	{
		struct dfs_fd fd;

		if (dfs_file_open(&fd, fullpath, DFS_O_RDONLY | DFS_O_DIRECTORY) < 0)
		{
			rt_free(fullpath);
			rt_set_errno(-DFS_STATUS_ENOTDIR);
			return -1;
		}
		dfs_file_close(&fd);
	}

	/* check whether the file system mounted or not */
	dfs_lock();
	for (index =0; index < DFS_FILESYSTEMS_MAX; index++)
	{
		if (filesystem_table[index].ops != RT_NULL &&
			strcmp(filesystem_table[index].path, path) == 0)
		{
			rt_set_errno(-DFS_STATUS_EINVAL);
			goto err1;
		}
	}

	/* find out an empty filesystem table entry */
	for (index = 0; index < DFS_FILESYSTEMS_MAX && filesystem_table[index].ops != RT_NULL;
		index++) ;
	if (index == DFS_FILESYSTEMS_MAX)	/* can't find en empty filesystem table entry */
	{
		rt_set_errno(-DFS_STATUS_ENOSPC);
		goto err1;
	}

	/* register file system */
	fs = &(filesystem_table[index]);
	fs->path = fullpath;
	fs->ops = ops;
	fs->dev_id = dev_id;
	/* release filesystem_table lock */
	dfs_unlock();

	/* open device, but do not check the status of device */
	if (dev_id != RT_NULL)
		rt_device_open(fs->dev_id, RT_DEVICE_OFLAG_RDWR);

	if (ops->mount == RT_NULL) /* there is no mount implementation */
	{
		if (dev_id != RT_NULL)
			rt_device_close(dev_id);
		dfs_lock();
		/* clear filesystem table entry */
		rt_memset(fs, 0, sizeof(struct dfs_filesystem));
		dfs_unlock();

		rt_free(fullpath);
		rt_set_errno(-DFS_STATUS_ENOSYS);
		return -1;
	}
	/* call mount of this filesystem */
	else if (ops->mount(fs, rwflag, data) < 0)
	{
		/* close device */
		if (dev_id != RT_NULL)
			rt_device_close(fs->dev_id);

		/* mount failed */
		dfs_lock();
		/* clear filesystem table entry */
		rt_memset(fs, 0, sizeof(struct dfs_filesystem));
		dfs_unlock();

		rt_free(fullpath);
		return -1;
	}

	return 0;

err1:
	dfs_unlock();
	if (fullpath != RT_NULL)
		rt_free(fullpath);

	return -1;
}

/**
 * this function will unmount a file system on specified path.
 *
 * @param specialfile the specified path which mounted a file system.
 *
 * @return 0 on successful or -1 on failed.
 */
int dfs_unmount(const char *specialfile)
{
	char *fullpath;
	struct dfs_filesystem *fs = RT_NULL;

	fullpath = dfs_normalize_path(RT_NULL, specialfile);
	if (fullpath == RT_NULL)
	{
		rt_set_errno(-DFS_STATUS_ENOTDIR);
		return -1;
	}

	/* lock filesystem */
	dfs_lock();

	fs = dfs_filesystem_lookup(fullpath);
	if (fs != RT_NULL && fs->ops->unmount != RT_NULL && fs->ops->unmount(fs) < 0)
	{
		goto err1;
	}

	/* close device, but do not check the status of device */
	if (fs->dev_id != RT_NULL)
		rt_device_close(fs->dev_id);

	if (fs->path != RT_NULL)
		rt_free(fs->path);

	/* clear this filesystem table entry */
	rt_memset(fs, 0, sizeof(struct dfs_filesystem));

	dfs_unlock();
	rt_free(fullpath);

	return 0;

err1:
	dfs_unlock();
	rt_free(fullpath);

	return -1;
}

/**
 * make a file system on the special device
 *
 * @param fs_name the file system name
 * @param device_name the special device name
 *
 * @return 0 on successful, otherwise failed.
 */
int dfs_mkfs(const char *fs_name, const char *device_name)
{
	int index;

	/* lock filesystem */
	dfs_lock();
	/* find the file system operations */
	for (index = 0; index < DFS_FILESYSTEM_TYPES_MAX; index++)
	{
		if (filesystem_operation_table[index] != RT_NULL &&
			strcmp(filesystem_operation_table[index]->name, fs_name) == 0)
		{
			/* find file system operation */
			const struct dfs_filesystem_operation* ops = filesystem_operation_table[index];
			dfs_unlock();

			if (ops->mkfs != RT_NULL)
				return ops->mkfs(device_name);

			break;
		}
	}
	dfs_unlock();

	return -1;
}

/**
 * this function will return the information about a mounted file system.
 *
 * @param path the path which mounted file system.
 * @param buffer the buffer to save the returned information.
 *
 * @return 0 on successful, others on failed.
 */
int dfs_statfs(const char *path, struct statfs *buffer)
{
	struct dfs_filesystem *fs;

	fs = dfs_filesystem_lookup(path);
	if (fs != RT_NULL)
	{
		if (fs->ops->statfs != RT_NULL)
			return fs->ops->statfs(fs, buffer);
	}

	return -1;
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void mkfs(const char *fs_name, const char *device_name)
{
	dfs_mkfs(fs_name, device_name);
}
FINSH_FUNCTION_EXPORT(mkfs, make a file system);

void df(const char *path)
{
	struct statfs buffer;

	if (dfs_statfs(path, &buffer) == 0)
	{
		rt_kprintf("disk free: %d block[%d bytes per block]\n", buffer.f_bfree, buffer.f_bsize);
	}
}
FINSH_FUNCTION_EXPORT(df, get disk free);
#endif

/* @} */
