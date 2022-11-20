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
 * FilePath: fxmac_g.c
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#include "fxmac.h"
#include "fparameters.h"
#include "ftypes.h"
/************************** Constant Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Prototypes ******************************/

/*
 * The configuration table for emacps device
 */

const FXmacConfig fxmac_cfg_tbl[FT_XMAC_NUM] =
{
    [FT_XMAC0_ID] =
    {
        .instance_id = (u32)FT_XMAC0_ID,               /* Device ID */
        .base_address = (uintptr)FT_XMAC0_BASEADDRESS, /* Device base address */
        .extral_mode_base = FT_XMAC0_MODE_SEL_BASEADDRESS,
        .extral_loopback_base = FT_XMAC0_LOOPBACK_SEL_BASEADDRESS,
        .interface = FXMAC_PHY_INTERFACE_MODE_SGMII,
        .speed = 1000,
        .duplex = 1,
        .auto_neg = 1,
        .pclk_hz = FT_XMAC0_PCLK,
        .max_queue_num = 16,
        .tx_queue_id = 0,
        .rx_queue_id = 0,
        .hotplug_irq_num = FT_XMAC0_HOTPLUG_IRQ_NUM,
        .dma_brust_length = 16,
        .network_default_config = FXMAC_DEFAULT_OPTIONS,
        .queue_irq_num =
        {
            FT_XMAC0_QUEUE0_IRQ_NUM,
            FT_XMAC0_QUEUE1_IRQ_NUM,
            FT_XMAC0_QUEUE2_IRQ_NUM,
            FT_XMAC0_QUEUE3_IRQ_NUM,
            FT_XMAC0_QUEUE4_IRQ_NUM,
            FT_XMAC0_QUEUE5_IRQ_NUM,
            FT_XMAC0_QUEUE6_IRQ_NUM,
            FT_XMAC0_QUEUE7_IRQ_NUM
        }
    },
#ifdef FT_XMAC1_ID
    [FT_XMAC1_ID] =
    {
        .instance_id = (u32)FT_XMAC1_ID,               /* Device ID */
        .base_address = (uintptr)FT_XMAC1_BASEADDRESS, /* Device base address */
        .extral_mode_base = FT_XMAC1_MODE_SEL_BASEADDRESS,
        .extral_loopback_base = FT_XMAC1_LOOPBACK_SEL_BASEADDRESS,
        .interface = FXMAC_PHY_INTERFACE_MODE_SGMII,
        .speed = 1000,
        .duplex = 1,
        .auto_neg = 1,
        .pclk_hz = FT_XMAC1_PCLK,
        .max_queue_num = 4,
        .tx_queue_id = 0,
        .rx_queue_id = 0,
        .hotplug_irq_num = FT_XMAC1_HOTPLUG_IRQ_NUM,
        .dma_brust_length = 16,
        .network_default_config = FXMAC_DEFAULT_OPTIONS,
        .queue_irq_num =
        {
            FT_XMAC1_QUEUE0_IRQ_NUM,
            FT_XMAC1_QUEUE1_IRQ_NUM,
            FT_XMAC1_QUEUE2_IRQ_NUM,
            FT_XMAC1_QUEUE3_IRQ_NUM
        }
    },
#endif
#ifdef FT_XMAC2_ID
    [FT_XMAC2_ID] =
    {
        .instance_id = (u32)FT_XMAC2_ID,               /* Device ID */
        .base_address = (uintptr)FT_XMAC2_BASEADDRESS, /* Device base address */
        .extral_mode_base = FT_XMAC2_MODE_SEL_BASEADDRESS,
        .extral_loopback_base = FT_XMAC2_LOOPBACK_SEL_BASEADDRESS,
        .interface = FXMAC_PHY_INTERFACE_MODE_RGMII,
        .speed = 1000,
        .duplex = 1,
        .auto_neg = 1,
        .pclk_hz = FT_XMAC2_PCLK,
        .max_queue_num = 4,
        .tx_queue_id = 0,
        .rx_queue_id = 0,
        .hotplug_irq_num = FT_XMAC2_HOTPLUG_IRQ_NUM,
        .dma_brust_length = 16,
        .network_default_config = FXMAC_DEFAULT_OPTIONS,
        .queue_irq_num =
        {
            FT_XMAC2_QUEUE0_IRQ_NUM,
            FT_XMAC2_QUEUE1_IRQ_NUM,
            FT_XMAC2_QUEUE2_IRQ_NUM,
            FT_XMAC2_QUEUE3_IRQ_NUM
        }
    },
#endif
#ifdef FT_XMAC3_ID
    [FT_XMAC3_ID] =
    {
        .instance_id = (u32)FT_XMAC3_ID,               /* Device ID */
        .base_address = (uintptr)FT_XMAC3_BASEADDRESS, /* Device base address */
        .extral_mode_base = FT_XMAC3_MODE_SEL_BASEADDRESS,
        .extral_loopback_base = FT_XMAC3_LOOPBACK_SEL_BASEADDRESS,
        .interface = FXMAC_PHY_INTERFACE_MODE_RGMII,
        .speed = 1000,
        .duplex = 1,
        .auto_neg = 1,
        .pclk_hz = FT_XMAC3_PCLK,
        .max_queue_num = 4,
        .tx_queue_id = 0,
        .rx_queue_id = 0,
        .hotplug_irq_num = FT_XMAC3_HOTPLUG_IRQ_NUM,
        .dma_brust_length = 16,
        .network_default_config = FXMAC_DEFAULT_OPTIONS,
        .queue_irq_num =
        {
            FT_XMAC3_QUEUE0_IRQ_NUM,
            FT_XMAC3_QUEUE1_IRQ_NUM,
            FT_XMAC3_QUEUE2_IRQ_NUM,
            FT_XMAC3_QUEUE3_IRQ_NUM
        }
    }
#endif
};
/** @} */
