/***************************************************************************//**
 * @file
 * @brief Bitband Peripheral API for EFM32
 * @author Energy Micro AS
 * @version 2.3.2
 *******************************************************************************
 * @section License
 * <b>(C) Copyright 2010 Energy Micro AS, http://www.energymicro.com</b>
 *******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
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
#ifndef __EFM32_BITBAND_H
#define __EFM32_BITBAND_H

#include "efm32.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup BITBAND
 * @brief BITBAND Peripheral API for EFM32
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
static __INLINE void BITBAND_Peripheral(volatile uint32_t *addr,
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
static __INLINE void BITBAND_SRAM(uint32_t *addr, uint32_t bit, uint32_t val)
{
  uint32_t tmp = BITBAND_RAM_BASE + (((uint32_t)addr - RAM_MEM_BASE) * 32) + (bit * 4);

  *((volatile uint32_t *)tmp) = (uint32_t)val;
}


/** @} (end addtogroup BITBAND) */
/** @} (end addtogroup EFM32_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EFM32_BITBAND_H */
