////////////////////////////////////////////////////////////////////////////////
/// @file     hal_misc.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE NVIC
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
#ifndef __HAL_MISC_H
#define __HAL_MISC_H

// Files includes
#include "types.h"
#include "reg_common.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup NVIC_HAL
/// @brief NVIC HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup NVIC_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  NVIC Init Structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    u8 NVIC_IRQChannel;
    u8 NVIC_IRQChannelPreemptionPriority;
    u8 NVIC_IRQChannelSubPriority;
    FunctionalState NVIC_IRQChannelCmd;
} NVIC_InitTypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  NVIC New Init Structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    u8              NVIC_IRQChannel;
    u8              NVIC_IRQChannelPreemptionPriority;                          // Cortex-M0 not used
    u8              NVIC_IRQChannelSubPriority;
    FunctionalState NVIC_IRQChannelCmd;
} exNVIC_Init_TypeDef;

/// @}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @defgroup NVIC_Exported_Constants
/// @{

#define NVIC_VectTab_RAM        (0x20000000U)
#define NVIC_VectTab_FLASH      (0x08000000U)

#define NVIC_LP_SEVONPEND       (0x10U)
#define NVIC_LP_SLEEPDEEP       (0x04U)
#define NVIC_LP_SLEEPONEXIT     (0x02U)

#define NVIC_PriorityGroup_0     (0x0700U) // 0 bits for pre-emption priority 4 bits for subpriority 
#define NVIC_PriorityGroup_1     (0x0600U) // 1 bits for pre-emption priority 3 bits for subpriority 
#define NVIC_PriorityGroup_2     (0x0500U) // 2 bits for pre-emption priority 2 bits for subpriority 
#define NVIC_PriorityGroup_3     (0x0400U) // 3 bits for pre-emption priority 1 bits for subpriority 
#define NVIC_PriorityGroup_4     (0x0300U) // 4 bits for pre-emption priority 0 bits for subpriority 

#define AIRCR_VECTKEY_MASK (0x05FA0000U)

#define SysTick_CLKSource_HCLK_Div8     (0xFFFFFFFBU)


#define SysTick_CLKSource_EXTCLK        (0xFFFFFFFBU)
#define SysTick_CLKSource_HCLK          (0x00000004U)
/// @}



////////////////////////////////////////////////////////////////////////////////
/// @defgroup NVIC_Exported_Variables
/// @{

#ifdef _HAL_NVIC_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup NVIC_Exported_Functions
/// @{

void NVIC_PriorityGroupConfig(u32 priority_group);
void NVIC_SetVectorTable(u32 vect_tab, u32 offset);

void NVIC_SystemLPConfig(u8 low_power_mode, FunctionalState state);
void NVIC_Init(NVIC_InitTypeDef* init_struct);

void SysTick_CLKSourceConfig(u32 systick_clk_source);

void exNVIC_Init(exNVIC_Init_TypeDef* init_struct);

/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif // __HAL_NVIC_H 
////////////////////////////////////////////////////////////////////////////////
