/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
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

NRF_SECTION_DEF(svc_data, const nrf_svc_func_t);
#define SVC_DATA_SECTION_ITEM_GET(i)        NRF_SECTION_ITEM_GET(svc_data, nrf_svc_func_reg_t, (i))
#define SVC_DATA_SECTION_ITEM_COUNT         NRF_SECTION_ITEM_COUNT(svc_data, nrf_svc_func_reg_t)


/**@brief   Function for handling second stage of SuperVisor Calls (SVC).
*
* @details  The function will use loop through the registered svc functions stored
*           in the named section "svc_data" and will call the registered function
*           if the svn_num corresponds with the registration.
*
* @param[in] svc_num    SVC number for function to be executed
* @param[in] p_svc_args Argument list for the SVC.
*
* @return This function returns by updating p_svc_arsg[0]. This will be reported back to the caller of SVC
*         @ref NRF_ERROR_SVC_HANDLER_MISSING is returned if no SVC handler is implemented for the
*         provided svc_num.
*/
void nrf_svc_handler_c(uint8_t svc_num, uint32_t * p_svc_args)
{
    uint32_t const  num_funcs = SVC_DATA_SECTION_ITEM_COUNT;
    bool            handled = false;
    uint32_t        svci_num = NRF_SVCI_SVC_NUM_INVALID;

    if(svc_num == NRF_SVCI_SVC_NUM)
    {
        /* load the stacked R12 as the svci_num */
        svci_num = p_svc_args[4];
    }

    for (int i = 0; i < num_funcs; i++)
    {
        nrf_svc_func_reg_t const * func_reg = SVC_DATA_SECTION_ITEM_GET(i);
        if (func_reg->svc_num != svc_num)
        {
            continue;
        }

        if(svci_num != NRF_SVCI_SVC_NUM_INVALID && func_reg->svci_num != svci_num)
        {
            continue;
        }

        p_svc_args[0] = func_reg->func_ptr(p_svc_args[0], p_svc_args[1], p_svc_args[2], p_svc_args[3]);
        handled = true;
    }

    if (handled == false)
    {
        p_svc_args[0] = NRF_ERROR_SVC_HANDLER_MISSING;
    }
}

/**@brief   Function for handling the first stage of SuperVisor Calls (SVC) in assembly.
*
* @details The function will use the link register (LR) to determine the stack (PSP or MSP) to be
*          used and then decode the SVC number afterwards. After decoding the SVC number then
*          @ref C_SVC_Handler is called for further processing of the SVC.
*/
#if defined ( __CC_ARM )
__ASM void SVC_Handler(void)
{
EXC_RETURN_CMD_PSP  EQU 0xFFFFFFFD                      ; EXC_RETURN using PSP for ARM Cortex.If Link register contains this value it indicates the PSP was used before the SVC, otherwise the MSP was used.

    IMPORT nrf_svc_handler_c
    LDR   R0, =EXC_RETURN_CMD_PSP                       ; Load the EXC_RETURN into R0 to be able to compare against LR to determine stack pointer used.
    CMP   R0, LR                                        ; Compare the link register with R0.If equal then PSP was used, otherwise MSP was used before SVC.
    BNE   UseMSP                                        ; Branch to code fetching SVC arguments using MSP.
    MRS   R1, PSP                                       ; Move PSP into R1.
    B     Call_nrf_svc_handler_c                        ; Branch to call_nrf_svc_handler_c below.
UseMSP                                                  ;
    MRS   R1, MSP                                       ; MSP was used, therefore Move MSP into R1.
Call_nrf_svc_handler_c                                  ;
    LDR   R0, [R1, #24]                                 ; The arguments for the SVC was stacked.R1 contains Stack Pointer, the values stacked before SVC are R0, R1, R2, R3, R12, LR, PC(Return address), xPSR.
                                                        ; R1 contains current SP so the PC of the stacked frame is at SP + 6 words(24 bytes).We load the PC into R0.
    SUBS  R0, #2                                        ; The PC before the SVC is in R0.We subtract 2 to get the address prior to the instruction executed where the SVC number is located.
    LDRB  R0, [R0]                                      ; SVC instruction low octet : Load the byte at the address before the PC to fetch the SVC number.
    LDR   R2, =nrf_svc_handler_c                        ; Load address of C implementation of SVC handler.
    BX    R2                                            ; Branch to C implementation of SVC handler.R0 is now the SVC number, R1 is the StackPointer where the arguments(R0 - R3) of the original SVC are located.
    ALIGN
}
#elif defined ( __GNUC__ )
void __attribute__((naked)) SVC_Handler(void)
{
    const uint32_t exc_return = 0xFFFFFFFD;                 // EXC_RETURN using PSP for ARM Cortex. If Link register contains this value it indicates the PSP was used before the SVC, otherwise the MSP was used.

    __ASM volatile(
        "cmp   lr, %0\t\n"                                  // Compare the link register with argument 0 (%0), which is exc_return. If equal then PSP was used, otherwise MSP was used before SVC.
        "bne   UseMSP\t\n"                                  // Branch to code fetching SVC arguments using MSP.
        "mrs   r1, psp\t\n"                                 // Move PSP into R1.
        "b     Call_nrf_svc_handler_c\t\n"                  // Branch to Call_nrf_svc_handler_c below.
        "UseMSP:\t\n"                                       //
        "mrs   r1, msp\t\n"                                 // MSP was used, therefore Move MSP into R1.
        "Call_nrf_svc_handler_c:\t\n"                       //
        "ldr   r0, [r1, #24]\t\n"                           // The arguments for the SVC was stacked. R1 contains Stack Pointer, the values stacked before SVC are R0, R1, R2, R3, R12, LR, PC (Return address), xPSR.
                                                            // R1 contains current SP so the PC of the stacked frame is at SP + 6 words (24 bytes). We load the PC into R0.
        "sub   r0, r0, #2\t\n"                              // The PC before the SVC is in R0. We subtract 2 to get the address prior to the instruction executed where the SVC number is located.
        "ldrb  r0, [r0]\t\n"                                // SVC instruction low octet: Load the byte at the address before the PC to fetch the SVC number.
        "bx    %1\t\n"                                      // Branch to C implementation of SVC handler, argument 1 (%1). R0 is now the SVC number, R1 is the StackPointer where the arguments (R0-R3) of the original SVC are located.
        ".align\t\n"                                        //
        :: "r" (exc_return), "r" (nrf_svc_handler_c)       	// Argument list for the gcc assembly. exc_return is %0, nrf_svc_handler_c is %1.
        : "r0", "r1"                                        // List of register maintained manually.
        );
}
#elif defined ( __ICCARM__ )
void SVC_Handler(void)
{
    __ASM("movs  r0, #0x02\n"                               // Load 0x02 into R6 to prepare for exec return test.
        "mvns  r0, r0\n"                                    // Invert R0 to obtain exec return code using PSP for ARM Cortex.
        "cmp   lr, r0\n"                                    // Compare the link register with argument 0 (%0), which is exc_return. If equal then PSP was used, otherwise MSP was used before SVC.
        "bne.n UseMSP\n"                                    // Branch to code fetching SVC arguments using MSP.
        "mrs   r1, psp\n"                                   // Move PSP into R1.
        "b.n   Call_nrf_svc_handler_c\t\n"                  // Branch to Call_nrf_svc_handler_c below.
        "UseMSP:  \n"                                       //
        "mrs   r1, msp\n"                                   // MSP was used, therefore Move MSP into R1.
        "Call_nrf_svc_handler_c:  \n"                       //
        "ldr   r0, [r1, #24]\n"                             // The arguments for the SVC was stacked. R1 contains Stack Pointer, the values stacked before SVC are R0, R1, R2, R3, R12, LR, PC (Return address), xPSR.
                                                            // R1 contains current SP so the PC of the stacked frame is at SP + 6 words (24 bytes). We load the PC into R0.
        "subs  r0, #0x02\n"                                 // The PC before the SVC is in R0. We subtract 2 to get the address prior to the instruction executed where the SVC number is located.
        "ldrb  r0, [r0]\n"                                  // SVC instruction low octet: Load the byte at the address before the PC to fetch the SVC number.
        "bx    %0\n"                                        // Branch to C implementation of SVC handler, argument 1 (%1). R0 is now the SVC number, R1 is the StackPointer where the arguments (R0-R3) of the original SVC are located.
        :: "r" (nrf_svc_handler_c)                          // Argument list for the gcc assembly. nrf_svc_handler_c is %0.
        : "r0", "r1"                                        // List of register maintained manually.
        );
}
#else

#error Compiler not supported.

#endif
