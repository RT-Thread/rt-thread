/***************************************************************************//**
* \file system_cyw20829.h
* \version 1.0
*
* \brief Device system header file.
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

#ifndef _SYSTEM_CYW20829_H_
#define _SYSTEM_CYW20829_H_

/**
* \addtogroup group_system_config_cm33
* \{
* Provides device startup, system configuration, and linker script files.
* The system startup provides the followings features:
* - \ref group_system_config_device_memory_definition_cm33
* - \ref group_system_config_device_initialization_cm33
* - \ref group_system_config_heap_stack_config_cm33
* - \ref group_system_config_default_handlers_cm33
* - \ref group_system_config_device_vector_table_cm33
*
* \section group_system_config_configuration_cm33 Configuration Considerations
*
* \subsection group_system_config_device_memory_definition_cm33 Device Memory Definition
* Allocation of different types of memory such as the ROM, flash and RAM etc. for the CPU is defined by the linker scripts.
*
* \note The linker files provided with the PDL are generic and handle all common
* use cases. Your project may not use every section defined in the linker files.
* In that case you may see warnings during the build process. To eliminate build
* warnings in your project, you can simply comment out or remove the relevant
* code in the linker file.
*
* <b>For CYW20829</b>
*
* <b>ARM GCC</b>\n
* The ROM, flash and RAM sections for the CPU are defined in the linker file:
* 'cyw20829_ns_flash_cbus.ld', where 'ns' indicates that the
* linker script file is for non-secure image.
* For devices without security extension, there will be only one linker file and it
* is always non-secure.
*
* Memory sections are for the GNU GCC ARM tool set is defined in the linker file
* cyw20829_ns_flash_cbus.ld. Following are the important memory sections for the User/Application image.
*
* Memory sections are for the GNU GCC ARM tool set is defined in the linker file
* \<device\>_ns.sct. Following are the important memory sections for the User/Application image.
* \code
* code        (rx)  : ORIGIN = CODE_VMA,      LENGTH = CODE_BS_SIZE  Starting address and the size of Non-secure bootstrap code
* bsData      (rwx) : ORIGIN = DATA_BS_VMA,   LENGTH = DATA_BS_SIZE  Starting address and the size of Non-secure bootstrap data
* appCodeRam  (rx)  : ORIGIN = DATA_CBUS_VMA, LENGTH = DATA_SIZE     Starting address and the size of Non-secure application ram functions
* data        (rwx) : ORIGIN = DATA_VMA,      LENGTH = DATA_SIZE     Starting address and the size of Non-secure application data
* xip         (rx)  : ORIGIN = XIP_VMA,       LENGTH = XIP_SIZE      Starting address and the size of Non-secure application code
* \endcode
*
* \note In CYW20829, the Bootstrap memory is used to place the startup code along with SMIF driver in the ram area. The size requirement for Bootstrap may vary
* depending on the number of functions that are linked from SMIF driver. When more functions are linked, you may see linker error.
* In order to fix this you need to increase Bootstarp memory size in the ram by modifying the value of BOOTSTRAP_OFFSET_RAM.\n
* E.g. if linker error suggests to increase by 8192 bytes, then you need to move the starting address of the bootstrap memory up by 8192 bytes as shown below \n
* BOOTSTRAP_OFFSET_RAM        = 0x0001E000; Old value\n
* BOOTSTRAP_OFFSET_RAM        = 0x0001C000; New value\n
* Because of the change in the bootstrap size, you may also need to move the application start address in the flash. If you see a linker error after above change,
* then you need to modify the application code offset APPCODE_OFFSET_FLASH in the flash.\n
* E.g. if linker error suggests 256 bytes overlap of .appText LMA with .bootstrapText LMA, you need to move the application start offset in the flash
* down by 256 bytes as shown below\n
* APPCODE_OFFSET_FLASH        = 0x00002200; Old value\n
* APPCODE_OFFSET_FLASH        = 0x00002300; New value
*
* <b>ARM Compiler</b>\n
* The ROM, flash and RAM sections for the CPU are defined in the linker file:
* 'cyw20829_ns_flash_cbus.sct', where 'ns' indicates that the
* linker script file is for non-secure image.
* For devices without security extension, there will be only one linker file and it
* is always non-secure.
*
* Memory sections are for the GNU GCC ARM tool set is defined in the linker file
* cyw20829_ns_flash_cbus.sct. Following are the important memory sections for the User/Application image.
* \code
* bootstrapText_vma   Starting address of bootstrap code
* bootstrapText_size  Size of memory reserved for Bootstrap code
* bootstrapData_vma   Starting address of Bootstrap data
* appText_vma         Stating address of application code
* appData_vma         Stating address of application data
* \endcode
*
* <b>IAR</b>\n
* The ROM, flash and RAM sections for the CPU are defined in the linker file:
* 'cyw20829_ns_flash_cbus.icf', where 'ns' indicates that the
* linker script file is for non-secure image.
* For devices without security extension, there will be only one linker file and it
* is always non-secure.
*
* Memory sections are for the GNU GCC ARM tool set is defined in the linker file
* cyw20829_ns_flash_cbus.icf. Following are the important memory sections for the User/Application image.
* \code
* define region CODE_region     = mem:[from CODE_VMA size CODE_BS_SIZE];      Bootstrap code region and size
* define region DATA_BS_region  = mem:[from DATA_BS_VMA size DATA_BS_SIZE];   Bootstrap data region and size
* define region DATA_region     = mem:[from DATA_VMA size DATA_SIZE];         Application data region and size
* define region XIP_region      = mem:[from XIP_VMA size XIP_SIZE];           Application code (xip) region and size
* \endcode
*
* \subsection group_system_config_device_initialization_cm33 Device Initialization
* <b>CM33 Without ARM TrustZone Support:</b><br/>
* Below MSC describes the simplified startup sequence starting from reset release of the core. As soon as the reset
* is released, the execution starts form the ROM interrupt vector table reset vector. The ROM code initializes the basic
* clock needed to access and configure MMIO registers and then sets up debug port so that the debugger can be attached.
* After it finishes all the necessary initialization, it reads the bootstrap (part of non secure application image)
* location, size from TOC2 header and loads the bootstrap code into SRAM.
*
* Before switching execution to the non-secure application code, the ROM code needs to initialize the stack pointer
* MSP_NS for the non-secure code. This value is picked form the first entry in the non-secure bootstrap's vector
* table __ns_vector_table. Once the non-secure stack is initialized, the ROM code will call the non-secure code entry
* point which is nothing but the Reset_Handler. Address of this function is picked form the second entry in the non-secure
* vector table __ns_vector_table and type casting it to function pointer.
*
* In the non-secure Reset_Handler, the vector table is copied to RAM area and then the address of the vector table is set
* to VTOR register. This calls SystemInit function which internally calls Cy_PDL_Init, Cy_SystemInit and SystemCoreClockUpdate
* functions. Then it calls C runtime initialization function which calls main function of the application code.
*
* Below sequence diagram captures the initialization process in the startup code.
* ![](explorer_ns_startup.png)
*
* \subsection group_system_config_heap_stack_config_cm33 Heap and Stack Configuration
* By default, the stack size is set to 0x00001000 and the entire remaining ram is used for the heap
*
* \subsubsection group_system_config_heap_stack_config_gcc_cm33 ARM GCC
* - <b>Editing source code files for non-secure image</b>\n
* The stack and heap sizes are defined in the linker script file: 'cyw20829_ns_flash_cbus.ld'.
* Change the stack size by modifying the following line:\n
* \code STACK_SIZE = 0x00001000; \endcode
* Remaining free RAM is used as heap.
*
* \subsubsection group_system_config_heap_stack_config_arm_cm33 ARM Compiler
* - <b>Editing source code files for non-secure image</b>\n
* The stack sizes are defined in the linker script file: 'cyw20829_ns_flash_cbus.sct'.
* Change the stack by modifying the following lines:\n
* \code #define STACK_SIZE  0x00001000 \endcode
* Remaining free RAM is used as heap.
*
* \subsubsection group_system_config_heap_stack_config_iar_cm33 IAR
* - <b>Editing source code files for non-secure image</b>\n
* The stack and heap sizes are defined in the linker script file: 'cyw20829_ns_flash_cbus.icf'.
* Change the stack size by modifying the following line:\n
* \code define symbol STACK_SIZE = 0x00001000; \endcode
* Remaining free RAM is used as heap.
*
* \subsection group_system_config_default_handlers_cm33 Default Interrupt Handlers Definition
* The default interrupt handler functions are dummy handler in the startup file.\n
* Below is the default handler for the non-secure interrupts:\n
* \code interrupt_type void InterruptHandler(void) {
*    while(1);
* } \endcode
*
* \subsection group_system_config_device_vector_table_cm33 Vectors Table Copy from ROM/Flash to RAM
* This process uses memory sections defined in the linker script. The startup code copies the
* default vector table contents to the non-secure SRAM region specified by the linker script.
* APIs are provided in the sysint driver to hook user implemented handler replacing the default
* handler for the corresponding interrupt.
*
* Following tables provide the address of the default and non-secure SRAM interrupt vector
* table for different supported compilers.
* \subsubsection group_system_config_device_vector_table_gcc_cm33 ARM GCC
* The linker script file is 'cyw20829_ns_flash_cbus.ld'.
* For non-secure world, it uses the following variable.\n
*       Copy interrupt vectors from ROM/flash to RAM: \n
*       From: \code __ns_vector_table \endcode
*       To:   \code __ns_vector_table_rw \endcode
* The vector table address (and the vector table itself) are defined in the
* ns_start_<device>.c startup file corresponding to non-secure world.
* The code in these files copies the vector table from ROM/Flash to RAM.
*
* \subsubsection group_system_config_device_vector_table_mdk_cm33 ARM Compiler
* The linker script file is 'cyw20829_ns_flash_cbus.sct'.
* For non-secure world, it uses the following variable.\n
*       Copy interrupt vectors from ROM/flash to RAM: \n
*       From: \code __ns_vector_table \endcode
*       To:   \code __ns_vector_table_rw \endcode
* The vector table address (and the vector table itself) are defined in the
* ns_start_<device>.c startup file corresponding to non-secure world.
* The code in these files copies the vector table from ROM/Flash to RAM.
*
* \subsubsection group_system_config_device_vector_table_iar_cm33 IAR
* The linker script file is 'cyw20829_ns_flash_cbus.icf'.
* For non-secure world, it uses the following variable.\n
*       Copy interrupt vectors from ROM/flash to RAM: \n
*       From: \code __ns_vector_table \endcode
*       To:   \code __ns_vector_table_rw \endcode
* The vector table address (and the vector table itself) are defined in the
* ns_start_<device>.c startup file corresponding to non-secure worlds.
* The code in these files copies the vector table from ROM/Flash to RAM.
*
* \section group_system_config_changelog_cm33 Changelog
*   <table class="doxtable">
*   <tr>
*       <th>Version</th>
*       <th>Changes</th>
*       <th>Reason for Change</th>
*   </tr>
*   <tr>
*       <td>1.0</td>
*       <td>Initial version</td>
*       <td></td>
*   </tr>
* </table>
*
*
* \defgroup group_system_config_macro_cm33 Macro
* \{
*   \defgroup group_system_config_system_macro_cm33            System
* \}
* \defgroup group_system_config_functions_cm33 Functions
* \{
*   \defgroup group_system_config_system_functions_cm33        System
* \}
* \defgroup group_system_config_globals_cm33 Global Variables
*
* \}
*/

/**
* \addtogroup group_system_config_system_functions_cm33
* \{
*   \details
*   The following system functions implement CMSIS Core functions.
* \}
*/

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
* Include files
*******************************************************************************/
#include <stdint.h>

#define CY_SYSTEM_CPU_CM33          1UL

/*******************************************************************************
* Global preprocessor symbols/macros ('define')
*******************************************************************************/

/*******************************************************************************
*
*                      START OF USER SETTINGS HERE
*                      ===========================
*
*                 All lines with '<<<' can be set by user.
*
*******************************************************************************/

/**
* \addtogroup group_system_config_system_macro_cm33
* \{
*/
#if (CY_SYSTEM_CPU_CM33 == 1UL) || defined(CY_DOXYGEN)
    /** The Cortex-M33 startup driver identifier */
    #define CY_STARTUP_M33_ID               ((uint32_t)((uint32_t)((0x0EU) & 0x3FFFU) << 18U))
#endif /* (CY_SYSTEM_CPU_CM33 == 1UL) */
/** \} group_system_config_system_macro_cm33 */


/**
* \addtogroup group_system_config_system_functions_cm33
* \{
*/
void SystemInit_CAT1B_CM33(void);

extern void SystemCoreClockUpdate(void);
/** \} group_system_config_system_functions */

/** \cond */
extern void     Cy_SystemInit(void);
extern void     bootstrapInit(void);

extern uint32_t cy_delayFreqHz;
extern uint32_t cy_delayFreqKhz;
extern uint8_t  cy_delayFreqMhz;
extern uint32_t cy_delay32kMs;
/** \endcond */



/** \addtogroup group_system_config_globals_cm33
* \{
*/

extern uint32_t SystemCoreClock;
extern uint32_t cy_Hfclk0FreqHz;
extern uint32_t cy_PeriClkFreqHz;

/** \} group_system_config_globals_cm33 */

#ifdef __cplusplus
}
#endif

#endif /* _SYSTEM_CYW20829_H_ */


/* [] END OF FILE */



