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
 * FilePath: fgmac_g.c
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

/*  - This file contains a configuration table that specifies the configuration
- 驱动全局变量定义，包括静态配置参数 */

/***************************** Include Files *********************************/

#include "fparameters.h"
#include "fgmac.h"

/************************** Constant Definitions *****************************/

const FGmacConfig FGMAC_CONFIG_TBL[GMAC_INSTANCE_NUM] =
{
    [GMAC_INSTANCE_0] =
    {
        .instance_id  = GMAC_INSTANCE_0,
        .base_addr = GMAC_INSTANCE_0_BASE_ADDR,
        .irq_num = GMAC_INSTANC_0_IRQ,
        .irq_prority = 0,
        .cheksum_mode = FGMAC_CHECKSUM_BY_SOFTWARE,
        .max_packet_size = GMAC_MAX_PACKET_SIZE
    },

    [GMAC_INSTANCE_1] =
    {
        .instance_id  = GMAC_INSTANCE_1,
        .base_addr = GMAC_INSTANCE_1_BASE_ADDR,
        .irq_num = GMAC_INSTANC_1_IRQ,
        .irq_prority = 0,
        .cheksum_mode = FGMAC_CHECKSUM_BY_SOFTWARE,
        .max_packet_size = GMAC_MAX_PACKET_SIZE
    }
};

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
