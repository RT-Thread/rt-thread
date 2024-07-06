#define pr_fmt(fmt) "blkpart: " fmt

#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <blkpart.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <drv_sdmmc.h>

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define ALIGN_DOWN(x, a) __ALIGN_KERNEL((x) - ((a) - 1), (a))
#define __ALIGN_KERNEL(x, a) __ALIGN_KERNEL_MASK(x, (typeof(x))(a) - 1)
#define __ALIGN_KERNEL_MASK(x, mask) (((x) + (mask)) & ~(mask))

static struct blkpart *blk_head = NULL;

void blkpart_del_list(struct blkpart *blk)
{
    struct blkpart *pblk, *pre;

    if (!blk_head)
    {
        return;
    }

    pblk = pre = blk_head;
    for (pblk = blk_head; pblk; pre = pblk, pblk = pblk->next)
    {
        if (pblk == blk)
        {
            if (pblk == blk_head)
            {
                blk_head = NULL;
            }
            else
            {
                pre->next = pblk->next;
            }
            break;
        }
    }
}

void blkpart_add_list(struct blkpart *blk)
{
    struct blkpart *pblk, *pre;

    blk->next = NULL;

    if (!blk_head)
    {
        blk_head = blk;
        return;
    }

    pblk = pre = blk_head;
    while (pblk)
    {
        pre = pblk;
        pblk = pblk->next;
    }
    pre->next = blk;
}

void del_blkpart(struct blkpart *blk)
{
    int i;

    if (!blk)
    {
        return;
    }

    for (i = 0; i < blk->n_parts; i++)
    {
        struct part *part = &blk->parts[i];

        if (!part)
        {
            continue;
        }
    }

    blkpart_del_list(blk);
}

struct part *get_part_by_index(const char *blk_name, uint32_t index)
{
    struct blkpart *blk = blk_head;

    for (blk = blk_head; blk; blk = blk->next)
    {
        if (!strcmp(blk_name, blk->name))
        {
            if (index == 0)
            {
                return &blk->root;
            }
            else if (index == PARTINDEX_THE_LAST)
            {
                return &blk->parts[blk->n_parts - 1];
            }
            else if (blk->n_parts >= index)
            {
                return &blk->parts[index - 1];
            }
            else
            {
                return NULL;
            }
        }
    }
    return NULL;
}

#ifdef CONFIG_BLKPART_SHOW_INFO_CMD
static int part_info_main(int argc, char **argv)
{
    int i;
    struct blkpart *blk;
    struct part *part;

    for (blk = blk_head; blk; blk = blk->next)
    {
        for (i = 0; i < blk->n_parts; i++)
        {
            part = &blk->parts[i];
            printf("%s(%s): bytes 0x%llx off 0x%llx\n", part->name, part->devname,
                   part->bytes, part->off);
        }
    }

    return 0;
}
FINSH_FUNCTION_EXPORT_CMD(part_info_main, __cmd_part_info, dump nor partitions);
#endif

struct part *get_part_by_name(const char *name)
{
    struct blkpart *blk;

    if (!strncmp(name, "/dev/", sizeof("/dev/") - 1))
    {
        name += sizeof("/dev/") - 1;
    }

    for (blk = blk_head; blk; blk = blk->next)
    {
        int i;

        for (i = 0; i < blk->n_parts; i++)
        {
            struct part *part = &blk->parts[i];

            if (!strcmp(part->name, name))
            {
                return part;
            }

            if (!strcmp(part->devname, name))
            {
                return part;
            }
        }
    }
    return NULL;
}

struct blkpart *get_blkpart_by_name(const char *name)
{
    struct blkpart *blk;

    if (!name)
    {
        return blk_head;
    }

    for (blk = blk_head; blk; blk = blk->next)
    {
        if (!strcmp(blk->name, name))
        {
            return blk;
        }
    }
    return NULL;
}

rt_size_t part_read(rt_device_t dev, rt_off_t offset, void *data, rt_size_t size)
{
    if (size == 0)
    {
        return 0;
    }

    ssize_t ret, sz = 0;
    struct part *part = (struct part *)dev->user_data;
    struct blkpart *blk = part->blk;
    rt_device_t spinor_dev = blk->dev;
    size *= blk->blk_bytes;  /* sector to size */
    offset *= blk->blk_bytes;

    char *page_buf = NULL;

    if (offset >= part->bytes)
    {
        printf("read offset %lu over part size %lu\n", offset, part->bytes);
        return 0;
    }

    if (offset + size > part->bytes)
    {
        printf("read %s(%s) over limit: offset %lu + size %lu over %lu\n",
               part->name, part->devname, offset, size, part->bytes);
    }

    size = MIN(part->bytes - offset, size);
    pr_debug("read %s(%s) off 0x%x size %lu\n", part->name, part->devname,
             offset, size);

    offset += part->off;

    if (offset % blk->page_bytes || size % blk->page_bytes)
    {
        page_buf = malloc(blk->page_bytes);
        if (!page_buf)
        {
            return -ENOMEM;
        }
        memset(page_buf, 0, blk->page_bytes);
    }

    /**
     * Step 1:
     * read the beginning data that not align to block size
     */
    if (offset % blk->page_bytes)
    {
        uint32_t addr, poff, len;

        addr = ALIGN_DOWN(offset, blk->page_bytes);
        poff = offset - addr;
        len = MIN(blk->page_bytes - poff, size);

        pr_debug("offset %lu not align %u, fix them before align read\n",
                 offset, blk->blk_bytes);
        pr_debug("step1: read page data from addr 0x%x\n", addr);

        ret = rt_dev_read(spinor_dev, addr / blk->page_bytes, page_buf, blk->page_bytes / blk->page_bytes);
        ret *= blk->page_bytes;
        if (ret != blk->blk_bytes)
        {
            goto err;
        }

        pr_debug("step2: copy page data to buf with page offset 0x%x and len %u\n",
                 poff, len);
        memcpy(data, page_buf + poff, len);

        offset += len;
        data += len;
        sz += len;
        size -= len;
    }

    /**
     * Step 2:
     * read data that align to block size
     */
    while (size >= blk->page_bytes)
    {
        uint32_t len = (size/blk->page_bytes)*blk->page_bytes;

        ret = rt_dev_read(spinor_dev, offset / blk->blk_bytes, (char *)data, len / blk->blk_bytes);
        ret *= blk->page_bytes;
        if (ret != len)
        {
            goto err;
        }

        offset += len;
        data += len;
        sz += len;
        size -= len;
    }

    /**
     * Step 3:
     * read the last data that not align to block size
     */
    if (size)
    {
        pr_debug("last size %u not align %u, read them\n", size, blk->blk_bytes);

        pr_debug("step1: read page data from addr 0x%x\n", offset);
        ret = rt_dev_read(spinor_dev, offset / blk->blk_bytes, page_buf, blk->page_bytes / blk->page_bytes);
        ret *= blk->page_bytes;
        if (ret != blk->page_bytes)
        {
            goto err;
        }

        pr_debug("step2: copy page data to buf with page with len %u\n", size);
        memcpy(data, page_buf, size);
        sz += size;
    }

#ifdef DEBUG
    pr_debug("read data:\n");
    hexdump(data, sz);
#endif
    ret = 0;
    goto out;

err:
    pr_err("read failed - %d\n", (int)ret);
out:
    if (page_buf)
    {
        free(page_buf);
    }
    return ret ? ret / blk->blk_bytes: sz / blk->blk_bytes;
}

int do_write_without_erase(rt_device_t dev, struct blkpart *blk, uint32_t addr, uint32_t size, char *buf)
{
    return rt_dev_write(dev, addr, buf, size);
}
static int do_erase_write_blk(rt_device_t dev, struct blkpart *blk, uint32_t addr, uint32_t size, char *buf)
{
#if 0
    /* The code is prepared for elmfat which mounted at spinor */
    int ret;
    uint8_t *read_buf;
    unsigned int align_addr = ALIGN_DOWN(addr, blk->blk_bytes);

    read_buf = malloc(blk->blk_bytes);
    if (!read_buf)
    {
        return -ENOMEM;
    }
    memset(read_buf, 0, blk->blk_bytes);

    ret = dev->read(dev, align_addr, read_buf, blk->blk_bytes);
    if (ret != blk->blk_bytes)
    {
        free(read_buf);
        return -EIO;
    }

    if (!(align_addr % blk->blk_bytes))
    {
        blk_dev_erase_t erase_sector;
        memset(&erase_sector, 0, sizeof(blk_dev_erase_t));
        erase_sector.addr = align_addr;
        erase_sector.len = blk->blk_bytes;
        ret = rt_dev_control(dev, BLOCK_DEVICE_CMD_ERASE_SECTOR, &erase_sector);
        if (ret)
        {
            free(read_buf);
            return ret;
        }
    }

    memcpy(read_buf + (addr - align_addr), buf, blk->page_bytes);

    ret = rt_dev_write(dev, align_addr, read_buf, blk->blk_bytes);
    free(read_buf);
    if (ret == blk->blk_bytes)
    {
        return blk->page_bytes;
    }
    else
    {
        return -EIO;
    }
#else
    int ret = -1;

    blk_dev_erase_t erase_sector;
    memset(&erase_sector, 0, sizeof(blk_dev_erase_t));
    erase_sector.addr = addr;
    erase_sector.len = size;
    ret = rt_dev_control(dev, BLOCK_DEVICE_CMD_ERASE_SECTOR, &erase_sector);
    if (ret)
    {
        return -EIO;
    }

    ret = rt_dev_write(dev, addr, buf, size);
    if (ret == size)
    {
        return size;
    }
    else
    {
        return -EIO;
    }
#endif
}
rt_size_t _part_write(rt_device_t dev, rt_off_t offset, const void *data, rt_size_t size, int erase_before_write)
{
    ssize_t ret, sz = 0;
    struct part *part = (struct part *)dev->user_data;
    struct blkpart *blk = part->blk;
    rt_device_t spinor_dev = blk->dev;
    char *blk_buf = NULL;
    int (*pwrite)(rt_device_t dev, struct blkpart * blk, uint32_t addr, uint32_t size, char *buf);

    if (size == 0)
    {
        return 0;
    }
    size *= blk->blk_bytes;  /* sector to size */
    offset *= blk->blk_bytes;

    if (offset >= part->bytes)
    {
        printf("write offset %lu over part size %lu\n", offset, part->bytes);
        return 0;
    }

    if (offset + size > part->bytes)
    {
        printf("write %s(%s) over limit: offset %lu + size %lu over %lu\n",
               part->name, part->devname, offset, size, part->bytes);
    }

    size = MIN(part->bytes - offset, size);
    pr_debug("write %s(%s) off 0x%x size %lu (erase %d)\n", part->name,
             part->devname, offset, size, erase_before_write);
    offset += part->off;

    if (offset % blk->blk_bytes || size % blk->blk_bytes)
    {
        blk_buf = malloc(blk->blk_bytes);
        if (!blk_buf)
        {
            return -ENOMEM;
        }
        memset(blk_buf, 0, blk->blk_bytes);
    }

    if (erase_before_write)
    {
        pwrite = do_erase_write_blk;
    }
    else
    {
        pwrite = do_write_without_erase;
    }

    /**
     * Step 1:
     * write the beginning data that not align to block size
     */
    if (offset % blk->blk_bytes)
    {
        uint32_t addr, poff, len;

        addr = ALIGN_DOWN(offset, blk->blk_bytes);
        poff = offset - addr;
        len = MIN(blk->blk_bytes - poff, size);

        pr_debug("offset %u not align %u, fix them before align write\n",
                 offset, blk->blk_bytes);
        pr_debug("step1: read page data from addr 0x%x\n", addr);
        ret = rt_dev_read(spinor_dev, addr / blk->blk_bytes, blk_buf, blk->blk_bytes / blk->blk_bytes);
        ret *= blk->blk_bytes;
        if (ret != blk->blk_bytes)
        {
            goto err;
        }

        /* addr must less or equal to address */
        pr_debug("step2: copy buf data to page data with page offset 0x%x and len %u\n",
                 poff, len);
        memcpy(blk_buf + poff, data, len);

        pr_debug("step3: flush the fixed page data\n");
        ret = pwrite(spinor_dev, blk, addr / blk->blk_bytes, blk->blk_bytes / blk->blk_bytes, blk_buf);
        ret *= blk->blk_bytes;
        if (ret != blk->blk_bytes)
        {
            goto err;
        }

        offset += len;
        data += len;
        sz += len;
        size -= len;
    }
    while (size >= blk->blk_bytes)
    {
        uint32_t len = (size/blk->blk_bytes)*blk->blk_bytes;
        ret = pwrite(spinor_dev, blk, offset / blk->blk_bytes, len / blk->blk_bytes, (char *)data);
        ret *= blk->blk_bytes;
        if (ret != len)
        {
            goto err;
        }

        offset += len;
        data += len;
        sz += len;
        size -= len;
    }

    if (size)
    {
        pr_debug("last size %u not align %u, write them\n", size, blk->blk_bytes);

        pr_debug("step1: read page data from addr 0x%x\n", offset);
        memset(blk_buf, 0x00, sizeof(blk->blk_bytes));
        ret = rt_dev_read(spinor_dev, offset / blk->blk_bytes, blk_buf, blk->blk_bytes);
        if (ret != blk->blk_bytes)
        {
            goto err;
        }

        pr_debug("step2: copy buf to page data with page with len %u\n", size);
        memcpy(blk_buf, data, size);

        pr_debug("step3: flush the fixed page data\n");
        ret = pwrite(spinor_dev, blk, offset / blk->blk_bytes, blk->blk_bytes / blk->blk_bytes, blk_buf);
        ret *= blk->blk_bytes;
        if (ret != blk->blk_bytes)
        {
            goto err;
        }
        sz += size;
    }
#ifdef DEBUG
    pr_debug("write data:\n");
    hexdump(data, sz);
#endif
    ret = 0;
    goto out;

err:
    pr_err("write failed - %d\n", (int)ret);
out:

    if (blk_buf)
    {
        free(blk_buf);
    }
    return ret ? ret / blk->blk_bytes: sz / blk->blk_bytes;
}
rt_size_t part_erase_before_write(rt_device_t dev, rt_off_t offset, const void *data, rt_size_t size)
{
    return _part_write(dev, offset, data, size, 1);
}

rt_size_t part_erase_without_write(rt_device_t dev, rt_off_t offset, const void *data, rt_size_t size)
{
    return _part_write(dev, offset, data, size, 0);
}

rt_err_t part_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t ret = -1;
    struct part *part = (struct part *)dev->user_data;
    struct blkpart *blk = part->blk;
    rt_device_t spinor_dev = blk->dev;
    struct rt_device_blk_geometry *geometry = NULL;

    blk_dev_erase_t *erase_sector = (blk_dev_erase_t *)args;

    switch (cmd)
    {
        case DEVICE_PART_CMD_ERASE_SECTOR:
            erase_sector = (blk_dev_erase_t *)(args);

            if (erase_sector->addr + erase_sector->len > part->bytes)
            {
                printf("erase %s(%s) over limit: offset %u + size %u over %lu\n",
                        part->name, part->devname, erase_sector->addr, erase_sector->len, part->bytes);
            }

            erase_sector->len = MIN(part->bytes - erase_sector->addr, erase_sector->len);
            erase_sector->addr = erase_sector->addr + part->off;

            if (spinor_dev && rt_dev_has_control(spinor_dev))
            {
                ret = rt_dev_control(spinor_dev, BLOCK_DEVICE_CMD_ERASE_SECTOR, erase_sector);
            }
            break;
        case DEVICE_PART_CMD_GET_BLOCK_SIZE:
            if (spinor_dev && rt_dev_has_control(spinor_dev))
            {
                ret = rt_dev_control(spinor_dev, BLOCK_DEVICE_CMD_GET_BLOCK_SIZE, args);
            }
            else
            {
                ret = -1;
            }
            break;
        case DEVICE_PART_CMD_GET_TOTAL_SIZE:
            *(unsigned int *)args = part->bytes;
            ret = 0;
            break;
        case RT_DEVICE_CTRL_BLK_GETGEOME:
            geometry = (struct rt_device_blk_geometry *)args;
            memset(geometry, 0, sizeof(struct rt_device_blk_geometry));
            if (spinor_dev && rt_dev_has_control(spinor_dev))
            {
                ret = rt_dev_control(spinor_dev, RT_DEVICE_CTRL_BLK_GETGEOME, args);
                if (!ret)
                {
                    geometry->sector_count = part->bytes / geometry->bytes_per_sector;
                    ret = 0;
                }
            }

            break;
        case RT_DEVICE_CTRL_BLK_ERASE:
            ret = 0;
            break;
        default:
            break;
    }

    return ret;
}

