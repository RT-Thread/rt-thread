/*!
 * @file        apm32f0xx_i2c.c
 *
 * @brief       This file contains all the functions for the I2C peripheral
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
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
#include "apm32f0xx_i2c.h"
#include "apm32f0xx_rcm.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup I2C_Driver
  @{
*/

/** @defgroup I2C_Macros Macros
  @{
  */

/**@} end of group I2C_Macros */

/** @defgroup I2C_Enumerates Enumerates
  @{
  */

/**@} end of group I2C_Enumerates */

/** @defgroup I2C_Structures Structures
  @{
  */

/**@} end of group I2C_Structures */

/** @defgroup I2C_Variables Variables
  @{
  */

/**@} end of group I2C_Variables */

/** @defgroup I2C_Functions Functions
  @{
  */

/*!
 * @brief     Set the I2C peripheral registers to their default reset values
 *
 * @param     i2c: Select I2C peripheral,it can be I2C1/I2C2.
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
 * @brief       Config the I2C peripheral according to the specified parameters in the adcConfig
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       adcConfig:  Pointer to a I2C_Config_T structure that
 *                          contains the configuration information for the I2C peripheral
 *
 * @retval      None
 */
void I2C_Config(I2C_T* i2c, I2C_Config_T* i2cConfig)
{
    uint32_t temp = 0;

    /* Disable I2C */
    i2c->CTRL1_B.I2CEN = BIT_RESET;

    /* FILTERS Configuration */
    temp = i2c->CTRL1;
    temp &= ((uint32_t)0x00CFE0FF);
    i2c->CTRL1_B.DNFCFG = i2cConfig->digitalfilter;
    i2c->CTRL1_B.ANFD = i2cConfig->analogfilter;

    /* TIMING Configuration */
    i2c->TIMING = i2cConfig-> timing & ((uint32_t)0xF0FFFFFF);

    /* Enable I2C */
    i2c->CTRL1_B.I2CEN = BIT_SET;

    /* ADDR1 Configuration */
    temp = 0;
    i2c->ADDR1 = 0;
    i2c->ADDR2 = 0;

    temp = (uint32_t)((uint32_t)i2cConfig->ackaddress << 10 | \
                      (uint32_t)i2cConfig->address1);

    /* Write to I2C ADDR1 */
    i2c->ADDR1 = temp;

    /* Enable Own Address1 acknowledgement */
    i2c->ADDR1_B.ADDR1EN  = BIT_SET;

    /* Mode Configuration */
    i2c->CTRL1 &= 0xFFCFFFF;
    temp = i2cConfig->mode;
    i2c->CTRL1 |= temp;

    /* Ack Configuration */
    i2c->CTRL2_B.NACKEN = i2cConfig->ack;
}

/*!
 * @brief       Fills each i2cConfig member with its default value
 *
 * @param       i2cConfig:    Pointer to a I2C_Config_T structure which will be initialized
 *
 * @retval      None
 */
void I2C_ConfigStructInit(I2C_Config_T* i2cConfig)
{
    i2cConfig->timing   = 0;
    i2cConfig->address1 = 0;
    i2cConfig->mode     = I2C_MODE_I2C;
    i2cConfig->analogfilter  = I2C_ANALOG_FILTER_ENABLE;
    i2cConfig->digitalfilter = I2C_DIGITAL_FILTER_0;

    i2cConfig->ack = I2C_ACK_DISABLE;
    i2cConfig->ackaddress = I2C_ACK_ADDRESS_7BIT;
}

/*!
 * @brief       Enable the I2C peripheral
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_Enable(I2C_T* i2c)
{
    i2c->CTRL1_B.I2CEN = BIT_SET;
}

/*!
 * @brief       Disable the I2C peripheral
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_Disable(I2C_T* i2c)
{
    i2c->CTRL1_B.I2CEN = BIT_RESET;
}

/*!
 * @brief       I2C Soft ware Reset
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_SoftwareReset(I2C_T* i2c)
{
    i2c->CTRL1_B.I2CEN = BIT_RESET;
    *(__IO uint32_t*)(uint32_t)i2c;
    i2c->CTRL1_B.I2CEN = BIT_SET;
}

/*!
 * @brief       Enables the specified interrupts
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       interrupt:  Specifies the I2C interrupts sources
 *                          The parameter can be combination of following values:
 *                          @arg I2C_INT_TXIE:    TX Interrupt enable
 *                          @arg I2C_INT_RXIE:    RX Interrupt enable
 *                          @arg I2C_INT_ADDRIE:  Address match interrupt enable (slave only)
 *                          @arg I2C_INT_NACKIE:  Not acknowledge received interrupt enable
 *                          @arg I2C_INT_STOPIE:  STOP detection Interrupt enable
 *                          @arg I2C_INT_TXCIE:   Transfer complete interrupt enable
 *                          @arg I2C_INT_ERRIE:   Error interrupts enable
 *
 * @retval      None
 */
void I2C_EnableInterrupt(I2C_T* i2c, uint8_t interrupt)
{
    i2c->CTRL1 |= (uint32_t)interrupt;
}

/*!
 * @brief       Disable the specified interrupts
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       interrupt:  Specifies the I2C interrupts sources
 *                          The parameter can be combination of following values:
 *                          @arg I2C_INT_TXIE:    TX Interrupt enable
 *                          @arg I2C_INT_RXIE:    RX Interrupt enable
 *                          @arg I2C_INT_ADDRIE:  Address match interrupt enable (slave only)
 *                          @arg I2C_INT_NACKIE:  Not acknowledge received interrupt enable
 *                          @arg I2C_INT_STOPIE:  STOP detection Interrupt enable
 *                          @arg I2C_INT_TXCIE:   Transfer complete interrupt enable
 *                          @arg I2C_INT_ERRIE:   Error interrupts enable
 *
 * @retval      None
 */
void I2C_DisableInterrupt(I2C_T* i2c, uint8_t interrupt)
{
    i2c->CTRL1 &= (uint32_t)~interrupt;
}

/*!
 * @brief       Enables the stretch clock
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_EnableStretchClock(I2C_T* i2c)
{
    i2c->CTRL1_B.CLKSTRETCHD = BIT_RESET;
}

/*!
 * @brief       Disables the stretch clock
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_DisableStretchClock(I2C_T* i2c)
{
    i2c->CTRL1_B.CLKSTRETCHD = BIT_SET;
}

/*!
 * @brief       Enables the stop mode
 *
 * @param       i2c:   Select I2C peripheral, It can be I2C1.
 *
 * @retval      None
 *
 * @note        It's not for APM32F030 devices
 */
void I2C_EnableStopMode(I2C_T* i2c)
{
    i2c->CTRL1_B.WUPEN = BIT_SET;
}

/*!
 * @brief       Disable the stop mode
 *
 * @param       i2c:   Select I2C peripheral, It can be I2C1.
 *
 * @retval      None
 *
 * @note        It's not for APM32F030 devices
 */
void I2C_DisableStopMode(I2C_T* i2c)
{
    i2c->CTRL1_B.WUPEN = BIT_RESET;
}

/*!
 * @brief       Enables the I2C own address 2
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_EnableOwnAddress2(I2C_T* i2c)
{
    i2c->ADDR2_B.ADDR2EN = BIT_SET;
}

/*!
 * @brief       Disables the I2C own address 2
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_DisableOwnAddress2(I2C_T* i2c)
{
    i2c->ADDR2_B.ADDR2EN = BIT_RESET;
}

/*!
 * @brief       I2C slave own address 2 and mask
 *
 * @param       i2c:  Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       mask: Own address 2 mask selection
 *                    The parameter can be one of following values:
 *                    @arg I2C_ADDR2MSK_NOMASK: No masked
 *                    @arg I2C_ADDR2MSK_MASK01: Don't care masked ADDR2[1:0]
 *                    @arg I2C_ADDR2MSK_MASK02: Don't care masked ADDR2[2:1]
 *                    @arg I2C_ADDR2MSK_MASK03: Don't care masked ADDR2[3:1]
 *                    @arg I2C_ADDR2MSK_MASK04: Don't care masked ADDR2[4:1]
 *                    @arg I2C_ADDR2MSK_MASK05: Don't care masked ADDR2[5:1]
 *                    @arg I2C_ADDR2MSK_MASK06: Don't care masked ADDR2[6:1]
 *                    @arg I2C_ADDR2MSK_MASK07: Don't care masked ADDR2[7:1]
 *
 * @retval      None
 */
void I2C_OwnAddress2Mask(I2C_T* i2c, uint16_t address, I2C_ADDR2MSK_T mask)
{
    i2c->ADDR2_B.ADDR2 = address;
    i2c->ADDR2_B.ADDR2MSK = mask;

}

/*!
 * @brief       Enables the Broadcast call mode
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_EnableBroadcastCall(I2C_T* i2c)
{
    i2c->CTRL1_B.RBEN = BIT_SET;
}

/*!
 * @brief       Disables the Broadcast call mode
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_DisableBroadcastCall(I2C_T* i2c)
{
    i2c->CTRL1_B.RBEN = BIT_RESET;
}

/*!
 * @brief       Enables the slave byte control
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_EnableSlaveByteControl(I2C_T* i2c)
{
    i2c->CTRL1_B.SBCEN = BIT_SET;
}

/*!
 * @brief       Disables the slave byte control
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_DisableSlaveByteControl(I2C_T* i2c)
{
    i2c->CTRL1_B.SBCEN = BIT_RESET;
}

/*!
 * @brief       Configures the slave address
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       address: set I2C slave uint16_t Address
 *
 * @retval      None
 */
void I2C_SlaveAddress(I2C_T* i2c, uint16_t address)
{
    uint32_t temp = 0;
    temp = i2c->CTRL2;

    temp &= (uint32_t)~((uint32_t)0x000003FF);
    i2c->CTRL2 = temp;

    i2c->ADDR2_B.ADDR2 = address;
}

/*!
 * @brief       Enables I2C 10-bit addressing mode for the master
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_Enable10BitAddressingMode(I2C_T* i2c)
{
    i2c->CTRL2_B.SADDRLEN = BIT_SET;
}

/*!
 * @brief       Disables I2C 10-bit addressing mode for the master
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_Disable10BitAddressingMode(I2C_T* i2c)
{
    i2c->CTRL2_B.SADDRLEN = BIT_RESET;
}

/*!
 * @brief       Enables the I2C automatic end mode
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_EnableAutoEnd(I2C_T* i2c)
{
    i2c->CTRL2_B.ENDCFG = BIT_SET;
}

/*!
 * @brief       Disables the I2C automatic end mode
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_DisableAutoEnd(I2C_T* i2c)
{
    i2c->CTRL2_B.ENDCFG = BIT_RESET;
}

/*!
 * @brief       Enables the I2C nbytes reload mode
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_EnableReload(I2C_T* i2c)
{
    i2c->CTRL2_B.RELOADEN = BIT_SET;
}

/*!
 * @brief       Disables the I2C nbytes reload mode
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_DisableReload(I2C_T* i2c)
{
    i2c->CTRL2_B.RELOADEN = BIT_RESET;
}

/*!
 * @brief       Configures the number of bytes to be transmitted/received
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       number:Set uint8_t bytes to read or write
 *
 * @retval      None
 */
void I2C_ConfigNumberOfBytes(I2C_T* i2c, uint8_t number)
{
    i2c->CTRL2_B.NUMBYT = 0xFF;
    i2c->CTRL2_B.NUMBYT  &= (uint8_t) number ;
}

/*!
 * @brief       Configures the type of transfer request for the master
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       direction: selects the I2C transfer direction.
 *                         The parameter can be one of following values:
 *                         @arg I2C_DIRECTION_TX:   Transmission direction
 *                         @arg I2C_DIRECTION_RX:   Reception direction
 *
 * @retval      None
 */
void I2C_ConfigMasterRequest(I2C_T* i2c, I2C_DIRECTION_T  direction)
{
    i2c->CTRL2_B.TXDIR  =  direction ;
}

/*!
 * @brief       Enables the generates i2c communication start condition
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_EnableGenerateStart(I2C_T* i2c)
{
    i2c->CTRL2_B.START = BIT_SET;
}

/*!
 * @brief       Disables the generates i2c communication start condition
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_DisableGenerateStart(I2C_T* i2c)
{
    i2c->CTRL2_B.START = BIT_RESET;
}

/*!
 * @brief       Enables the generates i2c communication stop condition
 *
 * @param       i2c:   Select I2C peripheral
 *                      This parameter can be any combination of the following values:
 *                     @arg I2C1
 *                     @arg I2C2
 *
 * @retval      None
 */
void I2C_EnableGenerateStop(I2C_T* i2c)
{
    i2c->CTRL2_B.STOP = BIT_SET;
}

/*!
 * @brief       Disables the generates i2c communication stop condition
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_DisableGenerateStop(I2C_T* i2c)
{
    i2c->CTRL2_B.STOP = BIT_RESET;
}

/*!
 * @brief       Enables I2C 10-bit header only mode with read direction
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_Enable10BitAddressHeader(I2C_T* i2c)
{
    i2c->CTRL2_B.ADDR10 = BIT_SET;
}

/*!
 * @brief       Disables I2C 10-bit header only mode with read direction
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_Disable10BitAddressHeader(I2C_T* i2c)
{
    i2c->CTRL2_B.ADDR10 = BIT_RESET;
}

/*!
 * @brief       Enables I2C communication Acknowledge
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_EnableAcknowledge(I2C_T* i2c)
{
    i2c->CTRL2_B.NACKEN = BIT_RESET;
}

/*!
 * @brief       Disables I2C communication Acknowledge
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_DisableAcknowledge(I2C_T* i2c)
{
    i2c->CTRL2_B.NACKEN = BIT_SET;
}

/*!
 * @brief       Returns the I2C slave matched address
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      The value is slave matched address
 */
uint8_t I2C_ReadAddressMatched(I2C_T* i2c)
{
    return ((uint8_t)i2c->STS_B.ADDRCMFLG);
}

/*!
 * @brief       Returns the I2C slave received request
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      The value of the received request
 */
uint16_t I2C_ReadTransferDirection(I2C_T* i2c)
{
    uint16_t direction = 0;
    uint32_t temp = 0;

    temp = (uint32_t) i2c->STS_B.TXDIRFLG;

    if (temp == 0)
    {
        direction = (uint16_t)I2C_DIRECTION_TX;
    }
    else
    {
        direction = (uint16_t)(I2C_DIRECTION_RX << 10);
    }

    return direction;
}

/*!
 * @brief       Handles I2Cx communication when starting transfer or during transfer
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       address:    specifies the slave address to be programmed.
 *
 * @param       number:     specifies the number of bytes to be programmed.
 *                          This parameter must be a value between 0 and 255.
 *
 * @param       reloadend:  the I2C reload end mode
 *                          The parameter can be one of following values:
 *                          @arg I2C_RELOAD_MODE_RELOAD:  Enable Reload mode.
 *                          @arg I2C_RELOAD_MODE_AUTOEND: Enable Automatic end mode.
 *                          @arg I2C_RELOAD_MODE_SOFTEND: Enable Software end mode.
 *
 * @param       generates:  the I2C start/stop mode
 *                          The parameter can be one of following values:
 *                          @arg I2C_GENERATE_NO_STARTSTOP: Don't Generate stop and start condition.
 *                          @arg I2C_GENERATE_START_WRITE:  Generate Restart for write request.
 *                          @arg I2C_GENERATE_STOP:         Generate stop condition
 *                          @arg I2C_GENERATE_START_READ:   Generate Restart for read request.
 *
 * @retval      None
 */
void I2C_HandlingTransfer(I2C_T* i2c, uint16_t address, uint8_t number, I2C_RELOAD_MODE_T reloadend, I2C_GENERATE_T generates)
{
    uint32_t temp = 0;

    /* Get the CTRL2 register value */
    temp = i2c->CTRL2;

    /* clear temp specific bits */
    temp &= (uint32_t)~((uint32_t)(I2C_CTRL2_SADD | I2C_CTRL2_NUMBYT | I2C_CTRL2_MASK));

    /* update temp */
    temp |= (uint32_t)(((uint32_t)address & I2C_CTRL2_SADD) | (((uint32_t)number << 16) & I2C_CTRL2_NUMBYT) | \
                       (uint32_t)reloadend | (uint32_t)generates);

    /* update CTRL2 register */
    i2c->CTRL2 = temp;
}

/*!
 * @brief       Enables I2C SMBus alert
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @retval      None
 */
void I2C_EnableSMBusAlert(I2C_T* i2c)
{
    i2c->CTRL1_B.ALTEN = BIT_SET;
}

/*!
 * @brief       Disables I2C SMBus alert
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @retval      None
 */
void I2C_DisableSMBusAlert(I2C_T* i2c)
{
    i2c->CTRL1_B.ALTEN = BIT_RESET;
}

/*!
 * @brief       Enable I2C SMBus HADDREN
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_EnableSMBusHAEN(I2C_T* i2c)
{
    i2c->CTRL1_B.HADDREN = BIT_SET;
}

/*!
 * @brief       Disable I2C SMBus HADDREN
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_DisableSMBusHAEN(I2C_T* i2c)
{
    i2c->CTRL1_B.HADDREN = BIT_RESET;
}

/*!
 * @brief       Enable I2C SMBus DEADDREN
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */

void I2C_EnableSMBusDAEN(I2C_T* i2c)
{
    i2c->CTRL1_B.DEADDREN = BIT_SET;
}

/*!
 * @brief       Disable I2C SMBus DEADDREN
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      None
 */
void I2C_DisableSMBusDAEN(I2C_T* i2c)
{
    i2c->CTRL1_B.DEADDREN = BIT_RESET;
}

/*!
 * @brief       Enables I2C Clock Timeout
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @retval      None
 */
void I2C_EnableClockTimeout(I2C_T* i2c)
{
    i2c->TIMEOUT_B.CLKTOEN = BIT_SET;
}

/*!
 * @brief       Disables I2C Clock Timeout
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @retval      None
 */
void I2C_DisableClockTimeout(I2C_T* i2c)
{
    i2c->TIMEOUT_B.CLKTOEN = BIT_RESET;
}

/*!
 * @brief       Enables I2C Extend Clock Timeout
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @retval      None
 */
void I2C_EnableExtendClockTimeout(I2C_T* i2c)
{
    i2c->TIMEOUT_B.EXCLKTOEN = BIT_SET;
}

/*!
 * @brief       Disables I2C Extend Clock Timeout
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @retval      None
 */
void I2C_DisableExtendClockTimeout(I2C_T* i2c)
{
    i2c->TIMEOUT_B.EXCLKTOEN = BIT_RESET;
}

/*!
 * @brief       Enables I2C Idle Clock Timeout
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @retval      None
 */
void I2C_EnableIdleClockTimeout(I2C_T* i2c)
{
    i2c->TIMEOUT_B.IDLECLKTO = BIT_SET;
}

/*!
 * @brief       Disables I2C Idle Clock Timeout
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @retval      None
 */
void I2C_DisableIdleClockTimeout(I2C_T* i2c)
{
    i2c->TIMEOUT_B.IDLECLKTO = BIT_RESET;
}

/*!
 * @brief       Configures the I2C Bus Timeout A
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @param       timeout: specifies the Timeout A to be programmed
 *
 * @retval      None
 */
void I2C_ConfigTimeoutA(I2C_T* i2c, uint16_t timeout)
{
    i2c->TIMEOUT_B.TIMEOUTA = timeout;
}

/*!
 * @brief       Configures the I2C Bus Timeout B
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @param       timeout: specifies the Timeout B to be programmed
 *
 * @retval      None
 */
void I2C_ConfigTimeoutB(I2C_T* i2c, uint16_t timeout)
{
    i2c->TIMEOUT_B.TIMEOUTB = timeout;
}

/*!
 * @brief       Enables I2C PEC calculation
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @retval      None
 */
void I2C_EnablePEC(I2C_T* i2c)
{
    i2c->CTRL1_B.PECEN = BIT_SET;
}

/*!
 * @brief       Disables I2C PEC calculation
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @retval      None
 */
void I2C_DisablePEC(I2C_T* i2c)
{
    i2c->CTRL1_B.PECEN = BIT_RESET;
}

/*!
 * @brief       Enables I2C PEC transmission/reception request
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @retval      None
 */
void I2C_EnablePECRequest(I2C_T* i2c)
{
    i2c->CTRL2_B.PEC = BIT_SET;
}

/*!
 * @brief       Disables I2C PEC transmission/reception request
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @retval      None
 */
void I2C_DisablePECRequest(I2C_T* i2c)
{
    i2c->CTRL2_B.PEC = BIT_RESET;
}

/*!
 * @brief       Returns the I2C PEC
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1.
 *
 * @retval      The value is PEC
 */
uint8_t I2C_ReadPEC(I2C_T* i2c)
{
    return ((uint8_t)i2c->PEC_B.PEC);
}

/*!
 * @brief       Reads the specified I2C register and returns its value
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       registers:  Specifies the I2C interrupts sources
 *                          The parameter can be one of following values:
 *                          @arg I2C_REGISTER_CTRL1:    CTRL1 register
 *                          @arg I2C_REGISTER_CTRL2:    CTRL2 register
 *                          @arg I2C_REGISTER_ADDR1:    ADDR1 register
 *                          @arg I2C_REGISTER_ADDR2:    ADDR2 register
 *                          @arg I2C_REGISTER_TIMING:   TIMING register
 *                          @arg I2C_REGISTER_TIMEOUT:  TIMEOUT register
 *                          @arg I2C_REGISTER_STS:      STS register
 *                          @arg I2C_REGISTER_INTFCLR:  INTFCLR register
 *                          @arg I2C_REGISTER_PEC:      PEC register
 *                          @arg I2C_REGISTER_RXDATA:   RXDATA register
 *                          @arg I2C_REGISTER_TXDATA:   TXDATA register
 *
 * @retval      None
 */
uint32_t I2C_ReadRegister(I2C_T* i2c, uint8_t registers)
{
    __IO uint32_t temp = 0;

    temp = (uint32_t)i2c;
    temp += registers;

    return (*(__IO uint32_t*) temp);
}

/*!
 * @brief       Send a byte by writing in the TXDATA register
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       data:   Byte to be sent
 *
 * @retval      None
 */
void I2C_TxData(I2C_T* i2c, uint8_t data)
{
    i2c->TXDATA = (uint32_t)data;
}

/*!
 * @brief       Returns the most recent received data
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @retval      The value of the received byte data
 */
uint8_t I2C_RxData(I2C_T* i2c)
{
    return (uint8_t)i2c->RXDATA;
}

/*!
 * @brief       Enables the I2C DMA interface
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       request: DMA transfer request
 *                       The parameter can be one of following values:
 *                       @arg I2C_DMA_REQ_TX:   TX DMA Transmission request
 *                       @arg I2C_DMA_REQ_RX:   RX DMA Transmission request
 *
 * @retval      None
 */
void I2C_EnableDMA(I2C_T* i2c, I2C_DMA_REQ_T request)
{
    if (request == I2C_DMA_REQ_TX)
    {
        i2c->CTRL1_B.DMATXEN = BIT_SET;
    }
    else
    {
        i2c->CTRL1_B.DMARXEN = BIT_SET;
    }
}

/*!
 * @brief       Disables the I2C DMA interface
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       request: DMA transfer request
 *                       The parameter can be one of following values:
 *                       @arg I2C_DMA_REQ_TX:   TX DMA Transmission request
 *                       @arg I2C_DMA_REQ_RX:   RX DMA Transmission request
 *
 * @retval      None
 */
void I2C_DisableDMA(I2C_T* i2c, I2C_DMA_REQ_T request)
{
    if (request == I2C_DMA_REQ_TX)
    {
        i2c->CTRL1_B.DMATXEN = BIT_RESET;
    }
    else
    {
        i2c->CTRL1_B.DMARXEN = BIT_RESET;
    }
}

/*!
 * @brief       Checks whether the specified I2C flag is set or not
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       flag:    Specifies the flag to check
 *                       The parameter can be one of following values:
 *                       @arg I2C_FLAG_TXBE:  Transmit buffer data register empty flag
 *                       @arg I2C_FLAG_TXINT: Transmit interrupt flag
 *                       @arg I2C_FLAG_RXBNE: Read buffer data register not empty flag
 *                       @arg I2C_FLAG_ADDR:  Address Sent/Matched (master/slave) flag
 *                       @arg I2C_FLAG_NACK:  Not acknowledge received flag
 *                       @arg I2C_FLAG_STOP:  Stop detected flag
 *                       @arg I2C_FLAG_TXCF:  Transfer complete flag
 *                       @arg I2C_FLAG_TCRF:  Transfer complete reload flag
 *                       @arg I2C_FLAG_BUSERR:Bus error flag
 *                       @arg I2C_FLAG_ALF:   Arbitration Loss flag
 *                       @arg I2C_FLAG_OVR:   Overrun/Underrun flag
 *                       @arg I2C_FLAG_PECERR:PEC error flag
 *                       @arg I2C_FLAG_TIMEOUT: Timeout or t_low detection flag
 *                       @arg I2C_FLAG_ALERT: SMBus alert flag
 *                       @arg I2C_FLAG_BUSY:  Bus Busy Flag
 *
 * @retval      Status of interrupt flag(SET or RESET)
 */
uint8_t I2C_ReadStatusFlag(I2C_T* i2c, I2C_FLAG_T flag)
{
    uint32_t status = 0;

    status = (uint32_t)(i2c->STS & (flag));

    if (status == flag)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear flags
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       flag:   Specifies the flag to clear
 *                       The parameter can be combination of following values:
 *                       @arg I2C_FLAG_ADDR:  Address Sent/Matched (master/slave) flag
 *                       @arg I2C_FLAG_NACK:  Not acknowledge received flag
 *                       @arg I2C_FLAG_STOP:  Stop detected flag
 *                       @arg I2C_FLAG_BUSERR:Bus error flag
 *                       @arg I2C_FLAG_ALF:   Arbitration Loss flag
 *                       @arg I2C_FLAG_OVR:   Overrun/Underrun flag
 *                       @arg I2C_FLAG_PECERR:PEC error flag
 *                       @arg I2C_FLAG_TIMEOUT: Timeout or t_low detection flag
 *                       @arg I2C_FLAG_ALERT: SMBus alert flag
 *
 * @retval      None
 */
void I2C_ClearStatusFlag(I2C_T* i2c, uint32_t flag)
{
    i2c->INTFCLR = (uint32_t)flag;
}

/*!
 * @brief       Checks whether the specified interrupt has occurred or not
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       flag:   Specifies the I2C interrupt pending bit to check
 *                      The parameter can be one of following values:
 *                      @arg I2C_INT_FLAG_TXINT:    Transmit interrupt flag
 *                      @arg I2C_INT_FLAG_RXBNE:    Read Buffer Data Register Not Empty interrupt flag
 *                      @arg I2C_INT_FLAG_ADDR:     Address Sent/Matched (master/slave) interrupt flag
 *                      @arg I2C_INT_FLAG_NACK:     Not acknowledge received interrupt flag
 *                      @arg I2C_INT_FLAG_STOP:     Stop detected interrupt flag
 *                      @arg I2C_INT_FLAG_TXCF:     Transfer complete interrupt flag
 *                      @arg I2C_INT_FLAG_TCRF:     Transfer Complete Reloadinterrupt flag

 *                      @arg I2C_INT_FLAG_BUSERR:   Bus error interrupt flag
 *                      @arg I2C_INT_FLAG_ALF:      Arbitration Loss interrupt flag
 *                      @arg I2C_INT_FLAG_OVR:      Overrun/Underrun interrupt flag
 *                      @arg I2C_INT_FLAG_PECERR:   PEC error interrupt flag
 *                      @arg I2C_INT_FLAG_TIMEOUT:  Timeout or t_low detection interrupt flag
 *                      @arg I2C_INT_FLAG_ALERT:    SMBus alert interrupt flag
 *
 * @retval      Status of interrupt flag(SET or RESET)
 */
uint8_t I2C_ReadIntFlag(I2C_T* i2c, I2C_INT_FLAG_T flag)
{
    uint32_t temp = 0;
    uint32_t enable = 0;

    if (flag & ((uint32_t)0x000000C0))
    {
        enable = (uint32_t)((BIT6) & (i2c->CTRL1));
    }
    else if (flag & ((uint32_t)0x00003F00))
    {
        enable = (uint32_t)((BIT7) & (i2c->CTRL1));
    }
    else
    {
        enable = (uint32_t)((flag) & (i2c->CTRL1));
    }

    temp = i2c->STS;

    temp &= flag;

    if ((temp != 0) && enable)
    {
        return SET;
    }
    else
    {
        return RESET;
    }
}

/*!
 * @brief       Clears the specified interrupt pending bits
 *
 * @param       i2c: Select I2C peripheral,it can be I2C1/I2C2.
 *
 * @param       flag:   Specifies the I2C interrupt pending bit to clear
 *                      The parameter can be combination of following values:
 *                       @arg I2C_INT_FLAG_ADDR:  Address Sent/Matched (master/slave) flag
 *                       @arg I2C_INT_FLAG_NACK:  Not acknowledge received flag
 *                       @arg I2C_INT_FLAG_STOP:  Stop detected flag
 *                       @arg I2C_INT_FLAG_BUSERR:Bus error flag
 *                       @arg I2C_INT_FLAG_ALF:   Arbitration Loss flag
 *                       @arg I2C_INT_FLAG_OVR:   Overrun/Underrun flag
 *                       @arg I2C_INT_FLAG_PECERR:PEC error flag
 *                       @arg I2C_INT_FLAG_TIMEOUT: Timeout or t_low detection flag
 *                       @arg I2C_INT_FLAG_ALERT: SMBus alert flag
 *
 * @retval
 */

void I2C_ClearIntFlag(I2C_T* i2c, uint32_t flag)
{
    i2c->INTFCLR = (uint32_t)flag;
}

/**@} end of group I2C_Functions */
/**@} end of group I2C_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */
