/*
 * File      : dfs_nfs.c
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
 
#include <stdio.h>
#include <rtthread.h>
#include <dfs_fs.h>
#include <dfs_def.h>

#include <rpc/rpc.h>

#include "mount.h"
#include "nfs.h"

#define NAME_MAX    64
#define DFS_NFS_MAX_MTU  1024

#ifdef _WIN32
#define strtok_r strtok_s
#endif

struct nfs_file
{
    nfs_fh3 handle;     /* handle */
    size_t offset;      /* current offset */

    size_t size;        /* total size */
    bool_t eof;         /* end of file */
};

struct nfs_dir
{
    nfs_fh3 handle;
    cookie3 cookie;
    cookieverf3 cookieverf;
    entry3 *entry;
    bool_t eof;
    READDIR3res res;
};

#define HOST_LENGTH         32
#define EXPORT_PATH_LENGTH  32
struct nfs_filesystem
{
    nfs_fh3 root_handle;
    nfs_fh3 current_handle;
    CLIENT *nfs_client;
    CLIENT *mount_client;

    char host[HOST_LENGTH];
    char export[EXPORT_PATH_LENGTH];
};
typedef struct nfs_file nfs_file;
typedef struct nfs_dir nfs_dir;
nfs_dir *nfs_opendir(struct nfs_filesystem *nfs, const char *path);

static int nfs_parse_host_export(const char *host_export, 
                                 char       *host,
                                 size_t      host_len, 
                                 char       *export,
                                 size_t      export_len)
{
    int index;

    for (index = 0; index < host_len; index ++)
    {
        /* it's end of string, failed */
        if (host_export[index] == 0)
            return -1;

        /* copy to host buffer */
        if (host_export[index] != ':')
            host[index] = host_export[index];
        else
            break;
    }

    /* host buffer is not enough, failed */
    if (index == host_len)
        return -1;

    /* make RT_NULL */
    host_len = index;
    host[host_len] = '\0';

    host_len ++;

    /* copy export path */
    for (index = host_len; index < host_len + export_len; index ++)
    {
        if (host_export[index] == 0) 
        {
            export[index - host_len] = '\0';

            return 0;
        }

        export[index - host_len] = host_export[index];
    }

    return -1;
}

static void copy_handle(nfs_fh3 *dest, const nfs_fh3 *source)
{
    dest->data.data_len = source->data.data_len;
    dest->data.data_val = rt_malloc(dest->data.data_len);
    if (dest->data.data_val == RT_NULL)
    {
        dest->data.data_len = 0;

        return;
    }

    memcpy(dest->data.data_val, source->data.data_val, dest->data.data_len);
}

static nfs_fh3 *get_handle(struct nfs_filesystem *nfs, const char *name)
{
    nfs_fh3 *handle = RT_NULL;
    char *file;
    char *path;
    char *init;

    init = path = rt_malloc(strlen(name)+1);
    if (init == RT_NULL)
        return RT_NULL;

    memcpy(init, name, strlen(name)+1);

    handle = rt_malloc(sizeof(nfs_fh3));
    if (handle == RT_NULL)
    {
        rt_free(init);

        return RT_NULL;
    }

    if (path[0] == '/')
    {
        path ++;
        copy_handle(handle, &nfs->root_handle);
    }
    else
    {
        copy_handle(handle, &nfs->current_handle);
    }

    while ((file = strtok_r(RT_NULL, "/", &path)) != RT_NULL)
    {
        LOOKUP3args args;
        LOOKUP3res res;
        memset(&res, 0, sizeof(res));
        copy_handle(&args.what.dir, handle);
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
        args.what.name = file;

        if (nfsproc3_lookup_3(args, &res, nfs->nfs_client) != RPC_SUCCESS)
        {
            rt_kprintf("Lookup failed\n");
            rt_free(init);
            rt_free(handle);
            xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&args.what.dir);

            return RT_NULL;
        }
        else if (res.status != NFS3_OK)
        {
            rt_kprintf("Lookup failed: %d\n", res.status);
            rt_free(init);
            rt_free(handle);
            xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&args.what.dir);
            xdr_free((xdrproc_t)xdr_LOOKUP3res, (char *)&res);

            return RT_NULL;
        }
        copy_handle(handle, &res.LOOKUP3res_u.resok.object);
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&args.what.dir);
        xdr_free((xdrproc_t)xdr_LOOKUP3res, (char *)&res);
    }

    rt_free(init);

    return handle;
}

static nfs_fh3 *get_dir_handle(struct nfs_filesystem *nfs, const char *name)
{
    nfs_fh3 *handle = RT_NULL;
    char *file;
    char *path;
    char *init;

    init = path = rt_malloc(strlen(name)+1);
    if (init == RT_NULL)
        return RT_NULL;
    memcpy(init, name, strlen(name)+1);

    handle = rt_malloc(sizeof(nfs_fh3));
    if (handle == RT_NULL)
    {
        rt_free(init);

        return RT_NULL;
    }

    if (path[0] == '/')
    {
        path ++;
        copy_handle(handle, &nfs->root_handle);
    }
    else
    {
        copy_handle(handle, &nfs->current_handle);
    }

    while ((file = strtok_r(RT_NULL, "/", &path)) != RT_NULL && path[0] != 0)
    {
        LOOKUP3args args;
        LOOKUP3res res;
        memset(&res, 0, sizeof(res));
        copy_handle(&args.what.dir, handle);
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
        args.what.name = file;

        if (nfsproc3_lookup_3(args, &res, nfs->nfs_client) != RPC_SUCCESS)
        {
            rt_kprintf("Lookup failed\n");
            rt_free(init);
            rt_free(handle);
            xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&args.what.dir);

            return RT_NULL;
        }
        else if (res.status != NFS3_OK)
        {
            rt_kprintf("Lookup failed: %d\n", res.status);
            rt_free(init);
            rt_free(handle);
            xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&args.what.dir);
            xdr_free((xdrproc_t)xdr_LOOKUP3res, (char *)&res);

            return RT_NULL;
        }
        copy_handle(handle, &res.LOOKUP3res_u.resok.object);
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&args.what.dir);
        xdr_free((xdrproc_t)xdr_LOOKUP3res, (char *)&res);
    }

    rt_free(init);

    return handle;
}

static size_t nfs_get_filesize(struct nfs_filesystem *nfs, nfs_fh3 *handle)
{
    GETATTR3args args;
    GETATTR3res res;
    fattr3 *info;
    size_t size;

    args.object = *handle;

    memset(&res, '\0', sizeof(res));

    if ((nfsproc3_getattr_3(args, &res, nfs->nfs_client)!=RPC_SUCCESS) ||
        res.status != NFS3_OK)
    {
        rt_kprintf("GetAttr failed: %d\n", res.status);

        return 0;
    }

    info = &res.GETATTR3res_u.resok.obj_attributes;
    size = info->size;
    xdr_free((xdrproc_t)xdr_GETATTR3res, (char *)&res);
    
    return size;
}

rt_bool_t nfs_is_directory(struct nfs_filesystem *nfs, const char *name)
{
    GETATTR3args args;
    GETATTR3res res;
    fattr3 *info;
    nfs_fh3 *handle;
    rt_bool_t result;

    result = RT_FALSE;
    handle = get_handle(nfs, name);
    if (handle == RT_NULL)
        return RT_FALSE;

    args.object = *handle;

    memset(&res, '\0', sizeof(res));

    if (nfsproc3_getattr_3(args, &res, nfs->nfs_client) != RPC_SUCCESS)
    {
        rt_kprintf("GetAttr failed\n");

        return RT_FALSE;
    }
    else if (res.status != NFS3_OK)
    {
        rt_kprintf("Getattr failed: %d\n", res.status);

        return RT_FALSE;
    }

    info=&res.GETATTR3res_u.resok.obj_attributes;

    if (info->type == NFS3DIR)
        result = RT_TRUE;

    xdr_free((xdrproc_t)xdr_GETATTR3res, (char *)&res);
    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
    rt_free(handle);
    
    return result;
}

int nfs_create(struct nfs_filesystem *nfs, const char *name, mode_t mode)
{
    CREATE3args args;
    CREATE3res res;
    int ret = 0;
    nfs_fh3 *handle;

    if (nfs->nfs_client == RT_NULL)
    {
        return -1;
    }

    handle = get_dir_handle(nfs, name);
    if (handle == RT_NULL)
    {
        return -1;
    }
    args.where.dir = *handle;
    args.where.name = strrchr(name, '/') + 1;
    if (args.where.name == RT_NULL)
    {
        args.where.name = (char *)name;
    }
    args.how.mode = GUARDED;

    args.how.createhow3_u.obj_attributes.mode.set_it = TRUE;
    args.how.createhow3_u.obj_attributes.mode.set_mode3_u.mode = mode;
    args.how.createhow3_u.obj_attributes.uid.set_it = FALSE;
    args.how.createhow3_u.obj_attributes.gid.set_it = FALSE;
    args.how.createhow3_u.obj_attributes.size.set_it = FALSE;
    args.how.createhow3_u.obj_attributes.atime.set_it = DONT_CHANGE;
    args.how.createhow3_u.obj_attributes.mtime.set_it = DONT_CHANGE;

    memset(&res, 0, sizeof(res));

    if (nfsproc3_create_3(args, &res, nfs->nfs_client) != RPC_SUCCESS)
    {
        rt_kprintf("Create failed\n");
        ret = -1;
    }
    else if (res.status != NFS3_OK)
    {
        rt_kprintf("Create failed: %d\n", res.status);
        ret = -1;
    }
    xdr_free((xdrproc_t)xdr_CREATE3res, (char *)&res);
    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
    rt_free(handle);

    return ret;
}

int nfs_mkdir(struct nfs_filesystem *nfs, const char *name, mode_t mode)
{
    MKDIR3args args;
    MKDIR3res res;
    int ret = 0;
    nfs_fh3 *handle;

    if (nfs->nfs_client == RT_NULL)
        return -1;

    handle = get_dir_handle(nfs, name);
    if (handle == RT_NULL)
        return -1;

    args.where.dir = *handle;
    args.where.name = strrchr(name, '/') + 1;
    if (args.where.name == RT_NULL)
    {
        args.where.name = (char *)name;
    }

    args.attributes.mode.set_it = TRUE;
    args.attributes.mode.set_mode3_u.mode = mode;
    args.attributes.uid.set_it = FALSE;
    args.attributes.gid.set_it = FALSE;
    args.attributes.size.set_it = FALSE;
    args.attributes.atime.set_it = DONT_CHANGE;
    args.attributes.mtime.set_it = DONT_CHANGE;

    memset(&res, 0, sizeof(res));

    if (nfsproc3_mkdir_3(args, &res, nfs->nfs_client) != RPC_SUCCESS)
    {
        rt_kprintf("Mkdir failed\n");
        ret = -1;
    }
    else if (res.status != NFS3_OK)
    {
        rt_kprintf("Mkdir failed: %d\n", res.status);
        ret = -1;
    }
    xdr_free((xdrproc_t)xdr_MKDIR3res, (char *)&res);
    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
    rt_free(handle);
    
    return ret;
}

/* mount(RT_NULL, "/mnt", "nfs", 0, "192.168.1.1:/export") */
int nfs_mount(struct dfs_filesystem *fs, unsigned long rwflag, const void *data)
{
    mountres3 res;
    struct nfs_filesystem *nfs;

    nfs = (struct nfs_filesystem *)rt_malloc(sizeof(struct nfs_filesystem));
    memset(nfs, 0, sizeof(struct nfs_filesystem));

    if (nfs_parse_host_export((const char *)data, nfs->host, HOST_LENGTH,
        nfs->export, EXPORT_PATH_LENGTH) < 0)
    {
        rt_kprintf("host or export path error\n");
        goto __return;
    }

    nfs->mount_client=clnt_create((char *)nfs->host, MOUNT_PROGRAM, MOUNT_V3, "udp");
    if (nfs->mount_client == RT_NULL)
    {
        rt_kprintf("create mount client failed\n");
        goto __return;
    }

    memset(&res, '\0', sizeof(mountres3));
    if (mountproc3_mnt_3((char *)nfs->export, &res, nfs->mount_client) != RPC_SUCCESS)
    {
        rt_kprintf("nfs mount failed\n");
        goto __return;
    }
    else if (res.fhs_status != MNT3_OK)
    {
        rt_kprintf("nfs mount failed\n");
        goto __return;
    }
    nfs->nfs_client=clnt_create((char *)nfs->host, NFS_PROGRAM, NFS_V3, "udp");
    if (nfs->nfs_client == RT_NULL)
    {
        rt_kprintf("creat nfs client failed\n");
        goto __return;
    }
    copy_handle(&nfs->root_handle, (nfs_fh3 *)&res.mountres3_u.mountinfo.fhandle);
    copy_handle(&nfs->current_handle, &nfs->root_handle);

    nfs->nfs_client->cl_auth = authnone_create();
    fs->data = nfs;

    return 0;

__return:
    if (nfs != RT_NULL)
    {
        if (nfs->mount_client != RT_NULL)
        {
            clnt_destroy(nfs->mount_client);
        }
        if (nfs->nfs_client != RT_NULL)
        {
            if (nfs->nfs_client->cl_auth != RT_NULL)
            {
                auth_destroy(nfs->nfs_client->cl_auth);
            }
            clnt_destroy(nfs->nfs_client);
        }
        rt_free(nfs);
    }

    return -1;
}

int nfs_unmount(struct dfs_filesystem *fs)
{
    struct nfs_filesystem *nfs;

    RT_ASSERT(fs != RT_NULL);
    RT_ASSERT(fs->data != RT_NULL);
    nfs = (struct nfs_filesystem *)fs->data;

    if (nfs->mount_client != RT_NULL && 
        mountproc3_umnt_3((char *)nfs->export, RT_NULL, nfs->mount_client) != RPC_SUCCESS)
    {
        rt_kprintf("umount failed\n");

        return -1;
    }

    /* destroy nfs client */
    if (nfs->nfs_client != RT_NULL)
    {
        if (nfs->nfs_client->cl_auth != RT_NULL)
        {
            auth_destroy(nfs->nfs_client->cl_auth);
            nfs->nfs_client->cl_auth = RT_NULL;
        }
        clnt_destroy(nfs->nfs_client);
        nfs->nfs_client = RT_NULL;
    }

    /* destroy mount client */
    if (nfs->mount_client != RT_NULL)
    {
        if (nfs->mount_client->cl_auth != RT_NULL)
        {
            auth_destroy(nfs->mount_client->cl_auth);
            nfs->mount_client->cl_auth = RT_NULL;
        }
        clnt_destroy(nfs->mount_client);
        nfs->mount_client = RT_NULL;
    }

    rt_free(nfs);
    fs->data = RT_NULL;

    return 0;
}

int nfs_ioctl(struct dfs_fd *file, int cmd, void *args)
{
    return -DFS_STATUS_ENOSYS;
}

int nfs_read(struct dfs_fd *file, void *buf, rt_size_t count)
{
    READ3args args;
    READ3res res;
    ssize_t bytes, total=0;
    nfs_file *fd;
    struct nfs_filesystem *nfs;

    if (file->type == FT_DIRECTORY)
        return -DFS_STATUS_EISDIR;

    fd = (nfs_file *)(file->data);
    RT_ASSERT(fd != RT_NULL);
    RT_ASSERT(file->fs != RT_NULL);
    RT_ASSERT(file->fs->data != RT_NULL);
    nfs = (struct nfs_filesystem *)file->fs->data;

    if (nfs->nfs_client == RT_NULL)
        return -1;

    /* end of file */
    if (fd->eof == TRUE)
        return 0;

    args.file = fd->handle;
    do {
        args.offset = fd->offset;
        args.count = count > DFS_NFS_MAX_MTU ? DFS_NFS_MAX_MTU : count;
        count -= args.count;

        memset(&res, 0, sizeof(res));
        if (nfsproc3_read_3(args, &res, nfs->nfs_client) != RPC_SUCCESS)
        {
            rt_kprintf("Read failed\n");
            total = 0;
            break;
        }
        else if (res.status != NFS3_OK)
        {
            rt_kprintf("Read failed: %d\n", res.status);
            total = 0;
            break;
        }
        else
        {
            bytes = res.READ3res_u.resok.count;
            total += bytes;
            fd->offset += bytes;
            /* update current position */
            file->pos = fd->offset;
            memcpy(buf, res.READ3res_u.resok.data.data_val, bytes);
            buf = (void *)((char *)buf + args.count);
            if (res.READ3res_u.resok.eof)
            {
                /* something should probably be here */
                fd->eof = TRUE;
                break;
            }
        }
        xdr_free((xdrproc_t)xdr_READ3res, (char *)&res);
    } while(count > 0);

    xdr_free((xdrproc_t)xdr_READ3res, (char *)&res);

    return total;
}

int nfs_write(struct dfs_fd *file, const void *buf, rt_size_t count)
{
    WRITE3args args;
    WRITE3res res;
    ssize_t bytes, total=0;
    nfs_file *fd;
    struct nfs_filesystem *nfs;

    if (file->type == FT_DIRECTORY)
        return -DFS_STATUS_EISDIR;

    fd = (nfs_file *)(file->data);
    RT_ASSERT(fd != RT_NULL);
    RT_ASSERT(file->fs != RT_NULL);
    RT_ASSERT(file->fs->data != RT_NULL);
    nfs = (struct nfs_filesystem *)file->fs->data;

    if (nfs->nfs_client == RT_NULL)
        return -1;

    args.file = fd->handle;
    args.stable = FILE_SYNC;

    do {
        args.offset = fd->offset;

        memset(&res, 0, sizeof(res));
        args.data.data_val=(void *)buf;
        args.count = count > DFS_NFS_MAX_MTU ? DFS_NFS_MAX_MTU : count;
        args.data.data_len = args.count;
        count -= args.count;
        buf = (const void *)((char *)buf + args.count);

        if (nfsproc3_write_3(args, &res, nfs->nfs_client) != RPC_SUCCESS)
        {
            rt_kprintf("Write failed\n");
            total = 0;
            break;
        }
        else if (res.status != NFS3_OK)
        {
            rt_kprintf("Write failed: %d\n", res.status);
            total = 0;
            break;
        }
        else
        {
            bytes = res.WRITE3res_u.resok.count;
            fd->offset += bytes;
            total += bytes;
            /* update current position */
            file->pos = fd->offset;
            /* update file size */
			if (fd->size < fd->offset) fd->size = fd->offset;
			file->size = fd->size;
        }
        xdr_free((xdrproc_t)xdr_WRITE3res, (char *)&res);
    } while (count > 0);

    xdr_free((xdrproc_t)xdr_WRITE3res, (char *)&res);

    return total;
}

int nfs_lseek(struct dfs_fd *file, rt_off_t offset)
{
    nfs_file *fd;

    if (file->type == FT_DIRECTORY)
        return -DFS_STATUS_EISDIR;

    fd = (nfs_file *)(file->data);
    RT_ASSERT(fd != RT_NULL);

    if (offset <= fd->size)
    {
        fd->offset = offset;

        return offset;
    }

    return -DFS_STATUS_EIO;
}

int nfs_close(struct dfs_fd *file)
{
    if (file->type == FT_DIRECTORY)
    {
        struct nfs_dir *dir;

        dir = (struct nfs_dir *)file->data;
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&dir->handle);
        xdr_free((xdrproc_t)xdr_READDIR3res, (char *)&dir->res);
        rt_free(dir);
    }
    else if (file->type == FT_REGULAR)
    {
        struct nfs_file *fd;

        fd = (struct nfs_file *)file->data;

        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&fd->handle);
        rt_free(fd);
    }

    file->data = RT_NULL;
    return 0;
}

int nfs_open(struct dfs_fd *file)
{
    struct nfs_filesystem *nfs;

    RT_ASSERT(file->fs != RT_NULL);
    RT_ASSERT(file->fs->data != RT_NULL);
    nfs = (struct nfs_filesystem *)file->fs->data;

    if (file->flags & DFS_O_DIRECTORY)
    {
        nfs_dir *dir;
    
        if (file->flags & DFS_O_CREAT)
        {
            if (nfs_mkdir(nfs, file->path, 0755) < 0)
                return -DFS_STATUS_EAGAIN;
        }

        /* open directory */
        dir = nfs_opendir(nfs, file->path);
        if (dir == RT_NULL) return -DFS_STATUS_ENOENT;
        file->data = dir;
    }
    else
    {
        nfs_file *fp;
        nfs_fh3 *handle;

        /* create file */
        if (file->flags & DFS_O_CREAT)
        {
            if (nfs_create(nfs, file->path, 0664) < 0)
                return -DFS_STATUS_EAGAIN;
        }

        /* open file (get file handle ) */
        fp = rt_malloc(sizeof(nfs_file));
        if (fp == RT_NULL)
            return -DFS_STATUS_ENOMEM;

        handle = get_handle(nfs, file->path);
        if (handle == RT_NULL)
        {
            rt_free(fp);

            return -DFS_STATUS_ENOENT;
        }

        /* get size of file */
        fp->size = nfs_get_filesize(nfs, handle);
        fp->offset = 0;
        fp->eof = FALSE;

        copy_handle(&fp->handle, handle);
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
        rt_free(handle);

        if (file->flags & DFS_O_APPEND)
        {
            fp->offset = fp->size;
        }

        /* set private file */
        file->data = fp;
        file->size = fp->size;
    }

    return 0;
}

int nfs_stat(struct dfs_filesystem *fs, const char *path, struct stat *st)
{
    GETATTR3args args;
    GETATTR3res res;
    fattr3 *info;
    nfs_fh3 *handle;
    struct nfs_filesystem *nfs;

    RT_ASSERT(fs != RT_NULL);
    RT_ASSERT(fs->data != RT_NULL);
    nfs = (struct nfs_filesystem *)fs->data;

    handle = get_handle(nfs, path);
    if (handle == RT_NULL)
        return -1;

    args.object = *handle;

    memset(&res, '\0', sizeof(res));

    if (nfsproc3_getattr_3(args, &res, nfs->nfs_client) != RPC_SUCCESS)
    {
        rt_kprintf("GetAttr failed\n");
        return -1;
    }
    else if (res.status != NFS3_OK)
    {
        rt_kprintf("Getattr failed: %d\n", res.status);
        return -1;
    }

    info = &res.GETATTR3res_u.resok.obj_attributes;

    st->st_dev = 0;

    st->st_mode = DFS_S_IFREG | DFS_S_IRUSR | DFS_S_IRGRP | DFS_S_IROTH |
    DFS_S_IWUSR | DFS_S_IWGRP | DFS_S_IWOTH;
    if (info->type == NFS3DIR)
    {
        st->st_mode &= ~DFS_S_IFREG;
        st->st_mode |= DFS_S_IFDIR | DFS_S_IXUSR | DFS_S_IXGRP | DFS_S_IXOTH;
    }

    st->st_size  = info->size;
    st->st_mtime = info->mtime.seconds;
    st->st_blksize = 512;

    xdr_free((xdrproc_t)xdr_GETATTR3res, (char *)&res);
    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
    rt_free(handle);

    return 0;
}

nfs_dir *nfs_opendir(struct nfs_filesystem *nfs, const char *path)
{
    nfs_dir *dir;
    nfs_fh3 *handle;

    dir = rt_malloc(sizeof(nfs_dir));
    if (dir == RT_NULL)
    {
        return RT_NULL;
    }

    handle = get_handle(nfs, path);
    if (handle == RT_NULL)
    {
        rt_free(dir);

        return RT_NULL;
    }

    copy_handle(&dir->handle, handle);
    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
    rt_free(handle);

    dir->cookie = 0;
    memset(&dir->cookieverf, '\0', sizeof(cookieverf3));
    dir->entry = RT_NULL;
    dir->eof = FALSE;
    memset(&dir->res, '\0', sizeof(dir->res));

    return dir;
}

char *nfs_readdir(struct nfs_filesystem *nfs, nfs_dir *dir)
{
    static char name[NAME_MAX];

    if (nfs->nfs_client == RT_NULL || dir == RT_NULL)
        return RT_NULL;

    if (dir->entry == RT_NULL)
    {
        READDIR3args args;

        xdr_free((xdrproc_t)xdr_READDIR3res, (char *)&dir->res);
        memset(&dir->res, '\0', sizeof(dir->res));

        args.dir = dir->handle;
        args.cookie = dir->cookie;
        memcpy(&args.cookieverf, &dir->cookieverf, sizeof(cookieverf3));
        args.count = 1024;

        if (nfsproc3_readdir_3(args, &dir->res, nfs->nfs_client) != RPC_SUCCESS)
        {
            rt_kprintf("Readdir failed\n");

            return RT_NULL;
        }
        else if (dir->res.status != NFS3_OK)
        {
            rt_kprintf("Readdir failed: %d\n", dir->res.status);

            return RT_NULL;
        }

        memcpy(&dir->cookieverf, &dir->res.READDIR3res_u.resok.cookieverf, sizeof(cookieverf3));
        dir->eof = dir->res.READDIR3res_u.resok.reply.eof;
        dir->entry = dir->res.READDIR3res_u.resok.reply.entries;
    }
    if (dir->eof == TRUE && dir->entry == RT_NULL)
        return RT_NULL;

    dir->cookie = dir->entry->cookie;
    strncpy(name, dir->entry->name, NAME_MAX-1);
    dir->entry = dir->entry->nextentry;
    name[NAME_MAX - 1] = '\0';

    return name;
}

int nfs_unlink(struct dfs_filesystem *fs, const char *path)
{
    int ret = 0;
    struct nfs_filesystem *nfs;

    RT_ASSERT(fs != RT_NULL);
    RT_ASSERT(fs->data != RT_NULL);
    nfs = (struct nfs_filesystem *)fs->data;

    if (nfs_is_directory(nfs, path) == RT_FALSE)
    {
        /* remove file */
        REMOVE3args args;
        REMOVE3res res;
        nfs_fh3 *handle;

        handle = get_dir_handle(nfs, path);
        if (handle == RT_NULL)
            return -1;

        args.object.dir = *handle;
        args.object.name = strrchr(path, '/') + 1;
        if (args.object.name == RT_NULL)
        {
            args.object.name = (char *)path;
        }

        memset(&res, 0, sizeof(res));

        if (nfsproc3_remove_3(args, &res, nfs->nfs_client) != RPC_SUCCESS)
        {
            rt_kprintf("Remove failed\n");
            ret = -1;
        }
        else if (res.status != NFS3_OK)
        {
            rt_kprintf("Remove failed: %d\n", res.status);
            ret = -1;
        }
        xdr_free((xdrproc_t)xdr_REMOVE3res, (char *)&res);
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
        rt_free(handle);
    }
    else
    {
        /* remove directory */
        RMDIR3args args;
        RMDIR3res res;
        nfs_fh3 *handle;

        handle = get_dir_handle(nfs, path);
        if (handle == RT_NULL)
            return -1;

        args.object.dir = *handle;
        args.object.name = strrchr(path, '/') + 1;
        if (args.object.name == RT_NULL)
        {
            args.object.name = (char *)path;
        }

        memset(&res, 0, sizeof(res));

        if (nfsproc3_rmdir_3(args, &res, nfs->nfs_client) != RPC_SUCCESS)
        {
            rt_kprintf("Rmdir failed\n");
            ret = -1;
        }
        else if (res.status != NFS3_OK)
        {
            rt_kprintf("Rmdir failed: %d\n", res.status);
            ret = -1;
        }

        xdr_free((xdrproc_t)xdr_RMDIR3res, (char *)&res);
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
        rt_free(handle);    
    }

    return ret;
}

int nfs_rename(struct dfs_filesystem *fs, const char *src, const char *dest)
{
    RENAME3args args;
    RENAME3res res;
    nfs_fh3 *sHandle;
    nfs_fh3 *dHandle;
    int ret = 0;
    struct nfs_filesystem *nfs;

    RT_ASSERT(fs != RT_NULL);
    RT_ASSERT(fs->data != RT_NULL);
    nfs = (struct nfs_filesystem *)fs->data;

    if (nfs->nfs_client == RT_NULL)
        return -1;

    sHandle = get_dir_handle(nfs, src);
    if (sHandle == RT_NULL)
        return -1;

    dHandle = get_dir_handle(nfs, dest);
    if (dHandle == RT_NULL)
        return -1;

    args.from.dir = *sHandle;
    args.from.name = strrchr(src, '/') + 1;
    if (args.from.name == RT_NULL)
        args.from.name = (char *)src;

    args.to.dir = *dHandle;
    args.to.name = strrchr(src, '/') + 1;
    if (args.to.name == RT_NULL)
        args.to.name = (char *)dest;

    memset(&res, '\0', sizeof(res));

    if (nfsproc3_rename_3(args, &res, nfs->nfs_client) != RPC_SUCCESS)
    {
        rt_kprintf("Rename failed\n");
        ret = -1;
    }
    else if (res.status != NFS3_OK)
    {
        rt_kprintf("Rename failed: %d\n", res.status);
        ret = -1;
    }

    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)sHandle);
    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)dHandle);
    xdr_free((xdrproc_t)xdr_RENAME3res, (char *)&res);

    return ret;
}

int nfs_getdents(struct dfs_fd *file, struct dirent *dirp, rt_uint32_t count)
{
    nfs_dir *dir;
    rt_uint32_t index;
    struct dirent *d;
    struct nfs_filesystem *nfs;
    char *name;

    dir = (nfs_dir *)(file->data);
    RT_ASSERT(dir != RT_NULL);
    RT_ASSERT(file->fs != RT_NULL);
    RT_ASSERT(file->fs->data != RT_NULL);
    nfs = (struct nfs_filesystem *)file->fs->data;

    /* make integer count */
    count = (count / sizeof(struct dirent)) * sizeof(struct dirent);
    if (count == 0)
        return -DFS_STATUS_EINVAL;

    index = 0;
    while (1)
    {
        d = dirp + index;

        name = nfs_readdir(nfs, dir);
        if (name == RT_NULL)
            break;

        d->d_type = DFS_DT_REG;

        d->d_namlen = rt_strlen(name);
        d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
        rt_strncpy(d->d_name, name, rt_strlen(name) + 1);

        index ++;
        if (index * sizeof(struct dirent) >= count)
            break;
    }

    return index * sizeof(struct dirent);
}

static const struct dfs_filesystem_operation _nfs = 
{
    "nfs",
    DFS_FS_FLAG_DEFAULT,    
    nfs_mount,
    nfs_unmount,
    RT_NULL, /* mkfs */
    RT_NULL, /* statfs */
    nfs_open,
    nfs_close,
    nfs_ioctl,
    nfs_read,
    nfs_write,
    RT_NULL, /* flush */
    nfs_lseek,
    nfs_getdents,
    nfs_unlink, 
    nfs_stat,
    nfs_rename,
};

int nfs_init(void)
{
    /* register fatfs file system */
    dfs_register(&_nfs);

    return RT_EOK;
}
INIT_FS_EXPORT(nfs_init);
