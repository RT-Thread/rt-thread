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
 * FilePath: fqspi.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-03-28 09:00:41
 * Description:  This files is for the qspi specific functions implementations
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/3/29  first release
 * 1.1   wangxiaodong  2022/9/9   improve functions
 * 1.2   zhangyan      2022/12/7  improve functions
 */

#include <string.h>
#include "fkernel.h"
#include "fassert.h"
#include "fqspi.h"
#include "fqspi_hw.h"
#include "fsleep.h"
#include "fqspi_flash.h"

#define FQSPI_DEBUG_TAG "FQSPI"
#define FQSPI_ERROR(format, ...)    FT_DEBUG_PRINT_E(FQSPI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FQSPI_WARN(format, ...)     FT_DEBUG_PRINT_W(FQSPI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FQSPI_INFO(format, ...)     FT_DEBUG_PRINT_I(FQSPI_DEBUG_TAG, format, ##__VA_ARGS__)
#define FQSPI_DEBUG(format, ...)    FT_DEBUG_PRINT_D(FQSPI_DEBUG_TAG, format, ##__VA_ARGS__)


/**
 * @name: FQspiCfgInitialize
 * @msg:  Initializes a specific instance such that it is ready to be used.
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {FQspiConfig} *input_config_p, Configuration parameters of FQSPI
 * @return err code information, FQSPI_SUCCESS indicates success，others indicates failed
 */
FError FQspiCfgInitialize(FQspiCtrl *pctrl, const FQspiConfig *input_config_p)
{
    FASSERT(pctrl && input_config_p);

    FError ret = FQSPI_SUCCESS;
    /*
    * If the device is started, disallow the initialize and return a Status
    * indicating it is started.  This allows the user to de-initialize the device
    * and reinitialize, but prevents a user from inadvertently
    * initializing.
    */
    if (FT_COMPONENT_IS_READY == pctrl->is_ready)
    {
        FQSPI_WARN("Device is already initialized!!!");
    }

    /*Set default values and configuration data */
    FQspiDeInitialize(pctrl);

    pctrl->config = *input_config_p;

    pctrl->is_ready = FT_COMPONENT_IS_READY;

    return ret;
}

/**
 * @name: FQspiDeInitialize
 * @msg: DeInitialization function for the device instance
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @return {*}
 */
void FQspiDeInitialize(FQspiCtrl *pctrl)
{
    FASSERT(pctrl);

    pctrl->is_ready = 0;
    memset(pctrl, 0, sizeof(*pctrl));

    return;
}

/**
 * @name: FQspiSetCapacityAndNum
 * @msg:  Initializes the capacity and number of flash connect to specific instance.
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @return void
 */
void FQspiSetCapacityAndNum(FQspiCtrl *pctrl)
{
    FASSERT(pctrl);
    u32 reg_val = 0;
    FQspiConfig *config_p = &pctrl->config;
    uintptr base_addr = pctrl->config.base_addr;

    switch (config_p->capacity)
    {
        case FQSPI_FLASH_CAP_4MB:
            pctrl->flash_size = SZ_4M;
            break;
        case FQSPI_FLASH_CAP_8MB:
            pctrl->flash_size = SZ_8M;
            break;
        case FQSPI_FLASH_CAP_16MB:
            pctrl->flash_size = SZ_16M;
            break;
        case FQSPI_FLASH_CAP_32MB:
            pctrl->flash_size = SZ_32M;
            break;
        case FQSPI_FLASH_CAP_64MB:
            pctrl->flash_size = SZ_64M;
            break;
        case FQSPI_FLASH_CAP_128MB:
            pctrl->flash_size = SZ_128M;
            break;
        case FQSPI_FLASH_CAP_256MB:
            pctrl->flash_size = SZ_256M;
            break;
        default:
            pctrl->flash_size = SZ_4M;
            break;
    }

    /* Write flash capacity and numbers information to qspi Capacity register */
    reg_val = (FQSPI_CAP_FLASH_NUM_MASK & FQSPI_CAP_FLASH_NUM(config_p->dev_num)) |
              (FQSPI_CAP_FLASH_CAP_MASK & FQSPI_CAP_FLASH_CAP(config_p->capacity));

    /*write value to flash capacity register 0x00 */
    FQSPI_WRITE_REG32(base_addr, FQSPI_REG_CAP_OFFSET, reg_val);
    FQSPI_INFO("The flash chip size is %ld bytes.\n",  pctrl->flash_size);
}


/**
 * @name: FQspiRdCfgConfig
 * @msg:  config read config register
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @return err code information, FQSPI_SUCCESS indicates success，others indicates failed
 */
FError FQspiRdCfgConfig(FQspiCtrl *pctrl)
{
    FASSERT(pctrl);
    FError ret = FQSPI_SUCCESS;
    u32 cmd_reg = 0;
    uintptr base_addr = pctrl->config.base_addr;

    FQspiRdCfgDef rd_config = pctrl->rd_cfg;

    cmd_reg |= FQSPI_RD_CFG_CMD(rd_config.rd_cmd);
    cmd_reg |= FQSPI_RD_CFG_THROUGH(rd_config.rd_through);
    cmd_reg |= FQSPI_RD_CFG_TRANSFER(rd_config.rd_transfer);
    cmd_reg |= FQSPI_RD_CFG_ADDR_SEL(rd_config.rd_addr_sel);
    cmd_reg |= FQSPI_RD_CFG_LATENCY(rd_config.rd_latency);
    cmd_reg |= FQSPI_RD_CFG_MODE_BYTE(rd_config.mode_byte);

    if ((rd_config.mode_byte) || (rd_config.cmd_sign == 0))
    {
        cmd_reg |= FQSPI_RD_CFG_CMD_SIGN(rd_config.cmd_sign);
    }
    else
    {
        FQSPI_ERROR("rd_cfg mode_byte disable !!!");
        return FQSPI_INVAL_PARAM;
    }

    if ((rd_config.rd_latency == FQSPI_CMD_LATENCY_ENABLE) || (rd_config.dummy == 0))
    {
        rd_config.dummy = rd_config.dummy ? rd_config.dummy : 1;
        cmd_reg |= FQSPI_RD_CFG_DUMMY(rd_config.dummy);
    }
    else
    {
        FQSPI_ERROR("rd_cfg latency disable !!!");
        return FQSPI_INVAL_PARAM;
    }

    cmd_reg |= FQSPI_RD_CFG_D_BUFFER(rd_config.d_buffer);
    cmd_reg |= FQSPI_RD_CFG_SCK_SEL(rd_config.rd_sck_sel);

    FQSPI_WRITE_REG32(base_addr, FQSPI_REG_RD_CFG_OFFSET, cmd_reg);
    return ret;
}

/**
 * @name: FQspiWrCfgConfig
 * @msg:  config write config register
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @return err code information, FQSPI_SUCCESS indicates success，others indicates failed
 */
FError FQspiWrCfgConfig(FQspiCtrl *pctrl)
{
    FASSERT(pctrl);
    FError ret = FQSPI_SUCCESS;
    u32 cmd_reg = 0;
    uintptr base_addr = pctrl->config.base_addr;

    FQspiWrCfgDef wr_config = pctrl->wr_cfg;

    cmd_reg |= FQSPI_WR_CFG_CMD(wr_config.wr_cmd);
    cmd_reg |= FQSPI_WR_CFG_WAIT(wr_config.wr_wait);
    cmd_reg |= FQSPI_WR_CFG_THROUGH(wr_config.wr_through);
    cmd_reg |= FQSPI_WR_CFG_TRANSFER(wr_config.wr_transfer);
    cmd_reg |= FQSPI_WR_CFG_ADDRSEL(wr_config.wr_addr_sel);
    cmd_reg |= FQSPI_WR_CFG_MODE(wr_config.wr_mode);
    cmd_reg |= FQSPI_WR_CFG_SCK_SEL(wr_config.wr_sck_sel);

    FQSPI_WRITE_REG32(base_addr, FQSPI_REG_WR_CFG_OFFSET, cmd_reg);

    return ret;
}


/**
 * @name: FQspiCommandPortConfig
 * @msg:  config command port register
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @return err code information, FQSPI_SUCCESS indicates success，others indicates failed
 */
FError FQspiCommandPortConfig(FQspiCtrl *pctrl)
{
    FASSERT(pctrl);
    FError ret = FQSPI_SUCCESS;
    u32 cmd_reg = 0;
    uintptr base_addr = pctrl->config.base_addr;

    FQspiCommandPortDef cmd_port_config = pctrl->cmd_def;

    cmd_reg |= FQSPI_CMD_PORT_CMD_MASK & FQSPI_CMD_PORT_CMD(cmd_port_config.cmd);

    cmd_reg |= FQSPI_CMD_PORT_WAIT(cmd_port_config.wait);

    cmd_reg |= FQSPI_CMD_PORT_THROUGH(cmd_port_config.through);

    cmd_reg |= FQSPI_CMD_PORT_CS_MASK & FQSPI_CMD_PORT_CS(cmd_port_config.cs);

    cmd_reg |= FQSPI_CMD_PORT_TRANSFER(cmd_port_config.transfer);

    cmd_reg |= FQSPI_CMD_PORT_CMD_ADDR(cmd_port_config.cmd_addr);

    cmd_reg |= FQSPI_CMD_PORT_LATENCY(cmd_port_config.latency);

    cmd_reg |= FQSPI_CMD_PORT_DATA_TRANS(cmd_port_config.data_transfer);

    cmd_reg |= FQSPI_CMD_PORT_ADDR_SEL(cmd_port_config.addr_sel);

    if ((cmd_port_config.latency == FQSPI_CMD_LATENCY_ENABLE) || (cmd_port_config.dummy == 0))
    {
        cmd_port_config.dummy = cmd_port_config.dummy ? cmd_port_config.dummy : 1;
        cmd_reg |= FQSPI_CMD_PORT_DUMMY(cmd_port_config.dummy);
    }
    else
    {
        FQSPI_ERROR("cmd_port latency disable !!!");
        return FQSPI_INVAL_PARAM;
    }

    cmd_reg |= FQSPI_CMD_PORT_P_BUFFER(cmd_port_config.p_buffer);

    /* read data num */
    cmd_reg |= FQSPI_CMD_PORT_RW_NUM_MASK & FQSPI_CMD_PORT_RW_NUM(cmd_port_config.rw_num);

    cmd_reg |= FQSPI_CMD_PORT_CLK_SEL_MASK & FQSPI_CMD_PORT_CLK_SEL(cmd_port_config.sck_sel);

    FQSPI_WRITE_REG32(base_addr, FQSPI_REG_CMD_PORT_OFFSET, cmd_reg);

    return ret;
}


/**
 * @name: FQspiChannelSet
 * @msg:  config qspi cs num
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {u32} channel, cs number
 * @return
 */
void FQspiChannelSet(FQspiCtrl *pctrl, u32 channel)
{
    FASSERT(pctrl);
    FASSERT(channel < FQSPI_CS_NUM);
    pctrl->config.channel = channel;
}

/**
 * @name: FQspiCsTimingSet
 * @msg:  config qspi cs timing
 * @param {FQspiCtrl} *pctrl, instance of FQSPI controller
 * @param {FQspiCsTimingCfgDef} cs_timing_cfg, cs timing
 * @return err code information, FQSPI_SUCCESS indicates success，others indicates failed
 */
void FQspiCsTimingSet(FQspiCtrl *pctrl, FQspiCsTimingCfgDef *cs_timing_cfg)
{
    FASSERT(pctrl);
    u32 cmd_reg = 0;
    uintptr base_addr = pctrl->config.base_addr;

    cmd_reg |= FQSPI_FUN_SET_CS_HOLD(cs_timing_cfg->cs_hold);

    cmd_reg |= FQSPI_FUN_SET_CS_SETUP(cs_timing_cfg->cs_setup);

    cmd_reg |= FQSPI_FUN_SET_CS_DELAY(cs_timing_cfg->cs_delay);

    FQSPI_WRITE_REG32(base_addr, FQSPI_REG_CS_TIMING_SET_OFFSET, cmd_reg);

}


