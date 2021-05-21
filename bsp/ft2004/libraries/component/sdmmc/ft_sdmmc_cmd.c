/*
 * @ : Copyright (c) 2020 Phytium Information Technology, Inc. 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms
 * of an applicable Phytium license agreement.
 * @Date: 2021-04-08 11:51:03
 * @LastEditTime: 2021-04-15 13:39:44
 * @Description:  This files is for 
 * 
 * @Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include <string.h>
#include "ft_sdmmc_defs.h"
#include "ft_sdmmc_cmd.h"
#include "ft_sdmmc_common.h"

static const char* TAG = "sdmmc_cmd";

ft_error_t Sdmmc_SendCmd(Sdmmc_Card_t* card, Sdmmc_Cmd_t* cmd)
{
    if (card->host.command_timeout_ms != 0) {
        cmd->timeout_ms = card->host.command_timeout_ms;
    } else if (cmd->timeout_ms == 0) {
        cmd->timeout_ms = SDMMC_DEFAULT_CMD_TIMEOUT_MS;
    }

    int slot = card->host.slot;
    Sdmmc_TraceHeapAlloc("BEF-TRANS");
    FT_SDMMC_DEBUG_V( "sending cmd slot=%d op=%d arg=%x flags=%x data=%p blklen=%d datalen=%d timeout=%d",
            slot, cmd->opcode, cmd->arg, cmd->flags, cmd->data, cmd->blklen, cmd->datalen, cmd->timeout_ms);
    //FT_SDMMC_DEBUG_I("transaction handler %x", (*card->host.do_transaction));
    ft_error_t err = (*card->host.do_transaction)(slot, cmd);
    if (err != 0) {
        FT_SDMMC_DEBUG_E("cmd=%d, sdmmc_req_run returned 0x%x", cmd->opcode, err);
        return err;
    }
    Sdmmc_TraceHeapAlloc("AFT-TRANS");
    int state = MMC_R1_CURRENT_STATE(cmd->response);
    FT_SDMMC_DEBUG_V( "CMD %d type %d arg 0x%x \r\n response--------- \r\n %08x \r\n %08x \r\n %08x \r\n %08x \r\n err=0x%x state=%d \r\n ---------",
               cmd->opcode, cmd->cmd_resp_type, cmd->arg,
               cmd->response[0],
               cmd->response[1],
               cmd->response[2],
               cmd->response[3],
               cmd->error,
               state);
    return cmd->error;
}

ft_error_t Sdmmc_sendAppCmd(Sdmmc_Card_t* card, Sdmmc_Cmd_t* cmd)
{
    Sdmmc_Cmd_t app_cmd = {
        .opcode = MMC_APP_CMD,
        .flags = SCF_CMD_AC | SCF_RSP_R1,
        .cmd_resp_type = SCT_RESP_SHORT,
        .arg = MMC_ARG_RCA(card->rca)
    };
    Sdmmc_TraceHeapAlloc("BEF-SEND");
    ft_error_t err = Sdmmc_SendCmd(card, &app_cmd);
    if (err != ERR_SDMMC_OK) {
        return err;
    }
    // Check APP_CMD status bit (only in SD mode)
    Sdmmc_TraceHeapAlloc("AFT-SEND");
    if (!Sdmmc_IsHostSpi(card) && !(MMC_R1(app_cmd.response) & MMC_R1_APP_CMD)) {
        FT_SDMMC_DEBUG_E("card doesn't support APP_CMD");
        return ERR_SDMMC_NOT_SUPPORTED;
    }
    return Sdmmc_SendCmd(card, cmd);
}


ft_error_t Sdmmc_SendCmdGoIdleState(Sdmmc_Card_t* card)
{
    Sdmmc_Cmd_t cmd = {
        .opcode = MMC_GO_IDLE_STATE,
        .flags = SCF_CMD_BC | SCF_RSP_R0,
        .cmd_resp_type = SCT_RESP_NONE
    };
    ft_error_t err = Sdmmc_SendCmd(card, &cmd);
    if (Sdmmc_IsHostSpi(card)) {
        /* To enter SPI mode, CMD0 needs to be sent twice (see figure 4-1 in
         * SD Simplified spec v4.10). Some cards enter SD mode on first CMD0,
         * so don't expect the above command to succeed.
         * SCF_RSP_R1 flag below tells the lower layer to expect correct R1
         * response (in SPI mode).
         */
        (void) err;
        Sdmmc_Delay(SDMMC_GO_IDLE_DELAY_MS / get_sdmmc_os_impl()->tick_period);

        cmd.flags |= SCF_RSP_R1;
        err = Sdmmc_SendCmd(card, &cmd);
    }
    if (err == ERR_SDMMC_OK) {
        Sdmmc_Delay(SDMMC_GO_IDLE_DELAY_MS / get_sdmmc_os_impl()->tick_period);
    }
    return err;
}


ft_error_t Sdmmc_SendCmdSendIfCond(Sdmmc_Card_t* card, u32 ocr)
{
    const u8 pattern = 0xaa; /* any pattern will do here */
    Sdmmc_Cmd_t cmd = {
        .opcode = SD_SEND_IF_COND,
        .arg = (((ocr & SD_OCR_VOL_MASK) != 0) << 8) | pattern,
        .flags = SCF_CMD_BCR | SCF_RSP_R7,
        .cmd_resp_type = SCT_RESP_SHORT,
    };
    ft_error_t err = Sdmmc_SendCmd(card, &cmd);
    if (err != ERR_SDMMC_OK) {
        return err;
    }
    u8 response = cmd.response[0] & 0xff;
    if (response != pattern) {
        FT_SDMMC_DEBUG_E("%s: received=0x%x expected=0x%x", __func__, response, pattern);
        return ERR_SDMMC_INVALID_RESPONSE;
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_SendCmdSendOpCond(Sdmmc_Card_t* card, u32 ocr, u32 *ocrp)
{
    ft_error_t err;
    
    Sdmmc_Cmd_t cmd = {
            .arg = ocr,
            .flags = SCF_CMD_BCR | SCF_RSP_R3,
            .cmd_resp_type = SCT_RESP_SHORT,
            .opcode = SD_APP_OP_COND
    };
    int nretries = SDMMC_SEND_OP_COND_MAX_RETRIES;
    int err_cnt = SDMMC_SEND_OP_COND_MAX_ERRORS;
    for (; nretries != 0; --nretries)  {
        bzero(&cmd, sizeof cmd);
        cmd.arg = ocr;
        cmd.flags = SCF_CMD_BCR | SCF_RSP_R3;
        if (!card->is_mmc) { /* SD mode */
            cmd.opcode = SD_APP_OP_COND;
            cmd.cmd_resp_type = SCT_RESP_SHORT;
            err = Sdmmc_sendAppCmd(card, &cmd);
        } else { /* MMC mode */
            cmd.arg &= ~MMC_OCR_ACCESS_MODE_MASK;
            cmd.arg |= MMC_OCR_SECTOR_MODE;
            cmd.opcode = MMC_SEND_OP_COND;
            cmd.cmd_resp_type = SCT_RESP_SHORT;
            err = Sdmmc_SendCmd(card, &cmd);
        }
        
        if (err != ERR_SDMMC_OK) {
            if (--err_cnt == 0) {
                FT_SDMMC_DEBUG_E("%s: Sdmmc_sendAppCmd err=0x%x", __func__, err);
                return err;
            } else {
                FT_SDMMC_DEBUG_V( "%s: ignoring err=0x%x", __func__, err);
                continue;
            }
        }
        // In SD protocol, card sets MEM_READY bit in OCR when it is ready.
        // In SPI protocol, card clears IDLE_STATE bit in R1 response.
        if (!Sdmmc_IsHostSpi(card)) {
            if ((MMC_R3(cmd.response) & MMC_OCR_MEM_READY) ||
                ocr == 0) {
                break;
            }
        } else {
            if ((SD_SPI_R1(cmd.response) & SD_SPI_R1_IDLE_STATE) == 0) {
                break;
            }
        }
        Sdmmc_Delay(10 / get_sdmmc_os_impl()->tick_period);
    }
    if (nretries == 0) {
        return ERR_SDMMC_TIMEOUT;
    }
    if (ocrp) {
        *ocrp = MMC_R3(cmd.response);
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_SendCmdReadOCR(Sdmmc_Card_t *card, u32 *ocrp)
{
    assert(ocrp);
    Sdmmc_Cmd_t cmd = {
        .opcode = SD_READ_OCR,
        .flags = SCF_CMD_BCR | SCF_RSP_R2,
        .cmd_resp_type = SCT_RESP_LONG
    };
    ft_error_t err = Sdmmc_SendCmd(card, &cmd);
    if (err != ERR_SDMMC_OK) {
        return err;
    }
    *ocrp = SD_SPI_R3(cmd.response);
    return ERR_SDMMC_OK;
}


ft_error_t Sdmmc_SendCmdAllSendCID(Sdmmc_Card_t* card, Sdmmc_Resp_t* out_raw_cid)
{
    assert(out_raw_cid);
    Sdmmc_Cmd_t cmd = {
            .opcode = MMC_ALL_SEND_CID,
            .flags = SCF_CMD_BCR | SCF_RSP_R2,
            .cmd_resp_type = SCT_RESP_LONG           
    };
    ft_error_t err = Sdmmc_SendCmd(card, &cmd);
    if (err != ERR_SDMMC_OK) {
        return err;
    }
    memcpy(out_raw_cid, &cmd.response, sizeof(Sdmmc_Resp_t));
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_SendCmdSendCID(Sdmmc_Card_t *card, Sdmmc_CID_t *out_cid)
{
    assert(out_cid);
    assert(Sdmmc_IsHostSpi(card) && "SEND_CID should only be used in SPI mode");
    assert(!card->is_mmc && "MMC cards are not supported in SPI mode");
    Sdmmc_Resp_t buf;
    Sdmmc_Cmd_t cmd = {
        .opcode = MMC_SEND_CID,
        .flags = SCF_CMD_READ | SCF_CMD_ADTC,
        .cmd_resp_type = SCT_RESP_LONG,
        .arg = 0,
        .data = &buf[0],
        .datalen = sizeof(buf)
    };
    ft_error_t err = Sdmmc_SendCmd(card, &cmd);
    if (err != ERR_SDMMC_OK) {
        return err;
    }
    Sdmmc_FilpByteOrder(buf, sizeof(buf));
    return Sdmmc_DecodeCID(buf, out_cid);
}


ft_error_t Sdmmc_SendCmdSetRelativeAddr(Sdmmc_Card_t* card, uint16_t* out_rca)
{
    assert(out_rca);
    Sdmmc_Cmd_t cmd = {
            .opcode = SD_SEND_RELATIVE_ADDR,
            .flags = SCF_CMD_BCR | SCF_RSP_R6,
            .cmd_resp_type = SCT_RESP_SHORT
    };

    /* MMC cards expect us to set the RCA.
     * Set RCA to 1 since we don't support multiple cards on the same bus, for now.
     */
    uint16_t mmc_rca = 1;
    if (card->is_mmc) {
        cmd.arg = MMC_ARG_RCA(mmc_rca);
    }

    ft_error_t err = Sdmmc_SendCmd(card, &cmd);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E("send CMD RCA failed!!");
        return err;
    }
    
    *out_rca = (card->is_mmc) ? mmc_rca : SD_R6_RCA(cmd.response);
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_SendCmdSetBlkLen(Sdmmc_Card_t* card, Sdmmc_CSD_t* csd)
{
    Sdmmc_Cmd_t cmd = {
            .opcode = MMC_SET_BLOCKLEN,
            .arg = csd->sectorSize,
            .flags = SCF_CMD_AC | SCF_RSP_R1,
            .cmd_resp_type = SCT_RESP_SHORT
    };
    return Sdmmc_SendCmd(card, &cmd);
}

ft_error_t Sdmmc_SendCmdSendCSD(Sdmmc_Card_t* card, Sdmmc_CSD_t* out_csd)
{
    /* The trick with SEND_CSD is that in SPI mode, it acts as a data read
     * command, while in SD mode it is an AC command with R2 response.
     */
    Sdmmc_Resp_t spi_buf;
    const bool_t is_spi = Sdmmc_IsHostSpi(card);
    Sdmmc_Cmd_t cmd = {
            .opcode = MMC_SEND_CSD,
            .arg = is_spi ? 0 : MMC_ARG_RCA(card->rca),
            .flags = is_spi ? (SCF_CMD_READ | SCF_CMD_ADTC | SCF_RSP_R1) :
                    (SCF_CMD_AC | SCF_RSP_R2),
            .cmd_resp_type = SCT_RESP_LONG,
            .data = is_spi ? &spi_buf[0] : 0,
            .datalen = is_spi ? sizeof(spi_buf) : 0,
    };
    ft_error_t err = Sdmmc_SendCmd(card, &cmd);
    if (err != ERR_SDMMC_OK) {
        return err;
    }
    u32* ptr = cmd.response;
    if (is_spi) {
        Sdmmc_FilpByteOrder(spi_buf,  sizeof(spi_buf));
        ptr = spi_buf;
    }
    if (card->is_mmc) {
        err = Sdmmc_MMCDecodeCSD(cmd.response, out_csd);
    } else {
        err = Sdmmc_DecodeCSD(ptr, out_csd);
    }
    return err;
}

ft_error_t Sdmmc_SendCmdSelectCard(Sdmmc_Card_t* card, u32 rca)
{
    /* Don't expect to see a response when de-selecting a card */
    u32 response = (rca == 0) ? 0 : SCF_RSP_R1;
    Sdmmc_Cmd_t cmd = {
            .opcode = MMC_SELECT_CARD,
            .arg = MMC_ARG_RCA(rca),
            .flags = SCF_CMD_AC | response,
            .cmd_resp_type = SCT_RESP_SHORT
    };
    return Sdmmc_SendCmd(card, &cmd);
}

ft_error_t Sdmmc_SendCmdSendSCR(Sdmmc_Card_t* card, Sdmmc_SCR_t *out_scr)
{
    size_t datalen = 8;
    u32* buf = (u32*) Sdmmc_HeapMalloc(datalen);
    if (buf == NULL) {
        return ERR_SDMMC_NO_MEM;
    }
    Sdmmc_Cmd_t cmd = {
            .data = buf,
            .datalen = datalen,
            .blklen = datalen,
            .flags = SCF_CMD_ADTC | SCF_CMD_READ | SCF_RSP_R1,
            .cmd_resp_type = SCT_RESP_SHORT,
            .opcode = SD_APP_SEND_SCR
    };
    Sdmmc_TraceHeapAlloc("BEF-APP-CMD");
    ft_error_t err = Sdmmc_sendAppCmd(card, &cmd);
    Sdmmc_TraceHeapAlloc("AFT-APP-CMD");
    if (err == ERR_SDMMC_OK) {
        err = Sdmmc_DecodeSCR(buf, out_scr);

        // if (ERR_SDMMC_OK != err){
        //     //dump_hex((u8*)buf, datalen * sizeof(u32));
        // }

        Sdmmc_TraceHeapAlloc("AFT-DECODE-SCR");
        FT_SDMMC_DEBUG_E("result: %x, bus width: %d, sd spec: %d", err,
                            out_scr->bus_width, out_scr->sdSpec);            
    }
    Sdmmc_HeapFree(buf);
    return err;
}

ft_error_t Sdmmc_SendCmdSetBusWidth(Sdmmc_Card_t* card, int width)
{
    Sdmmc_Cmd_t cmd = {
            .opcode = SD_APP_SET_BUS_WIDTH,
            .flags = SCF_RSP_R1 | SCF_CMD_AC,
            .cmd_resp_type = SCT_RESP_SHORT,
            .arg = (width == 4) ? SD_ARG_BUS_WIDTH_4 : SD_ARG_BUS_WIDTH_1,
    };

    return Sdmmc_sendAppCmd(card, &cmd);
}

ft_error_t Sdmmc_SendCmdCrcOnOff(Sdmmc_Card_t* card, bool_t crc_enable)
{
    assert(Sdmmc_IsHostSpi(card) && "CRC_ON_OFF can only be used in SPI mode");
    Sdmmc_Cmd_t cmd = {
            .opcode = SD_CRC_ON_OFF,
            .arg = crc_enable ? 1 : 0,
            .flags = SCF_CMD_AC | SCF_RSP_R1,
            .cmd_resp_type = SCT_RESP_SHORT
    };
    return Sdmmc_SendCmd(card, &cmd);
}

ft_error_t Sdmmc_SendCmdSendStatus(Sdmmc_Card_t* card, u32* out_status)
{
    Sdmmc_Cmd_t cmd = {
            .opcode = MMC_SEND_STATUS,
            .arg = MMC_ARG_RCA(card->rca),
            .flags = SCF_CMD_AC | SCF_RSP_R1,
            .cmd_resp_type = SCT_RESP_SHORT
    };
    ft_error_t err = Sdmmc_SendCmd(card, &cmd);
    if (err != ERR_SDMMC_OK) {
        return err;
    }
    if (out_status) {
        *out_status = MMC_R1(cmd.response);
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_SendCmdSwitch(Sdmmc_Card_t* card)
{
    size_t datalen = 64;
    ft_error_t err;
    u32* buf = (u32*) Sdmmc_HeapMalloc(datalen);
    if (buf == NULL) {
        return ERR_SDMMC_NO_MEM;
    }
    //memset(buf, 0, sizeof(u32) * datalen);
    // Sdmmc_Cmd_t cmd = {
    //         .opcode = MMC_SWITCH,
    //         .arg = 0x00FFFFF1,
    //         .flags = SCF_CMD_ADTC | SCF_RSP_R1,
    //         .cmd_resp_type = SCT_RESP_SHORT,
    //         .data = buf,
    //         .datalen = datalen,
    //         .blklen = datalen
    // };
    // ft_error_t err = Sdmmc_SendCmd(card, &cmd);
    // if (ERR_SDMMC_OK != err){
    //     goto _EXIT;
    // }

    // memset(buf, 0, sizeof(u32) * datalen);
    // Sdmmc_Cmd_t cmd2 = {
    //         .opcode = MMC_SWITCH,
    //         .arg = 0x80FFFFF1,
    //         .flags = SCF_CMD_ADTC | SCF_RSP_R1,
    //         .cmd_resp_type = SCT_RESP_SHORT,
    //         .data = buf,
    //         .datalen = datalen,
    //         .blklen = datalen         
    // };
    // err = Sdmmc_SendCmd(card, &cmd2);
    // if (ERR_SDMMC_OK != err){
    //     goto _EXIT;
    // }

    memset(buf, 0, datalen);
    Sdmmc_Cmd_t cmd3 = {
            .opcode = MMC_SWITCH,
            .arg = 0x00000002,
            .flags = SCF_CMD_ADTC | SCF_RSP_R1,
            .cmd_resp_type = SCT_RESP_SHORT,
            //.data = buf,
            //.datalen = datalen,
            //.blklen = datalen         
    };
    err = Sdmmc_sendAppCmd(card, &cmd3);

_EXIT:
    Sdmmc_HeapFree(buf);
    return err;    
}

ft_error_t Sdmmc_WriteSectors(Sdmmc_Card_t* card, const void* src,
        size_t start_block, size_t block_count)
{
    ft_error_t err = ERR_SDMMC_OK;
    size_t block_size = card->csd.sectorSize;
    if ((Sdmmc_DMACapable(src)) && ((intptr_t)src % 4 == 0)) {
        err = Sdmmc_WriteSectorsDMA(card, src, start_block, block_count);
    } else {
        // SDMMC peripheral needs DMA-capable buffers. Split the write into
        // separate single block writes, if needed, and allocate a temporary
        // DMA-capable buffer.
        void* tmp_buf = Sdmmc_HeapMalloc(block_size);
        if (tmp_buf == NULL) {
            return ERR_SDMMC_NO_MEM;
        }
        const u8* cur_src = (const u8*) src;
        for (size_t i = 0; i < block_count; ++i) {
            memcpy(tmp_buf, cur_src, block_size);
            cur_src += block_size;
            err = Sdmmc_WriteSectorsDMA(card, tmp_buf, start_block + i, 1);
            if (err != ERR_SDMMC_OK) {
                FT_SDMMC_DEBUG_D("%s: error 0x%x writing block %d+%d",
                        __func__, err, start_block, i);
                break;
            }
        }
        FT_SDMMC_DEBUG_D("before free");
        Sdmmc_HeapFree(tmp_buf);
    }

    return err;
}

ft_error_t Sdmmc_WriteSectorsDMA(Sdmmc_Card_t* card, const void* src,
        size_t start_block, size_t block_count)
{
    if (start_block + block_count > (size_t)card->csd.capacity) {
        return ERR_SDMMC_INVALID_SIZE;
    }
    size_t block_size = card->csd.sectorSize;
    Sdmmc_Cmd_t cmd = {
            .flags = SCF_CMD_ADTC | SCF_RSP_R1,
            .cmd_resp_type = SCT_RESP_SHORT,
            .blklen = block_size,
            .data = (void*) src,
            .datalen = block_count * block_size,
            .timeout_ms = SDMMC_WRITE_CMD_TIMEOUT_MS
    };
    if (block_count == 1) {
        cmd.opcode = MMC_WRITE_BLOCK_SINGLE;
    } else {
        cmd.opcode = MMC_WRITE_BLOCK_MULTIPLE;
    }
    if (card->ocr & SD_OCR_SDHC_CAP) {
        cmd.arg = start_block;
    } else {
        cmd.arg = start_block * block_size;
    }
    ft_error_t err = Sdmmc_SendCmd(card, &cmd);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E("%s: Sdmmc_SendCmd returned 0x%x", __func__, err);
        return err;
    }
    u32 status = 0;
    size_t count = 0;
    while (!Sdmmc_IsHostSpi(card) && !(status & MMC_R1_READY_FOR_DATA)) {
        // TODO: add some timeout here
        err = Sdmmc_SendCmdSendStatus(card, &status);
        if (err != ERR_SDMMC_OK) {
            return err;
        }
        if (++count % 10 == 0) {
            FT_SDMMC_DEBUG_V( "waiting for card to become ready (%d)", count);
        }
    }
    return ERR_SDMMC_OK;
}

ft_error_t Sdmmc_ReadSectors(Sdmmc_Card_t* card, void* dst,
        size_t start_block, size_t block_count)
{
    ft_error_t err = ERR_SDMMC_OK;
    size_t block_size = card->csd.sectorSize;
    FT_SDMMC_DEBUG_I("Sdmmc_ReadSectors dst 0x%x", dst);
    if (Sdmmc_DMACapable(dst) && (intptr_t)dst % 4 == 0) {
        FT_SDMMC_DEBUG_I("1");
        err = Sdmmc_ReadSectorsDMA(card, dst, start_block, block_count);
    } else {
        // SDMMC peripheral needs DMA-capable buffers. Split the read into
        // separate single block reads, if needed, and allocate a temporary
        // DMA-capable buffer.
        FT_SDMMC_DEBUG_I("2");
        void* tmp_buf = Sdmmc_HeapMalloc(block_size);
        if (tmp_buf == NULL) {
            return ERR_SDMMC_NO_MEM;
        }
        u8* cur_dst = (u8*) dst;
        for (size_t i = 0; i < block_count; ++i) {
            err = Sdmmc_ReadSectorsDMA(card, tmp_buf, start_block + i, 1);
            if (err != ERR_SDMMC_OK) {
                FT_SDMMC_DEBUG_D("%s: error 0x%x writing block %d+%d",
                        __func__, err, start_block, i);
                break;
            }
            memcpy(cur_dst, tmp_buf, block_size);
            cur_dst += block_size;
        }
        Sdmmc_HeapFree(tmp_buf);
    }
    return err;
}

ft_error_t Sdmmc_ReadSectorsDMA(Sdmmc_Card_t* card, void* dst,
        size_t start_block, size_t block_count)
{
    if (start_block + block_count > (size_t)card->csd.capacity) {
        return ERR_SDMMC_INVALID_SIZE;
    }
    size_t block_size = card->csd.sectorSize;
    Sdmmc_Cmd_t cmd = {
            .flags = SCF_CMD_ADTC | SCF_CMD_READ | SCF_RSP_R1,
            .cmd_resp_type = SCT_RESP_SHORT,
            .blklen = block_size,
            .data = (void*) dst,
            .datalen = block_count * block_size
    };
    if (block_count == 1) {
        cmd.opcode = MMC_READ_BLOCK_SINGLE;
    } else {
        cmd.opcode = MMC_READ_BLOCK_MULTIPLE;
    }
    if (card->ocr & SD_OCR_SDHC_CAP) {
        cmd.arg = start_block;
    } else {
        cmd.arg = start_block * block_size;
    }
    ft_error_t err = Sdmmc_SendCmd(card, &cmd);
    if (err != ERR_SDMMC_OK) {
        FT_SDMMC_DEBUG_E("%s: Sdmmc_SendCmd returned 0x%x", __func__, err);
        return err;
    }
    u32 status = 0;
    size_t count = 0;
    while (!Sdmmc_IsHostSpi(card) && !(status & MMC_R1_READY_FOR_DATA)) {
        // TODO: add some timeout here
        err = Sdmmc_SendCmdSendStatus(card, &status);
        if (err != ERR_SDMMC_OK) {
            return err;
        }
        if (++count % 10 == 0) {
            FT_SDMMC_DEBUG_V( "waiting for card to become ready (%d)", count);
        }
    }
    return ERR_SDMMC_OK;
}

