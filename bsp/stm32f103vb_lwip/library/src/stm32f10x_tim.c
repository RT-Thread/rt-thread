/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name          : stm32f10x_tim.c
* Author             : MCD Application Team
* Version            : V2.0.3Patch1
* Date               : 04/06/2009
* Description        : This file provides all the TIM firmware functions.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* ---------------------- TIM registers bit mask ------------------------ */
#define CR1_CEN_Set                 ((u16)0x0001)
#define CR1_CEN_Reset               ((u16)0x03FE)
#define CR1_UDIS_Set                ((u16)0x0002)
#define CR1_UDIS_Reset              ((u16)0x03FD)
#define CR1_URS_Set                 ((u16)0x0004)
#define CR1_URS_Reset               ((u16)0x03FB)
#define CR1_OPM_Reset               ((u16)0x03F7)
#define CR1_CounterMode_Mask        ((u16)0x038F)
#define CR1_ARPE_Set                ((u16)0x0080)
#define CR1_ARPE_Reset              ((u16)0x037F)
#define CR1_CKD_Mask                ((u16)0x00FF)

#define CR2_CCPC_Set                ((u16)0x0001)
#define CR2_CCPC_Reset              ((u16)0xFFFE)
#define CR2_CCUS_Set                ((u16)0x0004)
#define CR2_CCUS_Reset              ((u16)0xFFFB)
#define CR2_CCDS_Set                ((u16)0x0008)
#define CR2_CCDS_Reset              ((u16)0xFFF7)
#define CR2_MMS_Mask                ((u16)0xFF8F)
#define CR2_TI1S_Set                ((u16)0x0080)
#define CR2_TI1S_Reset              ((u16)0xFF7F)
#define CR2_OIS1_Reset              ((u16)0x7EFF)
#define CR2_OIS1N_Reset             ((u16)0x7DFF)
#define CR2_OIS2_Reset              ((u16)0x7BFF)
#define CR2_OIS2N_Reset             ((u16)0x77FF)
#define CR2_OIS3_Reset              ((u16)0x6FFF)
#define CR2_OIS3N_Reset             ((u16)0x5FFF)
#define CR2_OIS4_Reset              ((u16)0x3FFF)

#define SMCR_SMS_Mask               ((u16)0xFFF8)
#define SMCR_ETR_Mask               ((u16)0x00FF)
#define SMCR_TS_Mask                ((u16)0xFF8F)
#define SMCR_MSM_Reset              ((u16)0xFF7F)
#define SMCR_ECE_Set                ((u16)0x4000)

#define CCMR_CC13S_Mask             ((u16)0xFFFC)
#define CCMR_CC24S_Mask             ((u16)0xFCFF)
#define CCMR_TI13Direct_Set         ((u16)0x0001)
#define CCMR_TI24Direct_Set         ((u16)0x0100)
#define CCMR_OC13FE_Reset           ((u16)0xFFFB)
#define CCMR_OC24FE_Reset           ((u16)0xFBFF)
#define CCMR_OC13PE_Reset           ((u16)0xFFF7)
#define CCMR_OC24PE_Reset           ((u16)0xF7FF)
#define CCMR_OC13M_Mask             ((u16)0xFF8F)
#define CCMR_OC24M_Mask             ((u16)0x8FFF) 

#define CCMR_OC13CE_Reset           ((u16)0xFF7F)
#define CCMR_OC24CE_Reset           ((u16)0x7FFF)

#define CCMR_IC13PSC_Mask           ((u16)0xFFF3)
#define CCMR_IC24PSC_Mask           ((u16)0xF3FF)
#define CCMR_IC13F_Mask             ((u16)0xFF0F)
#define CCMR_IC24F_Mask             ((u16)0x0FFF)

#define CCMR_Offset                 ((u16)0x0018)
#define CCER_CCE_Set                ((u16)0x0001)
#define	CCER_CCNE_Set               ((u16)0x0004)

#define CCER_CC1P_Reset             ((u16)0xFFFD)
#define CCER_CC2P_Reset             ((u16)0xFFDF)
#define CCER_CC3P_Reset             ((u16)0xFDFF)
#define CCER_CC4P_Reset             ((u16)0xDFFF)

#define CCER_CC1NP_Reset            ((u16)0xFFF7)
#define CCER_CC2NP_Reset            ((u16)0xFF7F)
#define CCER_CC3NP_Reset            ((u16)0xF7FF)

#define CCER_CC1E_Set               ((u16)0x0001)
#define CCER_CC1E_Reset             ((u16)0xFFFE)

#define CCER_CC1NE_Reset            ((u16)0xFFFB)

#define CCER_CC2E_Set               ((u16)0x0010)
#define CCER_CC2E_Reset             ((u16)0xFFEF)

#define CCER_CC2NE_Reset            ((u16)0xFFBF)

#define CCER_CC3E_Set               ((u16)0x0100)
#define CCER_CC3E_Reset             ((u16)0xFEFF)

#define CCER_CC3NE_Reset            ((u16)0xFBFF)

#define CCER_CC4E_Set               ((u16)0x1000)
#define CCER_CC4E_Reset             ((u16)0xEFFF)

#define BDTR_MOE_Set                ((u16)0x8000)
#define BDTR_MOE_Reset              ((u16)0x7FFF)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void TI1_Config(TIM_TypeDef* TIMx, u16 TIM_ICPolarity, u16 TIM_ICSelection,
                       u16 TIM_ICFilter);
static void TI2_Config(TIM_TypeDef* TIMx, u16 TIM_ICPolarity, u16 TIM_ICSelection,
                       u16 TIM_ICFilter);
static void TI3_Config(TIM_TypeDef* TIMx, u16 TIM_ICPolarity, u16 TIM_ICSelection,
                       u16 TIM_ICFilter);
static void TI4_Config(TIM_TypeDef* TIMx, u16 TIM_ICPolarity, u16 TIM_ICSelection,
                       u16 TIM_ICFilter);
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : TIM_DeInit
* Description    : Deinitializes the TIMx peripheral registers to their default
*                  reset values.
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_DeInit(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx)); 
 
  switch (*(u32*)&TIMx)
  {
    case TIM1_BASE:
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, DISABLE);  
      break; 
      
    case TIM2_BASE:
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, DISABLE);
      break;
 
    case TIM3_BASE:
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3, DISABLE);
      break;
 
    case TIM4_BASE:
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4, DISABLE);
      break;
      
    case TIM5_BASE:
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM5, DISABLE);
      break;
      
    case TIM6_BASE:
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM6, DISABLE);
      break;
      
    case TIM7_BASE:
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, ENABLE);
      RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM7, DISABLE);
      break;
      
    case TIM8_BASE:
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, ENABLE);
      RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM8, DISABLE);  
      break; 
      
    default:
      break;
  }
}

/*******************************************************************************
* Function Name  : TIM_TimeBaseInit
* Description    : Initializes the TIMx Time Base Unit peripheral according to 
*                  the specified parameters in the TIM_TimeBaseInitStruct.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_TimeBaseInitStruct: pointer to a TIM_TimeBaseInitTypeDef
*                   structure that contains the configuration information for
*                   the specified TIM peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_COUNTER_MODE(TIM_TimeBaseInitStruct->TIM_CounterMode));
  assert_param(IS_TIM_CKD_DIV(TIM_TimeBaseInitStruct->TIM_ClockDivision));

  /* Select the Counter Mode and set the clock division */
  TIMx->CR1 &= CR1_CKD_Mask & CR1_CounterMode_Mask;
  TIMx->CR1 |= (u32)TIM_TimeBaseInitStruct->TIM_ClockDivision |
                TIM_TimeBaseInitStruct->TIM_CounterMode;
  /* Set the Autoreload value */
  TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period ;

  /* Set the Prescaler value */
  TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler;

  if (((*(u32*)&TIMx) == TIM1_BASE) || ((*(u32*)&TIMx) == TIM8_BASE))  
  {
    /* Set the Repetition Counter value */
    TIMx->RCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
  }        
  
  /* Generate an update event to reload the Prescaler value immediatly */
  TIMx->EGR = TIM_PSCReloadMode_Immediate;          
}

/*******************************************************************************
* Function Name  : TIM_OC1Init
* Description    : Initializes the TIMx Channel1 according to the specified
*                  parameters in the TIM_OCInitStruct.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
*                    that contains the configuration information for the specified
*                    TIM peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  u16 tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   

  /* Disable the Channel 1: Reset the CC1E Bit */
  TIMx->CCER &= CCER_CC1E_Reset;
  
  /* Get the TIMx CCER register value */
  tmpccer = TIMx->CCER;

  /* Get the TIMx CR2 register value */
  tmpcr2 =  TIMx->CR2;
  
  /* Get the TIMx CCMR1 register value */
  tmpccmrx = TIMx->CCMR1;
    
  /* Reset the Output Compare Mode Bits */
  tmpccmrx &= CCMR_OC13M_Mask;
  
  /* Select the Output Compare Mode */
  tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
  
  /* Reset the Output Polarity level */
  tmpccer &= CCER_CC1P_Reset;

  /* Set the Output Compare Polarity */
  tmpccer |= TIM_OCInitStruct->TIM_OCPolarity;
  
  /* Set the Output State */
  tmpccer |= TIM_OCInitStruct->TIM_OutputState;
  
  /* Set the Capture Compare Register value */
  TIMx->CCR1 = TIM_OCInitStruct->TIM_Pulse;
  
  if((*(u32*)&TIMx == TIM1_BASE) || (*(u32*)&TIMx == TIM8_BASE))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    
    /* Reset the Output N Polarity level */
    tmpccer &= CCER_CC1NP_Reset;

    /* Set the Output N Polarity */
    tmpccer |= TIM_OCInitStruct->TIM_OCNPolarity;

    /* Reset the Output N State */
    tmpccer &= CCER_CC1NE_Reset;
    
    /* Set the Output N State */
    tmpccer |= TIM_OCInitStruct->TIM_OutputNState;

    /* Reset the Ouput Compare and Output Compare N IDLE State */
    tmpcr2 &= CR2_OIS1_Reset;
    tmpcr2 &= CR2_OIS1N_Reset;

    /* Set the Output Idle state */
    tmpcr2 |= TIM_OCInitStruct->TIM_OCIdleState;

    /* Set the Output N Idle state */
    tmpcr2 |= TIM_OCInitStruct->TIM_OCNIdleState;
  }
  /* Write to TIMx CR2 */
  TIMx->CR2 = tmpcr2;
  
  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmrx;
  
  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TIM_OC2Init
* Description    : Initializes the TIMx Channel2 according to the specified
*                  parameters in the TIM_OCInitStruct.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
*                    that contains the configuration information for the specified
*                    TIM peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  u16 tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   

  /* Disable the Channel 2: Reset the CC2E Bit */
  TIMx->CCER &= CCER_CC2E_Reset;
  
  /* Get the TIMx CCER register value */  
  tmpccer = TIMx->CCER;

  /* Get the TIMx CR2 register value */
  tmpcr2 =  TIMx->CR2;
  
  /* Get the TIMx CCMR1 register value */
  tmpccmrx = TIMx->CCMR1;
    
  /* Reset the Output Compare Mode Bits */
  tmpccmrx &= CCMR_OC24M_Mask;
  
  /* Select the Output Compare Mode */
  tmpccmrx |= (u16)(TIM_OCInitStruct->TIM_OCMode << 8);
  
  /* Reset the Output Polarity level */
  tmpccer &= CCER_CC2P_Reset;

  /* Set the Output Compare Polarity */
  tmpccer |= (u16)(TIM_OCInitStruct->TIM_OCPolarity << 4);
  
  /* Set the Output State */
  tmpccer |= (u16)(TIM_OCInitStruct->TIM_OutputState << 4);
  
  /* Set the Capture Compare Register value */
  TIMx->CCR2 = TIM_OCInitStruct->TIM_Pulse;
  
  if((*(u32*)&TIMx == TIM1_BASE) || (*(u32*)&TIMx == TIM8_BASE))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    
    /* Reset the Output N Polarity level */
    tmpccer &= CCER_CC2NP_Reset;

    /* Set the Output N Polarity */
    tmpccer |= (u16)(TIM_OCInitStruct->TIM_OCNPolarity << 4);

    /* Reset the Output N State */
    tmpccer &= CCER_CC2NE_Reset;
    
    /* Set the Output N State */
    tmpccer |= (u16)(TIM_OCInitStruct->TIM_OutputNState << 4);

    /* Reset the Ouput Compare and Output Compare N IDLE State */
    tmpcr2 &= CR2_OIS2_Reset;
    tmpcr2 &= CR2_OIS2N_Reset;

    /* Set the Output Idle state */
    tmpcr2 |= (u16)(TIM_OCInitStruct->TIM_OCIdleState << 2);

    /* Set the Output N Idle state */
    tmpcr2 |= (u16)(TIM_OCInitStruct->TIM_OCNIdleState << 2);
  }

  /* Write to TIMx CR2 */
  TIMx->CR2 = tmpcr2;
  
  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmrx;
  
  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TIM_OC3Init
* Description    : Initializes the TIMx Channel3 according to the specified
*                  parameters in the TIM_OCInitStruct.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
*                    that contains the configuration information for the specified
*                    TIM peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  u16 tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   

  /* Disable the Channel 2: Reset the CC2E Bit */
  TIMx->CCER &= CCER_CC3E_Reset;
  
  /* Get the TIMx CCER register value */
  tmpccer = TIMx->CCER;

  /* Get the TIMx CR2 register value */
  tmpcr2 =  TIMx->CR2;
  
  /* Get the TIMx CCMR2 register value */
  tmpccmrx = TIMx->CCMR2;
    
  /* Reset the Output Compare Mode Bits */
  tmpccmrx &= CCMR_OC13M_Mask;
  
  /* Select the Output Compare Mode */
  tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
  
  /* Reset the Output Polarity level */
  tmpccer &= CCER_CC3P_Reset;

  /* Set the Output Compare Polarity */
  tmpccer |= (u16)(TIM_OCInitStruct->TIM_OCPolarity << 8);
  
  /* Set the Output State */
  tmpccer |= (u16)(TIM_OCInitStruct->TIM_OutputState << 8);
  
  /* Set the Capture Compare Register value */
  TIMx->CCR3 = TIM_OCInitStruct->TIM_Pulse;
  
  if((*(u32*)&TIMx == TIM1_BASE) || (*(u32*)&TIMx == TIM8_BASE))
  {
    assert_param(IS_TIM_OUTPUTN_STATE(TIM_OCInitStruct->TIM_OutputNState));
    assert_param(IS_TIM_OCN_POLARITY(TIM_OCInitStruct->TIM_OCNPolarity));
    assert_param(IS_TIM_OCNIDLE_STATE(TIM_OCInitStruct->TIM_OCNIdleState));
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));
    
    /* Reset the Output N Polarity level */
    tmpccer &= CCER_CC3NP_Reset;

    /* Set the Output N Polarity */
    tmpccer |= (u16)(TIM_OCInitStruct->TIM_OCNPolarity << 8);

    /* Reset the Output N State */
    tmpccer &= CCER_CC3NE_Reset;
    
    /* Set the Output N State */
    tmpccer |= (u16)(TIM_OCInitStruct->TIM_OutputNState << 8);

    /* Reset the Ouput Compare and Output Compare N IDLE State */
    tmpcr2 &= CR2_OIS3_Reset;
    tmpcr2 &= CR2_OIS3N_Reset;

    /* Set the Output Idle state */
    tmpcr2 |= (u16)(TIM_OCInitStruct->TIM_OCIdleState << 4);

    /* Set the Output N Idle state */
    tmpcr2 |= (u16)(TIM_OCInitStruct->TIM_OCNIdleState << 4);
  }

  /* Write to TIMx CR2 */
  TIMx->CR2 = tmpcr2;
  
  /* Write to TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmrx;
  
  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TIM_OC4Init
* Description    : Initializes the TIMx Channel4 according to the specified
*                  parameters in the TIM_OCInitStruct.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCInitStruct: pointer to a TIM_OCInitTypeDef structure
*                    that contains the configuration information for the specified
*                    TIM peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  u16 tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;
   
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));   

  /* Disable the Channel 2: Reset the CC4E Bit */
  TIMx->CCER &= CCER_CC4E_Reset;
  
  /* Get the TIMx CCER register value */
  tmpccer = TIMx->CCER;

  /* Get the TIMx CR2 register value */
  tmpcr2 =  TIMx->CR2;
  
  /* Get the TIMx CCMR2 register value */
  tmpccmrx = TIMx->CCMR2;
    
  /* Reset the Output Compare Mode Bits */
  tmpccmrx &= CCMR_OC24M_Mask;
  
  /* Select the Output Compare Mode */
  tmpccmrx |= (u16)(TIM_OCInitStruct->TIM_OCMode << 8);
  
  /* Reset the Output Polarity level */
  tmpccer &= CCER_CC4P_Reset;

  /* Set the Output Compare Polarity */
  tmpccer |= (u16)(TIM_OCInitStruct->TIM_OCPolarity << 12);
  
  /* Set the Output State */
  tmpccer |= (u16)(TIM_OCInitStruct->TIM_OutputState << 12);
  
  /* Set the Capture Compare Register value */
  TIMx->CCR4 = TIM_OCInitStruct->TIM_Pulse;
  
  if((*(u32*)&TIMx == TIM1_BASE) || (*(u32*)&TIMx == TIM8_BASE))
  {
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

    /* Reset the Ouput Compare IDLE State */
    tmpcr2 &= CR2_OIS4_Reset;

    /* Set the Output Idle state */
    tmpcr2 |= (u16)(TIM_OCInitStruct->TIM_OCIdleState << 6);
  }

  /* Write to TIMx CR2 */
  TIMx->CR2 = tmpcr2;
  
  /* Write to TIMx CCMR2 */  
  TIMx->CCMR2 = tmpccmrx;
  
  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TIM_ICInit
* Description    : Initializes the TIM peripheral according to the specified
*                  parameters in the TIM_ICInitStruct.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure
*                    that contains the configuration information for the specified
*                    TIM peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ICInit(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_CHANNEL(TIM_ICInitStruct->TIM_Channel));
  assert_param(IS_TIM_IC_POLARITY(TIM_ICInitStruct->TIM_ICPolarity));
  assert_param(IS_TIM_IC_SELECTION(TIM_ICInitStruct->TIM_ICSelection));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICInitStruct->TIM_ICPrescaler));
  assert_param(IS_TIM_IC_FILTER(TIM_ICInitStruct->TIM_ICFilter));
  
  if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_2)
  {
    /* TI2 Configuration */
    TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_3)
  {
    /* TI3 Configuration */
    TI3_Config(TIMx,  TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM_SetIC3Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else
  {
    /* TI4 Configuration */
    TI4_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
               TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM_SetIC4Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
}

/*******************************************************************************
* Function Name  : TIM_PWMIConfig
* Description    : Configures the TIM peripheral according to the specified
*                  parameters in the TIM_ICInitStruct to measure an external PWM
*                  signal.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ICInitStruct: pointer to a TIM_ICInitTypeDef structure
*                    that contains the configuration information for the specified
*                    TIM peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_PWMIConfig(TIM_TypeDef* TIMx, TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  u16 icoppositepolarity = TIM_ICPolarity_Rising;
  u16 icoppositeselection = TIM_ICSelection_DirectTI;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));

  /* Select the Opposite Input Polarity */
  if (TIM_ICInitStruct->TIM_ICPolarity == TIM_ICPolarity_Rising)
  {
    icoppositepolarity = TIM_ICPolarity_Falling;
  }
  else
  {
    icoppositepolarity = TIM_ICPolarity_Rising;
  }

  /* Select the Opposite Input */
  if (TIM_ICInitStruct->TIM_ICSelection == TIM_ICSelection_DirectTI)
  {
    icoppositeselection = TIM_ICSelection_IndirectTI;
  }
  else
  {
    icoppositeselection = TIM_ICSelection_DirectTI;
  }

  if (TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);

    /* TI2 Configuration */
    TI2_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
  else
  { 
    /* TI2 Configuration */
    TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
               TIM_ICInitStruct->TIM_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);

    /* TI1 Configuration */
    TI1_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);

    /* Set the Input Capture Prescaler value */
    TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
  }
}

/*******************************************************************************
* Function Name  : TIM_BDTRConfig
* Description    : Configures the: Break feature, dead time, Lock level, the OSSI,
*                  the OSSR State and the AOE(automatic output enable).
* Input          :- TIMx: where x can be  1 or 8 to select the TIM 
*                 - TIM_BDTRInitStruct: pointer to a TIM_BDTRInitTypeDef
*                    structure that contains the BDTR Register configuration
*                    information for the TIM peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_BDTRConfig(TIM_TypeDef* TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct)
{
  /* Check the parameters */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_OSSR_STATE(TIM_BDTRInitStruct->TIM_OSSRState));
  assert_param(IS_TIM_OSSI_STATE(TIM_BDTRInitStruct->TIM_OSSIState));
  assert_param(IS_TIM_LOCK_LEVEL(TIM_BDTRInitStruct->TIM_LOCKLevel));
  assert_param(IS_TIM_BREAK_STATE(TIM_BDTRInitStruct->TIM_Break));
  assert_param(IS_TIM_BREAK_POLARITY(TIM_BDTRInitStruct->TIM_BreakPolarity));
  assert_param(IS_TIM_AUTOMATIC_OUTPUT_STATE(TIM_BDTRInitStruct->TIM_AutomaticOutput));

  /* Set the Lock level, the Break enable Bit and the Ploarity, the OSSR State,
     the OSSI State, the dead time value and the Automatic Output Enable Bit */

  TIMx->BDTR = (u32)TIM_BDTRInitStruct->TIM_OSSRState | TIM_BDTRInitStruct->TIM_OSSIState |
             TIM_BDTRInitStruct->TIM_LOCKLevel | TIM_BDTRInitStruct->TIM_DeadTime |
             TIM_BDTRInitStruct->TIM_Break | TIM_BDTRInitStruct->TIM_BreakPolarity |
             TIM_BDTRInitStruct->TIM_AutomaticOutput;

}

/*******************************************************************************
* Function Name  : TIM_TimeBaseStructInit
* Description    : Fills each TIM_TimeBaseInitStruct member with its default value.
* Input          : - TIM_TimeBaseInitStruct : pointer to a TIM_TimeBaseInitTypeDef
*                    structure which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
  /* Set the default configuration */
  TIM_TimeBaseInitStruct->TIM_Period = 0xFFFF;
  TIM_TimeBaseInitStruct->TIM_Prescaler = 0x0000;
  TIM_TimeBaseInitStruct->TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct->TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct->TIM_RepetitionCounter = 0x0000;
}

/*******************************************************************************
* Function Name  : TIM_OCStructInit
* Description    : Fills each TIM_OCInitStruct member with its default value.
* Input          : - TIM_OCInitStruct : pointer to a TIM_OCInitTypeDef structure
*                    which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  /* Set the default configuration */
  TIM_OCInitStruct->TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStruct->TIM_OutputState = TIM_OutputState_Disable;
  TIM_OCInitStruct->TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStruct->TIM_Pulse = 0x0000;
  TIM_OCInitStruct->TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct->TIM_OCNPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct->TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStruct->TIM_OCNIdleState = TIM_OCNIdleState_Reset;
}

/*******************************************************************************
* Function Name  : TIM_ICStructInit
* Description    : Fills each TIM_ICInitStruct member with its default value.
* Input          : - TIM_ICInitStruct : pointer to a TIM_ICInitTypeDef structure
*                    which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ICStructInit(TIM_ICInitTypeDef* TIM_ICInitStruct)
{
  /* Set the default configuration */
  TIM_ICInitStruct->TIM_Channel = TIM_Channel_1;
  TIM_ICInitStruct->TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStruct->TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct->TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStruct->TIM_ICFilter = 0x00;
}

/*******************************************************************************
* Function Name  : TIM_BDTRStructInit
* Description    : Fills each TIM_BDTRInitStruct member with its default value.
* Input          : - TIM_BDTRInitStruct : pointer to a TIM_BDTRInitTypeDef
*                    structure which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef* TIM_BDTRInitStruct)
{
  /* Set the default configuration */
  TIM_BDTRInitStruct->TIM_OSSRState = TIM_OSSRState_Disable;
  TIM_BDTRInitStruct->TIM_OSSIState = TIM_OSSIState_Disable;
  TIM_BDTRInitStruct->TIM_LOCKLevel = TIM_LOCKLevel_OFF;
  TIM_BDTRInitStruct->TIM_DeadTime = 0x00;
  TIM_BDTRInitStruct->TIM_Break = TIM_Break_Disable;
  TIM_BDTRInitStruct->TIM_BreakPolarity = TIM_BreakPolarity_Low;
  TIM_BDTRInitStruct->TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
}

/*******************************************************************************
* Function Name  : TIM_Cmd
* Description    : Enables or disables the specified TIM peripheral.
* Input          : - TIMx: where x can be 1 to 8 to select the TIMx peripheral.
*                  - NewState: new state of the TIMx peripheral.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the TIM Counter */
    TIMx->CR1 |= CR1_CEN_Set;
  }
  else
  {
    /* Disable the TIM Counter */
    TIMx->CR1 &= CR1_CEN_Reset;
  }
}

/*******************************************************************************
* Function Name  : TIM_CtrlPWMOutputs
* Description    : Enables or disables the TIM peripheral Main Outputs.
* Input          :- TIMx: where x can be 1 or 8 to select the TIMx peripheral.
*                 - NewState: new state of the TIM peripheral Main Outputs.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the TIM Main Output */
    TIMx->BDTR |= BDTR_MOE_Set;
  }
  else
  {
    /* Disable the TIM Main Output */
    TIMx->BDTR &= BDTR_MOE_Reset;
  }  
}

/*******************************************************************************
* Function Name  : TIM_ITConfig
* Description    : Enables or disables the specified TIM interrupts.
* Input          : - TIMx: where x can be 1 to 8 to select the TIMx peripheral.
*                  - TIM_IT: specifies the TIM interrupts sources to be enabled
*                    or disabled.
*                    This parameter can be any combination of the following values:
*                       - TIM_IT_Update: TIM update Interrupt source
*                       - TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
*                       - TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
*                       - TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
*                       - TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
*                       - TIM_IT_COM: TIM Commutation Interrupt source
*                       - TIM_IT_Trigger: TIM Trigger Interrupt source
*                       - TIM_IT_Break: TIM Break Interrupt source
*                  - NewState: new state of the TIM interrupts.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ITConfig(TIM_TypeDef* TIMx, u16 TIM_IT, FunctionalState NewState)
{  
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_IT(TIM_IT));
  assert_param(IS_TIM_PERIPH_IT((TIMx), (TIM_IT)));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TIMx->DIER |= TIM_IT;
  }
  else
  {
    /* Disable the Interrupt sources */
    TIMx->DIER &= (u16)~TIM_IT;
  }
}

/*******************************************************************************
* Function Name  : TIM_GenerateEvent
* Description    : Configures the TIMx event to be generate by software.
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
*                  - TIM_EventSource: specifies the event source.
*                    This parameter can be one or more of the following values:	   
*                       - TIM_EventSource_Update: Timer update Event source
*                       - TIM_EventSource_CC1: Timer Capture Compare 1 Event source
*                       - TIM_EventSource_CC2: Timer Capture Compare 2 Event source
*                       - TIM_EventSource_CC3: Timer Capture Compare 3 Event source
*                       - TIM_EventSource_CC4: Timer Capture Compare 4 Event source
*                       - TIM_EventSource_Trigger: Timer Trigger Event source
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_GenerateEvent(TIM_TypeDef* TIMx, u16 TIM_EventSource)
{ 
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_EVENT_SOURCE(TIM_EventSource));
  assert_param(IS_TIM_PERIPH_EVENT((TIMx), (TIM_EventSource)));

  /* Set the event sources */
  TIMx->EGR = TIM_EventSource;
}

/*******************************************************************************
* Function Name  : TIM_DMAConfig
* Description    : Configures the TIMx’s DMA interface.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_DMABase: DMA Base address.
*                    This parameter can be one of the following values:
*                       - TIM_DMABase_CR, TIM_DMABase_CR2, TIM_DMABase_SMCR,
*                         TIM_DMABase_DIER, TIM1_DMABase_SR, TIM_DMABase_EGR,
*                         TIM_DMABase_CCMR1, TIM_DMABase_CCMR2, TIM_DMABase_CCER,
*                         TIM_DMABase_CNT, TIM_DMABase_PSC, TIM_DMABase_ARR,
*                         TIM_DMABase_RCR, TIM_DMABase_CCR1, TIM_DMABase_CCR2,
*                         TIM_DMABase_CCR3, TIM_DMABase_CCR4, TIM_DMABase_BDTR,
*                         TIM_DMABase_DCR.
*                   - TIM_DMABurstLength: DMA Burst length.
*                     This parameter can be one value between:
*                     TIM_DMABurstLength_1Byte and TIM_DMABurstLength_18Bytes.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_DMAConfig(TIM_TypeDef* TIMx, u16 TIM_DMABase, u16 TIM_DMABurstLength)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_DMA_BASE(TIM_DMABase));
  assert_param(IS_TIM_DMA_LENGTH(TIM_DMABurstLength));

  /* Set the DMA Base and the DMA Burst Length */
  TIMx->DCR = TIM_DMABase | TIM_DMABurstLength;
}

/*******************************************************************************
* Function Name  : TIM_DMACmd
* Description    : Enables or disables the TIMx’s DMA Requests.
* Input          : - TIMx: where x can be  1 to 8 to select the TIM peripheral. 
*                  - TIM_DMASources: specifies the DMA Request sources.
*                    This parameter can be any combination of the following values:
*                       - TIM_DMA_Update: TIM update Interrupt source
*                       - TIM_DMA_CC1: TIM Capture Compare 1 DMA source
*                       - TIM_DMA_CC2: TIM Capture Compare 2 DMA source
*                       - TIM_DMA_CC3: TIM Capture Compare 3 DMA source
*                       - TIM_DMA_CC4: TIM Capture Compare 4 DMA source
*                       - TIM_DMA_COM: TIM Commutation DMA source
*                       - TIM_DMA_Trigger: TIM Trigger DMA source
*                  - NewState: new state of the DMA Request sources.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_DMACmd(TIM_TypeDef* TIMx, u16 TIM_DMASource, FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_DMA_SOURCE(TIM_DMASource));
  assert_param(IS_TIM_PERIPH_DMA(TIMx, TIM_DMASource));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the DMA sources */
    TIMx->DIER |= TIM_DMASource; 
  }
  else
  {
    /* Disable the DMA sources */
    TIMx->DIER &= (u16)~TIM_DMASource;
  }
}

/*******************************************************************************
* Function Name  : TIM_InternalClockConfig
* Description    : Configures the TIMx interrnal Clock
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_InternalClockConfig(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));

  /* Disable slave mode to clock the prescaler directly with the internal clock */
  TIMx->SMCR &=  SMCR_SMS_Mask;
}
/*******************************************************************************
* Function Name  : TIM_ITRxExternalClockConfig
* Description    : Configures the TIMx Internal Trigger as External Clock
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ITRSource: Trigger source.
*                    This parameter can be one of the following values:
*                       - TIM_TS_ITR0: Internal Trigger 0
*                       - TIM_TS_ITR1: Internal Trigger 1
*                       - TIM_TS_ITR2: Internal Trigger 2
*                       - TIM_TS_ITR3: Internal Trigger 3
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, u16 TIM_InputTriggerSource)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_INTERNAL_TRIGGER_SELECTION(TIM_InputTriggerSource));

  /* Select the Internal Trigger */
  TIM_SelectInputTrigger(TIMx, TIM_InputTriggerSource);

  /* Select the External clock mode1 */
  TIMx->SMCR |= TIM_SlaveMode_External1;
}
/*******************************************************************************
* Function Name  : TIM_TIxExternalClockConfig
* Description    : Configures the TIMx Trigger as External Clock
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_TIxExternalCLKSource: Trigger source.
*                    This parameter can be one of the following values:
*                       - TIM_TIxExternalCLK1Source_TI1ED: TI1 Edge Detector
*                       - TIM_TIxExternalCLK1Source_TI1: Filtered Timer Input 1
*                       - TIM_TIxExternalCLK1Source_TI2: Filtered Timer Input 2
*                  - TIM_ICPolarity: specifies the TIx Polarity.
*                    This parameter can be:
*                       - TIM_ICPolarity_Rising
*                       - TIM_ICPolarity_Falling
*                   - ICFilter : specifies the filter value.
*                     This parameter must be a value between 0x0 and 0xF.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, u16 TIM_TIxExternalCLKSource,
                                u16 TIM_ICPolarity, u16 ICFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_TIXCLK_SOURCE(TIM_TIxExternalCLKSource));
  assert_param(IS_TIM_IC_POLARITY(TIM_ICPolarity));
  assert_param(IS_TIM_IC_FILTER(ICFilter));

  /* Configure the Timer Input Clock Source */
  if (TIM_TIxExternalCLKSource == TIM_TIxExternalCLK1Source_TI2)
  {
    TI2_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }
  else
  {
    TI1_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
  }

  /* Select the Trigger source */
  TIM_SelectInputTrigger(TIMx, TIM_TIxExternalCLKSource);

  /* Select the External clock mode1 */
  TIMx->SMCR |= TIM_SlaveMode_External1;
}

/*******************************************************************************
* Function Name  : TIM_ETRClockMode1Config
* Description    : Configures the External clock Mode1
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ExtTRGPrescaler: The external Trigger Prescaler.
*                    It can be one of the following values:
*                       - TIM_ExtTRGPSC_OFF
*                       - TIM_ExtTRGPSC_DIV2
*                       - TIM_ExtTRGPSC_DIV4
*                       - TIM_ExtTRGPSC_DIV8.
*                  - TIM_ExtTRGPolarity: The external Trigger Polarity.
*                    It can be one of the following values:
*                       - TIM_ExtTRGPolarity_Inverted
*                       - TIM_ExtTRGPolarity_NonInverted
*                  - ExtTRGFilter: External Trigger Filter.
*                    This parameter must be a value between 0x00 and 0x0F
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, u16 TIM_ExtTRGPolarity,
                             u16 ExtTRGFilter)
{
  u16 tmpsmcr = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));

  /* Configure the ETR Clock source */
  TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
  
  /* Get the TIMx SMCR register value */
  tmpsmcr = TIMx->SMCR;

  /* Reset the SMS Bits */
  tmpsmcr &= SMCR_SMS_Mask;
  /* Select the External clock mode1 */
  tmpsmcr |= TIM_SlaveMode_External1;

  /* Select the Trigger selection : ETRF */
  tmpsmcr &= SMCR_TS_Mask;
  tmpsmcr |= TIM_TS_ETRF;

  /* Write to TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/*******************************************************************************
* Function Name  : TIM_ETRClockMode2Config
* Description    : Configures the External clock Mode2
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ExtTRGPrescaler: The external Trigger Prescaler.
*                    It can be one of the following values:
*                       - TIM_ExtTRGPSC_OFF
*                       - TIM_ExtTRGPSC_DIV2
*                       - TIM_ExtTRGPSC_DIV4
*                       - TIM_ExtTRGPSC_DIV8
*                  - TIM_ExtTRGPolarity: The external Trigger Polarity.
*                    It can be one of the following values:
*                       - TIM_ExtTRGPolarity_Inverted
*                       - TIM_ExtTRGPolarity_NonInverted
*                  - ExtTRGFilter: External Trigger Filter.
*                    This parameter must be a value between 0x00 and 0x0F
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, 
                             u16 TIM_ExtTRGPolarity, u16 ExtTRGFilter)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));

  /* Configure the ETR Clock source */
  TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);

  /* Enable the External clock mode2 */
  TIMx->SMCR |= SMCR_ECE_Set;
}

/*******************************************************************************
* Function Name  : TIM_ETRConfig
* Description    : Configures the TIMx External Trigger (ETR).
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ExtTRGPrescaler: The external Trigger Prescaler.
*                    This parameter can be one of the following values:
*                       - TIM_ExtTRGPSC_OFF
*                       - TIM_ExtTRGPSC_DIV2
*                       - TIM_ExtTRGPSC_DIV4
*                       - TIM_ExtTRGPSC_DIV8
*                  - TIM_ExtTRGPolarity: The external Trigger Polarity.
*                    This parameter can be one of the following values:
*                       - TIM_ExtTRGPolarity_Inverted
*                       - TIM_ExtTRGPolarity_NonInverted
*                  - ExtTRGFilter: External Trigger Filter.
*                    This parameter must be a value between 0x00 and 0x0F.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ETRConfig(TIM_TypeDef* TIMx, u16 TIM_ExtTRGPrescaler, u16 TIM_ExtTRGPolarity,
                   u16 ExtTRGFilter)
{
  u16 tmpsmcr = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_EXT_PRESCALER(TIM_ExtTRGPrescaler));
  assert_param(IS_TIM_EXT_POLARITY(TIM_ExtTRGPolarity));
  assert_param(IS_TIM_EXT_FILTER(ExtTRGFilter));

  tmpsmcr = TIMx->SMCR;

  /* Reset the ETR Bits */
  tmpsmcr &= SMCR_ETR_Mask;

  /* Set the Prescaler, the Filter value and the Polarity */
  tmpsmcr |= TIM_ExtTRGPrescaler | TIM_ExtTRGPolarity | (u16)(ExtTRGFilter << 8);

  /* Write to TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/*******************************************************************************
* Function Name  : TIM_PrescalerConfig
* Description    : Configures the TIMx Prescaler.
* Input          : - TIMx: where x can be  1 to 8 to select the TIM peripheral.
*                  - Prescaler: specifies the Prescaler Register value
*                  - TIM_PSCReloadMode: specifies the TIM Prescaler Reload mode
*                    This parameter can be one of the following values:
*                       - TIM_PSCReloadMode_Update: The Prescaler is loaded at
*                         the update event.
*                       - TIM_PSCReloadMode_Immediate: The Prescaler is loaded
*                         immediatly.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, u16 Prescaler, u16 TIM_PSCReloadMode)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_PRESCALER_RELOAD(TIM_PSCReloadMode));

  /* Set the Prescaler value */
  TIMx->PSC = Prescaler;

  /* Set or reset the UG Bit */
  TIMx->EGR = TIM_PSCReloadMode;
}

/*******************************************************************************
* Function Name  : TIM_CounterModeConfig
* Description    : Specifies the TIMx Counter Mode to be used.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_CounterMode: specifies the Counter Mode to be used
*                    This parameter can be one of the following values:
*                       - TIM_CounterMode_Up: TIM Up Counting Mode
*                       - TIM_CounterMode_Down: TIM Down Counting Mode
*                       - TIM_CounterMode_CenterAligned1: TIM Center Aligned Mode1
*                       - TIM_CounterMode_CenterAligned2: TIM Center Aligned Mode2
*                       - TIM_CounterMode_CenterAligned3: TIM Center Aligned Mode3
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, u16 TIM_CounterMode)
{
  u16 tmpcr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_COUNTER_MODE(TIM_CounterMode));

  tmpcr1 = TIMx->CR1;

  /* Reset the CMS and DIR Bits */
  tmpcr1 &= CR1_CounterMode_Mask;

  /* Set the Counter Mode */
  tmpcr1 |= TIM_CounterMode;

  /* Write to TIMx CR1 register */
  TIMx->CR1 = tmpcr1;
}

/*******************************************************************************
* Function Name  : TIM_SelectInputTrigger
* Description    : Selects the Input Trigger source
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_InputTriggerSource: The Input Trigger source.
*                    This parameter can be one of the following values:
*                       - TIM_TS_ITR0: Internal Trigger 0
*                       - TIM_TS_ITR1: Internal Trigger 1
*                       - TIM_TS_ITR2: Internal Trigger 2
*                       - TIM_TS_ITR3: Internal Trigger 3
*                       - TIM_TS_TI1F_ED: TI1 Edge Detector
*                       - TIM_TS_TI1FP1: Filtered Timer Input 1
*                       - TIM_TS_TI2FP2: Filtered Timer Input 2
*                       - TIM_TS_ETRF: External Trigger input
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SelectInputTrigger(TIM_TypeDef* TIMx, u16 TIM_InputTriggerSource)
{
  u16 tmpsmcr = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_TRIGGER_SELECTION(TIM_InputTriggerSource));

  /* Get the TIMx SMCR register value */
  tmpsmcr = TIMx->SMCR;

  /* Reset the TS Bits */
  tmpsmcr &= SMCR_TS_Mask;

  /* Set the Input Trigger source */
  tmpsmcr |= TIM_InputTriggerSource;

  /* Write to TIMx SMCR */
  TIMx->SMCR = tmpsmcr;
}

/*******************************************************************************
* Function Name  : TIM_EncoderInterfaceConfig
* Description    : Configures the TIMx Encoder Interface.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_EncoderMode: specifies the TIMx Encoder Mode.
*                    This parameter can be one of the following values:
*                       - TIM_EncoderMode_TI1: Counter counts on TI1FP1 edge
*                         depending on TI2FP2 level.
*                       - TIM_EncoderMode_TI2: Counter counts on TI2FP2 edge
*                         depending on TI1FP1 level.
*                       - TIM_EncoderMode_TI12: Counter counts on both TI1FP1 and
*                         TI2FP2 edges depending on the level of the other input.
*                  - TIM_IC1Polarity: specifies the IC1 Polarity
*                    This parmeter can be one of the following values:
*                        - TIM_ICPolarity_Falling: IC Falling edge.
*                        - TIM_ICPolarity_Rising: IC Rising edge.
*                  - TIM_IC2Polarity: specifies the IC2 Polarity
*                    This parmeter can be one of the following values:
*                        - TIM_ICPolarity_Falling: IC Falling edge.
*                        - TIM_ICPolarity_Rising: IC Rising edge.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_EncoderInterfaceConfig(TIM_TypeDef* TIMx, u16 TIM_EncoderMode,
                                u16 TIM_IC1Polarity, u16 TIM_IC2Polarity)
{
  u16 tmpsmcr = 0;
  u16 tmpccmr1 = 0;
  u16 tmpccer = 0;
    
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_ENCODER_MODE(TIM_EncoderMode));
  assert_param(IS_TIM_IC_POLARITY(TIM_IC1Polarity));
  assert_param(IS_TIM_IC_POLARITY(TIM_IC2Polarity));

  /* Get the TIMx SMCR register value */
  tmpsmcr = TIMx->SMCR;

  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIMx->CCMR1;

  /* Get the TIMx CCER register value */
  tmpccer = TIMx->CCER;

  /* Set the encoder Mode */
  tmpsmcr &= SMCR_SMS_Mask;
  tmpsmcr |= TIM_EncoderMode;

  /* Select the Capture Compare 1 and the Capture Compare 2 as input */
  tmpccmr1 &= CCMR_CC13S_Mask & CCMR_CC24S_Mask;
  tmpccmr1 |= CCMR_TI13Direct_Set | CCMR_TI24Direct_Set;

  /* Set the TI1 and the TI2 Polarities */
  tmpccer &= CCER_CC1P_Reset & CCER_CC2P_Reset;
  tmpccer |= (TIM_IC1Polarity | (u16)(TIM_IC2Polarity << 4));

  /* Write to TIMx SMCR */
  TIMx->SMCR = tmpsmcr;

  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;

  /* Write to TIMx CCER */
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TIM_ForcedOC1Config
* Description    : Forces the TIMx output 1 waveform to active or inactive level.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ForcedAction: specifies the forced Action to be set to
*                    the output waveform.
*                    This parameter can be one of the following values:
*                       - TIM_ForcedAction_Active: Force active level on OC1REF
*                       - TIM_ForcedAction_InActive: Force inactive level on
*                         OC1REF.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ForcedOC1Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction)
{
  u16 tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));

  tmpccmr1 = TIMx->CCMR1;

  /* Reset the OC1M Bits */
  tmpccmr1 &= CCMR_OC13M_Mask;

  /* Configure The Forced output Mode */
  tmpccmr1 |= TIM_ForcedAction;

  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/*******************************************************************************
* Function Name  : TIM_ForcedOC2Config
* Description    : Forces the TIMx output 2 waveform to active or inactive level.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ForcedAction: specifies the forced Action to be set to
*                    the output waveform.
*                    This parameter can be one of the following values:
*                       - TIM_ForcedAction_Active: Force active level on OC2REF
*                       - TIM_ForcedAction_InActive: Force inactive level on
*                         OC2REF.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ForcedOC2Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction)
{
  u16 tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));

  tmpccmr1 = TIMx->CCMR1;

  /* Reset the OC2M Bits */
  tmpccmr1 &= CCMR_OC24M_Mask;

  /* Configure The Forced output Mode */
  tmpccmr1 |= (u16)(TIM_ForcedAction << 8);

  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/*******************************************************************************
* Function Name  : TIM_ForcedOC3Config
* Description    : Forces the TIMx output 3 waveform to active or inactive level.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ForcedAction: specifies the forced Action to be set to
*                    the output waveform.
*                    This parameter can be one of the following values:
*                       - TIM_ForcedAction_Active: Force active level on OC3REF
*                       - TIM_ForcedAction_InActive: Force inactive level on
*                         OC3REF.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ForcedOC3Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction)
{
  u16 tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));

  tmpccmr2 = TIMx->CCMR2;

  /* Reset the OC1M Bits */
  tmpccmr2 &= CCMR_OC13M_Mask;

  /* Configure The Forced output Mode */
  tmpccmr2 |= TIM_ForcedAction;

  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/*******************************************************************************
* Function Name  : TIM_ForcedOC4Config
* Description    : Forces the TIMx output 4 waveform to active or inactive level.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ForcedAction: specifies the forced Action to be set to
*                    the output waveform.
*                    This parameter can be one of the following values:
*                       - TIM_ForcedAction_Active: Force active level on OC4REF
*                       - TIM_ForcedAction_InActive: Force inactive level on
*                         OC4REF.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ForcedOC4Config(TIM_TypeDef* TIMx, u16 TIM_ForcedAction)
{
  u16 tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_FORCED_ACTION(TIM_ForcedAction));
  tmpccmr2 = TIMx->CCMR2;

  /* Reset the OC2M Bits */
  tmpccmr2 &= CCMR_OC24M_Mask;

  /* Configure The Forced output Mode */
  tmpccmr2 |= (u16)(TIM_ForcedAction << 8);

  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/*******************************************************************************
* Function Name  : TIM_ARRPreloadConfig
* Description    : Enables or disables TIMx peripheral Preload register on ARR.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - NewState: new state of the TIMx peripheral Preload register
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the ARR Preload Bit */
    TIMx->CR1 |= CR1_ARPE_Set;
  }
  else
  {
    /* Reset the ARR Preload Bit */
    TIMx->CR1 &= CR1_ARPE_Reset;
  }
}

/*******************************************************************************
* Function Name  : TIM_SelectCOM
* Description    : Selects the TIM peripheral Commutation event.
* Input          :- TIMx: where x can be  1 or 8 to select the TIMx peripheral
*                 - NewState: new state of the Commutation event.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SelectCOM(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the COM Bit */
    TIMx->CR2 |= CR2_CCUS_Set;
  }
  else
  {
    /* Reset the COM Bit */
    TIMx->CR2 &= CR2_CCUS_Reset;
  }
}

/*******************************************************************************
* Function Name  : TIM_SelectCCDMA
* Description    : Selects the TIMx peripheral Capture Compare DMA source.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - NewState: new state of the Capture Compare DMA source
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SelectCCDMA(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the CCDS Bit */
    TIMx->CR2 |= CR2_CCDS_Set;
  }
  else
  {
    /* Reset the CCDS Bit */
    TIMx->CR2 &= CR2_CCDS_Reset;
  }
}

/*******************************************************************************
* Function Name  : TIM_CCPreloadControl
* Description    : Sets or Resets the TIM peripheral Capture Compare Preload 
*                  Control bit.
* Input          :- TIMx: where x can be  1 or 8 to select the TIMx peripheral
*                 - NewState: new state of the Capture Compare Preload Control bit
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_CCPreloadControl(TIM_TypeDef* TIMx, FunctionalState NewState)
{ 
  /* Check the parameters */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the CCPC Bit */
    TIMx->CR2 |= CR2_CCPC_Set;
  }
  else
  {
    /* Reset the CCPC Bit */
    TIMx->CR2 &= CR2_CCPC_Reset;
  }
}

/*******************************************************************************
* Function Name  : TIM_OC1PreloadConfig
* Description    : Enables or disables the TIMx peripheral Preload register on CCR1.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCPreload: new state of the TIMx peripheral Preload
*                    register
*                    This parameter can be one of the following values:
*                       - TIM_OCPreload_Enable
*                       - TIM_OCPreload_Disable
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload)
{
  u16 tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

  tmpccmr1 = TIMx->CCMR1;

  /* Reset the OC1PE Bit */
  tmpccmr1 &= CCMR_OC13PE_Reset;

  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr1 |= TIM_OCPreload;

  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/*******************************************************************************
* Function Name  : TIM_OC2PreloadConfig
* Description    : Enables or disables the TIMx peripheral Preload register on CCR2.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCPreload: new state of the TIMx peripheral Preload
*                    register
*                    This parameter can be one of the following values:
*                       - TIM_OCPreload_Enable
*                       - TIM_OCPreload_Disable
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload)
{
  u16 tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

  tmpccmr1 = TIMx->CCMR1;

  /* Reset the OC2PE Bit */
  tmpccmr1 &= CCMR_OC24PE_Reset;

  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr1 |= (u16)(TIM_OCPreload << 8);

  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/*******************************************************************************
* Function Name  : TIM_OC3PreloadConfig
* Description    : Enables or disables the TIMx peripheral Preload register on CCR3.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCPreload: new state of the TIMx peripheral Preload
*                    register
*                    This parameter can be one of the following values:
*                       - TIM_OCPreload_Enable
*                       - TIM_OCPreload_Disable
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload)
{
  u16 tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

  tmpccmr2 = TIMx->CCMR2;

  /* Reset the OC3PE Bit */
  tmpccmr2 &= CCMR_OC13PE_Reset;

  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr2 |= TIM_OCPreload;

  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/*******************************************************************************
* Function Name  : TIM_OC4PreloadConfig
* Description    : Enables or disables the TIMx peripheral Preload register on CCR4.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCPreload: new state of the TIMx peripheral Preload
*                    register
*                    This parameter can be one of the following values:
*                       - TIM_OCPreload_Enable
*                       - TIM_OCPreload_Disable
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, u16 TIM_OCPreload)
{
  u16 tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCPRELOAD_STATE(TIM_OCPreload));

  tmpccmr2 = TIMx->CCMR2;

  /* Reset the OC4PE Bit */
  tmpccmr2 &= CCMR_OC24PE_Reset;

  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr2 |= (u16)(TIM_OCPreload << 8);

  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/*******************************************************************************
* Function Name  : TIM_OC1FastConfig
* Description    : Configures the TIMx Output Compare 1 Fast feature.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCFast: new state of the Output Compare Fast Enable Bit.
*                    This parameter can be one of the following values:
*                       - TIM_OCFast_Enable: TIM output compare fast enable
*                       - TIM_OCFast_Disable: TIM output compare fast disable
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC1FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast)
{
  u16 tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIMx->CCMR1;

  /* Reset the OC1FE Bit */
  tmpccmr1 &= CCMR_OC13FE_Reset;

  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr1 |= TIM_OCFast;

  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;
}

/*******************************************************************************
* Function Name  : TIM_OC2FastConfig
* Description    : Configures the TIMx Output Compare 2 Fast feature.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCFast: new state of the Output Compare Fast Enable Bit.
*                    This parameter can be one of the following values:
*                       - TIM_OCFast_Enable: TIM output compare fast enable
*                       - TIM_OCFast_Disable: TIM output compare fast disable
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast)
{
  u16 tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

  /* Get the TIMx CCMR1 register value */
  tmpccmr1 = TIMx->CCMR1;

  /* Reset the OC2FE Bit */
  tmpccmr1 &= CCMR_OC24FE_Reset;

  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr1 |= (u16)(TIM_OCFast << 8);

  /* Write to TIMx CCMR1 */
  TIMx->CCMR1 = tmpccmr1;
}

/*******************************************************************************
* Function Name  : TIM_OC3FastConfig
* Description    : Configures the TIMx Output Compare 3 Fast feature.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCFast: new state of the Output Compare Fast Enable Bit.
*                    This parameter can be one of the following values:
*                       - TIM_OCFast_Enable: TIM output compare fast enable
*                       - TIM_OCFast_Disable: TIM output compare fast disable
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast)
{
  u16 tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

  /* Get the TIMx CCMR2 register value */
  tmpccmr2 = TIMx->CCMR2;

  /* Reset the OC3FE Bit */
  tmpccmr2 &= CCMR_OC13FE_Reset;

  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr2 |= TIM_OCFast;

  /* Write to TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmr2;
}

/*******************************************************************************
* Function Name  : TIM_OC4FastConfig
* Description    : Configures the TIMx Output Compare 4 Fast feature.
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCFast: new state of the Output Compare Fast Enable Bit.
*                    This parameter can be one of the following values:
*                       - TIM_OCFast_Enable: TIM output compare fast enable
*                       - TIM_OCFast_Disable: TIM output compare fast disable
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, u16 TIM_OCFast)
{
  u16 tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCFAST_STATE(TIM_OCFast));

  /* Get the TIMx CCMR2 register value */
  tmpccmr2 = TIMx->CCMR2;

  /* Reset the OC4FE Bit */
  tmpccmr2 &= CCMR_OC24FE_Reset;

  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr2 |= (u16)(TIM_OCFast << 8);

  /* Write to TIMx CCMR2 */
  TIMx->CCMR2 = tmpccmr2;
}

/*******************************************************************************
* Function Name  : TIM_ClearOC1Ref
* Description    : Clears or safeguards the OCREF1 signal on an external event
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCClear: new state of the Output Compare Clear Enable Bit.
*                    This parameter can be one of the following values:
*                       - TIM_OCClear_Enable: TIM Output clear enable
*                       - TIM_OCClear_Disable: TIM Output clear disable
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear)
{
  u16 tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

  tmpccmr1 = TIMx->CCMR1;

  /* Reset the OC1CE Bit */
  tmpccmr1 &= CCMR_OC13CE_Reset;

  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr1 |= TIM_OCClear;

  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/*******************************************************************************
* Function Name  : TIM_ClearOC2Ref
* Description    : Clears or safeguards the OCREF2 signal on an external event
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCClear: new state of the Output Compare Clear Enable Bit.
*                    This parameter can be one of the following values:
*                       - TIM_OCClear_Enable: TIM Output clear enable
*                       - TIM_OCClear_Disable: TIM Output clear disable
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear)
{
  u16 tmpccmr1 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

  tmpccmr1 = TIMx->CCMR1;

  /* Reset the OC2CE Bit */
  tmpccmr1 &= CCMR_OC24CE_Reset;

  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr1 |= (u16)(TIM_OCClear << 8);

  /* Write to TIMx CCMR1 register */
  TIMx->CCMR1 = tmpccmr1;
}

/*******************************************************************************
* Function Name  : TIM_ClearOC3Ref
* Description    : Clears or safeguards the OCREF3 signal on an external event
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCClear: new state of the Output Compare Clear Enable Bit.
*                    This parameter can be one of the following values:
*                       - TIM_OCClear_Enable: TIM Output clear enable
*                       - TIM_OCClear_Disable: TIM Output clear disable
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear)
{
  u16 tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

  tmpccmr2 = TIMx->CCMR2;

  /* Reset the OC3CE Bit */
  tmpccmr2 &= CCMR_OC13CE_Reset;

  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr2 |= TIM_OCClear;

  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/*******************************************************************************
* Function Name  : TIM_ClearOC4Ref
* Description    : Clears or safeguards the OCREF4 signal on an external event
* Input          : - TIMx: where x can be  1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCClear: new state of the Output Compare Clear Enable Bit.
*                    This parameter can be one of the following values:
*                       - TIM_OCClear_Enable: TIM Output clear enable
*                       - TIM_OCClear_Disable: TIM Output clear disable
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, u16 TIM_OCClear)
{
  u16 tmpccmr2 = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OCCLEAR_STATE(TIM_OCClear));

  tmpccmr2 = TIMx->CCMR2;

  /* Reset the OC4CE Bit */
  tmpccmr2 &= CCMR_OC24CE_Reset;

  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr2 |= (u16)(TIM_OCClear << 8);

  /* Write to TIMx CCMR2 register */
  TIMx->CCMR2 = tmpccmr2;
}

/*******************************************************************************
* Function Name  : TIM_OC1PolarityConfig
* Description    : Configures the TIMx channel 1 polarity.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCPolarity: specifies the OC1 Polarity
*                    This parmeter can be one of the following values:
*                       - TIM_OCPolarity_High: Output Compare active high
*                       - TIM_OCPolarity_Low: Output Compare active low
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity)
{
  u16 tmpccer = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

  tmpccer = TIMx->CCER;

  /* Set or Reset the CC1P Bit */
  tmpccer &= CCER_CC1P_Reset;
  tmpccer |= TIM_OCPolarity;

  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TIM_OC1NPolarityConfig
* Description    : Configures the TIMx Channel 1N polarity.
* Input          : - TIMx: where x can be 1 or 8 to select the TIM peripheral.
*                  - TIM_OCNPolarity: specifies the OC1N Polarity
*                    This parmeter can be one of the following values:
*                       - TIM_OCNPolarity_High: Output Compare active high
*                       - TIM_OCNPolarity_Low: Output Compare active low
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity)
{
  u16 tmpccer = 0;

  /* Check the parameters */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
   
  tmpccer = TIMx->CCER;

  /* Set or Reset the CC1NP Bit */
  tmpccer &= CCER_CC1NP_Reset;
  tmpccer |= TIM_OCNPolarity;

  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TIM_OC2PolarityConfig
* Description    : Configures the TIMx channel 2 polarity.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCPolarity: specifies the OC2 Polarity
*                    This parmeter can be one of the following values:
*                       - TIM_OCPolarity_High: Output Compare active high
*                       - TIM_OCPolarity_Low: Output Compare active low
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity)
{
  u16 tmpccer = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

  tmpccer = TIMx->CCER;

  /* Set or Reset the CC2P Bit */
  tmpccer &= CCER_CC2P_Reset;
  tmpccer |= (u16)(TIM_OCPolarity << 4);

  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TIM_OC2NPolarityConfig
* Description    : Configures the TIMx Channel 2N polarity.
* Input          : - TIMx: where x can be 1 or 8 to select the TIM peripheral.
*                  - TIM_OCNPolarity: specifies the OC2N Polarity
*                    This parmeter can be one of the following values:
*                       - TIM_OCNPolarity_High: Output Compare active high
*                       - TIM_OCNPolarity_Low: Output Compare active low
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity)
{
  u16 tmpccer = 0;

  /* Check the parameters */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
  
  tmpccer = TIMx->CCER;

  /* Set or Reset the CC2NP Bit */
  tmpccer &= CCER_CC2NP_Reset;
  tmpccer |= (u16)(TIM_OCNPolarity << 4);

  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TIM_OC3PolarityConfig
* Description    : Configures the TIMx channel 3 polarity.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCPolarity: specifies the OC3 Polarity
*                    This parmeter can be one of the following values:
*                       - TIM_OCPolarity_High: Output Compare active high
*                       - TIM_OCPolarity_Low: Output Compare active low
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity)
{
  u16 tmpccer = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

  tmpccer = TIMx->CCER;

  /* Set or Reset the CC3P Bit */
  tmpccer &= CCER_CC3P_Reset;
  tmpccer |= (u16)(TIM_OCPolarity << 8);

  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TIM_OC3NPolarityConfig
* Description    : Configures the TIMx Channel 3N polarity.
* Input          : - TIMx: where x can be 1 or 8 to select the TIM peripheral.
*                  - TIM_OCNPolarity: specifies the OC3N Polarity
*                    This parmeter can be one of the following values:
*                       - TIM_OCNPolarity_High: Output Compare active high
*                       - TIM_OCNPolarity_Low: Output Compare active low
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCNPolarity)
{
  u16 tmpccer = 0;
 
  /* Check the parameters */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_OCN_POLARITY(TIM_OCNPolarity));
    
  tmpccer = TIMx->CCER;

  /* Set or Reset the CC3NP Bit */
  tmpccer &= CCER_CC3NP_Reset;
  tmpccer |= (u16)(TIM_OCNPolarity << 8);

  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TIM_OC4PolarityConfig
* Description    : Configures the TIMx channel 4 polarity.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_OCPolarity: specifies the OC4 Polarity
*                    This parmeter can be one of the following values:
*                       - TIM_OCPolarity_High: Output Compare active high
*                       - TIM_OCPolarity_Low: Output Compare active low
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, u16 TIM_OCPolarity)
{
  u16 tmpccer = 0;

  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCPolarity));

  tmpccer = TIMx->CCER;

  /* Set or Reset the CC4P Bit */
  tmpccer &= CCER_CC4P_Reset;
  tmpccer |= (u16)(TIM_OCPolarity << 12);

  /* Write to TIMx CCER register */
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TIM_CCxCmd
* Description    : Enables or disables the TIM Capture Compare Channel x.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM
*                    peripheral.
*                  - TIM_Channel: specifies the TIM Channel
*                    This parmeter can be one of the following values:
*                       - TIM_Channel_1: TIM Channel 1
*                       - TIM_Channel_2: TIM Channel 2
*                       - TIM_Channel_3: TIM Channel 3
*                       - TIM_Channel_4: TIM Channel 4
*                 - TIM_CCx: specifies the TIM Channel CCxE bit new state.
*                   This parameter can be: TIM_CCx_Enable or TIM_CCx_Disable. 
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_CCxCmd(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_CCx)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_CHANNEL(TIM_Channel));
  assert_param(IS_TIM_CCX(TIM_CCx));

  /* Reset the CCxE Bit */
  TIMx->CCER &= (u16)(~((u16)(CCER_CCE_Set << TIM_Channel)));

  /* Set or reset the CCxE Bit */ 
  TIMx->CCER |=  (u16)(TIM_CCx << TIM_Channel);
}

/*******************************************************************************
* Function Name  : TIM_CCxNCmd
* Description    : Enables or disables the TIM Capture Compare Channel xN.
* Input          :- TIMx: where x can be 1 or 8 to select the TIM peripheral.
*                 - TIM_Channel: specifies the TIM Channel
*                    This parmeter can be one of the following values:
*                       - TIM_Channel_1: TIM Channel 1
*                       - TIM_Channel_2: TIM Channel 2
*                       - TIM_Channel_3: TIM Channel 3
*                 - TIM_CCx: specifies the TIM Channel CCxNE bit new state.
*                   This parameter can be: TIM_CCxN_Enable or TIM_CCxN_Disable. 
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_CCxNCmd(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_CCxN)
{
  /* Check the parameters */
  assert_param(IS_TIM_18_PERIPH(TIMx));
  assert_param(IS_TIM_COMPLEMENTARY_CHANNEL(TIM_Channel));
  assert_param(IS_TIM_CCXN(TIM_CCxN));

  /* Reset the CCxNE Bit */
  TIMx->CCER &= (u16)(~((u16)(CCER_CCNE_Set << TIM_Channel)));

  /* Set or reset the CCxNE Bit */ 
  TIMx->CCER |=  (u16)(TIM_CCxN << TIM_Channel);
}

/*******************************************************************************
* Function Name  : TIM_SelectOCxM
* Description    : Selects the TIM Ouput Compare Mode.
*                  This function disables the selected channel before changing 
*                  the Ouput Compare Mode. User has to enable this channel using
*                  TIM_CCxCmd and TIM_CCxNCmd functions.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM
*                    peripheral.
*                  - TIM_Channel: specifies the TIM Channel
*                    This parmeter can be one of the following values:
*                       - TIM_Channel_1: TIM Channel 1
*                       - TIM_Channel_2: TIM Channel 2
*                       - TIM_Channel_3: TIM Channel 3
*                       - TIM_Channel_4: TIM Channel 4
*                  - TIM_OCMode: specifies the TIM Output Compare Mode.
*                    This paramter can be one of the following values:
*                       - TIM_OCMode_Timing
*                       - TIM_OCMode_Active
*                       - TIM_OCMode_Toggle
*                       - TIM_OCMode_PWM1
*                       - TIM_OCMode_PWM2
*                       - TIM_ForcedAction_Active
*                       - TIM_ForcedAction_InActive
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SelectOCxM(TIM_TypeDef* TIMx, u16 TIM_Channel, u16 TIM_OCMode)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_CHANNEL(TIM_Channel));
  assert_param(IS_TIM_OCM(TIM_OCMode));
  
  /* Disable the Channel: Reset the CCxE Bit */
  TIMx->CCER &= (u16)(~((u16)(CCER_CCE_Set << TIM_Channel)));

  if((TIM_Channel == TIM_Channel_1) ||(TIM_Channel == TIM_Channel_3))
  {
    /* Reset the OCxM bits in the CCMRx register */
    *((vu32 *)((*(u32*)&TIMx) + CCMR_Offset + (TIM_Channel>>1))) &= CCMR_OC13M_Mask;
   
    /* Configure the OCxM bits in the CCMRx register */
    *((vu32 *)((*(u32*)&TIMx) + CCMR_Offset + (TIM_Channel>>1))) |= TIM_OCMode;

  }
  else
  {
    /* Reset the OCxM bits in the CCMRx register */
    *((vu32 *)((*(u32*)&TIMx) + CCMR_Offset + ((u16)(TIM_Channel - 4)>> 1))) &= CCMR_OC24M_Mask;
    
    /* Configure the OCxM bits in the CCMRx register */
    *((vu32 *)((*(u32*)&TIMx) + CCMR_Offset + ((u16)(TIM_Channel - 4)>> 1))) |= (u16)(TIM_OCMode << 8);
  }
}

/*******************************************************************************
* Function Name  : TIM_UpdateDisableConfig
* Description    : Enables or Disables the TIMx Update event.
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
*                  - NewState: new state of the TIMx UDIS bit
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_UpdateDisableConfig(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the Update Disable Bit */
    TIMx->CR1 |= CR1_UDIS_Set;
  }
  else
  {
    /* Reset the Update Disable Bit */
    TIMx->CR1 &= CR1_UDIS_Reset;
  }
}

/*******************************************************************************
* Function Name  : TIM_UpdateRequestConfig
* Description    : Configures the TIMx Update Request Interrupt source.
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
*                  - TIM_UpdateSource: specifies the Update source.
*                    This parameter can be one of the following values:
*                       - TIM_UpdateSource_Regular
*                       - TIM_UpdateSource_Global
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_UpdateRequestConfig(TIM_TypeDef* TIMx, u16 TIM_UpdateSource)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_UPDATE_SOURCE(TIM_UpdateSource));

  if (TIM_UpdateSource != TIM_UpdateSource_Global)
  {
    /* Set the URS Bit */
    TIMx->CR1 |= CR1_URS_Set;
  }
  else
  {
    /* Reset the URS Bit */
    TIMx->CR1 &= CR1_URS_Reset;
  }
}

/*******************************************************************************
* Function Name  : TIM_SelectHallSensor
* Description    : Enables or disables the TIMx’s Hall sensor interface.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM peripheral.
*                  - NewState: new state of the TIMx Hall sensor interface.
*                    This parameter can be: ENABLE or DISABLE.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SelectHallSensor(TIM_TypeDef* TIMx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the TI1S Bit */
    TIMx->CR2 |= CR2_TI1S_Set;
  }
  else
  {
    /* Reset the TI1S Bit */
    TIMx->CR2 &= CR2_TI1S_Reset;
  }
}

/*******************************************************************************
* Function Name  : TIM_SelectOnePulseMode
* Description    : Selects the TIMx’s One Pulse Mode.
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
*                  - TIM_OPMode: specifies the OPM Mode to be used.
*                    This parameter can be one of the following values:
*                       - TIM_OPMode_Single
*                       - TIM_OPMode_Repetitive
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SelectOnePulseMode(TIM_TypeDef* TIMx, u16 TIM_OPMode)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_OPM_MODE(TIM_OPMode));

  /* Reset the OPM Bit */
  TIMx->CR1 &= CR1_OPM_Reset;

  /* Configure the OPM Mode */
  TIMx->CR1 |= TIM_OPMode;
}

/*******************************************************************************
* Function Name  : TIM_SelectOutputTrigger
* Description    : Selects the TIMx Trigger Output Mode.
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
*                  - TIM_TRGOSource: specifies the Trigger Output source.
*                    This paramter can be as follow:
*                      1/ For TIM1 to TIM8:
*                       - TIM_TRGOSource_Reset 
*                       - TIM_TRGOSource_Enable
*                       - TIM_TRGOSource_Update
*                      2/ These parameters are available for all TIMx except 
*                         TIM6 and TIM7:
*                       - TIM_TRGOSource_OC1
*                       - TIM_TRGOSource_OC1Ref
*                       - TIM_TRGOSource_OC2Ref
*                       - TIM_TRGOSource_OC3Ref
*                       - TIM_TRGOSource_OC4Ref
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SelectOutputTrigger(TIM_TypeDef* TIMx, u16 TIM_TRGOSource)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_TRGO_SOURCE(TIM_TRGOSource));
  assert_param(IS_TIM_PERIPH_TRGO(TIMx, TIM_TRGOSource));

  /* Reset the MMS Bits */
  TIMx->CR2 &= CR2_MMS_Mask;

  /* Select the TRGO source */
  TIMx->CR2 |=  TIM_TRGOSource;
}

/*******************************************************************************
* Function Name  : TIM_SelectSlaveMode
* Description    : Selects the TIMx Slave Mode.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_SlaveMode: specifies the Timer Slave Mode.
*                    This paramter can be one of the following values:
*                       - TIM_SlaveMode_Reset
*                       - TIM_SlaveMode_Gated
*                       - TIM_SlaveMode_Trigger
*                       - TIM_SlaveMode_External1
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SelectSlaveMode(TIM_TypeDef* TIMx, u16 TIM_SlaveMode)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_SLAVE_MODE(TIM_SlaveMode));

  /* Reset the SMS Bits */
  TIMx->SMCR &= SMCR_SMS_Mask;

  /* Select the Slave Mode */
  TIMx->SMCR |= TIM_SlaveMode;
}

/*******************************************************************************
* Function Name  : TIM_SelectMasterSlaveMode
* Description    : Sets or Resets the TIMx Master/Slave Mode.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_MasterSlaveMode: specifies the Timer Master Slave Mode.
*                    This paramter can be one of the following values:
*                       - TIM_MasterSlaveMode_Enable: synchronization between the
*                         current timer and its slaves (through TRGO).
*                       - TIM_MasterSlaveMode_Disable: No action
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SelectMasterSlaveMode(TIM_TypeDef* TIMx, u16 TIM_MasterSlaveMode)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_MSM_STATE(TIM_MasterSlaveMode));

  /* Reset the MSM Bit */
  TIMx->SMCR &= SMCR_MSM_Reset;
  
  /* Set or Reset the MSM Bit */
  TIMx->SMCR |= TIM_MasterSlaveMode;
}

/*******************************************************************************
* Function Name  : TIM_SetCounter
* Description    : Sets the TIMx Counter Register value
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
*                  - Counter: specifies the Counter register new value.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SetCounter(TIM_TypeDef* TIMx, u16 Counter)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));

  /* Set the Counter Register value */
  TIMx->CNT = Counter;
}

/*******************************************************************************
* Function Name  : TIM_SetAutoreload
* Description    : Sets the TIMx Autoreload Register value
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
*                  - Autoreload: specifies the Autoreload register new value.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SetAutoreload(TIM_TypeDef* TIMx, u16 Autoreload)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));

  /* Set the Autoreload Register value */
  TIMx->ARR = Autoreload;
}

/*******************************************************************************
* Function Name  : TIM_SetCompare1
* Description    : Sets the TIMx Capture Compare1 Register value
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - Compare1: specifies the Capture Compare1 register new value.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SetCompare1(TIM_TypeDef* TIMx, u16 Compare1)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));

  /* Set the Capture Compare1 Register value */
  TIMx->CCR1 = Compare1;
}

/*******************************************************************************
* Function Name  : TIM_SetCompare2
* Description    : Sets the TIMx Capture Compare2 Register value
* Input          :  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                   peripheral.
*                  - Compare2: specifies the Capture Compare2 register new value.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SetCompare2(TIM_TypeDef* TIMx, u16 Compare2)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));

  /* Set the Capture Compare2 Register value */
  TIMx->CCR2 = Compare2;
}

/*******************************************************************************
* Function Name  : TIM_SetCompare3
* Description    : Sets the TIMx Capture Compare3 Register value
* Input          :  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                   peripheral.
*                  - Compare3: specifies the Capture Compare3 register new value.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SetCompare3(TIM_TypeDef* TIMx, u16 Compare3)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));

  /* Set the Capture Compare3 Register value */
  TIMx->CCR3 = Compare3;
}

/*******************************************************************************
* Function Name  : TIM_SetCompare4
* Description    : Sets the TIMx Capture Compare4 Register value
* Input          :  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                   peripheral.
*                  - Compare4: specifies the Capture Compare4 register new value.
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SetCompare4(TIM_TypeDef* TIMx, u16 Compare4)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));

  /* Set the Capture Compare4 Register value */
  TIMx->CCR4 = Compare4;
}

/*******************************************************************************
* Function Name  : TIM_SetIC1Prescaler
* Description    : Sets the TIMx Input Capture 1 prescaler.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ICPSC: specifies the Input Capture1 prescaler
*                    new value.
*                    This parameter can be one of the following values:
*                       - TIM_ICPSC_DIV1: no prescaler
*                       - TIM_ICPSC_DIV2: capture is done once every 2 events
*                       - TIM_ICPSC_DIV4: capture is done once every 4 events
*                       - TIM_ICPSC_DIV8: capture is done once every 8 events
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SetIC1Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

  /* Reset the IC1PSC Bits */
  TIMx->CCMR1 &= CCMR_IC13PSC_Mask;

  /* Set the IC1PSC value */
  TIMx->CCMR1 |= TIM_ICPSC;
}

/*******************************************************************************
* Function Name  : TIM_SetIC2Prescaler
* Description    : Sets the TIMx Input Capture 2 prescaler.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ICPSC: specifies the Input Capture2 prescaler
*                    new value.
*                    This parameter can be one of the following values:
*                       - TIM_ICPSC_DIV1: no prescaler
*                       - TIM_ICPSC_DIV2: capture is done once every 2 events
*                       - TIM_ICPSC_DIV4: capture is done once every 4 events
*                       - TIM_ICPSC_DIV8: capture is done once every 8 events
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SetIC2Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

  /* Reset the IC2PSC Bits */
  TIMx->CCMR1 &= CCMR_IC24PSC_Mask;

  /* Set the IC2PSC value */
  TIMx->CCMR1 |= (u16)(TIM_ICPSC << 8);
}

/*******************************************************************************
* Function Name  : TIM_SetIC3Prescaler
* Description    : Sets the TIMx Input Capture 3 prescaler.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ICPSC: specifies the Input Capture3 prescaler
*                    new value.
*                    This parameter can be one of the following values:
*                       - TIM_ICPSC_DIV1: no prescaler
*                       - TIM_ICPSC_DIV2: capture is done once every 2 events
*                       - TIM_ICPSC_DIV4: capture is done once every 4 events
*                       - TIM_ICPSC_DIV8: capture is done once every 8 events
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SetIC3Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

  /* Reset the IC3PSC Bits */
  TIMx->CCMR2 &= CCMR_IC13PSC_Mask;

  /* Set the IC3PSC value */
  TIMx->CCMR2 |= TIM_ICPSC;
}

/*******************************************************************************
* Function Name  : TIM_SetIC4Prescaler
* Description    : Sets the TIMx Input Capture 4 prescaler.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ICPSC: specifies the Input Capture4 prescaler
*                    new value.
*                    This parameter can be one of the following values:
*                      - TIM_ICPSC_DIV1: no prescaler
*                      - TIM_ICPSC_DIV2: capture is done once every 2 events
*                      - TIM_ICPSC_DIV4: capture is done once every 4 events
*                      - TIM_ICPSC_DIV8: capture is done once every 8 events
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SetIC4Prescaler(TIM_TypeDef* TIMx, u16 TIM_ICPSC)
{  
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_IC_PRESCALER(TIM_ICPSC));

  /* Reset the IC4PSC Bits */
  TIMx->CCMR2 &= CCMR_IC24PSC_Mask;

  /* Set the IC4PSC value */
  TIMx->CCMR2 |= (u16)(TIM_ICPSC << 8);
}

/*******************************************************************************
* Function Name  : TIM_SetClockDivision
* Description    : Sets the TIMx Clock Division value.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_CKD: specifies the clock division value.
*                    This parameter can be one of the following value:
*                       - TIM_CKD_DIV1: TDTS = Tck_tim
*                       - TIM_CKD_DIV2: TDTS = 2*Tck_tim
*                       - TIM_CKD_DIV4: TDTS = 4*Tck_tim
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_SetClockDivision(TIM_TypeDef* TIMx, u16 TIM_CKD)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));
  assert_param(IS_TIM_CKD_DIV(TIM_CKD));

  /* Reset the CKD Bits */
  TIMx->CR1 &= CR1_CKD_Mask;

  /* Set the CKD value */
  TIMx->CR1 |= TIM_CKD;
}
/*******************************************************************************
* Function Name  : TIM_GetCapture1
* Description    : Gets the TIMx Input Capture 1 value.
* Input          :  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                   peripheral.
* Output         : None
* Return         : Capture Compare 1 Register value.
*******************************************************************************/
u16 TIM_GetCapture1(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));

  /* Get the Capture 1 Register value */
  return TIMx->CCR1;
}

/*******************************************************************************
* Function Name  : TIM_GetCapture2
* Description    : Gets the TIMx Input Capture 2 value.
* Input          :  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                   peripheral.
* Output         : None
* Return         : Capture Compare 2 Register value.
*******************************************************************************/
u16 TIM_GetCapture2(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));

  /* Get the Capture 2 Register value */
  return TIMx->CCR2;
}

/*******************************************************************************
* Function Name  : TIM_GetCapture3
* Description    : Gets the TIMx Input Capture 3 value.
* Input          :  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                   peripheral.
* Output         : None
* Return         : Capture Compare 3 Register value.
*******************************************************************************/
u16 TIM_GetCapture3(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx)); 

  /* Get the Capture 3 Register value */
  return TIMx->CCR3;
}

/*******************************************************************************
* Function Name  : TIM_GetCapture4
* Description    : Gets the TIMx Input Capture 4 value.
* Input          :  TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                   peripheral.
* Output         : None
* Return         : Capture Compare 4 Register value.
*******************************************************************************/
u16 TIM_GetCapture4(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_123458_PERIPH(TIMx));

  /* Get the Capture 4 Register value */
  return TIMx->CCR4;
}

/*******************************************************************************
* Function Name  : TIM_GetCounter
* Description    : Gets the TIMx Counter value.
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
* Output         : None
* Return         : Counter Register value.
*******************************************************************************/
u16 TIM_GetCounter(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));

  /* Get the Counter Register value */
  return TIMx->CNT;
}

/*******************************************************************************
* Function Name  : TIM_GetPrescaler
* Description    : Gets the TIMx Prescaler value.
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
* Output         : None
* Return         : Prescaler Register value.
*******************************************************************************/
u16 TIM_GetPrescaler(TIM_TypeDef* TIMx)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));

  /* Get the Prescaler Register value */
  return TIMx->PSC;
}

/*******************************************************************************
* Function Name  : TIM_GetFlagStatus
* Description    : Checks whether the specified TIM flag is set or not.
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
*                  - TIM_FLAG: specifies the flag to check.
*                    This parameter can be one of the following values:
*                       - TIM_FLAG_Update: TIM update Flag
*                       - TIM_FLAG_CC1: TIM Capture Compare 1 Flag
*                       - TIM_FLAG_CC2: TIM Capture Compare 2 Flag
*                       - TIM_FLAG_CC3: TIM Capture Compare 3 Flag
*                       - TIM_FLAG_CC4: TIM Capture Compare 4 Flag
*                       - TIM_FLAG_COM: TIM Commutation Flag
*                       - TIM_FLAG_Trigger: TIM Trigger Flag
*                       - TIM_FLAG_Break: TIM Break Flag
*                       - TIM_FLAG_CC1OF: TIM Capture Compare 1 overcapture Flag
*                       - TIM_FLAG_CC2OF: TIM Capture Compare 2 overcapture Flag
*                       - TIM_FLAG_CC3OF: TIM Capture Compare 3 overcapture Flag
*                       - TIM_FLAG_CC4OF: TIM Capture Compare 4 overcapture Flag
* Output         : None
* Return         : The new state of TIM_FLAG (SET or RESET).
*******************************************************************************/
FlagStatus TIM_GetFlagStatus(TIM_TypeDef* TIMx, u16 TIM_FLAG)
{ 
  ITStatus bitstatus = RESET;  

  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_GET_FLAG(TIM_FLAG));
  assert_param(IS_TIM_PERIPH_FLAG(TIMx, TIM_FLAG));
  
  if ((TIMx->SR & TIM_FLAG) != (u16)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : TIM_ClearFlag
* Description    : Clears the TIMx's pending flags.
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
*                  - TIM_FLAG: specifies the flag bit to clear.
*                    This parameter can be any combination of the following values:
*                       - TIM_FLAG_Update: TIM update Flag
*                       - TIM_FLAG_CC1: TIM Capture Compare 1 Flag
*                       - TIM_FLAG_CC2: TIM Capture Compare 2 Flag
*                       - TIM_FLAG_CC3: TIM Capture Compare 3 Flag
*                       - TIM_FLAG_CC4: TIM Capture Compare 4 Flag
*                       - TIM_FLAG_COM: TIM Commutation Flag
*                       - TIM_FLAG_Trigger: TIM Trigger Flag
*                       - TIM_FLAG_Break: TIM Break Flag
*                       - TIM_FLAG_CC1OF: TIM Capture Compare 1 overcapture Flag
*                       - TIM_FLAG_CC2OF: TIM Capture Compare 2 overcapture Flag
*                       - TIM_FLAG_CC3OF: TIM Capture Compare 3 overcapture Flag
*                       - TIM_FLAG_CC4OF: TIM Capture Compare 4 overcapture Flag
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ClearFlag(TIM_TypeDef* TIMx, u16 TIM_FLAG)
{  
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_CLEAR_FLAG(TIMx, TIM_FLAG));
   
  /* Clear the flags */
  TIMx->SR = (u16)~TIM_FLAG;
}

/*******************************************************************************
* Function Name  : TIM_GetITStatus
* Description    : Checks whether the TIM interrupt has occurred or not.
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
*                  - TIM_IT: specifies the TIM interrupt source to check.
*                    This parameter can be one of the following values:
*                       - TIM_IT_Update: TIM update Interrupt source
*                       - TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
*                       - TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
*                       - TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
*                       - TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
*                       - TIM_IT_COM: TIM Commutation Interrupt
*                         source
*                       - TIM_IT_Trigger: TIM Trigger Interrupt source
*                       - TIM_IT_Break: TIM Break Interrupt source
* Output         : None
* Return         : The new state of the TIM_IT(SET or RESET).
*******************************************************************************/
ITStatus TIM_GetITStatus(TIM_TypeDef* TIMx, u16 TIM_IT)
{
  ITStatus bitstatus = RESET;  
  u16 itstatus = 0x0, itenable = 0x0;

  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_GET_IT(TIM_IT));
  assert_param(IS_TIM_PERIPH_IT(TIMx, TIM_IT));
   
  itstatus = TIMx->SR & TIM_IT;
  
  itenable = TIMx->DIER & TIM_IT;

  if ((itstatus != (u16)RESET) && (itenable != (u16)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return bitstatus;
}

/*******************************************************************************
* Function Name  : TIM_ClearITPendingBit
* Description    : Clears the TIMx's interrupt pending bits.
* Input          : - TIMx: where x can be 1 to 8 to select the TIM peripheral.
*                  - TIM_IT: specifies the pending bit to clear.
*                    This parameter can be any combination of the following values:
*                       - TIM_IT_Update: TIM1 update Interrupt source
*                       - TIM_IT_CC1: TIM Capture Compare 1 Interrupt source
*                       - TIM_IT_CC2: TIM Capture Compare 2 Interrupt source
*                       - TIM_IT_CC3: TIM Capture Compare 3 Interrupt source
*                       - TIM_IT_CC4: TIM Capture Compare 4 Interrupt source
*                       - TIM_IT_COM: TIM Commutation Interrupt
*                         source
*                       - TIM_IT_Trigger: TIM Trigger Interrupt source
*                       - TIM_IT_Break: TIM Break Interrupt source
* Output         : None
* Return         : None
*******************************************************************************/
void TIM_ClearITPendingBit(TIM_TypeDef* TIMx, u16 TIM_IT)
{
  /* Check the parameters */
  assert_param(IS_TIM_ALL_PERIPH(TIMx));
  assert_param(IS_TIM_PERIPH_IT(TIMx, TIM_IT));

  /* Clear the IT pending Bit */
  TIMx->SR = (u16)~TIM_IT;
}

/*******************************************************************************
* Function Name  : TI1_Config
* Description    : Configure the TI1 as Input.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ICPolarity : The Input Polarity.
*                    This parameter can be one of the following values:
*                       - TIM_ICPolarity_Rising
*                       - TIM_ICPolarity_Falling
*                  - TIM_ICSelection: specifies the input to be used.
*                    This parameter can be one of the following values:
*                       - TIM_ICSelection_DirectTI: TIM Input 1 is selected to
*                         be connected to IC1.
*                       - TIM_ICSelection_IndirectTI: TIM Input 1 is selected to
*                         be connected to IC2.
*                       - TIM_ICSelection_TRC: TIM Input 1 is selected to be
*                         connected to TRC.
*                  - TIM_ICFilter: Specifies the Input Capture Filter.
*                    This parameter must be a value between 0x00 and 0x0F.
* Output         : None
* Return         : None
*******************************************************************************/
static void TI1_Config(TIM_TypeDef* TIMx, u16 TIM_ICPolarity, u16 TIM_ICSelection,
                       u16 TIM_ICFilter)
{
  u16 tmpccmr1 = 0, tmpccer = 0;

  /* Disable the Channel 1: Reset the CC1E Bit */
  TIMx->CCER &= CCER_CC1E_Reset;

  tmpccmr1 = TIMx->CCMR1;
  tmpccer = TIMx->CCER;

  /* Select the Input and set the filter */
  tmpccmr1 &= CCMR_CC13S_Mask & CCMR_IC13F_Mask;
  tmpccmr1 |= TIM_ICSelection | (u16)(TIM_ICFilter << 4);

  /* Select the Polarity and set the CC1E Bit */
  tmpccer &= CCER_CC1P_Reset;
  tmpccer |= TIM_ICPolarity | CCER_CC1E_Set;

  /* Write to TIMx CCMR1 and CCER registers */
  TIMx->CCMR1 = tmpccmr1;
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TI2_Config
* Description    : Configure the TI2 as Input.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ICPolarity : The Input Polarity.
*                    This parameter can be one of the following values:
*                       - TIM_ICPolarity_Rising
*                       - TIM_ICPolarity_Falling
*                  - TIM_ICSelection: specifies the input to be used.
*                    This parameter can be one of the following values:
*                       - TIM_ICSelection_DirectTI: TIM Input 2 is selected to
*                         be connected to IC2.
*                       - TIM_ICSelection_IndirectTI: TIM Input 2 is selected to
*                         be connected to IC1.
*                       - TIM_ICSelection_TRC: TIM Input 2 is selected to be
*                         connected to TRC.
*                  - TIM_ICFilter: Specifies the Input Capture Filter.
*                    This parameter must be a value between 0x00 and 0x0F.
* Output         : None
* Return         : None
*******************************************************************************/
static void TI2_Config(TIM_TypeDef* TIMx, u16 TIM_ICPolarity, u16 TIM_ICSelection,
                       u16 TIM_ICFilter)
{
  u16 tmpccmr1 = 0, tmpccer = 0, tmp = 0;

  /* Disable the Channel 2: Reset the CC2E Bit */
  TIMx->CCER &= CCER_CC2E_Reset;

  tmpccmr1 = TIMx->CCMR1;
  tmpccer = TIMx->CCER;
  tmp = (u16)(TIM_ICPolarity << 4);

  /* Select the Input and set the filter */
  tmpccmr1 &= CCMR_CC24S_Mask & CCMR_IC24F_Mask;
  tmpccmr1 |= (u16)(TIM_ICFilter << 12);
  tmpccmr1 |= (u16)(TIM_ICSelection << 8);

  /* Select the Polarity and set the CC2E Bit */
  tmpccer &= CCER_CC2P_Reset;
  tmpccer |=  tmp | CCER_CC2E_Set;

  /* Write to TIMx CCMR1 and CCER registers */
  TIMx->CCMR1 = tmpccmr1 ;
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TI3_Config
* Description    : Configure the TI3 as Input.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ICPolarity : The Input Polarity.
*                    This parameter can be one of the following values:
*                       - TIM_ICPolarity_Rising
*                       - TIM_ICPolarity_Falling
*                  - TIM_ICSelection: specifies the input to be used.
*                    This parameter can be one of the following values:
*                       - TIM_ICSelection_DirectTI: TIM Input 3 is selected to
*                         be connected to IC3.
*                       - TIM_ICSelection_IndirectTI: TIM Input 3 is selected to
*                         be connected to IC4.
*                       - TIM_ICSelection_TRC: TIM Input 3 is selected to be
*                         connected to TRC.
*                  - TIM_ICFilter: Specifies the Input Capture Filter.
*                    This parameter must be a value between 0x00 and 0x0F.
* Output         : None
* Return         : None
*******************************************************************************/
static void TI3_Config(TIM_TypeDef* TIMx, u16 TIM_ICPolarity, u16 TIM_ICSelection,
                       u16 TIM_ICFilter)
{
  u16 tmpccmr2 = 0, tmpccer = 0, tmp = 0;

  /* Disable the Channel 3: Reset the CC3E Bit */
  TIMx->CCER &= CCER_CC3E_Reset;

  tmpccmr2 = TIMx->CCMR2;
  tmpccer = TIMx->CCER;
  tmp = (u16)(TIM_ICPolarity << 8);

  /* Select the Input and set the filter */
  tmpccmr2 &= CCMR_CC13S_Mask & CCMR_IC13F_Mask;
  tmpccmr2 |= TIM_ICSelection | (u16)(TIM_ICFilter << 4);

  /* Select the Polarity and set the CC3E Bit */
  tmpccer &= CCER_CC3P_Reset;
  tmpccer |= tmp | CCER_CC3E_Set;

  /* Write to TIMx CCMR2 and CCER registers */
  TIMx->CCMR2 = tmpccmr2;
  TIMx->CCER = tmpccer;
}

/*******************************************************************************
* Function Name  : TI4_Config
* Description    : Configure the TI1 as Input.
* Input          : - TIMx: where x can be 1, 2, 3, 4, 5 or 8 to select the TIM 
*                    peripheral.
*                  - TIM_ICPolarity : The Input Polarity.
*                    This parameter can be one of the following values:
*                       - TIM_ICPolarity_Rising
*                       - TIM_ICPolarity_Falling
*                  - TIM_ICSelection: specifies the input to be used.
*                    This parameter can be one of the following values:
*                       - TIM_ICSelection_DirectTI: TIM Input 4 is selected to
*                         be connected to IC4.
*                       - TIM_ICSelection_IndirectTI: TIM Input 4 is selected to
*                         be connected to IC3.
*                       - TIM_ICSelection_TRC: TIM Input 4 is selected to be
*                         connected to TRC.
*                  - TIM_ICFilter: Specifies the Input Capture Filter.
*                    This parameter must be a value between 0x00 and 0x0F.
* Output         : None
* Return         : None
*******************************************************************************/
static void TI4_Config(TIM_TypeDef* TIMx, u16 TIM_ICPolarity, u16 TIM_ICSelection,
                       u16 TIM_ICFilter)
{
  u16 tmpccmr2 = 0, tmpccer = 0, tmp = 0;

  /* Disable the Channel 4: Reset the CC4E Bit */
  TIMx->CCER &= CCER_CC4E_Reset;

  tmpccmr2 = TIMx->CCMR2;
  tmpccer = TIMx->CCER;
  tmp = (u16)(TIM_ICPolarity << 12);

  /* Select the Input and set the filter */
  tmpccmr2 &= CCMR_CC24S_Mask & CCMR_IC24F_Mask;
  tmpccmr2 |= (u16)(TIM_ICSelection << 8) | (u16)(TIM_ICFilter << 12);

  /* Select the Polarity and set the CC4E Bit */
  tmpccer &= CCER_CC4P_Reset;
  tmpccer |= tmp | CCER_CC4E_Set;

  /* Write to TIMx CCMR2 and CCER registers */
  TIMx->CCMR2 = tmpccmr2;
  TIMx->CCER = tmpccer ;
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
