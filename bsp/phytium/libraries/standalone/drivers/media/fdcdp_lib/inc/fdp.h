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
 * FilePath: fdp.h
 * Date: 2022-09-08 14:53:42
 * LastEditTime: 2022-09-08 14:53:42
 * Description:  This file is for defining the dp config and function
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 *  1.0  Wangzq     2022/12/20   Modify the format and establish the version
 */

#ifndef FDP_H
#define FDP_H

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fparameters_comm.h"
#include "fdcdp_param.h"
#include "fdc.h"

/************************** Constant Definitions *****************************/
#define FMEDIA_DP_SUCCESS FT_SUCCESS

/************************** Constant Definitions *****************************/

#define FDP_HAS_TRAINED 1
#define FDP_NOT_TRAINED 0

#define FDP_IS_HPD_ON 1
#define FDP_IS_HPD_OFF 0

#define FDP_DIS_CONNECTED 1
#define FDP_IS_CONNECTED 0

#define DP_GOP_MAX_MODENUM 11

typedef enum
{
    FDP_TRAINING_OFF = 0,
    FDP_TRAINING_PATTERN_1,
    FDP_TRAINING_PATTERN_2,
    FDP_TRAINING_PATTERN_3
} FDpTrainPattern;

typedef enum
{
    FDP_BIT_DEPTH_6 = 0,
    FDP_BIT_DEPTH_8,
    FDP_BIT_DEPTH_10,
    FDP_BIT_DEPTH_12,
    FDP_BIT_DEPTH_16,
    FDP_BIT_DEPTH_RESERVE
} FDpBitDepth;

typedef enum
{
    FDP_PWR_MODE_D0 = 1,
    FDP_PWR_MODE_D3 = 2,
} FDpPwrMode; /* the power state of dp_phy */

typedef struct
{
    u16 h_total;
    u16 v_total;
    boolean h_polarity;      /*0 - active high , 1 - active low  */
    boolean v_polarity;      /*0 - active high , 1 - active low   */
    u16 hs_width;            /* Horizontal Sync Pulse Width in pixels. */
    u16 vs_width;            /* Vertical Sync Pulse Width in lines. */
    u16 h_res;               /* Horizontal Addressable video in lines. */
    u16 v_res;               /* Vertical Addressable video in lines. */
    u16 h_start;             /* Horizontal Blanking in pixels minus  Horizontal Front Proch in pixels. */
    u16 v_start;             /* Vertical Blanking in pixels minus  Vertical Front Proch in pixels. */
    boolean h_user_polarity; /* Horizontal Sync Polarity. */
    boolean v_user_polarity; /* Vertical Sync Polarity. */
} FDpSyncParameter;

typedef struct
{
    u32 lane_count;      /* The Number of lanes */
    u32 link_rate;       /* Main link bandwidth. 162 - 1.62   270 - 2  540 -  810 - 8.1G */
    u8 bit_depth;        /* Bit depth per color.For example , 6 means that Bit depth per color is 6 bits. */
    u8 color_rep_format; /* Color representation format. 0 - RGB , 1 - YCbCr 4:2:2 , 2 - YCbCr 4:4:4 , other - Reserved. */
    u8 clock_mode;       /* clock_mode   Clocking mode for the user data. 0 - asynchronous clock , 1 - synchronous clock. */
    u32 pixel_clock;     /* pixel clock frequence in megahertz unit */
    u8 transfer_size;    /* Transfer unit size.This parameter is usually 64. */
    u8 dis_type;         /* index of video mode description structure */
} FDpTransmissionConfig;

typedef struct
{
    u32 dp_hpd_on;  /* whether the dp is connected or not，1-connected，0-disconnected */
    u32 dp_trained; /* whether the dp has been trained or not，1-trained，0-distrained */
    u32 dp_connect; /* whether the source has been connected with sink or not ,1-trained，0-distrained */
} FDpStatus;

typedef struct
{
    u32 pixel_clock; /* the pixelclock of dp */
    u32 horPixel;   /* horizontal pixel */
    u32 verPixel;   /*vertical pixel */
    FDpSyncParameter sync_parameter[DP_GOP_MAX_MODENUM];
} FDpDtdTable;

typedef struct
{
    /* 设置参数 */
    FDpSyncParameter sync_parameter[DP_GOP_MAX_MODENUM];

    FDpTransmissionConfig transmission_config;

    /* 当前状态 */
    FDpStatus status;

    u8 down_spread_enable;
#define dtd_list_max 4
    /* edid 缓冲数据 */
    FDpDtdTable dtd_table[dtd_list_max]; /* the max dtd num is 4 */

} FDpCurrentConfig;

typedef struct
{
    u32 instance_id;
    uintptr dp_channe_base_addr;
    uintptr dp_phy_base_addr;
    u32 irq_num;
} FDpConfig;

typedef struct
{
    FDpCurrentConfig fdp_current_config;
    FDpConfig config;
} FDpCtrl;

/* dp init */
FError FDpInit(FDcCtrl *dc_config, FDpCtrl *instance_p, FDcDpDisplaySetting *gop_mode, u32 mode_id);

/* Initialization of dp configuration parameter */
void FDpConfigInit(FDpCtrl *instance_p, FDcDpDisplaySetting *gop_mode);

/* Dp connect to sink */
FError FDpConnect(FDpCtrl *instance_p);

/* Convert display resolution number to pixel clock frequence in megahertz unit */
FError FDpDistypeToPixelClock(u8 mode_Num);

/* sets the output of the transmitter core to the specified training pattern */
void FDpConfigTxTrainingPattern(FDpCtrl *instance_p, FDpTrainPattern train_pattern);

/* Force the transmitter core to use the alternate scrambler reset value */
FError FDpConfigTraingPattern(FDpCtrl *instance_p);

/* Config Main Stream Attributes.It is must to reset reset phy link after main
  stream attributes configuration*/
void FDpConfigMainStreamAttr(FDpCtrl *instance_p, FDpTransmissionConfig *fdp_trans_config, FDpSyncParameter *fdp_sync_config);

/*Dp link training*/

/*Set sink device to D0(normal operation mode).*/
FError FDpWakeUpSink(FDpCtrl *instance_p);

FError FDpStartLinkTrain(FDpCtrl *instance_p, u8 lane_count, u32 link_rate);

/* Get the status of all lanes */
FError FDpTxGetTrainingStatus(FDpCtrl *instance_p, u8 *train_status);

/* Determine whether retraining is needed at present.*/
FError FDpSinkNeedReTrain(FDpCtrl *instance_p); /* not use*/

/*Check the overall training status of the specified nameber of lanes and Tps type.*/
FError FDpCheckTrainingStatus(FDpCtrl *instance_p, u8 lane_count, u8 tpsn, u8 *value);

/*Check the HPD status*/
FError FDpCheckHpdStatus(FDpCtrl *instance_p);

#endif
