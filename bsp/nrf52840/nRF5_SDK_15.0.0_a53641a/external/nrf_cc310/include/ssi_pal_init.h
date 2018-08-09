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



#ifndef _SSI_PAL_INIT_H
#define _SSI_PAL_INIT_H

#include "ssi_pal_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This file contains the PAL layer entry point, it includes the definitions and APIs for PAL initialization and termination.
@defgroup ssi_pal_init CryptoCell PAL entry\exit point APIs
@{
@ingroup ssi_pal

*/

/**
 * @brief This function Performs all initializations that may be required by the customer's PAL implementation, specifically by the DMA-able buffer
 *  scheme. The existing implementation allocates a contiguous memory pool that is later used by the ARM TrustZone CryptoCell TEE implementation.
 *  In case no initializations are needed in the customer's environment, the function can be minimized to return OK.
 *      It is called by ::SaSi_LibInit.
 *
 * @return A non-zero value in case of failure.
 */
int SaSi_PalInit(void);



/**
 * @brief This function is used to terminate the PAL implementation and free the resources that were taken by ::SaSi_PalInit.
 *
 * @return Void.
 */
void SaSi_PalTerminate(void);



#ifdef __cplusplus
}
#endif
/**
@}
 */
#endif


