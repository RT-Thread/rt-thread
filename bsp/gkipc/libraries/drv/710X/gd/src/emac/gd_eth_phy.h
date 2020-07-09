/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/emac/gd_eth_phy.h
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
#ifndef _GD_ETH_PHY_H_
#define _GD_ETH_PHY_H_
#include "gtypes.h"
#include "gd_ethernet.h"
#include "gd_eth_phy_reg.h"



//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
/*lint -emacro(835,PHY_*) */
#define PHY_addr(N,M)       (PHY_REG##N##_##M)
#define PHY_mask(N,F)       ((U32)(PHY_REG##N##_bit_##F) << (PHY_REG##N##_sft_##F))
#define PHY_val(N,V)        ((U32)(PHY_REG##N##_val_##V))
#define PHY_get_val(N,F,V)  (V&(PHY_msk(N,F))


//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************


//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************
typedef struct
{
    U32     deviceID;           // Device identification
    char*   manufactureName;    // Pointer to manufacture name
    char*   deviceName;         // Pointer to device name
    GERR    (*GD_ETH_PHY_Init)(void);
    GERR    (*GD_ETH_PHY_Open)(GD_HANDLE handle);
    GERR    (*GD_ETH_PHY_Close)(GD_HANDLE handle);
    GERR    (*GD_ETH_PHY_SWReset)(GD_HANDLE handle);
    GERR    (*GD_ETH_PHY_SetWorkMode)(GD_HANDLE handle, GD_ETH_Work_ModeT Mode);
    GERR    (*GD_ETH_PHY_GetWorkStatus)(GD_HANDLE handle, GD_ETH_StatParamsT* pStat);
    GERR    (*GD_ETH_PHY_GetId)(GD_HANDLE handle, U32 *phy_id);

    GD_ETH_PHY_AddrE    addr;
    GD_ETH_Work_ModeT   workmode;
}GD_ETH_PHY_DEVICE_DATA_S;
//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************



#ifdef __cplusplus
extern "C" {
#endif


GERR GD_ETH_PHY_Init(U8 phyType);
GERR GD_ETH_PHY_Open(GD_ETH_PHY_AddrE* paddr, GD_HANDLE* pHandle);
GERR GD_ETH_PHY_Close(GD_HANDLE* pHandle);
GERR GD_ETH_PHY_SWReset(GD_HANDLE handle);
GERR GD_ETH_PHY_SetWorkMode(GD_HANDLE handle, GD_ETH_Work_ModeT Mode);
GERR GD_ETH_PHY_GetWorkStatus(GD_HANDLE handle, GD_ETH_StatParamsT* pStat);
GERR GD_ETH_PHY_GetId(GD_HANDLE handle, U32 *phy_id);

#ifdef __cplusplus
}
#endif


#endif /* _GD_ETH_PHY_H_ */

