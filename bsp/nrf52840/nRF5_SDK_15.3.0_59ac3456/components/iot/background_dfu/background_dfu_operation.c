/**
 * Copyright (c) 2017 - 2019, Nordic Semiconductor ASA
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

/** @file
 *
 * @defgroup background_dfu_operation background_dfu_operation.c
 * @{
 * @ingroup background_dfu
 * @brief Background DFU operations implementation.
 *
 */

#include "background_dfu_operation.h"

#include "sdk_config.h"
#include "nrf_dfu_req_handler.h"

#define NRF_LOG_MODULE_NAME background_dfu

#define NRF_LOG_LEVEL       BACKGROUND_DFU_CONFIG_LOG_LEVEL
#define NRF_LOG_INFO_COLOR  BACKGROUND_DFU_CONFIG_INFO_COLOR
#define NRF_LOG_DEBUG_COLOR BACKGROUND_DFU_CONFIG_DEBUG_COLOR

#include "nrf_log.h"

ret_code_t background_dfu_op_select(uint32_t                    object_type,
                                    nrf_dfu_response_callback_t callback,
                                    void                      * p_context)
{
    nrf_dfu_request_t  dfu_req;

    memset(&dfu_req, 0, sizeof(dfu_req));

    dfu_req.request            = NRF_DFU_OP_OBJECT_SELECT;
    dfu_req.select.object_type = object_type;
    dfu_req.p_context          = p_context;
    dfu_req.callback.response  = callback;

    return nrf_dfu_req_handler_on_req(&dfu_req);
}

ret_code_t background_dfu_op_create(uint32_t                    object_type,
                                    uint32_t                    object_size,
                                    nrf_dfu_response_callback_t callback,
                                    void                      * p_context)
{
    nrf_dfu_request_t  dfu_req;

    memset(&dfu_req, 0, sizeof(dfu_req));

    dfu_req.request            = NRF_DFU_OP_OBJECT_CREATE;
    dfu_req.create.object_size = object_size;
    dfu_req.create.object_type = object_type;
    dfu_req.p_context          = p_context;
    dfu_req.callback.response  = callback;

    return nrf_dfu_req_handler_on_req(&dfu_req);
}

ret_code_t background_dfu_op_write(const uint8_t             * p_payload,
                                   uint16_t                    payload_length,
                                   nrf_dfu_response_callback_t response_callback,
                                   nrf_dfu_flash_callback_t    write_callback,
                                   void                      * p_context)
{
    nrf_dfu_request_t  dfu_req;

    memset(&dfu_req, 0, sizeof(dfu_req));

    dfu_req.request           = NRF_DFU_OP_OBJECT_WRITE;
    dfu_req.write.p_data      = (uint8_t *)p_payload;
    dfu_req.write.len         = payload_length;
    dfu_req.p_context         = p_context;
    dfu_req.callback.response = response_callback;
    dfu_req.callback.write    = write_callback;

    return nrf_dfu_req_handler_on_req(&dfu_req);
}

ret_code_t background_dfu_op_crc(nrf_dfu_response_callback_t callback,
                                 void                      * p_context)
{
    nrf_dfu_request_t  dfu_req;

    memset(&dfu_req, 0, sizeof(dfu_req));

    dfu_req.request            = NRF_DFU_OP_CRC_GET;
    dfu_req.p_context          = p_context;
    dfu_req.callback.response  = callback;

    return nrf_dfu_req_handler_on_req(&dfu_req);
}

ret_code_t background_dfu_op_execute(nrf_dfu_response_callback_t callback,
                                     void                      * p_context)
{
    nrf_dfu_request_t  dfu_req;

    memset(&dfu_req, 0, sizeof(dfu_req));

    dfu_req.request            = NRF_DFU_OP_OBJECT_EXECUTE;
    dfu_req.p_context          = p_context;
    dfu_req.callback.response  = callback;

    return nrf_dfu_req_handler_on_req(&dfu_req);
}
