/*!
 * @file        qpm32f10x_qspi.c
 *
 * @brief       This file contains all the functions for the QSPI peripheral
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
#if defined (APM32F10X_MD) || defined (APM32F10X_LD)
#include "apm32f10x_qspi.h"

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup QSPI_Driver QSPI Driver
  @{
*/

/** @defgroup QSPI_Functions Functions
  @{
*/

/*!
 * @brief       Reset QSPI peripheral registers to their default values
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_Reset(void)
{
    volatile uint32_t dummy = 0;

    QSPI->IOSW = QSPI_IOSW_RESET_VALUE;
    QSPI->SSIEN = QSPI_SSIEN_RESET_VALUE;
    QSPI->INTEN = QSPI_INTEN_RESET_VALUE;
    dummy = QSPI->ICF;
    QSPI->CTRL1 = QSPI_CTRL1_RESET_VALUE;
    QSPI->CTRL2 = QSPI_CTRL2_RESET_VALUE;
    QSPI->CTRL3 = QSPI_CTRL3_RESET_VALUE;
    QSPI->SLAEN = QSPI_SLAEN_RESET_VALUE;
    QSPI->BR = QSPI_BR_RESET_VALUE;
    QSPI->TFL = QSPI_TFL_RESET_VALUE;
    QSPI->RFL = QSPI_RFL_RESET_VALUE;
    QSPI->TFTL = QSPI_TFTL_RESET_VALUE;
    QSPI->RFTL = QSPI_RFTL_RESET_VALUE;
    QSPI->STS = QSPI_STS_RESET_VALUE;
    QSPI->RSD = QSPI_RSD_RESET_VALUE;
}

/*!
 * @brief       Config the QSPI peripheral according to the specified parameters in the qspiConfig
 *
 * @param       qspiConfig: Pointer to a QSPI_Config_T structure that contains the configuration information
 *
 * @retval      None
 */
void QSPI_Config(QSPI_Config_T* qspiConfig)
{
    QSPI->CTRL1_B.CPHA = qspiConfig->clockPhase;
    QSPI->CTRL1_B.CPOL = qspiConfig->clockPolarity;
    QSPI->CTRL1_B.FRF = qspiConfig->frameFormat;
    QSPI->CTRL1_B.DFS = qspiConfig->dataFrameSize;;
    QSPI->CTRL1_B.SSTEN = qspiConfig->selectSlaveToggle;

    QSPI->BR = qspiConfig->clockDiv;
}

/*!
 * @brief       Fills each qspiConfig member with its default value
 *
 * @param       qspiConfig: Pointer to a QSPI_Config_T structure which will be initialized
 *
 * @retval      None
 */
void QSPI_ConfigStructInit(QSPI_Config_T* qspiConfig)
{
    qspiConfig->clockPhase = QSPI_CLKPHA_2EDGE;
    qspiConfig->clockPolarity = QSPI_CLKPOL_LOW;
    qspiConfig->clockDiv = 0;

    qspiConfig->frameFormat = QSPI_FRF_STANDARD;
    qspiConfig->dataFrameSize = QSPI_DFS_8BIT;
    qspiConfig->selectSlaveToggle = QSPI_SST_DISABLE;
}

/*!
 * @brief       Configs frame number
 *
 * @param       num: Configs a 16bit frame number
 *
 * @retval      None
 */
void QSPI_ConfigFrameNum(uint16_t num)
{
    QSPI->CTRL2_B.NDF = num;
}

/*!
 * @brief       Configs data frame size
 *
 * @param       dfs: Specifies the data frame size
 *                   The parameter can be one of following values:
 *                   @arg QSPI_DFS_4BIT  : Specifies data frame size to 4bit
 *                   @arg QSPI_DFS_5BIT  : Specifies data frame size to 5bit
 *                   @arg QSPI_DFS_6BIT  : Specifies data frame size to 6bit
 *                   @arg QSPI_DFS_7BIT  : Specifies data frame size to 7bit
 *                   @arg QSPI_DFS_8BIT  : Specifies data frame size to 8bit
 *                   @arg QSPI_DFS_9BIT  : Specifies data frame size to 9bit
 *                   @arg QSPI_DFS_10BIT : Specifies data frame size to 10bit
 *                   @arg QSPI_DFS_11BIT : Specifies data frame size to 11bit
 *                   @arg QSPI_DFS_12BIT : Specifies data frame size to 12bit
 *                   @arg QSPI_DFS_13BIT : Specifies data frame size to 13bit
 *                   @arg QSPI_DFS_14BIT : Specifies data frame size to 14bit
 *                   @arg QSPI_DFS_15BIT : Specifies data frame size to 15bit
 *                   @arg QSPI_DFS_16BIT : Specifies data frame size to 16bit
 *                   @arg QSPI_DFS_17BIT : Specifies data frame size to 17bit
 *                   @arg QSPI_DFS_18BIT : Specifies data frame size to 18bit
 *                   @arg QSPI_DFS_19BIT : Specifies data frame size to 19bit
 *                   @arg QSPI_DFS_20BIT : Specifies data frame size to 20bit
 *                   @arg QSPI_DFS_21BIT : Specifies data frame size to 21bit
 *                   @arg QSPI_DFS_22BIT : Specifies data frame size to 22bit
 *                   @arg QSPI_DFS_23BIT : Specifies data frame size to 23bit
 *                   @arg QSPI_DFS_24BIT : Specifies data frame size to 24bit
 *                   @arg QSPI_DFS_25BIT : Specifies data frame size to 25bit
 *                   @arg QSPI_DFS_26BIT : Specifies data frame size to 26bit
 *                   @arg QSPI_DFS_27BIT : Specifies data frame size to 27bit
 *                   @arg QSPI_DFS_28BIT : Specifies data frame size to 28bit
 *                   @arg QSPI_DFS_29BIT : Specifies data frame size to 29bit
 *                   @arg QSPI_DFS_30BIT : Specifies data frame size to 30bit
 *                   @arg QSPI_DFS_31BIT : Specifies data frame size to 31bit
 *                   @arg QSPI_DFS_32BIT : Specifies data frame size to 32bit
 *
 * @retval      None
 */
void QSPI_ConfigDataFrameSize(QSPI_DFS_T dfs)
{
    QSPI->CTRL1_B.DFS = dfs;
}

/*!
 * @brief       Configs frame format
 *
 * @param       frameFormat
 *
 * @retval      None
 */
void QSPI_ConfigFrameFormat(QSPI_FRF_T frameFormat)
{
    QSPI->CTRL1_B.FRF = frameFormat;
}

/*!
 * @brief       Enable QSPI
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_Enable(void)
{
    QSPI->SSIEN_B.EN = BIT_SET;
}

/*!
 * @brief       Disable QSPI
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_Disable(void)
{
    QSPI->SSIEN_B.EN = BIT_RESET;
}

/*!
 * @brief       Read Tx FIFO number of data
 *
 * @param       None
 *
 * @retval      None
 */
uint8_t QSPI_ReadTxFifoDataNum(void)
{
    return (uint8_t)QSPI->TFL_B.TFL;
}

/*!
 * @brief       Read Rx FIFO number of data
 *
 * @param       None
 *
 * @retval      Returns Rx FIFO number of data
 */
uint8_t QSPI_ReadRxFifoDataNum(void)
{
    return (uint8_t)QSPI->RFL_B.RFL;
}

/*!
 * @brief       Configs rx FIFO threshold
 *
 * @param       threshold: Speicifes rx FIFO threshold with a 3bit value
 *
 * @retval      None
 */
void QSPI_ConfigRxFifoThreshold(uint8_t threshold)
{
    QSPI->RFTL_B.RFT = threshold;
}

/*!
 * @brief       Congfigs Tx FIFO threshold
 *
 * @param       threshold: Speicifes Tx FIFO threshold with a 3bit value
 *
 * @retval      None
 */
void QSPI_ConfigTxFifoThreshold(uint8_t threshold)
{
    QSPI->TFTL_B.TFTH = threshold;
}

/*!
 * @brief       Congfigs Tx FIFO empty threshold
 *
 * @param       threshold: Speicifes Tx FIFO empty threshold with a 3bit value
 *
 * @retval      None
 */
void QSPI_ConfigTxFifoEmptyThreshold(uint8_t threshold)
{
    QSPI->TFTL_B.TFT = threshold;
}

/*!
 * @brief       Configs RX sample edge
 *
 * @param       rse: Specifies the sample edge
 *                   The parameter can be one of following values:
 *                   @arg QSPI_RSE_RISING : rising edge sample
 *                   @arg QSPI_RSE_FALLING: falling edge sample
 *
 * @retval      None
 */
void QSPI_ConfigRxSampleEdge(QSPI_RSE_T rse)
{
    QSPI->RSD_B.RSE = rse;
}

/*!
 * @brief       Set RX sample delay
 *
 * @param       delay: Specifies the sample delay with a 8-bit value
 *
 * @retval      None
 */
void QSPI_ConfigRxSampleDelay(uint8_t delay)
{
    QSPI->RSD_B.RSD = delay;
}

/*!
 * @brief       Clock stretch enable
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_EnableClockStretch(void)
{
    QSPI->CTRL3_B.CSEN = BIT_SET;
}

/*!
 * @brief       Clock stretch disable
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_DisableClockStretch(void)
{
    QSPI->CTRL3_B.CSEN = BIT_RESET;
}

/*!
 * @brief       Configs instruction length
 *
 * @param       len: Specifies the length of instruction
 *                   The parameter can be one of following values:
 *                   @arg QSPI_INST_LEN_0     : no instruction
 *                   @arg QSPI_INST_LEN_4BIT  : 4-bit instruction
 *                   @arg QSPI_INST_LEN_8BIT  : 8-bit instruction
 *                   @arg QSPI_INST_LEN_16BIT : 16-bit instruction
 *
 * @retval      None
 */
void QSPI_ConfigInstLen(QSPI_INST_LEN_T len)
{
    QSPI->CTRL3_B.INSLEN = len;
}

/*!
 * @brief       Configs address length
 *
 * @param       len: Specifies the address length
 *                   The parameter can be one of following values:
 *                   @arg QSPI_ADDR_LEN_0     : no address
 *                   @arg QSPI_ADDR_LEN_4BIT  : 4-bit address length
 *                   @arg QSPI_ADDR_LEN_8BIT, : 8-bit address length
 *                   @arg QSPI_ADDR_LEN_12BIT : 12-bit address length
 *                   @arg QSPI_ADDR_LEN_16BIT : 16-bit address length
 *                   @arg QSPI_ADDR_LEN_20BIT : 20-bit address length
 *                   @arg QSPI_ADDR_LEN_24BIT : 24-bit address length
 *                   @arg QSPI_ADDR_LEN_28BIT : 28-bit address length
 *                   @arg QSPI_ADDR_LEN_32BIT : 32-bit address length
 *                   @arg QSPI_ADDR_LEN_36BIT : 36-bit address length
 *                   @arg QSPI_ADDR_LEN_40BIT : 40-bit address length
 *                   @arg QSPI_ADDR_LEN_44BIT : 44-bit address length
 *                   @arg QSPI_ADDR_LEN_48BIT : 48-bit address length
 *                   @arg QSPI_ADDR_LEN_52BIT : 52-bit address length
 *                   @arg QSPI_ADDR_LEN_56BIT : 56-bit address length
 *                   @arg QSPI_ADDR_LEN_60BIT : 60-bit address length
 *
 * @retval      None
 */
void QSPI_ConfigAddrLen(QSPI_ADDR_LEN_T len)
{
    QSPI->CTRL3_B.ADDRLEN = len;
}

/*!
 * @brief       Configs instruction and address type
 *
 * @param       type: Specifies the instruction and address type
 *                    The parameter can be one of following values:
 *                    @arg QSPI_INST_ADDR_TYPE_STANDARD : Tx instruction in standard SPI mode,
 *                                                         Tx address in standard SPI mode
 *                    @arg QSPI_INST_TYPE_STANDARD      : Tx instruction in standard SPI mode,
 *                                                         Tx address in mode of SPI_FRF
 *                    @arg QSPI_INST_ADDR_TYPE_FRF      : Tx instruction in mode of SPI_FRF,
 *                                                         Tx address in mode of SPI_FRF
 *
 * @retval      None
 */
void QSPI_ConfigInstAddrType(QSPI_INST_ADDR_TYPE_T type)
{
    QSPI->CTRL3_B.IAT = type;
}

/*!
 * @brief       Configs wait cycle number
 *
 * @param       cycle: Specifies the wait cycle number with a 5-bit value
 *
 * @retval      None
 */
void QSPI_ConfigWaitCycle(uint8_t cycle)
{
    QSPI->CTRL3_B.WAITCYC = cycle;
}

/*!
 * @brief       Open QSPI GPIO
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_OpenIO(void)
{
    QSPI->IOSW_B.IOSW = BIT_SET;
}

/*!
 * @brief       Close QSPI GPIO
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_CloseIO(void)
{
    QSPI->IOSW_B.IOSW = BIT_RESET;
}

/*!
 * @brief       Set transmission mode
 *
 * @param       mode: Specifies the transmission mode
 *                    The parameter can be one of following values:
 *                    @arg QSPI_TRANS_MODE_TX_RX       : TX and RX mode
 *                    @arg QSPI_TRANS_MODE_TX          : TX mode only
 *                    @arg QSPI_TRANS_MODE_RX          : RX mode only
 *                    @arg QSPI_TRANS_MODE_EEPROM_READ : EEPROM read mode
 *
 * @retval      None
 */
void QSPI_ConfigTansMode(QSPI_TRANS_MODE_T mode)
{
    QSPI->CTRL1_B.TXMODE = mode;
}

/*!
 * @brief       Transmit data
 *
 * @param       data: Data to be transmited
 *
 * @retval      None
 */
void QSPI_TxData(uint32_t data)
{
    QSPI->DATA = data;
}

/*!
 * @brief       Returns the most recent received data
 *
 * @param       None
 *
 * @retval      The received data
 */
uint32_t QSPI_RxData(void)
{
    return (uint32_t)QSPI->DATA;
}

/*!
 * @brief       Enable Slave
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_EnableSlave(void)
{
    QSPI->SLAEN_B.SLAEN = BIT_SET;
}

/*!
 * @brief       Disable slave
 *
 * @param       None
 *
 * @retval      None
 */
void QSPI_DisableSlave(void)
{
    QSPI->SLAEN_B.SLAEN = BIT_RESET;
}

/*!
 * @brief       Enable the specified QSPI interrupts
 *
 * @param       interrupt:  Specifies the QSPI interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg QSPI_INT_TFE:      TX FIFO empty interrupt
 *                          @arg QSPI_INT_TFO:      TX FIFO overflow interrupt
 *                          @arg QSPI_INT_RFU:      RX FIFO underflow interrupt
 *                          @arg QSPI_INT_RFO:      RX FIFO overflow interrupt
 *                          @arg QSPI_INT_RFF:      RX FIFO full interrupt
 *                          @arg QSPI_INT_MST:      Master interrupt
 *
 * @retval      None
 */
void QSPI_EnableInterrupt(uint32_t interrupt)
{
    QSPI->INTEN |= interrupt;
}

/*!
 * @brief       Disable the specified QSPI interrupts
 *
 * @param       interrupt:  Specifies the QSPI interrupt sources
 *                          The parameter can be combination of following values:
 *                          @arg QSPI_INT_TFE:      TX FIFO empty interrupt
 *                          @arg QSPI_INT_TFO:      TX FIFO overflow interrupt
 *                          @arg QSPI_INT_RFU:      RX FIFO underflow interrupt
 *                          @arg QSPI_INT_RFO:      RX FIFO overflow interrupt
 *                          @arg QSPI_INT_RFF:      RX FIFO full interrupt
 *                          @arg QSPI_INT_MST:      Master interrupt
 *
 * @retval      None
 */
void QSPI_DisableInterrupt(uint32_t interrupt)
{
    QSPI->INTEN &= (uint32_t)~interrupt;
}

/*!
 * @brief       Read specified QSPI flag
 *
 * @param       flag:   Specifies the flag to be checked
 *                      The parameter can be one of following values:
 *                      @arg QSPI_FLAG_BUSY:    Busy flag
 *                      @arg QSPI_FLAG_TFNF:    TX FIFO not full flag
 *                      @arg QSPI_FLAG_TFE:     TX FIFO empty flag
 *                      @arg QSPI_FLAG_RFNE:    RX FIFO not empty flag
 *                      @arg QSPI_FLAG_RFF:     RX FIFO full flag
 *                      @arg QSPI_FLAG_DCE:     Data collision error
 *
 * @retval      The new state of flag (SET or RESET)
 */
uint8_t QSPI_ReadStatusFlag(QSPI_FLAG_T flag)
{
    uint8_t ret = RESET;

    ret = QSPI->STS & flag ? SET : RESET;

    return ret;
}

/*!
 * @brief       Clear specified QSPI flag
 *
 * @param       None
 *
 * @retval      None
 *
 * @note        This funtion only clear Data collision error flag(QSPI_FLAG_DCE)
 */
void QSPI_ClearStatusFlag(void)
{
    volatile uint32_t dummy = 0;

    dummy = QSPI->STS;
}

/*!
 * @brief       Read specified QSPI interrupt flag
 *
 * @param       flag:   Specifies the interrupt flag to be checked
 *                      The parameter can be one of following values:
 *                      @arg QSPI_INT_FLAG_TFE:     TX FIFO empty interrupt flag
 *                      @arg QSPI_INT_FLAG_TFO:     TX FIFO overflow interrupt flag
 *                      @arg QSPI_INT_FLAG_RFU:     RX FIFO underflow interrupt flag
 *                      @arg QSPI_INT_FLAG_RFO:     RX FIFO overflow interrupt flag
 *                      @arg QSPI_INT_FLAG_RFF:     RX FIFO full interrupt flag
 *                      @arg QSPI_INT_FLAG_MST:     Master interrupt flag
 *
 * @retval      The new state of flag (SET or RESET)
 */
uint8_t QSPI_ReadIntFlag(QSPI_INT_FLAG_T flag)
{
    uint8_t ret = RESET;

    ret = QSPI->ISTS & flag ? SET : RESET;

    return ret;
}

/*!
 * @brief       Clear specified QSPI interrupt flag
 *
 * @param       flag:   Specifies the interrupt flag to be checked
 *                      The parameter can be one of following values:
 *                      @arg QSPI_INT_FLAG_TFO:     TX FIFO overflow interrupt flag
 *                      @arg QSPI_INT_FLAG_RFU:     RX FIFO underflow interrupt flag
 *                      @arg QSPI_INT_FLAG_RFO:     RX FIFO overflow interrupt flag
 *                      @arg QSPI_INT_FLAG_MST:     Master interrupt flag
 *
 * @retval      None
 */
void QSPI_ClearIntFlag(uint32_t flag)
{
    volatile uint32_t dummy = 0;

    if (flag & QSPI_INT_FLAG_TFO)
    {
        dummy = QSPI->TFOIC;
    }
    else if (flag & QSPI_INT_FLAG_RFO)
    {
        dummy = QSPI->RFOIC;
    }
    else if (flag & QSPI_INT_FLAG_RFU)
    {
        dummy = QSPI->RFUIC;
    }
    else if (flag & QSPI_INT_FLAG_MST)
    {
        dummy = QSPI->MIC;
    }
}

/**@} end of group QSPI_Functions*/
/**@} end of group QSPI_Driver */
/**@} end of group APM32F10x_StdPeriphDriver*/
#endif //defined APM32F10X_MD/LD
