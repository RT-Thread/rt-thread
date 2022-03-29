/**
  ******************************************************************************
  * @file    lib_u32k.c 
  * @author  Application Team
  * @version V1.1.0
  * @date    2019-10-28
  * @brief   UART 32K library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_u32k.h"

#define U32K_STS_Msk            (0x7UL)
#define U32K_CTRL0_RSTValue     (0UL)
#define U32K_CTRL1_RSTValue     (0UL)
#define U32K_PHASE_RSTValue     (0x4B00UL)

/**
  * @brief  Initializes the U32Kx peripheral registers to their default reset values.
  * @param  U32Kx: U32K0~U32K1
  * @retval None
  */
void U32K_DeInit(U32K_Type *U32Kx)
{
  /* Check parameters */
  assert_parameters(IS_U32K_ALL_INSTANCE(U32Kx));
  
  /* Disable U32K */
  U32Kx->CTRL0 &= ~U32K_CTRL0_EN;
  /* clear interrupt status */
  U32Kx->STS = U32K_STS_Msk;
  /* write default reset values */
  U32Kx->CTRL0 = U32K_CTRL0_RSTValue;
  U32Kx->CTRL1 = U32K_CTRL1_RSTValue;
  U32Kx->BAUDDIV = U32K_PHASE_RSTValue;
}
                    
/**
  * @brief  Initializes U32K.
  * @param  U32Kx:
                U32K0~U32K1
            InitStruct: U32K configuration
                Debsel:
                    U32K_DEBSEL_0
                    U32K_DEBSEL_1
                    U32K_DEBSEL_2
                    U32K_DEBSEL_3
                Parity:
                    U32K_PARITY_EVEN
                    U32K_PARITY_ODD
                    U32K_PARITY_0
                    U32K_PARITY_1
                    U32K_PARITY_NONE
                FirstBit:
                    U32K_FIRSTBIT_LSB
                    U32K_FIRSTBIT_MSB
                AutoCal:
                    U32K_AUTOCAL_ON
                    U32K_AUTOCAL_OFF
                LineSel:
                    U32K_LINE_RX0
                    U32K_LINE_RX1
                    U32K_LINE_RX2
                    U32K_LINE_RX3
                Baudrate: Baudrate value, 300UL ~ 14400UL
  * @retval None
  */
void U32K_Init(U32K_Type *U32Kx, U32K_InitType *InitStruct)
{
  uint32_t tmp_reg1, tmp_reg2;
  
  /* Check parameters */
  assert_parameters(IS_U32K_ALL_INSTANCE(U32Kx));
  assert_parameters(IS_U32K_DEBSEL(InitStruct->Debsel));
  assert_parameters(IS_U32K_PARITY(InitStruct->Parity));
  assert_parameters(IS_U32K_FIRSTBIT(InitStruct->FirstBit));
  assert_parameters(IS_U32K_AUTOCAL(InitStruct->AutoCal));
  assert_parameters(IS_U32K_LINE(InitStruct->LineSel));
  assert_parameters(IS_U32K_BAUDRATE(InitStruct->Baudrate));
    
  tmp_reg1 = U32Kx->CTRL0;
  tmp_reg1 &= ~(U32K_CTRL0_DEBSEL\
               |U32K_CTRL0_PMODE\
               |U32K_CTRL0_MSB\
               |U32K_CTRL0_ACOFF);
  tmp_reg1 |= (InitStruct->Debsel\
              |InitStruct->Parity\
              |InitStruct->FirstBit\
              |InitStruct->AutoCal);
  U32Kx->CTRL0 = tmp_reg1;
  if ((RTC->PSCA & RTC_PSCA_PSCA) == RTC_PSCA_PSCA_0) //RTCCLK 32768Hz
    U32Kx->BAUDDIV = 65536*InitStruct->Baudrate/32768;
  else if ((RTC->PSCA & RTC_PSCA_PSCA) == RTC_PSCA_PSCA_1) //RTCCLK 8192Hz
    U32Kx->BAUDDIV = 65536*InitStruct->Baudrate/8192;
  else
    assert_parameters(0);
    
  tmp_reg2 = U32Kx->CTRL1;
  tmp_reg2 &= ~(U32K_CTRL1_RXSEL);
  tmp_reg2 |= (InitStruct->LineSel);
  U32Kx->CTRL1 = tmp_reg2;
}

/**
  * @brief  Fills each U32K_InitType member with its default value.
  * @param  InitStruct: pointer to an U32K_InitType structure which will be initialized.
  * @retval None
  */
void U32K_StructInit(U32K_InitType *InitStruct)
{
  /*-------------- Reset U32K init structure parameters values ---------------*/
  /* Initialize the AutoCal member */
  InitStruct->AutoCal = U32K_AUTOCAL_ON;
  /* Initialize the Baudrate member */
  InitStruct->Baudrate = 9600;
  /* Initialize the Debsel member */
  InitStruct->Debsel = U32K_DEBSEL_0;
  /* Initialize the FirstBit member */
  InitStruct->FirstBit = U32K_FIRSTBIT_LSB;
  /* Initialize the LineSel member */
  InitStruct->LineSel = U32K_LINE_RX0;  
  /* Initialize the Parity member */
  InitStruct->Parity = U32K_PARITY_NONE;
}

/**
  * @brief  Enables or disables U32K interrupt.
  * @param  U32Kx:
                U32K0~U32K1
            INTMask: can use the '|' operator
                U32K_INT_RXOV
                U32K_INT_RXPE
                U32K_INT_RX 
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void U32K_INTConfig(U32K_Type *U32Kx, uint32_t INTMask, uint8_t NewState)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_U32K_ALL_INSTANCE(U32Kx));
  assert_parameters(IS_U32K_INT(INTMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
    
  tmp = U32Kx->CTRL1;
  tmp &= ~INTMask;
  if (NewState == ENABLE)
  {
    tmp |= INTMask;
  }
  U32Kx->CTRL1 = tmp;
}

/**
  * @brief  Gets interrupt flag status.
  * @param  U32Kx:
                U32K0~U32K1
            INTMask:
                U32K_INTSTS_RXOV
                U32K_INTSTS_RXPE
                U32K_INTSTS_RX 
  * @retval Flag status
  */
uint8_t U32K_GetINTStatus(U32K_Type *U32Kx, uint32_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_U32K_ALL_INSTANCE(U32Kx));
  assert_parameters(IS_U32K_INTFLAGR(INTMask));
  
  if (U32Kx->STS&INTMask)
    return 1;
  else
    return 0;
}

/**
  * @brief  Clears flag status.
  * @param  U32Kx:
                U32K0~U32K1
            INTMask: can use the '|' operator
                U32K_INTSTS_RXOV
                U32K_INTSTS_RXPE
                U32K_INTSTS_RX 
  * @retval None
  */
void U32K_ClearINTStatus(U32K_Type *U32Kx, uint32_t INTMask)
{
  /* Check parameters */
  assert_parameters(IS_U32K_ALL_INSTANCE(U32Kx));
  assert_parameters(IS_U32K_INTFLAGC(INTMask));
  
  U32Kx->STS = INTMask;
}

/**
  * @brief  Reads receive data register.
  * @param  U32Kx:
                U32K0~U32K1
  * @retval Receive data value
  */
uint8_t U32K_ReceiveData(U32K_Type *U32Kx)
{
  /* Check parameters */
  assert_parameters(IS_U32K_ALL_INSTANCE(U32Kx));
  
  return (U32Kx->DATA);
}

/**
  * @brief  Configures U32K baudrate.
  * @param  U32Kx: U32K0~U32K1
            BaudRate: Baudrate value
  * @retval None
  */
void U32K_BaudrateConfig(U32K_Type *U32Kx, uint32_t BaudRate)
{
  /* Check parameters */
  assert_parameters(IS_U32K_ALL_INSTANCE(U32Kx));
  assert_parameters(IS_U32K_BAUDRATE(BaudRate));
  
  if ((RTC->PSCA & RTC_PSCA_PSCA) == RTC_PSCA_PSCA_0) //RTCCLK 32768Hz
    U32Kx->BAUDDIV = 65536*BaudRate/32768;
  else if ((RTC->PSCA & RTC_PSCA_PSCA) == RTC_PSCA_PSCA_1) //RTCCLK 8192Hz
    U32Kx->BAUDDIV = 65536*BaudRate/8192;
  else
    assert_parameters(0);
}

/**
  * @brief  Enables or disables U32K controlller.
  * @param  U32Kx:
                U32K0~U32K1
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void U32K_Cmd(U32K_Type *U32Kx, uint32_t NewState)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_U32K_ALL_INSTANCE(U32Kx));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  tmp = U32Kx->CTRL0;
  tmp &= ~(U32K_CTRL0_EN);
  if (NewState == ENABLE)
  {
    tmp |= U32K_CTRL0_EN;
  }
  U32Kx->CTRL0 = tmp;
}

/**
  * @brief  Configures U32K receive line.
  * @param  U32Kx:
                U32K0~U32K1
            Line:
                U32K_LINE_RX0
                U32K_LINE_RX1 
                U32K_LINE_RX2 
                U32K_LINE_RX3 
  * @retval None
  */
void U32K_LineConfig(U32K_Type *U32Kx, uint32_t Line)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_U32K_ALL_INSTANCE(U32Kx));
  assert_parameters(IS_U32K_LINE(Line));  

  tmp = U32Kx->CTRL1;
  tmp &= ~U32K_CTRL1_RXSEL_Msk;
  tmp |= Line;

  U32Kx->CTRL1 = tmp;
}

/**
  * @brief  Configures Wake-up mode.
  * @param  U32Kx:
                U32K0~U32K1
            WKUMode:
                U32K_WKUMOD_RX
                U32K_WKUMOD_PC
  * @retval None
  */
void U32K_WKUModeConfig(U32K_Type *U32Kx, uint32_t WKUMode)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_U32K_ALL_INSTANCE(U32Kx));
  assert_parameters(IS_U32K_WKUMODE(WKUMode));
  
  tmp = U32Kx->CTRL0;
  tmp &= ~U32K_CTRL0_WKUMODE_Msk;
  tmp |= WKUMode;
  U32Kx->CTRL0 = tmp;
}

/*********************************** END OF FILE ******************************/
