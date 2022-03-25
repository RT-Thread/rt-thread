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



static const struct pin_index pins[] =
{
    __ES_PIN_DEFAULT,
    __ES_PIN(1,E,2),
    __ES_PIN(2,E,3),
    __ES_PIN(3,E,4),
    __ES_PIN(4,E,5),
    __ES_PIN(5,E,6),
    __ES_PIN_DEFAULT,
    __ES_PIN(7,C,13),
    __ES_PIN(8,C,14),
    __ES_PIN(9,C,15),
    __ES_PIN_DEFAULT,
    __ES_PIN(11,F,4),
    __ES_PIN(12,H,0),
    __ES_PIN(13,H,1),
    __ES_PIN_DEFAULT,
    __ES_PIN(15,C,0),
    __ES_PIN(16,C,1),
    __ES_PIN(17,C,2),
    __ES_PIN(18,C,3),
    __ES_PIN(19,F,6),
    __ES_PIN(20,H,3),
    __ES_PIN(21,H,4),
    __ES_PIN(22,F,7),
    __ES_PIN(23,A,0),
    __ES_PIN(24,A,1),
    __ES_PIN(25,A,2),
    __ES_PIN(26,A,3),
    __ES_PIN(27,F,0),
    __ES_PIN(28,F,1),
    __ES_PIN(29,A,4),
    __ES_PIN(30,A,5),
    __ES_PIN(31,A,6),
    __ES_PIN(32,A,7),
    __ES_PIN(33,C,4),
    __ES_PIN(34,C,5),
    __ES_PIN(35,B,0),
    __ES_PIN(36,B,1),
    __ES_PIN(37,B,2),
    __ES_PIN(38,E,7),
    __ES_PIN(39,E,8),
    __ES_PIN(40,E,9),
    __ES_PIN(41,E,10),
    __ES_PIN(42,E,11),
    __ES_PIN(43,E,12),
    __ES_PIN(44,E,13),
    __ES_PIN(45,E,14),
    __ES_PIN(46,E,15),
    __ES_PIN(47,B,10),
    __ES_PIN(48,B,11),
    __ES_PIN_DEFAULT,
    __ES_PIN_DEFAULT,
    __ES_PIN(51,B,12),
    __ES_PIN(52,B,13),
    __ES_PIN(53,B,14),
    __ES_PIN(54,B,15),
    __ES_PIN(55,D,8),
    __ES_PIN(56,D,9),
    __ES_PIN(57,D,10),
    __ES_PIN(58,D,11),
    __ES_PIN(59,D,12),
    __ES_PIN(60,D,13),
    __ES_PIN(61,D,14),
    __ES_PIN(62,D,15),
    __ES_PIN(63,C,6),
    __ES_PIN(64,C,7),
    __ES_PIN(65,C,8),
    __ES_PIN(66,C,9),
    __ES_PIN(67,A,8),
    __ES_PIN(68,A,9),
    __ES_PIN(69,A,10),
    __ES_PIN(70,A,11),
    __ES_PIN(71,A,12),
    __ES_PIN(72,A,13),
    __ES_PIN_DEFAULT,
    __ES_PIN_DEFAULT,
    __ES_PIN_DEFAULT,
    __ES_PIN(76,A,14),
    __ES_PIN(77,A,15),
    __ES_PIN(78,C,10),
    __ES_PIN(79,C,11),
    __ES_PIN(80,C,12),
    __ES_PIN(81,D,0),
    __ES_PIN(82,D,1),
    __ES_PIN(83,D,2),
    __ES_PIN(84,D,3),
    __ES_PIN(85,D,4),
    __ES_PIN(86,D,5),
    __ES_PIN(87,D,6),
    __ES_PIN(88,D,7),
    __ES_PIN(89,B,3),
    __ES_PIN(90,B,4),
    __ES_PIN(91,B,5),
    __ES_PIN(92,B,6),
    __ES_PIN(93,B,7),
    __ES_PIN(94,H,2),
    __ES_PIN(95,B,8),
    __ES_PIN(96,B,9),
    __ES_PIN(97,E,0),
    __ES_PIN(98,E,1),
    __ES_PIN_DEFAULT,
    __ES_PIN_DEFAULT,
};



#define   ES_PIN_GPIO_E_2   1
#define   ES_PIN_GPIO_E_3   2
#define   ES_PIN_GPIO_E_4   3
#define   ES_PIN_GPIO_E_5   4
#define   ES_PIN_GPIO_E_6   5
#define   ES_PIN_GPIO_C_13   7
#define   ES_PIN_GPIO_C_14   8
#define   ES_PIN_GPIO_C_15   9
#define   ES_PIN_GPIO_F_4   11
#define   ES_PIN_GPIO_H_0   12
#define   ES_PIN_GPIO_H_1   13
#define   ES_PIN_GPIO_C_0   15
#define   ES_PIN_GPIO_C_1   16
#define   ES_PIN_GPIO_C_2   17
#define   ES_PIN_GPIO_C_3   18
#define   ES_PIN_GPIO_F_6   19
#define   ES_PIN_GPIO_H_3   20
#define   ES_PIN_GPIO_H_4   21
#define   ES_PIN_GPIO_F_7   22
#define   ES_PIN_GPIO_A_0   23
#define   ES_PIN_GPIO_A_1   24
#define   ES_PIN_GPIO_A_2   25
#define   ES_PIN_GPIO_A_3   26
#define   ES_PIN_GPIO_F_0   27
#define   ES_PIN_GPIO_F_1   28
#define   ES_PIN_GPIO_A_4   29
#define   ES_PIN_GPIO_A_5   30
#define   ES_PIN_GPIO_A_6   31
#define   ES_PIN_GPIO_A_7   32
#define   ES_PIN_GPIO_C_4   33
#define   ES_PIN_GPIO_C_5   34
#define   ES_PIN_GPIO_B_0   35
#define   ES_PIN_GPIO_B_1   36
#define   ES_PIN_GPIO_B_2   37
#define   ES_PIN_GPIO_E_7   38
#define   ES_PIN_GPIO_E_8   39
#define   ES_PIN_GPIO_E_9   40
#define   ES_PIN_GPIO_E_10   41
#define   ES_PIN_GPIO_E_11   42
#define   ES_PIN_GPIO_E_12   43
#define   ES_PIN_GPIO_E_13   44
#define   ES_PIN_GPIO_E_14   45
#define   ES_PIN_GPIO_E_15   46
#define   ES_PIN_GPIO_B_10   47
#define   ES_PIN_GPIO_B_11   48
#define   ES_PIN_GPIO_B_12   51
#define   ES_PIN_GPIO_B_13   52
#define   ES_PIN_GPIO_B_14   53
#define   ES_PIN_GPIO_B_15   54
#define   ES_PIN_GPIO_D_8   55
#define   ES_PIN_GPIO_D_9   56
#define   ES_PIN_GPIO_D_10   57
#define   ES_PIN_GPIO_D_11   58
#define   ES_PIN_GPIO_D_12   59
#define   ES_PIN_GPIO_D_13   60
#define   ES_PIN_GPIO_D_14   61
#define   ES_PIN_GPIO_D_15   62
#define   ES_PIN_GPIO_C_6   63
#define   ES_PIN_GPIO_C_7   64
#define   ES_PIN_GPIO_C_8   65
#define   ES_PIN_GPIO_C_9   66
#define   ES_PIN_GPIO_A_8   67
#define   ES_PIN_GPIO_A_9   68
#define   ES_PIN_GPIO_A_10   69
#define   ES_PIN_GPIO_A_11   70
#define   ES_PIN_GPIO_A_12   71
#define   ES_PIN_GPIO_A_13   72
#define   ES_PIN_GPIO_A_14   76
#define   ES_PIN_GPIO_A_15   77
#define   ES_PIN_GPIO_C_10   78
#define   ES_PIN_GPIO_C_11   79
#define   ES_PIN_GPIO_C_12   80
#define   ES_PIN_GPIO_D_0   81
#define   ES_PIN_GPIO_D_1   82
#define   ES_PIN_GPIO_D_2   83
#define   ES_PIN_GPIO_D_3   84
#define   ES_PIN_GPIO_D_4   85
#define   ES_PIN_GPIO_D_5   86
#define   ES_PIN_GPIO_D_6   87
#define   ES_PIN_GPIO_D_7   88
#define   ES_PIN_GPIO_B_3   89
#define   ES_PIN_GPIO_B_4   90
#define   ES_PIN_GPIO_B_5   91
#define   ES_PIN_GPIO_B_6   92
#define   ES_PIN_GPIO_B_7   93
#define   ES_PIN_GPIO_H_2   94
#define   ES_PIN_GPIO_B_8   95
#define   ES_PIN_GPIO_B_9   96
#define   ES_PIN_GPIO_E_0   97
#define   ES_PIN_GPIO_E_1   98



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

#ifndef ES_UART4_TX_GPIO_FUNC
#define ES_UART4_TX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART4_TX_GPIO_PORT
#define ES_UART4_TX_GPIO_PORT GPIOB
#endif
#ifndef ES_UART4_TX_GPIO_PIN
#define ES_UART4_TX_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_UART4_TX_PIN
#ifdef ES_PIN_GPIO_B_6
#define ES_UART4_TX_PIN ES_PIN_GPIO_B_6
#endif
#endif

#ifndef ES_UART4_TX_GPIO_FUNC
#define ES_UART4_TX_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_UART4_TX_GPIO_PORT
#define ES_UART4_TX_GPIO_PORT GPIOE
#endif
#ifndef ES_UART4_TX_GPIO_PIN
#define ES_UART4_TX_GPIO_PIN GPIO_PIN_10
#endif

#ifndef ES_UART4_TX_PIN
#ifdef ES_PIN_GPIO_E_10
#define ES_UART4_TX_PIN ES_PIN_GPIO_E_10
#endif
#endif


/* UART_RX */


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

#ifndef ES_UART4_RX_GPIO_FUNC
#define ES_UART4_RX_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART4_RX_GPIO_PORT
#define ES_UART4_RX_GPIO_PORT GPIOB
#endif
#ifndef ES_UART4_RX_GPIO_PIN
#define ES_UART4_RX_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_UART4_RX_PIN
#ifdef ES_PIN_GPIO_B_7
#define ES_UART4_RX_PIN ES_PIN_GPIO_B_7
#endif
#endif

#ifndef ES_UART4_RX_GPIO_FUNC
#define ES_UART4_RX_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_UART4_RX_GPIO_PORT
#define ES_UART4_RX_GPIO_PORT GPIOE
#endif
#ifndef ES_UART4_RX_GPIO_PIN
#define ES_UART4_RX_GPIO_PIN GPIO_PIN_11
#endif

#ifndef ES_UART4_RX_PIN
#ifdef ES_PIN_GPIO_E_11
#define ES_UART4_RX_PIN ES_PIN_GPIO_E_11
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

#ifndef ES_UART4_RTS_GPIO_FUNC
#define ES_UART4_RTS_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_UART4_RTS_GPIO_PORT
#define ES_UART4_RTS_GPIO_PORT GPIOE
#endif
#ifndef ES_UART4_RTS_GPIO_PIN
#define ES_UART4_RTS_GPIO_PIN GPIO_PIN_13
#endif

#ifndef ES_UART4_RTS_PIN
#ifdef ES_PIN_GPIO_E_13
#define ES_UART4_RTS_PIN ES_PIN_GPIO_E_13
#endif
#endif

#ifndef ES_UART4_RTS_GPIO_FUNC
#define ES_UART4_RTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART4_RTS_GPIO_PORT
#define ES_UART4_RTS_GPIO_PORT GPIOE
#endif
#ifndef ES_UART4_RTS_GPIO_PIN
#define ES_UART4_RTS_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_UART4_RTS_PIN
#ifdef ES_PIN_GPIO_E_1
#define ES_UART4_RTS_PIN ES_PIN_GPIO_E_1
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

#ifndef ES_UART4_CTS_GPIO_FUNC
#define ES_UART4_CTS_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_UART4_CTS_GPIO_PORT
#define ES_UART4_CTS_GPIO_PORT GPIOE
#endif
#ifndef ES_UART4_CTS_GPIO_PIN
#define ES_UART4_CTS_GPIO_PIN GPIO_PIN_12
#endif

#ifndef ES_UART4_CTS_PIN
#ifdef ES_PIN_GPIO_E_12
#define ES_UART4_CTS_PIN ES_PIN_GPIO_E_12
#endif
#endif

#ifndef ES_UART4_CTS_GPIO_FUNC
#define ES_UART4_CTS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART4_CTS_GPIO_PORT
#define ES_UART4_CTS_GPIO_PORT GPIOE
#endif
#ifndef ES_UART4_CTS_GPIO_PIN
#define ES_UART4_CTS_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_UART4_CTS_PIN
#ifdef ES_PIN_GPIO_E_0
#define ES_UART4_CTS_PIN ES_PIN_GPIO_E_0
#endif
#endif


/* UART_CK */


#ifndef ES_UART4_CK_GPIO_FUNC
#define ES_UART4_CK_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_UART4_CK_GPIO_PORT
#define ES_UART4_CK_GPIO_PORT GPIOE
#endif
#ifndef ES_UART4_CK_GPIO_PIN
#define ES_UART4_CK_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_UART4_CK_PIN
#ifdef ES_PIN_GPIO_E_6
#define ES_UART4_CK_PIN ES_PIN_GPIO_E_6
#endif
#endif

#ifndef ES_UART4_CK_GPIO_FUNC
#define ES_UART4_CK_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_UART4_CK_GPIO_PORT
#define ES_UART4_CK_GPIO_PORT GPIOE
#endif
#ifndef ES_UART4_CK_GPIO_PIN
#define ES_UART4_CK_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_UART4_CK_PIN
#ifdef ES_PIN_GPIO_E_7
#define ES_UART4_CK_PIN ES_PIN_GPIO_E_7
#endif
#endif

#ifndef ES_UART4_CK_GPIO_FUNC
#define ES_UART4_CK_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_UART4_CK_GPIO_PORT
#define ES_UART4_CK_GPIO_PORT GPIOA
#endif
#ifndef ES_UART4_CK_GPIO_PIN
#define ES_UART4_CK_GPIO_PIN GPIO_PIN_8
#endif

#ifndef ES_UART4_CK_PIN
#ifdef ES_PIN_GPIO_A_8
#define ES_UART4_CK_PIN ES_PIN_GPIO_A_8
#endif
#endif


/* USART_TX */



/* USART_RX */



/* USART_RTS */



/* USART_CTS */



/* USART_CK */



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


/* SPI_MISO */


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

#ifndef ES_SPI2_MISO_GPIO_FUNC
#define ES_SPI2_MISO_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_SPI2_MISO_GPIO_PORT
#define ES_SPI2_MISO_GPIO_PORT GPIOB
#endif
#ifndef ES_SPI2_MISO_GPIO_PIN
#define ES_SPI2_MISO_GPIO_PIN GPIO_PIN_4
#endif

#ifndef ES_SPI2_MISO_PIN
#ifdef ES_PIN_GPIO_B_4
#define ES_SPI2_MISO_PIN ES_PIN_GPIO_B_4
#endif
#endif

#ifndef ES_SPI2_MISO_GPIO_FUNC
#define ES_SPI2_MISO_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_SPI2_MISO_GPIO_PORT
#define ES_SPI2_MISO_GPIO_PORT GPIOB
#endif
#ifndef ES_SPI2_MISO_GPIO_PIN
#define ES_SPI2_MISO_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_SPI2_MISO_PIN
#ifdef ES_PIN_GPIO_B_0
#define ES_SPI2_MISO_PIN ES_PIN_GPIO_B_0
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

#ifndef ES_SPI2_MOSI_GPIO_FUNC
#define ES_SPI2_MOSI_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_SPI2_MOSI_GPIO_PORT
#define ES_SPI2_MOSI_GPIO_PORT GPIOB
#endif
#ifndef ES_SPI2_MOSI_GPIO_PIN
#define ES_SPI2_MOSI_GPIO_PIN GPIO_PIN_5
#endif

#ifndef ES_SPI2_MOSI_PIN
#ifdef ES_PIN_GPIO_B_5
#define ES_SPI2_MOSI_PIN ES_PIN_GPIO_B_5
#endif
#endif

#ifndef ES_SPI2_MOSI_GPIO_FUNC
#define ES_SPI2_MOSI_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_SPI2_MOSI_GPIO_PORT
#define ES_SPI2_MOSI_GPIO_PORT GPIOB
#endif
#ifndef ES_SPI2_MOSI_GPIO_PIN
#define ES_SPI2_MOSI_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_SPI2_MOSI_PIN
#ifdef ES_PIN_GPIO_B_1
#define ES_SPI2_MOSI_PIN ES_PIN_GPIO_B_1
#endif
#endif


/* SPI_SCK */


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

#ifndef ES_SPI2_SCK_GPIO_FUNC
#define ES_SPI2_SCK_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_SPI2_SCK_GPIO_PORT
#define ES_SPI2_SCK_GPIO_PORT GPIOC
#endif
#ifndef ES_SPI2_SCK_GPIO_PIN
#define ES_SPI2_SCK_GPIO_PIN GPIO_PIN_5
#endif

#ifndef ES_SPI2_SCK_PIN
#ifdef ES_PIN_GPIO_C_5
#define ES_SPI2_SCK_PIN ES_PIN_GPIO_C_5
#endif
#endif

#ifndef ES_SPI2_SCK_GPIO_FUNC
#define ES_SPI2_SCK_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_SPI2_SCK_GPIO_PORT
#define ES_SPI2_SCK_GPIO_PORT GPIOB
#endif
#ifndef ES_SPI2_SCK_GPIO_PIN
#define ES_SPI2_SCK_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_SPI2_SCK_PIN
#ifdef ES_PIN_GPIO_B_3
#define ES_SPI2_SCK_PIN ES_PIN_GPIO_B_3
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

#ifndef ES_SPI2_NSS_GPIO_FUNC
#define ES_SPI2_NSS_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_SPI2_NSS_GPIO_PORT
#define ES_SPI2_NSS_GPIO_PORT GPIOC
#endif
#ifndef ES_SPI2_NSS_GPIO_PIN
#define ES_SPI2_NSS_GPIO_PIN GPIO_PIN_4
#endif

#ifndef ES_SPI2_NSS_PIN
#ifdef ES_PIN_GPIO_C_4
#define ES_SPI2_NSS_PIN ES_PIN_GPIO_C_4
#endif
#endif

#ifndef ES_SPI2_NSS_GPIO_FUNC
#define ES_SPI2_NSS_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_SPI2_NSS_GPIO_PORT
#define ES_SPI2_NSS_GPIO_PORT GPIOA
#endif
#ifndef ES_SPI2_NSS_GPIO_PIN
#define ES_SPI2_NSS_GPIO_PIN GPIO_PIN_15
#endif

#ifndef ES_SPI2_NSS_PIN
#ifdef ES_PIN_GPIO_A_15
#define ES_SPI2_NSS_PIN ES_PIN_GPIO_A_15
#endif
#endif


/* CAN_TX */


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


/* CAN_RX */


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


/* AD16C4T_CH1 */


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

#ifndef ES_AD16C4T1_CH1_GPIO_FUNC
#define ES_AD16C4T1_CH1_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T1_CH1_GPIO_PORT
#define ES_AD16C4T1_CH1_GPIO_PORT GPIOC
#endif
#ifndef ES_AD16C4T1_CH1_GPIO_PIN
#define ES_AD16C4T1_CH1_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_AD16C4T1_CH1_PIN
#ifdef ES_PIN_GPIO_C_6
#define ES_AD16C4T1_CH1_PIN ES_PIN_GPIO_C_6
#endif
#endif


/* AD16C4T_CH2 */


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

#ifndef ES_AD16C4T1_CH2_GPIO_FUNC
#define ES_AD16C4T1_CH2_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T1_CH2_GPIO_PORT
#define ES_AD16C4T1_CH2_GPIO_PORT GPIOC
#endif
#ifndef ES_AD16C4T1_CH2_GPIO_PIN
#define ES_AD16C4T1_CH2_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_AD16C4T1_CH2_PIN
#ifdef ES_PIN_GPIO_C_7
#define ES_AD16C4T1_CH2_PIN ES_PIN_GPIO_C_7
#endif
#endif


/* AD16C4T_CH3 */


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

#ifndef ES_AD16C4T1_CH3_GPIO_FUNC
#define ES_AD16C4T1_CH3_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T1_CH3_GPIO_PORT
#define ES_AD16C4T1_CH3_GPIO_PORT GPIOC
#endif
#ifndef ES_AD16C4T1_CH3_GPIO_PIN
#define ES_AD16C4T1_CH3_GPIO_PIN GPIO_PIN_8
#endif

#ifndef ES_AD16C4T1_CH3_PIN
#ifdef ES_PIN_GPIO_C_8
#define ES_AD16C4T1_CH3_PIN ES_PIN_GPIO_C_8
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

#ifndef ES_AD16C4T1_CH4_GPIO_FUNC
#define ES_AD16C4T1_CH4_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T1_CH4_GPIO_PORT
#define ES_AD16C4T1_CH4_GPIO_PORT GPIOC
#endif
#ifndef ES_AD16C4T1_CH4_GPIO_PIN
#define ES_AD16C4T1_CH4_GPIO_PIN GPIO_PIN_9
#endif

#ifndef ES_AD16C4T1_CH4_PIN
#ifdef ES_PIN_GPIO_C_9
#define ES_AD16C4T1_CH4_PIN ES_PIN_GPIO_C_9
#endif
#endif


/* AD16C4T_CH1N */


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

#ifndef ES_AD16C4T1_CH1N_GPIO_FUNC
#define ES_AD16C4T1_CH1N_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_AD16C4T1_CH1N_GPIO_PORT
#define ES_AD16C4T1_CH1N_GPIO_PORT GPIOA
#endif
#ifndef ES_AD16C4T1_CH1N_GPIO_PIN
#define ES_AD16C4T1_CH1N_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_AD16C4T1_CH1N_PIN
#ifdef ES_PIN_GPIO_A_7
#define ES_AD16C4T1_CH1N_PIN ES_PIN_GPIO_A_7
#endif
#endif


/* AD16C4T_CH2N */


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

#ifndef ES_AD16C4T1_CH2N_GPIO_FUNC
#define ES_AD16C4T1_CH2N_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_AD16C4T1_CH2N_GPIO_PORT
#define ES_AD16C4T1_CH2N_GPIO_PORT GPIOB
#endif
#ifndef ES_AD16C4T1_CH2N_GPIO_PIN
#define ES_AD16C4T1_CH2N_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_AD16C4T1_CH2N_PIN
#ifdef ES_PIN_GPIO_B_0
#define ES_AD16C4T1_CH2N_PIN ES_PIN_GPIO_B_0
#endif
#endif


/* AD16C4T_CH3N */


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

#ifndef ES_AD16C4T1_CH3N_GPIO_FUNC
#define ES_AD16C4T1_CH3N_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_AD16C4T1_CH3N_GPIO_PORT
#define ES_AD16C4T1_CH3N_GPIO_PORT GPIOB
#endif
#ifndef ES_AD16C4T1_CH3N_GPIO_PIN
#define ES_AD16C4T1_CH3N_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_AD16C4T1_CH3N_PIN
#ifdef ES_PIN_GPIO_B_1
#define ES_AD16C4T1_CH3N_PIN ES_PIN_GPIO_B_1
#endif
#endif


/* AD16C4T_CH4N */



/* AD16C4T_ET */


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

#ifndef ES_AD16C4T1_ET_GPIO_FUNC
#define ES_AD16C4T1_ET_GPIO_FUNC GPIO_FUNC_4
#endif
#ifndef ES_AD16C4T1_ET_GPIO_PORT
#define ES_AD16C4T1_ET_GPIO_PORT GPIOA
#endif
#ifndef ES_AD16C4T1_ET_GPIO_PIN
#define ES_AD16C4T1_ET_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_AD16C4T1_ET_PIN
#ifdef ES_PIN_GPIO_A_0
#define ES_AD16C4T1_ET_PIN ES_PIN_GPIO_A_0
#endif
#endif


/* GP32C4T_CH1 */


#ifndef ES_GP32C4T0_CH1_GPIO_FUNC
#define ES_GP32C4T0_CH1_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP32C4T0_CH1_GPIO_PORT
#define ES_GP32C4T0_CH1_GPIO_PORT GPIOA
#endif
#ifndef ES_GP32C4T0_CH1_GPIO_PIN
#define ES_GP32C4T0_CH1_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_GP32C4T0_CH1_PIN
#ifdef ES_PIN_GPIO_A_0
#define ES_GP32C4T0_CH1_PIN ES_PIN_GPIO_A_0
#endif
#endif

#ifndef ES_GP32C4T0_CH1_GPIO_FUNC
#define ES_GP32C4T0_CH1_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP32C4T0_CH1_GPIO_PORT
#define ES_GP32C4T0_CH1_GPIO_PORT GPIOA
#endif
#ifndef ES_GP32C4T0_CH1_GPIO_PIN
#define ES_GP32C4T0_CH1_GPIO_PIN GPIO_PIN_15
#endif

#ifndef ES_GP32C4T0_CH1_PIN
#ifdef ES_PIN_GPIO_A_15
#define ES_GP32C4T0_CH1_PIN ES_PIN_GPIO_A_15
#endif
#endif

#ifndef ES_GP32C4T1_CH1_GPIO_FUNC
#define ES_GP32C4T1_CH1_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_GP32C4T1_CH1_GPIO_PORT
#define ES_GP32C4T1_CH1_GPIO_PORT GPIOA
#endif
#ifndef ES_GP32C4T1_CH1_GPIO_PIN
#define ES_GP32C4T1_CH1_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_GP32C4T1_CH1_PIN
#ifdef ES_PIN_GPIO_A_6
#define ES_GP32C4T1_CH1_PIN ES_PIN_GPIO_A_6
#endif
#endif

#ifndef ES_GP32C4T1_CH1_GPIO_FUNC
#define ES_GP32C4T1_CH1_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_GP32C4T1_CH1_GPIO_PORT
#define ES_GP32C4T1_CH1_GPIO_PORT GPIOC
#endif
#ifndef ES_GP32C4T1_CH1_GPIO_PIN
#define ES_GP32C4T1_CH1_GPIO_PIN GPIO_PIN_6
#endif

#ifndef ES_GP32C4T1_CH1_PIN
#ifdef ES_PIN_GPIO_C_6
#define ES_GP32C4T1_CH1_PIN ES_PIN_GPIO_C_6
#endif
#endif

#ifndef ES_GP32C4T1_CH1_GPIO_FUNC
#define ES_GP32C4T1_CH1_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP32C4T1_CH1_GPIO_PORT
#define ES_GP32C4T1_CH1_GPIO_PORT GPIOB
#endif
#ifndef ES_GP32C4T1_CH1_GPIO_PIN
#define ES_GP32C4T1_CH1_GPIO_PIN GPIO_PIN_4
#endif

#ifndef ES_GP32C4T1_CH1_PIN
#ifdef ES_PIN_GPIO_B_4
#define ES_GP32C4T1_CH1_PIN ES_PIN_GPIO_B_4
#endif
#endif


/* GP32C4T_CH2 */


#ifndef ES_GP32C4T0_CH2_GPIO_FUNC
#define ES_GP32C4T0_CH2_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP32C4T0_CH2_GPIO_PORT
#define ES_GP32C4T0_CH2_GPIO_PORT GPIOA
#endif
#ifndef ES_GP32C4T0_CH2_GPIO_PIN
#define ES_GP32C4T0_CH2_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_GP32C4T0_CH2_PIN
#ifdef ES_PIN_GPIO_A_1
#define ES_GP32C4T0_CH2_PIN ES_PIN_GPIO_A_1
#endif
#endif

#ifndef ES_GP32C4T0_CH2_GPIO_FUNC
#define ES_GP32C4T0_CH2_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP32C4T0_CH2_GPIO_PORT
#define ES_GP32C4T0_CH2_GPIO_PORT GPIOB
#endif
#ifndef ES_GP32C4T0_CH2_GPIO_PIN
#define ES_GP32C4T0_CH2_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_GP32C4T0_CH2_PIN
#ifdef ES_PIN_GPIO_B_3
#define ES_GP32C4T0_CH2_PIN ES_PIN_GPIO_B_3
#endif
#endif

#ifndef ES_GP32C4T1_CH2_GPIO_FUNC
#define ES_GP32C4T1_CH2_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP32C4T1_CH2_GPIO_PORT
#define ES_GP32C4T1_CH2_GPIO_PORT GPIOB
#endif
#ifndef ES_GP32C4T1_CH2_GPIO_PIN
#define ES_GP32C4T1_CH2_GPIO_PIN GPIO_PIN_5
#endif

#ifndef ES_GP32C4T1_CH2_PIN
#ifdef ES_PIN_GPIO_B_5
#define ES_GP32C4T1_CH2_PIN ES_PIN_GPIO_B_5
#endif
#endif

#ifndef ES_GP32C4T1_CH2_GPIO_FUNC
#define ES_GP32C4T1_CH2_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_GP32C4T1_CH2_GPIO_PORT
#define ES_GP32C4T1_CH2_GPIO_PORT GPIOA
#endif
#ifndef ES_GP32C4T1_CH2_GPIO_PIN
#define ES_GP32C4T1_CH2_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_GP32C4T1_CH2_PIN
#ifdef ES_PIN_GPIO_A_7
#define ES_GP32C4T1_CH2_PIN ES_PIN_GPIO_A_7
#endif
#endif

#ifndef ES_GP32C4T1_CH2_GPIO_FUNC
#define ES_GP32C4T1_CH2_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_GP32C4T1_CH2_GPIO_PORT
#define ES_GP32C4T1_CH2_GPIO_PORT GPIOC
#endif
#ifndef ES_GP32C4T1_CH2_GPIO_PIN
#define ES_GP32C4T1_CH2_GPIO_PIN GPIO_PIN_7
#endif

#ifndef ES_GP32C4T1_CH2_PIN
#ifdef ES_PIN_GPIO_C_7
#define ES_GP32C4T1_CH2_PIN ES_PIN_GPIO_C_7
#endif
#endif


/* GP32C4T_CH3 */


#ifndef ES_GP32C4T0_CH3_GPIO_FUNC
#define ES_GP32C4T0_CH3_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP32C4T0_CH3_GPIO_PORT
#define ES_GP32C4T0_CH3_GPIO_PORT GPIOA
#endif
#ifndef ES_GP32C4T0_CH3_GPIO_PIN
#define ES_GP32C4T0_CH3_GPIO_PIN GPIO_PIN_2
#endif

#ifndef ES_GP32C4T0_CH3_PIN
#ifdef ES_PIN_GPIO_A_2
#define ES_GP32C4T0_CH3_PIN ES_PIN_GPIO_A_2
#endif
#endif

#ifndef ES_GP32C4T0_CH3_GPIO_FUNC
#define ES_GP32C4T0_CH3_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP32C4T0_CH3_GPIO_PORT
#define ES_GP32C4T0_CH3_GPIO_PORT GPIOB
#endif
#ifndef ES_GP32C4T0_CH3_GPIO_PIN
#define ES_GP32C4T0_CH3_GPIO_PIN GPIO_PIN_10
#endif

#ifndef ES_GP32C4T0_CH3_PIN
#ifdef ES_PIN_GPIO_B_10
#define ES_GP32C4T0_CH3_PIN ES_PIN_GPIO_B_10
#endif
#endif

#ifndef ES_GP32C4T1_CH3_GPIO_FUNC
#define ES_GP32C4T1_CH3_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP32C4T1_CH3_GPIO_PORT
#define ES_GP32C4T1_CH3_GPIO_PORT GPIOB
#endif
#ifndef ES_GP32C4T1_CH3_GPIO_PIN
#define ES_GP32C4T1_CH3_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_GP32C4T1_CH3_PIN
#ifdef ES_PIN_GPIO_B_0
#define ES_GP32C4T1_CH3_PIN ES_PIN_GPIO_B_0
#endif
#endif

#ifndef ES_GP32C4T1_CH3_GPIO_FUNC
#define ES_GP32C4T1_CH3_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_GP32C4T1_CH3_GPIO_PORT
#define ES_GP32C4T1_CH3_GPIO_PORT GPIOC
#endif
#ifndef ES_GP32C4T1_CH3_GPIO_PIN
#define ES_GP32C4T1_CH3_GPIO_PIN GPIO_PIN_8
#endif

#ifndef ES_GP32C4T1_CH3_PIN
#ifdef ES_PIN_GPIO_C_8
#define ES_GP32C4T1_CH3_PIN ES_PIN_GPIO_C_8
#endif
#endif


/* GP32C4T_CH4 */


#ifndef ES_GP32C4T0_CH4_GPIO_FUNC
#define ES_GP32C4T0_CH4_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP32C4T0_CH4_GPIO_PORT
#define ES_GP32C4T0_CH4_GPIO_PORT GPIOB
#endif
#ifndef ES_GP32C4T0_CH4_GPIO_PIN
#define ES_GP32C4T0_CH4_GPIO_PIN GPIO_PIN_11
#endif

#ifndef ES_GP32C4T0_CH4_PIN
#ifdef ES_PIN_GPIO_B_11
#define ES_GP32C4T0_CH4_PIN ES_PIN_GPIO_B_11
#endif
#endif

#ifndef ES_GP32C4T0_CH4_GPIO_FUNC
#define ES_GP32C4T0_CH4_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP32C4T0_CH4_GPIO_PORT
#define ES_GP32C4T0_CH4_GPIO_PORT GPIOA
#endif
#ifndef ES_GP32C4T0_CH4_GPIO_PIN
#define ES_GP32C4T0_CH4_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_GP32C4T0_CH4_PIN
#ifdef ES_PIN_GPIO_A_3
#define ES_GP32C4T0_CH4_PIN ES_PIN_GPIO_A_3
#endif
#endif

#ifndef ES_GP32C4T1_CH4_GPIO_FUNC
#define ES_GP32C4T1_CH4_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP32C4T1_CH4_GPIO_PORT
#define ES_GP32C4T1_CH4_GPIO_PORT GPIOB
#endif
#ifndef ES_GP32C4T1_CH4_GPIO_PIN
#define ES_GP32C4T1_CH4_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_GP32C4T1_CH4_PIN
#ifdef ES_PIN_GPIO_B_1
#define ES_GP32C4T1_CH4_PIN ES_PIN_GPIO_B_1
#endif
#endif

#ifndef ES_GP32C4T1_CH4_GPIO_FUNC
#define ES_GP32C4T1_CH4_GPIO_FUNC GPIO_FUNC_3
#endif
#ifndef ES_GP32C4T1_CH4_GPIO_PORT
#define ES_GP32C4T1_CH4_GPIO_PORT GPIOC
#endif
#ifndef ES_GP32C4T1_CH4_GPIO_PIN
#define ES_GP32C4T1_CH4_GPIO_PIN GPIO_PIN_9
#endif

#ifndef ES_GP32C4T1_CH4_PIN
#ifdef ES_PIN_GPIO_C_9
#define ES_GP32C4T1_CH4_PIN ES_PIN_GPIO_C_9
#endif
#endif


/* GP32C4T_ET */


#ifndef ES_GP32C4T0_ET_GPIO_FUNC
#define ES_GP32C4T0_ET_GPIO_FUNC GPIO_FUNC_6
#endif
#ifndef ES_GP32C4T0_ET_GPIO_PORT
#define ES_GP32C4T0_ET_GPIO_PORT GPIOA
#endif
#ifndef ES_GP32C4T0_ET_GPIO_PIN
#define ES_GP32C4T0_ET_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_GP32C4T0_ET_PIN
#ifdef ES_PIN_GPIO_A_0
#define ES_GP32C4T0_ET_PIN ES_PIN_GPIO_A_0
#endif
#endif

#ifndef ES_GP32C4T0_ET_GPIO_FUNC
#define ES_GP32C4T0_ET_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_GP32C4T0_ET_GPIO_PORT
#define ES_GP32C4T0_ET_GPIO_PORT GPIOA
#endif
#ifndef ES_GP32C4T0_ET_GPIO_PIN
#define ES_GP32C4T0_ET_GPIO_PIN GPIO_PIN_15
#endif

#ifndef ES_GP32C4T0_ET_PIN
#ifdef ES_PIN_GPIO_A_15
#define ES_GP32C4T0_ET_PIN ES_PIN_GPIO_A_15
#endif
#endif

#ifndef ES_GP32C4T1_ET_GPIO_FUNC
#define ES_GP32C4T1_ET_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP32C4T1_ET_GPIO_PORT
#define ES_GP32C4T1_ET_GPIO_PORT GPIOD
#endif
#ifndef ES_GP32C4T1_ET_GPIO_PIN
#define ES_GP32C4T1_ET_GPIO_PIN GPIO_PIN_2
#endif

#ifndef ES_GP32C4T1_ET_PIN
#ifdef ES_PIN_GPIO_D_2
#define ES_GP32C4T1_ET_PIN ES_PIN_GPIO_D_2
#endif
#endif


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

#ifndef ES_GP16C4T1_CH1_GPIO_FUNC
#define ES_GP16C4T1_CH1_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_GP16C4T1_CH1_GPIO_PORT
#define ES_GP16C4T1_CH1_GPIO_PORT GPIOA
#endif
#ifndef ES_GP16C4T1_CH1_GPIO_PIN
#define ES_GP16C4T1_CH1_GPIO_PIN GPIO_PIN_0
#endif

#ifndef ES_GP16C4T1_CH1_PIN
#ifdef ES_PIN_GPIO_A_0
#define ES_GP16C4T1_CH1_PIN ES_PIN_GPIO_A_0
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

#ifndef ES_GP16C4T1_CH2_GPIO_FUNC
#define ES_GP16C4T1_CH2_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_GP16C4T1_CH2_GPIO_PORT
#define ES_GP16C4T1_CH2_GPIO_PORT GPIOA
#endif
#ifndef ES_GP16C4T1_CH2_GPIO_PIN
#define ES_GP16C4T1_CH2_GPIO_PIN GPIO_PIN_1
#endif

#ifndef ES_GP16C4T1_CH2_PIN
#ifdef ES_PIN_GPIO_A_1
#define ES_GP16C4T1_CH2_PIN ES_PIN_GPIO_A_1
#endif
#endif


/* GP16C4T_CH3 */


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

#ifndef ES_GP16C4T1_CH3_GPIO_FUNC
#define ES_GP16C4T1_CH3_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_GP16C4T1_CH3_GPIO_PORT
#define ES_GP16C4T1_CH3_GPIO_PORT GPIOA
#endif
#ifndef ES_GP16C4T1_CH3_GPIO_PIN
#define ES_GP16C4T1_CH3_GPIO_PIN GPIO_PIN_2
#endif

#ifndef ES_GP16C4T1_CH3_PIN
#ifdef ES_PIN_GPIO_A_2
#define ES_GP16C4T1_CH3_PIN ES_PIN_GPIO_A_2
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

#ifndef ES_GP16C4T1_CH4_GPIO_FUNC
#define ES_GP16C4T1_CH4_GPIO_FUNC GPIO_FUNC_5
#endif
#ifndef ES_GP16C4T1_CH4_GPIO_PORT
#define ES_GP16C4T1_CH4_GPIO_PORT GPIOA
#endif
#ifndef ES_GP16C4T1_CH4_GPIO_PIN
#define ES_GP16C4T1_CH4_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_GP16C4T1_CH4_PIN
#ifdef ES_PIN_GPIO_A_3
#define ES_GP16C4T1_CH4_PIN ES_PIN_GPIO_A_3
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

#ifndef ES_GP16C4T1_ET_GPIO_FUNC
#define ES_GP16C4T1_ET_GPIO_FUNC GPIO_FUNC_2
#endif
#ifndef ES_GP16C4T1_ET_GPIO_PORT
#define ES_GP16C4T1_ET_GPIO_PORT GPIOD
#endif
#ifndef ES_GP16C4T1_ET_GPIO_PIN
#define ES_GP16C4T1_ET_GPIO_PIN GPIO_PIN_3
#endif

#ifndef ES_GP16C4T1_ET_PIN
#ifdef ES_PIN_GPIO_D_3
#define ES_GP16C4T1_ET_PIN ES_PIN_GPIO_D_3
#endif
#endif


/* GP16C2T_CH1 */



/* GP16C2T_CH2 */



/* GP16C2T_CH1N*/



/* GP16C2T_CH2N*/



#define   ES_RTT_APP_LED_PIN   ES_PIN_GPIO_F_0

#endif
