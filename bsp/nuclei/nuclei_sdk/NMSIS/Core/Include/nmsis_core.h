/*
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
 * -- Adaptable modifications made for Nuclei Processors. --
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
#ifndef __NMSIS_CORE_H__
#define __NMSIS_CORE_H__

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

#include "nmsis_version.h"

/**
 * \ingroup NMSIS_Core_VersionControl
 * @{
 */
/* The following enum __NUCLEI_N_REV/__NUCLEI_NX_REV definition in this file
 * is only used for doxygen documentation generation,
 * The <device>.h is the real file to define it by vendor
 */
#if defined(__ONLY_FOR_DOXYGEN_DOCUMENT_GENERATION__)
/**
 * \brief Nuclei N class core revision number
 * \details
 * Reversion number format: [15:8] revision number, [7:0] patch number
 * \attention
 * This define is exclusive with \ref __NUCLEI_NX_REV
 */
#define __NUCLEI_N_REV                   (0x0104)
/**
 * \brief Nuclei NX class core revision number
 * \details
 * Reversion number format: [15:8] revision number, [7:0] patch number
 * \attention
 * This define is exclusive with \ref __NUCLEI_N_REV
 */
#define __NUCLEI_NX_REV                  (0x0100)
#endif /* __ONLY_FOR_DOXYGEN_DOCUMENT_GENERATION__ */
/** @} */ /* End of Group NMSIS_Core_VersionControl */

#include "nmsis_compiler.h"     /* NMSIS compiler specific defines */

/* === Include Nuclei Core Related Headers === */
/* Include core base feature header file */
#include "core_feature_base.h"

#ifndef __NMSIS_GENERIC
/* Include core eclic feature header file */
#include "core_feature_eclic.h"
/* Include core systimer feature header file */
#include "core_feature_timer.h"
#endif

/* Include core fpu feature header file */
#include "core_feature_fpu.h"
/* Include core dsp feature header file */
#include "core_feature_dsp.h"
/* Include core pmp feature header file */
#include "core_feature_pmp.h"
/* Include core cache feature header file */
#include "core_feature_cache.h"

/* Include compatiable functions header file */
#include "core_compatiable.h"

#ifdef __cplusplus
}
#endif
#endif /* __NMSIS_CORE_H__ */
