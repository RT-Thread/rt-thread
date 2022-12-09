/*
 * Copyright (C) 2017 ALLWINNERTECH TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of ALLWINNERTECH TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "sunxi_hal_common.h"
#include "hal_base.h"

#include "sys/endian.h"

#include "hal_sdhost.h"
#include "sdmmc.h"
#include "_sdhost.h"
#include "_core.h"
#ifdef CONFIG_USE_MMC
#include "_mmc.h"
#endif
#include "_sd.h"
#include "_sd_define.h"


#ifdef CONFIG_USE_SD
static const unsigned int tran_exp[] = { /* about KB/S */
    10000,      100000,     1000000,    10000000,
    0,      0,      0,      0
};

static const unsigned char tran_mant[] = { /* time value*10 */
    0,  10, 12, 13, 15, 20, 25, 30,
    35, 40, 45, 50, 55, 60, 70, 80,
};
/*
static const unsigned int tacc_exp[] = {
    1,  10, 100,    1000,   10000,  100000, 1000000, 10000000,
};

static const unsigned int tacc_mant[] = {
    0,  10, 12, 13, 15, 20, 25, 30,
    35, 40, 45, 50, 55, 60, 70, 80,
};
*/

static int32_t mmc_send_app_op_cond(struct mmc_host *host, uint32_t ocr, uint32_t *rocr)
{
    struct mmc_command cmd = {0};
    int32_t i, err;

    if (!host) {
        SDC_LOGE_RAW(ROM_ERR_MASK, "%s,%d err", __func__, __LINE__);
        return -1;
    }

    cmd.opcode = SD_APP_OP_COND;
    cmd.arg = ocr;
    cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R3 | MMC_CMD_BCR;

    for (i = 100; i; i--) {
        err = mmc_wait_for_app_cmd(host, NULL, &cmd);
        if (err) {
            // printf("%s,%d\n",__FUNCTION__,__LINE__);
            break;
        }

        /* otherwise wait until reset completes */
        if (cmd.resp[0] & MMC_CARD_BUSY){
            // printf("%s,%d\n",__FUNCTION__,__LINE__);
            break;
        }

        if (host->ocr_avail & MMC_VDD_165_195)
            cmd.arg = 0x41000000 | (cmd.resp[0] & 0xFF8000);
        else
            cmd.arg = 0x40000000 | (cmd.resp[0] & 0xFF8000);

        err = -1;

        mmc_mdelay(20);
//      printf("%s,%d %d\n",__FUNCTION__,__LINE__,i);

    }

    if (rocr)
        *rocr = cmd.resp[0];

    if(err)
        printf("%s,%d %ld\n",__FUNCTION__,__LINE__, HAL_PR_SZ_L(i));

    return err;
}

int32_t mmc_app_sd_status(struct mmc_card *card, uint8_t *ssr)
{
    struct mmc_request mrq;
    struct mmc_command cmd = {0};
    struct mmc_data data = {0};
    struct scatterlist sg;

    if (!ssr) {
        SD_LOGE("%s,%d err", __func__, __LINE__);
        return -1;
    }

    if (mmc_app_cmd(card->host, card)) {
        return -1;
    }

    mrq.cmd = &cmd;
    mrq.data = &data;

    cmd.opcode = SD_APP_SD_STATUS;
    cmd.arg = 0;
    cmd.flags = MMC_RSP_SPI_R2 | MMC_RSP_R1 | MMC_CMD_ADTC;

    data.blksz = 64;
    data.blocks = 1;
    data.flags = MMC_DATA_READ;
    data.sg = &sg;
    data.sg_len = 1;

    sg.len = 64;
    sg.buffer = ssr;

    if (mmc_wait_for_req(card->host, &mrq)) {
        return -1;
    }

    SD_LOGN("card raw SD status:\n");
    sd_hex_dump_bytes((void *)ssr, 64);

    return 0;
}

int32_t mmc_app_send_scr(struct mmc_card *card, uint32_t *raw_scr)
{
    struct mmc_command cmd = {0};
    struct mmc_data data = {0};
    struct mmc_request mrq;
    struct scatterlist sg;

    if (mmc_app_cmd(card->host, card)) {
        return -1;
    }

    mrq.cmd = &cmd;
    mrq.data = &data;

    cmd.opcode = SD_APP_SEND_SCR;
    cmd.arg = 0;
    cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;


    data.blksz = 8;
    data.blocks = 1;
    data.flags = MMC_DATA_READ;
    data.sg = &sg;
    data.sg_len = 1;

    sg.len = 8;
    sg.buffer = (void *)raw_scr;

    /* get scr, 8 bytes */
    if (mmc_wait_for_req(card->host, &mrq)) {
        return -1;
    }

    raw_scr[0] = be32_to_cpu(raw_scr[0]);
    raw_scr[1] = be32_to_cpu(raw_scr[1]);

    return 0;
}

#ifdef SD_SUPPORT_VERSION3
int32_t mmc_switch_to_1v8(struct mmc_card *card)
{
    struct mmc_command cmd = {0};

    cmd.opcode = SD_SWITCH_VOLTAGE;
    cmd.arg = 0;
    cmd.vol_switch  = 1;
    cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;

    if (mmc_wait_for_cmd(card->host, &cmd)) {
        SD_LOGW("sd switch 1v8 failed\n");
        return -1;
    }

    return 0;
}
#endif

/*
 * Given the decoded CSD structure, decode the raw CID to our CID structure.
 */
void mmc_decode_cid(struct mmc_card *card, uint32_t *resp)
{
    SDC_Memset(&card->cid, 0, sizeof(struct mmc_cid));

    /*
     * SD doesn't currently have a version field so we will
     * have to assume we can parse this.
     */
    card->cid.manfid = UNSTUFF_BITS(resp, 120, 8);
    card->cid.oemid = UNSTUFF_BITS(resp, 104, 8);
    card->cid.prod_name[0] = UNSTUFF_BITS(resp, 96, 8);
    card->cid.prod_name[1] = UNSTUFF_BITS(resp, 88, 8);
    card->cid.prod_name[2] = UNSTUFF_BITS(resp, 80, 8);
    card->cid.prod_name[3] = UNSTUFF_BITS(resp, 72, 8);
    card->cid.prod_name[4] = UNSTUFF_BITS(resp, 64, 8);
    card->cid.hwrev = UNSTUFF_BITS(resp, 60, 4);
    card->cid.fwrev = UNSTUFF_BITS(resp, 56, 4);
    card->cid.serial = UNSTUFF_BITS(resp, 24, 32);
    card->cid.year = UNSTUFF_BITS(resp, 12, 8);
    card->cid.month = UNSTUFF_BITS(resp, 8, 4);

    card->cid.year += 2000; /* SD cards year offset */
}

int32_t mmc_send_cid(struct mmc_card *card)
{
    struct mmc_command cmd = {0};
    uint32_t cid[4] = {0};

    cmd.opcode = MMC_SEND_CID;
    cmd.arg = card->rca << 16;
    cmd.flags = MMC_RSP_R2 | MMC_CMD_AC;

    if (mmc_wait_for_cmd(card->host, &cmd)) {
        return -1;
    }

    HAL_Memcpy((void *)cid, (void *)cmd.resp, 16);
    SD_LOGN("card raw cid:\n");
    sd_hex_dump_bytes((void *)cid, 16);

    mmc_decode_cid(card, cid);

    return 0;
}

/*
 * Given a 128-bit response, decode to our card CSD structure.
 */
static int32_t mmc_decode_csd(struct mmc_card *card, uint32_t *raw_csd)
{
    int32_t e, m, csd_struct;
    uint32_t *resp = raw_csd;
    struct mmc_csd *csd = &card->csd;

    csd_struct = UNSTUFF_BITS(resp, 126, 2);
    card->csd.csd_ver = csd_struct;

    switch (csd_struct) {
    case 0:
        //m = UNSTUFF_BITS(resp, 115, 4);
        //e = UNSTUFF_BITS(resp, 112, 3);
        //csd->tacc_ns = (tacc_exp[e] * tacc_mant[m] + 9) / 10;
        //csd->tacc_clks = UNSTUFF_BITS(resp, 104, 8) * 100;

        m = UNSTUFF_BITS(resp, 99, 4);
        e = UNSTUFF_BITS(resp, 96, 3);
        csd->max_dtr = tran_exp[e] * tran_mant[m];
        csd->cmdclass =  UNSTUFF_BITS(resp, 84, 12);

        m = UNSTUFF_BITS(resp, 80, 4);
        csd->read_blk_len = 1 << m;

        e = UNSTUFF_BITS(resp, 47, 3);
        m = UNSTUFF_BITS(resp, 62, 12);
        csd->capacity = (1 + m) * (1 << (e + 2)) * csd->read_blk_len;
        csd->capacity >>= 10; /* unit:KB */

        //csd->read_blkbits = UNSTUFF_BITS(resp, 80, 4);
        //csd->read_partial = UNSTUFF_BITS(resp, 79, 1);
        //csd->write_misalign = UNSTUFF_BITS(resp, 78, 1);
        //csd->read_misalign = UNSTUFF_BITS(resp, 77, 1);
        //csd->r2w_factor = UNSTUFF_BITS(resp, 26, 3);
        //csd->write_blkbits = UNSTUFF_BITS(resp, 22, 4);
        //csd->write_partial = UNSTUFF_BITS(resp, 21, 1);

        //if (UNSTUFF_BITS(resp, 46, 1)) {
        //  csd->erase_size = 1;
        //} else if (csd->write_blkbits >= 9) {
        //  csd->erase_size = UNSTUFF_BITS(resp, 39, 7) + 1;
        //  csd->erase_size <<= csd->write_blkbits - 9;
        //}
        break;
    case 1:
        /*
         * This is a block-addressed SDHC or SDXC card. Most
         * interesting fields are unused and have fixed
         * values. To avoid getting tripped by buggy cards,
         * we assume those fixed values ourselves.
         */
        mmc_card_set_blockaddr(card);

        //csd->tacc_ns = 0; /* Unused */
        //csd->tacc_clks = 0; /* Unused */

        m = UNSTUFF_BITS(resp, 99, 4);
        e = UNSTUFF_BITS(resp, 96, 3);
        csd->max_dtr = tran_exp[e] * tran_mant[m];
        csd->cmdclass =  UNSTUFF_BITS(resp, 84, 12);
        csd->read_blk_len = UNSTUFF_BITS(resp, 80, 4);

        m = UNSTUFF_BITS(resp, 48, 22);
        csd->capacity = (1 + m) << 9;

        /* SDXC cards have a minimum C_SIZE of 0x00FFFF */
        if (m >= 0xFFFF)
            mmc_card_set_ext_capacity(card);

        //csd->read_blkbits = 9;
        //csd->read_partial = 0;
        //csd->write_misalign = 0;
        //csd->read_misalign = 0;
        //csd->r2w_factor = 4; /* Unused */
        //csd->write_blkbits = 9;
        //csd->write_partial = 0;
        //csd->erase_size = 1;
        break;
    default:
        SD_LOGE("%s: unrecognised CSD structure version %d\n",
            __func__, (unsigned int)csd_struct);
        return -1;
    }

    //card->erase_size = csd->erase_size;
    SD_LOGD("%s %d ca:%d\n", __func__, (unsigned int)csd_struct, (unsigned int)csd->capacity);

    return 0;
}

#ifdef SD_SUPPORT_VERSION3

static void sd_update_bus_speed_mode(struct mmc_card *card)
{
    /*
     * If the host doesn't support any of the UHS-I modes, fallback on
     * default speed.
     */
    if (!(card->host->caps & (MMC_CAP_UHS_SDR12 | MMC_CAP_UHS_SDR25 |
        MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR104 | MMC_CAP_UHS_DDR50))) {
        card->sd_bus_speed = 0;
        return;
    }

    if ((card->host->caps & MMC_CAP_UHS_SDR104) &&
        (card->sw_caps.sd3_bus_mode & SD_MODE_UHS_SDR104)) {
        card->sd_bus_speed = UHS_SDR104_BUS_SPEED;
    } else if ((card->host->caps & MMC_CAP_UHS_DDR50) &&
               (card->sw_caps.sd3_bus_mode & SD_MODE_UHS_DDR50)) {
        card->sd_bus_speed = UHS_DDR50_BUS_SPEED;
    } else if ((card->host->caps & (MMC_CAP_UHS_SDR104 |
                MMC_CAP_UHS_SDR50)) && (card->sw_caps.sd3_bus_mode &
                SD_MODE_UHS_SDR50)) {
        card->sd_bus_speed = UHS_SDR50_BUS_SPEED;
    } else if ((card->host->caps & (MMC_CAP_UHS_SDR104 |
                MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR25)) &&
               (card->sw_caps.sd3_bus_mode & SD_MODE_UHS_SDR25)) {
        card->sd_bus_speed = UHS_SDR25_BUS_SPEED;
    } else if ((card->host->caps & (MMC_CAP_UHS_SDR104 |
                MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR25 |
                MMC_CAP_UHS_SDR12)) && (card->sw_caps.sd3_bus_mode &
                SD_MODE_UHS_SDR12)) {
        card->sd_bus_speed = UHS_SDR12_BUS_SPEED;
    }
}

static int32_t sd_set_bus_speed_mode(struct mmc_card *card, int8_t *status)
{
    int32_t err;
    uint32_t timing = 0;

    switch (card->sd_bus_speed) {
    case UHS_SDR104_BUS_SPEED:
        timing = MMC_TIMING_UHS_SDR104;
        card->sw_caps.uhs_max_dtr = UHS_SDR104_MAX_DTR;
        break;
    case UHS_DDR50_BUS_SPEED:
        timing = MMC_TIMING_UHS_DDR50;
        card->sw_caps.uhs_max_dtr = UHS_DDR50_MAX_DTR;
        break;
    case UHS_SDR50_BUS_SPEED:
        timing = MMC_TIMING_UHS_SDR50;
        card->sw_caps.uhs_max_dtr = UHS_SDR50_MAX_DTR;
        break;
    case UHS_SDR25_BUS_SPEED:
        timing = MMC_TIMING_UHS_SDR25;
        card->sw_caps.uhs_max_dtr = UHS_SDR25_MAX_DTR;
        break;
    case UHS_SDR12_BUS_SPEED:
        timing = MMC_TIMING_UHS_SDR12;
        card->sw_caps.uhs_max_dtr = UHS_SDR12_MAX_DTR;
        break;
    default:
        return 0;
    }

    err = mmc_sd_switch(card, 1, 0, card->sd_bus_speed, status);
    if (err)
        return err;

    if ((status[16] & 0xF) != card->sd_bus_speed)
        SD_LOGW("%s: Problem setting bus speed mode!\n", __func__);
    else {
        mmc_set_timing(card->host, timing);
        mmc_set_clock(card->host, card->sw_caps.uhs_max_dtr);
    }

    return 0;
}

static int32_t sd_set_current_limit(struct mmc_card *card, int8_t *status)
{
    int32_t current_limit = 0;
    int32_t err;

    /*
     * Current limit switch is only defined for SDR50, SDR104, and DDR50
     * bus speed modes. For other bus speed modes, we set the default
     * current limit of 200mA.
     */
    if ((card->sd_bus_speed == UHS_SDR50_BUS_SPEED) ||
        (card->sd_bus_speed == UHS_SDR104_BUS_SPEED) ||
        (card->sd_bus_speed == UHS_DDR50_BUS_SPEED)) {
        if (card->host->caps & MMC_CAP_MAX_CURRENT_800) {
            if (card->sw_caps.sd3_curr_limit & SD_MAX_CURRENT_800)
                current_limit = SD_SET_CURRENT_LIMIT_800;
            else if (card->sw_caps.sd3_curr_limit &
                    SD_MAX_CURRENT_600)
                current_limit = SD_SET_CURRENT_LIMIT_600;
            else if (card->sw_caps.sd3_curr_limit &
                    SD_MAX_CURRENT_400)
                current_limit = SD_SET_CURRENT_LIMIT_400;
            else if (card->sw_caps.sd3_curr_limit &
                    SD_MAX_CURRENT_200)
                current_limit = SD_SET_CURRENT_LIMIT_200;
        } else if (card->host->caps & MMC_CAP_MAX_CURRENT_600) {
            if (card->sw_caps.sd3_curr_limit & SD_MAX_CURRENT_600)
                current_limit = SD_SET_CURRENT_LIMIT_600;
            else if (card->sw_caps.sd3_curr_limit &
                    SD_MAX_CURRENT_400)
                current_limit = SD_SET_CURRENT_LIMIT_400;
            else if (card->sw_caps.sd3_curr_limit &
                    SD_MAX_CURRENT_200)
                current_limit = SD_SET_CURRENT_LIMIT_200;
        } else if (card->host->caps & MMC_CAP_MAX_CURRENT_400) {
            if (card->sw_caps.sd3_curr_limit & SD_MAX_CURRENT_400)
                current_limit = SD_SET_CURRENT_LIMIT_400;
            else if (card->sw_caps.sd3_curr_limit &
                    SD_MAX_CURRENT_200)
                current_limit = SD_SET_CURRENT_LIMIT_200;
        } else if (card->host->caps & MMC_CAP_MAX_CURRENT_200) {
            if (card->sw_caps.sd3_curr_limit & SD_MAX_CURRENT_200)
                current_limit = SD_SET_CURRENT_LIMIT_200;
        }
    } else
        current_limit = SD_SET_CURRENT_LIMIT_200;

    err = mmc_sd_switch(card, 1, 3, current_limit, status);
    if (err)
        return err;

    if (((status[15] >> 4) & 0x0F) != current_limit)
        SD_LOGW("%s: Problem setting current limit!\n", __func__);

    return 0;
}

int32_t mmc_sd_init_uhs_card(struct mmc_card *card)
{
    int32_t err;
    struct mmc_command cmd = {0};
    struct mmc_data data = {0};
    struct mmc_request mrq;
    struct scatterlist sg = {0};
    uint32_t time = 0;
    uint8_t pattern[] = {
        0xff, 0x0f, 0xff, 0x00, 0xff, 0xcc, 0xc3, 0xcc, 0xc3, 0x3c, 0xcc, 0xff, 0xfe, 0xff, 0xfe, 0xef,
        0xff, 0xdf, 0xff, 0xdd, 0xff, 0xfb, 0xff, 0xfb, 0xbf, 0xff, 0x7f, 0xff, 0x77, 0xf7, 0xbd, 0xef,
        0xff, 0xf0, 0xff, 0xf0, 0x0f, 0xfc, 0xcc, 0x3c, 0xcc, 0x33, 0xcc, 0xcf, 0xff, 0xef, 0xff, 0xee,
        0xff, 0xfd, 0xff, 0xfd, 0xdf, 0xff, 0xbf, 0xff, 0xbb, 0xff, 0xf7, 0xff, 0xf7, 0x7f, 0x7b, 0xde
    };
    uint32_t status[64/4] = {0};

    if (!card->scr.sda_spec3)
        return 0;

    if (!(card->csd.cmdclass & CCC_SWITCH))
        return 0;

    /* Set 4-bit bus width */
    if ((card->host->caps & MMC_CAP_4_BIT_DATA) &&
        (card->scr.bus_widths & SD_SCR_BUS_WIDTH_4)) {
        err = mmc_app_set_bus_width(card, MMC_BUS_WIDTH_4);
        if (err)
            goto out;

        HAL_SDC_Set_BusWidth(card->host, MMC_BUS_WIDTH_4);
    }

    /*
     * Select the bus speed mode depending on host
     * and card capability.
     */
    sd_update_bus_speed_mode(card);

    /* Set the driver strength for the card */
    err = sd_select_driver_type(card, status);
    if (err)
        goto out;

    /* Set current limit for the card */
    err = sd_set_current_limit(card, status);
    if (err)
        goto out;

    /* Set bus speed mode of the card */
    err = sd_set_bus_speed_mode(card, status);
    if (err)
        goto out;

    /* SPI mode doesn't define CMD19 */
    mmc_host_clk_hold(card->host);

    sg.len = 512;
    sg.buffer = status;
    cmd.opcode = MMC_SEND_TUNING_PATTERN;
    cmd.arg = 0;
    cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
    cmd.data = &data;

    data.blksz = 64;
    data.sg_len = 1;
    data.sg = &sg;
    data.flags = MMC_DATA_READ;
    mrq.cmd = &cmd;
    mrq.data = &data;
    do {
        if (mmc_wait_for_req(card->host, &mrq)) {
            continue;
        }
        time++;
    } while (time < 40);

    if (HAL_Memcmp((void *)pattern, (void *)status, 64))
        return -1;

    mmc_host_clk_release(card->host);

out:
    return 0;
}
#endif

/*
 * Given a 64-bit response, decode to our card SCR structure.
 */
static int32_t mmc_decode_scr(struct mmc_card *card, uint32_t *raw_scr)
{
    struct sd_scr *scr = &card->scr;
    uint32_t scr_struct;
    uint32_t resp[4];

    resp[3] = raw_scr[1];
    resp[2] = raw_scr[0];

    scr_struct = UNSTUFF_BITS(resp, 60, 4);
    if (scr_struct != 0) {
        SD_LOGW("sdc unrecognised SCR structure version %u\n", (unsigned int)scr_struct);
        return -1;
    }

    scr->sda_vsn = UNSTUFF_BITS(resp, 56, 4);
    scr->security_sup = UNSTUFF_BITS(resp, 52, 3);
    scr->bus_widths = UNSTUFF_BITS(resp, 48, 4);

    if (scr->sda_vsn == SCR_SPEC_VER_2)
        /* Check if Physical Layer Spec v3.0 is supported */
        scr->sda_spec3 = UNSTUFF_BITS(resp, 47, 1);

    //if (UNSTUFF_BITS(resp, 55, 1))
    //  card->erased_byte = 0xFF;
    //else
    //  card->erased_byte = 0x0;

    if (scr->sda_spec3) {
        scr->cmds = UNSTUFF_BITS(resp, 32, 2);
        scr->sda_spec4 = UNSTUFF_BITS(resp, 42, 1);
        scr->sda_spec5 = UNSTUFF_BITS(resp, 38, 4);
    }

    return 0;
}

/*
 * Fetch and process SD Status register.
 */
static int32_t mmc_read_ssr(struct mmc_card *card)
{
    int32_t err, i;
    uint32_t ssr[64/4];

    if (!(card->csd.cmdclass & CCC_APP_SPEC)) {
        SD_LOGW("%s: card lacks mandatory SD Status function.\n", __func__);
        return 0;
    }

    err = mmc_app_sd_status(card, (uint8_t *)ssr);
    if (err) {
        SD_LOGW("%s: problem reading SD Status register.\n", __func__);
        err = 0;
        goto out;
    }

    for (i = 0; i < 16; i++)
        ssr[i] = be32_to_cpu(ssr[i]);

#ifdef SD_SUPPORT_ERASE
    uint32_t au, es, et, eo;

    /*
     * UNSTUFF_BITS only works with four u32s so we have to offset the
     * bitfield positions accordingly.
     */
    au = UNSTUFF_BITS(ssr, 428 - 384, 4);
    if (au > 0 && au <= 9) {
        card->ssr.au = 1 << (au + 4);
        es = UNSTUFF_BITS(ssr, 408 - 384, 16);
        et = UNSTUFF_BITS(ssr, 402 - 384, 6);
        eo = UNSTUFF_BITS(ssr, 400 - 384, 2);
        if (es && et) {
            card->ssr.erase_timeout = (et * 1000) / es;
            card->ssr.erase_offset = eo * 1000;
        }
    } else {
        SD_LOGW("%s: SD Status: Invalid Allocation Unit size.\n", __func__);
    }
#endif

    card->speed_class = UNSTUFF_BITS(ssr, 440 - 384, 8) * 2;
    if (card->speed_class == 8)
        card->speed_class = 10;
out:
    return err;
}

/*
 * Fetches and decodes switch information
 */
static int32_t mmc_read_switch(struct mmc_card *card)
{
    int32_t err;
    uint32_t status[64/sizeof(uint32_t)] = {0};
    uint8_t *p_sta = (uint8_t *)status;

    if (card->scr.sda_vsn < SCR_SPEC_VER_1) {
        SD_LOGN("Card ver. does not support to read switch info!\n");
        return 0;
    }

    if (!(card->csd.cmdclass & CCC_SWITCH)) {
        SD_LOGW("card lacks mandatory switch function, performance might suffer.\n");
        return 0;
    }

    /* Find out the supported Bus Speed Modes. */
    err = mmc_sd_switch(card, SD_SWITCH_CHECK, SD_SWITCH_GRP_ACCESS_MODE,
                        SD_SWITCH_ACCESS_HS, p_sta);
    if (err) {
        SD_LOGW("%s: problem reading Bus Speed modes.\n", __func__);
        goto out;
    }

    if (p_sta[13] & SD_MODE_HIGH_SPEED)
        card->sw_caps.hs_max_dtr = HIGH_SPEED_MAX_DTR;

    if (card->scr.sda_spec3) {
        card->sw_caps.sd3_bus_mode = p_sta[13];

        /* Find out Driver Strengths supported by the card */
        err = mmc_sd_switch(card, SD_SWITCH_CHECK, SD_SWITCH_GRP_DRV_STRENGTH,
                            SD_SWITCH_ACCESS_HS, p_sta);
        if (err) {
            SD_LOGW("%s: problem reading Driver Strength.\n", __func__);
            goto out;
        }

        card->sw_caps.sd3_drv_type = p_sta[9];

        /* Find out Current Limits supported by the card */
        err = mmc_sd_switch(card, SD_SWITCH_CHECK, SD_SWITCH_GRP_CUR_LIMIT,
                            SD_SWITCH_ACCESS_HS, p_sta);
        if (err) {
            SD_LOGW("%s: problem reading Current Limit.\n", __func__);
            goto out;
        }

        card->sw_caps.sd3_curr_limit = p_sta[7];
    }

out:
    return err;
}

/*
 * Test if the card supports high-speed mode and, if so, switch to it.
 */
int32_t mmc_sd_switch_hs(struct mmc_card *card)
{
    int32_t err;
    uint32_t status[64/sizeof(uint32_t)] = {0};
    uint8_t *p_sta = (uint8_t *)status;

    if (card->scr.sda_vsn < SCR_SPEC_VER_1) {
        SD_LOGN("Card ver. does not support to switch to high speed!\n");
        return 0;
    }

    if (!(card->csd.cmdclass & CCC_SWITCH)) {
        SD_LOGN("Card cmdclass not support to switch to high speed!\n");
        return 0;
    }

    if (!(card->host->caps & MMC_CAP_SD_HIGHSPEED))
        return 0;

    if (card->sw_caps.hs_max_dtr == 0)
        return 0;

    /* Check function */
    err = mmc_sd_switch(card, SD_SWITCH_CHECK, SD_SWITCH_GRP_ACCESS_MODE,
                        SD_SWITCH_ACCESS_HS, p_sta);
    if (err)
        return err;

    if ((p_sta[16] & 0x0F) != 1) {
        SD_LOGW("%s: Problem switching card into high-speed mode!\n", __func__);
        err = 0;
    } else {
        err = 1;
    }

    return err;
}

static int32_t mmc_send_cxd_native(struct mmc_host *host, uint32_t arg, uint32_t *cxd, int32_t opcode)
{
    int32_t err;
    struct mmc_command cmd = {0};

    if (!host || !cxd) {
        SDC_LOGE_RAW(ROM_ERR_MASK, "%s,%d err", __func__, __LINE__);
        return -1;
    }

    cmd.opcode = opcode;
    cmd.arg = arg;
    cmd.flags = MMC_RSP_R2 | MMC_CMD_AC;

    err = mmc_wait_for_cmd(host, &cmd);
    if (err)
        return err;

    HAL_Memcpy(cxd, cmd.resp, sizeof(uint32_t) * 4);

    return 0;
}

int32_t mmc_send_csd(struct mmc_card *card, uint32_t *csd)
{
    return mmc_send_cxd_native(card->host, card->rca << 16,
                csd, MMC_SEND_CSD);
}

int32_t mmc_sd_get_csd(struct mmc_card *card)
{
    int32_t err;
    uint32_t csd[4] = {0};

    /* Fetch CSD from card. */
    err = mmc_send_csd(card, csd);
    if (err)
        return err;

    SD_LOGN("card raw csd:\n");
    sd_hex_dump_bytes((void *)csd, 16);

    err = mmc_decode_csd(card, csd);
    if (err)
        return err;

    return 0;
}

int32_t mmc_sd_setup_card(struct mmc_host *host, struct mmc_card *card)
{
    int32_t err;
    int32_t retries;
    uint32_t raw_scr[2] = {0};

    /* Fetch SCR from card. */
    err = mmc_app_send_scr(card, raw_scr);
    if (err)
        return err;

    SD_LOGN("card raw scr:\n");
    sd_hex_dump_bytes((void *)raw_scr, 8);

    err = mmc_decode_scr(card, raw_scr);
    if (err)
        return err;

    /* Fetch and process SD Status register. */
    err = mmc_read_ssr(card);
    if (err)
        return err;

#ifdef SD_SUPPORT_ERASE
    /* Erase init depends on CSD and SSR */
    mmc_init_erase(card);
#endif
    /* Fetch switch information from card. */
    for (retries = 1; retries <= 3; retries++) {
        err = mmc_read_switch(card);
        if (!err) {
            if (retries > 1) {
                SD_LOGW("%s: recovered\n", __func__);
            }
            break;
        } else {
            SD_LOGW("%s: read switch failed (attempt %d)\n",
                    __func__, (unsigned int)retries);
        }
    }

    if (err)
        return err;
#ifdef SD_SUPPORT_WRITEPROTECT
    int32_t ro = -1;

    /* Check if read-only switch is active. */
    mmc_host_clk_hold(card->host);
    ro = HAL_SDC_Get_ReadOnly(card->host);
    mmc_host_clk_release(card->host);

    if (ro < 0) {
        SD_LOGW("%s: host does not support reading read-only switch."
            " assuming write-enable.\n", __func__);
    } else if (ro > 0) {
        mmc_card_set_readonly(card);
    }
#endif
    return 0;
}

uint32_t mmc_sd_get_max_clock(struct mmc_card *card)
{
    uint32_t max_dtr = (uint32_t)-1;

    if (mmc_card_highspeed(card)) {
        if (max_dtr > card->sw_caps.hs_max_dtr)
            max_dtr = card->sw_caps.hs_max_dtr;
    } else if (max_dtr > card->csd.max_dtr) {
        max_dtr = card->csd.max_dtr;
    }

    return max_dtr;
}

/*
 * Handle the detection and initialisation of a card.
 *
 * In the case of a resume, "oldcard" will contain the card
 * we're trying to reinitialise.
 */
static int32_t mmc_sd_init_card(struct mmc_card *card, struct mmc_host *host)
{
    int32_t err = 0;

    /*
     * I/O voltage should be 3.3 V here for the initialization needed.
     */

    /* cmd2, send cid, check if card support 3.3V */
    err = mmc_all_send_cid(host, card->cidno);
    if (err) {
        SD_LOGW("Cards all send CID number failed !!\n");
        return -1;
    } else
        SD_LOGN("Card CID number:%x\n", (unsigned int)card->cidno[0]);

    card->type = MMC_TYPE_SD;

    /* cmd3, For native busses: get card RCA and quit open drain mode. */
    err = mmc_send_relative_addr(card->host, &card->rca);
    if (err) {
        SD_LOGW("Card public new RCA failed !!\n");
        return -1;
    } else
        SD_LOGD("Card public new RCA:%x\n", (unsigned int)card->rca);

    /* cmd10, get CID register */
    if (mmc_send_cid(card)) {
        SD_LOGW("Card send CID reg failed !!\n");
        return -1;
    }

    /* cmd9, get CSD register */
    if (mmc_sd_get_csd(card)) {
        SD_LOGW("Card send CSD reg failed !!\n");
        return -1;
    }

    /* cmd7, Select card  to standby state, as all following commands rely on that. */
    if (mmc_select_card(card, 1)) {
        SD_LOGW("mmc_select_card failed !!\n");
        return -1;
    }

    err = mmc_sd_setup_card(host, card);
    if (err)
        goto free_card;

    /* Initialization sequence for UHS-I cards */
#ifdef SD_SUPPORT_VERSION3
    if (card->ocr.ocr & SD_ROCR_S18A) {
        err = mmc_sd_init_uhs_card(card);
        if (err)
            goto free_card;

        /* Card is an ultra-high-speed card */
        mmc_card_set_uhs(card);

        /*
         * Since initialization is now complete, enable preset
         * value registers for UHS-I cards.
         */
        mmc_host_clk_hold(card->host);
        HAL_SDC_Enable_Preset_Value(card->host, true);
        mmc_host_clk_release(card->host);
    } else
#endif
    {
        uint32_t clk;
        uint32_t retries = 3;

        while (retries) {
            err = mmc_sd_switch_hs(card);
            if (err < 0) {
                SD_LOGE("%s: Re-switch hs, err %d (retries = %u)\n",
                        __func__, (unsigned int)err, (unsigned int)retries);
                mmc_mdelay(5);
                retries--;
                continue;
            }
            break;
        }

        if (err <= 0) {
            SD_LOGW("switch to high speed error, use DS: 25 MHz\n");
            clk = 25000000;
            err = HAL_SDC_Update_Clk(card->host, clk);
            if (err)
                return -1;
        } else {
            mmc_card_set_highspeed(card);
            card->sd_bus_speed = HIGH_SPEED_BUS_SPEED;

            clk = mmc_sd_get_max_clock(card);
            err = HAL_SDC_Update_Clk(card->host, clk);
            if (err)
                return -1;
            SD_LOGN("card is switched to high speed mode, clk:%u KHz\n", (unsigned int)clk/1000);
        }

        /* Switch to wider bus (if supported). */
        if ((host->caps & MMC_CAP_4_BIT_DATA) &&
            (card->scr.bus_widths & SD_SCR_BUS_WIDTH_4)) {
            err = mmc_app_set_bus_width(card, MMC_BUS_WIDTH_4);
            if (err) {
                SD_LOGW("Set bus width error, use default 1 bit !!\n");
                return -1;
            }

            /* config SDMMC controller bus width */
            HAL_SDC_Set_BusWidth(card->host, MMC_BUS_WIDTH_4);
            SD_LOGN("Set bus width type: %d\n", MMC_BUS_WIDTH_4);
        }
    }

    mmc_add_card(card);

    return 0;

free_card:
    return err;
}

#ifdef CONFIG_SD_PM
static int32_t mmc_sd_suspend(struct mmc_host *host)
{
    struct mmc_card *card = host->card;

    if (card == NULL) {
        SD_LOGE_RAW(ROM_ERR_MASK, "card open fail\n");
        return -1;
    }

    mmc_card_open(card->id);
    card->suspend = 1;
    mmc_card_deinit(host->card);
    SD_LOGD("%s ok\n", __func__);

    mmc_card_close(card->id);

    return 0;
}

static int32_t mmc_sd_resume(struct mmc_host *host)
{
    struct mmc_card *card = host->card;

    if (card == NULL) {
        SD_LOGE_RAW(ROM_ERR_MASK, "card open fail\n");
        return -1;
    }

    mmc_card_open(card->id);
    mmc_rescan(card, host->sdc_id);
    card->suspend = 0;
    SD_LOGD("%s ok\n", __func__);

    mmc_card_close(card->id);

    return 0;
}

static const struct mmc_bus_ops sd_bus_ops = {
    .suspend = mmc_sd_suspend,
    .resume = mmc_sd_resume,
};
#endif

/*
 * Starting point for SD card init.
 */
int32_t mmc_attach_sd(struct mmc_card *card, struct mmc_host *host)
{
    int32_t err = 0;
    uint32_t ocr = 0;

    if (!host) {
        SD_LOGE_RAW(ROM_ERR_MASK, "%s,%d err", __func__, __LINE__);
        return -1;
    }

    //SD_LOGE("%s,%d\n",__FUNCTION__,__LINE__);
    /* send cmd41/55 to check operation condition */
    err = mmc_send_app_op_cond(host, 0, &ocr);
    if (err) {
        return err;
    }
    SD_LOGN("card ocr: %08x\n", (unsigned int)ocr);

    /*
     * Sanity check the voltages that the card claims to
     * support.
     */
    if (ocr & 0x7F) {
        SD_LOGW("%s: card claims to support voltages below the defined range."
                " These will be ignored.\n", __func__);
        ocr &= ~0x7F;
    }

    card->ocr.ocr = 0x7fffffff & ocr; /* set card not in busy state */

    err = mmc_sd_init_card(card, host);
    if (err) {
        goto out;
    }
    host->card = card;
#ifdef CONFIG_SD_PM
    if (!card->suspend) {
        mmc_attach_bus(host, &sd_bus_ops);
    }
#endif

out:
    return err;
}

void mmc_deattach_sd(struct mmc_card *card, struct mmc_host *host)
{
    mmc_select_card(card, 0);
    card->state &= ~MMC_STATE_HIGHSPEED;

#ifdef CONFIG_SD_PM
    if (!card->suspend) {
        mmc_detach_bus(host);
        host->card = NULL;
    }
#else
    host->card = NULL;
#endif
}

#endif /* CONFIG_USE_SD */
