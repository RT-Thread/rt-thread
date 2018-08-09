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



#ifndef PKA_HW_PLAT_DEFS_H
#define PKA_HW_PLAT_DEFS_H

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief Contains the enums and definitions that are used in the PKA code (definitions that are platform dependent).
@defgroup ssi_pka_hw_plat_defs CryptoCell PKA specific types and definitions
@{
@ingroup cryptocell_pka

*/

/*! Size of PKA engine word.*/
#define SASI_PKA_WORD_SIZE_IN_BITS  64
/*! Maximal supported modulus size in bits. */
#define CRYS_SRP_MAX_MODULUS_SIZE_IN_BITS       3072
/*! Maximal supported modulus size in RSA in bits. */
#define CRYS_RSA_MAX_VALID_KEY_SIZE_VALUE_IN_BITS       2048
/*! Maximal supported key generation size in RSA in bits. */
#define CRYS_RSA_MAX_KEY_GENERATION_HW_SIZE_BITS        2048

/*! PKA operations maximal count of extra bits. */
#define PKA_EXTRA_BITS  8
/*! PKA operations number of memory registers. */
#define PKA_MAX_COUNT_OF_PHYS_MEM_REGS  32


#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif //PKA_HW_PLAT_DEFS_H


