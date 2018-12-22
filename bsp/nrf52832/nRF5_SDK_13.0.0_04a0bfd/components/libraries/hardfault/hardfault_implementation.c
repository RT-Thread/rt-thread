/**
 * Copyright (c) 2015 - 2017, Nordic Semiconductor ASA
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
#define NRF_LOG_MODULE_NAME "HARDFAULT"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
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
    NRF_LOG_ERROR("Hardfault PC:%x\r\n", ((HardFault_stack_t *)p_stack_address)->pc);
    NRF_LOG_FINAL_FLUSH();
#if defined(DEBUG_NRF)
    HardFault_p_stack = (HardFault_stack_t *)p_stack_address;
    (void)HardFault_p_stack;

    // Debugger detection is only possible on NRF52 (Cortex-M4), on NRF51
    // (Cortex-M0) the processor has no access to CoreDebug registers.
    #if __CORTEX_M == 0x04
        // C_DEBUGEN == 1 -> Debugger Connected
        if (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
        {
            /* Generate breakpoint if debugger is connected */
            NRF_BREAKPOINT;
        }
    #endif // __CORTEX_M == 0x04
#endif // DEBUG_NRF
    HardFault_process((HardFault_stack_t *)p_stack_address);
}
#endif //NRF_MODULE_ENABLED(HARDFAULT_HANDLER)
