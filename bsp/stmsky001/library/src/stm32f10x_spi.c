/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_spi.c
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file provides all the SPI firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_spi.h"
#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* SPI SPE mask */
#define CR1_SPE_Set          ((u16)0x0040)
#define CR1_SPE_Reset        ((u16)0xFFBF)

/* I2S I2SE mask */
#define I2SCFGR_I2SE_Set     ((u16)0x0400)
#define I2SCFGR_I2SE_Reset   ((u16)0xFBFF)

/* SPI CRCNext mask */
#define CR1_CRCNext_Set      ((u16)0x1000)

/* SPI CRCEN mask */
#define CR1_CRCEN_Set        ((u16)0x2000)
#define CR1_CRCEN_Reset      ((u16)0xDFFF)

/* SPI SSOE mask */
#define CR2_SSOE_Set         ((u16)0x0004)
#define CR2_SSOE_Reset       ((u16)0xFFFB)

/* SPI registers Masks */
#define CR1_CLEAR_Mask       ((u16)0x3040)
#define I2SCFGR_CLEAR_Mask   ((u16)0xF040)

/* SPI or I2S mode selection masks */
#define SPI_Mode_Select      ((u16)0xF7FF)
#define I2S_Mode_Select      ((u16)0x0800) 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : SPI_I2S_DeInit
* Description    : Deinitializes the SPIx peripheral registers to their default
*                  reset values (Affects also the I2Ss).
* Input          : - SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_I2S_DeInit(SPI_TypeDef* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  switch (*(u32*)&SPIx)
  {
    case SPI1_BASE:
      /* Enable SPI1 reset state */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
      /* Release SPI1 from reset state */
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);
      break;

    case SPI2_BASE:
      /* Enable SPI2 reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, ENABLE);
      /* Release SPI2 from reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2, DISABLE);
      break;

    case SPI3_BASE:
      /* Enable SPI3 reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, ENABLE);
      /* Release SPI3 from reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI3, DISABLE);
      break;

    default:
      break;
  }
}

/*******************************************************************************
* Function Name  : SPI_Init
* Description    : Initializes the SPIx peripheral according to the specified 
*                  parameters in the SPI_InitStruct.
* Input          : - SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
*                  - SPI_InitStruct: pointer to a SPI_InitTypeDef structure that
*                    contains the configuration information for the specified
*                    SPI peripheral.
* Output         : None
* Return         : None
******************************************************************************/
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
  u16 tmpreg = 0;
  
  /* check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));   
  
  /* Check the SPI parameters */
  assert_param(IS_SPI_DIRECTION_MODE(SPI_InitStruct->SPI_Direction));
  assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
  assert_param(IS_SPI_DATASIZE(SPI_InitStruct->SPI_DataSize));
  assert_param(IS_SPI_CPOL(SPI_InitStruct->SPI_CPOL));
  assert_param(IS_SPI_CPHA(SPI_InitStruct->SPI_CPHA));
  assert_param(IS_SPI_NSS(SPI_InitStruct->SPI_NSS));
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_InitStruct->SPI_BaudRatePrescaler));
  assert_param(IS_SPI_FIRST_BIT(SPI_InitStruct->SPI_FirstBit));
  assert_param(IS_SPI_CRC_POLYNOMIAL(SPI_InitStruct->SPI_CRCPolynomial));

/*---------------------------- SPIx CR1 Configuration ------------------------*/
  /* Get the SPIx CR1 value */
  tmpreg = SPIx->CR1;
  /* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
  tmpreg &= CR1_CLEAR_Mask;
  /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
     master/salve mode, CPOL and CPHA */
  /* Set BIDImode, BIDIOE and RxONLY bits according to SPI_Direction value */
  /* Set SSM, SSI and MSTR bits according to SPI_Mode and SPI_NSS values */
  /* Set LSBFirst bit according to SPI_FirstBit value */
  /* Set BR bits according to SPI_BaudRatePrescaler value */
  /* Set CPOL bit according to SPI_CPOL value */
  /* Set CPHA bit according to SPI_CPHA value */
  tmpreg |= (u16)((u32)SPI_InitStruct->SPI_Direction | SPI_InitStruct->SPI_Mode |
                  SPI_InitStruct->SPI_DataSize | SPI_InitStruct->SPI_CPOL |  
                  SPI_InitStruct->SPI_CPHA | SPI_InitStruct->SPI_NSS |  
                  SPI_InitStruct->SPI_BaudRatePrescaler | SPI_InitStruct->SPI_FirstBit);
  /* Write to SPIx CR1 */
  SPIx->CR1 = tmpreg;
  
  /* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
  SPIx->I2SCFGR &= SPI_Mode_Select;		

/*---------------------------- SPIx CRCPOLY Configuration --------------------*/
  /* Write to SPIx CRCPOLY */
  SPIx->CRCPR = SPI_InitStruct->SPI_CRCPolynomial;
}

/*******************************************************************************
* Function Name  : I2S_Init
* Description    : Initializes the SPIx peripheral according to the specified 
*                  parameters in the I2S_InitStruct.
* Input          : - SPIx: where x can be  2 or 3 to select the SPI peripheral
*                     (configured in I2S mode).
*                  - I2S_InitStruct: pointer to an I2S_InitTypeDef structure that
*                    contains the configuration information for the specified
*                    SPI peripheral configured in I2S mode.
* Output         : None
* Return         : None
******************************************************************************/
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct)
{
  u16 tmpreg = 0, i2sdiv = 2, i2sodd = 0, packetlength = 1;
  u32 tmp = 0;
  RCC_ClocksTypeDef RCC_Clocks;
   
  /* Check the I2S parameters */
  assert_param(IS_SPI_23_PERIPH(SPIx));
  assert_param(IS_I2S_MODE(I2S_InitStruct->I2S_Mode));
  assert_param(IS_I2S_STANDARD(I2S_InitStruct->I2S_Standard));
  assert_param(IS_I2S_DATA_FORMAT(I2S_InitStruct->I2S_DataFormat));
  assert_param(IS_I2S_MCLK_OUTPUT(I2S_InitStruct->I2S_MCLKOutput));
  assert_param(IS_I2S_AUDIO_FREQ(I2S_InitStruct->I2S_AudioFreq));
  assert_param(IS_I2S_CPOL(I2S_InitStruct->I2S_CPOL));  

/*----------------------- SPIx I2SCFGR & I2SPR Configuration -----------------*/

  /* Clear I2SMOD, I2SE, I2SCFG, PCMSYNC, I2SSTD, CKPOL, DATLEN and CHLEN bits */
  SPIx->I2SCFGR &= I2SCFGR_CLEAR_Mask; 
  SPIx->I2SPR = 0x0002;
  
  /* Get the I2SCFGR register value */
  tmpreg = SPIx->I2SCFGR;
  
  /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/
  if(I2S_InitStruct->I2S_AudioFreq == I2S_AudioFreq_Default)
  {
    i2sodd = (u16)0;
    i2sdiv = (u16)2;   
  }
  /* If the requested audio frequency is not the default, compute the prescaler */
  else
  {
    /* Check the frame length (For the Prescaler computing) */
    if(I2S_InitStruct->I2S_DataFormat == I2S_DataFormat_16b)
    {
      /* Packet length is 16 bits */
      packetlength = 1;
    }
    else
    {
      /* Packet length is 32 bits */
      packetlength = 2;
    }
    /* Get System Clock frequency */
    RCC_GetClocksFreq(&RCC_Clocks);
    
    /* Compute the Real divider depending on the MCLK output state with a flaoting point */
    if(I2S_InitStruct->I2S_MCLKOutput == I2S_MCLKOutput_Enable)
    {
      /* MCLK output is enabled */
      tmp = (u16)(((10 * RCC_Clocks.SYSCLK_Frequency) / (256 * I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    else
    {
      /* MCLK output is disabled */
      tmp = (u16)(((10 * RCC_Clocks.SYSCLK_Frequency) / (32 * packetlength * I2S_InitStruct->I2S_AudioFreq)) + 5);
    }
    
    /* Remove the flaoting point */
    tmp = tmp/10;  
      
    /* Check the parity of the divider */
    i2sodd = (u16)(tmp & (u16)0x0001);
   
    /* Compute the i2sdiv prescaler */
    i2sdiv = (u16)((tmp - i2sodd) / 2);
   
    /* Get the Mask for the Odd bit (SPI_I2SPR[8]) register */
    i2sodd = (u16) (i2sodd << 8);
  }
  
  /* Test if the divider is 1 or 0 */
  if ((i2sdiv < 2) || (i2sdiv > 0xFF))
  {
    /* Set the default values */
    i2sdiv = 2;
    i2sodd = 0;
  }

  /* Write to SPIx I2SPR register the computed value */
  SPIx->I2SPR = (u16)(i2sdiv | i2sodd | I2S_InitStruct->I2S_MCLKOutput);  
 
  /* Configure the I2S with the SPI_InitStruct values */
  tmpreg |= (u16)(I2S_Mode_Select | I2S_InitStruct->I2S_Mode | \
                  I2S_InitStruct->I2S_Standard | I2S_InitStruct->I2S_DataFormat | \
                  I2S_InitStruct->I2S_CPOL);
 
  /* Write to SPIx I2SCFGR */  
  SPIx->I2SCFGR = tmpreg;                                    
}

/*******************************************************************************
* Function Name  : SPI_StructInit
* Description    : Fills each SPI_InitStruct member with its default value.
* Input          : - SPI_InitStruct : pointer to a SPI_InitTypeDef structure
*                    which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
/*--------------- Reset SPI init structure parameters values -----------------*/
  /* Initialize the SPI_Direction member */
  SPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;

  /* initialize the SPI_Mode member */
  SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;

  /* initialize the SPI_DataSize member */
  SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;

  /* Initialize the SPI_CPOL member */
  SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;

  /* Initialize the SPI_CPHA member */
  SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;

  /* Initialize the SPI_NSS member */
  SPI_InitStruct->SPI_NSS = SPI_NSS_Hard;

  /* Initialize the SPI_BaudRatePrescaler member */
  SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;

  /* Initialize the SPI_FirstBit member */
  SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;

  /* Initialize the SPI_CRCPolynomial member */
  SPI_InitStruct->SPI_CRCPolynomial = 7;
}

/*******************************************************************************
* Function Name  : I2S_StructInit
* Description    : Fills each I2S_InitStruct member with its default value.
* Input          : - I2S_InitStruct : pointer to a I2S_InitTypeDef structure
*                    which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct)
{
/*--------------- Reset I2S init structure parameters values -----------------*/
  /* Initialize the I2S_Mode member */
  I2S_InitStruct->I2S_Mode = I2S_Mode_SlaveTx;
  
  /* Initialize the I2S_Standard member */
  I2S_InitStruct->I2S_Standard = I2S_Standard_Phillips;
  
  /* Initialize the I2S_DataFormat member */
  I2S_InitStruct->I2S_DataFormat = I2S_DataFormat_16b;
  
  /* Initialize the I2S_MCLKOutput member */
  I2S_InitStruct->I2S_MCLKOutput = I2S_MCLKOutput_Disable;
  
  /* Initialize the I2S_AudioFreq member */
  I2S_InitStruct->I2S_AudioFreq = I2S_AudioFreq_Default;
  
  /* Initialize the I2S_CPOL member */
  I2S_InitStruct->I2S_CPOL = I2S_CPOL_Low;
}

/*******************************************************************************
* Function Name  : SPI_Cmd
* Description    : Enables or disables the specified SPI peripheral.
* Input          : - SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
*                  - NewState: new state of the SPIx peripheral. 
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI peripheral */
    SPIx->CR1 |= CR1_SPE_Set;
  }
  else
  {
    /* Disable the selected SPI peripheral */
    SPIx->CR1 &= CR1_SPE_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2S_Cmd
* Description    : Enables or disables the specified SPI peripheral (in I2S mode).
* Input          : - SPIx: where x can be 2 or 3 to select the SPI peripheral.
*                  - NewState: new state of the SPIx peripheral. 
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_23_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI peripheral (in I2S mode) */
    SPIx->I2SCFGR |= I2SCFGR_I2SE_Set;
  }
  else
  {
    /* Disable the selected SPI peripheral (in I2S mode) */
    SPIx->I2SCFGR &= I2SCFGR_I2SE_Reset;
  }
}

/*******************************************************************************
* Function Name  : SPI_I2S_ITConfig
* Description    : Enables or disables the specified SPI/I2S interrupts.
* Input          : - SPIx: where x can be :
*                         - 1, 2 or 3 in SPI mode 
*                         - 2 or 3 in I2S mode
*                  - SPI_I2S_IT: specifies the SPI/I2S interrupt source to be 
*                    enabled or disabled. 
*                    This parameter can be one of the following values:
*                       - SPI_I2S_IT_TXE: Tx buffer empty interrupt mask
*                       - SPI_I2S_IT_RXNE: Rx buffer not empty interrupt mask
*                       - SPI_I2S_IT_ERR: Error interrupt mask
*                  - NewState: new state of the specified SPI/I2S interrupt.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_I2S_ITConfig(SPI_TypeDef* SPIx, u8 SPI_I2S_IT, FunctionalState NewState)
{
  u16 itpos = 0, itmask = 0 ;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_CONFIG_IT(SPI_I2S_IT));

  /* Get the SPI/I2S IT index */
  itpos = SPI_I2S_IT >> 4;
  /* Set the IT mask */
  itmask = (u16)((u16)1 << itpos);

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI/I2S interrupt */
    SPIx->CR2 |= itmask;
  }
  else
  {
    /* Disable the selected SPI/I2S interrupt */
    SPIx->CR2 &= (u16)~itmask;
  }
}

/*******************************************************************************
* Function Name  : SPI_I2S_DMACmd
* Description    : Enables or disables the SPIx/I2Sx DMA interface.
* Input          : - SPIx: where x can be :
*                         - 1, 2 or 3 in SPI mode 
*                         - 2 or 3 in I2S mode
*                  - SPI_I2S_DMAReq: specifies the SPI/I2S DMA transfer request 
*                    to be enabled or disabled. 
*                    This parameter can be any combination of the following values:
*                       - SPI_I2S_DMAReq_Tx: Tx buffer DMA transfer request
*                       - SPI_I2S_DMAReq_Rx: Rx buffer DMA transfer request
*                  - NewState: new state of the selected SPI/I2S DMA transfer 
*                    request.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_I2S_DMACmd(SPI_TypeDef* SPIx, u16 SPI_I2S_DMAReq, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_SPI_I2S_DMAREQ(SPI_I2S_DMAReq));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI/I2S DMA requests */
    SPIx->CR2 |= SPI_I2S_DMAReq;
  }
  else
  {
    /* Disable the selected SPI/I2S DMA requests */
    SPIx->CR2 &= (u16)~SPI_I2S_DMAReq;
  }
}

/*******************************************************************************
* Function Name  : SPI_I2S_SendData
* Description    : Transmits a Data through the SPIx/I2Sx peripheral.
* Input          : - SPIx: where x can be :
*                         - 1, 2 or 3 in SPI mode 
*                         - 2 or 3 in I2S mode
*                  - Data : Data to be transmitted..
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_I2S_SendData(SPI_TypeDef* SPIx, u16 Data)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* Write in the DR register the data to be sent */
  SPIx->DR = Data;
}

/*******************************************************************************
* Function Name  : SPI_I2S_ReceiveData
* Description    : Returns the most recent received data by the SPIx/I2Sx peripheral. 
* Input          : - SPIx: where x can be :
*                         - 1, 2 or 3 in SPI mode 
*                         - 2 or 3 in I2S mode
* Output         : None
* Return         : The value of the received data.
*******************************************************************************/
u16 SPI_I2S_ReceiveData(SPI_TypeDef* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* Return the data in the DR register */
  return SPIx->DR;
}

/*******************************************************************************
* Function Name  : SPI_NSSInternalSoftwareConfig
* Description    : Configures internally by software the NSS pin for the selected 
*                  SPI.
* Input          : - SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
*                  - SPI_NSSInternalSoft: specifies the SPI NSS internal state.
*                    This parameter can be one of the following values:
*                       - SPI_NSSInternalSoft_Set: Set NSS pin internally
*                       - SPI_NSSInternalSoft_Reset: Reset NSS pin internally
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, u16 SPI_NSSInternalSoft)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_NSS_INTERNAL(SPI_NSSInternalSoft));

  if (SPI_NSSInternalSoft != SPI_NSSInternalSoft_Reset)
  {
    /* Set NSS pin internally by software */
    SPIx->CR1 |= SPI_NSSInternalSoft_Set;
  }
  else
  {
    /* Reset NSS pin internally by software */
    SPIx->CR1 &= SPI_NSSInternalSoft_Reset;
  }
}

/*******************************************************************************
* Function Name  : SPI_SSOutputCmd
* Description    : Enables or disables the SS output for the selected SPI.
* Input          : - SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
*                  - NewState: new state of the SPIx SS output. 
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI SS output */
    SPIx->CR2 |= CR2_SSOE_Set;
  }
  else
  {
    /* Disable the selected SPI SS output */
    SPIx->CR2 &= CR2_SSOE_Reset;
  }
}

/*******************************************************************************
* Function Name  : SPI_DataSizeConfig
* Description    : Configures the data size for the selected SPI.
* Input          : - SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
*                  - SPI_DataSize: specifies the SPI data size.
*                    This parameter can be one of the following values:
*                       - SPI_DataSize_16b: Set data frame format to 16bit
*                       - SPI_DataSize_8b: Set data frame format to 8bit
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, u16 SPI_DataSize)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DATASIZE(SPI_DataSize));

  /* Clear DFF bit */
  SPIx->CR1 &= (u16)~SPI_DataSize_16b;
  /* Set new DFF bit value */
  SPIx->CR1 |= SPI_DataSize;
}

/*******************************************************************************
* Function Name  : SPI_TransmitCRC
* Description    : Transmit the SPIx CRC value.
* Input          : - SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_TransmitCRC(SPI_TypeDef* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* Enable the selected SPI CRC transmission */
  SPIx->CR1 |= CR1_CRCNext_Set;
}

/*******************************************************************************
* Function Name  : SPI_CalculateCRC
* Description    : Enables or disables the CRC value calculation of the
*                  transfered bytes.
* Input          : - SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
*                  - NewState: new state of the SPIx CRC value calculation.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected SPI CRC calculation */
    SPIx->CR1 |= CR1_CRCEN_Set;
  }
  else
  {
    /* Disable the selected SPI CRC calculation */
    SPIx->CR1 &= CR1_CRCEN_Reset;
  }
}

/*******************************************************************************
* Function Name  : SPI_GetCRC
* Description    : Returns the transmit or the receive CRC register value for
*                  the specified SPI.
* Input          : - SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
*                  - SPI_CRC: specifies the CRC register to be read.
*                    This parameter can be one of the following values:
*                       - SPI_CRC_Tx: Selects Tx CRC register
*                       - SPI_CRC_Rx: Selects Rx CRC register
* Output         : None
* Return         : The selected CRC register value..
*******************************************************************************/
u16 SPI_GetCRC(SPI_TypeDef* SPIx, u8 SPI_CRC)
{
  u16 crcreg = 0;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_CRC(SPI_CRC));

  if (SPI_CRC != SPI_CRC_Rx)
  {
    /* Get the Tx CRC register */
    crcreg = SPIx->TXCRCR;
  }
  else
  {
    /* Get the Rx CRC register */
    crcreg = SPIx->RXCRCR;
  }

  /* Return the selected CRC register */
  return crcreg;
}

/*******************************************************************************
* Function Name  : SPI_GetCRCPolynomial
* Description    : Returns the CRC Polynomial register value for the specified SPI.
* Input          : - SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
* Output         : None
* Return         : The CRC Polynomial register value.
*******************************************************************************/
u16 SPI_GetCRCPolynomial(SPI_TypeDef* SPIx)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  
  /* Return the CRC polynomial register */
  return SPIx->CRCPR;
}

/*******************************************************************************
* Function Name  : SPI_BiDirectionalLineConfig
* Description    : Selects the data transfer direction in bi-directional mode
*                  for the specified SPI.
* Input          : - SPIx: where x can be 1, 2 or 3 to select the SPI peripheral.
*                  - SPI_Direction: specifies the data transfer direction in
*                    bi-directional mode. 
*                    This parameter can be one of the following values:
*                       - SPI_Direction_Tx: Selects Tx transmission direction
*                       - SPI_Direction_Rx: Selects Rx receive direction
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, u16 SPI_Direction)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_DIRECTION(SPI_Direction));

  if (SPI_Direction == SPI_Direction_Tx)
  {
    /* Set the Tx only mode */
    SPIx->CR1 |= SPI_Direction_Tx;
  }
  else
  {
    /* Set the Rx only mode */
    SPIx->CR1 &= SPI_Direction_Rx;
  }
}

/*******************************************************************************
* Function Name  : SPI_I2S_GetFlagStatus
* Description    : Checks whether the specified SPI/I2S flag is set or not.
* Input          : - SPIx: where x can be :
*                         - 1, 2 or 3 in SPI mode 
*                         - 2 or 3 in I2S mode
*                  - SPI_I2S_FLAG: specifies the SPI/I2S flag to check. 
*                    This parameter can be one of the following values:
*                       - SPI_I2S_FLAG_TXE: Transmit buffer empty flag.
*                       - SPI_I2S_FLAG_RXNE: Receive buffer not empty flag.
*                       - SPI_I2S_FLAG_BSY: Busy flag.
*                       - SPI_I2S_FLAG_OVR: Overrun flag.
*                       - SPI_FLAG_MODF: Mode Fault flag.
*                       - SPI_FLAG_CRCERR: CRC Error flag.
*                       - I2S_FLAG_UDR: Underrun Error flag.
*                       - I2S_FLAG_CHSIDE: Channel Side flag.
* Output         : None
* Return         : The new state of SPI_I2S_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, u16 SPI_I2S_FLAG)
{
  FlagStatus bitstatus = RESET;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_GET_FLAG(SPI_I2S_FLAG));

  /* Check the status of the specified SPI/I2S flag */
  if ((SPIx->SR & SPI_I2S_FLAG) != (u16)RESET)
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

/*******************************************************************************
* Function Name  : SPI_I2S_ClearFlag
* Description    : Clears the SPIx CRC Error (CRCERR) flag.
* Input          : - SPIx: where x can be :
*                         - 1, 2 or 3 in SPI mode 
*                  - SPI_I2S_FLAG: specifies the SPI flag to clear. 
*                    This function clears only CRCERR flag.                                           
*                  Notes:
*                       - OVR (OverRun error) flag is cleared by software 
*                         sequence: a read operation to SPI_DR register 
*                         (SPI_I2S_ReceiveData()) followed by a read operation 
*                         to SPI_SR register (SPI_I2S_GetFlagStatus()).                           
*                       - UDR (UnderRun error) flag is cleared by a read 
*                         operation to SPI_SR register (SPI_I2S_GetFlagStatus()).                             
*                       - MODF (Mode Fault) flag is cleared by software sequence: 
*                         a read/write operation to SPI_SR register 
*                         (SPI_I2S_GetFlagStatus()) followed by a write 
*                         operation to SPI_CR1 register (SPI_Cmd() to enable 
*                         the SPI).   
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, u16 SPI_I2S_FLAG)
{
  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_CLEAR_FLAG(SPI_I2S_FLAG));
    
    /* Clear the selected SPI CRC Error (CRCERR) flag */
    SPIx->SR = (u16)~SPI_I2S_FLAG;
}

/*******************************************************************************
* Function Name  : SPI_I2S_GetITStatus
* Description    : Checks whether the specified SPI/I2S interrupt has occurred or not.
* Input          : - SPIx: where x can be :
*                         - 1, 2 or 3 in SPI mode 
*                         - 2 or 3 in I2S mode
*                  - SPI_I2S_IT: specifies the SPI/I2S interrupt source to check. 
*                    This parameter can be one of the following values:
*                       - SPI_I2S_IT_TXE: Transmit buffer empty interrupt.
*                       - SPI_I2S_IT_RXNE: Receive buffer not empty interrupt.
*                       - SPI_I2S_IT_OVR: Overrun interrupt.
*                       - SPI_IT_MODF: Mode Fault interrupt.
*                       - SPI_IT_CRCERR: CRC Error interrupt.
*                       - I2S_IT_UDR: Underrun Error interrupt.
* Output         : None
* Return         : The new state of SPI_I2S_IT (SET or RESET).
*******************************************************************************/
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef* SPIx, u8 SPI_I2S_IT)
{
  ITStatus bitstatus = RESET;
  u16 itpos = 0, itmask = 0, enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_GET_IT(SPI_I2S_IT));

  /* Get the SPI/I2S IT index */
  itpos = (u16)((u16)0x01 << (SPI_I2S_IT & (u8)0x0F));

  /* Get the SPI/I2S IT mask */
  itmask = SPI_I2S_IT >> 4;
  /* Set the IT mask */
  itmask = (u16)((u16)0x01 << itmask);
  /* Get the SPI_I2S_IT enable bit status */
  enablestatus = (SPIx->CR2 & itmask) ;

  /* Check the status of the specified SPI/I2S interrupt */
  if (((SPIx->SR & itpos) != (u16)RESET) && enablestatus)
  {
    /* SPI_I2S_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* SPI_I2S_IT is reset */
    bitstatus = RESET;
  }
  /* Return the SPI_I2S_IT status */
  return bitstatus;
}

/*******************************************************************************
* Function Name  : SPI_I2S_ClearITPendingBit
* Description    : Clears the SPIx CRC Error (CRCERR) interrupt pending bit.
* Input          : - SPIx: where x can be :
*                         - 1, 2 or 3 in SPI mode 
*                  - SPI_I2S_IT: specifies the SPI interrupt pending bit to clear.
*                    This function clears only CRCERR intetrrupt pending bit.   
*                  Notes:
*                       - OVR (OverRun Error) interrupt pending bit is cleared 
*                         by software sequence: a read operation to SPI_DR 
*                         register (SPI_I2S_ReceiveData()) followed by a read 
*                         operation to SPI_SR register (SPI_I2S_GetITStatus()).
*                       - UDR (UnderRun Error) interrupt pending bit is cleared 
*                         by a read operation to SPI_SR register 
*                         (SPI_I2S_GetITStatus()).                           
*                       - MODF (Mode Fault) interrupt pending bit is cleared by 
*                         software sequence: a read/write operation to SPI_SR 
*                         register (SPI_I2S_GetITStatus()) followed by a write 
*                         operation to SPI_CR1 register (SPI_Cmd() to enable the 
*                         SPI).   
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_I2S_ClearITPendingBit(SPI_TypeDef* SPIx, u8 SPI_I2S_IT)
{
  u16 itpos = 0;

  /* Check the parameters */
  assert_param(IS_SPI_ALL_PERIPH(SPIx));
  assert_param(IS_SPI_I2S_CLEAR_IT(SPI_I2S_IT));

  /* Get the SPI IT index */
  itpos = (u16)((u16)0x01 << (SPI_I2S_IT & (u8)0x0F));
  /* Clear the selected SPI CRC Error (CRCERR) interrupt pending bit */
  SPIx->SR = (u16)~itpos;
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
