/**************************************************************************//**
 * @file     wwdt.h
 * @brief    N9H30 WWDT driver header file
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_WWDT_H__
#define __NU_WWDT_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "N9H30.h"

/** @addtogroup N9H30_Device_Driver N9H30 Device Driver
  @{
*/

/** @addtogroup N9H30_WWDT_Driver WWDT Driver
  @{
*/

/** @addtogroup N9H30_WWDT_EXPORTED_CONSTANTS WWDT Exported Constants
  @{
*/
#define WWDT_PRESCALER_1          (0UL << 8)   ///< WWDT setting prescaler to 1     \hideinitializer
#define WWDT_PRESCALER_2          (1UL << 8)   ///< WWDT setting prescaler to 2     \hideinitializer
#define WWDT_PRESCALER_4          (2UL << 8)   ///< WWDT setting prescaler to 4     \hideinitializer
#define WWDT_PRESCALER_8          (3UL << 8)   ///< WWDT setting prescaler to 8     \hideinitializer
#define WWDT_PRESCALER_16         (4UL << 8)   ///< WWDT setting prescaler to 16    \hideinitializer
#define WWDT_PRESCALER_32         (5UL << 8)   ///< WWDT setting prescaler to 32    \hideinitializer
#define WWDT_PRESCALER_64         (6UL << 8)   ///< WWDT setting prescaler to 64    \hideinitializer
#define WWDT_PRESCALER_128        (7UL << 8)   ///< WWDT setting prescaler to 128   \hideinitializer
#define WWDT_PRESCALER_192        (8UL << 8)   ///< WWDT setting prescaler to 192   \hideinitializer
#define WWDT_PRESCALER_256        (9UL << 8)   ///< WWDT setting prescaler to 256   \hideinitializer
#define WWDT_PRESCALER_384        (0xAUL << 8) ///< WWDT setting prescaler to 384   \hideinitializer
#define WWDT_PRESCALER_512        (0xBUL << 8) ///< WWDT setting prescaler to 512   \hideinitializer
#define WWDT_PRESCALER_768        (0xCUL << 8) ///< WWDT setting prescaler to 768   \hideinitializer
#define WWDT_PRESCALER_1024       (0xDUL << 8) ///< WWDT setting prescaler to 1024  \hideinitializer
#define WWDT_PRESCALER_1536       (0xEUL << 8) ///< WWDT setting prescaler to 1536  \hideinitializer
#define WWDT_PRESCALER_2048       (0xFUL << 8) ///< WWDT setting prescaler to 2048  \hideinitializer

#define WWDT_RELOAD_WORD          (0x00005AA5)                     ///< Fill this value to RLD register to reload WWDT counter  \hideinitializer
/*@}*/ /* end of group N9H30_WWDT_EXPORTED_CONSTANTS */


/** @addtogroup N9H30_WWDT_EXPORTED_FUNCTIONS WWDT Exported Functions
  @{
*/

/**
  * @brief This macro clear WWDT time-out reset system flag.
  * @return None
  * \hideinitializer
  */
#define WWDT_CLEAR_RESET_FLAG()  outpw(REG_WWDT_STATUS, 0x2)

/**
  * @brief This macro clear WWDT compare match interrupt flag.
  * @return None
  * \hideinitializer
  */
#define WWDT_CLEAR_INT_FLAG() outpw(REG_WWDT_STATUS, 0x1)

/**
  * @brief This macro is use to get WWDT time-out reset system flag.
  * @return WWDT reset system or not
  * @retval 0 WWDT did not cause system reset
  * @retval 1 WWDT caused system reset
  * \hideinitializer
  */
#define WWDT_GET_RESET_FLAG() (inpw(REG_WWDT_STATUS) & 0x2 ? 1 : 0)

/**
  * @brief This macro is used to indicate WWDT compare match interrupt flag.
  * @return WWDT compare match interrupt occurred or not
  * @retval 0 WWDT compare match interrupt did not occur
  * @retval 1 WWDT compare match interrupt occurred
  * \hideinitializer
  */
#define WWDT_GET_INT_FLAG() (inpw(REG_WWDT_STATUS) & 0x1 ? 1 : 0)

/**
  * @brief This macro to reflects current WWDT counter value
  * @return Return current WWDT counter value
  * \hideinitializer
  */
#define WWDT_GET_COUNTER() inpw(REG_WWDT_CNT)

/**
  * @brief This macro is used to reload the WWDT counter value to 0x3F.
  * @return None
  * @details After WWDT enabled, application must reload WWDT counter while
  *          current counter is less than compare value and larger than 0,
  *          otherwise WWDT will cause system reset.
  * \hideinitializer
  */
#define WWDT_RELOAD_COUNTER() outpw(REG_WWDT_RLDCNT, WWDT_RELOAD_WORD)


void WWDT_Open(UINT u32PreScale, UINT u32CmpValue, UINT u32EnableInt);


/*@}*/ /* end of group N9H30_WWDT_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group N9H30_WWDT_Driver */

/*@}*/ /* end of group N9H30_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__NU_WWDT_H__

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
