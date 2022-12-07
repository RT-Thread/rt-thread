/***************************************************************************//**
* \file ns_start_cyw20829.c
* \version 1.0
*
* The cyw20829 startup source.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include "cy_device.h"
#if defined (CY_DEVICE_CYW20829)

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include "startup_cat1b.h"
#include "cy_sysint.h"
#include "cy_syspm.h"
#include "cy_syslib.h"
#include "cmsis_compiler.h"

CY_MISRA_FP_BLOCK_START('MISRA C-2012 Rule 8.6', 3, \
'Checked manually. The definition is a part of linker script or application.');
CY_MISRA_DEVIATE_BLOCK_START('ARRAY_VS_SINGLETON', 1, \
'Checked manually. Using pointer as an array will not corrupt or misinterpret adjacent memory locations.');
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 18.1', 3, \
'Checked manually. Dereferencing a pointer to one beyond the end of an array will not result in undefined behaviour.');
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 18.3', 1, \
'Checked manually. Attempting to make comparisons between pointers will not result in undefined behaviour.');

#if defined (__ARMCC_VERSION)
extern uint32_t Region$$Table$$Base;
extern uint32_t Region$$Table$$Limit;
typedef  void(*pGenericFunction)(uint8_t *pSrc, uint8_t* pDst, uint32_t len);     /* typedef for the generic function pointers */
#endif

__WEAK interrupt_type void Reset_Handler(void);
interrupt_type void MemManage_Handler(void);
interrupt_type void BusFault_Handler(void);
interrupt_type void UsageFault_Handler(void);
__WEAK interrupt_type void SVC_Handler(void);
interrupt_type void DebugMon_Handler(void);
__WEAK interrupt_type void PendSV_Handler(void);
__WEAK interrupt_type void SysTick_Handler(void);
interrupt_type void InterruptHandler(void);
interrupt_type void NMIException_Handler(void);
interrupt_type void HardFault_Handler(void);
void delay_infinite(void);
void SysLib_FaultHandler(uint32_t const *faultStackAddr);
extern int main(void);

#if defined (__ARMCC_VERSION)
void __attribute__((optnone)) Cy_RuntimeInit(void);
#else
void Cy_RuntimeInit(void);
#endif

#if defined(__ARMCC_VERSION)
extern unsigned int Image$$ARM_LIB_STACK$$ZI$$Limit;            /* for (default) One Region model */
interrupt_type extern void __main(void);
typedef void(* ExecFuncPtrRw)(void) interrupt_type;
ExecFuncPtrRw __ns_vector_table_rw[VECTORTABLE_SIZE] __attribute__( ( section(".bss.noinit.RESET_RAM"))) __attribute__((aligned(VECTORTABLE_ALIGN)));
#elif defined (__GNUC__)
extern unsigned int __StackTop;
extern uint32_t __StackLimit;
typedef void(* interrupt_type ExecFuncPtrRw)(void);
ExecFuncPtrRw __ns_vector_table_rw[VECTORTABLE_SIZE]   __attribute__( ( section(".ram_vectors"))) __attribute__((aligned(VECTORTABLE_ALIGN)));
#elif defined (__ICCARM__)
extern unsigned int CSTACK$$Limit;                      /* for (default) One Region model */
interrupt_type extern void  __cmain();
ExecFuncPtrRw __ns_vector_table_rw[VECTORTABLE_SIZE]   __attribute__( ( section(".intvec_ram"))) __attribute__((aligned(VECTORTABLE_ALIGN)));
#else
    #error "An unsupported toolchain"
#endif  /* (__ARMCC_VERSION) */

void SysLib_FaultHandler(uint32_t const *faultStackAddr)
{
    Cy_SysLib_FaultHandler(faultStackAddr);
}

// Exception Vector Table & Handlers
//----------------------------------------------------------------
interrupt_type void NMIException_Handler(void)
{
    __asm volatile(
        "bkpt #10\n"
        "B .\n"
    );
}

interrupt_type void HardFault_Handler(void)
{
    __asm (
        "MRS R0, CONTROL\n"
        "TST R0, #2\n"
        "ITE EQ\n"
        "MRSEQ R0, MSP\n"
        "MRSNE R0, PSP\n"
        "B SysLib_FaultHandler\n"
    );
}

interrupt_type void MemManage_Handler(void)        {while(true){}}
interrupt_type void BusFault_Handler(void)    {while(true){}}
interrupt_type void UsageFault_Handler(void)    {while(true){}}
__WEAK interrupt_type void SVC_Handler(void)    {while(true){}}
interrupt_type void DebugMon_Handler(void)       {while(true){}}
__WEAK interrupt_type void PendSV_Handler(void)      {while(true){}}
__WEAK interrupt_type void SysTick_Handler(void)    {while(true){}}

interrupt_type void InterruptHandler(void)
{
    __asm volatile(
        "bkpt #1\n"
        "B .\n"
    );
}

ExecFuncPtr __ns_vector_table[] __VECTOR_TABLE_ATTRIBUTE = {
    (ExecFuncPtr)&__INITIAL_SP,
    (ExecFuncPtr)Reset_Handler,           // initial PC/Reset
    (ExecFuncPtr)NMIException_Handler,
    (ExecFuncPtr)HardFault_Handler,
    (ExecFuncPtr)MemManage_Handler,       // Memory Manage Fault
    (ExecFuncPtr)BusFault_Handler,        // Bus Fault
    (ExecFuncPtr)UsageFault_Handler,      // Usage Fault
    0,                                                  // Secire Fault
    0,                                                  // RESERVED
    0,                                                  // RESERVED
    0,                                                  // RESERVED
    (ExecFuncPtr)SVC_Handler,             // SVC
    0,                                                  // debug
    0,                                                  // RESERVED
    (ExecFuncPtr)PendSV_Handler,         // Pend SV
    (ExecFuncPtr)SysTick_Handler,         // Secure systick
    /* External interrupts */
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler,
    (ExecFuncPtr)InterruptHandler
};

// Reset Handler
__WEAK interrupt_type void Reset_Handler(void)
{
    /* Disable I cache */
    ICACHE0->CTL = ICACHE0->CTL & (~ICACHE_CTL_CA_EN_Msk);

    /* Enable ECC */
    //ICACHE0->CTL = ICACHE0->CTL | ICACHE_CTL_ECC_EN_Msk;

    /* Enable I cache */
    ICACHE0->CTL = ICACHE0->CTL | ICACHE_CTL_CA_EN_Msk;

    __disable_irq();

    for (uint32_t count = 0; count < VECTORTABLE_SIZE; count++)
    {
        __ns_vector_table_rw[count] =__ns_vector_table[count];
    }

    SCB->VTOR = (uint32_t)__ns_vector_table_rw;
    __DMB();

#ifdef FLASH_BOOT
#if !defined (__ARMCC_VERSION)
    bootstrapInit();
#endif
#endif
    SystemInit_CAT1B_CM33();

   __PROGRAM_START();
}

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 18.3');
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 18.1');
CY_MISRA_BLOCK_END('ARRAY_VS_SINGLETON');
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 8.6');

#endif /* defined (CY_DEVICE_CYW20829) */
