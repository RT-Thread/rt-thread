/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      zylx         first version
 */

#ifndef __EXT_IO_H__
#define __EXT_IO_H__

#include "rtthread.h"
/*
    armfly STM32-V6 Development board Extend IO
    D0  - GPRS_RERM_ON
    D1  - GPRS_RESET
    D2  - NRF24L01_CE
    D3  - NRF905_TX_EN
    D4  - NRF905_TRX_CE/VS1053_XDCS
    D5  - NRF905_PWR_UP
    D6  - ESP8266_G0
    D7  - ESP8266_G2

    D8  - LED1
    D9  - LED2
    D10 - LED3
    D11 - LED4
    D12 - TP_NRST
    D13 - AD7606_OS0
    D14 - AD7606_OS1
    D15 - AD7606_OS2

    GPIO can output 5V
    D16  - Y50_0
    D17  - Y50_1
    D18  - Y50_2
    D19  - Y50_3
    D20  - Y50_4
    D21  - Y50_5
    D22  - Y50_6
    D23  - Y50_7

    GPIO can output 3.3V
    D24  - AD7606_RESET
    D25  - AD7606_RAGE
    D26  - Y33_2
    D27  - Y33_3
    D28  - Y33_4
    D29  - Y33_5
    D30  - Y33_6
    D31  - Y33_7
*/

#ifndef GPIO_Pin_0
    #define GPIO_Pin_0                 ((uint16_t)0x0001)  /* Pin 0 selected */
    #define GPIO_Pin_1                 ((uint16_t)0x0002)  /* Pin 1 selected */
    #define GPIO_Pin_2                 ((uint16_t)0x0004)  /* Pin 2 selected */
    #define GPIO_Pin_3                 ((uint16_t)0x0008)  /* Pin 3 selected */
    #define GPIO_Pin_4                 ((uint16_t)0x0010)  /* Pin 4 selected */
    #define GPIO_Pin_5                 ((uint16_t)0x0020)  /* Pin 5 selected */
    #define GPIO_Pin_6                 ((uint16_t)0x0040)  /* Pin 6 selected */
    #define GPIO_Pin_7                 ((uint16_t)0x0080)  /* Pin 7 selected */
    #define GPIO_Pin_8                 ((uint16_t)0x0100)  /* Pin 8 selected */
    #define GPIO_Pin_9                 ((uint16_t)0x0200)  /* Pin 9 selected */
    #define GPIO_Pin_10                ((uint16_t)0x0400)  /* Pin 10 selected */
    #define GPIO_Pin_11                ((uint16_t)0x0800)  /* Pin 11 selected */
    #define GPIO_Pin_12                ((uint16_t)0x1000)  /* Pin 12 selected */
    #define GPIO_Pin_13                ((uint16_t)0x2000)  /* Pin 13 selected */
    #define GPIO_Pin_14                ((uint16_t)0x4000)  /* Pin 14 selected */
    #define GPIO_Pin_15                ((uint16_t)0x8000)  /* Pin 15 selected */
#endif

#define GPIO_Pin_16                 ((uint32_t)0x00010000)  /* Pin 0 selected */
#define GPIO_Pin_17                 ((uint32_t)0x00020000)  /* Pin 1 selected */
#define GPIO_Pin_18                 ((uint32_t)0x00040000)  /* Pin 2 selected */
#define GPIO_Pin_19                 ((uint32_t)0x00080000)  /* Pin 3 selected */
#define GPIO_Pin_20                 ((uint32_t)0x00100000)  /* Pin 4 selected */
#define GPIO_Pin_21                 ((uint32_t)0x00200000)  /* Pin 5 selected */
#define GPIO_Pin_22                 ((uint32_t)0x00400000)  /* Pin 6 selected */
#define GPIO_Pin_23                 ((uint32_t)0x00800000)  /* Pin 7 selected */
#define GPIO_Pin_24                 ((uint32_t)0x01000000)  /* Pin 8 selected */
#define GPIO_Pin_25                 ((uint32_t)0x02000000)  /* Pin 9 selected */
#define GPIO_Pin_26                 ((uint32_t)0x04000000)  /* Pin 10 selected */
#define GPIO_Pin_27                 ((uint32_t)0x08000000)  /* Pin 11 selected */
#define GPIO_Pin_28                 ((uint32_t)0x10000000)  /* Pin 12 selected */
#define GPIO_Pin_29                 ((uint32_t)0x20000000)  /* Pin 13 selected */
#define GPIO_Pin_30                 ((uint32_t)0x40000000)  /* Pin 14 selected */
#define GPIO_Pin_31                 ((uint32_t)0x80000000)  /* Pin 15 selected */

/* Rename the macro for the sake of memory */
#define GPRS_TERM_ON   GPIO_Pin_0
#define GPRS_RESET     GPIO_Pin_1
#define NRF24L01_CE    GPIO_Pin_2
#define NRF905_TX_EN   GPIO_Pin_3
#define NRF905_TRX_CE  GPIO_Pin_4
  #define VS1053_XDCS    GPIO_Pin_4
#define NRF905_PWR_UP  GPIO_Pin_5
#define ESP8266_G0     GPIO_Pin_6
#define ESP8266_G2     GPIO_Pin_7

#define LED1           GPIO_Pin_8
#define LED2           GPIO_Pin_9
#define LED3           GPIO_Pin_10
#define LED4           GPIO_Pin_11
#define TP_NRST        GPIO_Pin_12
#define AD7606_OS0     GPIO_Pin_13
#define AD7606_OS1     GPIO_Pin_14
#define AD7606_OS2     GPIO_Pin_15

#define Y50_0          GPIO_Pin_16
#define Y50_1          GPIO_Pin_17
#define Y50_2          GPIO_Pin_18
#define Y50_3          GPIO_Pin_19
#define Y50_4          GPIO_Pin_20
#define Y50_5          GPIO_Pin_21
#define Y50_6          GPIO_Pin_22
#define Y50_7          GPIO_Pin_23

#define AD7606_RESET   GPIO_Pin_24
#define AD7606_RANGE   GPIO_Pin_25
#define Y33_2          GPIO_Pin_26
#define Y33_3          GPIO_Pin_27
#define Y33_4          GPIO_Pin_28
#define Y33_5          GPIO_Pin_29
#define Y33_6          GPIO_Pin_30
#define Y33_7          GPIO_Pin_31

void HC574_SetPin(rt_uint32_t _pin, uint8_t _value);
rt_uint8_t HC574_GetPin(rt_uint32_t _pin);

#endif /* __EXT_IO_H__ */
