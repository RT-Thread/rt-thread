/**
  ******************************************************************************
  * @file    lib_spi.c 
  * @author  Application Team
  * @version V4.4.0
  * @date    2018-09-27
  * @brief   SPI library.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "lib_spi.h"

#define SPI_MISC_RSTValue    (0UL)

/**
  * @brief  Reset SPI controller.
  * @param  SPIx:SPI1~SPI2
  * @retval None
  */
void SPI_DeviceInit(SPI_TypeDef *SPIx)
{
  __IO uint32_t dummy_data = 0UL;

  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));
  
  /* Disable SPI */
  SPIx->CTRL = 0;
  /* SPI soft reset */
  SPIx->CTRL |= SPI_CTRL_SPIRST;
  SPIx->CTRL &= ~SPI_CTRL_SPIRST;
  /* Clear flag */
  dummy_data = SPIx->RXDAT;
  dummy_data += 1;
  SPIx->TXSTS = SPI_TXSTS_TXIF;
  SPIx->RXSTS = SPI_RXSTS_RXIF;
  /* write default values */
  SPIx->MISC_ = SPI_MISC_RSTValue;
}

/**
  * @brief  Fills each SPI_InitType member with its default value.
  * @param  InitStruct: pointer to an SPI_InitType structure which will be initialized.
  * @retval None
  */
void SPI_StructInit(SPI_InitType *InitStruct)
{
  /*--------------- Reset SPI init structure parameters values ---------------*/
  /* Initialize the ClockDivision member */
  InitStruct->ClockDivision = SPI_CLKDIV_2;
  /* Initialize the CSNSoft member */
  InitStruct->CSNSoft = SPI_CSNSOFT_DISABLE;
  /* Initialize the Mode member */
  InitStruct->Mode = SPI_MODE_MASTER; 
  /* Initialize the SPH member */
  InitStruct->SPH = SPI_SPH_0; 
  /* Initialize the SPO member */
  InitStruct->SPO = SPI_SPO_0; 
  /* Initialize the SWAP member */
  InitStruct->SWAP = SPI_SWAP_DISABLE; 
}

/**
  * @brief  SPI initialization.
  * @param  SPIx:SPI1~SPI2
            InitStruct: SPI configuration.
                Mode:
                    SPI_MODE_MASTER
                    SPI_MODE_SLAVE
                SPH:
                    SPI_SPH_0
                    SPI_SPH_1
                SPO:
                    SPI_SPO_0
                    SPI_SPO_1
                ClockDivision:
                    SPI_CLKDIV_2
                    SPI_CLKDIV_4
                    SPI_CLKDIV_8
                    SPI_CLKDIV_16
                    SPI_CLKDIV_32
                    SPI_CLKDIV_64
                    SPI_CLKDIV_128
                CSNSoft:
                    SPI_CSNSOFT_ENABLE
                    SPI_CSNSOFT_DISABLE
                SWAP:
                    SPI_SWAP_ENABLE
                    SPI_SWAP_DISABLE
  * @retval None
  */
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitType *InitStruct)
{
  uint32_t tmp;
  
  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));  
  assert_parameters(IS_SPI_MODE(InitStruct->Mode));
  assert_parameters(IS_SPI_SPH(InitStruct->SPH));
  assert_parameters(IS_SPI_SPO(InitStruct->SPO));
  assert_parameters(IS_SPI_CLKDIV(InitStruct->ClockDivision));
  assert_parameters(IS_SPI_CSN(InitStruct->CSNSoft));
  assert_parameters(IS_SPI_SWAP(InitStruct->SWAP));
    
  tmp = SPIx->CTRL;
  tmp &= ~(SPI_CTRL_MOD\
          |SPI_CTRL_SCKPHA\
          |SPI_CTRL_SCKPOL\
          |SPI_CTRL_CSGPIO\
          |SPI_CTRL_SWAP\
          |SPI_CTRL_SCKSEL);
  tmp |= (InitStruct->Mode\
         |InitStruct->SPH\
         |InitStruct->SPO\
         |InitStruct->CSNSoft\
         |InitStruct->SWAP\
         |InitStruct->ClockDivision);
  SPIx->CTRL = tmp;
}

/**
  * @brief  Enables or disables SPI.
  * @param  SPIx:SPI1~SPI2
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void SPI_Cmd(SPI_TypeDef *SPIx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx)); 
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));  
  
  if (NewState == ENABLE)
    SPIx->CTRL |= SPI_CTRL_SPIEN;
  else
    SPIx->CTRL &= ~SPI_CTRL_SPIEN;
}

/**
  * @brief  SPI interrupt config.
  * @param  SPIx:SPI1~SPI2
            INTMask: can use the ¡®|¡¯ operator
                SPI_INT_TX     
                SPI_INT_RX
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void SPI_INTConfig(SPI_TypeDef *SPIx, uint32_t INTMask, uint32_t NewState)
{
  uint32_t tmp, tmp_INTMask;
  
  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx)); 
  assert_parameters(IS_SPI_INT(INTMask));
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  tmp_INTMask = INTMask;
  if (tmp_INTMask & 0x80000000)
  {
    INTMask &= 0xFFFF;
    tmp = SPIx->TXSTS;
    tmp &= ~SPI_TXSTS_TXIF;
    if (NewState == ENABLE)
    {
      tmp |= INTMask;
      SPIx->TXSTS = tmp;
    }
    else
    {
      tmp &= ~INTMask;
      SPIx->TXSTS = tmp;
    }
  }
  if (tmp_INTMask & 0x40000000)
  {
    INTMask &= 0xFFFF;
    tmp = SPIx->RXSTS;
    tmp &= ~SPI_RXSTS_RXIF;
    if (NewState == ENABLE)
    {
      tmp |= INTMask;
      SPIx->RXSTS = tmp;
    }
    else
    {
      tmp &= ~INTMask;
      SPIx->RXSTS = tmp;
    }
  }
}

/**
  * @brief  Get status flag.
  * @param  SPIx:SPI1~SPI2
            Status:
                SPI_STS_TXIF   
                SPI_STS_TXEMPTY 
                SPI_STS_TXFUR   
                SPI_STS_RXIF    
                SPI_STS_RXFULL  
                SPI_STS_RXFOV   
                SPI_STS_BSY     
                SPI_STS_RFF     
                SPI_STS_RNE     
                SPI_STS_TNF     
                SPI_STS_TFE     
  * @retval Flag status.
  */
uint8_t SPI_GetStatus(SPI_TypeDef *SPIx, uint32_t Status)
{
  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx)); 
  assert_parameters(IS_SPI_STSR(Status));  
  
  if ((Status&0xE0000000) == 0x80000000)
  {
    if (Status&SPIx->TXSTS)
      return 1;
    else
      return 0;
  }
  else if ((Status&0xE0000000) == 0x40000000)
  {
    if (Status&SPIx->RXSTS)
      return 1;
    else
      return 0;
  }
  else
  {
    if (Status&SPIx->MISC_)
      return 1;
    else
      return 0;
  }
}

/**
  * @brief  Clear status flag.
  * @param  SPIx:SPI1~SPI2
            Status: can use the ¡®|¡¯ operator
                SPI_STS_TXIF     
                SPI_STS_RXIF        
  * @retval None
  */
void SPI_ClearStatus(SPI_TypeDef *SPIx, uint32_t Status)
{
  uint32_t tmp_status;

  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx)); 
  assert_parameters(IS_SPI_STSC(Status));
    
  tmp_status = Status;
  if (tmp_status & 0x80000000)
  {
    Status &= 0xFFFF;
    SPIx->TXSTS |= Status;
  }
  if (tmp_status & 0x40000000)
  {
    Status &= 0xFFFF;
    SPIx->RXSTS |= Status;
  }
}

/**
  * @brief  Load send data register.
  * @param  SPIx:SPI1~SPI2
            ch: data write to send data register
  * @retval None
  */
void SPI_SendData(SPI_TypeDef *SPIx, uint8_t ch)
{
  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx)); 
  
  SPIx->TXDAT = ch;
}

/**
  * @brief  Read receive data register.
  * @param  SPIx:SPI1~SPI2
  * @retval receive data value
  */
uint8_t SPI_ReceiveData(SPI_TypeDef *SPIx)
{
  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx)); 
  
  return (SPIx->RXDAT);
}

/**
  * @brief  Transmit fifo level configure.
  * @param  SPIx:SPI1~SPI2
            FIFOLevel:
                SPI_TXFLEV_0
                SPI_TXFLEV_1
                SPI_TXFLEV_2 
                SPI_TXFLEV_3 
                SPI_TXFLEV_4 
                SPI_TXFLEV_5 
                SPI_TXFLEV_6 
                SPI_TXFLEV_7 
  * @retval None
  */
void SPI_TransmitFIFOLevelConfig(SPI_TypeDef *SPIx, uint32_t FIFOLevel)
{
  uint32_t tmp;

  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx)); 
  assert_parameters(IS_SPI_TXFLEV(FIFOLevel));
  
  tmp = SPIx->TXSTS;
  tmp &= ~(SPI_TXSTS_TXFLEV | SPI_TXSTS_TXIF);
  tmp |= FIFOLevel;
  SPIx->TXSTS = tmp;
}

/**
  * @brief  Receive fifo level configure.
  * @param  SPIx:SPI1~SPI2
            FIFOLevel:
                SPI_RXFLEV_0
                SPI_RXFLEV_1
                SPI_RXFLEV_2 
                SPI_RXFLEV_3 
                SPI_RXFLEV_4 
                SPI_RXFLEV_5 
                SPI_RXFLEV_6 
                SPI_RXFLEV_7 
  * @retval None
  */
void SPI_ReceiveFIFOLevelConfig(SPI_TypeDef *SPIx, uint32_t FIFOLevel)
{
  uint32_t tmp;
    
  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx)); 
  assert_parameters(IS_SPI_RXFLEV(FIFOLevel));
  
  tmp = SPIx->RXSTS;
  tmp &= ~(SPI_RXSTS_RXFLEV | SPI_RXSTS_RXIF);
  tmp |= FIFOLevel;
  SPIx->RXSTS = tmp;
}

/**
  * @brief  Get transmit fifo level.
  * @param  SPIx:SPI1~SPI2
  * @retval Transmit fifo level.
  */
uint8_t SPI_GetTransmitFIFOLevel(SPI_TypeDef *SPIx)
{
  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx)); 
  
  return (SPIx->TXSTS & SPI_TXSTS_TXFFLAG);
}

/**
  * @brief  Get receive fifo level.
  * @param  SPIx:SPI1~SPI2
  * @retval Receive fifo level.
  */
uint8_t SPI_GetReceiveFIFOLevel(SPI_TypeDef *SPIx)
{
  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));  

  return (SPIx->RXSTS & SPI_RXSTS_RXFFLAG);
}

/**
  * @brief  FIFO smart mode.
  * @param  SPIx:SPI1~SPI2
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void SPI_SmartModeCmd(SPI_TypeDef *SPIx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));  
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    SPIx->MISC_ |= SPI_MISC_SMART;
  }
  else
  {
    SPIx->MISC_ &= ~SPI_MISC_SMART;
  }
}

/**
  * @brief  FIFO over write mode.
  * @param  SPIx:SPI1~SPI2
            NewState:
                ENABLE
                DISABLE
  * @retval None
  */
void SPI_OverWriteModeCmd(SPI_TypeDef *SPIx, uint32_t NewState)
{
  /* Check parameters */
  assert_parameters(IS_SPI_ALL_INSTANCE(SPIx));  
  assert_parameters(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState == ENABLE)
  {
    SPIx->MISC_ |= SPI_MISC_OVER;
  }
  else
  {
    SPIx->MISC_ &= ~SPI_MISC_OVER;
  }
}

/*********************************** END OF FILE ******************************/
