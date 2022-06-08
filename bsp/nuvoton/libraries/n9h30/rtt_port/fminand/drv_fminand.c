/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-5-22       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#define BSP_USING_FMINAND

#if defined(BSP_USING_FMINAND)

#include "drivers/mtd_nand.h"
#include "board.h"
#include "drv_fminand.h"

#define LOG_TAG                 "drv_fminand"
#define DBG_ENABLE
#define DBG_SECTION_NAME        LOG_TAG
#define DBG_LEVEL               DBG_ERROR
#define DBG_COLOR
#include <rtdbg.h>

#define    DEF_BLOCKPERFLASH    1024
#define    DEF_PAGEPERBLOCK     128
#define    DEF_PAGESIZE         2048
#define    DEF_OOBSIZE          64

#include "nand.h"

struct nu_fminand
{
    struct nand_chip nandchip;
    struct rt_mutex  lock;
};
typedef struct nu_fminand *nu_fminand_t;

static struct nu_fminand s_nu_fminand = {0};
#define FMINAND_FLASH_LOCK   (&s_nu_fminand.lock)
#define FMINAND_NAND_CHIP    (&s_nu_fminand.nandchip)
#define FMINAND_MTD_INFO     (&s_nu_fminand.nandchip.mtd)

static void nu_fminand_dump_buffer(int page, rt_uint8_t *buf, int len, const char *title)
{
    int i;

    if (!buf)
    {
        return;
    }

    /* Just print 64-bytes.*/
    len = (len < 64) ? len : 64;

    LOG_I("[%s-Page-%d]", title, page);

    for (i = 0; i < len; i ++)
    {
        rt_kprintf("%02X ", buf[i]);
        if (i % 32 == 31) rt_kprintf("\n");
    }
    rt_kprintf("\n");
}

static rt_err_t nu_fminand_read_id(struct rt_mtd_nand_device *device)
{
    rt_err_t result = RT_EOK ;
    int maf_id, dev_id;
    struct nand_flash_dev *type = NULL;

    result = rt_mutex_take(FMINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    extern struct nand_flash_dev *nand_get_flash_type(struct mtd_info * mtd,
            struct nand_chip * chip, int *maf_id, int *dev_id, struct nand_flash_dev * type);
    extern struct nand_flash_dev nand_flash_ids[];

    type = nand_get_flash_type(FMINAND_MTD_INFO, FMINAND_NAND_CHIP, &maf_id, &dev_id, &nand_flash_ids[0]);

    result = rt_mutex_release(FMINAND_FLASH_LOCK);
    RT_ASSERT(result == RT_EOK);

    return (type != NULL) ? RT_EOK : -RT_ERROR;
}

static rt_err_t nu_fminand_read_page(struct rt_mtd_nand_device *device,
                                     rt_off_t page,
                                     rt_uint8_t *data,
                                     rt_uint32_t data_len,
                                     rt_uint8_t *spare,
                                     rt_uint32_t spare_len)
{
    rt_err_t result = RT_EOK ;

    LOG_I("[R-%d]data: 0x%08x %d, spare: 0x%08x, %d", page, data, data_len, spare, spare_len);

    RT_ASSERT(device);

    if (page / device->pages_per_block > device->block_end)
    {
        LOG_E("[EIO] read page:%d", page);
        return -RT_MTD_EIO;
    }

    result = rt_mutex_take(FMINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    if (data && data_len)
    {
        int ret = nand_read_skip_bad(FMINAND_MTD_INFO, FMINAND_MTD_INFO->writesize * page, &data_len, NULL, FMINAND_MTD_INFO->size, (u_char *)data);
        //int ret = nand_read(FMINAND_MTD_INFO, FMINAND_MTD_INFO->writesize*page, &data_len, (u_char *)data);
        if (ret != 0)
        {
            result = -RT_ERROR;
            goto exit_nu_fminand_read_page;
        }
    }

//    if (spare && spare_len)
//    {
//        if (result != RT_EOK)
//            goto exit_nu_fminand_read_page;
//    }


exit_nu_fminand_read_page:

    rt_mutex_release(FMINAND_FLASH_LOCK);

    return result;
}

static rt_err_t nu_fminand_write_page(struct rt_mtd_nand_device *device,
                                      rt_off_t page,
                                      const rt_uint8_t *data,
                                      rt_uint32_t data_len,
                                      const rt_uint8_t *spare,
                                      rt_uint32_t spare_len)
{
    rt_err_t result = RT_EOK ;

    LOG_I("[W-%d]data: 0x%08x %d, spare: 0x%08x, %d", page, data, data_len, spare, spare_len);

    RT_ASSERT(device);

    if (page / device->pages_per_block > device->block_end)
    {
        LOG_E("[EIO] write page:%d", page);
        return -RT_MTD_EIO;
    }

    result = rt_mutex_take(FMINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    /* Read data: 0~2111, to cache */
    if (data && data_len)
    {
        int ret = nand_write_skip_bad(FMINAND_MTD_INFO, FMINAND_MTD_INFO->writesize * page, &data_len, NULL, FMINAND_MTD_INFO->size, (u_char *)data, 0);
//            int ret = nand_write(FMINAND_MTD_INFO, FMINAND_MTD_INFO->writesize*page, &data_len, (u_char *)data);
        if (ret != 0)
        {
            result = -RT_ERROR;
            goto exit_nu_fminand_write_page;
        }
    }

//    if (spare && spare_len)
//    {
//        if (result != RT_EOK)
//            goto exit_nu_fminand_write_page;
//    }

exit_nu_fminand_write_page:

    rt_mutex_release(FMINAND_FLASH_LOCK);

    return result;
}

static rt_err_t nu_fminand_move_page(struct rt_mtd_nand_device *device, rt_off_t src_page, rt_off_t dst_page)
{
    rt_err_t result = RT_EOK ;
    void *page_buf = RT_NULL;

    RT_ASSERT(device);

    if ((src_page / device->pages_per_block > device->block_end) ||
            (dst_page / device->pages_per_block > device->block_end))
    {
        LOG_E("EIO src:%08x, dst:%08x!", src_page, dst_page);
        return -RT_MTD_EIO;
    }

    LOG_D("src_page: %d, dst_page: %d", src_page, dst_page);

    result = rt_mutex_take(FMINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    {
        page_buf = rt_malloc(FMINAND_MTD_INFO->writesize);
        size_t retlen = FMINAND_MTD_INFO->writesize;

        //int ret = nand_read(FMINAND_MTD_INFO, FMINAND_MTD_INFO->writesize*src_page, &retlen, (u_char *)page_buf);
        int ret = nand_read_skip_bad(FMINAND_MTD_INFO, FMINAND_MTD_INFO->writesize * src_page, &retlen, NULL, FMINAND_MTD_INFO->size, (u_char *)page_buf);
        if (ret != 0)
        {
            result = -RT_ERROR;
            goto exit_nu_fminand_move_page;
        }

        //ret = nand_write(FMINAND_MTD_INFO, FMINAND_MTD_INFO->writesize*dst_page, &retlen, (u_char *)page_buf);
        ret = nand_write_skip_bad(FMINAND_MTD_INFO, FMINAND_MTD_INFO->writesize * dst_page, &retlen, NULL, FMINAND_MTD_INFO->size, (u_char *)page_buf, 0);
        if (ret != 0)
        {
            result = -RT_ERROR;
            goto exit_nu_fminand_move_page;
        }

    }

exit_nu_fminand_move_page:

    if (page_buf)
        rt_free(page_buf);

    rt_mutex_release(FMINAND_FLASH_LOCK);

    return result;
}

static rt_err_t nu_fminand_erase_block_force(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    rt_err_t result = RT_EOK ;

    RT_ASSERT(device);

    if (block > device->block_end)
    {
        LOG_E("[EIO] block:%d", block);
        return -RT_MTD_EIO;
    }

    result = rt_mutex_take(FMINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    int ret = nand_erase(FMINAND_MTD_INFO, FMINAND_MTD_INFO->erasesize * block, FMINAND_MTD_INFO->erasesize);
    if (ret != 0)
    {
        result = -RT_ERROR;
        goto exit_nu_fminand_erase_block_force;
    }

exit_nu_fminand_erase_block_force:

    rt_mutex_release(FMINAND_FLASH_LOCK);

    return result;
}

static rt_err_t nu_fminand_erase_block(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    rt_err_t result = RT_EOK ;

    RT_ASSERT(device);

    if (block > device->block_end)
    {
        LOG_E("[EIO] block:%d", block);
        return -RT_MTD_EIO;
    }

    LOG_D("erase block: %d -> page: %d", block, page);

    result = rt_mutex_take(FMINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    int ret = nand_erase(FMINAND_MTD_INFO, FMINAND_MTD_INFO->erasesize * block, FMINAND_MTD_INFO->erasesize);
    if (ret != 0)
    {
        result = -RT_ERROR;
        goto exit_nu_fminand_erase_block;
    }

exit_nu_fminand_erase_block:

    rt_mutex_release(FMINAND_FLASH_LOCK);

    return result;
}

static rt_err_t nu_fminand_check_block(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    rt_err_t result = RT_EOK ;
    int isbad = 0;

    RT_ASSERT(device);

    if (block > device->block_end)
    {
        LOG_E("[EIO] block:%d", block);
        return -RT_MTD_EIO;
    }

    result = rt_mutex_take(FMINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    isbad = nand_block_isbad(FMINAND_MTD_INFO, block * FMINAND_MTD_INFO->erasesize);

    LOG_D("check block status: %d isbad=%d\n", block, isbad);

    result = rt_mutex_release(FMINAND_FLASH_LOCK);
    RT_ASSERT(result == RT_EOK);

    return (isbad == 0) ? RT_EOK : -RT_ERROR ;
}

static rt_err_t nu_fminand_mark_badblock(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    rt_err_t result = RT_EOK ;
    int ret;

    RT_ASSERT(device);

    if (block > device->block_end)
    {
        LOG_E("[EIO] block:%d", block);
        return -RT_MTD_EIO;
    }

    LOG_D("mark bad block: %d", block);

    result = rt_mutex_take(FMINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    ret = mtd_block_markbad(FMINAND_MTD_INFO, block * FMINAND_MTD_INFO->erasesize);
    if (ret != 0)
    {
        LOG_E("mark %d to bad, status:  %d\n", block, ret);
    }

    rt_mutex_release(FMINAND_FLASH_LOCK);

    return result;
}

static struct rt_mtd_nand_driver_ops nu_fminand_ops =
{
    nu_fminand_read_id,
    nu_fminand_read_page,
    nu_fminand_write_page,
    nu_fminand_move_page,
    nu_fminand_erase_block,
    nu_fminand_check_block,
    nu_fminand_mark_badblock
};

static int nand_init_chip(void)
{
    uint32_t base_addr = 0xB000D8B8;

    FMINAND_NAND_CHIP->IO_ADDR_R = FMINAND_NAND_CHIP->IO_ADDR_W = (void  __iomem *)base_addr;

    if (board_nand_init(FMINAND_NAND_CHIP))
        return -1;

    if (nand_scan_tail(FMINAND_MTD_INFO))
        return -1;

    return 0;
}

static uint32_t u32IsInited = 0;
int rt_hw_mtd_fminand_init(void)
{
    int i = 0;
    rt_err_t result;
    char szTmp[8];

    if (u32IsInited)
        return RT_EOK;

    result = rt_mutex_init(FMINAND_FLASH_LOCK, "fminand", RT_IPC_FLAG_PRIO);
    RT_ASSERT(result == RT_EOK);

    result = nand_init_chip();
    if (result != RT_EOK)
        return -RT_ERROR;

    for (i = 0; i < MTD_FMINAND_PARTITION_NUM; i++)
    {
        mtd_partitions[i].page_size       =  FMINAND_MTD_INFO->writesize;                     /* The Page size in the flash */
        mtd_partitions[i].pages_per_block =  FMINAND_MTD_INFO->erasesize / FMINAND_MTD_INFO->writesize;    /* How many page number in a block */

        mtd_partitions[i].oob_size        =  FMINAND_MTD_INFO->oobsize;                       /* Out of bank size */
        mtd_partitions[i].oob_free        =  FMINAND_MTD_INFO->oobavail;                      /* the free area in oob that flash driver not use */
        mtd_partitions[i].plane_num       =  0 ;                                 /* the number of plane in the NAND Flash */
        mtd_partitions[i].ops             =  &nu_fminand_ops;

        rt_snprintf(szTmp, sizeof(szTmp), "nand%d", i);

        result = rt_mtd_nand_register_device(szTmp, &mtd_partitions[i]);
        RT_ASSERT(result == RT_EOK);
    }

    u32IsInited = 1;

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_mtd_fminand_init);

#include <finsh.h>
static int nread(int argc, char **argv)
{
    int ret = -1;
    rt_uint8_t *spare = RT_NULL;
    rt_uint8_t *data_ptr = RT_NULL;
    struct rt_mtd_nand_device *device;
    rt_uint32_t partition, page;

    if (argc != 3)
    {
        LOG_E("Usage %s: %s <partition_no> <page>.\n", __func__, __func__);
        goto exit_nread;
    }

    page   = atoi(argv[2]);

    partition = atoi(argv[1]);

    if (partition >= MTD_FMINAND_PARTITION_NUM)
        goto exit_nread;

    device = &mtd_partitions[partition];
    data_ptr = (rt_uint8_t *) rt_malloc(device->page_size);
    if (data_ptr == RT_NULL)
    {
        LOG_E("data_ptr: no memory\n");
        goto exit_nread;
    }
    spare = (rt_uint8_t *) rt_malloc(device->oob_size);
    if (spare == RT_NULL)
    {
        LOG_E("spare: no memory\n");
        goto exit_nread;
    }

    rt_memset(spare, 0,    device->oob_size);
    rt_memset(data_ptr, 0, device->page_size);

    page = page + device->block_start * device->pages_per_block;

    if (nu_fminand_read_page(device, page, &data_ptr[0], device->page_size, &spare[0], device->oob_size) != RT_EOK)
        goto exit_nread;

    rt_kprintf("Partion:%d page-%d\n", partition, page);

    ret = 0;

    nu_fminand_dump_buffer(page, data_ptr, device->page_size, "Read Data");
    nu_fminand_dump_buffer(page, spare, device->oob_size, "Read Spare");

exit_nread:

    /* release memory */
    if (data_ptr)
        rt_free(data_ptr);

    if (spare)
        rt_free(spare);

    return ret;
}

static int nwrite(int argc, char **argv)
{
    int i, ret = -1;
    rt_uint8_t *data_ptr = RT_NULL;
    struct rt_mtd_nand_device *device;
    rt_uint32_t partition, page;

    if (argc != 3)
    {
        LOG_E("Usage %s: %s <partition_no> <page>.\n", __func__, __func__);
        goto exit_nwrite;
    }

    partition = atoi(argv[1]);
    page   = atoi(argv[2]);

    if (partition >= MTD_FMINAND_PARTITION_NUM)
        goto exit_nwrite;

    device = &mtd_partitions[partition];

    data_ptr = (rt_uint8_t *) rt_malloc(device->page_size);
    if (data_ptr == RT_NULL)
    {
        LOG_E("data_ptr: no memory\n");
        goto exit_nwrite;
    }

    /* Need random data to test ECC */
    for (i = 0; i < device->page_size; i ++)
        data_ptr[i] = i / 5 - i;

    page = page + device->block_start * device->pages_per_block;
    nu_fminand_write_page(device, page, &data_ptr[0], device->page_size, NULL, 0);

    rt_kprintf("Wrote data into %d in partition-index %d.\n", page, partition);

    ret = 0;

    nu_fminand_dump_buffer(page, data_ptr, device->page_size, "Write Data");

exit_nwrite:

    /* release memory */
    if (data_ptr)
        rt_free(data_ptr);

    return ret;
}

static int nmove(int argc, char **argv)
{
    struct rt_mtd_nand_device *device;
    rt_uint32_t partition, src, dst;
    rt_uint8_t *data_ptr = RT_NULL;

    if (argc != 4)
    {
        LOG_E("Usage %s: %s <partition_no> <src page> <dst page>.\n", __func__, __func__);
        goto exit_nmove;
    }

    partition = atoi(argv[1]);
    src   = atoi(argv[2]);
    dst   = atoi(argv[3]);

    if (partition >= MTD_FMINAND_PARTITION_NUM)
        return -1;

    device = &mtd_partitions[partition];

    nu_fminand_move_page(device,
                         src + device->block_start * device->pages_per_block,
                         dst + device->block_start * device->pages_per_block);

    rt_kprintf("Move data into %d from %d in partition-index %d.\n", dst, src, partition);

    data_ptr = (rt_uint8_t *) rt_malloc(device->page_size);
    if (data_ptr == RT_NULL)
    {
        LOG_E("spare: no memory\n");
        goto exit_nmove;
    }

    nu_fminand_dump_buffer(src + device->block_start * device->pages_per_block, data_ptr, device->page_size, "Move Src");
    nu_fminand_dump_buffer(dst + device->block_start * device->pages_per_block, data_ptr, device->page_size, "Move Dst");

    rt_free(data_ptr);
    return 0;

exit_nmove:
    return -1;
}

static int nerase(int argc, char **argv)
{
    struct rt_mtd_nand_device *device;
    int partition, block;

    if (argc != 3)
    {
        LOG_E("Usage %s: %s <partition_no> <block_no>.\n", __func__, __func__);
        goto exit_nerase;
    }

    partition = atoi(argv[1]);
    block   = atoi(argv[2]);

    if (partition >= MTD_FMINAND_PARTITION_NUM)
        goto exit_nerase;

    device = &mtd_partitions[partition];

    if (nu_fminand_erase_block(device, block + device->block_start) != RT_EOK)
        goto exit_nerase;

    rt_kprintf("Erased block %d in partition-index %d.\n", block + device->block_start, partition);

    return 0;

exit_nerase:

    return -1;
}

static int nerase_force(int argc, char **argv)
{
    struct rt_mtd_nand_device *device;
    int partition, block;

    if (argc != 2)
    {
        LOG_E("Usage %s: %s <partition_no>\n", __func__, __func__);
        goto exit_nerase_force;
    }

    partition = atoi(argv[1]);

    if (partition >= MTD_FMINAND_PARTITION_NUM)
        goto exit_nerase_force;

    device = &mtd_partitions[partition];

    for (block = 0; block <= device->block_end; block++)
    {
        if (nu_fminand_erase_block_force(device, block + device->block_start) != RT_EOK)
            goto exit_nerase_force;
        rt_kprintf("Erased block %d in partition-index %d. forcely\n", block + device->block_start, partition);
    }
    return 0;

exit_nerase_force:

    return -1;
}

static rt_err_t nmarkbad(int argc, char **argv)
{
    struct rt_mtd_nand_device *device;
    int partition, block;

    if (argc != 3)
    {
        LOG_E("Usage %s: %s <partition_no> <block_no>.\n", __func__, __func__);
        goto exit_nmarkbad;
    }

    partition = atoi(argv[1]);
    block   = atoi(argv[2]);

    if (partition >= MTD_FMINAND_PARTITION_NUM)
        goto exit_nmarkbad;

    device = &mtd_partitions[partition];

    if (nu_fminand_mark_badblock(device, block + device->block_start) != RT_EOK)
        goto exit_nmarkbad;


    rt_kprintf("Marked block %d in partition-index %d.\n", block + device->block_start, partition);

    return 0;

exit_nmarkbad:

    return -1;
}

static int nerase_all(int argc, char **argv)
{
    rt_uint32_t index;
    rt_uint32_t partition;
    struct rt_mtd_nand_device *device;

    if (argc != 2)
    {
        LOG_E("Usage %s: %s <partition_no>.\n", __func__, __func__);
        goto exit_nerase_all;
    }

    partition = atoi(argv[1]);

    if (partition >= MTD_FMINAND_PARTITION_NUM)
        goto exit_nerase_all;

    device = &mtd_partitions[partition];

    for (index = 0; index < device->block_total; index ++)
    {
        nu_fminand_erase_block(device, index);
    }

    rt_kprintf("Erased all block in partition-index %d.\n", partition);

    return 0;

exit_nerase_all:

    return -1;
}

static int ncheck_all(int argc, char **argv)
{
    rt_uint32_t index;
    rt_uint32_t partition;
    struct rt_mtd_nand_device *device;

    if (argc != 2)
    {
        LOG_E("Usage %s: %s <partition_no>.\n", __func__, __func__);
        return -1;
    }

    partition = atoi(argv[1]);

    if (partition >= MTD_FMINAND_PARTITION_NUM)
        return -1;

    device = &mtd_partitions[partition];

    for (index = 0; index < device->block_total; index ++)
    {
        rt_kprintf("Partion:%d Block-%d is %s\n", partition, index, nu_fminand_check_block(device, index + device->block_start) ? "bad" : "good");
    }

    return 0;
}

static int nid(int argc, char **argv)
{
    nu_fminand_read_id(RT_NULL);
    return 0;
}

static int nlist(int argc, char **argv)
{
    rt_uint32_t index;
    struct rt_mtd_nand_device *device;

    rt_kprintf("\n");
    for (index = 0 ; index < MTD_FMINAND_PARTITION_NUM ; index++)
    {
        device = &mtd_partitions[index];
        rt_kprintf("[Partition #%d]\n", index);
        rt_kprintf("Name: %s\n", device->parent.parent.name);
        rt_kprintf("Start block: %d\n", device->block_start);
        rt_kprintf("End block: %d\n", device->block_end);
        rt_kprintf("Block number: %d\n", device->block_total);
        rt_kprintf("Plane number: %d\n", device->plane_num);
        rt_kprintf("Pages per Block: %d\n", device->pages_per_block);
        rt_kprintf("Page size: %d bytes\n", device->page_size);
        rt_kprintf("Spare size: %d bytes\n", device->oob_size);
        rt_kprintf("Total size: %d bytes (%d KB)\n", device->block_total * device->pages_per_block * device->page_size,
                   device->block_total * device->pages_per_block * device->page_size / 1024);
        rt_kprintf("\n");
    }
    return 0;
}

static int nfiles(int argc, char **argv)
{
    char szCmd[64];
    int i;
    for (i = 0; i < 256; i++)
    {
        rt_snprintf(szCmd, 64, "echo %d /mnt/fminand/%d", i, i);
        system(szCmd);
        rt_kprintf("%s\n", szCmd);
    }

    for (i = 0; i < 256; i++)
    {
        rt_snprintf(szCmd, 64, "cat /mnt/fminand/%d", i);
        system(szCmd);
        rt_kprintf("%s\n", szCmd);
    }

    return 0;
}

#ifdef FINSH_USING_MSH
    MSH_CMD_EXPORT(nfiles, write files);
    MSH_CMD_EXPORT(nid, nand id);
    MSH_CMD_EXPORT(nlist, list all partition information on nand);
    MSH_CMD_EXPORT(nmove, nand copy page);
    MSH_CMD_EXPORT(nerase, nand erase a block of one partiton);
    MSH_CMD_EXPORT(nerase_force, nand erase a block of one partiton forcely);
    MSH_CMD_EXPORT(nerase_all, erase all blocks of a partition);
    MSH_CMD_EXPORT(ncheck_all, check all blocks of a partition);
    MSH_CMD_EXPORT(nmarkbad, nand mark bad block of one partition);
    MSH_CMD_EXPORT(nwrite, nand write page);
    MSH_CMD_EXPORT(nread, nand read page);
#endif

#endif
