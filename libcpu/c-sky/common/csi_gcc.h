/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     csi_gcc.h
 * @brief    CSI Header File for GCC.
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#ifndef _CSI_GCC_H_
#define _CSI_GCC_H_

#define __ASM            __asm                                      /*!< asm keyword for GNU Compiler */
#define __INLINE         inline                                     /*!< inline keyword for GNU Compiler */
#define __ALWAYS_INLINE  __attribute__((always_inline)) static inline

#include <stdlib.h>
#include "csi_reg.h"
#include "csi_instr.h"
#include "csi_simd.h"

#endif /* _CSI_GCC_H_ */
