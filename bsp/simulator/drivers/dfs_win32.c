/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-27     prife        the first version
 * 2013-03-03     aozima       add dfs_win32_stat st_mtime support.
 * 2017-10-20     urey         support rt-thread 3.0
 */
#include <rtthread.h>

#include <dfs_fs.h>
#include <dfs_file.h>
#include <rtdevice.h>

#include <io.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <WinError.h>
#include <windows.h>

/*
 * RT-Thread DFS Interface for win-directory as an disk device
 */
#define FILE_PATH_MAX           256  /* the longest file path */

#define WIN32_DIRDISK_ROOT  "./disk"

typedef struct {
    HANDLE handle;
    char *start;
    char *end;
    char *curr;
    struct _finddata_t finddata;
} WINDIR;

/* There are so many error codes in windows, you'd better google for details.
 * google  "System Error Codes (Windows)"
 * http://msdn.microsoft.com/ZH-CN/library/windows/desktop/ms681381(v=vs.85).aspx
 */

struct _errcode_map
{
    rt_uint16_t dfserr;
    rt_uint16_t win32err;
};

static const struct _errcode_map errcode_table[] =
{
    {ENOENT, ERROR_FILE_NOT_FOUND },
    {ENOENT, ERROR_PATH_NOT_FOUND },
    {EEXIST, ERROR_FILE_EXISTS },
    {EEXIST, ERROR_ALREADY_EXISTS },
    {ENOTEMPTY, ERROR_DIR_NOT_EMPTY },
    {EBUSY, ERROR_PATH_BUSY },
    {EINVAL, ERROR_ACCESS_DENIED },

#if 0 /* TODO: MORE NEED BE ADDED */
    {DFS_STATUS_EISDIR, ERROR_FILE_EXISTS },
    {DFS_STATUS_ENOTDIR, ERROR_FILE_EXISTS },
    {DFS_STATUS_EBADF, ERROR_FILE_EXISTS },
    {DFS_STATUS_EBUSY, ERROR_FILE_EXISTS },
    {DFS_STATUS_ENOMEM, ERROR_FILE_EXISTS },
    {DFS_STATUS_ENOSPC, ERROR_FILE_EXISTS },
#endif
};
static int win32_result_to_dfs(DWORD res)
{
    int i;
    int err = 0;
    for (i = 0; i < sizeof(errcode_table) / sizeof(struct _errcode_map); i++)
    {
        if (errcode_table[i].win32err == (res & 0xFFFF))
        {
            err = -errcode_table[i].dfserr;
            return err;
        }
    }

    /* unknown error */
    rt_kprintf("dfs win32 error not supported yet: %d\n", res);
    return -1;
}

static int dfs_win32_mount(
    struct dfs_filesystem *fs,
    unsigned long rwflag,
    const void *data)
{
    return 0;
}

static int dfs_win32_unmount(struct dfs_filesystem *fs)
{
    return 0;
}

static int dfs_win32_mkfs(rt_device_t devid)
{
    return -ENOSYS;
}

static int dfs_win32_statfs(struct dfs_filesystem *fs,
                            struct statfs *buf)
{
    return -ENOSYS;
}

static char *winpath_dirdup(char *des, const char *src)
{
    char *path;
    int i = 0;

    path = rt_malloc(FILE_PATH_MAX);
    if (path == RT_NULL)
        return RT_NULL;

    strcpy(path, des);
    strcat(path, src);

    while (1)
    {
        if (path[i] == 0)
            break;

        if (path[i] == '/')
            path[i] = '\\';

        i++;
    }

    return path;
}

/* This function can convert the path in rt-thread/dfs to the path in windows */
char * dfs_win32_dirdup(char * path)
{
    char * file_path;
    file_path = winpath_dirdup(WIN32_DIRDISK_ROOT, path);
    return file_path;
}

static int dfs_win32_open(struct dfs_file *file)
{
    int fd;
    uint32_t oflag, mode;
    char *file_path;
    int res;

    oflag = file->flags;
    if (oflag & O_DIRECTORY)   /* operations about dir */
    {
        WINDIR *wdirp;
        HANDLE handle;
        int len;

        file_path = winpath_dirdup(WIN32_DIRDISK_ROOT, file->vnode->path);

        if (oflag & O_CREAT)   /* create a dir*/
        {
            res = CreateDirectory(file_path, NULL);
            if (res == 0)
            {
                rt_free(file_path);
                return win32_result_to_dfs(GetLastError());
            }
        }

        len = strlen(file_path);
        if (file_path[len - 1] != '\\')
        {
            file_path[len] = '\\';
            file_path[len + 1] = 0;
        }

        strcat(file_path, "*.*");
        /* _findfirst will get '.' */
        /* save this pointer,will used by  dfs_win32_getdents*/
        wdirp = rt_malloc(sizeof(WINDIR));
        RT_ASSERT(wdirp != NULL);
        if ((handle = _findfirst(file_path, &wdirp->finddata)) == -1)
        {
            rt_free(wdirp);
            rt_free(file_path);
            goto __err;
        }
        len = strlen(wdirp->finddata.name) + 1;
        wdirp->handle = handle;
        //wdirp->nfiles = 1;
        wdirp->start = (char *)malloc(len); //not rt_malloc!
        wdirp->end = wdirp->curr = wdirp->start;
        wdirp->end += len;
        rt_strncpy(wdirp->curr, wdirp->finddata.name, len);

        file->vnode->data = (void *)wdirp;
        rt_free(file_path);
        return 0;
    }
    /* regular file operations */
    mode = O_BINARY;
    if (oflag & O_RDONLY) mode |= O_RDONLY;
    if (oflag & O_WRONLY) mode |= O_WRONLY;
    if (oflag & O_RDWR)   mode |= O_RDWR;
    /* Opens the file, if it is existing. If not, a new file is created. */
    if (oflag & O_CREAT) mode |= O_CREAT;
    /* Creates a new file. If the file is existing, it is truncated and overwritten. */
    if (oflag & O_TRUNC) mode |= O_TRUNC;
    /* Creates a new file. The function fails if the file is already existing. */
    if (oflag & O_EXCL) mode |= O_EXCL;

    file_path = winpath_dirdup(WIN32_DIRDISK_ROOT, file->vnode->path);
    fd = _open(file_path, mode, 0x0100 | 0x0080); /* _S_IREAD | _S_IWRITE */
    rt_free(file_path);

    if (fd < 0)
        goto __err;

    /* save this pointer, it will be used when calling read(), write(),
     * flush(), seek(), and will be free when calling close()*/
    file->data = (void *)fd;
    file->pos  = 0;
    file->vnode->size = _lseek(fd, 0, SEEK_END);

    if (oflag & O_APPEND)
    {
        file->pos = file->vnode->size;
    }
    else
        _lseek(fd, 0, SEEK_SET);

    return 0;

__err:
    res = GetLastError();
    return win32_result_to_dfs(res);
}

static int dfs_win32_close(struct dfs_file *file)
{
    if (file->flags & O_DIRECTORY)
    {
        WINDIR *wdirp = (WINDIR*)(file->vnode->data);
        RT_ASSERT(wdirp != RT_NULL);
        if (_findclose((intptr_t)wdirp->handle) == 0) {
            free(wdirp->start); /* NOTE: here we don't use rt_free! */
            rt_free(wdirp);
            return 0;
        }
    }
    else /* regular file operations */
    {
        if (_close((int)(file->data)) == 0)
            return 0;
    }

    return win32_result_to_dfs(GetLastError());
}

static int dfs_win32_ioctl(struct dfs_file *file, int cmd, void *args)
{
    return -ENOSYS;
}

static int dfs_win32_read(struct dfs_file *file, void *buf, size_t len)
{
    int fd;
    int char_read;

    fd = (int)(file->data);
    char_read = _read(fd, buf, len);
    if (char_read < 0)
        return win32_result_to_dfs(GetLastError());

    /* update position */
    file->pos = _lseek(fd, 0, SEEK_CUR);
    return char_read;
}

static int dfs_win32_write(struct dfs_file *file, const void *buf, size_t len)
{
    int fd;
    int char_write;

    fd = (int)(file->data);

    char_write = _write(fd, buf, len);
    if (char_write < 0)
        return win32_result_to_dfs(GetLastError());

    /* update position */
    file->pos = _lseek(fd, 0, SEEK_CUR);
    return char_write;
}

static int dfs_win32_flush(struct dfs_file *file)
{
    return 0;
}

static int dfs_win32_seek(struct dfs_file *file,
                          rt_off_t offset)
{
    int result;

    /* set offset as current offset */
    if (file->vnode->type == FT_DIRECTORY)
    {
        WINDIR* wdirp = (WINDIR*)(file->vnode->data);
        RT_ASSERT(wdirp != RT_NULL);
        wdirp->curr = wdirp->start + offset;
        return offset;
    }
    else //file->type == FT_REGULAR)
    {
        result = _lseek((int)(file->data), offset, SEEK_SET);
        if (result >= 0)
            return offset;
        else
            return win32_result_to_dfs(GetLastError());
    }
}

/* return the size of struct dirent*/
static int dfs_win32_getdents(struct dfs_file *file, struct dirent *dirp, rt_uint32_t count)
{
    WINDIR *wdirp;
    struct dirent *d = dirp;
    int result;

    /* make integer count */
    if (count / sizeof(struct dirent) != 1)
        return -EINVAL;

    wdirp = (WINDIR*)(file->vnode->data);
    RT_ASSERT(wdirp != RT_NULL);
    if (wdirp->curr == NULL) //no more entries in this directory
        return 0;

    /* get the current entry */
    if (wdirp->finddata.attrib & _A_SUBDIR)
        d->d_type = DT_DIR;
    else
        d->d_type = DT_REG;
    d->d_namlen = (rt_uint8_t)strlen(wdirp->curr);
    strncpy(d->d_name, wdirp->curr, DIRENT_NAME_MAX);
    d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
    wdirp->curr += (strlen(wdirp->curr) + 1);
    file->pos = wdirp->curr - wdirp->start + sizeof(struct dirent);//NOTE!

    /* now set up for the next call to readdir */
    if (wdirp->curr >= wdirp->end)
    {
        if (_findnext(wdirp->handle, &wdirp->finddata) == 0)
        {
            char* old_start = wdirp->start;
            long name_len = strlen(wdirp->finddata.name) + 1;
            wdirp->start = realloc(wdirp->start, wdirp->end - wdirp->start + name_len);
            wdirp->curr = wdirp->start + (wdirp->curr - old_start);
            wdirp->end = wdirp->curr + name_len;
            rt_strcpy(wdirp->curr, wdirp->finddata.name);
        }
        else
        {
            if ((result = GetLastError()) == ERROR_NO_MORE_FILES)
                wdirp->curr = NULL;
            else
                return win32_result_to_dfs(result);
        }
    }

    return sizeof(struct dirent);
}

static int dfs_win32_unlink(struct dfs_filesystem *fs, const char *path)
{
    int result;
    char *fp;
    fp = winpath_dirdup(WIN32_DIRDISK_ROOT, path);
    if (fp == RT_NULL)
    {
        rt_kprintf("out of memory.\n");
        return -ENOMEM;
    }

    result = GetFileAttributes(fp);
    if (result == INVALID_FILE_ATTRIBUTES)
        goto __err;

    if (result & FILE_ATTRIBUTE_DIRECTORY)//winnt.h
    {
        if (RemoveDirectory(fp) == RT_FALSE)
            goto __err;
    }
    else //(result & FILE_ATTRIBUTE_NORMAL)
    {
        if (_unlink(fp) < 0)
            goto __err;
    }

    rt_free(fp);
    return 0;
__err:
    rt_free(fp);
    return win32_result_to_dfs(GetLastError());
}

static int dfs_win32_rename(
    struct dfs_filesystem *fs,
    const char *oldpath,
    const char *newpath)
{
    int result;
    char *op, *np;
    op = winpath_dirdup(WIN32_DIRDISK_ROOT, oldpath);
    np = winpath_dirdup(WIN32_DIRDISK_ROOT, newpath);
    if (op == RT_NULL || np == RT_NULL)
    {
        rt_kprintf("out of memory.\n");
        return -ENOMEM;
    }

    /* If the function fails, the return value is zero. */
    result = MoveFile(op, np);

    rt_free(op);
    rt_free(np);

    if (result == 0)
        return win32_result_to_dfs(GetLastError());

    return 0;
}

static int dfs_win32_stat(struct dfs_filesystem *fs, const char *path, struct stat *st)
{
    WIN32_FIND_DATA fileInfo;
    HANDLE hFind;
    char *fp;
    fp = winpath_dirdup(WIN32_DIRDISK_ROOT, path);
    if (fp == RT_NULL)
    {
        rt_kprintf("out of memory.\n");
        return -ENOMEM;
    }

    hFind = FindFirstFile(fp, &fileInfo);
    rt_free(fp);

    if (hFind == INVALID_HANDLE_VALUE)
        goto __err;

    st->st_mode = S_IFREG | S_IRUSR | S_IRGRP | S_IROTH |
                  S_IWUSR | S_IWGRP | S_IWOTH;

    /* convert file info to dfs stat structure */
    if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        st->st_mode &= ~S_IFREG;
        st->st_mode |= S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;
    }

    st->st_dev  = 0;
    st->st_size = fileInfo.nFileSizeLow;

    /* get st_mtime. */
    {
        LARGE_INTEGER time_tmp;
        time_tmp.LowPart = fileInfo.ftLastWriteTime.dwLowDateTime;
        time_tmp.HighPart = fileInfo.ftLastWriteTime.dwHighDateTime;

        /* removes the diff between 1970 and 1601. */
        time_tmp.QuadPart -= 11644473600000 * 10000;
        /* converts back from 100-nanoseconds to seconds. */
        time_tmp.QuadPart /= 10UL * 1000 * 1000;

        st->st_mtime = time_tmp.QuadPart;
    }

    FindClose(hFind);

    return 0;

__err:
    return win32_result_to_dfs(GetLastError());
}

static const struct dfs_file_ops dfs_win32_file_ops =
{
    dfs_win32_open,
    dfs_win32_close,
    dfs_win32_ioctl,
    dfs_win32_read,
    dfs_win32_write,
    dfs_win32_flush,
    dfs_win32_seek,
    dfs_win32_getdents,
};

static const struct dfs_filesystem_ops dfs_win32_ops =
{
    "wdir", /* file system type: dir */
    DFS_FS_FLAG_DEFAULT,
    &dfs_win32_file_ops,
    dfs_win32_mount,
    dfs_win32_unmount,
    dfs_win32_mkfs,
    dfs_win32_statfs,
    dfs_win32_unlink,
    dfs_win32_stat,
    dfs_win32_rename,
};

int dfs_win32_init(void)
{
    /* register uffs file system */
    dfs_register(&dfs_win32_ops);

    return 0;
}

static rt_err_t nop_init(rt_device_t dev)
{
    return RT_EOK;
}

static rt_err_t nop_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t nop_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_ssize_t nop_read(rt_device_t dev,
                          rt_off_t    pos,
                          void       *buffer,
                          rt_size_t   size)
{
    return size;
}

static rt_ssize_t nop_write(rt_device_t dev,
                           rt_off_t    pos,
                           const void *buffer,
                           rt_size_t   size)
{
    return size;
}

static rt_err_t nop_control(rt_device_t dev, int cmd, void *args)
{
    return RT_EOK;
}

static struct rt_device win_sharedir_dev;
rt_err_t rt_win_sharedir_init(const char *name)
{
    rt_device_t dev;

    dev = &win_sharedir_dev;
    RT_ASSERT(dev != RT_NULL);

    /* set device class and generic device interface */
    dev->type        = RT_Device_Class_Block;
    dev->init        = nop_init;
    dev->open        = nop_open;
    dev->read        = nop_read;
    dev->write       = nop_write;
    dev->close       = nop_close;
    dev->control     = nop_control;

    dev->rx_indicate = RT_NULL;
    dev->tx_complete = RT_NULL;

    /* register to RT-Thread device system */
    return rt_device_register(dev, name, RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
}
