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
 * FilePath: fmhu_g.c
 * Date: 2022-12-29 16:41:46
 * LastEditTime: 2022-12-29 16:41:46
 * Description:  This file is for get default configs
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0 liushengming 2022/12/30 init
 */

#include <string.h>
#include "ftypes.h"
#include "fparameters.h"
#include "fmhu.h"
#include "fassert.h"

void FMhuGetDefConfig(FMhuConfig *config_p,u32 chan_id)
{
    FASSERT(NULL != config_p);

    memset(config_p, 0, sizeof(config_p));
    config_p->base_addr = FSCMI_MHU_BASE_ADDR;
    config_p->irq_num = FSCMI_MHU_IRQ_NUM;
    config_p->mhu_chan_id = chan_id;
    config_p->work_mode = TRUE;
}
