/*
 * (C) Copyright 2005
 * 2N Telekomunikace, a.s. <www.2n.cz>
 * Ladislav Michl <michl@2n.cz>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef _NAND_H_
#define _NAND_H_

//#include <config.h>
#define CONFIG_SYS_MAX_NAND_DEVICE  1

/*
 * All boards using a given driver must convert to self-init
 * at the same time, so do it here.  When all drivers are
 * converted, this will go away.
 */
#ifdef CONFIG_SPL_BUILD
    #if defined(CONFIG_NAND_FSL_ELBC) || defined(CONFIG_NAND_FSL_IFC)
        #define CONFIG_SYS_NAND_SELF_INIT
    #endif
#else
    #if defined(CONFIG_NAND_FSL_ELBC) || defined(CONFIG_NAND_ATMEL)\
        || defined(CONFIG_NAND_FSL_IFC)
        #define CONFIG_SYS_NAND_SELF_INIT
    #endif
#endif

extern int nand_init(void);

//#include <linux/compat.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>

int nand_mtd_to_devnum(struct mtd_info *mtd);

#ifdef CONFIG_SYS_NAND_SELF_INIT
    void board_nand_init(void);
    int nand_register(int devnum, struct mtd_info *mtd);
#else
    extern int board_nand_init(struct nand_chip *nand);
#endif

typedef struct mtd_info nand_info_t;

extern int nand_curr_device;
extern nand_info_t *nand_info[];

static __inline int nand_read(struct mtd_info *info, loff_t ofs, size_t *len,
                              u_char *buf)
{
    return mtd_read(info, ofs, *len, (size_t *)len, buf);
}

static __inline int nand_write(struct mtd_info *info, loff_t ofs, size_t *len,
                               u_char *buf)
{
    return mtd_write(info, ofs, *len, (size_t *)len, buf);
}

static __inline int nand_block_isbad(struct mtd_info *info, loff_t ofs)
{
    return mtd_block_isbad(info, ofs);
}

static __inline int nand_erase(struct mtd_info *info, loff_t off, size_t size)
{
    struct erase_info instr;

    instr.mtd = info;
    instr.addr = off;
    instr.len = size;
    instr.callback = 0;

    return mtd_erase(info, &instr);
}


/*****************************************************************************
 * declarations from nand_util.c
 ****************************************************************************/

typedef struct mtd_oob_ops mtd_oob_ops_t;

struct nand_erase_options
{
    loff_t length;      /* number of bytes to erase */
    loff_t offset;      /* first address in NAND to erase */
    int quiet;      /* don't display progress messages */
    int jffs2;      /* if true: format for jffs2 usage
                 * (write appropriate cleanmarker blocks) */
    int scrub;      /* if true, really clean NAND by erasing
                 * bad blocks (UNSAFE) */

    /* Don't include skipped bad blocks in size to be erased */
    int spread;
    /* maximum size that actual may be in order to not exceed the buf */
    loff_t lim;
};

typedef struct nand_erase_options nand_erase_options_t;

int nand_read_skip_bad(struct mtd_info *mtd, loff_t offset, size_t *length,
                       size_t *actual, loff_t lim, u_char *buffer);

#define WITH_DROP_FFS   (1 << 0) /* drop trailing all-0xff pages */
#define WITH_WR_VERIFY  (1 << 1) /* verify data was written correctly */

int nand_write_skip_bad(struct mtd_info *mtd, loff_t offset, size_t *length,
                        size_t *actual, loff_t lim, u_char *buffer, int flags);
int nand_erase_opts(struct mtd_info *mtd,
                    const nand_erase_options_t *opts);
int nand_torture(struct mtd_info *mtd, loff_t offset);
int nand_verify_page_oob(struct mtd_info *mtd, struct mtd_oob_ops *ops,
                         loff_t ofs);
int nand_verify(struct mtd_info *mtd, loff_t ofs, size_t len, u_char *buf);

#define NAND_LOCK_STATUS_TIGHT  0x01
#define NAND_LOCK_STATUS_UNLOCK 0x04

int nand_lock(struct mtd_info *mtd, int tight);
int nand_unlock(struct mtd_info *mtd, loff_t start, size_t length,
                int allexcept);
int nand_get_lock_status(struct mtd_info *mtd, loff_t offset);

int nand_spl_load_image(uint32_t offs, unsigned int size, void *dst);
int nand_spl_read_block(int block, int offset, int len, void *dst);
void nand_deselect(void);

#ifdef CONFIG_SYS_NAND_SELECT_DEVICE
    void board_nand_select_device(struct nand_chip *nand, int chip);
#endif

__attribute__((noreturn)) void nand_boot(void);

#endif
