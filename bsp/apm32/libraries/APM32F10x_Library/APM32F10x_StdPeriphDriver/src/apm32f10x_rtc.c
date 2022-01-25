/*!
 * @file       apm32f10x_rtc.c
 *
 * @brief      This file provides all the RTC firmware functions
 *
 * @version    V1.0.1
 *
 * @date       2021-03-23
 *
 */
#include "apm32f10x_rtc.h"

/** @addtogroup Peripherals_Library Standard Peripheral Library
  @{
*/

/** @addtogroup RTC_Driver RTC Driver
  @{
*/

/** @addtogroup RTC_Fuctions Fuctions
  @{
*/

/*!
 * @brief     Enter RTC configuration mode.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_EnableConfigMode(void)
{
    RTC->CSTS_B.CFGMFLG = BIT_SET;
}

/*!
 * @brief     Exit RTC configuration mode.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_DisableConfigMode(void)
{
    RTC->CSTS_B.CFGMFLG = BIT_RESET;
}

/*!
 * @brief     Read the RTC counter value.
 *
 * @param     None
 *
 * @retval    RTC counter value.
 */
uint32_t RTC_ReadCounter(void)
{
    return (((RTC->CNTH_B.CNTH) << 16) | (RTC->CNTL_B.CNTL));
}

/*!
 * @brief     Config the RTC counter value.
 *
 * @param     value: RTC counter new value.
 *
 * @retval    None
 */
void RTC_ConfigCounter(uint32_t value)
{
    RTC_EnableConfigMode();
    RTC->CNTH_B.CNTH = value >> 16;
    RTC->CNTL_B.CNTL = value & 0x0000FFFF;
    RTC_DisableConfigMode();
}

/*!
 * @brief     Config the RTC prescaler value.
 *
 * @param     value: RTC prescaler new value.
 *
 * @retval    None
 */
void RTC_ConfigPrescaler(uint32_t value)
{
    RTC_EnableConfigMode();
    RTC->PSCRLDH_B.PSCRLDH = value >> 16;
    RTC->PSCRLDL_B.PSCRLDL = value & 0x0000FFFF;
    RTC_DisableConfigMode();
}

/*!
 * @brief     Config the RTC alarm value.
 *
 * @param     value: RTC alarm new value.
 *
 * @retval    None
 */
void RTC_ConfigAlarm(uint32_t value)
{
    RTC_EnableConfigMode();
    RTC->ALRH_B.ALRH = value >> 16;
    RTC->ALRL_B.ALRL = value & 0x0000FFFF;
    RTC_DisableConfigMode();
}

/*!
 * @brief     Reads the RTC divider value.
 *
 * @param     None
 *
 * @retval    RTC Divider value.
 */
uint32_t RTC_ReadDivider(void)
{
    return ((RTC->PSCH_B.PSCH & 0x000F) << 16 ) | (RTC->PSCL_B.PSCL);
}

/*!
 * @brief     Waits until last write operation on RTC registers has finished.
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_WaitForLastTask(void)
{
    while(RTC->CSTS_B.OCFLG == BIT_RESET)
    {
    }
}

/*!
 * @brief     Waits until the RTC registers
 *
 * @param     None
 *
 * @retval    None
 */
void RTC_WaitForSynchor(void)
{
    RTC->CSTS_B.RSYNCFLG = BIT_RESET;
    while(RTC->CSTS_B.RSYNCFLG == BIT_RESET)
    {
    }
}

/*!
 * @brief     Enable RTC interrupts.
 *
 * @param     interrupt: RTC interrupt
 *
 * @retval    None
 */
void RTC_EnableInterrupt(uint16_t interrupt)
{
    RTC->CTRL |= interrupt;
}

/*!
 * @brief     Disable RTC interrupts.
 *
 * @param     interrupt: RTC interrupt
 *
 * @retval    None
 */
void RTC_DisableInterrupt(uint16_t interrupt)
{
    RTC->CTRL &= (uint32_t )~interrupt;
}

/*!
 * @brief     Read flag bit
 *
 * @param     flag: Flags to read
 *
 * @retval    flag bit
 */
uint8_t RTC_ReadStatusFlag(RTC_FLAG_T flag)
{
    return  (RTC->CSTS & flag) ? SET : RESET;
}

/*!
 * @brief     Clear flag bit
 *
 * @param     flag: Flags to clear
 *
 * @retval    None
 */
void RTC_ClearStatusFlag(uint16_t flag)
{
    RTC->CSTS &= (uint32_t)~flag;
}

/*!
 * @brief     Read interrupt flag bit is set
 *
 * @param     flag:Flag bit to check
 *
 * @retval    None
 */
uint8_t RTC_ReadIntFlag(RTC_INT_T flag)
{
    return (RTC->CSTS & flag) ? SET : RESET;
}

/*!
 * @brief     Clear RTC interrupt flag bit
 *
 * @param     flag: Clears the specified interrupt flag bit
 *
 * @retval    None
 */
void RTC_ClearIntFlag(uint16_t flag)
{
    RTC->CSTS &= (uint32_t)~flag;
}

/**@} end of group RTC_Fuctions*/
/**@} end of group RTC_Driver*/
/**@} end of group Peripherals_Library*/
