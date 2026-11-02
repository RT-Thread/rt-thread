/**
  ******************************************************************************
  * @file    lib_dma.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   DMA library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_dma.h"

//registers default reset values
#define DMA_CxCTL_RSTValue      (0UL)
#define DMA_CxSRC_RSTValue      (0UL)
#define DMA_CxDST_RSTValue      (0UL)
#define DMA_AESCTL_RSTValue     (0UL)
#define DMA_AESKEY_RSTValue     (0UL)

/**
  * @brief  Initializes the DMA channel peripheral registers to their default reset values.
  * @param  Channel: DMA_CHANNEL_0~DMA_CHANNEL_3
  * @retval None
  */
void DMA_DeInit(uint32_t Channel)
{
  __IO uint32_t *addr;

  /* Check parameters */
  assert_parameters(IS_DMA_CHANNEL(Channel));

  /* channel x disable, clear stop */
  addr = &DMA->C0CTL + Channel*4;
  *addr &= ~(DMA_CCTL_EN | DMA_CCTL_STOP);

  /* interrupt disable */
  DMA->IE &= ~((1<<(Channel))\
              |(1<<(Channel+4))\
              |(1<<(Channel+8)));

  /* interrupt state clear */
  DMA->STS = (1<<(Channel+4))\
            |(1<<(Channel+8))\
            |(1<<(Channel+12));
    
  /* DMA_CxCTL */
  addr = &DMA->C0CTL + Channel*4;
  *addr =  DMA_CxCTL_RSTValue;
    
  /* DMA_CxSRC */
  addr = &DMA->C0SRC + Channel*4;
  *addr =  DMA_CxSRC_RSTValue;
    
  /* DMA_CxDST */
  addr = &DMA->C0DST + Channel*4;
  *addr =  DMA_CxDST_RSTValue;
}
/**
  * @brief  Fills each DMA_InitType member with its default value.
  * @param  InitStruct: pointer to an DMA_InitType structure which will be initialized.
  * @retval None
  */
void DMA_StructInit(DMA_InitType *InitStruct)
{
  /*-------------- Reset DMA init structure parameters values ---------------*/
  /* Initialize the DestAddr member */
  InitStruct->DestAddr = 0;
  /* Initialize the SrcAddr member */
  InitStruct->SrcAddr = 0;
  /* Initialize the FrameLen member */
  InitStruct->FrameLen = 0;
  /* Initialize the PackLen member */
  InitStruct->PackLen = 0;
  /* Initialize the ContMode member */
  InitStruct->ContMode = DMA_CONTMODE_DISABLE;
  /* Initialize the TransMode member */
  InitStruct->TransMode = DMA_TRANSMODE_SINGLE;
  /* Initialize the ReqSrc member */
  InitStruct->ReqSrc = DMA_REQSRC_SOFT;
  /* Initialize the DestAddrMode member */
  InitStruct->DestAddrMode = DMA_DESTADDRMODE_FIX;
  /* Initialize the SrcAddrMode member */
  InitStruct->SrcAddrMode = DMA_SRCADDRMODE_FIX;
  /* Initialize the TransSize member */
  InitStruct->TransSize = DMA_TRANSSIZE_BYTE;
}
/**
  * @brief  Initializes DMA channel.
  * @param  InitStruct: DMA configuration.
                DestAddr  : destination address
                SrcAddr   : source address
                FrameLen  : Frame length   (Ranges 0~255, actual length FrameLen+1)
                PackLen   : Package length (Ranges 0~255, actual length PackLen+1)
                ContMode:
                    DMA_CONTMODE_ENABLE
                    DMA_CONTMODE_DISABLE
                TransMode:
                    DMA_TRANSMODE_SINGLE
                    DMA_TRANSMODE_PACK
                ReqSrc:
                    DMA_REQSRC_SOFT
                    DMA_REQSRC_ADC
                    DMA_REQSRC_UART0TX
                    DMA_REQSRC_UART0RX
                    DMA_REQSRC_UART1TX
                    DMA_REQSRC_UART1RX
                    DMA_REQSRC_UART2TX
                    DMA_REQSRC_UART2RX
                    DMA_REQSRC_UART3TX
                    DMA_REQSRC_UART3RX
                    DMA_REQSRC_UART4TX
                    DMA_REQSRC_UART4RX
                    DMA_REQSRC_UART5TX
                    DMA_REQSRC_UART5RX
                    DMA_REQSRC_ISO78160TX
                    DMA_REQSRC_ISO78160RX
                    DMA_REQSRC_ISO78161TX
                    DMA_REQSRC_ISO78161RX
                    DMA_REQSRC_TIMER0
                    DMA_REQSRC_TIMER1
                    DMA_REQSRC_TIMER2
                    DMA_REQSRC_TIMER3
                    DMA_REQSRC_SPI1TX
                    DMA_REQSRC_SPI1RX
                    DMA_REQSRC_U32K0
                    DMA_REQSRC_U32K1
                    DMA_REQSRC_CMP1
                    DMA_REQSRC_CMP2
                    DMA_REQSRC_SPI2TX
                    DMA_REQSRC_SPI2RX
                    DMA_REQSRC_SPI3TX
                    DMA_REQSRC_SPI3RX
                DestAddrMode:
                    DMA_DESTADDRMODE_FIX
                    DMA_DESTADDRMODE_PEND
                    DMA_DESTADDRMODE_FEND
                SrcAddrMode:
                    DMA_SRCADDRMODE_FIX
                    DMA_SRCADDRMODE_PEND
                    DMA_SRCADDRMODE_FEND
                TransSize:
                    DMA_TRANSSIZE_BYTE
                    DMA_TRANSSIZE_HWORD
                    DMA_TRANSSIZE_WORD
            Channel:
                DMA_CHANNEL_0
                DMA_CHANNEL_1 
                DMA_CHANNEL_2 
                DMA_CHANNEL_3 
  * @retval None
  */
void DMA_Init(DMA_InitType *InitStruct, uint32_t Channel)
{
  uint32_t tmp;
  __IO uint32_t *addr;
  
  /* Check parameters */
  assert_parameters(IS_DMA_CHANNEL(Channel));
  assert_parameters(IS_DMA_CONTMOD(InitStruct->ContMode));
  assert_parameters(IS_DMA_TRANSMOD(InitStruct->TransMode));
  assert_parameters(IS_DMA_REQSRC(InitStruct->ReqSrc));
  assert_parameters(IS_DMA_DESTADDRMOD(InitStruct->DestAddrMode));
  assert_parameters(IS_DMA_SRCADDRMOD(InitStruct->SrcAddrMode));
  assert_parameters(IS_DMA_TRANSSIZE(InitStruct->TransSize));
  
  if (InitStruct->TransSize == DMA_TRANSSIZE_HWORD)
  {
    assert_parameters(IS_DMA_ALIGNEDADDR_HWORD(InitStruct->SrcAddr));
    assert_parameters(IS_DMA_ALIGNEDADDR_HWORD(InitStruct->DestAddr));
  }
  if (InitStruct->TransSize == DMA_TRANSSIZE_WORD)
  {
    assert_parameters(IS_DMA_ALIGNEDADDR_WORD(InitStruct->SrcAddr));
    assert_parameters(IS_DMA_ALIGNEDADDR_WORD(InitStruct->DestAddr));    
  }
    
  addr = &DMA->C0DST + Channel*4;
  *addr = InitStruct->DestAddr;
    
  addr = &DMA->C0SRC + Channel*4;
  *addr = InitStruct->SrcAddr;
    
  addr = &DMA->C0CTL + Channel*4;
    
  tmp = *addr;
  tmp &= ~(DMA_CCTL_FLEN\
          |DMA_CCTL_PLEN\
          |DMA_CCTL_CONT\
          |DMA_CCTL_TMODE\
          |DMA_CCTL_DMASEL\
          |DMA_CCTL_DMODE\
          |DMA_CCTL_SMODE\
          |DMA_CCTL_SIZE);
  tmp |= ((InitStruct->FrameLen<<DMA_CCTL_FLEN_Pos)\
         |(InitStruct->PackLen<<DMA_CCTL_PLEN_Pos)\
         |(InitStruct->ContMode)\
         |(InitStruct->TransMode)\
         |(InitStruct->ReqSrc)\
         |(InitStruct->DestAddrMode)\
         |(InitStruct->SrcAddrMode)\
         |(InitStruct->TransSize));
  *addr = tmp;
}

/**
  * @brief  Initializes the DMA AES channel3 registers to their default reset values.
  * @param  None
  * @retval None
  */
void DMA_ASEDeInit(void)
{
  DMA->AESCTL = DMA_AESCTL_RSTValue;
  DMA->AESKEY[0] = DMA_AESKEY_RSTValue;
  DMA->AESKEY[1] = DMA_AESKEY_RSTValue;
  DMA->AESKEY[2] = DMA_AESKEY_RSTValue;
  DMA->AESKEY[3] = DMA_AESKEY_RSTValue;
  DMA->AESKEY[4] = DMA_AESKEY_RSTValue;
  DMA->AESKEY[5] = DMA_AESKEY_RSTValue;
  DMA->AESKEY[6] = DMA_AESKEY_RSTValue;
  DMA->AESKEY[7] = DMA_AESKEY_RSTValue;
}

/**
  * @brief  Initializes AES.
  * @param  InitStruct: AES configuration.
                Mode:
                    DMA_AESMODE_128
                    DMA_AESMODE_192
                    DMA_AESMODE_256
                Direction:
                    DMA_AESDIRECTION_ENCODE
                    DMA_AESDIRECTION_DECODE
                KeyStr: the pointer to DMA_AESKEYx register
  * @retval None
  */
void DMA_AESInit(DMA_AESInitType *InitStruct)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_DMA_AESMOD(InitStruct->Mode)); 
  assert_parameters(IS_DMA_AESDIR(InitStruct->Direction)); 
    
  tmp = DMA->AESCTL;
  tmp &= ~(DMA_AESCTL_MODE\
          |DMA_AESCTL_ENC);
  tmp |= (InitStruct->Mode\
         |InitStruct->Direction);
  DMA->AESCTL = tmp;
  DMA->AESKEY[0] = InitStruct->KeyStr[0];
  DMA->AESKEY[1] = InitStruct->KeyStr[1];
  DMA->AESKEY[2] = InitStruct->KeyStr[2];
  DMA->AESKEY[3] = InitStruct->KeyStr[3];
    
  if ((InitStruct->Mode == DMA_AESMODE_192) ||\
      (InitStruct->Mode == DMA_AESMODE_256))
  {
    DMA->AESKEY[4] = InitStruct->KeyStr[4];
    DMA->AESKEY[5] = InitStruct->KeyStr[5];
  }
  if (InitStruct->Mode == DMA_AESMODE_256)
  {
    DMA->AESKEY[6] = InitStruct->KeyStr[6];
    DMA->AESKEY[7] = InitStruct->KeyStr[7];
  }
}

/**
  * @brief  Enables or disables DMA interrupt.
  * @param  INTMask: can use the '|' operator
                 DMA_INT_C3DA 
                 DMA_INT_C2DA  
                 DMA_INT_C1DA  
                 DMA_INT_C0DA  
                 DMA_INT_C3FE  
                 DMA_INT_C2FE  
                 DMA_INT_C1FE  
                 DMA_INT_C0FE  
                 DMA_INT_C3PE  
                 DMA_INT_C2PE  
                 DMA_INT_C1PE  
                 DMA_INT_C0PE  
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void DMA_INTConfig(uint32_t INTMask, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_DMA_INT(INTMask)); 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
    DMA->IE |= INTMask;
  else
    DMA->IE &= ~INTMask;
}

/**
  * @brief  Gets DMA interrupt status.
  * @param  INTMask: 
                  DMA_INTSTS_C3DA  
                  DMA_INTSTS_C2DA    
                  DMA_INTSTS_C1DA    
                  DMA_INTSTS_C0DA    
                  DMA_INTSTS_C3FE    
                  DMA_INTSTS_C2FE    
                  DMA_INTSTS_C1FE    
                  DMA_INTSTS_C0FE    
                  DMA_INTSTS_C3PE    
                  DMA_INTSTS_C2PE    
                  DMA_INTSTS_C1PE    
                  DMA_INTSTS_C0PE    
                  DMA_INTSTS_C3BUSY 
                  DMA_INTSTS_C2BUSY 
                  DMA_INTSTS_C1BUSY 
                  DMA_INTSTS_C0BUSY 
  * @retval interrupt status.
  */
uint8_t DMA_GetINTStatus(uint32_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_DMA_INTFLAGR(INTMask)); 
  
  if (DMA->STS&INTMask)
    return 1;
  else
    return 0;
}

/**
  * @brief  Clears DMA interrupt status.
  * @param  INTMask: can use the '|' operator
               DMA_INTSTS_C3DA
               DMA_INTSTS_C2DA
               DMA_INTSTS_C1DA
               DMA_INTSTS_C0DA
               DMA_INTSTS_C3FE
               DMA_INTSTS_C2FE
               DMA_INTSTS_C1FE
               DMA_INTSTS_C0FE
               DMA_INTSTS_C3PE
               DMA_INTSTS_C2PE
               DMA_INTSTS_C1PE
               DMA_INTSTS_C0PE
  * @retval None
  */
void DMA_ClearINTStatus(uint32_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_DMA_INTFLAGC(INTMask));
  
  DMA->STS = INTMask;
}

/**
  * @brief  Enables or disables DMA channel.
  * @param  Channel:
                DMA_CHANNEL_0
                DMA_CHANNEL_1 
                DMA_CHANNEL_2 
                DMA_CHANNEL_3 
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void DMA_Cmd(uint32_t Channel, uint32_t NewState)
{
  __IO uint32_t *addr;
  
  /* Check parameters */
  assert_parameters(IS_DMA_CHANNEL(Channel)); 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
    
  addr = &DMA->C0CTL + Channel*4;
    
  if (NewState == ENABLE)
    *addr |= DMA_CCTL_EN;
  else
    *addr &= ~DMA_CCTL_EN;
}

/**
  * @brief  Enables or disables AES encrypt/decrypt function of DMA channel3.
  * @param  NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void DMA_AESCmd(uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));  
  
  if (NewState == ENABLE)
    DMA->C3CTL |= DMA_CCTL_AESEN;
  else
    DMA->C3CTL &= ~DMA_CCTL_AESEN;
}

/**
  * @brief  Stops DMA transmit.
  * @param  Channel:
                DMA_CHANNEL_0
                DMA_CHANNEL_1 
                DMA_CHANNEL_2 
                DMA_CHANNEL_3 
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void DMA_StopTransmit(uint32_t Channel, uint32_t NewState)
{
  __IO uint32_t *addr;

  /* Check parameters */
  assert_parameters(IS_DMA_CHANNEL(Channel)); 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  addr = &DMA->C0CTL + Channel*4;
    
  if (NewState == ENABLE)
    *addr |= DMA_CCTL_STOP;
  else
    *addr &= ~DMA_CCTL_STOP;
}

/**
  * @brief  Gets current frame transferred length.
  * @param  Channel:
                DMA_CHANNEL_0
                DMA_CHANNEL_1 
                DMA_CHANNEL_2 
                DMA_CHANNEL_3 
  * @retval Current frame transferred length.
  */
uint8_t DMA_GetFrameLenTransferred(uint32_t Channel)
{
  __IO uint32_t *addr;
  
  /* Check parameters */
  assert_parameters(IS_DMA_CHANNEL(Channel)); 
    
  addr = &DMA->C0LEN + Channel*4;
  return ((*addr&0xFF00)>>8);
}

/**
  * @brief  Gets current package transferred length.
  * @param  Channel:
                DMA_CHANNEL_0
                DMA_CHANNEL_1 
                DMA_CHANNEL_2 
                DMA_CHANNEL_3 
  * @retval Current package transferred length.
  */
uint8_t DMA_GetPackLenTransferred(uint32_t Channel)
{
  __IO uint32_t *addr;
  
  /* Check parameters */
  assert_parameters(IS_DMA_CHANNEL(Channel)); 
    
  addr = &DMA->C0LEN + Channel*4;
  return (*addr&0xFF);
}

/*********************************** END OF FILE ******************************/
