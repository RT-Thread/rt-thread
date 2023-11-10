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
 * FilePath: fgpio.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:29
 * Description:  This files is for GPIO user API implmentation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/3/1     init commit
 * 2.0   zhugengyu  2022/7/1     support e2000
 */


/***************************** Include Files *********************************/
#include "fdrivers_port.h"
#include "fparameters.h"

#include "fgpio_hw.h"
#include "fgpio.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/
#define FGPIO_DEBUG_TAG "FGPIO"
#define FGPIO_ERROR(format, ...) FT_DEBUG_PRINT_E(FGPIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGPIO_WARN(format, ...)  FT_DEBUG_PRINT_W(FGPIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGPIO_INFO(format, ...)  FT_DEBUG_PRINT_I(FGPIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FGPIO_DEBUG(format, ...) FT_DEBUG_PRINT_D(FGPIO_DEBUG_TAG, format, ##__VA_ARGS__)

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/

/*****************************************************************************/
/**
 * @name: FGpioCfgInitialize
 * @msg: 初始化GPIO控制器实例
 * @return {FError} FGPIO_SUCCESS 表示初始化成功
 * @param {FGpio} *instance, GPIO控制器实例
 * @param {FGpioConfig} *config, GPIO控制器配置
 */
FError FGpioCfgInitialize(FGpio *const instance, const FGpioConfig *const config)
{
    FASSERT(instance && config);

    if (0 == config->base_addr)
    {
        FGPIO_ERROR("Invalid base address !!!");
        return FGPIO_ERR_INVALID_PARA;
    }

    if (config != &instance->config)
    {
        instance->config = *config;
    }

    /* mask interrupt for all pins */
    FGpioWriteReg32(instance->config.base_addr, FGPIO_INTMASK_OFFSET, FGPIO_INTR_PORTA_MASKALL);

    instance->is_ready = FT_COMPONENT_IS_READY;
    return FGPIO_SUCCESS;
}

/**
 * @name: FGpioDeInitialize
 * @msg: 去初始化GPIO控制器实例
 * @return {*}
 * @param {FGpio} *instance, GPIO控制器实例
 */
void FGpioDeInitialize(FGpio *const instance)
{
    FASSERT(instance);
    u32 port_id;
    u32 pin_id;
    FGpioPin *pin = NULL;

    for (port_id = FGPIO_PORT_A; port_id < FGPIO_PORT_NUM; port_id++)
    {
        for (pin_id = FGPIO_PIN_0; pin_id < FGPIO_PIN_NUM; pin_id++)
        {
            pin = instance->pins[port_id][pin_id];
            if (NULL != pin)
            {
                FGpioPinDeInitialize(pin);
            }
        }
    }

    instance->is_ready = 0;
    return;
}

/**
 * @name: FGpioPinInitialize
 * @msg: 初始化GPIO引脚实例
 * @return {FError} FGPIO_SUCCESS 表示初始化成功
 * @param {FGpio} *instance, GPIO控制器实例
 * @param {FGpioPin} *pin_instance, GPIO引脚实例
 * @param {FGpioPinId} index, GPIO引脚索引
 */
FError FGpioPinInitialize(FGpio *const instance, FGpioPin *const pin_instance,
                          const FGpioPinId index)
{
    FASSERT(instance && pin_instance);
    FASSERT_MSG(index.port < FGPIO_PORT_NUM, "Invalid gpio port %d", index);
    FASSERT_MSG(index.pin < FGPIO_PIN_NUM, "Invalid gpio pin %d", index);

    if (FT_COMPONENT_IS_READY != instance->is_ready)
    {
        FGPIO_ERROR("gpio instance is not yet inited !!!");
        return FGPIO_ERR_NOT_INIT;
    }

    if (FT_COMPONENT_IS_READY == pin_instance->is_ready)
    {
        FGPIO_ERROR("gpio pin already inited !!!");
        return FGPIO_ERR_ALREADY_INIT;
    }

    pin_instance->index = index;
    instance->pins[index.port][index.pin] = pin_instance;
    pin_instance->instance = instance;
    pin_instance->irq_cb = NULL;
    pin_instance->irq_cb_params = NULL;
    pin_instance->irq_one_time = FALSE;
    pin_instance->is_ready = FT_COMPONENT_IS_READY;

    return FGPIO_SUCCESS;
}

/**
 * @name: FGpioPinDeInitialize
 * @msg: 去初始化GPIO引脚实例
 * @return {NONE}
 * @param {FGpioPin} *pin, GPIO引脚实例
 */
void FGpioPinDeInitialize(FGpioPin *const pin)
{
    FASSERT(pin);
    FGpio *const instance = pin->instance;

    if ((NULL == instance) || (FT_COMPONENT_IS_READY != instance->is_ready) ||
        (FT_COMPONENT_IS_READY != pin->is_ready))
    {
        FGPIO_ERROR("gpio instance is not yet inited !!!");
        return;
    }

    if (FGPIO_DIR_INPUT == FGpioGetDirection(pin))
    {
        FGpioSetInterruptMask(pin, FALSE);    /* 关闭引脚中断 */
    }

    FGpioPinId index = pin->index;
    FASSERT_MSG(instance->pins[index.port][index.pin] == pin, "invalid pin instance");
    instance->pins[index.port][index.pin] = NULL;
    pin->instance = NULL;
    pin->is_ready = 0U;

    return;
}

/**
 * @name: FGpioGetPinIrqSourceType
 * @msg: 获取引脚中断的上报方式
 * @return {FGpioIrqSourceType} 引脚中断的上报方式
 * @param {FGpioPin} *pin, GPIO引脚实例
 */
FGpioIrqSourceType FGpioGetPinIrqSourceType(FGpioPinId pin_id)
{
#if defined(FGPIO_VERSION_1) /* FT2000-4, D2000 */
    if (FGPIO_PORT_B == pin_id.port)
    {
        return FGPIO_IRQ_NOT_SUPPORT;
    }
#endif

    if (FGPIO_PORT_A == pin_id.port)
    {
#if defined(FGPIO_VERSION_2) /* E2000 GPIO 0 ~ 5 */
        if (pin_id.ctrl <= FGPIO_WITH_PIN_IRQ) /* 0 ~ 2 中断单独上报 */
        {
            return FGPIO_IRQ_BY_PIN;
        }
#endif

        return FGPIO_IRQ_BY_CONTROLLER;
    }

    return FGPIO_IRQ_NOT_SUPPORT;
}

/**
 * @name: FGpioReadRegDir
 * @msg: 从寄存器读取GPIO组的输入输出方向
 * @return {u32} GPIO组的输入输出方向, bit[8:0]有效
 * @param {uintptr} base_addr, GPIO控制器基地址
 * @param {FGpioPortIndex} port, GPIO组, A/B
 */
static u32 FGpioReadRegDir(uintptr base_addr, const FGpioPortIndex port)
{
    u32 reg_val = 0;

    if (FGPIO_PORT_A == port)
    {
        reg_val = FGpioReadReg32(base_addr, FGPIO_SWPORTA_DDR_OFFSET);
    }
#if defined(FGPIO_VERSION_1) /* FT2000-4, D2000 */
    else if (FGPIO_PORT_B == port)
    {
        reg_val = FGpioReadReg32(base_addr, FGPIO_SWPORTB_DDR_OFFSET);
    }
#endif
    else
    {
        FASSERT(0);
    }

    return reg_val;
}

/**
 * @name: FGpioWriteRegDir
 * @msg: 向寄存器写入GPIO组的输入输出方向
 * @return {*}
 * @param {uintptr} base_addr, GPIO控制器基地址
 * @param {FGpioPortIndex} port, GPIO组, A/B
 * @param {u32} reg_val, GPIO组的输入输出方向, bit[8:0]有效
 */
static void FGpioWriteRegDir(uintptr base_addr, const FGpioPortIndex port, const u32 reg_val)
{
    if (FGPIO_PORT_A == port)
    {
        FGpioWriteReg32(base_addr, FGPIO_SWPORTA_DDR_OFFSET, reg_val);
    }
#if defined(FGPIO_VERSION_1) /* FT2000-4, D2000 */
    else if (FGPIO_PORT_B == port)
    {
        FGpioWriteReg32(base_addr, FGPIO_SWPORTB_DDR_OFFSET, reg_val);
    }
#endif
    else
    {
        FASSERT(0);
    }

    return;
}

/**
 * @name: FGpioSetDirection
 * @msg: 设置GPIO引脚的输入输出方向
 * @return {*}
 * @param {FGpioPin} *instance, GPIO控制器实例
 * @param {FGpioDirection} dir, 待设置的GPIO的方向
 * @note 初始化 GPIO 实例后使用此函数
 */
void FGpioSetDirection(FGpioPin *const pin, FGpioDirection dir)
{
    FASSERT(pin);
    FGpio *const instance = pin->instance;
    FASSERT(instance);
    FASSERT_MSG(instance->is_ready == FT_COMPONENT_IS_READY, "gpio instance not is yet inited !!!");
    u32 reg_val;
    FGpioPinId index = pin->index;
    uintptr base_addr = instance->config.base_addr;

    reg_val = FGpioReadRegDir(base_addr, index.port);

    if (FGPIO_DIR_INPUT == dir)
    {
        reg_val &= ~BIT(index.pin); /* 0-Input */
    }
    else if (FGPIO_DIR_OUTPUT == dir)
    {
        reg_val |= BIT(index.pin); /* 1-Output */
    }
    else
    {
        FASSERT(0);
    }

    FGpioWriteRegDir(base_addr, index.port, reg_val);
    return;
}

/**
 * @name: FGpioGetDirection
 * @msg: 获取GPIO引脚的输入输出方向
 * @return {FGpioDirection} GPIO引脚方向
 * @param {FGpioPin} *pin, GPIO引脚实例
 * @note 初始化 GPIO 实例后使用此函数
 */
FGpioDirection FGpioGetDirection(FGpioPin *const pin)
{
    FASSERT(pin);
    FGpio *const instance = pin->instance;
    FASSERT(instance);
    FASSERT(instance->is_ready == FT_COMPONENT_IS_READY);

    FGpioPinId index = pin->index;
    uintptr base_addr = instance->config.base_addr;
    u32 reg_val = FGpioReadRegDir(base_addr, index.port);

    return (BIT(index.pin) & reg_val) ? FGPIO_DIR_OUTPUT : FGPIO_DIR_INPUT;
}

/**
 * @name: FGpioReadRegVal
 * @msg: 获取GPIO组的输出寄存器值
 * @return {u32} 输出寄存器值 bit[8:0]有效
 * @param {uintptr} base_addr, GPIO控制器基地址
 * @param {FGpioPortIndex} port, GPIO组
 */
static u32 FGpioReadRegVal(uintptr base_addr, const FGpioPortIndex port)
{
    u32 reg_val = 0;

    if (FGPIO_PORT_A == port)
    {
        reg_val = FGpioReadReg32(base_addr, FGPIO_SWPORTA_DR_OFFSET);
    }
#if defined(FGPIO_VERSION_1) /* FT2000-4, D2000 */
    else if (FGPIO_PORT_B == port)
    {
        reg_val = FGpioReadReg32(base_addr, FGPIO_SWPORTB_DR_OFFSET);
    }
#endif
    else
    {
        FASSERT(0);
    }

    return reg_val;
}

/**
 * @name: FGpioWriteRegVal
 * @msg: 设置GPIO组的输出寄存器值
 * @return {*}
 * @param {uintptr} base_addr, GPIO控制器基地址
 * @param {FGpioPortIndex} port, GPIO组
 * @param {u32} reg_val, 输出寄存器值 bit[8:0]有效
 */
void FGpioWriteRegVal(uintptr base_addr, const FGpioPortIndex port, const u32 reg_val)
{
    if (FGPIO_PORT_A == port)
    {
        FGpioWriteReg32(base_addr, FGPIO_SWPORTA_DR_OFFSET, reg_val);
    }
#if defined(FGPIO_VERSION_1) /* FT2000-4, D2000 */
    else if (FGPIO_PORT_B == port)
    {
        FGpioWriteReg32(base_addr, FGPIO_SWPORTB_DR_OFFSET, reg_val);
    }
#endif
    else
    {
        FASSERT(0);
    }

    return;
}

/**
 * @name: FGpioSetOutputValue
 * @msg: 设置GPIO引脚的输出值
 * @return {FError} FGPIO_SUCCESS 表示设置成功
 * @param {FGpioPin} *pin, GPIO引脚实例
 * @param {FGpioPinVal} output, GPIO引脚的输出值
 * @note 初始化 GPIO 实例后使用此函数，先设置 GPIO 引脚为输出后调用此函数
 */
FError FGpioSetOutputValue(FGpioPin *const pin, const FGpioPinVal output)
{
    FASSERT(pin);
    FGpio *const instance = pin->instance;
    FASSERT(instance);
    FASSERT_MSG(instance->is_ready == FT_COMPONENT_IS_READY, "gpio instance is not yet inited !!!");

    FGpioPinId index = pin->index;
    uintptr base_addr = instance->config.base_addr;
    u32 reg_val;

    if (FGPIO_DIR_OUTPUT != FGpioGetDirection(pin))
    {
        FGPIO_ERROR("Need to set GPIO direction as OUTPUT first !!!");
        return FGPIO_ERR_INVALID_STATE;
    }

    FGPIO_INFO("pin-%d at port %d", index.pin, index.port);
    reg_val = FGpioReadRegVal(base_addr, index.port);
    if (FGPIO_PIN_LOW == output)
    {
        reg_val &= ~BIT(index.pin);
    }
    else if (FGPIO_PIN_HIGH == output)
    {
        reg_val |= BIT(index.pin);
    }
    else
    {
        FASSERT(0);
    }

    FGPIO_INFO("Output val 0x%x", reg_val);
    FGpioWriteRegVal(base_addr, index.port, reg_val);
    FGPIO_INFO("Output val 0x%x", FGpioReadRegVal(base_addr, index.port));
    return FGPIO_SUCCESS;
}

/**
 * @name: FGpioGetInputValue
 * @msg: 获取GPIO引脚的输入值
 * @return {FGpioPinVal} 获取的输入值，高电平/低电平
 * @param {FGpioPin} *instance, GPIO引脚实例
 * @note 初始化 GPIO 实例后使用此函数，先设置 GPIO 引脚为输入后调用此函数
 */
FGpioPinVal FGpioGetInputValue(FGpioPin *const pin)
{
    FASSERT(pin);
    FGpio *const instance = pin->instance;
    FASSERT(instance);
    FASSERT(instance->is_ready == FT_COMPONENT_IS_READY);
    FGpioPinId index = pin->index;
    uintptr base_addr = instance->config.base_addr;
    u32 reg_val;

    if (FGPIO_DIR_INPUT != FGpioGetDirection(pin))
    {
        FGPIO_ERROR("Need to set GPIO direction as INPUT first !!!");
        return FGPIO_PIN_LOW;
    }

    if (FGPIO_PORT_A == index.port)
    {
        reg_val = FGpioReadReg32(base_addr, FGPIO_EXT_PORTA_OFFSET);
    }
#if defined(FGPIO_VERSION_1) /* FT2000-4, D2000 */
    else if (FGPIO_PORT_B == index.port)
    {
        reg_val = FGpioReadReg32(base_addr, FGPIO_EXT_PORTB_OFFSET);
    }
#endif
    else
    {
        FASSERT(0);
    }

    FGPIO_INFO("Input val: 0x%x.", reg_val);
    return (BIT(index.pin) & reg_val) ? FGPIO_PIN_HIGH : FGPIO_PIN_LOW;
}