/***************COPYRIGHT(C)  2019 WCH. A11 rights reserved*********************
* File Name          : ch32f10x_i2c.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2019/10/15
* Description        : This file provides all the I2C firmware functions. 
*******************************************************************************/ 
#include "ch32f10x_i2c.h"
#include "ch32f10x_rcc.h"


/* I2C SPE mask */
#define CTLR1_PE_Set              ((uint16_t)0x0001)
#define CTLR1_PE_Reset            ((uint16_t)0xFFFE)

/* I2C START mask */
#define CTLR1_START_Set           ((uint16_t)0x0100)
#define CTLR1_START_Reset         ((uint16_t)0xFEFF)

/* I2C STOP mask */
#define CTLR1_STOP_Set            ((uint16_t)0x0200)
#define CTLR1_STOP_Reset          ((uint16_t)0xFDFF)

/* I2C ACK mask */
#define CTLR1_ACK_Set             ((uint16_t)0x0400)
#define CTLR1_ACK_Reset           ((uint16_t)0xFBFF)

/* I2C ENGC mask */
#define CTLR1_ENGC_Set            ((uint16_t)0x0040)
#define CTLR1_ENGC_Reset          ((uint16_t)0xFFBF)

/* I2C SWRST mask */
#define CTLR1_SWRST_Set           ((uint16_t)0x8000)
#define CTLR1_SWRST_Reset         ((uint16_t)0x7FFF)

/* I2C PEC mask */
#define CTLR1_PEC_Set             ((uint16_t)0x1000)
#define CTLR1_PEC_Reset           ((uint16_t)0xEFFF)

/* I2C ENPEC mask */
#define CTLR1_ENPEC_Set           ((uint16_t)0x0020)
#define CTLR1_ENPEC_Reset         ((uint16_t)0xFFDF)

/* I2C ENARP mask */
#define CTLR1_ENARP_Set           ((uint16_t)0x0010)
#define CTLR1_ENARP_Reset         ((uint16_t)0xFFEF)

/* I2C NOSTRETCH mask */
#define CTLR1_NOSTRETCH_Set       ((uint16_t)0x0080)
#define CTLR1_NOSTRETCH_Reset     ((uint16_t)0xFF7F)

/* I2C registers Masks */
#define CTLR1_CLEAR_Mask          ((uint16_t)0xFBF5)

/* I2C DMAEN mask */
#define CTLR2_DMAEN_Set           ((uint16_t)0x0800)
#define CTLR2_DMAEN_Reset         ((uint16_t)0xF7FF)

/* I2C LAST mask */
#define CTLR2_LAST_Set            ((uint16_t)0x1000)
#define CTLR2_LAST_Reset          ((uint16_t)0xEFFF)

/* I2C FREQ mask */
#define CTLR2_FREQ_Reset          ((uint16_t)0xFFC0)

/* I2C ADD0 mask */
#define OADDR1_ADD0_Set           ((uint16_t)0x0001)
#define OADDR1_ADD0_Reset         ((uint16_t)0xFFFE)

/* I2C ENDUAL mask */
#define OADDR2_ENDUAL_Set         ((uint16_t)0x0001)
#define OADDR2_ENDUAL_Reset       ((uint16_t)0xFFFE)

/* I2C ADD2 mask */
#define OADDR2_ADD2_Reset         ((uint16_t)0xFF01)

/* I2C F/S mask */
#define CKCFGR_FS_Set             ((uint16_t)0x8000)

/* I2C CCR mask */
#define CKCFGR_CCR_Set            ((uint16_t)0x0FFF)

/* I2C FLAG mask */
#define FLAG_Mask                 ((uint32_t)0x00FFFFFF)

/* I2C Interrupt Enable mask */
#define ITEN_Mask                 ((uint32_t)0x07000000)


/*******************************************************************************
* Function Name  : I2C_DeInit
* Description    : Deinitializes the I2Cx peripheral registers to their default 
*      reset values.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* Return         : None
*******************************************************************************/	
void I2C_DeInit(I2C_TypeDef* I2Cx)
{
  if (I2Cx == I2C1)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
  }
  else
  {
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
  }
}

/*******************************************************************************
* Function Name  : I2C_Init
* Description    : Initializes the I2Cx peripheral according to the specified 
*      parameters in the I2C_InitStruct.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that
*      contains the configuration information for the specified I2C peripheral.
* Return         : None
*******************************************************************************/	
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
  uint16_t tmpreg = 0, freqrange = 0;
  uint16_t result = 0x04;
  uint32_t pclk1 = 8000000;
	
  RCC_ClocksTypeDef  rcc_clocks;

/*---------------------------- I2Cx CR2 Configuration ------------------------*/
  tmpreg = I2Cx->CTLR2;
  tmpreg &= CTLR2_FREQ_Reset;
  RCC_GetClocksFreq(&rcc_clocks);
  pclk1 = rcc_clocks.PCLK1_Frequency;
  freqrange = (uint16_t)(pclk1 / 1000000);
  tmpreg |= freqrange;
  I2Cx->CTLR2 = tmpreg;

/*---------------------------- I2Cx CCR Configuration ------------------------*/
  I2Cx->CTLR1 &= CTLR1_PE_Reset;
  tmpreg = 0;

  if (I2C_InitStruct->I2C_ClockSpeed <= 100000)
  {
    result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed << 1));

    if (result < 0x04)
    {
      result = 0x04;  
    }
		
    tmpreg |= result;	  
    I2Cx->RTR = freqrange + 1; 
  }
  else 
  {
    if (I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_2)
    {
      result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 3));
    }
    else
    {
      result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 25));
      result |= I2C_DutyCycle_16_9;
    }

    if ((result & CKCFGR_CCR_Set) == 0)
    {
      result |= (uint16_t)0x0001;  
    }
		
    tmpreg |= (uint16_t)(result | CKCFGR_FS_Set);
    I2Cx->RTR = (uint16_t)(((freqrange * (uint16_t)300) / (uint16_t)1000) + (uint16_t)1);  
  }

  I2Cx->CKCFGR = tmpreg;
  I2Cx->CTLR1 |= CTLR1_PE_Set;

/*---------------------------- I2Cx CR1 Configuration ------------------------*/
  tmpreg = I2Cx->CTLR1;
  tmpreg &= CTLR1_CLEAR_Mask;
  tmpreg |= (uint16_t)((uint32_t)I2C_InitStruct->I2C_Mode | I2C_InitStruct->I2C_Ack);
  I2Cx->CTLR1 = tmpreg;

/*---------------------------- I2Cx OAR1 Configuration -----------------------*/
  I2Cx->OADDR1 = (I2C_InitStruct->I2C_AcknowledgedAddress | I2C_InitStruct->I2C_OwnAddress1);
}

/*******************************************************************************
* Function Name  : I2C_StructInit
* Description    : Fills each I2C_InitStruct member with its default value.
* Input          : I2C_InitStruct: pointer to an I2C_InitTypeDef structure which 
*      will be initialized.
* Return         : None
*******************************************************************************/
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
/*---------------- Reset I2C init structure parameters values ----------------*/
  I2C_InitStruct->I2C_ClockSpeed = 5000;
  I2C_InitStruct->I2C_Mode = I2C_Mode_I2C;
  I2C_InitStruct->I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStruct->I2C_OwnAddress1 = 0;
  I2C_InitStruct->I2C_Ack = I2C_Ack_Disable;
  I2C_InitStruct->I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
}

/*******************************************************************************
* Function Name  : I2C_Cmd
* Description    : Enables or disables the specified I2C peripheral.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral. 
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->CTLR1 |= CTLR1_PE_Set;
  }
  else
  {
    I2Cx->CTLR1 &= CTLR1_PE_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_DMACmd
* Description    : Enables or disables the specified I2C DMA requests.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral. 
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void I2C_DMACmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->CTLR2 |= CTLR2_DMAEN_Set;
  }
  else
  {
    I2Cx->CTLR2 &= CTLR2_DMAEN_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_DMALastTransferCmd
* Description    : Specifies if the next DMA transfer will be the last one.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral. 
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void I2C_DMALastTransferCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->CTLR2 |= CTLR2_LAST_Set;
  }
  else
  {
    I2Cx->CTLR2 &= CTLR2_LAST_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_GenerateSTART
* Description    : Generates I2Cx communication START condition.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral. 
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->CTLR1 |= CTLR1_START_Set;
  }
  else
  {
    I2Cx->CTLR1 &= CTLR1_START_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_GenerateSTOP
* Description    : Generates I2Cx communication STOP condition.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral. 
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->CTLR1 |= CTLR1_STOP_Set;
  }
  else
  {
    I2Cx->CTLR1 &= CTLR1_STOP_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_AcknowledgeConfig
* Description    : Enables or disables the specified I2C acknowledge feature.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral. 
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->CTLR1 |= CTLR1_ACK_Set;
  }
  else
  {
    I2Cx->CTLR1 &= CTLR1_ACK_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_OwnAddress2Config
* Description    : Configures the specified I2C own address2.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral. 
*                  Address: specifies the 7bit I2C own address2.
* Return         : None
*******************************************************************************/
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint8_t Address)
{
  uint16_t tmpreg = 0;

  tmpreg = I2Cx->OADDR2;
  tmpreg &= OADDR2_ADD2_Reset;
  tmpreg |= (uint16_t)((uint16_t)Address & (uint16_t)0x00FE);
  I2Cx->OADDR2 = tmpreg;
}

/*******************************************************************************
* Function Name  : I2C_DualAddressCmd
* Description    : Enables or disables the specified I2C dual addressing mode.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral. 
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void I2C_DualAddressCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->OADDR2 |= OADDR2_ENDUAL_Set;
  }
  else
  {
    I2Cx->OADDR2 &= OADDR2_ENDUAL_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_GeneralCallCmd
* Description    : Enables or disables the specified I2C general call feature.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral. 
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void I2C_GeneralCallCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->CTLR1 |= CTLR1_ENGC_Set;
  }
  else
  {
    I2Cx->CTLR1 &= CTLR1_ENGC_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_ITConfig
* Description    : Enables or disables the specified I2C interrupts.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  I2C_IT: specifies the I2C interrupts sources to be enabled or disabled.
*                    I2C_IT_BUF: Buffer interrupt mask.
*                    I2C_IT_EVT: Event interrupt mask.
*                    I2C_IT_ERR: Error interrupt mask.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_IT, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->CTLR2 |= I2C_IT;
  }
  else
  {
    I2Cx->CTLR2 &= (uint16_t)~I2C_IT;
  }
}

/*******************************************************************************
* Function Name  : I2C_SendData
* Description    : Sends a data byte through the I2Cx peripheral.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  Data: Byte to be transmitted.
* Return         : None
*******************************************************************************/
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)
{
  I2Cx->DATAR = Data;
}

/*******************************************************************************
* Function Name  : I2C_ReceiveData
* Description    : Returns the most recent received data by the I2Cx peripheral.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* Return         : The value of the received data.
*******************************************************************************/
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
  return (uint8_t)I2Cx->DATAR;
}

/*******************************************************************************
* Function Name  : I2C_Send7bitAddress
* Description    : Transmits the address byte to select the slave device.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  Address: specifies the slave address which will be transmitted.
*                  I2C_Direction: specifies whether the I2C device will be a
*      Transmitter or a Receiver. 
*                    I2C_Direction_Transmitter: Transmitter mode.
*                    I2C_Direction_Receiver: Receiver mode.
* Return         : None
*******************************************************************************/
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, uint8_t Address, uint8_t I2C_Direction)
{
  if (I2C_Direction != I2C_Direction_Transmitter)
  {
    Address |= OADDR1_ADD0_Set;
  }
  else
  {
    Address &= OADDR1_ADD0_Reset;
  }

  I2Cx->DATAR = Address;
}

/*******************************************************************************
* Function Name  : I2C_ReadRegister
* Description    : Reads the specified I2C register and returns its value.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  I2C_Register: specifies the register to read.
*                    I2C_Register_CTLR1.
*                    I2C_Register_CTLR2.
*                    I2C_Register_OADDR1.
*                    I2C_Register_OADDR2.
*                    I2C_Register_DATAR.
*                    I2C_Register_STAR1.
*                    I2C_Register_STAR2.
*                    I2C_Register_CKCFGR.
*                    I2C_Register_RTR.
* Return         : The value of the received data.
*******************************************************************************/
uint16_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register)
{
  __IO uint32_t tmp = 0;

  tmp = (uint32_t) I2Cx;
  tmp += I2C_Register;

  return (*(__IO uint16_t *) tmp);
}

/*******************************************************************************
* Function Name  : I2C_SoftwareResetCmd
* Description    : Enables or disables the specified I2C software reset.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->CTLR1 |= CTLR1_SWRST_Set;
  }
  else
  {
    I2Cx->CTLR1 &= CTLR1_SWRST_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_NACKPositionConfig
* Description    : Selects the specified I2C NACK position in master receiver mode. 
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  I2C_NACKPosition: specifies the NACK position.
*                    I2C_NACKPosition_Next: indicates that the next byte will be 
*      the last received byte.  
*                    I2C_NACKPosition_Current: indicates that current byte is the
*      last received byte.
* Return         : None
*******************************************************************************/
void I2C_NACKPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_NACKPosition)
{
  if (I2C_NACKPosition == I2C_NACKPosition_Next)
  {
    I2Cx->CTLR1 |= I2C_NACKPosition_Next;
  }
  else
  {
    I2Cx->CTLR1 &= I2C_NACKPosition_Current;
  }
}

/*******************************************************************************
* Function Name  : I2C_SMBusAlertConfig
* Description    : Drives the SMBusAlert pin high or low for the specified I2C.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  I2C_SMBusAlert: specifies SMBAlert pin level. 
*                    I2C_SMBusAlert_Low: SMBAlert pin driven low.
*                    I2C_SMBusAlert_High: SMBAlert pin driven high.
* Return         : None
*******************************************************************************/
void I2C_SMBusAlertConfig(I2C_TypeDef* I2Cx, uint16_t I2C_SMBusAlert)
{
  if (I2C_SMBusAlert == I2C_SMBusAlert_Low)
  {
    I2Cx->CTLR1 |= I2C_SMBusAlert_Low;
  }
  else
  {
    I2Cx->CTLR1 &= I2C_SMBusAlert_High;
  }
}

/*******************************************************************************
* Function Name  : I2C_TransmitPEC
* Description    : Enables or disables the specified I2C PEC transfer.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void I2C_TransmitPEC(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->CTLR1 |= CTLR1_PEC_Set;
  }
  else
  {
    I2Cx->CTLR1 &= CTLR1_PEC_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_PECPositionConfig
* Description    : Selects the specified I2C PEC position.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  I2C_PECPosition: specifies the PEC position. 
*                    I2C_PECPosition_Next: indicates that the next byte is PEC.
*                    I2C_PECPosition_Current: indicates that current byte is PEC.
* Return         : None
*******************************************************************************/
void I2C_PECPositionConfig(I2C_TypeDef* I2Cx, uint16_t I2C_PECPosition)
{
  if (I2C_PECPosition == I2C_PECPosition_Next)
  {
    I2Cx->CTLR1 |= I2C_PECPosition_Next;
  }
  else
  {
    I2Cx->CTLR1 &= I2C_PECPosition_Current;
  }
}

/*******************************************************************************
* Function Name  : I2C_CalculatePEC
* Description    : Enables or disables the PEC value calculation of the transferred bytes.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void I2C_CalculatePEC(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->CTLR1 |= CTLR1_ENPEC_Set;
  }
  else
  {
    I2Cx->CTLR1 &= CTLR1_ENPEC_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_GetPEC
* Description    : Returns the PEC value for the specified I2C.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* Return         : The PEC value.
*******************************************************************************/
uint8_t I2C_GetPEC(I2C_TypeDef* I2Cx)
{
  return ((I2Cx->STAR2) >> 8);
}

/*******************************************************************************
* Function Name  : I2C_ARPCmd
* Description    : Enables or disables the specified I2C ARP.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : The PEC value.
*******************************************************************************/
void I2C_ARPCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState != DISABLE)
  {
    I2Cx->CTLR1 |= CTLR1_ENARP_Set;
  }
  else
  {
    I2Cx->CTLR1 &= CTLR1_ENARP_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_StretchClockCmd
* Description    : Enables or disables the specified I2C Clock stretching.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  NewState: ENABLE or DISABLE.
* Return         : None
*******************************************************************************/
void I2C_StretchClockCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
  if (NewState == DISABLE)
  {
    I2Cx->CTLR1 |= CTLR1_NOSTRETCH_Set;
  }
  else
  {
    I2Cx->CTLR1 &= CTLR1_NOSTRETCH_Reset;
  }
}

/*******************************************************************************
* Function Name  : I2C_FastModeDutyCycleConfig
* Description    : Selects the specified I2C fast mode duty cycle.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  I2C_DutyCycle: specifies the fast mode duty cycle.
*                    I2C_DutyCycle_2: I2C fast mode Tlow/Thigh = 2.
*                    I2C_DutyCycle_16_9: I2C fast mode Tlow/Thigh = 16/9.
* Return         : None
*******************************************************************************/
void I2C_FastModeDutyCycleConfig(I2C_TypeDef* I2Cx, uint16_t I2C_DutyCycle)
{
  if (I2C_DutyCycle != I2C_DutyCycle_16_9)
  {
    I2Cx->CKCFGR &= I2C_DutyCycle_2;
  }
  else
  {
    I2Cx->CKCFGR |= I2C_DutyCycle_16_9;
  }
}

/**
 ****************************************************************************************
 *
 *                         I2C State Monitoring Functions
 *                       
 ****************************************************************************************   
 * This I2C driver provides three different ways for I2C state monitoring
 *  depending on the application requirements and constraints:
 *        
 *  
 * 1) Basic state monitoring:
 *    Using I2C_CheckEvent() function:
 *    It compares the status registers (SR1 and SR2) content to a given event
 *    (can be the combination of one or more flags).
 *    It returns SUCCESS if the current status includes the given flags 
 *    and returns ERROR if one or more flags are missing in the current status.
 *    - When to use:
 *      - This function is suitable for most applications as well as for startup 
 *      activity since the events are fully described in the product reference manual 
 *      (RM0008).
 *      - It is also suitable for users who need to define their own events.
 *    - Limitations:
 *      - If an error occurs (ie. error flags are set besides to the monitored flags),
 *        the I2C_CheckEvent() function may return SUCCESS despite the communication
 *        hold or corrupted real state. 
 *        In this case, it is advised to use error interrupts to monitor the error
 *        events and handle them in the interrupt IRQ handler.
 *        
 *        @note 
 *        For error management, it is advised to use the following functions:
 *          - I2C_ITConfig() to configure and enable the error interrupts (I2C_IT_ERR).
 *          - I2Cx_ER_IRQHandler() which is called when the error interrupt occurs.
 *            Where x is the peripheral instance (I2C1, I2C2 ...)
 *          - I2C_GetFlagStatus() or I2C_GetITStatus() to be called into I2Cx_ER_IRQHandler() 
 *            in order to determine which error occured.
 *          - I2C_ClearFlag() or I2C_ClearITPendingBit() and/or I2C_SoftwareResetCmd()
 *            and/or I2C_GenerateStop() in order to clear the error flag and source,
 *            and return to correct communication status.
 *            
 *
 *  2) Advanced state monitoring:
 *     Using the function I2C_GetLastEvent() which returns the image of both status 
 *     registers in a single word (uint32_t) (Status Register 2 value is shifted left 
 *     by 16 bits and concatenated to Status Register 1).
 *     - When to use:
 *       - This function is suitable for the same applications above but it allows to
 *         overcome the mentioned limitation of I2C_GetFlagStatus() function.
 *         The returned value could be compared to events already defined in the 
 *         library (ch32f10x_i2c.h) or to custom values defined by user.
 *       - This function is suitable when multiple flags are monitored at the same time.
 *       - At the opposite of I2C_CheckEvent() function, this function allows user to
 *         choose when an event is accepted (when all events flags are set and no 
 *         other flags are set or just when the needed flags are set like 
 *         I2C_CheckEvent() function).
 *     - Limitations:
 *       - User may need to define his own events.
 *       - Same remark concerning the error management is applicable for this 
 *         function if user decides to check only regular communication flags (and 
 *         ignores error flags).
 *     
 *
 *  3) Flag-based state monitoring:
 *     Using the function I2C_GetFlagStatus() which simply returns the status of 
 *     one single flag (ie. I2C_FLAG_RXNE ...). 
 *     - When to use:
 *        - This function could be used for specific applications or in debug phase.
 *        - It is suitable when only one flag checking is needed (most I2C events 
 *          are monitored through multiple flags).
 *     - Limitations: 
 *        - When calling this function, the Status register is accessed. Some flags are
 *          cleared when the status register is accessed. So checking the status
 *          of one Flag, may clear other ones.
 *        - Function may need to be called twice or more in order to monitor one 
 *          single event.
 *
 *  For detailed description of Events, please refer to section I2C_Events in 
 *  ch32f10x_i2c.h file.
 *  
 */

/**
 * 
 *  1) Basic state monitoring
 *******************************************************************************
 */

/*******************************************************************************
* Function Name  : I2C_CheckEvent
* Description    : Checks whether the last I2Cx Event is equal to the one passed
*      as parameter.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  I2C_EVENT: specifies the event to be checked. 
*                    I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED           : EV1.
*                    I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED              : EV1.
*                    I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED     : EV1.
*                    I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED        : EV1.
*                    I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED            : EV1.
*                    I2C_EVENT_SLAVE_BYTE_RECEIVED                         : EV2.
*                    (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF)      : EV2.
*                    (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL)    : EV2.
*                    I2C_EVENT_SLAVE_BYTE_TRANSMITTED                      : EV3.
*                    (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALF)   : EV3.
*                    (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL) : EV3.
*                    I2C_EVENT_SLAVE_ACK_FAILURE                           : EV3_2.
*                    I2C_EVENT_SLAVE_STOP_DETECTED                         : EV4.
*                    I2C_EVENT_MASTER_MODE_SELECT                          : EV5.
*                    I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED            : EV6.    
*                    I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED               : EV6.
*                    I2C_EVENT_MASTER_BYTE_RECEIVED                        : EV7.
*                    I2C_EVENT_MASTER_BYTE_TRANSMITTING                    : EV8.
*                    I2C_EVENT_MASTER_BYTE_TRANSMITTED                     : EV8_2.
*                    I2C_EVENT_MASTER_MODE_ADDRESS10                       : EV9.
* Return         : ErrorStatus: SUCCESS or ERROR.
*******************************************************************************/	
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
  uint32_t lastevent = 0;
  uint32_t flag1 = 0, flag2 = 0;
  ErrorStatus status = ERROR;

  flag1 = I2Cx->STAR1;
  flag2 = I2Cx->STAR2;
  flag2 = flag2 << 16;

  lastevent = (flag1 | flag2) & FLAG_Mask;

  if ((lastevent & I2C_EVENT) == I2C_EVENT)
  {
    status = SUCCESS;
  }
  else
  {
    status = ERROR;
  }

  return status;
}

/**
 * 
 *  2) Advanced state monitoring
 *******************************************************************************
 */

/*******************************************************************************
* Function Name  : I2C_GetLastEvent
* Description    : Returns the last I2Cx Event.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* Return         : The last event.
*******************************************************************************/
uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx)
{
  uint32_t lastevent = 0;
  uint32_t flag1 = 0, flag2 = 0;

  flag1 = I2Cx->STAR1;
  flag2 = I2Cx->STAR2;
  flag2 = flag2 << 16;
  lastevent = (flag1 | flag2) & FLAG_Mask;

  return lastevent;
}

/**
 * 
 *  3) Flag-based state monitoring
 *******************************************************************************
 */

/*******************************************************************************
* Function Name  : I2C_GetFlagStatus
* Description    : Checks whether the last I2Cx Event is equal to the one passed
*      as parameter.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  I2C_FLAG: specifies the flag to check.  
*                    I2C_FLAG_DUALF: Dual flag (Slave mode).
*                    I2C_FLAG_SMBHOST: SMBus host header (Slave mode).
*                    I2C_FLAG_SMBDEFAULT: SMBus default header (Slave mode).
*                    I2C_FLAG_GENCALL: General call header flag (Slave mode).
*                    I2C_FLAG_TRA: Transmitter/Receiver flag.
*                    I2C_FLAG_BUSY: Bus busy flag.
*                    I2C_FLAG_MSL: Master/Slave flag.
*                    I2C_FLAG_SMBALERT: SMBus Alert flag.
*                    I2C_FLAG_TIMEOUT: Timeout or Tlow error flag.
*                    I2C_FLAG_PECERR: PEC error in reception flag.
*                    I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode).
*                    I2C_FLAG_AF: Acknowledge failure flag.
*                    I2C_FLAG_ARLO: Arbitration lost flag (Master mode).
*                    I2C_FLAG_BERR: Bus error flag.
*                    I2C_FLAG_TXE: Data register empty flag (Transmitter).
*                    I2C_FLAG_RXNE: Data register not empty (Receiver) flag.
*                    I2C_FLAG_STOPF: Stop detection flag (Slave mode).
*                    I2C_FLAG_ADD10: 10-bit header sent flag (Master mode).
*                    I2C_FLAG_BTF: Byte transfer finished flag.
*                    I2C_FLAG_ADDR: Address sent flag (Master mode) "ADSL"
*      Address matched flag (Slave mode)"ENDA".
*                    I2C_FLAG_SB: Start bit flag (Master mode).
* Return         : FlagStatus: SET or RESET.
*******************************************************************************/
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{
  FlagStatus bitstatus = RESET;
  __IO uint32_t i2creg = 0, i2cxbase = 0;

  i2cxbase = (uint32_t)I2Cx;
  i2creg = I2C_FLAG >> 28;
  I2C_FLAG &= FLAG_Mask;
  
  if(i2creg != 0)
  {
    i2cxbase += 0x14;
  }
  else
  {
    I2C_FLAG = (uint32_t)(I2C_FLAG >> 16);
    i2cxbase += 0x18;
  }
  
  if(((*(__IO uint32_t *)i2cxbase) & I2C_FLAG) != (uint32_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  
  return  bitstatus;
}

/*******************************************************************************
* Function Name  : I2C_ClearFlag
* Description    : Clears the I2Cx's pending flags.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  I2C_FLAG: specifies the flag to clear. 
*                    I2C_FLAG_SMBALERT: SMBus Alert flag.
*                    I2C_FLAG_TIMEOUT: Timeout or Tlow error flag.
*                    I2C_FLAG_PECERR: PEC error in reception flag.
*                    I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode).
*                    I2C_FLAG_AF: Acknowledge failure flag.
*                    I2C_FLAG_ARLO: Arbitration lost flag (Master mode).
*                    I2C_FLAG_BERR: Bus error flag.                   
* Return         : None
*******************************************************************************/
void I2C_ClearFlag(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG)
{
  uint32_t flagpos = 0;

  flagpos = I2C_FLAG & FLAG_Mask;
  I2Cx->STAR1 = (uint16_t)~flagpos;
}
	
/*******************************************************************************
* Function Name  : I2C_GetITStatus
* Description    : Checks whether the specified I2C interrupt has occurred or not.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  II2C_IT: specifies the interrupt source to check. 
*                    I2C_IT_SMBALERT: SMBus Alert flag.
*                    I2C_IT_TIMEOUT: Timeout or Tlow error flag.
*                    I2C_IT_PECERR: PEC error in reception flag.
*                    I2C_IT_OVR: Overrun/Underrun flag (Slave mode).
*                    I2C_IT_AF: Acknowledge failure flag.
*                    I2C_IT_ARLO: Arbitration lost flag (Master mode).
*                    I2C_IT_BERR: Bus error flag.
*                    I2C_IT_TXE: Data register empty flag (Transmitter).
*                    I2C_IT_RXNE: Data register not empty (Receiver) flag.
*                    I2C_IT_STOPF: Stop detection flag (Slave mode).
*                    I2C_IT_ADD10: 10-bit header sent flag (Master mode).
*                    I2C_IT_BTF: Byte transfer finished flag.
*                    I2C_IT_ADDR: Address sent flag (Master mode) "ADSL"  Address matched
*      flag (Slave mode)"ENDAD".
*                    I2C_IT_SB: Start bit flag (Master mode).                 
* Return         : None
*******************************************************************************/
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;

  enablestatus = (uint32_t)(((I2C_IT & ITEN_Mask) >> 16) & (I2Cx->CTLR2)) ;
  I2C_IT &= FLAG_Mask;

  if (((I2Cx->STAR1 & I2C_IT) != (uint32_t)RESET) && enablestatus)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return  bitstatus;
}

/*******************************************************************************
* Function Name  : I2C_ClearITPendingBit
* Description    : Clears the I2Cx's interrupt pending bits.
* Input          : I2Cx: where x can be 1 or 2 to select the I2C peripheral.
*                  I2C_IT: specifies the interrupt pending bit to clear. 
*                    I2C_IT_SMBALERT: SMBus Alert interrupt.
*                    I2C_IT_TIMEOUT: Timeout or Tlow error interrupt.
*                    I2C_IT_PECERR: PEC error in reception  interrupt.
*                    I2C_IT_OVR: Overrun/Underrun interrupt (Slave mode).
*                    I2C_IT_AF: Acknowledge failure interrupt.
*                    I2C_IT_ARLO: Arbitration lost interrupt (Master mode).
*                    I2C_IT_BERR: Bus error interrupt.               
* Return         : None
*******************************************************************************/
void I2C_ClearITPendingBit(I2C_TypeDef* I2Cx, uint32_t I2C_IT)
{
  uint32_t flagpos = 0;

  flagpos = I2C_IT & FLAG_Mask;
  I2Cx->STAR1 = (uint16_t)~flagpos;
}







