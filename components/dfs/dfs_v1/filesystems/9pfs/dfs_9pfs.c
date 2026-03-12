/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtservice.h>

#define DBG_TAG "dfs.9p"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "dfs_9pfs.h"
#include <drivers/misc.h>
#include <drivers/byteorder.h>
#include <posix/string.h>

#define OREAD   0       /* open for read */
#define OWRITE  1       /* write */
#define ORDWR   2       /* read and write */
#define OEXEC   3       /* execute, == read but check execute permission */
#define OEXCL   4
#define OTRUNC  16      /* or'ed in (except for exec), truncate file first */
#define OCEXEC  32      /* or'ed in, close on exec */
#define ORCLOSE 64      /* or'ed in, remove on close */
#define OAPPEND 128     /* or'ed in, append */

#define NOTAG   ((rt_uint16_t)~0)
#define NOFID   ((rt_uint32_t)~0)
#define TAG     1

static rt_list_t _protocol_nodes = RT_LIST_OBJECT_INIT(_protocol_nodes);
static struct rt_spinlock _protocol_lock = { 0 };

#ifndef rt_le8_to_cpu
#define rt_le8_to_cpu
#endif
#ifndef rt_cpu_to_le8
#define rt_cpu_to_le8
#endif

#define P9_OF_OPS_GET(width, dir) \
rt_inline rt_uint##width##_t get_##dir##_##value##width##_of(   \
        struct p9_connection *conn, unsigned idx)               \
{                                                               \
    rt_uint##width##_t *vp = (void *)&conn->dir##_buffer[idx];  \
    return rt_le##width##_to_cpu(*vp);                          \
}

#define P9_OF_OPS_PUT(width, dir) \
rt_inline void put_##dir##_##value##width##_of(                 \
        struct p9_connection *conn, unsigned idx,               \
        rt_uint##width##_t value)                               \
{                                                               \
    rt_uint##width##_t *vp = (void *)&conn->dir##_buffer[idx];  \
    *vp = rt_cpu_to_le##width(value);                           \
}

#define P9_OPS_PUT(width) \
rt_inline rt_off_t put_value##width(struct p9_connection *conn, \
        rt_off_t off, rt_uint##width##_t value)                 \
{                                                               \
    ((rt_uint##width##_t *)(conn->tx_buffer + off))[0] =        \
            rt_cpu_to_le##width(value);                         \
    return off + sizeof(value);                                 \
}

#define P9_OPS_GROUP(width)     \
    P9_OF_OPS_GET(width, rx)    \
    P9_OF_OPS_GET(width, tx)    \
    P9_OF_OPS_PUT(width, rx)    \
    P9_OF_OPS_PUT(width, tx)    \
    P9_OPS_PUT(width)

P9_OPS_GROUP(8)
P9_OPS_GROUP(16)
P9_OPS_GROUP(32)
P9_OPS_GROUP(64)
#undef P9_OF_OPS_GET
#undef P9_OF_OPS_PUT
#undef P9_OPS_GET
#undef P9_OPS_GROUP

rt_inline rt_uint32_t put_header(struct p9_connection *conn,
        rt_uint8_t hd, rt_uint16_t tag_flags)
{
    rt_uint8_t *stack = conn->tx_buffer;

    ((rt_uint32_t *)stack)[0] = rt_cpu_to_le32(0);
    stack += sizeof(rt_uint32_t);

    stack[0] = hd;
    stack += sizeof(rt_uint8_t);

    ((rt_uint16_t *)stack)[0] = rt_cpu_to_le16(tag_flags);
    stack += sizeof(rt_uint16_t);

    return stack - conn->tx_buffer;
}

rt_inline rt_off_t put_bytes(struct p9_connection *conn, rt_off_t off,
        rt_uint8_t *bytes, rt_uint32_t count)
{
    rt_uint8_t *stack = conn->tx_buffer + off;

    ((rt_uint16_t *)stack)[0] = rt_cpu_to_le16(count);
    stack += sizeof(rt_uint16_t);

    rt_memcpy(stack, bytes, count);
    stack += count;

    return stack - conn->tx_buffer;
}

rt_inline rt_off_t put_string(struct p9_connection *conn, rt_off_t off,
        char *string)
{
    rt_uint32_t len = rt_strlen(string);
    rt_uint8_t *stack = conn->tx_buffer + off;

    ((rt_uint16_t *)stack)[0] = rt_cpu_to_le16(len);
    stack += sizeof(rt_uint16_t);

    rt_memcpy(stack, string, len);
    stack += len;

    return stack - conn->tx_buffer;
}

struct p9_connection *p9_connection_alloc(struct p9_protocol *p9p,
        const char *aname, rt_uint32_t buffer_size)
{
    struct p9_connection *conn;

    if (!p9p || !aname)
    {
        return RT_NULL;
    }

    /* Buffer size expected to be 1M */
    buffer_size = rt_max_t(rt_uint32_t, buffer_size, 0x100000);

    if (!(conn = rt_malloc(sizeof(*conn) + buffer_size)))
    {
        return RT_NULL;
    }

    conn->msg_size = buffer_size;
    conn->fid = P9_ROOT_FID;
#ifdef RT_USING_SMART
    conn->uname = "rt-smart";
#else
    conn->uname = "rt-thread";
#endif
    conn->aname = (char *)aname;

    conn->rx_buffer = (void *)conn + sizeof(*conn);
    conn->tx_buffer = conn->rx_buffer + buffer_size / 2;
    rt_mutex_init(&conn->lock, conn->aname, RT_IPC_FLAG_PRIO);

    conn->protocol = p9p;

    return conn;
}

rt_err_t p9_connection_free(struct p9_connection *conn)
{
    rt_free(conn);

    return RT_EOK;
}

int p9_transaction(struct p9_connection *conn,
        rt_uint32_t tx_size, rt_uint32_t *out_rx_size)
{
    rt_err_t err;
    rt_uint32_t rx_size;

    RT_ASSERT(conn != RT_NULL);
    RT_ASSERT(conn->protocol != RT_NULL);

    rx_size = conn->msg_size;
    if ((err = conn->protocol->transport(conn->protocol,
            conn->tx_buffer, tx_size, conn->rx_buffer, &rx_size)))
    {
        return P9_TRANSPORT_ERROR;
    }

    if (get_rx_value16_of(conn, P9_MSG_TAG) !=
        get_tx_value16_of(conn, P9_MSG_TAG))
    {
        return P9_UNEXPECTED_TAG;
    }

    if (get_rx_value8_of(conn, P9_MSG_ID) == P9_MSG_ERR)
    {
        rt_uint32_t err_len = rt_min_t(rt_uint32_t, sizeof(conn->error) - 1,
                get_rx_value16_of(conn, P9_MSG_ERR_STR_LEN));

        rt_strncpy(conn->error, (void *)&conn->rx_buffer[P9_MSG_ERR_STR], err_len);

        return P9_R_ERROR;
    }

    if ((get_tx_value8_of(conn, P9_MSG_ID) + 1) !=
        get_rx_value8_of(conn, P9_MSG_ID))
    {
        return P9_UNEXPECTED_MSG;
    }

    if (out_rx_size)
    {
        *out_rx_size = rx_size;
    }

    return 0;
}

int p9_version(struct p9_connection *conn)
{
    int rc;
    rt_uint32_t size;

    RT_ASSERT(conn != RT_NULL);

    rt_mutex_take(&conn->lock, RT_WAITING_FOREVER);

    /*
     * size[4] Tversion tag[2] msize[4] version[s]
     * size[4] Rversion tag[2] msize[4] version[s]
     */
    size = put_header(conn, P9_HD_TVERSION, NOTAG);
    size = put_value32(conn, size, conn->msg_size);
    size = put_string(conn, size, P9_VERSION);
    put_tx_value32_of(conn, P9_MSG_SIZE, size);

    if (!(rc = p9_transaction(conn, size, RT_NULL)))
    {
        char *version;
        rt_uint32_t version_len;
        rt_uint32_t msg_size = get_rx_value32_of(conn, P9_MSG_VER_MSIZE);

        conn->msg_size = rt_min_t(rt_uint32_t, conn->msg_size, msg_size);

        version = (char *)&conn->rx_buffer[P9_MSG_VER_STR];
        version_len = get_rx_value16_of(conn, P9_MSG_VER_STR_LEN);

        LOG_D("Version: %s", version);

        if (!rt_strncmp(P9_VERSION_UNKNOWN, version, version_len))
        {
            rc = P9_UNKNOWN_VERSION;
        }
    }

    rt_mutex_release(&conn->lock);

    return rc;
}

int p9_attach(struct p9_connection *conn)
{
    int rc;
    rt_uint32_t size;

    RT_ASSERT(conn != RT_NULL);

    if (19 + rt_strlen(conn->uname) + rt_strlen(conn->aname) > conn->msg_size)
    {
        return P9_MSG_TOO_LONG;
    }

    rt_mutex_take(&conn->lock, RT_WAITING_FOREVER);

    /*
     * size[4] Tattach tag[2] fid[4] afid[4] uname[s] aname[s]
     * size[4] Rattach tag[2] qid[13]
     */
    size = put_header(conn, P9_HD_TATTACH, TAG);
    size = put_value32(conn, size, conn->fid);
    size = put_value32(conn, size, NOFID);
    size = put_string(conn, size, conn->uname);
    size = put_string(conn, size, conn->aname);
    size = put_value32(conn, size, RT_UINT32_MAX);
    put_tx_value32_of(conn, P9_MSG_SIZE, size);

    rc = p9_transaction(conn, size, RT_NULL);

    rt_mutex_release(&conn->lock);

    return rc;
}

static int p9_clunk_lockess(struct p9_connection *conn, rt_uint32_t fid)
{
    rt_uint32_t size;

    /*
     * size[4] Tclunk tag[2] fid[4]
     * size[4] Rclunk tag[2]
     */
    size = put_header(conn, P9_HD_TCLUNK, TAG);
    size = put_value32(conn, size, fid);
    put_tx_value32_of(conn, P9_MSG_SIZE, size);

    return p9_transaction(conn, size, RT_NULL);
}

int p9_clunk(struct p9_connection *conn, rt_uint32_t fid)
{
    int rc;

    RT_ASSERT(conn != RT_NULL);

    rt_mutex_take(&conn->lock, RT_WAITING_FOREVER);

    rc = p9_clunk_lockess(conn, fid);

    rt_mutex_release(&conn->lock);

    return rc;
}

rt_err_t dfs_9pfs_add_tag(struct p9_protocol *p9p)
{
    rt_ubase_t level;

    if (!p9p || !p9p->tag || !p9p->transport)
    {
        return -RT_EINVAL;
    }

    rt_list_init(&p9p->list);

    level = rt_spin_lock_irqsave(&_protocol_lock);
    rt_list_insert_before(&_protocol_nodes, &p9p->list);
    rt_spin_unlock_irqrestore(&_protocol_lock, level);

    LOG_D("Add tag(%s) on %s", p9p->tag, p9p->name);

    return RT_EOK;
}

rt_err_t dfs_9pfs_del_tag(struct p9_protocol *p9p)
{
    rt_ubase_t level;

    if (!p9p)
    {
        return -RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&_protocol_lock);
    rt_list_remove(&p9p->list);
    rt_spin_unlock_irqrestore(&_protocol_lock, level);

    LOG_D("Delete tag(%s) on %s", p9p->tag, p9p->name);

    return RT_EOK;
}

static int p9_to_fs_err(int rc)
{
    const int p9_err[] =
    {
        [0] = RT_EOK,
        [-P9_ERROR] = -EIO,
        [-P9_UNKNOWN_VERSION] = -ENOSYS,
        [-P9_R_ERROR] = -EIO,
        [-P9_MSG_TOO_LONG] = -ENOSPC,
        [-P9_UNEXPECTED_MSG] = -EINVAL,
        [-P9_UNEXPECTED_TAG] = -EINVAL,
        [-P9_TRANSPORT_ERROR] = -EIO,
        [-P9_NO_TRANSPORT] = -EINVAL,
        [-P9_NULL_PATH] = -EINVAL,
        [-P9_PATH_ELEMENT_TOO_LONG] = -EINVAL,
        [-P9_READ_UNEXPECTED_DATA] = -EINVAL,
        [-P9_NO_BUFFER] = -ENOSPC,
        [-P9_MSG_SIZE_TOO_BIG] = -ENOSPC,
    };

    return p9_err[-rc];
}

static int p9_alloc_fid(struct p9_connection *conn)
{
    int fid = rt_bitmap_next_clear_bit(conn->fid_map, 0, DFS_FD_MAX);

    if (fid < DFS_FD_MAX)
    {
        rt_bitmap_set_bit(conn->fid_map, fid);

        return fid + P9_FILE_FID;
    }

    return NOFID;
}

static void p9_free_fid(struct p9_connection *conn, int fid)
{
    if (fid >= P9_FILE_FID)
    {
        rt_bitmap_clear_bit(conn->fid_map, fid - P9_FILE_FID);
    }
}

static int p9_free_fid_clunk(struct p9_connection *conn, int fid)
{
    int rc;

    if (!(rc = p9_clunk_lockess(conn, fid)))
    {
        p9_free_fid(conn, fid);
    }

    return rc;
}

static rt_uint8_t fs_to_p9_flags(rt_uint32_t raw_flags)
{
    rt_uint8_t flags = 0;

    switch (raw_flags & 3)
    {
    case O_RDONLY: flags = OREAD; break;
    case O_WRONLY: flags = OWRITE; break;
    case O_RDWR: flags = ORDWR; break;
    default: RT_ASSERT(0); break;
    }

    if (raw_flags & O_TRUNC)
    {
        flags |= OTRUNC;
    }

    if (raw_flags & O_APPEND)
    {
        flags |= OAPPEND;
    }

    if (raw_flags & O_EXCL)
    {
        flags |= OEXCL;
    }

    return flags;
}

static char *p9_basename(const char *path)
{
    const char *basename = strrchr(path, '/');

    return (char *)(basename ? basename + 1 : path);
}

static int p9_walk_path_raw(struct p9_connection *conn, const char *path,
        rt_bool_t submode)
{
    rt_uint32_t size;
    const char *split;
    int rc, count = 0, len, fid = conn->fid, new_fid;

    new_fid = p9_alloc_fid(conn);

    if (new_fid < 0)
    {
        return P9_NO_BUFFER;
    }

    if (submode)
    {
        --count;
    }

    /* Pass '/' */
    ++path;

    /*
     * size[4] Twalk tag[2] fid[4] newfid[4] nwname[2] nwname*(wname[s])
     * size[4] Rwalk tag[2] nwqid[2] nwqid*(wqid[13])
     */
    size = put_header(conn, P9_HD_TWALK, TAG);
    size = put_value32(conn, size, fid);
    size = put_value32(conn, size, new_fid);
    size = put_value16(conn, size, 0);  /* Fill later */

    do {
        split = strchrnul(path, '/');

        len = split - path;
        size = put_bytes(conn, size, (rt_uint8_t *)path, len);

        path += len + 1;
        ++count;
    } while (*split && count < P9_MSG_WALK_MAX_ELMT);

    if (count < P9_MSG_WALK_MAX_ELMT)
    {
        put_value16(conn, P9_MSG_WALK_TX_ELMT, count);

        if (!(rc = p9_transaction(conn, size, RT_NULL)))
        {
            if (count == get_rx_value16_of(conn, P9_MSG_WALK_RX_ELMT))
            {
                rc = new_fid;
            }
            else
            {
                /* Should be `P9_PARTIAL_WALK` if support longer path. */
                rc = P9_ERROR;
                p9_free_fid(conn, new_fid);
            }
        }
    }
    else
    {
        rc = P9_PATH_ELEMENT_TOO_LONG;
        p9_free_fid(conn, new_fid);
    }

    return rc;
}

rt_inline int p9_walk_path(struct p9_connection *conn, const char *path)
{
    return p9_walk_path_raw(conn, path, RT_FALSE);
}

rt_inline int p9_walk_subpath(struct p9_connection *conn, const char *path)
{
    return p9_walk_path_raw(conn, path, RT_TRUE);
}

static int dfs_9pfs_open(struct dfs_file *fd)
{
    int rc;
    rt_uint32_t size;
    rt_bool_t is_root;
    struct p9_connection *conn;
    struct p9_file *p9f = rt_calloc(1, sizeof(*p9f));

    if (!p9f)
    {
        return -RT_ENOMEM;
    }
    conn = fd->vnode->fs->data;

    p9f->fid = conn->fid;
    p9f->connection = conn;
    is_root = !rt_strcmp(fd->vnode->path, "/");

    rt_mutex_take(&conn->lock, RT_WAITING_FOREVER);

    if (!is_root)
    {
        if ((rc = p9_walk_path(p9f->connection, fd->vnode->path)) > 0)
        {
            p9f->fid = rc;
        }
        else if (fd->flags & O_CREAT)
        {
            rt_uint32_t parent_fid, perm = 0755;

            if (fd->flags & O_DIRECTORY)
            {
                perm |= P9_STAT_MODE_DIR;
            }

            parent_fid = p9_walk_subpath(conn, fd->vnode->path);

            /*
             * size[4] Tcreate tag[2] fid[4] name[s] perm[4] mode[1] extension[s]
             * size[4] Rcreate tag[2] qid[13] iounit[4]
             */
            size = put_header(conn, P9_HD_TCREATE, TAG);
            size = put_value32(conn, size, parent_fid);
            size = put_string(conn, size, p9_basename(fd->vnode->path));
            size = put_value32(conn, size, perm);
            size = put_value8(conn, size, fs_to_p9_flags(fd->flags));
            size = put_string(conn, size, "");
            put_tx_value32_of(conn, P9_MSG_SIZE, size);

            if (!(rc = p9_transaction(conn, size, RT_NULL)))
            {
                p9f->iounit = get_rx_value32_of(conn, P9_MSG_CREATE_IOUNIT);

                if ((rc = p9_walk_path(p9f->connection, fd->vnode->path)) > 0)
                {
                    p9f->fid = rc;
                }
            }

            p9_free_fid_clunk(conn, parent_fid);
        }
    }

    if (is_root || rc >= 0)
    {
        /*
         * size[4] Tstat tag[2] fid[4]
         * size[4] Rstat tag[2] stat[n]
         */
        size = put_header(conn, P9_HD_TSTAT, TAG);
        size = put_value32(conn, size, p9f->fid);
        put_tx_value32_of(conn, P9_MSG_SIZE, size);

        if (!(rc = p9_transaction(conn, size, RT_NULL)))
        {
            fd->vnode->size = get_rx_value64_of(conn, P9_MSG_STAT_LEN);

            /*
             * size[4] Topen tag[2] fid[4] mode[1]
             * size[4] Ropen tag[2] qid[13] iounit[4]
             */
            size = put_header(conn, P9_HD_TOPEN, TAG);
            size = put_value32(conn, size, p9f->fid);
            size = put_value8(conn, size, fs_to_p9_flags(fd->flags));
            put_tx_value32_of(conn, P9_MSG_SIZE, size);

            if (!(rc = p9_transaction(conn, size, RT_NULL)))
            {
                p9f->iounit = get_rx_value32_of(conn, P9_MSG_OPEN_IOUNIT);
            }
        }
    }

    rt_mutex_release(&conn->lock);

    if (!is_root && rc)
    {
        if (p9f->fid != conn->fid)
        {
            p9_free_fid(conn, p9f->fid);
        }

        rt_free(p9f);

        return p9_to_fs_err(rc);
    }

    fd->vnode->data = p9f;

    return 0;
}

static int dfs_9pfs_close(struct dfs_file *fd)
{
    int rc = 0;
    struct p9_file *p9f = fd->vnode->data;
    struct p9_connection *conn = p9f->connection;

    if (p9f->fid != conn->fid)
    {
        rt_mutex_take(&conn->lock, RT_WAITING_FOREVER);
        rc = p9_free_fid_clunk(conn, p9f->fid);
        rt_mutex_release(&conn->lock);
    }

    if (!rc)
    {
        rt_free(p9f);
    }

    return p9_to_fs_err(rc);
}

static ssize_t dfs_9pfs_read(struct dfs_file *fd, void *buf, size_t count)
{
    int rc;
    size_t tcount = 0;
    rt_uint32_t max_count, set, size, got;
    struct p9_file *p9f = fd->vnode->data;
    struct p9_connection *conn = p9f->connection;

    max_count = conn->msg_size - P9_MSG_READ_DATA;

    rt_mutex_take(&conn->lock, RT_WAITING_FOREVER);

    while ((ssize_t)count > 0)
    {
        set = rt_min_t(rt_uint32_t, max_count, count);

        /*
         * size[4] Tread tag[2] fid[4] offset[8] count[4]
         * size[4] Rread tag[2] count[4] data[count]
         */
        size = put_header(conn, P9_HD_TREAD, TAG);
        size = put_value32(conn, size, p9f->fid);
        size = put_value64(conn, size, fd->pos);
        size = put_value32(conn, size, set);
        put_tx_value32_of(conn, P9_MSG_SIZE, size);

        if (!(rc = p9_transaction(conn, size, RT_NULL)))
        {
            got = get_rx_value32_of(conn, P9_MSG_READ_COUNT);

            if (got == 0)
            {
                break;
            }
            else if (got <= set)
            {
                fd->pos += got;

                rt_memcpy(buf, conn->rx_buffer + P9_MSG_READ_DATA, got);
            }
            else
            {
                tcount = p9_to_fs_err(P9_READ_UNEXPECTED_DATA);
                break;
            }

            count -= got;
            tcount += got;
        }
    }

    rt_mutex_release(&conn->lock);

    return tcount;
}

static ssize_t dfs_9pfs_write(struct dfs_file *fd, const void *buf, size_t count)
{
    int rc;
    size_t tcount = 0;
    rt_uint32_t max_count, set, size, got;
    struct p9_file *p9f = fd->vnode->data;
    struct p9_connection *conn = p9f->connection;

    max_count = conn->msg_size - P9_MSG_WRITE_DATA;

    rt_mutex_take(&conn->lock, RT_WAITING_FOREVER);

    while ((ssize_t)count > 0)
    {
        set = rt_min_t(rt_uint32_t, max_count, count);

        /*
         * size[4] Twrite tag[2] fid[4] offset[8] count[4] data[count]
         * size[4] Rwrite tag[2] count[4]
         */
        size = put_header(conn, P9_HD_TWRITE, TAG);
        size = put_value32(conn, size, p9f->fid);
        size = put_value64(conn, size, fd->pos);
        size = put_value32(conn, size, set);
        rt_memcpy(conn->tx_buffer + P9_MSG_WRITE_DATA, buf, set);
        size += set;
        put_tx_value32_of(conn, P9_MSG_SIZE, size);

        if (!(rc = p9_transaction(conn, size, RT_NULL)))
        {
            got = get_rx_value32_of(conn, P9_MSG_WRITE_COUNT);

            if (got <= set)
            {
                fd->pos += set;
            }
            else
            {
                tcount = p9_to_fs_err(P9_READ_UNEXPECTED_DATA);
                break;
            }

            count -= got;
            tcount += got;
        }
    }

    rt_mutex_release(&conn->lock);

    return tcount;
}

static int dfs_9pfs_flush(struct dfs_file *fd)
{
    int rc;
    rt_uint32_t size;
    struct p9_file *p9f = fd->vnode->data;
    struct p9_connection *conn = p9f->connection;

    /*
     * size[4] Tfsync tag[2] fid[4] datasync[4]
     * size[4] Rfsync tag[2]
     */
    size = put_header(conn, P9_HD_TFSYNC, TAG);
    size = put_value32(conn, size, p9f->fid);
    size = put_value32(conn, size, 1);
    put_tx_value32_of(conn, P9_MSG_SIZE, size);

    rc = p9_transaction(conn, size, RT_NULL);

    return p9_to_fs_err(rc);
}

static off_t dfs_9pfs_lseek(struct dfs_file *fd, off_t offset)
{
    int ret = -EIO;

    if (offset <= fd->vnode->size)
    {
        fd->pos = offset;
        ret = fd->pos;
    }

    return ret;
}

static int dfs_9pfs_getdents(struct dfs_file *fd, struct dirent *dirp, uint32_t count)
{
    int rc;
    rt_uint64_t off;
    rt_uint32_t ret, end, stat_size, size;
    struct p9_file *p9f = fd->vnode->data;
    struct p9_connection *conn = p9f->connection;

    count = (count / sizeof(struct dirent));

    if (!count)
    {
        return -EINVAL;
    }
    end = fd->pos + count;
    count = 0;

    rt_mutex_take(&conn->lock, RT_WAITING_FOREVER);

    /*
     * size[4] Tread tag[2] fid[4] offset[8] count[4]
     * size[4] Rread tag[2] count[4] stat[n]
     */
    size = put_header(conn, P9_HD_TREAD, TAG);
    size = put_value32(conn, size, p9f->fid);
    size = put_value64(conn, size, 0);
    size = put_value32(conn, size, fd->vnode->size);
    put_tx_value32_of(conn, P9_MSG_SIZE, size);

    if (!(rc = p9_transaction(conn, size, RT_NULL)))
    {
        ret = get_rx_value32_of(conn, P9_MSG_READ_COUNT);
        off = P9_MSG_READ_DATA - P9_MSG_STAT_SIZE;

        for (int i = 0; (rt_int32_t)ret > 0; off += stat_size, ret -= stat_size, ++i)
        {
            /*
             * size[2] type[2] dev[4] qid[1+4+8] mode[4] atime[4] mtime[4] length[8]
             */
            stat_size = get_rx_value16_of(conn, off + P9_MSG_STAT_SIZE) + sizeof(rt_uint16_t);

            if (i < fd->pos)
            {
                continue;
            }

            if (get_rx_value16_of(conn, off + P9_MSG_STAT_TYPE) & P9_STAT_MODE_DIR)
            {
                dirp->d_type = DT_DIR;
            }
            else
            {
                dirp->d_type = DT_REG;
            }

            /*
             * name_size[2] name[name_size]
             * uid_size[2] uid[uid_size]
             * gid_size[2] gid[gid_size]
             * muid_size[2] muid[muid_size]
             * extension_size[2] extension[extension_size]
             * n_uid[4]
             * n_gid[4]
             * n_muid[4]
             */
            dirp->d_namlen = get_rx_value16_of(conn, off + P9_MSG_STAT_NAME_LEN);
            dirp->d_reclen = (rt_uint16_t)sizeof(struct dirent);
            rt_strncpy(dirp->d_name,
                    (void *)conn->rx_buffer + off + P9_MSG_STAT_NAME,
                    dirp->d_namlen);
            dirp->d_name[dirp->d_namlen] = '\0';

            if (!rt_strcmp(dirp->d_name, ".") || !rt_strcmp(dirp->d_name, ".."))
            {
                ++fd->pos;
                continue;
            }

            ++fd->pos;
            ++dirp;
            ++count;

            if (fd->pos >= end)
            {
                break;
            }
        }
    }

    rt_mutex_release(&conn->lock);

    count *= sizeof(struct dirent);

    return count;
}

static const struct dfs_file_ops _9pfs_fops =
{
    .open       = dfs_9pfs_open,
    .close      = dfs_9pfs_close,
    .read       = dfs_9pfs_read,
    .write      = dfs_9pfs_write,
    .flush      = dfs_9pfs_flush,
    .lseek      = dfs_9pfs_lseek,
    .getdents   = dfs_9pfs_getdents,
};

static int dfs_9pfs_mount(struct dfs_filesystem *fs,
        unsigned long rwflag, const void *data)
{
    rt_ubase_t level;
    struct p9_protocol *p9p, *p9p_tmp;
    struct p9_connection *conn = RT_NULL;

    if (!data)
    {
        return (int)-RT_EINVAL;
    }

    level = rt_spin_lock_irqsave(&_protocol_lock);

    rt_list_for_each_entry(p9p_tmp, &_protocol_nodes, list)
    {
        if (!rt_strcmp(p9p_tmp->tag, data))
        {
            p9p = p9p_tmp;
            break;
        }
    }

    rt_spin_unlock_irqrestore(&_protocol_lock, level);

    if (!p9p)
    {
        return (int)-RT_EINVAL;
    }

    if (!(conn = p9_connection_alloc(p9p, p9p->tag, 0)))
    {
        return (int)-RT_ENOMEM;
    }

    if (p9_version(conn) || p9_attach(conn))
    {
        p9_connection_free(conn);
        return (int)-RT_EINVAL;
    }

    fs->data = conn;

    return (int)RT_EOK;
}

static int dfs_9pfs_unmount(struct dfs_filesystem *fs)
{
    struct p9_connection *conn = fs->data;

    p9_clunk(conn, conn->fid);

    return p9_connection_free(conn);
}

static int dfs_9pfs_statfs(struct dfs_filesystem *fs, struct statfs *buf)
{
    int rc;
    rt_uint32_t size;
    struct p9_connection *conn = fs->data;

    rt_mutex_take(&conn->lock, RT_WAITING_FOREVER);

    /*
     * size[4] Tstatfs tag[2] fid[4]
     * size[4] Rstatfs tag[2]
     *      f_type[4]
     *      f_bsize[4]
     *      f_blocks[8]
     *      f_bfree[8]
     *      f_bavail[8]
     *      f_files[8]
     *      f_ffree[8]
     *      fsid_val[8]
     *      f_namelen[4]
     */
    size = put_header(conn, P9_HD_TSTATFS, TAG);
    size = put_value32(conn, size, conn->fid);
    put_tx_value32_of(conn, P9_MSG_SIZE, size);

    if (!(rc = p9_transaction(conn, size, RT_NULL)))
    {
        buf->f_bsize = get_rx_value32_of(conn, P9_MSG_F_BSIZE);
        buf->f_blocks = get_rx_value64_of(conn, P9_MSG_F_BLOCKS);
        buf->f_bfree = get_rx_value64_of(conn, P9_MSG_F_BFREE);
        buf->f_bavail = get_rx_value64_of(conn, P9_MSG_F_BAVAIL);
    }

    rt_mutex_release(&conn->lock);

    return p9_to_fs_err(rc);
}

static int dfs_9pfs_unlink(struct dfs_filesystem *fs, const char *pathname)
{
    rt_uint32_t size;
    int rc = 0, fid;
    struct p9_connection *conn = fs->data;

    rt_mutex_take(&conn->lock, RT_WAITING_FOREVER);

    if ((rc = p9_walk_path(conn, pathname)) > 0)
    {
        fid = rc;

        /*
         * size[4] Tremove tag[2] fid[4]
         * size[4] Rremove tag[2]
         */
        size = put_header(conn, P9_HD_TREMOVE, TAG);
        size = put_value32(conn, size, fid);
        put_tx_value32_of(conn, P9_MSG_SIZE, size);

        rc = p9_transaction(conn, size, RT_NULL);
        p9_free_fid_clunk(conn, fid);
    }

    rt_mutex_release(&conn->lock);

    return p9_to_fs_err(rc);
}

static int dfs_9pfs_stat(struct dfs_filesystem *fs,
        const char *filename, struct stat *st)
{
    int rc = 0, fid;
    rt_uint32_t size, mode;
    struct p9_connection *conn = fs->data;

    rt_mutex_take(&conn->lock, RT_WAITING_FOREVER);

    if ((rc = p9_walk_path(conn, filename)) > 0)
    {
        fid = rc;

        /*
         * size[4] Tstat tag[2] fid[4]
         * size[4] Rstat tag[2] stat[n]
         */
        size = put_header(conn, P9_HD_TSTAT, TAG);
        size = put_value32(conn, size, fid);
        put_tx_value32_of(conn, P9_MSG_SIZE, size);

        if (!(rc = p9_transaction(conn, size, RT_NULL)))
        {
            st->st_dev = 0;

            mode = get_rx_value32_of(conn, P9_MSG_STAT_MODE);
            st->st_mode = 0;
            if (mode & P9_STAT_MODE_DIR)
            {
                st->st_mode |= S_IFDIR;
            }
            else
            {
                st->st_mode |= S_IFREG;
            }
            if (mode & P9_STAT_MODE_SYMLINK)
            {
                st->st_mode |= S_IFLNK;
            }
            if (mode & P9_STAT_MODE_SOCKET)
            {
                st->st_mode |= S_IFSOCK;
            }
            if (mode & P9_STAT_MODE_NAMED_PIPE)
            {
                st->st_mode |= S_IFIFO;
            }
            if (mode & P9_STAT_MODE_SETUID)
            {
                st->st_mode |= S_ISUID;
            }
            if (mode & P9_STAT_MODE_SETGID)
            {
                st->st_mode |= S_ISGID;
            }
            if (mode & P9_STAT_MODE_SETVTX)
            {
                st->st_mode |= S_ISVTX;
            }

            st->st_atime = get_rx_value32_of(conn, P9_MSG_STAT_ATIME);
            st->st_mtime = get_rx_value32_of(conn, P9_MSG_STAT_MTIME);
            st->st_size = get_rx_value64_of(conn, P9_MSG_STAT_LEN);

            /*
             * name_size[2] name[name_size]
             * uid_size[2] uid[uid_size]
             * gid_size[2] gid[gid_size]
             * muid_size[2] muid[muid_size]
             * extension_size[2] extension[extension_size]
             * n_uid[4]
             * n_gid[4]
             * n_muid[4]
             */
            size = P9_MSG_STAT_NAME_LEN;
            size += sizeof(rt_uint16_t) + get_rx_value16_of(conn, size);
            size += sizeof(rt_uint16_t) + get_rx_value16_of(conn, size);
            size += sizeof(rt_uint16_t) + get_rx_value16_of(conn, size);
            size += sizeof(rt_uint16_t) + get_rx_value16_of(conn, size);
            st->st_uid = get_rx_value32_of(conn, size) + sizeof(rt_uint32_t);
            st->st_gid = get_rx_value32_of(conn, size) + sizeof(rt_uint32_t);
        }

        p9_free_fid_clunk(conn, fid);
    }

    rt_mutex_release(&conn->lock);

    return p9_to_fs_err(rc);
}

static int dfs_9pfs_rename(struct dfs_filesystem *fs,
        const char *oldpath, const char *newpath)
{
    int rc = 0, fid;
    rt_uint32_t size;
    struct p9_connection *conn = fs->data;

    rt_mutex_take(&conn->lock, RT_WAITING_FOREVER);

    if ((fid = p9_walk_path(conn, oldpath)) > 0)
    {
        /*
         * size[4] Trename tag[2] fid[4] new_fid[4] name[s]
         * size[4] Rrename tag[2]
         */
        size = put_header(conn, P9_HD_TRENAME, TAG);
        size = put_value32(conn, size, fid);
        size = put_value32(conn, size, NOFID);
        size = put_string(conn, size, p9_basename(newpath));
        put_tx_value32_of(conn, P9_MSG_SIZE, size);

        rc = p9_transaction(conn, size, RT_NULL);
        p9_free_fid_clunk(conn, fid);
    }

    rt_mutex_release(&conn->lock);

    return p9_to_fs_err(rc);
}

static const struct dfs_filesystem_ops _9pfs =
{
    .name       = "9p",
    .flags      = DFS_FS_FLAG_DEFAULT,
    .fops       = &_9pfs_fops,

    .mount      = dfs_9pfs_mount,
    .unmount    = dfs_9pfs_unmount,

    .statfs     = dfs_9pfs_statfs,

    .unlink     = dfs_9pfs_unlink,
    .stat       = dfs_9pfs_stat,
    .rename     = dfs_9pfs_rename,
};

int dfs_9pfs_init(void)
{
    /* register 9p file system */
    return dfs_register(&_9pfs);
}
INIT_COMPONENT_EXPORT(dfs_9pfs_init);
