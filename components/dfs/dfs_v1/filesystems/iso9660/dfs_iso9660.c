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

#define DBG_TAG "dfs.iso9660"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "dfs_iso9660.h"
#include <dfs.h>
#include <dfs_fs.h>
#include <dfs_file.h>
#include <drivers/misc.h>
#include <drivers/byteorder.h>

#include <sys/time.h>

#define ISO9660_FSTYPE_DIR      0040000
#define ISO9660_FSTYPE_REG      0100000
#define ISO9660_FSTYPE_SYMLINK  0120000
#define ISO9660_FSTYPE_MASK     0170000

#define ISO9660_BLKSZ           2048

#define ISO9660_VOLDESC_BOOT    0
#define ISO9660_VOLDESC_PRIMARY 1
#define ISO9660_VOLDESC_SUPP    2
#define ISO9660_VOLDESC_PART    3
#define ISO9660_VOLDESC_END     255

rt_packed(struct iso9660_voldesc
{
    rt_uint8_t type;
    rt_uint8_t magic[5];
    rt_uint8_t version;
});

rt_packed(struct iso9660_date2
{
    rt_uint8_t year;
    rt_uint8_t month;
    rt_uint8_t day;
    rt_uint8_t hour;
    rt_uint8_t minute;
    rt_uint8_t second;
    rt_uint8_t offset;
});

/* Directory entry */
rt_packed(struct iso9660_dir
{
    rt_uint8_t len;
    rt_uint8_t ext_sectors;
    rt_le32_t first_sector;
    rt_le32_t first_sector_be;
    rt_le32_t size;
    rt_le32_t size_be;
    struct iso9660_date2 mtime;
#define FLAG_TYPE_PLAIN     0
#define FLAG_TYPE_DIR       2
#define FLAG_TYPE           3
#define FLAG_MORE_EXTENTS   0x80
    rt_uint8_t flags;
    rt_uint8_t file_unit_size;
    rt_uint8_t interleave_gap_size;
    rt_le16_t vol_seq_num;
    rt_le16_t vol_seq_num_be;
#define MAX_NAMELEN 255
    rt_uint8_t namelen;
    char name[0];
});

rt_packed(struct iso9660_date
{
    rt_uint8_t year[4];
    rt_uint8_t month[2];
    rt_uint8_t day[2];
    rt_uint8_t hour[2];
    rt_uint8_t minute[2];
    rt_uint8_t second[2];
    rt_uint8_t hundredth[2];
    rt_uint8_t offset;
});

/* Common volume descriptor */
rt_packed(struct iso9660_common_voldesc
{
    struct iso9660_voldesc voldesc;
    rt_uint8_t sysname[33];
    rt_uint8_t volname[32];
    rt_uint8_t unused2[8];
    rt_le32_t vol_space_size_le;
    rt_le32_t vol_space_size_be;
    rt_uint8_t escape[32];
    rt_le16_t vol_set_size_le;
    rt_le16_t vol_set_size_be;
    rt_le16_t vol_seq_num_le;
    rt_le16_t vol_seq_num_be;
    rt_le16_t logical_block_size_le;
    rt_le16_t logical_block_size_be;
    rt_le32_t path_table_size;
    rt_le32_t path_table_size_be;
    rt_le32_t path_table;
    rt_le32_t path_table_be;
    rt_uint8_t unused3[8];
    struct iso9660_dir rootdir;
    rt_uint8_t unused4[624];
    struct iso9660_date created;
    struct iso9660_date modified;
    rt_uint8_t unused5[0 /* 1201 */];
};

struct iso9660
{
    struct rt_device *dev;

    rt_uint8_t joliet;
    rt_uint8_t swap[ISO9660_BLKSZ];

    struct iso9660_common_voldesc primary, supp;
};

struct iso9660_fd
{
    struct iso9660 *iso;

    struct iso9660_dir dirent;
};

struct iso9660_iterate
{
    struct iso9660_fd *fd;

    int i, index, count;
    struct dirent *dirp;
};

static void iso9660_convert_string(char *dest, rt_uint16_t *src, int len)
{
    /* UTF16 to ASCII */
    len >>= 1;

    for (int i = 0; i < len; ++i)
    {
        rt_uint16_t utf16 = rt_be16_to_cpu(*src++);

        if (utf16 < 0x80)
        {
            *dest++ = (rt_uint8_t)utf16;
        }
        else
        {
            *dest++ = '?';
        }
    }
    *dest = '\0';
}

static void iso9660_convert_lower(char *dest, rt_uint8_t *src, int len)
{
    for (int i = 0; i < len; ++i, ++src)
    {
        if (*src >= 'A' && *src <= 'Z')
        {
            *dest++ = *src - ('A' - 'a');
        }
        else
        {
            *dest++ = *src;
        }
    }

    *dest = '\0';
}

static time_t iso9660_convert_unixtime(struct iso9660_date *date)
{
    struct tm tm;

    tm.tm_sec  = (date->second[0] - '0') * 10 + (date->second[1] - '0');
    tm.tm_min  = (date->minute[0] - '0') * 10 + (date->minute[1] - '0');
    tm.tm_hour = (date->hour[0] - '0') * 10 + (date->hour[1] - '0');
    tm.tm_mday = (date->day[0] - '0') * 10 + (date->day[1] - '0');
    tm.tm_mon  = (date->month[0] - '0') * 10 + (date->month[1] - '0');
    tm.tm_year = (date->year[0] - '0') * 1000 + (date->year[1] - '0') * 100 +
                 (date->year[2] - '0') * 10 + (date->year[3] - '0');
    tm.tm_wday = 0;

    return mktime(&tm);
}

static time_t iso9660_convert_unixtime2(struct iso9660_date2 *date)
{
    struct tm tm;

    tm.tm_sec  = date->second;
    tm.tm_min  = date->minute;
    tm.tm_hour = date->hour;
    tm.tm_mday = date->day;
    tm.tm_mon  = date->month;
    tm.tm_year = date->year + 1900;
    tm.tm_wday = 0;

    return mktime(&tm);
}

static struct iso9660_fd *iso9660_lookup(struct iso9660 *iso, const char *path,
        struct iso9660_iterate *it)
{
    rt_uint32_t lba;
    rt_size_t sz, len, namelen;
    char sname[MAX_NAMELEN];
    struct iso9660_fd *fd;
    struct iso9660_dir *dirent;

    if (it)
    {
        fd = it->fd;
        iso = fd->iso;
        dirent = &fd->dirent;

        /* No next entry, always goon */
        len = 1;
    }
    else
    {
        if (!(fd = rt_malloc(sizeof(*fd))))
        {
            return fd;
        }

        fd->iso = iso;
        dirent = iso->joliet ? &iso->supp.rootdir : &iso->primary.rootdir;

        if (!rt_strcmp(path, "/"))
        {
            rt_memcpy(&fd->dirent, dirent, sizeof(*dirent));
            return fd;
        }

        /* Skip the first '/' */
        ++path;
        len = rt_strchrnul(path, '/') - path;
    }

    lba = rt_le32_to_cpu(dirent->first_sector);
    if (rt_device_read(iso->dev, lba, iso->swap, 1) <= 0)
    {
        goto _fail;
    }
    dirent = (void *)iso->swap;
    sz = 0;

    do {
        /* Ignore "." and ".." */
        do {
            rt_uint32_t dlen = rt_le32_to_cpu(dirent->len);

            dirent = (void *)dirent + dlen;
            sz += dlen;

            if (ISO9660_BLKSZ - sz < sizeof(*dirent))
            {
                /* Sector end, goto the next sector */
                if (rt_device_read(iso->dev, ++lba, iso->swap, 1) <= 0)
                {
                    goto _fail;
                }
                dirent = (void *)iso->swap;
                sz = 0;
            }

            if (rt_le32_to_cpu(dirent->first_sector) == 0)
            {
                /* Is end, no found. */
                goto _fail;
            }
        } while (dirent->name[0] >> 1 == 0 && rt_le32_to_cpu(dirent->namelen) == 1);

        namelen = rt_le32_to_cpu(dirent->namelen);

        if (iso->joliet)
        {
            iso9660_convert_string(sname, (rt_uint16_t *)dirent->name, namelen);
        }
        else
        {
            if (!(rt_le32_to_cpu(dirent->flags) & FLAG_TYPE_DIR))
            {
                /* Remove ";1" */
                namelen -= 2;
            }

            iso9660_convert_lower(sname, (rt_uint8_t *)dirent->name, namelen);
        }

        if (it)
        {
            if (it->i < it->index)
            {
                goto _next;
            }

            if ((rt_le32_to_cpu(dirent->flags) & FLAG_TYPE) == FLAG_TYPE_DIR)
            {
                it->dirp->d_type = DT_DIR;
            }
            else
            {
                it->dirp->d_type = DT_REG;
            }

            it->dirp->d_namlen = namelen;
            rt_strncpy(it->dirp->d_name, sname, namelen);
            it->dirp->d_name[namelen] = '\0';
            it->dirp->d_reclen = (rt_uint16_t)sizeof(struct dirent);

            ++it->dirp;

        _next:
            ++it->i;

            if (it->i - it->index >= it->count)
            {
                /* Iterate end */
                return RT_NULL;
            }

            /* No next entry */
            continue;
        }

        if (!rt_strncmp(sname, path, len))
        {
            /* The end of path, found ok */
            if (!path[len])
            {
                rt_memcpy(&fd->dirent, dirent, sizeof(*dirent));
                return fd;
            }

            /* Next entry */
            lba = rt_le32_to_cpu(dirent->first_sector);
            if (rt_device_read(iso->dev, lba, iso->swap, 1) <= 0)
            {
                goto _fail;
            }
            dirent = (void *)iso->swap;
            sz = 0;

            path += len + 1;
            len = rt_strchrnul(path, '/') - path;
        }
    } while (len);

_fail:
    if (!it)
    {
        rt_free(fd);
    }

    return RT_NULL;
}

static int dfs_iso9660_open(struct dfs_file *fd)
{
    struct iso9660 *iso = fd->vnode->fs->data;

    fd->vnode->data = iso9660_lookup(iso, fd->vnode->path, RT_NULL);

    return fd->vnode->data ? 0 : -EINVAL;
}

static int dfs_iso9660_close(struct dfs_file *fd)
{
    struct iso9660_fd *iso_fd = fd->vnode->data;

    rt_free(iso_fd);

    return 0;
}

static int dfs_iso9660_read(struct dfs_file *fd, void *buf, size_t count)
{
    rt_uint32_t pos;
    void *buf_ptr;
    ssize_t read_blk, toread_blk;
    size_t rcount = 0, remain, size;
    struct iso9660_fd *iso_fd = fd->vnode->data;
    struct iso9660 *iso = iso_fd->iso;

    if (fd->pos + count > rt_le32_to_cpu(iso_fd->dirent.size))
    {
        count = rt_le32_to_cpu(iso_fd->dirent.size) - fd->pos;
    }
    pos = rt_le32_to_cpu(iso_fd->dirent.first_sector);

    /* Align to a sector */
    if (fd->pos)
    {
        pos += fd->pos / ISO9660_BLKSZ;
        remain = fd->pos & (ISO9660_BLKSZ - 1);

        if (rt_device_read(iso->dev, pos, iso->swap, 1) <= 0)
        {
            return -EIO;
        }

        size = rt_min_t(size_t, ISO9660_BLKSZ - remain, count);
        rt_memcpy(buf, &iso->swap[remain], size);
        rcount += size;
        count -= size;
        buf += size;
        pos += 1;
        fd->pos += size;

        if (!count)
        {
            goto _end;
        }
    }

    remain = count & (ISO9660_BLKSZ - 1);
    count = rt_max_t(size_t, count / ISO9660_BLKSZ, 1);

    while ((ssize_t)count > 0)
    {
        if (count == 1)
        {
            buf_ptr = iso->swap;
            toread_blk = 1;
        }
        else
        {
            buf_ptr = buf;
            toread_blk = count;
        }

        read_blk = rt_device_read(iso->dev, pos, buf_ptr, toread_blk);

        if (read_blk <= 0)
        {
            return (int)read_blk;
        }

        if (count == 1)
        {
            size = remain;
            rt_memcpy(buf, iso->swap, size);
        }
        else
        {
            size = read_blk * ISO9660_BLKSZ;
        }

        rcount += size;
        count -= read_blk;
        buf += size;
        pos += read_blk;
        fd->pos += size;
    }

_end:
    return rcount;
}

static int dfs_iso9660_lseek(struct dfs_file *fd, off_t offset)
{
    int ret = -EIO;

    if (offset <= fd->vnode->size)
    {
        fd->pos = offset;
        ret = fd->pos;
    }

    return ret;
}

static int dfs_iso9660_getdents(struct dfs_file *fd, struct dirent *dirp, uint32_t count)
{
    struct iso9660_iterate it;
    struct iso9660_fd *iso_fd = fd->vnode->data;

    count = (count / sizeof(struct dirent));

    if (!count)
    {
        return -EINVAL;
    }

    it.fd = iso_fd;
    it.i = 0;
    it.index = fd->pos;
    it.count = count;
    it.dirp = dirp;

    iso9660_lookup(RT_NULL, RT_NULL, &it);

    count = it.i - it.index;
    if (count > 0)
    {
        fd->pos += count;
    }

    count *= sizeof(struct dirent);

    return count;
}

static const struct dfs_file_ops _iso9660_fops =
{
    .open       = dfs_iso9660_open,
    .close      = dfs_iso9660_close,
    .read       = dfs_iso9660_read,
    .lseek      = dfs_iso9660_lseek,
    .getdents   = dfs_iso9660_getdents,
};

static int dfs_iso9660_mount(struct dfs_filesystem *fs,
        unsigned long rwflag, const void *data)
{
    int err;
    struct iso9660 *iso;
    struct iso9660_voldesc *voldesc;
    struct rt_device_blk_geometry geometry;

    if (!(iso = rt_malloc(sizeof(*iso))))
    {
        return -RT_ENOMEM;
    }

    iso->dev = fs->dev_id;
    rt_device_control(iso->dev, RT_DEVICE_CTRL_BLK_GETGEOME, &geometry);

    if (geometry.bytes_per_sector != ISO9660_BLKSZ)
    {
        LOG_E("%s: Logical block size = %d is not supported",
                iso->dev->parent.name, geometry.bytes_per_sector);

        err = -EINVAL;
        goto _fail;
    }

    iso->primary.rootdir.first_sector = 0;
    iso->supp.rootdir.first_sector = 0;

    /* LBA 0-15 is the bootloader's information */
    for (int lba = 16; ; ++lba)
    {
        if (rt_device_read(iso->dev, lba, &iso->swap, 1) <= 0)
        {
            err = -EIO;
            goto _fail;
        }

        voldesc = (void *)iso->swap;

        if (rt_strncmp((char *)voldesc->magic, "CD001", 5))
        {
            LOG_E("%s: Invalid magic \"%s\"", voldesc->magic);

            err = -EINVAL;
            goto _fail;
        }

        if (voldesc->type == ISO9660_VOLDESC_BOOT)
        {
            LOG_D("System Name: %s", ((struct iso9660_common_voldesc *)voldesc)->sysname);
            LOG_D("Volume Name: %s", ((struct iso9660_common_voldesc *)voldesc)->volname);
        }
        else if (voldesc->type == ISO9660_VOLDESC_PRIMARY)
        {
            iso->joliet = 0;
            rt_memcpy(&iso->primary, &iso->swap, sizeof(iso->primary));
        }
        else if (voldesc->type == ISO9660_VOLDESC_SUPP)
        {
            rt_memcpy(&iso->supp, &iso->swap, sizeof(iso->supp));

            if (iso->supp.escape[0] == 0x25 && iso->supp.escape[1] == 0x2f)
            {
                if (iso->supp.escape[2] == 0x40)
                {
                    iso->joliet = 1;
                }
                else if (iso->supp.escape[2] == 0x43)
                {
                    iso->joliet = 2;
                }
                else if (iso->supp.escape[2] == 0x45)
                {
                    iso->joliet = 3;
                }
                else
                {
                    continue;
                }
            }
        }
        else if (voldesc->type == ISO9660_VOLDESC_PART)
        {
            LOG_D("System Name: %s", ((struct iso9660_common_voldesc *)voldesc)->sysname);
            LOG_D("Volume Name: %s", ((struct iso9660_common_voldesc *)voldesc)->volname);
        }
        else if (voldesc->type == ISO9660_VOLDESC_END)
        {
            break;
        }
    }

    if (!iso->primary.rootdir.first_sector || !iso->supp.rootdir.first_sector)
    {
        LOG_E("No primary or secondary partition found");

        err = -EINVAL;
        goto _fail;
    }

    fs->data = iso;

    return 0;

_fail:
    rt_free(iso);

    return err;
}

static int dfs_iso9660_unmount(struct dfs_filesystem *fs)
{
    struct iso9660 *iso = fs->data;

    rt_free(iso);

    return 0;
}

static int dfs_iso9660_stat(struct dfs_filesystem *fs,
        const char *filename, struct stat *st)
{
    struct iso9660 *iso = fs->data;
    struct iso9660_fd *fd = iso9660_lookup(iso, filename, RT_NULL);

    if (!fd)
    {
        return -EINVAL;
    }

    st->st_dev = 0;
    st->st_mode = S_IFREG | S_IRUSR | S_IRGRP | S_IROTH |
        S_IWUSR | S_IWGRP | S_IWOTH;

    if ((fd->dirent.flags & FLAG_TYPE) == FLAG_TYPE_DIR)
    {
        st->st_mode &= ~S_IFREG;
        st->st_mode |= S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH;
    }

    st->st_atime = iso9660_convert_unixtime(iso->joliet ?
            &iso->supp.created : &iso->primary.created);
    st->st_mtime = iso9660_convert_unixtime2(&fd->dirent.mtime);
    st->st_size = rt_le32_to_cpu(fd->dirent.size);

    rt_free(fd);

    return 0;
}

static const struct dfs_filesystem_ops _iso9660 =
{
    .name       = "iso9660",
    .flags      = DFS_FS_FLAG_DEFAULT,
    .fops       = &_iso9660_fops,

    .mount      = dfs_iso9660_mount,
    .unmount    = dfs_iso9660_unmount,

    .stat       = dfs_iso9660_stat,
};

int dfs_iso9660_init(void)
{
    /* register iso9660 file system */
    return dfs_register(&_iso9660);
}
INIT_COMPONENT_EXPORT(dfs_iso9660_init);
