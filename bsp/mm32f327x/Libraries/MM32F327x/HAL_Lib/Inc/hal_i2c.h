////////////////////////////////////////////////////////////////////////////////
/// @file     hal_i2c.h
/// @author   AE TEAM
/// @brief    THIS FILE CONTAINS ALL THE FUNCTIONS PROTOTYPES FOR THE I2C
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
#ifndef __HAL_I2C_H
#define __HAL_I2C_H

// Files includes
#include "types.h"
#include "reg_i2c.h"

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup MM32_Hardware_Abstract_Layer
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_HAL
/// @brief I2C HAL modules
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_Exported_Types
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @defgroup DRV_Exported_Constants
/// @{

#define I2C_OWN_ADDRESS  0x20

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @brief  I2C Init structure definition
////////////////////////////////////////////////////////////////////////////////
typedef struct {
    union {
        u16 Mode;        ///< Specifies the I2C mode. This parameter can be a value of I2C_mode.
        u16 I2C_Mode;
    };
    union {
        u16 Speed;       ///< Specifies the I2C speed. This parameter can be a value of I2C_speed.
        u16 I2C_Speed;
    };
    union {
        u16 OwnAddress;  ///< Specifies the first device own address. This parameter can be a 7-bit or 10-bit address.
        u16 I2C_OwnAddress;
    };

    union {
        u32 ClockSpeed;  ///< Specifies the clock speed.
        u32 I2C_ClockSpeed;
    };
} I2C_InitTypeDef;
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_Exported_Constants
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C DMA Direction
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    RDMAE_SET = 1,  // 1 - DMA read
    TDMAE_SET       // 2 - DMA transmit
} I2C_DMA_Dir_TypeDef;
////////////////////////////////////////////////////////////////////////////////
/// @brief I2C Transfer Direction
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    I2C_Direction_Transmitter,  // I2C Transmitter
    I2C_Direction_Receiver      // I2C Receiver
} I2C_Trans_Dir_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @brief I2C Acknowledged Address
////////////////////////////////////////////////////////////////////////////////
typedef enum {
    I2C_AcknowledgedAddress_7bit  = 0x4000,  // 7-bit address
    I2C_AcknowledgedAddress_10bit = 0xC000   // 10-bit address
} I2C_ACKaddr_TypeDef;

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_Private_Defines
/// @{
#define INTR_MASK           ((u16)0xC000)
#define FLAG_Mask           ((u32)0x00793FFF)
#define IC_TAR_ENDUAL_Set   ((u16)0x1000)
#define IC_TAR_ENDUAL_Reset ((u16)0xEFFF)
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_modes
/// @{
#define TX_EMPTY_CTRL       I2C_CR_EMPINT
#define IC_SLAVE_DISABLE    I2C_CR_SLAVEDIS
#define IC_RESTART_EN       I2C_CR_REPEN
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_interrupts_definition
/// @{
#define I2C_IT_RX_UNDER     ((u16)0x0001)
#define I2C_IT_RX_OVER      ((u16)0x0002)
#define I2C_IT_RX_FULL      ((u16)0x0004)
#define I2C_IT_TX_OVER      ((u16)0x0008)
#define I2C_IT_TX_EMPTY     ((u16)0x0010)
#define I2C_IT_RD_REQ       ((u16)0x0020)
#define I2C_IT_TX_ABRT      ((u16)0x0040)
#define I2C_IT_RX_DONE      ((u16)0x0080)
#define I2C_IT_ACTIVITY     ((u16)0x0100)
#define I2C_IT_STOP_DET     ((u16)0x0200)
#define I2C_IT_START_DET    ((u16)0x0400)
#define I2C_IT_GEN_CALL     ((u16)0x0800)
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_flags_definition
/// @{
#define I2C_FLAG_RX_UNDER     ((u16)0x0001)
#define I2C_FLAG_RX_OVER      ((u16)0x0002)
#define I2C_FLAG_RX_FULL      ((u16)0x0004)
#define I2C_FLAG_TX_OVER      ((u16)0x0008)
#define I2C_FLAG_TX_EMPTY     ((u16)0x0010)
#define I2C_FLAG_RD_REQ       ((u16)0x0020)
#define I2C_FLAG_TX_ABRT      ((u16)0x0040)
#define I2C_FLAG_RX_DONE      ((u16)0x0080)
#define I2C_FLAG_ACTIVITY     ((u16)0x0100)
#define I2C_FLAG_STOP_DET     ((u16)0x0200)
#define I2C_FLAG_START_DET    ((u16)0x0400)
#define I2C_FLAG_GEN_CALL     ((u16)0x0800)
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_Events
/// @{
#define I2C_EVENT_RX_UNDER     ((u16)0x0001)
#define I2C_EVENT_RX_OVER      ((u16)0x0002)
#define I2C_EVENT_RX_FULL      ((u16)0x0004)
#define I2C_EVENT_TX_OVER      ((u16)0x0008)
#define I2C_EVENT_TX_EMPTY     ((u16)0x0010)
#define I2C_EVENT_RD_REQ       ((u16)0x0020)
#define I2C_EVENT_TX_ABRT      ((u16)0x0040)
#define I2C_EVENT_RX_DONE      ((u16)0x0080)
#define I2C_EVENT_ACTIVITY     ((u16)0x0100)
#define I2C_EVENT_STOP_DET     ((u16)0x0200)
#define I2C_EVENT_START_DET    ((u16)0x0400)
#define I2C_EVENT_GEN_CALL     ((u16)0x0800)
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_Statusflags_definition
/// @{
#define I2C_STATUS_FLAG_ACTIVITY    ((u16)0x8001)
#define I2C_STATUS_FLAG_TFNF        ((u16)0x8002)
#define I2C_STATUS_FLAG_TFE         ((u16)0x8004)
#define I2C_STATUS_FLAG_RFNE        ((u16)0x8008)
#define I2C_STATUS_FLAG_RFF         ((u16)0x8010)
#define I2C_STATUS_FLAG_M_ACTIVITY  ((u16)0x8020)
#define I2C_STATUS_FLAG_S_ACTIVITY  ((u16)0x8040)
/// @}



#define IC_SLAVE_ENABLE                 (0x0000<<6)
#define IC_7BITADDR_MASTER              (0x0000<<4)
#define IC_7BITADDR_SLAVE               (0x0000<<3)
#define I2C_Speed_STANDARD              ((u16)0x0002)
#define I2C_Speed_FAST                  ((u16)0x0004)
#define I2C_Mode_MASTER                 ((u16)0x0001)
#define I2C_Mode_SLAVE                  ((u16)0x0000)
#define CMD_READ                        ((u16)0x0100)
#define CMD_WRITE                       ((u16)0x0000)
#define I2C_Mode_I2C                    ((u16)0x0000)

/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_Exported_Variables
/// @{
#ifdef _HAL_I2C_C_

#define GLOBAL

static u8 I2C_CMD_DIR = 0;
u16       I2C_DMA_DIR = 0;

#else
#define GLOBAL extern
#endif

#undef GLOBAL
/// @}

////////////////////////////////////////////////////////////////////////////////
/// @defgroup I2C_Exported_Functions
/// @{
void I2C_DeInit(I2C_TypeDef* i2c);
void I2C_Init(I2C_TypeDef* i2c, I2C_InitTypeDef* init_struct);
void I2C_StructInit(I2C_InitTypeDef* init_struct);
void I2C_Cmd(I2C_TypeDef* i2c, FunctionalState state);
void I2C_DMACmd(I2C_TypeDef* i2c, FunctionalState state);
void I2C_GenerateSTART(I2C_TypeDef* i2c, FunctionalState state);
void I2C_GenerateSTOP(I2C_TypeDef* i2c, FunctionalState state);
void I2C_OwnAddress2Config(I2C_TypeDef* i2c, u8 addr);
void I2C_DualAddressCmd(I2C_TypeDef* i2c, FunctionalState state);
void I2C_GeneralCallCmd(I2C_TypeDef* i2c, FunctionalState state);
void I2C_ITConfig(I2C_TypeDef* i2c, u16 it, FunctionalState state);
void I2C_SendData(I2C_TypeDef* i2c, u8 dat);
void I2C_ReadCmd(I2C_TypeDef* i2c);
void I2C_Send7bitAddress(I2C_TypeDef* i2c, u8 addr, u8 dir);
void I2C_ClearFlag(I2C_TypeDef* i2c, u32 flag);
void I2C_ClearITPendingBit(I2C_TypeDef* i2c, u32 it);

u8  I2C_ReceiveData(I2C_TypeDef* i2c);
u16 I2C_ReadRegister(I2C_TypeDef* i2c, u8 reg);
u32 I2C_GetLastEvent(I2C_TypeDef* i2c);

ErrorStatus I2C_CheckEvent(I2C_TypeDef* i2c, u32 event);
FlagStatus  I2C_GetFlagStatus(I2C_TypeDef* i2c, u32 flag);
ITStatus    I2C_GetITStatus(I2C_TypeDef* i2c, u32 it);

////////////////////////////////////////////////////////////////////////////////
//          Extended function interface
////////////////////////////////////////////////////////////////////////////////
void I2C_SendSlaveAddress(I2C_TypeDef* i2c, u8 addr);
void I2C_SlaveConfigure(I2C_TypeDef* i2c, FunctionalState state);
void I2C_DMAConfigure(I2C_TypeDef* i2c, u8 dir);


/// @}

/// @}

/// @}

////////////////////////////////////////////////////////////////////////////////
#endif //__HAL_I2C_H 
////////////////////////////////////////////////////////////////////////////////
