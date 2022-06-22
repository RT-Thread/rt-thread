/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2011-07-25     weety     first version
 */

#ifndef __HOST_H__
#define __HOST_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

struct rt_mmcsd_io_cfg {
    rt_uint32_t clock;          /* clock rate */
    rt_uint16_t vdd;

/* vdd stores the bit number of the selected voltage range from below. */

    rt_uint8_t  bus_mode;       /* command output mode */

#define MMCSD_BUSMODE_OPENDRAIN 1
#define MMCSD_BUSMODE_PUSHPULL  2

    rt_uint8_t  chip_select;        /* SPI chip select */

#define MMCSD_CS_IGNORE     0
#define MMCSD_CS_HIGH       1
#define MMCSD_CS_LOW        2

    rt_uint8_t  power_mode;     /* power supply mode */

#define MMCSD_POWER_OFF     0
#define MMCSD_POWER_UP      1
#define MMCSD_POWER_ON      2

    rt_uint8_t  bus_width;      /* data bus width */

#define MMCSD_BUS_WIDTH_1       0
#define MMCSD_BUS_WIDTH_4       2
#define MMCSD_BUS_WIDTH_8       3
#define MMCSD_DDR_BUS_WIDTH_4   4
#define MMCSD_DDR_BUS_WIDTH_8   5
};

struct rt_mmcsd_host;
struct rt_mmcsd_req;

struct rt_mmcsd_host_ops {
    void (*request)(struct rt_mmcsd_host *host, struct rt_mmcsd_req *req);
    void (*set_iocfg)(struct rt_mmcsd_host *host, struct rt_mmcsd_io_cfg *io_cfg);
    rt_int32_t (*get_card_status)(struct rt_mmcsd_host *host);
    void (*enable_sdio_irq)(struct rt_mmcsd_host *host, rt_int32_t en);
};

struct rt_mmcsd_host {
    struct rt_mmcsd_card *card;
    const struct rt_mmcsd_host_ops *ops;
    rt_uint32_t  freq_min;
    rt_uint32_t  freq_max;
    struct rt_mmcsd_io_cfg io_cfg;
    rt_uint32_t  valid_ocr; /* current valid OCR */
#define VDD_165_195     (1 << 7)    /* VDD voltage 1.65 - 1.95 */
#define VDD_20_21       (1 << 8)    /* VDD voltage 2.0 ~ 2.1 */
#define VDD_21_22       (1 << 9)    /* VDD voltage 2.1 ~ 2.2 */
#define VDD_22_23       (1 << 10)   /* VDD voltage 2.2 ~ 2.3 */
#define VDD_23_24       (1 << 11)   /* VDD voltage 2.3 ~ 2.4 */
#define VDD_24_25       (1 << 12)   /* VDD voltage 2.4 ~ 2.5 */
#define VDD_25_26       (1 << 13)   /* VDD voltage 2.5 ~ 2.6 */
#define VDD_26_27       (1 << 14)   /* VDD voltage 2.6 ~ 2.7 */
#define VDD_27_28       (1 << 15)   /* VDD voltage 2.7 ~ 2.8 */
#define VDD_28_29       (1 << 16)   /* VDD voltage 2.8 ~ 2.9 */
#define VDD_29_30       (1 << 17)   /* VDD voltage 2.9 ~ 3.0 */
#define VDD_30_31       (1 << 18)   /* VDD voltage 3.0 ~ 3.1 */
#define VDD_31_32       (1 << 19)   /* VDD voltage 3.1 ~ 3.2 */
#define VDD_32_33       (1 << 20)   /* VDD voltage 3.2 ~ 3.3 */
#define VDD_33_34       (1 << 21)   /* VDD voltage 3.3 ~ 3.4 */
#define VDD_34_35       (1 << 22)   /* VDD voltage 3.4 ~ 3.5 */
#define VDD_35_36       (1 << 23)   /* VDD voltage 3.5 ~ 3.6 */
    rt_uint32_t  flags; /* define device capabilities */
#define MMCSD_BUSWIDTH_4    (1 << 0)
#define MMCSD_BUSWIDTH_8    (1 << 1)
#define MMCSD_MUTBLKWRITE   (1 << 2)
#define MMCSD_HOST_IS_SPI   (1 << 3)
#define controller_is_spi(host) (host->flags & MMCSD_HOST_IS_SPI)
#define MMCSD_SUP_SDIO_IRQ  (1 << 4)    /* support signal pending SDIO IRQs */
#define MMCSD_SUP_HIGHSPEED (1 << 5)    /* support high speed */
#define MMCSD_SUP_HIGHSPEED_DDR     (1 << 6)    /* support high speed(DDR) */
#define MMCSD_SUP_HIGHSPEED_HS200   (1 << 7)    /* support high speed HS200 */
#define MMCSD_SUP_HIGHSPEED_HS400   (1 << 8)    /* support high speed HS400 */

    rt_uint32_t max_seg_size;   /* maximum size of one dma segment */
    rt_uint32_t max_dma_segs;   /* maximum number of dma segments in one request */
    rt_uint32_t max_blk_size;   /* maximum block size */
    rt_uint32_t max_blk_count;  /* maximum block count */

    rt_uint32_t id;          /* Assigned host id */

    rt_uint32_t   spi_use_crc;
    struct rt_mutex  bus_lock;
    struct rt_semaphore  sem_ack;

    rt_uint32_t       sdio_irq_num;
    struct rt_semaphore    *sdio_irq_sem;
    struct rt_thread     *sdio_irq_thread;

    void *private_data;
};

rt_inline void mmcsd_delay_ms(rt_uint32_t ms)
{
    if (ms < 1000 / RT_TICK_PER_SECOND)
    {
        rt_thread_delay(1);
    }
    else
    {
        rt_thread_delay(ms/(1000 / RT_TICK_PER_SECOND));
    }
}

#ifdef __cplusplus
}
#endif

#endif
