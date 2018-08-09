/**************************************************************************************
* Copyright (c) 2016-2017, ARM Limited or its affiliates. All rights reserved         *
*                                                                                     *
* This file and the related binary are licensed under the following license:          *
*                                                                                     *
* ARM Object Code and Header Files License, v1.0 Redistribution.                      *
*                                                                                     *
* Redistribution and use of object code, header files, and documentation, without     *
* modification, are permitted provided that the following conditions are met:         *
*                                                                                     *
* 1) Redistributions must reproduce the above copyright notice and the                *
*    following disclaimer in the documentation and/or other materials                 *
*    provided with the distribution.                                                  *
*                                                                                     *
* 2) Unless to the extent explicitly permitted by law, no reverse                     *
*    engineering, decompilation, or disassembly of is permitted.                      *
*                                                                                     *
* 3) Redistribution and use is permitted solely for the purpose of                    *
*    developing or executing applications that are targeted for use                   *
*    on an ARM-based product.                                                         *
*                                                                                     *
* DISCLAIMER. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND                  *
* CONTRIBUTORS "AS IS." ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT             *
* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT,        *
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          *
* COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED            *
* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR              *
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF              *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING                *
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                  *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                        *
**************************************************************************************/
#ifdef DX_LINUX_PLATFORM
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#endif
#include "ssi_pal_types.h"
#include "ssi_regs.h"

#include "integration_test_plat_defs.h"
#include "crys_rnd.h"

#include "nrf52840.h"
#include "SEGGER_RTT.h"

/*Globals*/
uint32_t g_free_mem_addr;
uint32_t *g_test_stack_base_addr;
uint32_t g_rom_base_addr;
uint32_t g_env_rom_base_addr;


CRYS_RND_WorkBuff_t*  rndWorkBuff_ptr;
CRYS_RND_State_t*     rndState_ptr;

#if defined(__CC_ARM)
CRYS_RND_State_t   	 rndState = {0};
CRYS_RND_WorkBuff_t  rndWorkBuff = {0};
#else
CRYS_RND_State_t   	 rndState;
CRYS_RND_WorkBuff_t  rndWorkBuff;
#endif

uint32_t* UserSpace = 0;


//initializatoins that need to be done prior to running the integration tests.
SaSiError_t integration_tests_setup(void)
{
    SaSiError_t ret = 0;
    rndState_ptr = &rndState;
    rndWorkBuff_ptr = &rndWorkBuff;

    // Initialize Segger RTT logging

    (void)SEGGER_RTT_Init();

    INTEG_TEST_PRINT("==================== TEST START ====================\r\n");

    NVIC_EnableIRQ(CRYPTOCELL_IRQn);

    NRF_CRYPTOCELL->ENABLE = 1;

    return ret;
}


void integration_tests_clear(void)
{
    INTEG_TEST_PRINT("==================== TEST END ====================\r\n");
    while(1)
    {
        __WFI();
    }
}


void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
    (void)id;
    (void)pc;
    (void)info;
    while(1);
}


void SaSi_PalAbort(const char *msg)
{
    // This function overrides SaSi_PalAbort implemented in the library.
    // The library version does a NVIC_SystemReset() and has no logging.
    INTEG_TEST_PRINT("CC310 abort called: %s\r\n", msg);
    while(1);
}
