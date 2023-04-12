/*!
 * @file        apm32f10x_i2c.c
 *
 * @brief       This file provides all the I2C firmware functions
 *
 * @version     V1.0.4
 *
 * @date        2022-12-01
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "apm32f10x_i2c.h"
#include "apm32f10x_rcm.h"

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup I2C_Driver I2C Driver
  @{
*/

/** @defgroup I2C_Functions Functions
  @{
*/

/*!
 * @brief     Reset I2C
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_Reset(I2C_T* i2c)
{
    if (i2c == I2C1)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_I2C1);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_I2C1);
    }
    else
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_I2C2);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_I2C2);
    }
}

/*!
 * @brief     Configure I2C by configuring the structure
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     i2cConfig: pointer to a I2C_Config_T structure
 *
 * @retval    None
 */
void I2C_Config(I2C_T* i2c, I2C_Config_T* i2cConfig)
{
    uint16_t tmpreg = 0, freqrange = 0;
    uint32_t PCLK1 = 8000000, PCLK2 = 0;
    uint16_t result = 0x04;

    i2c->I2C_SWITCH = 0;

    /* I2C CTRL2 Configuration */
    RCM_ReadPCLKFreq(&PCLK1, &PCLK2);
    freqrange = PCLK1 / 1000000;
    i2c->CTRL2_B.CLKFCFG = freqrange;

    /* I2C CLKCTRL Configuration */
    i2c->CTRL1_B.I2CEN = BIT_RESET;

    if (i2cConfig->clockSpeed <= 100000)
    {
        result = (PCLK1 / (i2cConfig->clockSpeed << 1));
        if (result < 0x04)
        {
            result = 0x04;
        }
        i2c->RISETMAX = freqrange + 1;
        tmpreg |= result;
    }
    /* Configure speed in fast mode */
    else
    {
        if (i2cConfig->dutyCycle == I2C_DUTYCYCLE_2)
        {
            result = (PCLK1 / (i2cConfig->clockSpeed * 3));
        }
        else
        {
            result = (PCLK1 / (i2cConfig->clockSpeed * 25));
            result |= I2C_DUTYCYCLE_16_9;
        }

        if ((result & 0x0FFF) == 0)
        {
            result |= 0x0001;
        }

        tmpreg |= (uint16_t)(result | 0x8000);
        i2c->RISETMAX = ((((freqrange) * 300) / 1000) + 1);
    }
    i2c->CLKCTRL = tmpreg;
    i2c->CTRL1_B.I2CEN = BIT_SET;

    /* i2c CTRL1 Configuration  */
    i2c->CTRL1_B.ACKEN = BIT_RESET;
    i2c->CTRL1_B.SMBTCFG = BIT_RESET;
    i2c->CTRL1_B.SMBEN = BIT_RESET;

    i2c->CTRL1 |= i2cConfig->mode;
    i2c->CTRL1_B.ACKEN = i2cConfig->ack;

    i2c->SADDR1 = i2cConfig->ackAddress | i2cConfig->ownAddress1;
}

/*!
 * @brief     Fills each I2C_InitStruct member with its default value.
 *
 * @param     i2cConfig: pointer to a I2C_Config_T structure
 *
 * @retval    None
 */
void I2C_ConfigStructInit(I2C_Config_T* i2cConfig)
{
    i2cConfig->clockSpeed = 5000;
    i2cConfig->mode = I2C_MODE_I2C;
    i2cConfig->dutyCycle = I2C_DUTYCYCLE_2;
    i2cConfig->ownAddress1 = 0;
    i2cConfig->ack = I2C_ACK_DISABLE;
    i2cConfig->ackAddress = I2C_ACK_ADDRESS_7BIT;
}

/*!
 * @brief     Enable I2C
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_Enable(I2C_T* i2c)
{
    i2c->CTRL1_B.I2CEN = ENABLE;
}

/*!
 * @brief     Disable I2C
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_Disable(I2C_T* i2c)
{
    i2c->CTRL1_B.I2CEN = DISABLE;
}

/*!
 * @brief     Enable Generates i2c communication START condition.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_EnableGenerateStart(I2C_T* i2c)
{
    i2c->CTRL1_B.START = BIT_SET;
}

/*!
 * @brief     Disable Generates i2c communication START condition.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_DisableGenerateStart(I2C_T* i2c)
{
    i2c->CTRL1_B.START = BIT_RESET;
}

/*!
 * @brief     Enable Generates i2c communication STOP condition.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_EnableGenerateStop(I2C_T* i2c)
{
    i2c->CTRL1_B.STOP = BIT_SET;
}

/*!
 * @brief     Disable Generates i2c communication STOP condition.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_DisableGenerateStop(I2C_T* i2c)
{
    i2c->CTRL1_B.STOP = BIT_RESET;
}

/*!
 * @brief     Enables the specified I2C acknowledge feature.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_EnableAcknowledge(I2C_T* i2c)
{
    i2c->CTRL1_B.ACKEN = ENABLE;
}

/*!
 * @brief     Disables the specified I2C acknowledge feature.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_DisableAcknowledge(I2C_T* i2c)
{
    i2c->CTRL1_B.ACKEN = DISABLE;
}

/*!
 * @brief     Config the specified I2C own address2.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     address:specifies the 7bit I2C own address2.
 *
 * @retval    None
 */
void I2C_ConfigOwnAddress2(I2C_T* i2c, uint8_t address)
{
    i2c->SADDR2_B.ADDR2 = address;
}

/*!
 * @brief     Enables the specified I2C dual addressing mode.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_EnableDualAddress(I2C_T* i2c)
{
    i2c->SADDR2_B.ADDRNUM = ENABLE;
}

/*!
 * @brief     Disables the specified I2C dual addressing mode.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_DisableDualAddress(I2C_T* i2c)
{
    i2c->SADDR2_B.ADDRNUM = DISABLE;
}

/*!
 * @brief     Enables the specified I2C general call feature.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_EnableGeneralCall(I2C_T* i2c)
{
    i2c->CTRL1_B.SRBEN = ENABLE;
}

/*!
 * @brief     Disables the specified I2C general call feature.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_DisableGeneralCall(I2C_T* i2c)
{
    i2c->CTRL1_B.SRBEN = DISABLE;
}

/*!
 * @brief     Send one byte
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     data: data to send
 *
 * @retval    None
 */
void I2C_TxData(I2C_T* i2c, uint8_t data)
{
    i2c->DATA_B.DATA = data;
}

/*!
 * @brief     Returns the recevie data
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    received data
 */
uint8_t I2C_RxData(I2C_T* i2c)
{
    return i2c->DATA_B.DATA;
}

/*!
 * @brief     Transmits the address byte to select the slave device.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     address: slave address which will be transmitted
 *
 * @param     direction: Direction mode
 *              The parameter can be one of following values:
 *              @arg I2C_DIRECTION_TX: Transmitter mode
 *              @arg I2C_DIRECTION_RX: Receiver mode
 * @retval    None
 */
void I2C_Tx7BitAddress(I2C_T* i2c, uint8_t address, I2C_DIRECTION_T direction)
{
    if (direction != I2C_DIRECTION_TX)
    {
        i2c->DATA_B.DATA = address | 0x0001;
    }
    else
    {
        i2c->DATA_B.DATA = address & 0xFFFE;
    }
}

/*!
 * @brief     Reads the I2C register and returns its value.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     i2cRegister : register to read
 *              The parameter can be one of following values:
 *              @arg I2C_REGISTER_CTRL1: CTRL1 register
 *              @arg I2C_REGISTER_CTRL2: CTRL2 register
 *              @arg I2C_REGISTER_SADDR1: SADDR1 register
 *              @arg I2C_REGISTER_SADDR2: SADDR2 register
 *              @arg I2C_REGISTER_DATA: DATA register
 *              @arg I2C_REGISTER_STS1: STS1 register
 *              @arg I2C_REGISTER_STS2: STS2 register
 *              @arg I2C_REGISTER_CLKCTRL: CLKCTRL register
 *              @arg I2C_REGISTER_RISETMAX: RISETMAX register
 *              @arg I2C_REGISTER_SWITCH: SWITCH register
 *
 * @retval    The value of the read register
 */
uint16_t I2C_ReadRegister(I2C_T* i2c, I2C_REGISTER_T i2cRegister)
{
    switch (i2cRegister)
    {
        case I2C_REGISTER_CTRL1:
            return i2c->CTRL1;
        case I2C_REGISTER_CTRL2:
            return i2c->CTRL2;
        case I2C_REGISTER_SADDR1:
            return i2c->SADDR1;
        case I2C_REGISTER_SADDR2:
            return i2c->SADDR2;
        case I2C_REGISTER_DATA:
            return i2c->DATA;
        case I2C_REGISTER_STS1:
            return i2c->STS1;
        case I2C_REGISTER_STS2:
            return i2c->STS2;
        case I2C_REGISTER_CLKCTRL:
            return i2c->CLKCTRL;
        case I2C_REGISTER_RISETMAX:
            return i2c->RISETMAX;
        case I2C_REGISTER_SWITCH:
            return i2c->I2C_SWITCH;
        default:
            return 0;
    }
}

/*!
 * @brief     Enables the I2C software reset.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_EnableSoftwareReset(I2C_T* i2c)
{
    i2c->CTRL1_B.SWRST = ENABLE;
}

/*!
 * @brief     Disables the I2C software reset.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_DisableSoftwareReset(I2C_T* i2c)
{
    i2c->CTRL1_B.SWRST = DISABLE;
}

/*!
 * @brief     Selects the specified I2C NACK position in master receiver mode.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     NACKPosition: specifies the NACK position.
 *
 * @retval    None
 */
void I2C_ConfigNACKPosition(I2C_T* i2c, I2C_NACK_POSITION_T NACKPosition)
{
    if (NACKPosition == I2C_NACK_POSITION_NEXT)
    {
        i2c->CTRL1_B.ACKPOS = BIT_SET;
    }
    else
    {
        i2c->CTRL1_B.ACKPOS = BIT_RESET;
    }
}

/*!
 * @brief     Control the height of pin of SMBusAlert
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     SMBusState: SMBAlert pin level.
 *              The parameter can be one of following values:
 *              @arg I2C_SMBUSALER_LOW: SMBus Alert pin low
 *              @arg I2C_SMBUSALER_HIGH: SMBus Alert pin high
 * @retval    None
 */
void I2C_ConfigSMBusAlert(I2C_T* i2c, I2C_SMBUSALER_T SMBusState)
{
    if (SMBusState == I2C_SMBUSALER_LOW)
    {
        i2c->CTRL1_B.ALERTEN = BIT_SET;
    }
    else
    {
        i2c->CTRL1_B.ALERTEN = BIT_RESET;
    }
}

/*!
 * @brief     Enables the I2C PEC transfer.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_EnablePECTransmit(I2C_T* i2c)
{
    i2c->CTRL1_B.PEC = BIT_SET;
}

/*!
 * @brief     Disables the I2C PEC transfer.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_DisablePECTransmit(I2C_T* i2c)
{
    i2c->CTRL1_B.PEC = BIT_RESET;
}

/*!
 * @brief     Selects the I2C PEC position.
 *
 * @param     i2c: I2C selet 1 or 2
  *
 * @param     PECPosition: PEC position
 *              The parameter can be one of following values:
 *              @arg I2C_PEC_POSITION_NEXT: indicates that the next byte is PEC
 *              @arg I2C_PEC_POSITION_CURRENT: indicates that current byte is PEC
 * @retval    None
 */
void I2C_ConfigPECPosition(I2C_T* i2c, I2C_PEC_POSITION_T PECPosition)
{
    if (PECPosition == I2C_PEC_POSITION_NEXT)
    {
        i2c->CTRL1_B.ACKPOS = BIT_SET;
    }
    else
    {
        i2c->CTRL1_B.ACKPOS = BIT_RESET;
    }
}

/*!
 * @brief     Enables the PEC value calculation of the transferred bytes.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_EnablePEC(I2C_T* i2c)
{
    i2c->CTRL1_B.PECEN = BIT_SET;
}

/*!
 * @brief     Disables the PEC value calculation of the transferred bytes.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_DisablePEC(I2C_T* i2c)
{
    i2c->CTRL1_B.PECEN = BIT_RESET;
}

/*!
 * @brief     Read the PEC value for the I2C.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    value of PEC
 */
uint8_t I2C_ReadPEC(I2C_T* i2c)
{
    return i2c->STS2_B.PECVALUE;
}

/*!
 * @brief     Enables the I2C ARP.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_EnableARP(I2C_T* i2c)
{
    i2c->CTRL1_B.ARPEN = BIT_SET;
}

/*!
* @brief      Disables the I2C ARP.
*
* @param      i2c: I2C selet 1 or 2
*
* @retval     None
*/
void I2C_DisableARP(I2C_T* i2c)
{
    i2c->CTRL1_B.ARPEN = BIT_RESET;
}

/*!
 * @brief     Enables the I2C Clock stretching.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_EnableStretchClock(I2C_T* i2c)
{
    i2c->CTRL1_B.CLKSTRETCHD = BIT_RESET;
}

/*!
 * @brief     Disables the I2C Clock stretching.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_DisableStretchClock(I2C_T* i2c)
{
    i2c->CTRL1_B.CLKSTRETCHD = BIT_SET;
}

/*!
 * @brief     Selects the specified I2C fast mode duty cycle.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     dutyCycle: the fast mode duty cycle.
 *              The parameter can be one of following values:
 *              @arg I2C_DUTYCYCLE_16_9: I2C fast mode Tlow/Thigh = 16/9
 *              @arg I2C_DUTYCYCLE_2: I2C fast mode Tlow/Thigh = 2
 * @retval    None
 */
void I2C_ConfigFastModeDutyCycle(I2C_T* i2c, I2C_DUTYCYCLE_T dutyCycle)
{
    if (dutyCycle == I2C_DUTYCYCLE_16_9)
    {
        i2c->CLKCTRL_B.FDUTYCFG = BIT_SET;
    }
    else
    {
        i2c->CLKCTRL_B.FDUTYCFG = BIT_RESET;
    }
}

/*!
 * @brief     Enables the specified I2C DMA requests.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_EnableDMA(I2C_T* i2c)
{
    i2c->CTRL2_B.DMAEN = ENABLE;
}

/*!
 * @brief     Disable the specified I2C DMA requests.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_DisableDMA(I2C_T* i2c)
{
    i2c->CTRL2_B.DMAEN = DISABLE;
}

/*!
 * @brief     Enable DMA to receive the last transfer
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_EnableDMALastTransfer(I2C_T* i2c)
{
    i2c->CTRL2_B.LTCFG = BIT_SET;
}

/*!
 * @brief     Disable DMA to receive the last transfer
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    None
 */
void I2C_DisableDMALastTransfer(I2C_T* i2c)
{
    i2c->CTRL2_B.LTCFG = BIT_RESET;
}

/*!
 * @brief     Enables the specified I2C interrupts.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     interrupt:I2C interrupts sources
 *              The parameter can be any combination of following values:
 *              @arg I2C_INT_BUF: Buffer interrupt
 *              @arg I2C_INT_EVT: Event interrupt
 *              @arg I2C_INT_ERR: Error interrupt
 *
 * @retval    None
 */
void I2C_EnableInterrupt(I2C_T* i2c, uint16_t interrupt)
{
    i2c->CTRL2 |= interrupt;
}

/*!
 * @brief     Disable the specified I2C interrupts.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     interrupt:I2C interrupts sources
 *              The parameter can be any combination of following values:
 *              @arg I2C_INT_BUF: Buffer interrupt
 *              @arg I2C_INT_EVT: Event interrupt
 *              @arg I2C_INT_ERR: Error interrupt
 *
 * @retval    None
 */
void I2C_DisableInterrupt(I2C_T* i2c, uint16_t interrupt)
{
    i2c->CTRL2 &= ~interrupt;
}

/*!
 * @brief     Check that the last event is equal to the last passed event
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     i2cEvent: the event to be checked.
 *              The parameter can be one of the following values:
 *              @arg I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED           : EV1
 *              @arg I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED              : EV1
 *              @arg I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED     : EV1
 *              @arg I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED        : EV1
 *              @arg I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED            : EV1
 *              @arg I2C_EVENT_SLAVE_BYTE_RECEIVED                         : EV2
 *              @arg I2C_EVENT_SLAVE_BYTE_TRANSMITTED                      : EV3
 *              @arg I2C_EVENT_SLAVE_ACK_FAILURE                           : EV3_2
 *              @arg I2C_EVENT_SLAVE_STOP_DETECTED                         : EV4
 *              @arg I2C_EVENT_MASTER_MODE_SELECT                          : EV5
 *              @arg I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED            : EV6
 *              @arg I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED               : EV6
 *              @arg I2C_EVENT_MASTER_BYTE_RECEIVED                        : EV7
 *              @arg I2C_EVENT_MASTER_BYTE_TRANSMITTING                    : EV8
 *              @arg I2C_EVENT_MASTER_BYTE_TRANSMITTED                     : EV8_2
 *              @arg I2C_EVENT_MASTER_MODE_ADDRESS10                       : EV9
 *
 * @retval    Status: SUCCESS or ERROR
 */
uint8_t  I2C_ReadEventStatus(I2C_T* i2c, I2C_EVENT_T i2cEvent)
{
    uint32_t lastevent = 0;
    uint32_t flag1 = 0, flag2 = 0;

    flag1 = i2c->STS1 & 0x0000FFFF;
    flag2 = i2c->STS2 & 0x0000FFFF;
    flag2 = flag2 << 16;

    lastevent = (flag1 | flag2) & 0x00FFFFFF;

    if ((lastevent & i2cEvent) == i2cEvent)
    {
        return SUCCESS;
    }
    return ERROR;
}

/*!
 * @brief     Read the last i2c Event.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @retval    The last event
 */
uint32_t I2C_ReadLastEvent(I2C_T* i2c)
{
    uint32_t lastevent = 0;
    uint32_t flag1 = 0, flag2 = 0;

    flag1 = i2c->STS1 & 0x0000FFFF;
    flag2 = i2c->STS2 & 0x0000FFFF;
    flag2 = flag2 << 16;

    lastevent = (flag1 | flag2) & 0x00FFFFFF;

    return lastevent;
}

/*!
 * @brief     Check whether the I2C flag is set
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     flag: specifies the I2C flag
 *              The parameter can be one of the following values:
 *              @arg I2C_FLAG_DUALADDR: Dual flag (Slave mode)
 *              @arg I2C_FLAG_SMMHADDR: SMBus host header (Slave mode)
 *              @arg I2C_FLAG_SMBDADDR: SMBus default header (Slave mode)
 *              @arg I2C_FLAG_GENCALL:  General call header flag (Slave mode)
 *              @arg I2C_FLAG_TR:       Transmitter/Receiver flag
 *              @arg I2C_FLAG_BUSBSY:   Bus busy flag
 *              @arg I2C_FLAG_MS:       Master/Slave flag
 *              @arg I2C_FLAG_SMBALT:   SMBus Alert flag
 *              @arg I2C_FLAG_TTE:      Timeout or Tlow error flag
 *              @arg I2C_FLAG_PECE:     PEC error in reception flag
 *              @arg I2C_FLAG_OVRUR:    Overrun/Underrun flag (Slave mode)
 *              @arg I2C_FLAG_AE:       Acknowledge error flag
 *              @arg I2C_FLAG_AL:       Arbitration lost flag (Master mode)
 *              @arg I2C_FLAG_BERR:     Bus error flag
 *              @arg I2C_FLAG_TXBE:     Transmitter data register empty flag
 *              @arg I2C_FLAG_RXBNE:    Receiver data register not empty flag
 *              @arg I2C_FLAG_STOP:     Stop detection flag (Slave mode)
 *              @arg I2C_FLAG_ADDR10:   10-bit header sent flag (Master mode)
 *              @arg I2C_FLAG_BTC:      Byte transfer complete flag
 *              @arg I2C_FLAG_ADDR:     Address sent flag (Master mode)
 *              @arg I2C_FLAG_START:    Start bit flag (Master mode)
 *
 * @retval    Status: flag SET or RESET
 */
uint8_t I2C_ReadStatusFlag(I2C_T* i2c, I2C_FLAG_T flag)
{

    uint8_t status = 0;
    switch (flag)
    {
        case I2C_FLAG_DUALADDR:
            status = i2c->STS2_B.DUALADDRFLG;
            break;
        case I2C_FLAG_SMMHADDR:
            status = i2c->STS2_B.SMMHADDR;
            break;
        case I2C_FLAG_SMBDADDR:
            status = i2c->STS2_B.SMBDADDRFLG;
            break;
        case I2C_FLAG_GENCALL:
            status = i2c->STS2_B.GENCALLFLG;
            break;
        case I2C_FLAG_TR:
            status = i2c->STS2_B.TRFLG;
            break;
        case I2C_FLAG_BUSBSY:
            status = i2c->STS2_B.BUSBSYFLG;
            break;
        case I2C_FLAG_MS:
            status = i2c->STS2_B.MSFLG;
            break;
        case I2C_FLAG_SMBALT:
            status = i2c->STS1_B.SMBALTFLG;
            break;
        case I2C_FLAG_TTE:
            status = i2c->STS1_B.TTEFLG;
            break;
        case I2C_FLAG_PECE:
            status = i2c->STS1_B.PECEFLG;
            break;
        case  I2C_FLAG_OVRUR:
            status = i2c->STS1_B.OVRURFLG;
            break;
        case I2C_FLAG_AE:
            status = i2c->STS1_B.AEFLG;
            break;
        case I2C_FLAG_AL:
            status = i2c->STS1_B.ALFLG;
            break;
        case I2C_FLAG_BERR:
            status = i2c->STS1_B.BERRFLG;
            break;
        case I2C_FLAG_TXBE:
            status = i2c->STS1_B.TXBEFLG;
            break;
        case I2C_FLAG_RXBNE:
            status = i2c->STS1_B.RXBNEFLG;
            break;
        case I2C_FLAG_STOP:
            status = i2c->STS1_B.STOPFLG;
            break;
        case I2C_FLAG_ADDR10:
            status = i2c->STS1_B.ADDR10FLG;
            break;
        case I2C_FLAG_BTC:
            status = i2c->STS1_B.BTCFLG;
            break;
        case I2C_FLAG_ADDR:
            status = i2c->STS1_B.ADDRFLG;
            break;
        case I2C_FLAG_START:
            status = i2c->STS1_B.STARTFLG;
            break;
        default:
            break;
    }
    return status;
}

/*!
 * @brief     Clear the I2C flag
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     flag: specifies the I2C flag
 *              The parameter can be one of the following values:
 *              @arg I2C_FLAG_SMBALT:   SMBus Alert flag
 *              @arg I2C_FLAG_TTE:      Timeout or Tlow error flag
 *              @arg I2C_FLAG_PECE:     PEC error in reception flag
 *              @arg I2C_FLAG_OVRUR:    Overrun/Underrun flag (Slave mode)
 *              @arg I2C_FLAG_AE:       Acknowledge error flag
 *              @arg I2C_FLAG_AL:       Arbitration lost flag (Master mode)
 *              @arg I2C_FLAG_BERR:     Bus error flag
 *
 * @retval    None
 *
 * @note      1)I2C_FLAG_STOP: Stop detection flag is cleared by software sequence:
 *              a read operation to I2C_STS1 register (I2C_ReadStatusFlag())
 *              followed by a write operation to I2C_CRTL1 register (I2C_Enable()).
 *            2)I2C_FLAG_ADDR10: 10-bit header sent flag is cleared by software sequence:
 *              a read operation to I2C_STS1 (I2C_ReadStatusFlag())
 *              followed by writing the second byte of the address in I2C_DATA register.
 *            3)I2C_FLAG_BTC: Byte transfer complete flag is cleared by software sequence:
 *              a read operation to I2C_STS1 register (I2C_ReadStatusFlag())
 *              followed by a read/write to I2C_DATA register (I2C_TxData()).
 *            4)I2C_FLAG_ADDR: Address sent flag is cleared by software sequence:
 *              a read operation to I2C_STS1 register (I2C_ReadStatusFlag())
 *              followed by a read operation to I2C_STS2 register ((void)(I2Cx->STS2)).
 *            5)I2C_FLAG_START: Start bit flag is cleared software sequence:
 *              a read operation to I2C_STS1 register (I2C_ReadStatusFlag())
 *              followed by a write operation to I2C_DATA register (I2C_TxData()).
 */
void I2C_ClearStatusFlag(I2C_T* i2c, I2C_FLAG_T flag)
{
    switch (flag)
    {
        case I2C_FLAG_SMBALT:
            i2c->STS1_B.SMBALTFLG = BIT_RESET;
            break;
        case I2C_FLAG_TTE:
            i2c->STS1_B.TTEFLG = BIT_RESET;
            break;
        case I2C_FLAG_PECE:
            i2c->STS1_B.PECEFLG = BIT_RESET;
            break;
        case  I2C_FLAG_OVRUR:
            i2c->STS1_B.OVRURFLG = BIT_RESET;
            break;
        case I2C_FLAG_AE:
            i2c->STS1_B.AEFLG = BIT_RESET;
            break;
        case I2C_FLAG_AL:
            i2c->STS1_B.ALFLG = BIT_RESET;
            break;
        case I2C_FLAG_BERR:
            i2c->STS1_B.BERRFLG = BIT_RESET;
            break;
        default:
            break;
    }
}

/*!
 * @brief     Check whether the I2C interrupts is set
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     flag: specifies the I2C interrupts
 *              The parameter can be one of the following values:
 *              @arg I2C_INT_FLAG_SMBALT:   SMBus Alert flag
 *              @arg I2C_INT_FLAG_TTE:      Timeout or Tlow error flag
 *              @arg I2C_INT_FLAG_PECE:     PEC error in reception flag
 *              @arg I2C_INT_FLAG_OVRUR:    Overrun/Underrun flag (Slave mode)
 *              @arg I2C_INT_FLAG_AE:       Acknowledge error flag
 *              @arg I2C_INT_FLAG_AL:       Arbitration lost flag (Master mode)
 *              @arg I2C_INT_FLAG_BERR:     Bus error flag
 *              @arg I2C_INT_FLAG_TXBE:     Transmitter data register empty flag
 *              @arg I2C_INT_FLAG_RXBNE:    Receiver data register not empty flag
 *              @arg I2C_INT_FLAG_STOP:     Stop detection flag (Slave mode)
 *              @arg I2C_INT_FLAG_ADDR10:   10-bit header sent flag (Master mode)
 *              @arg I2C_INT_FLAG_BTC:      Byte transfer complete flag
 *              @arg I2C_INT_FLAG_ADDR:     Address sent flag (Master mode)
 *              @arg I2C_INT_FLAG_START:    Start bit flag (Master mode)
 *
 * @retval    Status: flag SET or RESET
 */
uint8_t I2C_ReadIntFlag(I2C_T* i2c, I2C_INT_FLAG_T flag)
{
    uint32_t enablestatus = 0;

    enablestatus = ((flag & 0x07000000) >> 16) & (i2c->CTRL2);
    flag &= 0x00FFFFFF;
    if (((i2c->STS1 & flag) != RESET) && enablestatus)
    {
        return SET;
    }
    return RESET;
}

/*!
 * @brief     Clears the I2C interrupt flag bits.
 *
 * @param     i2c: I2C selet 1 or 2
 *
 * @param     flag: specifies the I2C flag
 *              The parameter can be any combination of the following values:
 *              @arg I2C_INT_FLAG_SMBALT:   SMBus Alert flag
 *              @arg I2C_INT_FLAG_TTE:      Timeout or Tlow error flag
 *              @arg I2C_INT_FLAG_PECE:     PEC error in reception flag
 *              @arg I2C_INT_FLAG_OVRUR:    Overrun/Underrun flag (Slave mode)
 *              @arg I2C_INT_FLAG_AE:       Acknowledge error flag
 *              @arg I2C_INT_FLAG_AL:       Arbitration lost flag (Master mode)
 *              @arg I2C_INT_FLAG_BERR:     Bus error flag
 *
 * @retval    None
 *
 * @note      1)I2C_INT_FLAG_STOP: Stop detection flag is cleared by software sequence:
 *              a read operation to I2C_STS1 register (I2C_ReadIntFlag())
 *              followed by a write operation to I2C_CRTL1 register (I2C_Enable()).
 *            2)I2C_INT_FLAG_ADDR10: 10-bit header sent flag is cleared by software sequence:
 *              a read operation to I2C_STS1 (I2C_ReadIntFlag())
 *              followed by writing the second byte of the address in I2C_DATA register.
 *            3)I2C_INT_FLAG_BTC: Byte transfer complete flag is cleared by software sequence:
 *              a read operation to I2C_STS1 register (I2C_ReadIntFlag())
 *              followed by a read/write to I2C_DATA register (I2C_TxData()).
 *            4)I2C_INT_FLAG_ADDR: Address sent flag is cleared by software sequence:
 *              a read operation to I2C_STS1 register (I2C_ReadIntFlag())
 *              followed by a read operation to I2C_STS2 register ((void)(I2Cx->STS2)).
 *            5)I2C_INT_FLAG_START: Start bit flag is cleared software sequence:
 *              a read operation to I2C_STS1 register (I2C_ReadIntFlag())
 *              followed by a write operation to I2C_DATA register (I2C_TxData()).
 */
void I2C_ClearIntFlag(I2C_T* i2c, uint32_t flag)
{
    i2c->STS1 = (uint16_t)~(flag & 0x00FFFFFF);
}

/**@} end of group I2C_Functions*/
/**@} end of group I2C_Driver*/
/**@} end of group APM32F10x_StdPeriphDriver*/
