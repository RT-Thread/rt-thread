/* ------------------------------------------
 * Copyright (c) 2016, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * \version 2016.05
 * \date 2014-06-12
 * \author Wayne Ren(Wei.Ren@synopsys.com)
--------------------------------------------- */

/**
 * \file
 * \ingroup ARC_HAL_CORE_EM
 * \brief header file of EM series
 */

/**
 * \addtogroup ARC_HAL_CORE_EM
 * @{
 */

#ifndef _ARC_HAL_EM_H_
#define _ARC_HAL_EM_H_

#include "inc/arc/arc.h"

#define AUX_ACC0_LO		(0x580)
#define AUX_ACC0_GLO		(0x581)
#define AUX_ACC0_HI		(0x582)
#define AUX_ACC0_GHI		(0x583)
#define AUX_DSP_BFLY0		(0x598)
#define AUX_DSP_FFT_CTRL	(0x59e)
#define AUX_DSP_CTRL		(0x59f)

#define AUX_AGU_AUX_AP0		(0x5c0)
#define AUX_AGU_AUX_AP1		(0x5c1)
#define AUX_AGU_AUX_AP2		(0x5c2)
#define AUX_AGU_AUX_AP3		(0x5c3)
#define AUX_AGU_AUX_AP4		(0x5c4)
#define AUX_AGU_AUX_AP5		(0x5c5)
#define AUX_AGU_AUX_AP6		(0x5c6)
#define AUX_AGU_AUX_AP7		(0x5c7)
#define AUX_AGU_AUX_AP8		(0x5c8)
#define AUX_AGU_AUX_AP9		(0x5c9)
#define AUX_AGU_AUX_AP10	(0x5ca)
#define AUX_AGU_AUX_AP11	(0x5cb)
#define AUX_AGU_AUX_AP12	(0x5cc)
#define AUX_AGU_AUX_AP13	(0x5cd)
#define AUX_AGU_AUX_AP14	(0x5ce)
#define AUX_AGU_AUX_AP15	(0x5cf)

#define AUX_AGU_AXU_OS0		(0x5d0)
#define AUX_AGU_AXU_OS1		(0x5d1)
#define AUX_AGU_AXU_OS2		(0x5d2)
#define AUX_AGU_AXU_OS3		(0x5d3)
#define AUX_AGU_AXU_OS4		(0x5d4)
#define AUX_AGU_AXU_OS5		(0x5d5)
#define AUX_AGU_AXU_OS6		(0x5d6)
#define AUX_AGU_AXU_OS7		(0x5d7)
#define AUX_AGU_AXU_OS8		(0x5d8)
#define AUX_AGU_AXU_OS9		(0x5d9)
#define AUX_AGU_AXU_OS10	(0x5da)
#define AUX_AGU_AXU_OS11	(0x5db)
#define AUX_AGU_AXU_OS12	(0x5dc)
#define AUX_AGU_AXU_OS13	(0x5dd)
#define AUX_AGU_AXU_OS14	(0x5de)
#define AUX_AGU_AXU_OS15	(0x5df)

#define	AUX_AGU_AUX_MOD0	(0x5e0)
#define	AUX_AGU_AUX_MOD1	(0x5e1)
#define	AUX_AGU_AUX_MOD2	(0x5e2)
#define	AUX_AGU_AUX_MOD3	(0x5e3)
#define	AUX_AGU_AUX_MOD4	(0x5e4)
#define	AUX_AGU_AUX_MOD5	(0x5e5)
#define	AUX_AGU_AUX_MOD6	(0x5e6)
#define	AUX_AGU_AUX_MOD7	(0x5e7)
#define	AUX_AGU_AUX_MOD8	(0x5e8)
#define	AUX_AGU_AUX_MOD9	(0x5e9)
#define	AUX_AGU_AUX_MOD10	(0x5ea)
#define	AUX_AGU_AUX_MOD11	(0x5eb)
#define	AUX_AGU_AUX_MOD12	(0x5ec)
#define	AUX_AGU_AUX_MOD13	(0x5ed)
#define	AUX_AGU_AUX_MOD14	(0x5ee)
#define	AUX_AGU_AUX_MOD15	(0x5ef)
#define	AUX_AGU_AUX_MOD16	(0x5f0)
#define	AUX_AGU_AUX_MOD17	(0x5f1)
#define	AUX_AGU_AUX_MOD18	(0x5f2)
#define	AUX_AGU_AUX_MOD19	(0x5f3)
#define	AUX_AGU_AUX_MOD20	(0x5f4)
#define	AUX_AGU_AUX_MOD21	(0x5f5)
#define	AUX_AGU_AUX_MOD22	(0x5f6)
#define	AUX_AGU_AUX_MOD23	(0x5f7)

#define AUX_XCCM_BASE		(0x5f8)
#define AUX_YCCM_BASE		(0x5f9)


/** \todo add em series specific definitions here */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* _ARC_HAL_EM_H_ */

/** @} */
