/*!
 * @file        apm32f4Xx_sdio.c
 *
 * @brief       This file provides all the SDIO firmware functions
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

#include "apm32f4Xx_sdio.h"
#include "apm32f4Xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup SDIO_Driver
  * @brief SDIO driver modules
  @{
*/

/** @defgroup SDIO_Functions
  @{
*/

/*!
 * @brief     Reset sdio peripheral registers to their default reset values
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_Reset(void)
{
    RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_SDIO);
    RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_SDIO);
}

/*!
 * @brief     Config the SDIO peripheral according to the specified parameters in the sdioConfig
 *
 * @param     sdioConfig: pointer to a SDIO_Config_T structure
 *
 * @retval    None
 */
void SDIO_Config(SDIO_Config_T *sdioConfig)
{
    SDIO->CLKCTRL_B.CLKDIV   = sdioConfig->clockDiv;
    SDIO->CLKCTRL_B.PWRSAV   = sdioConfig->clockPowerSave;
    SDIO->CLKCTRL_B.BYPASSEN = sdioConfig->clockBypass;
    SDIO->CLKCTRL_B.WBSEL    = sdioConfig->busWide;
    SDIO->CLKCTRL_B.DEPSEL   = sdioConfig->clockEdge;
    SDIO->CLKCTRL_B.HFCEN    = sdioConfig->hardwareFlowControl;
}

/*!
 * @brief     Fills each SDIO_Config_T member with its default value
 *
 * @param     sdioConfig: pointer to a SDIO_Config_T structure
 *
 * @retval    None
 */
void SDIO_ConfigStructInit(SDIO_Config_T *sdioConfig)
{
    sdioConfig->clockDiv = 0x00;
    sdioConfig->clockEdge = SDIO_CLOCK_EDGE_RISING;
    sdioConfig->clockBypass = SDIO_CLOCK_BYPASS_DISABLE;
    sdioConfig->clockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
    sdioConfig->busWide = SDIO_BUS_WIDE_1B;
    sdioConfig->hardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
}

/*!
 * @brief     Enables the SDIO clock
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_EnableClock(void)
{
    SDIO->CLKCTRL_B.CLKEN = SET;
}

/*!
 * @brief     Disables the SDIO clock
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_DisableClock(void)
{
    SDIO->CLKCTRL_B.CLKEN = RESET;
}

/*!
 * @brief    Sets the power status of the controller
 *
 * @param    powerState: new state of the Power state
 *                       The parameter can be one of following values:
 *                       @arg SDIO_POWER_STATE_OFF : Power off
 *                       @arg SDIO_POWER_STATE_ON  : Power on
 *
 * @retval    None
 */
void SDIO_ConfigPowerState(SDIO_POWER_STATE_T powerState)
{
    SDIO->PWRCTRL_B.PWRCTRL = powerState;
}

/*!
 * @brief     Reads the SDIO power state
 *
 * @param     None
 *
 * @retval    The new state SDIO power
 *
 * @note      0x00:Power OFF, 0x02:Power UP, 0x03:Power ON
 */
uint32_t SDIO_ReadPowerState(void)
{
    return (uint8_t)SDIO->PWRCTRL_B.PWRCTRL;
}

/*!
 * @brief     Enables the SDIO DMA request
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_EnableDMA(void)
{
    SDIO->DCTRL_B.DMAEN = SET;
}

/*!
 * @brief     Disables the SDIO DMA request
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_DisableDMA(void)
{
    SDIO->DCTRL_B.DMAEN = RESET;
}

/*!
 * @brief     Configs the SDIO Command and send the command
 *
 * @param     cmdConfig: pointer to a SDIO_CmdConfig_T structure
 *
 * @retval    None
 */
void SDIO_TxCommand(SDIO_CmdConfig_T *cmdConfig)
{
    uint32_t tempReg = 0;

    SDIO->ARG = cmdConfig->argument;
    tempReg = SDIO->CMD;
    /* Clear CMDINDEX, WAITRES, WAITINT, WENDDATA, CPSMEN bits */
    tempReg &= ((uint32_t)0xFFFFF800);
    tempReg |= (uint32_t)(cmdConfig->cmdIndex) | (cmdConfig->response) << 6
               | (cmdConfig->wait) << 8 | (cmdConfig->CPSM) << 10;
    SDIO->CMD = tempReg;
}

/*!
 * @brief     Fills each cmdConfig member with its default value
 *
 * @param     cmdConfig: pointer to a SDIO_CmdConfig_T structure
 *
 * @retval    None
 */
void SDIO_TxCommandStructInit(SDIO_CmdConfig_T *cmdConfig)
{
    cmdConfig->argument = 0x00;
    cmdConfig->cmdIndex = 0x00;
    cmdConfig->response = SDIO_RESPONSE_NO;
    cmdConfig->wait = SDIO_WAIT_NO;
    cmdConfig->CPSM = SDIO_CPSM_DISABLE;
}

/*!
 * @brief     Reads the SDIO command response
 *
 * @param     None
 *
 * @retval    The command index of the last command response received
 */
uint8_t SDIO_ReadCommandResponse(void)
{
    return (uint8_t)(SDIO->CMDRES);
}

/*!
 * @brief     Reads the SDIO response
 *
 * @param     res:  Specifies the SDIO response register
 *                  The parameter can be one of following values:
 *                  @arg SDIO_RES1 : Response Register 1
 *                  @arg SDIO_RES2 : Response Register 2
 *                  @arg SDIO_RES3 : Response Register 3
 *                  @arg SDIO_RES4 : Response Register 4
 *
 * @retval    The Corresponding response register value
 */
uint32_t SDIO_ReadResponse(SDIO_RES_T res)
{
    __IO uint32_t tmp = 0;

    tmp = ((uint32_t)(SDIO_BASE + 0x14)) + res;

    return (*(__IO uint32_t *) tmp);
}

/*!
 * @brief     Configs the SDIO Dataaccording to the specified parameters in the dataConfig
 *
 * @param     dataConfig: pointer to a SDIO_DataConfig_T structure
 *
 * @retval    None
 */
void SDIO_ConfigData(SDIO_DataConfig_T *dataConfig)
{
    uint32_t tempReg = 0;

    SDIO->DATATIME = dataConfig->dataTimeOut;

    SDIO->DATALEN = dataConfig->dataLength;

    tempReg = SDIO->DCTRL;
    /* Clear DTEN, DTSEL, DTDRCFG and DBSIZE bits */
    tempReg &= ((uint32_t)0xFFFFFF08);
    tempReg |= (uint32_t)(dataConfig->dataBlockSize) << 4 | (dataConfig->transferDir) << 1
               | (dataConfig->transferMode) << 2 | (dataConfig->DPSM);
    SDIO->DCTRL = tempReg;
}

/*!
 * @brief     Fills each SDIO_DataConfig_T member with its default value
 *
 * @param     dataConfig: pointer to a SDIO_DataConfig_T structure
 *
 * @retval    None
 */
void SDIO_ConfigDataStructInit(SDIO_DataConfig_T *dataConfig)
{
    dataConfig->dataTimeOut = 0xFFFFFFFF;
    dataConfig->dataLength = 0x00;
    dataConfig->dataBlockSize = SDIO_DATA_BLOCKSIZE_1B;
    dataConfig->transferDir = SDIO_TRANSFER_DIR_TO_CARD;
    dataConfig->transferMode = SDIO_TRANSFER_MODE_BLOCK;
    dataConfig->DPSM = SDIO_DPSM_DISABLE;
}

/*!
 * @brief     Reads the SDIO Data counter
 *
 * @param     None
 *
 * @retval    The SDIO Data counter value
 */
uint32_t SDIO_ReadDataCounter(void)
{
    return SDIO->DCNT;
}

/*!
 * @brief     Write the SDIO Data
 *
 * @param     data : a 32-bit data to write
 *
 * @retval    None
 */
void SDIO_WriteData(uint32_t data)
{
    SDIO->FIFODATA = data;
}

/*!
 * @brief     Reads the SDIO Data
 *
 * @param     None
 *
 * @retval    The SDIO FIFO Data value
 */
uint32_t SDIO_ReadData(void)
{
    return SDIO->FIFODATA;
}

/*!
 * @brief     Reads the SDIO FIFO count value
 *
 * @param     None
 *
 * @retval    The SDIO FIFO count value
 */
uint32_t SDIO_ReadFIFOCount(void)
{
    return SDIO->FIFOCNT;
}

/*!
 * @brief     Enables SDIO start read wait
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_EnableStartReadWait(void)
{
    SDIO->DCTRL_B.RWSTR = SET;
}

/*!
 * @brief     Disables SDIO stop read wait
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_DisableStartReadWait(void)
{
    SDIO->DCTRL_B.RWSTR = RESET;
}

/*!
 * @brief     Disables SDIO start read wait
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_DisableStopReadWait(void)
{
    SDIO->DCTRL_B.RWSTOP = RESET;
}

/*!
 * @brief     Enables SDIO stop read wait
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_EnableStopReadWait(void)
{
    SDIO->DCTRL_B.RWSTOP = SET;
}

/*!
 * @brief     Config the read wait interval
 *
 * @param     readWaitMode: SDIO read Wait Mode
 *                  The parameter can be one of following values:
 *                  @arg SDIO_READ_WAIT_MODE_DATA2  : Read Wait control using SDIO_DATA2
 *                  @arg SDIO_READ_WAIT_MODE_CLK    : Read Wait control by stopping SDIOCLK
 *
 * @retval    None
 *
 * @note
 */
void SDIO_ConfigSDIOReadWaitMode(SDIO_READ_WAIT_MODE_T readWaitMode)
{
    SDIO->DCTRL_B.RDWAIT = readWaitMode;
}
/*!
 * @brief     Enables SDIO SD I/O Mode Operation
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_EnableSDIO(void)
{
    SDIO->DCTRL_B.SDIOF = SET;
}

/*!
 * @brief     Disables SDIO SD I/O Mode Operation
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_DisableSDIO(void)
{
    SDIO->DCTRL_B.SDIOF = RESET;
}

/*!
 * @brief     Ensables SDIO SD I/O Mode suspend command sending
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_EnableTxSDIOSuspend(void)
{
    SDIO->CMD_B.SDIOSC = SET;
}

/*!
 * @brief     Disables SDIO SD I/O Mode suspend command sending
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_DisableTxSDIOSuspend(void)
{
    SDIO->CMD_B.SDIOSC = RESET;
}

/*!
 * @brief     Enables the command completion signal
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_EnableCommandCompletion(void)
{
    SDIO->CMD_B.CMDCPEN = SET;
}

/*!
 * @brief     Disables the command completion signal
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_DisableCommandCompletion(void)
{
    SDIO->CMD_B.CMDCPEN = RESET;
}

/*!
 * @brief     Enables the CE-ATA interrupt
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_EnableCEATAInterrupt(void)
{
    SDIO->CMD_B.INTEN = RESET;
}

/*!
 * @brief     Disables the CE-ATA interrupt
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_DisableCEATAInterrupt(void)
{
    SDIO->CMD_B.INTEN =  SET;
}

/*!
 * @brief     Ensables Sends CE-ATA command
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_EnableTxCEATA(void)
{
    SDIO->CMD_B.ATACMD = SET;
}

/*!
 * @brief     Disables Sends CE-ATA command
 *
 * @param     None
 *
 * @retval    None
 */
void SDIO_DisableTxCEATA(void)
{
    SDIO->CMD_B.ATACMD = RESET;
}

/*!
 * @brief     Enables the specified SDIO interrupt
 *
 * @param     interrupt: Select the SDIO interrupt source
 *                       The parameter can be any combination of following values:
 *                       @arg SDIO_INT_COMRESP  : Command response received (CRC check failed) interrupt
 *                       @arg SDIO_INT_DBDR     : Data block sent/received (CRC check failed) interrupt
 *                       @arg SDIO_INT_CMDRESTO : Command response timeout interrupt
 *                       @arg SDIO_INT_DATATO   : Data timeout interrupt
 *                       @arg SDIO_INT_TXUDRER  : Transmit FIFO underrun error interrupt
 *                       @arg SDIO_INT_RXOVRER  : Received FIFO overrun error interrupt
 *                       @arg SDIO_INT_CMDRES   : Command response received (CRC check passed) interrupt
 *                       @arg SDIO_INT_CMDSENT  : Command sent (no response required) interrupt
 *                       @arg SDIO_INT_DATAEND  : Data end (data counter, SDIDCOUNT, is zero) interrupt
 *                       @arg SDIO_INT_SBE      : Start bit not detected on all data signals in wide bus mode interrupt
 *                       @arg SDIO_INT_DBCP     : Data block sent/received (CRC check passed) interrupt
 *                       @arg SDIO_INT_CMDACT   : Command transfer in progress interrupt
 *                       @arg SDIO_INT_TXACT    : Data transmit in progress interrupt
 *                       @arg SDIO_INT_RXACT    : Data receive in progress interrupt
 *                       @arg SDIO_INT_TXFHF    : Transmit FIFO Half Empty interrupt
 *                       @arg SDIO_INT_RXFHF    : Receive FIFO Half Full interrupt
 *                       @arg SDIO_INT_TXFF     : Transmit FIFO full interrupt
 *                       @arg SDIO_INT_RXFF     : Receive FIFO full interrupt
 *                       @arg SDIO_INT_TXFE     : Transmit FIFO empty interrupt
 *                       @arg SDIO_INT_RXFE     : Receive FIFO empty interrupt
 *                       @arg SDIO_INT_TXDA     : Data available in transmit FIFO interrupt
 *                       @arg SDIO_INT_RXDA     : Data available in receive FIFO interrupt
 *                       @arg SDIO_INT_SDIOINT  : SD I/O interrupt received interrupt
 *                       @arg SDIO_INT_ATAEND   : CE-ATA command completion signal received for CMD61 interrupt
 *
 * @retval    None
 */
void SDIO_EnableInterrupt(uint32_t interrupt)
{
    SDIO->MASK |= interrupt;
}

/*!
 * @brief     Disables the specified SDIO interrupt
 *
 * @param     interrupt: Select the SDIO interrupt source
 *                       The parameter can be any combination of following values:
 *                       @arg SDIO_INT_COMRESP  : Command response received (CRC check failed) interrupt
 *                       @arg SDIO_INT_DBDR     : Data block sent/received (CRC check failed) interrupt
 *                       @arg SDIO_INT_CMDRESTO : Command response timeout interrupt
 *                       @arg SDIO_INT_DATATO   : Data timeout interrupt
 *                       @arg SDIO_INT_TXUDRER  : Transmit FIFO underrun error interrupt
 *                       @arg SDIO_INT_RXOVRER  : Received FIFO overrun error interrupt
 *                       @arg SDIO_INT_CMDRES   : Command response received (CRC check passed) interrupt
 *                       @arg SDIO_INT_CMDSENT  : Command sent (no response required) interrupt
 *                       @arg SDIO_INT_DATAEND  : Data end (data counter, SDIDCOUNT, is zero) interrupt
 *                       @arg SDIO_INT_SBE      : Start bit not detected on all data signals in wide bus mode interrupt
 *                       @arg SDIO_INT_DBCP     : Data block sent/received (CRC check passed) interrupt
 *                       @arg SDIO_INT_CMDACT   : Command transfer in progress interrupt
 *                       @arg SDIO_INT_TXACT    : Data transmit in progress interrupt
 *                       @arg SDIO_INT_RXACT    : Data receive in progress interrupt
 *                       @arg SDIO_INT_TXFHF    : Transmit FIFO Half Empty interrupt
 *                       @arg SDIO_INT_RXFHF    : Receive FIFO Half Full interrupt
 *                       @arg SDIO_INT_TXFF     : Transmit FIFO full interrupt
 *                       @arg SDIO_INT_RXFF     : Receive FIFO full interrupt
 *                       @arg SDIO_INT_TXFE     : Transmit FIFO empty interrupt
 *                       @arg SDIO_INT_RXFE     : Receive FIFO empty interrupt
 *                       @arg SDIO_INT_TXDA     : Data available in transmit FIFO interrupt
 *                       @arg SDIO_INT_RXDA     : Data available in receive FIFO interrupt
 *                       @arg SDIO_INT_SDIOINT  : SD I/O interrupt received interrupt
 *                       @arg SDIO_INT_ATAEND   : CE-ATA command completion signal received for CMD61 interrupt
 *
 * @retval    None
 */
void SDIO_DisableInterrupt(uint32_t interrupt)
{
    SDIO->MASK &= ~interrupt;
}

/*!
 * @brief     Reads the specified SDIO flag
 *
 * @param     flag: Select the flag to read
 *              The parameter can be one of following values:
 *              @arg SDIO_FLAG_COMRESP  : Command response received (CRC check failed) flag
 *              @arg SDIO_FLAG_DBDR     : Data block sent/received (CRC check failed) flag
 *              @arg SDIO_FLAG_CMDRESTO : Command response timeout flag
 *              @arg SDIO_FLAG_DATATO   : Data timeout flag
 *              @arg SDIO_FLAG_TXUDRER  : Transmit FIFO underrun error flag
 *              @arg SDIO_FLAG_RXOVRER  : Received FIFO overrun error flag
 *              @arg SDIO_FLAG_CMDRES   : Command response received (CRC check passed) flag
 *              @arg SDIO_FLAG_CMDSENT  : Command sent (no response required) flag
 *              @arg SDIO_FLAG_DATAEND  : Data end (data counter is zero) flag
 *              @arg SDIO_FLAG_SBE      : Start bit not detected on all data signals in wide bus mode flag
 *              @arg SDIO_FLAG_DBCP     : Data block sent/received (CRC check passed) flag
 *              @arg SDIO_FLAG_CMDACT   : Command transfer in progress flag
 *              @arg SDIO_FLAG_TXACT    : Data transmit in progress flag
 *              @arg SDIO_FLAG_RXACT    : Data receive in progress flag
 *              @arg SDIO_FLAG_TXFHF    : Transmit FIFO Half Empty flag
 *              @arg SDIO_FLAG_RXFHF    : Receive FIFO Half Full flag
 *              @arg SDIO_FLAG_TXFF     : Transmit FIFO full flag
 *              @arg SDIO_FLAG_RXFF     : Receive FIFO full flag
 *              @arg SDIO_FLAG_TXFE     : Transmit FIFO empty flag
 *              @arg SDIO_FLAG_RXFE     : Receive FIFO empty flag
 *              @arg SDIO_FLAG_TXDA     : Data available in transmit FIFO flag
 *              @arg SDIO_FLAG_RXDA     : Data available in receive FIFO flag
 *              @arg SDIO_FLAG_SDIOINT  : SD I/O interrupt received flag
 *              @arg SDIO_FLAG_ATAEND   : CE-ATA command completion signal received for CMD61 flag
 *
 * @retval    SET or RESET
 */
uint8_t SDIO_ReadStatusFlag(SDIO_FLAG_T flag)
{
    return (SDIO->STS & flag) ? SET : RESET;
}

/*!
 * @brief     Clears the specified SDIO flag
 *
 * @param     flag: Select the flag to clear
 *              The parameter can be any combination of following values:
 *              @arg SDIO_FLAG_COMRESP  : Command response received (CRC check failed) flag
 *              @arg SDIO_FLAG_DBDR     : Data block sent/received (CRC check failed) flag
 *              @arg SDIO_FLAG_CMDRESTO : Command response timeout flag
 *              @arg SDIO_FLAG_DATATO   : Data timeout flag
 *              @arg SDIO_FLAG_TXUDRER  : Transmit FIFO underrun error flag
 *              @arg SDIO_FLAG_RXOVRER  : Received FIFO overrun error flag
 *              @arg SDIO_FLAG_CMDRES   : Command response received (CRC check passed) flag
 *              @arg SDIO_FLAG_CMDSENT  : Command sent (no response required) flag
 *              @arg SDIO_FLAG_DATAEND  : Data end (data counter is zero) flag
 *              @arg SDIO_FLAG_SBE      : Start bit not detected on all data signals in wide bus mode flag
 *              @arg SDIO_FLAG_DBCP     : Data block sent/received (CRC check passed) flag
 *              @arg SDIO_FLAG_SDIOINT  : SD I/O interrupt received flag
 *              @arg SDIO_FLAG_ATAEND   : CE-ATA command completion signal received for CMD61 flag
 *
 * @retval    None
 */
void SDIO_ClearStatusFlag(uint32_t flag)
{
    SDIO->ICF = flag;
}

/*!
 * @brief     Reads the specified SDIO Interrupt flag
 *
 * @param     flag: Select the SDIO interrupt source
 *              The parameter can be one of following values:
 *              @arg SDIO_INT_COMRESP   : Command response received (CRC check failed) interrupt
 *              @arg SDIO_INT_DBDR      : Data block sent/received (CRC check failed) interrupt
 *              @arg SDIO_INT_CMDRESTO  : Command response timeout interrupt
 *              @arg SDIO_INT_DATATO    : Data timeout interrupt
 *              @arg SDIO_INT_TXUDRER   : Transmit FIFO underrun error interrupt
 *              @arg SDIO_INT_RXOVRER   : Received FIFO overrun error interrupt
 *              @arg SDIO_INT_CMDRES    : Command response received (CRC check passed) interrupt
 *              @arg SDIO_INT_CMDSENT   : Command sent (no response required) interrupt
 *              @arg SDIO_INT_DATAEND   : Data end (data counter is zero) interrupt
 *              @arg SDIO_INT_SBE       : Start bit not detected on all data signals in wide bus mode interrupt
 *              @arg SDIO_INT_DBCP      : Data block sent/received (CRC check passed) interrupt
 *              @arg SDIO_INT_CMDACT    : Command transfer in progress interrupt
 *              @arg SDIO_INT_TXACT     : Data transmit in progress interrupt
 *              @arg SDIO_INT_RXACT     : Data receive in progress interrupt
 *              @arg SDIO_INT_TXFHF     : Transmit FIFO Half Empty interrupt
 *              @arg SDIO_INT_RXFHF     : Receive FIFO Half Full interrupt
 *              @arg SDIO_INT_TXFF      : Transmit FIFO full interrupt
 *              @arg SDIO_INT_RXFF      : Receive FIFO full interrupt
 *              @arg SDIO_INT_TXFE      : Transmit FIFO empty interrupt
 *              @arg SDIO_INT_RXFE      : Receive FIFO empty interrupt
 *              @arg SDIO_INT_TXDA      : Data available in transmit FIFO interrupt
 *              @arg SDIO_INT_RXDA      : Data available in receive FIFO interrupt
 *              @arg SDIO_INT_SDIOINT   : SD I/O interrupt received interrupt
 *              @arg SDIO_INT_ATAEND    : CE-ATA command completion signal received for CMD61 interrupt
 *
 * @retval    SET or RESET
 */
uint8_t SDIO_ReadIntFlag(SDIO_INT_T flag)
{
    uint32_t intEnable;
    uint32_t intStatus;

    intEnable = (uint32_t)(SDIO->MASK & flag);
    intStatus = (uint32_t)(SDIO->STS & flag);

    if (intEnable && intStatus)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief     Clears the specified SDIO Interrupt pending bits
 *
 * @param     flag: Select the SDIO interrupt source
 *              The parameter can be any combination of following values:
 *              @arg SDIO_INT_COMRESP   : Command response received (CRC check failed) interrupt
 *              @arg SDIO_INT_DBDR      : Data block sent/received (CRC check failed) interrupt
 *              @arg SDIO_INT_CMDRESTO  : Command response timeout interrupt
 *              @arg SDIO_INT_DATATO    : Data timeout interrupt
 *              @arg SDIO_INT_TXUDRER   : Transmit FIFO underrun error interrupt
 *              @arg SDIO_INT_RXOVRER   : Received FIFO overrun error interrupt
 *              @arg SDIO_INT_CMDRES    : Command response received (CRC check passed) interrupt
 *              @arg SDIO_INT_CMDSENT   : Command sent (no response required) interrupt
 *              @arg SDIO_INT_DATAEND   : Data end (data counter is zero) interrupt
 *              @arg SDIO_INT_SBE       : Start bit not detected on all data signals in wide bus mode interrupt
 *              @arg SDIO_INT_DBCP      : Data block sent/received (CRC check passed) interrupt
 *              @arg SDIO_INT_SDIOINT   : SD I/O interrupt received interrupt
 *              @arg SDIO_INT_ATAEND    : CE-ATA command completion signal received for CMD61 interrupt
 *
 * @retval    None
 */
void SDIO_ClearIntFlag(uint32_t flag)
{
    SDIO->ICF = flag;
}

/**@} end of group SDIO_Functions */
/**@} end of group SDIO_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
