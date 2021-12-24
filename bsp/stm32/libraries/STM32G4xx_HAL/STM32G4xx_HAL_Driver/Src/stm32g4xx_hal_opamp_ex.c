/**
  ******************************************************************************
  * @file    stm32g4xx_hal_opamp_ex.c
  * @author  MCD Application Team
  * @brief   Extended OPAMP HAL module driver.
  *
  *          This file provides firmware functions to manage the following
  *          functionalities of the operational amplifiers (OPAMP1...OPAMP6)
  *          peripheral:
  *           + Extended Initialization and de-initialization functions
  *           + Extended Peripheral Control functions
  *
  @verbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

#ifdef HAL_OPAMP_MODULE_ENABLED

/** @defgroup OPAMPEx OPAMPEx
  * @brief OPAMP Extended HAL module driver
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

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
      (+) OPAMP Self calibration.

@endverbatim
  * @{
  */

/**
  * @brief  Run the self calibration of up to 6 OPAMPs in parallel.
  * @note   Calibration is performed in the mode specified in OPAMP init
  *         structure (mode normal or high-speed).
  * @param  hopamp1 handle
  * @param  hopamp2 handle
  * @param  hopamp3 handle
  * @param  hopamp4 handle  (1)
  * @param  hopamp5 handle  (1)
  * @param  hopamp6 handle  (1)
  *         (1) Parameter not present on STM32GBK1CB/STM32G431xx/STM32G441xx/STM32G471xx devices.
  * @retval HAL status
  * @note   Updated offset trimming values (PMOS & NMOS), user trimming is enabled
  * @note   Calibration runs about 25 ms.
  */

#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G484xx)
HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2,
                                               OPAMP_HandleTypeDef *hopamp3, OPAMP_HandleTypeDef *hopamp4, OPAMP_HandleTypeDef *hopamp5, OPAMP_HandleTypeDef *hopamp6)
#elif defined(STM32GBK1CB) || defined(STM32G431xx) || defined(STM32G441xx) || defined(STM32G471xx)
HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2,
                                               OPAMP_HandleTypeDef *hopamp3)
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
HAL_StatusTypeDef HAL_OPAMPEx_SelfCalibrateAll(OPAMP_HandleTypeDef *hopamp1, OPAMP_HandleTypeDef *hopamp2,
                                               OPAMP_HandleTypeDef *hopamp3, OPAMP_HandleTypeDef *hopamp6)
#endif
{
  uint32_t trimmingvaluen1;
  uint32_t trimmingvaluep1;
  uint32_t trimmingvaluen2;
  uint32_t trimmingvaluep2;
  uint32_t trimmingvaluen3;
  uint32_t trimmingvaluep3;
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
  uint32_t trimmingvaluen4;
  uint32_t trimmingvaluep4;
  uint32_t trimmingvaluen5;
  uint32_t trimmingvaluep5;
  uint32_t trimmingvaluen6;
  uint32_t trimmingvaluep6;
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
  uint32_t trimmingvaluen6;
  uint32_t trimmingvaluep6;
#endif

  uint32_t delta;

  if ((hopamp1 == NULL) || (hopamp2 == NULL) || (hopamp3 == NULL)
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
      || (hopamp4 == NULL) || (hopamp5 == NULL) || (hopamp6 == NULL)
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
      || (hopamp6 == NULL)
#endif
     )
  {
    return HAL_ERROR;
  }
  else if (hopamp1->State != HAL_OPAMP_STATE_READY)
  {
    return HAL_ERROR;
  }
  else if (hopamp2->State != HAL_OPAMP_STATE_READY)
  {
    return HAL_ERROR;
  }
  else if (hopamp3->State != HAL_OPAMP_STATE_READY)
  {
    return HAL_ERROR;
  }
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
  else if (hopamp4->State != HAL_OPAMP_STATE_READY)
  {
    return HAL_ERROR;
  }
  else if (hopamp5->State != HAL_OPAMP_STATE_READY)
  {
    return HAL_ERROR;
  }
  else if (hopamp6->State != HAL_OPAMP_STATE_READY)
  {
    return HAL_ERROR;
  }
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
  else if (hopamp6->State != HAL_OPAMP_STATE_READY)
  {
    return HAL_ERROR;
  }
#endif
  else
  {

    /* Check the parameter */
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp1->Instance));
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp2->Instance));
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp3->Instance));
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp4->Instance));
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp5->Instance));
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp6->Instance));
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    assert_param(IS_OPAMP_ALL_INSTANCE(hopamp6->Instance));
#endif

    /* Set Calibration mode */
    /* Non-inverting input connected to calibration reference voltage. */
    SET_BIT(hopamp1->Instance->CSR, OPAMP_CSR_FORCEVP);
    SET_BIT(hopamp2->Instance->CSR, OPAMP_CSR_FORCEVP);
    SET_BIT(hopamp3->Instance->CSR, OPAMP_CSR_FORCEVP);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    SET_BIT(hopamp4->Instance->CSR, OPAMP_CSR_FORCEVP);
    SET_BIT(hopamp5->Instance->CSR, OPAMP_CSR_FORCEVP);
    SET_BIT(hopamp6->Instance->CSR, OPAMP_CSR_FORCEVP);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    SET_BIT(hopamp6->Instance->CSR, OPAMP_CSR_FORCEVP);
#endif

    /*  user trimming values are used for offset calibration */
    SET_BIT(hopamp1->Instance->CSR, OPAMP_CSR_USERTRIM);
    SET_BIT(hopamp2->Instance->CSR, OPAMP_CSR_USERTRIM);
    SET_BIT(hopamp3->Instance->CSR, OPAMP_CSR_USERTRIM);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    SET_BIT(hopamp4->Instance->CSR, OPAMP_CSR_USERTRIM);
    SET_BIT(hopamp5->Instance->CSR, OPAMP_CSR_USERTRIM);
    SET_BIT(hopamp6->Instance->CSR, OPAMP_CSR_USERTRIM);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    SET_BIT(hopamp6->Instance->CSR, OPAMP_CSR_USERTRIM);
#endif

    /* Enable calibration */
    SET_BIT(hopamp1->Instance->CSR, OPAMP_CSR_CALON);
    SET_BIT(hopamp2->Instance->CSR, OPAMP_CSR_CALON);
    SET_BIT(hopamp3->Instance->CSR, OPAMP_CSR_CALON);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    SET_BIT(hopamp4->Instance->CSR, OPAMP_CSR_CALON);
    SET_BIT(hopamp5->Instance->CSR, OPAMP_CSR_CALON);
    SET_BIT(hopamp6->Instance->CSR, OPAMP_CSR_CALON);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    SET_BIT(hopamp6->Instance->CSR, OPAMP_CSR_CALON);
#endif

    /* 1st calibration - N */
    /* Select 90% VREF */
    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);
    MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);
    MODIFY_REG(hopamp5->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);
    MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_90VDDA);
#endif

    /* Enable the opamps */
    SET_BIT(hopamp1->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    SET_BIT(hopamp2->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    SET_BIT(hopamp3->Instance->CSR, OPAMP_CSR_OPAMPxEN);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    SET_BIT(hopamp4->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    SET_BIT(hopamp5->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    SET_BIT(hopamp6->Instance->CSR, OPAMP_CSR_OPAMPxEN);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    SET_BIT(hopamp6->Instance->CSR, OPAMP_CSR_OPAMPxEN);
#endif

    /* Init trimming counter */
    /* Medium value */
    trimmingvaluen1 = 16UL;
    trimmingvaluen2 = 16UL;
    trimmingvaluen3 = 16UL;
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    trimmingvaluen4 = 16UL;
    trimmingvaluen5 = 16UL;
    trimmingvaluen6 = 16UL;
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    trimmingvaluen6 = 16UL;
#endif
    delta = 8UL;

    while (delta != 0UL)
    {
      /* Set candidate trimming */
      MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen1 << OPAMP_INPUT_INVERTING);
      MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen2 << OPAMP_INPUT_INVERTING);
      MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen3 << OPAMP_INPUT_INVERTING);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
      MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen4 << OPAMP_INPUT_INVERTING);
      MODIFY_REG(hopamp5->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen5 << OPAMP_INPUT_INVERTING);
      MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen6 << OPAMP_INPUT_INVERTING);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
      MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen6 << OPAMP_INPUT_INVERTING);
#endif

      /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
      /* Offset trim time: during calibration, minimum time needed between */
      /* two steps to have 1 mV accuracy */
      HAL_Delay(2);

      if ((hopamp1->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluen1 += delta;
      }
      else
      {
        /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
        trimmingvaluen1 -= delta;
      }

      if ((hopamp2->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluen2 += delta;
      }
      else
      {
        /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
        trimmingvaluen2 -= delta;
      }

      if ((hopamp3->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluen3 += delta;
      }
      else
      {
        /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
        trimmingvaluen3 -= delta;
      }

#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
      if ((hopamp4->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluen4 += delta;
      }
      else
      {
        /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
        trimmingvaluen4 -= delta;
      }

      if ((hopamp5->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluen5 += delta;
      }
      else
      {
        /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
        trimmingvaluen5 -= delta;
      }

      if ((hopamp6->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluen6 += delta;
      }
      else
      {
        /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
        trimmingvaluen6 -= delta;
      }

#elif defined(STM32G491xx) || defined(STM32G4A1xx)
      if ((hopamp6->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluen6 += delta;
      }
      else
      {
        /* OPAMP_CSR_OUTCAL is LOW try lower trimming */
        trimmingvaluen6 -= delta;
      }
#endif

      delta >>= 1;
    }

    /* Still need to check if righ calibration is current value or un step below */
    /* Indeed the first value that causes the OUTCAL bit to change from 1 to 0 */
    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen1 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen2 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen3 << OPAMP_INPUT_INVERTING);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen4 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp5->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen5 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen6 << OPAMP_INPUT_INVERTING);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen6 << OPAMP_INPUT_INVERTING);
#endif

    /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
    /* Offset trim time: during calibration, minimum time needed between */
    /* two steps to have 1 mV accuracy */
    HAL_Delay(2);

    if ((hopamp1->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluen1++;
      /* Set right trimming */
      MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen1 << OPAMP_INPUT_INVERTING);
    }

    if ((hopamp2->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluen2++;
      /* Set right trimming */
      MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen2 << OPAMP_INPUT_INVERTING);
    }

    if ((hopamp3->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluen3++;
      /* Set right trimming */
      MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen3 << OPAMP_INPUT_INVERTING);
    }

#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    if ((hopamp4->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluen4++;
      /* Set right trimming */
      MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen4 << OPAMP_INPUT_INVERTING);
    }

    if ((hopamp5->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluen5++;
      /* Set right trimming */
      MODIFY_REG(hopamp5->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen5 << OPAMP_INPUT_INVERTING);
    }

    if ((hopamp6->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluen6++;
      /* Set right trimming */
      MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen6 << OPAMP_INPUT_INVERTING);
    }

#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    if ((hopamp6->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* OPAMP_CSR_OUTCAL is actually one value more */
      trimmingvaluen6++;
      /* Set right trimming */
      MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen6 << OPAMP_INPUT_INVERTING);
    }
#endif

    /* 2nd calibration - P */
    /* Select 10% VREF */
    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);
    MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);
    MODIFY_REG(hopamp5->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);
    MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_CALSEL, OPAMP_VREF_10VDDA);
#endif

    /* Init trimming counter */
    /* Medium value */
    trimmingvaluep1 = 16UL;
    trimmingvaluep2 = 16UL;
    trimmingvaluep3 = 16UL;
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    trimmingvaluep4 = 16UL;
    trimmingvaluep5 = 16UL;
    trimmingvaluep6 = 16UL;
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    trimmingvaluep6 = 16UL;
#endif

    delta = 8UL;

    while (delta != 0UL)
    {
      /* Set candidate trimming */
      MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep1 << OPAMP_INPUT_NONINVERTING);
      MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep2 << OPAMP_INPUT_NONINVERTING);
      MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep3 << OPAMP_INPUT_NONINVERTING);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
      MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep4 << OPAMP_INPUT_NONINVERTING);
      MODIFY_REG(hopamp5->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep5 << OPAMP_INPUT_NONINVERTING);
      MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep6 << OPAMP_INPUT_NONINVERTING);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
      MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep6 << OPAMP_INPUT_NONINVERTING);
#endif

      /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
      /* Offset trim time: during calibration, minimum time needed between */
      /* two steps to have 1 mV accuracy */
      HAL_Delay(2);

      if ((hopamp1->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluep1 += delta;
      }
      else
      {
        trimmingvaluep1 -= delta;
      }

      if ((hopamp2->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluep2 += delta;
      }
      else
      {
        trimmingvaluep2 -= delta;
      }

      if ((hopamp3->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluep3 += delta;
      }
      else
      {
        trimmingvaluep3 -= delta;
      }

#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
      if ((hopamp4->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluep4 += delta;
      }
      else
      {
        trimmingvaluep4 -= delta;
      }

      if ((hopamp5->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluep5 += delta;
      }
      else
      {
        trimmingvaluep5 -= delta;
      }

      if ((hopamp6->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluep6 += delta;
      }
      else
      {
        trimmingvaluep6 -= delta;
      }

#elif defined(STM32G491xx) || defined(STM32G4A1xx)
      if ((hopamp6->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
      {
        /* OPAMP_CSR_OUTCAL is HIGH try higher trimming */
        trimmingvaluep6 += delta;
      }
      else
      {
        trimmingvaluep6 -= delta;
      }
#endif

      delta >>= 1;
    }

    /* Still need to check if righ calibration is current value or un step below */
    /* Indeed the first value that causes the OUTCAL bit to change from 1 to 0 */
    /* Set candidate trimming */
    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep1 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep2 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep3 << OPAMP_INPUT_NONINVERTING);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep4 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp5->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep5 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep6 << OPAMP_INPUT_NONINVERTING);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep6 << OPAMP_INPUT_NONINVERTING);
#endif

    /* OFFTRIMmax delay 2 ms as per datasheet (electrical characteristics */
    /* Offset trim time: during calibration, minimum time needed between */
    /* two steps to have 1 mV accuracy */
    HAL_Delay(2);

    if ((hopamp1->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* Trimming value is actually one value more */
      trimmingvaluep1++;
      /* Set right trimming */
      MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep1 << OPAMP_INPUT_NONINVERTING);
    }

    if ((hopamp2->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* Trimming value is actually one value more */
      trimmingvaluep2++;
      /* Set right trimming */
      MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep2 << OPAMP_INPUT_NONINVERTING);
    }

    if ((hopamp3->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* Trimming value is actually one value more */
      trimmingvaluep3++;
      /* Set right trimming */
      MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep3 << OPAMP_INPUT_NONINVERTING);
    }

#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    if ((hopamp4->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* Trimming value is actually one value more */
      trimmingvaluep4++;
      /* Set right trimming */
      MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep4 << OPAMP_INPUT_NONINVERTING);
    }

    if ((hopamp5->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* Trimming value is actually one value more */
      trimmingvaluep5++;
      /* Set right trimming */
      MODIFY_REG(hopamp5->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep5 << OPAMP_INPUT_NONINVERTING);
    }

    if ((hopamp6->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* Trimming value is actually one value more */
      trimmingvaluep6++;
      /* Set right trimming */
      MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep6 << OPAMP_INPUT_NONINVERTING);
    }

#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    if ((hopamp6->Instance->CSR & OPAMP_CSR_OUTCAL) != 0UL)
    {
      /* Trimming value is actually one value more */
      trimmingvaluep6++;
      /* Set right trimming */
      MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep6 << OPAMP_INPUT_NONINVERTING);
    }
#endif

    /* Disable calibration */
    CLEAR_BIT(hopamp1->Instance->CSR, OPAMP_CSR_CALON);
    CLEAR_BIT(hopamp2->Instance->CSR, OPAMP_CSR_CALON);
    CLEAR_BIT(hopamp3->Instance->CSR, OPAMP_CSR_CALON);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    CLEAR_BIT(hopamp4->Instance->CSR, OPAMP_CSR_CALON);
    CLEAR_BIT(hopamp5->Instance->CSR, OPAMP_CSR_CALON);
    CLEAR_BIT(hopamp6->Instance->CSR, OPAMP_CSR_CALON);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    CLEAR_BIT(hopamp6->Instance->CSR, OPAMP_CSR_CALON);
#endif

    /* Disable the OPAMPs */
    CLEAR_BIT(hopamp1->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    CLEAR_BIT(hopamp2->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    CLEAR_BIT(hopamp3->Instance->CSR, OPAMP_CSR_OPAMPxEN);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    CLEAR_BIT(hopamp4->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    CLEAR_BIT(hopamp5->Instance->CSR, OPAMP_CSR_OPAMPxEN);
    CLEAR_BIT(hopamp6->Instance->CSR, OPAMP_CSR_OPAMPxEN);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    CLEAR_BIT(hopamp6->Instance->CSR, OPAMP_CSR_OPAMPxEN);
#endif

    /* Set normal operating mode back */
    CLEAR_BIT(hopamp1->Instance->CSR, OPAMP_CSR_FORCEVP);
    CLEAR_BIT(hopamp2->Instance->CSR, OPAMP_CSR_FORCEVP);
    CLEAR_BIT(hopamp3->Instance->CSR, OPAMP_CSR_FORCEVP);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    CLEAR_BIT(hopamp4->Instance->CSR, OPAMP_CSR_FORCEVP);
    CLEAR_BIT(hopamp5->Instance->CSR, OPAMP_CSR_FORCEVP);
    CLEAR_BIT(hopamp6->Instance->CSR, OPAMP_CSR_FORCEVP);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    CLEAR_BIT(hopamp6->Instance->CSR, OPAMP_CSR_FORCEVP);
#endif

    /* Self calibration is successful  */
    /* Store calibration(user timing) results in init structure. */
    /* Select user timing mode */

    /* Write calibration result N */
    hopamp1->Init.TrimmingValueN = trimmingvaluen1;
    hopamp2->Init.TrimmingValueN = trimmingvaluen2;
    hopamp3->Init.TrimmingValueN = trimmingvaluen3;
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    hopamp4->Init.TrimmingValueN = trimmingvaluen4;
    hopamp5->Init.TrimmingValueN = trimmingvaluen5;
    hopamp6->Init.TrimmingValueN = trimmingvaluen6;
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    hopamp6->Init.TrimmingValueN = trimmingvaluen6;
#endif

    /* Write calibration result P */
    hopamp1->Init.TrimmingValueP = trimmingvaluep1;
    hopamp2->Init.TrimmingValueP = trimmingvaluep2;
    hopamp3->Init.TrimmingValueP = trimmingvaluep3;
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    hopamp4->Init.TrimmingValueP = trimmingvaluep4;
    hopamp5->Init.TrimmingValueP = trimmingvaluep5;
    hopamp6->Init.TrimmingValueP = trimmingvaluep6;
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    hopamp6->Init.TrimmingValueP = trimmingvaluep6;
#endif

    /* Select user timing mode */
    /* And updated with calibrated settings */
    hopamp1->Init.UserTrimming = OPAMP_TRIMMING_USER;
    hopamp2->Init.UserTrimming = OPAMP_TRIMMING_USER;
    hopamp3->Init.UserTrimming = OPAMP_TRIMMING_USER;
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    hopamp4->Init.UserTrimming = OPAMP_TRIMMING_USER;
    hopamp5->Init.UserTrimming = OPAMP_TRIMMING_USER;
    hopamp6->Init.UserTrimming = OPAMP_TRIMMING_USER;
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    hopamp6->Init.UserTrimming = OPAMP_TRIMMING_USER;
#endif

    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen1 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen2 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen3 << OPAMP_INPUT_INVERTING);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen4 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp5->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen5 << OPAMP_INPUT_INVERTING);
    MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen6 << OPAMP_INPUT_INVERTING);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETN, trimmingvaluen6 << OPAMP_INPUT_INVERTING);
#endif

    MODIFY_REG(hopamp1->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep1 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp2->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep2 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp3->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep3 << OPAMP_INPUT_NONINVERTING);
#if defined(STM32G473xx) || defined(STM32G474xx) || defined(STM32G483xx) || defined(STM32G483xx)
    MODIFY_REG(hopamp4->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep4 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp5->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep5 << OPAMP_INPUT_NONINVERTING);
    MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep6 << OPAMP_INPUT_NONINVERTING);
#elif defined(STM32G491xx) || defined(STM32G4A1xx)
    MODIFY_REG(hopamp6->Instance->CSR, OPAMP_CSR_TRIMOFFSETP, trimmingvaluep6 << OPAMP_INPUT_NONINVERTING);
#endif

  }

  return HAL_OK;
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

#endif /* HAL_OPAMP_MODULE_ENABLED */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
