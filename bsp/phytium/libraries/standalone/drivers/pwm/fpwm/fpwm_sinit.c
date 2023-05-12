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
 * FilePath: fpwm_sinit.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-04-25 11:45:05
 * Description:  This file is for pwm static variables implementation.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/4/25   init commit
 */


/***************************** Include Files *********************************/

#include "fpwm.h"
#include "fparameters.h"
#include "fassert.h"

extern FPwmConfig FPwmConfigTbl[FPWM_NUM];

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/*****************************************************************************/

/**
 * @name: FPwmLookupConfig
 * @msg: get pwm configs by id
 * @return {*}
 * @param {u32} instanceId, id of pwm ctrl
 */
const FPwmConfig *FPwmLookupConfig(u32 instance_id)
{
    const FPwmConfig *pconfig = NULL;
    FASSERT(instance_id < FPWM_NUM);

    u32 index = 0;

    for (index = 0; index < (u32)FPWM_NUM; index++)
    {
        if (FPwmConfigTbl[index].instance_id == instance_id)
        {
            pconfig = &FPwmConfigTbl[index];
            break;
        }
    }

    return (FPwmConfig *)pconfig;
}