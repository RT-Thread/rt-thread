/*
 * Copyright (c) 2008-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * @file sdk.h
 * @brief       Basic defines
 *
 * @ingroup diag_init
 */
#ifndef __SDK_H__
#define __SDK_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "sdk_types.h"
#include "sdk_version.h"
#include "io.h"

#include "soc_memory_map.h"
#include "registers.h"
#include "iomux_config.h"
#include "iomux_define.h"
#include "iomux_register.h"
#include "utility/system_util.h"
#include "gpio/gpio.h"
#include "core/interrupt.h"
#include "core/gic.h"
#include "ccm_pll.h"
#include "ioexpander/max7310.h"
#include "i2c/imx_i2c.h"
#include "uart/imx_uart.h"
#include "timer/timer.h"
// #include "usb/usb.h"
#include "keypad/keypad_port.h"
#include "spi/ecspi_ifc.h"
#if !defined(CHIP_MX6SL)
#include "enet/enet.h"
#else
#include "fec/fec.h"
#endif
#include "board_id/board_id.h"

#include "buffers.h"

#include "board_io_expanders.h"
#include "board_i2c.h"

#if defined(CHIP_MX6DQ)
#include "sata/imx_sata.h"
#endif

#endif // __SDK_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
