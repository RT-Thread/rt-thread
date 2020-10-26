/**
 **************************************************************************
 * File Name    : at32f4xx_tim.c
 * Description  : at32f4xx TTMER source file
 * Date         : 2018-10-08
 * Version      : V1.0.5
 **************************************************************************
 */


/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_tim.h"
#include "at32f4xx_rcc.h"

/** @addtogroup at32f4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup TMR
  * @brief TMR driver modules
  * @{
  */

/** @defgroup TMR_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup TMR_Private_Defines
  * @{
  */

/* ---------------------- TMR registers bit mask ------------------------ */
#define SMC_ETR_Mask               ((uint16_t)0x00FF)
#define CCMR_Offset                ((uint16_t)0x0018)
#define CCE_CCE_Set                ((uint16_t)0x0001)
#define	CCE_CCNE_Set               ((uint16_t)0x0004)

/**
  * @}
  */

/** @defgroup TMR_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup TMR_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup TMR_Private_FunctionPrototypes
  * @{
  */

static void TI1_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection,
                       uint16_t TMR_ICFilter);
static void TI2_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection,
                       uint16_t TMR_ICFilter);
static void TI3_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection,
                       uint16_t TMR_ICFilter);
static void TI4_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection,
                       uint16_t TMR_ICFilter);
/**
  * @}
  */

/** @defgroup TMR_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup TMR_Private_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup TMR_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup TMR_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the TMRx peripheral registers to their default reset values.
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @retval None
  */
void TMR_Reset(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));

  if (TMRx == TMR1)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_TMR1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_TMR1, DISABLE);
  }
  else if (TMRx == TMR2)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR2, DISABLE);
  }
  else if (TMRx == TMR3)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR3, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR3, DISABLE);
  }
  else if (TMRx == TMR4)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR4, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR4, DISABLE);
  }
  else if (TMRx == TMR5)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR5, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR5, DISABLE);
  }
#if defined (AT32F403xx)
  else if (TMRx == TMR6)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR6, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR6, DISABLE);
  }
  else if (TMRx == TMR7)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR7, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR7, DISABLE);
  }
#endif
#if defined (AT32F403xx) || defined (AT32F413xx)
  else if (TMRx == TMR8)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_TMR8, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_TMR8, DISABLE);
  }
#endif
  else if (TMRx == TMR9)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_TMR9, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_TMR9, DISABLE);
  }
  else if (TMRx == TMR10)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_TMR10, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_TMR10, DISABLE);
  }
  else if (TMRx == TMR11)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_TMR11, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_TMR11, DISABLE);
  }
#if defined (AT32F403xx)
  else if (TMRx == TMR12)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR12, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR12, DISABLE);
  }
  else if (TMRx == TMR13)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR13, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR13, DISABLE);
  }
  else if (TMRx == TMR14)
  {
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR14, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1PERIPH_TMR14, DISABLE);
  }
  else if (TMRx == TMR15)
  {
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_TMR15, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2PERIPH_TMR15, DISABLE);
  }
#endif
}

/**
  * @brief  Initializes the TMRx Time Base Unit peripheral according to
  *         the specified parameters in the TMR_TimeBaseInitStruct.
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @param  TMR_TimeBaseInitStruct: pointer to a TMR_TimerBaseInitType
  *         structure that contains the configuration information for the
  *         specified TMR peripheral.
  * @retval None
  */
void TMR_TimeBaseInit(TMR_Type* TMRx, TMR_TimerBaseInitType* TMR_TimeBaseInitStruct)
{
  uint16_t tmpcr1 = 0;

  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  assert_param(IS_TMR_COUNTER_DIR(TMR_TimeBaseInitStruct->TMR_CounterMode));
  assert_param(IS_TMR_CKD_DIV(TMR_TimeBaseInitStruct->TMR_ClockDivision));

  tmpcr1 = TMRx->CTRL1;

  if((TMRx == TMR1) || (TMRx == TMR2) ||
#if !defined (AT32F415xx)
     (TMRx == TMR8) ||
#endif
#if defined (AT32F403xx)
     (TMRx == TMR15) ||
#endif
     (TMRx == TMR3) || (TMRx == TMR4) || (TMRx == TMR5))
  {
    /* Select the Counter Mode */
    tmpcr1 &= (uint16_t)(~((uint16_t)(TMR_CTRL1_DIR | TMR_CTRL1_CMSEL)));
    tmpcr1 |= (uint32_t)TMR_TimeBaseInitStruct->TMR_CounterMode;
  }

#ifdef AT32F403xx
  if((TMRx != TMR6) && (TMRx != TMR7))
  {
    /* Set the clock division */
    tmpcr1 &= (uint16_t)(~((uint16_t)TMR_CTRL1_CLKDIV));
    tmpcr1 |= (uint32_t)TMR_TimeBaseInitStruct->TMR_ClockDivision;
  }
#endif

  TMRx->CTRL1 = tmpcr1;

  /* Set the Autoreload value */
  TMRx->AR = TMR_TimeBaseInitStruct->TMR_Period ;

  /* Set the Prescaler value */
  TMRx->DIV = TMR_TimeBaseInitStruct->TMR_DIV;

#ifdef AT32F415xx
	if (TMRx == TMR1)
#elif defined AT32F413xx
    if ((TMRx == TMR1) || (TMRx == TMR8))
#elif defined AT32F403xx
    if ((TMRx == TMR1) || (TMRx == TMR8) || (TMRx == TMR15))
#endif
  {
    /* Set the Repetition Counter value */
    TMRx->RC = TMR_TimeBaseInitStruct->TMR_RepetitionCounter;
  }

  /* Generate an update event to reload the Prescaler and the Repetition counter
     values immediately */
  TMRx->EVEG = TMR_DIVReloadMode_Immediate;
}

/**
  * @brief  Initializes the TIMx Plus Mode according to the specified
  *         parameters.
  * @param  TIMx: where x can be  2 or 5 to select the TIM peripheral.
  * @param  TIMx_PLUS_MODE_STATE: eable or disable the plus mode
  * @ex	    TMR_Plus_Mode_Enable
  *         TMR_Plus_Mode_Disable	
  * @retval None
  */
void TMR_SelectPlusMode(TMR_Type* TMRx, uint16_t TMRx_PLUS_MODE_STATE)
{
	/* Check the parameters */
  assert_param(IS_TMR_PLUSMODE_PERIPH(TMRx));
	assert_param(IS_TMR_PLUS_MODE_STATE(TMRx_PLUS_MODE_STATE));
	/*Config TIMx plus mode*/
	if((TMRx == TMR2) || (TMRx == TMR5))
	{
		/*Enable*/
		if(TMRx_PLUS_MODE_STATE)
		{
			TMRx->CTRL1 &= (uint16_t)(~((uint16_t)TMR_Plus_Mode_Enable));
			TMRx->CTRL1 |= TMRx_PLUS_MODE_STATE;
		}
		/*Disable*/
		else
		{
			TMRx->CTRL1 &= (uint16_t)(~((uint16_t)TMR_Plus_Mode_Enable));
			TMRx->CTRL1 |= TMRx_PLUS_MODE_STATE;
		}
	}
}



/**
  * @brief  Initializes the TMRx Channel1 according to the specified
  *         parameters in the TMR_OCInitStruct.
  * @param  TMRx: where x can be  1 to 15 except 6 and 7 to select the TMR peripheral.
  * @param  TMR_OCInitStruct: pointer to a TMR_OCInitType structure
  *         that contains the configuration information for the specified TMR peripheral.
  * @retval None
  */
void TMR_OC1Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

  /* Check the parameters */
  assert_param(IS_TMR_LIST8_PERIPH(TMRx));
  assert_param(IS_TMR_OC_MODE(TMR_OCInitStruct->TMR_OCMode));
  assert_param(IS_TMR_OUTPUT_STATE(TMR_OCInitStruct->TMR_OutputState));
  assert_param(IS_TMR_OC_POLARITY(TMR_OCInitStruct->TMR_OCPolarity));
  /* Disable the Channel 1: Reset the CC1E Bit */
  TMRx->CCE &= (uint16_t)(~(uint16_t)TMR_CCE_C1EN);
  /* Get the TMRx CCE register value */
  tmpccer = TMRx->CCE;
  /* Get the TMRx CR2 register value */
  tmpcr2 =  TMRx->CTRL2;

  /* Get the TMRx CCMR1 register value */
  tmpccmrx = TMRx->CCM1;

  /* Reset the Output Compare Mode Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCM1_OC1MODE));
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCM1_C1SEL));

  /* Select the Output Compare Mode */
  tmpccmrx |= TMR_OCInitStruct->TMR_OCMode;

  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TMR_CCE_C1P));
  /* Set the Output Compare Polarity */
  tmpccer |= TMR_OCInitStruct->TMR_OCPolarity;

  /* Set the Output State */
  tmpccer |= TMR_OCInitStruct->TMR_OutputState;

#ifdef AT32F415xx
	if (TMRx == TMR1)
#elif defined AT32F413xx
    if ((TMRx == TMR1) || (TMRx == TMR8))
#elif defined AT32F403xx
    if ((TMRx == TMR1) || (TMRx == TMR8) || (TMRx == TMR15))
#endif  
  {
    assert_param(IS_TMR_OUTPUTN_STATE(TMR_OCInitStruct->TMR_OutputNState));
    assert_param(IS_TMR_OCN_POLARITY(TMR_OCInitStruct->TMR_OCNPolarity));
    assert_param(IS_TMR_OCNIDLE_STATE(TMR_OCInitStruct->TMR_OCNIdleState));
    assert_param(IS_TMR_OCIDLE_STATE(TMR_OCInitStruct->TMR_OCIdleState));

    /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)TMR_CCE_C1NP));
    /* Set the Output N Polarity */
    tmpccer |= TMR_OCInitStruct->TMR_OCNPolarity;

    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)TMR_CCE_C1NEN));
    /* Set the Output N State */
    tmpccer |= TMR_OCInitStruct->TMR_OutputNState;

    /* Reset the Output Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CTRL2_OC1IS));
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CTRL2_OC1NIS));

    /* Set the Output Idle state */
    tmpcr2 |= TMR_OCInitStruct->TMR_OCIdleState;
    /* Set the Output N Idle state */
    tmpcr2 |= TMR_OCInitStruct->TMR_OCNIdleState;
  }

  /* Write to TMRx CR2 */
  TMRx->CTRL2 = tmpcr2;

  /* Write to TMRx CCMR1 */
  TMRx->CCM1 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TMRx->CC1 = TMR_OCInitStruct->TMR_Pulse;

  /* Write to TMRx CCE */
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Initializes the TMRx Channel2 according to the specified
  *         parameters in the TMR_OCInitStruct.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5, 8, 9, 12 or 15 to select
  *         the TMR peripheral.
  * @param  TMR_OCInitStruct: pointer to a TMR_OCInitType structure
  *         that contains the configuration information for the specified TMR peripheral.
  * @retval None
  */
void TMR_OC2Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  assert_param(IS_TMR_OC_MODE(TMR_OCInitStruct->TMR_OCMode));
  assert_param(IS_TMR_OUTPUT_STATE(TMR_OCInitStruct->TMR_OutputState));
  assert_param(IS_TMR_OC_POLARITY(TMR_OCInitStruct->TMR_OCPolarity));
  /* Disable the Channel 2: Reset the CC2E Bit */
  TMRx->CCE &= (uint16_t)(~((uint16_t)TMR_CCE_C2EN));

  /* Get the TMRx CCE register value */
  tmpccer = TMRx->CCE;
  /* Get the TMRx CR2 register value */
  tmpcr2 =  TMRx->CTRL2;

  /* Get the TMRx CCMR1 register value */
  tmpccmrx = TMRx->CCM1;

  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCM1_OC2MODE));
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCM1_C2SEL));

  /* Select the Output Compare Mode */
  tmpccmrx |= (uint16_t)(TMR_OCInitStruct->TMR_OCMode << 8);

  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TMR_CCE_C2P));
  /* Set the Output Compare Polarity */
  tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OCPolarity << 4);

  /* Set the Output State */
  tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OutputState << 4);

#ifdef AT32F415xx
	if (TMRx == TMR1)
#elif defined AT32F413xx
    if ((TMRx == TMR1) || (TMRx == TMR8))
#elif defined AT32F403xx
    if ((TMRx == TMR1) || (TMRx == TMR8) || (TMRx == TMR15))
#endif
  {
    assert_param(IS_TMR_OUTPUTN_STATE(TMR_OCInitStruct->TMR_OutputNState));
    assert_param(IS_TMR_OCN_POLARITY(TMR_OCInitStruct->TMR_OCNPolarity));
    assert_param(IS_TMR_OCNIDLE_STATE(TMR_OCInitStruct->TMR_OCNIdleState));
    assert_param(IS_TMR_OCIDLE_STATE(TMR_OCInitStruct->TMR_OCIdleState));

    /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)TMR_CCE_C2NP));
    /* Set the Output N Polarity */
    tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OCNPolarity << 4);

    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)TMR_CCE_C2NEN));
    /* Set the Output N State */
    tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OutputNState << 4);

    /* Reset the Output Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CTRL2_OC2IS));
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CTRL2_OC2NIS));

    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(TMR_OCInitStruct->TMR_OCIdleState << 2);
    /* Set the Output N Idle state */
    tmpcr2 |= (uint16_t)(TMR_OCInitStruct->TMR_OCNIdleState << 2);
  }

  /* Write to TMRx CR2 */
  TMRx->CTRL2 = tmpcr2;

  /* Write to TMRx CCMR1 */
  TMRx->CCM1 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TMRx->CC2 = TMR_OCInitStruct->TMR_Pulse;

  /* Write to TMRx CCE */
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Initializes the TMRx Channel3 according to the specified
  *         parameters in the TMR_OCInitStruct.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_OCInitStruct: pointer to a TMR_OCInitType structure
  *         that contains the configuration information for the specified TMR peripheral.
  * @retval None
  */
void TMR_OC3Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_OC_MODE(TMR_OCInitStruct->TMR_OCMode));
  assert_param(IS_TMR_OUTPUT_STATE(TMR_OCInitStruct->TMR_OutputState));
  assert_param(IS_TMR_OC_POLARITY(TMR_OCInitStruct->TMR_OCPolarity));
  /* Disable the Channel 2: Reset the CC2E Bit */
  TMRx->CCE &= (uint16_t)(~((uint16_t)TMR_CCE_C3EN));

  /* Get the TMRx CCE register value */
  tmpccer = TMRx->CCE;
  /* Get the TMRx CR2 register value */
  tmpcr2 =  TMRx->CTRL2;

  /* Get the TMRx CCMR2 register value */
  tmpccmrx = TMRx->CCM2;

  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCM2_OC3MODE));
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCM2_C3SEL));
  /* Select the Output Compare Mode */
  tmpccmrx |= TMR_OCInitStruct->TMR_OCMode;

  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TMR_CCE_C3P));
  /* Set the Output Compare Polarity */
  tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OCPolarity << 8);

  /* Set the Output State */
  tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OutputState << 8);

#ifdef AT32F415xx
	if (TMRx == TMR1)
#elif defined AT32F413xx
    if ((TMRx == TMR1) || (TMRx == TMR8))
#elif defined AT32F403xx
    if ((TMRx == TMR1) || (TMRx == TMR8) || (TMRx == TMR15))
#endif
  {
    assert_param(IS_TMR_OUTPUTN_STATE(TMR_OCInitStruct->TMR_OutputNState));
    assert_param(IS_TMR_OCN_POLARITY(TMR_OCInitStruct->TMR_OCNPolarity));
    assert_param(IS_TMR_OCNIDLE_STATE(TMR_OCInitStruct->TMR_OCNIdleState));
    assert_param(IS_TMR_OCIDLE_STATE(TMR_OCInitStruct->TMR_OCIdleState));

    /* Reset the Output N Polarity level */
    tmpccer &= (uint16_t)(~((uint16_t)TMR_CCE_C3NP));
    /* Set the Output N Polarity */
    tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OCNPolarity << 8);
    /* Reset the Output N State */
    tmpccer &= (uint16_t)(~((uint16_t)TMR_CCE_C3NEN));

    /* Set the Output N State */
    tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OutputNState << 8);
    /* Reset the Output Compare and Output Compare N IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CTRL2_OC3IS));
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CTRL2_OC3NIS));
    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(TMR_OCInitStruct->TMR_OCIdleState << 4);
    /* Set the Output N Idle state */
    tmpcr2 |= (uint16_t)(TMR_OCInitStruct->TMR_OCNIdleState << 4);
  }

  /* Write to TMRx CR2 */
  TMRx->CTRL2 = tmpcr2;

  /* Write to TMRx CCMR2 */
  TMRx->CCM2 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TMRx->CC3 = TMR_OCInitStruct->TMR_Pulse;

  /* Write to TMRx CCE */
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Initializes the TMRx Channel4 according to the specified
  *         parameters in the TMR_OCInitStruct.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_OCInitStruct: pointer to a TMR_OCInitType structure
  *         that contains the configuration information for the specified TMR peripheral.
  * @retval None
  */
void TMR_OC4Init(TMR_Type* TMRx, TMR_OCInitType* TMR_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_OC_MODE(TMR_OCInitStruct->TMR_OCMode));
  assert_param(IS_TMR_OUTPUT_STATE(TMR_OCInitStruct->TMR_OutputState));
  assert_param(IS_TMR_OC_POLARITY(TMR_OCInitStruct->TMR_OCPolarity));
  /* Disable the Channel 2: Reset the CC4E Bit */
  TMRx->CCE &= (uint16_t)(~((uint16_t)TMR_CCE_C4EN));

  /* Get the TMRx CCE register value */
  tmpccer = TMRx->CCE;
  /* Get the TMRx CR2 register value */
  tmpcr2 =  TMRx->CTRL2;

  /* Get the TMRx CCMR2 register value */
  tmpccmrx = TMRx->CCM2;

  /* Reset the Output Compare mode and Capture/Compare selection Bits */
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCM2_OC4MODE));
  tmpccmrx &= (uint16_t)(~((uint16_t)TMR_CCM2_CC4S));

  /* Select the Output Compare Mode */
  tmpccmrx |= (uint16_t)(TMR_OCInitStruct->TMR_OCMode << 8);

  /* Reset the Output Polarity level */
  tmpccer &= (uint16_t)(~((uint16_t)TMR_CCE_C4P));
  /* Set the Output Compare Polarity */
  tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OCPolarity << 12);

  /* Set the Output State */
  tmpccer |= (uint16_t)(TMR_OCInitStruct->TMR_OutputState << 12);

#ifdef AT32F415xx
	if (TMRx == TMR1)
#elif defined AT32F413xx
    if ((TMRx == TMR1) || (TMRx == TMR8))
#elif defined AT32F403xx
    if ((TMRx == TMR1) || (TMRx == TMR8) || (TMRx == TMR15))
#endif
  {
    assert_param(IS_TMR_OCIDLE_STATE(TMR_OCInitStruct->TMR_OCIdleState));
    /* Reset the Output Compare IDLE State */
    tmpcr2 &= (uint16_t)(~((uint16_t)TMR_CTRL2_OC4IS));
    /* Set the Output Idle state */
    tmpcr2 |= (uint16_t)(TMR_OCInitStruct->TMR_OCIdleState << 6);
  }

  /* Write to TMRx CR2 */
  TMRx->CTRL2 = tmpcr2;

  /* Write to TMRx CCMR2 */
  TMRx->CCM2 = tmpccmrx;

  /* Set the Capture Compare Register value */
  TMRx->CC4 = TMR_OCInitStruct->TMR_Pulse;

  /* Write to TMRx CCE */
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Initializes the TMR peripheral according to the specified
  *         parameters in the TMR_ICInitStruct.
  * @param  TMRx: where x can be  1 to 15 except 6 and 7 to select the TMR peripheral.
  * @param  TMR_ICInitStruct: pointer to a TMR_ICInitType structure
  *         that contains the configuration information for the specified TMR peripheral.
  * @retval None
  */
void TMR_ICInit(TMR_Type* TMRx, TMR_ICInitType* TMR_ICInitStruct)
{
  /* Check the parameters */
  assert_param(IS_TMR_CHANNEL(TMR_ICInitStruct->TMR_Channel));
  assert_param(IS_TMR_IC_SELECTION(TMR_ICInitStruct->TMR_ICSelection));
  assert_param(IS_TMR_IC_DIV(TMR_ICInitStruct->TMR_ICDIV));
  assert_param(IS_TMR_IC_FILTER(TMR_ICInitStruct->TMR_ICFilter));

    if((TMRx == TMR1) || (TMRx == TMR2) ||
#if !defined (AT32F415xx)
     (TMRx == TMR8) ||
#endif
#if defined (AT32F403xx)
     (TMRx == TMR15) || 
#endif

     (TMRx == TMR3) || (TMRx == TMR4) || (TMRx == TMR5))
  {
    assert_param(IS_TMR_IC_POLARITY(TMR_ICInitStruct->TMR_ICPolarity));
  }
  else
  {
    assert_param(IS_TMR_IC_POLARITY_LITE(TMR_ICInitStruct->TMR_ICPolarity));
  }

  if (TMR_ICInitStruct->TMR_Channel == TMR_Channel_1)
  {
    assert_param(IS_TMR_LIST8_PERIPH(TMRx));
    /* TI1 Configuration */
    TI1_Config(TMRx, TMR_ICInitStruct->TMR_ICPolarity,
               TMR_ICInitStruct->TMR_ICSelection,
               TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC1DIV(TMRx, TMR_ICInitStruct->TMR_ICDIV);
  }
  else if (TMR_ICInitStruct->TMR_Channel == TMR_Channel_2)
  {
    assert_param(IS_TMR_LIST6_PERIPH(TMRx));
    /* TI2 Configuration */
    TI2_Config(TMRx, TMR_ICInitStruct->TMR_ICPolarity,
               TMR_ICInitStruct->TMR_ICSelection,
               TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC2DIV(TMRx, TMR_ICInitStruct->TMR_ICDIV);
  }
  else if (TMR_ICInitStruct->TMR_Channel == TMR_Channel_3)
  {
    assert_param(IS_TMR_LIST3_PERIPH(TMRx));
    /* TI3 Configuration */
    TI3_Config(TMRx,  TMR_ICInitStruct->TMR_ICPolarity,
               TMR_ICInitStruct->TMR_ICSelection,
               TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC3DIV(TMRx, TMR_ICInitStruct->TMR_ICDIV);
  }
  else
  {
    assert_param(IS_TMR_LIST3_PERIPH(TMRx));
    /* TI4 Configuration */
    TI4_Config(TMRx, TMR_ICInitStruct->TMR_ICPolarity,
               TMR_ICInitStruct->TMR_ICSelection,
               TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC4DIV(TMRx, TMR_ICInitStruct->TMR_ICDIV);
  }
}

/**
  * @brief  Configures the TMR peripheral according to the specified
  *         parameters in the TMR_ICInitStruct to measure an external PWM signal.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TMR peripheral.
  * @param  TMR_ICInitStruct: pointer to a TMR_ICInitType structure
  *         that contains the configuration information for the specified TMR peripheral.
  * @retval None
  */
void TMR_PWMIConfig(TMR_Type* TMRx, TMR_ICInitType* TMR_ICInitStruct)
{
  uint16_t icoppositepolarity = TMR_ICPolarity_Rising;
  uint16_t icoppositeselection = TMR_ICSelection_DirectTI;
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));

  /* Select the Opposite Input Polarity */
  if (TMR_ICInitStruct->TMR_ICPolarity == TMR_ICPolarity_Rising)
  {
    icoppositepolarity = TMR_ICPolarity_Falling;
  }
  else
  {
    icoppositepolarity = TMR_ICPolarity_Rising;
  }

  /* Select the Opposite Input */
  if (TMR_ICInitStruct->TMR_ICSelection == TMR_ICSelection_DirectTI)
  {
    icoppositeselection = TMR_ICSelection_IndirectTI;
  }
  else
  {
    icoppositeselection = TMR_ICSelection_DirectTI;
  }

  if (TMR_ICInitStruct->TMR_Channel == TMR_Channel_1)
  {
    /* TI1 Configuration */
    TI1_Config(TMRx, TMR_ICInitStruct->TMR_ICPolarity, TMR_ICInitStruct->TMR_ICSelection,
               TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC1DIV(TMRx, TMR_ICInitStruct->TMR_ICDIV);
    /* TI2 Configuration */
    TI2_Config(TMRx, icoppositepolarity, icoppositeselection, TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC2DIV(TMRx, TMR_ICInitStruct->TMR_ICDIV);
  }
  else
  {
    /* TI2 Configuration */
    TI2_Config(TMRx, TMR_ICInitStruct->TMR_ICPolarity, TMR_ICInitStruct->TMR_ICSelection,
               TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC2DIV(TMRx, TMR_ICInitStruct->TMR_ICDIV);
    /* TI1 Configuration */
    TI1_Config(TMRx, icoppositepolarity, icoppositeselection, TMR_ICInitStruct->TMR_ICFilter);
    /* Set the Input Capture Prescaler value */
    TMR_SetIC1DIV(TMRx, TMR_ICInitStruct->TMR_ICDIV);
  }
}

/**
  * @brief  Configures the: Break feature, dead time, Lock level, the OSSI,
  *         the OSSR State and the AOE(automatic output enable).
  * @param  TMRx: where x can be  1 or 8 to select the TMR
  * @param  TMR_BDTRInitStruct: pointer to a TMR_BRKDTInitType structure that
  *         contains the BDTR Register configuration  information for the TMR peripheral.
  * @retval None
  */
void TMR_BRKDTConfig(TMR_Type* TMRx, TMR_BRKDTInitType *TMR_BDTRInitStruct)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST2_PERIPH(TMRx));
  assert_param(IS_TMR_OSIMR_STATE(TMR_BDTRInitStruct->TMR_OSIMRState));
  assert_param(IS_TMR_OSIMI_STATE(TMR_BDTRInitStruct->TMR_OSIMIState));
  assert_param(IS_TMR_LOCK_grade(TMR_BDTRInitStruct->TMR_LOCKgrade));
  assert_param(IS_TMR_BREAK_STATE(TMR_BDTRInitStruct->TMR_Break));
  assert_param(IS_TMR_BREAK_POLARITY(TMR_BDTRInitStruct->TMR_BreakPolarity));
  assert_param(IS_TMR_AUTOMATIC_OUTPUT_STATE(TMR_BDTRInitStruct->TMR_AutomaticOutput));
  /* Set the Lock level, the Break enable Bit and the Ploarity, the OSSR State,
     the OSSI State, the dead time value and the Automatic Output Enable Bit */
  TMRx->BRKDT = (uint32_t)TMR_BDTRInitStruct->TMR_OSIMRState | TMR_BDTRInitStruct->TMR_OSIMIState |
                TMR_BDTRInitStruct->TMR_LOCKgrade | TMR_BDTRInitStruct->TMR_DeadTime |
                TMR_BDTRInitStruct->TMR_Break | TMR_BDTRInitStruct->TMR_BreakPolarity |
                TMR_BDTRInitStruct->TMR_AutomaticOutput;
}

/**
  * @brief  Fills each TMR_TimeBaseInitStruct member with its default value.
  * @param  TMR_TimeBaseInitStruct : pointer to a TMR_TimerBaseInitType
  *         structure which will be initialized.
  * @retval None
  */
void TMR_TimeBaseStructInit(TMR_TimerBaseInitType* TMR_TimeBaseInitStruct)
{
  /* Set the default configuration */
  TMR_TimeBaseInitStruct->TMR_Period = 0xFFFF;
  TMR_TimeBaseInitStruct->TMR_DIV = 0x0000;
  TMR_TimeBaseInitStruct->TMR_ClockDivision = TMR_CKD_DIV1;
  TMR_TimeBaseInitStruct->TMR_CounterMode = TMR_CounterDIR_Up;
  TMR_TimeBaseInitStruct->TMR_RepetitionCounter = 0x0000;
}

/**
  * @brief  Fills each TMR_OCInitStruct member with its default value.
  * @param  TMR_OCInitStruct : pointer to a TMR_OCInitType structure which will
  *         be initialized.
  * @retval None
  */
void TMR_OCStructInit(TMR_OCInitType* TMR_OCInitStruct)
{
  /* Set the default configuration */
  TMR_OCInitStruct->TMR_OCMode = TMR_OCMode_Timing;
  TMR_OCInitStruct->TMR_OutputState = TMR_OutputState_Disable;
  TMR_OCInitStruct->TMR_OutputNState = TMR_OutputNState_Disable;
  TMR_OCInitStruct->TMR_Pulse = 0x0000;
  TMR_OCInitStruct->TMR_OCPolarity = TMR_OCPolarity_High;
  TMR_OCInitStruct->TMR_OCNPolarity = TMR_OCPolarity_High;
  TMR_OCInitStruct->TMR_OCIdleState = TMR_OCIdleState_Reset;
  TMR_OCInitStruct->TMR_OCNIdleState = TMR_OCNIdleState_Reset;
}

/**
  * @brief  Fills each TMR_ICInitStruct member with its default value.
  * @param  TMR_ICInitStruct: pointer to a TMR_ICInitType structure which will
  *         be initialized.
  * @retval None
  */
void TMR_ICStructInit(TMR_ICInitType* TMR_ICInitStruct)
{
  /* Set the default configuration */
  TMR_ICInitStruct->TMR_Channel = TMR_Channel_1;
  TMR_ICInitStruct->TMR_ICPolarity = TMR_ICPolarity_Rising;
  TMR_ICInitStruct->TMR_ICSelection = TMR_ICSelection_DirectTI;
  TMR_ICInitStruct->TMR_ICDIV = TMR_ICDIV_DIV1;
  TMR_ICInitStruct->TMR_ICFilter = 0x00;
}

/**
  * @brief  Fills each TMR_BDTRInitStruct member with its default value.
  * @param  TMR_BDTRInitStruct: pointer to a TMR_BRKDTInitType structure which
  *         will be initialized.
  * @retval None
  */
void TMR_BRKDTStructInit(TMR_BRKDTInitType* TMR_BDTRInitStruct)
{
  /* Set the default configuration */
  TMR_BDTRInitStruct->TMR_OSIMRState = TMR_OSIMRState_Disable;
  TMR_BDTRInitStruct->TMR_OSIMIState = TMR_OSIMIState_Disable;
  TMR_BDTRInitStruct->TMR_LOCKgrade = TMR_LOCKgrade_OFF;
  TMR_BDTRInitStruct->TMR_DeadTime = 0x00;
  TMR_BDTRInitStruct->TMR_Break = TMR_Break_Disable;
  TMR_BDTRInitStruct->TMR_BreakPolarity = TMR_BreakPolarity_Low;
  TMR_BDTRInitStruct->TMR_AutomaticOutput = TMR_AutomaticOutput_Disable;
}

/**
  * @brief  Enables or disables the specified TMR peripheral.
  * @param  TMRx: where x can be 1 to 15 to select the TMRx peripheral.
  * @param  NewState: new state of the TMRx peripheral.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_Cmd(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the TMR Counter */
    TMRx->CTRL1 |= TMR_CTRL1_CNTEN;
  }
  else
  {
    /* Disable the TMR Counter */
    TMRx->CTRL1 &= (uint16_t)(~((uint16_t)TMR_CTRL1_CNTEN));
  }
}

/**
  * @brief  Enables or disables the TMR peripheral Main Outputs.
  * @param  TMRx: where x can be 1, 8, 15 to select the TMRx peripheral.
  * @param  NewState: new state of the TMR peripheral Main Outputs.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_CtrlPWMOutputs(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST2_PERIPH(TMRx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the TMR Main Output */
    TMRx->BRKDT |= TMR_BRKDT_MOEN;
  }
  else
  {
    /* Disable the TMR Main Output */
    TMRx->BRKDT &= (uint16_t)(~((uint16_t)TMR_BRKDT_MOEN));
  }
}

/**
  * @brief  Enables or disables the specified TMR interrupts.
  * @param  TMRx: where x can be 1 to 15 to select the TMRx peripheral.
  * @param  TMR_INT: specifies the TMR interrupts sources to be enabled or disabled.
  *   This parameter can be any combination of the following values:
  *     @arg TMR_INT_Overflow: TMR update Interrupt source
  *     @arg TMR_INT_CC1: TMR Capture Compare 1 Interrupt source
  *     @arg TMR_INT_CC2: TMR Capture Compare 2 Interrupt source
  *     @arg TMR_INT_CC3: TMR Capture Compare 3 Interrupt source
  *     @arg TMR_INT_CC4: TMR Capture Compare 4 Interrupt source
  *     @arg TMR_INT_HALL: TMR Commutation Interrupt source
  *     @arg TMR_INT_Trigger: TMR Trigger Interrupt source
  *     @arg TMR_INT_Break: TMR Break Interrupt source
  * @note
  *   - TMR6 and TMR7 can only generate an update interrupt.
  *   - TMR9, TMR12 and TMR15 can have only TMR_INT_Overflow, TMR_INT_CC1,
  *      TMR_INT_CC2 or TMR_INT_Trigger.
  *   - TMR10, TMR11, TMR13, TMR14 can have TMR_INT_Overflow or TMR_INT_CC1.
  *   - TMR_INT_Break is used only with TMR1, TMR8 and TMR15.
  *   - TMR_INT_HALL is used only with TMR1, TMR8, TMR15.
  * @param  NewState: new state of the TMR interrupts.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_INTConfig(TMR_Type* TMRx, uint16_t TMR_INT, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  assert_param(IS_TMR_INT(TMR_INT));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the Interrupt sources */
    TMRx->DIE |= TMR_INT;
  }
  else
  {
    /* Disable the Interrupt sources */
    TMRx->DIE &= (uint16_t)~TMR_INT;
  }
}

/**
  * @brief  Configures the TMRx event to be generate by software.
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @param  TMR_EventSource: specifies the event source.
  *   This parameter can be one or more of the following values:
  *     @arg TMR_EventSource_Update: Timer update Event source
  *     @arg TMR_EventSource_CC1: Timer Capture Compare 1 Event source
  *     @arg TMR_EventSource_CC2: Timer Capture Compare 2 Event source
  *     @arg TMR_EventSource_CC3: Timer Capture Compare 3 Event source
  *     @arg TMR_EventSource_CC4: Timer Capture Compare 4 Event source
  *     @arg TMR_EventSource_HALL: Timer COM event source
  *     @arg TMR_EventSource_Trigger: Timer Trigger Event source
  *     @arg TMR_EventSource_Break: Timer Break event source
  * @note
  *   - TMR6 and TMR7 can only generate an update event.
  *   - TMR_EventSource_HALL and TMR_EventSource_Break are used only with TMR1 and TMR8.
  * @retval None
  */
void TMR_GenerateEvent(TMR_Type* TMRx, uint16_t TMR_EventSource)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  assert_param(IS_TMR_EVENT_SOURCE(TMR_EventSource));

  /* Set the event sources */
  TMRx->EVEG = TMR_EventSource;
}

/**
  * @brief  Configures the TMRx's DMA interface.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5, 8, 15 to select
  *   the TMR peripheral.
  * @param  TMR_DMABase: DMA Base address.
  *   This parameter can be one of the following values:
  *     @arg TMR_DMABase_CTRL1, TMR_DMABase_CTRL2, TMR_DMABase_SMC,
  *          TMR_DMABase_DIE, TMR_DMABase_STS, TMR_DMABase_EVEG,
  *          TMR_DMABase_CCM1, TMR_DMABase_CCM2, TMR_DMABase_CCE,
  *          TMR_DMABase_CNT, TMR_DMABase_DIV, TMR_DMABase_AR,
  *          TMR_DMABase_RC, TMR_DMABase_CC1, TMR_DMABase_CC2,
  *          TMR_DMABase_CC3, TMR_DMABase_CC4, TMR_DMABase_BRKDT,
  *          TMR_DMABase_DMAC.
  * @param  TMR_DMABurstLength: DMA Burst length.
  *   This parameter can be one value between:
  *   TMR_DMABurstLength_1Transfer and TMR_DMABurstLength_18Transfers.
  * @retval None
  */
void TMR_DMAConfig(TMR_Type* TMRx, uint16_t TMR_DMABase, uint16_t TMR_DMABurstLength)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST4_PERIPH(TMRx));
  assert_param(IS_TMR_DMA_BASE(TMR_DMABase));
  assert_param(IS_TMR_DMA_LENGTH(TMR_DMABurstLength));
  /* Set the DMA Base and the DMA Burst Length */
  TMRx->DMAC = TMR_DMABase | TMR_DMABurstLength;
}

/**
  * @brief  Enables or disables the TMRx's DMA Requests.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5, 6, 7, 8, 15
  *   to select the TMR peripheral.
  * @param  TMR_DMASource: specifies the DMA Request sources.
  *   This parameter can be any combination of the following values:
  *     @arg TMR_DMA_Update: TMR update Interrupt source
  *     @arg TMR_DMA_CC1: TMR Capture Compare 1 DMA source
  *     @arg TMR_DMA_CC2: TMR Capture Compare 2 DMA source
  *     @arg TMR_DMA_CC3: TMR Capture Compare 3 DMA source
  *     @arg TMR_DMA_CC4: TMR Capture Compare 4 DMA source
  *     @arg TMR_DMA_HALL: TMR Commutation DMA source
  *     @arg TMR_DMA_Trigger: TMR Trigger DMA source
  * @param  NewState: new state of the DMA Request sources.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_DMACmd(TMR_Type* TMRx, uint16_t TMR_DMASource, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST9_PERIPH(TMRx));
  assert_param(IS_TMR_DMA_SOURCE(TMR_DMASource));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the DMA sources */
    TMRx->DIE |= TMR_DMASource;
  }
  else
  {
    /* Disable the DMA sources */
    TMRx->DIE &= (uint16_t)~TMR_DMASource;
  }
}

/**
  * @brief  Configures the TMRx internal Clock
  * @param  TMRx: where x can be  1, 2, 3, 4, 5, 8, 9, 12 or 15
  *         to select the TMR peripheral.
  * @retval None
  */
void TMR_InternalClockConfig(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  /* Disable slave mode to clock the prescaler directly with the internal clock */
  TMRx->SMC &=  (uint16_t)(~((uint16_t)TMR_SMC_SMSEL));
}

/**
  * @brief  Configures the TMRx Internal Trigger as External Clock
  * @param  TMRx: where x can be  1, 2, 3, 4, 5, 9, 12 or 15 to select the TMR peripheral.
  * @param  TMR_ITRSource: Trigger source.
  *   This parameter can be one of the following values:
  * @param  TMR_TRGSEL_ITR0: Internal Trigger 0
  * @param  TMR_TRGSEL_ITR1: Internal Trigger 1
  * @param  TMR_TRGSEL_ITR2: Internal Trigger 2
  * @param  TMR_TRGSEL_ITR3: Internal Trigger 3
  * @retval None
  */
void TMR_ITRxExternalClockConfig(TMR_Type* TMRx, uint16_t TMR_InputTriggerSource)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  assert_param(IS_TMR_INTERNAL_TRIGGER_SELECTION(TMR_InputTriggerSource));
  /* Select the Internal Trigger */
  TMR_SelectInputTrigger(TMRx, TMR_InputTriggerSource);
  /* Select the External clock mode1 */
  TMRx->SMC |= TMR_SlaveMode_External1;
}

/**
  * @brief  Configures the TMRx Trigger as External Clock
  * @param  TMRx: where x can be  1, 2, 3, 4, 5, 9, 12 or 15 to select the TMR peripheral.
  * @param  TMR_TIxExternalCLKSource: Trigger source.
  *   This parameter can be one of the following values:
  *     @arg TMR_TIxExternalCLK1Source_TI1ED: TI1 Edge Detector
  *     @arg TMR_TIxExternalCLK1Source_TI1: Filtered Timer Input 1
  *     @arg TMR_TIxExternalCLK1Source_TI2: Filtered Timer Input 2
  * @param  TMR_ICPolarity: specifies the TIx Polarity.
  *   This parameter can be one of the following values:
  *     @arg TMR_ICPolarity_Rising
  *     @arg TMR_ICPolarity_Falling
  * @param  ICFilter : specifies the filter value.
  *   This parameter must be a value between 0x0 and 0xF.
  * @retval None
  */
void TMR_TIxExternalClockConfig(TMR_Type* TMRx, uint16_t TMR_TIxExternalCLKSource,
                                uint16_t TMR_ICPolarity, uint16_t ICFilter)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  assert_param(IS_TMR_TIXCLK_SOURCE(TMR_TIxExternalCLKSource));
  assert_param(IS_TMR_IC_POLARITY(TMR_ICPolarity));
  assert_param(IS_TMR_IC_FILTER(ICFilter));

  /* Configure the Timer Input Clock Source */
  if (TMR_TIxExternalCLKSource == TMR_TIxExternalCLK1Source_TI2)
  {
    TI2_Config(TMRx, TMR_ICPolarity, TMR_ICSelection_DirectTI, ICFilter);
  }
  else
  {
    TI1_Config(TMRx, TMR_ICPolarity, TMR_ICSelection_DirectTI, ICFilter);
  }

  /* Select the Trigger source */
  TMR_SelectInputTrigger(TMRx, TMR_TIxExternalCLKSource);
  /* Select the External clock mode1 */
  TMRx->SMC |= TMR_SlaveMode_External1;
}

/**
  * @brief  Configures the External clock Mode1
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_ExtTRGPrescaler: The external Trigger Prescaler.
  *   This parameter can be one of the following values:
  *     @arg TMR_ExtTRGDIV_OFF: ETRP Prescaler OFF.
  *     @arg TMR_ExtTRGDIV_DIV2: ETRP frequency divided by 2.
  *     @arg TMR_ExtTRGDIV_DIV4: ETRP frequency divided by 4.
  *     @arg TMR_ExtTRGDIV_DIV8: ETRP frequency divided by 8.
  * @param  TMR_ExtTRGPolarity: The external Trigger Polarity.
  *   This parameter can be one of the following values:
  *     @arg TMR_ExtTRGPolarity_Inverted: active low or falling edge active.
  *     @arg TMR_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TMR_ETRClockMode1Config(TMR_Type* TMRx, uint16_t TMR_ExtTRGPrescaler, uint16_t TMR_ExtTRGPolarity,
                             uint16_t ExtTRGFilter)
{
  uint16_t tmpsmcr = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_EXT_DIV(TMR_ExtTRGPrescaler));
  assert_param(IS_TMR_EXT_POLARITY(TMR_ExtTRGPolarity));
  assert_param(IS_TMR_EXT_FILTER(ExtTRGFilter));
  /* Configure the ETR Clock source */
  TMR_ETRConfig(TMRx, TMR_ExtTRGPrescaler, TMR_ExtTRGPolarity, ExtTRGFilter);

  /* Get the TMRx SMCR register value */
  tmpsmcr = TMRx->SMC;
  /* Reset the SMS Bits */
  tmpsmcr &= (uint16_t)(~((uint16_t)TMR_SMC_SMSEL));
  /* Select the External clock mode1 */
  tmpsmcr |= TMR_SlaveMode_External1;
  /* Select the Trigger selection : ETRF */
  tmpsmcr &= (uint16_t)(~((uint16_t)TMR_SMC_TRGSEL));
  tmpsmcr |= TMR_TRGSEL_ETRF;
  /* Write to TMRx SMCR */
  TMRx->SMC = tmpsmcr;
}

/**
  * @brief  Configures the External clock Mode2
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_ExtTRGPrescaler: The external Trigger Prescaler.
  *   This parameter can be one of the following values:
  *     @arg TMR_ExtTRGDIV_OFF: ETRP Prescaler OFF.
  *     @arg TMR_ExtTRGDIV_DIV2: ETRP frequency divided by 2.
  *     @arg TMR_ExtTRGDIV_DIV4: ETRP frequency divided by 4.
  *     @arg TMR_ExtTRGDIV_DIV8: ETRP frequency divided by 8.
  * @param  TMR_ExtTRGPolarity: The external Trigger Polarity.
  *   This parameter can be one of the following values:
  *     @arg TMR_ExtTRGPolarity_Inverted: active low or falling edge active.
  *     @arg TMR_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TMR_ETRClockMode2Config(TMR_Type* TMRx, uint16_t TMR_ExtTRGPrescaler,
                             uint16_t TMR_ExtTRGPolarity, uint16_t ExtTRGFilter)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_EXT_DIV(TMR_ExtTRGPrescaler));
  assert_param(IS_TMR_EXT_POLARITY(TMR_ExtTRGPolarity));
  assert_param(IS_TMR_EXT_FILTER(ExtTRGFilter));
  /* Configure the ETR Clock source */
  TMR_ETRConfig(TMRx, TMR_ExtTRGPrescaler, TMR_ExtTRGPolarity, ExtTRGFilter);
  /* Enable the External clock mode2 */
  TMRx->SMC |= TMR_SMC_ECLKEN;
}

/**
  * @brief  Configures the TMRx External Trigger (ETR).
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_ExtTRGPrescaler: The external Trigger Prescaler.
  *   This parameter can be one of the following values:
  *     @arg TMR_ExtTRGDIV_OFF: ETRP Prescaler OFF.
  *     @arg TMR_ExtTRGDIV_DIV2: ETRP frequency divided by 2.
  *     @arg TMR_ExtTRGDIV_DIV4: ETRP frequency divided by 4.
  *     @arg TMR_ExtTRGDIV_DIV8: ETRP frequency divided by 8.
  * @param  TMR_ExtTRGPolarity: The external Trigger Polarity.
  *   This parameter can be one of the following values:
  *     @arg TMR_ExtTRGPolarity_Inverted: active low or falling edge active.
  *     @arg TMR_ExtTRGPolarity_NonInverted: active high or rising edge active.
  * @param  ExtTRGFilter: External Trigger Filter.
  *   This parameter must be a value between 0x00 and 0x0F
  * @retval None
  */
void TMR_ETRConfig(TMR_Type* TMRx, uint16_t TMR_ExtTRGPrescaler, uint16_t TMR_ExtTRGPolarity,
                   uint16_t ExtTRGFilter)
{
  uint16_t tmpsmcr = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_EXT_DIV(TMR_ExtTRGPrescaler));
  assert_param(IS_TMR_EXT_POLARITY(TMR_ExtTRGPolarity));
  assert_param(IS_TMR_EXT_FILTER(ExtTRGFilter));
  tmpsmcr = TMRx->SMC;
  /* Reset the ETR Bits */
  tmpsmcr &= SMC_ETR_Mask;
  /* Set the Prescaler, the Filter value and the Polarity */
  tmpsmcr |= (uint16_t)(TMR_ExtTRGPrescaler | (uint16_t)(TMR_ExtTRGPolarity | (uint16_t)(ExtTRGFilter << (uint16_t)8)));
  /* Write to TMRx SMCR */
  TMRx->SMC = tmpsmcr;
}

/**
  * @brief  Configures the TMRx Prescaler.
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @param  Prescaler: specifies the Prescaler Register value
  * @param  TMR_PSCReloadMode: specifies the TMR Prescaler Reload mode
  *   This parameter can be one of the following values:
  *     @arg TMR_DIVReloadMode_Update: The Prescaler is loaded at the update event.
  *     @arg TMR_DIVReloadMode_Immediate: The Prescaler is loaded immediately.
  * @retval None
  */
void TMR_DIVConfig(TMR_Type* TMRx, uint16_t Prescaler, uint16_t TMR_PSCReloadMode)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  assert_param(IS_TMR_DIV_RELOAD(TMR_PSCReloadMode));
  /* Set the Prescaler value */
  TMRx->DIV = Prescaler;
  /* Set or reset the UG Bit */
  TMRx->EVEG = TMR_PSCReloadMode;
}

/**
  * @brief  Specifies the TMRx Counter Mode to be used.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_CounterMode: specifies the Counter Mode to be used
  *   This parameter can be one of the following values:
  *     @arg TMR_CounterDIR_Up: TMR Up Counting Mode
  *     @arg TMR_CounterDIR_Down: TMR Down Counting Mode
  *     @arg TMR_CounterDIR_CenterAligned1: TMR Center Aligned Mode1
  *     @arg TMR_CounterDIR_CenterAligned2: TMR Center Aligned Mode2
  *     @arg TMR_CounterDIR_CenterAligned3: TMR Center Aligned Mode3
  * @retval None
  */
void TMR_CounterModeConfig(TMR_Type* TMRx, uint16_t TMR_CounterMode)
{
  uint16_t tmpcr1 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_COUNTER_DIR(TMR_CounterMode));
  tmpcr1 = TMRx->CTRL1;
  /* Reset the CMS and DIR Bits */
  tmpcr1 &= (uint16_t)(~((uint16_t)(TMR_CTRL1_DIR | TMR_CTRL1_CMSEL)));
  /* Set the Counter Mode */
  tmpcr1 |= TMR_CounterMode;
  /* Write to TMRx CR1 register */
  TMRx->CTRL1 = tmpcr1;
}

/**
  * @brief  Selects the Input Trigger source
  * @param  TMRx: where x can be  1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TMR peripheral.
  * @param  TMR_InputTriggerSource: The Input Trigger source.
  *   This parameter can be one of the following values:
  *     @arg TMR_TRGSEL_ITR0: Internal Trigger 0
  *     @arg TMR_TRGSEL_ITR1: Internal Trigger 1
  *     @arg TMR_TRGSEL_ITR2: Internal Trigger 2
  *     @arg TMR_TRGSEL_ITR3: Internal Trigger 3
  *     @arg TMR_TRGSEL_TI1F_ED: TI1 Edge Detector
  *     @arg TMR_TRGSEL_TI1FP1: Filtered Timer Input 1
  *     @arg TMR_TRGSEL_TI2FP2: Filtered Timer Input 2
  *     @arg TMR_TRGSEL_ETRF: External Trigger input
  * @retval None
  */
void TMR_SelectInputTrigger(TMR_Type* TMRx, uint16_t TMR_InputTriggerSource)
{
  uint16_t tmpsmcr = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  assert_param(IS_TMR_TRIGGER_SELECTION(TMR_InputTriggerSource));
  /* Get the TMRx SMCR register value */
  tmpsmcr = TMRx->SMC;
  /* Reset the TS Bits */
  tmpsmcr &= (uint16_t)(~((uint16_t)TMR_SMC_TRGSEL));
  /* Set the Input Trigger source */
  tmpsmcr |= TMR_InputTriggerSource;
  /* Write to TMRx SMCR */
  TMRx->SMC = tmpsmcr;
}

/**
  * @brief  Configures the TMRx Encoder Interface.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_EncoderMode: specifies the TMRx Encoder Mode.
  *   This parameter can be one of the following values:
  *     @arg TMR_EncoderMode_TI1: Counter counts on TI1FP1 edge depending on TI2FP2 level.
  *     @arg TMR_EncoderMode_TI2: Counter counts on TI2FP2 edge depending on TI1FP1 level.
  *     @arg TMR_EncoderMode_TI12: Counter counts on both TI1FP1 and TI2FP2 edges depending
  *                                on the level of the other input.
  * @param  TMR_IC1Polarity: specifies the IC1 Polarity
  *   This parameter can be one of the following values:
  *     @arg TMR_ICPolarity_Falling: IC Falling edge.
  *     @arg TMR_ICPolarity_Rising: IC Rising edge.
  * @param  TMR_IC2Polarity: specifies the IC2 Polarity
  *   This parameter can be one of the following values:
  *     @arg TMR_ICPolarity_Falling: IC Falling edge.
  *     @arg TMR_ICPolarity_Rising: IC Rising edge.
  * @retval None
  */
void TMR_EncoderInterfaceConfig(TMR_Type* TMRx, uint16_t TMR_EncoderMode,
                                uint16_t TMR_IC1Polarity, uint16_t TMR_IC2Polarity)
{
  uint16_t tmpsmcr = 0;
  uint16_t tmpccmr1 = 0;
  uint16_t tmpccer = 0;

  /* Check the parameters */
  assert_param(IS_TMR_LIST5_PERIPH(TMRx));
  assert_param(IS_TMR_ENCODER_MODE(TMR_EncoderMode));
  assert_param(IS_TMR_IC_POLARITY(TMR_IC1Polarity));
  assert_param(IS_TMR_IC_POLARITY(TMR_IC2Polarity));

  /* Get the TMRx SMCR register value */
  tmpsmcr = TMRx->SMC;

  /* Get the TMRx CCMR1 register value */
  tmpccmr1 = TMRx->CCM1;

  /* Get the TMRx CCE register value */
  tmpccer = TMRx->CCE;

  /* Set the encoder Mode */
  tmpsmcr &= (uint16_t)(~((uint16_t)TMR_SMC_SMSEL));
  tmpsmcr |= TMR_EncoderMode;

  /* Select the Capture Compare 1 and the Capture Compare 2 as input */
  tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)TMR_CCM1_C1SEL)) & (uint16_t)(~((uint16_t)TMR_CCM1_C2SEL)));
  tmpccmr1 |= TMR_CCM1_C1SEL_0 | TMR_CCM1_C2SEL_0;

  /* Set the TI1 and the TI2 Polarities */
  tmpccer &= (uint16_t)(((uint16_t)~((uint16_t)TMR_CCE_C1P)) & ((uint16_t)~((uint16_t)TMR_CCE_C2P)));
  tmpccer |= (uint16_t)(TMR_IC1Polarity | (uint16_t)(TMR_IC2Polarity << (uint16_t)4));

  /* Write to TMRx SMCR */
  TMRx->SMC = tmpsmcr;
  /* Write to TMRx CCMR1 */
  TMRx->CCM1 = tmpccmr1;
  /* Write to TMRx CCE */
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Forces the TMRx output 1 waveform to active or inactive level.
  * @param  TMRx: where x can be  1 to 15 except 6 and 7 to select the TMR peripheral.
  * @param  TMR_ForcedAction: specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the following values:
  *     @arg TMR_ForcedAction_Active: Force active level on OC1REF
  *     @arg TMR_ForcedAction_InActive: Force inactive level on OC1REF.
  * @retval None
  */
void TMR_ForcedOC1Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST8_PERIPH(TMRx));
  assert_param(IS_TMR_FORCED_ACTION(TMR_ForcedAction));
  tmpccmr1 = TMRx->CCM1;
  /* Reset the OC1M Bits */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCM1_OC1MODE);
  /* Configure The Forced output Mode */
  tmpccmr1 |= TMR_ForcedAction;
  /* Write to TMRx CCMR1 register */
  TMRx->CCM1 = tmpccmr1;
}

/**
  * @brief  Forces the TMRx output 2 waveform to active or inactive level.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TMR peripheral.
  * @param  TMR_ForcedAction: specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the following values:
  *     @arg TMR_ForcedAction_Active: Force active level on OC2REF
  *     @arg TMR_ForcedAction_InActive: Force inactive level on OC2REF.
  * @retval None
  */
void TMR_ForcedOC2Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  assert_param(IS_TMR_FORCED_ACTION(TMR_ForcedAction));
  tmpccmr1 = TMRx->CCM1;
  /* Reset the OC2M Bits */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCM1_OC2MODE);
  /* Configure The Forced output Mode */
  tmpccmr1 |= (uint16_t)(TMR_ForcedAction << 8);
  /* Write to TMRx CCMR1 register */
  TMRx->CCM1 = tmpccmr1;
}

/**
  * @brief  Forces the TMRx output 3 waveform to active or inactive level.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_ForcedAction: specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the following values:
  *     @arg TMR_ForcedAction_Active: Force active level on OC3REF
  *     @arg TMR_ForcedAction_InActive: Force inactive level on OC3REF.
  * @retval None
  */
void TMR_ForcedOC3Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_FORCED_ACTION(TMR_ForcedAction));
  tmpccmr2 = TMRx->CCM2;
  /* Reset the OC1M Bits */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCM2_OC3MODE);
  /* Configure The Forced output Mode */
  tmpccmr2 |= TMR_ForcedAction;
  /* Write to TMRx CCMR2 register */
  TMRx->CCM2 = tmpccmr2;
}

/**
  * @brief  Forces the TMRx output 4 waveform to active or inactive level.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_ForcedAction: specifies the forced Action to be set to the output waveform.
  *   This parameter can be one of the following values:
  *     @arg TMR_ForcedAction_Active: Force active level on OC4REF
  *     @arg TMR_ForcedAction_InActive: Force inactive level on OC4REF.
  * @retval None
  */
void TMR_ForcedOC4Config(TMR_Type* TMRx, uint16_t TMR_ForcedAction)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_FORCED_ACTION(TMR_ForcedAction));
  tmpccmr2 = TMRx->CCM2;
  /* Reset the OC2M Bits */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCM2_OC4MODE);
  /* Configure The Forced output Mode */
  tmpccmr2 |= (uint16_t)(TMR_ForcedAction << 8);
  /* Write to TMRx CCMR2 register */
  TMRx->CCM2 = tmpccmr2;
}

/**
  * @brief  Enables or disables TMRx peripheral Preload register on ARR.
  * @param  TMRx: where x can be  1 to 15 to select the TMR peripheral.
  * @param  NewState: new state of the TMRx peripheral Preload register
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_ARPreloadConfig(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the ARR Preload Bit */
    TMRx->CTRL1 |= TMR_CTRL1_ARPEN;
  }
  else
  {
    /* Reset the ARR Preload Bit */
    TMRx->CTRL1 &= (uint16_t)~((uint16_t)TMR_CTRL1_ARPEN);
  }
}

/**
  * @brief  Selects the TMR peripheral Commutation event.
  * @param  TMRx: where x can be  1, 8, 15 to select the TMRx peripheral
  * @param  NewState: new state of the Commutation event.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_SelectHALL(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST2_PERIPH(TMRx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the COM Bit */
    TMRx->CTRL2 |= TMR_CTRL2_CUSEL;
  }
  else
  {
    /* Reset the COM Bit */
    TMRx->CTRL2 &= (uint16_t)~((uint16_t)TMR_CTRL2_CUSEL);
  }
}

/**
  * @brief  Selects the TMRx peripheral Capture Compare DMA source.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5, 8, 15 to select
  *         the TMR peripheral.
  * @param  NewState: new state of the Capture Compare DMA source
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_SelectCCDMA(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST4_PERIPH(TMRx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the CCDS Bit */
    TMRx->CTRL2 |= TMR_CTRL2_CDSEL;
  }
  else
  {
    /* Reset the CCDS Bit */
    TMRx->CTRL2 &= (uint16_t)~((uint16_t)TMR_CTRL2_CDSEL);
  }
}

/**
  * @brief  Sets or Resets the TMR peripheral Capture Compare Preload Control bit.
  * @param  TMRx: where x can be   1, 2, 3, 4, 5, 8 or 15
  *         to select the TMRx peripheral
  * @param  NewState: new state of the Capture Compare Preload Control bit
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_CCPreloadControl(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST5_PERIPH(TMRx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the CCPC Bit */
    TMRx->CTRL2 |= TMR_CTRL2_CPC;
  }
  else
  {
    /* Reset the CCPC Bit */
    TMRx->CTRL2 &= (uint16_t)~((uint16_t)TMR_CTRL2_CPC);
  }
}

/**
  * @brief  Enables or disables the TMRx peripheral Preload register on CCR1.
  * @param  TMRx: where x can be  1 to 15 except 6 and 7 to select the TMR peripheral.
  * @param  TMR_OCPreload: new state of the TMRx peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg TMR_OCPreload_Enable
  *     @arg TMR_OCPreload_Disable
  * @retval None
  */
void TMR_OC1PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST8_PERIPH(TMRx));
  assert_param(IS_TMR_OCPRELOAD_STATE(TMR_OCPreload));
  tmpccmr1 = TMRx->CCM1;
  /* Reset the OC1PE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCM1_OC1PEN);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr1 |= TMR_OCPreload;
  /* Write to TMRx CCMR1 register */
  TMRx->CCM1 = tmpccmr1;
}

/**
  * @brief  Enables or disables the TMRx peripheral Preload register on CCR2.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5, 8, 9, 12 or 15 to select
  *         the TMR peripheral.
  * @param  TMR_OCPreload: new state of the TMRx peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg TMR_OCPreload_Enable
  *     @arg TMR_OCPreload_Disable
  * @retval None
  */
void TMR_OC2PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  assert_param(IS_TMR_OCPRELOAD_STATE(TMR_OCPreload));
  tmpccmr1 = TMRx->CCM1;
  /* Reset the OC2PE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCM1_OC2PEN);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr1 |= (uint16_t)(TMR_OCPreload << 8);
  /* Write to TMRx CCMR1 register */
  TMRx->CCM1 = tmpccmr1;
}

/**
  * @brief  Enables or disables the TMRx peripheral Preload register on CCR3.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_OCPreload: new state of the TMRx peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg TMR_OCPreload_Enable
  *     @arg TMR_OCPreload_Disable
  * @retval None
  */
void TMR_OC3PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_OCPRELOAD_STATE(TMR_OCPreload));
  tmpccmr2 = TMRx->CCM2;
  /* Reset the OC3PE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCM2_OC3PEN);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr2 |= TMR_OCPreload;
  /* Write to TMRx CCMR2 register */
  TMRx->CCM2 = tmpccmr2;
}

/**
  * @brief  Enables or disables the TMRx peripheral Preload register on CCR4.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_OCPreload: new state of the TMRx peripheral Preload register
  *   This parameter can be one of the following values:
  *     @arg TMR_OCPreload_Enable
  *     @arg TMR_OCPreload_Disable
  * @retval None
  */
void TMR_OC4PreloadConfig(TMR_Type* TMRx, uint16_t TMR_OCPreload)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_OCPRELOAD_STATE(TMR_OCPreload));
  tmpccmr2 = TMRx->CCM2;
  /* Reset the OC4PE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCM2_OC4PE);
  /* Enable or Disable the Output Compare Preload feature */
  tmpccmr2 |= (uint16_t)(TMR_OCPreload << 8);
  /* Write to TMRx CCMR2 register */
  TMRx->CCM2 = tmpccmr2;
}

/**
  * @brief  Configures the TMRx Output Compare 1 Fast feature.
  * @param  TMRx: where x can be  1 to 15 except 6 and 7 to select the TMR peripheral.
  * @param  TMR_OCFast: new state of the Output Compare Fast Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg TMR_OCFast_Enable: TMR output compare fast enable
  *     @arg TMR_OCFast_Disable: TMR output compare fast disable
  * @retval None
  */
void TMR_OC1FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST8_PERIPH(TMRx));
  assert_param(IS_TMR_OCFAST_STATE(TMR_OCFast));
  /* Get the TMRx CCMR1 register value */
  tmpccmr1 = TMRx->CCM1;
  /* Reset the OC1FE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCM1_OC1FEN);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr1 |= TMR_OCFast;
  /* Write to TMRx CCMR1 */
  TMRx->CCM1 = tmpccmr1;
}

/**
  * @brief  Configures the TMRx Output Compare 2 Fast feature.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5, 8, 9, 12 or 15 to select
  *         the TMR peripheral.
  * @param  TMR_OCFast: new state of the Output Compare Fast Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg TMR_OCFast_Enable: TMR output compare fast enable
  *     @arg TMR_OCFast_Disable: TMR output compare fast disable
  * @retval None
  */
void TMR_OC2FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  assert_param(IS_TMR_OCFAST_STATE(TMR_OCFast));
  /* Get the TMRx CCMR1 register value */
  tmpccmr1 = TMRx->CCM1;
  /* Reset the OC2FE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCM1_OC2FNE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr1 |= (uint16_t)(TMR_OCFast << 8);
  /* Write to TMRx CCMR1 */
  TMRx->CCM1 = tmpccmr1;
}

/**
  * @brief  Configures the TMRx Output Compare 3 Fast feature.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_OCFast: new state of the Output Compare Fast Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg TMR_OCFast_Enable: TMR output compare fast enable
  *     @arg TMR_OCFast_Disable: TMR output compare fast disable
  * @retval None
  */
void TMR_OC3FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_OCFAST_STATE(TMR_OCFast));
  /* Get the TMRx CCMR2 register value */
  tmpccmr2 = TMRx->CCM2;
  /* Reset the OC3FE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCM2_OC3FEN);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr2 |= TMR_OCFast;
  /* Write to TMRx CCMR2 */
  TMRx->CCM2 = tmpccmr2;
}

/**
  * @brief  Configures the TMRx Output Compare 4 Fast feature.
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_OCFast: new state of the Output Compare Fast Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg TMR_OCFast_Enable: TMR output compare fast enable
  *     @arg TMR_OCFast_Disable: TMR output compare fast disable
  * @retval None
  */
void TMR_OC4FastConfig(TMR_Type* TMRx, uint16_t TMR_OCFast)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_OCFAST_STATE(TMR_OCFast));
  /* Get the TMRx CCMR2 register value */
  tmpccmr2 = TMRx->CCM2;
  /* Reset the OC4FE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCM2_OC4FE);
  /* Enable or Disable the Output Compare Fast Bit */
  tmpccmr2 |= (uint16_t)(TMR_OCFast << 8);
  /* Write to TMRx CCMR2 */
  TMRx->CCM2 = tmpccmr2;
}

/**
  * @brief  Clears or safeguards the OCREF1 signal on an external event
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_OCClear: new state of the Output Compare Clear Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg TMR_OCClear_Enable: TMR Output clear enable
  *     @arg TMR_OCClear_Disable: TMR Output clear disable
  * @retval None
  */
void TMR_ClearOC1Ref(TMR_Type* TMRx, uint16_t TMR_OCClear)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_OCCLEAR_STATE(TMR_OCClear));

  tmpccmr1 = TMRx->CCM1;

  /* Reset the OC1CE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCM1_C1CDIS);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr1 |= TMR_OCClear;
  /* Write to TMRx CCMR1 register */
  TMRx->CCM1 = tmpccmr1;
}

/**
  * @brief  Clears or safeguards the OCREF2 signal on an external event
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_OCClear: new state of the Output Compare Clear Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg TMR_OCClear_Enable: TMR Output clear enable
  *     @arg TMR_OCClear_Disable: TMR Output clear disable
  * @retval None
  */
void TMR_ClearOC2Ref(TMR_Type* TMRx, uint16_t TMR_OCClear)
{
  uint16_t tmpccmr1 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_OCCLEAR_STATE(TMR_OCClear));
  tmpccmr1 = TMRx->CCM1;
  /* Reset the OC2CE Bit */
  tmpccmr1 &= (uint16_t)~((uint16_t)TMR_CCM1_OC2CDIS);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr1 |= (uint16_t)(TMR_OCClear << 8);
  /* Write to TMRx CCMR1 register */
  TMRx->CCM1 = tmpccmr1;
}

/**
  * @brief  Clears or safeguards the OCREF3 signal on an external event
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_OCClear: new state of the Output Compare Clear Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg TMR_OCClear_Enable: TMR Output clear enable
  *     @arg TMR_OCClear_Disable: TMR Output clear disable
  * @retval None
  */
void TMR_ClearOC3Ref(TMR_Type* TMRx, uint16_t TMR_OCClear)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_OCCLEAR_STATE(TMR_OCClear));
  tmpccmr2 = TMRx->CCM2;
  /* Reset the OC3CE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCM2_OC3CDIS);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr2 |= TMR_OCClear;
  /* Write to TMRx CCMR2 register */
  TMRx->CCM2 = tmpccmr2;
}

/**
  * @brief  Clears or safeguards the OCREF4 signal on an external event
  * @param  TMRx: where x can be  1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_OCClear: new state of the Output Compare Clear Enable Bit.
  *   This parameter can be one of the following values:
  *     @arg TMR_OCClear_Enable: TMR Output clear enable
  *     @arg TMR_OCClear_Disable: TMR Output clear disable
  * @retval None
  */
void TMR_ClearOC4Ref(TMR_Type* TMRx, uint16_t TMR_OCClear)
{
  uint16_t tmpccmr2 = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_OCCLEAR_STATE(TMR_OCClear));
  tmpccmr2 = TMRx->CCM2;
  /* Reset the OC4CE Bit */
  tmpccmr2 &= (uint16_t)~((uint16_t)TMR_CCM2_OC4CDIS);
  /* Enable or Disable the Output Compare Clear Bit */
  tmpccmr2 |= (uint16_t)(TMR_OCClear << 8);
  /* Write to TMRx CCMR2 register */
  TMRx->CCM2 = tmpccmr2;
}

/**
  * @brief  Configures the TMRx channel 1 polarity.
  * @param  TMRx: where x can be 1 to 15 except 6 and 7 to select the TMR peripheral.
  * @param  TMR_OCPolarity: specifies the OC1 Polarity
  *   This parameter can be one of the following values:
  *     @arg TMR_OCPolarity_High: Output Compare active high
  *     @arg TMR_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC1PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST8_PERIPH(TMRx));
  assert_param(IS_TMR_OC_POLARITY(TMR_OCPolarity));
  tmpccer = TMRx->CCE;
  /* Set or Reset the CC1P Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCE_C1P);
  tmpccer |= TMR_OCPolarity;
  /* Write to TMRx CCE register */
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Configures the TMRx Channel 1N polarity.
  * @param  TMRx: where x can be 1, 8, 15 to select the TMR peripheral.
  * @param  TMR_OCNPolarity: specifies the OC1N Polarity
  *   This parameter can be one of the following values:
  *     @arg TMR_OCNPolarity_High: Output Compare active high
  *     @arg TMR_OCNPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC1NPolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCNPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST2_PERIPH(TMRx));
  assert_param(IS_TMR_OCN_POLARITY(TMR_OCNPolarity));

  tmpccer = TMRx->CCE;
  /* Set or Reset the CC1NP Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCE_C1NP);
  tmpccer |= TMR_OCNPolarity;
  /* Write to TMRx CCE register */
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Configures the TMRx channel 2 polarity.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TMR peripheral.
  * @param  TMR_OCPolarity: specifies the OC2 Polarity
  *   This parameter can be one of the following values:
  *     @arg TMR_OCPolarity_High: Output Compare active high
  *     @arg TMR_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC2PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  assert_param(IS_TMR_OC_POLARITY(TMR_OCPolarity));
  tmpccer = TMRx->CCE;
  /* Set or Reset the CC2P Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCE_C2P);
  tmpccer |= (uint16_t)(TMR_OCPolarity << 4);
  /* Write to TMRx CCE register */
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Configures the TMRx Channel 2N polarity.
  * @param  TMRx: where x can be 1 or 8 to select the TMR peripheral.
  * @param  TMR_OCNPolarity: specifies the OC2N Polarity
  *   This parameter can be one of the following values:
  *     @arg TMR_OCNPolarity_High: Output Compare active high
  *     @arg TMR_OCNPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC2NPolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCNPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST1_PERIPH(TMRx));
  assert_param(IS_TMR_OCN_POLARITY(TMR_OCNPolarity));

  tmpccer = TMRx->CCE;
  /* Set or Reset the CC2NP Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCE_C2NP);
  tmpccer |= (uint16_t)(TMR_OCNPolarity << 4);
  /* Write to TMRx CCE register */
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Configures the TMRx channel 3 polarity.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_OCPolarity: specifies the OC3 Polarity
  *   This parameter can be one of the following values:
  *     @arg TMR_OCPolarity_High: Output Compare active high
  *     @arg TMR_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC3PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_OC_POLARITY(TMR_OCPolarity));
  tmpccer = TMRx->CCE;
  /* Set or Reset the CC3P Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCE_C3P);
  tmpccer |= (uint16_t)(TMR_OCPolarity << 8);
  /* Write to TMRx CCE register */
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Configures the TMRx Channel 3N polarity.
  * @param  TMRx: where x can be 1 or 8 to select the TMR peripheral.
  * @param  TMR_OCNPolarity: specifies the OC3N Polarity
  *   This parameter can be one of the following values:
  *     @arg TMR_OCNPolarity_High: Output Compare active high
  *     @arg TMR_OCNPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC3NPolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCNPolarity)
{
  uint16_t tmpccer = 0;

  /* Check the parameters */
  assert_param(IS_TMR_LIST1_PERIPH(TMRx));
  assert_param(IS_TMR_OCN_POLARITY(TMR_OCNPolarity));

  tmpccer = TMRx->CCE;
  /* Set or Reset the CC3NP Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCE_C3NP);
  tmpccer |= (uint16_t)(TMR_OCNPolarity << 8);
  /* Write to TMRx CCER register */
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Configures the TMRx channel 4 polarity.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_OCPolarity: specifies the OC4 Polarity
  *   This parameter can be one of the following values:
  *     @arg TMR_OCPolarity_High: Output Compare active high
  *     @arg TMR_OCPolarity_Low: Output Compare active low
  * @retval None
  */
void TMR_OC4PolarityConfig(TMR_Type* TMRx, uint16_t TMR_OCPolarity)
{
  uint16_t tmpccer = 0;
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_OC_POLARITY(TMR_OCPolarity));
  tmpccer = TMRx->CCE;
  /* Set or Reset the CC4P Bit */
  tmpccer &= (uint16_t)~((uint16_t)TMR_CCE_C4P);
  tmpccer |= (uint16_t)(TMR_OCPolarity << 12);
  /* Write to TMRx CCE register */
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Enables or disables the TMR Capture Compare Channel x.
  * @param  TMRx: where x can be 1 to 15 except 6 and 7 to select the TMR peripheral.
  * @param  TMR_Channel: specifies the TMR Channel
  *   This parameter can be one of the following values:
  *     @arg TMR_Channel_1: TMR Channel 1
  *     @arg TMR_Channel_2: TMR Channel 2
  *     @arg TMR_Channel_3: TMR Channel 3
  *     @arg TMR_Channel_4: TMR Channel 4
  * @param  TMR_CCx: specifies the TMR Channel CCxE bit new state.
  *   This parameter can be: TMR_CCx_Enable or TMR_CCx_Disable.
  * @retval None
  */
void TMR_CCxCmd(TMR_Type* TMRx, uint16_t TMR_Channel, uint16_t TMR_CCx)
{
  uint16_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_TMR_LIST8_PERIPH(TMRx));
  assert_param(IS_TMR_CHANNEL(TMR_Channel));
  assert_param(IS_TMR_CCX(TMR_CCx));

  tmp = CCE_CCE_Set << TMR_Channel;

  /* Reset the CCxE Bit */
  TMRx->CCE &= (uint16_t)~ tmp;

  /* Set or reset the CCxE Bit */
  TMRx->CCE |=  (uint16_t)(TMR_CCx << TMR_Channel);
}

/**
  * @brief  Enables or disables the TMR Capture Compare Channel xN.
  * @param  TMRx: where x can be 1, 8, 15 to select the TMR peripheral.
  * @param  TMR_Channel: specifies the TMR Channel
  *   This parameter can be one of the following values:
  *     @arg TMR_Channel_1: TMR Channel 1
  *     @arg TMR_Channel_2: TMR Channel 2
  *     @arg TMR_Channel_3: TMR Channel 3
  * @param  TMR_CCxN: specifies the TMR Channel CCxNE bit new state.
  *   This parameter can be: TMR_CCxN_Enable or TMR_CCxN_Disable.
  * @retval None
  */
void TMR_CCxNCmd(TMR_Type* TMRx, uint16_t TMR_Channel, uint16_t TMR_CCxN)
{
  uint16_t tmp = 0;

  /* Check the parameters */
  assert_param(IS_TMR_LIST2_PERIPH(TMRx));
  assert_param(IS_TMR_COMPLEMENTARY_CHANNEL(TMR_Channel));
  assert_param(IS_TMR_CCXN(TMR_CCxN));

  tmp = CCE_CCNE_Set << TMR_Channel;

  /* Reset the CCxNE Bit */
  TMRx->CCE &= (uint16_t) ~tmp;

  /* Set or reset the CCxNE Bit */
  TMRx->CCE |=  (uint16_t)(TMR_CCxN << TMR_Channel);
}

/**
  * @brief  Selects the TMR Output Compare Mode.
  * @note   This function disables the selected channel before changing the Output
  *         Compare Mode.
  *         User has to enable this channel using TMR_CCxCmd and TMR_CCxNCmd functions.
  * @param  TMRx: where x can be 1 to 15 except 6 and 7 to select the TMR peripheral.
  * @param  TMR_Channel: specifies the TMR Channel
  *   This parameter can be one of the following values:
  *     @arg TMR_Channel_1: TMR Channel 1
  *     @arg TMR_Channel_2: TMR Channel 2
  *     @arg TMR_Channel_3: TMR Channel 3
  *     @arg TMR_Channel_4: TMR Channel 4
  * @param  TMR_OCMode: specifies the TMR Output Compare Mode.
  *   This parameter can be one of the following values:
  *     @arg TMR_OCMode_Timing
  *     @arg TMR_OCMode_Active
  *     @arg TMR_OCMode_Toggle
  *     @arg TMR_OCMode_PWM1
  *     @arg TMR_OCMode_PWM2
  *     @arg TMR_ForcedAction_Active
  *     @arg TMR_ForcedAction_InActive
  * @retval None
  */
void TMR_SelectOCxM(TMR_Type* TMRx, uint16_t TMR_Channel, uint16_t TMR_OCMode)
{
  uint32_t tmp = 0;
  uint16_t tmp1 = 0;

  /* Check the parameters */
  assert_param(IS_TMR_LIST8_PERIPH(TMRx));
  assert_param(IS_TMR_CHANNEL(TMR_Channel));
  assert_param(IS_TMR_OCM(TMR_OCMode));

  tmp = (uint32_t) TMRx;
  tmp += CCMR_Offset;

  tmp1 = CCE_CCE_Set << (uint16_t)TMR_Channel;

  /* Disable the Channel: Reset the CCxE Bit */
  TMRx->CCE &= (uint16_t) ~tmp1;

  if((TMR_Channel == TMR_Channel_1) || (TMR_Channel == TMR_Channel_3))
  {
    tmp += (TMR_Channel >> 1);

    /* Reset the OCxM bits in the CCMRx register */
    *(__IO uint32_t *) tmp &= (uint32_t)~((uint32_t)TMR_CCM1_OC1MODE);

    /* Configure the OCxM bits in the CCMRx register */
    *(__IO uint32_t *) tmp |= TMR_OCMode;
  }
  else
  {
    tmp += (uint16_t)(TMR_Channel - (uint16_t)4) >> (uint16_t)1;

    /* Reset the OCxM bits in the CCMRx register */
    *(__IO uint32_t *) tmp &= (uint32_t)~((uint32_t)TMR_CCM1_OC2MODE);

    /* Configure the OCxM bits in the CCMRx register */
    *(__IO uint32_t *) tmp |= (uint16_t)(TMR_OCMode << 8);
  }
}

/**
  * @brief  Enables or Disables the TMRx Update event.
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @param  NewState: new state of the TMRx UDIS bit
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_UpdateDisableConfig(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the Update Disable Bit */
    TMRx->CTRL1 |= TMR_CTRL1_UEVDIS;
  }
  else
  {
    /* Reset the Update Disable Bit */
    TMRx->CTRL1 &= (uint16_t)~((uint16_t)TMR_CTRL1_UEVDIS);
  }
}

/**
  * @brief  Configures the TMRx Update Request Interrupt source.
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @param  TMR_UpdateSource: specifies the Update source.
  *   This parameter can be one of the following values:
  *     @arg TMR_UpdateSource_Regular: Source of update is the counter overflow/underflow
                                       or the setting of UG bit, or an update generation
                                       through the slave mode controller.
  *     @arg TMR_UpdateSource_Global: Source of update is counter overflow/underflow.
  * @retval None
  */
void TMR_UpdateRequestConfig(TMR_Type* TMRx, uint16_t TMR_UpdateSource)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  assert_param(IS_TMR_UPDATE_SOURCE(TMR_UpdateSource));

  if (TMR_UpdateSource != TMR_UpdateSource_Global)
  {
    /* Set the URS Bit */
    TMRx->CTRL1 |= TMR_CTRL1_UVERS;
  }
  else
  {
    /* Reset the URS Bit */
    TMRx->CTRL1 &= (uint16_t)~((uint16_t)TMR_CTRL1_UVERS);
  }
}

/**
  * @brief  Enables or disables the TMRx's Hall sensor interface.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  NewState: new state of the TMRx Hall sensor interface.
  *   This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TMR_SelectHallSensor(TMR_Type* TMRx, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Set the TI1S Bit */
    TMRx->CTRL2 |= TMR_CTRL2_TI1SEL;
  }
  else
  {
    /* Reset the TI1S Bit */
    TMRx->CTRL2 &= (uint16_t)~((uint16_t)TMR_CTRL2_TI1SEL);
  }
}

/**
  * @brief  Selects the TMRx's One Pulse Mode.
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @param  TMR_OPMode: specifies the OPM Mode to be used.
  *   This parameter can be one of the following values:
  *     @arg TMR_OPMode_Once
  *     @arg TMR_OPMode_Repetitive
  * @retval None
  */
void TMR_SelectOnePulseMode(TMR_Type* TMRx, uint16_t TMR_OPMode)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  assert_param(IS_TMR_OPM_MODE(TMR_OPMode));
  /* Reset the OPM Bit */
  TMRx->CTRL1 &= (uint16_t)~((uint16_t)TMR_CTRL1_OPMODE);
  /* Configure the OPM Mode */
  TMRx->CTRL1 |= TMR_OPMode;
}

/**
  * @brief  Selects the TMRx Trigger Output Mode.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5, 6, 7, 8, 9, 12 or 15 to select the TMR peripheral.
  * @param  TMR_TRGOSource: specifies the Trigger Output source.
  *   This paramter can be one of the following values:
  *
  *  - For all TMRx
  *     @arg TMR_TRGOSource_Reset:  The UG bit in the TMR_EGR register is used as the trigger output (TRGO).
  *     @arg TMR_TRGOSource_Enable: The Counter Enable CEN is used as the trigger output (TRGO).
  *     @arg TMR_TRGOSource_Update: The update event is selected as the trigger output (TRGO).
  *
  *  - For all TMRx except TMR6 and TMR7
  *     @arg TMR_TRGOSource_OC1: The trigger output sends a positive pulse when the CC1IF flag
  *                              is to be set, as soon as a capture or compare match occurs (TRGO).
  *     @arg TMR_TRGOSource_OC1Ref: OC1REF signal is used as the trigger output (TRGO).
  *     @arg TMR_TRGOSource_OC2Ref: OC2REF signal is used as the trigger output (TRGO).
  *     @arg TMR_TRGOSource_OC3Ref: OC3REF signal is used as the trigger output (TRGO).
  *     @arg TMR_TRGOSource_OC4Ref: OC4REF signal is used as the trigger output (TRGO).
  *
  * @retval None
  */
void TMR_SelectOutputTrigger(TMR_Type* TMRx, uint16_t TMR_TRGOSource)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST7_PERIPH(TMRx));
  assert_param(IS_TMR_TRGO_SOURCE(TMR_TRGOSource));
  /* Reset the MMS Bits */
  TMRx->CTRL2 &= (uint16_t)~((uint16_t)TMR_CTRL2_MMSEL);
  /* Select the TRGO source */
  TMRx->CTRL2 |=  TMR_TRGOSource;
}

/**
  * @brief  Selects the TMRx Slave Mode.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TMR peripheral.
  * @param  TMR_SlaveMode: specifies the Timer Slave Mode.
  *   This parameter can be one of the following values:
  *     @arg TMR_SlaveMode_Reset: Rising edge of the selected trigger signal (TRGI) re-initializes
  *                               the counter and triggers an update of the registers.
  *     @arg TMR_SlaveMode_Gate:     The counter clock is enabled when the trigger signal (TRGI) is high.
  *     @arg TMR_SlaveMode_Trigger:   The counter starts at a rising edge of the trigger TRGI.
  *     @arg TMR_SlaveMode_External1: Rising edges of the selected trigger (TRGI) clock the counter.
  * @retval None
  */
void TMR_SelectSlaveMode(TMR_Type* TMRx, uint16_t TMR_SlaveMode)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  assert_param(IS_TMR_SLAVE_MODE(TMR_SlaveMode));
  /* Reset the SMS Bits */
  TMRx->SMC &= (uint16_t)~((uint16_t)TMR_SMC_SMSEL);
  /* Select the Slave Mode */
  TMRx->SMC |= TMR_SlaveMode;
}

/**
  * @brief  Sets or Resets the TMRx Master/Slave Mode.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TMR peripheral.
  * @param  TMR_MasterSlaveMode: specifies the Timer Master Slave Mode.
  *   This parameter can be one of the following values:
  *     @arg TMR_MasterSlaveMode_Enable: synchronization between the current timer
  *                                      and its slaves (through TRGO).
  *     @arg TMR_MasterSlaveMode_Disable: No action
  * @retval None
  */
void TMR_SelectMasterSlaveMode(TMR_Type* TMRx, uint16_t TMR_MasterSlaveMode)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  assert_param(IS_TMR_MSMODE_STATE(TMR_MasterSlaveMode));
  /* Reset the MSM Bit */
  TMRx->SMC &= (uint16_t)~((uint16_t)TMR_SMC_MSMODE);

  /* Set or Reset the MSM Bit */
  TMRx->SMC |= TMR_MasterSlaveMode;
}

/**
  * @brief  Sets the TMRx Counter Register value
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @param  Counter: specifies the Counter register new value.
  * @retval None
  */
void TMR_SetCounter(TMR_Type* TMRx, uint32_t Counter)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  /* Set the Counter Register value */
  TMRx->CNT = Counter;
}

/**
  * @brief  Sets the TMRx Autoreload Register value
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @param  Autoreload: specifies the Autoreload register new value.
  * @retval None
  */
void TMR_SetAutoreload(TMR_Type* TMRx, uint32_t Autoreload)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  /* Set the Autoreload Register value */
  TMRx->AR = Autoreload;
}

/**
  * @brief  Sets the TMRx Capture Compare1 Register value
  * @param  TMRx: where x can be 1 to 15 except 6 and 7 to select the TMR peripheral.
  * @param  Compare1: specifies the Capture Compare1 register new value.
  * @retval None
  */
void TMR_SetCompare1(TMR_Type* TMRx, uint32_t Compare1)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST8_PERIPH(TMRx));
  /* Set the Capture Compare1 Register value */
  TMRx->CC1 = Compare1;
}

/**
  * @brief  Sets the TMRx Capture Compare2 Register value
  * @param  TMRx: where x can be 1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TMR peripheral.
  * @param  Compare2: specifies the Capture Compare2 register new value.
  * @retval None
  */
void TMR_SetCompare2(TMR_Type* TMRx, uint32_t Compare2)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  /* Set the Capture Compare2 Register value */
  TMRx->CC2 = Compare2;
}

/**
  * @brief  Sets the TMRx Capture Compare3 Register value
  * @param  TMRx: where x can be 1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  Compare3: specifies the Capture Compare3 register new value.
  * @retval None
  */
void TMR_SetCompare3(TMR_Type* TMRx, uint32_t Compare3)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  /* Set the Capture Compare3 Register value */
  TMRx->CC3 = Compare3;
}

/**
  * @brief  Sets the TMRx Capture Compare4 Register value
  * @param  TMRx: where x can be 1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  Compare4: specifies the Capture Compare4 register new value.
  * @retval None
  */
void TMR_SetCompare4(TMR_Type* TMRx, uint32_t Compare4)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  /* Set the Capture Compare4 Register value */
  TMRx->CC4 = Compare4;
}

/**
  * @brief  Sets the TMRx Input Capture 1 prescaler.
  * @param  TMRx: where x can be 1 to 15 except 6 and 7 to select the TMR peripheral.
  * @param  TMR_ICPSC: specifies the Input Capture1 prescaler new value.
  *   This parameter can be one of the following values:
  *     @arg TMR_ICDIV_DIV1: no prescaler
  *     @arg TMR_ICDIV_DIV2: capture is done once every 2 events
  *     @arg TMR_ICDIV_DIV4: capture is done once every 4 events
  *     @arg TMR_ICDIV_DIV8: capture is done once every 8 events
  * @retval None
  */
void TMR_SetIC1DIV(TMR_Type* TMRx, uint16_t TMR_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST8_PERIPH(TMRx));
  assert_param(IS_TMR_IC_DIV(TMR_ICPSC));
  /* Reset the IC1PSC Bits */
  TMRx->CCM1 &= (uint16_t)~((uint16_t)TMR_CCM1_IC1DIV);
  /* Set the IC1PSC value */
  TMRx->CCM1 |= TMR_ICPSC;
}

/**
  * @brief  Sets the TMRx Input Capture 2 prescaler.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TMR peripheral.
  * @param  TMR_ICPSC: specifies the Input Capture2 prescaler new value.
  *   This parameter can be one of the following values:
  *     @arg TMR_ICDIV_DIV1: no prescaler
  *     @arg TMR_ICDIV_DIV2: capture is done once every 2 events
  *     @arg TMR_ICDIV_DIV4: capture is done once every 4 events
  *     @arg TMR_ICDIV_DIV8: capture is done once every 8 events
  * @retval None
  */
void TMR_SetIC2DIV(TMR_Type* TMRx, uint16_t TMR_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  assert_param(IS_TMR_IC_DIV(TMR_ICPSC));
  /* Reset the IC2PSC Bits */
  TMRx->CCM1 &= (uint16_t)~((uint16_t)TMR_CCM1_IC2DIV);
  /* Set the IC2PSC value */
  TMRx->CCM1 |= (uint16_t)(TMR_ICPSC << 8);
}

/**
  * @brief  Sets the TMRx Input Capture 3 prescaler.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_ICPSC: specifies the Input Capture3 prescaler new value.
  *   This parameter can be one of the following values:
  *     @arg TMR_ICDIV_DIV1: no prescaler
  *     @arg TMR_ICDIV_DIV2: capture is done once every 2 events
  *     @arg TMR_ICDIV_DIV4: capture is done once every 4 events
  *     @arg TMR_ICDIV_DIV8: capture is done once every 8 events
  * @retval None
  */
void TMR_SetIC3DIV(TMR_Type* TMRx, uint16_t TMR_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_IC_DIV(TMR_ICPSC));
  /* Reset the IC3PSC Bits */
  TMRx->CCM2 &= (uint16_t)~((uint16_t)TMR_CCM2_IC3DIV);
  /* Set the IC3PSC value */
  TMRx->CCM2 |= TMR_ICPSC;
}

/**
  * @brief  Sets the TMRx Input Capture 4 prescaler.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_ICPSC: specifies the Input Capture4 prescaler new value.
  *   This parameter can be one of the following values:
  *     @arg TMR_ICDIV_DIV1: no prescaler
  *     @arg TMR_ICDIV_DIV2: capture is done once every 2 events
  *     @arg TMR_ICDIV_DIV4: capture is done once every 4 events
  *     @arg TMR_ICDIV_DIV8: capture is done once every 8 events
  * @retval None
  */
void TMR_SetIC4DIV(TMR_Type* TMRx, uint16_t TMR_ICPSC)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  assert_param(IS_TMR_IC_DIV(TMR_ICPSC));
  /* Reset the IC4PSC Bits */
  TMRx->CCM2 &= (uint16_t)~((uint16_t)TMR_CCM2_IC4DIV);
  /* Set the IC4PSC value */
  TMRx->CCM2 |= (uint16_t)(TMR_ICPSC << 8);
}

/**
  * @brief  Sets the TMRx Clock Division value.
  * @param  TMRx: where x can be  1 to 15 except 6 and 7 to select
  *   the TMR peripheral.
  * @param  TMR_CKD: specifies the clock division value.
  *   This parameter can be one of the following value:
  *     @arg TMR_CKD_DIV1: TDTS = Tck_tim
  *     @arg TMR_CKD_DIV2: TDTS = 2*Tck_tim
  *     @arg TMR_CKD_DIV4: TDTS = 4*Tck_tim
  * @retval None
  */
void TMR_SetClockDivision(TMR_Type* TMRx, uint16_t TMR_CKD)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST8_PERIPH(TMRx));
  assert_param(IS_TMR_CKD_DIV(TMR_CKD));
  /* Reset the CKD Bits */
  TMRx->CTRL1 &= (uint16_t)~((uint16_t)TMR_CTRL1_CLKDIV);
  /* Set the CKD value */
  TMRx->CTRL1 |= TMR_CKD;
}

/**
  * @brief  Gets the TMRx Input Capture 1 value.
  * @param  TMRx: where x can be 1 to 15 except 6 and 7 to select the TMR peripheral.
  * @retval Capture Compare 1 Register value.
  */
uint32_t TMR_GetCapture1(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST8_PERIPH(TMRx));
  /* Get the Capture 1 Register value */
  return TMRx->CC1;
}

/**
  * @brief  Gets the TMRx Input Capture 2 value.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TMR peripheral.
  * @retval Capture Compare 2 Register value.
  */
uint32_t TMR_GetCapture2(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST6_PERIPH(TMRx));
  /* Get the Capture 2 Register value */
  return TMRx->CC2;
}

/**
  * @brief  Gets the TMRx Input Capture 3 value.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @retval Capture Compare 3 Register value.
  */
uint32_t TMR_GetCapture3(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  /* Get the Capture 3 Register value */
  return TMRx->CC3;
}

/**
  * @brief  Gets the TMRx Input Capture 4 value.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @retval Capture Compare 4 Register value.
  */
uint32_t TMR_GetCapture4(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_param(IS_TMR_LIST3_PERIPH(TMRx));
  /* Get the Capture 4 Register value */
  return TMRx->CC4;
}

/**
  * @brief  Gets the TMRx Counter value.
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @retval Counter Register value.
  */
uint32_t TMR_GetCounter(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  /* Get the Counter Register value */
  return TMRx->CNT;
}

/**
  * @brief  Gets the TMRx Prescaler value.
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @retval Prescaler Register value.
  */
uint16_t TMR_GetDIV(TMR_Type* TMRx)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  /* Get the Prescaler Register value */
  return TMRx->DIV;
}

/**
  * @brief  Checks whether the specified TMR flag is set or not.
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @param  TMR_FLAG: specifies the flag to check.
  *   This parameter can be one of the following values:
  *     @arg TMR_FLAG_Update: TMR update Flag
  *     @arg TMR_FLAG_CC1: TMR Capture Compare 1 Flag
  *     @arg TMR_FLAG_CC2: TMR Capture Compare 2 Flag
  *     @arg TMR_FLAG_CC3: TMR Capture Compare 3 Flag
  *     @arg TMR_FLAG_CC4: TMR Capture Compare 4 Flag
  *     @arg TMR_FLAG_HALL: TMR Commutation Flag
  *     @arg TMR_FLAG_Trigger: TMR Trigger Flag
  *     @arg TMR_FLAG_Break: TMR Break Flag
  *     @arg TMR_FLAG_C1OF: TMR Capture Compare 1 overcapture Flag
  *     @arg TMR_FLAG_C2OF: TMR Capture Compare 2 overcapture Flag
  *     @arg TMR_FLAG_C3OF: TMR Capture Compare 3 overcapture Flag
  *     @arg TMR_FLAG_C4OF: TMR Capture Compare 4 overcapture Flag
  * @note
  *   - TMR6 and TMR7 can have only one update flag.
  *   - TMR9, TMR12 and TMR15 can have only TMR_FLAG_Update, TMR_FLAG_CC1,
  *      TMR_FLAG_CC2 or TMR_FLAG_Trigger.
  *   - TMR10, TMR11, TMR13, TMR14 can have TMR_FLAG_Update or TMR_FLAG_CC1.
  *   - TMR_FLAG_Break is used only with TMR1, TMR8 and TMR15.
  *   - TMR_FLAG_HALL is used only with TMR1, TMR8, TMR15.
  * @retval The new state of TMR_FLAG (SET or RESET).
  */
FlagStatus TMR_GetFlagStatus(TMR_Type* TMRx, uint16_t TMR_FLAG)
{
  ITStatus bitstatus = RESET;
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  assert_param(IS_TMR_GET_FLAG(TMR_FLAG));

  if ((TMRx->STS & TMR_FLAG) != (uint16_t)RESET)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/**
  * @brief  Clears the TMRx's pending flags.
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @param  TMR_FLAG: specifies the flag bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg TMR_FLAG_Update: TMR update Flag
  *     @arg TMR_FLAG_CC1: TMR Capture Compare 1 Flag
  *     @arg TMR_FLAG_CC2: TMR Capture Compare 2 Flag
  *     @arg TMR_FLAG_CC3: TMR Capture Compare 3 Flag
  *     @arg TMR_FLAG_CC4: TMR Capture Compare 4 Flag
  *     @arg TMR_FLAG_HALL: TMR Commutation Flag
  *     @arg TMR_FLAG_Trigger: TMR Trigger Flag
  *     @arg TMR_FLAG_Break: TMR Break Flag
  *     @arg TMR_FLAG_C1OF: TMR Capture Compare 1 overcapture Flag
  *     @arg TMR_FLAG_C2OF: TMR Capture Compare 2 overcapture Flag
  *     @arg TMR_FLAG_C3OF: TMR Capture Compare 3 overcapture Flag
  *     @arg TMR_FLAG_C4OF: TMR Capture Compare 4 overcapture Flag
  * @note
  *   - TMR6 and TMR7 can have only one update flag.
  *   - TMR9, TMR12 and TMR15 can have only TMR_FLAG_Update, TMR_FLAG_CC1,
  *      TMR_FLAG_CC2 or TMR_FLAG_Trigger.
  *   - TMR10, TMR11, TMR13, TMR14 can have TMR_FLAG_Update or TMR_FLAG_CC1.
  *   - TMR_FLAG_Break is used only with TMR1, TMR8 and TMR15.
  *   - TMR_FLAG_HALL is used only with TMR1, TMR8, TMR15.
  * @retval None
  */
void TMR_ClearFlag(TMR_Type* TMRx, uint16_t TMR_FLAG)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  assert_param(IS_TMR_CLEAR_FLAG(TMR_FLAG));

  /* Clear the flags */
  TMRx->STS = (uint16_t)~TMR_FLAG;
}

/**
  * @brief  Checks whether the TMR interrupt has occurred or not.
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @param  TMR_INT: specifies the TMR interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg TMR_INT_Overflow: TMR update Interrupt source
  *     @arg TMR_INT_CC1: TMR Capture Compare 1 Interrupt source
  *     @arg TMR_INT_CC2: TMR Capture Compare 2 Interrupt source
  *     @arg TMR_INT_CC3: TMR Capture Compare 3 Interrupt source
  *     @arg TMR_INT_CC4: TMR Capture Compare 4 Interrupt source
  *     @arg TMR_INT_HALL: TMR Commutation Interrupt source
  *     @arg TMR_INT_Trigger: TMR Trigger Interrupt source
  *     @arg TMR_INT_Break: TMR Break Interrupt source
  * @note
  *   - TMR6 and TMR7 can generate only an update interrupt.
  *   - TMR9, TMR12 and TMR15 can have only TMR_INT_Overflow, TMR_INT_CC1,
  *      TMR_INT_CC2 or TMR_INT_Trigger.
  *   - TMR10, TMR11, TMR13, TMR14 can have TMR_INT_Overflow or TMR_INT_CC1.
  *   - TMR_INT_Break is used only with TMR1, TMR8 and TMR15.
  *   - TMR_INT_HALL is used only with TMR1, TMR8, TMR15.
  * @retval The new state of the TMR_INT(SET or RESET).
  */
ITStatus TMR_GetINTStatus(TMR_Type* TMRx, uint16_t TMR_INT)
{
  ITStatus bitstatus = RESET;
  uint16_t itstatus = 0x0, itenable = 0x0;
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  assert_param(IS_TMR_GET_INT(TMR_INT));

  itstatus = TMRx->STS & TMR_INT;

  itenable = TMRx->DIE & TMR_INT;

  if ((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }

  return bitstatus;
}

/**
  * @brief  Clears the TMRx's interrupt pending bits.
  * @param  TMRx: where x can be 1 to 15 to select the TMR peripheral.
  * @param  TMR_INT: specifies the pending bit to clear.
  *   This parameter can be any combination of the following values:
  *     @arg TMR_INT_Overflow: TMR1 update Interrupt source
  *     @arg TMR_INT_CC1: TMR Capture Compare 1 Interrupt source
  *     @arg TMR_INT_CC2: TMR Capture Compare 2 Interrupt source
  *     @arg TMR_INT_CC3: TMR Capture Compare 3 Interrupt source
  *     @arg TMR_INT_CC4: TMR Capture Compare 4 Interrupt source
  *     @arg TMR_INT_HALL: TMR Commutation Interrupt source
  *     @arg TMR_INT_Trigger: TMR Trigger Interrupt source
  *     @arg TMR_INT_Break: TMR Break Interrupt source
  * @note
  *   - TMR6 and TMR7 can generate only an update interrupt.
  *   - TMR9, TMR12 and TMR15 can have only TMR_INT_Overflow, TMR_INT_CC1,
  *      TMR_INT_CC2 or TMR_INT_Trigger.
  *   - TMR10, TMR11, TMR13, TMR14 can have TMR_INT_Overflow or TMR_INT_CC1.
  *   - TMR_INT_Break is used only with TMR1, TMR8 and TMR15.
  *   - TMR_INT_HALL is used only with TMR1, TMR8, TMR15.
  * @retval None
  */
void TMR_ClearITPendingBit(TMR_Type* TMRx, uint16_t TMR_INT)
{
  /* Check the parameters */
  assert_param(IS_TMR_ALL_PERIPH(TMRx));
  assert_param(IS_TMR_INT(TMR_INT));
  /* Clear the INT pending Bit */
  TMRx->STS = (uint16_t)~TMR_INT;
}

/**
  * @brief  Configure the TI1 as Input.
  * @param  TMRx: where x can be 1 to 15 except 6 and 7 to select the TMR peripheral.
  * @param  TMR_ICPolarity : The Input Polarity.
  *   This parameter can be one of the following values:
  *     @arg TMR_ICPolarity_Rising
  *     @arg TMR_ICPolarity_Falling
  * @param  TMR_ICSelection: specifies the input to be used.
  *   This parameter can be one of the following values:
  *     @arg TMR_ICSelection_DirectTI: TMR Input 1 is selected to be connected to IC1.
  *     @arg TMR_ICSelection_IndirectTI: TMR Input 1 is selected to be connected to IC2.
  *     @arg TMR_ICSelection_TRC: TMR Input 1 is selected to be connected to TRC.
  * @param  TMR_ICFilter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI1_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection,
                       uint16_t TMR_ICFilter)
{
  uint16_t tmpccmr1 = 0, tmpccer = 0;
  /* Disable the Channel 1: Reset the CC1E Bit */
  TMRx->CCE &= (uint16_t)~((uint16_t)TMR_CCE_C1EN);
  tmpccmr1 = TMRx->CCM1;
  tmpccer = TMRx->CCE;
  /* Select the Input and set the filter */
  tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)TMR_CCM1_C1SEL)) & ((uint16_t)~((uint16_t)TMR_CCM1_IC1F)));
  tmpccmr1 |= (uint16_t)(TMR_ICSelection | (uint16_t)(TMR_ICFilter << (uint16_t)4));


  if((TMRx == TMR1) || (TMRx == TMR2) ||
#if !defined (AT32F415xx)
     (TMRx == TMR8) ||
#endif
#if defined (AT32F403xx)
     (TMRx == TMR15) ||
#endif
      (TMRx == TMR3) || (TMRx == TMR4) || (TMRx == TMR5))
  {
    /* Select the Polarity and set the CC1E Bit */
    tmpccer &= (uint16_t)~((uint16_t)(TMR_CCE_C1P));
    tmpccer |= (uint16_t)(TMR_ICPolarity | (uint16_t)TMR_CCE_C1EN);
  }
  else
  {
    /* Select the Polarity and set the CC1E Bit */
    tmpccer &= (uint16_t)~((uint16_t)(TMR_CCE_C1P | TMR_CCE_C1NP));
    tmpccer |= (uint16_t)(TMR_ICPolarity | (uint16_t)TMR_CCE_C1EN);
  }

  /* Write to TMRx CCMR1 and CCE registers */
  TMRx->CCM1 = tmpccmr1;
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Configure the TI2 as Input.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5, 8, 9, 12 or 15 to select the TMR peripheral.
  * @param  TMR_ICPolarity : The Input Polarity.
  *   This parameter can be one of the following values:
  *     @arg TMR_ICPolarity_Rising
  *     @arg TMR_ICPolarity_Falling
  * @param  TMR_ICSelection: specifies the input to be used.
  *   This parameter can be one of the following values:
  *     @arg TMR_ICSelection_DirectTI: TMR Input 2 is selected to be connected to IC2.
  *     @arg TMR_ICSelection_IndirectTI: TMR Input 2 is selected to be connected to IC1.
  *     @arg TMR_ICSelection_TRC: TMR Input 2 is selected to be connected to TRC.
  * @param  TMR_ICFilter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI2_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection,
                       uint16_t TMR_ICFilter)
{
  uint16_t tmpccmr1 = 0, tmpccer = 0, tmp = 0;
  /* Disable the Channel 2: Reset the CC2E Bit */
  TMRx->CCE &= (uint16_t)~((uint16_t)TMR_CCE_C2EN);
  tmpccmr1 = TMRx->CCM1;
  tmpccer = TMRx->CCE;
  tmp = (uint16_t)(TMR_ICPolarity << 4);
  /* Select the Input and set the filter */
  tmpccmr1 &= (uint16_t)(((uint16_t)~((uint16_t)TMR_CCM1_C2SEL)) & ((uint16_t)~((uint16_t)TMR_CCM1_IC2DF)));
  tmpccmr1 |= (uint16_t)(TMR_ICFilter << 12);
  tmpccmr1 |= (uint16_t)(TMR_ICSelection << 8);

  if((TMRx == TMR1) || (TMRx == TMR2) ||
#if !defined (AT32F415xx)
     (TMRx == TMR8) ||
#endif
#if defined (AT32F403xx)
     (TMRx == TMR15) ||
#endif
      (TMRx == TMR3) || (TMRx == TMR4) || (TMRx == TMR5))
  {
    /* Select the Polarity and set the CC2E Bit */
    tmpccer &= (uint16_t)~((uint16_t)(TMR_CCE_C2P));
    tmpccer |=  (uint16_t)(tmp | (uint16_t)TMR_CCE_C2EN);
  }
  else
  {
    /* Select the Polarity and set the CC2E Bit */
    tmpccer &= (uint16_t)~((uint16_t)(TMR_CCE_C2P | TMR_CCE_C2NP));
    tmpccer |= (uint16_t)(tmp  | (uint16_t)TMR_CCE_C2EN);
  }

  /* Write to TMRx CCMR1 and CCE registers */
  TMRx->CCM1 = tmpccmr1 ;
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Configure the TI3 as Input.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_ICPolarity : The Input Polarity.
  *   This parameter can be one of the following values:
  *     @arg TMR_ICPolarity_Rising
  *     @arg TMR_ICPolarity_Falling
  * @param  TMR_ICSelection: specifies the input to be used.
  *   This parameter can be one of the following values:
  *     @arg TMR_ICSelection_DirectTI: TMR Input 3 is selected to be connected to IC3.
  *     @arg TMR_ICSelection_IndirectTI: TMR Input 3 is selected to be connected to IC4.
  *     @arg TMR_ICSelection_TRC: TMR Input 3 is selected to be connected to TRC.
  * @param  TMR_ICFilter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI3_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection,
                       uint16_t TMR_ICFilter)
{
  uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;
  /* Disable the Channel 3: Reset the CC3E Bit */
  TMRx->CCE &= (uint16_t)~((uint16_t)TMR_CCE_C3EN);
  tmpccmr2 = TMRx->CCM2;
  tmpccer = TMRx->CCE;
  tmp = (uint16_t)(TMR_ICPolarity << 8);
  /* Select the Input and set the filter */
  tmpccmr2 &= (uint16_t)(((uint16_t)~((uint16_t)TMR_CCM2_C3SEL)) & ((uint16_t)~((uint16_t)TMR_CCM2_IC3DF)));
  tmpccmr2 |= (uint16_t)(TMR_ICSelection | (uint16_t)(TMR_ICFilter << (uint16_t)4));

  if((TMRx == TMR1) || (TMRx == TMR2) ||
#if !defined (AT32F415xx)
     (TMRx == TMR8) ||
#endif
#if defined (AT32F403xx)
     (TMRx == TMR15) ||
#endif
      (TMRx == TMR3) || (TMRx == TMR4) || (TMRx == TMR5))
  {
    /* Select the Polarity and set the CC3E Bit */
    tmpccer &= (uint16_t)~((uint16_t)(TMR_CCE_C3P));
    tmpccer |= (uint16_t)(tmp | (uint16_t)TMR_CCE_C3EN);
  }
  else
  {
    /* Select the Polarity and set the CC3E Bit */
    tmpccer &= (uint16_t)~((uint16_t)(TMR_CCE_C3P | TMR_CCE_C3NP));
    tmpccer |= (uint16_t)(tmp | (uint16_t)TMR_CCE_C3EN);
  }

  /* Write to TMRx CCMR2 and CCE registers */
  TMRx->CCM2 = tmpccmr2;
  TMRx->CCE = tmpccer;
}

/**
  * @brief  Configure the TI4 as Input.
  * @param  TMRx: where x can be 1, 2, 3, 4, 5 or 8 to select the TMR peripheral.
  * @param  TMR_ICPolarity : The Input Polarity.
  *   This parameter can be one of the following values:
  *     @arg TMR_ICPolarity_Rising
  *     @arg TMR_ICPolarity_Falling
  * @param  TMR_ICSelection: specifies the input to be used.
  *   This parameter can be one of the following values:
  *     @arg TMR_ICSelection_DirectTI: TMR Input 4 is selected to be connected to IC4.
  *     @arg TMR_ICSelection_IndirectTI: TMR Input 4 is selected to be connected to IC3.
  *     @arg TMR_ICSelection_TRC: TMR Input 4 is selected to be connected to TRC.
  * @param  TMR_ICFilter: Specifies the Input Capture Filter.
  *   This parameter must be a value between 0x00 and 0x0F.
  * @retval None
  */
static void TI4_Config(TMR_Type* TMRx, uint16_t TMR_ICPolarity, uint16_t TMR_ICSelection,
                       uint16_t TMR_ICFilter)
{
  uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

  /* Disable the Channel 4: Reset the CC4E Bit */
  TMRx->CCE &= (uint16_t)~((uint16_t)TMR_CCE_C4EN);
  tmpccmr2 = TMRx->CCM2;
  tmpccer = TMRx->CCE;
  tmp = (uint16_t)(TMR_ICPolarity << 12);
  /* Select the Input and set the filter */
  tmpccmr2 &= (uint16_t)((uint16_t)(~(uint16_t)TMR_CCM2_CC4S) & ((uint16_t)~((uint16_t)TMR_CCM2_IC4DF)));
  tmpccmr2 |= (uint16_t)(TMR_ICSelection << 8);
  tmpccmr2 |= (uint16_t)(TMR_ICFilter << 12);

  if((TMRx == TMR1) || (TMRx == TMR2) ||
#if !defined (AT32F415xx)
     (TMRx == TMR8) ||
#endif
#if defined (AT32F403xx)
     (TMRx == TMR15) ||
#endif
      (TMRx == TMR3) || (TMRx == TMR4) || (TMRx == TMR5))
  {
    /* Select the Polarity and set the CC4E Bit */
    tmpccer &= (uint16_t)~((uint16_t)(TMR_CCE_C4P));
    tmpccer |= (uint16_t)(tmp | (uint16_t)TMR_CCE_C4EN);
  }
  else
  {
    /* Select the Polarity and set the CC4E Bit */
    tmpccer &= (uint16_t)~((uint16_t)(TMR_CCE_C3P | TMR_CCE_C4NP));
    tmpccer |= (uint16_t)(tmp | (uint16_t)TMR_CCE_C4EN);
  }

  /* Write to TMRx CCMR2 and CCE registers */
  TMRx->CCM2 = tmpccmr2;
  TMRx->CCE = tmpccer;
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


