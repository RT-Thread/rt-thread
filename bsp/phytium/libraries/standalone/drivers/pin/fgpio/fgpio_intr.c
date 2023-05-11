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
 * FilePath: fgpio_intr.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:29
 * Description:  This files is for GPIO interrupt function implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/3/1     init commit
 * 2.0   zhugengyu  2022/7/1     support e2000
 */


/***************************** Include Files *********************************/
#include "fdebug.h"
#include "fparameters.h"

#include "fgpio_hw.h"
#include "fgpio.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FGPIO_DEBUG_TAG "FGPIO-INTR"
#define FGPIO_ERROR(format, ...) FT_DEBUG_PRINT_E(FGPIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGPIO_WARN(format, ...)  FT_DEBUG_PRINT_W(FGPIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGPIO_INFO(format, ...)  FT_DEBUG_PRINT_I(FGPIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGPIO_DEBUG(format, ...) FT_DEBUG_PRINT_D(FGPIO_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
 * @name: FGpioGetInterruptMask
 * @msg: 获取GPIO A组引脚的中断屏蔽位
 * @return {*}
 * @param {FGpio} *instance, GPIO控制器实例
 * @param {u32} *mask, 返回的GPIO A组引脚中断屏蔽位
 * @param {u32} *enabled, 返回的GPIO A组中断使能位
 * @note 获取的是A组所有Pin的中断屏蔽位和中断使能位
 */
void FGpioGetInterruptMask(FGpio *const instance, u32 *mask, u32 *enabled)
{
    FASSERT(instance);
    FASSERT(instance->is_ready == FT_COMPONENT_IS_READY);
    uintptr base_addr = instance->config.base_addr;

    if (NULL != mask)
    {
        *mask = FGpioReadReg32(base_addr, FGPIO_INTMASK_OFFSET);
    }

    if (NULL != enabled)
    {
        *enabled = FGpioReadReg32(base_addr, FGPIO_INTEN_OFFSET);
    }

    return;
}

/**
 * @name: FGpioSetInterruptMask
 * @msg: 设置GPIO A组引脚的中断屏蔽位
 * @return {*}
 * @param {FGpioPin} *pin, GPIO引脚实例
 * @param {boolean} enable, TRUE表示使能GPIO引脚中断，FALSE表示去使能GPIO引脚中断
 * @note index对应的引脚必须为A组引脚，B组引脚不支持中断
 */
void FGpioSetInterruptMask(FGpioPin *const pin, boolean enable)
{
    FASSERT(pin);
    FGpio *const instance = pin->instance;
    FASSERT(instance);
    FASSERT(instance->is_ready == FT_COMPONENT_IS_READY);
    uintptr base_addr = instance->config.base_addr;
    u32 mask_bits = 0;
    u32 enable_bits = 0;
    FGpioPinId index = pin->index;

#if defined(FGPIO_VERSION_1) /* FT2000-4, D2000 */
    if (FGPIO_PORT_B == index.port)
    {
        FGPIO_ERROR("None interrupt support for PORT-B !!!");
        return;
    }
#endif

    if (FGPIO_DIR_OUTPUT == FGpioGetDirection(pin))
    {
        FGPIO_ERROR("None interrupt support for output GPIO !!!");
        return;
    }

    FGpioGetInterruptMask(instance, &mask_bits, &enable_bits);
    if (TRUE == enable)
    {
        mask_bits &= ~BIT(index.pin); /* not mask: 0 */
        enable_bits |= BIT(index.pin); /* enable pin irq: 1 */
    }
    else
    {
        mask_bits |= BIT(index.pin); /* mask: 1  */
        enable_bits &= ~BIT(index.pin); /* disable pin irq: 0 */
    }

    FGpioWriteReg32(base_addr, FGPIO_INTMASK_OFFSET, mask_bits);
    FGpioWriteReg32(base_addr, FGPIO_INTEN_OFFSET, enable_bits);

    return;
}

/**
 * @name: FGpioGetInterruptType
 * @msg: 获取GPIO A组引脚的中断类型和中断极性
 * @return {*}
 * @param {FGpio} *instance, GPIO控制器实例
 * @param {u32} *levels, GPIO A组引脚中断电平类型
 * @param {u32} *polarity, GPIO A组引脚中断极性类型
 * @note 获取的是A组所有Pin的电平和极性
 */
void FGpioGetInterruptType(FGpio *const instance, u32 *levels, u32 *polarity)
{
    FASSERT(instance);
    FASSERT(instance->is_ready == FT_COMPONENT_IS_READY);
    uintptr base_addr = instance->config.base_addr;

    if (NULL != levels)
    {
        *levels = FGpioReadReg32(base_addr, FGPIO_INTTYPE_LEVEL_OFFSET);
    }

    if (NULL != polarity)
    {
        *polarity = FGpioReadReg32(base_addr, FGPIO_INTTYPE_LEVEL_OFFSET);
    }

    return;
}

/**
 * @name: FGpioSetInterruptType
 * @msg: 设置GPIO引脚的中断类型
 * @return {*}
 * @param {FGpioPin} *pin, GPIO引脚实例
 * @param {FGpioIrqType} type, GPIO引脚中断触发类型
 * @note index对应的引脚必须为A组引脚，B组引脚不支持中断
 */
void FGpioSetInterruptType(FGpioPin *const pin, const FGpioIrqType type)
{
    FASSERT(pin);
    FGpio *const instance = pin->instance;
    FASSERT(instance);
    FASSERT(instance->is_ready == FT_COMPONENT_IS_READY);
    uintptr base_addr = instance->config.base_addr;
    u32 level = 0;
    u32 polarity = 0;
    FGpioPinId index = pin->index;

#if defined(FGPIO_VERSION_1) /* FT2000-4, D2000 */
    if (FGPIO_PORT_B == index.port)
    {
        FGPIO_ERROR("None interrupt support for PORT-B !!!");
        return;
    }
#endif

    FGpioGetInterruptType(instance, &level, &polarity);

    switch (type)
    {
        case FGPIO_IRQ_TYPE_EDGE_FALLING:
            level |= BIT(index.pin); /* 边沿敏感型 */
            polarity &= ~BIT(index.pin); /* 下降沿或低电平 */
            break;
        case FGPIO_IRQ_TYPE_EDGE_RISING:
            level |= BIT(index.pin); /* 边沿敏感型 */
            polarity |= BIT(index.pin); /* 上升沿或高电平 */
            break;
        case FGPIO_IRQ_TYPE_LEVEL_LOW:
            level &= ~BIT(index.pin); /* 电平敏感型 */
            polarity &= ~BIT(index.pin); /* 下降沿或低电平 */
            break;
        case FGPIO_IRQ_TYPE_LEVEL_HIGH:
            level &= ~BIT(index.pin); /* 电平敏感型 */
            polarity |= BIT(index.pin); /* 上升沿或高电平 */
            break;
        default:
            break;
    }

    FGpioWriteReg32(base_addr, FGPIO_INTTYPE_LEVEL_OFFSET, level);
    FGpioWriteReg32(base_addr, FGPIO_INT_POLARITY_OFFSET, polarity);

    return;
}

/**
 * @name: FGpioInterruptHandler
 * @msg: GPIO中断处理函数
 * @return {*}
 * @param {s32} vector, 中断输入参数1
 * @param {void} *param, 中断输入参数2
 * @note 需要用户将此函数注册到Interrtup上，使能GPIO中断才能生效
 */
void FGpioInterruptHandler(s32 vector, void *param)
{
    FGpio *const instance = (FGpio * const)param;
    FGpioPin *pin = NULL;
    FASSERT(instance);
    int loop;
    uintptr base_addr = instance->config.base_addr;
    u32 status = FGpioReadReg32(base_addr, FGPIO_INTSTATUS_OFFSET);
    u32 raw_status = FGpioReadReg32(base_addr, FGPIO_RAW_INTSTATUS_OFFSET);

#if defined(FGPIO_VERSION_2) /* E2000 gpio 3 ~ 5 */
    FASSERT_MSG(FGPIO_WITH_PIN_IRQ < instance->config.instance_id, "Handle interrupt through pin !!!")
#endif

    FGPIO_INFO("status: 0x%x, raw_status: 0x%x.", status, raw_status);
    for (loop = FGPIO_PIN_0; loop < FGPIO_PIN_NUM; loop++)
    {
        if (status & BIT(loop))
        {
            pin = instance->pins[FGPIO_PORT_A][loop];
            if (NULL == pin)
            {
                continue;
            }

            if (pin->irq_cb)
            {
                pin->irq_cb(0U, pin->irq_cb_params);

                /* disable pin interrupt after triggered */
                if (TRUE == pin->irq_one_time)
                {
                    FGpioSetInterruptMask(pin, FALSE);
                }
            }
            else
            {
                FGPIO_WARN("No irq handler callback for GPIO-%d-A-%d.",
                           instance->config.instance_id,
                           loop);
            }
        }
    }

    /* clear interrupt status */
    FGpioWriteReg32(base_addr, FGPIO_PORTA_EOI_OFFSET, status);
    return;
}

#if defined(FGPIO_VERSION_2) /* E2000 GPIO 0 ~ 2 */
/**
 * @name: FGpioPinInterruptHandler
 * @msg: GPIO引脚中断处理函数
 * @return {NONE}
 * @param {s32} vector, 中断输入参数1
 * @param {void} *param, 中断输入参数2
 */
void FGpioPinInterruptHandler(s32 vector, void *param)
{
    FGpioPin *const pin = (FGpioPin * const)param;
    FASSERT(pin);
    FGpio *const instance = pin->instance;
    FASSERT(instance);
    uintptr base_addr = instance->config.base_addr;

    u32 status = FGpioReadReg32(base_addr, FGPIO_INTSTATUS_OFFSET);
    u32 raw_status = FGpioReadReg32(base_addr, FGPIO_RAW_INTSTATUS_OFFSET);

    FGPIO_INFO("status: 0x%x, raw_status: 0x%x.", status, raw_status);
    if (pin->irq_cb)
    {
        pin->irq_cb(0U, pin->irq_cb_params);

        /* disable pin interrupt after triggered */
        if (TRUE == pin->irq_one_time)
        {
            FGpioSetInterruptMask(pin, FALSE);
        }
    }
    else
    {
        FGPIO_WARN("No irq handler callback for GPIO-%d-A-%d.",
                   pin->index.ctrl,
                   pin->index.pin);
    }


    /* clear interrupt status */
    FGpioWriteReg32(base_addr, FGPIO_PORTA_EOI_OFFSET, status);
    return;
}
#endif

/**
 * @name: FGpioRegisterInterruptCB
 * @msg: 注册GPIO引脚中断回调函数
 * @return {*}
 * @param {FGpioPin} pin, GPIO引脚实例
 * @param {FGpioInterruptCallback} cb, GPIO引脚中断回调函数
 * @param {void} *cb_param, GPIO引脚中断回调函数输入参数
 * @param {boolean} irq_one_time, TRUE表示引脚中断触发一次后自动关闭中断，用于电平敏感中断
 * @note 注册的回调函数在FGpioInterruptHandler中被调用
 */
void FGpioRegisterInterruptCB(FGpioPin *const pin, FGpioInterruptCallback cb, void *cb_param, boolean irq_one_time)
{
    FASSERT(pin);
    pin->irq_cb = cb;
    pin->irq_cb_params = cb_param;
    pin->irq_one_time = irq_one_time;
    return;
}