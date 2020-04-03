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
#ifndef __NMSIS_VERSION_H
#define __NMSIS_VERSION_H

/**
 * \defgroup NMSIS_Core_VersionControl    Version Control
 * \ingroup  NMSIS_Core
 * \brief    Version \#define symbols for NMSIS release specific C/C++ source code
 * \details
 *
 * We followed the [semantic versioning 2.0.0](https://semver.org/) to control NMSIS version.
 * The version format is **MAJOR.MINOR.PATCH**, increment the:
 * 1. MAJOR version when you make incompatible API changes,
 * 2. MINOR version when you add functionality in a backwards compatible manner, and
 * 3. PATCH version when you make backwards compatible bug fixes.
 *
 * The header file `nmsis_version.h` is included by each core header so that these definitions are available.
 *
 * **Example Usage for NMSIS Version Check**:
 * \code
 *   #if defined(__NMSIS_VERSION) && (__NMSIS_VERSION >= 0x00010105)
 *      #warning "Yes, we have NMSIS 1.1.5 or later"
 *   #else
 *      #error "We need NMSIS 1.1.5 or later!"
 *   #endif
 * \endcode
 *
 * @{
 */

/*!
 * \file     nmsis_version.h
 * \brief    NMSIS Version definitions
 **/

/**
 * \brief   Represent the NMSIS major version
 * \details
 * The NMSIS major version can be used to
 * differentiate between NMSIS major releases.
 * */
#define __NMSIS_VERSION_MAJOR            (1U)

/**
 * \brief   Represent the NMSIS minor version
 * \details
 * The NMSIS minor version can be used to
 * query a NMSIS release update including new features.
 *
 **/
#define __NMSIS_VERSION_MINOR            (0U)

/**
 * \brief   Represent the NMSIS patch version
 * \details
 * The NMSIS patch version can be used to
 * show bug fixes in this package.
 **/
#define __NMSIS_VERSION_PATCH            (0U)
/**
 * \brief   Represent the NMSIS Version
 * \details
 * NMSIS Version format: **MAJOR.MINOR.PATCH**
 * * MAJOR: \ref __NMSIS_VERSION_MAJOR, stored in `bits [31:16]` of \ref __NMSIS_VERSION
 * * MINOR: \ref __NMSIS_VERSION_MINOR, stored in `bits [15:8]` of \ref __NMSIS_VERSION
 * * PATCH: \ref __NMSIS_VERSION_PATCH, stored in `bits [7:0]` of \ref __NMSIS_VERSION
 **/
#define __NMSIS_VERSION                  ((__NMSIS_VERSION_MAJOR << 16U) | (__NMSIS_VERSION_MINOR << 8) | __NMSIS_VERSION_PATCH)

/** @} */ /* End of Doxygen Group NMSIS_Core_VersionControl */
#endif
