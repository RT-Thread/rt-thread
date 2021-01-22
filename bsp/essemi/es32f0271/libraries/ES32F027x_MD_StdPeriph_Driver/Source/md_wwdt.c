/**
  ******************************************************************************
  * @file    md_wwdt.c
  * @brief   ES32F0271 WWDT Source File.
  *
  * @version V1.00.01
  * @date    4/12/2018
  * @author  Eastsoft AE Team
  * @note
  * detailed description
  *
  * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd. ALL rights reserved.
  *******************************************************************************
  */

/* Includes -------------------------------------------------------------------*/
#include "md_rcu.h"
#include "md_wwdt.h"

/** @addtogroup Micro_Driver
  * @{
  */

#if defined (WWDT)

/** @defgroup WWDT WWDT
  * @brief WWDT micro driver
  * @{
  */

/* Private types --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private constants ----------------------------------------------------------*/
/* Private macros -------------------------------------------------------------*/

/* Public functions -----------------------------------------------------------*/
/** @addtogroup MD_RCU_Public_Functions RCU Public Functions
  * @{
  */
/**
  * @brief  De-initialize the GPIO registers to their default reset values.
  * @param  GPIOx GPIO Instance
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: GPIO registers are de-initialized
  *          - ERROR: GPIO registers are not de-initialized
  */
void md_wwdt_init(WWDT_TypeDef *WWD, md_wwdt_inittypedef *WWDT_InitStruct)
{
  /* Check the parameters */
  assert_param(IS_MD_WWDT_ALL_INSTANCE(WWD));
  assert_param(IS_MD_WWDT_PRESCALER(WWDT_InitStruct->Prescaler));
  assert_param(IS_MD_WWDT_WINDOW(WWDT_InitStruct->Window));
  assert_param(IS_MD_WWDT_COUNTER(WWDT_InitStruct->Counter));
  assert_param(IS_MD_WWDT_EWI_MODE(WWDT_InitStruct->EWIMode));

  if (WWDT_InitStruct->EWIMode == WWDT_EWI_ENABLE)
    md_wwdt_enable_ier_ewis(WWD);
  else
    md_wwdt_disable_idr_ewis(WWD);

  md_wwdt_set_con_t(WWD, WWDT_InitStruct->Counter);
  md_wwdt_set_cfg_wdgtb(WWD, WWDT_InitStruct->Prescaler);
  md_wwdt_set_cfg_w(WWD, WWDT_InitStruct->Window);
  md_wwdt_enable_con_wdga(WWD);
}











/**
  * @} GPIO
  */
#endif

/**
  * @} Micro_Driver
  */

/******************* (C) COPYRIGHT Eastsoft Microelectronics *****END OF FILE****/
