/*
 * File      : board_halley2_readboard_v2.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-01-01     Urey      first version
 */
#ifndef DRIVER_BOARD_HALLEY2_REALBOARD_V2_BOARD_HALLEY2_READBOARD_V2_H_
#define DRIVER_BOARD_HALLEY2_REALBOARD_V2_BOARD_HALLEY2_READBOARD_V2_H_

#ifdef __cplusplus
extern "C" {
#endif

#define AUDIO_SHUTDOWN_PORT     GPIO_PORT_C
#define AUDIO_SHUTDOWN_PIN      GPIO_Pin_26
#define AUDIO_SHUTDOWN_MUTE     0

#define LCD_RST_PORT            GPIO_PORT_C
#define LCD_RST_PIN             GPIO_Pin_23

#define LCD_BL_PORT             GPIO_PORT_D
#define LCD_BL_PIN              GPIO_Pin_1

#define LCD_TP_INT_PORT         GPIO_PORT_C
#define LCD_TP_INT_PIN          GPIO_Pin_25

/* BLINK LED */
#define BLINK_LED0_PORT         GPIO_PORT_B
#define BLINK_LED0_PIN          GPIO_Pin_9

#define BLINK_LED1_PORT         GPIO_PORT_B
#define BLINK_LED1_PIN          GPIO_Pin_8

#define BLINK_LED2_PORT         GPIO_PORT_B
#define BLINK_LED2_PIN          GPIO_Pin_13

#define BLINK_LED3_PORT         GPIO_PORT_B
#define BLINK_LED3_PIN          GPIO_Pin_11

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_BOARD_HALLEY2_REALBOARD_V2_BOARD_HALLEY2_READBOARD_V2_H_ */
