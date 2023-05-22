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
 * Description:  This file provide a template for user to define their own hardware settings.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2022/06/16    first release
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

const FXmacConfig fxmac_cfg_tbl[FXMAC_NUM] =
{
    [FXMAC0_ID] =
    {
        .instance_id = (u32)FXMAC0_ID,               /* Device ID */
        .base_address = (uintptr)FXMAC0_BASE_ADDR, /* Device base address */
#if defined(FXMAC0_MODE_SEL_BASE_ADDR)
        .extral_mode_base = FXMAC0_MODE_SEL_BASE_ADDR,
#endif
#if defined(FXMAC0_LOOPBACK_SEL_BASE_ADDR)
        .extral_loopback_base = FXMAC0_LOOPBACK_SEL_BASE_ADDR,
#endif
        .interface = FXMAC_PHY_INTERFACE_MODE_SGMII,
        .speed = 1000,
        .duplex = 1,
        .auto_neg = 1,
        .pclk_hz = FXMAC0_PCLK,
        .max_queue_num = 16,
        .tx_queue_id = 0,
        .rx_queue_id = 0,
#ifdef FXMAC0_HOTPLUG_IRQ_NUM
        .hotplug_irq_num = FXMAC0_HOTPLUG_IRQ_NUM,
#endif
        .dma_brust_length = 16,
        .network_default_config = FXMAC_DEFAULT_OPTIONS,
        .queue_irq_num =
        {
            FXMAC0_QUEUE0_IRQ_NUM,
            FXMAC0_QUEUE1_IRQ_NUM,
            FXMAC0_QUEUE2_IRQ_NUM,
            FXMAC0_QUEUE3_IRQ_NUM,
#if defined(FXMAC0_QUEUE4_IRQ_NUM)
            FXMAC0_QUEUE4_IRQ_NUM,
#endif
#if defined(FXMAC0_QUEUE5_IRQ_NUM)
            FXMAC0_QUEUE5_IRQ_NUM,
#endif
#if defined(FXMAC0_QUEUE6_IRQ_NUM)
            FXMAC0_QUEUE6_IRQ_NUM,
#endif
#if defined(FXMAC0_QUEUE7_IRQ_NUM)
            FXMAC0_QUEUE7_IRQ_NUM
#endif
        }
    },
#ifdef FXMAC1_ID
    [FXMAC1_ID] =
    {
        .instance_id = (u32)FXMAC1_ID,               /* Device ID */
        .base_address = (uintptr)FXMAC1_BASE_ADDR, /* Device base address */
        .extral_mode_base = FXMAC1_MODE_SEL_BASE_ADDR,
        .extral_loopback_base = FXMAC1_LOOPBACK_SEL_BASE_ADDR,
        .interface = FXMAC_PHY_INTERFACE_MODE_SGMII,
        .speed = 1000,
        .duplex = 1,
        .auto_neg = 1,
        .pclk_hz = FXMAC1_PCLK,
        .max_queue_num = 4,
        .tx_queue_id = 0,
        .rx_queue_id = 0,
#if defined(FXMAC1_HOTPLUG_IRQ_NUM)
        .hotplug_irq_num = FXMAC1_HOTPLUG_IRQ_NUM,
#endif
        .dma_brust_length = 16,
        .network_default_config = FXMAC_DEFAULT_OPTIONS,
        .queue_irq_num =
        {
            FXMAC1_QUEUE0_IRQ_NUM,
            FXMAC1_QUEUE1_IRQ_NUM,
            FXMAC1_QUEUE2_IRQ_NUM,
            FXMAC1_QUEUE3_IRQ_NUM
        }
    },
#endif
#ifdef FXMAC2_ID
    [FXMAC2_ID] =
    {
        .instance_id = (u32)FXMAC2_ID,               /* Device ID */
        .base_address = (uintptr)FXMAC2_BASE_ADDR, /* Device base address */
        .extral_mode_base = FXMAC2_MODE_SEL_BASE_ADDR,
        .extral_loopback_base = FXMAC2_LOOPBACK_SEL_BASE_ADDR,
        .interface = FXMAC_PHY_INTERFACE_MODE_RGMII,
        .speed = 1000,
        .duplex = 1,
        .auto_neg = 1,
        .pclk_hz = FXMAC2_PCLK,
        .max_queue_num = 4,
        .tx_queue_id = 0,
        .rx_queue_id = 0,
        .hotplug_irq_num = FXMAC2_HOTPLUG_IRQ_NUM,
        .dma_brust_length = 16,
        .network_default_config = FXMAC_DEFAULT_OPTIONS,
        .queue_irq_num =
        {
            FXMAC2_QUEUE0_IRQ_NUM,
            FXMAC2_QUEUE1_IRQ_NUM,
            FXMAC2_QUEUE2_IRQ_NUM,
            FXMAC2_QUEUE3_IRQ_NUM
        }
    },
#endif
#ifdef FXMAC3_ID
    [FXMAC3_ID] =
    {
        .instance_id = (u32)FXMAC3_ID,               /* Device ID */
        .base_address = (uintptr)FXMAC3_BASE_ADDR, /* Device base address */
        .extral_mode_base = FXMAC3_MODE_SEL_BASE_ADDR,
        .extral_loopback_base = FXMAC3_LOOPBACK_SEL_BASE_ADDR,
        .interface = FXMAC_PHY_INTERFACE_MODE_RGMII,
        .speed = 1000,
        .duplex = 1,
        .auto_neg = 1,
        .pclk_hz = FXMAC3_PCLK,
        .max_queue_num = 4,
        .tx_queue_id = 0,
        .rx_queue_id = 0,
        .hotplug_irq_num = FXMAC3_HOTPLUG_IRQ_NUM,
        .dma_brust_length = 16,
        .network_default_config = FXMAC_DEFAULT_OPTIONS,
        .queue_irq_num =
        {
            FXMAC3_QUEUE0_IRQ_NUM,
            FXMAC3_QUEUE1_IRQ_NUM,
            FXMAC3_QUEUE2_IRQ_NUM,
            FXMAC3_QUEUE3_IRQ_NUM
        }
    }
#endif
};
