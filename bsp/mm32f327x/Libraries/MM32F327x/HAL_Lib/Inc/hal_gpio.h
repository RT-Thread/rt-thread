////////////////////////////////////////////////////////////////////////////////
/// @file     hal_gpio.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE GPIO
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
#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

// Files includes
#include "types.h"
#include "reg_gpio.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup GPIO_HAL
/// @brief GPIO HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup GPIO_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief  Output Maximum frequency selection
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    GPIO_Speed_50MHz = 1,  ///< Maximum speed is 50MHz
    GPIO_Speed_20MHz,      ///< Maximum speed is 20MHz
    GPIO_Speed_10MHz       ///< Maximum speed is 10MHz
} GPIOSpeed_TypeDef;


////////////////////////////////////////////////////////////////////////////////
/// @brief  Configuration Mode enumeration
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    GPIO_Mode_AIN       = 0x00,  ///< Analog input
    GPIO_Mode_FLOATING  = 0x04,  ///< Floating input
    GPIO_Mode_IPD       = 0x28,  ///< Pull down input
    GPIO_Mode_IPU       = 0x48,  ///< Pull up input
    GPIO_Mode_Out_OD    = 0x14,  ///< Universal open drain output
    GPIO_Mode_Out_PP    = 0x10,  ///< Universal push-pull output
    GPIO_Mode_AF_OD     = 0x1C,  ///< Multiplex open drain output
    GPIO_Mode_AF_PP     = 0x18   ///< Multiplexed push-pull output
} GPIOMode_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief  Bit_SET and Bit_RESET enumeration
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    Bit_RESET = 0,  ///< bit reset
    Bit_SET         ///< bit set
} BitAction;

////////////////////////////////////////////////////////////////////////////////
/// @brief  GPIO Init structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    u16               GPIO_Pin;    ///< GPIO_Pin
    GPIOSpeed_TypeDef GPIO_Speed;  ///< GPIO_Speed
    GPIOMode_TypeDef  GPIO_Mode;   ///< GPIO_Mode
} GPIO_InitTypeDef;

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup GPIO_Exported_Constants
/// @{

#define GPIO_Speed_2MHz GPIO_Speed_20MHz

#define GPIO_Pin_0                  (0x0001U)                                   ///< Pin 0 selected
#define GPIO_Pin_1                  (0x0002U)                                   ///< Pin 1 selected
#define GPIO_Pin_2                  (0x0004U)                                   ///< Pin 2 selected
#define GPIO_Pin_3                  (0x0008U)                                   ///< Pin 3 selected
#define GPIO_Pin_4                  (0x0010U)                                   ///< Pin 4 selected
#define GPIO_Pin_5                  (0x0020U)                                   ///< Pin 5 selected
#define GPIO_Pin_6                  (0x0040U)                                   ///< Pin 6 selected
#define GPIO_Pin_7                  (0x0080U)                                   ///< Pin 7 selected
#define GPIO_Pin_8                  (0x0100U)                                   ///< Pin 8 selected
#define GPIO_Pin_9                  (0x0200U)                                   ///< Pin 9 selected
#define GPIO_Pin_10                 (0x0400U)                                   ///< Pin 10 selected
#define GPIO_Pin_11                 (0x0800U)                                   ///< Pin 11 selected
#define GPIO_Pin_12                 (0x1000U)                                   ///< Pin 12 selected
#define GPIO_Pin_13                 (0x2000U)                                   ///< Pin 13 selected
#define GPIO_Pin_14                 (0x4000U)                                   ///< Pin 14 selected
#define GPIO_Pin_15                 (0x8000U)                                   ///< Pin 15 selected
#define GPIO_Pin_All                (0xFFFFU)                                   ///< All pins selected


#define GPIO_AF_0                   (0x00U)                                     ///< Alternative function 0
#define GPIO_AF_1                   (0x01U)                                     ///< Alternative function 1
#define GPIO_AF_2                   (0x02U)                                     ///< Alternative function 2
#define GPIO_AF_3                   (0x03U)                                     ///< Alternative function 3
#define GPIO_AF_4                   (0x04U)                                     ///< Alternative function 4
#define GPIO_AF_5                   (0x05U)                                     ///< Alternative function 5
#define GPIO_AF_6                   (0x06U)                                     ///< Alternative function 6
#define GPIO_AF_7                   (0x07U)                                     ///< Alternative function 7
#define GPIO_AF_8                   (0x08U)                                     ///< Alternative function 8 
#define GPIO_AF_9                   (0x09U)                                     ///< Alternative function 9 
#define GPIO_AF_10                  (0x0AU)                                     ///< Alternative function 10
#define GPIO_AF_11                  (0x0BU)                                     ///< Alternative function 11
#define GPIO_AF_12                  (0x0CU)                                     ///< Alternative function 12
#define GPIO_AF_13                  (0x0DU)                                     ///< Alternative function 13
#define GPIO_AF_14                  (0x0EU)                                     ///< Alternative function 14
#define GPIO_AF_15                  (0x0FU)                                     ///< Alternative function 15
#define GPIO_PortSourceGPIOA        (0x00U)
#define GPIO_PortSourceGPIOB        (0x01U)
#define GPIO_PortSourceGPIOC        (0x02U)
#define GPIO_PortSourceGPIOD        (0x03U)

#define GPIO_PinSource0             (0x00U)
#define GPIO_PinSource1             (0x01U)
#define GPIO_PinSource2             (0x02U)
#define GPIO_PinSource3             (0x03U)
#define GPIO_PinSource4             (0x04U)
#define GPIO_PinSource5             (0x05U)
#define GPIO_PinSource6             (0x06U)
#define GPIO_PinSource7             (0x07U)
#define GPIO_PinSource8             (0x08U)
#define GPIO_PinSource9             (0x09U)
#define GPIO_PinSource10            (0x0AU)
#define GPIO_PinSource11            (0x0BU)
#define GPIO_PinSource12            (0x0CU)
#define GPIO_PinSource13            (0x0DU)
#define GPIO_PinSource14            (0x0EU)
#define GPIO_PinSource15            (0x0FU)

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup GPIO_Exported_Variables
/// @{

#ifdef _HAL_GPIO_C_

#define GLOBAL
#else
#define GLOBAL extern
#endif



#undef GLOBAL

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup GPIO_Exported_Functions
/// @{
void GPIO_DeInit(GPIO_TypeDef* gpio);
void GPIO_AFIODeInit(void);
void GPIO_Init(GPIO_TypeDef* gpio, GPIO_InitTypeDef* init_struct);
void GPIO_StructInit(GPIO_InitTypeDef* init_struct);
void GPIO_SetBits(GPIO_TypeDef* gpio, u16 pin);
void GPIO_ResetBits(GPIO_TypeDef* gpio, u16 pin);
void GPIO_WriteBit(GPIO_TypeDef* gpio, u16 pin, BitAction value);
void GPIO_Write(GPIO_TypeDef* gpio, u16 value);
void GPIO_PinLock(GPIO_TypeDef* gpio, u16 pin, FunctionalState state);
void GPIO_PinLockConfig(GPIO_TypeDef* gpio, u16 pin);
bool GPIO_ReadInputDataBit(GPIO_TypeDef* gpio, u16 pin);
bool GPIO_ReadOutputDataBit(GPIO_TypeDef* gpio, u16 pin);

u16 GPIO_ReadInputData(GPIO_TypeDef* gpio);
u16 GPIO_ReadOutputData(GPIO_TypeDef* gpio);


void GPIO_PinAFConfig(GPIO_TypeDef* gpio, u8 pin, u8 alternate_function);

void exGPIO_PinAFConfig(GPIO_TypeDef* gpio, u16 pin, s32 remap, s8 alternate_function);


/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif // __HAL_GPIO_H 
////////////////////////////////////////////////////////////////////////////////
