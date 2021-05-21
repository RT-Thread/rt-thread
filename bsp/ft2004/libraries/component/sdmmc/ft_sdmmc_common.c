/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-08 13:45:15
 * @LastEditTime: 2021-04-14 15:49:41
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "ft_sdmmc_common.h"
#include "ft_sdmmc_cmd.h"
#include "ft_sdmmc.h"

static const char* TAG = "sdmmc_common";

ft_error_t Sdmmc_InitOCR(Sdmmc_Card_t* card)
{
    ft_error_t err;
    /* In SPI mode, READ_OCR (CMD58) command is used to figure out which voltage
     * ranges the card can support. This step is skipped since 1.8V isn't
     * supported on the ESP32.
     */

    u32 host_ocr = Sdmmc_GetHostOCR(card->host.io_voltage);
    if ((card->ocr & SD_OCR_SDHC_CAP) != 0) {
        host_ocr |= SD_OCR_SDHC_CAP;
    }
    /* Send SEND_OP_COND (ACMD41) command to the card until it becomes ready. */
    err = Sdmmc_SendCmdSendOpCond(card, host_ocr, &card->ocr);

    /* If time-out, re-try send_op_cond as MMC */
    if (err == ERR_SDMMC_TIMEOUT && !Sdmmc_IsHostSpi(card)) {
        FT_SDMMC_DEBUG_D("send_op_cond timeout, trying MMC");
        card->is_mmc = 1;
        err = Sdmmc_SendCmdSendOpCond(card, host_ocr, &card->ocr);
    }

    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E("%s: send_op_cond (1) returned 0x%x", __func__, err);
        return err;
    }
    if (Sdmmc_IsHostSpi(card)) {
        err = Sdmmc_SendCmdReadOCR(card, &card->ocr);
        if (err != ERR_SDMMC_OK) {
            FT_SDMMC_DEBUG_E("%s: read_ocr returned 0x%x", __func__, err);
            return err;
        }
    }
    FT_SDMMC_DEBUG_D("host_ocr=0x%x card_ocr=0x%x", host_ocr, card->ocr);

    /* Clear all voltage bits in host's OCR which the card doesn't support.
     * Don't touch CCS bit because in SPI mode cards don't report CCS in ACMD41
     * response.
     */
    host_ocr &= (card->ocr | (~SD_OCR_VOL_MASK));
    FT_SDMMC_DEBUG_D("Sdmmc_CardInit: host_ocr=%08x, card_ocr=%08x", host_ocr, card->ocr);
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_InitCID(Sdmmc_Card_t* card)
{
    ft_error_t err;
    Sdmmc_Resp_t raw_cid;
    if (!Sdmmc_IsHostSpi(card)) {
        err = Sdmmc_SendCmdAllSendCID(card, &raw_cid);
        if (err != ERR_SDMMC_OK) {
            FT_SDMMC_DEBUG_E("%s: all_send_cid returned 0x%x", __func__, err);
            return err;
        }
        if (!card->is_mmc) {
            err = Sdmmc_DecodeCID(raw_cid, &card->cid);
            if (err != ERR_SDMMC_OK) {
                FT_SDMMC_DEBUG_E("%s: decoding CID failed (0x%x)", __func__, err);
                return err;
            }
        } else {
            /* For MMC, need to know CSD to decode CID. But CSD can only be read
             * in data transfer mode, and it is not possible to read CID in data
             * transfer mode. We temporiliy store the raw cid and do the
             * decoding after the RCA is set and the card is in data transfer
             * mode.
             */
            memcpy(card->raw_cid, raw_cid, sizeof(Sdmmc_Resp_t));
        }
    } else {
        err = Sdmmc_SendCmdSendCID(card, &card->cid);
        if (err != ERR_SDMMC_OK) {
            FT_SDMMC_DEBUG_E("%s: send_cid returned 0x%x", __func__, err);
            return err;
        }
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_InitRCA(Sdmmc_Card_t* card)
{
    ft_error_t err;
    err = Sdmmc_SendCmdSetRelativeAddr(card, &card->rca);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E("%s: set_relative_addr returned 0x%x", __func__, err);
        return err;
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_InitMMCDecodeCID(Sdmmc_Card_t* card)
{
    ft_error_t err;
    Sdmmc_Resp_t raw_cid;
    memcpy(raw_cid, card->raw_cid, sizeof(raw_cid));
    err = Sdmmc_MMCDecodeCID(card->csd.mmcVer, raw_cid, &card->cid);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E("%s: decoding CID failed (0x%x)", __func__, err);
        return err;
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_InitCSD(Sdmmc_Card_t* card)
{
    //FT_SDMMC_DEBUG_I("is mem: %d", card->is_mem);
    assert(card->is_mem == 1);
    /* Get and decode the contents of CSD register. Determine card capacity. */
    ft_error_t err = Sdmmc_SendCmdSendCSD(card, &card->csd);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E("%s: send_csd returned 0x%x", __func__, err);
        return err;
    }
    const size_t max_sdsc_capacity = UINT32_MAX / card->csd.sectorSize + 1;
    if (!(card->ocr & SD_OCR_SDHC_CAP) &&
         card->csd.capacity > (int)max_sdsc_capacity) {
        FT_SDMMC_DEBUG_W("%s: SDSC card reports capacity=%u. Limiting to %u.",
                __func__, card->csd.capacity, max_sdsc_capacity);
        card->csd.capacity = max_sdsc_capacity;
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_InitSelectCard(Sdmmc_Card_t* card)
{
    assert(!Sdmmc_IsHostSpi(card));
    ft_error_t err = Sdmmc_SendCmdSelectCard(card, card->rca);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E("%s: select_card returned 0x%x", __func__, err);
        return err;
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_InitCardHsMode(Sdmmc_Card_t* card)
{
    ft_error_t err = ERR_SDMMC_NOT_SUPPORTED;
    if (card->is_mem && !card->is_mmc) {
        err = Sdmmc_EnableHsModeAndCheck(card);
    } /*else if (card->is_sdio) {
        err = sdmmc_io_enable_hs_mode(card);
    } */else if (card->is_mmc){
        err = Sdmmc_MMCEnableHsMode(card);
    }
    if (err == ERR_SDMMC_NOT_SUPPORTED) {
        FT_SDMMC_DEBUG_D("%s: host supports HS mode, but card doesn't", __func__);
        card->max_freq_khz = SDMMC_FREQ_DEFAULT;
    } else if (err != ERR_SDMMC_OK) {
        return err;
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_InitHostBusWidth(Sdmmc_Card_t* card)
{
    int bus_width = 1;

    if ((card->host.flags & SDMMC_HOST_FLAG_4BIT) &&
        (card->log_bus_width == 2)) {
        bus_width = 4;
    } else if ((card->host.flags & SDMMC_HOST_FLAG_8BIT) &&
        (card->log_bus_width == 3)) {
        bus_width = 8;
    }
    FT_SDMMC_DEBUG_D("%s: using %d-bit bus", __func__, bus_width);
    if (bus_width > 1) {
        ft_error_t err = (*card->host.set_bus_width)(card->host.slot, bus_width);
        if (err != ERR_SDMMC_OK) {
            FT_SDMMC_DEBUG_E("host.set_bus_width failed (0x%x)", err);
            return err;
        }
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_InitHostFreq(Sdmmc_Card_t* card)
{
    assert(card->max_freq_khz <= card->host.max_freq_khz);

    /* Find highest frequency in the following list,
     * which is below card->max_freq_khz.
     */
    const u32 freq_values[] = {
            SDMMC_FREQ_52M,
            SDMMC_FREQ_HIGHSPEED,
            SDMMC_FREQ_26M,
            SDMMC_FREQ_DEFAULT
            //NOTE: in sdspi mode, 20MHz may not work. in that case, add 10MHz here.
    };
    const int n_freq_values = sizeof(freq_values) / sizeof(freq_values[0]);

    u32 selected_freq = SDMMC_FREQ_PROBING;
    for (int i = 0; i < n_freq_values; ++i) {
        u32 freq = freq_values[i];
        if (card->max_freq_khz >= freq) {
            selected_freq = freq;
            break;
        }
    }

    FT_SDMMC_DEBUG_D("%s: using %d kHz bus frequency", __func__, selected_freq);
    if (selected_freq > SDMMC_FREQ_PROBING) {
        ft_error_t err = (*card->host.set_card_clk)(card->host.slot, selected_freq);
        if (err != ERR_SDMMC_OK) {
            FT_SDMMC_DEBUG_E("failed to switch bus frequency (0x%x)", err);
            return err;
        }
    }

    if (card->is_ddr) {
        if (card->host.set_bus_ddr_mode == NULL) {
            FT_SDMMC_DEBUG_E("host doesn't support DDR mode or voltage switching");
            return ERR_SDMMC_NOT_SUPPORTED;
        }
        ft_error_t err = (*card->host.set_bus_ddr_mode)(card->host.slot, TRUE);
        if (err != ERR_SDMMC_OK) {
            FT_SDMMC_DEBUG_E("failed to switch bus to DDR mode (0x%x)", err);
            return err;
        }
    }
    return ERR_SDMMC_OK;
}

void Sdmmc_FilpByteOrder(u32* response, size_t size)
{
    assert(size % (2 * sizeof(u32)) == 0);
    const size_t n_words = size / sizeof(u32);
    for (int i = 0; i < (int)n_words / 2; ++i) {
        u32 left = __builtin_bswap32(response[i]);
        u32 right = __builtin_bswap32(response[n_words - i - 1]);
        response[i] = right;
        response[n_words - i - 1] = left;
    }
}

void Sdmmc_CardPrintInfo(FILE* stream, const Sdmmc_Card_t* card)
{
    bool_t print_scr = FALSE;
    bool_t print_csd = FALSE;
    const char* type;
    Sdmmc_Printf("Name: %s\n", card->cid.name);
    if (card->is_sdio) {
        type = "SDIO";
        print_scr = TRUE;
        print_csd = TRUE;
    } else if (card->is_mmc) {
        type = "MMC";
        print_csd = TRUE;
    } else {
        type = (card->ocr & SD_OCR_SDHC_CAP) ? "SDHC/SDXC" : "SDSC";
    }
    Sdmmc_Printf("Type: %s\n", type);
    if (card->max_freq_khz < 1000) {
        Sdmmc_Printf("Speed: %d kHz\n", card->max_freq_khz);
    } else {
        Sdmmc_Printf("Speed: %d MHz%s\n", card->max_freq_khz / 1000,
                card->is_ddr ? ", DDR" : "");
    }
    Sdmmc_Printf("Size: %lluMB\n", ((uint64_t) card->csd.capacity) * card->csd.sectorSize / (1024 * 1024));

    if (print_csd) {
        Sdmmc_Printf("CSD: ver=%d, sectorSize=%d, capacity=%d read_bl_len=%d\n",
                card->csd.csdVer,
                card->csd.sectorSize, card->csd.capacity, card->csd.readBlkLen);
    }
    if (print_scr) {
        Sdmmc_Printf("SCR: sdSpec=%d, bus_width=%d\n", card->scr.sdSpec, card->scr.bus_width);
    }
}

ft_error_t Sdmmc_FixHostFlags(Sdmmc_Card_t* card)
{
    const u32 width_1bit = SDMMC_HOST_FLAG_1BIT;
    const u32 width_4bit = SDMMC_HOST_FLAG_4BIT;
    const u32 width_8bit = SDMMC_HOST_FLAG_8BIT;
    const u32 width_mask = width_1bit | width_4bit | width_8bit;

    int slot_bit_width = card->host.get_bus_width(card->host.slot);
    if (slot_bit_width == 1 &&
            (card->host.flags & (width_4bit | width_8bit))) {
        card->host.flags &= ~width_mask;
        card->host.flags |= width_1bit;
    } else if (slot_bit_width == 4 && (card->host.flags & width_8bit)) {
        if ((card->host.flags & width_4bit) == 0) {
            FT_SDMMC_DEBUG_W("slot width set to 4, but host flags don't have 4 line mode enabled; using 1 line mode");
            card->host.flags &= ~width_mask;
            card->host.flags |= width_1bit;
        } else {
            card->host.flags &= ~width_mask;
            card->host.flags |= width_4bit;
        }
    }

    return ERR_SDMMC_OK;
}
