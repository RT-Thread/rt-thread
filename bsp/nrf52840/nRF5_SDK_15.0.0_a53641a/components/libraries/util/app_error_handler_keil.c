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
#include "sdk_common.h"
#include "compiler_abstraction.h"
#include "app_error.h"

#if defined (__CORTEX_M) && (__CORTEX_M == 0x04)
__ASM void app_error_handler(ret_code_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
    PRESERVE8 {TRUE}
    THUMB

    push {lr}

    /* reserve space on stack for error_info_t struct - preserve 8byte stack aligment */
    sub sp, sp, #__cpp(APP_ERROR_ERROR_INFO_SIZE_ALIGNED_8BYTE)

    /* prepare error_info_t struct */
    str r0, [sp, #__cpp(APP_ERROR_ERROR_INFO_OFFSET_ERR_CODE)]
    str r1, [sp, #__cpp(APP_ERROR_ERROR_INFO_OFFSET_LINE_NUM)]
    str r2, [sp, #__cpp(APP_ERROR_ERROR_INFO_OFFSET_P_FILE_NAME)]

    /* prepare arguments and call function: app_error_fault_handler */
    mov r0, #__cpp(NRF_FAULT_ID_SDK_ERROR)
    mov r1, lr
    mov r2, sp

    /* call function */
    bl __cpp(app_error_fault_handler)

    /* release stack */
    add sp, sp, #__cpp(APP_ERROR_ERROR_INFO_SIZE_ALIGNED_8BYTE)

    pop {pc}
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

