/**
 * \file
 *
 * \brief Management of C8263A LCD Glass component.
 *
 * Copyright (c) 2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef C8263A_H_INCLUDED
#define C8263A_H_INCLUDED

#include "compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup c8263a_display_group Atmel YMCC8263AAAFDCL LCD Glass component
 *
 * This is a driver for Atmel YMCC8263AAAFDCL LCD component.
 * This component is the custom LCD used for SAM4L-Xplained-Pro.
 * This driver provides functions for initialization and control of the
 * LCD segments.
 *
 * \section dependencies Dependencies
 * This driver depends on the following modules:
 * - SLCD driver.
 * @{
 */

/**
 * \name Value for battery Icon setting
 * @{
 */
enum c8263a_battery_value {
	C8263A_BATTERY_NONE = 0,
	C8263A_BATTERY_ONE,
	C8263A_BATTERY_TWO,
	C8263A_BATTERY_THREE,
};
/** @} */

/**
 * \name Value for wireless Icon setting
 * @{
 */
enum c8263a_wireless_value {
	C8263A_WIRELESS_NONE = 0,
	C8263A_WIRELESS_ONE,
	C8263A_WIRELESS_TWO,
	C8263A_WIRELESS_THREE,
};
/** @} */

/**
 * \name Function Prototypes
 * @{
 */

/**
 * \brief Initialize the C8263A LCD Glass component.
 *
 * This function initializes the LCD driver to control the LCD glass.
 * It perform LCD module intialization according to the C8263A characteristics.
 *
 */
void c8263a_init(void);

/**
 * \brief Show text on C8263A LCD glass alphanumeric field.
 *
 * This function will show text on the alphanumeric field of the LCD glass.
 *
 * \param data Pointer to the input string(max length is 8)
 */
void c8263a_show_text(const uint8_t *data);

/**
 * \brief Clear C8263A LCD glass alphanumeric field.
 *
 * This function will clear the alphanumeric field of the LCD glass.
 */
void c8263a_clear_text(void);

/**
 * \brief Clear a specific icon on the LCD glass.
 *
 * This function will clear a specific icon.
 *
 * \param icon_com  Pixel coordinate - COMx - of the icon.
 * \param icon_seg  Pixel coordinate - SEGy - of the icon.
 *
 * \note Use the icon define in header file.
 */
void c8263a_clear_icon(uint8_t icon_com, uint8_t icon_seg);

/**
 * \brief Show a specific icon on the LCD glass.
 *
 * This function will show a specific icon.
 *
 * \param icon_com  Pixel coordinate - COMx - of the icon.
 * \param icon_seg  Pixel coordinate - SEGy - of the icon.
 *
 * \note Use the icon define in header file.
 */
void c8263a_show_icon(uint8_t icon_com, uint8_t icon_seg);

/**
 * \brief Blink a specific icon on the LCD glass.
 *
 * This function will blink a specific icon.
 *
 * \param icon_com  Pixel coordinate - COMx - of the icon.
 * \param icon_seg  Pixel coordinate - SEGy - of the icon.
 *
 * \note Use the icon define in header file(with selected segments
 * blinking feature).
 */
void c8263a_blink_icon_start(uint8_t icon_com, uint8_t icon_seg);

/**
 * \brief Stop blink a specific icon on the LCD glass.
 *
 * This function will stop blink a specific icon.
 *
 * \param icon_com  Pixel coordinate - COMx - of the icon.
 * \param icon_seg  Pixel coordinate - SEGy - of the icon.
 *
 * \note Use the icon define in header file(with selected segments
 * blinking feature).
 */
void c8263a_blink_icon_stop(uint8_t icon_com, uint8_t icon_seg);

/**
 * \brief Blink the current screen content.
 *
 * This function will make the current screen blink.
 *
 */
void c8263a_blink_screen(void);

/**
 * \brief Disable all Blink.
 *
 * This function will disable all Blink content.
 *
 */
void c8263a_blink_disable(void);

/**
 * \brief Set the C8263A LCD glass contrast.
 *
 *  This function allows to adjust the contrast of the C8263A LCD glass.
 *
 *  \param contrast  Contrast vlaue [0-0xff].
 */
void c8263a_set_contrast(uint8_t contrast);

/**
 * \brief Scrolling start.
 *
 * This function start the text scrolling.
 *
 * \param data Data string buffer.
 * \param length Data string length.
 */
void c8263a_text_scrolling_start(const uint8_t *data, uint32_t length);

/**
 * \brief Scrolling stop.
 *
 * This function stop the text scrolling.
 */
void c8263a_text_scrolling_stop(void);

/**
 * \brief Show all content of the LCD glass.
 *
 * This function sets all pixels and areas of the LCD glass C8263A.
 *
 */
void c8263a_show_all(void);

/**
 * \brief Clear all content of the LCD glass.
 *
 * This function clears all pixels and areas of the LCD glass C8263A.
 *
 */
void c8263a_clear_all(void);

/**
 * \brief Show a decimal numeric value to LCD glass.
 *
 * This function displays an int32 value to the LCD numeric field of the glass.
 *
 * \param value The int32_t value to be displayed
 *
 * \note The value range is [-199999,199999].
 */
void c8263a_show_numeric_dec(int32_t value);

/**
 * \brief Clear C8263A LCD glass numeric field and the three
 * C8263A_ICON_MINUS*** icons.
 *
 * This function will clear the numeric field of the LCD glass.
 */
void c8263a_clear_numeric_dec(void);

/**
 * \brief Show battery condition by the battery icons on the LCD glass.
 *
 * This function allows to Show battery condition by the battery icons
 * on the LCD glass..
 *
 * \param val The 0 to 3 value which show the battery condition.
 */
void c8263a_show_battery(enum c8263a_battery_value val);

/**
 * \brief Show wireless signal condition by the wireless icons on the LCD glass.
 *
 * This function allows to Show wireless signal condition by the wireless icons
 * on the LCD glass..
 *
 * \param val The 0 to 3 value which show the wireless signal condition.
 */
 void c8263a_show_wireless(enum c8263a_wireless_value val);

/**
 * \brief Start autonomous segment animation.
 *
 * \param val The 0 to 3 value which show the wireless signal condition.
 *
 * \param size Shift data size.
 * \param data Shift data.
 */

void c8263a_circular_animation_start(uint8_t size, uint8_t data);

/**
 * \brief Stop autonomous segment animation.
 *
 */
void c8263a_circular_animation_stop(void);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* C8263A_H_INCLUDED */
