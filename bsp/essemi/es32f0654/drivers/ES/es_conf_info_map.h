/*
 *  Change Logs:
 *  Date            Author          Notes
 *  2021-04-20      liuhy          the first version
 *
 * Copyright (C) 2021 Shanghai Eastsoft Microelectronics Co., Ltd. All rights reserved.
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
 */

#ifndef __es_conf_info_map_H__
#define __es_conf_info_map_H__

#include <ald_gpio.h>


#define __ES_PIN(index, gpio, gpio_index) {index, GPIO##gpio, GPIO_PIN_##gpio_index}
#define __ES_PIN_DEFAULT {-1, 0, 0}

struct pin_index
{
    int index;
    GPIO_TypeDef *gpio;
    uint32_t pin;
};

static const struct pin_index pins[] =
{
    __ES_PIN_DEFAULT,
    __ES_PIN_DEFAULT,
    __ES_PIN(2, C, 13),
    __ES_PIN(3, C, 14),
    __ES_PIN(4, C, 15),
    __ES_PIN(5, H, 0),
    __ES_PIN(6, H, 1),
    __ES_PIN_DEFAULT,
    __ES_PIN(8, C, 0),
    __ES_PIN(9, C, 1),
    __ES_PIN(10, C, 2),
    __ES_PIN(11, C, 3),
    __ES_PIN(12, H, 3),
    __ES_PIN(13, H, 4),
    __ES_PIN(14, A, 0),
    __ES_PIN(15, A, 1),
    __ES_PIN(16, A, 2),
    __ES_PIN(17, A, 3),
    __ES_PIN(18, F, 0),
    __ES_PIN(19, F, 1),
    __ES_PIN(20, A, 4),
    __ES_PIN(21, A, 5),
    __ES_PIN(22, A, 6),
    __ES_PIN(23, A, 7),
    __ES_PIN(24, C, 4),
    __ES_PIN(25, C, 5),
    __ES_PIN(26, B, 0),
    __ES_PIN(27, B, 1),
    __ES_PIN(28, B, 2),
    __ES_PIN(29, B, 10),
    __ES_PIN(30, B, 11),
    __ES_PIN_DEFAULT,
    __ES_PIN_DEFAULT,
    __ES_PIN(33, B, 12),
    __ES_PIN(34, B, 13),
    __ES_PIN(35, B, 14),
    __ES_PIN(36, B, 15),
    __ES_PIN(37, C, 6),
    __ES_PIN(38, C, 7),
    __ES_PIN(39, C, 8),
    __ES_PIN(40, C, 9),
    __ES_PIN(41, A, 8),
    __ES_PIN(42, A, 9),
    __ES_PIN(43, A, 10),
    __ES_PIN(44, A, 11),
    __ES_PIN(45, A, 12),
    __ES_PIN(46, A, 13),
    __ES_PIN_DEFAULT,
    __ES_PIN_DEFAULT,
    __ES_PIN(49, A, 14),
    __ES_PIN(50, A, 15),
    __ES_PIN(51, C, 10),
    __ES_PIN(52, C, 11),
    __ES_PIN(53, C, 12),
    __ES_PIN(54, D, 2),
    __ES_PIN(55, B, 3),
    __ES_PIN(56, B, 4),
    __ES_PIN(57, B, 5),
    __ES_PIN(58, B, 6),
    __ES_PIN(59, B, 7),
    __ES_PIN(60, H, 2),
    __ES_PIN(61, B, 8),
    __ES_PIN(62, B, 9),
    __ES_PIN_DEFAULT,
    __ES_PIN_DEFAULT,
};

#define ES_GPIO_ADC_CH0_GPIO     GPIOC
#define ES_GPIO_ADC_CH1_GPIO     GPIOC
#define ES_GPIO_ADC_CH2_GPIO     GPIOC
#define ES_GPIO_ADC_CH3_GPIO     GPIOC
#define ES_GPIO_ADC_CH4_GPIO     GPIOA
#define ES_GPIO_ADC_CH5_GPIO     GPIOA
#define ES_GPIO_ADC_CH6_GPIO     GPIOA
#define ES_GPIO_ADC_CH7_GPIO     GPIOA
#define ES_GPIO_ADC_CH8_GPIO     GPIOA
#define ES_GPIO_ADC_CH9_GPIO     GPIOA
#define ES_GPIO_ADC_CH10_GPIO     GPIOA
#define ES_GPIO_ADC_CH11_GPIO     GPIOA
#define ES_GPIO_ADC_CH12_GPIO     GPIOC
#define ES_GPIO_ADC_CH13_GPIO     GPIOC
#define ES_GPIO_ADC_CH14_GPIO     GPIOB
#define ES_GPIO_ADC_CH15_GPIO     GPIOB

#define ES_GPIO_ADC_CH0_PIN      GPIO_PIN_0
#define ES_GPIO_ADC_CH1_PIN      GPIO_PIN_1
#define ES_GPIO_ADC_CH2_PIN      GPIO_PIN_2
#define ES_GPIO_ADC_CH3_PIN      GPIO_PIN_3
#define ES_GPIO_ADC_CH4_PIN      GPIO_PIN_0
#define ES_GPIO_ADC_CH5_PIN      GPIO_PIN_1
#define ES_GPIO_ADC_CH6_PIN      GPIO_PIN_2
#define ES_GPIO_ADC_CH7_PIN      GPIO_PIN_3
#define ES_GPIO_ADC_CH8_PIN      GPIO_PIN_4
#define ES_GPIO_ADC_CH9_PIN      GPIO_PIN_5
#define ES_GPIO_ADC_CH10_PIN      GPIO_PIN_6
#define ES_GPIO_ADC_CH11_PIN      GPIO_PIN_7
#define ES_GPIO_ADC_CH12_PIN      GPIO_PIN_4
#define ES_GPIO_ADC_CH13_PIN      GPIO_PIN_5
#define ES_GPIO_ADC_CH14_PIN      GPIO_PIN_0
#define ES_GPIO_ADC_CH15_PIN      GPIO_PIN_1




#define   ES_PIN_GPIO_C_13   2
#define   ES_PIN_GPIO_C_14   3
#define   ES_PIN_GPIO_C_15   4
#define   ES_PIN_GPIO_H_0   5
#define   ES_PIN_GPIO_H_1   6
#define   ES_PIN_GPIO_C_0   8
#define   ES_PIN_GPIO_C_1   9
#define   ES_PIN_GPIO_C_2   10
#define   ES_PIN_GPIO_C_3   11
#define   ES_PIN_GPIO_H_3   12
#define   ES_PIN_GPIO_H_4   13
#define   ES_PIN_GPIO_A_0   14
#define   ES_PIN_GPIO_A_1   15
#define   ES_PIN_GPIO_A_2   16
#define   ES_PIN_GPIO_A_3   17
#define   ES_PIN_GPIO_F_0   18
#define   ES_PIN_GPIO_F_1   19
#define   ES_PIN_GPIO_A_4   20
#define   ES_PIN_GPIO_A_5   21
#define   ES_PIN_GPIO_A_6   22
#define   ES_PIN_GPIO_A_7   23
#define   ES_PIN_GPIO_C_4   24
#define   ES_PIN_GPIO_C_5   25
#define   ES_PIN_GPIO_B_0   26
#define   ES_PIN_GPIO_B_1   27
#define   ES_PIN_GPIO_B_2   28
#define   ES_PIN_GPIO_B_10   29
#define   ES_PIN_GPIO_B_11   30
#define   ES_PIN_GPIO_B_12   33
#define   ES_PIN_GPIO_B_13   34
#define   ES_PIN_GPIO_B_14   35
#define   ES_PIN_GPIO_B_15   36
#define   ES_PIN_GPIO_C_6   37
#define   ES_PIN_GPIO_C_7   38
#define   ES_PIN_GPIO_C_8   39
#define   ES_PIN_GPIO_C_9   40
#define   ES_PIN_GPIO_A_8   41
#define   ES_PIN_GPIO_A_9   42
#define   ES_PIN_GPIO_A_10   43
#define   ES_PIN_GPIO_A_11   44
#define   ES_PIN_GPIO_A_12   45
#define   ES_PIN_GPIO_A_13   46
#define   ES_PIN_GPIO_A_14   49
#define   ES_PIN_GPIO_A_15   50
#define   ES_PIN_GPIO_C_10   51
#define   ES_PIN_GPIO_C_11   52
#define   ES_PIN_GPIO_C_12   53
#define   ES_PIN_GPIO_D_2   54
#define   ES_PIN_GPIO_B_3   55
#define   ES_PIN_GPIO_B_4   56
#define   ES_PIN_GPIO_B_5   57
#define   ES_PIN_GPIO_B_6   58
#define   ES_PIN_GPIO_B_7   59
#define   ES_PIN_GPIO_H_2   60
#define   ES_PIN_GPIO_B_8   61
#define   ES_PIN_GPIO_B_9   62



/* UART_TX */


#ifndef ES_UART0_TX_GPIO_FUNC
#define ES_UART0_TX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART0_TX_GPIO_PORT
#define ES_UART0_TX_GPIO_PORT GPIOB
#endif
#ifndef ES_UART0_TX_GPIO_PIN
#define ES_UART0_TX_GPIO_PIN GPIO_PIN_10
#endif

#ifndef ES_UART0_TX_PIN
#ifdef ES_PIN_GPIO_B_10
#define ES_UART0_TX_PIN ES_PIN_GPIO_B_10
#endif
#endif

#ifndef ES_UART0_TX_GPIO_FUNC
#define ES_UART0_TX_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART0_TX_GPIO_PORT
#define ES_UART0_TX_GPIO_PORT GPIOA
#endif
#ifndef ES_UART0_TX_GPIO_PIN
#define ES_UART0_TX_GPIO_PIN GPIO_PIN_9
#endif

#ifndef ES_UART0_TX_PIN
#ifdef ES_PIN_GPIO_A_9
#define ES_UART0_TX_PIN ES_PIN_GPIO_A_9
#endif
#endif

#ifndef ES_UART0_TX_GPIO_FUNC
#define ES_UART0_TX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART0_TX_GPIO_PORT
#define ES_UART0_TX_GPIO_PORT GPIOH
#endif
#ifndef ES_UART0_TX_GPIO_PIN
#define ES_UART0_TX_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_UART0_TX_PIN
#ifdef ES_PIN_GPIO_H_0
#define ES_UART0_TX_PIN ES_PIN_GPIO_H_0
#endif
#endif

#ifndef ES_UART0_TX_GPIO_FUNC
#define ES_UART0_TX_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART0_TX_GPIO_PORT
#define ES_UART0_TX_GPIO_PORT GPIOD
#endif
#ifndef ES_UART0_TX_GPIO_PIN
#define ES_UART0_TX_GPIO_PIN GPIO_PIN_8
#endif

#ifndef ES_UART0_TX_PIN
#ifdef ES_PIN_GPIO_D_8
#define ES_UART0_TX_PIN ES_PIN_GPIO_D_8
#endif
#endif

#ifndef ES_UART1_TX_GPIO_FUNC
#define ES_UART1_TX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART1_TX_GPIO_PORT
#define ES_UART1_TX_GPIO_PORT GPIOC
#endif
#ifndef ES_UART1_TX_GPIO_PIN
#define ES_UART1_TX_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_UART1_TX_PIN
#ifdef ES_PIN_GPIO_C_0
#define ES_UART1_TX_PIN ES_PIN_GPIO_C_0
#endif
#endif

#ifndef ES_UART1_TX_GPIO_FUNC
#define ES_UART1_TX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART1_TX_GPIO_PORT
#define ES_UART1_TX_GPIO_PORT GPIOC
#endif
#ifndef ES_UART1_TX_GPIO_PIN
#define ES_UART1_TX_GPIO_PIN GPIO_PIN_10
#endif

#ifndef ES_UART1_TX_PIN
#ifdef ES_PIN_GPIO_C_10
#define ES_UART1_TX_PIN ES_PIN_GPIO_C_10
#endif
#endif

#ifndef ES_UART1_TX_GPIO_FUNC
#define ES_UART1_TX_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_UART1_TX_GPIO_PORT
#define ES_UART1_TX_GPIO_PORT GPIOA
#endif
#ifndef ES_UART1_TX_GPIO_PIN
#define ES_UART1_TX_GPIO_PIN GPIO_PIN_13
#endif

#ifndef ES_UART1_TX_PIN
#ifdef ES_PIN_GPIO_A_13
#define ES_UART1_TX_PIN ES_PIN_GPIO_A_13
#endif
#endif

#ifndef ES_UART1_TX_GPIO_FUNC
#define ES_UART1_TX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART1_TX_GPIO_PORT
#define ES_UART1_TX_GPIO_PORT GPIOD
#endif
#ifndef ES_UART1_TX_GPIO_PIN
#define ES_UART1_TX_GPIO_PIN GPIO_PIN_5
#endif

#ifndef ES_UART1_TX_PIN
#ifdef ES_PIN_GPIO_D_5
#define ES_UART1_TX_PIN ES_PIN_GPIO_D_5
#endif
#endif

#ifndef ES_UART2_TX_GPIO_FUNC
#define ES_UART2_TX_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART2_TX_GPIO_PORT
#define ES_UART2_TX_GPIO_PORT GPIOC
#endif
#ifndef ES_UART2_TX_GPIO_PIN
#define ES_UART2_TX_GPIO_PIN GPIO_PIN_12
#endif

#ifndef ES_UART2_TX_PIN
#ifdef ES_PIN_GPIO_C_12
#define ES_UART2_TX_PIN ES_PIN_GPIO_C_12
#endif
#endif

#ifndef ES_UART2_TX_GPIO_FUNC
#define ES_UART2_TX_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART2_TX_GPIO_PORT
#define ES_UART2_TX_GPIO_PORT GPIOB
#endif
#ifndef ES_UART2_TX_GPIO_PIN
#define ES_UART2_TX_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_UART2_TX_PIN
#ifdef ES_PIN_GPIO_B_3
#define ES_UART2_TX_PIN ES_PIN_GPIO_B_3
#endif
#endif

#ifndef ES_UART2_TX_GPIO_FUNC
#define ES_UART2_TX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART2_TX_GPIO_PORT
#define ES_UART2_TX_GPIO_PORT GPIOE
#endif
#ifndef ES_UART2_TX_GPIO_PIN
#define ES_UART2_TX_GPIO_PIN GPIO_PIN_2
#endif

#ifndef ES_UART2_TX_PIN
#ifdef ES_PIN_GPIO_E_2
#define ES_UART2_TX_PIN ES_PIN_GPIO_E_2
#endif
#endif

#ifndef ES_UART3_TX_GPIO_FUNC
#define ES_UART3_TX_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_UART3_TX_GPIO_PORT
#define ES_UART3_TX_GPIO_PORT GPIOC
#endif
#ifndef ES_UART3_TX_GPIO_PIN
#define ES_UART3_TX_GPIO_PIN GPIO_PIN_4
#endif

#ifndef ES_UART3_TX_PIN
#ifdef ES_PIN_GPIO_C_4
#define ES_UART3_TX_PIN ES_PIN_GPIO_C_4
#endif
#endif

#ifndef ES_UART3_TX_GPIO_FUNC
#define ES_UART3_TX_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART3_TX_GPIO_PORT
#define ES_UART3_TX_GPIO_PORT GPIOE
#endif
#ifndef ES_UART3_TX_GPIO_PIN
#define ES_UART3_TX_GPIO_PIN GPIO_PIN_10
#endif

#ifndef ES_UART3_TX_PIN
#ifdef ES_PIN_GPIO_E_10
#define ES_UART3_TX_PIN ES_PIN_GPIO_E_10
#endif
#endif

#ifndef ES_UART3_TX_GPIO_FUNC
#define ES_UART3_TX_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_UART3_TX_GPIO_PORT
#define ES_UART3_TX_GPIO_PORT GPIOD
#endif
#ifndef ES_UART3_TX_GPIO_PIN
#define ES_UART3_TX_GPIO_PIN GPIO_PIN_14
#endif

#ifndef ES_UART3_TX_PIN
#ifdef ES_PIN_GPIO_D_14
#define ES_UART3_TX_PIN ES_PIN_GPIO_D_14
#endif
#endif


/* UART_RX */


#ifndef ES_UART0_RX_GPIO_FUNC
#define ES_UART0_RX_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART0_RX_GPIO_PORT
#define ES_UART0_RX_GPIO_PORT GPIOA
#endif
#ifndef ES_UART0_RX_GPIO_PIN
#define ES_UART0_RX_GPIO_PIN GPIO_PIN_10
#endif

#ifndef ES_UART0_RX_PIN
#ifdef ES_PIN_GPIO_A_10
#define ES_UART0_RX_PIN ES_PIN_GPIO_A_10
#endif
#endif

#ifndef ES_UART0_RX_GPIO_FUNC
#define ES_UART0_RX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART0_RX_GPIO_PORT
#define ES_UART0_RX_GPIO_PORT GPIOH
#endif
#ifndef ES_UART0_RX_GPIO_PIN
#define ES_UART0_RX_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_UART0_RX_PIN
#ifdef ES_PIN_GPIO_H_1
#define ES_UART0_RX_PIN ES_PIN_GPIO_H_1
#endif
#endif

#ifndef ES_UART0_RX_GPIO_FUNC
#define ES_UART0_RX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART0_RX_GPIO_PORT
#define ES_UART0_RX_GPIO_PORT GPIOB
#endif
#ifndef ES_UART0_RX_GPIO_PIN
#define ES_UART0_RX_GPIO_PIN GPIO_PIN_11
#endif

#ifndef ES_UART0_RX_PIN
#ifdef ES_PIN_GPIO_B_11
#define ES_UART0_RX_PIN ES_PIN_GPIO_B_11
#endif
#endif

#ifndef ES_UART0_RX_GPIO_FUNC
#define ES_UART0_RX_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART0_RX_GPIO_PORT
#define ES_UART0_RX_GPIO_PORT GPIOD
#endif
#ifndef ES_UART0_RX_GPIO_PIN
#define ES_UART0_RX_GPIO_PIN GPIO_PIN_9
#endif

#ifndef ES_UART0_RX_PIN
#ifdef ES_PIN_GPIO_D_9
#define ES_UART0_RX_PIN ES_PIN_GPIO_D_9
#endif
#endif

#ifndef ES_UART1_RX_GPIO_FUNC
#define ES_UART1_RX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART1_RX_GPIO_PORT
#define ES_UART1_RX_GPIO_PORT GPIOC
#endif
#ifndef ES_UART1_RX_GPIO_PIN
#define ES_UART1_RX_GPIO_PIN GPIO_PIN_11
#endif

#ifndef ES_UART1_RX_PIN
#ifdef ES_PIN_GPIO_C_11
#define ES_UART1_RX_PIN ES_PIN_GPIO_C_11
#endif
#endif

#ifndef ES_UART1_RX_GPIO_FUNC
#define ES_UART1_RX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART1_RX_GPIO_PORT
#define ES_UART1_RX_GPIO_PORT GPIOC
#endif
#ifndef ES_UART1_RX_GPIO_PIN
#define ES_UART1_RX_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_UART1_RX_PIN
#ifdef ES_PIN_GPIO_C_1
#define ES_UART1_RX_PIN ES_PIN_GPIO_C_1
#endif
#endif

#ifndef ES_UART1_RX_GPIO_FUNC
#define ES_UART1_RX_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_UART1_RX_GPIO_PORT
#define ES_UART1_RX_GPIO_PORT GPIOA
#endif
#ifndef ES_UART1_RX_GPIO_PIN
#define ES_UART1_RX_GPIO_PIN GPIO_PIN_14
#endif

#ifndef ES_UART1_RX_PIN
#ifdef ES_PIN_GPIO_A_14
#define ES_UART1_RX_PIN ES_PIN_GPIO_A_14
#endif
#endif

#ifndef ES_UART1_RX_GPIO_FUNC
#define ES_UART1_RX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART1_RX_GPIO_PORT
#define ES_UART1_RX_GPIO_PORT GPIOD
#endif
#ifndef ES_UART1_RX_GPIO_PIN
#define ES_UART1_RX_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_UART1_RX_PIN
#ifdef ES_PIN_GPIO_D_6
#define ES_UART1_RX_PIN ES_PIN_GPIO_D_6
#endif
#endif

#ifndef ES_UART2_RX_GPIO_FUNC
#define ES_UART2_RX_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART2_RX_GPIO_PORT
#define ES_UART2_RX_GPIO_PORT GPIOD
#endif
#ifndef ES_UART2_RX_GPIO_PIN
#define ES_UART2_RX_GPIO_PIN GPIO_PIN_2
#endif

#ifndef ES_UART2_RX_PIN
#ifdef ES_PIN_GPIO_D_2
#define ES_UART2_RX_PIN ES_PIN_GPIO_D_2
#endif
#endif

#ifndef ES_UART2_RX_GPIO_FUNC
#define ES_UART2_RX_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART2_RX_GPIO_PORT
#define ES_UART2_RX_GPIO_PORT GPIOB
#endif
#ifndef ES_UART2_RX_GPIO_PIN
#define ES_UART2_RX_GPIO_PIN GPIO_PIN_4
#endif

#ifndef ES_UART2_RX_PIN
#ifdef ES_PIN_GPIO_B_4
#define ES_UART2_RX_PIN ES_PIN_GPIO_B_4
#endif
#endif

#ifndef ES_UART2_RX_GPIO_FUNC
#define ES_UART2_RX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART2_RX_GPIO_PORT
#define ES_UART2_RX_GPIO_PORT GPIOE
#endif
#ifndef ES_UART2_RX_GPIO_PIN
#define ES_UART2_RX_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_UART2_RX_PIN
#ifdef ES_PIN_GPIO_E_3
#define ES_UART2_RX_PIN ES_PIN_GPIO_E_3
#endif
#endif

#ifndef ES_UART3_RX_GPIO_FUNC
#define ES_UART3_RX_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_UART3_RX_GPIO_PORT
#define ES_UART3_RX_GPIO_PORT GPIOC
#endif
#ifndef ES_UART3_RX_GPIO_PIN
#define ES_UART3_RX_GPIO_PIN GPIO_PIN_5
#endif

#ifndef ES_UART3_RX_PIN
#ifdef ES_PIN_GPIO_C_5
#define ES_UART3_RX_PIN ES_PIN_GPIO_C_5
#endif
#endif

#ifndef ES_UART3_RX_GPIO_FUNC
#define ES_UART3_RX_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART3_RX_GPIO_PORT
#define ES_UART3_RX_GPIO_PORT GPIOE
#endif
#ifndef ES_UART3_RX_GPIO_PIN
#define ES_UART3_RX_GPIO_PIN GPIO_PIN_11
#endif

#ifndef ES_UART3_RX_PIN
#ifdef ES_PIN_GPIO_E_11
#define ES_UART3_RX_PIN ES_PIN_GPIO_E_11
#endif
#endif

#ifndef ES_UART3_RX_GPIO_FUNC
#define ES_UART3_RX_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_UART3_RX_GPIO_PORT
#define ES_UART3_RX_GPIO_PORT GPIOD
#endif
#ifndef ES_UART3_RX_GPIO_PIN
#define ES_UART3_RX_GPIO_PIN GPIO_PIN_13
#endif

#ifndef ES_UART3_RX_PIN
#ifdef ES_PIN_GPIO_D_13
#define ES_UART3_RX_PIN ES_PIN_GPIO_D_13
#endif
#endif


/* UART_RTS */


#ifndef ES_UART0_RTS_GPIO_FUNC
#define ES_UART0_RTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART0_RTS_GPIO_PORT
#define ES_UART0_RTS_GPIO_PORT GPIOB
#endif
#ifndef ES_UART0_RTS_GPIO_PIN
#define ES_UART0_RTS_GPIO_PIN GPIO_PIN_14
#endif

#ifndef ES_UART0_RTS_PIN
#ifdef ES_PIN_GPIO_B_14
#define ES_UART0_RTS_PIN ES_PIN_GPIO_B_14
#endif
#endif

#ifndef ES_UART0_RTS_GPIO_FUNC
#define ES_UART0_RTS_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART0_RTS_GPIO_PORT
#define ES_UART0_RTS_GPIO_PORT GPIOA
#endif
#ifndef ES_UART0_RTS_GPIO_PIN
#define ES_UART0_RTS_GPIO_PIN GPIO_PIN_12
#endif

#ifndef ES_UART0_RTS_PIN
#ifdef ES_PIN_GPIO_A_12
#define ES_UART0_RTS_PIN ES_PIN_GPIO_A_12
#endif
#endif

#ifndef ES_UART0_RTS_GPIO_FUNC
#define ES_UART0_RTS_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART0_RTS_GPIO_PORT
#define ES_UART0_RTS_GPIO_PORT GPIOD
#endif
#ifndef ES_UART0_RTS_GPIO_PIN
#define ES_UART0_RTS_GPIO_PIN GPIO_PIN_12
#endif

#ifndef ES_UART0_RTS_PIN
#ifdef ES_PIN_GPIO_D_12
#define ES_UART0_RTS_PIN ES_PIN_GPIO_D_12
#endif
#endif

#ifndef ES_UART1_RTS_GPIO_FUNC
#define ES_UART1_RTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART1_RTS_GPIO_PORT
#define ES_UART1_RTS_GPIO_PORT GPIOC
#endif
#ifndef ES_UART1_RTS_GPIO_PIN
#define ES_UART1_RTS_GPIO_PIN GPIO_PIN_12
#endif

#ifndef ES_UART1_RTS_PIN
#ifdef ES_PIN_GPIO_C_12
#define ES_UART1_RTS_PIN ES_PIN_GPIO_C_12
#endif
#endif

#ifndef ES_UART1_RTS_GPIO_FUNC
#define ES_UART1_RTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART1_RTS_GPIO_PORT
#define ES_UART1_RTS_GPIO_PORT GPIOC
#endif
#ifndef ES_UART1_RTS_GPIO_PIN
#define ES_UART1_RTS_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_UART1_RTS_PIN
#ifdef ES_PIN_GPIO_C_3
#define ES_UART1_RTS_PIN ES_PIN_GPIO_C_3
#endif
#endif

#ifndef ES_UART2_RTS_GPIO_FUNC
#define ES_UART2_RTS_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART2_RTS_GPIO_PORT
#define ES_UART2_RTS_GPIO_PORT GPIOC
#endif
#ifndef ES_UART2_RTS_GPIO_PIN
#define ES_UART2_RTS_GPIO_PIN GPIO_PIN_10
#endif

#ifndef ES_UART2_RTS_PIN
#ifdef ES_PIN_GPIO_C_10
#define ES_UART2_RTS_PIN ES_PIN_GPIO_C_10
#endif
#endif

#ifndef ES_UART2_RTS_GPIO_FUNC
#define ES_UART2_RTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART2_RTS_GPIO_PORT
#define ES_UART2_RTS_GPIO_PORT GPIOE
#endif
#ifndef ES_UART2_RTS_GPIO_PIN
#define ES_UART2_RTS_GPIO_PIN GPIO_PIN_5
#endif

#ifndef ES_UART2_RTS_PIN
#ifdef ES_PIN_GPIO_E_5
#define ES_UART2_RTS_PIN ES_PIN_GPIO_E_5
#endif
#endif

#ifndef ES_UART3_RTS_GPIO_FUNC
#define ES_UART3_RTS_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_UART3_RTS_GPIO_PORT
#define ES_UART3_RTS_GPIO_PORT GPIOB
#endif
#ifndef ES_UART3_RTS_GPIO_PIN
#define ES_UART3_RTS_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_UART3_RTS_PIN
#ifdef ES_PIN_GPIO_B_1
#define ES_UART3_RTS_PIN ES_PIN_GPIO_B_1
#endif
#endif

#ifndef ES_UART3_RTS_GPIO_FUNC
#define ES_UART3_RTS_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART3_RTS_GPIO_PORT
#define ES_UART3_RTS_GPIO_PORT GPIOE
#endif
#ifndef ES_UART3_RTS_GPIO_PIN
#define ES_UART3_RTS_GPIO_PIN GPIO_PIN_13
#endif

#ifndef ES_UART3_RTS_PIN
#ifdef ES_PIN_GPIO_E_13
#define ES_UART3_RTS_PIN ES_PIN_GPIO_E_13
#endif
#endif


/* UART_CTS */


#ifndef ES_UART0_CTS_GPIO_FUNC
#define ES_UART0_CTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART0_CTS_GPIO_PORT
#define ES_UART0_CTS_GPIO_PORT GPIOB
#endif
#ifndef ES_UART0_CTS_GPIO_PIN
#define ES_UART0_CTS_GPIO_PIN GPIO_PIN_13
#endif

#ifndef ES_UART0_CTS_PIN
#ifdef ES_PIN_GPIO_B_13
#define ES_UART0_CTS_PIN ES_PIN_GPIO_B_13
#endif
#endif

#ifndef ES_UART0_CTS_GPIO_FUNC
#define ES_UART0_CTS_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART0_CTS_GPIO_PORT
#define ES_UART0_CTS_GPIO_PORT GPIOA
#endif
#ifndef ES_UART0_CTS_GPIO_PIN
#define ES_UART0_CTS_GPIO_PIN GPIO_PIN_11
#endif

#ifndef ES_UART0_CTS_PIN
#ifdef ES_PIN_GPIO_A_11
#define ES_UART0_CTS_PIN ES_PIN_GPIO_A_11
#endif
#endif

#ifndef ES_UART0_CTS_GPIO_FUNC
#define ES_UART0_CTS_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART0_CTS_GPIO_PORT
#define ES_UART0_CTS_GPIO_PORT GPIOD
#endif
#ifndef ES_UART0_CTS_GPIO_PIN
#define ES_UART0_CTS_GPIO_PIN GPIO_PIN_11
#endif

#ifndef ES_UART0_CTS_PIN
#ifdef ES_PIN_GPIO_D_11
#define ES_UART0_CTS_PIN ES_PIN_GPIO_D_11
#endif
#endif

#ifndef ES_UART1_CTS_GPIO_FUNC
#define ES_UART1_CTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART1_CTS_GPIO_PORT
#define ES_UART1_CTS_GPIO_PORT GPIOC
#endif
#ifndef ES_UART1_CTS_GPIO_PIN
#define ES_UART1_CTS_GPIO_PIN GPIO_PIN_2
#endif

#ifndef ES_UART1_CTS_PIN
#ifdef ES_PIN_GPIO_C_2
#define ES_UART1_CTS_PIN ES_PIN_GPIO_C_2
#endif
#endif

#ifndef ES_UART1_CTS_GPIO_FUNC
#define ES_UART1_CTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART1_CTS_GPIO_PORT
#define ES_UART1_CTS_GPIO_PORT GPIOD
#endif
#ifndef ES_UART1_CTS_GPIO_PIN
#define ES_UART1_CTS_GPIO_PIN GPIO_PIN_2
#endif

#ifndef ES_UART1_CTS_PIN
#ifdef ES_PIN_GPIO_D_2
#define ES_UART1_CTS_PIN ES_PIN_GPIO_D_2
#endif
#endif

#ifndef ES_UART2_CTS_GPIO_FUNC
#define ES_UART2_CTS_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART2_CTS_GPIO_PORT
#define ES_UART2_CTS_GPIO_PORT GPIOC
#endif
#ifndef ES_UART2_CTS_GPIO_PIN
#define ES_UART2_CTS_GPIO_PIN GPIO_PIN_11
#endif

#ifndef ES_UART2_CTS_PIN
#ifdef ES_PIN_GPIO_C_11
#define ES_UART2_CTS_PIN ES_PIN_GPIO_C_11
#endif
#endif

#ifndef ES_UART2_CTS_GPIO_FUNC
#define ES_UART2_CTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART2_CTS_GPIO_PORT
#define ES_UART2_CTS_GPIO_PORT GPIOE
#endif
#ifndef ES_UART2_CTS_GPIO_PIN
#define ES_UART2_CTS_GPIO_PIN GPIO_PIN_4
#endif

#ifndef ES_UART2_CTS_PIN
#ifdef ES_PIN_GPIO_E_4
#define ES_UART2_CTS_PIN ES_PIN_GPIO_E_4
#endif
#endif

#ifndef ES_UART3_CTS_GPIO_FUNC
#define ES_UART3_CTS_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_UART3_CTS_GPIO_PORT
#define ES_UART3_CTS_GPIO_PORT GPIOB
#endif
#ifndef ES_UART3_CTS_GPIO_PIN
#define ES_UART3_CTS_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_UART3_CTS_PIN
#ifdef ES_PIN_GPIO_B_0
#define ES_UART3_CTS_PIN ES_PIN_GPIO_B_0
#endif
#endif

#ifndef ES_UART3_CTS_GPIO_FUNC
#define ES_UART3_CTS_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART3_CTS_GPIO_PORT
#define ES_UART3_CTS_GPIO_PORT GPIOE
#endif
#ifndef ES_UART3_CTS_GPIO_PIN
#define ES_UART3_CTS_GPIO_PIN GPIO_PIN_12
#endif

#ifndef ES_UART3_CTS_PIN
#ifdef ES_PIN_GPIO_E_12
#define ES_UART3_CTS_PIN ES_PIN_GPIO_E_12
#endif
#endif


/* UART_CK */



/* USART_TX */


#ifndef ES_USART0_TX_GPIO_FUNC
#define ES_USART0_TX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_USART0_TX_GPIO_PORT
#define ES_USART0_TX_GPIO_PORT GPIOB
#endif
#ifndef ES_USART0_TX_GPIO_PIN
#define ES_USART0_TX_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_USART0_TX_PIN
#ifdef ES_PIN_GPIO_B_6
#define ES_USART0_TX_PIN ES_PIN_GPIO_B_6
#endif
#endif

#ifndef ES_USART0_TX_GPIO_FUNC
#define ES_USART0_TX_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_USART0_TX_GPIO_PORT
#define ES_USART0_TX_GPIO_PORT GPIOE
#endif
#ifndef ES_USART0_TX_GPIO_PIN
#define ES_USART0_TX_GPIO_PIN GPIO_PIN_10
#endif

#ifndef ES_USART0_TX_PIN
#ifdef ES_PIN_GPIO_E_10
#define ES_USART0_TX_PIN ES_PIN_GPIO_E_10
#endif
#endif

#ifndef ES_USART1_TX_GPIO_FUNC
#define ES_USART1_TX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_USART1_TX_GPIO_PORT
#define ES_USART1_TX_GPIO_PORT GPIOA
#endif
#ifndef ES_USART1_TX_GPIO_PIN
#define ES_USART1_TX_GPIO_PIN GPIO_PIN_2
#endif

#ifndef ES_USART1_TX_PIN
#ifdef ES_PIN_GPIO_A_2
#define ES_USART1_TX_PIN ES_PIN_GPIO_A_2
#endif
#endif

#ifndef ES_USART1_TX_GPIO_FUNC
#define ES_USART1_TX_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_USART1_TX_GPIO_PORT
#define ES_USART1_TX_GPIO_PORT GPIOB
#endif
#ifndef ES_USART1_TX_GPIO_PIN
#define ES_USART1_TX_GPIO_PIN GPIO_PIN_9
#endif

#ifndef ES_USART1_TX_PIN
#ifdef ES_PIN_GPIO_B_9
#define ES_USART1_TX_PIN ES_PIN_GPIO_B_9
#endif
#endif

#ifndef ES_USART1_TX_GPIO_FUNC
#define ES_USART1_TX_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_USART1_TX_GPIO_PORT
#define ES_USART1_TX_GPIO_PORT GPIOD
#endif
#ifndef ES_USART1_TX_GPIO_PIN
#define ES_USART1_TX_GPIO_PIN GPIO_PIN_5
#endif

#ifndef ES_USART1_TX_PIN
#ifdef ES_PIN_GPIO_D_5
#define ES_USART1_TX_PIN ES_PIN_GPIO_D_5
#endif
#endif


/* USART_RX */


#ifndef ES_USART0_RX_GPIO_FUNC
#define ES_USART0_RX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_USART0_RX_GPIO_PORT
#define ES_USART0_RX_GPIO_PORT GPIOB
#endif
#ifndef ES_USART0_RX_GPIO_PIN
#define ES_USART0_RX_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_USART0_RX_PIN
#ifdef ES_PIN_GPIO_B_7
#define ES_USART0_RX_PIN ES_PIN_GPIO_B_7
#endif
#endif

#ifndef ES_USART0_RX_GPIO_FUNC
#define ES_USART0_RX_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_USART0_RX_GPIO_PORT
#define ES_USART0_RX_GPIO_PORT GPIOE
#endif
#ifndef ES_USART0_RX_GPIO_PIN
#define ES_USART0_RX_GPIO_PIN GPIO_PIN_11
#endif

#ifndef ES_USART0_RX_PIN
#ifdef ES_PIN_GPIO_E_11
#define ES_USART0_RX_PIN ES_PIN_GPIO_E_11
#endif
#endif

#ifndef ES_USART1_RX_GPIO_FUNC
#define ES_USART1_RX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_USART1_RX_GPIO_PORT
#define ES_USART1_RX_GPIO_PORT GPIOA
#endif
#ifndef ES_USART1_RX_GPIO_PIN
#define ES_USART1_RX_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_USART1_RX_PIN
#ifdef ES_PIN_GPIO_A_3
#define ES_USART1_RX_PIN ES_PIN_GPIO_A_3
#endif
#endif

#ifndef ES_USART1_RX_GPIO_FUNC
#define ES_USART1_RX_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_USART1_RX_GPIO_PORT
#define ES_USART1_RX_GPIO_PORT GPIOD
#endif
#ifndef ES_USART1_RX_GPIO_PIN
#define ES_USART1_RX_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_USART1_RX_PIN
#ifdef ES_PIN_GPIO_D_6
#define ES_USART1_RX_PIN ES_PIN_GPIO_D_6
#endif
#endif

#ifndef ES_USART1_RX_GPIO_FUNC
#define ES_USART1_RX_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_USART1_RX_GPIO_PORT
#define ES_USART1_RX_GPIO_PORT GPIOB
#endif
#ifndef ES_USART1_RX_GPIO_PIN
#define ES_USART1_RX_GPIO_PIN GPIO_PIN_8
#endif

#ifndef ES_USART1_RX_PIN
#ifdef ES_PIN_GPIO_B_8
#define ES_USART1_RX_PIN ES_PIN_GPIO_B_8
#endif
#endif


/* USART_RTS */


#ifndef ES_USART0_RTS_GPIO_FUNC
#define ES_USART0_RTS_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_USART0_RTS_GPIO_PORT
#define ES_USART0_RTS_GPIO_PORT GPIOE
#endif
#ifndef ES_USART0_RTS_GPIO_PIN
#define ES_USART0_RTS_GPIO_PIN GPIO_PIN_13
#endif

#ifndef ES_USART0_RTS_PIN
#ifdef ES_PIN_GPIO_E_13
#define ES_USART0_RTS_PIN ES_PIN_GPIO_E_13
#endif
#endif

#ifndef ES_USART0_RTS_GPIO_FUNC
#define ES_USART0_RTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_USART0_RTS_GPIO_PORT
#define ES_USART0_RTS_GPIO_PORT GPIOE
#endif
#ifndef ES_USART0_RTS_GPIO_PIN
#define ES_USART0_RTS_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_USART0_RTS_PIN
#ifdef ES_PIN_GPIO_E_1
#define ES_USART0_RTS_PIN ES_PIN_GPIO_E_1
#endif
#endif

#ifndef ES_USART1_RTS_GPIO_FUNC
#define ES_USART1_RTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_USART1_RTS_GPIO_PORT
#define ES_USART1_RTS_GPIO_PORT GPIOA
#endif
#ifndef ES_USART1_RTS_GPIO_PIN
#define ES_USART1_RTS_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_USART1_RTS_PIN
#ifdef ES_PIN_GPIO_A_1
#define ES_USART1_RTS_PIN ES_PIN_GPIO_A_1
#endif
#endif

#ifndef ES_USART1_RTS_GPIO_FUNC
#define ES_USART1_RTS_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_USART1_RTS_GPIO_PORT
#define ES_USART1_RTS_GPIO_PORT GPIOD
#endif
#ifndef ES_USART1_RTS_GPIO_PIN
#define ES_USART1_RTS_GPIO_PIN GPIO_PIN_4
#endif

#ifndef ES_USART1_RTS_PIN
#ifdef ES_PIN_GPIO_D_4
#define ES_USART1_RTS_PIN ES_PIN_GPIO_D_4
#endif
#endif


/* USART_CTS */


#ifndef ES_USART0_CTS_GPIO_FUNC
#define ES_USART0_CTS_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_USART0_CTS_GPIO_PORT
#define ES_USART0_CTS_GPIO_PORT GPIOE
#endif
#ifndef ES_USART0_CTS_GPIO_PIN
#define ES_USART0_CTS_GPIO_PIN GPIO_PIN_12
#endif

#ifndef ES_USART0_CTS_PIN
#ifdef ES_PIN_GPIO_E_12
#define ES_USART0_CTS_PIN ES_PIN_GPIO_E_12
#endif
#endif

#ifndef ES_USART0_CTS_GPIO_FUNC
#define ES_USART0_CTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_USART0_CTS_GPIO_PORT
#define ES_USART0_CTS_GPIO_PORT GPIOE
#endif
#ifndef ES_USART0_CTS_GPIO_PIN
#define ES_USART0_CTS_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_USART0_CTS_PIN
#ifdef ES_PIN_GPIO_E_0
#define ES_USART0_CTS_PIN ES_PIN_GPIO_E_0
#endif
#endif

#ifndef ES_USART1_CTS_GPIO_FUNC
#define ES_USART1_CTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_USART1_CTS_GPIO_PORT
#define ES_USART1_CTS_GPIO_PORT GPIOA
#endif
#ifndef ES_USART1_CTS_GPIO_PIN
#define ES_USART1_CTS_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_USART1_CTS_PIN
#ifdef ES_PIN_GPIO_A_0
#define ES_USART1_CTS_PIN ES_PIN_GPIO_A_0
#endif
#endif

#ifndef ES_USART1_CTS_GPIO_FUNC
#define ES_USART1_CTS_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_USART1_CTS_GPIO_PORT
#define ES_USART1_CTS_GPIO_PORT GPIOD
#endif
#ifndef ES_USART1_CTS_GPIO_PIN
#define ES_USART1_CTS_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_USART1_CTS_PIN
#ifdef ES_PIN_GPIO_D_3
#define ES_USART1_CTS_PIN ES_PIN_GPIO_D_3
#endif
#endif


/* USART_CK */


#ifndef ES_USART0_CK_GPIO_FUNC
#define ES_USART0_CK_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_USART0_CK_GPIO_PORT
#define ES_USART0_CK_GPIO_PORT GPIOA
#endif
#ifndef ES_USART0_CK_GPIO_PIN
#define ES_USART0_CK_GPIO_PIN GPIO_PIN_8
#endif

#ifndef ES_USART0_CK_PIN
#ifdef ES_PIN_GPIO_A_8
#define ES_USART0_CK_PIN ES_PIN_GPIO_A_8
#endif
#endif

#ifndef ES_USART0_CK_GPIO_FUNC
#define ES_USART0_CK_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_USART0_CK_GPIO_PORT
#define ES_USART0_CK_GPIO_PORT GPIOE
#endif
#ifndef ES_USART0_CK_GPIO_PIN
#define ES_USART0_CK_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_USART0_CK_PIN
#ifdef ES_PIN_GPIO_E_6
#define ES_USART0_CK_PIN ES_PIN_GPIO_E_6
#endif
#endif

#ifndef ES_USART0_CK_GPIO_FUNC
#define ES_USART0_CK_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_USART0_CK_GPIO_PORT
#define ES_USART0_CK_GPIO_PORT GPIOE
#endif
#ifndef ES_USART0_CK_GPIO_PIN
#define ES_USART0_CK_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_USART0_CK_PIN
#ifdef ES_PIN_GPIO_E_7
#define ES_USART0_CK_PIN ES_PIN_GPIO_E_7
#endif
#endif

#ifndef ES_USART1_CK_GPIO_FUNC
#define ES_USART1_CK_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_USART1_CK_GPIO_PORT
#define ES_USART1_CK_GPIO_PORT GPIOA
#endif
#ifndef ES_USART1_CK_GPIO_PIN
#define ES_USART1_CK_GPIO_PIN GPIO_PIN_4
#endif

#ifndef ES_USART1_CK_PIN
#ifdef ES_PIN_GPIO_A_4
#define ES_USART1_CK_PIN ES_PIN_GPIO_A_4
#endif
#endif

#ifndef ES_USART1_CK_GPIO_FUNC
#define ES_USART1_CK_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_USART1_CK_GPIO_PORT
#define ES_USART1_CK_GPIO_PORT GPIOD
#endif
#ifndef ES_USART1_CK_GPIO_PIN
#define ES_USART1_CK_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_USART1_CK_PIN
#ifdef ES_PIN_GPIO_D_7
#define ES_USART1_CK_PIN ES_PIN_GPIO_D_7
#endif
#endif

#ifndef ES_USART1_CK_GPIO_FUNC
#define ES_USART1_CK_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_USART1_CK_GPIO_PORT
#define ES_USART1_CK_GPIO_PORT GPIOE
#endif
#ifndef ES_USART1_CK_GPIO_PIN
#define ES_USART1_CK_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_USART1_CK_PIN
#ifdef ES_PIN_GPIO_E_0
#define ES_USART1_CK_PIN ES_PIN_GPIO_E_0
#endif
#endif


/* I2C_SCL */


#ifndef ES_I2C0_SCL_GPIO_FUNC
#define ES_I2C0_SCL_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_I2C0_SCL_GPIO_PORT
#define ES_I2C0_SCL_GPIO_PORT GPIOB
#endif
#ifndef ES_I2C0_SCL_GPIO_PIN
#define ES_I2C0_SCL_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_I2C0_SCL_PIN
#ifdef ES_PIN_GPIO_B_6
#define ES_I2C0_SCL_PIN ES_PIN_GPIO_B_6
#endif
#endif

#ifndef ES_I2C0_SCL_GPIO_FUNC
#define ES_I2C0_SCL_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_I2C0_SCL_GPIO_PORT
#define ES_I2C0_SCL_GPIO_PORT GPIOB
#endif
#ifndef ES_I2C0_SCL_GPIO_PIN
#define ES_I2C0_SCL_GPIO_PIN GPIO_PIN_8
#endif

#ifndef ES_I2C0_SCL_PIN
#ifdef ES_PIN_GPIO_B_8
#define ES_I2C0_SCL_PIN ES_PIN_GPIO_B_8
#endif
#endif

#ifndef ES_I2C1_SCL_GPIO_FUNC
#define ES_I2C1_SCL_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_I2C1_SCL_GPIO_PORT
#define ES_I2C1_SCL_GPIO_PORT GPIOA
#endif
#ifndef ES_I2C1_SCL_GPIO_PIN
#define ES_I2C1_SCL_GPIO_PIN GPIO_PIN_5
#endif

#ifndef ES_I2C1_SCL_PIN
#ifdef ES_PIN_GPIO_A_5
#define ES_I2C1_SCL_PIN ES_PIN_GPIO_A_5
#endif
#endif

#ifndef ES_I2C1_SCL_GPIO_FUNC
#define ES_I2C1_SCL_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_I2C1_SCL_GPIO_PORT
#define ES_I2C1_SCL_GPIO_PORT GPIOB
#endif
#ifndef ES_I2C1_SCL_GPIO_PIN
#define ES_I2C1_SCL_GPIO_PIN GPIO_PIN_10
#endif

#ifndef ES_I2C1_SCL_PIN
#ifdef ES_PIN_GPIO_B_10
#define ES_I2C1_SCL_PIN ES_PIN_GPIO_B_10
#endif
#endif

#ifndef ES_I2C1_SCL_GPIO_FUNC
#define ES_I2C1_SCL_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_I2C1_SCL_GPIO_PORT
#define ES_I2C1_SCL_GPIO_PORT GPIOH
#endif
#ifndef ES_I2C1_SCL_GPIO_PIN
#define ES_I2C1_SCL_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_I2C1_SCL_PIN
#ifdef ES_PIN_GPIO_H_0
#define ES_I2C1_SCL_PIN ES_PIN_GPIO_H_0
#endif
#endif


/* I2C_SDA */


#ifndef ES_I2C0_SDA_GPIO_FUNC
#define ES_I2C0_SDA_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_I2C0_SDA_GPIO_PORT
#define ES_I2C0_SDA_GPIO_PORT GPIOB
#endif
#ifndef ES_I2C0_SDA_GPIO_PIN
#define ES_I2C0_SDA_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_I2C0_SDA_PIN
#ifdef ES_PIN_GPIO_B_7
#define ES_I2C0_SDA_PIN ES_PIN_GPIO_B_7
#endif
#endif

#ifndef ES_I2C0_SDA_GPIO_FUNC
#define ES_I2C0_SDA_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_I2C0_SDA_GPIO_PORT
#define ES_I2C0_SDA_GPIO_PORT GPIOB
#endif
#ifndef ES_I2C0_SDA_GPIO_PIN
#define ES_I2C0_SDA_GPIO_PIN GPIO_PIN_9
#endif

#ifndef ES_I2C0_SDA_PIN
#ifdef ES_PIN_GPIO_B_9
#define ES_I2C0_SDA_PIN ES_PIN_GPIO_B_9
#endif
#endif

#ifndef ES_I2C1_SDA_GPIO_FUNC
#define ES_I2C1_SDA_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_I2C1_SDA_GPIO_PORT
#define ES_I2C1_SDA_GPIO_PORT GPIOA
#endif
#ifndef ES_I2C1_SDA_GPIO_PIN
#define ES_I2C1_SDA_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_I2C1_SDA_PIN
#ifdef ES_PIN_GPIO_A_6
#define ES_I2C1_SDA_PIN ES_PIN_GPIO_A_6
#endif
#endif

#ifndef ES_I2C1_SDA_GPIO_FUNC
#define ES_I2C1_SDA_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_I2C1_SDA_GPIO_PORT
#define ES_I2C1_SDA_GPIO_PORT GPIOH
#endif
#ifndef ES_I2C1_SDA_GPIO_PIN
#define ES_I2C1_SDA_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_I2C1_SDA_PIN
#ifdef ES_PIN_GPIO_H_1
#define ES_I2C1_SDA_PIN ES_PIN_GPIO_H_1
#endif
#endif

#ifndef ES_I2C1_SDA_GPIO_FUNC
#define ES_I2C1_SDA_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_I2C1_SDA_GPIO_PORT
#define ES_I2C1_SDA_GPIO_PORT GPIOB
#endif
#ifndef ES_I2C1_SDA_GPIO_PIN
#define ES_I2C1_SDA_GPIO_PIN GPIO_PIN_11
#endif

#ifndef ES_I2C1_SDA_PIN
#ifdef ES_PIN_GPIO_B_11
#define ES_I2C1_SDA_PIN ES_PIN_GPIO_B_11
#endif
#endif


/* SPI_MISO */


#ifndef ES_SPI0_MISO_GPIO_FUNC
#define ES_SPI0_MISO_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI0_MISO_GPIO_PORT
#define ES_SPI0_MISO_GPIO_PORT GPIOB
#endif
#ifndef ES_SPI0_MISO_GPIO_PIN
#define ES_SPI0_MISO_GPIO_PIN GPIO_PIN_4
#endif

#ifndef ES_SPI0_MISO_PIN
#ifdef ES_PIN_GPIO_B_4
#define ES_SPI0_MISO_PIN ES_PIN_GPIO_B_4
#endif
#endif

#ifndef ES_SPI0_MISO_GPIO_FUNC
#define ES_SPI0_MISO_GPIO_FUNC GPIO_FUNC_6
#endif
#ifndef ES_SPI0_MISO_GPIO_PORT
#define ES_SPI0_MISO_GPIO_PORT GPIOA
#endif
#ifndef ES_SPI0_MISO_GPIO_PIN
#define ES_SPI0_MISO_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_SPI0_MISO_PIN
#ifdef ES_PIN_GPIO_A_6
#define ES_SPI0_MISO_PIN ES_PIN_GPIO_A_6
#endif
#endif

#ifndef ES_SPI0_MISO_GPIO_FUNC
#define ES_SPI0_MISO_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI0_MISO_GPIO_PORT
#define ES_SPI0_MISO_GPIO_PORT GPIOD
#endif
#ifndef ES_SPI0_MISO_GPIO_PIN
#define ES_SPI0_MISO_GPIO_PIN GPIO_PIN_4
#endif

#ifndef ES_SPI0_MISO_PIN
#ifdef ES_PIN_GPIO_D_4
#define ES_SPI0_MISO_PIN ES_PIN_GPIO_D_4
#endif
#endif

#ifndef ES_SPI1_MISO_GPIO_FUNC
#define ES_SPI1_MISO_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI1_MISO_GPIO_PORT
#define ES_SPI1_MISO_GPIO_PORT GPIOC
#endif
#ifndef ES_SPI1_MISO_GPIO_PIN
#define ES_SPI1_MISO_GPIO_PIN GPIO_PIN_2
#endif

#ifndef ES_SPI1_MISO_PIN
#ifdef ES_PIN_GPIO_C_2
#define ES_SPI1_MISO_PIN ES_PIN_GPIO_C_2
#endif
#endif

#ifndef ES_SPI1_MISO_GPIO_FUNC
#define ES_SPI1_MISO_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI1_MISO_GPIO_PORT
#define ES_SPI1_MISO_GPIO_PORT GPIOB
#endif
#ifndef ES_SPI1_MISO_GPIO_PIN
#define ES_SPI1_MISO_GPIO_PIN GPIO_PIN_14
#endif

#ifndef ES_SPI1_MISO_PIN
#ifdef ES_PIN_GPIO_B_14
#define ES_SPI1_MISO_PIN ES_PIN_GPIO_B_14
#endif
#endif


/* SPI_MOSI */


#ifndef ES_SPI0_MOSI_GPIO_FUNC
#define ES_SPI0_MOSI_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI0_MOSI_GPIO_PORT
#define ES_SPI0_MOSI_GPIO_PORT GPIOB
#endif
#ifndef ES_SPI0_MOSI_GPIO_PIN
#define ES_SPI0_MOSI_GPIO_PIN GPIO_PIN_5
#endif

#ifndef ES_SPI0_MOSI_PIN
#ifdef ES_PIN_GPIO_B_5
#define ES_SPI0_MOSI_PIN ES_PIN_GPIO_B_5
#endif
#endif

#ifndef ES_SPI0_MOSI_GPIO_FUNC
#define ES_SPI0_MOSI_GPIO_FUNC GPIO_FUNC_6
#endif
#ifndef ES_SPI0_MOSI_GPIO_PORT
#define ES_SPI0_MOSI_GPIO_PORT GPIOA
#endif
#ifndef ES_SPI0_MOSI_GPIO_PIN
#define ES_SPI0_MOSI_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_SPI0_MOSI_PIN
#ifdef ES_PIN_GPIO_A_7
#define ES_SPI0_MOSI_PIN ES_PIN_GPIO_A_7
#endif
#endif


#ifndef ES_SPI0_MOSI_GPIO_FUNC
#define ES_SPI0_MOSI_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI0_MOSI_GPIO_PORT
#define ES_SPI0_MOSI_GPIO_PORT GPIOD
#endif
#ifndef ES_SPI0_MOSI_GPIO_PIN
#define ES_SPI0_MOSI_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_SPI0_MOSI_PIN
#ifdef ES_PIN_GPIO_D_7
#define ES_SPI0_MOSI_PIN ES_PIN_GPIO_D_7
#endif
#endif

#ifndef ES_SPI1_MOSI_GPIO_FUNC
#define ES_SPI1_MOSI_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI1_MOSI_GPIO_PORT
#define ES_SPI1_MOSI_GPIO_PORT GPIOB
#endif
#ifndef ES_SPI1_MOSI_GPIO_PIN
#define ES_SPI1_MOSI_GPIO_PIN GPIO_PIN_15
#endif

#ifndef ES_SPI1_MOSI_PIN
#ifdef ES_PIN_GPIO_B_15
#define ES_SPI1_MOSI_PIN ES_PIN_GPIO_B_15
#endif
#endif

#ifndef ES_SPI1_MOSI_GPIO_FUNC
#define ES_SPI1_MOSI_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI1_MOSI_GPIO_PORT
#define ES_SPI1_MOSI_GPIO_PORT GPIOC
#endif
#ifndef ES_SPI1_MOSI_GPIO_PIN
#define ES_SPI1_MOSI_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_SPI1_MOSI_PIN
#ifdef ES_PIN_GPIO_C_3
#define ES_SPI1_MOSI_PIN ES_PIN_GPIO_C_3
#endif
#endif


/* SPI_SCK */


#ifndef ES_SPI0_SCK_GPIO_FUNC
#define ES_SPI0_SCK_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI0_SCK_GPIO_PORT
#define ES_SPI0_SCK_GPIO_PORT GPIOB
#endif
#ifndef ES_SPI0_SCK_GPIO_PIN
#define ES_SPI0_SCK_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_SPI0_SCK_PIN
#ifdef ES_PIN_GPIO_B_3
#define ES_SPI0_SCK_PIN ES_PIN_GPIO_B_3
#endif
#endif

#ifndef ES_SPI0_SCK_GPIO_FUNC
#define ES_SPI0_SCK_GPIO_FUNC GPIO_FUNC_6
#endif
#ifndef ES_SPI0_SCK_GPIO_PORT
#define ES_SPI0_SCK_GPIO_PORT GPIOA
#endif
#ifndef ES_SPI0_SCK_GPIO_PIN
#define ES_SPI0_SCK_GPIO_PIN GPIO_PIN_5
#endif

#ifndef ES_SPI0_SCK_PIN
#ifdef ES_PIN_GPIO_A_5
#define ES_SPI0_SCK_PIN ES_PIN_GPIO_A_5
#endif
#endif

#ifndef ES_SPI0_SCK_GPIO_FUNC
#define ES_SPI0_SCK_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI0_SCK_GPIO_PORT
#define ES_SPI0_SCK_GPIO_PORT GPIOD
#endif
#ifndef ES_SPI0_SCK_GPIO_PIN
#define ES_SPI0_SCK_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_SPI0_SCK_PIN
#ifdef ES_PIN_GPIO_D_3
#define ES_SPI0_SCK_PIN ES_PIN_GPIO_D_3
#endif
#endif

#ifndef ES_SPI1_SCK_GPIO_FUNC
#define ES_SPI1_SCK_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI1_SCK_GPIO_PORT
#define ES_SPI1_SCK_GPIO_PORT GPIOB
#endif
#ifndef ES_SPI1_SCK_GPIO_PIN
#define ES_SPI1_SCK_GPIO_PIN GPIO_PIN_13
#endif

#ifndef ES_SPI1_SCK_PIN
#ifdef ES_PIN_GPIO_B_13
#define ES_SPI1_SCK_PIN ES_PIN_GPIO_B_13
#endif
#endif

#ifndef ES_SPI1_SCK_GPIO_FUNC
#define ES_SPI1_SCK_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI1_SCK_GPIO_PORT
#define ES_SPI1_SCK_GPIO_PORT GPIOC
#endif
#ifndef ES_SPI1_SCK_GPIO_PIN
#define ES_SPI1_SCK_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_SPI1_SCK_PIN
#ifdef ES_PIN_GPIO_C_1
#define ES_SPI1_SCK_PIN ES_PIN_GPIO_C_1
#endif
#endif


/* SPI_NSS */


#ifndef ES_SPI0_NSS_GPIO_FUNC
#define ES_SPI0_NSS_GPIO_FUNC GPIO_FUNC_6
#endif
#ifndef ES_SPI0_NSS_GPIO_PORT
#define ES_SPI0_NSS_GPIO_PORT GPIOA
#endif
#ifndef ES_SPI0_NSS_GPIO_PIN
#define ES_SPI0_NSS_GPIO_PIN GPIO_PIN_4
#endif

#ifndef ES_SPI0_NSS_PIN
#ifdef ES_PIN_GPIO_A_4
#define ES_SPI0_NSS_PIN ES_PIN_GPIO_A_4
#endif
#endif

#ifndef ES_SPI0_NSS_GPIO_FUNC
#define ES_SPI0_NSS_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI0_NSS_GPIO_PORT
#define ES_SPI0_NSS_GPIO_PORT GPIOA
#endif
#ifndef ES_SPI0_NSS_GPIO_PIN
#define ES_SPI0_NSS_GPIO_PIN GPIO_PIN_15
#endif

#ifndef ES_SPI0_NSS_PIN
#ifdef ES_PIN_GPIO_A_15
#define ES_SPI0_NSS_PIN ES_PIN_GPIO_A_15
#endif
#endif

#ifndef ES_SPI1_NSS_GPIO_FUNC
#define ES_SPI1_NSS_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI1_NSS_GPIO_PORT
#define ES_SPI1_NSS_GPIO_PORT GPIOC
#endif
#ifndef ES_SPI1_NSS_GPIO_PIN
#define ES_SPI1_NSS_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_SPI1_NSS_PIN
#ifdef ES_PIN_GPIO_C_0
#define ES_SPI1_NSS_PIN ES_PIN_GPIO_C_0
#endif
#endif

#ifndef ES_SPI1_NSS_GPIO_FUNC
#define ES_SPI1_NSS_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_SPI1_NSS_GPIO_PORT
#define ES_SPI1_NSS_GPIO_PORT GPIOB
#endif
#ifndef ES_SPI1_NSS_GPIO_PIN
#define ES_SPI1_NSS_GPIO_PIN GPIO_PIN_12
#endif

#ifndef ES_SPI1_NSS_PIN
#ifdef ES_PIN_GPIO_B_12
#define ES_SPI1_NSS_PIN ES_PIN_GPIO_B_12
#endif
#endif


/* CAN_TX */


#ifndef ES_CAN0_TX_GPIO_FUNC
#define ES_CAN0_TX_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_CAN0_TX_GPIO_PORT
#define ES_CAN0_TX_GPIO_PORT GPIOA
#endif
#ifndef ES_CAN0_TX_GPIO_PIN
#define ES_CAN0_TX_GPIO_PIN GPIO_PIN_12
#endif

#ifndef ES_CAN0_TX_PIN
#ifdef ES_PIN_GPIO_A_12
#define ES_CAN0_TX_PIN ES_PIN_GPIO_A_12
#endif
#endif

#ifndef ES_CAN0_TX_GPIO_FUNC
#define ES_CAN0_TX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_CAN0_TX_GPIO_PORT
#define ES_CAN0_TX_GPIO_PORT GPIOB
#endif
#ifndef ES_CAN0_TX_GPIO_PIN
#define ES_CAN0_TX_GPIO_PIN GPIO_PIN_9
#endif

#ifndef ES_CAN0_TX_PIN
#ifdef ES_PIN_GPIO_B_9
#define ES_CAN0_TX_PIN ES_PIN_GPIO_B_9
#endif
#endif


/* CAN_RX */


#ifndef ES_CAN0_RX_GPIO_FUNC
#define ES_CAN0_RX_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_CAN0_RX_GPIO_PORT
#define ES_CAN0_RX_GPIO_PORT GPIOA
#endif
#ifndef ES_CAN0_RX_GPIO_PIN
#define ES_CAN0_RX_GPIO_PIN GPIO_PIN_11
#endif

#ifndef ES_CAN0_RX_PIN
#ifdef ES_PIN_GPIO_A_11
#define ES_CAN0_RX_PIN ES_PIN_GPIO_A_11
#endif
#endif

#ifndef ES_CAN0_RX_GPIO_FUNC
#define ES_CAN0_RX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_CAN0_RX_GPIO_PORT
#define ES_CAN0_RX_GPIO_PORT GPIOB
#endif
#ifndef ES_CAN0_RX_GPIO_PIN
#define ES_CAN0_RX_GPIO_PIN GPIO_PIN_8
#endif

#ifndef ES_CAN0_RX_PIN
#ifdef ES_PIN_GPIO_B_8
#define ES_CAN0_RX_PIN ES_PIN_GPIO_B_8
#endif
#endif


/* AD16C4T_CH1 */


#ifndef ES_AD16C4T0_CH1_GPIO_FUNC
#define ES_AD16C4T0_CH1_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH1_GPIO_PORT
#define ES_AD16C4T0_CH1_GPIO_PORT GPIOA
#endif
#ifndef ES_AD16C4T0_CH1_GPIO_PIN
#define ES_AD16C4T0_CH1_GPIO_PIN GPIO_PIN_8
#endif

#ifndef ES_AD16C4T0_CH1_PIN
#ifdef ES_PIN_GPIO_A_8
#define ES_AD16C4T0_CH1_PIN ES_PIN_GPIO_A_8
#endif
#endif

#ifndef ES_AD16C4T0_CH1_GPIO_FUNC
#define ES_AD16C4T0_CH1_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH1_GPIO_PORT
#define ES_AD16C4T0_CH1_GPIO_PORT GPIOE
#endif
#ifndef ES_AD16C4T0_CH1_GPIO_PIN
#define ES_AD16C4T0_CH1_GPIO_PIN GPIO_PIN_9
#endif

#ifndef ES_AD16C4T0_CH1_PIN
#ifdef ES_PIN_GPIO_E_9
#define ES_AD16C4T0_CH1_PIN ES_PIN_GPIO_E_9
#endif
#endif


/* AD16C4T_CH2 */


#ifndef ES_AD16C4T0_CH2_GPIO_FUNC
#define ES_AD16C4T0_CH2_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH2_GPIO_PORT
#define ES_AD16C4T0_CH2_GPIO_PORT GPIOA
#endif
#ifndef ES_AD16C4T0_CH2_GPIO_PIN
#define ES_AD16C4T0_CH2_GPIO_PIN GPIO_PIN_9
#endif

#ifndef ES_AD16C4T0_CH2_PIN
#ifdef ES_PIN_GPIO_A_9
#define ES_AD16C4T0_CH2_PIN ES_PIN_GPIO_A_9
#endif
#endif

#ifndef ES_AD16C4T0_CH2_GPIO_FUNC
#define ES_AD16C4T0_CH2_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH2_GPIO_PORT
#define ES_AD16C4T0_CH2_GPIO_PORT GPIOE
#endif
#ifndef ES_AD16C4T0_CH2_GPIO_PIN
#define ES_AD16C4T0_CH2_GPIO_PIN GPIO_PIN_11
#endif

#ifndef ES_AD16C4T0_CH2_PIN
#ifdef ES_PIN_GPIO_E_11
#define ES_AD16C4T0_CH2_PIN ES_PIN_GPIO_E_11
#endif
#endif


/* AD16C4T_CH3 */


#ifndef ES_AD16C4T0_CH3_GPIO_FUNC
#define ES_AD16C4T0_CH3_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH3_GPIO_PORT
#define ES_AD16C4T0_CH3_GPIO_PORT GPIOA
#endif
#ifndef ES_AD16C4T0_CH3_GPIO_PIN
#define ES_AD16C4T0_CH3_GPIO_PIN GPIO_PIN_10
#endif

#ifndef ES_AD16C4T0_CH3_PIN
#ifdef ES_PIN_GPIO_A_10
#define ES_AD16C4T0_CH3_PIN ES_PIN_GPIO_A_10
#endif
#endif

#ifndef ES_AD16C4T0_CH3_GPIO_FUNC
#define ES_AD16C4T0_CH3_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH3_GPIO_PORT
#define ES_AD16C4T0_CH3_GPIO_PORT GPIOE
#endif
#ifndef ES_AD16C4T0_CH3_GPIO_PIN
#define ES_AD16C4T0_CH3_GPIO_PIN GPIO_PIN_13
#endif

#ifndef ES_AD16C4T0_CH3_PIN
#ifdef ES_PIN_GPIO_E_13
#define ES_AD16C4T0_CH3_PIN ES_PIN_GPIO_E_13
#endif
#endif


/* AD16C4T_CH4 */


#ifndef ES_AD16C4T0_CH4_GPIO_FUNC
#define ES_AD16C4T0_CH4_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH4_GPIO_PORT
#define ES_AD16C4T0_CH4_GPIO_PORT GPIOE
#endif
#ifndef ES_AD16C4T0_CH4_GPIO_PIN
#define ES_AD16C4T0_CH4_GPIO_PIN GPIO_PIN_14
#endif

#ifndef ES_AD16C4T0_CH4_PIN
#ifdef ES_PIN_GPIO_E_14
#define ES_AD16C4T0_CH4_PIN ES_PIN_GPIO_E_14
#endif
#endif

#ifndef ES_AD16C4T0_CH4_GPIO_FUNC
#define ES_AD16C4T0_CH4_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH4_GPIO_PORT
#define ES_AD16C4T0_CH4_GPIO_PORT GPIOA
#endif
#ifndef ES_AD16C4T0_CH4_GPIO_PIN
#define ES_AD16C4T0_CH4_GPIO_PIN GPIO_PIN_11
#endif

#ifndef ES_AD16C4T0_CH4_PIN
#ifdef ES_PIN_GPIO_A_11
#define ES_AD16C4T0_CH4_PIN ES_PIN_GPIO_A_11
#endif
#endif


/* AD16C4T_CH1N */


#ifndef ES_AD16C4T0_CH1N_GPIO_FUNC
#define ES_AD16C4T0_CH1N_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_AD16C4T0_CH1N_GPIO_PORT
#define ES_AD16C4T0_CH1N_GPIO_PORT GPIOA
#endif
#ifndef ES_AD16C4T0_CH1N_GPIO_PIN
#define ES_AD16C4T0_CH1N_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_AD16C4T0_CH1N_PIN
#ifdef ES_PIN_GPIO_A_7
#define ES_AD16C4T0_CH1N_PIN ES_PIN_GPIO_A_7
#endif
#endif

#ifndef ES_AD16C4T0_CH1N_GPIO_FUNC
#define ES_AD16C4T0_CH1N_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH1N_GPIO_PORT
#define ES_AD16C4T0_CH1N_GPIO_PORT GPIOB
#endif
#ifndef ES_AD16C4T0_CH1N_GPIO_PIN
#define ES_AD16C4T0_CH1N_GPIO_PIN GPIO_PIN_13
#endif

#ifndef ES_AD16C4T0_CH1N_PIN
#ifdef ES_PIN_GPIO_B_13
#define ES_AD16C4T0_CH1N_PIN ES_PIN_GPIO_B_13
#endif
#endif

#ifndef ES_AD16C4T0_CH1N_GPIO_FUNC
#define ES_AD16C4T0_CH1N_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH1N_GPIO_PORT
#define ES_AD16C4T0_CH1N_GPIO_PORT GPIOE
#endif
#ifndef ES_AD16C4T0_CH1N_GPIO_PIN
#define ES_AD16C4T0_CH1N_GPIO_PIN GPIO_PIN_8
#endif

#ifndef ES_AD16C4T0_CH1N_PIN
#ifdef ES_PIN_GPIO_E_8
#define ES_AD16C4T0_CH1N_PIN ES_PIN_GPIO_E_8
#endif
#endif


/* AD16C4T_CH2N */


#ifndef ES_AD16C4T0_CH2N_GPIO_FUNC
#define ES_AD16C4T0_CH2N_GPIO_FUNC GPIO_FUNC_6
#endif
#ifndef ES_AD16C4T0_CH2N_GPIO_PORT
#define ES_AD16C4T0_CH2N_GPIO_PORT GPIOB
#endif
#ifndef ES_AD16C4T0_CH2N_GPIO_PIN
#define ES_AD16C4T0_CH2N_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_AD16C4T0_CH2N_PIN
#ifdef ES_PIN_GPIO_B_0
#define ES_AD16C4T0_CH2N_PIN ES_PIN_GPIO_B_0
#endif
#endif

#ifndef ES_AD16C4T0_CH2N_GPIO_FUNC
#define ES_AD16C4T0_CH2N_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH2N_GPIO_PORT
#define ES_AD16C4T0_CH2N_GPIO_PORT GPIOB
#endif
#ifndef ES_AD16C4T0_CH2N_GPIO_PIN
#define ES_AD16C4T0_CH2N_GPIO_PIN GPIO_PIN_14
#endif

#ifndef ES_AD16C4T0_CH2N_PIN
#ifdef ES_PIN_GPIO_B_14
#define ES_AD16C4T0_CH2N_PIN ES_PIN_GPIO_B_14
#endif
#endif

#ifndef ES_AD16C4T0_CH2N_GPIO_FUNC
#define ES_AD16C4T0_CH2N_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH2N_GPIO_PORT
#define ES_AD16C4T0_CH2N_GPIO_PORT GPIOE
#endif
#ifndef ES_AD16C4T0_CH2N_GPIO_PIN
#define ES_AD16C4T0_CH2N_GPIO_PIN GPIO_PIN_10
#endif

#ifndef ES_AD16C4T0_CH2N_PIN
#ifdef ES_PIN_GPIO_E_10
#define ES_AD16C4T0_CH2N_PIN ES_PIN_GPIO_E_10
#endif
#endif


/* AD16C4T_CH3N */


#ifndef ES_AD16C4T0_CH3N_GPIO_FUNC
#define ES_AD16C4T0_CH3N_GPIO_FUNC GPIO_FUNC_6
#endif
#ifndef ES_AD16C4T0_CH3N_GPIO_PORT
#define ES_AD16C4T0_CH3N_GPIO_PORT GPIOB
#endif
#ifndef ES_AD16C4T0_CH3N_GPIO_PIN
#define ES_AD16C4T0_CH3N_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_AD16C4T0_CH3N_PIN
#ifdef ES_PIN_GPIO_B_1
#define ES_AD16C4T0_CH3N_PIN ES_PIN_GPIO_B_1
#endif
#endif

#ifndef ES_AD16C4T0_CH3N_GPIO_FUNC
#define ES_AD16C4T0_CH3N_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH3N_GPIO_PORT
#define ES_AD16C4T0_CH3N_GPIO_PORT GPIOB
#endif
#ifndef ES_AD16C4T0_CH3N_GPIO_PIN
#define ES_AD16C4T0_CH3N_GPIO_PIN GPIO_PIN_15
#endif

#ifndef ES_AD16C4T0_CH3N_PIN
#ifdef ES_PIN_GPIO_B_15
#define ES_AD16C4T0_CH3N_PIN ES_PIN_GPIO_B_15
#endif
#endif

#ifndef ES_AD16C4T0_CH3N_GPIO_FUNC
#define ES_AD16C4T0_CH3N_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_CH3N_GPIO_PORT
#define ES_AD16C4T0_CH3N_GPIO_PORT GPIOE
#endif
#ifndef ES_AD16C4T0_CH3N_GPIO_PIN
#define ES_AD16C4T0_CH3N_GPIO_PIN GPIO_PIN_12
#endif

#ifndef ES_AD16C4T0_CH3N_PIN
#ifdef ES_PIN_GPIO_E_12
#define ES_AD16C4T0_CH3N_PIN ES_PIN_GPIO_E_12
#endif
#endif


/* AD16C4T_CH4N */



/* AD16C4T_ET */


#ifndef ES_AD16C4T0_ET_GPIO_FUNC
#define ES_AD16C4T0_ET_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_ET_GPIO_PORT
#define ES_AD16C4T0_ET_GPIO_PORT GPIOA
#endif
#ifndef ES_AD16C4T0_ET_GPIO_PIN
#define ES_AD16C4T0_ET_GPIO_PIN GPIO_PIN_12
#endif

#ifndef ES_AD16C4T0_ET_PIN
#ifdef ES_PIN_GPIO_A_12
#define ES_AD16C4T0_ET_PIN ES_PIN_GPIO_A_12
#endif
#endif

#ifndef ES_AD16C4T0_ET_GPIO_FUNC
#define ES_AD16C4T0_ET_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T0_ET_GPIO_PORT
#define ES_AD16C4T0_ET_GPIO_PORT GPIOE
#endif
#ifndef ES_AD16C4T0_ET_GPIO_PIN
#define ES_AD16C4T0_ET_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_AD16C4T0_ET_PIN
#ifdef ES_PIN_GPIO_E_7
#define ES_AD16C4T0_ET_PIN ES_PIN_GPIO_E_7
#endif
#endif


/* GP32C4T_CH1 */



/* GP32C4T_CH2 */



/* GP32C4T_CH3 */



/* GP32C4T_CH4 */



/* GP32C4T_ET */



/* GP16C4T_CH1 */


#ifndef ES_GP16C4T0_CH1_GPIO_FUNC
#define ES_GP16C4T0_CH1_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C4T0_CH1_GPIO_PORT
#define ES_GP16C4T0_CH1_GPIO_PORT GPIOB
#endif
#ifndef ES_GP16C4T0_CH1_GPIO_PIN
#define ES_GP16C4T0_CH1_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_GP16C4T0_CH1_PIN
#ifdef ES_PIN_GPIO_B_6
#define ES_GP16C4T0_CH1_PIN ES_PIN_GPIO_B_6
#endif
#endif

#ifndef ES_GP16C4T0_CH1_GPIO_FUNC
#define ES_GP16C4T0_CH1_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C4T0_CH1_GPIO_PORT
#define ES_GP16C4T0_CH1_GPIO_PORT GPIOD
#endif
#ifndef ES_GP16C4T0_CH1_GPIO_PIN
#define ES_GP16C4T0_CH1_GPIO_PIN GPIO_PIN_12
#endif

#ifndef ES_GP16C4T0_CH1_PIN
#ifdef ES_PIN_GPIO_D_12
#define ES_GP16C4T0_CH1_PIN ES_PIN_GPIO_D_12
#endif
#endif


/* GP16C4T_CH2 */


#ifndef ES_GP16C4T0_CH2_GPIO_FUNC
#define ES_GP16C4T0_CH2_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C4T0_CH2_GPIO_PORT
#define ES_GP16C4T0_CH2_GPIO_PORT GPIOB
#endif
#ifndef ES_GP16C4T0_CH2_GPIO_PIN
#define ES_GP16C4T0_CH2_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_GP16C4T0_CH2_PIN
#ifdef ES_PIN_GPIO_B_7
#define ES_GP16C4T0_CH2_PIN ES_PIN_GPIO_B_7
#endif
#endif

#ifndef ES_GP16C4T0_CH2_GPIO_FUNC
#define ES_GP16C4T0_CH2_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C4T0_CH2_GPIO_PORT
#define ES_GP16C4T0_CH2_GPIO_PORT GPIOD
#endif
#ifndef ES_GP16C4T0_CH2_GPIO_PIN
#define ES_GP16C4T0_CH2_GPIO_PIN GPIO_PIN_13
#endif

#ifndef ES_GP16C4T0_CH2_PIN
#ifdef ES_PIN_GPIO_D_13
#define ES_GP16C4T0_CH2_PIN ES_PIN_GPIO_D_13
#endif
#endif


/* GP16C4T_CH3 */


#ifndef ES_GP16C4T0_CH3_GPIO_FUNC
#define ES_GP16C4T0_CH3_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C4T0_CH3_GPIO_PORT
#define ES_GP16C4T0_CH3_GPIO_PORT GPIOD
#endif
#ifndef ES_GP16C4T0_CH3_GPIO_PIN
#define ES_GP16C4T0_CH3_GPIO_PIN GPIO_PIN_14
#endif

#ifndef ES_GP16C4T0_CH3_PIN
#ifdef ES_PIN_GPIO_D_14
#define ES_GP16C4T0_CH3_PIN ES_PIN_GPIO_D_14
#endif
#endif

#ifndef ES_GP16C4T0_CH3_GPIO_FUNC
#define ES_GP16C4T0_CH3_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C4T0_CH3_GPIO_PORT
#define ES_GP16C4T0_CH3_GPIO_PORT GPIOB
#endif
#ifndef ES_GP16C4T0_CH3_GPIO_PIN
#define ES_GP16C4T0_CH3_GPIO_PIN GPIO_PIN_8
#endif

#ifndef ES_GP16C4T0_CH3_PIN
#ifdef ES_PIN_GPIO_B_8
#define ES_GP16C4T0_CH3_PIN ES_PIN_GPIO_B_8
#endif
#endif


/* GP16C4T_CH4 */


#ifndef ES_GP16C4T0_CH4_GPIO_FUNC
#define ES_GP16C4T0_CH4_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C4T0_CH4_GPIO_PORT
#define ES_GP16C4T0_CH4_GPIO_PORT GPIOB
#endif
#ifndef ES_GP16C4T0_CH4_GPIO_PIN
#define ES_GP16C4T0_CH4_GPIO_PIN GPIO_PIN_9
#endif

#ifndef ES_GP16C4T0_CH4_PIN
#ifdef ES_PIN_GPIO_B_9
#define ES_GP16C4T0_CH4_PIN ES_PIN_GPIO_B_9
#endif
#endif

#ifndef ES_GP16C4T0_CH4_GPIO_FUNC
#define ES_GP16C4T0_CH4_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C4T0_CH4_GPIO_PORT
#define ES_GP16C4T0_CH4_GPIO_PORT GPIOD
#endif
#ifndef ES_GP16C4T0_CH4_GPIO_PIN
#define ES_GP16C4T0_CH4_GPIO_PIN GPIO_PIN_15
#endif

#ifndef ES_GP16C4T0_CH4_PIN
#ifdef ES_PIN_GPIO_D_15
#define ES_GP16C4T0_CH4_PIN ES_PIN_GPIO_D_15
#endif
#endif


/* GP16C4T_ET */


#ifndef ES_GP16C4T0_ET_GPIO_FUNC
#define ES_GP16C4T0_ET_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C4T0_ET_GPIO_PORT
#define ES_GP16C4T0_ET_GPIO_PORT GPIOE
#endif
#ifndef ES_GP16C4T0_ET_GPIO_PIN
#define ES_GP16C4T0_ET_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_GP16C4T0_ET_PIN
#ifdef ES_PIN_GPIO_E_0
#define ES_GP16C4T0_ET_PIN ES_PIN_GPIO_E_0
#endif
#endif


/* GP16C2T_CH1 */


#ifndef ES_GP16C2T0_CH1_GPIO_FUNC
#define ES_GP16C2T0_CH1_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C2T0_CH1_GPIO_PORT
#define ES_GP16C2T0_CH1_GPIO_PORT GPIOA
#endif
#ifndef ES_GP16C2T0_CH1_GPIO_PIN
#define ES_GP16C2T0_CH1_GPIO_PIN GPIO_PIN_15
#endif

#ifndef ES_GP16C2T0_CH1_PIN
#ifdef ES_PIN_GPIO_A_15
#define ES_GP16C2T0_CH1_PIN ES_PIN_GPIO_A_15
#endif
#endif

#ifndef ES_GP16C2T0_CH1_GPIO_FUNC
#define ES_GP16C2T0_CH1_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C2T0_CH1_GPIO_PORT
#define ES_GP16C2T0_CH1_GPIO_PORT GPIOA
#endif
#ifndef ES_GP16C2T0_CH1_GPIO_PIN
#define ES_GP16C2T0_CH1_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_GP16C2T0_CH1_PIN
#ifdef ES_PIN_GPIO_A_0
#define ES_GP16C2T0_CH1_PIN ES_PIN_GPIO_A_0
#endif
#endif

#ifndef ES_GP16C2T1_CH1_GPIO_FUNC
#define ES_GP16C2T1_CH1_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_GP16C2T1_CH1_GPIO_PORT
#define ES_GP16C2T1_CH1_GPIO_PORT GPIOA
#endif
#ifndef ES_GP16C2T1_CH1_GPIO_PIN
#define ES_GP16C2T1_CH1_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_GP16C2T1_CH1_PIN
#ifdef ES_PIN_GPIO_A_6
#define ES_GP16C2T1_CH1_PIN ES_PIN_GPIO_A_6
#endif
#endif

#ifndef ES_GP16C2T1_CH1_GPIO_FUNC
#define ES_GP16C2T1_CH1_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_GP16C2T1_CH1_GPIO_PORT
#define ES_GP16C2T1_CH1_GPIO_PORT GPIOC
#endif
#ifndef ES_GP16C2T1_CH1_GPIO_PIN
#define ES_GP16C2T1_CH1_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_GP16C2T1_CH1_PIN
#ifdef ES_PIN_GPIO_C_6
#define ES_GP16C2T1_CH1_PIN ES_PIN_GPIO_C_6
#endif
#endif

#ifndef ES_GP16C2T1_CH1_GPIO_FUNC
#define ES_GP16C2T1_CH1_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C2T1_CH1_GPIO_PORT
#define ES_GP16C2T1_CH1_GPIO_PORT GPIOB
#endif
#ifndef ES_GP16C2T1_CH1_GPIO_PIN
#define ES_GP16C2T1_CH1_GPIO_PIN GPIO_PIN_4
#endif

#ifndef ES_GP16C2T1_CH1_PIN
#ifdef ES_PIN_GPIO_B_4
#define ES_GP16C2T1_CH1_PIN ES_PIN_GPIO_B_4
#endif
#endif


/* GP16C2T_CH2 */


#ifndef ES_GP16C2T0_CH2_GPIO_FUNC
#define ES_GP16C2T0_CH2_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C2T0_CH2_GPIO_PORT
#define ES_GP16C2T0_CH2_GPIO_PORT GPIOA
#endif
#ifndef ES_GP16C2T0_CH2_GPIO_PIN
#define ES_GP16C2T0_CH2_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_GP16C2T0_CH2_PIN
#ifdef ES_PIN_GPIO_A_1
#define ES_GP16C2T0_CH2_PIN ES_PIN_GPIO_A_1
#endif
#endif

#ifndef ES_GP16C2T0_CH2_GPIO_FUNC
#define ES_GP16C2T0_CH2_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C2T0_CH2_GPIO_PORT
#define ES_GP16C2T0_CH2_GPIO_PORT GPIOB
#endif
#ifndef ES_GP16C2T0_CH2_GPIO_PIN
#define ES_GP16C2T0_CH2_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_GP16C2T0_CH2_PIN
#ifdef ES_PIN_GPIO_B_3
#define ES_GP16C2T0_CH2_PIN ES_PIN_GPIO_B_3
#endif
#endif

#ifndef ES_GP16C2T1_CH2_GPIO_FUNC
#define ES_GP16C2T1_CH2_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_GP16C2T1_CH2_GPIO_PORT
#define ES_GP16C2T1_CH2_GPIO_PORT GPIOA
#endif
#ifndef ES_GP16C2T1_CH2_GPIO_PIN
#define ES_GP16C2T1_CH2_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_GP16C2T1_CH2_PIN
#ifdef ES_PIN_GPIO_A_7
#define ES_GP16C2T1_CH2_PIN ES_PIN_GPIO_A_7
#endif
#endif

#ifndef ES_GP16C2T1_CH2_GPIO_FUNC
#define ES_GP16C2T1_CH2_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_GP16C2T1_CH2_GPIO_PORT
#define ES_GP16C2T1_CH2_GPIO_PORT GPIOC
#endif
#ifndef ES_GP16C2T1_CH2_GPIO_PIN
#define ES_GP16C2T1_CH2_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_GP16C2T1_CH2_PIN
#ifdef ES_PIN_GPIO_C_7
#define ES_GP16C2T1_CH2_PIN ES_PIN_GPIO_C_7
#endif
#endif

#ifndef ES_GP16C2T1_CH2_GPIO_FUNC
#define ES_GP16C2T1_CH2_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C2T1_CH2_GPIO_PORT
#define ES_GP16C2T1_CH2_GPIO_PORT GPIOB
#endif
#ifndef ES_GP16C2T1_CH2_GPIO_PIN
#define ES_GP16C2T1_CH2_GPIO_PIN GPIO_PIN_5
#endif

#ifndef ES_GP16C2T1_CH2_PIN
#ifdef ES_PIN_GPIO_B_5
#define ES_GP16C2T1_CH2_PIN ES_PIN_GPIO_B_5
#endif
#endif


/* GP16C2T_CH1N */


#ifndef ES_GP16C2T0_CH1N_GPIO_FUNC
#define ES_GP16C2T0_CH1N_GPIO_FUNC GPIO_FUNC_6
#endif
#ifndef ES_GP16C2T0_CH1N_GPIO_PORT
#define ES_GP16C2T0_CH1N_GPIO_PORT GPIOA
#endif
#ifndef ES_GP16C2T0_CH1N_GPIO_PIN
#define ES_GP16C2T0_CH1N_GPIO_PIN GPIO_PIN_2
#endif

#ifndef ES_GP16C2T0_CH1N_PIN
#ifdef ES_PIN_GPIO_A_2
#define ES_GP16C2T0_CH1N_PIN ES_PIN_GPIO_A_2
#endif
#endif

#ifndef ES_GP16C2T0_CH1N_GPIO_FUNC
#define ES_GP16C2T0_CH1N_GPIO_FUNC GPIO_FUNC_6
#endif
#ifndef ES_GP16C2T0_CH1N_GPIO_PORT
#define ES_GP16C2T0_CH1N_GPIO_PORT GPIOC
#endif
#ifndef ES_GP16C2T0_CH1N_GPIO_PIN
#define ES_GP16C2T0_CH1N_GPIO_PIN GPIO_PIN_10
#endif

#ifndef ES_GP16C2T0_CH1N_PIN
#ifdef ES_PIN_GPIO_C_10
#define ES_GP16C2T0_CH1N_PIN ES_PIN_GPIO_C_10
#endif
#endif

#ifndef ES_GP16C2T1_CH1N_GPIO_FUNC
#define ES_GP16C2T1_CH1N_GPIO_FUNC GPIO_FUNC_6
#endif
#ifndef ES_GP16C2T1_CH1N_GPIO_PORT
#define ES_GP16C2T1_CH1N_GPIO_PORT GPIOC
#endif
#ifndef ES_GP16C2T1_CH1N_GPIO_PIN
#define ES_GP16C2T1_CH1N_GPIO_PIN GPIO_PIN_4
#endif

#ifndef ES_GP16C2T1_CH1N_PIN
#ifdef ES_PIN_GPIO_C_4
#define ES_GP16C2T1_CH1N_PIN ES_PIN_GPIO_C_4
#endif
#endif

#ifndef ES_GP16C2T1_CH1N_GPIO_FUNC
#define ES_GP16C2T1_CH1N_GPIO_FUNC GPIO_FUNC_6
#endif
#ifndef ES_GP16C2T1_CH1N_GPIO_PORT
#define ES_GP16C2T1_CH1N_GPIO_PORT GPIOB
#endif
#ifndef ES_GP16C2T1_CH1N_GPIO_PIN
#define ES_GP16C2T1_CH1N_GPIO_PIN GPIO_PIN_8
#endif

#ifndef ES_GP16C2T1_CH1N_PIN
#ifdef ES_PIN_GPIO_B_8
#define ES_GP16C2T1_CH1N_PIN ES_PIN_GPIO_B_8
#endif
#endif


/* GP16C2T_CH2N */



#define   ES_RTT_APP_LED_PIN   ES_PIN_GPIO_C_8

#endif
