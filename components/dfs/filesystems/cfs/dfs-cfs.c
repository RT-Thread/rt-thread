/*********************************************************************************************************
**
**                                苏州诺金智通信息科技有限公司
**
**                               Copyright All Rights Reserved
**
**--------------文件信息--------------------------------------------------------------------------------
**
** 文 件 名: dfs-cfs.c
**
** 创 建 人: Urey(风飘柳絮)
**
** 创建日期: 2015年11月11日
**
** 描    述: TODO
*********************************************************************************************************/


/*********************************************************************************************************
**   头文件
*********************************************************************************************************/
#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>

#include "cfs.h"
#include "cfs-coffee.h"
#include "cfs-coffee_arch.h"


int dfs_cfs_mount    (struct dfs_filesystem *fs, unsigned long rwflag, const void *data)
{
    int result;

    result = xmem_init(fs->dev_id);
    if(result != RT_EOK)
        return -DFS_STATUS_ENOSYS;

    return DFS_STATUS_OK;
}

int dfs_cfs_unmount(struct dfs_filesystem *fs)
{
//    fs->data = RT_NULL;

    return DFS_STATUS_OK;
}



/* make a file system */
int dfs_cfs_mkfs(rt_device_t devid)
{
    cfs_coffee_format();

    return DFS_STATUS_OK;
}

int dfs_cfs_open(struct dfs_fd *file)
{
    CFS_FILE    *cfsFile;
    int flags;

    if(file->flags & DFS_O_DIRECTORY)
    {
        static struct cfs_dir dir;
        /* 打开根目录 */
        if(cfs_opendir(&dir, file->path) != 0)
            return  -DFS_STATUS_ENOSYS;

        file->data = &dir;
        return DFS_STATUS_OK;
    }
    else
    {
        if (file->flags == DFS_O_WRONLY)
            flags = CFS_WRITE;
        else if (file->flags == DFS_O_RDONLY)
            flags = CFS_READ;
        else
            flags = (CFS_WRITE | CFS_READ);

        if (file->flags & DFS_O_APPEND)
            flags |= CFS_APPEND;

        cfsFile = (CFS_FILE *) rt_malloc(sizeof(CFS_FILE));
        if (cfsFile == RT_NULL)
            return -DFS_STATUS_ENOMEM;

        cfsFile->fd = cfs_open(file->path, flags);
        if (cfsFile->fd >= 0)
        {
            cfsFile->desc = cfs_getdesc(cfsFile->fd);

            file->pos = cfsFile->desc->offset;
            file->size = cfsFile->desc->file->end;
            file->data = cfsFile;

            return DFS_STATUS_OK;
        }
    }

    return -DFS_STATUS_EIO;
}

int dfs_cfs_close(struct dfs_fd *file)
{
    if (file->type == FT_DIRECTORY)
    {
        struct cfs_dir *dir;

        dir = (struct cfs_dir *)file->data;
        RT_ASSERT(dir != RT_NULL);

        cfs_closedir(dir);
    }
    else
    {
        CFS_FILE *cfsFile = (CFS_FILE *) file->data;

        cfs_close(cfsFile->fd);
        if(cfsFile != RT_NULL)
            rt_free(cfsFile);

        file->data = RT_NULL;
    }
    return DFS_STATUS_OK;
}
int dfs_cfs_ioctl(struct dfs_fd *file, int cmd, void *args)
{
    return -DFS_STATUS_ENOSYS;
}
int dfs_cfs_read(struct dfs_fd *file, void *buf, rt_size_t count)
{
    CFS_FILE *cfsFile = (CFS_FILE *) file->data;
    int bytes;

    if (file->type == FT_DIRECTORY)
    {
        return -DFS_STATUS_EISDIR;
    }

    RT_ASSERT(cfsFile != RT_NULL);

    bytes = cfs_read(cfsFile->fd, buf, count);
    if (bytes > 0)
    {
        /* update position */
        file->pos = cfsFile->desc->offset;

        return bytes;
    }

    return -DFS_STATUS_EIO;
}
int dfs_cfs_write(struct dfs_fd *file, const void *buf, rt_size_t count)
{
    int bytes;
    CFS_FILE *cfsFile = (CFS_FILE *) file->data;

    if (file->type == FT_DIRECTORY)
    {
        return -DFS_STATUS_EISDIR;
    }

    RT_ASSERT(cfsFile != RT_NULL);

    bytes = cfs_write(cfsFile->fd, buf, count);
    if (bytes > 0)
    {
        /* update position */
        file->pos = cfsFile->desc->offset;

        return bytes;
    }

    return -DFS_STATUS_EIO;

}

int dfs_cfs_lseek(struct dfs_fd *file, rt_off_t offset)
{
    CFS_FILE *cfsFile = (CFS_FILE *) file->data;

    if (file->type == FT_DIRECTORY)
    {
        return -DFS_STATUS_EISDIR;
    }

    RT_ASSERT(cfsFile != RT_NULL);

    if (cfs_seek(cfsFile->fd, offset, CFS_SEEK_SET) > 0)
    {
        file->pos = cfsFile->desc->offset;
        return file->pos;
    }

    return -DFS_STATUS_EIO;
}

int dfs_cfs_getdents (struct dfs_fd *file, struct dirent *dirp, rt_uint32_t count)
{
    rt_size_t index;

    struct cfs_dir *cfs_dir = (struct cfs_dir *)file->data;
    //static cfs_offset_t totsize;
    struct cfs_dirent   cfs_dirent;

    struct dirent *d;

    if(cfs_dir == RT_NULL)
       return  -DFS_STATUS_EINVAL;

    /* make integer count */
    count = (count / sizeof(struct dirent));
    if (count == 0)
        return -DFS_STATUS_EINVAL;


    index = 0;
    for (index = 0; index < count; index++)
    {
        d = dirp + index;

        if(cfs_readdir(cfs_dir, &cfs_dirent) == 0)
        {
            /* coffee 根目录下只有文件 */
            d->d_type = DFS_DT_REG;
            d->d_namlen = rt_strlen(cfs_dirent.name);;
            d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
            rt_strncpy(d->d_name, cfs_dirent.name, rt_strlen(cfs_dirent.name) + 1);

            continue;
        }

        break;
    }

    return index * sizeof(struct dirent);
}

int dfs_cfs_stat(struct dfs_filesystem *fs, const char *path, struct stat *st)
{
    int fd;
    struct file_desc *desc;

    fd = cfs_open(path,CFS_READ);
    if(fd >= 0)
    {
        desc = cfs_getdesc(fd);

        st->st_dev = 0;
        st->st_mode = DFS_S_IFREG | DFS_S_IRUSR | DFS_S_IRGRP | DFS_S_IROTH | DFS_S_IWUSR | DFS_S_IWGRP | DFS_S_IWOTH;


        st->st_size = desc->file->end;
        st->st_mtime = 0;
        //st->st_blksize = 256;

        cfs_close(fd);
    }
    return 0;
}

static const struct dfs_filesystem_operation _cfs =
{
                "cfs",
                DFS_FS_FLAG_FULLPATH,
                /* mount and unmount file system */
                dfs_cfs_mount,
                RT_NULL,

                /* make a file system */
                dfs_cfs_mkfs,
                RT_NULL,

                dfs_cfs_open,
                dfs_cfs_close,
                dfs_cfs_ioctl,
                dfs_cfs_read,
                dfs_cfs_write,
                RT_NULL,
                dfs_cfs_lseek,
                dfs_cfs_getdents,

                RT_NULL,
                dfs_cfs_stat,
                RT_NULL,
};


int cfs_init(void)
{
    /* register rom file system */
    dfs_register(&_cfs);

    return 0;
}
INIT_FS_EXPORT(cfs_init);
