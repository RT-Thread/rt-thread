/***************************************************************************//**
* \file system_cat1c.h
* \version 1.0
*
* \brief Device system header file.
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


#ifndef _SYSTEM_FACELIFT_H_
#define _SYSTEM_FACELIFT_H_

/**
* \addtogroup group_system_config_cm7
* \{
* Provides device startup, system configuration, and linker script files.
* The system startup provides the followings features:
* - \ref group_system_config_device_memory_definition_cm7
* - \ref group_system_config_device_initialization_cm7
* - \ref group_system_config_heap_stack_config_cm7
* - \ref group_system_config_default_handlers_cm7
* - \ref group_system_config_device_vector_table_cm7
* - \ref group_system_config_cm7_functions
*
* \section group_system_config_configuration_cm7 Configuration Considerations
*
* \subsection group_system_config_device_memory_definition_cm7 Device Memory Definition
* Allocation of different types of memory such as the flash, RAM etc., for the CPU is defined by the linker scripts.
*
* \note - The linker files provided with the PDL are generic and handle all common
* use cases. Your project may not use every section defined in the linker files.
* In that case you may see warnings during the build process. To eliminate build
* warnings in your project, you can simply comment out or remove the relevant
* code in the linker file.
*
* \note - There is a common linker script for both CM7_0 and CM7_1 core.
* By default it links for CM7_0 core. But if the application is built for CM7_1, then a linker option _CORE_cm7_1 is provided in build system.
* For example, below piece of code is implemented in the build system.
* \code
* ifeq ($(TOOLCHAIN),IAR)
* LDFLAGS += --config_def _CORE_cm7_1_=1
* else ifeq ($(TOOLCHAIN),GCC_ARM)
* LDFLAGS += -Wl,'--defsym=_CORE_cm7_1_=1'
* endif
* \endcode
*
* <b>ARM GCC</b>\n
* The flash and RAM sections for the CPU are defined in the linker files:
* 'xx_yy_zz.ld', where 'xx_ yy' is the device group, and 'zz' is the target CPU;
* for example, 'xmc7200d_x8384_cm7.ld', 'xmc7100d_x4160_cm7.ld', 'xmc7200d_x8384_cm0plus.ld' and 'xmc7100d_x4160_cm0plus.ld'.
* \note If the start of the Cortex-M7_0 or Cortex-M7_1 application image is changed, the value
* of the \ref CY_CORTEX_M7_0_APPL_ADDR or \ref CY_CORTEX_M7_1_APPL_ADDR should also be changed. The
* \ref CY_CORTEX_M7_0_APPL_ADDR or \ref CY_CORTEX_M7_1_APPL_ADDR macro should be used as the parameter for the
* Cy_SysEnableCM7() function call.
* By default,
* - the COMPONENT_XMC7x_CM0P_SLEEP prebuilt image is used for the CM0p core of the XMC dual-core MCU device (CM0+, CM7_0).
* - the COMPONENT_XMC7xDUAL_CM0P_SLEEP prebuilt image is used for the CM0p core of the XMC dual CM7-core MCU device (CM0+, CM7_0 and CM7_1).
*
* Change the flash and RAM sizes by editing the macro values in the
* linker files for both CPUs:
* - 'xx_yy_cm0plus.ld', where 'xx_yy' is the device group:
* \code
* cm0_ram (rxw)  : ORIGIN = _base_SRAM_CM0P, LENGTH = _size_SRAM_CM0P
* cm0_flash (rx) : ORIGIN = _base_CODE_FLASH_CM0P,LENGTH = _size_CODE_FLASH_CM0P
* \endcode
* - 'xx_yy_cm7.ld', where 'xx_yy' is the device group:
* \code
* ram (rxw) : ORIGIN = _base_SRAM, LENGTH = _size_SRAM
* flash_cm0p (rx) : ORIGIN = _base_CODE_FLASH_CM0P, LENGTH = _size_CODE_FLASH_CM0P
* flash (rx) : ORIGIN = _base_CODE_FLASH, LENGTH = _size_CODE_FLASH
* \endcode
*
* Change the value of the \ref CY_CORTEX_M7_0_APPL_ADDR or \ref CY_CORTEX_M7_1_APPL_ADDR
* macro to the ROM ORIGIN's value (0x10000000) + FLASH_CM0P_SIZE
* value (0x80000, the size of a flash image of the Cortex-M0+ application should be the
* same value as the flash LENGTH in 'xx_yy_cm0plus.ld') in the 'xx_yy_cm7.ld' file,
* where 'xx_yy' is the device group.
*
* - Do this by editing the the \ref CY_CORTEX_M7_0_APPL_ADDR or \ref CY_CORTEX_M7_1_APPL_ADDR value
* in the 'system_xx.h', where 'xx' is the device family:\n
* \code
* #define CY_CORTEX_M7_0_APPL_ADDR BASE_CODE_FLASH_CM7_0
* #define CY_CORTEX_M7_1_APPL_ADDR BASE_CODE_FLASH_CM7_1
* \endcode
* 'BASE_CODE_FLASH_CM7_0' and ''BASE_CODE_FLASH_CM7_1' macros are defined in the xmc7xxx_partition.h
*
* <b>ARM Compiler</b>\n
* The flash and RAM sections for the CPU are defined in the linker files:
* 'xx_yy_zz.sct', where 'xx_ yy' is the device group, and 'zz' is the target CPU;
* for example 'xmc7200d_x8384_cm7.sct', 'xmc7100d_x4160_cm7.sct', 'xmc7200d_x8384_cm0plus.sct' and 'xmc7100d_x4160_cm0plus.sct'.
*
* \note If the start of the Cortex-M7_0 or Cortex-M7_1 application image is changed, the value
* of the \ref CY_CORTEX_M7_0_APPL_ADDR or \ref CY_CORTEX_M7_1_APPL_ADDR should also be changed. The
* \ref CY_CORTEX_M7_0_APPL_ADDR or \ref CY_CORTEX_M7_1_APPL_ADDR macro should be used as the parameter for the
* Cy_SysEnableCM7() function call.
* By default,
* - the COMPONENT_XMC7x_CM0P_SLEEP prebuilt image is used for the CM0p core of the XMC dual-core MCU device (CM0+, CM7_0).
* - the COMPONENT_XMC7xDUAL_CM0P_SLEEP prebuilt image is used for the CM0p core of the XMC dual CM7-core MCU device (CM0+, CM7_0 and CM7_1).
*
* \note The linker files provided with the PDL are generic and handle all common
* use cases. Your project may not use every section defined in the linker files.
* In that case you may see the warnings during the build process:
* L6314W (no section matches pattern) and/or L6329W
* (pattern only matches removed unused sections). In your project, you can
* suppress the warning by passing the "--diag_suppress=L6314W,L6329W" option to
* the linker. You can also comment out or remove the relevant code in the linker
* file.
*
* Change the flash and RAM sizes by editing the macros value in the
* linker files for both CPUs:
* - 'xx_yy_cm0plus.sct', where 'xx_yy' is the device group:
* \code
* #define SRAM_BASE_ADDRESS               0x28000000
* #define CM0PLUS_SRAM_RESERVE            0x00020000
* #define CODE_FLASH_BASE_ADDRESS         0x10000000
* #define CM0PLUS_CODE_FLASH_RESERVE      0x00080000
* \endcode
* - 'xx_yy_cm7.sct', where 'xx_yy' is the device group:
* \code
* #define SRAM_BASE_ADDRESS               0x28000000 //SRAM START
* #define CM7_0_SRAM_RESERVE              0x00060000 //cm7_0 sram size
* #define BASE_SRAM_CM7_0                 SRAM_BASE_ADDRESS + CM0PLUS_SRAM_RESERVE
* #define SIZE_SRAM_CM7_0                 CM7_0_SRAM_RESERVE
* //In case of dual CM7-core MCU device device
* #define SIZE_SRAM_CM7_1                 SRAM_TOTAL_SIZE - CM0PLUS_SRAM_RESERVE - CM7_0_SRAM_RESERVE
* #define BASE_SRAM_CM7_1                 SRAM_BASE_ADDRESS + CM0PLUS_SRAM_RESERVE + CM7_0_SRAM_RESERVE
*
* #define CODE_FLASH_BASE_ADDRESS         0x10000000 //FLASH START
* #define CM7_0_CODE_FLASH_RESERVE        0x00200000 //cm7_0 flash size
* #define BASE_CODE_FLASH_CM7_0           CODE_FLASH_BASE_ADDRESS + CM0PLUS_CODE_FLASH_RESERVE
* #define SIZE_CODE_FLASH_CM7_0           CM7_0_CODE_FLASH_RESERVE
* //In case of dual CM7-core MCU device device
* #define BASE_CODE_FLASH_CM7_1           CODE_FLASH_BASE_ADDRESS + CM0PLUS_CODE_FLASH_RESERVE + CM7_0_CODE_FLASH_RESERVE
* #define SIZE_CODE_FLASH_CM7_1           CODE_FLASH_TOTAL_SIZE - CM0PLUS_CODE_FLASH_RESERVE - CM7_0_CODE_FLASH_RESERVE
* \endcode
*
* Change the value of the \ref CY_CORTEX_M7_0_APPL_ADDR or \ref CY_CORTEX_M7_1_APPL_ADDR
* macro to the ROM ORIGIN's value (0x10000000) + FLASH_CM0P_SIZE
* value (0x80000, the size of a flash image of the Cortex-M0+ application should be the
* same value as the flash LENGTH in 'xx_yy_cm0plus.sct') in the 'xx_yy_cm7.sct' file,
* where 'xx_yy' is the device group.
*
* - Do this by editing the \ref CY_CORTEX_M7_0_APPL_ADDR or \ref CY_CORTEX_M7_1_APPL_ADDR value
* in the 'system_xx.h', where 'xx' is the device family:\n
* \code
* #define CY_CORTEX_M7_0_APPL_ADDR BASE_CODE_FLASH_CM7_0
* #define CY_CORTEX_M7_1_APPL_ADDR BASE_CODE_FLASH_CM7_1
* \endcode
* 'BASE_CODE_FLASH_CM7_0' and ''BASE_CODE_FLASH_CM7_1' macros are defined in the xmc7xxx_partition.h

* <b>IAR</b>\n
* The flash and RAM sections for the CPU are defined in the linker files:
* 'xx_yy_zz.icf', where 'xx_ yy' is the device group, and 'zz' is the target CPU; for example,
* 'xmc7200d_x8384_cm7.icf','xmc7100d_x4160_cm7.icf','xmc7200d_x8384_cm0plus.icf' and 'xmc7100d_x4160_cm0plus.icf'.
* \note If the start of the Cortex-M7_0 or Cortex-M7_1 application image is changed, the value
* of the \ref CY_CORTEX_M7_0_APPL_ADDR or \ref CY_CORTEX_M7_1_APPL_ADDR should also be changed. The
* \ref CY_CORTEX_M7_0_APPL_ADDR or \ref CY_CORTEX_M7_1_APPL_ADDR macro should be used as the parameter for the
* Cy_SysEnableCM7() function call.
* By default,
* - the COMPONENT_XMC7x_CM0P_SLEEP prebuilt image is used for the CM0p core of the XMC dual-core MCU device (CM0+, CM7_0).
* - the COMPONENT_XMC7xDUAL_CM0P_SLEEP prebuilt image is used for the CM0p core of the XMC dual CM7-core MCU device (CM0+, CM7_0 and CM7_1).
*
* Change the flash and RAM sizes by editing the macros value in the
* linker files for both CPUs:
* - 'xx_yy_cm0plus.icf', where 'xx_yy' is the device group:
* \code
* define symbol sram_base_address                 = 0x28000000;
* define symbol cm0plus_sram_reserve              = 0x00020000; //cm0 sram size
* define symbol code_flash_base_address           = 0x10000000;
* define symbol cm0plus_code_flash_reserve        = 0x00080000; //cm0 flash size
* \endcode
* - 'xx_yy_cm7.icf', where 'xx_yy' is the device group:
* \code
* define symbol sram_base_address                 = 0x28000000;
* define symbol cm7_0_sram_reserve                = 0x00060000;
* define symbol _base_SRAM_CM7_0                  = sram_base_address + cm0plus_sram_reserve;
* define symbol _size_SRAM_CM7_0                  = cm7_0_sram_reserve;
* //In case of dual CM7-core MCU device device
* define symbol _base_SRAM_CM7_1                  = sram_base_address + cm0plus_sram_reserve + cm7_0_sram_reserve;
* define symbol _size_SRAM_CM7_1                  = sram_total_size - cm0plus_sram_reserve - cm7_0_sram_reserve;
*
* define symbol code_flash_base_address           = 0x10000000;
* define symbol cm7_0_code_flash_reserve          = 0x00200000;
* define symbol _base_CODE_FLASH_CM7_0            = code_flash_base_address + cm0plus_code_flash_reserve;
* define symbol _size_CODE_FLASH_CM7_0            = cm7_0_code_flash_reserve;
* //In case of dual CM7-core MCU device device
* define symbol _base_CODE_FLASH_CM7_1            = code_flash_base_address + cm0plus_code_flash_reserve + cm7_0_code_flash_reserve;
* define symbol _size_CODE_FLASH_CM7_1            = code_flash_total_size - cm0plus_code_flash_reserve - cm7_0_code_flash_reserve;
* \endcode
*
* Change the value of the \ref CY_CORTEX_M7_0_APPL_ADDR or \ref CY_CORTEX_M7_1_APPL_ADDR
* macro to the ROM ORIGIN's value (0x10000000) + FLASH_CM0P_SIZE
* value (0x80000, the size of a flash image of the Cortex-M0+ application should be the
* same value as the flash LENGTH in 'xx_yy_cm0plus.icf') in the 'xx_yy_cm7.icf' file,
* where 'xx_yy' is the device group.
*
* - Do this by editing the \ref CY_CORTEX_M7_0_APPL_ADDR or \ref CY_CORTEX_M7_1_APPL_ADDR value
* in the 'system_xx.h', where 'xx' is the device family:\n
* \code
* #define CY_CORTEX_M7_0_APPL_ADDR BASE_CODE_FLASH_CM7_0
* #define CY_CORTEX_M7_1_APPL_ADDR BASE_CODE_FLASH_CM7_1
* \endcode
* 'BASE_CODE_FLASH_CM7_0' and ''BASE_CODE_FLASH_CM7_1' macros are defined in the xmc7xxx_partition.h
*
* \subsection group_system_config_device_initialization_cm7 Device Initialization
* After a power-on-reset (POR), the CM0+ starts boot-ROM directly from ROM and boot-ROM starts CM0+ startup.
* The CM0+ startup starts CM0+ user application. The CM0+ user application enables CM7 cores and starts CM7 startup.
* The startup code is the piece of code which is executed after every system reset.
* It initializes the system components like, memory, FPU, interrupts, clock, etc. and calls application's main() function.
* The startup code is always build as part of user application. There are two different startup codes for CM0+ and CM7 core.
*
* The CM0+ startup code implements the following functions to run the CM0+ application:
*
* 1. In the Reset Handler, it disables global interrupts
* 3. Disables the SRAM ECC checking: CM0+ bus width is 32-bit, but SRAM is built with 64-bit based ECC on Facelift parts with CM7 core,
*     sets CPUSS->RAMx_CTL0.ECC_CHECK_DIS bits to avoid causing unintentional ECC faults during startup while SRAM ECC has not been initialized yet.
* 4. Calls SystemInit() function
*   - Initializes and enables the SRAM memory for ECC
*   - Copies the vector table from ROM to RAM and updates the VTOR (Vector Table Offset Register)
*   - Sets the CM0+ IRQ0 and IRQ1 handlers from SROM vector table, sets the CM0+ IRQ0 and IRQ1priority,
*      then enables these interrupts: the SROM APIs are executed by CM0+ core in interrupt context using IRQ0 and IRQ1.
*      So, proper interrupt handler addresses and priorities need to be configured for IRQ0 and IRQ1
*   - Unlocks and disable WDT (Watchdog timer)
*   - Calls the SystemCoreClockUpdate()
* 5. Executes main() application
*
* The CM7 startup code implement the following functions to run the CM7 user application:
*
* 1. In the Reset handler, it disables global interrupts
* 2. Allows write access to Vector Table Offset Register and ITCM/DTCM configuration register
* 3. Enables CM7 core ITCM and DTCM
* 4. Enables the FPU if it is used
* 5. Copies the vector table from ROM to RAM and updates the VTOR (Vector Table Offset Register)
* 6. Enables the CM7 core instruction and data cache
* 7. Calls SystemInit() function
*    - Unlocks and disable WDT (Watchdog timer)
*    - Calls the SystemCoreClockUpdate()
* 6. Executes CM7 main() application
*
* \subsection group_system_config_heap_stack_config_cm7 Heap and Stack Configuration
* By default, the stack size is set to 0x00001000 and the Heap size is allocated
* dynamically to the whole available free memory up to stack memory.
* The Stack grows from higher to lower address. The Stack top or start is assigned to end of SRAM address.
* The Heap grows opposite of Stack. It grows from lower to higher address.
* The Heap top starts from end of used data section till Stack end.
*
* \subsubsection group_system_config_heap_stack_config_gcc_cm7 ARM GCC
* <b>Editing source code files</b>\n
* The stack size is defined in the linker script files: 'xx_yy_zz.ld',
* 'xx_yy_zz.ld', where 'xx_ yy' is the device group, and 'zz' is the target CPU; for example,
* 'xmc7200d_x8384_cm7.ld', 'xmc7100d_x4160_cm7.ld', 'xmc7200d_x8384_cm0plus.ld' and 'xmc7100d_x4160_cm0plus.ld'.
* Change the stack size by modifying the following line:\n
* \code STACK_SIZE = 0x1000; \endcode
*
* \note Correct operation of malloc and related functions depends on the working
* implementation of the 'sbrk' function. Newlib-nano (default C runtime library
* used by the GNU Arm Embedded toolchain) provides weak 'sbrk' implementation that
* doesn't check for heap and stack collisions during excessive memory allocations.
* To ensure the heap always remains within the range defined by __HeapBase and
* __HeapLimit linker symbols, provide a strong override for the 'sbrk' function:
* \snippet startup/snippet/main.c snippet_sbrk
* For FreeRTOS-enabled multi-threaded applications, it is sufficient to include
* clib-support library that provides newlib-compatible implementations of
* 'sbrk', '__malloc_lock' and '__malloc_unlock':
* <br>
* https://github.com/Infineon/clib-support.
*
* \subsubsection group_system_config_heap_stack_config_mdk_cm7 ARM Compiler
* <b>Editing source code files</b>\n
* The stack size is defined in the linker script files: 'xx_yy_zz.sct',
* 'xx_yy_zz.sct', where 'xx_ yy' is the device group, and 'zz' is the target CPU; for example,
* 'xmc7200d_x8384_cm7.sct', 'xmc7100d_x4160_cm7.sct', 'xmc7200d_x8384_cm0plus.sct' and 'xmc7100d_x4160_cm0plus.sct'.
* Change the stack size by modifying the following line:\n
* \code #define STACK_SIZE 0x1000 \endcode
*
* \subsubsection group_system_config_heap_stack_config_iar_cm7 IAR
* <b>Editing source code files</b>\n
* The heap and stack sizes are defined in the linker script files: 'xx_yy_zz.icf',
* where 'xx_ yy' is the device group, and 'zz' is the target CPU; for example,
* 'xmc7200d_x8384_cm7.icf','xmc7100d_x4160_cm7.icf','xmc7200d_x8384_cm0plus.icf' and 'xmc7100d_x4160_cm0plus.icf'.
* Change the heap and stack sizes by modifying the following lines:\n
* \code define symbol cm7_stack_reserve = 0x00001000; \endcode
*
* \subsection group_system_config_default_handlers_cm7 Default Interrupt Handlers Definition
* The default interrupt handler functions are defined as weak functions to a dummy
* handler in the startup file. The naming convention for the interrupt handler names
* is \<interrupt_name\>_IRQHandler. A default interrupt handler can be overwritten in
* user code by defining the handler function using the same name. For example:
* \code
* void scb_0_interrupt_IRQHandler(void)
*{
*    ...
*}
* \endcode
*
* \subsection group_system_config_device_vector_table_cm7 Vectors Table Copy from Flash to RAM
* This process uses memory sections defined in the linker script. The startup
* code actually defines the contents of the vector table and performs the copy.
*
* \subsubsection group_system_config_device_vector_table_gcc_cm7 ARM GCC
* The linker script file is 'xx_yy_zz.ld', where 'xx_ yy' is the device group, and 'zz' is the target CPU;
* for example, 'xmc7200d_x8384_cm7.ld', 'xmc7100d_x4160_cm7.ld', 'xmc7200d_x8384_cm0plus.ld' and 'xmc7100d_x4160_cm0plus.ld'.
* It defines sections and locations in memory.\n
*       Copy interrupt vectors from flash to RAM: \n
*       From: \code LONG (__Vectors) \endcode
*       To:   \code LONG (__ram_vectors_start__) \endcode
*       Size: \code LONG (__Vectors_End - __Vectors) \endcode
* The vector table address (and the vector table itself) are defined in the
*  startup files (e.g. startup_cm0plus.S and startup_cm7.c).
* The code in these files copies the vector table from Flash to RAM.
*
* \subsubsection group_system_config_device_vector_table_mdk_cm7 ARM Compiler
* The linker script file is 'xx_yy_zz.sct', where 'xx_ yy' is the device group, and 'zz' is the target CPU;
* for example 'xmc7200d_x8384_cm7.sct', 'xmc7100d_x4160_cm7.sct', 'xmc7200d_x8384_cm0plus.sct' and
* 'xmc7100d_x4160_cm0plus.sct'. The linker script specifies that the vector table
* (RESET_RAM) shall be first in the RAM section.\n
* RESET_RAM represents the vector table. It is defined in the startup
* files  (e.g. startup_cm0plus.S and startup_cm7.c).
* The code in these files copies the vector table from Flash to RAM.
*
* \subsubsection group_system_config_device_vector_table_iar_cm7 IAR
* The linker script file is 'xx_yy_zz.icf', where 'xx_ yy' is the device group, and 'zz' is the target CPU;
* for example, 'xmc7200d_x8384_cm7.icf','xmc7100d_x4160_cm7.icf','xmc7200d_x8384_cm0plus.icf' and '
* 'xmc7100d_x4160_cm0plus.icf'.\n
* The vector table address (and the vector table itself) are defined in the
* startup files (e.g. startup_cm0plus.S and startup_cm7.c).
* The code in these files copies the vector table from Flash to RAM.
*
* \section group_system_config_changelog_cm7 Changelog
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
* \defgroup group_system_config_macro_cm7 Macros
* \{
*   \defgroup group_system_config_system_macro_cm7 System Macros
* \}
* \defgroup group_system_config_functions_cm7 Functions
* \{
*   \defgroup group_system_config_cm7_functions Cortex-M7 Control
* \}
* \}
*/
#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
* Include files
*******************************************************************************/
#include <stdint.h>
#if defined (CY_DEVICE_TVIIC2D6M)
#include "tviic_partition.h"
#else
#include "xmc7xxx_partition.h"
#endif

/*******************************************************************************
* Global preprocessor symbols/macros ('define')
*******************************************************************************/
#if ((defined(__GNUC__)        &&  (__ARM_ARCH == 6) && (__ARM_ARCH_6M__ == 1)) || \
     (defined (__ICCARM__)     &&  (__CORE__ == __ARM6M__))  || \
     (defined(__ARMCC_VERSION) &&  (__TARGET_ARCH_THUMB == 3)))
    #define CY_SYSTEM_CPU_CM0P          1UL
#else
    #define CY_SYSTEM_CPU_CM0P          0UL
#endif


/*******************************************************************************
*
*                      START OF USER SETTINGS HERE
*                      ===========================
*
*                 All lines with '<<<' can be set by user.
*
*******************************************************************************/

/**
* \addtogroup group_system_config_system_macro_cm7
* \{
*/

/*******************************************************************************
*
*                         END OF USER SETTINGS HERE
*                         =========================
*
*******************************************************************************/

/**  Start address of the Cortex-M7_0 application */
#ifndef CY_CORTEX_M7_0_APPL_ADDR
    #define CY_CORTEX_M7_0_APPL_ADDR        BASE_CODE_FLASH_CM7_0
#endif

/**  Start address of the Cortex-M7_1 application */
#ifndef CY_CORTEX_M7_1_APPL_ADDR
    #define CY_CORTEX_M7_1_APPL_ADDR        BASE_CODE_FLASH_CM7_1
#endif

/** The Cortex-M7 core is enabled: power on, clock on, no isolate, no reset and no retain. */
#define CY_SYS_CM7_STATUS_ENABLED   (3U)
/** The Cortex-M7 core is disabled: power off, clock off, isolate, reset and no retain. */
#define CY_SYS_CM7_STATUS_DISABLED  (0U)
/** The Cortex-M7 core is retained. power off, clock off, isolate, no reset and retain. */
#define CY_SYS_CM7_STATUS_RETAINED  (2U)
/** The Cortex-M7 core is in the Reset mode: clock off, no isolated, no retain and reset. */
#define CY_SYS_CM7_STATUS_RESET     (1U)
/** \} group_system_config_system_macro_cm7 */

/** \cond */
/** Cortex-M7 core 0 */
#define CORE_CM7_0                  (0U)
/** Cortex-M7 core 1 */
#define CORE_CM7_1                  (1U)
/** Error Selection */
#define CORE_MAX                    (2U)

/** Define start of the function placed to the ITCM area by the linker */
#ifndef CY_SECTION_ITCM_BEGIN
#define CY_SECTION_ITCM_BEGIN CY_SECTION(".cy_itcm")
#endif

/** Define end of the function placed to the ITCM area by the linker */
#ifndef CY_SECTION_ITCM_END
#define CY_SECTION_ITCM_END
#endif

extern uint32_t cy_delayFreqHz;
extern uint32_t cy_delayFreqKhz;
extern uint32_t  cy_delayFreqMhz;

extern uint32_t SystemCoreClock;
extern uint32_t cy_Hfclk0FreqHz;
extern uint32_t cy_PeriClkFreqHz;
extern uint32_t cy_AhbFreqHz;

extern void SystemInit(void);
extern void SystemIrqInit(void);
extern void SystemCoreClockUpdate(void);

/** \endcond */

/**
* \addtogroup group_system_config_cm7_functions
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysGetCM7Status
****************************************************************************//**
*
* Gets the Cortex-M7 core power mode.
*
* \param core Core type (CM7_0 or CM7_1).
*
* \return \ref group_system_config_system_macro_cm7 \n
* If 0: CY_SYS_CM7_STATUS_DISABLED \n
*      1: CY_SYS_CM7_STATUS_RESET \n
*      2: CY_SYS_CM7_STATUS_RETAINED \n
*      3: CY_SYS_CM7_STATUS_ENABLED \n
*
******************************************************************************/
extern uint32_t Cy_SysGetCM7Status(uint8_t core);
/*******************************************************************************
* Function Name: Cy_SysEnableCM7
****************************************************************************//**
*
* Enables the Cortex-M7 core. The CPU is enabled once if it was in the disabled
* or retained mode.
*
* \param core Core type (CM7_0 or CM7_1).
*
* \param vectorTableOffset The offset of the vector table base address from
* memory address 0x00000000. The offset should be multiple to 1024 bytes.
*
*******************************************************************************/
extern void Cy_SysEnableCM7(uint8_t core, uint32_t vectorTableOffset);
/*******************************************************************************
* Function Name: Cy_SysDisableCM7
****************************************************************************//**
*
* Disables the Cortex-M7 core.
*
* \param core Core type (CM7_0 or CM7_1).
*
* \warning Do not call the function while the Cortex-M7 is executing because
* such a call may corrupt/abort a pending bus-transaction by the CPU and cause
* unexpected behavior in the system including a deadlock. Call the function
* while the Cortex-M7 core is in the Sleep or Deep Sleep low-power mode. Use
* the \ref group_syspm Power Management (syspm) API to put the CPU into the
* low-power modes. Use the \ref Cy_SysPm_ReadStatus() to get a status of the CPU.
*
*******************************************************************************/
extern void Cy_SysDisableCM7(uint8_t core);
/*******************************************************************************
* Function Name: Cy_SysRetainCM7
****************************************************************************//**
*
* Retains the Cortex-M7 core.
*
* \param core Core type (CM7_0 or CM7_1).
*
* \warning Do not call the function while the Cortex-M7 is executing because
* such a call may corrupt/abort a pending bus-transaction by the CPU and cause
* unexpected behavior in the system including a deadlock. Call the function
* while the Cortex-M7 core is in the Sleep or Deep Sleep low-power mode. Use
* the \ref group_syspm Power Management (syspm) API to put the CPU into the
* low-power modes. Use the \ref Cy_SysPm_ReadStatus() to get a status of the CPU.
*
*******************************************************************************/
extern void Cy_SysRetainCM7(uint8_t core);
/*******************************************************************************
* Function Name: Cy_SysResetCM7
****************************************************************************//**
*
* Resets the Cortex-M7 core.
*
* \param core Core type (CM7_0 or CM7_1).
*
* \warning Do not call the function while the Cortex-M7 is executing because
* such a call may corrupt/abort a pending bus-transaction by the CPU and cause
* unexpected behavior in the system including a deadlock. Call the function
* while the Cortex-M7 core is in the Sleep or Deep Sleep low-power mode. Use
* the \ref group_syspm Power Management (syspm) API to put the CPU into the
* low-power modes. Use the \ref Cy_SysPm_ReadStatus() to get a status of the CPU.
*
*******************************************************************************/
extern void Cy_SysResetCM7(uint8_t core);
/** \} group_system_config_cm7_functions */


/** \cond */

extern void     Default_Handler (void);

extern void     Cy_SystemInit(void);
extern void     Cy_SystemInitFpuEnable(void);
extern void     CyMain(void);

#define Cy_SaveIRQ      Cy_SysLib_EnterCriticalSection
#define Cy_RestoreIRQ   Cy_SysLib_ExitCriticalSection
/** \endcond */






#ifdef __cplusplus
}
#endif

#endif /* _SYSTEM_FACELIFT_H_ */


/* [] END OF FILE */
