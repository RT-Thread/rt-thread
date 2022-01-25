////////////////////////////////////////////////////////////////////////////////
/// @file     hal_eth.c
/// @author   AE TEM
/// @brief    THIS FILE PROVIDES ALL THE HAL_eth.c EXAMPLE.
/// ////////////////////////////////////////////////////////////////////////////
/// @attention
///
/// THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
/// CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
/// TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
/// CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
/// HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
/// CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
///
/// <H2><CENTER>&COPY; COPYRIGHT  MINDMOTION </CENTER></H2>
////////////////////////////////////////////////////////////////////////////////

#define _HAL_ETH_C_
#include "hal_rcc.h"
#include "hal_eth.h"
#include "reg_eth.h"


void ETH_DeInit(void)
{
    RCC_AHBPeriphResetCmd(RCC_AHBENR_ETHMAC, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBENR_ETHMAC, DISABLE);
}

void ETH_StructInit(ETH_InitTypeDef* ptr)
{
    ptr->ETH_AutoNegotiation         = ETH_AutoNegotiation_Enable;              ///< PHY Auto-negotiation enabled
    ptr->ETH_Watchdog                = ETH_Watchdog_Enable;                     ///< MAC watchdog enabled: cuts off long frame
    ptr->ETH_Jabber                  = ETH_Jabber_Enable;                       ///< MAC Jabber enabled in Half-duplex mode
    ptr->ETH_InterFrameGap           = ETH_InterFrameGap_96Bit;                 ///< Ethernet interframe gap set to 96 bits
    ptr->ETH_CarrierSense            = ETH_CarrierSense_Enable;                 ///< Carrier Sense Enabled in Half-Duplex mode
    ptr->ETH_Speed                   = ETH_Speed_100M;                          ///< PHY speed configured to 100Mbit/s
    ptr->ETH_ReceiveOwn              = ETH_ReceiveOwn_Enable;                   ///< Receive own Frames in Half-Duplex mode enabled
    ptr->ETH_LoopbackMode            = ETH_LoopbackMode_Disable;                ///< MAC MII loopback disabled
    ptr->ETH_Mode                    = ETH_Mode_FullDuplex;                     ///< Full-Duplex mode selected
    ptr->ETH_ChecksumOffload         = ETH_ChecksumOffload_Disable;             ///< IPv4 and TCP/UDP/ICMP frame Checksum Offload disabled
    ptr->ETH_RetryTransmission       = ETH_RetryTransmission_Enable;            ///< Retry Transmission enabled for half-duplex mode
    ptr->ETH_AutomaticPadCRCStrip    = ETH_AutomaticPadCRCStrip_Disable;        ///< Automatic PAD/CRC strip disable
    ptr->ETH_BackOffLimit            = ETH_BackOffLimit_10;                     ///< half-duplex mode retransmission Backoff time_limit = 10 slot time
    ptr->ETH_DeferralCheck           = ETH_DeferralCheck_Disable;               ///< half-duplex mode Deferral check disabled
    ptr->ETH_ReceiveAll              = ETH_ReceiveAll_Disable;                  ///< Receive all frames disabled
    ptr->ETH_SourceAddrFilter        = ETH_SourceAddrFilter_Disable;            ///< Source address filtering (on the optional MAC addresses) disabled
    ptr->ETH_PassControlFrames       = ETH_PassControlFrames_BlockAll;          ///< Do not forward control frames that do not pass the address filtering
    ptr->ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Disable;   ///< Disable reception of Broadcast frames
    ptr->ETH_DestinationAddrFilter   = ETH_DestinationAddrFilter_Normal;        ///< Normal Destination address filtering (not reverse addressing)
    ptr->ETH_PromiscuousMode         = ETH_PromiscuousMode_Disable;             ///< Promiscuous address filtering mode disabled
    ptr->ETH_MulticastFramesFilter   = ETH_MulticastFramesFilter_Perfect;       ///< Perfect address filtering for multicast addresses
    ptr->ETH_UnicastFramesFilter     = ETH_UnicastFramesFilter_Perfect;         ///< Perfect address filtering for unicast addresses
    ptr->ETH_HashTableHigh           = 0x0;                                     ///< Initialize hash table high and low regs
    ptr->ETH_HashTableLow            = 0x0;
    ptr->ETH_PauseTime               = 0x0;                                     ///< Flow control config (flow control disabled)
    ptr->ETH_ZeroQuantaPause         = ETH_ZeroQuantaPause_Enable;
    ptr->ETH_PauseLowThreshold       = ETH_PauseLowThreshold_Minus4;
    ptr->ETH_UnicastPauseFrameDetect = ETH_UnicastPauseFrameDetect_Disable;
    ptr->ETH_ReceiveFlowControl      = ETH_ReceiveFlowControl_Disable;
    ptr->ETH_TransmitFlowControl     = ETH_TransmitFlowControl_Disable;
    ptr->ETH_VLANTagComparison       = ETH_VLANTagComparison_16Bit;             ///< VLANtag config (VLAN field not checked)
    ptr->ETH_VLANTagIdentifier       = 0x0;

    ptr->ETH_DropTCPIPChecksumErrorFrame = ETH_DropTCPIPChecksumErrorFrame_Disable; ///< Drops frames with with TCP/IP checksum errors
    ptr->ETH_ReceiveStoreForward     = ETH_ReceiveStoreForward_Enable;          ///< Store and forward mode enabled for receive
    ptr->ETH_FlushReceivedFrame      = ETH_FlushReceivedFrame_Enable;           ///< Flush received frame that created FIFO overflow
    ptr->ETH_TransmitStoreForward    = ETH_TransmitStoreForward_Enable;         ///< Store and forward mode enabled for transmit
    ptr->ETH_TransmitThresholdControl = ETH_ReceiveThresholdControl_64Bytes;    ///< Threshold TXFIFO level set to 64 bytes (used when threshold mode is enabled)
    ptr->ETH_ForwardErrorFrames      = ETH_ForwardErrorFrames_Disable;          ///< Disable forwarding frames with errors (short frames, CRC,...)
    ptr->ETH_ForwardUndersizedGoodFrames = ETH_ForwardUndersizedGoodFrames_Disable; ///< Disable undersized good frames
    ptr->ETH_ReceiveThresholdControl = ETH_ReceiveThresholdControl_64Bytes;     ///< Threshold RXFIFO level set to 64 bytes (used when Cut through mode is enabled)
    ptr->ETH_SecondFrameOperate      = ETH_SecondFrameOperate_Disable;          ///< Disable Operate on second frame (transmit a second frame to FIFO without waiting status of previous frame
    ptr->ETH_AddressAlignedBeats     = ETH_AddressAlignedBeats_Enable;          ///< DMA works on 32-bit aligned start source and destinations addresses
    ptr->ETH_FixedBurst              = ETH_FixedBurst_Enable;                   ///< Enabled Fixed Burst Mode (mix of INC4, INC8, INC16 and SINGLE DMA transactions
    ptr->ETH_RxDMABurstLength        = ETH_RxDMABurstLength_32Beat;             ///< DMA transfer max burst length = 32 beats = 32 x 32bits
    ptr->ETH_TxDMABurstLength        = ETH_TxDMABurstLength_32Beat;
    ptr->ETH_DescriptorSkipLength    = 0x0;                                     ///< DMA Ring mode skip length = 0
    ptr->ETH_DMAArbitration          = ETH_DMAArbitration_RoundRobin_RxTx_1_1;  ///< Equal priority (round-robin) between transmit and receive DMA engines
}

u32 ETH_Init(ETH_InitTypeDef* ptr, u16 phy_addr)
{
    u32 hclk = RCC_GetHCLKFreq();
    u32 reg = ETH->MACMIIAR & MACMIIAR_CR_MASK;
    u32 temp_val = 0;
    hclk = 100000000;
    ////////////////////////////////////////////////////////////////////////////
    if (hclk >= 20000000 && hclk < 35000000) {
        reg |= ETH_MACMIIAR_CR_Div16;                                           ///< HCLK 20 ~ 35 MHz, /16
    }
    else if (hclk >= 35000000 && hclk < 60000000) {
        reg |= ETH_MACMIIAR_CR_Div26;                                           ///< HCLK 35 ~ 60 MHz, /26
    }
    else if (hclk >= 60000000 && hclk < 100000000) {
        reg |= ETH_MACMIIAR_CR_Div42;                                           ///< HCLK 60 ~ 100 MHz, /42
    }
    else if (hclk >= 100000000 && hclk < 150000000) {
        reg |= ETH_MACMIIAR_CR_Div62;                                           ///< HCLK 100 ~ 150 MHz, /62
    }
    else {
        reg |= ETH_MACMIIAR_CR_Div102;                                          ///< HCLK 150 ~ 168 MHz, /102
    }

    ETH->MACMIIAR = reg;

    ////////////////////////////////////////////////////////////////////////////
    ETH_WritePHYRegister(phy_addr, PHY_BCR, PHY_Reset);
    if (ptr->ETH_AutoNegotiation != ETH_AutoNegotiation_Disable) {
        // Wait for linked status
        while (!(ETH_ReadPHYRegister(phy_addr, PHY_BSR) & PHY_Linked_Status));
        ETH_WritePHYRegister(phy_addr, PHY_BCR, PHY_AutoNegotiation);
        // Enable Auto-Negitation
        while (!(ETH_ReadPHYRegister(phy_addr, PHY_BSR) & PHY_AutoNego_Complete)) {

        }
        // Read the result of the Auto-Negitation
        temp_val = ETH_ReadPHYRegister(phy_addr, 31);

        if ((temp_val & 0x1C) == 0x4) {
            ptr->ETH_Speed = ETH_Speed_10M;
            ptr->ETH_Mode = ETH_Mode_HalfDuplex;
            SYSCFG->CFGR2 &= ~(1 << 21);
        }
        else if((temp_val & 0x1C) == 0x14) {
            ptr->ETH_Speed = ETH_Speed_10M;
            ptr->ETH_Mode = ETH_Mode_FullDuplex;
            SYSCFG->CFGR2 |= 1 << 21;
        }
        else if((temp_val & 0x1C) == 0x8) {
            ptr->ETH_Speed = ETH_Speed_100M;
            ptr->ETH_Mode = ETH_Mode_HalfDuplex;
            SYSCFG->CFGR2 &= ~(1 << 21);
        }
        else if((temp_val & 0x1C) == 0x18) {
            ptr->ETH_Speed = ETH_Speed_100M;
            ptr->ETH_Mode = ETH_Mode_FullDuplex;
            SYSCFG->CFGR2 |= 1 << 21;
        }
    }
    else {
        ETH_WritePHYRegister(phy_addr, PHY_BCR, ((u16)(ptr->ETH_Mode >> 3) |
                             (u16)(ptr->ETH_Speed >> 1)));
        if(ptr->ETH_Speed == ETH_Speed_10M) {
            SYSCFG->CFGR2 &= ~(1 << 21);
        }
        else {
            SYSCFG->CFGR2 |= 1 << 21;
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    ETH->MACCR = ETH->MACCR & MACCR_CLEAR_MASK |   (ptr->ETH_Watchdog |
                 ptr->ETH_Jabber |
                 ptr->ETH_InterFrameGap |
                 ptr->ETH_CarrierSense |
                 ptr->ETH_Speed |
                 ptr->ETH_ReceiveOwn |
                 ptr->ETH_LoopbackMode |
                 ptr->ETH_Mode |
                 ptr->ETH_ChecksumOffload |
                 ptr->ETH_RetryTransmission |
                 ptr->ETH_AutomaticPadCRCStrip |
                 ptr->ETH_DeferralCheck);

    ETH->MACFFR =   ptr->ETH_ReceiveAll |
                    ptr->ETH_SourceAddrFilter |
                    ptr->ETH_PassControlFrames |
                    ptr->ETH_BroadcastFramesReception |
                    ptr->ETH_DestinationAddrFilter |
                    ptr->ETH_PromiscuousMode |
                    ptr->ETH_MulticastFramesFilter |
                    ptr->ETH_UnicastFramesFilter;

    ETH->MACHTHR = ptr->ETH_HashTableHigh;
    ETH->MACHTLR = ptr->ETH_HashTableLow;

    ETH->MACFCR = ETH->MACFCR & MACFCR_CLEAR_MASK | ((ptr->ETH_PauseTime << ETH_MACFCR_PT_Pos) |
                  ptr->ETH_ZeroQuantaPause |
                  ptr->ETH_PauseLowThreshold |
                  ptr->ETH_UnicastPauseFrameDetect |
                  ptr->ETH_ReceiveFlowControl |
                  ptr->ETH_TransmitFlowControl);

    ETH->MACVLANTR = ptr->ETH_VLANTagComparison | ptr->ETH_VLANTagIdentifier;

    ETH->DMAOMR = 0x00200004;
    ETH->DMAIER = 0x0001A040;
    ETH->DMABMR = ( ptr->ETH_AddressAlignedBeats |
                    ptr->ETH_FixedBurst |
                    ptr->ETH_RxDMABurstLength |                                 // !! if 4xPBL is selected for Tx or Rx it is applied for the other
                    ptr->ETH_TxDMABurstLength |
                    ptr->ETH_DescriptorSkipLength << 2 |
                    ptr->ETH_DMAArbitration);// |
//                    ETH_DMABMR_USP);                                            // Enable use of separate PBL for Rx and Tx

    return ETH_SUCCESS;
}

void ETH_Start(void)
{
    ETH_MACTransmissionCmd(ENABLE);
    ETH_MACReceptionCmd(ENABLE);
    ETH_FlushTransmitFIFO();
    ETH_DMATransmissionCmd(ENABLE);
    ETH_DMAReceptionCmd(ENABLE);
}

void ETH_Stop(void)
{
    ETH_DMATransmissionCmd(DISABLE);
    ETH_DMAReceptionCmd(DISABLE);
    ETH_MACReceptionCmd(DISABLE);
    ETH_FlushTransmitFIFO();
    ETH_MACTransmissionCmd(DISABLE);
}

void ETH_MACTransmissionCmd(FunctionalState sta)
{
    sta ? (ETH->MACCR |= ETH_MACCR_TE) : (ETH->MACCR &= ~ETH_MACCR_TE);
}

void ETH_MACReceptionCmd(FunctionalState sta)
{
    sta ? (ETH->MACCR |= ETH_MACCR_RE) : (ETH->MACCR &= ~ETH_MACCR_RE);
}

FlagStatus ETH_GetFlowControlBusyStatus(void)
{
    return (FlagStatus)(ETH->MACFCR & ETH_MACFCR_FCBBPA);
}

void ETH_InitiatePauseControlFrame(void)
{
    ETH->MACFCR |= ETH_MACFCR_FCBBPA;
}

void ETH_BackPressureActivationCmd(FunctionalState sta)
{
    sta ? (ETH->MACFCR |= ETH_MACFCR_FCBBPA) : (ETH->MACFCR &= ~ETH_MACFCR_FCBBPA);
}

void ETH_MACAddressConfig(u32 reg_addr, u8* mac_addr)
{
    *(__IO u32*)(ETH_MAC_ADDR_HBASE + reg_addr) =
        (u32)mac_addr[5] << 8 |
        (u32)mac_addr[4];

    *(__IO u32*)(ETH_MAC_ADDR_LBASE + reg_addr) =
        (u32)mac_addr[3] << 24 |
        (u32)mac_addr[2] << 16 |
        (u32)mac_addr[1] << 8 |
        (u32)mac_addr[0];
}

void ETH_GetMACAddress(u32 reg_addr, u8* mac_addr)
{
    mac_addr[5] = *(__IO u32*)(ETH_MAC_ADDR_HBASE + reg_addr) >> 8 & 0xFF;
    mac_addr[4] = *(__IO u32*)(ETH_MAC_ADDR_HBASE + reg_addr) & 0xFF;
    mac_addr[3] = *(__IO u32*)(ETH_MAC_ADDR_LBASE + reg_addr) >> 24 & 0xFF;
    mac_addr[2] = *(__IO u32*)(ETH_MAC_ADDR_LBASE + reg_addr) >> 16 & 0xFF;
    mac_addr[1] = *(__IO u32*)(ETH_MAC_ADDR_LBASE + reg_addr) >> 8 & 0xFF;
    mac_addr[0] = *(__IO u32*)(ETH_MAC_ADDR_LBASE + reg_addr) & 0xFF;
}

void ETH_MACAddressPerfectFilterCmd(u32 reg_addr, FunctionalState sta)
{
    sta ?   ((*(__IO u32*)(ETH_MAC_ADDR_HBASE + reg_addr)) |= ETH_MACA1HR_AE) :
    ((*(__IO u32*)(ETH_MAC_ADDR_HBASE + reg_addr)) &= ~ETH_MACA1HR_AE);
}

void ETH_MACAddressFilterConfig(u32 reg_addr, u32 sta)
{
    sta ?   ((*(__IO u32*)(ETH_MAC_ADDR_HBASE + reg_addr)) |= ETH_MACA1HR_SA) :
    ((*(__IO u32*)(ETH_MAC_ADDR_HBASE + reg_addr)) |= ETH_MACA1HR_SA);
}

void ETH_MACAddressMaskBytesFilterConfig(u32 reg_addr, u32 mask_byte)
{
    (*(__IO u32*)(ETH_MAC_ADDR_HBASE + reg_addr)) &= ~ETH_MACA1HR_MBC;

    (*(__IO u32*)(ETH_MAC_ADDR_HBASE + reg_addr)) |= mask_byte;
}

FrameTypeDef ETH_Get_Received_Frame(void)
{
    FrameTypeDef frame;

    frame.len = ((DMARxDescToGet->CS & ETH_DMA_RDES_FL) >> ETH_DMA_RDES_FL_Pos) - 4;
    frame.buf = (DMA_RX_FRAME_infos->ptrFS_Rx_Desc)->BUF1ADDR;
    frame.ptrDesc = DMA_RX_FRAME_infos->ptrFS_Rx_Desc;


    DMARxDescToGet = (ETH_DMADESCTypeDef*)(DMARxDescToGet->BUF2NDADDR);

    return frame;
}

FrameTypeDef ETH_Get_Received_Frame_interrupt(void)
{
    FrameTypeDef frame = {0};
    __IO u32 desc_cnt = 0;

    while(!(DMARxDescToGet->CS & ETH_DMA_RDES_OWN) && desc_cnt < ETH_RX_BUF_NUM) {
        desc_cnt++;

        if ( (DMARxDescToGet->CS & ETH_DMA_RDES_FS) &&
                !(DMARxDescToGet->CS & ETH_DMA_RDES_LS)) {
            DMA_RX_FRAME_infos->ptrFS_Rx_Desc = DMARxDescToGet;
            DMA_RX_FRAME_infos->cnt = 1;
            DMARxDescToGet = (ETH_DMADESCTypeDef*)(DMARxDescToGet->BUF2NDADDR);

        }
        else if ( (DMARxDescToGet->CS & ETH_DMA_RDES_FS) &&
                  (DMARxDescToGet->CS & ETH_DMA_RDES_LS)) {
            DMA_RX_FRAME_infos->cnt++;
            DMARxDescToGet = (ETH_DMADESCTypeDef*)(DMARxDescToGet->BUF2NDADDR);
        }
        else {
            DMA_RX_FRAME_infos->ptrLS_Rx_Desc = DMARxDescToGet;
            DMA_RX_FRAME_infos->cnt++;

            if (DMA_RX_FRAME_infos->cnt == 1)
                DMA_RX_FRAME_infos->ptrFS_Rx_Desc = DMARxDescToGet;

            frame.len = ((DMARxDescToGet->CS & ETH_DMA_RDES_FL) >> ETH_DMA_RDES_FL_Pos) - 4;

            frame.buf = (DMA_RX_FRAME_infos->cnt > 1) ?
                        (DMA_RX_FRAME_infos->ptrFS_Rx_Desc->BUF1ADDR) :
                        (DMARxDescToGet->BUF1ADDR);

            frame.ptrDesc = DMA_RX_FRAME_infos->ptrFS_Rx_Desc;

            DMARxDescToGet = (ETH_DMADESCTypeDef*)(DMARxDescToGet->BUF2NDADDR);

            return frame;
        }
    }

    return frame;
}

u32 ETH_Prepare_Transmit_Descriptors(u16 len)
{
    u32 cnt = 0, i = 0;
    __IO ETH_DMADESCTypeDef* temp_desc = DMATxDescToSet;

    if (DMATxDescToSet->CS & ETH_DMA_TDES_OWN)
        return ETH_ERROR;

    if(len > ETH_TX_BUF_SIZE) {
        cnt = len / ETH_TX_BUF_SIZE;

        if (len % ETH_TX_BUF_SIZE)
            cnt++;
    }
    else {
        cnt = 1;
    }

    if (cnt == 1) {
        temp_desc->BL &= ~(ETH_DMA_TDES_FS | ETH_DMA_TDES_LS | ETH_DMA_TDES_TBS1);

        temp_desc->BL |=    ETH_DMA_TDES_FS |
                            ETH_DMA_TDES_LS |
                            (len & ETH_DMA_TDES_TBS1);

        temp_desc->CS |= ETH_DMA_TDES_OWN;
        temp_desc = (ETH_DMADESCTypeDef*)(temp_desc->BUF2NDADDR);
    }
    else {
        for (i = 0; i < cnt; i++) {
            temp_desc->BL &= ~(ETH_DMA_TDES_FS | ETH_DMA_TDES_LS);

            if (i == 0)
                temp_desc->BL |= ETH_DMA_TDES_FS;

            temp_desc->BL = ETH_TX_BUF_SIZE & ETH_DMA_TDES_TBS1;

            if (i == (cnt - 1)) {
                temp_desc->BL &= ~ETH_DMA_TDES_TBS1;
                temp_desc->BL |=    ETH_DMA_TDES_LS |
                                    ((len - (cnt - 1) * ETH_TX_BUF_SIZE) & ETH_DMA_TDES_TBS1);
            }

            temp_desc->CS |= ETH_DMA_TDES_OWN;
            temp_desc = (ETH_DMADESCTypeDef*)(temp_desc->BUF2NDADDR);
        }
    }

    DMATxDescToSet = temp_desc;

    if (ETH->DMASR & ETH_DMASR_TBUS) {
        ETH->DMASR = ETH_DMASR_TBUS;
        ETH->DMATPDR = 0;
    }

    return ETH_SUCCESS;
}

void ETH_DMARxDescChainInit(ETH_DMADESCTypeDef* ptr_desc, u8* buf, u32 cnt)
{
    u32 i = 0;
    ETH_DMADESCTypeDef* temp_desc;

    DMARxDescToGet = ptr_desc;

    for (i = 0; i < cnt; i++) {
        temp_desc = ptr_desc + i;
        temp_desc->CS = ETH_DMA_RDES_OWN;
        temp_desc->BL = ETH_DMA_RDES_RCH | ETH_RX_BUF_SIZE;
        temp_desc->BUF1ADDR = (u32)&buf[i * ETH_RX_BUF_SIZE];

        if (i < cnt - 1) {
            temp_desc->BUF2NDADDR = (u32)(ptr_desc + i + 1);
        }
        else {
            temp_desc->BUF2NDADDR = (u32)(ptr_desc);
        }
    }

    ETH->DMARDLAR = (u32)ptr_desc;

    DMA_RX_FRAME_infos = &RX_Frame_Descriptor;
}

u32 ETH_CheckFrameReceived(void)
{
    if(!(DMARxDescToGet->CS & ETH_DMA_RDES_OWN) &&
            (DMARxDescToGet->CS & ETH_DMA_RDES_LS)) {

        DMA_RX_FRAME_infos->cnt++;

        if (DMA_RX_FRAME_infos->cnt == 1) {
            DMA_RX_FRAME_infos->ptrFS_Rx_Desc = DMARxDescToGet;
        }
        DMA_RX_FRAME_infos->ptrLS_Rx_Desc = DMARxDescToGet;
        return 1;
    }
    else if ( !(DMARxDescToGet->CS & ETH_DMA_RDES_OWN) &&
              !(DMARxDescToGet->CS & ETH_DMA_RDES_LS)  &&
              (DMARxDescToGet->CS & ETH_DMA_RDES_FS)) {
        DMA_RX_FRAME_infos->ptrFS_Rx_Desc = DMARxDescToGet;
        DMA_RX_FRAME_infos->ptrLS_Rx_Desc = (void*)0;
        DMA_RX_FRAME_infos->cnt = 1;
    }
    else if ( !(DMARxDescToGet->CS & ETH_DMA_RDES_OWN) &&
              !(DMARxDescToGet->CS & ETH_DMA_RDES_LS)  &&
              !(DMARxDescToGet->CS & ETH_DMA_RDES_FS)) {
        DMA_RX_FRAME_infos->cnt++;
        DMARxDescToGet = (ETH_DMADESCTypeDef*)(DMARxDescToGet->BUF2NDADDR);
    }

    return 0;
}

void ETH_DMATxDescChainInit(ETH_DMADESCTypeDef* ptr_desc, u8* buf, u32 cnt)
{
    u32 i = 0;
    ETH_DMADESCTypeDef* temp_desc;

    DMATxDescToSet = ptr_desc;

    for (i = 0; i < cnt; i++) {
        temp_desc = ptr_desc + i;
        temp_desc->BL = ETH_DMA_TDES_TCH;
        temp_desc->BUF1ADDR = (u32)(&buf[i * ETH_TX_BUF_SIZE]);

        if (i < cnt - 1) {
            temp_desc->BUF2NDADDR = (u32)(ptr_desc + i + 1);
        }
        else {
            temp_desc->BUF2NDADDR = (u32)(ptr_desc);
        }
    }

    ETH->DMATDLAR = (u32)ptr_desc;
}

FlagStatus ETH_GetDMATxDescFlagStatus(ETH_DMADESCTypeDef* ptr_desc, u32 flag)
{
    return (FlagStatus)(ptr_desc->CS & flag);
}

u32 ETH_GetDMATxDescCollisionCount(ETH_DMADESCTypeDef* ptr_desc)
{
    return (ptr_desc->CS & ETH_DMA_TDES_CC) >> ETH_DMA_TDES_COLLISION_COUNTSHIFT;
}

void ETH_SetDMATxDescOwnBit(ETH_DMADESCTypeDef* ptr_desc)
{
    ptr_desc->CS |= ETH_DMA_TDES_OWN;
}

void ETH_DMATxDescTransmitITConfig(ETH_DMADESCTypeDef* ptr_desc, FunctionalState sta)
{
    sta ? (ptr_desc->BL |= ETH_DMA_TDES_IC) : (ptr_desc->BL &= ~ETH_DMA_TDES_IC);
}

void ETH_DMATxDescFrameSegmentConfig(ETH_DMADESCTypeDef* ptr_desc, u32 val)
{
    ptr_desc->CS |= val;
}

void ETH_DMATxDescChecksumInsertionConfig(ETH_DMADESCTypeDef* ptr_desc, u32 val)
{
    ptr_desc->CS |= val;
}

void ETH_DMATxDescCRCCmd(ETH_DMADESCTypeDef* ptr_desc, FunctionalState sta)
{
    sta ? (ptr_desc->BL &= ~ETH_DMA_TDES_DC) : (ptr_desc->BL |= ETH_DMA_TDES_DC);
}

void ETH_DMATxDescSecondAddressChainedCmd(ETH_DMADESCTypeDef* ptr_desc, FunctionalState sta)
{
    sta ? (ptr_desc->BL |= ETH_DMA_TDES_TCH) : (ptr_desc->BL &= ~ETH_DMA_TDES_TCH);
}

void ETH_DMATxDescShortFramePaddingCmd(ETH_DMADESCTypeDef* ptr_desc, FunctionalState sta)
{
    sta ? (ptr_desc->BL &= ~ETH_DMA_TDES_DP) : (ptr_desc->BL |= ETH_DMA_TDES_DP);
}

void ETH_DMATxDescBufferSizeConfig(ETH_DMADESCTypeDef* ptr_desc, u32 buf1_size, u32 buf2_size)
{
    ptr_desc->BL |= buf1_size | (buf2_size << ETH_DMA_TDES_BUFFER2_SIZESHIFT);
}

FlagStatus ETH_GetDMARxDescFlagStatus(ETH_DMADESCTypeDef* ptr_desc, u32 flag)
{
    return (FlagStatus)(ptr_desc->CS & flag);
}

void ETH_SetDMARxDescOwnBit(ETH_DMADESCTypeDef* ptr_desc)
{
    ptr_desc->CS |= ETH_DMA_RDES_OWN;
}

u32 ETH_GetDMARxDescFrameLength(ETH_DMADESCTypeDef* ptr_desc)
{
    return (ptr_desc->CS & ETH_DMA_RDES_FL) >> ETH_DMA_RDES_FRAME_LENGTHSHIFT;
}

void ETH_DMARxDescReceiveITConfig(ETH_DMADESCTypeDef* ptr_desc, FunctionalState sta)
{
    sta ? (ptr_desc->CS &= ~ETH_DMA_RDES_DIC) : (ptr_desc->CS |= ETH_DMA_RDES_DIC);
}

u32 ETH_GetDMARxDescBufferSize(ETH_DMADESCTypeDef* ptr_desc, u32 buf)
{
    return (buf != ETH_DMA_RDES_Buffer1 ?
            ((ptr_desc->BL & ETH_DMA_RDES_RBS2) >> ETH_DMA_RDES_BUFFER2_SIZESHIFT) :
            (ptr_desc->BL & ETH_DMA_RDES_RBS1));
}

u32 ETH_GetRxPktSize(ETH_DMADESCTypeDef* ptr_desc)
{
    u32 len = 0;

    if (    !(ptr_desc->CS & ETH_DMA_RDES_OWN) &&
            !(ptr_desc->CS & ETH_DMA_RDES_ES) &&
            (ptr_desc->CS & ETH_DMA_RDES_LS)) {
        len = ETH_GetDMARxDescFrameLength(ptr_desc);
    }

    return len;
}

////////////////////////////////////////////////////////////////////////////////
void ETH_SoftwareReset(void)
{
    ETH->DMABMR |= ETH_DMABMR_SR;
}

FlagStatus ETH_GetSoftwareResetStatus(void)
{
    return (FlagStatus)(ETH->DMABMR & ETH_DMABMR_SR);
}

FlagStatus ETH_GetDMAFlagStatus(u32 flag)
{
    return (FlagStatus)(ETH->DMASR & flag);
}

void ETH_DMAClearFlag(u32 flag)
{
    ETH->DMASR = flag;
}

void ETH_DMAITConfig(u32 it, FunctionalState sta)
{
    sta ? (ETH->DMAIER |= it) : (ETH->DMAIER &= ~it);
}

ITStatus ETH_GetDMAITStatus(u32 it)
{
    return (ITStatus)(ETH->DMASR & it);
}

void ETH_DMAClearITPendingBit(u32 it)
{
    ETH->DMASR = it;
}

u32 ETH_GetTransmitProcessState(void)
{
    return ETH->DMASR & ETH_DMASR_TS;
}

u32 ETH_GetReceiveProcessState(void)
{
    return ETH->DMASR & ETH_DMASR_RS;
}

void ETH_FlushTransmitFIFO(void)
{
    ETH->DMAOMR |= ETH_DMAOMR_FTF;
}

FlagStatus ETH_GetFlushTransmitFIFOStatus(void)
{
    return (FlagStatus)(ETH->DMAOMR & ETH_DMAOMR_FTF);
}

void ETH_DMATransmissionCmd(FunctionalState sta)
{
    sta ? (ETH->DMAOMR |= ETH_DMAOMR_ST) : (ETH->DMAOMR &= ~ETH_DMAOMR_ST);
}

void ETH_DMAReceptionCmd(FunctionalState sta)
{
    sta ? (ETH->DMAOMR |= ETH_DMAOMR_SR) : (ETH->DMAOMR &= ~ETH_DMAOMR_SR);
}

FlagStatus ETH_GetDMAOverflowStatus(u32 val)
{
    return (FlagStatus)(ETH->DMAMFBOCR & val);
}

u32 ETH_GetRxOverflowMissedFrameCounter(void)
{
    return (ETH->DMAMFBOCR & ETH_DMAMFBOCR_MFA) >>
           ETH_DMA_RX_OVERFLOW_MISSEDFRAMES_COUNTERSHIFT;
}

u32 ETH_GetBufferUnavailableMissedFrameCounter(void)
{
    return ETH->DMAMFBOCR & ETH_DMAMFBOCR_MFC;
}

u32 ETH_GetCurrentTxDescStartAddress(void)
{
    return ETH->DMACHTDR;
}

u32 ETH_GetCurrentRxDescStartAddress(void)
{
    return ETH->DMACHRDR;
}

u32 ETH_GetCurrentTxBufferAddress(void)
{
    return ETH->DMACHTBAR;
}

u32 ETH_GetCurrentRxBufferAddress(void)
{
    return ETH->DMACHRBAR;
}

void ETH_ResumeDMATransmission(void)
{
    ETH->DMATPDR = 0;
}

void ETH_ResumeDMAReception(void)
{
    ETH->DMARPDR = 0;
}

void ETH_SetReceiveWatchdogTimer(u8 val)
{
    ETH->DMARSWTR = val;
}

////////////////////////////////////////////////////////////////////////////////
u16 ETH_ReadPHYRegister(u16 addr, u16 reg)
{
    u32 dat;
    // Set phy address and reg address, clear write flag
    ETH->MACMIIAR = (((ETH->MACMIIAR & ~MACMIIAR_CR_MASK) |
                      (addr << ETH_MACMIIAR_PA_Pos & ETH_MACMIIAR_PA) |
                      (reg  << ETH_MACMIIAR_MR_Pos & ETH_MACMIIAR_MR)) &
                     (~ETH_MACMIIAR_MW)) | ETH_MACMIIAR_MB;

    // Check busy flag
    while(ETH->MACMIIAR & ETH_MACMIIAR_MB);
    dat = (u16)ETH->MACMIIDR;
    if(dat == 0xFFFF) {
        dat = 0;
    }
    return dat;
}

u16 ETH_WritePHYRegister(u16 addr, u16 reg, u16 val)
{
    // Load data
    ETH->MACMIIDR = val;

    // Set phy address, reg address and write flag
    ETH->MACMIIAR = (ETH->MACMIIAR & ~MACMIIAR_CR_MASK) |
                    (addr << ETH_MACMIIAR_PA_Pos & ETH_MACMIIAR_PA) |
                    (reg  << ETH_MACMIIAR_MR_Pos & ETH_MACMIIAR_MR) |
                    ETH_MACMIIAR_MW |
                    ETH_MACMIIAR_MB;

    // Check busy flag
    while(ETH->MACMIIAR & ETH_MACMIIAR_MB);

    return ETH->MACMIIDR;
}

u32 ETH_PHYLoopBackCmd(u16 addr, FunctionalState sta)
{
    u16 temp_val = ETH_ReadPHYRegister(addr, PHY_BCR);

    sta ? (temp_val |= PHY_Loopback) : (temp_val &= ~PHY_Loopback);

    if(ETH_WritePHYRegister(addr, PHY_BCR, temp_val))
        return ETH_SUCCESS;

    return ETH_ERROR;
}

////////////////////////////////////////////////////////////////////////////////

void ETH_ResetWakeUpFrameFilterRegisterPointer(void)
{
    ETH->MACPMTCSR |= ETH_MACPMTCSR_WFFRPR;
}

void ETH_SetWakeUpFrameFilterRegister(u32* buf)
{
    u32 i = 0;

    for (i = 0; i < ETH_WAKEUP_REGISTER_LENGTH; i++) {
        ETH->MACRWUFFR = buf[i];
    }
}

void ETH_GlobalUnicastWakeUpCmd(FunctionalState sta)
{
    sta ?   (ETH->MACPMTCSR |= ETH_MACPMTCSR_GU) : (ETH->MACPMTCSR &= ~ETH_MACPMTCSR_GU);
}

FlagStatus ETH_GetPMTFlagStatus(u32 flag)
{
    return (FlagStatus)(ETH->MACPMTCSR & flag);
}

void ETH_WakeUpFrameDetectionCmd(FunctionalState sta)
{
    sta ? (ETH->MACPMTCSR |= ETH_MACPMTCSR_WFE) : (ETH->MACPMTCSR &= ~ETH_MACPMTCSR_WFE);
}

void ETH_MagicPacketDetectionCmd(FunctionalState sta)
{
    sta ? (ETH->MACPMTCSR |= ETH_MACPMTCSR_MPE) : (ETH->MACPMTCSR &= ~ETH_MACPMTCSR_MPE);
}

void ETH_PowerDownCmd(FunctionalState sta)
{
    sta ? (ETH->MACPMTCSR |= ETH_MACPMTCSR_PD) : (ETH->MACPMTCSR &= ~ETH_MACPMTCSR_PD);
}

////////////////////////////////////////////////////////////////////////////////

void ETH_MMCCounterFullPreset(void)
{
    ETH->MMCCR |= ETH_MMCCR_MCFHP | ETH_MMCCR_MCP;
}

void ETH_MMCCounterHalfPreset(void)
{
    ETH->MMCCR &= ~ETH_MMCCR_MCFHP;

    ETH->MMCCR |= ETH_MMCCR_MCP;
}

void ETH_MMCCounterFreezeCmd(FunctionalState sta)
{
    sta ? (ETH->MMCCR |= ETH_MMCCR_MCF) : (ETH->MMCCR &= ~ETH_MMCCR_MCF);
}

void ETH_MMCResetOnReadCmd(FunctionalState sta)
{
    sta ? (ETH->MMCCR |= ETH_MMCCR_ROR) : (ETH->MMCCR &= ~ETH_MMCCR_ROR);
}

void ETH_MMCCounterRolloverCmd(FunctionalState sta)
{
    sta ? (ETH->MMCCR &= ~ETH_MMCCR_CSR) : (ETH->MMCCR |= ETH_MMCCR_CSR);
}

void ETH_MMCCountersReset(void)
{
    ETH->MMCCR |= ETH_MMCCR_CR;
}

void ETH_MMCITConfig(u32 it, FunctionalState sta)
{
    if (it & 0x10000000) {
        it &= 0xEFFFFFFF;

        sta ? (ETH->MMCRIMR &= ~it) : (ETH->MMCRIMR |= it);
    }
    else {
        sta ? (ETH->MMCTIMR &= ~it) : (ETH->MMCTIMR |= it);
    }
}

ITStatus ETH_GetMMCITStatus(u32 it)
{
    if (it & 0x10000000) {
        return (ITStatus)((ETH->MMCRIR & it) && !(ETH->MMCRIMR & it));
    }
    else {
        return (ITStatus)((ETH->MMCTIR & it) && !(ETH->MMCTIMR & it));
    }
}

u32 ETH_GetMMCRegister(u32 reg)
{
    return *(vu32*)(ETH_BASE + reg);
}
