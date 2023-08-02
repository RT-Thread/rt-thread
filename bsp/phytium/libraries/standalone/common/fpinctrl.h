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
 * FilePath: fpinctrl.h
 * Date: 2022-03-28 14:16:09
 * LastEditTime: 2022-03-28 14:16:10
 * Description:  This file is for IO pin ctrl API definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu   2022/3/28   init commit
 */
#ifndef  FPINCTRL_H
#define  FPINCTRL_H

#ifdef __cplusplus
extern "C"
{
#endif

/***************************** Include Files *********************************/
#include "ftypes.h"
#include "sdkconfig.h"

#if defined(CONFIG_TARGET_F2000_4) || defined(CONFIG_TARGET_D2000)
#include "fioctrl.h"

/**************************** Type Definitions *******************************/

typedef enum
{
    FPIN_FUNC0 = 0b000,
    FPIN_FUNC1,
    FPIN_FUNC2,
    FPIN_FUNC3 = 0b011,

    FPIN_NUM_OF_FUNC
} FPinFunc; /* 引脚复用功能配置, func0为默认功能 */

typedef enum
{
    FPIN_PULL_NONE = 0b00,
    FPIN_PULL_DOWN = 0b01,
    FPIN_PULL_UP = 0b10,

    FPIN_NUM_OF_PULL
} FPinPull; /* 引脚上下拉配置 */

typedef enum
{
    FPIN_OUTPUT_DELAY = 0, /* 延时设置方向为输出 */
    FPIN_INPUT_DELAY, /* 延时设置方向为输入 */

    FPIN_NUM_OF_DELAY_DIR
} FPinDelayDir; /* 引脚延时配置方向 */

typedef enum
{
    FPIN_DELAY_COARSE_TUNING = 0, /* 延迟粗调档位 */
    FPIN_DELAY_FINE_TUNING, /* 延迟精调档位 */

    FPIN_NUM_OF_DELAY_TYPE
} FPinDelayType; /* 引脚延时配置类型 */

typedef enum
{
    FPIN_DELAY_NONE = 0,
    FPIN_DELAY_1,
    FPIN_DELAY_2,
    FPIN_DELAY_3,
    FPIN_DELAY_4,
    FPIN_DELAY_5,
    FPIN_DELAY_6,
    FPIN_DELAY_7,

    FPIN_NUM_OF_DELAY
} FPinDelay;

typedef enum
{
    FPIN_DELAY_IN_TYPE = 0,     /*  input delay */
    FPIN_DELAY_OUT_TYPE = 1,    /* output delay */
} FPinDelayIOType;

typedef struct
{
    u32 reg_off; /* 引脚配置寄存器偏移量 */
    u32 reg_bit; /* 引脚配置起始位 */
} FPinIndex; /* 引脚索引 */
/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FPIN_NULL  {0xffffffff, 0}

/************************** Function Prototypes ******************************/
/* 获取IO引脚当前的复用功能 */
FPinFunc FPinGetFunc(const FPinIndex pin);

/* 设置IO引脚复用功能 */
void FPinSetFunc(const FPinIndex pin, FPinFunc func);

/* 获取IO引脚当前的上下拉设置 */
FPinPull FPinGetPull(const FPinIndex pin);

/* 设置IO引脚的上下拉 */
void FPinSetPull(const FPinIndex pin, FPinPull pull);

/* 获取IO引脚的复用、上下拉和驱动能力设置 */
void FPinGetConfig(const FPinIndex pin, FPinFunc *func, FPinPull *pull);

/* 设置IO引脚的复用、上下拉和驱动能力 */
void FPinSetConfig(const FPinIndex pin, FPinFunc func, FPinPull pull);

/* 获取IO引脚当前的单项延时设置 */
FPinDelay FPinGetDelay(const FPinIndex pin, FPinDelayDir dir, FPinDelayType type);

/* 检查IO引脚延时是否使能 */
boolean FPinGetDelayEn(const FPinIndex pin, FPinDelayDir dir);

/* 设置IO引脚单项延时 */
void FPinSetDelay(const FPinIndex pin, FPinDelayDir dir, FPinDelayType type, FPinDelay delay);

/* 使能或去使能IO引脚延时 */
void FPinSetDelayEn(const FPinIndex pin, FPinDelayDir dir, boolean enable);

/* Update and enable common IO pin delay config */
void FPinSetDelayConfig(const FPinIndex pin, FPinDelayIOType in_out_type, FPinDelay roungh_delay, FPinDelay delicate_delay, boolean enable);

/* Get current common IO pin delay config */
void FPinGetDelayConfig(const FPinIndex pin, FPinDelay *in_roungh_delay, FPinDelay *in_delicate_delay,
                        FPinDelay *out_roungh_delay, FPinDelay *out_delicate_delay);

#ifdef __cplusplus
}
#endif

#endif
#endif