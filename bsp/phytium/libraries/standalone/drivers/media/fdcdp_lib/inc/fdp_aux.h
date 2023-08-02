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
 * FilePath: fdp_aux.h
 * Date: 2022-09-08 14:53:42
 * LastEditTime: 2022-09-08 14:53:42
 * Description:  This file is for Handling the aux register and
 *               providing some function interface
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 *  1.0  Wangzq     2022/12/20   Modify the format and establish the version
 */
#ifndef FDP_AUX_H
#define FDP_AUX_H
/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fdp.h"
#ifdef __cplusplus
extern "C"
{
#endif
/************************** Constant Definitions *****************************/

#define AUX_TIMEOUT 1
#define AUX_CONNECT 0
#define DTD_MAX 4

/**************************** Type Definitions *******************************/
typedef struct
{
    u32 pixel_clock;    /* pixel clock frequence in megahertz unit */
    u32 hor_pixel;      /* Horizontal total  lines. */
    u32 ver_pixel;      /* Vertical total lines. */
    u32 hor_blanking;    /* Horizontal Blanking in pixels minus*/
    u32 ver_blanking;     /* Vertical Blanking in pixels minus*/
    u32 hor_sync_front;   /*Horizontal Front Proch in pixels.  */
    u32 ver_sync_front;   /*vertical Front Proch in pixels. */
    u32 hor_sync_width;    /* Horizontal Sync Pulse Width in pixels. */
    u32 ver_sync_width;    /* Vertical Sync Pulse Width in lines. */
    u8 hor_polarity;      /*0 - active high , 1 - active low  */
    u8 ver_polarity;      /*0 - active high , 1 - active low   */
} Auxtable;

/************************** Function Prototypes ******************************/

/*Initialize AUX channel include aux clock Initialization, dp timer Initialization
  and interrupt mask. */
FError FDpInitAux(FDpCtrl *instance_p);

/*Wait util that an aux reply has been recieved*/
FError FDpWaitAuxReply(FDpCtrl *instance_p);

/*translate the dp information the dpsync*/
FError FDpTimingToDpSync(Auxtable *list, FDpSyncParameter *sync);

/*translate the dc information the dcsync*/
FError FDpTimingToDcSync(Auxtable *list, FDcSyncParameter *sync);

/* write phy register through aux channel.*/
FError FDpSinkDpcdWrite(FDpCtrl *instance_p, uintptr addr, u8 data);

/* Read phy register through aux channel. */
FError FDpSinkDpcdRead(FDpCtrl *instance_p, uintptr addr, u8 *data);

/* Get edid information form sink*/
FError FDpGetEdid(FDpCtrl *instance_p, u8 *buffer);

/*translate the edid information to the struct*/
FError FDpParseDpEdidDtdList(u8 *buffer, Auxtable *list);

#ifdef __cplusplus
}
#endif

#endif
