/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
 /*
 * spi_fh_adapt.h
 *
 *  Created on: Mar 2, 2016
 *      Author: duobao
 */

#ifndef SPI_FH_ADAPT_H_
#define SPI_FH_ADAPT_H_

#include <rtthread.h>
#include <drivers/spi.h>

#define MTD_WRITEABLE       0x400   /* Device is writeable */
#define MTD_BIT_WRITEABLE   0x800   /* Single bits can be flipped */
#define MTD_NO_ERASE        0x1000  /* No erase necessary */
#define MTD_POWERUP_LOCK    0x2000  /* Always locked after reset */

struct mtd_partition {
    char *name;                 /* identifier string */
    rt_uint32_t size;              /* partition size */
    rt_uint32_t offset;            /* offset within the master MTD space */
    rt_uint32_t mask_flags;        /* master MTD flags to mask out for this partition */
    struct nand_ecclayout *ecclayout;   /* out of band layout for this partition (NAND only) */
};

struct flash_platform_data {
    char        *flash_name;
    char        *spi_name;
    struct mtd_partition *parts;
    unsigned int    nr_parts;

    char        *type;

    /* we'll likely add more ... use JEDEC IDs, etc */
};


rt_err_t fh_flash_adapt_init(void);
#endif /* SPI_FH_ADAPT_H_ */





