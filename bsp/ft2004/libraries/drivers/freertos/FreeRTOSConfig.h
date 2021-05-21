/*
 * FreeRTOS V202011.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

/*
 * The FreeRTOS Cortex-A port implements a full interrupt nesting model.
 *
 * Interrupts that are assigned a priority at or below
 * configMAX_API_CALL_INTERRUPT_PRIORITY (which counter-intuitively in the ARM
 * generic interrupt controller [GIC] means a priority that has a numerical
 * value above configMAX_API_CALL_INTERRUPT_PRIORITY) can call FreeRTOS safe API
 * functions and will nest.
 *
 * Interrupts that are assigned a priority above
 * configMAX_API_CALL_INTERRUPT_PRIORITY (which in the GIC means a numerical
 * value below configMAX_API_CALL_INTERRUPT_PRIORITY) cannot call any FreeRTOS
 * API functions, will nest, and will not be masked by FreeRTOS critical
 * sections (although it is necessary for interrupts to be globally disabled
 * extremely briefly as the interrupt mask is updated in the GIC).
 *
 * FreeRTOS functions that can be called from an interrupt are those that end in
 * "FromISR".  FreeRTOS maintains a separate interrupt safe API to enable
 * interrupt entry to be shorter, faster, simpler and smaller.
 *
 */
#define configMAX_API_CALL_INTERRUPT_PRIORITY (16 - 1)

#define configCPU_CLOCK_HZ 100000000UL
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#define configUSE_TICKLESS_IDLE 0
#define configTICK_RATE_HZ ((TickType_t)100)
#define configUSE_PREEMPTION 1
#define configUSE_IDLE_HOOK 1
#define configUSE_TICK_HOOK 1
#define configMAX_PRIORITIES (7)
#define configMINIMAL_STACK_SIZE ((unsigned short)256)
#define configTOTAL_HEAP_SIZE (4096 * 1024)
#define configMAX_TASK_NAME_LEN (20)
#define configUSE_TRACE_FACILITY 1
#define configUSE_16_BIT_TICKS 0
#define configIDLE_SHOULD_YIELD 1
#define configUSE_MUTEXES 1
#define configQUEUE_REGISTRY_SIZE 8
#define configCHECK_FOR_STACK_OVERFLOW 0
#define configUSE_RECURSIVE_MUTEXES 1
#define configUSE_MALLOC_FAILED_HOOK 1
#define configUSE_APPLICATION_TASK_TAG 0
#define configUSE_COUNTING_SEMAPHORES 1
#define configUSE_QUEUE_SETS 1
#define configSUPPORT_STATIC_ALLOCATION 0
#define configSUPPORT_DYNAMIC_ALLOCATION 1

/* Include the query-heap CLI command to query the free heap space. */
#define configINCLUDE_QUERY_HEAP_COMMAND 1

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 0
#define configMAX_CO_ROUTINE_PRIORITIES (2)

/* Software timer definitions. */
#define configUSE_TIMERS 1
#define configTIMER_TASK_PRIORITY (configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH 5
#define configTIMER_TASK_STACK_DEPTH (configMINIMAL_STACK_SIZE * 2)

/* If configUSE_TASK_FPU_SUPPORT is set to 1 (or undefined) then each task will
be created without an FPU context, and a task must call vTaskUsesFPU() before
making use of any FPU registers.  If configUSE_TASK_FPU_SUPPORT is set to 2 then
tasks are created with an FPU context by default, and calling vTaskUsesFPU() has
no effect. */
#define configUSE_TASK_FPU_SUPPORT 1

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet 1
#define INCLUDE_uxTaskPriorityGet 1
#define INCLUDE_vTaskDelete 1
#define INCLUDE_vTaskCleanUpResources 1
#define INCLUDE_vTaskSuspend 1
#define INCLUDE_vTaskDelayUntil 1
#define INCLUDE_vTaskDelay 1
#define INCLUDE_xTimerPendFunctionCall 1
#define INCLUDE_eTaskGetState 1
#define INCLUDE_xTaskAbortDelay 1
#define INCLUDE_xTaskGetTaskHandle 1
#define INCLUDE_xTaskGetHandle 1
#define INCLUDE_xSemaphoreGetMutexHolder 1

/* This demo makes use of one or more example stats formatting functions.  These
format the raw data provided by the uxTaskGetSystemState() function in to human
readable ASCII form.  See the notes in the implementation of vTaskList() within
FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS 1

/* Run time stats are not generated.  portCONFIGURE_TIMER_FOR_RUN_TIME_STATS and
portGET_RUN_TIME_COUNTER_VALUE must be defined if configGENERATE_RUN_TIME_STATS
is set to 1. */
#define configGENERATE_RUN_TIME_STATS 0
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()
#define portGET_RUN_TIME_COUNTER_VALUE()

/* The size of the global output buffer that is available for use when there
are multiple command interpreters running at once (for example, one on a UART
and one on TCP/IP).  This is done to prevent an output buffer being defined by
each implementation - which would waste RAM.  In this case, there is only one
command interpreter running. */
#define configCOMMAND_INT_MAX_OUTPUT_SIZE 2096

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
// void vAssertCalled(const char *pcFile, unsigned long ulLine);
// #define configASSERT(x)
//     if ((x) == 0)
//         vAssertCalled(__FILE__, __LINE__);

#define configASSERT(x)                                                 \
    if ((x) == 0)                                                       \
    {                                                                   \
        extern void Ft_printf(const char *fmt, ...);                    \
        Ft_printf("configASSERT  is %s : %d \r\n", __FILE__, __LINE__); \
        taskDISABLE_INTERRUPTS();                                       \
        for (;;)                                                        \
            ;                                                           \
    }

/* If configTASK_RETURN_ADDRESS is not defined then a task that attempts to
return from its implementing function will end up in a "task exit error"
function - which contains a call to configASSERT().  However this can give GCC
some problems when it tries to unwind the stack, as the exit error function has
nothing to return to.  To avoid this define configTASK_RETURN_ADDRESS to 0.  */
#define configTASK_RETURN_ADDRESS NULL

/****** Hardware specific settings. *******************************************/

/*
 * The application must provide a function that configures a peripheral to
 * create the FreeRTOS tick interrupt, then define configSETUP_TICK_INTERRUPT()
 * in FreeRTOSConfig.h to call the function.    FreeRTOS_Tick_Handler() must
 * be installed as the peripheral's interrupt handler.
 */

#define configSETUP_TICK_INTERRUPT()                                                                                                          \
    do                                                                                                                                        \
    {                                                                                                                                         \
        void SystemSetupSystick(u32 tickRateHz, void *tickHandler, u32 intPriority);                                                          \
        /* Setup systick with lowest priority */                                                                                              \
        SystemSetupSystick(configTICK_RATE_HZ, (void *)FreeRTOS_Tick_Handler, (configUNIQUE_INTERRUPT_PRIORITIES - 2) << portPRIORITY_SHIFT); \
    } while (0)

#define configCLEAR_TICK_INTERRUPT() \
    do                               \
    {                                \
    } while (0)

#define FreeRTOS_IRQ_Handler IRQ_Handler
#define FreeRTOS_SWI_Handler SVC_Handler

#define configINTERRUPT_CONTROLLER_BASE_ADDRESS (0x71800000)
#define configINTERRUPT_CONTROLLER_CPU_INTERFACE_OFFSET (0x2000UL)
#define configUNIQUE_INTERRUPT_PRIORITIES 16

/****** Network configuration settings - only used when the lwIP example is
built.  See the page that documents this demo on the http://www.FreeRTOS.org
website for more information. ***********************************************/

/* The priority for the task that unblocked by the MAC interrupt to process
received packets. */
#define configMAC_INPUT_TASK_PRIORITY (configMAX_PRIORITIES - 1)

/* The priority of the task that runs the lwIP stack. */
#define configLWIP_TASK_PRIORITY (configMAX_PRIORITIES - 2)

/* The priority of the task that uses lwIP sockets to provide a simple command
line interface. */
#define configCLI_TASK_PRIORITY (tskIDLE_PRIORITY)

/* MAC address configuration. */
#define configMAC_ADDR0 0x00
#define configMAC_ADDR1 0x13
#define configMAC_ADDR2 0x14
#define configMAC_ADDR3 0x15
#define configMAC_ADDR4 0x15
#define configMAC_ADDR5 0x16

/* IP address configuration. */
#define configIP_ADDR0 172
#define configIP_ADDR1 25
#define configIP_ADDR2 218
#define configIP_ADDR3 200

/* Netmask configuration. */
#define configNET_MASK0 255
#define configNET_MASK1 255
#define configNET_MASK2 255
#define configNET_MASK3 0

#endif /* FREERTOS_CONFIG_H */
