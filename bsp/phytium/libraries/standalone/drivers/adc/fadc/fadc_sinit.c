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
 * FilePath: fadc_sinit.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-25 11:45:05
 * Description:  This files is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */


/***************************** Include Files *********************************/


#include "fparameters.h"
#include "fadc.h"
#include "fassert.h"

extern FAdcConfig FAdcConfigTbl[FADC_INSTANCE_NUM];

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/*****************************************************************************/

/**
 * @name: FAdcLookupConfig
 * @msg:  get default configuration of specific adc id.
 * @param {FAdcInstance} instance_id, instance id of FADC controller
 * @return {FAdcConfig*} Default configuration parameters of FADC
 */
const FAdcConfig *FAdcLookupConfig(FAdcInstance instance_id)
{
    const FAdcConfig *pconfig = NULL;
    FASSERT(instance_id < FADC_INSTANCE_NUM);

    u32 index = 0;

    for (index = 0; index < (u32)FADC_INSTANCE_NUM; index++)
    {
        if (FAdcConfigTbl[index].instance_id == instance_id)
        {
            pconfig = &FAdcConfigTbl[index];
            break;
        }
    }

    return (FAdcConfig *)pconfig;
}
