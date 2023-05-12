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
 * FilePath: ftimer_tacho.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 09:09:43
 * Description:  This file is for user ftimer_tacho API definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0  liushengming 2022/02/18   first commit
 */

#ifndef FTIMER_TACHO_H
#define FTIMER_TACHO_H

#include "ftypes.h"
#include "fdebug.h"
#include "ferror_code.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define FTIMER_TACHO_SUCCESS          FT_SUCCESS
#define FTIMER_TACHO_ERR_INVAL_PARM   FT_MAKE_ERRCODE(ErrModBsp, ErrBspTimer, 1)
#define FTIMER_TACHO_ERR_NOT_READY    FT_MAKE_ERRCODE(ErrModBsp, ErrBspTimer, 2)
#define FTIMER_TACHO_ERR_INIT_FAILED  FT_MAKE_ERRCODE(ErrModBsp, ErrBspTimer, 3)
#define FTIMER_TACHO_ERR_NOT_SUPPORT  FT_MAKE_ERRCODE(ErrModBsp, ErrBspTimer, 4)
#define FTIMER_TACHO_ERR_INVAL_STATE  FT_MAKE_ERRCODE(ErrModBsp, ErrBspTimer, 5)
#define FTIMER_TACHO_ERR_IS_READ      FT_MAKE_ERRCODE(ErrModBsp, ErrBspTimer, 6)
#define FTIMER_TACHO_ERR_ABORT        FT_MAKE_ERRCODE(ErrModBsp, ErrBspTimer, 7)
#define FTIMER_TACHO_ERR_FAILED       FT_MAKE_ERRCODE(ErrModBsp, ErrBspTimer, 8)

#define FTIMER_DEBUG_TAG "TIMER"
#define FTIMER_ERROR(format, ...)   FT_DEBUG_PRINT_E(FTIMER_DEBUG_TAG, format, ##__VA_ARGS__)
#define FTIMER_INFO(format, ...)    FT_DEBUG_PRINT_I(FTIMER_DEBUG_TAG, format, ##__VA_ARGS__)
#define FTIMER_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FTIMER_DEBUG_TAG, format, ##__VA_ARGS__)

#define FTACHO_DEBUG_TAG "TACHO"
#define FTACHO_ERROR(format, ...)   FT_DEBUG_PRINT_E(FTACHO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FTACHO_INFO(format, ...)    FT_DEBUG_PRINT_I(FTACHO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FTACHO_DEBUG(format, ...)   FT_DEBUG_PRINT_D(FTACHO_DEBUG_TAG, format, ##__VA_ARGS__)

typedef enum
{
    /*TimerTacho mode */
    FTIMER_WORK_MODE_TIMER = 0,
    FTIMER_WORK_MODE_TACHO,
    FTIMER_WORK_MODE_CAPTURE
} FTimerTachoModeType;

typedef enum
{
    /*Timer count mode*/
    FTIMER_FREE_RUN = 0,
    FTIMER_RESTART
} FTimerCntModeType;

typedef enum
{
    FTIMER_32_BITS = 0,
    FTIMER_64_BITS
} FTimerBitsType;

typedef enum
{
    FTIMER_ONCE_CMP = 0,
    FTIMER_CYC_CMP
} FTimerCmpType;

typedef enum
{
    FTACHO_EVENT_OVER = 0,      /*tacho超速事件*/
    FTACHO_EVENT_UNDER,         /*tacho低速事件*/
    FTIMER_EVENT_ROLL_OVER,     /*计数器翻转事件*/
    FTIMER_EVENT_ONCE_CMP,      /*单次定时输出事件*/
    FTIMER_EVENT_CYC_CMP,       /*重复定时输出事件*/
    FTACHO_EVENT_CAPTURE,       /*tacho输入捕获事件*/

    FMAX_TIMER_TACHO_EVENT
} FTimerTachoEventType;

typedef enum
{
    FTACHO_FALLING_EDGE = 0,    /*下降沿触发模式*/
    FTACHO_RISING_EDGE,         /*上升沿触发模式*/
    FTACHO_DOUBLE_EDGE          /*双边沿触发模式*/
} FTachoEdgeType;

typedef enum
{
    FTACHO_JITTER_LEVEL0 = 0,     /*消抖等级*/
    FTACHO_JITTER_LEVEL1,
    FTACHO_JITTER_LEVEL2,
    FTACHO_JITTER_LEVEL3,
} FTachoJitterLevelType;

typedef struct
{
    u32     id;        /* id of timer tacho */
    char    name[12];  /* instance name */
    u32     irq_priority; /* intr priority */
    u32     work_mode;  /* timer/tacho/capture mode */
    /* for timer function */
    u32     timer_mode; /* free-run/restart */
    u32     timer_bits; /* 32/64 bits */
    u32     cmp_type; /* once/cycle cmp */
    boolean clear_cnt;  /* clear timer counts */
    boolean force_load; /* start count from start val */
    /* for tacho function */
    u32     edge_mode; /* rising/falling/double */
    u32     jitter_level; /* jitter level */
    u32     plus_num;  /* plus_num of period to calculate rpm */
    u32     captue_cnt; /* in capture mode, when cnt reach this val, intr asserted */
} FTimerTachoConfig;

typedef void (*FTimerEventHandler)(void *instance_p);

typedef struct
{
    FTimerTachoConfig     config;   /* Current active configs */
    boolean               isready;  /* Device is initialized and ready */
    FTimerEventHandler    evt_handlers[FMAX_TIMER_TACHO_EVENT];/* event handler for interrupt */
} FTimerTachoCtrl;

/* Time & Tacho API */
/*将控制器复位*/
FError FTimerSoftwareReset(FTimerTachoCtrl *instance_p);

/*获取中断设置*/
u32 FTimerGetInterruptMask(FTimerTachoCtrl *instance_p);

/*设置中断,根据不同的intrType，将对于的中断mask置位*/
void FTimerSetInterruptMask(FTimerTachoCtrl *instance_p,
                            FTimerTachoEventType intrType,
                            boolean enable);

/*启动timer_tacho外设,根据不同的功能，开启使能位*/
FError FTimerStart(FTimerTachoCtrl *instance_p);

/*停止timer外设，根据不同的功能，关闭使能位，计数值停止并冻结*/
FError FTimerStop(FTimerTachoCtrl *instance_p);

/*用于timer 与 tacho-capture两种模式的切换，切换需要失能和清除计数器*/
FError FTimerSwithMode(FTimerTachoCtrl *instance_p, FTimerTachoConfig *new_config_p);

/* 注册中断事件处理回调函数 */
void FTimerRegisterEvtCallback(FTimerTachoCtrl *instance_p,
                               FTimerTachoEventType evt,
                               FTimerEventHandler callback);

/*打印寄存器信息*/
FError FTimeSettingDump(const FTimerTachoCtrl *instance_p);

/*TimerTacho中断处理函数，如果注册回调函数，则跳转到回调函数*/
void FTimerTachoIntrHandler(s32 vector, void *param);

/*根据工作模式和状态设置相应的中断*/
void FTimerTachoSetIntr(FTimerTachoCtrl *instance_p);

/* Timer API */
/*完成TimerTacho驱动实例的初始化，使之在就绪状态*/
FError FTimerInit(FTimerTachoCtrl *instance_p, const FTimerTachoConfig *config_p);

/*获取Timer驱动的默认配置参数*/
void FTimerGetDefConfig(u32 timer_id, FTimerTachoConfig *config_p);

/*设置32位计数模式下，计数器的compare的值，达到此值，如果开启中断，则开启中断*/
FError FTimerSetPeriod32(FTimerTachoCtrl *instance_p, u32 ticks);

/*设置64位计数模式下，计数器的compare的值，达到此值，如果开启中断，则开启中断*/
FError FTimerSetPeriod64(FTimerTachoCtrl *instance_p, u64 ticks);

/*32位模式下，获取计数器当前计数值*/
u32 FTimerGetCurCnt32(FTimerTachoCtrl *instance_p);

/*64位模式下，获取计数器当前计数值*/
u64 FTimerGetCurCnt64(FTimerTachoCtrl *instance_p);

/*设置计数器初始值*/
FError FTimerSetStartVal(FTimerTachoCtrl *instance_p, u32 cnt);

/*完成Timer驱动实例去使能，清零实例数据*/
void FTimerDeInit(FTimerTachoCtrl *instance_p);

/* Tacho API */
/*完成Tacho驱动实例的初始化，使之在就绪状态*/
FError FTachoInit(FTimerTachoCtrl *instance_p, const FTimerTachoConfig *config_p);

/*获取Tacho驱动的默认配置参数*/
void FTachoGetDefConfig(u32 tacho_id, FTimerTachoConfig *config_p);

/*配置tach转速周期= pulse_num*/
void FTachoSetCntPeriod(FTimerTachoCtrl *instance_p, u32 ticks);

/*预设的 tach 最大值*/
void FTachoSetOverLimit(FTimerTachoCtrl *instance_p, u32 overLim);

/*预设的 tach 最小值*/
void FTachoSetUnderLimit(FTimerTachoCtrl *instance_p, u32 underLim);

/*根据预设采样周期的值，来获取风扇的转速值*/
FError FTachoGetFanRPM(FTimerTachoCtrl *instance_p, u32 *rpm);

/*获取capture模式下tacho输入脉冲的个数*/
u32 FTachoGetCaptureCnt(FTimerTachoCtrl *instance_p);

/*完成Tacho驱动实例去使能，清零实例数据*/
void FTachoDeInit(FTimerTachoCtrl *instance_p);

#ifdef __cplusplus
}
#endif

#endif // !