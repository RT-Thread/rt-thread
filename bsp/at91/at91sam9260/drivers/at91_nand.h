/*
* Copyright (c) 2006-2022, RT-Thread Development Team
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date           Author        Notes
* 2022-01-08     brightsally   first version
*/

#ifndef _ATMEL_NAND_H_
#define _ATMEL_NAND_H_


/* NAND flash */
#define DATA_PART_ADDR                  0x900000                /*nand0=0-9MB;nand1=9MB-END*/

#define AT91C_BASE_CCFG                 0xffffef14
#define CCFG_EBICSA                     0x08                    /* EBI Chip Select Assignement Register */
#define AT91C_EBI_CS3A_SM               (0x1UL << 3)
#define AT91C_BASE_SMC                  0xffffec00
#define AT91C_BASE_PMC                  0xfffffc00
#define SMC_SETUP3                      0x30                    /* Setup Register for CS 3 */
#define SMC_PULSE3                      0x34                    /* Pulse Register for CS 3 */
#define SMC_CYCLE3                      0x38                    /* Cycle Register for CS 3 */
#define SMC_CTRL3                       0x3C                    /* Control Register for CS 3 */

#define AT91C_SMC_NWESETUP_(x)          ((x) << 0)
#define AT91C_SMC_NCS_WRSETUP_(x)       ((x) << 8)
#define AT91C_SMC_NRDSETUP_(x)          ((x) << 16)
#define AT91C_SMC_NCS_RDSETUP_(x)       ((x) << 24)
#define AT91C_SMC_NWEPULSE_(x)          ((x) << 0)
#define AT91C_SMC_NCS_WRPULSE_(x)       ((x) << 8)
#define AT91C_SMC_NRDPULSE_(x)          ((x) << 16)
#define AT91C_SMC_NCS_RDPULSE_(x)       ((x) << 24)

#define AT91C_SMC_NWECYCLE_(x)          ((x) << 0)
#define AT91C_SMC_NRDCYCLE_(x)          ((x) << 16)

#define AT91C_SMC_READMODE              (0x1UL << 0)
#define AT91C_SMC_WRITEMODE             (0x1UL << 1)
#define AT91C_SMC_NWAITM                (0x3UL << 4)
#define AT91C_SMC_DBW_WIDTH_BITS_8      (0x0UL << 12)
#define AT91C_SMC_DBW_WIDTH_BITS_16     (0x1UL << 12)
#define AT91C_SMC_DBW_WIDTH_BITS_32     (0x2UL << 12)
#define AT91C_SMC_TDF                   (0xFUL << 16)
#define AT91_SMC_TDF_(x)                ((x) << 16)

#define CMD_STATUS                      0x70
#define STATUS_READY                    (0x01 << 6)   /* Status code for Ready */
#define STATUS_ERROR                    (0x01 << 0)   /* Status code for Error */

/* Nand flash commands */
#define CMD_READID                      0x90
#define CMD_READ_1                      0x00
#define CMD_READ_2                      0x30

#define CMD_READ_A0                     0x00
#define CMD_READ_A1                     0x01
#define CMD_READ_C                      0x50

#define CMD_WRITE_A                     0x00
#define CMD_WRITE_C                     0x50

#define CMD_WRITE_1                     0x80
#define CMD_WRITE_2                     0x10

#define CMD_ERASE_1                     0x60
#define CMD_ERASE_2                     0xD0

/* read/write/move page */
#define CMD_REG                         0x40400000
#define ADDR_REG                        0x40200000
#define DATA_REG                        0x40000000

/*Values returned by the CheckBlock() function
GOOD = RT_EOK=0
BAD = -1
*/
#define BADBLOCK        -RT_ERROR       //-1
#define GOODBLOCK        RT_EOK         //0

struct nand_oobfree
{
    unsigned int offset;
    unsigned int length;
};

struct nand_ecclayout
{
    unsigned int eccbytes;
    unsigned int eccpos[680];
    unsigned int oobavail;
    struct nand_oobfree oobfree[32];
};

struct nand_chip_id
{
    unsigned short  chip_id;            /* Nand Chip ID */
    unsigned short  numblocks;          //0x1000=4096=4K            //4K*16K=64M
    unsigned int    blocksize;          //0x4000=16K                //SECTOR
    unsigned short  pagesize;           //0X200=512                 //1 BLOCK has pages=16K/512=32
    unsigned char   oobsize;            //0X10=16
    unsigned char   buswidth;
};
static struct nand_chip_id nand_ids[] =
{

    /* Samsung 32MB 8Bit SMALL BLOCK*/
    {0xec75, 0x800, 0x4000,  0x200, 0x10, 0x0},    //32M
    {0xec35, 0x800, 0x4000,  0x200, 0x10, 0x0},    //32M
    {0xec36, 0x1000, 0x4000,  0x200, 0x10, 0x0},   //4K*16K=64M
    /* Samsung 128MB 8bit BIG BLOCK*/
    {0xeca1, 0x400, 0x20000, 0x800, 0x40, 0x0},    //128M
    {0,}
};


int rt_hw_mtd_nand_init(void);
#endif
