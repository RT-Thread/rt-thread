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
#include <stdbool.h>
#include <stdint.h>
#include "nrf_svc_function.h"
#include "nrf_error.h"

#include "nrf_log.h"

//lint -esym(526, svc_dataBase) -esym(526, svc_dataLimit)
NRF_SECTION_DEF(svc_data, const nrf_svc_func_t);
#define SVC_DATA_SECTION_ITEM_GET(i)        NRF_SECTION_ITEM_GET(svc_data, nrf_svc_func_reg_t, (i))
#define SVC_DATA_SECTION_ITEM_COUNT         NRF_SECTION_ITEM_COUNT(svc_data, nrf_svc_func_reg_t)


#ifdef __GNUC__
// Prevent GCC from removing this function (called from assembly branch)
void nrf_svc_handler_c(uint32_t* p_svc_args) __attribute__((used));
#endif



/**@brief   Function for handling second stage of Supervisor Calls (SVC).
*
* @details  The function will use loop through the registered svc functions stored
*           in the named section "svc_data" and will call the registered function
*           if the svn_num corresponds with the registration.
*
* @param[in] p_svc_args Argument list for the SVC.
*
* @return This function returns by updating p_svc_arsg[0]. This will be reported back to the caller of SVC
*         @ref NRF_ERROR_SVC_HANDLER_MISSING is returned if no SVC handler is implemented for the
*         provided svc_num.
*/
void nrf_svc_handler_c(uint32_t* p_svc_args)
{
    uint32_t const  num_funcs = SVC_DATA_SECTION_ITEM_COUNT;
    bool            handled = false;
    uint8_t  const  svc_num = ((uint8_t *)p_svc_args[6])[-2];
    uint32_t        svci_num = NRF_SVCI_SVC_NUM_INVALID;
    
    if (svc_num == NRF_SVCI_SVC_NUM)
    {
        // load the stacked R12 as the svci_num
        svci_num = p_svc_args[4];
    }

    for (uint32_t i = 0; i < num_funcs; i++)
    {
        nrf_svc_func_reg_t const * func_reg = SVC_DATA_SECTION_ITEM_GET(i);
        if (func_reg->svc_num != svc_num)
        {
            continue;
        }

        if (svci_num != NRF_SVCI_SVC_NUM_INVALID && func_reg->svci_num != svci_num)
        {
            continue;
        }

        // Return value is placed in R0
        p_svc_args[0] = func_reg->func_ptr(p_svc_args[0], p_svc_args[1], p_svc_args[2], p_svc_args[3]);
        handled = true;
        break;
    }

    if (handled == false)
    {
        // Return value is placed in R0
        p_svc_args[0] = NRF_ERROR_SVC_HANDLER_MISSING;
    }
}

/**@brief   Function for handling the first stage of Supervisor Calls (SVC) in assembly.
*
* @details The function will use the link register (LR) to determine the stack (PSP or MSP) to be
*          used and then decode the SVC number afterwards. After decoding the SVC number,
*          @ref C_SVC_Handler is called for further processing of the SVC.
*/
#if defined ( __CC_ARM )
__ASM void SVC_Handler(void)
{
    tst lr, #4                          ; Test bit 2 of EXT_RETURN to see if MSP or PSP is used
    ite eq                              ; 
    mrseq r0, MSP                       ; If equal, copy stack pointer from MSP
    mrsne r0, PSP                       ; If not equal, copy stack pointer from PSP
    B     __cpp(nrf_svc_handler_c)      ; Call C-implementation of handler. Exception stack frame in R0
    ALIGN 4                             ; Protect with alignment
}
#elif defined ( __GNUC__ )
void __attribute__((naked)) SVC_Handler(void)
{
    __ASM volatile
    (
        "tst lr, #4\t\n"                // Test bit 2 of EXT_RETURN to see if MSP or PSP is used
        "ite eq\t\n"                    // 
        "mrseq r0, MSP\t\n"             // Move MSP into R0.
        "mrsne r0, PSP\t\n"             // Move PSP into R0.
        "b nrf_svc_handler_c\t\n"       // Call C-implementation of handler. Exception stack frame in R0
        ".align\t\n"                    // Protect with alignment
    );
}
#elif defined ( __ICCARM__ )
void SVC_Handler(void)
{
    __ASM volatile
    (
        "tst lr, #4\t\n"                // Test bit in link register responsible for stack indication.
        "ite eq\t\n"                    // Test bit 2 of EXT_RETURN to see if MSP or PSP is used
        "mrseq r0, MSP\t\n"             // Move MSP into R0.
        "mrsne r0, PSP\t\n"             // Move PSP into R0.
        "b    nrf_svc_handler_c\t\n" :  // Call C-implementation of handler. Exception stack frame in R0
    );
}
#else

#error Compiler not supported.

#endif
