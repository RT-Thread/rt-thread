/*
 * \file
 *
 * \brief ATSHA204 header file for the I2C layer for the device
 *
 *
 * Copyright (c) 2011-2015 Atmel Corporation. All rights reserved.
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

#ifndef SHA204_PHYSICAL_H
#   define SHA204_PHYSICAL_H

#include "sha204_config.h"                           //!< configuration values

#define SHA204_RSP_SIZE_MIN          ((uint8_t)  4)  //!< minimum number of bytes in response
#define SHA204_RSP_SIZE_MAX          ((uint8_t) 35)  //!< maximum size of response packet

#define SHA204_BUFFER_POS_COUNT      (0)             //!< buffer index of count byte in command or response
#define SHA204_BUFFER_POS_DATA       (1)             //!< buffer index of data in response

//! delay between Wakeup pulse and communication in ms
#define SHA204_WAKEUP_DELAY          (3)
/**
 * \defgroup sha204_communication_physical_group SHA204 Service - hardware dependent communication functions
 *
 * @{
 */
void    sha204p_init(void);
void    sha204p_set_device_id(uint8_t id);
uint8_t sha204p_send_command(uint8_t count, uint8_t *command);
uint8_t sha204p_receive_response(uint8_t size, uint8_t *response);
uint8_t sha204p_wakeup(void);
uint8_t sha204p_idle(void);
uint8_t sha204p_sleep(void);
uint8_t sha204p_reset_io(void);
uint8_t sha204p_resync(uint8_t size, uint8_t *response);
//! @}

#endif
