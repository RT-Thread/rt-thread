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
 * FilePath: fsdmmc_dma.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:51:25
 * Description:  This file is dma descriptormanagement API.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2021/12/2    init
 */

#ifndef  FSDMMC_DMA_H
#define  FSDMMC_DMA_H
/***************************** Include Files *********************************/
#include "ftypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
/* 设置读数据DMA配置 */
void FSdmmcSetReadDMA(uintptr base_addr, uintptr card_addr, u32 blk_cnt, void *buf_p);

/* 设置写数据DMA配置 */
void FSdmmcSetWriteDMA(uintptr base_addr, uintptr card_addr, u32 blk_cnt, const void *buf_p);

#ifdef __cplusplus
}
#endif

#endif
