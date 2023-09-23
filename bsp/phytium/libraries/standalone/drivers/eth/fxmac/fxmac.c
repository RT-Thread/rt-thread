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
 * FilePath: fxmac.c
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for xmac driver .Functions in this file are the minimum required functions
 * for this driver.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
 */

#include "fxmac.h"
#include "ftypes.h"
#include "fxmac_hw.h"
#include "stdio.h"

#include "fdebug.h"


#define FXMAC_DEBUG_TAG "FXMAC"
#define FXMAC_PRINT_E(format, ...) FT_DEBUG_PRINT_E(FXMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FXMAC_PRINT_I(format, ...) FT_DEBUG_PRINT_I(FXMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FXMAC_PRINT_D(format, ...) FT_DEBUG_PRINT_D(FXMAC_DEBUG_TAG, format, ##__VA_ARGS__)
#define FXMAC_PRINT_W(format, ...) FT_DEBUG_PRINT_W(FXMAC_DEBUG_TAG, format, ##__VA_ARGS__)


static void FXmacReset(FXmac *instance_p);
extern FError FXmacSetTypeIdCheck(FXmac *instance_p, u32 id_check, u8 index);


static void FXmacHighSpeedConfiguration(FXmac *instance_p,u32 speed)
{
    u32 reg_value;
    s32 set_speed = 0;
    switch (speed)
    {
        case FXMAC_SPEED_25000:
            set_speed = 2;
            break;
        case FXMAC_SPEED_10000:
            set_speed = 4;
            break;
        case FXMAC_SPEED_5000:
            set_speed = 3;
            break;
        case FXMAC_SPEED_2500:
            set_speed = 2;
            break;
        case FXMAC_SPEED_1000:
            set_speed = 1;
            break;
        default:
            set_speed = 0;
            break;
    }
    /*GEM_HSMAC(0x0050) provide rate to the external*/
    reg_value = FXMAC_READREG32(instance_p->config.base_address, FXMAC_GEM_HSMAC);
    reg_value &= ~FXMAC_GEM_HSMACSPEED_MASK;
    reg_value |= (set_speed) &FXMAC_GEM_HSMACSPEED_MASK;
    FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_HSMAC, reg_value);

    reg_value = FXMAC_READREG32(instance_p->config.base_address, FXMAC_GEM_HSMAC);

    FXMAC_PRINT_I("FXMAC_GEM_HSMAC is %x \r\n ", reg_value);
}

#if defined(FXMAC_CLK_TYPE_0)

/**
 * @name: FXmacSelectClk
 * @msg:  Determine the driver clock configuration based on the media independent interface
 * @param {FXmac} *instance_p is a pointer to the instance to be worked on.
 * @param {u32} speed interface speed
 * @return {*}
 */
void FXmacSelectClk(FXmac *instance_p)
{
    u32 reg_value;

    u32 speed = instance_p->config.speed;
    FASSERT(instance_p != NULL);
    FASSERT((speed == FXMAC_SPEED_10) || (speed == FXMAC_SPEED_100) || (speed == FXMAC_SPEED_1000) || (speed == FXMAC_SPEED_2500) || (speed == FXMAC_SPEED_10000));

    if ((instance_p->config.interface == FXMAC_PHY_INTERFACE_MODE_USXGMII) || (instance_p->config.interface == FXMAC_PHY_INTERFACE_MODE_XGMII))
    {
        if (speed == FXMAC_SPEED_10000)
        {
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_SRC_SEL_LN, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_DIV_SEL0_LN, 0x4);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_DIV_SEL1_LN, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_PMA_XCVR_POWER_STATE, 0x1);
        }
    }
    else if(instance_p->config.interface == FXMAC_PHY_INTERFACE_MODE_5GBASER)
    {
        if(speed == FXMAC_SPEED_5000)
        {
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_SRC_SEL_LN, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_DIV_SEL0_LN, 0x8);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_DIV_SEL1_LN, 0x2);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_PMA_XCVR_POWER_STATE, 0x0);
        }
    }
    else if(instance_p->config.interface == FXMAC_PHY_INTERFACE_MODE_2500BASEX)
    {
        if(speed == FXMAC_SPEED_25000)
        {
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_DIV_SEL0_LN, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_DIV_SEL1_LN, 0x2);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_PMA_XCVR_POWER_STATE, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL0, 0);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL1, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL2, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL3, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL0, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL1, 0x0);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL3_0, 0x0); /*0x1c70*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL4_0, 0x0); /*0x1c74*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL3_0, 0x0); /*0x1c78*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL4_0, 0x0); /*0x1c7c*/
        }
    }
    else if (instance_p->config.interface == FXMAC_PHY_INTERFACE_MODE_SGMII)
    {
        FXMAC_PRINT_I("FXMAC_PHY_INTERFACE_MODE_SGMII init");
        if (speed == FXMAC_SPEED_2500)
        {
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_SRC_SEL_LN, 0);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_DIV_SEL0_LN, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_DIV_SEL1_LN, 0x2);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_PMA_XCVR_POWER_STATE, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL0, 0);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL1, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL2, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL3, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL0, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL1, 0x0);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL3_0, 0x0); /*0x1c70*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL4_0, 0x0); /*0x1c74*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL3_0, 0x0); /*0x1c78*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL4_0, 0x0); /*0x1c7c*/
        }
        else if (speed == FXMAC_SPEED_1000)
        {
            FXMAC_PRINT_I("sgmii FXMAC_SPEED_1000 \r\n ");
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_SRC_SEL_LN, 1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_DIV_SEL0_LN, 0x4);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_DIV_SEL1_LN, 0x8);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_PMA_XCVR_POWER_STATE, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL0, 0x0);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL1, 0x0);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL2, 0x0);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL3, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL0, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL1, 0x0);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL3_0, 0x0); /*0x1c70*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL4_0, 0x0); /*0x1c74*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL3_0, 0x0); /*0x1c78*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL4_0, 0x0); /*0x1c7c*/
        }
        else if ((speed == FXMAC_SPEED_100) || (speed == FXMAC_SPEED_10))
        {
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_DIV_SEL0_LN, 0x4);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_DIV_SEL1_LN, 0x8);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_PMA_XCVR_POWER_STATE, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL0, 0x0);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL1, 0x0);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL2, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL3, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL0, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL1, 0x0);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL3_0, 0x1); /*0x1c70*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL4_0, 0x0); /*0x1c74*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL3_0, 0x0); /*0x1c78*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL4_0, 0x1); /*0x1c7c*/
        }
    }
    else if (instance_p->config.interface == FXMAC_PHY_INTERFACE_MODE_RGMII)
    {
        FXMAC_PRINT_I("FXMAC_PHY_INTERFACE_MODE_RGMII init");
        if (speed == FXMAC_SPEED_1000)
        {
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_MII_SELECT, 0x1);       /*0x1c18*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_SEL_MII_ON_RGMII, 0x0); /*0x1c1c*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL0, 0x0);      /*0x1c20*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL1, 0x1);      /*0x1c24*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL2, 0x0);      /*0x1c28*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL3, 0x0);      /*0x1c2c*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL0, 0x0);      /*0x1c30*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL1, 0x1);      /*0x1c34*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_CLK_250M_DIV10_DIV100_SEL,
                             0x0);                                                               /*0x1c38*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL5, 0x1);       /*0x1c48*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RGMII_TX_CLK_SEL0, 0x1); /*0x1c80*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RGMII_TX_CLK_SEL1, 0x0); /*0x1c84*/
        }
        else if (speed == FXMAC_SPEED_100)
        {
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_SEL_MII_ON_RGMII, 0x0); /*0x1c1c*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL0, 0x0);      /*0x1c20*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL1, 0x1);      /*0x1c24*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL2, 0x0);      /*0x1c28*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL3, 0x0);      /*0x1c2c*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL0, 0x0);      /*0x1c30*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL1, 0x1);      /*0x1c34*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_CLK_250M_DIV10_DIV100_SEL,
                             0x0);                                                               /*0x1c38*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL5, 0x1);       /*0x1c48*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RGMII_TX_CLK_SEL0, 0x0); /*0x1c80*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RGMII_TX_CLK_SEL1, 0x0); /*0x1c84*/
        }
        else
        {
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_SEL_MII_ON_RGMII, 0x0); /*0x1c1c*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL0, 0x0);      /*0x1c20*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL1, 0x1);      /*0x1c24*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL2, 0x0);      /*0x1c28*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_TX_CLK_SEL3, 0x0);      /*0x1c2c*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL0, 0x0);      /*0x1c30*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL1, 0x1);      /*0x1c34*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_CLK_250M_DIV10_DIV100_SEL,
                             0x1);                                                               /*0x1c38*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL5, 0x1);       /*0x1c48*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RGMII_TX_CLK_SEL0, 0x0); /*0x1c80*/
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RGMII_TX_CLK_SEL1, 0x0); /*0x1c84*/
        }
    }
    else if (instance_p->config.interface == FXMAC_PHY_INTERFACE_MODE_RMII)
    {
        FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_RX_CLK_SEL5, 0x1); /*0x1c48*/
    }

    FXmacHighSpeedConfiguration(instance_p,speed);
}
#else
void FXmacSelectClk(FXmac *instance_p)
{
    u32 reg_value;

    u32 speed = instance_p->config.speed;
    FASSERT(instance_p != NULL);
    FASSERT((speed == FXMAC_SPEED_10) || (speed == FXMAC_SPEED_100) || (speed == FXMAC_SPEED_1000) || (speed == FXMAC_SPEED_2500) || (speed == FXMAC_SPEED_10000));
    FXMAC_PRINT_I("************* FXmacSelectClk *************** ");
    if (instance_p->config.interface == FXMAC_PHY_INTERFACE_MODE_SGMII)
    {
        FXMAC_PRINT_I("FXMAC_PHY_INTERFACE_MODE_SGMII init");
        if ((speed == FXMAC_SPEED_100) || (speed == FXMAC_SPEED_10))
        {
            FXMAC_PRINT_I("speed IS %d \r\n",speed);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_DIV_SEL1_LN, 0x1);
            FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_GEM_SRC_SEL_LN, 0x1);
        }
    }

    if(speed == FXMAC_SPEED_10000)
    {
        FXMAC_PRINT_I("FXMAC_SPEED_10000 is not set high speed\r\n");
    }
    else
    {
        FXmacHighSpeedConfiguration(instance_p,speed);
    }
}
#endif

/**
 * Start the Ethernet controller as follows:
 *   - Enable transmitter if FXMAC_TRANSMIT_ENABLE_OPTION is set
 *   - Enable receiver if FXMAC_RECEIVER_ENABLE_OPTION is set
 *   - Start the SG DMA send and receive channels and enable the device
 *     interrupt
 *
 * @param instance_p is a pointer to the instance to be worked on.
 *
 * @return N/A
 *
 * @note
 * Hardware is configured with scatter-gather DMA, the driver expects to start
 * the scatter-gather channels and expects that the user has previously set up
 * the buffer descriptor lists.
 *
 * This function makes use of internal resources that are shared between the
 * Start, Stop, and Set/ClearOptions functions. So if one task might be setting
 * device options while another is trying to start the device, the user is
 * required to provide protection of this shared data (typically using a
 * semaphore).
 *
 * This function must not be preempted by an interrupt that may service the
 * device.
 *
 */
void FXmacStart(FXmac *instance_p)
{
    u32 reg_val;
    u32 reg = 0;

    /* Assert bad arguments and conditions */
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == (u32)FT_COMPONENT_IS_READY);


    /* clear any existed int status */
    FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_ISR_OFFSET,
                     FXMAC_IXR_ALL_MASK);

    /* Enable transmitter if not already enabled */
    if ((instance_p->config.network_default_config & (u32)FXMAC_TRANSMITTER_ENABLE_OPTION) != 0x00000000U)
    {
        reg_val = FXMAC_READREG32(instance_p->config.base_address,
                                  FXMAC_NWCTRL_OFFSET);
        if ((!(reg_val & FXMAC_NWCTRL_TXEN_MASK)) == TRUE)
        {
            FXMAC_WRITEREG32(instance_p->config.base_address,
                             FXMAC_NWCTRL_OFFSET,
                             reg_val | (u32)FXMAC_NWCTRL_TXEN_MASK);
        }
    }

    /* Enable receiver if not already enabled */
    if ((instance_p->config.network_default_config & FXMAC_RECEIVER_ENABLE_OPTION) != 0x00000000U)
    {

        reg_val = FXMAC_READREG32(instance_p->config.base_address,
                                  FXMAC_NWCTRL_OFFSET);
        FXMAC_PRINT_I("endable receiver 0x%x \r\n ", reg_val);
        if ((!(reg_val & FXMAC_NWCTRL_RXEN_MASK)) == TRUE)
        {
            FXMAC_WRITEREG32(instance_p->config.base_address,
                             FXMAC_NWCTRL_OFFSET,
                             reg_val | (u32)FXMAC_NWCTRL_RXEN_MASK);
        }
    }
    FXMAC_PRINT_I("FXMAC_NWCTRL_OFFSET is 0x%x \r\n", FXMAC_READREG32(instance_p->config.base_address,
                  FXMAC_NWCTRL_OFFSET));

    /* Enable TX and RX interrupt */
    FXMAC_INT_ENABLE(instance_p, instance_p->mask);


    /* Mark as started */
    instance_p->is_started = FT_COMPONENT_IS_STARTED;

    return;
}


/**
 * Gracefully stop the Ethernet MAC as follows:
 *   - Disable all interrupts from this device
 *   - Stop DMA channels
 *   - Disable the tansmitter and receiver
 *
 * Device options currently in effect are not changed.
 *
 * This function will disable all interrupts. Default interrupts settings that
 * had been enabled will be restored when FXmacStart() is called.
 *
 * @param instance_p is a pointer to the instance to be worked on.
 *
 * @note
 * This function makes use of internal resources that are shared between the
 * Start, Stop, Setoptions, and Clearoptions functions. So if one task might be
 * setting device options while another is trying to start the device, the user
 * is required to provide protection of this shared data (typically using a
 * semaphore).
 *
 * Stopping the DMA channels causes this function to block until the DMA
 * operation is complete.
 *
 */
void FXmacStop(FXmac *instance_p)
{
    u32 reg_val;

    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == (u32)FT_COMPONENT_IS_READY);

    /* Disable all interrupts */
    FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_IDR_OFFSET,
                     FXMAC_IXR_ALL_MASK);



    /* Disable the receiver & transmitter */
    reg_val = FXMAC_READREG32(instance_p->config.base_address,
                              FXMAC_NWCTRL_OFFSET);
    reg_val &= (u32)(~FXMAC_NWCTRL_RXEN_MASK);
    reg_val &= (u32)(~FXMAC_NWCTRL_TXEN_MASK);
    FXMAC_WRITEREG32(instance_p->config.base_address,
                     FXMAC_NWCTRL_OFFSET, reg_val);

    /* Mark as stopped */
    instance_p->is_started = 0U;
}

static u32 FXmacClkDivGet(FXmac *instance_p)
{
    FXmacConfig *config_p;

    config_p = &instance_p->config;

    if (config_p->pclk_hz <= 20000000)
    {
        return FXMAC_NWCFG_CLOCK_DIV8_MASK;
    }
    else if (config_p->pclk_hz <= 40000000)
    {
        return FXMAC_NWCFG_CLOCK_DIV16_MASK;
    }
    else if (config_p->pclk_hz <= 80000000)
    {
        return FXMAC_NWCFG_CLOCK_DIV32_MASK;
    }
    else if (instance_p->moudle_id >= 2)
    {
        if (config_p->pclk_hz <= 120000000)
        {
            return FXMAC_NWCFG_CLOCK_DIV48_MASK;
        }
        else if (config_p->pclk_hz <= 160000000)
        {
            return FXMAC_NWCFG_CLOCK_DIV64_MASK;
        }
        else if (config_p->pclk_hz <= 240000000)
        {
            return FXMAC_NWCFG_CLOCK_DIV96_MASK;
        }
        else if (config_p->pclk_hz <= 320000000)
        {
            return FXMAC_NWCFG_CLOCK_DIV128_MASK;
        }
        else
        {
            return FXMAC_NWCFG_CLOCK_DIV224_MASK;
        }
    }
    else
    {
        return FXMAC_NWCFG_CLOCK_DIV64_MASK;
    }
}

static u32 FXmacConfigureCaps(FXmac *instance_p)
{
    u32 read_regs = 0;
    FXmacConfig *config_p;
    instance_p->caps = 0;
    config_p = &instance_p->config;
    read_regs = FXMAC_READREG32(config_p->base_address, FXMAC_DESIGNCFG_DEBUG1_OFFSET);
    if((read_regs&FXMAC_DESIGNCFG_DEBUG1_BUS_IRQCOR_MASK) == 0)
    {
        instance_p->caps |= FXMAC_CAPS_ISR_CLEAR_ON_WRITE;
        FXMAC_PRINT_I("Has FXMAC_CAPS_ISR_CLEAR_ON_WRITE feature");
    }
}

static u32 FXmacDmaWidth(FXmac *instance_p)
{
    u32 read_regs = 0;
    FXmacConfig *config_p;
    config_p = &instance_p->config;

    if (instance_p->moudle_id < 2)
    {
        return FXMAC_NWCFG_BUS_WIDTH_32_MASK;
    }

    read_regs = FXMAC_READREG32(config_p->base_address, FXMAC_DESIGNCFG_DEBUG1_OFFSET);

    switch ((read_regs & FXMAC_DESIGNCFG_DEBUG1_BUS_WIDTH_MASK) >> 25)
    {
        case 4:
            FXMAC_PRINT_I("bus width is 128");
            return FXMAC_NWCFG_BUS_WIDTH_128_MASK;
        case 2:
            FXMAC_PRINT_I("bus width is 64");
            return FXMAC_NWCFG_BUS_WIDTH_64_MASK;
        default:
            FXMAC_PRINT_I("bus width is 32");
            return FXMAC_NWCFG_BUS_WIDTH_32_MASK;
    }
}

static void FXmacDmaReset(FXmac *instance_p)
{
    u32 queue = 0;
    FXmacConfig *config_p;
    config_p = &instance_p->config;
    u32 dmacfg = 0;
    u32 rx_buf_size = 0;

    rx_buf_size = instance_p->max_frame_size / FXMAC_RX_BUF_UNIT;
    rx_buf_size += ((instance_p->max_frame_size % FXMAC_RX_BUF_UNIT) != 0) ? 1 : 0; /* roundup */

    if (instance_p->moudle_id >= 2)
    {
        for (queue = 0; queue < config_p->max_queue_num; queue++)
        {
            dmacfg = 0;
            FXmacSetQueuePtr(instance_p, (uintptr)NULL, queue, (u16)FXMAC_SEND);
            FXmacSetQueuePtr(instance_p, (uintptr)NULL, queue, (u16)FXMAC_RECV);

            if (queue)
            {
                FXMAC_WRITEREG32(config_p->base_address, FXMAC_RXBUFQX_SIZE_OFFSET(queue), rx_buf_size);
            }
            else /* queue is 0 */
            {
                dmacfg |= ((u32)FXMAC_DMACR_RXBUF_MASK & (rx_buf_size << FXMAC_DMACR_RXBUF_SHIFT));
            }
        }

        dmacfg |= (config_p->dma_brust_length & FXMAC_DMACR_BLENGTH_MASK);

        dmacfg &= ~FXMAC_DMACR_ENDIAN_MASK;
        dmacfg &= ~FXMAC_DMACR_SWAP_MANAGEMENT_MASK; /* 选择小端 */

        dmacfg &= ~FXMAC_DMACR_TCPCKSUM_MASK; /* close  transmitter checksum generation engine */

        dmacfg &= ~FXMAC_DMACR_ADDR_WIDTH_64;
        dmacfg |= FXMAC_DMACR_RXSIZE_MASK | FXMAC_DMACR_TXSIZE_MASK;
#if defined(__aarch64__) || defined(__arch64__)
        dmacfg |= FXMAC_DMACR_ADDR_WIDTH_64;
#endif
    }
    else
    {
        FXmacSetQueuePtr(instance_p, (uintptr)NULL, 0, (u16)FXMAC_SEND);
        FXmacSetQueuePtr(instance_p, (uintptr)NULL, 0, (u16)FXMAC_RECV);
        dmacfg |= ((u32)FXMAC_DMACR_RXBUF_MASK & (rx_buf_size << FXMAC_DMACR_RXBUF_SHIFT));
        dmacfg |= (config_p->dma_brust_length & FXMAC_DMACR_BLENGTH_MASK);

        dmacfg &= ~FXMAC_DMACR_ENDIAN_MASK;
        dmacfg &= ~FXMAC_DMACR_SWAP_MANAGEMENT_MASK; /* 选择小端 */

        dmacfg &= ~FXMAC_DMACR_TCPCKSUM_MASK; /* close  transmitter checksum generation engine */

        dmacfg &= ~FXMAC_DMACR_ADDR_WIDTH_64;
        dmacfg |= FXMAC_DMACR_RXSIZE_MASK | FXMAC_DMACR_TXSIZE_MASK;
#if defined(__aarch64__) || defined(__arch64__)
        dmacfg |= FXMAC_DMACR_ADDR_WIDTH_64;
#endif
    }

    FXMAC_WRITEREG32(config_p->base_address, FXMAC_DMACR_OFFSET, dmacfg);
}


/**
 * Perform a graceful reset of the Ethernet MAC. Resets the DMA channels, the
 * transmitter, and the receiver.
 *
 * Steps to reset
 * - Stops transmit and receive channels
 * - Stops DMA
 * - Configure transmit and receive buffer size to default
 * - Clear transmit and receive status register and counters
 * - Clear all interrupt sources
 * - Clear phy (if there is any previously detected) address
 * - Clear MAC addresses (1-4) as well as Type IDs and hash value
 *
 * All options are placed in their default state. Any frames in the
 * descriptor lists will remain in the lists. The side effect of doing
 * this is that after a reset and following a restart of the device, frames
 * were in the list before the reset may be transmitted or received.
 *
 * The upper layer software is responsible for re-configuring (if necessary)
 * and restarting the MAC after the reset. Note also that driver statistics
 * are not cleared on reset. It is up to the upper layer software to clear the
 * statistics if needed.
 *
 * When a reset is required, the driver notifies the upper layer software of
 * this need through the ErrorHandler callback and specific status codes.
 * The upper layer software is responsible for calling this Reset function
 * and then re-configuring the device.
 *
 * @param instance_p is a pointer to the instance to be worked on.
 *
 */
static void FXmacReset(FXmac *instance_p)
{
    u32 reg_val, write_reg = 0;
    u8 i;
    s8 mac_addr[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    u32 rx_buf_num;

    FASSERT(instance_p != NULL);

    /* Stop the device and reset hardware */
    FXmacStop(instance_p);

    instance_p->moudle_id = (FXMAC_READREG32(instance_p->config.base_address, FXMAC_REVISION_REG_OFFSET) & FXMAC_IDENTIFICATION_MASK) >> 16;
    FXMAC_PRINT_I("instance_p->moudle_id is %d \r\n", instance_p->moudle_id);
    instance_p->max_mtu_size = FXMAC_MTU;
    instance_p->max_frame_size =  FXMAC_MAX_FRAME_SIZE;

    FXMAC_WRITEREG32(instance_p->config.base_address,
                     FXMAC_NWCTRL_OFFSET,
                     ((FXMAC_NWCTRL_STATCLR_MASK) & (u32)(~FXMAC_NWCTRL_LOOPBACK_LOCAL_MASK)) | FXMAC_NWCTRL_MDEN_MASK);
    FXmacConfigureCaps(instance_p);
    write_reg = FXmacClkDivGet(instance_p); /* mdio clock division */
    write_reg |= FXmacDmaWidth(instance_p); /* DMA位宽 */

    FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_NWCFG_OFFSET, write_reg);

    FXmacDmaReset(instance_p);

    /* This register, when read provides details of the status of the receive path. */
    FXMAC_WRITEREG32(instance_p->config.base_address,
                     FXMAC_RXSR_OFFSET, FXMAC_SR_ALL_MASK);

    /* write 1 ro the relavant bit location disable that particular interrupt */
    FXMAC_WRITEREG32(instance_p->config.base_address,
                     FXMAC_IDR_OFFSET, FXMAC_IXR_ALL_MASK);

    reg_val = FXMAC_READREG32(instance_p->config.base_address,
                              FXMAC_ISR_OFFSET);
    FXMAC_WRITEREG32(instance_p->config.base_address, FXMAC_ISR_OFFSET,
                     reg_val);

    FXMAC_WRITEREG32(instance_p->config.base_address,
                     FXMAC_TXSR_OFFSET, FXMAC_SR_ALL_MASK);

    FXmacClearHash(instance_p);

    /* set default mac address */
    for (i = 0U; i < 4U; i++)
    {
        (void)FXmacSetMacAddress(instance_p, mac_addr, i);
        (void)FXmacGetMacAddress(instance_p, mac_addr, i);
        (void)FXmacSetTypeIdCheck(instance_p, 0x00000000U, i);
    }

    /* clear all counters */
    for (i = 0U; i < (u8)((FXMAC_LAST_OFFSET - FXMAC_OCTTXL_OFFSET) / 4U);
         i++)
    {
        (void)FXMAC_READREG32(instance_p->config.base_address,
                              FXMAC_OCTTXL_OFFSET + (u32)(((u32)i) * ((u32)4)));
    }

    /* Sync default options with hardware but leave receiver and
     * transmitter disabled. They get enabled with FXmacStart() if
     * FXMAC_TRANSMITTER_ENABLE_OPTION and
     * FXMAC_RECEIVER_ENABLE_OPTION are set.
     */
    FXmacSetOptions(instance_p, instance_p->config.network_default_config & ~((u32)FXMAC_TRANSMITTER_ENABLE_OPTION | (u32)FXMAC_RECEIVER_ENABLE_OPTION), 0);
    FXmacClearOptions(instance_p, ~instance_p->config.network_default_config, 0);
}

/**
 * @name: FXmacInitInterface
 * @msg:  Initialize the MAC controller configuration based on the PHY interface type
 * @note:
 * @param {FXmac} *instance_p is a pointer to the instance to be worked on.
 */
void FXmacInitInterface(FXmac *instance_p)
{
    u32 config, control;
    FXmacConfig *config_p;
    config_p = &instance_p->config;

    if (config_p->interface == FXMAC_PHY_INTERFACE_MODE_XGMII )
    {
        config = FXMAC_READREG32(config_p->base_address, FXMAC_NWCFG_OFFSET);
        config &= ~FXMAC_NWCFG_PCSSEL_MASK;
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCFG_OFFSET, config);

        control = FXMAC_READREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET);
        control |= FXMAC_NWCTRL_ENABLE_HS_MAC_MASK; /* Use high speed MAC */
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET, control);

        config_p->duplex = 1;
    }
    else if (config_p->interface == FXMAC_PHY_INTERFACE_MODE_USXGMII || config_p->interface == FXMAC_PHY_INTERFACE_MODE_5GBASER)
    {
        FXMAC_PRINT_I("usx interface is %d",config_p->interface);
        /*  network_config */
        config_p->duplex = 1;
        config = FXMAC_READREG32(config_p->base_address, FXMAC_NWCFG_OFFSET);
        config |= FXMAC_NWCFG_PCSSEL_MASK;
        config &= ~FXMAC_NWCFG_100_MASK;
        config &= ~FXMAC_NWCFG_SGMII_MODE_ENABLE_MASK;
        if (config_p->duplex == 1)
        {
            FXMAC_PRINT_I("is duplex");
            config |= FXMAC_NWCFG_FDEN_MASK;
        }
    
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCFG_OFFSET, config);

        /* network_control */
        control = FXMAC_READREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET);
        control |= FXMAC_NWCTRL_ENABLE_HS_MAC_MASK; /* Use high speed MAC */
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET, control);
        
        
        /* High speed PCS control register */
        control = FXMAC_READREG32(config_p->base_address, FXMAC_GEM_USX_CONTROL_OFFSET);
        
        if (config_p->speed == FXMAC_SPEED_10000)
        {
            FXMAC_PRINT_I("is 10G");
            control |= FXMAC_GEM_USX_HS_MAC_SPEED_10G;
            control |= FXMAC_GEM_USX_SERDES_RATE_10G;
        }
        else if (config_p->speed == FXMAC_SPEED_25000)
        {
            control |= FXMAC_GEM_USX_HS_MAC_SPEED_2_5G;
        }
        else if (config_p->speed == FXMAC_SPEED_1000)
        {
            control |= FXMAC_GEM_USX_HS_MAC_SPEED_1G;
        }
        else if (config_p->speed == FXMAC_SPEED_100)
        {
            control |= FXMAC_GEM_USX_HS_MAC_SPEED_100M;
        }
        else if(config_p->speed == FXMAC_SPEED_5000)
        {
            control |= FXMAC_GEM_USX_HS_MAC_SPEED_5G;
            control |= FXMAC_GEM_USX_SERDES_RATE_5G;
        }
        
        control &= ~(FXMAC_GEM_USX_TX_SCR_BYPASS | FXMAC_GEM_USX_RX_SCR_BYPASS);
        control |= FXMAC_GEM_USX_RX_SYNC_RESET;
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_GEM_USX_CONTROL_OFFSET, control);

        control = FXMAC_READREG32(config_p->base_address, FXMAC_GEM_USX_CONTROL_OFFSET);
        control &= ~FXMAC_GEM_USX_RX_SYNC_RESET;
        control |= FXMAC_GEM_USX_TX_DATAPATH_EN;
        control |= FXMAC_GEM_USX_SIGNAL_OK;

        FXMAC_WRITEREG32(config_p->base_address, FXMAC_GEM_USX_CONTROL_OFFSET, control);

    }
    else if(config_p->interface == FXMAC_PHY_INTERFACE_MODE_2500BASEX)
    {
        /*  network_config */
        config_p->duplex = 1;
        config = FXMAC_READREG32(config_p->base_address, FXMAC_NWCFG_OFFSET);
        config |= FXMAC_NWCFG_PCSSEL_MASK | FXMAC_NWCFG_SGMII_MODE_ENABLE_MASK;
        config &= ~FXMAC_NWCFG_100_MASK;
        
        if (config_p->duplex == 1)
        {
            config |= FXMAC_NWCFG_FDEN_MASK;
        }
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCFG_OFFSET, config);

        /* network_control */
        control = FXMAC_READREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET);
        control &= ~FXMAC_NWCTRL_ENABLE_HS_MAC_MASK;
        control |= FXMAC_NWCTRL_TWO_PT_FIVE_GIG_MASK; /* Use high speed MAC */
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET, control);

        /* High speed PCS control register */
        control = FXMAC_READREG32(config_p->base_address, FXMAC_GEM_USX_CONTROL_OFFSET);
        
        if (config_p->speed == FXMAC_SPEED_25000)
        {
            control |= FXMAC_GEM_USX_HS_MAC_SPEED_2_5G;
        }
        
        control &= ~(FXMAC_GEM_USX_TX_SCR_BYPASS | FXMAC_GEM_USX_RX_SCR_BYPASS);
        control |= FXMAC_GEM_USX_RX_SYNC_RESET;
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_GEM_USX_CONTROL_OFFSET, control);

        control = FXMAC_READREG32(config_p->base_address, FXMAC_GEM_USX_CONTROL_OFFSET);
        control &= ~FXMAC_GEM_USX_RX_SYNC_RESET;
        control |= FXMAC_GEM_USX_TX_DATAPATH_EN;
        control |= FXMAC_GEM_USX_SIGNAL_OK;

        FXMAC_WRITEREG32(config_p->base_address, FXMAC_GEM_USX_CONTROL_OFFSET, control);

    }
    else if (config_p->interface == FXMAC_PHY_INTERFACE_MODE_SGMII)
    {
        config = FXMAC_READREG32(config_p->base_address, FXMAC_NWCFG_OFFSET);
        config |= FXMAC_NWCFG_PCSSEL_MASK | FXMAC_NWCFG_SGMII_MODE_ENABLE_MASK;

        config &= ~(FXMAC_NWCFG_100_MASK | FXMAC_NWCFG_FDEN_MASK|FXMAC_NWCFG_LENGTH_FIELD_ERROR_FRAME_DISCARD_MASK);

        if (instance_p->moudle_id >= 2)
        {
            config &= ~FXMAC_NWCFG_1000_MASK;
        }

        if (config_p->duplex)
        {
            config |= FXMAC_NWCFG_FDEN_MASK;
        }

        if (config_p->speed == FXMAC_SPEED_100)
        {
            config |= FXMAC_NWCFG_100_MASK;
        }
        else if (config_p->speed == FXMAC_SPEED_1000)
        {
            config |= FXMAC_NWCFG_1000_MASK;
        }

        FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCFG_OFFSET, config);

        if (config_p->speed == FXMAC_SPEED_2500)
        {
            control = FXMAC_READREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET);
            control |= FXMAC_NWCTRL_TWO_PT_FIVE_GIG_MASK;
            FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET, control);
        }
        else
        {
            control = FXMAC_READREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET);
            control &= ~FXMAC_NWCTRL_TWO_PT_FIVE_GIG_MASK;
            FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET, control);
        }

        control = FXMAC_READREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET);
        control &= ~FXMAC_NWCTRL_ENABLE_HS_MAC_MASK;
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET, control);

        control = FXMAC_READREG32(config_p->base_address, FXMAC_PCS_CONTROL_OFFSET);
        control |= FXMAC_PCS_CONTROL_ENABLE_AUTO_NEG;
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_PCS_CONTROL_OFFSET, control);
    }
    else
    {
        config = FXMAC_READREG32(config_p->base_address, FXMAC_NWCFG_OFFSET);

        FXMAC_PRINT_I("select rgmii \r\n");

        config &= ~FXMAC_NWCFG_PCSSEL_MASK;
        config &= ~(FXMAC_NWCFG_100_MASK | FXMAC_NWCFG_FDEN_MASK);

        if (instance_p->moudle_id >= 2)
        {
            config &= ~FXMAC_NWCFG_1000_MASK;
        }

        if (config_p->duplex)
        {
            config |= FXMAC_NWCFG_FDEN_MASK;
        }

        if (config_p->speed == FXMAC_SPEED_100)
        {
            config |= FXMAC_NWCFG_100_MASK;
        }
        else if (config_p->speed == FXMAC_SPEED_1000)
        {
            config |= FXMAC_NWCFG_1000_MASK;
        }

        FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCFG_OFFSET, config);

        control = FXMAC_READREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET);
        control &= ~FXMAC_NWCTRL_ENABLE_HS_MAC_MASK; /* Use high speed MAC */
        FXMAC_WRITEREG32(config_p->base_address, FXMAC_NWCTRL_OFFSET, control);
    }
}

static void FXmacIrqStubHandler(void)
{
    FASSERT_MSG(0, "Please register the interrupt callback function");
}

/**
 * @name: FXmacCfgInitialize
 * @msg:  Initialize a specific fxmac instance/driver.
 * @note:
 * @param {FXmac} *instance_p  is a pointer to the instance to be worked on.
 * @param {FXmacConfig} *config_p is the device configuration structure containing required
*        hardware build data.
 * @return {FT_SUCCESS} if initialization was successful
 */
FError FXmacCfgInitialize(FXmac *instance_p, const FXmacConfig *config_p)
{
    /* Verify arguments */
    FASSERT(instance_p != NULL);
    FASSERT(config_p != NULL);

    instance_p->config = *config_p;
    instance_p->link_status = FXMAC_LINKDOWN;
    /* Reset the hardware and set default options */
    instance_p->is_ready = FT_COMPONENT_IS_READY;
    FXmacReset(instance_p);

    instance_p->send_irq_handler = (FXmacIrqHandler)FXmacIrqStubHandler;
    instance_p->send_args = NULL;

    instance_p->recv_irq_handler = (FXmacIrqHandler)FXmacIrqStubHandler;
    instance_p->recv_args = NULL;

    instance_p->error_irq_handler = (FXmacErrorIrqHandler)FXmacIrqStubHandler;
    instance_p->error_args = NULL;

    instance_p->link_change_handler = (FXmacIrqHandler)FXmacIrqStubHandler;
    instance_p->link_change_args = NULL;

    instance_p->restart_handler = (FXmacIrqHandler)FXmacIrqStubHandler;
    instance_p->restart_args = NULL;

    instance_p->mask = FXMAC_INTR_MASK;
    return FT_SUCCESS;
}


/**
 * This function sets the start address of the transmit/receive buffer queue.
 *
 * @param   instance_p is a pointer to the instance to be worked on.
 * @param   queue_p is the address of the Queue to be written
 * @param   queue_num is the Buffer Queue Index
 * @param   direction indicates Transmit/Receive
 *
 * @note
 * The buffer queue addresses has to be set before starting the transfer, so
 * this function has to be called in prior to FXmacStart()
 *
 */
void FXmacSetQueuePtr(FXmac *instance_p, uintptr queue_p, u8 queue_num,
                      u32 direction)
{
    /* Assert bad arguments and conditions */
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == (u32)FT_COMPONENT_IS_READY);

    /* If already started, then there is nothing to do */
    if (instance_p->is_started == (u32)FT_COMPONENT_IS_STARTED)
    {
        return;
    }

    if (queue_num == 0x00U)
    {
        if (direction == FXMAC_SEND)
        {
            /* set base start address of TX buffer queue (tx buffer descriptor list) */
            FXMAC_WRITEREG32(instance_p->config.base_address,
                             FXMAC_TXQBASE_OFFSET,
                             (queue_p & ULONG64_LO_MASK) | (((queue_p == (uintptr)0)) ? 1 : 0));
        }
        else
        {
            /* set base start address of RX buffer queue (rx buffer descriptor list) */
            FXMAC_WRITEREG32(instance_p->config.base_address,
                             FXMAC_RXQBASE_OFFSET,
                             (queue_p & ULONG64_LO_MASK) | (((queue_p == (uintptr)0)) ? 1 : 0));
        }
    }
    else
    {
        if (direction == FXMAC_SEND)
        {
            FXMAC_WRITEREG32(instance_p->config.base_address,
                             FXMAC_QUEUE_REGISTER_OFFSET(FXMAC_TXQ1BASE_OFFSET, queue_num),
                             (queue_p & ULONG64_LO_MASK) | (((queue_p == (uintptr)0)) ? 1 : 0));
        }
        else
        {
            FXMAC_WRITEREG32(instance_p->config.base_address,
                             FXMAC_QUEUE_REGISTER_OFFSET(FXMAC_TXQ1BASE_OFFSET, queue_num),
                             (queue_p & ULONG64_LO_MASK) | (((queue_p == (uintptr)0)) ? 1 : 0));
        }
    }
#ifdef __aarch64__
    if (direction == FXMAC_SEND)
    {
        /* Set the MSB of TX Queue start address */
        FXMAC_WRITEREG32(instance_p->config.base_address,
                         FXMAC_MSBBUF_TXQBASE_OFFSET,
                         (u32)((queue_p & ULONG64_HI_MASK) >> 32U));
    }
    else
    {
        /* Set the MSB of RX Queue start address */
        FXMAC_WRITEREG32(instance_p->config.base_address,
                         FXMAC_MSBBUF_RXQBASE_OFFSET,
                         (u32)((queue_p & ULONG64_HI_MASK) >> 32U));
    }
#endif
}
