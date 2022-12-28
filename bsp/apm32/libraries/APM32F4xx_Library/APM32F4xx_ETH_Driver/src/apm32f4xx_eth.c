/*!
 * @file        apm32f4xx_eth.c
 *
 * @brief       This file provides all the ETH firmware functions
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

#include "apm32f4xx_eth.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_ETHDriver
  @{
*/

/** @defgroup ETH_Driver
  * @brief ETH driver modules
  @{
*/

#if defined   (__CC_ARM) /*!< ARM Compiler */
__align(4)
ETH_DMADescConfig_T  DMARxDscrTab[ETH_RXBUFNB]; /*!< Ethernet Rx MA Descriptor */
__align(4)
ETH_DMADescConfig_T  DMATxDscrTab[ETH_TXBUFNB]; /*!< Ethernet Tx DMA Descriptor */
__align(4)
uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE];  /*!< Ethernet Receive Buffer */
__align(4)
uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE];  /*!< Ethernet Transmit Buffer */

#elif defined ( __ICCARM__ )

ETH_DMADescConfig_T  DMARxDscrTab[ETH_RXBUFNB]; /*!< Ethernet Rx MA Descriptor */
ETH_DMADescConfig_T  DMATxDscrTab[ETH_TXBUFNB]; /*!< Ethernet Tx DMA Descriptor */
uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE];  /*!< Ethernet Receive Buffer */
uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE];  /*!< Ethernet Transmit Buffer */

#endif

/** @defgroup Global_Definition
  @{
*/

/* Global pointers on Tx and Rx descriptor used to transmit and receive descriptors */
__IO ETH_DMADescConfig_T  *DMATxDescToSet;
__IO ETH_DMADescConfig_T  *DMARxDescToGet;

/* Structure used to hold the last received packet descriptors info */
ETH_DMARxFrameInformations      RxFrameDescriptor;
__IO ETH_DMARxFrameInformations *DMARxFraminfos;
__IO uint32_t FrameRxindex;

/**
  * @}
  */

/** @defgroup ETH_Functions
  @{
*/

/*!
 * @brief  Inserts a delay time.
 *
 * @param  count: specifies the delay time length.
 *
 * @retval None
 */
static void ETH_Delay(__IO uint32_t count)
{
    __IO uint32_t i = 0;
    for(i = count; i!= 0; i--)
    {
    }
}

/** ETH Configuration */

/*!
 * @brief  Reset ETH peripheral registers to their default reset values.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_Reset(void)
{
    RCM_EnableAHB1PeriphReset(RCM_AHB1_PERIPH_ETH_MAC);
    RCM_DisableAHB1PeriphReset(RCM_AHB1_PERIPH_ETH_MAC);
}

/*!
 * @brief  Config ETH_Config_T member with its default value.
 *
 * @param  ethConfig: pointer to a ETH_Config_T structure which will be initialized.
 *
 * @retval None
 */
void ETH_ConfigStructInit(ETH_Config_T* ethConfig)
{
    /* MAC Configuration */
    ethConfig->autoNegotiation = ETH_AUTONEGOTIATION_ENABLE;
    ethConfig->watchDog = ETH_WATCHDOG_ENABLE;
    ethConfig->jabber = ETH_JABBER_ENABLE;
    ethConfig->interFrameGap = ETH_INTERFRAMEGAP_96BIT;
    ethConfig->carrierSense = ETH_CARRIERSENCE_ENABLE;
    ethConfig->speed = ETH_SPEED_100M;
    ethConfig->receiveOwn = ETH_RECEIVEOWN_ENABLE;
    ethConfig->loopbackMode = ETH_LOOPBACKMODE_DISABLE;
    ethConfig->mode = ETH_MODE_FULLDUPLEX;
    ethConfig->checksumOffload = ETH_CHECKSUMOFFLAOD_DISABLE;
    ethConfig->retryTransmission = ETH_RETRYTRANSMISSION_ENABLE;
    ethConfig->automaticPadCRCStrip = ETH_AUTOMATICPADCRCSTRIP_DISABLE;
    ethConfig->backOffLimit = ETH_BACKOFFLIMIT_10;
    ethConfig->deferralCheck = ETH_DEFFERRALCHECK_DISABLE;
    ethConfig->receiveAll = ETH_RECEIVEAll_DISABLE;
    ethConfig->sourceAddrFilter = ETH_SOURCEADDRFILTER_DISABLE;
    ethConfig->passControlFrames = ETH_PASSCONTROLFRAMES_BLOCKALL;
    ethConfig->broadcastFramesReception = ETH_BROADCASTFRAMESRECEPTION_DISABLE;
    ethConfig->destinationAddrFilter = ETH_DESTINATIONADDRFILTER_NORMAL;
    ethConfig->promiscuousMode = ETH_PROMISCUOUS_MODE_DISABLE;
    ethConfig->multicastFramesFilter = ETH_MULTICASTFRAMESFILTER_PERFECT;
    ethConfig->unicastFramesFilter = ETH_UNICASTFRAMESFILTER_PERFECT;
    ethConfig->hashTableHigh = 0x0000;
    ethConfig->hashTableLow = 0x0000;
    ethConfig->pauseTime = 0x0000;
    ethConfig->zeroQuantaPause = ETH_ZEROQUANTAPAUSE_DISABLE;
    ethConfig->pauseLowThreshold = ETH_PAUSELOWTHRESHOLD_MINUS4;
    ethConfig->unicastPauseFrameDetect = ETH_UNICASTPAUSEFRAMEDETECT_DISABLE;
    ethConfig->receiveFlowControl = ETH_RECEIVEFLOWCONTROL_DISABLE;
    ethConfig->transmitFlowControl = ETH_TRANSMITFLOWCONTROL_DISABLE;
    ethConfig->VLANTagComparison = ETH_VLANTAGCOMPARISON_16BIT;
    ethConfig->VLANTagIdentifier = 0x0000;
    /* DMA Configuration */
    ethConfig->dropTCPIPChecksumErrorFrame = ETH_DROPTCPIPCHECKSUMERRORFRAME_DISABLE;
    ethConfig->receiveStoreForward = ETH_RECEIVESTOREFORWARD_ENABLE;
    ethConfig->flushReceivedFrame = ETH_FLUSHRECEIVEDFRAME_ENABLE;
    ethConfig->transmitStoreForward = ETH_TRANSMITSTOREFORWARD_ENABLE;
    ethConfig->transmitThresholdControl = ETH_TRANSMITTHRESHOLDCONTROL_64BYTES;
    ethConfig->forwardErrorFrames = ETH_FORWARDERRORFRAMES_DISABLE;
    ethConfig->forwardUndersizedGoodFrames = ETH_FORWARDUNDERSIZEDGOODFRAMES_DISABLE;
    ethConfig->receiveThresholdControl = ETH_RECEIVEDTHRESHOLDCONTROL_64BYTES;
    ethConfig->secondFrameOperate = ETH_SECONDFRAMEOPERARTE_DISABLE;
    ethConfig->addressAlignedBeats = ETH_ADDRESSALIGNEDBEATS_ENABLE;
    ethConfig->fixedBurst = ETH_FIXEDBURST_ENABLE;
    ethConfig->rxDMABurstLength = ETH_RXDMABURSTLENGTH_32BEAT;
    ethConfig->txDMABurstLength = ETH_TXDMABURSTLENGTH_32BEAT;
    ethConfig->descriptorSkipLength = 0x00;
    ethConfig->DMAArbitration = ETH_DMAARBITRATION_ROUNDROBIN_RXTX_1_1;
}

/*!
 * @brief  Config the ETH peripheral parameters in the ethConfig.
 *
 * @param  ethConfig: pointer to a ETH_Config_T structure.
 *
 * @param  addr: external PHY address
 *
 * @retval ETH_ERROR: Ethernet initialization error
 *         ETH_SUCCESS: Ethernet initialization success
 */
uint32_t ETH_Config(ETH_Config_T* ethConfig, uint16_t addr)
{
    uint32_t regValue = 0;
    uint32_t hclk = 60000000;
    __IO uint32_t timeout = 0, err = ETH_SUCCESS;

    hclk = RCM_ReadHCLKFreq();

    if((hclk >= 20000000) && (hclk <= 35000000))
    {
        ETH->ADDR_B.CR = ETH_MACMIIAR_CR_DIV16;
    }
    else if((hclk >= 35000000)&&(hclk < 60000000))
    {
        ETH->ADDR_B.CR = ETH_MACMIIAR_CR_DIV26;
    }
    else if((hclk >= 60000000)&&(hclk < 100000000))
    {
        ETH->ADDR_B.CR = ETH_MACMIIAR_CR_DIV42;
    }
    else if((hclk >= 100000000)&&(hclk < 150000000))
    {
        ETH->ADDR_B.CR = ETH_MACMIIAR_CR_DIV62;
    }
    else
    {
        ETH->ADDR_B.CR = ETH_MACMIIAR_CR_DIV102;
    }

    /* PHY initialization and configuration */
    if(!(ETH_WritePHYRegister(addr, PHY_BCR, PHY_RESET)))
    {
    /* Return ERROR in case of write timeout */
    err = ETH_ERROR;
    goto error;
    }

    ETH_Delay(PHY_RESET_DELAY);

    if(ethConfig->autoNegotiation == ETH_AUTONEGOTIATION_ENABLE)
    {
        /* Wait for linked status */
        do
        {
            timeout++ ;
        } while(!(ETH_ReadPHYRegister(addr,PHY_BSR) & PHY_LINKED_STATUS) && (timeout < PHY_READ_TIMEOUT));

        /* Return ERROR in case of timeout */
        if(timeout == PHY_READ_TIMEOUT)
        {
            err = ETH_ERROR;
            goto error;
        }

        timeout = 0;
        /* Enable Auto-Negotiation */
        if(!(ETH_WritePHYRegister(addr, PHY_BCR, PHY_AUTONEGOTIATION)))
        {
            /* Return ERROR in case of write timeout */
            err = ETH_ERROR;
        }

        /* Wait until the auto-negotiation will be completed */
        do
        {
        timeout++;
        } while (!(ETH_ReadPHYRegister(addr, PHY_BSR) & PHY_AUTONEGO_COMPLETE) && (timeout < (uint32_t)PHY_READ_TIMEOUT));

        /* Return ERROR in case of timeout */
        if(timeout == PHY_READ_TIMEOUT)
        {
            err = ETH_ERROR;
            goto error;
        }

        timeout = 0;
        /* Read the result of the auto-negotiation */
        regValue = ETH_ReadPHYRegister(addr, PHY_SR);

        if((regValue & PHY_DUPLEX_STATUS) != (uint32_t)RESET)
        {
            ethConfig->mode = ETH_MODE_FULLDUPLEX;
        }
        else
        {
            ethConfig->mode = ETH_MODE_HALFDUPLEX;
        }
        if(regValue & PHY_SPEED_STATUS)
        {
            ethConfig->speed = ETH_SPEED_10M;
        }
        else
        {
            ethConfig->speed = ETH_SPEED_100M;
        }
    }
    else
    {
        if(!ETH_WritePHYRegister(addr, PHY_BCR,((uint16_t)(ethConfig->speed << 8) |
                                                (uint16_t)(ethConfig->mode  << 13))))
        {
            err = ETH_ERROR;
        }

        ETH_Delay(PHY_CONFIG_DELAY);
    }
error:
    if(err == ETH_ERROR)
    {
        ethConfig->speed = ETH_SPEED_100M;
        ethConfig->mode = ETH_MODE_FULLDUPLEX;
    }

    /* ETHERNET MAC_CFG Configuration */
    ETH->CFG_B.WDTDIS = ethConfig->watchDog;
    ETH->CFG_B.JDIS   = ethConfig->jabber;
    ETH->CFG_B.IFG    = ethConfig->interFrameGap;
    ETH->CFG_B.DISCRS = ethConfig->carrierSense;
    ETH->CFG_B.SSEL   = ethConfig->speed;
    ETH->CFG_B.DISRXO = ethConfig->receiveOwn;
    ETH->CFG_B.LBM    = ethConfig->loopbackMode;
    ETH->CFG_B.DM     = ethConfig->mode;
    ETH->CFG_B.IPC    = ethConfig->checksumOffload;
    ETH->CFG_B.DISR   = ethConfig->retryTransmission;
    ETH->CFG_B.ACS    = ethConfig->automaticPadCRCStrip;
    ETH->CFG_B.BL     = ethConfig->backOffLimit;
    ETH->CFG_B.DC     = ethConfig->deferralCheck;
    ETH_Delay(ETH_REG_WRITE_DELAY);

    /* ETHERNET MAC_FRAF Configuration */
    ETH->FRAF_B.RXA    = ethConfig->receiveAll;
    ETH->FRAF         |= ethConfig->sourceAddrFilter;
    ETH->FRAF_B.PCTRLF = ethConfig->passControlFrames;
    ETH->FRAF_B.DISBF  = ethConfig->broadcastFramesReception;
    ETH->FRAF_B.DAIF   = ethConfig->destinationAddrFilter;
    ETH->FRAF_B.PR     = ethConfig->promiscuousMode;
    ETH->FRAF         |= ethConfig->multicastFramesFilter;
    ETH->FRAF         |= ethConfig->unicastFramesFilter;
    ETH_Delay(ETH_REG_WRITE_DELAY);

    /* ETHERNET MAC_HTH/HTL Configuration */
    ETH->HTH = ethConfig->hashTableHigh;
    ETH->HTL = ethConfig->hashTableLow;

    /* ETHERNET MAC_FCTRL Configuration */
    ETH->FCTRL_B.PT        = ethConfig->pauseTime;
    ETH->FCTRL_B.ZQPDIS    = ethConfig->zeroQuantaPause;
    ETH->FCTRL_B.PTSEL     = ethConfig->pauseLowThreshold;
    ETH->FCTRL_B.UNPFDETE  = ethConfig->unicastPauseFrameDetect;
    ETH->FCTRL_B.RXFCTRLEN = ethConfig->receiveFlowControl;
    ETH->FCTRL_B.TXFCTRLEN = ethConfig->transmitFlowControl;
    ETH_Delay(ETH_REG_WRITE_DELAY);

    /* ETHERNET MAC_VLANT Configuration */
    ETH->VLANT_B.VLANTCOMP = ethConfig->VLANTagComparison;
    ETH->VLANT_B.VLANTID   = ethConfig->VLANTagIdentifier;
    ETH_Delay(ETH_REG_WRITE_DELAY);

    /* ETHERNET DMA_OPMOD Configuration */
    ETH->DMAOPMOD_B.DISDT    = ethConfig->dropTCPIPChecksumErrorFrame;
    ETH->DMAOPMOD_B.RXSF     = ethConfig->receiveStoreForward;
    ETH->DMAOPMOD_B.DISFRXF  = ethConfig->flushReceivedFrame;
    ETH->DMAOPMOD_B.TXSF     = ethConfig->transmitStoreForward;
    ETH->DMAOPMOD_B.TXTHCTRL = ethConfig->transmitThresholdControl;
    ETH->DMAOPMOD_B.FERRF    = ethConfig->forwardErrorFrames;
    ETH->DMAOPMOD_B.FUF      = ethConfig->forwardUndersizedGoodFrames;
    ETH->DMAOPMOD_B.RXTHCTRL = ethConfig->receiveThresholdControl;
    ETH->DMAOPMOD_B.OSECF    = ethConfig->secondFrameOperate;
    ETH_Delay(ETH_REG_WRITE_DELAY);

    /* ETHERNET DMA_BMOD Configuration */
    ETH->DMABMOD = RESET;
    ETH->DMABMOD_B.AAL = ethConfig->addressAlignedBeats;
    ETH->DMABMOD_B.FB = ethConfig->fixedBurst;
    ETH->DMABMOD |= ethConfig->rxDMABurstLength;
    ETH->DMABMOD |= ethConfig->txDMABurstLength;
    ETH->DMABMOD_B.DSL = ethConfig->descriptorSkipLength;
    ETH->DMABMOD |= ethConfig->DMAArbitration;
    ETH->DMABMOD_B.USP = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);

#if USE_ENHANCED_DMA_DESCRIPTORS
    ETH->DMABMOD_B.EDFEN = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
#endif

    if(err == ETH_SUCCESS)
    {
        return ETH_SUCCESS;
    }
    else
    {
        return ETH_ERROR;
    }
}

/*!
 * @brief  Resets all MAC subsystem internal registers and logic.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_SoftwareReset(void)
{
    ETH->DMABMOD_B.SWR = SET;
}

/*!
 * @brief  Read the ETH software reset bit.
 *
 * @param  None
 *
 * @retval SET or RESET.
 */
uint8_t ETH_ReadSoftwareReset(void)
{
    return ETH->DMABMOD_B.SWR;
}

/*!
 * @brief     Enables ETH MAC and DMA reception/transmission
 *
 * @param     None
 *
 * @retval    None
 */
void ETH_Start(void)
{
    ETH_EnableMACTransmission();
    ETH_EnableMACReceiver();
    ETH_FlushTransmitFIFO();
    ETH_EnableDMATransmission();
    ETH_EnableDMAReceiver();
}

/*!
 * @brief     Disables ETH MAC and DMA reception/transmission
 *
 * @param     None
 *
 * @retval    None
 */
void ETH_Stop(void)
{
    ETH_DisableDMATransmission();
    ETH_DisableDMAReceiver();
    ETH_DisableMACReceiver();
    ETH_FlushTransmitFIFO();
    ETH_DisableMACTransmission();
}

/*!
 * @brief  Read the size of the received packet.
 *
 * @param  None
 *
 * @retval frameLength: received packet size
 */
uint32_t ETH_ReadRxPacketSize(ETH_DMADescConfig_T *DMARxDesc)
{
    uint32_t frameLength = 0;
    if(((DMARxDesc->Status & ETH_DMARXDESC_OWN) == (uint32_t)RESET) &&
       ((DMARxDesc->Status & ETH_DMARXDESC_ERRS)  == (uint32_t)RESET) &&
       ((DMARxDesc->Status & ETH_DMARXDESC_LDES)  != (uint32_t)RESET))
    {
        frameLength =  ETH_ReadDMARxDescFrameLength(DMARxDesc);
    }
    return frameLength;
}

#if USE_ENHANCED_DMA_DESCRIPTORS
/*!
 * @brief  Enable the Enhanced descriptor structure.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_EnableEnhancedDescriptor(void)
{
     ETH->DMABMOD_B.EDFEN = SET;
}

/*!
 * @brief  Disable the Enhanced descriptor structure.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_DisableEnhancedDescriptor(void)
{
     ETH->DMABMOD_B.EDFEN = RESET;
}
#endif /** USE_ENHANCED_DMA_DESCRIPTORS */

/** PHY functions */

/*!
 * @brief  Read a PHY register
 *
 * @param  addr: PHY device address
 *               This parameter can be one of the following values: 0,..,31
 *
 * @param  reg:  PHY register
 *               This parameter can be one of the following values:
 *               @arg PHY_BCR : Transceiver Basic Control Register
 *               @arg PHY_BSR : Transceiver Basic Status Register
 *               @arg PHY_SR  :  Transceiver Status Register
 *
 * @retval ETH_ERROR: in case of timeout
 *         MAC DATA register value: Data read from the selected PHY register
 */
uint16_t ETH_ReadPHYRegister(uint16_t addr, uint16_t reg)
{
    __IO uint32_t timeout = 0;

    ETH->ADDR_B.PA = addr;
    ETH->ADDR_B.MR = reg;
    ETH->ADDR_B.MW = RESET;
    ETH->ADDR_B.MB = SET;
    /* Check for the Busy flag */
    do
    {
        timeout++ ;
    } while ((ETH->ADDR_B.MB == SET) && (timeout < PHY_READ_TIMEOUT));
    /* Return ERROR in case of timeout */
    if(timeout == PHY_READ_TIMEOUT)
    {
        return ETH_ERROR;
    }
    /* Return data register value */
    return (uint16_t)(ETH->DATA);
}

/*!
 * @brief  Write to a PHY register
 *
 * @param  addr: PHY device address
 *               This parameter can be one of the following values: 0,..,31

 * @param  reg:  PHY register
 *               This parameter can be one of the following values:
 *               @arg PHY_BCR : Transceiver Basic Control Register

 * @param  data: the data to write
 *
 * @retval ETH_ERROR: write timeout
 *         ETH_SUCCESS: write success
 */
uint32_t ETH_WritePHYRegister(uint16_t addr, uint16_t reg, uint16_t data)
{
    __IO uint32_t timeout = 0;

    ETH->DATA = data;
    ETH->ADDR_B.PA = addr;
    ETH->ADDR_B.MR = reg;
    ETH->ADDR_B.MW = SET;
    ETH->ADDR_B.MB = SET;

    /* Check for the Busy flag */
    do
    {
        timeout++ ;
    } while ((ETH->ADDR_B.MB == SET) && (timeout < PHY_WRITE_TIMEOUT));
    /* Return ERROR in case of timeout */
    if(timeout == PHY_WRITE_TIMEOUT)
    {
        return ETH_ERROR;
    }
    /* Return data register value */
    return ETH_SUCCESS;
}

/*!
 * @brief  Enable the PHY loopBack mode.
 *
 * @param  addr: PHY device address
 *               This parameter can be one of the following values: 0,..,31
 *
 * @retval ETH_ERROR or ETH_SUCCESS
 */
uint32_t ETH_EnablePHYLoopBack(uint16_t addr)
{
    uint16_t temp = 0;

    temp = ETH_ReadPHYRegister(addr,PHY_BCR);
    temp |= PHY_LOOPBACK;

    if(ETH_WritePHYRegister(addr,PHY_BCR,temp) == SET)
    {
        return ETH_SUCCESS;
    }
    else
    {
        return ETH_ERROR;
    }
}

/*!
 * @brief  Disable the PHY loopBack mode.
 *
 * @param  addr: PHY device address
 *               This parameter can be one of the following values: 0,..,31
 *
 * @retval ETH_ERROR or ETH_SUCCESS
 */
uint32_t ETH_DisablePHYLoopBack(uint16_t addr)
{
    uint16_t temp = 0;

    temp = ETH_ReadPHYRegister(addr,PHY_BCR);
    temp &= ((uint16_t)~PHY_LOOPBACK);

    if(ETH_WritePHYRegister(addr,PHY_BCR,temp) == SET)
    {
        return ETH_SUCCESS;
    }
    else
    {
        return ETH_ERROR;
    }
}

/* MAC functions */

/*!
 * @brief  Enable the MAC transmission.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_EnableMACTransmission(void)
{
    ETH->CFG_B.TXEN = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Disable the MAC transmission.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_DisableMACTransmission(void)
{
    ETH->CFG_B.TXEN = RESET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Enable the MAC receiver.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_EnableMACReceiver(void)
{
    ETH->CFG_B.RXEN = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Disable the MAC receiver.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_DisableMACReceiver(void)
{
    ETH->CFG_B.RXEN = RESET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Read the ETH flow control busy status
 *
 * @param  None
 *
 * @retval SET or RESET
 */
uint8_t ETH_ReadFlowControlBusyStatus(void)
{
    return ETH->FCTRL_B.FCTRLB;
}

/*!
 * @brief  Set a Pause Control Frame (Full-duplex only).
 *
 * @param  None
 *
 * @retval None
 */
void ETH_SetPauseControlFrame(void)
{
    ETH->FCTRL_B.FCTRLB = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Enable the MAC Back Pressure operation activation (Half-duplex only).
 *
 * @param  None
 *
 * @retval None
 */
void ETH_EnableBackPressureActivation(void)
{
    ETH->FCTRL_B.FCTRLB = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Disable the MAC Back Pressure operation activation (Half-duplex only).
 *
 * @param  None
 *
 * @retval None
 */
void ETH_DisableBackPressureActivation(void)
{
    ETH->FCTRL_B.FCTRLB = RESET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Read the specified ETH MAC flag
 *
 * @param  flag: Ethernet MAC flag:
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_FLAG_TST  : Time stamp trigger flag
 *           @arg ETH_MAC_FLAG_MMCT : MMC transmit flag
 *           @arg ETH_MAC_FLAG_MMCR : MMC receive flag
 *           @arg ETH_MAC_FLAG_MMC  : MMC flag
 *           @arg ETH_MAC_FLAG_PMT  : PMT flag
 *
 * @retval SET or RESET.
 */
uint8_t ETH_ReadMACFlagStatus(ETH_MAC_FLAG_T flag)
{
    return (ETH->ISTS & flag) ? SET : RESET;
}

/*!
 * @brief  Enable the specified ETH MAC interrupts.
 *
 * @param  interrupt: Ethernet MAC interrupt flag:
 *         This parameter can be any combination of the following values:
 *           @arg ETH_MAC_INT_TST : Time stamp trigger interrupt
 *           @arg ETH_MAC_INT_PMT : PMT interrupt
 *
 * @retval None
 */
void ETH_EnableMACInterrupt(uint32_t interrupt)
{
    ETH->IMASK |= interrupt;
}

/*!
 * @brief  Disable the specified ETH MAC interrupts.
 *
 * @param  interrupt: Ethernet MAC interrupt flag:
 *         This parameter can be any combination of the following values:
 *           @arg ETH_MAC_INT_TST : Time stamp trigger interrupt
 *           @arg ETH_MAC_INT_PMT : PMT interrupt
 *
 * @retval None
 */
void ETH_DisableMACInterrupt(uint32_t interrupt)
{
    ETH->IMASK &= (~(uint32_t)interrupt);
}

/*!
 * @brief  Config the MAC address.
 *
 * @param  macAddr: The MAC address.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESS0 : MAC Address0
 *           @arg ETH_MAC_ADDRESS1 : MAC Address1
 *           @arg ETH_MAC_ADDRESS2 : MAC Address2
 *           @arg ETH_MAC_ADDRESS3 : MAC Address3
 *
 * @param  addr: Pointer on MAC address buffer data (6 bytes).
 *
 * @retval None
 */
void ETH_ConfigMACAddress(ETH_MAC_ADDRESS_T macAddr, uint8_t *addr)
{
    uint32_t temp;

    temp = ((uint32_t)addr[5] << 8) | (uint32_t)addr[4];
    (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr)) = temp;

    temp = ((uint32_t)addr[3] << 24) | ((uint32_t)addr[2] << 16) | ((uint32_t)addr[1] << 8) | addr[0];
    (*(__IO uint32_t *) (ETH_MAC_ADDR_LBASE + macAddr)) = temp;
}

/*!
 * @brief  Read the MAC address.
 *
 * @param  macAddr: The MAC address.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESS0 : MAC Address0
 *           @arg ETH_MAC_ADDRESS1 : MAC Address1
 *           @arg ETH_MAC_ADDRESS2 : MAC Address2
 *           @arg ETH_MAC_ADDRESS3 : MAC Address3
 *
 * @param  addr: Pointer on MAC address buffer data (6 bytes).
 *
 * @retval None
 */
void ETH_ReadMACAddress(ETH_MAC_ADDRESS_T macAddr, uint8_t *addr)
{
    uint32_t temp;

    temp = (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr));

    addr[5] = ((temp >> 8) & 0xFF);
    addr[4] = (temp & 0xFF);

    temp = (*(__IO uint32_t *) (ETH_MAC_ADDR_LBASE + macAddr));
    addr[3] = ((temp >> 24) & 0xFF);
    addr[2] = ((temp >> 16) & 0xFF);
    addr[1] = ((temp >> 8)  & 0xFF);
    addr[0] = (temp & 0xFF);
}

/*!
 * @brief  Enable address filters module uses the MAC address for perfect filtering.
 *
 * @param  macAddr: The MAC address.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESS1 : MAC Address1
 *           @arg ETH_MAC_ADDRESS2 : MAC Address2
 *           @arg ETH_MAC_ADDRESS3 : MAC Address3
 *
 * @retval None
 */
void ETH_EnableMACAddressPerfectFilter(ETH_MAC_ADDRESS_T macAddr)
{
    __IO uint32_t temp = 0;
    (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr)) |= BIT31;
    ETH_Delay(ETH_REG_WRITE_DELAY);
    (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr)) = temp;
}

/*!
 * @brief  Disable address filters module uses the MAC address for perfect filtering.
 *
 * @param  macAddr: The MAC address.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESS1 : MAC Address1
 *           @arg ETH_MAC_ADDRESS2 : MAC Address2
 *           @arg ETH_MAC_ADDRESS3 : MAC Address3
 *
 * @retval None
 */
void ETH_DisableMACAddressPerfectFilter(ETH_MAC_ADDRESS_T macAddr)
{
    __IO uint32_t temp = 0;
    (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr)) &= (~BIT31);
    ETH_Delay(ETH_REG_WRITE_DELAY);
    (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr)) = temp;
}

/*!
 * @brief  Config the filter type for the MAC address
 *
 * @param  macAddr: The MAC address.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESS1 : MAC Address1
 *           @arg ETH_MAC_ADDRESS2 : MAC Address2
 *           @arg ETH_MAC_ADDRESS3 : MAC Address3
 *
 * @param  filter: Comparison with the SA/DA fields of the received frame.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESSFILTER_SA : MAC Address is used to compare with the
 *                                           SA fields of the received frame.
 *           @arg ETH_MAC_ADDRESSFILTER_DA : MAC Address is used to compare with the
 *                                           DA fields of the received frame.
 * @retval None
 */
void ETH_ConfigMACAddressFilter(ETH_MAC_ADDRESS_T macAddr, ETH_MAC_ADDRESSFILTER_T filter)
{
    if(filter == ETH_MAC_ADDRESSFILTER_SA)
    {
        (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr)) |= ETH_MAC_ADDRESSFILTER_SA;
    }
    else
    {
        (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr)) |= ETH_MAC_ADDRESSFILTER_DA;
    }

}

/*!
 * @brief  Config the filter type for the ETH MAC address.
 *
 * @param  macAddr: The MAC address.
 *         This parameter can be one of the following values:
 *           @arg ETH_MAC_ADDRESS1 : MAC Address1
 *           @arg ETH_MAC_ADDRESS2 : MAC Address2
 *           @arg ETH_MAC_ADDRESS3 : MAC Address3
 *
 * @param  MaskByte: specifies the used address bytes for comparison
 *         This parameter can be any combination of the following values:
 *           @arg ETH_MAC_ADDRESSMASK_BYTE6 : Mask MAC Address high reg bits [15:8].
 *           @arg ETH_MAC_ADDRESSMASK_BYTE5 : Mask MAC Address high reg bits [7:0].
 *           @arg ETH_MAC_ADDRESSMASK_BYTE4 : Mask MAC Address low reg bits [31:24].
 *           @arg ETH_MAC_ADDRESSMASK_BYTE3 : Mask MAC Address low reg bits [23:16].
 *           @arg ETH_MAC_ADDRESSMASK_BYTE2 : Mask MAC Address low reg bits [15:8].
 *           @arg ETH_MAC_ADDRESSMASK_BYTE1 : Mask MAC Address low reg bits [7:0].
 *
 * @retval None
 */
void ETH_ConfigMACAddressMaskBytesFilter(ETH_MAC_ADDRESS_T macAddr, uint32_t maskByte)
{
    __IO uint32_t temp = 0;

    (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr)) &=(~(uint32_t)0x3F000000);

    temp = (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr));
    ETH_Delay(ETH_REG_WRITE_DELAY);
    (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr)) = temp;

    /* Set the selected Filter mask bytes */
    (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr)) |= maskByte;

    temp = (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr));
    ETH_Delay(ETH_REG_WRITE_DELAY);
    (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + macAddr)) = temp;
}

/** DMA Descriptors functions */

/*!
 * @brief  Config the DMA Rx descriptors in chain mode.
 *
 * @param  DMARxDescTab: Pointer on the first Rx desc list
 *
 * @param  rxBuff: Pointer on the first RxBuffer list
 *
 * @param  rxBuffcount: Number of the used Rx desc in the list
 *
 * @retval None
 */
void ETH_ConfigDMARxDescChain(ETH_DMADescConfig_T *DMARxDescTab, uint8_t *rxBuff, uint32_t rxBuffcount)
{
    uint32_t i = 0;
    ETH_DMADescConfig_T *DMARxDesc;
    DMARxDescToGet = DMARxDescTab;

    for(i=0; i< rxBuffcount; i++)
    {
        DMARxDesc = DMARxDescTab+i;
        DMARxDesc->Status = ETH_DMARXDESC_OWN;
        DMARxDesc->ControlBufferSize = ETH_DMARXDESC_RXCH | ETH_RX_BUF_SIZE;
        DMARxDesc->Buffer1Addr = (uint32_t)(&rxBuff[i*ETH_RX_BUF_SIZE]);
        if(i < (rxBuffcount-1))
        {
            DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab+i+1);
        }
        else
        {
            DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab);
        }
    }


    ETH->DMARXDLADDR = (uint32_t) DMARxDescTab;
    DMARxFraminfos =&RxFrameDescriptor;
}

/*!
 * @brief  Initializes the DMA Tx descriptors in chain mode.
 *
 * @param  DMATxDescTab: Pointer on the first Tx desc list
 *
 * @param  txBuff: Pointer on the first TxBuffer list
 *
 * @param  txBuffcount: Number of the used Tx desc in the list
 *
 * @retval None
  */
void ETH_ConfigDMATxDescChain(ETH_DMADescConfig_T *DMATxDescTab, uint8_t* txBuff, uint32_t txBuffcount)
{
    uint32_t i = 0;
    ETH_DMADescConfig_T *DMATxDesc;
    DMATxDescToSet = DMATxDescTab;

    for(i=0; i< txBuffcount; i++)
    {
        DMATxDesc = DMATxDescTab+i;
        DMATxDesc->Status = ETH_DMATXDESC_TXCH;
        DMATxDesc->Buffer1Addr = (uint32_t)(&txBuff[i*ETH_TX_BUF_SIZE]);
        if(i < (txBuffcount-1))
        {
            DMATxDesc->Buffer2NextDescAddr = (uint32_t)(DMATxDescTab+i+1);
        }
        else
        {
            DMATxDesc->Buffer2NextDescAddr = (uint32_t)(DMATxDescTab);
        }
    }

    ETH->DMATXDLADDR = (uint32_t) DMATxDescTab;
}

/*!
 * @brief  This function polls for a frame receiver
 *
 * @param  None
 *
 * @retval Returns 1 when a frame is received, 0 if none.
 */
uint32_t ETH_CheckReceivedFrame(void)
{
    if(((DMARxDescToGet->Status & ETH_DMARXDESC_OWN) == (uint32_t)RESET) &&
        ((DMARxDescToGet->Status & ETH_DMARXDESC_LDES) != (uint32_t)RESET))
    {
        DMARxFraminfos->segCount++;
        if(DMARxFraminfos->segCount == 1)
        {
            DMARxFraminfos->FS_RxDesc = DMARxDescToGet;
        }
        DMARxFraminfos->LS_RxDesc = DMARxDescToGet;
        return 1;
    }
    else if(((DMARxDescToGet->Status & ETH_DMARXDESC_OWN) == (uint32_t)RESET) &&
             ((DMARxDescToGet->Status & ETH_DMARXDESC_FDES) != (uint32_t)RESET) &&
             ((DMARxDescToGet->Status & ETH_DMARXDESC_LDES) == (uint32_t)RESET))
    {
        DMARxFraminfos->FS_RxDesc = DMARxDescToGet;
        DMARxFraminfos->LS_RxDesc = NULL;
        DMARxFraminfos->segCount  = 1;
        DMARxDescToGet = (ETH_DMADescConfig_T*) (DMARxDescToGet->Buffer2NextDescAddr);
    }
    else if(((DMARxDescToGet->Status & ETH_DMARXDESC_OWN) == (uint32_t)RESET) &&
             ((DMARxDescToGet->Status & ETH_DMARXDESC_FDES) == (uint32_t)RESET) &&
             ((DMARxDescToGet->Status & ETH_DMARXDESC_LDES) == (uint32_t)RESET))
    {
        (DMARxFraminfos->segCount) ++;
        DMARxDescToGet = (ETH_DMADescConfig_T*) (DMARxDescToGet->Buffer2NextDescAddr);
    }
    return 0;
}

/*!
 * @brief  Prepares DMA Tx descriptors to transmit an ethernet frame
 *
 * @param  FrameLength : length of the frame to send
 *
 * @retval ETH_ERROR or ETH_SUCCESS
 */
uint32_t ETH_Transmit_Descriptors(u16 frameLength)
{
    uint32_t count=0, size=0, i=0;
    __IO ETH_DMADescConfig_T  *DMATxDesc;

    if((DMATxDescToSet->Status & ETH_DMATXDESC_OWN) == SET)
    {
        return ETH_ERROR;
    }

    DMATxDesc = DMATxDescToSet;

    if(frameLength > ETH_TX_BUF_SIZE)
    {
        count = frameLength/ETH_TX_BUF_SIZE;
        if(frameLength%ETH_TX_BUF_SIZE) count++;
    }
    else count =1;

    if(count == 1)
    {
        DMATxDesc->Status |= ETH_DMATXDESC_FS | ETH_DMATXDESC_LS;
        DMATxDesc->ControlBufferSize = (frameLength & ETH_DMATXDESC_TXBS1);
        DMATxDesc->Status |= ETH_DMATXDESC_OWN;
        DMATxDesc = (ETH_DMADescConfig_T*) (DMATxDesc->Buffer2NextDescAddr);
    }
    else
    {
        for(i=0; i<count; i++)
        {
            DMATxDesc->Status &= ~(ETH_DMATXDESC_FS | ETH_DMATXDESC_LS);

            if(i==0)
            {
                DMATxDesc->Status |= ETH_DMATXDESC_FS;
            }
            DMATxDesc->ControlBufferSize =(ETH_TX_BUF_SIZE & ETH_DMATXDESC_TXBS1);

            if(i== (count-1))
            {
                DMATxDesc->Status |= ETH_DMATXDESC_LS;
                size = frameLength - (count-1)*ETH_TX_BUF_SIZE;
                DMATxDesc->ControlBufferSize =(size & ETH_DMATXDESC_TXBS1);
            }

            DMATxDesc->Status |= ETH_DMATXDESC_OWN;
            DMATxDesc = (ETH_DMADescConfig_T*) (DMATxDesc->Buffer2NextDescAddr);
        }
    }
    DMATxDescToSet = DMATxDesc;

    if(ETH->DMASTS_B.TXBU == SET)
    {
        ETH->DMASTS = BIT2;
        ETH->DMATXPD = 0;
    }

    return ETH_SUCCESS;
}

/*!
 * @brief  Read the received frame.
 *
 * @param  none
 *
 * @retval Structure of type ETH_Frame_T
 */
ETH_Frame_T ETH_ReadReceivedFrame(void)
{
    uint32_t frameLength = 0;
    ETH_Frame_T frame = {0,0,0};

    frameLength = ((DMARxDescToGet->Status & ETH_DMARXDESC_FL) >> ETH_DMARXDESC_FRAMELENGTHSHIFT) - 4;
    frame.length = frameLength;

    frame.descriptor = DMARxFraminfos->FS_RxDesc;
    frame.buffer = (DMARxFraminfos->FS_RxDesc)->Buffer1Addr;
    DMARxDescToGet = (ETH_DMADescConfig_T*) (DMARxDescToGet->Buffer2NextDescAddr);

    return(frame);
}

/*!
 * @brief  Read ETH DMA Tx Descriptor flag.
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @param  flag: Specifies the flag to check.
 *         This parameter can be one of the following values:
 *           @arg ETH_DMATXDESC_OWN   : Descriptor is owned by DMA engine
 *           @arg ETH_DMATXDESC_INTC  : Interrupt on completion
 *           @arg ETH_DMATXDESC_LS    : Last Segment
 *           @arg ETH_DMATXDESC_FS    : First Segment
 *           @arg ETH_DMATXDESC_DISC  : Disable CRC
 *           @arg ETH_DMATXDESC_DISP  : Disable Pad
 *           @arg ETH_DMATXDESC_TXTSEN: Transmit Time Stamp Enable
 *           @arg ETH_DMATXDESC_TXENDR: Transmit End of Ring
 *           @arg ETH_DMATXDESC_TXCH  : Second Address Chained
 *           @arg ETH_DMATXDESC_TXTSS : Tx Time Stamp Status
 *           @arg ETH_DMATXDESC_IHERR : IP Header Error
 *           @arg ETH_DMATXDESC_ERRS  : Error summary
 *           @arg ETH_DMATXDESC_JTO   : Jabber Timeout
 *           @arg ETH_DMATXDESC_FF    : Frame Flushed: DMA/MTL flushed the frame due to SW flush
 *           @arg ETH_DMATXDESC_IPERR : Payload Checksum Error
 *           @arg ETH_DMATXDESC_LSC   : Loss of Carrier: carrier lost during transmission
 *           @arg ETH_DMATXDESC_NC    : No Carrier: no carrier signal from the transceiver
 *           @arg ETH_DMATXDESC_LC    : Late Collision: transmission aborted due to collision
 *           @arg ETH_DMATXDESC_EC    : Excessive Collision: transmission aborted after 16 collisions
 *           @arg ETH_DMATXDESC_VLANF : VLAN Frame
 *           @arg ETH_DMATXDESC_CCNT  : Collision Count
 *           @arg ETH_DMATXDESC_EDEF  : Excessive Deferral
 *           @arg ETH_DMATXDESC_UFERR : Underflow Error: late data arrival from the memory
 *           @arg ETH_DMATXDESC_DEF   : Deferred Bit
 *
 * @retval SET or RESET.
 */
uint8_t ETH_ReadDMATxDescFlagStatus(ETH_DMADescConfig_T *DMATxDesc, ETH_DMATXDESC_FLAG_T flag)
{
    return (DMATxDesc->Status & flag) ? SET : RESET;
}

/*!
 * @brief  Returns ETH DMA Tx Descriptor collision count.
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @retval The Transmit descriptor collision counter value.
 */
uint32_t ETH_ReadDMATxDescCollisionCount(ETH_DMADescConfig_T *DMATxDesc)
{
    return ((DMATxDesc->Status & ETH_DMATXDESC_CCNT) >> ETH_DMATXDESC_COLLISION_COUNTSHIFT);
}

/*!
 * @brief  Config the ETH DMA Tx Descriptor Own bit.
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @retval None
 */
void ETH_ConfigDMATxDescOwnBit(ETH_DMADescConfig_T *DMATxDesc)
{
    DMATxDesc->Status |= ETH_DMATXDESC_OWN;
}

/*!
 * @brief  Enable the ETH DMA Tx Descriptor Transmit interrupt.
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @retval None
 */
void ETH_EnableDMATxDescTransmitInterrupt(ETH_DMADescConfig_T *DMATxDesc)
{
    DMATxDesc->Status |= ETH_DMATXDESC_INTC;
}

/*!
 * @brief  Disable the ETH DMA Tx Descriptor Transmit interrupt.
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @retval None
 */
void ETH_DisableDMATxDescTransmitInterrupt(ETH_DMADescConfig_T *DMATxDesc)
{
    DMATxDesc->Status &= (~(uint32_t)ETH_DMATXDESC_INTC);
}

/*!
 * @brief  Config Tx descriptor as last or first segment
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @param  frameSegment: Tx desc contain last or first segment.
 *         This parameter can be one of the following values:
 *           @arg ETH_DMATXDESC_LASTSEGMENTS : Actual Tx desc contain last segment
 *           @arg ETH_DMATXDESC_FIRSTSEGMENT : Actual Tx desc contain first segment
 *
 * @retval None
 */
void ETH_ConfigDMATxDescFrameSegment(ETH_DMADescConfig_T *DMATxDesc, ETH_DMATXDESC_SEGMENTS_T frameSegment)
{
    DMATxDesc->Status |= frameSegment;
}
/*!
 * @brief  Config ETH DMA Tx Desc Checksum Insertion.
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @param  checksum: specifies is the DMA Tx desc checksum insertion.
 *         This parameter can be one of the following values:
 *           @arg ETH_DMATXDESC_CHECKSUMBYPASS              : Checksum bypass
 *           @arg ETH_DMATXDESC_CHECKSUMIPV4HEADER          : IPv4 header checksum
 *           @arg ETH_DMATXDESC_CHECKSUMTCPUDPICMPSEGMENT   : TCP/UDP/ICMP checksum. Pseudo header checksum is assumed to be present
 *           @arg ETH_DMATXDESC_CHECKSUMTCPUDPICMPFULL      : TCP/UDP/ICMP checksum fully in hardware including pseudo header
 *
 * @retval None
 */
void ETH_ConfigDMATxDescChecksumInsertion(ETH_DMADescConfig_T *DMATxDesc, ETH_DMATXDESC_CHECKSUMB_T checksum)
{
    DMATxDesc->Status |= checksum;
}

/*!
 * @brief  Enable the DMA Tx Desc CRC.
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @retval None
 */
void ETH_EnableDMATxDescCRC(ETH_DMADescConfig_T *DMATxDesc)
{
    DMATxDesc->Status &= (~(uint32_t)ETH_DMATXDESC_DISC);
}

/*!
 * @brief  Disable the DMA Tx Desc CRC.
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @retval None
 */
void ETH_DisableDMATxDescCRC(ETH_DMADescConfig_T *DMATxDesc)
{
    DMATxDesc->Status |= ETH_DMATXDESC_DISC;
}

/*!
 * @brief  Enable the DMA Tx Desc second address chained.
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @retval None
 */
void ETH_EnableDMATxDescSecondAddressChained(ETH_DMADescConfig_T *DMATxDesc)
{
    DMATxDesc->Status |= ETH_DMATXDESC_TXCH;
}

/*!
 * @brief  Disable the DMA Tx Desc second address chained.
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @retval None
 */
void ETH_DisableDMATxDescSecondAddressChained(ETH_DMADescConfig_T *DMATxDesc)
{
    DMATxDesc->Status &=(~(uint32_t)ETH_DMATXDESC_TXCH);
}

/*!
 * @brief  Enable the DMA Tx Desc padding for frame shorter than 64 bytes.
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @retval None
 */
void ETH_EnableDMATxDescShortFramePadding(ETH_DMADescConfig_T *DMATxDesc)
{
    DMATxDesc->Status &= (~(uint32_t)ETH_DMATXDESC_DISP);
}

/*!
 * @brief  Disable the DMA Tx Desc padding for frame shorter than 64 bytes.
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @retval None
 */
void ETH_DisableDMATxDescShortFramePadding(ETH_DMADescConfig_T *DMATxDesc)
{
    DMATxDesc->Status |= ETH_DMATXDESC_DISP;
}

/*!
 * @brief  Config the ETH DMA Tx Desc buffer1 and buffer2 sizes.
 *
 * @param  DMATxDesc: pointer on a DMA Tx descriptor
 *
 * @param  bufferSize1: specifies the Tx desc buffer1 size.
 *
 * @param  bufferSize2: specifies the Tx desc buffer2 size.
 *
 * @retval None
 */
void ETH_ConfigDMATxDescBufferSize(ETH_DMADescConfig_T *DMATxDesc, uint32_t bufferSize1, uint32_t bufferSize2)
{
    DMATxDesc->ControlBufferSize |= (bufferSize1 | (bufferSize2 << ETH_DMATXDESC_BUFFER2_SIZESHIFT));
}

/*!
 * @brief  Checks whether the specified ETHERNET Rx Desc flag is set or not.
 *
 * @param  DMARxDesc: pointer on a DMA Rx descriptor

 * @param  flag: specifies the flag to check.
 *         This parameter can be one of the following values:
 *           @arg ETH_DMARXDESC_OWN    :    Descriptor is owned by DMA engine
 *           @arg ETH_DMARXDESC_ADDRF  :    DA Filter Fail for the rx frame
 *           @arg ETH_DMARXDESC_ERRS   :    Error summary
 *           @arg ETH_DMARXDESC_DESERR :    Descriptor error: no more descriptors for receive frame
 *           @arg ETH_DMARXDESC_SADDRF :    SA Filter Fail for the received frame
 *           @arg ETH_DMARXDESC_LERR   :    Frame size not matching with length field
 *           @arg ETH_DMARXDESC_OFERR  :    Overflow Error: Frame was damaged due to buffer overflow
 *           @arg ETH_DMARXDESC_VLANF  :    VLAN Tag: received frame is a VLAN frame
 *           @arg ETH_DMARXDESC_FDES   :    First descriptor of the frame
 *           @arg ETH_DMARXDESC_LDES   :    Last descriptor of the frame
 *           @arg ETH_DMARXDESC_IPV4HCE:    IPC Checksum Error/Giant Frame: Rx Ipv4 header checksum error
 *           @arg ETH_DMARXDESC_LC     :    Late collision occurred during reception
 *           @arg ETH_DMARXDESC_FT     :    Frame type - Ethernet, otherwise 802.3
 *           @arg ETH_DMARXDESC_RXWDTTO:    Receive Watchdog Timeout: watchdog timer expired during reception
 *           @arg ETH_DMARXDESC_RERR   :    Receive error: error reported by MII interface
 *           @arg ETH_DMARXDESC_DERR   :    Dribble bit error: frame contains non int multiple of 8 bits
 *           @arg ETH_DMARXDESC_CERR   :    CRC error
 *           @arg ETH_DMARXDESC_MAMPCE :    Rx MAC Address/Payload Checksum Error: Rx MAC address matched/ Rx Payload Checksum Error
 *
 * @retval SET or RESET.
 */
uint8_t ETH_ReadDMARxDescFlagStatus(ETH_DMADescConfig_T *DMARxDesc, ETH_DMARXDESC_FLAG_T flag)
{
    return (DMARxDesc->Status & flag) ? SET : RESET;
}

#if USE_ENHANCED_DMA_DESCRIPTORS
/*!
 * @brief  Checks whether the specified ETHERNET PTP Rx Desc extended flag is set or not.
 *
 * @param  DMAPTPRxDesc: pointer on a DMA PTP Rx descriptor
 *
 * @param  flag: specifies the extended flag to check.
 *         This parameter can be one of the following values:
 *           @arg ETH_DMAPTPRXDESC_PTPV  :  PTP version
 *           @arg ETH_DMAPTPRXDESC_PTPFT :  PTP frame type
 *           @arg ETH_DMAPTPRXDESC_PTPMT :  PTP message type
 *           @arg ETH_DMAPTPRXDESC_IPV6P :  IPv6 packet received
 *           @arg ETH_DMAPTPRXDESC_IPV4P :  IPv4 packet received
 *           @arg ETH_DMAPTPRXDESC_IPCBP :  IP checksum bypassed
 *           @arg ETH_DMAPTPRXDESC_IPPERR:  IP payload error
 *           @arg ETH_DMAPTPRXDESC_IPHERR:  IP header error
 *           @arg ETH_DMAPTPRXDESC_IPPT  :  IP payload type
 *
 * @retval SET or RESET.
 */
uint8_t ETH_ReadDMAPTPRxDescExtendedFlagStatus(ETH_DMADescConfig_T *DMAPTPRxDesc, ETH_DMAPTPRXDESC_FLAG_T flag)
{
    return (DMAPTPRxDesc->Status & flag) ? SET : RESET;
}
#endif

/*!
 * @brief  Config the ETH DMA Rx Desc Own bit.
 *
 * @param  DMARxDesc: pointer on a DMA Rx descriptor
 *
 * @retval None
 */
void ETH_ConfigDMARxDescOwnBit(ETH_DMADescConfig_T *DMARxDesc)
{
    DMARxDesc->Status |= ETH_DMARXDESC_OWN;
}

/*!
 * @brief  Returns the ETH DMA Rx descriptor frame length.
 *
 * @param  DMARxDesc: pointer on a DMA Rx descriptor
 *
 * @retval The Rx descriptor received frame length.
 */
uint32_t ETH_ReadDMARxDescFrameLength(ETH_DMADescConfig_T *DMARxDesc)
{
    return ((DMARxDesc->Status & ETH_DMARXDESC_FL) >> ETH_DMARXDESC_FRAME_LENGTHSHIFT);
}

/*!
 * @brief  Enable the ETH DMA Rx Desc receive interrupt.
 *
 * @param  DMARxDesc: pointer on a DMA Rx descriptor
 *
 * @retval None
 */
void ETH_EnableDMARxDescReceiveInterrupt(ETH_DMADescConfig_T *DMARxDesc)
{
    DMARxDesc->ControlBufferSize &=(~(uint32_t)ETH_DMARXDESC_DINTC);
}

/*!
 * @brief  Disable the ETH DMA Rx Desc receive interrupt.
 *
 * @param  DMARxDesc: pointer on a DMA Rx descriptor
 *
 * @retval None
 */
void ETH_DisableDMARxDescReceiveInterrupt(ETH_DMADescConfig_T *DMARxDesc)
{
    DMARxDesc->ControlBufferSize |= ETH_DMARXDESC_DINTC;
}

/*!
 * @brief  Returns the ETH DMA Rx Desc buffer size.
 *
 * @param  DMARxDesc: pointer on a DMA Rx descriptor
 *
 * @param  buffer: specifies the DMA Rx Desc buffer.
 *         This parameter can be one of the following values:
 *           @arg ETH_DMARxDesc_Buffer1 : DMA Rx Desc Buffer1
 *           @arg ETH_DMARxDesc_Buffer2 : DMA Rx Desc Buffer2
 *
 * @retval The Receive descriptor frame length.
 */
uint32_t ETH_ReadDMARxDescBufferSize(ETH_DMADescConfig_T *DMARxDesc, ETH_DMARXDESC_BUFFER_T buffer)
{
    if(buffer == ETH_DMARXDESC_BUFFER1)
    {
        return (DMARxDesc->ControlBufferSize & ETH_DMARXDESC_RXBS1);
    }
    else
    {
        return ((DMARxDesc->ControlBufferSize & ETH_DMARXDESC_RXBS2) >> ETH_DMARXDESC_BUFFER2_SIZESHIFT);
    }
}

/*!
 * @brief  Read frame using DMA Receive interrupt.
 *         it allows scanning of Rx descriptors to get the the receive frame
 *
 * @param  None
 *
 * @retval Structure of type ETH_Frame_T
 */
ETH_Frame_T ETH_ReadReceivedFrameInterrupt(void)
{
    __IO uint32_t count = 0;
    ETH_Frame_T frame = {0,0,0};

    while (((DMARxDescToGet->Status & ETH_DMARXDESC_OWN) == (uint32_t)RESET)&& (count < ETH_RXBUFNB))
    {
        count ++;

        if(((DMARxDescToGet->Status & ETH_DMARXDESC_FDES) != (uint32_t)RESET)&&
        ((DMARxDescToGet->Status & ETH_DMARXDESC_LDES) == (uint32_t)RESET))
        {
            DMARxFraminfos->FS_RxDesc = DMARxDescToGet;
            DMARxFraminfos->segCount = 1;
            DMARxDescToGet = (ETH_DMADescConfig_T*) (DMARxDescToGet->Buffer2NextDescAddr);
        }
        else if (((DMARxDescToGet->Status & ETH_DMARXDESC_FDES) == (uint32_t)RESET)&&
                ((DMARxDescToGet->Status & ETH_DMARXDESC_LDES) == (uint32_t)RESET))
        {
            (DMARxFraminfos->segCount) ++;
            DMARxDescToGet = (ETH_DMADescConfig_T*) (DMARxDescToGet->Buffer2NextDescAddr);
        }
        else
        {
            DMARxFraminfos->LS_RxDesc = DMARxDescToGet;
            (DMARxFraminfos->segCount)++;

            if ((DMARxFraminfos->segCount)==1)
            DMARxFraminfos->FS_RxDesc = DMARxDescToGet;

            frame.length = ((DMARxDescToGet->Status & ETH_DMARXDESC_FL) >> ETH_DMARXDESC_FRAMELENGTHSHIFT) - 4;

            if(DMARxFraminfos->segCount >1)
            {
                frame.buffer = (DMARxFraminfos->FS_RxDesc)->Buffer1Addr;
            }
            else
            {
                frame.buffer = DMARxDescToGet->Buffer1Addr;
            }

            frame.descriptor = DMARxFraminfos->FS_RxDesc;
            DMARxDescToGet = (ETH_DMADescConfig_T*) (DMARxDescToGet->Buffer2NextDescAddr);

            return (frame);
        }
    }
    return (frame);
}

/** DMA functions */

/*!
 * @brief  Read the ETH DMA flag.
 *
 * @param  flag: specifies the flag to check.
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_FLAG_TST                  : Time-stamp trigger flag
 *           @arg ETH_DMA_FLAG_PMT                  : PMT flag
 *           @arg ETH_DMA_FLAG_MMC                  : MMC flag
 *           @arg ETH_DMA_FLAG_DATATRANSFERERROR    : Error bits 0-data buffer, 1-desc. access
 *           @arg ETH_DMA_FLAG_READWRITEERROR       : Error bits 0-write trnsf, 1-read transfr
 *           @arg ETH_DMA_FLAG_ACCESSERROR          : Error bits 0-Rx DMA, 1-Tx DMA
 *           @arg ETH_DMA_FLAG_NIS                  : Normal interrupt summary flag
 *           @arg ETH_DMA_FLAG_AIS                  : Abnormal interrupt summary flag
 *           @arg ETH_DMA_FLAG_ER                   : Early receive flag
 *           @arg ETH_DMA_FLAG_FBE                  : Fatal bus error flag
 *           @arg ETH_DMA_FLAG_ET                   : Early transmit flag
 *           @arg ETH_DMA_FLAG_RWT                  : Receive watchdog timeout flag
 *           @arg ETH_DMA_FLAG_RPS                  : Receive process stopped flag
 *           @arg ETH_DMA_FLAG_RBU                  : Receive buffer unavailable flag
 *           @arg ETH_DMA_FLAG_RX                   : Receive flag
 *           @arg ETH_DMA_FLAG_TU                   : Underflow flag
 *           @arg ETH_DMA_FLAG_RO                   : Overflow flag
 *           @arg ETH_DMA_FLAG_TJT                  : Transmit jabber timeout flag
 *           @arg ETH_DMA_FLAG_TBU                  : Transmit buffer unavailable flag
 *           @arg ETH_DMA_FLAG_TPS                  : Transmit process stopped flag
 *           @arg ETH_DMA_FLAG_TX                   : Transmit flag
 *
 * @retval SET or RESET.
 */
uint8_t ETH_ReadDMAFlagStatus(ETH_DMA_FLAG_T flag)
{
    return (ETH->DMASTS & flag) ? SET : RESET;
}

/*!
 * @brief  Clears the ETH DMA flag.
 *
 * @param  flag: specifies the flag to clear.
 *         This parameter can be any combination of the following values:
 *           @arg ETH_DMA_FLAG_NIS : Normal interrupt summary flag
 *           @arg ETH_DMA_FLAG_AIS : Abnormal interrupt summary flag
 *           @arg ETH_DMA_FLAG_ER  : Early receive flag
 *           @arg ETH_DMA_FLAG_FBE : Fatal bus error flag
 *           @arg ETH_DMA_FLAG_ET  : Early transmit flag
 *           @arg ETH_DMA_FLAG_RWT : Receive watchdog timeout flag
 *           @arg ETH_DMA_FLAG_RPS : Receive process stopped flag
 *           @arg ETH_DMA_FLAG_RBU : Receive buffer unavailable flag
 *           @arg ETH_DMA_FLAG_RX  : Receive flag
 *           @arg ETH_DMA_FLAG_TU  : Transmit Underflow flag
 *           @arg ETH_DMA_FLAG_RO  : Receive Overflow flag
 *           @arg ETH_DMA_FLAG_TJT : Transmit jabber timeout flag
 *           @arg ETH_DMA_FLAG_TBU : Transmit buffer unavailable flag
 *           @arg ETH_DMA_FLAG_TPS : Transmit process stopped flag
 *           @arg ETH_DMA_FLAG_TX  : Transmit flag
 *
 * @retval None
 */
void ETH_ClearDMAFlag(uint32_t flag)
{
    ETH->DMASTS = flag;
}

/*!
 * @brief  Read the ETH DMA interrupt flag.
 *
 * @param  flag: specifies the interrupt source to check.
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_INT_TST : Time-stamp trigger interrupt
 *           @arg ETH_DMA_INT_PMT : PMT interrupt
 *           @arg ETH_DMA_INT_MMC : MMC interrupt
 *           @arg ETH_DMA_INT_NIS : Normal interrupt summary
 *           @arg ETH_DMA_INT_AIS : Abnormal interrupt summary
 *           @arg ETH_DMA_INT_ER  : Early receive interrupt
 *           @arg ETH_DMA_INT_FBE : Fatal bus error interrupt
 *           @arg ETH_DMA_INT_ET  : Early transmit interrupt
 *           @arg ETH_DMA_INT_RWT : Receive watchdog timeout interrupt
 *           @arg ETH_DMA_INT_RPS : Receive process stopped interrupt
 *           @arg ETH_DMA_INT_RBU : Receive buffer unavailable interrupt
 *           @arg ETH_DMA_INT_RX  : Receive interrupt
 *           @arg ETH_DMA_INT_TU  : Underflow interrupt
 *           @arg ETH_DMA_INT_RO  : Overflow interrupt
 *           @arg ETH_DMA_INT_TJT : Transmit jabber timeout interrupt
 *           @arg ETH_DMA_INT_TBU : Transmit buffer unavailable interrupt
 *           @arg ETH_DMA_INT_TPS : Transmit process stopped interrupt
 *           @arg ETH_DMA_INT_TX  : Transmit interrupt
 *
 * @retval SET or RESET.
 */
uint8_t ETH_ReadDMAIntFlag(ETH_DMA_INT_T flag)
{
    return (ETH->DMASTS & flag) ? SET : RESET;
}

/*!
 * @brief  Clears the ETH DMA interrupt flag.
 *
 * @param  flag: specifies the interrupt flag to clear.
 *         This parameter can be any combination of the following values:
 *           @arg ETH_DMA_INT_NIS : Normal interrupt summary
 *           @arg ETH_DMA_INT_AIS : Abnormal interrupt summary
 *           @arg ETH_DMA_INT_ER  : Early receive interrupt
 *           @arg ETH_DMA_INT_FBE : Fatal bus error interrupt
 *           @arg ETH_DMA_INT_ET  : Early transmit interrupt
 *           @arg ETH_DMA_INT_RWT : Receive watchdog timeout interrupt
 *           @arg ETH_DMA_INT_RPS : Receive process stopped interrupt
 *           @arg ETH_DMA_INT_RBU : Receive buffer unavailable interrupt
 *           @arg ETH_DMA_INT_RX  : Receive interrupt
 *           @arg ETH_DMA_INT_TU  : Transmit Underflow interrupt
 *           @arg ETH_DMA_INT_RO  : Receive Overflow interrupt
 *           @arg ETH_DMA_INT_TJT : Transmit jabber timeout interrupt
 *           @arg ETH_DMA_INT_TBU : Transmit buffer unavailable interrupt
 *           @arg ETH_DMA_INT_TPS : Transmit process stopped interrupt
 *           @arg ETH_DMA_INT_TX  : Transmit interrupt
 *
 * @retval None
 */
void ETH_ClearDMAIntFlag(uint32_t flag)
{
    ETH->DMASTS = flag;
}

/*!
 * @brief  Returns the ETH DMA Transmit Process State.
 *
 * @param  None

 * @retval The new ETH DMA Transmit Process State:
 *         This can be one of the following values:
 *           - ETH_DMA_TRANSMITPROCESS_STOPPED   : Stopped - Reset or Stop Tx Command issued
 *           - ETH_DMA_TRANSMITPROCESS_FETCHING  : Running - fetching the Tx descriptor
 *           - ETH_DMA_TRANSMITPROCESS_WAITING   : Running - waiting for status
 *           - ETH_DMA_TRANSMITPROCESS_READING   : Running - reading the data from host memory
 *           - ETH_DMA_TRANSMITPROCESS_SUSPENDED : Suspended - Tx Descriptor unavailable
 *           - ETH_DMA_TRANSMITPROCESS_CLOSING   : Running - closing Rx descriptor
 */
uint32_t ETH_ReadTransmitProcessState(void)
{
    return ((uint32_t)(ETH->DMASTS & BIT0) ? SET : RESET);
}

/*!
 * @brief  Returns the ETH DMA Receive Process State.
 *
 * @param  None
 *
 * @retval The new ETH DMA Receive Process State:
 *         This can be one of the following values:
 *           - ETH_DMA_RECEIVEPROCESS_STOPPED   : Stopped - Reset or Stop Rx Command issued
 *           - ETH_DMA_RECEIVEPROCESS_FETCHING  : Running - fetching the Rx descriptor
 *           - ETH_DMA_RECEIVEPROCESS_WAITING   : Running - waiting for packet
 *           - ETH_DMA_RECEIVEPROCESS_SUSPENDED : Suspended - Rx Descriptor unavailable
 *           - ETH_DMA_RECEIVEPROCESS_CLOSING   : Running - closing descriptor
 *           - ETH_DMA_RECEIVEPROCESS_QUEUING   : Running - queuing the receive frame into host memory
 */
uint32_t ETH_ReadReceiveProcessState(void)
{
    return ((uint32_t)(ETH->DMASTS & BIT6) ? SET : RESET);
}

/*!
 * @brief  Flush the ETH transmit FIFO.
 *
 * @param  None
 *
 * @retval None
  */
void ETH_FlushTransmitFIFO(void)
{
    ETH->DMAOPMOD_B.FTXF = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Read the ETH flush transmit FIFO status.
 *
 * @param  None
 *
 * @retval SET or RESET.
 */
uint8_t ETH_ReadFlushTransmitFIFOStatus(void)
{
    return ETH->DMAOPMOD_B.FTXF;
}

/*!
 * @brief  Enable the DMA transmission.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_EnableDMATransmission(void)
{
    ETH->DMAOPMOD_B.STTX = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Disable the DMA transmission.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_DisableDMATransmission(void)
{
    ETH->DMAOPMOD_B.STTX = RESET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Enable the DMA receiver.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_EnableDMAReceiver(void)
{
    ETH->DMAOPMOD_B.STRX = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Disable the DMA receiver.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_DisableDMAReceiver(void)
{
    ETH->DMAOPMOD_B.STRX = RESET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Enable the ETH DMA interrupts.
 *
 * @param  interrupt: specifies the ETH DMA interrupt sources.
 *         This parameter can be any combination of the following values:
 *           @arg ETH_DMA_INT_NIS : Normal interrupt summary
 *           @arg ETH_DMA_INT_AIS : Abnormal interrupt summary
 *           @arg ETH_DMA_INT_ER  : Early receive interrupt
 *           @arg ETH_DMA_INT_FBE : Fatal bus error interrupt
 *           @arg ETH_DMA_INT_ET  : Early transmit interrupt
 *           @arg ETH_DMA_INT_RWT : Receive watchdog timeout interrupt
 *           @arg ETH_DMA_INT_RPS : Receive process stopped interrupt
 *           @arg ETH_DMA_INT_RBU : Receive buffer unavailable interrupt
 *           @arg ETH_DMA_INT_RX  : Receive interrupt
 *           @arg ETH_DMA_INT_TU  : Underflow interrupt
 *           @arg ETH_DMA_INT_RO  : Overflow interrupt
 *           @arg ETH_DMA_INT_TJT : Transmit jabber timeout interrupt
 *           @arg ETH_DMA_INT_TBU : Transmit buffer unavailable interrupt
 *           @arg ETH_DMA_INT_TPS : Transmit process stopped interrupt
 *           @arg ETH_DMA_INT_TX  : Transmit interrupt
 *
 * @retval None
 */
void ETH_EnableDMAInterrupt(uint32_t interrupt)
{
    ETH->DMAINTEN |= interrupt;
}

/*!
 * @brief  Disable the ETH DMA interrupts.
 *
 * @param  interrupt: specifies the ETH DMA interrupt sources.
 *         This parameter can be any combination of the following values:
 *           @arg ETH_DMA_INT_NIS : Normal interrupt summary
 *           @arg ETH_DMA_INT_AIS : Abnormal interrupt summary
 *           @arg ETH_DMA_INT_ER  : Early receive interrupt
 *           @arg ETH_DMA_INT_FBE : Fatal bus error interrupt
 *           @arg ETH_DMA_INT_ET  : Early transmit interrupt
 *           @arg ETH_DMA_INT_RWT : Receive watchdog timeout interrupt
 *           @arg ETH_DMA_INT_RPS : Receive process stopped interrupt
 *           @arg ETH_DMA_INT_RBU : Receive buffer unavailable interrupt
 *           @arg ETH_DMA_INT_RX  : Receive interrupt
 *           @arg ETH_DMA_INT_TU  : Underflow interrupt
 *           @arg ETH_DMA_INT_RO  : Overflow interrupt
 *           @arg ETH_DMA_INT_TJT : Transmit jabber timeout interrupt
 *           @arg ETH_DMA_INT_TBU : Transmit buffer unavailable interrupt
 *           @arg ETH_DMA_INT_TPS : Transmit process stopped interrupt
 *           @arg ETH_DMA_INT_TX  : Transmit interrupt
 *
 * @retval None
 */
void ETH_DisableDMAInterrupt(uint32_t interrupt)
{
    ETH->DMAINTEN &= ((uint32_t)~interrupt);
}

/*!
 * @brief  Read the ETH DMA overflow flag.
 *
 * @param  overflow: specifies the DMA overflow flag to check.
 *         This parameter can be one of the following values:
 *           @arg ETH_DMA_OVERFLOW_RXFIFOCOUNTER        : Overflow for FIFO Overflows Counter
 *           @arg ETH_DMA_OVERFLOW_MISSEDFRAMECOUNTER   : Overflow for Buffer Unavailable Missed Frame Counter
 *
 * @retval SET or RESET.
 */
uint8_t ETH_ReadDMAOverflowStatus(ETH_DMA_OVERFLOW_T overflow)
{
    return (ETH->DMAMFABOCNT & overflow) ? SET : RESET;
}

/*!
 * @brief  Read the ETH DMA Rx Overflow Missed Frame Counter value.
 *
 * @param  None
 *
 * @retval The value of Rx overflow Missed Frame Counter.
 */
uint32_t ETH_ReadRxOverflowMissedFrameCounter(void)
{
    return (uint32_t)(ETH->DMAMFABOCNT_B.AMISFCNT);
}

/*!
 * @brief  Read the ETH DMA Buffer Unavailable Missed Frame Counter value.
 *
 * @param  None
 *
 * @retval The value of Buffer unavailable Missed Frame Counter.
 */
uint32_t ETH_ReadBufferUnavailableMissedFrameCounter(void)
{
    return (uint32_t)(ETH->DMAMFABOCNT_B.MISFCNT);
}

/*!
 * @brief  Read the ETH DMA DMAHTXD register value.
 *
 * @param  None
 *
 * @retval The value of the current Tx desc start address.
 */
uint32_t ETH_ReadCurrentTxDescStartAddress(void)
{
    return ((uint32_t)(ETH->DMAHTXD));
}

/*!
 * @brief  Read the ETHERNET DMA DMAHRXD register value.
 *
 * @param  None
 *
 * @retval The value of the current Rx desc start address.
 */
uint32_t ETH_ReadCurrentRxDescStartAddress(void)
{
    return ((uint32_t)(ETH->DMAHRXD));
}

/*!
 * @brief  Read the ETH DMA DMAHTXBADDR register value.
 *
 * @param  None
 *
 * @retval The value of the current transmit descriptor data buffer address.
 */
uint32_t ETH_ReadCurrentTxBufferAddress(void)
{
    return ((uint32_t)(ETH->DMAHTXBADDR));
}

/*!
 * @brief  Read the ETH DMA DMAHRXBADDR register value.
 *
 * @param  None
 *
 * @retval The value of the current receive descriptor data buffer address.
 */
uint32_t ETH_ReadCurrentRxBufferAddress(void)
{
    return ((uint32_t)(ETH->DMAHRXBADDR));
}

/*!
 * @brief  Reset the DMA Transmission by writing to the DmaTxPollDemand register
 *
 * @param  None

 * @retval None.
 */
void ETH_ResetDMATransmission(void)
{
    ETH->DMATXPD = 0;
}

/*!
 * @brief  Reset the DMA Transmission by writing to the DmaRxPollDemand register
 *
 * @param  None
 *
 * @retval None.
 */
void ETH_ResetDMAReception(void)
{
    ETH->DMARXPD = 0;
}

/*!
 * @brief  Config the DMA Receive status watchdog timer register value
 *
 * @param  value: watchdog timer register value
 *
 * @retval None
 */
void ETH_ConfigReceiveWatchdogTimer(uint8_t value)
{
    ETH->DMARXFLGWDT_B.RXWDTCNT = value;
}

/** Power Management(PMT) functions */

/*!
 * @brief  Reset Wakeup frame filter register pointer.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_ResetWakeUpFrameFilterRegisterPointer(void)
{
    ETH->PMTCTRLSTS_B.WKUPFRST = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Populates the remote wakeup frame registers.
 *
 * @param  buffer: WakeUp Frame Filter Register buffer data (8 words).
 *
 * @retval None
 */
void ETH_ConfigWakeUpFrameFilterRegister(uint32_t *buffer)
{
    uint32_t i = 0;
    __IO uint32_t temp = 0;

    for(i = 0; i < ETH_WAKEUP_REGISTER_LENGTH; i++)
    {
        ETH->WKUPFFL = buffer[i];

        temp = ETH->WKUPFFL;
        ETH_Delay(ETH_REG_WRITE_DELAY);
        ETH->WKUPFFL = temp;
    }
}

/*!
 * @brief  Enable any unicast packet filtered by the MAC address
 *         recognition to be a wake-up frame.
 *
 * @retval None
 */
void ETH_EnableGlobalUnicastWakeUp(void)
{
    ETH->PMTCTRLSTS_B.GUN = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Disable any unicast packet filtered by the MAC address
 *         recognition to be a wake-up frame.
 *
 * @retval None
 */
void ETH_DisableGlobalUnicastWakeUp(void)
{
    ETH->PMTCTRLSTS_B.GUN = RESET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Read the ETH PMT flag.
 *
 * @param  flag: specifies the flag to check.
 *         This parameter can be one of the following values:
 *           @arg ETH_PMT_FLAG_WUFFRPR : Wake-Up Frame Filter Register Pointer Reset
 *           @arg ETH_PMT_FLAG_WUFR    : Wake-Up Frame Received
 *           @arg ETH_PMT_FLAG_MPR     : Magic Packet Received
 *
 * @retval SET or RESET.
 */
uint8_t ETH_ReadPMTFlagStatus(ETH_PMT_FLAG_T flag)
{
    return (ETH->PMTCTRLSTS & flag) ? SET : RESET;
}

/*!
 * @brief  Enable the MAC Wake-Up Frame Detection.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_EnableWakeUpFrameDetection(void)
{
    ETH->PMTCTRLSTS_B.WKUPFEN = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Disable the MAC Wake-Up Frame Detection.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_DisableWakeUpFrameDetection(void)
{
    ETH->PMTCTRLSTS_B.WKUPFEN = RESET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Enable the MAC Magic Packet Detection.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_EnableMagicPacketDetection(void)
{
    ETH->PMTCTRLSTS_B.MPEN = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Disable the MAC Magic Packet Detection.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_DisableMagicPacketDetection(void)
{
    ETH->PMTCTRLSTS_B.MPEN = RESET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Enable the MAC Power Down.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_EnablePowerDown(void)
{
    ETH->PMTCTRLSTS_B.PD = SET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/*!
 * @brief  Disable the MAC Power Down.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_DisablePowerDown(void)
{
    ETH->PMTCTRLSTS_B.PD = RESET;
    ETH_Delay(ETH_REG_WRITE_DELAY);
}

/** MMC functions */

/**
  * @brief  Preset and Initialize the MMC counters to almost-full value: 0xFFFF_FFF0 (full - 16)
  * @param  None
  * @retval None
  */
void ETH_PresetMMCCounterFull(void)
{
    ETH->CTRL_B.MCNTP = SET;
    ETH->CTRL_B.MCNTVALP = SET;
}

/**
  * @brief  Preset and Initialize the MMC counters to almost-hal value: 0x7FFF_FFF0 (half - 16)
  * @param  None
  * @retval None
  */
void ETH_PresetMMCCounterHalf(void)
{
    ETH->CTRL_B.MCNTP = SET;
    ETH->CTRL_B.MCNTVALP = RESET;
}

/*!
 * @brief  Enable the MMC Counter Freeze.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_EnableMMCCounterFreeze(void)
{
    ETH->CTRL_B.MCNTF = SET;
}

/*!
 * @brief  Disable the MMC Counter Freeze.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_DisableMMCCounterFreeze(void)
{
    ETH->CTRL_B.MCNTF = RESET;
}

/*!
 * @brief  Enable the MMC Reset On Read.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_EnableMMCResetOnRead(void)
{
    ETH->CTRL_B.RSTOR = SET;
}

/*!
 * @brief  Disable the MMC Reset On Read.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_DisableMMCResetOnRead(void)
{
    ETH->CTRL_B.RSTOR = RESET;
}

/*!
 * @brief  Enble the MMC Counter Stop Rollover.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_EnableMMCCounterRollover(void)
{
    ETH->CTRL_B.CNTSTOPRO = RESET;
}

/*!
 * @brief  Disable the MMC Counter Stop Rollover.
 *
 * @param  None
 *
 * @retval None
 */
void ETH_DisableMMCCounterRollover(void)
{
    ETH->CTRL_B.CNTSTOPRO = SET;
}

/**
  * @brief  Resets the MMC Counters.
  * @param  None
  * @retval None
  */
void ETH_ResetMMCCounters(void)
{
    ETH->CTRL_B.CNTRST = SET;
}

/*!
 * @brief  Enable the ETH MMC interrupts.
 *
 * @param  interrupt: specifies the ETH MMC interrupt sources.
 *         This parameter can be any combination of Tx interrupt or
 *         any combination of Rx interrupt (but not both)of the following values:
 *           @arg ETH_MMC_INT_TGF   : When Tx good frame counter reaches half the maximum value
 *           @arg ETH_MMC_INT_TGFMSC: When Tx good multi col counter reaches half the maximum value
 *           @arg ETH_MMC_INT_TGFSC : When Tx good single col counter reaches half the maximum value
 *           @arg ETH_MMC_INT_RGUF  : When Rx good unicast frames counter reaches half the maximum value
 *           @arg ETH_MMC_INT_RFAE  : When Rx alignment error counter reaches half the maximum value
 *           @arg ETH_MMC_INT_RFCE  : When Rx crc error counter reaches half the maximum value
 *
 * @retval None
 */
void ETH_EnableMMCInterrupt(uint32_t interrupt)
{
   if((interrupt & 0x10000000) == SET)
   {
        ETH->RXINTMASK &= (~(uint32_t)interrupt);
   }
   else
   {
        ETH->TXINTMASK &= (~(uint32_t)interrupt);
   }
}

/*!
 * @brief  Disable the ETH MMC interrupts.
 *
 * @param  interrupt: specifies the ETH MMC interrupt sources.
 *         This parameter can be any combination of Tx interrupt or
 *         any combination of Rx interrupt (but not both)of the following values:
 *           @arg ETH_MMC_INT_TGF   : When Tx good frame counter reaches half the maximum value
 *           @arg ETH_MMC_INT_TGFMSC: When Tx good multi col counter reaches half the maximum value
 *           @arg ETH_MMC_INT_TGFSC : When Tx good single col counter reaches half the maximum value
 *           @arg ETH_MMC_INT_RGUF  : When Rx good unicast frames counter reaches half the maximum value
 *           @arg ETH_MMC_INT_RFAE  : When Rx alignment error counter reaches half the maximum value
 *           @arg ETH_MMC_INT_RFCE  : When Rx crc error counter reaches half the maximum value
 *
 * @retval None
 */
void ETH_DisableMMCInterrupt(uint32_t interrupt)
{
   if((interrupt & 0x10000000) == SET)
   {
        ETH->RXINTMASK |= interrupt;
   }
   else
   {
        ETH->TXINTMASK |= interrupt;
   }
}

/*!
 * @brief  Read the ETH MMC interrupt flag.
 *
 * @param  flag: specifies the ETH MMC interrupt.
 *         This parameter can be one of the following values:
 *           @arg ETH_MMC_INT_TGF   : When Tx good frame counter reaches half the maximum value
 *           @arg ETH_MMC_INT_TGFMSC: When Tx good multi col counter reaches half the maximum value
 *           @arg ETH_MMC_INT_TGFSC : When Tx good single col counter reaches half the maximum value
 *           @arg ETH_MMC_INT_RGUF  : When Rx good unicast frames counter reaches half the maximum value
 *           @arg ETH_MMC_INT_RFAE  : When Rx alignment error counter reaches half the maximum value
 *           @arg ETH_MMC_INT_RFCE  : When Rx crc error counter reaches half the maximum value
 *
 * @retval SET or RESET.
 */
uint8_t ETH_ReadMMCIntFlag(uint32_t flag)
{
    if((flag & 0x10000000) == SET)
    {
        return ((((ETH->RXINT & flag) != RESET)) && ((ETH->RXINTMASK & flag) == RESET));
    }
    else
    {
        return ((((ETH->TXINT & flag) != RESET)) && ((ETH->TXINTMASK & flag) == RESET));
    }
}

/*!
 * @brief  Read the ETH MMC register value.
 *
 * @param  MMCReg: specifies the ETH MMC register.
 *         This parameter can be one of the following values:
 *           @arg ETH_MMC_CTRL      : MMC CTRL register
 *           @arg ETH_MMC_RXINT     : MMC RXINT register
 *           @arg ETH_MMC_TXINT     : MMC TXINT register
 *           @arg ETH_MMC_RXINTMASK : MMC RXINTMASK register
 *           @arg ETH_MMC_TXINTMASK : MMC TXINTMASK register
 *           @arg ETH_MMC_TXGFSCCNT : MMC TXGFSCCNT register
 *           @arg ETH_MMC_TXGFMCCNT : MMC TXGFMCCNT register
 *           @arg ETH_MMC_TXGFCNT   : MMC TXGFCNT register
 *           @arg ETH_MMC_RXFCECNT  : MMC RXFCECNT register
 *           @arg ETH_MMC_RXFAECNT  : MMC RXFAECNT register
 *           @arg ETH_MMC_RXGUNCNT  : MMC RXGUNCNT register
 *
 * @retval Return ETH MMC Register value.
 */
uint32_t ETH_ReadMMCRegister(ETH_MMC_REG_T MMCReg)
{
    return (*(__IO uint32_t *)(ETH_MAC_BASE + MMCReg));
}

/**@} end of group ETH_Functions */
/**@} end of group ETH_Driver */
/**@} end of group APM32F4xx_ETHDriver */
