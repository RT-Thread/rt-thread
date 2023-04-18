/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-06-15     hichard      first version
 */

#include <drivers/mmcsd_core.h>
#include <drivers/mmc.h>

#define DBG_TAG               "SDIO"
#ifdef RT_SDIO_DEBUG
#define DBG_LVL               DBG_LOG
#else
#define DBG_LVL               DBG_INFO
#endif /* RT_SDIO_DEBUG */
#include <rtdbg.h>

static const rt_uint32_t tran_unit[] =
{
    10000, 100000, 1000000, 10000000,
    0,     0,      0,       0
};

static const rt_uint8_t tran_value[] =
{
    0,  10, 12, 13, 15, 20, 25, 30,
    35, 40, 45, 50, 55, 60, 70, 80,
};

static const rt_uint32_t tacc_uint[] =
{
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
};

static const rt_uint8_t tacc_value[] =
{
    0,  10, 12, 13, 15, 20, 25, 30,
    35, 40, 45, 50, 55, 60, 70, 80,
};

rt_inline rt_uint32_t GET_BITS(rt_uint32_t *resp,
                               rt_uint32_t  start,
                               rt_uint32_t  size)
{
    const rt_int32_t __size = size;
    const rt_uint32_t __mask = (__size < 32 ? 1 << __size : 0) - 1;
    const rt_int32_t __off = 3 - ((start) / 32);
    const rt_int32_t __shft = (start) & 31;
    rt_uint32_t __res;

    __res = resp[__off] >> __shft;
    if (__size + __shft > 32)
        __res |= resp[__off - 1] << ((32 - __shft) % 32);

    return __res & __mask;
}

/*
 * Given a 128-bit response, decode to our card CSD structure.
 */
static rt_int32_t mmcsd_parse_csd(struct rt_mmcsd_card *card)
{
    rt_uint32_t a, b;
    struct rt_mmcsd_csd *csd = &card->csd;
    rt_uint32_t *resp = card->resp_csd;

    /*
    * We only understand CSD structure v1.1 and v1.2.
    * v1.2 has extra information in bits 15, 11 and 10.
    * We also support eMMC v4.4 & v4.41.
    */
    csd->csd_structure = GET_BITS(resp, 126, 2);
    if (csd->csd_structure == 0)
    {
        LOG_E("unrecognised CSD structure version %d!", csd->csd_structure);

        return -RT_ERROR;
    }

    csd->taac = GET_BITS(resp, 112, 8);
    csd->nsac = GET_BITS(resp, 104, 8);
    csd->tran_speed = GET_BITS(resp, 96, 8);
    csd->card_cmd_class = GET_BITS(resp, 84, 12);
    csd->rd_blk_len = GET_BITS(resp, 80, 4);
    csd->rd_blk_part = GET_BITS(resp, 79, 1);
    csd->wr_blk_misalign = GET_BITS(resp, 78, 1);
    csd->rd_blk_misalign = GET_BITS(resp, 77, 1);
    csd->dsr_imp = GET_BITS(resp, 76, 1);
    csd->c_size = GET_BITS(resp, 62, 12);
    csd->c_size_mult = GET_BITS(resp, 47, 3);
    csd->r2w_factor = GET_BITS(resp, 26, 3);
    csd->wr_blk_len = GET_BITS(resp, 22, 4);
    csd->wr_blk_partial = GET_BITS(resp, 21, 1);
    csd->csd_crc = GET_BITS(resp, 1, 7);

    card->card_blksize = 1 << csd->rd_blk_len;
    card->tacc_clks = csd->nsac * 100;
    card->tacc_ns = (tacc_uint[csd->taac & 0x07] * tacc_value[(csd->taac & 0x78) >> 3] + 9) / 10;
    card->max_data_rate = tran_unit[csd->tran_speed & 0x07] * tran_value[(csd->tran_speed & 0x78) >> 3];
    if (csd->wr_blk_len >= 9)
    {
        a = GET_BITS(resp, 42, 5);
        b = GET_BITS(resp, 37, 5);
        card->erase_size = (a + 1) * (b + 1);
        card->erase_size <<= csd->wr_blk_len - 9;
    }

    return 0;
}

/*
 * Read extended CSD.
 */
static int mmc_get_ext_csd(struct rt_mmcsd_card *card, rt_uint8_t **new_ext_csd)
{
    void *ext_csd;
    struct rt_mmcsd_req req;
    struct rt_mmcsd_cmd cmd;
    struct rt_mmcsd_data data;

    *new_ext_csd = RT_NULL;
    if (GET_BITS(card->resp_csd, 122, 4) < 4)
        return 0;

    /*
    * As the ext_csd is so large and mostly unused, we don't store the
    * raw block in mmc_card.
    */
    ext_csd = rt_malloc(512);
    if (!ext_csd)
    {
        LOG_E("alloc memory failed when get ext csd!");
        return -RT_ENOMEM;
    }

    rt_memset(&req, 0, sizeof(struct rt_mmcsd_req));
    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));
    rt_memset(&data, 0, sizeof(struct rt_mmcsd_data));

    req.cmd = &cmd;
    req.data = &data;

    cmd.cmd_code = SEND_EXT_CSD;
    cmd.arg = 0;

    /* NOTE HACK:  the RESP_SPI_R1 is always correct here, but we
    * rely on callers to never use this with "native" calls for reading
    * CSD or CID.  Native versions of those commands use the R2 type,
    * not R1 plus a data block.
    */
    cmd.flags = RESP_SPI_R1 | RESP_R1 | CMD_ADTC;

    data.blksize = 512;
    data.blks = 1;
    data.flags = DATA_DIR_READ;
    data.buf = ext_csd;

    /*
    * Some cards require longer data read timeout than indicated in CSD.
    * Address this by setting the read timeout to a "reasonably high"
    * value. For the cards tested, 300ms has proven enough. If necessary,
    * this value can be increased if other problematic cards require this.
    */
    data.timeout_ns = 300000000;
    data.timeout_clks = 0;

    mmcsd_send_request(card->host, &req);

    if (cmd.err)
        return cmd.err;
    if (data.err)
        return data.err;

    *new_ext_csd = ext_csd;
    return 0;
}

/*
 * Decode extended CSD.
 */
static int mmc_parse_ext_csd(struct rt_mmcsd_card *card, rt_uint8_t *ext_csd)
{
    rt_uint64_t card_capacity = 0;
    struct rt_mmcsd_host *host;
    if (card == RT_NULL || ext_csd == RT_NULL)
    {
        LOG_E("emmc parse ext csd fail, invaild args");
        return -1;
    }

    host = card->host;
    if (host->flags & MMCSD_SUP_HS200)
    {
        card->flags |=  CARD_FLAG_HS200;
        card->hs_max_data_rate = 200000000;
    }
    else if (host->flags & MMCSD_SUP_HIGHSPEED_DDR)
    {
        card->flags |=  CARD_FLAG_HIGHSPEED_DDR;
        card->hs_max_data_rate = 52000000;
    }
    else
    {
        card->flags |=  CARD_FLAG_HIGHSPEED;
        card->hs_max_data_rate = 52000000;
    }

    card_capacity = *((rt_uint32_t *)&ext_csd[EXT_CSD_SEC_CNT]);
    card->card_sec_cnt = card_capacity;
    card_capacity *= card->card_blksize;
    card_capacity >>= 10; /* unit:KB */
    card->card_capacity = card_capacity;
    LOG_I("emmc card capacity %d KB, card sec count:%d.", card->card_capacity, card->card_sec_cnt);

    return 0;
}

/**
 *   mmc_switch - modify EXT_CSD register
 *   @card: the MMC card associated with the data transfer
 *   @set: cmd set values
 *   @index: EXT_CSD register index
 *   @value: value to program into EXT_CSD register
 *
 *   Modifies the EXT_CSD register for selected card.
 */
static int mmc_switch(struct rt_mmcsd_card *card, rt_uint8_t set,
                      rt_uint8_t index, rt_uint8_t value)
{
    int err;
    struct rt_mmcsd_host *host = card->host;
    struct rt_mmcsd_cmd cmd = {0};

    cmd.cmd_code = SWITCH;
    cmd.arg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) |
              (index << 16) | (value << 8) | set;
    cmd.flags = RESP_R1B | CMD_AC;

    err = mmcsd_send_cmd(host, &cmd, 3);
    if (err)
        return err;

    return 0;
}

static int mmc_compare_ext_csds(struct rt_mmcsd_card *card,
                                rt_uint8_t *ext_csd, rt_uint32_t bus_width)
{
    rt_uint8_t *bw_ext_csd;
    int err;

    if (bus_width == MMCSD_BUS_WIDTH_1)
        return 0;

    err = mmc_get_ext_csd(card, &bw_ext_csd);

    if (err || bw_ext_csd == RT_NULL)
    {
        err = -RT_ERROR;
        goto out;
    }

    /* only compare read only fields */
    err = !((ext_csd[EXT_CSD_PARTITION_SUPPORT] == bw_ext_csd[EXT_CSD_PARTITION_SUPPORT]) &&
            (ext_csd[EXT_CSD_ERASED_MEM_CONT] == bw_ext_csd[EXT_CSD_ERASED_MEM_CONT]) &&
            (ext_csd[EXT_CSD_REV] == bw_ext_csd[EXT_CSD_REV]) &&
            (ext_csd[EXT_CSD_STRUCTURE] == bw_ext_csd[EXT_CSD_STRUCTURE]) &&
            (ext_csd[EXT_CSD_CARD_TYPE] == bw_ext_csd[EXT_CSD_CARD_TYPE]) &&
            (ext_csd[EXT_CSD_S_A_TIMEOUT] == bw_ext_csd[EXT_CSD_S_A_TIMEOUT]) &&
            (ext_csd[EXT_CSD_HC_WP_GRP_SIZE] == bw_ext_csd[EXT_CSD_HC_WP_GRP_SIZE]) &&
            (ext_csd[EXT_CSD_ERASE_TIMEOUT_MULT] == bw_ext_csd[EXT_CSD_ERASE_TIMEOUT_MULT]) &&
            (ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE] == bw_ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE]) &&
            (ext_csd[EXT_CSD_SEC_TRIM_MULT] == bw_ext_csd[EXT_CSD_SEC_TRIM_MULT]) &&
            (ext_csd[EXT_CSD_SEC_ERASE_MULT] == bw_ext_csd[EXT_CSD_SEC_ERASE_MULT]) &&
            (ext_csd[EXT_CSD_SEC_FEATURE_SUPPORT] == bw_ext_csd[EXT_CSD_SEC_FEATURE_SUPPORT]) &&
            (ext_csd[EXT_CSD_TRIM_MULT] == bw_ext_csd[EXT_CSD_TRIM_MULT]) &&
            (ext_csd[EXT_CSD_SEC_CNT + 0] == bw_ext_csd[EXT_CSD_SEC_CNT + 0]) &&
            (ext_csd[EXT_CSD_SEC_CNT + 1] == bw_ext_csd[EXT_CSD_SEC_CNT + 1]) &&
            (ext_csd[EXT_CSD_SEC_CNT + 2] == bw_ext_csd[EXT_CSD_SEC_CNT + 2]) &&
            (ext_csd[EXT_CSD_SEC_CNT + 3] == bw_ext_csd[EXT_CSD_SEC_CNT + 3]) &&
            (ext_csd[EXT_CSD_PWR_CL_52_195] == bw_ext_csd[EXT_CSD_PWR_CL_52_195]) &&
            (ext_csd[EXT_CSD_PWR_CL_26_195] == bw_ext_csd[EXT_CSD_PWR_CL_26_195]) &&
            (ext_csd[EXT_CSD_PWR_CL_52_360] == bw_ext_csd[EXT_CSD_PWR_CL_52_360]) &&
            (ext_csd[EXT_CSD_PWR_CL_26_360] == bw_ext_csd[EXT_CSD_PWR_CL_26_360]) &&
            (ext_csd[EXT_CSD_PWR_CL_200_195] == bw_ext_csd[EXT_CSD_PWR_CL_200_195]) &&
            (ext_csd[EXT_CSD_PWR_CL_200_360] == bw_ext_csd[EXT_CSD_PWR_CL_200_360]) &&
            (ext_csd[EXT_CSD_PWR_CL_DDR_52_195] == bw_ext_csd[EXT_CSD_PWR_CL_DDR_52_195]) &&
            (ext_csd[EXT_CSD_PWR_CL_DDR_52_360] == bw_ext_csd[EXT_CSD_PWR_CL_DDR_52_360]) &&
            (ext_csd[EXT_CSD_PWR_CL_DDR_200_360] == bw_ext_csd[EXT_CSD_PWR_CL_DDR_200_360]));

    if (err)
        err = -RT_ERROR;

out:
    rt_free(bw_ext_csd);
    return err;
}

/*
 * Select the bus width amoung 4-bit and 8-bit(SDR).
 * If the bus width is changed successfully, return the selected width value.
 * Zero is returned instead of error value if the wide width is not supported.
 */
static int mmc_select_bus_width(struct rt_mmcsd_card *card, rt_uint8_t *ext_csd)
{
    rt_uint32_t ext_csd_bits[][2] =
    {
        {EXT_CSD_BUS_WIDTH_8, EXT_CSD_DDR_BUS_WIDTH_8},
        {EXT_CSD_BUS_WIDTH_4, EXT_CSD_DDR_BUS_WIDTH_4},
        {EXT_CSD_BUS_WIDTH_1, EXT_CSD_BUS_WIDTH_1},
    };
    rt_uint32_t bus_widths[] =
    {
        MMCSD_BUS_WIDTH_8,
        MMCSD_BUS_WIDTH_4,
        MMCSD_BUS_WIDTH_1
    };
    struct rt_mmcsd_host *host = card->host;
    unsigned idx, bus_width = 0;
    int err = 0, ddr = 0;

    if (GET_BITS(card->resp_csd, 122, 4) < 4)
        return 0;

    if (card->flags & CARD_FLAG_HIGHSPEED_DDR)
    {
        ddr = 2;
    }
    /*
    * Unlike SD, MMC cards dont have a configuration register to notify
    * supported bus width. So bus test command should be run to identify
    * the supported bus width or compare the ext csd values of current
    * bus width and ext csd values of 1 bit mode read earlier.
    */
    for (idx = 0; idx < sizeof(bus_widths) / sizeof(rt_uint32_t); idx++)
    {
        /*
        * Host is capable of 8bit transfer, then switch
        * the device to work in 8bit transfer mode. If the
        * mmc switch command returns error then switch to
        * 4bit transfer mode. On success set the corresponding
        * bus width on the host. Meanwhile, mmc core would
        * bail out early if corresponding bus capable wasn't
        * set by drivers.
        */
        bus_width = bus_widths[idx];
        if (bus_width == MMCSD_BUS_WIDTH_1)
        {
            ddr = 0;
        }

        err = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
                         EXT_CSD_BUS_WIDTH,
                         ext_csd_bits[idx][0]);

        if (err)
            continue;

        mmcsd_set_bus_width(host, bus_width);
        err = mmc_compare_ext_csds(card, ext_csd, bus_width);
        if (!err)
        {
            break;
        }
        else
        {
            switch (ext_csd_bits[idx][0])
            {
            case 0:
                LOG_E("switch to bus width 1 bit failed!");
                break;
            case 1:
                LOG_E("switch to bus width 4 bit failed!");
                break;
            case 2:
                LOG_E("switch to bus width 8 bit failed!");
                break;
            default:
                break;
            }
        }
    }

    if (!err && ddr)
    {
        err = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
                         EXT_CSD_BUS_WIDTH,
                         ext_csd_bits[idx][1]);
    }

    if (!err)
    {
        if (card->flags & (CARD_FLAG_HIGHSPEED | CARD_FLAG_HIGHSPEED_DDR))
        {

            err = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
                             EXT_CSD_HS_TIMING,
                             1);
        }
    }

    return err;
}
rt_err_t mmc_send_op_cond(struct rt_mmcsd_host *host,
                          rt_uint32_t ocr, rt_uint32_t *rocr)
{
    struct rt_mmcsd_cmd cmd;
    rt_uint32_t i;
    rt_err_t err = RT_EOK;

    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));

    cmd.cmd_code = SEND_OP_COND;
    cmd.arg = controller_is_spi(host) ? 0 : ocr;
    cmd.flags = RESP_SPI_R1 | RESP_R3 | CMD_BCR;

    for (i = 100; i; i--)
    {
        err = mmcsd_send_cmd(host, &cmd, 3);
        if (err)
            break;

        /* if we're just probing, do a single pass */
        if (ocr == 0)
            break;

        /* otherwise wait until reset completes */
        if (controller_is_spi(host))
        {
            if (!(cmd.resp[0] & R1_SPI_IDLE))
                break;
        }
        else
        {
            if (cmd.resp[0] & CARD_BUSY)
                break;
        }

        err = -RT_ETIMEOUT;

        rt_thread_mdelay(10); //delay 10ms
    }

    if (rocr && !controller_is_spi(host))
        *rocr = cmd.resp[0];

    return err;
}

static rt_err_t mmc_set_card_addr(struct rt_mmcsd_host *host, rt_uint32_t rca)
{
    rt_err_t err;
    struct rt_mmcsd_cmd cmd;

    rt_memset(&cmd, 0, sizeof(struct rt_mmcsd_cmd));

    cmd.cmd_code = SET_RELATIVE_ADDR;
    cmd.arg = rca << 16;
    cmd.flags = RESP_R1 | CMD_AC;

    err = mmcsd_send_cmd(host, &cmd, 3);
    if (err)
        return err;

    return 0;
}

static int mmc_select_hs200(struct rt_mmcsd_card *card)
{
    int ret;

    ret = mmc_switch(card, EXT_CSD_CMD_SET_NORMAL,
                     EXT_CSD_HS_TIMING, EXT_CSD_TIMING_HS200);
    if (ret)
        return ret;

    mmcsd_set_timing(card->host, MMCSD_TIMING_MMC_HS200);
    mmcsd_set_clock(card->host, 200000000);

    ret = mmcsd_excute_tuning(card);

    return ret;
}

static int mmc_select_timing(struct rt_mmcsd_card *card)
{
    int ret = 0;

    if (card->flags & CARD_FLAG_HS200)
    {
        ret = mmc_select_hs200(card);
    }
    else if (card->flags & CARD_FLAG_HIGHSPEED_DDR)
    {
        mmcsd_set_timing(card->host, MMCSD_TIMING_MMC_DDR52);
        mmcsd_set_clock(card->host, card->hs_max_data_rate);
    }
    else
    {
        mmcsd_set_timing(card->host, MMCSD_TIMING_UHS_SDR50);
        mmcsd_set_clock(card->host, card->hs_max_data_rate);
    }

    return ret;
}

static rt_int32_t mmcsd_mmc_init_card(struct rt_mmcsd_host *host,
                                      rt_uint32_t           ocr)
{
    rt_int32_t err;
    rt_uint32_t resp[4];
    rt_uint32_t rocr = 0;
    rt_uint8_t *ext_csd = RT_NULL;
    struct rt_mmcsd_card *card = RT_NULL;

    mmcsd_go_idle(host);

    /* The extra bit indicates that we support high capacity */
    err = mmc_send_op_cond(host, ocr | (1 << 30), &rocr);
    if (err)
        goto err;

    if (controller_is_spi(host))
    {
        err = mmcsd_spi_use_crc(host, 1);
        if (err)
            goto err1;
    }

    if (controller_is_spi(host))
        err = mmcsd_get_cid(host, resp);
    else
        err = mmcsd_all_get_cid(host, resp);
    if (err)
        goto err;

    card = rt_malloc(sizeof(struct rt_mmcsd_card));
    if (!card)
    {
        LOG_E("malloc card failed!");
        err = -RT_ENOMEM;
        goto err;
    }
    rt_memset(card, 0, sizeof(struct rt_mmcsd_card));

    card->card_type = CARD_TYPE_MMC;
    card->host = host;
    card->rca = 1;
    rt_memcpy(card->resp_cid, resp, sizeof(card->resp_cid));

    /*
     * For native busses:  get card RCA and quit open drain mode.
     */
    if (!controller_is_spi(host))
    {
        err = mmc_set_card_addr(host, card->rca);
        if (err)
            goto err1;

        mmcsd_set_bus_mode(host, MMCSD_BUSMODE_PUSHPULL);
    }

    err = mmcsd_get_csd(card, card->resp_csd);
    if (err)
        goto err1;

    err = mmcsd_parse_csd(card);
    if (err)
        goto err1;

    if (!controller_is_spi(host))
    {
        err = mmcsd_select_card(card);
        if (err)
            goto err1;
    }

    /*
    * Fetch and process extended CSD.
    */

    err = mmc_get_ext_csd(card, &ext_csd);
    if (err)
        goto err1;
    err = mmc_parse_ext_csd(card, ext_csd);
    if (err)
        goto err1;

    /* If doing byte addressing, check if required to do sector
    * addressing.  Handle the case of <2GB cards needing sector
    * addressing.  See section 8.1 JEDEC Standard JED84-A441;
    * ocr register has bit 30 set for sector addressing.
    */
    if (!(card->flags & CARD_FLAG_SDHC) && (rocr & (1 << 30)))
        card->flags |= CARD_FLAG_SDHC;

    /*switch bus width and bus mode*/
    err = mmc_select_bus_width(card, ext_csd);
    if (err)
    {
        LOG_E("mmc select buswidth fail");
        goto err0;
    }

    err = mmc_select_timing(card);
    if (err)
    {
        LOG_E("mmc select timing fail");
        goto err0;
    }

    host->card = card;

    rt_free(ext_csd);
    return 0;

err0:
    rt_free(ext_csd);
err1:
    rt_free(card);
err:

    return err;
}

/*
 * Starting point for mmc card init.
 */
rt_int32_t init_mmc(struct rt_mmcsd_host *host, rt_uint32_t ocr)
{
    rt_int32_t err;
    rt_uint32_t  current_ocr;
    /*
     * We need to get OCR a different way for SPI.
     */
    if (controller_is_spi(host))
    {
        err = mmcsd_spi_read_ocr(host, 0, &ocr);
        if (err)
            goto err;
    }

    current_ocr = mmcsd_select_voltage(host, ocr);

    /*
     * Can we support the voltage(s) of the card(s)?
     */
    if (!current_ocr)
    {
        err = -RT_ERROR;
        goto err;
    }

    /*
     * Detect and init the card.
     */
    err = mmcsd_mmc_init_card(host, current_ocr);
    if (err)
        goto err;

    mmcsd_host_unlock(host);

    err = rt_mmcsd_blk_probe(host->card);
    if (err)
        goto remove_card;
    mmcsd_host_lock(host);

    return 0;

remove_card:
    mmcsd_host_lock(host);
    rt_mmcsd_blk_remove(host->card);
    rt_free(host->card);
    host->card = RT_NULL;
err:

    LOG_E("init MMC card failed!");

    return err;
}
