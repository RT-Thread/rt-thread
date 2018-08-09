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
#ifndef NRF_CLI_TYPES_H__
#define NRF_CLI_TYPES_H__

#include <inttypes.h>
#include "sdk_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (NRF_CLI_CMD_BUFF_SIZE > 65535)
    typedef uint32_t nrf_cli_cmd_len_t;
#elif (NRF_CLI_CMD_BUFF_SIZE > 255)
    typedef uint16_t nrf_cli_cmd_len_t;
#else
    typedef uint8_t nrf_cli_cmd_len_t;
#endif

typedef enum
{
    NRF_CLI_VT100_COLOR_DEFAULT,
    NRF_CLI_VT100_COLOR_BLACK,
    NRF_CLI_VT100_COLOR_RED,
    NRF_CLI_VT100_COLOR_GREEN,
    NRF_CLI_VT100_COLOR_YELLOW,
    NRF_CLI_VT100_COLOR_BLUE,
    NRF_CLI_VT100_COLOR_MAGENTA,
    NRF_CLI_VT100_COLOR_CYAN,
    NRF_CLI_VT100_COLOR_WHITE,

    VT100_COLOR_END
} nrf_cli_vt100_color_t;

typedef struct
{
    nrf_cli_vt100_color_t col;      // text color
    nrf_cli_vt100_color_t bgcol;    // background color
} nrf_cli_vt100_colors_t;

typedef struct
{
    nrf_cli_cmd_len_t cur_x;        // horizontal cursor position in edited command line
    nrf_cli_cmd_len_t cur_x_end;    // horizontal cursor position at the end of command
    nrf_cli_cmd_len_t cur_y;        // vertical cursor position in edited command
    nrf_cli_cmd_len_t cur_y_end;    // vertical cursor position at the end of command
    nrf_cli_cmd_len_t terminal_hei; // terminal screen height
    nrf_cli_cmd_len_t terminal_wid; // terminal screen width
    uint8_t name_len;               // console name length
} nrf_cli_multiline_cons_t;

typedef struct
{
    nrf_cli_multiline_cons_t cons;
    nrf_cli_vt100_colors_t col;
    nrf_cli_cmd_len_t printed_cmd;  // printed commands counter
} nrf_cli_vt100_ctx_t;

#ifdef __cplusplus
}
#endif

#endif /* NRF_CLI_TYPES_H__ */

