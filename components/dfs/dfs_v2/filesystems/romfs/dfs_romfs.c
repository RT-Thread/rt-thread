/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_dentry.h>
#include <dfs_file.h>
#include <dfs_mnt.h>

#include "dfs_romfs.h"
#include <errno.h>
#include <fcntl.h>

#include <rtdbg.h>

static const struct dfs_file_ops _rom_fops;

static const mode_t romfs_modemap[] =
{
    S_IFREG  | 0644,    /* regular file */
    S_IFDIR  | 0644,    /* directory */
    0,                  /* hard link */
    S_IFLNK  | 0777,    /* symlink */
    S_IFBLK  | 0600,    /* blockdev */
    S_IFCHR  | 0600,    /* chardev */
    S_IFSOCK | 0644,    /* socket */
    S_IFIFO  | 0644     /* FIFO */
};

static int dfs_romfs_mount(struct dfs_mnt *mnt, unsigned long rwflag, const void *data)
{
    struct romfs_dirent *root_dirent;

    if (data == NULL)
        return -1;

    root_dirent = (struct romfs_dirent *)data;
    mnt->data = root_dirent;

    return 0;
}

static int dfs_romfs_umount(struct dfs_mnt *fs)
{
    return RT_EOK;
}

int dfs_romfs_ioctl(struct dfs_file *file, int cmd, void *args)
{
    int ret = RT_EOK;
    struct romfs_dirent *dirent;

    dirent = (struct romfs_dirent *)file->data;
    RT_ASSERT(dirent != NULL);

    switch (cmd)
    {
    case RT_FIOGETADDR:
        {
            *(rt_ubase_t*)args = (rt_ubase_t)dirent->data;
            break;
        }
    case RT_FIOFTRUNCATE:
        {
            break;
        }
    default:
        ret = -RT_EINVAL;
        break;
    }
    return ret;
}

rt_inline int check_dirent(struct romfs_dirent *dirent)
{
    if (dirent == NULL
        ||(dirent->type != ROMFS_DIRENT_FILE && dirent->type != ROMFS_DIRENT_DIR)
        || dirent->size == ~0)
        return -1;
    return 0;
}

struct romfs_dirent *__dfs_romfs_lookup(struct romfs_dirent *root_dirent, const char *path, rt_size_t *size)
{
    rt_size_t index, found;
    const char *subpath, *subpath_end;
    struct romfs_dirent *dirent;
    rt_size_t dirent_size;

    /* Check the root_dirent. */
    if (check_dirent(root_dirent) != 0)
        return NULL;

    if (path[0] == '/' && path[1] == '\0')
    {
        *size = root_dirent->size;
        return root_dirent;
    }

    /* goto root directy entries */
    dirent = (struct romfs_dirent *)root_dirent->data;
    dirent_size = root_dirent->size;

    /* get the end position of this subpath */
    subpath_end = path;
    /* skip /// */
    while (*subpath_end && *subpath_end == '/')
        subpath_end ++;
    subpath = subpath_end;
    while ((*subpath_end != '/') && *subpath_end)
        subpath_end ++;

    while (dirent != NULL)
    {
        found = 0;

        /* search in folder */
        for (index = 0; index < dirent_size; index ++)
        {
            if (check_dirent(&dirent[index]) != 0)
                return NULL;
            if (rt_strlen(dirent[index].name) == (subpath_end - subpath) &&
                    rt_strncmp(dirent[index].name, subpath, (subpath_end - subpath)) == 0)
            {
                dirent_size = dirent[index].size;

                /* skip /// */
                while (*subpath_end && *subpath_end == '/')
                    subpath_end ++;
                subpath = subpath_end;
                while ((*subpath_end != '/') && *subpath_end)
                    subpath_end ++;

                if (!(*subpath))
                {
                    *size = dirent_size;
                    return &dirent[index];
                }

                if (dirent[index].type == ROMFS_DIRENT_DIR)
                {
                    /* enter directory */
                    dirent = (struct romfs_dirent *)dirent[index].data;
                    found = 1;
                    break;
                }
                else
                {
                    /* return file dirent */
                    return &dirent[index];
                }
            }
        }

        if (!found)
            break; /* not found */
    }

    /* not found */
    return NULL;
}

static struct dfs_vnode *dfs_romfs_lookup (struct dfs_dentry *dentry)
{
    rt_size_t size;
    struct dfs_vnode *vnode = RT_NULL;
    struct romfs_dirent *root_dirent = RT_NULL, *dirent = RT_NULL;

    RT_ASSERT(dentry != RT_NULL);
    RT_ASSERT(dentry->mnt != RT_NULL);

    root_dirent = (struct romfs_dirent *)dentry->mnt->data;
    if (check_dirent(root_dirent) == 0)
    {
        /* create a vnode */
        DLOG(msg, "rom", "vnode", DLOG_MSG, "dfs_vnode_create()");
        vnode = dfs_vnode_create();
        if (vnode)
        {
            dirent = __dfs_romfs_lookup(root_dirent, dentry->pathname, &size);
            if (dirent)
            {
                vnode->nlink = 1;
                vnode->size = dirent->size;
                if (dirent->type == ROMFS_DIRENT_DIR)
                {
                    vnode->mode = romfs_modemap[ROMFS_DIRENT_DIR] | S_IRUSR;
                    vnode->type = FT_DIRECTORY;
                }
                else if (dirent->type == ROMFS_DIRENT_FILE)
                {
                    vnode->mode = romfs_modemap[ROMFS_DIRENT_FILE] | S_IRUSR | S_IXUSR;
                    vnode->type = FT_REGULAR;
                }

                DLOG(msg, "rom", "rom", DLOG_MSG, "vnode->data = dirent");
                vnode->data = dirent;
                vnode->mnt = dentry->mnt;
            }
            else
            {
                /* no-entry */
                DLOG(msg, "rom", "vnode", DLOG_MSG, "dfs_vnode_destroy, no-dentry");
                dfs_vnode_destroy(vnode);
                vnode = RT_NULL;
            }
        }
    }

    return vnode;
}

static int dfs_romfs_free_vnode(struct dfs_vnode *vnode)
{
    /* nothing to be freed */
    if (vnode->ref_count <= 1)
    {
        vnode->data = NULL;
    }

    return 0;
}

static ssize_t dfs_romfs_read(struct dfs_file *file, void *buf, size_t count, off_t *pos)
{
    rt_size_t length;
    struct romfs_dirent *dirent;

    dirent = (struct romfs_dirent *)file->vnode->data;
    RT_ASSERT(dirent != NULL);

    if (check_dirent(dirent) != 0)
    {
        return -EIO;
    }

    if (count < file->vnode->size - *pos)
        length = count;
    else
        length = file->vnode->size - *pos;

    if (length > 0)
        memcpy(buf, &(dirent->data[*pos]), length);

    /* update file current position */
    *pos += length;

    return length;
}

static int dfs_romfs_close(struct dfs_file *file)
{
    return RT_EOK;
}

int dfs_romfs_open(struct dfs_file *file)
{
    rt_size_t size;
    struct romfs_dirent *dirent;
    struct romfs_dirent *root_dirent;
    struct dfs_mnt *mnt;

    if (file->flags & (O_CREAT | O_WRONLY | O_APPEND | O_TRUNC | O_RDWR))
    {
        return -EINVAL;
    }

    mnt = file->dentry->mnt;
    RT_ASSERT(mnt != RT_NULL);

    root_dirent = (struct romfs_dirent *)mnt->data;
    if (check_dirent(root_dirent) != 0)
    {
        return -EIO;
    }

    /* get rom dirent */
    dirent = __dfs_romfs_lookup(root_dirent, file->dentry->pathname, &size);
    if (dirent == NULL)
    {
        return -ENOENT;
    }

    file->data = dirent;
    file->fops = &_rom_fops;
    file->fpos = 0;

    return RT_EOK;
}

static int dfs_romfs_stat(struct dfs_dentry *dentry, struct stat *st)
{
    rt_err_t ret = dfs_file_lock();
    if (ret == RT_EOK)
    {
        st->st_dev = 0;
        st->st_mode = dentry->vnode->mode;
        st->st_size = dentry->vnode->size;
        st->st_nlink = dentry->vnode->nlink;
        st->st_mtime = 0;

        dfs_file_unlock();
    }

    return RT_EOK;
}

static int dfs_romfs_getdents(struct dfs_file *file, struct dirent *dirp, uint32_t count)
{
    rt_size_t index;
    const char *name;
    struct dirent *d;
    struct romfs_dirent *dirent, *sub_dirent;

    dirent = (struct romfs_dirent *)file->vnode->data;
    if (check_dirent(dirent) != 0)
    {
        return -EIO;
    }
    RT_ASSERT(dirent->type == ROMFS_DIRENT_DIR);

    /* enter directory */
    dirent = (struct romfs_dirent *)dirent->data;

    /* make integer count */
    count = (count / sizeof(struct dirent));
    if (count == 0)
    {
        return -EINVAL;
    }

    index = 0;
    for (index = 0; index < count && file->fpos < file->vnode->size; index++)
    {
        d = dirp + index;

        sub_dirent = &dirent[file->fpos];
        name = sub_dirent->name;

        /* fill dirent */
        if (sub_dirent->type == ROMFS_DIRENT_DIR)
            d->d_type = DT_DIR;
        else
            d->d_type = DT_REG;

        d->d_namlen = rt_strlen(name);
        d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
        rt_strncpy(d->d_name, name, rt_strlen(name) + 1);

        /* move to next position */
        ++ file->fpos;
    }

    return index * sizeof(struct dirent);
}

static const struct dfs_file_ops _rom_fops =
{
    .open             = dfs_romfs_open,
    .close            = dfs_romfs_close,
    .lseek            = generic_dfs_lseek,
    .read             = dfs_romfs_read,
    .getdents         = dfs_romfs_getdents,
};

static const struct dfs_filesystem_ops _romfs_ops =
{
    .name             ="rom",
    .flags            = 0,
    .default_fops     = &_rom_fops,
    .mount            = dfs_romfs_mount,
    .umount           = dfs_romfs_umount,
    .stat             = dfs_romfs_stat,
    .lookup           = dfs_romfs_lookup,
    .free_vnode       = dfs_romfs_free_vnode
};

static struct dfs_filesystem_type _romfs =
{
    .fs_ops           = &_romfs_ops,
};

int dfs_romfs_init(void)
{
    /* register rom file system */
    dfs_register(&_romfs);

    return 0;
}
INIT_COMPONENT_EXPORT(dfs_romfs_init);
