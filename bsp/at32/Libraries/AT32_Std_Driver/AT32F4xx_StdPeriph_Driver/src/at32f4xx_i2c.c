/**
 **************************************************************************
 * File Name    : at32f4xx_i2c.c
 * Description  : at32f4xx I2C source file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_i2c.h"
#include "at32f4xx_rcc.h"


/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup I2C
  * @brief I2C driver modules
  * @{
  */

/** @defgroup I2C_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup I2C_Private_Defines
  * @{
  */

/* I2C SPE mask */
#define CTRL1_PEN_Set               ((uint16_t)0x0001)
#define CTRL1_PEN_Reset             ((uint16_t)0xFFFE)

/* I2C START mask */
#define CTRL1_STARTGEN_Set          ((uint16_t)0x0100)
#define CTRL1_STARTGEN_Reset        ((uint16_t)0xFEFF)

/* I2C STOP mask */
#define CTRL1_STOPGEN_Set           ((uint16_t)0x0200)
#define CTRL1_STOPGEN_Reset         ((uint16_t)0xFDFF)

/* I2C ACK mask */
#define CTRL1_ACKEN_Set             ((uint16_t)0x0400)
#define CTRL1_ACKEN_Reset           ((uint16_t)0xFBFF)

/* I2C ENGC mask */
#define CTRL1_GCEN_Set              ((uint16_t)0x0040)
#define CTRL1_GCEN_Reset            ((uint16_t)0xFFBF)

/* I2C SWRST mask */
#define CTRL1_SWRESET_Set           ((uint16_t)0x8000)
#define CTRL1_SWRESET_Reset         ((uint16_t)0x7FFF)

/* I2C PEC mask */
#define CTRL1_PECTRA_Set            ((uint16_t)0x1000)
#define CTRL1_PECTRA_Reset          ((uint16_t)0xEFFF)

/* I2C ENPEC mask */
#define CTRL1_PECEN_Set             ((uint16_t)0x0020)
#define CTRL1_PECEN_Reset           ((uint16_t)0xFFDF)

/* I2C ENARP mask */
#define CTRL1_ARPEN_Set             ((uint16_t)0x0010)
#define CTRL1_ARPEN_Reset           ((uint16_t)0xFFEF)

/* I2C NOSTRETCH mask */
#define CTRL1_NOCLKSTRETCH_Set      ((uint16_t)0x0080)
#define CTRL1_NOCLKSTRETCH_Reset    ((uint16_t)0xFF7F)

/* I2C registers Masks */
#define CTRL1_CLEAR_MASK            ((uint16_t)0xFBF5)

/* I2C DMAEN mask */
#define CTRL2_DMAEN_Set             ((uint16_t)0x0800)
#define CTRL2_DMAEN_Reset           ((uint16_t)0xF7FF)

/* I2C LAST mask */
#define CTRL2_DMALAST_Set           ((uint16_t)0x1000)
#define CTRL2_DMALAST_Reset         ((uint16_t)0xEFFF)

/* I2C FREQ mask */
#define CTRL2_CLKFREQ_Reset         ((uint16_t)0xFF00)

/* I2C ADD0 mask */
#define OADDR1_ADDR0_Set            ((uint16_t)0x0001)
#define OADDR1_ADDR0_Reset          ((uint16_t)0xFFFE)

/* I2C ENDUAL mask */
#define OADDR2_DUALEN_Set           ((uint16_t)0x0001)
#define OADDR2_DUALEN_Reset         ((uint16_t)0xFFFE)

/* I2C ADD2 mask */
#define OADDR2_ADDR2_Reset          ((uint16_t)0xFF01)

/* I2C F/S mask */
#define CLKCTRL_FSMODE_Set          ((uint16_t)0x8000)

/* I2C CCR mask */
#define CLKCTRL_CLKCTRL_Set         ((uint16_t)0x0FFF)

/* I2C FLAG mask */
#define FLAG_Mask                   ((uint32_t)0x00FFFFFF)

/* I2C Interrupt Enable mask */
#define INTEN_Mask                  ((uint32_t)0x07000000)

/**
  * @}
  */

/** @defgroup I2C_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup I2C_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup I2C_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup I2C_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the I2Cx peripheral registers to their default reset values.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @retval None
  */
void I2C_DeInit(I2C_Type* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  if (I2Cx == I2C1)
  {
    /* Enable I2C1 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_I2C1, ENABLE);
    /* Release I2C1 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_I2C1, DISABLE);
  }
  else if (I2Cx == I2C2)
  {
    /* Enable I2C2 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_I2C2, ENABLE);
    /* Release I2C2 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_I2C2, DISABLE);
  }
#ifdef AT32F403xx
  else if (I2Cx == I2C3)
  {
    /* Enable I2C3 reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_I2C3, ENABLE);
    /* Release I2C3 from reset state */
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_I2C3, DISABLE);
  }
#endif
}

/**
  * @brief  Initializes the I2Cx peripheral according to the specified
  *   parameters in the I2C_InitStruct.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  I2C_InitStruct: pointer to a I2C_InitType structure that
  *   contains the configuration information for the specified I2C peripheral.
  * @retval None
  */
void I2C_Init(I2C_Type* I2Cx, I2C_InitType* I2C_InitStruct)
{
  uint16_t tmpreg = 0, freqrange = 0;
  uint16_t result = 0x04;
  uint32_t pclk1 = 8000000;
  RCC_ClockType  rcc_clocks;
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_BIT_RATE(I2C_InitStruct->I2C_BitRate));
  assert_param(IS_I2C_MODE(I2C_InitStruct->I2C_Mode));
  assert_param(IS_I2C_FM_DUTY_CYCLE(I2C_InitStruct->I2C_FmDutyCycle));
  assert_param(IS_I2C_OWN_ADDRESS1(I2C_InitStruct->I2C_OwnAddr1));
  assert_param(IS_I2C_ACK_STATE(I2C_InitStruct->I2C_Ack));
  assert_param(IS_I2C_ADDR_MODE(I2C_InitStruct->I2C_AddrMode));

  /*---------------------------- I2Cx CTRL2 Configuration ------------------------*/
  /* Get the I2Cx CTRL2 value */
  tmpreg = I2Cx->CTRL2;
  /* Clear frequency FREQ[7:0] bits */
  tmpreg &= CTRL2_CLKFREQ_Reset;
  /* Get pclk1 frequency value */
  RCC_GetClocksFreq(&rcc_clocks);
  pclk1 = rcc_clocks.APB1CLK_Freq;
  /* Set frequency bits depending on pclk1 value */
  freqrange = (uint16_t)(pclk1 / 1000000);
  tmpreg |= freqrange;
  /* Write to I2Cx CTRL2 */
  I2Cx->CTRL2 = tmpreg;

  /*---------------------------- I2Cx CCR Configuration ------------------------*/
  /* Disable the selected I2C peripheral to configure TRISE */
  I2Cx->CTRL1 &= CTRL1_PEN_Reset;
  /* Reset tmpreg value */
  /* Clear F/S, DUTY and CCR[11:0] bits */
  tmpreg = 0;

  /* Configure speed in standard mode */
  if (I2C_InitStruct->I2C_BitRate <= 100000)
  {
    /* Standard mode speed calculate */
    result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_BitRate << 1));

    /* Test if CCR value is under 0x4*/
    if (result < 0x04)
    {
      /* Set minimum allowed value */
      result = 0x04;
    }

    /* Set speed value for standard mode */
    tmpreg |= result;
    /* Set Maximum Rise Time for standard mode */
    I2Cx->TMRISE = freqrange + 1;
  }
  /* Configure speed in fast mode */
  else /*(I2C_InitStruct->I2C_ClockSpeed <= 400000)*/
  {
    if (I2C_InitStruct->I2C_FmDutyCycle == I2C_FmDutyCycle_2_1)
    {
      /* Fast mode speed calculate: Tlow/Thigh = 2 */
      result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_BitRate * 3));
    }
    else /*I2C_InitStruct->I2C_DutyCycle == I2C_FmDutyCycle_16_9*/
    {
      /* Fast mode speed calculate: Tlow/Thigh = 16/9 */
      result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_BitRate * 25));
      /* Set DUTY bit */
      result |= I2C_FmDutyCycle_16_9;
    }

    /* Test if CCR value is under 0x1*/
    if ((result & CLKCTRL_CLKCTRL_Set) == 0)
    {
      /* Set minimum allowed value */
      result |= (uint16_t)0x0001;
    }

    /* Set speed value and set F/S bit for fast mode */
    tmpreg |= (uint16_t)(result | CLKCTRL_FSMODE_Set);
    /* Set Maximum Rise Time for fast mode */
    I2Cx->TMRISE = (uint16_t)(((freqrange * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1);
  }

  /* Write to I2Cx CCR */
  I2Cx->CLKCTRL = tmpreg;
  /* Enable the selected I2C peripheral */
  I2Cx->CTRL1 |= CTRL1_PEN_Set;

  /*---------------------------- I2Cx CTRL1 Configuration ------------------------*/
  /* Get the I2Cx CTRL1 value */
  tmpreg = I2Cx->CTRL1;
  /* Clear ACK, SMBTYPE and  SMBUS bits */
  tmpreg &= CTRL1_CLEAR_MASK;
  /* Configure I2Cx: mode and acknowledgement */
  /* Set SMBTYPE and SMBUS bits according to I2C_Mode value */
  /* Set ACK bit according to I2C_Ack value */
  tmpreg |= (uint16_t)((uint32_t)I2C_InitStruct->I2C_Mode | I2C_InitStruct->I2C_Ack);
  /* Write to I2Cx CTRL1 */
  I2Cx->CTRL1 = tmpreg;

  /*---------------------------- I2Cx OAR1 Configuration -----------------------*/
  /* Set I2Cx Own Address1 and acknowledged address */
  I2Cx->OADDR1 = (I2C_InitStruct->I2C_AddrMode | I2C_InitStruct->I2C_OwnAddr1);
}

/**
  * @brief  Fills each I2C_InitStruct member with its default value.
  * @param  I2C_InitStruct: pointer to an I2C_InitType structure which will be initialized.
  * @retval None
  */
void I2C_StructInit(I2C_InitType* I2C_InitStruct)
{
  /*---------------- Reset I2C init structure parameters values ----------------*/
  /* initialize the I2C_ClockSpeed member */
  I2C_InitStruct->I2C_BitRate = 5000;
  /* Initialize the I2C_Mode member */
  I2C_InitStruct->I2C_Mode = I2C_Mode_I2CDevice;
  /* Initialize the I2C_DutyCycle member */
  I2C_InitStruct->I2C_FmDutyCycle = I2C_FmDutyCycle_2_1;
  /* Initialize the I2C_OwnAddress1 member */
  I2C_InitStruct->I2C_OwnAddr1 = 0;
  /* Initialize the I2C_Ack member */
  I2C_InitStruct->I2C_Ack = I2C_Ack_Disable;
  /* Initialize the I2C_AcknowledgedAddress member */
  I2C_InitStruct->I2C_AddrMode = I2C_AddrMode_7bit;
}

/**
  * @brief  Enables or disables the specified I2C peripheral.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Cmd(I2C_Type* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C peripheral */
    I2Cx->CTRL1 |= CTRL1_PEN_Set;
  }
  else
  {
    /* Disable the selected I2C peripheral */
    I2Cx->CTRL1 &= CTRL1_PEN_Reset;
  }
}

/**
  * @brief  Enables or disables the specified I2C DMA requests.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  NewState: new state of the I2C DMA transfer.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_DMACmd(I2C_Type* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C DMA requests */
    I2Cx->CTRL2 |= CTRL2_DMAEN_Set;
  }
  else
  {
    /* Disable the selected I2C DMA requests */
    I2Cx->CTRL2 &= CTRL2_DMAEN_Reset;
  }
}

/**
  * @brief  Specifies if the next DMA transfer will be the last one.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  NewState: new state of the I2C DMA last transfer.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_DMALastTransferCmd(I2C_Type* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Next DMA transfer is the last transfer */
    I2Cx->CTRL2 |= CTRL2_DMALAST_Set;
  }
  else
  {
    /* Next DMA transfer is not the last transfer */
    I2Cx->CTRL2 &= CTRL2_DMALAST_Reset;
  }
}

/**
  * @brief  Generates I2Cx communication START condition.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  NewState: new state of the I2C START condition generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_GenerateSTART(I2C_Type* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Generate a START condition */
    I2Cx->CTRL1 |= CTRL1_STARTGEN_Set;
  }
  else
  {
    /* Disable the START condition generation */
    I2Cx->CTRL1 &= CTRL1_STARTGEN_Reset;
  }
}

/**
  * @brief  Generates I2Cx communication STOP condition.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  NewState: new state of the I2C STOP condition generation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_GenerateSTOP(I2C_Type* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Generate a STOP condition */
    I2Cx->CTRL1 |= CTRL1_STOPGEN_Set;
  }
  else
  {
    /* Disable the STOP condition generation */
    I2Cx->CTRL1 &= CTRL1_STOPGEN_Reset;
  }
}

/**
  * @brief  Enables or disables the specified I2C acknowledge feature.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  NewState: new state of the I2C Acknowledgement.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_AcknowledgeConfig(I2C_Type* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the acknowledgement */
    I2Cx->CTRL1 |= CTRL1_ACKEN_Set;
  }
  else
  {
    /* Disable the acknowledgement */
    I2Cx->CTRL1 &= CTRL1_ACKEN_Reset;
  }
}

/**
  * @brief  Configures the specified I2C own address2.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  Address: specifies the 7bit I2C own address2.
  * @retval None.
  */
void I2C_OwnAddress2Config(I2C_Type* I2Cx, uint8_t Address)
{
  uint16_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Get the old register value */
  tmpreg = I2Cx->OADDR2;

  /* Reset I2Cx Own address2 bit [7:1] */
  tmpreg &= OADDR2_ADDR2_Reset;

  /* Set I2Cx Own address2 */
  tmpreg |= (uint16_t)((uint16_t)Address & (uint16_t)0x00FE);

  /* Store the new register value */
  I2Cx->OADDR2 = tmpreg;
}

/**
  * @brief  Enables or disables the specified I2C dual addressing mode.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  NewState: new state of the I2C dual addressing mode.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_DualAddressCmd(I2C_Type* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable dual addressing mode */
    I2Cx->OADDR2 |= OADDR2_DUALEN_Set;
  }
  else
  {
    /* Disable dual addressing mode */
    I2Cx->OADDR2 &= OADDR2_DUALEN_Reset;
  }
}

/**
  * @brief  Enables or disables the specified I2C general call feature.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  NewState: new state of the I2C General call.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GeneralCallCmd(I2C_Type* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable generall call */
    I2Cx->CTRL1 |= CTRL1_GCEN_Set;
  }
  else
  {
    /* Disable generall call */
    I2Cx->CTRL1 &= CTRL1_GCEN_Reset;
  }
}

/**
  * @brief  Enables or disables the specified I2C interrupts.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  I2C_INT: specifies the I2C interrupts sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg I2C_INT_BUF: Buffer interrupt mask
  *     @arg I2C_INT_EVT: Event interrupt mask
  *     @arg I2C_INT_ERR: Error interrupt mask
  * @param  NewState: new state of the specified I2C interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_INTConfig(I2C_Type* I2Cx, uint16_t I2C_INT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  assert_param(IS_I2C_CONFIG_INT(I2C_INT));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C interrupts */
    I2Cx->CTRL2 |= I2C_INT;
  }
  else
  {
    /* Disable the selected I2C interrupts */
    I2Cx->CTRL2 &= (uint16_t)~I2C_INT;
  }
}

/**
  * @brief  Sends a data byte through the I2Cx peripheral.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
void I2C_SendData(I2C_Type* I2Cx, uint8_t Data)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  /* Write in the DR register the data to be sent */
  I2Cx->DT = Data;
}

/**
  * @brief  Returns the most recent received data by the I2Cx peripheral.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @retval The value of the received data.
  */
uint8_t I2C_ReceiveData(I2C_Type* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  /* Return the data in the DR register */
  return (uint8_t)I2Cx->DT;
}

/**
  * @brief  Transmits the address byte to select the slave device.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  Address: specifies the slave address which will be transmitted
  * @param  I2C_Direction: specifies whether the I2C device will be a
  *   Transmitter or a Receiver. This parameter can be one of the following values
  *     @arg I2C_Direction_Transmit: Transmitter mode
  *     @arg I2C_Direction_Receive: Receiver mode
  * @retval None.
  */
void I2C_Send7bitAddress(I2C_Type* I2Cx, uint8_t Address, uint8_t I2C_Direction)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_DIRECTION(I2C_Direction));

  /* Test on the direction to set/reset the read/write bit */
  if (I2C_Direction != I2C_Direction_Transmit)
  {
    /* Set the address bit0 for read */
    Address |= OADDR1_ADDR0_Set;
  }
  else
  {
    /* Reset the address bit0 for write */
    Address &= OADDR1_ADDR0_Reset;
  }

  /* Send the address */
  I2Cx->DT = Address;
}

/**
  * @brief  Reads the specified I2C register and returns its value.
  * @param  I2C_Register: specifies the register to read.
  *   This parameter can be one of the following values:
  *     @arg I2C_Register_CTRL1:   CTRL1 register.
  *     @arg I2C_Register_CTRL2:   CTRL2 register.
  *     @arg I2C_Register_OADDR1:  OAR1 register.
  *     @arg I2C_Register_OADDR2:  OAR2 register.
  *     @arg I2C_Register_DT:      DR register.
  *     @arg I2C_Register_STS1:    SR1 register.
  *     @arg I2C_Register_STS2:    SR2 register.
  *     @arg I2C_Register_CLKCTRL: CCR register.
  *     @arg I2C_Register_TMRISE:  TRISE register.
  * @retval The value of the read register.
  */
uint16_t I2C_ReadRegister(I2C_Type* I2Cx, uint8_t I2C_Register)
{
  __IO uint32_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_REGISTER(I2C_Register));

  tmp = (uint32_t) I2Cx;
  tmp += I2C_Register;

  /* Return the selected register value */
  return (*(__IO uint16_t *) tmp);
}

/**
  * @brief  Enables or disables the specified I2C software reset.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  NewState: new state of the I2C software reset.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_SoftwareResetCmd(I2C_Type* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Peripheral under reset */
    I2Cx->CTRL1 |= CTRL1_SWRESET_Set;
  }
  else
  {
    /* Peripheral not under reset */
    I2Cx->CTRL1 &= CTRL1_SWRESET_Reset;
  }
}

/**
  * @brief  Selects the specified I2C NACK position in master receiver mode.
  *         This function is useful in I2C Master Receiver mode when the number
  *         of data to be received is equal to 2. In this case, this function
  *         should be called (with parameter I2C_NACKPosition_Next) before data
  *         reception starts,as described in the 2-byte reception procedure
  *         recommended in Reference Manual in Section: Master receiver.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  I2C_NACKPosition: specifies the NACK position.
  *   This parameter can be one of the following values:
  *     @arg I2C_NACKPosition_Next: indicates that the next byte will be the last
  *          received byte.
  *     @arg I2C_NACKPosition_Current: indicates that current byte is the last
  *          received byte.
  *
  * @note    This function configures the same bit (POS) as I2C_PECPositionConfig()
  *          but is intended to be used in I2C mode while I2C_PECPositionConfig()
  *          is intended to used in SMBUS mode.
  *
  * @retval None
  */
void I2C_NACKPositionConfig(I2C_Type* I2Cx, uint16_t I2C_NACKPosition)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_NACK_POSITION(I2C_NACKPosition));

  /* Check the input parameter */
  if (I2C_NACKPosition == I2C_NACKPosition_Next)
  {
    /* Next byte in shift register is the last received byte */
    I2Cx->CTRL1 |= I2C_NACKPosition_Next;
  }
  else
  {
    /* Current byte in shift register is the last received byte */
    I2Cx->CTRL1 &= I2C_NACKPosition_Current;
  }
}

/**
  * @brief  Drives the SMBusAlert pin high or low for the specified I2C.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  I2C_SMBusAlert: specifies SMBAlert pin level.
  *   This parameter can be one of the following values:
  *     @arg I2C_SMBusAlert_Low: SMBAlert pin driven low
  *     @arg I2C_SMBusAlert_High: SMBAlert pin driven high
  * @retval None
  */
void I2C_SMBusAlertConfig(I2C_Type* I2Cx, uint16_t I2C_SMBusAlert)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_SMBUS_ALERT(I2C_SMBusAlert));

  if (I2C_SMBusAlert == I2C_SMBusAlert_Low)
  {
    /* Drive the SMBusAlert pin Low */
    I2Cx->CTRL1 |= I2C_SMBusAlert_Low;
  }
  else
  {
    /* Drive the SMBusAlert pin High  */
    I2Cx->CTRL1 &= I2C_SMBusAlert_High;
  }
}

/**
  * @brief  Enables or disables the specified I2C PEC transfer.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  NewState: new state of the I2C PEC transmission.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_TransmitPEC(I2C_Type* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C PEC transmission */
    I2Cx->CTRL1 |= CTRL1_PECTRA_Set;
  }
  else
  {
    /* Disable the selected I2C PEC transmission */
    I2Cx->CTRL1 &= CTRL1_PECTRA_Reset;
  }
}

/**
  * @brief  Selects the specified I2C PEC position.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  I2C_PECPosition: specifies the PEC position.
  *   This parameter can be one of the following values:
  *     @arg I2C_PECPosition_Next: indicates that the next byte is PEC
  *     @arg I2C_PECPosition_Current: indicates that current byte is PEC
  *
  * @note    This function configures the same bit (POS) as I2C_NACKPositionConfig()
  *          but is intended to be used in SMBUS mode while I2C_NACKPositionConfig()
  *          is intended to used in I2C mode.
  *
  * @retval None
  */
void I2C_PECPositionConfig(I2C_Type* I2Cx, uint16_t I2C_PECPosition)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_PEC_POSITION(I2C_PECPosition));

  if (I2C_PECPosition == I2C_PECPosition_Next)
  {
    /* Next byte in shift register is PEC */
    I2Cx->CTRL1 |= I2C_PECPosition_Next;
  }
  else
  {
    /* Current byte in shift register is PEC */
    I2Cx->CTRL1 &= I2C_PECPosition_Current;
  }
}

/**
  * @brief  Enables or disables the PEC value calculation of the transferred bytes.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx PEC value calculation.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_CalculatePEC(I2C_Type* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C PEC calculation */
    I2Cx->CTRL1 |= CTRL1_PECEN_Set;
  }
  else
  {
    /* Disable the selected I2C PEC calculation */
    I2Cx->CTRL1 &= CTRL1_PECEN_Reset;
  }
}

/**
  * @brief  Returns the PEC value for the specified I2C.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @retval The PEC value.
  */
uint8_t I2C_GetPEC(I2C_Type* I2Cx)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  /* Return the selected I2C PEC value */
  return ((I2Cx->STS2) >> 8);
}

/**
  * @brief  Enables or disables the specified I2C ARP.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx ARP.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ARPCmd(I2C_Type* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected I2C ARP */
    I2Cx->CTRL1 |= CTRL1_ARPEN_Set;
  }
  else
  {
    /* Disable the selected I2C ARP */
    I2Cx->CTRL1 &= CTRL1_ARPEN_Reset;
  }
}

/**
  * @brief  Enables or disables the specified I2C Clock stretching.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx Clock stretching.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_StretchClockCmd(I2C_Type* I2Cx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState == DISABLE)
  {
    /* Enable the selected I2C Clock stretching */
    I2Cx->CTRL1 |= CTRL1_NOCLKSTRETCH_Set;
  }
  else
  {
    /* Disable the selected I2C Clock stretching */
    I2Cx->CTRL1 &= CTRL1_NOCLKSTRETCH_Reset;
  }
}

/**
  * @brief  Selects the specified I2C fast mode duty cycle.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  I2C_DutyCycle: specifies the fast mode duty cycle.
  *   This parameter can be one of the following values:
  *     @arg I2C_FmDutyCycle_2_1: I2C fast mode Tlow/Thigh = 2
  *     @arg I2C_FmDutyCycle_16_9: I2C fast mode Tlow/Thigh = 16/9
  * @retval None
  */
void I2C_FastModeDutyCycleConfig(I2C_Type* I2Cx, uint16_t I2C_DutyCycle)
{
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_FM_DUTY_CYCLE(I2C_DutyCycle));

  if (I2C_DutyCycle != I2C_FmDutyCycle_16_9)
  {
    /* I2C fast mode Tlow/Thigh=2 */
    I2Cx->CLKCTRL &= I2C_FmDutyCycle_2_1;
  }
  else
  {
    /* I2C fast mode Tlow/Thigh=16/9 */
    I2Cx->CLKCTRL |= I2C_FmDutyCycle_16_9;
  }
}

/**
  * @brief  Checks whether the last I2Cx Event is equal to the one passed
  *   as parameter.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  I2C_EVENT: specifies the event to be checked.
  *   This parameter can be one of the following values:
  *     @arg I2C_EVENT_SLAVE_ADDRESS_TRANSMITTER_MATCHED             : EV1
  *     @arg I2C_EVENT_SLAVE_ADDRESS_RECEIVER_MATCHED                : EV1
  *     @arg I2C_EVENT_SLAVE_SECONDADDRESS_TRANSMITTER_MATCHED       : EV1
  *     @arg I2C_EVENT_SLAVE_SECONDADDRESS_RECEIVER_MATCHED          : EV1
  *     @arg I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED              : EV1
  *     @arg I2C_EVENT_SLAVE_DATA_RECEIVED                           : EV2
  *     @arg (I2C_EVENT_SLAVE_DATA_RECEIVED | I2C_FLAG_DUALF)        : EV2
  *     @arg (I2C_EVENT_SLAVE_DATA_RECEIVED | I2C_FLAG_GCADDRF)      : EV2
  *     @arg I2C_EVENT_SLAVE_DATA_TRANSMITTED                        : EV3
  *     @arg (I2C_EVENT_SLAVE_DATA_TRANSMITTED | I2C_FLAG_DUALF)     : EV3
  *     @arg (I2C_EVENT_SLAVE_DATA_TRANSMITTED | I2C_FLAG_GCADDRF)   : EV3
  *     @arg I2C_EVENT_SLAVE_ACK_FAILURE_DETECTED                    : EV3_2
  *     @arg I2C_EVENT_SLAVE_STOP_DETECTED                           : EV4
  *     @arg I2C_EVENT_MASTER_START_GENERATED                        : EV5
  *     @arg I2C_EVENT_MASTER_ADDRESS | I2C_EVENT_MASTER_TRANSMITTER : EV6
  *     @arg I2C_EVENT_MASTER_ADDRESS_WITH_RECEIVER                  : EV6
  *     @arg I2C_EVENT_MASTER_DATA_RECEIVED                          : EV7
  *     @arg I2C_EVENT_MASTER_DATA_TRANSMITTING                      : EV8
  *     @arg I2C_EVENT_MASTER_DATA_TRANSMITTED                       : EV8_2
  *     @arg I2C_EVENT_MASTER_ADDRESS10_GENERATED                    : EV9
  *
  * @note: For detailed description of Events, please refer to section
  *    I2C_Events in at32f4xx_i2c.h file.
  *
  * @retval An ErrorStatus enumeration value:
  * - SUCCESS: Last event is equal to the I2C_EVENT
  * - ERROR: Last event is different from the I2C_EVENT
  */
ErrorStatus I2C_CheckEvent(I2C_Type* I2Cx, uint32_t I2C_EVENT)
{
  uint32_t lastevent = 0;
  uint32_t flag1 = 0, flag2 = 0;
  ErrorStatus status = ERROR;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_EVENT(I2C_EVENT));

  /* Read the I2Cx status register */
  flag1 = I2Cx->STS1;
  flag2 = I2Cx->STS2;
  flag2 = flag2 << 16;

  /* Get the last event value from I2C status register */
  lastevent = (flag1 | flag2) & FLAG_Mask;

  /* Check whether the last event contains the I2C_EVENT */
  if ((lastevent & I2C_EVENT) == I2C_EVENT)
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

/**
  * @brief  Returns the last I2Cx Event.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  *
  * @note: For detailed description of Events, please refer to section
  *    I2C_Events in at32f4xx_i2c.h file.
  *
  * @retval The last event
  */
uint32_t I2C_GetLastEvent(I2C_Type* I2Cx)
{
  uint32_t lastevent = 0;
  uint32_t flag1 = 0, flag2 = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));

  /* Read the I2Cx status register */
  flag1 = I2Cx->STS1;
  flag2 = I2Cx->STS2;
  flag2 = flag2 << 16;

  /* Get the last event value from I2C status register */
  lastevent = (flag1 | flag2) & FLAG_Mask;

  /* Return status */
  return lastevent;
}

/**
  * @brief  Checks whether the specified I2C flag is set or not.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  I2C_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg I2C_FLAG_DUALF: Dual flag (Slave mode)
  *     @arg I2C_FLAG_SMBHOSTADDRF: SMBus host header (Slave mode)
  *     @arg I2C_FLAG_SMBDEFTADDRF: SMBus default header (Slave mode)
  *     @arg I2C_FLAG_GCADDRF: General call header flag (Slave mode)
  *     @arg I2C_FLAG_TRF: Transmitter/Receiver flag
  *     @arg I2C_FLAG_BUSYF: Bus busy flag
  *     @arg I2C_FLAG_MSF: Master/Slave flag
  *     @arg I2C_FLAG_SMBALERTF: SMBus Alert flag
  *     @arg I2C_FLAG_TIMOUT: Timeout or Tlow error flag
  *     @arg I2C_FLAG_PECERR: PEC error in reception flag
  *     @arg I2C_FLAG_OVRUN: Overrun/Underrun flag (Slave mode)
  *     @arg I2C_FLAG_ACKFAIL: Acknowledge failure flag
  *     @arg I2C_FLAG_ARLOST: Arbitration lost flag (Master mode)
  *     @arg I2C_FLAG_BUSERR: Bus error flag
  *     @arg I2C_FLAG_TDE: Data register empty flag (Transmitter)
  *     @arg I2C_FLAG_RDNE: Data register not empty (Receiver) flag
  *     @arg I2C_FLAG_STOPF: Stop detection flag (Slave mode)
  *     @arg I2C_FLAG_ADDR10F: 10-bit header sent flag (Master mode)
  *     @arg I2C_FLAG_BTFF: Byte transfer finished flag
  *     @arg I2C_FLAG_ADDRF: Address sent flag (Master mode) "ADSL"
  *   Address matched flag (Slave mode)"ENDA"
  *     @arg I2C_FLAG_STARTF: Start bit flag (Master mode)
  * @retval The new state of I2C_FLAG (SET or RESET).
  */
FlagStatus I2C_GetFlagStatus(I2C_Type* I2Cx, uint32_t I2C_FLAG)
{
  FlagStatus bitstatus = RESET;
  __IO uint32_t i2creg = 0, i2cxbase = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_FLAG(I2C_FLAG));

  /* Get the I2Cx peripheral base address */
  i2cxbase = (uint32_t)I2Cx;

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
    I2C_FLAG = (uint32_t)(I2C_FLAG >> 16);
    /* Get the I2Cx SR2 register address */
    i2cxbase += 0x18;
  }

  if(((*(__IO uint32_t *)i2cxbase) & I2C_FLAG) != (uint32_t)RESET)
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



/**
  * @brief  Clears the I2Cx's pending flags.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  I2C_FLAG: specifies the flag to clear.
  *   This parameter can be any combination of the following values:
  *     @arg I2C_FLAG_SMBALERTF: SMBus Alert flag
  *     @arg I2C_FLAG_TIMOUT: Timeout or Tlow error flag
  *     @arg I2C_FLAG_PECERR: PEC error in reception flag
  *     @arg I2C_FLAG_OVRUN: Overrun/Underrun flag (Slave mode)
  *     @arg I2C_FLAG_ACKFAIL: Acknowledge failure flag
  *     @arg I2C_FLAG_ARLOST: Arbitration lost flag (Master mode)
  *     @arg I2C_FLAG_BUSERR: Bus error flag
  *
  * @note
  *   - STOPF (STOP detection) is cleared by software sequence: a read operation
  *     to I2C_SR1 register (I2C_GetFlagStatus()) followed by a write operation
  *     to I2C_CTRL1 register (I2C_Cmd() to re-enable the I2C peripheral).
  *   - ADD10 (10-bit header sent) is cleared by software sequence: a read
  *     operation to I2C_SR1 (I2C_GetFlagStatus()) followed by writing the
  *     second byte of the address in DR register.
  *   - BTF (Byte Transfer Finished) is cleared by software sequence: a read
  *     operation to I2C_SR1 register (I2C_GetFlagStatus()) followed by a
  *     read/write to I2C_DR register (I2C_SendData()).
  *   - ADDR (Address sent) is cleared by software sequence: a read operation to
  *     I2C_SR1 register (I2C_GetFlagStatus()) followed by a read operation to
  *     I2C_SR2 register ((void)(I2Cx->SR2)).
  *   - SB (Start Bit) is cleared software sequence: a read operation to I2C_SR1
  *     register (I2C_GetFlagStatus()) followed by a write operation to I2C_DR
  *     register  (I2C_SendData()).
  * @retval None
  */
void I2C_ClearFlag(I2C_Type* I2Cx, uint32_t I2C_FLAG)
{
  uint32_t flagpos = 0;
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLEAR_FLAG(I2C_FLAG));
  /* Get the I2C flag position */
  flagpos = I2C_FLAG & FLAG_Mask;
  /* Clear the selected I2C flag */
  I2Cx->STS1 = (uint16_t)~flagpos;
}

/**
  * @brief  Checks whether the specified I2C interrupt has occurred or not.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  I2C_INT: specifies the interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg I2C_INT_SMBALERTF: SMBus Alert flag
  *     @arg I2C_INT_TIMOUT: Timeout or Tlow error flag
  *     @arg I2C_INT_PECERR: PEC error in reception flag
  *     @arg I2C_INT_OVRUN: Overrun/Underrun flag (Slave mode)
  *     @arg I2C_INT_ACKFAIL: Acknowledge failure flag
  *     @arg I2C_INT_ARLOST: Arbitration lost flag (Master mode)
  *     @arg I2C_INT_BUSERR: Bus error flag
  *     @arg I2C_INT_TDE: Data register empty flag (Transmitter)
  *     @arg I2C_INT_RDNE: Data register not empty (Receiver) flag
  *     @arg I2C_INT_STOPF: Stop detection flag (Slave mode)
  *     @arg I2C_INT_ADDR10F: 10-bit header sent flag (Master mode)
  *     @arg I2C_INT_BTFF: Byte transfer finished flag
  *     @arg I2C_INT_ADDRF: Address sent flag (Master mode) "ADSL"
  *                       Address matched flag (Slave mode)"ENDAD"
  *     @arg I2C_INT_STARTF: Start bit flag (Master mode)
  * @retval The new state of I2C_INT (SET or RESET).
  */
ITStatus I2C_GetINTStatus(I2C_Type* I2Cx, uint32_t I2C_INT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_GET_INT(I2C_INT));

  /* Check if the interrupt source is enabled or not */
  enablestatus = (uint32_t)(((I2C_INT & INTEN_Mask) >> 16) & (I2Cx->CTRL2)) ;

  /* Get bit[23:0] of the flag */
  I2C_INT &= FLAG_Mask;

  /* Check the status of the specified I2C flag */
  if (((I2Cx->STS1 & I2C_INT) != (uint32_t)RESET) && enablestatus)
  {
    /* I2C_INT is set */
    bitstatus = SET;
  }
  else
  {
    /* I2C_INT is reset */
    bitstatus = RESET;
  }

  /* Return the I2C_INT status */
  return  bitstatus;
}

/**
  * @brief  Clears the I2Cx interrupt pending bits.
  * @param  I2Cx: where x can be 1, 2 or 3 to select the I2C peripheral.
  * @param  I2C_INT: specifies the interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg I2C_INT_SMBALERTF: SMBus Alert interrupt
  *     @arg I2C_INT_TIMOUT: Timeout or Tlow error interrupt
  *     @arg I2C_INT_PECERR: PEC error in reception  interrupt
  *     @arg I2C_INT_OVRUN: Overrun/Underrun interrupt (Slave mode)
  *     @arg I2C_INT_ACKFAIL: Acknowledge failure interrupt
  *     @arg I2C_INT_ARLOST: Arbitration lost interrupt (Master mode)
  *     @arg I2C_INT_BUSERR: Bus error interrupt
  *
  * @note
  *   - STOPF (STOP detection) is cleared by software sequence: a read operation
  *     to I2C_SR1 register (I2C_GetINTStatus()) followed by a write operation to
  *     I2C_CTRL1 register (I2C_Cmd() to re-enable the I2C peripheral).
  *   - ADD10 (10-bit header sent) is cleared by software sequence: a read
  *     operation to I2C_SR1 (I2C_GetINTStatus()) followed by writing the second
  *     byte of the address in I2C_DR register.
  *   - BTF (Byte Transfer Finished) is cleared by software sequence: a read
  *     operation to I2C_SR1 register (I2C_GetINTStatus()) followed by a
  *     read/write to I2C_DR register (I2C_SendData()).
  *   - ADDR (Address sent) is cleared by software sequence: a read operation to
  *     I2C_SR1 register (I2C_GetINTStatus()) followed by a read operation to
  *     I2C_SR2 register ((void)(I2Cx->SR2)).
  *   - SB (Start Bit) is cleared by software sequence: a read operation to
  *     I2C_SR1 register (I2C_GetINTStatus()) followed by a write operation to
  *     I2C_DR register (I2C_SendData()).
  * @retval None
  */
void I2C_ClearITPendingBit(I2C_Type* I2Cx, uint32_t I2C_INT)
{
  uint32_t flagpos = 0;
  /* Check the parameters */
  assert_param(IS_I2C_ALL_PERIPH(I2Cx));
  assert_param(IS_I2C_CLEAR_INT(I2C_INT));
  /* Get the I2C flag position */
  flagpos = I2C_INT & FLAG_Mask;
  /* Clear the selected I2C flag */
  I2Cx->STS1 = (uint16_t)~flagpos;
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


