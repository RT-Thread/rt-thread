/**
 * \file
 *
 * \brief Top level header file
 *
 * Copyright (c) 2018 Microchip Technology Inc.
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

#if defined(__SAMC21E15A__) || defined(__ATSAMC21E15A__)
#include "samc21e15a.h"
#elif defined(__SAMC21E16A__) || defined(__ATSAMC21E16A__)
#include "samc21e16a.h"
#elif defined(__SAMC21E17A__) || defined(__ATSAMC21E17A__)
#include "samc21e17a.h"
#elif defined(__SAMC21E18A__) || defined(__ATSAMC21E18A__)
#include "samc21e18a.h"
#elif defined(__SAMC21G15A__) || defined(__ATSAMC21G15A__)
#include "samc21g15a.h"
#elif defined(__SAMC21G16A__) || defined(__ATSAMC21G16A__)
#include "samc21g16a.h"
#elif defined(__SAMC21G17A__) || defined(__ATSAMC21G17A__)
#include "samc21g17a.h"
#elif defined(__SAMC21G18A__) || defined(__ATSAMC21G18A__)
#include "samc21g18a.h"
#elif defined(__SAMC21J15A__) || defined(__ATSAMC21J15A__)
#include "samc21j15a.h"
#elif defined(__SAMC21J16A__) || defined(__ATSAMC21J16A__)
#include "samc21j16a.h"
#elif defined(__SAMC21J17A__) || defined(__ATSAMC21J17A__)
#include "samc21j17a.h"
#elif defined(__SAMC21J17AU__) || defined(__ATSAMC21J17AU__)
#include "samc21j17au.h"
#elif defined(__SAMC21J18A__) || defined(__ATSAMC21J18A__)
#include "samc21j18a.h"
#elif defined(__SAMC21J18AU__) || defined(__ATSAMC21J18AU__)
#include "samc21j18au.h"
#else
#error Library does not support the specified device
#endif

#endif /* _SAM_ */
