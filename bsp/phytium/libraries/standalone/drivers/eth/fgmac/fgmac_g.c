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
 * Description:  This file is for configuration table that specifies the configuration of
 * ethernet devices .
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/07/13    first release
 */

/*  - This file contains a configuration table that specifies the configuration
- 驱动全局变量定义，包括静态配置参数 */

/***************************** Include Files *********************************/

#include "fparameters.h"
#include "fgmac.h"
#include "fgmac_phy.h"

/************************** Constant Definitions *****************************/

const FGmacConfig FGMAC_CONFIG_TBL[FGMAC_NUM] =
{
    [FGMAC0_ID] =
    {
        .instance_id  = FGMAC0_ID,
        .base_addr = FGMAC0_BASE_ADDR,
        .irq_num = FGMAC0_IRQ_NUM,
        .irq_prority = 0,
        .cheksum_mode = FGMAC_CHECKSUM_BY_SOFTWARE,
        .max_packet_size = FGMAC_MAX_PACKET_SIZE,
        .mdc_clk_hz = FGMAC_PHY_MII_ADDR_CR_250_300MHZ,
    },

    [FGMAC1_ID] =
    {
        .instance_id  = FGMAC1_ID,
        .base_addr = FGMAC1_BASE_ADDR,
        .irq_num =  FGMAC1_IRQ_NUM,
        .irq_prority = 0,
        .cheksum_mode = FGMAC_CHECKSUM_BY_SOFTWARE,
        .max_packet_size = FGMAC_MAX_PACKET_SIZE,
        .mdc_clk_hz = FGMAC_PHY_MII_ADDR_CR_250_300MHZ,
    }
};

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
