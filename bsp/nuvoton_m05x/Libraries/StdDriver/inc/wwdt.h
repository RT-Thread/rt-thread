/**************************************************************************//**
 * @file     wwdt.h
 * @version  V3.00
 * $Revision: 6 $
 * $Date: 14/01/28 10:49a $
 * @brief    M051 series WWDT driver header file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __WWDT_H__
#define __WWDT_H__

#ifdef __cplusplus
extern "C"
{
#endif


/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_WWDT_Driver WWDT Driver
  @{
*/

/** @addtogroup M051_WWDT_EXPORTED_CONSTANTS WWDT Exported Constants
  @{
*/
/*---------------------------------------------------------------------------------------------------------*/
/* WWDTCR Constants Definitions                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define WWDT_PRESCALER_1        (0 << WWDT_WWDTCR_PERIODSEL_Pos)  /*!< Select max time-out period to 1 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_2        (1 << WWDT_WWDTCR_PERIODSEL_Pos)  /*!< Select max time-out period to 2 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_4        (2 << WWDT_WWDTCR_PERIODSEL_Pos)  /*!< Select max time-out period to 4 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_8        (3 << WWDT_WWDTCR_PERIODSEL_Pos)  /*!< Select max time-out period to 8 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_16       (4 << WWDT_WWDTCR_PERIODSEL_Pos)  /*!< Select max time-out period to 16 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_32       (5 << WWDT_WWDTCR_PERIODSEL_Pos)  /*!< Select max time-out period to 32 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_64       (6 << WWDT_WWDTCR_PERIODSEL_Pos)  /*!< Select max time-out period to 64 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_128      (7 << WWDT_WWDTCR_PERIODSEL_Pos)  /*!< Select max time-out period to 128 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_192      (8 << WWDT_WWDTCR_PERIODSEL_Pos)  /*!< Select max time-out period to 192 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_256      (9 << WWDT_WWDTCR_PERIODSEL_Pos)  /*!< Select max time-out period to 256 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_384      (10 << WWDT_WWDTCR_PERIODSEL_Pos) /*!< Select max time-out period to 384 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_512      (11 << WWDT_WWDTCR_PERIODSEL_Pos) /*!< Select max time-out period to 512 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_768      (12 << WWDT_WWDTCR_PERIODSEL_Pos) /*!< Select max time-out period to 768 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_1024     (13 << WWDT_WWDTCR_PERIODSEL_Pos) /*!< Select max time-out period to 1024 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_1536     (14 << WWDT_WWDTCR_PERIODSEL_Pos) /*!< Select max time-out period to 1536 * (64*WWDT_CLK) */
#define WWDT_PRESCALER_2048     (15 << WWDT_WWDTCR_PERIODSEL_Pos) /*!< Select max time-out period to 2048 * (64*WWDT_CLK) */

#define WWDT_RELOAD_WORD        (0x00005AA5)                      /*!< Fill this value to WWDTRLD register to reload WWDT counter */

/*@}*/ /* end of group M051_WWDT_EXPORTED_CONSTANTS */


/** @addtogroup M051_WWDT_EXPORTED_FUNCTIONS WWDT Exported Functions
  @{
*/

/**
  * @details    This macro clear WWDT counter time-out reset system flag.
  */
#define WWDT_CLEAR_RESET_FLAG()     (WWDT->WWDTSR = WWDT_WWDTSR_WWDTRF_Msk)

/**
  * @details    This macro clear WWDT counter compare match interrupt flag.
  */
#define WWDT_CLEAR_INT_FLAG()       (WWDT->WWDTSR = WWDT_WWDTSR_WWDTIF_Msk)

/**
  * @brief      Get WWDT Reset Flag
  *
  * @return     WWDT counter time-out reset system or not
  * @retval     0   WWDT did not cause system reset
  * @retval     1   WWDT counter time-out caused system reset
  *
  * @details    This macro is used to indicate WWDT counter time-out reset system flag.
  */
#define WWDT_GET_RESET_FLAG()       ((((WWDT->WWDTSR) & WWDT_WWDTSR_WWDTRF_Msk) == WWDT_WWDTSR_WWDTRF_Msk)? 1:0)

/**
  * @brief      Get WWDT Compared Match Interrupt Flag
  *
  * @return     WWDT compare match interrupt occurred or not
  * @retval     0   WWDT counter compare match interrupt did not occur
  * @retval     1   WWDT counter compare match interrupt occurred
  *
  * @details    This macro indicate WWDT counter compare match interrupt occurred or not.
  */
#define WWDT_GET_INT_FLAG()         ((((WWDT->WWDTSR) & WWDT_WWDTSR_WWDTIF_Msk) == WWDT_WWDTSR_WWDTIF_Msk)? 1:0)

/**
  * @details    This macro to reflects the current WWDT counter value.
  */
#define WWDT_GET_COUNTER()          (WWDT->WWDTCVR)

/**
  * @details    This macro is used to reload the WWDT counter value to 0x3F.
  * @note       After WWDT enabled, application must reload WWDT counter while current counter is less than compare value \n
  *             and larger than 0, otherwise WWDT will cause system reset immediately.
  */
#define WWDT_RELOAD_COUNTER()       (WWDT->WWDTRLD = WWDT_RELOAD_WORD)

void WWDT_Open(uint32_t u32PreScale, uint32_t u32CmpValue, uint32_t u32EnableInt);

/*@}*/ /* end of group M051_WWDT_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_WWDT_Driver */

/*@}*/ /* end of group M051_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__WWDT_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
