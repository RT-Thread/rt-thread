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

#include "hal_def.h"

#include "sdio.h"
#include "sdmmc.h"
#include "hal_sdhost.h"

#include "_sdhost.h"
#include "_mmc.h"
#include "_sd.h"

#ifdef CONFIG_USE_MMC

/*
 int32_t mmc_sd_get_csd(struct mmc_card *card) //static
{
    struct mmc_command cmd = {0};
    uint32_t csd[4] = {0};

    cmd.opcode = MMC_SEND_CSD;
    cmd.arg = card->rca<<16;
    cmd.flags = MMC_RSP_R2 | MMC_CMD_AC;

    if (mmc_wait_for_cmd(card->host, &cmd)) {
        return -1;
    }

    HAL_Memcpy((void *)csd, (void *)cmd.resp, 16);

    //decode CSD reg
    card->csd.csd_ver  = (csd[3]>>30)&0x3;
    card->csd.trans_speed = csd[3]&0xff;
    card->csd.read_blk_len  = (csd[2]>>16)&0xf;
    if (card->type == CT_MMC || card->csd.csd_ver == 0) {
        card->csd.c_size_mult = (csd[1]>>15)&0x7;
        card->csd.c_size = ((csd[1]>>30)&0x3)|((csd[2]&0x3ff)<<2);
    } else {
        card->csd.c_size_mult = 0;
        card->csd.c_size = ((csd[1]>>16)&0xffff)|((csd[2]&0x3f)<<16);
    }
    card->csd.cmd_class  = (csd[2]>>20)&0xfff;
    card->csd.mmc_spec_ver  = (csd[3]>>26)&0xf;
    return 0;
}
*/

int32_t mmc_send_op_cond(struct mmc_card *card, uint32_t ocr, uint32_t *rocr)
{
    struct mmc_command cmd = {0};
    uint32_t i = 0;

    cmd.opcode = MMC_SEND_OP_COND;
    cmd.arg = 0;
    cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R3 | MMC_CMD_BCR;
    SD_LOGD("%s,%d arg use ocr?\n", __func__, __LINE__);
    do {
        if (mmc_wait_for_cmd(card->host, &cmd)) {
            return -1;
        }
        cmd.arg = 0x40000000|(cmd.resp[0]&0xFF8080);

#ifndef SYSTEM_SIMULATION
        HAL_MSleep(10);
        if (++i == 100)
            break;
#else
        smc_model_powerup_rdy(card->smc_no);
#endif
    } while(!(cmd.resp[0] & 0x80000000));

    if (!(cmd.resp[0] & 0x80000000)) {
        SD_LOGD("Wait card power up ready timeout, i = %d !\n", i);
        return -1;
    }
    cmd.resp[0] &= 0x7fffffff;
    HAL_Memcpy((void *)&card->ocr, (void *)&cmd.resp[0], 4);

    SD_LOGD("ocr = %08x !!\n", (unsigned int)cmd.resp[0]);

    if (card->ocr.high_capacity)  /* bit30 */
        mmc_card_set_blockaddr(card);

    return 0;
}

static int32_t mmc_public_new_rca(struct mmc_card *card)
{
    struct mmc_command cmd = {0};

    cmd.opcode = MMC_SET_RELATIVE_ADDR;
    cmd.arg = 0x1234 << 16;    // why 1234 ??
    cmd.flags = MMC_RSP_R1 | MMC_CMD_AC; //different from SD card;

    if (mmc_wait_for_cmd(card->host, &cmd)) {
        return -1;
    }

    card->rca = 0x1234;
    SD_LOGD("rca = %04x !!\n", (unsigned int)card->rca);

    return 0;
}

int32_t mmc_send_extcsd(struct mmc_card *card)
{
    struct mmc_command cmd = {0};
    struct mmc_data data = {0};
    struct mmc_request mrq;
    uint8_t extcsd[512] = {0};
    struct scatterlist sg = {0};
    sg.len = 512;
    sg.buffer = extcsd;

    cmd.opcode = MMC_SEND_EXT_CSD;
    cmd.arg = 0;
    cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
    cmd.data = &data;

    data.blksz = 512;
    data.sg_len = 1;
    data.sg = &sg;
    data.flags = MMC_DATA_READ;

    mrq.cmd = &cmd;
    mrq.data = &data;
    if (mmc_wait_for_req(card->host, &mrq)) {
        return -1;
    }

    SD_LOGD("%s,%d %s\n", __func__, __LINE__, "extcsd");
    sd_hex_dump_bytes((void *)extcsd, 512);

    //decode EXTCSD
    card->extcsd.version = extcsd[192];
    card->extcsd.card_type = extcsd[196];
    card->extcsd.csd_struc = extcsd[194];
    card->extcsd.hs_timing = extcsd[185];
    card->extcsd.bus_width = extcsd[183];
    if (extcsd[160] & MMC_SWITCH_PART_SUPPORT)
        card->extcsd.part_config = extcsd[179];
    if (card->extcsd.version >= 3)  //>=4.3
        card->extcsd.boot_bus_cond = extcsd[177];

    return 0;
}

static int32_t mmc_switch_buswidth(struct mmc_card *card, uint32_t width)
{
    uint8_t set_val;
    int32_t ret = -1;

    switch (width) {
        case MMC_BUS_WIDTH_1:
            set_val = MMC_EXT_CSD_BUS_WIDTH_1;
            break;
        case MMC_BUS_WIDTH_4:
            set_val = MMC_EXT_CSD_BUS_WIDTH_4;
            break;
        case MMC_BUS_WIDTH_8:
            set_val = MMC_EXT_CSD_BUS_WIDTH_8;
            break;
        default:
            set_val = MMC_EXT_CSD_BUS_WIDTH_1;
    }
    ret = mmc_switch(card, MMC_EXT_CSD_CMD_SET_NORMAL, MMC_EXT_CSD_BUS_WIDTH, set_val);

    if (-1 == ret) {
        SD_LOGW("Old-MMC Card with 1 bit data only!!\n");
        return -1;
    }

    SD_LOGD("RS-MMC Card!!\n");
    card->bus_width = width;

    return 0;
}

int32_t mmc_set_buswidth(struct mmc_card *card, uint32_t width)
{
    if (card->type == CT_MMC) {
        if (card->csd.mmc_spec_ver < MMC_CSD_SPEC_VER_4) {
            card->bus_width = width = MMC_BUS_WIDTH_1;
        } else if (mmc_switch_buswidth(card, width)) {
            SD_LOGD("Set bus width error, use default 1 bit !!\n");
            return -1;
        }
    } else if (card->type == CT_SDSC1x || card->type == CT_SDSC20 || \
               card->type == CT_SDHC20 || card->type == CT_SDXC30) {
        if (mmc_app_set_bus_width(card, width)) {
            SD_LOGD("Set bus width error, use default 1 bit !!\n");
            return -1;
        }
    } else
        return -1;

    HAL_SDC_Set_BusWidth(card->host, width);
    SD_LOGD("Set bus width type: %d !!\n", (unsigned int)width);

    return 0;
}

int32_t mmc_switch_part(struct mmc_card *card, uint32_t part_num)
{
    return mmc_switch(card, MMC_EXT_CSD_CMD_SET_NORMAL, MMC_EXT_CSD_PART_CONF,
              (card->extcsd.part_config & ~MMC_SWITCH_PART_ACCESS_MASK)
              | (part_num & MMC_SWITCH_PART_ACCESS_MASK));
}

int32_t mmc_switch_boot_part(struct mmc_card *card, uint32_t boot_ack, uint32_t boot_part)
{
    return mmc_switch(card, MMC_EXT_CSD_CMD_SET_NORMAL, MMC_EXT_CSD_PART_CONF,
              (card->extcsd.part_config & (~MMC_SWITCH_PART_BOOT_PART_MASK) & (~MMC_SWITCH_PART_BOOT_ACK_MASK))
              | ((boot_part << 3) & MMC_SWITCH_PART_BOOT_PART_MASK) | (boot_ack << 6));
}

int32_t mmc_switch_boot_bus_cond(struct mmc_card *card, uint32_t boot_mode, uint32_t rst_bus_cond, uint32_t bus_width)
{
    return mmc_switch(card, MMC_EXT_CSD_CMD_SET_NORMAL, MMC_EXT_CSD_BOOT_BUS_COND,
                      (card->extcsd.boot_bus_cond &
                       (~MMC_SWITCH_BOOT_MODE_MASK) &
                       (~MMC_SWITCH_BOOT_RST_BUS_COND_MASK) &
                       (~MMC_SWITCH_BOOT_BUS_WIDTH_MASK))
                      | ((boot_mode << 3) & MMC_SWITCH_BOOT_MODE_MASK)
                      | ((rst_bus_cond << 2) & MMC_SWITCH_BOOT_RST_BUS_COND_MASK)
                      | ((bus_width) & MMC_SWITCH_BOOT_BUS_WIDTH_MASK) );
}

int32_t smc_model_set_blkcnt(struct mmc_host *host, uint32_t blkcnt)
{
    struct mmc_command cmd = {0};

    cmd.opcode = MMC_SET_BLOCK_COUNT;
    cmd.arg = blkcnt & 0xffff;
    cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;

    if (mmc_wait_for_cmd(host, &cmd)) {
        return -1;
    }

    host->blkcnt = blkcnt;

    return 0;
}

int32_t sdmmc_stream_write(struct mmc_card *card, uint32_t blk_num, uint32_t blk_size, uint32_t sg_len, struct scatterlist *sg)
{
    struct mmc_command cmd = {0};
    struct mmc_data data = {0};
    struct mmc_request mrq;
    uint32_t status = 0;

    if (!card || !card->host) {
        SD_LOGE_RAW(ROM_ERR_MASK, "%s,%d err", __func__, __LINE__);
        return -1;
    }

    cmd.opcode = MMC_WRITE_SINGLE_BLOCK;
    cmd.arg = blk_num;
    if (!mmc_card_blockaddr(card))
        cmd.arg <<= 9;
    cmd.stop = 0;
    cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 |MMC_CMD_ADTC;
    cmd.data = &data;
    data.flags |= MMC_DATA_WRITE | MMC_DATA_STREAM;

    data.blksz = blk_size;
    data.sg_len = sg_len;
    data.sg = sg;
    mrq.cmd = &cmd;
    mrq.data = &data;
    if (mmc_wait_for_req(card->host, &mrq)) {
        return -1;
    }

    /* check busy */
    do {
        if (HAL_SDC_Is_Busy(card->host))
            continue;
        mmc_send_status(card, &status);
    } while (!(status & 0x100));
    return 0;
}

/*
 * Starting point for MMC card init.
 */
int mmc_attach_mmc(struct mmc_card *card, struct mmc_host *host)
{
    int err;
    uint32_t ocr;
    uint32_t clk = 400000;

    if (!host) {
        SD_LOGE_RAW(ROM_ERR_MASK, "%s,%d no host exist!\n", __func__, __LINE__);
        return -1;
    }
    //SD_WARN_ON(!host->claimed);

    /* send cmd1 to check MMC */
    err = mmc_send_op_cond(card, 0, &ocr);
    if (err)
        return err;

    card->type = CT_MMC;

    /* cmd2, send cid */
    if (mmc_all_send_cid(host, card->cidno)) {
        SD_LOGD("All cards send CID number failed !!\n");
        return -1;
    } else
        SD_LOGD("CID number:%x\n", (unsigned int)card->cidno[0]);

    SD_LOGD("%s,%d !!!!!!!@@@@@@@@ called mmc_attach_sd\n", __func__, __LINE__);
    /* cmd3, For native busses:  get card RCA and quit open drain mode. */
    err = mmc_public_new_rca(card);

    /* cmd10, get CID register */
    if (sdmmc_send_cid(card)) {
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

    if (card->csd.mmc_spec_ver < MMC_CSD_SPEC_VER_4)
        err = 0;
    else
        err = mmc_send_extcsd(card);
    if (err == -1)
        return -1;

    //sd-acmd6, set buswidth, mmc-cmd6, switch buswidth
    if (-1 == sdmmc_set_buswidth(card, 4))
        return -1;

    mmc_switch_to_high_speed(card);

    card->sd_bus_speed = SD_SWITCH_ACCESS_HS_SDR25;

    if (card->sd_bus_speed == SD_SWITCH_ACCESS_SDR104)
        clk = 208000000;
    else if (card->sd_bus_speed == SD_SWITCH_ACCESS_SDR50)
        clk = 104000000;
    else if (card->sd_bus_speed == SD_SWITCH_ACCESS_HS_SDR25)
        clk = 50000000;
    else
        clk = 25000000;

    clk = 50000000;

    HAL_SDC_Update_Clk(card->host, clk);

    sdmmc_enumerate_card_info(card);

    //send tunning pattern
    if (card->sd_bus_speed == SD_SWITCH_ACCESS_SDR104 || card->sd_bus_speed == SD_SWITCH_ACCESS_SDR50)
        sd_send_tuning_pattern(card);

    card->host->card = card;

    return err;
}

#endif /* CONFIG_USE_MMC */
