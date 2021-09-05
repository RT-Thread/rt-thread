/*
 * @ : Copyright (c) 2021 Phytium Information Technology, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0.
 *
 * @Date: 2021-04-27 17:55:12
 * @LastEditTime: 2021-04-30 14:38:45
 * @Description:  This files is for
 *
 * @Modify History:
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 */

#ifndef FT_BSP_GPIO_H
#define FT_BSP_GPIO_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ft_types.h"
#include "ft_gpio_hw.h"

/* gpio mode: gpio/int */
#define GPIO_MODE_GPIO 0
#define GPIO_MODE_INT 1

/* define debug utilities */
#define FT_GPIO_DEBUG_TAG "FT_GPIO"
#define FT_GPIO_ENABLE_DEBUG
#define FT_GPIO_ERROR(format, ...) FT_DEBUG_PRINT_E(FT_GPIO_DEBUG_TAG, format, ##__VA_ARGS__)
#ifdef FT_GPIO_ENABLE_DEBUG
#define FT_GPIO_DEBUG_I(format, ...) FT_DEBUG_PRINT_I(FT_GPIO_DEBUG_TAG, format, ##__VA_ARGS__)
#define FT_GPIO_DEBUG_W(format, ...) FT_DEBUG_PRINT_W(FT_GPIO_DEBUG_TAG, format, ##__VA_ARGS__)
#else
#define FT_GPIO_DEBUG_I(format, ...)
#define FT_GPIO_DEBUG_W(format, ...)
#endif

   /**
 * @name: FGpio_SetGroupModeA
 * @msg: set gpio mode, polling or intr
 * @return {*}
 * @param {FT_IN u32} ctrlId
 * @param {FT_IN u8} pin
 * @param {FT_IN u32} mode
 */
   void FGpio_SetGroupModeA(FT_IN u32 CtrlId, FT_IN u8 Pin, FT_IN u32 Mode);
   /**
 * @name: FGpio_ReadPinA
 * @msg: get gpio pin status
 * @return {*}
 * @param {FT_IN u32} ctrlId
 * @param {FT_IN u8} pin
 */
   u32 FGpio_ReadPinA(FT_IN u32 CtrlId, FT_IN u8 Pin);
   /**
 * @name: FGpio_WritePinA
 * @msg: set gpio pin status
 * @return {*}
 * @param {FT_IN u32} ctrlId
 * @param {FT_IN u8} pin
 * @param {FT_IN u8} onOff
 */
   void FGpio_WritePinA(FT_IN u32 CtrlId, FT_IN u8 Pin, FT_IN u8 OnOff);

#ifdef __cplusplus
}
#endif

#endif
