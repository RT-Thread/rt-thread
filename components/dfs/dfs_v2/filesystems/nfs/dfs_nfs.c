/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <stdio.h>
#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_dentry.h>
#include <dfs_file.h>
#include <dfs_mnt.h>

#include <rpc/rpc.h>

#include "mount.h"
#include "nfs.h"
#ifdef RT_USING_PAGECACHE
#include "dfs_pcache.h"
#endif

#define DFS_NFS_MAX_MTU  1344

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

#define HOST_LENGTH         256
#define EXPORT_PATH_LENGTH  256

struct nfs_filesystem
{
    nfs_fh3 root_handle;
    nfs_fh3 current_handle;
    CLIENT *nfs_client;
    CLIENT *mount_client;

    char host[HOST_LENGTH];
    char export[EXPORT_PATH_LENGTH];
    void *data;             /* nfs_file or nfs_dir */
};

typedef struct nfs_filesystem nfs_filesystem;
typedef struct nfs_file nfs_file;
typedef struct nfs_dir nfs_dir;

#ifdef RT_USING_PAGECACHE
static ssize_t nfs_page_read(struct dfs_file *file, struct dfs_page *page);
static ssize_t nfs_page_write(struct dfs_page *page);

static struct dfs_aspace_ops nfs_aspace_ops =
{
    .read = nfs_page_read,
    .write = nfs_page_write,
};
#endif

static nfs_dir *nfs_opendir(nfs_filesystem *nfs, const char *path);

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

    /* make NULL */
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
    if (dest->data.data_val == NULL)
    {
        dest->data.data_len = 0;

        return;
    }

    memcpy(dest->data.data_val, source->data.data_val, dest->data.data_len);
}

static nfs_fh3 *get_handle(nfs_filesystem *nfs, const char *name)
{
    nfs_fh3 *handle = NULL;
    char *file;
    char *path;
    char *init;

    init = path = rt_malloc(strlen(name) + 1);
    if (init == NULL)
        return NULL;

    memcpy(init, name, strlen(name) + 1);

    handle = rt_malloc(sizeof(nfs_fh3));
    if (handle == NULL)
    {
        rt_free(init);

        return NULL;
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

    while ((file = strtok_r(NULL, "/", &path)) != NULL)
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

            return NULL;
        }
        else if (res.status != NFS3_OK)
        {
            rt_free(init);
            rt_free(handle);
            xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&args.what.dir);
            xdr_free((xdrproc_t)xdr_LOOKUP3res, (char *)&res);

            return NULL;
        }
        copy_handle(handle, &res.LOOKUP3res_u.resok.object);
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&args.what.dir);
        xdr_free((xdrproc_t)xdr_LOOKUP3res, (char *)&res);
    }

    rt_free(init);

    return handle;
}

static nfs_fh3 *get_dir_handle(nfs_filesystem *nfs, const char *name)
{
    nfs_fh3 *handle = NULL;
    char *file;
    char *path;
    char *init;

    init = path = rt_malloc(strlen(name) + 1);
    if (init == NULL)
        return NULL;
    memcpy(init, name, strlen(name) + 1);

    handle = rt_malloc(sizeof(nfs_fh3));
    if (handle == NULL)
    {
        rt_free(init);

        return NULL;
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

    while ((file = strtok_r(NULL, "/", &path)) != NULL && path && path[0] != 0)
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

            return NULL;
        }
        else if (res.status != NFS3_OK)
        {
            rt_free(init);
            rt_free(handle);
            xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&args.what.dir);
            xdr_free((xdrproc_t)xdr_LOOKUP3res, (char *)&res);

            return NULL;
        }
        copy_handle(handle, &res.LOOKUP3res_u.resok.object);
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&args.what.dir);
        xdr_free((xdrproc_t)xdr_LOOKUP3res, (char *)&res);
    }

    rt_free(init);

    return handle;
}

static size_t nfs_get_filesize(nfs_filesystem *nfs, nfs_fh3 *handle)
{
    GETATTR3args args;
    GETATTR3res res;
    fattr3 *info;
    size_t size;

    args.object = *handle;

    memset(&res, '\0', sizeof(res));

    if ((nfsproc3_getattr_3(args, &res, nfs->nfs_client) != RPC_SUCCESS) ||
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

static rt_bool_t nfs_is_directory(nfs_filesystem *nfs, const char *name)
{
    GETATTR3args args;
    GETATTR3res res;
    fattr3 *info;
    nfs_fh3 *handle;
    rt_bool_t result;

    result = RT_FALSE;
    handle = get_handle(nfs, name);
    if (handle == NULL)
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

    info = &res.GETATTR3res_u.resok.obj_attributes;

    if (info->type == NFS3DIR)
        result = RT_TRUE;

    xdr_free((xdrproc_t)xdr_GETATTR3res, (char *)&res);
    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
    rt_free(handle);

    return result;
}

static int nfs_create(nfs_filesystem *nfs, const char *name, mode_t mode)
{
    CREATE3args args;
    CREATE3res res;
    int ret = 0;
    nfs_fh3 *handle;

    if (nfs->nfs_client == NULL)
    {
        return -1;
    }

    handle = get_dir_handle(nfs, name);
    if (handle == NULL)
    {
        return -1;
    }
    args.where.dir = *handle;
    args.where.name = strrchr(name, '/') + 1;
    if (args.where.name == NULL)
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

static int nfs_mkdir(nfs_filesystem *nfs, const char *name, mode_t mode)
{
    MKDIR3args args;
    MKDIR3res res;
    int ret = 0;
    nfs_fh3 *handle;

    if (nfs->nfs_client == NULL)
        return -1;

    handle = get_dir_handle(nfs, name);
    if (handle == NULL)
        return -1;

    args.where.dir = *handle;
    args.where.name = strrchr(name, '/') + 1;
    if (args.where.name == NULL)
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

/* mount(NULL, "/mnt", "nfs", 0, "192.168.1.1:/export") */
static int nfs_mount(struct dfs_mnt *mnt, unsigned long rwflag, const void *data)
{
    mountres3 res;
    nfs_filesystem *nfs;

    nfs = (nfs_filesystem *)rt_malloc(sizeof(nfs_filesystem));
    memset(nfs, 0, sizeof(nfs_filesystem));
    memset(&res, '\0', sizeof(mountres3));

    if (nfs_parse_host_export((const char *)data, nfs->host, HOST_LENGTH,
                              nfs->export, EXPORT_PATH_LENGTH) < 0)
    {
        rt_kprintf("host or export path error\n");
        goto __return;
    }

    nfs->mount_client = clnt_create((char *)nfs->host, MOUNT_PROGRAM, MOUNT_V3, "udp");
    if (nfs->mount_client == NULL)
    {
        rt_kprintf("create mount client failed\n");
        goto __return;
    }

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
    nfs->nfs_client = clnt_create((char *)nfs->host, NFS_PROGRAM, NFS_V3, "udp");
    if (nfs->nfs_client == NULL)
    {
        rt_kprintf("creat nfs client failed\n");
        goto __return;
    }
    copy_handle(&nfs->root_handle, (nfs_fh3 *)&res.mountres3_u.mountinfo.fhandle);
    copy_handle(&nfs->current_handle, &nfs->root_handle);
    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&res.mountres3_u.mountinfo.fhandle);
    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&res.mountres3_u.mountinfo.auth_flavors);

    nfs->nfs_client->cl_auth = authnone_create();
    mnt->data = nfs;

    return 0;

__return:
    if (nfs != NULL)
    {
        if (nfs->mount_client != NULL)
        {
            clnt_destroy(nfs->mount_client);
        }
        if (nfs->nfs_client != NULL)
        {
            if (nfs->nfs_client->cl_auth != NULL)
            {
                auth_destroy(nfs->nfs_client->cl_auth);
            }
            clnt_destroy(nfs->nfs_client);
        }
        rt_free(nfs);
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&res.mountres3_u.mountinfo.fhandle);
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&res.mountres3_u.mountinfo.auth_flavors);
    }

    return -1;
}

static int nfs_unmount(struct dfs_mnt *mnt)
{
    nfs_filesystem *nfs;

    RT_ASSERT(mnt != NULL);
    RT_ASSERT(mnt->data != NULL);
    nfs = (nfs_filesystem *)mnt->data;

    if (nfs->mount_client != NULL &&
        mountproc3_umnt_3((char *)nfs->export, NULL, nfs->mount_client) != RPC_SUCCESS)
    {
        rt_kprintf("unmount failed\n");

        return -1;
    }

    /* destroy nfs client */
    if (nfs->nfs_client != NULL)
    {
        if (nfs->nfs_client->cl_auth != NULL)
        {
            auth_destroy(nfs->nfs_client->cl_auth);
            nfs->nfs_client->cl_auth = NULL;
        }
        clnt_destroy(nfs->nfs_client);
        nfs->nfs_client = NULL;
    }

    /* destroy mount client */
    if (nfs->mount_client != NULL)
    {
        if (nfs->mount_client->cl_auth != NULL)
        {
            auth_destroy(nfs->mount_client->cl_auth);
            nfs->mount_client->cl_auth = NULL;
        }
        clnt_destroy(nfs->mount_client);
        nfs->mount_client = NULL;
    }

    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&nfs->root_handle);
    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&nfs->current_handle);

    rt_free(nfs);
    mnt->data = NULL;

    return 0;
}

static int nfs_ioctl(struct dfs_file *file, int cmd, void *args)
{
    return -ENOSYS;
}

static ssize_t nfs_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
{
    READ3args args;
    READ3res res;
    ssize_t bytes, total = 0;
    nfs_file *fd;
    nfs_filesystem *nfs;

    if (file->vnode->type == FT_DIRECTORY)
        return -EISDIR;

    nfs = (struct nfs_filesystem *)(file->vnode->mnt->data);
    fd = (nfs_file *)(file->vnode->data);
    RT_ASSERT(fd != NULL);

    if (nfs->nfs_client == NULL)
        return -1;

    /* end of file */
    if (fd->eof == TRUE)
        return 0;

    args.file = fd->handle;
    rt_mutex_take(&file->vnode->lock, RT_WAITING_FOREVER);
    fd->offset = *pos;
    do
    {
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
            *pos = fd->offset;
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
    }
    while (count > 0);
    rt_mutex_release(&file->vnode->lock);

    xdr_free((xdrproc_t)xdr_READ3res, (char *)&res);

    return total;
}

static ssize_t _nfs_write(struct dfs_vnode *vnode, const void *buf, size_t count, off_t *pos)
{
    WRITE3args args;
    WRITE3res res;
    ssize_t bytes, total = 0;
    nfs_file *fd;
    nfs_filesystem *nfs;

    if (vnode->type == FT_DIRECTORY)
        return -EISDIR;

    nfs = (struct nfs_filesystem *)(vnode->mnt->data);
    fd = (nfs_file *)(vnode->data);
    RT_ASSERT(fd != NULL);

    if (nfs->nfs_client == NULL)
        return -1;

    args.file = fd->handle;
    args.stable = FILE_SYNC;
    rt_mutex_take(&vnode->lock, RT_WAITING_FOREVER);
    fd->offset = *pos;
    do
    {
        args.offset = fd->offset;

        memset(&res, 0, sizeof(res));
        args.data.data_val = (void *)buf;
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
            *pos = fd->offset;
            /* update file size */
            if (fd->size < fd->offset)
                fd->size = fd->offset;
            if (vnode->size < fd->size)
                vnode->size = fd->size;
        }
        xdr_free((xdrproc_t)xdr_WRITE3res, (char *)&res);
    } while (count > 0);
    rt_mutex_release(&vnode->lock);

    xdr_free((xdrproc_t)xdr_WRITE3res, (char *)&res);

    return total;
}

static ssize_t nfs_write(struct dfs_file *file, const void *buf, size_t count, off_t *pos)
{
    struct dfs_vnode *vnode = file->vnode;
    return _nfs_write(vnode, buf, count, pos);
}

static off_t nfs_lseek(struct dfs_file *file, off_t offset, int wherece)
{
    if (file->vnode->type == FT_DIRECTORY)
        return -EISDIR;

    switch (wherece)
    {
    case SEEK_SET:
        break;

    case SEEK_CUR:
        offset += file->fpos;
        break;

    case SEEK_END:
        offset += file->vnode->size;
        break;

    default:
        return -EINVAL;
    }

    nfs_file *fd = (nfs_file *)(file->vnode->data);

    if (offset <= fd->size)
    {
        fd->offset = offset;

        return offset;
    }

    return -EIO;
}

static int nfs_close(struct dfs_file *file)
{
    struct dfs_vnode *vnode = (struct dfs_vnode *)(file->vnode);
    nfs_filesystem *nfs = (struct nfs_filesystem *)(vnode->mnt->data);

    RT_ASSERT(vnode->ref_count > 0);
    if (vnode->ref_count > 1)
    {
        return 0;
    }

    if (vnode->type == FT_DIRECTORY)
    {
        struct nfs_dir *dir;

        dir = (struct nfs_dir *)vnode->data;
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&dir->handle);
        xdr_free((xdrproc_t)xdr_READDIR3res, (char *)&dir->res);
        rt_free(dir);
    }
    else if (vnode->type == FT_REGULAR)
    {
        struct nfs_file *fd;

        fd = (struct nfs_file *)vnode->data;

        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)&fd->handle);
        rt_free(fd);
    }

    vnode->data = RT_NULL;
    rt_mutex_detach(&vnode->lock);
    return 0;
}

static int nfs_open(struct dfs_file *file)
{
    struct dfs_vnode *vnode = (struct dfs_vnode *)(file->vnode);
    nfs_filesystem *nfs = (struct nfs_filesystem *)(vnode->mnt->data);
    char *pathname = file->dentry->pathname;

    RT_ASSERT(vnode->ref_count > 0);
    if (vnode->data)
    {
        if (vnode->type == FT_DIRECTORY
                && !(file->flags & O_DIRECTORY))
        {
            return -ENOENT;
        }
        file->fpos = 0;
        return 0;
    }

    if (file->flags & O_DIRECTORY)
    {
        nfs_dir *dir;

        if (file->flags & O_CREAT)
        {
            if (nfs_mkdir(nfs, pathname, vnode->mode) < 0)
            {
                return -EAGAIN;
            }
        }

        /* open directory */
        dir = nfs_opendir(nfs, pathname);
        if (dir == NULL)
        {
            return -ENOENT;
        }
        vnode->type = FT_DIRECTORY;
        vnode->data = dir;
        rt_mutex_init(&vnode->lock, pathname, RT_IPC_FLAG_PRIO);
    }
    else
    {
        nfs_file *fp;
        nfs_fh3 *handle;

        /* create file */
        if (file->flags & O_CREAT)
        {
            if (nfs_create(nfs, pathname, vnode->mode) < 0)
            {
                return -EAGAIN;
            }
        }

        /* open file (get file handle ) */
        fp = rt_malloc(sizeof(nfs_file));
        if (fp == NULL)
            return -ENOMEM;

        handle = get_handle(nfs, pathname);
        if (handle == NULL)
        {
            rt_free(fp);

            return -ENOENT;
        }

        /* get size of file */
        fp->size = nfs_get_filesize(nfs, handle);
        fp->offset = 0;
        fp->eof = FALSE;

        copy_handle(&fp->handle, handle);
        xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
        rt_free(handle);

        if (file->flags & O_APPEND)
        {
            fp->offset = fp->size;
        }

        file->fpos = fp->offset;
        vnode->size = fp->size;
        vnode->type = FT_REGULAR;
        vnode->data = fp;
        rt_mutex_init(&file->vnode->lock, file->dentry->pathname, RT_IPC_FLAG_PRIO);
    }

    return 0;
}

static int nfs_stat(struct dfs_dentry *dentry, struct stat *st)
{
    GETATTR3args args;
    GETATTR3res res;
    fattr3 *info;
    nfs_fh3 *handle;
    nfs_filesystem *nfs;
    char *path;

    nfs = (nfs_filesystem *)dentry->mnt->data;
    path = dentry->pathname;

    handle = get_handle(nfs, path);
    if (handle == NULL)
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

    memset(st, 0, sizeof(struct stat));

    st->st_mode = info->mode;
    if (info->type == NFS3REG)
    {
        st->st_mode |= S_IFREG;
    }
    else if (info->type == NFS3DIR)
    {
        st->st_mode |= S_IFDIR;
    }
    else if (info->type == NFS3LNK)
    {
        st->st_mode |= S_IFLNK;
    }

    st->st_nlink = info->nlink;
    st->st_uid = info->uid;
    st->st_gid = info->gid;
#ifdef RT_USING_PAGECACHE
    st->st_size = (dentry->vnode && dentry->vnode->aspace) ? dentry->vnode->size : info->size;
#else
    st->st_size = info->size;
#endif
    st->st_atim.tv_sec = info->atime.seconds;
    st->st_atim.tv_nsec = info->atime.nseconds;
    st->st_mtim.tv_sec = info->mtime.seconds;
    st->st_mtim.tv_nsec = info->mtime.nseconds;
    st->st_ctim.tv_sec = info->ctime.seconds;
    st->st_ctim.tv_nsec = info->ctime.nseconds;

    xdr_free((xdrproc_t)xdr_GETATTR3res, (char *)&res);
    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
    rt_free(handle);

    return 0;
}

static nfs_dir *nfs_opendir(nfs_filesystem *nfs, const char *path)
{
    nfs_dir *dir;
    nfs_fh3 *handle;

    dir = rt_malloc(sizeof(nfs_dir));
    if (dir == NULL)
    {
        return NULL;
    }

    handle = get_handle(nfs, path);
    if (handle == NULL)
    {
        rt_free(dir);
        return NULL;
    }

    copy_handle(&dir->handle, handle);
    xdr_free((xdrproc_t)xdr_nfs_fh3, (char *)handle);
    rt_free(handle);

    dir->cookie = 0;
    memset(&dir->cookieverf, '\0', sizeof(cookieverf3));
    dir->entry = NULL;
    dir->eof = FALSE;
    memset(&dir->res, '\0', sizeof(dir->res));

    return dir;
}

static char *nfs_readdir(nfs_filesystem *nfs, nfs_dir *dir)
{
    static char name[NAME_MAX];

    if (nfs->nfs_client == NULL || dir == NULL)
        return NULL;

    if (dir->entry == NULL)
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

            return NULL;
        }
        else if (dir->res.status != NFS3_OK)
        {
            rt_kprintf("Readdir failed: %d\n", dir->res.status);

            return NULL;
        }

        memcpy(&dir->cookieverf, &dir->res.READDIR3res_u.resok.cookieverf, sizeof(cookieverf3));
        dir->eof = dir->res.READDIR3res_u.resok.reply.eof;
        dir->entry = dir->res.READDIR3res_u.resok.reply.entries;
    }
    if (dir->eof == TRUE && dir->entry == NULL)
        return NULL;

    dir->cookie = dir->entry->cookie;
    strncpy(name, dir->entry->name, NAME_MAX - 1);
    dir->entry = dir->entry->nextentry;
    name[NAME_MAX - 1] = '\0';

    return name;
}

static int nfs_unlink(struct dfs_dentry *dentry)
{
    int ret = 0;
    nfs_filesystem *nfs;
    char *path;

    nfs = (nfs_filesystem *)dentry->mnt->data;
    path = dentry->pathname;

    if (nfs_is_directory(nfs, path) == RT_FALSE)
    {
        /* remove file */
        REMOVE3args args;
        REMOVE3res res;
        nfs_fh3 *handle;

        handle = get_dir_handle(nfs, path);
        if (handle == NULL)
            return -1;

        args.object.dir = *handle;
        args.object.name = strrchr(path, '/') + 1;
        if (args.object.name == NULL)
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
        if (handle == NULL)
            return -1;

        args.object.dir = *handle;
        args.object.name = strrchr(path, '/') + 1;
        if (args.object.name == NULL)
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

static int nfs_rename(struct dfs_dentry *old_dentry, struct dfs_dentry *new_dentry)
{
    RENAME3args args;
    RENAME3res res;
    nfs_fh3 *sHandle;
    nfs_fh3 *dHandle;
    int ret = 0;
    nfs_filesystem *nfs;
    char *src, *dest;

    nfs = (nfs_filesystem *)old_dentry->mnt->data;
    src = old_dentry->pathname;
    dest = new_dentry->pathname;

    if (nfs->nfs_client == NULL)
        return -1;

    sHandle = get_dir_handle(nfs, src);
    if (sHandle == NULL)
        return -1;

    dHandle = get_dir_handle(nfs, dest);
    if (dHandle == NULL)
        return -1;

    args.from.dir = *sHandle;
    args.from.name = strrchr(src, '/') + 1;
    if (args.from.name == NULL)
        args.from.name = (char *)src;

    args.to.dir = *dHandle;
    args.to.name = strrchr(src, '/') + 1;
    if (args.to.name == NULL)
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

static int nfs_getdents(struct dfs_file *file, struct dirent *dirp, uint32_t count)
{
    nfs_dir *dir;
    rt_uint32_t index;
    struct dirent *d;
    nfs_filesystem *nfs;
    char *name;

    nfs = (struct nfs_filesystem *)(file->vnode->mnt->data);
    dir = (nfs_dir *)(file->vnode->data);
    RT_ASSERT(dir != NULL);

    /* make integer count */
    count = (count / sizeof(struct dirent)) * sizeof(struct dirent);
    if (count == 0)
        return -EINVAL;

    index = 0;
    while (1)
    {
        d = dirp + index;

        name = nfs_readdir(nfs, dir);
        if (name == NULL)
            break;

        if (rt_strcmp(name, ".") == 0)
        {
            continue;
        }
        else if (rt_strcmp(name, "..") == 0)
        {
            continue;
        }

        d->d_type = DT_REG;

        d->d_namlen = rt_strlen(name);
        d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
        rt_strncpy(d->d_name, name, DIRENT_NAME_MAX);

        index ++;
        if (index * sizeof(struct dirent) >= count)
            break;
    }

    file->fpos += index * sizeof(struct dirent);

    return index * sizeof(struct dirent);
}

static struct dfs_vnode *nfs_lookup(struct dfs_dentry *dentry)
{
    struct stat st;
    struct dfs_vnode *vnode = RT_NULL;

    if (dentry == NULL || dentry->mnt == NULL || dentry->mnt->data == NULL)
    {
        return NULL;
    }

    if (nfs_stat(dentry, &st) != 0)
    {
        return vnode;
    }

    vnode = dfs_vnode_create();
    if (vnode)
    {
        vnode->mnt = dentry->mnt;
        vnode->atime = st.st_atim;
        vnode->mtime = st.st_mtim;
        vnode->ctime = st.st_ctim;
        vnode->size = st.st_size;
        vnode->nlink = st.st_nlink;
        vnode->uid = st.st_uid;
        vnode->gid = st.st_gid;
        vnode->data = NULL;

        vnode->mode = st.st_mode;
        if (S_ISDIR(st.st_mode))
        {
            vnode->type = FT_DIRECTORY;
        }
        else
        {
            vnode->type = FT_REGULAR;
#ifdef RT_USING_PAGECACHE
            vnode->aspace = dfs_aspace_create(dentry, vnode, &nfs_aspace_ops);
#endif
        }
    }

    return vnode;
}

static struct dfs_vnode *nfs_create_vnode(struct dfs_dentry *dentry, int type, mode_t mode)
{
    struct dfs_vnode *vnode = RT_NULL;

    if (dentry == NULL || dentry->mnt == NULL || dentry->mnt->data == NULL)
    {
        return NULL;
    }

    vnode = dfs_vnode_create();
    if (vnode)
    {
        if (type == FT_DIRECTORY)
        {
            /* fat directory force mode 0555 */
            vnode->mode = S_IFDIR | (S_IRUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
            vnode->type = FT_DIRECTORY;
        }
        else
        {
            /* fat REGULAR file mode force mode 0777 */
            vnode->mode = S_IFREG | (S_IRWXU | S_IRWXG | S_IRWXO);
            vnode->type = FT_REGULAR;
#ifdef RT_USING_PAGECACHE
            vnode->aspace = dfs_aspace_create(dentry, vnode, &nfs_aspace_ops);
#endif
        }

        vnode->mnt = dentry->mnt;
        vnode->data = NULL;
        vnode->size = 0;
    }

    return vnode;
}

static int nfs_free_vnode(struct dfs_vnode *vnode)
{
    /* nothing to be freed */
    if (vnode && vnode->ref_count <= 1)
    {
        vnode->data = NULL;
    }

    return 0;
}

#ifdef RT_USING_PAGECACHE
static ssize_t nfs_page_read(struct dfs_file *file, struct dfs_page *page)
{
    int ret = -EINVAL;

    if (page->page)
    {
        off_t fpos = page->fpos;
        ret = nfs_read(file, page->page, page->size, &fpos);
    }

    return ret;
}

static ssize_t nfs_page_write(struct dfs_page *page)
{
    off_t fpos;
    ssize_t result;

    if (page->aspace->vnode->type == FT_DIRECTORY)
    {
        return -EISDIR;
    }

    rt_mutex_take(&page->aspace->vnode->lock, RT_WAITING_FOREVER);
    fpos = page->fpos;
    result = _nfs_write(page->aspace->vnode, page->page, page->len, &fpos);
    rt_mutex_release(&page->aspace->vnode->lock);

    return result;
}
#endif

static const struct dfs_file_ops nfs_fops =
{
    .open = nfs_open,
    .close = nfs_close,
    .read = nfs_read,
    .write = nfs_write,
    .ioctl = nfs_ioctl,
    .getdents = nfs_getdents,
    .lseek = nfs_lseek,
};

static const struct dfs_filesystem_ops nfs_fsops =
{
    .name = "nfs",
    .flags = DFS_FS_FLAG_DEFAULT,
    .default_fops = &nfs_fops,
    .mount = nfs_mount,
    .umount = nfs_unmount,
    .unlink = nfs_unlink,
    .stat = nfs_stat,
    .rename = nfs_rename,
    .lookup = nfs_lookup,
    .create_vnode = nfs_create_vnode,
    .free_vnode = nfs_free_vnode,
};

static struct dfs_filesystem_type _nfs =
{
    .fs_ops = &nfs_fsops,
};

int nfs_init(void)
{
    /* register nfs file system */
    dfs_register(&_nfs);

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(nfs_init);
