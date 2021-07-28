/**
  ******************************************************************************
  * @file    stm32f3xx_hal_opamp_ex.c
  * @author  MCD Application Team
  * @brief   Extended OPAMP HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the Power Controller (OPAMP) peripheral:
  *           + Extended Initialization and de-initialization  functions
  *           + Extended Peripheral Control  functions
  *
  @verbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

/** @addtogroup STM32F3xx_HAL_Driver
  * @{
  */

#ifdef HAL_OPAMP_MODULE_ENABLED

#if defined (OPAMP1) || defined (OPAMP2) || defined (OPAMP3) || defined (OPAMP4)

/** @defgroup OPAMPEx OPAMPEx
  * @brief OPAMP Extended HAL module driver.
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/** @defgroup OPAMPEx_Exported_Functions OPAMP Extended Exported Functions
  * @{
  */


/** @defgroup OPAMPEx_Exported_Functions_Group1 Extended Input and Output operation functions
  * @brief    Extended Self calibration functions
  *
@verbatim
 ===============================================================================
              ##### Extended IO operation functions #####
 ===============================================================================
  [..]

@endverbatim
  * @{
  */

#if defined(STM32F302xE) || \
    defined(STM32F302xC)
/*  2 OPAMPS available */
/*  2 OPAMPS can be calibrated in parallel */

/**
  * @brief  Run the self calibration of 2 OPAMPs in parallel.
  * @param  hopamp1 handle
  * @param  hopamp2 handle
  * @retval HAL status
  * @note   Updated offset trimming values (PMOS & NMOS), user trimming is enabled
  * @note   Calibration runs about 25 ms.
  */

HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2)
{
  HAL_StatusTypeDef status = HAL_OK;

  uint32_t trimmingvaluen1;
  uint32_t trimmingvaluep1;
  uint32_t trimmingvaluen2;
  uint32_t trimmingvaluep2;

  uint32_t delta;

  if ((hopamp1 == NULL) || (hopamp2 == NULL))
  {
    status = HAL_ERROR;
  }
  /* Check if OPAMP in calibration mode and calibration not yet enable */
  else if (hopamp1->State !=  HAL_OPAMP_STATE_READY)
  {
    status = HAL_ERROR;
  }
  else if (hopamp2->State != HAL_OPAMP_STATE_READY)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp1->Instance));
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp2->Instance));

    /* Set Calibration mode */
    /* Non-inverting input connected to calibration reference voltage. */
    SET_BIT(hopamp1->Instance->CSR, OPAMP_CSR_FORCEVP);
    SET_BIT(hopamp2->Instance->CSR, OPAMP_CSR_FORCEVP);

    /*  user trimming values are used for offset calibration */
    SET_BIT(hopamp1->Instance->CSR, OPAMP_CSR_USERTRIM);
    SET_BIT(hopamp2->Instance->CSR, OPAMP_CSR_USERTRIM);

    /* Enable calibration */
    SET_BIT(hopamp1->Instance->CSR, OPAMP_CSR_CALON);
    SET_BIT(hopamp2->Instance->CSR, OPAMP_CSR_CALON);

    /* 1st calibration - N */
    /* Select 90U% VREF */
    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);

    /* Enable the opamps */
    SET_BIT(hopamp1->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    SET_BIT(hopamp2->Instance->CSR, OPAMP_CSR_OPAMPxEN);

    /* Init trimming counter */
    /* Medium value */
    trimmingvaluen1 = 16U;
    trimmingvaluen2 = 16U;
    delta = 8U;

    while (delta != 0U)
    {
      /* Set candidate trimming */
      MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen1 << OPAMP_INPUT_INVERTING);
      MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen2 << OPAMP_INPUT_INVERTING);

      /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
      /* Offset trim time: during calibration, minimum time needed between */
      /* two steps to have 1 mV accuracy */
      HAL_Delay(2U);

      if (hopamp1->Instance->CSR & OPAMP_CSR_OUTCAL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluen1 += delta;
      }
      else
      {
        /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
        trimmingvaluen1 -= delta;
      }

      if (hopamp2->Instance->CSR & OPAMP_CSR_OUTCAL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluen2 += delta;
      }
      else
      {
        /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
        trimmingvaluen2 -= delta;
      }

      delta >>= 1U;
    }

    // Still need to check if righ calibration is current value or un step below
    // Indeed the first value that causes the OUTCAL bit to change from 1 to 0
    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen1 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen2 << OPAMP_INPUT_INVERTING);

    /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
    /* Offset trim time: during calibration, minimum time needed between */
    /* two steps to have 1 mV accuracy */
    HAL_Delay(2U);

    if (hopamp1->Instance->CSR & OPAMP_CSR_OUTCAL)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluen1++;
      /* Set right trimming */
      MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen1 << OPAMP_INPUT_INVERTING);
    }

    if (hopamp2->Instance->CSR & OPAMP_CSR_OUTCAL)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluen2++;
      /* Set right trimming */
      MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen2 << OPAMP_INPUT_INVERTING);
    }

    /* 2nd calibration - P */
    /* Select 10U% VREF */
    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);

    /* Init trimming counter */
    /* Medium value */
    trimmingvaluep1 = 16U;
    trimmingvaluep2 = 16U;
    delta = 8U;

    while (delta != 0U)
    {
      /* Set candidate trimming */
      MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep1 << OPAMP_INPUT_NONINVERTING);
      MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep2 << OPAMP_INPUT_NONINVERTING);

      /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
      /* Offset trim time: during calibration, minimum time needed between */
      /* two steps to have 1 mV accuracy */
      HAL_Delay(2U);

      if (hopamp1->Instance->CSR & OPAMP_CSR_OUTCAL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluep1 += delta;
      }
      else
      {
        trimmingvaluep1 -= delta;
      }

      if (hopamp2->Instance->CSR & OPAMP_CSR_OUTCAL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluep2 += delta;
      }
      else
      {
        trimmingvaluep2 -= delta;
      }

      delta >>= 1U;
    }

    // Still need to check if righ calibration is current value or un step below
    // Indeed the first value that causes the OUTCAL bit to change from 1 to 0
    /* Set candidate trimming */
    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep1 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep2 << OPAMP_INPUT_NONINVERTING);

    /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
    /* Offset trim time: during calibration, minimum time needed between */
    /* two steps to have 1 mV accuracy */
    HAL_Delay(2U);

    if (hopamp1->Instance->CSR & OPAMP_CSR_OUTCAL)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluep1++;
      /* Set right trimming */
      MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep1 << OPAMP_INPUT_NONINVERTING);
    }

    if (hopamp2->Instance->CSR & OPAMP_CSR_OUTCAL)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluep2++;
      /* Set right trimming */
      MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep2 << OPAMP_INPUT_NONINVERTING);
    }

    /* Disable calibration */
    CLEAR_BIT(hopamp1->Instance->CSR, OPAMP_CSR_CALON);
    CLEAR_BIT(hopamp2->Instance->CSR, OPAMP_CSR_CALON);

    /* Disable the OPAMPs */
    CLEAR_BIT(hopamp1->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    CLEAR_BIT(hopamp2->Instance->CSR, OPAMP_CSR_OPAMPxEN);

    /* Set operating mode back */
    CLEAR_BIT(hopamp1->Instance->CSR, OPAMP_CSR_FORCEVP);
    CLEAR_BIT(hopamp2->Instance->CSR, OPAMP_CSR_FORCEVP);

    /* Self calibration is successful  */
    /* Store calibration(user timming) results in init structure. */
    /* Select user timming mode */

    /* Write calibration result N */
    hopamp1->Init.TrimmingValueN = trimmingvaluen1;
    hopamp2->Init.TrimmingValueN = trimmingvaluen2;

    /* Write calibration result P */
    hopamp1->Init.TrimmingValueP = trimmingvaluep1;
    hopamp2->Init.TrimmingValueP = trimmingvaluep2;

    /* Calibration */
    hopamp1->Init.UserTrimming = OPAMP_TRIMMING_USER;
    hopamp2->Init.UserTrimming = OPAMP_TRIMMING_USER;

    /* Select user timming mode */
    /* And updated with calibrated settings */
    hopamp1->Init.UserTrimming = OPAMP_TRIMMING_USER;
    hopamp2->Init.UserTrimming = OPAMP_TRIMMING_USER;

    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen1 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen2 << OPAMP_INPUT_INVERTING);

    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep1 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep2 << OPAMP_INPUT_NONINVERTING);

  }
  return status;
}
#endif /* STM32F302xE || */
	   /* STM32F302xC    */

#if defined(STM32F303xE) || defined(STM32F398xx) || \
    defined(STM32F303xC) || defined(STM32F358xx)
/*  4 OPAMPS available */
/*  4 OPAMPS can be calibrated in parallel */

/**
  * @brief  Run the self calibration of 4 OPAMPs in parallel.
  * @param  hopamp1 handle
  * @param  hopamp2 handle
  * @param  hopamp3 handle
  * @param  hopamp4 handle
  * @retval HAL status
  * @note   Updated offset trimming values (PMOS & NMOS), user trimming is enabled
  * @note   Calibration runs about 25 ms.
  */

HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2, OPAMP_HandleTypeDef *hopamp3, OPAMP_HandleTypeDef *hopamp4)
{
  HAL_StatusTypeDef status = HAL_OK;

  uint32_t trimmingvaluen1;
  uint32_t trimmingvaluep1;
  uint32_t trimmingvaluen2;
  uint32_t trimmingvaluep2;
  uint32_t trimmingvaluen3;
  uint32_t trimmingvaluep3;
  uint32_t trimmingvaluen4;
  uint32_t trimmingvaluep4;

  uint32_t delta;

  if ((hopamp1 == NULL) || (hopamp2 == NULL) || (hopamp3 == NULL) || (hopamp4 == NULL))
  {
    status = HAL_ERROR;
  }
  /* Check if OPAMP in calibration mode and calibration not yet enable */
  else if (hopamp1->State !=  HAL_OPAMP_STATE_READY)
  {
    status = HAL_ERROR;
  }
  else if (hopamp2->State != HAL_OPAMP_STATE_READY)
  {
    status = HAL_ERROR;
  }
  else if (hopamp3->State != HAL_OPAMP_STATE_READY)
  {
    status = HAL_ERROR;
  }
  else if (hopamp3->State != HAL_OPAMP_STATE_READY)
  {
    status = HAL_ERROR;
  }
  else
  {
    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp1->Instance));
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp2->Instance));
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp3->Instance));
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp4->Instance));

    /* Set Calibration mode */
    /* Non-inverting input connected to calibration reference voltage. */
    SET_BIT(hopamp1->Instance->CSR, OPAMP_CSR_FORCEVP);
    SET_BIT(hopamp2->Instance->CSR, OPAMP_CSR_FORCEVP);
    SET_BIT(hopamp3->Instance->CSR, OPAMP_CSR_FORCEVP);
    SET_BIT(hopamp4->Instance->CSR, OPAMP_CSR_FORCEVP);

    /*  user trimming values are used for offset calibration */
    SET_BIT(hopamp1->Instance->CSR, OPAMP_CSR_USERTRIM);
    SET_BIT(hopamp2->Instance->CSR, OPAMP_CSR_USERTRIM);
    SET_BIT(hopamp3->Instance->CSR, OPAMP_CSR_USERTRIM);
    SET_BIT(hopamp4->Instance->CSR, OPAMP_CSR_USERTRIM);

    /* Enable calibration */
    SET_BIT(hopamp1->Instance->CSR, OPAMP_CSR_CALON);
    SET_BIT(hopamp2->Instance->CSR, OPAMP_CSR_CALON);
    SET_BIT(hopamp3->Instance->CSR, OPAMP_CSR_CALON);
    SET_BIT(hopamp4->Instance->CSR, OPAMP_CSR_CALON);

    /* 1st calibration - N */
    /* Select 90U% VREF */
    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);
    MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);
    MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);

    /* Enable the opamps */
    SET_BIT(hopamp1->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    SET_BIT(hopamp2->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    SET_BIT(hopamp3->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    SET_BIT(hopamp4->Instance->CSR, OPAMP_CSR_OPAMPxEN);

    /* Init trimming counter */
    /* Medium value */
    trimmingvaluen1 = 16U;
    trimmingvaluen2 = 16U;
    trimmingvaluen3 = 16U;
    trimmingvaluen4 = 16U;
    delta = 8U;

    while (delta != 0U)
    {
      /* Set candidate trimming */
      MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen1 << OPAMP_INPUT_INVERTING);
      MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen2 << OPAMP_INPUT_INVERTING);
      MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen3 << OPAMP_INPUT_INVERTING);
      MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen4 << OPAMP_INPUT_INVERTING);

      /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
      /* Offset trim time: during calibration, minimum time needed between */
      /* two steps to have 1 mV accuracy */
      HAL_Delay(2U);

      if ((hopamp1->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluen1 += delta;
      }
      else
      {
        /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
        trimmingvaluen1 -= delta;
      }

      if ((hopamp2->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluen2 += delta;
      }
      else
      {
        /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
        trimmingvaluen2 -= delta;
      }

      if ((hopamp3->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluen3 += delta;
      }
      else
      {
        /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
        trimmingvaluen3 -= delta;
      }

      if ((hopamp4->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluen4 += delta;
      }
      else
      {
        /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
        trimmingvaluen4 -= delta;
      }

      delta >>= 1U;
    }

    /* Still need to check if righ calibration is current value or un step below */
    /* Indeed the first value that causes the OUTCAL bit to change from 1 to 0U */
    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen1 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen2 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen3 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen4 << OPAMP_INPUT_INVERTING);

    /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
    /* Offset trim time: during calibration, minimum time needed between */
    /* two steps to have 1 mV accuracy */
    HAL_Delay(2U);

    if ((hopamp1->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluen1++;
      /* Set right trimming */
      MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen1 << OPAMP_INPUT_INVERTING);
    }

    if ((hopamp2->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluen2++;
      /* Set right trimming */
      MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen2 << OPAMP_INPUT_INVERTING);
    }

    if ((hopamp3->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluen3++;
      /* Set right trimming */
      MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen3 << OPAMP_INPUT_INVERTING);
    }

    if ((hopamp4->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluen4++;
      /* Set right trimming */
      MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen4 << OPAMP_INPUT_INVERTING);
    }

    /* 2nd calibration - P */
    /* Select 10U% VREF */
    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);
    MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);
    MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);

    /* Init trimming counter */
    /* Medium value */
    trimmingvaluep1 = 16U;
    trimmingvaluep2 = 16U;
    trimmingvaluep3 = 16U;
    trimmingvaluep4 = 16U;

    delta = 8U;

    while (delta != 0U)
    {
      /* Set candidate trimming */
      MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep1 << OPAMP_INPUT_NONINVERTING);
      MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep2 << OPAMP_INPUT_NONINVERTING);
      MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep3 << OPAMP_INPUT_NONINVERTING);
      MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep4 << OPAMP_INPUT_NONINVERTING);

      /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
      /* Offset trim time: during calibration, minimum time needed between */
      /* two steps to have 1 mV accuracy */
      HAL_Delay(2U);

      if ((hopamp1->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluep1 += delta;
      }
      else
      {
        trimmingvaluep1 -= delta;
      }

      if ((hopamp2->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluep2 += delta;
      }
      else
      {
        trimmingvaluep2 -= delta;
      }

      if ((hopamp3->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluep3 += delta;
      }
      else
      {
        trimmingvaluep3 -= delta;
      }

      if ((hopamp4->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluep4 += delta;
      }
      else
      {
        trimmingvaluep4 -= delta;
      }

      delta >>= 1U;
    }

    /* Still need to check if righ calibration is current value or un step below */
    /* Indeed the first value that causes the OUTCAL bit to change from 1 to 0U */
    /* Set candidate trimming */
    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep1 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep2 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep3 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep4 << OPAMP_INPUT_NONINVERTING);

    /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
    /* Offset trim time: during calibration, minimum time needed between */
    /* two steps to have 1 mV accuracy */
    HAL_Delay(2U);

    if ((hopamp1->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
    {
      /* Trimming value is actually one value more */
      trimmingvaluep1++;
      /* Set right trimming */
      MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep1 << OPAMP_INPUT_NONINVERTING);
    }

    if ((hopamp2->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
    {
      /* Trimming value is actually one value more */
      trimmingvaluep2++;
      /* Set right trimming */
      MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep2 << OPAMP_INPUT_NONINVERTING);
    }

    if ((hopamp3->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
    {
      /* Trimming value is actually one value more */
      trimmingvaluep3++;
      /* Set right trimming */
      MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep3 << OPAMP_INPUT_NONINVERTING);
    }

    if ((hopamp4->Instance->CSR & OPAMP_CSR_OUTCAL) != RESET)
    {
      /* Trimming value is actually one value more */
      trimmingvaluep4++;
      /* Set right trimming */
      MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep4 << OPAMP_INPUT_NONINVERTING);
    }

    /* Disable calibration */
    CLEAR_BIT(hopamp1->Instance->CSR, OPAMP_CSR_CALON);
    CLEAR_BIT(hopamp2->Instance->CSR, OPAMP_CSR_CALON);
    CLEAR_BIT(hopamp3->Instance->CSR, OPAMP_CSR_CALON);
    CLEAR_BIT(hopamp4->Instance->CSR, OPAMP_CSR_CALON);

    /* Disable the OPAMPs */
    CLEAR_BIT(hopamp1->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    CLEAR_BIT(hopamp2->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    CLEAR_BIT(hopamp3->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    CLEAR_BIT(hopamp4->Instance->CSR, OPAMP_CSR_OPAMPxEN);

    /* Set normal operating mode back */
    CLEAR_BIT(hopamp1->Instance->CSR, OPAMP_CSR_FORCEVP);
    CLEAR_BIT(hopamp2->Instance->CSR, OPAMP_CSR_FORCEVP);
    CLEAR_BIT(hopamp3->Instance->CSR, OPAMP_CSR_FORCEVP);
    CLEAR_BIT(hopamp4->Instance->CSR, OPAMP_CSR_FORCEVP);

    /* Self calibration is successful  */
    /* Store calibration(user timming) results in init structure. */
    /* Select user timming mode */

    /* Write calibration result N */
    hopamp1->Init.TrimmingValueN = trimmingvaluen1;
    hopamp2->Init.TrimmingValueN = trimmingvaluen2;
    hopamp3->Init.TrimmingValueN = trimmingvaluen3;
    hopamp4->Init.TrimmingValueN = trimmingvaluen4;

    /* Write calibration result P */
    hopamp1->Init.TrimmingValueP = trimmingvaluep1;
    hopamp2->Init.TrimmingValueP = trimmingvaluep2;
    hopamp3->Init.TrimmingValueP = trimmingvaluep3;
    hopamp4->Init.TrimmingValueP = trimmingvaluep4;

    /* Select user timming mode */
    /* And updated with calibrated settings */
    hopamp1->Init.UserTrimming = OPAMP_TRIMMING_USER;
    hopamp2->Init.UserTrimming = OPAMP_TRIMMING_USER;
    hopamp3->Init.UserTrimming = OPAMP_TRIMMING_USER;
    hopamp4->Init.UserTrimming = OPAMP_TRIMMING_USER;

    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen1 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen2 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen3 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen4 << OPAMP_INPUT_INVERTING);

    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep1 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep2 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep3 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep4 << OPAMP_INPUT_NONINVERTING);
  }
  return status;
}
#endif /* STM32F303xE || STM32F398xx  || */
       /* STM32F303xC || STM32F358xx     */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* OPAMP1 || OPAMP2 || OPAMP3 || OPAMP4 */

#endif /* HAL_OPAMP_MODULE_ENABLED */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
