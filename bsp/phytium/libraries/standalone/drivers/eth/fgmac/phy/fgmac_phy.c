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
 * FilePath: fgmac_phy.c
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:53
 * Description:  This file implements functionalities to:
 * Detect the available PHYs connected to a MAC
 * Negotiate speed
 * Configure speed
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 *  1.0   huanghe    2021/07/13    first release
 */

/***************************** Include Files *********************************/

#include "fassert.h"
#include "fio.h"
#include "ferror_code.h"
#include "ftypes.h"
#include "fdebug.h"
#include "fparameters.h"
#include "fgmac_hw.h"
#include "fgmac_phy.h"
#include "fgmac.h"
#include "fsleep.h"
#include "sdkconfig.h"

#ifdef  CONFIG_FGMAC_PHY_AR803X
    #include "fgmac_ar803x.h"
#endif

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FGMAC_DEBUG_TAG "FGMAC-PHY"
#define FGMAC_ERROR(format, ...)   FT_DEBUG_PRINT_E(FGMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGMAC_WARN(format, ...)    FT_DEBUG_PRINT_W(FGMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGMAC_INFO(format, ...)    FT_DEBUG_PRINT_I(FGMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGMAC_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FGMAC_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/


/************************** Variable Definitions *****************************/

/*****************************************************************************/

/* 此文件主要为了完成用户对外接口，用户可以使用这些接口直接开始工作 */

/* - 包括用户API的定义和实现
   - 同时包含必要的OPTION方法，方便用户进行配置
   - 如果驱动可以直接进行I/O操作，在此源文件下可以将API 进行实现 */

/* - 包括用户API的定义和实现
   - 同时包含必要的OPTION方法，方便用户进行配置
   - 如果驱动可以直接进行I/O操作，在此源文件下可以将API 进行实现 */

/**
 * @name: FGmacWaitPhyAutoNegotiationEnd
 * @msg: wait fgmac phy auto negotiation complete
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @param {u32} phy_address, phy address connect to fgmac
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
static FError FGmacWaitPhyAutoNegotiationEnd(FGmac *instance_p, u32 phy_address)
{
    u16 reg_val;
    FError ret = FGMAC_SUCCESS;
    int timeout = FGMAC_RETRY_TIMES;
    do
    {
        reg_val = 0;
        ret = FGmacReadPhyReg(instance_p, phy_address, FGMAC_PHY_MII_STATUS_REG, &reg_val);
        if (FGMAC_SUCCESS != ret)
        {
            break;
        }
        fsleep_millisec(20);
    }
    while ((FGMAC_PHY_MII_SR_AUTO_NEGOT_COMPLETE != (FGMAC_PHY_MII_SR_AUTO_NEGOT_COMPLETE & reg_val)) &&
           (0 < --timeout));

    if (FGMAC_SUCCESS != ret)
    {
        return ret;
    }

    if (0 >= timeout)
    {
        FGMAC_ERROR("Auto negotiation timeout, reg_val: %#x", reg_val);
        ret = FGmacReadPhyReg(instance_p, phy_address, FGMAC_PHY_MII_CTRL_REG, &reg_val);
        FGMAC_ERROR("Auto negotiation timeout, FGMAC_PHY_MII_CTRL_REG reg_val: %#x", reg_val);
        ret = FGMAC_ERR_TIMEOUT;
    }

    return ret;
}

/**
 * @name: FGmacPhyAutoNegotiation
 * @msg: fgmac phy auto negotiation configuration
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @param {u32} phy_address, phy address connect to fgmac
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
static FError FGmacPhyAutoNegotiation(FGmac *instance_p, u32 phy_address)
{
    FASSERT(instance_p);
    u16 reg_val;
    FError ret = FGMAC_SUCCESS;
    int timeout = FGMAC_RETRY_TIMES;
    /* check link state */
    do
    {
        reg_val = 0;
        ret = FGmacReadPhyReg(instance_p, phy_address, FGMAC_PHY_MII_STATUS_REG, &reg_val);
        if (FGMAC_SUCCESS != ret)
        {
            break;
        }
        fsleep_millisec(20);

    }
    while (!(reg_val & FGMAC_PHY_MII_SR_LSTATUS) && (0 <= --timeout));

    if (0 >= timeout)
    {
        FGMAC_ERROR("Timeout when wait phy auto negotiation.");
        return FGMAC_ERR_TIMEOUT;
    }

    if (FGMAC_SUCCESS != ret)
    {
        return ret;
    }

    ret = FGmacReadPhyReg(instance_p, phy_address, FGMAC_PHY_MII_CTRL_REG, &reg_val);
    if (FGMAC_SUCCESS != ret)
    {
        FGMAC_ERROR("Auto negotiation failed.");
        return ret;
    }

    reg_val |= FGMAC_PHY_MII_CR_AUTO_NEGOT;

    ret = FGmacWritePhyReg(instance_p, phy_address, FGMAC_PHY_MII_CTRL_REG, reg_val);
    if (FGMAC_SUCCESS != ret)
    {
        FGMAC_ERROR("Auto negotiation failed.");
        return ret;
    }

    ret = FGmacWaitPhyAutoNegotiationEnd(instance_p, phy_address);
    if (FGMAC_SUCCESS != ret)
    {
        return ret;
    }

    return ret;
}

/**
 * @name: FGmacPhyNoneNegotiation
 * @msg: fgmac phy not negotiation configuration
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @param {u32} phy_address, phy address connect to fgmac
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
static FError FGmacPhyNoneNegotiation(FGmac *instance_p, u32 phy_address)
{
    FASSERT(instance_p);
    u16 control_reg = 0;
    FError ret = FGMAC_SUCCESS;

    /* read phy control register */
    ret  = FGmacReadPhyReg(instance_p, phy_address, FGMAC_PHY_MII_CTRL_REG, &control_reg);
    if (FGMAC_SUCCESS != ret)
    {
        return ret;
    }

    /* 设置半双工模式 */
    if (FGMAC_PHY_MODE_FULLDUPLEX == instance_p->config.duplex_mode)
    {
        control_reg |= FGMAC_PHY_MII_CR_DUPLEX_MODE;
    }
    else
    {
        control_reg &= ~(FGMAC_PHY_MII_CR_DUPLEX_MODE);
    }

    /* 设置速度bit6|bit13, 10b-1000M, 01b-100M, 00b-10M */
    switch (instance_p->config.speed)
    {
        case FGMAC_PHY_SPEED_1000:
            control_reg |= FGMAC_PHY_MII_CR_SPEED_SEL_MSB;
            control_reg &= ~(FGMAC_PHY_MII_CR_SPEED_SEL_LSB);
            break;
        case FGMAC_PHY_SPEED_100:
            control_reg &= ~(FGMAC_PHY_MII_CR_SPEED_SEL_MSB);
            control_reg |= FGMAC_PHY_MII_CR_SPEED_SEL_LSB;
            break;
        case FGMAC_PHY_SPEED_10:
            control_reg &= ~(FGMAC_PHY_MII_CR_SPEED_SEL_MSB);
            control_reg &= ~(FGMAC_PHY_MII_CR_SPEED_SEL_LSB);
            break;
        default:
            FASSERT(0);
            break;
    }

    /* disable auto-negotiation */
    control_reg &= ~(FGMAC_PHY_MII_CR_AUTO_NEGOT);
    control_reg &= ~(FGMAC_PHY_MII_CR_RESTART_AUTO_NEGO);

    /* write phy control register */
    ret = FGmacWritePhyReg(instance_p, phy_address, FGMAC_PHY_MII_CTRL_REG, control_reg);
    if (FGMAC_SUCCESS != ret)
    {
        FGMAC_ERROR("Disable auto negotiation failed.");
        return ret;
    }

    return ret;
}

/**
 * @name: FGmacWritePhyReg
 * @msg: write phy register value
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @param {u32} phy_address, phy address connect to fgmac
 * @param {u16} phy_reg, phy register offset to write
 * @param {u16} phy_reg_val, value write to phy register
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
FError FGmacWritePhyReg(FGmac *instance_p, u32 phy_address, u16 phy_reg, u16 phy_reg_val)
{
    FASSERT(instance_p);
    u32 cmd_reg_val;
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FGMAC_SUCCESS;

    cmd_reg_val  = FGMAC_MII_ADDR_CR(instance_p->config.mdc_clk_hz);
    cmd_reg_val |= FGMAC_MII_ADDR_PA(phy_address);
    cmd_reg_val |= FGMAC_MII_ADDR_GR(phy_reg);
    cmd_reg_val |= FGMAC_MII_ADDR_GW;
    cmd_reg_val |= FGMAC_MII_ADDR_GB;

    FGMAC_WRITE_REG32(base_addr, FGMAC_GMII_DATA_OFFSET, phy_reg_val);
    FGMAC_WRITE_REG32(base_addr, FGMAC_GMII_ADDR_OFFSET, cmd_reg_val);

    ret = FGmacPhyWaitBusBusy(base_addr, FGMAC_RETRY_TIMES);
    return ret;
}

/**
 * @name: FGmacReadPhyReg
 * @msg: read phy register value
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @param {u32} phy_address, phy address connect to fgmac
 * @param {u16} phy_reg, phy register offset to read
 * @param {u16} *phy_reg_val_p, phy register value pointer
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
FError FGmacReadPhyReg(FGmac *instance_p, u32 phy_address, u16 phy_reg, u16 *phy_reg_val_p)
{
    FASSERT(instance_p && phy_reg_val_p);
    u32 cmd_reg_val;
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FGMAC_SUCCESS;

    cmd_reg_val = FGMAC_MII_ADDR_CR(instance_p->config.mdc_clk_hz);
    cmd_reg_val |= FGMAC_MII_ADDR_PA(phy_address);
    cmd_reg_val |= FGMAC_MII_ADDR_GR(phy_reg);
    cmd_reg_val &= ~FGMAC_MII_ADDR_GW;
    cmd_reg_val |= FGMAC_MII_ADDR_GB;

    ret = FGmacPhyWaitBusBusy(base_addr, FGMAC_RETRY_TIMES);
    if (FGMAC_SUCCESS != ret)
    {
        return ret;
    }

    FGMAC_WRITE_REG32(base_addr, FGMAC_GMII_ADDR_OFFSET, cmd_reg_val);

    ret = FGmacPhyWaitBusBusy(base_addr, FGMAC_RETRY_TIMES);
    if (FGMAC_SUCCESS != ret)
    {
        return ret;
    }

    *phy_reg_val_p = FGMAC_MII_DATA_GD_MASK & FGMAC_READ_REG32(base_addr, FGMAC_GMII_DATA_OFFSET);
    return ret;
}

/**
 * @name: FGmacPhyDetect
 * @msg: detect fgmac phy, and get phy addr
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
FError FGmacPhyDetect(FGmac *instance_p)
{
    u32 phy_addr = 0;
    u16 phy_reg = 0, phy_id1_reg, phy_id2_reg;
    FError ret = FGMAC_SUCCESS;
    u32 invalid_count = 0;

    for (phy_addr = 0; phy_addr < FGMAC_PHY_MAX_NUM; phy_addr++)
    {
        ret = FGmacReadPhyReg(instance_p, phy_addr, FGMAC_PHY_MII_STATUS_REG, &phy_reg);
        if (ret != FGMAC_SUCCESS)
        {
            FGMAC_ERROR("%s, phy operation is busy.", __func__);
            return ret;
        }

        if (phy_reg != 0xffff)
        {
            ret = FGmacReadPhyReg(instance_p, phy_addr, FGMAC_PHY_MII_PHYSID1_REG, &phy_id1_reg);
            ret |= FGmacReadPhyReg(instance_p, phy_addr, FGMAC_PHY_MII_PHYSID2_REG, &phy_id2_reg);

            if ((ret == FGMAC_SUCCESS) && (phy_id1_reg != 0xffff) && (phy_id2_reg != 0xffff))
            {
                /* assign the max valid phy address to instance_p->phy_addr */
                instance_p->phy_addr = phy_addr;
                instance_p->phy_valid_mask |= (1 << phy_addr);
                instance_p->phy_id1 = phy_id1_reg;

                FGMAC_INFO("Phy_addr: [%d], phy_valid_mask: 0x%x, phy id: [0x%08x][0x%08x], phy_reg:0x%x",
                           phy_addr, instance_p->phy_valid_mask, phy_id1_reg, phy_id2_reg, phy_reg);

                return ret;
            }
        }
        else
        {
            invalid_count++;
        }
    }

    if (invalid_count == FGMAC_PHY_MAX_NUM)
    {
        FGMAC_ERROR("Phy detect failed, phy address is not found!");
        return FGMAC_ERR_PHY_IS_NOT_FOUND;
    }

    return FGMAC_SUCCESS;
}

/**
 * @name: FGmacPhyReset
 * @msg: detect fgmac phy, and get phy addr
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @param {u32} phy_address, phy address connect to fgmac
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
FError FGmacPhyReset(FGmac *instance_p, u32 phy_address)
{
    FError ret = FGMAC_ERR_PHY_NOT_SUPPORT;
    uintptr base_addr = instance_p->config.base_addr;
    ret = FGmacWritePhyReg(instance_p, phy_address, FGMAC_PHY_MII_CTRL_REG, FGMAC_PHY_MII_CR_RESET);
    if (FGMAC_SUCCESS != ret)
    {
        FGMAC_ERROR("Reset phy failed.");
        return ret;
    }
    return FGMAC_SUCCESS;
}

/**
 * @name: FGmacGetPhySpecialStatus
 * @msg: read phy special status register to get speed and duplex mode
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @param {u32} phy_address, phy address connect to fgmac
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
static FError FGmacGetPhySpecialStatus(FGmac *instance_p, u32 phy_address)
{
    u16 phy_special_status = 0;
    u32 ret = FGMAC_SUCCESS;

    ret  = FGmacReadPhyReg(instance_p, phy_address, FGMAC_PHY_MII_PHY_SPECIAL_REG, &phy_special_status);
    if (FGMAC_SUCCESS != ret)
    {
        return ret;
    }

    switch (phy_special_status & FGMAC_PHY_SPECIFIC_STATUS_SPEED_MASK)
    {
        case FGMAC_PHY_SPECIFIC_STATUS_SPEED_1000M:
            instance_p->config.speed = FGMAC_PHY_SPEED_1000;
            break;
        case FGMAC_PHY_SPECIFIC_STATUS_SPEED_100M:
            instance_p->config.speed = FGMAC_PHY_SPEED_100;
            break;
        case FGMAC_PHY_SPECIFIC_STATUS_SPEED_10M:
            instance_p->config.speed = FGMAC_PHY_SPEED_10;
            break;
        default:
            break;
    }

    if (phy_special_status & FGMAC_PHY_SPECIFIC_STATUS_DUPLEX_MASK)
    {
        instance_p->config.duplex_mode = FGMAC_PHY_MODE_FULLDUPLEX;
    }
    else
    {
        instance_p->config.duplex_mode = FGMAC_PHY_MODE_HALFDUPLEX;
    }

    return ret;
}

/**
 * @name: FGmacPhyCfgInitialize
 * @msg: fgmac phy configuration
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
FError FGmacPhyCfgInitialize(FGmac *instance_p)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FGMAC_SUCCESS;
    u32 phy_addr;

    /* detect phy address, and assigned the minimum valid address to phy_addr */
    ret = FGmacPhyDetect(instance_p);
    if (FGMAC_SUCCESS != ret)
    {
        FGMAC_ERROR("Phy detect failed!");
        return ret;
    }

    for (phy_addr = 0; phy_addr <= instance_p->phy_addr; phy_addr++)
    {
        /* 计算出当前位置 */
        if (instance_p->phy_valid_mask & (1 << phy_addr))
        {
            /* set phy power down and set phy Normal operation  */
            FGmacPhyReset(instance_p, phy_addr);

            /* auto negotiation */
            if (instance_p->config.en_auto_negtiation)
            {
                ret = FGmacPhyAutoNegotiation(instance_p, phy_addr);
                if (FGMAC_SUCCESS != ret)
                {
                    FGMAC_ERROR("Auto negotiation phy failed.");
                    return ret;
                }
            }
            else
            {
                /* if gmac is disable auto negotiation, we need set speed */
                ret = FGmacPhyNoneNegotiation(instance_p, phy_addr);
                if (FGMAC_SUCCESS != ret)
                {
                    FGMAC_ERROR("Negotiation phy failed.");
                    return ret;
                }
            }

            /* read phy special status register to get speed and duplex mode */
            ret = FGmacGetPhySpecialStatus(instance_p, phy_addr);
            if (FGMAC_SUCCESS != ret)
            {
                FGMAC_ERROR("Get phy special status failed.");
                return ret;
            }

            FGMAC_DEBUG("instance_p->config.speed: %d", instance_p->config.speed);
            FGMAC_DEBUG("instance_p->config.duplex_mode: 0x%x", instance_p->config.duplex_mode);
            /* update mac controller speed setting */
            FGmacControllerSpeedConfig(instance_p, instance_p->config.speed);

            /* update mac controller duplex mode setting */
            FGmacControllerDuplexConfig(instance_p, instance_p->config.duplex_mode);
        }
    }
    return ret;
}

FError FGmacPhyCfgDeInitialize(FGmac *instance_p)
{
    FASSERT(instance_p);
    uintptr base_addr = instance_p->config.base_addr;
    FError ret = FGMAC_SUCCESS;
    u32 phy_addr;

    for (phy_addr = 0; phy_addr <= instance_p->phy_addr; phy_addr++)
    {
        /* 计算出当前位置 */
        if (instance_p->phy_valid_mask & (1 << phy_addr))
        {
            /* set phy power down and set phy Normal operation  */
            FGmacPhyReset(instance_p, phy_addr);
        }
    }
    return ret;
}

/**
 * @name: FGmacPhyAwaken
 * @msg: fgmac phy awaken
 * @param {FGmac} *instance_p, instance of FGmac controller
 * @return err code information, FGMAC_SUCCESS indicates success，others indicates failed
 */
FError  FGmacPhyAwaken(FGmac *instance_p)
{

    FError ret = FGMAC_SUCCESS;

#ifdef  CONFIG_FGMAC_PHY_AR803X
    ret = FGmacPhyDetect(instance_p);
    if (FGMAC_SUCCESS != ret)
    {
        FGMAC_ERROR("Phy detect failed!");
        return ret;
    }

    u16 phy_id1;
    phy_id1 = instance_p->phy_id1;

    if (phy_id1 == FGMAC_AR803X_PHY_ID1)
    {

        ret = FGmacAr803xDisableHibernate(instance_p);

    }
#endif
    return ret;
}
