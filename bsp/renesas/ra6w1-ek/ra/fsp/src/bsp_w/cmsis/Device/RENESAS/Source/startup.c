/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 * @{
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"
#include <stdint.h>

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#if BSP_TZ_SECURE_BUILD
 #define BSP_TZ_STACK_SEAL_SIZE    (8U)
#else
 #define BSP_TZ_STACK_SEAL_SIZE    (0U)
#endif

#define BSP_PRV_MAGIC_WORD_ADDR    (0x23010000)
#define BSP_PRV_MAGIC_WORD_0       (0xDEADBEEF)
#define BSP_PRV_MAGIC_WORD_1       (0xDEAD10CC)
#define BSP_PRV_DBG_DELAY_ITER     (0x15000)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/* Defines function pointers to be used with vector table. */
typedef void (* exc_ptr_t)(void);

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/
void Default_Handler(void);
void Reset_Handler(void);

#if defined(__ICCARM__)
extern void __iar_program_start(void);

#elif defined(__GNUC__) || defined(__ARMCC_VERSION)
extern void _start(void);
static void bsp_gcc_call_init_array(void);

#endif

#if (!BSP_TZ_NONSECURE_BUILD) && (BSP_CFG_STARTUP_MAGIC_CHECK)
static void bsp_debugger_attach_poll(void);

#endif

#if (BSP_CFG_IVT_COPY_ENABLE)
static void bsp_vector_table_copy(void);

#endif

#if (BSP_CFG_WAKEUP_RESET_HANDLER_ENABLE)
BSP_PLACE_CODE_IN_RAM static void Wakeup_Reset_Handler(void);
static void                       bsp_wakeup_reset_handler_set(void);

#endif

/*******************************************************************************************************************//**
 * MCU starts executing here out of reset. Main stack pointer is set up already.
 **********************************************************************************************************************/
void Reset_Handler (void)
{
#if (!BSP_TZ_NONSECURE_BUILD) && (BSP_CFG_STARTUP_MAGIC_CHECK)
    bsp_debugger_attach_poll();
#endif

#if (BSP_CFG_IVT_COPY_ENABLE)
    bsp_vector_table_copy();
#endif

#if (BSP_CFG_WAKEUP_RESET_HANDLER_ENABLE)
    bsp_wakeup_reset_handler_set();
#endif

    /* Initialize system using BSP. */
    SystemInit();

#if defined(__ICCARM__)
    __iar_program_start();
#elif defined(__GNUC__) || defined(__ARMCC_VERSION)
    bsp_gcc_call_init_array();
    extern int entry(void);
    entry();
#endif

    while (1)
    {
        /* Infinite Loop. */
    }
}

/*******************************************************************************************************************//**
 * Run init array entries without invoking newlib _start().
 **********************************************************************************************************************/
#if defined(__GNUC__) || defined(__ARMCC_VERSION)
static void bsp_gcc_call_init_array (void)
{
    extern void (* __preinit_array_start[])(void);
    extern void (* __preinit_array_end[])(void);
    extern void (* __init_array_start[])(void);
    extern void (* __init_array_end[])(void);

    for (void (** p_func)(void) = __preinit_array_start; p_func < __preinit_array_end; p_func++)
    {
        (*p_func)();
    }

    for (void (** p_func)(void) = __init_array_start; p_func < __init_array_end; p_func++)
    {
        (*p_func)();
    }
}

#endif

/*******************************************************************************************************************//**
 * Default exception handler.
 **********************************************************************************************************************/
void Default_Handler (void)
{
    CRG_TOP->SYS_CTRL_REG_b.DEBUGGER_ENABLE = 1;

    BSP_CFG_HANDLE_UNRECOVERABLE_ERROR(0);

    while (1)
    {
        __NOP();
    }

    ;
}

/* Main stack */
uint8_t g_main_stack[BSP_CFG_STACK_MAIN_BYTES + BSP_TZ_STACK_SEAL_SIZE] BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);

/* Heap */
BSP_DONT_REMOVE uint8_t g_heap[BSP_CFG_HEAP_BYTES] BSP_ALIGN_VARIABLE(BSP_STACK_ALIGNMENT);

/* All system exceptions in the vector table are weak references to Default_Handler. If the user wishes to handle
 * these exceptions in their code they should define their own function with the same name.
 */
#if defined(__ICCARM__)
 #define WEAK_REF_ATTRIBUTE

 #pragma weak NMI_Handler                              = Default_Handler
 #pragma weak MemManage_Handler                        = Default_Handler
 #pragma weak BusFault_Handler                         = Default_Handler
 #pragma weak UsageFault_Handler                       = Default_Handler
 #pragma weak SecureFault_Handler                      = Default_Handler
 #pragma weak SVC_Handler                              = Default_Handler
 #pragma weak DebugMon_Handler                         = Default_Handler
 #pragma weak PendSV_Handler                           = Default_Handler
 #pragma weak SysTick_Handler                          = Default_Handler
#elif defined(__GNUC__)

 #define WEAK_REF_ATTRIBUTE    __attribute__((weak, alias("Default_Handler")))
#endif

void HardFault_Handler(void);          // Implemented in ARM assembly.
void NMI_Handler(void) WEAK_REF_ATTRIBUTE;
void MemManage_Handler(void) WEAK_REF_ATTRIBUTE;
void BusFault_Handler(void) WEAK_REF_ATTRIBUTE;
void UsageFault_Handler(void) WEAK_REF_ATTRIBUTE;
void SecureFault_Handler(void) WEAK_REF_ATTRIBUTE;
void SVC_Handler(void) WEAK_REF_ATTRIBUTE;
void DebugMon_Handler(void) WEAK_REF_ATTRIBUTE;
void PendSV_Handler(void) WEAK_REF_ATTRIBUTE;
void SysTick_Handler(void) WEAK_REF_ATTRIBUTE;

/* Vector table. */
BSP_DONT_REMOVE const exc_ptr_t __VECTOR_TABLE[BSP_CORTEX_VECTOR_TABLE_ENTRIES] BSP_PLACE_IN_SECTION(
    BSP_SECTION_FIXED_VECTORS) =
{
    (exc_ptr_t) (&g_main_stack[0] + BSP_CFG_STACK_MAIN_BYTES), /*      Initial Stack Pointer     */
    Reset_Handler,                                             /*      Reset Handler             */
    NMI_Handler,                                               /*      NMI Handler               */
    HardFault_Handler,                                         /*      Hard Fault Handler        */
    MemManage_Handler,                                         /*      MPU Fault Handler         */
    BusFault_Handler,                                          /*      Bus Fault Handler         */
    UsageFault_Handler,                                        /*      Usage Fault Handler       */
    SecureFault_Handler,                                       /*      Secure Fault Handler      */
    0,                                                         /*      Reserved                  */
    0,                                                         /*      Reserved                  */
    0,                                                         /*      Reserved                  */
    SVC_Handler,                                               /*      SVCall Handler            */
    DebugMon_Handler,                                          /*      Debug Monitor Handler     */
    0,                                                         /*      Reserved                  */
    PendSV_Handler,                                            /*      PendSV Handler            */
    SysTick_Handler,                                           /*      SysTick Handler           */
};

#if BSP_CFG_IVT_COPY_ENABLE
BSP_DONT_REMOVE exc_ptr_t RAM_VECTOR_TABLE_COPY[BSP_VECTOR_TABLE_MAX_ENTRIES] BSP_PLACE_IN_SECTION(
    ".fsp_vector_table_copy");
BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(
    BSP_SECTION_APPLICATION_VECTORS) __attribute__((weak));

/*******************************************************************************************************************//**
 * Relocate the vector table to RAM. Substitute the Reset_Handler with the Wakeup_Reset_Handler for low power mode
 * support.
 **********************************************************************************************************************/
static void bsp_vector_table_copy (void)
{
    if (((uint32_t) RAM_VECTOR_TABLE_COPY) != SCB->VTOR)
    {
        /* Copy Vector Table to allocated space in RAM. */
        for (uint8_t it = 0; it < BSP_CORTEX_VECTOR_TABLE_ENTRIES; it++)
        {
            RAM_VECTOR_TABLE_COPY[it] = __VECTOR_TABLE[it];
        }

        for (uint8_t it = 0; it < BSP_ICU_VECTOR_MAX_ENTRIES; it++)
        {
            RAM_VECTOR_TABLE_COPY[BSP_CORTEX_VECTOR_TABLE_ENTRIES + it] = g_vector_table[it];
        }

        /* Update VTOR value. */
        SCB->VTOR = ((uint32_t) RAM_VECTOR_TABLE_COPY);

 #if !BSP_TZ_NONSECURE_BUILD
        SYSB->INITSVTOR_REG = ((uint32_t) RAM_VECTOR_TABLE_COPY);
 #else
        SYSB->INITNSVTOR_REG = ((uint32_t) RAM_VECTOR_TABLE_COPY);
 #endif
    }
}

#endif

#if (BSP_CFG_WAKEUP_RESET_HANDLER_ENABLE)

void wakeup_from_deepsleep(void);

BSP_PLACE_CODE_IN_RAM static void Wakeup_Reset_Handler (void)
{
    /* If this register is zeroed then this is a wakeup from deepsleep.
     * Otherwise it is a cold boot.
     */
    if (CRG_TOP->RESET_STAT_REG != 0)
    {
        Reset_Handler();
    }
    else
    {
        /* Call to assembly function that will restore the state of the SYSCPU. */
        wakeup_from_deepsleep();

        /* Wakeup from deepsleep returns execution to the function that called sleep.
         * This should not be reached.
         */
        BSP_CHECK_FATAL(0);
    }
}

static void bsp_wakeup_reset_handler_set (void)
{
    uint32_t * p_vector_table = (uint32_t *) SCB->VTOR;

    p_vector_table[1] = (uint32_t) Wakeup_Reset_Handler;
}

#endif

#if (!BSP_TZ_NONSECURE_BUILD) && (BSP_CFG_STARTUP_MAGIC_CHECK)

/*******************************************************************************************************************//**
 * Block execution until a debugger is attached if certain magic words are located in RAM.
 **********************************************************************************************************************/
static void bsp_debugger_attach_poll (void)
{
    volatile uint32_t * p_magic = (uint32_t *) BSP_PRV_MAGIC_WORD_ADDR;

    if ((BSP_PRV_MAGIC_WORD_0 == p_magic[0]) &&
        (BSP_PRV_MAGIC_WORD_0 == p_magic[1]) &&
        (BSP_PRV_MAGIC_WORD_0 == p_magic[2]) &&
        (BSP_PRV_MAGIC_WORD_1 == p_magic[3]))
    {
        uint32_t debug_setting = CRG_TOP->SYS_CTRL_REG;

        /* Enable debugger. */
        CRG_TOP->SYS_CTRL_REG = debug_setting | CRG_TOP_SYS_CTRL_REG_DEBUGGER_ENABLE_Msk;

        /* Refresh Watchdog */
        WDTSYS->WDTSYS_REG = 0xFF;

        for (volatile uint32_t it = BSP_PRV_DBG_DELAY_ITER; it > 0; it--)
        {
            ;
        }

        /* Clear magic so that this is skipped in the event of a SW reset. */
        p_magic[0] = 0;

        CRG_TOP->SYS_CTRL_REG = debug_setting;
    }
}

#endif

/** @} (end addtogroup BSP_MCU) */
