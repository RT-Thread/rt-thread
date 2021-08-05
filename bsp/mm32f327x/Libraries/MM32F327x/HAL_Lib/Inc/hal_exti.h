////////////////////////////////////////////////////////////////////////////////
/// @file     hal_exti.h
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
#ifndef __HAL_EXTI_H
#define __HAL_EXTI_H

// Files includes
#include "types.h"
#include "reg_common.h"
#include "reg_exti.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup EXTI_HAL
/// @brief EXTI HAL modules
/// @{


////////////////////////////////////////////////////////////////////////////////
/// @defgroup EXTI_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  EXTI mode enumeration
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    EXTI_Mode_Interrupt = 0x00,                                                 ///< EXTI interrupt mode
    EXTI_Mode_Event     = 0x04                                                  ///< EXTI event mode
} EXTIMode_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  EXTI Trigger enumeration
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    EXTI_Trigger_Rising = 0x08,                                                 ///< EXTI rising edge triggering
    EXTI_Trigger_Falling = 0x0C,                                                ///< EXTI falling edge triggering
    EXTI_Trigger_Rising_Falling = 0x10                                          ///< EXTI rising and falling edge triggers
} EXTITrigger_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  EXTI Init Structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    u32 EXTI_Line;                                                              ///< Specifies the EXTI lines to be enabled or disabled.
    ///< This parameter can be any combination of @ref EXTI_Lines
    EXTIMode_TypeDef EXTI_Mode;                                                 ///< Specifies the mode for the EXTI lines.
    ///< This parameter can be a value of @ref EXTIMode_TypeDef
    EXTITrigger_TypeDef EXTI_Trigger;                                           ///< Specifies the trigger signal active edge for the EXTI lines.
    ///< This parameter can be a value of @ref EXTIMode_TypeDef
    FunctionalState EXTI_LineCmd;                                               ///< Specifies the new state of the selected EXTI lines.
    ///< This parameter can be set either to ENABLE or DISABLE
} EXTI_InitTypeDef;

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup EXTI_Exported_Constants
/// @{



#define EXTI_LineNone   ((u32)0x0000000)                                        ///< No interrupt selected
#define EXTI_Line0      ((u32)0x0000001)                                        ///< External interrupt line 0
#define EXTI_Line1      ((u32)0x0000002)                                        ///< External interrupt line 1
#define EXTI_Line2      ((u32)0x0000004)                                        ///< External interrupt line 2
#define EXTI_Line3      ((u32)0x0000008)                                        ///< External interrupt line 3
#define EXTI_Line4      ((u32)0x0000010)                                        ///< External interrupt line 4
#define EXTI_Line5      ((u32)0x0000020)                                        ///< External interrupt line 5
#define EXTI_Line6      ((u32)0x0000040)                                        ///< External interrupt line 6
#define EXTI_Line7      ((u32)0x0000080)                                        ///< External interrupt line 7
#define EXTI_Line8      ((u32)0x0000100)                                        ///< External interrupt line 8
#define EXTI_Line9      ((u32)0x0000200)                                        ///< External interrupt line 9
#define EXTI_Line10     ((u32)0x0000400)                                        ///< External interrupt line 10
#define EXTI_Line11     ((u32)0x0000800)                                        ///< External interrupt line 11
#define EXTI_Line12     ((u32)0x0001000)                                        ///< External interrupt line 12
#define EXTI_Line13     ((u32)0x0002000)                                        ///< External interrupt line 13
#define EXTI_Line14     ((u32)0x0004000)                                        ///< External interrupt line 14
#define EXTI_Line15     ((u32)0x0008000)                                        ///< External interrupt line 15
#define EXTI_Line16     ((u32)0x0010000)                                        ///< External interrupt line 16 Connected to the PVD Output
#define EXTI_Line17     ((u32)0x0020000)                                        ///< External interrupt line 17 Connected to the RTC Alarm event
#define EXTI_Line18     ((u32)0x0040000)                                        ///< External interrupt line 18 Connected to the USB Wakeup from suspend event
#define EXTI_Line19     ((u32)0x0080000)                                        ///< External interrupt line 19
#define EXTI_Line20     ((u32)0x0100000)                                        ///< External interrupt line 20
#define EXTI_Line21     ((u32)0x0200000)                                        ///< External interrupt line 21
#define EXTI_Line22     ((u32)0x0400000)                                        ///< External interrupt line 22
#define EXTI_Line23     ((u32)0x0800000)                                        ///< External interrupt line 23
#define EXTI_Line24     ((u32)0x1000000)                                        ///< External interrupt line 24

#define EXTI_PortSourceGPIOA (0x00U)
#define EXTI_PortSourceGPIOB (0x01U)
#define EXTI_PortSourceGPIOC (0x02U)
#define EXTI_PortSourceGPIOD (0x03U)
#define EXTI_PortSourceGPIOE (0x04U)
#define EXTI_PortSourceGPIOF (0x05U)

#define EXTI_PinSource0     (0x00U)
#define EXTI_PinSource1     (0x01U)
#define EXTI_PinSource2     (0x02U)
#define EXTI_PinSource3     (0x03U)
#define EXTI_PinSource4     (0x04U)
#define EXTI_PinSource5     (0x05U)
#define EXTI_PinSource6     (0x06U)
#define EXTI_PinSource7     (0x07U)
#define EXTI_PinSource8     (0x08U)
#define EXTI_PinSource9     (0x09U)
#define EXTI_PinSource10    (0x0AU)
#define EXTI_PinSource11    (0x0BU)
#define EXTI_PinSource12    (0x0CU)
#define EXTI_PinSource13    (0x0DU)
#define EXTI_PinSource14    (0x0EU)
#define EXTI_PinSource15    (0x0FU)



////////////////////////////////////////////////////////////////////////////////
/// @defgroup EXTI_Exported_Variables
/// @{

#ifdef _HAL_EXTI_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif

#undef GLOBAL

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup EXTI_Exported_Functions
/// @{

FlagStatus EXTI_GetFlagStatus(u32 line);
ITStatus   EXTI_GetITStatus(u32 line);

void EXTI_DeInit(void);
void EXTI_Init(EXTI_InitTypeDef* init_struct);
void EXTI_StructInit(EXTI_InitTypeDef* init_struct);
void EXTI_GenerateSWInterrupt(u32 line);
void EXTI_ClearFlag(u32 line);
void EXTI_ClearITPendingBit(u32 line);
void exEXTI_LineDisable(u32 line);
u32  exEXTI_GetAllFlagStatus(void);


void EXTI_MemoryRemapConfig(u32 memory_remap);
void EXTI_LineConfig(u8 port_source_gpio, u8 pin_source);


/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif // __HAL_EXTI_H
////////////////////////////////////////////////////////////////////////////////



