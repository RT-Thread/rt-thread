/**
  ******************************************************************************
  * @file    stm32f10x_cec.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    11-March-2011
  * @brief   This file provides all the CEC firmware functions.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_cec.h"
#include "stm32f10x_rcc.h"

/** @addtogroup STM32F10x_StdPeriph_Driver
  * @{
  */

/** @defgroup CEC 
  * @brief CEC driver modules
  * @{
  */

/** @defgroup CEC_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */


/** @defgroup CEC_Private_Defines
  * @{
  */ 

/* ------------ CEC registers bit address in the alias region ----------- */
#define CEC_OFFSET                (CEC_BASE - PERIPH_BASE)

/* --- CFGR Register ---*/

/* Alias word address of PE bit */
#define CFGR_OFFSET                 (CEC_OFFSET + 0x00)
#define PE_BitNumber                0x00
#define CFGR_PE_BB                  (PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (PE_BitNumber * 4))

/* Alias word address of IE bit */
#define IE_BitNumber                0x01
#define CFGR_IE_BB                  (PERIPH_BB_BASE + (CFGR_OFFSET * 32) + (IE_BitNumber * 4))

/* --- CSR Register ---*/

/* Alias word address of TSOM bit */
#define CSR_OFFSET                  (CEC_OFFSET + 0x10)
#define TSOM_BitNumber              0x00
#define CSR_TSOM_BB                 (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TSOM_BitNumber * 4))

/* Alias word address of TEOM bit */
#define TEOM_BitNumber              0x01
#define CSR_TEOM_BB                 (PERIPH_BB_BASE + (CSR_OFFSET * 32) + (TEOM_BitNumber * 4))
  
#define CFGR_CLEAR_Mask            (uint8_t)(0xF3)        /* CFGR register Mask */
#define FLAG_Mask                  ((uint32_t)0x00FFFFFF) /* CEC FLAG mask */
 
/**
  * @}
  */ 


/** @defgroup CEC_Private_Macros
  * @{
  */ 

/**
  * @}
  */ 


/** @defgroup CEC_Private_Variables
  * @{
  */ 

/**
  * @}
  */ 


/** @defgroup CEC_Private_FunctionPrototypes
  * @{
  */
 
/**
  * @}
  */ 


/** @defgroup CEC_Private_Functions
  * @{
  */ 

/**
  * @brief  Deinitializes the CEC peripheral registers to their default reset 
  *         values.
  * @param  None
  * @retval None
  */
void CEC_DeInit(void)
{
  /* Enable CEC reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CEC, ENABLE);  
  /* Release CEC from reset state */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_CEC, DISABLE); 
}


/**
  * @brief  Initializes the CEC peripheral according to the specified 
  *         parameters in the CEC_InitStruct.
  * @param  CEC_InitStruct: pointer to an CEC_InitTypeDef structure that
  *         contains the configuration information for the specified
  *         CEC peripheral.
  * @retval None
  */
void CEC_Init(CEC_InitTypeDef* CEC_InitStruct)
{
  uint16_t tmpreg = 0;
 
  /* Check the parameters */
  assert_param(IS_CEC_BIT_TIMING_ERROR_MODE(CEC_InitStruct->CEC_BitTimingMode)); 
  assert_param(IS_CEC_BIT_PERIOD_ERROR_MODE(CEC_InitStruct->CEC_BitPeriodMode));
     
  /*---------------------------- CEC CFGR Configuration -----------------*/
  /* Get the CEC CFGR value */
  tmpreg = CEC->CFGR;
  
  /* Clear BTEM and BPEM bits */
  tmpreg &= CFGR_CLEAR_Mask;
  
  /* Configure CEC: Bit Timing Error and Bit Period Error */
  tmpreg |= (uint16_t)(CEC_InitStruct->CEC_BitTimingMode | CEC_InitStruct->CEC_BitPeriodMode);

  /* Write to CEC CFGR  register*/
  CEC->CFGR = tmpreg;
  
}

/**
  * @brief  Enables or disables the specified CEC peripheral.
  * @param  NewState: new state of the CEC peripheral. 
  *     This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CEC_Cmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CFGR_PE_BB = (uint32_t)NewState;

  if(NewState == DISABLE)
  {
    /* Wait until the PE bit is cleared by hardware (Idle Line detected) */
    while((CEC->CFGR & CEC_CFGR_PE) != (uint32_t)RESET)
    {
    }  
  }  
}

/**
  * @brief  Enables or disables the CEC interrupt.
  * @param  NewState: new state of the CEC interrupt.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CEC_ITConfig(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  *(__IO uint32_t *) CFGR_IE_BB = (uint32_t)NewState;
}

/**
  * @brief  Defines the Own Address of the CEC device.
  * @param  CEC_OwnAddress: The CEC own address
  * @retval None
  */
void CEC_OwnAddressConfig(uint8_t CEC_OwnAddress)
{
  /* Check the parameters */
  assert_param(IS_CEC_ADDRESS(CEC_OwnAddress));

  /* Set the CEC own address */
  CEC->OAR = CEC_OwnAddress;
}

/**
  * @brief  Sets the CEC prescaler value.
  * @param  CEC_Prescaler: CEC prescaler new value
  * @retval None
  */
void CEC_SetPrescaler(uint16_t CEC_Prescaler)
{
  /* Check the parameters */
  assert_param(IS_CEC_PRESCALER(CEC_Prescaler));

  /* Set the  Prescaler value*/
  CEC->PRES = CEC_Prescaler;
}

/**
  * @brief  Transmits single data through the CEC peripheral.
  * @param  Data: the data to transmit.
  * @retval None
  */
void CEC_SendDataByte(uint8_t Data)
{  
  /* Transmit Data */
  CEC->TXD = Data ;
}


/**
  * @brief  Returns the most recent received data by the CEC peripheral.
  * @param  None
  * @retval The received data.
  */
uint8_t CEC_ReceiveDataByte(void)
{
  /* Receive Data */
  return (uint8_t)(CEC->RXD);
}

/**
  * @brief  Starts a new message.
  * @param  None
  * @retval None
  */
void CEC_StartOfMessage(void)
{  
  /* Starts of new message */
  *(__IO uint32_t *) CSR_TSOM_BB = (uint32_t)0x1;
}

/**
  * @brief  Transmits message with or without an EOM bit.
  * @param  NewState: new state of the CEC Tx End Of Message. 
  *     This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CEC_EndOfMessageCmd(FunctionalState NewState)
{   
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  /* The data byte will be transmitted with or without an EOM bit*/
  *(__IO uint32_t *) CSR_TEOM_BB = (uint32_t)NewState;
}

/**
  * @brief  Gets the CEC flag status
  * @param  CEC_FLAG: specifies the CEC flag to check. 
  *   This parameter can be one of the following values:
  *     @arg CEC_FLAG_BTE: Bit Timing Error
  *     @arg CEC_FLAG_BPE: Bit Period Error
  *     @arg CEC_FLAG_RBTFE: Rx Block Transfer Finished Error
  *     @arg CEC_FLAG_SBE: Start Bit Error
  *     @arg CEC_FLAG_ACKE: Block Acknowledge Error
  *     @arg CEC_FLAG_LINE: Line Error
  *     @arg CEC_FLAG_TBTFE: Tx Block Transfer Finished Error
  *     @arg CEC_FLAG_TEOM: Tx End Of Message 
  *     @arg CEC_FLAG_TERR: Tx Error
  *     @arg CEC_FLAG_TBTRF: Tx Byte Transfer Request or Block Transfer Finished
  *     @arg CEC_FLAG_RSOM: Rx Start Of Message
  *     @arg CEC_FLAG_REOM: Rx End Of Message
  *     @arg CEC_FLAG_RERR: Rx Error
  *     @arg CEC_FLAG_RBTF: Rx Byte/Block Transfer Finished
  * @retval The new state of CEC_FLAG (SET or RESET)
  */
FlagStatus CEC_GetFlagStatus(uint32_t CEC_FLAG) 
{
  FlagStatus bitstatus = RESET;
  uint32_t cecreg = 0, cecbase = 0;
  
  /* Check the parameters */
  assert_param(IS_CEC_GET_FLAG(CEC_FLAG));
 
  /* Get the CEC peripheral base address */
  cecbase = (uint32_t)(CEC_BASE);
  
  /* Read flag register index */
  cecreg = CEC_FLAG >> 28;
  
  /* Get bit[23:0] of the flag */
  CEC_FLAG &= FLAG_Mask;
  
  if(cecreg != 0)
  {
    /* Flag in CEC ESR Register */
    CEC_FLAG = (uint32_t)(CEC_FLAG >> 16);
    
    /* Get the CEC ESR register address */
    cecbase += 0xC;
  }
  else
  {
    /* Get the CEC CSR register address */
    cecbase += 0x10;
  }
  
  if(((*(__IO uint32_t *)cecbase) & CEC_FLAG) != (uint32_t)RESET)
  {
    /* CEC_FLAG is set */
    bitstatus = SET;
  }
  else
  {
    /* CEC_FLAG is reset */
    bitstatus = RESET;
  }
  
  /* Return the CEC_FLAG status */
  return  bitstatus;
}

/**
  * @brief  Clears the CEC's pending flags.
  * @param  CEC_FLAG: specifies the flag to clear. 
  *   This parameter can be any combination of the following values:
  *     @arg CEC_FLAG_TERR: Tx Error
  *     @arg CEC_FLAG_TBTRF: Tx Byte Transfer Request or Block Transfer Finished
  *     @arg CEC_FLAG_RSOM: Rx Start Of Message
  *     @arg CEC_FLAG_REOM: Rx End Of Message
  *     @arg CEC_FLAG_RERR: Rx Error
  *     @arg CEC_FLAG_RBTF: Rx Byte/Block Transfer Finished
  * @retval None
  */
void CEC_ClearFlag(uint32_t CEC_FLAG)
{ 
  uint32_t tmp = 0x0;
  
  /* Check the parameters */
  assert_param(IS_CEC_CLEAR_FLAG(CEC_FLAG));

  tmp = CEC->CSR & 0x2;
       
  /* Clear the selected CEC flags */
  CEC->CSR &= (uint32_t)(((~(uint32_t)CEC_FLAG) & 0xFFFFFFFC) | tmp);
}

/**
  * @brief  Checks whether the specified CEC interrupt has occurred or not.
  * @param  CEC_IT: specifies the CEC interrupt source to check. 
  *   This parameter can be one of the following values:
  *     @arg CEC_IT_TERR: Tx Error
  *     @arg CEC_IT_TBTF: Tx Block Transfer Finished
  *     @arg CEC_IT_RERR: Rx Error
  *     @arg CEC_IT_RBTF: Rx Block Transfer Finished
  * @retval The new state of CEC_IT (SET or RESET).
  */
ITStatus CEC_GetITStatus(uint8_t CEC_IT)
{
  ITStatus bitstatus = RESET;
  uint32_t enablestatus = 0;
  
  /* Check the parameters */
   assert_param(IS_CEC_GET_IT(CEC_IT));
   
  /* Get the CEC IT enable bit status */
  enablestatus = (CEC->CFGR & (uint8_t)CEC_CFGR_IE) ;
  
  /* Check the status of the specified CEC interrupt */
  if (((CEC->CSR & CEC_IT) != (uint32_t)RESET) && enablestatus)
  {
    /* CEC_IT is set */
    bitstatus = SET;
  }
  else
  {
    /* CEC_IT is reset */
    bitstatus = RESET;
  }
  /* Return the CEC_IT status */
  return  bitstatus;
}

/**
  * @brief  Clears the CEC's interrupt pending bits.
  * @param  CEC_IT: specifies the CEC interrupt pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg CEC_IT_TERR: Tx Error
  *     @arg CEC_IT_TBTF: Tx Block Transfer Finished
  *     @arg CEC_IT_RERR: Rx Error
  *     @arg CEC_IT_RBTF: Rx Block Transfer Finished
  * @retval None
  */
void CEC_ClearITPendingBit(uint16_t CEC_IT)
{
  uint32_t tmp = 0x0;
  
  /* Check the parameters */
  assert_param(IS_CEC_GET_IT(CEC_IT));
  
  tmp = CEC->CSR & 0x2;
  
  /* Clear the selected CEC interrupt pending bits */
  CEC->CSR &= (uint32_t)(((~(uint32_t)CEC_IT) & 0xFFFFFFFC) | tmp);
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

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
