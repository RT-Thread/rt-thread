/*!
 * @file        apm32f4xx_i2c.h
 *
 * @brief       This file contains all the functions prototypes for the I2C firmware library
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32F4XX_I2C_H
#define __APM32F4XX_I2C_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup I2C_Driver
  @{
*/

/** @defgroup I2C_Enumerations
  @{
*/

/**
 * @brief I2C Mode
 */
typedef enum
{
    I2C_MODE_I2C          = 0x0000, /*!< I2C mode */
    I2C_MODE_SMBUUSDEVICE = 0x0002, /*!< SMBus device mode */
    I2C_MODE_SMBUSHOST    = 0x000A  /*!< SMBus host mode */
} I2C_MODE_T;

/**
 * @brief I2C duty cycle in fast mode
 */
typedef enum
{
    I2C_DUTYCYCLE_16_9 = 0x4000,    /*!< I2C fast mode Tlow/Thigh = 16/9 */
    I2C_DUTYCYCLE_2    = 0xBFFF     /*!< I2C fast mode Tlow/Thigh = 2 */
} I2C_DUTYCYCLE_T;

/**
 * @brief I2C acknowledgement
 */
typedef enum
{
    I2C_ACK_DISABLE,    /*!< Send acknowledge */
    I2C_ACK_ENABLE      /*!< Do not send acknowledge */
} I2C_ACK_T;

/**
 * @brief I2C transfer direction
 */

typedef enum
{
    I2C_DIRECTION_TX,   /*!< Transmitter mode */
    I2C_DIRECTION_RX    /*!< Receiver mode */
} I2C_DIRECTION_T;

/**
 * @brief I2C acknowledged address
 */
typedef enum
{
    I2C_ACK_ADDRESS_7BIT  = 0x4000, /*!< Set slave address length to 7-bit */
    I2C_ACK_ADDRESS_10BIT = 0xC000  /*!< Set slave address length to 10-bit */
} I2C_ACK_ADDRESS_T;

/**
 * @brief I2C Register
 */
typedef enum
{
    I2C_REGISTER_CTRL1,     /*!< CTRL1 register */
    I2C_REGISTER_CTRL2,     /*!< CTRL2 register */
    I2C_REGISTER_SADDR1,    /*!< SADDR1 register */
    I2C_REGISTER_SADDR2,    /*!< SADDR2 register */
    I2C_REGISTER_DATA,      /*!< DATA register */
    I2C_REGISTER_STS1,      /*!< STS1 register */
    I2C_REGISTER_STS2,      /*!< STS2 register */
    I2C_REGISTER_CLKCTRL,   /*!< CLKCTRL register */
    I2C_REGISTER_RISETMAX,  /*!< RISETMAX register */
} I2C_REGISTER_T;

/**
 * @brief I2C NCAK position
 */
typedef enum
{
    I2C_NACK_POSITION_NEXT,     /*!< Set NACK signal to next receive byte */
    I2C_NACK_POSITION_CURRENT   /*!< Set NACK signal to current receive byte */
} I2C_NACK_POSITION_T;

/**
 * @brief I2C SMBus alert pin level
 */
typedef enum
{
    I2C_SMBUSALER_LOW,  /*!< SMBus Alert pin low */
    I2C_SMBUSALER_HIGH  /*!< SMBus Alert pin high */
} I2C_SMBUSALER_T;

/**
 * @brief I2C PEC position
 */
typedef enum
{
    I2C_PEC_POSITION_NEXT,      /*!< Indicates that the next byte is PEC */
    I2C_PEC_POSITION_CURRENT    /*!< Indicates that current byte is PEC */
} I2C_PEC_POSITION_T;

/**
 * @brief I2C interrupts definition
 */
typedef enum
{
    I2C_INT_BUF = 0x0400,   /*!< Buffer interrupt */
    I2C_INT_EVT = 0x0200,   /*!< Event interrupt */
    I2C_INT_ERR = 0x0100    /*!< Error interrupt */
} I2C_INT_T;

/**
 * @brief I2C interrupt
 */
typedef enum
{
    I2C_INT_FLAG_SMBALT  = 0x01008000,  /*!< SMBus Alert flag */
    I2C_INT_FLAG_TTE     = 0x01004000,  /*!< Timeout or Tlow error flag */
    I2C_INT_FLAG_PECE    = 0x01001000,  /*!< PEC error in reception flag */
    I2C_INT_FLAG_OVRUR   = 0x01000800,  /*!< Overrun/Underrun flag (Slave mode) */
    I2C_INT_FLAG_AE      = 0x01000400,  /*!< Acknowledge error flag */
    I2C_INT_FLAG_AL      = 0x01000200,  /*!< Arbitration lost flag (Master mode) */
    I2C_INT_FLAG_BERR    = 0x01000100,  /*!< Bus error flag */
    I2C_INT_FLAG_TXBE    = 0x06000080,  /*!< Transmitter data register empty flag */
    I2C_INT_FLAG_RXBNE   = 0x06000040,  /*!< Receiver data register not empty flag */
    I2C_INT_FLAG_STOP    = 0x02000010,  /*!< Stop detection flag (Slave mode) */
    I2C_INT_FLAG_ADDR10  = 0x02000008,  /*!< 10-bit header sent flag (Master mode) */
    I2C_INT_FLAG_BTC     = 0x02000004,  /*!< Byte transfer complete flag */
    I2C_INT_FLAG_ADDR    = 0x02000002,  /*!< Address sent flag (Master mode) */
    I2C_INT_FLAG_START   = 0x02000001,  /*!< Start bit flag (Master mode) */
} I2C_INT_FLAG_T;

/**
 * @brief I2C  flags
 */
typedef enum
{
    /* STS2 register flags */
    I2C_FLAG_DUALADDR,      /*!< Dual flag (Slave mode) */
    I2C_FLAG_SMMHADDR,      /*!< SMBus host header (Slave mode) */
    I2C_FLAG_SMBDADDR,      /*!< SMBus default header (Slave mode) */
    I2C_FLAG_GENCALL,       /*!< General call header flag (Slave mode) */
    I2C_FLAG_TR,            /*!< Transmitter/Receiver flag */
    I2C_FLAG_BUSBSY,        /*!< Bus busy flag */
    I2C_FLAG_MS,            /*!< Master/Slave flag */

    /* STS1 register flags */
    I2C_FLAG_SMBALT,        /*!< SMBus Alert flag */
    I2C_FLAG_TTE,           /*!< Timeout or Tlow error flag */
    I2C_FLAG_PECE,          /*!< PEC error in reception flag */
    I2C_FLAG_OVRUR,         /*!< Overrun/Underrun flag (Slave mode) */
    I2C_FLAG_AE,            /*!< Acknowledge error flag */
    I2C_FLAG_AL,            /*!< Arbitration lost flag (Master mode) */
    I2C_FLAG_BERR,          /*!< Bus error flag */
    I2C_FLAG_TXBE,          /*!< Transmitter data register empty flag */
    I2C_FLAG_RXBNE,         /*!< Receiver data register not empty flag */
    I2C_FLAG_STOP,          /*!< Stop detection flag (Slave mode) */
    I2C_FLAG_ADDR10,        /*!< 10-bit header sent flag (Master mode) */
    I2C_FLAG_BTC,           /*!< Byte transfer complete flag */
    I2C_FLAG_ADDR,          /*!< Address sent flag (Master mode) */
    I2C_FLAG_START,         /*!< Start bit flag (Master mode) */
} I2C_FLAG_T;

/**
 * @brief I2C Events
 */
typedef enum
{
    /* I2C Master Events */
    /* Event 5: Communication start event */
    I2C_EVENT_MASTER_MODE_SELECT                       = 0x00030001,  /*!< BUSBSYFLG, MSFLG and STARTFLG flag */

    /* Event 6: 7-bit Address Acknowledge
       in case of master receiver
     */
    I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED         = 0x00070082,  /*!< BUSBSYFLG, MSFLG, ADDRFLG, TXBEFLG and TRFLG flags */
    I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED            = 0x00030002,  /*!< BUSBSYFLG, MSFLG and ADDRFLG flags */
    /* Event 9: Master has sent the first byte
       in 10-bit address mode
     */
    I2C_EVENT_MASTER_MODE_ADDRESS10                    = 0x00030008,  /*!< BUSBSYFLG, MSFLG and ADDR10FLG flags */

    /* Master RECEIVER mode */
    /* Event 7 */
    I2C_EVENT_MASTER_BYTE_RECEIVED                     = 0x00030040,  /*!< BUSBSYFLG, MSFLG and RXBNEFLG flags */

    /* Master TRANSMITTER mode */
    /* Event 8 */
    I2C_EVENT_MASTER_BYTE_TRANSMITTING                 = 0x00070080,  /*!< TRFLG, BUSBSYFLG, MSFLG, TXBEFLG flags */
    /* Event 8_2 */
    I2C_EVENT_MASTER_BYTE_TRANSMITTED                  = 0x00070084,  /*!< TRFLG, BUSBSYFLG, MSFLG, TXBEFLG and BTCFLG flags */


    /* EV1 (all the events below are variants of EV1) */
    /* 1, Case of One Single Address managed by the slave */
    I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED           = 0x00020002, /*!< BUSBSYFLG and ADDRFLG flags */
    I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED        = 0x00060082, /*!< TRFLG, BUSBSYFLG, TXBEFLG and ADDRFLG flags */

    /* 2, Case of Dual address managed by the slave */
    I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED     = 0x00820000, /*!< DUALF and BUSBSYFLG flags */
    I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED  = 0x00860080, /*!< DUALF, TRFLG, BUSBSYFLG and TXBEFLG flags */

    /* 3, Case of General Call enabled for the slave */
    I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED         = 0x00120000, /*!< GENCALL and BUSBSYFLG flags */


    /* Slave RECEIVER mode */
    /* EV2 */
    I2C_EVENT_SLAVE_BYTE_RECEIVED                      = 0x00020040, /*!< BUSBSYFLG and RXBNEFLG flags */
    I2C_EVENT_SLAVE_BYTE_RECEIVED1                     = 0x00820040, /*!< DUALADDRFLG, BUSBSYFLG and RXBNEFLG flags */
    I2C_EVENT_SLAVE_BYTE_RECEIVED2                     = 0x00120040, /*!< GENCALLFLG, BUSBSYFLG and RXBNEFLG flags */
    /* EV4  */
    I2C_EVENT_SLAVE_STOP_DETECTED                      = 0x00000010, /*!< STOPFLG flag */

    /* Slave TRANSMITTER mode */
    /* EV3 */
    I2C_EVENT_SLAVE_BYTE_TRANSMITTED                   = 0x00060084, /*!< TRFLG, BUSBSYFLG, TXBEFLG and BTCFLG flags */
    I2C_EVENT_SLAVE_BYTE_TRANSMITTED1                  = 0x00860084, /*!< DUALADDRFLG, TRFLG, BUSBSYFLG, TXBEFLG and BTCFLG flags */
    I2C_EVENT_SLAVE_BYTE_TRANSMITTED2                  = 0x00160084, /*!< GENCALLFLG, TRFLG, BUSBSYFLG, TXBEFLG and BTCFLG flags */
    I2C_EVENT_SLAVE_BYTE_TRANSMITTING                  = 0x00060080, /*!< TRFLG, BUSBSYFLG and TXBEFLG flags */
    /* EV3_2 */
    I2C_EVENT_SLAVE_ACK_FAILURE                        = 0x00000400, /*!< AEFLG flag */
} I2C_EVENT_T;

/**@} end of group I2C_Enumerations*/

/** @addtogroup I2C_Structure Data Structure
  @{
*/

/**
 * @brief I2C Config structure definition
 */
typedef struct
{
    uint32_t            clockSpeed;     /*!< I2C clock speed */
    I2C_MODE_T          mode;           /*!< I2C mode */
    I2C_DUTYCYCLE_T     dutyCycle;      /*!< I2C duty cycle */
    uint16_t            ownAddress1;    /*!< I2C own address */
    I2C_ACK_T           ack;            /*!< Acknowledge */
    I2C_ACK_ADDRESS_T   ackAddress;     /*!< I2C acknowledged address */
} I2C_Config_T;

/**@} end of group I2C_Structure*/

/** @defgroup I2C_Functions
  @{
*/

/* I2C reset and configuration */
void I2C_Reset(I2C_T* i2c);
void I2C_Config(I2C_T* i2c, I2C_Config_T* i2cConfig);
void I2C_ConfigStructInit(I2C_Config_T* i2cConfig);
void I2C_Enable(I2C_T* i2c);
void I2C_Disable(I2C_T* i2c);
void I2C_EnableGenerateStart(I2C_T* i2c);
void I2C_DisableGenerateStart(I2C_T* i2c);
void I2C_EnableGenerateStop(I2C_T* i2c);
void I2C_DisableGenerateStop(I2C_T* i2c);
void I2C_EnableAcknowledge(I2C_T* i2c);
void I2C_DisableAcknowledge(I2C_T* i2c);
void I2C_ConfigOwnAddress2(I2C_T* i2c, uint8_t address);
void I2C_EnableDualAddress(I2C_T* i2c);
void I2C_DisableDualAddress(I2C_T* i2c);
void I2C_EnableGeneralCall(I2C_T* i2c);
void I2C_DisableGeneralCall(I2C_T* i2c);
void I2C_EnableSoftwareReset(I2C_T* i2c);
void I2C_DisableSoftwareReset(I2C_T* i2c);
void I2C_EnableStretchClock(I2C_T* i2c);
void I2C_DisableStretchClock(I2C_T* i2c);
void I2C_ConfigFastModeDutyCycle(I2C_T* i2c, I2C_DUTYCYCLE_T dutyCycle);
void I2C_ConfigNACKPosition(I2C_T* i2c, I2C_NACK_POSITION_T NACKPosition);
void I2C_ConfigSMBusAlert(I2C_T* i2c, I2C_SMBUSALER_T SMBusState);
void I2C_EnableARP(I2C_T* i2c);
void I2C_DisableARP(I2C_T* i2c);
uint16_t I2C_ReadRegister(I2C_T* i2c, I2C_REGISTER_T i2cRegister);

/* Transmit Configuration */
void I2C_TxData(I2C_T* i2c, uint8_t data);
uint8_t I2C_RxData(I2C_T* i2c);
void I2C_Tx7BitAddress(I2C_T* i2c, uint8_t address, I2C_DIRECTION_T direction);

/* PEC */
void I2C_EnablePECTransmit(I2C_T* i2c);
void I2C_DisablePECTransmit(I2C_T* i2c);
void I2C_ConfigPECPosition(I2C_T* i2c, I2C_PEC_POSITION_T PECPosition);
void I2C_EnablePEC(I2C_T* i2c);
void I2C_DisablePEC(I2C_T* i2c);
uint8_t I2C_ReadPEC(I2C_T* i2c);

/* DMA */
void I2C_EnableDMA(I2C_T* i2c);
void I2C_DisableDMA(I2C_T* i2c);
void I2C_EnableDMALastTransfer(I2C_T* i2c);
void I2C_DisableDMALastTransfer(I2C_T* i2c);

/* Interrupts and flags */
void I2C_EnableInterrupt(I2C_T* i2c, uint16_t interrupt);
void I2C_DisableInterrupt(I2C_T* i2c, uint16_t interrupt);
uint8_t  I2C_ReadEventStatus(I2C_T* i2c, I2C_EVENT_T i2cEvent);
uint32_t I2C_ReadLastEvent(I2C_T* i2c);
uint8_t I2C_ReadStatusFlag(I2C_T* i2c, I2C_FLAG_T flag);
void I2C_ClearStatusFlag(I2C_T* i2c, I2C_FLAG_T flag);
uint8_t I2C_ReadIntFlag(I2C_T* i2c, I2C_INT_FLAG_T flag);
void I2C_ClearIntFlag(I2C_T* i2c, uint32_t flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_I2C_H */

/**@} end of group I2C_Enumerations */
/**@} end of group I2C_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
