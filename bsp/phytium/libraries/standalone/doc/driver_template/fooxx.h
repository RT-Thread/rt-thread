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
 * FilePath: fooxx.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:35
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


#ifndef  DRIVERS_模块名_FOOXX_H
#define  DRIVERS_模块名_FOOXX_H

#ifdef __cplusplus
extern "C"
{
#endif

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fassert.h"

/************************** Constant Definitions *****************************/

/* Configuration options */
#define FOOXX_OPTION_XX

/* Operational Mode */

#define FOOXX_OPER_MODE_XX

/**************************** Type Definitions *******************************/

/**
 * This typedef contains configuration information for the device.
 */
typedef struct
{
    u32     instance_id; /**< Device instance id */
    uintptr base_addr; /**< Device base address */
} FooxxConfig;

/**
 * This typedef contains driver instance data. The user is required to allocate a
 * variable of this type for every device in the system. A pointer
 * to a variable of this type is then passed to the driver API functions.
 */
typedef struct
{
    FooxxConfig config;      /**< Current active configs */
    u32         is_ready;    /**< Device is initialized and ready */
} Fooxx; /**< Device instance */

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
/**
 * @name: FXxxLookupConfig
 * @msg: Get the device instance default configure
 * @return {*}
 * @param {u32} instance_id
 */
const FooxxConfig *FXxxLookupConfig(u32 instance_id);

/*
 * @name: FooxxCfgInitialize
 * @msg:  Initializes a specific instance such that it is ready to be used.
 * @param {Fooxx} *instance_p is a pointer to the driver instance.
 * @param {FooxxConfig} *config_p is a reference to a structure containing information
 *                      about a specific driver.
 * @return SUCCESS if initialization was successful
 *         ERROR
 */
FError FooxxCfgInitialize(Fooxx *instance_p, const FooxxConfig *cofig_p);

/**
 * @name: FooxxDeInitialize
 * @msg: DeInitialization function for the device instance
 * @return {*}
 * @param {Fooxx} *instance_p
 */
void FooxxDeInitialize(Fooxx *instance_p);

#ifdef __cplusplus
}
#endif


#endif
