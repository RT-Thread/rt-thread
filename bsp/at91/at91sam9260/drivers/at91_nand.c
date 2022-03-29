/*
* Copyright (c) 2006-2022, RT-Thread Development Team
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date           Author        Notes
* 2022-01-08     brightsally   first version
*/

#include <rtdevice.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <at91sam926x.h>
#include "at91_nand.h"

static struct nand_chip_id *chip;
static unsigned int bufsize = 528;
static unsigned char pages_per_block = 32;
static unsigned char eccsize = 6;
static struct rt_mtd_nand_device _partition[2];
/*****************************************************************************
nand_calculate_ecc function copy from uboot
*****************************************************************************/
#define u_char unsigned char
/* Define default oob placement schemes for large and small page devices */
static struct nand_ecclayout nand_oob_16 =
{

    .eccbytes = 6,
      .eccpos = {0, 1, 2, 3, 6, 7},
      .oobfree = {
            {
            .offset = 8,
            . length = 8
            }
    }
};

static struct nand_ecclayout nand_oob_64 =
{
    .eccbytes = 24,
      .eccpos = {
        40, 41, 42, 43, 44, 45, 46, 47,
        48, 49, 50, 51, 52, 53, 54, 55,
        56, 57, 58, 59, 60, 61, 62, 63
    },
    .oobfree = {
        {
        .offset = 2,
        .length = 38
        }
        }
};
/*
* Pre-calculated 256-way 1 byte column parity
*/

static const u_char nand_ecc_precalc_table[] =
{
    0x00, 0x55, 0x56, 0x03, 0x59, 0x0c, 0x0f, 0x5a, 0x5a, 0x0f, 0x0c, 0x59, 0x03, 0x56, 0x55, 0x00,
    0x65, 0x30, 0x33, 0x66, 0x3c, 0x69, 0x6a, 0x3f, 0x3f, 0x6a, 0x69, 0x3c, 0x66, 0x33, 0x30, 0x65,
    0x66, 0x33, 0x30, 0x65, 0x3f, 0x6a, 0x69, 0x3c, 0x3c, 0x69, 0x6a, 0x3f, 0x65, 0x30, 0x33, 0x66,
    0x03, 0x56, 0x55, 0x00, 0x5a, 0x0f, 0x0c, 0x59, 0x59, 0x0c, 0x0f, 0x5a, 0x00, 0x55, 0x56, 0x03,
    0x69, 0x3c, 0x3f, 0x6a, 0x30, 0x65, 0x66, 0x33, 0x33, 0x66, 0x65, 0x30, 0x6a, 0x3f, 0x3c, 0x69,
    0x0c, 0x59, 0x5a, 0x0f, 0x55, 0x00, 0x03, 0x56, 0x56, 0x03, 0x00, 0x55, 0x0f, 0x5a, 0x59, 0x0c,
    0x0f, 0x5a, 0x59, 0x0c, 0x56, 0x03, 0x00, 0x55, 0x55, 0x00, 0x03, 0x56, 0x0c, 0x59, 0x5a, 0x0f,
    0x6a, 0x3f, 0x3c, 0x69, 0x33, 0x66, 0x65, 0x30, 0x30, 0x65, 0x66, 0x33, 0x69, 0x3c, 0x3f, 0x6a,
    0x6a, 0x3f, 0x3c, 0x69, 0x33, 0x66, 0x65, 0x30, 0x30, 0x65, 0x66, 0x33, 0x69, 0x3c, 0x3f, 0x6a,
    0x0f, 0x5a, 0x59, 0x0c, 0x56, 0x03, 0x00, 0x55, 0x55, 0x00, 0x03, 0x56, 0x0c, 0x59, 0x5a, 0x0f,
    0x0c, 0x59, 0x5a, 0x0f, 0x55, 0x00, 0x03, 0x56, 0x56, 0x03, 0x00, 0x55, 0x0f, 0x5a, 0x59, 0x0c,
    0x69, 0x3c, 0x3f, 0x6a, 0x30, 0x65, 0x66, 0x33, 0x33, 0x66, 0x65, 0x30, 0x6a, 0x3f, 0x3c, 0x69,
    0x03, 0x56, 0x55, 0x00, 0x5a, 0x0f, 0x0c, 0x59, 0x59, 0x0c, 0x0f, 0x5a, 0x00, 0x55, 0x56, 0x03,
    0x66, 0x33, 0x30, 0x65, 0x3f, 0x6a, 0x69, 0x3c, 0x3c, 0x69, 0x6a, 0x3f, 0x65, 0x30, 0x33, 0x66,
    0x65, 0x30, 0x33, 0x66, 0x3c, 0x69, 0x6a, 0x3f, 0x3f, 0x6a, 0x69, 0x3c, 0x66, 0x33, 0x30, 0x65,
    0x00, 0x55, 0x56, 0x03, 0x59, 0x0c, 0x0f, 0x5a, 0x5a, 0x0f, 0x0c, 0x59, 0x03, 0x56, 0x55, 0x00
};

/**
* nand_calculate_ecc - [NAND Interface] Calculate 3-byte ECC for 256-byte block
* @mtd:    MTD block structure
* @dat:    raw data
* @ecc_code:   buffer for ECC
*/
int nand_calculate_ecc(const u_char *dat, u_char *ecc_code)
{
    uint8_t idx, reg1, reg2, reg3, tmp1, tmp2;
    int i;

    /* Initialize variables */
    reg1 = reg2 = reg3 = 0;

    /* Build up column parity */
    for (i = 0; i < 256; i++)
    {
        /* Get CP0 - CP5 from table */
        idx = nand_ecc_precalc_table[*dat++];
        reg1 ^= (idx & 0x3f);

        /* All bit XOR = 1 ? */
        if (idx & 0x40)
        {
            reg3 ^= (uint8_t) i;
            reg2 ^= ~((uint8_t) i);
        }
    }

    /* Create non-inverted ECC code from line parity */
    tmp1  = (reg3 & 0x80) >> 0; /* B7 -> B7 */
    tmp1 |= (reg2 & 0x80) >> 1; /* B7 -> B6 */
    tmp1 |= (reg3 & 0x40) >> 1; /* B6 -> B5 */
    tmp1 |= (reg2 & 0x40) >> 2; /* B6 -> B4 */
    tmp1 |= (reg3 & 0x20) >> 2; /* B5 -> B3 */
    tmp1 |= (reg2 & 0x20) >> 3; /* B5 -> B2 */
    tmp1 |= (reg3 & 0x10) >> 3; /* B4 -> B1 */
    tmp1 |= (reg2 & 0x10) >> 4; /* B4 -> B0 */

    tmp2  = (reg3 & 0x08) << 4; /* B3 -> B7 */
    tmp2 |= (reg2 & 0x08) << 3; /* B3 -> B6 */
    tmp2 |= (reg3 & 0x04) << 3; /* B2 -> B5 */
    tmp2 |= (reg2 & 0x04) << 2; /* B2 -> B4 */
    tmp2 |= (reg3 & 0x02) << 2; /* B1 -> B3 */
    tmp2 |= (reg2 & 0x02) << 1; /* B1 -> B2 */
    tmp2 |= (reg3 & 0x01) << 1; /* B0 -> B1 */
    tmp2 |= (reg2 & 0x01) << 0; /* B7 -> B0 */

    /* Calculate final ECC code */
#ifdef CONFIG_MTD_NAND_ECC_SMC
    ecc_code[0] = ~tmp2;
    ecc_code[1] = ~tmp1;
#else
    ecc_code[0] = ~tmp1;
    ecc_code[1] = ~tmp2;
#endif
    ecc_code[2] = ((~reg1) << 2) | 0x03;

    return 0;
}
/*********nand_calculate_ecc function copy from uboot end*********************/
static void at91_nand_udelay(rt_uint32_t us)
{
    rt_uint32_t len;
    for (; us > 0; us --)
        for (len = 0; len < 10; len++);
}
static void wait_udelay()
{
    if (chip->pagesize == 2048)at91_nand_udelay(2000);
    else    at91_nand_udelay(1);
}
void nand_enable_cs(void)
{
    writel(0x00004000, 0xfffff834);
    readl(0xfffff838);
    //rt_kprintf("===i=0x%x\r\n",i);
    wait_udelay();
}
void nand_disable_cs(void)
{
    writeb(0xff, 0x40400000);
    writel(0x00004000, 0xfffff830);
    readl(0xfffff830);
    wait_udelay();
}

void nand_write_cmd(unsigned char cmd)
{
    writeb(cmd, CMD_REG);
    wait_udelay();
}
void nand_write_addr(unsigned char addr)
{
    writeb(addr, ADDR_REG);
    wait_udelay();
}
void nand_write_data_byte(unsigned char data)
{
    writeb(data, DATA_REG);
    wait_udelay();
}

unsigned char nand_read_data_byte(void)
{
    return readb(DATA_REG);
}

static int  nand_wait_ready(void)
{
    unsigned int timeout = 10000;

    nand_write_cmd(CMD_STATUS);
    while ((!(nand_read_data_byte() & STATUS_READY)) && timeout--);
    if (!timeout)return -1;
    return 0;
}

//----------------------------------------------------------------
/* read chip id */
static rt_err_t at9260_nand_read_id(struct rt_mtd_nand_device *device)
{
    int manf_id, dev_id;
    unsigned int chipid;
    unsigned int i;

    nand_enable_cs();

    nand_write_cmd(CMD_READID);
    nand_write_addr(CMD_READ_1);
    manf_id  = nand_read_data_byte();
    dev_id   = nand_read_data_byte();
    nand_disable_cs();

    chipid = (manf_id << 8) | dev_id;

    for (i = 0; i < ARRAY_SIZE(nand_ids); i++)
    {
        if (chipid == nand_ids[i].chip_id)
            break;
    }

    if (i == ARRAY_SIZE(nand_ids))
    {
        rt_kprintf("NAND: Not found Manufacturer ID: %x," \
            "Chip ID: 0x%x\n", manf_id, dev_id);
        return -1;
    }

    //find nand chip
    rt_kprintf("NAND: Manufacturer ID: %x Chip ID: %x Total Block:%d\n", manf_id, dev_id, nand_ids[i].numblocks);

    chip->numblocks = nand_ids[i].numblocks;
    chip->pagesize  = nand_ids[i].pagesize;
    chip->blocksize = nand_ids[i].blocksize;
    chip->oobsize   = nand_ids[i].oobsize;
    chip->buswidth  = nand_ids[i].buswidth;
    chip->numblocks = nand_ids[i].numblocks;

    bufsize = chip->pagesize + chip->oobsize;
    eccsize = (chip->pagesize) * 3 / 256;

    if (chip->pagesize == 512)
    {
        pages_per_block = 32;
        rt_kprintf("===small block pages===== \n");
    }
    else if (chip->pagesize == 2048)
    {
        pages_per_block = 64;
        rt_kprintf("===big   block pages===== \n");
    }

    return i;
}

int nand_read_page9260(unsigned int block, unsigned int page, unsigned char *data, rt_uint32_t data_len, unsigned char *spare, rt_uint32_t spare_len)
{
    int i = 0;
    unsigned int blockpage;
    unsigned char buff1[bufsize];

    blockpage = block * (pages_per_block) + page;
    memset(buff1, 0xff, bufsize);

    nand_enable_cs();
    nand_write_cmd(CMD_READ_A0);
    nand_write_addr(0);
    if (bufsize == 2112)nand_write_addr(0);
    nand_write_addr(blockpage & 0xff);
    nand_write_addr((blockpage >> 8) & 0xff);
    nand_write_addr((blockpage >> 16) & 0xff);

    at91_nand_udelay(2000);

    if (bufsize == 528)nand_write_cmd(CMD_READ_1);
    else if (bufsize == 2112)nand_write_cmd(CMD_READ_2);

    for (i = 0; i < chip->pagesize; i++)buff1[i] = nand_read_data_byte();
    for (i = 0; i < chip->oobsize; i++)buff1[i + chip->pagesize] = nand_read_data_byte();

    nand_wait_ready();
    nand_disable_cs();

    if (data != RT_NULL)
        rt_memcpy(data, buff1, data_len);
    if (spare != RT_NULL)
        rt_memcpy(spare, &buff1[chip->pagesize], spare_len);

    return 0x00;
}
//============================================================================
static rt_err_t at9260_nand_read_page(struct rt_mtd_nand_device *device,
                                      rt_off_t page,
                                      rt_uint8_t *data, rt_uint32_t data_len,
                                      rt_uint8_t *spare, rt_uint32_t spare_len)

{
    return nand_read_page9260(page / pages_per_block, page % pages_per_block, data, data_len, spare, spare_len);
}

int nand_write_page9260(unsigned int block, unsigned int page, unsigned char *data, rt_uint32_t data_len, unsigned char *spare, rt_uint32_t spare_len)
{
    unsigned int blockpage;
    unsigned char buff2[chip->pagesize];
    unsigned char se[chip->oobsize];
    unsigned char ecc_code[eccsize];
    int i = 0;

    blockpage = block * (pages_per_block) + page;
    memset(buff2, 0xff, chip->pagesize);
    memset(se, 0xff, chip->oobsize);
    memset(ecc_code, 0xff, eccsize);

    nand_enable_cs();
    nand_write_cmd(CMD_WRITE_1);

    nand_write_addr(0);
    if (bufsize == 2112)nand_write_addr(0);
    nand_write_addr(blockpage & 0xff);
    nand_write_addr((blockpage >> 8) & 0xff);
    nand_write_addr((blockpage >> 16) & 0xff);

    at91_nand_udelay(2000);

    for (i = 0; i < data_len; i++)buff2[i] = *(data + i);
    for (i = 0; i < chip->pagesize; i++)
    {
        nand_write_data_byte(buff2[i]);
    }

#ifndef RT_USING_DFS_UFFS
    if (bufsize == 528)
    {
        //caclu ECC
        nand_calculate_ecc(buff2, ecc_code);
        nand_calculate_ecc(&buff2[256], &ecc_code[3]);
        //use uboot MTD ECC layout
        for (i = 0; i < 6; i++)
        {
            se[nand_oob_16.eccpos[i]] = ecc_code[i];
        }
    }
    else if (bufsize == 2112)
    {
        //caclu ECC
        for (i = 0; i < 8; i++)
        {
            nand_calculate_ecc(&buff2[256 * i], &(ecc_code[3 * i]));
        }
        //use uboot MTD ECC layout
        for (i = 0; i < 24; i++)
        {
            se[nand_oob_64.eccpos[i]] = ecc_code[i];
        }
    }
#else
    //UFFS do ECC
    for (i = 0; i < chip->oobsize; i++)
    {
        se[i] = *(spare + i);
    }
#endif

    for (i = 0; i < chip->oobsize; i++)
    {
        nand_write_data_byte(se[i]);
    }

    nand_write_cmd(CMD_WRITE_2);
    nand_wait_ready();
    nand_disable_cs();

    return RT_EOK;
}
//===========================================================================================
static rt_err_t at9260_nand_write_page(struct rt_mtd_nand_device *device,
                                       rt_off_t page,
                                       rt_uint8_t *data, rt_uint32_t data_len,
                                       rt_uint8_t *oob, rt_uint32_t spare_len)
{

    return nand_write_page9260(page / pages_per_block, page % pages_per_block, data, data_len, oob, spare_len);
}
//===========================================================================================
static rt_err_t at9260_nand_move_page(struct rt_mtd_nand_device *device, rt_off_t src_page, rt_off_t dst_page)
{
    return RT_EOK;
}
//===========================================================================================
static long at9260_nand_isbad(struct rt_mtd_nand_device *nand, uint32_t blk)
{
    int i = 0;
    unsigned char buff2[bufsize];
    unsigned int blockpage = blk * (chip->blocksize / chip->pagesize) + 0;

    memset(buff2, 0xff, bufsize);

    //read blk page 0
    nand_enable_cs();
    nand_write_cmd(CMD_READ_A0);
    nand_write_addr(0);
    if (bufsize == 2112)nand_write_addr(0);
    nand_write_addr(blockpage & 0xff);
    nand_write_addr((blockpage >> 8) & 0xff);
    nand_write_addr((blockpage >> 16) & 0xff);

    at91_nand_udelay(2000);

    if (bufsize == 528)nand_write_cmd(CMD_READ_1);
    else if (bufsize == 2112)nand_write_cmd(CMD_READ_2);

    for (i = 0; i < bufsize; i++)
    {
        buff2[i] = nand_read_data_byte();
    }
    nand_disable_cs();

    if (bufsize == 528)
    {
        if (buff2[5 + 512] != 0xff)
        {
            rt_kprintf("\r\n Bad Block=0x%x: Cannot read page #0 of block #%d,addr=0x%x \n\r", buff2[5 + 512], blk, blk * 512 * 32);
            return buff2[5 + 512];
        }
    }
    else if (bufsize == 2112)
    {
        if ((buff2[2048 + 0] != 0xff) && (buff2[2048 + 1] != 0xff))
        {
            rt_kprintf("\r\n Bad Block=0x%x: Cannot read page #0 of block #%d,addr=0x%x \n\r", buff2[0 + 2048], blk, blk * 2048 * 64);
            return buff2[0 + 2048] << 8 | buff2[0 + 2048];
        }
    }

    //read blk page 1
    blockpage = blockpage + 1;
    memset(buff2, 0xff, bufsize);
    nand_enable_cs();
    nand_write_cmd(CMD_READ_A0);
    nand_write_addr(0);
    if (bufsize == 2112)nand_write_addr(0);
    nand_write_addr(blockpage & 0xff);
    nand_write_addr((blockpage >> 8) & 0xff);
    nand_write_addr((blockpage >> 16) & 0xff);
    at91_nand_udelay(2000);

    if (bufsize == 528)nand_write_cmd(CMD_READ_1);
    else if (bufsize == 2112)nand_write_cmd(CMD_READ_2);


    for (i = 0; i < bufsize; i++)
    {
        buff2[i] = nand_read_data_byte();
    }

    nand_disable_cs();

    if (bufsize == 528)
    {
        if (buff2[5 + 512] != 0xff)
        {
            rt_kprintf("\r\n Bad Block=0x%x: Cannot read page #1 of block #%d,addr=0x%x \n\r", buff2[5 + 512], blk, blk * 512 * 32);
            return buff2[5 + 512];
        }
    }
    else if (bufsize == 2112)
    {
        if ((buff2[2048 + 0] != 0xff) && (buff2[2048 + 1] != 0xff))
        {
            rt_kprintf("\r\n Bad Block=0x%x: Cannot read page #1 of block #%d,addr=0x%x \n\r", buff2[0 + 2048], blk, blk * 2048 * 64);
            return buff2[0 + 2048] << 8 | buff2[0 + 2048];
        }
    }

    return GOODBLOCK;
}

static long at9260_nand_markbad(struct rt_mtd_nand_device *nand, uint32_t blk)
{
    unsigned int i = 0;
    unsigned int blockpage = blk * (chip->blocksize / chip->pagesize) + 0;
    unsigned char bad_flag = 0xff;
    long ret_bad;

    ret_bad = at9260_nand_isbad(nand, blk);

    if (bufsize == 528)bad_flag = ret_bad & 0xff;
    else if (bufsize == 2112)
    {
        if (bad_flag == 0xff)bad_flag = (ret_bad >> 8) & 0xff;
    }

    if (bad_flag != 0xff)
    {
        nand_enable_cs();
        nand_write_cmd(CMD_WRITE_1);
        nand_write_addr(0);
        if (bufsize == 2112)nand_write_addr(0);
        nand_write_addr(blockpage & 0xff);
        nand_write_addr((blockpage >> 8) & 0xff);
        nand_write_addr((blockpage >> 16) & 0xff);
        at91_nand_udelay(2000);

        for (i = 0; i < bufsize; i++)
        {
            nand_write_data_byte(0x00);
        }

        nand_write_cmd(CMD_WRITE_2);
        nand_wait_ready();
        nand_disable_cs();
    }
    return RT_EOK;
}
//---------------------------------------------------------------------------------------------
/* erase block */
static rt_err_t at9260_nand_erase_block(struct rt_mtd_nand_device *device, rt_uint32_t block)
{
    unsigned int row_address;


    //Calculate address used for erase
    row_address = (block) * (chip->blocksize / chip->pagesize);

    nand_enable_cs();
    nand_write_cmd(CMD_ERASE_1);
    nand_write_addr(row_address & 0xff);
    nand_write_addr((row_address >> 8) & 0xff);
    nand_write_addr((row_address >> 16) & 0xff);
    nand_write_cmd(CMD_ERASE_2);

    at91_nand_udelay(2000);
    nand_wait_ready();
    nand_disable_cs();
    return RT_EOK;
}

const static struct rt_mtd_nand_driver_ops _ops =
{
    at9260_nand_read_id,
    at9260_nand_read_page,
    at9260_nand_write_page,
    at9260_nand_move_page,
    at9260_nand_erase_block,
#ifndef RT_USING_DFS_UFFS
    at9260_nand_isbad,
    at9260_nand_markbad,
#else
    RT_NULL,
    RT_NULL,
#endif
};

void nand_eraseall(void);

int rt_hw_mtd_nand_init(void)
{
    unsigned int i, reg, index;

    /* Setup Smart Media, first enable the address range of CS3 in HMATRIX user interface  */
    reg = readl(AT91C_BASE_CCFG + CCFG_EBICSA);
    reg |= AT91C_EBI_CS3A_SM;
    writel(reg, AT91C_BASE_CCFG + CCFG_EBICSA);
    /* Configure SMC CS3 */
    writel((AT91C_SMC_NWESETUP_(1) | AT91C_SMC_NCS_WRSETUP_(0)   | AT91C_SMC_NRDSETUP_(1) | AT91C_SMC_NCS_RDSETUP_(0)), AT91C_BASE_SMC + SMC_SETUP3);
    writel((AT91C_SMC_NWEPULSE_(3) | AT91C_SMC_NCS_WRPULSE_(3)   | AT91C_SMC_NRDPULSE_(3) | AT91C_SMC_NCS_RDPULSE_(3)), AT91C_BASE_SMC + SMC_PULSE3);
    writel((AT91C_SMC_NWECYCLE_(5) | AT91C_SMC_NRDCYCLE_(5)), AT91C_BASE_SMC + SMC_CYCLE3);
    writel((AT91C_SMC_READMODE  | AT91C_SMC_WRITEMODE   | (0x0 << 5) | AT91C_SMC_DBW_WIDTH_BITS_8 | AT91_SMC_TDF_(2)),    AT91C_BASE_SMC + SMC_CTRL3);
    /* {"NANDCS", AT91C_PIN_PC(14), 1, PIO_PULLUP, PIO_OUTPUT} */
    writel((0x01 << 14), 0xfffff800 + 0x0044);
    writel((0x01 << 14), 0xfffff800 + 0x0060);
    writel((0x01 << 14), 0xfffff800 + 0x0030);
    writel((0x01 << 14), 0xfffff800 + 0x0010);
    writel((0x01 << 14), 0xfffff800 + 0x0000);
    /* enable PIOC clock  */
    writel(0x01 << 4, 0x10 + AT91C_BASE_PMC);
    i = at9260_nand_read_id(RT_NULL);
    index = i;

    chip->pagesize  = nand_ids[index].pagesize;
    chip->blocksize = nand_ids[index].blocksize;
    chip->oobsize   = nand_ids[index].oobsize;
    chip->buswidth  = nand_ids[index].buswidth;
    chip->numblocks = nand_ids[index].numblocks;

    _partition[0].page_size = chip->pagesize;
    _partition[1].page_size = chip->pagesize;
    _partition[0].pages_per_block = chip->blocksize / chip->pagesize;
      _partition[1].pages_per_block = chip->blocksize / chip->pagesize;
    _partition[0].oob_size = _partition[1].oob_size = chip->oobsize;
    _partition[0].oob_free = _partition[1].oob_free = chip->oobsize - (chip->pagesize / 256 * 3); //oob_free = oob_size - ecc_size


    _partition[0].block_total  = DATA_PART_ADDR / (chip->blocksize);
    _partition[0].block_start  = 0;
    _partition[0].block_end    = DATA_PART_ADDR / (chip->blocksize) - 1;

    _partition[1].block_total  = chip->numblocks - _partition[0].block_total;
    _partition[1].block_start  = _partition[0].block_end + 1;
    _partition[1].block_end    = chip->numblocks - 1;

    _partition[0].ops = &_ops;
      _partition[1].ops = &_ops;

    rt_mtd_nand_register_device("nand0", &_partition[0]);
    rt_mtd_nand_register_device("nand1", &_partition[1]);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_mtd_nand_init);

#if defined(RT_USING_FINSH)
#include <finsh.h>
void nand_eraseall()
{
    int tmp=0;
    int index=0;


    if (chip->pagesize == 512)
        tmp = (DATA_PART_ADDR / 0x4000);            //0X4000=512*32=PAGER_SIZE*PAGES_PER_BLOCK
    else if (chip->pagesize == 2048)
        tmp = (DATA_PART_ADDR / 0x20000);                     //0X20000=2048*64

    for (index=tmp; index < chip->numblocks; index ++)
    {
        at9260_nand_erase_block(RT_NULL, index);
    }
}
FINSH_FUNCTION_EXPORT(nand_eraseall, erase all of block in the nand flash);

#endif //RT_USING_FINSH


