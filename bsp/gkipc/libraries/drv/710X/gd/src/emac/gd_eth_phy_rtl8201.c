/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/emac/gd_eth_phy_rtl8201.c
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
#include "gd_ethernet.h"
#include "gd_eth_priv.h"
#include "gd_eth_emac.h"
#include "gd_eth_phy.h"
#include "gd_eth_phy_rtl8201.h"

#include "gh_eth.h"
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

GERR GD_ETH_PHY_RTL8200_Init(void)
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
GERR GD_ETH_PHY_RTL8200_Open(GD_HANDLE handle)
{
    //GD_ETH_PHY_DEVICE_DATA_S* device = (GD_ETH_PHY_DEVICE_DATA_S*)handle;
    return GD_OK;
}
GERR GD_ETH_PHY_RTL8200_Close(GD_HANDLE handle)
{
    return GD_OK;
}
GERR GD_ETH_PHY_RTL8200_GetWorkStatus(GD_HANDLE handle, GD_ETH_StatParamsT* pStat)
{
    return GD_OK;
}

//*****************************************************************************
//*****************************************************************************
//** Local Functions
//*****************************************************************************
//*****************************************************************************

