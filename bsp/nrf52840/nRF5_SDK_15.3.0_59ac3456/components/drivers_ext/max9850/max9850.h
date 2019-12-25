/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef MAX9850_H__
#define MAX9850_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "nrf_drv_twi.h"

/**
 * @brief Default MAX9850 TWI configuration
 *
 * @param scl_pin   SCL pin number
 * @param sda_pin   SDA pin number
 */
#define MAX9850_DEFAULT_TWI_CONFIG(scl_pin, sda_pin)     {      \
        .scl                = scl_pin,                          \
        .sda                = sda_pin,                          \
        .frequency          = NRF_DRV_TWI_FREQ_100K,            \
        .interrupt_priority = APP_IRQ_PRIORITY_HIGH,            \
        .clear_bus_init     = false,                            \
        .hold_bus_uninit    = false                             \
}

/**
 * @brief   Internal MAX9850 register map
 * */
typedef struct {
    uint8_t status_a;           //!< Status register A (R)
    uint8_t status_b;           //!< Status register B (R)
    uint8_t volume;             //!< Volume control (RW)
    uint8_t general_purpose;    //!< General purpose register (RW)
    uint8_t interrupt_enable;   //!< Interrupt enable (RW)
    uint8_t enable;             //!< Enable register (RW)
    uint8_t clock;              //!< Clock control (RW)
    uint8_t charge_pump;        //!< Charge pump (RW)
    uint8_t lrclk_msb;          //!< LRCLK MSB register (RW)
    uint8_t lrclk_lsb;          //!< LRCLK LSB register (RW)
    uint8_t digital_audio;      //!< Digital audio (RW)
} max9850_regmap_t;

/**
 * @brief MAX9850 register map after reset
 * */
#define MAX9850_DEFAULT_REGMAP()    {   \
        .status_a = 0,                  \
        .status_b = 0,                  \
        .volume = 0x0C,                 \
        .general_purpose = 0,           \
        .interrupt_enable = 0,          \
        .enable = 0,                    \
        .clock = 0,                     \
        .charge_pump = 0,               \
        .lrclk_msb = 0,                 \
        .lrclk_lsb = 0,                 \
        .digital_audio = 0,             \
}

/**
 * @brief   Helper macro for creating MAX9850 TWI address
 * */
#define MAX9850_TWI_ADDR(v) (0x10 + (v))


/**
 * @brief MAX9850 configuration
 * */
typedef struct {
    nrf_drv_twi_t        twi;       //!< TWI instance
    nrf_drv_twi_config_t twi_cfg;   //!< TWI configuration
    max9850_regmap_t     regmap;    //!< MAX9850 register map
    uint8_t              twi_addr;  //!< MAX9850 TWI address
} max9850_config_t;

/**
 * @brief Initializes MAX9850 IC
 *
 * @param p_max9850 MAX9850 configuration
 *
 * @return Standard error code
 * */
ret_code_t max9850_init(max9850_config_t const * p_max9850);


#ifdef __cplusplus
}
#endif

#endif /* MAX9850_H__ */
