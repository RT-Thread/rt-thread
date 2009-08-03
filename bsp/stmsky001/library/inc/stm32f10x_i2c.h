/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : stm32f10x_i2c.h
* Author             : MCD Application Team
* Version            : V2.0.3Patch1
* Date               : 04/06/2009
* Description        : This file contains all the functions prototypes for the
*                      I2C firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_I2C_H    
#define __STM32F10x_I2C_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
/* I2C Init structure definition */
typedef struct
{
  u16 I2C_Mode;
  u16 I2C_DutyCycle;
  u16 I2C_OwnAddress1;
  u16 I2C_Ack;
  u16 I2C_AcknowledgedAddress;
  u32 I2C_ClockSpeed;
}I2C_InitTypeDef;

/* Exported constants --------------------------------------------------------*/
#define IS_I2C_ALL_PERIPH(PERIPH) (((*(u32*)&(PERIPH)) == I2C1_BASE) || \
                                   ((*(u32*)&(PERIPH)) == I2C2_BASE))

/* I2C modes */
#define I2C_Mode_I2C                    ((u16)0x0000)
#define I2C_Mode_SMBusDevice            ((u16)0x0002)
#define I2C_Mode_SMBusHost              ((u16)0x000A)

#define IS_I2C_MODE(MODE) (((MODE) == I2C_Mode_I2C) || \
                           ((MODE) == I2C_Mode_SMBusDevice) || \
                           ((MODE) == I2C_Mode_SMBusHost))
/* I2C duty cycle in fast mode */
#define I2C_DutyCycle_16_9              ((u16)0x4000)
#define I2C_DutyCycle_2                 ((u16)0xBFFF)

#define IS_I2C_DUTY_CYCLE(CYCLE) (((CYCLE) == I2C_DutyCycle_16_9) || \
                                  ((CYCLE) == I2C_DutyCycle_2))

/* I2C cknowledgementy */
#define I2C_Ack_Enable                  ((u16)0x0400)
#define I2C_Ack_Disable                 ((u16)0x0000)

#define IS_I2C_ACK_STATE(STATE) (((STATE) == I2C_Ack_Enable) || \
                                 ((STATE) == I2C_Ack_Disable))

/* I2C transfer direction */
#define  I2C_Direction_Transmitter      ((u8)0x00)
#define  I2C_Direction_Receiver         ((u8)0x01)

#define IS_I2C_DIRECTION(DIRECTION) (((DIRECTION) == I2C_Direction_Transmitter) || \
                                     ((DIRECTION) == I2C_Direction_Receiver))

/* I2C acknowledged address defines */
#define I2C_AcknowledgedAddress_7bit    ((u16)0x4000)
#define I2C_AcknowledgedAddress_10bit   ((u16)0xC000)

#define IS_I2C_ACKNOWLEDGE_ADDRESS(ADDRESS) (((ADDRESS) == I2C_AcknowledgedAddress_7bit) || \
                                             ((ADDRESS) == I2C_AcknowledgedAddress_10bit))

/* I2C registers */
#define I2C_Register_CR1                ((u8)0x00)
#define I2C_Register_CR2                ((u8)0x04)
#define I2C_Register_OAR1               ((u8)0x08)
#define I2C_Register_OAR2               ((u8)0x0C)
#define I2C_Register_DR                 ((u8)0x10)
#define I2C_Register_SR1                ((u8)0x14)
#define I2C_Register_SR2                ((u8)0x18)
#define I2C_Register_CCR                ((u8)0x1C)
#define I2C_Register_TRISE              ((u8)0x20)

#define IS_I2C_REGISTER(REGISTER) (((REGISTER) == I2C_Register_CR1) || \
                                   ((REGISTER) == I2C_Register_CR2) || \
                                   ((REGISTER) == I2C_Register_OAR1) || \
                                   ((REGISTER) == I2C_Register_OAR2) || \
                                   ((REGISTER) == I2C_Register_DR) || \
                                   ((REGISTER) == I2C_Register_SR1) || \
                                   ((REGISTER) == I2C_Register_SR2) || \
                                   ((REGISTER) == I2C_Register_CCR) || \
                                   ((REGISTER) == I2C_Register_TRISE))

/* I2C SMBus alert pin level */
#define I2C_SMBusAlert_Low              ((u16)0x2000)
#define I2C_SMBusAlert_High             ((u16)0xDFFF)

#define IS_I2C_SMBUS_ALERT(ALERT) (((ALERT) == I2C_SMBusAlert_Low) || \
                                   ((ALERT) == I2C_SMBusAlert_High))

/* I2C PEC position */
#define I2C_PECPosition_Next            ((u16)0x0800)
#define I2C_PECPosition_Current         ((u16)0xF7FF)

#define IS_I2C_PEC_POSITION(POSITION) (((POSITION) == I2C_PECPosition_Next) || \
                                       ((POSITION) == I2C_PECPosition_Current))

/* I2C interrupts definition */
#define I2C_IT_BUF                      ((u16)0x0400)
#define I2C_IT_EVT                      ((u16)0x0200)
#define I2C_IT_ERR                      ((u16)0x0100)

#define IS_I2C_CONFIG_IT(IT) ((((IT) & (u16)0xF8FF) == 0x00) && ((IT) != 0x00))

/* I2C interrupts definition */
#define I2C_IT_SMBALERT                 ((u32)0x01008000)
#define I2C_IT_TIMEOUT                  ((u32)0x01004000)
#define I2C_IT_PECERR                   ((u32)0x01001000)
#define I2C_IT_OVR                      ((u32)0x01000800)
#define I2C_IT_AF                       ((u32)0x01000400)
#define I2C_IT_ARLO                     ((u32)0x01000200)
#define I2C_IT_BERR                     ((u32)0x01000100)
#define I2C_IT_TXE                      ((u32)0x06000080)
#define I2C_IT_RXNE                     ((u32)0x06000040)
#define I2C_IT_STOPF                    ((u32)0x02000010)
#define I2C_IT_ADD10                    ((u32)0x02000008)
#define I2C_IT_BTF                      ((u32)0x02000004)
#define I2C_IT_ADDR                     ((u32)0x02000002)
#define I2C_IT_SB                       ((u32)0x02000001)

#define IS_I2C_CLEAR_IT(IT) ((((IT) & (u16)0x20FF) == 0x00) && ((IT) != (u16)0x00))                             

#define IS_I2C_GET_IT(IT) (((IT) == I2C_IT_SMBALERT) || ((IT) == I2C_IT_TIMEOUT) || \
                           ((IT) == I2C_IT_PECERR) || ((IT) == I2C_IT_OVR) || \
                           ((IT) == I2C_IT_AF) || ((IT) == I2C_IT_ARLO) || \
                           ((IT) == I2C_IT_BERR) || ((IT) == I2C_IT_TXE) || \
                           ((IT) == I2C_IT_RXNE) || ((IT) == I2C_IT_STOPF) || \
                           ((IT) == I2C_IT_ADD10) || ((IT) == I2C_IT_BTF) || \
                           ((IT) == I2C_IT_ADDR) || ((IT) == I2C_IT_SB))

/* I2C flags definition */
/* SR2 register flags */
#define I2C_FLAG_DUALF                  ((u32)0x00800000)
#define I2C_FLAG_SMBHOST                ((u32)0x00400000)
#define I2C_FLAG_SMBDEFAULT             ((u32)0x00200000)
#define I2C_FLAG_GENCALL                ((u32)0x00100000)
#define I2C_FLAG_TRA                    ((u32)0x00040000)
#define I2C_FLAG_BUSY                   ((u32)0x00020000)
#define I2C_FLAG_MSL                    ((u32)0x00010000)
/* SR1 register flags */
#define I2C_FLAG_SMBALERT               ((u32)0x10008000)
#define I2C_FLAG_TIMEOUT                ((u32)0x10004000)
#define I2C_FLAG_PECERR                 ((u32)0x10001000)
#define I2C_FLAG_OVR                    ((u32)0x10000800)
#define I2C_FLAG_AF                     ((u32)0x10000400)
#define I2C_FLAG_ARLO                   ((u32)0x10000200)
#define I2C_FLAG_BERR                   ((u32)0x10000100)
#define I2C_FLAG_TXE                    ((u32)0x10000080)
#define I2C_FLAG_RXNE                   ((u32)0x10000040)
#define I2C_FLAG_STOPF                  ((u32)0x10000010)
#define I2C_FLAG_ADD10                  ((u32)0x10000008)
#define I2C_FLAG_BTF                    ((u32)0x10000004)
#define I2C_FLAG_ADDR                   ((u32)0x10000002)
#define I2C_FLAG_SB                     ((u32)0x10000001)
                               
#define IS_I2C_CLEAR_FLAG(FLAG) ((((FLAG) & (u16)0x20FF) == 0x00) && ((FLAG) != (u16)0x00))                                  

#define IS_I2C_GET_FLAG(FLAG) (((FLAG) == I2C_FLAG_DUALF) || ((FLAG) == I2C_FLAG_SMBHOST) || \
                               ((FLAG) == I2C_FLAG_SMBDEFAULT) || ((FLAG) == I2C_FLAG_GENCALL) || \
                               ((FLAG) == I2C_FLAG_TRA) || ((FLAG) == I2C_FLAG_BUSY) || \
                               ((FLAG) == I2C_FLAG_MSL) || ((FLAG) == I2C_FLAG_SMBALERT) || \
                               ((FLAG) == I2C_FLAG_TIMEOUT) || ((FLAG) == I2C_FLAG_PECERR) || \
                               ((FLAG) == I2C_FLAG_OVR) || ((FLAG) == I2C_FLAG_AF) || \
                               ((FLAG) == I2C_FLAG_ARLO) || ((FLAG) == I2C_FLAG_BERR) || \
                               ((FLAG) == I2C_FLAG_TXE) || ((FLAG) == I2C_FLAG_RXNE) || \
                               ((FLAG) == I2C_FLAG_STOPF) || ((FLAG) == I2C_FLAG_ADD10) || \
                               ((FLAG) == I2C_FLAG_BTF) || ((FLAG) == I2C_FLAG_ADDR) || \
                               ((FLAG) == I2C_FLAG_SB))

/* I2C Events */
/* EV1 */
#define  I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED       ((u32)0x00060082) /* TRA, BUSY, TXE and ADDR flags */
#define  I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED          ((u32)0x00020002) /* BUSY and ADDR flags */
#define  I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED ((u32)0x00860080)  /* DUALF, TRA, BUSY and TXE flags */
#define  I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED    ((u32)0x00820000)  /* DUALF and BUSY flags */
#define  I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED        ((u32)0x00120000)  /* GENCALL and BUSY flags */

/* EV2 */
#define  I2C_EVENT_SLAVE_BYTE_RECEIVED                     ((u32)0x00020040)  /* BUSY and RXNE flags */
     
/* EV3 */
#define  I2C_EVENT_SLAVE_BYTE_TRANSMITTED                  ((u32)0x00060084)  /* TRA, BUSY, TXE and BTF flags */

/* EV4 */
#define  I2C_EVENT_SLAVE_STOP_DETECTED                     ((u32)0x00000010)  /* STOPF flag */

/* EV5 */
#define  I2C_EVENT_MASTER_MODE_SELECT                      ((u32)0x00030001)  /* BUSY, MSL and SB flag */

/* EV6 */
#define  I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED        ((u32)0x00070082)  /* BUSY, MSL, ADDR, TXE and TRA flags */
#define  I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED           ((u32)0x00030002)  /* BUSY, MSL and ADDR flags */

/* EV7 */
#define  I2C_EVENT_MASTER_BYTE_RECEIVED                    ((u32)0x00030040)  /* BUSY, MSL and RXNE flags */

/* EV8 */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING                 ((u32)0x00070080) /* TRA, BUSY, MSL, TXE flags */

/* EV8_2 */
#define  I2C_EVENT_MASTER_BYTE_TRANSMITTED                 ((u32)0x00070084)  /* TRA, BUSY, MSL, TXE and BTF flags */
      
/* EV9 */
#define  I2C_EVENT_MASTER_MODE_ADDRESS10                   ((u32)0x00030008)  /* BUSY, MSL and ADD10 flags */
                                          
/* EV3_2 */
#define  I2C_EVENT_SLAVE_ACK_FAILURE                       ((u32)0x00000400)  /* AF flag */

#define IS_I2C_EVENT(EVENT) (((EVENT) == I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED) || \
                             ((EVENT) == I2C_EVENT_SLAVE_BYTE_RECEIVED) || \
                             ((EVENT) == (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF)) || \
                             ((EVENT) == (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL)) || \
                             ((EVENT) == I2C_EVENT_SLAVE_BYTE_TRANSMITTED) || \
                             ((EVENT) == (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALF)) || \
                             ((EVENT) == (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL)) || \
                             ((EVENT) == I2C_EVENT_SLAVE_STOP_DETECTED) || \
                             ((EVENT) == I2C_EVENT_MASTER_MODE_SELECT) || \
                             ((EVENT) == I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) || \
                             ((EVENT) == I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) || \
                             ((EVENT) == I2C_EVENT_MASTER_BYTE_RECEIVED) || \
                             ((EVENT) == I2C_EVENT_MASTER_BYTE_TRANSMITTED) || \
                             ((EVENT) == I2C_EVENT_MASTER_BYTE_TRANSMITTING) || \
                             ((EVENT) == I2C_EVENT_MASTER_MODE_ADDRESS10) || \
                             ((EVENT) == I2C_EVENT_SLAVE_ACK_FAILURE))

/* I2C own address1 -----------------------------------------------------------*/
#define IS_I2C_OWN_ADDRESS1(ADDRESS1) ((ADDRESS1) <= 0x3FF)
/* I2C clock speed ------------------------------------------------------------*/
#define IS_I2C_CLOCK_SPEED(SPEED) (((SPEED) >= 0x1) && ((SPEED) <= 400000))

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, u8 Address);
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_ITConfig(I2C_TypeDef* I2Cx, u16 I2C_IT, FunctionalState NewState);
void I2C_SendData(I2C_TypeDef* I2Cx, u8 Data);
u8 I2C_ReceiveData(I2C_TypeDef* I2Cx);
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, u8 Address, u8 I2C_Direction);
u16 I2C_ReadRegister(I2C_TypeDef* I2Cx, u8 I2C_Register);
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, u16 I2C_SMBusAlert);
void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, u16 I2C_PECPosition);
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState);
u8 I2C_GetPEC(I2C_TypeDef* I2Cx);
void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, u16 I2C_DutyCycle);
u32 I2C_GetLastEvent(I2C_TypeDef* I2Cx);
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, u32 I2C_EVENT);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, u32 I2C_FLAG);
void I2C_ClearFlag(I2C_TypeDef* I2Cx, u32 I2C_FLAG);
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, u32 I2C_IT);
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, u32 I2C_IT);

#endif /*__STM32F10x_I2C_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
