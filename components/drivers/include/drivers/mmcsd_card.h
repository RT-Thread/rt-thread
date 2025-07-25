/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-07-25     weety         first version
 * 2024-05-24     HPMicro       add HS400 support
 * 2024-05-26     HPMicro       add UHS-I support for SD card
 */

#ifndef __MMCSD_CARD_H__
#define __MMCSD_CARD_H__

#include <drivers/mmcsd_host.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SD_SCR_BUS_WIDTH_1  (1 << 0)
#define SD_SCR_BUS_WIDTH_4  (1 << 2)

struct rt_mmcsd_cid {
    rt_uint8_t  mid;       /* ManufacturerID */
    rt_uint8_t  prv;       /* Product Revision */
    rt_uint16_t oid;       /* OEM/Application ID */
    rt_uint32_t psn;       /* Product Serial Number */
    rt_uint8_t  pnm[5];    /* Product Name */
    rt_uint8_t  reserved1;/* reserved */
    rt_uint16_t mdt;       /* Manufacturing Date */
    rt_uint8_t  crc;       /* CID CRC */
    rt_uint8_t  reserved2;/* not used, always 1 */
};

struct rt_mmcsd_csd {
    rt_uint8_t      csd_structure;  /* CSD register version */
    rt_uint8_t      taac;
    rt_uint8_t      nsac;
    rt_uint8_t      tran_speed; /* max data transfer rate */
    rt_uint16_t     card_cmd_class; /* card command classes */
    rt_uint8_t      rd_blk_len; /* max read data block length */
    rt_uint8_t      rd_blk_part;
    rt_uint8_t      wr_blk_misalign;
    rt_uint8_t      rd_blk_misalign;
    rt_uint8_t      dsr_imp;    /* DSR implemented */
    rt_uint8_t      c_size_mult;    /* CSD 1.0 , device size multiplier */
    rt_uint32_t     c_size;     /* device size */
    rt_uint8_t      r2w_factor;
    rt_uint8_t      wr_blk_len; /* max wtire data block length */
    rt_uint8_t      wr_blk_partial;
    rt_uint8_t      csd_crc;

};

struct rt_sd_scr {
    rt_uint8_t      sd_version;
    rt_uint8_t      sd_bus_widths;
};

struct rt_sdio_cccr {
    rt_uint8_t      sdio_version;
    rt_uint8_t      sd_version;
    rt_uint8_t      direct_cmd:1,     /*  Card Supports Direct Commands during data transfer
                                                   only SD mode, not used for SPI mode */
                multi_block:1,    /*  Card Supports Multi-Block */
                read_wait:1,      /*  Card Supports Read Wait
                                       only SD mode, not used for SPI mode */
                suspend_resume:1, /*  Card supports Suspend/Resume
                                       only SD mode, not used for SPI mode */
                s4mi:1,            /* generate interrupts during a 4-bit
                                      multi-block data transfer */
                e4mi:1,            /*  Enable the multi-block IRQ during
                                       4-bit transfer for the SDIO card */
                low_speed:1,      /*  Card  is  a  Low-Speed  card */
                low_speed_4:1;    /*  4-bit support for Low-Speed cards */

    rt_uint8_t      bus_width:1,     /* Support SDIO bus width, 1:4bit, 0:1bit */
                cd_disable:1,    /*  Connect[0]/Disconnect[1] the 10K-90K ohm pull-up
                                     resistor on CD/DAT[3] (pin 1) of the card */
                power_ctrl:1,    /* Support Master Power Control */
                high_speed:1;    /* Support High-Speed  */


};

/*
 * SD Status
 */
union rt_sd_status {
    rt_uint32_t status_words[16];
    struct {
        rt_uint32_t reserved[12];
        rt_uint64_t : 8;
        rt_uint64_t uhs_au_size: 4;
        rt_uint64_t uhs_speed_grade: 4;
        rt_uint64_t erase_offset: 2;
        rt_uint64_t erase_timeout: 6;
        rt_uint64_t erase_size: 16;
        rt_uint64_t : 4;
        rt_uint64_t au_size: 4;
        rt_uint64_t performance_move: 8;
        rt_uint64_t speed_class: 8;

        rt_uint32_t size_of_protected_area;

        rt_uint32_t sd_card_type: 16;
        rt_uint32_t : 6;
        rt_uint32_t : 7;
        rt_uint32_t secured_mode: 1;
        rt_uint32_t data_bus_width: 2;
    };
};

/*
 * SD Speed Class
 */
#define SD_SPEED_CLASS_0    0
#define SD_SPEED_CLASS_2    1
#define SD_SPEED_CLASS_4    2
#define SD_SPEED_CLASS_6    3
#define SD_SPEED_CLASS_10   4

/*
 * UHS Speed Grade
 */
#define UHS_SPEED_GRADE_0   0
#define UHS_SPEED_GRADE_1   1
#define UHS_SPEED_GRADE_3   3


struct rt_sdio_cis {
    rt_uint16_t     manufacturer;
    rt_uint16_t     product;
    rt_uint16_t     func0_blk_size;
    rt_uint32_t     max_tran_speed;
};

/*
 * SDIO function CIS tuple (unknown to the core)
 */
struct rt_sdio_function_tuple {
    struct rt_sdio_function_tuple *next;
    rt_uint8_t code;
    rt_uint8_t size;
    rt_uint8_t *data;
};

struct rt_sdio_function;
typedef void (rt_sdio_irq_handler_t)(struct rt_sdio_function *);

/*
 * SDIO function devices
 */
struct rt_sdio_function {
    struct rt_mmcsd_card        *card;      /* the card this device belongs to */
    rt_sdio_irq_handler_t   *irq_handler;   /* IRQ callback */
    rt_uint8_t      num;        /* function number */

    rt_uint8_t      func_code;   /*  Standard SDIO Function interface code  */
    rt_uint16_t     manufacturer;       /* manufacturer id */
    rt_uint16_t     product;        /* product id */

    rt_uint32_t     max_blk_size;   /* maximum block size */
    rt_uint32_t     cur_blk_size;   /* current block size */

    rt_uint32_t     enable_timeout_val; /* max enable timeout in msec */

    struct rt_sdio_function_tuple *tuples;

    void            *priv;
};

#define SDIO_MAX_FUNCTIONS      7

struct rt_mmc_ext_csd
{
    rt_uint32_t cache_size;
    rt_uint32_t enhanced_data_strobe;
};

struct rt_mmcsd_card {
    struct rt_mmcsd_host *host;
    rt_uint32_t rca;        /* card addr */
    rt_uint32_t resp_cid[4];    /* card CID register */
    rt_uint32_t resp_csd[4];    /* card CSD register */
    rt_uint32_t resp_scr[2];    /* card SCR register */

    rt_uint16_t tacc_clks;  /* data access time by ns */
    rt_uint32_t tacc_ns;    /* data access time by clk cycles */
    rt_uint32_t max_data_rate;  /* max data transfer rate */
    rt_uint32_t card_capacity;  /* card capacity, unit:KB */
    rt_uint32_t card_blksize;   /* card block size */
    rt_uint32_t card_sec_cnt;   /* card sector count*/
    rt_uint32_t erase_size; /* erase size in sectors */
    rt_uint16_t card_type;
#define CARD_TYPE_MMC                   0 /* MMC card */
#define CARD_TYPE_SD                    1 /* SD card */
#define CARD_TYPE_SDIO                  2 /* SDIO card */
#define CARD_TYPE_SDIO_COMBO            3 /* SD combo (IO+mem) card */

    rt_uint16_t flags;
#define CARD_FLAG_HIGHSPEED  (1 << 0)   /* SDIO bus speed 50MHz */
#define CARD_FLAG_SDHC       (1 << 1)   /* SDHC card */
#define CARD_FLAG_SDXC       (1 << 2)   /* SDXC card */
#define CARD_FLAG_HIGHSPEED_DDR  (1 << 3)   /* HIGH SPEED DDR */
#define CARD_FLAG_HS200      (1 << 4)   /* BUS SPEED 200MHz */
#define CARD_FLAG_HS400      (1 << 5)   /* BUS SPEED 400MHz */
#define CARD_FLAG_SDR50      (1 << 6)   /* BUS SPEED 100MHz */
#define CARD_FLAG_SDR104     (1 << 7)   /* BUS SPEED 200MHz */
#define CARD_FLAG_DDR50      (1 << 8)   /* DDR50, works on 1.8V only */
    struct rt_sd_scr    scr;
    struct rt_mmcsd_csd csd;
    rt_uint32_t     hs_max_data_rate;  /* max data transfer rate in high speed mode */

    rt_uint8_t      sdio_function_num;  /* total number of SDIO functions */
    struct rt_sdio_cccr    cccr;  /* common card info */
    struct rt_sdio_cis     cis;  /* common tuple info */
    struct rt_sdio_function *sdio_function[SDIO_MAX_FUNCTIONS + 1]; /* SDIO functions (devices) */
    void *blk_dev;

    struct rt_mmc_ext_csd ext_csd;
};

#ifdef __cplusplus
}
#endif

#endif
