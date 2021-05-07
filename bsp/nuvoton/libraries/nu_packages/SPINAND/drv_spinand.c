/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-1-13       Wayne        First version
*
******************************************************************************/

#include <rtthread.h>

#if defined(NU_PKG_USING_SPINAND) && defined(RT_USING_MTD_NAND)

#define LOG_TAG                 "drv_spinand"
#define DBG_ENABLE
#define DBG_SECTION_NAME        LOG_TAG
#define DBG_LEVEL               DBG_INFO
#define DBG_COLOR
#include <rtdbg.h>

#include "spinand.h"

struct nu_spinand g_spinandflash_dev = {0};

rt_size_t nu_qspi_transfer_message(struct rt_qspi_device  *device, struct rt_qspi_message *message)
{
    rt_err_t result;
    struct rt_spi_message *index;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(message != RT_NULL);

    result = rt_mutex_take(&(device->parent.bus->lock), RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        rt_set_errno(-RT_EBUSY);

        return 0;
    }

    /* reset errno */
    rt_set_errno(RT_EOK);

    /* configure SPI bus */
    if (device->parent.bus->owner != &device->parent)
    {
        /* not the same owner as current, re-configure SPI bus */
        result = device->parent.bus->ops->configure(&device->parent, &device->parent.config);
        if (result == RT_EOK)
        {
            /* set SPI bus owner */
            device->parent.bus->owner = &device->parent;
        }
        else
        {
            /* configure SPI bus failed */
            rt_set_errno(-RT_EIO);
            goto __exit;
        }
    }

    /* transmit each SPI message */
    index = &message->parent;
    while (index)
    {
        if (device->parent.bus->ops->xfer(&device->parent, index) == 0)
        {
            result = -RT_EIO;
            rt_set_errno(-RT_EIO);
            goto __exit;
        }
        index = index->next;
    }

    result = RT_EOK;

__exit:
    /* release bus lock */
    rt_mutex_release(&(device->parent.bus->lock));

    return result;
}

rt_err_t nu_qspi_send_then_recv(struct rt_qspi_device *device, const void *send_buf, rt_size_t send_length, void *recv_buf, rt_size_t recv_length)
{
    struct rt_qspi_message message[2] = {0};

    RT_ASSERT(send_buf);
    RT_ASSERT(recv_buf);
    RT_ASSERT(send_length != 0);

    /* Send message */
    message[0].qspi_data_lines = 1;

    /* Set send buf and send size */
    message[0].parent.recv_buf = RT_NULL;
    message[0].parent.send_buf = send_buf;
    message[0].parent.length = send_length;
    message[0].parent.cs_take = 1;

    message[0].parent.next = &message[1].parent;

    /* Receive message */
    message[1].qspi_data_lines = 1;

    /* Set recv buf and recv size */
    message[1].parent.recv_buf = recv_buf;
    message[1].parent.send_buf = RT_NULL;
    message[1].parent.length = recv_length;
    message[1].parent.cs_release = 1;

    return nu_qspi_transfer_message(device, &message[0]);
}

rt_err_t nu_qspi_send(struct rt_qspi_device *device, const void *send_buf, rt_size_t length)
{
    RT_ASSERT(send_buf);
    RT_ASSERT(length != 0);

    struct rt_qspi_message message = {0};
    char *ptr = (char *)send_buf;
    rt_size_t  count = 0;

    message.instruction.content = ptr[0];
    message.instruction.qspi_lines = 1;
    count++;

    /* set send buf and send size */
    message.qspi_data_lines = 1;

    message.parent.send_buf = ptr + count;
    message.parent.recv_buf = RT_NULL;
    message.parent.length = length - count;
    message.parent.cs_take = 1;
    message.parent.cs_release = 1;

    return nu_qspi_transfer_message(device, &message);
}

static void spinand_dump_buffer(int page, rt_uint8_t *buf, int len, const char *title)
{
    if ((DBG_LEVEL) >= DBG_LOG)
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
}

static rt_err_t spinand_read_id(struct rt_mtd_nand_device *device)
{
    rt_err_t result = RT_EOK ;
    uint32_t id = 0;

    result = rt_mutex_take(SPINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    SPINAND_FLASH_OPS->jedecid_get(SPINAND_FLASH_QSPI, &id);

    result = rt_mutex_release(SPINAND_FLASH_LOCK);
    RT_ASSERT(result == RT_EOK);

    return (id != 0x0) ? RT_EOK : -RT_ERROR;
}

static rt_err_t spinand_read_page(struct rt_mtd_nand_device *device,
                                  rt_off_t page,
                                  rt_uint8_t *data,
                                  rt_uint32_t data_len,
                                  rt_uint8_t *spare,
                                  rt_uint32_t spare_len)
{
    rt_err_t result = RT_EOK ;

    LOG_D("[R-%d]data: 0x%08x %d, spare: 0x%08x, %d", page, data, data_len, spare, spare_len);

    RT_ASSERT(device != RT_NULL);

    if (page / device->pages_per_block > device->block_end)
    {
        LOG_E("[EIO] read page:%d", page);
        return -RT_MTD_EIO;
    }

    result = rt_mutex_take(SPINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    /* Data load, Read data from flash to cache */
    result = SPINAND_FLASH_OPS->read_dataload(SPINAND_FLASH_QSPI, (page >> 16) & 0xFF, (page >> 8) & 0xFF, (page & 0xFF));
    if (result != RT_EOK)
        goto exit_spinand_read_page;

    if (data && data_len)
    {
        /* Read data: 0~data_len, Read cache to data */
        result = SPINAND_FLASH_OPS->read_quadoutput(SPINAND_FLASH_QSPI, 0, 0, data, data_len);
        if (result != RT_EOK)
            goto exit_spinand_read_page;
    }

    if (spare && spare_len)
    {
        /* Read data: 2048~spare_len, Read cache to spare */
        result = SPINAND_FLASH_OPS->read_quadoutput(SPINAND_FLASH_QSPI, (SPINAND_FLASH_PAGE_SIZE >> 8) & 0xff, SPINAND_FLASH_PAGE_SIZE & 0xff, spare, spare_len);
        if (result != RT_EOK)
            goto exit_spinand_read_page;
    }

exit_spinand_read_page:

    rt_mutex_release(SPINAND_FLASH_LOCK);

    spinand_dump_buffer(page, data, data_len, "Read Data");
    spinand_dump_buffer(page, spare, spare_len, "Read Spare");

    return result;
}

static rt_err_t spinand_write_page(struct rt_mtd_nand_device *device,
                                   rt_off_t page,
                                   const rt_uint8_t *data,
                                   rt_uint32_t data_len,
                                   const rt_uint8_t *spare,
                                   rt_uint32_t spare_len)
{
    rt_err_t result = RT_EOK ;

    LOG_D("[W-%d]data: 0x%08x %d, spare: 0x%08x, %d", page, data, data_len, spare, spare_len);

    RT_ASSERT(device != RT_NULL);

    if (page / device->pages_per_block > device->block_end)
    {
        LOG_E("[EIO] write page:%d", page);
        return -RT_MTD_EIO;
    }

    spinand_dump_buffer(page, (uint8_t *)data, data_len, "WRITE DATA");
    spinand_dump_buffer(page, (uint8_t *)spare, spare_len, "WRITE SPARE");

    result = rt_mutex_take(SPINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    if (SPINAND_FLASH_MCP == 1)
    {
        /* Select die. */
        if ((result = SPINAND_FLASH_OPS->die_select(SPINAND_FLASH_QSPI, SPINAND_DIE_ID0)) != RT_EOK)
            goto exit_spinand_write_page;
    }

    /* Read data: 0~2111, to cache */
    if (data && data_len)
        result = SPINAND_FLASH_OPS->program_dataload(SPINAND_FLASH_QSPI, 0, 0, (uint8_t *)data, data_len, (uint8_t *)spare, spare_len);
    else
        result = SPINAND_FLASH_OPS->program_dataload(SPINAND_FLASH_QSPI, (SPINAND_FLASH_PAGE_SIZE >> 8) & 0xff, SPINAND_FLASH_PAGE_SIZE & 0xff, RT_NULL, 0, (uint8_t *)spare, spare_len);

    if (result != RT_EOK)
        goto exit_spinand_write_page;

    /* Flush data in cache to flash */
    result = SPINAND_FLASH_OPS->program_execute(SPINAND_FLASH_QSPI, (((page) >> 16) & 0xFF), (((page) >> 8) & 0xFF), (page) & 0xFF);
    if (result != RT_EOK)
        goto exit_spinand_write_page;

    result = RT_EOK;

exit_spinand_write_page:

    rt_mutex_release(SPINAND_FLASH_LOCK);

    return result;
}

static rt_err_t spinand_move_page(struct rt_mtd_nand_device *device, rt_off_t src_page, rt_off_t dst_page)
{
    rt_err_t result = RT_EOK ;
    uint8_t u8WECmd;

    RT_ASSERT(device != RT_NULL);

    if ((src_page / device->pages_per_block > device->block_end) ||
            (dst_page / device->pages_per_block > device->block_end))
    {
        LOG_E("EIO src:%08x, dst:%08x!", src_page, dst_page);
        return -RT_MTD_EIO;
    }

    LOG_D("src_page: %d, dst_page: %d", src_page, dst_page);

    result = rt_mutex_take(SPINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    /* Data load, Read data from flash to cache */
    result = SPINAND_FLASH_OPS->read_dataload(SPINAND_FLASH_QSPI, (src_page >> 16) & 0xFF, (src_page >> 8) & 0xFF, (src_page & 0xFF));
    if (result != RT_EOK)
        goto exit_spinand_move_page;

    /* Enable WE before writting. */
    u8WECmd = 0x06;
    if ((result = nu_qspi_send(SPINAND_FLASH_QSPI, &u8WECmd, sizeof(u8WECmd))) != RT_EOK)
        goto exit_spinand_move_page;

    /* Flush cache to flash */
    result = SPINAND_FLASH_OPS->program_execute(SPINAND_FLASH_QSPI, (((dst_page) >> 16) & 0xFF), (((dst_page) >> 8) & 0xFF), (dst_page) & 0xFF);
    if (result != RT_EOK)
        goto exit_spinand_move_page;

    result = RT_EOK;

exit_spinand_move_page:

    rt_mutex_release(SPINAND_FLASH_LOCK);

    return result;
}

static rt_err_t spinand_erase_block_force(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    rt_err_t result = RT_EOK ;
    uint32_t page;

    RT_ASSERT(device != RT_NULL);

    if (block > device->block_end)
    {
        LOG_E("[EIO] block:%d", block);
        return -RT_MTD_EIO;
    }

    page = block * SPINAND_FLASH_PAGE_PER_BLOCK_NUM;

    LOG_D("force erase block: %d -> page: %d", block, page);

    result = rt_mutex_take(SPINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    result = SPINAND_FLASH_OPS->block_erase(SPINAND_FLASH_QSPI, (page >> 16) & 0xFF, (page >> 8) & 0xFF, page & 0xFF);
    if (result != RT_EOK)
        goto exit_spinand_erase_block_force;

    result = RT_EOK;

exit_spinand_erase_block_force:

    rt_mutex_release(SPINAND_FLASH_LOCK);

    return result;
}

static rt_err_t spinand_erase_block(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    rt_err_t result = RT_EOK ;
    uint32_t page;

    RT_ASSERT(device != RT_NULL);

    if (block > device->block_end)
    {
        LOG_E("[EIO] block:%d", block);
        return -RT_MTD_EIO;
    }

    page = block * SPINAND_FLASH_PAGE_PER_BLOCK_NUM;

    LOG_D("erase block: %d -> page: %d", block, page);

    result = rt_mutex_take(SPINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    /* Erase block after checking it is bad or not. */
    if (SPINAND_FLASH_OPS->block_isbad(SPINAND_FLASH_QSPI, page) != 0)
    {
        LOG_W("Block %d is bad.\n", block);
        result = -RT_ERROR;
        goto exit_spinand_erase_block;
    }
    else
    {
        result = SPINAND_FLASH_OPS->block_erase(SPINAND_FLASH_QSPI, (page >> 16) & 0xFF, (page >> 8) & 0xFF, page & 0xFF);
        if (result != RT_EOK)
            goto exit_spinand_erase_block;
    }

    result = RT_EOK;

exit_spinand_erase_block:

    rt_mutex_release(SPINAND_FLASH_LOCK);

    return result;
}

static rt_err_t spinand_check_block(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    rt_err_t result = RT_EOK ;
    uint32_t page = 0;
    uint8_t isbad = 0;

    RT_ASSERT(device != RT_NULL);

    if (block > device->block_end)
    {
        LOG_E("[EIO] block:%d", block);
        return -RT_MTD_EIO;
    }

    page = block * SPINAND_FLASH_PAGE_PER_BLOCK_NUM;

    LOG_D("check block status: %d -> page: %d", block, page);

    result = rt_mutex_take(SPINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    isbad = SPINAND_FLASH_OPS->block_isbad(SPINAND_FLASH_QSPI, page);

    result = rt_mutex_release(SPINAND_FLASH_LOCK);
    RT_ASSERT(result == RT_EOK);

    return (isbad == 0) ? RT_EOK : -RT_ERROR ;
}

static rt_err_t spinand_mark_badblock(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    rt_err_t result = RT_EOK ;
    uint32_t page = 0;

    RT_ASSERT(device != RT_NULL);

    if (block > device->block_end)
    {
        LOG_E("[EIO] block:%d", block);
        return -RT_MTD_EIO;
    }

    page = block * SPINAND_FLASH_PAGE_PER_BLOCK_NUM;

    LOG_D("mark bad block: %d -> page: %d", block, page);

    result = rt_mutex_take(SPINAND_FLASH_LOCK, RT_WAITING_FOREVER);
    RT_ASSERT(result == RT_EOK);

    /* Erase block after checking it is bad or not. */
    if (SPINAND_FLASH_OPS->block_isbad(SPINAND_FLASH_QSPI, page) != 0)
    {
        LOG_W("Block %d is bad.\n", block);
        result = RT_EOK;
    }
    else
    {
        result = SPINAND_FLASH_OPS->block_markbad(SPINAND_FLASH_QSPI, page);
    }

    rt_mutex_release(SPINAND_FLASH_LOCK);

    return result;
}

static struct rt_mtd_nand_driver_ops spinand_ops =
{
    spinand_read_id,
    spinand_read_page,
    spinand_write_page,
    spinand_move_page,
    spinand_erase_block,
    spinand_check_block,
    spinand_mark_badblock
};

static uint32_t u32IsInited = 0;
rt_err_t rt_hw_mtd_spinand_init(void)
{
    int i = 0;
    rt_err_t result;
    char szTmp[8];

    if (u32IsInited)
        return RT_EOK;

    result = rt_mutex_init(SPINAND_FLASH_LOCK, "spinand", RT_IPC_FLAG_FIFO);
    RT_ASSERT(result == RT_EOK);

    result = spinand_flash_init(SPINAND_FLASH_QSPI);
    RT_ASSERT(result == RT_EOK);

    for (i = 0; i < MTD_SPINAND_PARTITION_NUM; i++)
    {
        mtd_partitions[i].page_size       =  SPINAND_FLASH_PAGE_SIZE;            /* The Page size in the flash */
        mtd_partitions[i].pages_per_block =  SPINAND_FLASH_PAGE_PER_BLOCK_NUM;   /* How many page number in a block */

        mtd_partitions[i].oob_size        =  SPINAND_FLASH_OOB_SIZE;             /* Out of bank size */
        mtd_partitions[i].oob_free        =  32;                                 /* the free area in oob that flash driver not use */
        mtd_partitions[i].plane_num       =  SPINAND_FLASH_MCP ;                 /* the number of plane in the NAND Flash */
        mtd_partitions[i].ops             =  &spinand_ops;

        rt_snprintf(szTmp, sizeof(szTmp), "nand%d", i);

        result = rt_mtd_nand_register_device(szTmp, &mtd_partitions[i]);
        RT_ASSERT(result == RT_EOK);
    }

    u32IsInited = 1;

    return result;
}

rt_err_t rt_hw_mtd_spinand_register(const char *device_name)
{
    rt_device_t pDev;
    rt_err_t result;

    if ((pDev = rt_device_find(device_name)) == RT_NULL)
        return -RT_ERROR;

    SPINAND_FLASH_QSPI = (struct rt_qspi_device *)pDev;

    SPINAND_FLASH_QSPI->config.parent.mode = RT_SPI_MODE_0 | RT_SPI_MSB;
    SPINAND_FLASH_QSPI->config.parent.data_width = 8;
    SPINAND_FLASH_QSPI->config.parent.max_hz = 48000000;
    SPINAND_FLASH_QSPI->config.ddr_mode = 0;
    SPINAND_FLASH_QSPI->config.qspi_dl_width = 4;

    result = rt_spi_configure(&SPINAND_FLASH_QSPI->parent, &SPINAND_FLASH_QSPI->config.parent);
    RT_ASSERT(result == RT_EOK);

    return rt_hw_mtd_spinand_init();
}

#if defined(RT_USING_DFS_UFFS)
#include "dfs_uffs.h"
void uffs_setup_storage(struct uffs_StorageAttrSt *attr,
                        struct rt_mtd_nand_device *nand)
{
    RT_ASSERT(attr != RT_NULL);
    RT_ASSERT(nand != RT_NULL);

    rt_memset(attr, 0, sizeof(struct uffs_StorageAttrSt));

    attr->page_data_size = nand->page_size;                /* page data size */
    attr->pages_per_block = nand->pages_per_block;         /* pages per block */
    attr->spare_size = nand->oob_size;                     /* page spare size */
    attr->ecc_opt = RT_CONFIG_UFFS_ECC_MODE;               /* ecc option */
    attr->ecc_size = nand->oob_size - nand->oob_free;      /* ecc size */
    attr->block_status_offs = 0;                           /* indicate block bad or good, offset in spare */
    attr->layout_opt = RT_CONFIG_UFFS_LAYOUT;              /* let UFFS do the spare layout */

    /* initialize  _uffs_data_layout and _uffs_ecc_layout */
    rt_memcpy(attr->_uffs_data_layout, spinand_flash_data_layout, UFFS_SPARE_LAYOUT_SIZE);
    rt_memcpy(attr->_uffs_ecc_layout, spinand_flash_ecc_layout, UFFS_SPARE_LAYOUT_SIZE);

    attr->data_layout = attr->_uffs_data_layout;
    attr->ecc_layout = attr->_uffs_ecc_layout;
}
#endif

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

    if (partition >= MTD_SPINAND_PARTITION_NUM)
        goto exit_nread;

    device = &mtd_partitions[partition];
    data_ptr = (rt_uint8_t *) rt_malloc(SPINAND_FLASH_PAGE_SIZE);
    if (data_ptr == RT_NULL)
    {
        LOG_E("data_ptr: no memory\n");
        goto exit_nread;
    }
    spare = (rt_uint8_t *) rt_malloc(SPINAND_FLASH_OOB_SIZE);
    if (spare == RT_NULL)
    {
        LOG_E("spare: no memory\n");
        goto exit_nread;
    }

    rt_memset(spare, 0,    SPINAND_FLASH_OOB_SIZE);
    rt_memset(data_ptr, 0, SPINAND_FLASH_PAGE_SIZE);

    page = page + device->block_start * device->pages_per_block;

    if (spinand_read_page(device, page, &data_ptr[0], SPINAND_FLASH_PAGE_SIZE, &spare[0], SPINAND_FLASH_OOB_SIZE) != RT_EOK)
        goto exit_nread;

    LOG_I("Partion:%d page-%d", partition, page);

    ret = 0;

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

    if (partition >= MTD_SPINAND_PARTITION_NUM)
        goto exit_nwrite;

    device = &mtd_partitions[partition];

    data_ptr = (rt_uint8_t *) rt_malloc(SPINAND_FLASH_PAGE_SIZE);
    if (data_ptr == RT_NULL)
    {
        LOG_E("data_ptr: no memory\n");
        goto exit_nwrite;
    }

    /* Need random data to test ECC */
    for (i = 0; i < SPINAND_FLASH_PAGE_SIZE; i ++)
        data_ptr[i] = i / 5 - i;

    page = page + device->block_start * device->pages_per_block;
    spinand_write_page(device, page, &data_ptr[0], SPINAND_FLASH_PAGE_SIZE, NULL, 0);

    LOG_I("Wrote data into %d in partition-index %d.", page, partition);

    ret = 0;

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

    if (argc != 4)
    {
        LOG_E("Usage %s: %s <partition_no> <src page> <dst page>.\n", __func__, __func__);
        goto exit_nmove;
    }

    partition = atoi(argv[1]);
    src   = atoi(argv[2]);
    dst   = atoi(argv[3]);

    if (partition >= MTD_SPINAND_PARTITION_NUM)
        return -1;

    device = &mtd_partitions[partition];

    spinand_move_page(device,
                      src + device->block_start * device->pages_per_block,
                      dst + device->block_start * device->pages_per_block);

    LOG_I("Move data into %d from %d in partition-index %d.", dst, src, partition);

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

    if (partition >= MTD_SPINAND_PARTITION_NUM)
        goto exit_nerase;

    device = &mtd_partitions[partition];

    if (spinand_erase_block(device, block + device->block_start) != RT_EOK)
        goto exit_nerase;

    LOG_I("Erased block %d in partition-index %d.", block + device->block_start, partition);

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

    if (partition >= MTD_SPINAND_PARTITION_NUM)
        goto exit_nerase_force;

    device = &mtd_partitions[partition];

    for (block = 0; block <= device->block_end; block++)
    {
        if (spinand_erase_block_force(device, block + device->block_start) != RT_EOK)
            goto exit_nerase_force;
        LOG_I("Erased block %d in partition-index %d. forcely", block + device->block_start, partition);
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

    if (partition >= MTD_SPINAND_PARTITION_NUM)
        goto exit_nmarkbad;

    device = &mtd_partitions[partition];

    if (spinand_mark_badblock(device, block + device->block_start) != RT_EOK)
        goto exit_nmarkbad;


    LOG_I("Marked block %d in partition-index %d.", block + device->block_start, partition);

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

    if (partition >= MTD_SPINAND_PARTITION_NUM)
        goto exit_nerase_all;

    device = &mtd_partitions[partition];

    for (index = 0; index < device->block_total; index ++)
    {
        spinand_erase_block(device, index);
    }

    LOG_I("Erased all block in partition-index %d.", partition);

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

    if (partition >= MTD_SPINAND_PARTITION_NUM)
        return -1;

    device = &mtd_partitions[partition];

    for (index = 0; index < device->block_total; index ++)
    {
        LOG_I("Partion:%d Block-%d is %s", partition, index, spinand_check_block(device, index) ? "bad" : "good");
    }

    return 0;
}

static int nid(int argc, char **argv)
{
    spinand_read_id(RT_NULL);
    return 0;
}

static int nlist(int argc, char **argv)
{
    rt_uint32_t index;
    struct rt_mtd_nand_device *device;

    rt_kprintf("\n");
    for (index = 0 ; index < MTD_SPINAND_PARTITION_NUM ; index++)
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


#ifdef FINSH_USING_MSH
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
