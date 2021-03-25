/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-05-25     Bernard      first version
 */

#include "nand.h"
#include "mb9bf506r.h"

/*
 * NandFlash driver for SamSung K9F5608
 * 32M x 8bit
 */
#define PAGE_SIZE       512
#define PAGE_PER_BLOCK  32
#define BLOCK_NUM       2048

/* device driver debug trace */
/* #define NAND_DEBUG */
#ifdef NAND_DEBUG
#define trace_log       rt_kprintf
#else
#define trace_log(...)
#endif

/*
 * OOB,
 * when block has been erased,  OOB is 0xff.
 * when block has been written, OOB is 0x00.
 */
struct rt_device_nand
{
    struct rt_device parent;    /* which is inherited from rt_device */

    rt_uint16_t block_num;      /* total block number in device     */
    rt_uint16_t page_per_block; /* pages in one block               */
    rt_uint16_t page_size;      /* page size                        */

    /* this buffer which used as to save data before erase block    */
    rt_uint8_t  block_buffer[PAGE_SIZE * PAGE_PER_BLOCK];
};
static struct rt_device_nand _nand;

/* Flash operation definition */
#define NF_CMD(cmd)     {*(volatile unsigned char*)(NF_FLASH_BASE_ADDR+NF_CMD_OFFSET) = (unsigned char)(cmd);}
#define NF_ADDR(addr)   {*(volatile unsigned char*)(NF_FLASH_BASE_ADDR+NF_ADDR_OFFSET)= (unsigned char)(addr);}
#define NF_RDDATA()     (*(volatile unsigned char*)(NF_FLASH_BASE_ADDR+NF_DATA_OFFSET))
#define NF_WRDATA(data) {*(volatile unsigned char*)(NF_FLASH_BASE_ADDR+NF_DATA_OFFSET)= (unsigned char)(data);}
#define NF_CLR_ALE()    {*(volatile unsigned char*)(NF_FLASH_BASE_ADDR+NF_ALE_OFFSET) = (unsigned char)0;}

/* Flash Control IO definition */
#define NF_OE_H()       {IO_NF_PDOR |= NF_EN;}
#define NF_OE_L()       {IO_NF_PDOR &= ~NF_EN;}

#define NF_DATA_OUT()   {IO_NF_PDOR &= ~NF_DATA_DIR;}
#define NF_DATA_IN()    {IO_NF_PDOR |= NF_DATA_DIR;}

static unsigned char NF_ReadStatus(void);
static void Wait(unsigned int cnt);
static void NF_Reset(void);

static void Wait(unsigned int cnt)
{
    while(cnt--);
}

static void NF_Reset(void)
{
    NF_OE_L();
    NF_DATA_OUT();
    NF_CMD(NAND_CMD_RESET);
    NF_OE_H();

    Wait(10000);  /* wait for Trst */
}

static unsigned char NF_ReadStatus(void)
{
    unsigned int timeout=0;
    NF_DATA_OUT();
    NF_CMD(NAND_CMD_STATUS);
    NF_DATA_IN();

    while(!(NF_RDDATA() & 0x40))
    {
       timeout++;
       if(timeout == 0x00080000)
         return FLASH_NG;
    }
    if(NF_RDDATA() & 0x01)return FLASH_NG;

    return FLASH_OK;
}

/*
 * @ Funciton: NF_Init
 *   Parameter: None
 *   Return: None
 */
static void NF_Init(void)
{
    FM3_GPIO->PFR5 |= (0x7ff);      /*  D0-D5, CS7, ALE, CLE, WEX, REX */
    FM3_GPIO->PFR3 |= (0x3);        /* D6-D7 */
    FM3_GPIO->EPFR10 |= (1<<13      /* CS enable */
                       |1<<6        /* ALE, CLE, WEX, REX enable */
                       |1<<0);      /* D0-D7 enable */
    FM3_EXBUS->AREA7 = 0x001f00e0;  /* Select CS7 area, 32Mbyte size */
    FM3_EXBUS->MODE7 |= (1<<4);     /* Nand Flash mode turn on, set 8 bit width */

    IO_NF_PFR = IO_NF_PFR & ~(NF_EN|NF_DATA_DIR);
    IO_NF_DDR = IO_NF_DDR | (NF_EN|NF_DATA_DIR);
    IO_NF_PDOR = IO_NF_PDOR | (NF_EN | NF_DATA_DIR); /* disable Flash operation */

    /*Reset NAND*/
    NF_Reset();
}

static void NF_UnInit(void)
{
    FM3_GPIO->PFR5 &= ~(0x7ff);     /*  disable D0-D5, CS7, ALE, CLE, WEX, REX */
    FM3_GPIO->PFR3 &= ~(0x3);       /* disable D6-D7 */
    FM3_GPIO->EPFR10 &= ~(1<<13     /* disable CS enable */
                       |1<<6        /* disable ALE, CLE, WEX, REX enable */
                       |1<<0);      /* disable D0-D7 enable */
    FM3_EXBUS->MODE7 &= ~(1<<4);
    IO_NF_PFR = IO_NF_PFR & ~(NF_EN|NF_DATA_DIR);
    IO_NF_DDR = IO_NF_DDR | (NF_EN|NF_DATA_DIR);
    IO_NF_PDOR = IO_NF_PDOR | (NF_EN | NF_DATA_DIR); /* disable Flash operation */
}

/*
 * @ Funciton: NF_ReadPage
 *   Parameter: block (max: 2048)
 *              page  (max:32)
 *              buffer: pointer to data buffer
 *   Return: 0: Flash Operation OK
 *           1: Flash Operation NG
 */
int NF_ReadPage(unsigned int block, unsigned int page, unsigned char *buffer,
                unsigned char *oob)
{
    unsigned int blockPage,i;

    NF_Init();
    blockPage=(block<<5)+page;                      /* 1 block=32 page */
    NF_OE_L();
    NF_DATA_OUT();
    if (buffer != RT_NULL)
    {
        volatile unsigned char ch;

        NF_CMD(NAND_CMD_READ0);                     /* send read data */

        NF_ADDR(0);
        NF_ADDR(blockPage & 0xff);
        NF_ADDR((blockPage>>8) & 0xff);             /* send 3 byte address */
        NF_CLR_ALE();
        NF_DATA_IN();

        Wait(500);

        for(i=0;i<512;i++)                          /* read 512 bytes data */
            buffer[i] = NF_RDDATA();
        for(i=0;i<16;i++)                           /* read 16 bytes oob */
            if (oob != RT_NULL)
                oob[i] = NF_RDDATA();
            else
                ch = NF_RDDATA();
    }
    else
    {
        NF_CMD(NAND_CMD_READOOB);                   /* send read data */

        NF_ADDR(0);
        NF_ADDR(blockPage & 0xff);
        NF_ADDR((blockPage>>8) & 0xff);             /* send 3 byte address */
        NF_CLR_ALE();
        NF_DATA_IN();

        Wait(500);

        for (i=0; i<16; i++)                        /* read 16 bytes oob */
           oob[i] = NF_RDDATA();
    }

    NF_OE_H();
    NF_UnInit();
    return 0;
}

/*
 * @ Funciton: NF_EraseBlock
 *   Parameter: block (max: 2048)
 *   Return: 0: Flash Operation OK
 *           1: Flash Operation NG
 */
int NF_EraseBlock(unsigned int block)
{
    rt_uint32_t blockPage;

    trace_log("Erase block %d: ", block);

    NF_Init();
    blockPage = (block << 5);
    NF_OE_L();
    NF_DATA_OUT();
    NF_CMD(NAND_CMD_ERASE1);                        /* send erase command */
    NF_ADDR(blockPage & 0xff);
    NF_ADDR((blockPage >> 8) & 0xff);
    NF_CMD(NAND_CMD_ERASE2);                        /* start erase */

    if(NF_ReadStatus())
    {
        NF_Reset();
        NF_OE_H();
        NF_UnInit();
        trace_log("Failed\n");
        rt_kprintf("erase block failed\n");

        return FLASH_NG;
    }

    NF_OE_H();
    NF_UnInit();

    trace_log("OK\n");

    return FLASH_OK;
}

/*
 * @ Funciton: NF_WritePage
 *   Parameter: block (max: 2048)
 *              page  (max:32)
 *              buffer: pointer to data buffer
 *   Return: 0: Flash Operation OK
 *           1: Flash Operation NG
 */
int NF_WritePage(unsigned block, unsigned page, const rt_uint8_t *buffer)
{
    unsigned int blockPage,i;
    unsigned char se[16] = {0};
    unsigned char data;

    blockPage = (block<<5)+page;
    NF_Init();
    NF_OE_L();
    NF_DATA_OUT();
    NF_CMD(0x00);                                    /* set programming area */
    NF_CMD(NAND_CMD_SEQIN);                          /* send write command */
    NF_ADDR(0);
    NF_ADDR(blockPage & 0xff);
    NF_ADDR((blockPage>>8) & 0xff);
    NF_CLR_ALE();

    for(i=0;i<512;i++) NF_WRDATA(buffer[i]);    /* write data */
    for(i=0;i<16;i++) NF_WRDATA(se[i]);         /* dummy write */

    NF_CMD(NAND_CMD_PAGEPROG);                  /* start programming */

    if(NF_ReadStatus())
    {
        NF_Reset();
        NF_OE_H();
        NF_UnInit();

        trace_log("write failed\n");
        return FLASH_NG;
    }

    /* verify the write data */
    NF_DATA_OUT();
    NF_CMD(NAND_CMD_READ0);                     /* send read command */
    NF_ADDR(0);
    NF_ADDR(blockPage & 0xff);
    NF_ADDR((blockPage>>8) & 0xff);
    NF_CLR_ALE();
    NF_DATA_IN();

    Wait(500);
    for(i=0; i<512; i++)
    {
        data=NF_RDDATA();                       /* verify 1-512 byte */
        if(data != buffer[i])
        {
            trace_log("block %d, page %d\n", block , page);
            trace_log("write data failed[%d]: %02x %02x\n", i, data, buffer[i]);

            NF_Reset();
            NF_OE_H();
            NF_UnInit();
            return FLASH_NG;
        }
    }

    for(i=0; i<16; i++)
    {
       data=NF_RDDATA();                        /* verify 16 byte dummy data */
        if(data != se[i])
        {
            trace_log("block %d, page %d\n", block , page);
            trace_log("write oob failed[%d]: %02x %02x\n", i, data, se[i]);
            NF_Reset();
            NF_OE_H();
            NF_UnInit();
            return FLASH_NG;
        }
    }

    NF_OE_H();
    NF_UnInit();
    return FLASH_OK;
}

/*
 * @ Funciton: NF_ReadID
 *   Parameter: id: pointer to device ID
 *   Return: None
 */
void NF_ReadID(unsigned char *id)
{
    unsigned char maker_code;
    NF_Init();
    NF_OE_L();
    NF_DATA_OUT();
    NF_CMD(NAND_CMD_READID);
    NF_ADDR(0x00);
    NF_CLR_ALE();
    Wait(10);
    NF_DATA_IN();
    maker_code = NF_RDDATA();
    maker_code = maker_code;
    *id = NF_RDDATA();
    NF_OE_H();
    NF_UnInit();
}

static rt_err_t rt_nand_init (rt_device_t dev)
{
    /* empty implementation */
    return RT_EOK;
}

static rt_err_t rt_nand_open(rt_device_t dev, rt_uint16_t oflag)
{
    /* empty implementation */
    return RT_EOK;
}

static rt_err_t rt_nand_close(rt_device_t dev)
{
    /* empty implementation */
    return RT_EOK;
}

/* nand device read */
static rt_size_t rt_nand_read (rt_device_t dev, rt_off_t pos, void* buffer,
                               rt_size_t size)
{
    rt_ubase_t block;           /* block of position */
    rt_ubase_t page, index;     /* page in block of position */
    rt_uint8_t *page_ptr, oob[16];
    struct rt_device_nand *nand;

    /* get nand device */
    nand = (struct rt_device_nand*) dev;
    RT_ASSERT(nand != RT_NULL);

    /* get block and page */
    block = pos / nand->page_per_block;
    page  = pos % nand->page_per_block;

    trace_log("nand read: position %d, block %d, page %d, size %d\n",
        pos, block, page, size);

    /* set page buffer pointer */
    page_ptr = (rt_uint8_t*) buffer;
    for (index = 0; index < size; index ++)
    {
        NF_ReadPage(block, page + index, page_ptr, oob);
        page_ptr += nand->page_size;

        if (page + index > nand->page_per_block)
        {
            block += 1;
            page = 0;
        }
    }

    /* return read size (count of block) */
    return size;
}

/*
 * write pages by erase block first
 * @param nand the nand device driver
 * @param block the block of page
 * @param page the page
 * @param buffer the data buffer to be written
 * @param pages the number of pages to be written
 */
static int rt_nand_eraseblock_writepage(struct rt_device_nand* nand,
                                        rt_ubase_t block, rt_ubase_t page,
    const rt_uint8_t *buffer, rt_ubase_t pages)
{
    rt_ubase_t index;
    rt_uint32_t page_status;
    rt_uint8_t *page_ptr, oob[16];

    /* set page status */
    page_status = 0;

    /* read each page in block */
    page_ptr = nand->block_buffer;
    for (index = 0; index < nand->page_per_block; index ++)
    {
        NF_ReadPage(block, index, page_ptr, oob);
        if (!oob[0])
            page_status |= (1 << index);
        page_ptr += nand->page_size;
    }

    /* erase block */
    NF_EraseBlock(block);

    page_ptr = &(nand->block_buffer[page * nand->page_size]);
    /* merge buffer to page buffer */
    for (index = 0; index < pages; index ++)
    {
        rt_memcpy(page_ptr, buffer, nand->page_size);

        /* set page status */
        page_status |= (1 << (page + index));

        /* move to next page */
        page_ptr += nand->page_size;
        buffer += nand->page_size;
    }

    /* write to flash */
    page_ptr = nand->block_buffer;
    for (index = 0; index < nand->page_per_block; index ++)
    {
        if (page_status & (1 << index))
            NF_WritePage(block, index, page_ptr);

        /* move to next page */
        page_ptr += nand->page_size;
    }

    return 0;
}

/* nand device write */
static rt_size_t rt_nand_write (rt_device_t dev, rt_off_t pos,
                                const void* buffer, rt_size_t size)
{
    rt_ubase_t block, page;
    rt_uint8_t oob[16];
    struct rt_device_nand *nand;

    nand = (struct rt_device_nand*) dev;
    RT_ASSERT(nand != RT_NULL);

    /* get block and page */
    block = pos / nand->page_per_block;
    page  = pos % nand->page_per_block;

    trace_log("nand write: position %d, block %d, page %d, size %d\n",
        pos, block, page, size);

    if (size == 1)
    {
        /* write one page */

        /* read oob to get page status */
        NF_ReadPage(block, page, RT_NULL, oob);
        if (oob[0])
            NF_WritePage(block, page, buffer);
        else
            /* erase block and then write page */
            rt_nand_eraseblock_writepage(nand, block, page, buffer, 1);
    }
    else if (size > 1)
    {
        rt_ubase_t index;
        rt_ubase_t need_erase_block;
        const rt_uint8_t *page_ptr;
        rt_ubase_t chunk_pages, pages;

        pages = size;
        page_ptr = (const rt_uint8_t*) buffer;
        do
        {
            need_erase_block = 0;
            /* calculate pages in current chunk */
            if (pages > nand->page_per_block - page)
                chunk_pages = nand->page_per_block - page;
            else
                chunk_pages = pages;

            /* get page status in current block */
            for (index = page; index < page + chunk_pages; index ++)
            {
                NF_ReadPage(block, index, RT_NULL, oob);
                if (!oob[0])
                {
                    /* this page has data, need erase this block firstly */
                    need_erase_block = 1;
                    break;
                }
            }

            if (need_erase_block)
            {
                /* erase block and then write it */
                rt_nand_eraseblock_writepage(nand, block, page, page_ptr, chunk_pages);
                page_ptr += chunk_pages * nand->page_size;
            }
            else
            {
                /* write pages directly */
                for (index = page; index < page + chunk_pages; index ++)
                {
                    NF_WritePage(block, index, page_ptr);
                    page_ptr += nand->page_size;
                }
            }

            pages -= chunk_pages;
            page = 0; block ++; /* move to next block */
        }
        while (pages);
    }

    return size;
}

static rt_err_t rt_nand_control (rt_device_t dev, int cmd, void *args)
{
    struct rt_device_nand *nand;

    nand = (struct rt_device_nand*) dev;
    RT_ASSERT(dev != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_BLK_GETGEOME:
        {
            struct rt_device_blk_geometry *geometry;

            geometry = (struct rt_device_blk_geometry *)args;
            if (geometry == RT_NULL) return -RT_ERROR;

            geometry->bytes_per_sector = nand->page_size;
            geometry->block_size = nand->page_size * nand->page_per_block;
            geometry->sector_count = nand->block_num * nand->page_per_block;
        }
        break;
    }

    return RT_EOK;
}

void rt_hw_nand_init(void)
{
    /* initialize nand flash structure */
    _nand.block_num = BLOCK_NUM;
    _nand.page_per_block = PAGE_PER_BLOCK;
    _nand.page_size = PAGE_SIZE;

    rt_memset(_nand.block_buffer, 0, sizeof(_nand.block_buffer));

    _nand.parent.type       = RT_Device_Class_MTD;
    _nand.parent.rx_indicate = RT_NULL;
    _nand.parent.tx_complete = RT_NULL;
    _nand.parent.init       = rt_nand_init;
    _nand.parent.open       = rt_nand_open;
    _nand.parent.close      = rt_nand_close;
    _nand.parent.read       = rt_nand_read;
    _nand.parent.write      = rt_nand_write;
    _nand.parent.control    = rt_nand_control;

    /* register a MTD device */
    rt_device_register(&(_nand.parent), "nand", RT_DEVICE_FLAG_RDWR);
}

#ifdef NAND_DEBUG
#include <finsh.h>
unsigned char nand_buffer[512];
unsigned char nand_oob[16];

void dump_mem(unsigned char* buffer, int length)
{
    int i;

    if (length > 64) length = 64;
    for (i = 0; i < length; i ++)
    {
        rt_kprintf("%02x ", *buffer++);
        if (((i+1) % 16) == 0)
        rt_kprintf("\n");
    }
    rt_kprintf("\n");
}

void nand_read(int block, int page)
{
    rt_kprintf("read block %d, page %d\n", block, page);

    NF_ReadPage(block, page, nand_buffer, nand_oob);
    rt_kprintf("page data:\n");
    dump_mem(nand_buffer, 512);
    rt_kprintf("oob data:\n");
    dump_mem(nand_oob, 16);
}
FINSH_FUNCTION_EXPORT_ALIAS(nand_read, read_page, read page[block/page]);

void nand_write(int block, int page)
{
    int i;
    for (i = 0; i < 512; i ++)
        nand_buffer[i] = i;

    NF_WritePage(block, page, nand_buffer);
}
FINSH_FUNCTION_EXPORT_ALIAS(nand_write, write_page, write page[block/page]);

void nand_erase(int block)
{
    NF_EraseBlock(block);
}
FINSH_FUNCTION_EXPORT_ALIAS(nand_erase, erase_block, erase block[block]);

void nand_readoob(int block, int page)
{
    rt_kprintf("read oob on block %d, page %d\n", block, page);

    NF_ReadPage(block, page, RT_NULL, (unsigned char*)nand_oob);
    rt_kprintf("oob data:\n");
    dump_mem(nand_oob, 16);
}
FINSH_FUNCTION_EXPORT_ALIAS(nand_readoob, readoob, read oob[block/page]);

void nand_erase_chip()
{
    int i;
    unsigned char id;

    NF_ReadID(&id);
    rt_kprintf("id: %02x\n", id);

    for (i = 0; i < 2048; i ++)
    {
        NF_EraseBlock(i);
    }
}
FINSH_FUNCTION_EXPORT_ALIAS(nand_erase_chip, erase_chip, erase whole chip);
#endif
