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
 * FilePath: fi2c.h
 * Date: 2021-11-01 14:53:42
 * LastEditTime: 2022-02-18 08:37:04
 * Description:  This file is for complete user external interface definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  zhugengyu 2021/11/1  first commit
 * 1.1  liushengming 2022/2/18  modified to support i2c
 */



#ifndef  FI2C_H
#define  FI2C_H

/***************************** Include Files *********************************/

#include "ftypes.h"
#include "fassert.h"
#include "ferror_code.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
#define FI2C_SUCCESS          FT_SUCCESS
#define FI2C_ERR_INVAL_PARM   FT_MAKE_ERRCODE(ErrModBsp, ErrBspI2c, 1)
#define FI2C_ERR_NOT_READY    FT_MAKE_ERRCODE(ErrModBsp, ErrBspI2c, 2)
#define FI2C_ERR_TIMEOUT      FT_MAKE_ERRCODE(ErrModBsp, ErrBspI2c, 3)
#define FI2C_ERR_NOT_SUPPORT  FT_MAKE_ERRCODE(ErrModBsp, ErrBspI2c, 4)
#define FI2C_ERR_INVAL_STATE  FT_MAKE_ERRCODE(ErrModBsp, ErrBspI2c, 5)

/* add up new error code above and plust FI2C_ERR_CODE_MAX by ONE*/
#define FI2C_ERR_CODE_MAX     FT_MAKE_ERRCODE(ErrModBsp, ErrBspI2c, 6)
#define FI2C_ERR_CODE_PREFIX  FI2C_ERR_CODE_MAX & (FT_ERRCODE_SYS_MODULE_MASK | FT_ERRCODE_SUB_MODULE_MASK)
#define FI2C_NUM_OF_ERR_CODE  FI2C_ERR_CODE_MAX & FT_ERRCODE_TAIL_VALUE_MASK

/*
 * status codes
 */
#define STATUS_IDLE                 0x0
#define STATUS_WRITE_IN_PROGRESS    0x1
#define STATUS_READ_IN_PROGRESS     0x2

enum
{
    FI2C_MASTER = 0, /* i2c主设备 */
    FI2C_SLAVE       /* i2c从设备 */
};

enum
{
    FI2C_SPEED_STANDARD_RATE = 100000, /* 100kb/s */
    FI2C_SPEED_FAST_RATE = 400000      /* 400kb/s */
};

enum
{
    FI2C_EVT_MASTER_TRANS_ABORTED = 0,/*master模式传输出错回调函数事件值*/
    FI2C_EVT_MASTER_READ_DONE,        /*master模式接收完成回调函数事件值*/
    FI2C_EVT_MASTER_WRITE_DONE,       /*master模式发送完成回调函数事件值*/

    FI2C_MASTER_INTR_EVT_NUM
}; /* master mode evt */

enum/*slave模式回调函数事件值*/
{
    FI2C_EVT_SLAVE_READ_REQUESTED = 0,  /*slave收到主机读取内容的请求*/
    FI2C_EVT_SLAVE_WRITE_REQUESTED,     /*slave收到主机发送的写请求*/
    FI2C_EVT_SLAVE_READ_PROCESSED,      /*在Slave发送模式下，发送完数据的最后一个字节后，在规定时间内没有收到 Master 端的回应*/
    FI2C_EVT_SLAVE_WRITE_RECEIVED,      /*Slave收到主机发送的数据，需要存下*/
    FI2C_EVT_SLAVE_STOP,                /*I2C总线接口上是否产生了STOP。与控制器工作在Master模式还是 Slave 模式无关。*/

    FI2C_SLAVE_INTR_EVT_NUM
}; /* slave mode evt */

/**************************** Type Definitions *******************************/

typedef struct
{
    u32         instance_id; /* Device instance id */
    uintptr     base_addr;   /* Device base address */
    u32         irq_num;     /* Device interrupt id */
    u32         irq_prority;  /* Device interrupt priority */
    u32         ref_clk_hz;   /* Input reference clock frequency in Hz */
    u32         work_mode;   /* Device work mode Slave or Master */
    u32         slave_addr;  /*Master mode Slave Address writing/reading to/from ,Slave mode set local address*/
    boolean     use_7bit_addr;  /* Slave in-chip address offset in 7bit or 10bit */
    u32         speed_rate;  /* I2C speed rate */
} FI2cConfig; /* Device configure setting */

typedef void (*FI2cEvtHandler)(void *instance_p, void *param);

typedef struct
{
    /* data */
    const void *data_buff;
    u32 tx_total_num;
    volatile u32 tx_cnt;
    u32 flag;/* CMD BIT(8), STOP BIT(9) and RESTART BIT(10) Generation */
} FI2cFrameTX;

typedef struct
{
    /* data */
    void *data_buff;
    u32 rx_total_num;
    volatile u32 rx_cnt;
} FI2cFrameRX;

typedef struct
{
    FI2cConfig      config;             /* Current active configs */
    u32             is_ready;           /* Device is initialized and ready */
    volatile u32    status;
    FI2cFrameTX     txframe;
    FI2cFrameRX     rxframe;
    /** only apply to master device **/
    /* Master interrupt handler */
    FI2cEvtHandler master_evt_handlers[FI2C_MASTER_INTR_EVT_NUM];

    /** only apply to slave device **/
    /* Slave interrupt handler */
    FI2cEvtHandler slave_evt_handlers[FI2C_SLAVE_INTR_EVT_NUM];

} FI2c; /* Device instance */

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/* fi2c_sinit.c */
/* 获取I2C驱动的默认配置参数 */
const FI2cConfig *FI2cLookupConfig(u32 instance_id);

/* fi2c.c */
/* 完成I2C驱动实例的初始化，使之可以使用*/
FError FI2cCfgInitialize(FI2c *instance_p, const FI2cConfig *cofig_p);

/* 完成I2C驱动实例去使能，清零实例数据 */
void FI2cDeInitialize(FI2c *instance_p);

/* 获取I2C模块错误码对应的错误信息 */
const char *FI2cErrorToMessage(FError error);

/* fi2c_master.c */
/* I2C主机读，阻塞直到完成读操作或失败 */
FError FI2cMasterReadPoll(FI2c *instance_p, u32 mem_addr, u8 mem_byte_len, u8 *buf_p, u32 buf_len);

/*I2C主机读，接收中断读操作或者失败 */
FError FI2cMasterReadIntr(FI2c *instance_p, u32 mem_addr, u8 mem_byte_len, u8 *buf_p, u32 buf_len);

/* I2C主机写，中断发送直到完成写操作或失败 */
FError FI2cMasterWriteIntr(FI2c *instance_p, u32 mem_addr, u8 mem_byte_len, const u8 *buf_p, u32 buf_len);

/* I2C主机写，阻塞直到完成写操作或失败 */
FError FI2cMasterWritePoll(FI2c *instance_p, u32 mem_addr, u8 mem_byte_len, const u8 *buf_p, u32 buf_len);

/* 获取I2C的中断值*/
u32 FI2cGetIntr(FI2c *instance_p);

/* 设置I2C主机的中断 */
FError FI2cMasterSetupIntr(FI2c *instance_p, u32 mask);

/* 主机模式中断服务函数 */
void FI2cMasterIntrHandler(s32 vector, void *param);

/* 注册I2C主机中断事件函数 */
void FI2cMasterRegisterIntrHandler(FI2c *instance_p, u32 evt, FI2cEvtHandler handler);

/* 设置I2C从机的中断 */
FError FI2cSlaveSetupIntr(FI2c *instance_p);

/* 从机模式中断服务函数 */
void FI2cSlaveIntrHandler(s32 vector, void *param);

/* 注册I2C从机中断事件函数 */
void FI2cSlaveRegisterIntrHandler(FI2c *instance_p, u32 evt, FI2cEvtHandler handler);

#ifdef __cplusplus
}
#endif

#endif
