/**************************************************************************//**
 * @file     nu_ewdt.h
 * @version  V3.00
 * @brief    Extra Watchdog Timer(EWDT) driver header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_EWDT_H__
#define __NU_EWDT_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EWDT_Driver EWDT Driver
  @{
*/

/** @addtogroup EWDT_EXPORTED_CONSTANTS EWDT Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  EWDT Time-out Interval Period Constant Definitions                                                     */
/*---------------------------------------------------------------------------------------------------------*/
#define EWDT_TIMEOUT_2POW4           (0UL << EWDT_CTL_TOUTSEL_Pos) /*!< Setting EWDT time-out interval to 2^4 * EWDT clocks \hideinitializer */
#define EWDT_TIMEOUT_2POW6           (1UL << EWDT_CTL_TOUTSEL_Pos) /*!< Setting EWDT time-out interval to 2^6 * EWDT clocks \hideinitializer */
#define EWDT_TIMEOUT_2POW8           (2UL << EWDT_CTL_TOUTSEL_Pos) /*!< Setting EWDT time-out interval to 2^8 * EWDT clocks \hideinitializer */
#define EWDT_TIMEOUT_2POW10          (3UL << EWDT_CTL_TOUTSEL_Pos) /*!< Setting EWDT time-out interval to 2^10 * EWDT clocks \hideinitializer */
#define EWDT_TIMEOUT_2POW12          (4UL << EWDT_CTL_TOUTSEL_Pos) /*!< Setting EWDT time-out interval to 2^12 * EWDT clocks \hideinitializer */
#define EWDT_TIMEOUT_2POW14          (5UL << EWDT_CTL_TOUTSEL_Pos) /*!< Setting EWDT time-out interval to 2^14 * EWDT clocks \hideinitializer */
#define EWDT_TIMEOUT_2POW16          (6UL << EWDT_CTL_TOUTSEL_Pos) /*!< Setting EWDT time-out interval to 2^16 * EWDT clocks \hideinitializer */
#define EWDT_TIMEOUT_2POW18          (7UL << EWDT_CTL_TOUTSEL_Pos) /*!< Setting EWDT time-out interval to 2^18 * EWDT clocks \hideinitializer */
#define EWDT_TIMEOUT_2POW20          (8UL << EWDT_CTL_TOUTSEL_Pos) /*!< Setting EWDT time-out interval to 2^20 * EWDT clocks \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  EWDT Reset Delay Period Constant Definitions                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define EWDT_RESET_DELAY_1026CLK     (0UL << EWDT_ALTCTL_RSTDSEL_Pos) /*!< Setting EWDT reset delay period to 1026 * EWDT clocks \hideinitializer */
#define EWDT_RESET_DELAY_130CLK      (1UL << EWDT_ALTCTL_RSTDSEL_Pos) /*!< Setting EWDT reset delay period to 130 * EWDT clocks \hideinitializer */
#define EWDT_RESET_DELAY_18CLK       (2UL << EWDT_ALTCTL_RSTDSEL_Pos) /*!< Setting EWDT reset delay period to 18 * EWDT clocks \hideinitializer */
#define EWDT_RESET_DELAY_3CLK        (3UL << EWDT_ALTCTL_RSTDSEL_Pos) /*!< Setting EWDT reset delay period to 3 * EWDT clocks \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  EWDT Free Reset Counter Keyword Constant Definitions                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define EWDT_RESET_COUNTER_KEYWORD   (0x00005AA5UL)    /*!< Fill this value to EWDT_RSTCNT register to free reset EWDT counter \hideinitializer */

/**@}*/ /* end of group EWDT_EXPORTED_CONSTANTS */


/** @addtogroup EWDT_EXPORTED_FUNCTIONS EWDT Exported Functions
  @{
*/

/**
  * @brief      Clear EWDT Reset System Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro clears EWDT time-out reset system flag.
  * \hideinitializer
  */
#define EWDT_CLEAR_RESET_FLAG()          (EWDT->CTL = (EWDT->CTL & ~(EWDT_CTL_IF_Msk | EWDT_CTL_WKF_Msk)) | EWDT_CTL_RSTF_Msk)

/**
  * @brief      Clear EWDT Time-out Interrupt Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro clears EWDT time-out interrupt flag.
  * \hideinitializer
  */
#define EWDT_CLEAR_TIMEOUT_INT_FLAG()    (EWDT->CTL = (EWDT->CTL & ~(EWDT_CTL_RSTF_Msk | EWDT_CTL_WKF_Msk)) | EWDT_CTL_IF_Msk)

/**
  * @brief      Clear EWDT Wake-up Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro clears EWDT time-out wake-up system flag.
  * \hideinitializer
  */
#define EWDT_CLEAR_TIMEOUT_WAKEUP_FLAG() (EWDT->CTL = (EWDT->CTL & ~(EWDT_CTL_RSTF_Msk | EWDT_CTL_IF_Msk)) | EWDT_CTL_WKF_Msk)

/**
  * @brief      Get EWDT Time-out Reset Flag
  *
  * @param      None
  *
  * @retval     0   EWDT time-out reset system did not occur
  * @retval     1   EWDT time-out reset system occurred
  *
  * @details    This macro indicates system has been reset by EWDT time-out reset or not.
  * \hideinitializer
  */
#define EWDT_GET_RESET_FLAG()            ((EWDT->CTL & EWDT_CTL_RSTF_Msk)? 1UL : 0UL)

/**
  * @brief      Get EWDT Time-out Interrupt Flag
  *
  * @param      None
  *
  * @retval     0   EWDT time-out interrupt did not occur
  * @retval     1   EWDT time-out interrupt occurred
  *
  * @details    This macro indicates EWDT time-out interrupt occurred or not.
  * \hideinitializer
  */
#define EWDT_GET_TIMEOUT_INT_FLAG()      ((EWDT->CTL & EWDT_CTL_IF_Msk)? 1UL : 0UL)

/**
  * @brief      Get EWDT Time-out Wake-up Flag
  *
  * @param      None
  *
  * @retval     0   EWDT time-out interrupt does not cause CPU wake-up
  * @retval     1   EWDT time-out interrupt event cause CPU wake-up
  *
  * @details    This macro indicates EWDT time-out interrupt event has waked up system or not.
  * \hideinitializer
  */
#define EWDT_GET_TIMEOUT_WAKEUP_FLAG()   ((EWDT->CTL & EWDT_CTL_WKF_Msk)? 1UL : 0UL)

/**
  * @brief      Reset EWDT Counter
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to reset the internal 20-bit EWDT up counter value.
  * @note       If EWDT is activated and time-out reset system function is enabled also, user should \n
  *             reset the 20-bit EWDT up counter value to avoid generate EWDT time-out reset signal to \n
  *             reset system before the EWDT time-out reset delay period expires.
  * \hideinitializer
  */
#define EWDT_RESET_COUNTER()             (EWDT->RSTCNT = EWDT_RESET_COUNTER_KEYWORD)


/*---------------------------------------------------------------------------------------------------------*/
/* static inline functions                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
/* Declare these inline functions here to avoid MISRA C 2004 rule 8.1 error */
__STATIC_INLINE void EWDT_Close(void);
__STATIC_INLINE void EWDT_EnableInt(void);
__STATIC_INLINE void EWDT_DisableInt(void);

/**
  * @brief      Stop EWDT Counting
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This function will stop EWDT counting and disable EWDT module.
  */
__STATIC_INLINE void EWDT_Close(void)
{
    EWDT->CTL = 0UL;
    while((EWDT->CTL & EWDT_CTL_SYNC_Msk) == EWDT_CTL_SYNC_Msk) {} /* Wait disable WDTEN bit completed, it needs 2 * EWDT_CLK. */
}

/**
  * @brief      Enable EWDT Time-out Interrupt
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This function will enable the EWDT time-out interrupt function.
  */
__STATIC_INLINE void EWDT_EnableInt(void)
{
    EWDT->CTL |= EWDT_CTL_INTEN_Msk;
}

/**
  * @brief      Disable EWDT Time-out Interrupt
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This function will disable the EWDT time-out interrupt function.
  */
__STATIC_INLINE void EWDT_DisableInt(void)
{
    /* Do not touch another write 1 clear bits */
    EWDT->CTL &= ~(EWDT_CTL_INTEN_Msk | EWDT_CTL_RSTF_Msk | EWDT_CTL_IF_Msk | EWDT_CTL_WKF_Msk);
}

void EWDT_Open(uint32_t u32TimeoutInterval, uint32_t u32ResetDelay, uint32_t u32EnableReset, uint32_t u32EnableWakeup);

/**@}*/ /* end of group WDT_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group WDT_Driver */

/**@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_EWDT_H__ */

