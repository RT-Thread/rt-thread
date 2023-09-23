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
 * FilePath: fiopad.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-04-15 11:45:05
 * Description: This file is for detailed description of the device configuration and driver.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhangyan  2023/7/4   init commit
 */

#ifndef  FIOPAD_H
#define  FIOPAD_H

/***************************** Include Files *********************************/
#include "ftypes.h"
#include "fparameters.h"
#include "fio.h"
#include "fkernel.h"
#include "fassert.h"
#include "fdebug.h"
#include "stdio.h"
#include "fpinctrl.h"
#include "fiopad_hw.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**************************** Type Definitions *******************************/
#define FIOPAD_SUCCESS      FT_SUCCESS
#define FIOPAD_INVAL_PARAM  FT_MAKE_ERRCODE(ErrModBsp, ErrBspIOPad, 1)
#define FIOPAD_NOT_READY    FT_MAKE_ERRCODE(ErrModBsp, ErrBspIOPad, 2)
#define FIOPAD_NOT_SUPPORT  FT_MAKE_ERRCODE(ErrModBsp, ErrBspIOPad, 3)

typedef enum
{
    FIOPAD_FUNC0 = 0b000,
    FIOPAD_FUNC1,
    FIOPAD_FUNC2,
    FIOPAD_FUNC3 = 0b011,
    FIOPAD_FUNC4,
    FIOPAD_FUNC5,
    FIOPAD_FUNC6,
    FIOPAD_FUNC7 = 0b111,

    FIOPAD_NUM_OF_FUNC
} FIOPadFunc; /* Pin multiplexing function configuration, func0 is the default function */

typedef enum
{
    FIOPAD_DRV0 = 0b0000,
    FIOPAD_DRV1,
    FIOPAD_DRV2,
    FIOPAD_DRV3,
    FIOPAD_DRV4,
    FIOPAD_DRV5,
    FIOPAD_DRV6,
    FIOPAD_DRV7,
    FIOPAD_DRV8,
    FIOPAD_DRV9,
    FIOPAD_DRV10,
    FIOPAD_DRV11,
    FIOPAD_DRV12,
    FIOPAD_DRV13,
    FIOPAD_DRV14,
    FIOPAD_DRV15 = 0b1111,

    FIOPAD_NUM_OF_DRIVE
} FIOPadDrive; /* Pin drive capability configuration */

typedef enum
{
    FIOPAD_PULL_NONE = 0b00,
    FIOPAD_PULL_DOWN = 0b01,
    FIOPAD_PULL_UP = 0b10,

    FIOPAD_NUM_OF_PULL
} FIOPadPull; /* Pin up pull-down configuration */

typedef enum
{
    FIOPAD_OUTPUT_DELAY = 0, /* Delay setting direction to output */
    FIOPAD_INPUT_DELAY, /* Delay setting direction to input */

    FIOPAD_NUM_OF_DELAY_DIR
} FIOPadDelayDir; /* Pin delay configuration direction */

typedef enum
{
    FIOPAD_DELAY_COARSE_TUNING = 0, /*delay coarse tuning */
    FIOPAD_DELAY_FINE_TUNING, /*delay fine tuning */

    FIOPAD_NUM_OF_DELAY_TYPE
} FIOPadDelayType; /* Pin delay configuration type */

typedef enum
{
    FIOPAD_DELAY_NONE = 0,
    FIOPAD_DELAY_1,
    FIOPAD_DELAY_2,
    FIOPAD_DELAY_3,
    FIOPAD_DELAY_4,
    FIOPAD_DELAY_5,
    FIOPAD_DELAY_6,
    FIOPAD_DELAY_7,

    FIOPAD_NUM_OF_DELAY
} FIOPadDelay;

typedef struct
{
    u32 instance_id; /* Device instance id */
    uintptr base_address; 

} FIOPadConfig;

typedef struct
{
    FIOPadConfig config;
    u32 is_ready;
    
} FIOPadCtrl; 
/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/* get iopad configs by id */
const FIOPadConfig *FIOPadLookupConfig(u32 instance_id);

/*Initializes a specific instance such that it is ready to be used*/
FError FIOPadCfgInitialize(FIOPadCtrl *instance_p, const FIOPadConfig *input_config_p);

/*get the current multiplexing function of IO pins*/
FIOPadFunc FIOPadGetFunc(FIOPadCtrl *instance_p, const u32 pin_reg_off);

/*set the multiplexing function of IO pins*/
FError FIOPadSetFunc(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadFunc func);

/*get the current up_down_pull configuration of IO pins*/
FIOPadPull FIOPadGetPull(FIOPadCtrl *instance_p, const u32 pin_reg_off);

/*set the up_down_pull configuration of IO pins*/
FError FIOPadSetPull(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadPull pull);

/*get the current driver strength of IO pins*/
FIOPadDrive FIOPadGetDriver(FIOPadCtrl *instance_p, const u32 pin_reg_off);

/*get the driver strength of IO pins*/
FError FIOPadSetDriver(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadDrive drive);

/*set the func, pull, driver strength */
FError FIOPadGetConfig(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadFunc *func, FIOPadPull *pull, FIOPadDrive *drive);

/*set the func, pull, driver strength */
FError FIOPadSetConfig(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadFunc func, FIOPadPull pull, FIOPadDrive drive);

/*get the current delay configuration of IO pins*/
FIOPadDelay FIOPadGetDelay(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadDelayDir dir, FIOPadDelayType type);

/*set the current delay configuration of IO pins*/
FError FIOPadSetDelay(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadDelayDir dir, FIOPadDelayType type, FIOPadDelay delay);

/*Enable/disable IO pin delay*/
FError FIOPadSetDelayEn(FIOPadCtrl *instance_p, const u32 pin_reg_off, FIOPadDelayDir dir, boolean enable);

/* DeInitialization function for the device instance */
FError FIOPadDeInitialize(FIOPadCtrl *instance_p);

#ifdef __cplusplus
}

#endif
#endif
