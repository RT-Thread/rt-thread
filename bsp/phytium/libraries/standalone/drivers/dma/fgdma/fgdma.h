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
 * FilePath: fgdma.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:35
 * Description:  This file is for gdma user api implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe    2021/11/5    init commit
 * 1.1   zhugengyu  2022/5/16    modify according to tech manual.
 */

#ifndef FGDMA_H
#define FGDMA_H

#include "ftypes.h"
#include "fassert.h"
#include "ferror_code.h"
#include "fkernel.h"

#ifdef __cplusplus
extern "C"
{
#endif

/***************************** Include Files *********************************/



/************************** Constant Definitions *****************************/

/* gdma capacity mask  */

#define FGDMA_IRQ1_MASK BIT(0)   /* All Gdma channel share a single interrupt */
#define FGDMA_IRQ2_MASK BIT(1)   /* Each gdma channel owns an independent interrupt */
#define FGDMA_TRANS_NEED_RESET_MASK BIT(2) /* Gdma needs to be reset before transmission */

typedef enum
{
    FGDMA_OPER_NONE_PRIORITY_POLL = -1, /* Priority = -1 表示读写请求仲裁模式为Poll */
    FGDMA_OPER_PRIORITY0 = 0, /* Priority >= 0 表示读写请求仲裁模式为Qos */
    FGDMA_OPER_PRIORITY1 = 1,
    FGDMA_OPER_PRIORITY2 = 2,
    FGDMA_OPER_PRIORITY3 = 3,
    FGDMA_OPER_PRIORITY4 = 4,
    FGDMA_OPER_PRIORITY5 = 5,
    FGDMA_OPER_PRIORITY6 = 6,
    FGDMA_OPER_PRIORITY7 = 7,
    FGDMA_OPER_PRIORITY8 = 8,
    FGDMA_OPER_PRIORITY9 = 9,
    FGDMA_OPER_PRIORITY10 = 10,
    FGDMA_OPER_PRIORITY11 = 11,
    FGDMA_OPER_PRIORITY12 = 12,
    FGDMA_OPER_PRIORITY13 = 13,
    FGDMA_OPER_PRIORITY14 = 14,
    FGDMA_OPER_PRIORITY15 = 15
} FGdmaOperPriority; /* Qos配置，值越高，优先级越高 */

typedef enum
{
    FGDMA_OPER_DIRECT = 0, /* 直接操作模式 */
    FGDMA_OPER_BDL /* BDL操作模式 */
} FGdmaOperMode; /* 支持的操作模式 */

typedef enum
{
    FGDMA_WAIT_INTR = 0, /* 中断模式 */
    FGDMA_WAIT_POLL  /* 轮询模式 */
} FGdmaWaitEnd; /* 支持的等待传输完成的模式 */

typedef enum
{
    FGDMA_BURST_SIZE_1_BYTE = 0,
    FGDMA_BURST_SIZE_2_BYTE = 1,
    FGDMA_BURST_SIZE_4_BYTE = 2,
    FGDMA_BURST_SIZE_8_BYTE = 3,
    FGDMA_BURST_SIZE_16_BYTE = 4
} FGdmaBurstSize; /* 所支持的读写请求burst size范围，其值本身是一个二次幂指数
                   * 即，单次burst传输的最大数据字节数 = 2^burst size */

#define FGDMA_GET_BURST_BYTE(burst_size)   (1U << burst_size) /* 获取burst size所代表的单次burst传输的最大数据字节数 */

typedef enum
{
    FGDMA_CHAN_EVT_FIFO_EMPTY = 0, /* 通道Fifo空事件 */
    FGDMA_CHAN_EVT_FIFO_FULL,      /* 通道Fifo满事件 */
    FGDMA_CHAN_EVT_BDL_END,        /* BDL模式下一个BDL条目传输完成 */
    FGDMA_CHAN_EVT_TRANS_END,      /* 所有传输数据完成 */
    FGDMA_CHAN_EVT_BUSY,           /* 前一次传输未完成，当前还处于传输中 */

    FGDMA_CHAN_NUM_OF_EVT
} FGdmaChanEvtType; /* 通道中断事件 */

#define FGDMA_SUCCESS           FT_SUCCESS
#define FGDMA_ERR_NOT_INIT      FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 0)
#define FGDMA_ERR_CHAN_IN_USE   FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 1)
#define FGDMA_ERR_CHAN_NOT_INIT FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 2)
#define FGDMA_ERR_INVALID_ADDR  FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 3)
#define FGDMA_ERR_INVALID_SIZE  FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 4)
#define FGDMA_ERR_BDL_NOT_ENOUGH  FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 5)

#define FGDMA_ADDR_ALIGMENT                      128U /* BDL链表的地址需要按128字节对齐 */

/**************************** Type Definitions *******************************/
typedef struct _FGdma FGdma;
typedef struct _FGdmaChan FGdmaChan;

typedef struct
{
    u32 instance_id;                /* GDMA控制器ID */
    u32 irq_num[FGDMA_NUM_OF_CHAN]; /* GDMA控制器中断号 */
    u32 irq_prority;                /* GDMA控制器中断优先级 */
    volatile uintptr_t base_addr;   /* GDMA控制器基地址 */
    FGdmaOperPriority rd_qos;       /* 读操作优先级 */
    FGdmaOperPriority wr_qos;       /* 写操作优先级 */
    u32 caps;                       /* driver capacity */
} FGdmaConfig; /* GDMA控制器配置 */

typedef struct
{
    u32 src_addr_l; /* 0x0, 数据源地址低32位 */
    u32 src_addr_h; /* 0x4, 数据源地址高32位 */
    u32 dst_addr_l; /* 0x8, 数据目的地址低32位 */
    u32 dst_addr_h; /* 0xc, 数据目的地址高32位 */
#define FGDMA_SRC_TC_BDL_BURST_SET(x)      SET_REG32_BITS((x), 1U, 0U)
#define FGDMA_SRC_TC_BDL_SIZE_SET(x)       SET_REG32_BITS((x), 6U, 4U)
#define FGDMA_SRC_TC_BDL_LEN_SET(x)        SET_REG32_BITS((x), 15U, 8U)
    u32 src_tc;     /* 0x10, 源传输控制位 */
#define FGDMA_DST_TC_BDL_BURST_SET(x)      SET_REG32_BITS((x), 1U, 0U)
#define FGDMA_DST_TC_BDL_SIZE_SET(x)       SET_REG32_BITS((x), 6U, 4U)
#define FGDMA_DST_TC_BDL_LEN_SET(x)        SET_REG32_BITS((x), 15U, 8U)
    u32 dst_tc;     /* 0x14, 目的传输控制 */
    u32 total_bytes;/* 0x18, 传输数据总量，以Byte为单位  */
    u32 ioc;        /* 0x1c, 该条目传输完成中断产生控制位  */
} __attribute__((__packed__)) FGdmaBdlDesc; /* BDL描述符 */

FASSERT_STATIC(0x20U == sizeof(FGdmaBdlDesc));

typedef u32 FGdmaChanIndex;

typedef struct
{
    FGdmaChanIndex      chan_id; /* DMA通道ID */
    FGdmaOperPriority   rd_qos;  /* DMA通道读Qos配置 */
    FGdmaOperPriority   wr_qos;  /* DMA通道写Qos配置 */
    FGdmaOperMode       trans_mode; /* DMA通道的操作模式，直接模式或者BDL模式 */
    FGdmaWaitEnd        wait_mode; /* 等待传输完成信号的模式，中断模式或轮询模式 */
    /* Direct模式有效 */
    FGdmaBurstSize      rd_size; /* DMA读请求的burst size */
    FGdmaBurstSize      wr_size; /* DMA写请求的burst size */
    /* BDL模式有效 */
    boolean             roll_back; /* 循环模式，TRUE: 当前BDL列表完成后，从第一个BDL项从新开始传输 */
    FGdmaBdlDesc        *descs;
    u32                 total_desc_num;
    u32                 valid_desc_num;
} FGdmaChanConfig; /* DMA通道配置 */

typedef void (*FGdmaChanEvtHandler)(FGdmaChan *const chan, void *args);


typedef struct _FGdmaChan
{
    FGdmaChanConfig config;     /* DMA通道配置 */
    FGdma *gdma;                                              /* DMA控制器实例 */
    FGdmaChanEvtHandler evt_handlers[FGDMA_CHAN_NUM_OF_EVT];  /* DMA通道事件回调函数 */
    void *evt_handler_args[FGDMA_CHAN_NUM_OF_EVT];            /* DMA通道事件回调函数入参 */
} FGdmaChan; /* GDMA通道实例 */

typedef struct _FGdma
{
    FGdmaConfig config;       /* GDMA控制器配置 */
    u32 is_ready;             /* GDMA控制器初始化是否完成 */
    FGdmaChan *chans[FGDMA_NUM_OF_CHAN]; /* GDMA通道实例，如果通道没有分配，值为NULL */
} FGdma; /* GDMA控制器实例 */

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
/* 获取默认的通道配置 */
#define FGDMA_DEFAULT_DIRECT_CHAN_CONFIG(_chan_id)\
    (FGdmaChanConfig){ \
        .chan_id = (_chan_id),\
        .rd_size = FGDMA_BURST_SIZE_4_BYTE,\
        .wr_size = FGDMA_BURST_SIZE_4_BYTE,\
        .rd_qos = FGDMA_OPER_NONE_PRIORITY_POLL,\
        .wr_qos = FGDMA_OPER_NONE_PRIORITY_POLL,\
        .trans_mode = FGDMA_OPER_DIRECT,\
        .wait_mode = FGDMA_WAIT_INTR,\
        .roll_back = FALSE\
    }

#define FGDMA_DEFAULT_BDL_CHAN_CONFIG(_chan_id, _bdl_descs, _bdl_desc_num)\
    (FGdmaChanConfig){ \
        .chan_id = (_chan_id),\
        .rd_size = FGDMA_BURST_SIZE_4_BYTE,\
        .wr_size = FGDMA_BURST_SIZE_4_BYTE,\
        .rd_qos = FGDMA_OPER_NONE_PRIORITY_POLL,\
        .wr_qos = FGDMA_OPER_NONE_PRIORITY_POLL,\
        .trans_mode = FGDMA_OPER_BDL,\
        .wait_mode = FGDMA_WAIT_INTR,\
        .roll_back = FALSE,\
        .descs = _bdl_descs,\
        .total_desc_num = _bdl_desc_num,\
        .valid_desc_num = 0U\
    }

/************************** Function Prototypes ******************************/
/* 获取GDMA控制器默认配置 */
const FGdmaConfig *FGdmaLookupConfig(u32 instance_id);

/* 初始化GDMA控制器实例 */
FError FGdmaCfgInitialize(FGdma *const instance_p, const FGdmaConfig *config_p);

/* 去初始化GDMA控制器实例 */
void FGdmaDeInitialize(FGdma *const instance_p);

/* 分配指定GDMA通道 */
FError FGdmaAllocateChan(FGdma *const instance_p, FGdmaChan *const chan_p,
                         const FGdmaChanConfig *config_p);

/* 释放GDMA通道 */
FError FGdmaDellocateChan(FGdmaChan *const chan_p);

/* 直接操作模式下发起DMA传输 */
FError FGdmaDirectTransfer(FGdmaChan *const chan_p, uintptr src_addr, uintptr dst_addr, fsize_t data_len);

/* 设置BDL描述符的一个条目 */
FError FGdmaAppendBDLEntry(FGdmaChan *const chan_p, uintptr src_addr, uintptr dst_addr, fsize_t data_len);

/* BDL操作模式下发起DMA传输 */
FError FGdmaBDLTransfer(FGdmaChan *const chan_p);

/* 使能启动GDMA控制器 */
FError FGdmaStart(FGdma *const instance_p);

/* 停止GDMA控制器 */
FError FGdmaStop(FGdma *const instance_p);

/* GDMA中断处理函数 */
void FGdmaIrqHandler(s32 vector, void *args);
void FGdmaIrqHandlerPrivateChannel(s32 vector, void *args);

/* 注册GDMA通道事件回调函数 */
void FGdmaChanRegisterEvtHandler(FGdmaChan *const chan_p, FGdmaChanEvtType evt,
                                 FGdmaChanEvtHandler handler, void *handler_arg);

/* 打印当前的GDMA寄存器值, DEBUG模式下有效 */
void FGdmaDumpRegisterVals(uintptr base_addr, u32 max_chan);

#ifdef __cplusplus
}
#endif

#endif
