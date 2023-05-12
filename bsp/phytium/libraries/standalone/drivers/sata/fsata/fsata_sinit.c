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
 * FilePath: fsata_sinit.c
 * Date: 2022-02-10 14:55:11
 * LastEditTime: 2022-02-18 09:04:15
 * Description:  This file is for sata static init
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   wangxiaodong  2022/2/10    first release
 * 1.1   wangxiaodong  2022/10/21   improve functions
 */

/***************************** Include Files *********************************/

#include "fsata.h"
#include "fparameters.h"
#include "sdkconfig.h"
#include "fassert.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

extern const FSataConfig FSataPcieConfigTbl[PLAT_AHCI_HOST_MAX_COUNT];

#if defined(CONFIG_TARGET_E2000)
    extern const FSataConfig FSataControllerConfigTbl[FSATA_NUM];
#endif

/*****************************************************************************/
/**
 * @name: FSataLookupConfig
 * @msg: get sata configs by id and type, Support both pcie and SATA controllers
 * @return {FSataConfig *}
 * @param {u32} instance_id, id of sata ctrl
 */
const FSataConfig *FSataLookupConfig(u32 instance_id, u8 type)
{
    const FSataConfig *pconfig = NULL;
    if (type == FSATA_TYPE_CONTROLLER)
    {
#if defined(CONFIG_TARGET_E2000)
        FASSERT(instance_id < FSATA_NUM);
        pconfig = &FSataControllerConfigTbl[instance_id];
#endif
    }
    else
    {
        FASSERT(instance_id < PLAT_AHCI_HOST_MAX_COUNT);
        pconfig = &FSataPcieConfigTbl[instance_id];
    }

    return (const FSataConfig *)pconfig;
}

