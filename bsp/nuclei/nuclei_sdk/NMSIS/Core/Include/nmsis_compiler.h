/*
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __NMSIS_COMPILER_H
#define __NMSIS_COMPILER_H

#include <stdint.h>

/*!
 * @file     nmsis_compiler.h
 * @brief    NMSIS compiler generic header file
 */
#if defined ( __GNUC__ )
  /** GNU GCC Compiler */
  #include "nmsis_gcc.h"
#else
  #error Unknown compiler.
#endif


#endif /* __NMSIS_COMPILER_H */

