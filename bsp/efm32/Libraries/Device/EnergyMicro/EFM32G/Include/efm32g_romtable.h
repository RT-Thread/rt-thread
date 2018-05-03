/**************************************************************************//**
 * @file
 * @brief efm32g_romtable Register and Bit Field definitions
 * @author Energy Micro AS
 * @version 3.0.0
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
/**************************************************************************//**
 * @defgroup EFM32G_ROMTABLE
 * @{
 * @brief Chip Information, Revision numbers
 *****************************************************************************/
typedef struct
{
  __I uint32_t PID4; /**< JEP_106_BANK */
  __I uint32_t PID5; /**< Unused */
  __I uint32_t PID6; /**< Unused */
  __I uint32_t PID7; /**< Unused */
  __I uint32_t PID0; /**< Chip family LSB, chip major revision */
  __I uint32_t PID1; /**< JEP_106_NO, Chip family MSB */
  __I uint32_t PID2; /**< Chip minor rev MSB, JEP_106_PRESENT, JEP_106_NO */
  __I uint32_t PID3; /**< Chip minor rev LSB */
  __I uint32_t CID0; /**< Unused */
} ROMTABLE_TypeDef;  /** @} */

/**************************************************************************//**
 * @defgroup EFM32G_ROMTABLE_BitFields
 * @{
 *****************************************************************************/
/* Bit fields for EFM32G_ROMTABLE */
#define _ROMTABLE_PID0_FAMILYLSB_MASK       0x000000C0UL /**< Least Significant Bits [1:0] of CHIP FAMILY, mask */
#define _ROMTABLE_PID0_FAMILYLSB_SHIFT      6            /**< Least Significant Bits [1:0] of CHIP FAMILY, shift */
#define _ROMTABLE_PID0_REVMAJOR_MASK        0x0000003FUL /**< CHIP MAJOR Revison, mask */
#define _ROMTABLE_PID0_REVMAJOR_SHIFT       0            /**< CHIP MAJOR Revison, shift */
#define _ROMTABLE_PID1_FAMILYMSB_MASK       0x0000000FUL /**< Most Significant Bits [5:2] of CHIP FAMILY, mask */
#define _ROMTABLE_PID1_FAMILYMSB_SHIFT      0            /**< Most Significant Bits [5:2] of CHIP FAMILY, shift */
#define _ROMTABLE_PID2_REVMINORMSB_MASK     0x000000F0UL /**< Most Significant Bits [7:4] of CHIP MINOR revision, mask */
#define _ROMTABLE_PID2_REVMINORMSB_SHIFT    4            /**< Most Significant Bits [7:4] of CHIP MINOR revision, mask */
#define _ROMTABLE_PID3_REVMINORLSB_MASK     0x000000F0UL /**< Least Significant Bits [3:0] of CHIP MINOR revision, mask */
#define _ROMTABLE_PID3_REVMINORLSB_SHIFT    4            /**< Least Significant Bits [3:0] of CHIP MINOR revision, shift */

/** @} End of group EFM32G_ROMTABLE */


