/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-1-7       prife        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include "cyg/infra/cyg_type.h"
#include "cyg/fileio/fileio.h"
#include "port/codes.h"
#include "port/fcntl.h"
#undef mode_t

#include <dfs_fs.h>
#include <dfs_file.h>

#include "dfs_jffs2.h"
#include "jffs2_config.h"
#include "porting.h"
#include <string.h>

#if DEVICE_PART_MAX > 1
    #error "support only one jffs2 partition on a flash device!"
#endif

/* make sure the following struct var had been initilased to 0! */
struct device_part
{
    struct cyg_mtab_entry * mte;
    struct rt_mtd_nor_device *dev;
};
static struct device_part device_partition[DEVICE_PART_MAX] = {0};
static struct rt_mutex jffs2_lock;

#define jffs2_mount         jffs2_fste.mount
#define jffs2_umount        jffs2_fste.umount
#define jffs2_open          jffs2_fste.open
#define jffs2_file_unlink   jffs2_fste.unlink
#define jffs2_mkdir         jffs2_fste.mkdir
#define jffs2_rmdir         jffs2_fste.rmdir
#define jffs2_rename        jffs2_fste.rename
#define jffs2_link          jffs2_fste.link
#define jffs2_opendir       jffs2_fste.opendir
#define jffs2_chdir         jffs2_fste.chdir
#define jffs2_ops_stat      jffs2_fste.stat
#define jffs2_getinfo       jffs2_fste.getinfo
#define jffs2_setinfo       jffs2_fste.setinfo

#define jffs2_file_read     jffs2_fileops.fo_read
#define jffs2_file_write    jffs2_fileops.fo_write
#define jffs2_file_lseek    jffs2_fileops.fo_lseek
#define jffs2_file_ioctl    jffs2_fileops.fo_ioctl
#define jffs2_file_select   jffs2_fileops.fo_select
#define jffs2_file_fsync    jffs2_fileops.fo_fsync
#define jffs2_file_colse    jffs2_fileops.fo_close
#define jffs2_file_fstat    jffs2_fileops.fo_fstat
#define jffs2_file_getinfo  jffs2_fileops.fo_getinfo
#define jffs2_file_setinfo  jffs2_fileops.fo_setinfo

#define jffs2_dir_read      jffs2_dirops.fo_read
//#define jffs2_dir_write   jffs2_dirops.fo_write
#define jffs2_dir_lseek     jffs2_dirops.fo_lseek
//#define jffs2_dir_ioctl   jffs2_dirops.fo_ioctl
#define jffs2_dir_select    jffs2_dirops.fo_select
//#define jffs2_dir_fsync   jffs2_dirops.fo_fsync
#define jffs2_dir_colse     jffs2_dirops.fo_close
//#define jffs2_dir_fstat   jffs2_dirops.fo_fstat
//#define jffs2_dir_getinfo jffs2_dirops.fo_getinfo
//#define jffs2_dir_setinfo jffs2_dirops.fo_setinfo

/*
 * RT-Thread Device Interface for jffs2
 */

/* these code is in src/flashio.c */
static int jffs2_result_to_dfs(int result)
{
    if (result < 0) return  result;
    if (result > 0) return -result;

    return 0;
}

/*
 * RT-Thread DFS Interface for jffs2
 */
static int dfs_jffs2_mount(struct dfs_filesystem* fs,
                    unsigned long rwflag,
                    const void* data)
{
    unsigned index;
    struct cyg_mtab_entry * mte;
    int result;

    /* find a empty entry in partition table */
    for (index = 0; index < DEVICE_PART_MAX; index ++)
    {
        if (device_partition[index].dev == RT_NULL)
            break;
    }
    if (index == DEVICE_PART_MAX)
        return -ENOSPC;

    mte = rt_malloc(sizeof(struct cyg_mtab_entry));
    if (mte == RT_NULL)
        return -ENOMEM;

    mte->name = fs->path;
    mte->fsname = "jffs2";
    mte->devname = NULL;
    /* note that, i use mte->data to store rtt's device
     * while, in jffs2_mount, mte->data will be copy into
     * s_dev in struct super_block, and mte->data will be
     * filled with jffs2_sb(see the source of jffs2_mount.
     */
    mte->data = (CYG_ADDRWORD)fs->dev_id;

    device_partition[index].dev = RT_MTD_NOR_DEVICE(fs->dev_id);
    /* after jffs2_mount, mte->data will not be dev_id any more */
    result = jffs2_mount(NULL, mte);
    if (result != 0)
    {
        device_partition[index].dev = NULL;
        return jffs2_result_to_dfs(result);
    }

    /* save this pointer */
    device_partition[index].mte = mte;
    return 0;
}

static int _find_fs(struct cyg_mtab_entry ** mte, rt_device_t dev_id)
{
    unsigned index;

    /* find device index */
    for (index = 0; index < DEVICE_PART_MAX; index++)
    {
        if (device_partition[index].dev == RT_MTD_NOR_DEVICE(dev_id))
        {
            *mte = device_partition[index].mte;
            return 0;
        }
    }

    rt_kprintf("error, could not found the fs!");
    return -1;
}

static int dfs_jffs2_unmount(struct dfs_filesystem* fs)
{
    int result;
    unsigned index;

    /* find device index, then umount it */
    for (index = 0; index < DEVICE_PART_MAX; index++)
    {
        if (device_partition[index].dev == RT_MTD_NOR_DEVICE(fs->dev_id))
        {
            result = jffs2_umount(device_partition[index].mte);
            if (result) return jffs2_result_to_dfs(result);

            rt_free(device_partition[index].mte);
            device_partition[index].dev = NULL;
            device_partition[index].mte = NULL;
            return RT_EOK;
        }
    }

    return -ENOENT;
}

static int dfs_jffs2_mkfs(rt_device_t dev_id)
{
    /* just erase all blocks on this nand partition */
    return -ENOSYS;
}

static int dfs_jffs2_statfs(struct dfs_filesystem* fs,
                     struct statfs *buf)
{
    /* since the limit of unsigned long, so the max size of flash device is 4G */
    struct cyg_mtab_entry * mte;
    struct jffs2_fs_info info;
    int result;

    result = _find_fs(&mte, fs->dev_id);
    if (result)
        return -ENOENT;

    RT_ASSERT(mte->data != 0);

    jffs2_get_info_from_sb((void *)mte->data, &info);
    buf->f_bsize = info.sector_size;
    buf->f_blocks = info.nr_blocks;
    buf->f_bfree = info.free_size / info.sector_size;

    return 0;
}

static const char jffs2_root_path[] = ".";

static int dfs_jffs2_open(struct dfs_fd* file)
{
    int result;
    int oflag, mode;
    const char * name;
    cyg_file * jffs2_file;
    struct dfs_filesystem *fs;
    struct cyg_mtab_entry * mte;

    oflag = file->flags;
    fs = (struct dfs_filesystem *)file->data;
    RT_ASSERT(fs != RT_NULL);

    jffs2_file = rt_malloc(sizeof(cyg_file));
    if (jffs2_file == RT_NULL)
        return -ENOMEM;

    /* just escape '/' provided by dfs code */
    name = file->path;
    if ((name[0] == '/') && (name[1] == 0))
        name = jffs2_root_path;
    else /* name[0] still will be '/' */
        name ++;

    result = _find_fs(&mte, fs->dev_id);
    if (result)
    {
        rt_free(jffs2_file);
        return -ENOENT;
    }

    /* set mount table */
    jffs2_file->f_mte = mte;

    if (oflag & O_DIRECTORY) /* operations about dir */
    {
        rt_mutex_take(&jffs2_lock, RT_WAITING_FOREVER);
        if (oflag & O_CREAT) /* create a dir*/
        {
            /* fixme, should test file->path can end with '/' */
            result = jffs2_mkdir(mte, mte->root, name);
            if (result)
            {
                rt_mutex_release(&jffs2_lock);
                rt_free(jffs2_file);
                return jffs2_result_to_dfs(result);
            }
        }

        /* open dir */
        result = jffs2_opendir(mte, mte->root, name, jffs2_file);
        rt_mutex_release(&jffs2_lock);
        if (result)
        {
            rt_free(jffs2_file);
            return jffs2_result_to_dfs(result);
        }
#ifdef  CONFIG_JFFS2_NO_RELATIVEDIR
        jffs2_file->f_offset = 2;
#endif
        /* save this pointer, it will be used by dfs_jffs2_getdents*/
        file->data = jffs2_file;
        return 0;
    }
    /* regular file operations */
    mode = JFFS2_O_RDONLY;
    if (oflag & O_WRONLY) mode |= JFFS2_O_WRONLY;
    if (oflag & O_RDWR)   mode |= JFFS2_O_RDWR;
    /* Opens the file, if it is existing. If not, a new file is created. */
    if (oflag & O_CREAT) mode |= JFFS2_O_CREAT;
    /* Creates a new file. If the file is existing, it is truncated and overwritten. */
    if (oflag & O_TRUNC) mode |= JFFS2_O_TRUNC;
    /* Creates a new file. The function fails if the file is already existing. */
    if (oflag & O_EXCL) mode |= JFFS2_O_EXCL;

    rt_mutex_take(&jffs2_lock, RT_WAITING_FOREVER);
    result = jffs2_open(mte, 0, name, mode, jffs2_file);
    if (result != 0)
    {
        rt_mutex_release(&jffs2_lock);
        rt_free(jffs2_file);
        return jffs2_result_to_dfs(result);
    }

    /* save this pointer, it will be used when calling read(), write(),
    flush(), lessk(), and will be rt_free when calling close()*/
    file->data = jffs2_file;
    file->pos = jffs2_file->f_offset;
    file->size = 0;
    jffs2_file_lseek(jffs2_file, (off_t *)(&(file->size)), SEEK_END);
    jffs2_file->f_offset = (off_t)file->pos;
    rt_mutex_release(&jffs2_lock);

    if (oflag & O_APPEND)
    {
        file->pos = file->size;
        jffs2_file->f_offset = file->size;
    }

    return 0;
}

static int dfs_jffs2_close(struct dfs_fd* file)
{
    int result;
    cyg_file * jffs2_file;

    RT_ASSERT(file->data != NULL);
    jffs2_file = (cyg_file *)(file->data);

    if (file->flags & O_DIRECTORY) /* operations about dir */
    {
        rt_mutex_take(&jffs2_lock, RT_WAITING_FOREVER);
        result = jffs2_dir_colse(jffs2_file);
        rt_mutex_release(&jffs2_lock);
        if (result)
            return jffs2_result_to_dfs(result);

        rt_free(jffs2_file);
        return 0;
    }
    /* regular file operations */
    rt_mutex_take(&jffs2_lock, RT_WAITING_FOREVER);
    result = jffs2_file_colse(jffs2_file);
    rt_mutex_release(&jffs2_lock);
    if (result)
        return jffs2_result_to_dfs(result);

    /* release memory */
    rt_free(jffs2_file);
    return 0;
}

static int dfs_jffs2_ioctl(struct dfs_fd* file, int cmd, void* args)
{
    return -ENOSYS;
}

static int dfs_jffs2_read(struct dfs_fd* file, void* buf, size_t len)
{
    cyg_file * jffs2_file;
    struct CYG_UIO_TAG uio_s;
    struct CYG_IOVEC_TAG iovec;
    int char_read;
    int result;

    RT_ASSERT(file->data != NULL);
    jffs2_file = (cyg_file *)(file->data);
    uio_s.uio_iov = &iovec;
    uio_s.uio_iov->iov_base = buf;
    uio_s.uio_iov->iov_len = len;
    uio_s.uio_iovcnt = 1; //must be 1
    //uio_s.uio_offset //not used...
    uio_s.uio_resid = uio_s.uio_iov->iov_len; //seem no use in jffs2;

    char_read = jffs2_file->f_offset; /* the current offset */
    rt_mutex_take(&jffs2_lock, RT_WAITING_FOREVER);
    result = jffs2_file_read(jffs2_file, &uio_s);
    rt_mutex_release(&jffs2_lock);
    if (result)
        return jffs2_result_to_dfs(result);

    /* update position */
    file->pos = jffs2_file->f_offset;
    char_read = jffs2_file->f_offset - char_read;
    return char_read;
}

static int dfs_jffs2_write(struct dfs_fd* file,
                    const void* buf,
                    size_t len)
{
    cyg_file * jffs2_file;
    struct CYG_UIO_TAG uio_s;
    struct CYG_IOVEC_TAG iovec;
    int char_write;
    int result;

    RT_ASSERT(file->data != NULL);
    jffs2_file = (cyg_file *)(file->data);
    uio_s.uio_iov = &iovec;
    uio_s.uio_iov->iov_base = (void *)buf;
    uio_s.uio_iov->iov_len = len;
    uio_s.uio_iovcnt = 1; //must be 1
    //uio_s.uio_offset //not used...
    uio_s.uio_resid = uio_s.uio_iov->iov_len; //seem no use in jffs2;

    char_write = jffs2_file->f_offset;
    rt_mutex_take(&jffs2_lock, RT_WAITING_FOREVER);
    result = jffs2_file_write(jffs2_file, &uio_s);
    rt_mutex_release(&jffs2_lock);
    if (result)
        return jffs2_result_to_dfs(result);

    /* update position */
    file->pos = jffs2_file->f_offset;
    char_write = jffs2_file->f_offset - char_write;
    return char_write;
}

static int dfs_jffs2_flush(struct dfs_fd* file)
{
    /* infact, jffs2 not support, jffs2_fo_sync just return ok */
    return -ENOSYS;
}

/* fixme warning: the offset is rt_off_t, so maybe the size of a file is must <= 2G*/
static int dfs_jffs2_lseek(struct dfs_fd* file,
                    rt_off_t offset)
{
    cyg_file * jffs2_file;
    int result;

    RT_ASSERT(file->data != NULL);
    jffs2_file = (cyg_file *)(file->data);

    /* set offset as current offset */
    rt_mutex_take(&jffs2_lock, RT_WAITING_FOREVER);
    result = jffs2_file_lseek(jffs2_file, &offset, SEEK_SET);
    rt_mutex_release(&jffs2_lock);
    if (result)
        return jffs2_result_to_dfs(result);
    /* update file position */
    file->pos = offset;
    return offset;
}

/* return the size of  struct dirent*/
static int dfs_jffs2_getdents(struct dfs_fd* file,
                       struct dirent* dirp,
                       rt_uint32_t count)
{
    cyg_file * jffs2_file;
    struct CYG_UIO_TAG uio_s;
    struct CYG_IOVEC_TAG iovec;
    struct jffs2_dirent jffs2_d;
    struct dirent * d;
    rt_uint32_t index;
#if !defined (CYGPKG_FS_JFFS2_RET_DIRENT_DTYPE)
    struct jffs2_stat s;
    cyg_mtab_entry * mte;
    char * fullname;
#endif
    int result;

    RT_ASSERT(file->data != RT_NULL);
    jffs2_file = (cyg_file*)(file->data);
    mte = jffs2_file->f_mte;

    //set jffs2_d
    memset(&jffs2_d, 0, sizeof(struct jffs2_dirent));
    //set CYG_UIO_TAG uio_s
    uio_s.uio_iov = &iovec;
    uio_s.uio_iov->iov_base = &jffs2_d;
    uio_s.uio_iov->iov_len = sizeof(struct jffs2_dirent);;
    uio_s.uio_iovcnt = 1; //must be 1
    uio_s.uio_offset = 0;//not used...
    uio_s.uio_resid = uio_s.uio_iov->iov_len; //seem no use in jffs2;

    /* make integer count, usually count is 1 */
    count = (count / sizeof(struct dirent)) * sizeof(struct dirent);
    if (count == 0) return -EINVAL;

    index = 0;
    /* usually, the while loop should only be looped only once! */
    while (1)
    {
        d = dirp + index;
        rt_mutex_take(&jffs2_lock, RT_WAITING_FOREVER);
        result = jffs2_dir_read(jffs2_file, &uio_s);
        rt_mutex_release(&jffs2_lock);
        /* if met a error or all entry are read over, break while*/
        if (result || jffs2_d.d_name[0] == 0)
            break;

#if defined (CYGPKG_FS_JFFS2_RET_DIRENT_DTYPE)
        switch(jffs2_d.d_type & JFFS2_S_IFMT)
        {
        case JFFS2_S_IFREG: d->d_type = DT_REG; break;
        case JFFS2_S_IFDIR: d->d_type = DT_DIR; break;
        default: d->d_type = DT_UNKNOWN; break;
        }
#else
        fullname = rt_malloc(FILE_PATH_MAX);
        if(fullname == RT_NULL)
                return -ENOMEM;

        /* make a right entry */
        if ((file->path[0] == '/') )
        {
            if (file->path[1] == 0)
                strcpy(fullname, jffs2_d.d_name);
            else
                rt_sprintf(fullname, "%s/%s", file->path+1, jffs2_d.d_name);
        }
        else
            rt_sprintf(fullname, "%s/%s", file->path, jffs2_d.d_name);
        rt_mutex_take(&jffs2_lock, RT_WAITING_FOREVER);
        result = jffs2_porting_stat(mte, mte->root, fullname, (void *)&s);
        rt_mutex_release(&jffs2_lock);
        if (result)
            return jffs2_result_to_dfs(result);

        rt_free(fullname);
        /* convert to dfs stat structure */
        switch(s.st_mode & JFFS2_S_IFMT)
        {
        case JFFS2_S_IFREG: d->d_type = DT_REG; break;
        case JFFS2_S_IFDIR: d->d_type = DT_DIR; break;
        default: d->d_type = DT_UNKNOWN; break;
        }
#endif
        /* write the rest fields of struct dirent* dirp  */
        d->d_namlen = rt_strlen(jffs2_d.d_name);
        d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
        rt_strncpy(d->d_name, jffs2_d.d_name, d->d_namlen + 1);

        index ++;
        if (index * sizeof(struct dirent) >= count)
            break;
    }
    if (result)
        return jffs2_result_to_dfs(result);
    return index * sizeof(struct dirent);
}

static int dfs_jffs2_unlink(struct dfs_filesystem* fs, const char* path)
{
    int result;
    struct jffs2_stat s;
    cyg_mtab_entry * mte;

    result = _find_fs(&mte, fs->dev_id);
    if (result)
        return -ENOENT;

    /* deal path */
    if (path[0] == '/')
        path++;

    /* judge file type, dir is to be delete by rmdir, others by unlink */
    rt_mutex_take(&jffs2_lock, RT_WAITING_FOREVER);
    result = jffs2_porting_stat(mte, mte->root, path, (void *)&s);
    if (result)
    {
        rt_mutex_release(&jffs2_lock);
        return jffs2_result_to_dfs(result);
    }

    switch(s.st_mode & JFFS2_S_IFMT)
    {
    case JFFS2_S_IFREG:
        result = jffs2_file_unlink(mte, mte->root, path);
        break;
    case JFFS2_S_IFDIR:
        result = jffs2_rmdir(mte, mte->root, path);
        break;
    default:
        /* unknown file type */
        rt_mutex_release(&jffs2_lock);
        return -1;
    }
    rt_mutex_release(&jffs2_lock);
    if (result)
        return jffs2_result_to_dfs(result);
    return 0;
}

static int dfs_jffs2_rename(struct dfs_filesystem* fs,
                     const char* oldpath,
                     const char* newpath)
{
    int result;
    cyg_mtab_entry * mte;

    result = _find_fs(&mte, fs->dev_id);
    if (result)
        return -ENOENT;

    if (*oldpath == '/')
        oldpath += 1;
    if (*newpath == '/')
        newpath += 1;
    rt_mutex_take(&jffs2_lock, RT_WAITING_FOREVER);
    result = jffs2_rename(mte, mte->root, oldpath, mte->root, newpath);
    rt_mutex_release(&jffs2_lock);
    if (result)
        return jffs2_result_to_dfs(result);
    return 0;
}

static int dfs_jffs2_stat(struct dfs_filesystem* fs, const char *path, struct stat *st)
{
    int result;
    struct jffs2_stat s;
    cyg_mtab_entry * mte;

    /* deal the path for jffs2 */
    RT_ASSERT(!((path[0] == '/') && (path[1] == 0)));

    if (path[0] == '/')
        path++;

    result = _find_fs(&mte, fs->dev_id);
    if (result)
        return -ENOENT;

    rt_mutex_take(&jffs2_lock, RT_WAITING_FOREVER);
    result = jffs2_porting_stat(mte, mte->root, path, (void *)&s);
    rt_mutex_release(&jffs2_lock);

    if (result)
        return jffs2_result_to_dfs(result);
    /* convert to dfs stat structure */
    switch(s.st_mode & JFFS2_S_IFMT)
    {
    case JFFS2_S_IFREG:
        st->st_mode = S_IFREG | S_IRUSR | S_IRGRP | S_IROTH |
            S_IWUSR | S_IWGRP | S_IWOTH;
        break;

    case JFFS2_S_IFDIR:
        st->st_mode = S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;
        break;

    default:
        st->st_mode = DT_UNKNOWN; //fixme
        break;
    }

    st->st_dev  = 0;
    st->st_size = s.st_size;
    st->st_mtime = s.st_mtime;

    return 0;
}

static const struct dfs_file_ops _jffs2_fops =
{
    dfs_jffs2_open,
    dfs_jffs2_close,
    dfs_jffs2_ioctl,
    dfs_jffs2_read,
    dfs_jffs2_write,
    dfs_jffs2_flush,
    dfs_jffs2_lseek,
    dfs_jffs2_getdents,
};

static const struct dfs_filesystem_ops _jffs2_ops =
{
    "jffs2",
    DFS_FS_FLAG_DEFAULT,
    &_jffs2_fops,

    dfs_jffs2_mount,
    dfs_jffs2_unmount,
    dfs_jffs2_mkfs,
    dfs_jffs2_statfs,

    dfs_jffs2_unlink,
    dfs_jffs2_stat,
    dfs_jffs2_rename,
};

int dfs_jffs2_init(void)
{
    /* register fatfs file system */
    dfs_register(&_jffs2_ops);

    /* initialize mutex */
    if (rt_mutex_init(&jffs2_lock, "jffs2lock", RT_IPC_FLAG_FIFO) != RT_EOK)
    {
        rt_kprintf("init jffs2 lock mutex failed\n");
    }
    rt_kprintf("init jffs2 lock mutex okay\n");
    return 0;
}
INIT_COMPONENT_EXPORT(dfs_jffs2_init);
