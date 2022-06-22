/********************************** (C) COPYRIGHT  *******************************
* File Name          : ch32f20x_eth.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/08/08
* Description        : This file provides all the ETH firmware functions.
*******************************************************************************/
#include "ch32f20x_eth.h"
#include "ch32f20x_rcc.h"

ETH_DMADESCTypeDef  *DMATxDescToSet;
ETH_DMADESCTypeDef  *DMARxDescToGet;
ETH_DMADESCTypeDef  *DMAPTPTxDescToSet;
ETH_DMADESCTypeDef  *DMAPTPRxDescToGet;

  
/*******************************************************************************
* Function Name  : ETH_DeInit
* Description    : ETH hardware initialize again.
* Input          : None.
* Return         : None
*******************************************************************************/
void ETH_DeInit(void)
{
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_ETH_MAC, ENABLE);
    RCC_AHBPeriphResetCmd(RCC_AHBPeriph_ETH_MAC, DISABLE);
}

/*******************************************************************************
* Function Name  : ETH_StructInit
* Description    : Fills each ETH_InitStruct member with its default value.
* Input          : ETH_InitStruct: pointer to a ETH_InitTypeDef structure which will be initialized.
* Return         : None
*******************************************************************************/
void ETH_StructInit(ETH_InitTypeDef* ETH_InitStruct)
{
  /*------------------------   MAC   -----------------------------------*/     
  ETH_InitStruct->ETH_AutoNegotiation = ETH_AutoNegotiation_Disable;           
  ETH_InitStruct->ETH_Watchdog = ETH_Watchdog_Enable;                   
  ETH_InitStruct->ETH_Jabber = ETH_Jabber_Enable;                                                     
  ETH_InitStruct->ETH_InterFrameGap = ETH_InterFrameGap_96Bit;                                                                                                                          
  ETH_InitStruct->ETH_CarrierSense = ETH_CarrierSense_Enable;                              
  ETH_InitStruct->ETH_Speed = ETH_Speed_10M;                       
  ETH_InitStruct->ETH_ReceiveOwn = ETH_ReceiveOwn_Enable;               
  ETH_InitStruct->ETH_LoopbackMode = ETH_LoopbackMode_Disable;              
  ETH_InitStruct->ETH_Mode = ETH_Mode_HalfDuplex;                       
  ETH_InitStruct->ETH_ChecksumOffload = ETH_ChecksumOffload_Disable;                                                            
  ETH_InitStruct->ETH_RetryTransmission = ETH_RetryTransmission_Enable;                                                                                  
  ETH_InitStruct->ETH_AutomaticPadCRCStrip = ETH_AutomaticPadCRCStrip_Disable;                                                         
  ETH_InitStruct->ETH_BackOffLimit = ETH_BackOffLimit_10;                                                                
  ETH_InitStruct->ETH_DeferralCheck = ETH_DeferralCheck_Disable;                                                                                                                  
  ETH_InitStruct->ETH_ReceiveAll = ETH_ReceiveAll_Disable;                                                               
  ETH_InitStruct->ETH_SourceAddrFilter = ETH_SourceAddrFilter_Disable;                                
  ETH_InitStruct->ETH_PassControlFrames = ETH_PassControlFrames_BlockAll;          
  ETH_InitStruct->ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Disable;
  ETH_InitStruct->ETH_DestinationAddrFilter = ETH_DestinationAddrFilter_Normal;      
  ETH_InitStruct->ETH_PromiscuousMode = ETH_PromiscuousMode_Disable;                                                             
  ETH_InitStruct->ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_Perfect;      
  ETH_InitStruct->ETH_UnicastFramesFilter = ETH_UnicastFramesFilter_Perfect;      
  ETH_InitStruct->ETH_HashTableHigh = 0x0;                
  ETH_InitStruct->ETH_HashTableLow = 0x0;                     
  ETH_InitStruct->ETH_PauseTime = 0x0;                 
  ETH_InitStruct->ETH_ZeroQuantaPause = ETH_ZeroQuantaPause_Disable;            
  ETH_InitStruct->ETH_PauseLowThreshold = ETH_PauseLowThreshold_Minus4;         
  ETH_InitStruct->ETH_UnicastPauseFrameDetect = ETH_UnicastPauseFrameDetect_Disable;   
  ETH_InitStruct->ETH_ReceiveFlowControl = ETH_ReceiveFlowControl_Disable;        
  ETH_InitStruct->ETH_TransmitFlowControl = ETH_TransmitFlowControl_Disable;      
  ETH_InitStruct->ETH_VLANTagComparison = ETH_VLANTagComparison_16Bit;          
  ETH_InitStruct->ETH_VLANTagIdentifier = 0x0;          
  /*------------------------   DMA   -----------------------------------*/  
  ETH_InitStruct->ETH_DropTCPIPChecksumErrorFrame = ETH_DropTCPIPChecksumErrorFrame_Disable; 
  ETH_InitStruct->ETH_ReceiveStoreForward = ETH_ReceiveStoreForward_Enable;       
  ETH_InitStruct->ETH_FlushReceivedFrame = ETH_FlushReceivedFrame_Enable;
  ETH_InitStruct->ETH_TransmitStoreForward = ETH_TransmitStoreForward_Enable;     
  ETH_InitStruct->ETH_TransmitThresholdControl = ETH_TransmitThresholdControl_64Bytes;  
  ETH_InitStruct->ETH_ForwardErrorFrames = ETH_ForwardErrorFrames_Disable;       
  ETH_InitStruct->ETH_ForwardUndersizedGoodFrames = ETH_ForwardUndersizedGoodFrames_Disable; 
  ETH_InitStruct->ETH_ReceiveThresholdControl = ETH_ReceiveThresholdControl_64Bytes;   
  ETH_InitStruct->ETH_SecondFrameOperate = ETH_SecondFrameOperate_Disable;
  ETH_InitStruct->ETH_AddressAlignedBeats = ETH_AddressAlignedBeats_Enable;
  ETH_InitStruct->ETH_FixedBurst = ETH_FixedBurst_Disable;
  ETH_InitStruct->ETH_RxDMABurstLength = ETH_RxDMABurstLength_1Beat;
  ETH_InitStruct->ETH_TxDMABurstLength = ETH_TxDMABurstLength_1Beat;
  ETH_InitStruct->ETH_DescriptorSkipLength = 0x0;
  ETH_InitStruct->ETH_DMAArbitration = ETH_DMAArbitration_RoundRobin_RxTx_1_1;
}

/*******************************************************************************
* Function Name  : ETH_Start
* Description    : Enables ENET MAC and DMA reception/transmission.
* Input          : None.
* Return         : None.
*******************************************************************************/
void ETH_Start(void)
{
  ETH_MACTransmissionCmd(ENABLE);
  ETH_FlushTransmitFIFO();
  ETH_MACReceptionCmd(ENABLE);
  ETH_DMATransmissionCmd(ENABLE); 
  ETH_DMAReceptionCmd(ENABLE);   
}

/*******************************************************************************
* Function Name  : ETH_HandleTxPkt
* Description    : Transmits a packet, from application buffer, pointed by ppkt.
* Input          : ppkt: pointer to the application's packet buffer to transmit.
*                  FrameLength: Tx Packet size.
* Return         : ETH_ERROR: in case of Tx desc owned by DMA.
*                  ETH_SUCCESS: for correct transmission.
*******************************************************************************/
uint32_t ETH_HandleTxPkt(uint8_t *ppkt, uint16_t FrameLength)
{ 
  uint32_t offset = 0;

  if((DMATxDescToSet->Status & ETH_DMATxDesc_OWN) != (uint32_t)RESET)
  {
    return ETH_ERROR;
  }

  for(offset=0; offset<FrameLength; offset++)       
  {
    (*(__IO uint8_t *)((DMATxDescToSet->Buffer1Addr) + offset)) = (*(ppkt + offset));
  }
        
  DMATxDescToSet->ControlBufferSize = (FrameLength & ETH_DMATxDesc_TBS1);
  DMATxDescToSet->Status |= ETH_DMATxDesc_LS | ETH_DMATxDesc_FS ;
  DMATxDescToSet->Status |= ETH_DMATxDesc_OWN;

  if((ETH->DMASR & ETH_DMASR_TBUS) != (uint32_t)RESET)
  {
    ETH->DMASR = ETH_DMASR_TBUS;
    ETH->DMATPDR = 0;
  }

  if((DMATxDescToSet->Status & ETH_DMATxDesc_TCH) != (uint32_t)RESET)
  {     
    DMATxDescToSet = (ETH_DMADESCTypeDef*) (DMATxDescToSet->Buffer2NextDescAddr);    
  }
  else
  {  
    if((DMATxDescToSet->Status & ETH_DMATxDesc_TER) != (uint32_t)RESET)
    {
      DMATxDescToSet = (ETH_DMADESCTypeDef*) (ETH->DMATDLAR);      
    }
    else
    {  
      DMATxDescToSet = (ETH_DMADESCTypeDef*) ((uint32_t)DMATxDescToSet + 0x10 + ((ETH->DMABMR & ETH_DMABMR_DSL) >> 2));      
    }
  }

  return ETH_SUCCESS;   
}

/*******************************************************************************
* Function Name  : ETH_HandleRxPkt
* Description    : Receives a packet and copies it to memory pointed by ppkt.
* Input          : ppkt: pointer to the application packet receive buffer.
* Return         : ETH_ERROR: if there is error in reception
*                  framelength: received packet size if packet reception is correct
*******************************************************************************/
uint32_t ETH_HandleRxPkt(uint8_t *ppkt)
{ 
  uint32_t offset = 0, framelength = 0;

  if((DMARxDescToGet->Status & ETH_DMARxDesc_OWN) != (uint32_t)RESET)
  {
    return ETH_ERROR; 
  }
  
  if(((DMARxDescToGet->Status & ETH_DMARxDesc_ES) == (uint32_t)RESET) && 
     ((DMARxDescToGet->Status & ETH_DMARxDesc_LS) != (uint32_t)RESET) &&  
     ((DMARxDescToGet->Status & ETH_DMARxDesc_FS) != (uint32_t)RESET))  
  {      
    framelength = ((DMARxDescToGet->Status & ETH_DMARxDesc_FL) >> ETH_DMARXDESC_FRAME_LENGTHSHIFT) - 4;

    for(offset=0; offset<framelength; offset++)       
    {
      (*(ppkt + offset)) = (*(__IO uint8_t *)((DMARxDescToGet->Buffer1Addr) + offset));
    }
  }
  else
  {
    framelength = ETH_ERROR;
  }

  DMARxDescToGet->Status = ETH_DMARxDesc_OWN; 

  if ((ETH->DMASR & ETH_DMASR_RBUS) != (uint32_t)RESET)  
  {
    ETH->DMASR = ETH_DMASR_RBUS;
    ETH->DMARPDR = 0;
  }
  
  if((DMARxDescToGet->ControlBufferSize & ETH_DMARxDesc_RCH) != (uint32_t)RESET)
  {     
    DMARxDescToGet = (ETH_DMADESCTypeDef*) (DMARxDescToGet->Buffer2NextDescAddr);    
  }
  else
  {   
    if((DMARxDescToGet->ControlBufferSize & ETH_DMARxDesc_RER) != (uint32_t)RESET)
    {
      DMARxDescToGet = (ETH_DMADESCTypeDef*) (ETH->DMARDLAR);      
    }
    else
    { 
      DMARxDescToGet = (ETH_DMADESCTypeDef*) ((uint32_t)DMARxDescToGet + 0x10 + ((ETH->DMABMR & ETH_DMABMR_DSL) >> 2));      
    }
  }
  
  return (framelength);  
}

/*******************************************************************************
* Function Name  : ETH_GetRxPktSize
* Description    : Get the size of received the received packet.
* Input          : None.
* Return         : framelength: received packet size
*******************************************************************************/
uint32_t ETH_GetRxPktSize(void)
{
  uint32_t frameLength = 0;
  if(((DMARxDescToGet->Status & ETH_DMARxDesc_OWN) == (uint32_t)RESET) &&
     ((DMARxDescToGet->Status & ETH_DMARxDesc_ES) == (uint32_t)RESET) &&
     ((DMARxDescToGet->Status & ETH_DMARxDesc_LS) != (uint32_t)RESET) &&
     ((DMARxDescToGet->Status & ETH_DMARxDesc_FS) != (uint32_t)RESET))
  {
    frameLength = ETH_GetDMARxDescFrameLength(DMARxDescToGet);
  }
 
 return frameLength;
}

/*******************************************************************************
* Function Name  : ETH_DropRxPkt
* Description    : Drop a Received packet.
* Input          : None.
* Return         : None
*******************************************************************************/
void ETH_DropRxPkt(void)
{
  DMARxDescToGet->Status = ETH_DMARxDesc_OWN;  

  if((DMARxDescToGet->ControlBufferSize & ETH_DMARxDesc_RCH) != (uint32_t)RESET)
  {
    DMARxDescToGet = (ETH_DMADESCTypeDef*) (DMARxDescToGet->Buffer2NextDescAddr);
  }
  else
  {
    if((DMARxDescToGet->ControlBufferSize & ETH_DMARxDesc_RER) != (uint32_t)RESET)
    {
      DMARxDescToGet = (ETH_DMADESCTypeDef*) (ETH->DMARDLAR);
    }
    else
    {
      DMARxDescToGet = (ETH_DMADESCTypeDef*) ((uint32_t)DMARxDescToGet + 0x10 + ((ETH->DMABMR & ETH_DMABMR_DSL) >> 2));
    }
  }
}

/*******************************************************************************
* Function Name  : ETH_ReadPHYRegister
* Description    : Read a PHY register.
* Input          : PHYAddress: PHY device address, is the index of one of supported 32 PHY devices.
*                  PHYReg: PHY register address, is the index of one of the 32 PHY register.
* Return         : ETH_ERROR: in case of timeout.
*                  MAC MIIDR register value: Data read from the selected PHY register.
*******************************************************************************/
uint16_t ETH_ReadPHYRegister(uint16_t PHYAddress, uint16_t PHYReg)
{
  uint32_t tmpreg = 0;     
  __IO uint32_t timeout = 0;
  
  tmpreg = ETH->MACMIIAR;
  tmpreg &= ~MACMIIAR_CR_MASK;
  tmpreg |=(((uint32_t)PHYAddress<<11) & ETH_MACMIIAR_PA);
  tmpreg |=(((uint32_t)PHYReg<<6) & ETH_MACMIIAR_MR);
  tmpreg &= ~ETH_MACMIIAR_MW;
  tmpreg |= ETH_MACMIIAR_MB;
  ETH->MACMIIAR = tmpreg;

  do
  {
    timeout++;
    tmpreg = ETH->MACMIIAR;
  } while ((tmpreg & ETH_MACMIIAR_MB) && (timeout < (uint32_t)PHY_READ_TO));

  if(timeout == PHY_READ_TO)
  {
    return (uint16_t)ETH_ERROR;
  }
  
  return (uint16_t)(ETH->MACMIIDR);
}

/*******************************************************************************
* Function Name  : ETH_WritePHYRegister
* Description    : Write to a PHY register.
* Input          : PHYAddress: PHY device address, is the index of one of supported 32 PHY devices.
*                  PHYReg: PHY register address, is the index of one of the 32 PHY register.
*                  PHYValue: the value to write.
* Return         : ETH_ERROR: in case of timeout.
*                  ETH_SUCCESS: for correct write
*******************************************************************************/
uint32_t ETH_WritePHYRegister(uint16_t PHYAddress, uint16_t PHYReg, uint16_t PHYValue)
{
  uint32_t tmpreg = 0;     
  __IO uint32_t timeout = 0;
  
  tmpreg = ETH->MACMIIAR;
  tmpreg &= ~MACMIIAR_CR_MASK;
  tmpreg |=(((uint32_t)PHYAddress<<11) & ETH_MACMIIAR_PA);
  tmpreg |=(((uint32_t)PHYReg<<6) & ETH_MACMIIAR_MR);
  tmpreg |= ETH_MACMIIAR_MW;
  tmpreg |= ETH_MACMIIAR_MB;
  ETH->MACMIIDR = PHYValue;
  ETH->MACMIIAR = tmpreg;

  do
  {
    timeout++;
    tmpreg = ETH->MACMIIAR;
  } while ((tmpreg & ETH_MACMIIAR_MB) && (timeout < (uint32_t)PHY_WRITE_TO));

  if(timeout >= PHY_WRITE_TO)
  {
    return ETH_ERROR;
  }

  return ETH_SUCCESS;  
}

/*******************************************************************************
* Function Name  : ETH_PHYLoopBackCmd
* Description    : Enables or disables the PHY loopBack mode.
* Input          : PHYAddress: PHY device address, is the index of one of supported 32 PHY devices.
*                  NewState: new state of the PHY loopBack mode.
* Return         : ETH_ERROR: in case of bad PHY configuration.
*                  ETH_SUCCESS: for correct PHY configuration.
*******************************************************************************/
uint32_t ETH_PHYLoopBackCmd(uint16_t PHYAddress, FunctionalState NewState)
{
  uint16_t tmpreg = 0;
    
  tmpreg = ETH_ReadPHYRegister(PHYAddress, PHY_BCR); 
  
  if (NewState != DISABLE)
  {
    tmpreg |= PHY_Loopback;  
  }
  else
  {
    tmpreg &= (uint16_t)(~(uint16_t)PHY_Loopback);
  }

  if(ETH_WritePHYRegister(PHYAddress, PHY_BCR, tmpreg) != (uint32_t)RESET)
  {
    return ETH_SUCCESS;
  }
  else
  {
    return ETH_ERROR; 
  }   
}

/*******************************************************************************
* Function Name  : ETH_MACTransmissionCmd
* Description    : Enables or disables the MAC transmission.
* Input          : NewState: new state of the MAC transmission.
* Return         : None.
*******************************************************************************/
void ETH_MACTransmissionCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->MACCR |= ETH_MACCR_TE;  
  }
  else
  {
    ETH->MACCR &= ~ETH_MACCR_TE;
  }
}

/*******************************************************************************
* Function Name  : ETH_MACReceptionCmd
* Description    : Enables or disables the MAC reception.
* Input          : NewState: new state of the MAC reception.
* Return         : None.
*******************************************************************************/
void ETH_MACReceptionCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->MACCR |= ETH_MACCR_RE;  
  }
  else
  {
    ETH->MACCR &= ~ETH_MACCR_RE;
  }
}

/*******************************************************************************
* Function Name  : ETH_GetFlowControlBusyStatus
* Description    : Enables or disables the MAC reception.
* Input          : None
* Return         : The new state of flow control busy status bit (SET or RESET)..
*******************************************************************************/
FlagStatus ETH_GetFlowControlBusyStatus(void)
{
  FlagStatus bitstatus = RESET;

  if ((ETH->MACFCR & ETH_MACFCR_FCBBPA) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : ETH_InitiatePauseControlFrame
* Description    : Initiate a Pause Control Frame (Full-duplex only).
* Input          : None.
* Return         : None.
*******************************************************************************/
void ETH_InitiatePauseControlFrame(void)  
{ 
  ETH->MACFCR |= ETH_MACFCR_FCBBPA;  
}

/*******************************************************************************
* Function Name  : ETH_BackPressureActivationCmd
* Description    : Enables or disables the MAC BackPressure operation activation (Half-duplex only).
* Input          : NewState: new state of the MAC BackPressure operation activation.
* Return         : None.
*******************************************************************************/
void ETH_BackPressureActivationCmd(FunctionalState NewState)   
{
  if (NewState != DISABLE)
  {
    ETH->MACFCR |= ETH_MACFCR_FCBBPA; 
  }
  else
  {
    ETH->MACFCR &= ~ETH_MACFCR_FCBBPA; 
  } 
}

/*******************************************************************************
* Function Name  : ETH_GetMACFlagStatus
* Description    : Checks whether the specified ETHERNET MAC flag is set or not.
* Input          : ETH_MAC_FLAG: specifies the flag to check.
* Return         : The new state of ETHERNET MAC flag (SET or RESET).
*******************************************************************************/
FlagStatus ETH_GetMACFlagStatus(uint32_t ETH_MAC_FLAG)
{
  FlagStatus bitstatus = RESET;

  if ((ETH->MACSR & ETH_MAC_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : ETH_GetMACITStatus
* Description    : Checks whether the specified ETHERNET MAC interrupt has occurred or not.
* Input          : ETH_MAC_IT: specifies the interrupt source to check.
* Return         : The new state of ETHERNET MAC interrupt (SET or RESET).
*******************************************************************************/
ITStatus ETH_GetMACITStatus(uint32_t ETH_MAC_IT)
{
    FlagStatus bitstatus = RESET;

    if ((ETH->MACSR & ETH_MAC_IT) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/*******************************************************************************
* Function Name  : ETH_MACITConfig
* Description    : Enables or disables the specified ETHERNET MAC interrupts.
* Input          : ETH_MAC_IT: specifies the ETHERNET MAC interrupt sources to be.
*                  NewState: new state of the specified ETHERNET MAC interrupts.
* Return         : None.
*******************************************************************************/
void ETH_MACITConfig(uint32_t ETH_MAC_IT, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->MACIMR &= (~(uint32_t)ETH_MAC_IT);
  }
  else
  {
    ETH->MACIMR |= ETH_MAC_IT;
  }
}

/*******************************************************************************
* Function Name  : ETH_MACAddressConfig
* Description    : Configures the selected MAC address.
* Input          : MacAddr: The MAC addres to configure.
*                  ETH_MAC_Address0 : MAC Address0
*                  ETH_MAC_Address1 : MAC Address1
*                  ETH_MAC_Address2 : MAC Address2
*                  ETH_MAC_Address3 : MAC Address3
*                  Addr: Pointer on MAC address buffer data (6 bytes).
* Return         : None.
*******************************************************************************/
void ETH_MACAddressConfig(uint32_t MacAddr, uint8_t *Addr)
{
  uint32_t tmpreg;
  
  tmpreg = ((uint32_t)Addr[5] << 8) | (uint32_t)Addr[4];
  (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + MacAddr)) = tmpreg;
  tmpreg = ((uint32_t)Addr[3] << 24) | ((uint32_t)Addr[2] << 16) | ((uint32_t)Addr[1] << 8) | Addr[0];
 
  (*(__IO uint32_t *) (ETH_MAC_ADDR_LBASE + MacAddr)) = tmpreg;
}

/*******************************************************************************
* Function Name  : ETH_GetMACAddress
* Description    : Get the selected MAC address.
* Input          : MacAddr: The MAC address to return.
*                  ETH_MAC_Address0 : MAC Address0
*                  ETH_MAC_Address1 : MAC Address1
*                  ETH_MAC_Address2 : MAC Address2
*                  ETH_MAC_Address3 : MAC Address3
*                  Addr: Pointer on MAC address buffer data (6 bytes).
* Return         : None.
*******************************************************************************/
void ETH_GetMACAddress(uint32_t MacAddr, uint8_t *Addr)
{
  uint32_t tmpreg;
  
  tmpreg =(*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + MacAddr));
 
  Addr[5] = ((tmpreg >> 8) & (uint8_t)0xFF);
  Addr[4] = (tmpreg & (uint8_t)0xFF);
  tmpreg =(*(__IO uint32_t *) (ETH_MAC_ADDR_LBASE + MacAddr));
  Addr[3] = ((tmpreg >> 24) & (uint8_t)0xFF);
  Addr[2] = ((tmpreg >> 16) & (uint8_t)0xFF);
  Addr[1] = ((tmpreg >> 8 ) & (uint8_t)0xFF);
  Addr[0] = (tmpreg & (uint8_t)0xFF);
}

/*******************************************************************************
* Function Name  : ETH_MACAddressPerfectFilterCmd
* Description    : Enables or disables the Address filter module uses the specified.
* Input          : MacAddr: The MAC address to return.
*                  ETH_MAC_Address1 : MAC Address1
*                  ETH_MAC_Address2 : MAC Address2
*                  ETH_MAC_Address3 : MAC Address3
*                  NewState: new state of the specified ETHERNET MAC address use.
* Return         : None.
*******************************************************************************/
void ETH_MACAddressPerfectFilterCmd(uint32_t MacAddr, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + MacAddr)) |= ETH_MACA1HR_AE;
  }
  else
  {
    (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + MacAddr)) &=(~(uint32_t)ETH_MACA1HR_AE);
  }
}

/*******************************************************************************
* Function Name  : ETH_MACAddressFilterConfig
* Description    : Set the filter type for the specified ETHERNET MAC address.
* Input          : MacAddr: specifies the ETHERNET MAC address.
*                  ETH_MAC_Address1 : MAC Address1
*                  ETH_MAC_Address2 : MAC Address2
*                  ETH_MAC_Address3 : MAC Address3
*                  Filter: specifies the used frame received field for comparaison.
*                  ETH_MAC_AddressFilter_SA : MAC Address is used to compare with the
*                                             SA fields of the received frame.
*                  ETH_MAC_AddressFilter_DA : MAC Address is used to compare with the
*                                             DA fields of the received frame.
* Return         : None.
*******************************************************************************/
void ETH_MACAddressFilterConfig(uint32_t MacAddr, uint32_t Filter)
{
  if (Filter != ETH_MAC_AddressFilter_DA)
  {
    (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + MacAddr)) |= ETH_MACA1HR_SA;
  }
  else
  {
    (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + MacAddr)) &=(~(uint32_t)ETH_MACA1HR_SA);
  }
}

/*******************************************************************************
* Function Name  : ETH_MACAddressMaskBytesFilterConfig
* Description    : Set the filter type for the specified ETHERNET MAC address.
* Input          : MacAddr: specifies the ETHERNET MAC address.
*                  ETH_MAC_Address1 : MAC Address1
*                  ETH_MAC_Address2 : MAC Address2
*                  ETH_MAC_Address3 : MAC Address3
*                  MaskByte: specifies the used address bytes for comparaison
*                  ETH_MAC_AddressMask_Byte5 : Mask MAC Address high reg bits [7:0].
*                  ETH_MAC_AddressMask_Byte4 : Mask MAC Address low reg bits [31:24].
*                  ETH_MAC_AddressMask_Byte3 : Mask MAC Address low reg bits [23:16].
*                  ETH_MAC_AddressMask_Byte2 : Mask MAC Address low reg bits [15:8].
*                  ETH_MAC_AddressMask_Byte1 : Mask MAC Address low reg bits [7:0].
* Return         : None.
*******************************************************************************/
void ETH_MACAddressMaskBytesFilterConfig(uint32_t MacAddr, uint32_t MaskByte)
{
  (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + MacAddr)) &=(~(uint32_t)ETH_MACA1HR_MBC);
  (*(__IO uint32_t *) (ETH_MAC_ADDR_HBASE + MacAddr)) |= MaskByte;
}

/*******************************************************************************
* Function Name  : ETH_DMATxDescChainInit
* Description    : Initializes the DMA Tx descriptors in chain mode.
* Input          : DMATxDescTab: Pointer on the first Tx desc list
*                  TxBuff: Pointer on the first TxBuffer list
*                  TxBuffCount: Number of the used Tx desc in the list
* Return         : None.
*******************************************************************************/
void ETH_DMATxDescChainInit(ETH_DMADESCTypeDef *DMATxDescTab, uint8_t* TxBuff, uint32_t TxBuffCount)
{
  uint32_t i = 0;
  ETH_DMADESCTypeDef *DMATxDesc;
  
  DMATxDescToSet = DMATxDescTab;

  for(i=0; i < TxBuffCount; i++)
  {
    DMATxDesc = DMATxDescTab + i;
    DMATxDesc->Status = ETH_DMATxDesc_TCH;
    DMATxDesc->Buffer1Addr = (uint32_t)(&TxBuff[i*ETH_MAX_PACKET_SIZE]);
    
    if(i < (TxBuffCount-1))
    {
      DMATxDesc->Buffer2NextDescAddr = (uint32_t)(DMATxDescTab+i+1);
    }
    else
    {
      DMATxDesc->Buffer2NextDescAddr = (uint32_t) DMATxDescTab;  
    }
  }
   
  ETH->DMATDLAR = (uint32_t) DMATxDescTab;
}

/*******************************************************************************
* Function Name  : ETH_DMATxDescRingInit
* Description    : Initializes the DMA Tx descriptors in ring mode.
* Input          : DMATxDescTab: Pointer on the first Tx desc list.
*                  TxBuff1: Pointer on the first TxBuffer1 list.
*                  TxBuff2: Pointer on the first TxBuffer2 list.
*                  TxBuffCount: Number of the used Tx desc in the list.
* Return         : None.
*******************************************************************************/
void ETH_DMATxDescRingInit(ETH_DMADESCTypeDef *DMATxDescTab, uint8_t *TxBuff1, uint8_t *TxBuff2, uint32_t TxBuffCount)
{
  uint32_t i = 0;
  ETH_DMADESCTypeDef *DMATxDesc;
 
  DMATxDescToSet = DMATxDescTab;

  for(i=0; i < TxBuffCount; i++)
  {
    DMATxDesc = DMATxDescTab + i;
    DMATxDesc->Buffer1Addr = (uint32_t)(&TxBuff1[i*ETH_MAX_PACKET_SIZE]);
    DMATxDesc->Buffer2NextDescAddr = (uint32_t)(&TxBuff2[i*ETH_MAX_PACKET_SIZE]);
    
    if(i == (TxBuffCount-1))
    {
      DMATxDesc->Status = ETH_DMATxDesc_TER;
    }
  }
   
  ETH->DMATDLAR =  (uint32_t) DMATxDescTab;
}

/*******************************************************************************
* Function Name  : ETH_GetDMATxDescFlagStatus
* Description    : Checks whether the specified ETHERNET DMA Tx Desc flag is set or not.
* Input          : DMATxDesc: pointer on a DMA Tx descriptor
*                  ETH_DMATxDescFlag: specifies the flag to check.
*                  TxBuff2: Pointer on the first TxBuffer2 list.
*                  TxBuffCount: Number of the used Tx desc in the list.
*                  ETH_DMATxDesc_OWN : OWN bit: descriptor is owned by DMA engine
*                  ETH_DMATxDesc_IC  : Interrupt on completetion
*                  ETH_DMATxDesc_LS  : Last Segment
*                  ETH_DMATxDesc_FS  : First Segment
*                   ETH_DMATxDesc_DC  : Disable CRC
*                  ETH_DMATxDesc_DP  : Disable Pad
*                  ETH_DMATxDesc_TTSE: Transmit Time Stamp Enable
*                  ETH_DMATxDesc_TER : Transmit End of Ring
*                  ETH_DMATxDesc_TCH : Second Address Chained
*                  ETH_DMATxDesc_TTSS: Tx Time Stamp Status
*                  ETH_DMATxDesc_IHE : IP Header Error
*                  ETH_DMATxDesc_ES  : Error summary
*                  ETH_DMATxDesc_JT  : Jabber Timeout
*                  ETH_DMATxDesc_FF  : Frame Flushed: DMA/MTL flushed the frame due to SW flush
*                  ETH_DMATxDesc_PCE : Payload Checksum Error
*                  ETH_DMATxDesc_LCA : Loss of Carrier: carrier lost during tramsmission
*                  ETH_DMATxDesc_NC  : No Carrier: no carrier signal from the tranceiver
*                  ETH_DMATxDesc_LCO : Late Collision: transmission aborted due to collision
*                  ETH_DMATxDesc_EC  : Excessive Collision: transmission aborted after 16 collisions
*                  ETH_DMATxDesc_VF  : VLAN Frame
*                  ETH_DMATxDesc_CC  : Collision Count
*                  ETH_DMATxDesc_ED  : Excessive Deferral
*                  ETH_DMATxDesc_UF  : Underflow Error: late data arrival from the memory
*                  ETH_DMATxDesc_DB  : Deferred Bit
* Return         : The new state of ETH_DMATxDescFlag (SET or RESET).
*******************************************************************************/
FlagStatus ETH_GetDMATxDescFlagStatus(ETH_DMADESCTypeDef *DMATxDesc, uint32_t ETH_DMATxDescFlag)
{
    FlagStatus bitstatus = RESET;

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

/*******************************************************************************
* Function Name  : ETH_GetDMATxDescCollisionCount
* Description    : Returns the specified ETHERNET DMA Tx Desc collision count.
* Input          : pointer on a DMA Tx descriptor.
* Return         : The Transmit descriptor collision counter value.
*******************************************************************************/
uint32_t ETH_GetDMATxDescCollisionCount(ETH_DMADESCTypeDef *DMATxDesc)
{
  return ((DMATxDesc->Status & ETH_DMATxDesc_CC) >> ETH_DMATXDESC_COLLISION_COUNTSHIFT);
}


/*******************************************************************************
* Function Name  : ETH_SetDMATxDescOwnBit
* Description    : Set the specified DMA Tx Desc Own bit.
* Input          : DMATxDesc: Pointer on a Tx desc
* Return         : None
*******************************************************************************/
void ETH_SetDMATxDescOwnBit(ETH_DMADESCTypeDef *DMATxDesc)
{
  DMATxDesc->Status |= ETH_DMATxDesc_OWN;
}

/*******************************************************************************
* Function Name  : ETH_DMATxDescTransmitITConfig
* Description    : Enables or disables the specified DMA Tx Desc Transmit interrupt.
* Input          : Pointer on a Tx desc.
*                  NewState: new state of the DMA Tx Desc transmit interrupt.
* Return         : None.
*******************************************************************************/
void ETH_DMATxDescTransmitITConfig(ETH_DMADESCTypeDef *DMATxDesc, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DMATxDesc->Status |= ETH_DMATxDesc_IC;
  }
  else
  {
    DMATxDesc->Status &=(~(uint32_t)ETH_DMATxDesc_IC);
  }
}

/*******************************************************************************
* Function Name  : ETH_DMATxDescFrameSegmentConfig
* Description    : Enables or disables the specified DMA Tx Desc Transmit interrupt.
* Input          : PDMATxDesc: Pointer on a Tx desc.
*                  ETH_DMATxDesc_FirstSegment : actual Tx desc contain first segment.
* Return         : None.
*******************************************************************************/
void ETH_DMATxDescFrameSegmentConfig(ETH_DMADESCTypeDef *DMATxDesc, uint32_t DMATxDesc_FrameSegment)
{
  DMATxDesc->Status |= DMATxDesc_FrameSegment;
}

/*******************************************************************************
* Function Name  : ETH_DMATxDescChecksumInsertionConfig
* Description    : Selects the specified ETHERNET DMA Tx Desc Checksum Insertion.
* Input          : DMATxDesc: pointer on a DMA Tx descriptor.
*                  DMATxDesc_Checksum: specifies is the DMA Tx desc checksum insertion.
* Return         : None.
*******************************************************************************/
void ETH_DMATxDescChecksumInsertionConfig(ETH_DMADESCTypeDef *DMATxDesc, uint32_t DMATxDesc_Checksum)
{
  DMATxDesc->Status |= DMATxDesc_Checksum;
}

/*******************************************************************************
* Function Name  : ETH_DMATxDescCRCCmd
* Description    : Enables or disables the DMA Tx Desc CRC.
* Input          : DMATxDesc: pointer on a DMA Tx descriptor
*                  NewState: new state of the specified DMA Tx Desc CRC.
* Return         : None.
*******************************************************************************/
void ETH_DMATxDescCRCCmd(ETH_DMADESCTypeDef *DMATxDesc, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DMATxDesc->Status &= (~(uint32_t)ETH_DMATxDesc_DC);
  }
  else
  {
    DMATxDesc->Status |= ETH_DMATxDesc_DC; 
  }
}

/*******************************************************************************
* Function Name  : ETH_DMATxDescEndOfRingCmd
* Description    :Enables or disables the DMA Tx Desc end of ring.
* Input          : DMATxDesc: pointer on a DMA Tx descriptor.
*                  NewState: new state of the specified DMA Tx Desc end of ring.
* Return         : None.
*******************************************************************************/
void ETH_DMATxDescEndOfRingCmd(ETH_DMADESCTypeDef *DMATxDesc, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DMATxDesc->Status |= ETH_DMATxDesc_TER;  
  }
  else
  {
    DMATxDesc->Status &= (~(uint32_t)ETH_DMATxDesc_TER); 
  }
}

/*******************************************************************************
* Function Name  : ETH_DMATxDescSecondAddressChainedCmd
* Description    : Enables or disables the DMA Tx Desc second address chained.
* Input          : DMATxDesc: pointer on a DMA Tx descriptor
*                  NewState: new state of the specified DMA Tx Desc second address chained.
* Return         : None.
*******************************************************************************/
void ETH_DMATxDescSecondAddressChainedCmd(ETH_DMADESCTypeDef *DMATxDesc, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DMATxDesc->Status |= ETH_DMATxDesc_TCH;  
  }
  else
  {
    DMATxDesc->Status &=(~(uint32_t)ETH_DMATxDesc_TCH); 
  }
}

/*******************************************************************************
* Function Name  : ETH_DMATxDescShortFramePaddingCmd
* Description    : Enables or disables the DMA Tx Desc padding for frame shorter than 64 bytes.
* Input          : DMATxDesc: pointer on a DMA Tx descriptor.
*                  NewState: new state of the specified DMA Tx Desc padding for frame shorter than 64 bytes.
* Return         : None.
*******************************************************************************/
void ETH_DMATxDescShortFramePaddingCmd(ETH_DMADESCTypeDef *DMATxDesc, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DMATxDesc->Status &= (~(uint32_t)ETH_DMATxDesc_DP);
  }
  else
  {
    DMATxDesc->Status |= ETH_DMATxDesc_DP; 
  }
}

/*******************************************************************************
* Function Name  : ETH_DMATxDescTimeStampCmd
* Description    : Enables or disables the DMA Tx Desc time stamp.
* Input          : DMATxDesc: pointer on a DMA Tx descriptor
*                  NewState: new state of the specified DMA Tx Desc time stamp.
* Return         : None.
*******************************************************************************/
void ETH_DMATxDescTimeStampCmd(ETH_DMADESCTypeDef *DMATxDesc, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DMATxDesc->Status |= ETH_DMATxDesc_TTSE;  
  }
  else
  {
    DMATxDesc->Status &=(~(uint32_t)ETH_DMATxDesc_TTSE); 
  }
}

/*******************************************************************************
* Function Name  : ETH_DMATxDescBufferSizeConfig
* Description    : Configures the specified DMA Tx Desc buffer1 and buffer2 sizes.
* Input          : DMATxDesc: Pointer on a Tx desc.
*                  BufferSize1: specifies the Tx desc buffer1 size.
*                  RxBuff2: Pointer on the first RxBuffer2 list
*                  BufferSize2: specifies the Tx desc buffer2 size (put "0" if not used).
* Return         : None.
*******************************************************************************/
void ETH_DMATxDescBufferSizeConfig(ETH_DMADESCTypeDef *DMATxDesc, uint32_t BufferSize1, uint32_t BufferSize2)
{
  DMATxDesc->ControlBufferSize |= (BufferSize1 | (BufferSize2 << ETH_DMATXDESC_BUFFER2_SIZESHIFT));
}

/*******************************************************************************
* Function Name  : ETH_DMARxDescChainInit
* Description    : Initializes the DMA Rx descriptors in chain mode.
* Input          : DMARxDescTab: Pointer on the first Rx desc list.
*                  RxBuff: Pointer on the first RxBuffer list.
*                  RxBuffCount: Number of the used Rx desc in the list.
* Return         : None.
*******************************************************************************/
void ETH_DMARxDescChainInit(ETH_DMADESCTypeDef *DMARxDescTab, uint8_t *RxBuff, uint32_t RxBuffCount)
{
  uint32_t i = 0;
  ETH_DMADESCTypeDef *DMARxDesc;
  
  DMARxDescToGet = DMARxDescTab; 

  for(i=0; i < RxBuffCount; i++)
  {
    DMARxDesc = DMARxDescTab+i;
    DMARxDesc->Status = ETH_DMARxDesc_OWN;
    DMARxDesc->ControlBufferSize = ETH_DMARxDesc_RCH | (uint32_t)ETH_MAX_PACKET_SIZE;  
    DMARxDesc->Buffer1Addr = (uint32_t)(&RxBuff[i*ETH_MAX_PACKET_SIZE]);
    
    if(i < (RxBuffCount-1))
    {
      DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab+i+1); 
    }
    else
    {
      DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab); 
    }
  }
   
  ETH->DMARDLAR = (uint32_t) DMARxDescTab;  

}

/*******************************************************************************
* Function Name  : ETH_DMARxDescRingInit
* Description    : Initializes the DMA Rx descriptors in ring mode.
* Input          : DMARxDescTab: Pointer on the first Rx desc list.
*                  RxBuff1: Pointer on the first RxBuffer1 list.
*                  RxBuff2: Pointer on the first RxBuffer2 list
*                  RxBuffCount: Number of the used Rx desc in the list.
* Return         : None.
*******************************************************************************/
void ETH_DMARxDescRingInit(ETH_DMADESCTypeDef *DMARxDescTab, uint8_t *RxBuff1, uint8_t *RxBuff2, uint32_t RxBuffCount)
{
  uint32_t i = 0;
  ETH_DMADESCTypeDef *DMARxDesc;

  DMARxDescToGet = DMARxDescTab; 

  for(i=0; i < RxBuffCount; i++)
  {
    DMARxDesc = DMARxDescTab+i; 
    DMARxDesc->Status = ETH_DMARxDesc_OWN; 
    DMARxDesc->ControlBufferSize = ETH_MAX_PACKET_SIZE;  
    DMARxDesc->Buffer1Addr = (uint32_t)(&RxBuff1[i*ETH_MAX_PACKET_SIZE]);
    DMARxDesc->Buffer2NextDescAddr = (uint32_t)(&RxBuff2[i*ETH_MAX_PACKET_SIZE]); 
    
    if(i == (RxBuffCount-1))
    {
      DMARxDesc->ControlBufferSize |= ETH_DMARxDesc_RER;
    }
  }
   
  ETH->DMARDLAR = (uint32_t) DMARxDescTab;  
}

/*******************************************************************************
* Function Name  : ETH_GetDMARxDescFlagStatus
* Description    : Checks whether the specified ETHERNET Rx Desc flag is set or not.
* Input          : DMARxDesc: pointer on a DMA Rx descriptor.
*                  ETH_DMARxDescFlag: specifies the flag to check.
*                  ETH_DMARxDesc_OWN:         OWN bit: descriptor is owned by DMA engine
*                  ETH_DMARxDesc_AFM:         DA Filter Fail for the rx frame
*                  ETH_DMARxDesc_ES:          Error summary
*                  ETH_DMARxDesc_DE:          Desciptor error: no more descriptors for receive frame
*                  ETH_DMARxDesc_SAF:         SA Filter Fail for the received frame
*                  ETH_DMARxDesc_LE:          Frame size not matching with length field
*                  ETH_DMARxDesc_OE:          Overflow Error: Frame was damaged due to buffer overflow
*                  ETH_DMARxDesc_VLAN:        VLAN Tag: received frame is a VLAN frame
*                  ETH_DMARxDesc_FS:          First descriptor of the frame
*                  ETH_DMARxDesc_LS:          Last descriptor of the frame
*                  ETH_DMARxDesc_IPV4HCE:     IPC Checksum Error/Giant Frame: Rx Ipv4 header checksum error
*                  ETH_DMARxDesc_LC:          Late collision occurred during reception
*                  ETH_DMARxDesc_FT:          Frame type - Ethernet, otherwise 802.3
*                  ETH_DMARxDesc_RWT:         Receive Watchdog Timeout: watchdog timer expired during reception
*                  ETH_DMARxDesc_RE:          Receive error: error reported by MII interface
*                  ETH_DMARxDesc_DE:          Dribble bit error: frame contains non int multiple of 8 bits
*                  ETH_DMARxDesc_CE:          CRC error
*                  ETH_DMARxDesc_MAMPCE:      Rx MAC Address/Payload Checksum Error: Rx MAC address matched/ Rx Payload Checksum Error
* Return         : The new state of ETH_DMARxDescFlag (SET or RESET).
*******************************************************************************/
FlagStatus ETH_GetDMARxDescFlagStatus(ETH_DMADESCTypeDef *DMARxDesc, uint32_t ETH_DMARxDescFlag)
{
    FlagStatus bitstatus = RESET;

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

/*******************************************************************************
* Function Name  : ETH_SetDMARxDescOwnBit
* Description    : Set the specified DMA Rx Desc Own bit.
* Input          : DMARxDesc: Pointer on a Rx desc
* Return         : None.
*******************************************************************************/
void ETH_SetDMARxDescOwnBit(ETH_DMADESCTypeDef *DMARxDesc)
{
  DMARxDesc->Status |= ETH_DMARxDesc_OWN;
}

/*******************************************************************************
* Function Name  : ETH_GetDMARxDescFrameLength
* Description    : Returns the specified DMA Rx Desc frame length.
* Input          : DMARxDesc: pointer on a DMA Rx descriptor
* Return         : The Rx descriptor received frame length.
*******************************************************************************/
uint32_t ETH_GetDMARxDescFrameLength(ETH_DMADESCTypeDef *DMARxDesc)
{
  return ((DMARxDesc->Status & ETH_DMARxDesc_FL) >> ETH_DMARXDESC_FRAME_LENGTHSHIFT);
}

/*******************************************************************************
* Function Name  : ETH_DMARxDescReceiveITConfig
* Description    : Enables or disables the specified DMA Rx Desc receive interrupt.
* Input          : DMARxDesc: Pointer on a Rx desc
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void ETH_DMARxDescReceiveITConfig(ETH_DMADESCTypeDef *DMARxDesc, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DMARxDesc->ControlBufferSize &=(~(uint32_t)ETH_DMARxDesc_DIC);
  }
  else
  {
    DMARxDesc->ControlBufferSize |= ETH_DMARxDesc_DIC;
  }
}

/*******************************************************************************
* Function Name  : ETH_DMARxDescEndOfRingCmd
* Description    : Enables or disables the DMA Rx Desc end of ring.
* Input          : DMARxDesc: pointer on a DMA Rx descriptor.
*                  NewState: new state of the specified DMA Rx Desc end of ring.
* Return         : None.
*******************************************************************************/
void ETH_DMARxDescEndOfRingCmd(ETH_DMADESCTypeDef *DMARxDesc, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DMARxDesc->ControlBufferSize |= ETH_DMARxDesc_RER;  
  }
  else
  {
    DMARxDesc->ControlBufferSize &=(~(uint32_t)ETH_DMARxDesc_RER); 
  }
}

/*******************************************************************************
* Function Name  : ETH_DMARxDescSecondAddressChainedCmd
* Description    : Returns the specified ETHERNET DMA Rx Desc buffer size.
* Input          : DMARxDesc: pointer on a DMA Rx descriptor
*                  NewState: new state of the specified DMA Rx Desc second address chained.
* Return         : None.
*******************************************************************************/
void ETH_DMARxDescSecondAddressChainedCmd(ETH_DMADESCTypeDef *DMARxDesc, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    DMARxDesc->ControlBufferSize |= ETH_DMARxDesc_RCH;  
  }
  else
  {
    DMARxDesc->ControlBufferSize &=(~(uint32_t)ETH_DMARxDesc_RCH); 
  }
}

/*******************************************************************************
* Function Name  : ETH_GetDMARxDescBufferSize
* Description    : Returns the specified ETHERNET DMA Rx Desc buffer size.
* Input          : DMARxDesc: pointer on a DMA Rx descriptor.
*                  DMARxDesc_Buffer: specifies the DMA Rx Desc buffer.
*                  ETH_DMARxDesc_Buffer1 : DMA Rx Desc Buffer1
*                  ETH_DMARxDesc_Buffer2 : DMA Rx Desc Buffer2
* Return         : The Receive descriptor frame length.
*******************************************************************************/
uint32_t ETH_GetDMARxDescBufferSize(ETH_DMADESCTypeDef *DMARxDesc, uint32_t DMARxDesc_Buffer)
{
  if(DMARxDesc_Buffer != ETH_DMARxDesc_Buffer1)
  {
    return ((DMARxDesc->ControlBufferSize & ETH_DMARxDesc_RBS2) >> ETH_DMARXDESC_BUFFER2_SIZESHIFT); 
  }
  else
  {
    return (DMARxDesc->ControlBufferSize & ETH_DMARxDesc_RBS1); 
  }
}

/*******************************************************************************
* Function Name  : ETH_SoftwareReset
* Description    : Resets all MAC subsystem internal registers and logic.
* Input          : None.
* Return         : None.
*******************************************************************************/
void ETH_SoftwareReset(void)
{
  ETH->DMABMR |= ETH_DMABMR_SR;
}

/*******************************************************************************
* Function Name  : ETH_GetSoftwareResetStatus
* Description    : Checks whether the ETHERNET software reset bit is set or not.
* Input          : None.
* Return         : The new state of DMA Bus Mode register SR bit (SET or RESET).
*******************************************************************************/
FlagStatus ETH_GetSoftwareResetStatus(void)
{
  FlagStatus bitstatus = RESET;
  if((ETH->DMABMR & ETH_DMABMR_SR) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else 
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/*******************************************************************************
* Function Name  : ETH_GetlinkStaus
* Description    : Checks whether the internal 10BASE-T PHY is link or not.
* Input          : None.
* Return         : Internal 10BASE-T PHY is link or not.
*******************************************************************************/
FlagStatus ETH_GetlinkStaus (void)
{
    FlagStatus bitstatus = RESET;

    if((ETH->DMASR & 0x80000000) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/*******************************************************************************
* Function Name  : ETH_GetDMAFlagStatus
* Description    : Checks whether the specified ETHERNET DMA flag is set or not.
* Input          : ETH_DMA_FLAG: specifies the flag to check.
*                  ETH_DMA_FLAG_TST : Time-stamp trigger flag
*                  ETH_DMA_FLAG_PMT : PMT flag
*                  ETH_DMA_FLAG_MMC : MMC flag
*                  ETH_DMA_FLAG_DataTransferError : Error bits 0-data buffer, 1-desc. access
*                  ETH_DMA_FLAG_ReadWriteError    : Error bits 0-write trnsf, 1-read transfr
*                  ETH_DMA_FLAG_AccessError       : Error bits 0-Rx DMA, 1-Tx DMA
*                  ETH_DMA_FLAG_NIS : Normal interrupt summary flag
*                  ETH_DMA_FLAG_AIS : Abnormal interrupt summary flag
*                  ETH_DMA_FLAG_ER  : Early receive flag
*                  ETH_DMA_FLAG_FBE : Fatal bus error flag
*                  ETH_DMA_FLAG_ET  : Early transmit flag
*                  ETH_DMA_FLAG_RWT : Receive watchdog timeout flag
*                  ETH_DMA_FLAG_RPS : Receive process stopped flag
*                  ETH_DMA_FLAG_RBU : Receive buffer unavailable flag
*                  ETH_DMA_FLAG_R   : Receive flag
*                  ETH_DMA_FLAG_TU  : Underflow flag
*                  ETH_DMA_FLAG_RO  : Overflow flag
*                  ETH_DMA_FLAG_TJT : Transmit jabber timeout flag
*                  ETH_DMA_FLAG_TBU : Transmit buffer unavailable flag
*                  ETH_DMA_FLAG_TPS : Transmit process stopped flag
*                  ETH_DMA_FLAG_T   : Transmit flag
* Return         : The new state of ETH_DMA_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus ETH_GetDMAFlagStatus(uint32_t ETH_DMA_FLAG)
{  
  FlagStatus bitstatus = RESET;

  if ((ETH->DMASR & ETH_DMA_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : ETH_DMAClearFlag
* Description    : Checks whether the specified ETHERNET DMA interrupt has occured or not.
* Input          : ETH_DMA_FLAG: specifies the flag to clear.
*                  ETH_DMA_FLAG_NIS : Normal interrupt summary flag
*                  ETH_DMA_FLAG_AIS : Abnormal interrupt summary flag
*                  ETH_DMA_FLAG_ER  : Early receive flag
*                  ETH_DMA_FLAG_FBE : Fatal bus error flag
*                  ETH_DMA_FLAG_ETI : Early transmit flag
*                  ETH_DMA_FLAG_RWT : Receive watchdog timeout flag
*                  ETH_DMA_FLAG_RPS : Receive process stopped flag
*                  ETH_DMA_FLAG_RBU : Receive buffer unavailable flag
*                  ETH_DMA_FLAG_R   : Receive flag
*                  ETH_DMA_FLAG_TU  : Transmit Underflow flag
*                  ETH_DMA_FLAG_RO  : Receive Overflow flag
*                  ETH_DMA_FLAG_TJT : Transmit jabber timeout flag
*                  ETH_DMA_FLAG_TBU : Transmit buffer unavailable flag
*                  ETH_DMA_FLAG_TPS : Transmit process stopped flag
*                  ETH_DMA_FLAG_T   : Transmit flag
* Return         : None.
*******************************************************************************/
void ETH_DMAClearFlag(uint32_t ETH_DMA_FLAG)
{
  ETH->DMASR = (uint32_t) ETH_DMA_FLAG;
}

/*******************************************************************************
* Function Name  : ETH_GetDMAITStatus
* Description    : Checks whether the specified ETHERNET DMA interrupt has occured or not.
* Input          : ETH_DMA_IT: specifies the interrupt pending bit to clear.
*                  ETH_DMA_IT_TST : Time-stamp trigger interrupt
*                  ETH_DMA_IT_PMT : PMT interrupt
*                  ETH_DMA_IT_MMC : MMC interrupt
*                  ETH_DMA_IT_NIS : Normal interrupt summary
*                  ETH_DMA_IT_AIS : Abnormal interrupt summary
*                  ETH_DMA_IT_ER  : Early receive interrupt
*                  ETH_DMA_IT_FBE : Fatal bus error interrupt
*                  ETH_DMA_IT_ET  : Early transmit interrupt
*                  ETH_DMA_IT_RWT : Receive watchdog timeout interrupt
*                  ETH_DMA_IT_RPS : Receive process stopped interrupt
*                  ETH_DMA_IT_RBU : Receive buffer unavailable interrupt
*                  ETH_DMA_IT_R   : Receive interrupt
*                  ETH_DMA_IT_TU  : Underflow interrupt
*                  ETH_DMA_IT_RO  : Overflow interrupt
*                  ETH_DMA_IT_TJT : Transmit jabber timeout interrupt
*                  ETH_DMA_IT_TBU : Transmit buffer unavailable interrupt
*                  ETH_DMA_IT_TPS : Transmit process stopped interrupt
*                  ETH_DMA_IT_T   : Transmit interrupt
* Return         : The new state of ETH_DMA_IT (SET or RESET).
*******************************************************************************/
ITStatus ETH_GetDMAITStatus(uint32_t ETH_DMA_IT)
{  
  ITStatus bitstatus = RESET;

  if ((ETH->DMASR & ETH_DMA_IT) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : ETH_DMAClearITPendingBit
* Description    : Clears the ETHERNET’s DMA IT pending bit.
* Input          : ETH_DMA_IT: specifies the interrupt pending bit to clear.
*                  ETH_DMA_IT_NIS : Normal interrupt summary
*                  ETH_DMA_IT_AIS : Abnormal interrupt summary
*                  ETH_DMA_IT_ER  : Early receive interrupt
*                  ETH_DMA_IT_FBE : Fatal bus error interrupt
*                  ETH_DMA_IT_ETI : Early transmit interrupt
*                  ETH_DMA_IT_RWT : Receive watchdog timeout interrupt
*                  ETH_DMA_IT_RPS : Receive process stopped interrupt
*                  ETH_DMA_IT_RBU : Receive buffer unavailable interrupt
*                  ETH_DMA_IT_R   : Receive interrupt
*                  ETH_DMA_IT_TU  : Transmit Underflow interrupt
*                  ETH_DMA_IT_RO  : Receive Overflow interrupt
*                  ETH_DMA_IT_TJT : Transmit jabber timeout interrupt
*                  ETH_DMA_IT_TBU : Transmit buffer unavailable interrupt
*                  ETH_DMA_IT_TPS : Transmit process stopped interrupt
*                  ETH_DMA_IT_T   : Transmit interrupt
* Return         : None
*******************************************************************************/
void ETH_DMAClearITPendingBit(uint32_t ETH_DMA_IT)
{
  ETH->DMASR = (uint32_t) ETH_DMA_IT;
}

/*******************************************************************************
* Function Name  : ETH_GetTransmitProcessState
* Description    : Returns the ETHERNET DMA Transmit Process State.
* Input          : None.
* Return         : The new ETHERNET DMA Transmit Process State:
*                  ETH_DMA_TransmitProcess_Stopped   : Stopped - Reset or Stop Tx Command issued
*                  ETH_DMA_TransmitProcess_Fetching  : Running - fetching the Tx descriptor
*                  ETH_DMA_TransmitProcess_Waiting   : Running - waiting for status
*                  ETH_DMA_TransmitProcess_Reading   : unning - reading the data from host memory
*                  ETH_DMA_TransmitProcess_Suspended : Suspended - Tx Desciptor unavailabe
*                  ETH_DMA_TransmitProcess_Closing   : Running - closing Rx descriptor
*******************************************************************************/
uint32_t ETH_GetTransmitProcessState(void)
{
  return ((uint32_t)(ETH->DMASR & ETH_DMASR_TS)); 
}

/*******************************************************************************
* Function Name  : ETH_GetReceiveProcessState
* Description    : Returns the ETHERNET DMA Receive Process State.
* Input          : None.
* Return         : The new ETHERNET DMA Receive Process State:
*                  ETH_DMA_ReceiveProcess_Stopped   : Stopped - Reset or Stop Rx Command issued
*                  ETH_DMA_ReceiveProcess_Fetching  : Running - fetching the Rx descriptor
*                  ETH_DMA_ReceiveProcess_Waiting   : Running - waiting for packet
*                  ETH_DMA_ReceiveProcess_Suspended : Suspended - Rx Desciptor unavailable
*                  ETH_DMA_ReceiveProcess_Closing   : Running - closing descriptor
*                  ETH_DMA_ReceiveProcess_Queuing   : Running - queuing the recieve frame into host memory
*******************************************************************************/
uint32_t ETH_GetReceiveProcessState(void)
{
  return ((uint32_t)(ETH->DMASR & ETH_DMASR_RS)); 
}

/*******************************************************************************
* Function Name  : ETH_FlushTransmitFIFO
* Description    : Clears the ETHERNET transmit FIFO.
* Input          : None.
* Return         : None.
*******************************************************************************/
void ETH_FlushTransmitFIFO(void)
{
  ETH->DMAOMR |= ETH_DMAOMR_FTF;  
}

/*******************************************************************************
* Function Name  : ETH_GetFlushTransmitFIFOStatus
* Description    : Checks whether the ETHERNET transmit FIFO bit is cleared or not.
* Input          : None.
* Return         : The new state of ETHERNET flush transmit FIFO bit (SET or RESET).
*******************************************************************************/
FlagStatus ETH_GetFlushTransmitFIFOStatus(void)
{   
  FlagStatus bitstatus = RESET;
  if ((ETH->DMAOMR & ETH_DMAOMR_FTF) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus; 
}

/*******************************************************************************
* Function Name  : ETH_DMATransmissionCmd
* Description    : Enables or disables the DMA transmission.
* Input          : NewState: new state of the DMA transmission.
* Return         : None
*******************************************************************************/
void ETH_DMATransmissionCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->DMAOMR |= ETH_DMAOMR_ST;  
  }
  else
  {
    ETH->DMAOMR &= ~ETH_DMAOMR_ST;
  }
}

/*******************************************************************************
* Function Name  : ETH_DMAReceptionCmd
* Description    : Enables or disables the DMA reception.
* Input          : NewState: new state of the DMA reception.
* Return         : None
*******************************************************************************/
void ETH_DMAReceptionCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->DMAOMR |= ETH_DMAOMR_SR;  
  }
  else
  {
    ETH->DMAOMR &= ~ETH_DMAOMR_SR;
  }
}

/*******************************************************************************
* Function Name  : ETH_DMAITConfig
* Description    : Enables or disables the specified ETHERNET DMA interrupts.
* Input          : ETH_DMA_IT: specifies the ETHERNET DMA interrupt sources to be enabled or disabled.
*                  ETH_DMA_IT_NIS : Normal interrupt summary
*                  ETH_DMA_IT_AIS : Abnormal interrupt summary
*                  ETH_DMA_IT_ER  : Early receive interrupt
*                  ETH_DMA_IT_FBE : Fatal bus error interrupt
*                  ETH_DMA_IT_ET  : Early transmit interrupt
*                  ETH_DMA_IT_RWT : Receive watchdog timeout interrupt
*                  ETH_DMA_IT_RPS : Receive process stopped interrupt
*                  ETH_DMA_IT_RBU : Receive buffer unavailable interrupt
*                  ETH_DMA_IT_R   : Receive interrupt
*                  ETH_DMA_IT_TU  : Underflow interrupt
*                  ETH_DMA_IT_RO  : Overflow interrupt
*                  ETH_DMA_IT_TJT : Transmit jabber timeout interrupt
*                  ETH_DMA_IT_TBU : Transmit buffer unavailable interrupt
*                  ETH_DMA_IT_TPS : Transmit process stopped interrupt
*                  ETH_DMA_IT_T   : Transmit interrupt
*                  ETH_DMA_Overflow_RxFIFOCounter : Overflow for FIFO Overflow Counter
*                  ETH_DMA_Overflow_MissedFrameCounter : Overflow for Missed Frame Counter
*                  NewState: new state of the specified ETHERNET DMA interrupts.
* Return         : new state of the specified ETHERNET DMA interrupts.
*******************************************************************************/
void ETH_DMAITConfig(uint32_t ETH_DMA_IT, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->DMAIER |= ETH_DMA_IT;
  }
  else
  {
    ETH->DMAIER &=(~(uint32_t)ETH_DMA_IT);
  }
}

/*******************************************************************************
* Function Name  : ETH_GetDMAOverflowStatus
* Description    : Checks whether the specified ETHERNET DMA overflow flag is set or not.
* Input          : ETH_DMA_Overflow: specifies the DMA overflow flag to check.
*                  ETH_DMA_Overflow_RxFIFOCounter : Overflow for FIFO Overflow Counter
*                  ETH_DMA_Overflow_MissedFrameCounter : Overflow for Missed Frame Counter
* Return         : The new state of ETHERNET DMA overflow Flag (SET or RESET).
*******************************************************************************/
FlagStatus ETH_GetDMAOverflowStatus(uint32_t ETH_DMA_Overflow)
{
  FlagStatus bitstatus = RESET;
  
  if ((ETH->DMAMFBOCR & ETH_DMA_Overflow) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : ETH_GetRxOverflowMissedFrameCounter
* Description    : Get the ETHERNET DMA Rx Overflow Missed Frame Counter value.
* Input          : None.
* Return         : The value of Rx overflow Missed Frame Counter.
*******************************************************************************/
uint32_t ETH_GetRxOverflowMissedFrameCounter(void)
{
  return ((uint32_t)((ETH->DMAMFBOCR & ETH_DMAMFBOCR_MFA)>>ETH_DMA_RX_OVERFLOW_MISSEDFRAMES_COUNTERSHIFT));
}

/*******************************************************************************
* Function Name  : ETH_GetBufferUnavailableMissedFrameCounter
* Description    : Get the ETHERNET DMA Buffer Unavailable Missed Frame Counter value.
* Input          : None.
* Return         : The value of Buffer unavailable Missed Frame Counter.
*******************************************************************************/
uint32_t ETH_GetBufferUnavailableMissedFrameCounter(void)
{
  return ((uint32_t)(ETH->DMAMFBOCR) & ETH_DMAMFBOCR_MFC);
}

/*******************************************************************************
* Function Name  : ETH_GetCurrentTxDescStartAddress
* Description    : Get the ETHERNET DMA DMACHTDR register value.
* Input          : None.
* Return         : The value of the current Tx desc start address.
*******************************************************************************/
uint32_t ETH_GetCurrentTxDescStartAddress(void)
{
  return ((uint32_t)(ETH->DMACHTDR));
}

/*******************************************************************************
* Function Name  : ETH_GetCurrentRxDescStartAddress
* Description    : Get the ETHERNET DMA DMACHRDR register value.
* Input          : None.
* Return         : The value of the current Rx desc start address.
*******************************************************************************/
uint32_t ETH_GetCurrentRxDescStartAddress(void)
{
  return ((uint32_t)(ETH->DMACHRDR));
}

/*******************************************************************************
* Function Name  : ETH_GetCurrentTxBufferAddress
* Description    : Get the ETHERNET DMA DMACHTBAR register value.
* Input          : None.
* Return         : The value of the current Tx buffer address.
*******************************************************************************/
uint32_t ETH_GetCurrentTxBufferAddress(void)
{
    return (DMATxDescToSet->Buffer1Addr);
}

/*******************************************************************************
* Function Name  : ETH_GetCurrentRxBufferAddress
* Description    : Get the ETHERNET DMA DMACHRBAR register value.
* Input          : None.
* Return         : The value of the current Rx buffer address.
*******************************************************************************/
uint32_t ETH_GetCurrentRxBufferAddress(void)
{
  return ((uint32_t)(ETH->DMACHRBAR));
}

/*******************************************************************************
* Function Name  : ETH_ResumeDMATransmission
* Description    : Resumes the DMA Transmission by writing to the DmaTxPollDemand register
* Input          : None.
* Return         : None.
*******************************************************************************/
void ETH_ResumeDMATransmission(void)
{
  ETH->DMATPDR = 0;
}

/*******************************************************************************
* Function Name  : ETH_ResumeDMAReception
* Description    : Resumes the DMA Transmission by writing to the DmaRxPollDemand register.
* Input          : None.
* Return         : None.
*******************************************************************************/
void ETH_ResumeDMAReception(void)
{
  ETH->DMARPDR = 0;
}

/*******************************************************************************
* Function Name  : ETH_ResetWakeUpFrameFilterRegisterPointer
* Description    : Reset Wakeup frame filter register pointer.
* Input          : None.
* Return         : None.
*******************************************************************************/
void ETH_ResetWakeUpFrameFilterRegisterPointer(void)
{  
  ETH->MACPMTCSR |= ETH_MACPMTCSR_WFFRPR;  
}

/*******************************************************************************
* Function Name  : ETH_SetWakeUpFrameFilterRegister
* Description    : Populates the remote wakeup frame registers.
* Input          : Buffer: Pointer on remote WakeUp Frame Filter Register buffer data (8 words).
* Return         : None
*******************************************************************************/
void ETH_SetWakeUpFrameFilterRegister(uint32_t *Buffer)
{
  uint32_t i = 0;
  
  for(i =0; i<ETH_WAKEUP_REGISTER_LENGTH; i++)
  {
    ETH->MACRWUFFR = Buffer[i];
  }
}

/*******************************************************************************
* Function Name  : ETH_GlobalUnicastWakeUpCmd
* Description    : Enables or disables any unicast packet filtered by the MAC address.
* Input          : NewState: new state of the MAC Global Unicast Wake-Up.
* Return         : None
*******************************************************************************/
void ETH_GlobalUnicastWakeUpCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->MACPMTCSR |= ETH_MACPMTCSR_GU;  
  }
  else
  {
    ETH->MACPMTCSR &= ~ETH_MACPMTCSR_GU;
  }
}

/*******************************************************************************
* Function Name  : ETH_GetPMTFlagStatus
* Description    : Checks whether the specified ETHERNET PMT flag is set or not.
* Input          : ETH_PMT_FLAG: specifies the flag to check.
* Return         : The new state of ETHERNET PMT Flag (SET or RESET).
*******************************************************************************/
FlagStatus ETH_GetPMTFlagStatus(uint32_t ETH_PMT_FLAG)
{
    FlagStatus bitstatus = RESET;

    if ((ETH->MACPMTCSR & ETH_PMT_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

/*******************************************************************************
* Function Name  : ETH_WakeUpFrameDetectionCmd
* Description    : Enables or disables the MAC Wake-Up Frame Detection.
* Input          : NewState: new state of the MAC Wake-Up Frame Detection.
* Return         : None.
*******************************************************************************/
void ETH_WakeUpFrameDetectionCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->MACPMTCSR |= ETH_MACPMTCSR_WFE;  
  }
  else
  {
    ETH->MACPMTCSR &= ~ETH_MACPMTCSR_WFE;
  }
}

/*******************************************************************************
* Function Name  : ETH_MagicPacketDetectionCmd
* Description    : Enables or disables the MAC Magic Packet Detection.
* Input          : NewState: new state of the MAC Magic Packet Detection.
* Return         : None.
*******************************************************************************/
void ETH_MagicPacketDetectionCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->MACPMTCSR |= ETH_MACPMTCSR_MPE;  
  }
  else
  {
    ETH->MACPMTCSR &= ~ETH_MACPMTCSR_MPE;
  }
}

/*******************************************************************************
* Function Name  : ETH_PowerDownCmd
* Description    : Enables or disables the MAC Power Down.
* Input          : NewState: new state of the MAC Power Down.
* Return         : None.
*******************************************************************************/
void ETH_PowerDownCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->MACPMTCSR |= ETH_MACPMTCSR_PD;  
  }
  else
  {
    ETH->MACPMTCSR &= ~ETH_MACPMTCSR_PD;
  }
}

/*******************************************************************************
* Function Name  : ETH_MMCCounterFreezeCmd
* Description    : Enables or disables the MMC Counter Freeze.
* Input          : NewState: new state of the MMC Counter Freeze.
* Return         : None.
*******************************************************************************/
void ETH_MMCCounterFreezeCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->MMCCR |= ETH_MMCCR_MCF;
  }
  else
  {
    ETH->MMCCR &= ~ETH_MMCCR_MCF;
  }
}

/*******************************************************************************
* Function Name  : ETH_MMCResetOnReadCmd
* Description    : Enables or disables the MMC Reset On Read.
* Input          : NewState: new state of the MMC Reset On Read.
* Return         : None.
*******************************************************************************/
void ETH_MMCResetOnReadCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->MMCCR |= ETH_MMCCR_ROR; 
  }
  else
  {
    ETH->MMCCR &= ~ETH_MMCCR_ROR;
  }
}

/*******************************************************************************
* Function Name  : ETH_MMCCounterRolloverCmd
* Description    : Enables or disables the MMC Counter Stop Rollover.
* Input          : NewState: new state of the MMC Counter Stop Rollover.
* Return         : None.
*******************************************************************************/
void ETH_MMCCounterRolloverCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->MMCCR &= ~ETH_MMCCR_CSR;
  }
  else
  {
    ETH->MMCCR |= ETH_MMCCR_CSR; 
  }
}

/*******************************************************************************
* Function Name  : ETH_MMCCountersReset
* Description    : Resets the MMC Counters.
* Input          : None.
* Return         : None.
*******************************************************************************/
void ETH_MMCCountersReset(void)
{
  ETH->MMCCR |= ETH_MMCCR_CR; 
}

/*******************************************************************************
* Function Name  : ETH_MMCITConfig
* Description    : Enables or disables the specified ETHERNET MMC interrupts.
* Input          : ETH_MMC_IT: specifies the ETHERNET MMC interrupt.
*                  ETH_MMC_IT_TGF   : When Tx good frame counter reaches half the maximum value.
*                  ETH_MMC_IT_TGFMSC: When Tx good multi col counter reaches half the maximum value.
*                  ETH_MMC_IT_TGFSC : When Tx good single col counter reaches half the maximum value.
*                  ETH_MMC_IT_RGUF  : When Rx good unicast frames counter reaches half the maximum value.
*                  ETH_MMC_IT_RFAE  : When Rx alignment error counter reaches half the maximum value.
*                  ETH_MMC_IT_RFCE  : When Rx crc error counter reaches half the maximum value.
* Input          : NewState: new state of the specified ETHERNET MMC interrupts.
* Return         : None.
*******************************************************************************/
void ETH_MMCITConfig(uint32_t ETH_MMC_IT, FunctionalState NewState)
{
  if ((ETH_MMC_IT & (uint32_t)0x10000000) != (uint32_t)RESET)
  {
    ETH_MMC_IT &= 0xEFFFFFFF;
  
    if (NewState != DISABLE)
    {
      ETH->MMCRIMR &=(~(uint32_t)ETH_MMC_IT);
    }
    else
    {
      ETH->MMCRIMR |= ETH_MMC_IT;    
    }
  }
  else
  {
    if (NewState != DISABLE)
    {
      ETH->MMCTIMR &=(~(uint32_t)ETH_MMC_IT);
    }
    else
    {
      ETH->MMCTIMR |= ETH_MMC_IT;    
    }  
  }
}

/*******************************************************************************
* Function Name  : ETH_GetMMCITStatus
* Description    : Checks whether the specified ETHERNET MMC IT is set or not.
* Input          : ETH_MMC_IT: specifies the ETHERNET MMC interrupt.
*                  ETH_MMC_IT_TxFCGC: When Tx good frame counter reaches half the maximum value.
*                  ETH_MMC_IT_TxMCGC: When Tx good multi col counter reaches half the maximum value.
*                  ETH_MMC_IT_TxSCGC: When Tx good single col counter reaches half the maximum value .
*                  ETH_MMC_IT_RxUGFC: When Rx good unicast frames counter reaches half the maximum value.
*                  ETH_MMC_IT_RxAEC : When Rx alignment error counter reaches half the maximum value.
*                  ETH_MMC_IT_RxCEC : When Rx crc error counter reaches half the maximum value.
* Return         : The value of ETHERNET MMC IT (SET or RESET).
*******************************************************************************/
ITStatus ETH_GetMMCITStatus(uint32_t ETH_MMC_IT)
{
  ITStatus bitstatus = RESET;
  
  if ((ETH_MMC_IT & (uint32_t)0x10000000) != (uint32_t)RESET)
  {
    if ((((ETH->MMCRIR & ETH_MMC_IT) != (uint32_t)RESET)) && ((ETH->MMCRIMR & ETH_MMC_IT) != (uint32_t)RESET))
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
    if ((((ETH->MMCTIR & ETH_MMC_IT) != (uint32_t)RESET)) && ((ETH->MMCRIMR & ETH_MMC_IT) != (uint32_t)RESET))
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

/*******************************************************************************
* Function Name  : ETH_GetMMCRegister
* Description    : Get the specified ETHERNET MMC register value.
* Input          : ETH_MMCReg: specifies the ETHERNET MMC register.
*                  ETH_MMCCR      : MMC CR register
*                  ETH_MMCRIR     : MMC RIR register
*                  ETH_MMCTIR     : MMC TIR register
*                  ETH_MMCRIMR    : MMC RIMR register
*                  ETH_MMCTIMR    : MMC TIMR register
*                  ETH_MMCTGFSCCR : MMC TGFSCCR register
*                  ETH_MMCTGFMSCCR: MMC TGFMSCCR register
*                  ETH_MMCTGFCR   : MMC TGFCR register
*                  ETH_MMCRFCECR  : MMC RFCECR register
*                  ETH_MMCRFAECR  : MMC RFAECR register
*                  ETH_MMCRGUFCR  : MMC RGUFCRregister
* Return         : The value of ETHERNET MMC Register value.
*******************************************************************************/
uint32_t ETH_GetMMCRegister(uint32_t ETH_MMCReg)
{
  return (*(__IO uint32_t *)(ETH_MAC_BASE + ETH_MMCReg));
}

/*******************************************************************************
* Function Name  : ETH_EnablePTPTimeStampAddend
* Description    : Updated the PTP block for fine correction with the Time Stamp Addend register value.
* Input          : None.
* Return         : None.
*******************************************************************************/
void ETH_EnablePTPTimeStampAddend(void)
{
  ETH->PTPTSCR |= ETH_PTPTSCR_TSARU;    
}

/*******************************************************************************
* Function Name  : ETH_EnablePTPTimeStampInterruptTrigger
* Description    : Enable the PTP Time Stamp interrupt trigger
* Input          : None.
* Return         : None.
*******************************************************************************/
void ETH_EnablePTPTimeStampInterruptTrigger(void)
{
  ETH->PTPTSCR |= ETH_PTPTSCR_TSITE;    
}

/*******************************************************************************
* Function Name  : ETH_EnablePTPTimeStampUpdate
* Description    : Updated the PTP system time with the Time Stamp Update register value.
* Input          : None.
* Return         : None.
*******************************************************************************/
void ETH_EnablePTPTimeStampUpdate(void)
{
  ETH->PTPTSCR |= ETH_PTPTSCR_TSSTU;    
}

/*******************************************************************************
* Function Name  : ETH_InitializePTPTimeStamp
* Description    : Initialize the PTP Time Stamp.
* Input          : None.
* Return         : None.
*******************************************************************************/
void ETH_InitializePTPTimeStamp(void)
{
  ETH->PTPTSCR |= ETH_PTPTSCR_TSSTI;    
}

/*******************************************************************************
* Function Name  : ETH_PTPUpdateMethodConfig
* Description    : Selects the PTP Update method.
* Input          : UpdateMethod: the PTP Update method.
* Return         : None.
*******************************************************************************/
void ETH_PTPUpdateMethodConfig(uint32_t UpdateMethod)
{
  if (UpdateMethod != ETH_PTP_CoarseUpdate)
  {
    ETH->PTPTSCR |= ETH_PTPTSCR_TSFCU;
  }
  else
  {
    ETH->PTPTSCR &= (~(uint32_t)ETH_PTPTSCR_TSFCU);
  } 
}

/*******************************************************************************
* Function Name  : ETH_PTPTimeStampCmd
* Description    : Enables or disables the PTP time stamp for transmit and receive frames.
* Input          : NewState: new state of the PTP time stamp for transmit and receive frames.
* Return         : None.
*******************************************************************************/
void ETH_PTPTimeStampCmd(FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    ETH->PTPTSCR |= ETH_PTPTSCR_TSE;
  }
  else
  {
    ETH->PTPTSCR &= (~(uint32_t)ETH_PTPTSCR_TSE);
  }
}

/*******************************************************************************
* Function Name  : ETH_GetPTPFlagStatus
* Description    : Checks whether the specified ETHERNET PTP flag is set or not.
* Input          : ETH_PTP_FLAG: specifies the flag to check.
* Return         : The new state of ETHERNET PTP Flag (SET or RESET).
*******************************************************************************/
FlagStatus ETH_GetPTPFlagStatus(uint32_t ETH_PTP_FLAG)
{
  FlagStatus bitstatus = RESET;
  
  if ((ETH->PTPTSCR & ETH_PTP_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : ETH_SetPTPSubSecondIncrement
* Description    : Sets the system time Sub-Second Increment value.
* Input          : SubSecondValue: specifies the PTP Sub-Second Increment Register value.
* Return         : None.
*******************************************************************************/
void ETH_SetPTPSubSecondIncrement(uint32_t SubSecondValue)
{
  ETH->PTPSSIR = SubSecondValue;    
}

/*******************************************************************************
* Function Name  : ETH_SetPTPTimeStampUpdate
* Description    : Sets the Time Stamp update sign and values.
* Input          : Sign: specifies the PTP Time update value sign.
*                  SecondValue: specifies the PTP Time update second value.
*                  SubSecondValue: specifies the PTP Time update sub-second value.
* Return         : None.
*******************************************************************************/
void ETH_SetPTPTimeStampUpdate(uint32_t Sign, uint32_t SecondValue, uint32_t SubSecondValue)
{
  ETH->PTPTSHUR = SecondValue;
  ETH->PTPTSLUR = Sign | SubSecondValue;   
}

/*******************************************************************************
* Function Name  : ETH_SetPTPTimeStampAddend
* Description    : Sets the Time Stamp Addend value.
* Input          : Value: specifies the PTP Time Stamp Addend Register value.
* Return         : None.
*******************************************************************************/
void ETH_SetPTPTimeStampAddend(uint32_t Value)
{
  /* Set the PTP Time Stamp Addend Register */
  ETH->PTPTSAR = Value;    
}

/*******************************************************************************
* Function Name  : ETH_SetPTPTargetTime
* Description    : Sets the Target Time registers values.
* Input          : HighValue: specifies the PTP Target Time High Register value.
*                  LowValue: specifies the PTP Target Time Low Register value.
* Return         : None.
*******************************************************************************/
void ETH_SetPTPTargetTime(uint32_t HighValue, uint32_t LowValue)
{
  ETH->PTPTTHR = HighValue;
  ETH->PTPTTLR = LowValue;    
}

/*******************************************************************************
* Function Name  : ETH_GetPTPRegister
* Description    : Get the specified ETHERNET PTP register value.
* Input          : ETH_PTPReg: specifies the ETHERNET PTP register.
*                ETH_PTPTSCR  : Sub-Second Increment Register
*                ETH_PTPSSIR  : Sub-Second Increment Register
*                ETH_PTPTSHR  : Time Stamp High Register
*                ETH_PTPTSLR  : Time Stamp Low Register
*                ETH_PTPTSHUR : Time Stamp High Update Register
*                ETH_PTPTSLUR : Time Stamp Low Update Register
*                ETH_PTPTSAR  : Time Stamp Addend Register
*                ETH_PTPTTHR  : Target Time High Register
*                ETH_PTPTTLR  : Target Time Low Register
* Return         : The value of ETHERNET PTP Register value.
*******************************************************************************/
uint32_t ETH_GetPTPRegister(uint32_t ETH_PTPReg)
{
  return (*(__IO uint32_t *)(ETH_MAC_BASE + ETH_PTPReg));
}

/*******************************************************************************
* Function Name  : ETH_DMAPTPTxDescChainInit
* Description    : Initializes the DMA Tx descriptors in chain mode with PTP.
* Input          : DMATxDescTab: Pointer on the first Tx desc list.
*                  DMAPTPTxDescTab: Pointer on the first PTP Tx desc list.
*                  TxBuff: Pointer on the first TxBuffer list.
*                  TxBuffCount: Number of the used Tx desc in the list.
* Return         : None.
*******************************************************************************/
void ETH_DMAPTPTxDescChainInit(ETH_DMADESCTypeDef *DMATxDescTab, ETH_DMADESCTypeDef *DMAPTPTxDescTab,
                               uint8_t* TxBuff, uint32_t TxBuffCount)
{
  uint32_t i = 0;
  ETH_DMADESCTypeDef *DMATxDesc;
  
  DMATxDescToSet = DMATxDescTab;
  DMAPTPTxDescToSet = DMAPTPTxDescTab;

  for(i=0; i < TxBuffCount; i++)
  {
    DMATxDesc = DMATxDescTab+i;
    DMATxDesc->Status = ETH_DMATxDesc_TCH | ETH_DMATxDesc_TTSE;  
    DMATxDesc->Buffer1Addr =(uint32_t)(&TxBuff[i*ETH_MAX_PACKET_SIZE]);
    
    if(i < (TxBuffCount-1))
    {
      DMATxDesc->Buffer2NextDescAddr = (uint32_t)(DMATxDescTab+i+1);
    }
    else
    {
      DMATxDesc->Buffer2NextDescAddr = (uint32_t) DMATxDescTab;  
    }

    (&DMAPTPTxDescTab[i])->Buffer1Addr = DMATxDesc->Buffer1Addr;
    (&DMAPTPTxDescTab[i])->Buffer2NextDescAddr = DMATxDesc->Buffer2NextDescAddr;
  }

  (&DMAPTPTxDescTab[i-1])->Status = (uint32_t) DMAPTPTxDescTab;

  ETH->DMATDLAR = (uint32_t) DMATxDescTab;
}

/*******************************************************************************
* Function Name  : ETH_DMAPTPRxDescChainInit
* Description    : Initializes the DMA Rx descriptors in chain mode.
* Input          : DMARxDescTab: Pointer on the first Rx desc list.
*                  DMAPTPRxDescTab: Pointer on the first PTP Rx desc list.
*                  RxBuff: Pointer on the first RxBuffer list.
*                  RxBuffCount: Number of the used Rx desc in the list.
* Return         : None.
*******************************************************************************/
void ETH_DMAPTPRxDescChainInit(ETH_DMADESCTypeDef *DMARxDescTab, ETH_DMADESCTypeDef *DMAPTPRxDescTab,
                               uint8_t *RxBuff, uint32_t RxBuffCount)
{
  uint32_t i = 0;
  ETH_DMADESCTypeDef *DMARxDesc;
  
  DMARxDescToGet = DMARxDescTab; 
  DMAPTPRxDescToGet = DMAPTPRxDescTab;

  for(i=0; i < RxBuffCount; i++)
  {
    DMARxDesc = DMARxDescTab+i;
    DMARxDesc->Status = ETH_DMARxDesc_OWN;
    DMARxDesc->ControlBufferSize = ETH_DMARxDesc_RCH | (uint32_t)ETH_MAX_PACKET_SIZE;  
    DMARxDesc->Buffer1Addr = (uint32_t)(&RxBuff[i*ETH_MAX_PACKET_SIZE]);
    
    if(i < (RxBuffCount-1))
    {
      DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab+i+1); 
    }
    else
    {
      DMARxDesc->Buffer2NextDescAddr = (uint32_t)(DMARxDescTab); 
    }

    (&DMAPTPRxDescTab[i])->Buffer1Addr = DMARxDesc->Buffer1Addr;
    (&DMAPTPRxDescTab[i])->Buffer2NextDescAddr = DMARxDesc->Buffer2NextDescAddr;
  }

  (&DMAPTPRxDescTab[i-1])->Status = (uint32_t) DMAPTPRxDescTab;
  ETH->DMARDLAR = (uint32_t) DMARxDescTab;  
}

/*******************************************************************************
* Function Name  : ETH_HandlePTPTxPkt
* Description    : Transmits a packet, from application buffer, pointed by ppkt with Time Stamp values.
* Input          : ppkt: pointer to application packet buffer to transmit.
*                  FrameLength: Tx Packet size.
*                  PTPTxTab: Pointer on the first PTP Tx table to store Time stamp values.
* Return         : ETH_ERROR: in case of Tx desc owned by DMA.
*                  ETH_SUCCESS: for correct transmission.
*******************************************************************************/
uint32_t ETH_HandlePTPTxPkt(uint8_t *ppkt, uint16_t FrameLength, uint32_t *PTPTxTab)
{
  uint32_t offset = 0, timeout = 0;

  if((DMATxDescToSet->Status & ETH_DMATxDesc_OWN) != (uint32_t)RESET)
  {
    return ETH_ERROR;
  }

  for(offset=0; offset<FrameLength; offset++)
  {
    (*(__IO uint8_t *)((DMAPTPTxDescToSet->Buffer1Addr) + offset)) = (*(ppkt + offset));
  }

  DMATxDescToSet->ControlBufferSize = (FrameLength & (uint32_t)0x1FFF);
  DMATxDescToSet->Status |= ETH_DMATxDesc_LS | ETH_DMATxDesc_FS;
  DMATxDescToSet->Status |= ETH_DMATxDesc_OWN;

  if ((ETH->DMASR & ETH_DMASR_TBUS) != (uint32_t)RESET)
  {
    ETH->DMASR = ETH_DMASR_TBUS;
    ETH->DMATPDR = 0;
  }

  do
  {
    timeout++;
  } while (!(DMATxDescToSet->Status & ETH_DMATxDesc_TTSS) && (timeout < 0xFFFF));

  if(timeout == PHY_READ_TO)
  {
    return ETH_ERROR;
  }

  DMATxDescToSet->Status &= ~ETH_DMATxDesc_TTSS;
  *PTPTxTab++ = DMATxDescToSet->Buffer1Addr;
  *PTPTxTab = DMATxDescToSet->Buffer2NextDescAddr;

  if((DMATxDescToSet->Status & ETH_DMATxDesc_TCH) != (uint32_t)RESET)
  {  
    DMATxDescToSet = (ETH_DMADESCTypeDef*) (DMAPTPTxDescToSet->Buffer2NextDescAddr);
    if(DMAPTPTxDescToSet->Status != 0)
    { 
      DMAPTPTxDescToSet = (ETH_DMADESCTypeDef*) (DMAPTPTxDescToSet->Status);
    }
    else
    {
      DMAPTPTxDescToSet++;
    }
  }
  else
  {  
    if((DMATxDescToSet->Status & ETH_DMATxDesc_TER) != (uint32_t)RESET)
    {
      DMATxDescToSet = (ETH_DMADESCTypeDef*) (ETH->DMATDLAR); 
      DMAPTPTxDescToSet = (ETH_DMADESCTypeDef*) (ETH->DMATDLAR);
    }
    else
    {
      DMATxDescToSet = (ETH_DMADESCTypeDef*) ((uint32_t)DMATxDescToSet + 0x10 + ((ETH->DMABMR & ETH_DMABMR_DSL) >> 2));      
      DMAPTPTxDescToSet = (ETH_DMADESCTypeDef*) ((uint32_t)DMAPTPTxDescToSet + 0x10 + ((ETH->DMABMR & ETH_DMABMR_DSL) >> 2));      
    }
  }

  return ETH_SUCCESS;
}

/*******************************************************************************
* Function Name  : ETH_HandlePTPRxPkt
* Description    : Receives a packet and copies it to memory pointed by ppkt with Time Stamp values.
* Input          : ppkt: pointer to application packet receive buffer.
*                  PTPRxTab: Pointer on the first PTP Rx table to store Time stamp values.
* Return         : ETH_ERROR: if there is error in reception.
*                  framelength: received packet size if packet reception is correct
*******************************************************************************/
uint32_t ETH_HandlePTPRxPkt(uint8_t *ppkt, uint32_t *PTPRxTab)
{
  uint32_t offset = 0, framelength = 0;

  if((DMARxDescToGet->Status & ETH_DMARxDesc_OWN) != (uint32_t)RESET)
  {
    return ETH_ERROR;
  }
  if(((DMARxDescToGet->Status & ETH_DMARxDesc_ES) == (uint32_t)RESET) &&
     ((DMARxDescToGet->Status & ETH_DMARxDesc_LS) != (uint32_t)RESET) &&
     ((DMARxDescToGet->Status & ETH_DMARxDesc_FS) != (uint32_t)RESET))
  {
    framelength = ((DMARxDescToGet->Status & ETH_DMARxDesc_FL) >> ETH_DMARXDESC_FRAME_LENGTHSHIFT) - 4;

    for(offset=0; offset<framelength; offset++)
    {
      (*(ppkt + offset)) = (*(__IO uint8_t *)((DMAPTPRxDescToGet->Buffer1Addr) + offset));
    }
  }
  else
  {
    framelength = ETH_ERROR;
  }

  if ((ETH->DMASR & ETH_DMASR_RBUS) != (uint32_t)RESET)
  {
    ETH->DMASR = ETH_DMASR_RBUS;
    ETH->DMARPDR = 0;
  }

  *PTPRxTab++ = DMARxDescToGet->Buffer1Addr;
  *PTPRxTab = DMARxDescToGet->Buffer2NextDescAddr;
  DMARxDescToGet->Status |= ETH_DMARxDesc_OWN;

  if((DMARxDescToGet->ControlBufferSize & ETH_DMARxDesc_RCH) != (uint32_t)RESET)
  {
    DMARxDescToGet = (ETH_DMADESCTypeDef*) (DMAPTPRxDescToGet->Buffer2NextDescAddr);
    if(DMAPTPRxDescToGet->Status != 0)
    {
      DMAPTPRxDescToGet = (ETH_DMADESCTypeDef*) (DMAPTPRxDescToGet->Status);
    }
    else
    {
      DMAPTPRxDescToGet++;
    }
  }
  else
  {
    if((DMARxDescToGet->ControlBufferSize & ETH_DMARxDesc_RER) != (uint32_t)RESET)
    {
      DMARxDescToGet = (ETH_DMADESCTypeDef*) (ETH->DMARDLAR);
    }
    else
    {
      DMARxDescToGet = (ETH_DMADESCTypeDef*) ((uint32_t)DMARxDescToGet + 0x10 + ((ETH->DMABMR & ETH_DMABMR_DSL) >> 2));      
    }
  }

  return (framelength);
}


/*******************************************************************************
* Function Name  : RGMII_TXC_Delay
* Description    : Delay time.
* Input          : None
* Return         : None
*******************************************************************************/
void RGMII_TXC_Delay(uint8_t clock_polarity,uint8_t delay_time)
{
    if(clock_polarity){
        ETH->MACCR |= (uint32_t)((uint32_t)1<<1);
    }
    else{
        ETH->MACCR &=~(uint32_t)((uint32_t)1<<1);
    }
    if(delay_time<=7){
        ETH->MACCR |= (uint32_t)((uint32_t)delay_time<<29);
    }
}



