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
 * FilePath: fqspi_hw.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:00:41
 * Description:  This file is for the qspi register related functions
 * 
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/3/29  first release
 */
#include "ftypes.h"
#include "ferror_code.h"
#include "fassert.h"
#include "fdebug.h"
#include "fqspi_hw.h"

#define FQSPI_DEBUG_TAG "FQSPI-HW"
#define FQSPI_ERROR(format, ...)    FT_DEBUG_PRINT_E(FQSPI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FQSPI_WARN(format, ...)     FT_DEBUG_PRINT_W(FQSPI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FQSPI_INFO(format, ...)     FT_DEBUG_PRINT_I(FQSPI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FQSPI_DEBUG(format, ...)    FT_DEBUG_PRINT_D(FQSPI_DEBUG_TAG, format, ##__VA_ARGS__)


/**
 * @name: FQspiGetLdPortData
 * @msg:  read low data port register data
 * @param {uintptr} base_addr, FQSPI controller base address
 * @param {u8} *buf, read buffer
 * @param {size_t} len, read length
 * @return
 */
void FQspiGetLdPortData(uintptr base_addr, u8 *buf, size_t len)
{
    FASSERT(buf);
    u32 loop = 0;
    u32 reg_val = 0;

    for (loop = 0; loop < len; loop++)
    {
        /* read 4 bytes one time */
        if (0 == loop % 4)
        {
            reg_val = FQSPI_READ_REG32(base_addr, FQSPI_REG_LD_PORT_OFFSET);
        }

        /* assign buf byte by byte */
        buf[loop] = (u8)((reg_val >> (loop % 4) * 8) & 0xFF);
    }

}

/**
 * @name: FQspiSetLdPortData
 * @msg:  set low data port register data
 * @param {uintptr} base_addr, FQSPI controller base address
 * @param {u8} *buf, write buffer
 * @param {size_t} len, write length
 * @return
 */
void FQspiSetLdPortData(uintptr base_addr, const u8 *buf, size_t len)
{
    FASSERT(buf);
    FASSERT((len < 5) && (len));
    u32 reg_val = 0;

    if (1 == len)
    {
        reg_val = buf[0];
    }
    else if (2 == len)
    {
        reg_val = buf[1];
        reg_val = (reg_val << 8) + buf[0];
    }
    else if (3 == len)
    {
        reg_val = buf[2];
        reg_val = (reg_val << 8) + buf[1];
        reg_val = (reg_val << 8) + buf[0];
    }
    else
    {
        reg_val = buf[3];
        reg_val = (reg_val << 8) + buf[2];
        reg_val = (reg_val << 8) + buf[1];
        reg_val = (reg_val << 8) + buf[0];
    }

    /*write value to low bit port register 0x1c, make command valid */
    FQSPI_WRITE_REG32(base_addr, FQSPI_REG_LD_PORT_OFFSET, reg_val);
}


/**
 * @name: FQspiWriteFlush
 * @msg:  config write flush register to make wr_cfg complete program
 * @param {uintptr} base_addr, FQSPI controller base address
 * @return
 */
void FQspiWriteFlush(uintptr base_addr)
{
    FQSPI_WRITE_REG32(base_addr, FQSPI_REG_FLUSH_OFFSET, 0x1);
}

/**
 * @name: FQspiCommandPortSend
 * @msg:  send command port register value
 * @param {uintptr} base_addr, FQSPI controller base address
 * @return void
 */
void FQspiCommandPortSend(uintptr base_addr)
{
    FQSPI_WRITE_REG32(base_addr, FQSPI_REG_LD_PORT_OFFSET, 0x0);
}

/**
 * @name: FQspiAddrPortConfig
 * @msg:  config address port register value
 * @param {uintptr} base_addr, FQSPI controller base address
 * @param {u32} addr addresss value write to register
 * @return
 */
void FQspiAddrPortConfig(uintptr base_addr, u32 addr)
{
    FQSPI_WRITE_REG32(base_addr, FQSPI_REG_ADDR_PORT_OFFSET, addr);
}

/**
 * @name: FQspiXIPModeSet
 * @msg:  config qspi xip mode
 * @param {uintptr} base_addr, FQSPI controller base address
 * @param {u8} enable enable or disable xip mode
 * @return
 */
void FQspiXIPModeSet(uintptr base_addr, u8 enable)
{
    if (enable)
    {
        FQSPI_WRITE_REG32(base_addr, FQSPI_REG_MODE_OFFSET, FQSPI_QUAD_READ_MODE_ENABLE);
    }
    else
    {
        FQSPI_WRITE_REG32(base_addr, FQSPI_REG_MODE_OFFSET, FQSPI_QUAD_READ_MODE_DISABLE);
    }
}