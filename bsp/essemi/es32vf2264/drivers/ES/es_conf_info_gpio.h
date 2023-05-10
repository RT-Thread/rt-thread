/*
 *  Change Logs:
 *  Date            Author          Notes
 *  2022-02-10      Lisq            the first version
 *
 * Copyright (C) 2022 Shanghai Eastsoft Microelectronics Co., Ltd. All rights reserved.
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

#ifndef __ES_CONF_INFO_GPIO_H__
#define __ES_CONF_INFO_GPIO_H__

#include "es_conf_info_map.h"


/* GPIO 配置 */

typedef struct {
        uint8_t pin;
        uint8_t pin_mode;
        uint8_t pin_level;
        uint8_t irq_en;
        uint8_t irq_mode;
        void (*callback)(void *arg);
} gpio_conf_t;

/*参数的定义*/

#define ES_C_GPIO_LEVEL_HIGH          PIN_HIGH
#define ES_C_GPIO_LEVEL_LOW           PIN_LOW

#define ES_C_GPIO_MODE_OUTPUT           PIN_MODE_OUTPUT
#define ES_C_GPIO_MODE_INPUT            PIN_MODE_INPUT
#define ES_C_GPIO_MODE_INPUT_PULLUP     PIN_MODE_INPUT_PULLUP
#define ES_C_GPIO_MODE_INPUT_PULLDOWN   PIN_MODE_INPUT_PULLDOWN
#define ES_C_GPIO_MODE_OUTPUT_OD        PIN_MODE_OUTPUT_OD

#define ES_C_GPIO_IRQ_ENABLE       PIN_IRQ_ENABLE
#define ES_C_GPIO_IRQ_DISABLE      PIN_IRQ_DISABLE

#define ES_C_GPIO_IRQ_MODE_FALL    PIN_IRQ_MODE_FALLING
#define ES_C_GPIO_IRQ_MODE_RISE    PIN_IRQ_MODE_RISING
#define ES_C_GPIO_IRQ_MODE_R_F    PIN_IRQ_MODE_RISING_FALLING





/* codes_main */
//#define ES_INIT_PIN_GPIO_C_8
//#define ES_INIT_GPIO_C_8_IRQ_EN   ES_C_GPIO_IRQ_ENABLE



#ifndef  ES_DEVICE_NAME_PIN
#define  ES_DEVICE_NAME_PIN     "pin"
#endif

/*GPIO外部中断回调函数控制需要，补充是否中断*/
#if 11111

#ifndef  ES_INIT_GPIO_A_0_IRQ_EN
#define ES_INIT_GPIO_A_0_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_1_IRQ_EN
#define ES_INIT_GPIO_A_1_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_2_IRQ_EN
#define ES_INIT_GPIO_A_2_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_3_IRQ_EN
#define ES_INIT_GPIO_A_3_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_4_IRQ_EN
#define ES_INIT_GPIO_A_4_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_5_IRQ_EN
#define ES_INIT_GPIO_A_5_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_6_IRQ_EN
#define ES_INIT_GPIO_A_6_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_7_IRQ_EN
#define ES_INIT_GPIO_A_7_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_8_IRQ_EN
#define ES_INIT_GPIO_A_8_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_9_IRQ_EN
#define ES_INIT_GPIO_A_9_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_10_IRQ_EN
#define ES_INIT_GPIO_A_10_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_11_IRQ_EN
#define ES_INIT_GPIO_A_11_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_12_IRQ_EN
#define ES_INIT_GPIO_A_12_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_13_IRQ_EN
#define ES_INIT_GPIO_A_13_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_14_IRQ_EN
#define ES_INIT_GPIO_A_14_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_A_15_IRQ_EN
#define ES_INIT_GPIO_A_15_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_0_IRQ_EN
#define ES_INIT_GPIO_B_0_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_1_IRQ_EN
#define ES_INIT_GPIO_B_1_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_2_IRQ_EN
#define ES_INIT_GPIO_B_2_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_3_IRQ_EN
#define ES_INIT_GPIO_B_3_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_4_IRQ_EN
#define ES_INIT_GPIO_B_4_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_5_IRQ_EN
#define ES_INIT_GPIO_B_5_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_6_IRQ_EN
#define ES_INIT_GPIO_B_6_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_7_IRQ_EN
#define ES_INIT_GPIO_B_7_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_8_IRQ_EN
#define ES_INIT_GPIO_B_8_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_9_IRQ_EN
#define ES_INIT_GPIO_B_9_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_10_IRQ_EN
#define ES_INIT_GPIO_B_10_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_11_IRQ_EN
#define ES_INIT_GPIO_B_11_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_12_IRQ_EN
#define ES_INIT_GPIO_B_12_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_13_IRQ_EN
#define ES_INIT_GPIO_B_13_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_14_IRQ_EN
#define ES_INIT_GPIO_B_14_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_B_15_IRQ_EN
#define ES_INIT_GPIO_B_15_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_0_IRQ_EN
#define ES_INIT_GPIO_C_0_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_1_IRQ_EN
#define ES_INIT_GPIO_C_1_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_2_IRQ_EN
#define ES_INIT_GPIO_C_2_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_3_IRQ_EN
#define ES_INIT_GPIO_C_3_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_4_IRQ_EN
#define ES_INIT_GPIO_C_4_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_5_IRQ_EN
#define ES_INIT_GPIO_C_5_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_6_IRQ_EN
#define ES_INIT_GPIO_C_6_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_7_IRQ_EN
#define ES_INIT_GPIO_C_7_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_8_IRQ_EN
#define ES_INIT_GPIO_C_8_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_9_IRQ_EN
#define ES_INIT_GPIO_C_9_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_10_IRQ_EN
#define ES_INIT_GPIO_C_10_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_11_IRQ_EN
#define ES_INIT_GPIO_C_11_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_12_IRQ_EN
#define ES_INIT_GPIO_C_12_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_13_IRQ_EN
#define ES_INIT_GPIO_C_13_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_14_IRQ_EN
#define ES_INIT_GPIO_C_14_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_C_15_IRQ_EN
#define ES_INIT_GPIO_C_15_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_0_IRQ_EN
#define ES_INIT_GPIO_D_0_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_1_IRQ_EN
#define ES_INIT_GPIO_D_1_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_2_IRQ_EN
#define ES_INIT_GPIO_D_2_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_3_IRQ_EN
#define ES_INIT_GPIO_D_3_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_4_IRQ_EN
#define ES_INIT_GPIO_D_4_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_5_IRQ_EN
#define ES_INIT_GPIO_D_5_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_6_IRQ_EN
#define ES_INIT_GPIO_D_6_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_7_IRQ_EN
#define ES_INIT_GPIO_D_7_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_8_IRQ_EN
#define ES_INIT_GPIO_D_8_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_9_IRQ_EN
#define ES_INIT_GPIO_D_9_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_10_IRQ_EN
#define ES_INIT_GPIO_D_10_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_11_IRQ_EN
#define ES_INIT_GPIO_D_11_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_12_IRQ_EN
#define ES_INIT_GPIO_D_12_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_13_IRQ_EN
#define ES_INIT_GPIO_D_13_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_14_IRQ_EN
#define ES_INIT_GPIO_D_14_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_D_15_IRQ_EN
#define ES_INIT_GPIO_D_15_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_0_IRQ_EN
#define ES_INIT_GPIO_E_0_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_1_IRQ_EN
#define ES_INIT_GPIO_E_1_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_2_IRQ_EN
#define ES_INIT_GPIO_E_2_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_3_IRQ_EN
#define ES_INIT_GPIO_E_3_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_4_IRQ_EN
#define ES_INIT_GPIO_E_4_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_5_IRQ_EN
#define ES_INIT_GPIO_E_5_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_6_IRQ_EN
#define ES_INIT_GPIO_E_6_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_7_IRQ_EN
#define ES_INIT_GPIO_E_7_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_8_IRQ_EN
#define ES_INIT_GPIO_E_8_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_9_IRQ_EN
#define ES_INIT_GPIO_E_9_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_10_IRQ_EN
#define ES_INIT_GPIO_E_10_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_11_IRQ_EN
#define ES_INIT_GPIO_E_11_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_12_IRQ_EN
#define ES_INIT_GPIO_E_12_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_13_IRQ_EN
#define ES_INIT_GPIO_E_13_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_14_IRQ_EN
#define ES_INIT_GPIO_E_14_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_E_15_IRQ_EN
#define ES_INIT_GPIO_E_15_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_0_IRQ_EN
#define ES_INIT_GPIO_F_0_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_1_IRQ_EN
#define ES_INIT_GPIO_F_1_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_2_IRQ_EN
#define ES_INIT_GPIO_F_2_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_3_IRQ_EN
#define ES_INIT_GPIO_F_3_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_4_IRQ_EN
#define ES_INIT_GPIO_F_4_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_5_IRQ_EN
#define ES_INIT_GPIO_F_5_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_6_IRQ_EN
#define ES_INIT_GPIO_F_6_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_7_IRQ_EN
#define ES_INIT_GPIO_F_7_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_8_IRQ_EN
#define ES_INIT_GPIO_F_8_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_9_IRQ_EN
#define ES_INIT_GPIO_F_9_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_10_IRQ_EN
#define ES_INIT_GPIO_F_10_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_11_IRQ_EN
#define ES_INIT_GPIO_F_11_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_12_IRQ_EN
#define ES_INIT_GPIO_F_12_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_13_IRQ_EN
#define ES_INIT_GPIO_F_13_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_14_IRQ_EN
#define ES_INIT_GPIO_F_14_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_F_15_IRQ_EN
#define ES_INIT_GPIO_F_15_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_0_IRQ_EN
#define ES_INIT_GPIO_G_0_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_1_IRQ_EN
#define ES_INIT_GPIO_G_1_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_2_IRQ_EN
#define ES_INIT_GPIO_G_2_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_3_IRQ_EN
#define ES_INIT_GPIO_G_3_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_4_IRQ_EN
#define ES_INIT_GPIO_G_4_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_5_IRQ_EN
#define ES_INIT_GPIO_G_5_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_6_IRQ_EN
#define ES_INIT_GPIO_G_6_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_7_IRQ_EN
#define ES_INIT_GPIO_G_7_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_8_IRQ_EN
#define ES_INIT_GPIO_G_8_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_9_IRQ_EN
#define ES_INIT_GPIO_G_9_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_10_IRQ_EN
#define ES_INIT_GPIO_G_10_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_11_IRQ_EN
#define ES_INIT_GPIO_G_11_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_12_IRQ_EN
#define ES_INIT_GPIO_G_12_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_13_IRQ_EN
#define ES_INIT_GPIO_G_13_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_14_IRQ_EN
#define ES_INIT_GPIO_G_14_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_G_15_IRQ_EN
#define ES_INIT_GPIO_G_15_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_0_IRQ_EN
#define ES_INIT_GPIO_H_0_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_1_IRQ_EN
#define ES_INIT_GPIO_H_1_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_2_IRQ_EN
#define ES_INIT_GPIO_H_2_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_3_IRQ_EN
#define ES_INIT_GPIO_H_3_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_4_IRQ_EN
#define ES_INIT_GPIO_H_4_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_5_IRQ_EN
#define ES_INIT_GPIO_H_5_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_6_IRQ_EN
#define ES_INIT_GPIO_H_6_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_7_IRQ_EN
#define ES_INIT_GPIO_H_7_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_8_IRQ_EN
#define ES_INIT_GPIO_H_8_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_9_IRQ_EN
#define ES_INIT_GPIO_H_9_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_10_IRQ_EN
#define ES_INIT_GPIO_H_10_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_11_IRQ_EN
#define ES_INIT_GPIO_H_11_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_12_IRQ_EN
#define ES_INIT_GPIO_H_12_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_13_IRQ_EN
#define ES_INIT_GPIO_H_13_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_14_IRQ_EN
#define ES_INIT_GPIO_H_14_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#ifndef  ES_INIT_GPIO_H_15_IRQ_EN
#define ES_INIT_GPIO_H_15_IRQ_EN   ES_C_GPIO_IRQ_DISABLE
#endif

#endif //11111



/*是否需要 GPIO外部中断回调函数 （控制函数本体+声明）*/
#if 11111

#if (ES_INIT_GPIO_A_0_IRQ_EN)||(ES_INIT_GPIO_B_0_IRQ_EN)||(ES_INIT_GPIO_C_0_IRQ_EN)||(ES_INIT_GPIO_D_0_IRQ_EN)||   \
     (ES_INIT_GPIO_E_0_IRQ_EN)||(ES_INIT_GPIO_F_0_IRQ_EN)||(ES_INIT_GPIO_G_0_IRQ_EN)||(ES_INIT_GPIO_H_0_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_0
#endif

#if (ES_INIT_GPIO_A_1_IRQ_EN)||(ES_INIT_GPIO_B_1_IRQ_EN)||(ES_INIT_GPIO_C_1_IRQ_EN)||(ES_INIT_GPIO_D_1_IRQ_EN)||   \
     (ES_INIT_GPIO_E_1_IRQ_EN)||(ES_INIT_GPIO_F_1_IRQ_EN)||(ES_INIT_GPIO_G_1_IRQ_EN)||(ES_INIT_GPIO_H_1_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_1
#endif

#if (ES_INIT_GPIO_A_2_IRQ_EN)||(ES_INIT_GPIO_B_2_IRQ_EN)||(ES_INIT_GPIO_C_2_IRQ_EN)||(ES_INIT_GPIO_D_2_IRQ_EN)||   \
     (ES_INIT_GPIO_E_2_IRQ_EN)||(ES_INIT_GPIO_F_2_IRQ_EN)||(ES_INIT_GPIO_G_2_IRQ_EN)||(ES_INIT_GPIO_H_2_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_2
#endif

#if (ES_INIT_GPIO_A_3_IRQ_EN)||(ES_INIT_GPIO_B_3_IRQ_EN)||(ES_INIT_GPIO_C_3_IRQ_EN)||(ES_INIT_GPIO_D_3_IRQ_EN)||   \
     (ES_INIT_GPIO_E_3_IRQ_EN)||(ES_INIT_GPIO_F_3_IRQ_EN)||(ES_INIT_GPIO_G_3_IRQ_EN)||(ES_INIT_GPIO_H_3_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_3
#endif

#if (ES_INIT_GPIO_A_4_IRQ_EN)||(ES_INIT_GPIO_B_4_IRQ_EN)||(ES_INIT_GPIO_C_4_IRQ_EN)||(ES_INIT_GPIO_D_4_IRQ_EN)||   \
     (ES_INIT_GPIO_E_4_IRQ_EN)||(ES_INIT_GPIO_F_4_IRQ_EN)||(ES_INIT_GPIO_G_4_IRQ_EN)||(ES_INIT_GPIO_H_4_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_4
#endif

#if (ES_INIT_GPIO_A_5_IRQ_EN)||(ES_INIT_GPIO_B_5_IRQ_EN)||(ES_INIT_GPIO_C_5_IRQ_EN)||(ES_INIT_GPIO_D_5_IRQ_EN)||   \
     (ES_INIT_GPIO_E_5_IRQ_EN)||(ES_INIT_GPIO_F_5_IRQ_EN)||(ES_INIT_GPIO_G_5_IRQ_EN)||(ES_INIT_GPIO_H_5_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_5
#endif

#if (ES_INIT_GPIO_A_6_IRQ_EN)||(ES_INIT_GPIO_B_6_IRQ_EN)||(ES_INIT_GPIO_C_6_IRQ_EN)||(ES_INIT_GPIO_D_6_IRQ_EN)||   \
     (ES_INIT_GPIO_E_6_IRQ_EN)||(ES_INIT_GPIO_F_6_IRQ_EN)||(ES_INIT_GPIO_G_6_IRQ_EN)||(ES_INIT_GPIO_H_6_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_6
#endif

#if (ES_INIT_GPIO_A_7_IRQ_EN)||(ES_INIT_GPIO_B_7_IRQ_EN)||(ES_INIT_GPIO_C_7_IRQ_EN)||(ES_INIT_GPIO_D_7_IRQ_EN)||   \
     (ES_INIT_GPIO_E_7_IRQ_EN)||(ES_INIT_GPIO_F_7_IRQ_EN)||(ES_INIT_GPIO_G_7_IRQ_EN)||(ES_INIT_GPIO_H_7_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_7
#endif

#if (ES_INIT_GPIO_A_8_IRQ_EN)||(ES_INIT_GPIO_B_8_IRQ_EN)||(ES_INIT_GPIO_C_8_IRQ_EN)||(ES_INIT_GPIO_D_8_IRQ_EN)||   \
     (ES_INIT_GPIO_E_8_IRQ_EN)||(ES_INIT_GPIO_F_8_IRQ_EN)||(ES_INIT_GPIO_G_8_IRQ_EN)||(ES_INIT_GPIO_H_8_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_8
#endif

#if (ES_INIT_GPIO_A_9_IRQ_EN)||(ES_INIT_GPIO_B_9_IRQ_EN)||(ES_INIT_GPIO_C_9_IRQ_EN)||(ES_INIT_GPIO_D_9_IRQ_EN)||   \
     (ES_INIT_GPIO_E_9_IRQ_EN)||(ES_INIT_GPIO_F_9_IRQ_EN)||(ES_INIT_GPIO_G_9_IRQ_EN)||(ES_INIT_GPIO_H_9_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_9
#endif

#if (ES_INIT_GPIO_A_10_IRQ_EN)||(ES_INIT_GPIO_B_10_IRQ_EN)||(ES_INIT_GPIO_C_10_IRQ_EN)||(ES_INIT_GPIO_D_10_IRQ_EN)||   \
     (ES_INIT_GPIO_E_10_IRQ_EN)||(ES_INIT_GPIO_F_10_IRQ_EN)||(ES_INIT_GPIO_G_10_IRQ_EN)||(ES_INIT_GPIO_H_10_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_10
#endif

#if (ES_INIT_GPIO_A_11_IRQ_EN)||(ES_INIT_GPIO_B_11_IRQ_EN)||(ES_INIT_GPIO_C_11_IRQ_EN)||(ES_INIT_GPIO_D_11_IRQ_EN)||   \
     (ES_INIT_GPIO_E_11_IRQ_EN)||(ES_INIT_GPIO_F_11_IRQ_EN)||(ES_INIT_GPIO_G_11_IRQ_EN)||(ES_INIT_GPIO_H_11_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_11
#endif

#if (ES_INIT_GPIO_A_12_IRQ_EN)||(ES_INIT_GPIO_B_12_IRQ_EN)||(ES_INIT_GPIO_C_12_IRQ_EN)||(ES_INIT_GPIO_D_12_IRQ_EN)||   \
     (ES_INIT_GPIO_E_12_IRQ_EN)||(ES_INIT_GPIO_F_12_IRQ_EN)||(ES_INIT_GPIO_G_12_IRQ_EN)||(ES_INIT_GPIO_H_12_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_12
#endif

#if (ES_INIT_GPIO_A_13_IRQ_EN)||(ES_INIT_GPIO_B_13_IRQ_EN)||(ES_INIT_GPIO_C_13_IRQ_EN)||(ES_INIT_GPIO_D_13_IRQ_EN)||   \
     (ES_INIT_GPIO_E_13_IRQ_EN)||(ES_INIT_GPIO_F_13_IRQ_EN)||(ES_INIT_GPIO_G_13_IRQ_EN)||(ES_INIT_GPIO_H_13_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_13
#endif

#if (ES_INIT_GPIO_A_14_IRQ_EN)||(ES_INIT_GPIO_B_14_IRQ_EN)||(ES_INIT_GPIO_C_14_IRQ_EN)||(ES_INIT_GPIO_D_14_IRQ_EN)||   \
     (ES_INIT_GPIO_E_14_IRQ_EN)||(ES_INIT_GPIO_F_14_IRQ_EN)||(ES_INIT_GPIO_G_14_IRQ_EN)||(ES_INIT_GPIO_H_14_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_14
#endif

#if (ES_INIT_GPIO_A_15_IRQ_EN)||(ES_INIT_GPIO_B_15_IRQ_EN)||(ES_INIT_GPIO_C_15_IRQ_EN)||(ES_INIT_GPIO_D_15_IRQ_EN)||   \
     (ES_INIT_GPIO_E_15_IRQ_EN)||(ES_INIT_GPIO_F_15_IRQ_EN)||(ES_INIT_GPIO_G_15_IRQ_EN)||(ES_INIT_GPIO_H_15_IRQ_EN)
#define  ES_CONF_EXTI_IRQ_15
#endif

#endif //11111


/*GPIO外部中断 声明*/
#if 11111

#ifdef ES_CONF_EXTI_IRQ_0
void irq_pin0_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_1
void irq_pin1_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_2
void irq_pin2_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_3
void irq_pin3_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_4
void irq_pin4_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_5
void irq_pin5_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_6
void irq_pin6_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_7
void irq_pin7_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_8
void irq_pin8_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_9
void irq_pin9_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_10
void irq_pin10_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_11
void irq_pin11_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_12
void irq_pin12_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_13
void irq_pin13_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_14
void irq_pin14_callback(void* arg);
#endif

#ifdef ES_CONF_EXTI_IRQ_15
void irq_pin15_callback(void* arg);
#endif


#endif //11111




/*是否有配置的管脚*/
#if defined(ES_INIT_PIN_GPIO_A_0) || defined(ES_INIT_PIN_GPIO_A_1) || defined(ES_INIT_PIN_GPIO_A_2) || defined(ES_INIT_PIN_GPIO_A_3) || \
    defined(ES_INIT_PIN_GPIO_A_4) || defined(ES_INIT_PIN_GPIO_A_5) || defined(ES_INIT_PIN_GPIO_A_6) || defined(ES_INIT_PIN_GPIO_A_7) || \
    defined(ES_INIT_PIN_GPIO_A_8) || defined(ES_INIT_PIN_GPIO_A_9) || defined(ES_INIT_PIN_GPIO_A_10) || defined(ES_INIT_PIN_GPIO_A_11) || \
    defined(ES_INIT_PIN_GPIO_A_12) || defined(ES_INIT_PIN_GPIO_A_13) || defined(ES_INIT_PIN_GPIO_A_14) || defined(ES_INIT_PIN_GPIO_A_15) || \
    defined(ES_INIT_PIN_GPIO_B_0) || defined(ES_INIT_PIN_GPIO_B_1) || defined(ES_INIT_PIN_GPIO_B_2) || defined(ES_INIT_PIN_GPIO_B_3) || \
    defined(ES_INIT_PIN_GPIO_B_4) || defined(ES_INIT_PIN_GPIO_B_5) || defined(ES_INIT_PIN_GPIO_B_6) || defined(ES_INIT_PIN_GPIO_B_7) || \
    defined(ES_INIT_PIN_GPIO_B_8) || defined(ES_INIT_PIN_GPIO_B_9) || defined(ES_INIT_PIN_GPIO_B_10) || defined(ES_INIT_PIN_GPIO_B_11) || \
    defined(ES_INIT_PIN_GPIO_B_12) || defined(ES_INIT_PIN_GPIO_B_13) || defined(ES_INIT_PIN_GPIO_B_14) || defined(ES_INIT_PIN_GPIO_B_15) || \
    defined(ES_INIT_PIN_GPIO_C_0) || defined(ES_INIT_PIN_GPIO_C_1) || defined(ES_INIT_PIN_GPIO_C_2) || defined(ES_INIT_PIN_GPIO_C_3) || \
    defined(ES_INIT_PIN_GPIO_C_4) || defined(ES_INIT_PIN_GPIO_C_5) || defined(ES_INIT_PIN_GPIO_C_6) || defined(ES_INIT_PIN_GPIO_C_7) || \
    defined(ES_INIT_PIN_GPIO_C_8) || defined(ES_INIT_PIN_GPIO_C_9) || defined(ES_INIT_PIN_GPIO_C_10) || defined(ES_INIT_PIN_GPIO_C_11) || \
    defined(ES_INIT_PIN_GPIO_C_12) || defined(ES_INIT_PIN_GPIO_C_13) || defined(ES_INIT_PIN_GPIO_C_14) || defined(ES_INIT_PIN_GPIO_C_15) || \
    defined(ES_INIT_PIN_GPIO_D_0) || defined(ES_INIT_PIN_GPIO_D_1) || defined(ES_INIT_PIN_GPIO_D_2) || defined(ES_INIT_PIN_GPIO_D_3) || \
    defined(ES_INIT_PIN_GPIO_D_4) || defined(ES_INIT_PIN_GPIO_D_5) || defined(ES_INIT_PIN_GPIO_D_6) || defined(ES_INIT_PIN_GPIO_D_7) || \
    defined(ES_INIT_PIN_GPIO_D_8) || defined(ES_INIT_PIN_GPIO_D_9) || defined(ES_INIT_PIN_GPIO_D_10) || defined(ES_INIT_PIN_GPIO_D_11) || \
    defined(ES_INIT_PIN_GPIO_D_12) || defined(ES_INIT_PIN_GPIO_D_13) || defined(ES_INIT_PIN_GPIO_D_14) || defined(ES_INIT_PIN_GPIO_D_15) || \
    defined(ES_INIT_PIN_GPIO_E_0) || defined(ES_INIT_PIN_GPIO_E_1) || defined(ES_INIT_PIN_GPIO_E_2) || defined(ES_INIT_PIN_GPIO_E_3) || \
    defined(ES_INIT_PIN_GPIO_E_4) || defined(ES_INIT_PIN_GPIO_E_5) || defined(ES_INIT_PIN_GPIO_E_6) || defined(ES_INIT_PIN_GPIO_E_7) || \
    defined(ES_INIT_PIN_GPIO_E_8) || defined(ES_INIT_PIN_GPIO_E_9) || defined(ES_INIT_PIN_GPIO_E_10) || defined(ES_INIT_PIN_GPIO_E_11) || \
    defined(ES_INIT_PIN_GPIO_E_12) || defined(ES_INIT_PIN_GPIO_E_13) || defined(ES_INIT_PIN_GPIO_E_14) || defined(ES_INIT_PIN_GPIO_E_15) || \
    defined(ES_INIT_PIN_GPIO_F_0) || defined(ES_INIT_PIN_GPIO_F_1) || defined(ES_INIT_PIN_GPIO_F_2) || defined(ES_INIT_PIN_GPIO_F_3) || \
    defined(ES_INIT_PIN_GPIO_F_4) || defined(ES_INIT_PIN_GPIO_F_5) || defined(ES_INIT_PIN_GPIO_F_6) || defined(ES_INIT_PIN_GPIO_F_7) || \
    defined(ES_INIT_PIN_GPIO_F_8) || defined(ES_INIT_PIN_GPIO_F_9) || defined(ES_INIT_PIN_GPIO_F_10) || defined(ES_INIT_PIN_GPIO_F_11) || \
    defined(ES_INIT_PIN_GPIO_F_12) || defined(ES_INIT_PIN_GPIO_F_13) || defined(ES_INIT_PIN_GPIO_F_14) || defined(ES_INIT_PIN_GPIO_F_15) || \
    defined(ES_INIT_PIN_GPIO_G_0) || defined(ES_INIT_PIN_GPIO_G_1) || defined(ES_INIT_PIN_GPIO_G_2) || defined(ES_INIT_PIN_GPIO_G_3) || \
    defined(ES_INIT_PIN_GPIO_G_4) || defined(ES_INIT_PIN_GPIO_G_5) || defined(ES_INIT_PIN_GPIO_G_6) || defined(ES_INIT_PIN_GPIO_G_7) || \
    defined(ES_INIT_PIN_GPIO_G_8) || defined(ES_INIT_PIN_GPIO_G_9) || defined(ES_INIT_PIN_GPIO_G_10) || defined(ES_INIT_PIN_GPIO_G_11) || \
    defined(ES_INIT_PIN_GPIO_G_12) || defined(ES_INIT_PIN_GPIO_G_13) || defined(ES_INIT_PIN_GPIO_G_14) || defined(ES_INIT_PIN_GPIO_G_15) || \
    defined(ES_INIT_PIN_GPIO_H_0) || defined(ES_INIT_PIN_GPIO_H_1) || defined(ES_INIT_PIN_GPIO_H_2) || defined(ES_INIT_PIN_GPIO_H_3) || \
    defined(ES_INIT_PIN_GPIO_H_4) || defined(ES_INIT_PIN_GPIO_H_5) || defined(ES_INIT_PIN_GPIO_H_6) || defined(ES_INIT_PIN_GPIO_H_7) || \
    defined(ES_INIT_PIN_GPIO_H_8) || defined(ES_INIT_PIN_GPIO_H_9) || defined(ES_INIT_PIN_GPIO_H_10) || defined(ES_INIT_PIN_GPIO_H_11) || \
    defined(ES_INIT_PIN_GPIO_H_12) || defined(ES_INIT_PIN_GPIO_H_13) || defined(ES_INIT_PIN_GPIO_H_14) || defined(ES_INIT_PIN_GPIO_H_15)

#define ES_INIT_GPIOS

#endif


#ifdef   ES_INIT_GPIOS

static gpio_conf_t gpio_conf_all[] =
{

#ifdef  ES_INIT_PIN_GPIO_A_0

    {
      ES_PIN_GPIO_A_0 ,

#ifdef   ES_INIT_GPIO_A_0_MODE
      ES_INIT_GPIO_A_0_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_0_LEVEL
      ES_INIT_GPIO_A_0_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_0_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_0_IRQ_MODE
      ES_INIT_GPIO_A_0_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_0_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin0_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_1

    {
      ES_PIN_GPIO_A_1 ,

#ifdef   ES_INIT_GPIO_A_1_MODE
      ES_INIT_GPIO_A_1_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_1_LEVEL
      ES_INIT_GPIO_A_1_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_1_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_1_IRQ_MODE
      ES_INIT_GPIO_A_1_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_1_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin1_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_2

    {
      ES_PIN_GPIO_A_2 ,

#ifdef   ES_INIT_GPIO_A_2_MODE
      ES_INIT_GPIO_A_2_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_2_LEVEL
      ES_INIT_GPIO_A_2_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_2_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_2_IRQ_MODE
      ES_INIT_GPIO_A_2_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_2_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin2_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_3

    {
      ES_PIN_GPIO_A_3 ,

#ifdef   ES_INIT_GPIO_A_3_MODE
      ES_INIT_GPIO_A_3_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_3_LEVEL
      ES_INIT_GPIO_A_3_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_3_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_3_IRQ_MODE
      ES_INIT_GPIO_A_3_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_3_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin3_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_4

    {
      ES_PIN_GPIO_A_4 ,

#ifdef   ES_INIT_GPIO_A_4_MODE
      ES_INIT_GPIO_A_4_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_4_LEVEL
      ES_INIT_GPIO_A_4_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_4_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_4_IRQ_MODE
      ES_INIT_GPIO_A_4_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_4_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin4_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_5

    {
      ES_PIN_GPIO_A_5 ,

#ifdef   ES_INIT_GPIO_A_5_MODE
      ES_INIT_GPIO_A_5_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_5_LEVEL
      ES_INIT_GPIO_A_5_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_5_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_5_IRQ_MODE
      ES_INIT_GPIO_A_5_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_5_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin5_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_6

    {
      ES_PIN_GPIO_A_6 ,

#ifdef   ES_INIT_GPIO_A_6_MODE
      ES_INIT_GPIO_A_6_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_6_LEVEL
      ES_INIT_GPIO_A_6_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_6_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_6_IRQ_MODE
      ES_INIT_GPIO_A_6_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_6_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin6_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_7

    {
      ES_PIN_GPIO_A_7 ,

#ifdef   ES_INIT_GPIO_A_7_MODE
      ES_INIT_GPIO_A_7_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_7_LEVEL
      ES_INIT_GPIO_A_7_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_7_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_7_IRQ_MODE
      ES_INIT_GPIO_A_7_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_7_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin7_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_8

    {
      ES_PIN_GPIO_A_8 ,

#ifdef   ES_INIT_GPIO_A_8_MODE
      ES_INIT_GPIO_A_8_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_8_LEVEL
      ES_INIT_GPIO_A_8_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_8_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_8_IRQ_MODE
      ES_INIT_GPIO_A_8_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_8_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin8_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_9

    {
      ES_PIN_GPIO_A_9 ,

#ifdef   ES_INIT_GPIO_A_9_MODE
      ES_INIT_GPIO_A_9_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_9_LEVEL
      ES_INIT_GPIO_A_9_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_9_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_9_IRQ_MODE
      ES_INIT_GPIO_A_9_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_9_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin9_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_10

    {
      ES_PIN_GPIO_A_10 ,

#ifdef   ES_INIT_GPIO_A_10_MODE
      ES_INIT_GPIO_A_10_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_10_LEVEL
      ES_INIT_GPIO_A_10_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_10_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_10_IRQ_MODE
      ES_INIT_GPIO_A_10_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_10_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin10_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_11

    {
      ES_PIN_GPIO_A_11 ,

#ifdef   ES_INIT_GPIO_A_11_MODE
      ES_INIT_GPIO_A_11_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_11_LEVEL
      ES_INIT_GPIO_A_11_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_11_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_11_IRQ_MODE
      ES_INIT_GPIO_A_11_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_11_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin11_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_12

    {
      ES_PIN_GPIO_A_12 ,

#ifdef   ES_INIT_GPIO_A_12_MODE
      ES_INIT_GPIO_A_12_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_12_LEVEL
      ES_INIT_GPIO_A_12_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_12_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_12_IRQ_MODE
      ES_INIT_GPIO_A_12_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_12_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin12_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_13

    {
      ES_PIN_GPIO_A_13 ,

#ifdef   ES_INIT_GPIO_A_13_MODE
      ES_INIT_GPIO_A_13_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_13_LEVEL
      ES_INIT_GPIO_A_13_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_13_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_13_IRQ_MODE
      ES_INIT_GPIO_A_13_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_13_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin13_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_14

    {
      ES_PIN_GPIO_A_14 ,

#ifdef   ES_INIT_GPIO_A_14_MODE
      ES_INIT_GPIO_A_14_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_14_LEVEL
      ES_INIT_GPIO_A_14_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_14_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_14_IRQ_MODE
      ES_INIT_GPIO_A_14_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_14_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin14_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_A_15

    {
      ES_PIN_GPIO_A_15 ,

#ifdef   ES_INIT_GPIO_A_15_MODE
      ES_INIT_GPIO_A_15_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_A_15_LEVEL
      ES_INIT_GPIO_A_15_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_A_15_IRQ_EN ,

#ifdef   ES_INIT_GPIO_A_15_IRQ_MODE
      ES_INIT_GPIO_A_15_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_A_15_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin15_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_0

    {
      ES_PIN_GPIO_B_0 ,

#ifdef   ES_INIT_GPIO_B_0_MODE
      ES_INIT_GPIO_B_0_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_0_LEVEL
      ES_INIT_GPIO_B_0_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_0_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_0_IRQ_MODE
      ES_INIT_GPIO_B_0_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_0_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin0_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_1

    {
      ES_PIN_GPIO_B_1 ,

#ifdef   ES_INIT_GPIO_B_1_MODE
      ES_INIT_GPIO_B_1_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_1_LEVEL
      ES_INIT_GPIO_B_1_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_1_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_1_IRQ_MODE
      ES_INIT_GPIO_B_1_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_1_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin1_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_2

    {
      ES_PIN_GPIO_B_2 ,

#ifdef   ES_INIT_GPIO_B_2_MODE
      ES_INIT_GPIO_B_2_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_2_LEVEL
      ES_INIT_GPIO_B_2_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_2_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_2_IRQ_MODE
      ES_INIT_GPIO_B_2_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_2_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin2_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_3

    {
      ES_PIN_GPIO_B_3 ,

#ifdef   ES_INIT_GPIO_B_3_MODE
      ES_INIT_GPIO_B_3_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_3_LEVEL
      ES_INIT_GPIO_B_3_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_3_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_3_IRQ_MODE
      ES_INIT_GPIO_B_3_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_3_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin3_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_4

    {
      ES_PIN_GPIO_B_4 ,

#ifdef   ES_INIT_GPIO_B_4_MODE
      ES_INIT_GPIO_B_4_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_4_LEVEL
      ES_INIT_GPIO_B_4_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_4_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_4_IRQ_MODE
      ES_INIT_GPIO_B_4_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_4_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin4_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_5

    {
      ES_PIN_GPIO_B_5 ,

#ifdef   ES_INIT_GPIO_B_5_MODE
      ES_INIT_GPIO_B_5_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_5_LEVEL
      ES_INIT_GPIO_B_5_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_5_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_5_IRQ_MODE
      ES_INIT_GPIO_B_5_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_5_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin5_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_6

    {
      ES_PIN_GPIO_B_6 ,

#ifdef   ES_INIT_GPIO_B_6_MODE
      ES_INIT_GPIO_B_6_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_6_LEVEL
      ES_INIT_GPIO_B_6_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_6_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_6_IRQ_MODE
      ES_INIT_GPIO_B_6_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_6_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin6_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_7

    {
      ES_PIN_GPIO_B_7 ,

#ifdef   ES_INIT_GPIO_B_7_MODE
      ES_INIT_GPIO_B_7_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_7_LEVEL
      ES_INIT_GPIO_B_7_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_7_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_7_IRQ_MODE
      ES_INIT_GPIO_B_7_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_7_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin7_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_8

    {
      ES_PIN_GPIO_B_8 ,

#ifdef   ES_INIT_GPIO_B_8_MODE
      ES_INIT_GPIO_B_8_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_8_LEVEL
      ES_INIT_GPIO_B_8_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_8_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_8_IRQ_MODE
      ES_INIT_GPIO_B_8_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_8_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin8_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_9

    {
      ES_PIN_GPIO_B_9 ,

#ifdef   ES_INIT_GPIO_B_9_MODE
      ES_INIT_GPIO_B_9_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_9_LEVEL
      ES_INIT_GPIO_B_9_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_9_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_9_IRQ_MODE
      ES_INIT_GPIO_B_9_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_9_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin9_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_10

    {
      ES_PIN_GPIO_B_10 ,

#ifdef   ES_INIT_GPIO_B_10_MODE
      ES_INIT_GPIO_B_10_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_10_LEVEL
      ES_INIT_GPIO_B_10_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_10_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_10_IRQ_MODE
      ES_INIT_GPIO_B_10_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_10_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin10_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_11

    {
      ES_PIN_GPIO_B_11 ,

#ifdef   ES_INIT_GPIO_B_11_MODE
      ES_INIT_GPIO_B_11_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_11_LEVEL
      ES_INIT_GPIO_B_11_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_11_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_11_IRQ_MODE
      ES_INIT_GPIO_B_11_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_11_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin11_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_12

    {
      ES_PIN_GPIO_B_12 ,

#ifdef   ES_INIT_GPIO_B_12_MODE
      ES_INIT_GPIO_B_12_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_12_LEVEL
      ES_INIT_GPIO_B_12_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_12_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_12_IRQ_MODE
      ES_INIT_GPIO_B_12_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_12_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin12_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_13

    {
      ES_PIN_GPIO_B_13 ,

#ifdef   ES_INIT_GPIO_B_13_MODE
      ES_INIT_GPIO_B_13_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_13_LEVEL
      ES_INIT_GPIO_B_13_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_13_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_13_IRQ_MODE
      ES_INIT_GPIO_B_13_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_13_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin13_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_14

    {
      ES_PIN_GPIO_B_14 ,

#ifdef   ES_INIT_GPIO_B_14_MODE
      ES_INIT_GPIO_B_14_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_14_LEVEL
      ES_INIT_GPIO_B_14_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_14_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_14_IRQ_MODE
      ES_INIT_GPIO_B_14_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_14_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin14_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_B_15

    {
      ES_PIN_GPIO_B_15 ,

#ifdef   ES_INIT_GPIO_B_15_MODE
      ES_INIT_GPIO_B_15_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_B_15_LEVEL
      ES_INIT_GPIO_B_15_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_B_15_IRQ_EN ,

#ifdef   ES_INIT_GPIO_B_15_IRQ_MODE
      ES_INIT_GPIO_B_15_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_B_15_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin15_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_0

    {
      ES_PIN_GPIO_C_0 ,

#ifdef   ES_INIT_GPIO_C_0_MODE
      ES_INIT_GPIO_C_0_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_0_LEVEL
      ES_INIT_GPIO_C_0_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_0_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_0_IRQ_MODE
      ES_INIT_GPIO_C_0_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_0_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin0_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_1

    {
      ES_PIN_GPIO_C_1 ,

#ifdef   ES_INIT_GPIO_C_1_MODE
      ES_INIT_GPIO_C_1_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_1_LEVEL
      ES_INIT_GPIO_C_1_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_1_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_1_IRQ_MODE
      ES_INIT_GPIO_C_1_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_1_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin1_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_2

    {
      ES_PIN_GPIO_C_2 ,

#ifdef   ES_INIT_GPIO_C_2_MODE
      ES_INIT_GPIO_C_2_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_2_LEVEL
      ES_INIT_GPIO_C_2_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_2_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_2_IRQ_MODE
      ES_INIT_GPIO_C_2_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_2_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin2_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_3

    {
      ES_PIN_GPIO_C_3 ,

#ifdef   ES_INIT_GPIO_C_3_MODE
      ES_INIT_GPIO_C_3_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_3_LEVEL
      ES_INIT_GPIO_C_3_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_3_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_3_IRQ_MODE
      ES_INIT_GPIO_C_3_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_3_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin3_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_4

    {
      ES_PIN_GPIO_C_4 ,

#ifdef   ES_INIT_GPIO_C_4_MODE
      ES_INIT_GPIO_C_4_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_4_LEVEL
      ES_INIT_GPIO_C_4_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_4_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_4_IRQ_MODE
      ES_INIT_GPIO_C_4_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_4_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin4_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_5

    {
      ES_PIN_GPIO_C_5 ,

#ifdef   ES_INIT_GPIO_C_5_MODE
      ES_INIT_GPIO_C_5_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_5_LEVEL
      ES_INIT_GPIO_C_5_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_5_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_5_IRQ_MODE
      ES_INIT_GPIO_C_5_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_5_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin5_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_6

    {
      ES_PIN_GPIO_C_6 ,

#ifdef   ES_INIT_GPIO_C_6_MODE
      ES_INIT_GPIO_C_6_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_6_LEVEL
      ES_INIT_GPIO_C_6_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_6_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_6_IRQ_MODE
      ES_INIT_GPIO_C_6_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_6_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin6_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_7

    {
      ES_PIN_GPIO_C_7 ,

#ifdef   ES_INIT_GPIO_C_7_MODE
      ES_INIT_GPIO_C_7_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_7_LEVEL
      ES_INIT_GPIO_C_7_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_7_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_7_IRQ_MODE
      ES_INIT_GPIO_C_7_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_7_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin7_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_8

    {
      ES_PIN_GPIO_C_8 ,

#ifdef   ES_INIT_GPIO_C_8_MODE
      ES_INIT_GPIO_C_8_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_8_LEVEL
      ES_INIT_GPIO_C_8_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_8_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_8_IRQ_MODE
      ES_INIT_GPIO_C_8_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_8_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin8_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_9

    {
      ES_PIN_GPIO_C_9 ,

#ifdef   ES_INIT_GPIO_C_9_MODE
      ES_INIT_GPIO_C_9_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_9_LEVEL
      ES_INIT_GPIO_C_9_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_9_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_9_IRQ_MODE
      ES_INIT_GPIO_C_9_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_9_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin9_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_10

    {
      ES_PIN_GPIO_C_10 ,

#ifdef   ES_INIT_GPIO_C_10_MODE
      ES_INIT_GPIO_C_10_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_10_LEVEL
      ES_INIT_GPIO_C_10_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_10_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_10_IRQ_MODE
      ES_INIT_GPIO_C_10_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_10_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin10_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_11

    {
      ES_PIN_GPIO_C_11 ,

#ifdef   ES_INIT_GPIO_C_11_MODE
      ES_INIT_GPIO_C_11_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_11_LEVEL
      ES_INIT_GPIO_C_11_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_11_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_11_IRQ_MODE
      ES_INIT_GPIO_C_11_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_11_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin11_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_12

    {
      ES_PIN_GPIO_C_12 ,

#ifdef   ES_INIT_GPIO_C_12_MODE
      ES_INIT_GPIO_C_12_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_12_LEVEL
      ES_INIT_GPIO_C_12_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_12_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_12_IRQ_MODE
      ES_INIT_GPIO_C_12_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_12_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin12_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_13

    {
      ES_PIN_GPIO_C_13 ,

#ifdef   ES_INIT_GPIO_C_13_MODE
      ES_INIT_GPIO_C_13_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_13_LEVEL
      ES_INIT_GPIO_C_13_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_13_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_13_IRQ_MODE
      ES_INIT_GPIO_C_13_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_13_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin13_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_14

    {
      ES_PIN_GPIO_C_14 ,

#ifdef   ES_INIT_GPIO_C_14_MODE
      ES_INIT_GPIO_C_14_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_14_LEVEL
      ES_INIT_GPIO_C_14_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_14_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_14_IRQ_MODE
      ES_INIT_GPIO_C_14_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_14_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin14_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_C_15

    {
      ES_PIN_GPIO_C_15 ,

#ifdef   ES_INIT_GPIO_C_15_MODE
      ES_INIT_GPIO_C_15_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_C_15_LEVEL
      ES_INIT_GPIO_C_15_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_C_15_IRQ_EN ,

#ifdef   ES_INIT_GPIO_C_15_IRQ_MODE
      ES_INIT_GPIO_C_15_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_C_15_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin15_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_0

    {
      ES_PIN_GPIO_D_0 ,

#ifdef   ES_INIT_GPIO_D_0_MODE
      ES_INIT_GPIO_D_0_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_0_LEVEL
      ES_INIT_GPIO_D_0_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_0_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_0_IRQ_MODE
      ES_INIT_GPIO_D_0_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_0_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin0_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_1

    {
      ES_PIN_GPIO_D_1 ,

#ifdef   ES_INIT_GPIO_D_1_MODE
      ES_INIT_GPIO_D_1_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_1_LEVEL
      ES_INIT_GPIO_D_1_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_1_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_1_IRQ_MODE
      ES_INIT_GPIO_D_1_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_1_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin1_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_2

    {
      ES_PIN_GPIO_D_2 ,

#ifdef   ES_INIT_GPIO_D_2_MODE
      ES_INIT_GPIO_D_2_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_2_LEVEL
      ES_INIT_GPIO_D_2_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_2_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_2_IRQ_MODE
      ES_INIT_GPIO_D_2_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_2_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin2_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_3

    {
      ES_PIN_GPIO_D_3 ,

#ifdef   ES_INIT_GPIO_D_3_MODE
      ES_INIT_GPIO_D_3_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_3_LEVEL
      ES_INIT_GPIO_D_3_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_3_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_3_IRQ_MODE
      ES_INIT_GPIO_D_3_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_3_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin3_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_4

    {
      ES_PIN_GPIO_D_4 ,

#ifdef   ES_INIT_GPIO_D_4_MODE
      ES_INIT_GPIO_D_4_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_4_LEVEL
      ES_INIT_GPIO_D_4_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_4_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_4_IRQ_MODE
      ES_INIT_GPIO_D_4_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_4_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin4_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_5

    {
      ES_PIN_GPIO_D_5 ,

#ifdef   ES_INIT_GPIO_D_5_MODE
      ES_INIT_GPIO_D_5_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_5_LEVEL
      ES_INIT_GPIO_D_5_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_5_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_5_IRQ_MODE
      ES_INIT_GPIO_D_5_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_5_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin5_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_6

    {
      ES_PIN_GPIO_D_6 ,

#ifdef   ES_INIT_GPIO_D_6_MODE
      ES_INIT_GPIO_D_6_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_6_LEVEL
      ES_INIT_GPIO_D_6_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_6_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_6_IRQ_MODE
      ES_INIT_GPIO_D_6_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_6_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin6_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_7

    {
      ES_PIN_GPIO_D_7 ,

#ifdef   ES_INIT_GPIO_D_7_MODE
      ES_INIT_GPIO_D_7_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_7_LEVEL
      ES_INIT_GPIO_D_7_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_7_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_7_IRQ_MODE
      ES_INIT_GPIO_D_7_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_7_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin7_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_8

    {
      ES_PIN_GPIO_D_8 ,

#ifdef   ES_INIT_GPIO_D_8_MODE
      ES_INIT_GPIO_D_8_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_8_LEVEL
      ES_INIT_GPIO_D_8_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_8_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_8_IRQ_MODE
      ES_INIT_GPIO_D_8_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_8_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin8_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_9

    {
      ES_PIN_GPIO_D_9 ,

#ifdef   ES_INIT_GPIO_D_9_MODE
      ES_INIT_GPIO_D_9_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_9_LEVEL
      ES_INIT_GPIO_D_9_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_9_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_9_IRQ_MODE
      ES_INIT_GPIO_D_9_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_9_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin9_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_10

    {
      ES_PIN_GPIO_D_10 ,

#ifdef   ES_INIT_GPIO_D_10_MODE
      ES_INIT_GPIO_D_10_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_10_LEVEL
      ES_INIT_GPIO_D_10_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_10_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_10_IRQ_MODE
      ES_INIT_GPIO_D_10_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_10_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin10_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_11

    {
      ES_PIN_GPIO_D_11 ,

#ifdef   ES_INIT_GPIO_D_11_MODE
      ES_INIT_GPIO_D_11_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_11_LEVEL
      ES_INIT_GPIO_D_11_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_11_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_11_IRQ_MODE
      ES_INIT_GPIO_D_11_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_11_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin11_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_12

    {
      ES_PIN_GPIO_D_12 ,

#ifdef   ES_INIT_GPIO_D_12_MODE
      ES_INIT_GPIO_D_12_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_12_LEVEL
      ES_INIT_GPIO_D_12_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_12_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_12_IRQ_MODE
      ES_INIT_GPIO_D_12_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_12_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin12_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_13

    {
      ES_PIN_GPIO_D_13 ,

#ifdef   ES_INIT_GPIO_D_13_MODE
      ES_INIT_GPIO_D_13_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_13_LEVEL
      ES_INIT_GPIO_D_13_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_13_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_13_IRQ_MODE
      ES_INIT_GPIO_D_13_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_13_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin13_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_14

    {
      ES_PIN_GPIO_D_14 ,

#ifdef   ES_INIT_GPIO_D_14_MODE
      ES_INIT_GPIO_D_14_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_14_LEVEL
      ES_INIT_GPIO_D_14_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_14_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_14_IRQ_MODE
      ES_INIT_GPIO_D_14_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_14_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin14_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_D_15

    {
      ES_PIN_GPIO_D_15 ,

#ifdef   ES_INIT_GPIO_D_15_MODE
      ES_INIT_GPIO_D_15_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_D_15_LEVEL
      ES_INIT_GPIO_D_15_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_D_15_IRQ_EN ,

#ifdef   ES_INIT_GPIO_D_15_IRQ_MODE
      ES_INIT_GPIO_D_15_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_D_15_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin15_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_0

    {
      ES_PIN_GPIO_E_0 ,

#ifdef   ES_INIT_GPIO_E_0_MODE
      ES_INIT_GPIO_E_0_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_0_LEVEL
      ES_INIT_GPIO_E_0_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_0_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_0_IRQ_MODE
      ES_INIT_GPIO_E_0_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_0_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin0_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_1

    {
      ES_PIN_GPIO_E_1 ,

#ifdef   ES_INIT_GPIO_E_1_MODE
      ES_INIT_GPIO_E_1_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_1_LEVEL
      ES_INIT_GPIO_E_1_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_1_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_1_IRQ_MODE
      ES_INIT_GPIO_E_1_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_1_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin1_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_2

    {
      ES_PIN_GPIO_E_2 ,

#ifdef   ES_INIT_GPIO_E_2_MODE
      ES_INIT_GPIO_E_2_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_2_LEVEL
      ES_INIT_GPIO_E_2_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_2_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_2_IRQ_MODE
      ES_INIT_GPIO_E_2_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_2_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin2_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_3

    {
      ES_PIN_GPIO_E_3 ,

#ifdef   ES_INIT_GPIO_E_3_MODE
      ES_INIT_GPIO_E_3_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_3_LEVEL
      ES_INIT_GPIO_E_3_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_3_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_3_IRQ_MODE
      ES_INIT_GPIO_E_3_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_3_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin3_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_4

    {
      ES_PIN_GPIO_E_4 ,

#ifdef   ES_INIT_GPIO_E_4_MODE
      ES_INIT_GPIO_E_4_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_4_LEVEL
      ES_INIT_GPIO_E_4_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_4_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_4_IRQ_MODE
      ES_INIT_GPIO_E_4_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_4_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin4_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_5

    {
      ES_PIN_GPIO_E_5 ,

#ifdef   ES_INIT_GPIO_E_5_MODE
      ES_INIT_GPIO_E_5_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_5_LEVEL
      ES_INIT_GPIO_E_5_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_5_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_5_IRQ_MODE
      ES_INIT_GPIO_E_5_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_5_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin5_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_6

    {
      ES_PIN_GPIO_E_6 ,

#ifdef   ES_INIT_GPIO_E_6_MODE
      ES_INIT_GPIO_E_6_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_6_LEVEL
      ES_INIT_GPIO_E_6_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_6_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_6_IRQ_MODE
      ES_INIT_GPIO_E_6_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_6_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin6_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_7

    {
      ES_PIN_GPIO_E_7 ,

#ifdef   ES_INIT_GPIO_E_7_MODE
      ES_INIT_GPIO_E_7_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_7_LEVEL
      ES_INIT_GPIO_E_7_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_7_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_7_IRQ_MODE
      ES_INIT_GPIO_E_7_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_7_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin7_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_8

    {
      ES_PIN_GPIO_E_8 ,

#ifdef   ES_INIT_GPIO_E_8_MODE
      ES_INIT_GPIO_E_8_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_8_LEVEL
      ES_INIT_GPIO_E_8_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_8_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_8_IRQ_MODE
      ES_INIT_GPIO_E_8_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_8_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin8_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_9

    {
      ES_PIN_GPIO_E_9 ,

#ifdef   ES_INIT_GPIO_E_9_MODE
      ES_INIT_GPIO_E_9_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_9_LEVEL
      ES_INIT_GPIO_E_9_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_9_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_9_IRQ_MODE
      ES_INIT_GPIO_E_9_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_9_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin9_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_10

    {
      ES_PIN_GPIO_E_10 ,

#ifdef   ES_INIT_GPIO_E_10_MODE
      ES_INIT_GPIO_E_10_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_10_LEVEL
      ES_INIT_GPIO_E_10_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_10_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_10_IRQ_MODE
      ES_INIT_GPIO_E_10_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_10_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin10_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_11

    {
      ES_PIN_GPIO_E_11 ,

#ifdef   ES_INIT_GPIO_E_11_MODE
      ES_INIT_GPIO_E_11_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_11_LEVEL
      ES_INIT_GPIO_E_11_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_11_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_11_IRQ_MODE
      ES_INIT_GPIO_E_11_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_11_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin11_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_12

    {
      ES_PIN_GPIO_E_12 ,

#ifdef   ES_INIT_GPIO_E_12_MODE
      ES_INIT_GPIO_E_12_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_12_LEVEL
      ES_INIT_GPIO_E_12_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_12_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_12_IRQ_MODE
      ES_INIT_GPIO_E_12_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_12_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin12_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_13

    {
      ES_PIN_GPIO_E_13 ,

#ifdef   ES_INIT_GPIO_E_13_MODE
      ES_INIT_GPIO_E_13_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_13_LEVEL
      ES_INIT_GPIO_E_13_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_13_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_13_IRQ_MODE
      ES_INIT_GPIO_E_13_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_13_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin13_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_14

    {
      ES_PIN_GPIO_E_14 ,

#ifdef   ES_INIT_GPIO_E_14_MODE
      ES_INIT_GPIO_E_14_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_14_LEVEL
      ES_INIT_GPIO_E_14_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_14_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_14_IRQ_MODE
      ES_INIT_GPIO_E_14_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_14_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin14_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_E_15

    {
      ES_PIN_GPIO_E_15 ,

#ifdef   ES_INIT_GPIO_E_15_MODE
      ES_INIT_GPIO_E_15_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_E_15_LEVEL
      ES_INIT_GPIO_E_15_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_E_15_IRQ_EN ,

#ifdef   ES_INIT_GPIO_E_15_IRQ_MODE
      ES_INIT_GPIO_E_15_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_E_15_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin15_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_0

    {
      ES_PIN_GPIO_F_0 ,

#ifdef   ES_INIT_GPIO_F_0_MODE
      ES_INIT_GPIO_F_0_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_0_LEVEL
      ES_INIT_GPIO_F_0_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_0_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_0_IRQ_MODE
      ES_INIT_GPIO_F_0_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_0_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin0_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_1

    {
      ES_PIN_GPIO_F_1 ,

#ifdef   ES_INIT_GPIO_F_1_MODE
      ES_INIT_GPIO_F_1_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_1_LEVEL
      ES_INIT_GPIO_F_1_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_1_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_1_IRQ_MODE
      ES_INIT_GPIO_F_1_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_1_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin1_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_2

    {
      ES_PIN_GPIO_F_2 ,

#ifdef   ES_INIT_GPIO_F_2_MODE
      ES_INIT_GPIO_F_2_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_2_LEVEL
      ES_INIT_GPIO_F_2_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_2_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_2_IRQ_MODE
      ES_INIT_GPIO_F_2_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_2_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin2_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_3

    {
      ES_PIN_GPIO_F_3 ,

#ifdef   ES_INIT_GPIO_F_3_MODE
      ES_INIT_GPIO_F_3_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_3_LEVEL
      ES_INIT_GPIO_F_3_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_3_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_3_IRQ_MODE
      ES_INIT_GPIO_F_3_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_3_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin3_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_4

    {
      ES_PIN_GPIO_F_4 ,

#ifdef   ES_INIT_GPIO_F_4_MODE
      ES_INIT_GPIO_F_4_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_4_LEVEL
      ES_INIT_GPIO_F_4_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_4_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_4_IRQ_MODE
      ES_INIT_GPIO_F_4_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_4_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin4_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_5

    {
      ES_PIN_GPIO_F_5 ,

#ifdef   ES_INIT_GPIO_F_5_MODE
      ES_INIT_GPIO_F_5_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_5_LEVEL
      ES_INIT_GPIO_F_5_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_5_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_5_IRQ_MODE
      ES_INIT_GPIO_F_5_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_5_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin5_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_6

    {
      ES_PIN_GPIO_F_6 ,

#ifdef   ES_INIT_GPIO_F_6_MODE
      ES_INIT_GPIO_F_6_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_6_LEVEL
      ES_INIT_GPIO_F_6_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_6_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_6_IRQ_MODE
      ES_INIT_GPIO_F_6_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_6_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin6_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_7

    {
      ES_PIN_GPIO_F_7 ,

#ifdef   ES_INIT_GPIO_F_7_MODE
      ES_INIT_GPIO_F_7_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_7_LEVEL
      ES_INIT_GPIO_F_7_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_7_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_7_IRQ_MODE
      ES_INIT_GPIO_F_7_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_7_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin7_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_8

    {
      ES_PIN_GPIO_F_8 ,

#ifdef   ES_INIT_GPIO_F_8_MODE
      ES_INIT_GPIO_F_8_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_8_LEVEL
      ES_INIT_GPIO_F_8_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_8_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_8_IRQ_MODE
      ES_INIT_GPIO_F_8_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_8_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin8_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_9

    {
      ES_PIN_GPIO_F_9 ,

#ifdef   ES_INIT_GPIO_F_9_MODE
      ES_INIT_GPIO_F_9_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_9_LEVEL
      ES_INIT_GPIO_F_9_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_9_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_9_IRQ_MODE
      ES_INIT_GPIO_F_9_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_9_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin9_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_10

    {
      ES_PIN_GPIO_F_10 ,

#ifdef   ES_INIT_GPIO_F_10_MODE
      ES_INIT_GPIO_F_10_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_10_LEVEL
      ES_INIT_GPIO_F_10_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_10_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_10_IRQ_MODE
      ES_INIT_GPIO_F_10_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_10_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin10_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_11

    {
      ES_PIN_GPIO_F_11 ,

#ifdef   ES_INIT_GPIO_F_11_MODE
      ES_INIT_GPIO_F_11_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_11_LEVEL
      ES_INIT_GPIO_F_11_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_11_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_11_IRQ_MODE
      ES_INIT_GPIO_F_11_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_11_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin11_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_12

    {
      ES_PIN_GPIO_F_12 ,

#ifdef   ES_INIT_GPIO_F_12_MODE
      ES_INIT_GPIO_F_12_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_12_LEVEL
      ES_INIT_GPIO_F_12_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_12_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_12_IRQ_MODE
      ES_INIT_GPIO_F_12_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_12_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin12_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_13

    {
      ES_PIN_GPIO_F_13 ,

#ifdef   ES_INIT_GPIO_F_13_MODE
      ES_INIT_GPIO_F_13_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_13_LEVEL
      ES_INIT_GPIO_F_13_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_13_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_13_IRQ_MODE
      ES_INIT_GPIO_F_13_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_13_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin13_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_14

    {
      ES_PIN_GPIO_F_14 ,

#ifdef   ES_INIT_GPIO_F_14_MODE
      ES_INIT_GPIO_F_14_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_14_LEVEL
      ES_INIT_GPIO_F_14_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_14_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_14_IRQ_MODE
      ES_INIT_GPIO_F_14_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_14_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin14_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_F_15

    {
      ES_PIN_GPIO_F_15 ,

#ifdef   ES_INIT_GPIO_F_15_MODE
      ES_INIT_GPIO_F_15_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_F_15_LEVEL
      ES_INIT_GPIO_F_15_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_F_15_IRQ_EN ,

#ifdef   ES_INIT_GPIO_F_15_IRQ_MODE
      ES_INIT_GPIO_F_15_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_F_15_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin15_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_0

    {
      ES_PIN_GPIO_G_0 ,

#ifdef   ES_INIT_GPIO_G_0_MODE
      ES_INIT_GPIO_G_0_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_0_LEVEL
      ES_INIT_GPIO_G_0_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_0_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_0_IRQ_MODE
      ES_INIT_GPIO_G_0_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_0_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin0_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_1

    {
      ES_PIN_GPIO_G_1 ,

#ifdef   ES_INIT_GPIO_G_1_MODE
      ES_INIT_GPIO_G_1_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_1_LEVEL
      ES_INIT_GPIO_G_1_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_1_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_1_IRQ_MODE
      ES_INIT_GPIO_G_1_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_1_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin1_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_2

    {
      ES_PIN_GPIO_G_2 ,

#ifdef   ES_INIT_GPIO_G_2_MODE
      ES_INIT_GPIO_G_2_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_2_LEVEL
      ES_INIT_GPIO_G_2_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_2_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_2_IRQ_MODE
      ES_INIT_GPIO_G_2_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_2_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin2_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_3

    {
      ES_PIN_GPIO_G_3 ,

#ifdef   ES_INIT_GPIO_G_3_MODE
      ES_INIT_GPIO_G_3_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_3_LEVEL
      ES_INIT_GPIO_G_3_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_3_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_3_IRQ_MODE
      ES_INIT_GPIO_G_3_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_3_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin3_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_4

    {
      ES_PIN_GPIO_G_4 ,

#ifdef   ES_INIT_GPIO_G_4_MODE
      ES_INIT_GPIO_G_4_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_4_LEVEL
      ES_INIT_GPIO_G_4_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_4_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_4_IRQ_MODE
      ES_INIT_GPIO_G_4_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_4_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin4_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_5

    {
      ES_PIN_GPIO_G_5 ,

#ifdef   ES_INIT_GPIO_G_5_MODE
      ES_INIT_GPIO_G_5_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_5_LEVEL
      ES_INIT_GPIO_G_5_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_5_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_5_IRQ_MODE
      ES_INIT_GPIO_G_5_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_5_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin5_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_6

    {
      ES_PIN_GPIO_G_6 ,

#ifdef   ES_INIT_GPIO_G_6_MODE
      ES_INIT_GPIO_G_6_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_6_LEVEL
      ES_INIT_GPIO_G_6_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_6_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_6_IRQ_MODE
      ES_INIT_GPIO_G_6_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_6_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin6_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_7

    {
      ES_PIN_GPIO_G_7 ,

#ifdef   ES_INIT_GPIO_G_7_MODE
      ES_INIT_GPIO_G_7_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_7_LEVEL
      ES_INIT_GPIO_G_7_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_7_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_7_IRQ_MODE
      ES_INIT_GPIO_G_7_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_7_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin7_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_8

    {
      ES_PIN_GPIO_G_8 ,

#ifdef   ES_INIT_GPIO_G_8_MODE
      ES_INIT_GPIO_G_8_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_8_LEVEL
      ES_INIT_GPIO_G_8_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_8_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_8_IRQ_MODE
      ES_INIT_GPIO_G_8_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_8_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin8_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_9

    {
      ES_PIN_GPIO_G_9 ,

#ifdef   ES_INIT_GPIO_G_9_MODE
      ES_INIT_GPIO_G_9_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_9_LEVEL
      ES_INIT_GPIO_G_9_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_9_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_9_IRQ_MODE
      ES_INIT_GPIO_G_9_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_9_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin9_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_10

    {
      ES_PIN_GPIO_G_10 ,

#ifdef   ES_INIT_GPIO_G_10_MODE
      ES_INIT_GPIO_G_10_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_10_LEVEL
      ES_INIT_GPIO_G_10_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_10_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_10_IRQ_MODE
      ES_INIT_GPIO_G_10_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_10_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin10_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_11

    {
      ES_PIN_GPIO_G_11 ,

#ifdef   ES_INIT_GPIO_G_11_MODE
      ES_INIT_GPIO_G_11_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_11_LEVEL
      ES_INIT_GPIO_G_11_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_11_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_11_IRQ_MODE
      ES_INIT_GPIO_G_11_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_11_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin11_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_12

    {
      ES_PIN_GPIO_G_12 ,

#ifdef   ES_INIT_GPIO_G_12_MODE
      ES_INIT_GPIO_G_12_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_12_LEVEL
      ES_INIT_GPIO_G_12_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_12_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_12_IRQ_MODE
      ES_INIT_GPIO_G_12_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_12_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin12_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_13

    {
      ES_PIN_GPIO_G_13 ,

#ifdef   ES_INIT_GPIO_G_13_MODE
      ES_INIT_GPIO_G_13_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_13_LEVEL
      ES_INIT_GPIO_G_13_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_13_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_13_IRQ_MODE
      ES_INIT_GPIO_G_13_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_13_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin13_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_14

    {
      ES_PIN_GPIO_G_14 ,

#ifdef   ES_INIT_GPIO_G_14_MODE
      ES_INIT_GPIO_G_14_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_14_LEVEL
      ES_INIT_GPIO_G_14_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_14_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_14_IRQ_MODE
      ES_INIT_GPIO_G_14_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_14_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin14_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_G_15

    {
      ES_PIN_GPIO_G_15 ,

#ifdef   ES_INIT_GPIO_G_15_MODE
      ES_INIT_GPIO_G_15_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_G_15_LEVEL
      ES_INIT_GPIO_G_15_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_G_15_IRQ_EN ,

#ifdef   ES_INIT_GPIO_G_15_IRQ_MODE
      ES_INIT_GPIO_G_15_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_G_15_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin15_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_0

    {
      ES_PIN_GPIO_H_0 ,

#ifdef   ES_INIT_GPIO_H_0_MODE
      ES_INIT_GPIO_H_0_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_0_LEVEL
      ES_INIT_GPIO_H_0_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_0_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_0_IRQ_MODE
      ES_INIT_GPIO_H_0_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_0_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin0_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_1

    {
      ES_PIN_GPIO_H_1 ,

#ifdef   ES_INIT_GPIO_H_1_MODE
      ES_INIT_GPIO_H_1_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_1_LEVEL
      ES_INIT_GPIO_H_1_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_1_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_1_IRQ_MODE
      ES_INIT_GPIO_H_1_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_1_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin1_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_2

    {
      ES_PIN_GPIO_H_2 ,

#ifdef   ES_INIT_GPIO_H_2_MODE
      ES_INIT_GPIO_H_2_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_2_LEVEL
      ES_INIT_GPIO_H_2_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_2_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_2_IRQ_MODE
      ES_INIT_GPIO_H_2_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_2_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin2_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_3

    {
      ES_PIN_GPIO_H_3 ,

#ifdef   ES_INIT_GPIO_H_3_MODE
      ES_INIT_GPIO_H_3_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_3_LEVEL
      ES_INIT_GPIO_H_3_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_3_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_3_IRQ_MODE
      ES_INIT_GPIO_H_3_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_3_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin3_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_4

    {
      ES_PIN_GPIO_H_4 ,

#ifdef   ES_INIT_GPIO_H_4_MODE
      ES_INIT_GPIO_H_4_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_4_LEVEL
      ES_INIT_GPIO_H_4_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_4_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_4_IRQ_MODE
      ES_INIT_GPIO_H_4_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_4_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin4_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_5

    {
      ES_PIN_GPIO_H_5 ,

#ifdef   ES_INIT_GPIO_H_5_MODE
      ES_INIT_GPIO_H_5_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_5_LEVEL
      ES_INIT_GPIO_H_5_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_5_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_5_IRQ_MODE
      ES_INIT_GPIO_H_5_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_5_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin5_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_6

    {
      ES_PIN_GPIO_H_6 ,

#ifdef   ES_INIT_GPIO_H_6_MODE
      ES_INIT_GPIO_H_6_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_6_LEVEL
      ES_INIT_GPIO_H_6_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_6_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_6_IRQ_MODE
      ES_INIT_GPIO_H_6_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_6_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin6_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_7

    {
      ES_PIN_GPIO_H_7 ,

#ifdef   ES_INIT_GPIO_H_7_MODE
      ES_INIT_GPIO_H_7_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_7_LEVEL
      ES_INIT_GPIO_H_7_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_7_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_7_IRQ_MODE
      ES_INIT_GPIO_H_7_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_7_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin7_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_8

    {
      ES_PIN_GPIO_H_8 ,

#ifdef   ES_INIT_GPIO_H_8_MODE
      ES_INIT_GPIO_H_8_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_8_LEVEL
      ES_INIT_GPIO_H_8_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_8_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_8_IRQ_MODE
      ES_INIT_GPIO_H_8_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_8_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin8_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_9

    {
      ES_PIN_GPIO_H_9 ,

#ifdef   ES_INIT_GPIO_H_9_MODE
      ES_INIT_GPIO_H_9_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_9_LEVEL
      ES_INIT_GPIO_H_9_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_9_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_9_IRQ_MODE
      ES_INIT_GPIO_H_9_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_9_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin9_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_10

    {
      ES_PIN_GPIO_H_10 ,

#ifdef   ES_INIT_GPIO_H_10_MODE
      ES_INIT_GPIO_H_10_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_10_LEVEL
      ES_INIT_GPIO_H_10_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_10_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_10_IRQ_MODE
      ES_INIT_GPIO_H_10_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_10_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin10_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_11

    {
      ES_PIN_GPIO_H_11 ,

#ifdef   ES_INIT_GPIO_H_11_MODE
      ES_INIT_GPIO_H_11_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_11_LEVEL
      ES_INIT_GPIO_H_11_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_11_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_11_IRQ_MODE
      ES_INIT_GPIO_H_11_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_11_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin11_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_12

    {
      ES_PIN_GPIO_H_12 ,

#ifdef   ES_INIT_GPIO_H_12_MODE
      ES_INIT_GPIO_H_12_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_12_LEVEL
      ES_INIT_GPIO_H_12_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_12_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_12_IRQ_MODE
      ES_INIT_GPIO_H_12_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_12_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin12_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_13

    {
      ES_PIN_GPIO_H_13 ,

#ifdef   ES_INIT_GPIO_H_13_MODE
      ES_INIT_GPIO_H_13_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_13_LEVEL
      ES_INIT_GPIO_H_13_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_13_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_13_IRQ_MODE
      ES_INIT_GPIO_H_13_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_13_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin13_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_14

    {
      ES_PIN_GPIO_H_14 ,

#ifdef   ES_INIT_GPIO_H_14_MODE
      ES_INIT_GPIO_H_14_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_14_LEVEL
      ES_INIT_GPIO_H_14_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_14_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_14_IRQ_MODE
      ES_INIT_GPIO_H_14_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_14_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin14_callback ,
#else
     RT_NULL ,
#endif
    },

#endif

#ifdef  ES_INIT_PIN_GPIO_H_15

    {
      ES_PIN_GPIO_H_15 ,

#ifdef   ES_INIT_GPIO_H_15_MODE
      ES_INIT_GPIO_H_15_MODE ,
#else
     ES_C_GPIO_MODE_OUTPUT ,
#endif

#ifdef   ES_INIT_GPIO_H_15_LEVEL
      ES_INIT_GPIO_H_15_LEVEL ,
#else
     ES_C_GPIO_LEVEL_HIGH ,
#endif

      ES_INIT_GPIO_H_15_IRQ_EN ,

#ifdef   ES_INIT_GPIO_H_15_IRQ_MODE
      ES_INIT_GPIO_H_15_IRQ_MODE ,
#else
     ES_C_GPIO_IRQ_MODE_RISE ,
#endif

#if (ES_INIT_GPIO_H_15_IRQ_EN == ES_C_GPIO_IRQ_ENABLE)
      irq_pin15_callback ,
#else
     RT_NULL ,
#endif
    },

#endif



};

#endif



#endif
