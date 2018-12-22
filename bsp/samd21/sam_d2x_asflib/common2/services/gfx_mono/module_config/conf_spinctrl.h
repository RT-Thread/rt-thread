/**
 * \file
 *
 * \brief Default configurations for gfx_mono_spinctrl
 *
 * Copyright (c) 2009-2015 Atmel Corporation. All rights reserved.
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

#ifndef DEFAULT_GFX_MONO_SPINCTRL_H_INCLUDED
#define DEFAULT_GFX_MONO_SPINCTRL_H_INCLUDED

//! Spinner value indicator
/* Bitmap data, row by row, MSB is leftmost pixel, one byte per row. */
#define GFX_MONO_SPINCTRL_SPIN_INDICATOR_BITMAP 0x18, 0x3C, 0x7E, 0xFF
//! Height of spinner value indicator
#define GFX_MONO_SPINCTRL_SPIN_INDICATOR_HEIGHT 8
//! Width of spinner value indicator
#define GFX_MONO_SPINCTRL_SPIN_INDICATOR_WIDTH  4

//! Spinner indicator
/* Bitmap data, row by row, MSB is leftmost pixel, one byte per row. */
#define GFX_MONO_SPINCTRL_INDICATOR_BITMAP 0xFF, 0x7E, 0x3C, 0x18
//! Height of spinner indicator
#define GFX_MONO_SPINCTRL_INDICATOR_HEIGHT 8
//! Width of spinner indicator
#define GFX_MONO_SPINCTRL_INDICATOR_WIDTH  4

//! Keyboard code down
#define GFX_MONO_SPINCTRL_KEYCODE_DOWN  40
//! Keyboard code up
#define GFX_MONO_SPINCTRL_KEYCODE_UP    38
//! Keyboard code back
#define GFX_MONO_SPINCTRL_KEYCODE_BACK  8
//! Keyboard code enter
#define GFX_MONO_SPINCTRL_KEYCODE_ENTER 13

#endif /* DEFAULT_GFX_MONO_SPINCTRL_H_INCLUDED */
