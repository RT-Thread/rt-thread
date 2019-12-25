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
#include "sdk_common.h"
#include "compiler_abstraction.h"
#include "app_error.h"

#if defined (__CORTEX_M) && (__CORTEX_M == 0x04)
void app_error_handler(ret_code_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
    __ASM volatile(
    "push {lr}                      \n"
    /* reserve space on stack for error_info_t struct */
    "sub sp, sp, %0                 \n"

    /* prepare error_info_t struct */
    "str r0, [sp, %1]               \n"
    "str r1, [sp, %3]               \n"
    "str r2, [sp, %2]               \n"

    /* prepare arguments and call function: app_error_fault_handler */
    "ldr.n r0, 1f                   \n"
    "mov r1, LR                     \n"
    "mov r2, sp                     \n"

    /* call app_error_fault_handler */
    "bl %c5                         \n"

    /* release stack */
    "add sp, sp, %0                 \n"
    "pop {pc}                       \n"

    "DATA                           \n"
    "1:                             \n"
    " DC32 %c4                      \n"

    : /* Outputs */
    : /* Inputs */
    "i" (APP_ERROR_ERROR_INFO_SIZE_ALIGNED_8BYTE),
    "i" (APP_ERROR_ERROR_INFO_OFFSET_ERR_CODE),
    "i" (APP_ERROR_ERROR_INFO_OFFSET_P_FILE_NAME),
    "i" (APP_ERROR_ERROR_INFO_OFFSET_LINE_NUM),
    "i" (NRF_FAULT_ID_SDK_ERROR),
    "i" (app_error_fault_handler)
    : /* CLobbers */
    "r0", "r1", "r2"
    );
}
#elif defined(__CORTEX_M) && (__CORTEX_M == 0x00)
/* NRF51 implementation is currently not supporting PC readout */
void app_error_handler(ret_code_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
    error_info_t error_info = {
        .line_num    = line_num,
        .p_file_name = p_file_name,
        .err_code    = error_code,
    };
    app_error_fault_handler(NRF_FAULT_ID_SDK_ERROR, 0, (uint32_t)(&error_info));

    UNUSED_VARIABLE(error_info);
}
#else
#error Architecture not supported
#endif

