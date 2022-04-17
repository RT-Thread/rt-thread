/**
 * \file
 *
 * \brief Top header file for SAME54
 *
 * Copyright (c) 2019 Microchip Technology Inc.
 *
 * \asf_license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the Licence at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * \asf_license_stop
 *
 */

#ifndef _SAME54_
#define _SAME54_

/**
 * \defgroup SAME54_definitions SAME54 Device Definitions
 * \brief SAME54 CMSIS Definitions.
 */

#if   defined(__SAME54N19A__) || defined(__ATSAME54N19A__)
  #include "same54n19a.h"
#elif defined(__SAME54N20A__) || defined(__ATSAME54N20A__)
  #include "same54n20a.h"
#elif defined(__SAME54P19A__) || defined(__ATSAME54P19A__)
  #include "same54p19a.h"
#elif defined(__SAME54P20A__) || defined(__ATSAME54P20A__)
  #include "same54p20a.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAME54_ */
