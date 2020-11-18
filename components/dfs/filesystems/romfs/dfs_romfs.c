/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>

#include "dfs_romfs.h"

int dfs_romfs_mount(struct dfs_filesystem *fs, unsigned long rwflag, const void *data)
{
    struct root_data *root_data;

    if (data == NULL)
        return -EIO;

    root_data = (struct root_data *)rt_malloc(sizeof(struct root_data));
    if (root_data)
    {
        int size = sizeof(struct romfs_dirent);
        root_data->dirent = (struct romfs_dirent *)data;
        if ((const char *)root_data->dirent->data - root_data->dirent->name != 0x04)
            root_data->offset = 0;
        else
            root_data->offset = (int)root_data->dirent->name != size ? ((long long)data - (long long)root_data->dirent->name + size) : (long long)data;
        fs->data = root_data;
    }
    else
    {
        return -RT_ENOMEM;
    }

    return RT_EOK;
}

int dfs_romfs_unmount(struct dfs_filesystem *fs)
{
    if (fs->data)
    {
        rt_free(fs->data);
    }

    return RT_EOK;
}

int dfs_romfs_ioctl(struct dfs_fd *file, int cmd, void *args)
{
    return -EIO;
}

rt_inline int check_dirent(struct romfs_dirent *dirent)
{
    if ((dirent->type != ROMFS_DIRENT_FILE && dirent->type != ROMFS_DIRENT_DIR)
        || dirent->size == ~0)
        return -1;
    return 0;
}

struct romfs_dirent *dfs_romfs_lookup(struct root_data *root_data, const char *path, rt_size_t *size)
{
    rt_size_t index, found;
    const char *subpath, *subpath_end;
    struct romfs_dirent *dirent;
    rt_size_t dirent_size;

    /* Check the root_dirent. */
    if (check_dirent(root_data->dirent) != 0)
        return NULL;

    if (path[0] == '/' && path[1] == '\0')
    {
        *size = root_data->dirent->size;
        return root_data->dirent;
    }

    /* goto root directy entries */
    dirent = (struct romfs_dirent *)(root_data->dirent->data + root_data->offset);
    dirent_size = root_data->dirent->size;

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
            if (rt_strlen(dirent[index].name + root_data->offset) == (subpath_end - subpath) &&
                    rt_strncmp(dirent[index].name + root_data->offset, subpath, (subpath_end - subpath)) == 0)
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
                    dirent = (struct romfs_dirent *)(dirent[index].data + root_data->offset);
                    found = 1;
                    break;
                }
                else
                {
                    /* return file dirent */
                    if (subpath != NULL)
                        break; /* not the end of path */

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

int dfs_romfs_read(struct dfs_fd *file, void *buf, size_t count)
{
    rt_size_t length;
    struct romfs_dirent *dirent;
    struct root_data *root_data;

    root_data = (struct root_data *)file->fs->data;
    dirent = (struct romfs_dirent *)file->data;
    RT_ASSERT(dirent != NULL);

    if (check_dirent(dirent) != 0)
    {
        return -EIO;
    }

    if (count < file->size - file->pos)
        length = count;
    else
        length = file->size - file->pos;

    if (length > 0)
        memcpy(buf, &(dirent->data[file->pos]) + root_data->offset, length);

    /* update file current position */
    file->pos += length;

    return length;
}

int dfs_romfs_lseek(struct dfs_fd *file, off_t offset)
{
    if (offset <= file->size)
    {
        file->pos = offset;
        return file->pos;
    }

    return -EIO;
}

int dfs_romfs_close(struct dfs_fd *file)
{
    file->data = NULL;
    return RT_EOK;
}

int dfs_romfs_open(struct dfs_fd *file)
{
    rt_size_t size;
    struct romfs_dirent *dirent;
    struct root_data *root_data;

    root_data = (struct root_data *)file->fs->data;

    if (check_dirent(root_data->dirent) != 0)
        return -EIO;

    if (file->flags & (O_CREAT | O_WRONLY | O_APPEND | O_TRUNC | O_RDWR))
        return -EINVAL;

    dirent = dfs_romfs_lookup(root_data, file->path, &size);
    if (dirent == NULL)
        return -ENOENT;

    /* entry is a directory file type */
    if (dirent->type == ROMFS_DIRENT_DIR)
    {
        if (!(file->flags & O_DIRECTORY))
            return -ENOENT;
    }
    else
    {
        /* entry is a file, but open it as a directory */
        if (file->flags & O_DIRECTORY)
            return -ENOENT;
    }

    file->data = dirent;
    file->size = size;
    file->pos = 0;

    return RT_EOK;
}

int dfs_romfs_stat(struct dfs_filesystem *fs, const char *path, struct stat *st)
{
    rt_size_t size;
    struct romfs_dirent *dirent;
    struct root_data *root_data;

    root_data = (struct root_data *)fs->data;
    dirent = dfs_romfs_lookup(root_data, path, &size);

    if (dirent == NULL)
        return -ENOENT;

    st->st_dev = 0;
    st->st_mode = S_IFREG | S_IRUSR | S_IRGRP | S_IROTH |
                  S_IWUSR | S_IWGRP | S_IWOTH;

    if (dirent->type == ROMFS_DIRENT_DIR)
    {
        st->st_mode &= ~S_IFREG;
        st->st_mode |= S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;
    }

    st->st_size = dirent->size;
    st->st_mtime = 0;

    return RT_EOK;
}

int dfs_romfs_getdents(struct dfs_fd *file, struct dirent *dirp, uint32_t count)
{
    rt_size_t index;
    const char *name;
    struct dirent *d;
    struct romfs_dirent *dirent, *sub_dirent;
    struct root_data *root_data;

    root_data = (struct root_data *)file->fs->data;
    dirent = (struct romfs_dirent *)file->data;
    if (check_dirent(dirent) != 0)
        return -EIO;
    RT_ASSERT(dirent->type == ROMFS_DIRENT_DIR);

    /* enter directory */
    dirent = (struct romfs_dirent *)(dirent->data + root_data->offset);

    /* make integer count */
    count = (count / sizeof(struct dirent));
    if (count == 0)
        return -EINVAL;

    index = 0;
    for (index = 0; index < count && file->pos < file->size; index ++)
    {
        d = dirp + index;

        sub_dirent = &dirent[file->pos];
        name = sub_dirent->name + root_data->offset;

        /* fill dirent */
        if (sub_dirent->type == ROMFS_DIRENT_DIR)
            d->d_type = DT_DIR;
        else
            d->d_type = DT_REG;

        d->d_namlen = rt_strlen(name);
        d->d_reclen = (rt_uint16_t)sizeof(struct dirent);
        rt_strncpy(d->d_name, name, rt_strlen(name) + 1);

        /* move to next position */
        ++ file->pos;
    }

    return index * sizeof(struct dirent);
}

void *dfs_romfs_get(struct dfs_fd *file)
{
    struct root_data *root_data = (struct root_data *)file->fs->data;
    struct romfs_dirent *dirent = (struct romfs_dirent *)file->data;
    if (dirent)
    {
        return (void *)(&dirent->data[file->pos] + root_data->offset);
    }

    return RT_NULL;
}

static const struct dfs_file_ops _rom_fops =
{
    dfs_romfs_open,
    dfs_romfs_close,
    dfs_romfs_ioctl,
    dfs_romfs_read,
    NULL,
    NULL,
    dfs_romfs_lseek,
    dfs_romfs_getdents,
};
static const struct dfs_filesystem_ops _romfs =
{
    "rom",
    DFS_FS_FLAG_DEFAULT,
    &_rom_fops,

    dfs_romfs_mount,
    dfs_romfs_unmount,
    NULL,
    NULL,

    NULL,
    dfs_romfs_stat,
    NULL,
};

int dfs_romfs_init(void)
{
    /* register rom file system */
    dfs_register(&_romfs);
    return 0;
}
INIT_COMPONENT_EXPORT(dfs_romfs_init);

