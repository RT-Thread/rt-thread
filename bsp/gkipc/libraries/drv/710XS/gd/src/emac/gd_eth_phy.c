/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/emac/gd_eth_phy.c
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
#include <stdio.h>
#include <string.h>
#include "gtypes.h"
#include "gh_gpio.h"
#include "gh_eth.h"
#include "gd_ethernet.h"
#include "gd_eth_priv.h"
#include "gd_eth_emac.h"
#include "gd_eth_phy.h"
#include "gd_eth_phy_rtl8201.h"
#include "gd_eth_phy_lan8700.h"
#include "gd_eth_phy_ar8032.h"
#include "gd_eth_ephy.h"
#include "gd_timer.h"

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
static GBOOL                        initialized = GFALSE;
static GD_HANDLE                    phyhandle   = 0;
static GD_ETH_PHY_DEVICE_DATA_S*    phydevice[GD_ETH_PHY_EXTERNAL_AUTO];
static GD_ETH_PHY_DEVICE_DATA_S     phy[]=
{
    {
        0x0007C0C4,                         /* deviceID */
        "SMSC",                             /* manufactureName */
        "LAN8700",                          /* deviceName */
        GD_ETH_PHY_LAN8700_Init ,           /* GD_ETH_PHY_Init */
        GD_ETH_PHY_LAN8700_Open,            /* GD_ETH_PHY_Open */
        GD_ETH_PHY_LAN8700_Close,           /* GD_ETH_PHY_Close */
        NULL,                               /* GD_ETH_PHY_SWReset use the default*/
        NULL,                               /* GD_ETH_PHY_SetWorkMode */
        GD_ETH_PHY_LAN8700_GetWorkStatus,   /* GD_ETH_PHY_GetWorkStatus */
        NULL,                               /* GD_ETH_PHY_GetId use the default*/
        (GD_ETH_PHY_AddrE)-1,               /* addr*/
    },
    {
        0x0007C0F1,                         /* deviceID */
        "SMSC",                             /* manufactureName */
        "LAN8710/LAN8720",                          /* deviceName */
        GD_ETH_PHY_LAN8700_Init ,           /* GD_ETH_PHY_Init */
        GD_ETH_PHY_LAN8700_Open,            /* GD_ETH_PHY_Open */
        GD_ETH_PHY_LAN8700_Close,           /* GD_ETH_PHY_Close */
        NULL,                               /* GD_ETH_PHY_SWReset use the default*/
        NULL,                               /* GD_ETH_PHY_SetWorkMode */
        GD_ETH_PHY_LAN8700_GetWorkStatus,   /* GD_ETH_PHY_GetWorkStatus */
        NULL,                               /* GD_ETH_PHY_GetId use the default*/
        (GD_ETH_PHY_AddrE)-1,               /* addr*/
    },
    {
        0x001CC815,                         /* deviceID */
        "REALTEK",                          /* manufactureName */
        "RTL8201",                          /* deviceName */
        GD_ETH_PHY_RTL8200_Init ,           /* GD_ETH_PHY_Init */
        GD_ETH_PHY_RTL8200_Open,            /* GD_ETH_PHY_Open */
        GD_ETH_PHY_RTL8200_Close,           /* GD_ETH_PHY_Close */
        NULL,                               /* GD_ETH_PHY_SWReset use the default*/
        NULL,                               /* GD_ETH_PHY_SetWorkMode use the default*/
        GD_ETH_PHY_RTL8200_GetWorkStatus,   /* GD_ETH_PHY_GetWorkStatus */
        NULL,                               /* GD_ETH_PHY_GetId use the default*/
        (GD_ETH_PHY_AddrE)-1,               /* addr*/
    },
    {
        0x004DD023,                         /* deviceID */
        "ATHEROS",                          /* manufactureName */
        "AR8032",                           /* deviceName */
        GD_ETH_PHY_AR8032_Init ,            /* GD_ETH_PHY_Init */
        GD_ETH_PHY_AR8032_Open,             /* GD_ETH_PHY_Open */
        GD_ETH_PHY_AR8032_Close,            /* GD_ETH_PHY_Close */
        NULL,                               /* GD_ETH_PHY_SWReset use the default*/
        NULL,                               /* GD_ETH_PHY_SetWorkMode use the default*/
        GD_ETH_PHY_AR8032_GetWorkStatus,    /* GD_ETH_PHY_GetWorkStatus */
        NULL,                               /* GD_ETH_PHY_GetId use the default*/
        (GD_ETH_PHY_AddrE)-1,               /* addr*/
    },
    {
        0x00000000,                         /* deviceID */
        "GOKE",                             /* manufactureName */
        "GK7101E",                          /* deviceName */
        GD_ETH_EPHY_Init ,                  /* GD_ETH_PHY_Init */
        GD_ETH_EPHY_Open,                   /* GD_ETH_PHY_Open */
        GD_ETH_EPHY_Close,                  /* GD_ETH_PHY_Close */
        GD_ETH_EPHY_SWReset,                /* GD_ETH_PHY_SWReset*/
        GD_ETH_EPHY_SetWorkMode,            /* GD_ETH_PHY_SetWorkMode */
        GD_ETH_EPHY_GetWorkStatus,          /* GD_ETH_PHY_GetWorkStatus */
        GD_ETH_EPHY_GetId,                  /* GD_ETH_PHY_GetId*/
        0x1F,                               /* addr*/
    },
};

static const char *phy_if_strings[] __attribute__ ((section(".nocache_buffer"))) = {
    "mii",
    "gmii",
    "sgmii",
    "tbi",
    "rmii",
    "rgmii",
    "rgmii-id",
    "rgmii-rxid",
    "rgmii-txid",
    "rtbi",
    "xgmii",
    "",
};

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
GERR GD_ETH_PHY_Init(U8 phyType)
{
    U32 i,j,k,count,phy_id,try_time;
	U32 a = 0;
	
    if (initialized == GTRUE)
    {
        return GD_ERR_ALREADY_INITIALIZED;
    }

    try_time = 2;
    for(k=0; k<try_time && !initialized; k++)
    {
        count = sizeof(phy) / sizeof(GD_ETH_PHY_DEVICE_DATA_S);

        for (i=0; i<GD_ETH_PHY_EXTERNAL_AUTO; i++)
        {
            phydevice[i] = NULL;
            for (j=0; j<count; j++)
            {
                if(phy[j].addr == (GD_ETH_PHY_AddrE)-1)
                {
                    if(phy[j].GD_ETH_PHY_GetId)
                    {
                        phy[j].GD_ETH_PHY_GetId(i, &phy_id);
                    }
                    else
                    {
                        phy[j].addr = (GD_ETH_PHY_AddrE)i;
                        GD_ETH_PHY_GetId((GD_HANDLE)&phy[j], &phy_id);
                    }
                    if(phy_id == phy[j].deviceID)
                    {
                        phydevice[i]   = &phy[j];
                        phy[j].addr    = (GD_ETH_PHY_AddrE)i;
                        initialized = GTRUE;
                        printf("find phy[%s] at:%d\n", phy[j].deviceName, i);
                        break;
                    }
                    else
                    {
                        phy[j].addr    = (GD_ETH_PHY_AddrE)(-1);
                    }
                }
                else if(phy[j].addr == i)
                {
                    phydevice[i]   = &phy[j];
                    phy[j].addr    = (GD_ETH_PHY_AddrE)i;
                    initialized = GTRUE;
                    printf("find phy[%s] at:%d\n", phy[j].deviceName, i);
                    break;
                }
                //GD_TIMER_Delay(2);
			    if(phyType != 0)
			    {
					for(a=0;a<100000;a++)
					{
						GH_ETH_get_GAR();
					}
			    }
            }
        }
    }
    phyhandle   = 0;
    return initialized ? GD_OK : GD_ERR_NO_DEVICE_DETECT;
}

GERR GD_ETH_PHY_Open(GD_ETH_PHY_AddrE* paddr, GD_HANDLE* pHandle)
{
    U32 i;
    GERR gerr;
    GD_ETH_PHY_DEVICE_DATA_S*    device;
    if (initialized == GFALSE)
    {
        return GD_ERR_NOT_INITIALIZED;
    }
    if(phyhandle)
    {
        return GD_ERR_ALREADY_OPEN;
    }
    if(*paddr==GD_ETH_PHY_EXTERNAL_AUTO)
    {
        for(i=0;i<GD_ETH_PHY_EXTERNAL_AUTO;i++)
        {
            if(phydevice[i] != NULL)
            {
                phyhandle = (GD_HANDLE)phydevice[i];
                *pHandle  = phyhandle;
                *paddr    = (GD_ETH_PHY_AddrE)i;
                //return GD_OK;
				goto PHY_INIT;
                //if(phyhandle)
                //{
                //    return GD_ERR_ALREADY_OPEN;
                //}
            }
        }
        return GD_ERR_ETH_PHY_NOT_EXIST;
    }
    if(phydevice[*paddr] == NULL)
    {
        return GD_ERR_ETH_PHY_NOT_EXIST;
    }
    phyhandle   = (GD_HANDLE)phydevice[*paddr];
    *pHandle = phyhandle;

PHY_INIT:
    device = phydevice[*paddr];
    if(device->GD_ETH_PHY_Init)
    {
        gerr =  device->GD_ETH_PHY_Init();
        if(gerr != GD_OK)
        {
            return gerr;
        }
    }
    if(device->GD_ETH_PHY_Open)
    {
        gerr =  device->GD_ETH_PHY_Open(phyhandle);
        if(gerr != GD_OK)
        {
            return gerr;
        }
    }
    return GD_OK;
}

GERR GD_ETH_PHY_Close(GD_HANDLE* pHandle)
{
    GERR gerr;
    GD_ETH_PHY_DEVICE_DATA_S* device;
    if (initialized == GFALSE)
    {
        return GD_ERR_NOT_INITIALIZED;
    }

    if (pHandle == NULL)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    device = (GD_ETH_PHY_DEVICE_DATA_S*)(*pHandle);
    /* call close function if any */
    if (device->GD_ETH_PHY_Close != NULL)
    {
        gerr = device->GD_ETH_PHY_Close(*pHandle);
        if (gerr != GD_OK)
        {
            return gerr;
        }
    }
    /* reset phyhandle */
    phyhandle = (GD_HANDLE)0;
    *pHandle = (GD_HANDLE)0;
    return GD_OK;
}

GERR GD_ETH_PHY_SWReset(GD_HANDLE handle)
{
    GERR gerr = GD_OK;
    GD_ETH_PHY_DEVICE_DATA_S* device;
    if (initialized == GFALSE)
    {
        return GD_ERR_NOT_INITIALIZED;
    }

    if (handle == 0)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    device = (GD_ETH_PHY_DEVICE_DATA_S*)(handle);
    if (device->GD_ETH_PHY_SWReset != NULL)
    {
        gerr = device->GD_ETH_PHY_SWReset(handle);
    }
    else
    {
        GBOOL   retval;
        U32     ulRegV;
        int     timeout = 500;  //0.5s
        U8      addr = device->addr;

        /* Firstly read BMCR */
        retval = GD_ETH_ReadPhy(addr, PHY_addr(0,BMCR), &ulRegV);
        if ( retval != GTRUE )
        {
            return GD_ERR_ETH_PHY_RW;
        }

        /* Set up the softreset bit */
        ulRegV |= PHY_val(0,RESET);

        /* reset PHY */
        retval = GD_ETH_WritePhy(addr, PHY_addr(0,BMCR), ulRegV);
        if ( retval != GTRUE )
        {
            return GD_ERR_ETH_PHY_RW;
        }

        /*
            * Poll the control register for the reset bit to go to 0 (it is
            * auto-clearing).  This should happen within 0.5 seconds per the
            * IEEE spec.
            */
        ulRegV = PHY_val(0,RESET);
        while (((ulRegV & PHY_mask(0,RESET)) == PHY_val(0,RESET)) && timeout--)
        {
            /* Get PHY status */
            if (GD_ETH_ReadPhy(addr, PHY_addr(0,BMCR), &ulRegV) == GFALSE)
            {
                return GD_ERR_ETH_PHY_RW;
            }

            /* Delay 1ms */
            GD_TIMER_Delay(1);
        }

        /* Determine the PHY status */
        if (ulRegV & PHY_mask(0,RESET))
        {
            return GD_ERR_ETH_PHY_RW;
        }
    }
    return gerr;
}

GERR GD_ETH_PHY_SetWorkMode(GD_HANDLE handle, GD_ETH_Work_ModeT workmode)
{
    GERR gerr = GD_OK;
    GD_ETH_PHY_DEVICE_DATA_S* device;
    U8      ii = 0;
    GBOOL   retval = GFALSE;
    U32     regval = (U32)0;
    U8      addr;
    if (initialized == GFALSE)
    {
        return GD_ERR_NOT_INITIALIZED;
    }

    if (handle == 0)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    device = (GD_ETH_PHY_DEVICE_DATA_S*)(handle);

    if (device->GD_ETH_PHY_SetWorkMode != NULL)
    {
        gerr = device->GD_ETH_PHY_SetWorkMode(handle, workmode);
    }
    else
    {
        /*Set MII mode: reg 25 bit 10---0:MII , 1:RMII*/
        addr = (U8)device->addr;

        // workmode.mode
        while(1)
        {
            regval = 0;
            retval = GD_ETH_ReadPhy(addr, PHY_addr(25,TESTR), &regval);
            if ( retval != GTRUE )
            {
                printf("%s:Failed to read PHY Reg_%d!\n",__FUNCTION__, PHY_addr(25,TESTR));
                return GD_ERR_ETH_PHY_RW;
            }

            if(workmode.mode == GD_ETH_PHY_IF_MODE_RMII)
            {
                /*RMII mode*/
                if((regval & PHY_mask(25,RPHY_MODE)) == PHY_val(25,RPHY_RMII))//MII mode: bit 10---0:MII , 1:RMII
                {
                    if((regval&PHY_mask(25,RPHY_CLKIN)) == PHY_mask(25,RPHY_CLKIN))
                    {
                        regval &= (~PHY_mask(25,RPHY_CLKIN));
                        printf("25-%08x\n",regval );
                        retval = GD_ETH_WritePhy(addr, PHY_addr(25,TESTR), regval);
                        if ( retval != GTRUE )
                        {
                            printf("%s:Failed to write PHY Reg_%d!\n",__FUNCTION__, PHY_addr(25,TESTR));
                            return GD_ERR_ETH_PHY_RW;
                        }
                    }
                    else
                    {
                        printf("Rmii mode set OK!\n");
                    }
                    break;
                }

                regval &= (~PHY_mask(25,RPHY_MODE));
                regval |= PHY_val(25,RPHY_RMII);
            }
            else if(workmode.mode == GD_ETH_PHY_IF_MODE_MII)
            {
                /*MII mode*/
                if((regval & PHY_mask(25,RPHY_MODE)) == PHY_val(25,RPHY_MII))//MII mode: bit 10---0:MII , 1:RMII
                {
                    printf("mii mode set OK!\n");
                    break;
                }

                regval &= (~PHY_mask(25,RPHY_MODE));
                regval |= PHY_val(25,RPHY_MII);
            }
            else
            {
                return GD_ERR_ETH_NOT_SUPPORTED;
            }

            retval = GD_ETH_WritePhy(addr, PHY_addr(25,TESTR), regval);
            if ( retval != GTRUE )
            {
                printf("%s:Failed to write PHY Reg_%d!\n",__FUNCTION__, PHY_addr(25,TESTR));
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
            // RMII mode RXD_3 used as 10/100M indicator
            if(workmode.mode == GD_ETH_PHY_IF_MODE_RMII)
            {
                GH_GPIO_set_INPUT_CFG_in_sel(GD_GPIO_GET_IN_SEL(GD_GPIO_TYPE_INPUT_ENET_PHY_RXD_3)-2, GD_GPIO_GET_IN_SEL(GD_GPIO_TYPE_INPUT_1));
            }
        }
        else
        {
            /* speed */
            // workmode.speed
            regval &= (~PHY_mask(0,SPEEDSELECT));
            if (workmode.speed == GD_ETH_SPEED_100M )   /* 100M */
            {
                regval |= PHY_val(0,100M);
                // RMII mode RXD_3 used as 10/100M indicator
                if(workmode.mode == GD_ETH_PHY_IF_MODE_RMII)
                {                
			GH_GPIO_set_INPUT_CFG_in_sel(GD_GPIO_GET_IN_SEL(GD_GPIO_TYPE_INPUT_ENET_PHY_RXD_3)-2, GD_GPIO_GET_IN_SEL(GD_GPIO_TYPE_INPUT_1));
                }
            }
            else if (workmode.speed == GD_ETH_SPEED_10M )/* 10M */
            {
                regval |= PHY_val(0,10M);    //nothing need to do.
                // RMII mode RXD_3 used as 10/100M indicator
                if(workmode.mode == GD_ETH_PHY_IF_MODE_RMII)
                {
			GH_GPIO_set_INPUT_CFG_in_sel(GD_GPIO_GET_IN_SEL(GD_GPIO_TYPE_INPUT_ENET_PHY_RXD_3)-2, GD_GPIO_GET_IN_SEL(GD_GPIO_TYPE_INPUT_0));                    
                }
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
    return gerr;
}

GERR GD_ETH_PHY_GetWorkStatus(GD_HANDLE handle, GD_ETH_StatParamsT* pStat)
{
    GERR gerr = GD_OK;
    GD_ETH_PHY_DEVICE_DATA_S* device;
    if (initialized == GFALSE)
    {
        return GD_ERR_NOT_INITIALIZED;
    }

    if (handle == 0)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    device = (GD_ETH_PHY_DEVICE_DATA_S*)(handle);

    if (device->GD_ETH_PHY_GetWorkStatus != NULL)
    {
        gerr = device->GD_ETH_PHY_GetWorkStatus(handle, pStat);
    }
    else
    {
        gerr = GD_ERR_FEATURE_NOT_SUPPORTED;
    }
    return gerr;
}

GERR GD_ETH_PHY_GetId(GD_HANDLE handle, U32 *phy_id)
{
    GERR gerr = GD_OK;
    GD_ETH_PHY_DEVICE_DATA_S* device;
    //if (initialized == GFALSE)
    //{
    //    return GD_ERR_NOT_INITIALIZED;
    //}

    if (handle == 0)
    {
        return GD_ERR_INVALID_HANDLE;
    }

    device = (GD_ETH_PHY_DEVICE_DATA_S*)(handle);

    if (device->GD_ETH_PHY_GetId != NULL)
    {
        gerr = device->GD_ETH_PHY_GetId(device->addr, phy_id);
    }
    else
    {
        GBOOL   retval;
        U32     ulPhyId;
        U8      addr = device->addr;

        /* Grab the bits from PHYIR1, and put them in the upper half */
        retval = GD_ETH_ReadPhy(addr, PHY_addr(2,ID1), &ulPhyId);
        if ( retval != GTRUE )
        {
#ifdef PRINT_ETH_LOG
            printf("%s:PHYID1 read failed!\n",__FUNCTION__);
#endif
            return GD_ERR_ETH_PHY_RW;
        }

        *phy_id = (ulPhyId & 0xffff) << 16;

        /* Grab the bits from PHYIR2, and put them in the lower half */
        retval = GD_ETH_ReadPhy(addr, PHY_addr(3,ID2), &ulPhyId);
        if ( retval != GTRUE )
        {
#ifdef PRINT_ETH_LOG
            printf("%s:PHYID2 read failed!\n",__FUNCTION__);
#endif
            return GD_ERR_ETH_PHY_RW;
        }

        *phy_id |= (ulPhyId & 0xffff);
    }
    return gerr;
}



//*****************************************************************************
//*****************************************************************************
//** Local Functions
//*****************************************************************************
//*****************************************************************************

