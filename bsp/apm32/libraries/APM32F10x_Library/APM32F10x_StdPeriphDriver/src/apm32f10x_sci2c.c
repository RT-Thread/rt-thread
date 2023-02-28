/*!
 * @file        apm32f10x_sci2c.c
 *
 * @brief       This file contains all the functions for the SCI2C peripheral
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

#include "apm32f10x_sci2c.h"
#include "apm32f10x_rcm.h"

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup SCI2C_Driver SCI2C Driver
  * @brief SCI2C driver modules
  @{
*/

/** @defgroup SCI2C_Functions Functions
  @{
*/

/*!
 * @brief       Set I2C peripheral registers to their default reset values
 *
 * @param       i2c: Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      None
 */
void SCI2C_Reset(SCI2C_T* i2c)
{
    if (i2c == I2C3)
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_I2C1);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_I2C1);
    }
    else
    {
        RCM_EnableAPB1PeriphReset(RCM_APB1_PERIPH_I2C2);
        RCM_DisableAPB1PeriphReset(RCM_APB1_PERIPH_I2C2);
    }

    i2c->SW = 0;
    i2c->SW = 1;
    i2c->INTEN = 0;
}

/*!
 * @brief       Configures the I2C peripheral according to the specified parameters in the sci2cConfig
 *
 * @param       i2c: Select the the I2C peripheral.It can be I2C3 or I2C4
 *
 * @param       sci2cConfig: pointer to a SCI2C_Config_T structure
 *
 * @retval      None
 */
void SCI2C_Config(SCI2C_T* i2c, SCI2C_Config_T* sci2cConfig)
{
    i2c->SW = BIT_SET;

    i2c->CTRL2_B.I2CEN = BIT_RESET;

    if (sci2cConfig->mode == SCI2C_MODE_MASTER)
    {
        i2c->CTRL1_B.MST = BIT_SET;
        i2c->CTRL1_B.SLADIS = BIT_SET;
    }
    else
    {
        i2c->CTRL1_B.MST = BIT_RESET;
    }

    i2c->CTRL1_B.SPD = sci2cConfig->speed;
    i2c->CTRL1_B.RSTAEN = sci2cConfig->restart;

    i2c->TFT = sci2cConfig->txFifoThreshold;
    i2c->RFT = sci2cConfig->rxFifoThreshold;

    i2c->TARADDR_B.MAM = sci2cConfig->addrMode;
    i2c->CTRL1_B.SAM = sci2cConfig->addrMode;
    i2c->SLAADDR = sci2cConfig->slaveAddr;

    if (sci2cConfig->speed == SCI2C_SPEED_STANDARD)
    {
        i2c->SSCLC = sci2cConfig->clkLowPeriod;
        i2c->SSCHC = sci2cConfig->clkHighPeriod;
    }
    else if (sci2cConfig->speed == SCI2C_SPEED_FAST)
    {
        i2c->FSCLC = sci2cConfig->clkLowPeriod;
        i2c->FSCHC = sci2cConfig->clkHighPeriod;
    }
    else if (sci2cConfig->speed == SCI2C_SPEED_HIGH)
    {
        i2c->HSCLC = sci2cConfig->clkLowPeriod;
        i2c->HSCHC = sci2cConfig->clkHighPeriod;
    }
}

/*!
 * @brief       Fills each sci2cConfig member with its default value
 *
 * @param       sci2cConfig: pointer to a SCI2C_Config_T structure
 *
 * @retval      None
 */
void SCI2C_ConfigStructInit(SCI2C_Config_T* sci2cConfig)
{
    sci2cConfig->addrMode = SCI2C_ADDR_MODE_7BIT;
    sci2cConfig->slaveAddr = 0x55;
    sci2cConfig->clkHighPeriod = 0x3C;
    sci2cConfig->clkLowPeriod = 0x82;
    sci2cConfig->mode = SCI2C_MODE_MASTER;
    sci2cConfig->restart = SCI2C_RESTART_ENABLE;
    sci2cConfig->rxFifoThreshold = 0;
    sci2cConfig->txFifoThreshold = 0;
    sci2cConfig->speed = SCI2C_SPEED_FAST;
}

/*!
 * @brief       Read specified flag
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       flag:   Specifies the flag to be checked
 *                      The parameter can be one of following values:
 *                      @arg SCI2C_FLAG_ACT:    Activity flag
 *                      @arg SCI2C_FLAG_TFNF:   Tx FIFO not full flag
 *                      @arg SCI2C_FLAG_TFE:    TX FIFO empty flag
 *                      @arg SCI2C_FLAG_RFNE:   Rx FIFO not empty flag
 *                      @arg SCI2C_FLAG_RFF:    Rx FIFO full flag
 *                      @arg SCI2C_FLAG_MA:     Master activity flag
 *                      @arg SCI2C_FLAG_SA:     Slave activity flag
 *                      @arg SCI2C_FLAG_I2CEN:  I2C enable flag
 *                      @arg SCI2C_FLAG_SDWB:   Slave disable while busy flag
 *                      @arg SCI2C_FLAG_SRDL:   Slave receive data lost flag
 *
 * @retval      The new state of flag (SET or RESET)
 */
uint8_t SCI2C_ReadStatusFlag(SCI2C_T* i2c, SCI2C_FLAG_T flag)
{
    uint8_t ret = RESET;

    if (flag & BIT8)
    {
        ret = i2c->STS2 & flag ? SET : RESET;
    }
    else
    {
        ret = i2c->STS1 & flag ? SET : RESET;
    }

    return ret;
}

/*!
 * @brief       Read specified interrupt flag
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       flag:   Specifies the interrupt flag to be checked
 *                      The parameter can be one of following values:
 *                      @arg SCI2C_INT_RFU:    Rx FIFO underflow interrupt flag
 *                      @arg SCI2C_INT_RFO:    Rx FIFO onverflow interrupt flag
 *                      @arg SCI2C_INT_RFF:    Rx FIFO full interrupt flag
 *                      @arg SCI2C_INT_TFO:    Tx FIFO onverflow interrupt flag
 *                      @arg SCI2C_INT_TFE:    Tx FIFO empty interrupt flag
 *                      @arg SCI2C_INT_RR:     Read request interrupt flag
 *                      @arg SCI2C_INT_TA:     Tx abort interrupt flag
 *                      @arg SCI2C_INT_RD:     Read done interrupt flag
 *                      @arg SCI2C_INT_ACT:    Activity interrupt flag
 *                      @arg SCI2C_INT_STPD:   Stop detect interrupt flag
 *                      @arg SCI2C_INT_STAD:   Start detect interrupt flag
 *                      @arg SCI2C_INT_GC:     Gernal call interrupt flag
 *                      @arg SCI2C_INT_RSTAD:  Restart detect interrupt flag
 *                      @arg SCI2C_INT_MOH:    Master on hold interrupt flag
 *
 * @retval      The new state of flag (SET or RESET)
 */
uint8_t SCI2C_ReadIntFlag(SCI2C_T* i2c, SCI2C_INT_T flag)
{
    uint8_t ret = RESET;

    ret = i2c->INTSTS & flag ? SET : RESET;

    return ret;
}

/*!
 * @brief       Clear specified interrupt flag
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       flag:   Specifies the interrupt flag to be checked
 *                      The parameter can be one of following values:
 *                      @arg SCI2C_INT_RFU:    Rx FIFO underflow interrupt flag
 *                      @arg SCI2C_INT_RFO:    Rx FIFO onverflow interrupt flag
 *                      @arg SCI2C_INT_TFO:    Tx FIFO onverflow interrupt flag
 *                      @arg SCI2C_INT_RR:     Read request interrupt flag
 *                      @arg SCI2C_INT_TA:     Tx abort interrupt flag
 *                      @arg SCI2C_INT_RD:     Read done interrupt flag
 *                      @arg SCI2C_INT_ACT:    Activity interrupt flag
 *                      @arg SCI2C_INT_STPD:   Stop detect interrupt flag
 *                      @arg SCI2C_INT_STAD:   Start detect interrupt flag
 *                      @arg SCI2C_INT_GC:     Gernal call interrupt flag
 *                      @arg SCI2C_INT_ALL:    All interrupt flag
 * @retval      The new state of flag (SET or RESET)
 */
void SCI2C_ClearIntFlag(SCI2C_T* i2c, SCI2C_INT_T flag)
{
    volatile uint32_t dummy = 0;

    if (flag == SCI2C_INT_ALL)
    {
        dummy = i2c->INTCLR;
    }
    else if (flag == SCI2C_INT_RFU)
    {
        dummy = i2c->RFUIC;
    }
    else if (flag == SCI2C_INT_RFO)
    {
        dummy = i2c->RFOIC;
    }
    else if (flag == SCI2C_INT_TFO)
    {
        dummy = i2c->TFOIC;
    }
    else if (flag == SCI2C_INT_RR)
    {
        dummy = i2c->RRIC;
    }
    else if (flag == SCI2C_INT_TA)
    {
        dummy = i2c->TAIC;
    }
    else if (flag == SCI2C_INT_RD)
    {
        dummy = i2c->RDIC;
    }
    else if (flag == SCI2C_INT_ACT)
    {
        dummy = i2c->AIC;
    }
    else if (flag == SCI2C_INT_STPD)
    {
        dummy = i2c->STPDIC;
    }
    else if (flag == SCI2C_INT_STAD)
    {
        dummy = i2c->STADIC;
    }
    else if (flag == SCI2C_INT_GC)
    {
        dummy = i2c->GCIC;
    }
}

/*!
 * @brief       Read specified interrupt flag(Raw register)
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       flag:   Specifies the interrupt flag to be checked
 *                      The parameter can be one of following values:
 *                      @arg SCI2C_INT_RFU:    Rx FIFO underflow interrupt flag
 *                      @arg SCI2C_INT_RFO:    Rx FIFO onverflow interrupt flag
 *                      @arg SCI2C_INT_RFF:    Rx FIFO full interrupt flag
 *                      @arg SCI2C_INT_TFO:    Tx FIFO onverflow interrupt flag
 *                      @arg SCI2C_INT_TFE:    Tx FIFO empty interrupt flag
 *                      @arg SCI2C_INT_RR:     Read request interrupt flag
 *                      @arg SCI2C_INT_TA:     Tx abort interrupt flag
 *                      @arg SCI2C_INT_RD:     Read done interrupt flag
 *                      @arg SCI2C_INT_ACT:    Activity interrupt flag
 *                      @arg SCI2C_INT_STPD:   Stop detect interrupt flag
 *                      @arg SCI2C_INT_STAD:   Start detect interrupt flag
 *                      @arg SCI2C_INT_GC:     Gernal call interrupt flag
 *                      @arg SCI2C_INT_RSTAD:  Restart detect interrupt flag
 *                      @arg SCI2C_INT_MOH:    Master on hold interrupt flag
 *
 * @retval      The new state of flag (SET or RESET)
 */
uint8_t SCI2C_ReadRawIntFlag(SCI2C_T* i2c, SCI2C_INT_T flag)
{
    uint8_t ret = RESET;

    ret = i2c->RIS & flag ? SET : RESET;

    return ret;
}

/*!
 * @brief       Enable the specified interrupts
 *
 * @param       i2c:        Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       interrupt:  Specifies the interrupt sources
 *                          The parameter can be any combination of following values:
 *                          @arg SCI2C_INT_RFU:     Rx FIFO underflow interrupt
 *                          @arg SCI2C_INT_RFO:     Rx FIFO onverflow interrupt
 *                          @arg SCI2C_INT_RFF:     Rx FIFO full interrupt
 *                          @arg SCI2C_INT_TFO:     Tx FIFO onverflow interrupt
 *                          @arg SCI2C_INT_TFE:     Tx FIFO empty interrupt
 *                          @arg SCI2C_INT_RR:      Read request interrupt
 *                          @arg SCI2C_INT_TA:      Tx abort interrupt
 *                          @arg SCI2C_INT_RD:      Read done interrupt
 *                          @arg SCI2C_INT_ACT:     Activity interrupt
 *                          @arg SCI2C_INT_STPD:    Stop detect interrupt
 *                          @arg SCI2C_INT_STAD:    Start detect interrupt
 *                          @arg SCI2C_INT_GC:      Gernal call interrupt
 *                          @arg SCI2C_INT_RSTAD:   Restart detect interrupt
 *                          @arg SCI2C_INT_MOH:     Master on hold interrupt
 *
 * @retval      None
 */
void SCI2C_EnableInterrupt(SCI2C_T* i2c, uint16_t interrupt)
{
    i2c->INTEN |= interrupt;
}

/*!
 * @brief       Disable the specified interrupts
 *
 * @param       i2c:        Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       interrupt:  Specifies the interrupt sources
 *                          The parameter can be any combination of following values:
 *                          @arg SCI2C_INT_RFU:     Rx FIFO underflow interrupt
 *                          @arg SCI2C_INT_RFO:     Rx FIFO onverflow interrupt
 *                          @arg SCI2C_INT_RFF:     Rx FIFO full interrupt
 *                          @arg SCI2C_INT_TFO:     Tx FIFO onverflow interrupt
 *                          @arg SCI2C_INT_TFE:     Tx FIFO empty interrupt
 *                          @arg SCI2C_INT_RR:      Read request interrupt
 *                          @arg SCI2C_INT_TA:      Tx abort interrupt
 *                          @arg SCI2C_INT_RD:      Read done interrupt
 *                          @arg SCI2C_INT_ACT:     Activity interrupt
 *                          @arg SCI2C_INT_STPD:    Stop detect interrupt
 *                          @arg SCI2C_INT_STAD:    Start detect interrupt
 *                          @arg SCI2C_INT_GC:      Gernal call interrupt
 *                          @arg SCI2C_INT_RSTAD:   Restart detect interrupt
 *                          @arg SCI2C_INT_MOH:     Master on hold interrupt
 *
 * @retval      None
 */
void SCI2C_DisableInterrupt(SCI2C_T* i2c, uint16_t interrupt)
{
    i2c->INTEN &= ~interrupt;
}

/*!
 * @brief       Enable stop detected only master in activity.
 *
 * @param       i2c:   Select the the I2C peripheral. It can be I2C3 or I2C4
 */
void SCI2C_EnableStopDetectMasterActivity(SCI2C_T* i2c)
{
    i2c->CTRL1_B.DSMA = BIT_SET;
}

/*!
 * @brief       Disable stop detected only master in activity.
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 */
void SCI2C_DisableStopDetectMasterActivity(SCI2C_T* i2c)
{
    i2c->CTRL1_B.DSMA = BIT_RESET;
}

/*!
 * @brief       Enable stop detected only address is matched in slave mode.
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 */
void SCI2C_EnableStopDetectAddressed(SCI2C_T* i2c)
{
    i2c->CTRL1_B.DSA = BIT_SET;
}

/*!
 * @brief       Disable stop detected only address is matched in slave mode.
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 */
void SCI2C_DisableStopDetectAddressed(SCI2C_T* i2c)
{
    i2c->CTRL1_B.DSA = BIT_RESET;
}

/*!
 * @brief       Enable restart
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      None
 */
void SCI2C_EnableRestart(SCI2C_T* i2c)
{
    i2c->CTRL1_B.RSTAEN = BIT_SET;
}

/*!
 * @brief       Disable restart
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      None
 */
void SCI2C_DisableRestart(SCI2C_T* i2c)
{
    i2c->CTRL1_B.RSTAEN = BIT_RESET;
}

/*!
 * @brief       Configures speed.
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       speed:  Specifies the speed.
 *                      @arg SCI2C_SPEED_STANDARD:  Standard speed.
 *                      @arg SCI2C_SPEED_FAST:      Fast speed.
 *                      @arg SCI2C_SPEED_HIGH:      High speed.
 *
 * @retval      None
 */
void SCI2C_ConfigSpeed(SCI2C_T* i2c, SCI2C_SPEED_T speed)
{
    i2c->CTRL1_B.SPD = speed;
}

/*!
 * @brief       Configures master address.
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       mode:   Specifies the address mode.
 *                      @arg SCI2C_ADDR_MODE_7BIT:      7-bit address mode.
 *                      @arg SCI2C_ADDR_MODE_10BIT:     10-bit address mode.
 *
 * @param       addr:   Specifies the address.
 *
 * @retval      None
 */
void SCI2C_ConfigMasterAddr(SCI2C_T* i2c, SCI2C_ADDR_MODE_T mode, uint16_t addr)
{
    i2c->TARADDR_B.MAM = mode;
    i2c->TARADDR_B.ADDR = addr;
}


/*!
 * @brief       Configures slave address.
 *
 * @param       i2c:    Select the the I2C peripheral.It can be I2C3 or I2C4
 *
 * @param       mode:   Specifies the address mode.
 *                      @arg SCI2C_ADDR_MODE_7BIT:      7-bit address mode.
 *                      @arg SCI2C_ADDR_MODE_10BIT:     10-bit address mode.
 *
 * @param       addr:   Specifies the address.
 *
 * @retval      None
 */
void SCI2C_ConfigSlaveAddr(SCI2C_T* i2c, SCI2C_ADDR_MODE_T mode, uint16_t addr)
{
    i2c->CTRL1_B.SAM = mode;
    i2c->SLAADDR = addr;
}

/*!
 * @brief       Enable master mode
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      None
 */
void SCI2C_EnableMasterMode(SCI2C_T* i2c)
{
    i2c->CTRL1_B.MST = BIT_SET;
}

/*!
 * @brief       Disable master mode
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      None
 */
void SCI2C_DisableMasterMode(SCI2C_T* i2c)
{
    i2c->CTRL1_B.MST = BIT_RESET;
}

/*!
 * @brief       Enable slave mode
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      None
 */
void SCI2C_EnableSlaveMode(SCI2C_T* i2c)
{
    i2c->CTRL1_B.SLADIS = BIT_RESET;
}

/*!
 * @brief       Disable slave mode
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      None
 */
void SCI2C_DisableSlaveMode(SCI2C_T* i2c)
{
    i2c->CTRL1_B.SLADIS = BIT_SET;
}

/*!
 * @brief       Config master code
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       code:   Master code
 *
 * @retval      None
 */
void SCI2C_ConfigMasterCode(SCI2C_T* i2c, uint8_t code)
{
    i2c->HSMC = code;
}

/*!
 * @brief       Config data direction
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       dir:    Data direction
 *                      @arg SCI2C_DATA_DIR_WRITE:  Write data
 *                      @arg SCI2C_DATA_DIR_READ:   Read data
 *
 * @retval      None
 */
void SCI2C_ConfigDataDir(SCI2C_T* i2c, SCI2C_DATA_DIR_T dir)
{
    i2c->DATA = (uint32_t)(dir << 8);
}

/*!
 * @brief       Transmit data
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       data:   Data to be transmited
 *
 * @retval      None
 */
void SCI2C_TxData(SCI2C_T* i2c, uint8_t data)
{
    i2c->DATA_B.DATA = data;
}

/*!
 * @brief       Returns the most recent received data
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      Received data
 *
 */
uint8_t SCI2C_RxData(SCI2C_T* i2c)
{
    return (uint8_t)(i2c->DATA & 0XFF);
}

/*!
 * @brief       Configures data register
 *
 * @param       i2c:        Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       stop:       Enable or disable generate stop condition
 *
 * @param       dataDir:    Data direction. Read or write
 *                          @arg SCI2C_DATA_DIR_WRITE:  Write data
 *                          @arg SCI2C_DATA_DIR_READ:   Read data
 *
 * @param       data:       Data to be transmited
 *
 * @retval      None
 */
void SCI2C_ConfigDataRegister(SCI2C_T* i2c, SCI2C_STOP_T stop, SCI2C_DATA_DIR_T dataDir, uint8_t data)
{
    i2c->DATA = (uint32_t)((stop << 9) | (dataDir << 8) | data);
}

/*!
 * @brief       Read Rx FIFO data number
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      None
 */
uint8_t SCI2C_ReadRxFifoDataCnt(SCI2C_T* i2c)
{
    return (uint8_t)i2c->RFL;
}

/*!
 * @brief       Read Tx FIFO data number
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      None
 */
uint8_t SCI2C_ReadTxFifoDataCnt(SCI2C_T* i2c)
{
    return (uint8_t)i2c->TFL;
}

/*!
 * @brief       Configures Rx FIFO threshold
 *
 * @param       i2c:        Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       threshold:  FIFO threshold
 *
 * @retval      None
 */
void SCI2C_ConfigRxFifoThreshold(SCI2C_T* i2c, uint8_t threshold)
{
    i2c->RFT = threshold;
}

/*!
 * @brief       Configures Tx FIFO threshold
 *
 * @param       i2c:        Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       threshold:  FIFO threshold
 *
 * @retval      None
 */
void SCI2C_ConfigTxFifoThreshold(SCI2C_T* i2c, uint8_t threshold)
{
    i2c->TFT = threshold;
}

/*!
 * @brief       Enable I2C peripheral
 *
 * @param       i2c:        Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      None

 */
void SCI2C_Enable(SCI2C_T* i2c)
{
    i2c->CTRL2_B.I2CEN = BIT_SET;
}

/*!
 * @brief       Disable I2C peripheral
 *
 * @param       i2c:        Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      None
 */
void SCI2C_Disable(SCI2C_T* i2c)
{
    i2c->CTRL2_B.I2CEN = BIT_RESET;
}

/*!
 * @brief       Abort I2C transmit
 *
 * @param       i2c:        Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      None
 */
void SCI2C_Abort(SCI2C_T* i2c)
{
    i2c->CTRL2_B.ABR = BIT_SET;
}

/*!
 * @brief       Tx command block
 *
 * @param       i2c:        Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       enable:     ENABLE or DISABLE
 *
 * @retval      None
 */
void SCI2C_BlockTxCmd(SCI2C_T* i2c, uint8_t enable)
{
    i2c->CTRL2_B.TCB = enable;
}

/*!
 * @brief       Configures SCL high and low period
 *
 * @param       i2c:        Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       speed:      Specifies the speed.
 *                          @arg SCI2C_SPEED_STANDARD:  Standard speed.
 *                          @arg SCI2C_SPEED_FAST:      Fast speed.
 *                          @arg SCI2C_SPEED_HIGH:      High speed.
 *
 * @param       highPeriod: SCL high period
 *
 * @param       lowPeriod:  SCL low period
 *
 * @retval      None
 */
void SCI2C_ConfigClkPeriod(SCI2C_T* i2c, SCI2C_SPEED_T speed, uint16_t highPeriod, uint16_t lowPeriod)
{
    if (speed == SCI2C_SPEED_STANDARD)
    {
        i2c->SSCLC = lowPeriod;
        i2c->SSCHC = highPeriod;
    }
    else if (speed == SCI2C_SPEED_FAST)
    {
        i2c->FSCLC = lowPeriod;
        i2c->FSCHC = highPeriod;
    }
    else if (speed == SCI2C_SPEED_HIGH)
    {
        i2c->HSCLC = lowPeriod;
        i2c->HSCHC = highPeriod;
    }
}

/*!
 * @brief       Configures SDA hold time length
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       txHold: Tx SDA hold time length
 *
 * @param       rxHold: Rx SDA hold time length
 *
 * @retval      None
 */
void SCI2C_ConfigSDAHoldTime(SCI2C_T* i2c, uint16_t txHold, uint8_t rxHold)
{
    i2c->SDAHOLD_B.TXHOLD = txHold;
    i2c->SDAHOLD_B.RXHOLD = rxHold;
}

/*!
 * @brief       Configures SDA delay time
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       delay:  SDA delay time
 *
 * @retval      None
 */
void SCI2C_ConfigSDADelayTime(SCI2C_T* i2c, uint8_t delay)
{
    i2c->SDADLY = delay;
}

/*!
 * @brief       Enable or disable generate gernal call ack
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       enable: SDA delay time
 *
 * @retval      None
 */
void SCI2C_GernalCallAck(SCI2C_T* i2c, uint8_t enable)
{
    i2c->GCA = enable;
}

/*!
 * @brief       When received data no ack generated in slave mode.
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       enable: ENABLE or DISABLE
 *
 * @retval      None
 */
void SCI2C_SlaveDataNackOnly(SCI2C_T* i2c, uint8_t enable)
{
    i2c->SDNO = enable;
}

/*!
 * @brief       Read Tx abort source
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @retval      Return Tx abort source
 */
uint32_t SCI2C_ReadTxAbortSource(SCI2C_T* i2c)
{
    return (uint32_t)i2c->TAS;
}

/*!
 * @brief       Enable DMA
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       dma:    DMA requst source
 *                      @arg SCI2C_DMA_RX:  DMA RX channel
 *                      @arg SCI2C_DMA_TX:  DMA TX channel
 *
 * @retval      None
 */
void SCI2C_EnableDMA(SCI2C_T* i2c, SCI2C_DMA_T dma)
{
    i2c->DMACTRL |= dma;
}

/*!
 * @brief       Disable DMA
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       dma:    DMA requst source
 *                      @arg SCI2C_DMA_RX:  DMA RX channel
 *                      @arg SCI2C_DMA_TX:  DMA TX channel
 *
 * @retval      None
 */
void SCI2C_DisableDMA(SCI2C_T* i2c, SCI2C_DMA_T dma)
{
    i2c->DMACTRL &= (uint32_t)~dma;
}

/*!
 * @brief       Configures DMA Tx data level
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       cnt:    DMA Tx data level
 *
 * @retval      None
 */
void SCI2C_ConfigDMATxDataLevel(SCI2C_T* i2c, uint8_t cnt)
{
    i2c->DTDL = cnt;
}

/*!
 * @brief       Configures DMA Rx data level
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       cnt:    DMA Rx data level
 *
 * @retval      None
 */
void SCI2C_ConfigDMARxDataLevel(SCI2C_T* i2c, uint8_t cnt)
{
    i2c->DRDL = cnt;
}

/*!
 * @brief       Configures spike suppressio limit
 *
 * @param       i2c:    Select the the I2C peripheral. It can be I2C3 or I2C4
 *
 * @param       speed:  I2C speed mode
 *                      @arg SCI2C_SPEED_STANDARD:  Standard speed.
 *                      @arg SCI2C_SPEED_FAST:      Fast speed.
 *                      @arg SCI2C_SPEED_HIGH:      High speed.
 *
 * @param       limit:  Spike suppressio limit value
 *
 * @retval      None
 */
void SCI2C_ConfigSpikeSuppressionLimit(SCI2C_T* i2c, SCI2C_SPEED_T speed, uint8_t limit)
{
    if (speed == SCI2C_SPEED_HIGH)
    {
        i2c->HSSSL = limit;
    }
    else
    {
        i2c->LSSSL = limit;
    }
}

/**@} end of group SCI2C_Functions */
/**@} end of group SCI2C_Driver */
/**@} end of group APM32F10x_StdPeriphDriver */
