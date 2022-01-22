/**
  ******************************************************************************
  * @file    lib_uart.c 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   UART library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_uart.h"
#include "lib_clk.h"

#define UART_STATE_RCMsk       (0x3CUL)
#define UART_INTSTS_RCMsk      (0x3FUL)
#define UART_BAUDDIV_RSTValue  (0UL)
#define UART_CTRL_RSTValue     (0UL)
#define UART_CTRL2_RSTValue    (0UL)

/**
  * @brief  Iinitializes the UARTx peripheral registers to their default reset 
            values.
  * @param  UARTx: UART0~UART5
  * @retval None
  */
void UART_DeInit(UART_TypeDef *UARTx)
{ 
  __IO uint32_t dummy_data = 0UL;
  
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  
  /* read data, clear RXFULL flag */
  dummy_data = UARTx->DATA;
  dummy_data += 1;
    
  UARTx->INTSTS = UART_INTSTS_RCMsk;
  UARTx->STATE = UART_STATE_RCMsk;
  UARTx->BAUDDIV = UART_BAUDDIV_RSTValue;
  UARTx->CTRL2 = UART_CTRL2_RSTValue;
  UARTx->CTRL = UART_CTRL_RSTValue;
}

/**
  * @brief  UART initialization.
  * @param  UARTx: UART0~UART5
            InitStruct:UART configuration.
                Mode: (between UART_MODE_RX and UART_MODE_TX, can use the ¡®|¡¯ operator)
                    UART_MODE_RX
                    UART_MODE_TX
                    UART_MODE_OFF
                Parity:
                    UART_PARITY_EVEN 
                    UART_PARITY_ODD
                    UART_PARITY_0
                    UART_PARITY_1
                    UART_PARITY_NONE
                WordLen:
                    UART_WORDLEN_8B
                    UART_WORDLEN_9B
                FirstBit:
                    UART_FIRSTBIT_LSB
                    UART_FIRSTBIT_MSB
                Baudrate: Baudrate value
  * @retval None
  */
void UART_Init(UART_TypeDef *UARTx, UART_InitType *InitStruct)
{
  uint32_t pclk;
  uint32_t div;
  uint32_t tmp_reg1, tmp_reg2;
  
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_MODE(InitStruct->Mode));
  assert_parameters(IS_UART_PARITY(InitStruct->Parity));
  assert_parameters(IS_UART_WORDLEN(InitStruct->WordLen));
  assert_parameters(IS_UART_FIRSTBIT(InitStruct->FirstBit));
  assert_parameters(IS_UART_BAUDRATE(InitStruct->Baudrate));

  tmp_reg1 = UARTx->CTRL;
  tmp_reg1 &= ~(UART_CTRL_RXEN\
               |UART_CTRL_TXEN);
  tmp_reg1 |= (InitStruct->Mode);
    
  tmp_reg2 = UARTx->CTRL2;
  tmp_reg2 &= ~(UART_CTRL2_MSB \
               |UART_CTRL2_MODE \
               |UART_CTRL2_PMODE);
  tmp_reg2 |= (InitStruct->Parity\
              |InitStruct->WordLen\
              |InitStruct->FirstBit);
  UARTx->CTRL2 = tmp_reg2;
    
  pclk = CLK_GetPCLKFreq();
  div = pclk/InitStruct->Baudrate;
    
  if ((pclk%InitStruct->Baudrate) > (InitStruct->Baudrate/2))
  {
    div++;
  }
  
  UARTx->BAUDDIV = div; 
  UARTx->CTRL = tmp_reg1;
}

/**
  * @brief  Fills each UART_InitType member with its default value.
  * @param  InitStruct: pointer to an UART_InitType structure which will be initialized.
  * @retval None
  */
void UART_StructInit(UART_InitType *InitStruct)
{
  /*-------------- Reset UART init structure parameters values ---------------*/
  /* Initialize the Baudrate member */
  InitStruct->Baudrate = 9600;
  /* Initialize the FirstBit member */
  InitStruct->FirstBit = UART_FIRSTBIT_LSB; 
  /* Initialize the Mode member */
  InitStruct->Mode = UART_MODE_OFF; 
  /* Initialize the Parity member */
  InitStruct->Parity = UART_PARITY_NONE;  
  /* Initialize the WordLen member */
  InitStruct->WordLen = UART_WORDLEN_8B; 
}
                
/**
  * @brief  Get peripheral flag.
  * @param  UARTx: UART0~UART5
            FlagMask: flag to get.
            --UART_FLAG_RXPARITY
            --UART_FLAG_TXDONE  
            --UART_FLAG_RXPE    
            --UART_FLAG_RXOV    
            --UART_FLAG_TXOV    
            --UART_FLAG_RXFULL  
  * @retval 1:flag set
            0:flag reset
  */
uint8_t UART_GetFlag(UART_TypeDef *UARTx, uint32_t FlagMask)
{
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_FLAGR(FlagMask));
  
  if (UARTx->STATE&FlagMask)
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
  * @param  UARTx: UART0~UART5
            FlagMask: status to clear, can use the ¡®|¡¯ operator.
            --UART_FLAG_TXDONE 
            --UART_FLAG_RXPE     
            --UART_FLAG_RXOV     
            --UART_FLAG_TXOV     
  * @retval None
  */
void UART_ClearFlag(UART_TypeDef *UARTx, uint32_t FlagMask)
{
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_FLAGC(FlagMask));
  
  UARTx->STATE = FlagMask;
}

/**
  * @brief  Enable or disable the specified UART interrupts.
  * @param  UARTx: UART0~UART5
            INTMask: can use the ¡®|¡¯ operator.
            --UART_INT_TXDONE
            --UART_INT_RXPE   
            --UART_INT_RXOV   
            --UART_INT_TXOV   
            --UART_INT_RX        
            NewState:New status of interrupt mask.
  * @retval None
  */
void UART_INTConfig(UART_TypeDef *UARTx, uint32_t INTMask, uint8_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_INT(INTMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    UARTx->CTRL |= INTMask;
  }
  else
  {
    UARTx->CTRL &= ~INTMask;
  }
}

/**
  * @brief  Get interrupt status.
  * @param  UARTx: UART0~UART5
            INTMask: status to get.
            --UART_INTSTS_TXDONE
            --UART_INTSTS_RXPE    
            --UART_INTSTS_RXOV    
            --UART_INTSTS_TXOV    
            --UART_INTSTS_RX      
  * @retval 1:status set
            0:status reset
  */
uint8_t UART_GetINTStatus(UART_TypeDef *UARTx, uint32_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_INTFLAGR(INTMask));
  
  if (UARTx->INTSTS&INTMask)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  Clear interrupt status.
  * @param  UARTx: UART0~UART5
            INTMask: status to clear, can use the ¡®|¡¯ operator.
            --UART_INTSTS_TXDONE
            --UART_INTSTS_RXPE  
            --UART_INTSTS_RXOV  
            --UART_INTSTS_TXOV  
            --UART_INTSTS_RX      
  * @retval None
  */
void UART_ClearINTStatus(UART_TypeDef *UARTx, uint32_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_INTFLAGC(INTMask));
  
  UARTx->INTSTS = INTMask;
}

/**
  * @brief  Load send data register.
  * @param  UARTx: UART0~USART5
            DAT: data to send.
  * @retval None
  */
void UART_SendData(UART_TypeDef *UARTx, uint8_t ch)
{
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));  
  
  UARTx->DATA = ch;
}

/**
  * @brief  Read receive data register.
  * @param  UARTx: UART0~UART5
  * @retval The received data.
  */
uint8_t UART_ReceiveData(UART_TypeDef *UARTx)
{
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  
  return UARTx->DATA;
}

/**
  * @brief  UART Baudrate control.
  * @param  UARTx: UART0~UART5
            BaudRate: Baudrate value
  * @retval None
  */
void UART_BaudrateConfig(UART_TypeDef *UARTx, uint32_t BaudRate)
{
  uint32_t pclk;
  uint32_t div;
  
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_BAUDRATE(BaudRate));
    
  pclk = CLK_GetPCLKFreq();
  div = pclk/BaudRate;
  if ((pclk%BaudRate) > (BaudRate/2))
  {
    div++;
  }
    
  UARTx->BAUDDIV = div;
}

/**
  * @brief  UART Transmit/Receive enable control.
  * @param  UARTx: UART0~UART5
            Mode:
                UART_MODE_RX
                UART_MODE_TX
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void UART_Cmd(UART_TypeDef *UARTx, uint32_t Mode, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
  assert_parameters(IS_UART_MODE(Mode));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    UARTx->CTRL |= Mode;
  }
  else
  {
    UARTx->CTRL &= ~Mode;
  }
}

/**
  * @brief  Get UART configure information.
  * @param  UARTx: UART0~UART5
  *         ConfigInfo: The pointer of UART configuration.
  * @retval None
  */
void UART_GetConfigINFO(UART_TypeDef *UARTx, UART_ConfigINFOType *ConfigInfo)
{
  uint32_t tmp1, tmp2, tmp3;
  uint32_t pclk;
  
  /* Check parameters */
  assert_parameters(IS_UART_ALL_INSTANCE(UARTx));
    
  tmp1 = UARTx->CTRL;
  tmp2 = UARTx->BAUDDIV;
  pclk = CLK_GetPCLKFreq();
  tmp3 = UARTx->CTRL2;
    
  /* Mode_Transmit */
  if (tmp1 & UART_CTRL_TXEN)
    ConfigInfo->Mode_Transmit = 1;
  else
    ConfigInfo->Mode_Transmit = 0;
  
  /* Mode_Receive */
  if (tmp1 & UART_CTRL_RXEN)
    ConfigInfo->Mode_Receive = 1;
  else
    ConfigInfo->Mode_Receive = 0;
  
  /* Baudrate */
  ConfigInfo->Baudrate = pclk / tmp2; 
  
  /* LSB/MSB */
  if (tmp3 & UART_CTRL2_MSB)
    ConfigInfo->FirstBit = 1;
  else
    ConfigInfo->FirstBit = 0;
    
  /* WordLen */
  if (tmp3 & UART_CTRL2_MODE)
    ConfigInfo->WordLen = 9;
  else
    ConfigInfo->WordLen = 8;

  /* Parity */
  if ((tmp3 & UART_CTRL2_PMODE) == UART_CTRL2_PMODE_0)
    ConfigInfo->Parity = 0;
  else if ((tmp3 & UART_CTRL2_PMODE) == UART_CTRL2_PMODE_1)
    ConfigInfo->Parity = 1;
  else if ((tmp3 & UART_CTRL2_PMODE) == UART_CTRL2_PMODE_EVEN)
    ConfigInfo->Parity = 2;
  else
    ConfigInfo->Parity = 3;
}

/*********************************** END OF FILE ******************************/
