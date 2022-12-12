/**
 * \file
 *
 * \brief Top level header file
 *
 * Copyright (c) 2019 Microchip Technology Inc.
 *
 * \license_start
 *
 * \page License
 *
 * SPDX-License-Identifier: Apache-2.0
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
 *
 * \license_stop
 *
 */

#ifndef _SAM_
#define _SAM_

#if defined(__SAME70J19B__) || defined(__ATSAME70J19B__)
#include "same70j19b.h"
#elif defined(__SAME70J20B__) || defined(__ATSAME70J20B__)
#include "same70j20b.h"
#elif defined(__SAME70J21B__) || defined(__ATSAME70J21B__)
#include "same70j21b.h"
#elif defined(__SAME70N19B__) || defined(__ATSAME70N19B__)
#include "same70n19b.h"
#elif defined(__SAME70N20B__) || defined(__ATSAME70N20B__)
#include "same70n20b.h"
#elif defined(__SAME70N21B__) || defined(__ATSAME70N21B__)
#include "same70n21b.h"
#elif defined(__SAME70Q19B__) || defined(__ATSAME70Q19B__)
#include "same70q19b.h"
#elif defined(__SAME70Q20B__) || defined(__ATSAME70Q20B__)
#include "same70q20b.h"
#elif defined(__SAME70Q21B__) || defined(__ATSAME70Q21B__)
#include "same70q21b.h"
#else
#error Library does not support the specified device
#endif

#endif /* _SAM_ */
