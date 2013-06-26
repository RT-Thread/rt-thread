/*
 * RT-Thread Device Interface for uffs
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "dfs_uffs.h"

static int nand_init_flash(uffs_Device *dev)
{
    return UFFS_FLASH_NO_ERR;
}

static int nand_release_flash(uffs_Device *dev)
{
    return UFFS_FLASH_NO_ERR;
}
static int nand_erase_block(uffs_Device *dev, unsigned block)
{
    int res;

    res = rt_mtd_nand_erase_block(RT_MTD_NAND_DEVICE(dev->_private), block);

    return res == RT_EOK ? UFFS_FLASH_NO_ERR : UFFS_FLASH_IO_ERR;
}

#if defined(RT_UFFS_USE_CHECK_MARK_FUNCITON)
static int nand_check_block(uffs_Device *dev, unsigned block)
{
    int res;

    res = rt_mtd_nand_check_block(RT_MTD_NAND_DEVICE(dev->_private), block);

    return res == RT_EOK ? UFFS_FLASH_NO_ERR : UFFS_FLASH_BAD_BLK;
}

static int nand_mark_badblock(uffs_Device *dev, unsigned block)
{
    int res;

    res = rt_mtd_nand_mark_badblock(RT_MTD_NAND_DEVICE(dev->_private), block);

    return res == RT_EOK ? UFFS_FLASH_NO_ERR : UFFS_FLASH_IO_ERR;
}
#endif

#if (RT_CONFIG_UFFS_ECC_MODE == UFFS_ECC_NONE) || (RT_CONFIG_UFFS_ECC_MODE == UFFS_ECC_SOFT)
static int nand_read_page(uffs_Device *dev,
                          u32          block,
                          u32          page,
                          u8          *data,
                          int          data_len,
                          u8          *ecc,
                          rt_uint8_t  *spare,
                          int          spare_len)
{
    int res;

    page = block * dev->attr->pages_per_block + page;
    if (data == NULL && spare == NULL)
    {
#if defined(RT_UFFS_USE_CHECK_MARK_FUNCITON)
        RT_ASSERT(0); //should not be here
#else
        /* check block status: bad or good */
        rt_uint8_t spare[UFFS_MAX_SPARE_SIZE];

        rt_memset(spare, 0, UFFS_MAX_SPARE_SIZE);

        rt_mtd_nand_read(RT_MTD_NAND_DEVICE(dev->_private),
                         page, RT_NULL, 0,
                         spare, dev->attr->spare_size);//dev->mem.spare_data_size

        res = spare[dev->attr->block_status_offs] == 0xFF ?
                               UFFS_FLASH_NO_ERR : UFFS_FLASH_BAD_BLK;

        return res;
#endif
    }

    rt_mtd_nand_read(RT_MTD_NAND_DEVICE(dev->_private),
                     page, data, data_len, spare, spare_len);

    return UFFS_FLASH_NO_ERR;
}

static int nand_write_page(uffs_Device *dev,
                           u32          block,
                           u32          page,
                           const u8    *data,
                           int          data_len,
                           const u8    *spare,
                           int          spare_len)
{
    int res;

    RT_ASSERT(UFFS_MAX_SPARE_SIZE >= dev->attr->spare_size);

    page = block * dev->attr->pages_per_block + page;

    if (data == NULL && spare == NULL)
    {
#if defined(RT_UFFS_USE_CHECK_MARK_FUNCITON)
        RT_ASSERT(0); //should not be here
#else
        /* mark bad block  */
        rt_uint8_t spare[UFFS_MAX_SPARE_SIZE];

        rt_memset(spare, 0xFF, UFFS_MAX_SPARE_SIZE);
        spare[dev->attr->block_status_offs] =  0x00;

        res = rt_mtd_nand_write(RT_MTD_NAND_DEVICE(dev->_private),
                                page, RT_NULL, 0,
                                spare, dev->attr->spare_size);//dev->mem.spare_data_size
        if (res != RT_EOK)
            goto __error;
#endif
    }

    res = rt_mtd_nand_write(RT_MTD_NAND_DEVICE(dev->_private),
                           page,  data, data_len, spare, spare_len);
    if (res != RT_EOK)
        goto __error;

    return UFFS_FLASH_NO_ERR;

__error:
    return UFFS_FLASH_IO_ERR;
}

const uffs_FlashOps nand_ops =
{
    nand_init_flash,    /* InitFlash() */
    nand_release_flash, /* ReleaseFlash() */
    nand_read_page,     /* ReadPage() */
    NULL,               /* ReadPageWithLayout */
    nand_write_page,    /* WritePage() */
    NULL,               /* WirtePageWithLayout */
#if defined(RT_UFFS_USE_CHECK_MARK_FUNCITON)
    nand_check_block,
    nand_mark_badblock,
#else
    NULL,               /* IsBadBlock(), let UFFS take care of it. */
    NULL,               /* MarkBadBlock(), let UFFS take care of it. */
#endif
    nand_erase_block,   /* EraseBlock() */
};

void uffs_setup_storage(struct uffs_StorageAttrSt *attr,
                        struct rt_mtd_nand_device *nand)
{
    rt_memset(attr, 0, sizeof(struct uffs_StorageAttrSt));

//  attr->total_blocks = nand->end_block - nand->start_block + 1;/* no use */
    attr->page_data_size = nand->page_size;                /* page data size */
    attr->pages_per_block = nand->pages_per_block;         /* pages per block */
    attr->spare_size = nand->oob_size;                     /* page spare size */
    attr->ecc_opt = RT_CONFIG_UFFS_ECC_MODE;               /* ecc option */
    attr->ecc_size = 0;                                    /* ecc size is 0 , the uffs will calculate the ecc size*/
    attr->block_status_offs = attr->ecc_size;              /* indicate block bad or good, offset in spare */
    attr->layout_opt = RT_CONFIG_UFFS_LAYOUT;              /* let UFFS do the spare layout */
}

#elif  RT_CONFIG_UFFS_ECC_MODE == UFFS_ECC_HW_AUTO
static int WritePageWithLayout(uffs_Device         *dev,
                               u32                  block,
                               u32                  page,
                               const u8            *data,
                               int                  data_len,
                               const u8            *ecc,  //NULL
                               const uffs_TagStore *ts)
{
    int res;
    int spare_len;
    rt_uint8_t spare[UFFS_MAX_SPARE_SIZE];

    RT_ASSERT(UFFS_MAX_SPARE_SIZE >= dev->attr->spare_size);

    page = block * dev->attr->pages_per_block + page;
    spare_len = dev->mem.spare_data_size;

    if (data == NULL && ts == NULL)
    {
#if defined(RT_UFFS_USE_CHECK_MARK_FUNCITON)
        RT_ASSERT(0); //should not be here
#else
        /* mark bad block  */
        rt_memset(spare, 0xFF, UFFS_MAX_SPARE_SIZE);
        spare[dev->attr->block_status_offs] =  0x00;

        res = rt_mtd_nand_write(RT_MTD_NAND_DEVICE(dev->_private),
                                page, RT_NULL, 0,
                                spare, dev->attr->spare_size);//dev->mem.spare_data_size
        if (res != RT_EOK)
            goto __error;

        dev->st.io_write++;
        return UFFS_FLASH_NO_ERR;
#endif
    }

    if (data != NULL && data_len != 0)
    {
        RT_ASSERT(data_len == dev->attr->page_data_size);

        dev->st.page_write_count++;
        dev->st.io_write += data_len;
    }

    if (ts != RT_NULL)
    {
        uffs_FlashMakeSpare(dev, ts, RT_NULL, (u8 *)spare);
        dev->st.spare_write_count++;
        dev->st.io_write += spare_len;
    }

    res = rt_mtd_nand_write(RT_MTD_NAND_DEVICE(dev->_private),
                            page, data, data_len, spare, spare_len);
    if (res != RT_EOK)
        goto __error;

    return UFFS_FLASH_NO_ERR;

__error:
    return UFFS_FLASH_IO_ERR;
}

static URET ReadPageWithLayout(uffs_Device   *dev,
                               u32            block,
                               u32            page,
                               u8            *data,
                               int            data_len,
                               u8            *ecc,              //NULL
                               uffs_TagStore *ts,
                               u8            *ecc_store)        //NULL
{
    int res = UFFS_FLASH_NO_ERR;
    int spare_len;
    rt_uint8_t spare[UFFS_MAX_SPARE_SIZE];

    RT_ASSERT(UFFS_MAX_SPARE_SIZE >= dev->attr->spare_size);

    page = block * dev->attr->pages_per_block + page;
    spare_len = dev->mem.spare_data_size;

    if (data == RT_NULL && ts == RT_NULL)
    {
#if defined(RT_UFFS_USE_CHECK_MARK_FUNCITON)
        RT_ASSERT(0); //should not be here
#else
        /* check block good or bad */

        rt_mtd_nand_read(RT_MTD_NAND_DEVICE(dev->_private),
                         page, RT_NULL, 0,
                         spare, dev->attr->spare_size);//dev->mem.spare_data_size

        dev->st.io_read++;

        res = spare[dev->attr->block_status_offs] == 0xFF ?
                               UFFS_FLASH_NO_ERR : UFFS_FLASH_BAD_BLK;
        return res;
#endif
    }

    if (data != RT_NULL)
    {
        dev->st.io_read += data_len;
        dev->st.page_read_count++;
    }

    res = rt_mtd_nand_read(RT_MTD_NAND_DEVICE(dev->_private),
                           page, data, data_len, spare, spare_len);
    if (res == 0)
        res = UFFS_FLASH_NO_ERR;
    else if (res == -1)
    {
        //TODO ecc correct, add code to use hardware do ecc correct
        res = UFFS_FLASH_ECC_OK;
    }
    else
        res = UFFS_FLASH_ECC_FAIL;

    if (ts != RT_NULL)
    {
        // unload ts and ecc from spare, you can modify it if you like
        uffs_FlashUnloadSpare(dev, (const u8 *)spare, ts, RT_NULL);

        if ((spare[spare_len - 1] == 0xFF) && (res == UFFS_FLASH_NO_ERR))
            res = UFFS_FLASH_NOT_SEALED;

        dev->st.io_read += spare_len;
        dev->st.spare_read_count++;
    }

    return res;
}

const uffs_FlashOps nand_ops =
{
    nand_init_flash,    /* InitFlash() */
    nand_release_flash, /* ReleaseFlash() */
    NULL,               /* ReadPage() */
    ReadPageWithLayout, /* ReadPageWithLayout */
    NULL,               /* WritePage() */
    WritePageWithLayout,/* WirtePageWithLayout */

#if defined(RT_UFFS_USE_CHECK_MARK_FUNCITON)
    nand_check_block,
    nand_mark_badblock,
#else
    NULL,               /* IsBadBlock(), let UFFS take care of it. */
    NULL,               /* MarkBadBlock(), let UFFS take care of it. */
#endif
    nand_erase_block,   /* EraseBlock() */
};

static rt_uint8_t hw_flash_data_layout[UFFS_SPARE_LAYOUT_SIZE] =
{
    0x05, 0x08, 0xFF, 0x00
};

static rt_uint8_t hw_flash_ecc_layout[UFFS_SPARE_LAYOUT_SIZE] =
{
    0x00, 0x04, 0xFF, 0x00
};

void uffs_setup_storage(struct uffs_StorageAttrSt *attr,
                        struct rt_mtd_nand_device *nand)
{
    rt_memset(attr, 0, sizeof(struct uffs_StorageAttrSt));

//  attr->total_blocks = nand->end_block - nand->start_block + 1;/* no use */
    attr->page_data_size = nand->page_size;                /* page data size */
    attr->pages_per_block = nand->pages_per_block;         /* pages per block */
    attr->spare_size = nand->oob_size;                     /* page spare size */
    attr->ecc_opt = RT_CONFIG_UFFS_ECC_MODE;               /* ecc option */
    attr->ecc_size = nand->oob_size-nand->oob_free;        /* ecc size */
    attr->block_status_offs = attr->ecc_size;              /* indicate block bad or good, offset in spare */
    attr->layout_opt = RT_CONFIG_UFFS_LAYOUT;              /* let UFFS do the spare layout */

    /* calculate the ecc layout array */
    hw_flash_data_layout[0] = attr->ecc_size + 1; /* ecc size + 1byte block status */
    hw_flash_data_layout[1] = 0x08;
    hw_flash_data_layout[2] = 0xFF;
    hw_flash_data_layout[3] = 0x00;

    hw_flash_ecc_layout[0] = 0;
    hw_flash_ecc_layout[1] = attr->ecc_size;
    hw_flash_ecc_layout[2] = 0xFF;
    hw_flash_ecc_layout[3] = 0x00;

    /* initialize  _uffs_data_layout and _uffs_ecc_layout */
    rt_memcpy(attr->_uffs_data_layout, hw_flash_data_layout, UFFS_SPARE_LAYOUT_SIZE);
    rt_memcpy(attr->_uffs_ecc_layout, hw_flash_ecc_layout, UFFS_SPARE_LAYOUT_SIZE);

    attr->data_layout = attr->_uffs_data_layout;
    attr->ecc_layout = attr->_uffs_ecc_layout;
}
#endif
