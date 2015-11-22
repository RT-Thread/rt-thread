/* Copyright (c) 2015, Nordic Semiconductor ASA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice, this
 *     list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *   * Neither the name of Nordic Semiconductor ASA nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "nrf.h"
#include "system_nrf52.h"

/*lint ++flb "Enter library region" */

#define __SYSTEM_CLOCK_16M      (16000000UL)     
#define __SYSTEM_CLOCK_64M      (64000000UL)   

static bool ftpan_32(void); 
static bool ftpan_37(void); 
static bool ftpan_36(void); 


#if defined ( __CC_ARM )
    uint32_t SystemCoreClock __attribute__((used)) = __SYSTEM_CLOCK_64M;
#elif defined ( __ICCARM__ )
    __root uint32_t SystemCoreClock = __SYSTEM_CLOCK_64M;
#elif defined   ( __GNUC__ )
    uint32_t SystemCoreClock __attribute__((used)) = __SYSTEM_CLOCK_64M;
#endif

void SystemCoreClockUpdate(void)
{
    SystemCoreClock = __SYSTEM_CLOCK_64M;
}

void SystemInit(void)
{
    /* Workaround for FTPAN-32 "DIF: Debug session automatically enables TracePort pins" found at Product Anomaly document 
       for your device located at https://www.nordicsemi.com/ */
    if (ftpan_32()){        
        CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;
    }
    
    /* Workaround for FTPAN-37 "AMLI: EasyDMA is slow with Radio, ECB, AAR and CCM." found at Product Anomaly document 
       for your device located at https://www.nordicsemi.com/  */
    if (ftpan_37()){        
        *(volatile uint32_t *)0x400005A0 = 0x3;
    }
    
    /* Workaround for FTPAN-36 "CLOCK: Some registers are not reset when expected." found at Product Anomaly document 
       for your device located at https://www.nordicsemi.com/  */
    if (ftpan_36()){        
        NRF_CLOCK->EVENTS_DONE = 0;
        NRF_CLOCK->EVENTS_CTTO = 0;
    }

    /* Enable the FPU if the compiler used floating point unit instructions. __FPU_USED is a MACRO defined by the 
     * compiler. Since the FPU consumes energy, remember to disable FPU use in the compiler if floating point unit 
     * operations are not used in your code. */
    #if (__FPU_USED == 1)
        SCB->CPACR |= (3UL << 20) | (3UL << 22); 
        __DSB();
        __ISB();
    #endif
    
    /* Configure NFCT pins as GPIOs if NFCT is not to be used in your code. If CONFIG_NFCT_PINS_AS_GPIOS is not defined, 
       two GPIOs (see Product Specification to see which ones) will be reserved for NFC and will not be available as 
       normal GPIOs. */
    #if defined (CONFIG_NFCT_PINS_AS_GPIOS)
        if ((NRF_UICR->NFCPINS & UICR_NFCPINS_PROTECT_Msk) == (UICR_NFCPINS_PROTECT_NFC << UICR_NFCPINS_PROTECT_Pos)){
            NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
            while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}            
            NRF_UICR->NFCPINS &= ~UICR_NFCPINS_PROTECT_Msk;
            while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}            
            NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
            while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}            
            NVIC_SystemReset();
        }
    #endif
    
    /* Configure GPIO pads as pPin Reset pin if Pin Reset capabilities desired. If CONFIG_GPIO_AS_PINRESET is not
      defined, pin reset will not be available. One GPIO (see Product Specification to see which one) will then be 
      reserved for PinReset and not available as normal GPIO. */
    #if defined (CONFIG_GPIO_AS_PINRESET)
        if (((NRF_UICR->PSELRESET[0] & UICR_PSELRESET_CONNECT_Msk) != (UICR_PSELRESET_CONNECT_Connected << UICR_PSELRESET_CONNECT_Pos)) || 
            ((NRF_UICR->PSELRESET[0] & UICR_PSELRESET_CONNECT_Msk) != (UICR_PSELRESET_CONNECT_Connected << UICR_PSELRESET_CONNECT_Pos))){
            NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
            while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
            NRF_UICR->PSELRESET[0] = 21;
            while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
            NRF_UICR->PSELRESET[1] = 21;
            while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
            NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
            while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
            NVIC_SystemReset();
        }
    #endif
    
    /* Enable SWO trace functionality. If ENABLE_SWO is not defined, SWO pin will be used as GPIO (see Product 
       Specification to see which one). */
    #if defined (ENABLE_SWO)
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
        NRF_CLOCK->TRACECONFIG |= CLOCK_TRACECONFIG_TRACEMUX_Serial << CLOCK_TRACECONFIG_TRACEMUX_Pos;
    #endif
    
    /* Enable Trace functionality. If ENABLE_TRACE is not defined, TRACE pins will be used as GPIOs (see Product 
       Specification to see which ones). */
    #if defined (ENABLE_TRACE)
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
        NRF_CLOCK->TRACECONFIG |= CLOCK_TRACECONFIG_TRACEMUX_Parallel << CLOCK_TRACECONFIG_TRACEMUX_Pos;
    #endif

    SystemCoreClockUpdate();
}

static bool ftpan_32(void)
{
    if ((((*(uint32_t *)0xF0000FE0) & 0x000000FF) == 0x6) && (((*(uint32_t *)0xF0000FE4) & 0x0000000F) == 0x0))
    {
        if ((((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x30) && (((*(uint32_t *)0xF0000FEC) & 0x000000F0) == 0x0))
        {
            return true;
        }
    }
    
    return false;
}

static bool ftpan_37(void)
{
    if ((((*(uint32_t *)0xF0000FE0) & 0x000000FF) == 0x6) && (((*(uint32_t *)0xF0000FE4) & 0x0000000F) == 0x0))
    {
        if ((((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x30) && (((*(uint32_t *)0xF0000FEC) & 0x000000F0) == 0x0))
        {
            return true;
        }
    }
    
    return false;
}

static bool ftpan_36(void)
{
    if ((((*(uint32_t *)0xF0000FE0) & 0x000000FF) == 0x6) && (((*(uint32_t *)0xF0000FE4) & 0x0000000F) == 0x0))
    {
        if ((((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x30) && (((*(uint32_t *)0xF0000FEC) & 0x000000F0) == 0x0))
        {
            return true;
        }
    }
    
    return false;
}



/*lint --flb "Leave library region" */
