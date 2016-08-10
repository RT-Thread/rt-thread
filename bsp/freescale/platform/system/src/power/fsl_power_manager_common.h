/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_POWER_MANAGER_COMMON_H__
#define __FSL_POWER_MANAGER_COMMON_H__

#include "fsl_device_registers.h"

#if FSL_FEATURE_SOC_LLWU_COUNT
#include "fsl_llwu_hal.h"
#endif
#include "fsl_gpio_driver.h"

/*!
 * @addtogroup power_manager
 * @{
 */

#if FSL_FEATURE_SOC_LLWU_COUNT
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define POWER_MAKE_WAKEUP_PIN(llwuPin,port,pin) ( llwuPin | ( GPIO_MAKE_PIN(port,pin)<<16U) )
#define POWER_GPIO_RESERVED 0xFFFFU
#define POWER_EXTRACT_LLWU_PIN(pin) (llwu_wakeup_pin_t)( ((uint32_t)pin)&0xFFU)
#define POWER_EXTRACT_GPIO_PINNAME(pin) ((((uint32_t)pin)>>16)&0xFFFFU)
#define POWER_LLWU_GPIO_PIN(num)                                \
    POWER_MAKE_WAKEUP_PIN(kLlwuWakeupPin##num,                  \
                          FSL_FEATURE_LLWU_PIN##num##_GPIO_IDX, \
                          FSL_FEATURE_LLWU_PIN##num##_GPIO_PIN)
/*
 * Include the cpu specific API.
 */
/*!
 * @brief Power manager internal wake up modules.
 */
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE
typedef enum _power_wakeup_module
{
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE0
    kPowerManagerWakeupModule0      = kLlwuWakeupModule0,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE1
    kPowerManagerWakeupModule1      = kLlwuWakeupModule1,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE2
    kPowerManagerWakeupModule2      = kLlwuWakeupModule2,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE3
    kPowerManagerWakeupModule3      = kLlwuWakeupModule3,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE4
    kPowerManagerWakeupModule4      = kLlwuWakeupModule4,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE5
    kPowerManagerWakeupModule5      = kLlwuWakeupModule5,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE6
    kPowerManagerWakeupModule6      = kLlwuWakeupModule6,
#endif
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE7
    kPowerManagerWakeupModule7      = kLlwuWakeupModule7,
#endif
    kPowerManagerWakeupMax        = FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE
} power_wakeup_module_t;

#endif

#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN
/*!
 * @brief Power manager external wake up pins.
 */
typedef enum _power_wakeup_pin
{
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN0
    kPowerManagerWakeupPin0 = POWER_LLWU_GPIO_PIN(0),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN1
    kPowerManagerWakeupPin1 = POWER_LLWU_GPIO_PIN(1),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN2
    kPowerManagerWakeupPin2 = POWER_LLWU_GPIO_PIN(2),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN3
    kPowerManagerWakeupPin3 = POWER_LLWU_GPIO_PIN(3),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN4
    kPowerManagerWakeupPin4 = POWER_LLWU_GPIO_PIN(4),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN5
    kPowerManagerWakeupPin5 = POWER_LLWU_GPIO_PIN(5),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN6
    kPowerManagerWakeupPin6 = POWER_LLWU_GPIO_PIN(6),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN7
    kPowerManagerWakeupPin7 = POWER_LLWU_GPIO_PIN(7),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN8
    kPowerManagerWakeupPin8 = POWER_LLWU_GPIO_PIN(8),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN9
    kPowerManagerWakeupPin9 = POWER_LLWU_GPIO_PIN(9),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN10
    kPowerManagerWakeupPin10 = POWER_LLWU_GPIO_PIN(10),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN11
    kPowerManagerWakeupPin11 = POWER_LLWU_GPIO_PIN(11),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN12
    kPowerManagerWakeupPin12 = POWER_LLWU_GPIO_PIN(12),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN13
    kPowerManagerWakeupPin13 = POWER_LLWU_GPIO_PIN(13),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN14
    kPowerManagerWakeupPin14 = POWER_LLWU_GPIO_PIN(14),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN15
    kPowerManagerWakeupPin15 = POWER_LLWU_GPIO_PIN(15),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN16
    kPowerManagerWakeupPin16 = POWER_LLWU_GPIO_PIN(16),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN17
    kPowerManagerWakeupPin17 = POWER_LLWU_GPIO_PIN(17),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN18
    kPowerManagerWakeupPin18 = POWER_LLWU_GPIO_PIN(18),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN19
    kPowerManagerWakeupPin19 = POWER_LLWU_GPIO_PIN(19),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN20
    kPowerManagerWakeupPin20 = POWER_LLWU_GPIO_PIN(20),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN21
    kPowerManagerWakeupPin21 = POWER_LLWU_GPIO_PIN(21),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN22
    kPowerManagerWakeupPin22 = POWER_LLWU_GPIO_PIN(22),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN23
    kPowerManagerWakeupPin23 = POWER_LLWU_GPIO_PIN(23),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN24
    kPowerManagerWakeupPin24 = POWER_LLWU_GPIO_PIN(24),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN25
    kPowerManagerWakeupPin25 = POWER_LLWU_GPIO_PIN(25),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN26
    kPowerManagerWakeupPin26 = POWER_LLWU_GPIO_PIN(26),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN27
    kPowerManagerWakeupPin27 = POWER_LLWU_GPIO_PIN(27),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN28
    kPowerManagerWakeupPin28 = POWER_LLWU_GPIO_PIN(28),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN29
    kPowerManagerWakeupPin29 = POWER_LLWU_GPIO_PIN(29),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN30
    kPowerManagerWakeupPin30 = POWER_LLWU_GPIO_PIN(30),
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN31
    kPowerManagerWakeupPin31 = POWER_LLWU_GPIO_PIN(31),
#endif
}power_wakeup_pin_t;

#endif

#endif
/*! @}*/

#endif /* __FSL_POWER_MANAGER_COMMON_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

