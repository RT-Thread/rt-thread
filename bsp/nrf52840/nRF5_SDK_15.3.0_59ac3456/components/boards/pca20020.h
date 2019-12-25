/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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
#ifndef PCA20020_H
#define PCA20020_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

#define NRF_NUM_GPIO_PINS        32

#define OSC_XL1                  0
#define OSC_XL2                  1
#define ANA_DIG0                 2
#define ANA_DIG1                 3
#define ANA_DIG2                 4
#define IOEXT_OSCIO              5
#define MPU_INT                  6
#define TWI_SDA                  7
#define TWI_SCL                  8
#define NFC1                     9
#define NFC2                     10
#define BUTTON                   11
#define LIS_INT1                 12
#define USB_DETECT               13
#define TWI_SDA_EXT              14
#define TWI_SCL_EXT              15
#define SX_RESET                 16
#define BAT_CHG_STAT             17
#define MOS_1                    18
#define MOS_2                    19
#define MOS_3                    20
#define MOS_4                    21
#define CCS_INT                  22
#define LPS_INT                  23
#define HTS_INT                  24
#define MIC_DOUT                 25
#define MIC_CLK                  26
#define SPEAKER                  27
#define BATTERY                  28
#define SPK_PWR_CTRL             29
#define VDD_PWR_CTRL             30
#define BH_INT                   31

// Button config
#define BUTTONS_NUMBER           1
#define BUTTON_START             BUTTON
#define BUTTON_STOP              BUTTON
#define BUTTON_PULL              NRF_GPIO_PIN_PULLUP
#define BUTTONS_ACTIVE_STATE     0
#define BUTTONS_LIST             { BUTTON }

#define LEDS_NUMBER              0

// IO expander pins
#define SX_IOEXT_NUM_PINS        16

#define SX_IOEXT_0               0
#define SX_IOEXT_1               1
#define SX_IOEXT_2               2
#define SX_IOEXT_3               3
#define SX_BAT_MON_EN            4
#define SX_LIGHTWELL_G           5
#define SX_LIGHTWELL_B           6
#define SX_LIGHTWELL_R           7
#define SX_MPU_PWR_CTRL          8
#define SX_MIC_PWR_CTRL          9
#define SX_CCS_PWR_CTRL          10
#define SX_CCS_RESET             11
#define SX_CCS_WAKE              12
#define SX_SENSE_LED_R           13
#define SX_SENSE_LED_G           14
#define SX_SENSE_LED_B           15

// Uart configuration for testing
#define RX_PIN_NUMBER            ANA_DIG1
#define TX_PIN_NUMBER            ANA_DIG0
#define CTS_PIN_NUMBER           0
#define RTS_PIN_NUMBER           0
#define HWFC                     false


#ifdef __cplusplus
}
#endif

#endif // PCA20020_H
