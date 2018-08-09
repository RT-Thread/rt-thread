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

#include <stdio.h>
#include "SEGGER_RTT.h"
#include "ssi_pal_types_plat.h"

#if DX_LINUX_PLATFORM
extern uint32_t g_free_mem_addr;
extern uint32_t *g_test_stack_base_addr;
extern uint32_t g_rom_base_addr;
extern uint32_t g_env_rom_base_addr;
#endif


SaSiError_t   mapEnvMemory(void);
void unmapMemory(void);
SaSiError_t integration_tests_setup(void);
void integration_tests_clear(void);


#define REG_BASE_ADR			DX_BASE_CC
#define REG_AREA_LEN			0x20000
#define ENV_REG_BASE_ADR		DX_BASE_ENV_REGS
#define ENV_REG_AREA_LEN		0x20000
#define SRAM_BASE_ADR			0
#define TEST_DATA_START_ADDRESS         sizeof(CRYS_RND_State_t)+sizeof(CRYS_RND_WorkBuff_t)

/* Zynq EVBs have 1GB and we reserve the memory at offset 768M */
#define FREE_MEM_BASE_ADR             	0x20020000
#define CONTIG_FREE_MEM	                0x8000
/* Free memory is dedicated for SW image storage */
#define BOOT_FREE_MEM_BASE_ADR          FREE_MEM_BASE_ADR
#define BOOT_FREE_MEM_LEN		0x500000

/* user space follows the free memory, and uses for stack and workspace memory */
#define PTHREAD_STACK_BASE_ADR		(FREE_MEM_BASE_ADR + CONTIG_FREE_MEM)
#define PTHREAD_STACK_SIZE		16*1024

#define WORKSPACE_BASE_ADDR         (PTHREAD_STACK_BASE_ADR + PTHREAD_STACK_SIZE)

#define INTEG_TEST_PRINT(...)           SEGGER_RTT_printf(0, __VA_ARGS__)
