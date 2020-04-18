/**
  *********************************************************************************
  *
  * @file    ald_calc.h
  * @brief   Header file of CALC module driver.
  *
  * @version V1.0
  * @date    26 Jun 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ********************************************************************************
  */

#ifndef __ALD_CALC_H__
#define __ALD_CALC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup CALC
  * @{
  */

/** @addtogroup CALC_Public_Functions
  * @{
  */
extern uint32_t ald_calc_sqrt(uint32_t data);
extern uint32_t ald_calc_div(uint32_t dividend, uint32_t divisor, uint32_t *remainder);
extern int32_t ald_calc_div_sign(int32_t dividend, int32_t divisor, int32_t *remainder);
extern flag_status_t ald_calc_get_dz_status(void);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* __ALD_CALC_H__ */
