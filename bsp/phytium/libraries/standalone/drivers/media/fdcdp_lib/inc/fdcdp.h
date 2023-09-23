/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc.
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
 * FilePath: fdcdp.h
 * Date: 2022-09-05 17:28:55
 * LastEditTime: 2022-09-05 17:28:55
 * Description:  This file is for providing the general config of dc and dp
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------  -------- --------------------------------------
 *  1.0  Wangzq     2022/12/20   Modify the format and establish the version
 */

#ifndef FDCDP_H
#define FDCDP_H

#include "ftypes.h"
#include "fparameters.h"
#include "fdc.h"
#include "fdp.h"

/************************** Constant Definitions *****************************/
#define FMEDIA_DEFAULT_PARAM_ERR FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 1)
#define FMEDIA_ERR_PIXEL FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 3)
#define FMEDIA_ERR_EDID FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 4)
#define FMEDIA_ERR_HPD_DISCONNECTED  FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 5)
#define FMEDIA_AUX_CONNECT_FAILED FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 7)
#define FMEDIA_TRAIN_TIME_ERR FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 8)
#define FMEDIA_REACH_MAX_VOLTAGE FT_MAKE_ERRCODE(ErrModBsp, ErrBspMEDIA, 9)

/************************** Constant Definitions *****************************/
#define FMEDIA_DCDP_SUCCESS FT_SUCCESS

#define FDP_DISPLAY_REFRESH_RATE_60 60
#define FDP_DISPLAY_REFRESH_RATE_59 59
#define FDP_DISPLAY_REFRESH_RATE_40 40
#define FDP_DISPLAY_REFRESH_RATE_30 30

#define FDP_DISPLAY_COLOR_DEPTH_32 32
#define FDP_DISPLAY_COLOR_DEPTH_16 16

#define FDP_EDP_LIGHTTURNON_CMD 101
#define FDP_EDP_LIGHTTURNOFF_CMD 102
#define FDP_EDP_OPENPWR_CMD 103
#define FDP_EDP_POWEROFF_CMD 104
#define FDP_LIGHT_ADJUST_CMD 0x1
#define FDP_CMD_STATE_OFFSET 28
#define FDP_LIGHT_VALUE_OFFSET 21

#define FDP_MRAM_SIZE (3840 * 2160 * 4)

#ifdef __cplusplus
extern "C"
{
#endif



/**************************** Type Definitions *******************************/


/**************************** Type Definitions *******************************/
typedef enum
{
    FDCDP_HPD_IRQ_CONNECTED = 0, /* dp disconnected */
    FDCDP_HPD_IRQ_DISCONNECTED, /*the dp disconnected*/
    FDCDP_AUX_REPLY_TIMEOUT, /*receive aux reply timeout*/
    FDCDP_AUX_REPLY_ERROR, /*the aux reply is invalid*/

    FDCDP_INTR_MAX_NUM
} FDcDpIntrEventType;

typedef enum
{
    FDCDP_CONNECT_TO_DISCONNCET = 0,
    FDCDP_DISCONNCET_TO_CONNECT
} FDcDpConnectStatus;

typedef void (*FMediaIntrHandler)(void *param, u32 index);

typedef struct
{
    FDcDpIntrEventType type;  /* the intr type */
    FMediaIntrHandler  handler;
    void *param;
} FMediaIntrConfig;

typedef struct
{
    /* fdc instace object */
    FDcCtrl dc_instance_p[FDCDP_INSTANCE_NUM];
    /* fdp instace object */
    FDpCtrl dp_instance_p[FDCDP_INSTANCE_NUM];
    /* u8 *fb_config[FDCDP_INSTANCE_NUM];*/
    u8 *fb_config[FDCDP_INSTANCE_NUM];
   /*the intr config of dcdp*/
    FMediaIntrConfig intr_event[FDCDP_INTR_MAX_NUM];
    /*connect status ,1 :connected,0:disconnected*/
    u32 connect_flg[FDCDP_INSTANCE_NUM];
    /* Device is ininitialized and ready*/
     u32 is_ready; 
} FDcDp;

/************************** Function Prototypes ******************************/
/*set the dp static params*/
const FDpConfig *FDpLookupConfig(u32 instance_id);

/*set the dc static params*/
const FDcConfig *FDcLookupConfig(u32 instance_id);

/*init the dcdp*/
FError FDcDpCfgInitialize(FDcDp *instance_p);

/*get the default config*/
FError FDcDpGetDefaultConfig(FDcDp *instance_p);

/*the basic params init*/
FError FDcDpSetBasicParam(FDcDp *instance_p, u32 width, u32 height,u32 color_depth, u32 refresh_rate);

/* init the DcDp */

FError FDcDpInitial(FDcDp *instance_p, u32 channel, u32 width, u32 height, u32 color_depth, u32 multi_mode);
/* deinit the DcDp */
FError FDcDpDeInitialize(FDcDp *instance_p, u32 id);

/*register the interrupt*/
void FDcDpRegisterHandler(FDcDp *instance_p, FDcDpIntrEventType type,FMediaIntrHandler  handler,void *param);

/*the interrupt handler*/
void FDcDpInterruptHandler(s32 vector, void *args);

/*enable the interrupt*/
void FDcDpIrqEnable(FDcDp *instance_p,u32 index, FDcDpIntrEventType intr_event_p);

/*the hotplug information*/
void FDcDpHotPlug(FDcDp *instance_p, u32 index, FDcDpConnectStatus connect_status);

#ifdef __cplusplus
}
#endif

#endif
