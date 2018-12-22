/*
 * \file
 *
 * \brief ATSHA204 library return codes
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

#ifndef SHA204_LIB_RETURN_CODES_H
#   define SHA204_LIB_RETURN_CODES_H

#include <compiler.h>               //!< compiler dependent definitions

#define SHA204_SUCCESS              ((uint8_t)  0x00) //!< Function succeeded.
#define SHA204_PARSE_ERROR          ((uint8_t)  0xD2) //!< response status byte indicates parsing error
#define SHA204_CMD_FAIL             ((uint8_t)  0xD3) //!< response status byte indicates command execution error
#define SHA204_STATUS_CRC           ((uint8_t)  0xD4) //!< response status byte indicates CRC error
#define SHA204_FUNC_FAIL            ((uint8_t)  0xE0) //!< Function could not execute due to incorrect condition / state.
#define SHA204_BAD_PARAM            ((uint8_t)  0xE2) //!< bad argument (out of range, null pointer, etc.)
#define SHA204_INVALID_SIZE         ((uint8_t)  0xE4) //!< Count value is out of range or greater than buffer size.
#define SHA204_BAD_CRC              ((uint8_t)  0xE5) //!< incorrect CRC received
#define SHA204_RX_FAIL              ((uint8_t)  0xE6) //!< Timed out while waiting for response. Number of bytes received is > 0.
#define SHA204_RX_NO_RESPONSE       ((uint8_t)  0xE7) //!< Not an error while the Command layer is polling for a command response.
#define SHA204_RESYNC_WITH_WAKEUP   ((uint8_t)  0xE8) //!< re-synchronization succeeded, but only after generating a Wake-up

#define SHA204_COMM_FAIL            ((uint8_t)  0xF0) //!< Communication with device failed. Same as in hardware dependent modules.
#define SHA204_TIMEOUT              ((uint8_t)  0xF1) //!< Timed out while waiting for response. Number of bytes received is 0.

#endif
