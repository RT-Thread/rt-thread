/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-08 16:03:05
 * @LastEditTime: 2021-04-14 11:55:03
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include <unistd.h>
#include <assert.h>
#include "ft_sdmmc_defs.h"
#include "ft_sdmmc_common.h"

ft_error_t Sdmmc_InitMMCReadExtCSD(Sdmmc_Card_t* card)
{
    int card_type;
    ft_error_t err = ERR_SDMMC_OK;

    u8* ext_csd = Sdmmc_HeapMalloc(EXT_CSD_MMC_SIZE);
    if (!ext_csd) {
        FT_SDMMC_DEBUG_E("%s: could not allocate ext_csd", __func__);
        return ERR_SDMMC_NO_MEM;
    }

    uint32_t sectors = 0;

    FT_SDMMC_DEBUG_D("MMC version: %d", card->csd.mmcVer);
    if (card->csd.mmcVer < MMC_CSD_MMCVER_4_0) {
        err = ERR_SDMMC_NOT_SUPPORTED;
        goto out;
    }

    /* read EXT_CSD */
    err = Sdmmc_MMCSendExtCSDData(card, ext_csd, EXT_CSD_MMC_SIZE);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E("%s: send_ext_csd_data error 0x%x", __func__, err);
        goto out;
    }
    card_type = ext_csd[EXT_CSD_CARD_TYPE];

    card->is_ddr = 0;
    if (card_type & EXT_CSD_CARD_TYPE_F_52M_1_8V) {
        card->max_freq_khz = SDMMC_FREQ_52M;
        if ((card->host.flags & SDMMC_HOST_FLAG_DDR) &&
                card->host.max_freq_khz >= SDMMC_FREQ_26M &&
                card->host.get_bus_width(card->host.slot) == 4) {
            FT_SDMMC_DEBUG_D("card and host support DDR mode");
            card->is_ddr = 1;
        }
    } else if (card_type & EXT_CSD_CARD_TYPE_F_52M) {
        card->max_freq_khz = SDMMC_FREQ_52M;
    } else if (card_type & EXT_CSD_CARD_TYPE_F_26M) {
        card->max_freq_khz = SDMMC_FREQ_26M;
    } else {
        FT_SDMMC_DEBUG_W("%s: unknown CARD_TYPE 0x%x", __func__, card_type);
    }
    /* For MMC cards, use speed value from EXT_CSD */
    card->csd.transSpeed = card->max_freq_khz * 1000;
    FT_SDMMC_DEBUG_D("MMC card type %d, max_freq_khz=%d, is_ddr=%d", card_type, card->max_freq_khz, card->is_ddr);
    card->max_freq_khz = MIN(card->max_freq_khz, card->host.max_freq_khz);

    if (card->host.flags & SDMMC_HOST_FLAG_8BIT) {
        card->ext_csd.power_class = ext_csd[(card->max_freq_khz > SDMMC_FREQ_26M) ?
                EXT_CSD_PWR_CL_52_360 : EXT_CSD_PWR_CL_26_360] >> 4;
        card->log_bus_width = 3;
    } else if (card->host.flags & SDMMC_HOST_FLAG_4BIT) {
        card->ext_csd.power_class = ext_csd[(card->max_freq_khz > SDMMC_FREQ_26M) ?
                EXT_CSD_PWR_CL_52_360 : EXT_CSD_PWR_CL_26_360] & 0x0f;
        card->log_bus_width = 2;
    } else {
        card->ext_csd.power_class = 0; //card must be able to do full rate at powerclass 0 in 1-bit mode
        card->log_bus_width = 0;
    }

    sectors = ( ext_csd[EXT_CSD_SEC_COUNT + 0] << 0 )
        | ( ext_csd[EXT_CSD_SEC_COUNT + 1] << 8 )
        | ( ext_csd[EXT_CSD_SEC_COUNT + 2] << 16 )
        | ( ext_csd[EXT_CSD_SEC_COUNT + 3] << 24 );

    if (sectors > (2u * 1024 * 1024 * 1024) / 512) {
        card->csd.capacity = sectors;
    }

out:
    Sdmmc_HeapFree(ext_csd);
    return err;
}

ft_error_t Sdmmc_InitMMCBusWidth(Sdmmc_Card_t* card)
{
    ft_error_t err;
    if (card->ext_csd.power_class != 0) {
        err = Sdmmc_MMCSwitch(card, EXT_CSD_CMD_SET_NORMAL,
                EXT_CSD_POWER_CLASS, card->ext_csd.power_class);
        if (err != ERR_SDMMC_OK) {
            FT_SDMMC_DEBUG_E("%s: can't change power class (%d bit), 0x%x"
                    , __func__, card->ext_csd.power_class, err);
            return err;
        }
    }

    if (card->log_bus_width > 0) {
        int csd_bus_width_value = EXT_CSD_BUS_WIDTH_1;
        int bus_width = 1;
        if (card->log_bus_width == 2) {
            if (card->is_ddr) {
                csd_bus_width_value = EXT_CSD_BUS_WIDTH_4_DDR;
            } else {
                csd_bus_width_value = EXT_CSD_BUS_WIDTH_4;
            }
            bus_width = 4;
        } else if (card->log_bus_width == 3) {
            if (card->is_ddr) {
                csd_bus_width_value = EXT_CSD_BUS_WIDTH_8_DDR;
            } else {
                csd_bus_width_value = EXT_CSD_BUS_WIDTH_8;
            }
            bus_width = 8;
        }
        err = Sdmmc_MMCSwitch(card, EXT_CSD_CMD_SET_NORMAL,
                EXT_CSD_BUS_WIDTH, csd_bus_width_value);
        if (err != ERR_SDMMC_OK) {
            FT_SDMMC_DEBUG_E("%s: can't change bus width (%d bit), 0x%x",
                    __func__, bus_width, err);
            return err;
        }
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_MMCEnableHsMode(Sdmmc_Card_t* card)
{
    ft_error_t err;
    if (card->max_freq_khz > SDMMC_FREQ_26M) {
        /* switch to high speed timing */
        err = Sdmmc_MMCSwitch(card, EXT_CSD_CMD_SET_NORMAL,
                EXT_CSD_HS_TIMING, EXT_CSD_HS_TIMING_HS);
        if (err != ERR_SDMMC_OK) {
            FT_SDMMC_DEBUG_E("%s: mmc_switch EXT_CSD_HS_TIMING_HS error 0x%x",
                    __func__, err);
            return err;
        }
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_MMCDecodeCID(int mmcVer, Sdmmc_Resp_t resp, Sdmmc_CID_t* out_cid)
{
    if (mmcVer == MMC_CSD_MMCVER_1_0 ||
            mmcVer == MMC_CSD_MMCVER_1_4) {
        out_cid->mfgId = MMC_CID_MID_V1(resp);
        out_cid->oemId = 0;
        MMC_CID_PNM_V1_CPY(resp, out_cid->name);
        out_cid->revision = MMC_CID_REV_V1(resp);
        out_cid->serial = MMC_CID_PSN_V1(resp);
        out_cid->date = MMC_CID_MDT_V1(resp);
    } else if (mmcVer == MMC_CSD_MMCVER_2_0 ||
            mmcVer == MMC_CSD_MMCVER_3_1 ||
            mmcVer == MMC_CSD_MMCVER_4_0) {
        out_cid->mfgId = MMC_CID_MID_V2(resp);
        out_cid->oemId = MMC_CID_OID_V2(resp);
        MMC_CID_PNM_V1_CPY(resp, out_cid->name);
        out_cid->revision = 0;
        out_cid->serial = MMC_CID_PSN_V1(resp);
        out_cid->date = 0;
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_MMCDecodeCSD(Sdmmc_Resp_t response, Sdmmc_CSD_t* out_csd)
{
    out_csd->csdVer = MMC_CSD_CSDVER(response);
    if (out_csd->csdVer == MMC_CSD_CSDVER_1_0 ||
            out_csd->csdVer == MMC_CSD_CSDVER_2_0 ||
            out_csd->csdVer == MMC_CSD_CSDVER_EXT_CSD) {
        out_csd->mmcVer = MMC_CSD_MMCVER(response);
        out_csd->capacity = MMC_CSD_CAPACITY(response);
        out_csd->readBlkLen = MMC_CSD_READ_BL_LEN(response);
    } else {
        FT_SDMMC_DEBUG_E("unknown MMC CSD structure version 0x%x\n", out_csd->csdVer);
        return 1;
    }
    int read_bl_size = 1 << out_csd->readBlkLen;
    out_csd->sectorSize = MIN(read_bl_size, 512);
    if (out_csd->sectorSize < read_bl_size) {
        out_csd->capacity *= read_bl_size / out_csd->sectorSize;
    }
    /* transSpeed will be determined when reading CXD */
    out_csd->transSpeed = 0;
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_MMCSendExtCSDData(Sdmmc_Card_t* card, void *out_data, size_t datalen)
{
    assert(Sdmmc_DMACapable(out_data));
    Sdmmc_Cmd_t cmd = {
        .data = out_data,
        .datalen = datalen,
        .blklen = datalen,
        .opcode = MMC_SEND_EXT_CSD,
        .arg = 0,
        .flags = SCF_CMD_ADTC | SCF_RSP_R1 | SCF_CMD_READ,
        .cmd_resp_type = SCT_RESP_SHORT
    };
    return Sdmmc_SendCmd(card, &cmd);
}

ft_error_t Sdmmc_MMCSwitch(Sdmmc_Card_t* card, u8 set, u8 index, u8 value)
{
    Sdmmc_Cmd_t cmd = {
            .opcode = MMC_SWITCH,
            .arg = (MMC_SWITCH_MODE_WRITE_BYTE << 24) | (index << 16) | (value << 8) | set,
            .flags = SCF_RSP_R1B | SCF_CMD_AC | SCF_WAIT_BUSY,
            .cmd_resp_type = SCT_RESP_SHORT
    };
    ft_error_t err = Sdmmc_SendCmd(card, &cmd);
    if (err == ERR_SDMMC_OK) {
        //check response bit to see that switch was accepted
        if (MMC_R1(cmd.response) & MMC_R1_SWITCH_ERROR)
            err = ERR_SDMMC_INVALID_RESPONSE;
    }

    return err;
}

ft_error_t Sdmmc_InitMMCCheckCSD(Sdmmc_Card_t* card)
{
    ft_error_t err;
    assert(card->is_mem == 1);
    assert(card->rca != 0);
    //The card will not respond to send_csd command in the transfer state.
    //Deselect it first.
    err = Sdmmc_SendCmdSelectCard(card, 0);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E("%s: select_card returned 0x%x", __func__, err);
        return err;
    }

    Sdmmc_CSD_t csd;
    /* Get the contents of CSD register to verify the communication over CMD line
       is OK. */
    err = Sdmmc_SendCmdSendCSD(card, &csd);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E("%s: send_csd returned 0x%x", __func__, err);
        return err;
    }

    //Select the card again
    err = Sdmmc_SendCmdSelectCard(card, card->rca);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E("%s: select_card returned 0x%x", __func__, err);
        return err;
    }
    return ERR_SDMMC_OK;
}
