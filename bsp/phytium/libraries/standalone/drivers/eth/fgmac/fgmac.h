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
 * FilePath: fgmac.h
 * Date: 2022-04-06 14:46:52
 * LastEditTime: 2022-04-06 14:46:58
 * Description:  This file is for gmac driver.
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/07/13    first release
 */


#ifndef  FGMAC_H
#define  FGMAC_H

#include "ftypes.h"
#include "fassert.h"
#include "ferror_code.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***************************** Include Files *********************************/

#define FGMAC_PHY_MAX_NUM                         32U

/************************** Constant Definitions *****************************/
#define FGMAC_SUCCESS               FT_SUCCESS
#define FGMAC_ERR_TIMEOUT           FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 1)
#define FGMAC_ERR_INVALID_DMA_MEM   FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 2)
#define FGMAC_ERR_NOT_READY         FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 3)
#define FGMAC_ERR_TRANS_FAILED      FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 4)
#define FGMAC_ERR_PHY_NOT_SUPPORT   FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 5)
#define FGMAC_ERR_PHY_IS_NOT_FOUND  FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 6)
#define FGMAC_ERR_FAILED            FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 7)
#define FGMAC_ERR_PHY_AUTO_FAILED   FT_MAKE_ERRCODE(ErrModBsp, ErrBspEth, 8)


#define FGMAC_ERR_CODE_PREFIX  FGMAC_ERR_TIMEOUT & (FT_ERRCODE_SYS_MODULE_MASK | FT_ERRCODE_SUB_MODULE_MASK)
#define FGMAC_NUM_OF_ERR_CODE  5

/********发送描述符********/

/* TDES0 包含发送的帧状态和描述符所有权信息 */
#define FGMAC_DMA_TDES0_DEFERRED                  BIT(0)
#define FGMAC_DMA_TDES0_UNDERFLOW_ERROR           BIT(1)
#define FGMAC_DMA_TDES0_EXCESSIVE_DEFERRAL        BIT(2)
#define FGMAC_DMA_TDES0_COLLISION_COUNT_MASK      GENMASK(6, 3)
#define FGMAC_DMA_TDES0_VLAN_FRAME                BIT(7)
#define FGMAC_DMA_TDES0_EXCESSIVE_COLLISIONS      BIT(8)
#define FGMAC_DMA_TDES0_LATE_COLLISION            BIT(9)
#define FGMAC_DMA_TDES0_NO_CARRIER                BIT(10)
#define FGMAC_DMA_TDES0_LOSS_CARRIER              BIT(11)
#define FGMAC_DMA_TDES0_PAYLOAD_ERROR             BIT(12)
#define FGMAC_DMA_TDES0_FRAME_FLUSHED             BIT(13)
#define FGMAC_DMA_TDES0_JABBER_TIMEOUT            BIT(14)
#define FGMAC_DMA_TDES0_ERROR_SUMMARY             BIT(15)
#define FGMAC_DMA_TDES0_IP_HEADER_ERROR           BIT(16)
#define FGMAC_DMA_TDES0_TIME_STAMP_STATUS         BIT(17)   /* 指示已捕获相应发送帧的时间戳 */
#define FGMAC_DMA_TDES0_OWN                       BIT(31)   /* 该位表示描述符归 DMA 所有 */

/* TDES1 包含缓冲区大小和控制描述符链/环和正在传输的帧的其他位 */
#define FGMAC_DMA_TDES1_BUFFER1_SIZE_MASK         GENMASK(10, 0)
#define FGMAC_DMA_TDES1_BUFFER2_SIZE_MASK         GENMASK(21, 11)
#define FGMAC_DMA_TDES1_BUFFER2_SIZE_SHIFT        11
#define FGMAC_DMA_TDES1_TIME_STAMP_ENABLE         BIT(22)
#define FGMAC_DMA_TDES1_DISABLE_PADDING           BIT(23)
#define FGMAC_DMA_TDES1_SECOND_ADDRESS_CHAINED    BIT(24)
#define FGMAC_DMA_TDES1_END_RING                  BIT(25)
#define FGMAC_DMA_TDES1_CRC_DISABLE               BIT(26)
#define FGMAC_DMA_TDES1_CHECKSUM_INSERTION_MASK   GENMASK(28, 27)
#define FGMAC_DMA_TDES1_CHECKSUM_INSERTION_SHIFT  27
#define FGMAC_DMA_TDES1_FIRST_SEGMENT             BIT(29)
#define FGMAC_DMA_TDES1_LAST_SEGMENT              BIT(30)
#define FGMAC_DMA_TDES1_INTERRUPT                 BIT(31)

/********接收描述符********/

/* RDES0 包含接收的帧状态，帧长度和描述符所有权信息 */
#define FGMAC_DMA_RDES0_PAYLOAD_CSUM_ERR          BIT(0)
#define FGMAC_DMA_RDES0_CRC_ERROR                 BIT(1)
#define FGMAC_DMA_RDES0_DRIBBLING                 BIT(2)
#define FGMAC_DMA_RDES0_MII_ERROR                 BIT(3)
#define FGMAC_DMA_RDES0_RECEIVE_WATCHDOG          BIT(4)
#define FGMAC_DMA_RDES0_FRAME_TYPE                BIT(5)
#define FGMAC_DMA_RDES0_COLLISION                 BIT(6)
#define FGMAC_DMA_RDES0_IPC_CSUM_ERROR            BIT(7)
#define FGMAC_DMA_RDES0_LAST_DESCRIPTOR           BIT(8)
#define FGMAC_DMA_RDES0_FIRST_DESCRIPTOR          BIT(9)
#define FGMAC_DMA_RDES0_VLAN_TAG                  BIT(10)
#define FGMAC_DMA_RDES0_OVERFLOW_ERROR            BIT(11)
#define FGMAC_DMA_RDES0_LENGTH_ERROR              BIT(12)
#define FGMAC_DMA_RDES0_SA_FILTER_FAIL            BIT(13)
#define FGMAC_DMA_RDES0_DESCRIPTOR_ERROR          BIT(14)
#define FGMAC_DMA_RDES0_ERROR_SUMMARY             BIT(15)
#define FGMAC_DMA_RDES0_FRAME_LEN_MASK            (0x3FFF << 16) /* GENMASK(29, 16)*/
#define FGMAC_DMA_RDES0_FRAME_LEN_SHIFT           16
#define FGMAC_DMA_RDES0_DA_FILTER_FAIL            BIT(30)
#define FGMAC_DMA_RDES0_OWN                       BIT(31)

/* RDES1 包含缓冲区大小和控制描述符链/环的其他位 */
#define FGMAC_DMA_RDES1_BUFFER1_SIZE_MASK         GENMASK(10, 0)
#define FGMAC_DMA_RDES1_BUFFER2_SIZE_MASK         GENMASK(21, 11)
#define FGMAC_DMA_RDES1_BUFFER2_SIZE_SHIFT        11
#define FGMAC_DMA_RDES1_SECOND_ADDRESS_CHAINED    BIT(24)
#define FGMAC_DMA_RDES1_END_RING                  BIT(25)
#define FGMAC_DMA_RDES1_DISABLE_IC                BIT(31)

/* Operational Mode */
enum
{
    FGMAC_CHECKSUM_BY_SOFTWARE = 0,
    FGMAC_CHECKSUM_BY_HARDWARE
}; /* software checksum or hardware checksum */

enum
{
    FGMAC_TX_COMPLETE_EVT = 0,
    FGMAC_RX_COMPLETE_EVT,
    FGMAC_LINK_STATUS_EVT,
    FGMAC_PHY_STATUS_EVT,
    FGMAC_DMA_ERR_EVT,

    FGMAC_INTR_EVT_NUM
}; /* interrupt event type */


/**************************** Type Definitions *******************************/

/**
 * This typedef contains configuration information for the device.
 */
typedef struct
{
    u32     instance_id;  /* device instance id */
    uintptr base_addr;    /* device base address */
    u32     irq_num;      /* irq num */
    u32     irq_prority;  /* device intrrupt priority */
    u32     cheksum_mode; /* hardware or software checksum */
    u32     duplex_mode;         /* selects the MAC duplex mode: Half-Duplex or Full-Duplex mode */
    u32     max_packet_size;  /* max num of bytes in frame transfer */
    u32     mdc_clk_hz;          /* MDC clock access PHY. [1.0MHz ~2.5MHz] */
    boolean en_auto_negtiation;  /* auto-negotiation or not */
    u32     speed;               /* sets the Ethernet speed: 10/100/1000 Mbps. */

} FGmacConfig; /* FGMAC 驱动配置数据 */

/**
 * This typedef contains driver instance data. The user is required to allocate a
 * variable of this type for every device in the system. A pointer
 * to a variable of this type is then passed to the driver API functions.
 */

typedef struct
{
    volatile u32 status;
    u32 ctrl;
    u32 buf_addr;
    u32 next;
} FGmacDmaDesc; /* FGMAC DMA描述符 */

typedef struct
{
    u32 desc_idx;       /* For Current Desc position */
    u32 desc_buf_idx;   /* For Current Desc buffer buf position */
    u32 desc_max_num;   /* Max Number for Desc and Desc buffer */
    u8 *desc_buf_base;  /*  Desc buffer Base */
} FGmacRingDescData; /* FGMAC DMA描述符表(链式)相关数据 */

typedef void (*FGmacEvtHandler)(void *pCtrl);

typedef struct
{
    FGmacConfig config;      /* Current active configs */
    u32         is_ready;    /* Device is initialized and ready */
    FGmacRingDescData rx_ring;  /* RX DMA descriptor data (idx, length) */
    volatile FGmacDmaDesc *rx_desc;  /* RX DMA descriptor table in ring */
    FGmacRingDescData tx_ring; /* TX DMA descriptor data (idx, length) */
    volatile FGmacDmaDesc *tx_desc; /* TX DMA descriptor table in ring */
    FGmacEvtHandler evt_handler[FGMAC_INTR_EVT_NUM]; /* User registered interrupt handler */
    u32 phy_valid_mask;     /* phy valid addr sequence mask */
    u32 phy_speed;
    u32 phy_addr;            /* phy max valid addr, or the unique value */
    u16 phy_id1;            /*phy tag,only value to identify phy*/
} FGmac; /* FGMAC 驱动控制数据 */

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/
/* 获取FGMAC驱动的默认配置参数 */
const FGmacConfig *FGmacLookupConfig(u32 instance_id);

/* 完成FGMAC驱动实例的初始化，使之可以使用 */
FError FGmacCfgInitialize(FGmac *instance_p, const FGmacConfig *cofig_p);

/* 完成FGMAC驱动实例去使能，清零实例数据 */
FError FGmacDeInitialize(FGmac *instance_p);

/* 配置FGMAC的发送DMA描述符和缓冲区 */
FError FGmacSetupTxDescRing(FGmac *instance_p, volatile FGmacDmaDesc *tx_desc_tbl,
                            u8 *tx_buf, const fsize_t tx_pre_buf_len, const fsize_t tx_buf_num);

/* 配置FGMAC的接收DMA描述符和缓冲区 */
FError FGmacSetupRxDescRing(FGmac *instance_p, volatile FGmacDmaDesc *rx_desc_tbl,
                            u8 *rx_buf, const fsize_t rx_pre_buf_len, const fsize_t rx_buf_num);

/* FGMAC中断处理函数 */
void FGmacInterruptHandler(s32 vector, void *param);

/* 注册FGMAC中断事件处理函数 */
void FGmacRegisterEvtHandler(FGmac *instance_p, u32 evt, FGmacEvtHandler handler);

/* 使能FGMAC DMA，使之可以接收/发送数据 */
FError FGmacStartTrans(FGmac *instance_p);

/* 去使能FGMAC DMA, 使之不再能接收/发送数据 */
FError FGmacStopTrans(FGmac *instance_p);

/* 通过FGMAC接收数据帧 */
FError FGmacRecvFrame(FGmac *instance_p);

/* 通过FGMAC发送数据帧 */
FError FGmacSendFrame(FGmac *instance_p, u32 frame_len);

/* 设置FGMAC中断屏蔽位 */
void FGmacSetInterruptMask(FGmac *instance_p, u32 intr_type, u32 mask);

/* 设置FGMAC中断使能位 */
void FGmacSetInterruptUmask(FGmac *instance_p, u32 intr_type, u32 mask);

/*fgmac deplex mode configuration */
void FGmacControllerDuplexConfig(FGmac *instance_p, u32 duplex);

/*fgmac speed configuration */
void FGmacControllerSpeedConfig(FGmac *instance_p, u32 speed);

#ifdef __cplusplus
}
#endif


#endif
