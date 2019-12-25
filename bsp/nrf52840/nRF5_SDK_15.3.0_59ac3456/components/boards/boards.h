/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
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
#ifndef BOARDS_H
#define BOARDS_H

#include "nrf_gpio.h"
#include "nordic_common.h"

#if defined(BOARD_NRF6310)
  #include "nrf6310.h"
#elif defined(BOARD_PCA10000)
  #include "pca10000.h"
#elif defined(BOARD_PCA10001)
  #include "pca10001.h"
#elif defined(BOARD_PCA10002)
  #include "pca10000.h"
#elif defined(BOARD_PCA10003)
  #include "pca10003.h"
#elif defined(BOARD_PCA20006)
  #include "pca20006.h"
#elif defined(BOARD_PCA10028)
  #include "pca10028.h"
#elif defined(BOARD_PCA10031)
  #include "pca10031.h"
#elif defined(BOARD_PCA10036)
  #include "pca10036.h"
#elif defined(BOARD_PCA10040)
  #include "pca10040.h"
#elif defined(BOARD_PCA10056)
  #include "pca10056.h"
#elif defined(BOARD_PCA20020)
  #include "pca20020.h"
#elif defined(BOARD_PCA10059)
  #include "pca10059.h"
#elif defined(BOARD_WT51822)
  #include "wt51822.h"
#elif defined(BOARD_N5DK1)
  #include "n5_starterkit.h"
#elif defined (BOARD_D52DK1)
  #include "d52_starterkit.h"
#elif defined (BOARD_ARDUINO_PRIMO)
  #include "arduino_primo.h"
#elif defined (CUSTOM_BOARD_INC)
  #include STRINGIFY(CUSTOM_BOARD_INC.h)
#elif defined(BOARD_CUSTOM)
  #include "custom_board.h"
#else
#error "Board is not defined"

#endif

#ifdef __cplusplus
extern "C" {
#endif

/**@defgroup BSP_BOARD_INIT_FLAGS Board initialization flags.
 * @{ */
#define BSP_INIT_NONE    0        /**< No initialization of LEDs or buttons (@ref bsp_board_init).*/
#define BSP_INIT_LEDS    (1 << 0) /**< Enable LEDs during initialization (@ref bsp_board_init).*/
#define BSP_INIT_BUTTONS (1 << 1) /**< Enable buttons during initialization (@ref bsp_board_init).*/
/**@} */

/**
 * Function for returning the state of an LED.
 *
 * @param led_idx LED index (starting from 0), as defined in the board-specific header.
 *
 * @return True if the LED is turned on.
 */
bool bsp_board_led_state_get(uint32_t led_idx);

/**
 * Function for turning on an LED.
 *
 * @param led_idx LED index (starting from 0), as defined in the board-specific header.
 */
void bsp_board_led_on(uint32_t led_idx);

/**
 * Function for turning off an LED.
 *
 * @param led_idx LED index (starting from 0), as defined in the board-specific header.
 */
void bsp_board_led_off(uint32_t led_idx);

/**
 * Function for inverting the state of an LED.
 *
 * @param led_idx LED index (starting from 0), as defined in the board-specific header.
 */
void bsp_board_led_invert(uint32_t led_idx);
/**
 * Function for turning off all LEDs.
 */
void bsp_board_leds_off(void);

/**
 * Function for turning on all LEDs.
 */
void bsp_board_leds_on(void);

/**
 * Function for initializing the BSP handling for the board.
 *
 * @note This also initializes the USB DFU trigger library if @ref BOARDS_WITH_USB_DFU_TRIGGER is 1.
 *
 * @param[in]  init_flags  Flags specifying what to initialize (LEDs/buttons).
 *                         See @ref BSP_BOARD_INIT_FLAGS.
 */
void bsp_board_init(uint32_t init_flags);

/**
 * Function for converting pin number to LED index.
 *
 * @param pin_number Pin number.
 *
 * @return LED index of the given pin or 0xFFFFFFFF if invalid pin provided.
 */
uint32_t bsp_board_pin_to_led_idx(uint32_t pin_number);

/**
 * Function for converting LED index to pin number.
 *
 * @param led_idx LED index.
 *
 * @return Pin number.
 */
uint32_t bsp_board_led_idx_to_pin(uint32_t led_idx);

/**
 * Function for returning the state of a button.
 *
 * @param button_idx Button index (starting from 0), as defined in the board-specific header.
 *
 * @return True if the button is pressed.
 */
bool bsp_board_button_state_get(uint32_t button_idx);

/**
 * Function for converting pin number to button index.
 *
 * @param pin_number Pin number.
 *
 * @return Button index of the given pin or 0xFFFFFFFF if invalid pin provided.
 */
uint32_t bsp_board_pin_to_button_idx(uint32_t pin_number);


/**
 * Function for converting button index to pin number.
 *
 * @param button_idx Button index.
 *
 * @return Pin number.
 */
uint32_t bsp_board_button_idx_to_pin(uint32_t button_idx);

#define BSP_BOARD_LED_0 0
#define BSP_BOARD_LED_1 1
#define BSP_BOARD_LED_2 2
#define BSP_BOARD_LED_3 3
#define BSP_BOARD_LED_4 4
#define BSP_BOARD_LED_5 5
#define BSP_BOARD_LED_6 6
#define BSP_BOARD_LED_7 7

#define PIN_MASK(_pin)  /*lint -save -e504 */                     \
                        (1u << (uint32_t)((_pin) & (~P0_PIN_NUM))) \
                        /*lint -restore    */

#define PIN_PORT(_pin) (((_pin) >= P0_PIN_NUM) ? NRF_P1 : NRF_GPIO)

#ifdef BSP_LED_0
#define BSP_LED_0_MASK PIN_MASK(BSP_LED_0)
#define BSP_LED_0_PORT PIN_PORT(BSP_LED_0)
#else
#define BSP_LED_0_MASK 0
#define BSP_LED_0_PORT 0
#endif
#ifdef BSP_LED_1
#define BSP_LED_1_MASK PIN_MASK(BSP_LED_1)
#define BSP_LED_1_PORT PIN_PORT(BSP_LED_1)
#else
#define BSP_LED_1_MASK 0
#define BSP_LED_1_PORT 0
#endif
#ifdef BSP_LED_2
#define BSP_LED_2_MASK PIN_MASK(BSP_LED_2)
#define BSP_LED_2_PORT PIN_PORT(BSP_LED_2)
#else
#define BSP_LED_2_MASK 0
#define BSP_LED_2_PORT 0
#endif
#ifdef BSP_LED_3
#define BSP_LED_3_MASK PIN_MASK(BSP_LED_3)
#define BSP_LED_3_PORT PIN_PORT(BSP_LED_3)
#else
#define BSP_LED_3_MASK 0
#define BSP_LED_3_PORT 0
#endif
#ifdef BSP_LED_4
#define BSP_LED_4_MASK PIN_MASK(BSP_LED_4)
#define BSP_LED_4_PORT PIN_PORT(BSP_LED_4)
#else
#define BSP_LED_4_MASK 0
#define BSP_LED_4_PORT 0
#endif
#ifdef BSP_LED_5
#define BSP_LED_5_MASK PIN_MASK(BSP_LED_5)
#define BSP_LED_5_PORT PIN_PORT(BSP_LED_5)
#else
#define BSP_LED_5_MASK 0
#define BSP_LED_5_PORT 0
#endif
#ifdef BSP_LED_6
#define BSP_LED_6_MASK PIN_MASK(BSP_LED_6)
#define BSP_LED_6_PORT PIN_PORT(BSP_LED_6)
#else
#define BSP_LED_6_MASK 0
#define BSP_LED_6_PORT 0
#endif
#ifdef BSP_LED_7
#define BSP_LED_7_MASK PIN_MASK(BSP_LED_7)
#define BSP_LED_7_PORT PIN_PORT(BSP_LED_7)
#else
#define BSP_LED_7_MASK 0
#define BSP_LED_7_PORT 0
#endif


#define LEDS_MASK      (BSP_LED_0_MASK | BSP_LED_1_MASK | \
                        BSP_LED_2_MASK | BSP_LED_3_MASK | \
                        BSP_LED_4_MASK | BSP_LED_5_MASK | \
                        BSP_LED_6_MASK | BSP_LED_7_MASK)

#define BSP_BOARD_BUTTON_0 0
#define BSP_BOARD_BUTTON_1 1
#define BSP_BOARD_BUTTON_2 2
#define BSP_BOARD_BUTTON_3 3
#define BSP_BOARD_BUTTON_4 4
#define BSP_BOARD_BUTTON_5 5
#define BSP_BOARD_BUTTON_6 6
#define BSP_BOARD_BUTTON_7 7


#ifdef BSP_BUTTON_0
#define BSP_BUTTON_0_MASK (1<<BSP_BUTTON_0)
#else
#define BSP_BUTTON_0_MASK 0
#endif
#ifdef BSP_BUTTON_1
#define BSP_BUTTON_1_MASK (1<<BSP_BUTTON_1)
#else
#define BSP_BUTTON_1_MASK 0
#endif
#ifdef BSP_BUTTON_2
#define BSP_BUTTON_2_MASK (1<<BSP_BUTTON_2)
#else
#define BSP_BUTTON_2_MASK 0
#endif
#ifdef BSP_BUTTON_3
#define BSP_BUTTON_3_MASK (1<<BSP_BUTTON_3)
#else
#define BSP_BUTTON_3_MASK 0
#endif
#ifdef BSP_BUTTON_4
#define BSP_BUTTON_4_MASK (1<<BSP_BUTTON_4)
#else
#define BSP_BUTTON_4_MASK 0
#endif
#ifdef BSP_BUTTON_5
#define BSP_BUTTON_5_MASK (1<<BSP_BUTTON_5)
#else
#define BSP_BUTTON_5_MASK 0
#endif
#ifdef BSP_BUTTON_6
#define BSP_BUTTON_6_MASK (1<<BSP_BUTTON_6)
#else
#define BSP_BUTTON_6_MASK 0
#endif
#ifdef BSP_BUTTON_7
#define BSP_BUTTON_7_MASK (1<<BSP_BUTTON_7)
#else
#define BSP_BUTTON_7_MASK 0
#endif

#define BUTTONS_MASK   (BSP_BUTTON_0_MASK | BSP_BUTTON_1_MASK | \
                        BSP_BUTTON_2_MASK | BSP_BUTTON_3_MASK | \
                        BSP_BUTTON_4_MASK | BSP_BUTTON_5_MASK | \
                        BSP_BUTTON_6_MASK | BSP_BUTTON_7_MASK)


#define LEDS_OFF(leds_mask) do {  ASSERT(sizeof(leds_mask) == 4);                     \
                        NRF_GPIO->OUTSET = (leds_mask) & (LEDS_MASK & LEDS_INV_MASK); \
                        NRF_GPIO->OUTCLR = (leds_mask) & (LEDS_MASK & ~LEDS_INV_MASK); } while (0)

#define LEDS_ON(leds_mask) do {  ASSERT(sizeof(leds_mask) == 4);                     \
                       NRF_GPIO->OUTCLR = (leds_mask) & (LEDS_MASK & LEDS_INV_MASK); \
                       NRF_GPIO->OUTSET = (leds_mask) & (LEDS_MASK & ~LEDS_INV_MASK); } while (0)

#define LED_IS_ON(leds_mask) ((leds_mask) & (NRF_GPIO->OUT ^ LEDS_INV_MASK) )

#define LEDS_INVERT(leds_mask) do { uint32_t gpio_state = NRF_GPIO->OUT;      \
                              ASSERT(sizeof(leds_mask) == 4);                 \
                              NRF_GPIO->OUTSET = ((leds_mask) & ~gpio_state); \
                              NRF_GPIO->OUTCLR = ((leds_mask) & gpio_state); } while (0)

#define LEDS_CONFIGURE(leds_mask) do { uint32_t pin;                  \
                                  ASSERT(sizeof(leds_mask) == 4);     \
                                  for (pin = 0; pin < 32; pin++)      \
                                      if ( (leds_mask) & (1 << pin) ) \
                                          nrf_gpio_cfg_output(pin); } while (0)

#ifdef __cplusplus
}
#endif

#endif
