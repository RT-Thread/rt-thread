/**************************************************************************//**
 * @file     nu_rng.h
 * @version  V3.00
 * @brief    Random Number Generator Interface Controller (rng) driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_RNG_H__
#define __NU_RNG_H__


#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup RNG_Driver RNG Driver
  @{
*/

/** @addtogroup RNG_EXPORTED_CONSTANTS RNG Exported Constants
  @{
*/

/**@}*/ /* end of group RNG_EXPORTED_CONSTANTS */


/** @addtogroup RNG_EXPORTED_FUNCTIONS RNG Exported Functions
  @{
*/

int32_t RNG_Open(void);
int32_t RNG_Random(uint32_t *pu32Buf, int32_t nWords);

int32_t RNG_ECDSA_Init(uint32_t u32KeySize, uint32_t au32ECC_N[18]);
int32_t RNG_ECDSA(uint32_t u32KeySize);
int32_t RNG_ECDH_Init(uint32_t u32KeySize, uint32_t au32ECC_N[18]);
int32_t RNG_ECDH(uint32_t u32KeySize);

/**@}*/ /* end of group RNG_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group RNG_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_RNG_H__ */

