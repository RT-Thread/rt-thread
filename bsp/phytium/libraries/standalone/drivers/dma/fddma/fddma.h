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
 * FilePath: fddma.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:24:52
 * Description:  This file is for ddma interface definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/5/13    init commit
 */

#ifndef  FDDMA_H
#define  FDDMA_H

#include "ftypes.h"
#include "ferror_code.h"

#ifdef __cplusplus
extern "C"
{
#endif
/***************************** Include Files *********************************/

/************************** Constant Definitions *****************************/
/* ddma capacity mask  */

#define FDDMA_CAP_W0_ENABLE_IRQ  BIT(0)   /* the ddma have a different interrupt control,1: disable,0:enable*/
#define FDDMA_CAP_W1_ENABLE_IRQ  BIT(1)   /* the ddma have a different interrupt control,1: enable,0:disable  */

#define FDDMA_SUCCESS                   FT_SUCCESS
#define FDDMA_ERR_NOT_INIT              FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 0)
#define FDDMA_ERR_CHAN_BINDED           FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 1)
#define FDDMA_ERR_CHAN_RUNNING          FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 2)
#define FDDMA_ERR_INVALID_TRANS_SIZE    FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 3)
#define FDDMA_ERR_WAIT_TIMEOUT          FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 4)
#define FDDMA_ERR_INVALID_DDR_ADDR      FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 5)
#define FDDMA_ERR_BDL_NOT_ENOUGH         FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 6)
#define FDDMA_ERR_BDL_INVALID_ADDR         FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 7)
#define FDDMA_ERR_BDL_INVALID_SIZE         FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 8)
#define FDDMA_ERR_BDL_NO_INVALID_BLOCK        FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 9)

typedef struct FDdma_ FDdma;
typedef struct FDdmaChan_ FDdmaChan;
typedef enum
{
    FDDMA_CHAN_0 = 0,
    FDDMA_CHAN_1,
    FDDMA_CHAN_2,
    FDDMA_CHAN_3,
    FDDMA_CHAN_4,
    FDDMA_CHAN_5,
    FDDMA_CHAN_6,
    FDDMA_CHAN_7,

    FDDMA_NUM_OF_CHAN
} FDdmaChanIndex; /* DDMA channel index */

typedef enum
{
    FDDMA_CHAN_REQ_RX = 0,
    FDDMA_CHAN_REQ_TX,
} FDdmaChanRequst; /* DDMA channel direction */

typedef enum
{
    FDDMA_CHAN_EVT_REQ_DONE = 0,
    FDDMA_CHAN_EVT_FIFO_EMPTY,
    FDDMA_CHAN_EVT_FIFO_FULL,

    FDDMA_NUM_OF_CHAN_EVT
} FDdmaChanEvt; /* DDMA channel interrupt event */

#define FDDMA_SUCCESS                   FT_SUCCESS
#define FDDMA_ERR_NOT_INIT              FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 0)
#define FDDMA_ERR_CHAN_BINDED           FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 1)
#define FDDMA_ERR_CHAN_RUNNING          FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 2)
#define FDDMA_ERR_INVALID_TRANS_SIZE    FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 3)
#define FDDMA_ERR_WAIT_TIMEOUT          FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 4)
#define FDDMA_ERR_INVALID_DDR_ADDR      FT_MAKE_ERRCODE(ErrModBsp, ErrDdma, 5)

/**************************** Type Definitions *******************************/
typedef struct FDdma_ FDdma;
typedef struct FDdmaChan_ FDdmaChan;

typedef void (*FDdmaChanEvtHandler)(FDdmaChan *const dma_chan, void *arg); /* DMA interrupt event handler */

typedef struct
{
    u32 id;                     /* DDMA ctrl id */
    uintptr base_addr;          /* DDMA ctrl base address */
    u32 irq_num;                /* DDMA ctrl interrupt id */
    u32 irq_prority;            /* DDMA ctrl interrupt priority */
    u32 caps;
} FDdmaConfig; /* DDMA instance configuration */
typedef enum
{
    FDDMA_BURST_LENTH_1 = 0,
    FDDMA_BURST_LENTH_2 = 1,
    FDDMA_BURST_LENTH_4 = 3,
} FDdmaBurstLenth;

typedef enum
{
    FDDMA_BURST_SIZE_4_BYTE = 0,
    FDDMA_BURST_SIZE_1_BYTE = 1,
    FDDMA_BURST_SIZE_2_BYTE = 2,
} FDdmaBurstSize;

typedef struct
{
    u32 src_addr_l; /* 0x0, 数据源地址低32位 */
    u32 src_addr_h; /* 0x4, 数据源地址高32位 */
    u32 total_bytes; /*0x08, 传输数据总量*/
    u32 ioc;        /* 0x0c, 该条目传输完成中断产生控制位  */
} __attribute__((__packed__)) FDdmaBdlDesc; /* BDL描述符 */

typedef struct
{
    FDdmaChanIndex id;          /* DMA channel index */
    u32 slave_id;               /* Perpherial slave id for DDMA */
    FDdmaChanRequst req_mode;   /* DMA transfer direction */
    uintptr ddr_addr;           /* DMA channel DDR address, could be source or destination */
    u32 dev_addr;               /* DMA channel Perpherial, could be source or destination */
    u32 trans_len;              /* DMA channel transfer length */
#define FDDMA_MIN_TRANSFER_LEN      4  /* min bytes in transfer */
    u32 timeout;                /* timeout = 0 means no use DMA timeout */
    FDdmaBurstSize     rd_align;
    FDdmaBurstSize     wr_align;
       /*bdl 模式*/
    u32       total_desc_num;       /*总的条目数*/
    u32       valid_desc_num;       /*有效条目数*/
    FDdmaBdlDesc  *descs;           /*BDL 描述符*/
} FDdmaChanConfig;  /* DDMA channel instance */

typedef struct FDdmaChan_
{
    FDdmaChanConfig config; /* DDMA channel configuration */
    boolean is_used;        /* TRUE means channel is in use */
    FDdma *dma;             /* DMA instance of this channel */
    FDdmaChanEvtHandler evt_handler[FDDMA_NUM_OF_CHAN_EVT]; /* interrupt evt */
    void *evt_handler_args[FDDMA_NUM_OF_CHAN_EVT]; /* interrupt evt args */
} FDdmaChan; /* DDMA channel instance */

typedef struct FDdma_
{
    FDdmaConfig config;  /* DDMA instance configuration */
    FDdmaChan   *chan[FDDMA_NUM_OF_CHAN];  /* DDMA channel instance, NULL means channel not yet allocate */
    u32 is_ready;        /* TRUE means DDMA init ok */
    u32 bind_status;     /* channel bind status, BIT(n) = 1 means channel n is allocated */
} FDdma; /* DDMA instance */

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FDDMA_DDR_ADDR_ALIGMENT         128 /* DMA DDR Buffer need align wiht 128 bytes */

#define FDDMA_GET_BURST_SIZE(brust_align)   (1U << brust_align)

#define FDDMA_BDL_ADDR_ALIGMENT                      128U  /* BDL模式的地址需要按128位对齐 */
#define FDDMA_BDL_VALID_NUM                          4U    /*BDL模式下所有条目数据总量必须为4的倍数*/
/************************** Function Prototypes ******************************/
/* 获取DDMA实例默认配置 */
const FDdmaConfig *FDdmaLookupConfig(u32 instance_id);

/* 初始化DDMA控制器 */
FError FDdmaCfgInitialization(FDdma *const instance, const FDdmaConfig *input_config);

/* 去初始化DDMA控制器 */
void FDdmaDeInitialization(FDdma *const instance);

/* 按照配置分配DDMA通道 */
FError FDdmaAllocateChan(FDdma *const instance, FDdmaChan *const dma_chan, const FDdmaChanConfig *dma_chan_config);

/* 释放之前分配的DDMA通道 */
FError FDdmaDellocateChan(FDdmaChan *const dma_chan);

/* 使能指定的DDMA通道，调用FDdmaAllocateChan后无需调用此函数 */
FError FDdmaActiveChan(FDdmaChan *const dma_chan);

/* 去使能DDMA通道 */
FError FDdmaDeactiveChan(FDdmaChan *const dma_chan);

/* 启动DDMA控制器并开始传输 */
FError FDdmaStart(FDdma *const instance);

/* 停止DDMA控制器 */
FError FDdmaStop(FDdma *const instance);

/* DDMA中断处理函数 */
void FDdmaIrqHandler(s32 vector, void *args);

/* 注册DDMA通道中断响应事件函数 */
void FDdmaRegisterChanEvtHandler(FDdmaChan *const dma_chan,
                                 FDdmaChanEvt evt,
                                 FDdmaChanEvtHandler handler,
                                 void *handler_arg);
/* DDMA控制器寄存器自检测试 */
void FDdmaDumpRegisters(uintptr base_addr);

void FDdmaDumpChanRegisters(uintptr base_addr, FDdmaChanIndex chan);

#ifdef __cplusplus
}
#endif

#endif