/**************************************************************************//**
 * @file     nu_ewwdt.h
 * @version  V3.00
 * @brief    Extra Window Watchdog Timer(EWWDT) driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_EWWDT_H__
#define __NU_EWWDT_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EWWDT_Driver EWWDT Driver
  @{
*/

/** @addtogroup EWWDT_EXPORTED_CONSTANTS EWWDT Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  EWWDT Prescale Period Constant Definitions                                                             */
/*---------------------------------------------------------------------------------------------------------*/
#define EWWDT_PRESCALER_1        (0 << EWWDT_CTL_PSCSEL_Pos)  /*!< Select max time-out period to 1 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_2        (1 << EWWDT_CTL_PSCSEL_Pos)  /*!< Select max time-out period to 2 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_4        (2 << EWWDT_CTL_PSCSEL_Pos)  /*!< Select max time-out period to 4 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_8        (3 << EWWDT_CTL_PSCSEL_Pos)  /*!< Select max time-out period to 8 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_16       (4 << EWWDT_CTL_PSCSEL_Pos)  /*!< Select max time-out period to 16 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_32       (5 << EWWDT_CTL_PSCSEL_Pos)  /*!< Select max time-out period to 32 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_64       (6 << EWWDT_CTL_PSCSEL_Pos)  /*!< Select max time-out period to 64 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_128      (7 << EWWDT_CTL_PSCSEL_Pos)  /*!< Select max time-out period to 128 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_192      (8 << EWWDT_CTL_PSCSEL_Pos)  /*!< Select max time-out period to 192 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_256      (9 << EWWDT_CTL_PSCSEL_Pos)  /*!< Select max time-out period to 256 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_384      (10 << EWWDT_CTL_PSCSEL_Pos) /*!< Select max time-out period to 384 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_512      (11 << EWWDT_CTL_PSCSEL_Pos) /*!< Select max time-out period to 512 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_768      (12 << EWWDT_CTL_PSCSEL_Pos) /*!< Select max time-out period to 768 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_1024     (13 << EWWDT_CTL_PSCSEL_Pos) /*!< Select max time-out period to 1024 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_1536     (14 << EWWDT_CTL_PSCSEL_Pos) /*!< Select max time-out period to 1536 * (64*EWWDT_CLK) \hideinitializer */
#define EWWDT_PRESCALER_2048     (15 << EWWDT_CTL_PSCSEL_Pos) /*!< Select max time-out period to 2048 * (64*EWWDT_CLK) \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  EWWDT Reload Counter Keyword Constant Definitions                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define EWWDT_RELOAD_WORD        (0x00005AA5UL)         /*!< Fill this value to EWWDT_RLDCNT register to reload EWWDT counter \hideinitializer */

/**@}*/ /* end of group EWWDT_EXPORTED_CONSTANTS */


/** @addtogroup EWWDT_EXPORTED_FUNCTIONS EWWDT Exported Functions
  @{
*/

/**
  * @brief      Clear EWWDT Reset System Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to clear EWWDT time-out reset system flag.
  * \hideinitializer
  */
#define EWWDT_CLEAR_RESET_FLAG()     (EWWDT->STATUS = EWWDT_STATUS_WWDTRF_Msk)

/**
  * @brief      Clear EWWDT Compared Match Interrupt Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to clear EWWDT compared match interrupt flag.
  * \hideinitializer
  */
#define EWWDT_CLEAR_INT_FLAG()       (EWWDT->STATUS = EWWDT_STATUS_WWDTIF_Msk)

/**
  * @brief      Get EWWDT Reset System Flag
  *
  * @param      None
  *
  * @retval     0   EWWDT time-out reset system did not occur
  * @retval     1   EWWDT time-out reset system occurred
  *
  * @details    This macro is used to indicate system has been reset by EWWDT time-out reset or not.
  * \hideinitializer
  */
#define EWWDT_GET_RESET_FLAG()       ((EWWDT->STATUS & EWWDT_STATUS_WWDTRF_Msk)? 1 : 0)

/**
  * @brief      Get EWWDT Compared Match Interrupt Flag
  *
  * @param      None
  *
  * @retval     0   EWWDT compare match interrupt did not occur
  * @retval     1   EWWDT compare match interrupt occurred
  *
  * @details    This macro is used to indicate EWWDT counter value matches CMPDAT value or not.
  * \hideinitializer
  */
#define EWWDT_GET_INT_FLAG()         ((EWWDT->STATUS & EWWDT_STATUS_WWDTIF_Msk)? 1 : 0)

/**
  * @brief      Get EWWDT Counter
  *
  * @param      None
  *
  * @return     EWWDT Counter Value
  *
  * @details    This macro reflects the current EWWDT counter value.
  * \hideinitializer
  */
#define EWWDT_GET_COUNTER()          (EWWDT->CNT)

/**
  * @brief      Reload EWWDT Counter
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to reload the EWWDT counter value to 0x3F.
  * @note       User can only write EWWDT_RLDCNT register to reload EWWDT counter value when current EWWDT counter value \n
  *             between 0 and CMPDAT value. If user writes EWWDT_RLDCNT when current EWWDT counter value is larger than CMPDAT, \n
  *             EWWDT reset signal will generate immediately to reset system.
  * \hideinitializer
  */
#define EWWDT_RELOAD_COUNTER()       (EWWDT->RLDCNT = EWWDT_RELOAD_WORD)

void EWWDT_Open(uint32_t u32PreScale, uint32_t u32CmpValue, uint32_t u32EnableInt);

/**@}*/ /* end of group EWWDT_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group EWWDT_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_EWWDT_H__ */
