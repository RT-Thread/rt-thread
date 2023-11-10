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
 * FilePath: fpciec.c
 * Created Date: 2023-08-01 20:30:10
 * Last Modified: 2023-08-06 09:44:56
 * Description:  This file is for pciec initialization api
 *
 * Modify History:
 *  Ver      Who        Date               Changes
 * -----  ----------  --------  ---------------------------------
 * 1.0     huanghe    2023/08/06        first release
 */

#include "fpciec.h"
#include "ftypes.h"
#include "string.h"
#include "fassert.h"

/**
 * @name: FPcieCCfgInitialize
 * @msg: Initializes an instance of FPcieC using the provided configuration.
 * @param {FPcieC *} instance_p - Pointer to the FPcieC instance.
 * @param {FPcieCConfig *} config_p - Pointer to the FPcieCConfig configuration.
 * @return {FError} - Returns FT_SUCCESS if the initialization is successful.
 */
FError FPcieCCfgInitialize(FPcieC *instance_p, FPcieCConfig *config_p)
{
    /* Assert arguments */
    FASSERT(instance_p != NULL);
    FASSERT(config_p != NULL);

    /* Clear instance memory and make copy of configuration */
    memset(instance_p, 0, sizeof(FPcieC));
    memcpy(&instance_p->config, config_p, sizeof(FPcieCConfig));

    instance_p->is_ready = FT_COMPONENT_IS_READY;

    return FT_SUCCESS ;
}