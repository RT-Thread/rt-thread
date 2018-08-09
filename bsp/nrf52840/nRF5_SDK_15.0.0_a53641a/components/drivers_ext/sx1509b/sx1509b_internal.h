/**
 * Copyright (c) 2017 - 2018, Nordic Semiconductor ASA
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
#ifndef SX1509B_INTERNAL_H
#define SX1509B_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Device and IO banks registers.
 */
typedef enum
{
    SX1509B_REG_INPUT_DISABLE_B,
    SX1509B_REG_INPUT_DISABLE_A,
    SX1509B_REG_LONG_SLEW_B,
    SX1509B_REG_LONG_SLEW_A,
    SX1509B_REG_LOW_DRIVE_B,
    SX1509B_REG_LOW_DRIVE_A,
    SX1509B_REG_PULL_UP_B,
    SX1509B_REG_PULL_UP_A,
    SX1509B_REG_PULL_DOWN_B,
    SX1509B_REG_PULL_DOWN_A,
    SX1509B_REG_OPEN_DRAIN_B,
    SX1509B_REG_OPEN_DRAIN_A,
    SX1509B_REG_POLARITY_B,
    SX1509B_REG_POLARITY_A,
    SX1509B_REG_DIR_B,
    SX1509B_REG_DIR_A,
    SX1509B_REG_DATA_B,
    SX1509B_REG_DATA_A,
    SX1509B_REG_INT_MASK_B,
    SX1509B_REG_INT_MASK_A,
    SX1509B_REG_SENSE_H_B,
    SX1509B_REG_SENSE_L_B,
    SX1509B_REG_SENSE_H_A,
    SX1509B_REG_SENSE_L_A,
    SX1509B_REG_INT_SRC_B,
    SX1509B_REG_INT_SRC_A,
    SX1509B_REG_EVENT_STATUS_B,
    SX1509B_REG_EVENT_STATUS_A,
    SX1509B_REG_LEVEL_SHIFTER_1,
    SX1509B_REG_LEVEL_SHIFTER_2,
    SX1509B_REG_CLOCK,
    SX1509B_REG_MISC,
    SX1509B_REG_LED_DRV_ENABLE_B,
    SX1509B_REG_LED_DRV_ENABLE_A,
    SX1509B_REG_DEBOUNCE_CONFIG,
    SX1509B_REG_DEBOUNCE_EN_B,
    SX1509B_REG_DEBOUNCE_EN_A,
    SX1509B_REG_KEY_CONFIG_1,
    SX1509B_REG_KEY_CONFIG_2,
    SX1509B_REG_KEY_DATA_1,
    SX1509B_REG_KEY_DATA_2,
    SX1509B_REG_COUNT
} sx1509b_registers_t;

#define SX1509B_INNER_PIN_COUNT         16
#define SX1509B_INNER_NEXT_BANK         8

#define SX1509B_INNER_PORT_COUNT        2
#define SX1509B_INNER_SENSE_REG_NUM     4
#define SX1509B_INNER_RESET_BYTE1       0x12
#define SX1509B_INNER_RESET_BYTE2       0x34
/**
 * @brief LED Driver registers.
 */
#define SX1509B_REG_LED_BANK_A_START     0x29
#define SX1509B_REG_LED_FADE_A_START     0x35
#define SX1509B_REG_LED_BANK_B_START     0x49
#define SX1509B_REG_LED_FADE_B_START     0x55

#define SX1509B_LED_DRIVER_TIME_REG_LEN  3
#define SX1509B_LED_DRIVER_FADE_REG_LEN  5
#define SX1509B_LED_DRIVER_TIME_REG_NUM  ((SX1509B_REG_LED_FADE_A_START         \
                                           - SX1509B_REG_LED_BANK_A_START)      \
                                          / SX1509B_LED_DRIVER_TIME_REG_LEN)

#define SX1509B_LED_DRIVER_FADE_REG_NUM  ((SX1509B_REG_LED_BANK_B_START         \
                                           - SX1509B_REG_LED_FADE_A_START)      \
                                          / SX1509B_LED_DRIVER_FADE_REG_LEN)

/**
 * @brief Clock register bitmasks.
 */

// Bitmasks for osc src.
#define SX1509B_OSC_SRC_POS             5
#define SX1509B_OSC_SRC_MASK            (3 << SX1509B_OSC_SRC_POS)

// Bitmasks for oscio pin.
#define SX1509B_OSCIO_PIN_POS           4
#define SX1509B_OSCIO_PIN_MASK          (1 << SX1509B_OSCIO_PIN_POS)

// Bitmasks for oscout freq.
#define SX1509B_OSCOUT_FREQ_POS         0
#define SX1509B_OSCOUT_FREQ_MASK        (0x0F << SX1509B_OSCOUT_FREQ_POS)


/**
 * @brief Miscellaneous register bitmasks.
 */

// Bitmasks for led mode b.
#define SX1509B_LED_MODE_B_POS          7
#define SX1509B_LED_MODE_B_MASK         (1 << SX1509B_LED_MODE_B_POS)

// Bitmasks for led freq.
#define SX1509B_LED_FREQ_POS            4
#define SX1509B_LED_FREQ_MASK           (7 << SX1509B_LED_FREQ_POS)

// Bitmasks for led mode a.
#define SX1509B_LED_MODE_A_POS          3
#define SX1509B_LED_MODE_A_MASK         (1 << SX1509B_LED_MODE_A_POS)

// Bitmasks for nreset pin.
#define SX1509B_NRESET_PIN_POS          2
#define SX1509B_NRESET_PIN_MASK         (1 << SX1509B_NRESET_PIN_POS)

// Bitmasks for auto incr.
#define SX1509B_AUTO_INCR_POS           1
#define SX1509B_AUTO_INCR_MASK          (1 << SX1509B_AUTO_INCR_POS)

// Bitmasks for auto clear nint.
#define SX1509B_AUTO_CLEAR_NINT_POS     0
#define SX1509B_AUTO_CLEAR_NINT_MASK    (1 << SX1509B_AUTO_CLEAR_NINT_POS)


/**
 * @brief Key config 1 register bitmasks.
 */

// Bitmasks for sleep time.
#define SX1509B_SLEEP_TIME_POS          4
#define SX1509B_SLEEP_TIME_MASK         (7 << SX1509B_SLEEP_TIME_POS)

// Bitmasks for scan time.
#define SX1509B_SCAN_TIME_POS           0
#define SX1509B_SCAN_TIME_MASK          (7 << SX1509B_SCAN_TIME_POS)


/**
 * @brief Key config 2 register bitmasks.
 */

// Bitmasks for row num.
#define SX1509B_ROW_NUM_POS             3
#define SX1509B_ROW_NUM_MASK            (7 << SX1509B_ROW_NUM_POS)

// Bitmasks for col num.
#define SX1509B_COL_NUM_POS             0
#define SX1509B_COL_NUM_MASK            (7 << SX1509B_COL_NUM_POS)


/**
 * @brief Led driver off register bitmasks.
 */

// Bitmasks for OFF_TIME.
#define SX1509B_OFF_TIME_POS          3
#define SX1509B_OFF_TIME_MASK         (0x1F << SX1509B_OFF_TIME_POS)

// Bitmasks for off intensity.
#define SX1509B_OFF_INTENSITY_POS     0
#define SX1509B_OFF_INTENSITY_MASK    (7 << SX1509B_OFF_INTENSITY_POS)


/**
 * @brief Miscellaneous registers.
 */
#define SX1509B_REG_HIGH_INPUT_B        0x69
#define SX1509B_REG_HIGH_INPUT_A        0x6A
#define SX1509B_REG_SW_RESET            0x7D
#define SX1509B_REG_TEST_1              0x7E
#define SX1509B_REG_TEST_2              0x7F

/**
 * @brief Structure containing expander instance.
 */
typedef struct
{
    nrf_twi_sensor_t * p_sensor_data;
    uint8_t sensor_addr;
    uint8_t start_addr;
    uint8_t registers[SX1509B_REG_COUNT];
    uint8_t high_input[2];
} sx1509b_instance_t;


#ifdef __cplusplus
}
#endif

#endif // SX1509B_INTERNAL_H
