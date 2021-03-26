/**
  ******************************************************************************
  * @brief   ETH header file of the firmware library.
  ******************************************************************************
  */
#ifdef GD32F10X_CL
/* Includes ------------------------------------------------------------------*/
#include "gd32f10x_eth.h"
#include "gd32f10x_rcc.h"

/** @addtogroup GD32F10x_Firmware
  * @{
  */

/** @defgroup ETH
  * @brief ETH driver modules
  * @{
  */

/** @defgroup ETH_Private_Defines
  * @{
  */

/* Global transmit and receive descriptors pointers */
ETH_DMADESCTypeDef  *DMACurrentTxDesc;
ETH_DMADESCTypeDef  *DMACurrentRxDesc;
ETH_DMADESCTypeDef  *DMACurrentPTPTxDesc;
ETH_DMADESCTypeDef  *DMACurrentPTPRxDesc;

/* ETHERNET MAC address offsets */
#define ETH_MAC_ADDR_HBASE                              (ETH_MAC_BASE + 0x40)   /* ETHERNET MAC address high offset */
#define ETH_MAC_ADDR_LBASE                              (ETH_MAC_BASE + 0x44)   /* ETHERNET MAC address low offset */

/* ETHERNET MAC_PHYAR register Mask */
#define MAC_PHYAR_CLR_MASK                              ((uint32_t)0xFFFFFFE3)

/* ETHERNET MAC_PHYAR register PHY address shift */
#define MAC_PHYAR_PHYADDRSHIFT                          11

/* ETHERNET MAC_PHYAR register PHY register shift */
#define MAC_PHYAR_PHYREGSHIFT                           6

/* ETHERNET MAC_CFR register Mask */
#define MAC_CFR_CLEAR_MASK                              ((uint32_t)0xFF20810F)

/* ETHERNET MAC_FCTLR register Mask */
#define MAC_FCTLR_CLEAR_MASK                            ((uint32_t)0x0000FF41)

/* ETHERNET DMA_CTLR register Mask */
#define DMA_CTLR_CLEAR_MASK                             ((uint32_t)0xF8DE3F23)

/* ETHERNET Remote Wake-up frame register length */
#define ETH_WAKEUP_REGISTER_LENGTH                      8

/* ETHERNET Missed frames counter Shift */
#define  ETH_DMA_RX_OVERFLOW_MISSEDFRAMES_COUNTERSHIFT  17

/* ETHERNET DMA Tx descriptors Collision Count Shift */
#define  ETH_DMATXDESC_COLLISION_COUNTSHIFT             3

/* ETHERNET DMA Tx descriptors size */
#define  ETH_DMATXDESC_SIZE                             0x10

/* ETHERNET DMA Rx descriptors size */
#define  ETH_DMARXDESC_SIZE                             0x10

/* ETHERNET DMA Tx descriptors Buffer2 Size Shift */
#define  ETH_DMATXDESC_BUFFER2_SIZESHIFT                16

/* ETHERNET DMA Rx descriptors Frame Length Shift */
#define  ETH_DMARXDESC_FRAME_LENGTHSHIFT                16

/* ETHERNET DMA Rx descriptors Buffer2 Size Shift */
#define  ETH_DMARXDESC_BUFFER2_SIZESHIFT                16

/* ETHERNET errors */
#define  ERROR                                          ((uint32_t)0)
#define  SUCCESS                                        ((uint32_t)1)
/**
  * @}
  */

/** @defgroup ETH_Private_FunctionPrototypes
  * @{
  */

#ifndef USE_Delay
    static void ETH_Delay(__IO uint32_t nCount);
#endif /* USE_Delay*/

/**
  * @}
  */

/** @defgroup ETH_Private_Functions
  * @{
  */

/**
  * @brief  Reset the ETH registers.
  * @param  None
  * @retval None
  */
void ETH_DeInit(void)
{
    RCC_AHBPeriphReset_Enable(RCC_AHBPERIPH_ETH_MAC, ENABLE);
    RCC_AHBPeriphReset_Enable(RCC_AHBPERIPH_ETH_MAC, DISABLE);
}

/**
  * @brief  Initialize MDIO parameters.
  * @param  None
  * @retval None
  */
void ETH_MDIOInit(void)
{
    uint32_t temp = 0;
    RCC_ClocksPara  rcc_clocks;
    uint32_t hclk;

    /* ETHERNET MAC_PHYAR Configuration */
    /* Get the ETH_MAC_PHYAR value */
    temp = ETH_MAC->PHYAR;
    /* Clear Clock Range CLR[2:0] bits */
    temp &= MAC_PHYAR_CLR_MASK;
    /* Get hclk frequency value */
    RCC_GetClocksFreq(&rcc_clocks);
    hclk = rcc_clocks.AHB_Frequency;
    /* Set CLR bits depending on hclk value */
    if ((hclk >= 20000000) && (hclk < 35000000)) {
        /* Clock Range between 20-35 MHz */
        temp |= (uint32_t)ETH_MAC_PHYAR_CLR_DIV16;
    } else if ((hclk >= 35000000) && (hclk < 60000000)) {
        /* Clock Range between 35-60 MHz */
        temp |= (uint32_t)ETH_MAC_PHYAR_CLR_DIV26;
    } else if ((hclk >= 60000000) && (hclk < 90000000)) {
        /* Clock Range between 60-90 MHz */
        temp |= (uint32_t)ETH_MAC_PHYAR_CLR_DIV42;
    }
    /* ((hclk >= 90000000)&&(hclk <= 108000000)) */
    else {
        /* Clock Range between 90-108 MHz */
        temp |= (uint32_t)ETH_MAC_PHYAR_CLR_DIV64;
    }
    /* Write to ETHERNET MAC PHYAR */
    ETH_MAC->PHYAR = (uint32_t)temp;
}

/**
  * @brief  Initial the ETH parameters.
  * @param  ETH_InitParaStruct: The ETH_InitPara structure pointer.
  * @param  PHYAddress: external PHY address
  * @retval The Initialize result(ERROR or SUCCESS)
  */
uint32_t ETH_Init(ETH_InitPara *ETH_InitParaStruct, uint16_t PHYAddress)
{
    uint32_t RegValue = 0, temp = 0;
    __IO uint32_t i = 0;
    RCC_ClocksPara  rcc_clocks;
    uint32_t hclk;
    __IO uint32_t timeout = 0;

    /* MAC Config */
    /* ETH_MAC_PHYAR Configuration */
    /* Get the ETH_MAC_PHYAR value */
    temp = ETH_MAC->PHYAR;
    /* Clear Clock Range CLR[2:0] bits */
    temp &= MAC_PHYAR_CLR_MASK;
    /* Get hclk frequency value */
    RCC_GetClocksFreq(&rcc_clocks);
    hclk = rcc_clocks.AHB_Frequency;
    /* Set CLR bits depending on hclk value */
    if ((hclk >= 20000000) && (hclk < 35000000)) {
        /* Clock Range between 20-35 MHz */
        temp |= (uint32_t)ETH_MAC_PHYAR_CLR_DIV16;
    } else if ((hclk >= 35000000) && (hclk < 60000000)) {
        /* Clock Range between 35-60 MHz */
        temp |= (uint32_t)ETH_MAC_PHYAR_CLR_DIV26;
    } else if ((hclk >= 60000000) && (hclk < 90000000)) {
        /* Clock Range between 60-90 MHz */
        temp |= (uint32_t)ETH_MAC_PHYAR_CLR_DIV42;
    }
    /* ((hclk >= 90000000)&&(hclk <= 108000000)) */
    else {
        /* Clock Range between 90-108 MHz */
        temp |= (uint32_t)ETH_MAC_PHYAR_CLR_DIV64;
    }
    ETH_MAC->PHYAR = (uint32_t)temp;
    /* PHY initialization and configuration */
    /* Set the PHY into reset mode */
    if (!(ETH_SetPHYRegisterValue(PHYAddress, PHY_BCR, PHY_RESET))) {
        /* Return ERROR due to write timeout */
        return ERROR;
    }

    /* PHY reset need some time */
    _eth_delay_(PHY_RESETDELAY);

    if (ETH_InitParaStruct->ETH_MAC_AutoNegotiation != ETH_AUTONEGOTIATION_DISABLE) {
        /* Wait for PHY_LINKED_STATUS bit be set */
        do {
            timeout++;
        } while (!(ETH_GetPHYRegisterValue(PHYAddress, PHY_BSR) & PHY_LINKED_STATUS) && (timeout < PHY_READ_TO));
        /* Return ERROR due to timeout */
        if (timeout == PHY_READ_TO) {
            return ERROR;
        }
        /* Reset Timeout counter */
        timeout = 0;

        /* Enable Auto-Negotiation */
        if (!(ETH_SetPHYRegisterValue(PHYAddress, PHY_BCR, PHY_AUTONEGOTIATION))) {
            /* Return ERROR due to write timeout */
            return ERROR;
        }

        /* Wait for the PHY_AUTONEGO_COMPLETE bit be set */
        do {
            timeout++;
        } while (!(ETH_GetPHYRegisterValue(PHYAddress, PHY_BSR) & PHY_AUTONEGO_COMPLETE) && (timeout < (uint32_t)PHY_READ_TO));
        /* Return ERROR due to timeout */
        if (timeout == PHY_READ_TO) {
            return ERROR;
        }
        /* Reset Timeout counter */
        timeout = 0;

        /* Read the result of the autonegotiation */
        RegValue = ETH_GetPHYRegisterValue(PHYAddress, PHY_SR);

        /* Configure the Duplex Mode of MAC following the autonegotiation result */
        if ((RegValue & PHY_DUPLEX_STATUS) != (uint32_t)RESET) {
            ETH_InitParaStruct->ETH_MAC_Mode = ETH_MODE_FULLDUPLEX;

        } else {
            ETH_InitParaStruct->ETH_MAC_Mode = ETH_MODE_HALFDUPLEX;
        }
        /* Configure the Communication speed of MAC following the autonegotiation result */
        if (RegValue & PHY_Speed_Status) {
            ETH_InitParaStruct->ETH_MAC_Speed = ETH_SPEEDMODE_10M;
        } else {
            ETH_InitParaStruct->ETH_MAC_Speed = ETH_SPEEDMODE_100M;
        }
    } else {
        if (!ETH_SetPHYRegisterValue(PHYAddress, PHY_BCR, ((uint16_t)(ETH_InitParaStruct->ETH_MAC_Mode >> 3) |
                                     (uint16_t)(ETH_InitParaStruct->ETH_MAC_Speed >> 1)))) {
            /* Return ERROR due to write timeout */
            return ERROR;
        }
        /* PHY configuration need some time */
        _eth_delay_(PHY_CONFIGDELAY);
    }
    /* ETH_MAC_CFR Configuration */
    /* Get the ETH_MAC_CFR value */
    temp = ETH_MAC->CFR;
    temp &= MAC_CFR_CLEAR_MASK;
    /* Set the WDD bit according to ETH_MAC_Watchdog value */
    /* Set the JBD: bit according to ETH_MAC_Jabber value */
    /* Set the IG bit according to ETH_MAC_InterFrameGap value */
    /* Set the CSD bit according to ETH_MAC_CarrierSense value */
    /* Set the SPD bit according to ETH_MAC_Speed value */
    /* Set the ROD bit according to ETH_MAC_ReceiveOwn value */
    /* Set the LBM bit according to ETH_MAC_LoopbackMode value */
    /* Set the DPM bit according to ETH_MAC_Mode value */
    /* Set the IP4CO bit according to ETH_MAC_ChecksumOffload value */
    /* Set the RTD bit according to ETH_MAC_RetryTransmission value */
    /* Set the APCD bit according to ETH_MAC_AutomaticPadCRCDrop value */
    /* Set the BOL bit according to ETH_MAC_BackOffLimit value */
    /* Set the DFC bit according to ETH_MAC_DeferralCheck value */
    temp |= (uint32_t)(ETH_InitParaStruct->ETH_MAC_Watchdog |
                       ETH_InitParaStruct->ETH_MAC_Jabber |
                       ETH_InitParaStruct->ETH_MAC_InterFrameGap |
                       ETH_InitParaStruct->ETH_MAC_CarrierSense |
                       ETH_InitParaStruct->ETH_MAC_Speed |
                       ETH_InitParaStruct->ETH_MAC_ReceiveOwn |
                       ETH_InitParaStruct->ETH_MAC_LoopbackMode |
                       ETH_InitParaStruct->ETH_MAC_Mode |
                       ETH_InitParaStruct->ETH_MAC_ChecksumOffload |
                       ETH_InitParaStruct->ETH_MAC_RetryTransmission |
                       ETH_InitParaStruct->ETH_MAC_AutomaticPadCRCDrop |
                       ETH_InitParaStruct->ETH_MAC_BackOffLimit |
                       ETH_InitParaStruct->ETH_MAC_DeferralCheck);
    /* Write to ETH_MAC_CFR */
    ETH_MAC->CFR = (uint32_t)temp;

    /* ETH_MAC_FRMFR Configuration */
    /* Set the FD bit according to ETH_MAC_FilterDisable value */
    /* Set the SAFLT and SAIFLT bits according to ETH_MAC_SourceAddrFilter value */
    /* Set the PCFRM bit according to ETH_MAC_PassControlFrames value */
    /* Set the DBF bit according to ETH_MAC_BroadcastFramesReception value */
    /* Set the DAIFLT bit according to ETH_MAC_DestinationAddrFilter value */
    /* Set the PM bit according to ETH_MAC_PromiscuousMode value */
    /* Set the PM, HMF and HPFLT bits according to ETH_MAC_MulticastFramesFilter value */
    /* Set the HUF and HPFLT bits according to ETH_MAC_UnicastFramesFilter value */
    /* Write to ETH_MAC_FRMFR */
    ETH_MAC->FRMFR = (uint32_t)(ETH_InitParaStruct->ETH_MAC_FilterDisable |
                                ETH_InitParaStruct->ETH_MAC_SourceAddrFilter |
                                ETH_InitParaStruct->ETH_MAC_PassControlFrames |
                                ETH_InitParaStruct->ETH_MAC_BroadcastFramesReception |
                                ETH_InitParaStruct->ETH_MAC_DestinationAddrFilter |
                                ETH_InitParaStruct->ETH_MAC_PromiscuousMode |
                                ETH_InitParaStruct->ETH_MAC_MulticastFramesFilter |
                                ETH_InitParaStruct->ETH_MAC_UnicastFramesFilter);
    /* ETH_MAC_HLHR and MAC_HLLR Configuration */
    /* Write to ETHERNET MAC_HLHR */
    ETH_MAC->HLHR = (uint32_t)ETH_InitParaStruct->ETH_MAC_HashListHigh;
    /* Write to ETHERNET MAC_HLLR */
    ETH_MAC->HLLR = (uint32_t)ETH_InitParaStruct->ETH_MAC_HashListLow;
    /* ETH_MAC_FCTLR Configuration */
    /* Get the ETH_MAC_FCTLR value */
    temp = ETH_MAC->FCTLR;
    temp &= MAC_FCTLR_CLEAR_MASK;

    /* Set the PTM bit according to ETH_MAC_PauseTime value */
    /* Set the ZQPD bit according to ETH_MAC_ZeroQuantaPause value */
    /* Set the PLTS bit according to ETH_MAC_PauseLowThreshold value */
    /* Set the UPFDT bit according to  ETH_MAC_UnicastPauseFrameDetect value */
    /* Set the RFCEN bit according to ETH_MAC_ReceiveFlowControl value */
    /* Set the TFCEN bit according to ETH_MAC_TransmitFlowControl value */
    temp |= (uint32_t)((ETH_InitParaStruct->ETH_MAC_PauseTime << 16) |
                       ETH_InitParaStruct->ETH_MAC_ZeroQuantaPause |
                       ETH_InitParaStruct->ETH_MAC_PauseLowThreshold |
                       ETH_InitParaStruct->ETH_MAC_UnicastPauseFrameDetect |
                       ETH_InitParaStruct->ETH_MAC_ReceiveFlowControl |
                       ETH_InitParaStruct->ETH_MAC_TransmitFlowControl);
    /* Write to ETH_MAC_FCTLR */
    ETH_MAC->FCTLR = (uint32_t)temp;
    /* ETH_MAC_FCTHR Configuration */
    temp = ETH_MAC->FCTHR;
    temp |= (uint32_t)(ETH_InitParaStruct->ETH_MAC_FlowControlDeactiveThreshold |
                       ETH_InitParaStruct->ETH_MAC_FlowControlActiveThreshold);
    ETH_MAC->FCTHR = (uint32_t)temp;
    /* ETH_MAC_VLTR Configuration */
    /* Set the VLTC bit according to ETH_MAC_VLANTagComparison value */
    /* Set the VLTI bit according to ETH_MAC_VLANTagIdentifier value */
    ETH_MAC->VLTR = (uint32_t)(ETH_InitParaStruct->ETH_MAC_VLANTagComparison |
                               ETH_InitParaStruct->ETH_MAC_VLANTagIdentifier);

    /* DMA Config */
    /* ETH_DMA_CTLR Configuration */
    /* Get the ETHERNET DMA_CTLR value */
    temp = ETH_DMA->CTLR;
    temp &= DMA_CTLR_CLEAR_MASK;

    /* Set the DTCERFD bit according to ETH_DMA_DropTCPIPChecksumErrorFrame value */
    /* Set the RSFD bit according to ETH_DMA_ReceiveStoreForward value */
    /* Set the DAFRF bit according to ETH_DMA_FlushReceivedFrame value */
    /* Set the TSFD bit according to ETH_DMA_TransmitStoreForward value */
    /* Set the TTCH bit according to ETH_DMA_TransmitThresholdControl value */
    /* Set the FERF bit according to ETH_DMA_ForwardErrorFrames value */
    /* Set the FUF bit according to ETH_DMA_ForwardUndersizedGoodFrames value */
    /* Set the RTHC bit according to ETH_DMA_ReceiveThresholdControl value */
    /* Set the OSF bit according to ETH_DMA_SecondFrameOperate value */
    temp |= (uint32_t)(ETH_InitParaStruct->ETH_DMA_DropTCPIPChecksumErrorFrame |
                       ETH_InitParaStruct->ETH_DMA_ReceiveStoreForward |
                       ETH_InitParaStruct->ETH_DMA_FlushReceivedFrame |
                       ETH_InitParaStruct->ETH_DMA_TransmitStoreForward |
                       ETH_InitParaStruct->ETH_DMA_TransmitThresholdControl |
                       ETH_InitParaStruct->ETH_DMA_ForwardErrorFrames |
                       ETH_InitParaStruct->ETH_DMA_ForwardUndersizedGoodFrames |
                       ETH_InitParaStruct->ETH_DMA_ReceiveThresholdControl |
                       ETH_InitParaStruct->ETH_DMA_SecondFrameOperate);
    /* Write to ETH_DMA_CTLR */
    ETH_DMA->CTLR = (uint32_t)temp;

    /* ETH_DMA_BCR Configuration */
    /* Set the AA bit according to ETH_DMA_AddressAligned value */
    /* Set the FB bit according to ETH_DMA_FixedBurst value */
    /* Set the RXDP and 4*PBL bits according to ETH_DMA_RxDMABurstLength value */
    /* Set the FPBL and 4*PBL bits according to ETH_DMA_TxDMABurstLength value */
    /* Set the DPSL bit according to ETH_DesciptorSkipLength value */
    /* Set the RTPR and DAB bits according to ETH_DMA_Arbitration value */
    ETH_DMA->BCR = (uint32_t)(ETH_InitParaStruct->ETH_DMA_AddressAligned |
                              ETH_InitParaStruct->ETH_DMA_FixedBurst |
                              ETH_InitParaStruct->ETH_DMA_RxDMABurstLength | /* If 4xPBL is selected for Tx or Rx it is applied for the other */
                              ETH_InitParaStruct->ETH_DMA_TxDMABurstLength |
                              (ETH_InitParaStruct->ETH_DMA_DescriptorSkipLength << 2) |
                              ETH_InitParaStruct->ETH_DMA_Arbitration |
                              ETH_DMA_BCR_UIP); /* Enable use of separate PBL for Rx and Tx */
    /* Return Ethernet configuration success */
    return SUCCESS;
}

/**
  * @brief  Initial the sturct ETH_InitPara.
  * @param  ETH_InitParaStruct: pointer to a ETH_InitPara structure.
  * @retval None
  */
void ETH_ParaInit(ETH_InitPara *ETH_InitParaStruct)
{
    /* Reset ETH init structure parameters values */
    /* MAC */
    ETH_InitParaStruct->ETH_MAC_AutoNegotiation = ETH_AUTONEGOTIATION_DISABLE;
    ETH_InitParaStruct->ETH_MAC_Watchdog = ETH_WATCHDOG_ENABLE;
    ETH_InitParaStruct->ETH_MAC_Jabber = ETH_JABBER_ENABLE;
    ETH_InitParaStruct->ETH_MAC_InterFrameGap = ETH_INTERFRAMEGAP_96BIT;
    ETH_InitParaStruct->ETH_MAC_CarrierSense = ETH_CARRIERSENSE_ENABLE;
    ETH_InitParaStruct->ETH_MAC_Speed = ETH_SPEEDMODE_10M;
    ETH_InitParaStruct->ETH_MAC_ReceiveOwn = ETH_RECEIVEOWN_ENABLE;
    ETH_InitParaStruct->ETH_MAC_LoopbackMode = ETH_LOOPBACKMODE_DISABLE;
    ETH_InitParaStruct->ETH_MAC_Mode = ETH_MODE_HALFDUPLEX;
    ETH_InitParaStruct->ETH_MAC_ChecksumOffload = ETH_CHECKSUMOFFLOAD_DISABLE;
    ETH_InitParaStruct->ETH_MAC_RetryTransmission = ETH_RETRYTRANSMISSION_ENABLE;
    ETH_InitParaStruct->ETH_MAC_AutomaticPadCRCDrop = ETH_AUTOMATICPADCRCDROP_DISABLE;
    ETH_InitParaStruct->ETH_MAC_BackOffLimit = ETH_BACKOFFLIMIT_10;
    ETH_InitParaStruct->ETH_MAC_DeferralCheck = ETH_DEFERRALCHECK_DISABLE;
    ETH_InitParaStruct->ETH_MAC_FilterDisable = ETH_FILTERDISABLE_DISABLE;
    ETH_InitParaStruct->ETH_MAC_SourceAddrFilter = ETH_SOURCEADDRFILTER_DISABLE;
    ETH_InitParaStruct->ETH_MAC_PassControlFrames = ETH_PASSCONTROLFRAMES_BLOCKALL;
    ETH_InitParaStruct->ETH_MAC_BroadcastFramesReception = ETH_BROADCASTFRAMESRECEPTION_DISABLE;
    ETH_InitParaStruct->ETH_MAC_DestinationAddrFilter = ETH_DESTINATIONADDRFILTER_NORMAL;
    ETH_InitParaStruct->ETH_MAC_PromiscuousMode = ETH_PROMISCUOUSMODE_DISABLE;
    ETH_InitParaStruct->ETH_MAC_MulticastFramesFilter = ETH_MULTICASTFRAMESFILTER_PERFECT;
    ETH_InitParaStruct->ETH_MAC_UnicastFramesFilter = ETH_UNICASTFRAMESFILTER_PERFECT;
    ETH_InitParaStruct->ETH_MAC_HashListHigh = 0x0;
    ETH_InitParaStruct->ETH_MAC_HashListLow = 0x0;
    ETH_InitParaStruct->ETH_MAC_PauseTime = 0x0;
    ETH_InitParaStruct->ETH_MAC_ZeroQuantaPause = ETH_ZEROQUANTAPAUSE_DISABLE;
    ETH_InitParaStruct->ETH_MAC_PauseLowThreshold = ETH_PAUSELOWTHRESHOLD_MINUS4;
    ETH_InitParaStruct->ETH_MAC_FlowControlDeactiveThreshold = ETH_RFD_512BYTES;
    ETH_InitParaStruct->ETH_MAC_FlowControlActiveThreshold =  ETH_RFA_1536BYTES;
    ETH_InitParaStruct->ETH_MAC_UnicastPauseFrameDetect = ETH_UNICASTPAUSEFRAMEDETECT_DISABLE;
    ETH_InitParaStruct->ETH_MAC_ReceiveFlowControl = ETH_RECEIVEFLOWCONTROL_DISABLE;
    ETH_InitParaStruct->ETH_MAC_TransmitFlowControl = ETH_TRANSMITFLOWCONTROL_DISABLE;
    ETH_InitParaStruct->ETH_MAC_VLANTagComparison = ETH_VLANTAGCOMPARISON_16BIT;
    ETH_InitParaStruct->ETH_MAC_VLANTagIdentifier = 0x0;
    /* DMA */
    ETH_InitParaStruct->ETH_DMA_DropTCPIPChecksumErrorFrame = ETH_DROPTCPIPCHECKSUMERRORFRAME_DISABLE;
    ETH_InitParaStruct->ETH_DMA_ReceiveStoreForward = ETH_RECEIVESTOREFORWARD_ENABLE;
    ETH_InitParaStruct->ETH_DMA_FlushReceivedFrame = ETH_FLUSHRECEIVEDFRAME_DISABLE;
    ETH_InitParaStruct->ETH_DMA_TransmitStoreForward = ETH_TRANSMITSTOREFORWARD_ENABLE;
    ETH_InitParaStruct->ETH_DMA_TransmitThresholdControl = ETH_TRANSMITTHRESHOLDCONTROL_64BYTES;
    ETH_InitParaStruct->ETH_DMA_ForwardErrorFrames = ETH_FORWARDERRORFRAMES_DISABLE;
    ETH_InitParaStruct->ETH_DMA_ForwardUndersizedGoodFrames = ETH_FORWARDUNDERSIZEDGOODFRAMES_DISABLE;
    ETH_InitParaStruct->ETH_DMA_ReceiveThresholdControl = ETH_RECEIVETHRESHOLDCONTROL_64BYTES;
    ETH_InitParaStruct->ETH_DMA_SecondFrameOperate = ETH_SECONDFRAMEOPERATE_DISABLE;
    ETH_InitParaStruct->ETH_DMA_AddressAligned = ETH_ADDRESSALIGNED_ENABLE;
    ETH_InitParaStruct->ETH_DMA_FixedBurst = ETH_FIXEDBURST_DISABLE;
    ETH_InitParaStruct->ETH_DMA_RxDMABurstLength = ETH_RXDMABURSTLENGTH_1BEAT;
    ETH_InitParaStruct->ETH_DMA_TxDMABurstLength = ETH_TXDMABURSTLENGTH_1BEAT;
    ETH_InitParaStruct->ETH_DMA_DescriptorSkipLength = 0x0;
    ETH_InitParaStruct->ETH_DMA_Arbitration = ETH_DMAARBITRATION_ROUNDROBIN_RXTX_1_1;
}

/**
  * @brief  Enable or disable the ETH's receive and transmit.
  * @param  NewValue: ENABLE or DISABLE.
  * @retval None
  */
void ETH_Enable(TypeState NewValue)
{
    /* Enable or Disable the ETH module */
    if (NewValue != DISABLE) {
        /* Enable MAC transmit */
        ETH_MACTransmission_Enable(ENABLE);
        /* Flush ETHERNET DMA Transmit FIFO */
        ETH_CleanTransmitFIFO();
        /* Enable MAC receive */
        ETH_MACReception_Enable(ENABLE);

        /* Enable DMA transmission */
        ETH_DMATransmission_Enable(ENABLE);
        /* Enable DMA reception */
        ETH_DMAReception_Enable(ENABLE);
    } else {
        /* Disable MAC transmit */
        ETH_MACTransmission_Enable(DISABLE);
        /* Flush ETHERNET DMA Transmit FIFO */
        ETH_CleanTransmitFIFO();
        /* Disable MAC receive */
        ETH_MACReception_Enable(DISABLE);

        /* Disable DMA transmission */
        ETH_DMATransmission_Enable(DISABLE);
        /* Disable DMA reception */
        ETH_DMAReception_Enable(DISABLE);
    }
}

/**
  * @brief  Send data of application buffer as a transmit packet.
  * @param  pbuf: Pointer to the application buffer.
  * @param  size: the application buffer size.
  * @retval The transmission result(ERROR or SUCCESS)
  */
uint32_t ETH_HandleTxPkt(uint8_t *pbuf, uint16_t size)
{
    uint32_t offset = 0;

    /* Check the busy bit of Tx descriptor status */
    if ((DMACurrentTxDesc->Status & ETH_DMATXDESC_BUSY) != (uint32_t)RESET) {
        /* Return ERROR: the descriptor is busy due to own by the DMA */
        return ERROR;
    }

    for (offset = 0; offset < size; offset++) {
        (*(__IO uint8_t *)((DMACurrentTxDesc->Buffer1Addr) + offset)) = (*(pbuf + offset));
    }

    /* Setting the Frame Length */
    DMACurrentTxDesc->ControlBufferSize = (size & ETH_DMATXDESC_TB1S);
    /* Setting the segment of frame (ETH_DMATXDESC_LSG and ETH_DMATXDESC_FSG are SET that frame is transmitted in one descriptor) */
    DMACurrentTxDesc->Status |= ETH_DMATXDESC_LSG | ETH_DMATXDESC_FSG;
    /* Enable the DMA transmission */
    DMACurrentTxDesc->Status |= ETH_DMATXDESC_BUSY;
    /* Check Tx Buffer unavailable flag status */
    if ((ETH_DMA->STR & ETH_DMA_STR_TBU) != (uint32_t)RESET) {
        /* Clear TBU ETHERNET DMA flag */
        ETH_DMA->STR = ETH_DMA_STR_TBU;
        /* Resume DMA transmission by writing to the TPER register*/
        ETH_DMA->TPER = 0;
    }

    /* Update the ETHERNET DMA current Tx descriptor pointer to the next Tx decriptor in DMA Tx decriptor talbe*/
    /* Chained Mode */
    if ((DMACurrentTxDesc->Status & ETH_DMATXDESC_TCHM) != (uint32_t)RESET) {
        DMACurrentTxDesc = (ETH_DMADESCTypeDef *)(DMACurrentTxDesc->Buffer2NextDescAddr);
    }
    /* Ring Mode */
    else {
        if ((DMACurrentTxDesc->Status & ETH_DMATXDESC_TERM) != (uint32_t)RESET) {
            DMACurrentTxDesc = (ETH_DMADESCTypeDef *)(ETH_DMA->TDTAR);
        } else {
            DMACurrentTxDesc = (ETH_DMADESCTypeDef *)((uint32_t)DMACurrentTxDesc + ETH_DMATXDESC_SIZE + ((ETH_DMA->BCR & ETH_DMA_BCR_DPSL) >> 2));
        }
    }
    /* Return SUCCESS */
    return SUCCESS;
}

/**
  * @brief  Receive a packet data to application buffer.
  * @param  pbuf: Pointer on the application buffer.
  * @retval The Receive size(If framelength is equal to ERROR, the receiving unsuccessful)
  */
uint32_t ETH_HandleRxPkt(uint8_t *pbuf)
{
    uint32_t offset = 0, size = 0;

    /* Check the busy bit of Rx descriptor status */
    if ((DMACurrentRxDesc->Status & ETH_DMARXDESC_BUSY) != (uint32_t)RESET) {
        /* Return ERROR: the descriptor is busy due to own by the DMA */
        return ERROR;
    }

    if (((DMACurrentRxDesc->Status & ETH_DMARXDESC_ERRS) == (uint32_t)RESET) &&
            ((DMACurrentRxDesc->Status & ETH_DMARXDESC_LDES) != (uint32_t)RESET) &&
            ((DMACurrentRxDesc->Status & ETH_DMARXDESC_FDES) != (uint32_t)RESET)) {
        /* Get the Frame Length exclusive CRC */
        size = ((DMACurrentRxDesc->Status & ETH_DMARXDESC_FRML) >> ETH_DMARXDESC_FRAME_LENGTHSHIFT) - 4;
        for (offset = 0; offset < size; offset++) {
            (*(pbuf + offset)) = (*(__IO uint8_t *)((DMACurrentRxDesc->Buffer1Addr) + offset));
        }
    } else {
        /* Return ERROR */
        size = ERROR;
    }
    /* Enable reception */
    DMACurrentRxDesc->Status = ETH_DMARXDESC_BUSY;

    /* Check Rx Buffer unavailable flag status */
    if ((ETH_DMA->STR & ETH_DMA_STR_RBU) != (uint32_t)RESET) {
        /* Clear RBU ETHERNET DMA flag */
        ETH_DMA->STR = ETH_DMA_STR_RBU;
        /* Resume DMA reception by writing to the RPER register*/
        ETH_DMA->RPER = 0;
    }

    /* Update the ETHERNET DMA current Rx descriptor pointer to the next Rx decriptor in DMA Rx decriptor talbe*/
    /* Chained Mode */
    if ((DMACurrentRxDesc->ControlBufferSize & ETH_DMARXDESC_RCHM) != (uint32_t)RESET) {
        DMACurrentRxDesc = (ETH_DMADESCTypeDef *)(DMACurrentRxDesc->Buffer2NextDescAddr);
    }
    /* Ring Mode */
    else {
        if ((DMACurrentRxDesc->ControlBufferSize & ETH_DMARXDESC_RERR) != (uint32_t)RESET) {
            DMACurrentRxDesc = (ETH_DMADESCTypeDef *)(ETH_DMA->RDTAR);
        } else {
            DMACurrentRxDesc = (ETH_DMADESCTypeDef *)((uint32_t)DMACurrentRxDesc + ETH_DMARXDESC_SIZE + ((ETH_DMA->BCR & ETH_DMA_BCR_DPSL) >> 2));
        }
    }

    /* Return Frame size or ERROR */
    return (size);
}

/**
  * @brief  To obtain the received data length
  * @param  None
  * @retval Received frame length.
  */
uint32_t ETH_GetRxPktSize(void)
{
    uint32_t size = 0;

    if ((DMACurrentRxDesc->Status & ETH_DMARXDESC_BUSY) != (uint32_t)RESET) {
        return 0;
    }

    if (((DMACurrentRxDesc->Status & ETH_DMARXDESC_ERRS) != (uint32_t)RESET) ||
            ((DMACurrentRxDesc->Status & ETH_DMARXDESC_LDES) == (uint32_t)RESET) ||
            ((DMACurrentRxDesc->Status & ETH_DMARXDESC_FDES) == (uint32_t)RESET)) {
        ETH_DropRxPkt();

        return 0;
    }

    if (((DMACurrentRxDesc->Status & ETH_DMARXDESC_BUSY) == (uint32_t)RESET) &&
            ((DMACurrentRxDesc->Status & ETH_DMARXDESC_ERRS) == (uint32_t)RESET) &&
            ((DMACurrentRxDesc->Status & ETH_DMARXDESC_LDES) != (uint32_t)RESET) &&
            ((DMACurrentRxDesc->Status & ETH_DMARXDESC_FDES) != (uint32_t)RESET)) {
        /* Get the size of the received data including CRC */
        size = ETH_GetDMARxDescFrameLength(DMACurrentRxDesc);
    }

    /* Return Packet size */
    return size;
}

/**
  * @brief  Discard a Received packet
  * @param  None
  * @retval None
  */
void ETH_DropRxPkt(void)
{
    /* Enable reception */
    DMACurrentRxDesc->Status = ETH_DMARXDESC_BUSY;
    /* Chained Mode */
    if ((DMACurrentRxDesc->ControlBufferSize & ETH_DMARXDESC_RCHM) != (uint32_t)RESET) {
        DMACurrentRxDesc = (ETH_DMADESCTypeDef *)(DMACurrentRxDesc->Buffer2NextDescAddr);
    }
    /* Ring Mode */
    else {
        if ((DMACurrentRxDesc->ControlBufferSize & ETH_DMARXDESC_RERM) != (uint32_t)RESET) {
            DMACurrentRxDesc = (ETH_DMADESCTypeDef *)(ETH_DMA->RDTAR);
        } else {
            DMACurrentRxDesc = (ETH_DMADESCTypeDef *)((uint32_t)DMACurrentRxDesc + ETH_DMARXDESC_SIZE + ((ETH_DMA->BCR & ETH_DMA_BCR_DPSL) >> 2));
        }
    }
}

/* PHY */
/**
  * @brief Get PHY of ETHERNET parameters.
  * @param PHYAddr: PHY device address, devices number max is 32.
  * @param PHYReg: PHY register address, register address max is 32.
  *   Select one of the follwing values :
  *     @arg PHY_BCR: Tranceiver Basic Control Register
  *     @arg PHY_BSR: Tranceiver Basic Status Register
  *     @arg PHY_SR : Tranceiver Status Register
  *     @arg More PHY register could be read depending on the used PHY
  * @retval value read from the selected PHY register (if timeout return ERROR)
  */
uint16_t ETH_GetPHYRegisterValue(uint16_t PHYAddr, uint16_t PHYReg)
{
    uint32_t temp = 0;
    __IO uint32_t timeout = 0;

    /* Get the ETHERNET MAC_PHYAR value */
    temp = ETH_MAC->PHYAR;
    temp &= ~MAC_PHYAR_CLR_MASK;
    /* Configuration the PHY address register value */
    /* Set the PHY device address */
    temp |= (((uint32_t)PHYAddr << MAC_PHYAR_PHYADDRSHIFT) & ETH_MAC_PHYAR_PA);
    /* Set the PHY register address */
    temp |= (((uint32_t)PHYReg << MAC_PHYAR_PHYREGSHIFT) & ETH_MAC_PHYAR_PR);
    /* Set the read mode */
    temp &= ~ETH_MAC_PHYAR_PW;
    /* Set the PHY Busy bit */
    temp |= ETH_MAC_PHYAR_PB;
    ETH_MAC->PHYAR = temp;
    /* Check the PHY Busy flag status */
    do {
        timeout++;
        temp = ETH_MAC->PHYAR;
    } while ((temp & ETH_MAC_PHYAR_PB) && (timeout < (uint32_t)PHY_READ_TO));
    /* Return ERROR due to timeout */
    if (timeout == PHY_READ_TO) {
        return (uint16_t)ERROR;
    }

    /* Return PHY register selected value */
    return (uint16_t)(ETH_MAC->PHYDR);
}

/**
  * @brief Set PHY of ETHERNET parameters.
  * @param PHYAddr: PHY device address, devices number max is 32.
  * @param PHYReg: PHY register address, register address max is 32.
  *   Select one of the follwing values :
  *     @arg PHY_BCR    : Tranceiver Control Register
  *     @arg More PHY register could be written depending on the used PHY
  * @param  PHYValue: write to register value
  * @retval The Write to the selected PHY register result(ERROR or SUCCESS)
  */
uint32_t ETH_SetPHYRegisterValue(uint16_t PHYAddr, uint16_t PHYReg, uint16_t PHYValue)
{
    uint32_t temp = 0;
    __IO uint32_t timeout = 0;

    /* Get the ETHERNET MAC_PHYAR value */
    temp = ETH_MAC->PHYAR;
    temp &= ~MAC_PHYAR_CLR_MASK;
    /* Configuration the PHY register address value */
    /* Set the PHY device address */
    temp |= (((uint32_t)PHYAddr << MAC_PHYAR_PHYADDRSHIFT) & ETH_MAC_PHYAR_PA);
    /* Set the PHY register address */
    temp |= (((uint32_t)PHYReg << MAC_PHYAR_PHYREGSHIFT) & ETH_MAC_PHYAR_PR);
    /* Set the write mode */
    temp |= ETH_MAC_PHYAR_PW;
    /* Set the PHY Busy bit */
    temp |= ETH_MAC_PHYAR_PB;
    /* Set the PHY selected register value */
    ETH_MAC->PHYDR = PHYValue;
    ETH_MAC->PHYAR = temp;
    /* Check the PHY Busy flag status */
    do {
        timeout++;
        temp = ETH_MAC->PHYAR;
    } while ((temp & ETH_MAC_PHYAR_PB) && (timeout < (uint32_t)PHY_WRITE_TO));
    /* Return ERROR due to timeout */
    if (timeout == PHY_WRITE_TO) {
        return ERROR;
    }

    return SUCCESS;
}

/**
  * @brief  Enable or disable the PHY loopBack function by write PHY register.
  * @param  PHYAddr: PHY device address, devices number max is 32.
  * @param  NewValue: new value of the PHY loopBack mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval The Set PHYLoopBack mode result(ERROR or SUCCESS)
  */
uint32_t ETH_PHYLoopBack_Enable(uint16_t PHYAddr, TypeState NewValue)
{
    uint16_t temp = 0;

    /* Get the PHY BCR register value */
    temp = ETH_GetPHYRegisterValue(PHYAddr, PHY_BCR);

    if (NewValue != DISABLE) {
        /* Enable the PHY loopback mode */
        temp |= PHY_LOOPBACK;
    } else {
        /* Disable the PHY loopback mode (change to normal mode) */
        temp &= (uint16_t)(~(uint16_t)PHY_LOOPBACK);
    }
    /* Set the PHY BCR register with the new value */
    if (ETH_SetPHYRegisterValue(PHYAddr, PHY_BCR, temp) != (uint32_t)RESET) {
        return SUCCESS;
    } else {
        return ERROR;
    }
}

/* MAC */
/**
  * @brief  Enable or disable the MAC transmit function.
  * @param  NewValue: new value of the MAC transmit function.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_MACTransmission_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the MAC transmission */
        ETH_MAC->CFR |= ETH_MAC_CFR_TEN;
    } else {
        /* Disable the MAC transmission */
        ETH_MAC->CFR &= ~ETH_MAC_CFR_TEN;
    }
}

/**
  * @brief  Enable or disable the MAC receive function.
  * @param  NewValue: new value of the MAC reception.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_MACReception_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the MAC reception */
        ETH_MAC->CFR |= ETH_MAC_CFR_REN;
    } else {
        /* Disable the MAC reception */
        ETH_MAC->CFR &= ~ETH_MAC_CFR_REN;
    }
}

/**
  * @brief  Get the bit flag of the ETHERNET flow control busy status.
  * @param  None
  * @retval current flow control busy bit status
  */
TypeState ETH_GetFlowControlBusyBitState(void)
{
    /* Check the flow control busy bit status */
    if ((ETH_MAC->FCTLR & ETH_MAC_FCTLR_FLCBBKPA) != (uint32_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  Initiate a Pause Frame in Full-duplex mode only.
  * @param  None
  * @retval None
  */
void ETH_PauseFrameInit(void)
{
    /* Initiate pause control frame in full duplex mode*/
    ETH_MAC->FCTLR |= ETH_MAC_FCTLR_FLCBBKPA;
}

/**
  * @brief  Enable or disable the BackPressure requests in Half-duplex only.
  * @param  NewValue: new value of the BackPressure operation requests.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_BackPressureActivation_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the BackPressure requests */
        ETH_MAC->FCTLR |= ETH_MAC_FCTLR_FLCBBKPA;
    } else {
        /* Disable the BackPressure requests */
        ETH_MAC->FCTLR &= ~ETH_MAC_FCTLR_FLCBBKPA;
    }
}

/**
  * @brief  Get the status flag of ETH_MAC_ISR register.
  * @param  ETH_MAC_FLAG: the status flag of ETH_MAC_ISR register.
  *   Select one of the follwing values :
  *     @arg ETH_MAC_FLAG_TST  : Time stamp trigger flag
  *     @arg ETH_MAC_FLAG_MSCT : MSC transmit flag
  *     @arg ETH_MAC_FLAG_MSCR : MSC receive flag
  *     @arg ETH_MAC_FLAG_MSC  : MSC flag
  *     @arg ETH_MAC_FLAG_WUM  : WUM flag
  * @retval The current MAC bit selected status(SET or RESET).
  */
TypeState ETH_GetMACBitState(uint32_t ETH_MAC_FLAG)
{
    /* Check the ETH_MAC_FLAG status */
    if ((ETH_MAC->ISR & ETH_MAC_FLAG) != (uint32_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  Get the interrupt flag of ETH_MAC_ISR register.
  * @param  ETH_MAC_INT: the interrupt flag of ETH_MAC_ISR register.
  *   Select one of the follwing values :
  *     @arg ETH_MAC_INT_TST  : Time stamp trigger interrupt
  *     @arg ETH_MAC_INT_MSCT : MSC transmit interrupt
  *     @arg ETH_MAC_INT_MSCR : MSC receive interrupt
  *     @arg ETH_MAC_INT_MSC  : MSC interrupt
  *     @arg ETH_MAC_INT_WUM  : WUM interrupt
  * @retval The current MAC interrupt bit selected status(SET or RESET).
  */
TypeState ETH_GetMACIntBitState(uint32_t ETH_MAC_INT)
{
    /* Check the ETH_MAC_INT status */
    if ((ETH_MAC->ISR & ETH_MAC_INT) != (uint32_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

/**
  * @brief  Enable or disable the ETH_MAC_INT control bit.
  * @param  ETH_MAC_INT: the interrupt bit flag.
  *   Select one of the follwing values :
  *     @arg ETH_MAC_INT_TST : Time stamp trigger interrupt
  *     @arg ETH_MAC_INT_WUM : WUM interrupt
  * @param  NewValue: new value of the ETH_MAC_INT value.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_MACINTConfig(uint32_t ETH_MAC_INT, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the MAC interrupt */
        ETH_MAC->IMR &= (~(uint32_t)ETH_MAC_INT);
    } else {
        /* Disable the MAC interrupt */
        ETH_MAC->IMR |= ETH_MAC_INT;
    }
}

/**
  * @brief  Set the MAC address to MAC address register selected.
  * @param  addr: The MAC address register to selected.
  *  Select one of the follwing values :
  *     @arg ETH_MAC_ADDRESS0 : MAC Address0
  *     @arg ETH_MAC_ADDRESS1 : MAC Address1
  *     @arg ETH_MAC_ADDRESS2 : MAC Address2
  *     @arg ETH_MAC_ADDRESS3 : MAC Address3
  * @param buf: Pointer to application MAC address buffer(6 bytes).
  * @retval None
  */
void ETH_SetMACAddress(uint32_t addr, uint8_t *buf)
{
    uint32_t temp;

    temp = ((uint32_t)buf[5] << 8) | (uint32_t)buf[4];
    /* Set the selectecd MAC address high register */
    (*(__IO uint32_t *)(ETH_MAC_ADDR_HBASE + addr)) = temp;
    temp = ((uint32_t)buf[3] << 24) | ((uint32_t)buf[2] << 16) | ((uint32_t)buf[1] << 8) | buf[0];

    /* Set the selectecd MAC address low register */
    (*(__IO uint32_t *)(ETH_MAC_ADDR_LBASE + addr)) = temp;
}

/**
  * @brief  Get the MAC address from MAC address register selected.
  * @param  addr: The MAC addres to selected.
  *   Select one of the follwing values :
  *     @arg ETH_MAC_ADDRESS0 : MAC Address0
  *     @arg ETH_MAC_ADDRESS1 : MAC Address1
  *     @arg ETH_MAC_ADDRESS2 : MAC Address2
  *     @arg ETH_MAC_ADDRESS3 : MAC Address3
  * @param  buf: Pointer to application MAC address buffer(6 bytes).
  * @retval None
  */
void ETH_GetMACAddress(uint32_t addr, uint8_t *buf)
{
    uint32_t temp;

    /* Get the selectecd MAC address high register */
    temp = (*(__IO uint32_t *)(ETH_MAC_ADDR_HBASE + addr));

    buf[5] = ((temp >> 8) & (uint8_t)0xFF);
    buf[4] = (temp & (uint8_t)0xFF);
    /* Get the selectecd MAC address low register */
    temp = (*(__IO uint32_t *)(ETH_MAC_ADDR_LBASE + addr));
    buf[3] = ((temp >> 24) & (uint8_t)0xFF);
    buf[2] = ((temp >> 16) & (uint8_t)0xFF);
    buf[1] = ((temp >> 8) & (uint8_t)0xFF);
    buf[0] = (temp & (uint8_t)0xFF);
}

/**
  * @brief  Enable or disable the Address perfect filtering.
  * @param  addr: the MAC address register selected for prfect filtering.
  *   Select one of the follwing values :
  *     @arg ETH_MAC_ADDRESS1 : MAC Address1
  *     @arg ETH_MAC_ADDRESS2 : MAC Address2
  *     @arg ETH_MAC_ADDRESS3 : MAC Address3
  * @param  NewValue: new value of the MAC address register selected for perfect filtering.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_MACAddressPerfectFilter_Enable(uint32_t addr, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the perfect filtering to the MAC address register selected */
        (*(__IO uint32_t *)(ETH_MAC_ADDR_HBASE + addr)) |= ETH_MAC_A1HR_AFE;
    } else {
        /* Disable the perfect filtering to the MAC address register selected */
        (*(__IO uint32_t *)(ETH_MAC_ADDR_HBASE + addr)) &= (~(uint32_t)ETH_MAC_A1HR_AFE);
    }
}

/**
  * @brief  Set the selected MAC address filter type mode.
  * @param  addr: the MAC address to be used for filtering.
  *   Select one of the follwing values :
  *     @arg ETH_MAC_ADDRESS1 : MAC Address1
  *     @arg ETH_MAC_ADDRESS2 : MAC Address2
  *     @arg ETH_MAC_ADDRESS3 : MAC Address3
  * @param  Filterfield: the mode of receiving field for comparaison
  *   Select one of the follwing values :
  *     @arg ETH_MAC_ADDRESSFILTER_SA : Compare with the SA fields of the received frame.
  *     @arg ETH_MAC_ADDRESSFILTER_DA : Compare with the DA fields of the received frame.
  * @retval None
  */
void ETH_MACAddressFilterConfig(uint32_t addr, uint32_t Filterfield)
{
    if (Filterfield != ETH_MAC_ADDRESSFILTER_DA) {
        /* Compare with the SA fields of the received frame. */
        (*(__IO uint32_t *)(ETH_MAC_ADDR_HBASE + addr)) |= ETH_MAC_A1HR_SAF;
    } else {
        /* compare with the DA fields of the received frame. */
        (*(__IO uint32_t *)(ETH_MAC_ADDR_HBASE + addr)) &= (~(uint32_t)ETH_MAC_A1HR_SAF);
    }
}

/**
  * @brief  Set the selected MAC address filter maskbyte.
  * @param  addr: the MAC address to be used for filtering
  *   Select one of the follwing values :
  *     @arg ETH_MAC_ADDRESS1 : MAC Address1
  *     @arg ETH_MAC_ADDRESS2 : MAC Address2
  *     @arg ETH_MAC_ADDRESS3 : MAC Address3
  * @param addrmask: the address bytes be selected for address filtering comparaison
  *   Select one of the follwing values :
  *     @arg ETH_MAC_ADDRESSMASK_BYTE6 : Mask MAC Address high register bits [15:8].
  *     @arg ETH_MAC_ADDRESSMASK_BYTE5 : Mask MAC Address high register bits [7:0].
  *     @arg ETH_MAC_ADDRESSMASK_BYTE4 : Mask MAC Address low register bits [31:24].
  *     @arg ETH_MAC_ADDRESSMASK_BYTE3 : Mask MAC Address low register bits [23:16].
  *     @arg ETH_MAC_ADDRESSMASK_BYTE2 : Mask MAC Address low register bits [15:8].
  *     @arg ETH_MAC_ADDRESSMASK_BYTE1 : Mask MAC Address low register bits [7:0].
  * @retval None
  */
void ETH_MACAddressFilterMaskBytesConfig(uint32_t addr, uint32_t addrmask)
{
    /* Clear the MB bit of selected MAC address */
    (*(__IO uint32_t *)(ETH_MAC_ADDR_HBASE + addr)) &= (~(uint32_t)ETH_MAC_A1HR_MB);
    /* Set the mask bytes of selected Filetr */
    (*(__IO uint32_t *)(ETH_MAC_ADDR_HBASE + addr)) |= addrmask;
}

/* DMA Tx/Rx Desciptors */

/**
  * @brief  Initialize the DMA Tx descriptors's parameters in chain mode.
  * @param  DMATxDescTab: Pointer to the first Tx descriptor table
  * @param  pTxBuff: Pointer to the first TxBuffer table
  * @param  TxBuffCnt: the used Tx desc num in the table
  * @retval None
  */
void ETH_DMATxDescChainModeInit(ETH_DMADESCTypeDef *DMATxDescTab, uint8_t *pTxBuff, uint32_t TxBuffCnt)
{
    uint32_t num = 0;
    ETH_DMADESCTypeDef *DMATxDesc;

    DMACurrentTxDesc = DMATxDescTab;
    /* Configuration each DMATxDesc descriptor */
    for (num = 0; num < TxBuffCnt; num++) {
        /* Get the pointer to the next descriptor of the Tx Desc table */
        DMATxDesc = DMATxDescTab + num;
        /* Set TCH bit with desc status */
        DMATxDesc->Status = ETH_DMATXDESC_TCHM;

        /* Set Buffer1 address pointer to application buffer */
        DMATxDesc->Buffer1Addr = (uint32_t)(&pTxBuff[num * ETH_MAX_FRAME_SIZE]);

        if (num < (TxBuffCnt - 1)) {
            /* Buffer2NextDescAddr equal to next descriptor address in the Tx Desc table */
            DMATxDesc->Buffer2NextDescAddr = (uint32_t)(DMATxDescTab + num + 1);
        } else {
            /* When it is the last descriptor, Buffer2NextDescAddr equal to first descriptor address in the Tx Desc table */
            DMATxDesc->Buffer2NextDescAddr = (uint32_t) DMATxDescTab;
        }
    }
    ETH_DMA->TDTAR = (uint32_t) DMATxDescTab;
}

/**
  * @brief  Initialize the DMA Tx descriptors's parameters in ring mode.
  * @param  DMATxDescTab: Pointer to the first Tx descriptor table
  * @param  pTxBuff1: Pointer to the first TxBuffer1 table
  * @param  pTxBuff2: Pointer to the first TxBuffer2 table
  * @param  TxBuffCnt: the used Tx desc num in the table
  * @retval None
  */
void ETH_DMATxDescRingModeInit(ETH_DMADESCTypeDef *DMATxDescTab, uint8_t *pTxBuff1, uint8_t *pTxBuff2, uint32_t TxBuffCnt)
{
    uint32_t num = 0;
    ETH_DMADESCTypeDef *DMATxDesc;

    DMACurrentTxDesc = DMATxDescTab;
    /* Configuration each DMATxDesc descriptor */
    for (num = 0; num < TxBuffCnt; num++) {
        /* Get the pointer to the next descriptor of the Tx Desc table */
        DMATxDesc = DMATxDescTab + num;
        /* Set Buffer1 address pointer to application buffer1 */
        DMATxDesc->Buffer1Addr = (uint32_t)(&pTxBuff1[num * ETH_MAX_FRAME_SIZE]);

        /* Set Buffer2 address pointer to application buffer2 */
        DMATxDesc->Buffer2NextDescAddr = (uint32_t)(&pTxBuff2[num * ETH_MAX_FRAME_SIZE]);

        if (num == (TxBuffCnt - 1)) {
            /* Set ETH_DMATXDESC_TERM bit as transmitting End */
            DMATxDesc->Status = ETH_DMATXDESC_TERM;
        }
    }
    ETH_DMA->TDTAR = (uint32_t) DMATxDescTab;
}

/**
  * @brief  Get the bit flag of ETHERNET DMA Tx Desc.
  * @param  DMATxDesc: pointer to a DMA Tx descriptor
  * @param  ETH_DMATxDescFlag: the flag of Tx descriptor status.
  *   Select one of the follwing values :
  *     @arg ETH_DMATXDESC_BUSY  : BUSY bit: descriptor is owned by DMA engine
  *     @arg ETH_DMATXDESC_INTC  : Interrupt on completetion
  *     @arg ETH_DMATXDESC_LSG   : Last Segment
  *     @arg ETH_DMATXDESC_FSG   : First Segment
  *     @arg ETH_DMATXDESC_DCRC  : Disable CRC
  *     @arg ETH_DMATXDESC_DPAD  : Disable Pad
  *     @arg ETH_DMATXDESC_TTSEN : Transmit Time Stamp Enable
  *     @arg ETH_DMATXDESC_TERM  : Transmit End of Ring
  *     @arg ETH_DMATXDESC_TCHM  : Second Address Chained
  *     @arg ETH_DMATXDESC_TTMSS : Tx Time Stamp Status
  *     @arg ETH_DMATXDESC_IPHE  : IP Header Error
  *     @arg ETH_DMATXDESC_ES    : Error summary
  *     @arg ETH_DMATXDESC_JT    : Jabber Timeout
  *     @arg ETH_DMATXDESC_FRMF  : Frame Flushed: DMA/MTL flushed the frame due to SW flush
  *     @arg ETH_DMATXDESC_IPPE  : IP Payload Error
  *     @arg ETH_DMATXDESC_LCA   : Loss of Carrier: carrier lost during tramsmission
  *     @arg ETH_DMATXDESC_NCA   : No Carrier: no carrier signal from the tranceiver
  *     @arg ETH_DMATXDESC_LCO   : Late Collision: transmission aborted due to collision
  *     @arg ETH_DMATXDESC_ECO   : Excessive Collision: transmission aborted after 16 collisions
  *     @arg ETH_DMATXDESC_VFRM  : VLAN Frame
  *     @arg ETH_DMATXDESC_COCNT : Collision Count
  *     @arg ETH_DMATXDESC_EXD   : Excessive Deferral
  *     @arg ETH_DMATXDESC_UFE   : Underflow Error: late data arrival from the memory
  *     @arg ETH_DMATXDESC_DB    : Deferred Bit
  * @retval The current ETH_DMATxDescFlag selected bit status(SET or RESET).
  */
TypeState ETH_GetDMATxDescBitState(ETH_DMADESCTypeDef *DMATxDesc, uint32_t ETH_DMATxDescFlag)
{
    if ((DMATxDesc->Status & ETH_DMATxDescFlag) != (uint32_t)RESET) {
        /* ETH_DMATxDescFlag is set */
        return SET;
    } else {
        /* ETH_DMATxDescFlag is reset */
        return RESET;
    }
}

/**
  * @brief  Get the DMA Tx Desc collision count.
  * @param  DMATxDesc: pointer to a DMA Tx descriptor
  * @retval The value of Transmit descriptor collision counter.
  */
uint32_t ETH_GetDMATxDescCollisionCount(ETH_DMADESCTypeDef *DMATxDesc)
{
    return ((DMATxDesc->Status & ETH_DMATXDESC_COCNT) >> ETH_DMATXDESC_COLLISION_COUNTSHIFT);
}

/**
  * @brief  Set the DMA Tx Desc Busy bit for DMA or CPU.
  * @param  DMATxDesc: Pointer on a Transmit descriptor
  * @retval None
  */
void ETH_SetDMATxDescBusyBit(ETH_DMADESCTypeDef *DMATxDesc)
{
    DMATxDesc->Status |= ETH_DMATXDESC_BUSY;
}

/**
  * @brief  Enable or disable the ETH_DMATXDESC_INTC control bit.
  * @param  DMATxDesc: Pointer to a Tx descriptor
  * @param  NewValue: new value of the ETH_DMATXDESC_INTC control bit.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_DMATxDescTransmitINTConfig(ETH_DMADESCTypeDef *DMATxDesc, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the DMA Tx Desc after the frame has been transmitted Set Transmit interrupt */
        DMATxDesc->Status |= ETH_DMATXDESC_INTC;
    } else {
        /* Disable the DMA Tx Desc after the frame has been transmitted Set Transmit interrupt */
        DMATxDesc->Status &= (~(uint32_t)ETH_DMATXDESC_INTC);
    }
}

/**
  * @brief  Enable or disable the DMATxDesc_FrameSegment control bit.
  * @param  DMATxDesc: Pointer to a Tx descriptor
  * @param  DMATxDesc_Segment: the actual Tx buffer contain first or last segment.
  *   Select one of the follwing values :
  *     @arg ETH_DMATXDESC_LASTSEGMENT  : current Tx desc selected contain last segment
  *     @arg ETH_DMATXDESC_FIRSTSEGMENT : current Tx desc selected contain first segment
  * @retval None
  */
void ETH_SetDMATxDescFrameSegment(ETH_DMADESCTypeDef *DMATxDesc, uint32_t DMATxDesc_Segment)
{
    DMATxDesc->Status |= DMATxDesc_Segment;
}

/**
  * @brief  Set the DMA Tx Desc Checksum Insertion mode.
  * @param  DMATxDesc: pointer to a DMA Tx descriptor
  * @param  DMATxDesc_Checksum: the type of DMA Tx descriptor checksum insertion.
  *   Select one of the follwing values :
  *     @arg ETH_DMATXDESC_CHECKSUMDISABLE           : Checksum bypass
  *     @arg ETH_DMATXDESC_CHECKSUMIPV4HEADER        : IPv4 header checksum
  *     @arg ETH_DMATXDESC_CHECKSUMTCPUDPICMPSEGMENT : TCP/UDP/ICMP checksum. Pseudo header checksum is assumed to be present
  *     @arg ETH_DMATXDESC_CHECKSUMTCPUDPICMPFULL    : TCP/UDP/ICMP checksum fully in hardware including pseudo header
  * @retval None
  */
void ETH_SetDMATxDescChecksumInsertion(ETH_DMADESCTypeDef *DMATxDesc, uint32_t DMATxDesc_Checksum)
{
    DMATxDesc->Status |= DMATxDesc_Checksum;
}

/**
  * @brief  Enable or disable the DMA Tx descriptor CRC function.
  * @param  DMATxDesc: pointer to a DMA Tx descriptor
  * @param  NewValue: new value of the DMA Tx descriptor CRC function.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_DMATxDescCRC_Enable(ETH_DMADESCTypeDef *DMATxDesc, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the DMATxDesc CRC */
        DMATxDesc->Status &= (~(uint32_t)ETH_DMATXDESC_DCRC);
    } else {
        /* Disable the DMATxDesc CRC */
        DMATxDesc->Status |= ETH_DMATXDESC_DCRC;
    }
}

/**
  * @brief  Enable or disable the DMA Tx descriptor end of ring.
  * @param  DMATxDesc: pointer to a DMA Tx descriptor
  * @param  NewValue: new value of the DMA Tx descriptor end of ring.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_DMATxDescEndOfRing_Enable(ETH_DMADESCTypeDef *DMATxDesc, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the DMATxDesc end of ring */
        DMATxDesc->Status |= ETH_DMATXDESC_TERM;
    } else {
        /* Disable the DMATxDesc end of ring */
        DMATxDesc->Status &= (~(uint32_t)ETH_DMATXDESC_TERM);
    }
}

/**
  * @brief  Enable or disable the DMA Tx descriptor second address chained.
  * @param  DMATxDesc: pointer to a DMA Tx descriptor
  * @param  NewValue: new value of the DMA Tx descriptor second address chained.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_DMATxDescSecondAddressChained_Enable(ETH_DMADESCTypeDef *DMATxDesc, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the DMATxDesc second address chained */
        DMATxDesc->Status |= ETH_DMATXDESC_TCHM;
    } else {
        /* Disable the DMATxDesc second address chained */
        DMATxDesc->Status &= (~(uint32_t)ETH_DMATXDESC_TCHM);
    }
}

/**
  * @brief  Enable or disable auto padding when transmit frame shorter than 64 bytes.
  * @param  DMATxDesc: pointer to a DMA Tx descriptor
  * @param  NewValue: new value of the auto padding status.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_DMATxDescShortFramePadding_Enable(ETH_DMADESCTypeDef *DMATxDesc, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the DMATxDesc short frame padding */
        DMATxDesc->Status &= (~(uint32_t)ETH_DMATXDESC_DPAD);
    } else {
        /* Disable the DMATxDesc short frame padding */
        DMATxDesc->Status |= ETH_DMATXDESC_DPAD;
    }
}

/**
  * @brief  Enable or disable the DMA Tx descriptor time stamp function.
  * @param  DMATxDesc: pointer to a DMA Tx descriptor
  * @param  NewValue: new value of the DMA Tx descriptor time stamp.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_DMATxDescTimeStamp_Enable(ETH_DMADESCTypeDef *DMATxDesc, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the DMATxDesc time stamp */
        DMATxDesc->Status |= ETH_DMATXDESC_TTSEN;
    } else {
        /* Disable the DMATxDesc time stamp */
        DMATxDesc->Status &= (~(uint32_t)ETH_DMATXDESC_TTSEN);
    }
}

/**
  * @brief  Set the frame length by configures the DMA Tx Desc buffer1 and buffer2 sizes.
  * @param  DMATxDesc: Pointer to a Tx descriptor
  * @param  Buffer1Size: the Tx buffer1 size.
  * @param  Buffer2Size: the Tx buffer2 size, set to 0 indicates it is not being used.
  * @retval None
  */
void ETH_SetDMATxDescBufferSize(ETH_DMADESCTypeDef *DMATxDesc, uint32_t Buffer1Size, uint32_t Buffer2Size)
{
    DMATxDesc->ControlBufferSize |= (Buffer1Size | (Buffer2Size << ETH_DMATXDESC_BUFFER2_SIZESHIFT));
}

/**
  * @brief  Initialize the DMA Rx descriptors's parameters in chain mode.
  * @param  DMARxDescTab: Pointer to the first Rx descriptor table
  * @param  pRxBuff: Pointer to the first RxBuffer table
  * @param  RxBuffCnt: the used Rx desc num in the table
  * @retval None
  */
void ETH_DMARxDescChainModeInit(ETH_DMADESCTypeDef *DMARxDescTab, uint8_t *pRxBuff, uint32_t RxBuffCnt)
{
    uint32_t num = 0;
    ETH_DMADESCTypeDef *DMARxDesc;

    DMACurrentRxDesc = DMARxDescTab;
    /* Configuration each DMARxDesc descriptor */
    for (num = 0; num < RxBuffCnt; num++) {
        /* Get the pointer to the next descriptor of the Rx Desc table */
        DMARxDesc = DMARxDescTab + num;
        DMARxDesc->Status = ETH_DMARXDESC_BUSY;

        /* Set TCH bit and buffer1 size */
        DMARxDesc->ControlBufferSize = ETH_DMARXDESC_RCHM | (uint32_t)ETH_MAX_FRAME_SIZE;
        /* Set Buffer1 address pointer to application buffer */
        DMARxDesc->Buffer1Addr = (uint32_t)(&pRxBuff[num * ETH_MAX_FRAME_SIZE]);

        if (num < (RxBuffCnt - 1)) {
            /* Buffer2NextDescAddr equal to next descriptor address in the Rx Desc table */
            DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab + num + 1);
        } else {
            /* When it is the last descriptor, Buffer2NextDescAddr equal to first descriptor address in the Rx Desc table */
            DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab);
        }
    }

    ETH_DMA->RDTAR = (uint32_t) DMARxDescTab;
}

/**
  * @brief  Initialize the DMA Rx descriptors's parameters in ring mode.
  * @param  DMARxDescTab: Pointer to the first Rx descriptor table
  * @param  pRxBuff1: Pointer to the first RxBuffer1 table
  * @param  pRxBuff2: Pointer to the first RxBuffer2 table
  * @param  RxBuffCnt: the used Rx descriptor num in the table
  * @retval None
  */
void ETH_DMARxDescRingModeInit(ETH_DMADESCTypeDef *DMARxDescTab, uint8_t *pRxBuff1, uint8_t *pRxBuff2, uint32_t RxBuffCnt)
{
    uint32_t num = 0;
    ETH_DMADESCTypeDef *DMARxDesc;

    DMACurrentRxDesc = DMARxDescTab;
    /* Configuration each DMARxDesc descriptor */
    for (num = 0; num < RxBuffCnt; num++) {
        /* Get the pointer to the next descriptor of the Rx Desc table */
        DMARxDesc = DMARxDescTab + num;
        DMARxDesc->Status = ETH_DMARXDESC_BUSY;
        DMARxDesc->ControlBufferSize = ETH_MAX_FRAME_SIZE;
        /* Set Buffer1 address pointer to application buffer1 */
        DMARxDesc->Buffer1Addr = (uint32_t)(&pRxBuff1[num * ETH_MAX_FRAME_SIZE]);

        /* Set Buffer2 address pointer to application buffer2 */
        DMARxDesc->Buffer2NextDescAddr = (uint32_t)(&pRxBuff2[num * ETH_MAX_FRAME_SIZE]);

        if (num == (RxBuffCnt - 1)) {
            /* Set ETH_DMARXDESC_RERR bit as Receive End */
            DMARxDesc->ControlBufferSize |= ETH_DMARXDESC_RERR;
        }
    }

    ETH_DMA->RDTAR = (uint32_t) DMARxDescTab;
}

/**
  * @brief  Get the bit flag of ETHERNET Rx descriptor.
  * @param  DMARxDesc: pointer to a DMA Rx descriptor
  * @param  ETH_DMARxDescFlag: the flag of Rx descriptor status.
  *   Select one of the follwing values :
  *     @arg ETH_DMARXDESC_BUSY : Descriptor is owned by DMA engine
  *     @arg ETH_DMARXDESC_DAFF : DA Filter Fail for the rx frame
  *     @arg ETH_DMARXDESC_ERRS : Error summary
  *     @arg ETH_DMARXDESC_DERR : Desciptor error: no more descriptors for receive frame
  *     @arg ETH_DMARXDESC_SAFF : SA Filter Fail for the received frame
  *     @arg ETH_DMARXDESC_LERR : Frame size not matching with length field
  *     @arg ETH_DMARXDESC_OERR : Overflow Error: Frame was damaged due to buffer overflow
  *     @arg ETH_DMARXDESC_VTAG : VLAN Tag: received frame is a VLAN frame
  *     @arg ETH_DMARXDESC_FDES : First descriptor of the frame
  *     @arg ETH_DMARXDESC_LDES : Last descriptor of the frame
  *     @arg ETH_DMARXDESC_IPHCERR : IPC Checksum Error/Giant Frame: Rx Ipv4 header checksum error
  *     @arg ETH_DMARXDESC_LCO   : Late collision occurred during reception
  *     @arg ETH_DMARXDESC_FRMT  : Frame type - Ethernet, otherwise 802.3
  *     @arg ETH_DMARXDESC_RWDT  : Receive Watchdog Timeout: watchdog timer expired during reception
  *     @arg ETH_DMARXDESC_RERR  : Receive error: error reported by MII interface
  *     @arg ETH_DMARXDESC_DERR  : Dribble bit error: frame contains non int multiple of 8 bits
  *     @arg ETH_DMARXDESC_CERR  : CRC error
  *     @arg ETH_DMARXDESC_PCERR : Rx MAC Address/Payload Checksum Error: Rx MAC address matched/ Rx Payload Checksum Error
  * @retval The current ETH_DMARxDescFlag selected bit status(SET or RESET).
  */
TypeState ETH_GetDMARxDescBitState(ETH_DMADESCTypeDef *DMARxDesc, uint32_t ETH_DMARxDescFlag)
{
    if ((DMARxDesc->Status & ETH_DMARxDescFlag) != (uint32_t)RESET) {
        /* ETH_DMARxDescFlag is set */
        return SET;
    } else {
        /* ETH_DMARxDescFlag is reset */
        return RESET;
    }
}

/**
  * @brief  Set the DMA Rx Desc busy bit for DMA or CPU
  * @param  DMARxDesc: Pointer to a Rx descriptor
  * @retval None
  */
void ETH_SetDMARxDescBusyBit(ETH_DMADESCTypeDef *DMARxDesc)
{
    DMARxDesc->Status |= ETH_DMARXDESC_BUSY;
}

/**
  * @brief  Get the DMA Rx Desc frame length.
  * @param  DMARxDesc: pointer to a DMA Rx descriptor
  * @retval Received frame length of the Rx descriptor selected.
  */
uint32_t ETH_GetDMARxDescFrameLength(ETH_DMADESCTypeDef *DMARxDesc)
{
    return ((DMARxDesc->Status & ETH_DMARXDESC_FRML) >> ETH_DMARXDESC_FRAME_LENGTHSHIFT);
}

/**
  * @brief  Enable or disable the DMA Rx descriptor receive interrupt.
  * @param  DMARxDesc: Pointer to a Rx descriptor
  * @param  NewValue: new value of the DMA Rx descriptor interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_DMARxDescReceiveINTConfig(ETH_DMADESCTypeDef *DMARxDesc, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the DMARxDesc receive interrupt */
        DMARxDesc->ControlBufferSize &= (~(uint32_t)ETH_DMARXDESC_DINTC);
    } else {
        /* Disable the DMARxDesc receive interrupt */
        DMARxDesc->ControlBufferSize |= ETH_DMARXDESC_DINTC;
    }
}

/**
  * @brief  Enable or disable the DMA Rx descriptor end of ring.
  * @param  DMARxDesc: pointer to a DMA Rx descriptor
  * @param  NewValue: new value of the DMA Rx descriptor end of ring.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_DMARxDescEndOfRing_Enable(ETH_DMADESCTypeDef *DMARxDesc, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the DMARxDesc end of ring */
        DMARxDesc->ControlBufferSize |= ETH_DMARXDESC_RERR;
    } else {
        /* Disable the DMARxDesc end of ring */
        DMARxDesc->ControlBufferSize &= (~(uint32_t)ETH_DMARXDESC_RERR);
    }
}

/**
  * @brief  Enable or disable the DMA Rx descriptor second address chained.
  * @param  DMARxDesc: pointer to a DMA Rx descriptor
  * @param  NewValue: new value of the DMA Rx descriptor second address chained.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_DMARxDescSecondAddressChained_Enable(ETH_DMADESCTypeDef *DMARxDesc, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the DMARxDesc second address chained */
        DMARxDesc->ControlBufferSize |= ETH_DMARXDESC_RCHM;
    } else {
        /* Disable the DMARxDesc second address chained */
        DMARxDesc->ControlBufferSize &= (~(uint32_t)ETH_DMARXDESC_RCHM);
    }
}

/**
  * @brief  Get the ETHERNET DMA Rx Desc buffer size.
  * @param  DMARxDesc: pointer to a DMA Rx descriptor
  * @param  DMARxDesc_BufferSelect: the DMA Rx descriptor buffer.
  *   Select one of the follwing values :
  *     @arg ETH_DMARXDESC_BUFFER1 : DMA Rx Desc Buffer1
  *     @arg ETH_DMARXDESC_BUFFER2 : DMA Rx Desc Buffer2
  * @retval The Receive descriptor selected buffer size(buffer1 or buffer2).
  */
uint32_t ETH_GetDMARxDescBufferSize(ETH_DMADESCTypeDef *DMARxDesc, uint32_t DMARxDesc_BufferSelect)
{
    if (DMARxDesc_BufferSelect != ETH_DMARXDESC_BUFFER1) {
        return ((DMARxDesc->ControlBufferSize & ETH_DMARXDESC_RB2S) >> ETH_DMARXDESC_BUFFER2_SIZESHIFT);
    } else {
        return (DMARxDesc->ControlBufferSize & ETH_DMARXDESC_RB1S);
    }
}

/* DMA */
/**
  * @brief  Resets all MAC subsystem.
  * @param  None
  * @retval None
  */
void ETH_SoftReset(void)
{
    ETH_DMA->BCR |= ETH_DMA_BCR_SWR;
}

/**
  * @brief  Get the bit flag of ETHERNET software reset.
  * @param  None
  * @retval The current DMA Bus Mode register SWR bit status(SET or RESET).
  */
TypeState ETH_GetSoftResetStatus(void)
{
    if ((ETH_DMA->BCR & ETH_DMA_BCR_SWR) != (uint32_t)RESET) {
        /* The ETH_DMA_BCR_SWR bit is set */
        return SET;
    } else {
        /* The ETH_DMA_BCR_SWR bit is reset */
        return RESET;
    }
}

/**
  * @brief  Get the bit flag of specified ETHERNET DMA.
  * @param  ETH_DMA_FLAG: the flag of ETHERNET DMA_STR register.
  *   Select one of the follwing values :
  *     @arg ETH_DMA_FLAG_TST : Time-stamp trigger flag
  *     @arg ETH_DMA_FLAG_WUM : WUM flag
  *     @arg ETH_DMA_FLAG_MSC : MSC flag
  *     @arg ETH_DMA_FLAG_DATATRANSFERERROR : Error bits 0-data buffer, 1-desc. access
  *     @arg ETH_DMA_FLAG_READWRITEERROR    : Error bits 0-write trnsf, 1-read transfr
  *     @arg ETH_DMA_FLAG_ACCESSERROR       : Error bits 0-Rx DMA, 1-Tx DMA
  *     @arg ETH_DMA_FLAG_NIS : Normal interrupt summary flag
  *     @arg ETH_DMA_FLAG_AIS : Abnormal interrupt summary flag
  *     @arg ETH_DMA_FLAG_ER  : Early receive flag
  *     @arg ETH_DMA_FLAG_FBE : Fatal bus error flag
  *     @arg ETH_DMA_FLAG_ET  : Early transmit flag
  *     @arg ETH_DMA_FLAG_RWT : Receive watchdog timeout flag
  *     @arg ETH_DMA_FLAG_RPS : Receive process stopped flag
  *     @arg ETH_DMA_FLAG_RBU : Receive buffer unavailable flag
  *     @arg ETH_DMA_FLAG_R   : Receive flag
  *     @arg ETH_DMA_FLAG_TU  : Underflow flag
  *     @arg ETH_DMA_FLAG_RO  : Overflow flag
  *     @arg ETH_DMA_FLAG_TJT : Transmit jabber timeout flag
  *     @arg ETH_DMA_FLAG_TBU : Transmit buffer unavailable flag
  *     @arg ETH_DMA_FLAG_TPS : Transmit process stopped flag
  *     @arg ETH_DMA_FLAG_T   : Transmit flag
  * @retval The current ETH_DMA_FLAG selected bit status(SET or RESET).
  */
TypeState ETH_GetDMABitState(uint32_t ETH_DMA_FLAG)
{
    if ((ETH_DMA->STR & ETH_DMA_FLAG) != (uint32_t)RESET) {
        /* ETH_DMA_FLAG is set */
        return SET;
    } else {
        /* ETH_DMA_FLAG is reset */
        return RESET;
    }
}

/**
  * @brief  Clear the ETHERNET¡¯s DMA bit flag.
  * @param  ETH_DMA_FLAG: the flag of ETH_DMA_STR register to clear.
  *   Select one of the follwing values :
  *     @arg ETH_DMA_FLAG_NIS : Normal interrupt summary flag
  *     @arg ETH_DMA_FLAG_AIS : Abnormal interrupt summary flag
  *     @arg ETH_DMA_FLAG_ER  : Early receive flag
  *     @arg ETH_DMA_FLAG_FBE : Fatal bus error flag
  *     @arg ETH_DMA_FLAG_ETI : Early transmit flag
  *     @arg ETH_DMA_FLAG_RWT : Receive watchdog timeout flag
  *     @arg ETH_DMA_FLAG_RPS : Receive process stopped flag
  *     @arg ETH_DMA_FLAG_RBU : Receive buffer unavailable flag
  *     @arg ETH_DMA_FLAG_R   : Receive flag
  *     @arg ETH_DMA_FLAG_TU  : Transmit Underflow flag
  *     @arg ETH_DMA_FLAG_RO  : Receive Overflow flag
  *     @arg ETH_DMA_FLAG_TJT : Transmit jabber timeout flag
  *     @arg ETH_DMA_FLAG_TBU : Transmit buffer unavailable flag
  *     @arg ETH_DMA_FLAG_TPS : Transmit process stopped flag
  *     @arg ETH_DMA_FLAG_T   : Transmit flag
  * @retval None
  */
void ETH_DMAClearBitState(uint32_t ETH_DMA_FLAG)
{
    ETH_DMA->STR = (uint32_t) ETH_DMA_FLAG;
}

/**
  * @brief  Get the bit flag of DMA interrupt.
  * @param  ETH_DMA_INT: the interrupt source flag of ETHERNET DMA_STR register.
  *   Select one of the follwing values :
  *     @arg ETH_DMA_INT_TST : Time-stamp trigger interrupt
  *     @arg ETH_DMA_INT_WUM : WUM interrupt
  *     @arg ETH_DMA_INT_MSC : MSC interrupt
  *     @arg ETH_DMA_INT_NIS : Normal interrupt summary
  *     @arg ETH_DMA_INT_AIS : Abnormal interrupt summary
  *     @arg ETH_DMA_INT_ER  : Early receive interrupt
  *     @arg ETH_DMA_INT_FBE : Fatal bus error interrupt
  *     @arg ETH_DMA_INT_ET  : Early transmit interrupt
  *     @arg ETH_DMA_INT_RWT : Receive watchdog timeout interrupt
  *     @arg ETH_DMA_INT_RPS : Receive process stopped interrupt
  *     @arg ETH_DMA_INT_RBU : Receive buffer unavailable interrupt
  *     @arg ETH_DMA_INT_R   : Receive interrupt
  *     @arg ETH_DMA_INT_TU  : Underflow interrupt
  *     @arg ETH_DMA_INT_RO  : Overflow interrupt
  *     @arg ETH_DMA_INT_TJT : Transmit jabber timeout interrupt
  *     @arg ETH_DMA_INT_TBU : Transmit buffer unavailable interrupt
  *     @arg ETH_DMA_INT_TPS : Transmit process stopped interrupt
  *     @arg ETH_DMA_INT_T   : Transmit interrupt
  * @retval The current ETH_DMA_INT selected bit status(SET or RESET).
  */
TypeState ETH_GetDMAIntBitState(uint32_t ETH_DMA_INT)
{
    if ((ETH_DMA->STR & ETH_DMA_INT) != (uint32_t)RESET) {
        /* ETH_DMA_INT is set */
        return SET;
    } else {
        /* ETH_DMA_INT is reset */
        return RESET;
    }
}

/**
  * @brief  Clear the ETHERNET¡¯s DMA IT bit flag.
  * @param  ETH_DMA_INT: the interrupt source flag of ETH_DMA_STR register to clear.
  *   Select one of the follwing values :
  *     @arg ETH_DMA_INT_NIS : Normal interrupt summary
  *     @arg ETH_DMA_INT_AIS : Abnormal interrupt summary
  *     @arg ETH_DMA_INT_ER  : Early receive interrupt
  *     @arg ETH_DMA_INT_FBE : Fatal bus error interrupt
  *     @arg ETH_DMA_INT_ETI : Early transmit interrupt
  *     @arg ETH_DMA_INT_RWT : Receive watchdog timeout interrupt
  *     @arg ETH_DMA_INT_RPS : Receive process stopped interrupt
  *     @arg ETH_DMA_INT_RBU : Receive buffer unavailable interrupt
  *     @arg ETH_DMA_INT_R   : Receive interrupt
  *     @arg ETH_DMA_INT_TU  : Transmit Underflow interrupt
  *     @arg ETH_DMA_INT_RO  : Receive Overflow interrupt
  *     @arg ETH_DMA_INT_TJT : Transmit jabber timeout interrupt
  *     @arg ETH_DMA_INT_TBU : Transmit buffer unavailable interrupt
  *     @arg ETH_DMA_INT_TPS : Transmit process stopped interrupt
  *     @arg ETH_DMA_INT_T   : Transmit interrupt
  * @retval None
  */
void ETH_DMAClearIntBitState(uint32_t ETH_DMA_INT)
{
    ETH_DMA->STR = (uint32_t) ETH_DMA_INT;
}

/**
  * @brief  Get the DMA Transmit Process State.
  * @param  None
  * @retval The current DMA Transmit Process State:
  *   Select one of the follwing values :
  *     - ETH_DMA_TransmitProcess_Stopped   : Stopped - Reset or Stop Tx Command issued
  *     - ETH_DMA_TransmitProcess_Fetching  : Running - fetching the Tx descriptor
  *     - ETH_DMA_TransmitProcess_Waiting   : Running - waiting for status
  *     - ETH_DMA_TransmitProcess_Reading   : unning - reading the data from host memory
  *     - ETH_DMA_TransmitProcess_Suspended : Suspended - Tx Desciptor unavailabe
  *     - ETH_DMA_TransmitProcess_Closing   : Running - closing Rx descriptor
  */
uint32_t ETH_GetTransmitProcessState(void)
{
    return ((uint32_t)(ETH_DMA->STR & ETH_DMA_STR_TS));
}

/**
  * @brief  Get the DMA Receive Process State.
  * @param  None
  * @retval The current DMA Receive Process State:
  *   Select one of the follwing values :
  *     - ETH_DMA_ReceiveProcess_Stopped   : Stopped - Reset or Stop Rx Command issued
  *     - ETH_DMA_ReceiveProcess_Fetching  : Running - fetching the Rx descriptor
  *     - ETH_DMA_ReceiveProcess_Waiting   : Running - waiting for packet
  *     - ETH_DMA_ReceiveProcess_Suspended : Suspended - Rx Desciptor unavailable
  *     - ETH_DMA_ReceiveProcess_Closing   : Running - closing descriptor
  *     - ETH_DMA_ReceiveProcess_Queuing   : Running - queuing the recieve frame into host memory
  */
uint32_t ETH_GetReceiveProcessState(void)
{
    return ((uint32_t)(ETH_DMA->STR & ETH_DMA_STR_RS));
}

/**
  * @brief  Flush the ETHERNET transmit FIFO.
  * @param  None
  * @retval None
  */
void ETH_CleanTransmitFIFO(void)
{
    /* Set the FTF bit for Flushing Transmit FIFO */
    ETH_DMA->CTLR |= ETH_DMA_CTLR_FTF;
}

/**
  * @brief  Get the bit flag of ETHERNET transmit FIFO.
  * @param  None
  * @retval The current ETHERNET flush transmit FIFO bit status(SET or RESET).
  */
TypeState ETH_GetFlushTransmitFIFOStatus(void)
{
    if ((ETH_DMA->CTLR & ETH_DMA_CTLR_FTF) != (uint32_t)RESET) {
        /* Flush transmit FIFO bit is set */
        return SET;
    } else {
        /* Flush transmit FIFO bit is reset */
        return RESET;
    }
}

/**
  * @brief  Enable or disable the DMA transmission function.
  * @param  NewValue: new value of the DMA transmission status.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_DMATransmission_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Set the STE bit for Enable the DMA transmission */
        ETH_DMA->CTLR |= ETH_DMA_CTLR_STE;
    } else {
        /* Reset the STE bit for Disable the DMA transmission */
        ETH_DMA->CTLR &= ~ETH_DMA_CTLR_STE;
    }
}

/**
  * @brief  Enable or disable the DMA reception function.
  * @param  NewValue: new value of the DMA reception status.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_DMAReception_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable DMA reception */
        ETH_DMA->CTLR |= ETH_DMA_CTLR_SRE;
    } else {
        /* Disable DMA reception */
        ETH_DMA->CTLR &= ~ETH_DMA_CTLR_SRE;
    }
}

/**
  * @brief  Enable or disable the ETH_DMA_INT control bit.
  * @param  ETH_DMA_INT: the interrupt source flag of ETH_DMA_IER register.
  *   Select one of the follwing values :
  *     @arg ETH_DMA_INT_NIS : Normal interrupt summary
  *     @arg ETH_DMA_INT_AIS : Abnormal interrupt summary
  *     @arg ETH_DMA_INT_ER  : Early receive interrupt
  *     @arg ETH_DMA_INT_FBE : Fatal bus error interrupt
  *     @arg ETH_DMA_INT_ET  : Early transmit interrupt
  *     @arg ETH_DMA_INT_RWT : Receive watchdog timeout interrupt
  *     @arg ETH_DMA_INT_RPS : Receive process stopped interrupt
  *     @arg ETH_DMA_INT_RBU : Receive buffer unavailable interrupt
  *     @arg ETH_DMA_INT_R   : Receive interrupt
  *     @arg ETH_DMA_INT_TU  : Underflow interrupt
  *     @arg ETH_DMA_INT_RO  : Overflow interrupt
  *     @arg ETH_DMA_INT_TJT : Transmit jabber timeout interrupt
  *     @arg ETH_DMA_INT_TBU : Transmit buffer unavailable interrupt
  *     @arg ETH_DMA_INT_TPS : Transmit process stopped interrupt
  *     @arg ETH_DMA_INT_T   : Transmit interrupt
  * @param  NewValue: new value of the DMA interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_DMAINTConfig(uint32_t ETH_DMA_INT, TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the ETH_DMA_INT control bit */
        ETH_DMA->IER |= ETH_DMA_INT;
    } else {
        /* Disable the ETH_DMA_INT control bit */
        ETH_DMA->IER &= (~(uint32_t)ETH_DMA_INT);
    }
}

/**
  * @brief  Get the bit flag of ETHERNET DMA overflow.
  * @param  ETH_DMA_Overflow: the DMA overflow flag of ETHERNET DMA_MFBOCNT register.
  *   Select one of the follwing values :
  *     @arg ETH_DMA_OVERFLOW_RXFIFOCOUNTER : Overflow for FIFO Overflow Counter
  *     @arg ETH_DMA_OVERFLOW_MISSEDFRAMECOUNTER : Overflow for Missed Frame Counter
  * @retval The current ETHERNET DMA overflow Flag selected bit status(SET or RESET).
  */
TypeState ETH_GetDMAOverflowStatus(uint32_t ETH_DMA_Overflow)
{
    if ((ETH_DMA->MFBOCNT & ETH_DMA_Overflow) != (uint32_t)RESET) {
        /* DMA overflow Flag is set */
        return SET;
    } else {
        /* DMA overflow Flag is reset */
        return RESET;
    }
}

/**
  * @brief  Get the DMA Rx value of overflow Missed Frame Counter.
  * @param  None
  * @retval The ETH_DMA_MFBOCNT register MFA bit value.
  */
uint32_t ETH_GetRxOverflowMissedFrameCounter(void)
{
    return ((uint32_t)((ETH_DMA->MFBOCNT & ETH_DMA_MFBOCNT_MSFA) >> ETH_DMA_RX_OVERFLOW_MISSEDFRAMES_COUNTERSHIFT));
}

/**
  * @brief  Get the DMA value of Buffer unavailable Missed Frame Counter.
  * @param  None
  * @retval The ETH_DMA_MFBOCNT register MFC bit value.
  */
uint32_t ETH_GetBufferUnavailableMissedFrameCounter(void)
{
    return ((uint32_t)(ETH_DMA->MFBOCNT) & ETH_DMA_MFBOCNT_MSFC);
}

/**
  * @brief  Get the DMA value of the current Tx desc start address.
  * @param  None
  * @retval The ETH_DMA_CTDAR register value.
  */
uint32_t ETH_GetCurrentTxDescStartAddress(void)
{
    return ((uint32_t)(ETH_DMA->CTDAR));
}

/**
  * @brief  Get the DMA value of the current Rx desc start address.
  * @param  None
  * @retval The ETH_DMA_CRDAR register value.
  */
uint32_t ETH_GetCurrentRxDescStartAddress(void)
{
    return ((uint32_t)(ETH_DMA->CRDAR));
}

/**
  * @brief  Get the DMA value of the current Tx buffer address.
  * @param  None
  * @retval The ETH_DMA_CTBAR register value.
  */
uint32_t ETH_GetCurrentTxBufferAddress(void)
{
    return ((uint32_t)(ETH_DMA->CTBAR));
}

/**
  * @brief  Get the DMA value of the current Rx buffer address.
  * @param  None
  * @retval The ETH_DMA_CRBAR register value.
  */
uint32_t ETH_GetCurrentRxBufferAddress(void)
{
    return ((uint32_t)(ETH_DMA->CRBAR));
}

/**
  * @brief  Poll the DMA Transmission enable by writing any value to the ETH_DMA_TPER register.
  *   This will make the DMA to resume transmission.
  * @param  None
  * @retval None.
  */
void ETH_ResumeDMATransmission(void)
{
    ETH_DMA->TPER = 0;
}

/**
  * @brief  Poll the DMA Transmission enable by writing any value to the ETH_DMA_RPER register.
  *   This will make the DMA to resume reception.
  * @param  None
  * @retval None.
  */
void ETH_ResumeDMAReception(void)
{
    ETH_DMA->RPER = 0;
}

/* WUM */
/**
  * @brief  Reset Wakeup frame filter register pointer.
  * @param  None
  * @retval None
  */
void ETH_WakeUpFrameFilterRegisterReset(void)
{
    /* Set WUFFRPR bit for Reseting the ETH_MAC_RWFFR register pointer to 0 */
    ETH_MAC->WUMR |= ETH_MAC_WUMR_WUFFRPR;
}

/**
  * @brief  Set the remote wakeup frame registers.
  * @param  pBuffer: Pointer to remote WakeUp Frame Filter Register buffer data (8 words).
  * @retval None
  */
void ETH_SetWakeUpFrameFilterRegister(uint32_t *pBuffer)
{
    uint32_t num = 0;

    /* Configuration ETH_MAC_RWFFR register */
    for (num = 0; num < ETH_WAKEUP_REGISTER_LENGTH; num++) {
        ETH_MAC->RWFFR = pBuffer[num];
    }
}

/**
  * @brief  Enable or disable ETH_MAC_WUMR_GU control bit.
  * @param  NewValue: new value of the MAC Global Unicast Wake-Up.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_GlobalUnicastWakeUp_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the ETH_MAC_WUMR_GU control bit */
        ETH_MAC->WUMR |= ETH_MAC_WUMR_GU;
    } else {
        /* Disable the ETH_MAC_WUMR_GU control bit */
        ETH_MAC->WUMR &= ~ETH_MAC_WUMR_GU;
    }
}

/**
  * @brief  Get the bit flag of the WUM.
  * @param  ETH_WUM_FLAG: the flag of ETH_MAC_WUMR register.
  *   Select one of the follwing values :
  *     @arg ETH_WUM_FLAG_WUFFRPR : Wake-Up Frame Filter Register Poniter Reset
  *     @arg ETH_WUM_FLAG_WUFR    : Wake-Up Frame Received
  *     @arg ETH_WUM_FLAG_MPKR    : Magic Packet Received
  * @retval The current ETHERNET WUM Flag selected bit status(SET or RESET).
  */
TypeState ETH_GetWUMBitState(uint32_t ETH_WUM_FLAG)
{
    if ((ETH_MAC->WUMR & ETH_WUM_FLAG) != (uint32_t)RESET) {
        /* WUM Flag is set */
        return SET;
    } else {
        /* WUM Flag is reset */
        return RESET;
    }
}

/**
  * @brief  Enable or disable the ETH_MAC_WUMR_WFEN control bit.
  * @param  NewValue: new value of the ETH_MAC_WUMR_WFEN bit.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_WakeUpFrameDetection_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Active the MAC Wake-Up Frame Detection */
        ETH_MAC->WUMR |= ETH_MAC_WUMR_WFEN;
    } else {
        /* Deactive the MAC Wake-Up Frame Detection */
        ETH_MAC->WUMR &= ~ETH_MAC_WUMR_WFEN;
    }
}

/**
  * @brief  Enable or disable the ETH_MAC_WUMR_MPEN control bit.
  * @param  NewValue: new value of the ETH_MAC_WUMR_MPEN bit.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_MagicPacketDetection_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the ETH_MAC_WUMR_MPEN control bit */
        ETH_MAC->WUMR |= ETH_MAC_WUMR_MPEN;
    } else {
        /* Disable the ETH_MAC_WUMR_MPEN control bit */
        ETH_MAC->WUMR &= ~ETH_MAC_WUMR_MPEN;
    }
}

/**
  * @brief  Enable or disable the ETH_MAC_WUMR_PWD control bit.
  * @param  NewValue: new value of the ETH_MAC_WUMR_PWD bit.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_PowerDown_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the ETH_MAC_WUMR_PWD control bit */
        ETH_MAC->WUMR |= ETH_MAC_WUMR_PWD;
    } else {
        /* Disable the ETH_MAC_WUMR_PWD control bit */
        ETH_MAC->WUMR &= ~ETH_MAC_WUMR_PWD;
    }
}

/* MSC */
/**
  * @brief  Enable or disable the ETH_MSC_CTLR_MCFZ control bit.
  * @param  NewValue: new value of the MSC Counter Freeze.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_MSCCounterFreeze_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the ETH_MSC_CTLR_MCFZ control bit */
        ETH_MSC->CTLR |= ETH_MSC_CTLR_MCFZ;
    } else {
        /* Disable the ETH_MSC_CTLR_MCFZ control bit */
        ETH_MSC->CTLR &= ~ETH_MSC_CTLR_MCFZ;
    }
}

/**
  * @brief  Enable or disable the ETH_MSC_CTLR_RTOR control bit.
  * @param  NewValue: new value of the MSC Reset On Read.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_MSCResetOnRead_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the ETH_MSC_CTLR_RTOR control bit */
        ETH_MSC->CTLR |= ETH_MSC_CTLR_RTOR;
    } else {
        /* Disable the ETH_MSC_CTLR_RTOR control bit */
        ETH_MSC->CTLR &= ~ETH_MSC_CTLR_RTOR;
    }
}

/**
  * @brief  Enable or disable the ETH_MSC_CTLR_CTSR control bit.
  * @param  NewValue: new value of the ETH_MSC_CTLR_CTSR bit.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_MSCCounterRollover_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the ETH_MSC_CTLR_CTSR control bit */
        ETH_MSC->CTLR &= ~ETH_MSC_CTLR_CTSR;
    } else {
        /* Disable the ETH_MSC_CTLR_CTSR control bit */
        ETH_MSC->CTLR |= ETH_MSC_CTLR_CTSR;
    }
}

/**
  * @brief  Resets the MSC Counters.
  * @param  None
  * @retval None
  */
void ETH_MSCCountersReset(void)
{
    ETH_MSC->CTLR |= ETH_MSC_CTLR_CTR;
}

/**
  * @brief  Enable or disable the ETH_MSC_INT control bit.
  * @param  ETH_MSC_INT: the MSC interrupt sources flag of MSC_RIMR and MSC_TIMR.
  *   This parameter can be any combination of Tx interrupt or
  *   any combination of Rx interrupt (but not both)of the following values:
  *     @arg ETH_MSC_INT_TGF   : When Tx good frame counter reaches half the maximum value
  *     @arg ETH_MSC_INT_TGFMSC: When Tx good multi col counter reaches half the maximum value
  *     @arg ETH_MSC_INT_TGFSC : When Tx good single col counter reaches half the maximum value
  *     @arg ETH_MSC_INT_RGUF  : When Rx good unicast frames counter reaches half the maximum value
  *     @arg ETH_MSC_INT_RFAE  : When Rx alignment error counter reaches half the maximum value
  *     @arg ETH_MSC_INT_RFCE  : When Rx crc error counter reaches half the maximum value
  * @param  NewValue: new value of the MSC interrupt sources flag of MSC_RIMR and MSC_TIMR.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_MSCINTConfig(uint32_t ETH_MSC_INT, TypeState NewValue)
{
    if ((ETH_MSC_INT & (uint32_t)0x10000000) != (uint32_t)RESET) {
        /* Get MSC interrupts souce bit position */
        ETH_MSC_INT &= 0xEFFFFFFF;

        /* MSC Rx interrupts souce bit selected */
        if (NewValue != DISABLE) {
            /* Enable the Rx ETH_MSC_INT control bit */
            ETH_MSC->RIMR &= (~(uint32_t)ETH_MSC_INT);
        } else {
            /* Disable the Rx ETH_MSC_INT control bit */
            ETH_MSC->RIMR |= ETH_MSC_INT;
        }
    } else {
        /* MSC Tx interrupts souce bit selected */
        if (NewValue != DISABLE) {
            /* Enable the Tx ETH_MSC_INT control bit */
            ETH_MSC->TIMR &= (~(uint32_t)ETH_MSC_INT);
        } else {
            /* Disable the Tx ETH_MSC_INT control bit */
            ETH_MSC->TIMR |= ETH_MSC_INT;
        }
    }
}

/**
  * @brief  Get the bit flag of MSC INT.
  * @param  ETH_MSC_INT: the MSC interrupt flag of ETH_MSC_RISR and ETH_MSC_TISR.
  *   Select one of the follwing values :
  *     @arg ETH_MSC_INT_TGF: When Tx good frame counter reaches half the maximum value
  *     @arg ETH_MSC_INT_TGFMSC: When Tx good multi col counter reaches half the maximum value
  *     @arg ETH_MSC_INT_TGFSC: When Tx good single col counter reaches half the maximum value
  *     @arg ETH_MSC_INT_RGUF: When Rx good unicast frames counter reaches half the maximum value
  *     @arg ETH_MSC_INT_RFAE : When Rx alignment error counter reaches half the maximum value
  *     @arg ETH_MSC_INT_RFCE : When Rx crc error counter reaches half the maximum value
  * @retval The current ETHERNET MSC IT selected bit status(SET or RESET).
  */
TypeState ETH_GetMSCINTStatus(uint32_t ETH_MSC_INT)
{
    if ((ETH_MSC_INT & (uint32_t)0x10000000) != (uint32_t)RESET) {
        /* Check if the MSC interrupt flag of ETH_MSC_RISR selected is enabled and occured */
        if ((((ETH_MSC->RISR & ETH_MSC_INT) != (uint32_t)RESET)) && ((ETH_MSC->RIMR & ETH_MSC_INT) != (uint32_t)RESET)) {
            /* The MSC interrupt flag of ETH_MSC_RISR is set */
            return SET;
        } else {
            /* The MSC interrupt flag of ETH_MSC_RISR is reset */
            return RESET;
        }
    } else {
        /* Check if the MSC interrupt flag of ETH_MSC_TISR selected is enabled and occured */
        if ((((ETH_MSC->TISR & ETH_MSC_INT) != (uint32_t)RESET)) && ((ETH_MSC->RIMR & ETH_MSC_INT) != (uint32_t)RESET)) {
            /* The MSC interrupt flag of ETH_MSC_TISR is set */
            return SET;
        } else {
            /* The MSC interrupt flag of ETH_MSC_TISR is reset */
            return RESET;
        }
    }
}

/**
  * @brief  Read value of the MSC module register.
  * @param  ETH_MSC_Register: the MSC module register selected.
  *   Select one of the follwing values :
  *     @arg ETH_MSC_CTLR     : MSC CR register
  *     @arg ETH_MSC_RISR     : MSC RIR register
  *     @arg ETH_MSC_TISR     : MSC TIR register
  *     @arg ETH_MSC_RIMR     : MSC RIMR register
  *     @arg ETH_MSC_TIMR     : MSC TIMR register
  *     @arg ETH_MSC_SCCNT    : MSC TGFSCCR register
  *     @arg ETH_MSC_MSCCNT   : MSC TGFMSCCR register
  *     @arg ETH_MSC_TGFCNT   : MSC TGFCR register
  *     @arg ETH_MSC_RFCECNT  : MSC RFCECR register
  *     @arg ETH_MSC_RFAECNT  : MSC RFAECR register
  *     @arg ETH_MSC_RGUFCNT  : MSC RGUFCRregister
  * @retval MSC module Register selected value.
  */
uint32_t ETH_GetMSCRegister(uint32_t ETH_MSC_Register)
{
    /* Return the value of MSC module Register selected  */
    return (*(__IO uint32_t *)(ETH_MAC_BASE + ETH_MSC_Register));
}

/* PTP */
/**
  * @brief  Updated the Time Stamp Addend register value to the PTP block(used only when the system time is configured
  *   for Fine update mode).
  * @param  None
  * @retval None
  */
void ETH_PTPTimeStampAddendUpdate(void)
{
    ETH_PTP->TSCTLR |= ETH_PTP_TSCTLR_TMSARU;
}

/**
  * @brief  Set ETH_PTP_TSCTLR_TMSITEN bit.
  * @param  NewValue: new value of the MAC reception.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_PTPTimeStampIntTrigger_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable ETH_PTP_TSCTLR_TMSITEN bit */
        ETH_PTP->TSCTLR |= ETH_PTP_TSCTLR_TMSITEN;
    } else {
        /* Disable ETH_PTP_TSCTLR_TMSITEN bit */
        ETH_PTP->TSCTLR &= ~ETH_PTP_TSCTLR_TMSITEN;
    }
}

/**
  * @brief  Updated the Time Stamp Update register value to the PTP system time.
  * @param  NewValue: new value of the MAC reception.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_PTPTimeStampUpdate_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable PTP time stamp update */
        ETH_PTP->TSCTLR |= ETH_PTP_TSCTLR_TMSSTU;
    } else {
        /* Disable PTP time stamp update */
        ETH_PTP->TSCTLR &= ~ETH_PTP_TSCTLR_TMSSTU;
    }
}

/**
  * @brief  Initialize the PTP Time Stamp mode
  * @param  None
  * @retval None
  */
void ETH_PTPTimeStampInit(void)
{
    ETH_PTP->TSCTLR |= ETH_PTP_TSCTLR_TMSSTI;
}

/**
  * @brief  Set the PTP Time Stamp Update mode
  * @param  UpdateMode: the PTP Update mode selected
  *   Select one of the follwing values :
  *     @arg ETH_PTP_FINEMODE   : Fine Update method
  *     @arg ETH_PTP_COARSEMODE : Coarse Update method
  * @retval None
  */
void ETH_PTPUpdateModeConfig(uint32_t UpdateMode)
{
    if (UpdateMode != ETH_PTP_COARSEMODE) {
        /* Enable the PTP Fine Update mode */
        ETH_PTP->TSCTLR |= ETH_PTP_TSCTLR_TMSFCU;
    } else {
        /* Disable the PTP Coarse Update mode */
        ETH_PTP->TSCTLR &= (~(uint32_t)ETH_PTP_TSCTLR_TMSFCU);
    }
}

/**
  * @brief  Enable or disable ETH_PTP_TSCTLR_TMSEN control bit.
  * @param  NewValue: new value of the  ETH_PTP_TSCTLR_TMSEN control bit
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_PTPTimeStamp_Enable(TypeState NewValue)
{
    if (NewValue != DISABLE) {
        /* Enable the ETH_PTP_TSCTLR_TMSEN control bit */
        ETH_PTP->TSCTLR |= ETH_PTP_TSCTLR_TMSEN;
    } else {
        /* Disable the ETH_PTP_TSCTLR_TMSEN control bit */
        ETH_PTP->TSCTLR &= (~(uint32_t)ETH_PTP_TSCTLR_TMSEN);
    }
}

/**
  * @brief  Get the bit flag of ETHERNET PTP.
  * @param  ETH_PTP_FLAG: the flag of PTP_TSCTLR register.
  *   Select one of the follwing values :
  *     @arg ETH_PTP_FLAG_TMSARU  : Addend Register Update
  *     @arg ETH_PTP_FLAG_TMSITEN : Time Stamp Interrupt Trigger Enable
  *     @arg ETH_PTP_FLAG_TMSSTU  : Time Stamp Update
  *     @arg ETH_PTP_FLAG_TMSSTI  : Time Stamp Initialize
  * @retval The current ETHERNET PTP Flag selected bit status(SET or RESET).
  */
TypeState ETH_GetPTPBitState(uint32_t ETH_PTP_FLAG)
{
    if ((ETH_PTP->TSCTLR & ETH_PTP_FLAG) != (uint32_t)RESET) {
        /* ETH_PTP_FLAG is set */
        return SET;
    } else {
        /* ETH_PTP_FLAG is reset */
        return RESET;
    }
}

/**
  * @brief  Set Each HCLK cycle the system time Sub-Second Increased value.
  * @param  SubSecond: the PTP_SSINCR Register value.
  * @retval None
  */
void ETH_SetPTPSubSecondIncrement(uint32_t SubSecond)
{
    ETH_PTP->SSINCR = SubSecond;
}

/**
  * @brief  Set the system time update sign and values.
  * @param  Sign: the PTP Time update value sign(positive or negative).
  *   Select one of the follwing values :
  *     @arg ETH_PTP_POSITIVETIME : positive time value.
  *     @arg ETH_PTP_NEGATIVETIME : negative time value.
  * @param  Second: the PTP Time update value in second part.
  * @param  SubSecond: the PTP Time update value in sub-second part.
  *   This parameter is a 31 bit value, bit32 correspond to the sign.
  * @retval None
  */
void ETH_SetPTPUpdateTimeValue(uint32_t Sign, uint32_t SecondValue, uint32_t SubSecondValue)
{
    /* Set the PTP Time Update High Register with second value*/
    ETH_PTP->TMSHUR = SecondValue;

    /* Set the PTP Time Update Low Register with subsecond value and sign */
    ETH_PTP->TMSLUR = Sign | SubSecondValue;
}

/**
  * @brief  Set the system time Addend value(used only when the system time is configured
  * for Fine update mode).
  * @param  add: the PTP PTP_TSACNT Register value.
  * @retval None
  */
void ETH_SetPTPTimeStampAddend(uint32_t add)
{
    ETH_PTP->TSACNT = add;
}

/**
  * @brief  Set the Target system Time values.
  * @param  HighReg_Value: the PTP Expected Time High Register value.
  * @param  LowReg_Value:  the PTP Expected Time Low Register value.
  * @retval None
  */
void ETH_SetPTPTargetTime(uint32_t HighReg_Value, uint32_t LowReg_Value)
{
    /* Set the PTP Expected Time High Register */
    ETH_PTP->ETHR = HighReg_Value;
    /* Set the PTP Expected Time Low Register */
    ETH_PTP->ETLR = LowReg_Value;
}

/**
  * @brief  Read the value of PTP module register .
  * @param  ETH_PTPRegister: the PTP module register selected.
  *   Select one of the follwing values :
  *     @arg ETH_PTP_TSCTLR  : Sub-Second Increment Register
  *     @arg ETH_PTP_SSINCR  : Sub-Second Increment Register
  *     @arg ETH_PTP_TMSHR   : Time Stamp High Register
  *     @arg ETH_PTP_TMSLR   : Time Stamp Low Register
  *     @arg ETH_PTP_TMSHUR  : Time Stamp High Update Register
  *     @arg ETH_PTP_TMSLUR  : Time Stamp Low Update Register
  *     @arg ETH_PTP_TSACNT  : Time Stamp Addend Register
  *     @arg ETH_PTP_ETHR    : Target Time High Register
  *     @arg ETH_PTP_ETLR    : Target Time Low Register
  * @retval ETHERNET PTP Register selected value.
  */
uint32_t ETH_GetPTPRegister(uint32_t ETH_PTPRegister)
{
    return (*(__IO uint32_t *)(ETH_MAC_BASE + ETH_PTPRegister));
}

/**
  * @brief  Initialize the DMA Tx descriptors's parameters in chain mode with PTP.
  * @param  DMATxDescTab: Pointer to the first Tx descriptor table
  * @param  DMAPTPTxDescTab: Pointer to the first PTP Tx descriptor table
  * @param  pTxBuff: Pointer to the first TxBuffer table
  * @param  TxBuffCnt: the used Tx descriptor sum in the table
  * @retval None
  */
void ETH_DMAPTPTxDescChainModeInit(ETH_DMADESCTypeDef *DMATxDescTab, ETH_DMADESCTypeDef *DMAPTPTxDescTab,
                                   uint8_t *pTxBuff, uint32_t TxBuffCnt)
{
    uint32_t num = 0;
    ETH_DMADESCTypeDef *DMATxDesc;

    DMACurrentTxDesc = DMATxDescTab;
    DMACurrentPTPTxDesc = DMAPTPTxDescTab;
    /* Configuration each DMATxDesc descriptor */
    for (num = 0; num < TxBuffCnt; num++) {
        /* Get the pointer to the next descriptor of the Tx Desc table */
        DMATxDesc = DMATxDescTab + num;
        /* Set TCH bit and enable PTP with desc status */
        DMATxDesc->Status = ETH_DMATXDESC_TCHM | ETH_DMATXDESC_TTSEN;

        /* Set Buffer1 address pointer to application buffer */
        DMATxDesc->Buffer1Addr = (uint32_t)(&pTxBuff[num * ETH_MAX_FRAME_SIZE]);

        if (num < (TxBuffCnt - 1)) {
            /* Buffer2NextDescAddr equal to next descriptor address in the Tx Desc table */
            DMATxDesc->Buffer2NextDescAddr = (uint32_t)(DMATxDescTab + num + 1);
        } else {
            /* When it is the last descriptor, Buffer2NextDescAddr equal to first descriptor address in the Tx Desc table */
            DMATxDesc->Buffer2NextDescAddr = (uint32_t) DMATxDescTab;
        }
        /* Set DMAPTPTxDescTab equal to DMATxDescTab */
        (&DMAPTPTxDescTab[num])->Buffer1Addr = DMATxDesc->Buffer1Addr;
        (&DMAPTPTxDescTab[num])->Buffer2NextDescAddr = DMATxDesc->Buffer2NextDescAddr;
    }
    /* When it is the last PTPdescriptor, DMAPTPTxDesc status equal to the first descriptor address in the PTPTx Desc list address */
    (&DMAPTPTxDescTab[num - 1])->Status = (uint32_t) DMAPTPTxDescTab;

    ETH_DMA->TDTAR = (uint32_t) DMATxDescTab;
}

/**
  * @brief  Initialize the DMA Rx descriptors's parameters in chain mode with PTP.
  * @param  DMARxDescTab: Pointer to the first Rx descriptor table
  * @param  DMAPTPRxDescTab: Pointer to the first PTP Rx descriptor table
  * @param  pRxBuff: Pointer to the first RxBuffer table
  * @param  RxBuffCnt: the used Rx descriptor sum in the table
  * @retval None
  */
void ETH_DMAPTPRxDescChainModeInit(ETH_DMADESCTypeDef *DMARxDescTab, ETH_DMADESCTypeDef *DMAPTPRxDescTab,
                                   uint8_t *pRxBuff, uint32_t RxBuffCnt)
{
    uint32_t num = 0;
    ETH_DMADESCTypeDef *DMARxDesc;

    DMACurrentRxDesc = DMARxDescTab;
    DMACurrentPTPRxDesc = DMAPTPRxDescTab;
    /* Configuration each DMARxDesc descriptor */
    for (num = 0; num < RxBuffCnt; num++) {
        /* Get the pointer to the next descriptor of the Rx Desc table */
        DMARxDesc = DMARxDescTab + num;
        DMARxDesc->Status = ETH_DMARXDESC_BUSY;

        /* Set TCH bit and buffer1 size */
        DMARxDesc->ControlBufferSize = ETH_DMARXDESC_RCHM | (uint32_t)ETH_MAX_FRAME_SIZE;
        /* Set Buffer1 address pointer to application buffer */
        DMARxDesc->Buffer1Addr = (uint32_t)(&pRxBuff[num * ETH_MAX_FRAME_SIZE]);

        if (num < (RxBuffCnt - 1)) {
            /* Buffer2NextDescAddr equal to next descriptor address in the Rx Desc table */
            DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab + num + 1);
        } else {
            /* When it is the last descriptor, Buffer2NextDescAddr equal to first descriptor address in the Rx Desc table */
            DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab);
        }
        /* Set DMAPTPRxDescTab equal to DMARxDescTab */
        (&DMAPTPRxDescTab[num])->Buffer1Addr = DMARxDesc->Buffer1Addr;
        (&DMAPTPRxDescTab[num])->Buffer2NextDescAddr = DMARxDesc->Buffer2NextDescAddr;
    }
    /* When it is the last PTPdescriptor, DMAPTPRxDesc status equal to the first descriptor address in the PTPRx Desc table address */
    (&DMAPTPRxDescTab[num - 1])->Status = (uint32_t) DMAPTPRxDescTab;

    /* Update Receive Desciptor Table Address Register */
    ETH_DMA->RDTAR = (uint32_t) DMARxDescTab;
}

/**
  * @brief  Send data with Time Stamp values of application buffer as a transmit packet.
  * @param  pbuf: pointer to the applicationbuffer.
  * @param  size: the application buffer size.
  * @param  PTPTxTab: Pointer to the first PTP Tx table to store Time stamp values.
  * @retval The transmission with PTP result(ERROR or SUCCESS)
  */
uint32_t ETH_HandlePTPTxPkt(uint8_t *pbuf, uint16_t size, uint32_t *PTPTxTab)
{
    uint32_t offset = 0, timeout = 0;

    if ((DMACurrentTxDesc->Status & ETH_DMATXDESC_BUSY) != (uint32_t)RESET) {
        /* Return ERROR: the descriptor is busy due to own by the DMA */
        return ERROR;
    }
    for (offset = 0; offset < size; offset++) {
        (*(__IO uint8_t *)((DMACurrentPTPTxDesc->Buffer1Addr) + offset)) = (*(pbuf + offset));
    }
    /* Setting the Frame Length */
    DMACurrentTxDesc->ControlBufferSize = (size & (uint32_t)0x1FFF);
    /* Setting the segment of frame (ETH_DMATXDESC_LSG and ETH_DMATXDESC_FSG are SET that frame is transmitted in one descriptor) */
    DMACurrentTxDesc->Status |= ETH_DMATXDESC_LSG | ETH_DMATXDESC_FSG;
    /* Enable the DMA transmission */
    DMACurrentTxDesc->Status |= ETH_DMATXDESC_BUSY;
    /* Check Tx Buffer unavailable flag status */
    if ((ETH_DMA->STR & ETH_DMA_STR_TBU) != (uint32_t)RESET) {
        /* Clear TBU ETHERNET DMA flag */
        ETH_DMA->STR = ETH_DMA_STR_TBU;
        /* Resume DMA transmission by writing to the TPER register*/
        ETH_DMA->TPER = 0;
    }
    /* Wait for ETH_DMATXDESC_TTMSS flag to be set unless timeout */
    do {
        timeout++;
    } while (!(DMACurrentTxDesc->Status & ETH_DMATXDESC_TTMSS) && (timeout < 0xFFFF));
    /* Return ERROR due to timeout */
    if (timeout == PHY_READ_TO) {
        return ERROR;
    }
    /* Clear the DMACurrentTxDesc status register TTSS flag */
    DMACurrentTxDesc->Status &= ~ETH_DMATXDESC_TTMSS;
    *PTPTxTab++ = DMACurrentTxDesc->Buffer1Addr;
    *PTPTxTab = DMACurrentTxDesc->Buffer2NextDescAddr;
    /* Update the ETHERNET DMA current Tx descriptor pointer to the next Tx decriptor in DMA Tx decriptor talbe*/
    /* Chained Mode */
    if ((DMACurrentTxDesc->Status & ETH_DMATXDESC_TCHM) != (uint32_t)RESET) {
        DMACurrentTxDesc = (ETH_DMADESCTypeDef *)(DMACurrentPTPTxDesc->Buffer2NextDescAddr);
        if (DMACurrentPTPTxDesc->Status != 0) {
            DMACurrentPTPTxDesc = (ETH_DMADESCTypeDef *)(DMACurrentPTPTxDesc->Status);
        } else {
            DMACurrentPTPTxDesc++;
        }
    }
    /* Ring Mode */
    else {
        if ((DMACurrentTxDesc->Status & ETH_DMATXDESC_TERM) != (uint32_t)RESET) {
            DMACurrentTxDesc = (ETH_DMADESCTypeDef *)(ETH_DMA->TDTAR);
            DMACurrentPTPTxDesc = (ETH_DMADESCTypeDef *)(ETH_DMA->TDTAR);
        } else {
            DMACurrentTxDesc = (ETH_DMADESCTypeDef *)((uint32_t)DMACurrentTxDesc + ETH_DMATXDESC_SIZE + ((ETH_DMA->BCR & ETH_DMA_BCR_DPSL) >> 2));
            DMACurrentPTPTxDesc = (ETH_DMADESCTypeDef *)((uint32_t)DMACurrentPTPTxDesc + ETH_DMATXDESC_SIZE + ((ETH_DMA->BCR & ETH_DMA_BCR_DPSL) >> 2));
        }
    }
    return SUCCESS;
}

/**
  * @brief  Receive a packet data with Time Stamp values to application buffer.
  * @param  pbuf: Pointer on the application buffer.
  * @param  PTPRxTab: Pointer to the first PTP Rx table to store Time stamp values.
  * @retval The Receive frame length with PTP(If size is equal to ERROR, the receiving unsuccessful)
  */
uint32_t ETH_HandlePTPRxPkt(uint8_t *pbuf, uint32_t *PTPRxTab)
{
    uint32_t offset = 0, size = 0;

    if ((DMACurrentRxDesc->Status & ETH_DMARXDESC_BUSY) != (uint32_t)RESET) {
        /* Return ERROR: the descriptor is busy due to own by the DMA */
        return ERROR;
    }
    if (((DMACurrentRxDesc->Status & ETH_DMARXDESC_ERRS) == (uint32_t)RESET) &&
            ((DMACurrentRxDesc->Status & ETH_DMARXDESC_LDES) != (uint32_t)RESET) &&
            ((DMACurrentRxDesc->Status & ETH_DMARXDESC_FDES) != (uint32_t)RESET)) {
        /* Get the Frame Length exclusive CRC */
        size = ((DMACurrentRxDesc->Status & ETH_DMARXDESC_FRML) >> ETH_DMARXDESC_FRAME_LENGTHSHIFT) - 4;
        for (offset = 0; offset < size; offset++) {
            (*(pbuf + offset)) = (*(__IO uint8_t *)((DMACurrentPTPRxDesc->Buffer1Addr) + offset));
        }
    } else {
        /* Return ERROR */
        size = ERROR;
    }
    /* Check Rx Buffer unavailable flag status */
    if ((ETH_DMA->STR & ETH_DMA_STR_RBU) != (uint32_t)RESET) {
        /* Clear RBU ETHERNET DMA flag */
        ETH_DMA->STR = ETH_DMA_STR_RBU;
        /* Resume DMA reception by writing to the RPER register*/
        ETH_DMA->RPER = 0;
    }
    *PTPRxTab++ = DMACurrentRxDesc->Buffer1Addr;
    *PTPRxTab = DMACurrentRxDesc->Buffer2NextDescAddr;
    /* Enable reception */
    DMACurrentRxDesc->Status |= ETH_DMARXDESC_BUSY;
    /* Update the ETHERNET DMA current Rx descriptor pointer to the next Rx decriptor in DMA Rx decriptor talbe*/
    /* Chained Mode */
    if ((DMACurrentRxDesc->ControlBufferSize & ETH_DMARXDESC_RCHM) != (uint32_t)RESET) {
        DMACurrentRxDesc = (ETH_DMADESCTypeDef *)(DMACurrentPTPRxDesc->Buffer2NextDescAddr);
        if (DMACurrentPTPRxDesc->Status != 0) {
            DMACurrentPTPRxDesc = (ETH_DMADESCTypeDef *)(DMACurrentPTPRxDesc->Status);
        } else {
            DMACurrentPTPRxDesc++;
        }
    }
    /* Ring Mode */
    else {
        if ((DMACurrentRxDesc->ControlBufferSize & ETH_DMARXDESC_RERR) != (uint32_t)RESET) {
            DMACurrentRxDesc = (ETH_DMADESCTypeDef *)(ETH_DMA->RDTAR);
        } else {
            DMACurrentRxDesc = (ETH_DMADESCTypeDef *)((uint32_t)DMACurrentRxDesc + ETH_DMARXDESC_SIZE + ((ETH_DMA->BCR & ETH_DMA_BCR_DPSL) >> 2));
        }
    }
    /* Return Frame size or ERROR */
    return (size);
}

#ifndef USE_Delay
/**
  * @brief  Insert a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
static void ETH_Delay(__IO uint32_t nCount)
{
    __IO uint32_t time = 0;

    for (time = nCount; time != 0; time--) {
    }
}
#endif /* USE_Delay */
#endif /* GD32F10X_CL */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

