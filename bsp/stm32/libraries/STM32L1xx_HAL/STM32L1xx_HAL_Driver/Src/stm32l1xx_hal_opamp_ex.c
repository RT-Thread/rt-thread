/**
  ******************************************************************************
  * @file    stm32l1xx_hal_opamp_ex.c
  * @author  MCD Application Team
  * @brief   Extended OPAMP HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the operational amplifier(s)(OPAMP1, OPAMP2 etc)
  *          peripheral:
  *           + Extended Initialization and de-initialization functions
  *           + Extended Peripheral Control functions
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

#ifdef HAL_OPAMP_MODULE_ENABLED

#if defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L151xDX) || defined (STM32L152xE) || defined (STM32L152xDX) || defined (STM32L162xE) || defined (STM32L162xDX) || defined (STM32L162xC) || defined (STM32L152xC) || defined (STM32L151xC)

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @defgroup OPAMPEx OPAMPEx
  * @brief OPAMP Extended HAL module driver.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @addtogroup OPAMPEx_Exported_Functions OPAMPEx Exported Functions
  * @{
  */

/** @addtogroup OPAMPEx_Exported_Functions_Group1
  * @brief    Extended operation functions
  *
@verbatim
 ===============================================================================
              ##### Extended IO operation functions #####
 ===============================================================================
  [..]
      (+) OPAMP Self calibration.

@endverbatim
  * @{
  */

#if defined (STM32L151xD) || defined (STM32L152xD) || defined (STM32L162xD)

/*  3 OPAMPS available */
/*  3 OPAMPS can be calibrated in parallel */

/**
  * @brief  Run the self calibration of the 3 OPAMPs in parallel.
  * @note   Trimming values (PMOS & NMOS) are updated and user trimming is
  *         enabled is calibration is succesful.
  * @note   Calibration is performed in the mode specified in OPAMP init
  *         structure (mode normal or low-power). To perform calibration for
  *         both modes, repeat this function twice after OPAMP init structure
  *         accordingly updated.
  * @note   Calibration runs about 10 ms (5 dichotmy steps, repeated for P
  *         and N transistors: 10 steps with 1 ms for each step).
  * @param  hopamp1 handle
  * @param  hopamp2 handle
  * @param  hopamp3 handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2, OPAMP_HandleTypeDef *hopamp3)
{
  HAL_StatusTypeDef status = HAL_OK;

  uint32_t* opamp1_trimmingvalue;
  uint32_t opamp1_trimmingvaluen = 0;
  uint32_t opamp1_trimmingvaluep = 0;

  uint32_t* opamp2_trimmingvalue;
  uint32_t opamp2_trimmingvaluen = 0;
  uint32_t opamp2_trimmingvaluep = 0;

  uint32_t* opamp3_trimmingvalue;
  uint32_t opamp3_trimmingvaluen = 0;
  uint32_t opamp3_trimmingvaluep = 0;

  uint32_t trimming_diff_pair;              /* Selection of differential transistors pair high or low */

  __IO uint32_t* tmp_opamp1_reg_trimming;   /* Selection of register of trimming depending on power mode: OTR or LPOTR */
  __IO uint32_t* tmp_opamp2_reg_trimming;
  __IO uint32_t* tmp_opamp3_reg_trimming;
  uint32_t tmp_opamp1_otr_otuser;           /* Selection of bit OPAMP_OTR_OT_USER depending on trimming register pointed: OTR or LPOTR */
  uint32_t tmp_opamp2_otr_otuser;
  uint32_t tmp_opamp3_otr_otuser;

  uint32_t tmp_Opa1calout_DefaultSate;      /* Bit OPAMP_CSR_OPA1CALOUT default state when trimming value is 00000b. Used to detect the bit toggling */
  uint32_t tmp_Opa2calout_DefaultSate;      /* Bit OPAMP_CSR_OPA2CALOUT default state when trimming value is 00000b. Used to detect the bit toggling */
  uint32_t tmp_Opa3calout_DefaultSate;      /* Bit OPAMP_CSR_OPA3CALOUT default state when trimming value is 00000b. Used to detect the bit toggling */

  uint32_t tmp_OpaxSwitchesContextBackup = 0x0U;

  uint8_t trimming_diff_pair_iteration_count = 0x0U;    /* For calibration loop algorithm: to repeat the calibration loop for both differential transistors pair high and low */
  uint8_t delta;                                        /* For calibration loop algorithm: Variable for dichotomy steps value */
  uint8_t final_step_check = 0x0U;                      /* For calibration loop algorithm: Flag for additional check of last trimming step */


  if((hopamp1 == NULL) || (hopamp2 == NULL) || (hopamp3 == NULL))
  {
    status = HAL_ERROR;
  }
  /* Check if OPAMP in calibration mode and calibration not yet enable */
  else if(hopamp1->State !=  HAL_OPAMP_STATE_READY)
  {
    status = HAL_ERROR;
  }
  else if(hopamp2->State != HAL_OPAMP_STATE_READY)
  {
    status = HAL_ERROR;
  }
  else if(hopamp3->State != HAL_OPAMP_STATE_READY)
  {
    status = HAL_ERROR;
  }

  else
  {
      /* Check the parameter */
      assert_param(IS_OPAMP_ALL_INSTANCE(hopamp1->Instance));
      assert_param(IS_OPAMP_ALL_INSTANCE(hopamp2->Instance));
      assert_param(IS_OPAMP_ALL_INSTANCE(hopamp3->Instance));
      assert_param(IS_OPAMP_POWERMODE(hopamp1->Init.PowerMode));
      assert_param(IS_OPAMP_POWERMODE(hopamp2->Init.PowerMode));
      assert_param(IS_OPAMP_POWERMODE(hopamp3->Init.PowerMode));

      /* Update OPAMP state */
      hopamp1->State = HAL_OPAMP_STATE_CALIBBUSY;
      hopamp2->State = HAL_OPAMP_STATE_CALIBBUSY;
      hopamp3->State = HAL_OPAMP_STATE_CALIBBUSY;

      /* Backup of switches configuration to restore it at the end of the     */
      /* calibration.                                                         */
      tmp_OpaxSwitchesContextBackup = READ_BIT(OPAMP->CSR, OPAMP_CSR_ALL_SWITCHES_ALL_OPAMPS);

      /* Open all switches on non-inverting input, inverting input and output */
      /* feedback.                                                            */
      CLEAR_BIT(OPAMP->CSR, OPAMP_CSR_ALL_SWITCHES_ALL_OPAMPS);

      /* Set calibration mode to user programmed trimming values */
      SET_BIT(OPAMP->OTR, OPAMP_OTR_OT_USER);

      /* Select trimming settings depending on power mode */
      if (hopamp1->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
      {
        tmp_opamp1_otr_otuser = OPAMP_OTR_OT_USER;
        tmp_opamp1_reg_trimming = &OPAMP->OTR;
      }
      else
      {
        tmp_opamp1_otr_otuser = 0x00000000;
        tmp_opamp1_reg_trimming = &OPAMP->LPOTR;
      }

      if (hopamp2->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
      {
        tmp_opamp2_otr_otuser = OPAMP_OTR_OT_USER;
        tmp_opamp2_reg_trimming = &OPAMP->OTR;
      }
      else
      {
        tmp_opamp2_otr_otuser = 0x00000000;
        tmp_opamp2_reg_trimming = &OPAMP->LPOTR;
      }

      if (hopamp3->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
      {
        tmp_opamp3_otr_otuser = OPAMP_OTR_OT_USER;
        tmp_opamp3_reg_trimming = &OPAMP->OTR;
      }
      else
      {
        tmp_opamp3_otr_otuser = 0x00000000;
        tmp_opamp3_reg_trimming = &OPAMP->LPOTR;
      }

      /* Enable the selected opamp */
      CLEAR_BIT (OPAMP->CSR, OPAMP_CSR_OPAXPD_ALL);

      /* Perform trimming for both differential transistors pair high and low */
      for (trimming_diff_pair_iteration_count = 0U; trimming_diff_pair_iteration_count <= 1U; trimming_diff_pair_iteration_count++)
      {
        if (trimming_diff_pair_iteration_count == 0U)
        {
          /* Calibration of transistors differential pair high (NMOS) */
          trimming_diff_pair = OPAMP_FACTORYTRIMMING_N;
          opamp1_trimmingvalue = &opamp1_trimmingvaluen;
          opamp2_trimmingvalue = &opamp2_trimmingvaluen;
          opamp3_trimmingvalue = &opamp3_trimmingvaluen;

          /* Set bit OPAMP_CSR_OPAXCALOUT default state when trimming value   */
          /* is 00000b. Used to detect the bit toggling during trimming.      */
          tmp_Opa1calout_DefaultSate = RESET;
          tmp_Opa2calout_DefaultSate = RESET;
          tmp_Opa3calout_DefaultSate = RESET;

          /* Enable calibration for N differential pair */
          MODIFY_REG(OPAMP->CSR, OPAMP_CSR_OPAXCAL_L_ALL,
                                 OPAMP_CSR_OPAXCAL_H_ALL);
        }
        else /* (trimming_diff_pair_iteration_count == 1) */
        {
          /* Calibration of transistors differential pair low (PMOS) */
          trimming_diff_pair = OPAMP_FACTORYTRIMMING_P;
          opamp1_trimmingvalue = &opamp1_trimmingvaluep;
          opamp2_trimmingvalue = &opamp2_trimmingvaluep;
          opamp3_trimmingvalue = &opamp3_trimmingvaluep;

          /* Set bit OPAMP_CSR_OPAXCALOUT default state when trimming value   */
          /* is 00000b. Used to detect the bit toggling during trimming.      */
          tmp_Opa1calout_DefaultSate = OPAMP_CSR_OPAXCALOUT(hopamp1);
          tmp_Opa2calout_DefaultSate = OPAMP_CSR_OPAXCALOUT(hopamp2);
          tmp_Opa3calout_DefaultSate = OPAMP_CSR_OPAXCALOUT(hopamp3);

          /* Enable calibration for P differential pair */
          MODIFY_REG(OPAMP->CSR, OPAMP_CSR_OPAXCAL_H_ALL,
                                 OPAMP_CSR_OPAXCAL_L_ALL);
        }


        /* Perform calibration parameter search by dichotomy sweep */
        /*  - Delta initial value 16: for 5 dichotomy steps: 16 for the       */
        /*    initial range, then successive delta sweeps (8, 4, 2, 1).       */
        /*    can extend the search range to +/- 15 units.                    */
        /*  - Trimming initial value 15: search range will go from 0 to 30    */
        /*    (Trimming value 31 is forbidden).                               */
        /* Note: After dichotomy sweep, the trimming result is determined.    */
        /*       However, the final trimming step is deduced from previous    */
        /*       trimming steps tested but is not effectively tested.         */
        /*       An additional test step (using variable "final_step_check")  */
        /*       allow to Test the final trimming step.                       */
        *opamp1_trimmingvalue = 15U;
        *opamp2_trimmingvalue = 15U;
        *opamp3_trimmingvalue = 15U;
        delta = 16U;

        while ((delta != 0U) || (final_step_check == 1U))
        {
          /* Set candidate trimming */
          MODIFY_REG(*tmp_opamp1_reg_trimming, OPAMP_OFFSET_TRIM_SET(hopamp1, trimming_diff_pair, OPAMP_TRIM_VALUE_MASK) ,
                                               OPAMP_OFFSET_TRIM_SET(hopamp1, trimming_diff_pair, *opamp1_trimmingvalue) | tmp_opamp1_otr_otuser);

          MODIFY_REG(*tmp_opamp2_reg_trimming, OPAMP_OFFSET_TRIM_SET(hopamp2, trimming_diff_pair, OPAMP_TRIM_VALUE_MASK) ,
                                               OPAMP_OFFSET_TRIM_SET(hopamp2, trimming_diff_pair, *opamp2_trimmingvalue) | tmp_opamp2_otr_otuser);

          MODIFY_REG(*tmp_opamp3_reg_trimming, OPAMP_OFFSET_TRIM_SET(hopamp3, trimming_diff_pair, OPAMP_TRIM_VALUE_MASK) ,
                                               OPAMP_OFFSET_TRIM_SET(hopamp3, trimming_diff_pair, *opamp3_trimmingvalue) | tmp_opamp3_otr_otuser);

          /* Offset trimming time: during calibration, minimum time needed    */
          /* between two steps to have 1 mV accuracy.                         */
          HAL_Delay(OPAMP_TRIMMING_DELAY);

          /* Set flag for additional check of last trimming step equal to     */
          /* dichotomy step before its division by 2 (equivalent to previous  */
          /* value of dichotomy step).                                        */
          final_step_check = delta;

          /* Divide range by 2 to continue dichotomy sweep */
          delta >>= 1U;

          /* Set trimming values for next iteration in function of trimming   */
          /* result toggle (versus initial state).                            */
          /* Trimming values update with dichotomy delta of previous          */
          /* iteration.                                                       */
          /* Note: on the last trimming loop, delta is equal to 0 and         */
          /*       therefore has no effect.                                   */
          if (READ_BIT(OPAMP->CSR, OPAMP_CSR_OPAXCALOUT(hopamp1)) != tmp_Opa1calout_DefaultSate)
          {
            /* If calibration output is has toggled, try lower trimming */
            *opamp1_trimmingvalue -= delta;
          }
          else
          {
            /* If calibration output is has not toggled, try higher trimming */
            *opamp1_trimmingvalue += delta;
          }

          if (READ_BIT(OPAMP->CSR, OPAMP_CSR_OPAXCALOUT(hopamp2)) != tmp_Opa2calout_DefaultSate)
          {
            /* If calibration output is has toggled, try lower trimming */
            *opamp2_trimmingvalue -= delta;
          }
          else
          {
            /* If calibration output is has not toggled, try higher trimming */
            *opamp2_trimmingvalue += delta;
          }

        if (READ_BIT(OPAMP->CSR, OPAMP_CSR_OPAXCALOUT(hopamp3)) != tmp_Opa3calout_DefaultSate)
        {
          /* If calibration output is has toggled, try lower trimming */
          *opamp3_trimmingvalue -= delta;
        }
        else
        {
          /* If calibration output is has not toggled, try higher trimming */
          *opamp3_trimmingvalue += delta;
        }
      }

      /* Check trimming result of the selected step and perform final fine  */
      /* trimming.                                                          */
      /*  - If calibration output is has toggled: the current step is       */
      /*    already optimized.                                              */
      /*  - If calibration output is has not toggled: the current step can  */
      /*    be optimized by incrementing it of one step.                    */
      if (READ_BIT(OPAMP->CSR, OPAMP_CSR_OPAXCALOUT(hopamp1)) == tmp_Opa1calout_DefaultSate)
      {
        *opamp1_trimmingvalue += 1U;

        /* Set final fine trimming */
        MODIFY_REG(*tmp_opamp1_reg_trimming, OPAMP_OFFSET_TRIM_SET(hopamp1, trimming_diff_pair, OPAMP_TRIM_VALUE_MASK) ,
                                             OPAMP_OFFSET_TRIM_SET(hopamp1, trimming_diff_pair, *opamp1_trimmingvalue) | tmp_opamp1_otr_otuser);
      }
      if (READ_BIT(OPAMP->CSR, OPAMP_CSR_OPAXCALOUT(hopamp2)) == tmp_Opa2calout_DefaultSate)
      {
        *opamp2_trimmingvalue += 1U;

        /* Set final fine trimming */
        MODIFY_REG(*tmp_opamp2_reg_trimming, OPAMP_OFFSET_TRIM_SET(hopamp2, trimming_diff_pair, OPAMP_TRIM_VALUE_MASK) ,
                                             OPAMP_OFFSET_TRIM_SET(hopamp2, trimming_diff_pair, *opamp2_trimmingvalue) | tmp_opamp2_otr_otuser);
      }
      if (READ_BIT(OPAMP->CSR, OPAMP_CSR_OPAXCALOUT(hopamp3)) == tmp_Opa3calout_DefaultSate)
      {
        *opamp3_trimmingvalue += 1U;

        /* Set final fine trimming */
        MODIFY_REG(*tmp_opamp3_reg_trimming, OPAMP_OFFSET_TRIM_SET(hopamp3, trimming_diff_pair, OPAMP_TRIM_VALUE_MASK) ,
                                             OPAMP_OFFSET_TRIM_SET(hopamp3, trimming_diff_pair, *opamp3_trimmingvalue) | tmp_opamp3_otr_otuser);
      }

    }


    /* Disable calibration for P and N differential pairs */
    /* Disable the selected opamp */
    CLEAR_BIT (OPAMP->CSR, (OPAMP_CSR_OPAXCAL_H_ALL |
                            OPAMP_CSR_OPAXCAL_L_ALL |
                            OPAMP_CSR_OPAXPD_ALL     ));

    /* Backup of switches configuration to restore it at the end of the     */
    /* calibration.                                                         */
    SET_BIT(OPAMP->CSR, tmp_OpaxSwitchesContextBackup);

    /* Self calibration is successful */
    /* Store calibration (user trimming) results in init structure. */

    /* Set user trimming mode */
    hopamp1->Init.UserTrimming = OPAMP_TRIMMING_USER;
    hopamp2->Init.UserTrimming = OPAMP_TRIMMING_USER;
    hopamp3->Init.UserTrimming = OPAMP_TRIMMING_USER;

    /* Affect calibration parameters depending on mode normal/low power */
    if (hopamp1->Init.PowerMode != OPAMP_POWERMODE_LOWPOWER)
    {
      /* Write calibration result N */
      hopamp1->Init.TrimmingValueN = opamp1_trimmingvaluen;
      /* Write calibration result P */
      hopamp1->Init.TrimmingValueP = opamp1_trimmingvaluep;
    }
    else
    {
      /* Write calibration result N */
      hopamp1->Init.TrimmingValueNLowPower = opamp1_trimmingvaluen;
      /* Write calibration result P */
      hopamp1->Init.TrimmingValuePLowPower = opamp1_trimmingvaluep;
    }

    if (hopamp2->Init.PowerMode != OPAMP_POWERMODE_LOWPOWER)
    {
      /* Write calibration result N */
      hopamp2->Init.TrimmingValueN = opamp2_trimmingvaluen;
      /* Write calibration result P */
      hopamp2->Init.TrimmingValueP = opamp2_trimmingvaluep;
    }
    else
    {
      /* Write calibration result N */
      hopamp2->Init.TrimmingValueNLowPower = opamp2_trimmingvaluen;
      /* Write calibration result P */
      hopamp2->Init.TrimmingValuePLowPower = opamp2_trimmingvaluep;
    }

    if (hopamp3->Init.PowerMode != OPAMP_POWERMODE_LOWPOWER)
    {
      /* Write calibration result N */
      hopamp3->Init.TrimmingValueN = opamp3_trimmingvaluen;
      /* Write calibration result P */
      hopamp3->Init.TrimmingValueP = opamp3_trimmingvaluep;
    }
    else
    {
      /* Write calibration result N */
      hopamp3->Init.TrimmingValueNLowPower = opamp3_trimmingvaluen;
      /* Write calibration result P */
      hopamp3->Init.TrimmingValuePLowPower = opamp3_trimmingvaluep;
    }

    /* Update OPAMP state */
    hopamp1->State = HAL_OPAMP_STATE_READY;
    hopamp2->State = HAL_OPAMP_STATE_READY;
    hopamp3->State = HAL_OPAMP_STATE_READY;
  }
  return status;
}

#else

/*  2 OPAMPS available */
/*  2 OPAMPS can be calibrated in parallel */

/**
  * @brief  Run the self calibration of the 2 OPAMPs in parallel.
  * @note   Trimming values (PMOS & NMOS) are updated and user trimming is
  *         enabled is calibration is succesful.
  * @note   Calibration is performed in the mode specified in OPAMP init
  *         structure (mode normal or low-power). To perform calibration for
  *         both modes, repeat this function twice after OPAMP init structure
  *         accordingly updated.
  * @note   Calibration runs about 10 ms (5 dichotmy steps, repeated for P
  *         and N transistors: 10 steps with 1 ms for each step).
  * @param  hopamp1 handle
  * @param  hopamp2 handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2)
{
  HAL_StatusTypeDef status = HAL_OK;

  uint32_t* opamp1_trimmingvalue;
  uint32_t opamp1_trimmingvaluen = 0;
  uint32_t opamp1_trimmingvaluep = 0;

  uint32_t* opamp2_trimmingvalue;
  uint32_t opamp2_trimmingvaluen = 0;
  uint32_t opamp2_trimmingvaluep = 0;

  uint32_t trimming_diff_pair;          /* Selection of differential transistors pair high or low */

  __IO uint32_t* tmp_opamp1_reg_trimming;   /* Selection of register of trimming depending on power mode: OTR or LPOTR */
  __IO uint32_t* tmp_opamp2_reg_trimming;
  uint32_t tmp_opamp1_otr_otuser;       /* Selection of bit OPAMP_OTR_OT_USER depending on trimming register pointed: OTR or LPOTR */
  uint32_t tmp_opamp2_otr_otuser;

  uint32_t tmp_Opa1calout_DefaultSate;  /* Bit OPAMP_CSR_OPA1CALOUT default state when trimming value is 00000b. Used to detect the bit toggling */
  uint32_t tmp_Opa2calout_DefaultSate;  /* Bit OPAMP_CSR_OPA2CALOUT default state when trimming value is 00000b. Used to detect the bit toggling */

  uint32_t tmp_OpaxSwitchesContextBackup;

  uint8_t trimming_diff_pair_iteration_count;          /* For calibration loop algorithm: to repeat the calibration loop for both differential transistors pair high and low */
  uint8_t delta;                                       /* For calibration loop algorithm: Variable for dichotomy steps value */
  uint8_t final_step_check = 0x0U;                     /* For calibration loop algorithm: Flag for additional check of last trimming step */


  if((hopamp1 == NULL) || (hopamp2 == NULL))
  {
    status = HAL_ERROR;
  }
  /* Check if OPAMP in calibration mode and calibration not yet enable */
  else if(hopamp1->State !=  HAL_OPAMP_STATE_READY)
  {
    status = HAL_ERROR;
  }
  else if(hopamp2->State != HAL_OPAMP_STATE_READY)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp1->Instance));
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp2->Instance));
    assert_param(IS_OPAMP_POWERMODE(hopamp1->Init.PowerMode));
    assert_param(IS_OPAMP_POWERMODE(hopamp2->Init.PowerMode));

    /* Update OPAMP state */
    hopamp1->State = HAL_OPAMP_STATE_CALIBBUSY;
    hopamp2->State = HAL_OPAMP_STATE_CALIBBUSY;

    /* Backup of switches configuration to restore it at the end of the     */
    /* calibration.                                                         */
    tmp_OpaxSwitchesContextBackup = READ_BIT(OPAMP->CSR, OPAMP_CSR_ALL_SWITCHES_ALL_OPAMPS);

    /* Open all switches on non-inverting input, inverting input and output */
    /* feedback.                                                            */
    CLEAR_BIT(OPAMP->CSR, OPAMP_CSR_ALL_SWITCHES_ALL_OPAMPS);

    /* Set calibration mode to user programmed trimming values */
    SET_BIT(OPAMP->OTR, OPAMP_OTR_OT_USER);

    /* Select trimming settings depending on power mode */
    if (hopamp1->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
    {
      tmp_opamp1_otr_otuser = OPAMP_OTR_OT_USER;
      tmp_opamp1_reg_trimming = &OPAMP->OTR;
    }
    else
    {
      tmp_opamp1_otr_otuser = 0x00000000U;
      tmp_opamp1_reg_trimming = &OPAMP->LPOTR;
    }

    if (hopamp2->Init.PowerMode == OPAMP_POWERMODE_NORMAL)
    {
      tmp_opamp2_otr_otuser = OPAMP_OTR_OT_USER;
      tmp_opamp2_reg_trimming = &OPAMP->OTR;
    }
    else
    {
      tmp_opamp2_otr_otuser = 0x00000000U;
      tmp_opamp2_reg_trimming = &OPAMP->LPOTR;
    }

    /* Enable the selected opamp */
    CLEAR_BIT (OPAMP->CSR, OPAMP_CSR_OPAXPD_ALL);

    /* Perform trimming for both differential transistors pair high and low */
    for (trimming_diff_pair_iteration_count = 0U; trimming_diff_pair_iteration_count <= 1U; trimming_diff_pair_iteration_count++)
    {
      if (trimming_diff_pair_iteration_count == 0U)
      {
        /* Calibration of transistors differential pair high (NMOS) */
        trimming_diff_pair = OPAMP_FACTORYTRIMMING_N;
        opamp1_trimmingvalue = &opamp1_trimmingvaluen;
        opamp2_trimmingvalue = &opamp2_trimmingvaluen;

        /* Set bit OPAMP_CSR_OPAXCALOUT default state when trimming value   */
        /* is 00000b. Used to detect the bit toggling during trimming.      */
        tmp_Opa1calout_DefaultSate = 0U;
        tmp_Opa2calout_DefaultSate = 0U;

        /* Enable calibration for N differential pair */
        MODIFY_REG(OPAMP->CSR, OPAMP_CSR_OPAXCAL_L_ALL,
                               OPAMP_CSR_OPAXCAL_H_ALL);
      }
      else /* (trimming_diff_pair_iteration_count == 1) */
      {
        /* Calibration of transistors differential pair low (PMOS) */
        trimming_diff_pair = OPAMP_FACTORYTRIMMING_P;
        opamp1_trimmingvalue = &opamp1_trimmingvaluep;
        opamp2_trimmingvalue = &opamp2_trimmingvaluep;

        /* Set bit OPAMP_CSR_OPAXCALOUT default state when trimming value   */
        /* is 00000b. Used to detect the bit toggling during trimming.      */
        tmp_Opa1calout_DefaultSate = (uint32_t) OPAMP_CSR_OPAXCALOUT(hopamp1);
        tmp_Opa2calout_DefaultSate = OPAMP_CSR_OPAXCALOUT(hopamp2);

        /* Enable calibration for P differential pair */
        MODIFY_REG(OPAMP->CSR, OPAMP_CSR_OPAXCAL_H_ALL,
                               OPAMP_CSR_OPAXCAL_L_ALL);
      }


      /* Perform calibration parameter search by dichotomy sweep */
      /*  - Delta initial value 16: for 5 dichotomy steps: 16 for the       */
      /*    initial range, then successive delta sweeps (8, 4, 2, 1).       */
      /*    can extend the search range to +/- 15 units.                    */
      /*  - Trimming initial value 15: search range will go from 0 to 30    */
      /*    (Trimming value 31 is forbidden).                               */
      /* Note: After dichotomy sweep, the trimming result is determined.    */
      /*       However, the final trimming step is deduced from previous    */
      /*       trimming steps tested but is not effectively tested.         */
      /*       An additional test step (using variable "final_step_check")  */
      /*       allow to Test the final trimming step.                       */
      *opamp1_trimmingvalue = 15U;
      *opamp2_trimmingvalue = 15U;
      delta = 16U;

      while ((delta != 0U) || (final_step_check == 1U))
      {
        /* Set candidate trimming */
        MODIFY_REG(*tmp_opamp1_reg_trimming, OPAMP_OFFSET_TRIM_SET(hopamp1, trimming_diff_pair, OPAMP_TRIM_VALUE_MASK) ,
                                             OPAMP_OFFSET_TRIM_SET(hopamp1, trimming_diff_pair, *opamp1_trimmingvalue) | tmp_opamp1_otr_otuser);

        MODIFY_REG(*tmp_opamp2_reg_trimming, OPAMP_OFFSET_TRIM_SET(hopamp2, trimming_diff_pair, OPAMP_TRIM_VALUE_MASK) ,
                                             OPAMP_OFFSET_TRIM_SET(hopamp2, trimming_diff_pair, *opamp2_trimmingvalue) | tmp_opamp2_otr_otuser);


        /* Offset trimming time: during calibration, minimum time needed    */
        /* between two steps to have 1 mV accuracy.                         */
        HAL_Delay(OPAMP_TRIMMING_DELAY);

        /* Set flag for additional check of last trimming step equal to     */
        /* dichotomy step before its division by 2 (equivalent to previous  */
        /* value of dichotomy step).                                        */
        final_step_check = delta;

        /* Divide range by 2 to continue dichotomy sweep */
        delta >>= 1U;

        /* Set trimming values for next iteration in function of trimming   */
        /* result toggle (versus initial state).                            */
        /* Trimming values update with dichotomy delta of previous          */
        /* iteration.                                                       */
        /* Note: on the last trimming loop, delta is equal to 0 and         */
        /*       therefore has no effect.                                   */
        if (READ_BIT(OPAMP->CSR, OPAMP_CSR_OPAXCALOUT(hopamp1)) != tmp_Opa1calout_DefaultSate)
        {
          /* If calibration output is has toggled, try lower trimming */
          *opamp1_trimmingvalue -= delta;
        }
        else
        {
          /* If calibration output is has not toggled, try higher trimming */
          *opamp1_trimmingvalue += delta;
        }

        if (READ_BIT(OPAMP->CSR, OPAMP_CSR_OPAXCALOUT(hopamp2)) != tmp_Opa2calout_DefaultSate)
        {
          /* If calibration output is has toggled, try lower trimming */
          *opamp2_trimmingvalue -= delta;
        }
        else
        {
          /* If calibration output is has not toggled, try higher trimming */
          *opamp2_trimmingvalue += delta;
        }
      }

      /* Check trimming result of the selected step and perform final fine  */
      /* trimming.                                                          */
      /*  - If calibration output is has toggled: the current step is       */
      /*    already optimized.                                              */
      /*  - If calibration output is has not toggled: the current step can  */
      /*    be optimized by incrementing it of one step.                    */
      if (READ_BIT(OPAMP->CSR, OPAMP_CSR_OPAXCALOUT(hopamp1)) == tmp_Opa1calout_DefaultSate)
      {
        *opamp1_trimmingvalue += 1U;

        /* Set final fine trimming */
        MODIFY_REG(*tmp_opamp1_reg_trimming, OPAMP_OFFSET_TRIM_SET(hopamp1, trimming_diff_pair, OPAMP_TRIM_VALUE_MASK) ,
                                             OPAMP_OFFSET_TRIM_SET(hopamp1, trimming_diff_pair, *opamp1_trimmingvalue) | tmp_opamp1_otr_otuser);
      }
      if (READ_BIT(OPAMP->CSR, OPAMP_CSR_OPAXCALOUT(hopamp2)) == tmp_Opa2calout_DefaultSate)
      {
        *opamp2_trimmingvalue += 1U;

        /* Set final fine trimming */
        MODIFY_REG(*tmp_opamp2_reg_trimming, OPAMP_OFFSET_TRIM_SET(hopamp2, trimming_diff_pair, OPAMP_TRIM_VALUE_MASK) ,
                                             OPAMP_OFFSET_TRIM_SET(hopamp2, trimming_diff_pair, *opamp2_trimmingvalue) | tmp_opamp2_otr_otuser);

      }

    }


    /* Disable calibration for P and N differential pairs */
    /* Disable the selected opamp */
    CLEAR_BIT (OPAMP->CSR, (OPAMP_CSR_OPAXCAL_H_ALL |
                            OPAMP_CSR_OPAXCAL_L_ALL |
                            OPAMP_CSR_OPAXPD_ALL     ));

    /* Backup of switches configuration to restore it at the end of the     */
    /* calibration.                                                         */
    SET_BIT(OPAMP->CSR, tmp_OpaxSwitchesContextBackup);

    /* Self calibration is successful */
    /* Store calibration (user trimming) results in init structure. */

    /* Set user trimming mode */
    hopamp1->Init.UserTrimming = OPAMP_TRIMMING_USER;
    hopamp2->Init.UserTrimming = OPAMP_TRIMMING_USER;

    /* Affect calibration parameters depending on mode normal/low power */
    if (hopamp1->Init.PowerMode != OPAMP_POWERMODE_LOWPOWER)
    {
      /* Write calibration result N */
      hopamp1->Init.TrimmingValueN = opamp1_trimmingvaluen;
      /* Write calibration result P */
      hopamp1->Init.TrimmingValueP = opamp1_trimmingvaluep;
    }
    else
    {
      /* Write calibration result N */
      hopamp1->Init.TrimmingValueNLowPower = opamp1_trimmingvaluen;
      /* Write calibration result P */
      hopamp1->Init.TrimmingValuePLowPower = opamp1_trimmingvaluep;
    }

    if (hopamp2->Init.PowerMode != OPAMP_POWERMODE_LOWPOWER)
    {
      /* Write calibration result N */
      hopamp2->Init.TrimmingValueN = opamp2_trimmingvaluen;
      /* Write calibration result P */
      hopamp2->Init.TrimmingValueP = opamp2_trimmingvaluep;
    }
    else
    {
      /* Write calibration result N */
      hopamp2->Init.TrimmingValueNLowPower = opamp2_trimmingvaluen;
      /* Write calibration result P */
      hopamp2->Init.TrimmingValuePLowPower = opamp2_trimmingvaluep;
    }

    /* Update OPAMP state */
    hopamp1->State = HAL_OPAMP_STATE_READY;
    hopamp2->State = HAL_OPAMP_STATE_READY;
  }
  return status;
}

#endif /* STM32L151xD || STM32L152xD || STM32L162xD */

/**
  * @}
  */

/** @defgroup OPAMPEx_Exported_Functions_Group2 Extended Peripheral Control functions
 *  @brief   Extended peripheral control functions
 *
@verbatim
 ===============================================================================
             ##### Peripheral Control functions #####
 ===============================================================================
    [..]
      (+) OPAMP unlock.

@endverbatim
  * @{
  */

/**
  * @brief  Unlock the selected OPAMP configuration.
  *         This function must be called only when OPAMP is in state "locked".
  * @param  hopamp OPAMP handle
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_OPAMPEx_Unlock(OPAMP_HandleTypeDef* hopamp)
{
  HAL_StatusTypeDef status = HAL_OK;

  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  if(hopamp == NULL)
  {
    status = HAL_ERROR;
  }
  /* Check the OPAMP handle allocation */
  /* Check if OPAMP locked */
  else if(hopamp->State == HAL_OPAMP_STATE_BUSYLOCKED)
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp->Instance));

   /* OPAMP state changed to locked */
    hopamp->State = HAL_OPAMP_STATE_BUSY;
  }
  else
  {
    status = HAL_ERROR;
  }

  return status;
}

/**
  * @}
  */

/**
  * @}
  */

#endif /* STM32L151xCA || STM32L151xD || STM32L152xCA || STM32L152xD || STM32L162xCA || STM32L162xD || STM32L151xE || STM32L151xDX || STM32L152xE || STM32L152xDX || STM32L162xE || STM32L162xDX || STM32L162xC || STM32L152xC || STM32L151xC */

#endif /* HAL_OPAMP_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
