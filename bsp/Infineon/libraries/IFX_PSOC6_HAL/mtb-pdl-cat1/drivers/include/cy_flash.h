/***************************************************************************//**
* \file cy_flash.h
* \version 3.70
*
* Provides the API declarations of the Flash driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2021 Cypress Semiconductor Corporation
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

#if !defined (CY_FLASH_H)
#define CY_FLASH_H

/**
* \addtogroup group_flash
* \{
* Internal flash memory programming
*
* The functions and other declarations used in this driver are in cy_flash.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* Flash memory in PSoC devices provides non-volatile storage for user firmware,
* user configuration data, and bulk data storage.
*
* Flash operations are implemented as system calls. System calls are executed
* out of SROM in the privileged mode of operation. Users have no access to read
* or modify the SROM code. The driver API requests the system call by acquiring
* the Inter-processor communication (IPC) and writing the SROM function opcode
* and parameters to its input registers. As a result, an NMI interrupt is invoked
* and the requested SROM function is executed. The operation status is returned
* to the driver context and a release interrupt is triggered.
*
* Writing to flash can take up to 20 milliseconds. During this time,
* the device should not be reset (including XRES pin, software  reset, and
* watchdog) or unexpected changes may be made to portions of the flash.
* Also, the low-voltage detect circuits should be configured to generate an
* interrupt instead of a reset.
*
* A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring (neighboring restriction is applicable just for the
* CY8C6xx6, CY8C6xx7 devices) flash sector where the flash Write, Erase, or
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation, carefully split the
* Read and Write operation on flash sectors which are not neighboring,
* considering both cores in the multi-processor device. If the flash is divided
* into four equal sectors, you may edit the linker script to place the code
* into neighboring sectors. For example, use sectors number 0 and 1 for code
* and sectors 2 and 3 for data storage.
*
* \section group_flash_configuration Configuration Considerations
*
* \subsection group_flash_config_intro Introduction:
* The CAT1A devices user-programmable Flash consists of:
* - Application flash memory (from 2 to 8 sectors) - 128KB/256KB each.
* - EE emulation flash memory - 32KB.
*
* The CAT1C devices user-programmable Flash consists of:
* - Work flash region has 48 large sectors of 2 KB and 256 small sectors of 128 B.
*
* Write operation may be done as Blocking or Partially Blocking,
* defined as follows:
*
* \subsection group_flash_config_blocking Blocking:
* In this case, the entire Flash block is not available for the duration of the
* Write (&sim;16ms). Therefore, no Flash accesses (from any Bus Master) can
* occur during that time. CPU execution can be performed from SRAM. All
* pre-fetching must be disabled. Code execution from Flash is blocked for the
* Flash Write duration for both cores.
*
* \subsection group_flash_config_block_const Constraints for Blocking Flash operations:
* -# During write to flash, the device should not be reset (including XRES pin,
* software reset, and watchdog), or unexpected changes may be made to portions
* of the flash.
* -# The low-voltage detect circuits should be configured to generate an
*    interrupt instead of a reset.
* -# Flash write operation in CAT1A devices is allowed only in one of the following CM4 states:
*     -# CM4 is Active and initialized:<br>
*        call \ref Cy_SysEnableCM4 "Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR)".
*        <b>Note:</b> If desired user may put CM4 core in Deep Sleep any time
*        after calling Cy_SysEnableCM4().
*     -# CM4 is Off and disabled:<br>
*        call Cy_SysDisableCM4(). <b>Note:</b> In this state Debug mode is not
*        supported.
*
* -# Flash Write cannot be performed in Ultra Low Power (core voltage 0.9V) mode.
* -# Interrupts must be enabled on both active cores. Do not enter a critical
*    section during flash operation.
* -# For the CY8C6xx6, CY8C6xx7 devices user must guarantee that system pipe
*    interrupts (IPC interrupts 3 and 4) have the highest priority, or
*    at least that pipe interrupts are not interrupted or in a pending state
*    for more than 700 &micro;s.
* -# For CAT1A devices user must guarantee that during flash write operation no flash read
*    operations are performed by bus masters other than CM0+ and CM4 (DMA and
*    Crypto).
* -# For the CY8C6xx6, CY8C6xx7 devices if you do not use the default startup, perform the following steps
*    before any flash write/erase operations:
* \snippet flash/snippet/main.c Flash Initialization
*
* \subsection group_flash_config_rww Partially Blocking:
* This method has a much shorter time window during which Flash accesses are not
* allowed. Application code execution from Flash is blocked for only a part of
* Flash Write duration, for both cores. Blocking duration depends upon the API
* sequence used.
*
* For CAT1A Devices API sequence Cy_Flash_StartEraseRow() + Cy_Flash_StartProgram() there are
* four block-out regions during which Read is blocked. See <b>Figure 1</b>.
*
* For CAT1C devices Flash memory controller has the dual bank mode feature. When using dual bank mode,
* flash memory region is split into two half banks. One is called Logical Bank 0 and the other is called Logical Bank 1
* User will be able to read from a different logical bank while writing to one logical bank.
*
* For CAT1C devices Erase ROW is not supported. User has to erase the entire sector before writing to the sector.
*
* CM7 cores in CAT1C devices support Data Cache. Data Cache line is 32 bytes.
* User needs to make sure that the pointer passed to the following functions points to 32 byte aligned data.
* Cy_Flash_StartWrite, Cy_Flash_ProgramRow, Cy_Flash_Program and Cy_Flash_Program_WorkFlash.
* User can use CY_ALIGN(32) macro for 32 byte alignment.
*
* <center>
* <table class="doxtable">
* <caption>Table 1 - Block-out periods (timing values are valid just for the
* CY8C6xx6, CY8C6xx7 devices) </caption>
*   <tr>
*     <th>Block-out</th>
*     <th>Phase</th>
*     <th>Duration</th>
*   </tr>
*   <tr>
*     <td>A</td>
*     <td>The beginning of the Erase operation</td>
*     <td>2ms + 9500 SlowClk cycles</td>
*   </tr>
*   <tr>
*     <td>B</td>
*     <td>The end of the Erase operation</td>
*     <td>0.13ms + 1000 SlowClk cycles</td>
*   </tr>
*   <tr>
*     <td>C</td>
*     <td>The beginning of the Program operation</td>
*     <td>0.8ms + 6000 SlowClk cycles</td>
*   </tr>
*   <tr>
*     <td>D</td>
*     <td>The end of the Program operation</td>
*     <td>0.13ms + 1000 SlowClk cycles</td>
*   </tr>
* </table>
* </center>
*
* This allows both cores to execute for about 80% of Flash Write
* operation - see <b>Figure 1</b>.
* This capability is important for communication protocols that rely on fast
* response.
*
* \image html flash-rww-diagram.png "Figure 1 - Blocking Intervals in Flash Write operation"
*
* For the Cy_Flash_StartWrite() function, the block-out period is different for
* the two cores. The core that initiates Cy_Flash_StartWrite() is blocked for
* two periods:
* - From start of Erase operation (start of A on Figure 1) till the start of
*   Program operation (end of C on Figure 1).
* - During D period on <b>Figure 1</b>.
*
* The core that performs read/execute is blocked identically to the previous
* scenario - see <b>Figure 1</b>.
*
* This allows the core that initiates Cy_Flash_StartWrite() to execute for about
* 20% of Flash Write operation. The other core executes for about 80% of Flash
* Write operation.
*
* Some constraints must be planned for in the Partially Blocking mode which are
* described in detail below.
*
* \subsection group_flash_config_rww_const Constraints for Partially Blocking Flash operations:
* -# During write to flash, the device should not be reset (including XRES pin,
*    software reset, and watchdog) or unexpected changes may be made to portions
*    of the flash.
* -# The low-voltage detect circuits should be configured to generate an
*    interrupt instead of a reset.
* -# During write to flash, application code should not change the clock
*    settings. Use Cy_Flash_IsOperationComplete() to ensure flash write
*    operation is finished.
* -# During write to flash, application code should not start the clock
*    measurements (should not call Cy_SysClk_StartClkMeasurementCounters()).
* -# For CAT1A devices Flash write operation is allowed only in one of the following CM4 states:
*     -# CM4 is Active and initialized:<br>
*        call \ref Cy_SysEnableCM4 "Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR)".
*        <b>Note:</b> If desired user may put CM4 core in Deep Sleep any time
*        after calling Cy_SysEnableCM4().
*     -# CM4 is Off and disabled:<br>
*        call Cy_SysDisableCM4(). <b>Note:</b> In this state Debug mode is not
*        supported.
*     .
* -# For CAT1C devices flash write operation is only allowed after the sector in erased.
* -# For CAT1A devices use the following rules for split by sectors. (In this context, read means
*    read of any bus master: CM0+, CM4, DMA, Crypto, etc.)
*     -# Do not write to and read/execute from the same flash sector at the same
*        time. This is true for all sectors.
*     -# Writing rules in application flash (this restriction is applicable just
* for CY8C6xx6, CY8C6xx7 devices):
*         -# Any bus master can read/execute from UFLASH S0 and/or S1, during
*            flash write to UFLASH S2 or S3.
*         -# Any bus master can read/execute from UFLASH S2 and/or S3, during
*            flash write to UFLASH S0 or S1.
*
*         <b>Suggestion:</b> in case of bootloading, it is recommended to place
*         code for CM4 in either S0 or S1. CM0+ code resides in S0. Write data
*         to S2 and S3 sections.
*     .
* -# Flash Write cannot be performed in Ultra Low Power mode (core voltage 0.9V).
* -# Interrupts must be enabled on both active cores. Do not enter a critical
*    section during flash operation.
* -# For the CY8C6xx6, CY8C6xx7 devices user must guarantee that system pipe
*    interrupts (IPC interrupts 3 and 4) have the highest priority, or at
*    least that pipe interrupts are not interrupted or in a pending state
*    for more than 700 &micro;s.
* -# For the CY8C6xx6, CY8C6xx7 devices if you do not use the default startup, perform the following steps
*    before any flash write/erase operations:
* \snippet flash/snippet/main.c Flash Initialization
*
* \subsection group_flash_config_emeeprom EEPROM section use:
* If you plan to use "cy_em_eeprom" section for different purposes for both of
* device cores or use <b>Em_EEPROM Middleware</b> together with flash driver
* write operations you must modify the linker scripts.<br>
* For more information, refer to the <b>Middleware/Cypress Em_EEPROM Middleware
* Library</b> section of the PDL documentation.
*
* \section group_flash_more_information More Information
*
* See the technical reference manual (TRM) for more information about the Flash
* architecture.
*
* \section group_flash_changelog Changelog
*
* <table class="doxtable">
*   <tr><th>Version</th><th style="width: 52%;">Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>3.70</td>
*     <td>Fixed MISRA 2012 violations and Documentation Update.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>3.60</td>
*     <td>Added API's to support new product family. Enhancement for support of eCT flash.</td>
*     <td>eCT flash's contains Code flash and Work flash. New API's to program/erase both work flash and code flash are added.</td>
*   </tr>
*   <tr>
*     <td>3.50.1</td>
*     <td>Updated documentation to limit devices with the restrictions.</td>
*     <td>User experience enhancement.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">3.50</td>
*     <td>Updated attribute usage for the linker section placement.</td>
*     <td>Enhancement based on usability feedback.</td>
*   </tr>
*   <tr>
*     <td>Fixed/documented MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td rowspan="1">3.40</td>
*     <td>Updated Cy_Flash_OperationStatus() to access protected registers.</td>
*     <td>Added PSoC 64 device support.</td>
*   </tr>
*   <tr>
*     <td rowspan="1">3.30.4</td>
*     <td>Improved documentation.</td>
*     <td>User experience enhancement.</td>
*   </tr>
*   <tr>
*     <td rowspan="1">3.30.3</td>
*     <td>Updated documentation to limit devices with the restrictions. Improved calculation of the CY_FLASH_DELAY_CORRECTIVE macro.</td>
*     <td>User experience enhancement.</td>
*   </tr>
*   <tr>
*     <td rowspan="1">3.30.2</td>
*     <td>Updated documentation to limit devices with the neighboring restriction.</td>
*     <td>User experience enhancement.</td>
*   </tr>
*   <tr>
*     <td rowspan="1">3.30.1</td>
*     <td>Used the CY_RAMFUNC_BEGIN and CY_RAMFUNC_END macros that allocate the function in RAM instead of using the CY_SECTION(".cy_ramfunc") macros.</td>
*     <td>Removed the code duplication.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">3.30</td>
*     <td>Moved ipcWaitMessageStc structure to the RAM section called ".cy_sharedmem".</td>
*     <td>Support Secure Boot devices.</td>
*   </tr>
*   <tr>
*     <td>Renamed Function Cy_Flash_StartErase() to Cy_Flash_StartEraseRow().</td>
*     <td>The driver improvements based on the usability feedback.</td>
*   </tr>
*   <tr>
*     <td>Added new API functions \ref Cy_Flash_EraseSector,
*         \ref Cy_Flash_StartEraseSector, \ref Cy_Flash_EraseSubsector,
*         \ref Cy_Flash_StartEraseSubsector </td>
*     <td>The driver improvements based on the usability feedback.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">3.20</td>
*     <td>Flattened the organization of the driver source code into the single source directory and the single include directory.</td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td>Added new API function \ref Cy_Flash_InitExt</td>
*     <td>The driver improvements based on the usability feedback</td>
*   </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using dereferenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
*   <tr>
*     <td>3.11</td>
*     <td>Updated driver functionality to correctly use the SysClk measurement
*         counters while partially blocking flash operations</td>
*     <td>Added arbiter mechanism for correct usage of the SysClk measurement
*         counters</td>
*   </tr>
*   <tr>
*     <td>3.10</td>
*     <td>Updated Cy_Flash_SendCmd() code to support single core devices.</td>
*     <td>Support new devices</td>
*   </tr>
*   <tr>
*     <td>3.0</td>
*     <td>New function - Cy_Flash_ProgramRow();<br>
*         Updated Cy_Flash_RowChecksum(): changed input parameter to take the
*         <b>row address</b> (rowAddr) instead of the <b>row number</b>
*         (rowNum);<br>
*         Renamed macro for disabling RWW support in driver to
*         <b>CY_FLASH_RWW_DRV_SUPPORT_DISABLED</b>.<br>
*         Updated \ref group_flash_configuration documentation section with
*         flash usage constraints.</td>
*     <td>Improvements made based on usability feedback to use a common
*         interface</td>
*   </tr>
*   <tr>
*     <td rowspan="3">2.0</td>
*     <td>Added non-blocking erase function - Cy_Flash_StartErase().
*         Removed the clear cache function call.</td>
*     <td>The clear cache operation is removed from the blocking Write/Erase
*         function because in this case it is performed by the hardware.
*         Otherwise it is documented that it is the user's responsibility to
*         clear the cache after executing the non-blocking Write/Erase flash
*         operation.</td>
*   </tr>
*   <tr>
*     <td>Added new Cy_Flash_IsOperationComplete() function to check completeness.
*         Obsoleted Cy_Flash_IsWriteComplete(), Cy_Flash_IsProgramComplete(),
*         and Cy_Flash_IsEraseComplete() functions.<br>
*         Added Cy_Flash_GetExternalStatus() function to get unparsed status where
*         flash driver will be used in security applications with other modules
*         as SecureImage.<br>
*         Added Cy_Flash_Init() function to initialize all needed prerequisites
*         for Erase/Write operations.</td>
*     <td>Updated driver design to improve user experience.</td>
*   </tr>
*   <tr>
*     <td>Updated driver implementation to remove MISRA rules deviations.</td>
*     <td>Driver implementation quality improvement.</td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_flash_macros Macros
* \{
*     \defgroup group_flash_general_macros Flash general parameters
*         Provides general information about flash
*
*     \defgroup group_flash_config_macros  Flash configuration
*         Specifies the parameter values passed to SROM API
* \}
* \defgroup group_flash_functions Functions
* \defgroup group_flash_enumerated_types Enumerated Types
* \defgroup group_flash_srom_config_structure Structures
*/

#include "cy_device.h"

#if defined (CY_IP_M4CPUSS) || defined (CY_IP_M7CPUSS)

#include "cy_ipc_drv.h"
#include "cy_syslib.h"
#if defined(CY_IP_MXFLASHC_VERSION_ECT)
#include "cy_flash_srom.h"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
* Macro definitions
***************************************/
/**
* \addtogroup group_flash_macros
* \{
*/

/** Driver major version */
#define CY_FLASH_DRV_VERSION_MAJOR       3

/** Driver minor version */
#define CY_FLASH_DRV_VERSION_MINOR       70

#define CY_FLASH_ID               (CY_PDL_DRV_ID(0x14UL))                          /**< FLASH PDL ID */

#define CY_FLASH_ID_INFO          (uint32_t)( CY_FLASH_ID | CY_PDL_STATUS_INFO )   /**< Return prefix for FLASH driver function status codes */
#define CY_FLASH_ID_WARNING       (uint32_t)( CY_FLASH_ID | CY_PDL_STATUS_WARNING) /**< Return prefix for FLASH driver function warning return values */
#define CY_FLASH_ID_ERROR         (uint32_t)( CY_FLASH_ID | CY_PDL_STATUS_ERROR)   /**< Return prefix for FLASH driver function error return values */

/** \} group_flash_macros */


/**
* \addtogroup group_flash_general_macros
* \{
*/

/** Flash row size */
#define CY_FLASH_SIZEOF_ROW                (CPUSS_FLASHC_PA_SIZE * 4U)
/** Long words flash row size */
#define CY_FLASH_SIZEOF_ROW_LONG_UNITS     (CY_FLASH_SIZEOF_ROW / sizeof(uint32_t))

/** \} group_flash_general_macros */

#if defined(CY_IP_MXFLASHC_VERSION_ECT)

/** \cond INTERNAL */

/** Flash bounds */
typedef enum
{
    CY_FLASH_IN_BOUNDS,
    CY_FLASH_OUT_OF_BOUNDS,
} en_flash_bounds_t;

#define CY_FLASH_NUMBER_ROWS (CPUSS_FLASH_SIZE/CY_FLASH_SIZEOF_ROW) /** Number of flash rows */

#define CY_WFLASH_LG_SBM_TOP  CY_WFLASH_LG_SBM_BASE
#define CY_WFLASH_LG_SBM_END  (CY_WFLASH_LG_SBM_BASE + CY_WFLASH_LG_SBM_SIZE)

#define CY_WFLASH_SM_SBM_TOP  CY_WFLASH_SM_SBM_BASE
#define CY_WFLASH_SM_SBM_END  (CY_WFLASH_SM_SBM_BASE + CY_WFLASH_SM_SBM_SIZE)

#define CY_WFLASH_LG_DBM0_TOP CY_WFLASH_LG_DBM0_BASE
#define CY_WFLASH_LG_DBM0_END (CY_WFLASH_LG_DBM0_BASE + CY_WFLASH_LG_DBM0_SIZE)

#define CY_WFLASH_SM_DBM0_TOP CY_WFLASH_SM_DBM0_BASE
#define CY_WFLASH_SM_DBM0_END (CY_WFLASH_SM_DBM0_BASE + CY_WFLASH_SM_DBM0_SIZE)

#define CY_WFLASH_LG_DBM1_TOP CY_WFLASH_LG_DBM1_BASE
#define CY_WFLASH_LG_DBM1_END (CY_WFLASH_LG_DBM1_BASE + CY_WFLASH_LG_DBM1_SIZE)

#define CY_WFLASH_SM_DBM1_TOP CY_WFLASH_SM_DBM1_BASE
#define CY_WFLASH_SM_DBM1_END (CY_WFLASH_SM_DBM1_BASE + CY_WFLASH_SM_DBM1_SIZE)

#define CY_FLASH_LG_SBM_TOP  CY_FLASH_LG_SBM_BASE
#define CY_FLASH_LG_SBM_END  (CY_FLASH_LG_SBM_BASE + CY_FLASH_LG_SBM_SIZE)

#define CY_FLASH_SM_SBM_TOP  CY_FLASH_SM_SBM_BASE
#define CY_FLASH_SM_SBM_END  (CY_FLASH_SM_SBM_BASE + CY_FLASH_SM_SBM_SIZE)

#define CY_FLASH_LG_DBM0_TOP CY_FLASH_LG_DBM0_BASE
#define CY_FLASH_LG_DBM0_END (CY_FLASH_LG_DBM0_BASE + CY_FLASH_LG_DBM0_SIZE)

#define CY_FLASH_SM_DBM0_TOP CY_FLASH_SM_DBM0_BASE
#define CY_FLASH_SM_DBM0_END (CY_FLASH_SM_DBM0_BASE + CY_FLASH_SM_DBM0_SIZE)

#define CY_FLASH_LG_DBM1_TOP CY_FLASH_LG_DBM1_BASE
#define CY_FLASH_LG_DBM1_END (CY_FLASH_LG_DBM1_BASE + CY_FLASH_LG_DBM1_SIZE)

#define CY_FLASH_SM_DBM1_TOP CY_FLASH_SM_DBM1_BASE
#define CY_FLASH_SM_DBM1_END (CY_FLASH_SM_DBM1_BASE + CY_FLASH_SM_DBM1_SIZE)

#define CY_SFLASH_TOP  CY_SFLASH_BASE
#define CY_SFLASH_END  (CY_SFLASH_BASE + CY_SFLASH_SIZE)

#define CY_SFLASH1_TOP CY_SFLASH1_BASE
#define CY_SFLASH1_END (CY_SFLASH1_BASE + CY_SFLASH1_SIZE)

#define CY_WORK_LES_SIZE_IN_BYTE  (0x00000800UL)
#define CY_WORK_LES_SIZE_IN_WORD  (0x00000800UL / 4UL)
#define CY_WORK_SES_SIZE_IN_BYTE  (0x00000080UL)
#define CY_WORK_SES_SIZE_IN_WORD  (0x00000080UL / 4UL)

#define CY_CODE_LES_SIZE_IN_BYTE  (0x00008000UL)
#define CY_CODE_LES_SIZE_IN_WORD  (0x00008000UL / 4UL)
#define CY_CODE_SES_SIZE_IN_BYTE  (0x00002000UL)
#define CY_CODE_SES_SIZE_IN_WORD  (0x00002000UL / 4UL)


typedef enum
{
    CY_FLASH_MAIN_REGION = 0U,
    CY_FLASH_WORK_REGION,
    CY_FLASH_CA_CM0P_REGION
} cy_en_region_t;

typedef enum
{
    CY_FLASH_SINGLE_BANK_MODE = 0U,
    CY_FLASH_DUAL_BANK_MODE = 1U
} cy_en_bankmode_t;

typedef enum
{
    CY_FLASH_MAPPING_A = 0U,
    CY_FLASH_MAPPING_B = 1U
} cy_en_maptype_t;

/** \endcond */
#endif // (defined(CY_IP_MXFLASHC_VERSION_ECT))



/**
* \addtogroup group_flash_enumerated_types
* \{
*/

/** This enum has the return values of the Flash driver */
typedef enum cy_en_flashdrv_status
{
    CY_FLASH_DRV_SUCCESS                  =   0x00UL,  /**< Success */
    CY_FLASH_DRV_INV_PROT                 =   ( CY_FLASH_ID_ERROR + 0x0UL),  /**< Invalid device protection state */
    CY_FLASH_DRV_INVALID_FM_PL            =   ( CY_FLASH_ID_ERROR + 0x1UL),  /**< Invalid flash page latch address */
    CY_FLASH_DRV_INVALID_FLASH_ADDR       =   ( CY_FLASH_ID_ERROR + 0x2UL),  /**< Invalid flash address */
    CY_FLASH_DRV_ROW_PROTECTED            =   ( CY_FLASH_ID_ERROR + 0x3UL),  /**< Row is write protected */
    CY_FLASH_DRV_IPC_BUSY                 =   ( CY_FLASH_ID_ERROR + 0x5UL),  /**< IPC structure is already locked by another process */
    CY_FLASH_DRV_INVALID_INPUT_PARAMETERS =   ( CY_FLASH_ID_ERROR + 0x6UL),  /**< Input parameters passed to Flash API are not valid */
    CY_FLASH_DRV_PL_ROW_COMP_FA           =   ( CY_FLASH_ID_ERROR + 0x22UL), /**< Comparison between Page Latches and FM row failed */
    CY_FLASH_DRV_ERR_UNC                  =   ( CY_FLASH_ID_ERROR + 0xFFUL), /**< Unknown error code. See \ref Cy_Flash_GetExternalStatus() */
    CY_FLASH_DRV_PROGRESS_NO_ERROR        =   ( CY_FLASH_ID_INFO  + 0x0UL),  /**< Command in progress; no error */
    CY_FLASH_DRV_OPERATION_STARTED        =   ( CY_FLASH_ID_INFO  + 0x1UL),  /**< Flash operation is successfully initiated */
    CY_FLASH_DRV_OPCODE_BUSY              =   ( CY_FLASH_ID_INFO  + 0x2UL),  /**< Flash is under operation */
    CY_FLASH_DRV_CHECKSUM_NON_ZERO        =   ( CY_FLASH_ID_ERROR + 0x4UL),  /**< Checksum of FLASH resulted in non-zero (SROM STATUS CODE: 0xF000000A) */
    CY_FLASH_DRV_NO_ERASE_SUSPEND         =   ( CY_FLASH_ID_ERROR + 0x7UL),  /**< Returned when EraseResume is called when no sector is suspended from erase (SROM STATUS CODE: 0xF0000092) */
    CY_FLASH_DRV_FLASH_NOT_ERASED         =   ( CY_FLASH_ID_ERROR + 0x8UL),  /**< Returned when ProgramRow is invoked on unerased cells or blank check fails (SROM STATUS CODE: 0xF00000A4) */
    CY_FLASH_DRV_NO_ERASE_ONGOING         =   ( CY_FLASH_ID_ERROR + 0x9UL),  /**< Returned by EraseSuspend when called with no ongoing erase operation (SROM STATUS CODE: 0xF00000A5) */
    CY_FLASH_DRV_ACTIVE_ERASE             =   ( CY_FLASH_ID_ERROR + 0xAUL),  /**< Returned by ProgramRow when active erase operation is going on (SROM STATUS CODE: 0xF00000A6) */
    CY_FLASH_DRV_INVALID_DATA_WIDTH       =   ( CY_FLASH_ID_ERROR + 0xBUL),  /**< Returned by ProgramRow API if invalid program width option is provided (SROM STATUS CODE: 0xF00000A8) */
    CY_FLASH_DRV_FLASH_SAFTEY_ENABLED     =   ( CY_FLASH_ID_ERROR + 0xCUL),  /**< Returned by FLASH program/erase APIs when writes are disabled in safety register (SROM STATUS CODE: 0xF00000AA) */
    CY_FLASH_DRV_INVALID_SFLASH_ADDR      =   ( CY_FLASH_ID_ERROR + 0xDUL),  /**< Returned when WriteRow is called on invalid SFLASH rows in NORMAL state (SROM STATUS CODE: 0xF00000B2) */
    CY_FLASH_DRV_SFLASH_BACKUP_ERASED     =   ( CY_FLASH_ID_ERROR + 0xEUL),  /**< Returned by Sflash programming APIs when backup sector is in erased state (SROM STATUS CODE: 0xF00000BB) */
    CY_FLASH_DRV_SECTOR_SUSPEND           =   ( CY_FLASH_ID_ERROR + 0xFUL),  /**< Returned when Program operation is called on sector which is suspended from erase (SROM STATUS CODE: 0xF0000091) */
    CY_FLASH_DRV_SROM_API_TIMEOUT         =   ( CY_FLASH_ID_ERROR + 0x10UL)  /**< Time out happens after calling srom API driver */
} cy_en_flashdrv_status_t;


#if !defined (CY_FLASH_RWW_DRV_SUPPORT_DISABLED)
    /** Flash notification configuration structure */
    typedef struct
    {
        uint8_t  clientID;      /**< Client ID */
        uint8_t  pktType;       /**< Message Type */
        uint16_t intrRelMask;   /**< Mask */
    } cy_stc_flash_notify_t;
#endif /* !defined (CY_FLASH_RWW_DRV_SUPPORT_DISABLED) */

/** \} group_flash_enumerated_types */

#if (defined(CY_IP_MXFLASHC_VERSION_ECT))

/**
* \addtogroup group_flash_enumerated_types
* \{
*/
/** Flash Program row data size configuration */
typedef enum
{
    CY_FLASH_PROGRAMROW_DATA_SIZE_8BIT    = (0x00UL),   /**< Set program row data size 8 bit */
    CY_FLASH_PROGRAMROW_DATA_SIZE_16BIT   = (0x01UL),   /**< Set program row data size 16 bit */
    CY_FLASH_PROGRAMROW_DATA_SIZE_32BIT   = (0x02UL),   /**< Set program row data size 32 bit */
    CY_FLASH_PROGRAMROW_DATA_SIZE_64BIT   = (0x03UL),   /**< Set program row data size 64 bit */
    CY_FLASH_PROGRAMROW_DATA_SIZE_128BIT  = (0x04UL),   /**< Set program row data size 128 bit */
    CY_FLASH_PROGRAMROW_DATA_SIZE_256BIT  = (0x05UL),   /**< Set program row data size 256 bit */
    CY_FLASH_PROGRAMROW_DATA_SIZE_512BIT  = (0x06UL),   /**< Set program row data size 512 bit */
    CY_FLASH_PROGRAMROW_DATA_SIZE_1024BIT = (0x07UL),   /**< Set program row data size 1024 bit */
    CY_FLASH_PROGRAMROW_DATA_SIZE_2048BIT = (0x08UL),   /**< Set program row data size 2048 bit */
    CY_FLASH_PROGRAMROW_DATA_SIZE_4096BIT = (0x09UL)    /**< Set program row data size 4096 bit */
} cy_en_flash_programrow_datasize_t;

/** Flash Program row function execution type configuration */
typedef enum
{
    CY_FLASH_PROGRAMROW_NON_BLOCKING = (0x00UL),   /**< Set program row API in non blocking mode */
    CY_FLASH_PROGRAMROW_BLOCKING     = (0x01UL)    /**< Set program row API in blocking mode */
} cy_en_flash_programrow_blocking_t;

/** Flash blank check on Program row configuration */
typedef enum
{
    CY_FLASH_PROGRAMROW_BLANK_CHECK      =  (0x00UL),    /**< Performs blank check on Program Row */
    CY_FLASH_PROGRAMROW_SKIP_BLANK_CHECK =  (0x01UL)     /**< Does not perform blank check on Program Row */
} cy_en_flash_programrow_skipblankcheck_t;

/** Flash Program row data location configuration */
typedef enum
{
    CY_FLASH_PROGRAMROW_DATA_LOCATION_SRAM       = (0x01UL)  /**< Program Row data location is sram */
} cy_en_flash_programrow_location_t;

/** Flash Program row interrupt mask configuration */
typedef enum
{
    CY_FLASH_PROGRAMROW_NOT_SET_INTR_MASK = (0x00UL),  /**< Program Row API interrupt is not set */
    CY_FLASH_PROGRAMROW_SET_INTR_MASK     = (0x01UL)   /**< Program Row API interrupt is set */
} cy_en_flash_programrow_intrmask_t;

/** Flash Erase sector function execution type configuration */
typedef enum
{
    CY_FLASH_ERASESECTOR_NON_BLOCKING      = (0x00UL), /**< Erase sector API executed in non blocking mode */
    CY_FLASH_ERASESECTOR_BLOCKING          = (0x01UL)  /**< Erase sector API executed in blocking mode */
} cy_en_flash_erasesector_blocking_t;

/** Flash Erase sector interrupt mask configuration */
typedef enum
{
    CY_FLASH_ERASESECTOR_NOT_SET_INTR_MASK = (0x00UL), /**< Erase sector API interrupt is not set */
    CY_FLASH_ERASESECTOR_SET_INTR_MASK     = (0x01UL)  /**< Erase sector API interrupt is set */
} cy_en_flash_erasesector_intrmask_t;

/** Flash checksum bank configuration */
typedef enum
{
    CY_FLASH_CHECKSUM_BANK0     = (0x00UL), /**< Checksum calculated for Bank0 */
    CY_FLASH_CHECKSUM_BANK1     = (0x01UL)  /**< Checksum calculated for Bank1 */
} cy_en_flash_checksum_bank_t;

/** Flash checksum page configuration */
typedef enum
{
    CY_FLASH_CHECKSUM_PAGE     = (0x00UL), /**< Checksum calculated for that page */
    CY_FLASH_CHECKSUM_WHOLE    = (0x01UL)  /**< Checksum calculated for whole region */
} cy_en_flash_checksum_scope_t;

/** Flash checksum region configuration */
typedef enum
{
    CY_FLASH_CHECKSUM_MAIN        = (0x00UL), /**< Checksum calculated for Main flash region */
    CY_FLASH_CHECKSUM_WORK        = (0x01UL), /**< Checksum calculated for Work flash region */
    CY_FLASH_CHECKSUM_SUPERVISORY = (0x02UL)  /**< Checksum calculated for Supervisory flash region */
} cy_en_flash_checksum_region_t;

/** Flash compute hash configuration */
typedef enum
{
    CY_FLASH_COMPUTEHASH_BASIC  = (0x00UL), /**< Compute Basic hash */
    CY_FLASH_COMPUTEHASH_CRC8   = (0x01UL)  /**< Compute CRC8 hash */
} cy_en_flash_computehash_type_t;

/** Flash Erase resume interrupt mask configuration */
typedef enum
{
    CY_FLASH_ERASERESUME_NOT_SET_INTR_MASK  = (0x00UL), /**< Erase resume API interrupt is not set */
    CY_FLASH_ERASERESUME_SET_INTR_MASK      = (0x01UL)  /**< Erase resume API interrupt is set */
} cy_en_flash_eraseresume_setintr_t;

/** Flash Erase resume function execution type configuration */
typedef enum
{
    CY_FLASH_ERASERESUME_NON_BLOCKING  = (0x00UL), /**< Set erase resume API in non blocking mode */
    CY_FLASH_ERASERESUME_BLOCKING      = (0x01UL)  /**< Set erase resume API in blocking mode */
} cy_en_flash_eraseresume_blocking_t;

/** Flash driver function execution type configuration */
typedef enum
{
    CY_FLASH_DRIVER_NON_BLOCKING  = (0x00UL),    /**< Set SROM API in non blocking mode */
    CY_FLASH_DRIVER_BLOCKING      = (0x01UL)     /**< Set SROM API in blocking mode */
} cy_en_flash_driver_blocking_t;

/** \} group_flash_enumerated_types */
#endif // (defined(CY_IP_MXFLASHC_VERSION_ECT))

/***************************************
* Data Structure definitions
***************************************/
#if (defined(CY_IP_MXFLASHC_VERSION_ECT))

/**
* \addtogroup group_flash_srom_config_structure
* \{
*/
/** Flash program row configuration structure */
typedef struct
{
    const uint32_t*                         destAddr; /**< Destination address of flash  */
    const uint32_t*                         dataAddr; /**< pointer to 32byte aligned source data to be written to the flash */
    cy_en_flash_programrow_blocking_t       blocking; /**< blocking or non blocking mode. \ref cy_en_flash_programrow_blocking_t */
    cy_en_flash_programrow_skipblankcheck_t skipBC;   /**< blank check operation \ref cy_en_flash_programrow_skipblankcheck_t */
    cy_en_flash_programrow_datasize_t       dataSize; /**< size of the data to be written. \ref cy_en_flash_programrow_datasize_t */
    cy_en_flash_programrow_location_t       dataLoc;  /**< data location for the operation \ref cy_en_flash_programrow_location_t */
    cy_en_flash_programrow_intrmask_t       intrMask; /**< interrupt mask to be set. \ref cy_en_flash_programrow_intrmask_t */
}cy_stc_flash_programrow_config_t;

/** Flash erase row configuration structure */
typedef struct
{
    const uint32_t*                    sectorAddr;  /**< Sector address to be erased */
    cy_en_flash_erasesector_blocking_t blocking;    /**< blocking or non blocking mode \ref cy_en_flash_erasesector_blocking_t */
    cy_en_flash_erasesector_intrmask_t intrMask;    /**< interrupt mask to be set. \ref cy_en_flash_erasesector_intrmask_t */
}cy_stc_flash_erasesector_config_t;

/** Flash checksum configuration structure */
typedef struct
{
    uint8_t                       rowId;  /**< row id for checksum */
    cy_en_flash_checksum_bank_t   bank;   /**< Checksum calculated for Bank0 or Bank1 \ref cy_en_flash_checksum_bank_t */
    cy_en_flash_checksum_scope_t  whole;  /**< Checksum calculated for whole region or page \ref cy_en_flash_checksum_scope_t */
    cy_en_flash_checksum_region_t region; /**< Specifies the configuration of flash operation \ref cy_en_flash_checksum_region_t */
} cy_stc_flash_checksum_config_t;

/** Flash compute hash configuration structure */
typedef struct
{
    const uint32_t*                startAddr; /**< Address for computing hash */
    uint32_t                       numOfByte; /**< Number of Bytes for computing hash */
    cy_en_flash_computehash_type_t type;      /**< Compute CRC8 hash or basic hash. /ref cy_en_flash_computehash_type_t*/
} cy_stc_flash_computehash_config_t;

/** Flash erase resume configuration structure */
typedef struct
{
    cy_en_flash_eraseresume_setintr_t  intrMask; /**< Interrupt mask for erase resume operation \ref cy_en_flash_eraseresume_setintr_t */
    cy_en_flash_eraseresume_blocking_t blocking; /**< Blocking or non blocking mode. \ref cy_en_flash_eraseresume_blocking_t */
} cy_stc_flash_eraseresume_config_t;

/** Flash blank check configuration structure */
typedef struct
{
    const uint32_t* addrToBeChecked;         /**< Address for which blank check to be performed. */
    uint32_t        numOfWordsToBeChecked;   /**< No of words to be checked. */
} cy_stc_flash_blankcheck_config_t;

/** \} group_flash_srom_config_structure */

#endif // (defined(CY_IP_MXFLASHC_VERSION_ECT))


/***************************************
* Function Prototypes
***************************************/
#if (defined(CY_IP_MXFLASHC_VERSION_ECT))


/**
* \addtogroup group_flash_functions
* \{
*/


/*******************************************************************************
* Function Name: Cy_Flashc_MainWriteEnable
****************************************************************************//**
*
* \brief Enable writing to main flash.
* Enables writing to main flash.
*
* \note This function is applicable for CAT1C devices.
*
* \return none
*
*******************************************************************************/
void Cy_Flashc_MainWriteEnable(void);


/*******************************************************************************
* Function Name: Cy_Flashc_MainWriteDisable
****************************************************************************//**
*
* \brief Disable writing to main flash
* Disables writing to main flash.
*
* \note This function is applicable for CAT1C devices.
*
* \return none
*
*******************************************************************************/
void Cy_Flashc_MainWriteDisable(void);


/*******************************************************************************
* Function Name: Cy_Flashc_WorkWriteEnable
****************************************************************************//**
*
* \brief Enable writing work flash
* Work Flash embedded operations are enabled.
*
* \note This function is applicable for CAT1C devices.
*
* \return none
*
*******************************************************************************/
void Cy_Flashc_WorkWriteEnable(void);


/*******************************************************************************
* Function Name: Cy_Flashc_WorkWriteDisable
****************************************************************************//**
*
* \brief Disable writing work flash
* Work Flash embedded operations are blocked
*
* \note This function is applicable for CAT1C devices.
*
* \return none
*
*******************************************************************************/
void Cy_Flashc_WorkWriteDisable(void);


/*******************************************************************************
* Function Name: Cy_Flashc_WorkECCEnable
****************************************************************************//**
*
* \brief Enables ECC for work flash
* ECC checking/reporting on FLASH work interface is enabled.
* Correctable or non-correctable faults are reported by enabling ECC.
*
* \note This function is applicable for CAT1C devices.
*
* \return none
*
*******************************************************************************/
void Cy_Flashc_WorkECCEnable(void);

/*******************************************************************************
* Function Name: Cy_Flashc_WorkECCDisable
****************************************************************************//**
*
* \brief Disables ECC for work flash
* ECC checking/reporting on FLASH work interface is disabled.
* No correctable or non-correctable faults are reported by disabling ECC.
*
* \note This function is applicable for CAT1C devices.
*
* \return none
*
*******************************************************************************/
void Cy_Flashc_WorkECCDisable(void);


/*******************************************************************************
* Function Name: Cy_Flashc_MainECCEnable
****************************************************************************//**
*
* \brief Enables ECC for main flash
* ECC checking/reporting on FLASH main interface is enabled.
* Correctable or non-correctable faults are reported by enabling ECC.
*
* \note This function is applicable for CAT1C devices.
*
* \return none
*
*******************************************************************************/
void Cy_Flashc_MainECCEnable(void);

/*******************************************************************************
* Function Name: Cy_Flashc_MainECCDisable
****************************************************************************//**
*
* \brief Disables ECC for main flash.
* ECC checking/reporting on FLASH main interface is disabled.
* No correctable or non-correctable faults are reported by disabling ECC.
*
* \note This function is applicable for CAT1C devices.
*
* \return none
*
*******************************************************************************/
void Cy_Flashc_MainECCDisable(void);

/*******************************************************************************
* Function Name: Cy_Flash_Program_WorkFlash
****************************************************************************//**
*
* This function writes an array data to work flash. Reports success or
* or a reason for failure. User should only pass work flash address else it will return an error.
* This function executes in blocking mode only.
*
* Returns immediately and reports a CY_FLASH_DRV_IPC_BUSY error in the case when another
* process is operating flash. User firmware should not enter the hibernate
* mode until flash Write is complete. The Flash operation is allowed in Sleep and
* Deep-sleep modes. During the Flash operation, the device should not be reset,
* including the XRES pin, a software reset, and watchdog reset sources. Also,
* low-voltage detect circuits should be configured to generate an interrupt instead
* of a reset. Otherwise, portions of flash may undergo unexpected changes.
* \note  A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring flash sector where the flash Write, Erase, or
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation,
* use Cy_Flash_IsOperationComplete() to ensure flash operation is complete.
*
* \note This function is applicable for CAT1C devices.
*
* \note User needs to make sure that the data pointer passed to this function points to 32 byte aligned data.
*
* \param config configuration of this function.
* This parameter is defined by the cy_stc_flash_programrow_config_t
* in \ref group_flash_srom_config_structure macro.
*
* \return Returns the status of the Flash operation (see \ref cy_en_flashdrv_status_t).
*
* \funcusage
* \snippet flash/snippet/main.c snippet_Cy_Flash_Program_WorkFlash
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_Program_WorkFlash(const cy_stc_flash_programrow_config_t* config);

/*******************************************************************************
* Function Name: Cy_Flash_Program
****************************************************************************//**
*
* This function writes an array of data to flash. Reports success or
* or a reason for failure.
* Returns immediately and reports a CY_FLASH_DRV_IPC_BUSY error in the case when another
* process is operating flash. User firmware should not enter the hibernate
* mode until flash Write is complete. The Flash operation is allowed in Sleep and
* Deep-sleep modes. During the Flash operation, the device should not be reset,
* including the XRES pin, a software reset, and watchdog reset sources. Also,
* low-voltage detect circuits should be configured to generate an interrupt instead
* of a reset. Otherwise, portions of flash may undergo unexpected changes.
* \note  A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring flash sector where the flash Write, Erase, or
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation,
* use Cy_Flash_IsOperationComplete() to ensure flash operation is complete.
*
* \note This function is applicable for CAT1C devices.
*
* \note User needs to make sure that the data pointer passed to this function points to 32 byte aligned data.
*
* \param config configuration of this function.
* This parameter is defined by the cy_stc_flash_programrow_config_t
* in \ref group_flash_srom_config_structure macro.
*
* \param block specifies if the function to execute in blocking or non blocking mode.
*
* \return Returns the status of the Flash operation (see \ref cy_en_flashdrv_status_t).
* returns CY_FLASH_DRV_OPERATION_STARTED if operation starts with out error in non blocking mode.
* returns CY_FLASH_DRV_SUCCESS in blocking mode.
*
* \funcusage
* \snippet flash/snippet/main.c snippet_Cy_Flash_Program
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_Program(const cy_stc_flash_programrow_config_t* config, cy_en_flash_driver_blocking_t block);

/*******************************************************************************
* Function Name: Cy_Flash_Checksum
****************************************************************************//**
*
* Returns a checksum value of the specified flash row. supports only blocking
* mode for now.
*
* \note This function is applicable for CAT1C devices.
*
* \param config configuration of this function.
* This parameter is defined by the cy_stc_flash_checksum_config_t
* in \ref cy_stc_flash_checksum_config_t macro.
*
* \param checksumPtr The pointer to the address where checksum is to be stored
*
* \return Returns the status of the Flash operation.
*
* \funcusage
* \snippet flash/snippet/main.c snippet_Cy_Flash_Checksum
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_Checksum (const cy_stc_flash_checksum_config_t *config, uint32_t* checksumPtr);

/*******************************************************************************
* Function Name: Cy_Flash_EraseSuspend
****************************************************************************//**
*
* This function suspends an ongoing erase operation. User should not read from a
* sector which is suspended from an erase operation. Cy_Flash_ProgramRow function
* will return error if invoked on suspended sector.
* This function cannot be called on SFLASH. Reports success
* or a reason for failure. Does not return until the Erase operation is complete.
* Returns immediately and reports a CY_FLASH_DRV_IPC_BUSY error in the case when another
* process is operating flash.
* This function supports only blocking mode for now.
*
* \note This function is applicable for CAT1C devices.
*
* \return Returns the status of the Flash operation (see \ref cy_en_flashdrv_status_t).
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_EraseSuspend(void);

/*******************************************************************************
* Function Name: Cy_Flash_EraseResume
****************************************************************************//**
*
* This function calls to resume a suspended erase operation.
* Reports success or a reason for failure.
* Returns immediately and reports a CY_FLASH_DRV_IPC_BUSY error in the case when another
* process is operating flash.
* \note  A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring flash sector where the flash Write, Erase, or
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation,
* use Cy_Flash_IsOperationComplete() to ensure flash operation is complete.
*
* \note This function is applicable for CAT1C devices.
*
* \param config configuration of this function.
* This parameter is defined by the cy_stc_flash_eraseresume_config_t
* in \ref group_flash_srom_config_structure macro.
*
* \return Returns the status of the Flash operation (see \ref cy_en_flashdrv_status_t).
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_EraseResume(const cy_stc_flash_eraseresume_config_t *config);

/*******************************************************************************
* Function Name: Cy_Flash_BlankCheck
****************************************************************************//**
*
* This function performs blank check on the addressed work FLASH.
* Reports success or a reason for failure.
* Returns immediately and reports a CY_FLASH_DRV_IPC_BUSY error in the case when another
* process is operating flash.
*
* \note This function is applicable for CAT1C devices.
*
* \param config configuration of this function.
* This parameter is defined by the cy_stc_flash_blankcheck_config_t
* in \ref group_flash_srom_config_structure macro.
*
* \param block specifies if the function to execute in blocking or non blocking mode.
*
* \return Returns the status of the Flash operation (see \ref cy_en_flashdrv_status_t).
* returns CY_FLASH_DRV_OPERATION_STARTED if operation starts with out error in non blocking mode.
* returns CY_FLASH_DRV_SUCCESS in blocking mode.
*
* \funcusage
* \snippet flash/snippet/main.c snippet_Flashc_test_code
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_BlankCheck(const cy_stc_flash_blankcheck_config_t *config, cy_en_flash_driver_blocking_t block);

/*******************************************************************************
* Function Name: Cy_Flash_OperationStatus
****************************************************************************//**
*
* Checks the status of the Flash Operation, and returns it.
*
* \return Driver status.
* returns CY_FLASH_DRV_OPERATION_STARTED if operation in non blocking mode is not complete.
* returns CY_FLASH_DRV_SUCCESS if the operation is complete.
*
* \funcusage
* \snippet flash/snippet/main.c snippet_Flashc_test_code
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_OperationStatus(void);

/*******************************************************************************
* Function Name: Cy_Flashc_InjectECC
****************************************************************************//**
*
* This function enables ECC injection and sets the address where a parity will be injected
* and the parity value.
* Reports success or a reason for failure.
*
* \note This function is applicable for CAT1C devices.
*
* \param region An indicator which region (Code/Work/Cache) ECC parity will be injected to.
* This parameter is defined by the cy_en_region_t
* in \ref group_flash_macros macro.
*
* \param address The address where ECC parity will be injected.
*
* \param parity The parity value which will be injected.
*
* \return Returns the status of the Flash operation (see \ref cy_en_flashdrv_status_t).
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flashc_InjectECC(cy_en_region_t region, uint32_t address, uint8_t parity);


/*******************************************************************************
* Function Name: Cy_Flashc_SetWorkBankMode
****************************************************************************//**
*
* \brief Sets bank mode for work flash
* \note This function is applicable for CAT1C devices.
*
*
* \param mode bank mode to be set
*
* \return none
*
* \funcusage
* \snippet flash/snippet/main.c snippet_Cy_Flashc_WorkBankMode
*******************************************************************************/
void Cy_Flashc_SetWorkBankMode(cy_en_bankmode_t mode);

/*******************************************************************************
* Function Name: Cy_Flashc_GetWorkBankMode
****************************************************************************//**
*
* \brief Gets current bank mode for work flash
* \note This function is applicable for CAT1C devices.
*
*
* \return Current bank mode
*
* \funcusage
* \snippet flash/snippet/main.c snippet_Cy_Flashc_WorkBankMode
*******************************************************************************/
cy_en_bankmode_t Cy_Flashc_GetWorkBankMode(void);

/*******************************************************************************
* Function Name: Cy_Flashc_SetMainBankMode
****************************************************************************//**
*
* \brief Sets bank mode for main flash
*
* \param mode bank mode to be set
*
* \return
*
* \funcusage
* \snippet flash/snippet/main.c snippet_Cy_Flashc_MainBankMode
*******************************************************************************/
void Cy_Flashc_SetMainBankMode(cy_en_bankmode_t mode);

/*******************************************************************************
* Function Name: Cy_Flashc_GetMainBankMode
****************************************************************************//**
*
* \brief Gets current bank mode for main flash
* \note This function is applicable for CAT1C devices.
*
*
* \return Current bank mode
*
* \funcusage
* \snippet flash/snippet/main.c snippet_Cy_Flashc_MainBankMode
*******************************************************************************/
cy_en_bankmode_t Cy_Flashc_GetMainBankMode(void);


/** \} group_flash_functions */

#endif

#if ((!defined(CY_IP_MXFLASHC_VERSION_ECT)) || defined(CY_DOXYGEN))

/**
* \addtogroup group_flash_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_Flash_EraseRow
****************************************************************************//**
*
* This function erases a single row of flash. Reports success or
* a reason for failure. Does not return until the Write operation is
* complete. Returns immediately and reports a \ref CY_FLASH_DRV_IPC_BUSY error in
* the case when another process is writing to flash or erasing the row.
* User firmware should not enter the Hibernate or Deep Sleep mode until flash Erase
* is complete. The Flash operation is allowed in Sleep mode.
* During the Flash operation, the device should not be reset, including the
* XRES pin, a software reset, and watchdog reset sources. Also, low-voltage
* detect circuits should be configured to generate an interrupt instead of a
* reset. Otherwise, portions of flash may undergo unexpected changes.
* \note  A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring flash sector where the flash Write, Erase, ors
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation,
* use Cy_Flash_IsOperationComplete() to ensure flash operation is complete.
* \note This function is applicable for CAT1A devices.
*
* \param rowAddr Address of the flash row number.
* The Read-while-Write violation occurs when the flash read operation is
* initiated in the same flash sector where the flash write operation is
* performing. Refer to the device datasheet for the details.
* Address must match row start address.
*
* \return Returns the status of the Flash operation,
* see \ref cy_en_flashdrv_status_t.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_EraseRow(uint32_t rowAddr);

/*******************************************************************************
* Function Name: Cy_Flash_StartEraseRow
****************************************************************************//**
*
* Starts erasing a single row of flash. Returns immediately
* and reports a successful start or reason for failure.
* Reports a \ref CY_FLASH_DRV_IPC_BUSY error in the case when IPC structure is locked
* by another process. User firmware should not enter the Hibernate or Deep Sleep mode until
* flash Erase is complete. The Flash operation is allowed in Sleep mode.
* During the flash operation, the device should not be reset, including the
* XRES pin, a software reset, and watchdog reset sources. Also, the low-voltage
* detect circuits should be configured to generate an interrupt instead of a reset.
* Otherwise, portions of flash may undergo unexpected changes.
* \note To avoid situation of reading data from cache memory - before
* reading data from previously programmed/erased flash rows, the user must
* clear the flash cache with the Cy_SysLib_ClearFlashCacheAndBuffer()
* function.
* \note  A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring flash sector where the flash Write, Erase, or
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation,
* use Cy_Flash_IsOperationComplete() to ensure flash operation is complete.
* \note This function is applicable for CAT1A devices.
*
* \param rowAddr Address of the flash row number.
* The Read-while-Write violation occurs when the flash read operation is
* initiated in the same flash sector where the flash erase operation is
* performing. Refer to the device datasheet for the details.
* Address must match row start address.
*
* \return Returns the status of the Flash operation,
* see \ref cy_en_flashdrv_status_t.
* returns CY_FLASH_DRV_OPERATION_STARTED if operation starts with out error.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_StartEraseRow(uint32_t rowAddr);


/*******************************************************************************
* Function Name: Cy_Flash_EraseSubsector
****************************************************************************//**
*
* This function erases an 8-row subsector of flash. Reports success or
* a reason for failure. Does not return until the Write operation is
* complete. Returns immediately and reports a \ref CY_FLASH_DRV_IPC_BUSY error in
* the case when another process is writing to flash or erasing the row.
* User firmware should not enter the Hibernate or Deep-Sleep mode until flash Erase
* is complete. The Flash operation is allowed in Sleep mode.
* During the Flash operation, the device should not be reset, including the
* XRES pin, a software reset, and watchdog reset sources. Also, low-voltage
* detect circuits should be configured to generate an interrupt instead of a
* reset. Otherwise, portions of flash may undergo unexpected changes.
** \note  A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring flash sector where the flash Write, Erase, or
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation,
* use Cy_Flash_IsOperationComplete() to ensure flash operation is complete.
* \note This function is applicable for CAT1A devices.
*
* \param subSectorAddr Address of the flash row number.
* The Read-while-Write violation occurs when the flash read operation is
* initiated in the same flash sector where the flash write operation is
* performing. Refer to the device datasheet for the details.
* Address must match row start address.
*
* \return Returns the status of the Flash operation,
* see \ref cy_en_flashdrv_status_t.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_EraseSubsector(uint32_t subSectorAddr);

/*******************************************************************************
* Function Name: Cy_Flash_StartEraseSubsector
****************************************************************************//**
*
* Starts erasing an 8-row subsector of flash. Returns immediately
* and reports a successful start or reason for failure.
* Reports a \ref CY_FLASH_DRV_IPC_BUSY error in the case when IPC structure is locked
* by another process. User firmware should not enter the Hibernate or Deep-Sleep mode until
* flash Erase is complete. The Flash operation is allowed in Sleep mode.
* During the flash operation, the device should not be reset, including the
* XRES pin, a software reset, and watchdog reset sources. Also, the low-voltage
* detect circuits should be configured to generate an interrupt instead of a reset.
* Otherwise, portions of flash may undergo unexpected changes.
* \note Before reading data from previously programmed/erased flash rows, the
* user must clear the flash cache with the Cy_SysLib_ClearFlashCacheAndBuffer()
* function.
* \note  A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring flash sector where the flash Write, Erase, or
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation,
* use Cy_Flash_IsOperationComplete() to ensure flash operation is complete.
* \note This function is applicable for CAT1A devices.
*
* \param subSectorAddr Address of the flash row number.
* The Read-while-Write violation occurs when the flash read operation is
* initiated in the same flash sector where the flash erase operation is
* performing. Refer to the device datasheet for the details.
* Address must match row start address.
*
* \return Returns the status of the Flash operation,
* see \ref cy_en_flashdrv_status_t.
* returns CY_FLASH_DRV_OPERATION_STARTED if operation starts with out error.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_StartEraseSubsector(uint32_t subSectorAddr);



/*******************************************************************************
* Function Name: Cy_Flash_WriteRow
****************************************************************************//**
*
* This function writes an array of data to a single row of flash. This is done
* in three steps - pre-program, erase and then program flash row with the input
* data. Reports success or a reason for failure. Does not return until the Write
* operation is complete.
* Returns immediately and reports a \ref CY_FLASH_DRV_IPC_BUSY error in the case
* when another process is writing to flash. User firmware should not enter the
* Hibernate or Deep-sleep mode until flash Write is complete. The Flash operation
* is allowed in Sleep mode. During the Flash operation, the
* device should not be reset, including the XRES pin, a software
* reset, and watchdog reset sources. Also, low-voltage detect
* circuits should be configured to generate an interrupt
* instead of a reset. Otherwise, portions of flash may undergo
* unexpected changes.
* \note  A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring flash sector where the flash Write, Erase, or
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation,
* use Cy_Flash_IsOperationComplete() to ensure flash operation is complete.
*
* \note This is a blocking function and will not return until the Write operation is complete.
* \note This function is applicable for CAT1A devices.
*
* \param rowAddr Address of the flash row number.
* The Read-while-Write violation occurs when the flash read operation is
* initiated in the same flash sector where the flash write operation is
* performing. Refer to the device datasheet for the details.
* Address must match row start address.
*
* \param data The pointer to the data which has to be written to flash. The size
* of the data array must be equal to the flash row size. The flash row size for
* the selected device is defined by the \ref CY_FLASH_SIZEOF_ROW macro. Refer to
* the device datasheet for the details.
*
* \return Returns the status of the Flash operation,
* see \ref cy_en_flashdrv_status_t.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_WriteRow(uint32_t rowAddr, const uint32_t* data);

/*******************************************************************************
* Function Name: Cy_Flash_StartProgram
****************************************************************************//**
*
* Starts writing an array of data to a single row of flash. Returns immediately
* and reports a successful start or reason for failure.
* Reports a \ref CY_FLASH_DRV_IPC_BUSY error if another process is writing
* to flash. The user firmware should not enter Hibernate or Deep-Sleep mode until flash
* Program is complete. The Flash operation is allowed in Sleep mode.
* During the Flash operation, the device should not be reset, including the
* XRES pin, a software reset, and watchdog reset sources. Also, the low-voltage
* detect circuits should be configured to generate an interrupt instead of a reset.
* Otherwise, portions of flash may undergo unexpected changes.\n
* Before calling this function, the target flash region must be erased by
* the StartEraseRow/EraseRow function.\n
* Data to be programmed must be located in the SRAM memory region.
* \note Before reading data from previously programmed/erased flash rows, the
* user must clear the flash cache with the Cy_SysLib_ClearFlashCacheAndBuffer()
* function.
* \note  A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring flash sector where the flash Write, Erase, or
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation,
* use Cy_Flash_IsOperationComplete() to ensure flash operation is complete.
*
* \note This is a non blocking function and will not wait until the Write operation is complete.
* \note This function is applicable for CAT1A devices.
*
* \param rowAddr The address of the flash row number.
* The Read-while-Write violation occurs when the Flash Write operation is
* performing. Refer to the device datasheet for the details.
* The address must match the row start address.
*
* \param data The pointer to the data to be written to flash. The size
* of the data array must be equal to the flash row size. The flash row size for
* the selected device is defined by the \ref CY_FLASH_SIZEOF_ROW macro. Refer to
* the device datasheet for the details.
*
* \return Returns the status of the Flash operation,
* see \ref cy_en_flashdrv_status_t.
* returns CY_FLASH_DRV_OPERATION_STARTED if operation starts with out error.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_StartProgram(uint32_t rowAddr, const uint32_t* data);

/*******************************************************************************
* Function Name: Cy_Flash_GetExternalStatus
****************************************************************************//**
*
* This function handles the case where a module such as security image captures
* a system call from this driver and reports its own status or error code,
* for example protection violation. In that case, a function from this
* driver returns an unknown error (see cy_en_flashdrv_status_t). After receipt
* of an unknown error, the user may call this function to get the status
* of the capturing module.
*
* The user is responsible for parsing the content of the returned value
* and casting it to the appropriate enumeration.
* \note This function is applicable for CAT1A devices.
*
* \return Returns the status of the Flash operation code.
*******************************************************************************/
uint32_t Cy_Flash_GetExternalStatus(void);

#if !defined (CY_FLASH_RWW_DRV_SUPPORT_DISABLED)
/*******************************************************************************
* Function Name: Cy_Flash_InitExt
****************************************************************************//**
*
* Initiates all needed prerequisites to support flash erase/write.
* Should be called from each core. Defines the address of the message structure.
*
* Requires a call to Cy_IPC_Sema_Init(), Cy_IPC_Pipe_Config() and
* Cy_IPC_Pipe_Init() functions before use.
*
* \note This function is applicable for CAT1A devices.
*
* This function is called in the Cy_Flash_Init() function - see the
* \ref Cy_Flash_Init usage considerations.
*
*******************************************************************************/
void Cy_Flash_InitExt(cy_stc_flash_notify_t *ipcWaitMessageAddr);
#endif /* !defined (CY_FLASH_RWW_DRV_SUPPORT_DISABLED) */

/** \} group_flash_functions */

/** \cond INTERNAL */
#if (CY_CPU_CORTEX_M4)
void Cy_Flash_ResumeIrqHandler(void);
#endif

/*******************************************************************************
Backward compatibility macro. The following code is DEPRECATED and must
not be used in new projects
*******************************************************************************/
#define     CY_FLASH_NUMBER_ROWS             (CY_FLASH_SIZE / CY_FLASH_SIZEOF_ROW)
#define     Cy_Flash_StartErase              Cy_Flash_StartEraseRow

/** \endcond */


#endif //(defined(CY_IP_MXFLASHC_VERSION_ECT) || defined(CY_DOXYGEN))

/**
* \addtogroup group_flash_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_Flash_IsOperationComplete
****************************************************************************//**
*
* Reports a successful operation result, reason of failure or busy status
* ( \ref CY_FLASH_DRV_OPCODE_BUSY ).
*
* \return Returns the status of the Flash operation (see \ref cy_en_flashdrv_status_t).
* returns CY_FLASH_DRV_OPERATION_STARTED if operation in non blocking mode is not complete.
* returns CY_FLASH_DRV_SUCCESS if the operation is complete.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_IsOperationComplete(void);


/*******************************************************************************
* Function Name: Cy_Flash_StartWrite
****************************************************************************//**
*
* Starts programming the flash row with
* the input data. Returns immediately and reports a successful start
* or reason for failure. Reports a \ref CY_FLASH_DRV_IPC_BUSY error
* in the case when another process is writing to flash. User
* firmware should not enter the Hibernate or Deep-Sleep mode until
* flash Write is complete. The Flash operation is allowed in Sleep mode.
* During the flash operation, the device should not be reset, including the
* XRES pin, a software reset, and watchdog reset sources. Also, the low-voltage
* detect circuits should be configured to generate an interrupt instead of a reset.
* Otherwise, portions of flash may undergo unexpected changes.
* \note Before reading data from previously programmed/erased flash rows, the
* user must clear the flash cache with the Cy_SysLib_ClearFlashCacheAndBuffer()
* function.
* \note This is added as backword compatibility function in CAT1C devices.
* This function will not erase the row before writing to the row. Erase ROW is not supported in CAT1C devices.
* User can use \ref Cy_Flash_EraseSector or  Cy_Flash_EraseAll functions.
* \note  A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring flash sector where the flash Write, Erase, or
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation,
* use Cy_Flash_IsOperationComplete() to ensure flash operation is complete.
*
* \note This is a non blocking function and will not wait until the Write operation is complete.
*
* \note User needs to make sure that the data pointer passed to this function points to 32 byte aligned data for CAT1C devices.
*
* \param rowAddr Address of the flash row number.
* The Read-while-Write violation occurs when the flash read operation is
* initiated in the same flash sector where the flash write operation is
* performing. Refer to the device datasheet for the details.
* Address must match row start address.
*
* \param data The pointer to the data to be written to flash. The size
* of the data array must be equal to the flash row size. The flash row size for
* the selected device is defined by the \ref CY_FLASH_SIZEOF_ROW macro. Refer to
* the device datasheet for the details.
* For CAT1C devices this data pointer needs to point to 32 byte aligned data.
*
* \return Returns the status of the Flash operation,
* returns CY_FLASH_DRV_OPERATION_STARTED if operation starts with out error.
* see \ref cy_en_flashdrv_status_t.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_StartWrite(uint32_t rowAddr, const uint32_t* data);

/*******************************************************************************
* Function Name: Cy_Flash_StartEraseSector
****************************************************************************//**
*
* Starts erasing a sector of flash. Returns immediately
* and reports a successful start or reason for failure.
* Reports a \ref CY_FLASH_DRV_IPC_BUSY error in the case when IPC structure is locked
* by another process. User firmware should not enter the Hibernate or Deep Sleep mode until
* flash Erase is complete. The Flash operation is allowed in Sleep mode.
* During the flash operation, the device should not be reset, including the
* XRES pin, a software reset, and watchdog reset sources. Also, the low-voltage
* detect circuits should be configured to generate an interrupt instead of a reset.
* Otherwise, portions of flash may undergo unexpected changes.
* \note Before reading data from previously programmed/erased flash rows, the
* user must clear the flash cache with the Cy_SysLib_ClearFlashCacheAndBuffer()
* function.
* \note  A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring flash sector where the flash Write, Erase, or
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation,
* use Cy_Flash_IsOperationComplete() to ensure flash operation is complete.
*
* \note This is a non blocking function and will not wait until the operation is complete.
*
* \param sectorAddr Address of the flash row number.
* The Read-while-Write violation occurs when the flash read operation is
* initiated in the same flash sector where the flash erase operation is
* performing. Refer to the device datasheet for the details.
* Address must match row start address.
*
* \return Returns the status of the Flash operation,
* returns CY_FLASH_DRV_OPERATION_STARTED if operation starts with out error.
* see \ref cy_en_flashdrv_status_t.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_StartEraseSector(uint32_t sectorAddr);

/*******************************************************************************
* Function Name: Cy_Flash_ProgramRow
****************************************************************************//**
*
* This function writes an array of data to a single row of flash. Reports
* success or a reason for failure. Does not return until the Program operation
* is complete.
* Returns immediately and reports a \ref CY_FLASH_DRV_IPC_BUSY error in the case
* when another process is writing to flash. User firmware should not enter the
* Hibernate or Deep-sleep mode until flash Write is complete. The Flash operation
* is allowed in Sleep mode. During the Flash operation, the device should not be
* reset, including the XRES pin, a software reset, and watchdog reset sources.
* Also, low-voltage detect circuits should be configured to generate an interrupt
* instead of a reset. Otherwise, portions of flash may undergo unexpected
* changes.\n
* Before calling this function, the target flash region must be erased by
* the StartErase/EraseRow function.\n
* Data to be programmed must be located in the SRAM memory region.
* \note Before reading data from previously programmed/erased flash rows, the
* user must clear the flash cache with the Cy_SysLib_ClearFlashCacheAndBuffer()
* function.
* \note  A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring flash sector where the flash Write, Erase, or
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation,
* use Cy_Flash_IsOperationComplete() to ensure flash operation is complete.
*
* \note This is a blocking function and will not return until the Write operation is complete.
*
* \note User needs to make sure that the data pointer passed to this function points to 32 byte aligned data for CAT1C devices.
*
* \param rowAddr Address of the flash row number.
* The Read-while-Write violation occurs when the flash read operation is
* initiated in the same flash sector where the flash write operation is
* performing. Refer to the device datasheet for the details.
* Address must match row start address.
*
* \param data The pointer to the data which has to be written to flash. The size
* of the data array must be equal to the flash row size. The flash row size for
* the selected device is defined by the \ref CY_FLASH_SIZEOF_ROW macro. Refer to
* the device datasheet for the details.
* For CAT1C devices this data pointer needs to point to 32 byte aligned data.
*
* \return Returns the status of the Flash operation,
* see \ref cy_en_flashdrv_status_t.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_ProgramRow(uint32_t rowAddr, const uint32_t* data);

/*******************************************************************************
* Function Name: Cy_Flash_EraseSector
****************************************************************************//**
*
* This function erases a sector of flash. Reports success or
* a reason for failure. Does not return until the Erase operation is
* complete. Returns immediately and reports a \ref CY_FLASH_DRV_IPC_BUSY error in
* the case when another process is writing to flash or erasing the row.
* User firmware should not enter the Hibernate or Deep Sleep mode until flash Erase
* is complete. The Flash operation is allowed in Sleep mode.
* During the Flash operation, the device should not be reset, including the
* XRES pin, a software reset, and watchdog reset sources. Also, low-voltage
* detect circuits should be configured to generate an interrupt instead of a
* reset. Otherwise, portions of flash may undergo unexpected changes.
*
* \note  A Read while Write violation occurs when a flash Read operation is initiated
* in the same or neighboring flash sector where the flash Write, Erase, or
* Program operation is working. This violation may cause a HardFault exception.
* To avoid the Read while Write violation,
* use Cy_Flash_IsOperationComplete() to ensure flash operation is complete.
*
* \note This is a blocking function and will not return until the erase operation is complete.
*
* \param sectorAddr Address of the flash row number.
* The Read-while-Write violation occurs when the flash read operation is
* initiated in the same flash sector where the flash write operation is
* performing. Refer to the device datasheet for the details.
* Address must match row start address.
*
* \return Returns the status of the Flash operation,
* see \ref cy_en_flashdrv_status_t.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_EraseSector(uint32_t sectorAddr);

/*******************************************************************************
* Function Name: Cy_Flash_CalculateHash
****************************************************************************//**
*
* Returns a hash value of the specified region of flash.
*
* \param data Start the data address.
*
* \param numberOfBytes The hash value is calculated for the number of bytes after the
* start data address (0 - 1 byte, 1- 2 bytes etc).
*
* \param hashPtr The pointer to the address where hash is to be stored
*
* \return Returns the status of the Flash operation.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_CalculateHash(const uint32_t* data, uint32_t numberOfBytes, uint32_t* hashPtr);

/*******************************************************************************
* Function Name: Cy_Flash_RowChecksum
****************************************************************************//**
*
* Returns a checksum value of the specified flash row.
*
* \note Now Cy_Flash_RowChecksum() requires the row <b>address</b> (rowAddr)
*       as a parameter. In previous versions of the driver, this function used
*       the row <b>number</b> (rowNum) for this parameter.
*
* \param rowAddr The address of the flash row.
*
* \param checksumPtr The pointer to the address where checksum is to be stored
*
* \return Returns the status of the Flash operation.
*
*******************************************************************************/
cy_en_flashdrv_status_t Cy_Flash_RowChecksum(uint32_t rowAddr, uint32_t* checksumPtr);

/*******************************************************************************
* Function Name: Cy_Flash_Init
****************************************************************************//**
*
* Initiates all needed prerequisites to support flash erase/write.
* Should be called from each core.
*
* Requires a call to Cy_IPC_Sema_Init(), Cy_IPC_Pipe_Config() and
* Cy_IPC_Pipe_Init() functions before use for CAT1A devices.
*
* This function is called in the SystemInit() function, for proper flash write
* and erase operations. If the default startup file is not used, or the function
* SystemInit() is not called in your project, ensure to perform the following steps
* before any flash or EmEEPROM write/erase operations:
* \snippet flash/snippet/main.c Flash Initialization
*
*******************************************************************************/
void Cy_Flash_Init(void);

/** \} group_flash_functions */

/** \cond INTERNAL */

/*******************************************************************************
Backward compatibility macro. The following code is DEPRECATED and must
not be used in new projects
*******************************************************************************/

#define     Cy_Flash_IsWriteComplete(...)    Cy_Flash_IsOperationComplete()
#define     Cy_Flash_IsProgramComplete(...)  Cy_Flash_IsOperationComplete()
#define     Cy_Flash_IsEraseComplete(...)    Cy_Flash_IsOperationComplete()
/** \endcond */


#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_M4CPUSS || CY_IP_M7CPUSS*/

#endif /* #if !defined (CY_FLASH_H) */

/** \} group_flash */


/* [] END OF FILE */
