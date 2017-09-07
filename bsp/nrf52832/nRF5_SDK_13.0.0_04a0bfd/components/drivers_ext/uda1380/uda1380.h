/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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
#ifndef UDA1380_H__
#define UDA1380_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "nrf_drv_twi.h"


#define UDA1380_REG_CLK     0x00
#define UDA1380_REG_I2S     0x01
#define UDA1380_REG_PWR     0x02
#define UDA1380_REG_AMIX    0x03
#define UDA1380_REG_HPA     0x04

#define UDA1380_REG_VOL     0x10
#define UDA1380_REG_MIX_VOL 0x11
#define UDA1380_REG_PPROC   0x12
#define UDA1380_REG_DEEMP   0x13
#define UDA1380_REG_MIXER   0x14

#define UDA1380_REG_RESET   0x7F


/**
 * @brief Default UDA1380 TWI configuration
 *
 * @param scl_pin   SCL pin number
 * @param sda_pin   SDA pin number
 */
#define UDA1380_DEFAULT_TWI_CONFIG(scl_pin, sda_pin)     {      \
        .scl                = scl_pin,                          \
        .sda                = sda_pin,                          \
        .frequency          = NRF_TWI_FREQ_100K,                \
        .interrupt_priority = APP_IRQ_PRIORITY_HIGH,            \
        .clear_bus_init     = false,                            \
        .hold_bus_uninit    = false                             \
}

/**
 * @brief UDA1380 register descriptor
 * */
typedef struct {
    uint8_t addr;   //!< Internal register address
    uint8_t val[2]; //!< Internal register value
} uda1380_reg_t;

#define UDA1380_REG_INIT(address, value)   {        \
        .addr = address,                            \
        .val = {(value) / 256, (value) & 0xFF},     \
}

/**
 * @brief   UDA1380 TWI bus address*/
#define UDA1380_TWI_ADDRESS (0x18)

/**
 * @brief UDA1380 interface
 * */
typedef struct {
    nrf_drv_twi_t        twi;       //!< TWI instance
    nrf_drv_twi_config_t twi_cfg;   //!< TWI configuration
    uint8_t              twi_addr;  //!< UDA1380 TWI address
} uda1380_iface_t;


/**
 * @brief Initializes UDA1380 codec IC
 *
 * @param p_iface       Communication interface
 * @param p_reg_config  Configuration registers
 * @param reg_size      Number of configuration registers
 *
 * @return Standard error code
 * */
ret_code_t uda1380_init(uda1380_iface_t const * p_iface,
                        uda1380_reg_t const * p_reg_config,
                        size_t reg_size);

/**
 * @brief Enable UDA1380 codec
 *
 * @return Standard error code
 * */
ret_code_t uda1380_enable(uda1380_iface_t const * p_iface);


/**
 * @brief Disable UDA1380 codec
 *
 * @return Standard error code
 * */
ret_code_t uda1380_disable(uda1380_iface_t const * p_iface);

#ifdef __cplusplus
}
#endif

#endif /* UDA1380_H__ */
