/**************************************************************************//**
 * @file     wdt.h
 * @brief    NUC980 series WDT driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_WDT_H__
#define __NU_WDT_H__
#include "N9H30.h"

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup WDT_Driver WDT Driver
  @{
*/

/** @addtogroup WDT_EXPORTED_CONSTANTS WDT Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/*  WDT Time-out Interval Period Constant Definitions                                                      */
/*---------------------------------------------------------------------------------------------------------*/
#define WDT_TIMEOUT_2POW4           (0UL << 8) /*!< Setting WDT time-out interval to  2^4 * WDT clocks */
#define WDT_TIMEOUT_2POW6           (1UL << 8) /*!< Setting WDT time-out interval to  2^6 * WDT clocks */
#define WDT_TIMEOUT_2POW8           (2UL << 8) /*!< Setting WDT time-out interval to  2^8 * WDT clocks */
#define WDT_TIMEOUT_2POW10          (3UL << 8) /*!< Setting WDT time-out interval to 2^10 * WDT clocks */
#define WDT_TIMEOUT_2POW12          (4UL << 8) /*!< Setting WDT time-out interval to 2^12 * WDT clocks */
#define WDT_TIMEOUT_2POW14          (5UL << 8) /*!< Setting WDT time-out interval to 2^14 * WDT clocks */
#define WDT_TIMEOUT_2POW16          (6UL << 8) /*!< Setting WDT time-out interval to 2^16 * WDT clocks */
#define WDT_TIMEOUT_2POW18          (7UL << 8) /*!< Setting WDT time-out interval to 2^18 * WDT clocks */

/*---------------------------------------------------------------------------------------------------------*/
/*  WDT  Reset Delay Period Constant Definitions                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define WDT_RESET_DELAY_1026CLK     (0UL) /*!< Setting WDT reset delay period to 1026 * WDT clocks */
#define WDT_RESET_DELAY_130CLK      (1UL) /*!< Setting WDT reset delay period to  130 * WDT clocks */
#define WDT_RESET_DELAY_18CLK       (2UL) /*!< Setting WDT reset delay period to   18 * WDT clocks */
#define WDT_RESET_DELAY_3CLK        (3UL) /*!< Setting WDT reset delay period to    3 * WDT clocks */

/*@}*/ /* end of group WDT_EXPORTED_CONSTANTS */


/** @addtogroup WDT_EXPORTED_FUNCTIONS WDT Exported Functions
  @{
*/

/**
  * @brief      Clear WDT Reset System Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro clears WDT time-out reset system flag.
  *
  * \hideinitializer
  */
#define WDT_CLEAR_RESET_FLAG()          outpw(REG_WDT_CTL, (inpw(REG_WDT_CTL) & ~0x8) | 0x04)

/**
  * @brief      Clear WDT Time-out Interrupt Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro clears WDT time-out interrupt flag.
  *
  * \hideinitializer
  */
#define WDT_CLEAR_TIMEOUT_INT_FLAG()    outpw(REG_WDT_CTL, (inpw(REG_WDT_CTL) & ~0x4) | 0x08)

/**
  * @brief      Get WDT Time-out Reset Flag
  *
  * @param      None
  *
  * @retval     0   WDT time-out reset system did not occur
  * @retval     1   WDT time-out reset system occurred
  *
  * @details    This macro indicates system has been reset by WDT time-out reset or not.
  *
  * \hideinitializer
  */
#define WDT_GET_RESET_FLAG()            (inpw(REG_WDT_CTL) & 0x4 ? 1 : 0)

/**
  * @brief      Get WDT Time-out Interrupt Flag
  *
  * @param      None
  *
  * @retval     0   WDT time-out interrupt did not occur
  * @retval     1   WDT time-out interrupt occurred
  *
  * @details    This macro indicates WDT time-out interrupt occurred or not.
  *
  * \hideinitializer
  */
#define WDT_GET_TIMEOUT_INT_FLAG()      (inpw(REG_WDT_CTL) & 0x8 ? 1 : 0)

/**
  * @brief      Reset WDT Counter
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to reset the internal 18-bit WDT up counter value.
  * @note       If WDT is activated and time-out reset system function is enabled also, user should \n
  *             reset the 18-bit WDT up counter value to avoid generate WDT time-out reset signal to \n
  *             reset system before the WDT time-out reset delay period expires.
  *
  * \hideinitializer
  */
#define WDT_RESET_COUNTER()   outpw(REG_WDT_CTL, inpw(REG_WDT_CTL) | (0x1))

/**
  * @brief      Stop WDT Counting
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This function will stop WDT counting and disable WDT module.
  */
static __inline void WDT_Close(void)
{
    outpw(REG_WDT_CTL, 0);
    return;
}

/**
  * @brief      Enable WDT Time-out Interrupt
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This function will enable the WDT time-out interrupt function.
  */
static __inline void WDT_EnableInt(void)
{
    outpw(REG_WDT_CTL, inpw(REG_WDT_CTL) | 0x40);
    return;
}

/**
  * @brief      Disable WDT Time-out Interrupt
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This function will disable the WDT time-out interrupt function.
  */
static __inline void WDT_DisableInt(void)
{
    /* Do not touch another write 1 clear bits */
    outpw(REG_WDT_CTL, (inpw(REG_WDT_CTL) & ~0x6C) | 0x04);
    return;
}

void WDT_Open(UINT32 u32TimeoutInterval, UINT32 u32ResetDelay, UINT32 u32EnableReset, UINT32 u32EnableWakeup);

/*@}*/ /* end of group WDT_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group WDT_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

#endif /* __NU_WDT_H__ */

