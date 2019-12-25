/**
 * Copyright (c) 2016 - 2019, Nordic Semiconductor ASA
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
#include "sdk_common.h"
#if NRF_MODULE_ENABLED(NRF_LOG)
#include "nrf_log_backend_serial.h"
#include "nrf_log_str_formatter.h"
#include "nrf_log_internal.h"

void nrf_log_backend_serial_put(nrf_log_backend_t const * p_backend,
                               nrf_log_entry_t * p_msg,
                               uint8_t * p_buffer,
                               uint32_t  length,
                               nrf_fprintf_fwrite tx_func)
{
    nrf_memobj_get(p_msg);

    nrf_fprintf_ctx_t fprintf_ctx = {
            .p_io_buffer = (char *)p_buffer,
            .io_buffer_size = length,
            .io_buffer_cnt = 0,
            .auto_flush = false,
            .p_user_ctx = NULL,
            .fwrite = tx_func
    };

    nrf_log_str_formatter_entry_params_t params;

    nrf_log_header_t header;
    size_t           memobj_offset = 0;

    nrf_memobj_read(p_msg, &header, HEADER_SIZE*sizeof(uint32_t), memobj_offset);
    memobj_offset = HEADER_SIZE*sizeof(uint32_t);

    params.timestamp = header.timestamp;
    params.module_id = header.module_id;
    params.dropped   = header.dropped;
    params.use_colors = NRF_LOG_USES_COLORS;

    /*lint -save -e438*/
    if (header.base.generic.type == HEADER_TYPE_STD)
    {
        char const * p_log_str = (char const *)((uint32_t)header.base.std.addr);
        params.severity  = (nrf_log_severity_t)header.base.std.severity;
        uint32_t nargs = header.base.std.nargs;
        uint32_t args[NRF_LOG_MAX_NUM_OF_ARGS];

        nrf_memobj_read(p_msg, args, nargs*sizeof(uint32_t), memobj_offset);
        memobj_offset += (nargs*sizeof(uint32_t));

        nrf_log_std_entry_process(p_log_str,
                                  args,
                                  nargs,
                                  &params,
                                  &fprintf_ctx);

    }
    else if (header.base.generic.type == HEADER_TYPE_HEXDUMP)
    {
        uint32_t data_len = header.base.hexdump.len;
        params.severity   = (nrf_log_severity_t)header.base.hexdump.severity;
        uint8_t data_buf[8];
        uint32_t chunk_len;
        do
        {
            chunk_len = sizeof(data_buf) > data_len ? data_len : sizeof(data_buf);
            nrf_memobj_read(p_msg, data_buf, chunk_len, memobj_offset);
            memobj_offset += chunk_len;
            data_len -= chunk_len;

            nrf_log_hexdump_entry_process(data_buf,
                                         chunk_len,
                                         &params,
                                         &fprintf_ctx);
        } while (data_len > 0);
    }
    nrf_memobj_put(p_msg);
    /*lint -restore*/
}
#endif //NRF_LOG_ENABLED
