/***************************************************************************//**
 * @file
 * @brief Bitband Peripheral API
 * @author Energy Micro AS
 * @version 3.0.0
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
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
 ******************************************************************************/
#ifndef __EM_BITBAND_H
#define __EM_BITBAND_H

#include "em_part.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup BITBAND
 * @brief BITBAND Peripheral API
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Perform bit-band operation on peripheral memory location.
 *
 * @details
 *   Bit-banding provides atomic read-modify-write cycle for single bit
 *   modification. Please refer to the reference manual for further details
 *   about bit-banding.
 *
 * @param[in,out] addr Peripheral address location to modify bit in.
 *
 * @param[in] bit Bit position to modify, 0-31.
 *
 * @param[in] val Value to set bit to, 0 or 1.
 ******************************************************************************/
__STATIC_INLINE void BITBAND_Peripheral(volatile uint32_t *addr,
                                        uint32_t bit,
                                        uint32_t val)
{
  uint32_t tmp = BITBAND_PER_BASE + (((uint32_t)addr - PER_MEM_BASE) * 32) + (bit * 4);

  *((volatile uint32_t *)tmp) = (uint32_t)val;
}


/***************************************************************************//**
 * @brief
 *   Perform bit-band operation on SRAM memory location.
 *
 * @details
 *   Bit-banding provides atomic read-modify-write cycle for single bit
 *   modification. Please refer to the reference manual for further details
 *   about bit-banding.
 *
 * @param[in,out] addr SRAM address location to modify bit in.
 *
 * @param[in] bit Bit position to modify, 0-31.
 *
 * @param[in] val Value to set bit to, 0 or 1.
 ******************************************************************************/
__STATIC_INLINE void BITBAND_SRAM(uint32_t *addr, uint32_t bit, uint32_t val)
{
  uint32_t tmp = BITBAND_RAM_BASE + (((uint32_t)addr - RAM_MEM_BASE) * 32) + (bit * 4);

  *((volatile uint32_t *)tmp) = (uint32_t)val;
}


/** @} (end addtogroup BITBAND) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EM_BITBAND_H */
