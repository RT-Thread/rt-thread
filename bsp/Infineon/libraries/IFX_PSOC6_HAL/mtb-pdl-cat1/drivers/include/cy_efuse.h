/***************************************************************************//**
* \file cy_efuse.h
* \version 2.20
*
* Provides the API declarations of the eFuse driver.
*
********************************************************************************
* \copyright
* Copyright 2017-2020 Cypress Semiconductor Corporation
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

#if !defined(CY_EFUSE_H)
#define CY_EFUSE_H

/**
* \addtogroup group_efuse
* \{
*
* Electronic Fuses (eFuses) are non-volatile memory where each bit is one-time
* programmable (OTP).
*
* The functions and other declarations used in this driver are in cy_efuse.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* The eFuse driver enables reading the state of any bit.
* - CAT1A devices does not support writing to eFuse memory. Writing an
*   eFuse bit is typically done by a production programmer.
*   Fuses are programmed via the PSoC Programmer tool that parses the hex file
*   and extracts the necessary information; the fuse data must be located at the
*   dedicated section in the hex file. For more details see
*   [PSoC 6 Programming Specifications]
*   (http://www.cypress.com/documentation/programming-specifications/psoc-6-programming-specifications)
* - CAT1B devices support writing to eFuse memory.
* - CAT1C devices does not support writing to eFuse memory.
*
* One eFuse macro consists of 256 bits (32 * 8).
* Consult the device-specific datasheet to determine how many
* macros a device has. These are implemented as a regular Advanced
* High-performance Bus (AHB) peripheral with the following characteristics:
* - eFuses are used to control the device life-cycle stage (NORMAL, SECURE,
*   and SECURE_WITH_DEBUG) and the protection settings;
* - eFuse memory can be programmed (eFuse bit value changed from '0' to '1')
*   only once; if an eFuse bit is blown, it cannot be cleared again;
*
* \section group_efuse_configuration Configuration Considerations
*
* The eFuse driver provides the simplest way to read and write eFuse memory.
* No configuration is needed.
*
* \section group_efuse_more_information More Information
*
* Refer to the technical reference manual (TRM) and the device datasheet.
*
* \section group_efuse_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>2.20</td>
*     <td>Updated driver to support the CAT1C family of devices.</td>
*     <td>Added new family of devices.</td>
*   </tr>
*   <tr>
*     <td>2.10</td>
*     <td>Implementation for newly introduced APIs for CAT1B devices has been updated.</td>
*     <td>Updated driver APIs support for CAT1B devices.</td>
*   </tr>
*   <tr>
*     <td>2.0</td>
*     <td>Added the following functions: \ref Cy_EFUSE_Init,\n \ref Cy_EFUSE_DeInit,\n \ref Cy_EFUSE_Enable,\n
*         \ref Cy_EFUSE_Disable,\n \ref Cy_EFUSE_WriteBit,\n \ref Cy_EFUSE_WriteByte,\n \ref Cy_EFUSE_WriteWord,\n
*         \ref Cy_EFUSE_WriteWordArray,\n \ref Cy_EFUSE_ReadBit,\n \ref Cy_EFUSE_ReadByte,\n \ref Cy_EFUSE_ReadWord,\n
*         \ref Cy_EFUSE_ReadWordArray,\n \ref Cy_EFUSE_WriteBootRow,\n \ref Cy_EFUSE_ReadBootRow.</td>
*     <td>New driver APIs support for CAT1B devices.</td>
*   </tr>
*   <tr>
*     <td>1.10.4</td>
*     <td>Minor documentation updates.</td>
*     <td>Removed MISRA 2004 compliance details and verified MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>1.10.3</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.10.2</td>
*     <td>Fix driver header path.</td>
*     <td>Folder structure changed.</td>
*   </tr>
*   <tr>
*     <td>1.10.1</td>
*     <td>Added header guard CY_IP_MXEFUSE.</td>
*     <td>To enable the PDL compilation with wounded out IP blocks.</td>
*   </tr>
*   <tr>
*     <td>1.10</td>
*     <td>Flattened the organization of the driver source code into the single
*         source directory and the single include directory.
*     </td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_efuse_macros Macros
* \defgroup group_efuse_functions Functions
* \defgroup group_efuse_data_structures Data Structures
* \defgroup group_efuse_enumerated_types Enumerated Types
*/

#include "cy_device.h"

#if defined CY_IP_MXEFUSE

#include "cy_syslib.h"

/***************************************
* Macro Definitions
***************************************/
/**
* \addtogroup group_efuse_macros
* \{
*/

/** The driver major version */
#define CY_EFUSE_DRV_VERSION_MAJOR          2
/** The driver minor version */
#define CY_EFUSE_DRV_VERSION_MINOR          20
/** The eFuse driver identifier */
#define CY_EFUSE_ID                         (CY_PDL_DRV_ID(0x1AUL))
/** The number of bits in the byte */
#define CY_EFUSE_BITS_PER_BYTE              (8UL)
/** \} group_efuse_macros */

/***************************************
* Enumerated Types
***************************************/
/**
* \addtogroup group_efuse_enumerated_types
* \{
*/
/** This enum has the return values of the eFuse driver */
typedef enum
{
    CY_EFUSE_SUCCESS               = 0x00UL,  /**< Success */
    CY_EFUSE_INVALID_PROTECTION    = CY_EFUSE_ID | CY_PDL_STATUS_ERROR | 0x01UL, /**< Invalid access in the current protection state */
    CY_EFUSE_INVALID_FUSE_ADDR     = CY_EFUSE_ID | CY_PDL_STATUS_ERROR | 0x02UL, /**< Invalid eFuse address */
    CY_EFUSE_BAD_PARAM             = CY_EFUSE_ID | CY_PDL_STATUS_ERROR | 0x03UL, /**< One or more invalid parameters */
    CY_EFUSE_IPC_BUSY              = CY_EFUSE_ID | CY_PDL_STATUS_ERROR | 0x04UL, /**< The IPC structure is already locked by another process */
    CY_EFUSE_WRITE_BUSY            = CY_EFUSE_ID | CY_PDL_STATUS_ERROR | 0x05UL, /**< Previous write operation in progress
                                                                                   * \note Supported in CAT1B devices. */
    CY_EFUSE_WRITE_ERROR           = CY_EFUSE_ID | CY_PDL_STATUS_ERROR | 0x06UL, /**< Write operation failed. Retry operation.
                                                                                   * \note Supported in CAT1B devices. */
    CY_EFUSE_WRITE_TIMEOUT_ERROR   = CY_EFUSE_ID | CY_PDL_STATUS_ERROR | 0x07UL, /**< Timeout Error in Write Operation
                                                                                   * \note Supported in CAT1B devices. */
    CY_EFUSE_ERR_UNC               = CY_EFUSE_ID | CY_PDL_STATUS_ERROR | 0xFFUL  /**< Unknown error code. See Cy_EFUSE_GetExternalStatus() */
} cy_en_efuse_status_t;

/** \} group_efuse_data_structure */

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
*                            Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_efuse_functions
* \{
*/
#if (CY_IP_MXEFUSE_VERSION <= 2) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_EFUSE_GetEfuseBit
****************************************************************************//**
*
* Reports the current state of a given eFuse bit-number. Consult the device TRM
* to determine the target fuse bit number.
*
* \note An attempt to read an eFuse data from a protected memory region
* will generate a HardFault.
*
* \param bitNum
* The number of the bit to read. The valid range of the bit number is
* from 0 to EFUSE_EFUSE_NR * 32 * 8 - 1 where:
* - EFUSE_EFUSE_NR is number of efuse macros in the selected device series,
* - 32 is a number of fuse bytes in one efuse macro,
* - 8 is a number of fuse bits in the byte.
*
* The EFUSE_EFUSE_NR macro is defined in the series-specific header file, e.g
* \e \<PDL_DIR\>/devices/include/psoc6_01_config.\e h
*
* \param bitVal
* The pointer to the location to store the bit value.
*
* \return
* \ref cy_en_efuse_status_t
*
* \note
* Supported in CAT1A and CAT1C devices.
*
* \funcusage
* The example below shows how to read device life-cycle register bits in
* PSoC 6:
* \snippet efuse/snippet/main.c SNIPPET_EFUSE_READ_BIT
*
*******************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_GetEfuseBit(uint32_t bitNum, bool *bitVal);


/*******************************************************************************
* Function Name: Cy_EFUSE_GetEfuseByte
****************************************************************************//**
*
* Reports the current state of the eFuse byte.
* If the offset parameter is beyond the available quantities,
* zeroes will be stored to the byteVal parameter. Consult the device TRM
* to determine the target fuse byte offset.
*
* \note An attempt to read an eFuse data from a protected memory region
* will generate a HardFault.
*
* \param offset
* The offset of the byte to read. The valid range of the byte offset is
* from 0 to EFUSE_EFUSE_NR * 32 - 1 where:
* - EFUSE_EFUSE_NR is a number of efuse macros in the selected device series,
* - 32 is a number of fuse bytes in one efuse macro.
*
* The EFUSE_EFUSE_NR macro is defined in the series-specific header file, e.g
* \e \<PDL_DIR\>/devices/include/psoc6_01_config.\e h
*
* \param byteVal
* The pointer to the location to store eFuse data.
*
* \return
* \ref cy_en_efuse_status_t
*
* \note
* Supported in CAT1A and CAT1C devices.
*
* \funcusage
* The example below shows how to read a device life-cycle stage register in
* PSoC 6:
* \snippet efuse/snippet/main.c SNIPPET_EFUSE_READ_LIFECYCLE
*
*******************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_GetEfuseByte(uint32_t offset, uint8_t *byteVal);


/*******************************************************************************
* Function Name: Cy_EFUSE_GetExternalStatus
****************************************************************************//**
*
* This function handles the case where a module such as a security image captures
* a system call from this driver and reports its own status or error code,
* for example, protection violation. In that case, a function from this
* driver returns an unknown error (see \ref cy_en_efuse_status_t). After receipt
* of an unknown error, the user may call this function to get the status
* of the capturing module.
*
* The user is responsible for parsing the content of the returned value
* and casting it to the appropriate enumeration.
*
* \return
* The error code of the previous efuse operation.
*
* \note
* Supported in CAT1A and CAT1C devices.
*
*******************************************************************************/
uint32_t Cy_EFUSE_GetExternalStatus(void);
#endif

#if (CY_IP_MXEFUSE_VERSION >= 3) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_EFUSE_Init
****************************************************************************//**
*
* This function enables the EFUSE block and initializes the registers with the
* default values.
*
* \param base
* The pointer to the EFUSE instance.
*
* \return
* The EFUSE API status \ref cy_en_efuse_status_t.
*
* \note
* Supported in CAT1B devices.
*
*******************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_Init(EFUSE_Type *base);


/*******************************************************************************
* Function Name: Cy_EFUSE_Enable
****************************************************************************//**
*
* Enables the EFUSE block.
*
* \param base
* The pointer to the EFUSE instance.
*
* \note
* Supported in CAT1B devices.
*
*******************************************************************************/
void Cy_EFUSE_Enable(EFUSE_Type *base);


/*******************************************************************************
* Function Name: Cy_EFUSE_Disable
****************************************************************************//**
*
* Disables the EFUSE block. All non-retention registers (command and status
* registers) are reset to their default values when the IP is disabled.
*
* \param base
* The pointer to the EFUSE instance.
*
* \note
* Supported in CAT1B devices.
*
*******************************************************************************/
void Cy_EFUSE_Disable(EFUSE_Type *base);

/*******************************************************************************
* Function Name: Cy_EFUSE_IsEnabled
****************************************************************************//**
*
* Check if EFUSE block is Enabled or Not.
*
* \param base
* The pointer to the EFUSE instance.
*
* \return
* - True if the EFUSE is enabled.
* - False if EFUSE is disabled.
*
* \note
* Supported in CAT1B devices.
*
*******************************************************************************/
bool Cy_EFUSE_IsEnabled(EFUSE_Type *base);


/*******************************************************************************
* Function Name: Cy_EFUSE_DeInit
****************************************************************************//**
*
* Disables the EFUSE block. All non-retention registers (command and status
* registers) are reset to their default values when the IP is disabled.
*
* \param base
* The pointer to the EFUSE instance.
*
* \note
* Supported in CAT1B devices.
*
*******************************************************************************/
void Cy_EFUSE_DeInit(EFUSE_Type *base);


/*******************************************************************************
* Function Name: Cy_EFUSE_WriteBit
****************************************************************************//**
*
* Writes a bit to EFUSE by blowing a fuse, so this function is able to write 1s
* only. Before write operations you must call \ref Cy_EFUSE_Init().
* It is recommended to disable the block when not using it. Call
* \ref Cy_EFUSE_Disable() to disable the EFUSE block.
*
* \param base
* The pointer to the EFUSE instance.
*
* \param bitPos
* Bit position within byte.
*
* \param offset
* Byte position within EFUSE address space.
*
* \return
* The EFUSE API status \ref cy_en_efuse_status_t.
*
* \note
* - The caller is expected to verify the input parameters for correctness
*  and to check whether the bit is already blown before calling this function
*  to not over-program bits.
* - Supported in CAT1B devices.
*
*******************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_WriteBit(EFUSE_Type *base, uint32_t bitPos, uint32_t offset);


/*******************************************************************************
* Function Name: Cy_EFUSE_WriteByte
****************************************************************************//**
*
* Writes one byte.
* Before write operations you must call \ref Cy_EFUSE_Init().
* It is recommended to disable the block when not using it. Call
* \ref Cy_EFUSE_Disable() to disable the EFUSE block.
*
* \param base
* The pointer to the EFUSE instance.
*
* \param src
* Value to be written.
*
* \param offset
* Byte offset from the EFUSE base address
*
* \return
* The EFUSE API status \ref cy_en_efuse_status_t.
*
* \note
* - The caller is expected to check whether the bits within the byte
*  are already blown before calling this function to not over-program bits.
* - Supported in CAT1B devices.
*******************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_WriteByte(EFUSE_Type *base, uint32_t src, uint32_t offset);


/*******************************************************************************
* Function Name: Cy_EFUSE_WriteWord
****************************************************************************//**
*
* Writes every bit set in src that was not already programmed.
* Before write operations you must call \ref Cy_EFUSE_Init().
* It is recommended to disable the block when not using it. Call
* \ref Cy_EFUSE_Disable() to disable the EFUSE block.
*
* \param base
* The pointer to the EFUSE instance.
*
* \param src
* Value to be written.
*
* \param offset
* Offset from the EFUSE base address. Must be 4-byte aligned.
*
* \return
* The EFUSE API status \ref cy_en_efuse_status_t.
*
* \note
* - The caller is expected to check whether the bits within the 32-bit word
*  are already blown before calling this function to not over-program bits.
* - Supported in CAT1B devices.
*
*******************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_WriteWord(EFUSE_Type *base, uint32_t src, uint32_t offset);


/*******************************************************************************
* Function Name: Cy_EFUSE_WriteWordArray
****************************************************************************//**
*
* Writes the values of num 32-bit words from the location pointed to by src to
* the EFUSE location pointed to by offset.
*
* Before write operations you must call \ref Cy_EFUSE_Init().
* It is recommended to disable the block when not using it. Call
* \ref Cy_EFUSE_Disable() to disable the EFUSE block.
*
* \param base
* The pointer to the EFUSE instance.
*
* \param src
* Pointer to the source of data to be written.
*
* \param offset
* Offset from the EFUSE base address. Must be 4-byte aligned.
*
* \param num
* Number of 32-bit words to be written.
*
* \return
* The EFUSE API status \ref cy_en_efuse_status_t.
*
* \note
* - The caller is expected to check whether the bits within the 32-bit words
*  are already blown before calling this function to not over-program bits.
* - Supported in CAT1B devices.
*
*******************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_WriteWordArray(EFUSE_Type *base, const uint32_t *src, uint32_t offset, uint32_t num);

/*******************************************************************************
* Function Name: Cy_EFUSE_ReadBit
****************************************************************************//**
*
* Reads a bit from EFUSE.
* Before read operations you must call \ref Cy_EFUSE_Init().
* It is recommended to disable the block when not using it.
* Call \ref Cy_EFUSE_Disable() to disable the EFUSE block.
*
* \param base
* The pointer to the EFUSE instance.
*
* \param dst
* Pointer to the destination where the read bit is stored.
*
* \param bitPos
* Bit position within byte.
*
* \param offset
* Byte offset from the EFUSE base address.
*
* \return
* The EFUSE API status \ref cy_en_efuse_status_t.
*
* \note
* Supported in CAT1B devices.
*
*******************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_ReadBit(EFUSE_Type *base, uint8_t *dst, uint32_t bitPos, uint32_t offset);

/*******************************************************************************
* Function Name: Cy_EFUSE_ReadByte
****************************************************************************//**
*
* Reads byte from EFUSE.
* Before read operations you must call \ref Cy_EFUSE_Init().
* It is recommended to disable the block when not using it. Call
* \ref Cy_EFUSE_Disable() to disable the EFUSE block.
*
* \param base
* The pointer to the EFUSE instance.
*
* \param dst
* Pointer to the destination where the read byte is stored.
*
* \param offset
* Byte offset from the EFUSE base address.
*
* \return
* The EFUSE API status \ref cy_en_efuse_status_t.
*
* \note
* Supported in CAT1B devices.
*
*******************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_ReadByte(EFUSE_Type *base, uint8_t *dst, uint32_t offset);


/*******************************************************************************
* Function Name: Cy_EFUSE_ReadWord
****************************************************************************//**
*
* Reads a 32-bit word from EFUSE.
* Before read operations you must call \ref Cy_EFUSE_Init().
* It is recommended to disable the block when not using it. Call
* \ref Cy_EFUSE_Disable() to disable the EFUSE block.
*
* \param base
* The pointer to the EFUSE instance.
*
* \param dst
* Pointer to the destination where the read word is stored.
*
* \param offset
* Offset from the EFUSE base address. Must be 4-byte aligned.
*
* \return
* The EFUSE API status \ref cy_en_efuse_status_t.
*
* \note
* Supported in CAT1B devices.
*
*******************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_ReadWord(EFUSE_Type *base, uint32_t *dst, uint32_t offset);


/*******************************************************************************
* Function Name: Cy_EFUSE_ReadWordArray
****************************************************************************//**
*
* Reads an array of 32-bit words from EFUSE.
* Before read operations you must call \ref Cy_EFUSE_Init().
* It is recommended to disable the block when not using it. Call
* \ref Cy_EFUSE_Disable() to disable the EFUSE block.
*
* \param base
* The pointer to the EFUSE instance.
*
* \param dst
* Pointer to the destination array where the content is to be read.
*
* \param offset
* Start address of the data to read in EFUSE.
*
* \param num
* Number of words to read.
*
* \return
* The EFUSE API status \ref cy_en_efuse_status_t.
*
* \note
* Supported in CAT1B devices.
*
*******************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_ReadWordArray(EFUSE_Type *base, uint32_t *dst, uint32_t offset, uint32_t num);


/*******************************************************************************
* Function Name: Cy_EFUSE_WriteBootRow
****************************************************************************//**
*
* Writes data into BOOTROW.
* Before write operations you must call \ref Cy_EFUSE_Init().
* It is recommended to disable the block when not using it. Call
* \ref Cy_EFUSE_Disable() to disable the EFUSE block.
*
* \param base
* The pointer to the EFUSE instance.
*
* \param bootrow
* 32-bit value to be written into bootrow.
*
* \return
* The EFUSE API status \ref cy_en_efuse_status_t.
*
* \note
* Supported in CAT1B devices.
*
*******************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_WriteBootRow(EFUSE_Type *base, uint32_t bootrow);


/*******************************************************************************
* Function Name: Cy_EFUSE_ReadBootRow
****************************************************************************//**
*
* Reads data from BOOTROW.
* The BOOTROW information is latched upon system reset and is readable as
* MMIO register.
*
* \param base
* The pointer to the EFUSE instance.
*
* \param bootrow
* Pointer to the variable where the content of BOOTROW is read to.
*
* \return
* The EFUSE API status \ref cy_en_efuse_status_t.
*
* \note
* Supported in CAT1B devices.
*
*******************************************************************************/
cy_en_efuse_status_t Cy_EFUSE_ReadBootRow(EFUSE_Type *base, uint32_t *bootrow);
#endif

/** \} group_efuse_functions */

#if defined(__cplusplus)
}
#endif

#endif /* #ifdef CY_IP_MXEFUSE */

#endif /* #if !defined(CY_EFUSE_H) */

/** \} group_efuse */


/* [] END OF FILE */
