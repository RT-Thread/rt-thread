 /**
 * @file mxc_pins.c
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
 * $Date: 2018-12-18 15:37:22 -0600 (Tue, 18 Dec 2018) $
 * $Revision: 40072 $
 *
 **************************************************************************** */

/* **** Includes **** */
#include "gpio.h"
#include "mxc_config.h"

/**
 * @ingroup MXC_pins
 * @{
 */

/* **** TIMER pins **** */
const gpio_cfg_t gpio_cfg_tmr0         =    { PORT_0, PIN_3, GPIO_FUNC_ALT3, GPIO_PAD_NONE };

/* **** UART pins **** */
const gpio_cfg_t gpio_cfg_uart0rtscts  =   { PORT_0, (PIN_6 | PIN_7), GPIO_FUNC_ALT2, GPIO_PAD_NONE };
const gpio_cfg_t gpio_cfg_uart0a       =   { PORT_0, (PIN_4 | PIN_5), GPIO_FUNC_ALT2, GPIO_PAD_NONE };
const gpio_cfg_t gpio_cfg_uart1rtscts  =   { PORT_0, (PIN_12 | PIN_13), GPIO_FUNC_ALT2, GPIO_PAD_NONE };
const gpio_cfg_t gpio_cfg_uart1a       =   { PORT_0, (PIN_10 | PIN_11), GPIO_FUNC_ALT2, GPIO_PAD_NONE };
const gpio_cfg_t gpio_cfg_uart1b       =   { PORT_0, (PIN_0 | PIN_1), GPIO_FUNC_ALT3, GPIO_PAD_NONE };
const gpio_cfg_t gpio_cfg_uart1c       =   { PORT_0, (PIN_6 | PIN_7), GPIO_FUNC_ALT3, GPIO_PAD_NONE };

/* **** I2C pins **** */
const gpio_cfg_t gpio_cfg_i2c0         =   { PORT_0, (PIN_8 | PIN_9), GPIO_FUNC_ALT1, GPIO_PAD_PULL_UP };
const gpio_cfg_t gpio_cfg_i2c1         =   { PORT_0, (PIN_2 | PIN_3), GPIO_FUNC_ALT1, GPIO_PAD_PULL_UP };

/* **** SPI/I2S pins **** */
const gpio_cfg_t gpio_cfg_spi17y       =   { PORT_0, (PIN_4 | PIN_5 | PIN_6 | PIN_7), GPIO_FUNC_ALT1, GPIO_PAD_NONE };          // SPI0A
const gpio_cfg_t gpio_cfg_spimss1a     =   { PORT_0, (PIN_10  | PIN_11  | PIN_12  | PIN_13) , GPIO_FUNC_ALT1, GPIO_PAD_NONE };  // SPI1A
const gpio_cfg_t gpio_cfg_spimss1b     =   { PORT_0, (PIN_0   | PIN_1   | PIN_2   | PIN_3 ) , GPIO_FUNC_ALT2, GPIO_PAD_NONE };  // SPI1B
const gpio_cfg_t gpio_cfg_i2s1a        =   { PORT_0, (PIN_10  | PIN_11  | PIN_12  | PIN_13) , GPIO_FUNC_ALT1, GPIO_PAD_NONE };  // same port as SPI1A
const gpio_cfg_t gpio_cfg_i2s1b        =   { PORT_0, (PIN_0   | PIN_1   | PIN_2   | PIN_3 ) , GPIO_FUNC_ALT2, GPIO_PAD_NONE };  // same port as SPI1B

/* **** SWD pins **** */
const gpio_cfg_t gpio_cfg_swd          =   { PORT_0, (PIN_0   | PIN_1   | PIN_2   | PIN_3 ) , GPIO_FUNC_ALT1, GPIO_PAD_NONE };

/* **** RTC pins **** */
const gpio_cfg_t gpio_cfg_rtc          =   { PORT_0, PIN_2, GPIO_FUNC_ALT3, GPIO_PAD_NONE };

/**@} end of ingroup MXC_pins*/
