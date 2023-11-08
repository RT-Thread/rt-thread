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
/***************************** Include Files *********************************/
#include "ftypes.h"
#include "fassert.h"
#include "ferror_code.h"
#include "fkernel.h"

#include "fparameters.h"

#ifdef __cplusplus
extern "C"
{
#endif
/************************** Constant Definitions *****************************/
/* gdma capacity mask  */

#define FGDMA_IRQ1_MASK BIT(0)   /* All Gdma channel share a single interrupt */
#define FGDMA_IRQ2_MASK BIT(1)   /* Each gdma channel owns an independent interrupt */
#define FGDMA_TRANS_NEED_RESET_MASK BIT(2) /* Gdma needs to be reset before transmission */

typedef enum
{
    FGDMA_ARBITRATION_POLL = 0, /* 轮询模式 */
    FGDMA_ARBITRATION_QOS       /* Qos模式 */
} FGdmaArbitrationMode;         /* 控制器仲裁模式 */

typedef enum
{
    FGDMA_OPER_NONE_PRIORITY_POLL = -1, /* Priority = -1 表示读写请求仲裁模式为Poll */
    FGDMA_OPER_PRIORITY0 = 0,           /* Priority >= 0 表示读写请求仲裁模式为Qos */
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
    FGDMA_BURST_LENGTH_1 = 0,
    FGDMA_BURST_LENGTH_2 = 1,
    FGDMA_BURST_LENGTH_3 = 2,
    FGDMA_BURST_LENGTH_4 = 3,
    FGDMA_BURST_LENGTH_5 = 4,
    FGDMA_BURST_LENGTH_6 = 5,
    FGDMA_BURST_LENGTH_7 = 6,
    FGDMA_BURST_LENGTH_8 = 7
} FGdmaBurstLength; /* 所支持的读写请求burst length范围，其值加1为实际burst length值 */

typedef enum
{
    FGDMA_BURST_TYPE_FIXED = 0,
    FGDMA_BURST_TYPE_INCR
} FGdmaBurstType; /* 所支持的读写请求burst type，FIXED-读写仅在初始brust size内进行，INCR-读写递增传输 */

typedef enum
{
    FGDMA_CHAN_EVT_FIFO_EMPTY = 0, /* 通道Fifo空事件 */
    FGDMA_CHAN_EVT_FIFO_FULL,      /* 通道Fifo满事件 */
    FGDMA_CHAN_EVT_BDL_END,        /* BDL模式下一个BDL条目传输完成 */
    FGDMA_CHAN_EVT_TRANS_END,      /* 所有传输数据完成 */
    FGDMA_CHAN_EVT_BUSY,           /* 前一次传输未完成，当前还处于传输中 */

    FGDMA_CHAN_NUM_OF_EVT
} FGdmaChanEvtType; /* 通道中断事件 */

#define FGDMA_SUCCESS             FT_SUCCESS
#define FGDMA_ERR_COMMON          FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 0)
#define FGDMA_ERR_NOT_INIT        FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 1)
#define FGDMA_ERR_WRONG_PARA      FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 2)
#define FGDMA_ERR_CHAN_IN_USE     FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 3)
#define FGDMA_ERR_CHAN_NOT_INIT   FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 4)
#define FGDMA_ERR_INVALID_ADDR    FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 5)
#define FGDMA_ERR_INVALID_SIZE    FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 6)
#define FGDMA_ERR_BDL_NOT_ENOUGH  FT_MAKE_ERRCODE(ErrModBsp, ErrGdma, 7)

#define FGDMA_BDL_DESC_ALIGMENT                     128U /* BDL链表的地址需要按128字节对齐 */
/**************************** Type Definitions *******************************/
typedef struct _FGdma FGdma;
typedef struct _FGdmaChanIrq FGdmaChanIrq;

typedef struct
{
    u32                 instance_id;                /* GDMA控制器ID */
    u32                 irq_num[FGDMA_NUM_OF_CHAN]; /* GDMA控制器中断号 */
    u32                 irq_prority;                /* GDMA控制器中断优先级 */
    u32                 caps;                       /* GDMA控制器能力：标志传输前是否reset与通道中断是否共享等 */
    volatile uintptr_t  base_addr;                  /* GDMA控制器基地址 */
    FGdmaOperPriority   rd_qos;                     /* GDMA控制器读操作QoS优先级，表示GDMA控制器与别的控制器之间优先级关系 */
    FGdmaOperPriority   wr_qos;                     /* GDMA控制器写操作QoS优先级，表示GDMA控制器与别的控制器之间优先级关系 */
    FGdmaWaitEnd        wait_mode;                  /* GDMA控制器结果响应模式 */
} FGdmaConfig;                                      /* GDMA控制器配置 */

typedef struct
{
    u32 src_addr_l;                         /* 0x0, 数据源地址低32位 */
    u32 src_addr_h;                         /* 0x4, 数据源地址高32位 */
    u32 dst_addr_l;                         /* 0x8, 数据目的地址低32位 */
    u32 dst_addr_h;                         /* 0xc, 数据目的地址高32位 */
#define FGDMA_SRC_TC_BDL_BURST_SET(x)      SET_REG32_BITS((x), 1U, 0U)
#define FGDMA_SRC_TC_BDL_SIZE_SET(x)       SET_REG32_BITS((x), 6U, 4U)
#define FGDMA_SRC_TC_BDL_LEN_SET(x)        SET_REG32_BITS((x), 15U, 8U)
    u32 src_tc;                             /* 0x10, 源传输控制位 */
#define FGDMA_DST_TC_BDL_BURST_SET(x)      SET_REG32_BITS((x), 1U, 0U)
#define FGDMA_DST_TC_BDL_SIZE_SET(x)       SET_REG32_BITS((x), 6U, 4U)
#define FGDMA_DST_TC_BDL_LEN_SET(x)        SET_REG32_BITS((x), 15U, 8U)
    u32 dst_tc;                             /* 0x14, 目的传输控制 */
    u32 total_bytes;                        /* 0x18, 传输数据总量，以Byte为单位  */
    u32 ioc;                                /* 0x1c, 该条目传输完成中断产生控制位  */
} __attribute__((__packed__)) FGdmaBdlDesc; /* BDL描述符定义 */

FASSERT_STATIC(0x20U == sizeof(FGdmaBdlDesc));

typedef u32 FGdmaChanIndex;

typedef struct
{
    FGdmaOperMode     trans_mode;       /* GDMA通道的操作模式，直接模式或者BDL模式 */
    FGdmaWaitEnd      wait_mode;        /* GDMA通道结果响应模式 */
    FGdmaOperPriority rd_qos;           /* GDMA通道读操作Qos优先级，表示控制器内部不同通道之间的优先级关系 */
    FGdmaOperPriority wr_qos;           /* GDMA通道写操作Qos优先级，表示控制器内部不同通道之间的优先级关系*/
    /* Direct模式有效 */
    uintptr           src_addr;         /* GDMA传输源地址-物理地址 */
    uintptr           dst_addr;         /* GDMA传输目的地址-物理地址 */
    fsize_t           trans_length;     /* GDMA传输总数据量 */
    FGdmaBurstType    rd_type;          /* GDMA通道读操作burst type */
    FGdmaBurstType    wr_type;          /* GDMA通道写操作burst type */    
    FGdmaBurstSize    rd_size;          /* GDMA通道读操作burst size */
    FGdmaBurstSize    wr_size;          /* GDMA通道写操作burst size */
    FGdmaBurstLength  rd_length;        /* GDMA通道读操作burst length */
    FGdmaBurstLength  wr_length;        /* GDMA通道写操作burst length */
    /* BDL模式有效 */
    FGdmaBdlDesc      *first_desc_addr; /* BDL描述符列表首地址-物理地址 */
    fsize_t           valid_desc_num;   /* 需要使用的BDL描述符个数，从BDL描述符列表第一个描述符开始计数 */
    boolean           roll_back;        /* GDMA通道循环模式，TRUE: 当前BDL描述符列表传输完成后，再次从第一个BDL描述符重新开始传输 */
} FGdmaChanConfig; /* GDMA通道配置 */

typedef struct
{
    fsize_t           current_desc_num; /* 表示当前操作的是所在描述符列表中的第几个描述符 */
    uintptr           src_addr;         /* GDMA传输源地址-物理地址 */
    uintptr           dst_addr;         /* GDMA传输目的地址-物理地址 */
    fsize_t           trans_length;     /* 单个描述符所负责的传输数据量 */
    FGdmaBurstType    rd_type;          /* GDMA通道读操作burst type */
    FGdmaBurstType    wr_type;          /* GDMA通道写操作burst type */    
    FGdmaBurstSize    rd_size;          /* GDMA通道读操作burst size */
    FGdmaBurstSize    wr_size;          /* GDMA通道写操作burst size */
    FGdmaBurstLength  rd_length;        /* GDMA通道读操作burst length */
    FGdmaBurstLength  wr_length;        /* GDMA通道写操作burst length */
    boolean           ioc;              /* TRUE：该描述符传输完成会单独输出一个中断和置位状态位（DMA_Cx_STATE的[2]位）；FLASE：不单独输出 */
} FGdmaBdlDescConfig;  /* BDL描述符配置，同一个描述符列表中的不同描述符可以单独配置为不同的burst type、burst size、burst legth */

typedef void (*FGdmaChanEvtHandler)(FGdmaChanIrq *const chan_irq_info_p, void *args);
typedef struct _FGdmaChanIrq
{   
    FGdmaChanIndex      chan_id;                                  /* 信息所属GDMA通道的ID */
    FGdma               *gdma_instance;                           /* 信息所属GDMA通道所属的GDMA控制器实例 */
    void                *evt_handler_args[FGDMA_CHAN_NUM_OF_EVT]; /* GDMA通道事件回调函数输入参数 */
    FGdmaChanEvtHandler evt_handlers[FGDMA_CHAN_NUM_OF_EVT];      /* GDMA通道事件回调函数 */
} FGdmaChanIrq; /* GDMA通道中断回调信息 */

typedef struct _FGdma
{
    FGdmaConfig        config;                         /* GDMA控制器配置 */
    u32                gdma_ready;                     /* GDMA控制器初始化是否完成 */
    u32                chan_ready_flag;                /* GDMA通道使用标志位，第几位表示第几个通道进行完传输前的所有配置 */
    FGdmaChanIrq       chan_irq_info[FGDMA_NUM_OF_CHAN];   /* GDMA通道中断回调信息 */
} FGdma; /* GDMA控制器实例 */
/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
/* 获取默认的通道配置 */
#define FGDMA_DEFAULT_CHAN_CONFIG() \
    (FGdmaChanConfig){ \
        .trans_mode = FGDMA_OPER_DIRECT,\
        .wait_mode = FGDMA_WAIT_INTR,\
        .rd_qos = FGDMA_OPER_NONE_PRIORITY_POLL,\
        .wr_qos = FGDMA_OPER_NONE_PRIORITY_POLL,\
        .src_addr = 0,\
        .dst_addr = 0,\
        .trans_length = 0,\
        .rd_type = FGDMA_BURST_TYPE_INCR,\
        .wr_type = FGDMA_BURST_TYPE_INCR,\
        .rd_size = FGDMA_BURST_SIZE_16_BYTE,\
        .wr_size = FGDMA_BURST_SIZE_16_BYTE,\
        .rd_length = FGDMA_BURST_LENGTH_8,\
        .wr_length = FGDMA_BURST_LENGTH_8,\
        .roll_back = FALSE,\
        .valid_desc_num = 4,\
    }

/* 获取默认的描述符配置 */
#define FGDMA_DEFAULT_DESC_CONFIG()\
    (FGdmaBdlDescConfig){ \
        .src_addr = 0,\
        .dst_addr = 0,\
        .trans_length = 0,\
        .rd_type = FGDMA_BURST_TYPE_INCR,\
        .wr_type = FGDMA_BURST_TYPE_INCR,\
        .rd_size = FGDMA_BURST_SIZE_16_BYTE,\
        .wr_size = FGDMA_BURST_SIZE_16_BYTE,\
        .rd_length = FGDMA_BURST_LENGTH_8,\
        .wr_length = FGDMA_BURST_LENGTH_8,\
        .ioc = FALSE,\
    }
/************************** Function Prototypes ******************************/
/* 获取GDMA控制器默认配置 */
const FGdmaConfig *FGdmaLookupConfig(u32 instance_id);

/* 初始化GDMA控制器 */
FError FGdmaCfgInitialize(FGdma *const instance_p, FGdmaConfig const *controller_config_p);

/* 去初始化GDMA控制器 */
void FGdmaDeInitialize(FGdma *const instance_p);

/* 配置一个BDL描述符 */
FError FGdmaBDLSetDesc(FGdmaBdlDesc *const first_desc_addr_p, FGdmaBdlDescConfig const *bdl_desc_config_p);

/* 配置GDMA通道 */
FError FGdmaChanConfigure(FGdma *const instance_p, FGdmaChanIndex channel_id, FGdmaChanConfig const* channel_config_p);

/* 释放GDMA通道 */
FError FGdmaChanDeconfigure(FGdma *const instance_p, FGdmaChanIndex channel_id);

/* 启动某个GDMA通道传输 */
void FGdmaChanStartTrans(FGdma *const instance_p, FGdmaChanIndex channel_id);

/* 全局启动GDMA传输，被配置的GDMA通道将同时开始传输 */
void FGdmaGlobalStartTrans(FGdma *const instance_p);

/* GDMA通道Abort操作, 也可以作为单通道传输完毕后的通道停止操作，不会进行软复位操作 */
FError FGdmaChanAbort(FGdma *const instance_p, FGdmaChanIndex channel_id);

/* GDMA全局停止操作，所有通道传输停止，但是不会进行软复位操作 */
FError FGdmaGlobalStop(FGdma *const instance_p);

/* GDMA中断处理函数 */
void FGdmaIrqHandler(s32 vector, void *args);
void FGdmaIrqHandlerPrivateChannel(s32 vector, void *args);

/* 注册GDMA通道事件回调函数 */
void FGdmaChanRegisterEvtHandler(FGdma *const instance_p,
                                 FGdmaChanIndex channel_id,
                                 FGdmaChanEvtType evt,
                                 FGdmaChanEvtHandler handler, 
                                 void *handler_arg);

/* 打印当前的GDMA寄存器值, DEBUG模式下有效 */
void FGdmaDumpRegisterVals(uintptr base_addr, u32 max_chan);

#ifdef __cplusplus
}
#endif

#endif
