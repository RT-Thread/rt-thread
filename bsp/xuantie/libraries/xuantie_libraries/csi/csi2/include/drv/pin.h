 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     soc.h
 * @brief    For pin
 * @version  V1.0
 * @date     11. Mar 2020
 ******************************************************************************/

#ifndef _DRV_PIN_H_
#define _DRV_PIN_H_

#include <drv/common.h>
#include <drv/gpio.h>
#include <soc.h>

typedef csi_gpio_mode_t csi_pin_mode_t;

typedef enum {
    PIN_SPEED_LV0 = 0U,
    PIN_SPEED_LV1,
    PIN_SPEED_LV2,
    PIN_SPEED_LV3
} csi_pin_speed_t;

typedef enum {
    PIN_DRIVE_LV0 = 0U,
    PIN_DRIVE_LV1,
    PIN_DRIVE_LV2,
    PIN_DRIVE_LV3
} csi_pin_drive_t;

typedef enum{
    PIN_UART_TX = 0U,
    PIN_UART_RX,
    PIN_UART_CTS,
    PIN_UART_RTS
}csi_pin_uart_t;

typedef enum{
    PIN_IIC_SCL = 0U,
    PIN_IIC_SDA
}csi_pin_iic_t;

typedef enum{
    PIN_SPI_MISO = 0U,
    PIN_SPI_MOSI,
    PIN_SPI_SCK,
    PIN_SPI_CS
}csi_pin_spi_t;

typedef enum{
    PIN_I2S_MCLK = 0U,
    PIN_I2S_SCLK,
    PIN_I2S_WSCLK,
    PIN_I2S_SDA,
    PIN_I2S_SDI,
    PIN_I2S_SDO
}csi_pin_i2s_t;

typedef struct {
    pin_name_t  pin_name;
    uint8_t     idx;        ///< ctrl idx.    e.g: ADC0 channel 1, idx = 0, channel = 1
    uint8_t     channel;    ///< channel idx. e.g: same as the previous line
    pin_func_t  pin_func;
} csi_pinmap_t;

extern uint32_t target_pin_to_devidx(pin_name_t pin_name, const csi_pinmap_t *pinmap);
extern uint32_t target_pin_to_channel(pin_name_t pin_name,const csi_pinmap_t *pinmap);
extern pin_name_t target_gpio_to_pin(uint8_t gpio_idx, uint8_t channel,const csi_pinmap_t *pinmap);

/**
  \brief       Set pin mux function
  \param[in]   pin_name    Pin name, defined in soc.h
  \param[in]   pin_func    Pin function, defined in soc.h
  \return      \ref  csi_error_t
*/
csi_error_t csi_pin_set_mux(pin_name_t pin_name, pin_func_t pin_func);

/**
  \brief       Get pin function
  \param[in]   pin_name    Pin name, defined in soc.h
  \return      pin function
*/
pin_func_t csi_pin_get_mux(pin_name_t pin_name);

/**
  \brief       Set pin mode
  \param[in]   pin_name    Pin name, defined in soc.h
  \param[in]   mode        Push/pull mode
  \return      \ref  csi_error_t
*/
csi_error_t csi_pin_mode(pin_name_t pin_name, csi_pin_mode_t mode);

/**
  \brief       Set pin speed
  \param[in]   pin_name    Pin name, defined in soc.h
  \param[in]   speed       Io speed
  \return      \ref  csi_error_t
*/
csi_error_t csi_pin_speed(pin_name_t pin_name, csi_pin_speed_t speed);

/**
  \brief       Set pin drive
  \param[in]   pin_name    Pin name, defined in soc.h
  \param[in]   drive       Io drive
  \return      \ref  csi_error_t
*/
csi_error_t csi_pin_drive(pin_name_t pin_name, csi_pin_drive_t drive);

/**
  \brief       Get ctrl idx by pin
  \param[in]   pin_name    Pin name, defined in soc.h
  \return      idx
*/
__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_gpio_devidx(pin_name_t pin_name)
{
    extern const csi_pinmap_t gpio_pinmap[];
    return target_pin_to_devidx(pin_name, gpio_pinmap);
}

__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_uart_devidx(pin_name_t pin_name)
{
    extern const csi_pinmap_t uart_pinmap[];
    return target_pin_to_devidx(pin_name, uart_pinmap);
}

__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_iic_devidx(pin_name_t pin_name)
{
    extern const csi_pinmap_t iic_pinmap[];
    return target_pin_to_devidx(pin_name, iic_pinmap);
}

__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_spi_devidx(pin_name_t pin_name)
{
    extern const csi_pinmap_t spi_pinmap[];
    return target_pin_to_devidx(pin_name, spi_pinmap);
}

__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_i2s_devidx(pin_name_t pin_name)
{
    extern  const csi_pinmap_t i2s_pinmap[];
    return target_pin_to_devidx(pin_name, i2s_pinmap);
}

/**
  \brief       Get channel by pin
  \param[in]   pin_name    Pin name, defined in soc.h
  \return      channel
*/
__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_adc_channel(pin_name_t pin_name)
{
    extern const csi_pinmap_t adc_pinmap[];
    return target_pin_to_channel(pin_name, adc_pinmap);
}

__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_pwm_channel(pin_name_t pin_name)
{
    extern const csi_pinmap_t pwm_pinmap[];
    return target_pin_to_channel(pin_name, pwm_pinmap);
}

__ALWAYS_STATIC_INLINE uint32_t csi_pin_get_gpio_channel(pin_name_t pin_name)
{
    extern const csi_pinmap_t gpio_pinmap[];
    return target_pin_to_channel(pin_name, gpio_pinmap);
}

/**
  \brief       Get pin name by gpio ctrl idx and channel
  \param[in]   gpio_idx    Idx, defined in soc.h
  \param[in]   channel     Channel, defined in soc.h
  \return      pin name
*/
__ALWAYS_STATIC_INLINE pin_name_t csi_pin_get_pinname_by_gpio(uint8_t gpio_idx, uint8_t channel)
{
    extern const csi_pinmap_t gpio_pinmap[];
    return target_gpio_to_pin(gpio_idx,channel,gpio_pinmap);
}

#endif /* _DRV_PIN_H_ */
