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

#include "fdc.h"
#include "fdp.h"
#include "ftypes.h"
#include "fparameters.h"
#include "fdcdp_param.h"

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

#define FDP_ALL_CHANNEL                           0xffffffff

#define FDP_MRAM_SIZE (3840 * 2160 * 4)


typedef enum
{
    FDCDP_HPD_IRQ_CONNECTED = 0, /* hpd 中断 */
    FDCDP_HPD_IRQ_DISCONNECTED,
    FDCDP_AUX_REPLY_TIMEOUT,
    FDCDP_AUX_REPLY_ERROR,

    FDCDP_INTR_MAX_NUM
} FDcDpIntrEventType;

typedef void (*FMediaIntrHandler)(void *param, u32 index);

typedef struct 
{
  FDcDpIntrEventType type;  /* data */
  FMediaIntrHandler  handler;
  void *param;
} FMediaIntrConfig;

typedef struct
{
    /* fdc instace object */
    FDcCtrl dc_instance_p[FDCDP_INSTANCE_NUM];
    /* fdp instace object */
    FDpCtrl dp_instance_p[FDCDP_INSTANCE_NUM];
    /* user config */
    /* resolution */
    /* color depth */
    FDcDpDisplaySetting display_setting[FDCDP_DISPLAY_ID_MAX_NUM];
    /* gamma parameter */
    /* .... */
    /* uintptr fb_p[FDCDP_INSTANCE_NUM];*/
    u32 is_ready; /* Device is ininitialized and ready*/
    FMediaIntrConfig intr_event[FDCDP_INTR_MAX_NUM];
    
    void *args;
    u32 connect_flg[FDCDP_INSTANCE_NUM];
    u32 connect_changed_flg[FDCDP_INSTANCE_NUM];
} FDcDp;

const FDpConfig *FDpLookupConfig(u32 instance_id);
const FDcConfig *FDcLookupConfig(u32 instance_id);
/*get the default config*/
FError FDcDpGetDefaultConfig(FDcDp *instance_p, u32 channel_num);

/*register the interrupt*/
void FDcDpRegisterHandler(FDcDp *instance_p, FMediaIntrConfig *intr_event_p);

/*the interrupt handler*/
void FDcDpInterruptHandler(s32 vector, void *args);

/*enable the interrupt*/
void FDcDpIrqEnable(FDcDp *instance_p, FDcDpIntrEventType intr_event_p);

/* init the DcDp */
FError FDcDpInitial(FDcDp *instance_p, u32 channel_num, u32 mode_id,u32 multi_mode);

/*the basic params init*/
FError FDcDpSetBasicParam(FDcDp *instance_p, u32 channel_num, u32 mode_id);

#endif
