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
 * FilePath: fgpio.h
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:35
 * Description:  This files is for GPIO user API definition
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/3/1     init commit
 * 2.0   zhugengyu  2022/7/1     support e2000
 */


#ifndef  FGPIO_H
#define  FGPIO_H

#include "fparameters.h"
#include "ftypes.h"
#include "fassert.h"
#include "ferror_code.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

/************************** Constant Definitions *****************************/
#define FGPIO_SUCCESS            FT_SUCCESS
#define FGPIO_ERR_INVALID_PARA   FT_MAKE_ERRCODE(ErrModBsp, ErrBspGpio, 0x0)
#define FGPIO_ERR_INVALID_STATE  FT_MAKE_ERRCODE(ErrModBsp, ErrBspGpio, 0x1)
#define FGPIO_ERR_NOT_INIT       FT_MAKE_ERRCODE(ErrModBsp, ErrBspGpio, 0x2)
#define FGPIO_ERR_ALREADY_INIT   FT_MAKE_ERRCODE(ErrModBsp, ErrBspGpio, 0x3)

#if defined(CONFIG_TARGET_F2000_4) || defined(CONFIG_TARGET_D2000)
#define FGPIO_VERSION_1 /* 用于FT2000/4和D2000平台的GPIO 0 ~ 1 */
#elif defined(CONFIG_TARGET_E2000)
#define FGPIO_VERSION_2 /* 用于E2000平台的GPIO 3 ~ 5 */
#elif defined(TARDIGRADE)

#else
#error "Invalid target board !!!"
#endif

typedef enum
{
    FGPIO_PORT_A = 0,
#if defined(FGPIO_VERSION_1) /* FT2000-4, D2000 */
    FGPIO_PORT_B,
#endif

    FGPIO_PORT_NUM
} FGpioPortIndex; /* GPIO引脚所在的组 */

typedef enum
{
    FGPIO_PIN_0 = 0,
    FGPIO_PIN_1,
    FGPIO_PIN_2,
    FGPIO_PIN_3,
    FGPIO_PIN_4,
    FGPIO_PIN_5,
    FGPIO_PIN_6,
    FGPIO_PIN_7,
#if defined(FGPIO_VERSION_2) || defined(TARDIGRADE)/* E2000 GPIO 0 ~ 5 */
    FGPIO_PIN_8,
    FGPIO_PIN_9,
    FGPIO_PIN_10,
    FGPIO_PIN_11,
    FGPIO_PIN_12,
    FGPIO_PIN_13,
    FGPIO_PIN_14,
    FGPIO_PIN_15,
#endif

    FGPIO_PIN_NUM
} FGpioPinIndex; /* GPIO引脚号 */

#if defined(FGPIO_VERSION_1) /* FT2000-4, D2000 */
FASSERT_STATIC(8 == FGPIO_PIN_NUM); /* pin 0 ~ 7 */
FASSERT_STATIC(2 == FGPIO_PORT_NUM); /* port a/b */
#elif defined(FGPIO_VERSION_2) /* E2000 GPIO 0 ~ 5 */
FASSERT_STATIC(16 == FGPIO_PIN_NUM); /* pin 0 ~ 15 */
FASSERT_STATIC(1 == FGPIO_PORT_NUM); /* port a */
#endif
typedef enum
{
    FGPIO_DIR_INPUT = 0, /* 输入 */
    FGPIO_DIR_OUTPUT /* 输出 */
} FGpioDirection; /* GPIO引脚的输入输出方向 */

typedef enum
{
    FGPIO_IRQ_TYPE_EDGE_FALLING = 0, /* 下降沿中断，引脚检测到电平从高变低时触发 */
    FGPIO_IRQ_TYPE_EDGE_RISING, /* 上升沿中断，引脚检测到电平从低变高时触发 */
    FGPIO_IRQ_TYPE_LEVEL_LOW, /* 低电平中断，引脚电平为低时触发 */
    FGPIO_IRQ_TYPE_LEVEL_HIGH /* 高电平中断，引脚电平为高时触发 */
} FGpioIrqType; /* GPIO引脚中断类型 */

typedef enum
{
    FGPIO_IRQ_NOT_SUPPORT, /* 不支持引脚中断 */
    FGPIO_IRQ_BY_CONTROLLER, /* 引脚中断控制器合并上报 */
#if defined(FGPIO_VERSION_2) /* E2000 GPIO 0 ~ 5 */
    FGPIO_IRQ_BY_PIN, /* 引脚中断单独上报 */
#endif
} FGpioIrqSourceType;

typedef enum
{
    FGPIO_PIN_LOW = 0, /* 低电平 */
    FGPIO_PIN_HIGH /* 高电平 */
} FGpioPinVal; /* GPIO引脚电平类型 */

/**************************** Type Definitions *******************************/
typedef struct _FGpioPin FGpioPin;
typedef struct _FGpio FGpio;

typedef struct
{
    u32 instance_id; /* GPIO实例ID */
    uintptr base_addr; /* GPIO控制器基地址 */
#if defined(FGPIO_VERSION_1) || defined(TARDIGRADE)  /* FT2000-4, D2000 */
    u32 irq_num; /* GPIO控制器中断号 */
#elif defined(FGPIO_VERSION_2) /* E2000 GPIO 0 ~ 5 */
    u32 irq_num[FGPIO_PIN_NUM]; /* GPIO各引脚的中断号，如果是控制器中断，则数组所有值一致 */
#endif
    u32 irq_priority; /* 中断优先级 */
} FGpioConfig; /* GPIO控制器配置 */

typedef struct
{
    u32 ctrl; /* GPIO控制器号 */
    FGpioPortIndex port; /* GPIO引脚所在的组 */
    FGpioPinIndex  pin; /* GPIO引脚号 */
} FGpioPinId; /* GPIO引脚索引 */

typedef void (*FGpioInterruptCallback)(s32 vector, void *param); /* GPIO引脚中断回调函数类型 */

typedef struct _FGpioPin
{
    FGpioPinId index; /* 索引 */
    u32 is_ready;
    FGpio *instance;
    FGpioInterruptCallback irq_cb; /* 中断回调函数, Port-A有效 */
    void *irq_cb_params; /* 中断回调函数的入参, Port-A有效 */
    boolean irq_one_time; /* Port-A有效, TRUE: 进入中断后关闭该引脚的中断，用于电平敏感中断，防止一直进入中断 */
} FGpioPin; /* GPIO引脚实例 */

typedef struct _FGpio
{
    FGpioConfig config;
    u32 is_ready;
    FGpioPin *pins[FGPIO_PORT_NUM][FGPIO_PIN_NUM];
} FGpio; /* GPIO控制器实例 */

/************************** Variable Definitions *****************************/

/***************** Macros (Inline Functions) Definitions *********************/
/* 生成GPIO引脚索引 */
#define FGPIO_PIN(port, pin)   \
    (FGpioPinId) { \
        (port), (pin) \
    }

/************************** Function Prototypes ******************************/
/* 获取GPIO控制器的默认配置 */
const FGpioConfig *FGpioLookupConfig(u32 instance_id);

/* 初始化GPIO控制器实例 */
FError FGpioCfgInitialize(FGpio *const instance, const FGpioConfig *const config);

/* 初始化GPIO引脚实例 */
FError FGpioPinInitialize(FGpio *const instance, FGpioPin *const pin,
                          const FGpioPinId pin_id);

/* 去初始化GPIO引脚实例 */
void FGpioPinDeInitialize(FGpioPin *const pin);

/* 获取引脚中断的上报方式 */
FGpioIrqSourceType FGpioGetPinIrqSourceType(FGpioPinId pin_id);

/* 去初始化GPIO控制器实例 */
void FGpioDeInitialize(FGpio *const instance);

/* 设置GPIO引脚的输入输出方向 */
void FGpioSetDirection(FGpioPin *const pin, FGpioDirection dir);

/* 获取GPIO引脚的输入输出方向 */
FGpioDirection FGpioGetDirection(FGpioPin *const pin);

/* 设置GPIO引脚的输出值 */
FError FGpioSetOutputValue(FGpioPin *const pin, const FGpioPinVal output);

/* 获取GPIO引脚的输入值 */
FGpioPinVal FGpioGetInputValue(FGpioPin *const pin);

/* 获取GPIO A组引脚的中断屏蔽位 */
void FGpioGetInterruptMask(FGpio *const instance, u32 *mask, u32 *enabled);

/* 设置GPIO A组引脚的中断屏蔽位 */
void FGpioSetInterruptMask(FGpioPin *const pin, boolean enable);

/* 获取GPIO A组引脚的中断类型和中断极性 */
void FGpioGetInterruptType(FGpio *const instance, u32 *levels, u32 *polarity);

/* 设置GPIO A组引脚的中断类型 */
void FGpioSetInterruptType(FGpioPin *const pin, const FGpioIrqType type);

/* GPIO控制器中断处理函数 */
void FGpioInterruptHandler(s32 vector, void *param);

#if defined(FGPIO_VERSION_2) /* E2000 GPIO 0 ~ 2 */
/* GPIO引脚中断处理函数 */
void FGpioPinInterruptHandler(s32 vector, void *param);
#endif

/* 注册GPIO A组引脚中断回调函数 */
void FGpioRegisterInterruptCB(FGpioPin *const pin, FGpioInterruptCallback cb,
                              void *cb_param, boolean irq_one_time);

/* 打印GPIO控制寄存器信息 */
void FGpioDumpRegisters(uintptr base_addr);

#ifdef __cplusplus
}
#endif

#endif
