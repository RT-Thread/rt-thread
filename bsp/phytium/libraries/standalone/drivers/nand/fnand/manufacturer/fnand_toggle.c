/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
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
 * FilePath: fnand_toggle.c
 * Date: 2022-07-05 20:00:31
 * LastEditTime: 2022-07-05 20:00:31
 * Description:  This file is for toggle nand
 *
 * Modify History:
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */

#include "fnand.h"
#include "fnand_hw.h"
#include "stdio.h"
#include "string.h"
#include "fnand_dma.h"
#include "fnand_toggle.h"
#include "fnand_timing.h"
#include "fnand_ecc.h"
#include "fnand_common_cmd.h"
#include "fcache.h"
// #include "fsleep.h"
#include "fdebug.h"
#include "sdkconfig.h"

#define CONFIG_FNAND_TOGGLE_DEBUG_EN
#define FNAND_TOGGLE_DEBUG_TAG "FNAND_TOGGLE"
#ifdef CONFIG_FNAND_TOGGLE_DEBUG_EN

    #define FNAND_TOGGLE_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FNAND_TOGGLE_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_TOGGLE_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FNAND_TOGGLE_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_TOGGLE_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FNAND_TOGGLE_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_TOGGLE_DEBUG_D(format, ...) FT_DEBUG_PRINT_D(FNAND_TOGGLE_DEBUG_TAG, format, ##__VA_ARGS__)
#else
    #define FNAND_TOGGLE_DEBUG_I(format, ...)
    #define FNAND_TOGGLE_DEBUG_W(format, ...)
    #define FNAND_TOGGLE_DEBUG_E(format, ...)
    #define FNAND_TOGGLE_DEBUG_D(format, ...)
#endif

#define FNAND_ADDR_CYCLE_NUM0 0
#define FNAND_ADDR_CYCLE_NUM1 1
#define FNAND_ADDR_CYCLE_NUM2 2
#define FNAND_ADDR_CYCLE_NUM3 3
#define FNAND_ADDR_CYCLE_NUM4 4
#define FNAND_ADDR_CYCLE_NUM5 5

#define FNAND_TOGGLE_CRC_BASE   0x4F4E

#define FNAND_CTRL_ECC_EN 1
#define FNAND_CTRL_ECC_DIS 0

#define FNAND_CTRL_AUTO_AUTO_RS_EN 1
#define FNAND_CTRL_AUTO_AUTO_RS_DIS 0

/*
 * Special handling must be done for the WAITRDY timeout parameter as it usually
 * is either tPROG (after a prog), tR (before a read), tRST (during a reset) or
 * tBERS (during an erase) which all of them are u64 values that cannot be
 * divided by usual kernel macros and must be handled with the special
 * DIV_ROUND_UP_ULL() macro.
 *
 * Cast to type of dividend is needed here to guarantee that the result won't
 * be an unsigned long long when the dividend is an unsigned long (or smaller),
 * which is what the compiler does when it sees ternary operator with 2
 * different return types (picks the largest type to make sure there's no
 * loss).
 */
#define __DIVIDE(dividend, divisor) ({                      \
        (__typeof__(dividend))(sizeof(dividend) <= sizeof(unsigned long) ?  \
                               DIV_ROUND_UP(dividend, divisor) :        \
                               DIV_ROUND_UP_ULL(dividend, divisor));        \
    })
#define PSEC_TO_NSEC(x) __DIVIDE(x, 1000)
#define PSEC_TO_MSEC(x) __DIVIDE(x, 1000000000)

extern FError FNandSendCmd(FNand *instance_p, struct FNandDmaDescriptor *descriptor_p, FNandOperationType isr_type);
extern FError FNandTimingInterfaceUpdate(FNand *instance_p, u32 chip_addr);

FError FNandDmaPack(FNandCmdFormat *cmd_format,
                    struct FNandDmaDescriptor *descriptor_p,
                    FNandDmaPackData *pack_data_p
                   );





enum CommandsEnumNew
{
    CMD_READ_ID = 0,
    CMD_READ_DEVICE_TABLE,
    CMD_INDEX_LENGTH_NEW,
};


static FNandCmdFormat cmd_format[CMD_INDEX_LENGTH_NEW] =
{
    {TOGGLE_CMD_READ_ID, TOGGLE_END_CMD_NONE, FNAND_ADDR_CYCLE_NUM1, FNAND_CMDCTRL_TYPE_READ_ID, FNAND_CTRL_ECC_DIS, FNAND_CTRL_AUTO_AUTO_RS_DIS},
    {TOGGLE_CMD_READ_PARAM_PAGE, TOGGLE_END_CMD_NONE, FNAND_ADDR_CYCLE_NUM1, FNAND_CMDCTRL_READ_PARAM, FNAND_CTRL_ECC_DIS, FNAND_CTRL_AUTO_AUTO_RS_EN},
};

static u16 FNandToggleCrc16(u16 crc, u8 const *p, size_t len)
{
    int i;
    while (len--)
    {
        crc ^= *p++ << 8;
        for (i = 0; i < 8; i++)
        {
            crc = (crc << 1) ^ ((crc & 0x8000) ? 0x8005 : 0);
        }
    }

    return crc;
}



/* Sanitize ONFI strings so we can safely print them */
static void FNandSanitizeString(u8 *s, fsize_t len)
{
    fsize_t i;

    /* Null terminate */
    s[len - 1] = 0;

    /* Remove non printable chars */
    for (i = 0; i < len - 1; i++)
    {
        if (s[i] < ' ' || s[i] > 127)
        {
            s[i] = '?';
        }
    }

}


static FError FNandToggleReadParamPage(FNand *instance_p,  u8 *id_buffer, u32 buffer_length, u32 chip_addr)
{
    FError ret;
    u8 address = 0x40;
    u32 memcpy_length;
    FNandDmaPackData pack_data =
    {
        .addr_p = &address,
        .addr_length = 1,
        .phy_address = (uintptr)instance_p->dma_data_buffer.data_buffer,
        .phy_bytes_length = (3 * sizeof(struct ToggleNandGeometry) > FNAND_DMA_MAX_LENGTH) ? FNAND_DMA_MAX_LENGTH : (3 * sizeof(struct ToggleNandGeometry)),
        .chip_addr = chip_addr,
        .contiune_dma = 0,
    };

    FNandDmaPack(&cmd_format[CMD_READ_DEVICE_TABLE], (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], &pack_data);
    ret = FNandSendCmd(instance_p, (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], FNAND_READ_PAGE_TYPE);


    if (ret != FT_SUCCESS)
    {
        return FNAND_ERR_OPERATION;
    }

    if (buffer_length && id_buffer)
    {
        memcpy_length = (buffer_length > pack_data.phy_bytes_length) ? pack_data.phy_bytes_length : buffer_length;
        FCacheDCacheFlushRange((intptr)instance_p->dma_data_buffer.data_buffer, memcpy_length);
        memcpy(id_buffer, instance_p->dma_data_buffer.data_buffer, memcpy_length);
    }

    return FT_SUCCESS;
}

static FError FNandToggleDetectJedec(FNand *instance_p, struct ToggleNandGeometry *toggle_geometry_p, FNandNandGeometry *geometry_p)
{
    /* 检查crc */
    if (FNandToggleCrc16(FNAND_TOGGLE_CRC_BASE, (u8 *)toggle_geometry_p, 510) != toggle_geometry_p->crc)
    {
        FNAND_TOGGLE_DEBUG_E("Toggle error mode");
    }

    FNAND_TOGGLE_DEBUG_I("revision is %x", toggle_geometry_p->revision);

    FNandSanitizeString(toggle_geometry_p->manufacturer, sizeof(toggle_geometry_p->manufacturer));
    FNandSanitizeString(toggle_geometry_p->model, sizeof(toggle_geometry_p->model));
    FNAND_TOGGLE_DEBUG_I("manufacturer %s", toggle_geometry_p->manufacturer);
    FNAND_TOGGLE_DEBUG_I("model %s", toggle_geometry_p->model);

    geometry_p->bytes_per_page = toggle_geometry_p->byte_per_page;
    geometry_p->spare_bytes_per_page =  toggle_geometry_p->spare_bytes_per_page;
    geometry_p->pages_per_block = toggle_geometry_p->pages_per_block;
    geometry_p->blocks_per_lun = toggle_geometry_p->blocks_per_lun ;
    geometry_p->num_lun = toggle_geometry_p->lun_count;
    geometry_p->num_pages = (geometry_p->num_lun *
                             geometry_p->blocks_per_lun *
                             geometry_p->pages_per_block);
    geometry_p->num_blocks = (geometry_p->num_lun * geometry_p->blocks_per_lun);
    geometry_p->block_size = (geometry_p->pages_per_block * geometry_p->bytes_per_page);
    geometry_p->device_size = (geometry_p->num_blocks * geometry_p->block_size * geometry_p->bytes_per_page);
    geometry_p->rowaddr_cycles = toggle_geometry_p->addr_cycles & 0xf;
    geometry_p->coladdr_cycles = (toggle_geometry_p->addr_cycles >> 4) & 0xf ;
    geometry_p->hw_ecc_length =  FNandGetEccTotalLength(geometry_p->bytes_per_page, instance_p->config.ecc_strength);
    geometry_p->ecc_offset = geometry_p->spare_bytes_per_page - geometry_p->hw_ecc_length;
    geometry_p->hw_ecc_steps = geometry_p->bytes_per_page  / instance_p->config.ecc_step_size ;
    geometry_p->ecc_step_size = instance_p->config.ecc_step_size;
    FNAND_TOGGLE_DEBUG_D("bytes_per_page %d ", geometry_p->bytes_per_page);               /* Bytes per page */
    FNAND_TOGGLE_DEBUG_D("spare_bytes_per_page %d ", geometry_p->spare_bytes_per_page) ;  /* Size of spare area in bytes */
    FNAND_TOGGLE_DEBUG_D("pages_per_block %d ", geometry_p->pages_per_block) ;        /* Pages per block */
    FNAND_TOGGLE_DEBUG_D("blocks_per_lun %d ", geometry_p->blocks_per_lun) ;         /* Bocks per LUN */
    FNAND_TOGGLE_DEBUG_D("num_lun %d ", geometry_p->num_lun) ;                /* Total number of LUN */
    FNAND_TOGGLE_DEBUG_D("num_pages %d ", geometry_p->num_pages) ;              /* Total number of pages in device */
    FNAND_TOGGLE_DEBUG_D("num_blocks %d ", geometry_p->num_blocks) ;             /* Total number of blocks in device */
    FNAND_TOGGLE_DEBUG_D("block_size %d ", geometry_p->block_size) ;             /* Size of a block in bytes */
    FNAND_TOGGLE_DEBUG_D("device_size %d ", geometry_p->device_size) ;            /* Total device size in bytes */
    FNAND_TOGGLE_DEBUG_D("rowaddr_cycles %d ", geometry_p->rowaddr_cycles) ;          /* Row address cycles */
    FNAND_TOGGLE_DEBUG_D("coladdr_cycles %d ", geometry_p->coladdr_cycles) ;          /* Column address cycles */
    FNAND_TOGGLE_DEBUG_D("hw_ecc_length %d ", geometry_p->hw_ecc_length) ;          /* 产生硬件ecc校验参数的个数 */
    FNAND_TOGGLE_DEBUG_D("ecc_offset %d ", geometry_p->ecc_offset) ;          /* obb存放硬件ecc校验参数页位置的偏移 */
    FNAND_TOGGLE_DEBUG_D("hw_ecc_steps %d ", geometry_p->hw_ecc_steps) ;          /* number of ECC steps per page */
    FNAND_TOGGLE_DEBUG_D("ecc_step_size %d ", geometry_p->ecc_step_size) ;       /* 进行读写操作时，单次ecc 的步骤的跨度 */



    return FT_SUCCESS;
}


/**
 * @name: FNandToggleInit
 * @msg:  Toggle mode interface initialization
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @param {u32} chip_addr is chip address
 * @return {FError} FT_SUCCESS 初始化成功 ，FNAND_NOT_FET_TOGGLE_MODE 初始化toggle 模式错误。
 */
FError FNandToggleInit(FNand *instance_p, u32 chip_addr)
{
    FError ret;
    char id[6];
    FASSERT(instance_p != NULL);
    struct ToggleNandGeometry *toggle_geometry_p;
    /* step 1 .reset nand chip */
    ret = FNandFlashReset(instance_p, chip_addr) ;
    if (ret != FT_SUCCESS)
    {
        FNAND_TOGGLE_DEBUG_E("FNandFlashReset is error");
        return ret;
    }

    /* step 2. readid operation 40h */
    ret = FNandFlashReadId(instance_p, 0x40, id, sizeof(id), chip_addr);
    if (ret != FT_SUCCESS || strncmp(id, "JEDEC", sizeof(id) - 1))
    {
        FNAND_TOGGLE_DEBUG_E("The id value read out from 40H is %s ", id);
        return FNAND_NOT_FET_TOGGLE_MODE;
    }

    if (id[5] == 1)
    {
        instance_p->inter_mode[chip_addr] = FNAND_ASYN_SDR;
    }
    else if (id[5] == 2)
    {
        instance_p->inter_mode[chip_addr] = FNAND_TOG_ASYN_DDR;
    }
    else if (id[5] == 4)
    {
        instance_p->inter_mode[chip_addr] = FNAND_ASYN_SDR;
    }

    FNandTimingInterfaceUpdate(instance_p, chip_addr);

    /* step 3. read device id table */

    ret = FNandToggleReadParamPage(instance_p, NULL, 0, chip_addr);
    if (ret != FT_SUCCESS)
    {
        FNAND_TOGGLE_DEBUG_E("An error occured when reading device id table");
        return FNAND_NOT_FET_TOGGLE_MODE;
    }

    /* step 4. device id table parse */
    toggle_geometry_p = (struct ToggleNandGeometry *)instance_p->dma_data_buffer.data_buffer;

    return FNandToggleDetectJedec(instance_p, toggle_geometry_p, &instance_p->nand_geometry[chip_addr]);
}
