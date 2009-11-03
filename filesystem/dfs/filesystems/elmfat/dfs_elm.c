#include <dfs_fs.h>
#include <dfs_def.h>

#include "ff.h"

#define ELM_MAX_DISK	4
static rt_device_t disk[ELM_MAX_DISK] = {0};

static int elm_result_to_dfs(FRESULT result)
{
	int status = DFS_STATUS_OK;

	switch (result)
	{
	case FR_OK:
		break;

	case FR_NO_FILE:
	case FR_NO_PATH:
	case FR_NO_FILESYSTEM:
		status = -DFS_STATUS_ENOENT;
		break;

	case FR_INVALID_NAME:
		status = -DFS_STATUS_EINVAL;
		break;

	case FR_EXIST:
	case FR_INVALID_OBJECT:
		status = -DFS_STATUS_EEXIST;
		break;

	case FR_DISK_ERR:
	case FR_NOT_READY:
	case FR_INT_ERR:
		status = -DFS_STATUS_EIO;
		break;

	case FR_WRITE_PROTECTED:
	case FR_DENIED:
		status = -DFS_STATUS_EROFS;
		break;

	default:
		status = -1;
		break;
	}

	return status;
}

int dfs_elm_mount(struct dfs_filesystem* fs)
{
	FATFS *fat;
	FRESULT result;
	rt_uint32_t index;

	/* handle RT-Thread device routine */
	for (index = 0; index < ELM_MAX_DISK; index ++)
	{
		if (disk[index] == RT_NULL)
		{
			break;
		}
	}
	if (index == ELM_MAX_DISK) return -DFS_STATUS_EMMOUNT;

	/* get device */
	disk[index] = fs->dev_id;

	fat = (FATFS *) rt_malloc(sizeof(FATFS));
	if (fat == RT_NULL)
	{
		return -1;
	}

	/* mount fatfs, always 0 logic driver */
	result = f_mount(index, fat);
	if (result == FR_OK)
		fs->data = fat;
	else
	{
		rt_free(fat);
		return elm_result_to_dfs(result);
	}

	return 0;
}

int dfs_elm_unmount(struct dfs_filesystem* fs)
{
	FATFS *fat;
	fat = (FATFS*) fs->data;

	RT_ASSERT(fat != RT_NULL);

	/* elm not support unmount */
	RT_ASSERT(0);

	return 0;
}

int dfs_elm_open(struct dfs_fd* file)
{
	FIL* fd;
	BYTE mode;
	FRESULT result;

	if (file->flags & DFS_O_DIRECTORY)
	{
		DIR *dir;

		if (file->flags & DFS_O_CREAT)
		{
			result = f_mkdir(file->path);
			if (result != FR_OK)
			{
				return elm_result_to_dfs(result);
			}
		}

		/* open directory */
		dir = (DIR *)rt_malloc(sizeof(DIR));
		if (dir == RT_NULL)
		{
			return -DFS_STATUS_ENOMEM;
		}

		result = f_opendir(dir, file->path);
		if (result != FR_OK)
		{
			rt_free(dir);
			return elm_result_to_dfs(result);
		}

		file->data = dir;
		return DFS_STATUS_OK;
	}
	else
	{
		mode = FA_READ;

		if (file->flags & DFS_O_CREAT) mode |= FA_CREATE_NEW;
		if (file->flags & DFS_O_WRONLY) mode |= FA_WRITE;

		/* allocate a fd */
		fd = (FIL*)rt_malloc(sizeof(FIL));
		if (fd == RT_NULL)
		{
			return -DFS_STATUS_ENOMEM;
		}

		result = f_open(fd, file->path, mode);
		if (result == FR_OK)
		{
			file->pos  = fd->fptr;
			file->size = fd->fsize;
			file->data = fd;
		}
		else
		{
			/* open failed, return */
			rt_free(fd);
			return elm_result_to_dfs(result);
		}
	}

	return DFS_STATUS_OK;
}

int dfs_elm_close(struct dfs_fd* file)
{
	FRESULT result;

	result = FR_OK;
	if (file->type == FT_DIRECTORY)
	{
		DIR* dir;

		dir = (DIR*)(file->data);
		RT_ASSERT(dir != RT_NULL);

		/* release memory */
		rt_free(dir);
	}
	else if (file->type == FT_REGULAR)
	{
		FIL* fd;
		fd = (FIL*)(file->data);
		RT_ASSERT(fd != RT_NULL);

		result = f_close(fd);
		if (result == FR_OK)
		{
			/* release memory */
			rt_free(fd);
		}
	}

	return elm_result_to_dfs(result);
}

int dfs_elm_ioctl(struct dfs_fd* file, int cmd,	void* args)
{
	return -DFS_STATUS_ENOSYS;
}

int dfs_elm_read(struct dfs_fd* file, void* buf, rt_size_t len)
{
	FIL* fd;
	FRESULT result;
	UINT byte_read;

	if (file->type == FT_DIRECTORY)
	{
		return -DFS_STATUS_EISDIR;
	}

	fd = (FIL*)(file->data);
	RT_ASSERT(fd != RT_NULL);

	result = f_read(fd, buf, len, &byte_read);
	/* update position */
	file->pos  = fd->fptr;
	if (result == FR_OK) return byte_read;

	return elm_result_to_dfs(result);
}

int dfs_elm_write(struct dfs_fd* file, const void* buf, rt_size_t len)
{
	FIL* fd;
	FRESULT result;
	UINT byte_write;

	if (file->type == FT_DIRECTORY)
	{
		return -DFS_STATUS_EISDIR;
	}

	fd = (FIL*)(file->data);
	RT_ASSERT(fd != RT_NULL);

	result = f_write(fd, buf, len, &byte_write);
	/* update position */
	file->pos  = fd->fptr;
	if (result == FR_OK) return byte_write;

	return elm_result_to_dfs(result);
}

int dfs_elm_lseek(struct dfs_fd* file, rt_off_t offset)
{
	FIL* fd;
	FRESULT result;

	fd = (FIL*)(file->data);
	RT_ASSERT(fd != RT_NULL);

	result = f_lseek(fd, offset);
	return elm_result_to_dfs(result);
}

int dfs_elm_getdents(struct dfs_fd* file, struct dfs_dirent* dirp, rt_uint32_t count)
{
	DIR* dir;
	FILINFO fno;
	FRESULT result;
	rt_uint32_t index;
	struct dfs_dirent* d;

	dir = (DIR*)(file->data);
	RT_ASSERT(dir != RT_NULL);

	/* make integer count */
	count = (count / sizeof(struct dfs_dirent)) * sizeof(struct dfs_dirent);
	if ( count == 0 ) return -DFS_STATUS_EINVAL;

#if _USE_LFN
	/* allocate long file name */
	fno.lfname = rt_malloc(256);
	fno.lfsize = 256;
#endif

	index = 0;
	while (1)
	{
		char *fn;

		d = dirp + index;

		result = f_readdir(dir, &fno);
		if (result != FR_OK || fno.fname[0] == 0) break;

#if _USE_LFN
		fn = *fno.lfname? fno.lfname : fno.fname;
#else
		fn = fno.fname;
#endif

		d->d_type = DFS_DT_UNKNOWN;
		if (fno.fattrib & AM_DIR) d->d_type &= DFS_DT_DIR;
		else d->d_type &= DFS_DT_REG;

		d->d_namlen = rt_strlen(fn);
		d->d_reclen = (rt_uint16_t)sizeof(struct dfs_dirent);
		rt_strncpy(d->d_name, fn, rt_strlen(fn) + 1);

		index ++;
		if ( index * sizeof(struct dfs_dirent) >= count )
			break;
	}

#if _USE_LFN
	rt_free(fno.lfname);
#endif

	if (index == 0)
		return elm_result_to_dfs(result);

	return index * sizeof(struct dfs_dirent);
}

int dfs_elm_unlink(struct dfs_filesystem* fs, const char* path)
{
	FRESULT result;

	result = f_unlink(path);
	return elm_result_to_dfs(result);
}

int dfs_elm_rename(struct dfs_filesystem* fs, const char* oldpath, const char* newpath)
{
	FRESULT result;

	result = f_rename(oldpath, newpath);
	return elm_result_to_dfs(result);
}

int dfs_elm_stat(struct dfs_filesystem* fs, const char *path, struct dfs_stat *st)
{
	FILINFO file_info;
	FRESULT result;

#if _USE_LFN
	/* allocate long file name */
	file_info.lfname = rt_malloc(256);
	file_info.lfsize = 256;
#endif

	result = f_stat(path, &file_info);
	if (result == FR_OK)
	{
		/* convert to dfs stat structure */
		st->st_dev   = 0;

		st->st_mode = DFS_S_IFREG | DFS_S_IRUSR | DFS_S_IRGRP | DFS_S_IROTH | 
		DFS_S_IWUSR | DFS_S_IWGRP | DFS_S_IWOTH;
		if (file_info.fattrib & AM_DIR) 
		{
			st->st_mode &= ~DFS_S_IFREG;
			st->st_mode |= DFS_S_IFDIR | DFS_S_IXUSR | DFS_S_IXGRP | DFS_S_IXOTH;
		}
		if (file_info.fattrib & AM_RDO)
			st->st_mode &= ~(DFS_S_IWUSR | DFS_S_IWGRP | DFS_S_IWOTH);

		st->st_size  = file_info.fsize;
		st->st_mtime = file_info.ftime;
		st->st_blksize = 512;
	}

#if _USE_LFN
	rt_free(file_info.lfname);
#endif

	return elm_result_to_dfs(result);
}

static struct dfs_filesystem_operation dfs_elm;
int elm_init(void)
{
	rt_strncpy(dfs_elm.name, "elm", DFS_FS_NAME_MAX);

	dfs_elm.mount 	= dfs_elm_mount;
	dfs_elm.unmount = dfs_elm_unmount;
	dfs_elm.open	= dfs_elm_open;
	dfs_elm.close 	= dfs_elm_close;
	dfs_elm.ioctl 	= dfs_elm_ioctl;
	dfs_elm.read	= dfs_elm_read;
	dfs_elm.write 	= dfs_elm_write;
	dfs_elm.lseek 	= dfs_elm_lseek;
	dfs_elm.getdents= dfs_elm_getdents;
	dfs_elm.unlink 	= dfs_elm_unlink;
	dfs_elm.stat	= dfs_elm_stat;
	dfs_elm.rename 	= dfs_elm_rename;

    /* register fatfs file system */
    dfs_register(&dfs_elm);

	return 0;
}

/*
 * RT-Thread Device Interface for ELM FatFs
 */
#include "diskio.h"

/* Inidialize a Drive */
DSTATUS disk_initialize (BYTE drv)
{
	return 0;
}

/* Return Disk Status */
DSTATUS disk_status (BYTE drv)
{
	return 0;
}

/* Read Sector(s) */
DRESULT disk_read (BYTE drv, BYTE *buff, DWORD sector, BYTE count)
{
	rt_size_t result;
	rt_device_t device = disk[drv];

	result = rt_device_read(device, sector * 512, buff, count * 512);
	if (result == count * 512)
	{
		return RES_OK;
	}

	return RES_ERROR;
}

/* Write Sector(s) */
DRESULT disk_write (BYTE drv, const BYTE *buff, DWORD sector, BYTE count)
{
	rt_size_t result;
	rt_device_t device = disk[drv];

	result = rt_device_write(device, sector * 512, buff, count * 512);
	if (result == count * 512)
	{
		return RES_OK;
	}

	return RES_ERROR;
}

/* Miscellaneous Functions */
DRESULT disk_ioctl (BYTE drv, BYTE ctrl, void *buff)
{
	return RES_OK;
}

rt_time_t get_fattime()
{
	return 0;
}
