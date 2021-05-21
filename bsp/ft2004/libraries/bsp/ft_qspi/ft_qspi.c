/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-05 22:15:53
 * @LastEditTime: 2021-05-25 16:45:36
 * @Description:  Description of file
 * @Modify History:
 * * * Ver   Who        Date         Changes
 * * ----- ------     --------    --------------------------------------
 * *   1.00   hh        2021.04-06    init
 */

#include "ft_qspi.h"
#include "qspi_hw.h"
#include "ft_io.h"
#include "ft_assert.h"
#include "ft_types.h"
#include "string.h"

#include "ft_debug.h"

#define FTQSPI_DEBUG_TAG "FTQSPI"

#define FTQSPI_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FTQSPI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FTQSPI_DEBUG_E(format, ...) FT_DEBUG_PRINT_E(FTQSPI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FTQSPI_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FTQSPI_DEBUG_TAG, format, ##__VA_ARGS__)

ft_error_t FQSpi_CfgInitialize(FQSpi_t *pQspi, FQSpi_Config_t *pConfig)
{
    Ft_assertNonvoid(pQspi != NULL);
    Ft_assertNonvoid(pConfig != NULL);

    pQspi->config = *pConfig;
    pQspi->isReady = FT_COMPONENT_IS_READLY;

    FQSpi_Reset(pQspi);

    return FQSPI_SUCCESS;
}

/**
 * @name: FQSpi_MemcpyToReg
 * @msg: Memory copy To Register
 * @in param {FQSpi_t} *pQspi
 * @in param {u8} *buf
 * @in param {u32} length
 * @return {ft_error_t}
 */
static ft_error_t FQSpi_MemcpyToReg(FQSpi_t *pQspi, FT_IN u8 *buf, u32 length)
{
    u32 val = 0;
    FQSpi_Config_t *pConfig = NULL;
    Ft_assertNonvoid(pQspi != NULL);
    Ft_assertNonvoid(pQspi->isReady == FT_COMPONENT_IS_READLY);
    pConfig = &pQspi->config;
    if (!buf || (length > 4))
    {
        return FQSPI_FAILURE;
    }

    if (1 == length)
    {
        val = buf[0];
    }
    else if (2 == length)
    {
        val = buf[1];
        val = (val << 8) + buf[0];
    }
    else if (3 == length)
    {
        val = buf[2];
        val = (val << 8) + buf[1];
        val = (val << 8) + buf[0];
    }
    else if (4 == length)
    {
        val = buf[3];
        val = (val << 8) + buf[2];
        val = (val << 8) + buf[1];
        val = (val << 8) + buf[0];
    }

    Ft_out32(pConfig->baseAddress + FT_REG_QSPI_LD_PORT_OFFSET, val);
    return FQSPI_SUCCESS;
}

/**
 * @name: FQSpi_MemcpyFromReg
 * @msg:  Memory copy from Register
 * @in param {FT_INFQSpi_t} *pQspi
 * @out param {u8} *buf
 * @in param {u32} length
 * @return {*}
 */
static ft_error_t FQSpi_MemcpyFromReg(FQSpi_t *pQspi, u8 *buf, u32 length)
{
    s32 i;
    u32 val = 0;
    FQSpi_Config_t *pConfig = NULL;
    Ft_assertNonvoid(pQspi != NULL);
    Ft_assertNonvoid(pQspi->isReady == FT_COMPONENT_IS_READLY);
    pConfig = &pQspi->config;

    for (i = 0; i < length; i++)
    {
        /* code */
        if (0 == i % 4)
        {
            val = Ft_in32(pConfig->baseAddress + FT_REG_QSPI_LD_PORT_OFFSET);
        }
        buf[i] = (u8)(val >> (i % 4) * 8) & 0xff;
    }

    return FQSPI_SUCCESS;
}

/**
 * @name: FQSpi_FlashRead
 * @msg:   Reads bytes data from flash addr to buf
 * @in param pQspi:
 * @in param cmd:  Read the instruction byte of the command
 * @in param addr: Read the data start character
 * @out param rxBuf: Read buffer
 * @in param length: need read length
 * @return {*}
 */
ft_error_t FQSpi_FlashRead(FQSpi_t *pQspi,
                           FT_IN u8 cmd,
                           FT_IN u32 addr,
                           FT_OUT u8 *rxBuf,
                           u32 length)
{
    FQSpi_Config_t *pConfig = NULL;
    FQSpi_RdCfgReg_t rdCfgReg;
    Ft_assertNonvoid(pQspi != NULL);
    Ft_assertNonvoid(pQspi->isReady == FT_COMPONENT_IS_READLY);
    pConfig = &pQspi->config;

    if ((NULL == rxBuf) || (0 == length))
    {
        return FQSPI_FAILURE;
    }

    rdCfgReg.data = 0;

    rdCfgReg.val.rdCmd = cmd;
    rdCfgReg.val.dBuffer = 1;
    rdCfgReg.val.rdAddrSel = pConfig->addrMode;
    rdCfgReg.val.rdSckSel = pConfig->clkDiv;
    rdCfgReg.val.rdTransfer = pConfig->transMode;
    Ft_out32(pConfig->baseAddress + FT_REG_QSPI_RD_CFG_OFFSET, rdCfgReg.data);

    memcpy(rxBuf, (char *)(addr), length);

    return FQSPI_SUCCESS;
}

/**
 * @name: FQSpi_FlashWrite
 * @msg:  Writes one page into flash,changing bits from 1 to 0
 * @in param pQspi:
 * @in param cmd:  write the instruction byte of the command
 * @in param addr: write the data start character
 * @in param txBuf: write buffer
 * @in param length: need write length
 * @return {*}
 */
ft_error_t FQSpi_FlashWrite(FQSpi_t *pQspi,
                            FT_IN u8 cmd,
                            FT_IN u32 addr,
                            FT_IN u8 *txBuf,
                            u32 length)
{

    FQSpi_Config_t *pConfig = NULL;
    FQSpi_WrCfgReg_t wrCfgReg;
    u32 index = 0;
    u32 val = 0;
    u32 *pu32Buf = NULL;
    Ft_assertNonvoid(pQspi != NULL);
    Ft_assertNonvoid(pQspi->isReady == FT_COMPONENT_IS_READLY);
    pConfig = &pQspi->config;

    if ((NULL == txBuf) || (0 == length))
    {
        return FQSPI_FAILURE;
    }

    pu32Buf = (u32 *)txBuf;

    wrCfgReg.data = 0;
    wrCfgReg.val.wrCmd = cmd;
    wrCfgReg.val.wrWait = 1;
    wrCfgReg.val.wrSckSel = pConfig->clkDiv;
    wrCfgReg.val.wrAddrsel = pConfig->addrMode;
    wrCfgReg.val.wrTransfer = pConfig->transMode;
    wrCfgReg.val.wrMode = 1;

    Ft_out32(pConfig->baseAddress + FT_REG_QSPI_WR_CFG_OFFSET, wrCfgReg.data);

    while (length)
    {
        if (length >= 4)
        {
            Ft_out32(addr + index, pu32Buf[index / 4]);
            length -= 4;
            index += 4;
        }
        else
        {
            if (1 == length)
            {
                val = txBuf[index] | 0xFFFFFF00;
            }
            else if (2 == length)
            {
                val = txBuf[index] | (txBuf[index + 1] << 8) | 0xFFFF0000;
            }
            else
            {
                val = txBuf[index] | (txBuf[index + 1] << 8) | (txBuf[index + 2] << 8) | 0xFF000000;
            }

            Ft_out32(addr + index, val);
            length = 0;
        }
    }

    Ft_out32(pConfig->baseAddress + FT_REG_QSPI_FLUSH_OFFSET, 1);
    return FQSPI_SUCCESS;
}

/**
 * @name: FQSpi_FlashRegSet
 * @msg:  Set registers of flash
 * @in param cmd:  Command byte
 * @in param writebuf: write buffer
 * @in param length: need write length
 * @return {*}
 */
ft_error_t FQSpi_FlashRegSet(FQSpi_t *pQspi,
                             FT_IN u8 cmd,
                             FT_IN u8 *writebuf,
                             u32 length)
{
    FQSpi_Config_t *pConfig = NULL;
    FQSpi_CmdPortReg_t cmdPortReg;
    Ft_assertNonvoid(pQspi != NULL);
    Ft_assertNonvoid(pQspi->isReady == FT_COMPONENT_IS_READLY);
    pConfig = &pQspi->config;

    cmdPortReg.data = 0;
    cmdPortReg.val.cmd = cmd;
    cmdPortReg.val.wait = 1;
    cmdPortReg.val.sckSel = pConfig->clkDiv;
    cmdPortReg.val.transfer = pConfig->transMode;
    cmdPortReg.val.cs = pConfig->channel;

    if (length == 0)
    {
        Ft_out32(pConfig->baseAddress + FT_REG_QSPI_CMD_PORT_OFFSET, cmdPortReg.data);
        Ft_out32(pConfig->baseAddress + FT_REG_QSPI_LD_PORT_OFFSET, 1);
    }
    else
    {
        cmdPortReg.val.dataTransfer = 1;
        cmdPortReg.val.rwMum = length;
        Ft_out32(pConfig->baseAddress + FT_REG_QSPI_CMD_PORT_OFFSET, cmdPortReg.data);
        FQSpi_MemcpyToReg(pQspi, writebuf, length);
    }

    return FQSPI_SUCCESS;
}

ft_error_t FQSpi_FlashRegSetWithaddr(FQSpi_t *pQspi,
                                     FT_IN u8 cmd,
                                     FT_IN u32 addr,
                                     FT_IN u8 *writebuf,
                                     u32 length)
{
    FQSpi_Config_t *pConfig = NULL;
    FQSpi_CmdPortReg_t cmdPortReg;
    Ft_assertNonvoid(pQspi != NULL);
    Ft_assertNonvoid(pQspi->isReady == FT_COMPONENT_IS_READLY);
    pConfig = &pQspi->config;

    cmdPortReg.data = 0;
    cmdPortReg.val.cmd = cmd;
    cmdPortReg.val.wait = 1;
    cmdPortReg.val.sckSel = pConfig->clkDiv;
    cmdPortReg.val.transfer = pConfig->transMode;
    cmdPortReg.val.cs = pConfig->channel;
    cmdPortReg.val.cmdAddr = 1;
    cmdPortReg.val.addrSel = pConfig->addrMode;

    Ft_out32(pConfig->baseAddress + FT_REG_QSPI_ADDR_PORT_OFFSET, addr);

    if (length == 0)
    {
        Ft_out32(pConfig->baseAddress + FT_REG_QSPI_CMD_PORT_OFFSET, cmdPortReg.data);
        Ft_out32(pConfig->baseAddress + FT_REG_QSPI_LD_PORT_OFFSET, 0);
    }
    else
    {
        cmdPortReg.val.dataTransfer = 1;
        cmdPortReg.val.rwMum = length;
        Ft_out32(pConfig->baseAddress + FT_REG_QSPI_CMD_PORT_OFFSET, cmdPortReg.data);
        FQSpi_MemcpyToReg(pQspi, writebuf, length);
    }

    return FQSPI_SUCCESS;
}

ft_error_t FQSpi_FlashRegGet(FQSpi_t *pQspi,
                             FT_IN u8 cmd,
                             u8 *readbuf,
                             u32 length)
{
    FQSpi_Config_t *pConfig = NULL;
    FQSpi_CmdPortReg_t cmdPortReg;
    Ft_assertNonvoid(pQspi != NULL);
    Ft_assertNonvoid(pQspi->isReady == FT_COMPONENT_IS_READLY);
    pConfig = &pQspi->config;

    cmdPortReg.data = 0;
    cmdPortReg.val.cmd = cmd;
    cmdPortReg.val.wait = 1;
    cmdPortReg.val.sckSel = pConfig->clkDiv;
    cmdPortReg.val.transfer = pConfig->transMode;
    cmdPortReg.val.cs = pConfig->channel;
    cmdPortReg.val.dataTransfer = 1;
    cmdPortReg.val.pBuffer = 1;

    Ft_out32(pConfig->baseAddress + FT_REG_QSPI_CMD_PORT_OFFSET, cmdPortReg.data);
    FQSpi_MemcpyFromReg(pQspi, readbuf, length);
    return FQSPI_SUCCESS;
}

ft_error_t FQSpi_FlashRegGetWithAddr(FQSpi_t *pQspi,
                                     FT_IN u8 cmd,
                                     FT_IN u32 addr,
                                     FT_IN u32 dummyCycle,
                                     u8 *readbuf,
                                     u32 length)
{
    FQSpi_Config_t *pConfig = NULL;
    FQSpi_CmdPortReg_t cmdPortReg;
    Ft_assertNonvoid(pQspi != NULL);
    Ft_assertNonvoid(pQspi->isReady == FT_COMPONENT_IS_READLY);
    pConfig = &pQspi->config;

    cmdPortReg.data = 0;
    cmdPortReg.val.cmd = cmd;
    cmdPortReg.val.wait = 1;
    cmdPortReg.val.sckSel = pConfig->clkDiv;
    cmdPortReg.val.transfer = pConfig->transMode;
    cmdPortReg.val.cs = pConfig->channel;
    cmdPortReg.val.dataTransfer = 1;
    cmdPortReg.val.pBuffer = 1;
    cmdPortReg.val.cmdAddr = 1;

    cmdPortReg.val.addrSel = pConfig->addrMode;
    cmdPortReg.val.latency = 1;
    cmdPortReg.val.dummy = dummyCycle - 1;

    Ft_out32(pConfig->baseAddress + FT_REG_QSPI_ADDR_PORT_OFFSET, addr);
    Ft_out32(pConfig->baseAddress + FT_REG_QSPI_CMD_PORT_OFFSET, cmdPortReg.data);
    FQSpi_MemcpyFromReg(pQspi, readbuf, length);
    return FQSPI_SUCCESS;
}

ft_error_t FQSpi_Write(FQSpi_t *pQspi, struct FQSpi_DataPack *pDataPack)
{
    FQSpi_Config_t *pConfig = NULL;
    FQSpi_WrCfgReg_t wrCfgReg;
    u32 length;
    u32 index = 0;
    u32 val = 0;
    const u32 *pu32Buf = NULL;
    Ft_assertNonvoid(pQspi != NULL);
    Ft_assertNonvoid(pQspi->isReady == FT_COMPONENT_IS_READLY);
    pConfig = &pQspi->config;

    if ((FQSPI_DATA_ADDRESS_3BYTE_MASK | FQSPI_DATA_ADDRESS_4BYTE_MASK) == (pDataPack->flags & (FQSPI_DATA_ADDRESS_3BYTE_MASK | FQSPI_DATA_ADDRESS_4BYTE_MASK)))
    {
        FTQSPI_DEBUG_E(" Two addresses are not allowed at the same time ");
        return FQSPI_FAILURE;
    }

    if (0 == (pDataPack->flags & (FQSPI_DATA_ADDRESS_3BYTE_MASK | FQSPI_DATA_ADDRESS_4BYTE_MASK)))
    {
        FTQSPI_DEBUG_E(" There is no address configuration ");
        return FQSPI_FAILURE;
    }

    if (NULL == pDataPack->txBuf)
    {
        FTQSPI_DEBUG_E("pDataPack->txBuf is null");
        return FQSPI_FAILURE;
    }

    pu32Buf = (const u32 *)pDataPack->txBuf;
    wrCfgReg.data = 0;

    if (FQSPI_DATA_ADDRESS_3BYTE_MASK == (pDataPack->flags & FQSPI_DATA_ADDRESS_3BYTE_MASK))
    {
        wrCfgReg.val.wrAddrsel = FT_QSPI_ADDR_SEL_3;
    }
    else if (FQSPI_DATA_ADDRESS_4BYTE_MASK == (pDataPack->flags & FQSPI_DATA_ADDRESS_4BYTE_MASK))
    {
        wrCfgReg.val.wrAddrsel = FT_QSPI_ADDR_SEL_4;
    }

    wrCfgReg.val.wrCmd = pDataPack->cmd;
    wrCfgReg.val.wrWait = 1;
    wrCfgReg.val.wrSckSel = pConfig->clkDiv;
    wrCfgReg.val.wrTransfer = pConfig->transMode;
    wrCfgReg.val.wrMode = 1;
    length = pDataPack->length;

    Ft_out32(pConfig->baseAddress + FT_REG_QSPI_WR_CFG_OFFSET, wrCfgReg.data);

    while (length)
    {
        if (length >= 4)
        {
            Ft_out32(pDataPack->addr + index, pu32Buf[index / 4]);
            length -= 4;
            index += 4;
        }
        else
        {
            if (1 == length)
            {
                val = pDataPack->txBuf[index] | 0xFFFFFF00;
            }
            else if (2 == length)
            {
                val = pDataPack->txBuf[index] | (pDataPack->txBuf[index + 1] << 8) | 0xFFFF0000;
            }
            else
            {
                val = pDataPack->txBuf[index] | (pDataPack->txBuf[index + 1] << 8) | (pDataPack->txBuf[index + 2] << 8) | 0xFF000000;
            }
            FTQSPI_DEBUG_I("val is 0x%x", val);
            Ft_out32(pDataPack->addr + index, val);
            length = 0;
        }
    }

    Ft_out32(pConfig->baseAddress + FT_REG_QSPI_FLUSH_OFFSET, 1);
    return FQSPI_SUCCESS;
}

ft_error_t FQSpi_Read(FQSpi_t *pQspi, struct FQSpi_DataPack *pDataPack)
{
    FQSpi_Config_t *pConfig = NULL;
    FQSpi_RdCfgReg_t rdCfgReg;
    Ft_assertNonvoid(pQspi != NULL);
    Ft_assertNonvoid(pQspi->isReady == FT_COMPONENT_IS_READLY);
    pConfig = &pQspi->config;

    if ((FQSPI_DATA_ADDRESS_3BYTE_MASK | FQSPI_DATA_ADDRESS_4BYTE_MASK) == (pDataPack->flags & (FQSPI_DATA_ADDRESS_3BYTE_MASK | FQSPI_DATA_ADDRESS_4BYTE_MASK)))
    {
        FTQSPI_DEBUG_E(" Two addresses are not allowed at the same time ");
        return FQSPI_FAILURE;
    }

    if (0 == (pDataPack->flags & (FQSPI_DATA_ADDRESS_3BYTE_MASK | FQSPI_DATA_ADDRESS_4BYTE_MASK)))
    {
        FTQSPI_DEBUG_E(" There is no address configuration ");
        return FQSPI_FAILURE;
    }

    if (NULL == pDataPack->rxBuf)
    {
        FTQSPI_DEBUG_E("pDataPack->rxBuf is null");
        return FQSPI_FAILURE;
    }

    rdCfgReg.data = 0;

    if (FQSPI_DATA_NEED_DUMMY_MASK == (pDataPack->flags & FQSPI_DATA_NEED_DUMMY_MASK))
    {
        rdCfgReg.val.rdLatency = 1;
        rdCfgReg.val.dummy = pDataPack->dummyCycle - 1;
    }

    if (FQSPI_DATA_ADDRESS_3BYTE_MASK == (pDataPack->flags & FQSPI_DATA_ADDRESS_3BYTE_MASK))
    {
        rdCfgReg.val.rdAddrSel = FT_QSPI_ADDR_SEL_3;
    }
    else if (FQSPI_DATA_ADDRESS_4BYTE_MASK == (pDataPack->flags & FQSPI_DATA_ADDRESS_4BYTE_MASK))
    {
        rdCfgReg.val.rdAddrSel = FT_QSPI_ADDR_SEL_4;
    }

    rdCfgReg.val.rdCmd = pDataPack->cmd;
    rdCfgReg.val.dBuffer = 1;
    rdCfgReg.val.rdSckSel = pConfig->clkDiv;
    rdCfgReg.val.rdTransfer = pConfig->transMode;

    Ft_out32(pConfig->baseAddress + FT_REG_QSPI_RD_CFG_OFFSET, rdCfgReg.data);

    memcpy(pDataPack->rxBuf, (char *)(pDataPack->addr), pDataPack->length);

    return FQSPI_SUCCESS;
}

ft_error_t
FQSpi_CmdOperation(FQSpi_t *pQspi, struct FQSpi_CmdPack *pCmdPack)
{
    FQSpi_Config_t *pConfig = NULL;
    FQSpi_CmdPortReg_t cmdPortReg;
    Ft_assertNonvoid(pQspi != NULL);
    Ft_assertNonvoid(pQspi->isReady == FT_COMPONENT_IS_READLY);
    pConfig = &pQspi->config;
    if ((FQSPI_CMD_ADDRESS_3BYTE_MASK | FQSPI_CMD_ADDRESS_4BYTE_MASK) == (pCmdPack->flags & (FQSPI_CMD_ADDRESS_3BYTE_MASK | FQSPI_CMD_ADDRESS_4BYTE_MASK)))
    {
        FTQSPI_DEBUG_E(" Two addresses are not allowed at the same time ");
        return FQSPI_FAILURE;
    }

    cmdPortReg.data = 0;
    cmdPortReg.val.cmd = pCmdPack->cmd;
    cmdPortReg.val.wait = 1;
    cmdPortReg.val.sckSel = pConfig->clkDiv;
    cmdPortReg.val.transfer = pConfig->transMode;
    cmdPortReg.val.cs = pConfig->channel;

    if (FQSPI_CMD_NEED_ADDR_MASK == (pCmdPack->flags & FQSPI_CMD_NEED_ADDR_MASK))
    {
        // FTQSPI_DEBUG_I(" send addr is 0x%x ", pCmdPack->addr);
        cmdPortReg.val.cmdAddr = 1;
        Ft_out32(pConfig->baseAddress + FT_REG_QSPI_ADDR_PORT_OFFSET, pCmdPack->addr);
    }

    if (FQSPI_CMD_NEED_DUMMY_MASK == (pCmdPack->flags & FQSPI_CMD_NEED_DUMMY_MASK))
    {
        cmdPortReg.val.latency = 1;
        cmdPortReg.val.dummy = pCmdPack->dummyCycle - 1;
    }

    if (FQSPI_CMD_ADDRESS_3BYTE_MASK == (pCmdPack->flags & FQSPI_CMD_ADDRESS_3BYTE_MASK))
    {
        cmdPortReg.val.addrSel = FT_QSPI_ADDR_SEL_3;
    }
    else if (FQSPI_CMD_ADDRESS_4BYTE_MASK == (pCmdPack->flags & FQSPI_CMD_ADDRESS_4BYTE_MASK))
    {
        cmdPortReg.val.addrSel = FT_QSPI_ADDR_SEL_4;
    }

    if (FQSPI_CMD_NEED_SET_MASK == (pCmdPack->flags & (FQSPI_CMD_NEED_SET_MASK)))
    {
        cmdPortReg.val.dataTransfer = 1;
        cmdPortReg.val.rwMum = pCmdPack->length;
        Ft_out32(pConfig->baseAddress + FT_REG_QSPI_CMD_PORT_OFFSET, cmdPortReg.data);
        FQSpi_MemcpyToReg(pQspi, pCmdPack->txBuf, pCmdPack->length);
    }
    else if (FQSPI_CMD_NEED_GET_MASK == (pCmdPack->flags & (FQSPI_CMD_NEED_GET_MASK)))
    {
        cmdPortReg.val.dataTransfer = 1;
        cmdPortReg.val.pBuffer = 1;
        Ft_out32(pConfig->baseAddress + FT_REG_QSPI_CMD_PORT_OFFSET, cmdPortReg.data);
        FQSpi_MemcpyFromReg(pQspi, pCmdPack->rxBuf, pCmdPack->length);
    }
    else
    {
        Ft_out32(pConfig->baseAddress + FT_REG_QSPI_CMD_PORT_OFFSET, cmdPortReg.data);

        if (FQSPI_CMD_NEED_ADDR_MASK == (pCmdPack->flags & FQSPI_CMD_NEED_ADDR_MASK))
        {
            Ft_out32(pConfig->baseAddress + FT_REG_QSPI_LD_PORT_OFFSET, 0);
        }
        else
        {
            Ft_out32(pConfig->baseAddress + FT_REG_QSPI_LD_PORT_OFFSET, 1);
        }
    }

    return FQSPI_SUCCESS;
}
