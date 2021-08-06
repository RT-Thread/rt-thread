////////////////////////////////////////////////////////////////////////////////
/// @file     hal_pwr.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE PWR
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
#ifndef __HAL_PWR_H
#define __HAL_PWR_H

// Files includes
#include "types.h"
#include "reg_pwr.h"
#include "reg_syscfg.h"
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup PWR_HAL
/// @brief PWR HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup PWR_Exported_Types
/// @{

typedef enum {
    emWUP_Pin1 = 0,
    emWUP_Pin2 = 1,
    emWUP_Pin3,
    emWUP_Pin4,
    emWUP_Pin5,
    emWUP_Pin6,
} emWUP_Pin_Typedef;
////////////////////////////////////////////////////////////////////////////////
/// @brief PVD_detection_level

typedef enum {
    emPVD_LEVEL0  = SYSCFG_PDETCSR_PLS_1V7,
    emPVD_LEVEL1  = SYSCFG_PDETCSR_PLS_2V0,
    emPVD_LEVEL2  = SYSCFG_PDETCSR_PLS_2V3,
    emPVD_LEVEL3  = SYSCFG_PDETCSR_PLS_2V6,
    emPVD_LEVEL4  = SYSCFG_PDETCSR_PLS_2V9,
    emPVD_LEVEL5  = SYSCFG_PDETCSR_PLS_3V2,
    emPVD_LEVEL6  = SYSCFG_PDETCSR_PLS_3V5,
    emPVD_LEVEL7  = SYSCFG_PDETCSR_PLS_3V8,
    emPVD_LEVEL8  = SYSCFG_PDETCSR_PLS_4V1,
    emPVD_LEVEL9  = SYSCFG_PDETCSR_PLS_4V4,
    emPVD_LEVEL10 = SYSCFG_PDETCSR_PLS_4V7
} emPVD_Level_Typedef;
#define PWR_PVDLevel_1V7          SYSCFG_PDETCSR_PLS_1V7
#define PWR_PVDLevel_2V0          SYSCFG_PDETCSR_PLS_2V0
#define PWR_PVDLevel_2V3          SYSCFG_PDETCSR_PLS_2V3
#define PWR_PVDLevel_2V6          SYSCFG_PDETCSR_PLS_2V6
#define PWR_PVDLevel_2V9          SYSCFG_PDETCSR_PLS_2V9
#define PWR_PVDLevel_3V2          SYSCFG_PDETCSR_PLS_3V2
#define PWR_PVDLevel_3V5          SYSCFG_PDETCSR_PLS_3V5
#define PWR_PVDLevel_3V8          SYSCFG_PDETCSR_PLS_3V8
#define PWR_PVDLevel_4V1          SYSCFG_PDETCSR_PLS_4V1
#define PWR_PVDLevel_4V4          SYSCFG_PDETCSR_PLS_4V4
#define PWR_PVDLevel_4V7          SYSCFG_PDETCSR_PLS_4V7
/// @brief Regulator_state_is_STOP_mode
typedef enum {
    PWR_Regulator_ON       = 0x00000000,
    PWR_Regulator_LowPower = 0x00000001

} emPWR_Reg_Stop_mode_Typedef;

/// @brief STOP_mode_entry
typedef enum {
    PWR_STOPEntry_WFI = 0x00000001,
    PWR_STOPEntry_WFE = 0x00000002

} emPWR_STOP_ModeEn_Typedef;

/// @brief Low Power Mode
typedef enum {
    LP_STOP_MODE    = 0,
    LP_SLEEP_MODE   = 1,
    LP_STANDBY_MODE = 2
} emPWR_LP_Mode_Typedef;

/// @brief Wait_for_mode
typedef enum {
    LP_WFI,
    LP_WFE
} emPWR_Wait_Mode_Typedef;
//typedef enum {
//    PWR_FLAG_WU   = PWR_CSR_WUF,
//    PWR_FLAG_SB   = PWR_CSR_SBF,

//    PWR_FLAG_PVDO = PWR_CSR_PVDO


//} emPWR_PWR_Flag_Typedef;


/// @}

///////////////////////////////////////////////////////////////////////////////
/// @defgroup PWR_Exported_Variables
/// @{

#ifdef _HAL_PWR_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup PWR_Exported_Functions
/// @{

void PWR_DeInit(void);

void PWR_BackupAccessCmd(FunctionalState state);

void PWR_PVDCmd(FunctionalState state);
void PWR_PVDLevelConfig(emPVD_Level_Typedef pvd_level);
void PWR_WakeUpPinCmd(FunctionalState state);
void PWR_EnterSTOPMode(emPWR_Reg_Stop_mode_Typedef regulator, emPWR_STOP_ModeEn_Typedef stop_entry);
void PWR_EnterSTANDBYMode(void);


void PWR_ClearFlag(u32 flag);
FlagStatus PWR_GetFlagStatus(u32 flag);
FlagStatus PWR_GetPVDOFlagStatus(u32 flag);
void exPWR_EnterLowPowerMode(emPWR_LP_Mode_Typedef lp_mode, emPWR_Wait_Mode_Typedef wait_mode);

/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif // __HAL_PWR_H 
////////////////////////////////////////////////////////////////////////////////
