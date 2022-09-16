/**************************************************************************//**
 * @file     nu_trng.h
 * @version  V3.00
 * @brief    TRNG driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __NU_TRNG_H__
#define __NU_TRNG_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup TRNG_Driver TRNG Driver
  @{
*/


/** @addtogroup M460_TRNG_EXPORTED_MACROS TRNG Exported Macros
  @{
*/

/*----------------------------------------------------------------------------------------------*/
/*  Macros                                                                                      */
/*----------------------------------------------------------------------------------------------*/

/**
  * @brief  Let TRNG engine know the currrent PCLK frequency. The CLKPSC is the peripheral
  *         clock frequency range for the selected value , the CLKPSC setting must be higher
  *         than or equal to the actual peripheral clock frequency (for correct random generation).
  * @param  clkpsc   0: PCLK is 80~100 MHz
  *                  1: PCLK is 60~80 MHz
  *                  2: PCLK is 50~60 MHz
  *                  3: PCLK is 40~50 MHz
  *                  4: PCLK is 30~40 MHz
  *                  5: PCLK is 25~30 MHz
  *                  6: PCLK is 20~25 MHz
  *                  7: PCLK is 15~20 MHz
  *                  8: PCLK is 12~15 MHz
  *                  9: PCLK is 9~12  MHz
  *
  * @return None
  * \hideinitializer
  */
#define TRNG_SET_CLKP(clkpsc) do { TRNG->CTL = (TRNG->CTL&~TRNG_CTL_CLKP_Msk)|((clkpsc & 0xf)<<TRNG_CTL_CLKP_Pos); } while(0);


/*@}*/ /* end of group M460_TRNG_EXPORTED_MACROS */


/** @addtogroup TRNG_EXPORTED_FUNCTIONS TRNG Exported Functions
  @{
*/


/*---------------------------------------------------------------------------------------------------------*/
/*  Functions                                                                                      */
/*---------------------------------------------------------------------------------------------------------*/

int32_t TRNG_Open(void);
int32_t TRNG_GenWord(uint32_t *u32RndNum);
int32_t TRNG_GenBignum(uint8_t u8BigNum[], int32_t i32Len);
int32_t TRNG_GenBignumHex(char cBigNumHex[], int32_t i32Len);


/*@}*/ /* end of group TRNG_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group TRNG_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif  /* __NU_TRNG_H__ */
