/**
 **************************************************************************
 * File Name    : at32f4xx_spi.c
 * Description  : at32f4xx SPI source file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_spi.h"
#include "at32f4xx_rcc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup SPI
  * @brief SPI driver modules
  * @{
  */

/** @defgroup SPI_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */


/** @defgroup SPI_Private_Defines
  * @{
  */

/* SPI SPE mask */
#define CTRL1_SPIEN_SET         ((uint16_t)0x0040)
#define CTRL1_SPIEN_RESET       ((uint16_t)0xFFBF)

/* I2S I2SE mask */
#define I2SCTRL_I2SEN_SET       ((uint16_t)0x0400)
#define I2SCTRL_I2SEN_RESET     ((uint16_t)0xFBFF)

/* SPI CRCNext mask */
#define CTRL1_CTN_SET           ((uint16_t)0x1000)

/* SPI CRCEN mask */
#define CTRL1_CCE_SET           ((uint16_t)0x2000)
#define CTRL1_CCE_RESET         ((uint16_t)0xDFFF)

/* SPI SSOE mask */
#define CTRL2_NSSOE_SET         ((uint16_t)0x0004)
#define CTRL2_NSSOE_RESET       ((uint16_t)0xFFFB)

/* SPI registers Masks */
#define CTRL1_CLEAR_MASK        ((uint16_t)0x3040)
#define I2SCTRL_CLEAR_MASK      ((uint16_t)0xF040)

/* SPI or I2S mode selection masks */
#define SPI_MODE_SEL            ((uint16_t)0xF7FF)
#define I2S_MODE_SEL            ((uint16_t)0x0800)

/* I2S clock source selection masks */
#define I2S2_CLK_SRC            ((uint32_t)(0x00020000))
#define I2S3_CLK_SRC            ((uint32_t)(0x00040000))
#define I2S_MUL_MASK            ((uint32_t)(0x0000F000))
#define I2S_DIV_MASK            ((uint32_t)(0x000000F0))

/**
  * @}
  */

/** @defgroup SPI_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup SPI_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup SPI_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup SPI_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the SPIx peripheral registers to their default
  *         reset values (Affects also the I2Ss).
  * @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
  * @retval None
  */
void SPI_I2S_Reset(SPI_Type* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  if (SPIx == SPI1)
  {
    /* Enable SPI1 reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_SPI1, ENABLE);
    /* Release SPI1 from reset state */
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_SPI1, DISABLE);
  }
  else if (SPIx == SPI2)
  {
    /* Enable SPI2 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_SPI2, ENABLE);
    /* Release SPI2 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_SPI2, DISABLE);
  }
#if defined (AT32F403xx) || defined (AT32F403Axx) || \
    defined (AT32F407xx)
  else if (SPIx == SPI3)
  {
    /* Enable SPI3 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_SPI3, ENABLE);
    /* Release SPI3 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_SPI3, DISABLE);
  }
  else if (SPIx == SPI4)
  {
    /* Enable SPI4 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_SPI4, ENABLE);
    /* Release SPI4 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_SPI4, DISABLE);
  }
#endif
}

/**
  * @brief  Initializes the SPIx peripheral according to the specified
  *         parameters in the SPI_InitStruct.
  * @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
  * @param  SPI_InitStruct: pointer to a SPI_InitType structure that
  *         contains the configuration information for the specified SPI peripheral.
  * @retval None
  */
void SPI_Init(SPI_Type* SPIx, SPI_InitType* SPI_InitStruct)
{
  uint16_t tmpreg = 0;

  /* check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Check the SPI parameters */
  assert_param(IS_SPI_TRANS_MODE(SPI_InitStruct->SPI_TransMode));
  assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
  assert_param(IS_SPI_FRAMESIZE(SPI_InitStruct->SPI_FrameSize));
  assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  assert_param(IS_SPI_NSSSEL(SPI_InitStruct->SPI_NSSSEL));
  assert_param(IS_SPI_MCLKP(SPI_InitStruct->SPI_MCLKP));
  assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
  assert_param(IS_SPI_CPOLY(SPI_InitStruct->SPI_CPOLY));

  /*---------------------------- SPIx CTRL1 Configuration ------------------------*/
  /* Get the SPIx CTRL1 value */
  tmpreg = SPIx->CTRL1;
  /* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
  tmpreg &= CTRL1_CLEAR_MASK;
  /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
     master/salve mode, CPOL and CPHA */
  /* Set BIDImode, BIDIOE and RxONLY bits according to SPI_Direction value */
  /* Set SSM, SSI and MSTR bits according to SPI_Mode and SPI_NSS values */
  /* Set LSBFirst bit according to SPI_FirstBit value */
  /* Set BR bits according to SPI_BaudRatePrescaler value */
  /* Set CPOL bit according to SPI_CPOL value */
  /* Set CPHA bit according to SPI_CPHA value */

  if (SPI_InitStruct->SPI_MCLKP & SPI_MCLKP_OVER_256)
  {
    /* MCLKP is over 256 */
    SPIx->CTRL2 |= SPI_CTRL2_MCLKP_3;
  }
  else
  {
    SPIx->CTRL2 &= ~SPI_CTRL2_MCLKP_3;
  }

  tmpreg |= (uint16_t)((uint32_t)SPI_InitStruct->SPI_TransMode | SPI_InitStruct->SPI_Mode |
                       SPI_InitStruct->SPI_FrameSize | SPI_InitStruct->SPI_CPOL |
                       SPI_InitStruct->SPI_CPHA | SPI_InitStruct->SPI_NSSSEL |
                       (SPI_InitStruct->SPI_MCLKP & 0x7FFF) | SPI_InitStruct->SPI_FirstBit);
  /* Write to SPIx CTRL1 */
  SPIx->CTRL1 = tmpreg;


  /* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
  SPIx->I2SCTRL &= SPI_MODE_SEL;

  /*---------------------------- SPIx CRCPOLY Configuration --------------------*/
  /* Write to SPIx CRCPOLY */
  SPIx->CPOLY = SPI_InitStruct->SPI_CPOLY;
}

/**
  * @brief  Initializes the SPIx peripheral according to the specified
  *         parameters in the I2S_InitStruct.
  * @param  SPIx: where x can be 2, 3, or 4 to select the SPI peripheral
  *         (configured in I2S mode).
  * @param  I2S_InitStruct: pointer to an I2S_InitType structure that
  *         contains the configuration information for the specified SPI peripheral
  *         configured in I2S mode.
  * @note
  *  The function calculates the optimal prescaler needed to obtain the most
  *  accurate audio frequency (depending on the I2S clock source, the PLL values
  *  and the product configuration). But in case the prescaler value is greater
  *  than 511, the default value (0x02) will be configured instead.  *
  * @retval None
  */
void I2S_Init(SPI_Type* SPIx, I2S_InitType* I2S_InitStruct)
{
  uint16_t tmpreg = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
  uint32_t tmp = 0;
  RCC_ClockType RCC_Clocks;
  uint32_t sourceclock = 0;

  /* Check the I2S parameters */
  assert_param(IS_SPI_I2S_PERIPH(SPIx));
  assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
  assert_param(IS_I2S_AUDIOPROTOCOL(I2S_InitStruct->I2s_AudioProtocol));
  assert_param(IS_I2S_FRAMEFORMAT(I2S_InitStruct->I2S_FrameFormat));
  assert_param(IS_I2S_MCLKOE(I2S_InitStruct->I2S_MCLKOE));
  assert_param(IS_I2S_AUDIO_FREQ(I2S_InitStruct->I2S_AudioFreq));
  assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));

  /*----------------------- SPIx I2SCFGR & I2SPR Configuration -----------------*/
  /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
  SPIx->I2SCTRL &= I2SCTRL_CLEAR_MASK;
  SPIx->I2SCLKP = 0x0002;

  /* Get the I2SCFGR register value */
  tmpreg = SPIx->I2SCTRL;

  /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/
  if(I2S_InitStruct->I2S_AudioFreq == I2S_AUDIOFREQ_DEFAULT)
  {
    i2sodd = (uint16_t)0;
    i2sdiv = (uint16_t)2;
  }
  /* If the requested audio frequency is not the default, compute the prescaler */
  else
  {
    /* Check the frame length (For the Prescaler computing) */
    if(I2S_InitStruct->I2S_FrameFormat == I2S_FRAMEFORMAT_DL16BIT_CHL16BIT)
    {
      /* Packet length is 16 bits */
      packetlength = 1;
    }
    else
    {
      /* Packet length is 32 bits */
      packetlength = 2;
    }

    /* Get the I2S clock source mask depending on the peripheral number */
    if(((uint32_t)SPIx) == SPI2_BASE)
    {
      /* The mask is relative to I2S2 */
      tmp = I2S2_CLK_SRC;
    }
    else
    {
      /* The mask is relative to I2S3 */
      tmp = I2S3_CLK_SRC;
    }

    /* Check the I2S clock source configuration depending on the Device */
    /* I2S Clock source is System clock: Get System Clock frequency */
    RCC_GetClocksFreq(&RCC_Clocks);

    /* Get the source clock value: based on System Clock value */
    sourceclock = RCC_Clocks.SYSCLK_Freq;

    /* Compute the Real divider depending on the MCLK output state with a floating point */
    if(I2S_InitStruct->I2S_MCLKOE == I2S_MCLKOE_ENABLE)
    {
      /* MCLK output is enabled */
      tmp = (uint16_t)(((((sourceclock / 256) * 10) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    else
    {
      /* MCLK output is disabled */
      tmp = (uint16_t)(((((sourceclock / (32 * packetlength)) * 10 ) / I2S_InitStruct->I2S_AudioFreq)) + 5);
    }

    /* Remove the floating point */
    tmp = tmp / 10;

    /* Check the parity of the divider */
    i2sodd = (uint16_t)(tmp & (uint16_t)0x0001);

    /* Compute the i2sdiv prescaler */
    i2sdiv = (uint16_t)((tmp - i2sodd) / 2);

    /* Get the Mask for the Odd bit (SPI_I2SPR[8]) register */
    i2sodd = (uint16_t) (i2sodd << 8);
  }

  /* Test if the divider is 1 or 0 or greater than 0xFF */
  if ((i2sdiv < 2) || (i2sdiv > I2S_DIV_VALUE_MAX))
  {
    /* Set the default values */
    i2sdiv = 2;
    i2sodd = 0;
  }
  else if (i2sdiv & I2S_DIV_EXT_VALUE_MASK)
  {
    /* Shift I2SDIV[9:8] to SPI_I2SCLKP[11:10] */
    i2sdiv |= ((i2sdiv & I2S_DIV_EXT_VALUE_MASK) << I2S_DIV_EXT_VALUE_LSHIFT_OFFSET);
    i2sdiv &= ~I2S_DIV_EXT_VALUE_MASK;
  }

  /* Write to SPIx I2SPR register the computed value */
  SPIx->I2SCLKP = (uint16_t)(i2sdiv | (uint16_t)(i2sodd | (uint16_t)I2S_InitStruct->I2S_MCLKOE));

  /* Configure the I2S with the SPI_InitStruct values */
  tmpreg |= (uint16_t)(I2S_MODE_SEL | (uint16_t)(I2S_InitStruct->I2S_Mode | \
                       (uint16_t)(I2S_InitStruct->I2s_AudioProtocol | (uint16_t)(I2S_InitStruct->I2S_FrameFormat | \
                                  (uint16_t)I2S_InitStruct->I2S_CPOL))));

  /* Write to SPIx I2SCFGR */
  SPIx->I2SCTRL = tmpreg;
}

/**
  * @brief  Fills each SPI_InitStruct member with its default value.
  * @param  SPI_InitStruct : pointer to a SPI_InitType structure which will be initialized.
  * @retval None
  */
void SPI_DefaultInitParaConfig(SPI_InitType* SPI_InitStruct)
{
  /*--------------- Reset SPI init structure parameters values -----------------*/
  /* Initialize the SPI_Direction member */
  SPI_InitStruct->SPI_TransMode = SPI_TRANSMODE_FULLDUPLEX;
  /* initialize the SPI_Mode member */
  SPI_InitStruct->SPI_Mode = SPI_MODE_SLAVE;
  /* initialize the SPI_DataSize member */
  SPI_InitStruct->SPI_FrameSize = SPI_FRAMESIZE_8BIT;
  /* Initialize the SPI_CPOL member */
  SPI_InitStruct->SPI_CPOL = SPI_CPOL_LOW;
  /* Initialize the SPI_CPHA member */
  SPI_InitStruct->SPI_CPHA = SPI_CPHA_1EDGE;
  /* Initialize the SPI_NSS member */
  SPI_InitStruct->SPI_NSSSEL = SPI_NSSSEL_HARD;
  /* Initialize the SPI_BaudRatePrescaler member */
  SPI_InitStruct->SPI_MCLKP = SPI_MCLKP_2;
  /* Initialize the SPI_FirstBit member */
  SPI_InitStruct->SPI_FirstBit = SPI_FIRSTBIT_MSB;
  /* Initialize the SPI_CRCPolynomial member */
  SPI_InitStruct->SPI_CPOLY = 7;
}

/**
  * @brief  Fills each I2S_InitStruct member with its default value.
  * @param  I2S_InitStruct : pointer to a I2S_InitType structure which will be initialized.
  * @retval None
  */
void I2S_DefaultInit(I2S_InitType* I2S_InitStruct)
{
  /*--------------- Reset I2S init structure parameters values -----------------*/
  /* Initialize the I2S_Mode member */
  I2S_InitStruct->I2S_Mode = I2S_MODE_SLAVETX;

  /* Initialize the I2S_Standard member */
  I2S_InitStruct->I2s_AudioProtocol = I2S_AUDIOPROTOCOL_PHILLIPS;

  /* Initialize the I2S_DataFormat member */
  I2S_InitStruct->I2S_FrameFormat = I2S_FRAMEFORMAT_DL16BIT_CHL16BIT;

  /* Initialize the I2S_MCLKOutput member */
  I2S_InitStruct->I2S_MCLKOE = I2S_MCLKOE_DISABLE;

  /* Initialize the I2S_AudioFreq member */
  I2S_InitStruct->I2S_AudioFreq = I2S_AUDIOFREQ_DEFAULT;

  /* Initialize the I2S_CPOL member */
  I2S_InitStruct->I2S_CPOL = I2S_CPOL_LOW;
}

/**
  * @brief  Enables or disables the specified SPI peripheral.
  * @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
  * @param  NewState: new state of the SPIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_Enable(SPI_Type* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI peripheral */
    SPIx->CTRL1 |= CTRL1_SPIEN_SET;
  }
  else
  {
    /* Disable the selected SPI peripheral */
    SPIx->CTRL1 &= CTRL1_SPIEN_RESET;
  }
}

/**
  * @brief  Enables or disables the specified SPI peripheral (in I2S mode).
  * @param  SPIx: where x can be 2, 3, or 4 to select the SPI peripheral.
  * @param  NewState: new state of the SPIx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2S_Enable(SPI_Type* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_I2S_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI peripheral (in I2S mode) */
    SPIx->I2SCTRL |= I2SCTRL_I2SEN_SET;
  }
  else
  {
    /* Disable the selected SPI peripheral (in I2S mode) */
    SPIx->I2SCTRL &= I2SCTRL_I2SEN_RESET;
  }
}

/**
  * @brief  Enables or disables the specified SPI/I2S interrupts.
  * @param  SPIx: where x can be
  *   - 1, 2, 3, or 4 in SPI mode
  *   - 2, 3, or 4 in I2S mode
  * @param  SPI_I2S_INT: specifies the SPI/I2S interrupt source to be enabled or disabled.
  *   This parameter can be one of the following values:
  *     @arg SPI_I2S_INT_TE: Tx buffer empty interrupt mask
  *     @arg SPI_I2S_INT_RNE: Rx buffer not empty interrupt mask
  *     @arg SPI_I2S_INT_ERR: Error interrupt mask
  * @param  NewState: new state of the specified SPI/I2S interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_I2S_INTConfig(SPI_Type* SPIx, uint8_t SPI_I2S_INT, FunctionalState NewState)
{
  uint16_t itpos = 0, itmask = 0 ;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_CONFIG_INT(SPI_I2S_INT));

  /* Get the SPI/I2S INT index */
  itpos = SPI_I2S_INT >> 4;

  /* Set the INT mask */
  itmask = (uint16_t)1 << (uint16_t)itpos;

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI/I2S interrupt */
    SPIx->CTRL2 |= itmask;
  }
  else
  {
    /* Disable the selected SPI/I2S interrupt */
    SPIx->CTRL2 &= (uint16_t)~itmask;
  }
}

/**
  * @brief  Enables or disables the SPIx/I2Sx DMA interface.
  * @param  SPIx: where x can be
  *   - 1, 2, 3, or 4 in SPI mode
  *   - 2, 3, or 4 in I2S mode
  * @param  SPI_I2S_DMAReq: specifies the SPI/I2S DMA transfer request to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg SPI_I2S_DMA_TX: Tx buffer DMA transfer request
  *     @arg SPI_I2S_DMA_RX: Rx buffer DMA transfer request
  * @param  NewState: new state of the selected SPI/I2S DMA transfer request.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_I2S_DMAEnable(SPI_Type* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_DMA(SPI_I2S_DMAReq));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI/I2S DMA requests */
    SPIx->CTRL2 |= SPI_I2S_DMAReq;
  }
  else
  {
    /* Disable the selected SPI/I2S DMA requests */
    SPIx->CTRL2 &= (uint16_t)~SPI_I2S_DMAReq;
  }
}

/**
  * @brief  Transmits a Data through the SPIx/I2Sx peripheral.
  * @param  SPIx: where x can be
  *   - 1, 2, 3, or 4 in SPI mode
  *   - 2, 3, or 4 in I2S mode
  * @param  Data : Data to be transmitted.
  * @retval None
  */
void SPI_I2S_TxData(SPI_Type* SPIx, uint16_t Data)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Write in the DR register the data to be sent */
  SPIx->DT = Data;
}

/**
  * @brief  Returns the most recent received data by the SPIx/I2Sx peripheral.
  * @param  SPIx: where x can be
  *   - 1, 2, 3, or 4 in SPI mode
  *   - 2, 3, or 4 in I2S mode
  * @retval The value of the received data.
  */
uint16_t SPI_I2S_RxData(SPI_Type* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Return the data in the DR register */
  return SPIx->DT;
}

/**
  * @brief  Configures internally by software the NSS pin for the selected SPI.
  * @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
  * @param  SPI_NSSInternalSoft: specifies the SPI NSS internal state.
  *   This parameter can be one of the following values:
  *     @arg SPI_ISS_SET: Set NSS pin internally
  *     @arg SPI_ISS_RESET: Reset NSS pin internally
  * @retval None
  */
void SPI_NSSInternalSoftwareConfig(SPI_Type* SPIx, uint16_t SPI_NSSInternalSoft)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_ISS(SPI_NSSInternalSoft));

  if (SPI_NSSInternalSoft != SPI_ISS_RESET)
  {
    /* Set NSS pin internally by software */
    SPIx->CTRL1 |= SPI_ISS_SET;
  }
  else
  {
    /* Reset NSS pin internally by software */
    SPIx->CTRL1 &= SPI_ISS_RESET;
  }
}

/**
  * @brief  Enables or disables the SS output for the selected SPI.
  * @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
  * @param  NewState: new state of the SPIx SS output.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_NSSHardwareOutputEnable(SPI_Type* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI SS output */
    SPIx->CTRL2 |= CTRL2_NSSOE_SET;
  }
  else
  {
    /* Disable the selected SPI SS output */
    SPIx->CTRL2 &= CTRL2_NSSOE_RESET;
  }
}

/**
  * @brief  Configures the data size for the selected SPI.
  * @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
  * @param  SPI_DataSize: specifies the SPI data size.
  *   This parameter can be one of the following values:
  *     @arg SPI_FRAMESIZE_16BIT: Set data frame format to 16bit
  *     @arg SPI_FRAMESIZE_8BIT: Set data frame format to 8bit
  * @retval None
  */
void SPI_FrameSizeConfig(SPI_Type* SPIx, uint16_t SPI_DataSize)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_FRAMESIZE(SPI_DataSize));
  /* Clear DFF bit */
  SPIx->CTRL1 &= (uint16_t)~SPI_FRAMESIZE_16BIT;
  /* Set new DFF bit value */
  SPIx->CTRL1 |= SPI_DataSize;
}

/**
  * @brief  Transmit the SPIx CRC value.
  * @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
  * @retval None
  */
void SPI_TxCRC(SPI_Type* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Enable the selected SPI CRC transmission */
  SPIx->CTRL1 |= CTRL1_CTN_SET;
}

/**
  * @brief  Enables or disables the CRC value calculation of the transferred bytes.
  * @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
  * @param  NewState: new state of the SPIx CRC value calculation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_CRCEN(SPI_Type* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI CRC calculation */
    SPIx->CTRL1 |= CTRL1_CCE_SET;
  }
  else
  {
    /* Disable the selected SPI CRC calculation */
    SPIx->CTRL1 &= CTRL1_CCE_RESET;
  }
}

/**
  * @brief  Returns the transmit or the receive CRC register value for the specified SPI.
  * @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
  * @param  SPI_CRC: specifies the CRC register to be read.
  *   This parameter can be one of the following values:
  *     @arg SPI_CRC_TX: Selects Tx CRC register
  *     @arg SPI_CRC_RX: Selects Rx CRC register
  * @retval The selected CRC register value..
  */
uint16_t SPI_GetCRC(SPI_Type* SPIx, uint8_t SPI_CRC)
{
  uint16_t crcreg = 0;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_CRC(SPI_CRC));

  if (SPI_CRC != SPI_CRC_RX)
  {
    /* Get the Tx CRC register */
    crcreg = SPIx->TCRC;
  }
  else
  {
    /* Get the Rx CRC register */
    crcreg = SPIx->RCRC;
  }

  /* Return the selected CRC register */
  return crcreg;
}

/**
  * @brief  Returns the CRC Polynomial register value for the specified SPI.
  * @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
  * @retval The CRC Polynomial register value.
  */
uint16_t SPI_GetCRCPolynomial(SPI_Type* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));

  /* Return the CRC polynomial register */
  return SPIx->CPOLY;
}

/**
  * @brief  Selects the data transfer direction in bi-directional mode for the specified SPI.
  * @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
  * @param  SPI_Direction: specifies the data transfer direction in bi-directional mode.
  *   This parameter can be one of the following values:
  *     @arg SPI_HALFDUPLEX_TX: Selects Tx transmission direction
  *     @arg SPI_HALFDUPLEX_RX: Selects Rx receive direction
  * @retval None
  */
void SPI_HalfDuplexTransModeConfig(SPI_Type* SPIx, uint16_t SPI_Direction)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DIRECTION(SPI_Direction));

  if (SPI_Direction == SPI_HALFDUPLEX_TX)
  {
    /* Set the Tx only mode */
    SPIx->CTRL1 |= SPI_HALFDUPLEX_TX;
  }
  else
  {
    /* Set the Rx only mode */
    SPIx->CTRL1 &= SPI_HALFDUPLEX_RX;
  }
}

/**
  * @brief  Checks whether the specified SPI/I2S flag is set or not.
  * @param  SPIx: where x can be
  *   - 1, 2, 3, or 4 in SPI mode
  *   - 2, 3, or 4 in I2S mode
  * @param  SPI_I2S_FLAG: specifies the SPI/I2S flag to check.
  *   This parameter can be one of the following values:
  *     @arg SPI_I2S_FLAG_TE: Transmit buffer empty flag.
  *     @arg SPI_I2S_FLAG_RNE: Receive buffer not empty flag.
  *     @arg SPI_I2S_FLAG_BUSY: Busy flag.
  *     @arg SPI_I2S_FLAG_OVR: Overrun flag.
  *     @arg SPI_FLAG_MODF: Mode Fault flag.
  *     @arg SPI_FLAG_CERR: CRC Error flag.
  *     @arg I2S_FLAG_UDR: Underrun Error flag.
  *     @arg I2S_FLAG_CS: Channel Side flag.
  * @retval The new state of SPI_I2S_FLAG (SET or RESET).
  */
FlagStatus SPI_I2S_GetFlagStatus(SPI_Type* SPIx, uint16_t SPI_I2S_FLAG)
{
  FlagStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_GET_FLAG(SPI_I2S_FLAG));

  /* Check the status of the specified SPI/I2S flag */
  if ((SPIx->STS & SPI_I2S_FLAG) != (uint16_t)RESET)
  {
    /* SPI_I2S_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* SPI_I2S_FLAG is reset */
    bitstatus = RESET;
  }

  /* Return the SPI_I2S_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the SPIx CRC Error (CRCERR) flag.
  * @param  SPIx: where x can be
  *   - 1, 2, 3, or 4 in SPI mode
  * @param  SPI_I2S_FLAG: specifies the SPI flag to clear.
  *   This function clears only CRCERR flag.
  * @note
  *   - OVR (OverRun error) flag is cleared by software sequence: a read
  *     operation to SPI_DT register (SPI_I2S_RxData()) followed by a read
  *     operation to SPI_STS register (SPI_I2S_GetFlagStatus()).
  *   - UDR (UnderRun error) flag is cleared by a read operation to
  *     SPI_STS register (SPI_I2S_GetFlagStatus()).
  *   - MODF (Mode Fault) flag is cleared by software sequence: a read/write
  *     operation to SPI_STS register (SPI_I2S_GetFlagStatus()) followed by a
  *     write operation to SPI_CTRL1 register (SPI_Enable() to enable the SPI).
  * @retval None
  */
void SPI_I2S_ClearFlag(SPI_Type* SPIx, uint16_t SPI_I2S_FLAG)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_CLEAR_FLAG(SPI_I2S_FLAG));

  /* Clear the selected SPI CRC Error (CRCERR) flag */
  SPIx->STS = (uint16_t)~SPI_I2S_FLAG;
}

/**
  * @brief  Checks whether the specified SPI/I2S interrupt has occurred or not.
  * @param  SPIx: where x can be
  *   - 1, 2, 3, or 4 in SPI mode
  *   - 2, 3, or 4 in I2S mode
  * @param  SPI_I2S_INT: specifies the SPI/I2S interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg SPI_I2S_INT_TE: Transmit buffer empty interrupt.
  *     @arg SPI_I2S_INT_RNE: Receive buffer not empty interrupt.
  *     @arg SPI_I2S_INT_OVR: Overrun interrupt.
  *     @arg SPI_INT_MODF: Mode Fault interrupt.
  *     @arg SPI_INT_CERR: CRC Error interrupt.
  *     @arg I2S_INT_UDR: Underrun Error interrupt.
  * @retval The new state of SPI_I2S_INT (SET or RESET).
  */
ITStatus SPI_I2S_GetITStatus(SPI_Type* SPIx, uint8_t SPI_I2S_INT)
{
  ITStatus bitstatus = RESET;
  uint16_t itpos = 0, itmask = 0, enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_GET_INT(SPI_I2S_INT));

  /* Get the SPI/I2S INT index */
  itpos = 0x01 << (SPI_I2S_INT & 0x0F);

  /* Get the SPI/I2S INT mask */
  itmask = SPI_I2S_INT >> 4;

  /* Set the INT mask */
  itmask = 0x01 << itmask;

  /* Get the SPI_I2S_INT enable bit status */
  enablestatus = (SPIx->CTRL2 & itmask) ;

  /* Check the status of the specified SPI/I2S interrupt */
  if (((SPIx->STS & itpos) != (uint16_t)RESET) && enablestatus)
  {
    /* SPI_I2S_INT is set */
    bitstatus = SET;
  }
  else
  {
    /* SPI_I2S_INT is reset */
    bitstatus = RESET;
  }

  /* Return the SPI_I2S_INT status */
  return bitstatus;
}

/**
  * @brief  Clears the SPIx CRC Error (CRCERR) interrupt pending bit.
  * @param  SPIx: where x can be
  *   - 1, 2, 3, or 4 in SPI mode
  * @param  SPI_I2S_INT: specifies the SPI interrupt pending bit to clear.
  *   This function clears only CRCERR interrupt pending bit.
  * @note
  *   - OVR (OverRun Error) interrupt pending bit is cleared by software
  *     sequence: a read operation to SPI_DT register (SPI_I2S_RxData())
  *     followed by a read operation to SPI_STS register (SPI_I2S_GetITStatus()).
  *   - UDR (UnderRun Error) interrupt pending bit is cleared by a read
  *     operation to SPI_STS register (SPI_I2S_GetITStatus()).
  *   - MODF (Mode Fault) interrupt pending bit is cleared by software sequence:
  *     a read/write operation to SPI_STS register (SPI_I2S_GetITStatus())
  *     followed by a write operation to SPI_CTRL1 register (SPI_Enable() to enable
  *     the SPI).
  * @retval None
  */
void SPI_I2S_ClearINTPendingBit(SPI_Type* SPIx, uint8_t SPI_I2S_INT)
{
  uint16_t itpos = 0;
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_CLEAR_INT(SPI_I2S_INT));

  /* Get the SPI INT index */
  itpos = 0x01 << (SPI_I2S_INT & 0x0F);

  /* Clear the selected SPI CRC Error (CRCERR) interrupt pending bit */
  SPIx->STS = (uint16_t)~itpos;
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


