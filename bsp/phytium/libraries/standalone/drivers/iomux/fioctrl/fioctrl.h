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
 * FilePath: fioctrl.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-04-15 11:45:05
 * Description: This file is for user api definition of ioctrl
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2023/7/31   init commit
 */

#ifndef  FIOCTRL_H
#define  FIOCTRL_H

#ifdef __cplusplus
extern "C"
{
#endif

/***************************** Include Files *********************************/
#include "ftypes.h"
#include "ferror_code.h"

/************************** Constant Definitions *****************************/

#define FIOCTRL_SUCCESS      FT_SUCCESS
#define FIOCTRL_INVAL_PARAM  FT_MAKE_ERRCODE(ErrModBsp, ErrIoMux, 1)
#define FIOCTRL_NOT_READY    FT_MAKE_ERRCODE(ErrModBsp, ErrIoMux, 2)
#define FIOCTRL_NOT_SUPPORT  FT_MAKE_ERRCODE(ErrModBsp, ErrIoMux, 3)

/**************************** Type Definitions *******************************/
typedef enum
{
    FIOCTRL_FUNC0 = 0b000,
    FIOCTRL_FUNC1,
    FIOCTRL_FUNC2,
    FIOCTRL_FUNC3 = 0b011,

    FIOCTRL_NUM_OF_FUNC,
} FIOCtrlFunc; /* Pin multiplexing function configuration, func0 is the default function */

typedef enum
{
    FIOCTRL_PULL_NONE = 0b00,
    FIOCTRL_PULL_DOWN = 0b01,
    FIOCTRL_PULL_UP = 0b10,

    FIOCTRL_NUM_OF_PULL
} FIOCtrlPull; /* Pin up pull-down configuration */

typedef enum
{
    FIOCTRL_OUTPUT_DELAY = 0, /* pin output delay */
    FIOCTRL_INPUT_DELAY, /* pin input delay */

    FIOCTRL_NUM_OF_DELAY_DIR
} FIOCtrlDelayDir; /* Pin in/out delay direction */

typedef enum
{
    FIOCTRL_DELAY_COARSE_TUNING = 0, /* pin dealy corase tuning 粗调档位 */
    FIOCTRL_DELAY_FINE_TUNING, /* pin dealy fine tuning 精调档位 */

    FIOCTRL_NUM_OF_DELAY_TYPE
} FIOCtrlDelayType; /* Pin delay tuning type */

typedef enum
{
    FIOCTRL_DELAY_NONE = 0,
    FIOCTRL_DELAY_1,
    FIOCTRL_DELAY_2,
    FIOCTRL_DELAY_3,
    FIOCTRL_DELAY_4,
    FIOCTRL_DELAY_5,
    FIOCTRL_DELAY_6,
    FIOCTRL_DELAY_7,

    FIOCTRL_NUM_OF_DELAY
} FIOCtrlDelay; /* Pin delay tuning setting */

typedef struct
{
    u32 reg_off; /* 引脚配置寄存器偏移量 */
    u32 reg_bit; /* 引脚配置起始位 */
} FIOCtrlPinIndex;

typedef struct
{
    u32 instance_id; /* Device instance id */
    uintptr base_address;
} FIOCtrlConfig;

typedef struct
{
    FIOCtrlConfig config;
    u32 is_ready;
} FIOCtrl;
/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/* get ioctrl configs by id */
const FIOCtrlConfig *FIOCtrlLookupConfig(u32 instance_id);

/*Initializes a specific instance such that it is ready to be used*/
FError FIOCtrlCfgInitialize(FIOCtrl *instance_p, const FIOCtrlConfig *input_config_p);

/*De-inializes the instance*/
void FIOCtrlDeInitialize(FIOCtrl *instance_p);

/*get the current multiplexing function of IO pins*/
FIOCtrlFunc FIOCtrlGetFunc(FIOCtrl *instance_p, const FIOCtrlPinIndex pin);

/*set the multiplexing function of IO pins*/
FError FIOCtrlSetFunc(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlFunc func);

/*get the current up_down_pull configuration of IO pins*/
FIOCtrlPull FIOCtrlGetPull(FIOCtrl *instance_p, const FIOCtrlPinIndex pin);

/*set the up_down_pull configuration of IO pins*/
FError FIOCtrlSetPull(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlPull pull);

/*set the func, pull */
FError FIOCtrlGetConfig(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlFunc *func, FIOCtrlPull *pull);

/*set the func, pull */
FError FIOCtrlSetConfig(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlFunc func, FIOCtrlPull pull);

/*get the current delay configuration of IO pin*/
FIOCtrlDelay FIOCtrlGetDelay(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlDelayDir dir, FIOCtrlDelayType type);

/*set the current delay configuration of IO pin*/
FError FIOCtrlSetDelay(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlDelayDir dir, FIOCtrlDelayType type, FIOCtrlDelay delay);

/*enable/disable current delay configuration for IO pin*/
FError FIOCtrlSetDelayEn(FIOCtrl *instance_p, const FIOCtrlPinIndex pin, FIOCtrlDelayDir dir, boolean enable);

#ifdef __cplusplus
}

#endif
#endif