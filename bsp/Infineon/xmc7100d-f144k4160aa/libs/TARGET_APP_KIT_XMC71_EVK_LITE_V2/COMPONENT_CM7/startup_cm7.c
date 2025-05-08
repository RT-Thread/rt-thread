/***************************************************************************//**
* \file startup_cm7.c
* \version 1.0
*
* The device system-source file.
*
********************************************************************************
* \copyright
* Copyright 2021 Cypress Semiconductor Corporation
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


#include "cy_syslib.h"
#include "cmsis_compiler.h"
#include "startup_cat1c.h"
#include "core_cm7.h"
#include "system_cat1c.h"

#if defined(__cplusplus)
extern "C" {
#endif


extern void CM7_CpuIntr_Handler(uint8_t intrNum);

void Reset_Handler(void);

/* Internal Reference */
void Default_Handler(void);
void Default_NMIException_Handler(void);
void Default_Fault_Handler(void);
void SysLib_FaultHandler(uint32_t const *faultStackAddr);
__WEAK void cy_toolchain_init(void);
void FpuEnable(void);


#if defined(__ARMCC_VERSION)
extern unsigned int Image$$ARM_LIB_STACK$$ZI$$Limit;
interrupt_type extern void __main(void);
cy_israddress __ramVectors[VECTORTABLE_SIZE] __attribute__( ( section(".bss.noinit.RESET_RAM"))) __attribute__((aligned(VECTORTABLE_ALIGN)));
#elif defined (__GNUC__)
extern unsigned int __StackTop;
extern uint32_t __StackLimit;
cy_israddress __ramVectors[VECTORTABLE_SIZE]   __attribute__( ( section(".ram_vectors"))) __attribute__((aligned(VECTORTABLE_ALIGN)));
#elif defined (__ICCARM__)
extern unsigned int CSTACK$$Limit;
interrupt_type extern void  __cmain();
cy_israddress __ramVectors[VECTORTABLE_SIZE]   __attribute__( ( section(".intvec_ram"))) __attribute__((aligned(VECTORTABLE_ALIGN)));
#else
    #error "An unsupported toolchain"
#endif  /* (__ARMCC_VERSION) */

/* SCB->CPACR */
#define SCB_CPACR_CP10_CP11_ENABLE      (0xFUL << 20u)

/*******************************************************************************
* Function Name: FpuEnable
****************************************************************************//**
*
* Enables the FPU if it is used. The function is called from the startup file.
*
*******************************************************************************/
void FpuEnable(void)
{
    #if defined (__FPU_USED) && (__FPU_USED == 1U)
        uint32_t  interruptState;
        interruptState = Cy_SaveIRQ();
        SCB->CPACR |= SCB_CPACR_CP10_CP11_ENABLE;
        __DSB();
        __ISB();
        Cy_RestoreIRQ(interruptState);
    #endif /* (__FPU_USED) && (__FPU_USED == 1U) */
}


void SysLib_FaultHandler(uint32_t const *faultStackAddr)
{
    Cy_SysLib_FaultHandler(faultStackAddr);
}

/* Exception Vector Table & Handlers */
/*----------------------------------------------------------------*/
void Default_NMIException_Handler(void)
{
    __asm volatile(
        "bkpt #10\n"
        "B .\n"
    );
}

void Default_Fault_Handler(void)
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

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
    while(1);
}


/*******************************************************************************
* Function Name: Default_CM7_CpuIntr0_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt0 occurs.
*
*******************************************************************************/
CY_SECTION_ITCM_BEGIN
void Default_CpuIntr0_Handler(void)
{
    CM7_CpuIntr_Handler(0);
}
CY_SECTION_ITCM_END


/*******************************************************************************
* Function Name: Default_CM7_CpuIntr1_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt1 occurs.
*
*******************************************************************************/
CY_SECTION_ITCM_BEGIN
void Default_CpuIntr1_Handler(void)
{
    CM7_CpuIntr_Handler(1);
}
CY_SECTION_ITCM_END


/*******************************************************************************
* Function Name: Default_CM7_CpuIntr2_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt2 occurs.
*
*******************************************************************************/
CY_SECTION_ITCM_BEGIN
void Default_CpuIntr2_Handler(void)
{
    CM7_CpuIntr_Handler(2);
}
CY_SECTION_ITCM_END


/*******************************************************************************
* Function Name: Default_CM7_CpuIntr3_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt3 occurs.
*
*******************************************************************************/
CY_SECTION_ITCM_BEGIN
void Default_CpuIntr3_Handler(void)
{
    CM7_CpuIntr_Handler(3);
}
CY_SECTION_ITCM_END


/*******************************************************************************
* Function Name: Default_CM7_CpuIntr4_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt4 occurs.
*
*******************************************************************************/
CY_SECTION_ITCM_BEGIN
void Default_CpuIntr4_Handler(void)
{
    CM7_CpuIntr_Handler(4);
}
CY_SECTION_ITCM_END


/*******************************************************************************
* Function Name: Default_CM7_CpuIntr5_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt5 occurs.
*
*******************************************************************************/
CY_SECTION_ITCM_BEGIN
void Default_CpuIntr5_Handler(void)
{
    CM7_CpuIntr_Handler(5);
}
CY_SECTION_ITCM_END


/*******************************************************************************
* Function Name: Default_CM7_CpuIntr6_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt6 occurs.
*
*******************************************************************************/
CY_SECTION_ITCM_BEGIN
void Default_CpuIntr6_Handler(void)
{
    CM7_CpuIntr_Handler(6);
}
CY_SECTION_ITCM_END


/*******************************************************************************
* Function Name: Default_CM7_CpuIntr7_Handler
****************************************************************************//**
*
* The Handler is called when the CPU interrupt7 occurs.
*
*******************************************************************************/
CY_SECTION_ITCM_BEGIN
void Default_CpuIntr7_Handler(void)
{
    CM7_CpuIntr_Handler(7);
}
CY_SECTION_ITCM_END


void NMIException_Handler   (void) __attribute__ ((weak, alias("Default_NMIException_Handler")));
void HardFault_Handler      (void) __attribute__ ((weak, alias("Default_Fault_Handler")));
void MemManage_Handler      (void) __attribute__ ((weak, alias("Default_Fault_Handler")));
void BusFault_Handler       (void) __attribute__ ((weak, alias("Default_Fault_Handler")));
void UsageFault_Handler     (void) __attribute__ ((weak, alias("Default_Fault_Handler")));
void SVC_Handler            (void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler       (void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler         (void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler        (void) __attribute__ ((weak, alias("Default_Handler")));
void CM7_CpuIntr0_Handler   (void) __attribute__ ((weak, alias("Default_CpuIntr0_Handler")));
void CM7_CpuIntr1_Handler   (void) __attribute__ ((weak, alias("Default_CpuIntr1_Handler")));
void CM7_CpuIntr2_Handler   (void) __attribute__ ((weak, alias("Default_CpuIntr2_Handler")));
void CM7_CpuIntr3_Handler   (void) __attribute__ ((weak, alias("Default_CpuIntr3_Handler")));
void CM7_CpuIntr4_Handler   (void) __attribute__ ((weak, alias("Default_CpuIntr4_Handler")));
void CM7_CpuIntr5_Handler   (void) __attribute__ ((weak, alias("Default_CpuIntr5_Handler")));
void CM7_CpuIntr6_Handler   (void) __attribute__ ((weak, alias("Default_CpuIntr6_Handler")));
void CM7_CpuIntr7_Handler   (void) __attribute__ ((weak, alias("Default_CpuIntr7_Handler")));

extern const cy_israddress __Vectors[VECTORTABLE_SIZE];
#if defined (__GNUC__)
_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wpedantic\"")
#endif /* __GNUC__ */
const cy_israddress __Vectors[VECTORTABLE_SIZE] __VECTOR_TABLE_ATTRIBUTE = {
    (cy_israddress)&__INITIAL_SP,
    (cy_israddress)Reset_Handler,               /* initial PC/Reset */
    (cy_israddress)NMIException_Handler,        /* NMI */
    (cy_israddress)HardFault_Handler,           /* Hard Fault*/
    (cy_israddress)MemManage_Handler,           /* Memory Manage Fault */
    (cy_israddress)BusFault_Handler,            /* Bus Fault */
    (cy_israddress)UsageFault_Handler,          /* Usage Fault */
    0,                                          /* RESERVED */
    0,                                          /* RESERVED */
    0,                                          /* RESERVED */
    0,                                          /* RESERVED */
    (cy_israddress)SVC_Handler,                 /* SVC */
    (cy_israddress)DebugMon_Handler,            /* debug */
    0,                                          /* RESERVED */
    (cy_israddress)PendSV_Handler,              /* Pend SV */
    (cy_israddress)SysTick_Handler,             /* systick */
    /* External interrupts */
    (cy_israddress)CM7_CpuIntr0_Handler,
    (cy_israddress)CM7_CpuIntr1_Handler,
    (cy_israddress)CM7_CpuIntr2_Handler,
    (cy_israddress)CM7_CpuIntr3_Handler,
    (cy_israddress)CM7_CpuIntr4_Handler,
    (cy_israddress)CM7_CpuIntr5_Handler,
    (cy_israddress)CM7_CpuIntr6_Handler,
    (cy_israddress)CM7_CpuIntr7_Handler,
    /* Internal interrupts */
    (cy_israddress)Default_Handler,
    (cy_israddress)Default_Handler,
    (cy_israddress)Default_Handler,
    (cy_israddress)Default_Handler,
    (cy_israddress)Default_Handler,
    (cy_israddress)Default_Handler,
    (cy_israddress)Default_Handler,
    (cy_israddress)Default_Handler
};
#if defined (__GNUC__)
_Pragma("GCC diagnostic pop")
#endif /* __GNUC__ */

/* Provide empty __WEAK implementation for the low-level initialization
   routine required by the RTOS-enabled applications.
   clib-support library provides FreeRTOS-specific implementation:
   https://github.com/Infineon/clib-support */
void cy_toolchain_init(void);
__WEAK void cy_toolchain_init(void)
{
}

#if defined(__GNUC__) && !defined(__ARMCC_VERSION)
/* GCC: newlib crt0 _start executes software_init_hook.
   The cy_toolchain_init hook provided by clib-support library must execute
   after static data initialization and before static constructors. */
void software_init_hook();
void software_init_hook()
{
    cy_toolchain_init();
}
#elif defined(__ICCARM__)
/* Initialize data section */
void __iar_data_init3(void);

/* Call the constructors of all global objects */
void __iar_dynamic_initialization(void);

/* Define strong version to return zero for __iar_program_start
   to skip data sections initialization (__iar_data_init3). */
int __low_level_init(void);
int __low_level_init(void)
{
    return 0;
}
#else
/**/
#endif /* defined(__GNUC__) && !defined(__ARMCC_VERSION) */


// Reset Handler
void Reset_Handler(void)
{
    /* disable global interrupt */
    __disable_irq();

    /* Allow write access to Vector Table Offset Register and ITCM/DTCM configuration register
     * (CPUSS_CM7_X_CTL.PPB_LOCK[3] and CPUSS_CM7_X_CTL.PPB_LOCK[1:0]) */
#ifdef CORE_NAME_CM7_1
    CPUSS->CM7_1_CTL &= ~(0xB);
#elif CORE_NAME_CM7_0
    CPUSS->CM7_0_CTL &= ~(0xB);
#else
    #error "Not valid"
#endif

    __DSB();
    __ISB();

    /* Enable ITCM and DTCM */
    SCB->ITCMCR = SCB->ITCMCR | 0x7; /* Set ITCMCR.EN, .RMW and .RETEN fields */
    SCB->DTCMCR = SCB->DTCMCR | 0x7; /* Set DTCMCR.EN, .RMW and .RETEN fields */

#ifdef CORE_NAME_CM7_0
    CPUSS_CM7_0_CTL |= (0x1 << CPUSS_CM7_0_CTL_INIT_TCM_EN_Pos);
    CPUSS_CM7_0_CTL |= (0x2 << CPUSS_CM7_0_CTL_INIT_TCM_EN_Pos);
    CPUSS_CM7_0_CTL |= (0x1 << CPUSS_CM7_0_CTL_INIT_RMW_EN_Pos);
    CPUSS_CM7_0_CTL |= (0x2 << CPUSS_CM7_0_CTL_INIT_RMW_EN_Pos);
#elif CORE_NAME_CM7_1
    CPUSS_CM7_1_CTL |= (0x1 << CPUSS_CM7_1_CTL_INIT_TCM_EN_Pos);
    CPUSS_CM7_1_CTL |= (0x2 << CPUSS_CM7_1_CTL_INIT_TCM_EN_Pos);
    CPUSS_CM7_1_CTL |= (0x1 << CPUSS_CM7_1_CTL_INIT_RMW_EN_Pos);
    CPUSS_CM7_1_CTL |= (0x2 << CPUSS_CM7_1_CTL_INIT_RMW_EN_Pos);
#else
/**/
#endif

    // ITCMCR EN/RMW/RETEN enabled to access ITCM
    __UNALIGNED_UINT32_WRITE(((void const *)0xE000EF90), 0x2F);
    // DTCMCR EN/RMW/RETEN enabled to access DTCM
    __UNALIGNED_UINT32_WRITE(((void const *)0xE000EF94), 0x2F);

    /* Enable FPU if present */
    FpuEnable();

    /* copy vector table */
    for (uint32_t count = 0; count < VECTORTABLE_SIZE; count++)
    {
        __ramVectors[count] =__Vectors[count];
    }

    SCB->VTOR = (uint32_t)__ramVectors;

    __DSB();
    __ISB();

#ifdef ENABLE_CM7_INSTRUCTION_CACHE
    SCB_EnableICache();
#endif /* ENABLE_CM7_INSTRUCTION_CACHE */
#ifdef ENABLE_CM7_DATA_CACHE
    SCB_EnableDCache();
#else
    // Ensure that the undefined valid bits in the cache RAM are set to invalid if cache is disabled, because the application
    // may call further cache maintenance functions (e.g. SCB_CleanInvalidateDCache) independent of the "cache enabled" state.
    SCB_InvalidateDCache();
#endif /* ENABLE_CM7_DATA_CACHE */

    SystemInit();

#if defined(__ICCARM__)
    /* Initialize data section */
    __iar_data_init3();

    /* Initialization hook for RTOS environment  */
    cy_toolchain_init();

    /* Call the constructors of all global objects */
    __iar_dynamic_initialization();
#endif

    /* c-runtime */
    __PROGRAM_START();
}


#if defined(__cplusplus)
}
#endif


/* [] END OF FILE */
