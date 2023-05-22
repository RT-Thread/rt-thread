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
 * FilePath: fsdmmc_dma.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:49:31
 * Description:  This file is dma descriptor management API.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 */

/***************************** Include Files *********************************/
#include "fassert.h"
#include "fio.h"
#include "fdebug.h"

#include "fsdmmc_hw.h"
#include "fsdmmc.h"
#include "fsdmmc_dma.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FSDMMC_DEBUG_TAG "FSDMMC-DMA"
#define FSDMMC_ERROR(format, ...)   FT_DEBUG_PRINT_E(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDMMC_WARN(format, ...)    FT_DEBUG_PRINT_W(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDMMC_INFO(format, ...)    FT_DEBUG_PRINT_I(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FSDMMC_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FSDMMC_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
 * @name: FSdmmcSetReadDMA
 * @msg: 设置读数据DMA配置
 * @return {*}
 * @param {uintptr} base_addr FSDMMC 控制器基地址
 * @param {uintptr} card_addr 读卡地址
 * @param {u32} blk_cnt 读卡的block数
 * @param {void} *buf_p 读卡的目的地址
 */
void FSdmmcSetReadDMA(uintptr base_addr, uintptr card_addr, u32 blk_cnt, void *buf_p)
{
    FASSERT(buf_p);

    u32 dsth = UPPER_32_BITS((uintptr)buf_p); /* DMA传输目的地址--> sd read buf */
    u32 dstl = LOWER_32_BITS((uintptr)buf_p);
    u32 srch = UPPER_32_BITS((uintptr)card_addr); /* DMA传输源地址 --> sd card */
    u32 srcl = LOWER_32_BITS((uintptr)card_addr);

    FSDMMC_INFO("sd card: 0x%x:0x%x ==> mem space: 0x%x:0x%x",
                srch, srcl, dsth, dstl);

    FSDMMC_INFO("Read %d blks from 0x%x", blk_cnt, card_addr);

    /* DMA 复位 */
    FSDMMC_SET_BIT(base_addr, FSDMMC_SOFTWARE_RESET_REG_OFFSET, FSDMMC_SOFTWARE_RESET_BDRST);
    FSDMMC_CLR_BIT(base_addr, FSDMMC_SOFTWARE_RESET_REG_OFFSET, FSDMMC_SOFTWARE_RESET_BDRST);

    /* 设置传输块数目 */
    FSDMMC_WRITE_REG(base_addr, FSDMMC_BLK_CNT_REG_OFFSET, blk_cnt);

    /* 清除状态寄存器 */
    FSdmmcClearErrorInterruptStatus(base_addr);
    FSdmmcClearBDInterruptStatus(base_addr);
    FSdmmcClearNormalInterruptStatus(base_addr);

    FSDMMC_INFO("Base addr: 0x%x buf_p: %p", base_addr, buf_p);

    FSDMMC_DATA_BARRIER();

    /* DMA 读卡地址配置：4 个 cycle
    系统低 4B-系统高 4B-SD 低 4B- SD 高 4B */
    FSDMMC_WRITE_REG(base_addr, FSDMMC_DAT_IN_M_RX_BD_REG_OFFSET, dstl);
    FSDMMC_WRITE_REG(base_addr, FSDMMC_DAT_IN_M_RX_BD_REG_OFFSET, dsth);
    FSDMMC_WRITE_REG(base_addr, FSDMMC_DAT_IN_M_RX_BD_REG_OFFSET, srcl);
    FSDMMC_WRITE_REG(base_addr, FSDMMC_DAT_IN_M_RX_BD_REG_OFFSET, srch);


    FSDMMC_INFO("DMA READ START!");
    return;
}

/**
 * @name: FSdmmcSetWriteDMA
 * @msg: 设置写数据DMA配置
 * @return {*}
 * @param {uintptr} base_addr FSDMMC 控制器基地址
 * @param {uintptr} card_addr 写卡地址
 * @param {u32} blk_cnt 写卡的block数
 * @param {void} *buf_p 写卡的源地址
 */
void FSdmmcSetWriteDMA(uintptr base_addr, uintptr card_addr, u32 blk_cnt, const void *buf_p)
{
    FASSERT(buf_p);
    u32 srch = UPPER_32_BITS((uintptr)buf_p); /* DMA传输源地址--> sd read buf */
    u32 srcl = LOWER_32_BITS((uintptr)buf_p);
    u32 dsth = UPPER_32_BITS((uintptr)card_addr); /* DMA传输目的地址 --> sd card */
    u32 dstl = LOWER_32_BITS((uintptr)card_addr);

    FSDMMC_INFO("mem space: 0x%x:0x%x ==> sd card: 0x%x:0x%x",
                srch, srcl, dsth, dstl);

    FSDMMC_INFO("Write %d blks from 0x%x", blk_cnt, card_addr);

    /* DMA 复位 */
    FSDMMC_SET_BIT(base_addr, FSDMMC_SOFTWARE_RESET_REG_OFFSET, FSDMMC_SOFTWARE_RESET_BDRST);
    FSDMMC_CLR_BIT(base_addr, FSDMMC_SOFTWARE_RESET_REG_OFFSET, FSDMMC_SOFTWARE_RESET_BDRST);

    /* 设置传输块数目 */
    FSDMMC_WRITE_REG(base_addr, FSDMMC_BLK_CNT_REG_OFFSET, blk_cnt);

    /* 清除状态寄存器 */
    FSdmmcClearErrorInterruptStatus(base_addr);
    FSdmmcClearBDInterruptStatus(base_addr);
    FSdmmcClearNormalInterruptStatus(base_addr);

    FSDMMC_DATA_BARRIER();

    /* DMA 写卡地址配置：4 个 cycle
    系统低 4B-系统高 4B-SD 低 4B- SD 高 4B */
    FSDMMC_WRITE_REG(base_addr, FSDMMC_DAT_IN_M_TX_BD_REG_OFFSET, srcl);
    FSDMMC_WRITE_REG(base_addr, FSDMMC_DAT_IN_M_TX_BD_REG_OFFSET, srch);
    FSDMMC_WRITE_REG(base_addr, FSDMMC_DAT_IN_M_TX_BD_REG_OFFSET, dstl);
    FSDMMC_WRITE_REG(base_addr, FSDMMC_DAT_IN_M_TX_BD_REG_OFFSET, dsth);

    FSDMMC_INFO("DMA WRITE START!");
    return;
}