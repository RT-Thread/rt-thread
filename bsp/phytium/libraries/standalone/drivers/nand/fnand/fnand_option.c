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
 * FilePath: fnand_option.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:56:51
 * Description:  This file is for options functions for the fnand component.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/05/10    first release
 */


#include "fnand.h"
#include "fnand_hw.h"

/**
 * @name: FNandSetOption
 * @msg:
 * @note:
 * @param {FNand} *instance_p is the pointer to the FNand instance.
 * @param {u32} options is configuration options ，use FNAND_OPS_INTER_MODE_SELECT to select nand flash interface
 * @param {u32} value is set value
 * @return {FError}  FT_SUCCESS set option is ok ，FNAND_ERR_INVAILD_PARAMETER options is invalid
 */
FError FNandSetOption(FNand *instance_p, u32 options, u32 value)
{
    u32 reg_value;
    FNandConfig *config_p;
    FASSERT(instance_p != NULL);
    FASSERT(instance_p->is_ready == FT_COMPONENT_IS_READY);
    config_p = &instance_p->config;

    switch (options)
    {
        case FNAND_OPS_INTER_MODE_SELECT:
            FASSERT(FNAND_TOG_ASYN_DDR >= value) ;
            FNAND_CLEARBIT(config_p->base_address, FNAND_CTRL0_OFFSET, FNAND_CTRL0_INTER_MODE(3UL)) ;
            FNAND_SETBIT(config_p->base_address, FNAND_CTRL0_OFFSET, FNAND_CTRL0_INTER_MODE((unsigned long)value)) ;
            break;
        default:
            return FNAND_ERR_INVAILD_PARAMETER;
    }

    return FT_SUCCESS;
}


