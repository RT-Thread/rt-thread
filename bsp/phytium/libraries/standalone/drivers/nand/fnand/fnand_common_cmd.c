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
 * FilePath: fnand_common_cmd.c
 * Date: 2022-06-24 03:51:06
 * LastEditTime: 2022-06-24 03:51:07
 * Description:  This file is for nand generic command documentation
 *
 * Modify History:
 *  Ver   Who  Date   Changes
 * ----- ------  -------- --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */

#include "fnand_common_cmd.h"
#include "fnand_hw.h"
#include "stdio.h"
#include "string.h"
#include "fnand_dma.h"
#include "fnand_onfi.h"
#include "fnand_timing.h"
#include "fnand_ecc.h"
#include "fcache.h"
#include "fsleep.h"
#include "fdebug.h"
#include "sdkconfig.h"


#define FNAND_COMMON_DEBUG_TAG "FNAND_COMMON"


#ifdef CONFIG_FNAND_COMMON_DEBUG_EN
    #define FNAND_COMMON_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FNAND_COMMON_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_COMMON_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FNAND_COMMON_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_COMMON_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FNAND_COMMON_DEBUG_TAG, format, ##__VA_ARGS__)
    #define FNAND_COMMON_DEBUG_D(format, ...) FT_DEBUG_PRINT_D(FNAND_COMMON_DEBUG_TAG, format, ##__VA_ARGS__)
#else
    #define FNAND_COMMON_DEBUG_I(format, ...)
    #define FNAND_COMMON_DEBUG_W(format, ...)
    #define FNAND_COMMON_DEBUG_E(format, ...)
    #define FNAND_COMMON_DEBUG_D(format, ...)
#endif

#define FNAND_ADDR_CYCLE_NUM0 0
#define FNAND_ADDR_CYCLE_NUM1 1
#define FNAND_ADDR_CYCLE_NUM2 2
#define FNAND_ADDR_CYCLE_NUM3 3
#define FNAND_ADDR_CYCLE_NUM4 4
#define FNAND_ADDR_CYCLE_NUM5 5

#define FNAND_COMMON_CRC_BASE   0x4F4E

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

extern FError FNandDmaPack(FNandCmdFormat *cmd_format,
                           struct FNandDmaDescriptor *descriptor_p,
                           FNandDmaPackData *pack_data_p
                          );



enum CommandsEnumNew
{
    CMD_READ_OPTION_NEW = 0,
    CMD_RANDOM_DATA_OUT,
    CMD_PAGE_PROGRAM,
    CMD_PAGE_PROGRAM_WITH_OTHER,
    CMD_COPY_BACK_PROGRAM,
    CMD_BLOCK_ERASE,
    CMD_RESET,
    CMD_READ_ID,
    CMD_READ_DEVICE_TABLE,
    CMD_READ_PAGE,
    CMD_READ_STATUS,
    CMD_INDEX_LENGTH_NEW,
};


static FNandCmdFormat cmd_format[CMD_INDEX_LENGTH_NEW] =
{
    {NAND_CMD_READ1, NAND_CMD_READ2, FNAND_ADDR_CYCLE_NUM5, FNAND_CMDCTRL_TYPE_READ, FNAND_CTRL_ECC_DIS, FNAND_CTRL_AUTO_AUTO_RS_EN},
    {NAND_CMD_CHANGE_READ_COLUMN1, NAND_CMD_CHANGE_READ_COLUMN2, FNAND_ADDR_CYCLE_NUM2, FNAND_CMDCTRL_TYPE_READ_COL, FNAND_CTRL_ECC_EN, FNAND_CTRL_AUTO_AUTO_RS_DIS},
    {NAND_CMD_PAGE_PROG1, NAND_CMD_PAGE_PROG2, FNAND_ADDR_CYCLE_NUM5, FNAND_CMDCTRL_TYPE_PAGE_PRO, FNAND_CTRL_ECC_DIS, FNAND_CTRL_AUTO_AUTO_RS_EN},
    {NAND_CMD_PAGE_PROG1, NAND_END_CMD_NONE, FNAND_ADDR_CYCLE_NUM5, FNAND_CMDCTRL_CH_ROW_ADDR, FNAND_CTRL_ECC_DIS, FNAND_CTRL_AUTO_AUTO_RS_DIS},
    {NAND_CMD_CHANGE_WRITE_COLUMN, NAND_CMD_PAGE_PROG2, FNAND_ADDR_CYCLE_NUM2, FNAND_CMDCTRL_TYPE_PAGE_PRO, FNAND_CTRL_ECC_EN, FNAND_CTRL_AUTO_AUTO_RS_EN},
    {NAND_CMD_BLOCK_ERASE1, NAND_CMD_BLOCK_ERASE2, FNAND_ADDR_CYCLE_NUM3, FNAND_CMDCTRL_TYPE_ERASE, FNAND_CTRL_ECC_DIS, FNAND_CTRL_AUTO_AUTO_RS_EN},
    {NAND_CMD_RESET, NAND_END_CMD_NONE, FNAND_ADDR_CYCLE_NUM5, FNAND_CMDCTRL_TYPE_RESET, FNAND_CTRL_ECC_DIS, FNAND_CTRL_AUTO_AUTO_RS_EN},
    {NAND_CMD_READ_ID, NAND_END_CMD_NONE, FNAND_ADDR_CYCLE_NUM1, FNAND_CMDCTRL_TYPE_READ_ID, FNAND_CTRL_ECC_DIS, FNAND_CTRL_AUTO_AUTO_RS_DIS},
    {NAND_CMD_READ_PARAM_PAGE, NAND_END_CMD_NONE, FNAND_ADDR_CYCLE_NUM1, FNAND_CMDCTRL_READ_PARAM, FNAND_CTRL_ECC_DIS, FNAND_CTRL_AUTO_AUTO_RS_EN},
    {NAND_CMD_READ1, NAND_CMD_READ2, FNAND_ADDR_CYCLE_NUM5, FNAND_CMDCTRL_TYPE_READ_ID, FNAND_CTRL_ECC_DIS, FNAND_CTRL_AUTO_AUTO_RS_EN},
    {NAND_CMD_READ_STATUS, NAND_END_CMD_NONE, FNAND_ADDR_CYCLE_NUM5, FNAND_CMDCTRL_TYPE_READ_COL, FNAND_CTRL_ECC_DIS, FNAND_CTRL_AUTO_AUTO_RS_DIS},
};


FError FNandFlashReadId(FNand *instance_p, u8 address, u8 *id_buffer, u32 buffer_length, u32 chip_addr)
{
    FError ret;
    u32 memcpy_length;
    FNandDmaPackData pack_data =
    {
        .addr_p = &address,
        .addr_length = 1,
        .phy_address = (uintptr)instance_p->dma_data_buffer.data_buffer,
        .phy_bytes_length = (buffer_length > FNAND_DMA_MAX_LENGTH) ? FNAND_DMA_MAX_LENGTH : buffer_length,
        .chip_addr = chip_addr,
        .contiune_dma = 0,
    };

    memset((struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], 0, sizeof(struct FNandDmaDescriptor));
    FNandDmaPack(&cmd_format[CMD_READ_ID], (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], &pack_data);
    ret = FNandSendCmd(instance_p, (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], FNAND_CMD_TYPE);
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


static FError FNandFlashReadStatus(FNand *instance_p, u32 chip_addr)
{
    FError ret;
    FASSERT(instance_p != NULL);
    FNandDmaPackData pack_data =
    {
        .addr_p = NULL,
        .addr_length = 0,
        .phy_address = (uintptr)instance_p->dma_data_buffer.data_buffer,
        .phy_bytes_length = 4,
        .chip_addr = chip_addr,
        .contiune_dma  = 0,
    };

    memset((struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], 0, sizeof(struct FNandDmaDescriptor));
    FNandDmaPack(&cmd_format[CMD_READ_STATUS], (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], &pack_data); /* FNAND_CMDCTRL_TYPE_RESET */
    ret = FNandSendCmd(instance_p, (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], FNAND_READ_PAGE_TYPE);
    if (ret != FT_SUCCESS)
    {
        return ret;
    }

    FNAND_COMMON_DEBUG_I("Read status is 0x%x", instance_p->dma_data_buffer.data_buffer[0]);

    return (instance_p->dma_data_buffer.data_buffer[0] == 0xe0) ? FT_SUCCESS : FNAND_IS_BUSY;
}

FError FNandFlashReset(FNand *instance_p, u32 chip_addr)
{
    FASSERT(instance_p != NULL);
    FNandDmaPackData pack_data =
    {
        .addr_p = NULL,
        .addr_length = 0,
        .phy_address = (uintptr)NULL,
        .phy_bytes_length = 0,
        .chip_addr = chip_addr,
        .contiune_dma  = 0,
    };

    memset((struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], 0, sizeof(struct FNandDmaDescriptor));
    FNandDmaPack(&cmd_format[CMD_RESET], (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], &pack_data); /* FNAND_CMDCTRL_TYPE_RESET */
    return FNandSendCmd(instance_p, (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], FNAND_CMD_TYPE);
}


FError FNandFlashEraseBlock(FNand *instance_p, u32 page_addr, u32 chip_addr)
{
    u8 addr_buf[3] = {0};
    FError ret;
    u32 nand_state;

    while (FNandFlashReadStatus(instance_p, chip_addr) == FNAND_IS_BUSY)
        ; /* wait i/o idle */
    /* read operation */


    addr_buf[0] = page_addr;
    addr_buf[1] = page_addr >> 8;
    addr_buf[2] = page_addr >> 16;

    FNandDmaPackData pack_data =
    {
        .addr_p = addr_buf,
        .addr_length = 3,
        .phy_address = (uintptr)NULL,
        .phy_bytes_length = 0,
        .chip_addr = chip_addr,
        .contiune_dma  = 0,
    };

    FNandDmaPack(&cmd_format[CMD_BLOCK_ERASE], (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], &pack_data);
    ret = FNandSendCmd(instance_p, (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], FNAND_CMD_TYPE);

    if (ret != FT_SUCCESS)
    {
        return FNAND_ERR_OPERATION;
    }

    nand_state = FNAND_READREG(instance_p->config.base_address, FNAND_STATE_OFFSET);
    while (nand_state & FNAND_STATE_BUSY_OFFSET) /* wait busy state is over */
    {
        nand_state = FNAND_READREG(instance_p->config.base_address, FNAND_STATE_OFFSET);
    }

    return FT_SUCCESS;
}

static FError FNandPageRead(FNand *instance_p, u32 page_addr, u8 *buf, u32 page_copy_offset, u32 length, u32 chip_addr)
{
    u8 addr_buf[5] = {0};
    u32 memcpy_length;
    FError ret;
    addr_buf[4] = (page_addr >> 16);
    addr_buf[3] = (page_addr >> 8);
    addr_buf[2] = (page_addr);

    FNandDmaPackData pack_data =
    {
        .addr_p = addr_buf,
        .addr_length = 5,
        .phy_address = (uintptr)instance_p->dma_data_buffer.data_buffer,
        .phy_bytes_length = instance_p->nand_geometry[chip_addr].bytes_per_page,
        .chip_addr = chip_addr,
        .contiune_dma  = 0,
    };

    FNandDmaPack(&cmd_format[CMD_READ_OPTION_NEW], (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], &pack_data);
    ret = FNandSendCmd(instance_p, (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], FNAND_READ_PAGE_TYPE);

    if (ret != FT_SUCCESS)
    {
        return FNAND_ERR_OPERATION;
    }

    if (length && buf)
    {
        memcpy_length = (length > (pack_data.phy_bytes_length - page_copy_offset)) ? (pack_data.phy_bytes_length - page_copy_offset) : length;
        FCacheDCacheFlushRange((intptr)(instance_p->dma_data_buffer.data_buffer + page_copy_offset), memcpy_length);
        memcpy(buf, instance_p->dma_data_buffer.data_buffer + page_copy_offset, memcpy_length);
    }

    return FT_SUCCESS;
}

static FError FNandPageWrite(FNand *instance_p, u32 page_addr, u8 *buf, u32 page_copy_offset, u32 length, u32 chip_addr)
{
    u8 addr_buf[5] = {0};
    FError ret;
    u32 bytes_per_page = 0;
    addr_buf[4] = (page_addr >> 16);
    addr_buf[3] = (page_addr >> 8);
    addr_buf[2] = (page_addr);
    bytes_per_page = instance_p->nand_geometry[chip_addr].bytes_per_page;
    FNandDmaPackData pack_data =
    {
        .addr_p = addr_buf,
        .addr_length = 5,
        .phy_address = (uintptr)instance_p->dma_data_buffer.data_buffer,
        .phy_bytes_length = bytes_per_page,
        .chip_addr = chip_addr,
        .contiune_dma = 0,
    };

    memcpy(instance_p->dma_data_buffer.data_buffer + page_copy_offset, buf, ((bytes_per_page - page_copy_offset) > length) ? length : (bytes_per_page - page_copy_offset));

    FNandDmaPack(&cmd_format[CMD_PAGE_PROGRAM], (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], &pack_data);
    ret = FNandSendCmd(instance_p, (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], FNAND_WRITE_PAGE_TYPE);

    if (ret != FT_SUCCESS)
    {
        return FNAND_ERR_OPERATION;
    }
    while (FNandFlashReadStatus(instance_p, chip_addr) == FNAND_IS_BUSY);
    return FT_SUCCESS;
}

static FError FNandPageWriteHwEcc(FNand *instance_p, u32 page_addr, u8 *buf, u32 page_copy_offset, u32 length, u32 chip_addr)
{
    FError ret;
    u32 nand_state = 0;
    u8 addr_buf[5] = {0};
    u32 ecc_offset = 0;
    u32 bytes_per_page = 0;
    u32 spare_bytes_per_page = 0;
    /* read operation */
    addr_buf[2] = page_addr;
    addr_buf[3] = page_addr >> 8;
    addr_buf[4] = page_addr >> 16;

    ecc_offset = instance_p->nand_geometry[chip_addr].ecc_offset;
    bytes_per_page = instance_p->nand_geometry[chip_addr].bytes_per_page;
    spare_bytes_per_page = instance_p->nand_geometry[chip_addr].spare_bytes_per_page;

    FNandDmaPackData pack_data =
    {
        .addr_p = addr_buf,
        .addr_length = 5,
        .phy_address = (uintptr)instance_p->dma_data_buffer.data_buffer,
        .phy_bytes_length = bytes_per_page,
        .chip_addr = chip_addr,
        .contiune_dma = 1,
    };

    memset(instance_p->dma_data_buffer.data_buffer, 0xff, FNAND_DMA_MAX_LENGTH);
    memcpy(instance_p->dma_data_buffer.data_buffer + page_copy_offset, buf, ((bytes_per_page - page_copy_offset) < length) ? (bytes_per_page - page_copy_offset) : length);

    FNandDmaPack(&cmd_format[CMD_PAGE_PROGRAM_WITH_OTHER], (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], &pack_data) ;
    /*  Random Data Input */

    /* 写入存储硬件ecc 偏移位置参数 */
    memset(addr_buf, 0, sizeof(addr_buf));
    addr_buf[0] = bytes_per_page + ecc_offset;
    addr_buf[1] = (bytes_per_page + ecc_offset) >> 8;
    memset((instance_p->dma_data_buffer.data_buffer + bytes_per_page), 0xff, spare_bytes_per_page);
    FNandDmaPackData pack_data2 =
    {
        .addr_p = addr_buf,
        .addr_length = 2,
        .phy_address = (uintptr)instance_p->dma_data_buffer.data_buffer + bytes_per_page + ecc_offset,
        .phy_bytes_length = instance_p->nand_geometry[chip_addr].hw_ecc_length,
        .chip_addr = chip_addr,
        .contiune_dma = 0,
    };

    FNandDmaPack(&cmd_format[CMD_COPY_BACK_PROGRAM], (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[FNAND_DESCRIPTORS_SIZE], &pack_data2) ;
    ret = FNandSendCmd(instance_p, (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], FNAND_WRITE_PAGE_TYPE);
    if (ret != FT_SUCCESS)
    {
        return FNAND_ERR_OPERATION;
    }

    nand_state = FNAND_READREG(instance_p->config.base_address, FNAND_STATE_OFFSET);
    while (nand_state & FNAND_STATE_BUSY_OFFSET) /* wait busy state is over */
    {
        nand_state = FNAND_READREG(instance_p->config.base_address, FNAND_STATE_OFFSET);
    }
    while (FNandFlashReadStatus(instance_p, chip_addr) == FNAND_IS_BUSY)
        ; /* wait i/o idle */

    return FT_SUCCESS;
}

static FError FNandPageReadOOb(FNand *instance_p, u32 page_addr, u8 *buf, u32 page_copy_offset, u32 length, u32 chip_addr)
{
    FError ret;
    u8 addr_buf[5] = {0};
    u32 bytes_per_page = 0;
    u32 spare_bytes_per_page = 0;
    u32 memcpy_length = 0;
    bytes_per_page = instance_p->nand_geometry[chip_addr].bytes_per_page ;
    spare_bytes_per_page = instance_p->nand_geometry[chip_addr].spare_bytes_per_page ;

    FNandDmaPackData pack_data =
    {
        .addr_p = addr_buf,
        .addr_length = 5,
        .phy_address = (uintptr)instance_p->dma_data_buffer.data_buffer,
        .phy_bytes_length = spare_bytes_per_page, /* 读取所有的oob 数据 */
        .chip_addr = chip_addr,
        .contiune_dma = 0,
    };

    addr_buf[4] = (page_addr >> 16);
    addr_buf[3] = (page_addr >> 8);
    addr_buf[2] = (page_addr);
    addr_buf[1] = ((bytes_per_page >> 8) & 0xff); /* 从oob 位置读取 */
    addr_buf[0] = (bytes_per_page & 0xff);

    FNandDmaPack(&cmd_format[CMD_READ_OPTION_NEW], (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], &pack_data);
    ret = FNandSendCmd(instance_p, (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], FNAND_READ_PAGE_TYPE);

    if (ret != FT_SUCCESS)
    {
        return FNAND_ERR_OPERATION;
    }

    if (length && buf)
    {
        memcpy_length = (length > (spare_bytes_per_page - page_copy_offset)) ? (spare_bytes_per_page - page_copy_offset) : length;
        FCacheDCacheFlushRange((intptr)(instance_p->dma_data_buffer.data_buffer + page_copy_offset), memcpy_length);
        memcpy(buf, instance_p->dma_data_buffer.data_buffer + page_copy_offset, memcpy_length);
    }

    return FT_SUCCESS;
}

static FError FNandPageWriteOOb(FNand *instance_p, u32 page_addr, u8 *buf, u32 spare_page_offset, u32 length, u32 chip_addr)
{
    FError ret;
    u8 addr_buf[5] = {0};
    u32 bytes_per_page = 0;
    u32 spare_bytes_per_page = 0;

    bytes_per_page = instance_p->nand_geometry[chip_addr].bytes_per_page;
    spare_bytes_per_page = instance_p->nand_geometry[chip_addr].spare_bytes_per_page ;
    memset(instance_p->dma_data_buffer.data_buffer, 0xff, spare_bytes_per_page);

    FNandDmaPackData pack_data =
    {
        .addr_p = addr_buf,
        .addr_length = 5,
        .phy_address = (uintptr)instance_p->dma_data_buffer.data_buffer,
        .phy_bytes_length = (spare_bytes_per_page > length) ? length : spare_bytes_per_page,
        .chip_addr = chip_addr,
        .contiune_dma = 0,
    };

    addr_buf[4] = (page_addr >> 16);
    addr_buf[3] = (page_addr >> 8);
    addr_buf[2] = (page_addr);
    addr_buf[1] = ((bytes_per_page >> 8) & 0xff);
    addr_buf[0] = (bytes_per_page & 0xff);

    memcpy(instance_p->dma_data_buffer.data_buffer + spare_page_offset, buf, ((spare_bytes_per_page - spare_page_offset) > length) ? length : (spare_bytes_per_page - spare_page_offset));

    FNandDmaPack(&cmd_format[CMD_PAGE_PROGRAM], (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], &pack_data);

    ret = FNandSendCmd(instance_p, (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], FNAND_WRITE_PAGE_TYPE);

    if (ret != FT_SUCCESS)
    {
        return FNAND_ERR_OPERATION;
    }
    while (FNandFlashReadStatus(instance_p, chip_addr) == FNAND_IS_BUSY);
    return FT_SUCCESS ;
}

static FError FNandPageReadHwEcc(FNand *instance_p, u32 page_addr, u8 *buf, u32 page_copy_offset, u32 length, u32 chip_addr)
{
    FError ret;
    u32 nand_state = 0;
    u8 addr_buf[5] = {0};
    u32 memcpy_length = 0;
    volatile u32 wait_cnt;
    /* read operation */
    addr_buf[2] = page_addr;
    addr_buf[3] = page_addr >> 8;
    addr_buf[4] = page_addr >> 16;

    FNandDmaPackData pack_data =
    {
        .addr_p = addr_buf,
        .addr_length = 5,
        .phy_address = (uintptr)instance_p->dma_data_buffer.data_buffer,
        .phy_bytes_length = instance_p->nand_geometry[chip_addr].bytes_per_page,
        .chip_addr = chip_addr,
        .contiune_dma  = 1,
    };

    FNandDmaPack(&cmd_format[CMD_READ_OPTION_NEW], (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], &pack_data) ;

    /* Random Data Output */
    memset(addr_buf, 0, sizeof(addr_buf));
    /* 读取存储硬件ecc 偏移位置参数 */
    addr_buf[0] = instance_p->nand_geometry[chip_addr].bytes_per_page + instance_p->nand_geometry[chip_addr].ecc_offset;
    addr_buf[1] = (instance_p->nand_geometry[chip_addr].bytes_per_page + instance_p->nand_geometry[chip_addr].ecc_offset) >> 8;

    FNandDmaPackData pack_data2 =
    {
        .addr_p = addr_buf,
        .addr_length = 2,
        .phy_address = (uintptr)instance_p->dma_data_buffer.data_buffer + instance_p->nand_geometry[chip_addr].bytes_per_page,
        .phy_bytes_length = instance_p->nand_geometry[chip_addr].hw_ecc_length,
        .chip_addr = chip_addr,
        .contiune_dma = 0,
    };

    FNandDmaPack(&cmd_format[CMD_RANDOM_DATA_OUT], (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[16], &pack_data2) ;
    ret = FNandSendCmd(instance_p, (struct FNandDmaDescriptor *)&instance_p->descriptor_buffer.data_buffer[0], FNAND_WAIT_ECC_TYPE);
    if (ret != FT_SUCCESS)
    {
        return FNAND_ERR_OPERATION;
    }

    fsleep_microsec(100);
    /* 增加判断bit(16) 是否ecc 正忙 */
    nand_state = FNAND_READREG(instance_p->config.base_address, FNAND_STATE_OFFSET);

    while ((nand_state & FNAND_STATE_ECC_BUSY_OFFSET) && ((nand_state & FNAND_STATE_ECC_FINISH_OFFSET) == 0))
    {
        nand_state = FNAND_READREG(instance_p->config.base_address, FNAND_STATE_OFFSET);
    }

    if (nand_state & FNAND_STATE_ECC_ERROVER_OFFSET)
    {
        FNAND_COMMON_DEBUG_E("FNAND_STATE_ECC_ERROVER %x ,page is %x \n", 0, page_addr) ;
        return  FNAND_ERR_READ_ECC ;
    }
    else if (nand_state & FNAND_STATE_ECC_ERR_OFFSET)
    {
        s32 correct_num;
        FNAND_COMMON_DEBUG_W("FNAND ecc correct is in \r\n");
        correct_num = FNandCorrectEcc(instance_p->config.base_address, instance_p->nand_geometry[chip_addr].ecc_step_size,
                                      instance_p->nand_geometry[chip_addr].hw_ecc_steps, instance_p->dma_data_buffer.data_buffer,
                                      instance_p->nand_geometry[chip_addr].bytes_per_page);

        if (correct_num < 0)
        {
            FNAND_COMMON_DEBUG_W("CRC ECC IS ERROR \n") ;
            return FNAND_ERR_READ_ECC;
        }

        FNAND_COMMON_DEBUG_W("FNAND_STATE_ECC_ERR %x ,page is %x \n", correct_num, page_addr) ;
    }

    if (length && buf)
    {
        memcpy_length = (length > (pack_data.phy_bytes_length - page_copy_offset)) ? (pack_data.phy_bytes_length - page_copy_offset) : length;
        FCacheDCacheFlushRange((intptr)(instance_p->dma_data_buffer.data_buffer + page_copy_offset), memcpy_length);
        memcpy(buf, instance_p->dma_data_buffer.data_buffer + page_copy_offset, memcpy_length);
    }

    return FT_SUCCESS;
}

FError FNandFlashReadPageRaw(FNand *instance_p, FNandOpData *op_data_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(op_data_p != NULL);
    FError ret;
    ret = FNandPageRead(instance_p, op_data_p->page_addr, op_data_p->page_buf, op_data_p->page_offset, op_data_p->page_length, op_data_p->chip_addr);

    if (ret != FT_SUCCESS)
    {
        FNAND_COMMON_DEBUG_E("%s,FNandPageRead is error %x", __func__, ret);
        return ret;
    }

    if (op_data_p->obb_required)
    {
        ret = FNandPageReadOOb(instance_p, op_data_p->page_addr, op_data_p->oob_buf, op_data_p->oob_offset, op_data_p->oob_length, op_data_p->chip_addr);

        if (ret != FT_SUCCESS)
        {
            FNAND_COMMON_DEBUG_E("%s,FNandPageReadOOb is error %x", __func__, ret);
            return ret;
        }
    }

    return FT_SUCCESS;
}

FError FNandFlashReadPageHwEcc(FNand *instance_p, FNandOpData *op_data_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(op_data_p != NULL);
    FError ret;
    FNandConfig *config_p;
    config_p = &instance_p->config;
    FNandFlashReadStatus(instance_p, op_data_p->chip_addr);

    FNandEnableHwEcc(config_p->base_address);
    ret = FNandPageReadHwEcc(instance_p, op_data_p->page_addr, op_data_p->page_buf, op_data_p->page_offset, op_data_p->page_length, op_data_p->chip_addr);
    FNandDisableHwEcc(config_p->base_address);

    if (ret != FT_SUCCESS)
    {
        FNAND_COMMON_DEBUG_E("%s,FNandPageReadHwEcc is error %x", __func__, ret);
        return ret;
    }


    if (op_data_p->obb_required)
    {
        ret = FNandPageReadOOb(instance_p, op_data_p->page_addr, op_data_p->oob_buf, op_data_p->oob_offset, op_data_p->oob_length, op_data_p->chip_addr);
        if (ret != FT_SUCCESS)
        {
            FNAND_COMMON_DEBUG_E("%s,FNandPageReadOOb is error %x", __func__, ret);
            return ret;
        }
    }

    return  FT_SUCCESS;
}

FError FNandFlashWritePageRaw(FNand *instance_p, FNandOpData *op_data_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(op_data_p != NULL);
    FError ret;
    if (op_data_p->obb_required)
    {
        ret = FNandPageWriteOOb(instance_p, op_data_p->page_addr, op_data_p->oob_buf, op_data_p->oob_offset, op_data_p->oob_length, op_data_p->chip_addr);

        if (ret != FT_SUCCESS)
        {
            FNAND_COMMON_DEBUG_E("%s,FNandPageWriteOOb is error %x", __func__, ret);
            return ret;
        }
    }

    ret = FNandPageWrite(instance_p, op_data_p->page_addr, op_data_p->page_buf, op_data_p->page_offset, op_data_p->page_length, op_data_p->chip_addr);

    if (ret != FT_SUCCESS)
    {
        FNAND_COMMON_DEBUG_E("%s,FNandPageWrite is error %x", __func__, ret);
        return ret;
    }

    return FT_SUCCESS;
}


FError FNandFlashWritePageRawHwEcc(FNand *instance_p, FNandOpData *op_data_p)
{
    FError ret;
    FNandConfig *config_p;
    FASSERT(instance_p != NULL);
    FASSERT(op_data_p != NULL);

    FNandFlashReadStatus(instance_p, op_data_p->chip_addr);

    config_p = &instance_p->config;
    if (op_data_p->obb_required)
    {
        ret = FNandPageWriteOOb(instance_p, op_data_p->page_addr, op_data_p->oob_buf, op_data_p->oob_offset, op_data_p->oob_length, op_data_p->chip_addr);

        if (ret != FT_SUCCESS)
        {
            FNAND_COMMON_DEBUG_E("%s,FNandPageWriteOOb is error %x", __func__, ret);
            return ret;
        }
    }
    FNandEnableHwEcc(config_p->base_address);
    ret = FNandPageWriteHwEcc(instance_p, op_data_p->page_addr, op_data_p->page_buf, op_data_p->page_offset, op_data_p->page_length, op_data_p->chip_addr);
    FNandDisableHwEcc(config_p->base_address);

    if (ret != FT_SUCCESS)
    {
        FNAND_COMMON_DEBUG_E("%s,FNandPageWrite is error %x", __func__, ret);
        return ret;
    }

    return FT_SUCCESS;
}


FError FNandFlashOObRead(FNand *instance_p, FNandOpData *op_data_p)
{
    FASSERT(instance_p != NULL);
    FASSERT(op_data_p != NULL);
    FError ret;
    FNandConfig *config_p;
    config_p = &instance_p->config;

    ret = FNandPageReadOOb(instance_p, op_data_p->page_addr, op_data_p->oob_buf, op_data_p->oob_offset, op_data_p->oob_length, op_data_p->chip_addr);
    if (ret != FT_SUCCESS)
    {
        FNAND_COMMON_DEBUG_E("%s,FNandPageReadOOb is error %x", __func__, ret);
        return ret;
    }

    return FT_SUCCESS;
}



FError FNandFlashOObWrite(FNand *instance_p, FNandOpData *op_data_p)
{

    FASSERT(instance_p != NULL);
    FASSERT(op_data_p != NULL);
    FError ret;

    ret = FNandPageWriteOOb(instance_p, op_data_p->page_addr, op_data_p->oob_buf, op_data_p->oob_offset, op_data_p->oob_length, op_data_p->chip_addr);
    if (ret != FT_SUCCESS)
    {
        FNAND_COMMON_DEBUG_E("%s,FNandPageWriteOOb is error %x", __func__, ret);
        return ret;
    }
}


void FNandFlashFuncRegister(FNand *instance_p)
{
    FASSERT(instance_p != NULL);
    instance_p->write_p = FNandFlashWritePageRaw ;
    instance_p->read_p  = FNandFlashReadPageRaw ;
    instance_p->erase_p = FNandFlashEraseBlock ;
    instance_p->write_hw_ecc_p = FNandFlashWritePageRawHwEcc ;
    instance_p->read_hw_ecc_p = FNandFlashReadPageHwEcc ;
    instance_p->write_oob_p = FNandFlashOObWrite;
    instance_p->read_oob_p = FNandFlashOObRead;
}

