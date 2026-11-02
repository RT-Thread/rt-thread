/**
  ******************************************************************************
  * @file    lib_iso7816.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   ISO7816 library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_iso7816.h"
#include "lib_clk.h"

//registers default reset values
#define ISO7816_BAUDDIVL_RSTValue  (0UL)
#define ISO7816_BAUDDIVH_RSTValue  (0UL)
#define ISO7816_CFG_RSTValue       (0x400)
#define ISO7816_CLK_RSTValue       (0UL)
#define ISO7816_INFO_RC_MASK       (0x3ECUL)


/**
  * @brief  Initializes the ISO7816 peripheral registers to their default reset values.
  * @param  ISO7816x: ISO78160~ISO78161
  * @retval None
  */
void ISO7816_DeInit(ISO7816_Type *ISO7816x)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  
  ISO7816x->CFG &= ~ISO7816_CFG_EN;

  ISO7816x->INFO = ISO7816_INFO_RC_MASK;  /* clear interrupt flag */
  ISO7816x->BAUDDIVH = ISO7816_BAUDDIVH_RSTValue;
  ISO7816x->BAUDDIVL = ISO7816_BAUDDIVL_RSTValue;
  ISO7816x->CFG = ISO7816_CFG_RSTValue;
  ISO7816x->CLK = ISO7816_CLK_RSTValue;
}


/**
  * @brief  Fills each InitStruct member with its default value.
  * @param  InitStruct: pointer to an ISO7816_InitType structure which will be initialized.
  * @retval None
  */
void ISO7816_StructInit(ISO7816_InitType *InitStruct)
{
  /*--------------- Reset ISO7816 init structure parameters values ---------------*/
  /* Initialize the FirstBit member */ 
  InitStruct->FirstBit = ISO7816_FIRSTBIT_MSB;
  /* Initialize the Parity member */ 
  InitStruct->Parity = ISO7816_PARITY_EVEN;
  /* Initialize the Baudrate member */ 
  InitStruct->Baudrate = 9600;
  /* Initialize the TXRetry member */ 
  InitStruct->TXRetry = ISO7816_TXRTY_0;
  /* Initialize the RXACKLength member */ 
  InitStruct->RXACKLength = ISO7816_RXACKLEN_2;
  /* Initialize the TXNACKLength member */ 
  InitStruct->TXNACKLength = ISO7816_TXNACKLEN_0;
}

/**
  * @brief  Initializes ISO7816.
  * @param  ISO7816x: ISO78160~ISO78161
            Init_Struct:iso7816 configuration.
               FirstBit:
                   ISO7816_FIRSTBIT_MSB
                   ISO7816_FIRSTBIT_LSB
               Parity:
                   ISO7816_PARITY_EVEN
                   ISO7816_PARITY_ODD
               Baudrate: baudrate value to configure, 200UL ~ 2625000UL
               TXRetry:
                   ISO7816_TXRTY_0 ~ ISO7816_TXRTY_15
               RXACKLength:
                   ISO7816_RXACKLEN_2
                   ISO7816_RXACKLEN_1
               TXNACKLength:
                   ISO7816_TXNACKLEN_0
                   ISO7816_TXNACKLEN_1
                   ISO7816_TXNACKLEN_2
  * @retval None
  */
void ISO7816_Init(ISO7816_Type *ISO7816x, ISO7816_InitType *Init_Struct)
{
  uint32_t tmp;
  uint16_t div;
  uint32_t pclk;
  
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_ISO7816_FIRSTBIT(Init_Struct->FirstBit));
  assert_parameters(IS_ISO7816_PARITY(Init_Struct->Parity));
  assert_parameters(IS_ISO7816_BAUDRATE(Init_Struct->Baudrate));
  assert_parameters(IS_ISO7816_TXRTY(Init_Struct->TXRetry));
  assert_parameters(IS_ISO7816_RXACKLEN(Init_Struct->RXACKLength));
  assert_parameters(IS_ISO7816_TXNACKLEN(Init_Struct->TXNACKLength));

  tmp = ISO7816x->CFG;
  tmp &= ~(ISO7816_CFG_ACKLEN\
          |ISO7816_CFG_AUTORXACK\
          |ISO7816_CFG_LSB\
          |ISO7816_CFG_CHKP\
          |ISO7816_CFG_RXACKSET\
          |ISO7816_CFG_TXRTYCNT);
  tmp |= (Init_Struct->FirstBit\
         |Init_Struct->Parity\
         |Init_Struct->TXRetry\
         |Init_Struct->RXACKLength\
         |Init_Struct->TXNACKLength);
  ISO7816x->CFG = tmp;

  pclk = CLK_GetPCLKFreq();
  div = 0x10000 - (pclk/Init_Struct->Baudrate);
  ISO7816x->BAUDDIVH = (div>>8) & ISO7816_BAUDDIVH_BAUDDIVH;
  ISO7816x->BAUDDIVL = div & ISO7816_BAUDDIVL_BAUDDIVL;
}

/**
  * @brief  Enables or disables ISO7816.
  * @param  ISO7816x: ISO78160~ISO78161 
            NewState:
                ENABLE
                DISABLE
  * @retval None.
  */
void ISO7816_Cmd(ISO7816_Type *ISO7816x, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState)); 
  
  if (NewState == ENABLE)
  {
    ISO7816x->CFG |= ISO7816_CFG_EN;
  }
  else
  {
    ISO7816x->CFG &= ~ISO7816_CFG_EN;
  }
}

/**
  * @brief  Configures ISO7816 baudrate.
  * @param  ISO7816x: ISO78160~ISO78161
            BaudRate:Baud rate value
  * @retval None
  */
void ISO7816_BaudrateConfig(ISO7816_Type *ISO7816x, uint32_t BaudRate)
{
  uint32_t pclk;
  uint16_t div;
    
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));    
  assert_parameters(IS_ISO7816_BAUDRATE(BaudRate));  
  
  pclk = CLK_GetPCLKFreq();
  div = 0x10000 - (pclk/BaudRate);
  ISO7816x->BAUDDIVH = (div>>8) & ISO7816_BAUDDIVH_BAUDDIVH;
  ISO7816x->BAUDDIVL = div & ISO7816_BAUDDIVL_BAUDDIVL;
}

/**
  * @brief  Configures ISO7816 clock divider.
  * @param  ISO7816x: ISO78160~ISO78161
            Prescaler:1~128
  * @retval None
  */
void ISO7816_CLKDIVConfig(ISO7816_Type *ISO7816x, uint32_t Prescaler)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_ISO7816_PRESCALER(Prescaler));  
  
  tmp = ISO7816x->CLK;
  tmp &= ~ISO7816_CLK_CLKDIV;
  tmp |= (Prescaler - 1);
  ISO7816x->CLK = tmp;
}

/**
  * @brief  Enables or disables ISO7816 clock output function.
  * @param  ISO7816x: ISO78160~ISO78161
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void ISO7816_CLKOutputCmd(ISO7816_Type *ISO7816x, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    ISO7816x->CLK |= ISO7816_CLK_CLKEN;
  }
  else
  {
    ISO7816x->CLK &= ~ISO7816_CLK_CLKEN;
  }
}

/**
  * @brief  Reads ISO7816 data.
  * @param  ISO7816: ISO78160~ISO78161
  * @retval The received data.
  */
uint8_t ISO7816_ReceiveData(ISO7816_Type *ISO7816x)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));

  return ISO7816x->DATA;
}

/**
  * @brief  Writes ISO7816 data.
  * @param  ISO7816x: ISO78160~ISO78161
  *         ch: data to send
  * @retval None
  */
void ISO7816_SendData(ISO7816_Type *ISO7816x, uint8_t ch)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  
  ISO7816x->DATA = ch;
}

/**
  * @brief  ENables or disables ISO7816 interrupt.
  * @param  ISO7816x: ISO78160~ISO78161
            INTMask:
                This parameter can be any combination of the following values
                ISO7816_INT_TXRTYERR
                ISO7816_INT_RXOV
                ISO7816_INT_RX
                ISO7816_INT_TXDONE
                ISO7816_INT_RXERR
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void ISO7816_INTConfig(ISO7816_Type *ISO7816x, uint32_t INTMask, uint8_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_ISO7816_INT(INTMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));  
  
  if (NewState == ENABLE)
  {
    ISO7816x->CFG |= INTMask;
  }
  else
  {
    ISO7816x->CFG &= ~INTMask;
  }
}

/**
  * @brief  Gets ISO7816 interrupt state.
  * @param  ISO7816x: ISO78160~ISO78161
            INTMask:
                ISO7816_INTSTS_TXRTYERR
                ISO7816_INTSTS_TXDONE
                ISO7816_INTSTS_RXOV
                ISO7816_INTSTS_RX
                ISO7816_INTSTS_RXERR
  * @retval 1: state set
            0: state reset
  */
uint8_t ISO7816_GetINTStatus(ISO7816_Type *ISO7816x, uint32_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_ISO7816_INTFLAGR(INTMask));
  
  if (ISO7816x->INFO & INTMask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clears ISO7816 interrupt state.
  * @param  ISO7816x: ISO78160~ISO78161
            INTMask:
                This parameter can be any combination of the following values
                ISO7816_INTSTS_TXRTYERR
                ISO7816_INTSTS_TXDONE
                ISO7816_INTSTS_RXOV
                ISO7816_INTSTS_RX
                ISO7816_INTSTS_RXERR
  * @retval None
  */
void ISO7816_ClearINTStatus(ISO7816_Type *ISO7816x, uint32_t INTMask)
{
    uint32_t tmp;
    
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x)); 
  assert_parameters(IS_ISO7816_INTFLAGC(INTMask));
  
  tmp = ISO7816x->INFO;
  tmp &= ~ISO7816_INFO_RC_MASK;
  tmp |= INTMask;
  ISO7816x->INFO = tmp;
}

/**
  * @brief  Gets ISO7816 peripheral flag.
  * @param  ISO7816x: ISO78160~ISO78161
            FlagMask:
                ISO7816_FLAG_DMATXDONE
  * @retval 1: state set
            0: state reset
  */
uint8_t ISO7816_GetFlag(ISO7816_Type *ISO7816x, uint32_t FlagMask)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_ISO7816_FLAGR(FlagMask));  
  
  if (ISO7816x->INFO & FlagMask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clears ISO7816 peripheral flag.
  * @param  ISO7816x: ISO78160~ISO78161
            FlagMask:
                ISO7816_FLAG_DMATXDONE
  * @retval None
  */
void ISO7816_ClearFlag(ISO7816_Type *ISO7816x, uint32_t FlagMask)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x)); 
  assert_parameters(IS_ISO7816_FLAGC(FlagMask));  

  ISO7816x->INFO |= FlagMask;
}

/**
  * @brief  Gets last transmited ACK.
  * @param  ISO7816: ISO78160~ISO78161
  * @retval ACK value
  */
uint8_t ISO7816_GetLastTransmitACK(ISO7816_Type *ISO7816x)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  
  if (ISO7816x->INFO&ISO7816_INFO_RXACK)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Gets last received check sum bit.
  * @param  ISO7816: ISO78160~ISO78161
  * @retval CHKSUM bit value
  */
uint8_t ISO7816_GetLastReceiveCHKSUM(ISO7816_Type *ISO7816x)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  
  if (ISO7816x->INFO&ISO7816_INFO_CHKSUM)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/*********************************** END OF FILE ******************************/
