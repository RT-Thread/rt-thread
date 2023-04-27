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
 * FilePath: fmhu.c
 * Date: 2022-12-29 18:07:32
 * LastEditTime: 2022-12-29 18:07:32
 * Description:  This file is for mhu channel binding
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0 liushengming 2023/01/04 init
 */

#include "fassert.h"
#include "fmhu.h"
#include "fmhu_hw.h"
/**
 * @name: 
 * @msg: 
 * @return {*}
 * @param {FScmiMhu} *instance_p
 * @param {int} chan
 */
void FMhuChanProbe(FScmiMhu *instance_p)
{
    FASSERT(instance_p);

    instance_p->tx_complete = FALSE;
    instance_p->msg_count = 0U;

    instance_p->send_data = FMhuSendData;
    instance_p->startup = FMhuStartup;
    instance_p->shutdown = FMhuShutdown;
    instance_p->last_tx_done = FMhuLastTxDone;

    instance_p->mhu.is_ready = FT_COMPONENT_IS_READY;

    instance_p->startup(instance_p->mhu.config.base_addr);
    return;
}

/**
 * @name: 
 * @msg: 
 * @return {*}
 * @param {FScmiMhu} *instance_p
 * @param {int} chan
 */
void FMhuChanRemove(FScmiMhu *instance_p)
{
    FASSERT(instance_p);

    instance_p->tx_complete = TRUE;

    instance_p->send_data = NULL;
    instance_p->startup = NULL;
    instance_p->shutdown = NULL;
    instance_p->last_tx_done = NULL;

    instance_p->mhu.is_ready = 0U;

    instance_p->shutdown(instance_p->mhu.config.base_addr);
    return;
}
