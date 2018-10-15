/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
   2018-09-10     heyuanjie87   first version

 */

#ifndef _MTDNAND_H_
#define _MTDNAND_H_

#include "mtd.h"

 /* Status bits */
#define NAND_STATUS_FAIL        0x01
#define NAND_STATUS_FAIL_N1     0x02
#define NAND_STATUS_WP          0x80

typedef enum
{
    NAND_CMD_PAGE_RD,   /* read data to chip's page buffer,do WaitBusy after this cmd in low driver */
    NAND_CMD_PAGE_WR0,  /* write data to chip's page buffer */
    NAND_CMD_PAGE_WR1,  /* do flash programe */
    NAND_CMD_BLK_ERASE, /* erase block */
    NAND_CMD_ECC_EN,    /* enable gen HWECC */
    NAND_CMD_ECC_DIS    /* disable gen HWECC */
} nand_cmd_t;

typedef enum
{
    NAND_ECCM_NONE,
    NAND_ECCM_HW,
} nand_eccmode_t;

struct nand_chip;
struct nand_ops;

/**
* struct nand_buffers - buffer structure for read/write
* @ecccalc:    buffer pointer for calculated ECC, size is oobsize.
* @ecccode:    buffer pointer for ECC read from flash, size is oobsize.
*
*/
struct nand_buffers
{
    uint8_t *ecccalc;
    uint8_t *ecccode;
};

struct nand_ecc
{
    uint8_t mode;    /* nand_eccmode_t */
    uint8_t bytes;   /* gen ecc bytes per ecc step(usually 3) */
    uint16_t stepsize:12; /* min 256 */
    uint16_t _step:4;     /*  */

    /* driver must set the two interface if HWECC */
    void (*calculate)(struct nand_chip *chip, const uint8_t *dat, uint8_t *ecc_code);
    /* return max bit flips if can't correct,return -1 ECC is error(0 success) */
    int(*correct)(struct nand_chip *chip, uint8_t *dat, uint8_t *read_ecc, uint8_t *calc_ecc);
    /* ignore if NONECC */
    const struct mtd_oob_region *layout;
};

typedef struct nand_chip
{
    rt_mtd_t parent;

    /* driver must init these */
    const struct nand_ops *ops;
    struct nand_ecc ecc;
    const struct mtd_oob_region *freelayout;

    /* driver do not touch */
    struct nand_buffers buffers;
    uint8_t *oob_poi;
    uint8_t *pagebuf;
    uint32_t size;
    uint16_t oobsize;
    uint8_t pages_pb;
    uint16_t page_size;
    int(*read_page)(struct nand_chip *chip, uint8_t *buf, int oob_required, int page);
    int(*write_page)(struct nand_chip *chip, const uint8_t *buf, int oob_required, int page);
}rt_nand_t;

struct nand_ops
{
    int(*cmdfunc)(rt_nand_t *nand, int cmd, int page, int offset); /* send nand operation cmd, return Status bits(0 success),
                                                                      if nand is busy please wait in low driver */
    int(*read_buf)(rt_nand_t *nand, uint8_t *buf, int len);        /* read data from nand chip's page buffer */
    int(*write_buf)(rt_nand_t *nand, const  uint8_t *buf, int len);/* write data to nand chip's page buffer */
    int(*isbad)(rt_nand_t *nand, uint32_t blk);   /* if NULL OOB[0] used as bad mark(not 0xff is bad) */
    int(*markbad)(rt_nand_t *nand, uint32_t blk); /* if NULL OOB[0] used as bad mark(set to 0x00) */
};

int rt_mtd_nand_init(rt_nand_t *nand, int blk_size, int page_size, int oob_size);

#endif /* MTD_NAND_H_ */
