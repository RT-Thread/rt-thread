/**********************************************************************************
 *
 * @file    es32vf2264.h
 * @brief   ES32VF2264 Head File
 *
 * @date    13 Dec. 2022
 * @author  AE Team
 * @note
 *          Change Logs:
 *          Date            Author          Notes
 *          13 Dec. 2022    Lisq            the first version
 *
 * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 **********************************************************************************
 */

#ifndef __ES32VF2264_H__
#define __ES32VF2264_H__
#ifdef __cplusplus
#define __I  volatile       /* defines 'read only' permissions */
#else
#define __I  volatile const /* defines 'read only' permissions */
#endif
#define __O  volatile       /* defines 'write only' permissions */
#define __IO volatile       /* defines 'read / write' permissions */


typedef enum IRQn
{
    /* ES32VF2264 specific Interrupt Numbers */
    MACHINE_MODE_SOFT_IRQn      =3  ,  //         12
    CLINT_IRQn                  =7  ,  //         28
    MACHINE_MODE_EXTERNAL_IRQn  =11 ,  //         44   //no used in m602@20200218
    WWDT_IRQn                   =16 ,  //   0     64
    IWDT_IRQn                   =17 ,  //   1     68
    LVD_IRQn                    =18 ,  //   2     72
    CSU_IRQn                    =19 ,  //   3
    CMU_IRQn                    =20 ,  //   4     80
    EXTI0_3_IRQn                =21 ,  //   5     84
    EXTI4_7_IRQn                =22 ,  //   6     88
    EXTI8_11_IRQn               =23 ,  //   7     92
    EXTI12_15_IRQn              =24 ,  //   8     96
    DMA_IRQn                    =25 ,  //   9     100
    USB_IRQn                    =27 ,  //   11    108
    ADC_IRQn                    =28 ,  //   12    112
    AD16C4T_UP_TRIG_COM_IRQn    =29 ,  //   13    116
    AD16C4T_CC_IRQn             =30 ,  //   14    120
    BSTIM0_IRQn                 =31 ,  //   15    124
    GPTIMB0_IRQn                =33 ,  //   17    132
    GPTIMB1_IRQn                =34 ,  //   18    136
    GPTIMB2_IRQn                =35 ,  //   19    140
    AD16C4T_IRQn                =37 ,  //   21    148
    I2C0_IRQn                   =39 ,  //   23    156
    I2C1_IRQn                   =40 ,  //   24
    SPI0_I2S0_IRQn              =41 ,  //   25    164
    SPI1_I2S1_IRQn              =42 ,  //   26
    EUART0_IRQn                 =43 ,  //   27
    EUART1_IRQn                 =44 ,  //   28
    CUART0_IRQn                 =45 ,  //   29    180
    CUART1_IRQn                 =46 ,  //   30    184
    CUART2_IRQn                 =47 ,  //   31    188
} IRQn_Type;

#include <stdint.h>
#include "core_rv32.h"

#include "./ES32VF2264/reg_adc.h"
#include "./ES32VF2264/reg_cmu.h"
#include "./ES32VF2264/reg_crc.h"
#include "./ES32VF2264/reg_csu.h"
#include "./ES32VF2264/reg_dbg.h"
#include "./ES32VF2264/reg_dma.h"
#include "./ES32VF2264/reg_gpio.h"
#include "./ES32VF2264/reg_i2c.h"
#include "./ES32VF2264/reg_iwdt.h"
#include "./ES32VF2264/reg_msc.h"
#include "./ES32VF2264/reg_pis.h"
#include "./ES32VF2264/reg_pmu.h"
#include "./ES32VF2264/reg_rmu.h"
#include "./ES32VF2264/reg_spi.h"
#include "./ES32VF2264/reg_syscfg.h"
#include "./ES32VF2264/reg_timer.h"
#include "./ES32VF2264/reg_uart.h"
#include "./ES32VF2264/reg_wwdt.h"
#include "./ES32VF2264/reg_usb.h"

#define SRAM_BASE (0x20000000UL)
#define APB_BASE  (0x40000000UL)
#define AHB_BASE  (0x40080000UL)

#define SYSCFG_BASE     (AHB_BASE + 0x0000)
#define CMU_BASE        (AHB_BASE + 0x0400)
#define RMU_BASE        (AHB_BASE + 0x0800)
#define PMU_BASE        (AHB_BASE + 0x0C00)
#define MSC_BASE        (AHB_BASE + 0x1000)
#define GPIOA_BASE      (AHB_BASE + 0x4000)
#define GPIOB_BASE      (AHB_BASE + 0x4040)
#define GPIOC_BASE      (AHB_BASE + 0x4080)
#define GPIOD_BASE      (AHB_BASE + 0x40C0)
#define EXTI_BASE       (AHB_BASE + 0x4300)
#define CRC_BASE        (AHB_BASE + 0x5000)
#define DMA_BASE        (AHB_BASE + 0x5400)
#define CSU_BASE        (AHB_BASE + 0x5C00)
#define PIS_BASE        (AHB_BASE + 0x6000)
#define USB_BASE        (AHB_BASE + 0x6400)

#define AD16C4T_BASE    (APB_BASE + 0x0000)
#define BS16T_BASE      (APB_BASE + 0x0400)
#define GP16C4T0_BASE   (APB_BASE + 0x0800)
#define GP16C4T1_BASE   (APB_BASE + 0x0C00)
#define GP16C4T2_BASE   (APB_BASE + 0x1000)
#define EUART0_BASE     (APB_BASE + 0x4000)
#define EUART1_BASE     (APB_BASE + 0x4400)
#define CUART0_BASE     (APB_BASE + 0x5000)
#define CUART1_BASE     (APB_BASE + 0x5400)
#define CUART2_BASE     (APB_BASE + 0x5800)
#define SPI0_I2S0_BASE  (APB_BASE + 0x6000)
#define SPI1_I2S1_BASE  (APB_BASE + 0x6400)
#define I2C0_BASE       (APB_BASE + 0x8000)
#define I2C1_BASE       (APB_BASE + 0x8400)
#define WWDT_BASE       (APB_BASE + 0x8800)
#define IWDT_BASE       (APB_BASE + 0x8C00)
#define DBGC_BASE       (APB_BASE + 0x9000)
#define ADC_BASE        (APB_BASE + 0x9400)
#define DMA_MUX_BASE    (APB_BASE + 0xD000)

#define SYSCFG ((SYSCFG_TypeDef *) SYSCFG_BASE)
#define CMU    ((CMU_TypeDef *) CMU_BASE)
#define RMU    ((RMU_TypeDef *) RMU_BASE)
#define PMU    ((PMU_TypeDef *) PMU_BASE)
#define MSC    ((MSC_TypeDef *) MSC_BASE )

#define GPIOA       ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB       ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC       ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD       ((GPIO_TypeDef *) GPIOD_BASE)
#define EXTI        ((EXTI_TypeDef *) EXTI_BASE)
#define CRC         ((CRC_TypeDef *) CRC_BASE)
#define PIS         ((PIS_TypeDef *) PIS_BASE)
#define AD16C4T     ((TIMER_TypeDef *) AD16C4T_BASE)
#define BS16T       ((TIMER_TypeDef *) BS16T_BASE)
#define GP16C4T0    ((TIMER_TypeDef *) GP16C4T0_BASE)
#define GP16C4T1    ((TIMER_TypeDef *) GP16C4T1_BASE)
#define GP16C4T2    ((TIMER_TypeDef *) GP16C4T2_BASE)
#define EUART0      ((UART_TypeDef *) EUART0_BASE)
#define EUART1      ((UART_TypeDef *) EUART1_BASE)
#define CUART0      ((UART_TypeDef *) CUART0_BASE)
#define CUART1      ((UART_TypeDef *) CUART1_BASE)
#define CUART2      ((UART_TypeDef *) CUART2_BASE)
#define SPI0        ((SPI_I2S_TypeDef *) SPI0_I2S0_BASE)
#define SPI1        ((SPI_I2S_TypeDef *) SPI1_I2S1_BASE)
#define I2S0        ((SPI_I2S_TypeDef *) SPI0_I2S0_BASE)
#define I2S1        ((SPI_I2S_TypeDef *) SPI1_I2S1_BASE)
#define I2C0        ((I2C_TypeDef *) I2C0_BASE)
#define I2C1        ((I2C_TypeDef *) I2C1_BASE)
#define WWDT        ((WWDT_TypeDef *) WWDT_BASE)
#define IWDT        ((IWDT_TypeDef *) IWDT_BASE)
#define DBGC        ((DBGC_TypeDef *) DBGC_BASE)
#define ADC         ((ADC_TypeDef *) ADC_BASE)
#define DMA         ((DMA_TypeDef *) DMA_BASE)
#define DMA_MUX     ((DMA_MUX_Typedef *) DMA_MUX_BASE)
#define CSU         ((CSU_TypeDef *) CSU_BASE)
#define USB         ((USB_TypeDef *) USB_BASE)

#endif  /* __ES32VF2264_H__ */
