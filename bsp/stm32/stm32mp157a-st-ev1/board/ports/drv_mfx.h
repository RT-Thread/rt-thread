/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-08     thread-liu   first version
 */

#ifndef __DRV_MFX_H__
#define __DRV_MFX_H__

#include "board.h"
#include "mfxstm32l152.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
  BSP_IO_PIN_RESET = 0,
  BSP_IO_PIN_SET   = 1
}BSP_IO_PinStateTypeDef;

#define CAMERA_RST1   MFXSTM32L152_AGPIO_PIN_3
#define CAMERA_XSDN   MFXSTM32L152_AGPIO_PIN_2
#define CARMERA_PLUG  MFXSTM32L152_GPIO_PIN_12

void rt_mfx_init(void);
rt_uint32_t BSP_IO_ITGetStatus(rt_uint32_t IoPin);
void BSP_IO_ITClear(void);
void BSP_IO_ITClearPin(rt_uint32_t IO_Pins_To_Clear);
rt_uint8_t rt_mfx_pin_mode(rt_uint32_t IoPin, IO_ModeTypedef IoMode);
rt_uint8_t rt_mfx_config_irq(rt_uint8_t IoIrqOutPinPolarity, rt_uint8_t IoIrqOutPinType);
void rt_mfx_pin_write(rt_uint32_t IoPin, rt_base_t PinState);
rt_uint32_t rt_mfx_pin_read(rt_uint32_t IoPin);
void rt_mfx_pin_toggle(rt_uint32_t IoPin);

#ifdef __cplusplus
}
#endif

#endif
