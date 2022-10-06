/*
 *  \file   cache.h
 *
 *  \brief  Cache related function prototypes
 *
 *  This file contains the API prototypes for configuring ARMv7a Cache.
*/

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef __CACHE_H
#define __CACHE_H

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/*
** Macros which can be passed to CacheDisable/Enable APIs
*/
#define CACHE_ICACHE                 (0x01) /* Instruction cache */
#define CACHE_DCACHE                 (0x02) /* Data and Unified cache*/
#define CACHE_ALL                    (0x03) /* Instruction, Data and Unified
                                               Cache at all levels*/

/*****************************************************************************/
/*
** API prototypes
*/
extern void CacheEnable(unsigned int enFlag);
extern void CacheDisable(unsigned int disFlag);
extern void CacheInstInvalidateAll(void);
extern void CacheInstInvalidateBuff(unsigned int startAddr,
                                    unsigned int numBytes);
extern void CacheDataCleanInvalidateAll(void);
extern void CacheDataCleanAll(void);
extern void CacheDataInvalidateAll(void);
extern void CacheDataCleanBuff(unsigned int startAddr,
                               unsigned int numBytes);

extern void CacheDataInvalidateBuff(unsigned int startAddr,
                                    unsigned int numBytes);

extern void CacheDataCleanInvalidateBuff(unsigned int startAddr,
                                         unsigned int numBytes);

#ifdef __cplusplus
}
#endif
#endif /* __CACHE_H__ */

