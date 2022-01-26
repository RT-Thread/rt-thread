////////////////////////////////////////////////////////////////////////////////
/// @file     hal_bkp.c
/// @author   AE TEAM
/// @brief    THIS FILE PROVIDES ALL THE BKP FIRMWARE FUNCTIONS.
////////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

// Define to prevent recursive inclusion
#define _HAL_BKP_C_

// Files includes
#include "types.h"
#include "hal_pwr.h"
#include "hal_rcc.h"
#include "hal_bkp.h"



////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup BKP_HAL
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup BKP_Exported_Functions
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Deinitializes the BKP peripheral registers to their default reset
///         values.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BKP_DeInit(void)
{
    RCC_BackupResetCmd(ENABLE);
    RCC_BackupResetCmd(DISABLE);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Configures the Tamper Pin active level.
/// @param  tamper_pin_level: specifies the Tamper Pin active level.
///         This parameter can be one of the following values:
/// @arg    BKP_TamperPinLevel_High: Tamper pin active on high level
/// @arg    BKP_TamperPinLevel_Low: Tamper pin active on low level
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BKP_TamperPinLevelConfig(BKPTPAL_Typedef tamper_pin_level)
{
    BKP->CR = tamper_pin_level;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the Tamper Pin activation.
/// @param  state: new state of the Tamper Pin activation.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BKP_TamperPinCmd(FunctionalState state)
{
    (state) ? SET_BIT(BKP->CR, BKP_CR_TPE) : CLEAR_BIT(BKP->CR, BKP_CR_TPE);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Enables or disables the Tamper Pin Interrupt.
/// @param  state: new state of the Tamper Pin Interrupt.
///         This parameter can be: ENABLE or DISABLE.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BKP_ITConfig(FunctionalState state)
{
    (state) ? SET_BIT(BKP->CSR, BKP_CSR_TPIE) : CLEAR_BIT(BKP->CSR, BKP_CSR_TPIE);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Select the RTC output source to output on the Tamper pin.
/// @param  rtc_output_source: specifies the RTC output source.
///         This parameter can be one of the following values:
/// @arg    BKP_RTCOutputSource_None: no RTC output on the Tamper pin.
/// @arg    BKP_RTCOutputSource_CalibClock: output the RTC clock with frequency
///                                          divided by 64 on the Tamper pin.
/// @arg    BKP_RTCOutputSource_Alarm: output the RTC Alarm pulse signal on
///                                     the Tamper pin.
/// @arg    BKP_RTCOutputSource_Second: output the RTC Second pulse signal on
///                                      the Tamper pin.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BKP_RTCOutputConfig(BKPRTCOUTPUTSRC_Typedef rtc_output_source)
{
    MODIFY_REG(BKP->RTCCR, BKP_RTCCR_CCO | BKP_RTCCR_ASOE | BKP_RTCCR_ASOS, rtc_output_source);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Sets RTC Clock Calibration value.
/// @param  calibration_value: specifies the RTC Clock Calibration value.
///         This parameter must be a number between 0 and 0x7F.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BKP_SetRTCCalibrationValue(u8 calibration_value)
{
    MODIFY_REG(BKP->RTCCR, BKP_RTCCR_CAL, calibration_value);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the Tamper Pin Event flag is set or not.
/// @param  None.
/// @retval State: The new state of the Tamper Pin Event flag (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
FlagStatus BKP_GetFlagStatus(void)
{
    return ((BKP->CSR & BKP_CSR_TEF) ? SET : RESET);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears Tamper Pin Event pending flag.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BKP_ClearFlag(void)
{
    SET_BIT(BKP->CSR, BKP_CSR_CTE);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Checks whether the Tamper Pin Interrupt has occurred or not.
/// @param  None.
/// @retval State: The new state of the Tamper Pin Interrupt (SET or RESET).
////////////////////////////////////////////////////////////////////////////////
ITStatus BKP_GetITStatus(void)
{
    return ((BKP->CSR & BKP_CSR_TIF) ? SET : RESET);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Clears Tamper Pin Interrupt pending bit.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BKP_ClearITPendingBit(void)
{
    SET_BIT(BKP->CSR, BKP_CSR_CTI);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Writes user data to the specified data Backup Register.
/// @param  bkp_dr: specifies the data Backup Register.
///         This parameter can be BKP_DRx where x:[1, 10]
/// @param  data: data to write
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void BKP_WriteBackupRegister(BKPDR_Typedef bkp_dr, u16 data)
{
    *(vu16*)(BKP_BASE + bkp_dr) = data;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads data from the specified data Backup Register.
/// @param  bkp_dr: specifies the data Backup Register.
///         This parameter can be BKP_DRx where x:[1, 10]
/// @retval data: The content of the specified data Backup Register
////////////////////////////////////////////////////////////////////////////////
u16 BKP_ReadBackupRegister(BKPDR_Typedef bkp_dr)
{
    return (*(vu16*)(BKP_BASE + bkp_dr));
}
////////////////////////////////////////////////////////////////////////////////
//          Extended function interface
////////////////////////////////////////////////////////////////////////////////
/// @brief  Initializes the BKP peripheral, enable access to the backup
///         registers.
/// @param  None.
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exBKP_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_PWR, ENABLE);
    //COMMON_EnableIpClock(emCLOCK_PWR);
    RCC_APB1PeriphClockCmd(RCC_APB1ENR_BKP, ENABLE);
    //COMMON_EnableIpClock(emCLOCK_BKP);

    RCC->BDCR |= RCC_BDCR_DBP;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Writes user data to the specified data Backup Register immediately.
/// @param  bkp_dr: specifies the data Backup Register.
///         This parameter can be BKP_DRx where x:[1, 10]
/// @param  data: data to write
/// @retval None.
////////////////////////////////////////////////////////////////////////////////
void exBKP_ImmWrite(BKPDR_Typedef bkp_dr, u16 dat)
{
    RCC->BDCR |= RCC_BDCR_DBP;
    *(vu16*)(BKP_BASE + bkp_dr) = dat;
    RCC->BDCR &= ~RCC_BDCR_DBP;

}

////////////////////////////////////////////////////////////////////////////////
/// @brief  Reads data from the specified data Backup Register immediately.
/// @param  bkp_dr: specifies the data Backup Register.
///         This parameter can be BKP_DRx where x:[1, 10]
/// @retval data: The content of the specified data Backup Register
////////////////////////////////////////////////////////////////////////////////
u16 exBKP_ImmRead(BKPDR_Typedef bkp_dr)
{
    u16 dat;
    RCC->BDCR |= RCC_BDCR_DBP;
    dat = (*(vu16*)(BKP_BASE + bkp_dr));
    RCC->BDCR &= ~RCC_BDCR_DBP;
    return dat;
}

/// @}

/// @}

/// @}
