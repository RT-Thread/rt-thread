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
 * FilePath: fxmac_phy.c
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for phy types.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
 */

#include "fxmac.h"
#include "eth_ieee_reg.h"
#include "fdebug.h"
#include "sdkconfig.h"

#if defined(CONFIG_FXMAC_PHY_YT)
    #include "phy_yt.h"
#endif


#define FXMAC_DEBUG_TAG "FXMAC_PHY"
#define FXMAC_ERROR(format, ...) FT_DEBUG_PRINT_E(FXMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FXMAC_INFO(format, ...) FT_DEBUG_PRINT_I(FXMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FXMAC_DEBUG(format, ...) FT_DEBUG_PRINT_D(FXMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FXMAC_WARN(format, ...) FT_DEBUG_PRINT_W(FXMAC_DEBUG_TAG, format, ##__VA_ARGS__)

static FXmac *instance_b;
static u32 phy_addr_b;

static FError FXmacDetect(FXmac *instance_p, u32 *phy_addr_p)
{
    u32 phy_addr = 0, i = 0, index;
    u16 phy_reg = 0, phy_id1_reg, phy_id2_reg;
    FError ret;
    instance_b = instance_p;

    for (phy_addr = 0; phy_addr < FXMAC_PHY_MAX_NUM; phy_addr++)
    {
        ret = FXmacPhyRead(instance_p, phy_addr, PHY_STATUS_REG_OFFSET, &phy_reg);
        if (ret != FT_SUCCESS)
        {
            FXMAC_ERROR("Phy operation is busy.");
            return ret;
        }
        FXMAC_INFO("Phy status reg is %x", phy_reg);
        if (phy_reg != 0xffff)
        {
            ret = FXmacPhyRead(instance_p, phy_addr, PHY_IDENTIFIER_1_REG, &phy_id1_reg);
            ret |= FXmacPhyRead(instance_p, phy_addr, PHY_IDENTIFIER_2_REG, &phy_id2_reg);
            FXMAC_INFO("Phy id1 reg is 0x%x", phy_id1_reg);
            FXMAC_INFO("Phy id2 reg is 0x%x", phy_id2_reg);
            if ((ret == FT_SUCCESS) && (phy_id2_reg != 0) && (phy_id1_reg != 0xffff) && (phy_id1_reg != 0xffff))
            {
                *phy_addr_p = phy_addr;
                phy_addr_b = phy_addr;
                FXMAC_INFO("Phy addr is 0x%x", phy_addr);
                return FT_SUCCESS;
            }
        }
    }

    return FT_SUCCESS;
}

static FError FXmacGetIeeePhySpeed(FXmac *instance_p, u32 phy_addr)
{
    u16 temp, temp2;
    u16 control;
    u16 status;
    u16 partner_capabilities;
    u32 negotitation_timeout_cnt = 0;
    FError ret;
    volatile s32 wait;

    FXMAC_INFO("Start phy auto negotiation.");

    ret = FXmacPhyRead(instance_p, phy_addr, PHY_CONTROL_REG_OFFSET, &control);
    if (ret != FT_SUCCESS)
    {
        FXMAC_ERROR("%s:%d,read PHY_CONTROL_REG_OFFSET is error", __func__, __LINE__);
        return ret;
    }
    control |= PHY_CONTROL_RESET_MASK;

    ret = FXmacPhyWrite(instance_p, phy_addr, PHY_CONTROL_REG_OFFSET, control);
    if (ret != FT_SUCCESS)
    {
        FXMAC_ERROR("%s:%d,write PHY_CONTROL_REG_OFFSET is error", __func__, __LINE__);
        return ret;
    }
    for (wait = 0; wait < 100000; wait++)
        ;
    FXMAC_INFO(" Phy reset end.");
    ret = FXmacPhyRead(instance_p, phy_addr, PHY_CONTROL_REG_OFFSET, &control);
    if (ret != FT_SUCCESS)
    {
        FXMAC_ERROR("%s:%d,read PHY_CONTROL_REG_OFFSET is error", __func__, __LINE__);
        return ret;
    }

    control |= PHY_CONTROL_AUTONEGOTIATE_ENABLE;
    control |= PHY_CONTROL_AUTONEGOTIATE_RESTART;
    ret = FXmacPhyWrite(instance_p, phy_addr, PHY_CONTROL_REG_OFFSET, control);
    if (ret != FT_SUCCESS)
    {
        FXMAC_ERROR("%s:%d,write PHY_CONTROL_REG_OFFSET is error", __func__, __LINE__);
        return ret;
    }

    FXMAC_INFO("Waiting for phy to complete auto negotiation.");

    ret = FXmacPhyRead(instance_p, phy_addr, PHY_STATUS_REG_OFFSET, &status);
    if (ret != FT_SUCCESS)
    {
        FXMAC_ERROR("%s:%d,read PHY_CONTROL_REG_OFFSET is error", __func__, __LINE__);
        return ret;
    }


    while (!(status & PHY_STATUS_AUTONEGOTIATE_COMPLETE))
    {
        for (wait = 0; wait < 1000000; wait++)
            ;
        ret = FXmacPhyRead(instance_p, phy_addr, PHY_STATUS_REG_OFFSET, &status);
        if (ret != FT_SUCCESS)
        {
            FXMAC_ERROR("%s:%d,read PHY_STATUS_REG_OFFSET is error", __func__, __LINE__);
            return ret;
        }


        if (negotitation_timeout_cnt++ >= 0xfff)
        {
            FXMAC_ERROR("Auto negotiation is error.");
            return FXMAC_PHY_AUTO_AUTONEGOTIATION_FAILED;
        }
    }
    FXMAC_INFO("Auto negotiation complete.");

    ret = FXmacPhyRead(instance_p, phy_addr, PHY_SPECIFIC_STATUS_REG, &temp);
    if (ret != FT_SUCCESS)
    {
        FXMAC_ERROR("%s:%d,read PHY_SPECIFIC_STATUS_REG is error", __func__, __LINE__);
        return ret;
    }

    FXMAC_INFO("Temp is 0x%x", temp);
    ret = FXmacPhyRead(instance_p, phy_addr, PHY_STATUS_REG_OFFSET, &temp2);
    if (ret != FT_SUCCESS)
    {
        FXMAC_ERROR("%s:%d,read PHY_STATUS_REG_OFFSET is error", __func__, __LINE__);
        return ret;
    }

    FXMAC_INFO("Temp2 is 0x%x", temp2);

    if (temp & (1 << 13))
    {
        FXMAC_INFO("Duplex is full.");
        instance_p->config.duplex = 1;
    }
    else
    {
        FXMAC_INFO("Duplex is half.");
        instance_p->config.duplex = 0;
    }

    if ((temp & 0xC000) == PHY_SPECIFIC_STATUS_SPEED_1000M)
    {
        FXMAC_INFO("Speed is 1000M.");
        instance_p->config.speed = 1000;
    }
    else if ((temp & 0xC000) == PHY_SPECIFIC_STATUS_SPEED_100M)
    {
        FXMAC_INFO("Speed is 100M.");
        instance_p->config.speed = 100;
    }
    else
    {
        FXMAC_INFO("Speed is 10M.");
        instance_p->config.speed = 10;
    }

    return FT_SUCCESS;
}

void FxmaxLinkupCheck(void)
{
    u16 temp;
    FXmacPhyRead(instance_b, phy_addr_b, PHY_SPECIFIC_STATUS_REG, &temp);
    FXMAC_INFO("Reg 0x17 value is 0x%x", temp);
    FXMAC_INFO("Linkup status is 0x%x", temp & (1 << 10));
}


static FError FXmacConfigureIeeePhySpeed(FXmac *instance_p, u32 phy_addr, u32 speed, u32 duplex_mode)
{
    u16 control;
    u16 autonereg;
    volatile s32 wait;
    FError ret;
    u16 specific_reg = 0;

    FXMAC_INFO("Manual setting ,phy_addr is %d,speed %d, duplex_mode is %d.", phy_addr, speed, duplex_mode);

    ret = FXmacPhyRead(instance_p, phy_addr, PHY_AUTONEGO_ADVERTISE_REG, &autonereg);
    if (ret != FT_SUCCESS)
    {
        FXMAC_ERROR("%s:%d,read PHY_AUTONEGO_ADVERTISE_REG is error.", __func__, __LINE__);
        return ret;
    }

    autonereg |= PHY_AUTOADVERTISE_ASYMMETRIC_PAUSE_MASK;
    autonereg |= PHY_AUTOADVERTISE_PAUSE_MASK;
    ret = FXmacPhyWrite(instance_p, phy_addr, PHY_AUTONEGO_ADVERTISE_REG, autonereg);
    if (ret != FT_SUCCESS)
    {
        FXMAC_ERROR("%s:%d,write PHY_AUTONEGO_ADVERTISE_REG is error.", __func__, __LINE__);
        return ret;
    }


    ret = FXmacPhyRead(instance_p, phy_addr, PHY_CONTROL_REG_OFFSET, &control);
    if (ret != FT_SUCCESS)
    {
        FXMAC_ERROR("%s:%d,read PHY_AUTONEGO_ADVERTISE_REG is error.", __func__, __LINE__);
        return ret;
    }
    FXMAC_INFO("PHY_CONTROL_REG_OFFSET is 0x%x.", control);


    control &= ~PHY_CONTROL_LINKSPEED_1000M;
    control &= ~PHY_CONTROL_LINKSPEED_100M;
    control &= ~PHY_CONTROL_LINKSPEED_10M;

    if (speed == 1000)
    {
        control |= PHY_CONTROL_LINKSPEED_1000M;
    }
    else if (speed == 100)
    {
        control |= PHY_CONTROL_LINKSPEED_100M;
    }
    else if (speed == 10)
    {
        control |= PHY_CONTROL_LINKSPEED_10M;
    }

    if (duplex_mode == 1)
    {
        control |= PHY_CONTROL_FULL_DUPLEX_MASK;
    }
    else
    {
        control &= ~PHY_CONTROL_FULL_DUPLEX_MASK;
    }

    /* disable auto-negotiation */
    control &= ~(PHY_CONTROL_AUTONEGOTIATE_ENABLE);
    control &= ~(PHY_CONTROL_AUTONEGOTIATE_RESTART);

    ret = FXmacPhyWrite(instance_p, phy_addr, PHY_CONTROL_REG_OFFSET, control); /* Technology Ability Field */
    if (ret != FT_SUCCESS)
    {
        FXMAC_ERROR("%s:%d,write PHY_AUTONEGO_ADVERTISE_REG is error.", __func__, __LINE__);
        return ret;
    }

    for (wait = 0; wait < 100000; wait++)
        ;

    FXMAC_INFO("Manual selection completed.");

    ret = FXmacPhyRead(instance_p, phy_addr, PHY_SPECIFIC_STATUS_REG, &specific_reg);
    if (ret != FT_SUCCESS)
    {
        FXMAC_ERROR("%s:%d,read PHY_SPECIFIC_STATUS_REG is error.", __func__, __LINE__);
        return ret;
    }

    FXMAC_INFO("Specific reg is 0x%x.", specific_reg);

    if (specific_reg & (1 << 13))
    {
        FXMAC_INFO("Duplex is full.");
        instance_p->config.duplex = 1;
    }
    else
    {
        FXMAC_INFO("Duplex is half.");
        instance_p->config.duplex = 0;
    }

    if ((specific_reg & 0xC000) == PHY_SPECIFIC_STATUS_SPEED_1000M)
    {
        FXMAC_INFO("Speed is 1000M.");
        instance_p->config.speed = 1000;
    }
    else if ((specific_reg & 0xC000) == PHY_SPECIFIC_STATUS_SPEED_100M)
    {
        FXMAC_INFO("Speed is 100M.");
        instance_p->config.speed = 100;
    }
    else
    {
        FXMAC_INFO("Speed is 10M.");
        instance_p->config.speed = 10;
    }

    return FT_SUCCESS;
}

/**
 * @name: FXmacPhyInit
 * @msg:  setup the PHYs for proper speed setting.
 * @param {FXmac} *instance_p is a pointer to the instance to be worked on.
 * @param {u32} speed is phy operating speed
 * @param {u32} phy_addr is the address of the PHY to be read (supports multiple PHYs)
 * @param {u32} duplex_mode is The duplex mode can be selected via either the Auto-Negotiation process or manual duplex selection.
 * @param {u32} autonegotiation_en is an auto-negotiated flag . 1 is enable auto ,0 is manual
 * @return {FError}
 */
FError FXmacPhyInit(FXmac *instance_p, u32 speed, u32 duplex_mode, u32 autonegotiation_en)
{
    FError ret;
    u32 index = 0, phy_mask;
    u16 phy_identity;
    u32 phy_addr;

    if (FXmacDetect(instance_p, &phy_addr) != FT_SUCCESS)
    {
        FXMAC_ERROR("Phy is not found.");
        return FXMAC_PHY_IS_NOT_FOUND;
    }
    FXMAC_INFO("Setting phy addr is %d.", phy_addr);
    instance_p->phy_address = phy_addr;
    if (autonegotiation_en)
    {
        ret = FXmacGetIeeePhySpeed(instance_p, phy_addr);
        if (ret != FT_SUCCESS)
        {
            return ret;
        }
    }
    else
    {
        FXMAC_INFO("Set the communication speed manually.");
        ret = FXmacConfigureIeeePhySpeed(instance_p, phy_addr, speed, duplex_mode);
        if (ret != FT_SUCCESS)
        {
            FXMAC_ERROR("Failed to manually set the phy.");
            return ret;
        }

    }

    instance_p->link_status = FXMAC_LINKUP;
    return FT_SUCCESS;
}
