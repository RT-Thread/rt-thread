/***************************************************************************//**
 * @file
 * @brief Advanced encryption standard (AES) accelerator peripheral API for
 *   EFM32.
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
#ifndef __EM_AES_H
#define __EM_AES_H

#include <stdbool.h>
#include "em_part.h"

#if defined(AES_COUNT) && (AES_COUNT > 0)

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup EM_Library
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup AES
 * @{
 ******************************************************************************/

/*******************************************************************************
 ******************************   TYPEDEFS   ***********************************
 ******************************************************************************/

/**
 * @brief
 *   AES counter modification function pointer.
 * @details
 *   Parameters:
 *   @li ctr - Ptr to byte array (16 bytes) holding counter to be modified.
 */
typedef void (*AES_CtrFuncPtr_TypeDef)(uint8_t *ctr);

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void AES_CBC128(uint8_t *out,
                const uint8_t *in,
                unsigned int len,
                const uint8_t *key,
                const uint8_t *iv,
                bool encrypt);

void AES_CBC256(uint8_t *out,
                const uint8_t *in,
                unsigned int len,
                const uint8_t *key,
                const uint8_t *iv,
                bool encrypt);

void AES_CFB128(uint8_t *out,
                const uint8_t *in,
                unsigned int len,
                const uint8_t *key,
                const uint8_t *iv,
                bool encrypt);

void AES_CFB256(uint8_t *out,
                const uint8_t *in,
                unsigned int len,
                const uint8_t *key,
                const uint8_t *iv,
                bool encrypt);

void AES_CTR128(uint8_t *out,
                const uint8_t *in,
                unsigned int len,
                const uint8_t *key,
                uint8_t *ctr,
                AES_CtrFuncPtr_TypeDef ctrFunc);

void AES_CTR256(uint8_t *out,
                const uint8_t *in,
                unsigned int len,
                const uint8_t *key,
                uint8_t *ctr,
                AES_CtrFuncPtr_TypeDef ctrFunc);

void AES_CTRUpdate32Bit(uint8_t *ctr);

void AES_DecryptKey128(uint8_t *out, const uint8_t *in);

void AES_DecryptKey256(uint8_t *out, const uint8_t *in);

void AES_ECB128(uint8_t *out,
                const uint8_t *in,
                unsigned int len,
                const uint8_t *key,
                bool encrypt);

void AES_ECB256(uint8_t *out,
                const uint8_t *in,
                unsigned int len,
                const uint8_t *key,
                bool encrypt);

/***************************************************************************//**
 * @brief
 *   Clear one or more pending AES interrupts.
 *
 * @param[in] flags
 *   Pending AES interrupt source to clear. Use a bitwise logic OR combination of
 *   valid interrupt flags for the AES module (AES_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void AES_IntClear(uint32_t flags)
{
  AES->IFC = flags;
}


/***************************************************************************//**
 * @brief
 *   Disable one or more AES interrupts.
 *
 * @param[in] flags
 *   AES interrupt sources to disable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the AES module (AES_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void AES_IntDisable(uint32_t flags)
{
  AES->IEN &= ~(flags);
}


/***************************************************************************//**
 * @brief
 *   Enable one or more AES interrupts.
 *
 * @note
 *   Depending on the use, a pending interrupt may already be set prior to
 *   enabling the interrupt. Consider using AES_IntClear() prior to enabling
 *   if such a pending interrupt should be ignored.
 *
 * @param[in] flags
 *   AES interrupt sources to enable. Use a bitwise logic OR combination of
 *   valid interrupt flags for the AES module (AES_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void AES_IntEnable(uint32_t flags)
{
  AES->IEN |= flags;
}


/***************************************************************************//**
 * @brief
 *   Get pending AES interrupt flags.
 *
 * @note
 *   The event bits are not cleared by the use of this function.
 *
 * @return
 *   AES interrupt sources pending. A bitwise logic OR combination of valid
 *   interrupt flags for the AES module (AES_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE uint32_t AES_IntGet(void)
{
  return(AES->IF);
}


/***************************************************************************//**
 * @brief
 *   Set one or more pending AES interrupts from SW.
 *
 * @param[in] flags
 *   AES interrupt sources to set to pending. Use a bitwise logic OR combination
 *   of valid interrupt flags for the AES module (AES_IF_nnn).
 ******************************************************************************/
__STATIC_INLINE void AES_IntSet(uint32_t flags)
{
  AES->IFS = flags;
}


void AES_OFB128(uint8_t *out,
                const uint8_t *in,
                unsigned int len,
                const uint8_t *key,
                const uint8_t *iv);

void AES_OFB256(uint8_t *out,
                const uint8_t *in,
                unsigned int len,
                const uint8_t *key,
                const uint8_t *iv);


/** @} (end addtogroup AES) */
/** @} (end addtogroup EM_Library) */

#ifdef __cplusplus
}
#endif

#endif /* __EM_AES_H */

#endif /* defined(AES_COUNT) && (AES_COUNT > 0) */
