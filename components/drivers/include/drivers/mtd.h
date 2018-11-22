/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
   2018-09-10     heyuanjie87   first version

 */

#ifndef __MTD_H__
#define __MTD_H__

#include <rtthread.h>
#include <stddef.h>
#include <stdint.h>

#define MTD_TYPE_NOR    1
#define MTD_TYPE_NAND   2

 /**
  * MTD operation modes
  *
  * @MTD_OPM_PLACE_OOB:	OOB data are placed at the given offset (default)
  * @MTD_OPM_AUTO_OOB:	OOB data are automatically placed at the free areas
  * @MTD_OPM_RAW:	    data are transferred as-is, with no error correction;
  */
enum mtd_opm
{
    MTD_OPM_PLACE_OOB = 0,
    MTD_OPM_AUTO_OOB = 1,
    MTD_OPM_RAW = 2,
};

#ifndef loff_t
typedef long loff_t;
#endif

struct mtd_oob_region
{
    uint8_t offset;
    uint8_t length;
};

typedef struct mtd_info
{
    struct rt_device parent;

    const struct mtd_ops *ops;

    uint16_t oob_size;
    uint16_t sector_size;   /* Minimal writable flash unit size */
    uint32_t block_size:28; /* Erase size for the device */
    uint32_t type:4;

    size_t size;    /* Total size of the MTD */
    loff_t offset;  /* At which this MTD starts, from the beginning of the MEMORY */
    struct mtd_info *master;

    void *priv;
}rt_mtd_t;

struct mtd_io_desc
{
    uint8_t mode;      /* operation mode(enum mtd_opm) */
    uint8_t ooblen;    /* number of oob bytes to write/read */
    uint8_t oobretlen; /* number of oob bytes written/read */
    uint8_t ooboffs;   /* offset in the oob area  */
    uint8_t *oobbuf;

    size_t  datlen;    /* number of data bytes to write/read */
    size_t  datretlen; /* number of data bytes written/read */
    uint8_t *datbuf;   /* if NULL only oob are read/written */
};

struct mtd_ops
{
    int(*erase)(rt_mtd_t *mtd, loff_t addr, size_t len);    /* return 0 if success */
    int(*read) (rt_mtd_t *mtd, loff_t from, struct mtd_io_desc *ops); /* return 0 if success */
    int(*write) (rt_mtd_t *mtd, loff_t to, struct mtd_io_desc *ops);  /* return 0 if success */
    int(*isbad) (rt_mtd_t *mtd, uint32_t block);    /* return 1 if bad, 0 not bad */
    int(*markbad) (rt_mtd_t *mtd, uint32_t block);  /* return 0 if success */
};

struct mtd_part
{
    const char *name;           /* name of the MTD partion */
    loff_t offset;              /* start addr of partion */
    size_t size;                /* size of partion */
};

int rt_mtd_erase(rt_mtd_t *mtd, loff_t addr, size_t size);
int rt_mtd_block_erase(rt_mtd_t *mtd, uint32_t block);
int rt_mtd_read_oob(rt_mtd_t *mtd, loff_t from, struct mtd_io_desc *desc);
int rt_mtd_write_oob(rt_mtd_t *mtd, loff_t to, struct mtd_io_desc *desc);
int rt_mtd_read(rt_mtd_t *mtd, loff_t from, uint8_t *buf, size_t len);
int rt_mtd_write(rt_mtd_t *mtd, loff_t to, const uint8_t *buf, size_t len);
int rt_mtd_block_markbad(rt_mtd_t *mtd, uint32_t block);
int rt_mtd_block_isbad(rt_mtd_t *mtd, uint32_t block);

rt_mtd_t* rt_mtd_get(const char *name);
int rt_mtd_register(rt_mtd_t *master, const struct mtd_part *parts, int np);

#endif
