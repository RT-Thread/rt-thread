/*
 * Copyright (c) 2017 Christopher Haster
 * Distributed under the MIT license
 */
#include <rtthread.h>
//#include "fal.h"

#include "lfs.h"
#include "lfs_util.h"

#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define HAVE_DIR_STRUCTURE

#include <dfs_fs.h>
#include <dfs_file.h>

// config and other state
static struct lfs_config config = {0};
static lfs_t lfs;


static int lfs_result_to_dfs(int result)
{
    int status = RT_EOK;

    switch ( result )
    {
        case LFS_ERR_OK:
            break;
            
        case LFS_ERR_IO:
            status = -EIO;
            break;
            
        case LFS_ERR_CORRUPT:
            status = -EBADF;
            break;
            
        case LFS_ERR_NOENT:
            status = -ENOENT;
            break;
			
        case LFS_ERR_EXIST:
            status = -EEXIST;
            break;
            
        case LFS_ERR_NOTDIR:
            status = -ENOTDIR;
            break;
            
        case LFS_ERR_ISDIR:
            status = -EISDIR;
            break;
            
        case LFS_ERR_NOTEMPTY:
            status = -ENOTEMPTY;
            break;
            
        case LFS_ERR_BADF:
            status = -EBADF;
            break;
            
        case LFS_ERR_INVAL:
            status = -EINVAL;
            break;
            
        case LFS_ERR_NOSPC:
            status = -ENOSPC;
            break;
        case LFS_ERR_NOMEM:
            status = -ENOMEM;
            break;
        default:
            status = -1;
            break;
    }

    return status;
}

int dfs_lfs_mkfs(rt_device_t devid)
{
    int result;
    struct rt_device_blk_geometry geometry;

    /* check sector size */
    if (rt_device_control(devid, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry) != RT_EOK)
    {
        rt_kprintf("get sector size fail of lfs.\n");
        return -EINVAL;
    }

    config.block_count = geometry.sector_count;
    config.block_size  = geometry.block_size;
    config.read_size   = geometry.bytes_per_sector;
    config.prog_size   = geometry.bytes_per_sector;
    config.context     = devid;

    result = lfs_format(&lfs, &config);
    return lfs_result_to_dfs(result);
}

int dfs_lfs_mount(struct dfs_filesystem *fs, unsigned long rwflag, const void *data)
{
    int result;
    struct rt_device_blk_geometry geometry;

    /* check sector size */
    if (rt_device_control(fs->dev_id, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry) != RT_EOK)
    {
        rt_kprintf("get sector size fail of lfs.\n");
        return -EINVAL;
    }

    config.block_count = geometry.sector_count;
    config.block_size  = geometry.block_size;
    config.read_size   = geometry.bytes_per_sector;
    config.prog_size   = geometry.bytes_per_sector;
    config.context     = fs->dev_id;

    result = lfs_mount(&lfs, &config);
    if(result<0)
    {    
        return lfs_result_to_dfs(result);
    }
    
    fs->data = &lfs;

    return lfs_result_to_dfs(result);
}


int dfs_lfs_unmount(struct dfs_filesystem *fs) 
{
    int err = lfs_unmount(&lfs);
    return lfs_result_to_dfs(err);
}

static int dfs_lfs_statfs_count(void *p, lfs_block_t b) {
    *(lfs_size_t *)p += 1;
    return 0;
}

int dfs_lfs_statfs(struct dfs_filesystem *fs, struct statfs *buf) 
{
    memset(buf, 0, sizeof(struct statfs));

    lfs_size_t in_use = 0;
    int err = lfs_traverse(&lfs, dfs_lfs_statfs_count, &in_use);
    if (err) {
        return lfs_result_to_dfs(err);
    }

    buf->f_bsize  = config.block_size;
    buf->f_blocks = config.block_count;
    buf->f_bfree  = config.block_count - in_use;
    return lfs_result_to_dfs(err);
}

static void dfs_lfs_tostat(struct stat *s, struct lfs_info *info) {
    memset(s, 0, sizeof(struct stat));

    s->st_size = info->size;
    s->st_mode = S_IRWXU | S_IRWXG | S_IRWXO;

    switch (info->type) {
        case LFS_TYPE_DIR: s->st_mode |= S_IFDIR; break;
        case LFS_TYPE_REG: s->st_mode |= S_IFREG; break;
    }
}


int dfs_lfs_stat(struct dfs_filesystem *fs, const char *path, struct stat *st)
{
    struct lfs_info info;
    int err = lfs_stat((lfs_t*)fs->data, path, &info);
    if (err) {
        return lfs_result_to_dfs(err);
    }

    dfs_lfs_tostat(st, &info);
    return lfs_result_to_dfs(err);
}


int dfs_lfs_rename(struct dfs_filesystem *fs, const char *oldpath, const char *newpath)
{
    int err = lfs_rename((lfs_t*)fs->data, oldpath, newpath);
    return lfs_result_to_dfs(err);
}

int dfs_lfs_unlink(struct dfs_filesystem *fs, const char *path) 
{
    int err = lfs_remove((lfs_t*)fs->data, path);
    return lfs_result_to_dfs(err);
}


int dfs_lfs_open(struct dfs_fd *file)
{
    lfs_file_t *fd;
    int mode;
    int result;

    if (file->flags & O_DIRECTORY)
    {
        lfs_dir_t *dir;

        if (file->flags & O_CREAT)
        {
            result = lfs_mkdir(&lfs, file->path);
            if (result != LFS_ERR_OK)
            {
                return lfs_result_to_dfs(result);
            }
        }

        /* open directory */
        dir = (lfs_dir_t *)rt_malloc(sizeof(lfs_dir_t));
        if (dir == RT_NULL)
        {
            return -ENOMEM;
        }

        result = lfs_dir_open(&lfs, dir, file->path);
        if (result != LFS_ERR_OK)
        {
            rt_free(dir);
            return lfs_result_to_dfs(result);
        }

        file->data = dir;
        return RT_EOK;
    }
    else
    {
        mode = 0;

        if (file->flags & O_RDONLY)             mode |= LFS_O_RDONLY;
        if (file->flags & O_WRONLY)             mode |= LFS_O_WRONLY;
        if (file->flags & O_RDWR)               mode |= LFS_O_RDWR;
        if ((file->flags & O_ACCMODE) & O_RDWR) mode |= LFS_O_RDWR;
        /* Opens the file, if it is existing. If not, a new file is created. */
        if (file->flags & O_CREAT)              mode |= LFS_O_CREAT;
        /* Creates a new file. If the file is existing, it is truncated and overwritten. */
        if (file->flags & O_TRUNC)              mode |= LFS_O_TRUNC;
        /* Creates a new file. The function fails if the file is already existing. */
        if (file->flags & O_EXCL)               mode |= LFS_O_EXCL;
        if (file->flags & O_APPEND)             mode |= LFS_O_APPEND;

        /* allocate a fd */
        fd = (lfs_file_t *)rt_malloc(sizeof(lfs_file_t));
        if (fd == RT_NULL)
        {
            return -ENOMEM;
        }

        result = lfs_file_open(&lfs, fd, file->path, mode);
        if (result == LFS_ERR_OK)
        {
            file->pos  = fd->pos;
            file->size = fd->size;
            file->data = fd;
        }
        else
        {
            /* open failed, return */
            rt_free(fd);
            return lfs_result_to_dfs(result);
        }
    }

    return RT_EOK;
}

int dfs_lfs_close(struct dfs_fd *file)
{
    int result;

    result = LFS_ERR_OK; 
    if (file->type == FT_DIRECTORY)
    {
        lfs_dir_t *dir; 

        dir = (lfs_dir_t *)(file->data);
        RT_ASSERT(dir != RT_NULL);

        lfs_dir_close(&lfs, dir);
        /* release memory */
        rt_free(dir);
    }
    else if (file->type == FT_REGULAR)
    {
        lfs_file_t *fd; 
        fd = (lfs_file_t *)(file->data);
        RT_ASSERT(fd != RT_NULL);

        result = lfs_file_close(&lfs, fd);
        if (result == LFS_ERR_OK)
        {
            /* release memory */
            rt_free(fd);
        }
    }

    return lfs_result_to_dfs(result);
}


int dfs_lfs_ioctl(struct dfs_fd *file, int cmd, void *args)
{
    return -ENOSYS;
}

int dfs_lfs_read(struct dfs_fd *file, void *buf, size_t len)
{
    lfs_file_t *fd;
    int byte_read;

    if (file->type == FT_DIRECTORY)
    {
        return -EISDIR;
    }

    fd = (lfs_file_t *)(file->data);
    RT_ASSERT(fd != RT_NULL);

    byte_read = lfs_file_read(&lfs, fd, buf, len);

    /* update position */
    file->pos  = fd->pos;
    if (byte_read >= 0)
        return byte_read;

    return lfs_result_to_dfs(byte_read);
}

int dfs_lfs_write(struct dfs_fd *file, const void *buf, size_t len)
{
    lfs_file_t *fd;
    int byte_write;

    if (file->type == FT_DIRECTORY)
    {
        return -EISDIR;
    }

    fd = (lfs_file_t *)(file->data);
    RT_ASSERT(fd != RT_NULL);

    byte_write = lfs_file_write(&lfs, fd, buf, len);

    /* update position and file size */
    file->pos  = fd->pos;
    file->size = fd->size;
    if (byte_write >= 0)
        return byte_write;

    return lfs_result_to_dfs(byte_write);
}

int dfs_lfs_flush(struct dfs_fd *file)
{
    lfs_file_t *fd;
    int result;

    fd = (lfs_file_t *)(file->data);
    RT_ASSERT(fd != RT_NULL);

    result = lfs_file_sync(&lfs, fd);
    return lfs_result_to_dfs(result);
}


int dfs_lfs_lseek(struct dfs_fd *file, rt_off_t offset)
{
    int result = LFS_ERR_OK;
    if (file->type == FT_REGULAR)
    {
        lfs_file_t *fd;

        /* regular file type */
        fd = (lfs_file_t *)(file->data);
        RT_ASSERT(fd != RT_NULL);

        result = lfs_file_seek(&lfs, fd, offset, LFS_SEEK_SET);
        if (result == LFS_ERR_OK)
        {
            /* return current position */
            file->pos = fd->pos;
            return fd->pos;
        }
    }
    else if (file->type == FT_DIRECTORY)
    {
        /* which is a directory */
        lfs_dir_t *dir;

        dir = (lfs_dir_t *)(file->data);
        RT_ASSERT(dir != RT_NULL);

        result = lfs_dir_seek(&lfs, dir, offset / sizeof(struct dirent));
        if (result == LFS_ERR_OK)
        {
            /* update file position */
            file->pos = offset;
            return file->pos;
        }
    }

    return lfs_result_to_dfs(result);
}



int dfs_lfs_getdents(struct dfs_fd *file, struct dirent *dirp, uint32_t count)
{
    lfs_dir_t *dir;
    struct lfs_info fno;
    int result;
    rt_uint32_t index;
    struct dirent *d;

    dir = (lfs_dir_t *)(file->data);
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

        result = lfs_dir_read(&lfs, dir, &fno);
        if (result < 0 || fno.name[0] == 0)
            break;

        fn = fno.name;
        d->d_type = DT_UNKNOWN;
        if (fno.type& LFS_TYPE_DIR)
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
        return lfs_result_to_dfs(result);

    file->pos += index * sizeof(struct dirent);

    return index * sizeof(struct dirent);
}


static int lfs_port_bd_read(const struct lfs_config *cfg, lfs_block_t block,
        lfs_off_t off, void *buffer, lfs_size_t size) 
{
    int rdlen;
    rt_off_t pos, len;

    pos = (rt_off_t)block;
    len = size/cfg->block_size;
    if(len==0) len = 1;
    
    rdlen = rt_device_read((rt_device_t)cfg->context, pos, buffer, len);
    if(rdlen < 0)
    {
        return -EIO;
    }
    return 0;
}

static int lfs_port_bd_prog(const struct lfs_config *cfg, lfs_block_t block,
        lfs_off_t off, const void *buffer, lfs_size_t size) 
{
    int wrlen;
    rt_off_t pos, len;

    len = size/cfg->block_size;
    if(len==0) len = 1;
    
    pos = (rt_off_t)block;
    wrlen = rt_device_write((rt_device_t)cfg->context, pos, buffer, len);
    if(wrlen < 0)
    {
        return -EIO;
    }

    return 0;
}

static int lfs_port_bd_erase(const struct lfs_config *cfg, lfs_block_t block) 
{
    int ret;
    rt_uint32_t addr[3];

    addr[0] = block;   
    addr[1] = block;   
    if (rt_device_control((rt_device_t)cfg->context, RT_DEVICE_CTRL_BLK_ERASE, addr) != RT_EOK)
    {
        rt_kprintf("get sector size fail of lfs.\n");
        return -EINVAL;
    }    
    return 0;
}

static int lfs_port_bd_sync(const struct lfs_config *cfg) {
    const struct fal_partition* part = (const struct fal_partition *)cfg->context;

    return 0;
}


static const struct dfs_file_ops dfs_lfs_fops = 
{
    dfs_lfs_open,
    dfs_lfs_close,
    dfs_lfs_ioctl,
    dfs_lfs_read,
    dfs_lfs_write,
    dfs_lfs_flush,
    dfs_lfs_lseek,
    dfs_lfs_getdents,
    RT_NULL, /* poll interface */
};

static const struct dfs_filesystem_ops dfs_lfs =
{
    "lfs",
    DFS_FS_FLAG_DEFAULT,
    &dfs_lfs_fops,

    dfs_lfs_mount,
    dfs_lfs_unmount,
    dfs_lfs_mkfs,
    dfs_lfs_statfs,

    dfs_lfs_unlink,
    dfs_lfs_stat,
    dfs_lfs_rename,
};

int dfs_lfs_init(void)
{
    memset(&config, 0, sizeof(struct lfs_config));
    config.read = lfs_port_bd_read;
    config.prog = lfs_port_bd_prog;
    config.erase= lfs_port_bd_erase;
    config.sync = lfs_port_bd_sync;
    config.lookahead = 512;

    /* register lfs file system */
    dfs_register(&dfs_lfs);

    return 0;
}
INIT_COMPONENT_EXPORT(dfs_lfs_init);

