/**
  *********************************************************************************
  *
  * @file    ald_calc.c
  * @brief   CALC module driver.
  *
  * @version V1.0
  * @date    26 Jun 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#include "ald_calc.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup CALC CALC
  * @brief CALC module driver
  * @{
  */
#ifdef ALD_CALC

/** @defgroup CALC_Public_Functions CALC Public Functions
  * @brief    Accelerating calculate functions
  *
  * @verbatim
  ==============================================================================
              ##### Accelerating calculate functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Square root operation.

    @endverbatim
  * @{
  */

/**
  * @brief  Square root operation.
  * @param  data: The  radicand.
  * @retval The value of square root.
  */
uint32_t ald_calc_sqrt(uint32_t data)
{
	WRITE_REG(CALC->RDCND, data);
	while (READ_BIT(CALC->SQRTSR, CALC_SQRTSR_BUSY_MSK));

	return READ_REG(CALC->SQRTRES);
}
/**
  * @}
  */
#endif /* ALD_CALC */
/**
  * @}
  */
/**
  * @}
  */
