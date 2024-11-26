/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2024-08-16     zhujiale     first version
 */
#ifndef __SDHCI_MMC_H__
#define __SDHCI_MMC_H__

#include <rtthread.h>
#include <drivers/mmcsd_cmd.h>
#include <drivers/dev_mmcsd_core.h>
#include <drivers/mmcsd_host.h>
#include "sdhci_dma.h"
#define mmc_dev(x) ((x)->parent)

#define MMC_SEND_TUNING_BLOCK_HS200 SEND_TUNING_BLOCK_HS200
#define MMC_SEND_TUNING_BLOCK       SEND_TUNING_BLOCK
#define MMC_STOP_TRANSMISSION       STOP_TRANSMISSION
#define MMC_BUS_TEST_R              14 /* adtc                    R1  */
#define MMC_WRITE_MULTIPLE_BLOCK    WRITE_MULTIPLE_BLOCK
#define MMC_READ_MULTIPLE_BLOCK     READ_MULTIPLE_BLOCK

#define MMC_TIMING_UHS_DDR50  MMCSD_TIMING_UHS_DDR50
#define MMC_TIMING_UHS_SDR50  MMCSD_TIMING_UHS_SDR50
#define MMC_TIMING_MMC_HS200  MMCSD_TIMING_MMC_HS200
#define MMC_TIMING_MMC_HS400  MMCSD_TIMING_MMC_HS400
#define MMC_TIMING_UHS_SDR104 MMCSD_TIMING_UHS_SDR104
#define MMC_TIMING_UHS_SDR25  MMCSD_TIMING_UHS_SDR25
#define MMC_TIMING_MMC_DDR52  MMCSD_TIMING_MMC_DDR52
#define MMC_TIMING_UHS_SDR12  MMCSD_TIMING_UHS_SDR12
#define MMC_TIMING_SD_HS      MMCSD_TIMING_SD_HS
#define MMC_TIMING_MMC_HS     MMCSD_TIMING_MMC_HS

#define MMC_POWER_OFF       MMCSD_POWER_OFF
#define MMC_POWER_UP        MMCSD_POWER_UP
#define MMC_POWER_ON        MMCSD_POWER_ON
#define MMC_POWER_UNDEFINED 3

#define MMC_SET_DRIVER_TYPE_B 0
#define MMC_SET_DRIVER_TYPE_A 1
#define MMC_SET_DRIVER_TYPE_C 2
#define MMC_SET_DRIVER_TYPE_D 3

#define MMC_SIGNAL_VOLTAGE_330 0
#define MMC_SIGNAL_VOLTAGE_180 1
#define MMC_SIGNAL_VOLTAGE_120 2

#define MMC_RSP_PRESENT (1 << 16)
#define MMC_RSP_136     (1 << 17) /* 136 bit response */
#define MMC_RSP_CRC     (1 << 18) /* expect valid crc */
#define MMC_RSP_BUSY    (1 << 19) /* card may send busy */
#define MMC_RSP_OPCODE  (1 << 20) /* response contains opcode */

/*
 * These are the native response types, and correspond to valid bit
 * patterns of the above flags.  One additional valid pattern
 * is all zeros, which means we don't expect a response.
 */
#define MMC_RSP_NONE (0)
#define MMC_RSP_R1   (MMC_RSP_PRESENT | MMC_RSP_CRC | MMC_RSP_OPCODE)
#define MMC_RSP_R1B  (MMC_RSP_PRESENT | MMC_RSP_CRC | MMC_RSP_OPCODE | MMC_RSP_BUSY)
#define MMC_RSP_R2   (MMC_RSP_PRESENT | MMC_RSP_136 | MMC_RSP_CRC)
#define MMC_RSP_R3   (MMC_RSP_PRESENT)
#define MMC_RSP_R4   (MMC_RSP_PRESENT)
#define MMC_RSP_R5   (MMC_RSP_PRESENT | MMC_RSP_CRC | MMC_RSP_OPCODE)
#define MMC_RSP_R6   (MMC_RSP_PRESENT | MMC_RSP_CRC | MMC_RSP_OPCODE)
#define MMC_RSP_R7   (MMC_RSP_PRESENT | MMC_RSP_CRC | MMC_RSP_OPCODE)

#define MMC_CMD_ADTC CMD_ADTC

#define MMC_BUS_WIDTH_8 MMCSD_BUS_WIDTH_8
#define MMC_BUS_WIDTH_4 MMCSD_BUS_WIDTH_4
#define MMC_BUS_WIDTH_1 MMCSD_BUS_WIDTH_1

#define MMC_PM_KEEP_POWER    (1 << 0) /* preserve card power during suspend */
#define MMC_PM_WAKE_SDIO_IRQ (1 << 1) /* wake up host system on SDIO IRQ assertion */
enum mmc_blk_status
{
    MMC_BLK_SUCCESS = 0,
    MMC_BLK_PARTIAL,
    MMC_BLK_CMD_ERR,
    MMC_BLK_RETRY,
    MMC_BLK_ABORT,
    MMC_BLK_DATA_ERR,
    MMC_BLK_ECC_ERR,
    MMC_BLK_NOMEDIUM,
    MMC_BLK_NEW_REQUEST,
};

/************************************************************************************************ */

#define MMC_NUM_CLK_PHASES (MMC_TIMING_MMC_HS400 + 1)

struct mmc_host;

struct mmc_host_ops
{
    /*
     * It is optional for the host to implement pre_req and post_req in
     * order to support double buffering of requests (prepare one
     * request while another request is active).
     * pre_req() must always be followed by a post_req().
     * To undo a call made to pre_req(), call post_req() with
     * a nonzero err condition.
     */
    void (*post_req)(struct mmc_host *host, struct rt_mmcsd_req *req,
                     int err);
    void (*pre_req)(struct mmc_host *host, struct rt_mmcsd_req *req);
    void (*request)(struct mmc_host *host, struct rt_mmcsd_req *req);

    /*
     * Avoid calling the next three functions too often or in a "fast
     * path", since underlaying controller might implement them in an
     * expensive and/or slow way. Also note that these functions might
     * sleep, so don't call them in the atomic contexts!
     */

    /*
     * Notes to the set_ios callback:
     * ios->clock might be 0. For some controllers, setting 0Hz
     * as any other frequency works. However, some controllers
     * explicitly need to disable the clock. Otherwise e.g. voltage
     * switching might fail because the SDCLK is not really quiet.
     */
    void (*set_ios)(struct mmc_host *host, struct rt_mmcsd_io_cfg *ios);

    /*
     * Return values for the get_ro callback should be:
     *   0 for a read/write card
     *   1 for a read-only card
     *   -ENOSYS when not supported (equal to NULL callback)
     *   or a negative errno value when something bad happened
     */
    int (*get_ro)(struct mmc_host *host);

    /*
     * Return values for the get_cd callback should be:
     *   0 for a absent card
     *   1 for a present card
     *   -ENOSYS when not supported (equal to NULL callback)
     *   or a negative errno value when something bad happened
     */
    int (*get_cd)(struct mmc_host *host);

    void (*enable_sdio_irq)(struct mmc_host *host, int enable);
    /* Mandatory callback when using MMC_CAP2_SDIO_IRQ_NOTHREAD. */
    void (*ack_sdio_irq)(struct mmc_host *host);

    int (*start_signal_voltage_switch)(struct mmc_host *host, struct rt_mmcsd_io_cfg *ios);

    /* Check if the card is pulling dat[0:3] low */
    int (*card_busy)(struct mmc_host *host);

    /* The tuning command opcode value is different for SD and eMMC cards */
    int (*execute_tuning)(struct mmc_host *host, unsigned opcode);

    /* Prepare HS400 target operating frequency depending host driver */
    int (*prepare_hs400_tuning)(struct mmc_host *host, struct rt_mmcsd_io_cfg *ios);

    /* Prepare switch to DDR during the HS400 init sequence */
    int (*hs400_prepare_ddr)(struct mmc_host *host);

    /* Prepare for switching from HS400 to HS200 */
    void (*hs400_downgrade)(struct mmc_host *host);

    /* Complete selection of HS400 */
    void (*hs400_complete)(struct mmc_host *host);

    /* Prepare enhanced strobe depending host driver */
    void (*hs400_enhanced_strobe)(struct mmc_host        *host,
                                  struct rt_mmcsd_io_cfg *ios);

    /* Reset the eMMC card via RST_n */
    void (*hw_reset)(struct mmc_host *host);
    void (*card_event)(struct mmc_host *host);
};

struct regulator;
struct mmc_pwrseq;

struct mmc_supply
{
    struct regulator *vmmc;  /* Card power supply */
    struct regulator *vqmmc; /* Optional Vccq supply */
};

struct mmc_ctx
{
    struct task_struct *task;
};

/* VDD voltage 3.3 ~ 3.4 */
#define MMC_VDD_34_35 0x00400000 /* VDD voltage 3.4 ~ 3.5 */
#define MMC_VDD_35_36 0x00800000 /* VDD voltage 3.5 ~ 3.6 */

#define MMC_CAP2_HS200_1_8V_SDR MMCSD_SUP_HS200_1V8
#define MMC_CAP_4_BIT_DATA      MMCSD_BUSWIDTH_4
#define MMC_CAP_8_BIT_DATA      MMCSD_BUSWIDTH_8
#define MMC_CAP2_HS200          MMCSD_SUP_HS200
#define MMC_CAP_MMC_HIGHSPEED   MMCSD_SUP_HIGHSPEED
#define MMC_CAP_SD_HIGHSPEED    MMCSD_SUP_HIGHSPEED
#define MMC_CAP_1_8V_DDR        MMCSD_SUP_DDR_1V8
#define MMC_CAP_3_3V_DDR        MMCSD_SUP_DDR_3V3
#define MMC_CAP_1_2V_DDR        MMCSD_SUP_DDR_1V2
#define MMC_CAP_NONREMOVABLE    MMCSD_SUP_NONREMOVABLE


#define MMC_CAP_UHS_DDR50          0
#define MMC_CAP2_HS400             0
#define MMC_CAP_UHS_SDR50          0
#define MMC_CAP_UHS_SDR25          0
#define MMC_CAP_UHS_SDR12          0
#define MMC_CAP_UHS_SDR104         0
#define MMC_CAP_UHS                0
#define MMC_CAP2_HSX00_1_8V        0
#define MMC_CAP2_HS400_ES          0
#define MMC_CAP_NEEDS_POLL         0
#define MMC_CAP2_HSX00_1_2V        0
#define MMC_CAP2_HS400_1_8V        0
#define MMC_CAP_DRIVER_TYPE_D      0
#define MMC_CAP_DRIVER_TYPE_C      0
#define MMC_SET_DRIVER_TYPE_B      0
#define MMC_CAP_DRIVER_TYPE_A      0
#define MMC_CAP2_SDIO_IRQ_NOTHREAD 0
#define MMC_CAP_CMD23              0
#define MMC_CAP_SDIO_IRQ           0

#define MMC_CAP2_NO_SDIO (1 << 19)
#define MMC_CAP2_NO_SD   (1 << 21)
#define MMC_CAP2_NO_MMC  (1 << 22)
#define MMC_CAP2_CQE     (1 << 23)

#define MMC_VDD_165_195 VDD_165_195
#define MMC_VDD_20_21   VDD_20_21
#define MMC_VDD_29_30   VDD_29_30
#define MMC_VDD_30_31   VDD_30_31
#define MMC_VDD_32_33   VDD_32_33
#define MMC_VDD_33_34   VDD_33_34


struct mmc_host
{
    struct rt_mmcsd_host       rthost;
    struct rt_device          *parent;
    int                        index;
    const struct mmc_host_ops *ops;
    unsigned int               f_min;
    unsigned int               f_max;
    unsigned int               f_init;
    rt_uint32_t                ocr_avail;
    rt_uint32_t                ocr_avail_sdio; /* SDIO-specific OCR */
    rt_uint32_t                ocr_avail_sd;   /* SD-specific OCR */
    rt_uint32_t                ocr_avail_mmc;  /* MMC-specific OCR */
    struct wakeup_source      *ws;             /* Enable consume of uevents */
    rt_uint32_t                max_current_330;
    rt_uint32_t                max_current_300;
    rt_uint32_t                max_current_180;
    rt_uint32_t                caps; /* Host capabilities */

    rt_uint32_t caps2;               /* More host capabilities */


    /* host specific block data */
    unsigned int           max_seg_size;     /* see blk_queue_max_segment_size */
    unsigned short         max_segs;         /* see blk_queue_max_segments */
    unsigned short         unused;
    unsigned int           max_req_size;     /* maximum number of bytes in one req */
    unsigned int           max_blk_size;     /* maximum size of one mmc block */
    unsigned int           max_blk_count;    /* maximum number of blocks in one req */
    unsigned int           max_busy_timeout; /* max busy timeout in ms */
    struct rt_mmcsd_io_cfg ios;              /* current io bus settings */
    unsigned int           retune_period;
    /* group bitfields together to minimize padding */
    unsigned int use_spi_crc        : 1;
    unsigned int claimed            : 1; /* host exclusively claimed */
    unsigned int doing_init_tune    : 1; /* initial tuning in progress */
    unsigned int can_retune         : 1; /* re-tuning can be used */
    unsigned int doing_retune       : 1; /* re-tuning in progress */
    unsigned int retune_now         : 1; /* do re-tuning at next req */
    unsigned int retune_paused      : 1; /* re-tuning is temporarily disabled */
    unsigned int retune_crc_disable : 1; /* don't trigger retune upon crc */
    unsigned int can_dma_map_merge  : 1; /* merging can be used */
    unsigned int vqmmc_enabled      : 1; /* vqmmc regulator is enabled */

    int          need_retune;            /* re-tuning is needed */
    int          hold_retune;            /* hold off re-tuning */
    rt_bool_t    trigger_card_event;     /* card_event necessary */
    unsigned int sdio_irqs;
    rt_bool_t    sdio_irq_pending;

    struct led_trigger *led; /* activity led */

    struct mmc_supply supply;


    /* Ongoing data transfer that allows commands during transfer */
    struct rt_mmcsd_req *ongoing_mrq;


    unsigned int actual_clock; /* Actual HC clock rate */
    rt_uint32_t  pm_caps;
    unsigned long private[];
};


static inline int mmc_card_is_removable(struct mmc_host *host)
{
    return !(host->caps & MMC_CAP_NONREMOVABLE);
}

struct device_node;

struct mmc_host *mmc_alloc_host(int extra, struct rt_device *);
int              mmc_add_host(struct mmc_host *);
void             mmc_remove_host(struct mmc_host *);
void             mmc_free_host(struct mmc_host *);
int              mmc_of_parse(struct mmc_host *host);
int              mmc_of_parse_voltage(struct mmc_host *host, rt_uint32_t *mask);

static inline void *mmc_priv(struct mmc_host *host)
{
    return (void *)host->private;
}


#define mmc_host_is_spi(host) ((host)->caps & MMC_CAP_SPI)

#define mmc_dev(x)      ((x)->parent)
#define mmc_classdev(x) (&(x)->class_dev)
#define mmc_hostname(x) (x->parent->parent.name)

void mmc_detect_change(struct mmc_host *, unsigned long delay);
void mmc_request_done(struct mmc_host *, struct rt_mmcsd_req *);
void mmc_command_done(struct mmc_host *host, struct rt_mmcsd_req *mrq);

void mmc_cqe_request_done(struct mmc_host *host, struct rt_mmcsd_req *mrq);

/*
 * May be called from host driver's system/runtime suspend/resume callbacks,
 * to know if SDIO IRQs has been claimed.
 */
static inline rt_bool_t sdio_irq_claimed(struct mmc_host *host)
{
    return host->sdio_irqs > 0;
}

static inline int mmc_regulator_set_ocr(struct mmc_host  *mmc,
                                        struct regulator *supply,
                                        unsigned short    vdd_bit)
{
    return 0;
}

int  mmc_regulator_get_supply(struct mmc_host *mmc);
int  mmc_regulator_enable_vqmmc(struct mmc_host *mmc);
void mmc_regulator_disable_vqmmc(struct mmc_host *mmc);

void mmc_retune_timer_stop(struct mmc_host *host);

static inline void mmc_retune_needed(struct mmc_host *host)
{
    if (host->can_retune)
        host->need_retune = 1;
}

static inline rt_bool_t mmc_can_retune(struct mmc_host *host)
{
    return host->can_retune == 1;
}

static inline rt_bool_t mmc_doing_retune(struct mmc_host *host)
{
    return host->doing_retune == 1;
}

static inline rt_bool_t mmc_doing_tune(struct mmc_host *host)
{
    return host->doing_retune == 1 || host->doing_init_tune == 1;
}

static inline int mmc_get_dma_dir(struct rt_mmcsd_data *data)
{
    return data->flags & DATA_DIR_WRITE ? DMA_TO_DEVICE : DMA_FROM_DEVICE;
}

static inline rt_bool_t mmc_op_multi(rt_uint32_t opcode)
{
    return opcode == MMC_WRITE_MULTIPLE_BLOCK || opcode == MMC_READ_MULTIPLE_BLOCK;
}

static inline rt_bool_t mmc_op_tuning(rt_uint32_t opcode)
{
    return opcode == MMC_SEND_TUNING_BLOCK || opcode == MMC_SEND_TUNING_BLOCK_HS200;
}

int       mmc_gpio_get_cd(struct mmc_host *host);
void      mmc_detect_change(struct mmc_host *host, unsigned long delay);
int       mmc_regulator_set_vqmmc(struct mmc_host *mmc, struct rt_mmcsd_io_cfg *ios);
rt_bool_t mmc_can_gpio_ro(struct mmc_host *host);
int       mmc_gpio_get_ro(struct mmc_host *host);

int mmc_send_tuning(struct mmc_host *host, rt_uint32_t opcode, int *cmd_error);
int mmc_send_abort_tuning(struct mmc_host *host, rt_uint32_t opcode);
int mmc_of_parse(struct mmc_host *host);


#endif
