/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-22     ox-horse     first version - N32H7xx FDCAN driver
 */

#ifndef __DRV_FDCAN_H__
#define __DRV_FDCAN_H__

#include <rtdevice.h>
#include <rtthread.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *\*\name   n32_fdcan_arb_timing.
 *\*\brief  FDCAN arbitration segment (nominal) baud rate timing entry.
 */
struct n32_fdcan_arb_timing
{
    uint32_t baud_rate;         /**< baud rate in bps */
    uint16_t prescaler;         /**< prescaler (1~512) */
    uint8_t  sjw;               /**< synchronization jump width (1~128) */
    uint16_t tseg1;             /**< time segment 1 (2~256) */
    uint8_t  tseg2;             /**< time segment 2 (2~128) */
};

/**
 *\*\name   n32_fdcan_data_timing.
 *\*\brief  FDCAN data segment baud rate timing entry (for CAN FD with BRS).
 */
struct n32_fdcan_data_timing
{
    uint32_t baud_rate;         /**< data phase baud rate in bps */
    uint16_t prescaler;         /**< data phase prescaler (1~32) */
    uint8_t  sjw;               /**< data phase synchronization jump width (1~16) */
    uint16_t tseg1;             /**< data phase time segment 1 (1~32) */
    uint8_t  tseg2;             /**< data phase time segment 2 (1~16) */
};

/**
 *\*\name   n32_fdcan.
 *\*\brief  N32 FDCAN device structure.
 *\*\note   GPIO pin initialization is handled by CubeMX-generated code
 *\*\       in n32h7xx_cfg.c. This driver only handles peripheral configuration.
 */
struct n32_fdcan
{
    const char          *name;                   /**< device name */
    FDCAN_Module        *fdcan_x;              /**< FDCAN peripheral base address (FDCAN1~FDCAN8) */
    FDCAN_InitType       init_struct;         /**< FDCAN init parameters */
    FDCAN_MsgRamType     msg_ram;           /**< Message RAM block config */
    FDCAN_FilterType     filter_cfg;        /**< default filter configuration */
    FDCAN_TxHeaderType   tx_header;       /**< TX header cache */
    FDCAN_RxHeaderType   rx_header;       /**< RX header cache */
    rt_uint32_t          tx_pending_mask;        /**< software mask of TX buffers with a pending request
                                              (FDCAN_TX_BUFFER0<<i).  Cleared when the ISR detects
                                              TXBRP has gone to zero for that buffer, i.e. the
                                              hardware finished/cancelled the transmission. */
    struct rt_can_device device;        /**< RT-Thread CAN device base */
};

int rt_hw_fdcan_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_FDCAN_H__ */
