/**
  ****************************************************************************************************
  * @file    fm33_assert.h
  * @author  FMSH Application Team
  * @brief   Assert function define
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
#ifndef __FM33_ASSERT_H
#define __FM33_ASSERT_H
#include "fm33xx.h"
#ifdef __cplusplus
 extern "C" {
#endif


#ifdef  USE_FULL_ASSERT
#define assert_param(expr) do{if((expr) == 0)for(;;);}while(0)
#else
#define assert_param(expr) ((void)0U)
#endif

#ifdef __cplusplus
}
#endif


#endif

