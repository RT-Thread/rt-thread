/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file n32h76x_78x_eth.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */
#include "n32h76x_78x_eth.h"

/** ETH Private Defines **/

/* ETH Register MASK macro definition */
#define ETH1_MACCFG_MASK                        ((uint32_t)0xFFFFFF7CU)
#define ETH2_MACCFG_MASK                        ((uint32_t)0xFFFB7F7CU)
#define ETH_MACEXTCFG_MASK                      ((uint32_t)0x7F073FFFU)
#define ETH_MACPFLT_MASK                        ((uint32_t)0x803107FFU)
#define ETH_MACWDGTO_MASK                       ((uint32_t)0x0000010FU)
#define ETH_MACTXFLWCTRL_MASK                   ((uint32_t)0xFFFF00F2U)
#define ETH_MACRXFLWCTRL_MASK                   ((uint32_t)0x00000003U)
#define ETH_MTLTXQOPMOD_MASK                    ((uint32_t)0x00000072U)
#define ETH_MTLRXQOPMOD_MASK                    ((uint32_t)0x0000007BU)
#define ETH_DMAMODE_MASK                        ((uint32_t)0x00087802U)
#define ETH_DMASBMODE_MASK                      ((uint32_t)0x0000D001U)
#define ETH_DMACH0CTRL_MASK                     ((uint32_t)0x001D3FFFU)
#define ETH_DMACH0TXCTRL_MASK                   ((uint32_t)0x007F1010U)
#define ETH_DMACH0RXCTRL_MASK                   ((uint32_t)0x807F0000U)
#define ETH_MACVLANTAG_MASK                     ((uint32_t)0x037FFFFFU)

#define ETH_RXBUFFERSIZE_MASK                   ((uint32_t)0x00007FFEU)

/* ETH MAC CSR Clock Frequency macro definition */
#define ETH_MACCSR_CLOCK_FREQ_20M               ((uint32_t)20000000U)
#define ETH_MACCSR_CLOCK_FREQ_35M               ((uint32_t)35000000U)
#define ETH_MACCSR_CLOCK_FREQ_60M               ((uint32_t)60000000U)
#define ETH_MACCSR_CLOCK_FREQ_100M              ((uint32_t)100000000U)
#define ETH_MACCSR_CLOCK_FREQ_150M              ((uint32_t)150000000U)
#define ETH_MACCSR_CLOCK_FREQ_250M              ((uint32_t)250000000U)
#define ETH_MACCSR_CLOCK_FREQ_300M              ((uint32_t)300000000U)
#define ETH_MACCSR_CLOCK_FREQ_500M              ((uint32_t)500000000U)
#define ETH_MACCSR_CLOCK_FREQ_800M              ((uint32_t)800000000U)


/* ETH Timeout values macro definition */
#define ETH_SWRESET_TIMEOUT                     ((uint32_t)0xF0000000U)
#define ETH_MDIO_BUS_TIMEOUT                    ((uint32_t)0xF0000000U)
#define ETH_PHY_LINKED_TIMEOUT                  ((uint32_t)0xF0000000U)
#define ETH_PHY_AUTONEGO_COMPLETED_TIMEOUT      ((uint32_t)0xF0000000U)

/* ETH Remote Wake-up Filter register length definition */
#define ETH_WAKEUP_REGISTER_LEN                 ((uint32_t)8U)

/* ETH Delay between consecutive write registers */
#define ETH_WRITE_REG_DELAY                     ((uint32_t)5000U)

/* ETH External PHY Configuration Delay */
#define ETH_PHY_CONFIG_DELAY                    ((uint32_t)5000U)

/* ETH tx descriptor index increment */
#define __ETH_TXDESC_INDEX_INCR(Index, Offset)  do {                                                  \
                                                    (Index) += (Offset);                              \
                                                        if ((Index) >= ETH_TX_DESC_NUMBER)            \
                                                        {                                             \
                                                            (Index) = ((Index) - ETH_TX_DESC_NUMBER); \
                                                        }                                             \
                                                } while (0)
/* ETH rx descriptor index increment */
#define __ETH_RXDESC_INDEX_INCR(Index, Offset)  do {                                                  \
                                                    (Index) += (Offset);                              \
                                                        if ((Index) >= ETH_RX_DESC_NUMBER)            \
                                                        {                                             \
                                                            (Index) = ((Index) - ETH_RX_DESC_NUMBER); \
                                                        }                                             \
                                                } while (0)

/* ETH Tick&Delay through the DWT module */
#define __ETH_TICK_START()                      CPU_DELAY_INTI()
#define __ETH_GET_TICK                          DWT_CYCCNT
#define __ETH_TICK_STOP()                       CPU_DELAY_DISABLE()
#define __ETH_DELAY(Cnt)                        do{                                                   \
                                                    /* Check that DWT is enabled or not */            \
                                                    if ((DEM_CR & DEM_CR_TRCENA) == (uint32_t)RESET)  \
                                                    {                                                 \
                                                        /* Enable and initialize DWT */               \
                                                        __ETH_TICK_START();                           \
                                                    }                                                 \
                                                    Cnt += __ETH_GET_TICK;                            \
                                                    while (__ETH_GET_TICK < Cnt){};                   \
                                                    __ETH_TICK_STOP();                                \
                                                } while (0)

/* ETH MAC μs tick */
#define ETH_MAC_US_TICK                         ((uint32_t)1000000U)


/** ETH Driving Functions Declaration **/

/**
*\*\name    ETH_DeInit.
*\*\fun     DeInitializes the ETH peripheral.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
**/
void ETH_DeInit(ETH_Module* ETHx)
{
    /* Check the ETHx parameter */
    if (ETHx == ETH1)
    {
        /* ETH1 peripheral reset */
        RCC_EnableAHB2PeriphReset1(RCC_AHB2_PERIPHRST_ETH1);
    }
    else if (ETHx == ETH2)
    {
        /* ETH2 peripheral reset */
        RCC_EnableAHB1PeriphReset2(RCC_AHB1_PERIPHRST_ETH2);
    }
    else
    {
        /* Do nothing */
    }
}

/**
*\*\name    ETH_StructInit.
*\*\fun     Initializes the structure parameter of type ETH_InitType used to
*\*\        initialize ETH. This function is usually called before initializing
*\*\        a parameter of type ETH_InitType.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   ETH_InitParam :
*\*\          - Pointer to the ETH_InitType structure which will be initialized.
*\*\return  none
**/
void ETH_StructInit(ETH_Module* ETHx, ETH_InitType* ETH_InitParam)
{
    /** Set the default configuration **/

    /* Default 7-byte preamble length */
    ETH_InitParam->TxPreambleLen             = ETH_PREAMBLE_LEN_7BYTES;
    /* Default Disable deferral check function in the half-duplex mode */
    ETH_InitParam->DeferralCheck             = DISABLE;
    /* Default Back-off time_limit = 10 slot times in the half-duplex mode */
    ETH_InitParam->BackOffLimit              = ETH_BACK_OFF_LIMIT_10;
    /* Default Enable MAC retry transmission in the half-duplex mode */
    ETH_InitParam->DisTxRetry                = DISABLE;
    /* Default Enable Carrier Sense During Transmission in the half-duplex mode */
    ETH_InitParam->DisCSDuringTransmit       = DISABLE;
    /* Default Enable Receive Own in the half-duplex mode */
    ETH_InitParam->DisRxOwn                  = DISABLE;
    /* Default Disable Carrier Sense Before Transmission in the full-duplex mode */
    ETH_InitParam->CSBeforeTransmit          = DISABLE;
    /* Default Disable Loopback Mode */
    ETH_InitParam->Loopback                  = DISABLE;
    /* Default Half-duplex mode */
    ETH_InitParam->Duplex                    = ETH_HALF_DUPLEX_MODE;
    /* Set the default speed for ETH1/ETH2 */
    if (ETHx == ETH1)
    {
        /* Default Selects the speed mode: 1000Mbps */
        ETH_InitParam->SpeedSelect           = ETH_SPEED_1000M;
    }
    else
    {
        /* Default Selects the speed mode: 10Mbps */
        ETH_InitParam->SpeedSelect           = ETH_SPEED_10M;
    }
    /* Default Disable Jumbo Packet */
    ETH_InitParam->JumboPacket               = DISABLE;
    /* Default Enable Jabber timer on Tx path */
    ETH_InitParam->DisTxJabber               = DISABLE;
    /* Default Disable Packet Burst, Only ETH1 supports */
    ETH_InitParam->PacketBurst               = DISABLE;
    /* Default Enable Watchdog timer on Rx path */
    ETH_InitParam->DisRxWatchdog             = DISABLE;
    /* Default Disable Automatic Pad or CRC Stripping function */
    ETH_InitParam->AutoPadCRCStrip           = DISABLE;
    /* Default Disable CRC stripping for Type packets function */
    ETH_InitParam->CRCStripTypePacket        = DISABLE;
    /* Default Disable IEEE 802.3as Support for 2K Packets function */
    ETH_InitParam->Support2KPacket           = DISABLE;
    /* Default Disable Giant Packet Size Limit Control */
    ETH_InitParam->GiantPacketSizeLimitCtrl  = DISABLE;
    /* Default 96-bit Inter-Packet Gap */
    ETH_InitParam->InterPacketGapVal         = ETH_INTER_PACKET_GAP_96BIT;
    /* Default Disable Checksum Offload function */
    ETH_InitParam->ChecksumOffload           = DISABLE;
    /* Default Internal Signal Control Source Address Field */
    ETH_InitParam->SrcAddrCtrl               = ETH_SRC_ADDR_CTRL_INTERNAL_SIGNALS;
    /* Default Disable ARP Offload function */
    ETH_InitParam->ARPOffload                = DISABLE;

    /* Default Set Giant Packet Size Limit value: 0 */
    ETH_InitParam->GiantPacketSizeLimit      = 0U;
    /* Default Enable CRC Checking for Rx Packets */
    ETH_InitParam->DisRxPacketCRCCheck       = DISABLE;
    /* Default Disable Slow Protocol Detection */
    ETH_InitParam->SPDetect                  = DISABLE;
    /* Default Disable Unicast Slow Protocol Packet Detect */
    ETH_InitParam->USPPacketDetect           = DISABLE;
    /* Default Disable Extended Inter-Packet Gap */
    ETH_InitParam->ExtInterPacketGap         = DISABLE;
    /* Default Set the minimum Inter-Packet Gap value: 0 */
    ETH_InitParam->ExtInterPacketGapVal      = 0U;
    /* Default Disable ARP Packet Drop */
    ETH_InitParam->DropARPPacket             = DISABLE;

    /* Default Disable Promiscuous Mode */
    ETH_InitParam->Promiscuous               = DISABLE;
    /* Default Disable Hash Unicast Filtering Mode */
    ETH_InitParam->HashUnicast               = DISABLE;
    /* Default Disable Hash Multicast Filtering Mode */
    ETH_InitParam->HashMulticast             = DISABLE;
    /* Default Disable DA Inverse Filtering Mode */
    ETH_InitParam->DAInverseFiltering        = DISABLE;
    /* Default Disable Pass All Multicast Mode */
    ETH_InitParam->PassAllMulticast          = DISABLE;
    /* Default Enable Broadcast Packets */
    ETH_InitParam->DisBroadcastPackets       = DISABLE;
    /* Default Set the control packets: Filter out all */
    ETH_InitParam->PassControlPackets        = ETH_CTRL_PACKETS_FLTR_ALL;
    /* Default Disable SA Inverse Filtering Mode */
    ETH_InitParam->SAInverseFiltering        = DISABLE;
    /* Default Disable SA Filter */
    ETH_InitParam->SAFilter                  = DISABLE;
    /* Default Disable Hash or Perfect Filter */
    ETH_InitParam->HashOrPerfectFilter       = DISABLE;
    /* Default Disable VLAN Tag Filter */
    ETH_InitParam->VLANTagFilter             = DISABLE;
    /* Default Disable Layer 3 and Layer 4 Filter */
    ETH_InitParam->Layer3Layer4Filter        = DISABLE;
    /* Default Forward Non-TCP/UDP over IP Packets */
    ETH_InitParam->DropNonTcpUdpPackets      = DISABLE;
    /* Default Disable Receive All mode */
    ETH_InitParam->ReceiveAll                = DISABLE;

    /* Default Set Watchdog Timeout value: 2K bytes */
    ETH_InitParam->WatchdogTimeout           = ETH_WDG_TIMEOUT_2KBYTES;
    /* Default Disable Programmable Watchdog function */
    ETH_InitParam->ProgramWatchdog           = DISABLE;

    /* Default Disable Transmit Flow Control function */
    ETH_InitParam->TxFlowControl             = DISABLE;
    /* Default Set Pause Low Threshold value: Minus 4 time slots */
    ETH_InitParam->PauseLowThreshold         = ETH_PAUSE_LOW_THRESHOLD_PT4;
    /* Default Enable Zero-Quanta Pause function */
    ETH_InitParam->DisZeroQuantaPause        = DISABLE;
    /* Default Set Pause Time field value: 0 */
    ETH_InitParam->PauseTime                 = 0U;
    /* Default Disable Receive Flow Control function */
    ETH_InitParam->RxFlowControl             = DISABLE;
    /* Default Disable Unicast Pause Packet Detect */
    ETH_InitParam->UPPacketDetect            = DISABLE;

    /* Default Set TX Queue Operation Mode: Store and Forward Mode */
    ETH_InitParam->TxQueueOperateMode        = ETH_TXQUEUE_OPERATE_STOREFORWARD;
    /* Default Set RX Queue Operation Mode: Store and Forward Mode */
    ETH_InitParam->RxQueueOperateMode        = ETH_RXQUEUE_OPERATE_STOREFORWARD;
    /* Default Disable Forward Undersized Good Packets function */
    ETH_InitParam->ForwardUSGoodPacket       = DISABLE;
    /* Default Disable Forward Error Packets function */
    ETH_InitParam->ForwardErrorPacket        = DISABLE;
    /* Default Enable Dropping of TCP/IP Checksum Error Packets */
    ETH_InitParam->DisDropTCPIPCSErrorPacket = DISABLE;

    /* Default Set DMA Tx/Rx Arbitration Scheme: Rx:Tx = 1:1 */
    ETH_InitParam->TxRxArbitration           = ETH_DMA_ARBITRA_WRR_RX1_TX1;
    /* Default Disable Descriptor Cache function */
    ETH_InitParam->DescriptorCache           = DISABLE;
    /* Default Set AHB Master interface burst: Unspecified length (INCR) or SINGLE transfers */
    ETH_InitParam->BurstMode                 = ETH_BURST_MODE_UNFIXED;
    /* Default Disable AHB Master interface address-aligned burst transfers on Read and Write channels */
    ETH_InitParam->AddrAlignedBeats          = DISABLE;
    /* Default Disable AHB Master to rebuild the pending beats of any initiated burst transfer with INCRx and SINGLE transfers */
    ETH_InitParam->RebuildINCRxBurst         = DISABLE;
    /* Default Set the maximum segment size: 0 */
    ETH_InitParam->MaxSegmentSize            = 0U;
    /* Default Disable PBL multiplication by eigh mode */
    ETH_InitParam->PBLx8mode                 = DISABLE;
    /* Default Set the Word number to skip between two unchained descriptors: 0-bit */
    ETH_InitParam->DescriptorSkipLen         = ETH_DESC_SKIP_LEN_0BIT;
    /* Default Disable Operate on Second Packet mode */
    ETH_InitParam->OperateSecondPacket       = DISABLE;
    /* Default Disable TCP Segmentation function */
    ETH_InitParam->TCPSegment                = DISABLE;
    /* Default Set the maximum number of beats to be transferred in one DMA block data transfer: 1 */
    ETH_InitParam->TxBurstLength             = ETH_TX_PROGRAM_BURST_LEN_1;
    /* Default Disable Early Transmit Interrupt function */
    ETH_InitParam->EarlyTxInterruptCtrl      = DISABLE;
    /* Default Set the maximum number of beats to be transferred in one DMA block data transfer: 1 */
    ETH_InitParam->RxBurstLength             = ETH_RX_PROGRAM_BURST_LEN_1;
    /* Default Disable Early Receive Interrupt function */
    ETH_InitParam->EarlyRxInterruptCtrl      = DISABLE;
    /* Default Disable Rx Packet Flush function */
    ETH_InitParam->RxPacketFlush             = DISABLE;
}

/**
*\*\name    ETH_DMATxDescListInit.
*\*\fun     Initialize the ETH DMA transmit descriptor.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\return  none
**/
void ETH_DMATxDescListInit(ETH_Module* ETHx, ETH_InfoType* pInfo)
{
    uint32_t TempIndex;
    ETH_DMADescType* pTxDescriptor = NULL;

    /* Fill each DMATxDesc descriptor with the right values */
    for (TempIndex = 0U; TempIndex < ETH_TX_DESC_NUMBER; TempIndex++)
    {
        /* Get the descriptor address */
        pTxDescriptor = (pInfo->pTxDesc + TempIndex);

        pTxDescriptor->DESC0 = 0U;
        pTxDescriptor->DESC1 = 0U;
        pTxDescriptor->DESC2 = 0U;
        pTxDescriptor->DESC3 = 0U;
        /* Save Tx descritors adresses */
        pInfo->TxDescList.TxDesc[TempIndex] = (uint32_t)pTxDescriptor;
    }
    /* Set the current descriptor index to 0 */
    pInfo->TxDescList.CurTxDesc = 0U;

    /* Set Tx Descriptor Ring Length, The value written to the ETH_DMACH0TXDRLEN
    register must be the number of descriptors - 1 */
    WRITE_REG(ETHx->DMACH0TXDRLEN, (ETH_TX_DESC_NUMBER -1U));

    /* Set Tx Descriptor List Address */
    WRITE_REG(ETHx->DMACH0TXDLA, (uint32_t)pInfo->pTxDesc);

    /* Set Tx Descriptor Tail pointer */
    WRITE_REG(ETHx->DMACH0TXDTP, (uint32_t)pInfo->pTxDesc);
}

/**
*\*\name    ETH_DMARxDescListInit.
*\*\fun     Initialize the ETH DMA Receive descriptor.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\return  none
**/
void ETH_DMARxDescListInit(ETH_Module* ETHx, ETH_InfoType* pInfo)
{
    uint32_t TempIndex;
    ETH_DMADescType* pRxDescriptor = NULL;

    /* Fill each DMATxDesc descriptor with the right values */
    for (TempIndex = 0U; TempIndex < ETH_RX_DESC_NUMBER; TempIndex++)
    {
        /* Get the descriptor address */
        pRxDescriptor = (pInfo->pRxDesc + TempIndex);
    
        pRxDescriptor->DESC0 = 0U;
        pRxDescriptor->DESC1 = 0U;
        pRxDescriptor->DESC2 = 0U;
        pRxDescriptor->DESC3 = 0U;
        pRxDescriptor->Buf1Addr = 0U;
        pRxDescriptor->Buf2Addr = 0U;
        /* Save Rx descritors adresses */
        pInfo->RxDescList.RxDesc[TempIndex] = (uint32_t)pRxDescriptor;
    }
    /* Set the current descriptor index to 0 */
    pInfo->RxDescList.CurRxDesc = 0U;
    /* Set the first descriptor to 0 */
    pInfo->RxDescList.FirstAppDesc = 0U;
    /* Set the number of descriptors for the last packet to 0 */
    pInfo->RxDescList.AppDescNbr = 0U;
    /* Set to not generate a receive completion interrupt */
    pInfo->RxDescList.ItMode = 0U;
    /* Set to a non-context descriptor */
    pInfo->RxDescList.AppContextDesc = 0U;

    /* Set Rx Descriptor Ring Length, The value written to the ETH_DMACH0RXCTRL2
    register must be the number of descriptors - 1 */
    WRITE_REG(ETHx->DMACH0RXCTRL2, (ETH_RX_DESC_NUMBER - 1U));

    /* Set Rx Descriptor List Address */
    WRITE_REG(ETHx->DMACH0RXDLA, (uint32_t)pInfo->pRxDesc);

    /* Set Rx Descriptor Tail pointer */
    WRITE_REG(ETHx->DMACH0RXDTP, (uint32_t)(pInfo->pRxDesc + ((ETH_RX_DESC_NUMBER - 1U) * sizeof(ETH_DMADescType))));
}

/**
*\*\name    ETH_ConfigMDCNormalClock.
*\*\fun     Configure the normal clock frequency (1.0MHz ≤ MDC clock ≤ 2.5MHz) of the
*\*\        MDC based on the CSR clock frequency(HclkFreq),
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   pClk: 
*\*\          - pointer to a RCC_ClocksTypeDef structure which will hold the clocks frequencies. 
*\*\return  none
**/
void ETH_ConfigMDCNormalClock(ETH_Module* ETHx, RCC_ClocksTypeDef* pClk)
{
    uint32_t HclkFreq;
    
    if (ETHx == ETH1)
    {
        /* CSR clock of ETH1 is the AHB2 clock */
        HclkFreq = pClk->AHB2ClkFreq;
    }
    else
    {
        /* CSR clock of ETH2 is the AHB1 clock */
        HclkFreq = pClk->AHB1ClkFreq;
    }

    /* Set CR[3:0] bits by HclkFreq */
    if((HclkFreq >= ETH_MACCSR_CLOCK_FREQ_20M) && (HclkFreq < ETH_MACCSR_CLOCK_FREQ_35M))
    {
        /* CSR Clock Range between 20-35 MHz */
        MODIFY_REG(ETHx->MACMDIOADDR, ETH_MACMDIOADDR_CR_MASK, ETH_MDCNCLK_CRSCLK_DIV16);
    }
    else if((HclkFreq >= ETH_MACCSR_CLOCK_FREQ_35M) && (HclkFreq < ETH_MACCSR_CLOCK_FREQ_60M))
    {
        /* CSR Clock Range between 35-60 MHz */
        MODIFY_REG(ETHx->MACMDIOADDR, ETH_MACMDIOADDR_CR_MASK, ETH_MDCNCLK_CRSCLK_DIV26);
    }
    else if((HclkFreq >= ETH_MACCSR_CLOCK_FREQ_60M) && (HclkFreq < ETH_MACCSR_CLOCK_FREQ_100M))
    {
        /* CSR Clock Range between 60-100 MHz */
        MODIFY_REG(ETHx->MACMDIOADDR, ETH_MACMDIOADDR_CR_MASK, ETH_MDCNCLK_CRSCLK_DIV42);
    }
    else if((HclkFreq >= ETH_MACCSR_CLOCK_FREQ_100M) && (HclkFreq < ETH_MACCSR_CLOCK_FREQ_150M))
    {
        /* CSR Clock Range between 100-150 MHz */
        MODIFY_REG(ETHx->MACMDIOADDR, ETH_MACMDIOADDR_CR_MASK, ETH_MDCNCLK_CRSCLK_DIV62);
    }
    else if((HclkFreq >= ETH_MACCSR_CLOCK_FREQ_150M) && (HclkFreq <= ETH_MACCSR_CLOCK_FREQ_250M))
    {
        /* CSR Clock Range between 150-250 MHz */
        MODIFY_REG(ETHx->MACMDIOADDR, ETH_MACMDIOADDR_CR_MASK, ETH_MDCNCLK_CRSCLK_DIV102);
    }
    else if((HclkFreq >= ETH_MACCSR_CLOCK_FREQ_250M) && (HclkFreq < ETH_MACCSR_CLOCK_FREQ_300M))
    {
        /* CSR Clock Range between 250-300 MHz */
        MODIFY_REG(ETHx->MACMDIOADDR, ETH_MACMDIOADDR_CR_MASK, ETH_MDCNCLK_CRSCLK_DIV124);
    }
    else if((HclkFreq >= ETH_MACCSR_CLOCK_FREQ_300M) && (HclkFreq <= ETH_MACCSR_CLOCK_FREQ_500M))
    {
        /* CSR Clock Range between 300-500 MHz */
        MODIFY_REG(ETHx->MACMDIOADDR, ETH_MACMDIOADDR_CR_MASK, ETH_MDCNCLK_CRSCLK_DIV204);
    }
    else /* (HclkFreq >= ETH_MACCSR_CLOCK_FREQ_500M) && (HclkFreq <= ETH_MACCSR_CLOCK_FREQ_800M) */
    {
        /* CSR Clock Range between 500-800 MHz */
        MODIFY_REG(ETHx->MACMDIOADDR, ETH_MACMDIOADDR_CR_MASK, ETH_MDCNCLK_CRSCLK_DIV324);
    }
}

/**
*\*\name    ETH_ConfigMDCFastClock.
*\*\fun     Configure the fast clock frequency (MDC clock > 2.5MHz) of the MDC based
*\*\        on the CSR clock frequency(HclkFreq),
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   DivValue (The input parameters must be the following values):
*\*\          - ETH_MDCFCLK_CRSCLK_DIV4
*\*\          - ETH_MDCFCLK_CRSCLK_DIV6
*\*\          - ETH_MDCFCLK_CRSCLK_DIV8
*\*\          - ETH_MDCFCLK_CRSCLK_DIV10
*\*\          - ETH_MDCFCLK_CRSCLK_DIV12
*\*\          - ETH_MDCFCLK_CRSCLK_DIV14
*\*\          - ETH_MDCFCLK_CRSCLK_DIV16
*\*\          - ETH_MDCFCLK_CRSCLK_DIV18
*\*\return  none
*\*\note    Configure for fast clocks is only supported if the interface chip supports
*\*\        faster MDC clocks.
**/
void ETH_ConfigMDCFastClock(ETH_Module* ETHx, uint32_t DivValue)
{
    /* Set CR[3:0] bits */
    MODIFY_REG(ETHx->MACMDIOADDR, ETH_MACMDIOADDR_CR_MASK, DivValue);
}

/**
*\*\name    ETH_ReadPHYRegister.
*\*\fun     Read a PHY register.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   PHYAddr :
*\*\          - PHY port address, must be a value from 0 to 31.
*\*\param   PHYReg :
*\*\          - PHY register address, must be a value from 0 to 31.
*\*\param   pRegValue :
*\*\          - Points to the address where the read PHY register value is stored.
*\*\return  0 or 1.
**/
uint32_t ETH_ReadPHYRegister(ETH_Module* ETHx, uint32_t PHYAddr, uint32_t PHYReg, uint32_t* pRegValue)
{
    uint32_t TempReg;
    uint32_t timeout = ETH_MDIO_BUS_TIMEOUT;

    /* Check for the Busy flag */
    if (READ_BIT(ETHx->MACMDIOADDR, ETH_MACMDIOADDR_GB) != 0U)
    {
        /* PHY interface is busy, directly return 0 */
        return 0U;
    }

    /* Get the ETH_MACMDIOADDR register value */
    TempReg = READ_REG(ETHx->MACMDIOADDR);
    /* Set the PHY port address */
    MODIFY_REG(TempReg, ETH_MACMDIOADDR_PA, (PHYAddr << 21U));
    /* Set the PHY register address */
    MODIFY_REG(TempReg, ETH_MACMDIOADDR_RDA, (PHYReg << 16U));
    /* Set the read operation mode */
    MODIFY_REG(TempReg, ETH_MACMDIOADDR_GOC, (ETH_MACMDIOADDR_GOC0 | ETH_MACMDIOADDR_GOC1));
    
    /* Set the MII Busy bit */
    SET_BIT(TempReg, ETH_MACMDIOADDR_GB);

    /* Write the set value into the MDII Address register */
    WRITE_REG(ETHx->MACMDIOADDR, TempReg);

    /* Wait for the Busy flag to clear */
    while (READ_BIT(ETHx->MACMDIOADDR, ETH_MACMDIOADDR_GB) != 0U)
    {
        if (timeout == 0U)
        {
            /* Timeout, directly return 0 */
            return 0U;
        }
        
        timeout--;
    }

    /* Get MACMIIDR value */
    *pRegValue = READ_REG(ETHx->MACMDIODATA);

    /* Success, return 1 */
    return 1U;
}

/**
*\*\name    ETH_WritePHYRegister.
*\*\fun     Write a PHY register.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   PHYAddr :
*\*\          - PHY port address, must be a value from 0 to 31.
*\*\param   PHYReg :
*\*\          - PHY register address, must be a value from 0 to 31.
*\*\param   PHYRegValue :
*\*\          - The value to write.
*\*\return  0 or 1.
**/
uint32_t ETH_WritePHYRegister(ETH_Module* ETHx, uint32_t PHYAddr, uint32_t PHYReg, uint32_t PHYRegValue)
{
    uint32_t TempReg;
    uint32_t timeout = ETH_MDIO_BUS_TIMEOUT;

    /* Check for the Busy flag */
    if (READ_BIT(ETHx->MACMDIOADDR, ETH_MACMDIOADDR_GB) != 0U)
    {
        /* PHY interface is busy, directly return 0 */
        return 0U;
    }

    /* Get the ETH_MACMDIOADDR register value */
    TempReg = READ_REG(ETHx->MACMDIOADDR);
    /* Set the PHY port address */
    MODIFY_REG(TempReg, ETH_MACMDIOADDR_PA, (PHYAddr << 21U));
    /* Set the PHY register address */
    MODIFY_REG(TempReg, ETH_MACMDIOADDR_RDA, (PHYReg << 16U));
    /* Set the write operation mode */
    MODIFY_REG(TempReg, ETH_MACMDIOADDR_GOC, ETH_MACMDIOADDR_GOC0);
    
    /* Set the MII Busy bit */
    SET_BIT(TempReg, ETH_MACMDIOADDR_GB);

    /* Write the value to the MDIO data register */
    WRITE_REG(ETHx->MACMDIODATA, (uint16_t)PHYRegValue);

    /* Write the set value into the MDII Address register */
    WRITE_REG(ETHx->MACMDIOADDR, TempReg);
    
    /* Wait for the Busy flag to clear */
    while (READ_BIT(ETHx->MACMDIOADDR, ETH_MACMDIOADDR_GB) != 0U)
    {
        if (timeout == 0U)
        {
            /* Timeout, directly return 0 */
            return 0U;
        }
        
        timeout--;
    }

    /* Success, return 1 */
    return 1U;
}

/**
*\*\name    ETH_ExternalPHYInit.
*\*\fun     Initialize the external PHY, including settings related to whether or
*\*\        not to enable the PHY auto-negotiation function.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\param   ETH_InitParam :
*\*\          - Pointer to the ETH_InitType structure which will be initialized.
*\*\return  One of EthFuncStatusType.
**/
EthFuncStatusType ETH_ExternalPHYInit(ETH_Module* ETHx, ETH_InfoType* pInfo, ETH_InitType* ETH_InitParam)
{
    uint32_t TickStart;
    uint32_t rPHYRegVlaue;
    uint32_t wPHYRegVlaue;
    uint32_t TempDelay = ETH_PHY_CONFIG_DELAY;
    
    /* Put the PHY in reset mode */
    if (!(ETH_WritePHYRegister(ETHx, (uint32_t)pInfo->PHYInfo.phyAddr,
                                     (uint32_t)pInfo->PHYInfo.bcRegAddr,
                                     (uint32_t)pInfo->PHYInfo.phyReset)))
    {
        /* Return ERROR */
        return ETH_ERROR_WPHY;
    }
    
    /* Delay to assure PHY reset */
    __ETH_DELAY(TempDelay);
    
    /* Check that DWT is enabled or not */
    if ((DEM_CR & DEM_CR_TRCENA) == (uint32_t)RESET)
    {
        /* Enable and initialize DWT */
        __ETH_TICK_START();
    }
    
    /* Get tick */
    TickStart = __ETH_GET_TICK;
    /* Wait for linked status */
    do
    {
        /* Read the PHY register */
        if (!(ETH_ReadPHYRegister(ETHx, (uint32_t)pInfo->PHYInfo.phyAddr,
                                        (uint32_t)pInfo->PHYInfo.bsRegAddr,
                                        &rPHYRegVlaue)))
        {
            /* Return ERROR */
            return ETH_ERROR_RPHY;
        }
        
        if ((__ETH_GET_TICK - TickStart) > ETH_PHY_LINKED_TIMEOUT)
        {
            /* Disable tick */
            __ETH_TICK_STOP();
            /* Return timeout */
            return ETH_ERROR_TIMEOUT;
        }
    } while ((rPHYRegVlaue & pInfo->PHYInfo.phyLinkOK) != pInfo->PHYInfo.phyLinkOK);
    
    /* Read the PHY register */
    if (!(ETH_ReadPHYRegister(ETHx, (uint32_t)pInfo->PHYInfo.phyAddr,
                                    (uint32_t)pInfo->PHYInfo.bcRegAddr,
                                    &rPHYRegVlaue)))
    {
        /* Return ERROR */
        return ETH_ERROR_RPHY;
    }
    
    /* Check whether to enable AutoNegotiation */
    if (pInfo->AutoNegCmd != DISABLE)
    {
        wPHYRegVlaue = rPHYRegVlaue;
        /* Enable PHY auto-negotiation */
        wPHYRegVlaue |= pInfo->PHYInfo.phyAutoNeg;
        
        /* Write the PHY register */
        if (!(ETH_WritePHYRegister(ETHx, (uint32_t)pInfo->PHYInfo.phyAddr,
                                         (uint32_t)pInfo->PHYInfo.bcRegAddr,
                                          wPHYRegVlaue)))
        {
            /* Return ERROR */
            return ETH_ERROR_WPHY;
        }
        
        /* Delay to assure PHY set */
        __ETH_DELAY(TempDelay);
        
        /* Get tick */
        TickStart = __ETH_GET_TICK;
        /* Wait until the auto-negotiation will be completed */
        do
        {
            /* Read the PHY register */
            if (!(ETH_ReadPHYRegister(ETHx, (uint32_t)pInfo->PHYInfo.phyAddr,
                                            (uint32_t)pInfo->PHYInfo.bsRegAddr,
                                            &rPHYRegVlaue)))
            {
                /* Return ERROR */
                return ETH_ERROR_RPHY;
            }
            
            if ((__ETH_GET_TICK - TickStart) > ETH_PHY_AUTONEGO_COMPLETED_TIMEOUT)
            {
                /* Disable tick */
                __ETH_TICK_STOP();
                /* Return timeout */
                return ETH_ERROR_TIMEOUT;
            }
        } while ((rPHYRegVlaue & pInfo->PHYInfo.phyAutoNegOK) != pInfo->PHYInfo.phyAutoNegOK);
        
        /* Set the MAC speed and duplex mode parameters by the read link status */
        switch (pInfo->PHYInfo.phyGetLinkStatus(pInfo->PHYInfo.phyAddr, pInfo->PHYInfo.sdRegAddr))
        {
            case ETH_LINK_10FULL:
                /* 10M */
                ETH_InitParam->SpeedSelect = ETH_SPEED_10M;
                /* Full-duplex */
                ETH_InitParam->Duplex = ETH_FULL_DUPLEX_MODE;
                break;
            case ETH_LINK_10HALF:
                /* 10M */
                ETH_InitParam->SpeedSelect = ETH_SPEED_10M;
                /* Half-duplex */
                ETH_InitParam->Duplex = ETH_HALF_DUPLEX_MODE;
                break;
            case ETH_LINK_100FULL:
                /* 100M */
                ETH_InitParam->SpeedSelect = ETH_SPEED_100M;
                /* Full-duplex */
                ETH_InitParam->Duplex = ETH_FULL_DUPLEX_MODE;
                break;
            case ETH_LINK_100HALF:
                /* 100M */
                ETH_InitParam->SpeedSelect = ETH_SPEED_100M;
                /* Half-duplex */
                ETH_InitParam->Duplex = ETH_HALF_DUPLEX_MODE;
                break;
            case ETH_LINK_1000FULL:
                /* 1000M */
                ETH_InitParam->SpeedSelect = ETH_SPEED_1000M;
                /* Full-duplex */
                ETH_InitParam->Duplex = ETH_FULL_DUPLEX_MODE;
                break;
            case ETH_LINK_1000HALF:
                /* 1000M */
                ETH_InitParam->SpeedSelect = ETH_SPEED_1000M;
                /* Half-duplex */
                ETH_InitParam->Duplex = ETH_HALF_DUPLEX_MODE;
                break;
            default:
                /* Return ERROR */
                return ETH_ERROR_PARAM;
        }
    }
    else
    {
        wPHYRegVlaue = rPHYRegVlaue;
        /* Disable PHY auto-negotiation */
        wPHYRegVlaue &= pInfo->PHYInfo.phyAutoNeg;
        /* Clear the PHY speed bit */
        wPHYRegVlaue &= pInfo->PHYInfo.phySpeedMask;
        /* Clear the PHY duplex bit */
        wPHYRegVlaue &= pInfo->PHYInfo.phyDuplexMask;
        /* Set PHY speed, duplex mode */
        wPHYRegVlaue |= pInfo->PHYInfo.phyMode;
        
        /* Write the PHY register */
        if (!(ETH_WritePHYRegister(ETHx, (uint32_t)pInfo->PHYInfo.phyAddr,
                                         (uint32_t)pInfo->PHYInfo.bcRegAddr,
                                          wPHYRegVlaue)))
        {
            /* Return ERROR */
            return ETH_ERROR_WPHY;
        }
        
        /* Delay to assure PHY set */
        __ETH_DELAY(TempDelay);
    }
    
    /* Disable tick */
    __ETH_TICK_STOP();
    
    /* Return SUCCESS */
    return ETH_SUCCESS;
}

/**
*\*\name    ETH_Init.
*\*\fun     Initialize the ETH module with ETH_InitParam of type ETH_InitType, including
*\*\        ETH MAC initialization, MTL initialization, ETH DMA initialization, etc.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\param   ETH_InitParam :
*\*\          - Pointer to the ETH_InitType structure which will be initialized.
*\*\return  One of EthFuncStatusType.
**/
EthFuncStatusType ETH_Init(ETH_Module* ETHx, ETH_InfoType* pInfo, ETH_InitType* ETH_InitParam)
{
    uint32_t TickStart;
    uint32_t TempValue;
    RCC_ClocksTypeDef Clk;
    EthFuncStatusType TempStatus;
    
    /* Check the pInfo and ETH_InitParam parameter */
    if ((pInfo == NULL) || (ETH_InitParam == NULL))
    {
        /* Return ERROR */
        return ETH_ERROR_PARAM;
    }

    /* Enable AFIO Clock */
#ifdef CORE_CM4
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M4_AFIO, ENABLE);
#else /* CORE_CM7 */
    RCC_EnableAHB5PeriphClk2(RCC_AHB5_PERIPHEN_M7_AFIO, ENABLE);
#endif
    /* Check whether the media interface is GMII or MII or RMII */
    if (ETHx == ETH1)
    {
        /* ETH1 supports GMII, MII and RMII */
        if (pInfo->MediaInterface == ETH_GMII_MODE)
        {
            /* Enable GMII configuration in the AFIO register */
            AFIO_ConfigETH1Mode(ETH1_GMII_SEL);
        }
        else if (pInfo->MediaInterface == ETH_MII_MODE)
        {
            /* Enable MII configuration in the AFIO register */
            AFIO_ConfigETH1Mode(ETH1_MII_SEL);
        }
        else
        {
            /* Enable RMII configuration in the AFIO register */
            AFIO_ConfigETH1Mode(ETH1_RMII_SEL);
        }
    }
    else
    {
        /* ETH2 supports MII and RMII */
        if (pInfo->MediaInterface == ETH_MII_MODE)
        {
            /* Enable MII configuration in the AFIO register */
            AFIO_ConfigETH2Mode(ETH2_MII_SEL);
        }
        else if (pInfo->MediaInterface == ETH_RMII_MODE)
        {
            /* Enable RMII configuration in the AFIO register */
            AFIO_ConfigETH2Mode(ETH2_RMII_SEL);
        }
        else
        {
            /* Returns ERROR if GMII is selected */
            return ETH_ERROR_MIF;
        }
    }
    
    /* Ethernet Software reset */
    /* Set the SWR bit: resets all MAC subsystem internal registers and logic */
    /* After reset all the registers holds their respective reset values */
    SET_BIT(ETHx->DMAMODE, ETH_DMAMODE_SWR);

    /* Check that DWT is enabled or not */
    if ((DEM_CR & DEM_CR_TRCENA) == (uint32_t)RESET)
    {
        /* Enable and initialize DWT */
        __ETH_TICK_START();
    }

    /* Get tick */
    TickStart = __ETH_GET_TICK;
    /* Wait for software reset */
    while (READ_BIT(ETHx->DMAMODE, ETH_DMAMODE_SWR) != (uint32_t)RESET)
    {
        if ((__ETH_GET_TICK - TickStart) > ETH_SWRESET_TIMEOUT)
        {
            /* Disable tick */
            __ETH_TICK_STOP();

            /* Return timeout */
            return ETH_ERROR_TIMEOUT;
        }
    }

    /* Disable tick */
    __ETH_TICK_STOP();

    /* Get clock frequency value */
    RCC_GetClocksFreqValue(&Clk);
    /* Check MDC clock mode */
    if (pInfo->MDCClockMode == ETH_MDCCLK_NORMAL)
    {
        /* Configure normal MDC clock */
        ETH_ConfigMDCNormalClock(ETHx, &Clk);
    }
    else
    {
        /* Configure Fast MDC Clock */
        ETH_ConfigMDCFastClock(ETHx, pInfo->CSRClkDiv);
    }

    /* initialization the external PHY */
    TempStatus = ETH_ExternalPHYInit(ETHx, pInfo, ETH_InitParam);
    /* Check if it has been successfully initialized */
    if (TempStatus != ETH_SUCCESS)
    {
        /* Return ERROR */
        return TempStatus;
    }

    /** ETH MAC initialization configuration **/
    
    /* Configure the ETH_MACCFG register, including setting PRELEN[1:0], DC,
    BL[1:0], DR, DCRS, DO, ECRSFD, LM, DM, FES, PS, JE, JD, BE, WD, ACS, CST,
    S2KP, GPSLCE, IPG[2:0], CSO, SARC[2:0], ARPOE bits */
    if (ETHx == ETH1)
    {
        /* ETH1 supports 10M/100M/1000M and packet bursting */
        TempValue = ((ETH_InitParam->TxPreambleLen)       | (ETH_InitParam->DeferralCheck)
                   | (ETH_InitParam->BackOffLimit)        | (ETH_InitParam->DisTxRetry)
                   | (ETH_InitParam->DisCSDuringTransmit) | (ETH_InitParam->DisRxOwn)
                   | (ETH_InitParam->CSBeforeTransmit)    | (ETH_InitParam->Loopback)
                   | (ETH_InitParam->Duplex)              | (ETH_InitParam->SpeedSelect)
                   | (ETH_InitParam->JumboPacket)         | (ETH_InitParam->DisTxJabber)
                   | (ETH_InitParam->PacketBurst)
                   | (ETH_InitParam->DisRxWatchdog)       | (ETH_InitParam->AutoPadCRCStrip)
                   | (ETH_InitParam->CRCStripTypePacket)  | (ETH_InitParam->Support2KPacket)
                   | (ETH_InitParam->GiantPacketSizeLimitCtrl)
                   | (ETH_InitParam->InterPacketGapVal)   | (ETH_InitParam->ChecksumOffload)
                   | (ETH_InitParam->SrcAddrCtrl)         | (ETH_InitParam->ARPOffload));
        /* Write to ETH_MACCFG */
        MODIFY_REG(ETHx->MACCFG, ETH1_MACCFG_MASK, TempValue);
    }
    else
    {
        /* ETH2 supports 10M/100M and does not support packet bursting */
        TempValue = ((ETH_InitParam->TxPreambleLen)       | (ETH_InitParam->DeferralCheck)
                   | (ETH_InitParam->BackOffLimit)        | (ETH_InitParam->DisTxRetry)
                   | (ETH_InitParam->DisCSDuringTransmit) | (ETH_InitParam->DisRxOwn)
                   | (ETH_InitParam->CSBeforeTransmit)    | (ETH_InitParam->Loopback)
                   | (ETH_InitParam->Duplex)              | (ETH_InitParam->SpeedSelect)
                   | (ETH_InitParam->JumboPacket)         | (ETH_InitParam->DisTxJabber)
                   | (ETH_InitParam->DisRxWatchdog)       | (ETH_InitParam->AutoPadCRCStrip)
                   | (ETH_InitParam->CRCStripTypePacket)  | (ETH_InitParam->Support2KPacket)
                   | (ETH_InitParam->GiantPacketSizeLimitCtrl)
                   | (ETH_InitParam->InterPacketGapVal)   | (ETH_InitParam->ChecksumOffload)
                   | (ETH_InitParam->SrcAddrCtrl)         | (ETH_InitParam->ARPOffload));
        /* Write to ETH_MACCFG */
        MODIFY_REG(ETHx->MACCFG, ETH2_MACCFG_MASK, TempValue);
    }

    /* Configure the ETH_MACEXTCFG register, including setting GPSL, DCRCC, SPEN,
    USP, EIPGEN, EIPG[4:0], APDIM bits */
    TempValue = ((ETH_InitParam->GiantPacketSizeLimit) | (ETH_InitParam->DisRxPacketCRCCheck)
               | (ETH_InitParam->SPDetect)             | (ETH_InitParam->USPPacketDetect)
               | (ETH_InitParam->ExtInterPacketGap)    | (ETH_InitParam->ExtInterPacketGapVal)
               | (ETH_InitParam->DropARPPacket));
    /* Write to ETH_MACEXTCFG */
    MODIFY_REG(ETHx->MACEXTCFG, ETH_MACEXTCFG_MASK, TempValue);

    /* Configure the ETH_MACPFLT register, including setting PR, HUC, HMC, DAIF,
    PM, DBF, PCF[1:0], SAIF, SAF, HPF, VTFE, IPFE, DNTU, RA bits */
    TempValue = ((ETH_InitParam->Promiscuous)         | (ETH_InitParam->HashUnicast)
               | (ETH_InitParam->HashMulticast)       | (ETH_InitParam->DAInverseFiltering)
               | (ETH_InitParam->PassAllMulticast)    | (ETH_InitParam->DisBroadcastPackets)
               | (ETH_InitParam->PassControlPackets)  | (ETH_InitParam->SAInverseFiltering)
               | (ETH_InitParam->SAFilter)            | (ETH_InitParam->HashOrPerfectFilter)
               | (ETH_InitParam->VLANTagFilter)       | (ETH_InitParam->Layer3Layer4Filter)
               | (ETH_InitParam->DropNonTcpUdpPackets)| (ETH_InitParam->ReceiveAll));
    /* Write to ETH_MACPFLT */
    MODIFY_REG(ETHx->MACPFLT, ETH_MACPFLT_MASK, TempValue);

    /* Configure the ETH_MACWDGTO register, including setting WTO[3:0], PWE bits */
    TempValue = ((ETH_InitParam->WatchdogTimeout) | (ETH_InitParam->ProgramWatchdog));
    /* Write to ETH_MACWDGTO */
    MODIFY_REG(ETHx->MACWDGTO, ETH_MACWDGTO_MASK, TempValue);

    /* Configure the ETH_MACTXFLWCTRL register, including setting TFE, PLT[2:0],
    DZPQ, PT bits */
    TempValue = ((ETH_InitParam->TxFlowControl)      | (ETH_InitParam->PauseLowThreshold)
               | (ETH_InitParam->DisZeroQuantaPause) | (ETH_InitParam->PauseTime));
    /* Write to ETH_MACTXFLWCTRL */
    MODIFY_REG(ETHx->MACTXFLWCTRL, ETH_MACTXFLWCTRL_MASK, TempValue);

    /* Configure the ETH_MACRXFLWCTRL register, including setting RFE, UP bits */
    TempValue = ((ETH_InitParam->RxFlowControl) | (ETH_InitParam->UPPacketDetect));
    /* Write to ETH_MACRXFLWCTRL */
    MODIFY_REG(ETHx->MACRXFLWCTRL, ETH_MACRXFLWCTRL_MASK, TempValue);

    /** ETH MTL initialization configuration **/

    /* Configure the ETH_MTLTXQOPMOD register, including setting TSF, TTC[2:0] bits */
    TempValue = (ETH_InitParam->TxQueueOperateMode);
    /* Write to ETH_MTLTXQOPMOD */
    MODIFY_REG(ETHx->MTLTXQOPMOD, ETH_MTLTXQOPMOD_MASK, TempValue);

    /* Configure the ETH_MTLRXQOPMOD register, including setting RTC[1:0], FUP, FEP,
    RSF, DISTCPEF bits */
    TempValue = ((ETH_InitParam->RxQueueOperateMode) | (ETH_InitParam->ForwardUSGoodPacket)
               | (ETH_InitParam->ForwardErrorPacket) | (ETH_InitParam->DisDropTCPIPCSErrorPacket));
    /* Write to ETH_MTLRXQOPMOD */
    MODIFY_REG(ETHx->MTLRXQOPMOD, ETH_MTLRXQOPMOD_MASK, TempValue);

    /** ETH DMA initialization configuration **/

    /* Configure the ETH_DMAMODE register, including setting DA, TXPR, PR[2:0], DCHE bits */
    TempValue = (ETH_InitParam->TxRxArbitration | (ETH_InitParam->DescriptorCache));
    /* Write to ETH_DMAMODE */
    MODIFY_REG(ETHx->DMAMODE, ETH_DMAMODE_MASK, TempValue);

    /* Configure the ETH_DMASBMODE register, including setting FB, AAL, MB, RB bits */
    TempValue = ((ETH_InitParam->BurstMode) | (ETH_InitParam->AddrAlignedBeats)
               | (ETH_InitParam->RebuildINCRxBurst));
    /* Write to ETH_DMASBMODE */
    MODIFY_REG(ETHx->DMASBMODE, ETH_DMASBMODE_MASK, TempValue);

    /* Configure the ETH_DMACH0CTRL register, including setting MSS[13:0] PBLx8, DSL[2:0] bits */
    TempValue = ((ETH_InitParam->MaxSegmentSize) | (ETH_InitParam->PBLx8mode)
               | (ETH_InitParam->DescriptorSkipLen));
    /* Write to ETH_DMACH0CTRL */
    MODIFY_REG(ETHx->DMACH0CTRL, ETH_DMACH0CTRL_MASK, TempValue);

    /* Configure the ETH_DMACH0TXCTRL register, including setting OSF, TSE, TxPBL[5:0], ETIC bits */
    TempValue = ((ETH_InitParam->OperateSecondPacket) | (ETH_InitParam->TCPSegment)
               | (ETH_InitParam->TxBurstLength)       | (ETH_InitParam->EarlyTxInterruptCtrl));
    /* Write to ETH_DMACH0TXCTRL */
    MODIFY_REG(ETHx->DMACH0TXCTRL, ETH_DMACH0TXCTRL_MASK, TempValue);

    /* Configure the ETH_DMACH0RXCTRL register, including setting RxPBL[5:0], ERIC, RPF bits */
    TempValue = ((ETH_InitParam->RxBurstLength) | (ETH_InitParam->EarlyRxInterruptCtrl)
               | (ETH_InitParam->RxPacketFlush));
    /* Write to ETH_DMACH0RXCTRL */
    MODIFY_REG(ETHx->DMACH0RXCTRL, ETH_DMACH0RXCTRL_MASK, TempValue);

    /* Set Receive Buffers Length (must be a multiple of 4) */
    if ((pInfo->RxBuffLen % 4U) != 0U)
    {
        /* Return Error */
        return ETH_ERROR_PARAM;
    }
    else
    {
        /* Write to ETH_DMACH0RXCTRL */
        MODIFY_REG(ETHx->DMACH0RXCTRL, ETH_RXBUFFERSIZE_MASK, (pInfo->RxBuffLen << 1U));
    }

    /* Initialize transmit DMA descriptor */
    ETH_DMATxDescListInit(ETHx, pInfo);
    /* Initialize receive DMA descriptor */
    ETH_DMARxDescListInit(ETHx, pInfo);

    /* Set MAC address high 16 bits */
    WRITE_REG(ETHx->MACADDR0H, ((uint32_t)(pInfo->pMACAddr[5U] << 8U)  | (uint32_t)(pInfo->pMACAddr[4U])));
    /* Set MAC address low 32 bits */
    WRITE_REG(ETHx->MACADDR0L, ((uint32_t)(pInfo->pMACAddr[3U] << 24U) | (uint32_t)(pInfo->pMACAddr[2U] << 16U)
                              | (uint32_t)(pInfo->pMACAddr[1U] << 8U)  | (uint32_t)(pInfo->pMACAddr[0U])));

    /* Set 1 μs tick counter, used to update certain EEE-related counters */
    if (ETHx == ETH1)
    {
        /* CSR clock of ETH1 is the AHB2 clock */
        WRITE_REG(ETHx->MAC1USTICCNT, (((uint32_t)Clk.AHB2ClkFreq / ETH_MAC_US_TICK) - 1U));
    }
    else
    {
        /* CSR clock of ETH1 is the AHB2 clock */
        WRITE_REG(ETHx->MAC1USTICCNT, (((uint32_t)Clk.AHB1ClkFreq / ETH_MAC_US_TICK) - 1U));
    }

    /* Return SUCCESS */
    return ETH_SUCCESS;
}

/**
*\*\name    ETH_TxMACCmd.
*\*\fun     Enables or disables the MAC transmission.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_TxMACCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MAC transmission */
        SET_BIT(ETHx->MACCFG, ETH_MACCFG_TE);
    }
    else
    {
        /* Disable the MAC transmission */
        CLEAR_BIT(ETHx->MACCFG, ETH_MACCFG_TE);
    }
}

/**
*\*\name    ETH_RxMACCmd.
*\*\fun     Enables or disables the MAC reception.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_RxMACCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MAC reception */
        SET_BIT(ETHx->MACCFG, ETH_MACCFG_RE);
    }
    else
    {
        /* Disable the MAC reception */
        CLEAR_BIT(ETHx->MACCFG, ETH_MACCFG_RE);
    }
}

/**
*\*\name    ETH_SetHashTable.
*\*\fun     Set the ETH Hash Table Value.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   pHashTable :
*\*\          - Pointer to a table of two 32 bit values, that contains the 64
*\*\            bits of the hash table.
*\*\return  none
**/
void ETH_SetHashTable(ETH_Module* ETHx, uint32_t *pHashTable)
{
    /* Set the [31:0] bits of the hash table */
    WRITE_REG(ETHx->MACHASHTR0, pHashTable[0]);
    /* Set the [63:32] bits of the hash table */
    WRITE_REG(ETHx->MACHASHTR1, pHashTable[1]);
}

/**
*\*\name    ETH_RxVLANTagStructInit.
*\*\fun     Initializes the structure parameter of type ETH_RxVLANTagInitType used to
*\*\        initialize VLAN tag. This function is usually called before initializing
*\*\        a parameter of type ETH_RxVLANTagInitType.
*\*\param   ETH_InitParam :
*\*\          - Pointer to the ETH_RxVLANTagInitType structure which will be initialized.
*\*\return  none
**/
void ETH_RxVLANTagStructInit(ETH_RxVLANTagInitType* ETH_RxVTInitParam)
{
    /** Set the default configuration **/

    /* Default Disable VLAN Tag Hash Table Match */
    ETH_RxVTInitParam->VLANTagHashTableMatch  = DISABLE;
    /* Default Disable VLAN Tag in Rx status */
    ETH_RxVTInitParam->VLANTagInStatus        = DISABLE;
    /* Default Set the VLAN Tag Stripping on Receive: NONE */
    ETH_RxVTInitParam->StripVLANTag           = ETH_VLANTAGRXSTRIPPING_NONE;
    /* Default Set VLAN Type Check: DISABLE Check */
    ETH_RxVTInitParam->VLANTypeCheck          = ETH_VLANTYPECHECK_DISABLE;
    /* Default Disable VLAN Tag Inverse Match */
    ETH_RxVTInitParam->VLANTagInverceMatch    = DISABLE;
    /* Default Disable 12-Bit VLAN Tag Comparison */
    ETH_RxVTInitParam->VLANTagComparison12Bit = DISABLE;
}

/**
*\*\name    ETH_RxVLANTagInit.
*\*\fun     Initialize VLAN tag processing on the receive path.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   ETH_RxVTInitParam :
*\*\          - Pointer to the ETH_RxVLANTagInitType structure which will be initialized.
*\*\return  none
**/
void ETH_RxVLANTagInit(ETH_Module* ETHx, ETH_RxVLANTagInitType* ETH_RxVTInitParam)
{
    uint32_t TempValue;

    /* Configure the ETH_MACVLANTAG register, including setting VTHM, EVLRXS, EVLS, DOVLTC,
    ERSVLM, ESVL, VTIM, ETV, VL[15:0] bits */
    TempValue = ((ETH_RxVTInitParam->VLANTagInStatus)     | (ETH_RxVTInitParam->VLANTagHashTableMatch)
               | (ETH_RxVTInitParam->StripVLANTag)        | (ETH_RxVTInitParam->VLANTypeCheck)
               | (ETH_RxVTInitParam->VLANTagInverceMatch) | (ETH_RxVTInitParam->VLANTagComparison12Bit));
    /* Write to ETH_MACVLANTAG */
    MODIFY_REG(ETHx->MACVLANTAG, ETH_MACVLANTAG_MASK, TempValue);
}

/**
*\*\name    ETH_SetVLANHashTable.
*\*\fun     Set the ETH VLAN Hash Table Value.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   HashTable :
*\*\          - VLAN hash table 16 bit value.
*\*\return  none
**/
void ETH_SetVLANHashTable(ETH_Module* ETHx, uint16_t HashTable)
{
    /* Set the [16:0] bits of the VLAN hash table */
    WRITE_REG(ETHx->MACVHASHT, HashTable);
}

/**
*\*\name    ETH_SetRxVLANIdentifier.
*\*\fun     Set the VLAN Identifier for Rx packets.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   VLANIdentifier :
*\*\          - VLAN Identifier value.
*\*\return  none
**/
void ETH_SetRxVLANIdentifier(ETH_Module* ETHx, uint32_t VLANIdentifier)
{
    /* Check if 12-bit compare is enabled */
    if (READ_BIT(ETHx->MACVLANTAG, ETH_MACVLANTAG_ETV) != (uint32_t)RESET)
    {
        /* Write 12-bit Identifier */
        MODIFY_REG(ETHx->MACVLANTAG, ETH_MACVLANTAG_VL_VID, VLANIdentifier);
    }
    else
    {
        /* Write 16-bit Identifier */
        MODIFY_REG(ETHx->MACVLANTAG, ETH_MACVLANTAG_VL, VLANIdentifier);
    }
}

/**
*\*\name    ETH_InitiatePauseControlPacket.
*\*\fun     Initiates a pause control packet transmission during TX flow control
*\*\        operation.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
*\*\note    The pause packet function is only valid when the MAC is configured
*\*\        in full-duplex mode. 
*\*\note    During control packet transmission, this bit remains set to 1 to
*\*\        indicate that packet transmission is in progress. When pause packet
*\*\        transmission is complete, the MAC resets this bit to 0. No write
*\*\        operations should be performed to this register until this bit is
*\*\        cleared.
**/
void ETH_InitiatePauseControlPacket(ETH_Module* ETHx)
{
    /* Initiates pause control packet */
    SET_BIT(ETHx->MACTXFLWCTRL, ETH_MACTXFLWCTRL_FCB);
}

/**
*\*\name    ETH_ActivateBackpressure.
*\*\fun     Activate backpressure function during TX flow control operation.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
*\*\note    Activate backpressure function is only valid when the MAC is configured
*\*\        in half-duplex mode. 
*\*\note    during backpressure, when the MAC receives a new frame, the transmitter
*\*\        starts sending a JAM pattern resulting in a collision.
*\*\note    BPA is automatically disabled when the MAC is configured in full-duplex
*\*\        mode.
**/
void ETH_ActivateBackpressure(ETH_Module* ETHx)
{
    /* Activate the MAC BackPressure operation */
    SET_BIT(ETHx->MACTXFLWCTRL, ETH_MACTXFLWCTRL_BPA);
}

/**
*\*\name    ETH_PowerDownCmd.
*\*\fun     Enables or disables the ETH Power Down mode.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_PowerDownCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MAC Power Down */
        /* This puts the MAC in power down mode */
        SET_BIT(ETHx->MACPMTCTRLSTS, ETH_MACPMTCTRLSTS_PWRDWN);
    }
    else
    {
        /* Disable the MAC Power Down */ 
        CLEAR_BIT(ETHx->MACPMTCTRLSTS, ETH_MACPMTCTRLSTS_PWRDWN);
    }
}

/**
*\*\name    ETH_MagicPacketDetectionCmd.
*\*\fun     Enables or disables the MAC Magic Packet Detection.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_MagicPacketDetectionCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MAC Magic Packet Detection */
        SET_BIT(ETHx->MACPMTCTRLSTS, ETH_MACPMTCTRLSTS_MGKPKTEN);
    }
    else
    {
        /* Disable the MAC Magic Packet Detection */
        CLEAR_BIT(ETHx->MACPMTCTRLSTS, ETH_MACPMTCTRLSTS_MGKPKTEN);
    }
}

/**
*\*\name    ETH_WakeUpPacketDetectionCmd.
*\*\fun     Enables or disables the MAC Remote Wake-Up Packet Detection.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_WakeUpPacketDetectionCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MAC Remote Wake-Up Packet Detection */
        SET_BIT(ETHx->MACPMTCTRLSTS, ETH_MACPMTCTRLSTS_RWKPKTEN);
    }
    else
    {
        /* Disable the MAC Remote Wake-Up Packet Detection */ 
        CLEAR_BIT(ETHx->MACPMTCTRLSTS, ETH_MACPMTCTRLSTS_RWKPKTEN);
    }
}

/**
*\*\name    ETH_GlobalUnicastWakeUpCmd.
*\*\fun     Enables or disables any unicast packet filtered by the MAC
*\*\        address recognition to be a wake-up packet.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_GlobalUnicastWakeUpCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MAC Remote Wake-Up Packet Detection */
        SET_BIT(ETHx->MACPMTCTRLSTS, ETH_MACPMTCTRLSTS_GLBLUCAST);
    }
    else
    {
        /* Disable the MAC Remote Wake-Up Packet Detection */ 
        CLEAR_BIT(ETHx->MACPMTCTRLSTS, ETH_MACPMTCTRLSTS_GLBLUCAST);
    }
}

/**
*\*\name    ETH_ResetWakeUpPacketFilterRegPointer.
*\*\fun     Reset Wakeup packet filter register pointer.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
**/
void ETH_ResetWakeUpPacketFilterRegPointer(ETH_Module* ETHx)
{
    /* Resets the Remote Wake-up packet Filter register pointer to 0x0000 */
    SET_BIT(ETHx->MACPMTCTRLSTS, ETH_MACPMTCTRLSTS_RWKFILTRST);
}

/**
*\*\name    ETH_SetWakeUpPacketFilterRegister.
*\*\fun     Populates the remote wakeup packet registers.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   pBuffer :
*\*\          - Pointer on remote WakeUp Packet Filter Register buffer data (8 words).
*\*\return  none
*\*\note    When MAC RWK Packet Filter register is written, the content is transferred
*\*\        from CSR clock domain to PHY receive clock domain after the write operation,
*\*\        there should not be any further write to the MAC RWK Packet Filter register
*\*\        until the first write is updated in PHY receive clock domain. Otherwise, the
*\*\        second write operation does not get updated to the PHY receive clock domain.
*\*\        Therefore, the delay between two writes to the MAC RWK Packet Filter register
*\*\        should be at least 4 cycles of the PHY receive clock.
**/
void ETH_SetWakeUpPacketFilterRegister(ETH_Module* ETHx, uint32_t *pBuffer)
{
    uint32_t TempIndex;
    uint32_t TempDelay = ETH_WRITE_REG_DELAY;

    for (TempIndex = 0; TempIndex < ETH_WAKEUP_REGISTER_LEN; TempIndex++)
    {
        /* Write each time to the same register */
        WRITE_REG(ETHx->MACRWUPFLT, pBuffer[TempIndex]);

        /* Must be delayed at least 4 cycles of the PHY receive clock */
        __ETH_DELAY(TempDelay);
    }
}

/**
*\*\name    ETH_CSRRegisterWrite1ClearCmd.
*\*\fun     Enables or disables Write 1 clear mode for some CSR registers.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_CSRRegisterWrite1ClearCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enables Write 1 clear mode for some CSR registers */
        /* The application needs to set the corresponding bit to 1 to clear it */
        SET_BIT(ETHx->MACCSRSWCTRL, ETH_MACCSRSWCTRL_RCWE);
    }
    else
    {
        /* Disable Write 1 clear mode for some CSR registers */ 
        /* The access mode for these register fields remains "read clear" */
        CLEAR_BIT(ETHx->MACCSRSWCTRL, ETH_MACCSRSWCTRL_RCWE);
    }
}

/**
*\*\name    ETH_SetMACAddress.
*\*\fun     Set MAC address by application layer setting. Support configuring
*\*\        MAC address registers 0~3.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Offset (The input parameters must be the following values):
*\*\          - ETH_MAC_ADDR0_OFFSET
*\*\          - ETH_MAC_ADDR1_OFFSET
*\*\          - ETH_MAC_ADDR2_OFFSET
*\*\          - ETH_MAC_ADDR3_OFFSET
*\*\param   pAddr:
*\*\          - Pointer on MAC address buffer
*\*\return  none
**/
void ETH_SetMACAddress(ETH_Module* ETHx, EthMacAddr0123Type Offset, uint8_t* pAddr)
{
    uint32_t TempValue;
    uint32_t macAddrRegBaseH;
    uint32_t macAddrRegBaseL;

    /* Get the MAC address high register base address */
    macAddrRegBaseH = (uint32_t)&(ETHx->MACADDR0H);

    /* Get the MAC address low register base address */
    macAddrRegBaseL = (uint32_t)&(ETHx->MACADDR0L);

    /* Set MAC addr high bits (32~47) */
    TempValue = (((uint32_t)(pAddr[5]) << 8) | (uint32_t)pAddr[4]);
    (*(__IO uint32_t *) (macAddrRegBaseH + Offset)) = TempValue;

    /* Set MAC addr low bits (0~31) */
    TempValue = (((uint32_t)(pAddr[3]) << 24) | ((uint32_t)(pAddr[2]) << 16) |
                 ((uint32_t)(pAddr[1]) << 8) | (uint32_t)pAddr[0]);
    (*(__IO uint32_t *) (macAddrRegBaseL + Offset)) = TempValue;
}

/**
*\*\name    ETH_GetMACAddress.
*\*\fun     Get MAC address by application layer setting. Support get MAC address
*\*\        registers 0~3.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Offset (The input parameters must be the following values):
*\*\          - ETH_MAC_ADDR0_OFFSET
*\*\          - ETH_MAC_ADDR1_OFFSET
*\*\          - ETH_MAC_ADDR2_OFFSET
*\*\          - ETH_MAC_ADDR3_OFFSET
*\*\param   pAddr:
*\*\          - Pointer on MAC address buffer
*\*\return  none
**/
void ETH_GetMACAddress(ETH_Module* ETHx, EthMacAddr0123Type Offset, uint8_t* pAddr)
{
    uint32_t TempValue;
    uint32_t macAddrRegBaseH;
    uint32_t macAddrRegBaseL;

    /* Get the MAC address high register base address */
    macAddrRegBaseH = (uint32_t)&(ETHx->MACADDR0H);

    /* Get the MAC address low register base address */
    macAddrRegBaseL = (uint32_t)&(ETHx->MACADDR0L);

    /* Get the MAC address high register value */
    TempValue = *(__IO uint32_t *) (macAddrRegBaseH + Offset);
    /* Save MAC addr high bits (32~47) */
    pAddr[5] = ((TempValue >> 8) & (uint8_t)0xFF);
    pAddr[4] = (TempValue & (uint8_t)0xFF);

    /* Get the MAC address low register value */
    TempValue = *(__IO uint32_t *) (macAddrRegBaseL + Offset);
    /* Save MAC addr low bits (0~31) */
    pAddr[3] = ((TempValue >> 24) & (uint8_t)0xFF);
    pAddr[2] = ((TempValue >> 16) & (uint8_t)0xFF);
    pAddr[1] = ((TempValue >> 8) & (uint8_t)0xFF);
    pAddr[0] = (TempValue & (uint8_t)0xFF);
}

/**
*\*\name    ETH_MACAddressPerfectFilterCmd.
*\*\fun     Enables or disables the Address filter module uses the specified ETH
*\*\        MAC address (MAC address 1 ~ MAC address 3) for perfect filtering.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Offset (The input parameters must be the following values):
*\*\          - ETH_MACADDR1_OFFSET
*\*\          - ETH_MACADDR2_OFFSET
*\*\          - ETH_MACADDR3_OFFSET
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_MACAddressPerfectFilterCmd(ETH_Module* ETHx, EthMacAddr123Type Offset, FunctionalStatus Cmd)
{
    uint32_t macAddrRegBaseH;

    /* Get the MAC address high register base address */
    macAddrRegBaseH = (uint32_t)&(ETHx->MACADDR0H);

    if (Cmd != DISABLE)
    {
        /* Enable the selected ETH MAC address (1~3) for perfect filtering */
        (*(__IO uint32_t *) (macAddrRegBaseH + Offset)) |= ETH_MACADDR1H_AE;
    }
    else
    {
        /* Disable the selected ETH MAC address (1~3) for perfect filtering */
        (*(__IO uint32_t *) (macAddrRegBaseH + Offset)) &= (~ETH_MACADDR1H_AE);
    }
}

/**
*\*\name    ETH_SetMACAddressFilter.
*\*\fun     Set the filter type for the specified ETH MAC address (MAC address 1 ~
*\*\        MAC address 3).
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Offset (The input parameters must be the following values):
*\*\          - ETH_MACADDR1_OFFSET
*\*\          - ETH_MACADDR2_OFFSET
*\*\          - ETH_MACADDR3_OFFSET
*\*\param   Filter (The input parameters must be the following values):
*\*\          - ETH_MACADDR_FILTER_SA
*\*\          - ETH_MACADDR_FILTER_DA
*\*\return  none
**/
void ETH_SetMACAddressFilter(ETH_Module* ETHx, EthMacAddr123Type Offset, EthMacAddrFilterType Filter)
{
    uint32_t macAddrRegBaseH;

    /* Get the MAC address high register base address */
    macAddrRegBaseH = (uint32_t)&(ETHx->MACADDR0H);

    if (Filter != ETH_MACADDR_FILTER_DA)
    {
        /* The selected ETH MAC address is used to compare with the SA fields of the
        received frame */
        (*(__IO uint32_t *) (macAddrRegBaseH + Offset)) |= ETH_MACADDR1H_SA;
    }
    else
    {
        /* The selected ETH MAC address is used to compare with the DA fields of the
        received frame */
        (*(__IO uint32_t *) (macAddrRegBaseH + Offset)) &= (~ETH_MACADDR1H_SA);
    }
}

/**
*\*\name    ETH_SetMACAddressFilterMaskBytes.
*\*\fun     Set the filter mask bytes for the specified ETH MAC address (MAC address 1 ~
*\*\        MAC address 3).
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Offset (The input parameters must be the following values):
*\*\          - ETH_MACADDR1_OFFSET
*\*\          - ETH_MACADDR2_OFFSET
*\*\          - ETH_MACADDR3_OFFSET
*\*\param   MaskByte (The input parameters must be the following values):
*\*\          - ETH_MACADDR_MASK_BYTE6
*\*\          - ETH_MACADDR_MASK_BYTE5
*\*\          - ETH_MACADDR_MASK_BYTE4
*\*\          - ETH_MACADDR_MASK_BYTE3
*\*\          - ETH_MACADDR_MASK_BYTE2
*\*\          - ETH_MACADDR_MASK_BYTE1
*\*\return  none
**/
void ETH_SetMACAddressFilterMaskBytes(ETH_Module* ETHx, EthMacAddr123Type Offset, uint32_t MaskByte)
{
    uint32_t macAddrRegBaseH;

    /* Get the MAC address high register base address */
    macAddrRegBaseH = (uint32_t)&(ETHx->MACADDR0H);

    /* Clear MBC bits in the selected MAC address high register */
    (*(__IO uint32_t*)(macAddrRegBaseH + Offset)) &= (~ETH_MACADDR_MASK_MBC);

    /* Set the selected Filetr mask bytes */
    (*(__IO uint32_t*)(macAddrRegBaseH + Offset)) |= MaskByte;
}

/**
*\*\name    ETH_MMCCountersReset.
*\*\fun     Resets the MMC Counters.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
**/
void ETH_MMCCountersReset(ETH_Module* ETHx)
{
    /* Resets the MMC Counters */
    SET_BIT(ETHx->MMCCTRL, ETH_MMCCTRL_CNTRST);
}

/**
*\*\name    ETH_MMCCounterStopRolloverCmd.
*\*\fun     Enables or disables the MMC Counter Stop Rollover.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_MMCCounterStopRolloverCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MMC Counter Stop Rollover */
        /* The counter does not rollover to 0 after reaching the maximum value */
        SET_BIT(ETHx->MMCCTRL, ETH_MMCCTRL_CNTSTOPRO);
    }
    else
    {
        /* Disable the MMC Counter Stop Rollover */
        CLEAR_BIT(ETHx->MMCCTRL, ETH_MMCCTRL_CNTSTOPRO);
    }
}

/**
*\*\name    ETH_MMCResetOnReadCmd.
*\*\fun     Enables or disables the MMC Reset On Read.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_MMCResetOnReadCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MMC Counter reset on read */
        SET_BIT(ETHx->MMCCTRL, ETH_MMCCTRL_RSTONRD);
    }
    else
    {
        /* Disable the MMC Counter reset on read */
        CLEAR_BIT(ETHx->MMCCTRL, ETH_MMCCTRL_RSTONRD);
    }
}

/**
*\*\name    ETH_MMCCounterFreezeCmd.
*\*\fun     Enables or disables the MMC Counter Freeze.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_MMCCounterFreezeCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the MMC Counter Freeze */
        SET_BIT(ETHx->MMCCTRL, ETH_MMCCTRL_CNTFREEZ);
    }
    else
    {
        /* Disable the MMC Counter Freeze */
        CLEAR_BIT(ETHx->MMCCTRL, ETH_MMCCTRL_CNTFREEZ);
    }
}

/**
*\*\name    ETH_MMCCounterHalfPreset.
*\*\fun     Preset and Initialize the MMC counters to almost-half value:
*\*\        0x7FFF_FFF0.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
**/
void ETH_MMCCounterHalfPreset(ETH_Module* ETHx)
{
    /* Preset and Initialize the MMC counters to almost-half value */
    CLEAR_BIT(ETHx->MMCCTRL, ETH_MMCCTRL_CNTPRSTLVL);

    /* Enable counter preset function */
    SET_BIT(ETHx->MMCCTRL, ETH_MMCCTRL_CNTPRST);
}

/**
*\*\name    ETH_MMCCounterFullPreset.
*\*\fun     Preset and Initialize the MMC counters to almost-full value:
*\*\        0xFFFF_FFF0.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
**/
void ETH_MMCCounterFullPreset(ETH_Module* ETHx)
{
    /* Preset and Initialize the MMC counters to almost-full value */
    SET_BIT(ETHx->MMCCTRL, ETH_MMCCTRL_CNTPRSTLVL);

    /* Enable counter preset function */
    SET_BIT(ETHx->MMCCTRL, ETH_MMCCTRL_CNTPRST);
}

/**
*\*\name    ETH_MMCCounterUpdateForDropBCPacketCmd.
*\*\fun     Enables or disables the Update MMC Counters for Dropped Broadcast
*\*\        Packets.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_MMCCounterUpdateForDropBCPacketCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable Update MMC Counters for Dropped Broadcast Packets */
        SET_BIT(ETHx->MMCCTRL, ETH_MMCCTRL_UCDBC);
    }
    else
    {
        /* Disable Update MMC Counters for Dropped Broadcast Packets */
        CLEAR_BIT(ETHx->MMCCTRL, ETH_MMCCTRL_UCDBC);
    }
}

/**
*\*\name    ETH_GetMMCCounterValue.
*\*\fun     Get the specified ETH MMC counter value.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Offset (The input parameters must be the following values):
*\*\          - ETH_MMC_SCGP_OFFSET
*\*\          - ETH_MMC_MCGP_OFFSET
*\*\          - ETH_MMC_PCG_OFFSET
*\*\          - ETH_MMC_BPG_OFFSET
*\*\          - ETH_MMC_MPG_OFFSET
*\*\          - ETH_MMC_CRCEP_OFFSET
*\*\          - ETH_MMC_AEP_OFFSET
*\*\          - ETH_MMC_UPG_OFFSET
*\*\return  Corresponding counter value.
**/
uint32_t ETH_GetMMCCounterValue(ETH_Module* ETHx, EthMmcAddrType Offset)
{
    uint32_t mmcRegBaseAddr;

    /* Get the ETH MMC register base address */
    mmcRegBaseAddr = (uint32_t)&(ETHx->MMCCTRL);

    /* Return the selected counter register value */
    return (*(__IO uint32_t *)(mmcRegBaseAddr + Offset));
}

/**
*\*\name    ETH_MACTimeStampCmd.
*\*\fun     Enables or disables the MAC timestamp.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_MACTimeStampCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the time stamp for transmit and receive frames */
        SET_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TSENA);
    }
    else
    {
        /* Disable the time stamp for transmit and receive frames */
        CLEAR_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TSENA);
    }
}

/**
*\*\name    ETH_SetTimeStampUpdateMethod.
*\*\fun     Selects the MAC timestamp Update method.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Method (The input parameters must be the following values):
*\*\          - ETH_MACTS_FINE_UPDATE
*\*\          - ETH_MACTS_COARSE_UPDATE
*\*\return  none
**/
void ETH_SetTimeStampUpdateMethod(ETH_Module* ETHx, uint32_t Method)
{
    if (Method == ETH_MACTS_FINE_UPDATE)
    {
        /* Selects the Fine Update method */
        SET_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TSCFUPDT);
    }
    else
    {
        /* Selects the Coarse Update method */
        CLEAR_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TSCFUPDT);
    }
}

/**
*\*\name    ETH_MACTimeStampInit.
*\*\fun     Initialize the MAC timestamp. The system time is initialized
*\*\        (overwritten) with the values specified in the MAC System Time Seconds
*\*\        Update Register and the MAC System Time Nanoseconds Update Register.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
**/
void ETH_MACTimeStampInit(ETH_Module* ETHx)
{
    /* Initialize the MAC Time Stamp */
    SET_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TSINIT);
}

/**
*\*\name    ETH_MACTimeStampUpdate.
*\*\fun     Update the MAC timestamp. The system time is updated (added or
*\*\        subtracted) with the values specified in the MAC System Time Seconds
*\*\        Update Register and the MAC System Time Nanoseconds Update Register.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
**/
void ETH_MACTimeStampUpdate(ETH_Module* ETHx)
{
    /* Update the MAC Time Stamp */
    SET_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TSUPDT);
}

/**
*\*\name    ETH_EnableTimeStampIntTrigger.
*\*\fun     Enable the MAC TimeStamp interrupt trigger. the timestamp interrupt is
*\*\        generated when the System Time becomes greater than the value written
*\*\        in the Target Time register.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
**/
// void ETH_EnableTimeStampIntTrigger(ETH_Module* ETHx)
// {
//     /* Enable the MAC Time Stamp interrupt trigger */
//     SET_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TTSTRIG);
// }

/**
*\*\name    ETH_MACTimeStampAddendRegUpdate.
*\*\fun     Update the MAC timestamp addend register. the content of the Timestamp
*\*\        Addend register is updated in the PTP block for fine correction.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
**/
void ETH_MACTimeStampAddendRegUpdate(ETH_Module* ETHx)
{
    /* Update the MAC Time Stamp addend register */
    SET_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TSADDREG);
}

/**
*\*\name    ETH_MACTimeStampAllPacketsCmd.
*\*\fun     Enables or disables the MAC timestamp for All Packets.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_MACTimeStampAllPacketsCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable Timestamp for All Packets */
        SET_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TSENALL);
    }
    else
    {
        /* Disable Timestamp for all packets */
        CLEAR_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TSENALL);
    }
}

/**
*\*\name    ETH_MACTimeStampDigBinRolloverCmd.
*\*\fun     Enables or disables the MAC timestamp Rollover for Digital or Binary.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_MACTimeStampDigBinRolloverCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable Timestamp Digital or Binary Rollover */
        SET_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TSCTRLSSR);
    }
    else
    {
        /* Disables Timestamp Digital or Binary Rollover */
        CLEAR_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TSCTRLSSR);
    }
}

/**
*\*\name    ETH_PTPTypePacketProcesCmd.
*\*\fun     Enables or disables the processing for selected PTP packet type.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   PacketType (The input parameters must be the following values):
*\*\          - ETH_MACPTP_TYPE_VERSION2
*\*\          - ETH_MACPTP_TYPE_ETHERNET
*\*\          - ETH_MACPTP_TYPE_IPV6UDP
*\*\          - ETH_MACPTP_TYPE_IPV4UDP (default)
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_PTPTypePacketProcesCmd(ETH_Module* ETHx, uint32_t PacketType, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable processing for selected PTP packet types */
        SET_BIT(ETHx->MACTSCTRL, PacketType);
    }
    else
    {
        /* Disable processing for selected PTP packet types */
        CLEAR_BIT(ETHx->MACTSCTRL, PacketType);
    }
}

/**
*\*\name    ETH_MACAddrPTPPacketFilterCmd.
*\*\fun     Enables or disables the MAC address for PTP packet filtering.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_MACAddrPTPPacketFilterCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable MAC address for PTP packet filtering */
        SET_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TSENMACADDR);
    }
    else
    {
        /* Disable MAC address for PTP packet filtering */
        CLEAR_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TSENMACADDR);
    }
}

/**
*\*\name    ETH_MACTxTimeStampStatusModeCmd.
*\*\fun     Enables or disables the MAC TX timestamp status mode.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_MACTxTimeStampStatusModeCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable MAC TX timestamp status mode */
        SET_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TXTSSTSM);
    }
    else
    {
        /* Disable MAC TX timestamp status mode */
        CLEAR_BIT(ETHx->MACTSCTRL, ETH_MACTSCTRL_TXTSSTSM);
    }
}

/**
*\*\name    ETH_SetSubSecondIncrementValue.
*\*\fun     Sets the system time Sub-Second Increment value.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   IncValue :
*\*\          - 0~0xFF
*\*\return  none
**/
void ETH_SetSubSecondIncrementValue(ETH_Module* ETHx, uint8_t IncValue)
{
    /* Set the Sub-Second Increment Register */
    WRITE_REG(ETHx->MACSUBSINC, ((uint32_t)IncValue << 16));
}

/**
*\*\name    ETH_SetTimeStampUpdateValue.
*\*\fun     Sets the Time Stamp update value.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   CalMode (The input parameters must be the following values):
*\*\          - ETH_MACTS_CALMODE_SUB
*\*\          - ETH_MACTS_CALMODE_ADD
*\*\param   SecondValue :
*\*\          - 0~0xFFFFFFFF
*\*\param   SubSecondValue :
*\*\          - 0~0x7FFFFFFF
*\*\return  none
*\*\note    When CalMode is set to ETH_MACTS_CALMODE_SUB, the seconds field
*\*\        and nanosecond field must be programmed with the complement of
*\*\        the corresponding part of the update value.
**/
void ETH_SetTimeStampUpdateValue(ETH_Module* ETHx, uint32_t CalMode, uint32_t SecondValue, uint32_t SubSecondValue)
{
    /* Set MAC System Time Seconds Update Register */
    WRITE_REG(ETHx->MACSYSTSUP, SecondValue);
    /* Set MAC System Time Nanosecond Update Register */
    WRITE_REG(ETHx->MACSYSTNSUP, (CalMode | SubSecondValue));
}

/**
*\*\name    ETH_SetTimeStampAddendValue.
*\*\fun     Sets the Time Stamp addend value.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   AddValue :
*\*\          - 0~0xFFFFFFFF
*\*\return  none
**/
void ETH_SetTimeStampAddendValue(ETH_Module* ETHx, uint32_t AddValue)
{
    /* Set the MAC Timestamp Add Register */
    WRITE_REG(ETHx->MACTSADD, AddValue);
}

/**
*\*\name    ETH_GetTimeStampRegValue.
*\*\fun     Gets the specified ETH MAC TimeStamp register value.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Offset (The input parameters must be the following values):
*\*\          - ETH_MACTS_SSIR_OFFSET
*\*\          - ETH_MACTS_STSR_OFFSET
*\*\          - ETH_MACTS_STNSR_OFFSET
*\*\          - ETH_MACTS_STSUR_OFFSET
*\*\          - ETH_MACTS_STNSUR_OFFSET
*\*\          - ETH_MACTS_TAR_OFFSET
*\*\          - ETH_MACTS_TTSNSR_OFFSET
*\*\          - ETH_MACTS_TTSSR_OFFSET
*\*\          - ETH_MACTS_TICNSR_OFFSET
*\*\          - ETH_MACTS_TECNSR_OFFSET
*\*\          - ETH_MACTS_TILR_OFFSET
*\*\          - ETH_MACTS_TELR_OFFSET
*\*\          - ETH_MACTS_PTTSR_OFFSET
*\*\          - ETH_MACTS_PTTNSR_OFFSET
*\*\return  Corresponding MAC TimeStamp value.
**/
uint32_t ETH_GetTimeStampRegValue(ETH_Module* ETHx, EthTsAddrType Offset)
{
    uint32_t tsRegBaseAddr;

    /* Get the ETH MAC TimeStamp register base address */
    tsRegBaseAddr = (uint32_t)&(ETHx->MACTSCTRL);

    /* Return the selected MAC TimeStamp register value */
    return (*(__IO uint32_t *)(tsRegBaseAddr + Offset));
}

/**
*\*\name    ETH_ConfigPPSOutput.
*\*\fun     Configure the PPS output, e.g. configure the output frequency,
*\*\        which defaults to one pulse per second.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   OutputFreq (The input parameters must be the following values):
*\*\          - ETH_MACPPS_FREQCTRL_B2D1
*\*\          - ETH_MACPPS_FREQCTRL_B4D2
*\*\          - ETH_MACPPS_FREQCTRL_B8D4
*\*\          - ETH_MACPPS_FREQCTRL_B16D8
*\*\          - ETH_MACPPS_FREQCTRL_B32D16
*\*\          - ETH_MACPPS_FREQCTRL_B64D32
*\*\          - ETH_MACPPS_FREQCTRL_B128D64
*\*\          - ETH_MACPPS_FREQCTRL_B256D128
*\*\          - ETH_MACPPS_FREQCTRL_B512D256
*\*\          - ETH_MACPPS_FREQCTRL_B1024D512
*\*\          - ETH_MACPPS_FREQCTRL_B2048D1024
*\*\          - ETH_MACPPS_FREQCTRL_B4096D2048
*\*\          - ETH_MACPPS_FREQCTRL_B8192D4096
*\*\          - ETH_MACPPS_FREQCTRL_B16384D8192
*\*\          - ETH_MACPPS_FREQCTRL_B32768D16384
*\*\return  none
**/
void ETH_ConfigPPSOutput(ETH_Module* ETHx, uint32_t OutputFreq)
{
    /* Set PPS Output Frequency Control field */
    MODIFY_REG(ETHx->MACPPSCTRL, ETH_MACPPSCTRL_PPSCTRL, OutputFreq);
}

/**
*\*\name    ETH_SetPPSTargetTimeValue.
*\*\fun     Sets the PPS target time value with seconds field and nanosecond field.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   SecondValue :
*\*\          - 0~0xFFFFFFFF
*\*\param   SubSecondValue :
*\*\          - 0~0x7FFFFFFF
*\*\return  none
**/
void ETH_SetPPSTargetTimeValue(ETH_Module* ETHx, uint32_t SecondValue, uint32_t SubSecondValue)
{
    /* Set MAC PPS Target Time Seconds Register */
    WRITE_REG(ETHx->MACPPSTTS, SecondValue);
    /* Set MAC PPS Target Time Nanosecond Register */
    WRITE_REG(ETHx->MACPPSTTNS, SubSecondValue);
}



/**
*\*\name    ETH_MTLDropTxStatusCmd.
*\*\fun     Enables or disables the Drop Transmit Status.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_MTLDropTxStatusCmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Tx packet status received from the MAC is dropped in the MTL */
        SET_BIT(ETHx->MTLOPMOD, ETH_MTLOPMOD_DTXSTS);
    }
    else
    {
        /* Tx packet status received from the MAC is forwarded to the application */
        CLEAR_BIT(ETHx->MTLOPMOD, ETH_MTLOPMOD_DTXSTS);
    }
}

/**
*\*\name    ETH_MTLCounterPreset.
*\*\fun     Preset and Initialize the MTL counters to value: 0x7F0.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
**/
void ETH_MTLCounterPreset(ETH_Module* ETHx)
{
    /* Set the CNTPRST bit */
    SET_BIT(ETHx->MTLOPMOD, ETH_MTLOPMOD_CNTPRST);
}

/**
*\*\name    ETH_MTLCounterReset.
*\*\fun     Reset all counters of MTL.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
*\*\note    The counter reset control bit is automatically cleared after 1 clock
*\*\        cycle.
**/
void ETH_MTLCounterReset(ETH_Module* ETHx)
{
    /* Set the CNTCLR bit */
    SET_BIT(ETHx->MTLOPMOD, ETH_MTLOPMOD_CNTCLR);
}

/**
*\*\name    ETH_FlushTransmitQueue.
*\*\fun     Clears the ETH transmit FIFO.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
*\*\note    The MTL Transmit Queue Operation Mode Register (ETH_MTLTXQOPMOD)
*\*\        should not be written until the flush operation is complete.
*\*\        This function causes all data in the Tx FIFO to be lost or flushed.
*\*\        However, data that has been accepted by the MAC transmitter will not
*\*\        be flushed. It will be scheduled for transmission and will result in
*\*\        underflow and short packets being sent.
**/
void ETH_FlushTransmitQueue(ETH_Module* ETHx)
{
    /* Set the FTQ bit */
    SET_BIT(ETHx->MTLTXQOPMOD, ETH_MTLTXQOPMOD_FTQ);
}

/**
*\*\name    ETH_GetMTLUnderflowPacketCounter.
*\*\fun     Get the number of packets aborted by the controller due to Tx queue
*\*\        underflow.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  Counter value: 0~0x7FF.
**/
uint16_t ETH_GetMTLUnderflowPacketCounter(ETH_Module* ETHx)
{
    /* Return the value of the Underflow Packet Counter */
    return ((uint16_t)READ_BIT(ETHx->MTLTXQUDF, ETH_MTLTXQUDF_UFFRMCNT));
}

/**
*\*\name    ETH_GetMTLOverflowPacketCounter.
*\*\fun     Gets the number of packets discarded due to Rx queue overflow.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  Counter value: 0~0x7FF.
**/
uint16_t ETH_GetMTLOverflowPacketCounter(ETH_Module* ETHx)
{
    /* Return the value of the Overflow Packet Counter */
    return ((uint16_t)READ_BIT(ETHx->MTLRXQMPOFCNT, ETH_MTLRXQMPOFCNT_OVFPKTCNT));
}

/**
*\*\name    ETH_GetMTLMissedPacketCounter.
*\*\fun     Gets the number of packets lost due to the application performing
*\*\        packet refresh requests against this queue.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  Counter value: 0~0x7FF.
**/
uint16_t ETH_GetMTLMissedPacketCounter(ETH_Module* ETHx)
{
    /* Return the value of the Missed Packet Counter */
    return ((uint16_t)READ_BIT(ETHx->MTLRXQMPOFCNT, ETH_MTLRXQMPOFCNT_MISPKTCNT));
}



/**
*\*\name    ETH_SoftwareReset.
*\*\fun     ETH software reset, the MAC and the DMA controller reset the logic
*\*\        and all internal registers of the DMA, MTL, and MAC.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
*\*\note    1. The software reset status bit (SWR) is automatically cleared after
*\*\        the reset operation is completed.
*\*\        2. Before reprogramming any ETH register, a value of zero should be
*\*\        read in SWR bit.
*\*\        3. The SWR bit must be read at least 4 CSR clock cycles after it is
*\*\        written to 1.
**/
void ETH_SoftwareReset(ETH_Module* ETHx)
{
    /* Set the SWR bit */
    SET_BIT(ETHx->DMAMODE, ETH_DMAMODE_SWR);
}

/**
*\*\name    ETH_TxDMACmd.
*\*\fun     Enables or disables the DMA transmission.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_TxDMACmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DMA transmission */
        SET_BIT(ETHx->DMACH0TXCTRL, ETH_DMACH0TXCTRL_ST);
    }
    else
    {
        /* Disable the DMA transmission */
        CLEAR_BIT(ETHx->DMACH0TXCTRL, ETH_DMACH0TXCTRL_ST);
    }
}

/**
*\*\name    ETH_RxDMACmd.
*\*\fun     Enables or disables the DMA reception.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_RxDMACmd(ETH_Module* ETHx, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DMA reception */
        SET_BIT(ETHx->DMACH0RXCTRL, ETH_DMACH0RXCTRL_SR);
    }
    else
    {
        /* Disable the DMA reception */
        CLEAR_BIT(ETHx->DMACH0RXCTRL, ETH_DMACH0RXCTRL_SR);
    }
}

/**
*\*\name    ETH_ResumeDMATransmission.
*\*\fun     Resume TX DMA by writing any value to transmit descriptor tail pointer
*\*\        register when TX DMA enters suspend mode.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
*\*\note    This function is only applicable when the DMA enters suspend mode.
**/
void ETH_ResumeDMATransmission(ETH_Module* ETHx)
{
    /* Write ETH_DMACH0TXDTP register */
    WRITE_REG(ETHx->DMACH0TXDTP, 0U);
}

/**
*\*\name    ETH_ResumeDMAReception.
*\*\fun     Resume RX DMA by writing any value to receive descriptor tail pointer
*\*\        register when RX DMA enters suspend mode.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
*\*\note    This function is only applicable when the DMA enters suspend mode.
**/
void ETH_ResumeDMAReception(ETH_Module* ETHx)
{
    /* Write ETH_DMACH0RXDTP register */
    WRITE_REG(ETHx->DMACH0RXDTP, 0U);
}

/**
*\*\name    ETH_SetRxInterruptWatchdogTimer.
*\*\fun     Set the watchdog timer for the DMA receive interrupt.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   CntUnit (The input parameters must be the following values):
*\*\          - ETH_DMARXINT_WDGTIM_CNTUNIT_256
*\*\          - ETH_DMARXINT_WDGTIM_CNTUNIT_512
*\*\          - ETH_DMARXINT_WDGTIM_CNTUNIT_1024
*\*\          - ETH_DMARXINT_WDGTIM_CNTUNIT_2048
*\*\param   CntValue :
*\*\          - Count value: 0~0x000000FF.
*\*\return  none
*\*\note    Timer cycles = count unit * count value (CntUnit * CntValue) system
*\*\        clock cycles.
**/
void ETH_SetRxInterruptWatchdogTimer(ETH_Module* ETHx, uint32_t CntUnit, uint32_t CntValue)
{
    /* Set the RWTU bit and RWT bit */
    MODIFY_REG(ETHx->DMACH0RXINTWT, (ETH_DMACH0RXINTWT_RWTU | ETH_DMACH0RXINTWT_RWT), (CntUnit | CntValue));
}

/**
*\*\name    ETH_GetCurrentTxDescriptorAddress.
*\*\fun     Gets the address of the current application transmit descriptor read
*\*\        by the DMA.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  The value of the current Tx descriptor address.
**/
uint32_t ETH_GetCurrentTxDescriptorAddress(ETH_Module* ETHx)
{
    /* Return the value of ETH_DMACH0CATXD */
    return (READ_REG(ETHx->DMACH0CATXD));
}

/**
*\*\name    ETH_GetCurrentRxDescriptorAddress.
*\*\fun     Gets the address of the current application receive descriptor read
*\*\        by the DMA.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  The value of the current Rx descriptor address.
**/
uint32_t ETH_GetCurrentRxDescriptorAddress(ETH_Module* ETHx)
{
    /* Return the value of ETH_DMACH0CARXD */
    return (READ_REG(ETHx->DMACH0CARXD));
}

/**
*\*\name    ETH_GetCurrentTxBufferAddress.
*\*\fun     Gets the address of the current application transmit buffer read
*\*\        by the DMA.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  The value of the current Tx buffer address.
**/
uint32_t ETH_GetCurrentTxBufferAddress(ETH_Module* ETHx)
{
    /* Return the value of ETH_DMACH0CATXB */
    return (READ_REG(ETHx->DMACH0CATXB));
}

/**
*\*\name    ETH_GetCurrentRxBufferAddress.
*\*\fun     Gets the address of the current application receive buffer read
*\*\        by the DMA.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  The value of the current Rx buffer address.
**/
uint32_t ETH_GetCurrentRxBufferAddress(ETH_Module* ETHx)
{
    /* Return the value of ETH_DMACH0CARXB */
    return (READ_REG(ETHx->DMACH0CARXB));
}

/**
*\*\name    ETH_GetTxDMAErrorType.
*\*\fun     Get the type of TX DMA error that caused the fatal bus error.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  TX DMA Error Bits[2:0] Value:
*\*\          - bit[0]:
*\*\            - 1: Error during read transfer
*\*\            - 0: Error during write transfer
*\*\          - bit[1]:
*\*\            - 1: Error during descriptor access
*\*\            - 0: Error during data buffer access
*\*\          - bit[2]:
*\*\            - 1: Error during data transfer by Tx DMA
*\*\            - 0: No Error during data transfer by Tx DMA
*\*\        Invalid value:
*\*\          - 0xFF
*\*\note    This function returns a valid value only if a fatal bus error occurs
*\*\        (FBE set to 1). And these error types do not generate interrupts.
**/
uint8_t ETH_GetTxDMAErrorType(ETH_Module* ETHx)
{
    uint8_t ReturnValue;

    /* Check if a fatal bus error has occurred */
    if (READ_BIT(ETHx->DMACH0STS, ETH_DMACH0STS_FBE) != (uint32_t)RESET)
    {
        /* Return the value of the TX DMA error bits */
        ReturnValue = (uint8_t)(READ_BIT(ETHx->DMACH0STS, ETH_DMACH0STS_TEB) >> 16);
    }
    else
    {
        /* Return invalid value 0xFF */
        ReturnValue = (uint8_t)(0xFFU);
    }

    return ReturnValue;
}

/**
*\*\name    ETH_GetRxDMAErrorType.
*\*\fun     Get the type of RX DMA error that caused the fatal bus error.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  RX DMA Error Bits[2:0] Value:
*\*\          - bit[0]:
*\*\            - 1: Error during read transfer
*\*\            - 0: Error during write transfer
*\*\          - bit[1]:
*\*\            - 1: Error during descriptor access
*\*\            - 0: Error during data buffer access
*\*\          - bit[2]:
*\*\            - 1: Error during data transfer by Rx DMA
*\*\            - 0: No Error during data transfer by Rx DMA
*\*\        Invalid value:
*\*\          - 0xFF
*\*\note    This function returns a valid value only if a fatal bus error occurs
*\*\        (FBE set to 1). And these error types do not generate interrupts.
**/
uint8_t ETH_GetRxDMAErrorType(ETH_Module* ETHx)
{
    uint8_t ReturnValue;

    /* Check if a fatal bus error has occurred */
    if (READ_BIT(ETHx->DMACH0STS, ETH_DMACH0STS_FBE) != (uint32_t)RESET)
    {
        /* Return the value of the RX DMA error bits */
        ReturnValue = (uint8_t)(READ_BIT(ETHx->DMACH0STS, ETH_DMACH0STS_REB) >> 19);
    }
    else
    {
        /* Return invalid value 0xFF */
        ReturnValue = (uint8_t)(0xFFU);
    }

    return ReturnValue;
}

/**
*\*\name    ETH_GetDMACh0DroppedPacketCounter.
*\*\fun     Get the number of packet counters dropped by the DMA due to bus errors
*\*\        or programming the RPF field in the DMA Channel 0 Rx Control Register.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  Counter value: 0~0x7FF.
**/
uint16_t ETH_GetDMACh0DroppedPacketCounter(ETH_Module* ETHx)
{
    /* Return the value of the Dropped Packet Counter */
    return ((uint16_t)READ_BIT(ETHx->DMACH0DPCNT, ETH_DMACH0DPCNT_DPC));
}

/**
*\*\name    ETH_GetDMACh0ERICounter.
*\*\fun     Get the number of counts for the number of times an ERI (Early Receive
*\*\        Interrupt) is valid.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  Counter value: 0~0xFFF.
**/
uint16_t ETH_GetDMACh0ERICounter(ETH_Module* ETHx)
{
    /* Return the value of the ERI Counter */
    return ((uint16_t)READ_BIT(ETHx->DMACH0RXERICNT, ETH_DMACH0RXERICNT_ECNT));
}



/**
*\*\name    ETH_RxDescAssignMemory.
*\*\fun     Assign memory buffers to a DMA Rx descriptor.
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\param   Index :
*\*\          - Index of the DMA Rx descriptor.
*\*\param   pBuffer1 :
*\*\          - Points to Buffer1 address.
*\*\param   pBuffer2 :
*\*\          - Points to Buffer2 address, if available.
*\*\return  One of EthFuncStatusType.
**/
EthFuncStatusType ETH_RxDescAssignMemory(ETH_InfoType* pInfo, uint32_t Index, uint8_t* pBuffer1, uint8_t* pBuffer2)
{
    ETH_DMADescType* pRxDescriptor = NULL;
    /* Get the descriptor address */
    pRxDescriptor = (ETH_DMADescType*)pInfo->RxDescList.RxDesc[Index];

    /* Check the parameter */
    if ((pBuffer1 == NULL) || (Index >= ETH_RX_DESC_NUMBER))
    {
        /* Return ERROR */
        return ETH_ERROR_PARAM;
    }
    
    /* Write buffer1 address to RDES0 */
    pRxDescriptor->DESC0 = (uint32_t)pBuffer1;
    /* Backup buffer1 address */
    pRxDescriptor->Buf1Addr = (uint32_t)pBuffer1;
    /* Set buffer1 address valid bit to RDES3 */
    SET_BIT(pRxDescriptor->DESC3, ETH_DMARXND3RF_BUF1V);

    if (pBuffer2 != NULL)
    {
        /* Write buffer2 address to RDES2 */
        pRxDescriptor->DESC2 = (uint32_t)pBuffer2;
        /* Backup buffer2 address */
        pRxDescriptor->Buf2Addr = (uint32_t)pBuffer2;
        /* Set buffer2 address valid bit to RDES3 */
        SET_BIT(pRxDescriptor->DESC3, ETH_DMARXND3RF_BUF2V);
    }
    
    /* Set OWN bit to RDES3 */
    SET_BIT(pRxDescriptor->DESC3, ETH_DMARXND3RF_OWN);

    /* Return SUCCESS */
    return ETH_SUCCESS;
}

/**
*\*\name    ETH_BuildRxDescriptors.
*\*\fun     This function gives back Rx Desc of the last received Packet to the DMA,
*\*\        so ETH DMA will be able to use these descriptors to receive next Packets.
*\*\        It should be called after processing the received Packet.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\return  One of EthFuncStatusType.
**/
EthFuncStatusType ETH_BuildRxDescriptors(ETH_Module* ETHx, ETH_InfoType* pInfo)
{
    uint32_t TempIndex;
    uint32_t DescIndex;
    uint32_t TotalAppDescNbr;
    ETH_DMADescType* pRxDescriptor = NULL;
    ETH_RxDescListType* pRxDescList = NULL;

    pRxDescList     = &pInfo->RxDescList;
    DescIndex       = pRxDescList->FirstAppDesc;
    TotalAppDescNbr = pRxDescList->AppDescNbr;
    pRxDescriptor   = (ETH_DMADescType*)pRxDescList->RxDesc[DescIndex];

    if (pRxDescList->AppDescNbr == 0U)
    {
        /* No Rx descriptors to build */
        return NO_DESC_TO_BUILD;
    }

    if (pRxDescList->AppContextDesc != 0U)
    {
        /* A context descriptor is available */
        TotalAppDescNbr += 1U;
    }

    for (TempIndex = 0; TempIndex < TotalAppDescNbr; TempIndex++)
    {
        /* Set Buffer1 address */
        WRITE_REG(pRxDescriptor->DESC0, pRxDescriptor->Buf1Addr);
        /* Set Buffer1 valid bit */
        SET_BIT(pRxDescriptor->DESC3, ETH_DMARXND3RF_BUF1V);

        /* Check if Buffer2 is valid */
        if (pRxDescriptor->Buf2Addr != 0U)
        {
            /* Set Buffer2 address */
            WRITE_REG(pRxDescriptor->DESC2, pRxDescriptor->Buf2Addr);
            /* Set Buffer2 valid bit */
            SET_BIT(pRxDescriptor->DESC3, ETH_DMARXND3RF_BUF2V);
        }
        
        /* Set OWN bit */
        SET_BIT(pRxDescriptor->DESC3, ETH_DMARXND3RF_OWN);

        /* Check if interrupt mode */
        if (pRxDescList->ItMode != 0U)
        {
            /* Set IOC bit */
            SET_BIT(pRxDescriptor->DESC3, ETH_DMARXND3RF_IOC);
        }

        if (TempIndex < (pRxDescList->AppDescNbr - 1U))
        {
            /* Increment current rx descriptor index */
            __ETH_RXDESC_INDEX_INCR(DescIndex, 1U);
            /* Get current descriptor address */
            pRxDescriptor = (ETH_DMADescType*)pRxDescList->RxDesc[DescIndex];
        }
    }

    /* Set the Tail pointer address to the last rx descriptor hold by the app */
    WRITE_REG(ETHx->DMACH0RXDTP, (uint32_t)pRxDescriptor);

    /* Reset the Application desc number */
    pRxDescList->AppDescNbr = 0U;

    /* Return SUCCESS */
    return ETH_SUCCESS;
}

/**
*\*\name    ETH_PrepareTxDescriptors.
*\*\fun     Prepare Tx DMA descriptor before transmission.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\param   pTxPacket :
*\*\          - Points to the TX packet, containing some configuration information
*\*\param   ItMode :
*\*\          - Mode Selection: 1 indicates to interrupt mode, 0 indicates to polling mode.
*\*\return  One of EthFuncStatusType.
**/
EthFuncStatusType ETH_PrepareTxDescriptors(ETH_Module* ETHx, ETH_InfoType* pInfo, ETH_TxPacketType* pTxPacket, uint32_t ItMode)
{
    uint32_t TempIndex;
    uint32_t DescIndex;
    uint32_t DescCnt = 0;
    uint32_t FirstDescIndex;
    ETH_BufferType* pTxBuf = NULL;
    ETH_DMADescType* pTxDescriptor = NULL;
    ETH_TxDescListType* pTxDescList = NULL;

    pTxDescList    = &pInfo->TxDescList;
    pTxBuf         = pTxPacket->pTxBuffer;
    DescIndex      = pTxDescList->CurTxDesc;
    FirstDescIndex = pTxDescList->CurTxDesc;
    pTxDescriptor  = (ETH_DMADescType*)(pTxDescList->TxDesc[DescIndex]);

    /* Check if the current TX descriptor is owned by the application */
    if ((pTxDescriptor->DESC3 & ETH_DMATXND3RF_OWN) == ETH_DMATXND3RF_OWN)
    {
        /* Returns directly when the current TX descriptor is owned by the DMA */
        return DESC_OWNED_BY_DMA;
    }

    /* Starting to configure TX context descriptors */
    /* If VLAN tag is enabled for this packet */
    if ((pTxPacket->Attributes & ETH_TX_PACKETS_FEATURES_VLANTAG) != (uint32_t)RESET)
    {
        // N32H487 does not support VLAN insertion or replacemen

        /* If inner VLAN is enabled for this packet */
        if ((pTxPacket->Attributes & ETH_TX_PACKETS_FEATURES_INNERVLANTAG) != (uint32_t)RESET)
        {
            // N32H487 does not support double VLAN processing
        }
    }

    /* If tcp segementation is enabled for this packet */
    if ((pTxPacket->Attributes & ETH_TX_PACKETS_FEATURES_TSO) != (uint32_t)RESET)
    {
        // N32H487 does not support TCP segementation
    }
    
    /* If One-Step Timestamp Correction is enabled for this packet */
    if ((pTxPacket->Attributes & ETH_TX_PACKETS_FEATURES_OSTC) != (uint32_t)RESET)
    {
        /* Set One-Step Timestamp Correction Enable bit */
        SET_BIT(pTxDescriptor->DESC3, ETH_DMATXCD3_OSTC);
        /* Set One-Step Timestamp Correction Input Valid bit */
        SET_BIT(pTxDescriptor->DESC3, ETH_DMATXCD3_TCMSSV);
    }
    
    if(((pTxPacket->Attributes & ETH_TX_PACKETS_FEATURES_VLANTAG)  != (uint32_t)RESET)
        || ((pTxPacket->Attributes & ETH_TX_PACKETS_FEATURES_TSO)  != (uint32_t)RESET)
        || ((pTxPacket->Attributes & ETH_TX_PACKETS_FEATURES_OSTC) != (uint32_t)RESET))
    {
        /* Set as context descriptor */
        SET_BIT(pTxDescriptor->DESC3, ETH_DMATXCD3_CTXT);
        /* Set own bit */
        SET_BIT(pTxDescriptor->DESC3, ETH_DMATXCD3_OWN);
        /* Increment current tx descriptor index */
        __ETH_TXDESC_INDEX_INCR(DescIndex, 1U);
        /* Get current descriptor address */
        pTxDescriptor = (ETH_DMADescType*)(pTxDescList->TxDesc[DescIndex]);

        /* Incremental Descriptor Count */
        DescCnt += 1U;

        /* Check if the current TX descriptor is owned by the application */
        if ((pTxDescriptor->DESC3 & ETH_DMATXCD3_OWN) == ETH_DMATXCD3_OWN)
        {
            /* Get the first TX descriptor address */
            pTxDescriptor = (ETH_DMADescType*)(pTxDescList->TxDesc[FirstDescIndex]);
            /* Clear the OWN bit of first Descriptor */
            CLEAR_BIT(pTxDescriptor->DESC3, ETH_DMATXCD3_OWN);
            /* Returns directly when the current TX descriptor is owned by the DMA */
            return DESC_OWNED_BY_DMA;
        }
    }
    
    /* Starting to configure TX Normal descriptor */
    /* Set header or buffer 1 address */
    WRITE_REG(pTxDescriptor->DESC0, (uint32_t)pTxBuf->pBuf);
    /* Set header or buffer 1 Length */
    MODIFY_REG(pTxDescriptor->DESC2, ETH_DMATXND2RF_B1L, pTxBuf->Len);

    /* If the next buffer exists */
    if (pTxBuf->pNext != NULL)
    {
        /* Get buffer address */
        pTxBuf = pTxBuf->pNext;
        /* Set buffer 2 address */
        WRITE_REG(pTxDescriptor->DESC1, (uint32_t)pTxBuf->pBuf);
        /* Set buffer 2 Length */
        MODIFY_REG(pTxDescriptor->DESC2, ETH_DMATXND2RF_B2L, (pTxBuf->Len << 16));
    }
    else
    {
        /* Set buffer 2 address field to 0 */
        WRITE_REG(pTxDescriptor->DESC1, 0x0U);
        /* Set buffer 2 Length field to 0 */
        MODIFY_REG(pTxDescriptor->DESC2, ETH_DMATXND2RF_B2L, 0);
    }

    /* If tcp segementation is enabled for this packet */
    if ((pTxPacket->Attributes & ETH_TX_PACKETS_FEATURES_TSO) != (uint32_t)RESET)
    {
        // N32H487 does not support TCP segementation
    }
    else
    {
        /* Set Frame Length */
        MODIFY_REG(pTxDescriptor->DESC3, ETH_DMATXND3RF_FL, pTxPacket->Length);

        /* If Checksum is enabled for this packet */
        if ((pTxPacket->Attributes & ETH_TX_PACKETS_FEATURES_CSUM) != (uint32_t)RESET)
        {
            /* Set Checksum Insertion Control bits */
            MODIFY_REG(pTxDescriptor->DESC3, ETH_DMATXND3RF_CIC, pTxPacket->ChecksumCtrl);
        }
    }

    /* If CRC Pad Control is enabled for this packet */
    if ((pTxPacket->Attributes & ETH_TX_PACKETS_FEATURES_CRCPAD) != (uint32_t)RESET)
    {
        /* Set CRC Pad Control bits */
        MODIFY_REG(pTxDescriptor->DESC3, ETH_DMATXND3RF_CPC, pTxPacket->CRCPadCtrl);
    }

    /* If VLAN Tag Control is enabled for this packet */
    if ((pTxPacket->Attributes & ETH_TX_PACKETS_FEATURES_VLANTAG) != (uint32_t)RESET)
    {
        // N32H487 does not support SA and VLAN Insertion on Tx option
    }

    /* If Source Address Control is enabled for this packet */
    if ((pTxPacket->Attributes & ETH_TX_PACKETS_FEATURES_SAIC) != (uint32_t)RESET)
    {
        // N32H487 does not support SA and VLAN Insertion on Tx option
    }

    /* Set as First Descriptor */
    SET_BIT(pTxDescriptor->DESC3, ETH_DMATXND3RF_FD);
    /* Set as NORMAL descriptor */
    CLEAR_BIT(pTxDescriptor->DESC3, ETH_DMATXND3RF_CTXT);
    /* Set own bit of First descriptor */
    SET_BIT(pTxDescriptor->DESC3, ETH_DMATXND3RF_OWN);

    /* Only if the packet is splitted into more than one descriptors > 1 */
    while (pTxBuf->pNext != NULL)
    {
        /* Clear the LD bit of previous descriptor */
        CLEAR_BIT(pTxDescriptor->DESC3, ETH_DMATXND3RF_LD);

        /* Increment current tx descriptor index */
        __ETH_TXDESC_INDEX_INCR(DescIndex, 1);
        /* Get current descriptor address */
        pTxDescriptor = (ETH_DMADescType*)(pTxDescList->TxDesc[DescIndex]);

        /* Incremental Descriptor Count */
        DescCnt += 1U;

        /* Clear the FD bit of new Descriptor */
        CLEAR_BIT(pTxDescriptor->DESC3, ETH_DMATXND3RF_FD);

        /* Check if the current TX descriptor is owned by the application */
        if ((pTxDescriptor->DESC3 & ETH_DMATXND3RF_OWN) == ETH_DMATXND3RF_OWN)
        {
            DescIndex = FirstDescIndex;
            /* Get the first TX descriptor address */
            pTxDescriptor = (ETH_DMADescType*)(pTxDescList->TxDesc[DescIndex]);

            /* Clear the OWN bit of all previous descriptors */
            for (TempIndex = 0; TempIndex < DescCnt; TempIndex++)
            {
                /* Clear the OWN bit of new Descriptor */
                CLEAR_BIT(pTxDescriptor->DESC3, ETH_DMATXND3RF_OWN);
                /* Increment current tx descriptor index */
                __ETH_TXDESC_INDEX_INCR(DescIndex, 1);
                /* Get current descriptor address */
                pTxDescriptor = (ETH_DMADescType*)(pTxDescList->TxDesc[DescIndex]);
            }

            /* Returns directly when the current TX descriptor is owned by the DMA */
            return DESC_OWNED_BY_DMA;
        }

        /* Get the next Tx buffer in the list */
        pTxBuf = pTxBuf->pNext;

        /* Set header or buffer 1 address */
        WRITE_REG(pTxDescriptor->DESC0, (uint32_t)pTxBuf->pBuf);
        /* Set header or buffer 1 Length */
        MODIFY_REG(pTxDescriptor->DESC2, ETH_DMATXND2RF_B1L, pTxBuf->Len);

        /* If the next buffer exists */
        if (pTxBuf->pNext != NULL)
        {
            /* Get buffer address */
            pTxBuf = pTxBuf->pNext;
            /* Set buffer 2 address */
            WRITE_REG(pTxDescriptor->DESC1, (uint32_t)pTxBuf->pBuf);
            /* Set buffer 2 Length */
            MODIFY_REG(pTxDescriptor->DESC2, ETH_DMATXND2RF_B2L, (pTxBuf->Len << 16));
        }
        else
        {
            /* Set buffer 2 address field to 0 */
            WRITE_REG(pTxDescriptor->DESC1, 0x0U);
            /* Set buffer 2 Length field to 0 */
            MODIFY_REG(pTxDescriptor->DESC2, ETH_DMATXND2RF_B2L, 0);
        }

        /* Set Frame Length */
        MODIFY_REG(pTxDescriptor->DESC3, ETH_DMATXND3RF_FL, pTxPacket->Length);

        /* Set as NORMAL descriptor */
        CLEAR_BIT(pTxDescriptor->DESC3, ETH_DMATXND3RF_CTXT);
        /* Set own bit of this descriptor */
        SET_BIT(pTxDescriptor->DESC3, ETH_DMATXND3RF_OWN);
    }

    /*
      Note:
      The LD bit is 0 and the Early Transmit Interrupt (ETIC) is turned on,
      which controls the ETI; the LD bit is 1, which controls the Transmit
      Interrupt (TI).
      The ETI is generated after completing a data transfer from the buffer
      of the descriptor for which the IOC is set, and the TI is generated
      only after a complete packet is transferred to the TxFIFO.
    */
    if (ItMode)
    {
        /* Set Interrupt on Completion bit */
        SET_BIT(pTxDescriptor->DESC2, ETH_DMATXND2RF_IOC);
    }
    else
    {
        /* Clear Interrupt on Completion bit */
        CLEAR_BIT(pTxDescriptor->DESC2, ETH_DMATXND2RF_IOC);
    }

    /* Set as Last Descriptor */
    SET_BIT(pTxDescriptor->DESC3, ETH_DMATXND3RF_LD);

    /* Update current Tx descriptor index */
    pTxDescList->CurTxDesc = DescIndex;

    /* Return SUCCESS */
    return ETH_SUCCESS;
}

/**
*\*\name    ETH_Transmit.
*\*\fun     Send packets via polling mode.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\param   pTxPacket :
*\*\          - Points to the TX packet, containing some configuration information
*\*\param   Timeout :
*\*\          - timeout value
*\*\return  One of EthFuncStatusType.
**/
EthFuncStatusType ETH_Transmit(ETH_Module* ETHx, ETH_InfoType* pInfo, ETH_TxPacketType* pTxPacket, uint32_t Timeout)
{
    uint32_t TickStart;
    EthFuncStatusType TempStatus;
    const ETH_DMADescType* pTxDescriptor;

    /* Check the pTxPacket parameter */
    if (pTxPacket == NULL)
    {
        /* Return ERROR */
        return ETH_ERROR_PARAM;
    }

    /* Config DMA Tx descriptor by Tx Packet info */
    TempStatus = ETH_PrepareTxDescriptors(ETHx, pInfo, pTxPacket, 0);

    /* Check if it has been successfully configured */
    if (TempStatus != ETH_SUCCESS)
    {
        /* Return ERROR */
        return TempStatus;
    }

    /* Get the descriptor address */
    pTxDescriptor = (ETH_DMADescType*)(&pInfo->TxDescList)->TxDesc[pInfo->TxDescList.CurTxDesc];
    /* Increment current tx descriptor index */
    __ETH_TXDESC_INDEX_INCR(pInfo->TxDescList.CurTxDesc, 1U);
    /* Send a polling command to the TX DMA by writing the address of the next idle
    descriptor to the ETH_DMACH0TXDTP register, and then start the transfer */
    WRITE_REG(ETHx->DMACH0TXDTP, (uint32_t)pInfo->TxDescList.TxDesc[pInfo->TxDescList.CurTxDesc]);

    /* Check that DWT is enabled or not */
    if ((DEM_CR & DEM_CR_TRCENA) == (uint32_t)RESET)
    {
        /* Enable and initialize DWT */
        __ETH_TICK_START();
    }

    /* Get tick */
    TickStart = __ETH_GET_TICK;

    /* Wait for data to be transmitted or timeout occured */
    while ((pTxDescriptor->DESC3 & ETH_DMATXND3WBF_OWN) != (uint32_t)RESET)
    {
        /* Check for fatal bus error */
        if ((ETHx->DMACH0STS & ETH_DMACH0STS_FBE) != (uint32_t)RESET)
        {
            /* Return ERROR */
            return FATAL_BUS_ERROR;
        }

        /* Check for the Timeout */
        if (((__ETH_GET_TICK - TickStart) > Timeout) || (Timeout == 0U))
        {
            /* Disable tick */
            __ETH_TICK_STOP();

            /* Return timeout */
            return ETH_ERROR_TIMEOUT;
        }
    }

    /* Disable tick */
    __ETH_TICK_STOP();

    /* Return SUCCESS */
    return ETH_SUCCESS;
}

/**
*\*\name    ETH_TransmitIT.
*\*\fun     Send packets via interrupt mode.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\param   pTxPacket :
*\*\          - Points to the TX packet, containing some configuration information
*\*\return  One of EthFuncStatusType.
**/
EthFuncStatusType ETH_TransmitIT(ETH_Module* ETHx, ETH_InfoType* pInfo, ETH_TxPacketType* pTxPacket)
{
    EthFuncStatusType TempStatus;

    /* Check the pTxPacket parameter */
    if (pTxPacket == NULL)
    {
        /* Return ERROR */
        return ETH_ERROR_PARAM;
    }

    /* Config DMA Tx descriptor by Tx Packet info */
    TempStatus = ETH_PrepareTxDescriptors(ETHx, pInfo, pTxPacket, 1);

    /* Check if it has been successfully configured */
    if (TempStatus != ETH_SUCCESS)
    {
        /* Return ERROR */
        return TempStatus;
    }

    /* Increment current tx descriptor index */
    __ETH_TXDESC_INDEX_INCR(pInfo->TxDescList.CurTxDesc, 1U);
    /* Send a polling command to the TX DMA by writing the address of the next idle
    descriptor to the ETH_DMACH0TXDTP register, and then start the transfer */
    WRITE_REG(ETHx->DMACH0TXDTP, (uint32_t)pInfo->TxDescList.TxDesc[pInfo->TxDescList.CurTxDesc]);

    /* Return SUCCESS */
    return ETH_SUCCESS;
}

/**
*\*\name    ETH_IsRxDataAvailable.
*\*\fun     Checks the data of received packets.
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\return  1 or 0.
**/
uint8_t ETH_IsRxDataAvailable(ETH_InfoType* pInfo)
{
    uint32_t DescIndex;
    uint32_t DescCnt = 0;
    uint32_t AppDescCnt = 0;
    uint32_t AppFirstDescIndex = 0;
    ETH_DMADescType* pRxDescriptor = NULL;
    ETH_RxDescListType* pRxDescList = NULL;

    pRxDescList   = &pInfo->RxDescList;
    DescIndex     = pRxDescList->CurRxDesc;
    pRxDescriptor = (ETH_DMADescType*)pRxDescList->RxDesc[DescIndex];

    /* Check the number of descriptors */
    if (pRxDescList->AppDescNbr != 0)
    {
        /* Data already received by not yet processed */
        return 0;
    }

    /* Check if descriptor is not owned by DMA */
    while (((pRxDescriptor->DESC3 & ETH_DMARXND3WBF_OWN) == (uint32_t)RESET) && (DescCnt < ETH_RX_DESC_NUMBER))
    {
        /* Incremental Descriptor Count */
        DescCnt += 1U;

        /* Check if last descriptor */
        if ((pRxDescriptor->DESC3 & ETH_DMARXND3WBF_LD) != (uint32_t)RESET)
        {
            /* Increment the number of descriptors to be passed to the application */
            AppDescCnt += 1U;
            
            /* If the first descriptor */
            if (AppDescCnt == 1U)
            {
                /* Record the index corresponding to the first descriptor */
                AppFirstDescIndex = DescIndex;
            }
            
            /* Increment current rx descriptor index */
            __ETH_RXDESC_INDEX_INCR(DescIndex, 1U);
            /* Get current descriptor address */
            pRxDescriptor = (ETH_DMADescType*)pRxDescList->RxDesc[DescIndex];

            /* Check if descriptor is not owned by DMA */
            if ((pRxDescriptor->DESC3 & ETH_DMARXND3WBF_OWN) == (uint32_t)RESET)
            {
                /* Check for Context descriptor */
                if ((pRxDescriptor->DESC3 & ETH_DMARXND3WBF_CTXT) != (uint32_t)RESET)
                {
                    /* Indicated as a context descriptor */
                    pRxDescList->AppContextDesc = 1;
                    /* Increment current rx descriptor index */
                    __ETH_RXDESC_INDEX_INCR(DescIndex, 1U);
                }
            }
            /* Saves the current descriptor index */
            pRxDescList->CurRxDesc = DescIndex;
            /* Saves the first descriptor subscript */
            pRxDescList->FirstAppDesc = AppFirstDescIndex;
            /* Saves the number of descriptors */
            pRxDescList->AppDescNbr = AppDescCnt;

            /* Packets received, return 1 */
            return 1;
        }
        /* Check if first descriptor */
        else if ((pRxDescriptor->DESC3 & ETH_DMARXND3WBF_FD) != (uint32_t)RESET)
        {
            /* Record the index corresponding to the first descriptor */
            AppFirstDescIndex = DescIndex;
            /* Increment the number of descriptors to be passed to the application */
            AppDescCnt = 1U;

            /* Increment current rx descriptor index */
            __ETH_RXDESC_INDEX_INCR(DescIndex, 1U);
            /* Get current descriptor address */
            pRxDescriptor = (ETH_DMADescType*)pRxDescList->RxDesc[DescIndex];
        }
        /* It should be an intermediate descriptor */
        else
        {
            /* Increment the number of descriptors to be passed to the application */
            AppDescCnt += 1U;

            /* Increment current rx descriptor index */
            __ETH_RXDESC_INDEX_INCR(DescIndex, 1U);
            /* Get current descriptor address */
            pRxDescriptor = (ETH_DMADescType*)pRxDescList->RxDesc[DescIndex];
        }
    }

    /* Build Descriptors if an incomplete Packet is received */
    if (AppDescCnt > 0U)
    {
        /* Get the first descriptor */
        DescIndex = AppFirstDescIndex;
        /* Get current descriptor address */
        pRxDescriptor = (ETH_DMADescType*)pRxDescList->RxDesc[DescIndex];

        for (DescCnt = 0; DescCnt < AppDescCnt; DescCnt++)
        {
            /* Write buffer1 address to RDES0 */
            pRxDescriptor->DESC0 = pRxDescriptor->Buf1Addr;
            /* Set buffer1 address valid bit to RDES3 */
            SET_BIT(pRxDescriptor->DESC3, ETH_DMARXND3RF_BUF1V);

            if (pRxDescriptor->Buf2Addr != (uint32_t)RESET)
            {
                /* Write buffer2 address to RDES2 */
                pRxDescriptor->DESC2 = pRxDescriptor->Buf2Addr;
                /* Set buffer2 address valid bit to RDES3 */
                SET_BIT(pRxDescriptor->DESC3, ETH_DMARXND3RF_BUF2V);
            }

            /* Set OWN bit */
            SET_BIT(pRxDescriptor->DESC3, ETH_DMARXND3RF_OWN);

            if (pRxDescList->ItMode != (uint32_t)RESET)
            {
                /* Set IOC bit */
                SET_BIT(pRxDescriptor->DESC3, ETH_DMARXND3RF_IOC);
            }

            /* Increment current rx descriptor index */
            __ETH_RXDESC_INDEX_INCR(DescIndex, 1U);
            /* Get current descriptor address */
            pRxDescriptor = (ETH_DMADescType*)pRxDescList->RxDesc[DescIndex];
        }
    }

    /* No received Packet */
    pRxDescList->AppDescNbr = 0U;

    /* No received Packet, return 0 */
    return 0;
}

/**
*\*\name    ETH_GetRxDataBuffer.
*\*\fun     Used to fetch the data buffer when processing the received Packet.
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\param   pRxBuffer :
*\*\          - Points to the RX buffer, ETH_BufferType structure.
*\*\return  One of EthFuncStatusType.
**/
EthFuncStatusType ETH_GetRxDataBuffer(ETH_InfoType* pInfo, ETH_BufferType* pRxBuffer)
{
    uint32_t TempIndex;
    uint32_t DescIndex;
    uint32_t LastDescLen;
    uint32_t AccumulatedLen = 0;

    ETH_BufferType* pRxBuf = NULL;
    ETH_DMADescType* pRxDescriptor = NULL;
    ETH_RxDescListType* pRxDescList = NULL;

    pRxBuf        = pRxBuffer;
    pRxDescList   = &pInfo->RxDescList;
    DescIndex     = pRxDescList->FirstAppDesc;
    pRxDescriptor = (ETH_DMADescType*)pRxDescList->RxDesc[DescIndex];

    /* Check the pRxBuffer parameter */
    if (pRxBuf == NULL)
    {
        /* Return ERROR */
        return ETH_ERROR_PARAM;
    }

    if (pRxDescList->AppDescNbr == 0U)
    {
        /* Check for data received */
        if (ETH_IsRxDataAvailable(pInfo) == 0U)
        {
            /* No data to be transferred to the application */
            return NO_DATA_TRANSFER;
        }
        else
        {
            /* Update the current descriptor index */
            DescIndex = pRxDescList->FirstAppDesc;
            /* Get current descriptor address */
            pRxDescriptor = (ETH_DMADescType*)pRxDescList->RxDesc[DescIndex];
        }
    }
    
    /* Get intermediate descriptors buffers: in case of the Packet is splitted into multi descriptors */
    for (TempIndex = 0; TempIndex < (pRxDescList->AppDescNbr - 1); TempIndex++)
    {
        /* Get Address of the first buffer address */
        pRxBuf->pBuf = (uint8_t*)pRxDescriptor->Buf1Addr;
        /* Get length of the first buffer address */
        pRxBuf->Len = pInfo->RxBuffLen;

        /* Check if the second buffer address of this descriptor is valid */
        if (pRxDescriptor->Buf2Addr != 0U)
        {
            /* Point to next buffer */
            pRxBuf = pRxBuf->pNext;
            /* Get Address of the second buffer address */
            pRxBuf->pBuf = (uint8_t*)pRxDescriptor->Buf2Addr;
            /* Get length of the second buffer address */
            pRxBuf->Len = pInfo->RxBuffLen;
        }

        /* Get accumulated length until this descriptor */
        AccumulatedLen = READ_BIT(pRxDescriptor->DESC3, ETH_DMARXND3WBF_PL);

        /* Increment current rx descriptor index */
        __ETH_RXDESC_INDEX_INCR(DescIndex, 1U);
        /* Get current descriptor address */
        pRxDescriptor = (ETH_DMADescType*)pRxDescList->RxDesc[DescIndex];

        /* Point to next buffer */
        pRxBuf = pRxBuf->pNext;
    }

    /* Get last descriptor data length */
    LastDescLen = READ_BIT(pRxDescriptor->DESC3, ETH_DMARXND3WBF_PL) - AccumulatedLen;
    
    /* Get Address of the first buffer address */
    pRxBuf->pBuf = (uint8_t*)pRxDescriptor->Buf1Addr;

    /* Data is in only one buffer */
    if (LastDescLen <= pInfo->RxBuffLen)
    {
        /* Record buffer length */
        pRxBuf->Len = LastDescLen;
    }
    /* Data is in two buffers */
    else if (pRxDescriptor->Buf2Addr != 0U)
    {
        /* Get the Length of the first buffer address */
        pRxBuf->Len = pInfo->RxBuffLen;
        /* Point to next buffer */
        pRxBuf = pRxBuf->pNext;
        /* Get the Address of the second buffer address */
        pRxBuf->pBuf = (uint8_t*)pRxDescriptor->Buf2Addr;
        /* Get the Length of the second buffer address */
        pRxBuf->Len = LastDescLen - (pInfo->RxBuffLen);
    }
    else
    {
        /* Return ERROR */
        return ETH_ERROR_PARAM;
    }

    /* Return SUCCESS */
    return ETH_SUCCESS;
}

/**
*\*\name    ETH_GetRxDataLength.
*\*\fun     Used to fetch the data length of last received Packet when processing the
*\*\        received Packet.
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\return  NO_DATA_TRANSFER or length of last received Packet.
**/
uint32_t ETH_GetRxDataLength(ETH_InfoType* pInfo)
{
    uint32_t DescIndex;
    ETH_DMADescType* pRxDescriptor  = NULL;
    ETH_RxDescListType* pRxDescList = NULL;

    pRxDescList   = &pInfo->RxDescList;
    DescIndex     = pRxDescList->FirstAppDesc;

    if (pRxDescList->AppDescNbr == 0U)
    {
        /* Check for data received */
        if (ETH_IsRxDataAvailable(pInfo) == 0U)
        {
            /* No data to be transferred to the application */
            return (uint32_t)NO_DATA_TRANSFER;
        }
    }

    /* Get index of last descriptor */
    __ETH_RXDESC_INDEX_INCR(DescIndex, (pRxDescList->AppDescNbr - 1U));
    /* Point to last descriptor */
    pRxDescriptor = (ETH_DMADescType*)pRxDescList->RxDesc[DescIndex];

    /* Return the length of last received Packet */
    return READ_BIT(pRxDescriptor->DESC3, ETH_DMARXND3WBF_PL);
}

/**
*\*\name    ETH_GetRxPacketInfo.
*\*\fun     Get the Rx Packet info (Packet type, VLAN tag, Filters status, ...).
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\param   pRxPacket :
*\*\          - Points to the RX packet, containing some packet information.
*\*\return  One of EthFuncStatusType.
**/
EthFuncStatusType ETH_GetRxPacketInfo(ETH_InfoType* pInfo, ETH_RxPacketType* pRxPacket)
{
    uint32_t DescIndex;
    ETH_DMADescType* pRxDescriptor = NULL;
    ETH_RxDescListType* pRxDescList = NULL;

    pRxDescList   = &pInfo->RxDescList;
    DescIndex     = pRxDescList->FirstAppDesc;

    if (pRxDescList->AppDescNbr == 0U)
    {
        /* Check for data received */
        if (ETH_IsRxDataAvailable(pInfo) == 0U)
        {
            /* No data to be transferred to the application */
            return NO_DATA_TRANSFER;
        }
    }

    /* Get index of last descriptor */
    __ETH_RXDESC_INDEX_INCR(DescIndex, (pRxDescList->AppDescNbr - 1U));
    /* Point to last descriptor */
    pRxDescriptor = (ETH_DMADescType*)pRxDescList->RxDesc[DescIndex];

    if ((pRxDescriptor->DESC3 & ETH_DMARXND3WBF_ES) != (uint32_t)RESET)
    {
        /* Get packet error status from RDES3 */
        pRxPacket->ErrorCode = READ_BIT(pRxDescriptor->DESC3, (ETH_DMARXND3WBF_DE
                                                             | ETH_DMARXND3WBF_RE
                                                             | ETH_DMARXND3WBF_OE
                                                             | ETH_DMARXND3WBF_RWT
                                                             | ETH_DMARXND3WBF_GP
                                                             | ETH_DMARXND3WBF_CE)); 
    }
    else
    {
        if ((pRxDescriptor->DESC3 & ETH_DMARXND3WBF_RS0V) != (uint32_t)RESET)
        {
            /* Check for Double VLAN packet types */
            if ((pRxDescriptor->DESC3 & ETH_DMARXND3WBF_LT) == ETH_DMARXND3WBF_LT_DVLAN)
            {
                // N32H487 does not support Double VLAN Tag
            }
            else
            {
                /* Get Outer VLAN Tag */
                pRxPacket->VlanTag = READ_BIT(pRxDescriptor->DESC0, ETH_DMARXND0WBF_OVT);
            }
        }

        if ((pRxDescriptor->DESC3 & ETH_DMARXND3WBF_RS1V) != (uint32_t)RESET)
        {
            /* Get Payload type */
            pRxPacket->PayloadType = READ_BIT(pRxDescriptor->DESC1, ETH_DMARXND1WBF_PT);
            /* Get Header type */
            pRxPacket->PayloadType = READ_BIT(pRxDescriptor->DESC1, (ETH_DMARXND1WBF_IPV4
                                                                   | ETH_DMARXND1WBF_IPV6));
            /* Get Checksum status */
            pRxPacket->PayloadType = READ_BIT(pRxDescriptor->DESC1, (ETH_DMARXND1WBF_IPHE
                                                                   | ETH_DMARXND1WBF_IPCB
                                                                   | ETH_DMARXND1WBF_IPCE));
        }

        if ((pRxDescriptor->DESC3 & ETH_DMARXND3WBF_RS2V) != (uint32_t)RESET)
        {
            /* Get MAC Filtering Status */
            pRxPacket->MACFilterStatus = READ_BIT(pRxDescriptor->DESC2, (ETH_DMARXND2WBF_VFS
                                                                       | ETH_DMARXND2WBF_SAF
                                                                       | ETH_DMARXND2WBF_DAF
                                                                       | ETH_DMARXND2WBF_HF));
        }
    }

    /* Get the Rx Descriptors count */
    pRxPacket->DescriptorCnt = pRxDescList->AppDescNbr;

    /* Return SUCCESS */
    return ETH_SUCCESS;
}

/**
*\*\name    ETH_Start.
*\*\fun     Turn on ETH via polling mode, including turning on TX and RX DMA engines,
*\*\        turning on TX and RX MAC controllers, etc.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none.
**/
void ETH_Start(ETH_Module* ETHx)
{
    /* Start the MAC Transmitter */
    SET_BIT(ETHx->MACCFG, ETH_MACCFG_TE);
    
    /* Start the MAC Receiver */
    SET_BIT(ETHx->MACCFG, ETH_MACCFG_RE);
    
    /* Set the Flush Transmit Queue bit */
    SET_BIT(ETHx->MTLTXQOPMOD, ETH_MTLTXQOPMOD_FTQ);
    
    /* Start the DMA Transmitter */
    SET_BIT(ETHx->DMACH0TXCTRL, ETH_DMACH0TXCTRL_ST);
    
    /* Start the DMA Receiver */
    SET_BIT(ETHx->DMACH0RXCTRL, ETH_DMACH0RXCTRL_SR);

    /* Clear Tx and Rx process stopped flags */
    SET_BIT(ETHx->DMACH0STS, (ETH_DMACH0STS_TPS | ETH_DMACH0STS_RPS));
}

/**
*\*\name    ETH_StartIT.
*\*\fun     Turn on ETH via interrupt mode, including turning on TX and RX DMA engines,
*\*\        turning on TX and RX MAC controllers, etc.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\return  none.
**/
void ETH_StartIT(ETH_Module* ETHx, ETH_InfoType* pInfo)
{
    uint32_t TempIndex, DescIndex = 0;
    ETH_DMADescType* pRxDescriptor = NULL;

    /* Get the descriptor address */
    pRxDescriptor = (ETH_DMADescType*)pInfo->RxDescList.RxDesc[DescIndex];

    /* Set IOC bit to all Rx descriptors */
    for (TempIndex = 0; TempIndex < ETH_RX_DESC_NUMBER; TempIndex++)
    {
        /* Set Interrupt on Completion bit */
        SET_BIT(pRxDescriptor->DESC3, ETH_DMARXND3RF_IOC);
        /* Increment rx descriptor index */
        __ETH_RXDESC_INDEX_INCR(DescIndex, 1U);
        /* Get the descriptor address */
        pRxDescriptor = (ETH_DMADescType*)pInfo->RxDescList.RxDesc[DescIndex];
    }
    
    /* Enable ETH DMA Transmit Interrupt, Receive Interrupt, Fatal Bus Error Interrupt,
    Abnormal Interrupt Summary, Normal Interrupt Summary*/
    SET_BIT(ETHx->DMACH0INTEN, (ETH_DMACH0INTEN_TIE | ETH_DMACH0INTEN_RIE
                              | ETH_DMACH0INTEN_NIE | ETH_DMACH0INTEN_AIE
                              | ETH_DMACH0INTEN_FBEE));

    /* Start the MAC Transmitter */
    SET_BIT(ETHx->MACCFG, ETH_MACCFG_TE);
    
    /* Start the MAC Receiver */
    SET_BIT(ETHx->MACCFG, ETH_MACCFG_RE);
    
    /* Set the Flush Transmit Queue bit */
    SET_BIT(ETHx->MTLTXQOPMOD, ETH_MTLTXQOPMOD_FTQ);
    
    /* Start the DMA Transmitter */
    SET_BIT(ETHx->DMACH0TXCTRL, ETH_DMACH0TXCTRL_ST);
    
    /* Start the DMA Receiver */
    SET_BIT(ETHx->DMACH0RXCTRL, ETH_DMACH0RXCTRL_SR);

    /* Clear Tx and Rx process stopped flags */
    SET_BIT(ETHx->DMACH0STS, (ETH_DMACH0STS_TPS | ETH_DMACH0STS_RPS));
    
    /* Save IT mode */
    pInfo->RxDescList.ItMode = 1U;
}

/**
*\*\name    ETH_Stop.
*\*\fun     Turn off ETH in polling mode, including turning off TX and RX DMA engines,
*\*\        turning off TX and RX MAC controllers, etc.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none.
**/
void ETH_Stop(ETH_Module* ETHx)
{
    /* Stop the DMA Transmitter */
    CLEAR_BIT(ETHx->DMACH0TXCTRL, ETH_DMACH0TXCTRL_ST);

    /* Wait for any previous frame transmissions to complete */
    while (((ETHx->MTLTXQDBG & ETH_TRCSTS_MASK) == ETH_MTLTXQSTS_READ)
        && ((ETHx->MTLTXQDBG & ETH_MTLTXQSTS_NOT_EMPTY) == ETH_MTLTXQSTS_NOT_EMPTY))
    {
    }
    
    /* Stop the MAC Transmitter */
    CLEAR_BIT(ETHx->MACCFG, ETH_MACCFG_TE);
    
    /* Stop the MAC Receiver */
    CLEAR_BIT(ETHx->MACCFG, ETH_MACCFG_RE);

    /* Wait for all data to be transferred to system memory */
    while (((ETHx->MTLRXQDBG & ETH_RXQSTS_MASK) != ETH_MTLRXQSTS_EMPTY)
        && ((ETHx->MTLRXQDBG & ETH_MTLRXQSTS_PACK_NBR) != (uint32_t)RESET))
    {
    }
    
    /* Stop the DMA Receiver */
    CLEAR_BIT(ETHx->DMACH0RXCTRL, ETH_DMACH0RXCTRL_SR);

    /* Set the Flush Transmit Queue bit */
    SET_BIT(ETHx->MTLTXQOPMOD, ETH_MTLTXQOPMOD_FTQ);
}

/**
*\*\name    ETH_StopIT.
*\*\fun     Turn off ETH in interrupt mode, including turning off TX and RX DMA engines,
*\*\        turning off TX and RX MAC controllers, etc.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   pInfo :
*\*\          - Pointer to an ETH_InfoType structure parameter containing various
*\*\            information about the operation of the ETH module.
*\*\return  none.
**/
void ETH_StopIT(ETH_Module* ETHx, ETH_InfoType* pInfo)
{
    uint32_t TempIndex, DescIndex = 0;
    ETH_DMADescType* pRxDescriptor = NULL;

    /* Get the descriptor address */
    pRxDescriptor = (ETH_DMADescType*)pInfo->RxDescList.RxDesc[DescIndex];

    /* Disable ETH DMA Transmit Interrupt, Receive Interrupt, Fatal Bus Error Interrupt,
    Abnormal Interrupt Summary, Normal Interrupt Summary*/
    CLEAR_BIT(ETHx->DMACH0INTEN, (ETH_DMACH0INTEN_TIE | ETH_DMACH0INTEN_RIE
                                | ETH_DMACH0INTEN_NIE | ETH_DMACH0INTEN_AIE
                                | ETH_DMACH0INTEN_FBEE));
    
    /* Stop the DMA Transmitter */
    CLEAR_BIT(ETHx->DMACH0TXCTRL, ETH_DMACH0TXCTRL_ST);

    /* Wait for any previous frame transmissions to complete */
    while (((ETHx->MTLTXQDBG & ETH_TRCSTS_MASK) == ETH_MTLTXQSTS_READ)
        && ((ETHx->MTLTXQDBG & ETH_MTLTXQSTS_NOT_EMPTY) == ETH_MTLTXQSTS_NOT_EMPTY))
    {
    }
    
    /* Stop the MAC Transmitter */
    CLEAR_BIT(ETHx->MACCFG, ETH_MACCFG_TE);
    
    /* Stop the MAC Receiver */
    CLEAR_BIT(ETHx->MACCFG, ETH_MACCFG_RE);

    /* Wait for all data to be transferred to system memory */
    while (((ETHx->MTLRXQDBG & ETH_RXQSTS_MASK) != ETH_MTLRXQSTS_EMPTY)
        && ((ETHx->MTLRXQDBG & ETH_MTLRXQSTS_PACK_NBR) != (uint32_t)RESET))
    {
    }
    
    /* Stop the DMA Receiver */
    CLEAR_BIT(ETHx->DMACH0RXCTRL, ETH_DMACH0RXCTRL_SR);

    /* Set the Flush Transmit Queue bit */
    SET_BIT(ETHx->MTLTXQOPMOD, ETH_MTLTXQOPMOD_FTQ);

    /* Clear IOC bit to all Rx descriptors */
    for (TempIndex = 0; TempIndex < ETH_RX_DESC_NUMBER; TempIndex++)
    {
        /* Clear Interrupt on Completion bit */
        CLEAR_BIT(pRxDescriptor->DESC3, ETH_DMARXND3RF_IOC);
        /* Increment rx descriptor index */
        __ETH_RXDESC_INDEX_INCR(DescIndex, 1U);
        /* Get the descriptor address */
        pRxDescriptor = (ETH_DMADescType*)pInfo->RxDescList.RxDesc[DescIndex];
    }
    
    /* Clear IT mode to */
    pInfo->RxDescList.ItMode = 0U;
}



/**
*\*\name    ETH_GetTxDescFlagStatus.
*\*\fun     Checks whether the specified ETH DMA Tx Descriptor status flag
*\*\        bits is set or not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Flag (The input parameters must be the following values):
*\*\          - ETH_DMATXDESC_FLAG_IHE
*\*\          - ETH_DMATXDESC_FLAG_DB
*\*\          - ETH_DMATXDESC_FLAG_UF
*\*\          - ETH_DMATXDESC_FLAG_ED
*\*\          - ETH_DMATXDESC_FLAG_CC
*\*\          - ETH_DMATXDESC_FLAG_EC
*\*\          - ETH_DMATXDESC_FLAG_LC
*\*\          - ETH_DMATXDESC_FLAG_NC
*\*\          - ETH_DMATXDESC_FLAG_LOC
*\*\          - ETH_DMATXDESC_FLAG_PCE
*\*\          - ETH_DMATXDESC_FLAG_PF
*\*\          - ETH_DMATXDESC_FLAG_JT
*\*\          - ETH_DMATXDESC_FLAG_ES
*\*\          - ETH_DMATXDESC_FLAG_TTSS
*\*\          - ETH_DMATXDESC_FLAG_DE
*\*\          - ETH_DMATXDESC_FLAG_LD
*\*\          - ETH_DMATXDESC_FLAG_FD
*\*\return  SET or RESET
**/
FlagStatus ETH_GetTxDescFlagStatus(ETH_DMADescType* pTxDescriptor, uint32_t Flag)
{
    FlagStatus TempStatus;

    /* Read the status of the corresponding flag bits */
    if(READ_BIT(pTxDescriptor->DESC3, Flag) != (uint32_t)RESET)
    {
        /* This flag is SET */
        TempStatus = SET;
    }
    else
    {
        /* This flag is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetRxDescExtendedFlagStatus.
*\*\fun     Checks whether the specified ETH DMA Rx Descriptor Extended status
*\*\        flag bits is set or not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Flag (The input parameters must be the following values):
*\*\          - ETH_DMARXDESC_EXTFLAG_PT_NONE
*\*\          - ETH_DMARXDESC_EXTFLAG_PT_NUDP
*\*\          - ETH_DMARXDESC_EXTFLAG_PT_TCP
*\*\          - ETH_DMARXDESC_EXTFLAG_PT_ICNP
*\*\          - ETH_DMARXDESC_EXTFLAG_IPHE
*\*\          - ETH_DMARXDESC_EXTFLAG_IPV4
*\*\          - ETH_DMARXDESC_EXTFLAG_IPV6
*\*\          - ETH_DMARXDESC_EXTFLAG_IPCB
*\*\          - ETH_DMARXDESC_EXTFLAG_IPCE
*\*\          - ETH_DMARXDESC_EXTFLAG_PMT_NONE
*\*\          - ETH_DMARXDESC_EXTFLAG_PMT_SYNC
*\*\          - ETH_DMARXDESC_EXTFLAG_PMT_FU
*\*\          - ETH_DMARXDESC_EXTFLAG_PMT_DREQ
*\*\          - ETH_DMARXDESC_EXTFLAG_PMT_DRESP
*\*\          - ETH_DMARXDESC_EXTFLAG_PMT_PDREQ
*\*\          - ETH_DMARXDESC_EXTFLAG_PMT_PDRESP
*\*\          - ETH_DMARXDESC_EXTFLAG_PMT_PRFU
*\*\          - ETH_DMARXDESC_EXTFLAG_PMT_ANN
*\*\          - ETH_DMARXDESC_EXTFLAG_PMT_MAN
*\*\          - ETH_DMARXDESC_EXTFLAG_PMT_SIG
*\*\          - ETH_DMARXDESC_EXTFLAG_PMT_PRT
*\*\          - ETH_DMARXDESC_EXTFLAG_PFT
*\*\          - ETH_DMARXDESC_EXTFLAG_PV
*\*\          - ETH_DMARXDESC_EXTFLAG_TSA
*\*\          - ETH_DMARXDESC_EXTFLAG_TD
*\*\return  SET or RESET
**/
FlagStatus ETH_GetRxDescExtendedFlagStatus(ETH_DMADescType* pRxDescriptor, uint32_t Flag)
{
    FlagStatus TempStatus;

    /* Read the status of the corresponding flag bits */
    if(READ_BIT(pRxDescriptor->DESC1, Flag) != (uint32_t)RESET)
    {
        /* This flag is SET */
        TempStatus = SET;
    }
    else
    {
        /* This flag is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetRxDescFilterFlagStatus.
*\*\fun     Checks whether the specified ETH DMA Rx Descriptor Filter status flag
*\*\        bits is set or not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Flag (The input parameters must be the following values):
*\*\          - ETH_DMARXDESC_FLTFLAG_VFS
*\*\          - ETH_DMARXDESC_FLTFLAG_SAF
*\*\          - ETH_DMARXDESC_FLTFLAG_DAF
*\*\          - ETH_DMARXDESC_FLTFLAG_HF
*\*\return  SET or RESET
**/
FlagStatus ETH_GetRxDescFilterFlagStatus(ETH_DMADescType* pRxDescriptor, uint32_t Flag)
{
    FlagStatus TempStatus;

    /* Read the status of the corresponding flag bits */
    if(READ_BIT(pRxDescriptor->DESC2, Flag) != (uint32_t)RESET)
    {
        /* This flag is SET */
        TempStatus = SET;
    }
    else
    {
        /* This flag is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetRxDescFlagStatus.
*\*\fun     Checks whether the specified ETH DMA Rx Descriptor status flag bits
*\*\        is set or not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Flag (The input parameters must be the following values):
*\*\          - ETH_DMARXDESC_FLAG_ES
*\*\          - ETH_DMARXDESC_FLAG_LT_LP
*\*\          - ETH_DMARXDESC_FLAG_LT_TP
*\*\          - ETH_DMARXDESC_FLAG_LT_ARP
*\*\          - ETH_DMARXDESC_FLAG_LT_VLAN
*\*\          - ETH_DMARXDESC_FLAG_LT_DVLAN
*\*\          - ETH_DMARXDESC_FLAG_LT_MAC
*\*\          - ETH_DMARXDESC_FLAG_LT_OAM
*\*\          - ETH_DMARXDESC_FLAG_DE
*\*\          - ETH_DMARXDESC_FLAG_RE
*\*\          - ETH_DMARXDESC_FLAG_OE
*\*\          - ETH_DMARXDESC_FLAG_RWT
*\*\          - ETH_DMARXDESC_FLAG_GP
*\*\          - ETH_DMARXDESC_FLAG_CE
*\*\          - ETH_DMARXDESC_FLAG_RS0V
*\*\          - ETH_DMARXDESC_FLAG_RS1V
*\*\          - ETH_DMARXDESC_FLAG_RS2V
*\*\          - ETH_DMARXDESC_FLAG_LD
*\*\          - ETH_DMARXDESC_FLAG_FD
*\*\return  SET or RESET
**/
FlagStatus ETH_GetRxDescFlagStatus(ETH_DMADescType* pRxDescriptor, uint32_t Flag)
{
    FlagStatus TempStatus;

    /* Read the status of the corresponding flag bits */
    if(READ_BIT(pRxDescriptor->DESC3, Flag) != (uint32_t)RESET)
    {
        /* This flag is SET */
        TempStatus = SET;
    }
    else
    {
        /* This flag is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetFlowControlBusyStatus.
*\*\fun     Checks whether the ETH flow control busy bit is set or not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  SET or RESET
*\*\note    The Flow Control register should not be written to until this bit
*\*\        is cleared.
**/
FlagStatus ETH_GetFlowControlBusyStatus(ETH_Module* ETHx)
{
    FlagStatus TempStatus;

    /* Read the status of the FCB bit */
    if(READ_BIT(ETHx->MACTXFLWCTRL, ETH_MACTXFLWCTRL_FCB) != (uint32_t)RESET)
    {
        /* This flag is SET */
        TempStatus = SET;
    }
    else
    {
        /* This flag is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetMACInterruptStatus.
*\*\fun     Checks whether the specified ETH MAC Interrupt flag is set or
*\*\        not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   IntFlag (The input parameters must be the following values):
*\*\          - ETH_MAC_INT_FLAG_PHY
*\*\          - ETH_MAC_INT_FLAG_PMT
*\*\          - ETH_MAC_INT_FLAG_MMCRX
*\*\          - ETH_MAC_INT_FLAG_MMCTX
*\*\          - ETH_MAC_INT_FLAG_TS
*\*\          - ETH_MAC_INT_FLAG_TX
*\*\          - ETH_MAC_INT_FLAG_RX
*\*\          - ETH_MAC_INT_FLAG_MDIO
*\*\return  SET or RESET
**/
INTStatus ETH_GetMACInterruptStatus(ETH_Module* ETHx, uint32_t IntFlag)
{
    INTStatus TempStatus;

    /* Read the status of the corresponding INT bits */
    if(READ_BIT(ETHx->MACINTSTS, IntFlag) != (uint32_t)RESET)
    {
        /* This Interrupt is SET */
        TempStatus = SET;
    }
    else
    {
        /* This Interrupt is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetMACTxRxFlagStatus.
*\*\fun     Checks whether the specified ETH MAC transmit-receive status
*\*\        flag bits is set or not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Flag (The input parameters must be the following values):
*\*\          - ETH_MACTX_FLAG_TJT
*\*\          - ETH_MACTX_FLAG_NCARR
*\*\          - ETH_MACTX_FLAG_LCARR
*\*\          - ETH_MACTX_FLAG_EXDEF
*\*\          - ETH_MACTX_FLAG_LCOL
*\*\          - ETH_MACTX_FLAG_EXCOL
*\*\          - ETH_MACRX_FLAG_RWT
*\*\return  SET or RESET
**/
FlagStatus ETH_GetMACTxRxFlagStatus(ETH_Module* ETHx, uint32_t Flag)
{
    FlagStatus TempStatus;

    /* Read the status of the corresponding flag bits */
    if(READ_BIT(ETHx->MACRXTXSTS, Flag) != (uint32_t)RESET)
    {
        /* This flag is SET */
        TempStatus = SET;
    }
    else
    {
        /* This flag is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetPMTFlagStatus.
*\*\fun     Checks whether the specified ETH PMT status flag bits is set or
*\*\        not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Flag (The input parameters must be the following values):
*\*\          - ETH_PMT_FLAG_WUPFRPR
*\*\          - ETH_PMT_FLAG_WUPR
*\*\          - ETH_PMT_FLAG_MPR
*\*\return  SET or RESET
**/
FlagStatus ETH_GetPMTFlagStatus(ETH_Module* ETHx, uint32_t Flag)
{
    FlagStatus TempStatus;

    /* Read the status of the corresponding flag bits */
    if(READ_BIT(ETHx->MACPMTCTRLSTS, Flag) != (uint32_t)RESET)
    {
        /* This flag is SET */
        TempStatus = SET;
    }
    else
    {
        /* This flag is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetMMCRxInterruptStatus.
*\*\fun     Checks whether the specified ETH MMC RX Interrupt flag is set or
*\*\        not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   IntFlag (The input parameters must be the following values):
*\*\          - ETH_MMCRX_INT_FLAG_BCGPIS
*\*\          - ETH_MMCRX_INT_FLAG_MCGPIS
*\*\          - ETH_MMCRX_INT_FLAG_CRCERPIS
*\*\          - ETH_MMCRX_INT_FLAG_ALGNERPIS
*\*\          - ETH_MMCRX_INT_FLAG_UCGPIS
*\*\return  SET or RESET
**/
INTStatus ETH_GetMMCRxInterruptStatus(ETH_Module* ETHx, uint32_t IntFlag)
{
    INTStatus TempStatus;

    /* Read the status of the corresponding INT bits */
    if(READ_BIT(ETHx->MMCRXINT, IntFlag) != (uint32_t)RESET)
    {
        /* This Interrupt is SET */
        TempStatus = SET;
    }
    else
    {
        /* This Interrupt is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetMMCTxInterruptStatus.
*\*\fun     Checks whether the specified ETH MMC TX Interrupt flag is set or
*\*\        not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   IntFlag (The input parameters must be the following values):
*\*\          - ETH_MMCTX_INT_FLAG_SCOLGPIS
*\*\          - ETH_MMCTX_INT_FLAG_MCOLGPIS
*\*\          - ETH_MMCTX_INT_FLAG_GPKTIS
*\*\return  SET or RESET
**/
INTStatus ETH_GetMMCTxInterruptStatus(ETH_Module* ETHx, uint32_t IntFlag)
{
    INTStatus TempStatus;

    /* Read the status of the corresponding INT bits */
    if(READ_BIT(ETHx->MMCTXINT, IntFlag) != (uint32_t)RESET)
    {
        /* This Interrupt is SET */
        TempStatus = SET;
    }
    else
    {
        /* This Interrupt is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetMACTimeStampFlagStatus.
*\*\fun     Checks whether the specified ETH MAC Time Stamp flag is set or
*\*\        not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Flag (The input parameters must be the following values):
*\*\          - ETH_MACTS_FLAG_SOVF
*\*\          - ETH_MACTS_FLAG_TARGT0
*\*\          - ETH_MACTS_FLAG_TRGTERR0
*\*\          - ETH_MACTS_FLAG_TXTSSIS
*\*\return  SET or RESET
**/
FlagStatus ETH_GetMACTimeStampFlagStatus(ETH_Module* ETHx, uint32_t Flag)
{
    FlagStatus TempStatus;

    /* Read the status of the corresponding flag bits */
    if(READ_BIT(ETHx->MACTSSTS, Flag) != (uint32_t)RESET)
    {
        /* This flag is SET */
        TempStatus = SET;
    }
    else
    {
        /* This flag is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetFlushTransmitQueueStatus.
*\*\fun     Checks whether the ETH Flush Transmit Queue bit is cleared or not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  SET or RESET
*\*\note    The MTL Transmit Queue Operation Mode Register (ETH_MTLTXQOPMOD)
*\*\        should not be written until the Flush Transmit Queue bit is reset.
**/
FlagStatus ETH_GetFlushTransmitQueueStatus(ETH_Module* ETHx)
{
    FlagStatus TempStatus;

    /* Read the status of the Flush Transmit Queue */
    if(READ_BIT(ETHx->MTLTXQOPMOD, ETH_MTLTXQOPMOD_FTQ) != (uint32_t)RESET)
    {
        /* This flag is SET */
        TempStatus = SET;
    }
    else
    {
        /* This flag is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetMTLInterruptStatus.
*\*\fun     Checks whether the specified ETH MTL Interrupt flag is set or not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   IntFlag (The input parameters must be the following values):
*\*\          - ETH_MTL_INT_FLAG_Q0IS
*\*\return  SET or RESET
**/
INTStatus ETH_GetMTLInterruptStatus(ETH_Module* ETHx, uint32_t IntFlag)
{
    INTStatus TempStatus;

    /* Read the status of the corresponding INT bits */
    if(READ_BIT(ETHx->MTLINTSTS, IntFlag) != (uint32_t)RESET)
    {
        /* This Interrupt is SET */
        TempStatus = SET;
    }
    else
    {
        /* This Interrupt is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetMTLQueueInterruptStatus.
*\*\fun     Checks whether the specified ETH MTL queue Interrupt flag is set or
*\*\        not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   IntFlag (The input parameters must be the following values):
*\*\          - ETH_MTLTXQUEUE_INT_FLAG_UNFIS
*\*\          - ETH_MTLRXQUEUE_INT_FLAG_OVFIS
*\*\return  SET or RESET
**/
INTStatus ETH_GetMTLQueueInterruptStatus(ETH_Module* ETHx, uint32_t IntFlag)
{
    INTStatus TempStatus;

    /* Read the status of the corresponding INT bits */
    if(READ_BIT(ETHx->MTLQINTCTRLSTS, IntFlag) != (uint32_t)RESET)
    {
        /* This Interrupt is SET */
        TempStatus = SET;
    }
    else
    {
        /* This Interrupt is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetMTLCounterFlagStatus.
*\*\fun     Checks whether the specified ETH MTL Counter flag is set or not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Flag (The input parameters must be the following values):
*\*\          - ETH_MTLCOUNTER_FLAG_UFCNTOVF
*\*\          - ETH_MTLCOUNTER_FLAG_OVFCNTOVF
*\*\          - ETH_MTLCOUNTER_FLAG_MISCNTOVF
*\*\return  SET or RESET
**/
FlagStatus ETH_GetMTLCounterFlagStatus(ETH_Module* ETHx, uint32_t Flag)
{
    FlagStatus TempStatus;

    if (Flag == ETH_MTLCOUNTER_FLAG_UFCNTOVF)
    {
        /* Read the status of the corresponding flag bits */
        if(READ_BIT(ETHx->MTLTXQUDF, Flag) != (uint32_t)RESET)
        {
            /* This flag is SET */
            TempStatus = SET;
        }
        else
        {
            /* This flag is RESET */
            TempStatus = RESET;
        }
    }
    else
    {
        /* Read the status of the corresponding flag bits */
        if(READ_BIT(ETHx->MTLRXQMPOFCNT, Flag) != (uint32_t)RESET)
        {
            /* This flag is SET */
            TempStatus = SET;
        }
        else
        {
            /* This flag is RESET */
            TempStatus = RESET;
        }
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetSoftwareResetStatus.
*\*\fun     Checks whether the ETH software reset bit (SWR) is set or not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  SET or RESET
*\*\note    1. Before reprogramming any ETH register, a value of zero should be
*\*\        read in SWR bit.
*\*\        2. The SWR bit must be read at least 4 CSR clock cycles after it is
*\*\        written to 1.
**/
FlagStatus ETH_GetSoftwareResetStatus(ETH_Module* ETHx)
{
    FlagStatus TempStatus;

    /* Read the status of the ETH software reset */
    if(READ_BIT(ETHx->DMAMODE, ETH_DMAMODE_SWR) != (uint32_t)RESET)
    {
        /* This flag is SET */
        TempStatus = SET;
    }
    else
    {
        /* This flag is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetDMAInterruptStatus.
*\*\fun     Checks whether the specified ETH DMA Interrupt flag is set or not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   IntFlag (The input parameters must be the following values):
*\*\          - ETH_DMA_INT_FLAG_DMACH0
*\*\          - ETH_DMA_INT_FLAG_MTL
*\*\          - ETH_DMA_INT_FLAG_MAC
*\*\return  SET or RESET
**/
INTStatus ETH_GetDMAInterruptStatus(ETH_Module* ETHx, uint32_t IntFlag)
{
    INTStatus TempStatus;

    /* Read the status of the corresponding INT bits */
    if(READ_BIT(ETHx->DMAINTSTS, IntFlag) != (uint32_t)RESET)
    {
        /* This Interrupt is SET */
        TempStatus = SET;
    }
    else
    {
        /* This Interrupt is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetDMACh0TxProcessStatus.
*\*\fun     Returns the ETH DMA Transmit Process Status.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  One of the following values:
*\*\          - ETH_DMACH0_TXPRO_FLAG_STOP
*\*\          - ETH_DMACH0_TXPRO_FLAG_RUN_FTTD
*\*\          - ETH_DMACH0_TXPRO_FLAG_RUN_WS
*\*\          - ETH_DMACH0_TXPRO_FLAG_RUN_RDS
*\*\          - ETH_DMACH0_TXPRO_FLAG_TSTMP_WS
*\*\          - ETH_DMACH0_TXPRO_FLAG_SUSPND
*\*\          - ETH_DMACH0_TXPRO_FLAG_RUN_CTD
**/
uint32_t ETH_GetDMACh0TxProcessStatus(ETH_Module* ETHx)
{
    /* Return The new ETH DMA Transmit Process Status */
    return (READ_BIT(ETHx->DMADBGSTS, ETH_DMADBGSTS_TPS0));
}

/**
*\*\name    ETH_GetDMACh0RxProcessStatus.
*\*\fun     Returns the ETH DMA Receive Process Status.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  One of the following values:
*\*\          - ETH_DMACH0_RXPRO_FLAG_STOP
*\*\          - ETH_DMACH0_RXPRO_FLAG_RUN_FTTD
*\*\          - ETH_DMACH0_RXPRO_FLAG_RUN_WRP
*\*\          - ETH_DMACH0_RXPRO_FLAG_SUSPND
*\*\          - ETH_DMACH0_RXPRO_FLAG_RUN_CRD
*\*\          - ETH_DMACH0_RXPRO_FLAG_TSTMP
*\*\          - ETH_DMACH0_RXPRO_FLAG_RUN_TRP
**/
uint32_t ETH_GetDMACh0RxProcessStatus(ETH_Module* ETHx)
{
    /* Return The new ETH DMA Receive Process Status */
    return (READ_BIT(ETHx->DMADBGSTS, ETH_DMADBGSTS_RPS0));
}

/**
*\*\name    ETH_GetDMACh0FlagStatus.
*\*\fun     Checks whether the specified ETH DMA-CH0 flag is set or not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Flag (The input parameters must be the following values):
*\*\          - ETH_DMACH0_FLAG_TI
*\*\          - ETH_DMACH0_FLAG_TPS
*\*\          - ETH_DMACH0_FLAG_TBU
*\*\          - ETH_DMACH0_FLAG_RI
*\*\          - ETH_DMACH0_FLAG_RBU
*\*\          - ETH_DMACH0_FLAG_RPS
*\*\          - ETH_DMACH0_FLAG_RWT
*\*\          - ETH_DMACH0_FLAG_ETI
*\*\          - ETH_DMACH0_FLAG_ERI
*\*\          - ETH_DMACH0_FLAG_FBE
*\*\          - ETH_DMACH0_FLAG_CDE
*\*\          - ETH_DMACH0_FLAG_AIS
*\*\          - ETH_DMACH0_FLAG_NIS
*\*\return  SET or RESET
**/
FlagStatus ETH_GetDMACh0FlagStatus(ETH_Module* ETHx, uint32_t Flag)
{
    FlagStatus TempStatus;

    /* Read the status of the corresponding flag bits */
    if(READ_BIT(ETHx->DMACH0STS, Flag) != (uint32_t)RESET)
    {
        /* This flag is SET */
        TempStatus = SET;
    }
    else
    {
        /* This flag is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}

/**
*\*\name    ETH_GetDMACh0InterruptStatus.
*\*\fun     Checks whether the specified ETH DMA-CH0 Interrupt flag is set or
*\*\        not.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   IntFlag (The input parameters must be the following values):
*\*\          - ETH_DMACH0_INT_FLAG_TI
*\*\          - ETH_DMACH0_INT_FLAG_TPS
*\*\          - ETH_DMACH0_INT_FLAG_TBU
*\*\          - ETH_DMACH0_INT_FLAG_RI
*\*\          - ETH_DMACH0_INT_FLAG_RBU
*\*\          - ETH_DMACH0_INT_FLAG_RPS
*\*\          - ETH_DMACH0_INT_FLAG_RWT
*\*\          - ETH_DMACH0_INT_FLAG_ETI
*\*\          - ETH_DMACH0_INT_FLAG_ERI
*\*\          - ETH_DMACH0_INT_FLAG_FBE
*\*\          - ETH_DMACH0_INT_FLAG_CDE
*\*\          - ETH_DMACH0_INT_FLAG_AIS
*\*\          - ETH_DMACH0_INT_FLAG_NIS
*\*\return  SET or RESET
**/
INTStatus ETH_GetDMACh0InterruptStatus(ETH_Module* ETHx, uint32_t IntFlag)
{
    INTStatus TempStatus;

    /* Read the status of the corresponding INT bits */
    if(READ_BIT(ETHx->DMACH0STS, IntFlag) != (uint32_t)RESET)
    {
        /* This Interrupt is SET */
        TempStatus = SET;
    }
    else
    {
        /* This Interrupt is RESET */
        TempStatus = RESET;
    }

    /* Return status */
    return TempStatus;
}



/**
*\*\name    ETH_ClearMACPHYInterruptFlag.
*\*\fun     Clears the MAC PHY Interrupt pending flag for the ETH.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
**/
void ETH_ClearMACPHYInterruptFlag(ETH_Module* ETHx)
{
    /* Check whether register write 1 clear is enabled or not */
    if (READ_BIT(ETHx->MACCSRSWCTRL, ETH_MACCSRSWCTRL_RCWE) != (uint32_t)RESET)
    {
        /* Clear the ETH PHY Interrupt flag by write 1 */
        SET_BIT(ETHx->MACINTSTS, ETH_MACINTSTS_PHYIS);
    }
    else
    {
        /* Clear the ETH PHY Interrupt flag by read */
        READ_BIT(ETHx->MACINTSTS, ETH_MACINTSTS_PHYIS);
    }
}

/**
*\*\name    ETH_ClearPMTFlag.
*\*\fun     Clears the MAC PMT pending flag for the ETH.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Flag (The input parameters must be the following values):
*\*\          - ETH_PMT_FLAG_WUPR
*\*\          - ETH_PMT_FLAG_MPR
*\*\return  none
**/
void ETH_ClearPMTFlag(ETH_Module* ETHx, uint32_t Flag)
{
    /* Check whether register write 1 clear is enabled or not */
    if (READ_BIT(ETHx->MACCSRSWCTRL, ETH_MACCSRSWCTRL_RCWE) != (uint32_t)RESET)
    {
        if (Flag == ETH_PMT_FLAG_WUPR)
        {
            /* Clear the ETH PMT flag by write 1 */
            SET_BIT(ETHx->MACPMTCTRLSTS, ETH_PMT_FLAG_WUPR);
        }
        else
        {
            /* Clear the ETH PMT flag by write 1 */
            SET_BIT(ETHx->MACPMTCTRLSTS, ETH_PMT_FLAG_MPR);
        }
    }
    else
    {
        /* Clear the ETH PMT flag by read */
        READ_REG(ETHx->MACPMTCTRLSTS);
    }
}

/**
*\*\name    ETH_ClearMMCRxInterruptFlag.
*\*\fun     Clears the MMC RX Interrupt pending flag for the ETH.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   IntFlag (The input parameters must be the following values):
*\*\          - ETH_MMCRX_INT_FLAG_BCGPIS
*\*\          - ETH_MMCRX_INT_FLAG_MCGPIS
*\*\          - ETH_MMCRX_INT_FLAG_CRCERPIS
*\*\          - ETH_MMCRX_INT_FLAG_ALGNERPIS
*\*\          - ETH_MMCRX_INT_FLAG_UCGPIS
*\*\return  none
**/
void ETH_ClearMMCRxInterruptFlag(ETH_Module* ETHx, uint32_t IntFlag)
{
    /* Clear the ETH MMC RX Interrupt flag by read */
    READ_BIT(ETHx->MMCRXINT, IntFlag);
}

/**
*\*\name    ETH_ClearMMCTxInterruptFlag.
*\*\fun     Clears the MMC TX Interrupt pending flag for the ETH.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   IntFlag (The input parameters must be the following values):
*\*\          - ETH_MMCTX_INT_FLAG_SCOLGPIS
*\*\          - ETH_MMCTX_INT_FLAG_MCOLGPIS
*\*\          - ETH_MMCTX_INT_FLAG_GPKTIS
*\*\return  none
**/
void ETH_ClearMMCTxInterruptFlag(ETH_Module* ETHx, uint32_t IntFlag)
{
    /* Clear the ETH MMC TX Interrupt flag by read */
    READ_BIT(ETHx->MMCTXINT, IntFlag);
}

/**
*\*\name    ETH_ClearMACTimeStampFlag.
*\*\fun     Clears the MAC Time Stamp pending flag for the ETH.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Flag (The input parameters must be the following values):
*\*\          - ETH_MACTS_FLAG_SOVF
*\*\          - ETH_MACTS_FLAG_TARGT0
*\*\          - ETH_MACTS_FLAG_TRGTERR0
*\*\          - ETH_MACTS_FLAG_TXTSSIS
*\*\return  none
**/
void ETH_ClearMACTimeStampFlag(ETH_Module* ETHx, uint32_t Flag)
{
    /* Check whether register write 1 clear is enabled or not */
    if (READ_BIT(ETHx->MACCSRSWCTRL, ETH_MACCSRSWCTRL_RCWE) != (uint32_t)RESET)
    {
        if (Flag == ETH_MACTS_FLAG_TXTSSIS)
        {
            /* Clear the MAC Time Stamp flag by write register */
            WRITE_REG(ETHx->MACTXTSSTSS, 1U);
        }
        else
        {
            /* Clear the MAC Time Stamp flag by write 1 */
            SET_BIT(ETHx->MACTSSTS, Flag);
        }
    }
    else
    {
        if (Flag == ETH_MACTS_FLAG_TXTSSIS)
        {
            /* Clear the MAC Time Stamp flag by read register */
            READ_REG(ETHx->MACTXTSSTSS);
        }
        else
        {
            /* Clear the MAC Time Stamp flag by read */
            READ_BIT(ETHx->MACTSSTS, Flag);
        }
    }
}

/**
*\*\name    ETH_ClearMACTxRxFlag.
*\*\fun     Clears the MAC TX RX pending flag for the ETH.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Flag (The input parameters must be the following values):
*\*\          - ETH_MACTX_FLAG_TJT
*\*\          - ETH_MACTX_FLAG_NCARR
*\*\          - ETH_MACTX_FLAG_LCARR
*\*\          - ETH_MACTX_FLAG_EXDEF
*\*\          - ETH_MACTX_FLAG_LCOL
*\*\          - ETH_MACTX_FLAG_EXCOL
*\*\          - ETH_MACRX_FLAG_RWT
*\*\return  none
**/
void ETH_ClearMACTxRxFlag(ETH_Module* ETHx, uint32_t Flag)
{
    /* Check whether register write 1 clear is enabled or not */
    if (READ_BIT(ETHx->MACCSRSWCTRL, ETH_MACCSRSWCTRL_RCWE) != (uint32_t)RESET)
    {
        /* Clear the ETH MAC TX RX Interrupt flag by write 1 */
        SET_BIT(ETHx->MACRXTXSTS, Flag);
    }
    else
    {
        /* Clear the ETH MAC TX RX Interrupt flag by read */
        READ_BIT(ETHx->MACRXTXSTS, Flag);
    }
}

/**
*\*\name    ETH_ClearMACMDIOInterruptFlag.
*\*\fun     Clears the MAC MDIO Interrupt pending flag for the ETH.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\return  none
**/
void ETH_ClearMACMDIOInterruptFlag(ETH_Module* ETHx)
{
    /* Check whether register write 1 clear is enabled or not */
    if (READ_BIT(ETHx->MACCSRSWCTRL, ETH_MACCSRSWCTRL_RCWE) != (uint32_t)RESET)
    {
        /* Clear the ETH MDIO Interrupt flag by write 1 */
        SET_BIT(ETHx->MACINTSTS, ETH_MACINTSTS_MDIOIS);
    }
    else
    {
        /* Clear the ETH MDIO Interrupt flag by read */
        READ_BIT(ETHx->MACINTSTS, ETH_MACINTSTS_MDIOIS);
    }
}

/**
*\*\name    ETH_ClearMTLQueueInterruptFlag.
*\*\fun     Clears the MTL Queue Interrupt pending flag for the ETH.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   IntFlag (The input parameters must be the following values):
*\*\          - ETH_MTLTXQUEUE_INT_FLAG_UNFIS
*\*\          - ETH_MTLRXQUEUE_INT_FLAG_OVFIS
*\*\return  none
**/
void ETH_ClearMTLQueueInterruptFlag(ETH_Module* ETHx, uint32_t IntFlag)
{
    /* Clear the selected ETH MTL Queue Interrupt flag */
    SET_BIT(ETHx->MTLQINTCTRLSTS, IntFlag);
}

/**
*\*\name    ETH_ClearDMACh0Flag.
*\*\fun     Clears the DMA Channel 0 pending flag for the ETH.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Flag (The input parameters must be the following values):
*\*\          - ETH_DMACH0_FLAG_TI
*\*\          - ETH_DMACH0_FLAG_TPS
*\*\          - ETH_DMACH0_FLAG_TBU
*\*\          - ETH_DMACH0_FLAG_RI
*\*\          - ETH_DMACH0_FLAG_RBU
*\*\          - ETH_DMACH0_FLAG_RPS
*\*\          - ETH_DMACH0_FLAG_RWT
*\*\          - ETH_DMACH0_FLAG_ETI
*\*\          - ETH_DMACH0_FLAG_ERI
*\*\          - ETH_DMACH0_FLAG_FBE
*\*\          - ETH_DMACH0_FLAG_CDE
*\*\          - ETH_DMACH0_FLAG_AIS
*\*\          - ETH_DMACH0_FLAG_NIS
*\*\return  none
**/
void ETH_ClearDMACh0Flag(ETH_Module* ETHx, uint32_t Flag)
{
    /* Clear the selected ETH DMA Channel 0 flag */
    SET_BIT(ETHx->DMACH0STS, Flag);
}

/**
*\*\name    ETH_ClearDMACh0InterruptFlag.
*\*\fun     Clears the DMA Channel 0 Interrupt pending flag for the ETH.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   IntFlag (The input parameters must be the following values):
*\*\          - ETH_DMACH0_INT_FLAG_TI
*\*\          - ETH_DMACH0_INT_FLAG_TPS
*\*\          - ETH_DMACH0_INT_FLAG_TBU
*\*\          - ETH_DMACH0_INT_FLAG_RI
*\*\          - ETH_DMACH0_INT_FLAG_RBU
*\*\          - ETH_DMACH0_INT_FLAG_RPS
*\*\          - ETH_DMACH0_INT_FLAG_RWT
*\*\          - ETH_DMACH0_INT_FLAG_ETI
*\*\          - ETH_DMACH0_INT_FLAG_ERI
*\*\          - ETH_DMACH0_INT_FLAG_FBE
*\*\          - ETH_DMACH0_INT_FLAG_CDE
*\*\          - ETH_DMACH0_INT_FLAG_AIS
*\*\          - ETH_DMACH0_INT_FLAG_NIS
*\*\return  none
**/
void ETH_ClearDMACh0InterruptFlag(ETH_Module* ETHx, uint32_t IntFlag)
{
    /* Clear the selected ETH DMA Channel 0 Interrupt flag */
    SET_BIT(ETHx->DMACH0STS, IntFlag);
}



/**
*\*\name    ETH_ConfigMACInterrupt.
*\*\fun     Enables or disables the specified ETH MAC interrupts.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Interrupt (The input parameters must be the following values):
*\*\          - ETH_MAC_INT_PHY
*\*\          - ETH_MAC_INT_PMT
*\*\          - ETH_MAC_INT_TS
*\*\          - ETH_MAC_INT_TX
*\*\          - ETH_MAC_INT_RX
*\*\          - ETH_MAC_INT_MDIO
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_ConfigMACInterrupt(ETH_Module* ETHx, uint32_t Interrupt, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ETH MAC interrupts */
        SET_BIT(ETHx->MACINTEN, Interrupt);
    }
    else
    {
        /* Disable the selected ETH MAC interrupts */
        CLEAR_BIT(ETHx->MACINTEN, Interrupt);
    }
}

/**
*\*\name    ETH_ConfigMMCRxInterrupt.
*\*\fun     Enables or disables the specified ETH MMC RX interrupts.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Interrupt (The input parameters must be the following values):
*\*\          - ETH_MMCRX_INT_BCGPIM
*\*\          - ETH_MMCRX_INT_MCGPIM
*\*\          - ETH_MMCRX_INT_CRCERPIM
*\*\          - ETH_MMCRX_INT_ALGNERPIM
*\*\          - ETH_MMCRX_INT_UCGPIM
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_ConfigMMCRxInterrupt(ETH_Module* ETHx, uint32_t Interrupt, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ETH MMC RX interrupts */
        CLEAR_BIT(ETHx->MMCRXINTMSK, Interrupt);
    }
    else
    {
        /* Disable the selected ETH MMC RX interrupts */
        SET_BIT(ETHx->MMCRXINTMSK, Interrupt);
    }
}

/**
*\*\name    ETH_ConfigMMCTxInterrupt.
*\*\fun     Enables or disables the specified ETH MMC TX interrupts.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Interrupt (The input parameters must be the following values):
*\*\          - ETH_MMCTX_INT_SCOLGPIM
*\*\          - ETH_MMCTX_INT_MCOLGPIM
*\*\          - ETH_MMCTX_INT_GPKTIM
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_ConfigMMCTxInterrupt(ETH_Module* ETHx, uint32_t Interrupt, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ETH MMC TX interrupts */
        CLEAR_BIT(ETHx->MMCTXINTMSK, Interrupt);
    }
    else
    {
        /* Disable the selected ETH MMC TX interrupts */
        SET_BIT(ETHx->MMCTXINTMSK, Interrupt);
    }
}

/**
*\*\name    ETH_ConfigMTLQueueInterrupt.
*\*\fun     Enables or disables the specified ETH MTL Queue interrupts.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Interrupt (The input parameters must be the following values):
*\*\          - ETH_MTLTXQUEUE_INT_UIE
*\*\          - ETH_MTLRXQUEUE_INT_OIE
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_ConfigMTLQueueInterrupt(ETH_Module* ETHx, uint32_t Interrupt, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ETH MTL Queue interrupts */
        SET_BIT(ETHx->MTLQINTCTRLSTS, Interrupt);
    }
    else
    {
        /* Disable the selected ETH MTL Queue interrupts */
        CLEAR_BIT(ETHx->MTLQINTCTRLSTS, Interrupt);
    }
}

/**
*\*\name    ETH_ConfigDMACh0Interrupt.
*\*\fun     Enables or disables the specified ETH DMA Channel 0 interrupts.
*\*\param   ETHx (The input parameters must be the following values):
*\*\          - ETH1
*\*\          - ETH2
*\*\param   Interrupt (The input parameters must be the following values):
*\*\          - ETH_DMACH0_INT_TI
*\*\          - ETH_DMACH0_INT_TPS
*\*\          - ETH_DMACH0_INT_TBU
*\*\          - ETH_DMACH0_INT_RI
*\*\          - ETH_DMACH0_INT_RBU
*\*\          - ETH_DMACH0_INT_RPS
*\*\          - ETH_DMACH0_INT_RWT
*\*\          - ETH_DMACH0_INT_ETI
*\*\          - ETH_DMACH0_INT_ERI
*\*\          - ETH_DMACH0_INT_FBE
*\*\          - ETH_DMACH0_INT_CDE
*\*\          - ETH_DMACH0_INT_AIS
*\*\          - ETH_DMACH0_INT_NIS
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ETH_ConfigDMACh0Interrupt(ETH_Module* ETHx, uint32_t Interrupt, FunctionalStatus Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ETH DMA Channel 0 interrupts */
        SET_BIT(ETHx->DMACH0INTEN, Interrupt);
    }
    else
    {
        /* Disable the selected ETH DMA Channel 0 interrupts */
        CLEAR_BIT(ETHx->DMACH0INTEN, Interrupt);
    }
}


