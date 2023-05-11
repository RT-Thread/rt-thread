/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
 * All Rights Reserved.
 *
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,
 * either version 1.0 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details.
 *
 *
 * FilePath: fnand_dma.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:56:22
 * Description:  This file is dma descriptor management API.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */


#include "fnand_dma.h"
#include "fnand.h"
#include "ferror_code.h"
#include "fdebug.h"
#include <string.h>
#include <stdio.h>
#include "fcache.h"
#include "fnand_toggle.h"
#include "sdkconfig.h"

#ifdef CONFIG_FNAND_DMA_DEBUG_EN
    #define FNAND_DMA_DEBUG_TAG "FNAND_DMA"
    #define FNAND_DMA_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FNAND_DMA_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_DMA_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FNAND_DMA_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_DMA_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FNAND_DMA_DEBUG_TAG, format, ##__VA_ARGS__)
#else
    #define FNAND_DMA_DEBUG_I(format, ...)
    #define FNAND_DMA_DEBUG_W(format, ...)
    #define FNAND_DMA_DEBUG_E(format, ...)
#endif


void FNandDmaDump(struct FNandDmaDescriptor *descriptor_p)
{
    FNAND_DMA_DEBUG_I("Phytium NFC cmd dump: ");
    FNAND_DMA_DEBUG_I("cmd0:%x, cmd1:%x, ctrl:%x, page_cnt:%d ",
                      descriptor_p->cmd0, descriptor_p->cmd1, descriptor_p->cmd_ctrl.ctrl, descriptor_p->page_cnt);
    FNAND_DMA_DEBUG_I("mem_addr_first:%02x %02x %02x %02x %02x ",
                      descriptor_p->mem_addr_first[0], descriptor_p->mem_addr_first[1], descriptor_p->mem_addr_first[2], descriptor_p->mem_addr_first[3], descriptor_p->mem_addr_first[4]);
    FNAND_DMA_DEBUG_I("addr:%02x %02x %02x %02x %02x ",
                      descriptor_p->addr[0], descriptor_p->addr[1], descriptor_p->addr[2], descriptor_p->addr[3], descriptor_p->addr[4]);

    FNAND_DMA_DEBUG_I(" csel : 0x%x  ", descriptor_p->cmd_ctrl.nfc_ctrl.csel);
    FNAND_DMA_DEBUG_I(" dbc : %d  ", descriptor_p->cmd_ctrl.nfc_ctrl.dbc);
    FNAND_DMA_DEBUG_I(" addr_cyc : %d  ", descriptor_p->cmd_ctrl.nfc_ctrl.addr_cyc);
    FNAND_DMA_DEBUG_I(" nc : %d  ", descriptor_p->cmd_ctrl.nfc_ctrl.nc);
    FNAND_DMA_DEBUG_I(" cmd_type : %d  ", descriptor_p->cmd_ctrl.nfc_ctrl.cmd_type);
    FNAND_DMA_DEBUG_I(" dc : %d  ", descriptor_p->cmd_ctrl.nfc_ctrl.dc);
    FNAND_DMA_DEBUG_I(" auto_rs : %d  ", descriptor_p->cmd_ctrl.nfc_ctrl.auto_rs);
    FNAND_DMA_DEBUG_I(" ecc_en : %d  ", descriptor_p->cmd_ctrl.nfc_ctrl.ecc_en);

}

static void FNandAddrCorrect(struct FNandDmaDescriptor *descriptor_p,
                             u8 *addr_p,
                             u32 addr_length)
{
    int i, j;
    if (addr_length == 0 || addr_p == NULL)
    {
        FNAND_DMA_DEBUG_I("The addr_p is null , Calibration is not required ");
        return;
    }

    if (addr_length >= FNAND_NFC_ADDR_MAX_LEN)
    {
        memcpy(descriptor_p->addr, addr_p, FNAND_NFC_ADDR_MAX_LEN);
        descriptor_p->cmd_ctrl.nfc_ctrl.addr_cyc = FNAND_NFC_ADDR_MAX_LEN;
        return;
    }

    descriptor_p->cmd_ctrl.nfc_ctrl.addr_cyc = 0;
    for (i = addr_length - 1, j = FNAND_NFC_ADDR_MAX_LEN - 1; i >= 0; i--, j--)
    {
        descriptor_p->addr[j] = addr_p[i]; /* data shift to high array */
        descriptor_p->addr[i] = 0;
        descriptor_p->cmd_ctrl.nfc_ctrl.addr_cyc++;
    }
}

FError FNandDmaPack(FNandCmdFormat *cmd_format,
                    struct FNandDmaDescriptor *descriptor_p,
                    FNandDmaPackData *pack_data_p
                   )
{
    u32 i;
    FASSERT(cmd_format != NULL);
    FASSERT(descriptor_p != NULL);
    descriptor_p->cmd_ctrl.ctrl = 0;

    /* cmd */
    if (cmd_format->end_cmd == TOGGLE_END_CMD_NONE) /* Only one cmd ,need to correct */
    {
        descriptor_p->cmd1 = cmd_format->start_cmd;
        descriptor_p->cmd0 = 0;
    }
    else
    {
        descriptor_p->cmd0 = cmd_format->start_cmd;
        descriptor_p->cmd1 = cmd_format->end_cmd;
        descriptor_p->cmd_ctrl.nfc_ctrl.dbc = 1;
    }

    /* addr */
    FNandAddrCorrect(descriptor_p, pack_data_p->addr_p, pack_data_p->addr_length);
    descriptor_p->cmd_ctrl.nfc_ctrl.cmd_type = cmd_format->cmd_type; /* cmd type */
    FNAND_DMA_DEBUG_I("cmd_type is %x", descriptor_p->cmd_ctrl.nfc_ctrl.cmd_type);
    if (pack_data_p->contiune_dma)
    {
        descriptor_p->cmd_ctrl.nfc_ctrl.nc = 1;
    }

    descriptor_p->cmd_ctrl.nfc_ctrl.csel = (0xf ^ (1 << pack_data_p->chip_addr));

    if (pack_data_p->phy_address && (pack_data_p->phy_bytes_length > 0))
    {
        descriptor_p->cmd_ctrl.nfc_ctrl.dc = 1;
        for (i = 0; i < FNAND_NFC_ADDR_MAX_LEN; i++)
        {
            descriptor_p->mem_addr_first[i] = pack_data_p->phy_address >> (8 * i) & 0xff;
        }
        descriptor_p->page_cnt = pack_data_p->phy_bytes_length;
    }

    if (cmd_format->auto_rs)
    {
        descriptor_p->cmd_ctrl.nfc_ctrl.auto_rs = 1;
    }

    if (cmd_format->ecc_en)
    {
        descriptor_p->cmd_ctrl.nfc_ctrl.ecc_en = 1;
    }

    /* invalid descriptor and buffer */
    FCacheDCacheInvalidateRange((intptr)descriptor_p, sizeof(struct FNandDmaDescriptor));
    FCacheDCacheInvalidateRange((intptr)pack_data_p->addr_p, pack_data_p->addr_length);

    FNandDmaDump(descriptor_p);

    return FT_SUCCESS;
}
