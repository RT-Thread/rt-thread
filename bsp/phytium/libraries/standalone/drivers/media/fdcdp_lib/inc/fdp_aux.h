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


#define AUX_TIMEOUT 1
#define AUX_CONNECT 0
#define dtd_list_max 4

typedef struct
{
    u32 pixel_clock;
    u32 hor_pixel;
    u32 ver_pixel;
    u32 hor_blanking;
    u32 ver_blanking;
    u32 hor_sync_front;
    u32 ver_sync_front;
    u32 hor_sync_width;
    u32 ver_sync_width;
    u8 hor_polarity;
    u8 ver_polarity;
} Auxtable;
/*Initialize AUX channel include aux clock Initialization, dp timer Initialization
  and interrupt mask. */
FError FDpInitAux(FDpCtrl *instance_p);

/*Wait util that an aux reply has been recieved*/
FError FDpWaitAuxReply(FDpCtrl *instance_p);

/*translate the dp information the dpsync*/
FError FDpTimingToDpSync(Auxtable *instance_p, FDpSyncParameter *sync);

/*translate the dc information the dcsync*/
FError FDpTimingToDcSync(Auxtable *instance_p, FDcSyncParameter *sync);

/* write phy register through aux channel.*/
FError FDpSinkDpcdWrite(FDpCtrl *instance_p, u32 addr, u8 data);

/* Read phy register through aux channel. */
FError FDpSinkDpcdRead(FDpCtrl *instance_p, u32 addr, u8 *data);

/* Get edid information form sink*/
FError FDpGetEdid(FDpCtrl *instance_p, u8 *buffer);

/*translate the edid information to the struct*/
FError FDpParseDpEdidDtdList(u8 *buffer, Auxtable *list);

#endif
