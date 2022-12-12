////////////////////////////////////////////////////////////////////////////////
/// @file     hal_bkp.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE BKP
///           FIRMWARE LIBRARY.
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
#ifndef __HAL_BKP_H
#define __HAL_BKP_H

// Files includes
#include "types.h"
#include "reg_bkp.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup BKP_HAL
/// @brief BKP HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup BKP_Exported_Types
/// @{
////////////////////////////////////////////////////////////////////////////////
/// @brief  Data_Backup_Register
/// @anchor Data_Backup_Register

typedef enum {
    BKP_DR1  = 0x0010,
    BKP_DR2  = 0x0014,
    BKP_DR3  = 0x0018,
    BKP_DR4  = 0x001C,
    BKP_DR5  = 0x0020,
    BKP_DR6  = 0x0024,
    BKP_DR7  = 0x0028,
    BKP_DR8  = 0x002C,
    BKP_DR9  = 0x0030,
    BKP_DR10 = 0x0034,
    BKP_DR11 = 0x0038,
    BKP_DR12 = 0x003C,
    BKP_DR13 = 0x0040,
    BKP_DR14 = 0x0044,
    BKP_DR15 = 0x0048,
    BKP_DR16 = 0x004C,
    BKP_DR17 = 0x0050,
    BKP_DR18 = 0x0054,
    BKP_DR19 = 0x0058,
    BKP_DR20 = 0x005C
} BKPDR_Typedef;


////////////////////////////////////////////////////////////////////////////////
/// @brief Tamper_Pin_active_level
/// @anchor Tamper_Pin_active_level
typedef enum {
    BKP_TamperPinLevel_High,                                                    ///< Tamper pin active on high level
    BKP_TamperPinLevel_Low = BKP_CR_TPAL,                                       ///< Tamper pin active on low level
} BKPTPAL_Typedef;

////////////////////////////////////////////////////////////////////////////////
/// @brief RTC_output_source_to_output_on_the_Tamper_pin
/// @anchor RTC_output_source_to_output_on_the_Tamper_pin
typedef enum {
    BKP_RTCOutputSource_None       = 0x0000,                                    ///< No RTC output on the Tamper pin
    BKP_RTCOutputSource_CalibClock = 0x0080,                                    ///< Output the RTC clock with frequency divided by 64 on the Tamper pin
    BKP_RTCOutputSource_Alarm      = 0x0100,                                    ///< Output the RTC Alarm pulse signal on the Tamper pin
    BKP_RTCOutputSource_Second     = 0x0300                                     ///< Output the RTC Second pulse signal on the Tamper pin
} BKPRTCOUTPUTSRC_Typedef;


/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup BKP_Exported_Variables
/// @{
#ifdef _HAL_BKP_C_
#define GLOBAL

#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup BKP_Exported_Functions
/// @{

void BKP_WriteBackupRegister(BKPDR_Typedef bkp_dr, u16 data);
u16  BKP_ReadBackupRegister(BKPDR_Typedef bkp_dr);

void BKP_DeInit(void);
void BKP_ClearFlag(void);
void BKP_ClearITPendingBit(void);
void BKP_TamperPinLevelConfig(BKPTPAL_Typedef tamper_pin_level);
void BKP_TamperPinCmd(FunctionalState state);
void BKP_ITConfig(FunctionalState state);
void BKP_RTCOutputConfig(BKPRTCOUTPUTSRC_Typedef rtc_output_source);
void BKP_SetRTCCalibrationValue(u8 calibration_value);

ITStatus   BKP_GetITStatus(void);
FlagStatus BKP_GetFlagStatus(void);
void exBKP_Init(void);
void exBKP_ImmWrite(BKPDR_Typedef bkp_dr, u16 data);
u16  exBKP_ImmRead(BKPDR_Typedef bkp_dr);
/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif // __HAL_BKP_H
////////////////////////////////////////////////////////////////////////////////
