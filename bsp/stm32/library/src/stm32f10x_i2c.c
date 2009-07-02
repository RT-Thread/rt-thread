/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : stm32f10x_i2c.c
* Author             : MCD Application Team
* Version            : V2.0.3Patch1
* Date               : 04/06/2009
* Description        : This file provides all the I2C firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
	 
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* I2C SPE mask */
#define CR1_PE_Set              ((u16)0x0001)
#define CR1_PE_Reset            ((u16)0xFFFE)

/* I2C START mask */
#define CR1_START_Set           ((u16)0x0100)
#define CR1_START_Reset         ((u16)0xFEFF)

/* I2C STOP mask */
#define CR1_STOP_Set            ((u16)0x0200)
#define CR1_STOP_Reset          ((u16)0xFDFF)

/* I2C ACK mask */
#define CR1_ACK_Set             ((u16)0x0400)
#define CR1_ACK_Reset           ((u16)0xFBFF)

/* I2C ENGC mask */
#define CR1_ENGC_Set            ((u16)0x0040)
#define CR1_ENGC_Reset          ((u16)0xFFBF)

/* I2C SWRST mask */
#define CR1_SWRST_Set           ((u16)0x8000)
#define CR1_SWRST_Reset         ((u16)0x7FFF)

/* I2C PEC mask */
#define CR1_PEC_Set             ((u16)0x1000)
#define CR1_PEC_Reset           ((u16)0xEFFF)

/* I2C ENPEC mask */
#define CR1_ENPEC_Set           ((u16)0x0020)
#define CR1_ENPEC_Reset         ((u16)0xFFDF)

/* I2C ENARP mask */
#define CR1_ENARP_Set           ((u16)0x0010)
#define CR1_ENARP_Reset         ((u16)0xFFEF)

/* I2C NOSTRETCH mask */
#define CR1_NOSTRETCH_Set       ((u16)0x0080)
#define CR1_NOSTRETCH_Reset     ((u16)0xFF7F)

/* I2C registers Masks */
#define CR1_CLEAR_Mask          ((u16)0xFBF5)

/* I2C DMAEN mask */
#define CR2_DMAEN_Set           ((u16)0x0800)
#define CR2_DMAEN_Reset         ((u16)0xF7FF)

/* I2C LAST mask */
#define CR2_LAST_Set            ((u16)0x1000)
#define CR2_LAST_Reset          ((u16)0xEFFF)

/* I2C FREQ mask */
#define CR2_FREQ_Reset          ((u16)0xFFC0)

/* I2C ADD0 mask */
#define OAR1_ADD0_Set           ((u16)0x0001)
#define OAR1_ADD0_Reset         ((u16)0xFFFE)

/* I2C ENDUAL mask */
#define OAR2_ENDUAL_Set         ((u16)0x0001)
#define OAR2_ENDUAL_Reset       ((u16)0xFFFE)

/* I2C ADD2 mask */
#define OAR2_ADD2_Reset         ((u16)0xFF01)

/* I2C F/S mask */
#define CCR_FS_Set              ((u16)0x8000)

/* I2C CCR mask */
#define CCR_CCR_Set             ((u16)0x0FFF)

/* I2C FLAG mask */
#define FLAG_Mask               ((u32)0x00FFFFFF)

/* I2C Interrupt Enable mask */
#define ITEN_Mask               ((u32)0x07000000)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : I2C_DeInit
* Description    : Deinitializes the I2Cx peripheral registers to their default
*                  reset values.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_DeInit(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  switch (*(u32*)&I2Cx)
  {
    case I2C1_BASE:
      /* Enable I2C1 reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
      /* Release I2C1 from reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
      break;

    case I2C2_BASE:
      /* Enable I2C2 reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
      /* Release I2C2 from reset state */
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
      break;

    default:
      break;
  }
}

/*******************************************************************************
* Function Name  : I2C_Init
* Description    : Initializes the I2Cx peripheral according to the specified 
*                  parameters in the I2C_InitStruct.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - I2C_InitStruct: pointer to a I2C_InitTypeDef structure that
*                    contains the configuration information for the specified
*                    I2C peripheral.
* Output         : None
* Return         : None
******************************************************************************/
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
  u16 tmpreg = 0, freqrange = 0;
  u16 result = 0x04;
  u32 pclk1 = 8000000;
  RCC_ClocksTypeDef  rcc_clocks;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_MODE(I2C_InitStruct->I2C_Mode));
  assert_param(IS_I2C_DUTY_CYCLE(I2C_InitStruct->I2C_DutyCycle));
  assert_param(IS_I2C_OWN_ADDRESS1(I2C_InitStruct->I2C_OwnAddress1));
  assert_param(IS_I2C_ACK_STATE(I2C_InitStruct->I2C_Ack));
  assert_param(IS_I2C_ACKNOWLEDGE_ADDRESS(I2C_InitStruct->I2C_AcknowledgedAddress));
  assert_param(IS_I2C_CLOCK_SPEED(I2C_InitStruct->I2C_ClockSpeed));

/*---------------------------- I2Cx CR2 Configuration ------------------------*/
  /* Get the I2Cx CR2 value */
  tmpreg = I2Cx->CR2;
  /* Clear frequency FREQ[5:0] bits */
  tmpreg &= CR2_FREQ_Reset;
  /* Get pclk1 frequency value */
  RCC_GetClocksFreq(&rcc_clocks);
  pclk1 = rcc_clocks.PCLK1_Frequency;
  /* Set frequency bits depending on pclk1 value */
  freqrange = (u16)(pclk1 / 1000000);
  tmpreg |= freqrange;
  /* Write to I2Cx CR2 */
  I2Cx->CR2 = tmpreg;

/*---------------------------- I2Cx CCR Configuration ------------------------*/
  /* Disable the selected I2C peripheral to configure TRISE */
  I2Cx->CR1 &= CR1_PE_Reset;

  /* Reset tmpreg value */
  /* Clear F/S, DUTY and CCR[11:0] bits */
  tmpreg = 0;

  /* Configure speed in standard mode */
  if (I2C_InitStruct->I2C_ClockSpeed <= 100000)
  {
    /* Standard mode speed calculate */
    result = (u16)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed << 1));
    /* Test if CCR value is under 0x4*/
    if (result < 0x04)
    {
      /* Set minimum allowed value */
      result = 0x04;  
    }
    /* Set speed value for standard mode */
    tmpreg |= result;	  
    /* Set Maximum Rise Time for standard mode */
    I2Cx->TRISE = freqrange + 1; 
  }
  /* Configure speed in fast mode */
  else /*(I2C_InitStruct->I2C_ClockSpeed <= 400000)*/
  {
    if (I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_2)
    {
      /* Fast mode speed calculate: Tlow/Thigh = 2 */
      result = (u16)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 3));
    }
    else /*I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_16_9*/
    {
      /* Fast mode speed calculate: Tlow/Thigh = 16/9 */
      result = (u16)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 25));
      /* Set DUTY bit */
      result |= I2C_DutyCycle_16_9;
    }
    /* Test if CCR value is under 0x1*/
    if ((result & CCR_CCR_Set) == 0)
    {
      /* Set minimum allowed value */
      result |= (u16)0x0001;  
    }
    /* Set speed value and set F/S bit for fast mode */
    tmpreg |= result | CCR_FS_Set;
    /* Set Maximum Rise Time for fast mode */
    I2Cx->TRISE = (u16)(((freqrange * 300) / 1000) + 1);  
  }
  /* Write to I2Cx CCR */
  I2Cx->CCR = tmpreg;

  /* Enable the selected I2C peripheral */
  I2Cx->CR1 |= CR1_PE_Set;

/*---------------------------- I2Cx CR1 Configuration ------------------------*/
  /* Get the I2Cx CR1 value */
  tmpreg = I2Cx->CR1;
  /* Clear ACK, SMBTYPE and  SMBUS bits */
  tmpreg &= CR1_CLEAR_Mask;
  /* Configure I2Cx: mode and acknowledgement */
  /* Set SMBTYPE and SMBUS bits according to I2C_Mode value */
  /* Set ACK bit according to I2C_Ack value */
  tmpreg |= (u16)((u32)I2C_InitStruct->I2C_Mode | I2C_InitStruct->I2C_Ack);
  /* Write to I2Cx CR1 */
  I2Cx->CR1 = tmpreg;

/*---------------------------- I2Cx OAR1 Configuration -----------------------*/
  /* Set I2Cx Own Address1 and acknowledged address */
  I2Cx->OAR1 = (I2C_InitStruct->I2C_AcknowledgedAddress | I2C_InitStruct->I2C_OwnAddress1);
}

/*******************************************************************************
* Function Name  : I2C_StructInit
* Description    : Fills each I2C_InitStruct member with its default value.
* Input          : - I2C_InitStruct: pointer to an I2C_InitTypeDef structure
*                    which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
/*---------------- Reset I2C init structure parameters values ----------------*/
  /* Initialize the I2C_Mode member */
  I2C_InitStruct->I2C_Mode = I2C_Mode_I2C;

  /* Initialize the I2C_DutyCycle member */
  I2C_InitStruct->I2C_DutyCycle = I2C_DutyCycle_2;

  /* Initialize the I2C_OwnAddress1 member */
  I2C_InitStruct->I2C_OwnAddress1 = 0;

  /* Initialize the I2C_Ack member */
  I2C_InitStruct->I2C_Ack = I2C_Ack_Disable;

  /* Initialize the I2C_AcknowledgedAddress member */
  I2C_InitStruct->I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

  /* initialize the I2C_ClockSpeed member */
  I2C_InitStruct->I2C_ClockSpeed = 5000;
}

/*******************************************************************************
* Function Name  : I2C_Cmd
* Description    : Enables or disables the specified I2C peripheral.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - NewState: new state of the I2Cx peripheral. This parameter
*                    can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C peripheral */
    I2Cx->CR1 |= CR1_PE_Set;
  }
  else
  {
    /* Disable the selected I2C peripheral */
    I2Cx->CR1 &= CR1_PE_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_DMACmd
* Description    : Enables or disables the specified I2C DMA requests.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - NewState: new state of the I2C DMA transfer.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C DMA requests */
    I2Cx->CR2 |= CR2_DMAEN_Set;
  }
  else
  {
    /* Disable the selected I2C DMA requests */
    I2Cx->CR2 &= CR2_DMAEN_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_DMALastTransferCmd
* Description    : Specifies that the next DMA transfer is the last one.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - NewState: new state of the I2C DMA last transfer.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Next DMA transfer is the last transfer */
    I2Cx->CR2 |= CR2_LAST_Set;
  }
  else
  {
    /* Next DMA transfer is not the last transfer */
    I2Cx->CR2 &= CR2_LAST_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_GenerateSTART
* Description    : Generates I2Cx communication START condition.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - NewState: new state of the I2C START condition generation.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None.
*******************************************************************************/
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Generate a START condition */
    I2Cx->CR1 |= CR1_START_Set;
  }
  else
  {
    /* Disable the START condition generation */
    I2Cx->CR1 &= CR1_START_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_GenerateSTOP
* Description    : Generates I2Cx communication STOP condition.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - NewState: new state of the I2C STOP condition generation.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None.
*******************************************************************************/
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Generate a STOP condition */
    I2Cx->CR1 |= CR1_STOP_Set;
  }
  else
  {
    /* Disable the STOP condition generation */
    I2Cx->CR1 &= CR1_STOP_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_AcknowledgeConfig
* Description    : Enables or disables the specified I2C acknowledge feature.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - NewState: new state of the I2C Acknowledgement.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None.
*******************************************************************************/
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the acknowledgement */
    I2Cx->CR1 |= CR1_ACK_Set;
  }
  else
  {
    /* Disable the acknowledgement */
    I2Cx->CR1 &= CR1_ACK_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_OwnAddress2Config
* Description    : Configures the specified I2C own address2.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - Address: specifies the 7bit I2C own address2.
* Output         : None
* Return         : None.
*******************************************************************************/
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, u8 Address)
{
  u16 tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Get the old register value */
  tmpreg = I2Cx->OAR2;
  /* Reset I2Cx Own address2 bit [7:1] */
  tmpreg &= OAR2_ADD2_Reset;
  /* Set I2Cx Own address2 */
  tmpreg |= (u16)(Address & (u16)0x00FE);
  /* Store the new register value */
  I2Cx->OAR2 = tmpreg;
}

/*******************************************************************************
* Function Name  : I2C_DualAddressCmd
* Description    : Enables or disables the specified I2C dual addressing mode.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - NewState: new state of the I2C dual addressing mode.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable dual addressing mode */
    I2Cx->OAR2 |= OAR2_ENDUAL_Set;
  }
  else
  {
    /* Disable dual addressing mode */
    I2Cx->OAR2 &= OAR2_ENDUAL_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_GeneralCallCmd
* Description    : Enables or disables the specified I2C general call feature.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - NewState: new state of the I2C General call.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable generall call */
    I2Cx->CR1 |= CR1_ENGC_Set;
  }
  else
  {
    /* Disable generall call */
    I2Cx->CR1 &= CR1_ENGC_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_ITConfig
* Description    : Enables or disables the specified I2C interrupts.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - I2C_IT: specifies the I2C interrupts sources to be enabled
*                    or disabled. 
*                    This parameter can be any combination of the following values:
*                       - I2C_IT_BUF: Buffer interrupt mask
*                       - I2C_IT_EVT: Event interrupt mask
*                       - I2C_IT_ERR: Error interrupt mask
*                  - NewState: new state of the specified I2C interrupts.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_ITConfig(I2C_TypeDef* I2Cx, u16 I2C_IT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_I2C_CONFIG_IT(I2C_IT));
  
  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    I2Cx->CR2 |= I2C_IT;
  }
  else
  {
    /* Disable the selected I2C interrupts */
    I2Cx->CR2 &= (u16)~I2C_IT;
  }
}

/*******************************************************************************
* Function Name  : I2C_SendData
* Description    : Sends a data byte through the I2Cx peripheral.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - Data: Byte to be transmitted..
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_SendData(I2C_TypeDef* I2Cx, u8 Data)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Write in the DR register the data to be sent */
  I2Cx->DR = Data;
}

/*******************************************************************************
* Function Name  : I2C_ReceiveData
* Description    : Returns the most recent received data by the I2Cx peripheral.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* Output         : None
* Return         : The value of the received data.
*******************************************************************************/
u8 I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Return the data in the DR register */
  return (u8)I2Cx->DR;
}

/*******************************************************************************
* Function Name  : I2C_Send7bitAddress
* Description    : Transmits the address byte to select the slave device.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - Address: specifies the slave address which will be transmitted
*                  - I2C_Direction: specifies whether the I2C device will be a
*                    Transmitter or a Receiver. 
*                    This parameter can be one of the following values
*                       - I2C_Direction_Transmitter: Transmitter mode
*                       - I2C_Direction_Receiver: Receiver mode
* Output         : None
* Return         : None.
*******************************************************************************/
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, u8 Address, u8 I2C_Direction)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_DIRECTION(I2C_Direction));

  /* Test on the direction to set/reset the read/write bit */
  if (I2C_Direction != I2C_Direction_Transmitter)
  {
    /* Set the address bit0 for read */
    Address |= OAR1_ADD0_Set;
  }
  else
  {
    /* Reset the address bit0 for write */
    Address &= OAR1_ADD0_Reset;
  }
  /* Send the address */
  I2Cx->DR = Address;
}

/*******************************************************************************
* Function Name  : I2C_ReadRegister
* Description    : Reads the specified I2C register and returns its value.
* Input1         : - I2C_Register: specifies the register to read.
*                    This parameter can be one of the following values:
*                       - I2C_Register_CR1:  CR1 register.
*                       - I2C_Register_CR2:   CR2 register.
*                       - I2C_Register_OAR1:  OAR1 register.
*                       - I2C_Register_OAR2:  OAR2 register.
*                       - I2C_Register_DR:    DR register.
*                       - I2C_Register_SR1:   SR1 register.
*                       - I2C_Register_SR2:   SR2 register.
*                       - I2C_Register_CCR:   CCR register.
*                       - I2C_Register_TRISE: TRISE register.
* Output         : None
* Return         : The value of the read register.
*******************************************************************************/
u16 I2C_ReadRegister(I2C_TypeDef* I2Cx, u8 I2C_Register)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_REGISTER(I2C_Register));

  /* Return the selected register value */
  return (*(vu16 *)(*((vu32 *)&I2Cx) + I2C_Register));
}

/*******************************************************************************
* Function Name  : I2C_SoftwareResetCmd
* Description    : Enables or disables the specified I2C software reset.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - NewState: new state of the I2C software reset.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Peripheral under reset */
    I2Cx->CR1 |= CR1_SWRST_Set;
  }
  else
  {
    /* Peripheral not under reset */
    I2Cx->CR1 &= CR1_SWRST_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_SMBusAlertConfig
* Description    : Drives the SMBusAlert pin high or low for the specified I2C.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - I2C_SMBusAlert: specifies SMBAlert pin level. 
*                    This parameter can be one of the following values:
*                       - I2C_SMBusAlert_Low: SMBAlert pin driven low
*                       - I2C_SMBusAlert_High: SMBAlert pin driven high
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, u16 I2C_SMBusAlert)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_SMBUS_ALERT(I2C_SMBusAlert));

  if (I2C_SMBusAlert == I2C_SMBusAlert_Low)
  {
    /* Drive the SMBusAlert pin Low */
    I2Cx->CR1 |= I2C_SMBusAlert_Low;
  }
  else
  {
    /* Drive the SMBusAlert pin High  */
    I2Cx->CR1 &= I2C_SMBusAlert_High;
  }
}

/*******************************************************************************
* Function Name  : I2C_TransmitPEC
* Description    : Enables or disables the specified I2C PEC transfer.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - NewState: new state of the I2C PEC transmission.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C PEC transmission */
    I2Cx->CR1 |= CR1_PEC_Set;
  }
  else
  {
    /* Disable the selected I2C PEC transmission */
    I2Cx->CR1 &= CR1_PEC_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_PECPositionConfig
* Description    : Selects the specified I2C PEC position.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - I2C_PECPosition: specifies the PEC position. 
*                    This parameter can be one of the following values:
*                       - I2C_PECPosition_Next: indicates that the next
*                         byte is PEC
*                       - I2C_PECPosition_Current: indicates that current
*                         byte is PEC
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, u16 I2C_PECPosition)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_PEC_POSITION(I2C_PECPosition));

  if (I2C_PECPosition == I2C_PECPosition_Next)
  {
    /* Next byte in shift register is PEC */
    I2Cx->CR1 |= I2C_PECPosition_Next;
  }
  else
  {
    /* Current byte in shift register is PEC */
    I2Cx->CR1 &= I2C_PECPosition_Current;
  }
}

/*******************************************************************************
* Function Name  : I2C_CalculatePEC
* Description    : Enables or disables the PEC value calculation of the
*                  transfered bytes.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - NewState: new state of the I2Cx PEC value calculation.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C PEC calculation */
    I2Cx->CR1 |= CR1_ENPEC_Set;
  }
  else
  {
    /* Disable the selected I2C PEC calculation */
    I2Cx->CR1 &= CR1_ENPEC_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_GetPEC
* Description    : Returns the PEC value for the specified I2C.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* Output         : None
* Return         : The PEC value.
*******************************************************************************/
u8 I2C_GetPEC(I2C_TypeDef* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Return the selected I2C PEC value */
  return ((I2Cx->SR2) >> 8);
}

/*******************************************************************************
* Function Name  : I2C_ARPCmd
* Description    : Enables or disables the specified I2C ARP.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - NewState: new state of the I2Cx ARP. 
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C ARP */
    I2Cx->CR1 |= CR1_ENARP_Set;
  }
  else
  {
    /* Disable the selected I2C ARP */
    I2Cx->CR1 &= CR1_ENARP_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_StretchClockCmd
* Description    : Enables or disables the specified I2C Clock stretching.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - NewState: new state of the I2Cx Clock stretching.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState == DISABLE)
  {
    /* Enable the selected I2C Clock stretching */
    I2Cx->CR1 |= CR1_NOSTRETCH_Set;
  }
  else
  {
    /* Disable the selected I2C Clock stretching */
    I2Cx->CR1 &= CR1_NOSTRETCH_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_FastModeDutyCycleConfig
* Description    : Selects the specified I2C fast mode duty cycle.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - I2C_DutyCycle: specifies the fast mode duty cycle.
*                    This parameter can be one of the following values:
*                       - I2C_DutyCycle_2: I2C fast mode Tlow/Thigh = 2
*                       - I2C_DutyCycle_16_9: I2C fast mode Tlow/Thigh = 16/9
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, u16 I2C_DutyCycle)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_DUTY_CYCLE(I2C_DutyCycle));

  if (I2C_DutyCycle != I2C_DutyCycle_16_9)
  {
    /* I2C fast mode Tlow/Thigh=2 */
    I2Cx->CCR &= I2C_DutyCycle_2;
  }
  else
  {
    /* I2C fast mode Tlow/Thigh=16/9 */
    I2Cx->CCR |= I2C_DutyCycle_16_9;
  }
}

/*******************************************************************************
* Function Name  : I2C_GetLastEvent
* Description    : Returns the last I2Cx Event.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* Output         : None
* Return         : The last event
*******************************************************************************/
u32 I2C_GetLastEvent(I2C_TypeDef* I2Cx)
{
  u32 lastevent = 0;
  u32 flag1 = 0, flag2 = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Read the I2Cx status register */
  flag1 = I2Cx->SR1;
  flag2 = I2Cx->SR2;
  flag2 = flag2 << 16;

  /* Get the last event value from I2C status register */
  lastevent = (flag1 | flag2) & FLAG_Mask;

  /* Return status */
  return lastevent;
}

/*******************************************************************************
* Function Name  : I2C_CheckEvent
* Description    : Checks whether the last I2Cx Event is equal to the one passed
*                  as parameter.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - I2C_EVENT: specifies the event to be checked. 
*                    This parameter can be one of the following values:
*                       - I2C_EVENT_SLAVE_ADDRESS_MATCHED   : EV1
*                       - I2C_EVENT_SLAVE_BYTE_RECEIVED     : EV2
*                       - I2C_EVENT_SLAVE_BYTE_TRANSMITTED  : EV3
*                       - I2C_EVENT_SLAVE_ACK_FAILURE       : EV3-2
*                       - I2C_EVENT_MASTER_MODE_SELECT      : EV5
*                       - I2C_EVENT_MASTER_MODE_SELECTED    : EV6
*                       - I2C_EVENT_MASTER_BYTE_RECEIVED    : EV7
*                       - I2C_EVENT_MASTER_BYTE_TRANSMITTED : EV8
*                       - I2C_EVENT_MASTER_MODE_ADDRESS10   : EV9
*                       - I2C_EVENT_SLAVE_STOP_DETECTED     : EV4
* Output         : None
* Return         : An ErrorStatus enumuration value:
*                       - SUCCESS: Last event is equal to the I2C_EVENT
*                       - ERROR: Last event is different from the I2C_EVENT
*******************************************************************************/
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, u32 I2C_EVENT)
{
  u32 lastevent = 0;
  u32 flag1 = 0, flag2 = 0;
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_EVENT(I2C_EVENT));

  /* Read the I2Cx status register */
  flag1 = I2Cx->SR1;
  flag2 = I2Cx->SR2;
  flag2 = flag2 << 16;

  /* Get the last event value from I2C status register */
  lastevent = (flag1 | flag2) & FLAG_Mask;

  /* Check whether the last event is equal to I2C_EVENT */
  if (lastevent == I2C_EVENT )
  {
    /* SUCCESS: last event is equal to I2C_EVENT */
    status = SUCCESS;
  }
  else
  {
    /* ERROR: last event is different from I2C_EVENT */
    status = ERROR;
  }

  /* Return status */
  return status;
}

/*******************************************************************************
* Function Name  : I2C_GetFlagStatus
* Description    : Checks whether the specified I2C flag is set or not.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - I2C_FLAG: specifies the flag to check. 
*                    This parameter can be one of the following values:
*                       - I2C_FLAG_DUALF: Dual flag (Slave mode)
*                       - I2C_FLAG_SMBHOST: SMBus host header (Slave mode)
*                       - I2C_FLAG_SMBDEFAULT: SMBus default header (Slave mode)
*                       - I2C_FLAG_GENCALL: General call header flag (Slave mode)
*                       - I2C_FLAG_TRA: Transmitter/Receiver flag
*                       - I2C_FLAG_BUSY: Bus busy flag
*                       - I2C_FLAG_MSL: Master/Slave flag
*                       - I2C_FLAG_SMBALERT: SMBus Alert flag
*                       - I2C_FLAG_TIMEOUT: Timeout or Tlow error flag
*                       - I2C_FLAG_PECERR: PEC error in reception flag
*                       - I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode)
*                       - I2C_FLAG_AF: Acknowledge failure flag
*                       - I2C_FLAG_ARLO: Arbitration lost flag (Master mode)
*                       - I2C_FLAG_BERR: Bus error flag
*                       - I2C_FLAG_TXE: Data register empty flag (Transmitter)
*                       - I2C_FLAG_RXNE: Data register not empty (Receiver) flag
*                       - I2C_FLAG_STOPF: Stop detection flag (Slave mode)
*                       - I2C_FLAG_ADD10: 10-bit header sent flag (Master mode)
*                       - I2C_FLAG_BTF: Byte transfer finished flag
*                       - I2C_FLAG_ADDR: Address sent flag (Master mode) “ADSL
*                                        Address matched flag (Slave mode)”ENDAD
*                       - I2C_FLAG_SB: Start bit flag (Master mode)
* Output         : None
* Return         : The new state of I2C_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, u32 I2C_FLAG)
{
  FlagStatus bitstatus = RESET;
  vu32 i2creg = 0, i2cxbase = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_FLAG(I2C_FLAG));

  /* Get the I2Cx peripheral base address */
  i2cxbase = (*(u32*)&(I2Cx));
  
  /* Read flag register index */
  i2creg = I2C_FLAG >> 28;
  
  /* Get bit[23:0] of the flag */
  I2C_FLAG &= FLAG_Mask;
  
  if(i2creg != 0)
  {
    /* Get the I2Cx SR1 register address */
    i2cxbase += 0x14;
  }
  else
  {
    /* Flag in I2Cx SR2 Register */
    I2C_FLAG = (u32)(I2C_FLAG >> 16);
    /* Get the I2Cx SR2 register address */
    i2cxbase += 0x18;
  }
  
  if(((*(vu32 *)i2cxbase) & I2C_FLAG) != (u32)RESET)
  {
    /* I2C_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_FLAG is reset */
    bitstatus = RESET;
  }
  
  /* Return the I2C_FLAG status */
  return  bitstatus;
}

/*******************************************************************************
* Function Name  : I2C_ClearFlag
* Description    : Clears the I2Cx's pending flags.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - I2C_FLAG: specifies the flag to clear. 
*                    This parameter can be any combination of the following
*                    values:
*                       - I2C_FLAG_SMBALERT: SMBus Alert flag
*                       - I2C_FLAG_TIMEOUT: Timeout or Tlow error flag
*                       - I2C_FLAG_PECERR: PEC error in reception flag
*                       - I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode)
*                       - I2C_FLAG_AF: Acknowledge failure flag
*                       - I2C_FLAG_ARLO: Arbitration lost flag (Master mode)
*                       - I2C_FLAG_BERR: Bus error flag
*                       
*                  Notes: 
*                        - STOPF (STOP detection) is cleared by software 
*                          sequence: a read operation to I2C_SR1 register 
*                          (I2C_GetFlagStatus()) followed by a write operation 
*                          to I2C_CR1 register (I2C_Cmd() to re-enable the 
*                          I2C peripheral). 
*                        - ADD10 (10-bit header sent) is cleared by software 
*                          sequence: a read operation to I2C_SR1 
*                          (I2C_GetFlagStatus()) followed by writing the
*                          second byte of the address in DR register.
*                        - BTF (Byte Transfer Finished) is cleared by software 
*                          sequence: a read operation to I2C_SR1 register 
*                          (I2C_GetFlagStatus()) followed by a read/write to 
*                          I2C_DR register (I2C_SendData()).
*                        - ADDR (Address sent) is cleared by software sequence: 
*                          a read operation to I2C_SR1 register 
*                          (I2C_GetFlagStatus()) followed by a read operation to 
*                          I2C_SR2 register ((void)(I2Cx->SR2)).
*                        - SB (Start Bit) is cleared software sequence: a read 
*                          operation to I2C_SR1 register (I2C_GetFlagStatus()) 
*                          followed by a write operation to I2C_DR reigister 
*                          (I2C_SendData()). 
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_ClearFlag(I2C_TypeDef* I2Cx, u32 I2C_FLAG)
{
  u32 flagpos = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLEAR_FLAG(I2C_FLAG));

  /* Get the I2C flag position */
  flagpos = I2C_FLAG & FLAG_Mask;

  /* Clear the selected I2C flag */
  I2Cx->SR1 = (u16)~flagpos;
}

/*******************************************************************************
* Function Name  : I2C_GetITStatus
* Description    : Checks whether the specified I2C interrupt has occurred or not.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - I2C_IT: specifies the interrupt source to check. 
*                    This parameter can be one of the following values:
*                       - I2C_IT_SMBALERT: SMBus Alert flag
*                       - I2C_IT_TIMEOUT: Timeout or Tlow error flag
*                       - I2C_IT_PECERR: PEC error in reception flag
*                       - I2C_IT_OVR: Overrun/Underrun flag (Slave mode)
*                       - I2C_IT_AF: Acknowledge failure flag
*                       - I2C_IT_ARLO: Arbitration lost flag (Master mode)
*                       - I2C_IT_BERR: Bus error flag
*                       - I2C_IT_TXE: Data register empty flag (Transmitter)
*                       - I2C_IT_RXNE: Data register not empty (Receiver) flag
*                       - I2C_IT_STOPF: Stop detection flag (Slave mode)
*                       - I2C_IT_ADD10: 10-bit header sent flag (Master mode)
*                       - I2C_IT_BTF: Byte transfer finished flag
*                       - I2C_IT_ADDR: Address sent flag (Master mode) “ADSL
*                                      Address matched flag (Slave mode)”ENDAD
*                       - I2C_IT_SB: Start bit flag (Master mode)
* Output         : None
* Return         : The new state of I2C_IT (SET or RESET).
*******************************************************************************/
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, u32 I2C_IT)
{
  ITStatus bitstatus = RESET;
  u32 enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_IT(I2C_IT));

  /* Check if the interrupt source is enabled or not */
  enablestatus = (u32)(((I2C_IT & ITEN_Mask) >> 16) & (I2Cx->CR2)) ;  

  /* Get bit[23:0] of the flag */
  I2C_IT &= FLAG_Mask;

  /* Check the status of the specified I2C flag */
  if (((I2Cx->SR1 & I2C_IT) != (u32)RESET) && enablestatus)
  {
    /* I2C_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_IT is reset */
    bitstatus = RESET;
  }
  /* Return the I2C_IT status */
  return  bitstatus;
}

/*******************************************************************************
* Function Name  : I2C_ClearITPendingBit
* Description    : Clears the I2Cx’s interrupt pending bits.
* Input          : - I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  - I2C_IT: specifies the interrupt pending bit to clear. 
*                    This parameter can be any combination of the following 
*                    values:
*                       - I2C_IT_SMBALERT: SMBus Alert interrupt
*                       - I2C_IT_TIMEOUT: Timeout or Tlow error interrupt
*                       - I2C_IT_PECERR: PEC error in reception  interrupt
*                       - I2C_IT_OVR: Overrun/Underrun interrupt (Slave mode)
*                       - I2C_IT_AF: Acknowledge failure interrupt
*                       - I2C_IT_ARLO: Arbitration lost interrupt (Master mode)
*                       - I2C_IT_BERR: Bus error interrupt
*                       
*                  Notes:
*                        - STOPF (STOP detection) is cleared by software 
*                          sequence: a read operation to I2C_SR1 register 
*                          (I2C_GetITStatus()) followed by a write operation to 
*                          I2C_CR1 register (I2C_Cmd() to re-enable the I2C 
*                          peripheral). 
*                        - ADD10 (10-bit header sent) is cleared by software 
*                          sequence: a read operation to I2C_SR1 
*                          (I2C_GetITStatus()) followed by writing the second 
*                          byte of the address in I2C_DR register.
*                        - BTF (Byte Transfer Finished) is cleared by software 
*                          sequence: a read operation to I2C_SR1 register 
*                          (I2C_GetITStatus()) followed by a read/write to 
*                          I2C_DR register (I2C_SendData()).
*                        - ADDR (Address sent) is cleared by software sequence: 
*                          a read operation to I2C_SR1 register (I2C_GetITStatus()) 
*                          followed by a read operation to I2C_SR2 register 
*                          ((void)(I2Cx->SR2)).
*                        - SB (Start Bit) is cleared by software sequence: a 
*                          read operation to I2C_SR1 register (I2C_GetITStatus()) 
*                          followed by a write operation to I2C_DR reigister 
*                          (I2C_SendData()). 
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, u32 I2C_IT)
{
  u32 flagpos = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLEAR_IT(I2C_IT));

  /* Get the I2C flag position */
  flagpos = I2C_IT & FLAG_Mask;

  /* Clear the selected I2C flag */
  I2Cx->SR1 = (u16)~flagpos;
}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
