/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/emac/gd_eth_phy_lan8700.c
**
** \version     $Id$
**
** \brief       1
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/
#include "gtypes.h"
#include "gd_timer.h"
#include "gh_gpio.h"
#include "gd_gpio.h"
#define PHY_RESET_GPIO_TYPE_OUTPUT  GD_GPIO_TYPE_OUTPUT_0
#include "gd_ethernet.h"
#include "gd_eth_priv.h"
#include "gd_eth_emac.h"
#include "gd_eth_phy.h"
#include "gd_eth_phy_lan8700.h"

#include "gh_eth.h"
//#define DEBUG_PRINT
#ifdef DEBUG_PRINT
#include <gm_lib/gm_debug.h>
#endif

//*****************************************************************************
//*****************************************************************************
//** Local Defines
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local structures
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local Functions Declaration
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************

GERR GD_ETH_PHY_LAN8700_Init(void)
{
#if 0
    GBOOL   ret;
    U32     features;
    U32     phyRegVal;
    /* For now, I'll claim that the generic driver supports
        * all possible port types */
    features = (SP_TP | SP_MII | SP_AUI | SP_FIBRE | SP_BNC);

    /* Do we support autonegotiation? */
    ret = GD_ETH_ReadPhy(pPhyDev->addr, ETH_BMSR_REG1, &phyRegVal);
    if (ret != GTRUE)
        return GD_ERR_ETH_PHY_RW;

    if (phyRegVal & ETH_BMSR_ANEG_CAPABLE)
        features |= SP_AUTONEG;

    if (phyRegVal & ETH_BMSR_100TX_FULL)
        features |= SP_100T_FULL;
    if (phyRegVal & ETH_BMSR_100TX_HALF)
        features |= SP_100T_HALF;
    if (phyRegVal & ETH_BMSR_10T_FULL)
        features |= SP_10T_FULL;
    if (phyRegVal & ETH_BMSR_10T_HALF)
        features |= SP_10T_HALF;

    if (phyRegVal & ETH_BMSR_ESTATEN) {
        ret = GD_ETH_ReadPhy(pPhyDev->addr, ETH_EXPS_REG15, &phyRegVal);
        if (ret != GTRUE) return GD_ERR_ETH_PHY_RW;

        if (phyRegVal & ETH_EXPS_1000_TFULL)
            features |= SP_1000T_FULL;
        if (phyRegVal & ETH_EXPS_1000_THALF)
            features |= SP_1000T_HALF;
    }

    pPhyDev->supported      = features;
    pPhyDev->advertising    = features;

    GD_ETH_PHY_ConfigANeg(pPhyDev);
#endif
    return GD_OK;
}
GERR GD_ETH_PHY_LAN8700_Open(GD_HANDLE handle)
{
    //GD_ETH_PHY_DEVICE_DATA_S* device = (GD_ETH_PHY_DEVICE_DATA_S*)handle;
    return GD_OK;
}
GERR GD_ETH_PHY_LAN8700_Close(GD_HANDLE handle)
{
    return GD_OK;
}
GERR GD_ETH_PHY_LAN8700_SetWorkMode(GD_HANDLE handle, GD_ETH_Work_ModeT workmode)
{
    /*Set MII mode: reg 18 bit 14---0:MII , 1:RMII*/
    U8      ii = 0;
    GBOOL   retval = GFALSE;
    U32     regval = (U32)0;
    GD_ETH_PHY_DEVICE_DATA_S* device = (GD_ETH_PHY_DEVICE_DATA_S*)handle;
    U8      addr = (U8)device->addr;
    // workmode.mode
    while(1)
    {
        regval = 0;
        retval = GD_ETH_ReadPhy(addr, PHY_addr(18,SCSR), &regval);
        if ( retval != GTRUE )
        {
#ifdef DEBUG_PRINT
            GM_Printf("%s:Failed to read PHY Reg_%d!\n",__FUNCTION__, PHY_addr(18,SCSR));
#endif
            return GD_ERR_ETH_PHY_RW;
        }

        if(workmode.mode == GD_ETH_PHY_IF_MODE_RMII)
        {
            /*RMII mode*/
            if((regval & PHY_mask(18,RPHY_MODE)) == PHY_val(18,RPHY_RMII))//MII mode: bit 10---0:MII , 1:RMII
            {
#ifdef DEBUG_PRINT
                GM_Printf("Rmii mode set OK!\n");
#endif
                break;
            }

            regval &= (~PHY_mask(18,RPHY_MODE));
            regval |= PHY_val(18,RPHY_RMII);
        }
        else if(workmode.mode == GD_ETH_PHY_IF_MODE_MII)
        {
            /*MII mode*/
            if((regval & PHY_mask(18,RPHY_MODE)) == PHY_val(18,RPHY_MII))//MII mode: bit 10---0:MII , 1:RMII
            {
#ifdef DEBUG_PRINT
                GM_Printf("mii mode set OK!\n");
#endif
                break;
            }

            regval &= (~PHY_mask(18,RPHY_MODE));
            regval |= PHY_val(18,RPHY_MII);
        }
        else
        {
            return GD_ERR_ETH_NOT_SUPPORTED;
        }

        retval = GD_ETH_WritePhy(addr, PHY_addr(18,SCSR), regval);
        if ( retval != GTRUE )
        {
#ifdef DEBUG_PRINT
            GM_Printf("%s:Failed to write PHY Reg_%d!\n",__FUNCTION__, PHY_addr(18,SCSR));
#endif
            return GD_ERR_ETH_PHY_RW;
        }

        ii++;
        if(ii >= 10)
        {
            //GM_Printf("%s mode set failure!\n", phy_str_for_if(pPhyDev->phyPort));
            return GD_ERR_ETH_PHY_OTHER;
        }
    }


    regval = (U32)0;
    /* loopback setting */
    // workmode.loopback
    regval &= (~PHY_mask(0,LOOPBACK));
    if (workmode.loopback == GD_ETH_LOOP_ON_PHY )
    {
        regval |= PHY_val(0,LOOPBACK);
    }

        /* auto nego */
    // workmode.bEnAutoNeg
    regval &= (~PHY_mask(0,AN_ENABLE));
    if (workmode.bEnAutoNeg == GTRUE)
    {
        regval |= PHY_val(0,AUTO_NEGO);
    }
    else
    {
        /* speed */
        // workmode.speed
        regval &= (~PHY_mask(0,SPEEDSELECT));
        if (workmode.speed == GD_ETH_SPEED_100M )   /* 100M */
        {
            regval |= PHY_val(0,100M);
        }
        else if (workmode.speed == GD_ETH_SPEED_10M )/* 10M */
        {
            regval |= PHY_val(0,10M);    //nothing need to do.
        }
        else
        {
            return GD_ERR_ETH_NOT_SUPPORTED;
        }

        /* duplex */
        // workmode.duplex
        regval &= (~PHY_mask(0,DUPLEX_MODE));
        if(workmode.duplex == GD_ETH_FULL_DUPLEX)   /* Full Duplex */
        {
            regval |= PHY_val(0,DUPLEX_FULL);
        }
        else if(workmode.duplex == GD_ETH_HALF_DUPLEX) /* half */
        {
            regval |= PHY_val(0,DUPLEX_HALF);    //nothing need to do.
        }
        else
        {
            return GD_ERR_ETH_NOT_SUPPORTED;
        }
    }
    /* write settings */
    retval = GD_ETH_WritePhy(addr, PHY_addr(0,BMCR), regval);
    if ( retval != GTRUE )
        return GD_ERR_ETH_PHY_RW;
    return GD_OK;
}
GERR GD_ETH_PHY_LAN8700_GetWorkStatus(GD_HANDLE handle, GD_ETH_StatParamsT* pStat)
{
    return GD_OK;
}

//*****************************************************************************
//*****************************************************************************
//** Local Functions
//*****************************************************************************
//*****************************************************************************

