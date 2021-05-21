/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-08 11:51:42
 * @LastEditTime: 2021-04-14 11:55:34
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */
#include <string.h>
#include <limits.h>
#include "ft_sdmmc_defs.h"
#include "ft_sdmmc.h"
#include "ft_sdmmc_common.h"

ft_error_t Sdmmc_InitSdIfCond(Sdmmc_Card_t* card)
{
    /* SEND_IF_COND (CMD8) command is used to identify SDHC/SDXC cards.
     * SD v1 and non-SD cards will not respond to this command.
     */
    u32 host_ocr = Sdmmc_GetHostOCR(card->host.io_voltage);
    ft_error_t err = Sdmmc_SendCmdSendIfCond(card, host_ocr);
    if (err == ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_D( "SDHC/SDXC card");
        host_ocr |= SD_OCR_SDHC_CAP;
    } else if (err == ERR_SDMMC_TIMEOUT) {
        FT_SDMMC_DEBUG_D( "CMD8 timeout; not an SD v2.00 card");
    } else if (Sdmmc_IsHostSpi(card) && err == ERR_SDMMC_NOT_SUPPORTED) {
        FT_SDMMC_DEBUG_D( "CMD8 rejected; not an SD v2.00 card");
    } else {
        FT_SDMMC_DEBUG_E( "%s: send_if_cond (1) returned 0x%x", __func__, err);
        return err;
    }
    card->ocr = host_ocr;
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_InitSdBlkLen(Sdmmc_Card_t* card)
{
    /* SDSC cards support configurable data block lengths.
     * We don't use this feature and set the block length to 512 bytes,
     * same as the block length for SDHC cards.
     */
    if ((card->ocr & SD_OCR_SDHC_CAP) == 0) {
        ft_error_t err = Sdmmc_SendCmdSetBlkLen(card, &card->csd);
        if (err != ERR_SDMMC_OK) {
            FT_SDMMC_DEBUG_E( "%s: set_blocklen returned 0x%x", __func__, err);
            return err;
        }
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_InitSdSCR(Sdmmc_Card_t* card)
{
    ft_error_t err;
    /* Get the contents of SCR register: bus width and the version of SD spec
     * supported by the card.
     * In SD mode, this is the first command which uses D0 line. Errors at
     * this step usually indicate connection issue or lack of pull-up resistor.
     */
    err = Sdmmc_SendCmdSendSCR(card, &card->scr);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E( "%s: send_scr (1) returned 0x%x", __func__, err);
        return err;
    }

    if ((card->scr.bus_width & SCR_SD_BUS_WIDTHS_4BIT)
            && (card->host.flags & SDMMC_HOST_FLAG_4BIT)) {
        card->log_bus_width = 2;
    } else {
        card->log_bus_width = 0;
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_InitSwitchHs(Sdmmc_Card_t* card)
{
    ft_error_t err;

    err = Sdmmc_SendCmdSwitch(card);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E("switch card to high speed failed !!");
        return err;
    }

    return err;
}

ft_error_t Sdmmc_InitSdBusWidth(Sdmmc_Card_t* card)
{
    int width = 1;
    if (card->log_bus_width == 2) {
        width = 4;
    } else if (card->log_bus_width == 3) {
        width = 8;
    }
    ft_error_t err = Sdmmc_SendCmdSetBusWidth(card, width);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E( "set_bus_width failed (0x%x)", err);
        return err;
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_InitSdWaitDataReady(Sdmmc_Card_t* card)
{
    /* Wait for the card to be ready for data transfers */
    u32 status = 0;
    u32 count = 0;
    while (!Sdmmc_IsHostSpi(card) && !(status & MMC_R1_READY_FOR_DATA)) {
        // TODO: add some timeout here
        ft_error_t err = Sdmmc_SendCmdSendStatus(card, &status);
        if (err != ERR_SDMMC_OK) {
            return err;
        }
        if (++count % 16 == 0) {
            FT_SDMMC_DEBUG_V("waiting for card to become ready (%d)", count);
        }
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_SendCmdSwitchFunc(Sdmmc_Card_t* card,
        u32 mode, u32 group, u32 function,
        Sdmmc_SwitchFuncRsp_t* resp)
{
    if (card->scr.sdSpec < SCR_SD_SPEC_VER_1_10 ||
        ((card->csd.cardCmdClass & SD_CSD_CCC_SWITCH) == 0)) {
            return ERR_SDMMC_NOT_SUPPORTED;
    }

    if (group == 0 ||
        group > SD_SFUNC_GROUP_MAX ||
        function > SD_SFUNC_FUNC_MAX) {
        return ERR_SDMMC_INVALID_ARG;
    }

    if (mode > 1) {
        return ERR_SDMMC_INVALID_ARG;
    }

    u32 group_shift = (group - 1) << 2;
    /* all functions which should not be affected are set to 0xf (no change) */
    u32 other_func_mask = (0x00ffffff & ~(0xf << group_shift));
    u32 func_val = (function << group_shift) | other_func_mask;

    Sdmmc_Cmd_t cmd = {
            .opcode = MMC_SWITCH,
            .flags = SCF_CMD_ADTC | SCF_CMD_READ | SCF_RSP_R1,
            .cmd_resp_type = SCT_RESP_SHORT,
            .blklen = sizeof(Sdmmc_SwitchFuncRsp_t),
            .data = resp->data,
            .datalen = sizeof(Sdmmc_SwitchFuncRsp_t),
            .arg = (!!mode << 31) | func_val
    };

    ft_error_t err = Sdmmc_SendCmd(card, &cmd);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E( "%s: Sdmmc_SendCmd returned 0x%x", __func__, err);
        return err;
    }
    Sdmmc_FilpByteOrder(resp->data, sizeof(Sdmmc_SwitchFuncRsp_t));
    u32 resp_ver = SD_SFUNC_VER(resp->data);
    if (resp_ver == 0) {
        /* busy response is never sent */
    } else if (resp_ver == 1) {
        if (SD_SFUNC_BUSY(resp->data, group) & (1 << function)) {
            FT_SDMMC_DEBUG_D( "%s: response indicates function %d:%d is busy",
                    __func__, group, function);
            return ERR_SDMMC_INVALID_STATE;
        }
    } else {
        FT_SDMMC_DEBUG_D( "%s: got an invalid version of SWITCH_FUNC response: 0x%02x",
                __func__, resp_ver);
        return ERR_SDMMC_INVALID_RESPONSE;
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_EnableHsMode(Sdmmc_Card_t* card)
{
    /* This will determine if the card supports SWITCH_FUNC command,
     * and high speed mode. If the cards supports both, this will enable
     * high speed mode at the card side.
     */
    if (card->scr.sdSpec < SCR_SD_SPEC_VER_1_10 ||
        ((card->csd.cardCmdClass & SD_CSD_CCC_SWITCH) == 0)) {
            return ERR_SDMMC_NOT_SUPPORTED;
    }
    Sdmmc_SwitchFuncRsp_t* response = (Sdmmc_SwitchFuncRsp_t*)
            Sdmmc_HeapMalloc(sizeof(*response));
    if (response == NULL) {
        return ERR_SDMMC_NO_MEM;
    }

    ft_error_t err = Sdmmc_SendCmdSwitchFunc(card, 0, SD_ACCESS_MODE, 0, response);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_D( "%s: Sdmmc_SendCmdSwitchFunc (1) returned 0x%x", __func__, err);
        goto out;
    }
    u32 supported_mask = SD_SFUNC_SUPPORTED(response->data, 1);
    if ((supported_mask & BIT(SD_ACCESS_MODE_SDR25)) == 0) {
        err = ERR_SDMMC_NOT_SUPPORTED;
        goto out;
    }
    err = Sdmmc_SendCmdSwitchFunc(card, 1, SD_ACCESS_MODE, SD_ACCESS_MODE_SDR25, response);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_D( "%s: Sdmmc_SendCmdSwitchFunc (2) returned 0x%x", __func__, err);
        goto out;
    }

out:
    Sdmmc_HeapFree(response);
    return err;
}

ft_error_t Sdmmc_EnableHsModeAndCheck(Sdmmc_Card_t* card)
{
    /* All cards should support at least default speed */
    card->max_freq_khz = SDMMC_FREQ_DEFAULT;
    if (card->host.max_freq_khz <= card->max_freq_khz) {
        /* Host is configured to use low frequency, don't attempt to switch */
        card->max_freq_khz = card->host.max_freq_khz;
        return ERR_SDMMC_OK;
    }

    /* Try to enabled HS mode */
    ft_error_t err = Sdmmc_EnableHsMode(card);
    if (err != ERR_SDMMC_OK) {
        return err;
    }
    /* HS mode has been enabled on the card.
     * Read CSD again, it should now indicate that the card supports
     * 50MHz clock.
     * Since SEND_CSD is allowed only in standby mode, and the card is currently in data transfer
     * mode, deselect the card first, then get the CSD, then select the card again. This step is
     * not required in SPI mode, since CMD7 (select_card) is not supported.
     */
    const bool_t is_spi = Sdmmc_IsHostSpi(card);
    if (!is_spi) {
        err = Sdmmc_SendCmdSelectCard(card, 0);
        if (err != ERR_SDMMC_OK) {
            FT_SDMMC_DEBUG_E( "%s: select_card (1) returned 0x%x", __func__, err);
            return err;
        }
    }
    err = Sdmmc_SendCmdSendCSD(card, &card->csd);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E( "%s: send_csd returned 0x%x", __func__, err);
        return err;
    }
    if (!is_spi) {
        err = Sdmmc_SendCmdSelectCard(card, card->rca);
        if (err != ERR_SDMMC_OK) {
            FT_SDMMC_DEBUG_E( "%s: select_card (2) returned 0x%x", __func__, err);
            return err;
        }
    }

    if (card->csd.transSpeed != 50000000) {
        FT_SDMMC_DEBUG_W("unexpected: after enabling HS mode, transSpeed=%d", card->csd.transSpeed);
        return ERR_SDMMC_NOT_SUPPORTED;
    }

    card->max_freq_khz = SDMMC_FREQ_HIGHSPEED;
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_CheckSCR(Sdmmc_Card_t* card)
{
    /* If frequency switch has been performed, read SCR register one more time
     * and compare the result with the previous one. Use this simple check as
     * an indicator of potential signal integrity issues.
     */
    Sdmmc_SCR_t scr_tmp;
    ft_error_t err = Sdmmc_SendCmdSendSCR(card, &scr_tmp);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E( "%s: send_scr returned 0x%x", __func__, err);
        return err;
    }
    if (memcmp(&card->scr, &scr_tmp, sizeof(scr_tmp)) != 0) {
        FT_SDMMC_DEBUG_E( "got corrupted data after increasing clock frequency");
        return ERR_SDMMC_INVALID_RESPONSE;
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_InitSpiCrc(Sdmmc_Card_t* card)
{
    /* In SD mode, CRC checks of data transfers are mandatory and performed
     * by the hardware. In SPI mode, CRC16 of data transfers is optional and
     * needs to be enabled.
     */
    assert(Sdmmc_IsHostSpi(card));
    ft_error_t err = Sdmmc_SendCmdCrcOnOff(card, TRUE);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E( "%s: Sdmmc_SendCmdCrcOnOff returned 0x%x", __func__, err);
        return err;
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_DecodeCID(Sdmmc_Resp_t resp, Sdmmc_CID_t* out_cid)
{
    out_cid->mfgId = SD_CID_MID(resp);
    out_cid->oemId = SD_CID_OID(resp);
    SD_CID_PNM_CPY(resp, out_cid->name);
    out_cid->revision = SD_CID_REV(resp);
    out_cid->serial = SD_CID_PSN(resp);
    out_cid->date = SD_CID_MDT(resp);
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_DecodeCSD(Sdmmc_Resp_t response, Sdmmc_CSD_t* out_csd)
{
    out_csd->csdVer = SD_CSD_CSDVER(response);
    FT_SDMMC_DEBUG_I("is sd v%d.0", out_csd->csdVer + 1);
    switch (out_csd->csdVer) {
    case SD_CSD_CSDVER_2_0:
        out_csd->capacity = SD_CSD_V2_CAPACITY(response);
        out_csd->readBlkLen = SD_CSD_V2_BL_LEN;
        break;
    case SD_CSD_CSDVER_1_0:
        out_csd->capacity = SD_CSD_CAPACITY(response);
        out_csd->readBlkLen = SD_CSD_READ_BL_LEN(response);
        break;
    default:
        FT_SDMMC_DEBUG_E( "unknown SD CSD structure version 0x%x", out_csd->csdVer);
        return ERR_SDMMC_NOT_SUPPORTED;
    }
    
    out_csd->cardCmdClass = SD_CSD_CCC(response);
    int read_bl_size = 1 << out_csd->readBlkLen;
    out_csd->sectorSize = MIN(read_bl_size, 512);
    if (out_csd->sectorSize < read_bl_size) {
        out_csd->capacity *= read_bl_size / out_csd->sectorSize;
    }
    int speed = SD_CSD_SPEED(response);
    if (speed == SD_CSD_SPEED_50_MHZ) {
        out_csd->transSpeed = 50000000;
    } else {
        out_csd->transSpeed = 25000000;
    }
    
    FT_SDMMC_DEBUG_I("sd capacity is %dMB", ((out_csd->capacity / 1000) * out_csd->sectorSize)/1000);
    return ERR_SDMMC_OK;
}

#define be32_to_cpu(x) ((u32)(              \
    (((u32)(x) & (u32)0x000000ffUL) << 24) |        \
    (((u32)(x) & (u32)0x0000ff00UL) <<  8) |        \
    (((u32)(x) & (u32)0x00ff0000UL) >>  8) |        \
    (((u32)(x) & (u32)0xff000000UL) >> 24)))

ft_error_t Sdmmc_DecodeSCR(u32 *raw_scr, Sdmmc_SCR_t* out_scr)
{
    Sdmmc_Resp_t resp = { 0 };
    FT_SDMMC_DEBUG_D("raw scr 0x%x 0x%x", raw_scr[0], raw_scr[1]);
    resp[1] = be32_to_cpu(raw_scr[0]);
    resp[0] = be32_to_cpu(raw_scr[1]);
    FT_SDMMC_DEBUG_D("resp 0x%x 0x%x", resp[0], resp[1]);
    int ver = SCR_STRUCTURE(resp);
    if (ver != 0) {
        FT_SDMMC_DEBUG_E("not support!! scr version is %d", ver);
        return ERR_SDMMC_NOT_SUPPORTED;
    }
    out_scr->sdSpec = SCR_SD_SPEC(resp);
    out_scr->bus_width = SCR_SD_BUS_WIDTHS(resp);
    return ERR_SDMMC_OK;
}

