/**
 * Copyright (c) 2016 - 2018, Nordic Semiconductor ASA
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
 * @defgroup sdk_nrf_svc_function Supervisor function
 * @{
 * @ingroup app_common
 *
 * @brief Macros to create Supervisor functions.
 */

#ifndef NRF_SVC_FUNCTION_H__
#define NRF_SVC_FUNCTION_H__

#include <stdint.h>
#include "nrf_section.h"
#include "app_util.h"
#include "nrf_svci.h"

#ifdef __cplusplus
extern "C" {
#endif


/** @brief Function to be called from an SVC handler.
 *
 * @warning This function prototype has no arguments. It will be cast to a function prototype
 *          that has 0 to 4 arguments. 4 arguments is the highest number of allowed arguments in
 *          a Supervisor call.
 *
 * @warning The nrf_svc_func_t function prototype should not have void as parameter list as there
 *          will be 0 to 4 arguments after casting.
 */
typedef uint32_t (*nrf_svc_func_t)();

/** @brief Type holding the SVC number, SVCI number, and the pointer to the corresponding handler
 *         function.
 *
 * @note The function that is pointed to must not change version.
 */
typedef struct
{
    uint32_t            svc_num;        /**< Supervisor call number (actually 8-bit, padded for alignment). */
    uint32_t            svci_num;       /**< Supervisor call indirect number. */
    nrf_svc_func_t      func_ptr;
} nrf_svc_func_reg_t;


// Verify that the size of nrf_svc_func_t is aligned to make sure it can be used in nrf_section.
STATIC_ASSERT(sizeof(nrf_svc_func_reg_t) % 4 == 0);


/** @brief  Macro for registering a structure holding SVC number and SVC handler
 *          function pointer.
 *
 * @details     This macro places a variable in a section named "svc_data" that
 *              the SVC handler uses during regular operation.
 *
 * @note        This macro must be invoked from a source file. There should only be one
 *              registration by a given SVC number. SVC number 0 (zero) is invalid input
 *              and will cause a compile time assertion.
 *
 * @param[in]   name        Name of the structure. Logically accessible from the source file.
 * @param[in]   svc_number  SVC number to register.
 * @param[in]   func        Function to call for a given SVC number.
 *
 * @retval  Variable registration in @ref lib_section_vars named svc_data.
 */
#define NRF_SVC_FUNCTION_REGISTER(svc_number, name, func)               \
STATIC_ASSERT(svc_number != 0);                                         \
NRF_SECTION_ITEM_REGISTER(svc_data, nrf_svc_func_reg_t const name) =    \
{                                                                       \
    .svc_num = svc_number,                                              \
    .svci_num = NRF_SVCI_SVC_NUM_INVALID,                               \
    .func_ptr = (nrf_svc_func_t)func                                    \
}


/** @brief  Macro for registering a structure holding SVC number, SVCI number, and SVCI handler
 *          function pointer.
 *
 * @details     This macro places a variable in a section named "svc_data" that
 *              the SVC handler uses during regular operation.
 *
 * @note        This macro must be invoked from a source file. There should only be one registration
 *              for a given SVC indirect number.
 *
 * @param[in]   name        Name of the structure. Logically accessible from the source file.
 * @param[in]   svci_number SVC indirect number to register.
 * @param[in]   func        Function to call for a given SVC indirect number.
 *
 * @retval  Variable registration in @ref lib_section_vars named svc_data.
 */
#define NRF_SVCI_FUNCTION_REGISTER(svci_number, name, func)             \
NRF_SECTION_ITEM_REGISTER(svc_data, nrf_svc_func_reg_t const name) =    \
{                                                                       \
    .svc_num = NRF_SVCI_SVC_NUM,                                        \
    .svci_num = svci_number,                                            \
    .func_ptr = (nrf_svc_func_t)func                                    \
}


#ifdef __cplusplus
}
#endif

#endif // NRF_SVC_FUNCTION_H__

/** @} */
