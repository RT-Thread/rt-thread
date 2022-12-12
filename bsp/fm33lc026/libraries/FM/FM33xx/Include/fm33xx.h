/**
  ****************************************************************************************************
  * @file    fm33xx.h
  * @author  FMSH Application Team
  * @brief   Header file of FL Module
  ****************************************************************************************************
  * @attention
  *
  * Copyright (c) [2019] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under the Mulan PSL v1.
  * can use this software according to the terms and conditions of the Mulan PSL v1.
  * You may obtain a copy of Mulan PSL v1 at:
  * http://license.coscl.org.cn/MulanPSL
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR
  * PURPOSE.
  * See the Mulan PSL v1 for more details.
  *
  ****************************************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

#ifndef __FM33xx_H
#define __FM33xx_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

/** @addtogroup Library_configuration_section
  * @{
  */


/**
  * @brief FM33 Family
  */
#if !defined (FM33xx)
#define FM33xx
#endif /* FM33XX */
/**
  * @brief CMSIS Device version number
  */
#define __FM33x0xx_CMSIS_VERSION_MAIN   (0x02) /*!< [31:24] main version */
#define __FM33x0xx_CMSIS_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __FM33x0xx_CMSIS_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __FM33x0xx_CMSIS_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __FM33x0xx_CMSIS_VERSION        ((__FM33x0xx_CMSIS_VERSION_MAIN  << 24)\
                                         |(__FM33x0xx_CMSIS_VERSION_SUB1 << 16)\
                                         |(__FM33x0xx_CMSIS_VERSION_SUB2 << 8 )\
                                         |(__FM33x0xx_CMSIS_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */
#if defined(FM33L0XX)
  #include "fm33l0xx.h"
#elif defined(FM33LC0XX)
  #include "fm33lc0xx.h"
#elif defined(FM33LG0XX)
  #include "fm33lg0xx.h"
#else
 #error "Please select first the target FM33x0xx device used in your application (in FM33xxx.h file)"
#endif

/**
  * @}
  */

/** @addtogroup Exported_macro
  * @{
  */

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**
  * @}
  */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __FM33xx_H */

/**
  * @}
  */


/************************ (C) COPYRIGHT Fudan Microelectronics *****END OF FILE****/
