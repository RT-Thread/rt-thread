/**
 * Copyright (c) 2015 - 2018, Nordic Semiconductor ASA
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
#if NRF_MODULE_ENABLED(HARDFAULT_HANDLER)
#include "hardfault.h"
#include "nrf.h"
#include "compiler_abstraction.h"
#include "app_util_platform.h"
#ifdef SOFTDEVICE_PRESENT
#include "nrf_soc.h"
#endif
#define NRF_LOG_MODULE_NAME hardfault
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
NRF_LOG_MODULE_REGISTER();

#if defined(DEBUG_NRF)
/**
 * @brief Pointer to the last received stack pointer.
 *
 * This pointer is set in the debug version of the HardFault handler.
 * It helps to debug HardFault reasons.
 */
volatile HardFault_stack_t * HardFault_p_stack;
#endif

/*lint -save -e14 */
__WEAK void HardFault_process(HardFault_stack_t * p_stack)
{
    // Restart the system by default
    NVIC_SystemReset();
}
/*lint -restore */

void HardFault_c_handler(uint32_t * p_stack_address)
{
    NRF_LOG_FINAL_FLUSH();

#if (__CORTEX_M == 0x04)

#ifndef CFSR_MMARVALID
  #define CFSR_MMARVALID (1 << (0 + 7))
#endif

#ifndef CFSR_BFARVALID
  #define CFSR_BFARVALID (1 << (8 + 7))
#endif

 #if defined(DEBUG)

    HardFault_stack_t * p_stack = (HardFault_stack_t *)p_stack_address;
    static const char *cfsr_msgs[] = {
        [0]  = "The processor has attempted to execute an undefined instruction",
        [1]  = "The processor attempted a load or store at a location that does not permit the operation",
        [2]  = NULL,
        [3]  = "Unstack for an exception return has caused one or more access violations",
        [4]  = "Stacking for an exception entry has caused one or more access violations",
        [5]  = "A MemManage fault occurred during floating-point lazy state preservation",
        [6]  = NULL,
        [7]  = NULL,
        [8]  = "Instruction bus error",
        [9]  = "Data bus error (PC value stacked for the exception return points to the instruction that caused the fault)",
        [10] = "Data bus error (return address in the stack frame is not related to the instruction that caused the error)",
        [11] = "Unstack for an exception return has caused one or more BusFaults",
        [12] = "Stacking for an exception entry has caused one or more BusFaults",
        [13] = "A bus fault occurred during floating-point lazy state preservation",
        [14] = NULL,
        [15] = NULL,
        [16] = "The processor has attempted to execute an undefined instruction",
        [17] = "The processor has attempted to execute an instruction that makes illegal use of the EPSR",
        [18] = "The processor has attempted an illegal load of EXC_RETURN to the PC, as a result of an invalid context, or an invalid EXC_RETURN value",
        [19] = "The processor has attempted to access a coprocessor",
        [20] = NULL,
        [21] = NULL,
        [22] = NULL,
        [23] = NULL,
        [24] = "The processor has made an unaligned memory access",
        [25] = "The processor has executed an SDIV or UDIV instruction with a divisor of 0",
    };

    uint32_t cfsr = SCB->CFSR;
    
    // Print information about error.
    NRF_LOG_ERROR("HARD FAULT at 0x%08X", p_stack->pc);
    NRF_LOG_ERROR("  R0:  0x%08X  R1:  0x%08X  R2:  0x%08X  R3:  0x%08X",
                         p_stack->r0, p_stack->r1, p_stack->r2, p_stack->r3);
    NRF_LOG_ERROR("  R12: 0x%08X  LR:  0x%08X  PSR: 0x%08X",
                         p_stack->r12, p_stack->lr, p_stack->psr);

    if (SCB->HFSR & SCB_HFSR_VECTTBL_Msk)
    {
        NRF_LOG_ERROR("Cause: BusFault on a vector table read during exception processing.");
    }

    for (uint32_t i = 0; i < sizeof(cfsr_msgs) / sizeof(cfsr_msgs[0]); i++)
    {
        if (((cfsr & (1 << i)) != 0) && (cfsr_msgs[i] != NULL))
        {
            NRF_LOG_ERROR("Cause: %s.", (uint32_t)cfsr_msgs[i]);
        }
    }

    if (cfsr & CFSR_MMARVALID)
    {
        NRF_LOG_ERROR("MemManage Fault Address: 0x%08X", SCB->MMFAR);
    }

    if (cfsr & CFSR_BFARVALID)
    {
        NRF_LOG_ERROR("Bus Fault Address: 0x%08X", SCB->BFAR);
    }

    NRF_BREAKPOINT_COND;

 #endif // defined (DEBUG)

#endif // __CORTEX_M == 0x04

    HardFault_process((HardFault_stack_t *)p_stack_address);
}
#endif //NRF_MODULE_ENABLED(HARDFAULT_HANDLER)
