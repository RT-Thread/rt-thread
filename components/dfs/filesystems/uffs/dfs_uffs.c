/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-10-22     prife        the first version
 * 2012-03-28     prife        use mtd device interface
 * 2012-04-05     prife        update uffs with official repo and use uffs_UnMount/Mount
 * 2017-04-12     lizhen9880   fix the f_bsize and f_blocks issue in function dfs_uffs_statfs
 */

#include <rtthread.h>

#include <dfs_fs.h>
#include <dfs_file.h>
#include <rtdevice.h>

#include "dfs_uffs.h"

#include "uffs/uffs_fd.h" /* posix file api is here */
#include "uffs/uffs_mtb.h"
#include "uffs/uffs_mem.h"
#include "uffs/uffs_utils.h"

/*
 * RT-Thread DFS Interface for uffs
 */
#define UFFS_DEVICE_MAX         2    /* the max partions on a nand deivce*/
#define UFFS_MOUNT_PATH_MAX     128  /* the mount point max length */
#define FILE_PATH_MAX           256  /* the longest file path */

struct _nand_dev
{
    struct rt_mtd_nand_device * dev;
    struct uffs_StorageAttrSt storage;
    uffs_Device uffs_dev;
    uffs_MountTable mount_table;
    char mount_path[UFFS_MOUNT_PATH_MAX];
    void * data;  /* when uffs use static buf, it will save ptr here */ 
};
/* make sure the following struct var had been initilased to 0! */
static struct _nand_dev nand_part[UFFS_DEVICE_MAX] = {0};

static int uffs_result_to_dfs(int result)
{
    int status = -1;

    result = result < 0 ? -result : result;
    switch (result)
    {
    case UENOERR:/** no error */
        break;
    case UEACCES:/** Tried to open read-only file for writing, or files sharing mode
                   does not allow specified operations, or given path is directory */
        status = -EINVAL;
        break;/* no suitable */
    case UEEXIST:   /** _O_CREAT and _O_EXCL flags specified, but filename already exists */
        status = -EEXIST;
        break;
    case UEINVAL:  /** Invalid oflag or pmode argument */
        status = -EINVAL;
        break;
    case UEMFILE: /** No more file handles available(too many open files)  */
        status = -1;
        break;
    case UENOENT: /** file or path not found */
        status = -ENOENT;
        break;
    case UETIME: /** can't set file time */
        status = -1;
        break;
    case UEBADF: /** invalid file handle */
        status = -EBADF;
        break;
    case UENOMEM:/** no enough memory */
        status = -ENOSPC;
        break;
    case UEIOERR: /** I/O error from lower level flash operation */
        status = -EIO;
        break;
    case UENOTDIR: /** Not a directory */
        status = -ENOTDIR;
        break;
    case UEISDIR: /** Is a directory */
        status = -EISDIR;
        break;
    case UEUNKNOWN_ERR:
    default:
        status = -1;
        break; /* unknown error! */
    }

    return status;
}

static URET _device_init(uffs_Device *dev)
{
    dev->attr->_private = NULL; // hook nand_chip data structure to attr->_private
    dev->ops = (struct uffs_FlashOpsSt *)&nand_ops;

    return U_SUCC;
}

static URET _device_release(uffs_Device *dev)
{
    return U_SUCC;
}

static int init_uffs_fs(
    struct _nand_dev * nand_part)
{
    uffs_MountTable * mtb;
    struct rt_mtd_nand_device * nand;
    struct uffs_StorageAttrSt * flash_storage;

    mtb = &nand_part->mount_table;
    nand = nand_part->dev;
    flash_storage = &nand_part->storage;

    /* setup nand storage attributes */
    uffs_setup_storage(flash_storage, nand);

    /* register mount table */
    if(mtb->dev)
    {
        /* set memory allocator for uffs */
#if CONFIG_USE_SYSTEM_MEMORY_ALLOCATOR > 0
        uffs_MemSetupSystemAllocator(&mtb->dev->mem);
#endif
        /* setup device init/release entry */
        mtb->dev->Init = _device_init;
        mtb->dev->Release = _device_release;
        mtb->dev->attr = flash_storage;

        uffs_RegisterMountTable(mtb);
    }
    /* mount uffs partion on nand device */
    return uffs_Mount(nand_part->mount_path) == U_SUCC ? 0 : -1;
}

static int dfs_uffs_mount(
    struct dfs_filesystem* fs,
    unsigned long rwflag,
    const void* data)
{
    rt_base_t index;
    uffs_MountTable * mount_part;
    struct rt_mtd_nand_device * dev;
    
    RT_ASSERT(rt_strlen(fs->path) < (UFFS_MOUNT_PATH_MAX-1));
    dev = RT_MTD_NAND_DEVICE(fs->dev_id);

    /*1. find a empty entry in partition table */
    for (index = 0; index < UFFS_DEVICE_MAX ; index ++)
    {
        if (nand_part[index].dev == RT_NULL)
            break;
    }
    if (index == UFFS_DEVICE_MAX)
        return -ENOENT;

    /*2. fill partition structure */
    nand_part[index].dev = dev;

    /* make a right mount path for uffs, end with '/' */
    rt_snprintf(nand_part[index].mount_path, UFFS_MOUNT_PATH_MAX, "%s/", fs->path);
    if (nand_part[index].mount_path[1] == '/')
        nand_part[index].mount_path[1] = 0;

    mount_part = &(nand_part[index].mount_table);
    mount_part->mount   = nand_part[index].mount_path;
    mount_part->dev = &(nand_part[index].uffs_dev);
    rt_memset(mount_part->dev, 0, sizeof(uffs_Device));//in order to make uffs happy.
    mount_part->dev->_private = dev;   /* save dev_id into uffs */
    mount_part->start_block = dev->block_start;
    mount_part->end_block = dev->block_end;
    /*3. mount uffs */
    if (init_uffs_fs(&nand_part[index]) < 0)
    {
        return uffs_result_to_dfs(uffs_get_error());
    }
    return 0;
}

static int dfs_uffs_unmount(struct dfs_filesystem* fs)
{
    rt_base_t index;
    int result;

    /* find the device index and then unmount it */
    for (index = 0; index < UFFS_DEVICE_MAX; index++)
    {
        if (nand_part[index].dev == RT_MTD_NAND_DEVICE(fs->dev_id))
        {
            nand_part[index].dev = RT_NULL;
            result = uffs_UnMount(nand_part[index].mount_path);
            if (result != U_SUCC)
                break;

            result = uffs_UnRegisterMountTable(& nand_part[index].mount_table);
            return (result == U_SUCC) ? RT_EOK : -1;
        }
    }
    return -ENOENT;
}

static int dfs_uffs_mkfs(rt_device_t dev_id)
{
    rt_base_t index;
    rt_uint32_t block;
    struct rt_mtd_nand_device * mtd;

    /*1. find the device index */
    for (index = 0; index < UFFS_DEVICE_MAX; index++)
    {
        if (nand_part[index].dev == (struct rt_mtd_nand_device *)dev_id)
            break;
    }

    if (index == UFFS_DEVICE_MAX)
    {
        /* can't find device driver */
        return -ENOENT;
    }

    /*2. then unmount the partition */
    uffs_Mount(nand_part[index].mount_path);
    mtd = nand_part[index].dev;

    /*3. erase all blocks on the partition */
    block = mtd->block_start;
    for (; block <= mtd->block_end; block++)
    {
        rt_mtd_nand_erase_block(mtd, block);
        if (rt_mtd_nand_check_block(mtd, block) != RT_EOK)
        {
            rt_kprintf("found bad block %d\n", block);
            rt_mtd_nand_mark_badblock(mtd, block);
        }
    }

    /*4. remount it */
    if (init_uffs_fs(&nand_part[index]) < 0)
    {
        return uffs_result_to_dfs(uffs_get_error());
    }
    return RT_EOK;
}

static int dfs_uffs_statfs(struct dfs_filesystem* fs,
                    struct statfs *buf)
{
    rt_base_t index;
    struct rt_mtd_nand_device * mtd = RT_MTD_NAND_DEVICE(fs->dev_id);

    RT_ASSERT(mtd != RT_NULL);

    /* find the device index */
    for (index = 0; index < UFFS_DEVICE_MAX; index++)
    {
        if (nand_part[index].dev == (void *)mtd)
            break;
    }
    if (index == UFFS_DEVICE_MAX)
        return -ENOENT;
    
    buf->f_bsize = mtd->page_size*mtd->pages_per_block;
    buf->f_blocks = (mtd->block_end - mtd->block_start + 1);
    buf->f_bfree = uffs_GetDeviceFree(&nand_part[index].uffs_dev)/buf->f_bsize ;
    
    return 0;
}

static int dfs_uffs_open(struct dfs_fd* file)
{
    int fd;
    int oflag, mode;
    char * file_path;

    oflag = file->flags;
    if (oflag & O_DIRECTORY)   /* operations about dir */
    {
        uffs_DIR * dir;

        if (oflag & O_CREAT)   /* create a dir*/
        {
            if (uffs_mkdir(file->path) < 0)
                return uffs_result_to_dfs(uffs_get_error());
        }
        /* open dir */
        file_path = rt_malloc(FILE_PATH_MAX);
        if(file_path == RT_NULL)
            return -ENOMEM;         

        if (file->path[0] == '/' && !(file->path[1] == 0))
            rt_snprintf(file_path, FILE_PATH_MAX, "%s/", file->path);
        else
        {
            file_path[0] = '/';
            file_path[1] = 0;
        }

        dir = uffs_opendir(file_path);

        if (dir == RT_NULL)
        {
            rt_free(file_path);         
            return uffs_result_to_dfs(uffs_get_error());
        }
        /* save this pointer,will used by  dfs_uffs_getdents*/
        file->data = dir;
        rt_free(file_path);
        return RT_EOK;
    }
    /* regular file operations */
    /* int uffs_open(const char *name, int oflag, ...); what is this?
     * uffs_open can open dir!!  **/
    mode = 0;
    if (oflag & O_RDONLY) mode |= UO_RDONLY;
    if (oflag & O_WRONLY) mode |= UO_WRONLY;
    if (oflag & O_RDWR)   mode |= UO_RDWR;
    /* Opens the file, if it is existing. If not, a new file is created. */
    if (oflag & O_CREAT) mode |= UO_CREATE;
    /* Creates a new file. If the file is existing, it is truncated and overwritten. */
    if (oflag & O_TRUNC) mode |= UO_TRUNC;
    /* Creates a new file. The function fails if the file is already existing. */
    if (oflag & O_EXCL) mode |= UO_EXCL;

    fd = uffs_open(file->path, mode);
    if (fd < 0)
    {
        return uffs_result_to_dfs(uffs_get_error());
    }

    /* save this pointer, it will be used when calling read(), write(),
     * flush(), seek(), and will be free when calling close()*/

    file->data = (void *)fd;
    file->pos  = uffs_seek(fd, 0, USEEK_CUR);
    file->size = uffs_seek(fd, 0, USEEK_END);
    uffs_seek(fd, file->pos, USEEK_SET);

    if (oflag & O_APPEND)
    {
        file->pos = uffs_seek(fd, 0, USEEK_END);
    }
    return 0;
}

static int dfs_uffs_close(struct dfs_fd* file)
{
    int oflag;
    int fd;

    oflag = file->flags;
    if (oflag & O_DIRECTORY)
    {
        /* operations about dir */
        if (uffs_closedir((uffs_DIR *)(file->data)) < 0)
            return uffs_result_to_dfs(uffs_get_error());

        return 0;
    }
    /* regular file operations */
    fd = (int)(file->data);

    if (uffs_close(fd) == 0)
        return 0;

    return uffs_result_to_dfs(uffs_get_error());
}

static int dfs_uffs_ioctl(struct dfs_fd * file, int cmd, void* args)
{
    return -ENOSYS;
}

static int dfs_uffs_read(struct dfs_fd * file, void* buf, size_t len)
{
    int fd;
    int char_read;

    fd = (int)(file->data);
    char_read = uffs_read(fd, buf, len);
    if (char_read < 0)
        return uffs_result_to_dfs(uffs_get_error());

    /* update position */
    file->pos = uffs_seek(fd, 0, USEEK_CUR);
    return char_read;
}

static int dfs_uffs_write(struct dfs_fd* file,
                   const void* buf,
                   size_t len)
{
    int fd;
    int char_write;

    fd = (int)(file->data);

    char_write = uffs_write(fd, buf, len);
    if (char_write < 0)
        return uffs_result_to_dfs(uffs_get_error());

    /* update position */
    file->pos = uffs_seek(fd, 0, USEEK_CUR);
    return char_write;
}

static int dfs_uffs_flush(struct dfs_fd* file)
{
    int fd;
    int result;

    fd = (int)(file->data);

    result = uffs_flush(fd);
    if (result < 0 )
        return uffs_result_to_dfs(uffs_get_error());
    return 0;
}

int uffs_seekdir(uffs_DIR *dir, long offset)
{
    int i = 0;

    while(i < offset)
    {   
        if (uffs_readdir(dir) == RT_NULL)
            return -1;
        i++;
    } 
    return 0;
}


static int dfs_uffs_seek(struct dfs_fd* file,
                  rt_off_t offset)
{
    int result;

    /* set offset as current offset */
    if (file->type == FT_DIRECTORY)
    {
        uffs_rewinddir((uffs_DIR *)(file->data));
        result = uffs_seekdir((uffs_DIR *)(file->data), offset/sizeof(struct dirent));
        if (result >= 0)
        {
            file->pos = offset; 
            return offset;
        }
    }
    else if (file->type == FT_REGULAR)
    {
        result = uffs_seek((int)(file->data), offset, USEEK_SET);
        if (result >= 0)    
            return offset;
    }

    return uffs_result_to_dfs(uffs_get_error());
}

/* return the size of struct dirent*/
static int dfs_uffs_getdents(
    struct dfs_fd* file,
    struct dirent* dirp,
    uint32_t count)
{
    rt_uint32_t index;
    char * file_path;
    struct dirent* d;
    uffs_DIR* dir;
    struct uffs_dirent * uffs_d;
    
    dir = (uffs_DIR*)(file->data);
    RT_ASSERT(dir != RT_NULL);
    
    /* round count, count is always 1 */
    count = (count / sizeof(struct dirent)) * sizeof(struct dirent);
    if (count == 0) return -EINVAL;

    /* allocate file name */
    file_path = rt_malloc(FILE_PATH_MAX);
    if (file_path == RT_NULL)
        return -ENOMEM;
        
    index = 0;
    /* usually, the while loop should only be looped only once! */
    while (1)
    {
        struct uffs_stat s;
        
        d = dirp + index;

        uffs_d = uffs_readdir(dir);
        if (uffs_d == RT_NULL)
        {
            rt_free(file_path);
            return (uffs_result_to_dfs(uffs_get_error()));
        }

        if (file->path[0] == '/' && !(file->path[1] == 0))
            rt_snprintf(file_path, FILE_PATH_MAX, "%s/%s", file->path, uffs_d->d_name);
        else
            rt_strncpy(file_path, uffs_d->d_name, FILE_PATH_MAX);

        uffs_stat(file_path, &s); 
        switch(s.st_mode & US_IFMT)   /* file type mark */
        {
        case US_IFREG: /* directory */
            d->d_type = DT_REG;
            break;
        case US_IFDIR: /* regular file */
            d->d_type = DT_DIR;
            break;
        case US_IFLNK: /* symbolic link */
        case US_IREAD: /* read permission */
        case US_IWRITE:/* write permission */
        default:
            d->d_type = DT_UNKNOWN;
            break;
        }

        /* write the rest args of struct dirent* dirp  */
        d->d_namlen = rt_strlen(uffs_d->d_name);
        d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
        rt_strncpy(d->d_name, uffs_d->d_name, rt_strlen(uffs_d->d_name) + 1);

        index ++;
        if (index * sizeof(struct dirent) >= count)
            break;
    }
    
    /* free file name buf */
    rt_free(file_path);
    
    if (index == 0)
        return uffs_result_to_dfs(uffs_get_error());

    file->pos += index * sizeof(struct dirent);

    return index * sizeof(struct dirent);
}

static int dfs_uffs_unlink(struct dfs_filesystem* fs, const char* path)
{
    int result;
    struct uffs_stat s;

    /* judge file type, dir is to be delete by uffs_rmdir, others by uffs_remove */
    if (uffs_lstat(path, &s) < 0)
    {
        return uffs_result_to_dfs(uffs_get_error());
    }

    switch(s.st_mode & US_IFMT)
    {
    case US_IFREG:
        result = uffs_remove(path);
        break;
    case US_IFDIR:
        result = uffs_rmdir(path);
        break;
    default:
        /* unknown file type */
        return -1;
    }
    if (result < 0)
        return uffs_result_to_dfs(uffs_get_error());

    return 0;
}

static int dfs_uffs_rename(
    struct dfs_filesystem* fs,
    const char* oldpath,
    const char* newpath)
{
    int result;
    
    result = uffs_rename(oldpath, newpath);
    if (result < 0)
        return uffs_result_to_dfs(uffs_get_error());

    return 0;
}

static int dfs_uffs_stat(struct dfs_filesystem* fs, const char *path, struct stat *st)
{
    int result;
    struct uffs_stat s;

    result = uffs_stat(path, &s);
    if (result < 0)
        return uffs_result_to_dfs(uffs_get_error());

    /* convert uffs stat to dfs stat structure */
    /* FIXME, these field may not be the same */
    st->st_dev  = 0;
    st->st_mode = s.st_mode;
    st->st_size = s.st_size;
    st->st_mtime = s.st_mtime;

    return 0;
}

static const struct dfs_file_ops dfs_uffs_fops = 
{
    dfs_uffs_open,
    dfs_uffs_close,
    dfs_uffs_ioctl,
    dfs_uffs_read,
    dfs_uffs_write,
    dfs_uffs_flush,
    dfs_uffs_seek,
    dfs_uffs_getdents,
};

static const struct dfs_filesystem_ops dfs_uffs_ops =
{
    "uffs", /* file system type: uffs */
#if RTTHREAD_VERSION >= 10100
    DFS_FS_FLAG_FULLPATH,
#else
#error "uffs can only work with rtthread whose version should >= 1.01\n"
#endif
    &dfs_uffs_fops,

    dfs_uffs_mount,
    dfs_uffs_unmount,
    dfs_uffs_mkfs,
    dfs_uffs_statfs,

    dfs_uffs_unlink,
    dfs_uffs_stat,
    dfs_uffs_rename,
};

int dfs_uffs_init(void)
{
    /* register uffs file system */
    dfs_register(&dfs_uffs_ops);

    if (uffs_InitObjectBuf() == U_SUCC)
    {
        if (uffs_DirEntryBufInit() == U_SUCC)
        {
            uffs_InitGlobalFsLock();
            return RT_EOK;
        }
    }
    return -RT_ERROR;
}
INIT_COMPONENT_EXPORT(dfs_uffs_init);

