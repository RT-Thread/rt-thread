/**
  ******************************************************************************
  * @brief   I2C header file of the firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F10X_I2C_H
#define __GD32F10X_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gd32f10x.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @addtogroup I2C
  * @{
  */

/** @defgroup I2C_Exported_Types
  * @{
  */

/**
  * @brief I2C Initial Parameters
  */
typedef struct {
    uint16_t I2C_Protocol;              /*!< The protocol type, detailed in @ref I2C_Protocol */
    uint16_t I2C_DutyCycle;             /*!< The fast mode duty cycle, detailed in @ref I2C_Duty_Cycle */
    uint32_t I2C_BitRate;               /*!< The I2C bit rate which must be lower than 400k bit/s */
    uint16_t I2C_AddressingMode;        /*!< The I2C addressing mode, detailed in @ref I2C_Addressing_Mode */
    uint16_t I2C_DeviceAddress;         /*!< The device address */
} I2C_InitPara;

/**
  * @}
  */

/** @defgroup I2C_Exported_Constants
  * @{
  */

/** @defgroup I2C_Protocol
  * @{
  */
#define I2C_PROTOCOL_I2C                ((uint16_t)0x0000)
#define I2C_PROTOCOL_SMBUSDEVICE        ((uint16_t)0x0002)
#define I2C_PROTOCOL_SMBUSHOST          ((uint16_t)0x000A)

/**
  * @}
  */

/** @defgroup I2C_Duty_Cycle
  * @{
  */
#define I2C_DUTYCYCLE_16_9              ((uint16_t)0x4000) /*!< I2C fast mode Tlow/Thigh = 16/9 */
#define I2C_DUTYCYCLE_2                 ((uint16_t)0xBFFF) /*!< I2C fast mode Tlow/Thigh = 2 */

/**
  * @}
  */

/** @defgroup I2C_Addressing_Mode
  * @{
  */
#define I2C_ADDRESSING_MODE_7BIT        ((uint16_t)0x4000)
#define I2C_ADDRESSING_MODE_10BIT       ((uint16_t)0xC000)

/**
  * @}
  */

/** @defgroup I2C_Direction
  * @{
  */
#define I2C_DIRECTION_TRANSMITTER       ((uint8_t)0x00)
#define I2C_DIRECTION_RECEIVER          ((uint8_t)0x01)

/**
  * @}
  */

/** @defgroup I2C_Registers
  * @{
  */
#define I2C_REGISTER_CTLR1              ((uint8_t)0x00)
#define I2C_REGISTER_CTLR2              ((uint8_t)0x04)
#define I2C_REGISTER_AR1                ((uint8_t)0x08)
#define I2C_REGISTER_AR2                ((uint8_t)0x0C)
#define I2C_REGISTER_DTR                ((uint8_t)0x10)
#define I2C_REGISTER_STR1               ((uint8_t)0x14)
#define I2C_REGISTER_STR2               ((uint8_t)0x18)
#define I2C_REGISTER_CLKR               ((uint8_t)0x1C)
#define I2C_REGISTER_RTR                ((uint8_t)0x20)

/**
  * @}
  */

/** @defgroup I2C_PEC_Position
  * @{
  */
#define I2C_PECPOSITION_NEXT            I2C_CTLR1_POAP
#define I2C_PECPOSITION_CURRENT         ((uint16_t)~I2C_CTLR1_POAP)

/**
  * @}
  */

/** @defgroup I2C_NACK_Position
  * @{
  */
#define I2C_NACKPOSITION_NEXT           I2C_CTLR1_POAP
#define I2C_NACKPOSITION_CURRENT        ((uint16_t)~I2C_CTLR1_POAP)

/**
  * @}
  */

/** @defgroup I2C_Interrupt_Control
  * @{
  */
#define I2C_INT_EIE                     I2C_CTLR2_EIE
#define I2C_INT_EE                      I2C_CTLR2_EE
#define I2C_INT_BIE                     I2C_CTLR2_BIE

/**
  * @}
  */

/** @defgroup I2C_Interrupt_Source
  * @{
  */
#define I2C_INT_SMBALTS                 ((uint32_t)0x01008000)
#define I2C_INT_SMBTO                   ((uint32_t)0x01004000)
#define I2C_INT_PECE                    ((uint32_t)0x01001000)
#define I2C_INT_RXORE                   ((uint32_t)0x01000800)
#define I2C_INT_AE                      ((uint32_t)0x01000400)
#define I2C_INT_LOSTARB                 ((uint32_t)0x01000200)
#define I2C_INT_BE                      ((uint32_t)0x01000100)
#define I2C_INT_TBE                     ((uint32_t)0x06000080)
#define I2C_INT_RBNE                    ((uint32_t)0x06000040)
#define I2C_INT_STPSEND                 ((uint32_t)0x02000010)
#define I2C_INT_ADD10SEND               ((uint32_t)0x02000008)
#define I2C_INT_BTC                     ((uint32_t)0x02000004)
#define I2C_INT_ADDSEND                 ((uint32_t)0x02000002)
#define I2C_INT_SBSEND                  ((uint32_t)0x02000001)

/**
  * @}
  */

/** @defgroup I2C_FLAG
  * @{
  */

/**
  * @brief  STR2 register flags
  */
#define I2C_FLAG_DUMODF                 ((uint32_t)0x00800000)
#define I2C_FLAG_HSTSMB                 ((uint32_t)0x00400000)
#define I2C_FLAG_DEFSMB                 ((uint32_t)0x00200000)
#define I2C_FLAG_RXGC                   ((uint32_t)0x00100000)
#define I2C_FLAG_TRS                    ((uint32_t)0x00040000)
#define I2C_FLAG_I2CBSY                 ((uint32_t)0x00020000)
#define I2C_FLAG_MASTER                 ((uint32_t)0x00010000)

/**
  * @brief  STR1 register flags
  */
#define I2C_FLAG_SMBALTS                ((uint32_t)0x10008000)
#define I2C_FLAG_SMBTO                  ((uint32_t)0x10004000)
#define I2C_FLAG_PECE                   ((uint32_t)0x10001000)
#define I2C_FLAG_RXORE                  ((uint32_t)0x10000800)
#define I2C_FLAG_AE                     ((uint32_t)0x10000400)
#define I2C_FLAG_LOSTARB                ((uint32_t)0x10000200)
#define I2C_FLAG_BE                     ((uint32_t)0x10000100)
#define I2C_FLAG_TBE                    ((uint32_t)0x10000080)
#define I2C_FLAG_RBNE                   ((uint32_t)0x10000040)
#define I2C_FLAG_STPSEND                ((uint32_t)0x10000010)
#define I2C_FLAG_ADD10SEND              ((uint32_t)0x10000008)
#define I2C_FLAG_BTC                    ((uint32_t)0x10000004)
#define I2C_FLAG_ADDSEND                ((uint32_t)0x10000002)
#define I2C_FLAG_SBSEND                 ((uint32_t)0x10000001)

/**
  * @}
  */

/** @defgroup I2C_ProgrammingMode
  * @{
  */
#define I2C_PROGRAMMINGMODE_MASTER_SBSEND                               ((uint32_t)0x00030001)  /*!< I2CBSY, MASTER and SBSEND flag */

#define I2C_PROGRAMMINGMODE_MASTER_TRANSMITTER_ADDSEND                  ((uint32_t)0x00070002)  /*!< I2CBSY, MASTER, ADDSEND and TRS flags */
#define I2C_PROGRAMMINGMODE_MASTER_RECEIVER_ADDSEND                     ((uint32_t)0x00030002)  /*!< I2CBSY, MASTER and ADDSEND flags */

#define I2C_PROGRAMMINGMODE_MASTER_ADD10SEND                            ((uint32_t)0x00030008)  /*!< I2CBSY, MASTER and ADD10SEND flags */

#define I2C_PROGRAMMINGMODE_MASTER_BYTE_RECEIVED                        ((uint32_t)0x00030040)  /*!< I2CBSY, MASTER and RBNE flags */
#define I2C_PROGRAMMINGMODE_MASTER_BYTE_TRANSMITTING                    ((uint32_t)0x00070080)  /*!< TRS, I2CBSY, MASTER, TBE flags */
#define I2C_PROGRAMMINGMODE_MASTER_BYTE_TRANSMITTED                     ((uint32_t)0x00070084)  /*!< TRS, I2CBSY, MASTER, TBE and BTC flags */

#define I2C_PROGRAMMINGMODE_SLAVE_RECEIVER_ADDSEND                      ((uint32_t)0x00020002)  /*!< I2CBSY and ADDSEND flags */
#define I2C_PROGRAMMINGMODE_SLAVE_TRANSMITTER_ADDSEND                   ((uint32_t)0x00060002)  /*!< TRS, I2CBSY and ADDSEND flags */

#define I2C_PROGRAMMINGMODE_SLAVE_RECEIVER_SECONDADDRESS_SELECTED       ((uint32_t)0x00820000)  /*!< DUMODF and I2CBSY flags */
#define I2C_PROGRAMMINGMODE_SLAVE_TRANSMITTER_SECONDADDRESS_SELECTED    ((uint32_t)0x00860080)  /*!< DUMODF, TRS, I2CBSY and TBE flags */

#define I2C_PROGRAMMINGMODE_SLAVE_GENERALCALLADDRESS_SELECTED           ((uint32_t)0x00120000)  /*!< RXGC and I2CBSY flags */

#define I2C_PROGRAMMINGMODE_SLAVE_BYTE_RECEIVED                         ((uint32_t)0x00020040)  /*!< I2CBSY and RBNE flags */
#define  I2C_PROGRAMMINGMODE_SLAVE_STOP_DETECTED                        ((uint32_t)0x00000010)  /*!< STPSEND flag */

#define I2C_PROGRAMMINGMODE_SLAVE_BYTE_TRANSMITTED                      ((uint32_t)0x00060084)  /*!< TRS, I2CBSY, TBE and BTC flags */
#define I2C_PROGRAMMINGMODE_SLAVE_BYTE_TRANSMITTING                     ((uint32_t)0x00060080)  /*!< TRS, I2CBSY and TBE flags */
#define I2C_PROGRAMMINGMODE_SLAVE_ACK_FAILURE                           ((uint32_t)0x00000400)  /*!< AE flag */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup I2C_Exported_Functions
  * @{
  */
void I2C_DeInit(I2C_TypeDef *I2Cx);
void I2C_Init(I2C_TypeDef *I2Cx, I2C_InitPara *I2C_InitParaStruct);
void I2C_ParaInit(I2C_InitPara *I2C_InitParaStruct);
void I2C_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
void I2C_DMA_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
void I2C_DMALastTransfer_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
void I2C_StartOnBus_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
void I2C_StopOnBus_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
void I2C_Acknowledge_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
void I2C_OwnAddress2(I2C_TypeDef *I2Cx, uint8_t Address);
void I2C_DualAddress_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
void I2C_GeneralCall_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
void I2C_INTConfig(I2C_TypeDef *I2Cx, uint16_t I2C_INT, TypeState NewValue);
void I2C_SendData(I2C_TypeDef *I2Cx, uint8_t Data);
uint8_t I2C_ReceiveData(I2C_TypeDef *I2Cx);
void I2C_AddressingDevice_7bit(I2C_TypeDef *I2Cx, uint8_t Address, uint8_t I2C_Direction);
uint16_t I2C_ReadRegister(I2C_TypeDef *I2Cx, uint8_t I2C_Register);
void I2C_SoftwareReset_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
void I2C_NACKPosition_Enable(I2C_TypeDef *I2Cx, uint16_t I2C_NACKPosition);
void I2C_SMBusAlertSend_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
void I2C_PECTransmit_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
void I2C_PECPosition_Enable(I2C_TypeDef *I2Cx, uint16_t I2C_PECPosition);
void I2C_PEC_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
uint8_t I2C_GetPECValue(I2C_TypeDef *I2Cx);
void I2C_ARP_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
void I2C_StretchClock_Enable(I2C_TypeDef *I2Cx, TypeState NewValue);
void I2C_FastModeDutyCycle(I2C_TypeDef *I2Cx, uint16_t I2C_DutyCycle);

TypeState I2C_StateDetect(I2C_TypeDef *I2Cx, uint32_t I2C_State);
uint32_t I2C_GetCurrentState(I2C_TypeDef *I2Cx);
TypeState I2C_GetBitState(I2C_TypeDef *I2Cx, uint32_t I2C_FLAG);
void I2C_ClearBitState(I2C_TypeDef *I2Cx, uint32_t I2C_FLAG);
TypeState I2C_GetIntBitState(I2C_TypeDef *I2Cx, uint32_t I2C_INT);
void I2C_ClearIntBitState(I2C_TypeDef *I2Cx, uint32_t I2C_INT);

#ifdef __cplusplus
}
#endif

#endif /*__GD32F10X_I2C_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

