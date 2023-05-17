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
 * FilePath: fgpio_sinit.c
 * Date: 2022-02-10 14:53:42
 * LastEditTime: 2022-02-18 08:25:29
 * Description:  This files is for GPIO static variables implementation
 *
 * Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   zhugengyu  2022/3/1     init commit
 * 2.0   zhugengyu  2022/7/1     support e2000
 */


/***************************** Include Files *********************************/
#include "fparameters.h"

#include "fgpio_hw.h"
#include "fgpio.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

/************************** Variable Definitions *****************************/
#if defined(FGPIO_VERSION_1)|| defined(TARDIGRADE) /* FT2000-4, D2000 */
extern const FGpioConfig fgpio_cfg_tbl[FGPIO_NUM];
#elif defined(FGPIO_VERSION_2) /* E2000 GPIO 0 ~ 5 */
extern FGpioConfig fgpio_cfg_tbl[FGPIO_NUM];
#endif

/*****************************************************************************/

#if defined(FGPIO_VERSION_1) || defined(TARDIGRADE) /* FT2000-4, D2000 */
/**
 * @name: FGpioLookupConfig
 * @msg: 获取GPIO控制器的默认配置
 * @return {const FGpioConfig *} GPIO控制器的默认配置
 * @param {u32} instance_id, GPIO控制器实例号
 */
const FGpioConfig *FGpioLookupConfig(u32 instance_id)
{
    const FGpioConfig *ptr = NULL;
    u32 index;

    for (index = 0; index < FGPIO_NUM; index++)
    {
        if (fgpio_cfg_tbl[index].instance_id == instance_id)
        {
            ptr = &fgpio_cfg_tbl[index];
            break;
        }
    }

    return ptr;
}
#elif defined(FGPIO_VERSION_2) /* E2000 GPIO 0 ~ 5 */
/**
 * @name: FGpioSetIrqNum
 * @msg: 设置GPIO控制器各引脚的中断号
 * @return {NONE}
 * @param {u32} instance_id, GPIO控制器实例号
 * @param {FGpioConfig} *ptr, GPIO控制器的默认配置
 */
static void FGpioSetIrqNum(u32 instance_id, FGpioConfig *ptr)
{
    u32 pin_id;
    u32 irq_num;

    if (FGPIO_WITH_PIN_IRQ >= instance_id) /* GPIO 0 ~ 2 */
    {
        /* each pin has its own interrupt id */
        for (pin_id = FGPIO_PIN_0; pin_id < FGPIO_PIN_NUM; pin_id++)
        {
            ptr->irq_num[pin_id] = FGPIO_PIN_IRQ_NUM_GET(instance_id, pin_id);
        }
    }
    else
    {
        if (FGPIO3_ID == instance_id)
        {
            irq_num = FGPIO_3_IRQ_NUM;
        }
        else if (FGPIO4_ID == instance_id)
        {
            irq_num = FGPIO_4_IRQ_NUM;
        }
        else if (FGPIO5_ID == instance_id)
        {
            irq_num = FGPIO_5_IRQ_NUM;
        }

        /* all pins in the controller share the same interrupt id */
        for (pin_id = FGPIO_PIN_0; pin_id < FGPIO_PIN_NUM; pin_id++)
        {
            ptr->irq_num[pin_id] = irq_num;
        }
    }

    return;
}

/**
 * @name: FGpioLookupConfig
 * @msg: 获取GPIO控制器的默认配置
 * @return {const FGpioConfig *} GPIO控制器的默认配置
 * @param {u32} instance_id, GPIO控制器实例号
 */
const FGpioConfig *FGpioLookupConfig(u32 instance_id)
{
    const FGpioConfig *ptr = NULL;
    u32 index;
    static boolean irq_num_set = FALSE;

    if (FALSE == irq_num_set) /* set irq num in the first time */
    {
        for (index = 0; index < FGPIO_NUM; index++)
        {
            FGpioSetIrqNum(index, &fgpio_cfg_tbl[index]);
        }
        irq_num_set = TRUE;
    }

    for (index = 0; index < FGPIO_NUM; index++) /* find configs of controller */
    {
        if (fgpio_cfg_tbl[index].instance_id == instance_id)
        {
            ptr = &fgpio_cfg_tbl[index];
            break;
        }
    }

    return ptr;
}

#endif