/**
  ******************************************************************************
  * @file    at32f4xx_comp.c
  * @author  Artery
  * @version V1.0.1
  * @date    20-April-2012
  * @brief   This file provides firmware functions to manage the following 
  *          functionalities of the comparators (COMP1 and COMP2) peripheral: 
  *           + Comparators configuration
  *           + Window mode control
  *
  *  @verbatim
  *
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..]           
   
         The device integrates two analog comparators COMP1 and COMP2:
         (+) The non inverting input is set to PA1 for COMP1 and to PA3
             for COMP2.
  
         (+) The inverting input can be selected among: DAC_OUT1, 
             1/4 VREFINT, 1/2 VERFINT, 3/4 VREFINT, VREFINT,
             I/O (PA0 for COMP1 and PA2 for COMP2)
  
         (+) The COMP output is internally is available using COMP_GetOutputState()
             and can be set on GPIO pins: PA0, PA6, PA11 for COMP1
             and PA2, PA7, PA12 for COMP2
  
         (+) The COMP output can be redirected to embedded timers (TIM1, TIM2
             and TIM3)
  
         (+) The two comparators COMP1 and COMP2 can be combined in window
             mode and only COMP1 non inverting (PA1) can be used as non-
             inverting input.
  
         (+) The two comparators COMP1 and COMP2 have interrupt capability 
             with wake-up from Sleep and Stop modes (through the EXTI controller).
             COMP1 and COMP2 outputs are internally connected to EXTI Line 21
             and EXTI Line 22 respectively.
                   

                     ##### How to configure the comparator #####
 ===============================================================================
    [..] 
           This driver provides functions to configure and program the Comparators 
           of all AT32F4xx devices.
             
    [..]   To use the comparator, perform the following steps:
  
         (#) Enable the SYSCFG APB clock to get write access to comparator
             register using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  
         (#) Configure the comparator input in analog mode using GPIO_Init()
  
         (#) Configure the comparator output in alternate function mode
             using GPIO_Init() and use GPIO_PinAFConfig() function to map the
             comparator output to the GPIO pin
  
         (#) Configure the comparator using COMP_Init() function:
                 (++)  Select the inverting input
                 (++)  Select the output polarity  
                 (++)  Select the output redirection
                 (++)  Select the hysteresis level
                 (++)  Select the power mode
    
         (#) Enable the comparator using COMP_Cmd() function
  
         (#) If required enable the COMP interrupt by configuring and enabling
             EXTI line in Interrupt mode and selecting the desired sensitivity
             level using EXTI_Init() function. After that enable the comparator
             interrupt vector using NVIC_Init() function.
  
     @endverbatim
  *    
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 Artery</center></h2>
  *
  * Licensed under Artery Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "at32f4xx_comp.h"

/** @addtogroup AT32F4xx_StdPeriph_Driver
  * @{
  */

/** @defgroup COMP 
  * @brief COMP driver modules
  * @{
  */ 

#if defined (AT32F415xx)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* CTRLSTS1 register Mask */
#define COMP_CTRLSTS1_CLEAR_MASK              ((uint32_t)0x00003FFE)
#define COMP_CTRLSTS2_CLEAR_MASK              ((uint32_t)0x00000003)
#define COMP_HIGH_PULSE_CLEAR_MASK            ((uint16_t)0x003F) 
#define COMP_LOW_PULSE_CLEAR_MASK             ((uint16_t)0x003F)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup COMP_Private_Functions
  * @{
  */
   
/**
  * @brief  Deinitializes COMP peripheral registers to their default reset values.
  * @note   Deinitialization can't be performed if the COMP configuration is locked.
  *         To unlock the configuration, perform a system reset.
  * @param  None
  * @retval None
  */
void COMP_Reset(void)
{
  COMP->CTRLSTS1 = ((uint32_t)0x00000000);    /*!< Set COMP_CTRLSTS register to reset value */
}

/**
  * @brief  Initializes the COMP peripheral according to the specified parameters
  *         in COMP_InitStruct
  * @note   If the selected comparator is locked, initialization can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @note   By default, PA1 is selected as COMP1 non inverting input.
  *         To use PA4 as COMP1 non inverting input call COMP_SwitchCmd() after COMP_Init()
  * @param  COMP_Selection: the selected comparator. 
  *          This parameter can be one of the following values:
  *            @arg COMP1_Selection: COMP1 selected
  *            @arg COMP2_Selection: COMP2 selected
  * @param  COMP_InitStruct: pointer to an COMP_InitType structure that contains 
  *         the configuration information for the specified COMP peripheral.
  * @retval None
  */
void COMP_Init(uint32_t COMP_Selection, COMP_InitType* COMP_InitStruct)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
  assert_param(IS_COMP_INVERTING_INPUT(COMP_InitStruct->COMP_INMInput));
  assert_param(IS_COMP_OUTPUT(COMP_InitStruct->COMP_Output));
  assert_param(IS_COMP_OUTPUT_POL(COMP_InitStruct->COMP_OutPolarity));
  assert_param(IS_COMP_HYSTERESIS(COMP_InitStruct->COMP_Hysteresis));
  assert_param(IS_COMP_MODE(COMP_InitStruct->COMP_Mode));

  /*!< Get the COMP_CTRLSTS register value */
  tmpreg = COMP->CTRLSTS1;

  /*!< Clear the COMP1SW1, COMPx_IN_SEL, COMPx_OUT_TIM_SEL, COMPx_POL, COMPx_HYST and COMPx_PWR_MODE bits */ 
  tmpreg &= (uint32_t) ~(COMP_CTRLSTS1_CLEAR_MASK<<COMP_Selection);

  /*!< Configure COMP: inverting input, output redirection, hysteresis value and power mode */
  /*!< Set COMPxINSEL bits according to COMP_InitStruct->COMP_InvertingInput value */
  /*!< Set COMPxOUTSEL bits according to COMP_InitStruct->COMP_Output value */
  /*!< Set COMPxPOL bit according to COMP_InitStruct->COMP_OutputPol value */
  /*!< Set COMPxHYST bits according to COMP_InitStruct->COMP_Hysteresis value */
  /*!< Set COMPxMODE bits according to COMP_InitStruct->COMP_Mode value */   
  tmpreg |= (uint32_t)((COMP_InitStruct->COMP_INMInput | COMP_InitStruct->COMP_Output |
                       COMP_InitStruct->COMP_OutPolarity | COMP_InitStruct->COMP_Hysteresis |
                       COMP_InitStruct->COMP_Mode)<<COMP_Selection);

  /*!< Write to COMP_CTRLSTS1 register */
  COMP->CTRLSTS1 = tmpreg;  
}

/**
  * @brief  Select the non-inverting input for COMP1/COMP2.
  * @param  COMP_Selection: the selected comparator. 
  *          This parameter can be one of the following values:
  *            @arg COMP1_Selection: COMP1 selected
  *            @arg COMP2_Selection: COMP2 selected
  * @param  COMP_INPInput: the selected COMP non-inverting input.
  *         This parameter can be one of the following values:
  *            @arg COMP_INPInput_00: PA5/PA7 connected to comparator1/2 non-inverting input
  *            @arg COMP_INPInput_01: PA1/PA3 connected to comparator1/2 non-inverting input
  *            @arg COMP_INPInput_10: PA0/PA2 connected to comparator1/2 non-inverting input
  * @retval None
  */
void COMP_SelectINPInput(uint32_t COMP_Selection, uint32_t COMP_INPInput)
{
  uint32_t tmpreg = 0;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
  assert_param(IS_COMP_NONINVERTING_INPUT(COMP_INPInput));

  /*!< Get the COMP_CTRLSTS register value */
  tmpreg = COMP->CTRLSTS2;

  /*!< Clear the COMPxINPSEL bits */ 
  tmpreg &= (uint32_t) ~(COMP_CTRLSTS2_CLEAR_MASK<<COMP_Selection);

  /*!< Set COMPxINPSEL bits according to COMP_InitStruct->COMP_NonInvertingInput value */
  tmpreg |= (uint32_t)(COMP_INPInput<<COMP_Selection);

  /*!< Write to COMP_CTRLSTS2 register */
  COMP->CTRLSTS2 = tmpreg;  
}

/**
  * @brief  Fills each COMP_InitStruct member with its default value.
  * @param  COMP_InitStruct: pointer to an COMP_InitType structure which will 
  *         be initialized.
  * @retval None
  */
void COMP_StructInit(COMP_InitType* COMP_InitStruct)
{
  COMP_InitStruct->COMP_INMInput = COMP_INMInput_1_4VREFINT;
  COMP_InitStruct->COMP_Output = COMP_Output_None;
  COMP_InitStruct->COMP_OutPolarity = COMP_OutPolarity_NonInverted;
  COMP_InitStruct->COMP_Hysteresis = COMP_Hysteresis_No;
  COMP_InitStruct->COMP_Mode = COMP_Mode_Slow;
}

/**
  * @brief  Enable or disable the COMP peripheral.
  * @note   If the selected comparator is locked, enable/disable can't be performed.
  *         To unlock the configuration, perform a system reset.
  * @param  COMP_Selection: the selected comparator.
  *          This parameter can be one of the following values:
  *            @arg COMP1_Selection: COMP1 selected
  *            @arg COMP2_Selection: COMP2 selected
  * @param  NewState: new state of the COMP peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @note   When enabled, the comparator compares the non inverting input with 
  *         the inverting input and the comparison result is available on comparator output.
  * @note   When disabled, the comparator doesn't perform comparison and the 
  *         output level is low.
  * @retval None
  */
void COMP_Cmd(uint32_t COMP_Selection, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Enable the selected COMP peripheral */
    COMP->CTRLSTS1 |= (uint32_t) (1<<COMP_Selection);
  }
  else
  {
    /* Disable the selected COMP peripheral  */
    COMP->CTRLSTS1 &= (uint32_t)(~((uint32_t)1<<COMP_Selection));
  }
}

/**
  * @brief  Close or Open the SW1 switch.
  * @note   This switch is solely intended to redirect signals onto high
  *         impedance input, such as COMP1 non-inverting input (highly resistive switch)
  * @param  NewState: New state of the analog switch.
  *          This parameter can be: ENABLE or DISABLE. 
  * @note   When enabled, the SW1 is closed; PA1 is connected to PA4
  * @note   When disabled, the SW1 switch is open; PA1 is disconnected from PA4
  * @retval None
  */
void COMP_SwitchCmd(FunctionalState NewState)
{
  /* Check the parameter */
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    /* Close SW1 switch */
    COMP->CTRLSTS1 |= (uint32_t) (COMP_CTRLSTS_COMP1SW1);
  }
  else
  {
    /* Open SW1 switch */
    COMP->CTRLSTS1 &= (uint32_t)(~COMP_CTRLSTS_COMP1SW1);
  }
}

/**
  * @brief  Return the output level (high or low) of the selected comparator. 
  * @note   The output level depends on the selected polarity.
  * @note   If the polarity is not inverted:
  *          - Comparator output is low when the non-inverting input is at a lower
  *            voltage than the inverting input
  *          - Comparator output is high when the non-inverting input is at a higher
  *            voltage than the inverting input
  * @note   If the polarity is inverted:
  *          - Comparator output is high when the non-inverting input is at a lower
  *            voltage than the inverting input
  *          - Comparator output is low when the non-inverting input is at a higher
  *            voltage than the inverting input
  * @param  COMP_Selection: the selected comparator. 
  *          This parameter can be one of the following values:
  *            @arg COMP1_Selection: COMP1 selected
  *            @arg COMP2_Selection: COMP2 selected  
  * @retval Returns the selected comparator output level: low or high.
  *       
  */
uint32_t COMP_GetOutputState(uint32_t COMP_Selection)
{
  uint32_t compout = 0x0;

  /* Check the parameters */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

  /* Check if selected comparator output is high */
  if ((COMP->CTRLSTS1 & (COMP_CTRLSTS_COMP1OUT<<COMP_Selection)) != 0)
  {
    compout = COMP_OutputState_High;
  }
  else
  {
    compout = COMP_OutputState_Low;
  }

  /* Return the comparator output level */
  return (uint32_t)(compout);
}

/**
  * @brief  Enables or disables the window mode.
  * @note   In window mode, COMP1 and COMP2 non inverting inputs are connected
  *         together and only COMP1 non inverting input (PA1) can be used.
  * @param  NewState: new state of the window mode.
  *          This parameter can be :
  *           @arg ENABLE: COMP1 and COMP2 non inverting inputs are connected together.
  *           @arg DISABLE: OMP1 and COMP2 non inverting inputs are disconnected.
  * @retval None
  */
void COMP_WindowCmd(FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the window mode */
    COMP->CTRLSTS1 |= (uint32_t)COMP_CTRLSTS_WNDWEN;
  }
  else
  {
    /* Disable the window mode */
    COMP->CTRLSTS1 &= (uint32_t)(~COMP_CTRLSTS_WNDWEN);
  }
}

/**
  * @brief  Lock the selected comparator (COMP1/COMP2) configuration.
  * @note   Locking the configuration means that all control bits are read-only.
  *         To unlock the comparator configuration, perform a system reset.
  * @param  COMP_Selection: selects the comparator to be locked 
  *          This parameter can be a value of the following values:
  *            @arg COMP1_Selection: COMP1 configuration is locked.
  *            @arg COMP2_Selection: COMP2 configuration is locked.  
  * @retval None
  */
void COMP_LockConfig(uint32_t COMP_Selection)
{
  /* Check the parameter */
  assert_param(IS_COMP_ALL_PERIPH(COMP_Selection));

  /* Set the lock bit corresponding to selected comparator */
  COMP->CTRLSTS1 |= (uint32_t) (COMP_CTRLSTS_COMP1LOCK<<COMP_Selection);
}

/**
  * @brief  Configure COMP Glitch Filter.
  * @note   G_FILTER_EN, HIGH_PULSE and LOW_PULSE registers will
  *         act on both COMP1 and COMP2.
  * @param  COMP_HighPulseCnt: COMP High Pulse Count.
  *         This parameter must be a value between 0x00 and 0x3F  
  * @param  COMP_LowPulseCnt: COMP Low Pulse Count.
  *         This parameter must be a value between 0x00 and 0x3F  
  * @param  NewState: new state of the Glitch Filter.
  *          This parameter can be :
  *           @arg ENABLE: COMP1 and COMP2 turn on glitch filter.
  *           @arg DISABLE: COMP1 and COMP2 turn off glitch filter.
  * @retval None
  */
void COMP_FilterConfig(uint16_t COMP_HighPulseCnt, uint16_t COMP_LowPulseCnt, FunctionalState NewState)
{
  uint16_t tmphp = 0;
  uint16_t tmplp = 0;
  /* Check the parameters */
  assert_param(IS_COMP_HighPulseCnt(COMP_HighPulseCnt));
  assert_param(IS_COMP_LowPulseCnt(COMP_LowPulseCnt));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  
  if (NewState != DISABLE)
  {
    /* Enable the glitch filter */
    COMP->G_FILTER_EN |= (uint16_t)COMP_G_FILTER_EN_GFE;
    
    tmphp = COMP->HIGH_PULSE;
    tmplp = COMP->LOW_PULSE;
    
    /* Reset the H_PULSE_CNT and L_PULSE_CNT Bits */
    tmphp &= ~COMP_HIGH_PULSE_CLEAR_MASK;
    tmplp &= ~COMP_LOW_PULSE_CLEAR_MASK;
    
    /* Set the H_PULSE_CNT and L_PULSE_CNT Bits */
    tmphp |= COMP_HighPulseCnt;
    tmplp |= COMP_LowPulseCnt;
    
    /* Write to COMP HIGH_PULSE and LOW_PULSE */
    COMP->HIGH_PULSE = tmphp;
    COMP->LOW_PULSE = tmplp;
  }
  else
  {
    /* Disable the glitch filter */
    COMP->G_FILTER_EN &= (uint16_t)(~COMP_G_FILTER_EN_GFE);
    
    /* Reset the H_PULSE_CNT and L_PULSE_CNT Bits */
    COMP->HIGH_PULSE &= ~COMP_HIGH_PULSE_CLEAR_MASK;
    COMP->LOW_PULSE &= ~COMP_LOW_PULSE_CLEAR_MASK;
  }
}

/**
  * @}
  */

#endif /* AT32F415xx */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Artery *****END OF FILE****/
