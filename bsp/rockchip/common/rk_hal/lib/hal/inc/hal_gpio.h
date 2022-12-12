/* SPDX-License-Identifier: BSD-3-Clause */
/*
 * Copyright (c) 2020-2021 Rockchip Electronics Co., Ltd.
 */

#include "hal_conf.h"

/** @addtogroup RK_HAL_Driver
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

#include "hal_def.h"
#include "hal_pinctrl.h"

/***************************** MACRO Definition ******************************/
/** @defgroup GPIO_Exported_Definition_Group1 Basic Definition
 *  @{
 */

#ifndef GPIO_VER_ID
#define GPIO_VER_ID (0U)
#endif

#define PIN_NUMBER_PER_BANK (32)

#define GPIO_PIN_SHIFT  (0) /**< Bits 0-4: GPIO Pin number: 0 - 31 */
#define GPIO_PIN_MASK   (0x1f << GPIO_PIN_SHIFT)
#define GPIO_BANK_SHIFT (5) /**< Bits 5-7: GPIO Port number: 0 - 7 */
#define GPIO_BANK_MASK  (0x7 << GPIO_BANK_SHIFT)

#define BANK_PIN(BANK, PIN) ((((BANK) << GPIO_BANK_SHIFT) & GPIO_BANK_MASK) + (((PIN) << GPIO_PIN_SHIFT) & GPIO_PIN_MASK))

/***************************** Structure Definition **************************/
/** GPIO pin level definition */
typedef enum {
    GPIO_LOW,
    GPIO_HIGH
} eGPIO_pinLevel;

/** GPIO pin direction definition */
typedef enum {
    GPIO_IN,
    GPIO_OUT
} eGPIO_pinDirection;

/** GPIO pin debounce definition */
typedef enum {
    GPIO_DEBOUNCE_DIS,
    GPIO_DEBOUNCE_EN
} eGPIO_pinDebounce;

/** GPIO pin interrupt enable definition */
typedef enum {
    GPIO_INT_ENABLE,
    GPIO_INT_DISABLE
} eGPIO_intEnable;

/** GPIO pin interrupt type definition */
typedef enum {
    GPIO_INT_TYPE_NONE         = 0x00000000,
    GPIO_INT_TYPE_EDGE_RISING  = 0x00000001,
    GPIO_INT_TYPE_EDGE_FALLING = 0x00000002,
    GPIO_INT_TYPE_EDGE_BOTH    = (GPIO_INT_TYPE_EDGE_FALLING | GPIO_INT_TYPE_EDGE_RISING),
    GPIO_INT_TYPE_LEVEL_HIGH   = 0x00000004,
    GPIO_INT_TYPE_LEVEL_LOW    = 0x00000008,
    GPIO_INT_TYPE_LEVEL_MASK   = (GPIO_INT_TYPE_LEVEL_LOW | GPIO_INT_TYPE_LEVEL_HIGH),
    GPIO_INT_TYPE_SENSE_MASK   = 0x0000000f,
    GPIO_INT_TYPE_DEFAULT      = GPIO_INT_TYPE_SENSE_MASK,
} eGPIO_intType;

/** GPIO pin interrupt mode definition */
typedef enum {
    GPIO_INT_MODE_EDGE_RISING,
    GPIO_INT_MODE_EDGE_FALLING,
    GPIO_INT_MODE_EDGE_RISING_FALLING,
    GPIO_INT_MODE_LEVEL_HIGH,
    GPIO_INT_MODE_LEVEL_LOW,
    GPIO_INT_MODE_INVALID
} eGPIO_intMode;

#define IS_GPIO_PIN_DIR(ACTION)   (((ACTION) == GPIO_IN) || ((ACTION) == GPIO_OUT))
#define IS_GPIO_PIN_LEVEL(ACTION) (((ACTION) == GPIO_LOW) || ((ACTION) == GPIO_HIGH))

#define IS_GPIO_PIN(PIN)      ((PIN) != 0x00000000U)
#define IS_GPIO_HIGH_PIN(PIN) IS_GPIO_PIN(((PIN) & 0xFFFF0000U))

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_PIN_A0) || \
                              ((PIN) == GPIO_PIN_A1) || \
                              ((PIN) == GPIO_PIN_A2) || \
                              ((PIN) == GPIO_PIN_A3) || \
                              ((PIN) == GPIO_PIN_A4) || \
                              ((PIN) == GPIO_PIN_A5) || \
                              ((PIN) == GPIO_PIN_A6) || \
                              ((PIN) == GPIO_PIN_A7) || \
                              ((PIN) == GPIO_PIN_B0) || \
                              ((PIN) == GPIO_PIN_B1) || \
                              ((PIN) == GPIO_PIN_B2) || \
                              ((PIN) == GPIO_PIN_B3) || \
                              ((PIN) == GPIO_PIN_B4) || \
                              ((PIN) == GPIO_PIN_B5) || \
                              ((PIN) == GPIO_PIN_B6) || \
                              ((PIN) == GPIO_PIN_B7) || \
                              ((PIN) == GPIO_PIN_C0) || \
                              ((PIN) == GPIO_PIN_C1) || \
                              ((PIN) == GPIO_PIN_C2) || \
                              ((PIN) == GPIO_PIN_C3) || \
                              ((PIN) == GPIO_PIN_C4) || \
                              ((PIN) == GPIO_PIN_C5) || \
                              ((PIN) == GPIO_PIN_C6) || \
                              ((PIN) == GPIO_PIN_C7) || \
                              ((PIN) == GPIO_PIN_D0) || \
                              ((PIN) == GPIO_PIN_D1) || \
                              ((PIN) == GPIO_PIN_D2) || \
                              ((PIN) == GPIO_PIN_D3) || \
                              ((PIN) == GPIO_PIN_D4) || \
                              ((PIN) == GPIO_PIN_D5) || \
                              ((PIN) == GPIO_PIN_D6) || \
                              ((PIN) == GPIO_PIN_D7))

/** @} */
/***************************** Function Declare ******************************/
/** @defgroup GPIO_Exported_Definition_Group2 Public Functions Declare.
 *  @{
 */
eGPIO_pinDirection HAL_GPIO_GetPinDirection(struct GPIO_REG *pGPIO, ePINCTRL_GPIO_PINS pin);
eGPIO_pinLevel HAL_GPIO_GetPinLevel(struct GPIO_REG *pGPIO, ePINCTRL_GPIO_PINS pin);
eGPIO_pinLevel HAL_GPIO_GetPinData(struct GPIO_REG *pGPIO, ePINCTRL_GPIO_PINS pin);
uint32_t HAL_GPIO_GetBankLevel(struct GPIO_REG *pGPIO);

HAL_Status HAL_GPIO_SetPinLevel(struct GPIO_REG *pGPIO, ePINCTRL_GPIO_PINS pin, eGPIO_pinLevel level);
HAL_Status HAL_GPIO_SetPinDirection(struct GPIO_REG *pGPIO, ePINCTRL_GPIO_PINS pin, eGPIO_pinDirection direction);
HAL_Status HAL_GPIO_SetIntType(struct GPIO_REG *pGPIO, ePINCTRL_GPIO_PINS pin, eGPIO_intType mode);

HAL_Status HAL_GPIO_SetPinsLevel(struct GPIO_REG *pGPIO, uint32_t mPins, eGPIO_pinLevel level);
HAL_Status HAL_GPIO_SetPinsDirection(struct GPIO_REG *pGPIO, uint32_t mPins, eGPIO_pinDirection direction);

void HAL_GPIO_EnableIRQ(struct GPIO_REG *pGPIO, ePINCTRL_GPIO_PINS pin);
void HAL_GPIO_DisableIRQ(struct GPIO_REG *pGPIO, ePINCTRL_GPIO_PINS pin);
void HAL_GPIO_IRQHandler(struct GPIO_REG *pGPIO, eGPIO_bankId bank);

/* The parameter pin for this function is special, it's 0~31. */
void HAL_GPIO_IRQDispatch(eGPIO_bankId bank, uint32_t pin);

/** @} */

#endif
/** @} */

/** @} */
