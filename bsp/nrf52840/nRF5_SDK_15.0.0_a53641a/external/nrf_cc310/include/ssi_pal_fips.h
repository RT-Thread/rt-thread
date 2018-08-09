/**************************************************************************************
* Copyright (c) 2016-2017, ARM Limited or its affiliates. All rights reserved         *
*                                                                                     *
* This file and the related binary are licensed under the following license:          *
*                                                                                     *
* ARM Object Code and Header Files License, v1.0 Redistribution.                      *
*                                                                                     *
* Redistribution and use of object code, header files, and documentation, without     *
* modification, are permitted provided that the following conditions are met:         *
*                                                                                     *
* 1) Redistributions must reproduce the above copyright notice and the                *
*    following disclaimer in the documentation and/or other materials                 *
*    provided with the distribution.                                                  *
*                                                                                     *
* 2) Unless to the extent explicitly permitted by law, no reverse                     *
*    engineering, decompilation, or disassembly of is permitted.                      *
*                                                                                     *
* 3) Redistribution and use is permitted solely for the purpose of                    *
*    developing or executing applications that are targeted for use                   *
*    on an ARM-based product.                                                         *
*                                                                                     *
* DISCLAIMER. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND                  *
* CONTRIBUTORS "AS IS." ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT             *
* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT,        *
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE          *
* COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED            *
* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR              *
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF              *
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING                *
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                  *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                        *
**************************************************************************************/


#ifndef  _SSI_PAL_FIPS_H
#define  _SSI_PAL_FIPS_H

/*!
@file
@brief This file contains definitions that are used by the FIPS related APIs. The implementation of these functions
need to be replaced according to Platform and OS.
*/

#include "ssi_pal_types_plat.h"
#include "crys_fips.h"
#include "crys_fips_defs.h"

/**
 * @brief This function purpose is to get the FIPS state.
 *
 *
 * @return Zero on success.
 * @return A non-zero value on failure.
 */
SaSiError_t SaSi_PalFipsGetState(CC_FipsState_t *pFipsState);


/**
 * @brief This function purpose is to get the FIPS Error.
 *
 *
 * @return Zero on success.
 * @return A non-zero value on failure.
 */
SaSiError_t SaSi_PalFipsGetError(CC_FipsError_t *pFipsError);


/**
 * @brief This function purpose is to get the FIPS trace.
 *
 *
 * @return Zero on success.
 * @return A non-zero value on failure.
 */
SaSiError_t SaSi_PalFipsGetTrace(CC_FipsTrace_t *pFipsTrace);


/**
 * @brief This function purpose is to set the FIPS state.
 *
 *
 * @return Zero on success.
 * @return A non-zero value on failure.
 */
SaSiError_t SaSi_PalFipsSetState(CC_FipsState_t fipsState);


/**
 * @brief This function purpose is to set the FIPS error.
 *
 *
 * @return Zero on success.
 * @return A non-zero value on failure.
 */
SaSiError_t SaSi_PalFipsSetError(CC_FipsError_t fipsError);


/**
 * @brief This function purpose is to set the FIPS trace.
 *
 *
 * @return Zero on success.
 * @return A non-zero value on failure.
 */
SaSiError_t SaSi_PalFipsSetTrace(CC_FipsTrace_t fipsTrace);


/**
 * @brief This function should push the FIPS TEE library error towards the REE library,
 *        the FIPS error can occur while running KAT tests at library init or while running
 *        conditional or continues tests
 *
 * @return Zero on success.
 * @return A non-zero value on failure.
 */
SaSiError_t SaSi_PalFipsNotifyUponTeeError(void);

#endif  // _SSI_PAL_FIPS_H