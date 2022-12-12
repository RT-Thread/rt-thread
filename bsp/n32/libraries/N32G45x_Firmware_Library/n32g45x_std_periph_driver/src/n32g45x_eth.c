/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_eth.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32g45x_eth.h"
#include "n32g45x_gpio.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup ETH
 * @brief ETH driver modules
 * @{
 */

/**
 * @brief Initialize GPIO pins for MII/RMII interface.
 *
 * @param ETH_Interface specifies the interface, can be the following values:
 *  @arg ETH_INTERFACE_RMII Reduced media-independent interface
 *  @arg ETH_INTERFACE_MII Media-independent interface
 * @param remap remap mode, can be 0~3
 */
void ETH_ConfigGpio(uint8_t ETH_Interface, uint8_t remap)
{
    GPIO_InitType GPIO_InitStructure;
    uint32_t ETH_PA_O;
    uint32_t ETH_PA_I;
    uint32_t ETH_PB_O;
    uint32_t ETH_PB_I;
    uint32_t ETH_PC_O;
    uint32_t ETH_PC_I;
    uint32_t ETH_PD_O;
    uint32_t ETH_PD_I;
    if (ETH_Interface == ETH_INTERFACE_MII)
    {
        switch (remap)
        {
        case 0:
            ETH_PA_O = GPIO_PIN_2;
            ETH_PA_I = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_7;
            ETH_PB_O = GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
            ETH_PB_I = GPIO_PIN_10 | GPIO_PIN_0 | GPIO_PIN_1;
            ETH_PC_O = GPIO_PIN_1 | GPIO_PIN_2;
            ETH_PC_I = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
            ETH_PD_O = 0;
            ETH_PD_I = 0;
            break;
        case 1:
            ETH_PA_O = GPIO_PIN_2;
            ETH_PA_I = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3;
            ETH_PB_O = GPIO_PIN_8 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
            ETH_PB_I = GPIO_PIN_10;
            ETH_PC_O = GPIO_PIN_1 | GPIO_PIN_2;
            ETH_PC_I = GPIO_PIN_3;
            ETH_PD_O = 0;
            ETH_PD_I = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
            GPIO_ConfigPinRemap(GPIO_RMP1_ETH, ENABLE);
            break;
        case 2:
            ETH_PA_O = GPIO_PIN_2;
            ETH_PA_I = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_7;
            ETH_PB_O = GPIO_PIN_7 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
            ETH_PB_I = GPIO_PIN_10 | GPIO_PIN_0 | GPIO_PIN_1;
            ETH_PC_O = GPIO_PIN_1 | GPIO_PIN_2;
            ETH_PC_I = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
            ETH_PD_O = 0;
            ETH_PD_I = 0;
            GPIO_ConfigPinRemap(GPIO_RMP2_ETH, ENABLE);
            break;
        case 3:
            ETH_PA_O = GPIO_PIN_2;
            ETH_PA_I = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3;
            ETH_PB_O = GPIO_PIN_7 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
            ETH_PB_I = GPIO_PIN_10 | GPIO_PIN_0 | GPIO_PIN_1;
            ETH_PC_O = GPIO_PIN_1 | GPIO_PIN_2;
            ETH_PC_I = GPIO_PIN_3;
            ETH_PD_O = 0;
            ETH_PD_I = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
            GPIO_ConfigPinRemap(GPIO_RMP3_ETH, ENABLE);
            break;
        default:
            while (1)
                ;
        }
    }
    else /* RMII */
    {
        switch (remap)
        {
        case 0:
        case 2:
            ETH_PA_O = GPIO_PIN_2;
            ETH_PA_I = GPIO_PIN_1 | GPIO_PIN_7;
            ETH_PB_O = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
            ETH_PB_I = 0;
            ETH_PC_O = GPIO_PIN_1;
            ETH_PC_I = GPIO_PIN_4 | GPIO_PIN_5;
            ETH_PD_O = 0;
            ETH_PD_I = 0;
            break;
        case 1:
        case 3:
            ETH_PA_O = GPIO_PIN_2;
            ETH_PA_I = GPIO_PIN_1;
            ETH_PB_O = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
            ETH_PB_I = 0;
            ETH_PC_O = GPIO_PIN_1;
            ETH_PC_I = 0;
            ETH_PD_O = 0;
            ETH_PD_I = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
            GPIO_ConfigPinRemap(GPIO_RMP1_ETH, ENABLE);
            break;
        default:
            while (1)
                ;
        }
    }
    if (ETH_PA_O)
    {
        /* Configure Ethernet PA and PA8 (MCO) as alternate function push-pull */
        GPIO_InitStructure.Pin        = ETH_PA_O;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    }
    if (ETH_PB_O)
    {
        /* Configure Ethernet PB and PB5 (PPS) as alternate function push-pull */
        GPIO_InitStructure.Pin        = ETH_PB_O;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    }
    if (ETH_PC_O)
    {
        /* Configure Ethernet PC as alternate function push-pull */
        GPIO_InitStructure.Pin        = ETH_PC_O;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
    }
    if (ETH_PD_O)
    {
        /* Configure Ethernet PD as alternate function push-pull */
        GPIO_InitStructure.Pin        = ETH_PD_O;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);
    }

    if (ETH_PA_I)
    {
        /* Configure Ethernet PA as input */
        GPIO_InitStructure.Pin        = ETH_PA_I;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
        GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    }
    if (ETH_PB_I)
    {
        /* Configure Ethernet PB as input */
        GPIO_InitStructure.Pin        = ETH_PB_I;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
        GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    }
    if (ETH_PC_I)
    {
        /* Configure Ethernet PC as input */
        GPIO_InitStructure.Pin        = ETH_PC_I;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
        GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
    }
    if (ETH_PD_I)
    {
        /* Configure Ethernet PD as input */
        GPIO_InitStructure.Pin        = ETH_PD_I;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
        GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);
    }
}

/** @addtogroup ETH_Private_TypesDefinitions
 * @{
 */
/**
 * @}
 */

/** @addtogroup ETH_Private_Defines
 * @{
 */
/* Global pointers on Tx and Rx descriptor used to track transmit and receive descriptors */
__IO ETH_DMADescType* DMATxDescToSet;
__IO ETH_DMADescType* DMARxDescToGet;
__IO ETH_DMADescType* DMAPTPTxDescToSet;
__IO ETH_DMADescType* DMAPTPRxDescToGet;

/* ETHERNET MAC address offsets */
#define ETH_MAC_ADDR_HBASE (ETH_MAC_BASE + 0x40) /* ETHERNET MAC address high offset */
#define ETH_MAC_ADDR_LBASE (ETH_MAC_BASE + 0x44) /* ETHERNET MAC address low offset */

/* ETHERNET MACMIIADDR register Mask */
#define MACMIIAR_CR_MASK ((uint32_t)0xFFFFFFE3)

/* ETHERNET MACCFG register Mask */
#define MACCR_CLR_MASK ((uint32_t)0xFF20810F)

/* ETHERNET MACFLWCTRL register Mask */
#define MACFCR_CLR_MASK ((uint32_t)0x0000FF41)

/* ETHERNET DMAOPMOD register Mask */
#define DMAOMR_CLR_MASK ((uint32_t)0xF8DE3F23)

/* ETHERNET Remote Wake-up frame register length */
#define ETH_WAKEUP_REG_LEN 8

/* ETHERNET Missed frames counter Shift */
#define ETH_DMA_RX_OVERFLOW_MISSEDFRAMES_COUNTER_SHIFT 17

/* ETHERNET DMA Tx descriptors Collision Count Shift */
#define ETH_DMA_TX_DESC_COLLISION_COUNTER_SHIFT 3

/* ETHERNET DMA Tx descriptors Buffer2 Size Shift */
#define ETH_DMA_TX_DESC_BUF2_SIZE_SHIFT 11

/* ETHERNET DMA Rx descriptors Frame Length Shift */
#define ETH_DMA_RX_DESC_FRAME_LEN_SHIFT 16

/* ETHERNET DMA Rx descriptors Buffer2 Size Shift */
#define ETH_DMA_RX_DESC_BUF2_SIZE_SHIFT 11

/**
 * @}
 */

/** @addtogroup ETH_Private_Macros
 * @{
 */
/**
 * @}
 */

/** @addtogroup ETH_Private_Variables
 * @{
 */
/**
 * @}
 */

/** @addtogroup ETH_Private_FunctionPrototypes
 * @{
 */
/**
 * @}
 */

/** @addtogroup ETH_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the ETHERNET peripheral registers to their default reset values.
 */
void ETH_DeInit(void)
{
    RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ETHMAC, ENABLE);
    RCC_EnableAHBPeriphReset(RCC_AHB_PERIPH_ETHMAC, DISABLE);
}
/**
 * @brief  Initializes the ETHERNET peripheral according to the specified
 *   parameters in the ETH_InitStruct .
 * @param ETH_InitStruct pointer to a ETH_InitType structure that contains
 *   the configuration information for the specified ETHERNET peripheral.
 * @param callable a function pointer of @ref ETH_InitPHY
 * @return ETH_ERROR: Ethernet initialization failed
 *         ETH_SUCCESS: Ethernet successfully initialized
 */
uint32_t ETH_Init(ETH_InitType* ETH_InitStruct, ETH_InitPHY callable)
{
    uint32_t tmpregister = 0;
    RCC_ClocksType rcc_clocks;
    uint32_t hclk = 60000000;
    /* Check the parameters */
    /* MAC --------------------------*/
    assert_param(IS_ETH_AUTONEG(ETH_InitStruct->AutoNegotiation));
    assert_param(IS_ETH_WATCHDOG(ETH_InitStruct->Watchdog));
    assert_param(IS_ETH_JABBER(ETH_InitStruct->Jabber));
    assert_param(IS_ETH_INTER_FRAME_GAP(ETH_InitStruct->InterFrameGap));
    assert_param(IS_ETH_CARRIER_SENSE(ETH_InitStruct->CarrierSense));
    assert_param(IS_ETH_SPEED_MODE(ETH_InitStruct->SpeedMode));
    assert_param(IS_ETH_RX_OWN(ETH_InitStruct->RxOwn));
    assert_param(IS_ETH_LOOPBACK_MODE(ETH_InitStruct->LoopbackMode));
    assert_param(IS_ETH_DUPLEX_MODE(ETH_InitStruct->DuplexMode));
    assert_param(IS_ETH_CHECKSUM_OFFLOAD(ETH_InitStruct->ChecksumOffload));
    assert_param(IS_ETH_RETRY_TRANSMISSION(ETH_InitStruct->RetryTransmission));
    assert_param(IS_ETH_AUTO_PAD_CRC_STRIP(ETH_InitStruct->AutomaticPadCRCStrip));
    assert_param(IS_ETH_BACKOFF_LIMIT(ETH_InitStruct->BackoffLimit));
    assert_param(IS_ETH_DEFERRAL_CHECK(ETH_InitStruct->DeferralCheck));
    assert_param(IS_ETH_RX_ALL(ETH_InitStruct->RxAll));
    assert_param(IS_ETH_SRC_ADDR_FILTER(ETH_InitStruct->SrcAddrFilter));
    assert_param(IS_ETH_PASS_CTRL_FRAMES(ETH_InitStruct->PassCtrlFrames));
    assert_param(IS_ETH_BROADCAST_FRAMES_RECEPTION(ETH_InitStruct->BroadcastFramesReception));
    assert_param(IS_ETH_DEST_ADDR_FILTER(ETH_InitStruct->DestAddrFilter));
    assert_param(IS_ETH_PROMISCUOUS_MODE(ETH_InitStruct->PromiscuousMode));
    assert_param(IS_ETH_MULTICAST_FRAMES_FILTER(ETH_InitStruct->MulticastFramesFilter));
    assert_param(IS_ETH_UNICAST_FRAMES_FILTER(ETH_InitStruct->UnicastFramesFilter));
    assert_param(IS_ETH_PAUSE_TIME(ETH_InitStruct->PauseTime));
    assert_param(IS_ETH_ZERO_QUANTA_PAUSE(ETH_InitStruct->ZeroQuantaPause));
    assert_param(IS_ETH_PAUSE_LOW_THRESHOLD(ETH_InitStruct->PauseLowThreshold));
    assert_param(IS_ETH_UNICAST_PAUSE_FRAME_DETECT(ETH_InitStruct->UnicastPauseFrameDetect));
    assert_param(IS_ETH_RX_FLOW_CTRL(ETH_InitStruct->RxFlowCtrl));
    assert_param(IS_ETH_TX_FLOW_CTRL(ETH_InitStruct->TxFlowCtrl));
    assert_param(IS_ETH_VLAN_TAG_COMPARISON(ETH_InitStruct->VLANTagComparison));
    assert_param(IS_ETH_VLAN_TAG_IDENTIFIER(ETH_InitStruct->VLANTagIdentifier));
    /* DMA --------------------------*/
    assert_param(IS_ETH_DROP_TCPIP_CHECKSUM_FRAME(ETH_InitStruct->DropTCPIPChecksumErrorFrame));
    assert_param(IS_ETH_RX_STORE_FORWARD(ETH_InitStruct->RxStoreForward));
    assert_param(IS_ETH_FLUSH_RX_FRAME(ETH_InitStruct->FlushRxFrame));
    assert_param(IS_ETH_TX_STORE_FORWARD(ETH_InitStruct->TxStoreForward));
    assert_param(IS_ETH_TX_THRESHOLD_CTRL(ETH_InitStruct->TxThresholdCtrl));
    assert_param(IS_ETH_FORWARD_ERROR_FRAMES(ETH_InitStruct->ForwardErrorFrames));
    assert_param(IS_ETH_FORWARD_UNDERSIZED_GOOD_FRAMES(ETH_InitStruct->ForwardUndersizedGoodFrames));
    assert_param(IS_ETH_RX_THRESHOLD_CTRL(ETH_InitStruct->RxThresholdCtrl));
    assert_param(IS_ETH_SECOND_FRAME_OPERATE(ETH_InitStruct->SecondFrameOperate));
    assert_param(IS_ETH_ADDR_ALIGNED_BEATS(ETH_InitStruct->AddrAlignedBeats));
    assert_param(IS_ETH_FIXED_BURST(ETH_InitStruct->FixedBurst));
    assert_param(IS_ETH_RX_DMA_BURST_LEN(ETH_InitStruct->RxDMABurstLen));
    assert_param(IS_ETH_TX_DMA_BURST_LEN(ETH_InitStruct->TxDMABurstLen));
    assert_param(IS_ETH_DMA_DESC_SKIP_LEN(ETH_InitStruct->DescSkipLen));
    assert_param(IS_ETH_DMA_ARBITRATION_ROUND_ROBIN_RXTX(ETH_InitStruct->DMAArbitration));
    /*-------------------------------- MAC Config ------------------------------*/
    /*---------------------- ETHERNET MACMIIADDR Configuration -------------------*/
    /* Get the ETHERNET MACMIIADDR value */
    tmpregister = ETH->MACMIIADDR;
    /* Clear CTRLSTS Clock Range CTRL[2:0] bits */
    tmpregister &= MACMIIAR_CR_MASK;
    /* Get hclk frequency value */
    RCC_GetClocksFreqValue(&rcc_clocks);
    hclk = rcc_clocks.HclkFreq;
    /* Set CTRL bits depending on hclk value */
    if (/*(hclk >= 20000000) && */ (hclk < 35000000))
    {
        /* CTRLSTS Clock Range between 20-35 MHz */
        tmpregister |= (uint32_t)ETH_MACMIIADDR_CR_DIV16;
    }
    else if ((hclk >= 35000000) && (hclk < 60000000))
    {
        /* CTRLSTS Clock Range between 35-60 MHz */
        tmpregister |= (uint32_t)ETH_MACMIIADDR_CR_DIV26;
    }
    else if ((hclk >= 60000000) && (hclk <= 72000000))
    {
        /* CTRLSTS Clock Range between 60-72 MHz */
        tmpregister |= (uint32_t)ETH_MACMIIADDR_CR_DIV42;
    }
    /* Write to ETHERNET MAC MIIAR: Configure the ETHERNET CTRLSTS Clock Range */
    ETH->MACMIIADDR = (uint32_t)tmpregister;
    /*-------------------- PHY initialization and configuration ----------------*/
    if (ETH_ERROR == callable(ETH_InitStruct))
    {
        return ETH_ERROR;
    }

    /*------------------------ ETHERNET MACCFG Configuration --------------------*/
    /* Get the ETHERNET MACCFG value */
    tmpregister = ETH->MACCFG;
    /* Clear WD, PCE, PS, TE and RE bits */
    tmpregister &= MACCR_CLR_MASK;
    /* Set the WD bit according to Watchdog value */
    /* Set the JD: bit according to Jabber value */
    /* Set the IFG bit according to InterFrameGap value */
    /* Set the DCRS bit according to CarrierSense value */
    /* Set the FES bit according to SpeedMode value */
    /* Set the DO bit according to RxOwn value */
    /* Set the LM bit according to LoopbackMode value */
    /* Set the DM bit according to DuplexMode value */
    /* Set the IPC bit according to ChecksumOffload value */
    /* Set the DAT bit according to RetryTransmission value */
    /* Set the ACS bit according to AutomaticPadCRCStrip value */
    /* Set the BL bit according to BackoffLimit value */
    /* Set the DC bit according to DeferralCheck value */
    tmpregister |= (uint32_t)(
        ETH_InitStruct->Watchdog | ETH_InitStruct->Jabber | ETH_InitStruct->InterFrameGap | ETH_InitStruct->CarrierSense
        | ETH_InitStruct->SpeedMode | ETH_InitStruct->RxOwn | ETH_InitStruct->LoopbackMode | ETH_InitStruct->DuplexMode
        | ETH_InitStruct->ChecksumOffload | ETH_InitStruct->RetryTransmission | ETH_InitStruct->AutomaticPadCRCStrip
        | ETH_InitStruct->BackoffLimit | ETH_InitStruct->DeferralCheck);
    /* Write to ETHERNET MACCFG */
    ETH->MACCFG = (uint32_t)tmpregister;

    /*----------------------- ETHERNET MACFFLT Configuration --------------------*/
    /* Set the RA bit according to RxAll value */
    /* Set the SAF and SAIF bits according to SrcAddrFilter value */
    /* Set the PCF bit according to PassCtrlFrames value */
    /* Set the DBF bit according to BroadcastFramesReception value */
    /* Set the DAIF bit according to DestAddrFilter value */
    /* Set the PEND bit according to PromiscuousMode value */
    /* Set the PM, HMC and HPF bits according to MulticastFramesFilter value */
    /* Set the HUC and HPF bits according to UnicastFramesFilter value */
    /* Write to ETHERNET MACFFLT */
    ETH->MACFFLT = (uint32_t)(ETH_InitStruct->RxAll | ETH_InitStruct->SrcAddrFilter | ETH_InitStruct->PassCtrlFrames
                              | ETH_InitStruct->BroadcastFramesReception | ETH_InitStruct->DestAddrFilter
                              | ETH_InitStruct->PromiscuousMode | ETH_InitStruct->MulticastFramesFilter
                              | ETH_InitStruct->UnicastFramesFilter);
    /*--------------- ETHERNET MACHASHHI and MACHASHLO Configuration ---------------*/
    /* Write to ETHERNET MACHASHHI */
    ETH->MACHASHHI = (uint32_t)ETH_InitStruct->HashTableHigh;
    /* Write to ETHERNET MACHASHLO */
    ETH->MACHASHLO = (uint32_t)ETH_InitStruct->HashTableLow;
    /*----------------------- ETHERNET MACFLWCTRL Configuration --------------------*/
    /* Get the ETHERNET MACFLWCTRL value */
    tmpregister = ETH->MACFLWCTRL;
    /* Clear xx bits */
    tmpregister &= MACFCR_CLR_MASK;

    /* Set the PT bit according to PauseTime value */
    /* Set the DZPQ bit according to ZeroQuantaPause value */
    /* Set the PLT bit according to PauseLowThreshold value */
    /* Set the UP bit according to UnicastPauseFrameDetect value */
    /* Set the RFE bit according to RxFlowCtrl value */
    /* Set the TFE bit according to TxFlowCtrl value */
    tmpregister |= (uint32_t)((ETH_InitStruct->PauseTime << 16) | ETH_InitStruct->ZeroQuantaPause
                              | ETH_InitStruct->PauseLowThreshold | ETH_InitStruct->UnicastPauseFrameDetect
                              | ETH_InitStruct->RxFlowCtrl | ETH_InitStruct->TxFlowCtrl);
    /* Write to ETHERNET MACFLWCTRL */
    ETH->MACFLWCTRL = (uint32_t)tmpregister;
    /*----------------------- ETHERNET MACVLANTAG Configuration -----------------*/
    /* Set the ETV bit according to VLANTagComparison value */
    /* Set the VL bit according to VLANTagIdentifier value */
    ETH->MACVLANTAG = (uint32_t)(ETH_InitStruct->VLANTagComparison | ETH_InitStruct->VLANTagIdentifier);

    /*-------------------------------- DMA Config ------------------------------*/
    /*----------------------- ETHERNET DMAOPMOD Configuration --------------------*/
    /* Get the ETHERNET DMAOPMOD value */
    tmpregister = ETH->DMAOPMOD;
    /* Clear xx bits */
    tmpregister &= DMAOMR_CLR_MASK;

    /* Set the DT bit according to DropTCPIPChecksumErrorFrame value */
    /* Set the RSYF bit according to RxStoreForward value */
    /* Set the DFF bit according to FlushRxFrame value */
    /* Set the TSF bit according to TxStoreForward value */
    /* Set the TTC bit according to TxThresholdCtrl value */
    /* Set the FEF bit according to ForwardErrorFrames value */
    /* Set the FUF bit according to ForwardUndersizedGoodFrames value */
    /* Set the RTC bit according to RxThresholdCtrl value */
    /* Set the OSF bit according to SecondFrameOperate value */
    tmpregister |=
        (uint32_t)(ETH_InitStruct->DropTCPIPChecksumErrorFrame | ETH_InitStruct->RxStoreForward
                   | ETH_InitStruct->FlushRxFrame | ETH_InitStruct->TxStoreForward | ETH_InitStruct->TxThresholdCtrl
                   | ETH_InitStruct->ForwardErrorFrames | ETH_InitStruct->ForwardUndersizedGoodFrames
                   | ETH_InitStruct->RxThresholdCtrl | ETH_InitStruct->SecondFrameOperate);
    /* Write to ETHERNET DMAOPMOD */
    ETH->DMAOPMOD = (uint32_t)tmpregister;

    /*----------------------- ETHERNET DMABUSMOD Configuration --------------------*/
    /* Set the AAL bit according to AddrAlignedBeats value */
    /* Set the FB bit according to FixedBurst value */
    /* Set the RPBL and 4*PBL bits according to RxDMABurstLen value */
    /* Set the PBL and 4*PBL bits according to TxDMABurstLen value */
    /* Set the DSL bit according to ETH_DesciptorSkipLength value */
    /* Set the PEND and DA bits according to DMAArbitration value */
    ETH->DMABUSMOD =
        (uint32_t)(ETH_InitStruct->AddrAlignedBeats | ETH_InitStruct->FixedBurst | ETH_InitStruct->RxDMABurstLen
                   | /* !! if 4xPBL is selected for Tx or Rx it is applied for the other */
                   ETH_InitStruct->TxDMABurstLen | (ETH_InitStruct->DescSkipLen << 2) | ETH_InitStruct->DMAArbitration
                   | ETH_DMABUSMOD_USP); /* Enable use of separate PBL for Rx and Tx */

    /* Disable all MMC interrupt */
    ETH->MMCRXINTMSK   = 0xffffffffUL;
    ETH->MMCTXINTMSK   = 0xffffffffUL;
    ETH->MMCRXCOINTMSK = 0xffffffffUL;

    /* Return Ethernet configuration success */
    return ETH_SUCCESS;
}

/**
 * @brief  Fills each ETH_InitStruct member with its default value.
 * @param ETH_InitStruct pointer to a ETH_InitType structure which will be initialized.
 */
void ETH_InitStruct(ETH_InitType* ETH_InitStruct)
{
    /* ETH_InitStruct members default value */
    /*------------------------   MAC   -----------------------------------*/
    ETH_InitStruct->AutoNegotiation          = ETH_AUTONEG_DISABLE;
    ETH_InitStruct->Watchdog                 = ETH_WATCHDOG_ENABLE;
    ETH_InitStruct->Jabber                   = ETH_JABBER_ENABLE;
    ETH_InitStruct->InterFrameGap            = ETH_INTER_FRAME_GAP_96BIT;
    ETH_InitStruct->CarrierSense             = ETH_CARRIER_SENSE_ENABLE;
    ETH_InitStruct->SpeedMode                = ETH_SPEED_MODE_10M;
    ETH_InitStruct->RxOwn                    = ETH_RX_OWN_ENABLE;
    ETH_InitStruct->LoopbackMode             = ETH_LOOPBACK_MODE_DISABLE;
    ETH_InitStruct->DuplexMode               = ETH_DUPLEX_MODE_HALF;
    ETH_InitStruct->ChecksumOffload          = ETH_CHECKSUM_OFFLOAD_DISABLE;
    ETH_InitStruct->RetryTransmission        = ETH_RETRY_TRANSMISSION_ENABLE;
    ETH_InitStruct->AutomaticPadCRCStrip     = ETH_AUTO_PAD_CRC_STRIP_DISABLE;
    ETH_InitStruct->BackoffLimit             = ETH_BACKOFF_LIMIT_10;
    ETH_InitStruct->DeferralCheck            = ETH_DEFERRAL_CHECK_DISABLE;
    ETH_InitStruct->RxAll                    = ETH_RX_ALL_DISABLE;
    ETH_InitStruct->SrcAddrFilter            = ETH_SRC_ADDR_FILTER_DISABLE;
    ETH_InitStruct->PassCtrlFrames           = ETH_PASS_CTRL_FRAMES_BLOCK_ALL;
    ETH_InitStruct->BroadcastFramesReception = ETH_BROADCAST_FRAMES_RECEPTION_DISABLE;
    ETH_InitStruct->DestAddrFilter           = ETH_DEST_ADDR_FILTER_NORMAL;
    ETH_InitStruct->PromiscuousMode          = ETH_PROMISCUOUS_MODE_DISABLE;
    ETH_InitStruct->MulticastFramesFilter    = ETH_MULTICAST_FRAMES_FILTER_PERFECT;
    ETH_InitStruct->UnicastFramesFilter      = ETH_UNICAST_FRAMES_FILTER_PERFECT;
    ETH_InitStruct->HashTableHigh            = 0x0;
    ETH_InitStruct->HashTableLow             = 0x0;
    ETH_InitStruct->PauseTime                = 0x0;
    ETH_InitStruct->ZeroQuantaPause          = ETH_ZERO_QUANTA_PAUSE_DISABLE;
    ETH_InitStruct->PauseLowThreshold        = ETH_PAUSE_LOW_THRESHOLD_MINUS4;
    ETH_InitStruct->UnicastPauseFrameDetect  = ETH_UNICAST_PAUSE_FRAME_DETECT_DISABLE;
    ETH_InitStruct->RxFlowCtrl               = ETH_RX_FLOW_CTRL_DISABLE;
    ETH_InitStruct->TxFlowCtrl               = ETH_TX_FLOW_CTRL_DISABLE;
    ETH_InitStruct->VLANTagComparison        = ETH_VLAN_TAG_COMPARISON_16BIT;
    ETH_InitStruct->VLANTagIdentifier        = 0x0;
    /*------------------------   DMA   -----------------------------------*/
    ETH_InitStruct->DropTCPIPChecksumErrorFrame = ETH_DROP_TCPIP_CHECKSUM_ERROR_FRAME_DISABLE;
    ETH_InitStruct->RxStoreForward              = ETH_RX_STORE_FORWARD_ENABLE;
    ETH_InitStruct->FlushRxFrame                = ETH_FLUSH_RX_FRAME_DISABLE;
    ETH_InitStruct->TxStoreForward              = ETH_TX_STORE_FORWARD_ENABLE;
    ETH_InitStruct->TxThresholdCtrl             = ETH_TX_THRESHOLD_CTRL_64BYTES;
    ETH_InitStruct->ForwardErrorFrames          = ETH_FORWARD_ERROR_FRAMES_DISABLE;
    ETH_InitStruct->ForwardUndersizedGoodFrames = ETH_FORWARD_UNDERSIZED_GOOD_FRAMES_ENABLE;
    ETH_InitStruct->RxThresholdCtrl             = ETH_RX_THRESHOLD_CTRL_64BYTES;
    ETH_InitStruct->SecondFrameOperate          = ETH_SECOND_FRAME_OPERATE_DISABLE;
    ETH_InitStruct->AddrAlignedBeats            = ETH_ADDR_ALIGNED_BEATS_ENABLE;
    ETH_InitStruct->FixedBurst                  = ETH_FIXED_BURST_DISABLE;
    ETH_InitStruct->RxDMABurstLen               = ETH_RX_DMA_BURST_LEN_1BEAT;
    ETH_InitStruct->TxDMABurstLen               = ETH_TX_DMA_BURST_LEN_1BEAT;
    ETH_InitStruct->DescSkipLen                 = 0x0;
    ETH_InitStruct->DMAArbitration              = ETH_DMA_ARBITRATION_ROUND_ROBIN_RXTX_1_1;
}

/**
 * @brief  Enables ENET MAC and DMA reception/transmission
 */
void ETH_EnableTxRx(void)
{
    /* Enable transmit state machine of the MAC for transmission on the MII */
    ETH_EnableMacTx(ENABLE);
    /* Flush Transmit DATFIFO */
    ETH_FlushTxFifo();
    /* Enable receive state machine of the MAC for reception from the MII */
    ETH_EnableMacRx(ENABLE);

    /* Start DMA transmission */
    ETH_EnableDmaTx(ENABLE);
    /* Start DMA reception */
    ETH_EnableDmaRx(ENABLE);
}

/**
 * @brief  Transmits a packet, from application buffer, pointed by ppkt.
 * @param ppkt pointer to the application's packet buffer to transmit.
 * @param FrameLength Tx Packet size.
 * @return ETH_ERROR: in case of Tx desc owned by DMA
 *         ETH_SUCCESS: for correct transmission
 */
uint32_t ETH_TxPacket(uint8_t* ppkt, uint16_t FrameLength)
{
    uint32_t send_len = 0;

    while (send_len < FrameLength)
    {
        uint32_t offset = 0;

        /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
        if ((DMATxDescToSet->Status & ETH_DMA_TX_DESC_OWN) != (uint32_t)RESET)
        {
            /* Return ERROR: OWN bit set */
            return ETH_ERROR;
        }

        uint16_t block_len = FrameLength - send_len;
        if (block_len > ETH_DMA_TX_DESC_TBS1)
        {
            block_len = ETH_DMA_TX_DESC_TBS1;
        }
        /* Copy the frame to be sent into memory pointed by the current ETHERNET DMA Tx descriptor */
        for (offset = 0; offset < block_len; offset++)
        {
            (*(__IO uint8_t*)((DMATxDescToSet->Buf1Addr) + offset)) = (*(ppkt + offset + send_len));
        }

        /* Setting the Frame Length: bits[10:0] */
        DMATxDescToSet->CtrlOrBufSize &= (~ETH_DMA_TX_DESC_TBS1);
        DMATxDescToSet->CtrlOrBufSize |= block_len;
        /* Setting the last segment and first segment bits (in this case a frame is transmitted in one descriptor) */
        if (send_len == 0)
        {
            DMATxDescToSet->CtrlOrBufSize |= ETH_DMA_TX_DESC_FS;
        }
        send_len += block_len;
        if (send_len == FrameLength)
        {
            DMATxDescToSet->CtrlOrBufSize |= ETH_DMA_TX_DESC_LS;
        }

        /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
        DMATxDescToSet->Status |= ETH_DMA_TX_DESC_OWN;
        /* When Tx Buffer unavailable flag is set: clear it and resume transmission */
        if ((ETH->DMASTS & ETH_DMASTS_TU) != (uint32_t)RESET)
        {
            /* Clear TBUS ETHERNET DMA flag */
            ETH->DMASTS = ETH_DMASTS_TU;
            /* Resume DMA transmission*/
            ETH->DMATXPD = 0;
        }

        /* Update the ETHERNET DMA global Tx descriptor with next Tx decriptor */
        /* Chained Mode */
        if ((DMATxDescToSet->CtrlOrBufSize & ETH_DMA_TX_DESC_TCH) != (uint32_t)RESET)
        {
            /* Selects the next DMA Tx descriptor list for next buffer to send */
            DMATxDescToSet = (ETH_DMADescType*)(DMATxDescToSet->Buf2OrNextDescAddr);
        }
        else /* Ring Mode */
        {
            if ((DMATxDescToSet->CtrlOrBufSize & ETH_DMA_TX_DESC_TER) != (uint32_t)RESET)
            {
                /* Selects the first DMA Tx descriptor for next buffer to send: last Tx descriptor was used */
                DMATxDescToSet = (ETH_DMADescType*)(ETH->DMATXDLADDR);
            }
            else
            {
                /* Selects the next DMA Tx descriptor list for next buffer to send */
                DMATxDescToSet =
                    (ETH_DMADescType*)((uint32_t)DMATxDescToSet + 0x10 + ((ETH->DMABUSMOD & ETH_DMABUSMOD_DSL)));
            }
        }
    }
    /* Return SUCCESS */
    return ETH_SUCCESS;
}

/**
 * @brief  Receives a packet and copies it to memory pointed by ppkt.
 * @param ppkt pointer to the application packet receive buffer.
 * @param checkErr whether check error
 * @return ETH_ERROR: if there is error in reception
 *         framelength: received packet size if packet reception is correct
 */
uint32_t ETH_RxPacket(uint8_t* ppkt, uint8_t checkErr)
{
    uint32_t offset = 0, framelength = 0;
    /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
    if ((DMARxDescToGet->Status & ETH_DMA_RX_DESC_OWN) != (uint32_t)RESET)
    {
        /* Return error: OWN bit set */
        return ETH_ERROR;
    }

    if (((checkErr && ((DMARxDescToGet->Status & ETH_DMA_RX_DESC_ES) == (uint32_t)RESET)) || !checkErr)
        && ((DMARxDescToGet->Status & ETH_DMA_RX_DESC_LS) != (uint32_t)RESET)
        && ((DMARxDescToGet->Status & ETH_DMA_RX_DESC_FS) != (uint32_t)RESET))
    {
        /* Get the Frame Length of the received packet */
        framelength = ((DMARxDescToGet->Status & ETH_DMA_RX_DESC_FL) >> ETH_DMA_RX_DESC_FRAME_LEN_SHIFT);
        /* Copy the received frame into buffer from memory pointed by the current ETHERNET DMA Rx descriptor */
        for (offset = 0; offset < framelength; offset++)
        {
            (*(ppkt + offset)) = (*(__IO uint8_t*)((DMARxDescToGet->Buf1Addr) + offset));
        }
    }
    else
    {
        /* Return ERROR */
        framelength = ETH_ERROR;
    }
    /* Set Own bit of the Rx descriptor Status: gives the buffer back to ETHERNET DMA */
    DMARxDescToGet->Status = ETH_DMA_RX_DESC_OWN;

    /* When Rx Buffer unavailable flag is set: clear it and resume reception */
    if ((ETH->DMASTS & ETH_DMASTS_RU) != (uint32_t)RESET)
    {
        /* Clear RBUS ETHERNET DMA flag */
        ETH->DMASTS = ETH_DMASTS_RU;
        /* Resume DMA reception */
        ETH->DMARXPD = 0;
    }

    /* Update the ETHERNET DMA global Rx descriptor with next Rx decriptor */
    /* Chained Mode */
    if ((DMARxDescToGet->CtrlOrBufSize & ETH_DMA_RX_DESC_RCH) != (uint32_t)RESET)
    {
        /* Selects the next DMA Rx descriptor list for next buffer to read */
        DMARxDescToGet = (ETH_DMADescType*)(DMARxDescToGet->Buf2OrNextDescAddr);
    }
    else /* Ring Mode */
    {
        if ((DMARxDescToGet->CtrlOrBufSize & ETH_DMA_RX_DESC_RER) != (uint32_t)RESET)
        {
            /* Selects the first DMA Rx descriptor for next buffer to read: last Rx descriptor was used */
            DMARxDescToGet = (ETH_DMADescType*)(ETH->DMARXDLADDR);
        }
        else
        {
            /* Selects the next DMA Rx descriptor list for next buffer to read */
            DMARxDescToGet =
                (ETH_DMADescType*)((uint32_t)DMARxDescToGet + 0x10 + ((ETH->DMABUSMOD & ETH_DMABUSMOD_DSL)));
        }
    }

    /* Return Frame Length/ERROR */
    return (framelength);
}

/**
 * @brief  Get the size of received the received packet.
 * @return framelength: received packet size
 */
uint32_t ETH_GetRxPacketSize(void)
{
    uint32_t frameLength = 0;
    if (((DMARxDescToGet->Status & ETH_DMA_RX_DESC_OWN) == (uint32_t)RESET)
        && ((DMARxDescToGet->Status & ETH_DMA_RX_DESC_ES) == (uint32_t)RESET)
        && ((DMARxDescToGet->Status & ETH_DMA_RX_DESC_LS) != (uint32_t)RESET)
        && ((DMARxDescToGet->Status & ETH_DMA_RX_DESC_FS) != (uint32_t)RESET))
    {
        /* Get the size of the packet: including 4 bytes of the CRC */
        frameLength = ETH_GetDmaRxDescFrameLen(DMARxDescToGet);
    }

    /* Return Frame Length */
    return frameLength;
}

/**
 * @brief  Drop a Received packet (too small packet, etc...)
 */
void ETH_DropRxPacket(void)
{
    /* Set Own bit of the Rx descriptor Status: gives the buffer back to ETHERNET DMA */
    DMARxDescToGet->Status = ETH_DMA_RX_DESC_OWN;
    /* Chained Mode */
    if ((DMARxDescToGet->CtrlOrBufSize & ETH_DMA_RX_DESC_RCH) != (uint32_t)RESET)
    {
        /* Selects the next DMA Rx descriptor list for next buffer read */
        DMARxDescToGet = (ETH_DMADescType*)(DMARxDescToGet->Buf2OrNextDescAddr);
    }
    else /* Ring Mode */
    {
        if ((DMARxDescToGet->CtrlOrBufSize & ETH_DMA_RX_DESC_RER) != (uint32_t)RESET)
        {
            /* Selects the next DMA Rx descriptor list for next buffer read: this will
            be the first Rx descriptor in this case */
            DMARxDescToGet = (ETH_DMADescType*)(ETH->DMARXDLADDR);
        }
        else
        {
            /* Selects the next DMA Rx descriptor list for next buffer read */
            DMARxDescToGet =
                (ETH_DMADescType*)((uint32_t)DMARxDescToGet + 0x10 + ((ETH->DMABUSMOD & ETH_DMABUSMOD_DSL)));
        }
    }
}

/*---------------------------------  PHY  ------------------------------------*/
/**
 * @brief  Read a PHY register
 * @param PHYAddress PHY device address, is the index of one of supported 32 PHY devices.
 *   This parameter can be one of the following values: 0,..,31
 * @param PHYReg PHY register address, is the index of one of the 32 PHY register.
 *   This parameter can be one of the following values:
 *     @arg PHY_BCR Tranceiver Basic Control Register
 *     @arg PHY_BSR Tranceiver Basic Status Register
 *     @arg PHY_SR Tranceiver Status Register
 *     @arg More PHY register could be read depending on the used PHY
 * @return ETH_ERROR: in case of timeout
 *         MAC MIIDR register value: Data read from the selected PHY register (correct read )
 */
uint16_t ETH_ReadPhyRegister(uint16_t PHYAddress, uint16_t PHYReg)
{
    uint32_t tmpregister  = 0;
    __IO uint32_t timeout = 0;
    /* Check the parameters */
    assert_param(IS_ETH_PHY_ADDRESS(PHYAddress));
    assert_param(IS_ETH_PHY_REG(PHYReg));

    /* Get the ETHERNET MACMIIADDR value */
    tmpregister = ETH->MACMIIADDR;
    /* Keep only the CTRLSTS Clock Range CTRL[2:0] bits value */
    tmpregister &= ~MACMIIAR_CR_MASK;
    /* Prepare the MII address register value */
    tmpregister |= (((uint32_t)PHYAddress << 11) & ETH_MACMIIADDR_PA); /* Set the PHY device address */
    tmpregister |= (((uint32_t)PHYReg << 6) & ETH_MACMIIADDR_MR);      /* Set the PHY register address */
    tmpregister &= ~ETH_MACMIIADDR_MW;                                 /* Set the read mode */
    tmpregister |= ETH_MACMIIADDR_MB;                                  /* Set the MII Busy bit */
    /* Write the result value into the MII Address register */
    ETH->MACMIIADDR = tmpregister;
    /* Check for the Busy flag */
    do
    {
        timeout++;
        tmpregister = ETH->MACMIIADDR;
    } while ((tmpregister & ETH_MACMIIADDR_MB) && (timeout < (uint32_t)PHY_READ_TO));
    /* Return ERROR in case of timeout */
    if (timeout == PHY_READ_TO)
    {
        return (uint16_t)ETH_ERROR;
    }

    /* Return data register value */
    uint16_t ret = (uint16_t)(ETH->MACMIIDAT);
    return ret;
}

/**
 * @brief  Write to a PHY register
 * @param PHYAddress PHY device address, is the index of one of supported 32 PHY devices.
 *   This parameter can be one of the following values: 0,..,31
 * @param PHYReg PHY register address, is the index of one of the 32 PHY register.
 *   This parameter can be one of the following values:
 *     @arg PHY_BCR Tranceiver Control Register
 *     @arg More PHY register could be written depending on the used PHY
 * @param PHYValue the value to write
 * @return ETH_ERROR: in case of timeout
 *         ETH_SUCCESS: for correct write
 */
uint32_t ETH_WritePhyRegister(uint16_t PHYAddress, uint16_t PHYReg, uint16_t PHYValue)
{
    uint32_t tmpregister  = 0;
    __IO uint32_t timeout = 0;
    /* Check the parameters */
    assert_param(IS_ETH_PHY_ADDRESS(PHYAddress));
    assert_param(IS_ETH_PHY_REG(PHYReg));

    /* Get the ETHERNET MACMIIADDR value */
    tmpregister = ETH->MACMIIADDR;
    /* Keep only the CTRLSTS Clock Range CTRL[2:0] bits value */
    tmpregister &= ~MACMIIAR_CR_MASK;
    /* Prepare the MII register address value */
    tmpregister |= (((uint32_t)PHYAddress << 11) & ETH_MACMIIADDR_PA); /* Set the PHY device address */
    tmpregister |= (((uint32_t)PHYReg << 6) & ETH_MACMIIADDR_MR);      /* Set the PHY register address */
    tmpregister |= ETH_MACMIIADDR_MW;                                  /* Set the write mode */
    tmpregister |= ETH_MACMIIADDR_MB;                                  /* Set the MII Busy bit */
    /* Give the value to the MII data register */
    ETH->MACMIIDAT = PHYValue;
    /* Write the result value into the MII Address register */
    ETH->MACMIIADDR = tmpregister;
    /* Check for the Busy flag */
    do
    {
        timeout++;
        tmpregister = ETH->MACMIIADDR;
    } while ((tmpregister & ETH_MACMIIADDR_MB) && (timeout < (uint32_t)PHY_WRITE_TO));
    /* Return ERROR in case of timeout */
    if (timeout == PHY_WRITE_TO)
    {
        return ETH_ERROR;
    }

    /* Return SUCCESS */
    return ETH_SUCCESS;
}

/**
 * @brief  Enables or disables the PHY loopBack mode.
 * @note: Don't be confused with ETH_MACLoopBackCmd function which enables internal
 *  loopback at MII level
 * @param PHYAddress PHY device address, is the index of one of supported 32 PHY devices.
 *   This parameter can be one of the following values:
 * @param Cmd new state of the PHY loopBack mode.
 *   This parameter can be: ENABLE or DISABLE.
 * @return ETH_ERROR: in case of bad PHY configuration
 *         ETH_SUCCESS: for correct PHY configuration
 */
uint32_t ETH_EnablePhyLoopBack(uint16_t PHYAddress, FunctionalState Cmd)
{
    uint16_t tmpregister = 0;
    /* Check the parameters */
    assert_param(IS_ETH_PHY_ADDRESS(PHYAddress));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    /* Get the PHY configuration to update it */
    tmpregister = ETH_ReadPhyRegister(PHYAddress, PHY_BCR);

    if (Cmd != DISABLE)
    {
        /* Enable the PHY loopback mode */
        tmpregister |= PHY_LOOPBACK;
    }
    else
    {
        /* Disable the PHY loopback mode: normal mode */
        tmpregister &= (uint16_t)(~(uint16_t)PHY_LOOPBACK);
    }
    /* Update the PHY control register with the new configuration */
    if (ETH_WritePhyRegister(PHYAddress, PHY_BCR, tmpregister) != (uint32_t)RESET)
    {
        return ETH_SUCCESS;
    }
    else
    {
        /* Return SUCCESS */
        return ETH_ERROR;
    }
}

/*---------------------------------  MAC  ------------------------------------*/
/**
 * @brief  Enables or disables the MAC transmission.
 * @param Cmd new state of the MAC transmission.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableMacTx(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the MAC transmission */
        ETH->MACCFG |= ETH_MACCFG_TE;
    }
    else
    {
        /* Disable the MAC transmission */
        ETH->MACCFG &= ~ETH_MACCFG_TE;
    }
}

/**
 * @brief  Enables or disables the MAC reception.
 * @param Cmd new state of the MAC reception.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableMacRx(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the MAC reception */
        ETH->MACCFG |= ETH_MACCFG_RE;
    }
    else
    {
        /* Disable the MAC reception */
        ETH->MACCFG &= ~ETH_MACCFG_RE;
    }
}

/**
 * @brief  Checks whether the ETHERNET flow control busy bit is set or not.
 * @return The new state of flow control busy status bit (SET or RESET).
 */
FlagStatus ETH_GetFlowCtrlBusyStatus(void)
{
    FlagStatus bitstatus = RESET;
    /* The Flow Control register should not be written to until this bit is cleared */
    if ((ETH->MACFLWCTRL & ETH_MACFLWCTRL_FCB_BPA) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Initiate a Pause Control Frame (Full-duplex only).
 */
void ETH_GeneratePauseCtrlFrame(void)
{
    /* When Set In full duplex MAC initiates pause control frame */
    ETH->MACFLWCTRL |= ETH_MACFLWCTRL_FCB_BPA;
}

/**
 * @brief  Enables or disables the MAC BackPressure operation activation (Half-duplex only).
 * @param Cmd new state of the MAC BackPressure operation activation.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableBackPressureActivation(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Activate the MAC BackPressure operation */
        /* In Half duplex: during backpressure, when the MAC receives a new frame,
        the transmitter starts sending a JAM pattern resulting in a collision */
        ETH->MACFLWCTRL |= ETH_MACFLWCTRL_FCB_BPA;
    }
    else
    {
        /* Desactivate the MAC BackPressure operation */
        ETH->MACFLWCTRL &= ~ETH_MACFLWCTRL_FCB_BPA;
    }
}

/**
 * @brief  Checks whether the specified ETHERNET MAC flag is set or not.
 * @param ETH_MAC_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg ETH_MAC_FLAG_TST Time stamp trigger flag
 *     @arg ETH_MAC_FLAG_MMCTX MMC transmit flag
 *     @arg ETH_MAC_FLAG_MMCRX MMC receive flag
 *     @arg ETH_MAC_FLAG_MMC MMC flag
 *     @arg ETH_MAC_FLAG_PMT PMT flag
 * @return The new state of ETHERNET MAC flag (SET or RESET).
 */
FlagStatus ETH_GetMacFlagStatus(uint32_t ETH_MAC_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ETH_MAC_GET_FLAG(ETH_MAC_FLAG));
    if ((ETH->MACINTSTS & ETH_MAC_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Checks whether the specified ETHERNET MAC interrupt has occurred or not.
 * @param ETH_MAC_IT specifies the interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg ETH_MAC_INT_TST Time stamp trigger interrupt
 *     @arg ETH_MAC_INT_MMCTX MMC transmit interrupt
 *     @arg ETH_MAC_INT_MMCRX MMC receive interrupt
 *     @arg ETH_MAC_INT_MMC MMC interrupt
 *     @arg ETH_MAC_INT_PMT PMT interrupt
 * @return The new state of ETHERNET MAC interrupt (SET or RESET).
 */
INTStatus ETH_GetMacIntStatus(uint32_t ETH_MAC_IT)
{
    INTStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ETH_MAC_GET_INT(ETH_MAC_IT));
    if ((ETH->MACINTSTS & ETH_MAC_IT) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Enables or disables the specified ETHERNET MAC interrupts.
 * @param ETH_MAC_IT specifies the ETHERNET MAC interrupt sources to be
 *   enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg ETH_MAC_INT_TST Time stamp trigger interrupt
 *     @arg ETH_MAC_INT_PMT PMT interrupt
 * @param Cmd new state of the specified ETHERNET MAC interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableMacInt(uint32_t ETH_MAC_IT, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_ETH_MAC_INT(ETH_MAC_IT));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected ETHERNET MAC interrupts */
        ETH->MACINTMSK &= (~(uint32_t)ETH_MAC_IT);
    }
    else
    {
        /* Disable the selected ETHERNET MAC interrupts */
        ETH->MACINTMSK |= ETH_MAC_IT;
    }
}

/**
 * @brief  Configures the selected MAC address.
 * @param MacAddr The MAC addres to configure.
 *   This parameter can be one of the following values:
 *     @arg ETH_MAC_ADDR0 MAC Address0
 *     @arg ETH_MAC_ADDR1 MAC Address1
 *     @arg ETH_MAC_ADDR2 MAC Address2
 *     @arg ETH_MAC_ADDR3 MAC Address3
 * @param Addr Pointer on MAC address buffer data (6 bytes).
 */
void ETH_SetMacAddr(uint32_t MacAddr, uint8_t* Addr)
{
    uint32_t tmpregister;
    /* Check the parameters */
    assert_param(IS_ETH_MAC_ADDR0123(MacAddr));

    /* Calculate the selectecd MAC address high register */
    tmpregister = ((uint32_t)Addr[5] << 8) | (uint32_t)Addr[4];
    /* Load the selectecd MAC address high register */
    (*(__IO uint32_t*)(ETH_MAC_ADDR_HBASE + MacAddr)) = tmpregister;
    /* Calculate the selectecd MAC address low register */
    tmpregister = ((uint32_t)Addr[3] << 24) | ((uint32_t)Addr[2] << 16) | ((uint32_t)Addr[1] << 8) | Addr[0];

    /* Load the selectecd MAC address low register */
    (*(__IO uint32_t*)(ETH_MAC_ADDR_LBASE + MacAddr)) = tmpregister;
}

/**
 * @brief  Get the selected MAC address.
 * @param MacAddr The MAC addres to return.
 *   This parameter can be one of the following values:
 *     @arg ETH_MAC_ADDR0 MAC Address0
 *     @arg ETH_MAC_ADDR1 MAC Address1
 *     @arg ETH_MAC_ADDR2 MAC Address2
 *     @arg ETH_MAC_ADDR3 MAC Address3
 * @param Addr Pointer on MAC address buffer data (6 bytes).
 */
void ETH_GetMacAddr(uint32_t MacAddr, uint8_t* Addr)
{
    uint32_t tmpregister;
    /* Check the parameters */
    assert_param(IS_ETH_MAC_ADDR0123(MacAddr));

    /* Get the selectecd MAC address high register */
    tmpregister = (*(__IO uint32_t*)(ETH_MAC_ADDR_HBASE + MacAddr));

    /* Calculate the selectecd MAC address buffer */
    Addr[5] = ((tmpregister >> 8) & (uint8_t)0xFF);
    Addr[4] = (tmpregister & (uint8_t)0xFF);
    /* Load the selectecd MAC address low register */
    tmpregister = (*(__IO uint32_t*)(ETH_MAC_ADDR_LBASE + MacAddr));
    /* Calculate the selectecd MAC address buffer */
    Addr[3] = ((tmpregister >> 24) & (uint8_t)0xFF);
    Addr[2] = ((tmpregister >> 16) & (uint8_t)0xFF);
    Addr[1] = ((tmpregister >> 8) & (uint8_t)0xFF);
    Addr[0] = (tmpregister & (uint8_t)0xFF);
}

/**
 * @brief  Enables or disables the Address filter module uses the specified
 *   ETHERNET MAC address for perfect filtering
 * @param MacAddr specifies the ETHERNET MAC address to be used for prfect filtering.
 *   This parameter can be one of the following values:
 *     @arg ETH_MAC_ADDR1 MAC Address1
 *     @arg ETH_MAC_ADDR2 MAC Address2
 *     @arg ETH_MAC_ADDR3 MAC Address3
 * @param Cmd new state of the specified ETHERNET MAC address use.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableMacAddrPerfectFilter(uint32_t MacAddr, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_ETH_MAC_ADDR123(MacAddr));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected ETHERNET MAC address for perfect filtering */
        (*(__IO uint32_t*)(ETH_MAC_ADDR_HBASE + MacAddr)) |= ETH_MACADDR1HI_AE;
    }
    else
    {
        /* Disable the selected ETHERNET MAC address for perfect filtering */
        (*(__IO uint32_t*)(ETH_MAC_ADDR_HBASE + MacAddr)) &= (~(uint32_t)ETH_MACADDR1HI_AE);
    }
}

/**
 * @brief  Set the filter type for the specified ETHERNET MAC address
 * @param MacAddr specifies the ETHERNET MAC address
 *   This parameter can be one of the following values:
 *     @arg ETH_MAC_ADDR1 MAC Address1
 *     @arg ETH_MAC_ADDR2 MAC Address2
 *     @arg ETH_MAC_ADDR3 MAC Address3
 * @param Filter specifies the used frame received field for comparaison
 *   This parameter can be one of the following values:
 *     @arg ETH_MAC_ADDR_FILTER_SA MAC Address is used to compare with the
 *                                     SA fields of the received frame.
 *     @arg ETH_MAC_ADDR_FILTER_DA MAC Address is used to compare with the
 *                                     DA fields of the received frame.
 */
void ETH_ConfigMacAddrFilter(uint32_t MacAddr, uint32_t Filter)
{
    /* Check the parameters */
    assert_param(IS_ETH_MAC_ADDR123(MacAddr));
    assert_param(IS_ETH_MAC_ADDR_FILTER(Filter));

    if (Filter != ETH_MAC_ADDR_FILTER_DA)
    {
        /* The selected ETHERNET MAC address is used to compare with the SA fields of the
        received frame. */
        (*(__IO uint32_t*)(ETH_MAC_ADDR_HBASE + MacAddr)) |= ETH_MACADDR1HI_SA;
    }
    else
    {
        /* The selected ETHERNET MAC address is used to compare with the DA fields of the
        received frame. */
        (*(__IO uint32_t*)(ETH_MAC_ADDR_HBASE + MacAddr)) &= (~(uint32_t)ETH_MACADDR1HI_SA);
    }
}

/**
 * @brief  Set the filter type for the specified ETHERNET MAC address
 * @param MacAddr specifies the ETHERNET MAC address
 *   This parameter can be one of the following values:
 *     @arg ETH_MAC_ADDR1 MAC Address1
 *     @arg ETH_MAC_ADDR2 MAC Address2
 *     @arg ETH_MAC_ADDR3 MAC Address3
 * @param MaskByte specifies the used address bytes for comparaison
 *   This parameter can be any combination of the following values:
 *     @arg ETH_MAC_ADDR_MASK_BYTE6 Mask MAC Address high reg bits [15:8].
 *     @arg ETH_MAC_ADDR_MASK_BYTE5 Mask MAC Address high reg bits [7:0].
 *     @arg ETH_MAC_ADDR_MASK_BYTE4 Mask MAC Address low reg bits [31:24].
 *     @arg ETH_MAC_ADDR_MASK_BYTE3 Mask MAC Address low reg bits [23:16].
 *     @arg ETH_MAC_ADDR_MASK_BYTE2 Mask MAC Address low reg bits [15:8].
 *     @arg ETH_MAC_ADDR_MASK_BYTE1 Mask MAC Address low reg bits [7:0].
 */
void ETH_ConfigMacAddrMaskBytesFilter(uint32_t MacAddr, uint32_t MaskByte)
{
    /* Check the parameters */
    assert_param(IS_ETH_MAC_ADDR123(MacAddr));
    assert_param(IS_ETH_MAC_ADDR_MASK(MaskByte));

    /* Clear MBC bits in the selected MAC address  high register */
    (*(__IO uint32_t*)(ETH_MAC_ADDR_HBASE + MacAddr)) &= (~(uint32_t)ETH_MACADDR1HI_MBC);
    /* Set the selected Filetr mask bytes */
    (*(__IO uint32_t*)(ETH_MAC_ADDR_HBASE + MacAddr)) |= MaskByte;
}
/*------------------------  DMA Tx/Rx Desciptors -----------------------------*/

/**
 * @brief  Initializes the DMA Tx descriptors in chain mode.
 * @param DMATxDescTab Pointer on the first Tx desc list
 * @param TxBuff Pointer on the first TxBuffer list
 * @param BuffSize Buffer size of each descriptor
 * @param TxBuffCount Number of the used Tx desc in the list
 */
void ETH_ConfigDmaTxDescInChainMode(ETH_DMADescType* DMATxDescTab,
                                    uint8_t* TxBuff,
                                    uint32_t BuffSize,
                                    uint32_t TxBuffCount)
{
    uint32_t i = 0;
    ETH_DMADescType* DMATxDesc;

    /* Set the DMATxDescToSet pointer with the first one of the DMATxDescTab list */
    DMATxDescToSet = DMATxDescTab;
    /* Fill each DMATxDesc descriptor with the right values */
    for (i = 0; i < TxBuffCount; i++)
    {
        /* Get the pointer on the ith member of the Tx Desc list */
        DMATxDesc = DMATxDescTab + i;
        /* Set Second Address Chained bit */
        DMATxDesc->Status        = 0;
        DMATxDesc->CtrlOrBufSize = ETH_DMA_TX_DESC_TCH;

        /* Set Buffer1 address pointer */
        DMATxDesc->Buf1Addr = (uint32_t)(&TxBuff[i * BuffSize]);

        /* Initialize the next descriptor with the Next Desciptor Polling Enable */
        if (i < (TxBuffCount - 1))
        {
            /* Set next descriptor address register with next descriptor base address */
            DMATxDesc->Buf2OrNextDescAddr = (uint32_t)(DMATxDescTab + i + 1);
        }
        else
        {
            /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
            DMATxDesc->Buf2OrNextDescAddr = (uint32_t)DMATxDescTab;
        }
    }

    /* Set Transmit Desciptor List Address Register */
    ETH->DMATXDLADDR = (uint32_t)DMATxDescTab;
}

/**
 * @brief  Initializes the DMA Tx descriptors in ring mode.
 * @param DMATxDescTab Pointer on the first Tx desc list
 * @param TxBuff1 Pointer on the first TxBuffer1 list
 * @param TxBuff2 Pointer on the first TxBuffer2 list
 * @param BuffSize Buffer size of each descriptor
 * @param TxBuffCount Number of the used Tx desc in the list
 *   Note: see decriptor skip length defined in ETH_DMA_InitStruct
 *   for the number of Words to skip between two unchained descriptors.
 */
void ETH_ConfigDmaTxDescInRingMode(ETH_DMADescType* DMATxDescTab,
                                   uint8_t* TxBuff1,
                                   uint8_t* TxBuff2,
                                   uint32_t BuffSize,
                                   uint32_t TxBuffCount)
{
    uint32_t i = 0;
    ETH_DMADescType* DMATxDesc;
    uint32_t dsl = (ETH->DMABUSMOD & ETH_DMABUSMOD_DSL) >> 2;

    /* Set the DMATxDescToSet pointer with the first one of the DMATxDescTab list */
    DMATxDescToSet = DMATxDescTab;
    /* Fill each DMATxDesc descriptor with the right values */
    for (i = 0; i < TxBuffCount; i++)
    {
        /* Get the pointer on the ith member of the Tx Desc list */
        // DMATxDesc = DMATxDescTab + i;
        DMATxDesc = (ETH_DMADescType*)((uint32_t)DMATxDescTab + i * (16 + 4 * dsl));
        /* Set Buffer1 address pointer */
        DMATxDesc->Buf1Addr = (uint32_t)(&TxBuff1[i * BuffSize]);

        /* Set Buffer2 address pointer */
        DMATxDesc->Buf2OrNextDescAddr = (uint32_t)(&TxBuff2[i * BuffSize]);

        /* Set Transmit End of Ring bit for last descriptor: The DMA returns to the base
        address of the list, creating a Desciptor Ring */
        if (i == (TxBuffCount - 1))
        {
            /* Set Transmit End of Ring bit */
            DMATxDesc->CtrlOrBufSize = ETH_DMA_TX_DESC_TER;
        }
    }

    /* Set Transmit Desciptor List Address Register */
    ETH->DMATXDLADDR = (uint32_t)DMATxDescTab;
}

/**
 * @brief  Checks whether the specified ETHERNET DMA Tx Desc flag is set or not.
 * @param DMATxDesc pointer on a DMA Tx descriptor
 * @param ETH_DMATxDescFlag specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg ETH_DMA_TX_DESC_OWN OWN bit: descriptor is owned by DMA engine
 *     @arg ETH_DMA_TX_DESC_IC Interrupt on completetion
 *     @arg ETH_DMA_TX_DESC_LS Last Segment
 *     @arg ETH_DMA_TX_DESC_FS First Segment
 *     @arg ETH_DMA_TX_DESC_DC Disable CRC
 *     @arg ETH_DMA_TX_DESC_DP Disable Pad
 *     @arg ETH_DMA_TX_DESC_TTSE Transmit Time Stamp Enable
 *     @arg ETH_DMA_TX_DESC_TER Transmit End of Ring
 *     @arg ETH_DMA_TX_DESC_TCH Second Address Chained
 *     @arg ETH_DMA_TX_DESC_TTSS Tx Time Stamp Status
 *     @arg ETH_DMA_TX_DESC_IHE IP Header Error
 *     @arg ETH_DMA_TX_DESC_ES Error summary
 *     @arg ETH_DMA_TX_DESC_JT Jabber Timeout
 *     @arg ETH_DMA_TX_DESC_FF Frame Flushed: DMA/MTL flushed the frame due to SW flush
 *     @arg ETH_DMA_TX_DESC_PCE Payload Checksum Error
 *     @arg ETH_DMA_TX_DESC_LOC Loss of Carrier: carrier lost during tramsmission
 *     @arg ETH_DMA_TX_DESC_NC No Carrier: no carrier signal from the tranceiver
 *     @arg ETH_DMA_TX_DESC_LC Late Collision: transmission aborted due to collision
 *     @arg ETH_DMA_TX_DESC_EC Excessive Collision: transmission aborted after 16 collisions
 *     @arg ETH_DMA_TX_DESC_VF VLAN Frame
 *     @arg ETH_DMA_TX_DESC_CC Collision Count
 *     @arg ETH_DMA_TX_DESC_ED Excessive Deferral
 *     @arg ETH_DMA_TX_DESC_UF Underflow Error: late data arrival from the memory
 *     @arg ETH_DMA_TX_DESC_DB Deferred Bit
 * @return The new state of ETH_DMATxDescFlag (SET or RESET).
 */
FlagStatus ETH_GetDmaTxDescFlagStatus(ETH_DMADescType* DMATxDesc, uint32_t ETH_DMATxDescFlag)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ETH_DMATXDESC_GET_FLAG(ETH_DMATxDescFlag));

    if ((DMATxDesc->Status & ETH_DMATxDescFlag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Returns the specified ETHERNET DMA Tx Desc collision count.
 * @param DMATxDesc pointer on a DMA Tx descriptor
 * @return The Transmit descriptor collision counter value.
 */
uint32_t ETH_GetDmaTxDescCollisionCount(ETH_DMADescType* DMATxDesc)
{
    /* Return the Receive descriptor frame length */
    return ((DMATxDesc->Status & ETH_DMA_TX_DESC_CC) >> ETH_DMA_TX_DESC_COLLISION_COUNTER_SHIFT);
}

/**
 * @brief  Set the specified DMA Tx Desc Own bit.
 * @param DMATxDesc Pointer on a Tx desc
 */
void ETH_SetDmaTxDescOwn(ETH_DMADescType* DMATxDesc)
{
    /* Set the DMA Tx Desc Own bit */
    DMATxDesc->Status |= ETH_DMA_TX_DESC_OWN;
}

/**
 * @brief  Enables or disables the specified DMA Tx Desc Transmit interrupt.
 * @param DMATxDesc Pointer on a Tx desc
 * @param Cmd new state of the DMA Tx Desc transmit interrupt.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableDmaTxDescTransmitInt(ETH_DMADescType* DMATxDesc, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the DMA Tx Desc Transmit interrupt */
        DMATxDesc->CtrlOrBufSize |= ETH_DMA_TX_DESC_IC;
    }
    else
    {
        /* Disable the DMA Tx Desc Transmit interrupt */
        DMATxDesc->CtrlOrBufSize &= (~(uint32_t)ETH_DMA_TX_DESC_IC);
    }
}

/**
 * @brief  Set the specified DMA Tx Desc frame segment.
 * @param DMATxDesc Pointer on a Tx desc
 * @param DMATxDesc_FrameSegment specifies is the actual Tx desc contain last or first segment.
 *   This parameter can be one of the following values:
 *     @arg ETH_DMA_TX_DESC_LAST_SEGMENT actual Tx desc contain last segment
 *     @arg ETH_DMA_TX_DESC_FIRST_SEGMENT actual Tx desc contain first segment
 */
void ETH_ConfigDmaTxDescFrameSegment(ETH_DMADescType* DMATxDesc, uint32_t DMATxDesc_FrameSegment)
{
    /* Check the parameters */
    assert_param(IS_ETH_DMA_TX_DESC_SEGMENT(DMATxDesc_FrameSegment));

    /* Selects the DMA Tx Desc Frame segment */
    DMATxDesc->CtrlOrBufSize |= DMATxDesc_FrameSegment;
}

/**
 * @brief  Selects the specified ETHERNET DMA Tx Desc Checksum Insertion.
 * @param DMATxDesc pointer on a DMA Tx descriptor
 * @param DMATxDesc_Checksum specifies is the DMA Tx desc checksum insertion.
 *   This parameter can be one of the following values:
 *     @arg ETH_DMA_TX_DESC_CHECKSUM_BYPASS Checksum bypass
 *     @arg ETH_DMA_TX_DESC_CHECKSUM_IPV4_HEADER IPv4 header checksum
 *     @arg ETH_DMA_TX_DESC_CHECKSUM_TCPUDPICMP_SEGMENT TCP/UDP/ICMP checksum. Pseudo header checksum is assumed to be
 * present
 *     @arg ETH_DMA_TX_DESC_CHECKSUM_TCPUDPICMP_FULL TCP/UDP/ICMP checksum fully in hardware including pseudo header
 */
void ETH_ConfigDmaTxDescChecksumInsertion(ETH_DMADescType* DMATxDesc, uint32_t DMATxDesc_Checksum)
{
    /* Check the parameters */
    assert_param(IS_ETH_DMA_TX_DESC_CHECKSUM(DMATxDesc_Checksum));

    /* Set the selected DMA Tx desc checksum insertion control */
    DMATxDesc->CtrlOrBufSize |= DMATxDesc_Checksum;
}

/**
 * @brief  Enables or disables the DMA Tx Desc CRC.
 * @param DMATxDesc pointer on a DMA Tx descriptor
 * @param Cmd new state of the specified DMA Tx Desc CRC.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableDmaTxDescCrc(ETH_DMADescType* DMATxDesc, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected DMA Tx Desc CRC */
        DMATxDesc->CtrlOrBufSize &= (~(uint32_t)ETH_DMA_TX_DESC_DC);
    }
    else
    {
        /* Disable the selected DMA Tx Desc CRC */
        DMATxDesc->CtrlOrBufSize |= ETH_DMA_TX_DESC_DC;
    }
}

/**
 * @brief  Enables or disables the DMA Tx Desc end of ring.
 * @param DMATxDesc pointer on a DMA Tx descriptor
 * @param Cmd new state of the specified DMA Tx Desc end of ring.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableDmaTxDescEndOfRing(ETH_DMADescType* DMATxDesc, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected DMA Tx Desc end of ring */
        DMATxDesc->CtrlOrBufSize |= ETH_DMA_TX_DESC_TER;
    }
    else
    {
        /* Disable the selected DMA Tx Desc end of ring */
        DMATxDesc->CtrlOrBufSize &= (~(uint32_t)ETH_DMA_TX_DESC_TER);
    }
}

/**
 * @brief  Enables or disables the DMA Tx Desc second address chained.
 * @param DMATxDesc pointer on a DMA Tx descriptor
 * @param Cmd new state of the specified DMA Tx Desc second address chained.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableDmaTxDescSecondAddrChained(ETH_DMADescType* DMATxDesc, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected DMA Tx Desc second address chained */
        DMATxDesc->CtrlOrBufSize |= ETH_DMA_TX_DESC_TCH;
    }
    else
    {
        /* Disable the selected DMA Tx Desc second address chained */
        DMATxDesc->CtrlOrBufSize &= (~(uint32_t)ETH_DMA_TX_DESC_TCH);
    }
}

/**
 * @brief  Enables or disables the DMA Tx Desc padding for frame shorter than 64 bytes.
 * @param DMATxDesc pointer on a DMA Tx descriptor
 * @param Cmd new state of the specified DMA Tx Desc padding for frame shorter than 64 bytes.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableDmaTxDescShortFramePadding(ETH_DMADescType* DMATxDesc, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected DMA Tx Desc padding for frame shorter than 64 bytes */
        DMATxDesc->CtrlOrBufSize &= (~(uint32_t)ETH_DMA_TX_DESC_DP);
    }
    else
    {
        /* Disable the selected DMA Tx Desc padding for frame shorter than 64 bytes*/
        DMATxDesc->CtrlOrBufSize |= ETH_DMA_TX_DESC_DP;
    }
}

/**
 * @brief  Enables or disables the DMA Tx Desc time stamp.
 * @param DMATxDesc pointer on a DMA Tx descriptor
 * @param Cmd new state of the specified DMA Tx Desc time stamp.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableDmaTxDescTimeStamp(ETH_DMADescType* DMATxDesc, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected DMA Tx Desc time stamp */
        DMATxDesc->CtrlOrBufSize |= ETH_DMA_TX_DESC_TTSE;
    }
    else
    {
        /* Disable the selected DMA Tx Desc time stamp */
        DMATxDesc->CtrlOrBufSize &= (~(uint32_t)ETH_DMA_TX_DESC_TTSE);
    }
}

/**
 * @brief  Configures the specified DMA Tx Desc buffer1 and buffer2 sizes.
 * @param DMATxDesc Pointer on a Tx desc
 * @param BufferSize1 specifies the Tx desc buffer1 size.
 * @param BufferSize2 specifies the Tx desc buffer2 size (put "0" if not used).
 */
void ETH_ConfigDmaTxDescBufSize(ETH_DMADescType* DMATxDesc, uint32_t BufferSize1, uint32_t BufferSize2)
{
    /* Check the parameters */
    assert_param(IS_ETH_DMA_TX_DESC_BUFFER_SIZE(BufferSize1));
    assert_param(IS_ETH_DMA_TX_DESC_BUFFER_SIZE(BufferSize2));

    /* Set the DMA Tx Desc buffer1 and buffer2 sizes values */
    DMATxDesc->CtrlOrBufSize |= (BufferSize1 | (BufferSize2 << ETH_DMA_TX_DESC_BUF2_SIZE_SHIFT));
}

/**
 * @brief  Initializes the DMA Rx descriptors in chain mode.
 * @param DMARxDescTab Pointer on the first Rx desc list
 * @param RxBuff Pointer on the first RxBuffer list
 * @param BuffSize the buffer size of each RxBuffer
 * @param RxBuffCount Number of the used Rx desc in the list
 */
void ETH_ConfigDmaRxDescInChainMode(ETH_DMADescType* DMARxDescTab,
                                    uint8_t* RxBuff,
                                    uint32_t BuffSize,
                                    uint32_t RxBuffCount)
{
    uint32_t i = 0;
    ETH_DMADescType* DMARxDesc;

    /* Set the DMARxDescToGet pointer with the first one of the DMARxDescTab list */
    DMARxDescToGet = DMARxDescTab;
    /* Fill each DMARxDesc descriptor with the right values */
    for (i = 0; i < RxBuffCount; i++)
    {
        /* Get the pointer on the ith member of the Rx Desc list */
        DMARxDesc = DMARxDescTab + i;
        /* Set Own bit of the Rx descriptor Status */
        DMARxDesc->Status = ETH_DMA_RX_DESC_OWN;

        /* Set Buffer1 size and Second Address Chained bit */
        DMARxDesc->CtrlOrBufSize = ETH_DMA_RX_DESC_RCH | (uint32_t)(BuffSize & 0x1FFFUL);
        /* Set Buffer1 address pointer */
        DMARxDesc->Buf1Addr = (uint32_t)(&RxBuff[i * BuffSize]);

        /* Initialize the next descriptor with the Next Desciptor Polling Enable */
        if (i < (RxBuffCount - 1))
        {
            /* Set next descriptor address register with next descriptor base address */
            DMARxDesc->Buf2OrNextDescAddr = (uint32_t)(DMARxDescTab + i + 1);
        }
        else
        {
            /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
            DMARxDesc->Buf2OrNextDescAddr = (uint32_t)(DMARxDescTab);
        }
    }

    /* Set Receive Desciptor List Address Register */
    ETH->DMARXDLADDR = (uint32_t)DMARxDescTab;
}

/**
 * @brief  Initializes the DMA Rx descriptors in ring mode.
 * @param DMARxDescTab Pointer on the first Rx desc list
 * @param RxBuff1 Pointer on the first RxBuffer1 list
 * @param RxBuff2 Pointer on the first RxBuffer2 list
 * @param BuffSize the buffer size of each RxBuffer
 * @param RxBuffCount Number of the used Rx desc in the list
 *   Note: see decriptor skip length defined in ETH_DMA_InitStruct
 *   for the number of Words to skip between two unchained descriptors.
 */
void ETH_ConfigDmaRxDescInRingMode(ETH_DMADescType* DMARxDescTab,
                                   uint8_t* RxBuff1,
                                   uint8_t* RxBuff2,
                                   uint32_t BuffSize,
                                   uint32_t RxBuffCount)
{
    uint32_t i = 0;
    ETH_DMADescType* DMARxDesc;
    uint32_t dsl = (ETH->DMABUSMOD & ETH_DMABUSMOD_DSL) >> 2;
    /* Set the DMARxDescToGet pointer with the first one of the DMARxDescTab list */
    DMARxDescToGet = DMARxDescTab;
    /* Fill each DMARxDesc descriptor with the right values */
    for (i = 0; i < RxBuffCount; i++)
    {
        /* Get the pointer on the ith member of the Rx Desc list */
        // DMARxDesc = DMARxDescTab + i;
        DMARxDesc = (ETH_DMADescType*)((uint32_t)DMARxDescTab + i * (16 + 4 * dsl));
        /* Set Own bit of the Rx descriptor Status */
        DMARxDesc->Status = ETH_DMA_RX_DESC_OWN;
        /* Set Buffer1 size */
        DMARxDesc->CtrlOrBufSize = BuffSize;
        /* Set Buffer1 address pointer */
        DMARxDesc->Buf1Addr = (uint32_t)(&RxBuff1[i * BuffSize]);

        /* Set Buffer2 address pointer */
        DMARxDesc->Buf2OrNextDescAddr = (uint32_t)(&RxBuff2[i * BuffSize]);

        /* Set Receive End of Ring bit for last descriptor: The DMA returns to the base
        address of the list, creating a Desciptor Ring */
        if (i == (RxBuffCount - 1))
        {
            /* Set Receive End of Ring bit */
            DMARxDesc->CtrlOrBufSize |= ETH_DMA_RX_DESC_RER;
        }
    }

    /* Set Receive Desciptor List Address Register */
    ETH->DMARXDLADDR = (uint32_t)DMARxDescTab;
}

/**
 * @brief  Checks whether the specified ETHERNET Rx Desc flag is set or not.
 * @param DMARxDesc pointer on a DMA Rx descriptor
 * @param ETH_DMARxDescFlag specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg ETH_DMA_RX_DESC_OWN OWN bit: descriptor is owned by DMA engine
 *     @arg ETH_DMA_RX_DESC_AFM DA Filter Fail for the rx frame
 *     @arg ETH_DMA_RX_DESC_ES Error summary
 *     @arg ETH_DMA_RX_DESC_DE Desciptor error: no more descriptors for receive frame
 *     @arg ETH_DMA_RX_DESC_SAF SA Filter Fail for the received frame
 *     @arg ETH_DMA_RX_DESC_LE Frame size not matching with length field
 *     @arg ETH_DMA_RX_DESC_OE Overflow Error: Frame was damaged due to buffer overflow
 *     @arg ETH_DMA_RX_DESC_VLAN VLAN Tag: received frame is a VLAN frame
 *     @arg ETH_DMA_RX_DESC_FS First descriptor of the frame
 *     @arg ETH_DMA_RX_DESC_LS Last descriptor of the frame
 *     @arg ETH_DMA_RX_DESC_IPV4HCE IPC Checksum Error/Giant Frame: Rx Ipv4 header checksum error
 *     @arg ETH_DMA_RX_DESC_LC Late collision occurred during reception
 *     @arg ETH_DMA_RX_DESC_FT Frame type - Ethernet, otherwise 802.3
 *     @arg ETH_DMA_RX_DESC_RWT Receive Watchdog Timeout: watchdog timer expired during reception
 *     @arg ETH_DMA_RX_DESC_RE Receive error: error reported by MII interface
 *     @arg ETH_DMA_RX_DESC_DE Dribble bit error: frame contains non int multiple of 8 bits
 *     @arg ETH_DMA_RX_DESC_CE CRC error
 *     @arg ETH_DMA_RX_DESC_RMAPCE Rx MAC Address/Payload Checksum Error: Rx MAC address matched/ Rx Payload Checksum
 * Error
 * @return The new state of ETH_DMARxDescFlag (SET or RESET).
 */
FlagStatus ETH_GetDmaRxDescFlagStatus(ETH_DMADescType* DMARxDesc, uint32_t ETH_DMARxDescFlag)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ETH_DMA_RX_DESC_GET_FLAG(ETH_DMARxDescFlag));
    if ((DMARxDesc->Status & ETH_DMARxDescFlag) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Set the specified DMA Rx Desc Own bit.
 * @param DMARxDesc Pointer on a Rx desc
 */
void ETH_SetDmaRxDescOwn(ETH_DMADescType* DMARxDesc)
{
    /* Set the DMA Rx Desc Own bit */
    DMARxDesc->Status |= ETH_DMA_RX_DESC_OWN;
}

/**
 * @brief  Returns the specified DMA Rx Desc frame length.
 * @param DMARxDesc pointer on a DMA Rx descriptor
 * @return The Rx descriptor received frame length.
 */
uint32_t ETH_GetDmaRxDescFrameLen(__IO ETH_DMADescType* DMARxDesc)
{
    /* Return the Receive descriptor frame length */
    return ((DMARxDesc->Status & ETH_DMA_RX_DESC_FL) >> ETH_DMA_RX_DESC_FRAME_LEN_SHIFT);
}

/**
 * @brief  Enables or disables the specified DMA Rx Desc receive interrupt.
 * @param DMARxDesc Pointer on a Rx desc
 * @param Cmd new state of the specified DMA Rx Desc interrupt.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableDmaRxDescReceiveInt(ETH_DMADescType* DMARxDesc, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the DMA Rx Desc receive interrupt */
        DMARxDesc->CtrlOrBufSize &= (~(uint32_t)ETH_DMA_RX_DESC_DIC);
    }
    else
    {
        /* Disable the DMA Rx Desc receive interrupt */
        DMARxDesc->CtrlOrBufSize |= ETH_DMA_RX_DESC_DIC;
    }
}

/**
 * @brief  Enables or disables the DMA Rx Desc end of ring.
 * @param DMARxDesc pointer on a DMA Rx descriptor
 * @param Cmd new state of the specified DMA Rx Desc end of ring.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableDmaRxDescEndOfRing(ETH_DMADescType* DMARxDesc, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected DMA Rx Desc end of ring */
        DMARxDesc->CtrlOrBufSize |= ETH_DMA_RX_DESC_RER;
    }
    else
    {
        /* Disable the selected DMA Rx Desc end of ring */
        DMARxDesc->CtrlOrBufSize &= (~(uint32_t)ETH_DMA_RX_DESC_RER);
    }
}

/**
 * @brief  Enables or disables the DMA Rx Desc second address chained.
 * @param DMARxDesc pointer on a DMA Rx descriptor
 * @param Cmd new state of the specified DMA Rx Desc second address chained.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableDmaRxDescSecondAddrChained(ETH_DMADescType* DMARxDesc, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected DMA Rx Desc second address chained */
        DMARxDesc->CtrlOrBufSize |= ETH_DMA_RX_DESC_RCH;
    }
    else
    {
        /* Disable the selected DMA Rx Desc second address chained */
        DMARxDesc->CtrlOrBufSize &= (~(uint32_t)ETH_DMA_RX_DESC_RCH);
    }
}

/**
 * @brief  Returns the specified ETHERNET DMA Rx Desc buffer size.
 * @param DMARxDesc pointer on a DMA Rx descriptor
 * @param DMARxDesc_Buffer specifies the DMA Rx Desc buffer.
 *   This parameter can be any one of the following values:
 *     @arg ETH_DMA_RX_DESC_BUFFER1 DMA Rx Desc Buffer1
 *     @arg ETH_DMA_RX_DESC_BUFFER2 DMA Rx Desc Buffer2
 * @return The Receive descriptor frame length.
 */
uint32_t ETH_GetDmaRxDescBufSize(ETH_DMADescType* DMARxDesc, uint32_t DMARxDesc_Buffer)
{
    /* Check the parameters */
    assert_param(IS_ETH_DMA_RXDESC_BUFFER(DMARxDesc_Buffer));

    if (DMARxDesc_Buffer != ETH_DMA_RX_DESC_BUFFER1)
    {
        /* Return the DMA Rx Desc buffer2 size */
        return ((DMARxDesc->CtrlOrBufSize & ETH_DMA_RX_DESC_RBS2) >> ETH_DMA_RX_DESC_BUF2_SIZE_SHIFT);
    }
    else
    {
        /* Return the DMA Rx Desc buffer1 size */
        return (DMARxDesc->CtrlOrBufSize & ETH_DMA_RX_DESC_RBS1);
    }
}

/*---------------------------------  DMA  ------------------------------------*/
/**
 * @brief  Resets all MAC subsystem internal registers and logic.
 */
void ETH_SoftwareReset(void)
{
    /* Set the SWR bit: resets all MAC subsystem internal registers and logic */
    /* After reset all the registers holds their respective reset values */
    ETH->DMABUSMOD |= ETH_DMABUSMOD_SWR;
}

/**
 * @brief  Checks whether the ETHERNET software reset bit is set or not.
 * @return The new state of DMA Bus Mode register STS bit (SET or RESET).
 */
FlagStatus ETH_GetSoftwareResetStatus(void)
{
    FlagStatus bitstatus = RESET;
    if ((ETH->DMABUSMOD & ETH_DMABUSMOD_SWR) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Checks whether the specified ETHERNET DMA flag is set or not.
 * @param ETH_DMA_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg ETH_DMA_FLAG_TST Time-stamp trigger flag
 *     @arg ETH_DMA_FLAG_PMT PMT flag
 *     @arg ETH_DMA_FLAG_MMC MMC flag
 *     @arg ETH_DMA_FLAG_DATA_TRANSFER_ERROR Error bits 0-data buffer, 1-desc. access
 *     @arg ETH_DMA_FLAG_READ_WRITE_ERROR Error bits 0-write trnsf, 1-read transfr
 *     @arg ETH_DMA_FLAG_ACCESS_ERROR Error bits 0-Rx DMA, 1-Tx DMA
 *     @arg ETH_DMA_FLAG_NIS Normal interrupt summary flag
 *     @arg ETH_DMA_FLAG_AIS Abnormal interrupt summary flag
 *     @arg ETH_DMA_FLAG_EARLY_RX Early receive flag
 *     @arg ETH_DMA_FLAG_FATAL_BUS_ERROR Fatal bus error flag
 *     @arg ETH_DMA_FLAG_EARLY_TX Early transmit flag
 *     @arg ETH_DMA_FLAG_RX_WDG_TIMEOUT Receive watchdog timeout flag
 *     @arg ETH_DMA_FLAG_RX_PROC_STOP Receive process stopped flag
 *     @arg ETH_DMA_FLAG_RX_BUF_UA Receive buffer unavailable flag
 *     @arg ETH_DMA_FLAG_RX Receive flag
 *     @arg ETH_DMA_FLAG_TX_UNDERFLOW Underflow flag
 *     @arg ETH_DMA_FLAG_RX_OVERFLOW Overflow flag
 *     @arg ETH_DMA_FLAG_TX_JABBER_TIMEOUT Transmit jabber timeout flag
 *     @arg ETH_DMA_FLAG_TX_BUF_UA Transmit buffer unavailable flag
 *     @arg ETH_DMA_FLAG_TX_PROC_STOP Transmit process stopped flag
 *     @arg ETH_DMA_FLAG_TX Transmit flag
 * @return The new state of ETH_DMA_FLAG (SET or RESET).
 */
FlagStatus ETH_GetDmaFlagStatus(uint32_t ETH_DMA_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ETH_DMA_GET_INT(ETH_DMA_FLAG));
    if ((ETH->DMASTS & ETH_DMA_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Clears the ETHERNET's DMA pending flag.
 * @param ETH_DMA_FLAG specifies the flag to clear.
 *   This parameter can be any combination of the following values:
 *     @arg ETH_DMA_FLAG_NIS Normal interrupt summary flag
 *     @arg ETH_DMA_FLAG_AIS Abnormal interrupt summary flag
 *     @arg ETH_DMA_FLAG_EARLY_RX Early receive flag
 *     @arg ETH_DMA_FLAG_FATAL_BUS_ERROR Fatal bus error flag
 *     @arg ETH_DMA_FLAG_ETI Early transmit flag
 *     @arg ETH_DMA_FLAG_RX_WDG_TIMEOUT Receive watchdog timeout flag
 *     @arg ETH_DMA_FLAG_RX_PROC_STOP Receive process stopped flag
 *     @arg ETH_DMA_FLAG_RX_BUF_UA Receive buffer unavailable flag
 *     @arg ETH_DMA_FLAG_RX Receive flag
 *     @arg ETH_DMA_FLAG_TX_UNDERFLOW Transmit Underflow flag
 *     @arg ETH_DMA_FLAG_RX_OVERFLOW Receive Overflow flag
 *     @arg ETH_DMA_FLAG_TX_JABBER_TIMEOUT Transmit jabber timeout flag
 *     @arg ETH_DMA_FLAG_TX_BUF_UA Transmit buffer unavailable flag
 *     @arg ETH_DMA_FLAG_TX_PROC_STOP Transmit process stopped flag
 *     @arg ETH_DMA_FLAG_TX Transmit flag
 */
void ETH_ClrDmaFlag(uint32_t ETH_DMA_FLAG)
{
    /* Check the parameters */
    assert_param(IS_ETH_DMA_FLAG(ETH_DMA_FLAG));

    /* Clear the selected ETHERNET DMA FLAG */
    ETH->DMASTS = (uint32_t)ETH_DMA_FLAG;
}

/**
 * @brief  Checks whether the specified ETHERNET DMA interrupt has occured or not.
 * @param ETH_DMA_IT specifies the interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg ETH_DMA_INT_TST Time-stamp trigger interrupt
 *     @arg ETH_DMA_INT_PMT PMT interrupt
 *     @arg ETH_DMA_INT_MMC MMC interrupt
 *     @arg ETH_DMA_INT_NIS Normal interrupt summary
 *     @arg ETH_DMA_INT_AIS Abnormal interrupt summary
 *     @arg ETH_DMA_INT_EARLY_RX Early receive interrupt
 *     @arg ETH_DMA_INT_FATAL_BUS_ERROR Fatal bus error interrupt
 *     @arg ETH_DMA_INT_EARLY_TX Early transmit interrupt
 *     @arg ETH_DMA_INT_RX_WDG_TIMEOUT Receive watchdog timeout interrupt
 *     @arg ETH_DMA_INT_RX_PROC_STOP Receive process stopped interrupt
 *     @arg ETH_DMA_INT_RX_BUF_UA Receive buffer unavailable interrupt
 *     @arg ETH_DMA_INT_RX Receive interrupt
 *     @arg ETH_DMA_INT_TX_UNDERFLOW Underflow interrupt
 *     @arg ETH_DMA_INT_RX_OVERFLOW Overflow interrupt
 *     @arg ETH_DMA_INT_TX_JABBER_TIMEOUT Transmit jabber timeout interrupt
 *     @arg ETH_DMA_INT_TX_BUF_UA Transmit buffer unavailable interrupt
 *     @arg ETH_DMA_INT_TX_PROC_STOP Transmit process stopped interrupt
 *     @arg ETH_DMA_INT_TX Transmit interrupt
 * @return The new state of ETH_DMA_IT (SET or RESET).
 */
INTStatus ETH_GetDmaIntStatus(uint32_t ETH_DMA_IT)
{
    INTStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ETH_DMA_GET_INT(ETH_DMA_IT));
    if ((ETH->DMASTS & ETH_DMA_IT) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Clears the ETHERNET's DMA IT pending bit.
 * @param ETH_DMA_IT specifies the interrupt pending bit to clear.
 *   This parameter can be any combination of the following values:
 *     @arg ETH_DMA_INT_NIS Normal interrupt summary
 *     @arg ETH_DMA_INT_AIS Abnormal interrupt summary
 *     @arg ETH_DMA_INT_EARLY_RX Early receive interrupt
 *     @arg ETH_DMA_INT_FATAL_BUS_ERROR Fatal bus error interrupt
 *     @arg ETH_DMA_IT_ETI Early transmit interrupt
 *     @arg ETH_DMA_INT_RX_WDG_TIMEOUT Receive watchdog timeout interrupt
 *     @arg ETH_DMA_INT_RX_PROC_STOP Receive process stopped interrupt
 *     @arg ETH_DMA_INT_RX_BUF_UA Receive buffer unavailable interrupt
 *     @arg ETH_DMA_INT_RX Receive interrupt
 *     @arg ETH_DMA_INT_TX_UNDERFLOW Transmit Underflow interrupt
 *     @arg ETH_DMA_INT_RX_OVERFLOW Receive Overflow interrupt
 *     @arg ETH_DMA_INT_TX_JABBER_TIMEOUT Transmit jabber timeout interrupt
 *     @arg ETH_DMA_INT_TX_BUF_UA Transmit buffer unavailable interrupt
 *     @arg ETH_DMA_INT_TX_PROC_STOP Transmit process stopped interrupt
 *     @arg ETH_DMA_INT_TX Transmit interrupt
 */
void ETH_ClrDmaIntPendingBit(uint32_t ETH_DMA_IT)
{
    /* Check the parameters */
    assert_param(IS_ETH_DMA_INT(ETH_DMA_IT));

    /* Clear the selected ETHERNET DMA IT */
    ETH->DMASTS = (uint32_t)ETH_DMA_IT;
}

/**
 * @brief  Returns the ETHERNET DMA Transmit Process State.
 * @return The new ETHERNET DMA Transmit Process State:
 *   This can be one of the following values:
 *     - ETH_DMA_TX_PROC_STOPPED   : Stopped - Reset or Stop Tx Command issued
 *     - ETH_DMA_TX_PROC_FETCHING  : Running - fetching the Tx descriptor
 *     - ETH_DMA_TX_PROC_WAITING   : Running - waiting for status
 *     - ETH_DMA_TX_PROC_READING   : unning - reading the data from host memory
 *     - ETH_DMA_TX_PROC_SUSPENDED : Suspended - Tx Desciptor unavailabe
 *     - ETH_DMA_TX_PROC_CLOSING   : Running - closing Rx descriptor
 */
uint32_t ETH_GetTxProcState(void)
{
    return ((uint32_t)(ETH->DMASTS & ETH_DMASTS_TI));
}

/**
 * @brief  Returns the ETHERNET DMA Receive Process State.
 * @return The new ETHERNET DMA Receive Process State:
 *   This can be one of the following values:
 *     - ETH_DMA_RX_PROC_STOPPED   : Stopped - Reset or Stop Rx Command issued
 *     - ETH_DMA_RX_PROC_FETCHING  : Running - fetching the Rx descriptor
 *     - ETH_DMA_RX_PROC_WAITING   : Running - waiting for packet
 *     - ETH_DMA_RX_PROC_SUSPENDED : Suspended - Rx Desciptor unavailable
 *     - ETH_DMA_RX_PROC_CLOSING   : Running - closing descriptor
 *     - ETH_DMA_RX_PROC_QUEUING   : Running - queuing the recieve frame into host memory
 */
uint32_t ETH_GetRxProcState(void)
{
    return ((uint32_t)(ETH->DMASTS & ETH_DMASTS_RI));
}

/**
 * @brief  Clears the ETHERNET transmit DATFIFO.
 */
void ETH_FlushTxFifo(void)
{
    /* Set the Flush Transmit DATFIFO bit */
    ETH->DMAOPMOD |= ETH_DMAOPMOD_FTF;
}

/**
 * @brief  Checks whether the ETHERNET transmit DATFIFO bit is cleared or not.
 * @return The new state of ETHERNET flush transmit DATFIFO bit (SET or RESET).
 */
FlagStatus ETH_GetFlushTxFifoStatus(void)
{
    FlagStatus bitstatus = RESET;
    if ((ETH->DMAOPMOD & ETH_DMAOPMOD_FTF) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Enables or disables the DMA transmission.
 * @param Cmd new state of the DMA transmission.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableDmaTx(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the DMA transmission */
        ETH->DMAOPMOD |= ETH_DMAOPMOD_ST;
    }
    else
    {
        /* Disable the DMA transmission */
        ETH->DMAOPMOD &= ~ETH_DMAOPMOD_ST;
    }
}

/**
 * @brief  Enables or disables the DMA reception.
 * @param Cmd new state of the DMA reception.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableDmaRx(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the DMA reception */
        ETH->DMAOPMOD |= ETH_DMAOPMOD_SR;
    }
    else
    {
        /* Disable the DMA reception */
        ETH->DMAOPMOD &= ~ETH_DMAOPMOD_SR;
    }
}

/**
 * @brief  Enables or disables the specified ETHERNET DMA interrupts.
 * @param ETH_DMA_IT specifies the ETHERNET DMA interrupt sources to be
 *   enabled or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg ETH_DMA_INT_NIS Normal interrupt summary
 *     @arg ETH_DMA_INT_AIS Abnormal interrupt summary
 *     @arg ETH_DMA_INT_EARLY_RX Early receive interrupt
 *     @arg ETH_DMA_INT_FATAL_BUS_ERROR Fatal bus error interrupt
 *     @arg ETH_DMA_INT_EARLY_TX Early transmit interrupt
 *     @arg ETH_DMA_INT_RX_WDG_TIMEOUT Receive watchdog timeout interrupt
 *     @arg ETH_DMA_INT_RX_PROC_STOP Receive process stopped interrupt
 *     @arg ETH_DMA_INT_RX_BUF_UA Receive buffer unavailable interrupt
 *     @arg ETH_DMA_INT_RX Receive interrupt
 *     @arg ETH_DMA_INT_TX_UNDERFLOW Underflow interrupt
 *     @arg ETH_DMA_INT_RX_OVERFLOW Overflow interrupt
 *     @arg ETH_DMA_INT_TX_JABBER_TIMEOUT Transmit jabber timeout interrupt
 *     @arg ETH_DMA_INT_TX_BUF_UA Transmit buffer unavailable interrupt
 *     @arg ETH_DMA_INT_TX_PROC_STOP Transmit process stopped interrupt
 *     @arg ETH_DMA_INT_TX Transmit interrupt
 * @param Cmd new state of the specified ETHERNET DMA interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableDmaInt(uint32_t ETH_DMA_IT, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_ETH_DMA_INT(ETH_DMA_IT));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected ETHERNET DMA interrupts */
        ETH->DMAINTEN |= ETH_DMA_IT;
    }
    else
    {
        /* Disable the selected ETHERNET DMA interrupts */
        ETH->DMAINTEN &= (~(uint32_t)ETH_DMA_IT);
    }
}

/**
 * @brief  Checks whether the specified ETHERNET DMA overflow flag is set or not.
 * @param ETH_DMA_Overflow specifies the DMA overflow flag to check.
 *   This parameter can be one of the following values:
 *     @arg ETH_DMA_OVERFLOW_RX_FIFO_COUNTER Overflow for DATFIFO Overflow Counter
 *     @arg ETH_DMA_OVERFLOW_MISSED_FRAME_COUNTER Overflow for Missed Frame Counter
 * @return The new state of ETHERNET DMA overflow Flag (SET or RESET).
 */
FlagStatus ETH_GetDmaOverflowStatus(uint32_t ETH_DMA_Overflow)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ETH_DMA_GET_OVERFLOW(ETH_DMA_Overflow));

    if ((ETH->DMAMFBOCNT & ETH_DMA_Overflow) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Get the ETHERNET DMA Rx Overflow Missed Frame Counter value.
 * @return The value of Rx overflow Missed Frame Counter.
 */
uint32_t ETH_GetRxOverflowMissedFrameCounter(void)
{
    return ((uint32_t)((ETH->DMAMFBOCNT & ETH_DMAMFBOCNT_OVFFRMCNT) >> ETH_DMA_RX_OVERFLOW_MISSEDFRAMES_COUNTER_SHIFT));
}

/**
 * @brief  Get the ETHERNET DMA Buffer Unavailable Missed Frame Counter value.
 * @return The value of Buffer unavailable Missed Frame Counter.
 */
uint32_t ETH_GetBufUnavailableMissedFrameCounter(void)
{
    return ((uint32_t)(ETH->DMAMFBOCNT) & ETH_DMAMFBOCNT_MISFRMCNT);
}

/**
 * @brief  Get the ETHERNET DMA DMACHTXDESC register value.
 * @return The value of the current Tx desc start address.
 */
uint32_t ETH_GetCurrentTxDescAddr(void)
{
    return ((uint32_t)(ETH->DMACHTXDESC));
}

/**
 * @brief  Get the ETHERNET DMA DMACHRXDESC register value.
 * @return The value of the current Rx desc start address.
 */
uint32_t ETH_GetCurrentRxDescAddr(void)
{
    return ((uint32_t)(ETH->DMACHRXDESC));
}

/**
 * @brief  Get the ETHERNET DMA DMACHTXBADDR register value.
 * @return The value of the current Tx buffer address.
 */
uint32_t ETH_GetCurrentTxBufAddr(void)
{
    return ((uint32_t)(ETH->DMACHTXBADDR));
}

/**
 * @brief  Get the ETHERNET DMA DMACHRXBADDR register value.
 * @return The value of the current Rx buffer address.
 */
uint32_t ETH_GetCurrentRxBufAddr(void)
{
    return ((uint32_t)(ETH->DMACHRXBADDR));
}

/**
 * @brief  Resumes the DMA Transmission by writing to the DmaTxPollDemand register
 *   (the data written could be anything). This forces  the DMA to resume transmission.
 */
void ETH_ResumeDmaTx(void)
{
    ETH->DMATXPD = 0;
}

/**
 * @brief  Resumes the DMA Transmission by writing to the DmaRxPollDemand register
 *   (the data written could be anything). This forces the DMA to resume reception.
 */
void ETH_ResumeDmaRx(void)
{
    ETH->DMARXPD = 0;
}

/*---------------------------------  PMT  ------------------------------------*/
/**
 * @brief  Reset Wakeup frame filter register pointer.
 */
void ETH_ResetWakeUpFrameFilter(void)
{
    /* Resets the Remote Wake-up Frame Filter register pointer to 0x0000 */
    ETH->MACPMTCTRLSTS |= ETH_MACPMTCTRLSTS_RWKUPFLTRST;
}

/**
 * @brief  Populates the remote wakeup frame registers.
 * @param Buffer Pointer on remote WakeUp Frame Filter Register buffer data (8 words).
 */
void ETH_SetWakeUpFrameFilter(uint32_t* Buffer)
{
    uint32_t i = 0;

    /* Fill Remote Wake-up Frame Filter register with Buffer data */
    for (i = 0; i < ETH_WAKEUP_REG_LEN; i++)
    {
        /* Write each time to the same register */
        ETH->MACRMTWUFRMFLT = Buffer[i];
    }
}

/**
 * @brief  Enables or disables any unicast packet filtered by the MAC address
 *   recognition to be a wake-up frame.
 * @param Cmd new state of the MAC Global Unicast Wake-Up.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableGlobalUnicastWakeUp(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the MAC Global Unicast Wake-Up */
        ETH->MACPMTCTRLSTS |= ETH_MACPMTCTRLSTS_GLBLUCAST;
    }
    else
    {
        /* Disable the MAC Global Unicast Wake-Up */
        ETH->MACPMTCTRLSTS &= ~ETH_MACPMTCTRLSTS_GLBLUCAST;
    }
}

/**
 * @brief  Checks whether the specified ETHERNET PMT flag is set or not.
 * @param ETH_PMT_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg ETH_PMT_FLAG_RWKUPFILTRST Wake-Up Frame Filter Register Poniter Reset
 *     @arg ETH_PMT_FLAG_RWKPRCVD Wake-Up Frame Received
 *     @arg ETH_PMT_FLAG_MGKPRCVD Magic Packet Received
 * @return The new state of ETHERNET PMT Flag (SET or RESET).
 */
FlagStatus ETH_GetPmtFlagStatus(uint32_t ETH_PMT_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ETH_PMT_GET_FLAG(ETH_PMT_FLAG));

    if ((ETH->MACPMTCTRLSTS & ETH_PMT_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Enables or disables the MAC Wake-Up Frame Detection.
 * @param Cmd new state of the MAC Wake-Up Frame Detection.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableWakeUpFrameDetection(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the MAC Wake-Up Frame Detection */
        ETH->MACPMTCTRLSTS |= ETH_MACPMTCTRLSTS_RWKPKTEN;
    }
    else
    {
        /* Disable the MAC Wake-Up Frame Detection */
        ETH->MACPMTCTRLSTS &= ~ETH_MACPMTCTRLSTS_RWKPKTEN;
    }
}

/**
 * @brief  Enables or disables the MAC Magic Packet Detection.
 * @param Cmd new state of the MAC Magic Packet Detection.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableMagicPacketDetection(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the MAC Magic Packet Detection */
        ETH->MACPMTCTRLSTS |= ETH_MACPMTCTRLSTS_MGKPKTEN;
    }
    else
    {
        /* Disable the MAC Magic Packet Detection */
        ETH->MACPMTCTRLSTS &= ~ETH_MACPMTCTRLSTS_MGKPKTEN;
    }
}

/**
 * @brief  Enables or disables the MAC Power Down.
 * @param Cmd new state of the MAC Power Down.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnablePowerDown(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the MAC Power Down */
        /* This puts the MAC in power down mode */
        ETH->MACPMTCTRLSTS |= ETH_MACPMTCTRLSTS_PWRDWN;
    }
    else
    {
        /* Disable the MAC Power Down */
        ETH->MACPMTCTRLSTS &= ~ETH_MACPMTCTRLSTS_PWRDWN;
    }
}

/*---------------------------------  MMC  ------------------------------------*/
/**
 * @brief  Enables or disables the MMC Counter Freeze.
 * @param Cmd new state of the MMC Counter Freeze.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableMmcCounterFreeze(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the MMC Counter Freeze */
        ETH->MMCCTRL |= ETH_MMCCTRL_CNTFREEZ;
    }
    else
    {
        /* Disable the MMC Counter Freeze */
        ETH->MMCCTRL &= ~ETH_MMCCTRL_CNTFREEZ;
    }
}

/**
 * @brief  Enables or disables the MMC Reset On Read.
 * @param Cmd new state of the MMC Reset On Read.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableMmcResetOnRead(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the MMC Counter reset on read */
        ETH->MMCCTRL |= ETH_MMCCTRL_RSTONRD;
    }
    else
    {
        /* Disable the MMC Counter reset on read */
        ETH->MMCCTRL &= ~ETH_MMCCTRL_RSTONRD;
    }
}

/**
 * @brief  Enables or disables the MMC Counter Stop Rollover.
 * @param Cmd new state of the MMC Counter Stop Rollover.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableMmcCounterRollover(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Disable the MMC Counter Stop Rollover  */
        ETH->MMCCTRL &= ~ETH_MMCCTRL_CNTSTOPRO;
    }
    else
    {
        /* Enable the MMC Counter Stop Rollover */
        ETH->MMCCTRL |= ETH_MMCCTRL_CNTSTOPRO;
    }
}

/**
 * @brief  Resets the MMC Counters.
 */
void ETH_ResetMmcCounters(void)
{
    /* Resets the MMC Counters */
    ETH->MMCCTRL |= ETH_MMCCTRL_CNTRST;
}

/**
 * @brief  Enables or disables the specified ETHERNET MMC interrupts.
 * @param ETH_MMC_IT specifies the ETHERNET MMC interrupt sources to be enabled or disabled.
 *   This parameter can be any combination of Tx interrupt or
 *   any combination of Rx interrupt (but not both)of the following values:
 *     @arg ETH_MMC_INT_TXGFRMIS When Tx good frame counter reaches half the maximum value
 *     @arg ETH_MMC_INT_TXMCOLGFIS When Tx good multi col counter reaches half the maximum value
 *     @arg ETH_MMC_INT_TXSCOLGFIS When Tx good single col counter reaches half the maximum value
 *     @arg ETH_MMC_INT_RXUCGFIS When Rx good unicast frames counter reaches half the maximum value
 *     @arg ETH_MMC_INT_RXALGNERFIS When Rx alignment error counter reaches half the maximum value
 *     @arg ETH_MMC_INT_RXCRCERFIS When Rx crc error counter reaches half the maximum value
 * @param Cmd new state of the specified ETHERNET MMC interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_EnableMmcInt(uint32_t ETH_MMC_IT, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_ETH_MMC_INT(ETH_MMC_IT));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if ((ETH_MMC_IT & (uint32_t)0x10000000) != (uint32_t)RESET)
    {
        /* Remove egister mak from IT */
        ETH_MMC_IT &= 0xEFFFFFFF;

        /* ETHERNET MMC Rx interrupts selected */
        if (Cmd != DISABLE)
        {
            /* Enable the selected ETHERNET MMC interrupts */
            ETH->MMCRXINTMSK &= (~(uint32_t)ETH_MMC_IT);
        }
        else
        {
            /* Disable the selected ETHERNET MMC interrupts */
            ETH->MMCRXINTMSK |= ETH_MMC_IT;
        }
    }
    else
    {
        /* ETHERNET MMC Tx interrupts selected */
        if (Cmd != DISABLE)
        {
            /* Enable the selected ETHERNET MMC interrupts */
            ETH->MMCTXINTMSK &= (~(uint32_t)ETH_MMC_IT);
        }
        else
        {
            /* Disable the selected ETHERNET MMC interrupts */
            ETH->MMCTXINTMSK |= ETH_MMC_IT;
        }
    }
}

/**
 * @brief  Checks whether the specified ETHERNET MMC IT is set or not.
 * @param ETH_MMC_IT specifies the ETHERNET MMC interrupt.
 *   This parameter can be one of the following values:
 *     @arg ETH_MMC_IT_TxFCGC When Tx good frame counter reaches half the maximum value
 *     @arg ETH_MMC_IT_TxMCGC When Tx good multi col counter reaches half the maximum value
 *     @arg ETH_MMC_IT_TxSCGC When Tx good single col counter reaches half the maximum value
 *     @arg ETH_MMC_IT_RxUGFC When Rx good unicast frames counter reaches half the maximum value
 *     @arg ETH_MMC_IT_RxAEC When Rx alignment error counter reaches half the maximum value
 *     @arg ETH_MMC_IT_RxCEC When Rx crc error counter reaches half the maximum value
 * @return The value of ETHERNET MMC IT (SET or RESET).
 */
INTStatus ETH_GetMmcIntStatus(uint32_t ETH_MMC_IT)
{
    INTStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ETH_MMC_GET_INT(ETH_MMC_IT));

    if ((ETH_MMC_IT & (uint32_t)0x10000000) != (uint32_t)RESET)
    {
        /* ETHERNET MMC Rx interrupts selected */
        /* Check if the ETHERNET MMC Rx selected interrupt is enabled and occured */
        if ((((ETH->MMCRXINT & ETH_MMC_IT) != (uint32_t)RESET)) && ((ETH->MMCRXINTMSK & ETH_MMC_IT) != (uint32_t)RESET))
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else
    {
        /* ETHERNET MMC Tx interrupts selected */
        /* Check if the ETHERNET MMC Tx selected interrupt is enabled and occured */
        if ((((ETH->MMCTXINT & ETH_MMC_IT) != (uint32_t)RESET)) && ((ETH->MMCRXINTMSK & ETH_MMC_IT) != (uint32_t)RESET))
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }

    return bitstatus;
}

/**
 * @brief  Get the specified ETHERNET MMC register value.
 * @param ETH_MMCReg specifies the ETHERNET MMC register.
 *   This parameter can be one of the following values:
 *     @arg ETH_MMCCTRL MMC CTRL register
 *     @arg ETH_MMCRXINT MMC RIR register
 *     @arg ETH_MMCTXINT MMC TIR register
 *     @arg ETH_MMCRXINTMSK MMC RIMR register
 *     @arg ETH_MMCTXINTMSK MMC TIMR register
 *     @arg ETH_MMCTXGFASCCNT MMC TGFSCCR register
 *     @arg ETH_MMCTXGFAMSCCNT MMC TGFMSCCR register
 *     @arg ETH_MMCTXGFCNT MMC TGFCR register
 *     @arg ETH_MMCRXFCECNT MMC RFCECR register
 *     @arg ETH_MMCRXFAECNT MMC RFAECR register
 *     @arg ETH_MMCRXGUFCNT MMC RGUFCRregister
 * @return The value of ETHERNET MMC Register value.
 */
uint32_t ETH_GetMmcRegisterValue(uint32_t ETH_MMCReg)
{
    /* Check the parameters */
    assert_param(IS_ETH_MMC_REGISTER(ETH_MMCReg));

    /* Return the selected register value */
    return (*(__IO uint32_t*)(ETH_MAC_BASE + ETH_MMCReg));
}
/*---------------------------------  PTP  ------------------------------------*/

/**
 * @brief  Updated the PTP block for fine correction with the Time Stamp Addend register value.
 */
void ETH_UpdatePtpTimeStampAddend(void)
{
    /* Enable the PTP block update with the Time Stamp Addend register value */
    ETH->PTPTSCTRL |= ETH_PTPTSCTRL_TSADDREG;
}

/**
 * @brief  Enable the PTP Time Stamp interrupt trigger
 */
void ETH_EnablePtpTimeStampIntTrigger(void)
{
    /* Enable the PTP target time interrupt */
    ETH->PTPTSCTRL |= ETH_PTPTSCTRL_TSTRIG;
}

/**
 * @brief  Updated the PTP system time with the Time Stamp Update register value.
 */
void ETH_UpdatePtpTimeStamp(void)
{
    /* Enable the PTP system time update with the Time Stamp Update register value */
    ETH->PTPTSCTRL |= ETH_PTPTSCTRL_TSUPDT;
}

/**
 * @brief  Initialize the PTP Time Stamp
 */
void ETH_InitPtpTimeStamp(void)
{
    /* Initialize the PTP Time Stamp */
    ETH->PTPTSCTRL |= ETH_PTPTSCTRL_TSINIT;
}

/**
 * @brief  Selects the PTP Update method
 * @param UpdateMethod the PTP Update method
 *   This parameter can be one of the following values:
 *     @arg ETH_PTP_FINE_UPDATE Fine Update method
 *     @arg ETH_PTP_COARSE_UPDATE Coarse Update method
 */
void ETH_ConfigPtpUpdateMethod(uint32_t UpdateMethod)
{
    /* Check the parameters */
    assert_param(IS_ETH_PTP_UPDATE(UpdateMethod));

    if (UpdateMethod != ETH_PTP_COARSE_UPDATE)
    {
        /* Enable the PTP Fine Update method */
        ETH->PTPTSCTRL |= ETH_PTPTSCTRL_TSCFUPDT;
    }
    else
    {
        /* Disable the PTP Coarse Update method */
        ETH->PTPTSCTRL &= (~(uint32_t)ETH_PTPTSCTRL_TSCFUPDT);
    }
}

/**
 * @brief  Enables or disables the PTP time stamp for transmit and receive frames.
 * @param Cmd new state of the PTP time stamp for transmit and receive frames
 *   This parameter can be: ENABLE or DISABLE.
 */
void ETH_StartPTPTimeStamp(FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the PTP time stamp for transmit and receive frames */
        ETH->PTPTSCTRL |= ETH_PTPTSCTRL_TSENA;
    }
    else
    {
        /* Disable the PTP time stamp for transmit and receive frames */
        ETH->PTPTSCTRL &= (~(uint32_t)ETH_PTPTSCTRL_TSENA);
    }
}

/**
 * @brief  Checks whether the specified ETHERNET PTP flag is set or not.
 * @param ETH_PTP_FLAG specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg ETH_PTP_FLAG_TSADDREG Addend Register Update
 *     @arg ETH_PTP_FLAG_TSTRIG Time Stamp Interrupt Trigger Enable
 *     @arg ETH_PTP_FLAG_TSUPDT Time Stamp Update
 *     @arg ETH_PTP_FLAG_TSINIT Time Stamp Initialize
 * @return The new state of ETHERNET PTP Flag (SET or RESET).
 */
FlagStatus ETH_GetPtpFlagStatus(uint32_t ETH_PTP_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ETH_PTP_GET_FLAG(ETH_PTP_FLAG));

    if ((ETH->PTPTSCTRL & ETH_PTP_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
 * @brief  Sets the system time Sub-Second Increment value.
 * @param SubSecondValue specifies the PTP Sub-Second Increment Register value.
 */
void ETH_SetPtpSubSecondInc(uint32_t SubSecondValue)
{
    /* Check the parameters */
    assert_param(IS_ETH_PTP_SUBSECOND_INCREMENT(SubSecondValue));
    /* Set the PTP Sub-Second Increment Register */
    ETH->PTPSSINC = SubSecondValue;
}

/**
 * @brief  Sets the Time Stamp update sign and values.
 * @param Sign specifies the PTP Time update value sign.
 *   This parameter can be one of the following values:
 *     @arg ETH_PTP_POSITIVE_TIME positive time value.
 *     @arg ETH_PTP_NEGATIVE_TIME negative time value.
 * @param SecondValue specifies the PTP Time update second value.
 * @param SubSecondValue specifies the PTP Time update sub-second value.
 *   This parameter is a 31 bit value, bit32 correspond to the sign.
 */
void ETH_SetPtpTimeStampUpdate(uint32_t Sign, uint32_t SecondValue, uint32_t SubSecondValue)
{
    /* Check the parameters */
    assert_param(IS_ETH_PTP_TIME_SIGN(Sign));
    assert_param(IS_ETH_PTP_TIME_STAMP_UPDATE_SUBSECOND(SubSecondValue));
    /* Set the PTP Time Update High Register */
    ETH->PTPSECUP = SecondValue;

    /* Set the PTP Time Update Low Register with sign */
    ETH->PTPNSUP = Sign | SubSecondValue;
}

/**
 * @brief  Sets the Time Stamp Addend value.
 * @param Value specifies the PTP Time Stamp Addend Register value.
 */
void ETH_SetPtpTimeStampAddend(uint32_t Value)
{
    /* Set the PTP Time Stamp Addend Register */
    ETH->PTPTSADD = Value;
}

/**
 * @brief  Sets the Target Time registers values.
 * @param HighValue specifies the PTP Target Time High Register value.
 * @param LowValue specifies the PTP Target Time Low Register value.
 */
void ETH_SetPtpTargetTime(uint32_t HighValue, uint32_t LowValue)
{
    /* Set the PTP Target Time High Register */
    ETH->PTPTTSEC = HighValue;
    /* Set the PTP Target Time Low Register */
    ETH->PTPTTNS = LowValue;
}

/**
 * @brief  Get the specified ETHERNET PTP register value.
 * @param ETH_PTPReg specifies the ETHERNET PTP register.
 *   This parameter can be one of the following values:
 *     @arg ETH_PTPTSCTRL Sub-Second Increment Register
 *     @arg ETH_PTPSSINC Sub-Second Increment Register
 *     @arg ETH_PTPSEC Time Stamp High Register
 *     @arg ETH_PTPNS Time Stamp Low Register
 *     @arg ETH_PTPSECUP Time Stamp High Update Register
 *     @arg ETH_PTPNSUP Time Stamp Low Update Register
 *     @arg ETH_PTPTSADD Time Stamp Addend Register
 *     @arg ETH_PTPTTSEC Target Time High Register
 *     @arg ETH_PTPTTNS Target Time Low Register
 * @return The value of ETHERNET PTP Register value.
 */
uint32_t ETH_GetPtpRegisterValue(uint32_t ETH_PTPReg)
{
    /* Check the parameters */
    assert_param(IS_ETH_PTP_REGISTER(ETH_PTPReg));

    /* Return the selected register value */
    return (*(__IO uint32_t*)(ETH_MAC_BASE + ETH_PTPReg));
}

/**
 * @brief  Initializes the DMA Tx descriptors in chain mode with PTP.
 * @param DMATxDescTab Pointer on the first Tx desc list
 * @param DMAPTPTxDescTab Pointer on the first PTP Tx desc list
 * @param TxBuff Pointer on the first TxBuffer list
 * @param TxBuffCount Number of the used Tx desc in the list
 */
void ETH_ConfigDmaPtpTxDescInChainMode(ETH_DMADescType* DMATxDescTab,
                                       ETH_DMADescType* DMAPTPTxDescTab,
                                       uint8_t* TxBuff,
                                       uint32_t TxBuffCount)
{
    uint32_t i = 0;
    ETH_DMADescType* DMATxDesc;

    /* Set the DMATxDescToSet pointer with the first one of the DMATxDescTab list */
    DMATxDescToSet    = DMATxDescTab;
    DMAPTPTxDescToSet = DMAPTPTxDescTab;
    /* Fill each DMATxDesc descriptor with the right values */
    for (i = 0; i < TxBuffCount; i++)
    {
        /* Get the pointer on the ith member of the Tx Desc list */
        DMATxDesc = DMATxDescTab + i;
        /* Set Second Address Chained bit and enable PTP */
        DMATxDesc->Status        = 0;
        DMATxDesc->CtrlOrBufSize = ETH_DMA_TX_DESC_TCH | ETH_DMA_TX_DESC_TTSE;

        /* Set Buffer1 address pointer */
        DMATxDesc->Buf1Addr = (uint32_t)(&TxBuff[i * ETH_MAX_PACKET_SIZE]);

        /* Initialize the next descriptor with the Next Desciptor Polling Enable */
        if (i < (TxBuffCount - 1))
        {
            /* Set next descriptor address register with next descriptor base address */
            DMATxDesc->Buf2OrNextDescAddr = (uint32_t)(DMATxDescTab + i + 1);
        }
        else
        {
            /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
            DMATxDesc->Buf2OrNextDescAddr = (uint32_t)DMATxDescTab;
        }
        /* make DMAPTPTxDescTab points to the same addresses as DMATxDescTab */
        (&DMAPTPTxDescTab[i])->Buf1Addr           = DMATxDesc->Buf1Addr;
        (&DMAPTPTxDescTab[i])->Buf2OrNextDescAddr = DMATxDesc->Buf2OrNextDescAddr;
    }
    /* Store on the last DMAPTPTxDescTab desc status record the first list address */
    (&DMAPTPTxDescTab[i - 1])->Status = (uint32_t)DMAPTPTxDescTab;

    /* Set Transmit Desciptor List Address Register */
    ETH->DMATXDLADDR = (uint32_t)DMATxDescTab;
}

/**
 * @brief  Initializes the DMA Rx descriptors in chain mode.
 * @param DMARxDescTab Pointer on the first Rx desc list
 * @param DMAPTPRxDescTab Pointer on the first PTP Rx desc list
 * @param RxBuff Pointer on the first RxBuffer list
 * @param RxBuffCount Number of the used Rx desc in the list
 */
void ETH_ConfigDmaPtpRxDescInChainMode(ETH_DMADescType* DMARxDescTab,
                                       ETH_DMADescType* DMAPTPRxDescTab,
                                       uint8_t* RxBuff,
                                       uint32_t RxBuffCount)
{
    uint32_t i = 0;
    ETH_DMADescType* DMARxDesc;

    /* Set the DMARxDescToGet pointer with the first one of the DMARxDescTab list */
    DMARxDescToGet    = DMARxDescTab;
    DMAPTPRxDescToGet = DMAPTPRxDescTab;
    /* Fill each DMARxDesc descriptor with the right values */
    for (i = 0; i < RxBuffCount; i++)
    {
        /* Get the pointer on the ith member of the Rx Desc list */
        DMARxDesc = DMARxDescTab + i;
        /* Set Own bit of the Rx descriptor Status */
        DMARxDesc->Status = ETH_DMA_RX_DESC_OWN;

        /* Set Buffer1 size and Second Address Chained bit */
        DMARxDesc->CtrlOrBufSize = ETH_DMA_RX_DESC_RCH | (uint32_t)ETH_MAX_PACKET_SIZE;
        /* Set Buffer1 address pointer */
        DMARxDesc->Buf1Addr = (uint32_t)(&RxBuff[i * ETH_MAX_PACKET_SIZE]);

        /* Initialize the next descriptor with the Next Desciptor Polling Enable */
        if (i < (RxBuffCount - 1))
        {
            /* Set next descriptor address register with next descriptor base address */
            DMARxDesc->Buf2OrNextDescAddr = (uint32_t)(DMARxDescTab + i + 1);
        }
        else
        {
            /* For last descriptor, set next descriptor address register equal to the first descriptor base address */
            DMARxDesc->Buf2OrNextDescAddr = (uint32_t)(DMARxDescTab);
        }
        /* Make DMAPTPRxDescTab points to the same addresses as DMARxDescTab */
        (&DMAPTPRxDescTab[i])->Buf1Addr           = DMARxDesc->Buf1Addr;
        (&DMAPTPRxDescTab[i])->Buf2OrNextDescAddr = DMARxDesc->Buf2OrNextDescAddr;
    }
    /* Store on the last DMAPTPRxDescTab desc status record the first list address */
    (&DMAPTPRxDescTab[i - 1])->Status = (uint32_t)DMAPTPRxDescTab;

    /* Set Receive Desciptor List Address Register */
    ETH->DMARXDLADDR = (uint32_t)DMARxDescTab;
}

/**
 * @brief  Transmits a packet, from application buffer, pointed by ppkt with Time Stamp values.
 * @param ppkt pointer to application packet buffer to transmit.
 * @param FrameLength Tx Packet size.
 * @param PTPTxTab Pointer on the first PTP Tx table to store Time stamp values.
 * @return ETH_ERROR: in case of Tx desc owned by DMA
 *         ETH_SUCCESS: for correct transmission
 */
uint32_t ETH_TxPtpPacket(uint8_t* ppkt, uint16_t FrameLength, uint32_t* PTPTxTab)
{
    uint32_t offset = 0, timeout = 0;
    /* Check if the descriptor is owned by the ETHERNET DMA (when set) or CPU (when reset) */
    if ((DMATxDescToSet->Status & ETH_DMA_TX_DESC_OWN) != (uint32_t)RESET)
    {
        /* Return ERROR: OWN bit set */
        return ETH_ERROR;
    }
    /* Copy the frame to be sent into memory pointed by the current ETHERNET DMA Tx descriptor */
    for (offset = 0; offset < FrameLength; offset++)
    {
        (*(__IO uint8_t*)((DMAPTPTxDescToSet->Buf1Addr) + offset)) = (*(ppkt + offset));
    }
    /* Setting the Frame Length: bits[10:0] */
    DMATxDescToSet->CtrlOrBufSize &= (~ETH_DMA_TX_DESC_TBS1);
    DMATxDescToSet->CtrlOrBufSize |= (FrameLength & ETH_DMA_TX_DESC_TBS1);
    /* Setting the last segment and first segment bits (in this case a frame is transmitted in one descriptor) */
    DMATxDescToSet->CtrlOrBufSize |= ETH_DMA_TX_DESC_LS | ETH_DMA_TX_DESC_FS;
    /* Set Own bit of the Tx descriptor Status: gives the buffer back to ETHERNET DMA */
    DMATxDescToSet->Status |= ETH_DMA_TX_DESC_OWN;
    /* When Tx Buffer unavailable flag is set: clear it and resume transmission */
    if ((ETH->DMASTS & ETH_DMASTS_TU) != (uint32_t)RESET)
    {
        /* Clear TBUS ETHERNET DMA flag */
        ETH->DMASTS = ETH_DMASTS_TU;
        /* Resume DMA transmission*/
        ETH->DMATXPD = 0;
    }
    /* Wait for ETH_DMA_TX_DESC_TTSS flag to be set */
    do
    {
        timeout++;
    } while (!(DMATxDescToSet->Status & ETH_DMA_TX_DESC_TTSS) && (timeout < 0xFFFF));
    /* Return ERROR in case of timeout */
    if (timeout == PHY_READ_TO)
    {
        return ETH_ERROR;
    }
    /* Clear the DMATxDescToSet status register TTSS flag */
    DMATxDescToSet->Status &= ~ETH_DMA_TX_DESC_TTSS;
    *PTPTxTab++ = DMATxDescToSet->Buf1Addr;
    *PTPTxTab   = DMATxDescToSet->Buf2OrNextDescAddr;
    /* Update the ENET DMA current descriptor */
    /* Chained Mode */
    if ((DMATxDescToSet->CtrlOrBufSize & ETH_DMA_TX_DESC_TCH) != (uint32_t)RESET)
    {
        /* Selects the next DMA Tx descriptor list for next buffer read */
        DMATxDescToSet = (ETH_DMADescType*)(DMAPTPTxDescToSet->Buf2OrNextDescAddr);
        if (DMAPTPTxDescToSet->Status != 0)
        {
            DMAPTPTxDescToSet = (ETH_DMADescType*)(DMAPTPTxDescToSet->Status);
        }
        else
        {
            DMAPTPTxDescToSet++;
        }
    }
    else /* Ring Mode */
    {
        if ((DMATxDescToSet->CtrlOrBufSize & ETH_DMA_TX_DESC_TER) != (uint32_t)RESET)
        {
            /* Selects the next DMA Tx descriptor list for next buffer read: this will
            be the first Tx descriptor in this case */
            DMATxDescToSet    = (ETH_DMADescType*)(ETH->DMATXDLADDR);
            DMAPTPTxDescToSet = (ETH_DMADescType*)(ETH->DMATXDLADDR);
        }
        else
        {
            /* Selects the next DMA Tx descriptor list for next buffer read */
            DMATxDescToSet =
                (ETH_DMADescType*)((uint32_t)DMATxDescToSet + 0x10 + ((ETH->DMABUSMOD & ETH_DMABUSMOD_DSL)));
            DMAPTPTxDescToSet =
                (ETH_DMADescType*)((uint32_t)DMAPTPTxDescToSet + 0x10 + ((ETH->DMABUSMOD & ETH_DMABUSMOD_DSL)));
        }
    }
    /* Return SUCCESS */
    return ETH_SUCCESS;
}

/**
 * @brief  Receives a packet and copies it to memory pointed by ppkt with Time Stamp values.
 * @param ppkt pointer to application packet receive buffer.
 * @param PTPRxTab Pointer on the first PTP Rx table to store Time stamp values.
 * @return ETH_ERROR: if there is error in reception
 *         framelength: received packet size if packet reception is correct
 */
uint32_t ETH_RxPtpPacket(uint8_t* ppkt, uint32_t* PTPRxTab)
{
    uint32_t offset = 0, framelength = 0;
    /* Check if the descriptor is owned by the ENET or CPU */
    if ((DMARxDescToGet->Status & ETH_DMA_RX_DESC_OWN) != (uint32_t)RESET)
    {
        /* Return error: OWN bit set */
        return ETH_ERROR;
    }
    if (((DMARxDescToGet->Status & ETH_DMA_RX_DESC_ES) == (uint32_t)RESET)
        && ((DMARxDescToGet->Status & ETH_DMA_RX_DESC_LS) != (uint32_t)RESET)
        && ((DMARxDescToGet->Status & ETH_DMA_RX_DESC_FS) != (uint32_t)RESET))
    {
        /* Get the Frame Length of the received packet: substruct 4 bytes of the CRC */
        framelength = ((DMARxDescToGet->Status & ETH_DMA_RX_DESC_FL) >> ETH_DMA_RX_DESC_FRAME_LEN_SHIFT) - 4;
        /* Copy the received frame into buffer from memory pointed by the current ETHERNET DMA Rx descriptor */
        for (offset = 0; offset < framelength; offset++)
        {
            (*(ppkt + offset)) = (*(__IO uint8_t*)((DMAPTPRxDescToGet->Buf1Addr) + offset));
        }
    }
    else
    {
        /* Return ERROR */
        framelength = ETH_ERROR;
    }
    /* When Rx Buffer unavailable flag is set: clear it and resume reception */
    if ((ETH->DMASTS & ETH_DMASTS_RU) != (uint32_t)RESET)
    {
        /* Clear RBUS ETHERNET DMA flag */
        ETH->DMASTS = ETH_DMASTS_RU;
        /* Resume DMA reception */
        ETH->DMARXPD = 0;
    }
    *PTPRxTab++ = DMARxDescToGet->Buf1Addr;
    *PTPRxTab   = DMARxDescToGet->Buf2OrNextDescAddr;
    /* Set Own bit of the Rx descriptor Status: gives the buffer back to ETHERNET DMA */
    DMARxDescToGet->Status |= ETH_DMA_RX_DESC_OWN;
    /* Update the ETHERNET DMA global Rx descriptor with next Rx decriptor */
    /* Chained Mode */
    if ((DMARxDescToGet->CtrlOrBufSize & ETH_DMA_RX_DESC_RCH) != (uint32_t)RESET)
    {
        /* Selects the next DMA Rx descriptor list for next buffer read */
        DMARxDescToGet = (ETH_DMADescType*)(DMAPTPRxDescToGet->Buf2OrNextDescAddr);
        if (DMAPTPRxDescToGet->Status != 0)
        {
            DMAPTPRxDescToGet = (ETH_DMADescType*)(DMAPTPRxDescToGet->Status);
        }
        else
        {
            DMAPTPRxDescToGet++;
        }
    }
    else /* Ring Mode */
    {
        if ((DMARxDescToGet->CtrlOrBufSize & ETH_DMA_RX_DESC_RER) != (uint32_t)RESET)
        {
            /* Selects the first DMA Rx descriptor for next buffer to read: last Rx descriptor was used */
            DMARxDescToGet = (ETH_DMADescType*)(ETH->DMARXDLADDR);
        }
        else
        {
            /* Selects the next DMA Rx descriptor list for next buffer to read */
            DMARxDescToGet =
                (ETH_DMADescType*)((uint32_t)DMARxDescToGet + 0x10 + ((ETH->DMABUSMOD & ETH_DMABUSMOD_DSL)));
        }
    }
    /* Return Frame Length/ERROR */
    return (framelength);
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
