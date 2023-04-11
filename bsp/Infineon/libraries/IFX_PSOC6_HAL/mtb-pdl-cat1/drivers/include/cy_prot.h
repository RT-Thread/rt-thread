/***************************************************************************//**
* \file cy_prot.h
* \version 1.80
*
* \brief
* Provides an API declaration of the Protection Unit driver
*
********************************************************************************
* \copyright
* Copyright (c) (2016-2022), Cypress Semiconductor Corporation
* (an Infineon company) or an affiliate of Cypress Semiconductor Corporation.
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

/**
* \addtogroup group_prot
* \{
*
* The Protection Unit driver provides an API to configure the Memory Protection
* Units (MPU), Shared Memory Protection Units (SMPU), and Peripheral Protection
* Units (PPU). These are separate from the ARM Core MPUs and provide additional
* mechanisms for securing resource accesses. The Protection units address the
* following concerns in an embedded design:
* - <b>Security requirements:</b> This includes the prevention of malicious attacks
*   to access secure memory or peripherals.
* - <b>Safety requirements:</b> This includes detection of accidental (non-malicious)
*   SW errors and random HW errors. It is important to enable failure analysis
*   to investigate the root cause of a safety violation.
*
* The functions and other declarations used in this driver are in cy_prot.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* \section group_prot_protection_type Protection Types
*
* Protection units are hardware configuration structures that control bus accesses
* to the resources that they protect. By combining these individual configuration
* structures, a system is built to allow strict restrictions on the capabilities
* of individual bus masters (e.g. CM0+, CM4, Crypt) and their operating modes.
* This architecture can then be integrated into the overall security system
* of the end application. To build this system, 3 main protection unit types
* are available; MPU, SMPU and PPU. When a resource is accessed (memory/register),
* it must pass the evaluation performed for each category. These access evaluations
* are prioritized, where MPU has the highest priority, followed by SMPU, followed
* by PPU. i.e. if an SMPU and a PPU protect the same resource and if access is
* denied by the SMPU, then the PPU access evaluation is skipped. This can lead to a
* denial-of-service scenario and the application should pay special attention in
* taking ownership of the protection unit configurations.
*
* \subsection group_prot_memory_protection Memory Protection
*
* Memory access control for a bus master is controlled using an MPU. These are
* most often used to distinguish user and privileged accesses from a single bus
* master such as task switching in an OS/kernel. For ARM cores (CM0+, CM4), the
* core MPUs are used to perform this task. For other non-ARM bus masters such
* as Crypto, MPU structs are available, which can be used in a similar manner
* as the ARM core MPUs. These MPUs however must be configured by the ARM cores.
* Other bus masters that do not have an MPU, such as DMA (DW), inherit the access
* control attributes of the bus master that configured the channel. Also note
* that unlike other protection units, MPUs do not support protection context
* evaluation. MPU structs have a descending priority, where larger index struct
* has higher priority access evaluation over lower index structs. E.g. MPU_STRUCT15
* has higher priority than MPU_STRUCT14 and its access will be evaluated before
* MPU_STRUCT14. If both target the same memory, then the higher index (MPU_STRUCT15)
* will be used, and the lower index (MPU_STRUCT14) will be ignored.
*
* \subsection group_prot_shared_memory_protection Shared Memory Protection
*
* In order to protect a region of memory from all bus masters, an SMPU is used.
* This protection effectively allows only those with correct bus master access
* settings to read/write/execute the memory region. This type of protection
* is used in general memory such as Flash and SRAM. Peripheral registers are
* best configured using the peripheral protection units instead. SMPU structs
* have a descending priority, where larger index struct has higher priority
* access evaluation over lower index structs. E.g. SMPU_STRUCT15 has higher priority
* than SMPU_STRUCT14 and its access will be evaluated before SMPU_STRUCT14.
* If both target the same memory, then the higher index (MPU_STRUCT15) will be
* used, and the lower index (SMPU_STRUCT14) will be ignored.
*
* \subsection group_prot_peripheral_protection Peripheral Protection
*
* Peripheral protection is provided by PPUs and allow control of peripheral
* register accesses by bus masters. Four types of PPUs are available.
* - <b>Fixed Group (GR) PPUs</b> are used to protect an entire peripheral MMIO group
*   from invalid bus master accesses. The MMIO grouping information and which
*   resource belongs to which group is device specific and can be obtained
*   from the device technical reference manual (TRM). Group PPUs have the highest
*   priority in the PPU category. Therefore their access evaluations take precedence
*   over the other types of PPUs.
* - <b>Programmable (PROG) PPUs</b> are used to protect any peripheral memory region
*   in a device from invalid bus master accesses. It is the most versatile
*   type of peripheral protection unit. Programmable PPUs have the second highest
*   priority and take precedence over Region PPUs and Slave PPUs. Similar to SMPUs,
*   higher index PROG PPUs have higher priority than lower indexes PROG PPUs.
* - <b>Fixed Region (RG) PPUs</b> are used to protect an entire peripheral slave
*   instance from invalid bus master accesses. For example, TCPWM0, TCPWM1,
*   SCB0, and SCB1, etc. Region PPUs have the third highest priority and take precedence
*   over Slave PPUs.
* - <b>Fixed Slave (SL) PPUs</b> are used to protect specified regions of peripheral
*   instances. For example, individual DW channel structs, SMPU structs, and
*   IPC structs, etc. Slave PPUs have the lowest priority in the PPU category and
*   therefore are evaluated last.
*
* \section group_prot_protection_context Protection Context
*
* Protection context (PC) attribute is present in all bus masters and is evaluated
* when accessing memory protected by an SMPU or a PPU. There are no limitations
* to how the PC values are allocated to the bus masters and this makes it
* possible for multiple bus masters to essentially share protection context
* values. The exception to this rule is the PC value 0.
*
* \subsection group_prot_pc0 PC=0
*
* Protection context 0 is a hardware controlled protection context update
* mechanism that allows only a single entry point for transitioning into PC=0
* value. This mechanism is only present for the secure CM0+ core and is a
* fundamental feature in defining a security solution. While all bus masters
* are configured to PC=0 at device boot, it is up to the security solution
* to transition these bus masters to PC!=0 values. Once this is done, those
* bus masters can no longer revert back to PC=0 and can no longer access
* resources protected at PC=0.
*
* In order to enter PC=0, the CM0+ core must assign an interrupt vector or
* an exception handler address to the CPUSS.CM0_PC0_HANDLER register. This
* allows the hardware to check whether the executing code address matches the
* value in this register. If they match, the current PC value is saved and
* the CM0+ bus master automatically transitions to PC=0. It is then up to
* the executing code to decide if and when it will revert to a PC!=0 value.
* At that point, the only way to re-transition to PC=0 is through the defined
* exception/interrupt handler.
*
* \note Devices with CPUSS ver_2 have a hardware-controlled protection context
* update mechanism that allows only a single-entry point for transitioning
* into PC=0, 1, 2, and 3. The interrupt vector or the exception handler
* address can be assigned to the CPUSS.CM0_PC0_HANDLER, CPUSS.CM0_PC1_HANDLER,
* CPUSS.CM0_PC2_HANDLER or CPUSS.CM0_PC2_HANDLER register. Also, the control
* register CPUSS.CM0_PC_CTL of the CM0+ protection context must be set:
* bit 0 - the valid field for CM0_PC0_HANDLER,
* bit 1 - the valid field for CM0_PC1_HANDLER,
* bit 2 - the valid field for CM0_PC2_HANDLER,
* and bit 3 - the valid field for CM0_PC3_HANDLER.
*
* The example of using of the single entry point mechanism is shown below.
* \snippet prot/snippet/main.c snippet_Cy_Prot_ProtectionContext
*
* \section group_prot_access_evaluation Access Evaluation
*
* Each protection unit is capable of evaluating several access types. These can
* be used to build a system of logical evaluations for different kinds of
* bus master modes of operations. These access types can be divided into
* three broad access categories.
*
* - <b>User/Privileged access:</b> The ARM convention of user mode versus privileged
*   mode is applied in the protection units. For ARM cores, switching between
*   user and privileged modes is handled by updating its Control register or
*   by exception entries. Other bus masters such as Crypto have their own
*   user/privileged settings bit in the bus master control register. This is
*   then controlled by the ARM cores. Bus masters that do not have
*   user/privileged access controls, such as DMA, inherit their attributes
*   from the bus master that configured it. The user/privileged distinction
*   is used mainly in the MPUs for single bus master accesses but they can
*   also be used in all other protection units.
* - <b>Secure/Non-secure access:</b> The secure/non-secure attribute is another
*   identifier to distinguish between two separate modes of operations. Much
*   like the user/privileged access, the secure/non-secure mode flag is present
*   in the bus master control register. The ARM core does not have this
*   attribute in its control register and must use the bus master control
*   register instead. Bus masters that inherit their attributes, such as DMA,
*   inherit the secure/non-secure attribute. The primary use-case for this
*   access evaluation is to define a region to be secure or non-secure using
*   an SMPU or a PPU. A bus master with a secure attribute can access
*   both secure and non-secure regions, whereas a bus master with non-secure
*   attribute can only access non-secure regions.
* - <b>Protection Context access:</b> Protection Context is an attribute
*   that serves two purposes; To enter the hardware controlled secure PC=0
*   mode of operation from non-secure modes and to provide finer granularity
*   to the bus master access definitions. It is used in SMPU and PPU configuration
*   to control which bus master protection context can access the resources
*   that they protect.
*
* \section group_prot_protection_structure Protection Structure
*
* Each protection unit is comprised of a master struct and a slave struct pair.
* The exception to this rule is MPU structs, which only have the slave struct
* equivalent. The protection units apply their access evaluations in a decreasing
* index order. For example, if SMPU1 and SMPU2 both protect a specific memory region,
* the the higher index (SMPU2) will be evaluated first. In a secure system, the
* higher index protection structs would then provide the high level of security
* and the lower indexes would provide the lower level of security. Refer to the
* \ref group_prot_protection_type section for more information.
*
* \subsection group_prot_slave_struct Slave Struct
*
* The slave struct is used to configure the protection settings for the resource
* of interest (memory/registers). Depending on the type of protection unit,
* the available attributes differ. However all Slave protection units have the
* following general format.
*
* \subsubsection group_prot_slave_addr Slave Struct Address Definition
*
* - Address: For MPU, SMPU and PROG PPU, the address field is used to define
*   the base memory region to apply the protection. This field has a dependency
*   on the region size, which dictates the alignment of the protection unit. E.g.
*   if the region size is 64KB, the address field is aligned to 64KB. Hence
*   the lowest bits [15:0] are ignored. For instance, if the address is defined
*   at 0x0800FFFF, the protection unit would apply its protection settings from
*   0x08000000. Thus alignment must be checked before defining the protection
*   address. The address field for other PPUs are not used, as they are bound
*   to their respective peripheral memory locations.
* - Region Size: For MPU, SMPU and PROG PPU, the region size is used to define
*   the memory block size to apply the protection settings, starting from the
*   defined base address. It is also used to define the 8 sub-regions for the
*   chosen memory block. E.g. If the region size is 64KB, each subregion would
*   be 8KB. This information can then be used to disable the protection
*   settings for select subregions, which gives finer granularity to the
*   memory regions. PPUs do not have region size definitions as they are bound
*   to their respective peripheral memory locations.
* - Subregions: The memory block defined by the address and region size fields
*   is divided into 8 (0 to 7) equally spaced subregions. The protection settings
*   of the protection unit can be disabled for these subregions. E.g. for a
*   given 64KB of memory block starting from address 0x08000000, disabling
*   subregion 0 would result in the protection settings not affecting the memory
*   located between 0x08000000 to 0x08001FFF. PPUs do not have subregion
*   definitions as they are bound to their respective peripheral memory locations.
*
* \subsubsection group_prot_slave_attr Slave Struct Attribute Definition
*
* - User Permission: Protection units can control the access restrictions
*   of the read (R), write (W) and execute (X) (subject to their availability
*   depending on the type of protection unit) operations on the memory block
*   when the bus master is operating in user mode. PPU structs do not provide
*   execute attributes.
* - Privileged Permission: Similar to the user permission, protection units can
*   control the access restrictions of the read (R), write (W) and execute (X)
*   (subject to their availability depending on the type of protection unit)
*   operations on the memory block when the bus master is operating in
*   privileged mode. PPU structs do not provide execute attributes.
* - Secure/Non-secure: Applies the secure/non-secure protection settings to
*   the defined memory region. Secure protection allows only bus masters that
*   access the memory with secure attribute. Non-secure protection allows
*   bus masters that have either secure or non-secure attributes.
* - PC match: This attribute allows the protection unit to either apply the
*   3 access evaluations (user/privileged, secure/non-secure, protection context)
*   or to only provide an address range match. This is useful when multiple
*   protection units protect an overlapping memory region and it's desirable
*   to only have access evaluations applied from only one of these protection
*   units. For example, SMPU1 protects memory A and SMPU2 protects memory B.
*   There exists a region where A and B intersect and this is accessed by a
*   bus master. Both SMPU1 and SMPU2 are configured to operate in "match" mode.
*   In this scenario, the access evaluation will only be applied by the higher
*   index protection unit (i.e. SMPU2) and the access attributes of SMPU1 will
*   be ignored. If the bus master then tries to access a memory region A (that
*   does not intersect with B), the access evaluation from SMPU1 will be used.
*   Note that the PC match functionality is only available in SMPUs.
* - PC mask: Defines the allowed protection context values that can access the
*   protected memory. The bus master attribute must be operating in one of the
*   protection context values allowed by the protection unit. E.g. If SMPU1 is
*   configured to allow only PC=1 and PC=5, a bus master (such as CM4) must
*   be operating at PC=1 or PC=5 when accessing the protected memory region.
*
* \subsection group_prot_master_struct Master Struct
*
* The master struct protects its slave struct in the protection unit. This
* architecture makes possible for the slave configuration to be protected from
* reconfiguration by an unauthorized bus master. The configuration attributes
* and the format are similar to that of the slave structs.
*
* \subsubsection group_prot_master_addr Master Struct Address Definition
*
* - Address: The address definition for master struct is fixed to the slave
*   struct that it protects.
* - Region Size: The region size is fixed to 256B region.
* - Subregion: This value is fixed to only enable the first 64B subregions,
*   which applies the protection settings to the entire protection unit.
*
* \subsubsection group_prot_master_attr Master Struct Attribute Definition
*
* - User Permission: Only the write (W) access attribute is allowed for
*   master structs, which controls whether a bus master operating in user
*   mode has the write access.
* - Privileged Permission: Only the write (W) access attribute is allowed for
*   master structs, which controls whether a bus master operating in privileged
*   mode has the write access.
* - Secure/Non-Secure: Same behavior as slave struct.
* - PC match: Same behavior as slave struct.
* - PC mask: Same behavior as slave struct.
*
* \section group_prot_driver_usage Driver Usage
*
* Setting up and using protection units can be summed up in four stages:
*
* - Configure the bus master attributes. This defines the capabilities of
*   the bus master when trying to access the protected resources.
* - Configure the slave struct of a given protection unit. This defines
*   the protection attributes to be applied to the bus master accessing
*   the protected resource and also defines the size and location of the
*   memory block to protect.
* - Configure the master struct of the protection unit. This defines the
*   attributes to be checked against the bus master that is trying to
*   reconfigure the slave struct.
* - Set the active PC value of the bus master and place it in the correct
*   mode of operation (user/privileged, secure/non-secure). Then access
*   the protected memory.
*
* For example, by configuring the CM0+ bus master configuration to allow
* only protection contexts 2 and 3, the bus master will be able to
* set its protection context only to 2 or 3. During runtime, the CM0+ core
* can set its protection context to 2 by calling Cy_Prot_SetActivePC()
* and access all regions of protected memory that allow PC=2. A fault will
* be triggered if a resource is protected with different protection settings.
*
* Note that each protection unit is distinguished by its type (e.g.
* PROT_MPU_MPU_STRUCT_Type). The list of supported protection units can be
* obtained from the device definition header file. Choose a protection unit
* of interest, and call its corresponding Cy_Prot_Config<X>Struct() function
* with its software protection unit configuration structure populated. Then
* enable the protection unit by calling the Cy_Prot_Enable<X>Struct() function.
*
* Note that the bus master ID (en_prot_master_t) is defined in the device
* config header file.
*
* \section group_prot_configuration Configuration Considerations
*
* When a resource (memory/register) is accessed, it must pass evaluation of
* all three protection unit categories in the following order: MPU->SMPU->PPU.
* The application should ensure that a denial-of-service attack cannot be
* made on the PPU by the SMPU. For this reason, it is recommended that the
* application's security policy limit the ability for the non-secure client
* from configuring the SMPUs.
*
* Within each category, the priority hierarchy must be carefully considered
* to ensure that a higher priority protection unit cannot be configured to
* override the security configuration of a lower index protection unit.
* Therefore if a lower index protection unit is configured, relevant higher
* priority indexes should be configured (or protected from unwanted
* reconfiguration). E.g. If a PPU_SL is configured, PPU_RG and PPU_GR that
* overlaps with the protected registers should also be configured. SImilar
* to SMPUs, it is recommended that the configuration of PPU_PROG be limited.
* Otherwise they can be used to override the protection settings of PPU_RG
* and PPU_SL structs.
*
* All bus masters are set to PC=0 value at device reset and therefore have full
* access to all resources. It is up to the security solution to implement
* what privileges each bus master has. Once transitioned to a PC!=0 value,
* only the CM0+ core is capable of re-entering the PC=0 via the user-defined
* exception entry in the CPUSS.CM0_PC0_HANDLER register.
*
* - SMPU 15 and 14 are configured and enabled to only allow PC=0 accesses at
*   device boot.
* - PROG PPU 15, 14, 13 and 12 are configured to only allow PC=0 accesses at
*   device boot.
* - GR PPU 0 and 2 are configured to only allow PC=0 accesses at device boot.
*
* \section group_prot_more_information More Information
*
* Refer to Technical Reference Manual (TRM) and the device datasheet.
*
* \section group_prot_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.80</td>
*     <td>\ref Cy_Prot_ConfigPpuProgSlaveAddr(), \ref Cy_Prot_EnablePpuProgSlaveRegion() \ref Cy_Prot_DisablePpuProgSlaveRegion()
*         APIs are only available for PSoC6 devices</td>
*     <td>MISRA C-2012 compliance and Move PERI version-1 APIs to supported devices</td>
*   </tr>
*   <tr>
*     <td>1.70</td>
*     <td> Added support for CAT1C devices. </td>
*     <td> New device added. </td>
*   </tr>
*   <tr>
*     <td>1.60</td>
*     <td>Modified \ref Cy_Prot_ConfigPpuProgMasterAtt() & \ref Cy_Prot_ConfigPpuFixedMasterAtt()
*         functions to ignore unavailable protection context.</td>
*     <td>Defect fix.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">1.50</td>
*     <td>Updated implementation of the \ref Cy_Prot_ConfigPpuProgMasterAtt(),
*         \ref Cy_Prot_ConfigPpuProgSlaveAtt(), \ref Cy_Prot_ConfigPpuFixedMasterAtt(),
*         and \ref Cy_Prot_ConfigPpuFixedSlaveAtt() to start registers update from
*         the higher-numbered PCs in order to prevent lockup for the case when registers
*         are configured to read-only.</td>
*     <td>Defect fix.</td>
*   </tr>
*   <tr>
*     <td>Added macros for memory region size setting in \ref cy_en_prot_size_t initialization.</td>
*     <td>The macros can be useful for the pre-processor checks.</td>
*   </tr>
*   <tr>
*     <td>Fixed/Documented MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>1.40</td>
*     <td>
*         - Updated the \ref Cy_Prot_SetActivePC() function to report an error when called
*         on the secure CYB06xx7 devices as no access privileges are available.
*         - Updated the \ref Cy_Prot_GetActivePC() function for the secure CYB06xx7
*         devices to access the protected registers via the \ref group_pra driver.
*    </td>
*     <td>Added PSoC 64 devices support.</td>
*   </tr>
*   <tr>
*     <td>1.30.3</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.30.2</td>
*     <td>Clarified the description of the next API functions: \ref Cy_Prot_ConfigPpuProgMasterAtt,\n
*         \ref Cy_Prot_ConfigPpuProgSlaveAtt, \ref Cy_Prot_ConfigPpuFixedMasterAtt, \ref Cy_Prot_ConfigPpuFixedSlaveAtt.</td>
*     <td>API enhancement based on usability feedback.</td>
*   </tr>
*   <tr>
*     <td>1.30.1</td>
*     <td>Snippet updated.</td>
*     <td>Old snippet outdated.</td>
*   </tr>
*   <tr>
*     <td>1.30</td>
*     <td>Defect in \ref Cy_Prot_GetPpuProgStruct() function due to faulty defines is fixed.</td>
*     <td>Defect fixing.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">1.20</td>
*     <td>Flattened the organization of the driver source code into the single
*         source directory and the single include directory.</td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td>Added functions for CPUSS ver_2:
*         - \ref Cy_Prot_ConfigPpuProgMasterAtt()
*         - \ref Cy_Prot_ConfigPpuProgSlaveAddr()
*         - \ref Cy_Prot_ConfigPpuProgSlaveAtt()
*         - \ref Cy_Prot_EnablePpuProgSlaveRegion()
*         - \ref Cy_Prot_DisablePpuProgSlaveRegion()
*         - \ref Cy_Prot_ConfigPpuFixedMasterAtt()
*         - \ref Cy_Prot_ConfigPpuFixedSlaveAtt()
*     </td>
*     <td>Added support for CPUSS ver_2.</td>
*   </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using dereferenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">1.10</td>
*     <td>Added input parameter validation to the API functions.<br>
*     cy_en_prot_pcmask_t, cy_en_prot_subreg_t and cy_en_prot_pc_t
*     types are set to typedef enum</td>
*     <td>Improved debugging capability</td>
*   </tr>
*   <tr>
*     <td>Expanded documentation</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_prot_macros Macros
* \defgroup group_prot_functions Functions
* \{
*   \defgroup group_prot_functions_busmaster    Bus Master and PC Functions
*   \defgroup group_prot_functions_mpu          MPU Functions
*   \defgroup group_prot_functions_smpu         SMPU Functions
*   \defgroup group_prot_functions_ppu_prog_v2  PPU Programmable (PROG) v2 Functions
*   \defgroup group_prot_functions_ppu_fixed_v2 PPU Fixed (FIXED) v2 Functions
*   \defgroup group_prot_functions_ppu_prog     PPU Programmable (PROG) v1 Functions
*   \defgroup group_prot_functions_ppu_gr       PPU Group (GR) v1 Functions
*   \defgroup group_prot_functions_ppu_sl       PPU Slave (SL) v1 Functions
*   \defgroup group_prot_functions_ppu_rg       PPU Region (RG) v1 Functions
* \}
* \defgroup group_prot_data_structures Data Structures
* \defgroup group_prot_enums Enumerated Types
*/

#if !defined (CY_CY_PROT_PDL_H)
#define CY_CY_PROT_PDL_H

#include "cy_device.h"

#if defined (CY_IP_M4CPUSS) || defined (CY_IP_M7CPUSS)

#include <stdbool.h>
#include <stddef.h>
#include "cy_device_headers.h"
#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_prot_macros
* \{
*/

/** Driver major version */
#define CY_PROT_DRV_VERSION_MAJOR       1

/** Driver minor version */
#define CY_PROT_DRV_VERSION_MINOR       70

/** Prot driver ID */
#define CY_PROT_ID                      (CY_PDL_DRV_ID(0x30U))

/** \} group_prot_macros */

/**
* \addtogroup group_prot_enums
* \{
*/

/**
* Prot Driver error codes
*/
typedef enum
{
    CY_PROT_SUCCESS       = 0x00U,                                    /**< Returned successful */
    CY_PROT_BAD_PARAM     = CY_PROT_ID | CY_PDL_STATUS_ERROR | 0x01U, /**< Bad parameter was passed */
    CY_PROT_INVALID_STATE = CY_PROT_ID | CY_PDL_STATUS_ERROR | 0x02U, /**< The operation is not setup */
    CY_PROT_FAILURE       = CY_PROT_ID | CY_PDL_STATUS_ERROR | 0x03U, /**< The resource is locked */
    CY_PROT_UNAVAILABLE   = CY_PROT_ID | CY_PDL_STATUS_ERROR | 0x04U  /**< The resource is unavailable */
} cy_en_prot_status_t;

/**
* User/Privileged permission
*/
typedef enum
{
    CY_PROT_PERM_DISABLED = 0x00U, /**< Read, Write and Execute disabled */
    CY_PROT_PERM_R        = 0x01U, /**< Read enabled */
    CY_PROT_PERM_W        = 0x02U, /**< Write enabled */
    CY_PROT_PERM_RW       = 0x03U, /**< Read and Write enabled */
    CY_PROT_PERM_X        = 0x04U, /**< Execute enabled */
    CY_PROT_PERM_RX       = 0x05U, /**< Read and Execute enabled */
    CY_PROT_PERM_WX       = 0x06U, /**< Write and Execute enabled */
    CY_PROT_PERM_RWX      = 0x07U  /**< Read, Write and Execute enabled */
}cy_en_prot_perm_t;

/**
* Constants for memory region size setting.
* These may be useful for pre-processor-time tests.
*/
#define PROT_SIZE_4B_BIT_SHIFT      1U   /**< 4 bytes */
#define PROT_SIZE_8B_BIT_SHIFT      2U   /**< 8 bytes */
#define PROT_SIZE_16B_BIT_SHIFT     3U   /**< 16 bytes */
#define PROT_SIZE_32B_BIT_SHIFT     4U   /**< 32 bytes */
#define PROT_SIZE_64B_BIT_SHIFT     5U   /**< 64 bytes */
#define PROT_SIZE_128B_BIT_SHIFT    6U   /**< 128 bytes */
#define PROT_SIZE_256B_BIT_SHIFT    7U   /**< 256 bytes */
#define PROT_SIZE_512B_BIT_SHIFT    8U   /**< 512 bytes */

#define PROT_SIZE_1KB_BIT_SHIFT     9U   /**< 1 Kilobyte */
#define PROT_SIZE_2KB_BIT_SHIFT     10U  /**< 2 Kilobytes */
#define PROT_SIZE_4KB_BIT_SHIFT     11U  /**< 4 Kilobytes */
#define PROT_SIZE_8KB_BIT_SHIFT     12U  /**< 8 Kilobytes */
#define PROT_SIZE_16KB_BIT_SHIFT    13U  /**< 16 Kilobytes */
#define PROT_SIZE_32KB_BIT_SHIFT    14U  /**< 32 Kilobytes */
#define PROT_SIZE_64KB_BIT_SHIFT    15U  /**< 64 Kilobytes */
#define PROT_SIZE_128KB_BIT_SHIFT   16U  /**< 128 Kilobytes */
#define PROT_SIZE_256KB_BIT_SHIFT   17U  /**< 256 Kilobytes */
#define PROT_SIZE_512KB_BIT_SHIFT   18U  /**< 512 Kilobytes */

#define PROT_SIZE_1MB_BIT_SHIFT     19U  /**< 1 Megabyte */
#define PROT_SIZE_2MB_BIT_SHIFT     20U  /**< 2 Megabytes */
#define PROT_SIZE_4MB_BIT_SHIFT     21U  /**< 4 Megabytes */
#define PROT_SIZE_8MB_BIT_SHIFT     22U  /**< 8 Megabytes */
#define PROT_SIZE_16MB_BIT_SHIFT    23U  /**< 16 Megabytes */
#define PROT_SIZE_32MB_BIT_SHIFT    24U  /**< 32 Megabytes */
#define PROT_SIZE_64MB_BIT_SHIFT    25U  /**< 64 Megabytes */
#define PROT_SIZE_128MB_BIT_SHIFT   26U  /**< 128 Megabytes */
#define PROT_SIZE_256MB_BIT_SHIFT   27U  /**< 256 Megabytes */
#define PROT_SIZE_512MB_BIT_SHIFT   28U  /**< 512 Megabytes */

#define PROT_SIZE_1GB_BIT_SHIFT     29U  /**< 1 Gigabyte */
#define PROT_SIZE_2GB_BIT_SHIFT     30U  /**< 2 Gigabytes */
#define PROT_SIZE_4GB_BIT_SHIFT     31U  /**< 4 Gigabytes */

/**
* Memory region size
*/
typedef enum
{
    CY_PROT_SIZE_4B    = PROT_SIZE_4B_BIT_SHIFT,    /**< 4 bytes */
    CY_PROT_SIZE_8B    = PROT_SIZE_8B_BIT_SHIFT,    /**< 8 bytes */
    CY_PROT_SIZE_16B   = PROT_SIZE_16B_BIT_SHIFT,   /**< 16 bytes */
    CY_PROT_SIZE_32B   = PROT_SIZE_32B_BIT_SHIFT,   /**< 32 bytes */
    CY_PROT_SIZE_64B   = PROT_SIZE_64B_BIT_SHIFT,   /**< 64 bytes */
    CY_PROT_SIZE_128B  = PROT_SIZE_128B_BIT_SHIFT,  /**< 128 bytes */
    CY_PROT_SIZE_256B  = PROT_SIZE_256B_BIT_SHIFT,  /**< 256 bytes */
    CY_PROT_SIZE_512B  = PROT_SIZE_512B_BIT_SHIFT,  /**< 512 bytes */
    CY_PROT_SIZE_1KB   = PROT_SIZE_1KB_BIT_SHIFT,   /**< 1 Kilobyte */
    CY_PROT_SIZE_2KB   = PROT_SIZE_2KB_BIT_SHIFT,   /**< 2 Kilobytes */
    CY_PROT_SIZE_4KB   = PROT_SIZE_4KB_BIT_SHIFT,   /**< 4 Kilobytes */
    CY_PROT_SIZE_8KB   = PROT_SIZE_8KB_BIT_SHIFT,   /**< 8 Kilobytes */
    CY_PROT_SIZE_16KB  = PROT_SIZE_16KB_BIT_SHIFT,  /**< 16 Kilobytes */
    CY_PROT_SIZE_32KB  = PROT_SIZE_32KB_BIT_SHIFT,  /**< 32 Kilobytes */
    CY_PROT_SIZE_64KB  = PROT_SIZE_64KB_BIT_SHIFT,  /**< 64 Kilobytes */
    CY_PROT_SIZE_128KB = PROT_SIZE_128KB_BIT_SHIFT, /**< 128 Kilobytes */
    CY_PROT_SIZE_256KB = PROT_SIZE_256KB_BIT_SHIFT, /**< 256 Kilobytes */
    CY_PROT_SIZE_512KB = PROT_SIZE_512KB_BIT_SHIFT, /**< 512 Kilobytes */
    CY_PROT_SIZE_1MB   = PROT_SIZE_1MB_BIT_SHIFT,   /**< 1 Megabyte */
    CY_PROT_SIZE_2MB   = PROT_SIZE_2MB_BIT_SHIFT,   /**< 2 Megabytes */
    CY_PROT_SIZE_4MB   = PROT_SIZE_4MB_BIT_SHIFT,   /**< 4 Megabytes */
    CY_PROT_SIZE_8MB   = PROT_SIZE_8MB_BIT_SHIFT,   /**< 8 Megabytes */
    CY_PROT_SIZE_16MB  = PROT_SIZE_16MB_BIT_SHIFT,  /**< 16 Megabytes */
    CY_PROT_SIZE_32MB  = PROT_SIZE_32MB_BIT_SHIFT,  /**< 32 Megabytes */
    CY_PROT_SIZE_64MB  = PROT_SIZE_64MB_BIT_SHIFT,  /**< 64 Megabytes */
    CY_PROT_SIZE_128MB = PROT_SIZE_128MB_BIT_SHIFT, /**< 128 Megabytes */
    CY_PROT_SIZE_256MB = PROT_SIZE_256MB_BIT_SHIFT, /**< 256 Megabytes */
    CY_PROT_SIZE_512MB = PROT_SIZE_512MB_BIT_SHIFT, /**< 512 Megabytes */
    CY_PROT_SIZE_1GB   = PROT_SIZE_1GB_BIT_SHIFT,   /**< 1 Gigabyte */
    CY_PROT_SIZE_2GB   = PROT_SIZE_2GB_BIT_SHIFT,   /**< 2 Gigabytes */
    CY_PROT_SIZE_4GB   = PROT_SIZE_4GB_BIT_SHIFT    /**< 4 Gigabytes */
}cy_en_prot_size_t;

/**
* Protection Context (PC)
*/
enum cy_en_prot_pc_t
{
    CY_PROT_PC1  = 1U,  /**< PC = 1 */
    CY_PROT_PC2  = 2U,  /**< PC = 2 */
    CY_PROT_PC3  = 3U,  /**< PC = 3 */
    CY_PROT_PC4  = 4U,  /**< PC = 4 */
    CY_PROT_PC5  = 5U,  /**< PC = 5 */
    CY_PROT_PC6  = 6U,  /**< PC = 6 */
    CY_PROT_PC7  = 7U,  /**< PC = 7 */
    CY_PROT_PC8  = 8U,  /**< PC = 8 */
    CY_PROT_PC9  = 9U,  /**< PC = 9 */
    CY_PROT_PC10 = 10U, /**< PC = 10 */
    CY_PROT_PC11 = 11U, /**< PC = 11 */
    CY_PROT_PC12 = 12U, /**< PC = 12 */
    CY_PROT_PC13 = 13U, /**< PC = 13 */
    CY_PROT_PC14 = 14U, /**< PC = 14 */
    CY_PROT_PC15 = 15U  /**< PC = 15 */
};

/**
* Subregion disable (0-7)
*/
enum cy_en_prot_subreg_t
{
    CY_PROT_SUBREGION_DIS0 = 0x01U,  /**< Disable subregion 0 */
    CY_PROT_SUBREGION_DIS1 = 0x02U,  /**< Disable subregion 1 */
    CY_PROT_SUBREGION_DIS2 = 0x04U,  /**< Disable subregion 2 */
    CY_PROT_SUBREGION_DIS3 = 0x08U,  /**< Disable subregion 3 */
    CY_PROT_SUBREGION_DIS4 = 0x10U,  /**< Disable subregion 4 */
    CY_PROT_SUBREGION_DIS5 = 0x20U,  /**< Disable subregion 5 */
    CY_PROT_SUBREGION_DIS6 = 0x40U,  /**< Disable subregion 6 */
    CY_PROT_SUBREGION_DIS7 = 0x80U   /**< Disable subregion 7 */
};

/**
* Protection context mask (PC_MASK)
*/
enum cy_en_prot_pcmask_t
{
    CY_PROT_PCMASK1  = 0x0001U,  /**< Mask to allow PC = 1 */
    CY_PROT_PCMASK2  = 0x0002U,  /**< Mask to allow PC = 2 */
    CY_PROT_PCMASK3  = 0x0004U,  /**< Mask to allow PC = 3 */
    CY_PROT_PCMASK4  = 0x0008U,  /**< Mask to allow PC = 4 */
    CY_PROT_PCMASK5  = 0x0010U,  /**< Mask to allow PC = 5 */
    CY_PROT_PCMASK6  = 0x0020U,  /**< Mask to allow PC = 6 */
    CY_PROT_PCMASK7  = 0x0040U,  /**< Mask to allow PC = 7 */
    CY_PROT_PCMASK8  = 0x0080U,  /**< Mask to allow PC = 8 */
    CY_PROT_PCMASK9  = 0x0100U,  /**< Mask to allow PC = 9 */
    CY_PROT_PCMASK10 = 0x0200U,  /**< Mask to allow PC = 10 */
    CY_PROT_PCMASK11 = 0x0400U,  /**< Mask to allow PC = 11 */
    CY_PROT_PCMASK12 = 0x0800U,  /**< Mask to allow PC = 12 */
    CY_PROT_PCMASK13 = 0x1000U,  /**< Mask to allow PC = 13 */
    CY_PROT_PCMASK14 = 0x2000U,  /**< Mask to allow PC = 14 */
    CY_PROT_PCMASK15 = 0x4000U   /**< Mask to allow PC = 15 */
};

/**
* Request mode to get the SMPU or programmed PU structure
*/
typedef enum
{
    CY_PROT_REQMODE_HIGHPRIOR = 0U,    /**< Request mode to return PU structure with highest priority */
    CY_PROT_REQMODE_LOWPRIOR  = 1U,     /**< Request mode to return PU structure with lowest priority */
    CY_PROT_REQMODE_INDEX     = 2U       /**< Request mode to return PU structure with specific index */
}cy_en_prot_req_mode_t;

/** \} group_prot_enums */


/***************************************
*        Constants
***************************************/

/** \cond INTERNAL */

/* Number of SMPU structures with highest priority */
#define PROT_SMPU_STRUCT_WTH_HIGHEST_PR       (15)

/* Number of Programmable PPU structures with lowest priority */
#define PROT_PPU_PROG_STRUCT_WTH_LOWEST_PR    (15)

/* Define to check maximum value of active PC */
#define PROT_PC_MAX                       (16U)

/* Define to check maximum mask of PC */
#define PROT_PC_MASK_MAX                          (0x7FFFUL)

#if defined (CY_IP_MXPERI_VERSION) && (CY_IP_MXPERI_VERSION == 1U)
    typedef PERI_MS_PPU_PR_V2_Type PERI_MS_PPU_PR_Type;
    typedef PERI_MS_PPU_FX_V2_Type PERI_MS_PPU_FX_Type;
#endif /* defined (CY_IP_MXPERI_VERSION) && (CY_IP_MXPERI_VERSION == 1U) */

#if defined (CY_IP_MXPERI_VERSION) && (CY_IP_MXPERI_VERSION > 1U)
    #if defined (CY_IP_M4CPUSS)
        typedef PERI_PPU_PR_V1_Type PERI_PPU_PR_Type;
        typedef PERI_PPU_GR_V1_Type PERI_PPU_GR_Type;
        typedef PERI_GR_PPU_SL_V1_Type PERI_GR_PPU_SL_Type;
        typedef PERI_GR_PPU_RG_V1_Type PERI_GR_PPU_RG_Type;
    #else
        #define PERI_MS_PPU_PR_V2_MS_ATT0_PC0_NS_Msk PERI_MS_PPU_PR_MS_ATT0_PC0_NS_Msk
        #define PERI_MS_PPU_PR_V2_MS_ATT0_PC1_UR_Pos PERI_MS_PPU_PR_MS_ATT0_PC1_UR_Pos

    #endif
#endif /* defined (CY_IP_MXPERI_VERSION) && (CY_IP_MXPERI_VERSION > 1U) */


/* General Masks and shifts */
#define CY_PROT_MSX_CTL_SHIFT                   (0x02UL) /**< Shift for MSx_CTL register */
#define CY_PROT_STRUCT_ENABLE                   (0x01UL) /**< Enable protection unit struct */
#define CY_PROT_STRUCT_DISABLE                  (0x00UL) /**< Disable protection unit struct */
#define CY_PROT_ADDR_SHIFT                      (8UL)    /**< Address shift for MPU, SMPU and PROG PPU structs */
#define CY_PROT_PCMASK_CHECK                    (0x01UL) /**< Shift and mask for pcMask check */
#define CY_PROT_PCMASK_VALID                    ((0xFFFFUL) & (~(0xFFFFUL << PERI_PC_NR))) /**< Bitmask to mask pcMask for unavailable protection contexts */

/* Permission masks and shifts */
#define CY_PROT_ATT_PERMISSION_MASK             (0x07UL) /**< Protection Unit attribute permission mask */
#define CY_PROT_ATT_PRIV_PERMISSION_SHIFT       (0x03UL) /**< Protection Unit privileged attribute permission shift */

#define CY_PROT_ATT_PERI_USER_PERM_Pos          (0UL)    /**< PERI v2 privileged attribute permission shift */
#define CY_PROT_ATT_PERI_USER_PERM_Msk          (0x03UL) /**< PERI v2 attribute permission mask */
#define CY_PROT_ATT_PERI_PRIV_PERM_Pos          (2UL)    /**< PERI v2 privileged attribute permission shift */
#define CY_PROT_ATT_PERI_PRIV_PERM_Msk          ((uint32_t)(0x03UL << CY_PROT_ATT_PERI_PRIV_PERM_Pos)) /**< PERI v2 attribute permission mask */

#define CY_PROT_ATT_REGS_MAX                    (4U)     /**< Maximum number of ATT registers */
#define CY_PROT_ATT_PC_MAX                      (4U)     /**< Maximum PC value per ATT reg */

/* BWC macros */
#define CY_PROT_ATT_PERI_PERM_MASK              (0x03UL)
#define CY_PROT_ATT_PERI_PRIV_PERM_SHIFT        (0x02UL)
/* End of BWC macros */

#define CY_PROT_SMPU_PC_LIMIT_MASK              ((uint32_t) 0xFFFFFFFFUL << (CY_PROT_PC_MAX - 1UL))
#define CY_PROT_PPU_PROG_PC_LIMIT_MASK          ((uint32_t) 0xFFFFFFFFUL << (CY_PROT_PC_MAX - 1UL))
#define CY_PROT_PPU_FIXED_PC_LIMIT_MASK         ((uint32_t) 0xFFFFFFFFUL << (CY_PROT_PC_MAX - 1UL))

#define CY_PROT_SMPU_ATT0_MASK                  ((uint32_t)~(PROT_SMPU_SMPU_STRUCT_ATT0_PC_MASK_0_Msk))
#define CY_PROT_SMPU_ATT1_MASK                  ((uint32_t)~(PROT_SMPU_SMPU_STRUCT_ATT1_UX_Msk \
                                                       | PROT_SMPU_SMPU_STRUCT_ATT1_PX_Msk \
                                                       | PROT_SMPU_SMPU_STRUCT_ATT1_PC_MASK_0_Msk \
                                                       | PROT_SMPU_SMPU_STRUCT_ATT1_REGION_SIZE_Msk \
                                                ))

#define CY_PROT_PPU_PROG_ATT0_MASK              ((uint32_t)~(PERI_PPU_PR_ATT0_UX_Msk \
                                                       | PERI_PPU_PR_ATT0_PX_Msk \
                                                       | PERI_PPU_PR_ATT0_PC_MASK_0_Msk \
                                                ))
#define CY_PROT_PPU_PROG_ATT1_MASK              ((uint32_t)~(PERI_PPU_PR_ATT1_UX_Msk \
                                                       | PERI_PPU_PR_ATT1_PX_Msk \
                                                       | PERI_PPU_PR_ATT1_PC_MASK_0_Msk \
                                                       | PERI_PPU_PR_ATT1_REGION_SIZE_Msk \
                                                ))
#define CY_PROT_PPU_GR_ATT0_MASK                ((uint32_t)~(PERI_PPU_GR_ATT0_UX_Msk \
                                                       | PERI_PPU_GR_ATT0_PX_Msk \
                                                       | PERI_PPU_GR_ATT0_PC_MASK_0_Msk \
                                                       | PERI_PPU_GR_ATT0_REGION_SIZE_Msk \
                                                ))
#define CY_PROT_PPU_GR_ATT1_MASK                ((uint32_t)~(PERI_PPU_GR_ATT1_UX_Msk \
                                                       | PERI_PPU_GR_ATT1_PX_Msk \
                                                       | PERI_PPU_GR_ATT1_PC_MASK_0_Msk \
                                                       | PERI_PPU_GR_ATT1_REGION_SIZE_Msk \
                                                ))
#define CY_PROT_PPU_SL_ATT0_MASK                ((uint32_t)~(PERI_PPU_GR_ATT0_UX_Msk \
                                                       | PERI_PPU_GR_ATT0_PX_Msk \
                                                       | PERI_PPU_GR_ATT0_PC_MASK_0_Msk \
                                                       | PERI_PPU_GR_ATT0_REGION_SIZE_Msk \
                                                ))
#define CY_PROT_PPU_SL_ATT1_MASK                ((uint32_t)~(PERI_PPU_GR_ATT1_UX_Msk \
                                                       | PERI_PPU_GR_ATT1_PX_Msk \
                                                       | PERI_PPU_GR_ATT1_PC_MASK_0_Msk \
                                                       | PERI_PPU_GR_ATT1_REGION_SIZE_Msk \
                                                ))
#define CY_PROT_PPU_RG_ATT0_MASK                ((uint32_t)~(PERI_PPU_GR_ATT0_UX_Msk \
                                                       | PERI_PPU_GR_ATT0_PX_Msk \
                                                       | PERI_PPU_GR_ATT0_PC_MASK_0_Msk \
                                                       | PERI_PPU_GR_ATT0_REGION_SIZE_Msk \
                                                ))
#define CY_PROT_PPU_RG_ATT1_MASK                ((uint32_t)~(PERI_PPU_GR_ATT1_UX_Msk \
                                                       | PERI_PPU_GR_ATT1_PX_Msk \
                                                       | PERI_PPU_GR_ATT1_PC_MASK_0_Msk \
                                                       | PERI_PPU_GR_ATT1_REGION_SIZE_Msk \
                                                ))

/* Parameter check macros */
#define CY_PROT_IS_BUS_MASTER_VALID(busMaster)  ((CY_PROT_BUS_MASTER_MASK & (1UL << (uint32_t)(busMaster))) != 0UL)

#define CY_PROT_IS_MPU_PERM_VALID(permission)   (((permission) == CY_PROT_PERM_DISABLED) || \
                                                 ((permission) == CY_PROT_PERM_R) || \
                                                 ((permission) == CY_PROT_PERM_W) || \
                                                 ((permission) == CY_PROT_PERM_RW) || \
                                                 ((permission) == CY_PROT_PERM_X) || \
                                                 ((permission) == CY_PROT_PERM_RX) || \
                                                 ((permission) == CY_PROT_PERM_WX) || \
                                                 ((permission) == CY_PROT_PERM_RWX))

#define CY_PROT_IS_SMPU_MS_PERM_VALID(permission) (((permission) == CY_PROT_PERM_R) || \
                                                 ((permission) == CY_PROT_PERM_RW))

#define CY_PROT_IS_SMPU_SL_PERM_VALID(permission) (((permission) == CY_PROT_PERM_DISABLED) || \
                                                   ((permission) == CY_PROT_PERM_R) || \
                                                   ((permission) == CY_PROT_PERM_W) || \
                                                   ((permission) == CY_PROT_PERM_RW) || \
                                                   ((permission) == CY_PROT_PERM_X) || \
                                                   ((permission) == CY_PROT_PERM_RX) || \
                                                   ((permission) == CY_PROT_PERM_WX) || \
                                                   ((permission) == CY_PROT_PERM_RWX))

#define CY_PROT_IS_PROG_MS_PERM_VALID(permission) (((permission) == CY_PROT_PERM_R) || \
                                                 ((permission) == CY_PROT_PERM_RW))

#define CY_PROT_IS_PROG_SL_PERM_VALID(permission) (((permission) == CY_PROT_PERM_DISABLED) || \
                                                   ((permission) == CY_PROT_PERM_R) || \
                                                   ((permission) == CY_PROT_PERM_W) || \
                                                   ((permission) == CY_PROT_PERM_RW))

#define CY_PROT_IS_FIXED_MS_PERM_VALID(permission) (((permission) == CY_PROT_PERM_DISABLED) || \
                                                    ((permission) == CY_PROT_PERM_R) || \
                                                    ((permission) == CY_PROT_PERM_W) || \
                                                    ((permission) == CY_PROT_PERM_RW))

#define CY_PROT_IS_FIXED_MS_MS_PERM_VALID(permission) (((permission) == CY_PROT_PERM_R) || \
                                                    ((permission) == CY_PROT_PERM_RW))


#define CY_PROT_IS_FIXED_SL_PERM_VALID(permission) (((permission) == CY_PROT_PERM_DISABLED) || \
                                                    ((permission) == CY_PROT_PERM_R) || \
                                                    ((permission) == CY_PROT_PERM_W) || \
                                                    ((permission) == CY_PROT_PERM_RW))

#define CY_PROT_IS_REGION_SIZE_VALID(regionSize) (((regionSize) == CY_PROT_SIZE_256B) || \
                                                  ((regionSize) == CY_PROT_SIZE_512B) || \
                                                  ((regionSize) == CY_PROT_SIZE_1KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_2KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_4KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_8KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_16KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_32KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_64KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_128KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_256KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_512KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_1MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_2MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_4MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_8MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_16MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_32MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_64MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_128MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_256MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_512MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_1GB) || \
                                                  ((regionSize) == CY_PROT_SIZE_2GB) || \
                                                  ((regionSize) == CY_PROT_SIZE_4GB))

#define CY_PROT_IS_PPU_V2_SIZE_VALID(regionSize)  (((regionSize) == CY_PROT_SIZE_4B) || \
                                                  ((regionSize) == CY_PROT_SIZE_8B) || \
                                                  ((regionSize) == CY_PROT_SIZE_16B) || \
                                                  ((regionSize) == CY_PROT_SIZE_32B) || \
                                                  ((regionSize) == CY_PROT_SIZE_64B) || \
                                                  ((regionSize) == CY_PROT_SIZE_128B) || \
                                                  ((regionSize) == CY_PROT_SIZE_256B) || \
                                                  ((regionSize) == CY_PROT_SIZE_512B) || \
                                                  ((regionSize) == CY_PROT_SIZE_1KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_2KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_4KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_8KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_16KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_32KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_64KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_128KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_256KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_512KB) || \
                                                  ((regionSize) == CY_PROT_SIZE_1MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_2MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_4MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_8MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_16MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_32MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_64MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_128MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_256MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_512MB) || \
                                                  ((regionSize) == CY_PROT_SIZE_1GB) || \
                                                  ((regionSize) == CY_PROT_SIZE_2GB) || \
                                                  ((regionSize) == CY_PROT_SIZE_4GB))

#define CY_PROT_IS_SMPU_REQ_MODE_VALID(reqMode)    (((reqMode) == CY_PROT_REQMODE_HIGHPRIOR) || \
                                                    ((reqMode) == CY_PROT_REQMODE_LOWPRIOR) || \
                                                    ((reqMode) == CY_PROT_REQMODE_INDEX))

#define CY_PROT_IS_PPU_PROG_REQ_MODE_VALID(reqMode)    (((reqMode) == CY_PROT_REQMODE_HIGHPRIOR) || \
                                                        ((reqMode) == CY_PROT_REQMODE_LOWPRIOR) || \
                                                        ((reqMode) == CY_PROT_REQMODE_INDEX))

#define CY_PROT_IS_SMPU_IDX_VALID(smpuIndex)       ((smpuIndex) <= (uint32_t)PROT_SMPU_STRUCT_WTH_HIGHEST_PR)

#define CY_PROT_IS_PPU_PROG_IDX_VALID(ppuIndex)    ((ppuIndex) <= (uint32_t)PROT_PPU_PROG_STRUCT_WTH_LOWEST_PR)

#define CY_PROT_IS_PC_VALID(pc)                    ((pc) < PROT_PC_MAX)
#define CY_PROT_IS_PC_MASK_VALID(pcMask)           (((pcMask) & ((uint32_t)~PROT_PC_MASK_MAX)) == 0UL)

/** \endcond */


/***************************************
*       Configuration Structures
***************************************/

/**
* \addtogroup group_prot_data_structures
* \{
*/

/** Configuration structure for MPU Struct initialization */
typedef struct
{
    uint32_t*         address;          /**< Base address of the memory region */
    cy_en_prot_size_t regionSize;       /**< Size of the memory region */
    uint8_t           subregions;       /**< Mask of the 8 subregions to disable */
    cy_en_prot_perm_t userPermission;   /**< User permissions for the region */
    cy_en_prot_perm_t privPermission;   /**< Privileged permissions for the region */
    bool              secure;           /**< Non Secure = 0, Secure = 1 */
} cy_stc_mpu_cfg_t;

/** Configuration structure for SMPU struct initialization */
typedef struct
{
    uint32_t*         address;          /**< Base address of the memory region (Only applicable to slave) */
    cy_en_prot_size_t regionSize;       /**< Size of the memory region (Only applicable to slave) */
    uint8_t           subregions;       /**< Mask of the 8 subregions to disable (Only applicable to slave) */
    cy_en_prot_perm_t userPermission;   /**< User permissions for the region */
    cy_en_prot_perm_t privPermission;   /**< Privileged permissions for the region */
    bool              secure;           /**< Non Secure = 0, Secure = 1 */
    bool              pcMatch;          /**< Access evaluation = 0, Matching = 1  */
    uint16_t          pcMask;           /**< Mask of allowed protection context(s) */
} cy_stc_smpu_cfg_t;

/** Configuration structure for Programmable (PROG) PPU (PPU_PR) struct initialization */
typedef struct
{
    uint32_t*         address;          /**< Base address of the memory region (Only applicable to slave) */
    cy_en_prot_size_t regionSize;       /**< Size of the memory region (Only applicable to slave) */
    uint8_t           subregions;       /**< Mask of the 8 subregions to disable (Only applicable to slave) */
    cy_en_prot_perm_t userPermission;   /**< User permissions for the region */
    cy_en_prot_perm_t privPermission;   /**< Privileged permissions for the region */
    bool              secure;           /**< Non Secure = 0, Secure = 1 */
    bool              pcMatch;          /**< Access evaluation = 0, Matching = 1  */
    uint16_t          pcMask;           /**< Mask of allowed protection context(s) */
} cy_stc_ppu_prog_cfg_t;

/** Configuration structure for Fixed Group (GR) PPU (PPU_GR) struct initialization */
typedef struct
{
    cy_en_prot_perm_t userPermission;   /**< User permissions for the region */
    cy_en_prot_perm_t privPermission;   /**< Privileged permissions for the region */
    bool              secure;           /**< Non Secure = 0, Secure = 1 */
    bool              pcMatch;          /**< Access evaluation = 0, Matching = 1  */
    uint16_t          pcMask;           /**< Mask of allowed protection context(s) */
} cy_stc_ppu_gr_cfg_t;

/** Configuration structure for Fixed Slave (SL) PPU (PPU_SL) struct initialization */
typedef struct
{
    cy_en_prot_perm_t userPermission;   /**< User permissions for the region */
    cy_en_prot_perm_t privPermission;   /**< Privileged permissions for the region */
    bool              secure;           /**< Non Secure = 0, Secure = 1 */
    bool              pcMatch;          /**< Access evaluation = 0, Matching = 1  */
    uint16_t          pcMask;           /**< Mask of allowed protection context(s) */
} cy_stc_ppu_sl_cfg_t;

/** Configuration structure for Fixed Region (RG) PPU (PPU_RG) struct initialization */
typedef struct
{
    cy_en_prot_perm_t userPermission;  /**< User permissions for the region */
    cy_en_prot_perm_t privPermission;  /**< Privileged permissions for the region */
    bool             secure;           /**< Non Secure = 0, Secure = 1 */
    bool             pcMatch;          /**< Access evaluation = 0, Matching = 1  */
    uint16_t         pcMask;           /**< Mask of allowed protection context(s) */
} cy_stc_ppu_rg_cfg_t;

/** \} group_prot_data_structures */


/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_prot_functions
* \{
*/

/**
* \addtogroup group_prot_functions_busmaster
* \{
*/
cy_en_prot_status_t Cy_Prot_ConfigBusMaster(en_prot_master_t busMaster, bool privileged, bool secure, uint32_t pcMask);
cy_en_prot_status_t Cy_Prot_SetActivePC(en_prot_master_t busMaster, uint32_t pc);
uint32_t Cy_Prot_GetActivePC(en_prot_master_t busMaster);
/** \} group_prot_functions_busmaster */

/**
* \addtogroup group_prot_functions_mpu
* \{
*/
cy_en_prot_status_t Cy_Prot_ConfigMpuStruct(PROT_MPU_MPU_STRUCT_Type* base, const cy_stc_mpu_cfg_t* config);
cy_en_prot_status_t Cy_Prot_EnableMpuStruct(PROT_MPU_MPU_STRUCT_Type* base);
cy_en_prot_status_t Cy_Prot_DisableMpuStruct(PROT_MPU_MPU_STRUCT_Type* base);
/** \} group_prot_functions_mpu */

/**
* \addtogroup group_prot_functions_smpu
* \{
*/
__STATIC_INLINE cy_en_prot_status_t Cy_Prot_DisableSmpuStruct(PROT_SMPU_SMPU_STRUCT_Type* base);
cy_en_prot_status_t Cy_Prot_GetSmpuStruct(PROT_SMPU_SMPU_STRUCT_Type** base, cy_en_prot_req_mode_t reqMode, uint32_t smpuIndex);

cy_en_prot_status_t Cy_Prot_ConfigSmpuMasterStruct(PROT_SMPU_SMPU_STRUCT_Type* base, const cy_stc_smpu_cfg_t* config);
cy_en_prot_status_t Cy_Prot_ConfigSmpuSlaveStruct(PROT_SMPU_SMPU_STRUCT_Type* base, const cy_stc_smpu_cfg_t* config);
cy_en_prot_status_t Cy_Prot_EnableSmpuMasterStruct(PROT_SMPU_SMPU_STRUCT_Type* base);
cy_en_prot_status_t Cy_Prot_DisableSmpuMasterStruct(PROT_SMPU_SMPU_STRUCT_Type* base);
cy_en_prot_status_t Cy_Prot_EnableSmpuSlaveStruct(PROT_SMPU_SMPU_STRUCT_Type* base);
cy_en_prot_status_t Cy_Prot_DisableSmpuSlaveStruct(PROT_SMPU_SMPU_STRUCT_Type* base);

/** \} group_prot_functions_smpu */



/**
* \addtogroup group_prot_functions_ppu_prog_v2
* \{
*/

cy_en_prot_status_t Cy_Prot_ConfigPpuProgMasterAtt(PERI_MS_PPU_PR_Type* base, uint16_t pcMask, cy_en_prot_perm_t userPermission, cy_en_prot_perm_t privPermission, bool secure);
cy_en_prot_status_t Cy_Prot_ConfigPpuProgSlaveAtt(PERI_MS_PPU_PR_Type* base, uint16_t pcMask, cy_en_prot_perm_t userPermission, cy_en_prot_perm_t privPermission, bool secure);
#if defined (CY_IP_M4CPUSS)
cy_en_prot_status_t Cy_Prot_ConfigPpuProgSlaveAddr(PERI_MS_PPU_PR_Type* base, uint32_t address, cy_en_prot_size_t regionSize);
cy_en_prot_status_t Cy_Prot_EnablePpuProgSlaveRegion(PERI_MS_PPU_PR_Type* base);
cy_en_prot_status_t Cy_Prot_DisablePpuProgSlaveRegion(PERI_MS_PPU_PR_Type* base);
#endif

/** \} group_prot_functions_ppu_prog_v2 */

/**
* \addtogroup group_prot_functions_ppu_fixed_v2
* \{
*/
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedMasterAtt(PERI_MS_PPU_FX_Type* base, uint16_t pcMask, cy_en_prot_perm_t userPermission, cy_en_prot_perm_t privPermission, bool secure);
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedSlaveAtt(PERI_MS_PPU_FX_Type* base, uint16_t pcMask, cy_en_prot_perm_t userPermission, cy_en_prot_perm_t privPermission, bool secure);
/** \} group_prot_functions_ppu_fixed_v2 */


#if defined (CY_IP_M4CPUSS)
/**
* \addtogroup group_prot_functions_ppu_prog
* \{
*/
__STATIC_INLINE cy_en_prot_status_t Cy_Prot_DisablePpuProgStruct(PERI_PPU_PR_Type* base);

cy_en_prot_status_t Cy_Prot_ConfigPpuProgMasterStruct(PERI_PPU_PR_Type* base, const cy_stc_ppu_prog_cfg_t* config);
cy_en_prot_status_t Cy_Prot_ConfigPpuProgSlaveStruct(PERI_PPU_PR_Type* base, const cy_stc_ppu_prog_cfg_t* config);
cy_en_prot_status_t Cy_Prot_EnablePpuProgMasterStruct(PERI_PPU_PR_Type* base);
cy_en_prot_status_t Cy_Prot_DisablePpuProgMasterStruct(PERI_PPU_PR_Type* base);
cy_en_prot_status_t Cy_Prot_EnablePpuProgSlaveStruct(PERI_PPU_PR_Type* base);
cy_en_prot_status_t Cy_Prot_DisablePpuProgSlaveStruct(PERI_PPU_PR_Type* base);

cy_en_prot_status_t Cy_Prot_GetPpuProgStruct(PERI_PPU_PR_Type** base, cy_en_prot_req_mode_t reqMode, uint32_t ppuProgIndex);

/** \} group_prot_functions_ppu_prog */

/**
* \addtogroup group_prot_functions_ppu_gr
* \{
*/
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedGrMasterStruct(PERI_PPU_GR_Type* base, const cy_stc_ppu_gr_cfg_t* config);
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedGrSlaveStruct(PERI_PPU_GR_Type* base, const cy_stc_ppu_gr_cfg_t* config);
cy_en_prot_status_t Cy_Prot_EnablePpuFixedGrMasterStruct(PERI_PPU_GR_Type* base);
cy_en_prot_status_t Cy_Prot_DisablePpuFixedGrMasterStruct(PERI_PPU_GR_Type* base);
cy_en_prot_status_t Cy_Prot_EnablePpuFixedGrSlaveStruct(PERI_PPU_GR_Type* base);
cy_en_prot_status_t Cy_Prot_DisablePpuFixedGrSlaveStruct(PERI_PPU_GR_Type* base);
/** \} group_prot_functions_ppu_gr */

/**
* \addtogroup group_prot_functions_ppu_sl
* \{
*/
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedSlMasterStruct(PERI_GR_PPU_SL_Type* base, const cy_stc_ppu_sl_cfg_t* config);
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedSlSlaveStruct(PERI_GR_PPU_SL_Type* base, const cy_stc_ppu_sl_cfg_t* config);
cy_en_prot_status_t Cy_Prot_EnablePpuFixedSlMasterStruct(PERI_GR_PPU_SL_Type* base);
cy_en_prot_status_t Cy_Prot_DisablePpuFixedSlMasterStruct(PERI_GR_PPU_SL_Type* base);
cy_en_prot_status_t Cy_Prot_EnablePpuFixedSlSlaveStruct(PERI_GR_PPU_SL_Type* base);
cy_en_prot_status_t Cy_Prot_DisablePpuFixedSlSlaveStruct(PERI_GR_PPU_SL_Type* base);
/** \} group_prot_functions_ppu_sl */

/**
* \addtogroup group_prot_functions_ppu_rg
* \{
*/
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedRgMasterStruct(PERI_GR_PPU_RG_Type* base, const cy_stc_ppu_rg_cfg_t* config);
cy_en_prot_status_t Cy_Prot_ConfigPpuFixedRgSlaveStruct(PERI_GR_PPU_RG_Type* base, const cy_stc_ppu_rg_cfg_t* config);
cy_en_prot_status_t Cy_Prot_EnablePpuFixedRgMasterStruct(PERI_GR_PPU_RG_Type* base);
cy_en_prot_status_t Cy_Prot_DisablePpuFixedRgMasterStruct(PERI_GR_PPU_RG_Type* base);
cy_en_prot_status_t Cy_Prot_EnablePpuFixedRgSlaveStruct(PERI_GR_PPU_RG_Type* base);
cy_en_prot_status_t Cy_Prot_DisablePpuFixedRgSlaveStruct(PERI_GR_PPU_RG_Type* base);
/** \} group_prot_functions_ppu_rg */

#endif /* (CY_IP_M4CPUSS) */

/** \} group_prot_functions */



/**
* \addtogroup group_prot_functions
* \{
*/

/**
* \addtogroup group_prot_functions_smpu
* \{
*/

/*******************************************************************************
* Function Name: Cy_Prot_DisableSmpuStruct
****************************************************************************//**
*
* This function disables both the master and slave parts of a protection unit.
*
* \param base
* The base address for the SMPU structure to be disabled.
*
* \return
* Status of the function call.
*
*   Status               | Description
*   ---------------------| -----------
*   CY_PROT_SUCCESS      | The Master and Slave SMPU struct was disabled
*   CY_PROT_FAILURE      | The Master and/or slave SMPU  struct was not disabled
*  CY_PROT_INVALID_STATE | Function was called on the unsupported PERI IP version
*
* \funcusage
* \snippet prot/snippet/main.c snippet_Cy_Prot_DisableSmpuStruct
*
*******************************************************************************/
__STATIC_INLINE cy_en_prot_status_t Cy_Prot_DisableSmpuStruct(PROT_SMPU_SMPU_STRUCT_Type* base)
{
    cy_en_prot_status_t status = Cy_Prot_DisableSmpuMasterStruct(base);

    if (CY_PROT_SUCCESS == status)
    {
        status = Cy_Prot_DisableSmpuSlaveStruct(base);
    }

    return status;
}
/** \} group_prot_functions_smpu */


#if defined (CY_IP_M4CPUSS)
/**
* \addtogroup group_prot_functions_ppu_prog
* \{
*/
/*******************************************************************************
* Function Name: Cy_Prot_DisablePpuProgStruct
****************************************************************************//**
*
* This function disables both the master and slave parts of a protection unit.
*
* \note
* This functions has an effect only on devices with PERI IP version 1. Refer
* to the device datasheet for information about PERI HW IP version.
*
* \param base
* The base address for the Programmable PU structure to be disabled.
*
* \return
* Status of the function call.
*
*   Status               | Description
*   ---------------------| -----------
*   CY_PROT_SUCCESS      | The Master and Slave Programmable PU struct was disabled
*   CY_PROT_FAILURE      | The Master and/or slave Programmable PU struct was not disabled
*  CY_PROT_INVALID_STATE | Function was called on the unsupported PERI IP version
*
* \funcusage
* \snippet prot/snippet/main.c snippet_Cy_Prot_DisablePpuProgStruct
*
*******************************************************************************/
__STATIC_INLINE cy_en_prot_status_t Cy_Prot_DisablePpuProgStruct(PERI_PPU_PR_Type* base)
{
    cy_en_prot_status_t status = CY_PROT_INVALID_STATE;

    if (CY_PERI_V1 != 0U)
    {
        status = Cy_Prot_DisablePpuProgMasterStruct(base);

        if (CY_PROT_SUCCESS == status)
        {
            status = Cy_Prot_DisablePpuProgSlaveStruct(base);
        }
    }

    return status;
}
/** \} group_prot_functions_ppu_prog */
#endif /* (CY_IP_M4CPUSS) */
/** \} group_prot_functions */
/** \} group_prot */

#if defined(__cplusplus)
}
#endif

#endif /* defined (CY_IP_M4CPUSS) || defined (CY_IP_M7CPUSS) */

#endif /* CY_PROT_H */
