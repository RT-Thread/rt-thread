/***************************************************************************//**
 * @file
 * @brief On-board Flash controller module peripheral API for EFM32
 *   devices.
 * @author Energy Micro AS
 * @version 1.3.0
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
#ifndef __EFM32_MSC_H
#define __EFM32_MSC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "efm32.h"
#include "core_cm3.h"
#include <stdint.h>

/***************************************************************************//**
 * @addtogroup EFM32_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup MSC
 * @brief EFM32 Flash controller utilities.
 * @{
 ******************************************************************************/

/*******************************************************************************
 *************************   DEFINES   *****************************************
 ******************************************************************************/

/**
 * @brief
 *    The timeout used while waiting for the flash to become ready after
 *    a write. This number indicates the number of iterations to perform before
 *    issuing a timeout.
 * @note
 *    This timeout is set very large (in the order of 100x longer than
 *    necessary). This is to avoid any corner cases.
 *
 */
#define MSC_PROGRAM_TIMEOUT    10000000ul

/*******************************************************************************
 *************************   TYPEDEFS   ****************************************
 ******************************************************************************/

/** Return codes for writing/erasing the flash */
typedef enum
{
  mscReturnOk          = 0,  /**< Flash write/erase successful. */
  mscReturnInvalidAddr = -1, /**< Invalid address. Write to an address that is not flash. */
  mscReturnLocked      = -2, /**< Flash address is locked. */
  mscReturnTimeOut     = -3, /**< Timeout while writing to flash. */
  mscReturnUnaligned   = -4  /**< Unaligned access to flash. */
} msc_Return_TypeDef;


/*******************************************************************************
 *************************   PROTOTYPES   **************************************
 ******************************************************************************/

void MSC_Deinit(void);
void MSC_Init(void);

/***************************************************************************//**
 * @brief
 *    Clear one or more pending MSC interrupts.
 *
 * @param[in] flags
 *    Pending MSC intterupt source to clear. Use a logical OR combination of
 *    valid interrupt flags for the MSC module (MSC_IF_nnn).
 ******************************************************************************/
static __INLINE void MSC_IntClear(uint32_t flags)
{
  MSC->IFC = flags;
}

/***************************************************************************//**
 * @brief
 *   Disable one or more MSC interrupts.
 *
 * @param[in] flags
 *   MSC interrupt sources to disable. Use a logical OR combination of
 *   valid interrupt flags for the MSC module (MSC_IF_nnn).
 ******************************************************************************/
static __INLINE void MSC_IntDisable(uint32_t flags)
{
  MSC->IEN &= ~(flags);
}


/***************************************************************************//**
 * @brief
 *   Enable one or more MSC interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using MSC_IntClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] flags
 *   MSC interrupt sources to enable. Use a logical OR combination of
 *   valid interrupt flags for the MSC module (MSC_IF_nnn).
 ******************************************************************************/
static __INLINE void MSC_IntEnable(uint32_t flags)
{
  MSC->IEN |= flags;
}


/***************************************************************************//**
 * @brief
 *   Get pending MSV interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @return
 *   MSC interrupt sources pending. A logical OR combination of valid
 *   interrupt flags for the MSC module (MSC_IF_nnn).
 ******************************************************************************/
static __INLINE uint32_t MSC_IntGet(void)
{
  return(MSC->IF);
}


/***************************************************************************//**
 * @brief
 *   Set one or more pending MSC interrupts from SW.
 *
 * @param[in] flags
 *   MSC interrupt sources to set to pending. Use a logical OR combination of
 *   valid interrupt flags for the MSC module (MSC_IF_nnn).
 ******************************************************************************/
static __INLINE void MSC_IntSet(uint32_t flags)
{
  MSC->IFS = flags;
}

#ifdef __CC_ARM  /* MDK-ARM compiler */
msc_Return_TypeDef MSC_WriteWord(uint32_t *address, void *data, int numBytes);
msc_Return_TypeDef MSC_ErasePage(uint32_t *startAddress);
#endif /* __CC_ARM */

#ifdef __ICCARM__ /* IAR compiler */
__ramfunc msc_Return_TypeDef MSC_WriteWord(uint32_t *address, void *data, int numBytes);
__ramfunc msc_Return_TypeDef MSC_ErasePage(uint32_t *startAddress);
#endif /* __ICCARM__ */

#ifdef __GNUC__  /* GCC based compilers */
#ifdef __CROSSWORKS_ARM  /* Rowley Crossworks */
msc_Return_TypeDef MSC_WriteWord(uint32_t *address, void *data, int numBytes) __attribute__ ((section(".fast")));
msc_Return_TypeDef MSC_ErasePage(uint32_t *startAddress) __attribute__ ((section(".fast")));
#else /* Sourcery G++ */
msc_Return_TypeDef MSC_WriteWord(uint32_t *address, void *data, int numBytes) __attribute__ ((section(".ram")));
msc_Return_TypeDef MSC_ErasePage(uint32_t *startAddress) __attribute__ ((section(".ram")));
#endif /* __GNUC__ */
#endif /* __CROSSWORKS_ARM */

/** @} (end addtogroup MSC) */
/** @} (end addtogroup EFM32_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EFM32_MSC_H */
