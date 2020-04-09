/**
  *********************************************************************************
  *
  * @file    ald_calc.c
  * @brief   CALC module driver.
  *
  * @version V1.0
  * @date    04 Dec 2017
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
      (+) Division.
      (+) Get DZ flag.

    @endverbatim
  * @{
  */

/**
  * @brief  Square root operation.
  * @param  data: The data;
  * @retval The value of square root.
  */
uint32_t ald_calc_sqrt(uint32_t data)
{
    WRITE_REG(CALC->RDCND, data);

    while (READ_BIT(CALC->SQRTSR, CALC_SQRTSR_BUSY_MSK));

    return READ_REG(CALC->SQRTRES);
}

/**
  * @brief  Calculating division.
  * @param  dividend: The value of the dividend.
  * @param  divisor: The value of the divisor.
  * @param  remainder: The value of the remainder.
  * @retval The result of division.
  */
uint32_t ald_calc_div(uint32_t dividend, uint32_t divisor, uint32_t *remainder)
{
    CLEAR_BIT(CALC->DIVCSR, CALC_DIVCSR_SIGN_MSK);
    SET_BIT(CALC->DIVCSR, CALC_DIVCSR_TRM_MSK);
    WRITE_REG(CALC->DIVDR, dividend);
    WRITE_REG(CALC->DIVSR, divisor);

    while (READ_BIT(CALC->DIVCSR, CALC_DIVCSR_BUSY_MSK));

    *remainder = READ_REG(CALC->DIVRR);
    return READ_REG(CALC->DIVQR);
}

/**
  * @brief  Calculating division.
  * @param  dividend: The value of the dividend.
  * @param  divisor: The value of the divisor.
  * @param  remainder: The value of the remainder.
  * @retval The result of division.
  */
int32_t ald_calc_div_sign(int32_t dividend, int32_t divisor, int32_t *remainder)
{
    SET_BIT(CALC->DIVCSR, CALC_DIVCSR_SIGN_MSK);
    SET_BIT(CALC->DIVCSR, CALC_DIVCSR_TRM_MSK);
    WRITE_REG(CALC->DIVDR, dividend);
    WRITE_REG(CALC->DIVSR, divisor);

    while (READ_BIT(CALC->DIVCSR, CALC_DIVCSR_BUSY_MSK));

    *remainder = READ_REG(CALC->DIVRR);
    return READ_REG(CALC->DIVQR);
}

/**
  * @brief  Get the flag of divisor is zero.
  * @retval The status, SET/RESET.
  */
flag_status_t ald_calc_get_dz_status(void)
{
    if (READ_BIT(CALC->DIVCSR, CALC_DIVCSR_DZ_MSK))
        return SET;

    return RESET;
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
