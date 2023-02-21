/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__

#include "hal_common.h"

/*!
 * @addtogroup GPIO
 * @{
 */

/*!
 * @addtogroup GPIO_PIN
 * @brief GPIO pin mask codes.
 * @{
 */
#define GPIO_PIN_0    (0x0001u) /*!< Pin 0 selected. */
#define GPIO_PIN_1    (0x0002u) /*!< Pin 1 selected. */
#define GPIO_PIN_2    (0x0004u) /*!< Pin 2 selected. */
#define GPIO_PIN_3    (0x0008u) /*!< Pin 3 selected. */
#define GPIO_PIN_4    (0x0010u) /*!< Pin 4 selected. */
#define GPIO_PIN_5    (0x0020u) /*!< Pin 5 selected. */
#define GPIO_PIN_6    (0x0040u) /*!< Pin 6 selected. */
#define GPIO_PIN_7    (0x0080u) /*!< Pin 7 selected. */
#define GPIO_PIN_8    (0x0100u) /*!< Pin 8 selected. */
#define GPIO_PIN_9    (0x0200u) /*!< Pin 9 selected. */
#define GPIO_PIN_10   (0x0400u) /*!< Pin 10 selected. */
#define GPIO_PIN_11   (0x0800u) /*!< Pin 11 selected. */
#define GPIO_PIN_12   (0x1000u) /*!< Pin 12 selected. */
#define GPIO_PIN_13   (0x2000u) /*!< Pin 13 selected. */
#define GPIO_PIN_14   (0x4000u) /*!< Pin 14 selected. */
#define GPIO_PIN_15   (0x8000u) /*!< Pin 15 selected. */
#define GPIO_PINS_ALL (0xFFFFu) /*!< All pins selected. */
/*!
 * @}
 */

/*!
 * @addtogroup GPIO_AF
 * @brief GPIO pin alternative function.
 * @{
 */
#define GPIO_AF_0     (0x00u)   /*!< Alternative function 0. */
#define GPIO_AF_1     (0x01u)   /*!< Alternative function 1. */
#define GPIO_AF_2     (0x02u)   /*!< Alternative function 2. */
#define GPIO_AF_3     (0x03u)   /*!< Alternative function 3. */
#define GPIO_AF_4     (0x04u)   /*!< Alternative function 4. */
#define GPIO_AF_5     (0x05u)   /*!< Alternative function 5. */
#define GPIO_AF_6     (0x06u)   /*!< Alternative function 6. */
#define GPIO_AF_7     (0x07u)   /*!< Alternative function 7. */
#define GPIO_AF_8     (0x08u)   /*!< Alternative function 8. */
#define GPIO_AF_9     (0x09u)   /*!< Alternative function 9. */
#define GPIO_AF_10    (0x0Au)   /*!< Alternative function 10. */
#define GPIO_AF_11    (0x0Bu)   /*!< Alternative function 11. */
#define GPIO_AF_12    (0x0Cu)   /*!< Alternative function 12. */
#define GPIO_AF_13    (0x0Du)   /*!< Alternative function 13. */
#define GPIO_AF_14    (0x0Eu)   /*!< Alternative function 14. */
#define GPIO_AF_15    (0x0Fu)   /*!< Alternative function 15. */
/*!
 * @}
 */

/*!
 * @brief GPIO maximum speed type.
 */
typedef enum
{
    GPIO_Speed_50MHz = 1u,  /*!< Maximum speed is 50MHz. */
    GPIO_Speed_20MHz = 2u,  /*!< Maximum speed is 20MHz. */
    GPIO_Speed_10MHz = 3u,  /*!< Maximum speed is 10MHz. */
} GPIO_Speed_Type;

/*!
* @brief Port input / output mode.
*/
typedef enum
{
    GPIO_PinMode_In_Analog      = 0x00u,  /*!< Analog input. */
    GPIO_PinMode_In_Floating    = 0x04u,  /*!< Floating input. */
    GPIO_PinMode_In_PullDown    = 0x28u,  /*!< Pull down input. */
    GPIO_PinMode_In_PullUp      = 0x48u,  /*!< Pull up input. */
    GPIO_PinMode_Out_OpenDrain  = 0x14u,  /*!< Universal open drain output. */
    GPIO_PinMode_Out_PushPull   = 0x10u,  /*!< Universal push-pull output. */
    GPIO_PinMode_AF_OpenDrain   = 0x1Cu,  /*!< Multiplex open drain output. */
    GPIO_PinMode_AF_PushPull    = 0x18u,  /*!< Multiplexed push-pull output. */
} GPIO_PinMode_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref GPIO_Init() to initialize the GPIO module.
 */
typedef struct
{
    uint16_t           Pins;    /*!< GPIO operating pins. */
    GPIO_Speed_Type    Speed;   /*!< GPIO pin speed mode. */
    GPIO_PinMode_Type  PinMode; /*!< GPIO pin input / output functional mode. */
} GPIO_Init_Type;

/*!
 * @brief Initialize the GPIO module.
 *
 * @param GPIOx GPIO instance.
 * @param init Pointer to the initialization structure. See to @ref GPIO_Init_Type.
 * @return None.
 */
void GPIO_Init(GPIO_Type * GPIOx, GPIO_Init_Type * init);

/*!
 * @brief Set the specified data port bit.
 *
 * @param GPIOx GPIO instance.
 * @param pins GPIO operating pins. See to @ref GPIO_PIN.
 * @return None.
 */
void GPIO_SetBits(GPIO_Type * GPIOx, uint16_t pins);

/*!
 * @brief Clear the specified data port bit.
 *
 * @param GPIOx GPIO instance.
 * @param pins GPIO operating pins. See to @ref GPIO_PIN.
 * @return None.
 */
void GPIO_ClearBits(GPIO_Type * GPIOx, uint16_t pins);

/*!
 * @brief Writes 0 or 1 to the specified bit.
 *
 * @param GPIOx GPIO instance.
 * @param pins GPIO operating pins. See to @ref GPIO_PIN.
 * @param val Decide whether to set or clear.
 * @return None.
 */
void GPIO_WriteBit(GPIO_Type * GPIOx, uint16_t pins, uint16_t val);

/*!
 * @brief Write 0 or 1 for multiple I/O ports.
 *
 * @param GPIOx GPIO instance.
 * @param val Decide whether to set or clear.
 * @return None.
 */
void GPIO_WriteBits(GPIO_Type * GPIOx, uint16_t val);

/*!
 * @brief Keep the set I/O configuration can not be changed.
 *
 * @param GPIOx GPIO instance.
 * @param pins GPIO operating pins. See to @ref GPIO_PIN.
 * @param enable_lock enable 'true' to enable the lock, 'false' to disable the lock.
 * @return None.
 */
void GPIO_PinLock(GPIO_Type * GPIOx, uint16_t pins, bool enable_lock);

/*!
 * @brief Lock the corresponding bit of the select port configuration register.
 *
 * @param GPIOx GPIO instance.
 * @param pins GPIO operating pins. See to @ref GPIO_PIN.
 * @return None.
 */
void GPIO_PinLockConf(GPIO_Type * GPIOx, uint16_t pins);

/*!
 * @brief Read the value once entered before by the specified pin.
 *
 * @param GPIOx GPIO instance.
 * @param pins GPIO operating pins. See to @ref GPIO_PIN.
 * @return Status of a pin's logic level, 0 for low level or 1 for high level.
 */
bool GPIO_ReadInDataBit(GPIO_Type * GPIOx, uint16_t pins);

/*!
 * @brief Read the value previously output by the specified pin.
 *
 * @param GPIOx GPIO instance.
 * @param pins GPIO operating pins. See to @ref GPIO_PIN.
 * @return Status of a pin's logic level, 0 for low level or 1 for high level.
 */
bool GPIO_ReadOutDataBit(GPIO_Type * GPIOx, uint16_t pins);

/*!
 * @brief Read the specified GPIO port input.
 *
 * @param GPIOx GPIO instance.
 * @return A hexadecimal number.
 */
uint16_t GPIO_ReadInData(GPIO_Type * GPIOx);

/*!
 * @brief Read the specified GPIO port output.
 *
 * @param GPIOx GPIO instance.
 * @return A hexadecimal number.
 */
uint16_t GPIO_ReadOutData(GPIO_Type * GPIOx);

/*!
 * @brief Pin alternate function configuration of GPIO.
 *
 * @param GPIOx GPIO instance.
 * @param pins GPIO operating pins. See to @ref GPIO_PIN.
 * @param alternate_function Reuse the unified I/O port, but the function is different.
 * @return None.
 */
void GPIO_PinAFConf(GPIO_Type* GPIOx, uint16_t pins, uint8_t alternate_function);

/*!
 * @}
 */

#endif /* __HAL_GPIO_H__ */

