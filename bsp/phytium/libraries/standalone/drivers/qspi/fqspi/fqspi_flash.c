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
 * FilePath: fqspi_flash.c
 * Date: 2022-07-12 15:42:55
 * LastEditTime: 2022-07-12 15:42:56
 * Description:  This file is for S25FS256, GD25Q256, GD25Q64 norflash program functions
 *
 * Modify History:
 *  Ver Who      Date        Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/3/29  first release
 * 1.1   wangxiaodong  2022/9/9   improve functions
 */

#include <string.h>
#include "fkernel.h"
#include "fassert.h"
#include "fqspi_flash.h"
#include "fqspi_hw.h"
#include "fqspi.h"
#include "sdkconfig.h"

#define FQSPI_DEBUG_TAG "FQSPI_FLASH"
#define FQSPI_ERROR(format, ...)    FT_DEBUG_PRINT_E(FQSPI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FQSPI_WARN(format, ...)     FT_DEBUG_PRINT_W(FQSPI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FQSPI_INFO(format, ...)     FT_DEBUG_PRINT_I(FQSPI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FQSPI_DEBUG(format, ...)    FT_DEBUG_PRINT_D(FQSPI_DEBUG_TAG, format, ##__VA_ARGS__)

/* When entering direct address access mode,
   read and write memory addresses need to be accessed in 4-byte alignment  */
#define FQSPI_ALIGNED_BYTE 4

typedef struct
{
    char *name;
    u8 mf_id;
    u8 type_id;
    u8 capacity_id;
    u32 capacity;
} FQspiFlashInfo;

/* supported manufacturer information table */
static const FQspiFlashInfo flash_info_table[] = FQSPI_FLASH_INFO_TABLE;

/*
 * @name: FQspiFlashDetect
 * @msg:  detect qspi flash information, include id, type, capacity, set qspi capacity register.
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed
 */
FError FQspiFlashDetect(FQspiCtrl *pctrl)
{
    FASSERT(pctrl);
    FError ret = FQSPI_SUCCESS;
    u8 flash_id[3] = {0};
    u8 i = 0;
    u32 index;
    u32 cs_number = 0;
    u32 min_detected_cs  = FQSPI_CS_NUM ; 
    
    for (index = 0; index < FQSPI_CS_NUM ; index++)
    {
        /* read id to flash_id */
        pctrl->config.channel = index;
        ret = FQspiFlashSpecialInstruction(pctrl, FQSPI_FLASH_CMD_RDID, flash_id, sizeof(flash_id));
        if (FQSPI_SUCCESS != ret)
        {
            FQSPI_INFO("Read flash id failed, ret 0x%x\r\n", ret);
            return ret;
        }

        if (flash_id[0] != 0xff)
        {
            FQSPI_INFO("CSN%d flash id = 0x%x, 0x%x, 0x%x\r\n", index, flash_id[0], flash_id[1], flash_id[2]);
        }
        else
        {
            FQSPI_INFO("The Detected CSN%d flash is not matched", index);
        }

        for (i = 0; i < sizeof(flash_info_table) / sizeof(FQspiFlashInfo); i++)
        {
            if ((flash_info_table[i].mf_id == flash_id[0]) && (flash_info_table[i].type_id == flash_id[1])
                && (flash_info_table[i].capacity_id == flash_id[2]))
            {
                pctrl->mf_id = flash_info_table[i].mf_id;
                pctrl->config.capacity = flash_info_table[i].capacity;
                cs_number++;
                /*get the min detected flash channel*/
                min_detected_cs = (min_detected_cs > index)?index:min_detected_cs ; 
                FQSPI_INFO("CSN%d Find a %s flash chip.\n", index, flash_info_table[i].name);
                break;
            }
        }
        /*The default channel is the min detected flash*/
        pctrl->config.channel = min_detected_cs;

        if (i == sizeof(flash_info_table) / sizeof(FQspiFlashInfo) && flash_id[0] != 0xff)
        {
            FQSPI_INFO("The Detected CSN%d flash not detected, id = 0x%x, 0x%x, 0x%x\r\n", index, flash_id[0], flash_id[1], flash_id[2]);
        }

    }

    pctrl->config.dev_num = cs_number - 1;
    /* set flash num and flash capacity */
    FQspiSetCapacityAndNum(pctrl);
    return ret;
}

/*
 * @name: FQspiFlashReset
 * @msg:  qspi Flash soft reset, FQSPI_CMD_ENABLE_RESET and FQSPI_CMD_RESET.
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed
 */
static FError FQspiFlashReset(FQspiCtrl *pctrl)
{
    FASSERT(pctrl);
    FError ret = FQSPI_SUCCESS;
    ret = FQspiFlashWriteReg(pctrl, FQSPI_CMD_ENABLE_RESET, NULL, 0);
    if (FQSPI_SUCCESS != ret)
    {
        FQSPI_ERROR("Failed to enable reset, test result 0x%x\r\n", ret);
        return ret;
    }

    ret = FQspiFlashWriteReg(pctrl, FQSPI_CMD_RESET, NULL, 0);
    if (FQSPI_SUCCESS != ret)
    {
        FQSPI_ERROR("Failed to reset, test result 0x%x\r\n", ret);
        return ret;
    }

    return ret;
}

/**
 * @name: FQspiFlashSpecialInstruction
 * @msg: Read some flash information by different cmd
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {u8} cmd, read register value command, include RDID, RDSR1, RDSR2, RDCR...
 * @param {u8} *buf, read buffer
 * @param {size_t} len, read length
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed
 */
FError FQspiFlashSpecialInstruction(FQspiCtrl *pctrl, u8 cmd, u8 *buf, size_t len)
{
    FASSERT(pctrl && buf);
    FError ret = FQSPI_SUCCESS;
    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        FQSPI_ERROR("Nor flash not ready !!!");
        return FQSPI_NOT_READY;
    }

    uintptr base_addr = pctrl->config.base_addr;

    memset(&pctrl->cmd_def, 0, sizeof(pctrl->cmd_def));
    pctrl->cmd_def.cmd = cmd;
    pctrl->cmd_def.wait = FQSPI_WAIT_DISABLE;
    pctrl->cmd_def.through = 0;
    pctrl->cmd_def.cs = pctrl->config.channel;
    pctrl->cmd_def.transfer = FQSPI_TRANSFER_1_1_1;
    pctrl->cmd_def.cmd_addr = FQSPI_CMD_ADDR_DISABLE;
    pctrl->cmd_def.latency = FQSPI_CMD_LATENCY_DISABLE;
    pctrl->cmd_def.data_transfer = FQSPI_CMD_DATA_ENABLE;
    pctrl->cmd_def.addr_sel = FQSPI_ADDR_SEL_3;
    pctrl->cmd_def.dummy = 0;
    pctrl->cmd_def.p_buffer = FQSPI_USE_BUFFER_ENABLE;
    pctrl->cmd_def.rw_num = (len - 1);
    pctrl->cmd_def.sck_sel = FQSPI_SCK_DIV_128;

    ret = FQspiCommandPortConfig(pctrl);
    if (ret != FT_SUCCESS)
    {
        FQSPI_ERROR("FQspiFlashSpecialInstruction FQspiCommandPortConfig failed!");
        return ret;
    }

    FQspiCommandPortSend(base_addr);

    FQspiGetLdPortData(base_addr, buf, len);

    return ret;
}

/**
 * @name: FQspiFlashReadSfdp
 * @msg: Read flash Serial Flash Discoverable Parameters
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {u32} offset，Relative Byte Address Offset
 * @param {u8} *buf, read buffer
 * @param {size_t} len, read length
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed
 */
FError FQspiFlashReadSfdp(FQspiCtrl *pctrl, u32 offset, u8 *buf, size_t len)
{
    FASSERT(pctrl && buf);
    FError ret = FQSPI_SUCCESS;
    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        FQSPI_ERROR("Nor flash not ready !!!");
        return FQSPI_NOT_READY;
    }

    uintptr base_addr = pctrl->config.base_addr;

    memset(&pctrl->cmd_def, 0, sizeof(pctrl->cmd_def));
    pctrl->cmd_def.cmd = FQSPI_FLASH_CMD_SFDP;
    pctrl->cmd_def.wait = FQSPI_WAIT_DISABLE;
    pctrl->cmd_def.through = 0;
    pctrl->cmd_def.cs = pctrl->config.channel;
    pctrl->cmd_def.transfer = FQSPI_TRANSFER_1_1_1;
    pctrl->cmd_def.cmd_addr = FQSPI_CMD_ADDR_ENABLE;
    pctrl->cmd_def.latency = FQSPI_CMD_LATENCY_ENABLE;
    pctrl->cmd_def.data_transfer = FQSPI_CMD_DATA_ENABLE;
    pctrl->cmd_def.addr_sel = FQSPI_ADDR_SEL_3;
    pctrl->cmd_def.dummy = 8;
    pctrl->cmd_def.p_buffer = FQSPI_USE_BUFFER_ENABLE;
    pctrl->cmd_def.rw_num = (len - 1);
    pctrl->cmd_def.sck_sel = FQSPI_SCK_DIV_128;

    ret = FQspiCommandPortConfig(pctrl);
    if (ret != FT_SUCCESS)
    {
        FQSPI_ERROR("FQspiFlashReadSfdp FQspiCommandPortConfig failed!");
        return ret;
    }

    /* write addr port register */
    FQspiAddrPortConfig(base_addr, offset);

    FQspiCommandPortSend(base_addr);

    FQspiGetLdPortData(base_addr, buf, len);

    return ret;
}

/**
 * @name: FQspiFlashReadReg
 * @msg: Read Qspi register value
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {u32} offset，Relative Byte Address Offset
 * @param {u8} *buf, read buffer
 * @param {size_t} len, read length
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed
 */
FError FQspiFlashReadReg(FQspiCtrl *pctrl, u32 offset, u8 *buf, size_t len)
{
    FASSERT(pctrl && buf);
    FError ret = FQSPI_SUCCESS;
    u32 cmd_reg = 0;
    uintptr base_addr = pctrl->config.base_addr;

    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        FQSPI_ERROR("Nor flash not ready !!!");
        return FQSPI_NOT_READY;
    }

    memset(&pctrl->cmd_def, 0, sizeof(pctrl->cmd_def));
    pctrl->cmd_def.cmd = FQSPI_FLASH_CMD_RDAR;
    pctrl->cmd_def.wait = FQSPI_WAIT_DISABLE;
    pctrl->cmd_def.through = 0;
    pctrl->cmd_def.cs = pctrl->config.channel;
    pctrl->cmd_def.transfer = FQSPI_TRANSFER_1_1_1;
    pctrl->cmd_def.cmd_addr = FQSPI_CMD_ADDR_ENABLE;
    pctrl->cmd_def.latency = FQSPI_CMD_LATENCY_ENABLE;
    pctrl->cmd_def.data_transfer = FQSPI_CMD_DATA_ENABLE;
    pctrl->cmd_def.addr_sel = FQSPI_ADDR_SEL_3;
    pctrl->cmd_def.dummy = 8;
    pctrl->cmd_def.p_buffer = FQSPI_USE_BUFFER_ENABLE;
    pctrl->cmd_def.rw_num = (len - 1);
    pctrl->cmd_def.sck_sel = FQSPI_SCK_DIV_128;

    ret = FQspiCommandPortConfig(pctrl);
    if (ret != FT_SUCCESS)
    {
        FQSPI_ERROR("FQspiFlashReadReg FQspiCommandPortConfig failed!");
        return ret;
    }

    /* write addr port register */
    FQspiAddrPortConfig(base_addr, offset);

    FQspiCommandPortSend(base_addr);

    FQspiGetLdPortData(base_addr, buf, len);

    /* wait SR1V bit0 WIP is ready, not device busy */
    ret = FQspiFlashWaitForCmd(pctrl);
    if (ret != FT_SUCCESS)
    {
        FQSPI_ERROR("FQspiFlashReadReg FQspiCommandPortConfig failed!");
        return ret;
    }

    return ret;
}

/**
 * @name: FQspiFlashReadData
 * @msg:  read flash data
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {u32} chip_addr, The start address of the chip to read
 * @param {u8} *buf, read buffer
 * @param {size_t} len, read length
 * @return size_t Indicates the length of the data read, zero indicates read fails
 */
size_t FQspiFlashReadData(FQspiCtrl *pctrl, u32 chip_addr, u8 *buf, size_t len)
{
    /* addr of copy dst or src might be zero */
    FASSERT(pctrl && buf);
    size_t loop = 0;
    const size_t cnt = len / FQSPI_ALIGNED_BYTE;    /* cnt number of 4-bytes need copy  */
    const size_t remain = len % FQSPI_ALIGNED_BYTE; /* remain number of 1-byte not aligned */
    u8 align_buf[FQSPI_ALIGNED_BYTE];
    size_t copy_len = 0;
    u32 addr = pctrl->config.mem_start + pctrl->config.channel * pctrl->flash_size + chip_addr;
    intptr src_addr = (intptr)addr; /* conver to 32/64 bit addr */
    intptr dst_addr = (intptr)buf;

    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        FQSPI_ERROR("Nor flash not ready !!!");
        return 0;
    }
    if (0 == pctrl->rd_cfg.rd_cmd)
    {
        FQSPI_ERROR("Nor flash read command is not ready !!!");
        return 0;
    }

    if (0 == len)
    {
        return 0;
    }

    if (IS_ALIGNED(src_addr, FQSPI_ALIGNED_BYTE)) /* if copy src is aligned by 4 bytes */
    {
        /* read 4-bytes aligned buf part */
        for (loop = 0; loop < cnt; loop++)
        {
            *(u32 *)dst_addr = *(volatile u32 *)(src_addr);
            src_addr += FQSPI_ALIGNED_BYTE;
            dst_addr += FQSPI_ALIGNED_BYTE;
        }

        copy_len += (loop << 2);

        if (remain > 0)
        {
            *(u32 *)align_buf = *(volatile u32 *)(src_addr);
        }

        /* read remain un-aligned buf byte by byte */
        for (loop = 0; loop < remain; loop++)
        {
            *(u8 *)dst_addr = align_buf[loop];
            dst_addr += 1;
        }

        copy_len += loop;

    }
    else /* if copy src is not aligned */
    {
        /* read byte by byte */
        for (loop = 0; loop < len; loop++)
        {
            *(u8 *)dst_addr = *(volatile u8 *)(src_addr);
            dst_addr += 1;
            src_addr += 1;
        }
        copy_len += loop;

    }

    return copy_len;
}

/**
 * @name: FQspiFlashReadDataConfig
 * @msg:  read flash data configuration
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {u8} command, command to read flash，see the Flash manual for details
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed 表示配置成功，其它返回值表示配置失败
 */
FError FQspiFlashReadDataConfig(FQspiCtrl *pctrl, u8 command)
{
    FASSERT(pctrl);
    FError ret = FQSPI_SUCCESS;

    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        FQSPI_ERROR("Nor flash not ready !!!");
        ret |= FQSPI_NOT_READY;
        return ret;
    }

    uintptr base_addr = pctrl->config.base_addr;

    /* clear sr1 = 0, set config register1 bit1 quad = 1 */
    u8 wrr_buf[2] = {0x0, 0x02};

    FQspiXIPModeSet(base_addr, FQSPI_XIP_ENTER);

    /* set cmd region, command */
    memset(&pctrl->rd_cfg, 0, sizeof(pctrl->rd_cfg));
    pctrl->rd_cfg.rd_cmd = command;

    /* read buffer */
    pctrl->rd_cfg.d_buffer = FQSPI_USE_BUFFER_ENABLE;
    pctrl->rd_cfg.rd_sck_sel = FQSPI_SCK_DIV_128;

    switch (command)
    {
        case FQSPI_FLASH_CMD_READ:
            FQspiFlashReset(pctrl);
            pctrl->rd_cfg.rd_addr_sel = FQSPI_ADDR_SEL_3;
            pctrl->rd_cfg.rd_transfer = FQSPI_TRANSFER_1_1_1;
            break;

        case FQSPI_FLASH_CMD_4READ:
            pctrl->rd_cfg.rd_addr_sel = FQSPI_ADDR_SEL_4;
            pctrl->rd_cfg.rd_transfer = FQSPI_TRANSFER_1_1_1;
            break;

        case FQSPI_FLASH_CMD_FAST_READ:
            pctrl->rd_cfg.rd_addr_sel = FQSPI_ADDR_SEL_3;
            pctrl->rd_cfg.rd_transfer = FQSPI_TRANSFER_1_1_1;
            pctrl->rd_cfg.dummy = 8;
            pctrl->rd_cfg.rd_latency = FQSPI_CMD_LATENCY_ENABLE;
            break;

        case FQSPI_FLASH_CMD_4FAST_READ:
            pctrl->rd_cfg.rd_addr_sel = FQSPI_ADDR_SEL_4;
            pctrl->rd_cfg.rd_transfer = FQSPI_TRANSFER_1_1_1;
            pctrl->rd_cfg.dummy = 8;
            pctrl->rd_cfg.rd_latency = FQSPI_CMD_LATENCY_ENABLE;
            break;

        case FQSPI_FLASH_CMD_DOR:
            pctrl->rd_cfg.rd_addr_sel = FQSPI_ADDR_SEL_3;
            pctrl->rd_cfg.rd_transfer = FQSPI_TRANSFER_1_1_2;
            pctrl->rd_cfg.dummy = 8;
            pctrl->rd_cfg.rd_latency = FQSPI_CMD_LATENCY_ENABLE;
            break;

        case FQSPI_FLASH_CMD_QOR:
            pctrl->rd_cfg.rd_addr_sel = FQSPI_ADDR_SEL_3;
            pctrl->rd_cfg.rd_transfer = FQSPI_TRANSFER_1_1_4;
            pctrl->rd_cfg.dummy = 8;
            pctrl->rd_cfg.rd_latency = FQSPI_CMD_LATENCY_ENABLE;
            break;

        case FQSPI_FLASH_CMD_QWFR:
            pctrl->rd_cfg.rd_addr_sel = FQSPI_ADDR_SEL_3;
            pctrl->rd_cfg.rd_transfer = FQSPI_TRANSFER_1_4_4;
            pctrl->rd_cfg.dummy = 2;
            pctrl->rd_cfg.rd_latency = FQSPI_CMD_LATENCY_ENABLE;
            break;

        case FQSPI_FLASH_CMD_DUAL_READ:
            pctrl->rd_cfg.rd_addr_sel = FQSPI_ADDR_SEL_3;
            pctrl->rd_cfg.rd_transfer = FQSPI_TRANSFER_1_2_2;
            pctrl->rd_cfg.rd_latency = FQSPI_CMD_LATENCY_ENABLE;
            pctrl->rd_cfg.dummy = 4;
            if (pctrl->mf_id == FQSPI_FLASH_MF_ID_CYPRESS)
            {
                pctrl->rd_cfg.mode_byte = 0x1;
                pctrl->rd_cfg.cmd_sign = FQSPI_QUAD_READ_MODE_CMD;
                pctrl->rd_cfg.dummy = 8;
            }
            else if (pctrl->mf_id == FQSPI_FLASH_MF_ID_GIGADEVICE)
            {
                pctrl->rd_cfg.dummy = 4;
            }
            else if (pctrl->mf_id == FQSPI_FLASH_MF_ID_BOYA)
            {
                pctrl->rd_cfg.dummy = 4;
            }
            break;

        case FQSPI_FLASH_CMD_QIOR:
            /* set SR1V and CR1V */
            FQspiFlashEnableWrite(pctrl);

            pctrl->rd_cfg.rd_addr_sel = FQSPI_ADDR_SEL_3;
            pctrl->rd_cfg.rd_transfer = FQSPI_TRANSFER_1_4_4;
            pctrl->rd_cfg.rd_latency = FQSPI_CMD_LATENCY_ENABLE;
            
            pctrl->rd_cfg.dummy = 6;

            if (pctrl->mf_id == FQSPI_FLASH_MF_ID_CYPRESS)
            {
                pctrl->rd_cfg.dummy = 10;
                /* use wrr write config register 1 */
                ret = FQspiFlashWriteReg(pctrl, FQSPI_FLASH_CMD_WRR, wrr_buf, sizeof(wrr_buf));
                if (FQSPI_SUCCESS != ret)
                {
                    FQSPI_ERROR("Failed to write cmd wrr, test result 0x%x", ret);
                    return 0;
                }
            }
            else if (pctrl->mf_id == FQSPI_FLASH_MF_ID_GIGADEVICE)
            {
                pctrl->rd_cfg.dummy = 6;
                /* use wrr write config register 1 */
                ret = FQspiFlashWriteReg(pctrl, FQSPI_FLASH_CMD_WRR, wrr_buf, sizeof(wrr_buf));
                if (FQSPI_SUCCESS != ret)
                {
                    FQSPI_ERROR("Failed to write cmd wrr, test result 0x%x", ret);
                    return 0;
                }
            }
            else if (pctrl->mf_id == FQSPI_FLASH_MF_ID_BOYA)
            {
                pctrl->rd_cfg.dummy = 6;
                ret = FQspiFlashWriteReg(pctrl, FQSPI_FLASH_CMD_WRITE_SR2, &wrr_buf[1], 1);
                if (FQSPI_SUCCESS != ret)
                {
                    FQSPI_ERROR("Failed to write cmd wrr, test result 0x%x", ret);
                    return 0;
                }
            }

            break;

        case FQSPI_FLASH_CMD_4QIOR:
            pctrl->rd_cfg.rd_addr_sel = FQSPI_ADDR_SEL_4;
            pctrl->rd_cfg.rd_transfer = FQSPI_TRANSFER_1_4_4;
            pctrl->rd_cfg.mode_byte = 0x1;
            pctrl->rd_cfg.cmd_sign = FQSPI_QUAD_READ_MODE_CMD;
            pctrl->rd_cfg.rd_latency = FQSPI_CMD_LATENCY_ENABLE;
            pctrl->rd_cfg.dummy = 8;

            /* set SR1V and CR1V */
            FQspiFlashEnableWrite(pctrl);
            /* use wrr write config register 1 */
            ret = FQspiFlashWriteReg(pctrl, FQSPI_FLASH_CMD_WRR, wrr_buf, sizeof(wrr_buf));
            if (FQSPI_SUCCESS != ret)
            {
                FQSPI_ERROR("Failed to write cmd wrr, test result 0x%x\r\n", ret);
                return ret;
            }
            break;

        default:
            return FQSPI_INVAL_PARAM;
            break;
    }

    ret = FQspiRdCfgConfig(pctrl);

    return ret;
}

/**
 * @name: FQspiFlashWriteData
 * @msg:  write flash data
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {u8} command, command to write flash，see the Flash manual for details
 * @param {u32} chip_addr, The start address of the chip to write
 * @param {u8} *buf, write buffer
 * @param {size_t} len, write length
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed 表示写入成功，其它返回值表示写入失败
 */
FError FQspiFlashWriteData(FQspiCtrl *pctrl, u8 command, u32 chip_addr, const u8 *buf, size_t len)
{
    FASSERT(pctrl && buf);
    FError ret = FQSPI_SUCCESS;
    u32 loop = 0;
    const u32 mask = (u32)GENMASK(1, 0);
    u32 reg_val = 0;
    u32 val = 0;
    u32 aligned_bit = 0;

    u8 tmp[FQSPI_ALIGNED_BYTE] = {0xff, 0xff, 0xff, 0xff};
    u32 addr = pctrl->config.mem_start + pctrl->config.channel * pctrl->flash_size + chip_addr;
    uintptr base_addr = pctrl->config.base_addr;

    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        FQSPI_ERROR("Nor flash not ready !!!");
        return FQSPI_NOT_READY;
    }

    /* Flash write enable */
    FQspiFlashEnableWrite(pctrl);

    memset(&pctrl->wr_cfg, 0, sizeof(pctrl->wr_cfg));
    /* set cmd region, command */
    pctrl->wr_cfg.wr_cmd = command;
    pctrl->wr_cfg.wr_wait = FQSPI_WAIT_ENABLE;
    /* clear addr select bit */
    pctrl->wr_cfg.wr_addr_sel = 0;
    /* set wr mode, use buffer */
    pctrl->wr_cfg.wr_mode = FQSPI_USE_BUFFER_ENABLE;
    /* set sck_sel region, clk_div */
    pctrl->wr_cfg.wr_sck_sel = FQSPI_SCK_DIV_128;

    /* set addr_sel region, FQSPI_ADDR_SEL_3 or FQSPI_ADDR_SEL_4 */
    switch (command)
    {
        case FQSPI_FLASH_CMD_PP:
            pctrl->wr_cfg.wr_addr_sel = FQSPI_ADDR_SEL_3;
            break;
        case FQSPI_FLASH_CMD_QPP:
            pctrl->wr_cfg.wr_addr_sel = FQSPI_ADDR_SEL_3;
            pctrl->wr_cfg.wr_transfer = FQSPI_TRANSFER_1_1_4;
            break;
        case FQSPI_FLASH_CMD_4PP:
        case FQSPI_FLASH_CMD_4QPP:
            pctrl->wr_cfg.wr_addr_sel = FQSPI_ADDR_SEL_4;
            break;
        default:
            ret |= FQSPI_NOT_SUPPORT;
            return ret;
            break;
    }

    /*write wr_cfg to Write config register 0x08 */
    FQspiWrCfgConfig(pctrl);

    if (IS_ALIGNED(addr, FQSPI_ALIGNED_BYTE)) /* if copy src is aligned by 4 bytes */
    {
        /* write alligned data into memory space */
        for (loop = 0; loop < (len >> 2); loop++)
        {
            FQSPI_DAT_WRITE(addr + FQSPI_ALIGNED_BYTE * loop, *(u32 *)(buf + FQSPI_ALIGNED_BYTE * loop));
        }
        /* write not alligned data into memory space */
        if (len & mask)
        {
            addr = addr + (len & ~mask);
            memcpy(tmp, buf + (len & ~mask), len & mask);
            FQSPI_DAT_WRITE(addr, *(u32 *)(tmp));
        }
    }
    else
    {
        aligned_bit = (addr & mask);
        addr = addr - aligned_bit;
        reg_val = FQSPI_READ_REG32(addr, 0);

        for (loop = 0; loop < (FQSPI_ALIGNED_BYTE - aligned_bit); loop++)
        {
            val = (val << 8) | (buf[loop]);
            reg_val &= (~(0xff << (loop * 8)));
        }

        reg_val |= val;
        reg_val = __builtin_bswap32(reg_val);
        FQSPI_DAT_WRITE(addr, reg_val);

        buf = buf + loop;
        len = len - loop;
        addr = addr + FQSPI_ALIGNED_BYTE;

        FQSPI_DEBUG("addr=%p, buf=%p, len=%d, value=%#x\r\n", addr, buf, len, *(u32 *)(buf));

        for (loop = 0; loop < (len >> 2); loop++)
        {
            FQSPI_DAT_WRITE(addr + FQSPI_ALIGNED_BYTE * loop, *(u32 *)(buf + FQSPI_ALIGNED_BYTE * loop));
        }

        if (!IS_ALIGNED(len, FQSPI_ALIGNED_BYTE))
        {
            buf = buf + FQSPI_ALIGNED_BYTE * loop;
            len = len - FQSPI_ALIGNED_BYTE * loop;
            addr = addr + FQSPI_ALIGNED_BYTE * loop;
            memcpy(tmp, buf, len);
            FQSPI_DAT_WRITE(addr, *(u32 *)(tmp));
        }
    }

    /* flush buffer data to Flash */
    FQspiWriteFlush(base_addr);

    ret = FQspiFlashWaitForCmd(pctrl);

    return ret;
}

/**
 * @name: FQspiFlashPortReadData
 * @msg:  read flash data use register port
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {u8} cmd, command to read flash，see the Flash manual for details
 * @param {u32} chip_addr, The start address of the chip to read
 * @param {u8} *buf, read buffer
 * @param {size_t} len, read length
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed
 */
FError FQspiFlashPortReadData(FQspiCtrl *pctrl, u8 cmd, u32 chip_addr, u8 *buf, size_t len)
{
    FASSERT(pctrl && buf);
    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        FQSPI_ERROR("Nor flash not ready !!!");
        return FQSPI_NOT_READY;
    }

    FError ret = FQSPI_SUCCESS;
    u32 addr = chip_addr + pctrl->config.channel * pctrl->flash_size;
    uintptr base_addr = pctrl->config.base_addr;

    FQspiXIPModeSet(base_addr, FQSPI_XIP_EXIT);

    memset(&pctrl->cmd_def, 0, sizeof(pctrl->cmd_def));
    pctrl->cmd_def.cmd = cmd;
    pctrl->cmd_def.wait = FQSPI_WAIT_ENABLE;
    pctrl->cmd_def.through = 0;
    pctrl->cmd_def.cs = pctrl->config.channel;
    pctrl->cmd_def.transfer = FQSPI_TRANSFER_1_1_1;
    pctrl->cmd_def.cmd_addr = FQSPI_CMD_ADDR_ENABLE;
    pctrl->cmd_def.latency = FQSPI_CMD_LATENCY_DISABLE;
    pctrl->cmd_def.data_transfer = FQSPI_CMD_DATA_ENABLE;
    pctrl->cmd_def.addr_sel = FQSPI_ADDR_SEL_3;
    pctrl->cmd_def.dummy = 0;
    pctrl->cmd_def.p_buffer = FQSPI_USE_BUFFER_ENABLE;
    pctrl->cmd_def.rw_num = (len - 1);
    pctrl->cmd_def.sck_sel = FQSPI_SCK_DIV_128;

    ret = FQspiCommandPortConfig(pctrl);
    if (ret != FT_SUCCESS)
    {
        FQSPI_ERROR("FQspiFlashPortReadData FQspiCommandPortConfig failed!");
        return ret;
    }

    /* write addr port register */
    FQspiAddrPortConfig(base_addr, addr);

    FQspiCommandPortSend(base_addr);

    FQspiGetLdPortData(base_addr, buf, len);

    /* wait SR1V bit0 WIP is ready, not device busy */
    ret = FQspiFlashWaitForCmd(pctrl);

    return ret;
}

/**
 * @name: FQspiFlashPortWriteData
 * @msg:  write flash data use register port
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {u8} cmd, command to write flash，see the Flash manual for details
 * @param {u32} chip_addr, The start address of the chip to write
 * @param {u8} *buf, write buffer
 * @param {size_t} len, write length
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed
 */
FError FQspiFlashPortWriteData(FQspiCtrl *pctrl, u8 cmd, u32 chip_addr, u8 *buf, size_t len)
{
    FASSERT(pctrl && buf);
    FASSERT(len <= FQSPI_CMD_PORT_CMD_RW_MAX);

    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        FQSPI_ERROR("Nor flash not ready !!!");
        return FQSPI_NOT_READY;
    }

    FError ret = FQSPI_SUCCESS;
    u32 addr = chip_addr + pctrl->config.channel * pctrl->flash_size;
    uintptr base_addr = pctrl->config.base_addr;

    /* Flash write enable */
    FQspiFlashEnableWrite(pctrl);

    memset(&pctrl->cmd_def, 0, sizeof(pctrl->cmd_def));
    pctrl->cmd_def.cmd = cmd;
    pctrl->cmd_def.wait = FQSPI_WAIT_ENABLE;
    pctrl->cmd_def.through = 0;
    pctrl->cmd_def.cs = pctrl->config.channel;
    pctrl->cmd_def.transfer = FQSPI_TRANSFER_1_1_1;
    pctrl->cmd_def.cmd_addr = FQSPI_CMD_ADDR_ENABLE;
    pctrl->cmd_def.latency = FQSPI_CMD_LATENCY_DISABLE;
    pctrl->cmd_def.data_transfer = FQSPI_CMD_DATA_ENABLE;
    pctrl->cmd_def.addr_sel = FQSPI_ADDR_SEL_3;
    pctrl->cmd_def.dummy = 0;
    pctrl->cmd_def.p_buffer = FQSPI_USE_BUFFER_DISABLE;
    pctrl->cmd_def.rw_num = (len - 1);
    pctrl->cmd_def.sck_sel = FQSPI_SCK_DIV_128;

    /*write cmd_reg to Command port register 0x10 */
    ret = FQspiCommandPortConfig(pctrl);
    if (ret != FT_SUCCESS)
    {
        FQSPI_ERROR("FQspiFlashPortWriteData FQspiCommandPortConfig failed!");
        return ret;
    }

    /* write addr port register */
    FQspiAddrPortConfig(base_addr, addr);

    FQspiSetLdPortData(base_addr, buf, len);

    /* wait SR1V bit0 WIP is ready, not device busy */
    ret = FQspiFlashWaitForCmd(pctrl);

    return ret;
}


/**
 * @name: FQspiFlashErase
 * @msg:  erase flash data
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {u8} command, command to erase flash, see the Flash manual for details
 * @param {u32} offset，Relative Byte Address Offset
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed 表示擦除成功，其它返回值表示擦除失败
 */
FError FQspiFlashErase(FQspiCtrl *pctrl, u8 command, u32 offset)
{
    FASSERT(pctrl);
    FError ret = FQSPI_SUCCESS;
    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        FQSPI_ERROR("Nor flash not ready !!!");
        return FQSPI_NOT_READY;
    }

    uintptr base_addr = pctrl->config.base_addr;

    /* Flash write enable */
    FQspiFlashEnableWrite(pctrl);

    memset(&pctrl->cmd_def, 0, sizeof(pctrl->cmd_def));
    pctrl->cmd_def.cmd = command;
    pctrl->cmd_def.cs = pctrl->config.channel;
    pctrl->cmd_def.sck_sel = FQSPI_SCK_DIV_128;

    switch (command)
    {
        case FQSPI_FLASH_CMD_SE:
            /* set addr_sel region, FQSPI_ADDR_SEL_3 or FQSPI_ADDR_SEL_4 */
            pctrl->cmd_def.addr_sel = FQSPI_ADDR_SEL_3;

            /* set cmd_addr region, by command, have addr transfer */
            pctrl->cmd_def.cmd_addr = FQSPI_CMD_ADDR_ENABLE;

            /* need some execution time  */
            pctrl->cmd_def.wait = FQSPI_WAIT_ENABLE;

            break;
        case FQSPI_FLASH_CMD_4SE:
            pctrl->cmd_def.addr_sel = FQSPI_ADDR_SEL_4;
            pctrl->cmd_def.cmd_addr = FQSPI_CMD_ADDR_ENABLE;
            pctrl->cmd_def.wait = FQSPI_WAIT_ENABLE;

            break;
        case FQSPI_FLASH_CMD_P4E:
            pctrl->cmd_def.addr_sel = FQSPI_ADDR_SEL_3;
            pctrl->cmd_def.cmd_addr = FQSPI_CMD_ADDR_ENABLE;

            break;
        case FQSPI_FLASH_CMD_4P4E:
            pctrl->cmd_def.addr_sel = FQSPI_ADDR_SEL_4;
            pctrl->cmd_def.cmd_addr = FQSPI_CMD_ADDR_ENABLE;

            break;
        case FQSPI_FLASH_CMD_BE:
            pctrl->cmd_def.addr_sel = FQSPI_ADDR_SEL_3;
            break;
        case FQSPI_FLASH_CMD_4BE:
            pctrl->cmd_def.addr_sel = FQSPI_ADDR_SEL_3;
            break;
        default:
            return FQSPI_NOT_SUPPORT;
    }

    /*write cmd_reg to Command port register 0x10 */
    ret = FQspiCommandPortConfig(pctrl);
    if (ret != FT_SUCCESS)
    {
        FQSPI_ERROR("FQspiFlashErase FQspiCommandPortConfig failed!");
        return ret;
    }

    /* set addr port register, specify addr transfer */
    FQspiAddrPortConfig(base_addr, offset);

    /*write value to low bit port register 0x1c, make command valid */
    FQspiCommandPortSend(base_addr);

    /* wait command perform end */
    ret = FQspiFlashWaitForCmd(pctrl);

    return ret;
}

/**
 * @name: FQspiFlashEnableWrite
 * @msg:  Flash write enable
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed 表示执行成功，其它返回值表示执行失败
 */
FError FQspiFlashEnableWrite(FQspiCtrl *pctrl)
{
    FASSERT(pctrl);
    FError ret = FQSPI_SUCCESS;
    u32 timeout = FQSPI_BUSY_TIMEOUT_US;

    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        FQSPI_ERROR("Nor flash not ready !!!");
        return FQSPI_NOT_READY;
    }
    uintptr base_addr = pctrl->config.base_addr;

    memset(&pctrl->cmd_def, 0, sizeof(pctrl->cmd_def));
    pctrl->cmd_def.cmd = FQSPI_FLASH_CMD_WREN;
    pctrl->cmd_def.cs = pctrl->config.channel;
    pctrl->cmd_def.sck_sel = FQSPI_SCK_DIV_128;

    /*write cmd_reg to Command port register 0x10 */
    ret = FQspiCommandPortConfig(pctrl);
    if (ret != FT_SUCCESS)
    {
        FQSPI_ERROR("FQspiFlashEnableWrite FQspiCommandPortConfig failed!");
        return ret;
    }

    /*write value to low bit port register 0x1c, make command valid */
    FQspiCommandPortSend(base_addr);

    /* wait SR1V bit0 WIP is ready, not device busy */
    ret = FQspiFlashWaitForCmd(pctrl);

    return ret;
}

/**
 * @name: FQspiFlashDisableWrite
 * @msg:  Flash write disable
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed 表示执行成功，其它返回值表示执行失败
 */
FError FQspiFlashDisableWrite(FQspiCtrl *pctrl)
{
    FASSERT(pctrl);
    FError ret = FQSPI_SUCCESS;
    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        FQSPI_ERROR("Nor flash not ready !!!");
        return FQSPI_NOT_READY;
    }
    uintptr base_addr = pctrl->config.base_addr;

    memset(&pctrl->cmd_def, 0, sizeof(pctrl->cmd_def));
    pctrl->cmd_def.cmd = FQSPI_FLASH_CMD_WRDI;
    pctrl->cmd_def.cs = pctrl->config.channel;
    pctrl->cmd_def.sck_sel = FQSPI_SCK_DIV_128;

    /*write cmd_reg to Command port register 0x10 */
    ret = FQspiCommandPortConfig(pctrl);
    if (ret != FT_SUCCESS)
    {
        FQSPI_ERROR("FQspiFlashDisableWrite FQspiCommandPortConfig failed!");
        return ret;
    }

    /*write value to low bit port register 0x1c, make command valid */
    FQspiCommandPortSend(base_addr);

    return ret;
}

/**
 * @name: FQspiFlashWriteReg
 * @msg: write flash register
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {u8} command, command to write flash register，see the Flash manual for details
 * @param {u8} *buf, write buffer
 * @param {size_t} len, write length
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed 表示写入成功，其它返回值表示写入失败
 */
FError FQspiFlashWriteReg(FQspiCtrl *pctrl, u8 command, const u8 *buf, size_t len)
{
    FASSERT(pctrl);
    FError ret = FQSPI_SUCCESS;
    u8 sr1_v = 0;

    if (FT_COMPONENT_IS_READY != pctrl->is_ready)
    {
        FQSPI_ERROR("Nor flash not ready !!!");
        return FQSPI_NOT_READY;
    }

    uintptr base_addr = pctrl->config.base_addr;

    memset(&pctrl->cmd_def, 0, sizeof(pctrl->cmd_def));
    pctrl->cmd_def.cmd = command;
    pctrl->cmd_def.cs = pctrl->config.channel;
    pctrl->cmd_def.data_transfer = FQSPI_CMD_DATA_ENABLE;
    pctrl->cmd_def.p_buffer = FQSPI_USE_BUFFER_ENABLE;
    pctrl->cmd_def.sck_sel = FQSPI_SCK_DIV_128;

    if (len > 4)
    {
        FQSPI_ERROR("Data length exceed. commad 0x%lx, len:%d \n", command, len);
        return FQSPI_INVAL_PARAM;
    }
    else if ((len > 0) && (buf != NULL))
    {
        /* set rw_num region, len - 1 */
        pctrl->cmd_def.rw_num = (len - 1);

        /*write cmd_reg to Command port register 0x10 */
        FQspiCommandPortConfig(pctrl);

        /* set ld port data(buf) and make command valid */
        FQspiSetLdPortData(base_addr, buf, len);
    }
    else
    {
        /*write cmd_reg to Command port register 0x10 */
        FQspiCommandPortConfig(pctrl);

        FQspiCommandPortSend(base_addr);
    }

    /* wait SR1V bit0 WIP is ready, not device busy */
    ret = FQspiFlashWaitForCmd(pctrl);

    return ret;
}

/**
 * @name: FQspiFlashWaitForCmd
 * @msg: wait flash command execution complete
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @return {FError} err code information, FQSPI_SUCCESS indicates success，others indicates failed 表示成功完成，其它返回值表示失败
 */
FError FQspiFlashWaitForCmd(FQspiCtrl *pctrl)
{
    FASSERT(pctrl);
    u32 timeout = FQSPI_BUSY_TIMEOUT_US;
    FError ret = FQSPI_SUCCESS;
    u8 sr1 = 0;

    uintptr base_addr = pctrl->config.base_addr;

    ret = FQspiFlashSpecialInstruction(pctrl, FQSPI_FLASH_CMD_RDSR1, &sr1, sizeof(sr1));
    if (FQSPI_SUCCESS != ret)
    {
        FQSPI_ERROR("Failed to read sr1, result 0x%x\r\n", ret);
        return ret;
    }

    do
    {
        timeout--;
        /* read value from low bit port register 0x1c,
        Read Status Register 1 is related to SR1V WIP field (bit0) */
        FQspiGetLdPortData(base_addr, &sr1, 1);

        if (!timeout)
        {
            FQSPI_ERROR("Wait cmd timeout !!!");
            ret = FQSPI_TIMEOUT;
            break;
        }

    }
    while (sr1 & FQSPI_NOR_FLASH_STATE_BUSY);

    return ret;
}

/**
 * @name: FQspiFlashWProtectSet
 * @msg:  Set qspi write protection function
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {u32} Write protect function enable/disable 1:enable,0:disable
 * @return err code information, FQSPI_SUCCESS indicates success，others indicates failed
 */
FError FQspiFlashWProtectSet(FQspiCtrl *pctrl, boolean wprotect, u8 channel)
{
    FASSERT(pctrl);
    FError ret = FQSPI_SUCCESS;
    u8 wp_block[2] = {FQSPI_FLASH_WP_ENABLE, FQSPI_FLASH_WP_DISABLE};
    FQspiChannelSet(pctrl, channel);
    ret = FQspiFlashEnableWrite(pctrl);
    if (wprotect == TRUE)
    {
        ret = FQspiFlashWriteReg(pctrl, FQSPI_FLASH_CMD_WRR, &wp_block[0], 1);
    }
    else if (wprotect == FALSE)
    {
        ret = FQspiFlashWriteReg(pctrl, FQSPI_FLASH_CMD_WRR, &wp_block[1], 1);
    }
    return ret;
}