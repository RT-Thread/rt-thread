 /**
 * @file       mxc_pins.h
 * @brief      This file contains constant pin configurations for the peripherals.
 */

/* *****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2018-08-09 18:45:02 -0500 (Thu, 09 Aug 2018) $
 * $Revision: 36818 $
 *
 **************************************************************************** */
 
/* Define to prevent redundant inclusion */ 
#ifndef _MXC_PINS_H_
#define _MXC_PINS_H_

/* **** Includes **** */
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/* **** Global Variables **** */

// Predefined GPIO Configurations

/*****  @brief TIMER pins *****/
extern const gpio_cfg_t gpio_cfg_tmr0;

/***** @brief UART pins *****/
extern const gpio_cfg_t gpio_cfg_uart0rtscts;
extern const gpio_cfg_t gpio_cfg_uart0a;
extern const gpio_cfg_t gpio_cfg_uart1rtscts;
extern const gpio_cfg_t gpio_cfg_uart1a;
extern const gpio_cfg_t gpio_cfg_uart1b;
extern const gpio_cfg_t gpio_cfg_uart1c;
extern const gpio_cfg_t gpio_cfg_uart2;

/***** @brief I2C pins *****/
extern const gpio_cfg_t gpio_cfg_i2c0;
extern const gpio_cfg_t gpio_cfg_i2c1;

/***** @brief SPI/I2S pins *****/
extern const gpio_cfg_t gpio_cfg_spi17y;    // SPI0A
extern const gpio_cfg_t gpio_cfg_spimss1a;  // SPI1A
extern const gpio_cfg_t gpio_cfg_spimss1b;  // SPI1B
extern const gpio_cfg_t gpio_cfg_i2s1a;     // same port as SPI1A
extern const gpio_cfg_t gpio_cfg_i2s1b;     // same port as SPI1B

/***** @brief SWD pins *****/
extern const gpio_cfg_t gpio_cfg_swd;

/***** @brief RTC pins *****/
extern const gpio_cfg_t gpio_cfg_rtc;

#ifdef __cplusplus
}
#endif

#endif /* _MXC_PINS_H_ */

