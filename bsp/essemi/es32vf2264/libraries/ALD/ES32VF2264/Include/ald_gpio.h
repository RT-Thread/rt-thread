/**
  *********************************************************************************
  *
  * @file    ald_gpio.h
  * @brief   Header file of GPIO module driver
  *
  * @version V1.0
  * @date    30 Jan. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          30 Jan. 2023    Lisq            The first version
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
  **********************************************************************************
  */

#ifndef __ALD_GPIO_H__
#define __ALD_GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

#include "ald_utils.h"


/** @addtogroup ALD
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/**
  * @defgroup GPIO_Public_Macros GPIO Public Macros
  * @{
  */
#define ALD_GPIO_PIN_0      (0x1U)
#define ALD_GPIO_PIN_1      (0x2U)
#define ALD_GPIO_PIN_2      (0x4U)
#define ALD_GPIO_PIN_3      (0x8U)
#define ALD_GPIO_PIN_4      (0x10U)
#define ALD_GPIO_PIN_5      (0x20U)
#define ALD_GPIO_PIN_6      (0x40U)
#define ALD_GPIO_PIN_7      (0x80U)
#define ALD_GPIO_PIN_8      (0x100U)
#define ALD_GPIO_PIN_9      (0x200U)
#define ALD_GPIO_PIN_10     (0x400U)
#define ALD_GPIO_PIN_11     (0x800U)
#define ALD_GPIO_PIN_12     (0x1000U)
#define ALD_GPIO_PIN_13     (0x2000U)
#define ALD_GPIO_PIN_14     (0x4000U)
#define ALD_GPIO_PIN_15     (0x8000U)
#define ALD_GPIO_PIN_ALL    (0xFFFF)

/* Toggle IO */
#define ALD_GPIOA_TOGGLE_PIN(x)    (GPIOA->BIR = (x))
#define ALD_GPIOB_TOGGLE_PIN(x)    (GPIOB->BIR = (x))
#define ALD_GPIOC_TOGGLE_PIN(x)    (GPIOC->BIR = (x))
#define ALD_GPIOD_TOGGLE_PIN(x)    (GPIOD->BIR = (x))

/* Read IO level */
#define ALD_GPIOA_READ_PIN(x)      ((GPIOA->DIN & (x)) ? 1 : 0)
#define ALD_GPIOB_READ_PIN(x)      ((GPIOB->DIN & (x)) ? 1 : 0)
#define ALD_GPIOC_READ_PIN(x)      ((GPIOC->DIN & (x)) ? 1 : 0)
#define ALD_GPIOD_READ_PIN(x)      ((GPIOD->DIN & (x)) ? 1 : 0)

/* Set IO as high */
#define ALD_GPIOA_SET_PIN(x)       (GPIOA->BSRR = (x))
#define ALD_GPIOB_SET_PIN(x)       (GPIOB->BSRR = (x))
#define ALD_GPIOC_SET_PIN(x)       (GPIOC->BSRR = (x))
#define ALD_GPIOD_SET_PIN(x)       (GPIOD->BSRR = (x))

/* Set IO as low */
#define ALD_GPIOA_RESET_PIN(x)     (GPIOA->BSRR = ((x) << 16))
#define ALD_GPIOB_RESET_PIN(x)     (GPIOB->BSRR = ((x) << 16))
#define ALD_GPIOC_RESET_PIN(x)     (GPIOC->BSRR = ((x) << 16))
#define ALD_GPIOD_RESET_PIN(x)     (GPIOD->BSRR = ((x) << 16))
/**
  * @}
  */

/**
  * @defgroup GPIO_Public_Types GPIO Public Types
  * @{
  */

/**
  * @brief GPIO mode
  */
typedef enum {
    ALD_GPIO_MODE_CLOSE  = 0x0U,    /**< Digital close  Analog open */
    ALD_GPIO_MODE_INPUT  = 0x1U,    /**< Input */
    ALD_GPIO_MODE_OUTPUT = 0x2U,    /**< Output */
} ald_gpio_mode_t;

/**
  * @brief GPIO open-drain or push-pull
  */
typedef enum {
    ALD_GPIO_PUSH_PULL   = 0x0U,    /**< Push-Pull */
    ALD_GPIO_OPEN_DRAIN  = 0x2U,    /**< Open-Drain. Can't output high level */
} ald_gpio_od_t;

/**
  * @brief GPIO push-up or push-down
  */
typedef enum {
    ALD_GPIO_FLOATING     = 0x0U,   /**< Floating */
    ALD_GPIO_PUSH_UP      = 0x1U,   /**< Push-Up */
    ALD_GPIO_PUSH_DOWN    = 0x2U,   /**< Push-Down */
    ALD_GPIO_PUSH_UP_DOWN = 0x3U,   /**< Push-Up and Push-Down */
} ald_gpio_push_t;

/**
  * @brief GPIO output drive
  */
typedef enum {
    ALD_GPIO_OUT_DRIVE_NORMAL = 0x0U,   /**< Normal current flow */
    ALD_GPIO_OUT_DRIVE_STRONG = 0x1U,   /**< Strong current flow */
} ald_gpio_out_drive_t;

/**
  * @brief GPIO filter
  */
typedef enum {
    ALD_GPIO_FILTER_DISABLE = 0x0U, /**< Disable filter */
    ALD_GPIO_FILTER_ENABLE  = 0x1U, /**< Enable filter */
} ald_gpio_filter_t;

/**
  * @brief GPIO type
  */
typedef enum {
    ALD_GPIO_TYPE_CMOS = 0x0U,  /**< CMOS Type */
    ALD_GPIO_TYPE_TTL  = 0x1U,  /**< TTL Type */
} ald_gpio_type_t;

/**
  * @brief GPIO functions
  */
typedef enum {
    ALD_GPIO_FUNC_0 = 0U,   /**< function #0 */
    ALD_GPIO_FUNC_1 = 1U,   /**< function #1 */
    ALD_GPIO_FUNC_2 = 2U,   /**< function #2 */
    ALD_GPIO_FUNC_3 = 3U,   /**< function #3 */
    ALD_GPIO_FUNC_4 = 4U,   /**< function #4 */
    ALD_GPIO_FUNC_5 = 5U,   /**< function #5 */
    ALD_GPIO_FUNC_6 = 6U,   /**< function #6 */
    ALD_GPIO_FUNC_7 = 7U,   /**< function #7 */
} ald_gpio_func_t;

/**
  * @brief GPIO Init Structure definition
  */
typedef struct {
    ald_gpio_mode_t mode;   /**< Specifies the operating mode for the selected pins.
                     This parameter can be any value of @ref gpio_mode_t */
    ald_gpio_od_t od;   /**< Specifies the Open-Drain or Push-Pull for the selected pins.
                     This parameter can be a value of @ref gpio_od_t */
    ald_gpio_push_t pupd;   /**< Specifies the Pull-up or Pull-Down for the selected pins.
                     This parameter can be a value of @ref gpio_push_t */
    ald_gpio_out_drive_t odrv;  /**< Specifies the output MOS driver for the selected pins.
                     This parameter can be a value of @ref gpio_out_drive_t */
    ald_gpio_filter_t flt;  /**< Specifies the input filter for the selected pins.
                     This parameter can be a value of @ref gpio_filter_t */
    ald_gpio_type_t type;   /**< Specifies the type for the selected pins.
                     This parameter can be a value of @ref gpio_type_t */
    ald_gpio_func_t func;   /**< Specifies the function for the selected pins.
                     This parameter can be a value of @ref gpio_func_t */
} ald_gpio_init_t;

/**
  * @brief EXTI trigger style
  */
typedef enum {
    ALD_EXTI_TRIGGER_RISING_EDGE   = 0U,    /**< Rising edge trigger */
    ALD_EXTI_TRIGGER_TRAILING_EDGE = 1U,    /**< Trailing edge trigger */
    ALD_EXTI_TRIGGER_BOTH_EDGE     = 2U,    /**< Rising and trailing edge trigger */
} ald_exti_trigger_style_t;

/**
  * @brief EXTI Init Structure definition
  */
typedef struct {
    type_func_t filter;     /**< Enable filter. */
    uint8_t filter_time;    /**< Filter duration */
} ald_exti_init_t;
/**
  * @}
  */

/**
  * @defgroup GPIO_Private_Macros GPIO Private Macros
  * @{
  */
#define ALD_PIN_MASK    0xFFFFU
#define ALD_UNLOCK_KEY  0x55AAU

#define IS_GPIO_PIN(x)  ((((x) & (uint16_t)0x00) == 0) && ((x) != (uint16_t)0x0))
#define IS_GPIO_PORT(GPIOx) ((GPIOx == GPIOA) || \
                 (GPIOx == GPIOB) || \
                 (GPIOx == GPIOC) || \
                 (GPIOx == GPIOD))
#define IS_GPIO_MODE(x)     (((x) == ALD_GPIO_MODE_CLOSE) || \
                                 ((x) == ALD_GPIO_MODE_INPUT) || \
                                 ((x) == ALD_GPIO_MODE_OUTPUT))
#define IS_GPIO_OD(x)       (((x) == ALD_GPIO_PUSH_PULL)  || \
                                 ((x) == ALD_GPIO_OPEN_DRAIN))
#define IS_GPIO_PUPD(x)     (((x) == ALD_GPIO_FLOATING)  || \
                                 ((x) == ALD_GPIO_PUSH_UP)   || \
                                 ((x) == ALD_GPIO_PUSH_DOWN) || \
                                 ((x) == ALD_GPIO_PUSH_UP_DOWN))
#define IS_GPIO_ODRV(x)     (((x) == ALD_GPIO_OUT_DRIVE_NORMAL) || \
                                 ((x) == ALD_GPIO_OUT_DRIVE_STRONG))
#define IS_GPIO_FLT(x)      (((x) == ALD_GPIO_FILTER_DISABLE) || \
                                 ((x) == ALD_GPIO_FILTER_ENABLE))
#define IS_GPIO_TYPE(x)     (((x) == ALD_GPIO_TYPE_TTL) || \
                                 ((x) == ALD_GPIO_TYPE_CMOS))
#define IS_TRIGGER_STYLE(x) (((x) == ALD_EXTI_TRIGGER_RISING_EDGE)   || \
                                 ((x) == ALD_EXTI_TRIGGER_TRAILING_EDGE) || \
                                 ((x) == ALD_EXTI_TRIGGER_BOTH_EDGE))
#define IS_GPIO_FUNC(x)     ((x) <= 7)
/**
  * @}
  */

/** @addtogroup GPIO_Public_Functions
  * @{
  */

/** @addtogroup GPIO_Public_Functions_Group1
  * @{
  */
void ald_gpio_init(GPIO_TypeDef *GPIOx, uint16_t pin, ald_gpio_init_t *init);
void ald_gpio_init_default(GPIO_TypeDef *GPIOx, uint16_t pin);
void ald_gpio_func_default(GPIO_TypeDef *GPIOx);
void ald_gpio_exti_init(GPIO_TypeDef *GPIOx, uint16_t pin, ald_exti_init_t *init);
/**
  * @}
  */

/** @addtogroup GPIO_Public_Functions_Group2
  * @{
  */
uint8_t ald_gpio_read_pin(GPIO_TypeDef *GPIOx, uint16_t pin);
void ald_gpio_write_pin(GPIO_TypeDef *GPIOx, uint16_t pin, uint8_t val);
void ald_gpio_toggle_pin(GPIO_TypeDef *GPIOx, uint16_t pin);
void ald_gpio_toggle_dir(GPIO_TypeDef *GPIOx, uint16_t pin);
void ald_gpio_lock_pin(GPIO_TypeDef *GPIOx, uint16_t pin);
uint16_t ald_gpio_read_port(GPIO_TypeDef *GPIOx);
void ald_gpio_write_port(GPIO_TypeDef *GPIOx, uint16_t val);
/**
  * @}
  */

/** @addtogroup GPIO_Public_Functions_Group3
  * @{
  */
void ald_gpio_exti_interrupt_config(uint16_t pin, ald_exti_trigger_style_t style, type_func_t status);
type_func_t ald_gpio_exti_get_ie_status(uint16_t pin);
flag_status_t ald_gpio_exti_get_flag_status(uint16_t pin);
void ald_gpio_exti_clear_flag_status(uint16_t pin);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __ALD_GPIO_H__ */
