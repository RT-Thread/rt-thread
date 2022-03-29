/**
  ******************************************************************************
  * @file    lib_iso7816.c 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   ISO7816 library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_iso7816.h"
#include "lib_clk.h"

//registers default reset values
#define ISO7816_BAUDDIVL_RSTValue   0
#define ISO7816_BAUDDIVH_RSTValue   0
#define ISO7816_CFG_RSTValue        0
#define ISO7816_CLK_RSTValue        0

#define ISO7816_INFO_RC_MASK    (0xECUL) //R/C
#define ISO7816_INFO_RW_MASK    (0x13UL) //R/W

/**
  * @brief  ISO7816 initialization.
  * @param  ISO7816x: ISO78160~ISO78161
            Init_Struct:iso7816 configuration.
                FirstBit:
                    ISO7816_FIRSTBIT_LSB
                    ISO7816_FIRSTBIT_MSB
                ACKLen:
                    ISO7816_ACKLEN_1
                    ISO7816_ACKLEN_2
                Parity:
                    ISO7816_PARITY_EVEN
                    ISO7816_PARITY_ODD
                Baudrate: Baud rate value
  * @retval None
  */
void ISO7816_Init(ISO7816_TypeDef *ISO7816x, ISO7816_InitType *Init_Struct)
{
  uint32_t tmp;
  uint16_t div;
  uint32_t pclk;
  
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_ISO7816_FIRSTBIT(Init_Struct->FirstBit));  
  assert_parameters(IS_ISO7816_ACKLEN(Init_Struct->ACKLen));
  assert_parameters(IS_ISO7816_PARITY(Init_Struct->Parity));
  assert_parameters(IS_ISO7816_BAUDRATE(Init_Struct->Baudrate));

  tmp = ISO7816x->INFO;
  tmp &= ~(ISO7816_INFO_LSB|ISO7816_INFO_RC_MASK);
  tmp |= Init_Struct->FirstBit;
  ISO7816x->INFO = tmp;

  tmp = ISO7816x->CFG;
  tmp &= ~(ISO7816_CFG_ACKLEN\
          |BIT3\
          |BIT2\
          |ISO7816_CFG_CHKP);
  tmp |= (Init_Struct->ACKLen\
         |Init_Struct->Parity);
  ISO7816x->CFG = tmp;

  pclk = CLK_GetPCLKFreq();
  div = 0x10000 - (pclk/Init_Struct->Baudrate);
  ISO7816x->BAUDDIVH = (div>>8) & ISO7816_BAUDDIVH;
  ISO7816x->BAUDDIVL = div & ISO7816_BAUDDIVL;
}

/**
  * @brief  Fills each InitStruct member with its default value.
  * @param  InitStruct: pointer to an ISO7816_InitType structure which will be initialized.
  * @retval None
  */
void ISO7816_StructInit(ISO7816_InitType *InitStruct)
{
  /*--------------- Reset ISO7816 init structure parameters values ---------------*/
  /* Initialize the ACKLen member */ 
  InitStruct->ACKLen = ISO7816_ACKLEN_1;
  /* Initialize the Baudrate member */ 
  InitStruct->Baudrate = 9600;
  /* Initialize the FirstBit member */ 
  InitStruct->FirstBit = ISO7816_FIRSTBIT_MSB;
  /* Initialize the Parity member */ 
  InitStruct->Parity = ISO7816_PARITY_EVEN;
}

/**
  * @brief  Initializes the ISO7816 peripheral registers to their default reset 
            values.
  * @param  ISO7816x: ISO78160~ISO78161
  * @retval None
  */
void ISO7816_DeInit(ISO7816_TypeDef *ISO7816x)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  
  ISO7816x->CFG &= ~ISO7816_CFG_EN;

  /* clear interrupt flag */
  ISO7816x->INFO = ISO7816_INFO_RC_MASK;
  ISO7816x->BAUDDIVH = ISO7816_BAUDDIVH_RSTValue;
  ISO7816x->BAUDDIVL = ISO7816_BAUDDIVL_RSTValue;
  ISO7816x->CFG = ISO7816_CFG_RSTValue;
  ISO7816x->CLK = ISO7816_CLK_RSTValue;
}

/**
  * @brief  ISO7816 enable control.
  * @param  ISO7816x: ISO78160~ISO78161 
            NewState:
                ENABLE
                DISABLE
  * @retval None.
  */
void ISO7816_Cmd(ISO7816_TypeDef *ISO7816x, uint32_t NewState)
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
  * @brief  ISO7816 Baudrate control.
  * @param  ISO7816x: ISO78160~ISO78161
            BaudRate:
  * @retval None
  */
void ISO7816_BaudrateConfig(ISO7816_TypeDef *ISO7816x, uint32_t BaudRate)
{
  uint32_t pclk;
  uint16_t div;
    
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));    
  assert_parameters(IS_ISO7816_BAUDRATE(BaudRate));  
  
  pclk = CLK_GetPCLKFreq();
  div = 0x10000 - (pclk/BaudRate);
  ISO7816x->BAUDDIVH = (div>>8) & ISO7816_BAUDDIVH;
  ISO7816x->BAUDDIVL = div & ISO7816_BAUDDIVL;
}

/**
  * @brief  ISO7816 clock divider configure.
  * @param  ISO7816x: ISO78160~ISO78161
            Prescaler:1~128
  * @retval None
  */
void ISO7816_CLKDIVConfig(ISO7816_TypeDef *ISO7816x, uint32_t Prescaler)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_ISO7816_PRESCALER(Prescaler));  
  
  tmp = ISO7816x->CLK;
  tmp &= ~ISO7816_CLK_CLKDIV;
  tmp |= ((Prescaler - 1) & ISO7816_CLK_CLKDIV);
  ISO7816x->CLK = tmp;
}

/**
  * @brief  ISO7816 clock output enable control.
  * @param  ISO7816x: ISO78160~ISO78161
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void ISO7816_CLKOutputCmd(ISO7816_TypeDef *ISO7816x, uint32_t NewState)
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
  * @brief  Read data.
  * @param  ISO7816: ISO78160~ISO78161
  * @retval The received data.
  */
uint8_t ISO7816_ReceiveData(ISO7816_TypeDef *ISO7816x)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));

  return ISO7816x->DATA;
}

/**
  * @brief  Write data.
  * @param  ISO7816x: ISO78160~ISO78161
  * @retval None
  */
void ISO7816_SendData(ISO7816_TypeDef *ISO7816x, uint8_t ch)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  
  ISO7816x->DATA = ch;
}

/**
  * @brief  Interrupt configure.
  * @param  ISO7816x: ISO78160~ISO78161
            INTMask:
                This parameter can be any combination of the following values
                ISO7816_INT_RXOV
                ISO7816_INT_RX
                ISO7816_INT_TX
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void ISO7816_INTConfig(ISO7816_TypeDef *ISO7816x, uint32_t INTMask, uint8_t NewState)
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
  * @brief  Get interrupt state
  * @param  ISO7816x: ISO78160~ISO78161
            INTMask:
                ISO7816_INTSTS_RXOV
                ISO7816_INTSTS_RX
                ISO7816_INTSTS_TX
  * @retval 1: state set
            0: state reset
  */
uint8_t ISO7816_GetINTStatus(ISO7816_TypeDef *ISO7816x, uint32_t INTMask)
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
  * @brief  Clear interrupt state.
  * @param  ISO7816x: ISO78160~ISO78161
            INTMask:
                This parameter can be any combination of the following values
                ISO7816_INTSTS_RXOV
                ISO7816_INTSTS_RX
                ISO7816_INTSTS_TX
  * @retval None
  */
void ISO7816_ClearINTStatus(ISO7816_TypeDef *ISO7816x, uint32_t INTMask)
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
  * @brief  Get peripheral flag.
  * @param  ISO7816x: ISO78160~ISO78161
            FlagMask:
                ISO7816_FLAG_SDERR
                ISO7816_FLAG_RCERR
  * @retval 1: state set
            0: state reset
  */
uint8_t ISO7816_GetFlag(ISO7816_TypeDef *ISO7816x, uint32_t FlagMask)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  assert_parameters(IS_ISO7816_FLAGR(FlagMask));  
  
  if (ISO7816x->INFO&FlagMask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clear peripheral flag.
  * @param  ISO7816x: ISO78160~ISO78161
            FlagMask:
                This parameter can be any combination of the following values
                ISO7816_FLAG_SDERR
                ISO7816_FLAG_RCERR
  * @retval None
  */
void ISO7816_ClearFlag(ISO7816_TypeDef *ISO7816x, uint32_t FlagMask)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x)); 
  assert_parameters(IS_ISO7816_FLAGC(FlagMask));  
  
  tmp = ISO7816x->INFO;
  tmp &= ~ISO7816_INFO_RC_MASK;
  tmp |= FlagMask;
  ISO7816x->INFO = tmp;
}

/**
  * @brief  Get last transmit ACK.
  * @param  ISO7816: ISO78160~ISO78161
  * @retval ACK value
  */
uint8_t ISO7816_GetLastTransmitACK(ISO7816_TypeDef *ISO7816x)
{
  /* Check parameters */
  assert_parameters(IS_ISO7816_ALL_INSTANCE(ISO7816x));
  
  if (ISO7816x->INFO&ISO7816_INFO_RCACK)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
            
/**
  * @brief  Get last receive check sum bit.
  * @param  ISO7816: ISO78160~ISO78161
  * @retval CHKSUM bit value
  */
uint8_t ISO7816_GetLastReceiveCHKSUM(ISO7816_TypeDef *ISO7816x)
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
