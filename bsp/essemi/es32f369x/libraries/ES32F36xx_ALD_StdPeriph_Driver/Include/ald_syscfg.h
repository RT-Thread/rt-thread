/**
  *********************************************************************************
  *
  * @file    ald_syscfg.h
  * @brief   SYSCFG module driver.
  *
  * @version V1.0
  * @date    04 Jun 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#ifndef __ALD_SYSCFG_H__
#define __ALD_SYSCFG_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup SYSCFG SYSCFG
  * @brief SYSCFG module driver
  * @{
  */

/** @defgroup SYSCFG_Public_Macros SYSCFG Public Macros
  * @{
  */
#define SYSCFG_LOCK()  		WRITE_REG(SYSCFG->PROT, 0x0U)
#define SYSCFG_UNLOCK()		WRITE_REG(SYSCFG->PROT, 0x55AA6996U)
#define GET_SYSCFG_LOCK()	READ_BIT(SYSCFG->PROT, SYSCFG_PROT_PROT_MSK)

#define SYSCFG_BOOTFLASH_MAPPING_ENABLE()	SET_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_BFRMPEN_MSK)
#define SYSCFG_BOOTFLASH_MAPPING_DISABLE()	CLEAR_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_BFRMPEN_MSK)
/**
  * @}
  */

/** @defgroup SYSCFG_Public_Functions SYSCFG Public Functions
  * @{
  */
/**
  * @brief  Set the offset of the interrup vector map
  * @param  offset: Offset of the interrup vector map
  * @param  status: ENABLE/DISABLE
  * @retval None
  */
__STATIC_INLINE__ void ald_vtor_config(uint32_t offset, type_func_t status)
{
	SCB->VTOR = status ? (offset & ~0x3FU) : 0;
	return;
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

#ifdef __cplusplus
}
#endif

#endif
