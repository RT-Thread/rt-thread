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
#ifndef NRF_CC310_BL_ECDSA_VERIFY_COMMON_H__
#define NRF_CC310_BL_ECDSA_VERIFY_COMMON_H__

/**@file
 *
 * @defgroup nrf_cc310_bl_ecdsa_verify_common nrf_cc310_bl ECDSA verify common declarations
 * @ingroup nrf_cc310_bl
 * @brief Common declarations for nrf_cc310_bl ECDSA verify APIs.
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#define NRF_CC310_BL_ECDSA_CONTEXT_INITIALIZED (0xBBAA55DD)

#define NRF_CC310_BL_ECDSA_VERIFY_CONTEXT_SIZE_SECP224R1   (140)     //!< Macro for the size of the ECDSA Verify context.
#define NRF_CC310_BL_ECDSA_VERIFY_CONTEXT_SIZE_SECP256R1   (160)     //!< Macro for the size of the ECDSA Verify context.

#ifdef __cplusplus
}
#endif

/** @} */


#endif // NRF_CC310_BL_ECDSA_VERIFY_COMMON_H__
