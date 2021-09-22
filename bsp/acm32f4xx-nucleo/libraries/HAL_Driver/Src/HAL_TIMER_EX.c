/***********************************************************************
 * Filename    : hal_lpuart.c
 * Description : lpuart driver source file
 * Author(s)   : xwl  
 * version     : V1.0
 * Modify date : 2021-04-02
 ***********************************************************************/
#include "ACM32Fxx_HAL.h"  


/*********************************************************************************
* Function    : HAL_TIMER_ConfigBreakDeadTime  
* Description : configure deadtime parameter   
* Input       : timer handler, break and deadtime configuration  
* Output      : none  
* Author      : xwl                       
**********************************************************************************/  
void HAL_TIMEx_ConfigBreakDeadTime(TIM_HandleTypeDef *htim, TIM_BreakDeadTimeConfigTypeDef * sBreakDeadTimeConfig)
{
  /* Keep this variable initialized to 0 as it is used to configure BDTR register */
    uint32_t break_deadtime_reg = 0U;

    /* Set the BDTR bits */
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_DTG,  sBreakDeadTimeConfig->DeadTime);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_LOCK, sBreakDeadTimeConfig->LockLevel);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_OSSI, sBreakDeadTimeConfig->OffStateIDLEMode);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_OSSR, sBreakDeadTimeConfig->OffStateRunMode);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_BKE, sBreakDeadTimeConfig->BreakState);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_BKP, sBreakDeadTimeConfig->BreakPolarity);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_AOE, sBreakDeadTimeConfig->AutomaticOutput);
    MODIFY_REG(break_deadtime_reg, TIM_BDTR_BKF, (sBreakDeadTimeConfig->BreakFilter << TIM_BDTR_BKF_Pos));
  
    /* Set TIMx_BDTR */
    htim->Instance->BDTR = break_deadtime_reg;  

}
  
/*********************************************************************************
* Function    : HAL_TIMEx_ConfigBreakInput  
* Description : Configures the break input source.  
* Input       :
              htim: timer handler 
              BreakInput: TIM_BREAKINPUT_BRK  
              sBreakInputConfig: Break input source configuration   
* Output      :   
* Author      : xwl                       
**********************************************************************************/
HAL_StatusTypeDef HAL_TIMEx_ConfigBreakInput(TIM_HandleTypeDef *htim, uint32_t BreakInput,
                                             TIMEx_BreakInputConfigTypeDef *sBreakInputConfig)
{
    uint32_t tmporx;
    uint32_t bkin_enable_mask;
    uint32_t bkin_polarity_mask;
    uint32_t bkin_enable_bitpos;
    uint32_t bkin_polarity_bitpos;   

    switch(sBreakInputConfig->Source)
    {
        case TIM_BREAKINPUTSOURCE_BKIN:
        {
            bkin_enable_mask = TIM1_AF1_BKINE;
            bkin_enable_bitpos = TIM1_AF1_BKINE_Pos;
            bkin_polarity_mask = TIM1_AF1_BKINP;
            bkin_polarity_bitpos = TIM1_AF1_BKINP_Pos;
            break;
        }
#ifdef HAL_COMP_MODULE_ENABLED  
        case TIM_BREAKINPUTSOURCE_COMP1:
        {
            bkin_enable_mask = TIM1_AF1_BKCMP1E;
            bkin_enable_bitpos = TIM1_AF1_BKCMP1E_Pos;
            bkin_polarity_mask = TIM1_AF1_BKCMP1P;
            bkin_polarity_bitpos = TIM1_AF1_BKCMP1P_Pos;
            break;
        }
        case TIM_BREAKINPUTSOURCE_COMP2:
        {
            bkin_enable_mask = TIM1_AF1_BKCMP2E;
            bkin_enable_bitpos = TIM1_AF1_BKCMP2E_Pos;
            bkin_polarity_mask = TIM1_AF1_BKCMP2P;
            bkin_polarity_bitpos = TIM1_AF1_BKCMP2P_Pos;
            break;
        }
#endif /* COMP1 && COMP2 */

        default:
        {
            bkin_enable_mask = 0U;
            bkin_enable_bitpos = 0U;
            bkin_polarity_mask = 0U;
            bkin_polarity_bitpos = 0U;
            break;
        }
    }
  
    switch(BreakInput)
    {
        case TIM_BREAKINPUT_BRK:
        {
            /* Get the TIMx_AF1 register value */
            tmporx = htim->Instance->AF1;
        
            /* Enable the break input */
            tmporx &= ~bkin_enable_mask;
            tmporx |= (sBreakInputConfig->Enable << bkin_enable_bitpos) & bkin_enable_mask;
        
            /* Set the break input polarity */
            tmporx &= ~bkin_polarity_mask;
            tmporx |= (sBreakInputConfig->Polarity << bkin_polarity_bitpos) & bkin_polarity_mask;
        
            /* Set TIMx_AF1 */
            htim->Instance->AF1 = tmporx;        
            break;
    }

    default:
      break;
    }

    return HAL_OK;  
}   


/*********************************************************************************
* Function    : HAL_TIMEx_ConfigCommutEvent  
* Description : Configure the TIM commutation event sequence. This function is mandatory to use the commutation event 
                in order to update the configuration at each commutation detection on the TRGI input of the Timer.
* Input       :
              htim: timer handler 
              InputTrigger: TIM_TRIGGER_SOURCE_ITR0, TIM_TRIGGER_SOURCE_ITR1...   
              CommutationSource: TIM_COMMUTATION_TRGI, TIM_COMMUTATION_SOFTWARE  
* Output      :   
* Author      : xwl                       
**********************************************************************************/ 
void HAL_TIMEx_ConfigCommutEvent(TIM_HandleTypeDef *htim, uint32_t  InputTrigger, uint32_t  CommutationSource)
{

    if ((InputTrigger == TIM_TRIGGER_SOURCE_ITR0) || (InputTrigger == TIM_TRIGGER_SOURCE_ITR1) ||
      (InputTrigger == TIM_TRIGGER_SOURCE_ITR2) || (InputTrigger == TIM_TRIGGER_SOURCE_ITR3))
    {
        /* Select the Input trigger */
        htim->Instance->SMCR &= (~(BIT4|BIT5|BIT6));
        htim->Instance->SMCR |= InputTrigger;
    }

    /* Select the Capture Compare preload feature */
    htim->Instance->CR2 |= TIM_CR2_CCPC;
    /* Select the Commutation event source */
    htim->Instance->CR2 &= ~TIM_CR2_CCUS;
    htim->Instance->CR2 |= CommutationSource;

    /* Disable Commutation Interrupt */
    HAL_TIM_DISABLE_IT(htim, TIM_IT_COM);

  /* Disable Commutation DMA request */
    HAL_TIM_DISABLE_DMA(htim, TIM_DMA_COM);

}


