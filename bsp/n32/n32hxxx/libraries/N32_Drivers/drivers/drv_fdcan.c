/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-06-22     ox-horse     first version - N32H7xx FDCAN driver
 */

#include "drv_fdcan.h"
#include "drv_config.h"

#if defined(RT_USING_CAN)

#if defined(BSP_USING_FDCAN1) || defined(BSP_USING_FDCAN2) || defined(BSP_USING_FDCAN3) || \
    defined(BSP_USING_FDCAN4) || defined(BSP_USING_FDCAN5) || defined(BSP_USING_FDCAN6) || \
    defined(BSP_USING_FDCAN7) || defined(BSP_USING_FDCAN8)

//#define DRV_DEBUG
#define LOG_TAG "drv.fdcan"
#include <drv_log.h>

/* FDCAN kernel clock: 40MHz (APB1/APB2 peripheral clock) */
#define FDCAN_KERNEL_CLK (40000000U)

/* FDCAN Message RAM base addresses */
#define FDCAN_MSG_RAM_BASE1 ((uint32_t)0x30050000U)  /* SRAM5 BANK1: FDCAN1~4 */
#define FDCAN_MSG_RAM_BASE2 ((uint32_t)0x30054000U)  /* SRAM5 BANK2: FDCAN5~8 */

/* Message RAM offset per FDCAN instance within a bank (in words) */
#define FDCAN_MSG_RAM_OFFSET_PER_INSTANCE ((uint32_t)0x400U)

/* Number of dedicated TX Buffers for blocking send */
#define FDCAN_TX_BUF_NUM (3U)

/* Number of RX FIFO0 elements */
#define FDCAN_RX_FIFO0_SIZE (8U)

/* Default RX FIFO0 watermark (50%) */
#define FDCAN_RX_FIFO0_WATERMARK (4U)

/*==============================================================================
 * Baud rate configuration tables (40MHz FDCAN kernel clock)
 * Matching STM32 H7 FDCAN timing values.
 * Formula: BaudRate = FDCAN_KERNEL_CLK / (Prescaler * (Tseg1 + Tseg2 + 1))
 *============================================================================*/

/**
 *\*\name   _fdcan_arb_timing_table.
 *\*\brief  FDCAN arbitration segment (nominal) baud rate table.
 *\*\note   40MHz FDCAN kernel clock.
 */
static const struct n32_fdcan_arb_timing _fdcan_arb_timing_table[] = {
    { CAN1MBaud, 1, 8, 29, 10 },  /* 1Mbps   : 40M / (1  * (29+10+1)) = 1.000M */
    { CAN800kBaud, 1, 8, 37, 12 },  /* 800kbps : 40M / (1  * (37+12+1)) = 800k  */
    { CAN500kBaud, 1, 8, 59, 20 },  /* 500kbps : 40M / (1  * (59+20+1)) = 500k  */
    { CAN250kBaud, 2, 8, 63, 16 },  /* 250kbps : 40M / (2  * (63+16+1)) = 250k  */
    { CAN125kBaud, 5, 8, 55, 8 },  /* 125kbps : 40M / (5  * (55+8+1))  = 125k  */
    { CAN100kBaud, 8, 8, 41, 8 },  /* 100kbps : 40M / (8  * (41+8+1))  = 100k  */
    { CAN50kBaud, 16, 8, 41, 8 },  /* 50kbps  : 40M / (16 * (41+8+1))  = 50k   */
    { CAN20kBaud, 40, 8, 41, 8 },  /* 20kbps  : 40M / (40 * (41+8+1))  = 20k   */
    { CAN10kBaud, 100, 8, 31, 8 },  /* 10kbps  : 40M / (100* (31+8+1))  = 10k   */
};

/**
 *\*\name   _fdcan_data_timing_table.
 *\*\brief  FDCAN data segment baud rate table (for CAN FD with BRS).
 *\*\note   40MHz FDCAN kernel clock.
 */
static const struct n32_fdcan_data_timing _fdcan_data_timing_table[] = {
    { CAN1MBaud * 8, 1, 1, 3, 1 },  /* 8Mbps   : 40M / (1  * (3+1+1))  = 8M    */
    { CAN1MBaud * 5, 1, 2, 5, 2 },  /* 5Mbps   : 40M / (1  * (5+2+1))  = 5M    */
    { CAN1MBaud * 4, 1, 2, 7, 2 },  /* 4Mbps   : 40M / (1  * (7+2+1))  = 4M    */
    { CAN1MBaud * 2, 1, 4, 15, 4 },  /* 2Mbps   : 40M / (4  * (3+1+1))  = 2M    */
    { CAN1MBaud, 1, 8, 31, 8 },  /* 1Mbps   : 40M / (1  * (31+8+1)) = 1M    */
    { CAN800kBaud, 2, 5, 19, 5 },  /* 800kbps : 40M / (2  * (19+5+1)) = 800k  */
    { CAN500kBaud, 4, 4, 15, 4 },  /* 400kbps : 40M / (4  * (15+4+1)) = 500k  */
};

/*==============================================================================
 * FDCAN instance objects
 *============================================================================*/

#ifdef BSP_USING_FDCAN1
static struct n32_fdcan _drv_fdcan1 = {
    .name = "fdcan1",
};
#endif

#ifdef BSP_USING_FDCAN2
static struct n32_fdcan _drv_fdcan2 = {
    .name = "fdcan2",
};
#endif

#ifdef BSP_USING_FDCAN3
static struct n32_fdcan _drv_fdcan3 = {
    .name = "fdcan3",
};
#endif

#ifdef BSP_USING_FDCAN4
static struct n32_fdcan _drv_fdcan4 = {
    .name = "fdcan4",
};
#endif

#ifdef BSP_USING_FDCAN5
static struct n32_fdcan _drv_fdcan5 = {
    .name = "fdcan5",
};
#endif

#ifdef BSP_USING_FDCAN6
static struct n32_fdcan _drv_fdcan6 = {
    .name = "fdcan6",
};
#endif

#ifdef BSP_USING_FDCAN7
static struct n32_fdcan _drv_fdcan7 = {
    .name = "fdcan7",
};
#endif

#ifdef BSP_USING_FDCAN8
static struct n32_fdcan _drv_fdcan8 = {
    .name = "fdcan8",
};
#endif

/*==============================================================================
 * DLC conversion utilities
 *============================================================================*/

/**
 *\*\name   _dlc_to_length.
 *\*\fun    Convert a raw FDCAN_TxHeaderType/FDCAN_RxHeaderType.DataLength value
 *\*\       (DLC pre-shifted into bits[19:16], as produced by FDCAN_GetRxMsg())
 *\*\       to the actual frame length.
 *\*\param  dlc :
 *\*\          raw DataLength field value (FDCAN_DLC_BYTES_x / FDCAN_ELEMENT_DLC)
 *\*\return Actual length in bytes (0~64)
 */
static uint8_t _dlc_to_length(uint32_t dlc)
{
    const uint8_t dlc_table[16] = {
        0, 1, 2, 3, 4, 5, 6, 7,
        8, 12, 16, 20, 24, 32, 48, 64
    };

    dlc >>= FDCAN_ELEMENT_DLC_OFFSET;
    if (dlc > 15)
        return 8;
    return dlc_table[dlc];
}

/**
 *\*\name   _length_to_dlc.
 *\*\fun    Convert CAN-FD frame length to a DataLength value ready to assign
 *\*\       to FDCAN_TxHeaderType.DataLength (DLC pre-shifted into bits[19:16],
 *\*\       matching the FDCAN_DLC_BYTES_x constants consumed by FDCAN_CopyMsgToRAM()).
 *\*\       CAN-FD DLC mapping (length -> DLC):
 *\*\        0~8   -> 0~8
 *\*\        9~12  -> 9
 *\*\        13~16 -> 10
 *\*\        17~20 -> 11
 *\*\        21~24 -> 12
 *\*\        25~32 -> 13
 *\*\        33~48 -> 14
 *\*\        49~64 -> 15
 *\*\param  len :
 *\*\          Frame length in bytes (0~64)
 *\*\return raw DataLength field value (DLC code shifted into bits[19:16])
 */
static uint32_t _length_to_dlc(uint8_t len)
{
    uint32_t dlc;

    if (len <= 8)
        dlc = len;
    else if (len <= 12)
        dlc = 9;
    else if (len <= 16)
        dlc = 10;
    else if (len <= 20)
        dlc = 11;
    else if (len <= 24)
        dlc = 12;
    else if (len <= 32)
        dlc = 13;
    else if (len <= 48)
        dlc = 14;
    else
        dlc = 15;

    return dlc << FDCAN_ELEMENT_DLC_OFFSET;
}

/*==============================================================================
 * Baud rate lookup
 *============================================================================*/

/**
 *\*\name   _get_arb_baud_index.
 *\*\fun    Get the arbitration segment baud rate configuration index.
 *\*\param  baud_rate :
 *\*\          Target baud rate in bps
 *\*\return Table index, or (uint32_t)-1 if not found
 */
static uint32_t _get_arb_baud_index(uint32_t baud_rate)
{
    uint32_t len = sizeof(_fdcan_arb_timing_table) / sizeof(_fdcan_arb_timing_table[0]);

    for (uint32_t i = 0; i < len; i++)
    {
        if (_fdcan_arb_timing_table[i].baud_rate == baud_rate)
            return i;
    }
    return (uint32_t)-1;
}

/**
 *\*\name   _get_data_baud_index.
 *\*\fun    Get the data segment baud rate configuration index.
 *\*\param  baud_rate :
 *\*\          Target data phase baud rate in bps
 *\*\return Table index, or (uint32_t)-1 if not found
 */
static uint32_t _get_data_baud_index(uint32_t baud_rate)
{
    uint32_t len = sizeof(_fdcan_data_timing_table) / sizeof(_fdcan_data_timing_table[0]);

    for (uint32_t i = 0; i < len; i++)
    {
        if (_fdcan_data_timing_table[i].baud_rate == baud_rate)
            return i;
    }
    return (uint32_t)-1;
}

/*==============================================================================
 * Instance index calculation
 *============================================================================*/

/**
 *\*\name   _fdcan_get_index.
 *\*\fun    Get the index of the specified FDCAN instance.
 *\*\param  FDCANx :
 *\*\          - FDCAN1
 *\*\          - FDCAN2
 *\*\          - FDCAN3
 *\*\          - FDCAN4
 *\*\          - FDCAN5
 *\*\          - FDCAN6
 *\*\          - FDCAN7
 *\*\          - FDCAN8
 *\*\return Instance index (0=FDCAN1, 1=FDCAN2, ..., 7=FDCAN8)
 */
static uint8_t _fdcan_get_index(FDCAN_Module *FDCANx)
{
    if (FDCANx == FDCAN1)
        return 0;
    if (FDCANx == FDCAN2)
        return 1;
    if (FDCANx == FDCAN3)
        return 2;
    if (FDCANx == FDCAN4)
        return 3;
    if (FDCANx == FDCAN5)
        return 4;
    if (FDCANx == FDCAN6)
        return 5;
    if (FDCANx == FDCAN7)
        return 6;
    return 7; /* FDCAN8 */
}

/**
 *\*\name   _fdcan_get_int0_irqn.
 *\*\fun    Get the INT0 interrupt vector number for the specified FDCAN instance.
 *\*\param  FDCANx :
 *\*\          FDCAN instance pointer
 *\*\return INT0 IRQn value
 */
static IRQn_Type _fdcan_get_int0_irqn(FDCAN_Module *FDCANx)
{
    if (FDCANx == FDCAN1)
        return FDCAN1_INT0_IRQn;
    if (FDCANx == FDCAN2)
        return FDCAN2_INT0_IRQn;
    if (FDCANx == FDCAN3)
        return FDCAN3_INT0_IRQn;
    if (FDCANx == FDCAN4)
        return FDCAN4_INT0_IRQn;
    if (FDCANx == FDCAN5)
        return FDCAN5_INT0_IRQn;
    if (FDCANx == FDCAN6)
        return FDCAN6_INT0_IRQn;
    if (FDCANx == FDCAN7)
        return FDCAN7_INT0_IRQn;
    return FDCAN8_INT0_IRQn;
}

/**
 *\*\name   _fdcan_get_int1_irqn.
 *\*\fun    Get the INT1 interrupt vector number for the specified FDCAN instance.
 *\*\param  FDCANx :
 *\*\          FDCAN instance pointer
 *\*\return INT1 IRQn value
 */
static IRQn_Type _fdcan_get_int1_irqn(FDCAN_Module *FDCANx)
{
    if (FDCANx == FDCAN1)
        return FDCAN1_INT1_IRQn;
    if (FDCANx == FDCAN2)
        return FDCAN2_INT1_IRQn;
    if (FDCANx == FDCAN3)
        return FDCAN3_INT1_IRQn;
    if (FDCANx == FDCAN4)
        return FDCAN4_INT1_IRQn;
    if (FDCANx == FDCAN5)
        return FDCAN5_INT1_IRQn;
    if (FDCANx == FDCAN6)
        return FDCAN6_INT1_IRQn;
    if (FDCANx == FDCAN7)
        return FDCAN7_INT1_IRQn;
    return FDCAN8_INT1_IRQn;
}

/*==============================================================================
 * FDCAN device operations: configure
 *============================================================================*/

/**
 *\*\name   _fdcan_configure.
 *\*\fun    Configure the FDCAN device with the specified parameters.
 *\*\param  can :
 *\*\          Pointer to RT-Thread CAN device structure
 *\*\param  cfg :
 *\*\          Pointer to CAN configuration structure
 *\*\return RT_EOK on success, or negative error code on failure
 */
static rt_err_t _fdcan_configure(struct rt_can_device *can, struct can_configure *cfg)
{
    struct n32_fdcan *p_drv;
    ErrorStatus       status;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    p_drv = (struct n32_fdcan *)can->parent.user_data;
    RT_ASSERT(p_drv != RT_NULL);

    /* Fill FDCAN init parameters */
    p_drv->init_struct.FrameFormat        = FDCAN_FRAME_FD_BRS;
    p_drv->init_struct.Mode               = FDCAN_MODE_NORMAL;
    p_drv->init_struct.AutoRetransmission = ENABLE;
    p_drv->init_struct.TransmitPause      = DISABLE;
    p_drv->init_struct.ProtocolException  = ENABLE;

    /* Configure operation mode */
    switch (cfg->mode)
    {
    case RT_CAN_MODE_NORMAL:
        p_drv->init_struct.Mode = FDCAN_MODE_NORMAL;
        break;
    case RT_CAN_MODE_LISTEN:
        p_drv->init_struct.Mode = FDCAN_MODE_BUS_MONITORING;
        break;
    case RT_CAN_MODE_LOOPBACK:
        p_drv->init_struct.Mode = FDCAN_MODE_INTERNAL_LOOPBACK;
        break;
    case RT_CAN_MODE_LOOPBACKANLISTEN:
        p_drv->init_struct.Mode = FDCAN_MODE_EXTERNAL_LOOPBACK;
        break;
    default:
        p_drv->init_struct.Mode = FDCAN_MODE_NORMAL;
        break;
    }

    /* Lookup arbitration segment baud rate */
    uint32_t arb_idx = _get_arb_baud_index(cfg->baud_rate);
    if (arb_idx == (uint32_t)-1)
    {
        LOG_E("%s: baud rate %d not supported", p_drv->name, cfg->baud_rate);
        return -RT_ERROR;
    }

    p_drv->init_struct.Prescaler     = _fdcan_arb_timing_table[arb_idx].prescaler;
    p_drv->init_struct.SyncJumpWidth = _fdcan_arb_timing_table[arb_idx].sjw;
    p_drv->init_struct.TimeSeg1      = _fdcan_arb_timing_table[arb_idx].tseg1;
    p_drv->init_struct.TimeSeg2      = _fdcan_arb_timing_table[arb_idx].tseg2;

#ifdef RT_CAN_USING_CANFD
    /* Configure CAN FD data segment baud rate */
    if (cfg->enable_canfd && cfg->baud_rate_fd)
    {
        uint32_t data_idx = _get_data_baud_index(cfg->baud_rate_fd);
        if (data_idx == (uint32_t)-1)
        {
            LOG_E("%s: FD baud rate %d not supported", p_drv->name, cfg->baud_rate_fd);
            return -RT_ERROR;
        }

        p_drv->init_struct.DataPrescaler     = _fdcan_data_timing_table[data_idx].prescaler;
        p_drv->init_struct.DataSyncJumpWidth = _fdcan_data_timing_table[data_idx].sjw;
        p_drv->init_struct.DataTimeSeg1      = _fdcan_data_timing_table[data_idx].tseg1;
        p_drv->init_struct.DataTimeSeg2      = _fdcan_data_timing_table[data_idx].tseg2;
    }
    else
    {
        /* When CAN FD is not enabled, data phase parameters match arbitration */
        p_drv->init_struct.DataPrescaler     = p_drv->init_struct.Prescaler;
        p_drv->init_struct.DataSyncJumpWidth = p_drv->init_struct.SyncJumpWidth;
        p_drv->init_struct.DataTimeSeg1      = p_drv->init_struct.TimeSeg1;
        p_drv->init_struct.DataTimeSeg2      = p_drv->init_struct.TimeSeg2;
    }
#endif

    /* Configure Message RAM: FDCAN1~4 use BANK1, FDCAN5~8 use BANK2 */
    uint32_t instance_idx = _fdcan_get_index(p_drv->fdcan_x);
    if (instance_idx < 4)
    {
        p_drv->init_struct.MsgRamStrAddr = FDCAN_MSG_RAM_BASE1;
        p_drv->init_struct.MsgRamOffset  = instance_idx * FDCAN_MSG_RAM_OFFSET_PER_INSTANCE;
    }
    else
    {
        p_drv->init_struct.MsgRamStrAddr = FDCAN_MSG_RAM_BASE2;
        p_drv->init_struct.MsgRamOffset  = (instance_idx - 4) * FDCAN_MSG_RAM_OFFSET_PER_INSTANCE;
    }

    /* Filter configuration */
    p_drv->init_struct.StdFilterSize = 2;       /* 2 standard ID filters */
    p_drv->init_struct.ExtFilterSize = 2;       /* 2 extended ID filters */

    /* RX FIFO0 configuration */
    p_drv->init_struct.RxFifo0Size     = FDCAN_RX_FIFO0_SIZE;
    p_drv->init_struct.RxFifo0DataSize = FDCAN_DATA_BYTES_64;

    /* RX FIFO1 configuration (not used) */
    p_drv->init_struct.RxFifo1Size     = 0;
    p_drv->init_struct.RxFifo1DataSize = FDCAN_DATA_BYTES_64;

    /* RX Buffer configuration (not used) */
    p_drv->init_struct.RxBufferSize     = 0;
    p_drv->init_struct.RxBufferDataSize = FDCAN_DATA_BYTES_64;

    /* TX Event FIFO configuration (not used) */
    p_drv->init_struct.TxEventSize = 0;

    /* TX Buffer configuration: dedicated Tx Buffer mode */
    p_drv->init_struct.TxBufferSize     = FDCAN_TX_BUF_NUM;
    p_drv->init_struct.TxBufferDataSize = FDCAN_DATA_BYTES_64;
    p_drv->init_struct.TxFifoQueueMode  = FDCAN_TX_FIFO_MODE;
    p_drv->init_struct.TxFifoQueueSize  = 0;  /* not using Tx FIFO, use Dedicated Tx Buffer */

    /* Message RAM info pointer */
    p_drv->init_struct.pMsgInfo = &p_drv->msg_ram;

    /* Stop FDCAN before re-initializing (needed for mode/baud changes) */
    FDCAN_Stop(p_drv->fdcan_x);

    /* A Tx Buffer Request stays pending in hardware (TXBRP) until it
     * completes or is explicitly cancelled, so cancel any leftover request
     * on every reconfigure. FDCAN_AbortTxRequest() is asynchronous - poll
     * TXBRP until it actually clears before continuing. */
    {
        rt_uint32_t       cancel_mask = FDCAN_TX_BUFFER0 | FDCAN_TX_BUFFER1 | FDCAN_TX_BUFFER2;
        volatile uint32_t timeout     = 1000000;
        FDCAN_AbortTxRequest(p_drv->fdcan_x, cancel_mask);
        while ((p_drv->fdcan_x->TXBRP & cancel_mask) && --timeout)
        {
        }
        p_drv->tx_pending_mask = 0;
    }

    /* Initialize FDCAN */
    status = FDCAN_Init(p_drv->fdcan_x, &p_drv->init_struct);
    if (status != SUCCESS)
    {
        LOG_E("%s: FDCAN_Init failed", p_drv->name);
        return -RT_ERROR;
    }

#ifdef RT_CAN_USING_CANFD
    /* Configure and enable Transmitter Delay Compensation (TDC) */
    if (cfg->enable_canfd)
    {
        FDCAN_ConfigTxDelayCompensation(p_drv->fdcan_x, 0x0C, 0x00);
        FDCAN_EnableTxDelayCompensation(p_drv->fdcan_x);
    }
#endif

    /* Configure global filter: accept all non-matching frames to RX FIFO0 */
    FDCAN_ConfigGlobalFilter(p_drv->fdcan_x,
                             FDCAN_ACCEPT_STD_IN_RX_FIFO0,
                             FDCAN_ACCEPT_EXT_IN_RX_FIFO0,
                             FDCAN_FILTER_STD_REMOTE,
                             FDCAN_FILTER_EXT_REMOTE);

    /* Apply default filter */
    FDCAN_ConfigFilter(p_drv->fdcan_x, &p_drv->filter_cfg);

    /* Configure RX FIFO0 as Overwrite mode */
    FDCAN_ConfigRxFifoMode(p_drv->fdcan_x, FDCAN_RX_FIFO0, FDCAN_RX_FIFO_OVERWRITE);

    /* Configure RX FIFO0 watermark */
    FDCAN_ConfigFifoWatermark(p_drv->fdcan_x, FDCAN_RX_FIFO0, FDCAN_RX_FIFO0_WATERMARK);

    /* Enable RX FIFO0 New Message interrupt (INT0) */
    FDCAN_ConfigIntLine(p_drv->fdcan_x, FDCAN_INT_RX_FIFO0_NEW_MESSAGE, FDCAN_INTERRUPT_LINE0);
    FDCAN_EnableInt(p_drv->fdcan_x, FDCAN_INT_RX_FIFO0_NEW_MESSAGE);

    /* Initialize TX Header cache */
    p_drv->tx_header.ID            = 0x000000;
    p_drv->tx_header.IdType        = FDCAN_EXTENDED_ID;
    p_drv->tx_header.TxFrameType   = FDCAN_DATA_FRAME;
    p_drv->tx_header.DataLength    = FDCAN_DLC_BYTES_8;
    p_drv->tx_header.ErrorState    = FDCAN_ESI_ACTIVE;
    p_drv->tx_header.BitRateSwitch = FDCAN_BRS_OFF;
    p_drv->tx_header.FDFormat      = FDCAN_CLASSIC_CAN;
    p_drv->tx_header.TxEventFifo   = FDCAN_NO_TX_EVENTS;
    p_drv->tx_header.MsgMarker     = 0;

    /* Start FDCAN */
    FDCAN_Start(p_drv->fdcan_x);

    LOG_I("%s: configured, baud=%d, mode=%d", p_drv->name, cfg->baud_rate, cfg->mode);

    return RT_EOK;
}

/*==============================================================================
 * FDCAN device operations: filter configuration
 *============================================================================*/

/**
 *\*\name   _fdcan_filter_config.
 *\*\fun    Configure FDCAN hardware filters.
 *\*\param  p_drv :
 *\*\          Pointer to FDCAN device structure
 *\*\param  filter_cfg :
 *\*\          Pointer to RT-Thread filter configuration
 *\*\return RT_EOK on success, or negative error code on failure
 */
static rt_err_t _fdcan_filter_config(struct n32_fdcan            *p_drv,
                                     struct rt_can_filter_config *filter_cfg)
{
    RT_ASSERT(p_drv != RT_NULL);
    RT_ASSERT(filter_cfg != RT_NULL);

    for (rt_uint32_t i = 0; i < filter_cfg->count; i++)
    {
        /* Set ID type */
        if (filter_cfg->items[i].ide == RT_CAN_EXTID)
        {
            p_drv->filter_cfg.IdType      = FDCAN_EXTENDED_ID;
            p_drv->filter_cfg.FilterIndex = filter_cfg->items[i].hdr_bank;
        }
        else
        {
            p_drv->filter_cfg.IdType      = FDCAN_STANDARD_ID;
            p_drv->filter_cfg.FilterIndex = filter_cfg->items[i].hdr_bank;
        }

        /* Set filter ID and mask */
        p_drv->filter_cfg.FilterID1 = filter_cfg->items[i].id;
        p_drv->filter_cfg.FilterID2 = filter_cfg->items[i].mask;

        /* Use Mask mode filtering */
        p_drv->filter_cfg.FilterType = FDCAN_FILTER_MASK;

        /* Store matching messages into RX FIFO0 */
        p_drv->filter_cfg.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;

        /* Apply filter configuration */
        FDCAN_ConfigFilter(p_drv->fdcan_x, &p_drv->filter_cfg);
    }

    return RT_EOK;
}

/*==============================================================================
 * FDCAN device operations: control
 *============================================================================*/

/**
 *\*\name   _fdcan_control.
 *\*\fun    Handle control commands for the FDCAN device.
 *\*\param  can :
 *\*\          Pointer to RT-Thread CAN device structure
 *\*\param  cmd :
 *\*\          Control command
 *\*\param  arg :
 *\*\          Command argument
 *\*\return RT_EOK on success, or negative error code on failure
 */
static rt_err_t _fdcan_control(struct rt_can_device *can, int cmd, void *arg)
{
    rt_uint32_t                  argval;
    struct n32_fdcan            *p_drv;
    struct rt_can_filter_config *filter_cfg;

    RT_ASSERT(can != RT_NULL);
    p_drv = (struct n32_fdcan *)can->parent.user_data;
    RT_ASSERT(p_drv != RT_NULL);

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        argval = (rt_uint32_t)arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            /* Disable RX FIFO0 interrupt */
            FDCAN_DisableInt(p_drv->fdcan_x, FDCAN_INT_RX_FIFO0_NEW_MESSAGE);
            NVIC_DisableIRQ(_fdcan_get_int0_irqn(p_drv->fdcan_x));
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            /* Disable TX Complete interrupt (including per-buffer activation) */
            FDCAN_DeactivateInt(p_drv->fdcan_x, FDCAN_INT_TX_COMPLETE);
            FDCAN_DisableInt(p_drv->fdcan_x, FDCAN_INT_TX_COMPLETE);
            NVIC_DisableIRQ(_fdcan_get_int1_irqn(p_drv->fdcan_x));
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            /* Disable error interrupts */
            FDCAN_DisableInt(p_drv->fdcan_x, FDCAN_INT_BUS_OFF);
            FDCAN_DisableInt(p_drv->fdcan_x, FDCAN_INT_ERROR_WARNING);
            FDCAN_DisableInt(p_drv->fdcan_x, FDCAN_INT_ERROR_PASSIVE);
            FDCAN_DisableInt(p_drv->fdcan_x, FDCAN_INT_ARB_PROTOCOL_ERROR);
        }
        break;

    case RT_DEVICE_CTRL_SET_INT:
        argval = (rt_uint32_t)arg;
        if (argval == RT_DEVICE_FLAG_INT_RX)
        {
            /* Enable RX FIFO0 interrupt (INT0) */
            FDCAN_ConfigIntLine(p_drv->fdcan_x, FDCAN_INT_RX_FIFO0_NEW_MESSAGE,
                                FDCAN_INTERRUPT_LINE0);
            FDCAN_EnableInt(p_drv->fdcan_x, FDCAN_INT_RX_FIFO0_NEW_MESSAGE);
            /* FDCAN_EnableInt() only sets IE; the interrupt line itself still
             * needs to be switched on via ILE, otherwise INT0 never reaches the NVIC */
            p_drv->fdcan_x->ILE |= FDCAN_INTERRUPT_LINE0;
            NVIC_SetPriority(_fdcan_get_int0_irqn(p_drv->fdcan_x), 1);
            NVIC_EnableIRQ(_fdcan_get_int0_irqn(p_drv->fdcan_x));
        }
        else if (argval == RT_DEVICE_FLAG_INT_TX)
        {
            /* Enable TX Complete interrupt (INT1) */
            FDCAN_ConfigIntLine(p_drv->fdcan_x, FDCAN_INT_TX_COMPLETE,
                                FDCAN_INTERRUPT_LINE1);
            /* Activate TX Complete interrupt for each dedicated TX Buffer */
            FDCAN_ActivateInt(p_drv->fdcan_x, FDCAN_INT_TX_COMPLETE,
                              FDCAN_TX_BUFFER0 | FDCAN_TX_BUFFER1 | FDCAN_TX_BUFFER2);
            NVIC_SetPriority(_fdcan_get_int1_irqn(p_drv->fdcan_x), 2);
            NVIC_EnableIRQ(_fdcan_get_int1_irqn(p_drv->fdcan_x));
        }
        else if (argval == RT_DEVICE_CAN_INT_ERR)
        {
            /* Enable error interrupts (INT1) */
            FDCAN_ConfigIntLine(p_drv->fdcan_x, FDCAN_INT_BUS_OFF,
                                FDCAN_INTERRUPT_LINE1);
            FDCAN_ConfigIntLine(p_drv->fdcan_x, FDCAN_INT_ERROR_WARNING,
                                FDCAN_INTERRUPT_LINE1);
            FDCAN_ConfigIntLine(p_drv->fdcan_x, FDCAN_INT_ERROR_PASSIVE,
                                FDCAN_INTERRUPT_LINE1);
            FDCAN_ConfigIntLine(p_drv->fdcan_x, FDCAN_INT_ARB_PROTOCOL_ERROR,
                                FDCAN_INTERRUPT_LINE1);

            FDCAN_EnableInt(p_drv->fdcan_x, FDCAN_INT_BUS_OFF);
            FDCAN_EnableInt(p_drv->fdcan_x, FDCAN_INT_ERROR_WARNING);
            FDCAN_EnableInt(p_drv->fdcan_x, FDCAN_INT_ERROR_PASSIVE);
            FDCAN_EnableInt(p_drv->fdcan_x, FDCAN_INT_ARB_PROTOCOL_ERROR);
            p_drv->fdcan_x->ILE |= FDCAN_INTERRUPT_LINE1;
        }
        break;

    case RT_CAN_CMD_SET_FILTER:
        if (RT_NULL == arg)
        {
            /* Restore default filter */
            FDCAN_ConfigFilter(p_drv->fdcan_x, &p_drv->filter_cfg);
        }
        else
        {
            filter_cfg = (struct rt_can_filter_config *)arg;
            _fdcan_filter_config(p_drv, filter_cfg);
        }
        break;

    case RT_CAN_CMD_SET_MODE:
        argval = (rt_uint32_t)arg;
        if (argval != RT_CAN_MODE_NORMAL &&
            argval != RT_CAN_MODE_LISTEN &&
            argval != RT_CAN_MODE_LOOPBACK &&
            argval != RT_CAN_MODE_LOOPBACKANLISTEN)
        {
            return -RT_ERROR;
        }
        if (argval != p_drv->device.config.mode)
        {
            /* Direct CCCR register modification for mode change
             * (avoids full FDCAN_Stop+Init re-init which can fail) */
            FDCAN_Module *fdcan = p_drv->fdcan_x;

            /* Cancel any Tx request left pending from the previous mode
             * (see _fdcan_configure() for the same pattern); the abort is
             * asynchronous, so poll TXBRP until it actually clears. */
            {
                rt_uint32_t       cm = FDCAN_TX_BUFFER0 | FDCAN_TX_BUFFER1 | FDCAN_TX_BUFFER2;
                volatile uint32_t to = 1000000;
                FDCAN_AbortTxRequest(fdcan, cm);
                while ((fdcan->TXBRP & cm) && --to)
                {
                }
                p_drv->tx_pending_mask = 0;
            }

            /* CCE can only be set by software once INIT has actually taken
             * effect (Bosch M_CAN: writes to CCE are ignored while INIT=0).
             * INIT must therefore be requested and confirmed first. */
            fdcan->CCCR |= FDCAN_CCCR_INIT;
            while ((fdcan->CCCR & FDCAN_CCCR_INIT) == 0)
                ;
            fdcan->CCCR |= FDCAN_CCCR_CCE;
            /* Clear previous mode bits */
            fdcan->CCCR &= ~(FDCAN_CCCR_TEST | FDCAN_CCCR_MON | FDCAN_CCCR_ASM);
            if (argval == RT_CAN_MODE_LOOPBACK)
                fdcan->CCCR |= FDCAN_CCCR_TEST | FDCAN_CCCR_MON;
            else if (argval == RT_CAN_MODE_LISTEN)
                fdcan->CCCR |= FDCAN_CCCR_MON;
            else if (argval == RT_CAN_MODE_LOOPBACKANLISTEN)
                fdcan->CCCR |= FDCAN_CCCR_TEST;
            /* TEST.LBCK must follow CCCR.TEST: it is the bit that actually
             * routes TX back into RX for both internal and external loopback */
            if (argval == RT_CAN_MODE_LOOPBACK || argval == RT_CAN_MODE_LOOPBACKANLISTEN)
                fdcan->TEST |= FDCAN_TEST_LBCK;
            else
                fdcan->TEST &= ~FDCAN_TEST_LBCK;
            fdcan->CCCR &= ~FDCAN_CCCR_INIT;
            while (fdcan->CCCR & FDCAN_CCCR_INIT)
                ;
            p_drv->device.config.mode = argval;
            LOG_I("%s: mode changed to %d", p_drv->name, argval);
        }
        break;

    case RT_CAN_CMD_SET_BAUD:
        argval = (rt_uint32_t)arg;
        if (_get_arb_baud_index(argval) == (uint32_t)-1)
        {
            return -RT_ERROR;
        }
        if (argval != p_drv->device.config.baud_rate)
        {
            p_drv->device.config.baud_rate = argval;
            return _fdcan_configure(&p_drv->device, &p_drv->device.config);
        }
        break;

    case RT_CAN_CMD_SET_PRIV:
        argval = (rt_uint32_t)arg;
        if (argval != RT_CAN_MODE_PRIV && argval != RT_CAN_MODE_NOPRIV)
        {
            return -RT_ERROR;
        }
        p_drv->device.config.privmode = argval;
        break;

    case RT_CAN_CMD_GET_STATUS:
    {
        rt_uint32_t ecr_val = p_drv->fdcan_x->ECR;
        rt_uint32_t psr_val = p_drv->fdcan_x->PSR;

        p_drv->device.status.rcverrcnt   = (ecr_val >> 8) & 0x000000FF;
        p_drv->device.status.snderrcnt   = (ecr_val) & 0x000000FF;
        p_drv->device.status.lasterrtype = psr_val & 0x00000007;

        rt_memcpy(arg, &p_drv->device.status, sizeof(p_drv->device.status));
    }
    break;

    case RT_CAN_CMD_SET_BAUD_FD:
    {
#ifdef RT_CAN_USING_CANFD
        argval = (rt_uint32_t)arg;
        if (_get_data_baud_index(argval) == (uint32_t)-1)
        {
            return -RT_ERROR;
        }
        if (argval != p_drv->device.config.baud_rate_fd)
        {
            p_drv->device.config.baud_rate_fd = argval;
            return _fdcan_configure(&p_drv->device, &p_drv->device.config);
        }
#endif
    }
    break;

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}

/*==============================================================================
 * FDCAN device operations: send message (blocking)
 *============================================================================*/

/**
 *\*\name   _fdcan_sendmsg.
 *\*\fun    Send a CAN message using a dedicated TX Buffer (blocking mode).
 *\*\param  can :
 *\*\          Pointer to RT-Thread CAN device structure
 *\*\param  buf :
 *\*\          Pointer to the CAN message to be sent
 *\*\param  box_no :
 *\*\          TX Buffer index (0 ~ FDCAN_TX_BUF_NUM-1)
 *\*\return RT_EOK on success, or negative error code on failure
 */
static rt_ssize_t _fdcan_sendmsg(struct rt_can_device *can, const void *buf, rt_uint32_t box_no)
{
    struct n32_fdcan  *p_drv;
    struct rt_can_msg *p_msg;
    ErrorStatus        status;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    p_drv = (struct n32_fdcan *)can->parent.user_data;
    RT_ASSERT(p_drv != RT_NULL);

    p_msg = (struct rt_can_msg *)buf;

    /* Set ID type */
    if (p_msg->ide == RT_CAN_EXTID)
    {
        p_drv->tx_header.IdType = FDCAN_EXTENDED_ID;
    }
    else
    {
        p_drv->tx_header.IdType = FDCAN_STANDARD_ID;
    }

    /* Set frame type */
    if (RT_CAN_DTR == p_msg->rtr)
    {
        p_drv->tx_header.TxFrameType = FDCAN_DATA_FRAME;
    }
    else
    {
        p_drv->tx_header.TxFrameType = FDCAN_REMOTE_FRAME;
    }

    /* Set CAN ID */
    p_drv->tx_header.ID = p_msg->id;

    /* Set data length (DLC) */
    p_drv->tx_header.DataLength = _length_to_dlc(p_msg->len);

#ifdef RT_CAN_USING_CANFD
    /* Set CAN FD related flags */
    if (p_msg->fd_frame == 1)
    {
        p_drv->tx_header.FDFormat = FDCAN_FD_CAN;
    }
    else
    {
        p_drv->tx_header.FDFormat = FDCAN_CLASSIC_CAN;
    }

    if (p_msg->brs == 1)
    {
        p_drv->tx_header.BitRateSwitch = FDCAN_BRS_ON;
    }
    else
    {
        p_drv->tx_header.BitRateSwitch = FDCAN_BRS_OFF;
    }
#endif

    /* FDCAN_TX_BUFFER0 is the single-bit mask for buffer 0; shift it to get
     * the mask for an arbitrary buffer index. */
    rt_uint32_t buf_bit = FDCAN_TX_BUFFER0 << box_no;
    status              = FDCAN_AddMsgToTxBuffer(p_drv->fdcan_x, &p_drv->tx_header,
                                                 p_msg->data, buf_bit);
    if (status != SUCCESS)
    {
        LOG_W("%s: FDCAN_AddMsgToTxBuffer failed, buf=%d", p_drv->name, box_no);
        return -RT_ERROR;
    }

    /* Request transmission */
    FDCAN_EnableTxBufferRequest(p_drv->fdcan_x, buf_bit);
    p_drv->tx_pending_mask |= buf_bit;

    return RT_EOK;
}

/*==============================================================================
 * FDCAN device operations: receive message
 *============================================================================*/

/**
 *\*\name   _fdcan_recvmsg.
 *\*\fun    Receive a CAN message from RX FIFO.
 *\*\param  can :
 *\*\          Pointer to RT-Thread CAN device structure
 *\*\param  buf :
 *\*\          Pointer to receive buffer
 *\*\param  fifo :
 *\*\          RX FIFO number (CAN_RX_FIFO0 or CAN_RX_FIFO1)
 *\*\return Number of bytes received, or 0 if no data
 */
static rt_ssize_t _fdcan_recvmsg(struct rt_can_device *can, void *buf, rt_uint32_t fifo)
{
    struct rt_can_msg *p_msg;
    struct n32_fdcan  *p_drv;
    ErrorStatus        status;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    p_drv = (struct n32_fdcan *)can->parent.user_data;
    RT_ASSERT(p_drv != RT_NULL);

    p_msg = (struct rt_can_msg *)buf;

    /* rt_hw_can_isr() treats a -1 return as "nothing to read" and otherwise
     * copies the message unconditionally, so a failed read must report -1,
     * not 0 (which would forward stale/uninitialized data as a real frame). */
    status = FDCAN_GetRxMsg(p_drv->fdcan_x, FDCAN_RX_FIFO0 + fifo,
                            &p_drv->rx_header, p_msg->data);
    if (status != SUCCESS)
    {
        return -1;
    }

    /* Convert ID type */
    if (p_drv->rx_header.IdType == FDCAN_EXTENDED_ID)
    {
        p_msg->ide = RT_CAN_EXTID;
    }
    else
    {
        p_msg->ide = RT_CAN_STDID;
    }

    /* Convert frame type */
    if (p_drv->rx_header.RxFrameType == FDCAN_DATA_FRAME)
    {
        p_msg->rtr = RT_CAN_DTR;
    }
    else
    {
        p_msg->rtr = RT_CAN_RTR;
    }

    /* Extract CAN ID */
    p_msg->id = p_drv->rx_header.ID;

    /* Convert DLC to actual length */
    p_msg->len = _dlc_to_length(p_drv->rx_header.DataLength);

    /* ANMF ("Accepted Non-Matching Frame") means the frame was accepted by
     * the global catch-all filter rather than a specific filter element, so
     * FilterIndex holds the reserved sentinel 127 - out of can->config.maxhdr
     * range and would trip the framework's RT_ASSERT(hdr < maxhdr). Report
     * bank 0 (always valid) instead; a bare, unconnected bank is a no-op for
     * the framework's HDR-specific list, and rt_device_read() with the
     * default software FIFO ignores this field anyway. */
    if (p_drv->rx_header.Matching == FDCAN_ACCEPT_NON_MATCHING)
    {
        p_msg->hdr_index = 0;
    }
    else
    {
        p_msg->hdr_index = (rt_int32_t)p_drv->rx_header.FilterIndex;
    }

#ifdef RT_CAN_USING_CANFD
    /* Extract CAN FD flags */
    p_msg->fd_frame = (p_drv->rx_header.FDFormat == FDCAN_FD_CAN) ? 1 : 0;
    p_msg->brs      = (p_drv->rx_header.BitRateSwitch == FDCAN_BRS_ON) ? 1 : 0;
#endif

    return sizeof(struct rt_can_msg);
}

/*==============================================================================
 * FDCAN device operations: send message (non-blocking)
 *============================================================================*/

/**
 *\*\name   _fdcan_sendmsg_nonblocking.
 *\*\fun    Send a CAN message in non-blocking mode.
 *\*\       Checks for a free dedicated TX Buffer, sends immediately, and returns.
 *\*\param  can :
 *\*\          Pointer to RT-Thread CAN device structure
 *\*\param  buf :
 *\*\          Pointer to the CAN message to be sent
 *\*\return RT_EOK on success, -RT_EBUSY if no TX Buffer is available
 */
static rt_ssize_t _fdcan_sendmsg_nonblocking(struct rt_can_device *can, const void *buf)
{
    struct n32_fdcan  *p_drv;
    struct rt_can_msg *p_msg;
    ErrorStatus        status;
    int32_t            free_buf = -1;

    RT_ASSERT(can != RT_NULL);
    RT_ASSERT(buf != RT_NULL);

    p_drv = (struct n32_fdcan *)can->parent.user_data;
    RT_ASSERT(p_drv != RT_NULL);

    /* Scan dedicated TX Buffers for a free one */
    for (rt_uint32_t i = 0; i < FDCAN_TX_BUF_NUM; i++)
    {
        if (FDCAN_CheckTxBufRequest(p_drv->fdcan_x, FDCAN_TX_BUFFER0 << i) == RESET)
        {
            free_buf = (int32_t)i;
            break;
        }
    }

    if (free_buf < 0)
    {
        return -RT_EBUSY;
    }

    p_msg = (struct rt_can_msg *)buf;

    /* Set TX Header */
    p_drv->tx_header.IdType      = (p_msg->ide == RT_CAN_EXTID) ? FDCAN_EXTENDED_ID : FDCAN_STANDARD_ID;
    p_drv->tx_header.TxFrameType = (p_msg->rtr == RT_CAN_DTR) ? FDCAN_DATA_FRAME : FDCAN_REMOTE_FRAME;
    p_drv->tx_header.ID          = p_msg->id;
    p_drv->tx_header.DataLength  = _length_to_dlc(p_msg->len);

#ifdef RT_CAN_USING_CANFD
    p_drv->tx_header.FDFormat      = (p_msg->fd_frame == 1) ? FDCAN_FD_CAN : FDCAN_CLASSIC_CAN;
    p_drv->tx_header.BitRateSwitch = (p_msg->brs == 1) ? FDCAN_BRS_ON : FDCAN_BRS_OFF;
#endif

    /* Write message to the free dedicated TX Buffer */
    rt_uint32_t buf_bit = FDCAN_TX_BUFFER0 << free_buf;
    status              = FDCAN_AddMsgToTxBuffer(p_drv->fdcan_x, &p_drv->tx_header,
                                                 p_msg->data, buf_bit);
    if (status != SUCCESS)
    {
        return -RT_EBUSY;
    }

    /* Request transmission */
    FDCAN_EnableTxBufferRequest(p_drv->fdcan_x, buf_bit);
    p_drv->tx_pending_mask |= buf_bit;

    return RT_EOK;
}

/*==============================================================================
 * FDCAN operations table
 *============================================================================*/

static const struct rt_can_ops _fdcan_ops = {
    .configure           = _fdcan_configure,
    .control             = _fdcan_control,
    .sendmsg             = _fdcan_sendmsg,
    .recvmsg             = _fdcan_recvmsg,
    .sendmsg_nonblocking = _fdcan_sendmsg_nonblocking,
};

/*==============================================================================
 * FDCAN interrupt processing
 *============================================================================*/

/**
 *\*\name   _fdcan_int0_isr.
 *\*\fun    FDCAN INT0 interrupt handler (RX FIFO0 new message).
 *\*\       Checks the RX FIFO0 New Message flag, clears it,
 *\*\       and notifies the upper layer via rt_hw_can_isr.
 *\*\param  p_drv :
 *\*\          Pointer to FDCAN device structure
 *\*\return none
 */
static void _fdcan_int0_isr(struct n32_fdcan *p_drv)
{
    /* Check RX FIFO0 New Message flag */
    if (FDCAN_GetFlag(p_drv->fdcan_x, FDCAN_FLAG_RX_FIFO0_NEW_MESSAGE) == SET)
    {
        /* Clear flag */
        FDCAN_ClearFlag(p_drv->fdcan_x, FDCAN_FLAG_RX_FIFO0_NEW_MESSAGE);

        /* Notify upper layer that new message has arrived */
        rt_hw_can_isr(&p_drv->device, RT_CAN_EVENT_RX_IND | (CAN_RX_FIFO0 << 8));
    }
}

/**
 *\*\name   _fdcan_int1_isr.
 *\*\fun    FDCAN INT1 interrupt handler (TX Complete + Errors).
 *\*\       Handles:
 *\*\        - TX Complete: transmission completed event
 *\*\        - Bus Off / Error Warning / Error Passive / Arbitration Protocol Error
 *\*\param  p_drv :
 *\*\          Pointer to FDCAN device structure
 *\*\return none
 */
static void _fdcan_int1_isr(struct n32_fdcan *p_drv)
{
    FDCAN_Module *fdcan = p_drv->fdcan_x;
    rt_uint32_t   ecr_val;
    rt_uint32_t   psr_val;

    /* Check TX Complete flag */
    if (FDCAN_GetFlag(fdcan, FDCAN_FLAG_TX_COMPLETE) == SET)
    {
        FDCAN_ClearFlag(fdcan, FDCAN_FLAG_TX_COMPLETE);

        /* Determine which TX Buffer completed. FDCAN_CheckBufTxResult()
         * reads TXBTO which is a sticky snapshot of TXBRP — bits
         * accumulate across multiple completions, so after the first
         * successful send the ISR would forever report buffer 0 even
         * when buffer 1 or 2 actually just finished.  Instead walk
         * our software pending mask and look for buffers whose TXBRP
         * was just cleared by the hardware (pending → !pending). */
        rt_uint32_t buffer_idx = 0;
        rt_bool_t   found      = RT_FALSE;

        for (rt_uint32_t i = 0; i < FDCAN_TX_BUF_NUM; i++)
        {
            rt_uint32_t bit = FDCAN_TX_BUFFER0 << i;
            if ((p_drv->tx_pending_mask & bit) && !(fdcan->TXBRP & bit))
            {
                p_drv->tx_pending_mask &= ~bit;
                buffer_idx              = i;
                found                   = RT_TRUE;
                break;
            }
        }

        /* Fallback: if no buffer matched the TXBRP transition (should
         * not normally happen), report buffer 0 rather than silently
         * dropping the event. */
        if (!found)
        {
            for (rt_uint32_t i = 0; i < FDCAN_TX_BUF_NUM; i++)
            {
                rt_uint32_t bit = FDCAN_TX_BUFFER0 << i;
                if (p_drv->tx_pending_mask & bit)
                {
                    p_drv->tx_pending_mask &= ~bit;
                    buffer_idx              = i;
                    found                   = RT_TRUE;
                    break;
                }
            }
        }

        if (found)
            rt_hw_can_isr(&p_drv->device, RT_CAN_EVENT_TX_DONE | (buffer_idx << 8));
    }

    /* IR.EW/EP/PEA are bus protocol *status* change notifications, not
     * per-buffer completion events - AutoRetransmission keeps retrying a
     * still-pending Tx request straight through an Error-Passive/Warning
     * transition. Only a genuine Bus-Off entry actually makes the hardware
     * abort every pending Tx request, so that is the only status condition
     * reported as TX_FAIL - and only for the buffers that were actually
     * pending, the same way the TX Complete branch above discovers
     * completions via the tx_pending_mask/TXBRP transition. */
    if (FDCAN_GetFlag(fdcan, FDCAN_FLAG_BUS_OFF) == SET)
    {
        FDCAN_ClearFlag(fdcan, FDCAN_FLAG_BUS_OFF);

        if (fdcan->PSR & FDCAN_PSR_BO)
        {
            /* PSR.BO == 1 means this IR.BO edge is a Bus-Off *entry*; == 0
             * would mean leaving Bus-Off (recovery is kicked off separately
             * by the ARB_PROTOCOL_ERROR branch below). */
            for (rt_uint32_t i = 0; i < FDCAN_TX_BUF_NUM; i++)
            {
                rt_uint32_t bit = FDCAN_TX_BUFFER0 << i;
                if (p_drv->tx_pending_mask & bit)
                {
                    p_drv->tx_pending_mask &= ~bit;
                    rt_hw_can_isr(&p_drv->device, RT_CAN_EVENT_TX_FAIL | (i << 8));
                }
            }
        }
    }
    if (FDCAN_GetFlag(fdcan, FDCAN_FLAG_ERROR_WARNING) == SET)
    {
        FDCAN_ClearFlag(fdcan, FDCAN_FLAG_ERROR_WARNING);
    }
    if (FDCAN_GetFlag(fdcan, FDCAN_FLAG_ERROR_PASSIVE) == SET)
    {
        FDCAN_ClearFlag(fdcan, FDCAN_FLAG_ERROR_PASSIVE);
    }
    if (FDCAN_GetFlag(fdcan, FDCAN_FLAG_ARB_PROTOCOL_ERROR) == SET)
    {
        FDCAN_ClearFlag(fdcan, FDCAN_FLAG_ARB_PROTOCOL_ERROR);

        /* Check for Bus-Off recovery condition (ARB_PROTOCOL_ERROR + INIT) */
        if (fdcan->CCCR & FDCAN_CCCR_INIT)
        {
            /* Bus-Off state: set CCE, clear INIT to trigger recovery sequence */
            fdcan->CCCR                  |= FDCAN_CCCR_CCE;
            fdcan->CCCR                  &= ~FDCAN_CCCR_INIT;
            p_drv->device.status.errcode  = 0xFF;
        }
        else
        {
            /* Update error counters and status */
            ecr_val = fdcan->ECR;
            psr_val = fdcan->PSR;

            p_drv->device.status.rcverrcnt   = (ecr_val >> 8) & 0x000000FF;
            p_drv->device.status.snderrcnt   = (ecr_val) & 0x000000FF;
            p_drv->device.status.lasterrtype = psr_val & 0x00000007;
        }
    }
    if (FDCAN_GetFlag(fdcan, FDCAN_FLAG_DATA_PROTOCOL_ERROR) == SET)
    {
        FDCAN_ClearFlag(fdcan, FDCAN_FLAG_DATA_PROTOCOL_ERROR);
    }
}

/*==============================================================================
 * FDCAN interrupt service routines (ISR)
 *============================================================================*/

#ifdef BSP_USING_FDCAN1
/**
 *\*\name   FDCAN1_INT0_IRQHandler.
 *\*\fun    FDCAN1 INT0 interrupt service routine (RX FIFO0).
 *\*\return none
 */
void FDCAN1_INT0_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int0_isr(&_drv_fdcan1);
    rt_interrupt_leave();
}

/**
 *\*\name   FDCAN1_INT1_IRQHandler.
 *\*\fun    FDCAN1 INT1 interrupt service routine (TX Complete + Errors).
 *\*\return none
 */
void FDCAN1_INT1_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int1_isr(&_drv_fdcan1);
    rt_interrupt_leave();
}
#endif /* BSP_USING_FDCAN1 */

#ifdef BSP_USING_FDCAN2
void FDCAN2_INT0_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int0_isr(&_drv_fdcan2);
    rt_interrupt_leave();
}

void FDCAN2_INT1_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int1_isr(&_drv_fdcan2);
    rt_interrupt_leave();
}
#endif /* BSP_USING_FDCAN2 */

#ifdef BSP_USING_FDCAN3
void FDCAN3_INT0_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int0_isr(&_drv_fdcan3);
    rt_interrupt_leave();
}

void FDCAN3_INT1_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int1_isr(&_drv_fdcan3);
    rt_interrupt_leave();
}
#endif /* BSP_USING_FDCAN3 */

#ifdef BSP_USING_FDCAN4
void FDCAN4_INT0_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int0_isr(&_drv_fdcan4);
    rt_interrupt_leave();
}

void FDCAN4_INT1_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int1_isr(&_drv_fdcan4);
    rt_interrupt_leave();
}
#endif /* BSP_USING_FDCAN4 */

#ifdef BSP_USING_FDCAN5
void FDCAN5_INT0_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int0_isr(&_drv_fdcan5);
    rt_interrupt_leave();
}

void FDCAN5_INT1_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int1_isr(&_drv_fdcan5);
    rt_interrupt_leave();
}
#endif /* BSP_USING_FDCAN5 */

#ifdef BSP_USING_FDCAN6
void FDCAN6_INT0_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int0_isr(&_drv_fdcan6);
    rt_interrupt_leave();
}

void FDCAN6_INT1_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int1_isr(&_drv_fdcan6);
    rt_interrupt_leave();
}
#endif /* BSP_USING_FDCAN6 */

#ifdef BSP_USING_FDCAN7
void FDCAN7_INT0_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int0_isr(&_drv_fdcan7);
    rt_interrupt_leave();
}

void FDCAN7_INT1_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int1_isr(&_drv_fdcan7);
    rt_interrupt_leave();
}
#endif /* BSP_USING_FDCAN7 */

#ifdef BSP_USING_FDCAN8
void FDCAN8_INT0_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int0_isr(&_drv_fdcan8);
    rt_interrupt_leave();
}

void FDCAN8_INT1_IRQHandler(void)
{
    rt_interrupt_enter();
    _fdcan_int1_isr(&_drv_fdcan8);
    rt_interrupt_leave();
}
#endif /* BSP_USING_FDCAN8 */

/*==============================================================================
 * FDCAN driver initialization
 *============================================================================*/

/**
 *\*\name   rt_hw_fdcan_init.
 *\*\fun    Initialize and register all enabled FDCAN devices.
 *\*\       Performs clock enable for each enabled FDCAN instance,
 *\*\       then registers the device with the RT-Thread CAN framework.
 *\*\       GPIO pin initialization is handled by CubeMX-generated code
 *\*\       in n32h7xx_cfg.c.
 *\*\return 0
 */
static int rt_hw_fdcan_init(void)
{
    struct can_configure config;
    FDCAN_FilterType     default_filter;

    /* Default CAN configuration */
    config.baud_rate    = CAN1MBaud;
    config.msgboxsz     = RT_CANMSG_BOX_SZ;
    config.sndboxnumber = FDCAN_TX_BUF_NUM;
    config.mode         = RT_CAN_MODE_NORMAL;
    config.privmode     = RT_CAN_MODE_NOPRIV;
    config.ticks        = 50;
#ifdef RT_CAN_USING_HDR
    config.maxhdr = 14;
#endif
#ifdef RT_CAN_USING_CANFD
    config.baud_rate_fd = CAN1MBaud * 5;
    config.enable_canfd = 1;
#endif

    /* Default filter: accept all standard frames into RX FIFO0 */
    default_filter.IdType        = FDCAN_STANDARD_ID;
    default_filter.FilterIndex   = 0;
    default_filter.FilterType    = FDCAN_FILTER_MASK;
    default_filter.FilterConfig  = FDCAN_FILTER_TO_RXFIFO0;
    default_filter.FilterID1     = 0x000;
    default_filter.FilterID2     = 0x000;
    default_filter.RxBufferIndex = 0;

#ifdef BSP_USING_FDCAN1
    _drv_fdcan1.fdcan_x       = FDCAN1;
    _drv_fdcan1.filter_cfg    = default_filter;
    _drv_fdcan1.device.config = config;
    rt_hw_can_register(&_drv_fdcan1.device, _drv_fdcan1.name, &_fdcan_ops, &_drv_fdcan1);
    LOG_I("FDCAN1 registered");
#endif

#ifdef BSP_USING_FDCAN2
    _drv_fdcan2.fdcan_x       = FDCAN2;
    _drv_fdcan2.filter_cfg    = default_filter;
    _drv_fdcan2.device.config = config;
    rt_hw_can_register(&_drv_fdcan2.device, _drv_fdcan2.name, &_fdcan_ops, &_drv_fdcan2);
    LOG_I("FDCAN2 registered");
#endif

#ifdef BSP_USING_FDCAN3
    _drv_fdcan3.fdcan_x       = FDCAN3;
    _drv_fdcan3.filter_cfg    = default_filter;
    _drv_fdcan3.device.config = config;
    rt_hw_can_register(&_drv_fdcan3.device, _drv_fdcan3.name, &_fdcan_ops, &_drv_fdcan3);
    LOG_I("FDCAN3 registered");
#endif

#ifdef BSP_USING_FDCAN4
    _drv_fdcan4.fdcan_x       = FDCAN4;
    _drv_fdcan4.filter_cfg    = default_filter;
    _drv_fdcan4.device.config = config;
    rt_hw_can_register(&_drv_fdcan4.device, _drv_fdcan4.name, &_fdcan_ops, &_drv_fdcan4);
    LOG_I("FDCAN4 registered");
#endif

#ifdef BSP_USING_FDCAN5
    _drv_fdcan5.fdcan_x       = FDCAN5;
    _drv_fdcan5.filter_cfg    = default_filter;
    _drv_fdcan5.device.config = config;
    rt_hw_can_register(&_drv_fdcan5.device, _drv_fdcan5.name, &_fdcan_ops, &_drv_fdcan5);
    LOG_I("FDCAN5 registered");
#endif

#ifdef BSP_USING_FDCAN6
    _drv_fdcan6.fdcan_x       = FDCAN6;
    _drv_fdcan6.filter_cfg    = default_filter;
    _drv_fdcan6.device.config = config;
    rt_hw_can_register(&_drv_fdcan6.device, _drv_fdcan6.name, &_fdcan_ops, &_drv_fdcan6);
    LOG_I("FDCAN6 registered");
#endif

#ifdef BSP_USING_FDCAN7
    _drv_fdcan7.fdcan_x       = FDCAN7;
    _drv_fdcan7.filter_cfg    = default_filter;
    _drv_fdcan7.device.config = config;
    rt_hw_can_register(&_drv_fdcan7.device, _drv_fdcan7.name, &_fdcan_ops, &_drv_fdcan7);
    LOG_I("FDCAN7 registered");
#endif

#ifdef BSP_USING_FDCAN8
    _drv_fdcan8.fdcan_x       = FDCAN8;
    _drv_fdcan8.filter_cfg    = default_filter;
    _drv_fdcan8.device.config = config;
    rt_hw_can_register(&_drv_fdcan8.device, _drv_fdcan8.name, &_fdcan_ops, &_drv_fdcan8);
    LOG_I("FDCAN8 registered");
#endif

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_fdcan_init);

#endif /* BSP_USING_FDCAN1 || BSP_USING_FDCAN2 || ... || BSP_USING_FDCAN8 */
#endif /* RT_USING_CAN */
