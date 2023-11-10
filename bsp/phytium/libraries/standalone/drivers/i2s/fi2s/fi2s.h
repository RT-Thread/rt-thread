/*
 * Copyright : (C) 2023 Phytium Information Technology, Inc.
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
 * FilePath: fi2s.h
 * Created Date: 2023-05-09 11:15:39
 * Last Modified: 2023-09-27 19:05:39
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------  -------- --------------------------------------
 *  1.0  Wangzq     2023/05/09  Modify the format and establish the version
 */


#ifndef FI2S_H
#define FI2S_H

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "ferror_code.h"
#ifdef __cplusplus
extern "C"
{
#endif
/************************** Constant Definitions *****************************/

#define FI2S_SUCCESS                          FT_SUCCESS
#define FI2S_ERR_NOT_INIT                     FT_MAKE_ERRCODE(ErrModBsp, ErrBspI2s, 0)
#define FI2S_ERR_CONFIG_SET_FAILED                     FT_MAKE_ERRCODE(ErrModBsp, ErrBspI2s, 1)

/**************************** Type Definitions *******************************/
#define FI2s_Clk_Base  600000000


typedef enum
{
    FI2S_INTR_TRANS_FO = 0, /*trans fifo overflow*/
    FI2S_INTR_TRANS_FE = 1, /*trans fifo idle*/
    FI2S_INTR_RECEIVE_FO = 2, /*receive fifo overflow*/
    FI2S_INTR_RECEIVE_FE = 3, /*receive fifo idle*/

    FI2S_INTR_EVENT_NUM
} FI2SIntrEventType;

typedef enum
{
    FI2S_CAPTURE = 0,      /* i2s capture mode */
    FI2S_PALYBACK = 1,     /* i2s playback mode */
} FI2sWorkMode;

typedef enum
{
    FI2S_12BIT_LR = 1, /*the bit length of resplution*/
    FI2S_16BIT_LR = 2,
    FI2S_24BIT_LR = 3,
    FI2S_32BIT_LR = 4,

    FI2S_RESPLUTION
} FI2sResplution;

typedef enum
{
    FI2S_WORLD_LENGTH_16 = 0, /*the length of trans word*/
    FI2S_WORLD_LENGTH_20,
    FI2S_WORLD_LENGTH_24,
    FI2S_WORLD_LENGTH_32,
} FI2sDataWidth;

typedef enum
{
    FI2S_SAMPLE_RATE_PHONE = 8000,
    FI2S_SAMPLE_RATE_DAT = 32000,
    FI2S_SAMPLE_RATE_CD = 44100,
    FI2S_SAMPLE_RATE_DV = 48000,
    FI2S_SAMPLE_RATE_DVD = 96000,
} FI2sDataSampleRate;

typedef struct
{
    u32 word_length;  /*the word length of i2s data*/
    u32 data_length;  /*the data length of i2s data*/
    u32 sample_rate;   /*the sample rate of i2s data*/
    u32 resolution;    /*the resolution i2s data*/
    u32 work_mode;     /*the work mode of i2s*/
} FI2sData;

typedef void (*FI2SIntrEventHandler)(void *param);

typedef struct
{
    u32 instance_id;
    uintptr base_addr;
    u32 irq_num;
    u32 irq_prority;
} FI2sConfig;

typedef struct
{
    FI2sConfig  config;
    u32         is_ready;
    FI2SIntrEventHandler event_handler[FI2S_INTR_EVENT_NUM];
    void *event_param[FI2S_INTR_EVENT_NUM];   /* parameters of event handler */
    FI2sData    data_config;
} FI2s;

const FI2sConfig *FI2sLookupConfig(u32 instance_id);
/*init the config of i2s*/
FError FI2sCfgInitialize(FI2s *instance, const FI2sConfig *config_p);
/*deinit the config of i2s*/
void FI2sDeInitialize(FI2s *instance);

/*diable the all channel*/
void FI2sChannelDisable(FI2s *instance);

/*set the hw config*/
void FI2sSetHwconfig(FI2s *instance);

/*enables/disables the i2s driver*/
void FI2sTxRxEnable(FI2s *instance, boolean enable);

/*enables i2s receiver and set the hw config*/
void FI2sRxHwEnable(FI2s *instance);

/*enables i2s playbacker and set the hw config*/
void FI2sTxHwEnable(FI2s *instance);

/*  set the i2s clk and resolution*/
FError FI2sClkOutDiv(FI2s *instance);

/*enable i2s irq*/
void FI2sEnableIrq(FI2s *instance, u32 event_type);

/*disable i2s irq*/
void FI2sDisableIrq(FI2s *instance,  u32 event_type);

/*stop the i2s*/
void FI2sStopWork(FI2s *instance_p);

void FI2sIntrHandler(s32 vector, void *args);

void FI2sRegisterInterruptHandler(FI2s *instance, FI2SIntrEventType event_type,
                                  FI2SIntrEventHandler handler, void *param);
#ifdef __cplusplus
}
#endif

#endif