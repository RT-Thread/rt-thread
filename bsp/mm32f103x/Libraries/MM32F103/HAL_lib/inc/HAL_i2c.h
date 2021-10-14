/**
******************************************************************************
* @file    HAL_i2c.h
* @author  AE Team
* @version V1.1.0
* @date    28/08/2019
* @brief   This file contains all the functions prototypes for the I2C firmware
*          library.
******************************************************************************
* @copy
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <h2><center>&copy; COPYRIGHT 2019 MindMotion</center></h2>
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_I2C_H
#define __HAL_I2C_H

/* Includes ------------------------------------------------------------------*/
#include "HAL_device.h"

/** @addtogroup StdPeriph_Driver
* @{
*/

/** @addtogroup I2C
* @{
*/

/** @defgroup I2C_Exported_Types
* @{
*/

/**
* @brief  I2C Init structure definition
*/
/*
typedef struct
{
uint16_t I2C_Mode;
uint16_t I2C_DutyCycle;
uint16_t I2C_OwnAddress1;
uint16_t I2C_Ack;
uint16_t I2C_AcknowledgedAddress;
uint32_t I2C_ClockSpeed;
}I2C_InitTypeDef;
*/
typedef struct
{
    uint16_t I2C_Mode;
    uint16_t I2C_Speed;
    uint16_t I2C_OwnAddress;
    uint32_t I2C_ClockSpeed;
} I2C_InitTypeDef;

/**
* @}
*/


/** @defgroup I2C_Exported_Constants
* @{
*/

#define IS_I2C_ALL_PERIPH(PERIPH) (((*(uint32_t*)&(PERIPH)) == I2C1_BASE) || \
                                   ((*(uint32_t*)&(PERIPH)) == I2C2_BASE))
/** @defgroup I2C_modes
* @{
*/

#define   TX_EMPTY_CTRL						(0x0001<<8)
#define		IC_SLAVE_DISABLE				(0x0001<<6)
#define		IC_SLAVE_ENABLE					(0x0000<<6)
#define		IC_RESTART_EN						(0x0001<<5)
#define		IC_7BITADDR_MASTER			(0x0000<<4)
#define		IC_7BITADDR_SLAVE				(0x0000<<3)

#define 	I2C_Speed_STANDARD      ((uint16_t)0x0002)
#define 	I2C_Speed_FAST         	((uint16_t)0x0004)
#define 	I2C_Mode_MASTER					((uint16_t)0x0001)
#define 	I2C_Mode_SLAVE					((uint16_t)0x0000)

#define 	TDMAE_SET								((uint16_t)0x0002)
#define 	RDMAE_SET								((uint16_t)0x0001)

#define 	CMD_READ								((uint16_t)0x0100)
#define 	CMD_WRITE								((uint16_t)0x0000)




#define I2C_Mode_I2C                    ((uint16_t)0x0000)

#define IS_I2C_MODE(MODE) (((MODE) == I2C_Mode_I2C))

/**
* @}
*/


/** @defgroup I2C_transfer_direction
* @{
*/

#define  I2C_Direction_Transmitter      ((uint8_t)0x00)
#define  I2C_Direction_Receiver         ((uint8_t)0x01)
#define IS_I2C_DIRECTION(DIRECTION) (((DIRECTION) == I2C_Direction_Transmitter) || \
                                     ((DIRECTION) == I2C_Direction_Receiver))
/**
* @}
*/

/** @defgroup I2C_acknowledged_address_defines
* @{
*/

#define I2C_AcknowledgedAddress_7bit    ((uint16_t)0x4000)
#define I2C_AcknowledgedAddress_10bit   ((uint16_t)0xC000)
#define IS_I2C_ACKNOWLEDGE_ADDRESS(ADDRESS) (((ADDRESS) == I2C_AcknowledgedAddress_7bit) || \
        ((ADDRESS) == I2C_AcknowledgedAddress_10bit))

/**
* @}
*/

/** @defgroup I2C_interrupts_definition
* @{
*/


#define IS_I2C_CONFIG_IT(IT) ((((IT) & (uint16_t)0xF8FF) == 0x00) && ((IT) != 0x00))
/**
* @}
*/

/** @defgroup I2C_interrupts_definition
* @{
*/

#define I2C_IT_RX_UNDER					((uint16_t)0x0001)
#define I2C_IT_RX_OVER					((uint16_t)0x0002)
#define I2C_IT_RX_FULL  				((uint16_t)0x0004)
#define I2C_IT_TX_OVER					((uint16_t)0x0008)
#define I2C_IT_TX_EMPTY					((uint16_t)0x0010)
#define I2C_IT_RD_REQ						((uint16_t)0x0020)
#define I2C_IT_TX_ABRT					((uint16_t)0x0040)
#define I2C_IT_RX_DONE					((uint16_t)0x0080)
#define I2C_IT_ACTIVITY					((uint16_t)0x0100)
#define I2C_IT_STOP_DET					((uint16_t)0x0200)
#define I2C_IT_START_DET				((uint16_t)0x0400)
#define I2C_IT_GEN_CALL				((uint16_t)0x0800)

#define IS_I2C_CLEAR_IT(IT) ((((IT) & (uint16_t)0xF000) == 0x00) && ((IT) != (uint16_t)0x00))

#define IS_I2C_GET_IT(IT) (((IT) == I2C_IT_RX_UNDER) || ((IT) == I2C_IT_RX_OVER) || \
                           ((IT) == I2C_IT_RX_FULL) || ((IT) == I2C_IT_TX_OVER) || \
                           ((IT) == I2C_IT_TX_EMPTY) || ((IT) == I2C_IT_RD_REQ) || \
                           ((IT) == I2C_IT_TX_ABRT) || ((IT) == I2C_IT_RX_DONE) || \
                           ((IT) == I2C_IT_ACTIVITY) || ((IT) == I2C_IT_STOP_DET) || \
                           ((IT) == I2C_IT_START_DET) || ((IT) == I2C_IT_GEN_CALL))
/**
* @}
*/

/** @defgroup I2C_flags_definition
* @{
*/



#define I2C_FLAG_RX_UNDER					((uint16_t)0x0001)
#define I2C_FLAG_RX_OVER					((uint16_t)0x0002)
#define I2C_FLAG_RX_FULL  				((uint16_t)0x0004)
#define I2C_FLAG_TX_OVER					((uint16_t)0x0008)
#define I2C_FLAG_TX_EMPTY					((uint16_t)0x0010)
#define I2C_FLAG_RD_REQ						((uint16_t)0x0020)
#define I2C_FLAG_TX_ABRT					((uint16_t)0x0040)
#define I2C_FLAG_RX_DONE					((uint16_t)0x0080)
#define I2C_FLAG_ACTIVITY					((uint16_t)0x0100)
#define I2C_FLAG_STOP_DET					((uint16_t)0x0200)
#define I2C_FLAG_START_DET				((uint16_t)0x0400)
#define I2C_FLAG_GEN_CALL					((uint16_t)0x0800)






#define IS_I2C_CLEAR_FLAG(FLAG) ((((FLAG) & (uint16_t)0xF000) == 0x00) && ((FLAG) != (uint16_t)0x00))

#define IS_I2C_GET_FLAG(FLAG) (((FLAG) == I2C_FLAG_RX_UNDER) || ((FLAG) == I2C_FLAG_RX_OVER) || \
                               ((FLAG) == I2C_FLAG_RX_FULL) || ((FLAG) == I2C_FLAG_TX_OVER) || \
                               ((FLAG) == I2C_FLAG_TX_EMPTY) || ((FLAG) == I2C_FLAG_RD_REQ) || \
                               ((FLAG) == I2C_FLAG_TX_ABRT) || ((FLAG) == I2C_FLAG_RX_DONE) || \
                               ((FLAG) == I2C_FLAG_ACTIVITY) || ((FLAG) == I2C_FLAG_STOP_DET) || \
                               ((FLAG) == I2C_FLAG_START_DET) || ((FLAG) == I2C_FLAG_GEN_CALL))


/** @defgroup I2C_Statusflags_definition
* @{
*/

#define I2C_STATUS_FLAG_ACTIVITY				((uint16_t)0x8001)
#define I2C_STATUS_FLAG_TFNF					((uint16_t)0x8002)
#define I2C_STATUS_FLAG_TFE						((uint16_t)0x8004)
#define I2C_STATUS_FLAG_RFNE					((uint16_t)0x8008)
#define I2C_STATUS_FLAG_RFF						((uint16_t)0x8010)
#define I2C_STATUS_FLAG_M_ACTIVITY				((uint16_t)0x8020)
#define I2C_STATUS_FLAG_S_ACTIVITY				((uint16_t)0x8040)


/**
* @}
*/

/** @defgroup I2C_Events
* @{
*/


#define I2C_EVENT_RX_UNDER				((uint32_t)0x0001)
#define I2C_EVENT_RX_OVER				((uint32_t)0x0002)
#define I2C_EVENT_RX_FULL  				((uint32_t)0x0004)
#define I2C_EVENT_TX_OVER				((uint32_t)0x0008)
#define I2C_EVENT_TX_EMPTY				((uint32_t)0x0010)
#define I2C_EVENT_RD_REQ				((uint32_t)0x0020)
#define I2C_EVENT_TX_ABRT				((uint32_t)0x0040)
#define I2C_EVENT_RX_DONE				((uint32_t)0x0080)
#define I2C_EVENT_ACTIVITY				((uint32_t)0x0100)
#define I2C_EVENT_STOP_DET				((uint32_t)0x0200)
#define I2C_EVENT_START_DET				((uint32_t)0x0400)
#define I2C_EVENT_GEN_CALL				((uint32_t)0x0800)


#define IS_I2C_EVENT(EVENT)  (((EVENT) == I2C_EVENT_RX_UNDER) || \
                              ((EVENT) == I2C_EVENT_RX_OVER) || \
                              ((EVENT) == I2C_EVENT_RX_FULL) || \
                              ((EVENT) == I2C_EVENT_TX_OVER) || \
                              ((EVENT) == I2C_EVENT_RD_REQ) || \
                              ((EVENT) == I2C_EVENT_TX_ABRT) || \
                              ((EVENT) == I2C_EVENT_RX_DONE) || \
                              ((EVENT) == (I2C_EVENT_ACTIVITY | I2C_EVENT_STOP_DET)) || \
                              ((EVENT) == (I2C_EVENT_START_DET | I2C_EVENT_GEN_CALL)))

/**
* @}
*/

/** @defgroup I2C_own_address1
* @{
*/

#define IS_I2C_OWN_ADDRESS1(ADDRESS1) ((ADDRESS1) <= 0x3FF)
/**
* @}
*/

/** @defgroup I2C_clock_speed
* @{
*/

#define IS_I2C_CLOCK_SPEED(SPEED) (((SPEED) >= 0x1) && ((SPEED) <= 400000))
/**
* @}
*/

/**
* @}
*/

/** @defgroup I2C_Exported_Macros
* @{
*/

/**
* @}
*/

/** @defgroup I2C_Exported_Functions
* @{
*/

void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);

void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address);
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState);
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
void I2C_SendLastDataOrStop(I2C_TypeDef* I2Cx, uint8_t Data);
void I2C_ReadCmd(I2C_TypeDef* I2Cx);
uint8_t I2C_ReadLastDataOrStop(I2C_TypeDef* I2Cx);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction);
uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register);

uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx);
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT);
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT);



#endif /*__HAL_I2C_H */
/**
* @}
*/

/**
* @}
*/

/**
* @}
*/

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/
