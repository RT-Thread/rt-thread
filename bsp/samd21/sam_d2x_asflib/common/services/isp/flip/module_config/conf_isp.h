/**
 * \file
 *
 * \brief ISP configuration file template.
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
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

#ifndef _CONF_ISP_H_
#define _CONF_ISP_H_

// Bootloader Versions
// Example: Version 0x00 gives 1.0.0 on batchisp log
// Example: Version 0x03 gives 1.0.3 on batchisp log
// Example: Version 0x25 gives 1.2.5 on batchisp log
//
// Note: a specific UC3 rule is defined:
// - 1.0.X for USB bootloaders that follow the AVR32784 application note
// specification
// - 1.1.X for USB bootloaders that follow the AVR32806 application note
// specification
//
#define BOOTLOADER_VERSION   0x00  // 1.0.0

// If all memories (flash,eeprom,...) do not exceed 64KB.
// then the ISP interface can be optimized to save CODE.
#define ISP_SMALL_MEMORY_SIZE

// Definition of hardware condition to enter in ISP mode on AVR Xmega devices
#define ISP_PORT_DIR      PORTX_DIR
#define ISP_PORT_PINCTRL  PORTX_PIN5CTRL
#define ISP_PORT_IN       PORTX_IN
#define ISP_PORT_PIN      0 to 7

#endif // _CONF_ISP_H_
