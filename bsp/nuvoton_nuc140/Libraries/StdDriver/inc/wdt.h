/**************************************************************************//**
 * @file     wdt.h
 * @version  V3.00
 * $Revision: 2 $
 * $Date: 15/05/04 3:27p $
 * @brief    WDT driver header file
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __WDT_H__
#define __WDT_H__

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
/* WTCR Constants Definitions                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define WDT_TIMEOUT_2POW4           (0UL << WDT_WTCR_WTIS_Pos) /*!< Setting WDT time-out interval to 2^4 * WDT clocks */
#define WDT_TIMEOUT_2POW6           (1UL << WDT_WTCR_WTIS_Pos) /*!< Setting WDT time-out interval to 2^6 * WDT clocks */
#define WDT_TIMEOUT_2POW8           (2UL << WDT_WTCR_WTIS_Pos) /*!< Setting WDT time-out interval to 2^8 * WDT clocks */
#define WDT_TIMEOUT_2POW10          (3UL << WDT_WTCR_WTIS_Pos) /*!< Setting WDT time-out interval to 2^10 * WDT clocks */
#define WDT_TIMEOUT_2POW12          (4UL << WDT_WTCR_WTIS_Pos) /*!< Setting WDT time-out interval to 2^12 * WDT clocks */
#define WDT_TIMEOUT_2POW14          (5UL << WDT_WTCR_WTIS_Pos) /*!< Setting WDT time-out interval to 2^14 * WDT clocks */
#define WDT_TIMEOUT_2POW16          (6UL << WDT_WTCR_WTIS_Pos) /*!< Setting WDT time-out interval to 2^16 * WDT clocks */
#define WDT_TIMEOUT_2POW18          (7UL << WDT_WTCR_WTIS_Pos) /*!< Setting WDT time-out interval to 2^18 * WDT clocks */

/*---------------------------------------------------------------------------------------------------------*/
/* WTCRALT Constants Definitions                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
#define WDT_RESET_DELAY_1026CLK     (0UL << WDT_WTCRALT_WTRDSEL_Pos) /*!< Setting WDT reset delay period to 1026 * WDT clocks */
#define WDT_RESET_DELAY_130CLK      (1UL << WDT_WTCRALT_WTRDSEL_Pos) /*!< Setting WDT reset delay period to 130 * WDT clocks */
#define WDT_RESET_DELAY_18CLK       (2UL << WDT_WTCRALT_WTRDSEL_Pos) /*!< Setting WDT reset delay period to 18 * WDT clocks */
#define WDT_RESET_DELAY_3CLK        (3UL << WDT_WTCRALT_WTRDSEL_Pos) /*!< Setting WDT reset delay period to 3 * WDT clocks */

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
  * @details    This macro clear WDT time-out reset system flag.
  */
#define WDT_CLEAR_RESET_FLAG()          (WDT->WTCR = (WDT->WTCR & ~(WDT_WTCR_WTIF_Msk | WDT_WTCR_WTWKF_Msk)) | WDT_WTCR_WTRF_Msk)

/**
  * @brief      Clear WDT Time-out Interrupt Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro clear WDT time-out interrupt flag.
  */
#define WDT_CLEAR_TIMEOUT_INT_FLAG()    (WDT->WTCR = (WDT->WTCR & ~(WDT_WTCR_WTRF_Msk | WDT_WTCR_WTWKF_Msk)) | WDT_WTCR_WTIF_Msk)

/**
  * @brief      Clear WDT Wake-up Flag
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro clear WDT time-out wake-up system flag.
  */
#define WDT_CLEAR_TIMEOUT_WAKEUP_FLAG() (WDT->WTCR = (WDT->WTCR & ~(WDT_WTCR_WTRF_Msk | WDT_WTCR_WTIF_Msk)) | WDT_WTCR_WTWKF_Msk)

/**
  * @brief      Get WDT Time-out Reset Flag
  *
  * @param      None
  *
  * @retval     0   WDT did not cause system reset
  * @retval     1   WDT caused system reset
  *
  * @details    This macro indicate WDT time-out to reset system or not.
  */
#define WDT_GET_RESET_FLAG()            ((WDT->WTCR & WDT_WTCR_WTRF_Msk)? 1 : 0)

/**
  * @brief      Get WDT Time-out Interrupt Flag
  *
  * @param      None
  *
  * @retval     0   WDT time-out interrupt did not occur
  * @retval     1   WDT time-out interrupt occurred
  *
  * @details    This macro indicate WDT time-out interrupt occurred or not.
  */
#define WDT_GET_TIMEOUT_INT_FLAG()      ((WDT->WTCR & WDT_WTCR_WTIF_Msk)? 1 : 0)

/**
  * @brief      Get WDT Time-out Wake-up Flag
  *
  * @param      None
  *
  * @retval     0   WDT did not wake up system
  * @retval     1   WDT waked up system
  *
  * @details    This macro indicate WDT time-out waked system up or not
  */
#define WDT_GET_TIMEOUT_WAKEUP_FLAG()   ((WDT->WTCR & WDT_WTCR_WTWKF_Msk)? 1 : 0)

/**
  * @brief      Reset WDT Counter
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This macro is used to reset 18-bit WDT counter.
  * @note       If WDT is activated and enabled to reset system, user must reset WDT counter \n
  *             before WDT time-out plus reset delay reached. Or WDT generate a reset signal.
  */
#define WDT_RESET_COUNTER()             (WDT->WTCR  = (WDT->WTCR & ~(WDT_WTCR_WTIF_Msk | WDT_WTCR_WTWKF_Msk | WDT_WTCR_WTRF_Msk)) | WDT_WTCR_WTR_Msk)

/**
  * @brief      Stop WDT Counting
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This function stops WDT counting and disable WDT module.
  */
static __INLINE void WDT_Close(void)
{
    WDT->WTCR = 0;
    return;
}

/**
  * @brief      Enable WDT Time-out Interrupt
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This function enable the WDT time-out interrupt.
  */
static __INLINE void WDT_EnableInt(void)
{
    WDT->WTCR |= WDT_WTCR_WTIE_Msk;
    return;
}

/**
  * @brief      Disable WDT Time-out Interrupt
  *
  * @param      None
  *
  * @return     None
  *
  * @details    This function disables the WDT time-out interrupt.
  */
static __INLINE void WDT_DisableInt(void)
{
    // Do not touch write 1 clear bits
    WDT->WTCR &= ~(WDT_WTCR_WTIE_Msk | WDT_WTCR_WTRF_Msk | WDT_WTCR_WTIF_Msk | WDT_WTCR_WTWKF_Msk);
    return;
}

void WDT_Open(uint32_t u32TimeoutInterval, uint32_t u32ResetDelay, uint32_t u32EnableReset, uint32_t u32EnableWakeup);

/*@}*/ /* end of group WDT_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group WDT_Driver */

/*@}*/ /* end of group Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__WDT_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
