////////////////////////////////////////////////////////////////////////////////
/// @file     hal_syscfg.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE EXTI
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
#ifndef __HAL_SYSCFG_H
#define __HAL_SYSCFG_H

// Files includes
#include "types.h"
#include "mm32_device.h"
#include "hal_exti.h"
////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup SYSCFG_HAL
/// @brief SYSCFG HAL modules
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @defgroup SYSCFG_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  SYSCFG mode enumeration
////////////////////////////////////////////////////////////////////////////////
// @defgroup SYSCFG_Memory_Remap_Config
#define SYSCFG_MemoryRemap_Flash                ((u8)0x00)
#define SYSCFG_MemoryRemap_SystemMemory         ((u8)0x01)
#define SYSCFG_MemoryRemap_SRAM                 ((u8)0x03)




///
/// @}
///




// Exported macro ------------------------------------------------------------
// Exported functions -------------------------------------------------------

//  Function used to set the SYSCFG configuration to the default reset state
#define SYSCFG_DeInit                   EXTI_DeInit
#define SYSCFG_MemoryRemapConfig        EXTI_MemoryRemapConfig
#define SYSCFG_EXTILineConfig           EXTI_LineConfig
u32 SYSCFG_GetPendingIT(u32 ITSourceLine);
void SYSCFG_BreakConfig(u32 SYSCFG_Break);
FlagStatus SYSCFG_GetFlagStatus(u32 SYSCFG_Flag);
void SYSCFG_ClearFlag(u32 SYSCFG_Flag);


/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif //__HAL_SYSCFG_H 
////////////////////////////////////////////////////////////////////////////////



