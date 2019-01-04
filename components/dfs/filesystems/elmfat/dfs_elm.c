/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-02-22     QiuYi        The first version.
 * 2011-10-08     Bernard      fixed the block size in statfs.
 * 2011-11-23     Bernard      fixed the rename issue.
 * 2012-07-26     aozima       implement ff_memalloc and ff_memfree.
 * 2012-12-19     Bernard      fixed the O_APPEND and lseek issue.
 * 2013-03-01     aozima       fixed the stat(st_mtime) issue.
 * 2014-01-26     Bernard      Check the sector size before mount.
 * 2017-02-13     Hichard      Update Fatfs version to 0.12b, support exFAT.
 * 2017-04-11     Bernard      fix the st_blksize issue.
 * 2017-05-26     Urey         fix f_mount error when mount more fats
 */

#include <rtthread.h>
#include "ffconf.h"
#include "ff.h"
#include <string.h>
#include <time.h>

/* ELM FatFs provide a DIR struct */
#define HAVE_DIR_STRUCTURE

#include <dfs_fs.h>
#include <dfs_file.h>

static rt_device_t disk[_VOLUMES] = {0};

static int elm_result_to_dfs(FRESULT result)
{
    int status = RT_EOK;

    switch (result)
    {
    case FR_OK:
        break;

    case FR_NO_FILE:
    case FR_NO_PATH:
    case FR_NO_FILESYSTEM:
        status = -ENOENT;
        break;

    case FR_INVALID_NAME:
        status = -EINVAL;
        break;

    case FR_EXIST:
    case FR_INVALID_OBJECT:
        status = -EEXIST;
        break;

    case FR_DISK_ERR:
    case FR_NOT_READY:
    case FR_INT_ERR:
        status = -EIO;
        break;

    case FR_WRITE_PROTECTED:
    case FR_DENIED:
        status = -EROFS;
        break;

    case FR_MKFS_ABORTED:
        status = -EINVAL;
        break;

    default:
        status = -1;
        break;
    }

    return status;
}

/* results:
 *  -1, no space to install fatfs driver
 *  >= 0, there is an space to install fatfs driver
 */
static int get_disk(rt_device_t id)
{
    int index;

    for (index = 0; index < _VOLUMES; index ++)
    {
        if (disk[index] == id)
            return index;
    }

    return -1;
}

int dfs_elm_mount(struct dfs_filesystem *fs, unsigned long rwflag, const void *data)
{
    FATFS *fat;
    FRESULT result;
    int index;
    struct rt_device_blk_geometry geometry;
    char logic_nbr[2] = {'0',':'};

    /* get an empty position */
    index = get_disk(RT_NULL);
    if (index == -1)
        return -ENOENT;
    logic_nbr[0] = '0' + index;

    /* save device */
    disk[index] = fs->dev_id;
    /* check sector size */
    if (rt_device_control(fs->dev_id, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry) == RT_EOK)
    {
        if (geometry.bytes_per_sector > _MAX_SS)
        {
            rt_kprintf("The sector size of device is greater than the sector size of FAT.\n");
            return -EINVAL;
        }
    }

    fat = (FATFS *)rt_malloc(sizeof(FATFS));
    if (fat == RT_NULL)
    {
        disk[index] = RT_NULL;
        return -ENOMEM;
    }

    /* mount fatfs, always 0 logic driver */
    result = f_mount(fat, (const TCHAR*)logic_nbr, 1);
    if (result == FR_OK)
    {
        char drive[8];
        DIR *dir;

        rt_snprintf(drive, sizeof(drive), "%d:/", index);
        dir = (DIR *)rt_malloc(sizeof(DIR));
        if (dir == RT_NULL)
        {
            f_mount(RT_NULL, (const TCHAR*)logic_nbr, 1);
            disk[index] = RT_NULL;
            rt_free(fat);
            return -ENOMEM;
        }

        /* open the root directory to test whether the fatfs is valid */
        result = f_opendir(dir, drive);
        if (result != FR_OK)
            goto __err;

        /* mount succeed! */
        fs->data = fat;
        rt_free(dir);
        return 0;
    }

__err:
    f_mount(RT_NULL, (const TCHAR*)logic_nbr, 1);
    disk[index] = RT_NULL;
    rt_free(fat);
    return elm_result_to_dfs(result);
}

int dfs_elm_unmount(struct dfs_filesystem *fs)
{
    FATFS *fat;
    FRESULT result;
    int  index;
    char logic_nbr[2] = {'0',':'};

    fat = (FATFS *)fs->data;

    RT_ASSERT(fat != RT_NULL);

    /* find the device index and then umount it */
    index = get_disk(fs->dev_id);
    if (index == -1) /* not found */
        return -ENOENT;

    logic_nbr[0] = '0' + index;
    result = f_mount(RT_NULL, logic_nbr, (BYTE)1); 
    if (result != FR_OK)
        return elm_result_to_dfs(result);

    fs->data = RT_NULL;
    disk[index] = RT_NULL;
    rt_free(fat);

    return RT_EOK;
}

int dfs_elm_mkfs(rt_device_t dev_id)
{
#define FSM_STATUS_INIT            0
#define FSM_STATUS_USE_TEMP_DRIVER 1
    FATFS *fat = RT_NULL;
    BYTE *work;
    int flag;
    FRESULT result;
    int index;
    char logic_nbr[2] = {'0',':'};
    
    work = rt_malloc(_MAX_SS);
    if(RT_NULL == work) {
        return -ENOMEM;
    }

    if (dev_id == RT_NULL)
    {
        rt_free(work); /* release memory */
        return -EINVAL;
    }

    /* if the device is already mounted, then just do mkfs to the drv,
     * while if it is not mounted yet, then find an empty drive to do mkfs
     */

    flag = FSM_STATUS_INIT;
    index = get_disk(dev_id);
    if (index == -1)
    {
        /* not found the device id */
        index = get_disk(RT_NULL);
        if (index == -1)
        {
            /* no space to store an temp driver */
            rt_kprintf("sorry, there is no space to do mkfs! \n");
            rt_free(work); /* release memory */
            return -ENOSPC;
        }
        else
        {
            fat = rt_malloc(sizeof(FATFS));
            if (fat == RT_NULL)
            {
                rt_free(work); /* release memory */
                return -ENOMEM;
            }

            flag = FSM_STATUS_USE_TEMP_DRIVER;

            disk[index] = dev_id;
            /* try to open device */
            rt_device_open(dev_id, RT_DEVICE_OFLAG_RDWR);

            /* just fill the FatFs[vol] in ff.c, or mkfs will failded!
             * consider this condition: you just umount the elm fat,
             * then the space in FatFs[index] is released, and now do mkfs
             * on the disk, you will get a failure. so we need f_mount here,
             * just fill the FatFS[index] in elm fatfs to make mkfs work.
             */
            logic_nbr[0] = '0' + index;
            f_mount(fat, logic_nbr, (BYTE)index);
        }
    }
    else
    {
        logic_nbr[0] = '0' + index;
    }

    /* [IN] Logical drive number */
    /* [IN] Format options */
    /* [IN] Size of the allocation unit */
    /* [-]  Working buffer */
    /* [IN] Size of working buffer */
    result = f_mkfs(logic_nbr, FM_ANY|FM_SFD, 0, work, _MAX_SS);
    rt_free(work); work = RT_NULL;

    /* check flag status, we need clear the temp driver stored in disk[] */
    if (flag == FSM_STATUS_USE_TEMP_DRIVER)
    {
        rt_free(fat);
        f_mount(RT_NULL, logic_nbr,(BYTE)index);
        disk[index] = RT_NULL;
        /* close device */
        rt_device_close(dev_id);
    }

    if (result != FR_OK)
    {
        rt_kprintf("format error\n");
        return elm_result_to_dfs(result);
    }

    return RT_EOK;
}

int dfs_elm_statfs(struct dfs_filesystem *fs, struct statfs *buf)
{
    FATFS *f;
    FRESULT res;
    char driver[4];
    DWORD fre_clust, fre_sect, tot_sect;

    RT_ASSERT(fs != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    f = (FATFS *)fs->data;

    rt_snprintf(driver, sizeof(driver), "%d:", f->drv);
    res = f_getfree(driver, &fre_clust, &f);
    if (res)
        return elm_result_to_dfs(res);

    /* Get total sectors and free sectors */
    tot_sect = (f->n_fatent - 2) * f->csize;
    fre_sect = fre_clust * f->csize;

    buf->f_bfree = fre_sect;
    buf->f_blocks = tot_sect;
#if _MAX_SS != 512
    buf->f_bsize = f->ssize;
#else
    buf->f_bsize = 512;
#endif

    return 0;
}

int dfs_elm_open(struct dfs_fd *file)
{
    FIL *fd;
    BYTE mode;
    FRESULT result;
    char *drivers_fn;

#if (_VOLUMES > 1)
    int vol;
    struct dfs_filesystem *fs = (struct dfs_filesystem *)file->data;
    extern int elm_get_vol(FATFS * fat);

    if (fs == NULL)
        return -ENOENT;

    /* add path for ELM FatFS driver support */
    vol = elm_get_vol((FATFS *)fs->data);
    if (vol < 0)
        return -ENOENT;
    drivers_fn = rt_malloc(256);
    if (drivers_fn == RT_NULL)
        return -ENOMEM;

    rt_snprintf(drivers_fn, 256, "%d:%s", vol, file->path);
#else
    drivers_fn = file->path;
#endif

    if (file->flags & O_DIRECTORY)
    {
        DIR *dir;

        if (file->flags & O_CREAT)
        {
            result = f_mkdir(drivers_fn);
            if (result != FR_OK)
            {
#if _VOLUMES > 1
                rt_free(drivers_fn);
#endif
                return elm_result_to_dfs(result);
            }
        }

        /* open directory */
        dir = (DIR *)rt_malloc(sizeof(DIR));
        if (dir == RT_NULL)
        {
#if _VOLUMES > 1
            rt_free(drivers_fn);
#endif
            return -ENOMEM;
        }

        result = f_opendir(dir, drivers_fn);
#if _VOLUMES > 1
        rt_free(drivers_fn);
#endif
        if (result != FR_OK)
        {
            rt_free(dir);
            return elm_result_to_dfs(result);
        }

        file->data = dir;
        return RT_EOK;
    }
    else
    {
        mode = FA_READ;

        if (file->flags & O_WRONLY)
            mode |= FA_WRITE;
        if ((file->flags & O_ACCMODE) & O_RDWR)
            mode |= FA_WRITE;
        /* Opens the file, if it is existing. If not, a new file is created. */
        if (file->flags & O_CREAT)
            mode |= FA_OPEN_ALWAYS;
        /* Creates a new file. If the file is existing, it is truncated and overwritten. */
        if (file->flags & O_TRUNC)
            mode |= FA_CREATE_ALWAYS;
        /* Creates a new file. The function fails if the file is already existing. */
        if (file->flags & O_EXCL)
            mode |= FA_CREATE_NEW;

        /* allocate a fd */
        fd = (FIL *)rt_malloc(sizeof(FIL));
        if (fd == RT_NULL)
        {
#if _VOLUMES > 1
            rt_free(drivers_fn);
#endif
            return -ENOMEM;
        }

        result = f_open(fd, drivers_fn, mode);
#if _VOLUMES > 1
        rt_free(drivers_fn);
#endif
        if (result == FR_OK)
        {
            file->pos  = fd->fptr;
            file->size = f_size(fd);
            file->data = fd;

            if (file->flags & O_APPEND)
            {
                /* seek to the end of file */
                f_lseek(fd, f_size(fd));
                file->pos = fd->fptr;
            }
        }
        else
        {
            /* open failed, return */
            rt_free(fd);
            return elm_result_to_dfs(result);
        }
    }

    return RT_EOK;
}

int dfs_elm_close(struct dfs_fd *file)
{
    FRESULT result;

    result = FR_OK;
    if (file->type == FT_DIRECTORY)
    {
        DIR *dir;

        dir = (DIR *)(file->data);
        RT_ASSERT(dir != RT_NULL);

        /* release memory */
        rt_free(dir);
    }
    else if (file->type == FT_REGULAR)
    {
        FIL *fd;
        fd = (FIL *)(file->data);
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

int dfs_elm_ioctl(struct dfs_fd *file, int cmd, void *args)
{
    return -ENOSYS;
}

int dfs_elm_read(struct dfs_fd *file, void *buf, size_t len)
{
    FIL *fd;
    FRESULT result;
    UINT byte_read;

    if (file->type == FT_DIRECTORY)
    {
        return -EISDIR;
    }

    fd = (FIL *)(file->data);
    RT_ASSERT(fd != RT_NULL);

    result = f_read(fd, buf, len, &byte_read);
    /* update position */
    file->pos  = fd->fptr;
    if (result == FR_OK)
        return byte_read;

    return elm_result_to_dfs(result);
}

int dfs_elm_write(struct dfs_fd *file, const void *buf, size_t len)
{
    FIL *fd;
    FRESULT result;
    UINT byte_write;

    if (file->type == FT_DIRECTORY)
    {
        return -EISDIR;
    }

    fd = (FIL *)(file->data);
    RT_ASSERT(fd != RT_NULL);

    result = f_write(fd, buf, len, &byte_write);
    /* update position and file size */
    file->pos  = fd->fptr;
    file->size = f_size(fd);
    if (result == FR_OK)
        return byte_write;

    return elm_result_to_dfs(result);
}

int dfs_elm_flush(struct dfs_fd *file)
{
    FIL *fd;
    FRESULT result;

    fd = (FIL *)(file->data);
    RT_ASSERT(fd != RT_NULL);

    result = f_sync(fd);
    return elm_result_to_dfs(result);
}

int dfs_elm_lseek(struct dfs_fd *file, rt_off_t offset)
{
    FRESULT result = FR_OK;
    if (file->type == FT_REGULAR)
    {
        FIL *fd;

        /* regular file type */
        fd = (FIL *)(file->data);
        RT_ASSERT(fd != RT_NULL);

        result = f_lseek(fd, offset);
        if (result == FR_OK)
        {
            /* return current position */
            file->pos = fd->fptr;
            return fd->fptr;
        }
    }
    else if (file->type == FT_DIRECTORY)
    {
        /* which is a directory */
        DIR *dir;

        dir = (DIR *)(file->data);
        RT_ASSERT(dir != RT_NULL);

        result = f_seekdir(dir, offset / sizeof(struct dirent));
        if (result == FR_OK)
        {
            /* update file position */
            file->pos = offset;
            return file->pos;
        }
    }

    return elm_result_to_dfs(result);
}

int dfs_elm_getdents(struct dfs_fd *file, struct dirent *dirp, uint32_t count)
{
    DIR *dir;
    FILINFO fno;
    FRESULT result;
    rt_uint32_t index;
    struct dirent *d;

    dir = (DIR *)(file->data);
    RT_ASSERT(dir != RT_NULL);

    /* make integer count */
    count = (count / sizeof(struct dirent)) * sizeof(struct dirent);
    if (count == 0)
        return -EINVAL;

    index = 0;
    while (1)
    {
        char *fn;

        d = dirp + index;

        result = f_readdir(dir, &fno);
        if (result != FR_OK || fno.fname[0] == 0)
            break;

#if _USE_LFN
        fn = *fno.fname ? fno.fname : fno.altname;
#else
        fn = fno.fname;
#endif

        d->d_type = DT_UNKNOWN;
        if (fno.fattrib & AM_DIR)
            d->d_type = DT_DIR;
        else
            d->d_type = DT_REG;

        d->d_namlen = (rt_uint8_t)rt_strlen(fn);
        d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
        rt_strncpy(d->d_name, fn, rt_strlen(fn) + 1);

        index ++;
        if (index * sizeof(struct dirent) >= count)
            break;
    }

    if (index == 0)
        return elm_result_to_dfs(result);

    file->pos += index * sizeof(struct dirent);

    return index * sizeof(struct dirent);
}

int dfs_elm_unlink(struct dfs_filesystem *fs, const char *path)
{
    FRESULT result;

#if _VOLUMES > 1
    int vol;
    char *drivers_fn;
    extern int elm_get_vol(FATFS * fat);

    /* add path for ELM FatFS driver support */
    vol = elm_get_vol((FATFS *)fs->data);
    if (vol < 0)
        return -ENOENT;
    drivers_fn = rt_malloc(256);
    if (drivers_fn == RT_NULL)
        return -ENOMEM;

    rt_snprintf(drivers_fn, 256, "%d:%s", vol, path);
#else
    const char *drivers_fn;
    drivers_fn = path;
#endif

    result = f_unlink(drivers_fn);
#if _VOLUMES > 1
    rt_free(drivers_fn);
#endif
    return elm_result_to_dfs(result);
}

int dfs_elm_rename(struct dfs_filesystem *fs, const char *oldpath, const char *newpath)
{
    FRESULT result;

#if _VOLUMES > 1
    char *drivers_oldfn;
    const char *drivers_newfn;
    int vol;
    extern int elm_get_vol(FATFS * fat);

    /* add path for ELM FatFS driver support */
    vol = elm_get_vol((FATFS *)fs->data);
    if (vol < 0)
        return -ENOENT;

    drivers_oldfn = rt_malloc(256);
    if (drivers_oldfn == RT_NULL)
        return -ENOMEM;
    drivers_newfn = newpath;

    rt_snprintf(drivers_oldfn, 256, "%d:%s", vol, oldpath);
#else
    const char *drivers_oldfn, *drivers_newfn;

    drivers_oldfn = oldpath;
    drivers_newfn = newpath;
#endif

    result = f_rename(drivers_oldfn, drivers_newfn);
#if _VOLUMES > 1
    rt_free(drivers_oldfn);
#endif
    return elm_result_to_dfs(result);
}

int dfs_elm_stat(struct dfs_filesystem *fs, const char *path, struct stat *st)
{
    FILINFO file_info;
    FRESULT result;

#if _VOLUMES > 1
    int vol;
    char *drivers_fn;
    extern int elm_get_vol(FATFS * fat);

    /* add path for ELM FatFS driver support */
    vol = elm_get_vol((FATFS *)fs->data);
    if (vol < 0)
        return -ENOENT;
    drivers_fn = rt_malloc(256);
    if (drivers_fn == RT_NULL)
        return -ENOMEM;

    rt_snprintf(drivers_fn, 256, "%d:%s", vol, path);
#else
    const char *drivers_fn;
    drivers_fn = path;
#endif

    result = f_stat(drivers_fn, &file_info);
#if _VOLUMES > 1
    rt_free(drivers_fn);
#endif
    if (result == FR_OK)
    {
        /* convert to dfs stat structure */
        st->st_dev = 0;

        st->st_mode = S_IFREG | S_IRUSR | S_IRGRP | S_IROTH |
                      S_IWUSR | S_IWGRP | S_IWOTH;
        if (file_info.fattrib & AM_DIR)
        {
            st->st_mode &= ~S_IFREG;
            st->st_mode |= S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;
        }
        if (file_info.fattrib & AM_RDO)
            st->st_mode &= ~(S_IWUSR | S_IWGRP | S_IWOTH);

        st->st_size  = file_info.fsize;

        /* get st_mtime. */
        {
            struct tm tm_file;
            int year, mon, day, hour, min, sec;
            WORD tmp;

            tmp = file_info.fdate;
            day = tmp & 0x1F;           /* bit[4:0] Day(1..31) */
            tmp >>= 5;
            mon = tmp & 0x0F;           /* bit[8:5] Month(1..12) */
            tmp >>= 4;
            year = (tmp & 0x7F) + 1980; /* bit[15:9] Year origin from 1980(0..127) */

            tmp = file_info.ftime;
            sec = (tmp & 0x1F) * 2;     /* bit[4:0] Second/2(0..29) */
            tmp >>= 5;
            min = tmp & 0x3F;           /* bit[10:5] Minute(0..59) */
            tmp >>= 6;
            hour = tmp & 0x1F;          /* bit[15:11] Hour(0..23) */

            memset(&tm_file, 0, sizeof(tm_file));
            tm_file.tm_year = year - 1900; /* Years since 1900 */
            tm_file.tm_mon  = mon - 1;     /* Months *since* january: 0-11 */
            tm_file.tm_mday = day;         /* Day of the month: 1-31 */
            tm_file.tm_hour = hour;        /* Hours since midnight: 0-23 */
            tm_file.tm_min  = min;         /* Minutes: 0-59 */
            tm_file.tm_sec  = sec;         /* Seconds: 0-59 */

            st->st_mtime = mktime(&tm_file);
        } /* get st_mtime. */
    }

    return elm_result_to_dfs(result);
}

static const struct dfs_file_ops dfs_elm_fops = 
{
    dfs_elm_open,
    dfs_elm_close,
    dfs_elm_ioctl,
    dfs_elm_read,
    dfs_elm_write,
    dfs_elm_flush,
    dfs_elm_lseek,
    dfs_elm_getdents,
    RT_NULL, /* poll interface */
};

static const struct dfs_filesystem_ops dfs_elm =
{
    "elm",
    DFS_FS_FLAG_DEFAULT,
    &dfs_elm_fops,

    dfs_elm_mount,
    dfs_elm_unmount,
    dfs_elm_mkfs,
    dfs_elm_statfs,

    dfs_elm_unlink,
    dfs_elm_stat,
    dfs_elm_rename,
};

int elm_init(void)
{
    /* register fatfs file system */
    dfs_register(&dfs_elm);

    return 0;
}
INIT_COMPONENT_EXPORT(elm_init);

/*
 * RT-Thread Device Interface for ELM FatFs
 */
#include "diskio.h"

/* Initialize a Drive */
DSTATUS disk_initialize(BYTE drv)
{
    return 0;
}

/* Return Disk Status */
DSTATUS disk_status(BYTE drv)
{
    return 0;
}

/* Read Sector(s) */
DRESULT disk_read (BYTE drv, BYTE* buff, DWORD sector, UINT count)
{
    rt_size_t result;
    rt_device_t device = disk[drv];

    result = rt_device_read(device, sector, buff, count);
    if (result == count)
    {
        return RES_OK;
    }

    return RES_ERROR;
}

/* Write Sector(s) */
DRESULT disk_write (BYTE drv, const BYTE* buff, DWORD sector, UINT count)
{
    rt_size_t result;
    rt_device_t device = disk[drv];

    result = rt_device_write(device, sector, buff, count);
    if (result == count)
    {
        return RES_OK;
    }

    return RES_ERROR;
}

/* Miscellaneous Functions */
DRESULT disk_ioctl(BYTE drv, BYTE ctrl, void *buff)
{
    rt_device_t device = disk[drv];

    if (device == RT_NULL)
        return RES_ERROR;

    if (ctrl == GET_SECTOR_COUNT)
    {
        struct rt_device_blk_geometry geometry;

        rt_memset(&geometry, 0, sizeof(geometry));
        rt_device_control(device, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry);

        *(DWORD *)buff = geometry.sector_count;
        if (geometry.sector_count == 0)
            return RES_ERROR;
    }
    else if (ctrl == GET_SECTOR_SIZE)
    {
        struct rt_device_blk_geometry geometry;

        rt_memset(&geometry, 0, sizeof(geometry));
        rt_device_control(device, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry);

        *(WORD *)buff = (WORD)(geometry.bytes_per_sector);
    }
    else if (ctrl == GET_BLOCK_SIZE) /* Get erase block size in unit of sectors (DWORD) */
    {
        struct rt_device_blk_geometry geometry;

        rt_memset(&geometry, 0, sizeof(geometry));
        rt_device_control(device, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry);

        *(DWORD *)buff = geometry.block_size / geometry.bytes_per_sector;
    }
    else if (ctrl == CTRL_SYNC)
    {
        rt_device_control(device, RT_DEVICE_CTRL_BLK_SYNC, RT_NULL);
    }
    else if (ctrl == CTRL_TRIM)
    {
        rt_device_control(device, RT_DEVICE_CTRL_BLK_ERASE, buff);
    }

    return RES_OK;
}

DWORD get_fattime(void)
{
    DWORD fat_time = 0;

#ifdef RT_USING_LIBC 
    time_t now;
    struct tm *p_tm;
    struct tm tm_now;

    /* get current time */
    now = time(RT_NULL);

    /* lock scheduler. */
    rt_enter_critical();
    /* converts calendar time time into local time. */
    p_tm = localtime(&now);
    /* copy the statically located variable */
    memcpy(&tm_now, p_tm, sizeof(struct tm));
    /* unlock scheduler. */
    rt_exit_critical();

    fat_time =  (DWORD)(tm_now.tm_year - 80) << 25 |
                (DWORD)(tm_now.tm_mon + 1)   << 21 |
                (DWORD)tm_now.tm_mday        << 16 |
                (DWORD)tm_now.tm_hour        << 11 |
                (DWORD)tm_now.tm_min         <<  5 |
                (DWORD)tm_now.tm_sec / 2 ;
#endif /* RT_USING_LIBC  */

    return fat_time;
}

#if _FS_REENTRANT
int ff_cre_syncobj(BYTE drv, _SYNC_t *m)
{
    char name[8];
    rt_mutex_t mutex;

    rt_snprintf(name, sizeof(name), "fat%d", drv);
    mutex = rt_mutex_create(name, RT_IPC_FLAG_FIFO);
    if (mutex != RT_NULL)
    {
        *m = mutex;
        return RT_TRUE;
    }

    return RT_FALSE;
}

int ff_del_syncobj(_SYNC_t m)
{
    if (m != RT_NULL)
        rt_mutex_delete(m);

    return RT_TRUE;
}

int ff_req_grant(_SYNC_t m)
{
    if (rt_mutex_take(m, _FS_TIMEOUT) == RT_EOK)
        return RT_TRUE;

    return RT_FALSE;
}

void ff_rel_grant(_SYNC_t m)
{
    rt_mutex_release(m);
}

#endif

/* Memory functions */
#if _USE_LFN == 3
/* Allocate memory block */
void *ff_memalloc(UINT size)
{
    return rt_malloc(size);
}

/* Free memory block */
void ff_memfree(void *mem)
{
    rt_free(mem);
}
#endif /* _USE_LFN == 3 */

